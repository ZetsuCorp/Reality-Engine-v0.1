#include "Encoder.h"

#include <algorithm>
#include <stdexcept>

namespace rare::tokenizer {

Encoder::Encoder(
    const BPE& bpe,
    const Vocabulary& vocabulary)
    : bpe_(&bpe),
      vocabulary_(&vocabulary) {
}

void Encoder::set_bpe(const BPE& bpe) {
    bpe_ = &bpe;
}

void Encoder::set_vocabulary(const Vocabulary& vocabulary) {
    vocabulary_ = &vocabulary;
}

void Encoder::set_special_tokens(std::vector<std::string> tokens) {
    // Longest-first so a longer reserved phrase is matched before a
    // shorter one that happens to be its prefix.
    std::sort(tokens.begin(), tokens.end(),
        [](const std::string& a, const std::string& b) {
            return a.size() > b.size();
        });
    specialTokens_ = std::move(tokens);
}

std::vector<std::uint32_t> Encoder::encode(
    const std::string& text) const {

    if (bpe_ == nullptr) {
        throw std::runtime_error(
            "Encoder::encode: BPE is not set.");
    }

    if (vocabulary_ == nullptr) {
        throw std::runtime_error(
            "Encoder::encode: vocabulary is not set.");
    }

    std::vector<std::uint32_t> ids;

    // Runs BPE over a plain (non-special) span and appends resulting IDs.
    const auto encodePlainSpan = [&](const std::string& span) {
        if (span.empty()) {
            return;
        }
        for (const std::string& token : bpe_->apply(span)) {
            ids.push_back(vocabulary_->id_for(token));
        }
    };

    std::size_t pos = 0;
    std::size_t spanStart = 0;

    while (pos < text.size()) {
        bool matched = false;

        for (const std::string& special : specialTokens_) {
            if (special.empty() || special.size() > text.size() - pos) {
                continue;
            }
            if (text.compare(pos, special.size(), special) == 0) {
                encodePlainSpan(text.substr(spanStart, pos - spanStart));
                ids.push_back(vocabulary_->id_for(special));
                pos += special.size();
                spanStart = pos;
                matched = true;
                break;
            }
        }

        if (!matched) {
            ++pos;
        }
    }

    encodePlainSpan(text.substr(spanStart, pos - spanStart));

    return ids;
}

} // namespace rare::tokenizer
