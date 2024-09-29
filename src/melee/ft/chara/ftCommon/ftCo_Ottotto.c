#include <platform.h>

#include "ftCommon/forward.h"
#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

#include "ftCo_Ottotto.h"

#include "ftCo_Attack1.h"
#include "ftCo_AttackHi3.h"
#include "ftCo_AttackHi4.h"
#include "ftCo_AttackLw3.h"
#include "ftCo_AttackLw4.h"
#include "ftCo_AttackS3.h"
#include "ftCo_AttackS4.h"
#include "ftCo_Guard.h"
#include "ftCo_SpecialS.h"
#include "math.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C88.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/types.h"
#include "mp/mplib.h"

#include <common_structs.h>

/* 09A410 */ static void ftCo_8009A410(ftCo_GObj* gobj);
/* 09A6B8 */ static void ftCo_8009A6B8(ftCo_GObj* gobj);

bool ftCo_8009A3C8(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->coll_data.env_flags & MPCOLL_FLAGS_B23 && !fp->x2228_b2) {
        ftCo_8009A410(gobj);
        return true;
    }
    return false;
}

void ftCo_8009A410(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_Ottotto, Ft_MF_None, 0, 1, 0,
                              NULL);
    fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
    fp->gr_vel = 0;
}

void ftCo_Ottotto_Anim(ftCo_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_8009A6B8(gobj);
    }
}

void ftCo_Ottotto_IASA(ftCo_GObj* gobj)
{
    u8 _[8] = { 0 };
    RETURN_IF(ftCo_SpecialS_CheckInput(gobj));
    RETURN_IF(ftCo_Attack100_CheckInput(gobj));
    RETURN_IF(ftCo_800D6824(gobj));
    RETURN_IF(ftCo_800D68C0(gobj));
    RETURN_IF(ftCo_Catch_CheckInput(gobj));
    RETURN_IF(ftCo_AttackS4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackHi4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackLw4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackS3_CheckInput(gobj));
    RETURN_IF(ftCo_AttackHi3_CheckInput(gobj));
    RETURN_IF(ftCo_AttackLw3_CheckInput(gobj));
    RETURN_IF(ftCo_Attack1_CheckInput(gobj));
    RETURN_IF(ftCo_80091A4C(gobj));
    RETURN_IF(ftCo_800DE9D8(gobj));
    RETURN_IF(ftCo_Jump_CheckInput(gobj));
    RETURN_IF(ftCo_Dash_CheckInput(gobj));
    RETURN_IF(ftCo_800D5FB0(gobj));
    RETURN_IF(ftCo_Turn_CheckInput(gobj));
    RETURN_IF(ftCo_800C94B4(gobj));
}

void ftCo_Ottotto_Phys(HSD_GObj* gobj) {}

void ftCo_Ottotto_Coll(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    {
        if (!ft_800827A0(gobj)) {
            ftCo_800CC730(gobj);
        } else {
            u8 _[4] = { 0 };
            Vec3 pos;
            {
                u8 _[4] = { 0 };
                if (fp->facing_dir > 0) {
                    mpLib_80053FF4(fp->coll_data.floor.index, &pos);
                } else {
                    mpLib_80054158(fp->coll_data.floor.index, &pos);
                }
                {
                    float x = fp->cur_pos.x - pos.x;
                    x = ABS(x);
                    if (x > p_ftCommonData->x478 + p_ftCommonData->x47C) {
                        ft_8008A2BC(gobj);
                    }
                }
            }
        }
    }
}

void ftCo_8009A6B8(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_OttottoWait, Ft_MF_None, 0, 1, 0,
                              NULL);
    ft_80088770(fp);
    ft_800887CC(fp);
    ft_80088328(fp, fp->ft_data->x4C_sfx->x18, 127, 64);
}

void ftCo_OttottoWait_Anim(HSD_GObj* gobj) {}

void ftCo_OttottoWait_IASA(Fighter_GObj* gobj)
{
    ftCo_Ottotto_IASA(gobj);
}

void ftCo_OttottoWait_Phys(HSD_GObj* gobj) {}

/// @todo Shared code with #ftCo_Ottotto_Coll
void ftCo_OttottoWait_Coll(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    {
        if (!ft_800827A0(gobj)) {
            ftCo_800CC730(gobj);
        } else {
            u8 _[4] = { 0 };
            Vec3 pos;
            {
                u8 _[20] = { 0 };
                if (fp->facing_dir > 0) {
                    mpLib_80053FF4(fp->coll_data.floor.index, &pos);
                } else {
                    mpLib_80054158(fp->coll_data.floor.index, &pos);
                }
                if (ABS(fp->cur_pos.x - pos.x) >
                    p_ftCommonData->x478 + p_ftCommonData->x47C)
                {
                    ft_8008A2BC(gobj);
                }
            }
        }
    }
}
