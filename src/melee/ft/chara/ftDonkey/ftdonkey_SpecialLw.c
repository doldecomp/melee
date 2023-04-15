#include "ftdonkey_SpecialLw.h"

#include "ftdonkey.h"

#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/inlines.h"

void ftDk_SpecialLw_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.dk.speciallw.x0 = 0;
    Fighter_ChangeMotionState(gobj, 0x17F, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
}

void ftDk_SpecialLw_8010DCD8(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftDk_SpecialLw_8010DE88(gobj);
    }
}

void ftDk_SpecialLw_8010DD14(HSD_GObj* gobj) {}

void ftDk_SpecialLw_8010DD18(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialLw_8010DD38(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ft_800CC730(gobj);
    }
}

void ftDk_SpecialLw_8010DD74(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->mv.dk.speciallw.x0) {
            fp->mv.dk.speciallw.x0 = 0;
            ftDk_SpecialLw_8010DE88(gobj);
        } else {
            ftDk_SpecialLw_8010DFF8(gobj);
        }
    }
}

void ftDk_SpecialLw_8010DDDC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.x668 & 0x200) {
        fp->mv.dk.speciallw.x0 = 1;
    }
}

void ftDk_SpecialLw_8010DDF8(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialLw_8010DE18(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ft_800CC730(gobj);
    }
}

void ftDk_SpecialLw_8010DE54(HSD_GObj* gobj)
{
    ft_80089824(gobj);
    ft_800892A0(gobj);
}

void ftDonkey_8010DE88_inner(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!fp->x2219_flag.bits.b0) {
        efAsync_Spawn(gobj, &fp->x60C, 1, 0x4CC, fp->ft_bones[0].x0_jobj);
        fp->x2219_flag.bits.b0 = true;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

void ftDk_SpecialLw_8010DE88(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cb.x21EC_callback = &ftDk_SpecialLw_8010DE54;
    fp->x2210_ThrowFlags.flags = 0;
    Fighter_ChangeMotionState(gobj, 0x180, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftDonkey_8010DE88_inner(gobj);
    fp->cb.x21BC_callback_Accessory4 = &ftDk_Init_8010DB3C;
}

void ftDk_SpecialLw_8010DF5C(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftDk_SpecialLw_8010DF98(HSD_GObj* gobj) {}

void ftDk_SpecialLw_8010DF9C(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialLw_8010DFBC(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ft_800CC730(gobj);
    }
}

void ftDk_SpecialLw_8010DFF8(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x181, 0, NULL, 0.0f, 1.0f, 0.0f);
}

void ftDk_SpecialLw_8010E030(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CC730(gobj);
    }
}

void ftDk_SpecialLw_8010E06C(HSD_GObj* gobj) {}

void ftDk_SpecialLw_8010E070(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftDk_SpecialLw_8010E090(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftDk_SpecialLw_8010E0CC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_flag.bits.b0) {
        efSync_Spawn(0x4C6, gobj, fp->ft_bones[1].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
}

void ftDk_SpecialLw_8010E148(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_flag.bits.b0) {
        efSync_Spawn(0x4C7, gobj, fp->ft_bones[1].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
}
