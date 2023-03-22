#include "ftdrmario.h"

#include "ft/ft_unknown_006.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftMario/ftMario_Init.h"
#include "it/code_8027CF30.h"

MotionState ftDrMario_MotionStateTable[] = {
    { 239, 0x00000071, 0x01000000, ftDrMario_80149954, ftDrMario_80149A6C,
      ftDrMario_80149A8C, ftDrMario_80149AAC, Fighter_UpdateCameraBox },
    { 240, 0x00000071, 0x01000000, ftDrMario_80149954, ftDrMario_80149A6C,
      ftDrMario_80149A8C, ftDrMario_80149AAC, Fighter_UpdateCameraBox },
    { 295, 0x00340111, 0x12000000, ftMario_SpecialN_Anim,
      ftMario_SpecialN_IASA, ftMario_SpecialN_Phys, ftMario_SpecialN_Coll,
      Fighter_UpdateCameraBox },
    { 296, 0x00340511, 0x12000000, ftMario_SpecialAirN_Anim,
      ftMario_SpecialAirN_IASA, ftMario_SpecialAirN_Phys,
      ftMario_SpecialAirN_Coll, Fighter_UpdateCameraBox },
    { 297, 0x00341012, 0x13000000, ftMario_SpecialS_Anim,
      ftMario_SpecialS_IASA, ftMario_SpecialS_Phys, ftMario_SpecialS_Coll,
      Fighter_UpdateCameraBox },
    { 298, 0x00341012, 0x13000000, ftMario_SpecialAirS_Anim,
      ftMario_SpecialAirS_IASA, ftMario_SpecialAirS_Phys,
      ftMario_SpecialAirS_Coll, Fighter_UpdateCameraBox },
    { 299, 0x00340213, 0x14000000, ftMario_SpecialHi_Anim,
      ftMario_SpecialHi_IASA, ftMario_SpecialHi_Phys, ftMario_SpecialHi_Coll,
      Fighter_UpdateCameraBox },
    { 300, 0x00340613, 0x14000000, ftMario_SpecialAirHi_Anim,
      ftMario_SpecialAirHi_IASA, ftMario_SpecialAirHi_Phys,
      ftMario_SpecialAirHi_Coll, Fighter_UpdateCameraBox },
    { 301, 0x00340214, 0x15000000, ftMario_SpecialLw_Anim,
      ftMario_SpecialLw_IASA, ftMario_SpecialLw_Phys, ftMario_SpecialLw_Coll,
      Fighter_UpdateCameraBox },
    { 302, 0x00340614, 0x15000000, ftMario_SpecialAirLw_Anim,
      ftMario_SpecialAirLw_IASA, ftMario_SpecialAirLw_Phys,
      ftMario_SpecialAirLw_Coll, Fighter_UpdateCameraBox },
};

char lbl_803D15D8[] = "PlDr.dat";
char lbl_803D15E4[] = "ftDataDrmario";
char lbl_803D15F4[] = "PlDrNr.dat";
char lbl_803D1600[] = "PlyDrmario5K_Share_joint";
char lbl_803D161C[] = "PlyDrmario5K_Share_matanim_joint";
char lbl_803D1640[] = "PlDrRe.dat";
char lbl_803D164C[] = "PlyDrmario5KRe_Share_joint";
char lbl_803D1668[] = "PlyDrmario5KRe_Share_matanim_joint";
char lbl_803D168C[] = "PlDrBu.dat";
char lbl_803D1698[] = "PlyDrmario5KBu_Share_joint";
char lbl_803D16B4[] = "PlyDrmario5KBu_Share_matanim_joint";
char lbl_803D16D8[] = "PlDrGr.dat";
char lbl_803D16E4[] = "PlyDrmario5KGr_Share_joint";
char lbl_803D1700[] = "PlyDrmario5KGr_Share_matanim_joint";
char lbl_803D1724[] = "PlDrBk.dat";
char lbl_803D1730[] = "PlyDrmario5KBk_Share_joint";
char lbl_803D174C[] = "PlyDrmario5KBk_Share_matanim_joint";
char lbl_803D1770[] = "PlDrAJ.dat";

Fighter_DemoStrings lbl_803D17FC = {
    "ftDemoResultMotionFileDrmario",
    "ftDemoIntroMotionFileDrmario",
    "ftDemoEndingMotionFileDrmario",
    "ftDemoViWaitMotionFileDrmario",
};

Fighter_CostumeStrings lbl_803D180C[] = {
    { lbl_803D15F4, lbl_803D1600, lbl_803D161C },
    { lbl_803D1640, lbl_803D164C, lbl_803D1668 },
    { lbl_803D168C, lbl_803D1698, lbl_803D16B4 },
    { lbl_803D16D8, lbl_803D16E4, lbl_803D1700 },
    { lbl_803D1724, lbl_803D1730, lbl_803D174C },
};

void ftDrMario_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = (Fighter*) gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    fp->fv.mr.x2234_tornadoCharge = 0;
    fp->fv.mr.x2238_isCapeBoost = false;
    fp->fv.mr.x223C_capeGObj = NULL;
    fp->fv.mr.x2240 = 0;
}

void ftDrMario_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp;
    void** items;
    ftDrMarioAttributes* sa;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp = gobj->user_data;
    items = fp->ft_data->x48_items;
    ftMario_OnLoadForDrMario(fp);
    sa = fp->x2D4_specialAttributes;
    func_8026B3F8(items[1], 0x31);
    func_8026B3F8(items[3], sa->x14);
}

void ftDrMario_80149540(HSD_GObj* gobj)
{
    ftDrMario_801497CC(gobj);
}

void ftDrMario_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftDrMario_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftDrMario_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftDrMario_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftDrMario_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftMario_LoadSpecialAttrs(gobj);
}

void ftDrMario_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftDrMario_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

void ftDrMario_801497CC(HSD_GObj* gobj)
{
    Fighter* fp;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (gobj != NULL) {
        fp = gobj->user_data;
        if (fp != NULL && fp->fv.mr.x2240 != 0) {
            func_802C0DBC(fp->fv.mr.x2240);
            fp->fv.mr.x2240 = 0;
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

bool ftDrMario_80149844(HSD_GObj* gobj)
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
    tmp = fp->motion_id;
    if (tmp != 0x155 && tmp != 0x156) {
        return true;
    }
    if (fp->fv.mr.x2240 == 0) {
        return true;
    }
    return false;
}

void ftDrMario_801498A0(HSD_GObj* gobj)
{
    Fighter* fp;

    if (gobj != NULL) {
        fp = gobj->user_data;
        if (fp != NULL && fp->fv.mr.x2240 != 0) {
            fp->fv.mr.x2240 = 0;
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

u32 ftDrMario_801498EC(HSD_GObj* gobj)
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

void ftDrMario_80149910(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    func_800DEAE8(gobj, 0x155, 0x156);
    fp->x2200_ftcmd_var0 = 1;
    fp->x2204_ftcmd_var1 = 0;
}
