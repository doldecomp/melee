#ifndef MELEE_FT_CHARA_FTPURIN_FTPURIN_H
#define MELEE_FT_CHARA_FTPURIN_FTPURIN_H

#include "melee/ft/forward.h"

#include "ft/ftcommon.h"
#include "ft/types.h"
#include "lb/lbvector.h"

typedef struct _ftPurinAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    s32 x14;
    f32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C;
    u8 data_filler_1[0x100 - 0x30];
} ftPurinAttributes;

extern MotionState ftPr_Init_MotionStateTable[];
extern char ftPr_Init_DatFilename[];
extern char ftPr_Init_DataName[];
extern Fighter_CostumeStrings ftPr_Init_CostumeStrings[];
extern char ftPr_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftPr_Init_DemoMotionFilenames;

/// functions

void ftPr_Init_LoadSpecialAttrs(HSD_GObj* gobj);
void ftPr_Init_OnDeath(HSD_GObj* gobj);
void ftPr_Init_OnItemDrop(HSD_GObj* gobj, bool bool1);
void ftPr_Init_OnItemInvisible(HSD_GObj* gobj);
void ftPr_Init_OnItemPickup(HSD_GObj* gobj, bool bool);
void ftPr_Init_OnItemVisible(HSD_GObj* gobj);
void ftPr_Init_OnKnockbackEnter(HSD_GObj* gobj);
void ftPr_Init_OnKnockbackExit(HSD_GObj* gobj);
void ftPr_Init_OnLoad(HSD_GObj* gobj);
void ftPr_Init_OnUserDataRemove(HSD_GObj* gobj);
void ftPr_SpecialAirHi_Enter(HSD_GObj*);
void ftPr_SpecialAirLw_Enter(HSD_GObj*);
void ftPr_SpecialAirN_Enter(HSD_GObj*);
void ftPr_SpecialAirS_Enter(HSD_GObj*);
void ftPurin_SpecialHi_SetVars(HSD_GObj* gobj);
void ftPr_SpecialHi_Enter(HSD_GObj*);
void ftPr_SpecialLw_Enter(HSD_GObj*);
void ftPr_SpecialN_Enter(HSD_GObj*);
void ftPr_SpecialS_Enter(HSD_GObj*);
void ftCo_MultiJump_Anim(HSD_GObj*);
void ftCo_MultiJump_IASA(HSD_GObj*);
void ftCo_MultiJump_Phys(HSD_GObj*);
void ftCo_MultiJump_Coll(HSD_GObj*);
void ftPr_Init_8013C2F8(void);
void ftPr_Init_8013C360(HSD_GObj* gobj);
void ftPr_Init_8013C494(HSD_GObj* gobj);
void ftPr_Init_UnkMtxFunc0(HSD_GObj* gobj, int arg1, Mtx vmtx);
void ftPr_Init_UnkIntBoolFunc0(Fighter* fp, int arg1, bool arg2);
void ftPr_SpecialHi_8013CD34(HSD_GObj*);
void ftPr_SpecialHi_8013CDD8(HSD_GObj*);
void ftPr_SpecialLw_8013D104(HSD_GObj*);
void ftPr_SpecialLw_8013D19C(HSD_GObj*);
void ftPr_SpecialS_8013D590(HSD_GObj*);
void ftPr_SpecialS_8013D5F0(HSD_GObj*);
void ftPr_SpecialS_8013D8E4(HSD_GObj*);
void ftPr_SpecialS_8013DA24(HSD_GObj*);
void ftPr_SpecialS_8013DC64(HSD_GObj*);
void ftPr_SpecialS_8013DD54(HSD_GObj*);
void ftPr_Init_8013C94C(HSD_GObj*);
void ftPr_SpecialHi_Anim(HSD_GObj*);
void ftPr_SpecialAirHi_Anim(HSD_GObj*);
void ftPr_SpecialHi_IASA(HSD_GObj*);
void ftPr_SpecialAirHi_IASA(HSD_GObj*);
void ftPr_SpecialHi_Phys(HSD_GObj*);
void ftPr_SpecialAirHi_Phys(HSD_GObj*);
void ftPr_SpecialHi_Coll(HSD_GObj*);
void ftPr_SpecialAirHi_Coll(HSD_GObj*);
void ftPr_SpecialHi_8013CE7C(HSD_GObj*);
void ftPr_SpecialLw_Anim(HSD_GObj*);
void ftPr_SpecialAirLw_Anim(HSD_GObj*);
void ftPr_SpecialLw_IASA(HSD_GObj*);
void ftPr_SpecialAirLw_IASA(HSD_GObj*);
void ftPr_SpecialLw_Phys(HSD_GObj*);
void ftPr_SpecialAirLw_Phys(HSD_GObj*);
void ftPr_SpecialLw_Coll(HSD_GObj*);
void ftPr_SpecialAirLw_Coll(HSD_GObj*);
void ftPr_SpecialS_Anim(HSD_GObj*);
void ftPr_SpecialAirS_Anim(HSD_GObj*);
void ftPr_SpecialS_IASA(HSD_GObj*);
void ftPr_SpecialAirS_IASA(HSD_GObj*);
void ftPr_SpecialS_Phys(HSD_GObj*);
void ftPr_SpecialAirS_Phys(HSD_GObj*);
void ftPr_SpecialS_Coll(HSD_GObj*);
void ftPr_SpecialAirS_Coll(HSD_GObj*);
void ftPr_SpecialS_8013D658(HSD_GObj*);
void ftPr_SpecialS_8013D764(HSD_GObj*);
void ftPr_SpecialS_8013D8B0(HSD_GObj*);
void ftPr_SpecialNChargeStart_Anim(HSD_GObj*);
void ftPr_SpecialNChargeLoop_Anim(HSD_GObj*);
void ftPr_SpecialNChargeFull_Anim(HSD_GObj*);
void ftPr_SpecialNChargeRelease_Anim(HSD_GObj*);
void ftPr_SpecialNStartTurn_Anim(HSD_GObj*);
void ftPr_SpecialNEnd_Anim(HSD_GObj*);
void ftPr_SpecialAirNChargeStart_Anim(HSD_GObj*);
void ftPr_SpecialAirNChargeLoop_Anim(HSD_GObj*);
void ftPr_SpecialAirNChargeFull_Anim(HSD_GObj*);
void ftPr_SpecialAirNChargeRelease_Anim(HSD_GObj*);
void ftPr_SpecialAirNStartTurn_Anim(HSD_GObj*);
void ftPr_SpecialAirNEnd_Anim(HSD_GObj*);
void ftPr_SpecialNHit_Anim(HSD_GObj*);
void ftPr_SpecialNChargeStart_IASA(HSD_GObj*);
void ftPr_SpecialNChargeLoop_IASA(HSD_GObj*);
void ftPr_SpecialNChargeFull_IASA(HSD_GObj*);
void ftPr_SpecialNChargeRelease_IASA(HSD_GObj*);
void ftPr_SpecialNStartTurn_IASA(HSD_GObj*);
void ftPr_SpecialNEnd_IASA(HSD_GObj*);
void ftPr_SpecialAirNChargeStart_IASA(HSD_GObj*);
void ftPr_SpecialAirNChargeLoop_IASA(HSD_GObj*);
void ftPr_SpecialAirNChargeFull_IASA(HSD_GObj*);
void ftPr_SpecialAirNChargeRelease_IASA(HSD_GObj*);
void ftPr_SpecialAirNStartTurn_IASA(HSD_GObj*);
void ftPr_SpecialAirNEnd_IASA(HSD_GObj*);
void ftPr_SpecialNHit_IASA(HSD_GObj*);
void ftPr_SpecialNChargeStart_Phys(HSD_GObj*);
void ftPr_SpecialNChargeLoop_Phys(HSD_GObj*);
void ftPr_SpecialNChargeFull_Phys(HSD_GObj*);
void ftPr_SpecialNChargeRelease_Phys(HSD_GObj*);
void ftPr_SpecialNStartTurn_Phys(HSD_GObj*);
void ftPr_SpecialNEnd_Phys(HSD_GObj*);
void ftPr_SpecialAirNChargeStart_Phys(HSD_GObj*);
void ftPr_SpecialAirNChargeLoop_Phys(HSD_GObj*);
void ftPr_SpecialAirNChargeFull_Phys(HSD_GObj*);
void ftPr_SpecialAirNChargeRelease_Phys(HSD_GObj*);
void ftPr_SpecialAirNStartTurn_Phys(HSD_GObj*);
void ftPr_SpecialAirNEnd_Phys(HSD_GObj*);
void ftPr_SpecialNHit_Phys(HSD_GObj*);
void ftPr_SpecialNChargeStart_Coll(HSD_GObj*);
void ftPr_SpecialNChargeLoop_Coll(HSD_GObj*);
void ftPr_SpecialNChargeFull_Coll(HSD_GObj*);
void ftPr_SpecialNChargeRelease_Coll(HSD_GObj*);
void ftPr_SpecialNStartTurn_Coll(HSD_GObj*);
void ftPr_SpecialNEnd_Coll(HSD_GObj*);
void ftPr_SpecialAirNChargeStart_Coll(HSD_GObj*);
void ftPr_SpecialAirNChargeLoop_Coll(HSD_GObj*);
void ftPr_SpecialAirNChargeFull_Coll(HSD_GObj*);
void ftPr_SpecialAirNChargeRelease_Coll(HSD_GObj*);
void ftPr_SpecialAirNStartTurn_Coll(HSD_GObj*);
void ftPr_SpecialAirNEnd_Coll(HSD_GObj*);
void ftPr_SpecialNHit_Coll(HSD_GObj*);
void ftPr_SpecialN_8014222C(HSD_GObj*);
void* ftPr_Init_UnkMotionStates6(HSD_GObj* gobj);

#endif
