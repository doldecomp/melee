#include "ftPk_Init.h"

#include "ftPk_SpecialHi.h"
#include "ftPk_SpecialLw.h"
#include "ftPk_SpecialN.h"
#include "ftPk_SpecialS.h"
#include "types.h"

#include <platform.h>

#include "forward.h"

#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "it/it_26B1.h"

#include <dolphin/mtx.h>

MotionState ftPk_Init_MotionStateTable[ftPk_MS_SelfCount] = {
    {
        // ftPk_MS_SpecialN = 341
        ftPk_SM_SpecialN,
        ftPk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftPk_SpecialN_Anim,
        ftPk_SpecialN_IASA,
        ftPk_SpecialN_Phys,
        ftPk_SpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialAirN = 342
        ftPk_SM_SpecialAirN,
        ftPk_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftPk_SpecialAirN_Anim,
        ftPk_SpecialAirN_IASA,
        ftPk_SpecialAirN_Phys,
        ftPk_SpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialSStart = 343
        ftPk_SM_SpecialSStart,
        ftPk_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftPk_SpecialSStart_Anim,
        ftPk_SpecialSStart_IASA,
        ftPk_SpecialSStart_Phys,
        ftPk_SpecialSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialSHold = 344
        ftPk_SM_SpecialSHold,
        ftPk_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftPk_SpecialSHold_Anim,
        ftPk_SpecialSHold_IASA,
        ftPk_SpecialSHold_Phys,
        ftPk_SpecialSHold_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialS1 = 345
        ftPk_SM_SpecialS1,
        ftPk_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftPk_SpecialS1_Anim,
        ftPk_SpecialS1_IASA,
        ftPk_SpecialS1_Phys,
        ftPk_SpecialS1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialSEnd = 346
        ftPk_SM_SpecialSEnd,
        ftPk_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftPk_SpecialSEnd_Anim,
        ftPk_SpecialSEnd_IASA,
        ftPk_SpecialSEnd_Phys,
        ftPk_SpecialSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialS0 = 347
        ftPk_SM_SpecialS0,
        ftPk_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftPk_SpecialS0_Anim,
        ftPk_SpecialS0_IASA,
        ftPk_SpecialS0_Phys,
        ftPk_SpecialS0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialAirSStart = 348
        ftPk_SM_SpecialAirSStart,
        ftPk_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftPk_SpecialAirSStart_Anim,
        ftPk_SpecialAirSStart_IASA,
        ftPk_SpecialAirSStart_Phys,
        ftPk_SpecialAirSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialAirSHold = 349
        ftPk_SM_SpecialAirSHold,
        ftPk_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftPk_SpecialAirSHold_Anim,
        ftPk_SpecialAirSHold_IASA,
        ftPk_SpecialAirSHold_Phys,
        ftPk_SpecialAirSHold_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialAirS1 = 350
        ftPk_SM_SpecialS1,
        ftPk_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftPk_SpecialAirS1_Anim,
        ftPk_SpecialAirS1_IASA,
        ftPk_SpecialAirS1_Phys,
        ftPk_SpecialAirS1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialAirSEnd = 351
        ftPk_SM_SpecialAirSEnd,
        ftPk_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftPk_SpecialAirSEnd_Anim,
        ftPk_SpecialAirSEnd_IASA,
        ftPk_SpecialAirSEnd_Phys,
        ftPk_SpecialAirSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialAirS0 = 352
        ftPk_SM_SpecialS,
        ftPk_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftPk_SpecialAirS0_Anim,
        ftPk_SpecialAirS0_IASA,
        ftPk_SpecialAirS0_Phys,
        ftPk_SpecialAirS0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialHiStart0 = 353
        ftPk_SM_SpecialHiStart0,
        ftPk_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPk_SpecialHiStart0_Anim,
        ftPk_SpecialHiStart0_IASA,
        ftPk_SpecialHiStart0_Phys,
        ftPk_SpecialHiStart0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialHiStart1 = 354
        ftPk_SM_SpecialHiStart1,
        ftPk_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPk_SpecialHiStart1_Anim,
        ftPk_SpecialHiStart1_IASA,
        ftPk_SpecialHiStart1_Phys,
        ftPk_SpecialHiStart1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialHiEnd = 355
        ftPk_SM_SpecialHiEnd,
        ftPk_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPk_SpecialHiEnd_Anim,
        ftPk_SpecialHiEnd_IASA,
        ftPk_SpecialHiEnd_Phys,
        ftPk_SpecialHiEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialAirHiStart0 = 356
        ftPk_SM_SpecialAirHiStart0,
        ftPk_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPk_SpecialAirHiStart0_Anim,
        ftPk_SpecialAirHiStart0_IASA,
        ftPk_SpecialAirHiStart0_Phys,
        ftPk_SpecialAirHiStart0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialAirHiStart1 = 357
        ftPk_SM_SpecialAirHiStart1,
        ftPk_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPk_SpecialAirHiStart1_Anim,
        ftPk_SpecialAirHiStart1_IASA,
        ftPk_SpecialAirHiStart1_Phys,
        ftPk_SpecialAirHiStart1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialAirHiEnd = 358
        ftPk_SM_SpecialAirHiEnd,
        ftPk_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPk_SpecialAirHiEnd_Anim,
        ftPk_SpecialAirHiEnd_IASA,
        ftPk_SpecialAirHiEnd_Phys,
        ftPk_SpecialAirHiEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialLwStart = 359
        ftPk_SM_SpecialLwStart,
        ftPk_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftPk_SpecialLwStart_Anim,
        NULL,
        ftPk_SpecialLwStart_Phys,
        ftPk_SpecialLwStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialLwLoop0 = 360
        ftPk_SM_SpecialLwLoop0,
        ftPk_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftPk_SpecialLwLoop0_Anim,
        NULL,
        ftPk_SpecialLwLoop0_Phys,
        ftPk_SpecialLwLoop0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialLwLoop1 = 361
        ftPk_SM_SpecialLwLoop1,
        ftPk_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftPk_SpecialLwLoop1_Anim,
        NULL,
        ftPk_SpecialLwLoop1_Phys,
        ftPk_SpecialLwLoop1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialLwEnd = 362
        ftPk_SM_SpecialLwEnd,
        ftPk_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftPk_SpecialLwEnd_Anim,
        NULL,
        ftPk_SpecialLwEnd_Phys,
        ftPk_SpecialLwEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialAirLwStart = 363
        ftPk_SM_SpecialAirLwStart,
        ftPk_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftPk_SpecialAirLwStart_Anim,
        NULL,
        ftPk_SpecialAirLwStart_Phys,
        ftPk_SpecialAirLwStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialAirLwLoop0 = 364
        ftPk_SM_SpecialAirLwLoop0,
        ftPk_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftPk_SpecialAirLwLoop0_Anim,
        NULL,
        ftPk_SpecialAirLwLoop0_Phys,
        ftPk_SpecialAirLwLoop0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialAirLwLoop1 = 365
        ftPk_SM_SpecialAirLwLoop1,
        ftPk_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftPk_SpecialAirLwLoop1_Anim,
        NULL,
        ftPk_SpecialAirLwLoop1_Phys,
        ftPk_SpecialAirLwLoop1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPk_MS_SpecialAirLwEnd = 366
        ftPk_SM_SpecialAirLwEnd,
        ftPk_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftPk_SpecialAirLwEnd_Anim,
        NULL,
        ftPk_SpecialAirLwEnd_Phys,
        ftPk_SpecialAirLwEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftPk_Init_DatFilename[] = "PlPk.dat";
char ftPk_Init_DataName[] = "ftDataPikachu";
char ftPk_Init_803CE0D4[] = "PlPkNr.dat";
char ftPk_Init_803CE0E0[] = "PlyPikachu5K_Share_joint";
char ftPk_Init_803CE0FC[] = "PlyPikachu5K_Share_matanim_joint";
char ftPk_Init_803CE120[] = "PlPkRe.dat";
char ftPk_Init_803CE12C[] = "PlyPikachu5KRe_Share_joint";
char ftPk_Init_803CE148[] = "PlyPikachu5KRe_Share_matanim_joint";
char ftPk_Init_803CE16C[] = "PlPkBu.dat";
char ftPk_Init_803CE178[] = "PlyPikachu5KBu_Share_joint";
char ftPk_Init_803CE194[] = "PlyPikachu5KBu_Share_matanim_joint";
char ftPk_Init_803CE1B8[] = "PlPkGr.dat";
char ftPk_Init_803CE1C4[] = "PlyPikachu5KGr_Share_joint";
char ftPk_Init_803CE1E0[] = "PlyPikachu5KGr_Share_matanim_joint";
char ftPk_Init_AnimDatFilename[] = "PlPkAJ.dat";

Fighter_DemoStrings ftPk_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFilePikachu",
    "ftDemoIntroMotionFilePikachu",
    "ftDemoEndingMotionFilePikachu",
    "ftDemoViWaitMotionFilePikachu",
};

Fighter_CostumeStrings ftPk_Init_CostumeStrings[] = {
    { ftPk_Init_803CE0D4, ftPk_Init_803CE0E0, ftPk_Init_803CE0FC },
    { ftPk_Init_803CE120, ftPk_Init_803CE12C, ftPk_Init_803CE148 },
    { ftPk_Init_803CE16C, ftPk_Init_803CE178, ftPk_Init_803CE194 },
    { ftPk_Init_803CE1B8, ftPk_Init_803CE1C4, ftPk_Init_803CE1E0 },
};

void ftPk_Init_OnLoadForPichu(Fighter* fp)
{
    PUSH_ATTRS(fp, ftPikachuAttributes);
}

void ftPk_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void** item_list = fp->ft_data->x48_items;

    PUSH_ATTRS(fp, ftPikachuAttributes);

    {
        ftPikachuAttributes* pika_attr = fp->dat_attrs;
        it_8026B3F8(item_list[0], pika_attr->xDC);
        it_8026B3F8(item_list[1], pika_attr->x14);
        it_8026B3F8(item_list[2], pika_attr->x18);
    }
}

void ftPk_Init_OnDeath(HSD_GObj* gobj)
{
    u8 _[8];

    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 1, 0);
}

void ftPk_Init_OnItemPickup(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemPickup(gobj, flag, 0, 0);
}

void ftPk_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 0);
}

void ftPk_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

void ftPk_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 0, 0);
}

void ftPk_Init_UnkMotionStates1(HSD_GObj* gobj)
{
    u8 _[8];

    ftParts_80074A4C(gobj, 1, -1);
    ftParts_80074B0C(gobj, 1, 0);
}

void ftPk_Init_UnkMotionStates2(HSD_GObj* gobj)
{
    u8 _[8];

    ftParts_80074A4C(gobj, 1, 0);
    ftParts_80074B0C(gobj, 1, 0);
}

void ftPk_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftPikachuAttributes);
    if (fp->x34_scale.y != 1.0f) {
        int i;
        for (i = 0;
             i < (signed) (sizeof(sA2->height_attributes) / sizeof(float));
             i++)
        {
            *(float*) &sA2->height_attributes[i] *= fp->x34_scale.y;
        }
    }
}

void ftPk_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftPk_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}
