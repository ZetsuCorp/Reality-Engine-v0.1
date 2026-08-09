#include "Vocabulary.h"

Vocabulary::Vocabulary()
    : nextId(4)
{
    idToToken.reserve(4);

    idToToken.push_back("<PAD>");
    idToToken.push_back("<UNK>");
    idToToken.push_back("<BOS>");
    idToToken.push_back("<EOS>");

    tokenToId.emplace("<PAD>", PAD_ID);
    tokenToId.emplace("<UNK>", UNK_ID);
    tokenToId.emplace("<BOS>", BOS_ID);
    tokenToId.emplace("<EOS>", EOS_ID);
}

uint32_t Vocabulary::addToken(const std::string& token)
{
    auto it = tokenToId.find(token);

    if (it != tokenToId.end())
        return it->second;

    const uint32_t id = nextId++;

    tokenToId.emplace(token, id);
    idToToken.push_back(token);

    return id;
}

uint32_t Vocabulary::getTokenId(const std::string& token) const
{
    auto it = tokenToId.find(token);

    if (it != tokenToId.end())
        return it->second;

    return UNK_ID;
}

const std::string& Vocabulary::getToken(uint32_t id) const
{
    if (id < idToToken.size())
        return idToToken[id];

    return idToToken[UNK_ID];
}

bool Vocabulary::contains(const std::string& token) const
{
    return tokenToId.find(token) != tokenToId.end();
}

std::size_t Vocabulary::size() const
{
    return idToToken.size();
}
