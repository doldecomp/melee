#include "ftLg_SpecialN.h"

#include <platform.h>

#include "ef/efsync.h"

#include "forward.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_Wait.h"

#include "it/forward.h"

#include "it/items/itluigifireball.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx.h>

// SpecialN/SpecialAirN (Fireball)
#define FTLUIGI_SPECIALN_COLL_FLAG Ft_MF_UpdateCmd | Ft_MF_SkipColAnim

// 0x8014267C
// https://decomp.me/scratch/dB9mj // Luigi's grounded Fireball Motion State
// handler
void ftLg_SpecialN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialN, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = &ftLg_SpecialN_FireSpawn;
}

// 0x801426EC - Luigi's aerial Fireball Motion State handler
void ftLg_SpecialAirN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialAirN, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = &ftLg_SpecialN_FireSpawn;
}

// 0x8014275C
// https://decomp.me/scratch/X40ls // Luigi's grounded Fireball Animation
// callback
void ftLg_SpecialN_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

// 0x80142798 - Luigi's aerial Fireball Animation callback
void ftLg_SpecialAirN_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

// 0x801427D4
// https://decomp.me/scratch/JesBp // Luigi's grounded Fireball IASA callback
void ftLg_SpecialN_IASA(HSD_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->cmd_vars[0] != 0U) {
        ftCo_Wait_IASA(gobj);
    }
}

// 0x80142804 - Luigi's aerial Fireball IASA callback
void ftLg_SpecialAirN_IASA(HSD_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->cmd_vars[0] != 0U) {
        ftCo_Fall_IASA_Inner(gobj);
    }
}

// 0x80142834 - Luigi's grounded Fireball Physics callback
void ftLg_SpecialN_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 0x80142854 - Luigi's aerial Fireball Physics callback
void ftLg_SpecialAirN_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

// 0x80142874
// https://decomp.me/scratch/xtPSc // Luigi's grounded Fireball Collision
// callback
void ftLg_SpecialN_Coll(HSD_GObj* gobj)
{
    Fighter* fp;

    if (ft_80082708(gobj) == false) {
        fp = GET_FIGHTER(gobj);
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialAirN,
                                  FTLUIGI_SPECIALN_COLL_FLAG,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        fp->accessory4_cb = &ftLg_SpecialN_FireSpawn;
    }
}

// 0x801428E8 - Luigi's aerial Fireball Collision callback
void ftLg_SpecialAirN_Coll(HSD_GObj* gobj)
{
    Fighter* fp;

    if (ft_80081D0C(gobj) != false) {
        fp = GET_FIGHTER(gobj);
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialN,
                                  FTLUIGI_SPECIALN_COLL_FLAG,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        fp->accessory4_cb = &ftLg_SpecialN_FireSpawn;
    }
}

// 0x8014295C
// https://decomp.me/scratch/6miNL // Luigi's Fireball Spawn callback
void ftLg_SpecialN_FireSpawn(HSD_GObj* gobj)
{
    Vec3 sp10;
    Fighter* fp = GET_FIGHTER(gobj);
    bool flag;

    if (fp->throw_flags_b0 != 0) {
        fp->throw_flags_b0 = 0;
        flag = true;
    } else {
        flag = false;
    }

    if (flag != false) {
        lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_L1stNb)].joint,
                    NULL, &sp10);
        it_802C01AC(gobj, &sp10, It_Kind_Luigi_Fire, fp->facing_dir);
        efSync_Spawn(1287, gobj,
                     fp->parts[ftParts_GetBoneIndex(fp, FtPart_L1stNb)].joint,
                     &fp->facing_dir);
    }
}
