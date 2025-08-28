#include "ftSs_SpecialLw_0.h"

#include "ftSs_Init.h"
#include "ftSs_SpecialLw_1.h"
#include "types.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Attack1.h"
#include "ftCommon/ftCo_AttackHi3.h"
#include "ftCommon/ftCo_AttackHi4.h"
#include "ftCommon/ftCo_AttackLw3.h"
#include "ftCommon/ftCo_AttackLw4.h"
#include "ftCommon/ftCo_AttackS3.h"
#include "ftCommon/ftCo_AttackS4.h"
#include "ftCommon/ftCo_Escape.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_SpecialS.h"
#include "lb/lbcollision.h"

#include <common_structs.h>
#include <trigf.h>
#include <dolphin/mtx.h>

void ftSs_Init_80128944(HSD_GObj* gobj, float farg1, float farg2)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* da = fp->dat_attrs;
    float float_result = ftSs_Init_80128AC8(gobj, farg1, farg2);

    u8 _[8];

    if (!ftColl_8007B868(gobj)) {
        switch (fp->x2070.x2071_b0_3) {
        case 0:
        case 2:
        case 3:
        case 4:
            if ((fp->x2070.x2073 == 0x14) || ((fp->x2070.x2071_b5) == 0)) {
                if (fp->x5F4_arr[0].x1 == 2) {
                    ftSs_Init_80128B1C(gobj, float_result, da->x0, 1.0f);
                } else {
                    ftSs_Init_80128B1C(gobj, float_result, 0.0f, 1.0f);
                }
            }
        }
    }
}

bool ftSs_Init_80128A1C(HSD_GObj* gobj, UNK_T arg1, float farg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;

    for (i = 0; i < fp->hurt_capsules_len; i++) {
        if (lbColl_80008248(arg1, &fp->hurt_capsules[i].capsule,
                            ftCommon_8007F804(fp), farg1, fp->x34_scale.y,
                            fp->cur_pos.z))
        {
            return true;
        }
    }

    return false;
}

float ftSs_Init_80128AC8(HSD_GObj* gobj, float farg1, float farg2)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* da = getFtSpecialAttrs(fp);
    float value = (fp->cur_pos.x - farg1) / farg2;
    if (value >= 1.0f) {
        value = 1.0f;
    }
    if (value <= -1.0f) {
        value = -1.0f;
    }
    return (-da->x4 * value) + 1.5707963705062866f;
}

inline void ftSamus_80128B1C_inner(HSD_GObj* gobj, float angle)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct ftCo_DatAttrs* ftAttr = &fp->co_attrs;
    ftSs_DatAttrs* samus_attr = getFtSpecialAttrs(fp);

    fp = GET_FIGHTER(gobj);
    fp->self_vel.x = samus_attr->x8 * cosf(angle);
    fp->self_vel.y = samus_attr->x8 * sinf(angle);
    ftCommon_8007D440(fp, ftAttr->air_drift_max * samus_attr->x10);
}

void ftSs_Init_80128B1C(HSD_GObj* gobj, float angle, float arg9, float argA)
{
    Fighter* fp;
    Fighter* fighter2;

    u8 _[8];

    fp = fighter2 = GET_FIGHTER(gobj);
    ftCommon_8007DB58(gobj);
    ftSamus_80128B1C_inner(gobj, angle);
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = 0;
    fp->mv.ss.unk2.x0 = 0;
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D5D4(fighter2);
    }
    Fighter_ChangeMotionState(gobj, 0x156, 0, arg9, argA, 0.0f, 0);
    ftAnim_8006EBA4(gobj);
}

void ftSs_SpecialLw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->cmd_vars[0]) && (!fp->mv.ss.unk2.x0)) {
        ftSs_SpecialLw_8012AEBC(gobj);
        fp->mv.ss.unk2.x0 = 1;
    }
    if ((!fp->cmd_vars[0]) && (fp->mv.ss.unk2.x0)) {
        ftSs_SpecialLw_8012AF38(gobj);
        fp->mv.ss.unk2.x0 = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftSs_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->cmd_vars[0]) && (!fp->mv.ss.unk2.x0)) {
        ftSs_SpecialLw_8012AEBC(gobj);
        fp->mv.ss.unk2.x0 = 1;
    }
    if ((!fp->cmd_vars[0]) && (fp->mv.ss.unk2.x0)) {
        ftSs_SpecialLw_8012AF38(gobj);
        fp->mv.ss.unk2.x0 = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftSs_SpecialLw_IASA(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[1] && fp->input.lstick.y < da->x14) {
        fp->cmd_vars[1] = 0;
        ftCo_800D638C(gobj);
        return;
    }
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
    RETURN_IF(ftCo_80099794(gobj));
}

void ftSs_SpecialAirLw_IASA(HSD_GObj* gobj)
{
    ftCo_Fall_IASA_Inner(gobj);
}

void ftSs_SpecialLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[4];

    struct ftCo_DatAttrs* ftAttr = &fp->co_attrs;

    if (fp->cmd_vars[0]) {
        float samus_attr_xC = samus_attr->xC;
        ftCommon_8007CADC(fp, 0.0f, ftAttr->walk_init_vel * samus_attr_xC,
                          ftAttr->walk_max_vel * samus_attr_xC);
        ftCommon_8007CB74(gobj);
    } else {
        ft_80084F3C(gobj);
    }
}

void ftSs_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;
    struct ftCo_DatAttrs* ftAttr = &fp->co_attrs;

    u8 _[8];

    ftCommon_8007D4B8(fp);
    ftCommon_8007D344(fp, 0.0f,
                      ftAttr->ground_to_air_jump_momentum_multiplier *
                          samus_attr->x10,
                      ftAttr->jump_h_max_velocity * samus_attr->x10);
}

void ftSs_SpecialLw_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    if (fp->cmd_vars[0]) {
        /// @todo Remove cast.
        if (!ft_80082888(gobj,
                         (ftCollisionBox*) &samus_attr->height_attributes))
        {
            ftSs_SpecialLw_80129048(gobj);
        }
    } else if (!ft_800827A0(gobj)) {
        ftSs_SpecialLw_80129048(gobj);
    }
}

void ftSs_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    if (fp->cmd_vars[0]) {
        if (ft_800824A0(gobj,
                        (ftCollisionBox*) &samus_attr->height_attributes))
        {
            ftSs_SpecialLw_801290A4(gobj);
        }
    } else if (ft_80081D0C(gobj)) {
        ftSs_SpecialLw_801290A4(gobj);
    }
}

void ftSs_SpecialLw_80129048(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x156, 0x10, fp->cur_anim_frame,
                              fp->frame_speed_mul, 0.0f, 0);
}

void ftSs_SpecialLw_801290A4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x155, 0x10, fp->cur_anim_frame,
                              fp->frame_speed_mul, 0.0f, 0);
}

int ftSs_SpecialLw_80129100(HSD_GObj* gobj, s32* arg1, s32* arg2)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftSs_DatAttrs* samus_attr = fp->dat_attrs;

        u8 _[4];

        if (!fp->fv.ss.x222C) {
            return -1;
        }

        *arg1 = fp->fv.ss.x2230;
        *arg2 = samus_attr->x18;
        return 0;
    }

    return -1;
}

s32 ftSs_SpecialLw_80129158(HSD_GObj* gobj)
{
    if (gobj) {
        Fighter* fp = GET_FIGHTER(gobj);
        s32 motion_state_index = fp->motion_id;
        switch (motion_state_index) {
        case 0x157:
        case 0x158:
        case 0x159:
        case 0x15A:
        case 0x15B:
        case 0x15C:
            if (fp->x2070.x2071_b6) {
                return 1;
            }
            return 0;
        }

        return 1;
    }
    return 1;
}

s32 ftSs_SpecialN_801291A8(HSD_GObj* gobj)
{
    if (gobj) {
        Fighter* fp = GET_FIGHTER(gobj);
        s32 motion_state_index = fp->motion_id;

        switch (motion_state_index) {
        case 0x157:
        case 0x158:
        case 0x15A:
        case 0x15B:
        case 0x15C:
            return 0;
        }

        return 1;
    }
    return 1;
}
