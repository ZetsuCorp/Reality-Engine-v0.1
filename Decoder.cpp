#include "Decoder.h"

namespace rare::tokenizer {

Decoder::Decoder(const Vocabulary& vocabulary)
    : vocabulary_(vocabulary) {}

std::string Decoder::decode(
    const std::vector<std::uint32_t>& ids) const {

    std::string text;

    for (const auto id : ids) {
        if (id == Vocabulary::kUnknownId)
            continue;

        text += vocabulary_.token_for(id);
    }

    return text;
}

} // namespace rare::tokenizer
