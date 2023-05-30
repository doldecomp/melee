#include <platform.h>
#include "ft/forward.h"

#include "ftCo_CliffAttack.h"

#include "ftCo_CliffClimb.h"
#include "ftCo_CliffEscape.h"

#include "ft/fighter.h"
#include "ft/ft_08A4.h"
#include "ft/ftcommon.h"

/* 09AEA4 */ static void ftCo_8009AEA4(ftCo_GObj* gobj);

void ftCo_8009AE14(ftCo_GObj* gobj)
{
    ftCommon_8007D7FC(gobj->user_data);
}

static inline bool inlineA0(ftCo_Fighter* fp)
{
    if (fp->input.x668 & (HSD_PAD_A | HSD_PAD_B)) {
        return true;
    }
    return false;
}

bool ftCo_8009AE38(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (inlineA0(fp) || ftCo_800DF6F8(fp)) {
        ftCo_8009AEA4(gobj);
        return true;
    }
    return false;
}

void ftCo_8009AEA4(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    FtMotionId msid = (float) fp->dmg.x1830_percent < p_ftCommonData->x488
                          ? ftCo_MS_CliffAttackQuick
                          : ftCo_MS_CliffAttackSlow;
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2F4(fp, 32);
    fp->x221D_b7 = true;
    fp->x221D_b5 = true;
    ftCo_CliffCatch_Phys(gobj);
}

void ftCo_CliffAttack_Anim(ftCo_GObj* gobj)
{
    ftCo_CliffClimb_Anim(gobj);
}

void ftCo_CliffAttack_IASA(ftCo_GObj* gobj) {}

void ftCo_CliffAttack_Phys(ftCo_GObj* gobj)
{
    ftCo_CliffClimb_Phys(gobj);
}

void ftCo_CliffAttack_Coll(ftCo_GObj* gobj)
{
    ftCo_CliffClimb_Coll(gobj);
}

static inline bool inlineB0(ftCo_Fighter* fp)
{
    if (fp->input.x668 & HSD_PAD_LR) {
        return true;
    }
    return false;
}

bool ftCo_8009AFD4(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (inlineB0(fp) || ftCo_800DF72C(fp)) {
        ftCo_8009B040(gobj);
        return true;
    }
    return false;
}
