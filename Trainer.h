#pragma once

#include "BPE.h"
#include <cstddef>
#include <string>
#include <vector>

class BPETrainer {
public:
    using Corpus = std::vector<std::string>;

    struct Config {
        std::size_t target_vocab_size = 32000;
        std::size_t min_pair_frequency = 2;
        std::size_t max_merges = 0;
    };

    BPETrainer();
    explicit BPETrainer(const Config& config);

    void setConfig(const Config& config);
    const Config& getConfig() const noexcept;
    rare::tokenizer::BPE train(const Corpus& corpus) const;

private:
    Config config_;
    std::size_t determineMergeCount(std::size_t initialVocabularySize) const;
};
