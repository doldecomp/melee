#include "ftpikachu.h"

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/efsync.h"
#include "ft/code_80081B38.h"
#include "ft/fighter.h"
#include "ft/ft_unknown_006.h"
#include "it/code_8027CF30.h"

bool ftPikachu_CheckProperty_801275CC(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

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

void ftPikachu_80127608(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_80030E44(2, &fp->xB0_pos);
    func_8007EBAC(fp, 0xB, 0);
}

void ftPikachu_SetState_8012764C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    fp->x2344_stateVar2 = 3;
}

static inline f32 nested_sum_fabs(f32 fighter_pos_y, f32 pika_attr_xBC,
                                  f32 pika_attr_xBC_abs, f32 vec_y)
{
    if (fighter_pos_y + pika_attr_xBC_abs - vec_y < 0.0f)
        return -(fighter_pos_y + fabs_inline(pika_attr_xBC) - vec_y);
    else
        return fighter_pos_y + fabs_inline(pika_attr_xBC) - vec_y;
}

bool ftPikachu_8012765C(HSD_GObj* fighter_gobj)
{
    Vec3 vec;
    Fighter* fp = fighter_gobj->user_data;
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;
    u32 state_var = fp->x2340_stateVar1_u32;

    if (!fp->x2344_stateVar2_s32)
        return false;

    if (state_var)
        func_802B1FE8(state_var, &vec);
    else
        return false;

    if (fabs_inline(fp->xB0_pos.x - vec.x) < fabs_inline(pika_attr->xC4)) {
        f32 final_y_pos = nested_sum_fabs(fp->xB0_pos.y, pika_attr->xBC,
                                          fabs_inline(pika_attr->xBC), vec.y);

        if ((final_y_pos < pika_attr->xC8) && fp->x2340_stateVar1_u32 &&
            !func_802B1DEC(fp->x2340_stateVar1_u32))
        {
            func_802B1FC8(fp->x2340_stateVar1_u32);
            return true;
        }
    }

    return false;
}

void ftPikachu_SetState_8012779C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    fp->x2344_stateVar2 = 0;
}

void ftPikachu_EfSpawn_801277AC(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[4];
#endif

    Vec3 pos;
    Vec3 ef_pos;
    Vec3 vec;

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;

    {
        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 unused[4];
#endif

        /// @todo Result of an inner function.
        bool result;
        if (fp->x2210_ThrowFlags.b0) {
            fp->x2210_ThrowFlags.b0 = false;
            result = true;
        } else {
            result = false;
        }

        if (result && !fp->x2340_stateVar1_u32) {
            pos = fp->xB0_pos;

            pos.y += pika_attr->xD0;
            ef_pos = pos;
            ef_pos.y += pika_attr->xCC;
            ef_Spawn(0x4C3, fighter_gobj, &ef_pos);
            {
                vec.z = 0.0f;
                vec.x = 0.0f;
                vec.y = pika_attr->xC0;
                fp->x2340_stateVar1 =
                    func_802B1DF8(fighter_gobj, &pos, &vec, pika_attr->xD4,
                                  pika_attr->xD8, pika_attr->xDC);
            }
        }
    }
}

void ftPikachu_SpecialLw_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    fp->x2200_ftcmd_var0 = 0;
    *((u32*) (&fp->x2210_ThrowFlags)) = 0;
    fp->x2344_stateVar2 = 1;
    fp->x2340_stateVar1 = 0;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x167, 0, 0, 0.0f, 1.0f,
                                       0.0f);
    func_8006EBA4(fighter_gobj);
}

void ftPikachu_SpecialAirLw_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    fp->x2200_ftcmd_var0 = 0;
    *((u32*) (&fp->x2210_ThrowFlags)) = 0;
    fp->x2344_stateVar2 = 1;
    fp->x2340_stateVar1 = 0;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16B, 0, 0, 0.0f, 1.0f,
                                       0.0f);
    func_8006EBA4(fighter_gobj);
}

void ftPikachu_ActionChange_8012798C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x167, 0xC4C5086, 0,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_ActionChange_801279EC(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16B, 0xC4C5086, 0,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007D468(fp);
}

void ftPikachu_ActionChange_80127A54(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x168, 0xC4C588E, 0,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
    fp->cb.x21DC_callback_OnTakeDamage = &ftPikachu_SetState_8012779C;
    fp->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_801277AC;
}

void ftPikachu_ActionChange_80127ACC(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16C, 0xC4C588E, 0,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
    fp->cb.x21DC_callback_OnTakeDamage = &ftPikachu_SetState_8012779C;
    fp->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_801277AC;
    func_8007D468(fp);
}

void ftPikachu_ActionChange_80127B4C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x169, 0xC4C508E, 0,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_ActionChange_80127BAC(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16D, 0xC4C508E, 0,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007D468(fp);
}

void ftPikachu_ActionChange_80127C14(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16A, 0xC4C5086, 0,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_ActionChange_80127C74(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16E, 0xC4C5086, 0,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007D468(fp);
}

void ftPikachu_ActionChange_80127CDC(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter* fighter_copy;
        Fighter* fp = GET_FIGHTER(fighter_gobj);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x168, 0x800, 0, 0.0f,
                                           1.0f, 0.0f);
        fighter_copy = GET_FIGHTER(fighter_gobj);
        *((u32*) (&fighter_copy->x2210_ThrowFlags)) = 0;
        fighter_copy->cb.x21DC_callback_OnTakeDamage =
            &ftPikachu_SetState_8012779C;
        fp->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_801277AC;
    }
}

void ftPikachu_ActionChange_80127D60(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter* fighter_copy;
        Fighter* fp = GET_FIGHTER(fighter_gobj);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16C, 0x800, 0, 0.0f,
                                           1.0f, 0.0f);
        fighter_copy = GET_FIGHTER(fighter_gobj);
        *((u32*) (&fighter_copy->x2210_ThrowFlags)) = 0;
        fighter_copy->cb.x21DC_callback_OnTakeDamage =
            &ftPikachu_SetState_8012779C;
        fp->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_801277AC;
    }
}

void ftPikachu_ActionChange_80127DE4(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if ((fp->x2344_stateVar2_s32 == 3) || fp->x2200_ftcmd_var0) {
        fp->cb.x21DC_callback_OnTakeDamage = 0;
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16A, 0, 0, 0.0f,
                                           1.0f, 0.0f);
        return;
    }
    if (ftPikachu_8012765C(fighter_gobj)) {
        Fighter* fighter_copy = GET_FIGHTER(fighter_gobj);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x169, 0, 0, 0.0f,
                                           1.0f, 0.0f);
        fighter_copy->x2200_ftcmd_var0 = 0;
        fighter_copy->cb.x21DC_callback_OnTakeDamage = 0;
        fp = GET_FIGHTER(fighter_gobj);
        efAsync_Spawn(fighter_gobj, &fp->x60C, 0, 0x4C0,
                      fighter_copy->x5E8_fighterBones[0].x0_jobj);
    }
}

void ftPikachu_ActionChange_80127EC0(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[24];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if ((fp->x2344_stateVar2_s32 == 3) || fp->x2200_ftcmd_var0) {
        fp->cb.x21DC_callback_OnTakeDamage = 0;
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16E, 0, 0, 0.0f,
                                           1.0f, 0.0f);
        return;
    }
    if (ftPikachu_8012765C(fighter_gobj)) {
        Fighter* fighter_copy = GET_FIGHTER(fighter_gobj);
        ftPikachuAttributes* pika_attr = fighter_copy->x2D4_specialAttributes;
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16D, 0, 0, 0.0f,
                                           1.0f, 0.0f);
        fighter_copy->x2200_ftcmd_var0 = 0;
        fighter_copy->cb.x21DC_callback_OnTakeDamage = 0;
        fighter_copy->x80_self_vel.y = (f32) pika_attr->xB4;
        fp = GET_FIGHTER(fighter_gobj);
        efAsync_Spawn(fighter_gobj, &fp->x60C, 0, 0x4C0,
                      fighter_copy->x5E8_fighterBones[0].x0_jobj);
    }
}

void ftPikachu_ActionChange_80127FB0(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (fp->x2200_ftcmd_var0) {
        fp->cb.x21DC_callback_OnTakeDamage = 0;
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16A, 0, 0, 0.0f,
                                           1.0f, 0.0f);
    }
}

void ftPikachu_ActionChange_80128000(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (fp->x2200_ftcmd_var0) {
        fp->cb.x21DC_callback_OnTakeDamage = 0;
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16E, 0, 0, 0.0f,
                                           1.0f, 0.0f);
    }
}

void ftPikachu_80128050(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        func_8008A2BC(fighter_gobj);
}

void ftPikachu_8012808C(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        func_800CC730(fighter_gobj);
}

void ftPikachu_801280C8(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

void ftPikachu_801280E8(HSD_GObj* fighter_gobj)
{
    func_80084EEC(fighter_gobj);
}

void ftPikachu_80128108(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

void ftPikachu_80128128(HSD_GObj* fighter_gobj)
{
    func_80084EEC(fighter_gobj);
}

void ftPikachu_80128148(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

void ftPikachu_80128168(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;
    f32 pika_B8 = pika_attr->xB8;
    f32 terminal_velocity = fp->x110_attr.x170_TerminalVelocity;
    func_8007D494(fp, pika_B8, terminal_velocity);
    func_8007CF58(fp);
}

void ftPikachu_801281AC(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

void ftPikachu_801281CC(HSD_GObj* fighter_gobj)
{
    func_80084EEC(fighter_gobj);
}

void ftPikachu_PrepCallActionChange_801281EC(HSD_GObj* fighter_gobj)
{
    func_8008403C(fighter_gobj, &ftPikachu_ActionChange_801279EC);
}

void ftPikachu_PrepCallActionChange_80128214(HSD_GObj* fighter_gobj)
{
    func_80082C74(fighter_gobj, &ftPikachu_ActionChange_8012798C);
}

void ftPikachu_PrepCallActionChange_8012823C(HSD_GObj* fighter_gobj)
{
    func_8008403C(fighter_gobj, &ftPikachu_ActionChange_80127ACC);
}

void ftPikachu_PrepCallActionChange_80128264(HSD_GObj* fighter_gobj)
{
    func_80082C74(fighter_gobj, &ftPikachu_ActionChange_80127A54);
}

void ftPikachu_PrepCallActionChange_8012828C(HSD_GObj* fighter_gobj)
{
    func_8008403C(fighter_gobj, &ftPikachu_ActionChange_80127BAC);
}

void ftPikachu_PrepCallActionChange_801282B4(HSD_GObj* fighter_gobj)
{
    func_80082C74(fighter_gobj, &ftPikachu_ActionChange_80127B4C);
}

void ftPikachu_PrepCallActionChange_801282DC(HSD_GObj* fighter_gobj)
{
    func_8008403C(fighter_gobj, &ftPikachu_ActionChange_80127C74);
}

void ftPikachu_PrepCallActionChange_80128304(HSD_GObj* fighter_gobj)
{
    func_80082C74(fighter_gobj, &ftPikachu_ActionChange_80127C14);
}
