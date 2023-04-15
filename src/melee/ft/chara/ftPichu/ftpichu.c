#include "ftpichu.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftPikachu/ftpikachu.h"

MotionState ftPc_Init_MotionStateTable[] = {
    { 295, 0x00340111, 0x12000000, ftPk_SpecialN_80124908,
      ftPk_SpecialN_80124B6C, ftPk_SpecialN_80124B74,
      ftPk_SpecialN_ChangeMotion_Unk0, ftCamera_UpdateCameraBox },
    { 296, 0x00340511, 0x12000000, ftPk_SpecialN_80124A20,
      ftPk_SpecialN_80124B70, ftPk_SpecialN_80124B94,
      ftPk_SpecialN_ChangeMotion_Unk1, ftCamera_UpdateCameraBox },
    { 297, 0x00340212, 0x13000000, ftPk_SpecialS_80124F64,
      ftPk_SpecialS_80124FDC, ftPk_SpecialS_80124FE4, ftPk_SpecialS_80125084,
      ftCamera_UpdateCameraBox },
    { 298, 0x00340212, 0x13000000, ftPk_SpecialS_801251BC,
      ftPk_SpecialS_801252FC, ftPk_SpecialS_8012535C, ftPk_SpecialS_8012539C,
      ftCamera_UpdateCameraBox },
    { 300, 0x00340212, 0x13000000, ftPk_SpecialS_8012590C,
      ftPk_SpecialS_8012594C, ftPk_SpecialS_80125954, ftPk_SpecialS_801259D4,
      ftCamera_UpdateCameraBox },
    { 301, 0x00340212, 0x13000000, ftPk_SpecialS_80125B34,
      ftPk_SpecialS_80125BAC, ftPk_SpecialS_80125BB4, ftPk_SpecialS_80125C44,
      ftCamera_UpdateCameraBox },
    { 299, 0x00340212, 0x13000000, ftPk_SpecialS_8012557C,
      ftPk_SpecialS_801256B4, ftPk_SpecialS_801256BC, ftPk_SpecialS_801256FC,
      ftCamera_UpdateCameraBox },
    { 302, 0x00340612, 0x13000000, ftPk_SpecialS_80124FA0,
      ftPk_SpecialS_80124FE0, ftPk_SpecialS_80125024, ftPk_SpecialS_801250C0,
      ftCamera_UpdateCameraBox },
    { 303, 0x00340612, 0x13000000, ftPk_SpecialS_8012525C,
      ftPk_SpecialS_8012532C, ftPk_SpecialS_8012537C, ftPk_SpecialS_801253D8,
      ftCamera_UpdateCameraBox },
    { 300, 0x00340612, 0x13000000, ftPk_SpecialS_80125910,
      ftPk_SpecialS_80125950, ftPk_SpecialS_80125958, ftPk_SpecialS_801259D8,
      ftCamera_UpdateCameraBox },
    { 305, 0x00340612, 0x13000000, ftPk_SpecialS_80125B70,
      ftPk_SpecialS_80125BB0, ftPk_SpecialS_80125BF4, ftPk_SpecialS_80125C80,
      ftCamera_UpdateCameraBox },
    { 304, 0x00340612, 0x13000000, ftPk_SpecialS_8012561C,
      ftPk_SpecialS_801256B8, ftPk_SpecialS_801256DC, ftPk_SpecialS_80125738,
      ftCamera_UpdateCameraBox },
    { 306, 0x00340113, 0x14000000, ftPk_SpecialHi_80125ED8,
      ftPk_SpecialHi_80125F50, ftPk_SpecialHi_80125F58,
      ftPk_SpecialHi_80125FD8, ftCamera_UpdateCameraBox },
    { 307, 0x00340113, 0x14000000, ftPk_SpecialHi_80126144,
      ftPk_SpecialHi_80126424, ftPk_SpecialHi_801265D4,
      ftPk_SpecialHi_80126614, ftCamera_UpdateCameraBox },
    { 308, 0x00340113, 0x14000000, ftPk_SpecialHi_80127198,
      ftPk_SpecialHi_801272D8, ftPk_SpecialHi_801272E0,
      ftPk_SpecialHi_8012738C, ftCamera_UpdateCameraBox },
    { 309, 0x00340513, 0x14000000, ftPk_SpecialHi_80125F14,
      ftPk_SpecialHi_80125F54, ftPk_SpecialHi_80125F78,
      ftPk_SpecialHi_80126014, ftCamera_UpdateCameraBox },
    { 310, 0x00340513, 0x14000000, ftPk_SpecialHi_801262B4,
      ftPk_SpecialHi_80126428, ftPk_SpecialHi_801265F4,
      ftPk_SpecialHi_801267C8, ftCamera_UpdateCameraBox },
    { 311, 0x00340513, 0x14000000, ftPk_SpecialHi_80127228,
      ftPk_SpecialHi_801272DC, ftPk_SpecialHi_80127310,
      ftPk_SpecialHi_801273D4, ftCamera_UpdateCameraBox },
    { 312, 0x00340014, 0x15000000, ftPk_SpecialLw_ChangeMotion_Unk08, NULL,
      ftPk_SpecialLw_801280C8, ftPk_SpecialLw_PrepCallMotionChange_Unk0,
      ftCamera_UpdateCameraBox },
    { 313, 0x00340014, 0x15000000, ftPk_SpecialLw_ChangeMotion_Unk10, NULL,
      ftPk_SpecialLw_80128108, ftPk_SpecialLw_PrepCallMotionChange_Unk2,
      ftCamera_UpdateCameraBox },
    { 314, 0x00340014, 0x15000000, ftPk_SpecialLw_ChangeMotion_Unk12, NULL,
      ftPk_SpecialLw_80128148, ftPk_SpecialLw_PrepCallMotionChange_Unk4,
      ftCamera_UpdateCameraBox },
    { 315, 0x00340014, 0x15000000, ftPk_SpecialLw_80128050, NULL,
      ftPk_SpecialLw_801281AC, ftPk_SpecialLw_PrepCallMotionChange_Unk6,
      ftCamera_UpdateCameraBox },
    { 316, 0x00340414, 0x15000000, ftPk_SpecialLw_ChangeMotion_Unk09, NULL,
      ftPk_SpecialLw_801280E8, ftPk_SpecialLw_PrepCallMotionChange_Unk1,
      ftCamera_UpdateCameraBox },
    { 317, 0x00340414, 0x15000000, ftPk_SpecialLw_ChangeMotion_Unk11, NULL,
      ftPk_SpecialLw_80128128, ftPk_SpecialLw_PrepCallMotionChange_Unk3,
      ftCamera_UpdateCameraBox },
    { 318, 0x00340414, 0x15000000, ftPk_SpecialLw_ChangeMotion_Unk13, NULL,
      ftPk_SpecialLw_80128168, ftPk_SpecialLw_PrepCallMotionChange_Unk5,
      ftCamera_UpdateCameraBox },
    { 319, 0x00340414, 0x15000000, ftPk_SpecialLw_8012808C, NULL,
      ftPk_SpecialLw_801281CC, ftPk_SpecialLw_PrepCallMotionChange_Unk7,
      ftCamera_UpdateCameraBox },
};

char ftPc_Init_DatFilename[] = "PlPc.dat";
char ftPc_Init_DataName[] = "ftDataPichu";
char ftPc_Init_803D2200[] = "PlPcNr.dat";
char ftPc_Init_803D220C[] = "PlyPichu5K_Share_joint";
char ftPc_Init_803D2224[] = "PlyPichu5K_Share_matanim_joint";
char ftPc_Init_803D2244[] = "PlPcRe.dat";
char ftPc_Init_803D2250[] = "PlyPichu5KRe_Share_joint";
char ftPc_Init_803D226C[] = "PlyPichu5KRe_Share_matanim_joint";
char ftPc_Init_803D2290[] = "PlPcBu.dat";
char ftPc_Init_803D229C[] = "PlyPichu5KBu_Share_joint";
char ftPc_Init_803D22B8[] = "PlyPichu5KBu_Share_matanim_joint";
char ftPc_Init_803D22DC[] = "PlPcGr.dat";
char ftPc_Init_803D22E8[] = "PlyPichu5KGr_Share_joint";
char ftPc_Init_803D2304[] = "PlyPichu5KGr_Share_matanim_joint";
char ftPc_Init_AnimDatFilename[] = "PlPcAJ.dat";

Fighter_DemoStrings ftPc_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFilePichu",
    "ftDemoIntroMotionFilePichu",
    "ftDemoEndingMotionFilePichu",
    "ftDemoViWaitMotionFilePichu",
};

Fighter_CostumeStrings ftPc_Init_CostumeStrings[] = {
    { ftPc_Init_803D2200, ftPc_Init_803D220C, ftPc_Init_803D2224 },
    { ftPc_Init_803D2244, ftPc_Init_803D2250, ftPc_Init_803D226C },
    { ftPc_Init_803D2290, ftPc_Init_803D229C, ftPc_Init_803D22B8 },
    { ftPc_Init_803D22DC, ftPc_Init_803D22E8, ftPc_Init_803D2304 },
};

void ftPc_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftData* ftdata = fp->ft_data;
    void** items = ftdata->x48_items;
    fp->x2224_flag.bits.b7 = true;
    ftPk_Init_OnLoadForPichu(fp);

    {
        ftPichuAttributes* attrs = fp->x2D4_specialAttributes;
        it_8026B3F8(items[0], attrs->xDC);
        it_8026B3F8(items[1], attrs->x14);
        it_8026B3F8(items[2], attrs->x18);
    }
}

void ftPc_Init_OnDeath(HSD_GObj* gobj)
{
    u8 temp_r0;
    Fighter* fp = gobj->user_data;

    ftParts_80074A4C(gobj, 0, 0);
    temp_r0 = fp->x619_costume_id;

    switch (temp_r0) {
    case 0:
        ftParts_80074A4C(gobj, 1, -1);
        ftParts_80074A4C(gobj, 2, -1);
        ftParts_80074A4C(gobj, 3, -1);
        break;
    case 1:
        ftParts_80074A4C(gobj, 1, 0);
        ftParts_80074A4C(gobj, 2, -1);
        ftParts_80074A4C(gobj, 3, -1);
        break;
    case 2:
        ftParts_80074A4C(gobj, 1, -1);
        ftParts_80074A4C(gobj, 2, 0);
        ftParts_80074A4C(gobj, 3, -1);
        break;
    case 3:
        ftParts_80074A4C(gobj, 1, -1);
        ftParts_80074A4C(gobj, 2, -1);
        ftParts_80074A4C(gobj, 3, 0);
        break;
    }
}

void ftPc_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 0, 0);
}

void ftPc_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 0);
}

void ftPc_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

void ftPc_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 0, 0);
}

void ftPc_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftPk_Init_LoadSpecialAttrs(gobj);
}

void ftPc_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftPc_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}
