#include <melee/ft/chara/ftMewtwo/ftmewtwo.h>

#include <melee/ft/chara/ftMewtwo/ftmewtwo.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/types.h>
#include <melee/it/itkind.h>

ActionState ftMewtwo_MotionStateTable[] = {
    { 295, 0x00340111, 0x12000000, ftMewtwo_SpecialNStart_Anim,
      ftMewtwo_SpecialNStart_IASA, ftMewtwo_SpecialNStart_Phys,
      ftMewtwo_SpecialNStart_Coll, ftCamera_UpdateCameraBox },
    { 296, 0x003C0111, 0x12000000, ftMewtwo_SpecialNLoop_Anim,
      ftMewtwo_SpecialNLoop_IASA, ftMewtwo_SpecialNLoop_Phys,
      ftMewtwo_SpecialNLoop_Coll, ftCamera_UpdateCameraBox },
    { 297, 0x003C0111, 0x12000000, ftMewtwo_SpecialNFull_Anim,
      ftMewtwo_SpecialNFull_IASA, ftMewtwo_SpecialNFull_Phys,
      ftMewtwo_SpecialNFull_Coll, ftCamera_UpdateCameraBox },
    { 298, 0x00340111, 0x12000000, ftMewtwo_SpecialNCancel_Anim,
      ftMewtwo_SpecialNCancel_IASA, ftMewtwo_SpecialNCancel_Phys,
      ftMewtwo_SpecialNCancel_Coll, ftCamera_UpdateCameraBox },
    { 299, 0x00340111, 0x12000000, ftMewtwo_SpecialNEnd_Anim,
      ftMewtwo_SpecialNEnd_IASA, ftMewtwo_SpecialNEnd_Phys,
      ftMewtwo_SpecialNEnd_Coll, ftCamera_UpdateCameraBox },
    { 300, 0x00340511, 0x12000000, ftMewtwo_SpecialAirNStart_Anim,
      ftMewtwo_SpecialAirNStart_IASA, ftMewtwo_SpecialAirNStart_Phys,
      ftMewtwo_SpecialAirNStart_Coll, ftCamera_UpdateCameraBox },
    { 301, 0x003C0511, 0x12000000, ftMewtwo_SpecialAirNLoop_Anim,
      ftMewtwo_SpecialAirNLoop_IASA, ftMewtwo_SpecialAirNLoop_Phys,
      ftMewtwo_SpecialAirNLoop_Coll, ftCamera_UpdateCameraBox },
    { 302, 0x003C0511, 0x12000000, ftMewtwo_SpecialAirNFull_Anim,
      ftMewtwo_SpecialAirNFull_IASA, ftMewtwo_SpecialAirNFull_Phys,
      ftMewtwo_SpecialAirNFull_Coll, ftCamera_UpdateCameraBox },
    { 303, 0x00340511, 0x12000000, ftMewtwo_SpecialAirNCancel_Anim,
      ftMewtwo_SpecialAirNCancel_IASA, ftMewtwo_SpecialAirNCancel_Phys,
      ftMewtwo_SpecialAirNCancel_Coll, ftCamera_UpdateCameraBox },
    { 304, 0x00340511, 0x12000000, ftMewtwo_SpecialAirNEnd_Anim,
      ftMewtwo_SpecialAirNEnd_IASA, ftMewtwo_SpecialAirNEnd_Phys,
      ftMewtwo_SpecialAirNEnd_Coll, ftCamera_UpdateCameraBox },
    { 305, 0x00341012, 0x13000000, ftMewtwo_SpecialS_Anim,
      ftMewtwo_SpecialS_IASA, ftMewtwo_SpecialS_Phys, ftMewtwo_SpecialS_Coll,
      ftCamera_UpdateCameraBox },
    { 306, 0x00341412, 0x13000000, ftMewtwo_SpecialAirS_Anim,
      ftMewtwo_SpecialAirS_IASA, ftMewtwo_SpecialAirS_Phys,
      ftMewtwo_SpecialAirS_Coll, ftCamera_UpdateCameraBox },
    { 307, 0x00340013, 0x14000000, ftMewtwo_SpecialHiStart_Anim,
      ftMewtwo_SpecialHiStart_IASA, ftMewtwo_SpecialHiStart_Phys,
      ftMewtwo_SpecialHiStart_Coll, ftCamera_UpdateCameraBox },
    { 309, 0x00340013, 0x14000000, ftMewtwo_SpecialHi_Anim,
      ftMewtwo_SpecialHi_IASA, ftMewtwo_SpecialHi_Phys, ftMewtwo_SpecialHi_Coll,
      ftCamera_UpdateCameraBox },
    { 308, 0x00340013, 0x14000000, ftMewtwo_SpecialHiLost_Anim,
      ftMewtwo_SpecialHiLost_IASA, ftMewtwo_SpecialHiLost_Phys,
      ftMewtwo_SpecialHiLost_Coll, ftCamera_UpdateCameraBox },
    { 310, 0x00340413, 0x14000000, ftMewtwo_SpecialAirHiStart_Anim,
      ftMewtwo_SpecialAirHiStart_IASA, ftMewtwo_SpecialAirHiStart_Phys,
      ftMewtwo_SpecialAirHiStart_Coll, ftCamera_UpdateCameraBox },
    { 309, 0x00340413, 0x14000000, ftMewtwo_SpecialAirHi_Anim,
      ftMewtwo_SpecialAirHi_IASA, ftMewtwo_SpecialAirHi_Phys,
      ftMewtwo_SpecialAirHi_Coll, ftCamera_UpdateCameraBox },
    { 311, 0x00340413, 0x14000000, ftMewtwo_SpecialAirHiLost_Anim,
      ftMewtwo_SpecialAirHiLost_IASA, ftMewtwo_SpecialAirHiLost_Phys,
      ftMewtwo_SpecialAirHiLost_Coll, ftCamera_UpdateCameraBox },
    { 312, 0x00340114, 0x15000000, ftMewtwo_SpecialLw_Anim,
      ftMewtwo_SpecialLw_IASA, ftMewtwo_SpecialLw_Phys, ftMewtwo_SpecialLw_Coll,
      ftCamera_UpdateCameraBox },
    { 313, 0x00340514, 0x15000000, ftMewtwo_SpecialAirLw_Anim,
      ftMewtwo_SpecialAirLw_IASA, ftMewtwo_SpecialAirLw_Phys,
      ftMewtwo_SpecialAirLw_Coll, ftCamera_UpdateCameraBox },
};

char lbl_803D0D80[] = "PlMt.dat";
char lbl_803D0D8C[] = "ftDataMewtwo";
char lbl_803D0D9C[] = "PlMtNr.dat";
char lbl_803D0DA8[] = "PlyMewtwo5K_Share_joint";
char lbl_803D0DC0[] = "PlyMewtwo5K_Share_matanim_joint";
char lbl_803D0DE0[] = "PlMtRe.dat";
char lbl_803D0DEC[] = "PlyMewtwo5KRe_Share_joint";
char lbl_803D0E08[] = "PlyMewtwo5KRe_Share_matanim_joint";
char lbl_803D0E2C[] = "PlMtBu.dat";
char lbl_803D0E38[] = "PlyMewtwo5KBu_Share_joint";
char lbl_803D0E54[] = "PlyMewtwo5KBu_Share_matanim_joint";
char lbl_803D0E78[] = "PlMtGr.dat";
char lbl_803D0E84[] = "PlyMewtwo5KGr_Share_joint";
char lbl_803D0EA0[] = "PlyMewtwo5KGr_Share_matanim_joint";
char lbl_803D0EC4[] = "PlMtAJ.dat";

Fighter_DemoStrings lbl_803D0F4C = {
    "ftDemoResultMotionFileMewtwo",
    "ftDemoIntroMotionFileMewtwo",
    "ftDemoEndingMotionFileMewtwo",
    "ftDemoViWaitMotionFileMewtwo",
};

Fighter_CostumeStrings lbl_803D0F5C[] = {
    { lbl_803D0D9C, lbl_803D0DA8, lbl_803D0DC0 },
    { lbl_803D0DE0, lbl_803D0DEC, lbl_803D0E08 },
    { lbl_803D0E2C, lbl_803D0E38, lbl_803D0E54 },
    { lbl_803D0E78, lbl_803D0E84, lbl_803D0EA0 },
};

void ftMewtwo_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = (Fighter*) gobj->user_data;
    ftParts_80074A4C(gobj, 0, 0);
    fp->ev.mt.x222C_disableGObj = NULL;
    fp->ev.mt.x2230_shadowHeldGObj = NULL;
    fp->ev.mt.x2234_shadowBallCharge = 0;
    fp->ev.mt.x2238_shadowBallGObj = NULL;
    fp->ev.mt.x223C_isConfusionBoost = false;
}

void ftMewtwo_OnLoad(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    void** item_list = fp->x10C_ftData->x48_items;

    PUSH_ATTRS(fp, ftMewtwoAttributes);

    {
        fp->x5E8_fighterBones[1].flags.bits.b4 = 1;
        fp->x2221_flag.bits.b2 = 1;
    }
    it_8026B3F8(item_list[0], It_Kind_Mewtwo_Disable);
    it_8026B3F8(item_list[1], It_Kind_Mewtwo_ShadowBall);
}

void ftMewTwo_OnItemPickup(HSD_GObj* fighter_gobj, bool bool)
{
    return;
}

void ftMewtwo_OnDeath2(HSD_GObj* fighter_gobj)
{
    ftMewtwo_SpecialLw_RemoveDisable(fighter_gobj);
    ftMewtwo_SpecialN_OnTakeDamage(fighter_gobj);
}

void ftMewtwo_OnTakeDamage(HSD_GObj* fighter_gobj)
{
    ftMewtwo_SpecialLw_RemoveDisable(fighter_gobj);
    ftMewtwo_SpecialN_OnDeath(fighter_gobj);
}

void ftMewTwo_OnItemDrop(HSD_GObj* fighter_gobj, bool bool) {}

void ftMewTwo_OnItemInvisible(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMewTwo_OnItemVisible(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMewTwo_80144F58(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftMewtwoAttributes* attr = fp->x2D4_specialAttributes;
    f32 attr_value = attr->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES;

    if (fp->ev.mt.x2234_shadowBallCharge == attr_value)
        ft_800BFFD0(fp, 0x5C, 0);
}

void ftMewTwo_LoadSpecialAttrs(HSD_GObj* fighter_gobj)
{
    COPY_ATTRS(fighter_gobj, ftMewtwoAttributes);
    if (fp->x34_scale.y != 1.0f) {
        sA2->x80_MEWTWO_DISABLE_OFFSET_X *= fp->x34_scale.y;
        sA2->x84_MEWTWO_DISABLE_OFFSET_Y *= fp->x34_scale.y;
    }
}

void ftMewTwo_OnKnockbackEnter(HSD_GObj* fighter_gobj)
{
    Fighter_OnKnockbackEnter(fighter_gobj, 2);
}

void ftMewTwo_OnKnockbackExit(HSD_GObj* fighter_gobj)
{
    Fighter_OnKnockbackExit(fighter_gobj, 2);
}
