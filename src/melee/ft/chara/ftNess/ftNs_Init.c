#include "ft/forward.h"

#include "ft/chara/ftNess/ftNs_Init.h"

#include "ft/chara/ftNess/ftNs_SpecialLw.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/types.h"

MotionState ftNs_Init_MotionStateTable[] = {
    { 62, 0x00241A09, 0x0A000000, ftNs_AttackS4_Anim, ftNs_AttackS4_IASA,
      ftNs_AttackS4_Phys, ftNs_AttackS4_Coll, ftCamera_UpdateCameraBox },
    { 66, 0x00240A0A, 0x0B800000, ftNs_AttackHi4_Anim, ftNs_AttackHi4_IASA,
      ftNs_AttackHi4_Phys, ftNs_AttackHi4_Coll, ftCamera_UpdateCameraBox },
    { 295, 0x0024080A, 0x0B000000, ftNs_AttackHi4Charge_Anim,
      ftNs_AttackHi4Charge_IASA, ftNs_AttackHi4Charge_Phys,
      ftNs_AttackHi4Charge_Coll, ftCamera_UpdateCameraBox },
    { 296, 0x0024080A, 0x0B000000, ftNs_AttackHi4Release_Anim,
      ftNs_AttackHi4Release_IASA, ftNs_AttackHi4Release_Phys,
      ftNs_AttackHi4Release_Coll, ftCamera_UpdateCameraBox },
    { 67, 0x00240A0B, 0x0C800000, ftNs_AttackLw4_Anim, ftNs_AttackLw4_IASA,
      ftNs_AttackLw4_Phys, ftNs_AttackLw4_Coll, ftCamera_UpdateCameraBox },
    { 297, 0x0024080B, 0x0C000000, ftNs_AttackLw4Charge_Anim,
      ftNs_AttackLw4Charge_IASA, ftNs_AttackLw4Charge_Phys,
      ftNs_AttackLw4Charge_Coll, ftCamera_UpdateCameraBox },
    { 298, 0x0024080B, 0x0C000000, ftNs_AttackLw4Release_Anim,
      ftNs_AttackLw4Release_IASA, ftNs_AttackLw4Release_Phys,
      ftNs_AttackLw4Release_Coll, ftCamera_UpdateCameraBox },
    { 299, 0x00340111, 0x12000000, ftNs_SpecialNStart_Anim,
      ftNs_SpecialNStart_IASA, ftNs_SpecialNStart_Phys,
      ftNs_SpecialNStart_Coll, ftCamera_UpdateCameraBox },
    { 300, 0x00340111, 0x12000000, ftNs_SpecialNHold_Anim,
      ftNs_SpecialNHold_IASA, ftNs_SpecialNHold_Phys, ftNs_SpecialNHold_Coll,
      ftCamera_UpdateCameraBox },
    { 301, 0x00340111, 0x12000000, ftNs_SpecialNHold_Anim,
      ftNs_SpecialNHold_IASA, ftNs_SpecialNHold_Phys, ftNs_SpecialNHold_Coll,
      ftCamera_UpdateCameraBox },
    { 302, 0x00340111, 0x12000000, ftNs_SpecialNEnd_Anim,
      ftNs_SpecialNEnd_IASA, ftNs_SpecialNEnd_Phys, ftNs_SpecialNEnd_Coll,
      ftCamera_UpdateCameraBox },
    { 303, 0x00340511, 0x12000000, ftNs_SpecialAirNStart_Anim,
      ftNs_SpecialAirNStart_IASA, ftNs_SpecialAirNStart_Phys,
      ftNs_SpecialAirNStart_Coll, ftCamera_UpdateCameraBox },
    { 304, 0x00340511, 0x12000000, ftNs_SpecialAirNHold_Anim,
      ftNs_SpecialAirNHold_IASA, ftNs_SpecialAirNHold_Phys,
      ftNs_SpecialAirNHold_Coll, ftCamera_UpdateCameraBox },
    { 305, 0x00340511, 0x12000000, ftNs_SpecialAirNHold_Anim,
      ftNs_SpecialAirNHold_IASA, ftNs_SpecialAirNHold_Phys,
      ftNs_SpecialAirNHold_Coll, ftCamera_UpdateCameraBox },
    { 306, 0x00340511, 0x12000000, ftNs_SpecialAirNEnd_Anim,
      ftNs_SpecialAirNEnd_IASA, ftNs_SpecialAirNEnd_Phys,
      ftNs_SpecialAirNEnd_Coll, ftCamera_UpdateCameraBox },
    { 307, 0x00340112, 0x13000000, ftNs_SpecialS_Anim, NULL,
      ftNs_SpecialS_Phys, ftNs_SpecialS_Coll, ftCamera_UpdateCameraBox },
    { 308, 0x00340512, 0x13000000, ftNs_SpecialAirS_Anim, NULL,
      ftNs_SpecialAirS_Phys, ftNs_SpecialAirS_Coll, ftCamera_UpdateCameraBox },
    { 309, 0x00340113, 0x14000000, ftNs_SpecialHiStart_Anim,
      ftNs_SpecialHiStart_IASA, ftNs_SpecialHiStart_Phys,
      ftNs_SpecialHiStart_Coll, ftCamera_UpdateCameraBox },
    { 310, 0x00340113, 0x14000000, ftNs_SpecialHiHold_Anim,
      ftNs_SpecialHiHold_IASA, ftNs_SpecialHiHold_Phys,
      ftNs_SpecialHiHold_Coll, ftCamera_UpdateCameraBox },
    { 311, 0x00340113, 0x14000000, ftNs_SpecialHiEnd_Anim,
      ftNs_SpecialHiEnd_IASA, ftNs_SpecialHiEnd_Phys, ftNs_SpecialHiEnd_Coll,
      ftCamera_UpdateCameraBox },
    { 312, 0x00340113, 0x14000000, ftNs_SpecialHi_Anim, ftNs_SpecialHi_IASA,
      ftNs_SpecialHi_Phys, ftNs_SpecialHi_Coll, ftCamera_UpdateCameraBox },
    { 313, 0x00340513, 0x14000000, ftNs_SpecialAirHiStart_Anim,
      ftNs_SpecialAirHiStart_IASA, ftNs_SpecialAirHiStart_Phys,
      ftNs_SpecialAirHiStart_Coll, ftCamera_UpdateCameraBox },
    { 314, 0x00340513, 0x14000000, ftNs_SpecialAirHiHold_Anim,
      ftNs_SpecialAirHiHold_IASA, ftNs_SpecialAirHiHold_Phys,
      ftNs_SpecialAirHiHold_Coll, ftCamera_UpdateCameraBox },
    { 315, 0x00340513, 0x14000000, ftNs_SpecialAirHiEnd_Anim,
      ftNs_SpecialAirHiEnd_IASA, ftNs_SpecialAirHiEnd_Phys,
      ftNs_SpecialAirHiEnd_Coll, ftCamera_UpdateCameraBox },
    { 316, 0x00340513, 0x14000000, ftNs_SpecialAirHi_Anim,
      ftNs_SpecialAirHi_IASA, ftNs_SpecialAirHi_Phys, ftNs_SpecialAirHi_Coll,
      ftCamera_UpdateCameraBox },
    { 317, 0x00340113, 0x14000000, ftNs_SpecialAirHiRebound_Anim,
      ftNs_SpecialAirHiRebound_IASA, ftNs_SpecialAirHiRebound_Phys,
      ftNs_SpecialAirHiRebound_Coll, ftCamera_UpdateCameraBox },
    { 318, 0x00340014, 0x15000000, ftNs_SpecialLwStart_Anim,
      ftNs_SpecialLwStart_IASA, ftNs_SpecialLwStart_Phys,
      ftNs_SpecialLwStart_Coll, ftCamera_UpdateCameraBox },
    { 319, 0x003C0014, 0x15000000, ftNs_SpecialLwHold_Anim,
      ftNs_SpecialLwHold_IASA, ftNs_SpecialLwHold_Phys,
      ftNs_SpecialLwHold_Coll, ftCamera_UpdateCameraBox },
    { 320, 0x00340014, 0x15000000, ftNs_SpecialLwHit_Anim,
      ftNs_SpecialLwHit_IASA, ftNs_SpecialLwHit_Phys, ftNs_SpecialLwHit_Coll,
      ftCamera_UpdateCameraBox },
    { 321, 0x00340014, 0x15000000, ftNs_SpecialLwEnd_Anim,
      ftNs_SpecialLwEnd_IASA, ftNs_SpecialLwEnd_Phys, ftNs_SpecialLwEnd_Coll,
      ftCamera_UpdateCameraBox },
    { 319, 0x00340014, 0x15000000, ftNs_SpecialLwTurn_Anim,
      ftNs_SpecialLwTurn_IASA, ftNs_SpecialLwTurn_Phys,
      ftNs_SpecialLwTurn_Coll, ftCamera_UpdateCameraBox },
    { 322, 0x00340414, 0x15000000, ftNs_SpecialAirLwStart_Anim,
      ftNs_SpecialAirLwStart_IASA, ftNs_SpecialAirLwStart_Phys,
      ftNs_SpecialAirLwStart_Coll, ftCamera_UpdateCameraBox },
    { 323, 0x003C0414, 0x15000000, ftNs_SpecialAirLwHold_Anim,
      ftNs_SpecialAirLwHold_IASA, ftNs_SpecialAirLwHold_Phys,
      ftNs_SpecialAirLwHold_Coll, ftCamera_UpdateCameraBox },
    { 324, 0x00340414, 0x15000000, ftNs_SpecialAirLwHit_Anim,
      ftNs_SpecialAirLwHit_IASA, ftNs_SpecialAirLwHit_Phys,
      ftNs_SpecialAirLwHit_Coll, ftCamera_UpdateCameraBox },
    { 325, 0x00340414, 0x15000000, ftNs_SpecialAirLwEnd_Anim,
      ftNs_SpecialAirLwEnd_IASA, ftNs_SpecialAirLwEnd_Phys,
      ftNs_SpecialAirLwEnd_Coll, ftCamera_UpdateCameraBox },
    { 323, 0x00340414, 0x15000000, ftNs_SpecialAirLwTurn_Anim,
      ftNs_SpecialAirLwTurn_IASA, ftNs_SpecialAirLwTurn_Phys,
      ftNs_SpecialAirLwTurn_Coll, ftCamera_UpdateCameraBox },
};

char ftNs_Init_DatFilename[] = "PlNs.dat";
char ftNs_Init_DataName[] = "ftDataNess";
char ftNs_Init_803CCAE8[] = "PlNsNr.dat";
char ftNs_Init_803CCAF4[] = "PlyNess5K_Share_joint";
char ftNs_Init_803CCB0C[] = "PlyNess5K_Share_matanim_joint";
char ftNs_Init_803CCB2C[] = "PlNsYe.dat";
char ftNs_Init_803CCB38[] = "PlyNess5KYe_Share_joint";
char ftNs_Init_803CCB50[] = "PlyNess5KYe_Share_matanim_joint";
char ftNs_Init_803CCB70[] = "PlNsBu.dat";
char ftNs_Init_803CCB7C[] = "PlyNess5KBu_Share_joint";
char ftNs_Init_803CCB94[] = "PlyNess5KBu_Share_matanim_joint";
char ftNs_Init_803CCBB4[] = "PlNsGr.dat";
char ftNs_Init_803CCBC0[] = "PlyNess5KGr_Share_joint";
char ftNs_Init_803CCBD8[] = "PlyNess5KGr_Share_matanim_joint";
char ftNs_Init_AnimDatFilename[] = "PlNsAJ.dat";

Fighter_DemoStrings ftNs_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileNess",
    "ftDemoIntroMotionFileNess",
    "ftDemoEndingMotionFileNess",
    "ftDemoViWaitMotionFileNess",
};

Fighter_CostumeStrings ftNs_Init_CostumeStrings[] = {
    { ftNs_Init_803CCAE8, ftNs_Init_803CCAF4, ftNs_Init_803CCB0C },
    { ftNs_Init_803CCB2C, ftNs_Init_803CCB38, ftNs_Init_803CCB50 },
    { ftNs_Init_803CCB70, ftNs_Init_803CCB7C, ftNs_Init_803CCB94 },
    { ftNs_Init_803CCBB4, ftNs_Init_803CCBC0, ftNs_Init_803CCBD8 },
};

void ftNs_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftParts_80074A4C(gobj, 0, 0);
    fp->ev.ns.x2240_flashGObj = NULL;
    fp->ev.ns.x2244_pkThunderGObj = NULL;
    fp->ev.ns.x2248_baseballBatGObj = NULL;
    fp->ev.ns.x222C_yoyoGObj = NULL;
    fp->ev.ns.x224C_thunderGFX = false;
}

void ftNs_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    void** item_list = fp->x10C_ftData->x48_items;

    PUSH_ATTRS(fp, ftNessAttributes);

    it_8026B3F8(item_list[0], It_Kind_Ness_PKFire);
    it_8026B3F8(item_list[1], It_Kind_Ness_PKFire_Flame);
    it_8026B3F8(item_list[2], It_Kind_Ness_PKFlush);
    it_8026B3F8(item_list[8], It_Kind_Ness_PKFlush_Explode);
    it_8026B3F8(item_list[3], It_Kind_Ness_PKThunder);
    it_8026B3F8(item_list[4], It_Kind_Ness_PKThunder1);
    it_8026B3F8(item_list[5], It_Kind_Ness_PKThunder2);
    it_8026B3F8(item_list[6], It_Kind_Ness_PKThunder3);
    it_8026B3F8(item_list[7], It_Kind_Ness_PKThunder4);
    it_8026B3F8(item_list[9], It_Kind_Ness_Bat);
    it_8026B3F8(item_list[10], It_Kind_Ness_Yoyo);
}

void ftNs_Init_OnDamage(HSD_GObj* gobj)
{
    ftNs_AttackHi4_YoyoItemDespawn(gobj);
    ftNs_SpecialN_ItemPKFlushSetNULL(gobj);
    ftNs_SpecialHi_TakeDamage(gobj);
    ftNs_AttackS4_ItemNessBatRemove(gobj);
}

void ftNs_Init_OnAbsorb(HSD_GObj* gobj)
{
    ftNs_AbsorbThink_DecideAction(gobj);
}

f32 ftNs_Init_GetAbsorbHeal(Fighter* fp)
{
    return ((ftNessAttributes*) fp->x2D4_specialAttributes)
        ->x94_PSI_MAGNET_HEAL_MUL;
}

void ftNs_Init_OnItemPickup(HSD_GObj* gobj, bool catchItemFlag)
{
    Fighter_OnItemPickup(gobj, catchItemFlag, 1, 1);
}

void ftNs_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftNs_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftNs_Init_OnItemDrop(HSD_GObj* gobj, bool dropItemFlag)
{
    Fighter_OnItemDrop(gobj, dropItemFlag, 1, 1);
}

void ftNs_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftNessAttributes);
}

void ftNs_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftNs_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}
