#include "ftDk_SpecialLw.h"

#include "ftdonkey.h"

#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"

void ftDk_SpecialLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->sv.dk.speciallw.x0 = 0;
    Fighter_ChangeMotionState(gobj, 0x17F, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
}

void ftDk_SpecialLwStart_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftDk_SpecialLw_8010DE88(gobj);
    }
}

void ftDk_SpecialLwStart_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialLwStart_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialLwStart_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ft_800CC730(gobj);
    }
}

void ftDk_SpecialLwLoop_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->sv.dk.speciallw.x0) {
            fp->sv.dk.speciallw.x0 = 0;
            ftDk_SpecialLw_8010DE88(gobj);
        } else {
            ftDk_SpecialLw_8010DFF8(gobj);
        }
    }
}

void ftDk_SpecialLwLoop_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.x668 & 0x200) {
        fp->sv.dk.speciallw.x0 = 1;
    }
}

void ftDk_SpecialLwLoop_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialLwLoop_Coll(HSD_GObj* gobj)
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
        efAsync_Spawn(gobj, &fp->x60C, 1, 0x4CC,
                      fp->x5E8_fighterBones[0].x0_jobj);
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

void ftDk_SpecialLwEnd_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftDk_SpecialLwEnd_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialLwEnd_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialLwEnd_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ft_800CC730(gobj);
    }
}

void ftDk_SpecialLw_8010DFF8(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x181, 0, NULL, 0.0f, 1.0f, 0.0f);
}

void ftDk_MS_386_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CC730(gobj);
    }
}

void ftDk_MS_386_IASA(HSD_GObj* gobj) {}

void ftDk_MS_386_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftDk_MS_386_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftDk_SpecialLw_8010E0CC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_flag.bits.b0) {
        efSync_Spawn(0x4C6, gobj, fp->x5E8_fighterBones[1].x0_jobj);
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
        efSync_Spawn(0x4C7, gobj, fp->x5E8_fighterBones[1].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
}
