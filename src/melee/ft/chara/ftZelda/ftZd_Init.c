#include "ftZd_Init.h"

#include "ftZd_SpecialHi.h"
#include "ftZd_SpecialLw.h"
#include "ftZd_SpecialN.h"
#include "ftZd_SpecialS.h"

#include "forward.h"

#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftZelda/types.h"
#include "it/it_26B1.h"

MotionState ftZd_Init_MotionStateTable[ftZd_MS_SelfCount] = {
    {
        // ftZd_MS_SpecialN = 341
        ftZd_SM_SpecialN,
        ftZd_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftZd_SpecialN_Anim,
        ftZd_SpecialN_IASA,
        ftZd_SpecialN_Phys,
        ftZd_SpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftZd_MS_SpecialAirN = 342
        ftZd_SM_SpecialAirN,
        ftZd_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftZd_SpecialAirN_Anim,
        ftZd_SpecialAirN_IASA,
        ftZd_SpecialAirN_Phys,
        ftZd_SpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftZd_MS_SpecialSStart = 343
        ftZd_SM_SpecialSStart,
        ftZd_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftZd_SpecialSStart_Anim,
        ftZd_SpecialSStart_IASA,
        ftZd_SpecialSStart_Phys,
        ftZd_SpecialSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftZd_MS_SpecialSLoop = 344
        ftZd_SM_SpecialSLoop,
        ftZd_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftZd_SpecialSLoop_Anim,
        ftZd_SpecialSLoop_IASA,
        ftZd_SpecialSLoop_Phys,
        ftZd_SpecialSLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftZd_MS_SpecialSEnd = 345
        ftZd_SM_SpecialSEnd,
        ftZd_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftZd_SpecialSEnd_Anim,
        ftZd_SpecialSEnd_IASA,
        ftZd_SpecialSEnd_Phys,
        ftZd_SpecialSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftZd_MS_SpecialAirSStart = 346
        ftZd_SM_SpecialAirSStart,
        ftZd_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftZd_SpecialAirSStart_Anim,
        ftZd_SpecialAirSStart_IASA,
        ftZd_SpecialAirSStart_Phys,
        ftZd_SpecialAirSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftZd_MS_SpecialAirSLoop = 347
        ftZd_SM_SpecialAirSLoop,
        ftZd_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftZd_SpecialAirSLoop_Anim,
        ftZd_SpecialAirSLoop_IASA,
        ftZd_SpecialAirSLoop_Phys,
        ftZd_SpecialAirSLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftZd_MS_SpecialAirSEnd = 348
        ftZd_SM_SpecialAirSEnd,
        ftZd_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftZd_SpecialAirSEnd_Anim,
        ftZd_SpecialAirSEnd_IASA,
        ftZd_SpecialAirSEnd_Phys,
        ftZd_SpecialAirSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftZd_MS_SpecialHiStart_0 = 349
        ftZd_SM_SpecialHiStart,
        ftZd_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftZd_SpecialHiStart_0_Anim,
        ftZd_SpecialHiStart_0_IASA,
        ftZd_SpecialHiStart_0_Phys,
        ftZd_SpecialHiStart_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftZd_MS_SpecialHiStart_1 = 350
        ftZd_SM_SpecialHiStart,
        ftZd_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftZd_SpecialHiStart_1_Anim,
        ftZd_SpecialHiStart_1_IASA,
        ftZd_SpecialHiStart_1_Phys,
        ftZd_SpecialHiStart_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftZd_MS_SpecialHi = 351
        ftZd_SM_SpecialHi,
        ftZd_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftZd_SpecialHi_Anim,
        ftZd_SpecialHi_IASA,
        ftZd_SpecialHi_Phys,
        ftZd_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftZd_MS_SpecialAirHiStart_0 = 352
        ftZd_SM_SpecialAirHiStart,
        ftZd_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftZd_SpecialAirHiStart_0_Anim,
        ftZd_SpecialAirHiStart_0_IASA,
        ftZd_SpecialAirHiStart_0_Phys,
        ftZd_SpecialAirHiStart_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftZd_MS_SpecialAirHiStart_1 = 353
        ftZd_SM_SpecialAirHiStart,
        ftZd_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftZd_SpecialAirHiStart_1_Anim,
        ftZd_SpecialAirHiStart_1_IASA,
        ftZd_SpecialAirHiStart_1_Phys,
        ftZd_SpecialAirHiStart_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftZd_MS_SpecialAirHi = 354
        ftZd_SM_SpecialAirHi,
        ftZd_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftZd_SpecialAirHi_Anim,
        ftZd_SpecialAirHi_IASA,
        ftZd_SpecialAirHi_Phys,
        ftZd_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftZd_MS_SpecialLw = 355
        ftZd_SM_SpecialLw,
        ftZd_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftZd_SpecialLw_Anim,
        ftZd_SpecialLw_IASA,
        ftZd_SpecialLw_Phys,
        ftZd_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftZd_MS_SpecialLw2 = 356
        ftZd_SM_SpecialLw2,
        ftZd_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftZd_SpecialLw2_Anim,
        ftZd_SpecialLw2_IASA,
        ftZd_SpecialLw2_Phys,
        ftZd_SpecialLw2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftZd_MS_SpecialAirLw = 357
        ftZd_SM_SpecialAirLw,
        ftZd_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftZd_SpecialAirLw_Anim,
        ftZd_SpecialAirLw_IASA,
        ftZd_SpecialAirLw_Phys,
        ftZd_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftZd_MS_SpecialAirLw2 = 358
        ftZd_SM_SpecialAirLw2,
        ftZd_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftZd_SpecialAirLw2_Anim,
        ftZd_SpecialAirLw2_IASA,
        ftZd_SpecialAirLw2_Phys,
        ftZd_SpecialAirLw2_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftZd_Init_DatFilename[] = "PlZd.dat";
char ftZd_Init_DataName[] = "ftDataZelda";
char ftZd_Init_803CFCB0[] = "PlZdNr.dat";
char ftZd_Init_803CFCBC[] = "PlyZelda5K_Share_joint";
char ftZd_Init_803CFCD4[] = "PlyZelda5K_Share_matanim_joint";
char ftZd_Init_803CFCF4[] = "PlZdRe.dat";
char ftZd_Init_803CFD00[] = "PlyZelda5KRe_Share_joint";
char ftZd_Init_803CFD1C[] = "PlyZelda5KRe_Share_matanim_joint";
char ftZd_Init_803CFD40[] = "PlZdBu.dat";
char ftZd_Init_803CFD4C[] = "PlyZelda5KBu_Share_joint";
char ftZd_Init_803CFD68[] = "PlyZelda5KBu_Share_matanim_joint";
char ftZd_Init_803CFD8C[] = "PlZdGr.dat";
char ftZd_Init_803CFD98[] = "PlyZelda5KGr_Share_joint";
char ftZd_Init_803CFDB4[] = "PlyZelda5KGr_Share_matanim_joint";
char ftZd_Init_803CFDD8[] = "PlZdWh.dat";
char ftZd_Init_803CFDE4[] = "PlyZelda5KWh_Share_joint";
char ftZd_Init_803CFE00[] = "PlyZelda5KWh_Share_matanim_joint";
char ftZd_Init_AnimDatFilename[] = "PlZdAJ.dat";

Fighter_DemoStrings ftZd_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileZelda",
    "ftDemoIntroMotionFileZelda",
    "ftDemoEndingMotionFileZelda",
    "ftDemoViWaitMotionFileZelda",
};

Fighter_CostumeStrings ftZd_Init_CostumeStrings[] = {
    { ftZd_Init_803CFCB0, ftZd_Init_803CFCBC, ftZd_Init_803CFCD4 },
    { ftZd_Init_803CFCF4, ftZd_Init_803CFD00, ftZd_Init_803CFD1C },
    { ftZd_Init_803CFD40, ftZd_Init_803CFD4C, ftZd_Init_803CFD68 },
    { ftZd_Init_803CFD8C, ftZd_Init_803CFD98, ftZd_Init_803CFDB4 },
    { ftZd_Init_803CFDD8, ftZd_Init_803CFDE4, ftZd_Init_803CFE00 },
};

void ftZd_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 1, 0);
    fp->fv.zd.x222C = 0;
}

void ftZd_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void** item_list = fp->ft_data->x48_items;

    PUSH_ATTRS(fp, ftZelda_DatAttrs);

    it_8026B3F8(item_list[0], 108);
    it_8026B3F8(item_list[1], 109);
}

void ftZd_Init_801393AC(HSD_GObj* gobj)
{
    ftZd_SpecialLw_8013B5EC(gobj);
}

void ftZd_Init_OnItemPickup(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemPickup(gobj, flag, 1, 1);
}

void ftZd_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftZd_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftZd_Init_OnItemDrop(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemDrop(gobj, flag, 1, 1);
}

void ftZd_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftZelda_DatAttrs);
}

/// Zelda_RemoveDress
void ftZd_Init_801395C8(HSD_GObj* gobj)
{
    u8 _[8];

    int result = ftParts_80074A74(gobj, 1);
    if (result == -1) {
        ftParts_80074A4C(gobj, 1, 0);
    } else {
        ftParts_80074A4C(gobj, 1, -1);
    }
}

void ftZd_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftZd_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}
