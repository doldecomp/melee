#include "ftdrmario.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftMario/ftmario.h"
#include "it/it_27CF.h"

MotionState ftDr_Init_MotionStateTable[] = {
    { 239, 0x00000071, 0x01000000, ftDr_Appeal_Anim, ftDr_Appeal_IASA,
      ftDr_Appeal_Phys, ftDr_Appeal_Coll, ftCamera_UpdateCameraBox },
    { 240, 0x00000071, 0x01000000, ftDr_Appeal_Anim, ftDr_Appeal_IASA,
      ftDr_Appeal_Phys, ftDr_Appeal_Coll, ftCamera_UpdateCameraBox },
    { 295, 0x00340111, 0x12000000, ftMr_SpecialN_Anim,
      ftMr_SpecialN_IASA, ftMr_SpecialN_Phys, ftMr_SpecialN_Coll,
      ftCamera_UpdateCameraBox },
    { 296, 0x00340511, 0x12000000, ftMr_SpecialAirN_Anim,
      ftMr_SpecialAirN_IASA, ftMr_SpecialAirN_Phys,
      ftMr_SpecialAirN_Coll, ftCamera_UpdateCameraBox },
    { 297, 0x00341012, 0x13000000, ftMr_SpecialS_Anim,
      ftMr_SpecialS_IASA, ftMr_SpecialS_Phys, ftMr_SpecialS_Coll,
      ftCamera_UpdateCameraBox },
    { 298, 0x00341012, 0x13000000, ftMr_SpecialAirS_Anim,
      ftMr_SpecialAirS_IASA, ftMr_SpecialAirS_Phys,
      ftMr_SpecialAirS_Coll, ftCamera_UpdateCameraBox },
    { 299, 0x00340213, 0x14000000, ftMr_SpecialHi_Anim,
      ftMr_SpecialHi_IASA, ftMr_SpecialHi_Phys, ftMr_SpecialHi_Coll,
      ftCamera_UpdateCameraBox },
    { 300, 0x00340613, 0x14000000, ftMr_SpecialAirHi_Anim,
      ftMr_SpecialAirHi_IASA, ftMr_SpecialAirHi_Phys,
      ftMr_SpecialAirHi_Coll, ftCamera_UpdateCameraBox },
    { 301, 0x00340214, 0x15000000, ftMr_SpecialLw_Anim,
      ftMr_SpecialLw_IASA, ftMr_SpecialLw_Phys, ftMr_SpecialLw_Coll,
      ftCamera_UpdateCameraBox },
    { 302, 0x00340614, 0x15000000, ftMr_SpecialAirLw_Anim,
      ftMr_SpecialAirLw_IASA, ftMr_SpecialAirLw_Phys,
      ftMr_SpecialAirLw_Coll, ftCamera_UpdateCameraBox },
};

char ftDr_Init_DatFilename[] = "PlDr.dat";
char ftDr_Init_DataName[] = "ftDataDrmario";
char ftDr_Init_803D15F4[] = "PlDrNr.dat";
char ftDr_Init_803D1600[] = "PlyDrmario5K_Share_joint";
char ftDr_Init_803D161C[] = "PlyDrmario5K_Share_matanim_joint";
char ftDr_Init_803D1640[] = "PlDrRe.dat";
char ftDr_Init_803D164C[] = "PlyDrmario5KRe_Share_joint";
char ftDr_Init_803D1668[] = "PlyDrmario5KRe_Share_matanim_joint";
char ftDr_Init_803D168C[] = "PlDrBu.dat";
char ftDr_Init_803D1698[] = "PlyDrmario5KBu_Share_joint";
char ftDr_Init_803D16B4[] = "PlyDrmario5KBu_Share_matanim_joint";
char ftDr_Init_803D16D8[] = "PlDrGr.dat";
char ftDr_Init_803D16E4[] = "PlyDrmario5KGr_Share_joint";
char ftDr_Init_803D1700[] = "PlyDrmario5KGr_Share_matanim_joint";
char ftDr_Init_803D1724[] = "PlDrBk.dat";
char ftDr_Init_803D1730[] = "PlyDrmario5KBk_Share_joint";
char ftDr_Init_803D174C[] = "PlyDrmario5KBk_Share_matanim_joint";
char ftDr_Init_AnimDatFilename[] = "PlDrAJ.dat";

Fighter_DemoStrings ftDr_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileDrmario",
    "ftDemoIntroMotionFileDrmario",
    "ftDemoEndingMotionFileDrmario",
    "ftDemoViWaitMotionFileDrmario",
};

Fighter_CostumeStrings ftDr_Init_CostumeStrings[] = {
    { ftDr_Init_803D15F4, ftDr_Init_803D1600, ftDr_Init_803D161C },
    { ftDr_Init_803D1640, ftDr_Init_803D164C, ftDr_Init_803D1668 },
    { ftDr_Init_803D168C, ftDr_Init_803D1698, ftDr_Init_803D16B4 },
    { ftDr_Init_803D16D8, ftDr_Init_803D16E4, ftDr_Init_803D1700 },
    { ftDr_Init_803D1724, ftDr_Init_803D1730, ftDr_Init_803D174C },
};

void ftDr_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = (Fighter*) gobj->user_data;
    ftParts_80074A4C(gobj, 0, 0);
    fp->ev.mr.x2234_tornadoCharge = 0;
    fp->ev.mr.x2238_isCapeBoost = false;
    fp->ev.mr.x223C_capeGObj = NULL;
    fp->ev.mr.x2240 = 0;
}

void ftDr_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp;
    void** items;
    ftDrMarioAttributes* sa;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp = gobj->user_data;
    items = fp->x10C_ftData->x48_items;
    ftMr_Init_OnLoadForDrMario(fp);
    sa = fp->x2D4_specialAttributes;
    it_8026B3F8(items[1], 0x31);
    it_8026B3F8(items[3], sa->x14);
}

void ftDr_Init_80149540(HSD_GObj* gobj)
{
    ftDr_Init_801497CC(gobj);
}

void ftDr_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftDr_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftDr_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftDr_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftDr_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftMr_Init_LoadSpecialAttrs(gobj);
}

void ftDr_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftDr_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

void ftDr_Init_801497CC(HSD_GObj* gobj)
{
    Fighter* fp;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (gobj != NULL) {
        fp = gobj->user_data;
        if (fp != NULL && fp->ev.mr.x2240 != 0) {
            it_802C0DBC(fp->ev.mr.x2240);
            fp->ev.mr.x2240 = 0;
        }
    }

    if (gobj != NULL) {
        fp = gobj->user_data;
        if (fp != NULL) {
            fp->cb.x21DC_callback_OnTakeDamage = 0;
            fp->cb.x21E4_callback_OnDeath2 = 0;
        }
    }
}

bool ftDr_Init_80149844(HSD_GObj* gobj)
{
    s32 tmp;
    Fighter* fp;

    if (gobj == NULL) {
        return true;
    }
    fp = gobj->user_data;
    if (fp == NULL) {
        return true;
    }
    tmp = fp->action_id;
    if (tmp != 0x155 && tmp != 0x156) {
        return true;
    }
    if (fp->ev.mr.x2240 == 0) {
        return true;
    }
    return false;
}

void ftDr_Init_801498A0(HSD_GObj* gobj)
{
    Fighter* fp;

    if (gobj != NULL) {
        fp = gobj->user_data;
        if (fp != NULL && fp->ev.mr.x2240 != 0) {
            fp->ev.mr.x2240 = 0;
        }
    }
    if (gobj != NULL) {
        fp = gobj->user_data;
        if (fp != NULL) {
            fp->cb.x21DC_callback_OnTakeDamage = 0;
            fp->cb.x21E4_callback_OnDeath2 = 0;
        }
    }
}

u32 ftDr_Init_801498EC(HSD_GObj* gobj)
{
    Fighter* fp;

    if (gobj != NULL) {
        fp = gobj->user_data;
        if (fp != NULL) {
            return fp->x2204_ftcmd_var1;
        }
    }

    return 0;
}

void ftDr_Init_80149910(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    ft_800DEAE8(gobj, 0x155, 0x156);
    fp->x2200_ftcmd_var0 = 1;
    fp->x2204_ftcmd_var1 = 0;
}
