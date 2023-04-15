#include "it/forward.h"

#include "ftgigakoopa.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftKoopa/ftkoopa.h"

MotionState ftGk_Init_MotionStateTable[] = {
    { 295, 0x00340011, 0x12000000, ftKp_Unk3_80134F48, ftKp_Unk3_801351B0,
      ftKp_Unk3_80135438, ftKp_Unk3_801354F8, ftCamera_UpdateCameraBox },
    { 296, 0x003C0011, 0x12000000, ftKp_Unk3_80134F9C, ftKp_Unk3_801351B4,
      ftKp_Unk3_80135458, ftKp_Unk3_80135564, ftCamera_UpdateCameraBox },
    { 297, 0x00340011, 0x12000000, ftKp_Unk3_80135040, ftKp_Unk3_801352F0,
      ftKp_Unk3_80135478, ftKp_Unk3_801355D0, ftCamera_UpdateCameraBox },
    { 298, 0x00340411, 0x12000000, ftKp_Unk3_8013507C, ftKp_Unk3_801352F4,
      ftKp_Unk3_80135498, ftKp_Unk3_8013563C, ftCamera_UpdateCameraBox },
    { 299, 0x003C0411, 0x12000000, ftKp_Unk3_801350D0, ftKp_Unk3_801352F8,
      ftKp_Unk3_801354B8, ftKp_Unk3_801356A8, ftCamera_UpdateCameraBox },
    { 300, 0x00340411, 0x12000000, ftKp_Unk3_80135174, ftKp_Unk3_80135434,
      ftKp_Unk3_801354D8, ftKp_Unk3_80135714, ftCamera_UpdateCameraBox },
    { 301, 0x00340012, 0x13000000, ftKp_Init_80133654, NULL,
      ftKp_Unk3_80134224, ftKp_Unk3_80134388, ftCamera_UpdateCameraBox },
    { 302, 0x00340012, 0x13000000, ftKp_Init_801336CC, ftKp_Unk3_80133BF4,
      ftKp_Unk3_80134288, ftKp_Unk3_801343D8, ftCamera_UpdateCameraBox },
    { 303, 0x00340012, 0x13000000, ftKp_Init_801336CC, ftKp_Unk3_80133BF4,
      ftKp_Unk3_80134288, ftKp_Unk3_801343D8, ftCamera_UpdateCameraBox },
    { -1, 0x00340012, 0x13000000, ftKp_Unk3_801339AC, ftKp_Unk3_80133E4C,
      ftKp_Unk3_801342C8, ftKp_Unk3_80134428, ftCamera_UpdateCameraBox },
    { 304, 0x00340012, 0x13000000, ftKp_Unk3_801339B4, NULL,
      ftKp_Unk3_80134308, ftKp_Unk3_80134478, ftCamera_UpdateCameraBox },
    { 305, 0x00340012, 0x13000000, ftKp_Unk3_80133A90, NULL,
      ftKp_Unk3_80134328, ftKp_Unk3_801344A0, ftCamera_UpdateCameraBox },
    { 306, 0x00340412, 0x13000000, ftKp_Init_80133690, NULL,
      ftKp_Unk3_80134244, ftKp_Unk3_801343B0, ftCamera_UpdateCameraBox },
    { 307, 0x00340412, 0x13000000, ftKp_Unk3_8013383C, ftKp_Unk3_80133D20,
      ftKp_Unk3_801342A8, ftKp_Unk3_80134400, ftCamera_UpdateCameraBox },
    { 308, 0x00340412, 0x13000000, ftKp_Unk3_8013383C, ftKp_Unk3_80133D20,
      ftKp_Unk3_801342A8, ftKp_Unk3_80134400, ftCamera_UpdateCameraBox },
    { -1, 0x00340012, 0x13000000, ftKp_Unk3_801339B0, ftKp_Unk3_80134038,
      ftKp_Unk3_801342E8, ftKp_Unk3_80134450, ftCamera_UpdateCameraBox },
    { 309, 0x00340412, 0x13000000, ftKp_Unk3_80133AD4, NULL,
      ftKp_Unk3_80134348, ftKp_Unk3_801344C8, ftCamera_UpdateCameraBox },
    { 310, 0x00340412, 0x13000000, ftKp_Unk3_80133BB0, NULL,
      ftKp_Unk3_80134368, ftKp_Unk3_801344F0, ftCamera_UpdateCameraBox },
    { 311, 0x00340213, 0x14000000, ftKp_Unk3_80135C08, ftKp_Unk3_80135D78,
      ftKp_Unk3_80135D80, ftKp_Unk3_80135E4C, ftCamera_UpdateCameraBox },
    { 312, 0x00340613, 0x14000000, ftKp_Unk3_80135C60, ftKp_Unk3_80135D7C,
      ftKp_Unk3_80135DE0, ftKp_Unk3_80135F6C, ftCamera_UpdateCameraBox },
    { 313, 0x00340214, 0x15000000, ftKp_Unk3_8013474C, NULL,
      ftKp_Unk3_801347C4, ftKp_Unk3_801348A0, ftCamera_UpdateCameraBox },
    { 314, 0x00340614, 0x15000000, ftKp_Unk3_80134788, NULL,
      ftKp_Unk3_80134804, ftKp_Unk3_801348C0, ftCamera_UpdateCameraBox },
    { 315, 0x00340214, 0x15000000, ftKp_Unk3_801349C4, NULL,
      ftKp_Unk3_80134A00, ftKp_Unk3_80134A20, ftCamera_UpdateCameraBox },
};

MotionState ftGk_Init_UnkMotionStates0[] = {
    { 14, 0, 0x01000000, NULL, NULL, ft_800C74AC, NULL, NULL },
};

char ftGk_Init_DatFilename[] = "PlGk.dat";
char ftGk_Init_DataName[] = "ftDataGkoopa";
char ftGk_Init_803D3904[] = "PlGkNr.dat";
char ftGk_Init_803D3910[] = "PlyGkoopa5K_Share_joint";
char ftGk_Init_803D3928[] = "PlyGkoopa5K_Share_matanim_joint";
char ftGk_Init_AnimDatFilename[] = "PlGkAJ.dat";

Fighter_DemoStrings ftGk_Init_DemoMotionFilenames = { 0 };

char* ftGk_Init_803D3984[] = { "ftDemoVi1201V2MotionFileGkoopa" };

Fighter_CostumeStrings ftGk_Init_CostumeStrings[] = {
    { ftGk_Init_803D3904, ftGk_Init_803D3910, ftGk_Init_803D3928 },
};

void ftGk_Init_OnDeath(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* koopaAttr = fp->x2D4_specialAttributes;

    ftParts_80074A4C(gobj, 0, 0);
    fp->dmg.x18B0 = koopaAttr->x0;
    fp->fv.gk.x222C = koopaAttr->x10;
    fp->fv.gk.x2230 = koopaAttr->x18;
}

void ftGk_Init_UnkMotionStates3(HSD_GObj* gobj)
{
    ftKp_Init_UnkMotionStates3(gobj);
}

void ftGk_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftData* ftdata = fp->ft_data;
    void** items = ftdata->x48_items;

    ftKp_OnLoadForGKoopa(fp);
    it_8026B3F8(items[0], It_Kind_Koopa_Flame);

    fp->x2226_flag.bits.b1 = true;
    fp->x222A_flag.bits.b0 = true;
}

void ftGk_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, true, true);
}

void ftGk_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, true);
}

void ftGk_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, true);
}

void ftGk_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, true, true);
}

void ftGk_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftKp_Init_LoadSpecialAttrs(gobj);
}

void ftGk_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, true);
}

void ftGk_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, true);
}

void ftGk_Init_UnkDemoCallbacks0(s32 arg0, s32* arg1, s32* arg2)
{
    if (arg0 == 0xF) {
        *arg2 = 0xE;
        *arg1 = 0xE;
    }
}

/// @warning UB warning: this function may use offset uninitialized
char* ftGk_Init_GetMotionFileString(enum_t arg0)
{
    int offset;

    switch (arg0) {
    case 15:
        offset = 14;
    }

    return ftGk_Init_803D3984[offset - 14];
}
