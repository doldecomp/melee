#include <platform.h>
#include "ft/forward.h"
#include "ftYoshi/forward.h"

#include "ftYoshi/ftYs_SpecialN.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_CaptureYoshi.h"
#include "it/items/it_2F2B.h"

#include <dolphin/mtx/types.h>
#include <baselib/gobj.h>

/* 12CEE0 */ static void fn_8012CEE0(HSD_GObj*);
/* 12CF7C */ static void fn_8012CF7C(HSD_GObj*);
/* 12DF00 */ static void ftYs_SpecialS_8012DF00(HSD_GObj*);
/* 12E644 */ static void fn_8012E644(HSD_GObj*);
/* 12EAD8 */ static void ftYs_SpecialS_8012EAD8(HSD_GObj*);

bool ftYs_Unk3_803CED48[] = {
    false, true, false, false, false, true, true, false,
    false, true, true,  true,  false, true, true,
};

Vec4 ftYs_Unk3_803CED84 = {
    0.65,
    0.7,
    0.8,
    1,
};

Vec4 ftYs_Unk3_803CED94 = {
    1.1,
    1.35,
    1.3,
    1.2,
};

Vec3 ftYs_Unk3_803CEDA4[] = {
    { 12, 0, -6 },
    { 6, 6, 6 },
};

Vec3 const ftYs_Unk1_803B75C0 = { 0 };

void ftYs_SpecialN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialN1, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
    {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007E2D0(fp, 4, fn_8012CF7C, fn_8012CEE0, ftCo_800BBB8C);
    }
}

void fn_8012CEE0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    it_802F2BFC(fp->x1A60, gobj);
    Fighter_ChangeMotionState(gobj, 348, 528530, fp->cur_anim_frame, 1, 0,
                              NULL);
    fp->x2222_b2 = true;
    fp->mv.ys.specialn.x0_b0 = true;
    ftYs_SpecialS_8012DF00(gobj);
    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
}

void fn_8012CF7C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 347, 528530, fp->cur_anim_frame, 1, 0,
                              NULL);
    fp->x2222_b2 = 1;
    fp->mv.ys.specialn.x0_b0 = false;
    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
}

void ftYs_SpecialS_8012DF18(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x1A60 != NULL) {
        ftYoshi_MotionState motion_id = fp->motion_id;
        bool clear_destroy_type = false;
        if (motion_id == ftYs_MS_SpecialN1_1 ||
            motion_id == ftYs_MS_SpecialN2_1 ||
            motion_id == ftYs_MS_SpecialAirN1_2 ||
            motion_id == ftYs_MS_SpecialAirN2_1)
        {
            clear_destroy_type = true;
        }
        it_802F2CE0(fp->x1A60, clear_destroy_type);
        fp->x1A64 = NULL;
        fp->x1A60 = NULL;
    }
}

extern f32 ftYs_Init_804D9A5C;
extern f32 ftYs_Init_804D9A60;

inline void ftYoshi_SpecialLw_SetVars(HSD_GObj* arg0)
{
    Fighter* fp = GET_FIGHTER(arg0);
    fp->cmd_vars[0] = fp->cmd_vars[1] = 0;
    fp->throw_flags_b0 = false;
    fp->self_vel.x = fp->self_vel.y = 0;
    fp->x6A4_transNOffset.y = 0;
    fp->x2223_b4 = true;
}

void ftYs_SpecialLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4 * 4);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialLw, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
    ftYoshi_SpecialLw_SetVars(gobj);
}

void ftYs_SpecialLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ft_80085134(gobj);
    if (fp->self_vel.y < 0) {
        fp->self_vel.y = 0;
    }
}

void ftYs_SpecialLw_Coll(HSD_GObj* gobj)
{
    ftYs_SpecialAirLw_Coll(gobj);
}

void ftYs_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int facing_dir;
    if (fp->facing_dir < 0) {
        facing_dir = -1;
    } else {
        facing_dir = +1;
    }
    if (ft_CheckGroundAndLedge(gobj, facing_dir)) {
        if (fp->cmd_vars[0] != 0 && fp->self_vel.y <= 0) {
            ftYs_SpecialS_8012EAD8(gobj);
        } else {
            ftCommon_8007D5D4(fp);
        }
    } else if (fp->cmd_vars[0] != 0 && ftCliffCommon_80081298(gobj)) {
        ftCliffCommon_80081370(gobj);
    }
}

void ftYs_SpecialS_8012EAD8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->gr_vel = 0;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialLwLanding, Ft_MF_None, 0, 1,
                              0, NULL);
    fp->accessory4_cb = fn_8012E644;
}
