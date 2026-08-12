#pragma once

#include "BPE.h"
#include "Vocabulary.h"

#include <cstdint>
#include <string>
#include <vector>

namespace rare::tokenizer {

class Encoder {
public:
    Encoder() = default;
    Encoder(const BPE& bpe, const Vocabulary& vocabulary);

    void set_bpe(const BPE& bpe);
    void set_vocabulary(const Vocabulary& vocabulary);

    // Reserved exact-match strings (e.g. "ACTIVE REALITY") that must always
    // be emitted as a single atomic ID, never split by BPE merges.
    // Each entry must already exist in the Vocabulary.
    void set_special_tokens(std::vector<std::string> tokens);

    std::vector<std::uint32_t> encode(const std::string& text) const;

private:
    const BPE* bpe_ = nullptr;
    const Vocabulary* vocabulary_ = nullptr;
    std::vector<std::string> specialTokens_;
};

} // namespace rare::tokenizer
