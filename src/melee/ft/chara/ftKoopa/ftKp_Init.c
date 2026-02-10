#include "ftKp_Init.h"

#include "ftKp_SpecialHi.h"
#include "ftKp_SpecialLw.h"
#include "ftKp_SpecialN.h"
#include "ftKp_SpecialS.h"

#include <placeholder.h>

#include "forward.h"

#include "ft/fighter.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcamera.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftCo_CaptureCut.h"
#include "ftCommon/ftCo_CaptureDamageKoopa.h"
#include "ftCommon/ftCo_CaptureKoopa.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_Throw.h"
#include "ftCommon/ftCo_Thrown.h"
#include "ftCommon/ftCo_ThrownKoopa.h"
#include "ftKoopa/types.h"

#include "it/forward.h"

#include "it/it_26B1.h"

MotionState ftKp_Init_MotionStateTable[ftKp_MS_SelfCount] = {
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
        ftKp_SM_SpecialSHit0,
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
        ftKp_SM_SpecialAirSHit0,
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

char ftKp_Init_DatFilename[] = "PlKp.dat";
char ftKp_Init_DataName[] = "ftDataKoopa";
char ftKp_Init_803CF0B8[] = "PlKpNr.dat";
char ftKp_Init_803CF0C4[] = "PlyKoopa5K_Share_joint";
char ftKp_Init_803CF0DC[] = "PlyKoopa5K_Share_matanim_joint";
char ftKp_Init_803CF0FC[] = "PlKpRe.dat";
char ftKp_Init_803CF108[] = "PlyKoopa5KRe_Share_joint";
char ftKp_Init_803CF124[] = "PlyKoopa5KRe_Share_matanim_joint";
char ftKp_Init_803CF148[] = "PlKpBu.dat";
char ftKp_Init_803CF154[] = "PlyKoopa5KBu_Share_joint";
char ftKp_Init_803CF170[] = "PlyKoopa5KBu_Share_matanim_joint";
char ftKp_Init_803CF194[] = "PlKpBk.dat";
char ftKp_Init_803CF1A0[] = "PlyKoopa5KBk_Share_joint";
char ftKp_Init_803CF1BC[] = "PlyKoopa5KBk_Share_matanim_joint";
char ftKp_Init_AnimDatFilename[] = "PlKpAJ.dat";

Fighter_DemoStrings ftKp_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileKoopa",
    "ftDemoIntroMotionFileKoopa",
    "ftDemoEndingMotionFileKoopa",
    "ftDemoViWaitMotionFileKoopa",
};

Fighter_CostumeStrings ftKp_Init_CostumeStrings[] = {
    { ftKp_Init_803CF0B8, ftKp_Init_803CF0C4, ftKp_Init_803CF0DC },
    { ftKp_Init_803CF0FC, ftKp_Init_803CF108, ftKp_Init_803CF124 },
    { ftKp_Init_803CF148, ftKp_Init_803CF154, ftKp_Init_803CF170 },
    { ftKp_Init_803CF194, ftKp_Init_803CF1A0, ftKp_Init_803CF1BC },
};

void ftKp_Init_OnDeath(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* koopaAttr = fp->dat_attrs;

    ftParts_80074A4C(gobj, 0, 0);

    {
        ftKoopaVars* vars = (ftKoopaVars*) &fp->fv.kp.x222C;

        fp->dmg.armor0 = koopaAttr->x0;
        vars->x0 = koopaAttr->x10;
        vars->x4 = koopaAttr->x18;
    }
}

/* static */ void ftKp_SpecialLw_80134D78(HSD_GObj* gobj);

void ftKp_Init_UnkMotionStates3(HSD_GObj* gobj)
{
    ftKp_SpecialLw_80134D78(gobj);
}

void ftKp_Init_OnLoadForGKoopa(Fighter* fp)
{
    PUSH_ATTRS(fp, ftKoopaAttributes);
}

void ftKp_Init_OnLoad(HSD_GObj* gobj)
{
    /// @@todo #GET_FIGHTER is 8 bytes too much stack but it should be possible
    Fighter* fp = gobj->user_data;

    ftData* ftDataInfo = fp->ft_data;
    UNK_T* items = ftDataInfo->x48_items;

    PUSH_ATTRS(fp, ftKoopaAttributes);
    it_8026B3F8(items[0], It_Kind_Koopa_Flame);
    fp->x2226_b1 = true;
}

void ftKp_Init_80132B38(void) {}

void ftKp_Init_OnItemPickup(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemPickup(gobj, flag, true, true);
}

void ftKp_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, true);
}

void ftKp_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, true);
}

void ftKp_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, true, true);
}

void ftKp_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftKoopaAttributes);
}

void ftKp_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, true);
}

void ftKp_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, true);
}

float ftKp_SpecialS_80132DC0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->dat_attrs;
    return sa->x4C;
}

float ftKp_SpecialS_80132DD0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->dat_attrs;
    return sa->x48;
}

float ftKp_SpecialS_80132DE0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->dat_attrs;
    return sa->x44;
}

float ftKp_SpecialS_80132DF0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->dat_attrs;
    return sa->x40;
}

float ftKp_SpecialS_80132E00(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->dat_attrs;
    return sa->x3C;
}

float ftKp_SpecialS_80132E10(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->dat_attrs;
    return sa->x34;
}

float ftKp_SpecialS_80132E20(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->dat_attrs;
    return sa->x38;
}

void ftKp_SpecialS_80132E30(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    {
        bool throw_flag;
        if (fp->throw_flags_b4) {
            fp->throw_flags_b4 = false;
            throw_flag = true;
        } else {
            throw_flag = false;
        }

        if (throw_flag) {
            fp->facing_dir = -fp->facing_dir;
            fp->mv.kp.unk1.xC = true;
        }
    }

    if (fp->cmd_vars[0] == 0) {
        return;
    }

    if (fp->victim_gobj == NULL) {
        return;
    }

    {
        HSD_GObj* victim_gobj = fp->victim_gobj;
        ftCommon_8007E2F4(fp, 0);
        ftCo_800DE2A8(gobj, victim_gobj);
        ftCo_800DE7C0(victim_gobj, 0, 0);
        fp->cmd_vars[0] = 0;
    }
}
