#include "Vocabulary.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace rare::tokenizer {
namespace {

std::string json_escape(const std::string& value) {
    std::ostringstream out;
    for (unsigned char c : value) {
        switch (c) {
            case '"': out << "\\\""; break;
            case '\\': out << "\\\\"; break;
            case '\n': out << "\\n"; break;
            case '\r': out << "\\r"; break;
            case '\t': out << "\\t"; break;
            default:
                if (c < 0x20) {
                    const char* hex = "0123456789abcdef";
                    out << "\\u00" << hex[c >> 4] << hex[c & 0x0f];
                } else {
                    out << static_cast<char>(c);
                }
        }
    }
    return out.str();
}

} // namespace

void Vocabulary::clear() {
    token_to_id_.clear();
    id_to_token_.clear();
}

bool Vocabulary::contains(const std::string& token) const {
    return token_to_id_.find(token) != token_to_id_.end();
}

std::uint32_t Vocabulary::id_for(const std::string& token) const {
    const auto it = token_to_id_.find(token);
    return it == token_to_id_.end() ? kUnknownId : it->second;
}

const std::string& Vocabulary::token_for(std::uint32_t id) const {
    if (id >= id_to_token_.size()) {
        throw std::out_of_range("Vocabulary token ID out of range");
    }
    return id_to_token_[id];
}

std::uint32_t Vocabulary::add(const std::string& token) {
    const auto existing = token_to_id_.find(token);
    if (existing != token_to_id_.end()) {
        return existing->second;
    }

    const auto id = static_cast<std::uint32_t>(id_to_token_.size());
    token_to_id_.emplace(token, id);
    id_to_token_.push_back(token);
    return id;
}

std::size_t Vocabulary::size() const noexcept {
    return id_to_token_.size();
}

bool Vocabulary::save_json(const std::string& path) const {
    std::ofstream out(path, std::ios::binary);
    if (!out) return false;

    out << "{\n  \"tokens\": [\n";
    for (std::size_t i = 0; i < id_to_token_.size(); ++i) {
        out << "    {\"id\": " << i << ", \"token\": \""
            << json_escape(id_to_token_[i]) << "\"}";
        if (i + 1 != id_to_token_.size()) out << ',';
        out << '\n';
    }
    out << "  ]\n}\n";
    return true;
}

bool Vocabulary::load_json(const std::string&) {
    // Intentionally left for the next implementation pass. The encoder can
    // load a tokenizer through a dedicated binary/validated format later.
    return false;
}

} // namespace rare::tokenizer
