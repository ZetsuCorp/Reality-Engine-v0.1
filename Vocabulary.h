#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

class Vocabulary
{
public:
    // Reserved token IDs
    static constexpr uint32_t PAD_ID = 0;
    static constexpr uint32_t UNK_ID = 1;
    static constexpr uint32_t BOS_ID = 2;
    static constexpr uint32_t EOS_ID = 3;

    Vocabulary();

    // Add a token if it does not already exist.
    // Returns the token's ID.
    uint32_t addToken(const std::string& token);

    // Return the ID for a token.
    // Returns UNK_ID if the token does not exist.
    uint32_t getTokenId(const std::string& token) const;

    // Return the token associated with an ID.
    // Returns <UNK> if the ID does not exist.
    const std::string& getToken(uint32_t id) const;

    // Check whether a token exists.
    bool contains(const std::string& token) const;

    // Number of tokens currently in the vocabulary.
    std::size_t size() const;

private:
    std::unordered_map<std::string, uint32_t> tokenToId;
    std::vector<std::string> idToToken;

    uint32_t nextId;
};
