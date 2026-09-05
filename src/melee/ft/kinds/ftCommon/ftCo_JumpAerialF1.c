#include "ftCo_Attack100.h"
#include "ftCo_Fall.h"
#include "ftCo_FallAerial.h"
#include "ftCo_ItemScrew.h"
#include "ftCo_JumpAerial.h"

#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0D27.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/inlines.h>

static inline struct Fighter_x2D0_t* ftCo_800D74A4_inline(Fighter* fp)
{
    return fp->x2D0;
}

bool ftCo_800D730C(Fighter_GObj* gobj, bool arg1)
{
    s32 unused1;
    struct Fighter_x2D0_t* x2d0;
    s32 canJump;
    s32 r29;
    Fighter* fp;
    Vec3 vel;
    s32 r4;
    s32 result;
    s32 unused2;
    s32 unused3;
    s32 unused4;
    s32 unused5;
    s32 unused6;
    s32 unused7;

    fp = GET_FIGHTER(gobj);
    x2d0 = fp->x2D0;
    if (fp->motion_id == 0x9B) {
        if (ft_did_jump(fp, arg1)) {
            ftCo_800D74A4(gobj);
            return 1;
        }
        return 0;
    }
    if (fp->x1968_jumpsUsed == 1) {
        if (ft_did_jump(fp, arg1)) {
            if (ft_800D2D0C(gobj)) {
                vel.x = fp->input.lstick.x * x2d0->x8;
                vel.y = x2d0->x14[0];
                vel.z = 0.0F;
                ft_800D2E7C(gobj, &vel);
            } else {
                ftCommon_8007D5D4(fp);
                ftCo_800D74A4(gobj);
            }
            return 1;
        }
    } else {
        r29 = 1;
        canJump = fp->x1968_jumpsUsed < fp->co_attrs.max_jumps;
        if (ftCo_800D72A0(fp) && fp->cmd_vars[0] == 0) {
            r29 = 0;
        }
        r4 = 1;
        if (!(fp->input.lstick.y >= p_ftCommonData->tap_jump_threshold) &&
            !(fp->input.held_inputs & 0xC00))
        {
            r4 = 0;
        }
        if (canJump && r29 && r4) {
            result = 1;
        } else {
            result = 0;
        }
        if (result) {
            ftCo_800D74A4(gobj);
            return 1;
        }
    }
    return 0;
}

void ftCo_800D74A4(Fighter_GObj* gobj)
{
    Vec3 vel;
    Fighter* fp;
    struct Fighter_x2D0_t* tmp;
    s32 msid;
    s32 msid2;
    struct Fighter_x2D0_t* p;
    PAD_STACK(0x14);

    fp = gobj->user_data;
    p = ftCo_800D74A4_inline(fp);
    fp->cmd_vars[0] = 0;
    tmp = fp->x2D0;
    msid =
        fp->x1968_jumpsUsed +
        (tmp = (struct Fighter_x2D0_t*) ((s32*) tmp + ftCo_800D7268(fp)))->x2C;
    msid2 = --msid;
    vel.x = fp->input.lstick.x * p->x8;
    tmp = fp->x2D0;
    tmp = (struct Fighter_x2D0_t*) ((s32*) tmp + ftCo_800D7268(fp));
    vel.y = p->x14[msid - tmp->x2C];
    vel.z = 0.0F;
    ftCo_800CBAC4(gobj, msid2, &vel, false);
    if ((fp->input.lstick.x * fp->facing_dir) < -p->x4) {
        *(s32*) &fp->mv.ca.specials.grav = p->x0;
    } else {
        *(s32*) &fp->mv.ca.specials.grav = 0;
    }
    ft_800CB6EC(fp, p->x0);
}

void ftCo_JumpAerialF1_Anim(Fighter_GObj* gobj)
{
    ftCo_DatAttrs* co;
    Fighter* temp_r30 = GET_FIGHTER(gobj);
    int tmp = temp_r30->x2D0->x0;
    PAD_STACK(4);
    co = &temp_r30->co_attrs;
    ft_800CB6EC(temp_r30, tmp);
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        if (temp_r30->x1968_jumpsUsed >= co->max_jumps) {
            ftCo_FallAerial_Enter(gobj);
        } else {
            ftCo_Fall_Enter(gobj);
        }
    }
}

void ftCo_JumpAerialF1_IASA(Fighter_GObj* gobj)
{
    ftCo_JumpAerial_IASA(gobj);
}

void ftCo_JumpAerialF1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co = &fp->co_attrs;
    struct Fighter_x2D0_t* temp_r6 = fp->x2D0;
    ft_80084E1C(gobj, p_ftCommonData->x258,
                co->air_drift_stick_mul * temp_r6->xC,
                co->air_drift_max * temp_r6->x10);
}

void ftCo_JumpAerialF1_Coll(Fighter_GObj* gobj)
{
    ft_80082F28(gobj);
}
