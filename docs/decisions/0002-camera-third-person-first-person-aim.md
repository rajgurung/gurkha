# 0002: Third-person camera, first person when aiming

Status: Accepted · Date: 12 October 2026 · Approved by: Raj

## Summary

Until Dawn plays in third person by default, with the camera behind Bir's shoulder. Holding aim switches to first person through the rifle sights. Firing and working the bolt happen in either view. Reloading, first aid, ammo, the kukri and talking all happen in third person. The main cost is a full set of player animations that must look right from behind.

## Options considered

| Option | For | Against |
|---|---|---|
| A. First person throughout (current spec) | Closest to the template. Fewest player animations: arms only. Strongest "read the dark" feeling. No camera collision in the trench. | Bir is never seen, so less sense of a person among comrades. Matches the concept board less well. Raj played it and prefers B. |
| B. Third person, first person when aiming (Raj's choice) | You see Bir, his kit and his comrades. Matches concept Scene 2. Aiming keeps the precise, slow sight picture the rifle needs. Easier to read where the 3 posts are. | Two camera modes to tune. Full-body animations plus a few first-person ones. The camera can see over cover that Bir cannot. Camera collision in a narrow trench. |
| C. Over-the-shoulder throughout | One camera mode. No view switch. | Aiming a bolt-action rifle over the shoulder feels loose and arcade-like. A reticle becomes almost necessary, which breaks the empty HUD. |

## Decision

Option B, with the rules below. As designer I support it, on condition that rules 2 and 3 hold in playtest.

### 1. The two views

| | Third person (default) | First person (aiming) |
|---|---|---|
| Sees | Bir from behind, right shoulder, camera pivot at head height | Down the rifle sights |
| Controls | Move, crouch, sprint, interact, fire from the hip, bolt, reload | Slow walk or parapet only, fire, bolt. No sprint. |
| Look speed | Hip sensitivity | Aim sensitivity (lower) |

- **Switch:** hold aim by default. Toggle aim is an accessibility setting.
- **Transition:** a short blend into the sights and out again (tuning values below). No cut.
- **Shoulder swap:** one key moves the camera to the other shoulder. Manual only in the milestone. Aiming always uses the right eye and sights.
- **Aim drops automatically** for sprint, reload, every interaction and taking a hit while badly wounded. If aim is still held when the action ends, Bir goes back into the sights.

### 2. Trench and parapet

- **No peeking advantage.** The camera pivot sits at Bir's head height with no extra height. Crouched behind a parapet, the camera may not rise more than a small clearance above the parapet top. The player must stand or aim to see the lane. This keeps the risk of looking.
- **Camera collision.** The arm shortens in the trench and at the parapet. If the camera gets very close to Bir, his mesh fades out so it never fills the screen.
- **Parapet.** Interact snaps Bir into the firing position as before. The camera tightens and sits low over the shoulder. Aim gives the steady first-person sight picture.
- **Night readability.** Bir sits in the lower left of the frame. He is lit by the same moonlight as the scene, with no rim light. The lane in front stays the brightest part of the view.
- **Three posts close together.** Third person helps the player see which post they are in and where Dhan and Kesar are. Callouts and sound still carry the threat direction.

### 3. Rifle in both views

| Action | Third person | First person (aiming) |
|---|---|---|
| Fire | Allowed, from the hip, with wide spread. Wastes rounds, which is the cost. | Accurate, with the sway rules from the spec. |
| Bolt cycle | Full-body animation. | Stays in the sights, with a small dip of the view. Needs a historian check (see Unverified). |
| Charger reload | Full-body animation. Partial reload as specified. | Not allowed. Reload drops aim to third person. |

Shots trace from the muzzle, not from the camera, so the hip shot goes where the rifle points.

### 4. Which view each action uses

All in third person: dress own wound, first aid on Kesar (camera moves in closer and lower for the 3 steps), give ammo to Dhan, take ammo at the cache, check pouches, kukri brush clearing, talking with Dhan and Kesar, carrying Kesar at dawn, the dawn walk. Seeing Bir do these things supports "hold together" better than first-person hands would.

### 5. HUD and crosshair

- No crosshair in either view by default. The empty HUD rule stands.
- The optional aim dot (accessibility) shows in both views. In third person it marks where the muzzle trace hits.
- No new HUD elements. Interaction targets are read from Bir's position and the scene.

### 6. New tuning values (data, per decision 0001)

All are starting values for tuning, not tested.

| Value | Start |
|---|---|
| Camera arm length: open / trench / parapet | 2.0 m / 1.4 m / 1.1 m |
| Shoulder offset, sideways | 0.45 m |
| Camera clearance above parapet top when crouched | 0.10 m |
| Field of view: third person / aiming | 72° / 65° |
| Aim in / aim out blend | 0.20 s / 0.15 s |
| Shoulder swap blend | 0.25 s |
| Look sensitivity: hip / aim multiplier | 1.0 / 0.6 |
| Hip-fire spread | 4° |
| Bolt cycle view dip in aim | 2° |
| Mesh fade start distance | 0.6 m |
| Camera collision probe radius | 0.15 m |
| First aid close camera arm length | 0.9 m |
| Default aim mode | Hold |

## Animation list (main cost)

Third person, full body, must look right from behind and at night:

1. Locomotion with rifle: idle, walk, crouch walk, sprint, turn in place. Trench and mud variants can use play rate.
2. Wounded and badly wounded locomotion and idle.
3. Parapet: enter, idle, exit.
4. Hip fire, bolt cycle and charger reload, standing, crouched and at the parapet. Partial reload. Wounded speeds by play rate, not new clips.
5. Hit reactions, 3 directions.
6. Dress own wound. First aid on Kesar: kneel and open, press, tie.
7. Give ammo, take ammo at the cache, check pouches.
8. Kukri: draw, cut brush loop, sheathe.
9. Carry Kesar at dawn. Sit and talk idles.

First person: aim idle with sight picture, fire, bolt cycle in aim.

Offset: Kesar and Dhan need most of items 1 to 5 anyway. If they share Bir's skeleton, much of the work is reused. Whether to use a separate first-person arms mesh or a camera on the full-body head is the Unreal engineer's call.

Option B also puts Bir's uniform, webbing, helmet and kukri scabbard on screen all the time. That raises the bar for the player model and its research.

## Changes from review

All four reviewers approved with changes. Each change below is adopted.

### Build (unreal-engineer)

1. **Separate first-person arms and rifle mesh, shown only while aiming.** The template already builds one (`UntilDawnCharacter.cpp`, lines 19 to 35). The full body is visible in third person and hidden from the owner while aiming, using `SetOwnerNoSee`.
2. **One camera, blended in `AUntilDawnCameraManager`.** The view and field of view blend between the spring arm view and the sight view by an aim value. `SetViewTargetWithBlend` cannot blend two cameras on one pawn.
3. **Spring arm per zone.** Copy the boom setup from the Third Person template. Trench and parapet volumes change the arm length. Values live in a data asset.
4. **Parapet clearance is a hard clamp.** Looking down raises the camera on the arm, about 0.55 m at 30 degrees, so the arm alone leaks. While crouched, the camera manager clamps camera height to the parapet top plus 0.10 m, after the collision probe. Each parapet actor carries its top height. A functional test sweeps the full pitch range.
5. **New muzzle trace.** The Shooter template aims from the camera, which breaks rule 3. Hip fire traces from the world rifle's muzzle socket along the barrel, with spread. Aim traces along the sight line. Never trace from first-person mesh sockets.
6. **First playable** uses Manny, `ABP_TP_Rifle`, `ABP_FP_Weapon` and the template rifle clips. The generic reload stands in for the bolt and the charger.

### Art (art-director)

7. **Exposure is clamped,** or metered from the centre of the frame, so Bir's dark body cannot brighten the night.
8. **Bir covers at most about 25% of the frame** in the trench. Shoulder swap stays easy to reach.
9. **Moonlight only on Bir.** Wet cloth, helmet and rifle metal catch light through roughness, never through extra lights. Bir stays darker than the lane on average.
10. **Shadows.** Full player shadow on Medium and above. A capsule or blob shadow on Low. Muzzle flash light is short, with no shadow on Low.
11. **Detail priority from behind:** helmet and net, webbing straps and pouches, rear belt, kukri scabbard, rifle. The scabbard must read in silhouette and not hide behind the pack.

### Assets (technical-artist)

12. **Bir, Dhan and Kesar share the UE5 Mannequin skeleton,** so locomotion, wounded and hit animations are made once.
13. **Carrying Kesar at dawn becomes a fade or a cutscene** for this milestone. Two-person carry and first aid are the most expensive animations.
14. **Budget:** Bir about 35k triangles at LOD0 including kit, one 2048 texture set for the uniform, 1024 sets for kit, a 2048 set for the first-person rifle. Comrades about 20k with LODs. The close-camera fade uses dithered masked opacity, not translucency.
15. **Tripo characters need 1 to 2 days of cleanup each** before they deform well on the Mannequin skeleton.

### History (historian)

16. **Bolt in aim stays.** Keep the butt in the shoulder in both views. Sources say the Lee-Enfield could be worked without leaving the sights, with one dissenting forum post. Label: single source, contested. Do not animate a thumb-and-forefinger grip.
17. **Hip fire is a game cost, not a period drill.** No in-game text presents it as technique.
18. **Kit:** kukri on the belt at the back (verified). 1937 pattern webbing, often two basic pouches and a belt (verified).
19. **Headgear stays a swappable asset** until helmet versus slouch hat at night is confirmed.
20. **No regimental badge, battalion number or shoulder title** on Bir. Never 8th Gurkha Rifles, the real regiment of Lachhiman Gurung.

### Resolved disagreements

- **Field of view:** the proposal had 80°, art-director asked for 70 to 75°. The start value is now 72°, still a tuning value.
- **Arms mesh or full-body camera:** technical-artist preferred the full body to avoid a second mesh. unreal-engineer chose the arms mesh for clean sights and no clipping. The engineer's choice stands, because the proposal gave it that call.
- **Triangle budget:** technical-artist proposed under 30k, art-director 35k including kit. 35k including kit is adopted.

## Tradeoffs accepted

- Two rigs and two animation blueprints, for the arms and the body.
- Camera blend logic is our own C++ instead of engine defaults. Reviewable, but more to own.
- Every parapet must carry a top height. A test catches misses.
- More animation work than option A, before the first playable.
- Two camera modes to tune instead of one.
- Hip fire exists, so a careless player can waste ammunition faster. This fits "every round counts".
- Third person is a little less claustrophobic in the dark than first person.

## Dissent

None. The three disagreements above were settled in merge.

## Revisit when

- Playtesters spot enemies from third person that they could not see by aiming. Then tighten rule 2 or move to option A.
- Players report discomfort from the view switch.
- The animation list blocks the first playable for more than 2 weeks. Then fall back to option A for the milestone.

## Spec sections that change if accepted

- `story-and-technical-spec.md`: Immersion and presentation (line 66), Shared art requirements (line 107), First playable milestone item 2 (line 166), Decisions still open (line 177).
- `until-dawn-gameplay-spec.md`: Movement (parapet camera), Rifle (both views, hip fire, reload drops aim), Ammunition and Player wounds (view for give and dress), First aid on comrades (close camera), Preparation (kukri in third person), HUD and accessibility (aim toggle, shoulder swap, sensitivity, dot in both views), Milestone performance budget (player mesh always on screen), Open questions (remove line 248).

## Unverified

- Lee-Enfield bolt in the shoulder: single source, contested.
- Headgear at night, shade of jungle green, bandolier use, Kesar's rank marks. Which rifle: No. 1 Mk III or No. 4.
- Whether toggling `SetOwnerNoSee` on aim is cheap at runtime.
- Whether the moon is a stationary or movable light. This decides the player shadow.
- Whether Mannequin rifle clips read well from behind at night.
- UE 5.8 exposure behaviour with a large dark foreground.
- Whether Tripo's auto-rig outputs Mannequin bone names.
- Fab packs and licences for WW2 bolt-action animation.
- All triangle, texture, FOV and coverage numbers. Nothing is profiled or playtested.
- Trench width in the blockout. The arm lengths assume about 1 m.
- Whether the parapet clearance rule stops peeking in practice.
- Cost of the always-visible player mesh, its shadow and textures on a base M1 with 8 GB.
- Where suitable bolt-action animations come from, and their licence.

## Who took part

- Proposal: game-designer
- Reviews: unreal-engineer, art-director, technical-artist, historian
- Merged by: producer (main session)
- Human check later: the Gurkha Museum, Winchester, on the final player model
