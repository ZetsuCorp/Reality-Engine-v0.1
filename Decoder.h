#pragma once

#include "Vocabulary.h"

#include <cstdint>
#include <string>
#include <vector>

namespace rare::tokenizer {

class Decoder {
public:
    explicit Decoder(const Vocabulary& vocabulary);

    std::string decode(const std::vector<std::uint32_t>& ids) const;

private:
    const Vocabulary& vocabulary_;
};

} // namespace rare::tokenizer
