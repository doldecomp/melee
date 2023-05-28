#include <platform.h>
#include "ft/forward.h"

#include "ftCo_CliffClimb.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ft/ftcommon.h"
#include "mp/mplib.h"

/* 09AAFC */ static bool ftCo_8009AAFC(ftCo_GObj* gobj, bool arg1,
                                       float stick_x, float stick_angle);
/* 09AB9C */ static void ftCo_8009AB9C(ftCo_GObj* gobj);

static inline bool inlineA0(ftCo_Fighter* fp)
{
    if (ABS(fp->input.lstick.x) >= p_ftCommonData->x494 ||
        ABS(fp->input.lstick.y) >= p_ftCommonData->x494)
    {
        return true;
    }
    return false;
}

bool ftCo_8009AA0C(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (inlineA0(fp)) {
        return ftCo_8009AAFC(gobj, true, fp->input.lstick.x,
                             ftCo_GetLStickAngle(fp));
    }
    if (ftCo_800DF79C(fp)) {
        return ftCo_8009AAFC(gobj, false, fp->input.cstick.x,
                             ftCo_GetCStickAngle(fp));
    }
    fp->mv.co.cliff.x8 = true;
    return 0;
}

bool ftCo_8009AAFC(ftCo_GObj* gobj, int arg1, float stick_x, float angle)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (angle > p_ftCommonData->x20 ||
        (angle > -p_ftCommonData->x20 && stick_x * fp->facing_dir >= 0))
    {
        if (arg1 && fp->mv.co.cliff.x8) {
            ftCo_8009AB9C(gobj);
            return true;
        }
        return false;
    }
    if (fp->mv.co.cliff.x8) {
        fp->x2064_ledgeCooldown = p_ftCommonData->ledge_cooldown;
        ft_800CC730(gobj);
        return true;
    }
    return false;
}

void ftCo_8009AB9C(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    FtMotionId msid = (float) fp->dmg.x1830_percent < p_ftCommonData->x488
                          ? ftCo_MS_CliffClimbQuick
                          : ftCo_MS_CliffClimbSlow;
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, NULL, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2F4(fp, 32);
    fp->x221D_b7 = true;
    fp->x221D_b5 = true;
    ftCo_CliffCatch_Phys(gobj);
}

void ftCo_CliffClimb_Anim(ftCo_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
    }
}

void ftCo_CliffClimb_IASA(ftCo_GObj* gobj) {}

void ftCo_CliffClimb_Phys(ftCo_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        if (mpLib_80054ED8(fp->mv.co.cliff.ledge_id)) {
            Vec3 vec;
            /// @todo Unused stack.
#ifdef MUST_MATCH
            u8 _[8] = { 0 };
#endif
            if (fp->facing_dir > 0) {
                mpLib_80053ECC(fp->mv.co.cliff.ledge_id, &vec);
            } else {
                mpLib_80053DA4(fp->mv.co.cliff.ledge_id, &vec);
            }
            fp->cur_pos.x = fp->x68C_transNPos.z * fp->facing_dir + vec.x;
            fp->cur_pos.y = vec.y + fp->x68C_transNPos.y;
            if (fp->ground_or_air == GA_Air && fp->x68C_transNPos.z >= 0 &&
                fp->x68C_transNPos.y >= 0)
            {
                fp->coll_data.floor.index = fp->mv.co.cliff.ledge_id;
                ftCommon_8007D7FC(fp);
            }
        } else {
            ft_800CC730(gobj);
        }
    } else {
        ft_80084FA8(gobj);
    }
}

void ftCo_CliffClimb_Coll(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        if (ft_800821DC(gobj)) {
            ftCo_8009AE14(gobj);
        } else if (ft_8009EF68(gobj)) {
            return;
        }
    } else {
        ft_80084104(gobj);
    }
}
