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

    std::vector<std::uint32_t> encode(const std::string& text) const;

private:
    const BPE* bpe_ = nullptr;
    const Vocabulary* vocabulary_ = nullptr;
};

} // namespace rare::tokenizer
