#include "Trainer.h"
#include <stdexcept>

BPETrainer::BPETrainer() = default;

BPETrainer::BPETrainer(const Config& config) : config_(config) {}

void BPETrainer::setConfig(const Config& config) {
    config_ = config;
}

const BPETrainer::Config& BPETrainer::getConfig() const noexcept {
    return config_;
}

std::size_t BPETrainer::determineMergeCount(
    std::size_t initialVocabularySize) const {
    if (config_.max_merges != 0) return config_.max_merges;
    if (config_.target_vocab_size <= initialVocabularySize) return 0;
    return config_.target_vocab_size - initialVocabularySize;
}

BPE BPETrainer::train(const Corpus& corpus) const {
    if (corpus.empty()) {
        throw std::invalid_argument("BPETrainer::train: corpus cannot be empty.");
    }
    if (config_.min_pair_frequency == 0) {
        throw std::invalid_argument("BPETrainer::train: min_pair_frequency must be greater than zero.");
    }

    constexpr std::size_t initialVocabularySize = 256;
    const std::size_t mergeCount = determineMergeCount(initialVocabularySize);

    BPE bpe;
    if (mergeCount != 0) {
        bpe.train(corpus, mergeCount, config_.min_pair_frequency);
    }
    return bpe;
}
