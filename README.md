# R.A.R.E. Tokenizer

Initial C++ tokenizer implementation for the R.A.R.E. training pipeline.

## Components

- `BPE.*` — BPE merge representation and application.
- `Trainer.*` — learns byte-level BPE merges from a corpus and writes tokenizer data.
- `Vocabulary.*` — token/ID mapping and vocabulary serialization.
- `Encoder.*` — converts text into token IDs.
- `Decoder.*` — converts token IDs back into text.
- `merges.txt` — generated merge rules.
- `vocabulary.json` — generated vocabulary.

This first implementation deliberately uses byte-level symbols (0–255) so arbitrary UTF-8 input can be represented without a Python dependency.
