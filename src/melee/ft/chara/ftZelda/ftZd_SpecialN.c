#include "ftZd_SpecialN.h"

#include <platform.h>

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftZelda/types.h"

#include <dolphin/mtx.h>

void ftZd_SpecialN_8013A830(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_b0) {
        efSync_Spawn(1268, gobj, fp->parts[FtPart_TransN].joint);
        fp->x2219_b0 = true;
    }

    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

void ftZd_SpecialN_8013A8AC(HSD_GObj* gobj)
{
    Fighter* fp; // r31

    fp = GET_FIGHTER(gobj);
    if (!fp->x2219_b0) {
        efSync_Spawn(1269, gobj, fp->parts[FtPart_TransN].joint);
        fp->x2219_b0 = true;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

inline void startActionHelper(HSD_GObj* gobj)
{
    ftZelda_DatAttrs* attributes;
    Fighter* fighter2; // r5
    fighter2 = GET_FIGHTER(gobj);
    attributes = fighter2->dat_attrs;
    fighter2->cmd_vars[0] = 0;
    fighter2->mv.zd.specialn.x0 = attributes->x4;
}

void ftZd_SpecialN_Enter(HSD_GObj* gobj)
{
    float temp_f1;
    Fighter* fp; // r31

    u8 _[11];

    temp_f1 = 0;
    fp = GET_FIGHTER(gobj);

    Fighter_ChangeMotionState(gobj, 341, 0, temp_f1, 1.0, temp_f1, NULL);
    ftAnim_8006EBA4(gobj);
    startActionHelper(gobj);
    fp->accessory4_cb = &ftZd_SpecialN_8013A830;
}

void ftZd_SpecialAirN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftZelda_DatAttrs* sa = fp->dat_attrs;

    u8 _[20];

    fp->self_vel.y = 0;
    fp->self_vel.x = fp->self_vel.x / sa->x8;

    Fighter_ChangeMotionState(gobj, 342, 0, 0, 1.0, 0, NULL);
    ftAnim_8006EBA4(gobj);

    startActionHelper(gobj);
    fp->accessory4_cb = &ftZd_SpecialN_8013A8AC;
}

void ftZd_SpecialN_Anim(HSD_GObj* gobj)
{
    Fighter* fp;
    ftZelda_DatAttrs* attributes;

    u8 _[12];

    fp = GET_FIGHTER(gobj);
    attributes = fp->dat_attrs;

    if (fp->cmd_vars[0] == 1) {
        fp->cmd_vars[0] = 2;
        ftColl_CreateReflectHit(gobj, &attributes->x84,
                                &ftZd_SpecialN_8013ADB0);
    }

    if (fp->cmd_vars[0] == 0) {
        fp->reflecting = false;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

/// 8013AACC - 8013AB60 (148 bytes)
/// https://decomp.me/scratch/ttWvN
void ftZd_SpecialAirN_Anim(HSD_GObj* gobj)
{
    Fighter* fp;
    ftZelda_DatAttrs* attributes;

    u8 _[12];

    fp = GET_FIGHTER(gobj);
    attributes = fp->dat_attrs;

    if (fp->cmd_vars[0] == 1U) {
        fp->cmd_vars[0] = 2U;
        ftColl_CreateReflectHit(gobj, &attributes->x84,
                                &ftZd_SpecialN_8013ADB0);
    }

    if (fp->cmd_vars[0] == 0) {
        fp->reflecting = false;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftZd_SpecialN_IASA(HSD_GObj* gobj)
{
    return;
}
void ftZd_SpecialAirN_IASA(HSD_GObj* gobj)
{
    return;
}

/// 8013AB68 - 8013AB9C (52 bytes)
void ftZd_SpecialN_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEF8(gobj);
}

/// 8013AB9C - 8013AC10 (116 bytes)
/// https://decomp.me/scratch/juoPH
void ftZd_SpecialAirN_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    {
        s32 var1 = fp->mv.zd.specialn.x0;
        ftCo_DatAttrs* da = &fp->co_attrs;
        ftZelda_DatAttrs* sa = fp->dat_attrs;

        if (var1 != 0) {
            fp->mv.zd.specialn.x0 = var1 - 1;
        } else {
            ftCommon_Fall(fp, sa->xC, da->terminal_vel);
        }
    }

    ftCommon_8007CF58(fp);
    ftColl_8007AEF8(gobj);
}

/// 8013AC10 - 8013AC4C (60 bytes)
/// https://decomp.me/scratch/CT7dz
void ftZd_SpecialN_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftZd_SpecialN_8013AC88(gobj);
    }
}

/// 8013AC4C - 8013AC88 (60 bytes)
/// https://decomp.me/scratch/CT7dz
void ftZd_SpecialAirN_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj) != 0) {
        ftZd_SpecialN_8013AD1C(gobj);
    }
}

void ftZd_SpecialN_8013AC88(HSD_GObj* gobj)
{
    ftZelda_DatAttrs* attributes;
    Fighter* fp;
    Fighter* fighter2;

    u8 _[12];

    fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 342, 0x0C4C508E, fp->cur_anim_frame, 1.0,
                              0, NULL);

    fighter2 = GET_FIGHTER(gobj);
    attributes = fighter2->dat_attrs;

    if (fighter2->cmd_vars[0] == 2U) {
        ftColl_CreateReflectHit(gobj, &attributes->x84,
                                &ftZd_SpecialN_8013ADB0);
    }
    fp->accessory4_cb = &ftZd_SpecialN_8013A8AC;
}

void ftZd_SpecialN_8013AD1C(HSD_GObj* gobj)
{
    ftZelda_DatAttrs* attributes;
    Fighter* fp;
    Fighter* fighter2;

    u8 _[12];

    fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 341, 0x0C4C508E, fp->cur_anim_frame, 1.0,
                              0, NULL);

    fighter2 = GET_FIGHTER(gobj);
    attributes = fighter2->dat_attrs;

    if (fighter2->cmd_vars[0] == 2U) {
        ftColl_CreateReflectHit(gobj, &attributes->x84,
                                &ftZd_SpecialN_8013ADB0);
    }
    fp->accessory4_cb = &ftZd_SpecialN_8013A830;
}

void ftZd_SpecialN_8013ADB0(HSD_GObj* gobj)
{
    return;
}
