#include "ftMr_SpecialS.h"

#include "ftMr_Init.h"
#include "types.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <stddef.h>
#include <dolphin/mtx/types.h>
#include <baselib/random.h>

static void setCallbacks(Fighter* fp)
{
    if (fp->fv.mr.x223C_capeGObj != NULL) {
        fp->cb.x21E4_callback_OnDeath2 = ftMr_Init_OnTakeDamage;
        fp->cb.x21DC_callback_OnTakeDamage = ftMr_Init_OnTakeDamage;
    }

    fp->cb.x21D4_callback_EnterHitlag = ftMr_SpecialS_EnterHitlag;
    fp->cb.x21D8_callback_ExitHitlag = ftMr_SpecialS_ExitHitlag;
}

void ftMr_SpecialS_CreateCape(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMario_DatAttrs* sa = fp->dat_attrs;

    if (!fp->cmd_vars[2]) {
        /// @todo Can't move below @c _.
        Vec3 coords;

        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[4];
#endif

        fp->cmd_vars[2] = true;
        lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_RThumbNb)].joint,
                    NULL, &coords);

        {
            HSD_GObj* cape = it_802B2560(gobj, fp->facing_dir, &coords,
                                         ftParts_8007500C(fp, FtPart_RThumbNb),
                                         sa->specials.cape_kind);

            fp->fv.mr.x223C_capeGObj = cape;
        }

        fp->x1984_heldItemSpec = fp->fv.mr.x223C_capeGObj;
        setCallbacks(fp);
        fp->cb.x21BC_callback_Accessory4 = NULL;
    }
}

void ftMr_SpecialS_Reset(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMr_SpecialS_ExitHitlag(gobj);
    fp->fv.mr.x223C_capeGObj = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

void ftMr_SpecialS_RemoveCape(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.mr.x223C_capeGObj != NULL) {
        it_802B2674(fp->fv.mr.x223C_capeGObj);
        ftMr_SpecialS_Reset(gobj);
    }
}

void ftMr_SpecialS_EnterHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.mr.x223C_capeGObj != NULL) {
        it_802B26C0(fp->fv.mr.x223C_capeGObj);
    }
}

void ftMr_SpecialS_ExitHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.mr.x223C_capeGObj != NULL) {
        it_802B26E0(fp->fv.mr.x223C_capeGObj);
    }
}

bool ftMr_SpecialS_CheckItemCapeRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    enum_t msid = fp->motion_id;

    if (msid >= ftMr_MS_SpecialS && msid <= ftMr_MS_SpecialAirS) {
        return false;
    }

    return true;
}

static void changeAction(HSD_GObj* gobj, ftMario_MotionState msid)
{
    Fighter_ChangeMotionState(gobj, msid, 0, NULL, 0, 1, 0);
    ftAnim_8006EBA4(gobj);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->cmd_vars[2] = 0;
        fp->cmd_vars[1] = 0;
        fp->cmd_vars[0] = 0;
        fp->mv.mr.SpecialS.reflecting = false;
        fp->cb.x21BC_callback_Accessory4 = ftMr_SpecialS_CreateCape;
    }
}

void ftMr_SpecialS_Enter(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.y = 0;

    changeAction(gobj, ftMr_MS_SpecialS);
}

void ftMr_SpecialAirS_Enter(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftMario_DatAttrs* sa = fp->dat_attrs;
    fp->self_vel.x /= sa->specials.vel_x_decay;
    changeAction(gobj, ftMr_MS_SpecialAirS);
}

void ftMr_SpecialS_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftMr_SpecialAirS_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800CC730(gobj);
    }
}

void ftMr_SpecialS_IASA(HSD_GObj* gobj) {}

void ftMr_SpecialAirS_IASA(HSD_GObj* gobj) {}

static void reflect(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMario_DatAttrs* sa = fp->dat_attrs;

    if (fp->cmd_vars[1] == 1 && !fp->mv.mr.SpecialS.reflecting) {
        fp->mv.mr.SpecialS.reflecting = true;
        ftColl_CreateReflectHit(gobj, &sa->cape_reflection, NULL);
    } else if (fp->cmd_vars[1] == 0 && fp->mv.mr.SpecialS.reflecting == true) {
        fp->mv.mr.SpecialS.reflecting = false;
        fp->x2218_b3 = false;
    }

    ftColl_8007AEF8(gobj);
}

void ftMr_SpecialS_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused0[4];
#endif

    {
        /// @todo Cannot be moved above @c unused0 or below @c unused1.
        Vec3 coords;

        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 unused1[16];
#endif

        Fighter* fp = GET_FIGHTER(gobj);

        if (fp->cmd_vars[0] == 1U) {
            fp->cmd_vars[0] = 2U;
            lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_HipN)].joint,
                        NULL, &coords);

            coords.x += 3 * fp->facing_dir;
            lb_800119DC(&coords, 120, 0.9, 0.02, M_PI_3);
        }
    }

    ft_80084F3C(gobj);
    reflect(gobj);
}

void ftMr_SpecialAirS_Phys(HSD_GObj* gobj)
{
    u32 ftcmd_var0_tmp;

    Fighter* fp;
    ftMario_DatAttrs* sa;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused0[4];
#endif

    Vec3 coords;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused1[24];
#endif

    fp = gobj->user_data;

    ftcmd_var0_tmp = fp->cmd_vars[0];
    sa = fp->dat_attrs;

    if (ftcmd_var0_tmp >= 1U) {
        if (ftcmd_var0_tmp == 1U) {
            fp->cmd_vars[0] = 2U;
            if (!fp->fv.mr.x2238_isCapeBoost) {
                fp->fv.mr.x2238_isCapeBoost = true;
                fp->self_vel.y = sa->specials.vel.y;
            } else {
                fp->self_vel.y = 0;
            }
            lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_HipN)].joint,
                        NULL, &coords);
            coords.x += 3 * fp->facing_dir;
            lb_800119DC(&coords, 120, 3, 0.1, M_PI_3);
        }
        ftCommon_8007D494(fp, sa->specials.grav, sa->specials.terminal_vel);
    } else {
        ftCommon_8007D4B8(fp);
    }

    ftCommon_8007CE94(fp, sa->specials.vel.x);
    reflect(gobj);
}

void ftMr_SpecialS_Coll(HSD_GObj* gobj)
{
    if (ft_800827A0(gobj) == false) {
        ftMr_SpecialS_GroundToAir(gobj);
    }
}

void ftMr_SpecialAirS_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj) != false) {
        ftMr_SpecialAirS_AirToGround(gobj);
    }
}

static void collUpdateVars(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((s32) fp->mv.mr.SpecialS.reflecting != false) {
        fp->x2218_b3 = 1;
    }
    setCallbacks(fp);
    fp->cb.x21BC_callback_Accessory4 = ftMr_SpecialS_CreateCape;
}

static usize_t const transition_flags =
    Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipHit | Ft_MF_SkipMatAnim |
    Ft_MF_UpdateCmd | Ft_MF_SkipColAnim | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
    Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags | Ft_MF_Unk27;

void ftMr_SpecialS_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftMr_MS_SpecialAirS, transition_flags,
                              NULL, fp->cur_anim_frame, 1, 0);
    if ((s32) fp->cmd_vars[0] == 1U) {
        fp->cmd_vars[0] = 2U;
    }

    collUpdateVars(gobj);
}

void ftMr_SpecialAirS_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    fp = gobj->user_data;
    fp->fv.mr.x2238_isCapeBoost = false;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftMr_MS_SpecialS, transition_flags, NULL,
                              fp->cur_anim_frame, 1, 0);

    collUpdateVars(gobj);
}
