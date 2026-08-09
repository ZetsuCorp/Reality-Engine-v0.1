#pragma once

#include "BPE.h"
#include "Vocabulary.h"

#include <cstddef>
#include <string>

namespace rare::tokenizer {

struct TrainerConfig {
    std::size_t vocabulary_size = 8192;
    std::string corpus_path;
    std::string merges_output_path = "merges.txt";
    std::string vocabulary_output_path = "vocabulary.json";
};

class Trainer {
public:
    explicit Trainer(TrainerConfig config);

    // Trains a byte-level BPE tokenizer from the configured corpus.
    bool train(BPE& bpe, Vocabulary& vocabulary);

private:
    TrainerConfig config_;
};

} // namespace rare::tokenizer
