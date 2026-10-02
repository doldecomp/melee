/**
 * @file ftpikachuspeciallw.c
 * @brief Pikachu
 * @details This file contains Pikachu's specific functions.
 * Module prefix: ftPk
 */

#include "ftpikachuspeciallw.h"

#include <Runtime/platform.h>

#include <melee/ft/forward.h>

#include "forward.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <melee/cm/camera.h>
#include <melee/ef/efasync.h>
#include <melee/ef/efsync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/kinds/ftCommon/inlines.h>
#include <melee/ft/types.h>
#include <melee/it/kinds/itpikachuthunder.h>

/**
 * @brief Function for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
bool ftPk_SpecialLw_CheckProperty(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    s32 value = fp->x2070.x0.x2071_b0_3;

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

/**
 * @brief Function for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLw_80127608(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Camera_RequestQuake(QuakeKind_Small, &fp->cur_pos);
    ftCommon_8007EBAC(fp, 11, 0);
}

/**
 * @brief Function for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLw_SetState_Unk0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.pk.specialhi.x4 = 3;
}

/**
 * @brief Function for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
bool ftPk_SpecialLw_8012765C(HSD_GObj* gobj)
{
    Vec3 vec;
    Fighter* fp = GET_FIGHTER(gobj);
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

    if (ABS(fp->cur_pos.x - vec.x) < ABS(pika_attr->xC4)) {
        float final_y_pos = ABS(fp->cur_pos.y + ABS(pika_attr->xBC) - vec.y);

        if ((final_y_pos < pika_attr->xC8) && fp->mv.pk.speciallw.x0 != NULL &&
            !it_802B1DEC(fp->mv.pk.speciallw.x0))
        {
            it_802B1FC8(fp->mv.pk.speciallw.x0);
            return true;
        }
    }

    return false;
}

/**
 * @brief Function for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLw_SetState_Unk1(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.pk.specialhi.x4 = 0;
}

/**
 * @brief Function for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
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

        if (ftCheckThrowB0(fp) && !fp->mv.pk.speciallw.x0) {
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

/**
 * @brief Action State initialization for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    fp->x2210.throw_flags = 0;
    fp->mv.pk.specialhi.x4 = 1;
    fp->mv.pk.specialhi.x0 = 0;
    Fighter_ChangeMotionState(gobj, 359, Ft_MF_None, 0.0f, 1.0f, 0.0f, 0);
    ftAnim_8006EBA4(gobj);
}

/**
 * @brief Action State initialization for
 * @param gobj The fighter's game object
 */
void ftPk_SpecialAirLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    fp->x2210.throw_flags = 0;
    fp->mv.pk.specialhi.x4 = 1;
    fp->mv.pk.specialhi.x0 = 0;
    Fighter_ChangeMotionState(gobj, 363, Ft_MF_None, 0.0f, 1.0f, 0.0f, 0);
    ftAnim_8006EBA4(gobj);
}

/**
 * @brief Function for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLw_ChangeMotion_Unk00(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    ftCommon_AirToGroundStateChange(gobj, fp, 359, ftPk_MF_SpecialLw_Coll);
}

/**
 * @brief Function for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLw_ChangeMotion_Unk01(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_GroundToAirStateChange(gobj, fp, 363, ftPk_MF_SpecialLw_Coll);
    ftCommon_ClampAirDrift(fp);
}

/**
 * @brief Function for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLw_ChangeMotion_Unk02(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    ftCommon_AirToGroundStateChange(gobj, fp, 360,
                                    ftPk_MF_SpecialLwHitRumble_Coll);
    fp->take_dmg_cb = &ftPk_SpecialLw_SetState_Unk1;
    fp->accessory4_cb = &ftPk_SpecialLw_SpawnEffect;
}

/**
 * @brief Function for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLw_ChangeMotion_Unk03(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_GroundToAirStateChange(gobj, fp, 364,
                                    ftPk_MF_SpecialLwHitRumble_Coll);
    fp->take_dmg_cb = &ftPk_SpecialLw_SetState_Unk1;
    fp->accessory4_cb = &ftPk_SpecialLw_SpawnEffect;
    ftCommon_ClampAirDrift(fp);
}

/**
 * @brief Function for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLw_ChangeMotion_Unk04(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    ftCommon_AirToGroundStateChange(gobj, fp, 361, ftPk_MF_SpecialLwHit_Coll);
}

/**
 * @brief Function for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLw_ChangeMotion_Unk05(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_GroundToAirStateChange(gobj, fp, 365, ftPk_MF_SpecialLwHit_Coll);
    ftCommon_ClampAirDrift(fp);
}

/**
 * @brief Function for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLw_ChangeMotion_Unk06(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    ftCommon_AirToGroundStateChange(gobj, fp, 362, ftPk_MF_SpecialLw_Coll);
}

/**
 * @brief Function for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLw_ChangeMotion_Unk07(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_GroundToAirStateChange(gobj, fp, 366, ftPk_MF_SpecialLw_Coll);
    ftCommon_ClampAirDrift(fp);
}

/**
 * @brief Animation callback for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLwStart_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fighter_copy;
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter_ChangeMotionState(gobj, 360, Ft_MF_SkipRumble, 0.0f, 1.0f,
                                  0.0f, 0);
        fighter_copy = GET_FIGHTER(gobj);
        fighter_copy->x2210.throw_flags = 0;
        fighter_copy->take_dmg_cb = &ftPk_SpecialLw_SetState_Unk1;
        fp->accessory4_cb = &ftPk_SpecialLw_SpawnEffect;
    }
}

/**
 * @brief Animation callback for
 * @param gobj The fighter's game object
 */
void ftPk_SpecialAirLwStart_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fighter_copy;
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter_ChangeMotionState(gobj, 364, Ft_MF_SkipRumble, 0.0f, 1.0f,
                                  0.0f, 0);
        fighter_copy = GET_FIGHTER(gobj);
        fighter_copy->x2210.throw_flags = 0;
        fighter_copy->take_dmg_cb = &ftPk_SpecialLw_SetState_Unk1;
        fp->accessory4_cb = &ftPk_SpecialLw_SpawnEffect;
    }
}

/**
 * @brief Animation callback for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLwLoop0_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->mv.pk.specialhi.x4 == 3) || fp->cmd_vars[0]) {
        fp->take_dmg_cb = 0;
        Fighter_ChangeMotionState(gobj, 362, Ft_MF_None, 0.0f, 1.0f, 0.0f, 0);
        return;
    }
    if (ftPk_SpecialLw_8012765C(gobj)) {
        Fighter* fighter_copy = GET_FIGHTER(gobj);
        Fighter_ChangeMotionState(gobj, 361, Ft_MF_None, 0.0f, 1.0f, 0.0f, 0);
        fighter_copy->cmd_vars[0] = 0;
        fighter_copy->take_dmg_cb = 0;
        fp = GET_FIGHTER(gobj);
        efAsync_Spawn(gobj, &fp->x60C, 0, 1216,
                      fighter_copy->parts[FtPart_TopN].joint);
    }
}

/**
 * @brief Animation callback for
 * @param gobj The fighter's game object
 */
void ftPk_SpecialAirLwLoop0_Anim(HSD_GObj* gobj)
{
    u8 _[24];

    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->mv.pk.specialhi.x4 == 3) || fp->cmd_vars[0]) {
        fp->take_dmg_cb = 0;
        Fighter_ChangeMotionState(gobj, 366, Ft_MF_None, 0.0f, 1.0f, 0.0f, 0);
        return;
    }
    if (ftPk_SpecialLw_8012765C(gobj)) {
        Fighter* fighter_copy = GET_FIGHTER(gobj);
        ftPikachuAttributes* pika_attr = fighter_copy->dat_attrs;
        Fighter_ChangeMotionState(gobj, 365, Ft_MF_None, 0.0f, 1.0f, 0.0f, 0);
        fighter_copy->cmd_vars[0] = 0;
        fighter_copy->take_dmg_cb = NULL;
        fighter_copy->self_vel.y = pika_attr->xB4;
        fp = GET_FIGHTER(gobj);
        efAsync_Spawn(gobj, &fp->x60C, 0, 1216,
                      fighter_copy->parts[FtPart_TopN].joint);
    }
}

/**
 * @brief Animation callback for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLwLoop1_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0]) {
        fp->take_dmg_cb = 0;
        Fighter_ChangeMotionState(gobj, 362, Ft_MF_None, 0.0f, 1.0f, 0.0f, 0);
    }
}

/**
 * @brief Animation callback for
 * @param gobj The fighter's game object
 */
void ftPk_SpecialAirLwLoop1_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0]) {
        fp->take_dmg_cb = 0;
        Fighter_ChangeMotionState(gobj, 366, Ft_MF_None, 0.0f, 1.0f, 0.0f, 0);
    }
}

/**
 * @brief Animation callback for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLwEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

/**
 * @brief Animation callback for
 * @param gobj The fighter's game object
 */
void ftPk_SpecialAirLwEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

/**
 * @brief Physics callback for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLwStart_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics callback for
 * @param gobj The fighter's game object
 */
void ftPk_SpecialAirLwStart_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/**
 * @brief Physics callback for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLwLoop0_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics callback for
 * @param gobj The fighter's game object
 */
void ftPk_SpecialAirLwLoop0_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/**
 * @brief Physics callback for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLwLoop1_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics callback for
 * @param gobj The fighter's game object
 */
void ftPk_SpecialAirLwLoop1_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->dat_attrs;
    float pika_B8 = pika_attr->xB8;
    float terminal_velocity = fp->co_attrs.terminal_velocity;
    ftCommon_Fall(fp, pika_B8, terminal_velocity);
    ftCommon_CalcSelfAccel_DeaccelQuickAir(fp);
}

/**
 * @brief Physics callback for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLwEnd_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics callback for
 * @param gobj The fighter's game object
 */
void ftPk_SpecialAirLwEnd_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/**
 * @brief Collision callback for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLwStart_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, &ftPk_SpecialLw_ChangeMotion_Unk01);
}

/**
 * @brief Collision callback for
 * @param gobj The fighter's game object
 */
void ftPk_SpecialAirLwStart_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, ftPk_SpecialLw_ChangeMotion_Unk00);
}

/**
 * @brief Collision callback for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLwLoop0_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, ftPk_SpecialLw_ChangeMotion_Unk03);
}

/**
 * @brief Collision callback for
 * @param gobj The fighter's game object
 */
void ftPk_SpecialAirLwLoop0_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, ftPk_SpecialLw_ChangeMotion_Unk02);
}

/**
 * @brief Collision callback for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLwLoop1_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, ftPk_SpecialLw_ChangeMotion_Unk05);
}

/**
 * @brief Collision callback for
 * @param gobj The fighter's game object
 */
void ftPk_SpecialAirLwLoop1_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, ftPk_SpecialLw_ChangeMotion_Unk04);
}

/**
 * @brief Collision callback for Down-B (Thunder)
 * @param gobj The fighter's game object
 */
void ftPk_SpecialLwEnd_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, ftPk_SpecialLw_ChangeMotion_Unk07);
}

/**
 * @brief Collision callback for
 * @param gobj The fighter's game object
 */
void ftPk_SpecialAirLwEnd_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, ftPk_SpecialLw_ChangeMotion_Unk06);
}
