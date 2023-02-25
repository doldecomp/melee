#include <melee/ft/chara/ftZelda/ftzelda.h>

#include <melee/ef/eflib.h>
#include <melee/ef/efsync.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcoll.h>

void ftZelda_8013A830(HSD_GObj* fighter_gobj)
{
    Fighter* fp; // r31

    fp = GET_FIGHTER(fighter_gobj);
    if (fp->x2219_flag.bits.b0 == 0) {
        ef_Spawn(0x4F4, fighter_gobj, fp->x5E8_fighterBones[1].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
}

void ftZelda_8013A8AC(HSD_GObj* fighter_gobj)
{
    Fighter* fp; // r31

    fp = GET_FIGHTER(fighter_gobj);
    if (fp->x2219_flag.bits.b0 == 0) {
        ef_Spawn(0x4F5, fighter_gobj, fp->x5E8_fighterBones[1].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
}

inline void startActionHelper(HSD_GObj* fighter_gobj)
{
    ftZeldaAttributes* attributes;
    Fighter* fighter2; // r5
    fighter2 = GET_FIGHTER(fighter_gobj);
    attributes = fighter2->x2D4_specialAttributes;
    fighter2->x2200_ftcmd_var0 = 0;
    fighter2->x2340_stateVar1 = attributes->x4;
}

void ftZelda_SpecialN_StartAction(HSD_GObj* fighter_gobj)
{
    f32 temp_f1;
    Fighter* fp; // r31

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[11];
#endif

    temp_f1 = 0;
    fp = GET_FIGHTER(fighter_gobj);

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x155, 0, NULL, temp_f1,
                                       1.0, temp_f1);
    func_8006EBA4(fighter_gobj);
    startActionHelper(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = &ftZelda_8013A830;
}

void ftZelda_SpecialAirN_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp; // r31
    ftZeldaAttributes* attributes;
    f32 unused[5];

    fp = GET_FIGHTER(fighter_gobj);
    attributes = (ftZeldaAttributes*) fp->x2D4_specialAttributes;
    fp->x80_self_vel.y = 0;
    fp->x80_self_vel.x = fp->x80_self_vel.x / attributes->x8;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x156, 0, NULL, 0, 1.0, 0);
    func_8006EBA4(fighter_gobj);

    startActionHelper(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = &ftZelda_8013A8AC;
}

void ftZelda_8013AA38(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    ftZeldaAttributes* attributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[12];
#endif

    fp = GET_FIGHTER(fighter_gobj);
    attributes = fp->x2D4_specialAttributes;

    if (fp->x2200_ftcmd_var0 == 1) {
        fp->x2200_ftcmd_var0 = 2;
        ftColl_CreateReflectHit(fighter_gobj, &attributes->x84,
                                &ftZelda_8013ADB0);
    }

    if (fp->x2200_ftcmd_var0 == 0)
        fp->x2218_flag.bits.b3 = 0;

    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        func_8008A2BC(fighter_gobj);
}

// 8013AACC - 8013AB60 (0x94 bytes)
// https://decomp.me/scratch/ttWvN
void ftZelda_8013AACC(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    ftZeldaAttributes* attributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[12];
#endif

    fp = GET_FIGHTER(fighter_gobj);
    attributes = fp->x2D4_specialAttributes;

    if (fp->x2200_ftcmd_var0 == 1U) {
        fp->x2200_ftcmd_var0 = 2U;
        ftColl_CreateReflectHit(fighter_gobj, &attributes->x84,
                                &ftZelda_8013ADB0);
    }

    if (fp->x2200_ftcmd_var0 == 0U) {
        fp->x2218_flag.bits.b3 = 0;
    }

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_800CC730(fighter_gobj);
    }
}

void ftZelda_8013AB60(HSD_GObj* fighter_gobj)
{
    return;
}
void ftZelda_8013AB64(HSD_GObj* fighter_gobj)
{
    return;
}

// 8013AB68 - 8013AB9C (0x34 bytes)
void ftZelda_8013AB68(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
    func_8007AEF8(fighter_gobj);
}

// 8013AB9C - 8013AC10 (0x74 bytes)
// https://decomp.me/scratch/juoPH
void ftZelda_8013AB9C(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    s32 stateVar1;
    attr* fighterAttr;
    ftZeldaAttributes* charAttr;
    f32 arg2, arg3;
    s32 unused[2];

    fp = GET_FIGHTER(fighter_gobj);
    stateVar1 = fp->x2340_stateVar1;
    fighterAttr = &fp->x110_attr;
    charAttr = fp->x2D4_specialAttributes;

    if (stateVar1 != 0) {
        fp->x2340_stateVar1 = stateVar1 - 1;
    } else {
        arg2 = charAttr->xC;
        arg3 = fighterAttr->x170_TerminalVelocity;
        func_8007D494(fp, arg2, arg3);
    }

    func_8007CF58(fp);
    func_8007AEF8(fighter_gobj);
}

// 8013AC10 - 8013AC4C (0x3C bytes)
// https://decomp.me/scratch/CT7dz
void ftZelda_8013AC10(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == 0) {
        ftZelda_8013AC88(fighter_gobj);
    }
}

// 8013AC4C - 8013AC88 (0x3C bytes)
// https://decomp.me/scratch/CT7dz
void ftZelda_8013AC4C(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != 0) {
        ftZelda_8013AD1C(fighter_gobj);
    }
}

void ftZelda_8013AC88(HSD_GObj* fighter_gobj)
{
    ftZeldaAttributes* attributes;
    Fighter* fp;
    Fighter* fighter2;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[12];
#endif

    fp = GET_FIGHTER(fighter_gobj);
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x156, 0x0C4C508E, NULL,
                                       fp->x894_currentAnimFrame, 1.0, 0);

    fighter2 = GET_FIGHTER(fighter_gobj);
    attributes = fighter2->x2D4_specialAttributes;

    if (fighter2->x2200_ftcmd_var0 == 2U) {
        ftColl_CreateReflectHit(fighter_gobj, &attributes->x84,
                                &ftZelda_8013ADB0);
    }
    fp->cb.x21BC_callback_Accessory4 = &ftZelda_8013A8AC;
}

void ftZelda_8013AD1C(HSD_GObj* fighter_gobj)
{
    ftZeldaAttributes* attributes;
    Fighter* fp;
    Fighter* fighter2;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[12];
#endif

    fp = GET_FIGHTER(fighter_gobj);
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x155, 0x0C4C508E, NULL,
                                       fp->x894_currentAnimFrame, 1.0, 0);

    fighter2 = GET_FIGHTER(fighter_gobj);
    attributes = fighter2->x2D4_specialAttributes;

    if (fighter2->x2200_ftcmd_var0 == 2U) {
        ftColl_CreateReflectHit(fighter_gobj, &attributes->x84,
                                &ftZelda_8013ADB0);
    }
    fp->cb.x21BC_callback_Accessory4 = &ftZelda_8013A830;
}

void ftZelda_8013ADB0(HSD_GObj* fighter_gobj)
{
    return;
}
