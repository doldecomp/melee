#include "ftCo_JumpAerial.h"

#include "math.h"

#include <placeholder.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0D14.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_AirCatch.h"
#include "ftCommon/ftCo_AttackAir.h"
#include "ftCommon/ftCo_EscapeAir.h"
#include "ftCommon/ftCo_FallAerial.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftCommon/ftCo_HammerWait.h"
#include "ftCommon/ftCo_ItemParasolOpen.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftCommon/ftCo_SpecialAir.h"
#include "ftPeach/ftPe_Float.h"

/* 0CC3C4 */ static void ftYs_JumpAerial_Anim_Cb(Fighter_GObj* gobj);
/* 0CC654 */ static void ftNs_JumpAerial_Phys_Cb(Fighter_GObj* gobj);

void ft_800CB6EC(Fighter* fp, s32 arg1)
{
    if (fp->mv.co.jumpaerial.x0 != 0) {
        fp->mv.co.jumpaerial.x0 -= 1;
        HSD_JObjAddRotationY(fp->parts->joint,
                             -(deg_to_rad * (180.0F / arg1)));
        if (fp->mv.co.jumpaerial.x0 == (arg1 / 2)) {
            fp->facing_dir = -fp->facing_dir;
        }
    }
}

bool ft_did_jump(Fighter* fp, bool arg1)
{
    if (fp->x1968_jumpsUsed < fp->co_attrs.max_jumps &&
        ((fp->input.lstick.y >= p_ftCommonData->tap_jump_threshold &&
          fp->x671_timer_lstick_tilt_y < p_ftCommonData->x74) ||
         fp->input.x668 & HSD_PAD_XY) &&
        !(arg1 && (fp->x68A < p_ftCommonData->x1C)))
    {
        return true;
    }

    return false;
}

bool ftCo_800CB870(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftCo_800C5240(gobj)) {
        return false;
    }
    if (fp->can_multijump) {
        return ftCo_800D730C(gobj, false);
    }
    return ftCo_JumpAerial_CheckInput(gobj, false);
}

bool ftCo_800CB8E0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftCo_800C5240(gobj)) {
        return false;
    }
    if (fp->can_multijump) {
        return ftCo_800D730C(gobj, true);
    }
    return ftCo_JumpAerial_CheckInput(gobj, true);
}

bool ftCo_JumpAerial_CheckInput(Fighter_GObj* gobj, bool arg1)
{
    ftCo_DatAttrs* co_attrs;
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    co_attrs = &fp->co_attrs;
    if (ft_did_jump(fp, arg1)) {
        if (ft_800D2D0C(gobj)) {
            Vec3 v;
            PAD_STACK(8);
            v.x = fp->input.lstick.x * co_attrs->air_jump_h_multiplier;
            v.y = co_attrs->jump_v_initial_velocity *
                  co_attrs->air_jump_v_multiplier;
            v.z = 0.0F;
            ft_800D2E7C(gobj, &v);
            return true;
        }
        switch (fp->kind) {
        case FTKIND_NESS:
            ftNs_JumpAerial_Enter(gobj);
            break;
        case FTKIND_YOSHI:
            ftYs_JumpAerial_Enter(gobj);
            break;
        case FTKIND_PEACH:
            ftPe_JumpAerial_Enter(gobj);
            break;
        case FTKIND_MEWTWO:
            ftMt_JumpAerial_Enter(gobj);
            break;
        default:
            ftCo_JumpAerial_Enter_Basic(gobj);
            break;
        }
        return true;
    }
    return false;
}

static inline void ft_SetVec(Vec3* dst, Vec3* src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

static inline void ft_JumpAerial_Sound(Fighter* fp, FighterKind ftkind)
{
    if (ftkind != FTKIND_MEWTWO && (ftkind >= 0x10 || ftkind != FTKIND_NESS) &&
        fp->x197C != NULL)
    {
        ft_PlaySFX(fp, 0x11B, SFX_VOLUME_MAX, SFX_PAN_MID);
    }
}

void ftCo_800CBAC4(Fighter_GObj* gobj, FtMotionId msid, Vec3* vel, bool arg3)
{
    Fighter* fp = GET_FIGHTER(gobj);

    Fighter_ChangeMotionState(gobj, msid, Ft_MF_SkipNametagVis, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->x2221_b7 = true;
    ft_SetVec(&fp->self_vel, vel);
    if (arg3) {
        fp->x671_timer_lstick_tilt_y = 0xFE;
    }
    fp->x1968_jumpsUsed += 1;
    ft_80088770(fp);
    ft_80088328(fp, fp->ft_data->x4C_sfx->x14, SFX_VOLUME_MAX, SFX_PAN_MID);
    ft_JumpAerial_Sound(fp, fp->kind);
}

void ftCo_JumpAerial_Enter_Basic(Fighter_GObj* gobj)
{
    ftCo_DatAttrs* co_attrs;
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid;
    Vec3 vel;
    co_attrs = &fp->co_attrs;
    PAD_STACK(8);

    ftCommon_8007D5D4(fp);
    fp->cmd_vars[0] = 1;
    msid = (fp->input.lstick.x * fp->facing_dir) > -p_ftCommonData->x78
               ? ftCo_MS_JumpAerialF
               : ftCo_MS_JumpAerialB;
    vel.x = fp->input.lstick.x * co_attrs->air_jump_h_multiplier;
    vel.y =
        co_attrs->jump_v_initial_velocity * co_attrs->air_jump_v_multiplier;
    vel.z = 0.0F;
    ftCo_800CBAC4(gobj, msid, &vel, true);
}

void ftNs_JumpAerial_Enter(Fighter_GObj* gobj)
{
    ftCo_DatAttrs* co_attrs_r31;
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 vel = { 0.0F, 0.0F, 0.0F };
    FtMotionId msid;
    PAD_STACK(4);
    co_attrs_r31 = &fp->co_attrs;

    ftCommon_8007D5D4(fp);
    fp->cmd_vars[0] = 1;
    msid = (fp->input.lstick.x * fp->facing_dir) > -p_ftCommonData->x78
               ? ftCo_MS_JumpAerialF
               : ftCo_MS_JumpAerialB;

    ftCo_800CBAC4(gobj, msid, &vel, true);
    fp->phys_cb = (HSD_GObjEvent) ftNs_JumpAerial_Phys_Cb;
    fp->mv.co.jumpaerial.init_h_vel =
        fp->input.lstick.x * co_attrs_r31->air_jump_h_multiplier;
}

void ftYs_JumpAerial_Enter(Fighter_GObj* gobj)
{
    // mv.co.jumpaerial.x0 could also be mv.ys.jumpaerial.x0
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* ys_attrs = fp->dat_attrs;
    Vec3 vel;
    int arg1;
    PAD_STACK(16);

    ftCommon_8007D5D4(fp);
    fp->cmd_vars[0] = 1;
    vel.x = fp->input.lstick.x * fp->co_attrs.air_jump_h_multiplier;
    vel.y = 0.0F;
    vel.z = 0.0F;
    ftCo_800CBAC4(gobj, ftCo_MS_JumpAerialF, &vel, true);
    fp->phys_cb = (HSD_GObjEvent) ftCo_JumpAerial_Phys_Cb;
    fp->anim_cb = (HSD_GObjEvent) ftYs_JumpAerial_Anim_Cb;
    fp->dmg.armor1 = ys_attrs->x8;
    if ((fp->input.lstick.x * fp->facing_dir) < -ys_attrs->x4) {
        fp->mv.co.jumpaerial.x0 = ys_attrs->x0;
    } else {
        fp->mv.co.jumpaerial.x0 = 0;
    }

    arg1 = ys_attrs->x0;
    ft_800CB6EC(fp, arg1);
}

void ftPe_JumpAerial_Enter(Fighter_GObj* gobj)
{
    ftCo_DatAttrs* co_attrs;
    Fighter* fp_r31 = GET_FIGHTER(gobj);
    FtMotionId msid;
    Vec3 vel;
    co_attrs = &fp_r31->co_attrs;
    PAD_STACK(8);

    ftCommon_8007D5D4(fp_r31);
    fp_r31->cmd_vars[0] = 1;
    msid = (fp_r31->input.lstick.x * fp_r31->facing_dir) > -p_ftCommonData->x78
               ? ftCo_MS_JumpAerialF
               : ftCo_MS_JumpAerialB;
    vel.x = fp_r31->input.lstick.x * co_attrs->air_jump_h_multiplier;
    vel.y = 0.0F;
    vel.z = 0.0F;
    ftCo_800CBAC4(gobj, msid, &vel, true);
    fp_r31->phys_cb = (HSD_GObjEvent) ftCo_JumpAerial_Phys_Cb;
}

void ftMt_JumpAerial_Enter(Fighter_GObj* gobj)
{
    ftCo_DatAttrs* co_attrs;
    Fighter* fp_r31 = GET_FIGHTER(gobj);
    FtMotionId msid;
    Vec3 vel;
    co_attrs = &fp_r31->co_attrs;
    PAD_STACK(8);

    ftCommon_8007D5D4(fp_r31);
    fp_r31->cmd_vars[0] = 1;
    msid = (fp_r31->input.lstick.x * fp_r31->facing_dir) > -p_ftCommonData->x78
               ? ftCo_MS_JumpAerialF
               : ftCo_MS_JumpAerialB;
    vel.x = fp_r31->input.lstick.x * co_attrs->air_jump_h_multiplier;
    vel.y = 0.0F;
    vel.z = 0.0F;
    ftCo_800CBAC4(gobj, msid, &vel, true);
    fp_r31->phys_cb = (HSD_GObjEvent) ftCo_JumpAerial_Phys_Cb;
}

void ftCo_JumpAerial_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_FallAerial_Enter(gobj);
    }
}

void ftYs_JumpAerial_Anim_Cb(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* ys_attrs = fp->dat_attrs;
    PAD_STACK(8);
    ftCo_JumpAerial_Anim(gobj);
    ft_800CB6EC(fp, ys_attrs->x0);
}

void ftCo_JumpAerial_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    RETURN_IF(ftCo_SpecialAir_CheckInput(gobj));
    RETURN_IF(ftCo_80095328(gobj, NULL));
    RETURN_IF(ftCo_800D7100(gobj));
    RETURN_IF(ftCo_800C3B10(gobj));
    RETURN_IF(ftCo_80099A58(gobj));
    RETURN_IF(ftCo_AttackAir_CheckItemThrowInput(gobj));
    RETURN_IF(ftCo_800D705C(gobj));
    RETURN_IF(ftPe_8011BA54(gobj));
    RETURN_IF(ftCo_800CB870(gobj));
    RETURN_IF(fp->cmd_vars[0] && ftPe_8011BAD8(gobj));
    RETURN_IF(!fp->cmd_vars[0]);
    RETURN_IF(ftCo_800CEE70(gobj));
}

void ftCo_JumpAerial_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftNs_JumpAerial_Phys_Cb(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D28C(fp, fp->mv.co.jumpaerial.init_h_vel);
    fp->mv.co.jumpaerial.init_h_vel += fp->x74_anim_vel.x;
    fp->x74_anim_vel.x = 0.0F;
    fp->self_vel.x = fp->x6A4_transNOffset.z * fp->facing_dir +
                     fp->mv.co.jumpaerial.init_h_vel;
    ft_800851D0(gobj);
}

void ftCo_JumpAerial_Phys_Cb(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D268(fp);
    ft_800851D0(gobj);
}

void ftCo_JumpAerial_Coll(Fighter_GObj* gobj)
{
    ft_800835B0(gobj, ftCo_80096CC8, (HSD_GObjEvent) ft_80082B1C);
}
