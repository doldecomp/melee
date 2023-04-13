#include "ftgigakoopa.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftKoopa/ftkoopa.h"

ActionState ftGigaKoopa_MotionStateTable[] = {
    { 295, 0x00340011, 0x12000000, ftKoopa_80134F48, ftKoopa_801351B0,
      ftKoopa_80135438, ftKoopa_801354F8, ftCamera_UpdateCameraBox },
    { 296, 0x003C0011, 0x12000000, ftKoopa_80134F9C, ftKoopa_801351B4,
      ftKoopa_80135458, ftKoopa_80135564, ftCamera_UpdateCameraBox },
    { 297, 0x00340011, 0x12000000, ftKoopa_80135040, ftKoopa_801352F0,
      ftKoopa_80135478, ftKoopa_801355D0, ftCamera_UpdateCameraBox },
    { 298, 0x00340411, 0x12000000, ftKoopa_8013507C, ftKoopa_801352F4,
      ftKoopa_80135498, ftKoopa_8013563C, ftCamera_UpdateCameraBox },
    { 299, 0x003C0411, 0x12000000, ftKoopa_801350D0, ftKoopa_801352F8,
      ftKoopa_801354B8, ftKoopa_801356A8, ftCamera_UpdateCameraBox },
    { 300, 0x00340411, 0x12000000, ftKoopa_80135174, ftKoopa_80135434,
      ftKoopa_801354D8, ftKoopa_80135714, ftCamera_UpdateCameraBox },
    { 301, 0x00340012, 0x13000000, ftKoopa_80133654, NULL, ftKoopa_80134224,
      ftKoopa_80134388, ftCamera_UpdateCameraBox },
    { 302, 0x00340012, 0x13000000, ftKoopa_801336CC, ftKoopa_80133BF4,
      ftKoopa_80134288, ftKoopa_801343D8, ftCamera_UpdateCameraBox },
    { 303, 0x00340012, 0x13000000, ftKoopa_801336CC, ftKoopa_80133BF4,
      ftKoopa_80134288, ftKoopa_801343D8, ftCamera_UpdateCameraBox },
    { -1, 0x00340012, 0x13000000, ftKoopa_801339AC, ftKoopa_80133E4C,
      ftKoopa_801342C8, ftKoopa_80134428, ftCamera_UpdateCameraBox },
    { 304, 0x00340012, 0x13000000, ftKoopa_801339B4, NULL, ftKoopa_80134308,
      ftKoopa_80134478, ftCamera_UpdateCameraBox },
    { 305, 0x00340012, 0x13000000, ftKoopa_80133A90, NULL, ftKoopa_80134328,
      ftKoopa_801344A0, ftCamera_UpdateCameraBox },
    { 306, 0x00340412, 0x13000000, ftKoopa_80133690, NULL, ftKoopa_80134244,
      ftKoopa_801343B0, ftCamera_UpdateCameraBox },
    { 307, 0x00340412, 0x13000000, ftKoopa_8013383C, ftKoopa_80133D20,
      ftKoopa_801342A8, ftKoopa_80134400, ftCamera_UpdateCameraBox },
    { 308, 0x00340412, 0x13000000, ftKoopa_8013383C, ftKoopa_80133D20,
      ftKoopa_801342A8, ftKoopa_80134400, ftCamera_UpdateCameraBox },
    { -1, 0x00340012, 0x13000000, ftKoopa_801339B0, ftKoopa_80134038,
      ftKoopa_801342E8, ftKoopa_80134450, ftCamera_UpdateCameraBox },
    { 309, 0x00340412, 0x13000000, ftKoopa_80133AD4, NULL, ftKoopa_80134348,
      ftKoopa_801344C8, ftCamera_UpdateCameraBox },
    { 310, 0x00340412, 0x13000000, ftKoopa_80133BB0, NULL, ftKoopa_80134368,
      ftKoopa_801344F0, ftCamera_UpdateCameraBox },
    { 311, 0x00340213, 0x14000000, ftKoopa_80135C08, ftKoopa_80135D78,
      ftKoopa_80135D80, ftKoopa_80135E4C, ftCamera_UpdateCameraBox },
    { 312, 0x00340613, 0x14000000, ftKoopa_80135C60, ftKoopa_80135D7C,
      ftKoopa_80135DE0, ftKoopa_80135F6C, ftCamera_UpdateCameraBox },
    { 313, 0x00340214, 0x15000000, ftKoopa_8013474C, NULL, ftKoopa_801347C4,
      ftKoopa_801348A0, ftCamera_UpdateCameraBox },
    { 314, 0x00340614, 0x15000000, ftKoopa_80134788, NULL, ftKoopa_80134804,
      ftKoopa_801348C0, ftCamera_UpdateCameraBox },
    { 315, 0x00340214, 0x15000000, ftKoopa_801349C4, NULL, ftKoopa_80134A00,
      ftKoopa_80134A20, ftCamera_UpdateCameraBox },
};

ActionState lbl_803D38C8[] = {
    { 14, 0, 0x01000000, NULL, NULL, ft_800C74AC, NULL, NULL },
};

char lbl_803D38E8[] = "PlGk.dat";
char lbl_803D38F4[] = "ftDataGkoopa";
char lbl_803D3904[] = "PlGkNr.dat";
char lbl_803D3910[] = "PlyGkoopa5K_Share_joint";
char lbl_803D3928[] = "PlyGkoopa5K_Share_matanim_joint";
char lbl_803D3948[] = "PlGkAJ.dat";

Fighter_DemoStrings lbl_803D3954 = { 0 };

char* lbl_803D3984[] = { "ftDemoVi1201V2MotionFileGkoopa" };

Fighter_CostumeStrings lbl_803D3988[] = {
    { lbl_803D3904, lbl_803D3910, lbl_803D3928 },
};

void ftGigaKoopa_OnDeath(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* koopaAttr = fp->x2D4_specialAttributes;

    ftParts_80074A4C(gobj, 0, 0);
    fp->dmg.x18B0 = koopaAttr->x0;
    fp->ev.gk.x222C = koopaAttr->x10;
    fp->ev.gk.x2230 = koopaAttr->x18;
}

void ftGigaKoopa_8014F698(HSD_GObj* gobj)
{
    ftKoopa_80132A64(gobj);
}

void ftGigaKoopa_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftData* ftdata = fp->x10C_ftData;
    void** items = ftdata->x48_items;

    ftKoopa_OnLoadForGKoopa(fp);
    it_8026B3F8(items[0], It_Kind_Koopa_Flame);

    fp->x2226_flag.bits.b1 = true;
    fp->x222A_flag.bits.b0 = true;
}

void ftGigaKoopa_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, true, true);
}

void ftGigaKoopa_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, true);
}

void ftGigaKoopa_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, true);
}

void ftGigaKoopa_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, true, true);
}

void ftGigaKoopa_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftKoopa_LoadSpecialAttrs(gobj);
}

void ftGigaKoopa_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, true);
}

void ftGigaKoopa_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, true);
}

void ftGigaKoopa_8014F98C(s32 arg0, s32* arg1, s32* arg2)
{
    if (arg0 == 0xF) {
        *arg2 = 0xE;
        *arg1 = 0xE;
    }
}

/// @remarks UB warning: this function may use offset uninitialized
unk_t ftGigaKoopa_GetMotionFileString(enum_t arg0)
{
    int offset;

    switch (arg0) {
    case 15:
        offset = 14;
    }

    return lbl_803D3984[offset - 14];
}
