#include "ftkirbyspecialpeach.h"

#include "types.h"

#include <placeholder.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"

#include "ftKirby/forward.h"

#include "ftKirby/ftkirby.h"
#include "it/items/itpeachtoad.h"
#include "it/items/itpeachtoadspore.h"
#include "lb/lb_00B0.h"

#include <common_structs.h>
#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

/* 10C344 */ static void fn_8010C344(Fighter_GObj* gobj);
/* 10C44C */ static void fn_8010C44C(Fighter_GObj* gobj);
/* 10CD88 */ static void fn_8010CD88(Fighter_GObj* gobj);

static void fn_8010C288(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->cmd_vars[2]) {
        Vec3 pos;
        fp->cmd_vars[2] = true;
        lb_8000B1CC(fp->parts[FtPart_R3rdNa].joint, 0, &pos);
        fp->fv.kb.xD0 =
            it_802BDE18(gobj, &pos, FtPart_R3rdNa, 134, fp->facing_dir);
        if (fp->fv.kb.xD0 != NULL) {
            fp->death2_cb = &ftKb_Init_800EE74C;
            fp->take_dmg_cb = &ftKb_Init_800EE7B8;
        }
        fp->accessory4_cb = NULL;
        fp->pre_hitlag_cb = fn_8010C44C;
        fp->post_hitlag_cb = ftKb_SpecialNPe_8010C47C;
    }
}

void fn_8010C344(HSD_GObj* arg0)
{
    PAD_STACK(4);
    {
        Fighter* fp = arg0->user_data;
        Vec3 pos;
        PAD_STACK(4 * 2);
        lb_8000B1CC(fp->parts[FtPart_R3rdNa].joint, 0, &pos);
        pos.y += 2.5f;
        pos.z = 0;
        it_802BE214(arg0, &pos, 135, fp->facing_dir);
        fp->accessory4_cb = NULL;
    }
}

void ftKb_SpecialNPe_8010C3C0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialNPe_8010C47C(gobj);
    fp->fv.kb.xD0 = NULL;
}

void ftKb_SpecialNPe_8010C3F4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xD0 != NULL) {
        it_802BDF40(fp->fv.kb.xD0);
        ftKb_SpecialNPe_8010C3C0(gobj);
    }
}

void fn_8010C44C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xD0 != NULL) {
        it_802BDFA0(fp->fv.kb.xD0);
    }
}

void ftKb_SpecialNPe_8010C47C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xD0 != NULL) {
        it_802BDFC0(fp->fv.kb.xD0);
    }
}

bool ftKb_SpecialNPe_8010C4AC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->motion_id >= ftKb_MS_PeSpecialLw &&
        fp->motion_id <= ftKb_MS_PeSpecialAirLwHit)
    {
        return false;
    }
    return true;
}

static void inlineA0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4 * 2);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    fp->mv.kb.specialn_pe.facing_dir = fp->facing_dir;
    fp->accessory4_cb = fn_8010C288;
}

static void inlineA1(HSD_GObj* gobj, ftKirby_MotionState msid)
{
    Fighter_ChangeMotionState(gobj, msid, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    inlineA0(gobj);
}

void ftKb_SpecialNPe_8010C4D4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4 * 2);
    fp->self_vel.y = 0;
    inlineA1(gobj, ftKb_MS_PeSpecialLw);
}

void ftKb_SpecialNPe_8010C560(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4 * 2);
    fp->self_vel.x /= da->specialn_pe_friction;
    inlineA1(gobj, ftKb_MS_PeSpecialAirLw);
}

static inline void doPeAnim(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u32 cmd_var1 = fp->cmd_vars[1];
    struct ftKb_DatAttrs* da = fp->dat_attrs;

    if (cmd_var1 == 1) {
        fp->cmd_vars[1] = 2;
        ftColl_8007B1B8(gobj, (ShieldDesc*) &da->specialn_pe_absorbdesc,
                        fn_8010CD88);
        fp->x221B_b3 = true;
        fp->shield_unk0 = da->specialn_pe_unk3;
        fp->shield_unk1 = da->specialn_pe_unk3;
    } else if (cmd_var1 == 0) {
        fp->x221B_b0 = false;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
    }
}

void ftKb_PeSpecialLw_Anim(HSD_GObj* gobj)
{
    PAD_STACK(4 * 4);
    doPeAnim(gobj, ft_8008A2BC);
}

void ftKb_PeSpecialAirLw_Anim(HSD_GObj* gobj)
{
    PAD_STACK(4 * 4);
    doPeAnim(gobj, ftCo_Fall_Enter);
}

void ftKb_PeSpecialLw_IASA(Fighter_GObj* gobj) {}

void ftKb_PeSpecialAirLw_IASA(Fighter_GObj* gobj) {}

void ftKb_PeSpecialLw_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEE0(gobj);
}

void ftKb_PeSpecialAirLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u32 cmd_var0 = fp->cmd_vars[0];
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4 * 4);
    if (cmd_var0 >= 1) {
        if (cmd_var0 == 1) {
            fp->cmd_vars[0] = 2;
            if (!fp->fv.kb.xCC) {
                fp->fv.kb.xCC = true;
                fp->self_vel.y = da->specialn_pe_air_initial_vertical_momentum;
            } else {
                fp->self_vel.y = 0;
            }
        }
        ftCommon_Fall(fp, da->specialn_pe_fall_acceleration,
                      da->specialn_pe_unk2);
    } else {
        ftCommon_FallBasic(fp);
    }
    ftCommon_ApplyFrictionAir(
        fp, da->specialn_pe_air_horizontal_momentum_preservation);
    ftColl_8007AEE0(gobj);
}

void ftKb_PeSpecialLw_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftKb_SpecialNPe_8010C8D8(gobj);
    }
}

void ftKb_PeSpecialAirLw_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftKb_SpecialNPe_8010C9CC(gobj);
    }
}

void ftKb_SpecialNPe_8010C8D8(HSD_GObj* gobj)
{
    /// @todo Flag names.
    static u32 const mf = (1 << 2) | (1 << 3) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4 * 2);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_PeSpecialAirLw, mf,
                              fp->cur_anim_frame, 1, 0, NULL);
    if (fp->cmd_vars[0] == 1) {
        fp->cmd_vars[0] = 2;
    }
    {
        /// @todo @c da can't move below @c fp
        ftKb_DatAttrs* da;
        Fighter* fp = GET_FIGHTER(gobj);
        da = fp->dat_attrs;
        if (fp->fv.kb.xD0 != NULL) {
            fp->death2_cb = ftKb_Init_800EE74C;
            fp->take_dmg_cb = ftKb_Init_800EE7B8;
        }

        fp->accessory4_cb = fn_8010C288;
        fp->pre_hitlag_cb = fn_8010C44C;
        fp->post_hitlag_cb = ftKb_SpecialNPe_8010C47C;

        if (fp->cmd_vars[1] == 2) {
            ftColl_8007B1B8(gobj, (ShieldDesc*) &da->specialn_pe_absorbdesc,
                            fn_8010CD88);
            fp->x221B_b3 = true;
        }
    }
}

void ftKb_SpecialNPe_8010C9CC(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 2) | (1 << 3) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.kb.xCC = false;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_PeSpecialLw, mf,
                              fp->cur_anim_frame, 1, 0, NULL);
    {
        /// @todo @c da can't move below @c fp
        ftKb_DatAttrs* da;
        Fighter* fp = GET_FIGHTER(gobj);
        PAD_STACK(4 * 2);
        da = fp->dat_attrs;
        if (fp->fv.kb.xD0 != NULL) {
            fp->death2_cb = ftKb_Init_800EE74C;
            fp->take_dmg_cb = ftKb_Init_800EE7B8;
        }
        fp->accessory4_cb = fn_8010C288;
        fp->pre_hitlag_cb = fn_8010C44C;
        fp->post_hitlag_cb = ftKb_SpecialNPe_8010C47C;

        if (fp->cmd_vars[1] == 2) {
            ftColl_8007B1B8(gobj, (ShieldDesc*) &da->specialn_pe_absorbdesc,
                            fn_8010CD88);
            fp->x221B_b3 = true;
        }
    }
}

static inline void doPeHitAnim(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[3]) {
        fp->cmd_vars[3] = false;
        fp->accessory4_cb = fn_8010C344;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
    }
}

void ftKb_PeSpecialLwHit_Anim(HSD_GObj* gobj)
{
    doPeHitAnim(gobj, ft_8008A2BC);
}

void ftKb_PeSpecialAirLwHit_Anim(HSD_GObj* gobj)
{
    doPeHitAnim(gobj, ftCo_Fall_Enter);
}

void ftKb_PeSpecialLwHit_IASA(Fighter_GObj* gobj) {}

void ftKb_PeSpecialAirLwHit_IASA(Fighter_GObj* gobj) {}

void ftKb_PeSpecialLwHit_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_PeSpecialAirLwHit_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4 * 2);
    ftCommon_Fall(fp, da->specialn_pe_fall_acceleration, da->specialn_pe_unk2);
    ftCommon_ApplyFrictionAir(
        fp, da->specialn_pe_air_horizontal_momentum_preservation);
}

void ftKb_PeSpecialLwHit_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftKb_SpecialNGw_8010CC6C(gobj);
    }
}

void ftKb_PeSpecialAirLwHit_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftKb_SpecialNGw_8010CCD4(gobj);
    }
}

void ftKb_SpecialNGw_8010CC6C(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 2) | (1 << 3) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_PeSpecialAirLwHit, mf,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftKb_SpecialNGw_8010CD44(gobj);
}

void ftKb_SpecialNGw_8010CCD4(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 2) | (1 << 3) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.kb.xCC = false;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_PeSpecialLwHit, mf,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftKb_SpecialNGw_8010CD44(gobj);
}

void ftKb_SpecialNGw_8010CD44(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xD0 != NULL) {
        fp->death2_cb = ftKb_Init_800EE74C;
        fp->take_dmg_cb = ftKb_Init_800EE7B8;
    }
    fp->pre_hitlag_cb = fn_8010C44C;
    fp->post_hitlag_cb = ftKb_SpecialNPe_8010C47C;
}

void fn_8010CD88(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.kb.specialn_pe.facing_dir = fp->specialn_facing_dir;
    {
        ftKirby_MotionState msid;
        if (fp->ground_or_air == GA_Ground) {
            msid = ftKb_MS_PeSpecialLwHit;
        } else {
            msid = ftKb_MS_PeSpecialAirLwHit;
        }
        Fighter_ChangeMotionState(gobj, msid, 0, 9, 1, 0, 0);
    }
    ftAnim_8006EBA4(gobj);
    if (fp->fv.kb.xD0 != NULL) {
        it_802BE100(fp->fv.kb.xD0);
    }
    ftKb_SpecialNGw_8010CD44(gobj);
}
