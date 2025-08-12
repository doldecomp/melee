#include "ftLuigi/ftLg_Init.h"

#include "ftLg_SpecialHi.h"
#include "ftLg_SpecialLw.h"
#include "ftLg_SpecialN.h"
#include "ftLg_SpecialS.h"
#include "types.h"

#include "forward.h"

#include "ft/ft_0C31.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"
#include "it/forward.h"

#include "it/it_26B1.h"

MotionState ftLg_Init_MotionStateTable[ftLg_MS_SelfCount] = {
    {
        // ftLg_MS_SpecialN = 341
        ftLg_SM_SpecialN,
        ftLg_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftLg_SpecialN_Anim,
        ftLg_SpecialN_IASA,
        ftLg_SpecialN_Phys,
        ftLg_SpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLg_MS_SpecialAirN = 342
        ftLg_SM_SpecialAirN,
        ftLg_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftLg_SpecialAirN_Anim,
        ftLg_SpecialAirN_IASA,
        ftLg_SpecialAirN_Phys,
        ftLg_SpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLg_MS_SpecialSStart = 343
        ftLg_SM_SpecialSStart,
        ftLg_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftLg_SpecialSStart_Anim,
        ftLg_SpecialSStart_IASA,
        ftLg_SpecialSStart_Phys,
        ftLg_SpecialSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLg_MS_SpecialSHold = 344
        ftLg_SM_SpecialSHold,
        ftLg_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftLg_SpecialSHold_Anim,
        ftLg_SpecialSHold_IASA,
        ftLg_SpecialSHold_Phys,
        ftLg_SpecialSHold_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLg_MS_SpecialS2 = 345
        ftLg_SM_SpecialS2,
        ftLg_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftLg_SpecialS2_Anim,
        ftLg_SpecialS2_IASA,
        ftLg_SpecialS2_Phys,
        ftLg_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLg_MS_SpecialSEnd = 346
        ftLg_SM_SpecialSEnd,
        ftLg_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftLg_SpecialSEnd_Anim,
        ftLg_SpecialSEnd_IASA,
        ftLg_SpecialSEnd_Phys,
        ftLg_SpecialSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLg_MS_SpecialS = 347
        ftLg_SM_SpecialS,
        ftLg_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftLg_SpecialS_Anim,
        ftLg_SpecialS_IASA,
        ftLg_SpecialS_Phys,
        ftLg_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLg_MS_SpecialSMisfire = 348
        ftLg_SM_SpecialSMisfire,
        ftLg_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftLg_SpecialSMisfire_Anim,
        ftLg_SpecialSMisfire_IASA,
        ftLg_SpecialSMisfire_Phys,
        ftLg_SpecialSMisfire_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLg_MS_SpecialAirSStart = 349
        ftLg_SM_SpecialAirSStart,
        ftLg_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftLg_SpecialAirSStart_Anim,
        ftLg_SpecialAirSStart_IASA,
        ftLg_SpecialAirSStart_Phys,
        ftLg_SpecialAirSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLg_MS_SpecialAirSHold = 350
        ftLg_SM_SpecialAirSHold,
        ftLg_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftLg_SpecialAirSHold_Anim,
        ftLg_SpecialAirSHold_IASA,
        ftLg_SpecialAirSHold_Phys,
        ftLg_SpecialAirSHold_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLg_MS_SpecialAirS2 = 351
        ftLg_SM_SpecialS2,
        ftLg_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftLg_SpecialAirS2_Anim,
        ftLg_SpecialAirS2_IASA,
        ftLg_SpecialAirS2_Phys,
        ftLg_SpecialAirS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLg_MS_SpecialAirSEnd = 352
        ftLg_SM_SpecialAirSEnd,
        ftLg_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftLg_SpecialAirSEnd_Anim,
        ftLg_SpecialAirSEnd_IASA,
        ftLg_SpecialAirSEnd_Phys,
        ftLg_SpecialAirSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLg_MS_SpecialAirS = 353
        ftLg_SM_SpecialAirS,
        ftLg_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftLg_SpecialAirS_Anim,
        ftLg_SpecialAirS_IASA,
        ftLg_SpecialAirS_Phys,
        ftLg_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLg_MS_SpecialAirSMisfire = 354
        ftLg_SM_SpecialAirSMisfire,
        ftLg_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftLg_SpecialAirSMisfire_Anim,
        ftLg_SpecialAirSMisfire_IASA,
        ftLg_SpecialAirSMisfire_Phys,
        ftLg_SpecialAirSMisfire_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLg_MS_SpecialHi = 355
        ftLg_SM_SpecialHi,
        ftLg_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftLg_SpecialHi_Anim,
        ftLg_SpecialHi_IASA,
        ftLg_SpecialHi_Phys,
        ftLg_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLg_MS_SpecialAirHi = 356
        ftLg_SM_SpecialAirHi,
        ftLg_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftLg_SpecialAirHi_Anim,
        ftLg_SpecialAirHi_IASA,
        ftLg_SpecialAirHi_Phys,
        ftLg_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLg_MS_SpecialLw = 357
        ftLg_SM_SpecialLw,
        ftLg_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftLg_SpecialLw_Anim,
        ftLg_SpecialLw_IASA,
        ftLg_SpecialLw_Phys,
        ftLg_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLg_MS_SpecialAirLw = 358
        ftLg_SM_SpecialAirLw,
        ftLg_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftLg_SpecialAirLw_Anim,
        ftLg_SpecialAirLw_IASA,
        ftLg_SpecialAirLw_Phys,
        ftLg_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
};

MotionState ftLg_Init_UnkMotionStates0[] = {
    {
        ftCo_SM_RunBrake,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        ftCo_800C7158,
        NULL,
        NULL,
    },
    {
        ftCo_SM_Kneebend,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        ftCo_800C7200,
        NULL,
        NULL,
    },
};

char ftLg_Init_DatFilename[] = "PlLg.dat";
char ftLg_Init_DataName[] = "ftDataLuigi";
char ftLg_Init_803D08C0[] = "PlLgNr.dat";
char ftLg_Init_803D08CC[] = "PlyLuigi5K_Share_joint";
char ftLg_Init_803D08E4[] = "PlyLuigi5K_Share_matanim_joint";
char ftLg_Init_803D0904[] = "PlLgWh.dat";
char ftLg_Init_803D0910[] = "PlyLuigi5KWh_Share_joint";
char ftLg_Init_803D092C[] = "PlyLuigi5KWh_Share_matanim_joint";
char ftLg_Init_803D0950[] = "PlLgAq.dat";
char ftLg_Init_803D095C[] = "PlyLuigi5KAq_Share_joint";
char ftLg_Init_803D0978[] = "PlyLuigi5KAq_Share_matanim_joint";
char ftLg_Init_803D099C[] = "PlLgPi.dat";
char ftLg_Init_803D09A8[] = "PlyLuigi5KPi_Share_joint";
char ftLg_Init_803D09C4[] = "PlyLuigi5KPi_Share_matanim_joint";
char ftLg_Init_AnimDatFilename[] = "PlLgAJ.dat";

Fighter_DemoStrings ftLg_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileLuigi",
    "ftDemoIntroMotionFileLuigi",
    "ftDemoEndingMotionFileLuigi",
    "ftDemoViWaitMotionFileLuigi",
};

char* ftLg_Init_803D0AAC[] = {
    "ftDemoVi0102MotionFileLuigi",
    "ftDemoVi1101MotionFileLuigi",
};

Fighter_CostumeStrings ftLg_Init_CostumeStrings[] = {
    { ftLg_Init_803D08C0, ftLg_Init_803D08CC, ftLg_Init_803D08E4 },
    { ftLg_Init_803D0904, ftLg_Init_803D0910, ftLg_Init_803D092C },
    { ftLg_Init_803D0950, ftLg_Init_803D095C, ftLg_Init_803D0978 },
    { ftLg_Init_803D099C, ftLg_Init_803D09A8, ftLg_Init_803D09C4 },
};

void ftLg_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0, false);
    fp->fv.lg.x2234 = 0;
}

void ftLg_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void** item_list = fp->ft_data->x48_items;

    PUSH_ATTRS(fp, ftLuigiAttributes);

    it_8026B3F8(item_list[0], It_Kind_Luigi_Fire);
}

void ftLg_Init_OnItemPickup(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemPickup(gobj, flag, 1, 1);
}

void ftLg_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftLg_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftLg_Init_OnItemDrop(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemDrop(gobj, flag, 1, 1);
}

void ftLg_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftLuigiAttributes);
}

void ftLg_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftLg_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

void ftLg_Init_UnkDemoCallbacks0(int arg0, int* arg1, int* arg2)
{
    if (arg0 != 10) {
        if (arg0 < 10 && arg0 >= 9) {
            *arg2 = 14;
            *arg1 = 14;
        }
    } else {
        *arg2 = 15;
        *arg1 = 15;
    }
}

char* ftLg_Init_GetMotionFileString(enum_t arg0)
{
    int offset;

    switch (arg0) {
    case 9:
        offset = 14;
        break;
    case 10:
        offset = 15;
        break;
    }

    return ftLg_Init_803D0AAC[offset - 14];
}
