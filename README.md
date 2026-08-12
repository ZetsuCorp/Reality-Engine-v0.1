# Reality Engine

**Reality Engine** is the runtime. It's the system that loads a Reality and operates inside it — not skimming files and guessing, but building an actual model of what's true: canon, entities, relationships, visual language, rules.

**Reality Cartridge** is what it loads. A portable package holding a Reality's Instructions (how to read it), Story, and Visuals. Any Cartridge plugs into any compatible Engine and runs the same way, every time.

**R.A.R.E. (Reality Architect Reality Engine)** is the algorithm that connects the two. It's what the Engine runs the moment a Cartridge is loaded — Context Analysis → Visual Analysis → Reality Synthesis → Reality Model → Inference → Generation → Reality Evolution. It's the process that turns a static Cartridge into an active Reality the AI can actually operate inside.

Together, Engine + Cartridge + R.A.R.E. produce a Reality Model — a living, structured representation of a world that an AI reasons from directly, instead of re-estimating its understanding from scratch every message.

## What's in this repo

This repo is the tokenizer — the first piece of the Engine, and the layer everything else depends on. It determines how the Engine physically receives text: Instructions, Story, and Visual descriptions alike, converted into the token IDs the rest of the system operates on. Runtime states and commands (`ACTIVE REALITY`, `VALIDATION FAILED`, `START REALITY`, etc.) are reserved as atomic tokens, so the Engine never has those split apart by ordinary merge training.

- `BPE.*` — byte-level BPE: learns merges from a corpus, applies them at inference.
- `Trainer.*` — `BPETrainer`, the training wrapper around `BPE`.
- `Vocabulary.*` — token ↔ ID mapping.
- `Encoder.*` / `Decoder.*` — text ↔ token IDs.
- `train_engine.cpp` — trains on the Instructions layer (shared by every Cartridge), never on Story or Visuals.
- `corpus/` — the Instructions-layer training data.
- `merges.txt` / `vocabulary.json` — generated tokenizer output.

Built from scratch — byte-level, zero external dependency, no borrowed tokenizer.
