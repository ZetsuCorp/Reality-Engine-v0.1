#include "Encoder.h"

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

    const std::vector<std::string> tokens =
        bpe_->encode(text);

    std::vector<std::uint32_t> ids;
    ids.reserve(tokens.size());

    for (const std::string& token : tokens) {
        ids.push_back(vocabulary_->id_for(token));
    }

    return ids;
}

} // namespace rare::tokenizer
