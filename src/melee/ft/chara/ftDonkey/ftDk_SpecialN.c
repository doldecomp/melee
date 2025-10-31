#include "ftDk_SpecialN.h"

#include "ftDk_Init.h"

#include <platform.h>

#include "ef/eflib.h"
#include "ef/efsync.h"

#include "forward.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Escape.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftDonkey/types.h"

#include "lb/forward.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

static void setCallbacks(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = ftDk_Init_8010D774;
    fp->death2_cb = ftDk_Init_8010D774;
    fp->take_dmg_2_cb = ftDk_SpecialN_DestroyAllEffects;
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

static void updateVelocity(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp);
    fp->gr_vel =
        fp->facing_dir * (donkey_attr->SpecialN.x34_PUNCH_HORIZONTAL_VEL *
                          fp->mv.dk.specialn.xC);
}

void ftDk_SpecialN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->dat_attrs;
    u8 _[8];
    if (fp->fv.dk.x222C == donkey_attr->SpecialN.x2C_MAX_ARM_SWINGS) {
        Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialNFull, 0, 0, 1, 0,
                                  NULL);
        fp->mv.dk.specialn.x8 = 1;
        fp->mv.dk.specialn.xC = fp->fv.dk.x222C;
        fp->fv.dk.x222C = 0;
    } else {
        Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialNStart, 0, 0, 1, 0,
                                  NULL);
        fp->mv.dk.specialn.x8 = 0;
        fp->mv.dk.specialn.xC = 0;
    }
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    fp->mv.dk.specialn.x0 = 0;
    fp->mv.dk.specialn.x4 = 0;
    fp->mv.dk.specialn.x14 = -1;
    fp->mv.dk.specialn.x10 = -1;
    ftCommon_8007D7FC(fp);
    fp->self_vel.y = 0;
    setCallbacks(gobj);
    ftAnim_8006EBA4(gobj);
}

void ftDk_SpecialAirN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->dat_attrs;
    u8 _[8];
    if (fp->fv.dk.x222C == donkey_attr->SpecialN.x2C_MAX_ARM_SWINGS) {
        Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialAirNFull, 0, 0, 1, 0,
                                  NULL);
        fp->mv.dk.specialn.x8 = 1;
        fp->mv.dk.specialn.xC = fp->fv.dk.x222C;
        fp->fv.dk.x222C = 0;
    } else {
        Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialAirNStart, 0, 0, 1, 0,
                                  NULL);
        fp->mv.dk.specialn.x8 = 0;
        fp->mv.dk.specialn.xC = 0;
    }
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    fp->mv.dk.specialn.x0 = 0;
    fp->mv.dk.specialn.x4 = 0;
    fp->mv.dk.specialn.x14 = -1;
    fp->mv.dk.specialn.x10 = -1;
    setCallbacks(gobj);
    ftAnim_8006EBA4(gobj);
}

void ftDk_SpecialNStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialNLoop, 0, 0, 1, 0,
                                  NULL);
        setCallbacks(gobj);
    }
}

static void clearCallbacks(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_2_cb = NULL;
    fp->pre_hitlag_cb = NULL;
    fp->post_hitlag_cb = NULL;
}

void ftDk_SpecialNLoop_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->dat_attrs;
    if (fp->cur_anim_frame == 0) {
        fp->fv.dk.x222C += 1;
        if (fp->fv.dk.x222C >= donkey_attr->SpecialN.x2C_MAX_ARM_SWINGS) {
            Fighter* fighter2 = fp;
            ftCo_800BFFD0(fighter2, 57, 0);
            fighter2->fv.dk.x222C = donkey_attr->SpecialN.x2C_MAX_ARM_SWINGS;
            clearCallbacks(gobj);
            ft_8008A2BC(gobj);
        }
    }
}

void ftDk_SpecialNCancel_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        clearCallbacks(gobj);
        ft_8008A2BC(gobj);
    }
}

void ftDk_SpecialN_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->dat_attrs;
    if (fp->cmd_vars[0]) {
        if (fp->mv.dk.specialn.x8 == 0) {
            fp->mv.dk.specialn.x8++;
        }
    }
    if (fp->mv.dk.specialn.x8 == 1) {
        fp->mv.dk.specialn.x8++;
        if (fp->ground_or_air == GA_Air) {
            efSync_Spawn(1225, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        } else {
            efSync_Spawn(1224, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        }
    }
    if (fp->x914[0].state != HitCapsule_Disabled) {
        if (fp->mv.dk.specialn.x4 == 0) {
            fp->mv.dk.specialn.x4 = 1;
        }
        if (fp->mv.dk.specialn.x10 == -1) {
            fp->mv.dk.specialn.x10 = fp->x914[0].damage;
        }
        ftColl_8007ABD0(&fp->x914[0],
                        fp->mv.dk.specialn.x10 +
                            (fp->mv.dk.specialn.xC *
                             donkey_attr->SpecialN.x30_DAMAGE_PER_SWING),
                        gobj);
        if (fp->mv.dk.specialn.x14 == -1) {
            fp->mv.dk.specialn.x14 = fp->x914[1].damage;
        }
        ftColl_8007ABD0(&fp->x914[1],
                        fp->mv.dk.specialn.x14 +
                            (fp->mv.dk.specialn.xC *
                             donkey_attr->SpecialN.x30_DAMAGE_PER_SWING),
                        gobj);
    }
    if (fp->mv.dk.specialn.x4 == 1) {
        fp->mv.dk.specialn.x4 = 2;
        updateVelocity(gobj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.dk.x222C = 0;
        clearCallbacks(gobj);
        ft_8008A2BC(gobj);
    }
}

void ftDk_SpecialNFull_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[8];
    if (fp->cmd_vars[0]) {
        if (fp->mv.dk.specialn.x8 == 0) {
            fp->mv.dk.specialn.x8++;
        }
    }
    if (fp->mv.dk.specialn.x8 == 1) {
        fp->mv.dk.specialn.x8++;
        if (fp->ground_or_air == GA_Air) {
            efSync_Spawn(1225, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        } else {
            efSync_Spawn(1224, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        }
    }
    if (fp->x914[0].state != HitCapsule_Disabled &&
        (fp->mv.dk.specialn.x4 == 0))
    {
        fp->mv.dk.specialn.x4 = 1;
    }
    if (fp->mv.dk.specialn.x4 == 1) {
        fp->mv.dk.specialn.x4 = 2;
        updateVelocity(gobj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.dk.x222C = 0;
        clearCallbacks(gobj);
        ft_8008A2BC(gobj);
    }
}

void ftDk_SpecialAirNStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialAirNLoop, 0, 0, 1, 0,
                                  NULL);
        setCallbacks(gobj);
    }
}

void ftDk_SpecialAirNLoop_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->dat_attrs;
    if (fp->cur_anim_frame == 0) {
        fp->fv.dk.x222C += 1;
        if (fp->fv.dk.x222C >= donkey_attr->SpecialN.x2C_MAX_ARM_SWINGS) {
            Fighter* fighter2 = fp;
            ftCo_800BFFD0(fighter2, 57, 0);
            fp->fv.dk.x222C = donkey_attr->SpecialN.x2C_MAX_ARM_SWINGS;
            clearCallbacks(gobj);
            ftCo_Fall_Enter(gobj);
        }
    }
}

void ftDk_SpecialAirNCancel_Anim(HSD_GObj* gobj)
{
    u8 _[16];
    if (!ftAnim_IsFramesRemaining(gobj)) {
        clearCallbacks(gobj);
        ftCo_Fall_Enter(gobj);
    }
}

void ftDk_SpecialAirN_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->dat_attrs;
    u8 _[8];
    if (fp->cmd_vars[0]) {
        if (fp->mv.dk.specialn.x8 == 0) {
            fp->mv.dk.specialn.x8++;
        }
    }
    if (fp->mv.dk.specialn.x8 == 1) {
        fp->mv.dk.specialn.x8++;
        if (fp->ground_or_air == GA_Air) {
            efSync_Spawn(1225, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        } else {
            efSync_Spawn(1224, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        }
    }
    if (fp->x914[0].state != HitCapsule_Disabled) {
        if (fp->mv.dk.specialn.x10 == -1) {
            fp->mv.dk.specialn.x10 = fp->x914[0].damage;
        }
        ftColl_8007ABD0(&fp->x914[0],
                        fp->mv.dk.specialn.x10 +
                            (fp->mv.dk.specialn.xC *
                             donkey_attr->SpecialN.x30_DAMAGE_PER_SWING),
                        gobj);
        if (fp->mv.dk.specialn.x14 == -1) {
            fp->mv.dk.specialn.x14 = fp->x914[1].damage;
        }
        ftColl_8007ABD0(&fp->x914[1],
                        fp->mv.dk.specialn.x14 +
                            (fp->mv.dk.specialn.xC *
                             donkey_attr->SpecialN.x30_DAMAGE_PER_SWING),
                        gobj);
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.dk.x222C = 0;
        clearCallbacks(gobj);
        if (donkey_attr->SpecialN.x38_LANDING_LAG == 0) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1,
                          donkey_attr->SpecialN.x38_LANDING_LAG);
        }
    }
}

void ftDk_SpecialAirNFull_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->dat_attrs;
    u8 _[8];
    if (fp->cmd_vars[0]) {
        if (fp->mv.dk.specialn.x8 == 0) {
            fp->mv.dk.specialn.x8++;
        }
    }
    if (fp->mv.dk.specialn.x8 == 1) {
        fp->mv.dk.specialn.x8++;
        if (fp->ground_or_air == GA_Air) {
            efSync_Spawn(1225, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        } else {
            efSync_Spawn(1224, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.dk.x222C = 0;
        clearCallbacks(gobj);
        if (donkey_attr->SpecialN.x38_LANDING_LAG == 0) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1,
                          donkey_attr->SpecialN.x38_LANDING_LAG);
        }
    }
}

void ftDk_SpecialNStart_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialNLoop_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[8];
    if (!ftCo_8009917C(gobj)) {
        if ((fp->input.x668 & HSD_PAD_B)) {
            Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialN, 0, 0, 1, 0,
                                      NULL);
            fp->mv.dk.specialn.xC = fp->fv.dk.x222C;
            fp->fv.dk.x222C = 0;
            setCallbacks(gobj);
            ftAnim_8006EBA4(gobj);
        }
        if (fp->input.x668 & HSD_PAD_LR) {
            fp->mv.dk.specialn.x0 = 1;
        }
        if (fp->cur_anim_frame == 0 && fp->mv.dk.specialn.x0) {
            Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialNCancel, 0, 0, 1, 0,
                                      NULL);
            setCallbacks(gobj);
        }
    }
}

void ftDk_SpecialNCancel_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialN_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialNFull_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialAirNStart_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialAirNLoop_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[4];
    if (fp->input.x668 & HSD_PAD_B) {
        Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialAirN, 0, 0, 1, 0, NULL);
        fp->mv.dk.specialn.xC = fp->fv.dk.x222C;
        fp->fv.dk.x222C = 0;
        setCallbacks(gobj);
        ftAnim_8006EBA4(gobj);
    }
    if (fp->input.x668 & HSD_PAD_LR) {
        fp->mv.dk.specialn.x0 = 1;
    }
    if (fp->cur_anim_frame == 0 && fp->mv.dk.specialn.x0) {
        Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialAirNCancel, 0, 0, 1, 0,
                                  NULL);
        setCallbacks(gobj);
    }
}

void ftDk_SpecialAirNCancel_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialAirN_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialAirNFull_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialNStart_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialNLoop_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialNCancel_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialN_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialNFull_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialAirNStart_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftDk_SpecialAirNLoop_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftDk_SpecialAirNCancel_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftDk_SpecialAirN_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftDk_SpecialAirNFull_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftDk_SpecialNStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialAirNStart, 0x0C4C5080,
                                  fp->cur_anim_frame, 1, 0, NULL);
        setCallbacks(gobj);
    }
}

void ftDk_SpecialNLoop_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialAirNLoop, 0x0C4C5080,
                                  fp->cur_anim_frame, 1, 0, NULL);
        setCallbacks(gobj);
    }
}

void ftDk_SpecialNCancel_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialAirNCancel, 0x0C4C5080,
                                  fp->cur_anim_frame, 1, 0, NULL);
        setCallbacks(gobj);
    }
}

void ftDk_SpecialN_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_800827A0(gobj) == 0) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialAirN, 0x0C4D508E,
                                  fp->cur_anim_frame, 1, 0, NULL);
        setCallbacks(gobj);
    }
}

void ftDk_SpecialNFull_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_800827A0(gobj) == 0) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialAirNFull, 0x0C4D508E,
                                  fp->cur_anim_frame, 1, 0, NULL);
        setCallbacks(gobj);
    }
}

void ftDk_SpecialAirNStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == 1) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialNStart, 0x0C4C5080,
                                  fp->cur_anim_frame, 1, 0, NULL);
        setCallbacks(gobj);
    }
}

void ftDk_SpecialAirNLoop_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == 1) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialNLoop, 0x0C4C5080,
                                  fp->cur_anim_frame, 1, 0, NULL);
        setCallbacks(gobj);
    }
}

void ftDk_SpecialAirNCancel_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == 1) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialNCancel, 0x0C4C5080,
                                  fp->cur_anim_frame, 1, 0, NULL);
        setCallbacks(gobj);
    }
}

void ftDk_SpecialAirN_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj)) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialN, 0x0C4D508E,
                                  fp->cur_anim_frame, 1, 0, NULL);
        setCallbacks(gobj);
    }
}

void ftDk_SpecialAirNFull_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj)) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialNFull, 0x0C4D508E,
                                  fp->cur_anim_frame, 1, 0, NULL);
        setCallbacks(gobj);
    }
}

void ftDk_SpecialN_DestroyAllEffects(HSD_GObj* gobj)
{
    efLib_DestroyAll(gobj);
}

void ftDk_SpecialN_DestroyAllEffectsPlus(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.dk.x222C = 0;
    efLib_DestroyAll(gobj);
}
