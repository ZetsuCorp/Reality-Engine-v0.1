#include "BPE.h"

#include <cstddef>
#include <fstream>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace rare::tokenizer {

BPE::BPE() = default;

std::size_t BPE::PairHash::operator()(
    const std::pair<std::string, std::string>& pair) const noexcept {
    const std::size_t h1 = std::hash<std::string>{}(pair.first);
    const std::size_t h2 = std::hash<std::string>{}(pair.second);
    return h1 ^ (h2 + static_cast<std::size_t>(0x9e3779b9) + (h1 << 6U) + (h1 >> 2U));
}

namespace {

using Symbol = std::string;
using Sequence = std::vector<Symbol>;
using Pair = std::pair<Symbol, Symbol>;


std::vector<Symbol> byteSymbols(const std::string& text) {
    std::vector<Symbol> symbols;
    symbols.reserve(text.size());

    for (unsigned char byte : text) {
        symbols.emplace_back(1, static_cast<char>(byte));
    }

    return symbols;
}

std::unordered_map<Pair, std::size_t, BPE::PairHash> countPairs(
    const std::vector<Sequence>& sequences) {
    std::unordered_map<Pair, std::size_t, BPE::PairHash> counts;

    for (const Sequence& sequence : sequences) {
        if (sequence.size() < 2) {
            continue;
        }

        for (std::size_t i = 0; i + 1 < sequence.size(); ++i) {
            ++counts[{sequence[i], sequence[i + 1]}];
        }
    }

    return counts;
}

Pair mostFrequentPair(
    const std::unordered_map<Pair, std::size_t, BPE::PairHash>& counts,
    std::size_t minPairFrequency) {
    Pair best;
    std::size_t bestCount = 0;

    for (const auto& [pair, count] : counts) {
        if (count > bestCount ||
            (count == bestCount && (best.first.empty() || pair < best))) {
            best = pair;
            bestCount = count;
        }
    }

    if (bestCount == 0 || bestCount < minPairFrequency) {
        return {};
    }

    return best;
}

Sequence mergePair(const Sequence& sequence, const Pair& target) {
    Sequence merged;
    merged.reserve(sequence.size());

    for (std::size_t i = 0; i < sequence.size();) {
        if (i + 1 < sequence.size() &&
            sequence[i] == target.first &&
            sequence[i + 1] == target.second) {
            merged.push_back(target.first + target.second);
            i += 2;
        } else {
            merged.push_back(sequence[i]);
            ++i;
        }
    }

    return merged;
}

} // namespace

void BPE::clear() {
    merges_.clear();
    mergeRanks_.clear();
}

void BPE::train(
    const std::vector<std::string>& corpus,
    std::size_t mergeCount,
    std::size_t minPairFrequency) {
    clear();

    std::vector<Sequence> sequences;
    sequences.reserve(corpus.size());

    for (const std::string& text : corpus) {
        sequences.push_back(byteSymbols(text));
    }

    for (std::size_t iteration = 0; iteration < mergeCount; ++iteration) {
        const auto counts = countPairs(sequences);
        const Pair best = mostFrequentPair(counts, minPairFrequency);

        if (best.first.empty() && best.second.empty()) {
            break;
        }

        const std::size_t rank = merges_.size();
        merges_.push_back({best.first, best.second});
        mergeRanks_.emplace(best, rank);

        for (Sequence& sequence : sequences) {
            sequence = mergePair(sequence, best);
        }
    }
}

std::vector<std::string> BPE::apply(const std::string& text) const {
    Sequence sequence = byteSymbols(text);

    if (sequence.empty() || merges_.empty()) {
        return sequence;
    }

    while (sequence.size() > 1) {
        std::size_t bestRank = std::numeric_limits<std::size_t>::max();
        Pair bestPair;
        bool found = false;

        for (std::size_t i = 0; i + 1 < sequence.size(); ++i) {
            const Pair pair{sequence[i], sequence[i + 1]};
            const auto it = mergeRanks_.find(pair);

            if (it != mergeRanks_.end() && it->second < bestRank) {
                bestRank = it->second;
                bestPair = pair;
                found = true;
            }
        }

        if (!found) {
            break;
        }

        sequence = mergePair(sequence, bestPair);
    }

    return sequence;
}

const std::vector<BPE::Merge>& BPE::merges() const noexcept {
    return merges_;
}

namespace {

// Byte-level symbols can contain any byte, including '\t', '\n', '\\'.
// Escape those so merges.txt stays one merge per line.
std::string escapeSymbol(const std::string& symbol) {
    std::string out;
    out.reserve(symbol.size());
    for (const char c : symbol) {
        switch (c) {
            case '\\': out += "\\\\"; break;
            case '\t': out += "\\t"; break;
            case '\n': out += "\\n"; break;
            default: out += c; break;
        }
    }
    return out;
}

std::string unescapeSymbol(const std::string& symbol) {
    std::string out;
    out.reserve(symbol.size());
    for (std::size_t i = 0; i < symbol.size(); ++i) {
        if (symbol[i] == '\\' && i + 1 < symbol.size()) {
            const char next = symbol[i + 1];
            if (next == '\\') { out += '\\'; ++i; continue; }
            if (next == 't') { out += '\t'; ++i; continue; }
            if (next == 'n') { out += '\n'; ++i; continue; }
        }
        out += symbol[i];
    }
    return out;
}

} // namespace

bool BPE::save_merges(const std::string& path) const {
    std::ofstream out(path, std::ios::trunc);
    if (!out.is_open()) {
        return false;
    }

    for (const Merge& merge : merges_) {
        out << escapeSymbol(merge.first) << '\t'
            << escapeSymbol(merge.second) << '\n';
    }

    return static_cast<bool>(out);
}

bool BPE::load_merges(const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open()) {
        return false;
    }

    clear();

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) {
            continue;
        }

        const std::size_t tab = line.find('\t');
        if (tab == std::string::npos) {
            continue;
        }

        Merge merge;
        merge.first = unescapeSymbol(line.substr(0, tab));
        merge.second = unescapeSymbol(line.substr(tab + 1));

        const std::size_t rank = merges_.size();
        merges_.push_back(merge);
        mergeRanks_.emplace(Pair{merge.first, merge.second}, rank);
    }

    return true;
}

} // namespace rare::tokenizer
