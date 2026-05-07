#ifndef GALE01_29A114
#define GALE01_29A114

#include <platform.h>

#include "it/forward.h"

#include "it/items/types.h"

typedef struct itLipstickSporeAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    s32 x14;
    s32 x18;
} itLipstickSporeAttributes;

/* 29A114 */ void it_8029A114(Fighter_GObj*, Vec*, f32 facing_dir, s32 arg4);
/* 29A218 */ void it_8029A218(HSD_GObj* owner, Vec3* pos, f32 facing_dir,
                              s32 arg4);
/* 29A31C */ void it_8029A31C(Item_GObj*, Fighter_GObj*, Item*);
/* 29A498 */ void it_8029A498(Item_GObj* gobj, Fighter_GObj* owner);
/* 29A504 */ bool itLipstickspore_UnkMotion0_Anim(Item_GObj* gobj);
/* 29A524 */ void itLipstickspore_UnkMotion0_Phys(Item_GObj* gobj);
/* 29A58C */ bool itLipstickspore_UnkMotion0_Coll(Item_GObj* gobj);
/* 29A5C0 */ bool itLipstickspore_UnkMotion1_Anim(Item_GObj* gobj);
/* 29A5E0 */ void itLipstickspore_UnkMotion1_Phys(Item_GObj*);
/* 29A600 */ bool itLipstickSpore_Logic37_DmgDealt(Item_GObj*);
/* 29A608 */ bool itLipstickSpore_Logic37_Clanked(Item_GObj*);
/* 29A610 */ bool itLipstickSpore_Logic37_HitShield(Item_GObj*);
/* 29A618 */ bool itLipstickSpore_Logic37_Absorbed(Item_GObj*);
/* 29A620 */ bool itLipstickSpore_Logic37_Reflected(Item_GObj*);
/* 29A704 */ bool itLipstickSpore_Logic37_ShieldBounced(Item_GObj*);
/* 29A728 */ void itLipstickSpore_Logic37_EvtUnk(Item_GObj*, Item_GObj*);
/* 3F6680 */ extern ItemStateTable it_803F6680[];

#endif
