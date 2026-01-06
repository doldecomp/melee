#include "ftDk_SpecialHi.h"

#include "ftDk_Init.h"

#include <platform.h>

#include "ef/eflib.h"
#include "ef/efsync.h"

#include "forward.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftDonkey/types.h"

#include <dolphin/mtx.h>

static void setCallbacks(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = ftDk_Init_8010D774;
    fp->death2_cb = ftDk_Init_8010D774;
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

void ftDk_SpecialHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp);
    Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialHi, 0, 0, 1, 0, NULL);
    setCallbacks(gobj);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    ftCommon_ClampGrVel(
        fp, donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
    fp->self_vel.x = fp->gr_vel;
    fp->self_vel.y = 0;
    fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
    ftAnim_8006EBA4(gobj);
    efSync_Spawn(1226, gobj, fp->parts[FtPart_TopN].joint);
}

void ftDk_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->dat_attrs;
    u8 _[8];
    Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialAirHi, 0, 0, 1, 0, NULL);
    setCallbacks(gobj);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    ftCommon_ClampSelfVelX(
        fp, donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
    fp->self_vel.y = donkey_attr->SpecialHi.x4C_AERIAL_VERTICAL_VELOCITY;
    fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
    ftAnim_8006EBA4(gobj);
    efSync_Spawn(1226, gobj, fp->parts[FtPart_TopN].joint);
}

void ftDk_SpecialHi_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftDk_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->dat_attrs;
    u8 _[8];
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D60C(fp);
        if (donkey_attr->SpecialHi.x64_LANDING_LAG == 0) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1,
                          donkey_attr->SpecialHi.x64_LANDING_LAG);
        }
    }
}

void ftDk_SpecialHi_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialAirHi_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialHi_Phys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp);
    ftCommon_8007CADC(fp, 0, donkey_attr->SpecialHi.x5C_GROUNDED_MOBILITY,
                      donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
    ftCommon_ApplyGroundMovement(gobj);
}

void ftDk_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->dat_attrs;
    float grav_mul;
    if (fp->cmd_vars[0]) {
        grav_mul = 1;
    } else {
        grav_mul = donkey_attr->SpecialHi.x50_AERIAL_GRAVITY;
    }
    ftCommon_Fall(fp, grav_mul * fp->co_attrs.grav, fp->co_attrs.terminal_vel);
    ftCommon_8007D344(fp, 0, donkey_attr->SpecialHi.x60_AERIAL_MOBILITY,
                      donkey_attr->SpecialHi.x58_AERIAL_HORIZONTAL_VELOCITY);
}

void ftDk_SpecialHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->dat_attrs;

    if (!ft_80082708(gobj)) {
        ftCommon_8007D60C(fp);
        Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialAirHi, 0x0C4C5080,
                                  fp->cur_anim_frame, 1, 0, NULL);
        setCallbacks(gobj);
        ftCommon_ClampSelfVelX(
            fp, donkey_attr->SpecialHi.x58_AERIAL_HORIZONTAL_VELOCITY);
    }
}

void ftDk_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->dat_attrs;
    u8 _[8];
    if (fp->self_vel.y >= 0) {
        if (ft_80081D0C(gobj)) {
            ftCommon_8007D7FC(fp);
            Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialHi, 0x0C4C5080,
                                      fp->cur_anim_frame, 1, 0, NULL);
            setCallbacks(gobj);
            ftCommon_ClampGrVel(
                fp, donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
        }
    } else {
        if (ft_CheckGroundAndLedge(gobj, 0)) {
            ftCommon_8007D7FC(fp);
            Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialHi, 0x0C4C5080,
                                      fp->cur_anim_frame, 1, 0, NULL);
            setCallbacks(gobj);
            ftCommon_ClampGrVel(
                fp, donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
        } else if (ftCliffCommon_80081298(gobj)) {
            ftCliffCommon_80081370(gobj);
        }
    }
}

void ftDk_SpecialHi_DestroyAllEffects(HSD_GObj* gobj)
{
    efLib_DestroyAll(gobj);
}
