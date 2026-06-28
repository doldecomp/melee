#ifndef GALE01_290938
#define GALE01_290938

#include <platform.h>

#include "it/forward.h"

#include "it/items/types.h"

typedef enum itFlipper_MotionState {
    FLIPPER_MS_RESTING,
    FLIPPER_MS_FALLING,
    FLIPPER_MS_HELD,
    FLIPPER_MS_INFLIGHT,
    FLIPPER_MS_AIRBORNE,
    FLIPPER_MS_ACTIVE,
    FLIPPER_MS_SPINNING,
} itFlipper_MotionState;

/* 290938 */ HSD_GObj* itFlipper_Spawn(HSD_JObj*);
/* 290A20 */ void itFlipper_Spawned(Item_GObj*);
/* 290A7C */ void itFlipper_UpdateSpin(Item_GObj*);
/* 290C38 */ void itFlipper_AddSpinImpulse(Item_GObj*, Vec3*, f32);
/* 290CE8 */ void itFlipper_SpinFromFighter(Item_GObj*);
/* 290DD4 */ void itFlipper_Repel(Item_GObj* gobj, s32 kind, Vec3* pos);
/* 290E78 */ void itFlipper_EnterResting(Item_GObj*);
/* 290EC8 */ bool itFlipper_Resting_Anim(Item_GObj* gobj);
/* 290ED0 */ void itFlipper_Resting_Phys(Item_GObj* gobj);
/* 290ED4 */ bool itFlipper_Resting_Coll(Item_GObj* gobj);
/* 290F00 */ void itFlipper_EnterFalling(Item_GObj* gobj);
/* 290F28 */ bool itFlipper_Falling_Anim(Item_GObj* gobj);
/* 290F30 */ void itFlipper_Falling_Phys(Item_GObj* gobj);
/* 290F60 */ bool itFlipper_Falling_Coll(Item_GObj* gobj);
/* 290F8C */ void itFlipper_PickedUp(Item_GObj*);
/* 290FB4 */ bool itFlipper_Held_Anim(Item_GObj* gobj);
/* 290FBC */ void itFlipper_Held_Phys(Item_GObj* gobj);
/* 290FC0 */ void itFlipper_Dropped(Item_GObj*);
/* 290FE0 */ void itFlipper_Thrown(Item_GObj*);
/* 291068 */ bool itFlipper_Inflight_Anim(Item_GObj* gobj);
/* 2910A8 */ void itFlipper_Inflight_Phys(Item_GObj* gobj);
/* 291188 */ bool itFlipper_Inflight_Coll(Item_GObj* gobj);
/* 291254 */ void itFlipper_Settle(Item_GObj*);
/* 29131C */ void itFlipper_EnterActive(Item_GObj* gobj);
/* 291344 */ bool itFlipper_UpdateActive(Item_GObj* gobj);
/* 2914C8 */ bool itFlipper_Active_Anim(Item_GObj* gobj);
/* 29151C */ bool itFlipper_Spinning_Anim(Item_GObj* gobj);
/* 291570 */ void itFlipper_Spinning_Phys(Item_GObj* gobj);
/* 2915B4 */ bool itFlipper_Spinning_Coll(Item_GObj* gobj);
/* 2915E8 */ bool itFlipper_DmgDealt(Item_GObj*);
/* 2917C8 */ bool itFlipper_Clanked(Item_GObj*);
/* 2918A0 */ bool itFlipper_HitShield(Item_GObj*);
/* 291978 */ bool itFlipper_Reflected(Item_GObj*);
/* 291998 */ bool itFlipper_ShieldBounced(Item_GObj*);
/* 2919B8 */ bool itFlipper_DmgReceived(Item_GObj*);
/* 291B58 */ void itFlipper_EnteredAir(Item_GObj*);
/* 291B80 */ bool itFlipper_Airborne_Anim(Item_GObj* gobj);
/* 291B88 */ void itFlipper_Airborne_Phys(Item_GObj* gobj);
/* 291B8C */ bool itFlipper_Airborne_Coll(Item_GObj* gobj);
/* 291BC0 */ void itFlipper_EvtUnk(Item_GObj*, Item_GObj*);
/* 3F5EA8 */ extern ItemStateTable ItemStateTable_Flipper[];

#endif
