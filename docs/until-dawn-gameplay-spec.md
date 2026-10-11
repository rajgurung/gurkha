# Until Dawn: Gameplay Specification

First playable milestone for GURKHA: The Long Way Home. Draft, 11 October 2026.

Companion to [story-and-technical-spec.md](story-and-technical-spec.md). All numbers here are starting values for tuning, not tested results.

## Goal of the prototype

Prove that one night of holding a small position feels tense, readable and personal, on a base M1 MacBook with 8 GB. If this mission is not good at 10 to 15 minutes, a longer campaign will not fix it.

## Design pillars

- **Hold together.** The threat is losing a post or a comrade, not a low score. Bir's job is to keep the section intact until relief.
- **Every round counts.** Ammunition is limited and reloading takes effort. The player should feel the cost of wasted shots.
- **Read the dark.** Enemies are mostly heard and glimpsed. Sound, muzzle flashes and flares carry the information a HUD would normally show.
- **Earned quiet.** Fighting comes in short phases. The pauses between them are part of the design, not loading gaps.

## Setting and layout

A small forward position on a ridge spur, overlooking one jungle approach.

- **Three posts** joined by a shallow trench: Left, Centre and Right. Each is a weapon pit with a parapet.
- **Exposed gap.** The trench between Centre and Right is shallow for about 8 metres. Crossing it under fire is a real risk. The player can crouch-run it or take the longer covered route behind the ridge.
- **Ammunition cache** in a dugout behind Centre.
- **Telephone line** running back down the ridge to platoon HQ. It is cut during the first attack.
- **The hut.** A bamboo-and-timber hut sits forward of the Left post, about 40 metres out. Attackers use it as cover. It collapses during Phase 2 (see Destruction).
- **The approach.** Three lanes come up through the jungle: one towards each post. Each lane has 3 to 4 cover points for enemies (fallen trunks, rocks, the hut).

Night landmarks the player learns at dusk: a dead tree on the left lane, a white boulder in the centre, the hut. Comrades use these names in callouts ("dead tree", "boulder", "hut") so the player can find threats in the dark.

## Characters in the mission

- **Bir (player).** Rifleman. Moves between posts.
- **Havildar Kesar.** Section leader, holds Centre. Gives orders in Phase 1. Wounded in Phase 2, which moves responsibility to Bir.
- **Dhan.** Holds Right. Talks the most, calls for ammunition, keeps the mood human.
- **Left post** is Bir's own post until Phase 2, when he starts moving between all three.

The milestone has two comrades only. A full section can come later.

## Mission flow

Target length is about 14 minutes for a first playthrough.

| # | Phase | Length | What the player does |
|---|---|---|---|
| 0 | Dusk arrival | 1 min | Walk up the ridge behind Kesar. Learn movement. Short exchange with Dhan. |
| 1 | Preparation | 3 to 4 min | Choose and complete preparation tasks before dark. |
| 2 | First watch | 2 min | Share the watch with Dhan. Listen. One false alarm. |
| 3 | The probe | 2 min | First contact on the Left lane. Telephone line goes dead. |
| 4 | Interval | 1 min | Kesar sends Bir to fetch ammunition and check Right. |
| 5 | The main attack | 3 to 4 min | Attacks on two lanes at once. Hut collapses. Kesar is wounded. |
| 6 | Interval | 1 min | Dress Kesar's wound. Share out the remaining ammunition. |
| 7 | Before first light | 2 min | Last push on the weakest post. Hold it. |
| 8 | Dawn and relief | 2 min | Relief arrives. Walk the position in daylight. Help with the wounded. |

Checkpoints sit at the start of phases 2, 5 and 7.

### 1. Preparation

The light fades on a visible timer: the sun goes down behind the far ridge. There is time for 3 of 5 tasks. Each choice changes the night that follows.

| Task | Effect later |
|---|---|
| Clear the left fire lane with the kukri | Better sightline on the left lane. Enemies there are visible earlier. |
| Clear the right fire lane with the kukri | Same for the right lane. |
| Build up the Centre parapet | Kesar is wounded later and less badly. Phase 6 first aid is quicker. |
| Carry extra ammunition to Right | Dhan calls for ammunition once less in Phase 5. |
| Walk the telephone line and learn the route | In Phase 4, a marked shortcut to the cache appears. |

This is where the kukri appears in the milestone. It is a working tool for cutting brush, as in the village chapter. It is not a combat weapon in this prototype.

No task is wrong. The aim is to make the player feel that their dusk choices mattered when it gets dark.

### 2. First watch

No combat. Dhan talks quietly in Nepali (subtitled) about home and the cold. Jungle sounds fill the silence. A noise on the right lane turns out to be an animal. This teaches the player to listen and makes the real attack land harder.

### 3. The probe

A small group tests the Left lane. Kesar orders "wait for it" and then "fire". Kesar tries the telephone. It is dead.

Teaches: aiming at muzzle flashes, bolt-action rhythm, reloading with chargers.

### 5. The main attack

Attacks come up two lanes at once. The player cannot cover both from one post. They must move between posts, decide where the danger is greatest and resupply Dhan.

Scripted beats, in order:

1. Enemy fire from behind the hut pins down the Left post.
2. A mortar round hits the hut. It collapses and the enemies behind it lose their cover.
3. Kesar is hit. He calls out but keeps the Centre post for 30 seconds before he can no longer fire.
4. Bir must hold Centre and Left himself while Dhan holds Right.

### 7. Before first light

The enemy attacks whichever post was under most pressure at the end of Phase 5. The sky starts to lighten in the last 30 seconds. The attack breaks off.

### 8. Dawn and relief

Shouts in Nepali from down the ridge. Relief troops arrive. The player walks the position in grey light: the collapsed hut, the spent cases, the damage to the parapet. Bir helps carry Kesar to the stretcher. Dhan sits down on the edge of the trench.

There is no score screen. An end card shows the date and the line "Inspired by the soldiers of the Gurkha regiments", then returns to the menu.

## Core mechanics

### Movement

- Walk, crouch and short sprint. No prone in the milestone.
- Mud and trench water slow movement slightly. Sprint drains faster in the trench.
- The parapet at each post has a fixed firing position. Pressing interact snaps into it, which steadies aim.

### Rifle

The milestone has one bolt-action rifle with a 10-round magazine. The exact model (Lee-Enfield No. 1 Mk III or No. 4) depends on research into the chosen unit. Unverified.

- Work the bolt after every shot. Firing again too quickly does nothing.
- Reload with 5-round chargers. A partial reload is allowed: the player can push in one charger when the magazine is half empty.
- Aiming down the sights is steady at a parapet and sways more when standing in the open.
- No crosshair by default. An optional dot is in accessibility settings.

### Ammunition

| Item | Starting value |
|---|---|
| Rounds carried | 10 in magazine plus 8 chargers (50 total) |
| Cache | 20 chargers (100 rounds), shared by the whole section |
| Dhan's calls for ammo in Phase 5 | 2 (1 if Right was resupplied during prep) |

Giving a comrade ammunition is a held interaction of about 1.5 seconds, beside them. The aim is that a careful player finishes Phase 7 with fewer than 10 rounds left. A wasteful player will run dry and have to go back to the cache under fire.

### Player wounds

No health regeneration. Bir has three states:

| State | Effect |
|---|---|
| Unhurt | Normal |
| Wounded | Slower bolt and reload, more aim sway, muffled sound for a few seconds after each hit |
| Badly wounded | Slow movement, heavy sway. Another hit ends the attempt. |

The player can dress their own wound during a quiet moment (hold for 4 seconds, cannot fire). It brings them back one state, with a limit of 2 dressings. Wounds from the night stay visible in the dawn scene.

### First aid on comrades

Dressing Kesar's wound in Phase 6 is a short hands-on sequence. Kneel, open the dressing, press, tie. It uses three button presses in a slow rhythm, not a quick-time test. It should feel careful, not like a minigame.

### Comrades

Comrades follow scripts with a few states: firing, reloading, calling for ammo, calling a target, wounded. They do not die at random. In the milestone:

- Kesar is always wounded in Phase 5. How badly depends on the parapet task.
- Dhan can be wounded if the Right post runs out of ammunition for more than 20 seconds. He survives in the milestone either way. Whether a comrade can die is a campaign decision for later.

Callouts use the landmark names and come from the comrade's direction. This is the main way the player learns where to look.

### Post pressure

Each post has a hidden pressure value. It rises while enemies are close to that lane and no one is firing from the post. It falls when the post is manned and firing. The player learns pressure from sound and from comrades shouting, not from a meter.

If pressure stays at maximum for 10 seconds, enemies reach the trench and the attempt ends.

### Failure and retry

The attempt fails if Bir is hit while badly wounded or if a post is overrun. The screen fades and restarts at the last checkpoint. Preparation choices are kept. No "mission failed" banner: a short line of Kesar's dialogue plays over the fade instead.

## Enemies

- Small groups of 2 to 4 that move between cover points on a lane.
- They fire, go to ground when fired on and advance when fire stops. That is enough to make suppression matter.
- At most 8 active enemies at one time. This is both a design choice and a performance limit for the base M1.
- Enemy soldiers are shown as soldiers, without caricature in faces, voices or behaviour. Their equipment and language need period research.
- No enemy grenades in the milestone. This keeps the encounter clearly separate from the details of Lachhiman Gurung's real action.

## Darkness and readability

- Low moonlight with a cool blue ambient level. Silhouettes against the sky are readable from the parapet.
- Muzzle flashes briefly light the shooter's position.
- Enemy flares rise every 30 to 60 seconds in combat phases and light the approach for a few seconds. These are the best moments to fire.
- A brightness calibration screen runs on first launch. Gameplay must be readable at the default setting on a MacBook display.

Night is also helpful for performance. Most of the jungle can stay dark and simple.

## Destruction

One Chaos event in the milestone: the hut collapse in Phase 5.

- The collapse is triggered by a script, not by player fire, so it is the same every time.
- Prepare the hut as an intact mesh and a pre-fractured version.
- The gameplay result (enemy cover removed) is the same on every graphics preset. Only dust and small debris scale with settings.
- The collapse sound must work on its own, since the player may not be looking at the hut.

## HUD and accessibility

Default HUD is almost empty.

- Ammunition is shown only while reloading, or when the player presses a "check pouches" key.
- A subtle red edge shows the direction of a hit.
- An objective line appears for a few seconds when the phase changes and can be turned off.

Accessibility settings for the milestone:

- Subtitles with speaker names and size options.
- Separate volume sliders for dialogue, effects and ambience.
- Optional aim dot and optional enemy outline in flare light.
- Two difficulty levels. Story gives more ammunition, more dressings and a slower pressure rise. Standard uses the values above.
- Rebindable keys.

## Audio priorities

1. Comrade callouts with direction.
2. Enemy movement in the foliage: snapping twigs, rustling, low voices.
3. Rifle, bolt and charger sounds. These carry the weight of each shot.
4. Rain, insects and wind as the base layer.

Dialogue among the Gurkhas is in Nepali with English subtitles. A Nepali speaker should write or review all lines.

## Milestone performance budget

These are planning limits for a base M1 MacBook with 8 GB, to be checked in a packaged build.

| Item | Limit |
|---|---|
| Active enemies | 8 |
| Comrades | 2 |
| Chaos destruction events | 1 |
| Dynamic lights at once | Moon, plus up to 2 flares and short muzzle flashes |
| Approach area | About 60 by 80 metres of playable jungle; the rest is a backdrop |

Profile the main attack at the moment the hut collapses. That is the heaviest point of the mission.

## Prototype success test

After 5 or more people outside the project have played it, check:

- Could they say which post was in danger without a HUD?
- Did they run low on ammunition at least once?
- Did they mention Kesar or Dhan by name afterwards?
- Did the dawn scene land as a relief and not a letdown?
- Did it hold 30 fps on a base M1 with 8 GB during the hut collapse?

## Open questions

- Rifle model and exact equipment, from research into the chosen unit.
- How enemy soldiers are depicted, and which language and equipment they use.
- Whether comrades can die in the full campaign.
- Who writes and reviews the Nepali dialogue.
- First-person is assumed here. A third-person version would need the same layout but different animation work.
