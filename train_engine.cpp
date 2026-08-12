#include "BPE.h"
#include "Trainer.h"
#include "Vocabulary.h"
#include "Encoder.h"
#include "Decoder.h"

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace {

std::string readFile(const fs::path& path) {
    std::ifstream in(path, std::ios::binary);
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

} // namespace

int main() {
    using namespace rare::tokenizer;

    // ---- 1. Load corpus (Instructions + control docs only) ----
    std::vector<std::string> corpus;
    const fs::path corpusDir = "corpus";

    for (const auto& entry : fs::directory_iterator(corpusDir)) {
        if (entry.is_regular_file()) {
            corpus.push_back(readFile(entry.path()));
        }
    }

    std::cout << "Loaded " << corpus.size() << " corpus files.\n";

    // ---- 2. Build base vocabulary: <UNK> + 256 bytes + reserved specials ----
    Vocabulary vocab;
    vocab.add("<UNK>"); // id 0, matches Vocabulary::kUnknownId

    for (int b = 0; b < 256; ++b) {
        vocab.add(std::string(1, static_cast<char>(b)));
    }

    // Runtime state names and commands, drawn directly from
    // Instructions/Definitions.md and BOOT.md. These must always be
    // emitted as one atomic ID, never left to BPE merge luck.
    const std::vector<std::string> specialTokens = {
        "NOT INITIALIZED",
        "INITIALIZING",
        "LOADED REALITY",
        "ACTIVE REALITY",
        "REFERENCE INCOMPLETE",
        "VALIDATION FAILED",
        "START REALITY",
        "CONFIRM REALITY",
        "INSPECTED",
        "UNINSPECTED",
    };

    for (const std::string& token : specialTokens) {
        vocab.add(token);
    }

    std::cout << "Base vocabulary (before merges): " << vocab.size() << "\n";

    // ---- 3. Train BPE on the corpus ----
    BPETrainer::Config config;
    config.target_vocab_size = 1500;
    config.min_pair_frequency = 3; // reject one-off/coincidental pairs
    BPETrainer trainer(config);

    BPE bpe = trainer.train(corpus);
    std::cout << "Learned merges: " << bpe.merges().size() << "\n";

    // ---- 4. Add learned merges to the vocabulary ----
    for (const auto& merge : bpe.merges()) {
        vocab.add(merge.first + merge.second);
    }

    std::cout << "Final vocabulary size: " << vocab.size() << "\n";

    // ---- 5. Persist real artifacts ----
    if (!bpe.save_merges("merges.txt")) {
        std::cerr << "Failed to save merges.txt\n";
        return 1;
    }
    if (!vocab.save_json("vocabulary.json")) {
        std::cerr << "Failed to save vocabulary.json\n";
        return 1;
    }
    std::cout << "Wrote merges.txt and vocabulary.json\n";

    // ---- 6. Verify special tokens and round-trip on real cartridge text ----
    Encoder encoder(bpe, vocab);
    encoder.set_special_tokens(specialTokens);
    Decoder decoder(vocab);

    const std::vector<std::string> checks = {
        "The Runtime is now in ACTIVE REALITY.",
        "If validation fails, enter VALIDATION FAILED and revise the content.",
        "The Runtime begins the transition from NOT INITIALIZED to INITIALIZING.",
        "A visual reference shall be considered UNINSPECTED until examined.",
        "Reality Model and Reality Cartridge and Reality Architect.",
    };

    bool allOk = true;
    for (const std::string& text : checks) {
        const auto ids = encoder.encode(text);
        const std::string decoded = decoder.decode(ids);
        const bool ok = (decoded == text);
        allOk = allOk && ok;
        std::cout << "\n[" << (ok ? "OK" : "MISMATCH") << "] \"" << text << "\"\n";
        std::cout << "  tokens: " << ids.size() << "\n";
    }

    // Confirm a special token collapses to exactly one ID
    {
        const auto ids = encoder.encode("ACTIVE REALITY");
        std::cout << "\n\"ACTIVE REALITY\" -> " << ids.size() << " token(s)";
        if (ids.size() == 1) {
            std::cout << " (id " << ids[0] << ", atomic - correct)\n";
        } else {
            std::cout << " (NOT atomic - FAIL)\n";
            allOk = false;
        }
    }

    std::cout << "\n" << (allOk ? "ALL CHECKS PASSED" : "SOME CHECKS FAILED") << "\n";
    return allOk ? 0 : 1;
}
