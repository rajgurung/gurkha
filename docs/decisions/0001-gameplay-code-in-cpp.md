# 0001: Gameplay logic in C++, tuning as data

Status: Accepted · Date: 12 October 2026 · Approved by: Raj

## Summary

Game rules are written in C++. Everything a designer or performance tuner changes is data, edited in the Unreal editor without a compile. Blueprints only wire up meshes, sounds and animations.

## Options considered

| Option | For | Against |
|---|---|---|
| A. Blueprint-first (current spec) | Fast visual iteration. No compile step. | Agents cannot read, diff or review Blueprint graphs. Binary merge conflicts. Logic hidden from review. |
| B. C++ logic, thin Blueprints | All logic is reviewable text. Normal diffs. Automation tests. Engine ships a C++ first-person template. | Every logic change needs a compile. No Live Coding on Mac. |
| C. B plus data-driven tuning (chosen) | Everything in B. Raj tunes values with no compile. | Every tunable must be exposed as data. Some assets stay binary. |

## Decision

Option C, with these rules:

1. **Mission beats are data.** Phase order, triggers, delays, actions and dialogue line IDs live in a data table that C++ runs. Raj reorders beats without compiling. The Phase 7 rule ("attack the post under most pressure") may need one C++ condition type.
2. **Tuning values are data:**
   - Ammo: 50 carried, 100 in cache, Dhan's ammo calls, give-ammo hold time.
   - Wounds: per-state bolt, reload, sway and muffle multipliers; dressing time and limit.
   - Pressure: weights, rise and fall rates, distance threshold, overrun window.
   - Timers: Dhan's ammo-out, Kesar's hold, flare interval, phase lengths, preparation timer.
   - Movement: mud and trench slow, sprint drain.
   - Enemies: group size, active cap.
   - Difficulty: one profile per level. Story overrides Standard. No difficulty branches in code.
   - Preparation tasks: each task mapped to its modifiers.
   - Callouts: a table of event, landmark, line and cooldown.
   - Graphics presets: dust and debris counts, flare count, enemy cap.
3. **The pressure rule's shape is code;** its weights are data.
4. **C++ reads tuning values when it uses them,** not once at start, so edits during Play apply if the engine allows it.
5. **Allowed binary assets:** Animation Blueprints, UI layouts, StateTree assets (their tasks and conditions in C++), the Chaos destruction asset, levels, Level Sequences, curve assets, sound attenuation and MetaSounds, and input assets. Blueprint subclasses hold asset references only, with no graph logic. Any exception is added to this list.
6. **Developer cheats and a debug overlay from day one:** jump to a phase or checkpoint, set pressure per post, refill ammo, god mode, show hidden pressure. One command jumps to Phase 5 and fires the hut collapse, so the heaviest moment is profiled the same way every time.
7. **Tests first,** as plain C++ automation tests: charger reload and ammo counts, wound states and first aid, post overrun after 10 seconds at maximum, checkpoint save and restore keeping preparation choices, and the 8-enemy cap.
8. **Checks for binary assets,** added when each asset type first exists:
   - A functional test that fires the hut collapse and checks enemy cover is gone, on Low and Ultra.
   - A functional test that drives one enemy group through suppress, go to ground and advance.
   - A test that the HUD is empty by default.
   - A screenshot comparison for animation.
   - A Python script that dumps data values and any Blueprint graph nodes as text, so thin Blueprints stay thin.
9. **Profiling results are CSV files in git,** so frame-time numbers can be compared as text.

Items 1 to 7 and 9 are part of the first build. Item 8 grows with the assets.

### Planned layout

```
game/Source/Gurkha/          C++ by system: Weapons, Health, Interaction, AI, Squad, Mission, Destruction
game/Source/Gurkha/Tests/    Automation tests
game/Content/Gurkha/Data/    Data assets and data tables (CSV sources in git)
game/Content/Gurkha/Blueprints/  Thin subclasses only
game/Scripts/                Python editor scripts
```

## Tradeoffs accepted

- **No Live Coding on Mac.** A logic change needs a rebuild and an editor restart. Live Coding is Windows-only in the installed engine (`TargetRules.cs`, line 1589).
- **Raj cannot sketch new mechanics in Blueprint.** New behaviour waits on C++ and a compile.
- **Setup comes first.** The beat table, cheats and tests are built before the first playable.
- **Some assets stay outside text review.** Levels, the destruction asset and animations are checked by tests and measurement only.

## Dissent

None. The game designer and performance reviewer both approved with changes, and all their changes are adopted above. One argument was dropped: "Blueprint runs slower" is not a reason for this choice, because the GPU and memory are the real limits on the M1.

## Revisit when

- A small code change takes more than about 2 minutes on Raj's Mac, measured from edit to back in the editor.
- Raj finds he often needs to prototype mechanics himself.

## Unverified

- Compile and editor restart times on the M1 Pro.
- Whether data asset and data table edits apply during Play in 5.8.3.
- Whether hot reload is reliable on Mac.
- Whether Xcode 26.1.1 builds a 5.8.3 C++ project cleanly.
- Whether the engine's test frameworks run in packaged Mac builds.
- Nothing has been measured on a base M1 with 8 GB.

## Who took part

- Proposal: unreal-engineer
- Reviews: game-designer, perf-qa
- Merged by: producer (main session)

## Notes

12 October 2026: the project was created at `game/UntilDawn/` (`UntilDawn.uproject`) with module `UntilDawn`, not `Gurkha`. Unreal put the project in a subfolder. Paths in Planned layout map to:

| Planned | Real |
|---|---|
| `game/Source/Gurkha/` | `game/UntilDawn/Source/UntilDawn/`, one subfolder per system |
| `game/Source/Gurkha/Tests/` | `game/UntilDawn/Source/UntilDawn/Tests/` |
| `game/Content/Gurkha/Data/` | `game/UntilDawn/Content/Gurkha/Data/` |
| `game/Content/Gurkha/Blueprints/` | `game/UntilDawn/Content/Gurkha/Blueprints/` |
| `game/Scripts/` | `game/UntilDawn/Scripts/` |

12 October 2026: verified that Xcode 26.1.1 builds a 5.8.3 C++ project. The first editor build succeeded in 381 seconds.
