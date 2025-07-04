#include <platform.h>

#include "forward.h"

#include "ftDonkey/ftDk_SpecialS.h"

#include "ftDk_SpecialLw.h"

#include "ef/eflib.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftDonkey/types.h"

#include <dolphin/mtx.h>

void ftDk_SpecialS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[8];
    Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialS, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    Fighter_UnsetCmdVar0(gobj);
    fp->accessory4_cb = ftDk_SpecialLw_8010E0CC;
}

void ftDk_SpecialAirS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->dat_attrs;
    fp->self_vel.x /= donkey_attr->SpecialS.x3C_MIN_STICK_X_MOMENTUM;
    fp->self_vel.y = 0;
    Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialAirS, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    Fighter_UnsetCmdVar0(gobj);
    fp->accessory4_cb = &ftDk_SpecialLw_8010E148;
}

void ftDk_SpecialS_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftDk_SpecialAirS_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800CC730(gobj);
    }
}

void ftDk_SpecialS_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialAirS_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialS_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialAirS_Phys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftCo_DatAttrs* ca = &fp->co_attrs;
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp);
    if (fp->cmd_vars[0]) {
        ftCommon_8007D494(fp, donkey_attr->SpecialS.x44_AERIAL_GRAVITY,
                          ca->terminal_vel);
    }
    ftCommon_8007CE94(fp,
                      donkey_attr->SpecialS.x40_MOMENTUM_TRANSITION_MODIFIER);
    if (fp->cmd_vars[0] != 0) {
        /// @todo Fix control flow.
    }
}

static void doAirTransition(HSD_GObj* gobj);

void ftDk_SpecialS_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0]) {
        if (!ft_800827A0(gobj)) {
            doAirTransition(gobj);
        }
    } else if (!ft_80082708(gobj)) {
        doAirTransition(gobj);
    }
}

static void doGroundTransition(HSD_GObj* gobj);

void ftDk_SpecialAirS_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        doGroundTransition(gobj);
    }
}

void doAirTransition(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialAirS, 0x0C4C508A,
                              fp->cur_anim_frame, 1, 0, NULL);
    if (fp->x2219_b0 == true) {
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
    }
}

static void doGroundTransition(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialS, 0x0C4C508A,
                              fp->cur_anim_frame, 1, 0, NULL);
    if (fp->x2219_b0 == true) {
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
    }
}
