#ifndef GALE01_281164
#define GALE01_281164

#include <platform.h>

#include "it/forward.h"

#include "it/items/types.h"

// Keep this if it is NOT defined in itCommonItems.h or similar.
// If you get a redefinition error for this too, remove it.
typedef struct itDoseiAttributes {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} itDoseiAttributes;

/* * NOTE: itDosei_ItemVars is removed from here because
 * it is defined in src/melee/it/itCommonItems.h
 */

/* 281164 */ void it_3F14_Logic7_Spawned(Item_GObj*);
/* 281390 */ void fn_80281390(Item_GObj*);
/* 2813F8 */ bool itDosei_UnkMotion0_Anim(Item_GObj* gobj);
/* 2816F0 */ void itDosei_UnkMotion0_Phys(Item_GObj* gobj);
/* 2816F4 */ bool itDosei_UnkMotion0_Coll(Item_GObj* gobj);
/* 281734 */ void fn_80281734(Item_GObj* gobj);
/* 2817A0 */ void it_802817A0(Item_GObj*);
/* 281AB4 */ bool itDosei_UnkMotion1_Anim(Item_GObj* gobj);
/* 281B44 */ void itDosei_UnkMotion1_Phys(Item_GObj* gobj);
/* 281B7C */ bool itDosei_UnkMotion1_Coll(Item_GObj* gobj);
/* 281C6C */ void it_80281C6C(Item_GObj* gobj);
/* 281D00 */ bool itDosei_UnkMotion2_Anim(Item_GObj* gobj);
/* 281E30 */ void itDosei_UnkMotion2_Phys(Item_GObj* gobj);
/* 281E34 */ bool itDosei_UnkMotion2_Coll(Item_GObj* gobj);
/* 282074 */ void it_80282074(Item_GObj* gobj);
/* 2820CC */ bool itDosei_UnkMotion3_Anim(Item_GObj* gobj);
/* 282130 */ void itDosei_UnkMotion3_Phys(Item_GObj* gobj);
/* 282160 */ bool itDosei_UnkMotion5_Coll(Item_GObj* gobj);
/* 28218C */ void it_3F14_Logic7_PickedUp(Item_GObj*);
/* 2824B8 */ bool itDosei_UnkMotion4_Anim(Item_GObj* gobj);
/* 2826F4 */ void itDosei_UnkMotion4_Phys(Item_GObj* gobj);
/* 2826F8 */ void it_3F14_Logic7_Dropped(Item_GObj*);
/* 2829FC */ void it_3F14_Logic7_Thrown(Item_GObj*);
/* 282AC0 */ bool itDosei_UnkMotion5_Anim(Item_GObj* gobj);
/* 282AC8 */ void itDosei_UnkMotion5_Phys(Item_GObj* gobj);
/* 282B14 */ void it_3F14_Logic7_EnteredAir(Item_GObj*);
/* 282B84 */ bool itDosei_UnkMotion6_Anim(Item_GObj* gobj);
/* 282BA8 */ void itDosei_UnkMotion6_Phys(Item_GObj* gobj);
/* 282BAC */ bool itDosei_UnkMotion6_Coll(Item_GObj* gobj);
/* 282BFC */ void it_80282BFC(Item_GObj* gobj);
/* 282C54 */ bool itDosei_UnkMotion8_Anim(Item_GObj* gobj);
/* 282C78 */ void itDosei_UnkMotion8_Phys(Item_GObj* gobj);
/* 282CA8 */ bool itDosei_UnkMotion8_Coll(Item_GObj* gobj);
/* 282CD4 */ void fn_80282CD4(Item_GObj*);
/* 282D48 */ bool itDosei_UnkMotion7_Anim(Item_GObj* gobj);
/* 282DA0 */ void itDosei_UnkMotion7_Phys(Item_GObj* gobj);
/* 282DA4 */ bool itDosei_UnkMotion7_Coll(Item_GObj* gobj);
/* 282DE4 */ UNK_RET it_80282DE4(UNK_PARAMS);
/* 2830F4 */ bool itDosei_UnkMotion9_Anim(Item_GObj* gobj);
/* 2832A8 */ void itDosei_UnkMotion9_Phys(Item_GObj* gobj);
/* 2832AC */ bool itDosei_UnkMotion9_Coll(Item_GObj* gobj);
/* 283504 */ bool itDosei_UnkMotion10_Anim(Item_GObj* gobj);
/* 283550 */ void itDosei_UnkMotion10_Phys(Item_GObj* gobj);
/* 283554 */ bool itDosei_UnkMotion10_Coll(Item_GObj* gobj);
/* 283588 */ bool it_3F14_Logic7_DmgReceived(Item_GObj*);
/* 2838FC */ bool itDosei_UnkMotion11_Anim(Item_GObj* gobj);
/* 283960 */ void itDosei_UnkMotion11_Phys(Item_GObj* gobj);
/* 283990 */ bool itDosei_UnkMotion11_Coll(Item_GObj* gobj);
/* 2839BC */ bool it_3F14_Logic7_DmgDealt(Item_GObj*);
/* 283A3C */ bool it_3F14_Logic7_Reflected(Item_GObj*);
/* 283A5C */ bool it_3F14_Logic7_Clanked(Item_GObj*);
/* 283A80 */ bool it_3F14_Logic7_HitShield(Item_GObj*);
/* 283AA4 */ bool it_3F14_Logic7_ShieldBounced(Item_GObj*);
/* 283AC4 */ void it_3F14_Logic7_EvtUnk(Item_GObj*, Item_GObj*);
/* 3F55D0 */ extern ItemStateTable it_803F55D0[];

#endif
