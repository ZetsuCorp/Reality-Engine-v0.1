# Tier 1 — Foundation

These definitions establish the fundamental concepts of the Reality Engine specification. Every component of the system is built upon the relationship between a Reality, a Runtime, and a Reality Cartridge.

---

## Reality

A Reality is a complete and self-contained existence defined by its own rules, systems, history, entities, relationships, terminology, and visual language.

A Reality operates according to its own internal logic and shall be interpreted independently of real-world assumptions unless explicitly defined otherwise.

While active, the Reality serves as the highest contextual authority for the Runtime.

---

## Runtime

A Runtime is any system capable of loading, interpreting, and executing a Reality Cartridge.

Its purpose is to construct, maintain, and reason over an internal understanding of the supplied Reality in order to fulfill requests while preserving the Reality's identity and consistency.

A Runtime may be an artificial intelligence, software application, service, or any future system capable of implementing the Reality Engine specification.

---

## Reality Cartridge

A Reality Cartridge is the portable package used to communicate a Reality to a Runtime.

It contains the information necessary for the Runtime to construct an internal Reality Model, understand the Reality's established systems, and collaborate with the Reality Architect.

A Reality Cartridge is independent of any specific Runtime implementation, allowing the same Reality to be executed across multiple compatible systems while preserving its identity.



# Tier 2 — Participants

These definitions establish the active participants within the Reality Engine ecosystem.

Participants interact to construct, interpret, preserve, and expand a Reality.

---

## Reality Architect

A Reality Architect is the individual responsible for creating, defining, modifying, or expanding a Reality.

The Reality Architect establishes the Reality's identity through the creation of Reality Cartridges and through direct interaction with a Runtime.

When a Reality Cartridge is active, the Runtime shall treat the active Reality Architect as the authoritative source for new instructions, clarifications, and approved Reality expansions unless explicitly instructed otherwise.

---

## Reality Engine

A Reality Engine is a system specification that defines how a Runtime analyzes, understands, reasons about, and generates content from a Reality Cartridge.

The Reality Engine does not generate content directly.

Instead, it defines the processes, behaviors, and rules a Runtime shall follow while constructing and maintaining an internal understanding of a Reality.

Any Runtime that correctly implements the Reality Engine specification should produce consistent interpretations of the same Reality Cartridge regardless of the underlying technology.


# Tier 3 — Cartridge Components

These definitions describe the functional components that make up a Reality Cartridge.

Each component provides a specific type of information used by the Runtime to construct and operate an understanding of the Reality.

---

## Story

Story is the contextual source material of a Reality.

It establishes the Reality's events, characters, history, locations, systems, relationships, terminology, and contextual understanding.

The Runtime shall analyze Story to determine what exists, why it exists, and how the Reality operates.

---

## Visuals

Visuals are the visual source material of a Reality.

They establish the Reality's artistic identity, visual language, character design, environments, objects, color logic, rendering style, and other visual systems.

The Runtime shall analyze Visuals to determine how the Reality should appear while allowing intelligent expansion consistent with the established visual language.

---

## Instructions

Instructions define the operational behavior of the Runtime while a Reality Cartridge is active.

Instructions specify how the Runtime shall interpret, analyze, reason over, and synthesize the supplied Reality.

Instructions govern Runtime behavior.

They do not define the Reality itself.

---

## Manifest

The Manifest is the Runtime-generated inventory of the active Reality Cartridge.

It records the cartridge's discovered structure, available resources, recognized components, and any other information required for Runtime operation.

The Manifest is generated during initialization and may be updated as the Runtime's understanding of the cartridge changes.

---

## Boot

Boot is the Runtime's initialization process for a Reality Cartridge.

During Boot, the Runtime prepares the cartridge for execution by loading its components, constructing an initial Reality Model, and preparing the Reality for analysis and interaction.

Boot establishes the Runtime's starting state before normal operation begins.




# Tier 4 — Internal Concepts

These definitions describe the internal concepts used by the Runtime while constructing, understanding, and reasoning over a Reality.

Internal Concepts are not cartridge components.

They are the Runtime's interpretation of the information contained within a Reality Cartridge.

---

## Reality Model

A Reality Model is the Runtime's unified internal representation of an active Reality.

The Reality Model is constructed through the Reality Synthesis Reality Engine by combining the outputs of one or more Analysis Reality Engines.

It represents the Runtime's complete operational understanding of the active Reality and serves as the foundation for Runtime reasoning, inference, and generation.

The Reality Model continuously evolves as new Reality information is analyzed and synthesized during the active Runtime session.

---

## Canon

Canon is the collection of information accepted as true within an active Reality.

Canon is established through the Reality Cartridge and may be expanded or modified by the Reality Architect during Runtime operation.

The Runtime shall preserve Canon while reasoning and generation are performed.

---

## Pattern

A Pattern is a recurring relationship, structure, behavior, or characteristic identified within the Reality.

Patterns provide evidence for inference by allowing the Runtime to recognize consistency across multiple observations rather than relying upon isolated examples.

Patterns are discovered through Runtime analysis and become part of the Reality Model.

---

## System

A System is an organized collection of rules, behaviors, relationships, or processes that operate together within a Reality.

Systems describe how portions of the Reality function.

Examples may include technological systems, magical systems, social systems, biological systems, political systems, visual systems, or any recurring structure governing Reality behavior.

The Runtime shall preserve established Systems when generating new information.

---

## Context

Context is the collection of relevant information surrounding the Runtime's current task.

Context is determined by combining:

• the active request

• the established Reality Model

• Canon

• Story

• accepted Runtime knowledge

The Runtime shall use Context to determine relevance, meaning, and appropriate reasoning.

---

## Visual Language

Visual Language is the collection of recurring visual principles that define how a Reality is visually expressed.

It includes, but is not limited to:

• artistic style

• design philosophy

• proportions

• color logic

• rendering methods

• composition

• recurring visual motifs

The Runtime shall use the established Visual Language when generating new visual content to preserve consistency while allowing intelligent expansion.




# Tier 5 — Runtime Processes

These definitions describe the processes performed by the Runtime while executing the Reality Engine specification.

Runtime Processes transform the information contained within a Reality Cartridge into an evolving understanding of the active Reality and use that understanding to fulfill requests.

---

## Analysis

Analysis is the process by which the Runtime examines Reality source material without performing inference.

Analysis identifies and organizes information contained within the Reality Cartridge while preserving its original meaning.

Reality Engine performs Analysis through specialized Analysis Reality Engines.

Each Analysis Reality Engine constructs an internal model representing a specific aspect of the Reality.

Analysis produces structured understanding.

It does not produce conclusions beyond the supplied evidence.
---

## Inference

Inference is the process of reasoning beyond explicit information using the established Reality Model.

Inference allows the Runtime to discover relationships, identify patterns, extend established systems, and satisfy requests while preserving the Reality's internal consistency.

Inference shall follow the Runtime's established Inference Rules.

---

## Synthesis

Synthesis is the process of combining multiple internal Reality models into a unified Reality Model.

Reality Engine performs Synthesis through the Reality Synthesis Reality Engine.

Synthesis resolves relationships between contextual understanding, visual understanding, and any future specialized models while preserving the Reality's established identity and consistency.

The result of Synthesis is a single Reality Model used by the Runtime for reasoning and generation.
---

## Generation

Generation is the process of producing an output based upon the synthesized understanding of the Reality.

Generated content should preserve established Canon, Systems, Context, and Visual Language while satisfying the Reality Architect's request.

Generation is the final expression of the Runtime's reasoning process.

---

## Expansion

Expansion is the process of incorporating newly accepted information into the active Reality Model.

Expansion occurs when the Reality Architect establishes new canonical information or when previously unknown aspects of the Reality become accepted.

Expansion strengthens the Runtime's understanding without replacing established Canon unless explicitly instructed.

---

## Session

A Session is the continuous period during which a Runtime interacts with an active Reality Cartridge.

Throughout a Session, the Runtime maintains its Reality Model, preserves accepted Runtime knowledge, and applies newly accepted expansions until the Session concludes.


## NOT INITIALIZED

NOT INITIALIZED is the initial state of a Reality Cartridge before its initial initialization has been completed.

---

## INITIALIZING

INITIALIZING is the state in which the Reality Cartridge is undergoing its initial initialization and the Runtime is constructing the Reality Model.

---

## ACTIVE REALITY

ACTIVE REALITY is the state entered after the initial initialization has successfully completed and the Reality Model has been constructed.

In this state, the Runtime is ready for interaction within the rules of the constructed Reality.

## LOADED REALITY

The state where the Runtime has completed cartridge initialization and constructed the Reality Model.


# START REALITY

## Definition

START REALITY is the initialization command used to begin execution of a Reality Cartridge™.

When received, the Runtime shall begin the Reality Cartridge initialization procedure.

The command signals that the uploaded package should be interpreted as a Reality Cartridge™ rather than as a collection of independent files.

START REALITY begins the transition from NOT INITIALIZED to INITIALIZING.

---

# CONFIRM REALITY

## Definition

CONFIRM REALITY is the validation command used after Reality Cartridge™ initialization.

When received, the Runtime shall verify that the Reality Model has been constructed and transition the Runtime into ACTIVE REALITY.

CONFIRM REALITY indicates that the Runtime should begin operating from the constructed Reality Model as the active source of context, canon, visual identity, and generation rules.

CONFIRM REALITY completes the transition from LOADED REALITY to ACTIVE REALITY.


## REFERENCE INCOMPLETE

REFERENCE INCOMPLETE is a Runtime state in which one or more required
Reality references have not been sufficiently analyzed or inspected to
fulfill the current request with Reality fidelity.

While in REFERENCE INCOMPLETE:

• Generation is prohibited.
• Inference requiring the missing reference is prohibited.
• Generic substitution is prohibited.
• The Runtime shall identify the missing reference.
• The Runtime shall complete the appropriate Analysis Reality Engine before
  returning to ACTIVE REALITY.

## VALIDATION FAILED

VALIDATION FAILED is a Runtime state entered when generated content fails
post-generation validation against established Canon, Systems, Context,
Visual Language, or Reality Architect instructions.

Content in VALIDATION FAILED state shall not be presented as
Reality-consistent output.

The Runtime shall revise or regenerate the output before completion.
  

# Tier 6 — Runtime Classification

These definitions describe how the Runtime classifies information while reasoning over an active Reality.

Classification enables the Runtime to determine the origin of information, the amount of reasoning performed, and whether newly generated information has become part of the established Reality.

---

## Inference Depth

Inference Depth is the Runtime's internal measurement of how far it must reason beyond Established Canon to satisfy a request.

The Runtime shall always use the lowest Inference Depth capable of producing a valid result.

Lower Inference Depth indicates stronger support from the established Reality.

Higher Inference Depth indicates greater dependence upon Runtime reasoning.

Inference Depth is an internal Runtime process and should not alter Canon.

---

## Established Canon

Established Canon is information accepted as true within the active Reality.

Established Canon may originate from:

• Story

• Visuals

• Reality Architect instructions

• Previously accepted Reality expansions

Established Canon serves as the primary foundation for all Runtime reasoning.

Unless explicitly modified by the Reality Architect, Established Canon shall be preserved throughout Runtime operation.

---

## System Extension

System Extension is the process of applying established Reality systems, patterns, and relationships to situations that have not been explicitly defined.

System Extension does not create new Reality rules.

Instead, it extends existing Reality logic into new circumstances while preserving established consistency.

Whenever possible, the Runtime should prefer System Extension over Creative Expansion.

---

## Creative Expansion

Creative Expansion is the process of constructing new information when Established Canon and System Extension cannot fully satisfy a request.

Creative Expansion shall preserve the Reality's established identity, systems, context, and visual language.

Creative Expansion remains proposed Reality knowledge until accepted by the Reality Architect.

Once accepted, Creative Expansion becomes Established Canon.
