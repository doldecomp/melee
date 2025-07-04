#include <platform.h>

#include "ftSs_SpecialHi.h"

#include "inlines.h"
#include "math.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftSamus/types.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

void ftSs_SpecialHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    Fighter_ChangeMotionState(gobj, 353, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftSamus_updateDamageDeathCBs(gobj);
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    ftCommon_8007D7FC(fp);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->mv.ss.unk5.x0 = 0;
    ftAnim_8006EBA4(gobj);
    efSync_Spawn(1154, gobj, fp->parts[FtPart_YRotN].joint);
    fp->fv.ss.x2244 = 1;
}

void ftSs_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    Fighter_ChangeMotionState(gobj, 354, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftSamus_updateDamageDeathCBs(gobj);
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    ftCommon_8007D60C(fp);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->mv.ss.unk5.x0 = 0;
    fp->self_vel.y = samus_attr->x44;
    ftCommon_8007D440(fp, samus_attr->x40);
    ftAnim_8006EBA4(gobj);
    efSync_Spawn(1154, gobj, fp->parts[FtPart_YRotN].joint);
    fp->fv.ss.x2244 = 1;
}

static void ftSamus_DestroyAllUnsetx2444(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    efLib_DestroyAll(gobj);
    fp->fv.ss.x2244 = 0;
}

void ftSs_SpecialHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr;
    ftSs_DatAttrs* samus_attr2;
    samus_attr = samus_attr2 = fp->dat_attrs;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fighter2 = fp;
        ftSamus_DestroyAllUnsetx2444(gobj);
        ftCommon_8007D60C(fighter2);
        if (samus_attr->x50 == 0.0f) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 1, 0, samus_attr->x48, samus_attr->x50);
    }
}

void ftSs_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr;
    ftSs_DatAttrs* samus_attr2;
    samus_attr = samus_attr2 = fp->dat_attrs;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fighter2 = fp;
        ftSamus_DestroyAllUnsetx2444(gobj);
        ftCommon_8007D60C(fighter2);
        if (samus_attr->x50 == 0.0f) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 1, 0, samus_attr->x48, samus_attr->x50);
    }
}

void ftSs_SpecialHi_IASA(HSD_GObj* gobj)
{
    float mag;
    float lstick_x;
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[4];

    if ((!fp->cmd_vars[1]) && (!fp->mv.ss.unk5.x0)) {
        if ((lstick_x = fp->input.lstick.x) < 0.0f) {
            mag = -lstick_x;
        } else {
            mag = lstick_x;
        }
        if (mag > samus_attr->x4C) {
            if (((fp->facing_dir == 1.0f) && (lstick_x < 0.0f)) ||
                ((fp->facing_dir == -1.0f) && (lstick_x > 0.0f)))
            {
                fp->cmd_vars[1] = 1;
                fp->mv.ss.unk5.x0 = 1;
                ftCommon_8007D9FC(fp);
                ftParts_80075AF0(fp, 0, M_PI_2 * fp->facing_dir);
            }
        }
    }
}

void ftSs_SpecialAirHi_IASA(HSD_GObj* gobj)
{
    float mag;
    float lstick_x;
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    if ((!fp->cmd_vars[1]) && (!fp->mv.ss.unk5.x0)) {
        if ((lstick_x = fp->input.lstick.x) < 0.0f) {
            mag = -lstick_x;
        } else {
            mag = lstick_x;
        }
        if (mag > samus_attr->x4C) {
            if (((fp->facing_dir == 1.0f) && (lstick_x < 0.0f)) ||
                ((fp->facing_dir == -1.0f) && (lstick_x > 0.0f)))
            {
                fp->cmd_vars[1] = 1;
                fp->mv.ss.unk5.x0 = 1;
                ftCommon_8007D9FC(fp);
                ftParts_80075AF0(fp, 0, M_PI_2 * fp->facing_dir);
            }
        }
    }
}

void ftSs_SpecialHi_Phys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftSs_DatAttrs* samus_attr = getFtSpecialAttrs(fp);

    if (fp->cmd_vars[0]) {
        ftCommon_8007D60C(fp);
        fp->cmd_vars[0] = 0;
        fp->self_vel.x = samus_attr->x38 * fp->facing_dir;
    }
    if (fp->ground_or_air == 1) {
        ft_800851C0(gobj);
        ftCommon_8007D344(fp, 0.0f, samus_attr->x3C, samus_attr->x40);
        ftCommon_8007D268(fp);
        return;
    }
    ft_80084F3C(gobj);
}

void ftSs_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    ft_80084DB0(gobj);
    ftCommon_8007D344(fp, 0.0f, samus_attr->x3C, samus_attr->x40);
}

void ftSs_SpecialHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    if (fp->ground_or_air == GA_Air) {
        int direction;

        if (fp->self_vel.y >= 0.0f) {
            ft_80081D0C(gobj);
            return;
        }
        if (fp->facing_dir == 1.0f) {
            direction = 1;
        } else {
            direction = -1;
        }
        if (ft_CheckGroundAndLedge(gobj, direction)) {
            ftSamus_DestroyAllUnsetx2444(gobj);
            ftCo_800D5CB0(gobj, 0, samus_attr->x50);
            return;
        }
        if (ftCliffCommon_80081298(gobj)) {
            ftSamus_DestroyAllUnsetx2444(gobj);
            ftCliffCommon_80081370(gobj);
        }
    } else {
        ft_80084104(gobj);
    }
}

void ftSs_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[4];

    if (fp->ground_or_air == GA_Air) {
        int direction;

        if (fp->self_vel.y >= 0.0f) {
            ft_80081D0C(gobj);
            return;
        }
        if (fp->facing_dir == 1.0f) {
            direction = 1;
        } else {
            direction = -1;
        }
        if (ft_CheckGroundAndLedge(gobj, direction)) {
            ftSamus_DestroyAllUnsetx2444(gobj);
            ftCo_800D5CB0(gobj, 0, samus_attr->x50);
            return;
        }
        if (ftCliffCommon_80081298(gobj)) {
            ftSamus_DestroyAllUnsetx2444(gobj);
            ftCliffCommon_80081370(gobj);
        }
    } else {
        ft_80084104(gobj);
    }
}
