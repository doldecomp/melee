#include "ftCo_AttackS4.h"

#include "ftCo_Attack1.h"
#include "ftCo_AttackHi3.h"
#include "ftCo_AttackHi4.h"
#include "ftCo_AttackLw3.h"
#include "ftCo_AttackLw4.h"
#include "ftCo_AttackS3.h"
#include "ftCo_Guard.h"
#include "ftCo_ItemThrow.h"
#include "ftCo_SpecialS.h"
#include "math.h"

#include <platform.h>

#include "ef/eflib.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0CDD.h"
#include "ft/ft_0D14.h"
#include "ft/ft_0DF1.h"
#include "ft/ftanim.h"
#include "ft/ftattacks4combo.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/ftswing.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_AppealS.h"
#include "ftCommon/ftCo_Dash.h"
#include "ftCommon/ftCo_Jump.h"
#include "ftCommon/ftCo_Turn.h"
#include "ftCommon/ftCo_Walk.h"
#include "ftGameWatch/ftGw_AttackS4.h"
#include "ftNess/ftNs_AttackS4.h"
#include "ftPeach/ftPe_AttackS4.h"
#include "it/it_26B1.h"

#include <baselib/forward.h>

#include <common_structs.h>
#include <dolphin/mtx.h>

typedef enum cmd_var_idx {
    cmd_unk0_bool,
} cmd_var_idx;

/* 08C22C */ static bool checkItemThrow(Fighter_GObj* gobj,
                                        float stick_x_sign);
/* 08C348 */ static void decideFighter(Fighter_GObj* gobj, float stick_x_sign,
                                       float stick_angle);
/* 08C3E0 */ static void doEnter(Fighter_GObj* gobj, float stick_angle);

static bool checkLStick(Fighter* fp)
{
    if (fp->input.x668 & HSD_PAD_A &&
        ABS(fp->input.lstick.x) >= p_ftCommonData->x3C &&
        fp->x670_timer_lstick_tilt_x < p_ftCommonData->x40)
    {
        return true;
    }
    return false;
}

bool ftCo_AttackS4_CheckInput(Fighter_GObj* gobj)
{
    float stick_x_sign, stick_angle;
    Fighter* fp = GET_FIGHTER(gobj);
    if (checkLStick(fp)) {
        stick_x_sign = fp->input.lstick.x >= 0 ? (float) +1 : -1;
        stick_angle = ftCo_GetLStickAngle(fp);
    } else if (ftCo_800DF1C8(fp)) {
        stick_x_sign = fp->input.cstick.x >= 0 ? (float) +1 : -1;
        stick_angle = ftCo_GetCStickAngle(fp);
    } else {
        return false;
    }
    if (checkItemThrow(gobj, stick_x_sign)) {
        return true;
    }
    decideFighter(gobj, stick_x_sign, stick_angle);
    return true;
}

static bool checkFacingDir(Fighter* fp)
{
    if (fp->input.x668 & HSD_PAD_A &&
        fp->input.lstick.x * fp->facing_dir >= p_ftCommonData->x3C)
    {
        return true;
    } else {
        return false;
    }
}

/// @todo Can maybe be combined with #ftCo_AttackS4_CheckInput
bool ftCo_AttackS4_8008C114(Fighter_GObj* gobj)
{
    float stick_x_sign, stick_angle;
    Fighter* fp = GET_FIGHTER(gobj);
    if (checkFacingDir(fp)) {
        stick_x_sign = fp->facing_dir;
        stick_angle = ftCo_GetLStickAngle(fp);
    } else if (ftCo_800DF1C8(fp)) {
        stick_x_sign = fp->input.cstick.x >= 0 ? (float) +1 : -1;
        stick_angle = ftCo_GetCStickAngle(fp);
    } else {
        return false;
    }
    if (checkItemThrow(gobj, stick_x_sign)) {
        return true;
    }
    decideFighter(gobj, stick_x_sign, stick_angle);
    return true;
}

static bool checkItemThrow(Fighter_GObj* gobj, float stick_x_sign)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->item_gobj != NULL) {
        if (fp->input.held_inputs & HSD_PAD_LR ||
            it_8026B30C(fp->item_gobj) == 0 ||
            (it_8026B30C(fp->item_gobj) == 3 && it_8026B594(fp->item_gobj)) ||
            ftCo_800DF21C(fp))
        {
            ftCo_800957F4(gobj, stick_x_sign * fp->facing_dir >= 0
                                    ? ftCo_MS_LightThrowF4
                                    : ftCo_MS_LightThrowB4);
            return true;
        }
        switch (it_8026B30C(fp->item_gobj)) {
        case 2:
            fp->facing_dir = stick_x_sign;
            ftCo_Attack_800CCF58(gobj, 2);
            return true;
        case 3:
            fp->facing_dir = stick_x_sign;
            ftCo_Attack_800CDD14(gobj);
            return true;
        }
    }
    return false;
}

void decideFighter(HSD_GObj* gobj, float stick_x_sign, float stick_angle)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->facing_dir = stick_x_sign;
    switch (fp->kind) {
    case FTKIND_NESS:
        ftNs_AttackS4_Enter(gobj);
        return;
    case FTKIND_PEACH:
        ftPe_AttackS4_Enter(gobj);
        return;
    case FTKIND_GAMEWATCH:
        ftGw_AttackS4_Enter(gobj);
        return;
    case FTKIND_PIKACHU:
    case FTKIND_PICHU:
        doEnter(gobj, stick_angle);
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
        return;
    default:
        doEnter(gobj, stick_angle);
        return;
    }
}

static void doEnter(Fighter_GObj* gobj, float stick_angle)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid;
    if (stick_angle > p_ftCommonData->xB8 &&
        ftData_80085FD4(fp, ftCo_MS_AttackS4S)->x8 != NULL)
    {
        msid = ftCo_MS_AttackS4Hi;
    } else if (stick_angle > p_ftCommonData->xBC &&
               ftData_80085FD4(fp, ftCo_MS_AttackS4LwS)->x8 != NULL)
    {
        msid = ftCo_MS_AttackS4HiS;
    } else if (stick_angle < p_ftCommonData->xC4 &&
               ftData_80085FD4(fp, ftCo_MS_AttackLw4)->x8 != NULL)
    {
        msid = ftCo_MS_AttackS4Lw;
    } else if (stick_angle < p_ftCommonData->xC0 &&
               ftData_80085FD4(fp, ftCo_MS_AttackHi4)->x8 != NULL)
    {
        msid = ftCo_MS_AttackS4LwS;
    } else {
        msid = ftCo_MS_AttackS4S;
    }
    fp->allow_interrupt = false;
    fp->cmd_vars[cmd_unk0_bool] = false;
    fp->throw_flags = 0;
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCo_AttackS4_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_AttackS4_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->allow_interrupt) {
        RETURN_IF(ftCo_SpecialS_CheckInput(gobj));
        RETURN_IF(ftCo_Attack100_CheckInput(gobj));
        RETURN_IF(ftCo_800D6824(gobj));
        RETURN_IF(ftCo_800D68C0(gobj));
        RETURN_IF(ftCo_Catch_CheckInput(gobj));
    }
    RETURN_IF(ftCo_800CECE8(gobj));
    if (fp->allow_interrupt) {
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
        RETURN_IF(ftCo_Walk_CheckInput(gobj));
    }
}

void ftCo_AttackS4_Phys(Fighter_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftCo_AttackS4_Coll(Fighter_GObj* gobj)
{
    ft_80084104(gobj);
}
