#include "forward.h"

#include "ef/efsync.h"
#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftparts.h"
#include "ftLuigi/ftluigi.h"
#include "it/code_8027CF30.h"
#include "lb/lbunknown_001.h"

#include <dolphin/mtx/types.h>

// 0x8014267C
// https://decomp.me/scratch/dB9mj // Luigi's grounded Fireball Motion State
// handler
void ftLuigi_SpecialN_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    Fighter_ChangeMotionState(gobj, MS_LUIGI_SPECIALN, 0, NULL, 0.0f, 1.0f,
                              0.0f);
    func_8006EBA4(gobj);
    fp->cb.x21BC_callback_Accessory4 = &ftLuigi_SpecialN_FireSpawn;
}

// 0x801426EC - Luigi's aerial Fireball Motion State handler
void ftLuigi_SpecialAirN_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    Fighter_ChangeMotionState(gobj, MS_LUIGI_SPECIALAIRN, 0, NULL, 0.0f, 1.0f,
                              0.0f);
    func_8006EBA4(gobj);
    fp->cb.x21BC_callback_Accessory4 = &ftLuigi_SpecialN_FireSpawn;
}

// 0x8014275C
// https://decomp.me/scratch/X40ls // Luigi's grounded Fireball Animation
// callback
void ftLuigi_SpecialN_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

// 0x80142798 - Luigi's aerial Fireball Animation callback
void ftLuigi_SpecialAirN_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        func_800CC730(gobj);
}

// 0x801427D4
// https://decomp.me/scratch/JesBp // Luigi's grounded Fireball IASA callback
void ftLuigi_SpecialN_IASA(HSD_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->x2200_ftcmd_var0 != 0U)
        func_8008A4D4(gobj);
}

// 0x80142804 - Luigi's aerial Fireball IASA callback
void ftLuigi_SpecialAirN_IASA(HSD_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->x2200_ftcmd_var0 != 0U)
        func_800CCAAC(gobj);
}

// 0x80142834 - Luigi's grounded Fireball Physics callback
void ftLuigi_SpecialN_Phys(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

// 0x80142854 - Luigi's aerial Fireball Physics callback
void ftLuigi_SpecialAirN_Phys(HSD_GObj* gobj)
{
    func_80084DB0(gobj);
}

// 0x80142874
// https://decomp.me/scratch/xtPSc // Luigi's grounded Fireball Collision
// callback
void ftLuigi_SpecialN_Coll(HSD_GObj* gobj)
{
    Fighter* fp;

    if (func_80082708(gobj) == false) {
        fp = GET_FIGHTER(gobj);
        func_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, MS_LUIGI_SPECIALAIRN,
                                  FTLUIGI_SPECIALN_COLL_FLAG, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        fp->cb.x21BC_callback_Accessory4 = &ftLuigi_SpecialN_FireSpawn;
    }
}

// 0x801428E8 - Luigi's aerial Fireball Collision callback
void ftLuigi_SpecialAirN_Coll(HSD_GObj* gobj)
{
    Fighter* fp;

    if (func_80081D0C(gobj) != false) {
        fp = GET_FIGHTER(gobj);
        func_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, MS_LUIGI_SPECIALN,
                                  FTLUIGI_SPECIALN_COLL_FLAG, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        fp->cb.x21BC_callback_Accessory4 = &ftLuigi_SpecialN_FireSpawn;
    }
}

// 0x8014295C
// https://decomp.me/scratch/6miNL // Luigi's Fireball Spawn callback
void ftLuigi_SpecialN_FireSpawn(HSD_GObj* gobj)
{
    Vec3 sp10;
    Fighter* fp = GET_FIGHTER(gobj);
    bool flag;

    if (fp->x2210_ThrowFlags.b0 != 0) {
        fp->x2210_ThrowFlags.b0 = 0;
        flag = true;
    } else
        flag = false;

    if (flag != false) {
        func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 0x17)].x0_jobj,
                      NULL, &sp10);
        func_802C01AC(gobj, &sp10, It_Kind_Luigi_Fire, fp->facing_dir);
        ef_Spawn(0x507, gobj,
                 fp->x5E8_fighterBones[func_8007500C(fp, 0x17)].x0_jobj,
                 &fp->facing_dir);
    }
}
