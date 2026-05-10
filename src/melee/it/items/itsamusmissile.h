#ifndef GALE01_2B62D0
#define GALE01_2B62D0

#include <platform.h>

#include "it/forward.h"

#include "it/items/types.h"

struct _m2c_stack_it_802B64FC {
    /* 0x00 */ char pad_0[0x10];
    /* 0x10 */ Vec3 vec0;
    /* 0x1C */ Vec3 vec1;
    /* 0x28 */ Vec3 vec2;
    /* 0x34 */ Vec3 vec3;
    /* 0x40 */ char pad_40[8];
}; /* size = 0x48 */

struct _m2c_stack_itSamusmissile_UnkMotion0_Phys {
    /* 0x00 */ char pad_0[0x40];
    /* 0x40 */ Vec3 vec;
    /* 0x4C */ char pad_4C[0x14];
}; /* size = 0x60 */

/* 2B6C28 */ bool it_2725_Logic52_DmgDealt(Item_GObj*);
/* 2B6C7C */ bool it_2725_Logic52_Clanked(Item_GObj*);
/* 2B6CD0 */ bool it_2725_Logic52_HitShield(Item_GObj*);
/* 2B62D0 */ Item_GObj* it_802B62D0(Item_GObj*, Vec3* pos, bool,
                                    float facing_dir);
/* 2B63F8 */ void it_802B63F8(HSD_GObj* gobj);
/* 2B64FC */ void it_802B64FC(Item_GObj* gobj);
/* 2B66A8 */ void* it_802B66A8(HSD_GObj* gobj);
/* 2B6774 */ long itSamusmissile_UnkMotion0_Anim(struct HSD_GObj*);
/* 2B67E4 */ void itSamusmissile_UnkMotion0_Phys(Item_GObj* gobj);
/* 2B6A34 */ bool itSamusmissile_UnkMotion0_Coll(Item_GObj* gobj);
/* 2B6A60 */ void it_802B6A60(HSD_GObj* gobj);
/* 2B6B1C */ long itSamusmissile_UnkMotion1_Anim(struct HSD_GObj*);
/* 2B6B8C */ void itSamusmissile_UnkMotion1_Phys(Item_GObj* gobj);
/* 2B6BFC */ bool itSamusmissile_UnkMotion1_Coll(Item_GObj* gobj);
/* 2B6C28 */ bool it_2725_Logic52_DmgDealt(Item_GObj*);
/* 2B6C7C */ bool it_2725_Logic52_Clanked(Item_GObj*);
/* 2B6CD0 */ bool it_2725_Logic52_HitShield(Item_GObj*);
/* 2B6D24 */ bool it_2725_Logic52_ShieldBounced(Item_GObj*);
/* 2B6E4C */ bool it_2725_Logic52_Reflected(Item_GObj*);
/* 2B701C */ void it_802B701C(Item_GObj*);
/* 2B7080 */ bool itSamusmissile_UnkMotion3_Anim(Item_GObj* gobj);
/* 2B70A0 */ void it_802B70A0(Item_GObj*);
/* 2B7104 */ void it_2725_Logic52_EvtUnk(Item_GObj*, Item_GObj*);
/* 3F7340 */ extern ItemStateTable it_803F7340[];

#endif
