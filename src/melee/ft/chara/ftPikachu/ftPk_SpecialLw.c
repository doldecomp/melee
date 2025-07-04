#include <platform.h>

#include "ftPk_SpecialLw.h"

#include "math.h"

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftPikachu/types.h"
#include "it/items/itpikachuthunder.h"

#include <dolphin/mtx.h>

bool ftPk_SpecialLw_CheckProperty(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    s32 value = fp->x2070.x2071_b0_3;

    switch (value) {
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        return true;
    default:
        return false;
    }
}

void ftPk_SpecialLw_80127608(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Camera_80030E44(2, &fp->cur_pos);
    ftCommon_8007EBAC(fp, 11, 0);
}

void ftPk_SpecialLw_SetState_Unk0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.pk.specialhi.x4 = 3;
}

static inline float nested_sum_fabs(float fighter_pos_y, float pika_attr_xBC,
                                    float pika_attr_xBC_abs, float vec_y)
{
    if (fighter_pos_y + pika_attr_xBC_abs - vec_y < 0.0f) {
        return -(fighter_pos_y + fabs_inline(pika_attr_xBC) - vec_y);
    } else {
        return fighter_pos_y + fabs_inline(pika_attr_xBC) - vec_y;
    }
}

bool ftPk_SpecialLw_8012765C(HSD_GObj* gobj)
{
    Vec3 vec;
    Fighter* fp = gobj->user_data;
    ftPikachuAttributes* pika_attr = fp->dat_attrs;
    Item_GObj* thunder_gobj = fp->mv.pk.speciallw.x0;

    if (!fp->mv.pk.speciallw.x4) {
        return false;
    }

    if (thunder_gobj) {
        it_802B1FE8(thunder_gobj, &vec);
    } else {
        return false;
    }

    if (fabs_inline(fp->cur_pos.x - vec.x) < fabs_inline(pika_attr->xC4)) {
        float final_y_pos = nested_sum_fabs(
            fp->cur_pos.y, pika_attr->xBC, fabs_inline(pika_attr->xBC), vec.y);

        if ((final_y_pos < pika_attr->xC8) && fp->mv.pk.speciallw.x0 != NULL &&
            !it_802B1DEC(fp->mv.pk.speciallw.x0))
        {
            it_802B1FC8(fp->mv.pk.speciallw.x0);
            return true;
        }
    }

    return false;
}

void ftPk_SpecialLw_SetState_Unk1(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.pk.specialhi.x4 = 0;
}

void ftPk_SpecialLw_SpawnEffect(HSD_GObj* gobj)
{
    u8 _[4];

    Vec3 pos;
    Vec3 ef_pos;
    Vec3 vec;

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->dat_attrs;

    {
        u8 _[4];

        /// @todo Result of an inner function.
        bool result;
        if (fp->throw_flags_b0) {
            fp->throw_flags_b0 = false;
            result = true;
        } else {
            result = false;
        }

        if (result && !fp->mv.pk.speciallw.x0) {
            pos = fp->cur_pos;

            pos.y += pika_attr->xD0;
            ef_pos = pos;
            ef_pos.y += pika_attr->xCC;
            efSync_Spawn(1219, gobj, &ef_pos);
            {
                vec.z = 0.0f;
                vec.x = 0.0f;
                vec.y = pika_attr->xC0;
                fp->mv.pk.speciallw.x0 =
                    it_802B1DF8(gobj, &pos, &vec, pika_attr->xD4,
                                pika_attr->xD8, pika_attr->xDC);
            }
        }
    }
}

void ftPk_SpecialLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    fp->mv.pk.specialhi.x4 = 1;
    fp->mv.pk.specialhi.x0 = 0;
    Fighter_ChangeMotionState(gobj, 359, 0, 0.0f, 1.0f, 0.0f, 0);
    ftAnim_8006EBA4(gobj);
}

void ftPk_SpecialAirLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    fp->mv.pk.specialhi.x4 = 1;
    fp->mv.pk.specialhi.x0 = 0;
    Fighter_ChangeMotionState(gobj, 363, 0, 0.0f, 1.0f, 0.0f, 0);
    ftAnim_8006EBA4(gobj);
}

void ftPk_SpecialLw_ChangeMotion_Unk00(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 359, 206327942, fp->cur_anim_frame, 1.0f,
                              0.0f, 0);
}

void ftPk_SpecialLw_ChangeMotion_Unk01(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 363, 206327942, fp->cur_anim_frame, 1.0f,
                              0.0f, 0);
    ftCommon_8007D468(fp);
}

void ftPk_SpecialLw_ChangeMotion_Unk02(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 360, 206329998, fp->cur_anim_frame, 1.0f,
                              0.0f, 0);
    fp->take_dmg_cb = &ftPk_SpecialLw_SetState_Unk1;
    fp->accessory4_cb = &ftPk_SpecialLw_SpawnEffect;
}

void ftPk_SpecialLw_ChangeMotion_Unk03(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 364, 206329998, fp->cur_anim_frame, 1.0f,
                              0.0f, 0);
    fp->take_dmg_cb = &ftPk_SpecialLw_SetState_Unk1;
    fp->accessory4_cb = &ftPk_SpecialLw_SpawnEffect;
    ftCommon_8007D468(fp);
}

void ftPk_SpecialLw_ChangeMotion_Unk04(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 361, 206327950, fp->cur_anim_frame, 1.0f,
                              0.0f, 0);
}

void ftPk_SpecialLw_ChangeMotion_Unk05(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 365, 206327950, fp->cur_anim_frame, 1.0f,
                              0.0f, 0);
    ftCommon_8007D468(fp);
}

void ftPk_SpecialLw_ChangeMotion_Unk06(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 362, 206327942, fp->cur_anim_frame, 1.0f,
                              0.0f, 0);
}

void ftPk_SpecialLw_ChangeMotion_Unk07(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 366, 206327942, fp->cur_anim_frame, 1.0f,
                              0.0f, 0);
    ftCommon_8007D468(fp);
}

void ftPk_SpecialLwStart_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fighter_copy;
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter_ChangeMotionState(gobj, 360, 2048, 0.0f, 1.0f, 0.0f, 0);
        fighter_copy = GET_FIGHTER(gobj);
        fighter_copy->throw_flags = 0;
        fighter_copy->take_dmg_cb = &ftPk_SpecialLw_SetState_Unk1;
        fp->accessory4_cb = &ftPk_SpecialLw_SpawnEffect;
    }
}

void ftPk_SpecialAirLwStart_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fighter_copy;
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter_ChangeMotionState(gobj, 364, 2048, 0.0f, 1.0f, 0.0f, 0);
        fighter_copy = GET_FIGHTER(gobj);
        fighter_copy->throw_flags = 0;
        fighter_copy->take_dmg_cb = &ftPk_SpecialLw_SetState_Unk1;
        fp->accessory4_cb = &ftPk_SpecialLw_SpawnEffect;
    }
}

void ftPk_SpecialLwLoop0_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->mv.pk.specialhi.x4 == 3) || fp->cmd_vars[0]) {
        fp->take_dmg_cb = 0;
        Fighter_ChangeMotionState(gobj, 362, 0, 0.0f, 1.0f, 0.0f, 0);
        return;
    }
    if (ftPk_SpecialLw_8012765C(gobj)) {
        Fighter* fighter_copy = GET_FIGHTER(gobj);
        Fighter_ChangeMotionState(gobj, 361, 0, 0.0f, 1.0f, 0.0f, 0);
        fighter_copy->cmd_vars[0] = 0;
        fighter_copy->take_dmg_cb = 0;
        fp = GET_FIGHTER(gobj);
        efAsync_Spawn(gobj, &fp->x60C, 0, 1216,
                      fighter_copy->parts[FtPart_TopN].joint);
    }
}

void ftPk_SpecialAirLwLoop0_Anim(HSD_GObj* gobj)
{
    u8 _[24];

    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->mv.pk.specialhi.x4 == 3) || fp->cmd_vars[0]) {
        fp->take_dmg_cb = 0;
        Fighter_ChangeMotionState(gobj, 366, 0, 0.0f, 1.0f, 0.0f, 0);
        return;
    }
    if (ftPk_SpecialLw_8012765C(gobj)) {
        Fighter* fighter_copy = GET_FIGHTER(gobj);
        ftPikachuAttributes* pika_attr = fighter_copy->dat_attrs;
        Fighter_ChangeMotionState(gobj, 365, 0, 0.0f, 1.0f, 0.0f, 0);
        fighter_copy->cmd_vars[0] = 0;
        fighter_copy->take_dmg_cb = NULL;
        fighter_copy->self_vel.y = (float) pika_attr->xB4;
        fp = GET_FIGHTER(gobj);
        efAsync_Spawn(gobj, &fp->x60C, 0, 1216,
                      fighter_copy->parts[FtPart_TopN].joint);
    }
}

void ftPk_SpecialLwLoop1_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0]) {
        fp->take_dmg_cb = 0;
        Fighter_ChangeMotionState(gobj, 362, 0, 0.0f, 1.0f, 0.0f, 0);
    }
}

void ftPk_SpecialAirLwLoop1_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0]) {
        fp->take_dmg_cb = 0;
        Fighter_ChangeMotionState(gobj, 366, 0, 0.0f, 1.0f, 0.0f, 0);
    }
}

void ftPk_SpecialLwEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftPk_SpecialAirLwEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800CC730(gobj);
    }
}

void ftPk_SpecialLwStart_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPk_SpecialAirLwStart_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftPk_SpecialLwLoop0_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPk_SpecialAirLwLoop0_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftPk_SpecialLwLoop1_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPk_SpecialAirLwLoop1_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->dat_attrs;
    float pika_B8 = pika_attr->xB8;
    float terminal_velocity = fp->co_attrs.terminal_vel;
    ftCommon_8007D494(fp, pika_B8, terminal_velocity);
    ftCommon_8007CF58(fp);
}

void ftPk_SpecialLwEnd_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPk_SpecialAirLwEnd_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftPk_SpecialLwStart_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, &ftPk_SpecialLw_ChangeMotion_Unk01);
}

void ftPk_SpecialAirLwStart_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, ftPk_SpecialLw_ChangeMotion_Unk00);
}

void ftPk_SpecialLwLoop0_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, ftPk_SpecialLw_ChangeMotion_Unk03);
}

void ftPk_SpecialAirLwLoop0_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, ftPk_SpecialLw_ChangeMotion_Unk02);
}

void ftPk_SpecialLwLoop1_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, ftPk_SpecialLw_ChangeMotion_Unk05);
}

void ftPk_SpecialAirLwLoop1_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, ftPk_SpecialLw_ChangeMotion_Unk04);
}

void ftPk_SpecialLwEnd_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, ftPk_SpecialLw_ChangeMotion_Unk07);
}

void ftPk_SpecialAirLwEnd_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, ftPk_SpecialLw_ChangeMotion_Unk06);
}
