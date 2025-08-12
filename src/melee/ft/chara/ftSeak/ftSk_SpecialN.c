#include "ftSk_SpecialN.h"

#include "ef/efsync.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ft_0D14.h"
#include "ft/ftcolanim.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"

#include "ftSeak/forward.h"

#include "ftSeak/ftSk_Init.h"
#include "it/items/itseakneedleheld.h"
#include "it/items/itseakneedlethrown.h"

#include <common_structs.h>

/* 1120D4 */ static void ftSk_SpecialN_801120D4(Fighter_GObj* gobj);
/* 112D44 */ static void shootNeedles(Fighter_GObj* gobj);

static float needleYPosScale[] = {
    -1, -0.75f, -0.5f, -0.25f, 0, +0.25f, +0.5f, +0.75f, +1,
};

/// Sheik_CheckAndDestroyNeedles
void ftSk_SpecialN_80111FBC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* da = fp->dat_attrs;
    if (fp->fv.sk.x4 != NULL) {
        fp->fv.sk.x4 = NULL;
        while (fp->fv.sk.x0 != 0) {
            Vec3 pos = fp->cur_pos;
            PAD_STACK(4 * 1);
            {
                float y_scale;
                if (fp->ground_or_air == GA_Ground) {
                    y_scale = da->x4;
                } else {
                    y_scale = da->xC;
                }
                pos.y += fp->x34_scale.y * y_scale;
            }
            pos.z = 0;
            {
                Item_GObj* item_gobj =
                    it_802AFD8C(gobj, &pos, 79, fp->facing_dir);
                if (item_gobj != NULL) {
                    it_802AFEA8(item_gobj, gobj, 1);
                }
            }
            --fp->fv.sk.x0;
        }
        if (fp->death2_cb == ftSk_Init_80110198 ||
            fp->take_dmg_cb == ftSk_Init_80110198)
        {
            ftSk_SpecialN_801120D4(gobj);
        }
    }
    fp->fv.sk.x0 = 0;
}

void ftSk_SpecialN_801120D4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = NULL;
    fp->death2_cb = NULL;
}

static inline void setDmgCallbacks(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = ftSk_Init_80110198;
    fp->death2_cb = ftSk_Init_80110198;
}

static inline void doEnter(Fighter_GObj* gobj, ftSeak_MotionState msid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0, NULL);
    fp->throw_flags_b0 = false;
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    fp->mv.sk.specialn.x0 = 0;
    if (fp->fv.sk.x0 == 0) {
        fp->fv.sk.x0 = 1;
    }
    fp->mv.sk.specialn.x4 = 0;
    fp->mv.sk.specialn.x8 = 0;
    setDmgCallbacks(gobj);
    ftAnim_8006EBA4(gobj);
}

void ftSk_SpecialN_Enter(Fighter_GObj* gobj)
{
    doEnter(gobj, ftSk_MS_SpecialNStart);
}

void ftSk_SpecialAirN_Enter(Fighter_GObj* gobj)
{
    doEnter(gobj, ftSk_MS_SpecialAirNStart);
}

void ftSk_SpecialNStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.sk.x4 = it_802B19AC(gobj, &fp->cur_pos, 23, 80, fp->facing_dir);
        Fighter_ChangeMotionState(gobj, ftSk_MS_SpecialNLoop, Ft_MF_None, 0, 1,
                                  0, NULL);
        setDmgCallbacks(gobj);
    }
}

/// Sheik_ChargeNeedlesIncrementer
void ftSk_SpecialNLoop_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (fp->mv.sk.specialn.x8) {
    case 0: {
        Fighter* fp = GET_FIGHTER(gobj);
        ft_PlaySFX(fp, 270134, 127, 64);
    }
    }
    ++fp->mv.sk.specialn.x8;
    if (fp->cur_anim_frame == 0) {
        ++fp->fv.sk.x0;
        fp->mv.sk.specialn.x8 = 0;
        if (fp->fv.sk.x0 > 6) {
            fp->fv.sk.x0 = 6;
            fp->mv.sk.specialn.x8 = 100;
            ftCo_800BFFD0(fp, 86, 0);
        }
    }
}

void ftSk_SpecialNCancel_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.sk.x4 = 0;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftSk_SpecialNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4 * 8);
    switch (fp->mv.sk.specialn.x0) {
    case 2:
    case 5:
    case 8:
    case 11:
    case 14:
    case 17:
        fp->mv.sk.specialn.x4 = true;
        fp->fv.sk.x4 = NULL;
    }
    ++fp->mv.sk.specialn.x0;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftSk_SpecialAirNStart_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.sk.x4 = it_802B19AC(gobj, &fp->cur_pos, 23, 80, fp->facing_dir);
        Fighter_ChangeMotionState(gobj, ftSk_MS_SpecialAirNLoop, Ft_MF_None, 0,
                                  1, 0, NULL);
        setDmgCallbacks(gobj);
    }
}

void ftSk_SpecialAirNLoop_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (fp->mv.sk.specialn.x8) {
    case 0: {
        Fighter* fp = GET_FIGHTER(gobj);
        ft_PlaySFX(fp, 270134, 127, 64);
    }
    }
    ++fp->mv.sk.specialn.x8;
    if (fp->cur_anim_frame == 0) {
        ++fp->fv.sk.x0;
        fp->mv.sk.specialn.x8 = 0;
        if (fp->fv.sk.x0 > 6) {
            fp->fv.sk.x0 = 6;
            fp->mv.sk.specialn.x8 = 100;
            ftCo_800BFFD0(fp, 86, 0);
        }
    }
}

void ftSk_SpecialAirNCancel_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* da = fp->dat_attrs;
    PAD_STACK(4 * 2);
    fp->fv.sk.x4 = 0;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (da->x10 == 0) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, true, 1, da->x10);
        }
    }
}

void ftSk_SpecialAirNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* da = fp->dat_attrs;

    PAD_STACK(4 * 8);

    switch (fp->mv.sk.specialn.x0) {
    case 2:
    case 5:
    case 8:
    case 11:
    case 14:
    case 17:
        fp->mv.sk.specialn.x4 = true;
        fp->fv.sk.x4 = NULL;
    }

    ++fp->mv.sk.specialn.x0;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (da->x10 == 0) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, true, 1, da->x10);
        }
    }
}

void ftSk_SpecialNStart_IASA(Fighter_GObj* gobj) {}

static void doIasa(Fighter_GObj* gobj, ftSeak_MotionState end_msid,
                   ftSeak_MotionState cancel_msid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->mv.sk.specialn.x0 = 0;
        Fighter_ChangeMotionState(gobj, end_msid, Ft_MF_None, 0, 1, 0, NULL);
        setDmgCallbacks(gobj);
        fp->accessory4_cb = shootNeedles;
    } else if (fp->input.x668 & HSD_PAD_LR) {
        Fighter_ChangeMotionState(gobj, cancel_msid, Ft_MF_None, 0, 1, 0,
                                  NULL);
        setDmgCallbacks(gobj);
    }
}

void ftSk_SpecialNLoop_IASA(Fighter_GObj* gobj)
{
    doIasa(gobj, ftSk_MS_SpecialNEnd, ftSk_MS_SpecialNCancel);
}

void ftSk_SpecialNCancel_IASA(Fighter_GObj* gobj) {}

void ftSk_SpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftSk_SpecialAirNStart_IASA(Fighter_GObj* gobj) {}

void ftSk_SpecialAirNLoop_IASA(Fighter_GObj* gobj)
{
    doIasa(gobj, ftSk_MS_SpecialAirNEnd, ftSk_MS_SpecialAirNCancel);
}

void ftSk_SpecialAirNCancel_IASA(Fighter_GObj* gobj) {}

void ftSk_SpecialAirNEnd_IASA(Fighter_GObj* gobj) {}

void ftSk_SpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSk_SpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSk_SpecialNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSk_SpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSk_SpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftSk_SpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftSk_SpecialAirNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftSk_SpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftSk_SpecialNStart_Coll(Fighter_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 7) | (1 << 12) | (1 << 14) | (1 << 18) |
                          (1 << 19) | (1 << 22) | (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftSk_MS_SpecialAirNStart, mf,
                                  fp->cur_anim_frame, 1, 0, NULL);

        {
            setDmgCallbacks(gobj);
        }
    }
}

void ftSk_SpecialNLoop_Coll(Fighter_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 7) | (1 << 12) | (1 << 14) | (1 << 18) |
                          (1 << 19) | (1 << 22) | (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftSk_MS_SpecialAirNLoop, mf,
                                  fp->cur_anim_frame, 1, 0, NULL);

        setDmgCallbacks(gobj);
    }
}

static inline void clearDmgCallbacks(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = NULL;
    fp->death2_cb = NULL;
}

void ftSk_SpecialNCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* da = fp->dat_attrs;
    PAD_STACK(4 * 2);
    if (ft_80082708(gobj) == GA_Ground) {
        clearDmgCallbacks(gobj);
        if (da->x10 == 0) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, true, 1, da->x10);
        }
    }
}

void ftSk_SpecialNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* da = fp->dat_attrs;
    if (ft_80082708(gobj) == GA_Ground) {
        clearDmgCallbacks(gobj);
        fp->fv.sk.x0 = 0;
        fp->mv.sk.specialn.x4 = false;
        if (da->x10 == 0) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1, da->x10);
        }
    }
}

static inline void doColl(Fighter_GObj* gobj, ftSeak_MotionState msid)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 7) | (1 << 12) | (1 << 14) | (1 << 18) |
                          (1 << 19) | (1 << 22) | (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, msid, mf, fp->cur_anim_frame, 1, 0,
                                  NULL);
        setDmgCallbacks(gobj);
    }
}

void ftSk_SpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    doColl(gobj, ftSk_MS_SpecialNStart);
}

void ftSk_SpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    doColl(gobj, ftSk_MS_SpecialNLoop);
}

void ftSk_SpecialAirNCancel_Coll(Fighter_GObj* gobj)
{
    PAD_STACK(4 * 2);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCo_800D5BF8(gobj);
        clearDmgCallbacks(gobj);
    }
}

void ftSk_SpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        clearDmgCallbacks(gobj);
        fp->fv.sk.x0 = 0;
        fp->mv.sk.specialn.x4 = false;
        ftCo_800D5BF8(gobj);
    }
}

void shootNeedles(Fighter_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftSeakAttributes* da = fp->dat_attrs;

    if (fp->mv.sk.specialn.x4) {
        fp->mv.sk.specialn.x4 = false;

        if (fp->fv.sk.x0 > 0) {
            Vec3 pos = fp->cur_pos;
            float x_scale, y_scale;
            int rand;
            if (fp->ground_or_air == GA_Ground) {
                x_scale = da->x0 * fp->facing_dir;
                pos.x += fp->x34_scale.y * x_scale;
                rand = HSD_Randi(9);
                y_scale = da->x4 + needleYPosScale[rand];
                pos.y += fp->x34_scale.y * y_scale;
            } else {
                x_scale = da->x8 * fp->facing_dir;
                pos.x += fp->x34_scale.y * x_scale;
                rand = HSD_Randi(9);
                y_scale = (2.0f * needleYPosScale[rand]) + da->xC;
                pos.y += fp->x34_scale.y * y_scale;
            }
            pos.z = 0;

            {
                Item_GObj* item_gobj =
                    it_802AFD8C(gobj, &pos, 79, fp->facing_dir);
                if (item_gobj != NULL) {
                    item_gobj = it_802AFEA8(item_gobj, gobj, 0);
                }
            }

            --fp->fv.sk.x0;

            efSync_Spawn(1283, gobj, &pos);
            ft_PlaySFX(fp, 270140, 127, 64);
        }
    }
}
