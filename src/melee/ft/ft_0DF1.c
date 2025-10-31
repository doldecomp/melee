#include "ft_0DF1.h"

#include "platform.h"
#include "stdbool.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

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
        ftCo_GetCStickAngle(fp) < p_ftCommonData->x20_radians)
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
    if (!gm_8016B0FC()) {
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
