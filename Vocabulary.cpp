#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace rare::tokenizer {

struct BytePair {
    std::string left;
    std::string right;

    bool operator==(const BytePair& other) const {
        return left == other.left && right == other.right;
    }
};

struct BytePairHash {
    std::size_t operator()(const BytePair& pair) const noexcept;
};

class BPE {
public:
    using MergeMap = std::unordered_map<BytePair, std::size_t, BytePairHash>;

    BPE() = default;

    void set_merges(MergeMap merges);
    const MergeMap& merges() const noexcept;

    // Applies learned merges to a sequence of byte-string symbols.
    std::vector<std::string> apply(const std::vector<std::string>& symbols) const;

    // Returns the next merge that should be applied, if any.
    bool best_merge(const std::vector<std::string>& symbols,
                    std::size_t& position,
                    BytePair& pair) const;

private:
    MergeMap merges_;
};

} // namespace rare::tokenizer
