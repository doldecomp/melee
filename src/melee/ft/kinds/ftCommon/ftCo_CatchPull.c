#include "ftCo_Attack100.h"
#include "ftCo_Fall.h"
#include "ftCo_Throw.h"

#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/inlines.h>
#include <melee/it/inlines.h>
#include <melee/it/kinds/itlinkhookshot.h>
#include <melee/it/kinds/itsamusgrapple.h>
#include <melee/lb/lb_00B0.h>

void fn_800D9CE8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* yattrs;
    Item_GObj* item;
    Item* it;
    f32 frame;
    f32 rate;
    f32 startFrame;
    s32 nextMotion;
    PAD_STACK(0x18);

    fp->gr_vel = 0.0f;
    frame = fp->cur_anim_frame;
    startFrame = frame;
    if (fp->motion_id == 0xD4) {
        nextMotion = 0xD5;
        if (fp->kind == FTKIND_YOSHI) {
            yattrs = fp->dat_attrs;
            if (frame >= yattrs->x124 && frame < yattrs->x128) {
                rate = frame - yattrs->x124;
                ftAnim_SetAnimRate(gobj, rate);
                ftAnim_8006EBA4(gobj);
                startFrame = (f32) yattrs->x12C[(s32) rate];
            }
        }
    } else {
        nextMotion = 0xD7;
    }

    switch (fp->kind) {
    case FTKIND_CLINK:
    case FTKIND_LINK:
        item = fp->u.lk.xC;
        it = GET_ITEM(item);
        it_802A7840((HSD_GObj*) item);
        fp->mv.co.capturedamage.x18 = it->xDD4_itemVar.linkhookshot.xC;
        break;
    case FTKIND_SAMUS:
        item = fp->u.ss.x223C;
        it = GET_ITEM(item);
        it_802BAA94(item);
        fp->mv.co.capturedamage.x18 = it->xDD4_itemVar.samusgrapple.xC;
        break;
    default:
        fp->mv.co.capturedamage.x18 = fp->parts[fp->ft_data->x8->x11].joint;
        break;
    }

    fp->throw_flags = 0;
    Fighter_ChangeMotionState(gobj, nextMotion, 0x4000, startFrame, 1.0f, 0.0f,
                              NULL);
    fp->accessory1_cb = fn_800DA190;
    fp->x221B_b7 = 0;
}

void ftCo_CatchPull_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int should_transition = false;
    PAD_STACK(16);

    switch (fp->kind) {
    case FTKIND_LINK:
    case FTKIND_CLINK: {
        Item_GObj* item_gobj = fp->u.lk.xC;
        if (item_gobj == NULL) {
            should_transition = true;
        } else {
            Item* ip = GET_ITEM(item_gobj);
            if (ip->xDD4_itemVar.linkhookshot.x14 != 0) {
                should_transition = true;
            }
        }
        break;
    }
    case FTKIND_SAMUS: {
        Item_GObj* item_gobj = fp->u.ss.x223C;
        if (item_gobj == NULL) {
            should_transition = true;
        } else {
            Item* ip = GET_ITEM(item_gobj);
            if (ip->xDD4_itemVar.samusgrapple.x14 != 0) {
                should_transition = true;
            }
        }
        break;
    }
    default:
        if (ftAnim_IsFramesRemaining(gobj) != 0) {
            int result;
            if (fp->throw_flags_b3) {
                fp->throw_flags_b3 = 0;
                result = 1;
            } else {
                result = 0;
            }
            if (result == 0) {
                break;
            }
        }
        should_transition = true;
        break;
    }

    if (should_transition) {
        fn_800DA1D8(gobj);
    }
}

void ftCo_CatchPull_IASA(Fighter_GObj* gobj) {}

void ftCo_CatchPull_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_ApplyFrictionGround(fp, p_ftCommonData->x64 *
                                         fp->co_attrs.ground_friction);
    ftCommon_ApplyGroundMovement(gobj);
}

void ftCo_CatchPull_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, fn_800DA004);
}

void fn_800DA004(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_GObj* victim = fp->victim_gobj;
    ftCo_800DC920(gobj, victim);
    ftCo_Fall_Enter(gobj);
    ftCo_Fall_Enter(victim);
}

void fn_800DA054(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* victim = HSD_GObjGetUserData(fp->victim_gobj);
    Fighter* new_var2;
    u32 pad1;
    u32 pad2;
    u32 pad3;
    float tmp;
    u32 pad4;
    u32 pad5;
    u32 pad6;
    Vec3 victimPos;
    Vec3 selfPos;
    f32 facing;
    f32 dx;
    HSD_JObj* new_var;
    f32 dy;
    float new_var3;
    f32 v;
    f32 spd;
    PAD_STACK(0x20);

    if (!victim->x2226_b2) {
        new_var = fp->mv.co.capturedamage.x18;
        lb_8000B1CC(new_var, 0L, &selfPos);
        new_var2 = victim;
        lb_8000B1CC(
            victim->parts[ftParts_GetBoneIndex(new_var2, FtPart_XRotN)].joint,
            0L, &victimPos);
        facing = (new_var3 = fp->facing_dir);
        new_var3 = victimPos.y - selfPos.y;
        dx = victimPos.x - selfPos.x;
        dy = new_var3 + fp->x2170;

        if ((dx * facing > p_ftCommonData->x34C)) {
            goto jmp;
        }

        if (dy < 0.0f) {
            dy = -dy;
        }
        if (dy > p_ftCommonData->x350) {
        jmp:
            ftCo_800DA698(gobj, 1);
        } else if (dx * facing < 0.0f) {
            v = (dx < 0.0f ? -dx : dx);
            spd = (tmp = fp->co_attrs.walk_max_vel);

            if (v > spd) {
                v = spd;
            }
            fp->gr_vel = (dx > 0.0f) ? v : (-v);
        }
    }
}

void fn_800DA190(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (fp->kind) {
    case 6:
    case 13:
    case 20:
        break;
    default:
        fn_800DA054(gobj);
        break;
    }
}
