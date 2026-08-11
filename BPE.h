#pragma once

#include <cstddef>
#include <functional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace rare::tokenizer {

class BPE {
public:
    using Symbol = std::string;
    using Pair = std::pair<std::string, std::string>;

    struct Merge {
        std::string first;
        std::string second;
    };

    struct PairHash {
        std::size_t operator()(const Pair& pair) const noexcept;
    };

    BPE();

    void clear();

    void train(
        const std::vector<std::string>& corpus,
        std::size_t mergeCount);

    std::vector<std::string> apply(
        const std::string& text) const;

    const std::vector<Merge>& merges() const noexcept;

private:
    std::vector<Merge> merges_;

    std::unordered_map<Pair, std::size_t, PairHash> mergeRanks_;
};

} // namespace rare::tokenizer
