#include "ftPk_Init.h"

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/inlines.h"
#include "it/it_27CF.h"

#include <dolphin/mtx/types.h>

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
    ftCommon_8007EBAC(fp, 0xB, 0);
}

void ftPk_SpecialLw_SetState_Unk0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.pk.unk4.x4 = 3;
}

static inline f32 nested_sum_fabs(f32 fighter_pos_y, f32 pika_attr_xBC,
                                  f32 pika_attr_xBC_abs, f32 vec_y)
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
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;
    u32 state_var = fp->mv.pk.unk4.x0;

    if (!fp->mv.pk.unk4.x4) {
        return false;
    }

    if (state_var) {
        it_802B1FE8(state_var, &vec);
    } else {
        return false;
    }

    if (fabs_inline(fp->cur_pos.x - vec.x) < fabs_inline(pika_attr->xC4)) {
        f32 final_y_pos = nested_sum_fabs(fp->cur_pos.y, pika_attr->xBC,
                                          fabs_inline(pika_attr->xBC), vec.y);

        if ((final_y_pos < pika_attr->xC8) && fp->mv.pk.unk4.x0 != 0 &&
            !it_802B1DEC(fp->mv.pk.unk4.x0))
        {
            it_802B1FC8(fp->mv.pk.unk4.x0);
            return true;
        }
    }

    return false;
}

void ftPk_SpecialLw_SetState_Unk1(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.pk.unk4.x4 = 0;
}

void ftPk_SpecialLw_SpawnEffect(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Vec3 pos;
    Vec3 ef_pos;
    Vec3 vec;

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;

    {
        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[4];
#endif

        /// @todo Result of an inner function.
        bool result;
        if (fp->x2210_ThrowFlags.b0) {
            fp->x2210_ThrowFlags.b0 = false;
            result = true;
        } else {
            result = false;
        }

        if (result && fp->mv.pk.unk4.x0 == 0) {
            pos = fp->cur_pos;

            pos.y += pika_attr->xD0;
            ef_pos = pos;
            ef_pos.y += pika_attr->xCC;
            efSync_Spawn(0x4C3, gobj, &ef_pos);
            {
                vec.z = 0.0f;
                vec.x = 0.0f;
                vec.y = pika_attr->xC0;
                fp->mv.pk.unk4.x0 =
                    it_802B1DF8(gobj, &pos, &vec, pika_attr->xD4,
                                pika_attr->xD8, pika_attr->xDC);
            }
        }
    }
}

void ftPk_SpecialLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2200_ftcmd_var0 = 0;
    *((u32*) (&fp->x2210_ThrowFlags)) = 0;
    fp->mv.pk.unk4.x4 = 1;
    fp->mv.pk.unk4.x0 = 0;
    Fighter_ChangeMotionState(gobj, 0x167, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
}

void ftPk_SpecialAirLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2200_ftcmd_var0 = 0;
    *((u32*) (&fp->x2210_ThrowFlags)) = 0;
    fp->mv.pk.unk4.x4 = 1;
    fp->mv.pk.unk4.x0 = 0;
    Fighter_ChangeMotionState(gobj, 0x16B, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
}

void ftPk_SpecialLw_ChangeMotion_Unk00(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x167, 0xC4C5086, 0,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPk_SpecialLw_ChangeMotion_Unk01(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x16B, 0xC4C5086, 0,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftCommon_8007D468(fp);
}

void ftPk_SpecialLw_ChangeMotion_Unk02(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x168, 0xC4C588E, 0,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
    fp->cb.x21DC_callback_OnTakeDamage = &ftPk_SpecialLw_SetState_Unk1;
    fp->cb.x21BC_callback_Accessory4 = &ftPk_SpecialLw_SpawnEffect;
}

void ftPk_SpecialLw_ChangeMotion_Unk03(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x16C, 0xC4C588E, 0,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
    fp->cb.x21DC_callback_OnTakeDamage = &ftPk_SpecialLw_SetState_Unk1;
    fp->cb.x21BC_callback_Accessory4 = &ftPk_SpecialLw_SpawnEffect;
    ftCommon_8007D468(fp);
}

void ftPk_SpecialLw_ChangeMotion_Unk04(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x169, 0xC4C508E, 0,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPk_SpecialLw_ChangeMotion_Unk05(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x16D, 0xC4C508E, 0,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftCommon_8007D468(fp);
}

void ftPk_SpecialLw_ChangeMotion_Unk06(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x16A, 0xC4C5086, 0,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPk_SpecialLw_ChangeMotion_Unk07(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x16E, 0xC4C5086, 0,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftCommon_8007D468(fp);
}

void ftPk_SpecialLwStart_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fighter_copy;
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter_ChangeMotionState(gobj, 0x168, 0x800, 0, 0.0f, 1.0f, 0.0f);
        fighter_copy = GET_FIGHTER(gobj);
        *((u32*) (&fighter_copy->x2210_ThrowFlags)) = 0;
        fighter_copy->cb.x21DC_callback_OnTakeDamage =
            &ftPk_SpecialLw_SetState_Unk1;
        fp->cb.x21BC_callback_Accessory4 = &ftPk_SpecialLw_SpawnEffect;
    }
}

void ftPk_SpecialAirLwStart_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fighter_copy;
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter_ChangeMotionState(gobj, 0x16C, 0x800, 0, 0.0f, 1.0f, 0.0f);
        fighter_copy = GET_FIGHTER(gobj);
        *((u32*) (&fighter_copy->x2210_ThrowFlags)) = 0;
        fighter_copy->cb.x21DC_callback_OnTakeDamage =
            &ftPk_SpecialLw_SetState_Unk1;
        fp->cb.x21BC_callback_Accessory4 = &ftPk_SpecialLw_SpawnEffect;
    }
}

void ftPk_SpecialLw_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->mv.pk.unk4.x4 == 3) || fp->x2200_ftcmd_var0) {
        fp->cb.x21DC_callback_OnTakeDamage = 0;
        Fighter_ChangeMotionState(gobj, 0x16A, 0, 0, 0.0f, 1.0f, 0.0f);
        return;
    }
    if (ftPk_SpecialLw_8012765C(gobj)) {
        Fighter* fighter_copy = GET_FIGHTER(gobj);
        Fighter_ChangeMotionState(gobj, 0x169, 0, 0, 0.0f, 1.0f, 0.0f);
        fighter_copy->x2200_ftcmd_var0 = 0;
        fighter_copy->cb.x21DC_callback_OnTakeDamage = 0;
        fp = GET_FIGHTER(gobj);
        efAsync_Spawn(gobj, &fp->x60C, 0, 0x4C0,
                      fighter_copy->ft_bones[0].x0_jobj);
    }
}

void ftPk_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->mv.pk.unk4.x4 == 3) || fp->x2200_ftcmd_var0) {
        fp->cb.x21DC_callback_OnTakeDamage = 0;
        Fighter_ChangeMotionState(gobj, 0x16E, 0, 0, 0.0f, 1.0f, 0.0f);
        return;
    }
    if (ftPk_SpecialLw_8012765C(gobj)) {
        Fighter* fighter_copy = GET_FIGHTER(gobj);
        ftPikachuAttributes* pika_attr = fighter_copy->x2D4_specialAttributes;
        Fighter_ChangeMotionState(gobj, 0x16D, 0, 0, 0.0f, 1.0f, 0.0f);
        fighter_copy->x2200_ftcmd_var0 = 0;
        fighter_copy->cb.x21DC_callback_OnTakeDamage = 0;
        fighter_copy->x80_self_vel.y = (f32) pika_attr->xB4;
        fp = GET_FIGHTER(gobj);
        efAsync_Spawn(gobj, &fp->x60C, 0, 0x4C0,
                      fighter_copy->ft_bones[0].x0_jobj);
    }
}

void ftPk_SpecialLwHit_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2200_ftcmd_var0) {
        fp->cb.x21DC_callback_OnTakeDamage = 0;
        Fighter_ChangeMotionState(gobj, 0x16A, 0, 0, 0.0f, 1.0f, 0.0f);
    }
}

void ftPk_SpecialAirLwHit_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2200_ftcmd_var0) {
        fp->cb.x21DC_callback_OnTakeDamage = 0;
        Fighter_ChangeMotionState(gobj, 0x16E, 0, 0, 0.0f, 1.0f, 0.0f);
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
        ft_800CC730(gobj);
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

void ftPk_SpecialLw_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPk_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftPk_SpecialLwHit_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPk_SpecialAirLwHit_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;
    f32 pika_B8 = pika_attr->xB8;
    f32 terminal_velocity = fp->x110_attr.x170_TerminalVelocity;
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
    ft_80082C74(gobj, &ftPk_SpecialLw_ChangeMotion_Unk00);
}

void ftPk_SpecialLw_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, &ftPk_SpecialLw_ChangeMotion_Unk03);
}

void ftPk_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, &ftPk_SpecialLw_ChangeMotion_Unk02);
}

void ftPk_SpecialLwHit_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, &ftPk_SpecialLw_ChangeMotion_Unk05);
}

void ftPk_SpecialAirLwHit_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, &ftPk_SpecialLw_ChangeMotion_Unk04);
}

void ftPk_SpecialLwEnd_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, &ftPk_SpecialLw_ChangeMotion_Unk07);
}

void ftPk_SpecialAirLwEnd_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, &ftPk_SpecialLw_ChangeMotion_Unk06);
}
