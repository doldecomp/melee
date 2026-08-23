#include "ftCo_Attack100.h"
#include "ftCo_Fall.h"
#include "ftCo_ItemThrow.h"
#include "ftpickupitem.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_084E.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"

bool ftCo_800952DC(Fighter_GObj*);
void fn_800D9CE8(Fighter_GObj*);
void fn_800DAADC(Fighter_GObj* arg0, Fighter_GObj* arg1);

bool ftCo_Catch_CheckInput(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftCo_800951D0(gobj)) {
        return true;
    }
    if (!fn_800D8E94(gobj)) {
        return false;
    }
    if (!fn_800D952C(gobj)) {
        return false;
    }
    if ((fp->input.held_inputs & HSD_PAD_LR) && (fp->input.x668 & HSD_PAD_A)) {
        ftCo_800D8C54(gobj, ftCo_MS_Catch);
        return true;
    }
    return false;
}

bool ftCo_800D8A38(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftCo_80095254(gobj)) {
        return true;
    }
    if (!fn_800D8E94(gobj)) {
        return false;
    }
    if (!fn_800D952C(gobj)) {
        return false;
    }
    if ((fp->input.held_inputs & HSD_PAD_LR) && (fp->input.x668 & HSD_PAD_A)) {
        ftCo_800D8C54(gobj, ftCo_MS_CatchDash);
        return true;
    }
    return false;
}

bool ftCo_800D8AE0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (ftCo_800952DC(gobj)) {
        return true;
    }
    if (!fn_800D8E94(gobj)) {
        return false;
    }
    if (!fn_800D952C(gobj)) {
        return false;
    }
    if ((fp->input.held_inputs & HSD_PAD_LR) && fp->mv.co.common.x0 != 0) {
        ftCo_800D8C54(gobj, ftCo_MS_CatchDash);
        return true;
    }
    if (fp->mv.co.common.x0 != 0) {
        fp->mv.co.common.x0--;
    }
    return false;
}

bool ftCo_800D8B9C(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if ((fp->input.x668 & HSD_PAD_A) && fp->mv.co.guard.x24 != 0) {
        ftCo_800D8C54(gobj, ftCo_MS_CatchDash);
        return true;
    }
    if (fp->mv.co.guard.x24 != 0) {
        fp->mv.co.guard.x24--;
    }
    return false;
}

void fn_800D8BFC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftpickupitem_800948A8(gobj, fp->target_item_gobj);
    fp->x1A64 = NULL;
    fp->target_item_gobj = NULL;
    ftpickupitem_80094694(gobj, 0x5D, 1);
}

void ftCo_800D8C54(Fighter_GObj* gobj, FtMotionId msid)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->x74_anim_vel.z = 0.0F;
    fp->x74_anim_vel.y = 0.0F;
    fp->x74_anim_vel.x = 0.0F;
    fp->mv.co.catch.x0 = 0.0F;
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0F, 1.0F, 0.0F, NULL);
    ftCommon_8007E2D0(fp, 1, fn_800D9CE8, fn_800D8BFC, fn_800DAADC);
}

void ftCo_Catch_Anim(Fighter_GObj* gobj)
{
    u8 _[8];

    if (fn_800D8EC8(gobj)) {
        return;
    }
    if (fn_800D9558(gobj)) {
        return;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_CatchDash_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (!fn_800D9228(gobj) && !fn_800D9930(gobj) &&
        !ftAnim_IsFramesRemaining(gobj))
    {
        ft_8008A2BC(gobj);
    }
}

void ftCo_Catch_IASA(Fighter_GObj* gobj) {}

void ftCo_CatchDash_IASA(Fighter_GObj* gobj) {}

void ftCo_Catch_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_ApplyFrictionGround(fp, p_ftCommonData->x64 *
                                         fp->co_attrs.ground_friction);
    ftCommon_ApplyGroundMovement(gobj);
}

void ftCo_CatchDash_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ft_80085030(gobj, p_ftCommonData->x64 * fp->co_attrs.ground_friction,
                fp->facing_dir);
}

void ftCo_Catch_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, fn_800D8E30);
}

void fn_800D8E30(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    fn_800D949C(gobj);
    fn_800D9C64(gobj);
    ftCo_Fall_Enter(gobj);
}

void ftCo_CatchDash_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, fn_800D8E30);
}

bool fn_800D8E94(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FighterKind kind = fp->kind;
    if (((kind == FTKIND_LINK) || (kind == FTKIND_CLINK)) &&
        (fp->u.lk.xC != NULL))
    {
        return false;
    }
    return true;
}
