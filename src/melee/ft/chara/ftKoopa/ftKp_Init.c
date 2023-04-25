#include "forward.h"
#include "ft/forward.h"
#include "it/forward.h"

#include "ftKoopa/ftKp_Init.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

MotionState ftKp_Init_MotionStateTable[] = {
    {
        ftKp_AnimId_SpecialNStart,
        ftKp_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftKp_SpecialNStart_Anim,
        ftKp_SpecialNStart_IASA,
        ftKp_SpecialNStart_Phys,
        ftKp_SpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_SpecialNLoop,
        ftKp_MF_SpecialNLoop,
        FtMoveId_SpecialN << 24,
        ftKp_SpecialNLoop_Anim,
        ftKp_SpecialNLoop_IASA,
        ftKp_SpecialNLoop_Phys,
        ftKp_SpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_SpecialNEnd,
        ftKp_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftKp_SpecialNEnd_Anim,
        ftKp_SpecialNEnd_IASA,
        ftKp_SpecialNEnd_Phys,
        ftKp_SpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_SpecialAirNStart,
        ftKp_MF_SpecialNStart,
        FtMoveId_SpecialN << 24,
        ftKp_SpecialAirNStart_Anim,
        ftKp_SpecialAirNStart_IASA,
        ftKp_SpecialAirNStart_Phys,
        ftKp_SpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_SpecialAirNLoop,
        ftKp_MF_SpecialAirNLoop,
        FtMoveId_SpecialN << 24,
        ftKp_SpecialAirNLoop_Anim,
        ftKp_SpecialAirNLoop_IASA,
        ftKp_SpecialAirNLoop_Phys,
        ftKp_SpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_SpecialAirNEnd,
        ftKp_MF_SpecialNStart,
        FtMoveId_SpecialN << 24,
        ftKp_SpecialAirNEnd_Anim,
        ftKp_SpecialAirNEnd_IASA,
        ftKp_SpecialAirNEnd_Phys,
        ftKp_SpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_SpecialS,
        ftKp_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialS_Anim,
        NULL,
        ftKp_SpecialS_Phys,
        ftKp_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_Unk302,
        ftKp_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialSCatch_Anim,
        ftKp_SpecialSCatch_IASA,
        ftKp_SpecialSCatch_Phys,
        ftKp_SpecialSCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_SpecialSCatch1,
        ftKp_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialSCatch_Anim,
        ftKp_SpecialSCatch_IASA,
        ftKp_SpecialSCatch_Phys,
        ftKp_SpecialSCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_Unk302,
        ftKp_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialSWait_Anim,
        ftKp_SpecialSWait_IASA,
        ftKp_SpecialSWait_Phys,
        ftKp_SpecialSWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_SpecialSThrowF,
        ftKp_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialSThrowF_Anim,
        NULL,
        ftKp_SpecialSThrowF_Phys,
        ftKp_SpecialSThrowF_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_SpecialSThrowB,
        ftKp_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialSThrowB_Anim,
        NULL,
        ftKp_SpecialSThrowB_Phys,
        ftKp_SpecialSThrowB_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_SpecialAirS,
        ftKp_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialAirS_Anim,
        NULL,
        ftKp_SpecialAirS_Phys,
        ftKp_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_Unk307,
        ftKp_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialAirSCatch_Anim,
        ftKp_SpecialAirSCatch_IASA,
        ftKp_SpecialAirSCatch_Phys,
        ftKp_SpecialAirSCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_SpecialAirSCatch1,
        ftKp_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialAirSCatch_Anim,
        ftKp_SpecialAirSCatch_IASA,
        ftKp_SpecialAirSCatch_Phys,
        ftKp_SpecialAirSCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_Unk307,
        ftKp_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialAirSWait_Anim,
        ftKp_SpecialAirSWait_IASA,
        ftKp_SpecialAirSWait_Phys,
        ftKp_SpecialAirSWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_SpecialAirSThrowF,
        ftKp_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialAirSThrowF_Anim,
        NULL,
        ftKp_SpecialAirSThrowF_Phys,
        ftKp_SpecialAirSThrowF_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_SpecialAirSThrowB,
        ftKp_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftKp_SpecialAirSThrowB_Anim,
        NULL,
        ftKp_SpecialAirSThrowB_Phys,
        ftKp_SpecialAirSThrowB_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_SpecialHi,
        ftKp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftKp_SpecialHi_Anim,
        ftKp_SpecialHi_IASA,
        ftKp_SpecialHi_Phys,
        ftKp_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_SpecialAirHi,
        ftKp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftKp_SpecialAirHi_Anim,
        ftKp_SpecialAirHi_IASA,
        ftKp_SpecialAirHi_Phys,
        ftKp_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_SpecialLwStart,
        ftKp_MF_SpecialLwStart,
        FtMoveId_SpecialLw << 24,
        ftKp_SpecialLwStart_Anim,
        NULL,
        ftKp_SpecialLwStart_Phys,
        ftKp_SpecialLwStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_SpecialAirLw,
        ftKp_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftKp_SpecialAirLw_Anim,
        NULL,
        ftKp_SpecialAirLw_Phys,
        ftKp_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftKp_AnimId_SpecialLwLanding,
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

/* static */ extern const f32 ftKp_Init_804D9ADC; // = 1.0F
/* static */ extern const f32 ftKp_Init_804D9AD8; // = 0.0F

void ftKp_Init_OnDeath(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* koopaAttr = fp->x2D4_specialAttributes;

    ftParts_80074A4C(gobj, 0, 0);

    {
        ftKoopaVars* vars = (ftKoopaVars*) &fp->fv.kp.x222C;

        fp->dmg.x18B0 = koopaAttr->x0;
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
    /// @todo #GET_FIGHTER is 8 bytes too much stack but it should be possible
    Fighter* fp = gobj->user_data;

    ftData* ftDataInfo = fp->ft_data;
    UNK_T* items = ftDataInfo->x48_items;

    PUSH_ATTRS(fp, ftKoopaAttributes);
    it_8026B3F8(items[0], It_Kind_Koopa_Flame);
    fp->x2226_flag.bits.b1 = true;
}

void ftKp_Init_80132B38(void) {}

void ftKp_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, true, true);
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

f32 ftKp_SpecialS_80132DC0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x4C;
}

f32 ftKp_SpecialS_80132DD0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x48;
}

f32 ftKp_SpecialS_80132DE0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x44;
}

f32 ftKp_SpecialS_80132DF0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x40;
}

f32 ftKp_SpecialS_80132E00(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x3C;
}

f32 ftKp_SpecialS_80132E10(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x34;
}

f32 ftKp_SpecialS_80132E20(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x38;
}

void ftKp_SpecialS_80132E30(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    {
        bool throw_flag;
        if (fp->x2210_ThrowFlags.b4) {
            fp->x2210_ThrowFlags.b4 = false;
            throw_flag = true;
        } else {
            throw_flag = false;
        }

        if (throw_flag) {
            fp->facing_dir = -fp->facing_dir;
            fp->mv.kp.unk1.xC = true;
        }
    }

    if (fp->x2200_ftcmd_var0 == 0) {
        return;
    }

    if (fp->x1A58_interactedFighter == NULL) {
        return;
    }

    {
        HSD_GObj* victim_gobj = fp->x1A58_interactedFighter;
        ftCommon_8007E2F4(fp, 0);
        ft_800DE2A8(gobj, victim_gobj);
        ft_800DE7C0(victim_gobj, 0, 0);
        fp->x2200_ftcmd_var0 = 0;
    }
}

void ftKp_SpecialS_Enter(HSD_GObj* gobj)
{
    {
        Fighter* fp = GET_FIGHTER(gobj);

        fp->x2210_ThrowFlags.flags = 0;
        fp->x2200_ftcmd_var0 = 0;
        fp->mv.kp.unk1.x4 = 0;
        fp->mv.kp.unk1.xC = 0;
    }

    Fighter_ChangeMotionState(gobj, 347, 0, 0, ftKp_Init_804D9AD8,
                              ftKp_Init_804D9ADC, ftKp_Init_804D9AD8);

    ftAnim_8006EBA4(gobj);

    {
        Fighter* fp = GET_FIGHTER(gobj);

        ftCommon_8007E2D0(fp, 8, ftKp_SpecialS_8013302C, NULL, ft_800BC7E0);

        fp->mv.kp.unk1.x0 = 0;
        fp->mv.kp.unk1.x8 = 0;
    }
}

void ftKp_SpecialAirS_Enter(HSD_GObj* gobj)
{
    {
        Fighter* fp = GET_FIGHTER(gobj);

        fp->x2210_ThrowFlags.flags = 0;
        fp->x2200_ftcmd_var0 = 0;
        fp->mv.kp.unk1.x4 = 0;
        fp->mv.kp.unk1.xC = 0;
    }

    Fighter_ChangeMotionState(gobj, 353, 0, 0, ftKp_Init_804D9AD8,
                              ftKp_Init_804D9ADC, ftKp_Init_804D9AD8);

    ftAnim_8006EBA4(gobj);

    {
        Fighter* fp = GET_FIGHTER(gobj);

        ftCommon_8007E2D0(fp, 8, ftKp_SpecialS_801330E4, NULL, ft_800BC8D4);

        fp->mv.kp.unk1.x0 = 0;
        fp->mv.kp.unk1.x8 = 0;
    }
}

static u32 const transition_flags0 = Ft_MF_SkipMatAnim;

void ftKp_SpecialS_8013302C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((signed) fp->mv.kp.unk1.x4 != 0) {
        Fighter_ChangeMotionState(gobj, 349, transition_flags0, 0,
                                  ftKp_Init_804D9AD8, ftKp_Init_804D9ADC,
                                  ftKp_Init_804D9AD8);
    } else {
        Fighter_ChangeMotionState(gobj, 348, 0, 0, ftKp_Init_804D9AD8,
                                  ftKp_Init_804D9ADC, ftKp_Init_804D9AD8);
    }

    fp->x2222_flag.bits.b2 = true;
    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
    fp->mv.kp.unk1.x0 = 0;
    fp->x2200_ftcmd_var0 = 0;
}

void ftKp_SpecialS_801330E4(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = gobj->user_data;
    if ((signed) fp->mv.kp.unk1.x4 != 0) {
        Fighter_ChangeMotionState(gobj, 355, transition_flags0, 0,
                                  ftKp_Init_804D9AD8, ftKp_Init_804D9ADC,
                                  ftKp_Init_804D9AD8);
    } else {
        Fighter_ChangeMotionState(gobj, 354, 0, 0, ftKp_Init_804D9AD8,
                                  ftKp_Init_804D9ADC, ftKp_Init_804D9AD8);
    }

    fp->x2222_flag.bits.b2 = true;
    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
    fp->mv.kp.unk1.x0 = 0;
    fp->x2200_ftcmd_var0 = 0;
}

static u32 const transition_flags1 =
    Ft_MF_SkipHit | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd |
    Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
    Ft_MF_SkipModelFlags | Ft_MF_Unk27;

void ftKp_SpecialS_8013319C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, 353, transition_flags1, 0,
                              fp->x894_currentAnimFrame, ftKp_Init_804D9ADC,
                              ftKp_Init_804D9AD8);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007E2D0(fp, 8, ftKp_SpecialS_801330E4, NULL, ft_800BC8D4);
        fp->mv.kp.unk1.x0 = 0;
        fp->mv.kp.unk1.x8 = 0;
    }
}

void ftKp_SpecialS_8013322C(HSD_GObj* gobj)
{
    /// @todo @c fp0 cannot move below @c fp1, which is very strange.
    ///       Perhaps there is a temporary @c Fighter* somewhere.
    Fighter* fp0;
    Fighter* fp1 = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp1);

    Fighter_ChangeMotionState(gobj, 347, transition_flags1, 0,
                              fp1->x894_currentAnimFrame, ftKp_Init_804D9ADC,
                              ftKp_Init_804D9AD8);

    {
        fp0 = GET_FIGHTER(gobj);
        ftCommon_8007E2D0(fp0, 8, ftKp_SpecialS_8013302C, NULL, ft_800BC7E0);
        fp0->mv.kp.unk1.x0 = 0;
        fp0->mv.kp.unk1.x8 = 0;
    }

    fp1->mv.kp.unk1.x0 = 0;
    fp1->x2200_ftcmd_var0 = 0;
}

void ftKp_SpecialS_801332C4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    HSD_GObj* victim_gobj = fp->x1A58_interactedFighter;

    ftCommon_8007D5D4(fp);

    if (victim_gobj != NULL) {
        ft_800DC920(gobj, victim_gobj);
        ft_800CC730(victim_gobj);
    }

    ft_800CC730(gobj);
}

void ftKp_SpecialS_80133324(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, 348, transition_flags1, 0,
                              fp->x894_currentAnimFrame, ftKp_Init_804D9ADC,
                              ftKp_Init_804D9AD8);

    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
}

void ftKp_SpecialS_80133398(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* victim_gobj = fp->x1A58_interactedFighter;

    ftCommon_8007D5D4(fp);

    if (victim_gobj != NULL) {
        ft_800DC920(gobj, victim_gobj);
        ft_800CC730(victim_gobj);
    }

    ft_800CC730(gobj);
}
/// @todo Combine common flags with #transition_flags0.
static u32 const transition_flags2 =
    Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
    Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags;

void ftKp_SpecialS_801333F8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, 350, transition_flags2, 0,
                              fp->x894_currentAnimFrame, ftKp_Init_804D9ADC,
                              ftKp_Init_804D9AD8);

    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
    ftAnim_8006F0FC(gobj, ftKp_Init_804D9AD8);
    fp->mv.kp.unk1.x0 = 0;
    fp->x2200_ftcmd_var0 = 0;
}

void ftKp_SpecialS_80133484(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* victim_gobj = fp->x1A58_interactedFighter;

    ftCommon_8007D5D4(fp);

    if (victim_gobj != NULL) {
        ft_800DC920(gobj, victim_gobj);
        ft_800CC730(victim_gobj);
    }

    ft_800CC730(gobj);
}

void ftKp_SpecialS_801334E4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);

    if ((signed) fp->mv.kp.unk1.xC != 0) {
        fp->facing_dir = -fp->facing_dir;
    }

    Fighter_ChangeMotionState(gobj, 351, transition_flags1, 0,
                              fp->x894_currentAnimFrame, ftKp_Init_804D9ADC,
                              ftKp_Init_804D9AD8);

    if ((s32) fp->mv.kp.unk1.xC != 0) {
        fp->facing_dir = -fp->facing_dir;
    }

    if (fp->x1A58_interactedFighter != NULL) {
        ft_800BCE64(fp->x1A58_interactedFighter, ftCo_MS_ThrownKoopaF);
    }

    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
}

void ftKp_SpecialS_8013359C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);

    if ((signed) fp->mv.kp.unk1.xC != 0) {
        fp->facing_dir = -fp->facing_dir;
    }

    Fighter_ChangeMotionState(gobj, 352, transition_flags1, 0,
                              fp->x894_currentAnimFrame, ftKp_Init_804D9ADC,
                              ftKp_Init_804D9AD8);

    if ((signed) fp->mv.kp.unk1.xC != 0) {
        fp->facing_dir = -fp->facing_dir;
    }

    if (fp->x1A58_interactedFighter != NULL) {
        ft_800BCE64(fp->x1A58_interactedFighter, ftCo_MS_ThrownKoopaB);
    }

    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
}

void ftKp_SpecialS_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKp_SpecialAirS_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CC730(gobj);
    }
}

static u32 const transition_flags3 = Ft_MF_SkipMatAnim | Ft_MF_Unk19;

void ftKp_SpecialSCatch_Anim(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);

    {
        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 unused0[8];
#endif

        Fighter* fp1 = fp0;

        {
            ftKoopaAttributes* koopaAttr = fp1->x2D4_specialAttributes;

            if (fp1->x2200_ftcmd_var0 != 0 && (signed) fp1->mv.kp.unk1.x4 != 0)
            {
                ftColl_8007ABD0(&fp1->x914[0], koopaAttr->x2C, gobj);
                fp1->x2200_ftcmd_var0 = 0;
            }
        }

        if (ftAnim_IsFramesRemaining(gobj)) {
            return;
        }

        if ((signed) fp1->mv.kp.unk1.x0 != 0) {
            fp1->mv.kp.unk1.x4 = true;

            {
                /// @todo Combine @c fp0 with other branch somehow
                fp0 = GET_FIGHTER(gobj);

                if ((signed) fp0->mv.kp.unk1.x4 != false) {
                    Fighter_ChangeMotionState(
                        gobj, 349, transition_flags0, 0, ftKp_Init_804D9AD8,
                        ftKp_Init_804D9ADC, ftKp_Init_804D9AD8);
                } else {
                    Fighter_ChangeMotionState(
                        gobj, 348, Ft_MF_None, 0, ftKp_Init_804D9AD8,
                        ftKp_Init_804D9ADC, ftKp_Init_804D9AD8);
                }

                fp0->x2222_flag.bits.b2 = true;
                ftCommon_8007E2F4(fp0, 511);
                ftCommon_8007E2FC(gobj);
                fp0->mv.kp.unk1.x0 = 0;
                fp0->x2200_ftcmd_var0 = 0;
            }

            ft_800BC9C8(fp1->x1A58_interactedFighter);

        } else {
            /// @todo Combine @c fp0 with other branch somehow
            fp0 = GET_FIGHTER(gobj);
            Fighter_ChangeMotionState(gobj, 350, transition_flags3, 0,
                                      fp0->x894_currentAnimFrame,
                                      ftKp_Init_804D9ADC, ftKp_Init_804D9AD8);

            ftAnim_8006F0FC(gobj, ftKp_Init_804D9AD8);
            fp0->mv.kp.unk1.x0 = 0;
            fp0->x2200_ftcmd_var0 = 0;
            ftCommon_8007E2F4(fp0, 511);
        }
    }
}
