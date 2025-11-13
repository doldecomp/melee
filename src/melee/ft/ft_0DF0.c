#include "ft_0DF0.h"

#include "placeholder.h"
#include "platform.h"
#include "stdbool.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ftcolanim.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

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

void ftCo_800DEE84(Fighter_GObj* gobj, u32 arg1,
                   float arg2, float dmg_mult)
{
    Fighter* fp = GET_FIGHTER(gobj);
    SmashAttr* attr = &fp->smash_attrs;

    attr->state = SmashState_PreCharge;
    attr->x2118_frames = 0.0F;
    attr->x211C_holdFrame = arg2;
    attr->x2120_damageMul = dmg_mult;
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
    default:
        break;
    }
}
