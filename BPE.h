#include "Trainer.h"

#include <algorithm>
#include <fstream>
#include <limits>
#include <unordered_map>
#include <vector>

namespace rare::tokenizer {
namespace {

struct PairCount {
    BytePair pair;
    std::size_t count = 0;
};

std::vector<std::string> bytes_of(const std::string& text) {
    std::vector<std::string> result;
    result.reserve(text.size());
    for (unsigned char byte : text) {
        result.emplace_back(1, static_cast<char>(byte));
    }
    return result;
}

} // namespace

Trainer::Trainer(TrainerConfig config)
    : config_(std::move(config)) {}

bool Trainer::train(BPE& bpe, Vocabulary& vocabulary) {
    std::ifstream corpus(config_.corpus_path, std::ios::binary);
    if (!corpus) return false;

    std::string text((std::istreambuf_iterator<char>(corpus)),
                     std::istreambuf_iterator<char>());

    vocabulary.clear();
    for (int i = 0; i < 256; ++i) {
        vocabulary.add(std::string(1, static_cast<char>(i)));
    }

    std::vector<std::string> symbols = bytes_of(text);
    BPE::MergeMap merges;

    const std::size_t target_merges =
        config_.vocabulary_size > 256 ? config_.vocabulary_size - 256 : 0;

    for (std::size_t rank = 0; rank < target_merges && symbols.size() > 1; ++rank) {
        std::unordered_map<BytePair, std::size_t, BytePairHash> counts;
        for (std::size_t i = 0; i + 1 < symbols.size(); ++i) {
            ++counts[BytePair{symbols[i], symbols[i + 1]}];
        }

        BytePair best;
        std::size_t best_count = 0;
        bool found = false;

        for (const auto& entry : counts) {
            if (entry.second > best_count) {
                best = entry.first;
                best_count = entry.second;
                found = true;
            }
        }

        if (!found || best_count < 2) break;

        merges.emplace(best, rank);
        vocabulary.add(best.left + best.right);

        std::vector<std::string> next;
        next.reserve(symbols.size());
        for (std::size_t i = 0; i < symbols.size();) {
            if (i + 1 < symbols.size() && symbols[i] == best.left && symbols[i + 1] == best.right) {
                next.push_back(symbols[i] + symbols[i + 1]);
                i += 2;
            } else {
                next.push_back(symbols[i]);
                ++i;
            }
        }
        symbols.swap(next);
    }

    bpe.set_merges(std::move(merges));

    std::ofstream merges_out(config_.merges_output_path, std::ios::binary);
    if (!merges_out) return false;
    merges_out << "# R.A.R.E. byte-level BPE merges\n";

    std::vector<std::pair<std::size_t, BytePair>> ordered;
    ordered.reserve(bpe.merges().size());
    for (const auto& entry : bpe.merges()) {
        ordered.emplace_back(entry.second, entry.first);
    }
    std::sort(ordered.begin(), ordered.end(),
              [](const auto& a, const auto& b) { return a.first < b.first; });

    auto hex = [](const std::string& value) {
        static const char* digits = "0123456789ABCDEF";
        std::string out;
        for (unsigned char c : value) {
            out += digits[c >> 4];
            out += digits[c & 0x0F];
        }
        return out;
    };

    for (const auto& [rank, pair] : ordered) {
        merges_out << rank << ' ' << hex(pair.left) << ' ' << hex(pair.right) << '\n';
    }

    return vocabulary.save_json(config_.vocabulary_output_path);
}

} // namespace rare::tokenizer
