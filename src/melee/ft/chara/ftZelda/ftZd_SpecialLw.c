#include <platform.h>

#include "ftZd_SpecialLw.h"

#include "math.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftSeak/ftSk_SpecialLw.h"
#include "ftZelda/types.h"
#include "it/items/itzeldadinfire.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <dolphin/mtx.h>

// 8013ADB4 - 8013AE30 (124 bytes)
// https://decomp.me/scratch/LbMVE
void ftZd_SpecialLw_8013ADB4(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    if (!fp->x2219_b0) {
        efSync_Spawn(1276, gobj, fp->parts[104].joint);
        fp->x2219_b0 = true;
    }

    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

// 8013AE30 - 8013AEAC (124 bytes)
// https://decomp.me/scratch/iojLO
void ftZd_SpecialLw_8013AE30(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    if (!fp->x2219_b0) {
        efSync_Spawn(1277, gobj, fp->parts[FtPart_HipN].joint);
        fp->x2219_b0 = true;
    }

    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

// Zelda_TransformToSubcharacter
// 8013AEAC - 8013AEE0 (52 bytes)
// https://decomp.me/scratch/iINH1
void ftZd_SpecialLw_8013AEAC(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    fp->accessory4_cb = 0;

    ftCommon_8007EFC8(gobj, ftSk_SpecialLw_80114758);
}

// Helper function for both ftZd_SpecialLw_Enter /
// ftZd_SpecialAirLw_Enter
static void ftZelda_SpecialLw_StartAction_Helper(HSD_GObj* gobj)
{
    Vec3 sp20;
    Fighter* fp;                  // r31
    ftZelda_DatAttrs* attributes; // r3

    fp = getFighterPlus(gobj);
    attributes = getFtSpecialAttrs(fp);

    fp->cmd_vars[0] = 0;
    fp->self_vel.x = fp->self_vel.x / attributes->x70;
    fp->self_vel.y = fp->self_vel.y / attributes->x74;
    fp->gr_vel = fp->gr_vel / attributes->x70;

    lb_8000B1CC(fp->parts[FtPart_TopN].joint, NULL, &sp20);
    lb_800119DC(&sp20, 120, 0.4, 0.003, 60 * deg_to_rad);

    fp->accessory4_cb = &ftZd_SpecialLw_8013ADB4;
}

// Zelda_AS_355_Transform_Grounded
// 8013AEE0 - 8013AFA4 (196 bytes)
// https://decomp.me/scratch/jZJgg (with helper)
// https://decomp.me/scratch/Lw6fO (single function)
void ftZd_SpecialLw_Enter(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 355, 0, 0, 1, 0, NULL);

    ftAnim_8006EBA4(gobj);

    ftZelda_SpecialLw_StartAction_Helper(gobj);
}

// Zelda_AS_357_Transform_Aerial
// 8013AFA4 - 8013B068 (196 bytes)
// For a scratch using helper function, see the above function.
// https://decomp.me/scratch/8W7ZF (single function)
void ftZd_SpecialAirLw_Enter(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 357, 0, 0, 1.0, 0, NULL);

    ftAnim_8006EBA4(gobj);

    ftZelda_SpecialLw_StartAction_Helper(gobj);
}

// 8013B068 - 8013B0A8 (64 bytes)
// https://decomp.me/scratch/DrRr5
void ftZd_SpecialLw_Anim(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->accessory4_cb = &ftZd_SpecialLw_8013AEAC;
    }
}

// 8013B0A8 - 8013B0E8 (64 bytes)
// https://decomp.me/scratch/DrRr5
void ftZd_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->accessory4_cb = &ftZd_SpecialLw_8013AEAC;
    }
}

void ftZd_SpecialLw_IASA(HSD_GObj* gobj)
{
    return;
}
void ftZd_SpecialAirLw_IASA(HSD_GObj* gobj)
{
    return;
}

// 8013B0F0 - 8013B110 (32 bytes)
void ftZd_SpecialLw_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 8013B110 - 8013B154 (68 bytes)
// https://decomp.me/scratch/Nm958
void ftZd_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp;
    ftZelda_DatAttrs* attributes;

    u8 _[4];

    fp = GET_FIGHTER(gobj);
    attributes = fp->dat_attrs;

    ftCommon_8007D494(fp, attributes->x78, attributes->x7C);
    ftCommon_8007CEF4(fp);
}

// 8013B154 - 8013B190 (60 bytes)
// https://decomp.me/scratch/8ceOO
void ftZd_SpecialLw_Coll(HSD_GObj* gobj)
{
    if (ft_80082708(gobj) == 0) {
        ftZd_SpecialLw_8013B1CC(gobj);
    }
}

// 8013B190 - 8013B1CC (60 bytes)
// https://decomp.me/scratch/8ceOO
void ftZd_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj) != 0) {
        ftZd_SpecialLw_8013B238(gobj);
    }
}

// 8013B1CC - 8013B238 (108 bytes)
// https://decomp.me/scratch/w04qW
void ftZd_SpecialLw_8013B1CC(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 357, 0x0C4C508E, fp->cur_anim_frame, 1.0,
                              0, NULL);
    fp->accessory4_cb = &ftZd_SpecialLw_8013ADB4;
}

// 8013B238 - 8013B2A4 (108 bytes)
void ftZd_SpecialLw_8013B238(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 355, 0x0C4C508E, fp->cur_anim_frame, 1.0,
                              0, NULL);
    fp->accessory4_cb = &ftZd_SpecialLw_8013ADB4;
}

// 8013B2A4 - 8013B2E0 (60 bytes)
void ftZd_SpecialLw2_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

// 8013B2E0 - 8013B31C (60 bytes)
void ftZd_SpecialAirLw2_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftZd_SpecialLw2_IASA(HSD_GObj* gobj)
{
    return;
}
void ftZd_SpecialAirLw2_IASA(HSD_GObj* gobj)
{
    return;
}

// 8013B324 - 8013B344 (32 bytes)
void ftZd_SpecialLw2_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 8013B344 - 8013B388 (68 bytes)
// https://decomp.me/scratch/r3T6y
void ftZd_SpecialAirLw2_Phys(HSD_GObj* gobj)
{
    Fighter* fp;
    ftZelda_DatAttrs* attributes;

    u8 _[4];

    fp = GET_FIGHTER(gobj);
    attributes = fp->dat_attrs;

    ftCommon_8007D494(fp, attributes->x78, attributes->x7C);
    ftCommon_8007CEF4(fp);
}

// 8013B388 - 8013B3C4 (60 bytes)
// https://decomp.me/scratch/t8hrY
void ftZd_SpecialLw2_Coll(HSD_GObj* gobj)
{
    if (ft_80082708(gobj) == 0) {
        ftZd_SpecialLw_8013B400(gobj);
    }
}

// 8013B3C4 - 8013B400 (60 bytes)
// https://decomp.me/scratch/t8hrY
void ftZd_SpecialAirLw2_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj) != 0) {
        ftZd_SpecialLw_8013B46C(gobj);
    }
}

// 8013B400 - 8013B46C (108 bytes)
// https://decomp.me/scratch/EZlpO
void ftZd_SpecialLw_8013B400(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 358, 0x0C4C508E, fp->cur_anim_frame, 1.0,
                              0, NULL);
    fp->accessory4_cb = &ftZd_SpecialLw_8013AE30;
}

// 8013B46C - 8013B4D8 (108 bytes)
// https://decomp.me/scratch/EZlpO
void ftZd_SpecialLw_8013B46C(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 356, 0x0C4C508E, fp->cur_anim_frame, 1.0,
                              0, NULL);
    fp->accessory4_cb = &ftZd_SpecialLw_8013AE30;
}

// AS_ZeldaFinishTransformation
// 8013B4D8 - 8013B540 (104 bytes)
// https://decomp.me/scratch/wpEbJ
void ftZd_SpecialLw_8013B4D8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftZelda_DatAttrs* sa = fp->dat_attrs;

    u8 _[4];

    {
        enum_t msid;
        if (fp->ground_or_air == 0) {
            msid = 356;
        } else {
            msid = 358;
        }

        Fighter_ChangeMotionState(gobj, msid, 0, sa->x80, 1.0, 0, NULL);
    }
    fp->accessory4_cb = &ftZd_SpecialLw_8013AE30;
}

// 8013B540 - 8013B574 (52 bytes)
// https://decomp.me/scratch/L6UUI
s32 ftZd_SpecialLw_8013B540(HSD_GObj* gobj)
{
    s32 actionStateIndex;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    actionStateIndex = fp->motion_id;

    if (((actionStateIndex == 344) || (actionStateIndex == 347)) &&
        (fp->fv.zd.x222C != 0U))
    {
        return 1;
    }
    return 0;
}

// 8013B574 - 8013B5C4 (80 bytes)
// https://decomp.me/scratch/tgIRc (fork of below)
// https://decomp.me/scratch/pTAiQ
bool ftZd_SpecialLw_8013B574(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.zd.x222C != 0) {
        switch (fp->motion_id) {
        case 348:
        case 345:
            if (fp->cmd_vars[1] == 1) {
                fp->cmd_vars[1] = 0;
                return true;
            }
            break;
        }
    }

    return false;
}

// 8013B5C4 - 8013B5EC ( bytes)
// https://decomp.me/scratch/VdBYJ
void ftZd_SpecialLw_8013B5C4(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    if (fp->fv.zd.x222C != 0) {
        fp->fv.zd.x222C = 0;
    }

    fp->death2_cb = 0;
    fp->take_dmg_cb = 0;
}

// 8013B5EC - 8013B638 (76 bytes)
// https://decomp.me/scratch/8QoCa
void ftZd_SpecialLw_8013B5EC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.zd.x222C != NULL) {
        it_802C3D44(fp->fv.zd.x222C);
        fp->fv.zd.x222C = NULL;
    }

    fp->death2_cb = 0;
    fp->take_dmg_cb = 0;
}
