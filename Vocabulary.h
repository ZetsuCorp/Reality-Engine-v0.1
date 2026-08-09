#include "Encoder.h"

namespace rare::tokenizer {

Encoder::Encoder(const BPE& bpe, const Vocabulary& vocabulary)
    : bpe_(bpe), vocabulary_(vocabulary) {}

std::vector<std::uint32_t> Encoder::encode(const std::string& text) const {
    std::vector<std::string> bytes;
    bytes.reserve(text.size());

    for (unsigned char byte : text) {
        bytes.emplace_back(1, static_cast<char>(byte));
    }

    const auto merged = bpe_.apply(bytes);
    std::vector<std::uint32_t> ids;
    ids.reserve(merged.size());

    for (const auto& token : merged) {
        ids.push_back(vocabulary_.id_for(token));
    }

    return ids;
}

} // namespace rare::tokenizer
