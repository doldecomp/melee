/**
 * @file ftpeachspecialn.c
 * @brief Neutral-B (Toad)
 * @details Neutral-B (Toad) logic for Peach.
 * Module prefix: ftPe
 */
#include "ftpeachspecialn.h"

#include <Runtime/platform.h>

#include <melee/ft/forward.h>
#include <sysdolphin/baselib/forward.h>

#include "ftpeach.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/kinds/ftCommon/inlines.h>
#include <melee/ft/types.h>
#include <melee/it/kinds/itpeachtoad.h>
#include <melee/it/kinds/itpeachtoadspore.h>
#include <melee/lb/lb_00B0.h>

typedef enum cmd_var_idx {
    cmd_phys_state,
    cmd_anim_state,
    cmd_accessory4,
    cmd_hit_anim_state,
} cmd_var_idx;

typedef enum accessory4_state {
    accessory4_state_0,
    accessory4_state_1,
    accessory4_state_2,
} accessory4_state;

typedef enum anim_state {
    anim_state_0,
    anim_state_1,
    anim_state_2,
} anim_state;

typedef enum phys_state {
    phys_state_0,
    phys_state_1,
    phys_state_2,
} phys_state;

/* 11E174 */ static void onAccessory4(HSD_GObj* gobj);
/* 11E230 */ static void onHitAccessory4(HSD_GObj* gobj);
/* 11E348 */ static void onEnterHitlag(HSD_GObj* gobj);
/* 11E378 */ static void onExitHitlag(HSD_GObj* gobj);
/* 11E7D4 */ static void doColl(HSD_GObj* gobj);
/* 11E8C0 */ static void doAirColl(HSD_GObj* gobj);
/* 11EB58 */ static void doHitColl(HSD_GObj* gobj);
/* 11EBC0 */ static void doAirHitColl(HSD_GObj* gobj);
/* 11EC30 */ static void setupHitColl(HSD_GObj* gobj);
/* 11EC6C */ static void onUnkHit(HSD_GObj* gobj);

/**
 * @brief Neutral-B (Toad) - onAccessory4
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void onAccessory4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[cmd_accessory4] != accessory4_state_0) {
        return;
    }
    fp->cmd_vars[cmd_accessory4] = accessory4_state_1;
    {
        Vec3 pos;
        lb_8000B1CC(fp->parts[FtPart_109].joint, NULL, &pos);
        fp->u.pe.toad_gobj = it_802BDE18(gobj, &pos, FtPart_109,
                                         It_Kind_Peach_Toad, fp->facing_dir);
    }
    fp->x1984_heldItemSpec = fp->u.pe.toad_gobj;
    if (fp->u.pe.toad_gobj != NULL) {
        fp->death2_cb = ftPe_Init_OnDeath2;
        fp->take_dmg_cb = ftPe_Init_OnDeath2;
    }
    fp->accessory4_cb = NULL;
    fp->pre_hitlag_cb = onEnterHitlag;
    fp->post_hitlag_cb = onExitHitlag;
}

/**
 * @brief Neutral-B (Toad) - doHitAccessory4
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
static void doHitAccessory4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    lb_8000B1CC(fp->parts[FtPart_109].joint, NULL, &pos);
    pos.y += 2.5f;
    pos.z = 0;
    it_802BE214(gobj, &pos, It_Kind_Peach_ToadSpore, fp->facing_dir);
}

/**
 * @brief Neutral-B (Toad) - onHitAccessory4
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
static void onHitAccessory4(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    doHitAccessory4(gobj);
    fp->accessory4_cb = NULL;
}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialN_DoDeath2
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_SpecialN_DoDeath2(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    onExitHitlag(gobj);
    fp->u.pe.toad_gobj = NULL;
    fp->death2_cb = NULL;
    fp->take_dmg_cb = NULL;
}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialN_OnDeath2
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_SpecialN_OnDeath2(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.pe.toad_gobj != NULL) {
        it_802BDF40(fp->u.pe.toad_gobj);
        ftPe_SpecialN_DoDeath2(gobj);
    }
}

/**
 * @brief Neutral-B (Toad) - onEnterHitlag
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
static void onEnterHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.pe.toad_gobj != NULL) {
        it_802BDFA0(fp->u.pe.toad_gobj);
    }
}

/**
 * @brief Neutral-B (Toad) - onExitHitlag
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
static void onExitHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.pe.toad_gobj != NULL) {
        it_802BDFC0(fp->u.pe.toad_gobj);
    }
}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialN_IsActive
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
bool ftPe_SpecialN_IsActive(HSD_GObj* gobj)
{
    FtMotionId msid = GET_FIGHTER(gobj)->motion_id;
    if (msid >= ftPe_MS_SpecialN && msid <= ftPe_MS_SpecialAirNHit) {
        return false;
    } else {
        return true;
    }
}

/**
 * @brief Neutral-B (Toad) - reset
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
static void reset(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[cmd_phys_state] = fp->cmd_vars[cmd_anim_state] =
        fp->cmd_vars[cmd_accessory4] = fp->cmd_vars[cmd_hit_anim_state] = 0;
    fp->mv.pe.specialn.facing_dir = fp->facing_dir;
    fp->accessory4_cb = onAccessory4;
}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialN_Enter
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_SpecialN_Enter(HSD_GObj* gobj)
{
    u8 _[8];
    GET_FIGHTER(gobj)->self_vel.y = 0;
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialN, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
    reset(gobj);
}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialAirN_Enter
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_SpecialAirN_Enter(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    fp->self_vel.x /= da->specialairn_vel_x_div;
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialAirN, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
    reset(gobj);
}

/**
 * @brief Neutral-B (Toad) - doAnim
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
static void doAnim(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[cmd_anim_state] == anim_state_1) {
        fp->cmd_vars[cmd_anim_state] = anim_state_2;
        ftColl_8007B1B8(gobj, (ShieldDesc*) &da->xAC, onUnkHit);
        fp->x221B.x221B_b3 = true;
        fp->shield_unk0 = da->xA8;
        fp->shield_unk1 = da->xA8;
    } else if (fp->cmd_vars[cmd_anim_state] == anim_state_0) {
        fp->x221B.x221B_b0 = false;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
    }
}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialN_Anim
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_SpecialN_Anim(HSD_GObj* gobj)
{
    u8 _[16];
    doAnim(gobj, ft_8008A2BC);
}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialAirN_Anim
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_SpecialAirN_Anim(HSD_GObj* gobj)
{
    u8 _[16];
    doAnim(gobj, ftCo_Fall_Enter);
}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialN_IASA
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_SpecialN_IASA(HSD_GObj* gobj) {}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialAirN_IASA
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_SpecialAirN_IASA(HSD_GObj* gobj) {}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialN_Phys
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_SpecialN_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEE0(gobj);
}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialAirN_Phys
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_SpecialAirN_Phys(HSD_GObj* gobj)
{
    u8 _[16];
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[cmd_phys_state] >= 1) {
        if (fp->cmd_vars[cmd_phys_state] == 1) {
            fp->cmd_vars[cmd_phys_state] = phys_state_2;
            if (!fp->u.pe.specialairn_used) {
                fp->u.pe.specialairn_used = true;
                fp->self_vel.y = da->specialairn_vel_y;
            } else {
                fp->self_vel.y = 0;
            }
        }
        ftCommon_Fall(fp, da->xA0, da->xA4);
    } else {
        ftCommon_FallBasic(fp);
    }
    ftCommon_CalcSelfAccel_Deaccel(fp, da->x98);
    ftColl_8007AEE0(gobj);
}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialN_Coll
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_SpecialN_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        doColl(gobj);
    }
}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialAirN_Coll
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_SpecialAirN_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        doAirColl(gobj);
    }
}

/**
 * @brief Neutral-B (Toad) - setupColl
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
static void setupColl(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    if (fp->u.pe.toad_gobj != NULL) {
        fp->death2_cb = ftPe_Init_OnDeath2;
        fp->take_dmg_cb = ftPe_Init_OnDeath2;
    }
    fp->accessory4_cb = onAccessory4;
    fp->pre_hitlag_cb = onEnterHitlag;
    fp->post_hitlag_cb = onExitHitlag;
    if (fp->cmd_vars[cmd_anim_state] == anim_state_2) {
        ftColl_8007B1B8(gobj, (ShieldDesc*) &da->xAC, onUnkHit);
        fp->x221B.x221B_b3 = true;
    }
}

static MotionFlags const coll_mf =
    Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipHit | Ft_MF_SkipMatAnim |
    Ft_MF_SkipColAnim | Ft_MF_UpdateCmd | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
    Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags | Ft_MF_Unk27;

/**
 * @brief Neutral-B (Toad) - doColl
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
static void doColl(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_GroundToAirStateChange(gobj, fp, ftPe_MS_SpecialAirN, coll_mf);
    if (fp->cmd_vars[cmd_phys_state] == phys_state_1) {
        fp->cmd_vars[cmd_phys_state] = phys_state_2;
    }
    setupColl(gobj);
}

/**
 * @brief Neutral-B (Toad) - doAirColl
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
static void doAirColl(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    fp->u.pe.specialairn_used = false;
    ftCommon_AirToGroundStateChange(gobj, fp, ftPe_MS_SpecialN, coll_mf);
    setupColl(gobj);
}

/**
 * @brief Neutral-B (Toad) - doHitAnim
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
static void doHitAnim(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[cmd_hit_anim_state]) {
        fp->cmd_vars[cmd_hit_anim_state] = false;
        fp->accessory4_cb = onHitAccessory4;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
    }
}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialNHit_Anim
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_SpecialNHit_Anim(HSD_GObj* gobj)
{
    doHitAnim(gobj, ft_8008A2BC);
}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialAirNHit_Anim
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_SpecialAirNHit_Anim(HSD_GObj* gobj)
{
    doHitAnim(gobj, ftCo_Fall_Enter);
}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialNHit_IASA
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_SpecialNHit_IASA(HSD_GObj* gobj) {}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialAirNHit_IASA
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_SpecialAirNHit_IASA(HSD_GObj* gobj) {}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialNHit_Phys
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_SpecialNHit_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialAirNHit_Phys
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_SpecialAirNHit_Phys(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    ftCommon_Fall(fp, da->xA0, da->xA4);
    ftCommon_CalcSelfAccel_Deaccel(fp, da->x98);
}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialNHit_Coll
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_SpecialNHit_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        doHitColl(gobj);
    }
}

/**
 * @brief Neutral-B (Toad) - ftPe_SpecialAirNHit_Coll
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_SpecialAirNHit_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        doAirHitColl(gobj);
    }
}

/**
 * @brief Neutral-B (Toad) - doHitColl
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
static void doHitColl(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_GroundToAirStateChange(gobj, fp, ftPe_MS_SpecialAirNHit, coll_mf);
    setupHitColl(gobj);
}

/// @todo Can maybe me combined with #doAirColl.
/**
 * @brief Neutral-B (Toad) - doAirHitColl
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void doAirHitColl(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->u.pe.specialairn_used = false;
    ftCommon_AirToGroundStateChange(gobj, fp, ftPe_MS_SpecialNHit, coll_mf);
    setupHitColl(gobj);
}

/**
 * @brief Neutral-B (Toad) - setupHitColl
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
static void setupHitColl(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.pe.toad_gobj != NULL) {
        fp->death2_cb = ftPe_Init_OnDeath2;
        fp->take_dmg_cb = ftPe_Init_OnDeath2;
    }

    fp->pre_hitlag_cb = onEnterHitlag;
    fp->post_hitlag_cb = onExitHitlag;
}

/**
 * @brief Neutral-B (Toad) - onUnkHit
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
static void onUnkHit(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid;
    fp->mv.pe.specialn.facing_dir = fp->specialn_facing_dir;
    if (fp->ground_or_air == GA_Ground) {
        msid = ftPe_MS_SpecialNHit;
    } else {
        msid = ftPe_MS_SpecialAirNHit;
    }
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 9, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    if (fp->u.pe.toad_gobj != NULL) {
        it_802BE100(fp->u.pe.toad_gobj);
    }
    setupHitColl(gobj);
}
