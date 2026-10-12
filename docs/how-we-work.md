# How We Work

Status: Draft for review · Owner: Raj · Last updated: 12 October 2026

A small team of Claude Code agents plans, builds and reviews the game. Agents agree on a plan before anything is built, and Raj approves every plan. Every agreed decision is written down in `docs/decisions/`, with its tradeoffs.

## Who decides

- **Raj** is the final approver. No plan is built without his yes.
- **The main Claude Code session acts as producer.** It hands work to agents, collects their feedback and merges it into one proposal. Subagents cannot talk to each other directly, so the producer carries plans between them.
- **Agents advise and build.** An agent can block a plan in its own area, for example the historian on historical accuracy. Raj can still overrule a block, and the decision record says so.

## The team

Agents live in `.claude/agents/` in this repo. Each has one job. All eight exist now; the rollout below sets the order they start doing real work.

### Core team: planning and review

| Agent | File | Owns | Active from |
|---|---|---|---|
| Game designer | `game-designer` | Mechanics, tuning, mission specs. Answers "is this fun?" | Phase 1 |
| Historian and cultural researcher | `historian` | Gurkha history, the Burma campaign, period kit, Nepali culture and language. Cites sources. Marks anything unverified. | Phase 1 |
| Documentation editor | `docs-editor` | Doc structure, style, decision records. Checks every change for doc impact. | Phase 1 |
| Narrative designer | `narrative-designer` | Story, characters, dialogue, tone. Keeps the fiction separate from real people. | Phase 3 |
| Art director | `art-director` | Visual direction, asset specs. Reviews renders against the concept board. | Phase 3 |

### Build team: implementation

| Agent | File | Owns | Tools | Active from |
|---|---|---|---|---|
| Unreal engineer | `unreal-engineer` | Gameplay code, levels, packaged builds | Unreal command line with Python editor scripts, C++ | Phase 1 |
| Technical artist | `technical-artist` | Asset pipeline: generate, clean up, LODs, collision, import | Blender headless with Python, Tripo API | Phase 2 |
| Performance and QA | `perf-qa` | Profiling on a base M1 with 8 GB, test plans, playtest checklists | Packaged builds, Unreal automation tests | Phase 2 |

The global `staff-reviewer` agent reviews code and diffs. There is no product manager agent. The producer and Raj cover scope and priorities.

### Rollout

1. **Phase 1:** the four Phase 1 agents test the process on one real decision: [0001](decisions/0001-gameplay-code-in-cpp.md).
2. **Phase 2:** the technical artist and performance agents start once the Unreal project exists.
3. **Phase 3:** the narrative designer and art director start when story and art work begins.

Any agent can still be asked to review earlier if a decision touches its area.

## How a decision is made

Two levels, so small changes stay quick.

### Big decisions: the full loop

Use this for anything that changes the design, the tech approach, the budget or the story.

1. **Propose.** The agent closest to the problem drafts a plan.
2. **Review.** Only the agents the decision affects review it, in parallel. Each reviews from its own area.
3. **Resolve.** The producer merges the feedback into one proposal. Disagreements are written as tradeoffs, not hidden. At most 2 review rounds.
4. **Approve.** Raj approves, changes or rejects it.
5. **Record.** The documentation editor writes a decision record in `docs/decisions/`.
6. **Build.** An implementer builds it.
7. **Review.** A reviewer checks the result. Docs are updated in the same change.

### Review format

Every agent review returns the same four parts, so the producer can merge them quickly.

```
Verdict: Approve | Approve with changes | Block
Findings: numbered, concrete, each naming the file or section
Tradeoffs: what the plan gives up, from this agent's area
Unverified: claims in the plan, or in this review, that no one has checked
```

A Block must say exactly what would turn it into an Approve.

### Watching the loop

The agent-board mod shows the loop live in Claude Code. A band above the prompt shows the decision, a stage bar, the agents running with their elapsed time, and the next step. `/board` opens a pane with the full table.

The producer keeps `.claude/loop.json` up to date at each stage: decision, title, stage number, stage names, the next step, and a note per agent. The mod measures agent status and time itself. The file is local and ignored by git.

The mod currently lives in this Claude Code session's mods folder, not in the repo.

### Small changes: the short path

Use this for bug fixes, tuning values and wording. One implementer, one reviewer, and a doc check. No decision record unless the change turns out to be bigger than expected.

## Decision records

One file per decision, numbered in order, for example `docs/decisions/0001-gameplay-code-in-cpp.md`. The [index](decisions/README.md) lists them all.

```
# 0001: Title in plain words

Status: Proposed | Accepted | Replaced by 00NN · Date · Approved by: Raj

## Summary
2 to 3 lines. A reader can stop here.

## Options considered
| Option | For | Against |

## Decision
What we chose and why.

## Tradeoffs accepted
What we gave up.

## Dissent
Which agent disagreed, and why.

## Revisit when
The condition that would reopen this decision.
```

Rules:

- An accepted record is never edited. A new record replaces it, and the old one is marked "Replaced by".
- The summary must work on its own.

## Where things live

```
README.md            Start here: what this is, status, where things live
docs/
  how-we-work.md     This page
  status.md          Current milestone: done, doing, blocked (planned)
  decisions/         Decision records, indexed in decisions/README.md
  design/            Story and gameplay specs (planned; specs sit in docs/ for now)
  art/               Art direction, asset list, concept images
  tech/              Engine setup, pipeline, performance budgets (planned)
  research/          Historical sources, each fact marked verified or unverified (planned)
  glossary.md        Nepali, military and Unreal terms, one line each (planned)
```

Each kind of information has one home:

| What | Where |
|---|---|
| Why we chose something | `docs/decisions/` |
| What the game is | `docs/design/` and the other docs folders |
| Tasks and progress | Beads (`bd`), not yet set up in this repo |
| What happened in each Claude Code session | StaffOS |

## StaffOS

Every Claude Code session in this repo is recorded in StaffOS (project "Gurkha") through Claude Code hooks. StaffOS keeps the evidence of each session: prompts, files touched and commands run. The repo stays the source of truth for decisions and docs.

The hooks and token are local only. `.staffos.yml` and `.claude/settings.json` are in `.gitignore`.

## Documentation rules

The documentation editor checks these on every change.

- **Summary first.** Every page opens with 2 to 3 lines that answer "what is this?", plus status, owner and last-updated date.
- **One page, one purpose.** Link to other pages instead of copying their text.
- **Plain English.** Short sentences, one idea each. Explain a technical term once, then use it freely. No padding.
- **Scannable.** Short headers, tables and lists. A page should be readable in under 3 minutes.
- **Honest.** Mark anything unverified as unverified. Cite sources for historical claims.
- **Docs change with the work.** A change that affects documented behaviour updates the doc in the same commit.

## Hard rules for agents

- **No paid Tripo calls without Raj's approval.** The default spend is zero. This should be enforced with a hook, not only written here.
- **No secrets in git.** API keys go in `.env`, which is ignored.
- **Git commits are authored by Raj.** No Claude co-author lines.
- **Large files go through Git LFS.** See `.gitattributes`.
- **Humans check what agents cannot.** A native speaker reviews Nepali dialogue. Real players do playtests.

## Known limits

- **Blueprints are binary.** Agents cannot read or edit Blueprint graphs as text. [Decision 0001](decisions/0001-gameplay-code-in-cpp.md) keeps gameplay logic out of Blueprints for this reason.
- **Live Unreal editor control** needs a community MCP server. Its quality for Unreal 5.8 is unverified.
- **Agent reviews cost tokens.** Use the full loop only for big decisions.

## Open questions

- **Decision 0001 is resolved.** Gameplay logic is C++ and tuning is data. See [0001](decisions/0001-gameplay-code-in-cpp.md).
- **Set up beads in this repo** for task tracking, or use something else?
- **Extract a reusable game-dev plugin** (agents, loop, board, guard hooks, docs scaffold) once the process has worked on a few Gurkha decisions and been tried on a second game.
