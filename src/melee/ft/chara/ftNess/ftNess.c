#include "ftNess/ftNess.h"

#include "ft/forward.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftNess/ftNess_SpecialLw.h"

ActionState as_table_ness[] = {
    { 62, 0x00241A09, 0x0A000000, ftNess_AttackS4_Anim, ftNess_AttackS4_IASA,
      ftNess_AttackS4_Phys, ftNess_AttackS4_Coll, func_800761C8 },
    { 66, 0x00240A0A, 0x0B800000, ftNess_AttackHi4_Anim, ftNess_AttackHi4_IASA,
      ftNess_AttackHi4_Phys, ftNess_AttackHi4_Coll, func_800761C8 },
    { 295, 0x0024080A, 0x0B000000, ftNess_AttackHi4_Charge_Anim,
      ftNess_AttackHi4_Charge_IASA, ftNess_AttackHi4_Charge_Phys,
      ftNess_AttackHi4_Charge_Coll, func_800761C8 },
    { 296, 0x0024080A, 0x0B000000, ftNess_AttackHi4_Release_Anim,
      ftNess_AttackHi4_Release_IASA, ftNess_AttackHi4_Release_Phys,
      ftNess_AttackHi4_Release_Coll, func_800761C8 },
    { 67, 0x00240A0B, 0x0C800000, ftNess_AttackLw4_Anim, ftNess_AttackLw4_IASA,
      ftNess_AttackLw4_Phys, ftNess_AttackLw4_Coll, func_800761C8 },
    { 297, 0x0024080B, 0x0C000000, ftNess_AttackLw4_Charge_Anim,
      ftNess_AttackLw4_Charge_IASA, ftNess_AttackLw4_Charge_Phys,
      ftNess_AttackLw4_Charge_Coll, func_800761C8 },
    { 298, 0x0024080B, 0x0C000000, ftNess_AttackLw4_Release_Anim,
      ftNess_AttackLw4_Release_IASA, ftNess_AttackLw4_Release_Phys,
      ftNess_AttackLw4_Release_Coll, func_800761C8 },
    { 299, 0x00340111, 0x12000000, ftNess_SpecialNStart_Anim,
      ftNess_SpecialNStart_IASA, ftNess_SpecialNStart_Phys,
      ftNess_SpecialNStart_Coll, func_800761C8 },
    { 300, 0x00340111, 0x12000000, ftNess_SpecialNHold_Anim,
      ftNess_SpecialNHold_IASA, ftNess_SpecialNHold_Phys,
      ftNess_SpecialNHold_Coll, func_800761C8 },
    { 301, 0x00340111, 0x12000000, ftNess_SpecialNHold_Anim,
      ftNess_SpecialNHold_IASA, ftNess_SpecialNHold_Phys,
      ftNess_SpecialNHold_Coll, func_800761C8 },
    { 302, 0x00340111, 0x12000000, ftNess_SpecialNEnd_Anim,
      ftNess_SpecialNEnd_IASA, ftNess_SpecialNEnd_Phys,
      ftNess_SpecialNEnd_Coll, func_800761C8 },
    { 303, 0x00340511, 0x12000000, ftNess_SpecialAirNStart_Anim,
      ftNess_SpecialAirNStart_IASA, ftNess_SpecialAirNStart_Phys,
      ftNess_SpecialAirNStart_Coll, func_800761C8 },
    { 304, 0x00340511, 0x12000000, ftNess_SpecialAirNHold_Anim,
      ftNess_SpecialAirNHold_IASA, ftNess_SpecialAirNHold_Phys,
      ftNess_SpecialAirNHold_Coll, func_800761C8 },
    { 305, 0x00340511, 0x12000000, ftNess_SpecialAirNHold_Anim,
      ftNess_SpecialAirNHold_IASA, ftNess_SpecialAirNHold_Phys,
      ftNess_SpecialAirNHold_Coll, func_800761C8 },
    { 306, 0x00340511, 0x12000000, ftNess_SpecialAirNEnd_Anim,
      ftNess_SpecialAirNEnd_IASA, ftNess_SpecialAirNEnd_Phys,
      ftNess_SpecialAirNEnd_Coll, func_800761C8 },
    { 307, 0x00340112, 0x13000000, ftNess_SpecialS_Anim, NULL,
      ftNess_SpecialS_Phys, ftNess_SpecialS_Coll, func_800761C8 },
    { 308, 0x00340512, 0x13000000, ftNess_SpecialAirS_Anim, NULL,
      ftNess_SpecialAirS_Phys, ftNess_SpecialAirS_Coll, func_800761C8 },
    { 309, 0x00340113, 0x14000000, ftNess_SpecialHiStart_Anim,
      ftNess_SpecialHiStart_IASA, ftNess_SpecialHiStart_Phys,
      ftNess_SpecialHiStart_Coll, func_800761C8 },
    { 310, 0x00340113, 0x14000000, ftNess_SpecialHiHold_Anim,
      ftNess_SpecialHiHold_IASA, ftNess_SpecialHiHold_Phys,
      ftNess_SpecialHiHold_Coll, func_800761C8 },
    { 311, 0x00340113, 0x14000000, ftNess_SpecialHiEnd_Anim,
      ftNess_SpecialHiEnd_IASA, ftNess_SpecialHiEnd_Phys,
      ftNess_SpecialHiEnd_Coll, func_800761C8 },
    { 312, 0x00340113, 0x14000000, ftNess_SpecialHi_Anim,
      ftNess_SpecialHi_IASA, ftNess_SpecialHi_Phys, ftNess_SpecialHi_Coll,
      func_800761C8 },
    { 313, 0x00340513, 0x14000000, ftNess_SpecialAirHiStart_Anim,
      ftNess_SpecialAirHiStart_IASA, ftNess_SpecialAirHiStart_Phys,
      ftNess_SpecialAirHiStart_Coll, func_800761C8 },
    { 314, 0x00340513, 0x14000000, ftNess_SpecialAirHiHold_Anim,
      ftNess_SpecialAirHiHold_IASA, ftNess_SpecialAirHiHold_Phys,
      ftNess_SpecialAirHiHold_Coll, func_800761C8 },
    { 315, 0x00340513, 0x14000000, ftNess_SpecialAirHiEnd_Anim,
      ftNess_SpecialAirHiEnd_IASA, ftNess_SpecialAirHiEnd_Phys,
      ftNess_SpecialAirHiEnd_Coll, func_800761C8 },
    { 316, 0x00340513, 0x14000000, ftNess_SpecialAirHi_Anim,
      ftNess_SpecialAirHi_IASA, ftNess_SpecialAirHi_Phys,
      ftNess_SpecialAirHi_Coll, func_800761C8 },
    { 317, 0x00340113, 0x14000000, ftNess_SpecialAirHiRebound_Anim,
      ftNess_SpecialAirHiRebound_IASA, ftNess_SpecialAirHiRebound_Phys,
      ftNess_SpecialAirHiRebound_Coll, func_800761C8 },
    { 318, 0x00340014, 0x15000000, ftNess_SpecialLwStart_Anim,
      ftNess_SpecialLwStart_IASA, ftNess_SpecialLwStart_Phys,
      ftNess_SpecialLwStart_Coll, func_800761C8 },
    { 319, 0x003C0014, 0x15000000, ftNess_SpecialLwHold_Anim,
      ftNess_SpecialLwHold_IASA, ftNess_SpecialLwHold_Phys,
      ftNess_SpecialLwHold_Coll, func_800761C8 },
    { 320, 0x00340014, 0x15000000, ftNess_SpecialLwHit_Anim,
      ftNess_SpecialLwHit_IASA, ftNess_SpecialLwHit_Phys,
      ftNess_SpecialLwHit_Coll, func_800761C8 },
    { 321, 0x00340014, 0x15000000, ftNess_SpecialLwEnd_Anim,
      ftNess_SpecialLwEnd_IASA, ftNess_SpecialLwEnd_Phys,
      ftNess_SpecialLwEnd_Coll, func_800761C8 },
    { 319, 0x00340014, 0x15000000, ftNess_SpecialLwTurn_Anim,
      ftNess_SpecialLwTurn_IASA, ftNess_SpecialLwTurn_Phys,
      ftNess_SpecialLwTurn_Coll, func_800761C8 },
    { 322, 0x00340414, 0x15000000, ftNess_SpecialAirLwStart_Anim,
      ftNess_SpecialAirLwStart_IASA, ftNess_SpecialAirLwStart_Phys,
      ftNess_SpecialAirLwStart_Coll, func_800761C8 },
    { 323, 0x003C0414, 0x15000000, ftNess_SpecialAirLwHold_Anim,
      ftNess_SpecialAirLwHold_IASA, ftNess_SpecialAirLwHold_Phys,
      ftNess_SpecialAirLwHold_Coll, func_800761C8 },
    { 324, 0x00340414, 0x15000000, ftNess_SpecialAirLwHit_Anim,
      ftNess_SpecialAirLwHit_IASA, ftNess_SpecialAirLwHit_Phys,
      ftNess_SpecialAirLwHit_Coll, func_800761C8 },
    { 325, 0x00340414, 0x15000000, ftNess_SpecialAirLwEnd_Anim,
      ftNess_SpecialAirLwEnd_IASA, ftNess_SpecialAirLwEnd_Phys,
      ftNess_SpecialAirLwEnd_Coll, func_800761C8 },
    { 323, 0x00340414, 0x15000000, ftNess_SpecialAirLwTurn_Anim,
      ftNess_SpecialAirLwTurn_IASA, ftNess_SpecialAirLwTurn_Phys,
      ftNess_SpecialAirLwTurn_Coll, func_800761C8 },
};

char lbl_803CCAD0[] = "PlNs.dat";
char lbl_803CCADC[] = "ftDataNess";
char lbl_803CCAE8[] = "PlNsNr.dat";
char lbl_803CCAF4[] = "PlyNess5K_Share_joint";
char lbl_803CCB0C[] = "PlyNess5K_Share_matanim_joint";
char lbl_803CCB2C[] = "PlNsYe.dat";
char lbl_803CCB38[] = "PlyNess5KYe_Share_joint";
char lbl_803CCB50[] = "PlyNess5KYe_Share_matanim_joint";
char lbl_803CCB70[] = "PlNsBu.dat";
char lbl_803CCB7C[] = "PlyNess5KBu_Share_joint";
char lbl_803CCB94[] = "PlyNess5KBu_Share_matanim_joint";
char lbl_803CCBB4[] = "PlNsGr.dat";
char lbl_803CCBC0[] = "PlyNess5KGr_Share_joint";
char lbl_803CCBD8[] = "PlyNess5KGr_Share_matanim_joint";
char lbl_803CCBF8[] = "PlNsAJ.dat";

Fighter_DemoStrings lbl_803CCC74 = {
    "ftDemoResultMotionFileNess",
    "ftDemoIntroMotionFileNess",
    "ftDemoEndingMotionFileNess",
    "ftDemoViWaitMotionFileNess",
};

Fighter_CostumeStrings lbl_803CCC84[] = {
    { lbl_803CCAE8, lbl_803CCAF4, lbl_803CCB0C },
    { lbl_803CCB2C, lbl_803CCB38, lbl_803CCB50 },
    { lbl_803CCB70, lbl_803CCB7C, lbl_803CCB94 },
    { lbl_803CCBB4, lbl_803CCBC0, lbl_803CCBD8 },
};

void ftNess_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    fp->fv.ns.x2240_flashGObj = NULL;
    fp->fv.ns.x2244_pkThunderGObj = NULL;
    fp->fv.ns.x2248_baseballBatGObj = NULL;
    fp->fv.ns.x222C_yoyoGObj = NULL;
    fp->fv.ns.x224C_thunderGFX = false;
}

void ftNess_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    void** item_list = fp->x10C_ftData->x48_items;

    PUSH_ATTRS(fp, ftNessAttributes);

    func_8026B3F8(item_list[0], It_Kind_Ness_PKFire);
    func_8026B3F8(item_list[1], It_Kind_Ness_PKFire_Flame);
    func_8026B3F8(item_list[2], It_Kind_Ness_PKFlush);
    func_8026B3F8(item_list[8], It_Kind_Ness_PKFlush_Explode);
    func_8026B3F8(item_list[3], It_Kind_Ness_PKThunder);
    func_8026B3F8(item_list[4], It_Kind_Ness_PKThunder1);
    func_8026B3F8(item_list[5], It_Kind_Ness_PKThunder2);
    func_8026B3F8(item_list[6], It_Kind_Ness_PKThunder3);
    func_8026B3F8(item_list[7], It_Kind_Ness_PKThunder4);
    func_8026B3F8(item_list[9], It_Kind_Ness_Bat);
    func_8026B3F8(item_list[10], It_Kind_Ness_Yoyo);
}

void ftNess_OnDamage(HSD_GObj* gobj)
{
    ftNess_YoyoItemDespawn(gobj);
    ftNess_ItemPKFlushSetNULL(gobj);
    ftNess_SpecialHiTakeDamage(gobj);
    ftNess_ItemNessBatRemove(gobj);
}

void ftNess_OnAbsorb(HSD_GObj* gobj)
{
    ftNess_AbsorbThink_DecideAction(gobj);
}

f32 ftNess_GetAbsorbHeal(Fighter* fp)
{
    return ((ftNessAttributes*) fp->x2D4_specialAttributes)
        ->x94_PSI_MAGNET_HEAL_MUL;
}

void ftNess_OnItemPickup(HSD_GObj* gobj, bool catchItemFlag)
{
    Fighter_OnItemPickup(gobj, catchItemFlag, 1, 1);
}

void ftNess_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftNess_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftNess_OnItemDrop(HSD_GObj* gobj, bool dropItemFlag)
{
    Fighter_OnItemDrop(gobj, dropItemFlag, 1, 1);
}

void ftNess_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftNessAttributes);
}

void ftNess_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftNess_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}
