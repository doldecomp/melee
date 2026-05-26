#include "ft_081B.h"
#include "ft_0C31.h"
#include "ftcommon.h"

#include <placeholder.h>

#include "cm/camera.h"
#include "ft/fighter.h"
#include "ft/ftcolanim.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Damage.h"
#include "ftCommon/ftCo_DamageFall.h"
#include "ftCommon/ftCo_Lift.h"
#include "ftCommon/ftCo_Throw.h"
#include "it/items/itleadead.h"
#include "pl/player.h"

/* 0C74CC */ void fn_800C74CC(Fighter_GObj* gobj);
/* 0C7568 */ void fn_800C7568(Fighter_GObj* gobj);

/* 0C77E0 */ static void fn_800C77E0(Fighter_GObj* arg0);

void ftCo_800C7590(Fighter_GObj* gobj)
{
    ftCommonData* cd;
    f32 temp_f31;
    Fighter* fp = gobj->user_data;

    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    ftCo_8008DCE0(gobj, -1, 0.0f);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureLeadead, 0x1080, 0.0f, 1.0f,
                              0.0f, NULL);
    fp->take_dmg_cb = fn_800C74CC;
    fp->death2_cb = fn_800C7568;
    fp->mv.co.captureleadead.x0 = (Item_GObj*) fp->dmg.x1868_source;
    ftCommon_8007E2FC(gobj);
    cd = p_ftCommonData;
    {
        f32 tmp1 =
            cd->x728 * (cd->x72C - (f32) (Player_80033BB8(fp->player_id) + 1));
        f32 tmp2 = (cd->x720 * (cd->x724 - Player_GetHandicap(fp->player_id)) +
                    cd->x71C);
        tmp2 += tmp1;
        ftCommon_InitGrab(fp, 1, fp->dmg.x1830_percent * cd->x730 + tmp2);
    }
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->x221D_b5 = true;
    fp->x2220_b3 = true;
    it_802EAAEC(fp->mv.co.captureleadead.x0, gobj, 0, 0.0f);
    ftCommon_8007EBAC(fp, 0xC, 0);
    Camera_80030E44(2, &fp->cur_pos);
}

void ftCo_CaptureLeadead_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->grab_timer -= p_ftCommonData->x734;
    ftCommon_GrabMash(fp, p_ftCommonData->x738);
    if (fp->grab_timer <= 0.0F) {
        it_802EAE80(fp->mv.co.captureleadead.x0);
        ftCo_800C7800(gobj);
    }
}

void ftCo_CaptureLeadead_IASA(Fighter_GObj* gobj) {}

void ftCo_CaptureLeadead_Phys(Fighter_GObj* gobj) {}

static void fn_800C77E0(Fighter_GObj* arg0)
{
    ftCo_80090780(arg0);
}

void ftCo_CaptureLeadead_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800C77E0);
}

void ftCo_800C7800(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Ground) {
        fp->gr_vel = -fp->facing_dir * p_ftCommonData->x370;
    } else {
        fp->self_vel.x = -fp->facing_dir * p_ftCommonData->x370;
    }
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureCut, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    fp->capture_timer = p_ftCommonData->x73C;
}

void fn_800C7890(Fighter_GObj* gobj)
{
    ftCo_800C7A30(gobj);
}
