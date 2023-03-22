#include "ftZelda_SpecialN.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"

void ftZelda_8013A830(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_flag.bits.b0) {
        efSync_Spawn(0x4F4, gobj, fp->ft_bones[1].x0_jobj);
        fp->x2219_flag.bits.b0 = true;
    }

    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
}

void ftZelda_8013A8AC(HSD_GObj* gobj)
{
    Fighter* fp; // r31

    fp = GET_FIGHTER(gobj);
    if (fp->x2219_flag.bits.b0 == 0) {
        efSync_Spawn(0x4F5, gobj, fp->ft_bones[1].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
}

inline void startActionHelper(HSD_GObj* gobj)
{
    ftZelda_DatAttrs* attributes;
    Fighter* fighter2; // r5
    fighter2 = GET_FIGHTER(gobj);
    attributes = fighter2->x2D4_specialAttributes;
    fighter2->x2200_ftcmd_var0 = 0;
    fighter2->mv.zd.specialn.x0 = attributes->x4;
}

void ftZelda_SpecialN_StartMotion(HSD_GObj* gobj)
{
    f32 temp_f1;
    Fighter* fp; // r31

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[11];
#endif

    temp_f1 = 0;
    fp = GET_FIGHTER(gobj);

    Fighter_ChangeMotionState(gobj, 0x155, 0, NULL, temp_f1, 1.0, temp_f1);
    ftAnim_8006EBA4(gobj);
    startActionHelper(gobj);
    fp->cb.x21BC_callback_Accessory4 = &ftZelda_8013A830;
}

void ftZelda_SpecialAirN_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftZelda_DatAttrs* sa = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    fp->x80_self_vel.y = 0;
    fp->x80_self_vel.x = fp->x80_self_vel.x / sa->x8;

    Fighter_ChangeMotionState(gobj, 0x156, 0, NULL, 0, 1.0, 0);
    ftAnim_8006EBA4(gobj);

    startActionHelper(gobj);
    fp->cb.x21BC_callback_Accessory4 = &ftZelda_8013A8AC;
}

void ftZelda_8013AA38(HSD_GObj* gobj)
{
    Fighter* fp;
    ftZelda_DatAttrs* attributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12];
#endif

    fp = GET_FIGHTER(gobj);
    attributes = fp->x2D4_specialAttributes;

    if (fp->x2200_ftcmd_var0 == 1) {
        fp->x2200_ftcmd_var0 = 2;
        ftColl_CreateReflectHit(gobj, &attributes->x84, &ftZelda_8013ADB0);
    }

    if (fp->x2200_ftcmd_var0 == 0) {
        fp->x2218_flag.bits.b3 = 0;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

// 8013AACC - 8013AB60 (0x94 bytes)
// https://decomp.me/scratch/ttWvN
void ftZelda_8013AACC(HSD_GObj* gobj)
{
    Fighter* fp;
    ftZelda_DatAttrs* attributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12];
#endif

    fp = GET_FIGHTER(gobj);
    attributes = fp->x2D4_specialAttributes;

    if (fp->x2200_ftcmd_var0 == 1U) {
        fp->x2200_ftcmd_var0 = 2U;
        ftColl_CreateReflectHit(gobj, &attributes->x84, &ftZelda_8013ADB0);
    }

    if (fp->x2200_ftcmd_var0 == 0U) {
        fp->x2218_flag.bits.b3 = 0;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CC730(gobj);
    }
}

void ftZelda_8013AB60(HSD_GObj* gobj)
{
    return;
}
void ftZelda_8013AB64(HSD_GObj* gobj)
{
    return;
}

// 8013AB68 - 8013AB9C (0x34 bytes)
void ftZelda_8013AB68(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEF8(gobj);
}

// 8013AB9C - 8013AC10 (0x74 bytes)
// https://decomp.me/scratch/juoPH
void ftZelda_8013AB9C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    {
        s32 var1 = fp->mv.zd.specialn.x0;
        attr* attr = &fp->x110_attr;
        ftZelda_DatAttrs* sa = fp->x2D4_specialAttributes;

        if (var1 != 0) {
            fp->mv.zd.specialn.x0 = var1 - 1;
        } else {
            ftCommon_8007D494(fp, sa->xC, attr->x170_TerminalVelocity);
        }
    }

    ftCommon_8007CF58(fp);
    ftColl_8007AEF8(gobj);
}

// 8013AC10 - 8013AC4C (0x3C bytes)
// https://decomp.me/scratch/CT7dz
void ftZelda_8013AC10(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftZelda_8013AC88(gobj);
    }
}

// 8013AC4C - 8013AC88 (0x3C bytes)
// https://decomp.me/scratch/CT7dz
void ftZelda_8013AC4C(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj) != 0) {
        ftZelda_8013AD1C(gobj);
    }
}

void ftZelda_8013AC88(HSD_GObj* gobj)
{
    ftZelda_DatAttrs* attributes;
    Fighter* fp;
    Fighter* fighter2;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12];
#endif

    fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x156, 0x0C4C508E, NULL,
                              fp->x894_currentAnimFrame, 1.0, 0);

    fighter2 = GET_FIGHTER(gobj);
    attributes = fighter2->x2D4_specialAttributes;

    if (fighter2->x2200_ftcmd_var0 == 2U) {
        ftColl_CreateReflectHit(gobj, &attributes->x84, &ftZelda_8013ADB0);
    }
    fp->cb.x21BC_callback_Accessory4 = &ftZelda_8013A8AC;
}

void ftZelda_8013AD1C(HSD_GObj* gobj)
{
    ftZelda_DatAttrs* attributes;
    Fighter* fp;
    Fighter* fighter2;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12];
#endif

    fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x155, 0x0C4C508E, NULL,
                              fp->x894_currentAnimFrame, 1.0, 0);

    fighter2 = GET_FIGHTER(gobj);
    attributes = fighter2->x2D4_specialAttributes;

    if (fighter2->x2200_ftcmd_var0 == 2U) {
        ftColl_CreateReflectHit(gobj, &attributes->x84, &ftZelda_8013ADB0);
    }
    fp->cb.x21BC_callback_Accessory4 = &ftZelda_8013A830;
}

void ftZelda_8013ADB0(HSD_GObj* gobj)
{
    return;
}
