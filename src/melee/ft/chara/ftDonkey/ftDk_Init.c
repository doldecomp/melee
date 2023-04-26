#include "forward.h"
#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ftDonkey/ftDk_Init.h"

#include "ftDk_MS_341.h"
#include "ftDk_MS_342.h"
#include "ftDk_MS_345_0.h"
#include "ftDk_MS_345_1.h"
#include "ftDk_MS_346.h"
#include "ftDk_MS_347.h"
#include "ftDk_MS_348.h"
#include "ftDk_MS_349.h"
#include "ftDk_SpecialHi.h"
#include "ftDk_SpecialLw.h"
#include "ftDk_SpecialN.h"
#include "ftDk_SpecialS.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftcoll.h"
#include "ft/ftdata.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "lb/lbmthp.h"
#include "mp/mplib.h"

#include <dolphin/mtx/types.h>

MotionState ftDk_Init_MotionStateTable[] = {
    {
        ftDk_SM_HeavyWait0,
        ftDk_MF_MS_341,
        (FtMoveId_ThrowF << 24) | (1 << 22),
        NULL,
        ftDk_MS_341_IASA,
        ftDk_MS_341_Phys,
        ftDk_MS_341_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_HeavyWalkSlow,
        ftDk_MF_MS_342,
        FtMoveId_ThrowF << 24,
        ftDk_MS_342_Anim,
        ftDk_MS_342_IASA,
        ftDk_MS_342_Phys,
        ftDk_MS_342_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_HeavyWalkMiddle,
        ftDk_MF_MS_342,
        FtMoveId_ThrowF << 24,
        ftDk_MS_342_Anim,
        ftDk_MS_342_IASA,
        ftDk_MS_342_Phys,
        ftDk_MS_342_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_HeavyWalkFast,
        ftDk_MF_MS_342,
        FtMoveId_ThrowF << 24,
        ftDk_MS_342_Anim,
        ftDk_MS_342_IASA,
        ftDk_MS_342_Phys,
        ftDk_MS_342_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_HeavyTurn,
        ftDk_MF_MS_345,
        FtMoveId_ThrowF << 24,
        ftDk_MS_345_Anim,
        ftDk_MS_345_IASA,
        ftDk_MS_345_Phys,
        ftDk_MS_345_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_HeavyWait1,
        ftDk_MF_MS_341,
        FtMoveId_ThrowF << 24,
        ftDk_MS_346_Anim,
        ftDk_MS_346_IASA,
        ftDk_MS_346_Phys,
        ftDk_MS_346_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_HeavyFall,
        ftDk_MF_MS_341,
        FtMoveId_ThrowF << 24,
        NULL,
        ftDk_MS_347_IASA,
        ftDk_MS_347_Phys,
        ftDk_MS_347_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_HeavyJump,
        ftDk_MF_MS_348,
        FtMoveId_ThrowF << 24,
        NULL,
        ftDk_MS_348_IASA,
        ftDk_MS_348_Phys,
        ftDk_MS_348_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_HeavyLanding,
        ftDk_MF_MS_341,
        (FtMoveId_ThrowF << 24) | (1 << 22),
        ftDk_MS_349_Anim,
        NULL,
        ftDk_MS_349_Phys,
        ftDk_MS_349_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_HeavyWait2,
        ftDk_MF_MS_350,
        FtMoveId_ThrowF << 24,
        ftDk_MS_350_Anim,
        NULL,
        ftDk_MS_350_Phys,
        ftDk_MS_350_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_ThrowFWait0,
        ftDk_MF_CargoWait,
        (FtMoveId_ThrowF << 24) | (1 << 22),
        ftCo_CargoWait_Anim,
        ftCo_CargoWait_IASA,
        ftCo_CargoWait_Phys,
        ftCo_CargoWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_ThrowFWalkSlow,
        ftDk_MF_CargoWalk,
        FtMoveId_ThrowF << 24,
        ftCo_CargoWalk_Anim,
        ftCo_CargoWalk_IASA,
        ftCo_CargoWalk_Phys,
        ftCo_CargoWalk_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_ThrowFWalkMiddle,
        ftDk_MF_CargoWalk,
        FtMoveId_ThrowF << 24,
        ftCo_CargoWalk_Anim,
        ftCo_CargoWalk_IASA,
        ftCo_CargoWalk_Phys,
        ftCo_CargoWalk_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_ThrowFWalkFast,
        ftDk_MF_CargoWalk,
        FtMoveId_ThrowF << 24,
        ftCo_CargoWalk_Anim,
        ftCo_CargoWalk_IASA,
        ftCo_CargoWalk_Phys,
        ftCo_CargoWalk_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_ThrowFTurn,
        ftDk_MF_CargoTurn,
        FtMoveId_ThrowF << 24,
        ftCo_CargoTurn_Anim,
        ftCo_CargoTurn_IASA,
        ftCo_CargoTurn_Phys,
        ftCo_CargoTurn_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_ThrowFWait1,
        ftDk_MF_CargoWait,
        FtMoveId_ThrowF << 24,
        ftCo_CargoKneebend_Anim,
        ftCo_CargoKneebend_IASA,
        ftCo_CargoKneebend_Phys,
        ftCo_CargoKneebend_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_ThrowFFall,
        ftDk_MF_CargoWait,
        FtMoveId_ThrowF << 24,
        ftCo_CargoFall_Anim,
        ftCo_CargoFall_IASA,
        ftCo_CargoFall_Phys,
        ftCo_CargoFall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_ThrowFJump,
        ftDk_MF_CargoJump,
        FtMoveId_ThrowF << 24,
        ftCo_CargoJump_Anim,
        ftCo_CargoJump_IASA,
        ftCo_CargoJump_Phys,
        ftCo_CargoJump_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_ThrowFLanding,
        ftDk_MF_CargoWait,
        (FtMoveId_ThrowF << 24) | (1 << 22),
        ftCo_CargoLanding_Anim,
        NULL,
        ftCo_CargoLanding_Phys,
        ftCo_CargoLanding_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_ThrowFWait2,
        ftDk_MF_MS_360,
        FtMoveId_ThrowF << 24,
        ftCo_MS_360_Anim,
        NULL,
        ftCo_MS_360_Phys,
        ftCo_MS_360_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_ThrowFF,
        ftDk_MF_CargoThrowF,
        FtMoveId_CargoThrowF << 24,
        ftCo_CargoThrowF_Anim,
        ftCo_CargoThrowF_IASA,
        ftCo_CargoThrowF_Phys,
        ftCo_CargoThrowF_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_ThrowFB,
        ftDk_MF_CargoThrowB,
        FtMoveId_CargoThrowB << 24,
        ftCo_CargoThrowB_Anim,
        ftCo_CargoThrowB_IASA,
        ftCo_CargoThrowB_Phys,
        ftCo_CargoThrowB_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_ThrowFHi,
        ftDk_MF_CargoThrowHi,
        FtMoveId_CargoThrowHi << 24,
        ftCo_CargoThrowU_Anim,
        ftCo_CargoThrowU_IASA,
        ftCo_CargoThrowU_Phys,
        ftCo_CargoThrowU_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_ThrowFLw,
        ftDk_MF_CargoThrowLw,
        FtMoveId_CargoThrowLw << 24,
        ftCo_CargoThrowD_Anim,
        ftCo_CargoThrowD_IASA,
        ftCo_CargoThrowD_Phys,
        ftCo_CargoThrowD_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_ThrowFF,
        ftDk_MF_CargoThrowF,
        FtMoveId_CargoThrowF << 24,
        ftCo_CargoAirThrow_Anim,
        ftCo_CargoAirThrow_IASA,
        ftCo_CargoAirThrow_Phys,
        ftCo_CargoAirThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_ThrowFB,
        ftDk_MF_CargoThrowB,
        FtMoveId_CargoThrowB << 24,
        ftCo_CargoAirThrow_Anim,
        ftCo_CargoAirThrow_IASA,
        ftCo_CargoAirThrow_Phys,
        ftCo_CargoAirThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_ThrowFHi,
        ftDk_MF_CargoThrowHi,
        FtMoveId_CargoThrowHi << 24,
        ftCo_CargoAirThrow_Anim,
        ftCo_CargoAirThrow_IASA,
        ftCo_CargoAirThrow_Phys,
        ftCo_CargoAirThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_ThrowFLw,
        ftDk_MF_CargoThrowLw,
        FtMoveId_CargoThrowLw << 24,
        ftCo_CargoAirThrow_Anim,
        ftCo_CargoAirThrow_IASA,
        ftCo_CargoAirThrow_Phys,
        ftCo_CargoAirThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_SpecialNStart,
        ftDk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftDk_SpecialNChargeStart_Anim,
        ftDk_SpecialNChargeStart_IASA,
        ftDk_SpecialNChargeStart_Phys,
        ftDk_SpecialNChargeStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_SpecialNLoop,
        ftDk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftDk_SpecialNChargeLoop_Anim,
        ftDk_SpecialNChargeLoop_IASA,
        ftDk_SpecialNChargeLoop_Phys,
        ftDk_SpecialNChargeLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_SpecialNCancel,
        ftDk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftDk_SpecialNChargeStop_Anim,
        ftDk_SpecialNChargeStop_IASA,
        ftDk_SpecialNChargeStop_Phys,
        ftDk_SpecialNChargeStop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_SpecialN,
        ftDk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftDk_SpecialNEarlyRelease_Anim,
        ftDk_SpecialNEarlyRelease_IASA,
        ftDk_SpecialNEarlyRelease_Phys,
        ftDk_SpecialNEarlyRelease_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_SpecialNFull,
        ftDk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftDk_SpecialNFullRelease_Anim,
        ftDk_SpecialNFullRelease_IASA,
        ftDk_SpecialNFullRelease_Phys,
        ftDk_SpecialNFullRelease_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_SpecialAirNStart,
        ftDk_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftDk_SpecialAirNChargeStart_Anim,
        ftDk_SpecialAirNChargeStart_IASA,
        ftDk_SpecialAirNChargeStart_Phys,
        ftDk_SpecialAirNChargeStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_SpecialAirNLoop,
        ftDk_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftDk_SpecialAirNChargeLoop_Anim,
        ftDk_SpecialAirNChargeLoop_IASA,
        ftDk_SpecialAirNChargeLoop_Phys,
        ftDk_SpecialAirNChargeLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_SpecialAirNCancel,
        ftDk_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftDk_SpecialAirNChargeStop_Anim,
        ftDk_SpecialAirNChargeStop_IASA,
        ftDk_SpecialAirNChargeStop_Phys,
        ftDk_SpecialAirNChargeStop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_SpecialAirN,
        ftDk_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftDk_SpecialAirNEarlyRelease_Anim,
        ftDk_SpecialAirNEarlyRelease_IASA,
        ftDk_SpecialAirNEarlyRelease_Phys,
        ftDk_SpecialAirNEarlyRelease_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_SpecialAirNFull,
        ftDk_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftDk_SpecialAirNFullRelease_Anim,
        ftDk_SpecialAirNFullRelease_IASA,
        ftDk_SpecialAirNFullRelease_Phys,
        ftDk_SpecialAirNFullRelease_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_SpecialS,
        ftDk_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftDk_SpecialS_Anim,
        ftDk_SpecialS_IASA,
        ftDk_SpecialS_Phys,
        ftDk_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_SpecialAirS,
        ftDk_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftDk_SpecialAirS_Anim,
        ftDk_SpecialAirS_IASA,
        ftDk_SpecialAirS_Phys,
        ftDk_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_SpecialHi,
        ftDk_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftDk_SpecialHi_Anim,
        ftDk_SpecialHi_IASA,
        ftDk_SpecialHi_Phys,
        ftDk_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_SpecialAirHi,
        ftDk_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftDk_SpecialAirHi_Anim,
        ftDk_SpecialAirHi_IASA,
        ftDk_SpecialAirHi_Phys,
        ftDk_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_SpecialLwStart,
        ftDk_MF_SpecialLwStart,
        FtMoveId_SpecialLw << 24,
        ftDk_SpecialLwStart_Anim,
        ftDk_SpecialLwStart_IASA,
        ftDk_SpecialLwStart_Phys,
        ftDk_SpecialLwStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_SpecialLwLoop,
        ftDk_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftDk_SpecialLwLoop_Anim,
        ftDk_SpecialLwLoop_IASA,
        ftDk_SpecialLwLoop_Phys,
        ftDk_SpecialLwLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_SpecialLwEnd0,
        ftDk_MF_SpecialLwStart,
        FtMoveId_SpecialLw << 24,
        ftDk_SpecialLwEnd_Anim,
        ftDk_SpecialLwEnd_IASA,
        ftDk_SpecialLwEnd_Phys,
        ftDk_SpecialLwEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftDk_SM_SpecialLwEnd1,
        ftDk_MF_MS_386,
        FtMoveId_SpecialLw << 24,
        ftDk_MS_386_Anim,
        ftDk_MS_386_IASA,
        ftDk_MS_386_Phys,
        ftDk_MS_386_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftDk_Init_DatFilename[] = "PlDk.dat";
char ftDk_Init_DataName[] = "ftDataDonkey";
char ftDk_Init_803CBE14[] = "PlDkNr.dat";
char ftDk_Init_803CBE20[] = "PlyDonkey5K_Share_joint";
char ftDk_Init_803CBE38[] = "PlyDonkey5K_Share_matanim_joint";
char ftDk_Init_803CBE58[] = "PlDkBk.dat";
char ftDk_Init_803CBE64[] = "PlyDonkey5KBk_Share_joint";
char ftDk_Init_803CBE80[] = "PlyDonkey5KBk_Share_matanim_joint";
char ftDk_Init_803CBEA4[] = "PlDkRe.dat";
char ftDk_Init_803CBEB0[] = "PlyDonkey5KRe_Share_joint";
char ftDk_Init_803CBECC[] = "PlyDonkey5KRe_Share_matanim_joint";
char ftDk_Init_803CBEF0[] = "PlDkBu.dat";
char ftDk_Init_803CBEFC[] = "PlyDonkey5KBu_Share_joint";
char ftDk_Init_803CBF18[] = "PlyDonkey5KBu_Share_matanim_joint";
char ftDk_Init_803CBF3C[] = "PlDkGr.dat";
char ftDk_Init_803CBF48[] = "PlyDonkey5KGr_Share_joint";
char ftDk_Init_803CBF64[] = "PlyDonkey5KGr_Share_matanim_joint";
char ftDk_Init_AnimDatFilename[] = "PlDkAJ.dat";

Fighter_DemoStrings ftDk_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileDonkey",
    "ftDemoIntroMotionFileDonkey",
    "ftDemoEndingMotionFileDonkey",
    "ftDemoViWaitMotionFileDonkey",
};

Fighter_CostumeStrings ftDk_Init_CostumeStrings[] = {
    { ftDk_Init_803CBE14, ftDk_Init_803CBE20, ftDk_Init_803CBE38 },
    { ftDk_Init_803CBE58, ftDk_Init_803CBE64, ftDk_Init_803CBE80 },
    { ftDk_Init_803CBEA4, ftDk_Init_803CBEB0, ftDk_Init_803CBECC },
    { ftDk_Init_803CBEF0, ftDk_Init_803CBEFC, ftDk_Init_803CBF18 },
    { ftDk_Init_803CBF3C, ftDk_Init_803CBF48, ftDk_Init_803CBF64 },
};

void ftDk_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.dk.x222C = 0;
    ftParts_80074A4C(gobj, 0, 0);
}

void ftDk_Init_8010D774(HSD_GObj* gobj)
{
    ftDk_SpecialN_DestroyAllEffectsPlus(gobj);
    ftDk_SpecialHi_DestroyAllEffects(gobj);
}

void ftDk_Init_OnItemPickup(HSD_GObj* gobj, bool arg1)
{
    Fighter_OnItemPickup(gobj, arg1, 1, 1);
}

void ftDk_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, true);
}

void ftDk_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, true);
}

void ftDk_Init_OnItemDrop(HSD_GObj* gobj, bool arg1)
{
    Fighter_OnItemDrop(gobj, arg1, true, true);
}

void ftDk_Init_UnkMotionStates4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* attr = fp->x2D4_specialAttributes;
    if (fp->fv.dk.x222C == attr->SpecialN.x2C_MAX_ARM_SWINGS) {
        ft_800BFFD0(fp, 57, 0);
    }
}

void ftDk_Init_OnLoad(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    ftData* ftdata = fp->ft_data;
    ftDonkeyAttributes* ftData_attr = ftdata->ext_attr;
    ftData_attr->x8 = lbMthp_8001E8F8(ftData_80085E50(fp, 296));
    ftData_attr->xC = lbMthp_8001E8F8(ftData_80085E50(fp, 297));
    ftData_attr->x10 = lbMthp_8001E8F8(ftData_80085E50(fp, 298));
    PUSH_ATTRS(fp, ftDonkeyAttributes);
    fp->x2222_flag.bits.b0 = true;
    fp->x2CC = fp->x2D4_specialAttributes;
}

void ftDk_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftDonkeyAttributes);
}

void ftDk_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, true);
}

void ftDk_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, true);
}

void ftDk_Init_8010DB3C(HSD_GObj* gobj)
{
    bool was_throw_b3;
    Fighter* fp = gobj->user_data;
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;
    CollData* colldata = &fp->x6F0_collData;
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    if (fp->x2210_ThrowFlags.b3) {
        fp->x2210_ThrowFlags.b3 = false;
        was_throw_b3 = true;
    } else {
        was_throw_b3 = false;
    }
    if (was_throw_b3 && (colldata->x134_envFlags & 98304)) {
        Vec3 vec_list[4];
        int i;
        for (i = 0; i < 4; i++) {
            f32 temp_f5 = (donkey_attr->SpecialLw.x68 * i) -
                          (donkey_attr->SpecialLw.x68 * 1.5f);
            f32 temp_f3 = donkey_attr->SpecialLw.x6C * fp->facing_dir;
            f32 temp_f6 = temp_f5 + temp_f3;

            if (!mpLib_80056C54(colldata->x14C_ground.index, &fp->cur_pos, 0,
                                &vec_list[i], 0, 0, temp_f6,
                                donkey_attr->SpecialLw.x70,
                                donkey_attr->SpecialLw.x68 * 1.5f,
                                donkey_attr->SpecialLw.x68))
            {
                vec_list[i] = fp->cur_pos;
            }

            vec_list[i].y += 2.0f;
            ftColl_8007B8A8(&fp->x914[i], &vec_list[i]);
        }
    }
}
