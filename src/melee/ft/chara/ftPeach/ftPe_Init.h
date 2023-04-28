#ifndef GALE01_11B51C
#define GALE01_11B51C

#include "ftPeach/forward.h"
#include <baselib/forward.h>

#include "ft/types.h"

/* 11B51C */ void ftPe_Init_OnDeath(HSD_GObj* gobj);
/* 11B628 */ void ftPe_Init_OnLoad(HSD_GObj* gobj);
/* 11B704 */ void ftPe_Init_8011B704(HSD_GObj* gobj);
/* 11B740 */ void ftPe_Init_OnItemPickup(HSD_GObj* gobj, bool bool);
/* 11B820 */ void ftPe_Init_OnItemInvisible(HSD_GObj* gobj);
/* 11B868 */ void ftPe_Init_OnItemVisible(HSD_GObj* gobj);
/* 11B8B0 */ void ftPe_Init_OnItemDrop(HSD_GObj* gobj, bool bool1);
/* 11B904 */ void ftPe_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 11B93C */ void ftPe_Init_8011B93C(HSD_GObj* gobj);
/* 11B998 */ void ftPe_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 11B9DC */ void ftPe_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 11BA20 */ s32 ftPe_8011BA20(Fighter* fp);
/* 11BC38 */ void ftPe_Float_Anim(HSD_GObj* gobj);
/* 11BC8C */ void ftPe_Float_IASA(HSD_GObj* gobj);
/* 11BD18 */ void ftPe_Float_Phys(HSD_GObj* gobj);
/* 11BD3C */ void ftPe_Float_Coll(HSD_GObj* gobj);
/* 11BDF0 */ void ftPe_FloatFall_Anim(HSD_GObj* gobj);
/* 11BE2C */ void ftPe_FloatFall_IASA(HSD_GObj* gobj);
/* 11BE30 */ void ftPe_FloatFall_Phys(HSD_GObj* gobj);
/* 11BE50 */ void ftPe_FloatFall_Coll(HSD_GObj* gobj);
/* 11BF88 */ void ftPe_FloatAttackAir_Anim(HSD_GObj* gobj);
/* 11C044 */ void ftPe_FloatAttackAir_IASA(HSD_GObj* gobj);
/* 11C160 */ void ftPe_FloatAttackAir_Phys(HSD_GObj* gobj);
/* 11C198 */ void ftPe_FloatAttackAir_Coll(HSD_GObj* gobj);
/* 11C248 */ void ftPe_AttackS4_Anim(HSD_GObj* gobj);
/* 11C284 */ void ftPe_AttackS4_IASA(HSD_GObj* gobj);
/* 11C2B4 */ void ftPe_AttackS4_Phys(HSD_GObj* gobj);
/* 11C2D4 */ void ftPe_AttackS4_Coll(HSD_GObj* gobj);
/* 11C34C */ void ftPe_SpecialS_Enter(HSD_GObj* gobj);
/* 11C3C4 */ void ftPe_SpecialAirS_Enter(HSD_GObj* gobj);
/* 11C4F0 */ void ftPe_SpecialSStart_Anim(HSD_GObj* gobj);
/* 11C588 */ void ftPe_SpecialAirSStart_Anim(HSD_GObj* gobj);
/* 11C5E8 */ void ftPe_SpecialSStart_IASA(HSD_GObj* gobj);
/* 11C5EC */ void ftPe_SpecialAirSStart_IASA(HSD_GObj* gobj);
/* 11C5F0 */ void ftPe_SpecialSStart_Phys(HSD_GObj* gobj);
/* 11C644 */ void ftPe_SpecialAirSStart_Phys(HSD_GObj* gobj);
/* 11C664 */ void ftPe_SpecialSStart_Coll(HSD_GObj* gobj);
/* 11C6FC */ void ftPe_SpecialAirSStart_Coll(HSD_GObj* gobj);
/* 11C878 */ void ftPe_SpecialAirSJump_Anim(HSD_GObj* gobj);
/* 11C8C8 */ void ftPe_SpecialAirSJump_IASA(HSD_GObj* gobj);
/* 11C8CC */ void ftPe_SpecialAirSJump_Phys(HSD_GObj* gobj);
/* 11C93C */ void ftPe_SpecialAirSJump_Coll(HSD_GObj* gobj);
/* 11CA84 */ void ftPe_SpecialSEnd_Anim(HSD_GObj* gobj);
/* 11CAC0 */ void ftPe_SpecialAirSEnd_Anim(HSD_GObj* gobj);
/* 11CAFC */ void ftPe_SpecialSEnd_IASA(HSD_GObj* gobj);
/* 11CB00 */ void ftPe_SpecialAirSEnd_IASA(HSD_GObj* gobj);
/* 11CB04 */ void ftPe_SpecialSEnd_Phys(HSD_GObj* gobj);
/* 11CB24 */ void ftPe_SpecialAirSEnd_Phys(HSD_GObj* gobj);
/* 11CB44 */ void ftPe_SpecialSEnd_Coll(HSD_GObj* gobj);
/* 11CB80 */ void ftPe_SpecialAirSEnd_Coll(HSD_GObj* gobj);
/* 11D11C */ void ftPe_SpecialLw_Enter(HSD_GObj* gobj);
/* 11D1C4 */ void ftPe_SpecialAirLw_Enter(HSD_GObj* gobj);
/* 11D2EC */ void ftPe_SpecialLw_Anim(HSD_GObj* gobj);
/* 11D340 */ void ftPe_SpecialAirLw_Anim(HSD_GObj* gobj);
/* 11D394 */ void ftPe_SpecialLw_Phys(HSD_GObj* gobj);
/* 11D3B4 */ void ftPe_SpecialAirLw_Phys(HSD_GObj* gobj);
/* 11D3D4 */ void ftPe_SpecialLw_Coll(HSD_GObj* gobj);
/* 11D3FC */ void ftPe_SpecialAirLw_Coll(HSD_GObj* gobj);
/* 11D72C */ void ftPe_SpecialHi_Enter(HSD_GObj* gobj);
/* 11D7F0 */ void ftPe_SpecialAirHi_Enter(HSD_GObj* gobj);
/* 11D8D0 */ void ftPe_SpecialHiStart_Anim(HSD_GObj* gobj);
/* 11D980 */ void ftPe_SpecialAirHiStart_Anim(HSD_GObj* gobj);
/* 11DA30 */ void ftPe_SpecialHiStart_IASA(HSD_GObj* gobj);
/* 11DB78 */ void ftPe_SpecialAirHiStart_IASA(HSD_GObj* gobj);
/* 11DCC0 */ void ftPe_SpecialHiStart_Phys(HSD_GObj* gobj);
/* 11DCF8 */ void ftPe_SpecialAirHiStart_Phys(HSD_GObj* gobj);
/* 11DDBC */ void ftPe_SpecialHiStart_Coll(HSD_GObj* gobj);
/* 11DE2C */ void ftPe_SpecialAirHiStart_Coll(HSD_GObj* gobj);
/* 11DE9C */ void ftPe_SpecialHiEnd_Anim(HSD_GObj* gobj);
/* 11DEFC */ void ftPe_SpecialAirHiEnd_Anim(HSD_GObj* gobj);
/* 11DF5C */ void ftPe_SpecialHiEnd_IASA(HSD_GObj* gobj);
/* 11DF60 */ void ftPe_SpecialAirHiEnd_IASA(HSD_GObj* gobj);
/* 11DF64 */ void ftPe_SpecialHiEnd_Phys(HSD_GObj* gobj);
/* 11DFD0 */ void ftPe_SpecialAirHiEnd_Phys(HSD_GObj* gobj);
/* 11E094 */ void ftPe_SpecialHiEnd_Coll(HSD_GObj* gobj);
/* 11E104 */ void ftPe_SpecialAirHiEnd_Coll(HSD_GObj* gobj);
/* 11E3D0 */ void ftPe_SpecialN_Enter(HSD_GObj* gobj);
/* 11E45C */ void ftPe_SpecialAirN_Enter(HSD_GObj* gobj);
/* 11E4F8 */ void ftPe_SpecialN_Anim(HSD_GObj* gobj);
/* 11E5B4 */ void ftPe_SpecialAirN_Anim(HSD_GObj* gobj);
/* 11E670 */ void ftPe_SpecialN_IASA(HSD_GObj* gobj);
/* 11E674 */ void ftPe_SpecialAirN_IASA(HSD_GObj* gobj);
/* 11E678 */ void ftPe_SpecialN_Phys(HSD_GObj* gobj);
/* 11E6AC */ void ftPe_SpecialAirN_Phys(HSD_GObj* gobj);
/* 11E75C */ void ftPe_SpecialN_Coll(HSD_GObj* gobj);
/* 11E798 */ void ftPe_SpecialAirN_Coll(HSD_GObj* gobj);
/* 11E9A0 */ void ftPe_SpecialNHit_Anim(HSD_GObj* gobj);
/* 11EA04 */ void ftPe_SpecialAirNHit_Anim(HSD_GObj* gobj);
/* 11EA68 */ void ftPe_SpecialNHit_IASA(HSD_GObj* gobj);
/* 11EA6C */ void ftPe_SpecialAirNHit_IASA(HSD_GObj* gobj);
/* 11EA70 */ void ftPe_SpecialNHit_Phys(HSD_GObj* gobj);
/* 11EA90 */ void ftPe_SpecialAirNHit_Phys(HSD_GObj* gobj);
/* 11EAE0 */ void ftPe_SpecialNHit_Coll(HSD_GObj* gobj);
/* 11EB1C */ void ftPe_SpecialAirNHit_Coll(HSD_GObj* gobj);
/* 3CCCB8 */ extern MotionState ftPe_Init_MotionStateTable[ftPe_MS_SelfCount];
/* 3CD078 */ extern char ftPe_Init_DatFilename[];
/* 3CD084 */ extern char ftPe_Init_DataName[];
/* 3CD204 */ extern char ftPe_Init_AnimDatFilename[];
/* 3CD280 */ extern Fighter_DemoStrings ftPe_Init_DemoMotionFilenames;
/* 3CD290 */ extern Fighter_CostumeStrings ftPe_Init_CostumeStrings[];

#endif
