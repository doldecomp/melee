#include "ftYoshi/ftYs_SpecialN.static.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_CaptureYoshi.h"
#include "ftYoshi/ftYs_Init.h"
#include "it/items/it_2F2B.h"

#include <dolphin/mtx/types.h>
#include <baselib/gobj.h>

/* 3B75C0 */ Vec3 const ftYs_Unk1_803B75C0 = { 0 };

float ftYs_SpecialN_8012CD10(ftYs_GObj* gobj)
{
    return M2C_FIELD(gFtDataList[0xE]->ext_attr, f32*, 0x28);
}

float ftYs_SpecialN_8012CD28(void)
{
    return M2C_FIELD(gFtDataList[0xE]->ext_attr, f32*, 0x2C);
}

float ftYs_SpecialN_8012CD40(void)
{
    return M2C_FIELD(gFtDataList[0xE]->ext_attr, f32*, 0x30);
}

float ftYs_SpecialN_8012CD58(void)
{
    return M2C_FIELD(gFtDataList[0xE]->ext_attr, f32*, 0x34);
}

int ftYs_SpecialN_8012CD70(void)
{
    return M2C_FIELD(gFtDataList[0xE]->ext_attr, s32*, 0x38);
}

/// #ftYs_SpecialN_8012CD88

/// #ftYs_SpecialN_8012CDB4

HSD_Joint* ftYs_SpecialN_8012CDD4(ftYs_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftData* ca = fp->ft_data;
    return ca->x48_items[3];
}

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

/// #ftYs_SpecialAirN_Enter

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

/// #fn_8012D004

/// #fn_8012D0A0

/// #fn_8012D128

/// #fn_8012D1AC

/// #fn_8012D230

/// #fn_8012D298

/// #fn_8012D2F8

/// #fn_8012D360

/// #fn_8012D3C0

/// #fn_8012D428

/// #fn_8012D488

/// #fn_8012D4F0

/// #ftYs_SpecialN1_Anim

/// #ftYs_SpecialAirN1_0_Anim

/// #ftYs_SpecialN1_1_Anim

/// #ftYs_SpecialN1_0_Anim

/// #ftYs_SpecialAirN1_2_Anim

/// #ftYs_SpecialAirN1_1_Anim

/// #ftYs_SpecialN2_1_Anim

/// #ftYs_SpecialN2_0_Anim

/// #ftYs_SpecialAirN2_1_Anim

/// #ftYs_SpecialAirN2_0_Anim

/// #ftYs_SpecialN1_Phys

/// #ftYs_SpecialAirN1_0_Phys

/// #ftYs_SpecialN1_1_Phys

/// #ftYs_SpecialN1_0_Phys

/// #ftYs_SpecialAirN1_2_Phys

/// #ftYs_SpecialAirN1_1_Phys

/// #ftYs_SpecialN2_1_Phys

/// #ftYs_SpecialN2_0_Phys

/// #ftYs_SpecialAirN2_1_Phys

/// #ftYs_SpecialAirN2_0_Phys

/// #ftYs_SpecialN1_Coll

/// #ftYs_SpecialAirN1_0_Coll

/// #ftYs_SpecialN1_1_Coll

/// #ftYs_SpecialN1_0_Coll

/// #ftYs_SpecialAirN1_2_Coll

/// #ftYs_SpecialAirN1_1_Coll

/// #ftYs_SpecialN2_1_Coll

/// #ftYs_SpecialN2_0_Coll

/// #ftYs_SpecialAirN2_1_Coll

/// #ftYs_SpecialAirN2_0_Coll

void ftYs_SpecialS_8012DF00(HSD_GObj* arg0)
{
    void* temp_r3;

    temp_r3 = arg0->user_data;
    M2C_FIELD(temp_r3, void (**)(HSD_GObj*), 0x21DC) = ftYs_Init_8012BA8C;
    M2C_FIELD(temp_r3, void (**)(HSD_GObj*), 0x21E4) = ftYs_Init_8012BA8C;
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

/// #ftYs_SpecialS_8012DF8C

/// #fn_8012E110

/// #ftYs_SpecialS_8012E270

/// #ftYs_SpecialHi_Enter

/// #ftYs_SpecialAirHi_Enter

/// #fn_8012E3B4

/// #fn_8012E44C

/// #ftYs_SpecialHi_Anim

/// #ftYs_SpecialAirHi_Anim

/// #ftYs_SpecialHi_Phys

/// #ftYs_SpecialAirHi_Phys

/// #ftYs_SpecialHi_Coll

/// #ftYs_SpecialAirHi_Coll

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

/// #ftYs_SpecialLw_Anim

/// #ftYs_SpecialAirLw_Anim

void ftYs_SpecialLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ft_80085134(gobj);
    if (fp->self_vel.y < 0) {
        fp->self_vel.y = 0;
    }
}

/// #ftYs_SpecialAirLw_Phys

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

/// #ftYs_SpecialS_8012EA04

/// #ftYs_SpecialLwLanding_Anim

/// #ftYs_SpecialLwLanding_Phys

/// #ftYs_SpecialLwLanding_Coll

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

/// #fn_8012EFC0

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

void ftYs_SpecialAirSStart_0_IASA(ftYs_GObj* gobj) {}

/// #ftYs_SpecialAirSLoop_0_IASA

/// #ftYs_SpecialAirSLoop_1_IASA

void ftYs_SpecialAirSEnd_IASA(ftYs_GObj* gobj) {}

void ftYs_SpecialAirSStart_1_IASA(ftYs_GObj* gobj)
{
    M2C_FIELD(gobj->user_data, s32*, 0x2370) = 0;
}

/// #ftYs_SpecialAirSLoop_2_IASA

/// #ftYs_SpecialAirSLoop_3_IASA

void ftYs_SpecialAirSLanding_IASA(ftYs_GObj* gobj)
{
    M2C_FIELD(gobj->user_data, s32*, 0x2370) = 0;
}

/// #ftYs_SpecialAirSStart_0_Phys

/// #ftYs_SpecialAirSLoop_0_Phys

/// #ftYs_SpecialAirSLoop_1_Phys

/// #ftYs_SpecialAirSEnd_Phys

/// #ftYs_SpecialAirSStart_1_Phys

/// #ftYs_SpecialAirSLoop_2_Phys

/// #ftYs_SpecialAirSLoop_3_Phys

/// #ftYs_SpecialAirSLanding_Phys

/// #ftYs_SpecialAirSStart_0_Coll

/// #ftYs_SpecialAirSLoop_0_Coll

/// #ftYs_SpecialAirSLoop_1_Coll

/// #ftYs_SpecialAirSEnd_Coll

/// #ftYs_SpecialAirSStart_1_Coll

/// #ftYs_SpecialAirSLoop_2_Coll

/// #ftYs_SpecialAirSLoop_3_Coll

/// #ftYs_SpecialAirSLanding_Coll

/// #fn_8013295C
