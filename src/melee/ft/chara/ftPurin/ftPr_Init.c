#include "ftPr_Init.h"

#include "ftPr_SpecialHi.h"
#include "ftPr_SpecialLw.h"
#include "ftPr_SpecialN.h"
#include "ftPr_SpecialS.h"
#include "types.h"

#include <placeholder.h>

#include "ef/eflib.h"
#include "ef/efsync.h"

#include "forward.h"

#include "ft/fighter.h"
#include "ft/ft_0852.h"
#include "ft/ft_0877.h"
#include "ft/ftanim.h"
#include "ft/ftcamera.h"
#include "ft/ftdynamics.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Attack100.h"
#include "it/it_26B1.h"

#include <common_structs.h>
#include <baselib/archive.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/objalloc.h>

MotionState ftPr_Init_MotionStateTable[ftPr_MS_SelfCount] = {
    {
        // ftPr_MS_JumpAerialF1 = 341
        ftPr_SM_JumpAerialF1,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCo_JumpAerialF1_Anim,
        ftCo_JumpAerialF1_IASA,
        ftCo_JumpAerialF1_Phys,
        ftCo_JumpAerialF1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_JumpAerialF2 = 342
        ftPr_SM_JumpAerialF2,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCo_JumpAerialF1_Anim,
        ftCo_JumpAerialF1_IASA,
        ftCo_JumpAerialF1_Phys,
        ftCo_JumpAerialF1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_JumpAerialF3 = 343
        ftPr_SM_JumpAerialF3,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCo_JumpAerialF1_Anim,
        ftCo_JumpAerialF1_IASA,
        ftCo_JumpAerialF1_Phys,
        ftCo_JumpAerialF1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_JumpAerialF4 = 344
        ftPr_SM_JumpAerialF4,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCo_JumpAerialF1_Anim,
        ftCo_JumpAerialF1_IASA,
        ftCo_JumpAerialF1_Phys,
        ftCo_JumpAerialF1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_JumpAerialF5 = 345
        ftPr_SM_JumpAerialF5,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCo_JumpAerialF1_Anim,
        ftCo_JumpAerialF1_IASA,
        ftCo_JumpAerialF1_Phys,
        ftCo_JumpAerialF1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialNStartR = 346
        ftPr_SM_SpecialNStartR,
        ftPr_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftPr_SpecialNStart_Anim,
        ftPr_SpecialNStart_IASA,
        ftPr_SpecialNStart_Phys,
        ftPr_SpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialNStartL = 347
        ftPr_SM_SpecialNStartL,
        ftPr_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftPr_SpecialNStart_Anim,
        ftPr_SpecialNStart_IASA,
        ftPr_SpecialNStart_Phys,
        ftPr_SpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialNLoop = 348
        ftPr_SM_SpecialNChargeLoop,
        ftPr_MF_SpecialNCharged,
        FtMoveId_SpecialN << 24,
        ftPr_SpecialNLoop_Anim,
        ftPr_SpecialNLoop_IASA,
        ftPr_SpecialNLoop_Phys,
        ftPr_SpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialNFull = 349
        ftPr_SM_SpecialNChargeFull,
        ftPr_MF_SpecialNCharged,
        FtMoveId_SpecialN << 24,
        ftPr_SpecialNFull_Anim,
        ftPr_SpecialNFull_IASA,
        ftPr_SpecialNFull_Phys,
        ftPr_SpecialNFull_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialNRelease = 350
        ftPr_SM_SpecialNChargeRelease,
        ftPr_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftPr_SpecialNRelease_Anim,
        ftPr_SpecialNRelease_IASA,
        ftPr_SpecialNRelease_Phys,
        ftPr_SpecialNRelease_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialNTurn = 351
        ftPr_SM_SpecialNStartTurn,
        ftPr_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftPr_SpecialNTurn_Anim,
        ftPr_SpecialNTurn_IASA,
        ftPr_SpecialNTurn_Phys,
        ftPr_SpecialNTurn_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialNEndR = 352
        ftPr_SM_SpecialNEndR,
        ftPr_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftPr_SpecialNEnd_Anim,
        ftPr_SpecialNEnd_IASA,
        ftPr_SpecialNEnd_Phys,
        ftPr_SpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialNEndL = 353
        ftPr_SM_SpecialNEndL,
        ftPr_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftPr_SpecialNEnd_Anim,
        ftPr_SpecialNEnd_IASA,
        ftPr_SpecialNEnd_Phys,
        ftPr_SpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialAirNStartR = 354
        ftPr_SM_SpecialAirNStartR,
        ftPr_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftPr_SpecialAirNStart_Anim,
        ftPr_SpecialAirNStart_IASA,
        ftPr_SpecialAirNStart_Phys,
        ftPr_SpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialAirNStartL = 355
        ftPr_SM_SpecialAirNStartL,
        ftPr_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftPr_SpecialAirNStart_Anim,
        ftPr_SpecialAirNStart_IASA,
        ftPr_SpecialAirNStart_Phys,
        ftPr_SpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialAirNChargeLoop = 356
        ftPr_SM_SpecialAirNChargeLoop,
        ftPr_SpecialAirNCharged,
        FtMoveId_SpecialN << 24,
        ftPr_SpecialAirNChargeLoop_Anim,
        ftPr_SpecialAirNChargeLoop_IASA,
        ftPr_SpecialAirNChargeLoop_Phys,
        ftPr_SpecialAirNChargeLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialAirNChargeFull = 357
        ftPr_SM_SpecialAirNChargeFull,
        ftPr_SpecialAirNCharged,
        FtMoveId_SpecialN << 24,
        ftPr_SpecialAirNChargeFull_Anim,
        ftPr_SpecialAirNChargeFull_IASA,
        ftPr_SpecialAirNChargeFull_Phys,
        ftPr_SpecialAirNChargeFull_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialAirNChargeRelease = 358
        ftPr_SM_SpecialAirNChargeRelease,
        ftPr_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftPr_SpecialAirNChargeRelease_Anim,
        ftPr_SpecialAirNChargeRelease_IASA,
        ftPr_SpecialAirNChargeRelease_Phys,
        ftPr_SpecialAirNChargeRelease_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialAirNStartTurn = 359
        ftPr_SM_SpecialAirNStartTurn,
        ftPr_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftPr_SpecialAirNStartTurn_Anim,
        ftPr_SpecialAirNStartTurn_IASA,
        ftPr_SpecialAirNStartTurn_Phys,
        ftPr_SpecialAirNStartTurn_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialAirNEndR = 360
        ftPr_SM_SpecialAirNEndR,
        ftPr_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftPr_SpecialAirNEnd_Anim,
        ftPr_SpecialAirNEnd_IASA,
        ftPr_SpecialAirNEnd_Phys,
        ftPr_SpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialAirNEndL = 361
        ftPr_SM_SpecialAirNEndL,
        ftPr_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftPr_SpecialAirNEnd_Anim,
        ftPr_SpecialAirNEnd_IASA,
        ftPr_SpecialAirNEnd_Phys,
        ftPr_SpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialNHit = 362
        ftPr_SM_SpecialNHit,
        ftPr_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftPr_SpecialNHit_Anim,
        ftPr_SpecialNHit_IASA,
        ftPr_SpecialNHit_Phys,
        ftPr_SpecialNHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialS = 363
        ftPr_SM_SpecialS,
        ftPr_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftPr_SpecialS_Anim,
        ftPr_SpecialS_IASA,
        ftPr_SpecialS_Phys,
        ftPr_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialAirS = 364
        ftPr_SM_SpecialAirS,
        ftPr_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftPr_SpecialAirS_Anim,
        ftPr_SpecialAirS_IASA,
        ftPr_SpecialAirS_Phys,
        ftPr_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialHiL = 365
        ftPr_SM_SpecialHiL,
        ftPr_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPr_SpecialHi_Anim,
        ftPr_SpecialHi_IASA,
        ftPr_SpecialHi_Phys,
        ftPr_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialAirHiL = 366
        ftPr_SM_SpecialAirHiL,
        ftPr_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPr_SpecialAirHi_Anim,
        ftPr_SpecialAirHi_IASA,
        ftPr_SpecialAirHi_Phys,
        ftPr_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialHiR = 367
        ftPr_SM_SpecialHiR,
        ftPr_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPr_SpecialHi_Anim,
        ftPr_SpecialHi_IASA,
        ftPr_SpecialHi_Phys,
        ftPr_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialAirHiR = 368
        ftPr_SM_SpecialAirHiR,
        ftPr_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPr_SpecialAirHi_Anim,
        ftPr_SpecialAirHi_IASA,
        ftPr_SpecialAirHi_Phys,
        ftPr_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialLwL = 369
        ftPr_SM_SpecialLwL,
        ftPr_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftPr_SpecialLw_Anim,
        ftPr_SpecialLw_IASA,
        ftPr_SpecialLw_Phys,
        ftPr_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialAirLwL = 370
        ftPr_SM_SpecialAirLwL,
        ftPr_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftPr_SpecialAirLw_Anim,
        ftPr_SpecialAirLw_IASA,
        ftPr_SpecialAirLw_Phys,
        ftPr_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialLwR = 371
        ftPr_SM_SpecialLwR,
        ftPr_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftPr_SpecialLw_Anim,
        ftPr_SpecialLw_IASA,
        ftPr_SpecialLw_Phys,
        ftPr_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPr_MS_SpecialAirLwR = 372
        ftPr_SM_SpecialAirLwR,
        ftPr_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftPr_SpecialAirLw_Anim,
        ftPr_SpecialAirLw_IASA,
        ftPr_SpecialAirLw_Phys,
        ftPr_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftPr_Init_DatFilename[] = "PlPr.dat";
char ftPr_Init_DataName[] = "ftDataPurin";
char ftPr_Init_803D0308[] = "PlPrNr.dat";
char ftPr_Init_803D0314[] = "PlyPurin5K_Share_joint";
char ftPr_Init_803D032C[] = "PlyPurin5K_Share_matanim_joint";
char ftPr_Init_803D034C[] = "PlPrRe.dat";
char ftPr_Init_803D0358[] = "PlyPurin5KRe_Share_joint";
char ftPr_Init_803D0374[] = "PlyPurin5KRe_Share_matanim_joint";
char ftPr_Init_803D0398[] = "PlPrBu.dat";
char ftPr_Init_803D03A4[] = "PlyPurin5KBu_Share_joint";
char ftPr_Init_803D03C0[] = "PlyPurin5KBu_Share_matanim_joint";
char ftPr_Init_803D03E4[] = "PlPrGr.dat";
char ftPr_Init_803D03F0[] = "PlyPurin5KGr_Share_joint";
char ftPr_Init_803D040C[] = "PlyPurin5KGr_Share_matanim_joint";
char ftPr_Init_803D0430[] = "PlPrYe.dat";
char ftPr_Init_803D043C[] = "PlyPurin5KYe_Share_joint";
char ftPr_Init_803D0458[] = "PlyPurin5KYe_Share_matanim_joint";
char ftPr_Init_AnimDatFilename[] = "PlPrAJ.dat";

Fighter_DemoStrings ftPr_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFilePurin",
    "ftDemoIntroMotionFilePurin",
    "ftDemoEndingMotionFilePurin",
    "ftDemoViWaitMotionFilePurin",
};

Fighter_CostumeStrings ftPr_Init_CostumeStrings[] = {
    { ftPr_Init_803D0308, ftPr_Init_803D0314, ftPr_Init_803D032C },
    { ftPr_Init_803D034C, ftPr_Init_803D0358, ftPr_Init_803D0374 },
    { ftPr_Init_803D0398, ftPr_Init_803D03A4, ftPr_Init_803D03C0 },
    { ftPr_Init_803D03E4, ftPr_Init_803D03F0, ftPr_Init_803D040C },
    { ftPr_Init_803D0430, ftPr_Init_803D043C, ftPr_Init_803D0458 },
};

char* ftPr_Init_803D05B4[] = {
    NULL,
    "PlyPurinReHat_TopN_joint",
    "PlyPurinBuHat_TopN_joint",
    "PlyPurinGrHat_TopN_joint",
    "PlyPurinYeHat_TopN_joint",
};

Vec4 ftPr_Init_803D05C8 = { 0.65, 0.7, 0.8, 1 };
Vec4 ftPr_Init_803D05D8 = { 1.1, 1.35, 1.3, 1.2 };

char ftPr_Init_assert_msg_0[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";

Vec3 ftPr_Init_803D0610[] = {
    { +8, +0, -4 },
    { +4, +4, +4 },
};
/* static */ extern char* ftPr_Init_803D05B4[5];

void ftPr_Init_8013C2F8(void)
{
    ft_8045A1E0[0] = NULL;
    ft_8045A1E0[1] = NULL;
    ft_8045A1E0[2] = NULL;
    ft_8045A1E0[3] = NULL;
    ft_8045A1E0[4] = NULL;
}

void ftPr_Init_OnDeath(HSD_GObj* gobj)
{
    ftParts_80074A4C(gobj, 0, 0);
}

void ftPr_Init_OnUserDataRemove(HSD_GObj* gobj)
{
    ftPr_Init_8013C494(gobj);
}

void ftPr_Init_8013C360(HSD_GObj* gobj)
{
    HSD_Joint** joints = ft_8045A1E0;
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftPr_Init_803D05B4[fp->x619_costume_id]) {
        /// @@todo clean up memory accesses - this looks similar to
        /// ftKb_SpecialN_800EFB4C
        UNK_T* items = fp->ft_data->x48_items;
        UNK_T* items_shifted = items[1];

        if (!joints[fp->x619_costume_id]) {
            UnkCostumeStruct* costume_list =
                CostumeListsForeachCharacter[fp->kind].costume_list;
            joints[fp->x619_costume_id] = HSD_ArchiveGetPublicAddress(
                costume_list[fp->x619_costume_id].x14_archive,
                ftPr_Init_803D05B4[fp->x619_costume_id]);
        }

        fp->fv.pr.x2240.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
        ftPartsPObjSetDefaultClass();
        fp->fv.pr.x223C = HSD_JObjLoadJoint(joints[fp->x619_costume_id]);
        fp->x2225_b2 = true;
        ftPartsPObjClearDefaultClass();
        ftParts_80075650(gobj, fp->fv.pr.x223C, &fp->fv.pr.x2240);

        ftParts_8007487C((FtPartsDesc*) &items_shifted[1], &fp->fv.pr.x2248,
                         fp->x619_costume_id, &fp->fv.pr.x2240,
                         &fp->fv.pr.x2240);
        ftCo_8009DC54(fp);
        return;
    }

    fp->fv.pr.x223C = 0;
}

void ftPr_Init_8013C494(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.pr.x223C != NULL) {
        HSD_JObjRemoveAll(fp->fv.pr.x223C);
        fp->fv.pr.x223C = NULL;
        HSD_ObjFree(&fighter_x2040_alloc_data, fp->fv.pr.x2240.data);
        fp->fv.pr.x2240.data = NULL;
    }
}

void ftPr_Init_UnkMtxFunc0(HSD_GObj* gobj, int arg1, Mtx vmtx)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.pr.x223C && fp->x2225_b2) {
        MtxPtr mtx = HSD_JObjGetMtxPtr(fp->parts[FtPart_LLegJA].joint);
        HSD_JObj* jobj = fp->fv.pr.x223C;
        HSD_JObjCopyMtx(fp->fv.pr.x223C, mtx);
        jobj->flags |= (1 << 23) | (1 << 24) | (1 << 25);
        HSD_JObjSetMtxDirty(jobj);

        HSD_JObjDispAll(fp->fv.pr.x223C, vmtx, HSD_GObj_80390EB8(arg1), 0);
    }
}

void ftPr_Init_UnkIntBoolFunc0(Fighter* fp, int arg1, bool arg2)
{
    if (fp->fv.pr.x223C) {
        if (arg2) {
            ftParts_80074CA0(&fp->fv.pr.x2248, arg1, &fp->fv.pr.x2240);
        } else {
            ftParts_80074D7C(&fp->fv.pr.x2248, arg1, &fp->fv.pr.x2240);
        }
    }
}

HSD_JObj* ftPr_Init_UnkMotionStates6(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.pr.x223C) {
        return fp->fv.pr.x223C;
    }

    /// @@todo What???
    return (HSD_JObj*) gobj;
}

void ftPr_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PUSH_ATTRS(fp, ftPurinAttributes);
    fp->can_multijump = true;
    fp->x2D0 = fp->dat_attrs;
    ftPr_Init_8013C360(gobj);
}

void ftPr_Init_OnItemPickup(HSD_GObj* gobj, bool flag)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!it_8026B2B4(fp->item_gobj)) {
        switch (it_8026B320(fp->item_gobj)) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            ftAnim_80070FB4(gobj, 0, 0);
            break;
        case 4:
            ftAnim_80070FB4(gobj, 0, 1);
            break;
        }
        if (flag) {
            ftAnim_80070C48(gobj, 0);
        }
    }
}

void ftPr_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->item_gobj) {
        if (!it_8026B2B4(fp->item_gobj)) {
            ftAnim_80070CC4(gobj, 0);
        }
    }
}

void ftPr_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->item_gobj) {
        if (!it_8026B2B4(fp->item_gobj)) {
            ftAnim_80070C48(gobj, 0);
        }
    }
}

void ftPr_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 0, 0);
}

void ftPr_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftPurinAttributes);
}

void ftPr_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftPr_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

void ftPr_Init_8013C94C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!fp->x2219_b0) {
        efSync_Spawn(1238, gobj, fp->parts[FtPart_WaistN].joint);
        fp->x2219_b0 = true;
    }

    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}
