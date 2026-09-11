# Flipper naming: debugger evidence {#itflipper_naming}


These flipper names were determined by Claude (an AI), not recovered from an
original author. Each was inferred from a concrete observation in a running,
retail-matching build; the experiments below are that supporting evidence,
reproduced from the analysis (function references updated to their current
names). Treat every name as tentative until confirmed by a human.

@note The experiments reference fields by raw struct offset (e.g. `xDD4`,
`attrs->x0`), matching the original derivation; each field's current name is
recorded on its @c \@alias tag.

## Method

- Tooling: Dolphin GDB stub (port 2159) + dolphin-debugger-mcp, with symbols
  loaded from the matching decomp (`config/GALE01`). Because the build
  byte-matches retail GALE01, `symbols.txt` addresses are the live RAM
  addresses, so a halted PC / field offset maps directly to source.
- Layout: item field offsets are absolute within `struct Item`.
  `ip = gobj->user_data` (`gobj + 0x2C`); flipper itemVars at `ip + 0xDD4`;
  flipper DatAttrs at `ip->xC4_article_data->x4_specialAttributes`.
- Instance addresses are per-spawn; the offsets are stable. (E0-E3 used
  `ip = 0x80d79900`; after a game reboot E4/E5 used `ip = 0x80d77520`.)

## Experiments

@anchor fp_e0
### E0 — Read the static DatAttrs out of RAM
Action: broke at itFlipper_Spawned(); followed
`ip -> xC4_article_data -> x4_specialAttributes` to `attrs = 0x80825a44`;
read 40 bytes. Observed (offset = value): `x0=18 x4=25 x8=500 xC=0.8 x10=0.5
x14=10 x18=11.5 x1C=0.131(rad) x20=0.000872 x24=0.8727(rad, = 50 deg)`.

@anchor fp_e1
### E1 — Flipper deals damage while airborne (normal throw)
Action: broke at itFlipper_DmgDealt(); threw the flipper into a fighter
mid-flight.
Observed: `xDD4 = 18` (== `attrs->x0`); `xDD8 = 0`;
`Item.xCF4_fighterGObjUnk = 0x80cb2a60` (set), `Item.xCEC_fighterGObj =
NULL`. Deduced: `xDD4` is loaded from a flight-timer attr; `xDD8 = 0` is the
"airborne projectile" state (itFlipper_DmgDealt() took the bounce branch);
the dealt handler reads `xCF4`, the received handler reads `xCEC`.

@anchor fp_e2
### E2 — Flight timer counts down and triggers settle (strong throw)
Action: broke at itFlipper_Inflight_Anim() (per flight frame) and
itFlipper_Settle(). Threw the flipper into open space; sampled `xDD4` each
frame; read `xD44_lifeTimer` and `xDD8` immediately before and after
itFlipper_Settle().
Observed:
- `xDD4` over consecutive frames: `25 -> 24 -> 23` (-1/frame); ==
`attrs->x4` at throw (this was the strong throw).
- itFlipper_Settle() entry: `xDD4 = 0`, `xDD8 = 0`, `xD44_lifeTimer =
1400.0`.
- itFlipper_Settle() return: `xDD8 = 1`, `xD44_lifeTimer = 500.0` (==
`attrs->x8`).

Deduced: `xDD4` = flight timer (counts down; reaching 0 triggers settle);
`x4` = strong-throw flight value (25); `xDD8` = settled flag (0 -> 1 on
settle); `x8` = post-settle lifetime (500).

@anchor fp_e3
### E3 — Settled flipper strikes a fighter (spin + hitbox)
Action: broke at itFlipper_AddSpinImpulse(), then itFlipper_UpdateSpin();
walked a fighter into the settled, spinning flipper and sampled
`xDE0`/`xDE4` over consecutive frames. Observed:
- At the hit: caller of itFlipper_AddSpinImpulse() =
`itFlipper_DmgDealt+0x114` (the settled, `xDD8=1` branch); `xDDC = 10` (==
`attrs->x14`).
- `xDE4` (spin velocity): `0 -> 0.528` at the impulse, then per-frame
  `0.5283 -> 0.5274 -> 0.5266` (decreasing ~0.00087/frame == `attrs->x20`).
- `xDE0` (spin angle): `0 -> 0.5274 -> 1.0539`, i.e. `xDE0 += xDE4` each
frame; itFlipper_UpdateSpin() feeds this to HSD_JObjSetRotationX() (the
paddle visibly spins).

Deduced: `xDDC` = hitbox cooldown set from `attrs->x14` (10) on a hit;
`xDE4` = angular velocity (kicked on contact, decays by `attrs->x20`);
`xDE0` = accumulated spin angle driving the paddle rotation;
`x20` = per-frame spin decay; `x14` = hitbox interval.

@anchor fp_e4
### E4 — Hard hit saturates the spin clamp
Action: broke at itFlipper_AddSpinImpulse(); dash/aerial into a
freshly-settled flipper (`xDE4 = 0`). Read the `angle` arg (`f1`) and `xDE4`
before, then `xDE4` after via the return address
(`itFlipper_DmgDealt+0x114`). Observed: `angle` arg `f1 = 0.8047` rad (~46
deg); `xDE4` before = 0; `xDE4` after = `0xbf5f66f3` = `-0.8727` (==
`-attrs->x24`; same magnitude bits as `x24 = 0x3f5f66f3`). Deduced: `x24` =
maximum |spin velocity|; `xDE4` saturates at `+/-x24`. The `angle` arg (=
`MTXDegToRad(x18) * fighter_speed`, per itFlipper_SpinFromFighter())
confirms `x18` scales fighter speed into spin. This hit's `angle + x1C`
(~0.936) exceeded `x24`, so it clamped -- `x18`/`x1C` magnitudes are read
(11.5 / 0.131) but their exact split is not isolated from a clamped hit.

@anchor fp_e5
### E5 — Wall and floor bounce restitution
Action: disassembled itFlipper_Inflight_Coll(); set breakpoints at the two
collision-gated `vel.x` stores: `+0x44` (`vel.x *= -xC`, on wall `coll &
0xC`) and `+0x98` (`vel.x *= x10`, on floor `coll & 1`). Threw the flipper
into a wall, then skipped it off the floor; read `vel.x` before (`f1`) and
after (`f0`). Observed:
- Wall (`coll = 0x4`): `vel.x` `-1.6953 -> +1.3562` (factor `-0.800` ==
`-attrs->xC`).
- Floor (`coll = 0x1`): `vel.x` `-2.6798 -> -1.3399` (factor `0.500` ==
`attrs->x10`).

Deduced: `xC` = wall/ceiling restitution (0.8; flips and scales `vel.x`);
`x10` = floor restitution (0.5; scales `vel.x`).

@anchor fp_e6
### E6 — Stage-anchored flipper (Bowser's Target Test)
itFlipper_Spawn() (the only writer of `xDE8 = 1` / `xDEC = jobj`) is called
from Ground_801C42AC(), which runs on **Target Test** stage load and spawns
a flipper anchored to each stage joint in `stage_info.x280[0xFC..0x103]`. It
never fires in Training mode (no such joints), which is why E0-E5 only saw
`xDE8 = 0`. Action: entered **Bowser's Break the Targets** (its course has a
flipper obstacle oscillating on a moving joint); broke at
itFlipper_UpdateActive() (settled-flipper per-frame); read the itemVars and
compared the flipper's `pos` (`ip + 0x4C`) to the anchor jobj's world-matrix
translation
(`xDEC + 0x44`, column 3).
Observed: `xDE8 = 1`; `xDEC = 0x80c2d140` (non-NULL HSD_JObj); `xDE4 = 0`
(idle, state 5 via itFlipper_Active_Anim()); flipper `pos = (20.326, 16.621,
0.0)` == anchor jobj world translation `(20.326, 16.621, 0.0)`, bit-for-bit
identical
(`0x41a29c00 0x4184f7d3 0x0`).
Verified at spawn: reset the stage with a breakpoint at itFlipper_Spawn();
it was called with `jobj` arg `r3 = 0x80c2d140`, and the flipper it returned
had `xDE8 = 1` and `xDEC = 0x80c2d140` (== the arg) with `xDE0 = 0` (fresh)
-- so itFlipper_Spawn() sets `xDE8 = 1` and `xDEC` directly from its jobj
argument. Deduced: `xDE8` = stage-anchored flag (set only by
itFlipper_Spawn()); `xDEC` = the anchor HSD_JObj the flipper is pinned to
(its `pos` tracks the joint exactly).

## Function experiments

@anchor fp_f1
### F1 — Motion-state machine (`msid` = `ip + 0x24`)
Action: write-watchpoint on a flipper's `msid`; drove it spawn -> fall ->
land
-> pick up -> throw -> settle (Training mode), logging each `(new msid,
caller)` (caller = LR at the Item_80268E5C() store). Observed transitions:
- itFlipper_EnterFalling() -> `msid 1` (at spawn): falling
- itFlipper_EnterResting() -> `msid 0` (on landing): rest on ground (also
resets velocity)
- itFlipper_PickedUp() -> `msid 2`: held
- itFlipper_Thrown() -> `msid 3`: thrown / in flight
- itFlipper_EnterActive() -> `msid 5` (via itFlipper_Settle()): active
flipper

Deduced state ids: `0`=rest, `1`=fall, `2`=held, `3`=flight, `5`=active
(matches E6's anchored flipper sitting in state 5).

@anchor fp_f2
### F2 — Flipper-vs-flipper separation (itFlipper_Repel())
Action: broke at itFlipper_Repel(); clanked an attack into a settled
flipper, then put two flippers in contact. Read the `kind` arg (`r4` =
`ip->xC38`) and `x40_vel` before/after. Observed:
- Normal attack clank: `kind = -1` (0xFFFFFFFF); `x40_vel` unchanged
`(0,0,0)`.
- Two flippers touching: `kind = 0x14` (== `It_Kind_Flipper`); `x40_vel`
  `(0,0,0) -> (0.199, -0.019, 0)`, magnitude exactly `0.2`, directed away
from the other flipper.

Deduced: itFlipper_Repel() adds a fixed `0.2` separation impulse away from a
colliding flipper, only when the collided kind is `It_Kind_Flipper`.
