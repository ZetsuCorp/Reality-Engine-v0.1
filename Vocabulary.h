#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace rare::tokenizer {

class Vocabulary {
public:
    static constexpr std::uint32_t kUnknownId = 0;

    void clear();
    bool contains(const std::string& token) const;
    std::uint32_t id_for(const std::string& token) const;
    const std::string& token_for(std::uint32_t id) const;

    std::uint32_t add(const std::string& token);
    std::size_t size() const noexcept;

    bool save_json(const std::string& path) const;
    bool load_json(const std::string& path);

private:
    std::unordered_map<std::string, std::uint32_t> token_to_id_;
    std::vector<std::string> id_to_token_;
};

} // namespace rare::tokenizer
