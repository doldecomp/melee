#include "ftPr_SpecialN.h"

#include <placeholder.h>

#include "forward.h"

#include "ft/chara/ftCommon/ftCo_Fall.h"
#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
#include "ft/chara/ftCommon/ftCo_Landing.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftPurin/ftPr_Init.h"
#include "ftPurin/types.h"
#include "MSL/trigf.h"

#include <common_structs.h>
#include <math.h>
#include <baselib/archive.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/objalloc.h>
#include <melee/cm/camera.h>
#include <melee/ef/efsync.h>
#include <melee/mp/mplib.h>

#define SIGNF(x) ((x) > 0.0f ? 1.0f : -1.0f)

static inline void ftPr_JObjSetRotationY(HSD_JObj* jobj, f32 y, f32* base)
{
    ((jobj) ? ((void) 0) : __assert("jobj.h", 660, "jobj"));
    ((!(jobj->flags & JOBJ_USE_QUATERNION))
         ? ((void) 0)
         : __assert("jobj.h", 661, (char*) &base[8]));
    jobj->rotate.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

void ftPr_SpecialS_8013D658(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObjSetScale(jobj, &fp->fv.pr.x2230);
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2 * fp->facing_dir);
    if (fp->mv.pr.specialn.facing_dir != 0) {
        fp->facing_dir = fp->mv.pr.specialn.facing_dir;
    }
    fp->mv.pr.specialn.facing_dir = 0;
}

void ftPr_SpecialS_8013D764(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 9) |
                          (1 << 18) | (1 << 19) | (1 << 22) | (1 << 26) |
                          (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    PAD_STACK(4);

    fp->mv.pr.specialn.xC = 0;
    switch (fp->motion_id) {
    case ftPr_MS_SpecialNRelease:
    case ftPr_MS_SpecialNTurn:
    case ftPr_MS_SpecialAirNChargeRelease:
    case ftPr_MS_SpecialAirNStartTurn:
        fp->mv.pr.specialn.x0 -= da->x38;
        fp->facing_dir = fp->mv.pr.specialn.x34.x;

        ftColl_8007AFF8(gobj);
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialNHit, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);

        fp->death2_cb = ftPr_SpecialS_8013D658;
        fp->take_dmg_cb = ftPr_SpecialS_8013D658;
        fp->deal_dmg_cb = NULL;

        if (fp->ground_or_air == GA_Ground) {
            fp->self_vel.x = fp->gr_vel * da->specialn_vel.x;
            ftCommon_8007D5D4(fp);
        } else {
            fp->self_vel.x *= da->specialn_vel.x;
        }

        fp->self_vel.y = da->specialn_vel.y;
        fp->x74_anim_vel.x = fp->x74_anim_vel.y = 0;
        fp->xE4_ground_accel_1 = 0;
        fp->gr_vel = 0;
        fp->mv.pr.specialn.facing_dir = 0;

        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
        ft_PlaySFX(fp, 250070, 127, 64);
    }
}

void ftPr_SpecialS_8013D8B0(Fighter_GObj* gobj)
{
    ft_80089824(gobj);
    ft_800892A0(gobj);
}

static inline void setupPurinCallbacks(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->death2_cb = ftPr_SpecialS_8013D658;
    fp->take_dmg_cb = ftPr_SpecialS_8013D658;
    fp->deal_dmg_cb = ftPr_SpecialS_8013D764;
    fp->x21F8 = ftPr_SpecialN_8014222C;
}

static inline void normalizeAndSetRollAngle(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    while (fp->mv.pr.specialn.x14 < 0.0f) {
        fp->mv.pr.specialn.x14 += M_PI * 2;
    }
    while (fp->mv.pr.specialn.x14 > M_PI * 2) {
        fp->mv.pr.specialn.x14 -= M_PI * 2;
    }
    ftPartSetRotX(fp, FtPart_YRotN, fp->mv.pr.specialn.x14);
}

void ftPr_SpecialS_8013D8E4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    HitCapsuleState state = fp->x914[0].state;
    f32 abs_vel;
    s32 damage;
    PAD_STACK(8);
    if (fp->ground_or_air == GA_Air) {
        abs_vel = fp->self_vel.x;
        if (abs_vel < 0.0f) {
            abs_vel = -abs_vel;
        }
    } else {
        abs_vel = fp->gr_vel;
        if (abs_vel < 0.0f) {
            abs_vel = -abs_vel;
        }
    }
    if (abs_vel < da->xCC) {
        fp->x914[0].state = HitCapsule_Disabled;
        ftCo_800BFFAC(fp);
    } else if (state == HitCapsule_Disabled) {
        fp->x914[0].state = HitCapsule_Enabled;
    }
    if (fp->x914[0].state != HitCapsule_Disabled) {
        if (fp->ground_or_air == GA_Air) {
            abs_vel = fp->self_vel.x;
            if (abs_vel < 0.0f) {
                abs_vel = -abs_vel;
            }
            damage = da->x84 * (da->x80 + abs_vel);
        } else {
            abs_vel = fp->gr_vel;
            if (abs_vel < 0.0f) {
                abs_vel = -abs_vel;
            }
            damage = da->x84 * (da->x80 + abs_vel);
        }
        if (damage < 1) {
            damage = 1;
        }
        ftColl_8007ABD0(&fp->x914[0], damage, gobj);
    }
}

void ftPr_SpecialS_8013DA24(HSD_GObj* gobj, bool is_air, MotionFlags flags,
                            float anim_start)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    fp->facing_dir = fp->mv.pr.specialn.x34.x;
    ftColl_8007AFF8(gobj);
    if (!is_air) {
        int msid;
        if (fp->facing_dir == 1) {
            msid = ftPr_MS_SpecialNEndR;
        } else {
            msid = ftPr_MS_SpecialNEndL;
        }
        Fighter_ChangeMotionState(gobj, msid, flags, anim_start, 1, 0, NULL);
        fp->gr_vel *= da->x90;
        fp->x74_anim_vel.y = 0;
        fp->self_vel.y = 0;
    } else {
        int msid;
        if (fp->facing_dir == 1) {
            msid = ftPr_MS_SpecialAirNEndR;
        } else {
            msid = ftPr_MS_SpecialAirNEndL;
        }
        Fighter_ChangeMotionState(gobj, msid, flags, anim_start, 1, 0, NULL);
        fp->self_vel.x *= da->x90;
        fp->self_vel.y *= da->x94;
        fp->xE4_ground_accel_1 = 0;
        fp->gr_vel = 0;
    }
    setupPurinCallbacks(gobj);
    ftPr_SpecialS_8013D658(gobj);
    fp->mv.pr.specialn.facing_dir = 0;
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2 * fp->facing_dir);
}

void ftPr_SpecialS_8013DC64(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    HSD_JObjGetScale(jobj, &fp->fv.pr.x2230);
    fp->gr_vel = 0;
    fp->mv.pr.specialn.x0 = da->x34;
    fp->mv.pr.specialn.x4 = -1;
    fp->mv.pr.specialn.x8 = -1;
    fp->mv.pr.specialn.xC = 0;
    fp->mv.pr.specialn.x14 = 0;
    fp->mv.pr.specialn.x34.y = 0;
    fp->mv.pr.specialn.facing_dir = 0;
    fp->mv.pr.specialn.x24 = 0;
    fp->mv.pr.specialn.x28 = 0;
    fp->mv.pr.specialn.x2C = da->xA0;
    fp->mv.pr.specialn.x30 = 0;
    fp->deal_dmg_cb = ftPr_SpecialS_8013D764;
    fp->x21F8 = ftPr_SpecialN_8014222C;
}

static inline void playRollSFX(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int sfx_id;
    if (fp->ground_or_air == GA_Air) {
        sfx_id = 250067;
    } else {
        sfx_id = 250064;
    }
    ft_80088510(fp, sfx_id, 127, 64);
}

static inline void scaleAnimStep(HSD_GObj* gobj, Vec3* scale)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    int frame = fp->mv.pr.specialn.x8;
    if (frame >= 0 && frame < 4) {
        scale->x = fp->fv.pr.x2230.x;
        scale->y = fp->fv.pr.x2230.y * ftPr_Init_803D05C8[frame];
        scale->z = fp->fv.pr.x2230.z * ftPr_Init_803D05D8[frame];
        HSD_JObjSetScale(jobj, scale);
        fp->mv.pr.specialn.x8 += 1;
    } else {
        HSD_JObjSetScale(jobj, &fp->fv.pr.x2230);
    }
}

static inline void hitCapsuleToggle(HSD_GObj* gobj)
{
    ftPurinAttributes* da;
    Fighter* fp = GET_FIGHTER(gobj);
    da = fp->dat_attrs;
    fp->mv.pr.specialn.xC += 1;
    if (fp->mv.pr.specialn.xC >= da->x9C &&
        fp->x914[0].state != HitCapsule_Disabled)
    {
        fp->x914[0].x4 = (fp->x914[0].x4 + 1) & 1;
        fp->mv.pr.specialn.xC = 0;
    }
}

void ftPr_SpecialS_8013DD54(HSD_GObj* gobj, bool arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    while (fp->mv.pr.specialn.x14 < 0.0f) {
        fp->mv.pr.specialn.x14 += M_PI * 2;
    }
    while (fp->mv.pr.specialn.x14 > M_PI * 2) {
        fp->mv.pr.specialn.x14 -= M_PI * 2;
    }
    if (fp->mv.pr.specialn.x34.y == 0.0f) {
        playRollSFX(gobj);
    } else {
        if (fp->mv.pr.specialn.x34.x == ((arg1) ? -1.0f : 1.0f)) {
            if (fp->mv.pr.specialn.x14 < fp->mv.pr.specialn.x34.y) {
                playRollSFX(gobj);
            }
        } else if (fp->mv.pr.specialn.x14 > fp->mv.pr.specialn.x34.y) {
            playRollSFX(gobj);
        }
    }
    fp->mv.pr.specialn.x34.y = fp->mv.pr.specialn.x14;
}

void ftPr_SpecialN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    PAD_STACK(4 * 4);
    fp->mv.pr.specialn.x34.x = fp->facing_dir;
    {
        int msid;
        if (fp->mv.pr.specialn.x34.x == 1) {
            msid = ftPr_MS_SpecialNStartR;
        } else {
            msid = ftPr_MS_SpecialNStartL;
        }
        Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0, NULL);
    }
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    ftAnim_8006EBA4(gobj);
    ftPr_SpecialS_8013DC64(gobj);
    fp->x74_anim_vel.y = 0;
    fp->self_vel.y = 0;
    fp->mv.pr.specialn.x1C = da->x44;
}

void ftPr_SpecialAirN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    PAD_STACK(4 * 4);
    fp->mv.pr.specialn.x34.x = fp->facing_dir;
    {
        int msid;
        if (fp->mv.pr.specialn.x34.x == 1) {
            msid = ftPr_MS_SpecialAirNStartR;
        } else {
            msid = ftPr_MS_SpecialAirNStartL;
        }
        Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0, NULL);
    }
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    ftAnim_8006EBA4(gobj);
    ftPr_SpecialS_8013DC64(gobj);
    fp->x74_anim_vel.y = da->x3C;
    fp->mv.pr.specialn.x1C = da->x54;
}

void ftPr_SpecialNStart_Anim(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 18);
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    fp->mv.pr.specialn.facing_dir = 0;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialNLoop, mf, 0, 0, 0,
                                  NULL);
        setupPurinCallbacks(gobj);
        fp->cur_anim_frame = 0;
        ftAnim_SetAnimRate(gobj, 0);
        fp->gr_vel = fp->self_vel.x = fp->facing_dir * 0.0001f;
        fp->xE4_ground_accel_1 = fp->x74_anim_vel.x = 0;
        ftPartSetRotY(fp, 0, M_PI_2);
    }
}

void ftPr_SpecialNLoop_Anim(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 9) |
                          (1 << 18) | (1 << 19) | (1 << 22) | (1 << 26) |
                          (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    ftPr_SpecialS_8013DD54(gobj, false);
    fp->mv.pr.specialn.facing_dir = 0;
    fp->mv.pr.specialn.x2C += da->xA8;
    if (fp->mv.pr.specialn.x2C >= da->xA4) {
        fp->mv.pr.specialn.x2C = da->xA4;
        if (fp->mv.pr.specialn.x30 == 0) {
            ftCo_800BFFD0(fp, 5, 0);
        }
        fp->mv.pr.specialn.x30 = 1;
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialNFull, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
    }
    fp->mv.pr.specialn.x14 +=
        fp->mv.pr.specialn.x34.x *
        (fp->mv.pr.specialn.x2C * (deg_to_rad * da->xAC));
    normalizeAndSetRollAngle(gobj);
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
}

void ftPr_SpecialNFull_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    ftPr_SpecialS_8013DD54(gobj, false);
    fp->mv.pr.specialn.facing_dir = 0;
    fp->mv.pr.specialn.x2C += da->xA8;
    if (fp->mv.pr.specialn.x2C >= da->xA4) {
        fp->mv.pr.specialn.x2C = da->xA4;
        fp->mv.pr.specialn.x30 = 1;
    }
    fp->mv.pr.specialn.x14 +=
        fp->mv.pr.specialn.x34.x *
        (fp->mv.pr.specialn.x2C * (deg_to_rad * da->xAC));
    normalizeAndSetRollAngle(gobj);
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
}

void ftPr_SpecialNRelease_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    Vec3 scale;
    PAD_STACK(16);
    ftPr_SpecialS_8013DD54(gobj, false);
    fp->mv.pr.specialn.facing_dir = 0;
    scaleAnimStep(gobj, &scale);
    hitCapsuleToggle(gobj);
    ftPr_SpecialS_8013D8E4(gobj);
    {
        f32 old_angle = fp->mv.pr.specialn.x14;
        f32 delta = deg_to_rad * fp->mv.pr.specialn.x2C *
                    (f32) (0.2 * da->x98 * fp->mv.pr.specialn.x34.x);
        fp->mv.pr.specialn.x14 = old_angle + delta;
        normalizeAndSetRollAngle(gobj);
        fp->mv.pr.specialn.x0 -= 1;
        if (fp->mv.pr.specialn.x0 <= 0) {
            if (M_PI_2 < fp->mv.pr.specialn.x14 &&
                fp->mv.pr.specialn.x14 < M_PI_2 * 3)
            {
                if (delta > 0.0f) {
                    if (fp->mv.pr.specialn.x14 > M_PI && old_angle < M_PI) {
                        fp->mv.pr.specialn.x0 = 0;
                        ftPr_SpecialS_8013DA24(gobj, false, 0x40012, 0);
                        return;
                    }
                    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
                    return;
                }
                if (fp->mv.pr.specialn.x14 < M_PI && old_angle > M_PI) {
                    fp->mv.pr.specialn.x0 = 0;
                    ftPr_SpecialS_8013DA24(gobj, false, 0x40012, 0);
                    return;
                }
                ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
                return;
            }
            ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
            return;
        }
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
    }
}

void ftPr_SpecialNTurn_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    f32 angle;
    Vec3 scale;
    PAD_STACK(8);
    ftPr_SpecialS_8013DD54(gobj, true);
    scaleAnimStep(gobj, &scale);
    fp->mv.pr.specialn.x14 += 0.2 * da->x6C * -fp->mv.pr.specialn.x34.x;
    normalizeAndSetRollAngle(gobj);
    fp->mv.pr.specialn.x0 -= 1;
    if (fp->mv.pr.specialn.x0 <= 0) {
        fp->mv.pr.specialn.x0 = 0;
        fp->mv.pr.specialn.x34.x = -fp->mv.pr.specialn.x34.x;
        ftPr_SpecialS_8013DA24(gobj, false, 0x40012, 0);
        return;
    }
    if ((fp->mv.pr.specialn.x24 % da->x70) == 0) {
        angle = atan2f(-fp->coll_data.floor.normal.x,
                       fp->coll_data.floor.normal.y);
        efSync_Spawn(0x3FF, gobj, &fp->cur_pos, &fp->facing_dir, &angle);
    }
    fp->mv.pr.specialn.x24 += 1;
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
}

void ftPr_SpecialNEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 scale;
    fp->mv.pr.specialn.facing_dir = 0;
    scaleAnimStep(gobj, &scale);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftPr_SpecialS_8013D658(gobj);
        ft_8008A2BC(gobj);
    }
}

void ftPr_SpecialAirNStart_Anim(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 18);
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    fp->mv.pr.specialn.facing_dir = 0;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirNChargeLoop, mf, 0,
                                  0, 0, NULL);
        setupPurinCallbacks(gobj);
        fp->cur_anim_frame = 0;
        ftAnim_SetAnimRate(gobj, 0);
        fp->self_vel.x = fp->facing_dir * 0.0001f;
        fp->x74_anim_vel.x = 0;
        ftPartSetRotY(fp, 0, M_PI_2);
    }
}
void ftPr_SpecialAirNChargeLoop_Anim(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 9) |
                          (1 << 18) | (1 << 19) | (1 << 22) | (1 << 26) |
                          (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    ftPr_SpecialS_8013DD54(gobj, false);
    fp->mv.pr.specialn.facing_dir = 0;
    fp->mv.pr.specialn.x2C += da->xA8;
    if (fp->mv.pr.specialn.x2C >= da->xA4) {
        fp->mv.pr.specialn.x2C = da->xA4;
        if (fp->mv.pr.specialn.x30 == 0) {
            ftCo_800BFFD0(fp, 5, 0);
        }
        fp->mv.pr.specialn.x30 = 1;
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirNChargeFull, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
    }
    fp->mv.pr.specialn.x14 +=
        fp->mv.pr.specialn.x34.x *
        (fp->mv.pr.specialn.x2C * (deg_to_rad * da->xAC));
    normalizeAndSetRollAngle(gobj);
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
}

void ftPr_SpecialAirNChargeFull_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    ftPr_SpecialS_8013DD54(gobj, false);
    fp->mv.pr.specialn.facing_dir = 0;
    fp->mv.pr.specialn.x2C += da->xA8;
    if (fp->mv.pr.specialn.x2C >= da->xA4) {
        fp->mv.pr.specialn.x2C = da->xA4;
        fp->mv.pr.specialn.x30 = 1;
    }
    fp->mv.pr.specialn.x14 +=
        fp->mv.pr.specialn.x34.x *
        (fp->mv.pr.specialn.x2C * (deg_to_rad * da->xAC));
    normalizeAndSetRollAngle(gobj);
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
}

static inline void ftPr_SpecialAirNChargeRelease_Anim_inline(HSD_GObj* gobj,
                                                             Vec3* scale,
                                                             f32* scale_base)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    s32 frame = fp->mv.pr.specialn.x8;
    if (frame >= 0 && frame < 4) {
        scale->x = fp->fv.pr.x2230.x;
        scale->y = fp->fv.pr.x2230.y * scale_base[frame];
        scale->z = fp->fv.pr.x2230.z * scale_base[frame + 4];
        HSD_JObjSetScale(jobj, scale);
        fp->mv.pr.specialn.x8 += 1;
    } else {
        HSD_JObjSetScale(jobj, &fp->fv.pr.x2230);
    }
}

void ftPr_SpecialAirNChargeRelease_Anim(HSD_GObj* gobj)
{
    f32* scale_base = ftPr_Init_803D05C8;
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    Vec3 scale;
    f32 prev_angle;
    f32 delta;
    PAD_STACK(16);

    ftPr_SpecialS_8013DD54(gobj, false);
    fp->mv.pr.specialn.facing_dir = 0;
    ftPr_SpecialAirNChargeRelease_Anim_inline(gobj, &scale, scale_base);

    hitCapsuleToggle(gobj);
    ftPr_SpecialS_8013D8E4(gobj);
    prev_angle = fp->mv.pr.specialn.x14;
    delta = (f32) (0.2 * da->x98 * fp->mv.pr.specialn.x34.x) *
            (0.017453292f * fp->mv.pr.specialn.x2C * da->xBC);
    fp->mv.pr.specialn.x14 += delta;
    normalizeAndSetRollAngle(gobj);
    fp->mv.pr.specialn.x0--;
    if (fp->mv.pr.specialn.x0 <= 0) {
        if (M_PI_2 < fp->mv.pr.specialn.x14 &&
            fp->mv.pr.specialn.x14 < M_PI_2 * 3)
        {
            if (delta > 0.0f) {
                if (fp->mv.pr.specialn.x14 > M_PI && prev_angle < M_PI) {
                    fp->mv.pr.specialn.x0 = 0;
                    ftPr_SpecialS_8013DA24(gobj, true, 0x40012, 0);
                    return;
                }
                ftPr_JObjSetRotationY(fp->parts[FtPart_TopN].joint, M_PI_2,
                                      scale_base);
                return;
            }
            if (fp->mv.pr.specialn.x14 < M_PI && prev_angle > M_PI) {
                fp->mv.pr.specialn.x0 = 0;
                ftPr_SpecialS_8013DA24(gobj, true, 0x40012, 0);
                return;
            }
            ftPr_JObjSetRotationY(fp->parts[FtPart_TopN].joint, M_PI_2,
                                  scale_base);
            return;
        }
        ftPr_JObjSetRotationY(fp->parts[FtPart_TopN].joint, M_PI_2,
                              scale_base);
        return;
    }
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
}

void ftPr_SpecialAirNStartTurn_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    Vec3 scale;
    PAD_STACK(4);
    ftPr_SpecialS_8013DD54(gobj, true);
    scaleAnimStep(gobj, &scale);
    fp->mv.pr.specialn.x14 +=
        da->xBC * (f32) (0.2 * da->x6C * -fp->mv.pr.specialn.x34.x);
    normalizeAndSetRollAngle(gobj);
    fp->mv.pr.specialn.x0 -= 1;
    if (fp->mv.pr.specialn.x0 <= 0) {
        fp->mv.pr.specialn.x0 = 0;
        fp->mv.pr.specialn.x34.x = -fp->mv.pr.specialn.x34.x;
        ftPr_SpecialS_8013DA24(gobj, false, 0x40012, 0);
        return;
    }
    fp->mv.pr.specialn.x24 += 1;
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
}

void ftPr_SpecialAirNEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    u8 _[16];
    Vec3 scale;
    PAD_STACK(4);
    fp->mv.pr.specialn.facing_dir = 0;
    scaleAnimStep(gobj, &scale);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftPr_SpecialS_8013D658(gobj);
        if (da->xD8 == 0.0f) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1.0f, da->xD8);
        }
    }
}

void ftPr_SpecialNHit_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    u8 _[12];
    Vec3 scale;
    PAD_STACK(4);
    scaleAnimStep(gobj, &scale);
    fp->mv.pr.specialn.x14 +=
        da->xBC * (f32) (0.2 * da->x6C * -fp->mv.pr.specialn.x34.x);
    normalizeAndSetRollAngle(gobj);
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
}

void ftPr_SpecialNStart_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialNLoop_IASA(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf =
        (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) | (1 << 18);
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    if (!(fp->input.held_inputs & 0x200)) {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialNRelease, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
        setupPurinCallbacks(gobj);
        ftAnim_8006EBA4(gobj);
        fp->gr_vel = fp->mv.pr.specialn.x34.x *
                     (da->xC0 * (fp->mv.pr.specialn.x2C - da->xA0));
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
        normalizeAndSetRollAngle(gobj);
        ft_PlaySFX(fp, 250073, 127, 64);
    }
}

void ftPr_SpecialNFull_IASA(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf =
        (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) | (1 << 18);
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    if (!(fp->input.held_inputs & 0x200)) {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialNRelease, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
        setupPurinCallbacks(gobj);
        ftAnim_8006EBA4(gobj);
        fp->gr_vel = fp->mv.pr.specialn.x34.x *
                     (da->xC0 * (fp->mv.pr.specialn.x2C - da->xA0));
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
        normalizeAndSetRollAngle(gobj);
        ft_PlaySFX(fp, 250073, 127, 64);
    }
}

void ftPr_SpecialNRelease_IASA(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 9) |
                          (1 << 18) | (1 << 19) | (1 << 22) | (1 << 26) |
                          (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    f32 dir;
    if (ABS(fp->input.lstick.x) > da->x68) {
        dir = SIGNF(fp->input.lstick.x);
        if (fp->mv.pr.specialn.x34.x != dir) {
            ftColl_8007AFF8(gobj);
            fp->mv.pr.specialn.facing_dir = dir;
            fp->mv.pr.specialn.x34.x = -dir;
            Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialNTurn, mf,
                                      fp->cur_anim_frame, 0, 0, NULL);
            setupPurinCallbacks(gobj);
            fp->mv.pr.specialn.x10 = fp->gr_vel;
            fp->mv.pr.specialn.x1C = -0.05f * fp->gr_vel;
            fp->mv.pr.specialn.x24 = 0;
            normalizeAndSetRollAngle(gobj);
            ft_PlaySFX(fp, 250073, 127, 64);
        }
    }
}

void ftPr_SpecialNTurn_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialNEnd_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialAirNStart_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialAirNChargeLoop_IASA(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf =
        (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) | (1 << 18);
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    if (!(fp->input.held_inputs & 0x200)) {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirNChargeRelease, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
        setupPurinCallbacks(gobj);
        ftAnim_8006EBA4(gobj);
        fp->self_vel.x = fp->mv.pr.specialn.x34.x *
                         (da->xC0 * (fp->mv.pr.specialn.x2C - da->xA0));
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
        normalizeAndSetRollAngle(gobj);
        ft_PlaySFX(fp, 250073, 127, 64);
    }
}

void ftPr_SpecialAirNChargeFull_IASA(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf =
        (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) | (1 << 18);
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    if (!(fp->input.held_inputs & 0x200)) {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirNChargeRelease, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
        setupPurinCallbacks(gobj);
        ftAnim_8006EBA4(gobj);
        fp->self_vel.x = fp->mv.pr.specialn.x34.x *
                         (da->xC0 * (fp->mv.pr.specialn.x2C - da->xA0));
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
        normalizeAndSetRollAngle(gobj);
        ft_PlaySFX(fp, 250073, 127, 64);
    }
}

void ftPr_SpecialAirNChargeRelease_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialAirNStartTurn_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialAirNEnd_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialNHit_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialNStart_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->xE4_ground_accel_1 = 0;
    fp->gr_vel = 0;
    fp->self_vel.x = fp->facing_dir * 0.0001f;
    fp->self_vel.y = 0;
    fp->x74_anim_vel.y = 0;
    fp->x74_anim_vel.x = 0;
}

void ftPr_SpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ftPr_SpecialNStart_Phys(gobj);
}

void ftPr_SpecialNFull_Phys(Fighter_GObj* gobj)
{
    ftPr_SpecialNStart_Phys(gobj);
}

void ftPr_SpecialNRelease_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    f32 slope = fp->coll_data.floor.normal.x;
    u8 __[8];
    f32 base_vel = fp->mv.pr.specialn.x34.x *
                   (da->xC0 * (fp->mv.pr.specialn.x2C - da->xB8));
    {
        f32 influence = da->xC8 * (base_vel * ABS(slope));
        if (fp->coll_data.floor.normal.x > 0.0f) {
            if (fp->mv.pr.specialn.x1C > 0.0f) {
                fp->gr_vel = base_vel + influence;
            } else {
                fp->gr_vel = base_vel + influence;
            }
        } else if (fp->mv.pr.specialn.x1C > 0.0f) {
            fp->gr_vel = base_vel - influence;
        } else {
            fp->gr_vel = base_vel - influence;
        }
    }
    {
        f32 max_vel;
        if (ABS(fp->gr_vel) > (max_vel = da->x4C)) {
            if (fp->gr_vel < 0.0f) {
                max_vel = -max_vel;
            }
            fp->gr_vel = max_vel;
        }
    }
    {
        f32 max_vel;
        if (ABS(fp->gr_vel) > (max_vel = da->x50)) {
            if (fp->gr_vel < 0.0f) {
                max_vel = -max_vel;
            }
            fp->gr_vel = max_vel;
        }
    }
    fp->mv.pr.specialn.x18 = ABS(fp->gr_vel);
    fp->x74_anim_vel.y = 0;
    fp->self_vel.y = 0;
    ftCommon_ApplyGroundMovement(gobj);
    fp->mv.pr.specialn.x2C -= da->xB4;
    if (fp->mv.pr.specialn.x2C < da->xB8) {
        ftPr_SpecialS_8013DA24(gobj, false, 0x40012, 0);
    }
}

static inline void setFacingDir(Fighter* fp)
{
    if (fp->mv.pr.specialn.facing_dir != 0.0f) {
        fp->mv.pr.specialn.x34.x = fp->facing_dir =
            fp->mv.pr.specialn.facing_dir;
    }
    fp->mv.pr.specialn.facing_dir = 0.0f;
    fp->mv.pr.specialn.xC = 0;
}

void ftPr_SpecialNTurn_Phys(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf1 = (1 << 4) | (1 << 18) | (1 << 25);
    static u32 const mf2 = (1 << 1) | (1 << 4) | (1 << 18) | (1 << 25);
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    f32 scale = da->xC4 * mpLib_800569EC(fp->coll_data.floor.flags);
    f32 slope = ABS(fp->coll_data.floor.normal.x);
    f32 x1C = fp->mv.pr.specialn.x1C;
    f32 influence = da->xC8 * (x1C * slope);
    if (fp->coll_data.floor.normal.x > 0.0f) {
        if (x1C > 0.0f) {
            fp->gr_vel += scale * (x1C + influence);
        } else {
            fp->gr_vel += scale * (x1C + influence);
        }
    } else {
        if (x1C > 0.0f) {
            fp->gr_vel += scale * (x1C - influence);
        } else {
            fp->gr_vel += scale * (x1C - influence);
        }
    }
    fp->x74_anim_vel.y = 0;
    fp->self_vel.y = 0;
    ftCommon_ApplyGroundMovement(gobj);
    if (fp->mv.pr.specialn.x10 > 0.0f) {
        if (fp->gr_vel < 0.0f) {
            if (ABS(fp->gr_vel) >= ABS(fp->mv.pr.specialn.x10 * da->xD0)) {
                fp->x21EC = ftPr_SpecialS_8013D8B0;
                Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialNRelease, mf1,
                                          fp->cur_anim_frame, 0.0f, 0.0f,
                                          NULL);
                setupPurinCallbacks(gobj);
                setFacingDir(fp);
            }
        }
    } else {
        if (fp->gr_vel > 0.0f) {
            if (ABS(fp->gr_vel) >= ABS(fp->mv.pr.specialn.x10 * da->xD0)) {
                fp->x21EC = ftPr_SpecialS_8013D8B0;
                Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialNRelease, mf2,
                                          fp->cur_anim_frame, 0.0f, 0.0f,
                                          NULL);
                setupPurinCallbacks(gobj);
                setFacingDir(fp);
            }
        }
    }
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
    normalizeAndSetRollAngle(gobj);
}

void ftPr_SpecialNEnd_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_ApplyFrictionGround(fp, fp->co_attrs.gr_friction);
    ftCommon_ApplyGroundMovement(gobj);
}

void ftPr_SpecialAirNStart_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    ftCommon_Fall(fp, da->x3C, da->x40);
}

void ftPr_SpecialAirNChargeLoop_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    ftCommon_Fall(fp, da->x3C, da->x40);
}

void ftPr_SpecialAirNChargeFull_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    ftCommon_Fall(fp, da->x3C, da->x40);
}

void ftPr_SpecialAirNChargeRelease_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    PAD_STACK(4 * 4);
    fp->self_vel.x = fp->mv.pr.specialn.x34.x *
                     (da->xC0 * (fp->mv.pr.specialn.x2C - da->xB8));
    {
        f32 decel;
        if (fp->self_vel.x > 0.0f) {
            decel = da->x58;
        } else {
            decel = -da->x58;
        }
        fp->self_vel.x -= decel;
    }
    {
        f32 vel = fp->self_vel.x;
        f32 min_vel;
        if (ABS(vel) < (min_vel = da->x5C)) {
            if (vel < 0.0f) {
                min_vel = -min_vel;
            }
            fp->self_vel.x = min_vel;
        }
    }
    fp->mv.pr.specialn.x18 = ABS(fp->self_vel.x);
    ftCommon_Fall(fp, da->x3C, da->x40);
    fp->mv.pr.specialn.x2C -= da->xB4;
    if (fp->mv.pr.specialn.x2C < da->xB8) {
        ftPr_SpecialS_8013DA24(gobj, true, 0x40012, 0);
    }
}

void ftPr_SpecialAirNStartTurn_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    f32 var_f1;
    if (fp->self_vel.x > 0.0f) {
        var_f1 = da->x58;
    } else {
        var_f1 = -da->x58;
    }
    fp->self_vel.x -= var_f1;
    {
        f32 vel = fp->self_vel.x;
        f32 min_vel;
        if (ABS(vel) < (min_vel = da->x5C)) {
            if (vel < 0.0f) {
                min_vel = -min_vel;
            }
            fp->self_vel.x = min_vel;
        }
    }
    ftCommon_Fall(fp, da->x3C, da->x40);
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
    normalizeAndSetRollAngle(gobj);
}

void ftPr_SpecialAirNEnd_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    ftCommon_Fall(fp, da->x3C, da->x40);
}

void ftPr_SpecialNHit_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    PAD_STACK(4 * 2);

    if (fp->self_vel.y <= -da->x40) {
        ftCommon_8007D268(fp);
    }
    ftCommon_Fall(fp, da->x3C, da->x40);
}

void ftPr_SpecialNStart_Coll(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        {
            int msid;
            if (fp->mv.pr.specialn.x34.x == 1) {
                msid = ftPr_MS_SpecialAirNStartR;
            } else {
                msid = ftPr_MS_SpecialAirNStartL;
            }
            Fighter_ChangeMotionState(gobj, msid, mf, fp->cur_anim_frame, 1, 0,
                                      NULL);
        }
        {
            Fighter* fp = GET_FIGHTER(gobj);
            fp->death2_cb = ftPr_SpecialS_8013D658;
            fp->take_dmg_cb = ftPr_SpecialS_8013D658;
            fp->deal_dmg_cb = ftPr_SpecialS_8013D764;
            fp->x21F8 = ftPr_SpecialN_8014222C;
        }
    }
}

void ftPr_SpecialNLoop_Coll(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf =
        (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) | (1 << 18);
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirNChargeLoop, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
        setupPurinCallbacks(gobj);
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
        normalizeAndSetRollAngle(gobj);
    }
}

void ftPr_SpecialNFull_Coll(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf =
        (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) | (1 << 18);
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirNChargeFull, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
        setupPurinCallbacks(gobj);
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
        normalizeAndSetRollAngle(gobj);
    }
}

static inline void wallBounceEffect(HSD_GObj* gobj, Fighter* fp, f32 dir,
                                    Vec3* pos, f32* angle)
{
    Fighter* fp2 = GET_FIGHTER(gobj);
    *pos = fp2->cur_pos;
    *angle = atan2f(-fp->coll_data.left_facing_wall.normal.x * dir,
                    fp->coll_data.left_facing_wall.normal.y);
    if (dir > 0.0f) {
        pos->x += ABS(fp2->coll_data.ecb.right.x);
    } else {
        pos->x -= ABS(fp2->coll_data.ecb.left.x);
    }
    pos->y +=
        0.5f * ABS(fp2->coll_data.ecb.top.y + fp2->coll_data.ecb.bottom.y);
    efSync_Spawn(0x406, gobj, pos, angle);
    Camera_80030E44(3, pos);
    ftCommon_8007EBAC(fp2, 0xC, 0xA);
    ft_PlaySFX(fp2, 250070, 127, 64);
}

void ftPr_SpecialNRelease_Coll(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 3) | (1 << 4) | (1 << 7) |
                          (1 << 12) | (1 << 14) | (1 << 18) | (1 << 19) |
                          (1 << 22) | (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    bool coll = ft_80082888(gobj, &ftPr_Init_803D0610);
    bool wall_hit;

    if (fp->mv.pr.specialn.x34.x == 1.0f) {
        wall_hit = fp->coll_data.env_flags & 0x3F;
        if (wall_hit) {
            Vec3 pos;
            f32 angle;
            wallBounceEffect(gobj, fp, 1.0f, &pos, &angle);
        }
    } else {
        wall_hit = fp->coll_data.env_flags & 0xFC0;
        if (wall_hit) {
            Vec3 pos;
            f32 angle;
            wallBounceEffect(gobj, fp, -1.0f, &pos, &angle);
        }
    }

    if (wall_hit) {
        u8 _pad[4];
        fp->mv.pr.specialn.x2C *= da->xD4;
        if (fp->mv.pr.specialn.x2C < 0) {
            fp->mv.pr.specialn.x2C = 0;
        }
        fp->mv.pr.specialn.x18 *= da->xD4;
        fp->gr_vel = -fp->gr_vel * da->xD4;
        fp->self_vel.x = -fp->self_vel.x * da->xD4;
        fp->mv.pr.specialn.x34.x = SIGNF(fp->gr_vel);
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
    }

    if (!coll) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirNChargeRelease, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
        setupPurinCallbacks(gobj);
        normalizeAndSetRollAngle(gobj);
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
        fp->mv.pr.specialn.x1C = da->x54;
    }
}

void ftPr_SpecialNTurn_Coll(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    f32 abs_vel = fp->gr_vel;
    ftPurinAttributes* da = fp->dat_attrs;
    bool coll;
    PAD_STACK(8);
    if (abs_vel < 0.0f) {
        abs_vel = -abs_vel;
    }
    if (abs_vel > da->x74) {
        coll = ft_80082888(gobj, &ftPr_Init_803D0610);
    } else {
        coll = ft_80082978(gobj, &ftPr_Init_803D0610);
    }
    if (!coll) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirNStartTurn, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
        setupPurinCallbacks(gobj);
    }
}

void ftPr_SpecialNEnd_Coll(Fighter_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        ftPr_SpecialS_8013DA24(gobj, true, mf, fp->cur_anim_frame);
    }
}

void ftPr_SpecialAirNStart_Coll(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        {
            int msid;
            if (fp->mv.pr.specialn.x34.x == 1) {
                msid = ftPr_MS_SpecialNStartR;
            } else {
                msid = ftPr_MS_SpecialNStartL;
            }
            Fighter_ChangeMotionState(gobj, msid, mf, fp->cur_anim_frame, 1, 0,
                                      NULL);
        }
        setupPurinCallbacks(gobj);
    }
}

void ftPr_SpecialAirNChargeLoop_Coll(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf =
        (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) | (1 << 18);
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialNLoop, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
        setupPurinCallbacks(gobj);
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
        normalizeAndSetRollAngle(gobj);
    }
}

void ftPr_SpecialAirNChargeFull_Coll(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf =
        (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) | (1 << 18);
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialNFull, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
        setupPurinCallbacks(gobj);
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
        normalizeAndSetRollAngle(gobj);
    }
}

static inline void ftPr_SpecialAirNChargeRelease_Coll_inline(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObjSetScale(jobj, &fp->fv.pr.x2230);
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2 * fp->facing_dir);
    if (fp->mv.pr.specialn.facing_dir != 0) {
        fp->facing_dir = fp->mv.pr.specialn.facing_dir;
    }
    fp->mv.pr.specialn.facing_dir = 0;
    ftCliffCommon_80081370(gobj);
}

void ftPr_SpecialAirNChargeRelease_Coll(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 3) | (1 << 4) | (1 << 7) |
                          (1 << 12) | (1 << 14) | (1 << 18) | (1 << 19) |
                          (1 << 22) | (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    bool coll;
    int wall_hit;
    f32 land_angle;

    if (fp->mv.pr.specialn.x34.x == 1.0f) {
        coll = ft_8008239C(gobj, 1, &ftPr_Init_803D0610);
    } else {
        coll = ft_8008239C(gobj, -1, &ftPr_Init_803D0610);
    }

    if (fp->mv.pr.specialn.x34.x == 1.0f) {
        wall_hit = fp->coll_data.env_flags & 0x3F;
        if (wall_hit) {
            {
                Vec3 pos;
                f32 angle;
                wallBounceEffect(gobj, fp, 1.0f, &pos, &angle);
            }
        }
    } else {
        wall_hit = fp->coll_data.env_flags & 0xFC0;
        if (wall_hit) {
            {
                Vec3 pos;
                f32 angle;
                wallBounceEffect(gobj, fp, -1.0f, &pos, &angle);
            }
        }
    }

    if (wall_hit) {
        fp->mv.pr.specialn.x2C *= da->xD4;
        if (fp->mv.pr.specialn.x2C < 0) {
            fp->mv.pr.specialn.x2C = 0;
        }
        fp->mv.pr.specialn.x18 *= da->xD4;
        fp->self_vel.x = -fp->self_vel.x * da->xD4;
        fp->mv.pr.specialn.x34.x = -fp->mv.pr.specialn.x34.x;
    }

    if (coll) {
        f32 vel_y = ABS(fp->self_vel.y * da->x78);
        fp->self_vel.y = vel_y;
        if (vel_y < da->x7C) {
            ftCommon_8007D7FC(fp);
            Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialNRelease, mf,
                                      fp->cur_anim_frame, 0, 0, NULL);
            setupPurinCallbacks(gobj);
            {
                f32 vel = fp->mv.pr.specialn.x18 * fp->mv.pr.specialn.x34.x;
                fp->gr_vel = vel;
                fp->self_vel.x = vel;
            }
            fp->self_vel.z = 0;
            fp->self_vel.y = 0;
            normalizeAndSetRollAngle(gobj);
            ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
            land_angle = atan2f(-fp->coll_data.floor.normal.x,
                                fp->coll_data.floor.normal.y);
            efSync_Spawn(0x3FF, gobj, &fp->cur_pos, &fp->facing_dir,
                         &land_angle);
            fp->mv.pr.specialn.x1C = da->x44;
        } else {
            if (ABS(fp->input.lstick.x) > da->x68) {
                f32 dir = SIGNF(fp->input.lstick.x);
                fp->mv.pr.specialn.x34.x = dir;
                fp->self_vel.x = fp->gr_vel =
                    fp->mv.pr.specialn.x18 * fp->mv.pr.specialn.x34.x;
                ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
            }
            normalizeAndSetRollAngle(gobj);
        }
        fp->mv.pr.specialn.x8 = 0;
        return;
    }

    if (ftCliffCommon_80081298(gobj)) {
        ftPr_SpecialAirNChargeRelease_Coll_inline(gobj);
    }
}

void ftPr_SpecialAirNStartTurn_Coll(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (ft_800824A0(gobj, &ftPr_Init_803D0610)) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialNTurn, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
        setupPurinCallbacks(gobj);
        fp->gr_vel = fp->self_vel.x;
        fp->self_vel.z = 0;
        fp->self_vel.y = 0;
    }
}

/// @todo Maybe shared inline with #ftPr_SpecialNEnd_Coll?
void ftPr_SpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        ftPr_SpecialS_8013DA24(gobj, false, mf, fp->cur_anim_frame);
    }
}

void ftPr_SpecialNHit_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    if (ft_800824A0(gobj, &ftPr_Init_803D0610)) {
        ftPr_SpecialS_8013D658(gobj);
        ftCommon_8007D7FC(fp);
        if (da->xD8 == 0.0f) {
            ft_8008A2BC(gobj);
        } else {
            ftCo_LandingFallSpecial_Enter(gobj, 0, da->xD8);
        }
    }
}

void ftPr_SpecialN_8014222C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2 * fp->facing_dir);
    fp->self_vel.x = -fp->self_vel.x;
    fp->gr_vel = -fp->gr_vel;
    fp->xE4_ground_accel_1 = -fp->xE4_ground_accel_1;
    fp->mv.pr.specialn.x10 = -fp->mv.pr.specialn.x10;
    fp->mv.pr.specialn.x14 = -fp->mv.pr.specialn.x14;
    fp->mv.pr.specialn.x18 = -fp->mv.pr.specialn.x18;
    fp->mv.pr.specialn.x1C = -fp->mv.pr.specialn.x1C;
    fp->mv.pr.specialn.facing_dir = -fp->mv.pr.specialn.facing_dir;
    fp->mv.pr.specialn.x34.x = -fp->mv.pr.specialn.x34.x;
    fp->mv.pr.specialn.x34.y = -fp->mv.pr.specialn.x34.y;
}
