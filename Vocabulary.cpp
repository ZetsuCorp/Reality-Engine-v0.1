#include "Vocabulary.h"

#include <cstdint>
#include <fstream>
#include <limits>
#include <string>

namespace rare::tokenizer {
namespace {

std::string json_escape(const std::string& value) {
    std::string result;
    result.reserve(value.size());

    for (unsigned char c : value) {
        switch (c) {
        case '"':
            result += "\\\"";
            break;
        case '\\':
            result += "\\\\";
            break;
        case '\b':
            result += "\\b";
            break;
        case '\f':
            result += "\\f";
            break;
        case '\n':
            result += "\\n";
            break;
        case '\r':
            result += "\\r";
            break;
        case '\t':
            result += "\\t";
            break;
        default:
            if (c < 0x20) {
                const char* hex = "0123456789abcdef";
                result += "\\u00";
                result += hex[(c >> 4) & 0x0F];
                result += hex[c & 0x0F];
            } else {
                result += static_cast<char>(c);
            }
            break;
        }
    }

    return result;
}

bool json_unescape(
    const std::string& input,
    std::size_t& pos,
    std::string& output) {

    if (pos >= input.size() || input[pos] != '"') {
        return false;
    }

    ++pos;
    output.clear();

    while (pos < input.size()) {
        const char c = input[pos++];

        if (c == '"') {
            return true;
        }

        if (c != '\\') {
            output += c;
            continue;
        }

        if (pos >= input.size()) {
            return false;
        }

        switch (input[pos++]) {
        case '"':
            output += '"';
            break;
        case '\\':
            output += '\\';
            break;
        case '/':
            output += '/';
            break;
        case 'b':
            output += '\b';
            break;
        case 'f':
            output += '\f';
            break;
        case 'n':
            output += '\n';
            break;
        case 'r':
            output += '\r';
            break;
        case 't':
            output += '\t';
            break;
        default:
            return false;
        }
    }

    return false;
}

void skip_whitespace(const std::string& text, std::size_t& pos) {
    while (pos < text.size()) {
        const char c = text[pos];

        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            ++pos;
        } else {
            break;
        }
    }
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

    if (it == token_to_id_.end()) {
        return kUnknownId;
    }

    return it->second;
}

const std::string& Vocabulary::token_for(std::uint32_t id) const {
    static const std::string unknown = "<UNK>";

    if (id >= id_to_token_.size()) {
        return unknown;
    }

    return id_to_token_[id];
}

std::uint32_t Vocabulary::add(const std::string& token) {
    const auto existing = token_to_id_.find(token);

    if (existing != token_to_id_.end()) {
        return existing->second;
    }

    if (id_to_token_.size() >=
        static_cast<std::size_t>(std::numeric_limits<std::uint32_t>::max())) {
        return kUnknownId;
    }

    const std::uint32_t id =
        static_cast<std::uint32_t>(id_to_token_.size());

    token_to_id_[token] = id;
    id_to_token_.push_back(token);

    return id;
}

std::size_t Vocabulary::size() const noexcept {
    return id_to_token_.size();
}

bool Vocabulary::save_json(const std::string& path) const {
    std::ofstream file(path, std::ios::binary);

    if (!file) {
        return false;
    }

    file << "{\n";
    file << "  \"tokens\": [\n";

    for (std::size_t i = 0; i < id_to_token_.size(); ++i) {
        file << "    \""
             << json_escape(id_to_token_[i])
             << "\"";

        if (i + 1 < id_to_token_.size()) {
            file << ",";
        }

        file << "\n";
    }

    file << "  ]\n";
    file << "}\n";

    return static_cast<bool>(file);
}

bool Vocabulary::load_json(const std::string& path) {
    std::ifstream file(path, std::ios::binary);

    if (!file) {
        return false;
    }

    const std::string text(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());

    std::size_t pos = 0;

    skip_whitespace(text, pos);

    if (pos >= text.size() || text[pos++] != '{') {
        return false;
    }

    skip_whitespace(text, pos);

    std::string key;

    if (!json_unescape(text, pos, key) || key != "tokens") {
        return false;
    }

    skip_whitespace(text, pos);

    if (pos >= text.size() || text[pos++] != ':') {
        return false;
    }

    skip_whitespace(text, pos);

    if (pos >= text.size() || text[pos++] != '[') {
        return false;
    }

    Vocabulary loaded;

    skip_whitespace(text, pos);

    if (pos < text.size() && text[pos] == ']') {
        ++pos;
    } else {
        while (true) {
            skip_whitespace(text, pos);

            std::string token;

            if (!json_unescape(text, pos, token)) {
                return false;
            }

            loaded.add(token);

            skip_whitespace(text, pos);

            if (pos >= text.size()) {
                return false;
            }

            if (text[pos] == ']') {
                ++pos;
                break;
            }

            if (text[pos] != ',') {
                return false;
            }

            ++pos;
        }
    }

    skip_whitespace(text, pos);

    if (pos >= text.size() || text[pos++] != '}') {
        return false;
    }

    skip_whitespace(text, pos);

    if (pos != text.size()) {
        return false;
    }

    token_to_id_ = std::move(loaded.token_to_id_);
    id_to_token_ = std::move(loaded.id_to_token_);

    return true;
}

} // namespace rare::tokenizer
