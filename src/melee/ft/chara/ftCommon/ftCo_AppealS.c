#include "ftCo_AppealS.h"

#include "placeholder.h"
#include "platform.h"
#include "stdbool.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0D14.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Attack1.h"
#include "ftCommon/ftCo_AttackHi3.h"
#include "ftCommon/ftCo_AttackHi4.h"
#include "ftCommon/ftCo_AttackLw3.h"
#include "ftCommon/ftCo_AttackLw4.h"
#include "ftCommon/ftCo_AttackS3.h"
#include "ftCommon/ftCo_AttackS4.h"
#include "ftCommon/ftCo_Guard.h"
#include "ftCommon/ftCo_SpecialS.h"

#include <math.h>
#include <baselib/gobj.h>
#include <melee/cm/camera.h>
#include <melee/ef/efsync.h>
#include <melee/ft/chara/ftCommon/ftCo_Attack1.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS4.h>
#include <melee/ft/chara/ftCommon/ftCo_DamageIce.h>
#include <melee/ft/chara/ftCommon/ftCo_Escape.h>
#include <melee/ft/chara/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/chara/ftCommon/ftCo_Guard.h>
#include <melee/ft/chara/ftCommon/ftCo_Lift.h>
#include <melee/ft/chara/ftCommon/ftCo_SpecialS.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ft_0CDD.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftchangeparam.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/ftmaterial.h>
#include <melee/ft/ftmetal.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gr/stage.h>
#include <melee/it/item.h>
#include <melee/it/items/it_2E5A.h>
#include <melee/it/items/itkinoko.h>
#include <melee/pl/pl_040D.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonuslib.h>
#include <melee/pl/plstale.h>

void ftCo_AppealS_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->allow_interrupt && (ftCo_SpecialS_CheckInput(gobj) == 0) &&
        (ftCo_Attack100_CheckInput(gobj) == 0) && (ftCo_800D6824(gobj) == 0) &&
        (ftCo_800D68C0(gobj) == 0) && (ftCo_Catch_CheckInput(gobj) == 0) &&
        (ftCo_AttackS4_CheckInput(gobj) == 0) &&
        (ftCo_AttackHi4_CheckInput(gobj) == 0) &&
        (ftCo_AttackLw4_CheckInput(gobj) == 0) &&
        (ftCo_AttackS3_CheckInput(gobj) == 0) &&
        (ftCo_AttackHi3_CheckInput(gobj) == 0) &&
        (ftCo_AttackLw3_CheckInput(gobj) == 0) &&
        (ftCo_Attack1_CheckInput(gobj) == 0) && (ftCo_80099794(gobj) == 0))
    {
        ftCo_80091A4C(gobj);
    }
}

/// #ftCo_800DE854

/// #ftCo_800DE920

/// #ftCo_800DE974

/// #ftCo_800DE9B8

bool ftCo_800DE9D8(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

/// #ftCo_800DEA28

/// #ftCo_800DEAE8

/// #ftCo_800DEBD0

void ftCo_AppealS_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

/// #ftCo_AppealS_IASA

void ftCo_AppealS_Phys(Fighter_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftCo_AppealS_Coll(Fighter_GObj* gobj)
{
    ft_80084104(gobj);
}

void ftCo_800DEE84(Fighter_GObj* gobj, int arg1, char* arg2, u32 arg3,
                   f32 arg4, f32 arg5)
{
    Fighter* fp = GET_FIGHTER(gobj);
    SmashAttr* attr = &fp->smash_attrs;

    attr->state = SmashState_PreCharge;
    attr->x2118_frames = 0.0F;
    attr->x211C_holdFrame = arg4;
    attr->x2120_damageMul = arg5;
    attr->x2128 = arg1;
}

void ftCo_800DEEA8(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->smash_attrs.state = SmashState_None;
}

f32 ftCo_800DEEB8(Fighter* fp, f32 arg1)
{
    SmashAttr* attrs = &fp->smash_attrs;
    if (attrs->state != SmashState_Release) {
        return arg1;
    }
    return arg1 * ((attrs->x2120_damageMul - 1.0F) *
                       (attrs->x2118_frames / attrs->x211C_holdFrame) +
                   1.0F);
}

Vec2* ftCo_800DEEE8(Fighter* fp, Vec2* shift)
{
    SmashAttr* temp_r6 = &fp->smash_attrs;
    if (temp_r6->state == SmashState_Charging || temp_r6->state == 4) {
        Vec2* temp_r5 = &Fighter_804D6528->x0[temp_r6->x212C];
        shift->x = temp_r5->x;
        shift->y = temp_r5->y;
        return shift;
    }
    return NULL;
}

void ftCo_800DEF38(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    SmashAttr* attr = &fp->smash_attrs;
    if (attr->state == SmashState_Charging) {
        attr->x2118_frames++;
        attr->x212C++;
        if (attr->x212C >= attr->x212D) {
            attr->x212C = 0;
        }
        if (attr->x2118_frames >= attr->x211C_holdFrame) {
            if (attr->x2118_frames > attr->x211C_holdFrame) {
                attr->x2118_frames = attr->x211C_holdFrame;
            }
            {
                SmashAttr* attr;
                Fighter* fp = GET_FIGHTER(gobj);
                attr = &fp->smash_attrs;
                attr->state = SmashState_Release;
                ftAnim_SetAnimRate(gobj, attr->x2124_frameSpeedMul);
                ftCo_800C0200(fp, attr->x2128);
                ftCommon_8007ECD4(fp, 0x24);
            }
        }
        if (!attr->x2130_sfxBool && attr->x2118_frames >= p_ftCommonData->x7C8)
        {
            ft_PlaySFX(fp, 0x7B, 0x7F, 0x40);
            attr->x2130_sfxBool = true;
        }
    } else if (attr->state == 4) {
        attr->x2118_frames++;
        attr->x212C++;
        if (attr->x212C >= attr->x212D) {
            attr->x212C = 0;
        }
        if (!attr->x2130_sfxBool && attr->x2118_frames >= p_ftCommonData->x7C8)
        {
            ft_PlaySFX(fp, 0x7B, 0x7F, 0x40);
            attr->x2130_sfxBool = true;
        }
    }
}

void ftCo_800DF0D0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    SmashAttr* attr = &fp->smash_attrs;

    PAD_STACK(0x18);

    switch (fp->smash_attrs.state) {
    case SmashState_PreCharge:
        if (fp->input.held_inputs & HSD_PAD_A) {
            attr->state = SmashState_Charging;
            attr->x2124_frameSpeedMul = fp->frame_speed_mul;
            attr->x212C = 0;
            attr->x212D = Fighter_804D6528->x4;
            attr->x2130_sfxBool = 0;
            ftAnim_SetAnimRate(gobj, 0.0f);
            if (attr->x2128 != 0x7B) {
                ftCo_800BFFD0(fp, attr->x2128, 0);
            }
            ftCommon_8007EBAC(fp, 0x24U, 0U);
        } else {
            attr->state = SmashState_None;
        }
        break;
    case SmashState_Charging:
        if (!(fp->input.held_inputs & HSD_PAD_A)) {
            attr->state = SmashState_Release;
            ftAnim_SetAnimRate(gobj, attr->x2124_frameSpeedMul);
            ftCo_800C0200(fp, attr->x2128);
            ftCommon_8007ECD4(fp, 0x24);
        }
        break;
    }
}

static inline bool canUseCstick(Fighter* fp)
{
    /// Returns true if single-button mode is off,
    /// and the held item allows using the C-stick.
    if (!gm_8016B0FC() || it_8026B30C(fp->item_gobj) == 0) {
        return true;
    } else {
        return false;
    }
}

bool ftCo_800DF1C8(Fighter* fp)
{
    if (ABS(fp->input.cstick1.x) < p_ftCommonData->x3C &&
        ABS(fp->input.cstick.x) >= p_ftCommonData->x3C)
    {
        return true;
    }
    return false;
}

bool ftCo_800DF21C(Fighter* fp)
{
    if (canUseCstick(fp) && ftCo_800DF1C8(fp)) {
        return true;
    }
    return false;
}

bool ftCo_800DF2D8(Fighter* fp)
{
    if (fp->input.cstick1.y < p_ftCommonData->xCC &&
        fp->input.cstick.y >= p_ftCommonData->xCC)
    {
        return true;
    }
    return false;
}

bool ftCo_800DF30C(Fighter* fp)
{
    if (canUseCstick(fp) && ftCo_800DF2D8(fp)) {
        return true;
    }
    return false;
}

bool ftCo_800DF3A8(Fighter* fp)
{
    if (fp->input.cstick1.y > p_ftCommonData->xD4 &&
        fp->input.cstick.y <= p_ftCommonData->xD4)
    {
        return true;
    }
    return false;
}

bool ftCo_800DF3DC(Fighter* fp)
{
    bool var_r0_2;

    if (canUseCstick(fp) && ftCo_800DF3A8(fp)) {
        return true;
    }
    return false;
}

bool ftCo_800DF478(Fighter* arg0)
{
    if ((ABS(arg0->input.cstick1.x) < p_ftCommonData->xDC &&
         ABS(arg0->input.cstick.x) >= p_ftCommonData->xDC) ||
        (ABS(arg0->input.cstick1.y) < p_ftCommonData->xE0 &&
         ABS(arg0->input.cstick.y) >= p_ftCommonData->xE0))
    {
        return true;
    }
    return false;
}

bool ftCo_800DF50C(Fighter* fp)
{
    bool var_r0;

    if (!gm_8016B0FC() || it_8026B30C(fp->item_gobj) == 0) {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0 && ftCo_800DF478(fp)) {
        return true;
    }
    return false;
}

bool ftCo_800DF608(Fighter* fp)
{
    if (SQ(fp->input.cstick.x) + SQ(fp->input.cstick.y) >=
        SQ(p_ftCommonData->x4B0))
    {
        return true;
    }
    return false;
}

bool ftCo_800DF644(Fighter* fp)
{
    if (fp->input.cstick1.y < p_ftCommonData->x7F4 &&
        fp->input.cstick.y >= p_ftCommonData->x7F4)
    {
        return true;
    }
    return false;
}

bool ftCo_800DF678(Fighter* fp)
{
    if (ABS(fp->input.cstick1.x) < p_ftCommonData->x248 &&
        ABS(fp->input.cstick.x) >= p_ftCommonData->x248 &&
        ftCo_GetCStickAngle(fp) < p_ftCommonData->x20)
    {
        return true;
    }
    return false;
}

bool ftCo_800DF6F8(Fighter* fp)
{
    if (fp->input.cstick1.y < p_ftCommonData->x7F8 &&
        fp->input.cstick.y >= p_ftCommonData->x7F8)
    {
        return true;
    }
    return false;
}

bool ftCo_800DF72C(Fighter* fp)
{
    if (gm_8016B0FC() == 0) {
        if (fp->facing_dir * fp->input.cstick1.x < p_ftCommonData->x7FC &&
            fp->facing_dir * fp->input.cstick.x >= p_ftCommonData->x7FC)
        {
            return true;
        }
    }
    return false;
}

bool ftCo_800DF79C(Fighter* fp)
{
    if (ABS(fp->input.cstick.x) >= p_ftCommonData->x494 ||
        ABS(fp->input.cstick.y) >= p_ftCommonData->x494)
    {
        return true;
    }
    return false;
}

bool ftCo_800DF7F4(Fighter* fp)
{
    f32 temp_f1 = p_ftCommonData->x98;
    if ((fp->input.cstick1.x < temp_f1 && fp->input.cstick.x >= temp_f1) ||
        (fp->input.cstick1.x > -temp_f1 && fp->input.cstick.x <= -temp_f1))
    {
        return true;
    }
    return false;
}

bool ftCo_800DF844(Fighter* fp)
{
    f32 temp_f1 = p_ftCommonData->attackhi3_stick_threshold_y;
    if (fp->input.cstick1.y < temp_f1 && fp->input.cstick.y >= temp_f1) {
        return true;
    }
    return false;
}

bool ftCo_800DF878(Fighter* fp)
{
    f32 temp_f1 = p_ftCommonData->xB0;
    if (fp->input.cstick1.y <= temp_f1 && fp->input.cstick.y <= temp_f1) {
        return true;
    }
    return false;
}

bool ftCo_800DF8B0(Fighter* fp)
{
    if (ABS(fp->input.cstick.x) >= p_ftCommonData->x31C) {
        return true;
    }
    return false;
}

bool ftCo_800DF8E8(Fighter* fp)
{
    if (fp->input.cstick.y <= p_ftCommonData->x314) {
        return true;
    }
    return false;
}

bool ftCo_800DF910(Fighter* fp)
{
    if (fp->input.cstick.y >= p_ftCommonData->tap_jump_threshold) {
        return true;
    }
    return false;
}
