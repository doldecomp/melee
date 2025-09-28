#include "placeholder.h"

#include <platform.h>

#include "cm/camera.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_CaptureDamageKoopa.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftCommon/ftCo_Throw.h"
#include "ftCommon/ftCo_Thrown.h"
#include "ftCommon/ftCo_ThrownKoopa.h"
#include "ftCommon/ftCo_CaptureKoopa.h"

#include "ftKoopa/forward.h"

#include "ftKoopa/ftKp_Init.h"
#include "ftKoopa/types.h"

#include <baselib/forward.h>

#include <trigf.h>
#include <baselib/gobj.h>

static s32 ftKp_SpecialS_set_dir(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    s32 facing_dir = 0;
    if (fp->input.x668 & HSD_PAD_B) {
        fp->mv.kp.specials.b_held = true;
    }
    if (fp->input.lstick1.x > -da->x30 && fp->input.lstick.x < -da->x30) {
        facing_dir = -1;
    }
    if (fp->input.lstick1.x < da->x30 && fp->input.lstick.x > da->x30) {
        facing_dir = +1;
    }
    fp->mv.kp.specials.facing_dir = fp->facing_dir * facing_dir;
    return facing_dir;
}

void ftKp_SpecialS_Enter(HSD_GObj* gobj)
{
    {
        Fighter* fp = GET_FIGHTER(gobj);

        fp->throw_flags = 0;
        fp->cmd_vars[0] = 0;
        fp->mv.kp.unk1.x4 = 0;
        fp->mv.kp.unk1.xC = 0;
    }

    Fighter_ChangeMotionState(gobj, 347, 0, 0.0F,
                              1.0F, 0.0F, 0);

    ftAnim_8006EBA4(gobj);

    {
        Fighter* fp = GET_FIGHTER(gobj);

        ftCommon_8007E2D0(fp, 8, ftKp_SpecialS_8013302C, NULL, ftCo_800BC7E0);

        fp->mv.kp.unk1.x0 = 0;
        fp->mv.kp.unk1.x8 = 0;
    }
}

void ftKp_SpecialAirS_Enter(HSD_GObj* gobj)
{
    {
        Fighter* fp = GET_FIGHTER(gobj);

        fp->throw_flags = 0;
        fp->cmd_vars[0] = 0;
        fp->mv.kp.unk1.x4 = 0;
        fp->mv.kp.unk1.xC = 0;
    }

    Fighter_ChangeMotionState(gobj, 353, 0, 0.0F,
                              1.0F, 0.0F, 0);

    ftAnim_8006EBA4(gobj);

    {
        Fighter* fp = GET_FIGHTER(gobj);

        ftCommon_8007E2D0(fp, 8, ftKp_SpecialS_801330E4, NULL, ftCo_800BC8D4);

        fp->mv.kp.unk1.x0 = 0;
        fp->mv.kp.unk1.x8 = 0;
    }
}

static u32 const transition_flags0 = Ft_MF_SkipMatAnim;

void ftKp_SpecialS_8013302C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((signed) fp->mv.kp.unk1.x4 != 0) {
        Fighter_ChangeMotionState(gobj, 349, transition_flags0,
                                  0.0F, 1.0F,
                                  0.0F, 0);
    } else {
        Fighter_ChangeMotionState(gobj, 348, 0, 0.0F,
                                  1.0F, 0.0F, 0);
    }

    fp->x2222_b2 = true;
    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
    fp->mv.kp.unk1.x0 = 0;
    fp->cmd_vars[0] = 0;
}

void ftKp_SpecialS_801330E4(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = gobj->user_data;
    if ((signed) fp->mv.kp.unk1.x4 != 0) {
        Fighter_ChangeMotionState(gobj, 355, transition_flags0,
                                  0.0F, 1.0F,
                                  0.0F, 0);
    } else {
        Fighter_ChangeMotionState(gobj, 354, 0, 0.0F,
                                  1.0F, 0.0F, 0);
    }

    fp->x2222_b2 = true;
    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
    fp->mv.kp.unk1.x0 = 0;
    fp->cmd_vars[0] = 0;
}

static u32 const transition_flags1 =
    Ft_MF_SkipHit | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd |
    Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
    Ft_MF_SkipModelFlags | Ft_MF_Unk27;

void ftKp_SpecialS_8013319C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, 353, transition_flags1, fp->cur_anim_frame,
                              1.0F, 0.0F, 0);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007E2D0(fp, 8, ftKp_SpecialS_801330E4, NULL, ftCo_800BC8D4);
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

    Fighter_ChangeMotionState(gobj, 347, transition_flags1,
                              fp1->cur_anim_frame, 1.0F,
                              0.0F, 0);

    {
        fp0 = GET_FIGHTER(gobj);
        ftCommon_8007E2D0(fp0, 8, ftKp_SpecialS_8013302C, NULL, ftCo_800BC7E0);
        fp0->mv.kp.unk1.x0 = 0;
        fp0->mv.kp.unk1.x8 = 0;
    }

    fp1->mv.kp.unk1.x0 = 0;
    fp1->cmd_vars[0] = 0;
}

void ftKp_SpecialS_801332C4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    HSD_GObj* victim_gobj = fp->victim_gobj;

    ftCommon_8007D5D4(fp);

    if (victim_gobj != NULL) {
        ftCo_800DC920(gobj, victim_gobj);
        ftCo_Fall_Enter(victim_gobj);
    }

    ftCo_Fall_Enter(gobj);
}

void ftKp_SpecialS_80133324(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, 348, transition_flags1, fp->cur_anim_frame,
                              1.0F, 0.0F, 0);

    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
}

void ftKp_SpecialS_80133398(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* victim_gobj = fp->victim_gobj;

    ftCommon_8007D5D4(fp);

    if (victim_gobj != NULL) {
        ftCo_800DC920(gobj, victim_gobj);
        ftCo_Fall_Enter(victim_gobj);
    }

    ftCo_Fall_Enter(gobj);
}
/// @todo Combine common flags with #transition_flags0.
static u32 const transition_flags2 =
    Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
    Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags;

void ftKp_SpecialS_801333F8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, 350, transition_flags2, fp->cur_anim_frame,
                              1.0F, 0.0F, 0);

    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
    ftAnim_8006F0FC(gobj, 0.0F);
    fp->mv.kp.unk1.x0 = 0;
    fp->cmd_vars[0] = 0;
}

void ftKp_SpecialS_80133484(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* victim_gobj = fp->victim_gobj;

    ftCommon_8007D5D4(fp);

    if (victim_gobj != NULL) {
        ftCo_800DC920(gobj, victim_gobj);
        ftCo_Fall_Enter(victim_gobj);
    }

    ftCo_Fall_Enter(gobj);
}

void ftKp_SpecialS_801334E4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);

    if ((signed) fp->mv.kp.unk1.xC != 0) {
        fp->facing_dir = -fp->facing_dir;
    }

    Fighter_ChangeMotionState(gobj, 351, transition_flags1, fp->cur_anim_frame,
                              1.0F, 0.0F, 0);

    if ((s32) fp->mv.kp.unk1.xC != 0) {
        fp->facing_dir = -fp->facing_dir;
    }

    if (fp->victim_gobj != NULL) {
        ftCo_800BCE64(fp->victim_gobj, ftCo_MS_ThrownKoopaF);
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

    Fighter_ChangeMotionState(gobj, 352, transition_flags1, fp->cur_anim_frame,
                              1.0F, 0.0F, 0);

    if ((signed) fp->mv.kp.unk1.xC != 0) {
        fp->facing_dir = -fp->facing_dir;
    }

    if (fp->victim_gobj != NULL) {
        ftCo_800BCE64(fp->victim_gobj, ftCo_MS_ThrownKoopaB);
    }

    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
}

void ftKp_SpecialSStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKp_SpecialAirSStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

static u32 const transition_flags3 = Ft_MF_SkipMatAnim | Ft_MF_Unk19;

void ftKp_SpecialSHit_Anim(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);

    {
        u8 unused0[8];

        Fighter* fp1 = fp0;

        {
            ftKoopaAttributes* koopaAttr = fp1->dat_attrs;

            if (fp1->cmd_vars[0] != 0 && (signed) fp1->mv.kp.unk1.x4 != 0) {
                ftColl_8007ABD0(&fp1->x914[0], koopaAttr->x2C, gobj);
                fp1->cmd_vars[0] = 0;
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
                        gobj, 349, transition_flags0, 0.0F,
                        1.0F, 0.0F, 0);
                } else {
                    Fighter_ChangeMotionState(
                        gobj, 348, Ft_MF_None, 0.0F,
                        1.0F, 0.0F, 0);
                }

                fp0->x2222_b2 = true;
                ftCommon_8007E2F4(fp0, 511);
                ftCommon_8007E2FC(gobj);
                fp0->mv.kp.unk1.x0 = 0;
                fp0->cmd_vars[0] = 0;
            }

            ftCo_800BC9C8(fp1->victim_gobj);

        } else {
            /// @todo Combine @c fp0 with other branch somehow
            fp0 = GET_FIGHTER(gobj);
            Fighter_ChangeMotionState(gobj, 350, transition_flags3,
                                      fp0->cur_anim_frame, 1.0F,
                                      0.0F, 0);

            ftAnim_8006F0FC(gobj, 0.0F);
            fp0->mv.kp.unk1.x0 = 0;
            fp0->cmd_vars[0] = 0;
            ftCommon_8007E2F4(fp0, 511);
        }
    }
}

inline void inlineA0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.kp.specials.x4) {
        Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialAirSHit1,
                                  Ft_MF_SkipMatAnim, 0, 1, 0, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialAirSHit0_0, Ft_MF_None,
                                  0, 1, 0, NULL);
    }
    fp->x2222_b2 = true;
    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007E2FC(gobj);
    fp->mv.kp.specials.b_held = false;
    fp->cmd_vars[0] = 0;
}

static inline void inlineA1(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialAirSHit0_1,
                              Ft_MF_SkipMatAnim | Ft_MF_Unk19,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftAnim_8006F0FC(gobj, 0);
    fp->mv.kp.specials.b_held = false;
    fp->cmd_vars[0] = 0;
    ftCommon_8007E2F4(fp, 0x1FF);
}

void ftKp_SpecialAirSHit_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(4 * 2);
    if (fp->cmd_vars[0] != 0 && fp->mv.kp.specials.x4) {
        ftColl_8007ABD0(fp->x914, da->x2C, gobj);
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->mv.kp.specials.b_held) {
            fp->mv.kp.specials.x4 = true;
            inlineA0(gobj);
            ftCo_800BCAF4(fp->victim_gobj);
        } else {
            inlineA1(gobj);
        }
    }
}

void ftKp_SpecialSWait_Anim(HSD_GObj* gobj) {}

void ftKp_SpecialAirSWait_Anim(HSD_GObj* gobj) {}

static inline void doEndFAnim(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FORCE_PAD_STACK(4 * 2);
    if (ftCheckThrowB4(fp)) {
        fp->facing_dir = -fp->facing_dir;
        fp->mv.kp.specials.xC = true;
    }
    if (fp->cmd_vars[0] != 0) {
        HSD_GObj* victim_gobj = fp->victim_gobj;
        if (victim_gobj != NULL) {
            ftCommon_8007E2F4(fp, 0);
            ftCo_800DE2A8(gobj, victim_gobj);
            ftCo_800DE7C0(victim_gobj, 0, 0);
            fp->cmd_vars[0] = 0;
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
    }
}

void ftKp_SpecialSEndF_Anim(HSD_GObj* gobj)
{
    doEndFAnim(gobj, ft_8008A2BC);
}

static inline void doEndBAnim(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    FORCE_PAD_STACK(4 * 2);
    ftKp_SpecialS_80132E30(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
    }
}

void ftKp_SpecialSEndB_Anim(HSD_GObj* gobj)
{
    doEndBAnim(gobj, ft_8008A2BC);
}

void ftKp_SpecialAirSEndF_Anim(HSD_GObj* gobj)
{
    doEndFAnim(gobj, ftCo_Fall_Enter);
}

void ftKp_SpecialAirSEndB_Anim(HSD_GObj* gobj)
{
    doEndBAnim(gobj, ftCo_Fall_Enter);
}

inline void ftKoopa_SpecialS_ChangeAction(HSD_GObj* gobj,
                                          ftKoopa_MotionState kp_msid_f,
                                          ftCommon_MotionState victim_msid_f,
                                          ftKoopa_MotionState kp_msid_b,
                                          ftCommon_MotionState victim_msid_b)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    fp->throw_flags = 0;
    fp->cmd_vars[0] = 0;
    if (fp->mv.kp.specials.facing_dir == +1) {
        Fighter_ChangeMotionState(gobj, kp_msid_f, Ft_MF_Unk19, 0, 1, 0, NULL);
        ftCo_800BCDE0(fp->victim_gobj, victim_msid_f);
    } else {
        Fighter_ChangeMotionState(gobj, kp_msid_b, Ft_MF_Unk19, 0, 1, 0, NULL);
        ftCo_800BCDE0(fp->victim_gobj, victim_msid_b);
    }
}

/// @todo Shared inline with #ftKp_SpecialAirSHit_IASA.
void ftKp_SpecialSHit_IASA(HSD_GObj* gobj)
{
    s32 facing_dir = ftKp_SpecialS_set_dir(gobj);
    PAD_STACK(16);
    if (facing_dir != 0) {
        ftKoopa_SpecialS_ChangeAction(
            gobj, ftKp_MS_SpecialSEndF, ftCo_MS_ThrownKoopaF,
            ftKp_MS_SpecialSEndB, ftCo_MS_ThrownKoopaB);
    }
}

/// @todo Shared inline with #ftKp_SpecialSHit_IASA.
void ftKp_SpecialAirSHit_IASA(HSD_GObj* gobj)
{
    s32 facing_dir = ftKp_SpecialS_set_dir(gobj);
    PAD_STACK(16);
    if (facing_dir != 0) {
        ftKoopa_SpecialS_ChangeAction(
            gobj, ftKp_MS_SpecialAirSEndF, ftCo_MS_ThrownKoopaAirF,
            ftKp_MS_SpecialAirSEndB, ftCo_MS_ThrownKoopaAirB);
    }
}

inline void ftKp_SpecialSWait_IASA_inline(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.kp.specials.x4) {
        Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialSHit1,
                                  Ft_MF_SkipMatAnim, 0, 1, 0, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialSHit0_0, Ft_MF_None, 0,
                                  1, 0, NULL);
    }
    fp->x2222_b2 = true;
    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007E2FC(gobj);
    fp->mv.kp.specials.b_held = false;
    fp->cmd_vars[0] = 0;
}

void ftKp_SpecialSWait_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 facing_dir = ftKp_SpecialS_set_dir(gobj);
    PAD_STACK(16);
    if (facing_dir != 0) {
        ftKoopa_SpecialS_ChangeAction(
            gobj, ftKp_MS_SpecialSEndF, ftCo_MS_ThrownKoopaF,
            ftKp_MS_SpecialSEndB, ftCo_MS_ThrownKoopaB);
    } else {
        if (fp->mv.kp.specials.b_held) {
            fp->mv.kp.specials.x4 = true;
            ftKp_SpecialSWait_IASA_inline(gobj);
            ftCo_800BC9C8(fp->victim_gobj);
        }
    }
}

static void ftKp_SpecialAirSWait_IASA_inline_2(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.ca.specialhi.vel.x != 0) {
        Fighter_ChangeMotionState(gobj, 0x163, 0x80U, 0.0f, 1.0f, 0.0f, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, 0x162, 0U, 0.0f, 1.0f, 0.0f, NULL);
    }
    fp->x2222_b2 = 1;
    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007E2FC(gobj);
    fp->mv.kp.specials.b_held = false;
    fp->cmd_vars[0] = 0;
}

void ftKp_SpecialAirSWait_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 facing_dir = ftKp_SpecialS_set_dir(gobj);
    PAD_STACK(16);
    if (facing_dir != 0) {
        ftKoopa_SpecialS_ChangeAction(
            gobj, ftKp_MS_SpecialAirSEndF, ftCo_MS_ThrownKoopaAirF,
            ftKp_MS_SpecialAirSEndB, ftCo_MS_ThrownKoopaAirB);
    } else {
        if (fp->mv.kp.specials.b_held) {
            fp->mv.kp.specials.x4 = true;
            inlineA0(gobj);
            ftCo_800BCAF4(fp->victim_gobj);
        }
    }
}

void ftKp_SpecialSStart_Phys(Fighter_GObj* gobj)
{
    ft_800850B4(gobj);
}

void ftKp_SpecialAirSStart_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 vel_y = fp->self_vel.y;
    ft_80085134(gobj);
    fp->self_vel.y = vel_y;
    ftCommon_8007D4B8(fp);
}

void ftKp_SpecialSHit_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKp_SpecialAirSHit_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKp_SpecialSWait_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKp_SpecialAirSWait_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKp_SpecialSEndF_Phys(Fighter_GObj* gobj)
{
    ft_800850B4(gobj);
}

void ftKp_SpecialSEndB_Phys(Fighter_GObj* gobj)
{
    ft_800850B4(gobj);
}

void ftKp_SpecialAirSEndF_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKp_SpecialAirSEndB_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKp_SpecialSStart_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, ftKp_SpecialS_8013319C);
}

void ftKp_SpecialAirSStart_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, ftKp_SpecialS_8013322C);
}

void ftKp_SpecialSHit_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, ftKp_SpecialS_801332C4);
}

void ftKp_SpecialAirSHit_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, ftKp_SpecialS_80133324);
}

void ftKp_SpecialSWait_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, ftKp_SpecialS_80133398);
}

void ftKp_SpecialAirSWait_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, ftKp_SpecialS_801333F8);
}

void ftKp_SpecialSEndF_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, ftKp_SpecialS_80133484);
}

void ftKp_SpecialSEndB_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, ftKp_SpecialS_80133484);
}

void ftKp_SpecialAirSEndF_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, ftKp_SpecialS_801334E4);
}

void ftKp_SpecialAirSEndB_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, ftKp_SpecialS_8013359C);
}
