#include "ftCommon/forward.h"

#include "ftCo_PassiveCeil.h"

#include "ftCo_DamageFall.h"
#include "ftCo_DownAttack.h"
#include "ftCo_FallSpecial.h"

#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0C88.h"
#include "ft/ftanim.h"
#include "ft/ftcolanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftKirby/ftKb_Init.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

bool ftCo_800C23A0(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->coll_data.env_flags & MPCOLL_FLAGS_B14 && ftCo_800986B0(gobj)) {
        ftCo_800C23FC(gobj);
        return true;
    }
    return false;
}

/// @todo Shared code with #ftCo_800C1E64.
void ftCo_800C23FC(ftCo_GObj* gobj)
{
    Vec3 ef_offset;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007E2FC(gobj);
    fp->throw_flags = 0;
    ef_offset.x = 0;
    ef_offset.y = fp->coll_data.xA4_ecbCurrCorrect.top.y;
    ef_offset.z = 0;
    ftKb_SpecialN_800F1F1C(gobj, &ef_offset);
    Fighter_ChangeMotionState(gobj, ftCo_MS_PassiveCeil, Ft_MF_None, 0, 1, 0,
                              NULL);
    {
        float pos_y_offset = fp->cur_pos.y + ef_offset.y;
        Vec3 ef_pos;
        u8 _[4] = { 0 };
        ef_pos.x = fp->cur_pos.x;
        ef_pos.y = pos_y_offset;
        ef_pos.z = fp->cur_pos.z;
        efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 2,
                      (1 << 0) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 10),
                      NULL, &ef_pos);
        fp->cur_pos.y = pos_y_offset + fp->x68C_transNPos.y;
    }
    ftCo_80090574(gobj);
    ft_800881D8(fp, fp->ft_data->x4C_sfx->x24, 0x7F, 0x40);
    ft_80088148(fp, 3, 0x7F, 0x40);
    ftCommon_8007EBAC(fp, 12, 0);
    ftCo_800BFFD0(fp, 120, 0);
}

void ftCo_PassiveCeil_Anim(ftCo_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftCheckThrowB3(fp)) {
        fp->self_vel.x = fp->input.lstick.x * fp->co_attrs.passiveceil_vel_x;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800CC730(gobj);
    }
}

void ftCo_PassiveCeil_IASA(ftCo_GObj* gobj) {}

void ftCo_PassiveCeil_Phys(ftCo_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_PassiveCeil_Coll(ftCo_GObj* gobj)
{
    ft_800831CC(gobj, ftCo_80096CC8, ft_80082B1C);
}
