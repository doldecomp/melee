#include <platform.h>

#include "ftPopo/forward.h"

#include "ftNn_Init.h"

#include "ft/fighter.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftPopo/ftPp_1211.h"
#include "ftPopo/ftPp_Init.h"
#include "ftPopo/ftPp_SpecialN.h"
#include "ftPopo/ftPp_SpecialS.h"
#include "ftPopo/types.h"

#include <dolphin/mtx.h>

/* static */ void ftNn_Init_801238E4(HSD_GObj* gobj);

char ftNn_Init_803CD7F8[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";

Vec3 ftNn_Init_803CD820[] = {
    { 12, 0, -6 },
    { 6, 6, 6 },
};

MotionState ftNn_Init_MotionStateTable[ftPp_MS_SelfCount] = {
    {
        // ftPp_MS_SpecialN = 341
        ftPp_SM_SpecialN,
        ftPp_MF_SpecialN,
        (FtMoveId_SpecialN << 24) | (1 << 23),
        ftPp_SpecialN_Anim,
        ftPp_SpecialN_IASA,
        ftPp_SpecialN_Phys,
        ftPp_SpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirN = 342
        ftPp_SM_SpecialAirN,
        ftPp_MF_SpecialAirN,
        (FtMoveId_SpecialN << 24) | (1 << 23),
        ftPp_SpecialAirN_Anim,
        ftPp_SpecialAirN_IASA,
        ftPp_SpecialAirN_Phys,
        ftPp_SpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialS1 = 343
        ftPp_SM_SpecialS1,
        ftPp_MF_SpecialS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialS1_Anim,
        ftPp_SpecialS1_IASA,
        ftPp_SpecialS1_Phys,
        ftPp_SpecialS1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialS2 = 344
        ftPp_SM_SpecialS2,
        ftPp_MF_SpecialS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialS2_Anim,
        ftPp_SpecialS2_IASA,
        ftPp_SpecialS2_Phys,
        ftPp_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirS1 = 345
        ftPp_SM_SpecialAirS1,
        ftPp_MF_SpecialAirS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialAirS1_Anim,
        ftPp_SpecialAirS1_IASA,
        ftPp_SpecialAirS1_Phys,
        ftPp_SpecialAirS1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirS2 = 346
        ftPp_SM_SpecialAirS2,
        ftPp_MF_SpecialAirS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialAirS2_Anim,
        ftPp_SpecialAirS2_IASA,
        ftPp_SpecialAirS2_Phys,
        ftPp_SpecialAirS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHiStart_0 = 347
        ftPp_SM_SpecialHiStart_0,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHiStart_0_Anim,
        ftPp_SpecialHiStart_0_IASA,
        ftPp_SpecialHiStart_0_Phys,
        ftPp_SpecialHiStart_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHiThrow_0 = 348
        ftPp_SM_SpecialHiThrow_0,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHiThrow_0_Anim,
        ftPp_SpecialHiThrow_0_IASA,
        ftPp_SpecialHiThrow_0_Phys,
        ftPp_SpecialHiThrow_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHiThrow2 = 349
        ftPp_SM_SpecialHiThrow2,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHiThrow2_Anim,
        ftPp_SpecialHiThrow2_IASA,
        ftPp_SpecialHiThrow2_Phys,
        ftPp_SpecialHiThrow2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHiStart_1 = 350
        ftPp_SM_SpecialHiStart_1,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHiStart_1_Anim,
        ftPp_SpecialHiStart_1_IASA,
        ftPp_SpecialHiStart_1_Phys,
        ftPp_SpecialHiStart_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHiThrow_1 = 351
        ftPp_SM_SpecialHiThrow_1,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHiThrow_1_Anim,
        ftPp_SpecialHiThrow_1_IASA,
        ftPp_SpecialHiThrow_1_Phys,
        ftPp_SpecialHiThrow_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirHiStart_0 = 352
        ftPp_SM_SpecialAirHiStart_0,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialAirHiStart_0_Anim,
        ftPp_SpecialAirHiStart_0_IASA,
        ftPp_SpecialAirHiStart_0_Phys,
        ftPp_SpecialAirHiStart_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirHiThrow_0 = 353
        ftPp_SM_SpecialAirHiThrow_0,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialAirHiThrow_0_Anim,
        ftPp_SpecialAirHiThrow_0_IASA,
        ftPp_SpecialAirHiThrow_0_Phys,
        ftPp_SpecialAirHiThrow_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirHiThrow2 = 354
        ftPp_SM_SpecialAirHiThrow2,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialAirHiThrow2_Anim,
        ftPp_SpecialAirHiThrow2_IASA,
        ftPp_SpecialAirHiThrow2_Phys,
        ftPp_SpecialAirHiThrow2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirHiStart_1 = 355
        ftPp_SM_SpecialAirHiStart_1,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialAirHiStart_1_Anim,
        ftPp_SpecialAirHiStart_1_IASA,
        ftPp_SpecialAirHiStart_1_Phys,
        ftPp_SpecialAirHiStart_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirHiThrow_1 = 356
        ftPp_SM_SpecialAirHiThrow_1,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialAirHiThrow_1_Anim,
        ftPp_SpecialAirHiThrow_1_IASA,
        ftPp_SpecialAirHiThrow_1_Phys,
        ftPp_SpecialAirHiThrow_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialLw = 357
        ftPp_SM_SpecialLw,
        ftPp_MF_SpecialLw,
        (FtMoveId_SpecialLw << 24) | (1 << 23),
        ftPp_SpecialLw_Anim,
        ftPp_SpecialLw_IASA,
        ftPp_SpecialLw_Phys,
        ftPp_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirLw = 358
        ftPp_SM_SpecialAirLw,
        ftPp_MF_MS_358,
        (FtMoveId_SpecialLw << 24) | (1 << 23),
        ftPp_SpecialAirLw_Anim,
        ftPp_SpecialAirLw_IASA,
        ftPp_SpecialAirLw_Phys,
        ftPp_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialS_0 = 359
        ftPp_SM_SpecialS_0,
        ftPp_MF_SpecialS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialS_0_Anim,
        ftPp_SpecialS_0_IASA,
        ftPp_SpecialS_0_Phys,
        ftPp_SpecialS_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialS_1 = 360
        ftPp_SM_SpecialS_1,
        ftPp_MF_SpecialAirS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialS_1_Anim,
        ftPp_SpecialS_1_IASA,
        ftPp_SpecialS_1_Phys,
        ftPp_SpecialS_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHi_0 = 361
        ftPp_SM_SpecialHi_0,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHi_0_Anim,
        ftPp_SpecialHi_0_IASA,
        ftPp_SpecialHi_0_Phys,
        ftPp_SpecialHi_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHi_1 = 362
        ftPp_SM_SpecialHi_1,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHi_1_Anim,
        ftPp_SpecialHi_1_IASA,
        ftPp_SpecialHi_1_Phys,
        ftPp_SpecialHi_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHi_2 = 363
        ftPp_SM_SpecialHi_2,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHi_3 = 364
        ftPp_SM_SpecialHi_3,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHi_3_Anim,
        ftPp_SpecialHi_3_IASA,
        ftPp_SpecialHi_3_Phys,
        ftPp_SpecialHi_3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHi_4 = 365
        ftPp_SM_SpecialHi_4,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHi_4_Anim,
        ftPp_SpecialHi_4_IASA,
        ftPp_SpecialHi_4_Phys,
        ftPp_SpecialHi_4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHi_5 = 366
        ftPp_SM_SpecialHi_5,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        ftCamera_UpdateCameraBox,
    },
};

char ftNn_Init_DatFilename[] = "PlNn.dat";
char ftNn_Init_DataName[] = "ftDataNana";
char ftNn_Init_803CDB90[] = "PlNnNr.dat";
char ftNn_Init_803CDB9C[] = "PlyNana5K_Share_joint";
char ftNn_Init_803CDBB4[] = "PlyNana5K_Share_matanim_joint";
char ftNn_Init_803CDBD4[] = "PlNnYe.dat";
char ftNn_Init_803CDBE0[] = "PlyNana5KYe_Share_joint";
char ftNn_Init_803CDBF8[] = "PlyNana5KYe_Share_matanim_joint";
char ftNn_Init_803CDC18[] = "PlNnAq.dat";
char ftNn_Init_803CDC24[] = "PlyNana5KAq_Share_joint";
char ftNn_Init_803CDC3C[] = "PlyNana5KAq_Share_matanim_joint";
char ftNn_Init_803CDC5C[] = "PlNnWh.dat";
char ftNn_Init_803CDC68[] = "PlyNana5KWh_Share_joint";
char ftNn_Init_803CDC80[] = "PlyNana5KWh_Share_matanim_joint";
char ftNn_Init_AnimDatFilename[] = "PlNnAJ.dat";
char ftNn_Init_803CDCAC[] = "ftDemoResultMotionFileNana";
char ftNn_Init_803CDCC8[] = "ftDemoIntroMotionFileNana";
char ftNn_Init_803CDCE4[] = "ftDemoEndingMotionFileNana";
char ftNn_Init_803CDD00[] = "ftDemoViWaitMotionFilePopo";

Fighter_DemoStrings ftNn_Init_DemoMotionFilenames = {
    ftNn_Init_803CDCAC,
    ftNn_Init_803CDCC8,
    ftNn_Init_803CDCE4,
    ftNn_Init_803CDD00,
};

Fighter_CostumeStrings ftNn_Init_CostumeStrings[] = {
    { ftNn_Init_803CDB90, ftNn_Init_803CDB9C, ftNn_Init_803CDBB4 },
    { ftNn_Init_803CDBD4, ftNn_Init_803CDBE0, ftNn_Init_803CDBF8 },
    { ftNn_Init_803CDC18, ftNn_Init_803CDC24, ftNn_Init_803CDC3C },
    { ftNn_Init_803CDC5C, ftNn_Init_803CDC68, ftNn_Init_803CDC80 },
};

extern float ftNn_Init_804D9898;

void ftNn_Init_OnLoad(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2222_b4 = true;
    ftPp_Init_OnLoadForNana(fp);

    {
        ftIceClimberAttributes* da = fp->dat_attrs;
        fp->x40 = da->xC4;
    }
}

void ftNn_Init_OnDeath(HSD_GObj* gobj)
{
    u8 _[4];

    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    fp->dmg.armor0 = da->xC8;
    ftParts_80074A4C(gobj, 0U, 0);
    ftParts_80074A4C(gobj, 1U, 0);
    fp->fv.nn.x2234 = 0;
    fp->fv.nn.x222C = 0;
    fp->fv.nn.x2230_b0 = 0;
    fp->fv.nn.x2238 = 0;
    fp->fv.nn.x224C = 0;
    fp->fv.nn.x2250 = ftNn_Init_804D9898;
}

void ftNn_Init_80122FAC(HSD_GObj* gobj)
{
    ftNn_Init_801238E4(gobj);
}

void ftNn_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftIceClimberAttributes);
}

/// #ftNn_Init_8012300C

/// #ftNn_Init_8012309C

/// #ftNn_Init_801230D0

/// #fn_80123218

/// #ftNn_Init_801232A4

/// #ftPp_SpecialHi_0_Anim

void ftPp_SpecialHi_3_Anim(Fighter_GObj* gobj) {}

void ftPp_SpecialHi_0_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialHi_3_IASA(Fighter_GObj* gobj) {}

/// #ftPp_SpecialHi_0_Phys

void ftPp_SpecialHi_3_Phys(Fighter_GObj* gobj) {}

void ftPp_SpecialHi_0_Coll(Fighter_GObj* gobj) {}

void ftPp_SpecialHi_3_Coll(Fighter_GObj* gobj) {}

/// #ftNn_Init_801233F8

/// #ftPp_SpecialHi_1_Anim

/// #ftPp_SpecialHi_4_Anim

void ftPp_SpecialHi_1_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialHi_4_IASA(Fighter_GObj* gobj) {}

/// #ftPp_SpecialHi_1_Phys

/// #ftPp_SpecialHi_4_Phys

/// #ftPp_SpecialHi_1_Coll

/// #ftPp_SpecialHi_4_Coll

/// #ftNn_Init_80123720

/// #ftNn_Init_8012378C

/// #ftNn_Init_801237F8

/// #ftNn_Init_801238E4

/// #ftNn_Init_80123954

/// #ftNn_Init_80123B10

/// #ftNn_Init_80123B3C

/// #ftNn_Init_80123BF0

/// #ftPp_SpecialS_0_Anim

/// #ftPp_SpecialS_1_Anim

void ftPp_SpecialS_0_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialS_1_IASA(Fighter_GObj* gobj) {}

/// #ftPp_SpecialS_0_Phys

/// #ftPp_SpecialS_1_Phys

/// #ftPp_SpecialS_0_Coll

/// #ftPp_SpecialS_1_Coll
