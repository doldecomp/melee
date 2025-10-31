#include "ftGk_Init.h"

#include "ft/ft_0C31.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"
#include "ftKoopa/forward.h"

#include "ftKoopa/ftKp_Init.h"
#include "ftKoopa/ftKp_SpecialN.h"
#include "ftKoopa/ftKp_SpecialLw.h"
#include "ftKoopa/ftKp_SpecialHi.h"
#include "ftKoopa/types.h"

#include "it/forward.h"

#include "it/it_26B1.h"

#include <common_structs.h>

MotionState ftGk_Init_MotionStateTable[ftKp_MS_SelfCount] = {
    {
        // ftKp_MS_SpecialNStart = 341
        ftKp_SM_SpecialNStart,
        ftKp_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftKp_SpecialNStart_Anim,
        ftKp_SpecialNStart_IASA,
        ftKp_SpecialNStart_Phys,
        ftKp_SpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialN = 342
        ftKp_SM_SpecialN,
        ftKp_MF_SpecialNLoop,
        FtMoveId_SpecialN << 24,
        ftKp_SpecialN_Anim,
        ftKp_SpecialN_IASA,
        ftKp_SpecialN_Phys,
        ftKp_SpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialNEnd = 343
        ftKp_SM_SpecialNEnd,
        ftKp_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftKp_SpecialNEnd_Anim,
        ftKp_SpecialNEnd_IASA,
        ftKp_SpecialNEnd_Phys,
        ftKp_SpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialAirNStart = 344
        ftKp_SM_SpecialAirNStart,
        ftKp_MF_SpecialNStart,
        FtMoveId_SpecialN << 24,
        ftKp_SpecialAirNStart_Anim,
        ftKp_SpecialAirNStart_IASA,
        ftKp_SpecialAirNStart_Phys,
        ftKp_SpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialAirN = 345
        ftKp_SM_SpecialAirN,
        ftKp_MF_SpecialAirNLoop,
        FtMoveId_SpecialN << 24,
        ftKp_SpecialAirN_Anim,
        ftKp_SpecialAirN_IASA,
        ftKp_SpecialAirN_Phys,
        ftKp_SpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialAirNEnd = 346
        ftKp_SM_SpecialAirNEnd,
        ftKp_MF_SpecialNStart,
        FtMoveId_SpecialN << 24,
        ftKp_SpecialAirNEnd_Anim,
        ftKp_SpecialAirNEnd_IASA,
        ftKp_SpecialAirNEnd_Phys,
        ftKp_SpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialSStart = 347
        ftKp_SM_SpecialSStart,
        ftKp_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialSStart_Anim,
        NULL,
        ftKp_SpecialSStart_Phys,
        ftKp_SpecialSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialSHit0_0 = 348
        ftKp_SM_SpecialSHit0,
        ftKp_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialSHit_Anim,
        ftKp_SpecialSHit_IASA,
        ftKp_SpecialSHit_Phys,
        ftKp_SpecialSHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialSHit1 = 349
        ftKp_SM_SpecialSHit1,
        ftKp_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialSHit_Anim,
        ftKp_SpecialSHit_IASA,
        ftKp_SpecialSHit_Phys,
        ftKp_SpecialSHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialSHit0_1 = 350
        ftCo_SM_None,
        ftKp_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialSWait_Anim,
        ftKp_SpecialSWait_IASA,
        ftKp_SpecialSWait_Phys,
        ftKp_SpecialSWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialSEndF = 351
        ftKp_SM_SpecialSEndF,
        ftKp_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialSEndF_Anim,
        NULL,
        ftKp_SpecialSEndF_Phys,
        ftKp_SpecialSEndF_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialSEndB = 352
        ftKp_SM_SpecialSEndB,
        ftKp_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialSEndB_Anim,
        NULL,
        ftKp_SpecialSEndB_Phys,
        ftKp_SpecialSEndB_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialAirSStart = 353
        ftKp_SM_SpecialAirSStart,
        ftKp_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialAirSStart_Anim,
        NULL,
        ftKp_SpecialAirSStart_Phys,
        ftKp_SpecialAirSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialAirSHit0_0 = 354
        ftKp_SM_SpecialAirSHit0,
        ftKp_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialAirSHit_Anim,
        ftKp_SpecialAirSHit_IASA,
        ftKp_SpecialAirSHit_Phys,
        ftKp_SpecialAirSHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialAirSHit1 = 355
        ftKp_SM_SpecialAirSHit1,
        ftKp_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialAirSHit_Anim,
        ftKp_SpecialAirSHit_IASA,
        ftKp_SpecialAirSHit_Phys,
        ftKp_SpecialAirSHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialAirSHit0_1 = 356
        ftCo_SM_None,
        ftKp_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialAirSWait_Anim,
        ftKp_SpecialAirSWait_IASA,
        ftKp_SpecialAirSWait_Phys,
        ftKp_SpecialAirSWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialAirSEndF = 357
        ftKp_SM_SpecialAirSEndF,
        ftKp_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialAirSEndF_Anim,
        NULL,
        ftKp_SpecialAirSEndF_Phys,
        ftKp_SpecialAirSEndF_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialAirSEndB = 358
        ftKp_SM_SpecialAirSEndB,
        ftKp_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialAirSEndB_Anim,
        NULL,
        ftKp_SpecialAirSEndB_Phys,
        ftKp_SpecialAirSEndB_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialHi = 359
        ftKp_SM_SpecialHi,
        ftKp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftKp_SpecialHi_Anim,
        ftKp_SpecialHi_IASA,
        ftKp_SpecialHi_Phys,
        ftKp_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialAirHi = 360
        ftKp_SM_SpecialAirHi,
        ftKp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftKp_SpecialAirHi_Anim,
        ftKp_SpecialAirHi_IASA,
        ftKp_SpecialAirHi_Phys,
        ftKp_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialLw = 361
        ftKp_SM_SpecialLw,
        ftKp_MF_SpecialLwStart,
        FtMoveId_SpecialLw << 24,
        ftKp_SpecialLw_Anim,
        NULL,
        ftKp_SpecialLw_Phys,
        ftKp_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialAirLw = 362
        ftKp_SM_SpecialAirLw,
        ftKp_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftKp_SpecialAirLw_Anim,
        NULL,
        ftKp_SpecialAirLw_Phys,
        ftKp_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKp_MS_SpecialLwLanding = 363
        ftKp_SM_SpecialLwLanding,
        ftKp_MF_SpecialLwStart,
        FtMoveId_SpecialLw << 24,
        ftKp_SpecialLwLanding_Anim,
        NULL,
        ftKp_SpecialLwLanding_Phys,
        ftKp_SpecialLwLanding_Coll,
        ftCamera_UpdateCameraBox,
    },
};

MotionState ftGk_Init_UnkMotionStates0[] = {
    {
        ftCo_SM_RunBrake,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        ftCo_800C74AC,
        NULL,
        NULL,
    },
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
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* koopaAttr = fp->dat_attrs;

    ftParts_80074A4C(gobj, 0, 0);
    fp->dmg.armor0 = koopaAttr->x0;
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

    ftKp_Init_OnLoadForGKoopa(fp);
    it_8026B3F8(items[0], It_Kind_Koopa_Flame);

    fp->x2226_b1 = true;
    fp->x222A_b0 = true;
}

void ftGk_Init_OnItemPickup(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemPickup(gobj, flag, true, true);
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

void ftGk_Init_UnkDemoCallbacks0(int arg0, int* arg1, int* arg2)
{
    if (arg0 == 0xF) {
        *arg2 = 0xE;
        *arg1 = 0xE;
    }
}

/// @remarks UB warning: this function may use offset uninitialized
char* ftGk_Init_GetMotionFileString(enum_t arg0)
{
    int offset;

    switch (arg0) {
    case 15:
        offset = 14;
    }

    return ftGk_Init_803D3984[offset - 14];
}
