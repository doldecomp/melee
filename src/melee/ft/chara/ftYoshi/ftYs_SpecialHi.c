#include "ftYs_SpecialHi.static.h"

#include "placeholder.h"

#include "baselib/forward.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_CaptureYoshi.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_YoshiEgg.h"
#include "ftYoshi/ftYs_Init.h"
#include "it/items/it_2F2B.h"
#include "it/items/ityoshieggthrow.h"

#include <dolphin/mtx.h>
#include <baselib/gobj.h>

void ftYs_SpecialS_8012DF18(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->target_item_gobj != NULL) {
        ftYoshi_MotionState msid = fp->motion_id;
        bool clear_destroy_type = false;
        if (msid == ftYs_MS_SpecialN1_1 || msid == ftYs_MS_SpecialN2_1 ||
            msid == ftYs_MS_SpecialAirN1_2 || msid == ftYs_MS_SpecialAirN2_1)
        {
            clear_destroy_type = true;
        }
        it_802F2CE0(fp->target_item_gobj, clear_destroy_type);
        fp->x1A64 = NULL;
        fp->target_item_gobj = NULL;
    }
}

/// #ftYs_SpecialS_8012DF8C

/// #fn_8012E110

void ftYs_SpecialS_8012E270(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.ys.x2238 != NULL && fp->mv.ys.specials.x0 == 0) {
        it_802B2890(fp->fv.ys.x2238);
    }
    fp->fv.ys.x2238 = NULL;
    fp->take_dmg_cb = NULL;
    fp->death2_cb = NULL;
}

/// #ftYs_SpecialHi_Enter

/// #ftYs_SpecialAirHi_Enter

inline void qwe(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->accessory4_cb = fn_8012E110;
}
inline void fn_8012E3B4_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.ys.x2238 != NULL) {
        fp->take_dmg_cb = ftYs_Init_8012BA8C;
        fp->death2_cb = ftYs_Init_8012BA8C;
    }
}
void fn_8012E3B4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x16D, 0x0C4C5082U, fp->cur_anim_frame, 0,
                              1, NULL);

    fn_8012E3B4_inline(gobj);
    qwe(gobj);

    ftCommon_8007D468(fp);
}

void fn_8012E44C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x16C, 0x0C4C5082U, fp->cur_anim_frame, 0,
                              1, NULL);
    fn_8012E3B4_inline(gobj);
    qwe(gobj);
}

void ftYs_SpecialHi_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    if (fp->input.held_inputs & 0x200) {
        fp->mv.ys.specialhi.x4 += 1;
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

void ftYs_SpecialAirHi_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    if (fp->input.held_inputs & 0x200) {
        fp->mv.ys.specialhi.x4 += 1;
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftYs_SpecialHi_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftYs_SpecialAirHi_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftYs_SpecialHi_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, (void(*)) fn_8012E3B4);
}

void ftYs_SpecialAirHi_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.ys.specialhi.x0 != 0) {
        // ft_80083A48(NULL, fn_8012E44C);
        ft_80083A48(gobj, fn_8012E44C);
        // return;
    } else {
        ft_80082C74(gobj, fn_8012E44C);
    }
}

/// #fn_8012E644

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

/// #ftYs_SpecialAirLw_Enter

void ftYs_SpecialLw_Anim(Fighter_GObj* gobj)
{
    u8 _[8];

    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftYs_SpecialS_8012EA04(gobj);
    }
}

void ftYs_SpecialAirLw_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        fp->cmd_vars[1] = 1;
    }
}

void ftYs_SpecialLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ft_80085134(gobj);
    if (fp->self_vel.y < 0) {
        fp->self_vel.y = 0;
    }
}

void ftYs_SpecialAirLw_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    u8 _[8];

    ft_80085134(gobj);
    if ((fp->self_vel.y < attributes->x114) || ((u32) fp->cmd_vars[1] != 0U)) {
        fp->self_vel.y = attributes->x114;
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

extern f32 ftYs_Init_804D9A5C;
extern f32 ftYs_Init_804D9A60;
extern f32 ftYs_Init_804D9A64;
void ftYs_SpecialS_8012EA04(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x170, 0x0C4C5088U, ftYs_Init_804D9A64,
                              ftYs_Init_804D9A5C, ftYs_Init_804D9A60, NULL);
}

void ftYs_SpecialLwLanding_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

void ftYs_SpecialLwLanding_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftYs_SpecialLwLanding_Coll(Fighter_GObj* gobj)
{
    u8 _[8];

    if (ft_80082708(gobj) == GA_Ground) {
        ftCo_Fall_Enter(gobj);
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

/// #ftYs_SpecialS_8012EB48

/// #fn_8012EC7C

/// #fn_8012EDE8

void fn_8012EFC0(Fighter_GObj* gobj)
{
    ft_80089824(gobj);
    ft_800892A0(gobj);
}

/// #fn_8012EFF4

/// #ftYs_SpecialS_8012F0DC

/// #ftYs_SpecialS_8012F35C

/// #ftYs_SpecialS_Enter

/// #ftYs_SpecialAirS_Enter

/// #ftYs_SpecialAirSStart_0_Anim

/// #ftYs_SpecialAirSLoop_0_Anim

/// #ftYs_SpecialAirSLoop_1_Anim

/// #ftYs_SpecialAirSEnd_Anim

/// #ftYs_SpecialAirSStart_1_Anim

/// #ftYs_SpecialAirSLoop_2_Anim

/// #ftYs_SpecialAirSLoop_3_Anim

/// #ftYs_SpecialAirSLanding_Anim

void ftYs_SpecialAirSStart_0_IASA(Fighter_GObj* gobj) {}

/// #ftYs_SpecialAirSLoop_0_IASA

void ftYs_SpecialAirSLoop_1_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    s32 x48 = attributes->x48;
    s32 x4C = attributes->x4C;
    s32 difference = x48 - x4C;

    if ((fp->mv.ys.specials.x0 < difference) && (fp->input.x668 & HSD_PAD_B)) {
        ftYs_SpecialS_8012F0DC(gobj, 0, 0x440012, 0.0f);
    }
}

void ftYs_SpecialAirSEnd_IASA(Fighter_GObj* gobj) {}

void ftYs_SpecialAirSStart_1_IASA(Fighter_GObj* gobj)
{
    M2C_FIELD(gobj->user_data, s32*, 0x2370) = 0;
}

void ftYs_SpecialAirSLoop_2_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    fp->mv.ys.specials.x30 = 0;
    if ((fp->mv.ys.specials.x0 < attributes->x48 - attributes->x4C) &&
        (fp->input.x668 & HSD_PAD_B))
    {
        ftYs_SpecialS_8012F0DC(gobj, 1, 0x440012, 0.0f);
    }
}

void ftYs_SpecialAirSLoop_3_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    fp->mv.ys.specials.x30 = 0;

    if ((fp->mv.ys.specials.x0 < (attributes->x48 - attributes->x4C)) &&
        (fp->input.x668 & HSD_PAD_B))
    {
        ftYs_SpecialS_8012F0DC(gobj, 1, 0x440012, 0.0f);
    }
}

void ftYs_SpecialAirSLanding_IASA(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->mv.ys.specials.x30 = 0;
}

void ftYs_SpecialAirSStart_0_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->xE4_ground_accel_1 = 0.0f;
    fp->gr_vel = 0.0f;
    fp->self_vel.y = 0.0f;
    fp->self_vel.x = 0.0f;
    fp->x74_anim_vel.y = 0.0f;
    fp->x74_anim_vel.x = 0.0f;
}

/// #ftYs_SpecialAirSLoop_0_Phys

/// #ftYs_SpecialAirSLoop_1_Phys

void ftYs_SpecialAirSEnd_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007C930((Fighter*) fp, fp->co_attrs.gr_friction);
    ftCommon_8007CB74(gobj);
}

void ftYs_SpecialAirSStart_1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    fp->mv.ys.specials.x30 = 0;
    ftCommon_8007D494(fp, attributes->x6C, attributes->x70);
}

/// #ftYs_SpecialAirSLoop_2_Phys

/// #ftYs_SpecialAirSLoop_3_Phys

void ftYs_SpecialAirSLanding_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    fp->mv.ys.specials.x30 = 0;
    ftCommon_8007D494(fp, attributes->x6C, attributes->x70);
}

/// #ftYs_SpecialAirSStart_0_Coll

/// #ftYs_SpecialAirSLoop_0_Coll

/// #ftYs_SpecialAirSLoop_1_Coll

void ftYs_SpecialAirSEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        ftYs_SpecialS_8012F0DC(gobj, 1, 0x4C4092, fp->cur_anim_frame);
    }
}

/// #ftYs_SpecialAirSStart_1_Coll

/// #ftYs_SpecialAirSLoop_2_Coll

/// #ftYs_SpecialAirSLoop_3_Coll

/// #ftYs_SpecialAirSLanding_Coll

/// #fn_8013295C
