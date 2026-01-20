#include "ftKb_Init.h"
#include "types.h"

#include <placeholder.h>

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_CaptureWaitKirby.h"
#include "ft/chara/ftCommon/ftCo_Damage.h"
#include "ft/chara/ftCommon/ftCo_Escape.h"
#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
#include "ft/chara/ftCommon/ftCo_Jump.h"
#include "ft/chara/ftCommon/ftCo_KneeBend.h"
#include "ft/chara/ftCommon/ftCo_Lift.h"
#include "ft/chara/ftCommon/ftCo_Throw.h"
#include "ft/chara/ftCommon/ftCo_Wait.h"
#include "ft/chara/ftCommon/ftpickupitem.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C31.h"
#include "ft/ftcamera.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/ftdynamics.h"
#include "ft/ftparts.h"
#include "ft/ftwalkcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftCo_CaptureKirby.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_Landing.h"

#include "ftKirby/forward.h"

#include "ftLink/types.h"
#include "it/it_26B1.h"
#include "it/item.h"
#include "it/items/it_27CF.h"
#include "it/items/it_2ADA.h"
#include "it/items/it_2F28.h"
#include "it/items/itclimbersice.h"
#include "it/items/itgamewatchchef.h"
#include "it/items/itkirby_2F23.h"
#include "it/items/itkirbycutterbeam.h"
#include "it/items/itkirbygamewatchchefpan.h"
#include "it/items/itkirbyhammer.h"
#include "it/items/itkirbyyoshispecialn.h"
#include "it/items/itlinkarrow.h"
#include "it/items/itlinkbow.h"
#include "it/items/itmewtwoshadowball.h"
#include "it/items/itnesspkflush.h"
#include "it/items/itpeachtoad.h"
#include "it/items/itpeachtoadspore.h"
#include "it/items/itpikachutjoltground.h"
#include "it/items/itsamuschargeshot.h"
#include "it/items/itseakneedleheld.h"
#include "lb/lb_00B0.h"
#include "lb/lbanim.h"
#include "lb/lbvector.h"
#include "melee/lb/lbrefract.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"
#include "pl/player.h"

#include <common_structs.h>
#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

// Forward declarations for functions called before definition
void fn_80105AB0(Fighter_GObj*);
void fn_80105A34(Fighter_GObj*);
void fn_801090D4(Fighter_GObj*);
static void fn_801095DC(HSD_GObj*);
static void fn_80109680(HSD_GObj*);
static void fn_80109714(HSD_GObj*);
static void fn_801097B8(HSD_GObj*);
void fn_8010A930(Fighter_GObj*, Fighter_GObj*);

inline void ftKirbyDmgInline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->death2_cb = (void (*)(HSD_GObj*)) ftKb_Init_800EE74C;
    fp->take_dmg_cb = (void (*)(HSD_GObj*)) ftKb_Init_800EE7B8;
}

static inline void ftKb_SpecialNZd_Helper(Fighter_GObj* gobj)
{
    ftKb_DatAttrs* attributes;
    Fighter* fighter2; // r5
    fighter2 = GET_FIGHTER(gobj);
    attributes = fighter2->dat_attrs;
    fighter2->cmd_vars[0] = 0;
    fighter2->mv.zd.specialn.x0 =
        attributes->specialn_zd_frames_before_gravity;
}

void ftKb_SpecialNZd_80105BA8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(20);

    fp->self_vel.y = 0;
    fp->self_vel.x =
        fp->self_vel.x / da->specialn_zd_horizontal_momentum_preservation;

    Fighter_ChangeMotionState(gobj, ftKb_MS_ZdSpecialAirN, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);

    ftKb_SpecialNZd_Helper(gobj);
    fp->accessory4_cb = fn_80105AB0;
}

void ftKb_ZdSpecialN_Anim(Fighter_GObj* gobj)
{
    int var0;
    Fighter* fp;
    int zero;
    int var1;
    ftKb_DatAttrs* da;

    fp = GET_FIGHTER(gobj);
    da = fp->dat_attrs;

    if (fp->cmd_vars[0] == 1) {
        fp->cmd_vars[0] = 2;
        ftColl_CreateReflectHit(gobj, &da->specialn_zd_reflectdesc,
                                fn_80105FEC);
    }

    var1 = 0;
    zero = var1;
    var0 = var1;
    if (fp->cmd_vars[var0] == 0) {
        fp->reflecting = zero;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_ZdSpecialAirN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp;
    ftKb_DatAttrs* da;

    fp = GET_FIGHTER(gobj);
    da = fp->dat_attrs;

    if (fp->cmd_vars[0] == 1U) {
        fp->cmd_vars[0] = 2U;
        ftColl_CreateReflectHit(gobj, &da->specialn_zd_reflectdesc,
                                fn_80105FEC);
    }

    if (fp->cmd_vars[0] == 0) {
        fp->reflecting = false;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_ZdSpecialN_IASA(Fighter_GObj* gobj) {}

void ftKb_ZdSpecialAirN_IASA(Fighter_GObj* gobj) {}

void ftKb_ZdSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEF8(gobj);
}

void ftKb_ZdSpecialAirN_Phys(Fighter_GObj* gobj)
{
    int new_var;
    Fighter* fp = GET_FIGHTER(gobj);

    {
        s32 var1 = fp->mv.zd.specialn.x0;
        ftCo_DatAttrs* co_attrs = &fp->co_attrs;
        ftKb_DatAttrs* da = fp->dat_attrs;

        if (var1 != 0) {
            new_var = var1 - 1;
            fp->mv.zd.specialn.x0 = new_var;
        } else {
            ftCommon_Fall(fp, da->specialn_zd_fall_acceleration,
                          co_attrs->terminal_vel);
        }
    }

    ftCommon_8007CF58(fp);
    ftColl_8007AEF8(gobj);
}

void ftKb_ZdSpecialN_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        ftKb_SpecialNSk_80105E8C(gobj);
    }
}

void ftKb_ZdSpecialAirN_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftKb_SpecialNSk_80105F3C(gobj);
    }
}

void ftKb_SpecialNSk_80105E8C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_ZdSpecialAirN, 0x0C4C508E,
                              fp->cur_anim_frame, 1.0F, 0.0F, NULL);
    fp = GET_FIGHTER(gobj);
    da = fp->dat_attrs;
    if (fp->x2219_b0 == true) {
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
    }
    if (fp->cmd_vars[0] == 2U) {
        ftColl_CreateReflectHit(gobj, &da->specialn_zd_reflectdesc,
                                fn_80105FEC);
    }
}

void ftKb_SpecialNSk_80105F3C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_ZdSpecialN, 0x0C4C508E,
                              fp->cur_anim_frame, 1.0F, 0.0F, NULL);
    fp = GET_FIGHTER(gobj);
    da = fp->dat_attrs;
    if (fp->x2219_b0 == true) {
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
    }
    if (fp->cmd_vars[0] == 2U) {
        ftColl_CreateReflectHit(gobj, &da->specialn_zd_reflectdesc,
                                fn_80105FEC);
    }
}

bool ftKb_SpecialNSk_80105FF0(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (gobj != NULL) {
        if (ft->fv.kb.xB8 != 0) {
            return false;
        }
        return true;
    }
    return true;
}

s32 ftKb_SpecialNSk_80106020(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (gobj != NULL) {
        return ft->fv.kb.xB4;
    }
    return 0;
}

/// #ftKb_SpecialNSk_8010603C

void ftKb_SpecialNSk_8010612C(Fighter_GObj* gobj)
{
    int new_var;
    int new_var2;
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialNStart, 0, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->throw_flags_b0 = false;
    new_var2 = 3;
    new_var = 0;
    fp->cmd_vars[new_var2] = new_var;
    fp->cmd_vars[2] = new_var;
    fp->cmd_vars[1] = new_var;
    fp->cmd_vars[new_var] = new_var;
    fp->mv.kb.specialhi.x0 = 0;
    if (fp->fv.kb.xB4 == new_var) {
        fp->fv.kb.xB4 = 1;
    }
    fp->mv.kb.specialhi.x4 = 0;
    fp->mv.kb.specialhi.x8.i = 0;
    fp = GET_FIGHTER(gobj);
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
    ftAnim_8006EBA4(gobj);
}

void ftKb_SpecialNSk_801061E4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int new_var2;
    int new_var;
    Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialAirNStart, 0, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->throw_flags_b0 = false;
    new_var2 = 0;
    fp->cmd_vars[3] = new_var2;
    fp->cmd_vars[2] = 0;
    new_var = 0;
    fp->cmd_vars[1] = new_var;
    fp->cmd_vars[0] = 0;
    fp->mv.kb.specialhi.x0 = 0;
    if (fp->fv.kb.xB4 == 0) {
        fp->fv.kb.xB4 = 1;
    }
    fp->mv.kb.specialhi.x4 = 0;
    fp->mv.kb.specialhi.x8.i = 0;
    fp = GET_FIGHTER(gobj);
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
    ftAnim_8006EBA4(gobj);
}

void ftKb_SkSpecialNStart_Anim(Fighter_GObj* gobj)
{
    /// FAKE MATCH: comma operator required for regalloc
    Fighter* fp = (0, GET_FIGHTER(gobj));
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.kb.xB8 =
            it_802B19AC(gobj, &fp->cur_pos, 39, 153, fp->facing_dir);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialNLoop, 0, 0, 1, 0,
                                  NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SkSpecialNLoop_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* new_var = fp;
    switch (fp->mv.kb.specialhi.x8.i) {
    case 0:
        ft_PlaySFX(new_var, 270134, 127, 64);
        break;
    }
    ++fp->mv.kb.specialhi.x8.i;
    if (fp->cur_anim_frame == 0) {
        ++fp->fv.kb.xB4;
        fp->mv.kb.specialhi.x8.i = 0;
        if (fp->fv.kb.xB4 > 6) {
            fp->fv.kb.xB4 = 6;
            fp->mv.kb.specialhi.x8.i = 100;
            ftCo_800BFFD0(fp, 87, 0);
        }
    }
}

void ftKb_SkSpecialNCancel_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.kb.xB8 = 0;
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

/// #ftKb_SkSpecialNEnd_Anim

void ftKb_SkSpecialAirNStart_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_GObj* new_var;
    Fighter_GObj* new_var2;
    new_var = gobj;
    if (!ftAnim_IsFramesRemaining(new_var)) {
        if (new_var) {
        }
        fp->fv.kb.xB8 =
            it_802B19AC(new_var, &fp->cur_pos, 39, 153, fp->facing_dir);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialAirNLoop, 0, 0, 1, 0,
                                  NULL);
        new_var2 = gobj;
        ftKirbyDmgInline(new_var2);
    }
}

void ftKb_SkSpecialAirNLoop_Anim(Fighter_GObj* gobj)
{
    volatile unsigned char pad;
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* new_var;
    switch (fp->mv.kb.specialhi.x8.i) {
    case 0:
        ft_PlaySFX(fp, 270134, 127, 64);
        break;
    }
    ++fp->mv.kb.specialhi.x8.i;
    if (fp->cur_anim_frame == 0) {
        new_var = fp;
        ++fp->fv.kb.xB4;
        fp->mv.kb.specialhi.x8.i = 0;
        if (fp->fv.kb.xB4 > 6) {
            new_var->fv.kb.xB4 = 6;
            new_var->mv.kb.specialhi.x8.i = 100;
            ftCo_800BFFD0(fp, 87, 0);
        }
    }
}

void ftKb_SkSpecialAirNCancel_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    /// FAKE MATCH: comma operator required for regalloc
    ftKb_DatAttrs* da = (0, fp->dat_attrs);
    ftKb_DatAttrs* new_var;
    new_var = da;
    fp->fv.kb.xB8 = 0;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (new_var->specialn_sk_freefall_toggle == 0.0F) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1.0F,
                          da->specialn_sk_freefall_toggle);
        }
    }
}

/// #ftKb_SkSpecialAirNEnd_Anim

void ftKb_SkSpecialNStart_IASA(Fighter_GObj* gobj) {}

/// #ftKb_SkSpecialNLoop_IASA

void ftKb_SkSpecialNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_SkSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_SkSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

/// #ftKb_SkSpecialAirNLoop_IASA

void ftKb_SkSpecialAirNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_SkSpecialAirNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_SkSpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SkSpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SkSpecialNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SkSpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SkSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SkSpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SkSpecialAirNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SkSpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SkSpecialNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialAirNStart,
                                  0x0C4C5080U, fp->cur_anim_frame, 1.0f, 0.0f,
                                  NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SkSpecialNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialAirNLoop, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SkSpecialNCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (ft_80082708(gobj) == GA_Ground) {
        if (da->specialn_sk_freefall_toggle == 0.0F) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 0.0F,
                          da->specialn_sk_freefall_toggle);
        }
    }
}

void ftKb_SkSpecialNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (ft_80082708(gobj) == GA_Ground) {
        fp->fv.kb.xB4 = 0;
        fp->mv.kb.specialhi.x4 = 0;
        if (da->specialn_sk_freefall_toggle == 0.0F) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 0.0F,
                          da->specialn_sk_freefall_toggle);
        }
    }
}

void ftKb_SkSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) != GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialNStart, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SkSpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) != GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialNLoop, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SkSpecialAirNCancel_Coll(Fighter_GObj* gobj)
{
    FORCE_PAD_STACK_16;

    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCo_Landing_Enter_Basic(gobj);
    }
}

void ftKb_SkSpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (ft_80081D0C(gobj)) {
        fp->fv.kb.xB4 = 0;
        fp->mv.kb.specialhi.x4 = 0;
        ftKb_SpecialNSk_80105E8C(gobj);
    }
}

/// @brief Returns Mewtwo copy charge info if active.
/// @param gobj Fighter game object
/// @param out_charge Output: current charge value
/// @param out_max Output: max charge time (integer)
/// @return 0 if valid, -1 if invalid/inactive
int ftKb_SpecialNMt_80106F44(Fighter_GObj* gobj, int* out_charge, int* out_max)
{
    Vec2 unused;
    Fighter* fp;
    ftKb_DatAttrs* da;
    if (gobj == NULL) {
        goto null_return;
    }
    fp = GET_FIGHTER(gobj);
    da = fp->dat_attrs;
    if (fp->fv.kb.x98 == 0) {
        return -1;
    }
    *out_charge = fp->fv.kb.x9C;
    *out_max = da->specialn_mt_charge_time;
    return 0;
null_return:
    return -1;
}

/// #ftKb_SpecialNMt_80106F9C

/// #ftKb_SpecialNMt_80106FEC

/// @brief Clears Mewtwo copy ability state and effects.
void ftKb_SpecialNMt_80107040(Fighter_GObj* gobj)
{
    Vec2 unused;
    Fighter* fp;
    if (gobj == NULL) {
        return;
    }
    fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.x98 != 0) {
        fp->fv.kb.x98 = 0;
    }
    if (gobj == NULL) {
        return;
    }
    fp = GET_FIGHTER(gobj);
    efLib_DestroyAll(gobj);
    fp->fv.kb.xA0 = 0;
}

/// @brief Full cleanup of Mewtwo copy ability state.
void ftKb_SpecialNMt_8010709C(Fighter_GObj* gobj)
{
    Vec3 unused;
    s32 unused2;
    Fighter* fp;
    Fighter* fp2;
    if (gobj == NULL) {
        return;
    }
    fp2 = fp = GET_FIGHTER(gobj);
    if (gobj == NULL) {
        goto skip;
    }
    if (fp->fv.kb.x98 != 0) {
        it_802C573C(fp->fv.kb.x98);
        fp->fv.kb.x98 = 0;
    }
    if (gobj == NULL) {
        goto skip;
    }
    fp = GET_FIGHTER(gobj);
    efLib_DestroyAll(gobj);
    fp->fv.kb.xA0 = 0;
skip:
    fp2->fv.kb.x9C = 0;
    ftCo_800BFFAC(fp2);
    efLib_DestroyAll(gobj);
}

/// @brief Mewtwo copy cleanup with charge check.
void ftKb_SpecialNMt_80107130(Fighter_GObj* gobj)
{
    Vec3 unused;
    s32 unused2;
    Vec2 unused3;
    Fighter* fp;
    Fighter* fp2;
    ftKb_DatAttrs* da;
    if (gobj == NULL) {
        return;
    }
    fp = GET_FIGHTER(gobj);
    da = fp->dat_attrs;
    fp2 = fp;
    if (gobj == NULL) {
        goto check;
    }
    if (fp->fv.kb.x98 != 0) {
        it_802C573C(fp->fv.kb.x98);
        fp->fv.kb.x98 = 0;
    }
    if (gobj == NULL) {
        goto check;
    }
    fp = GET_FIGHTER(gobj);
    efLib_DestroyAll(gobj);
    fp->fv.kb.xA0 = 0;
check:
    if ((float) fp2->fv.kb.x9C == da->specialn_mt_charge_time) {
        return;
    }
    fp2->fv.kb.x9C = 0;
    ftCo_800BFFAC(fp2);
    efLib_DestroyAll(gobj);
}

/// #ftKb_SpecialNMt_801071FC

/// #ftKb_SpecialNMt_80107410

/// #ftKb_SpecialNMt_80107568

void ftKb_SpecialNMt_80107638(Fighter_GObj* gobj)
{
    s32 timer;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialAirNStart, 0, 0.0F, 1.0F,
                              0.0F, NULL);
    timer = 0;
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp = GET_FIGHTER(gobj);
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
    fp->mv.kb.specialhi.x0 = 0;
    fp->mv.kb.specialhi.x4 = 0;
    if (fp->fv.kb.x9C == 0) {
        timer = da->specialn_mt_frames_to_transition;
    }
    fp->mv.kb.specialhi.xC = timer;
    fp->mv.kb.specialhi.x10.f = 0.0F;
    fp->self_vel.y *= 0.5F;
    ftAnim_8006EBA4(gobj);
}

/// #ftKb_MtSpecialNStart_Anim

/// #ftKb_MtSpecialNLoop_Anim

void ftKb_MtSpecialNLoopFull_Anim(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = ft->dat_attrs;
    PAD_STACK(4);
    ft->mv.kb.specialhi.x8.i = 1;
    ft->fv.kb.x9C = da->specialn_mt_charge_time;
}

void ftKb_MtSpecialNCancel_Anim(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->fv.kb.x98 != 0) {
            it_802C573C(fp->fv.kb.x98);
            fp->fv.kb.x98 = 0;
        }
        if (gobj != NULL) {
            Fighter* fp2 = GET_FIGHTER(gobj);
            efLib_DestroyAll(gobj);
            fp2->fv.kb.xA0 = 0;
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_MtSpecialNEnd_Anim(Fighter_GObj* gobj)
{
    u8 _[24];

    ftKb_SpecialNMt_801071FC(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

/// #ftKb_MtSpecialAirNStart_Anim

/// #ftKb_MtSpecialAirNLoop_Anim

void ftKb_MtSpecialAirNLoopFull_Anim(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = ft->dat_attrs;
    PAD_STACK(4);
    ft->mv.kb.specialhi.x8.i = 0;
    ft->fv.kb.x9C = da->specialn_mt_charge_time;
}

void ftKb_MtSpecialAirNCancel_Anim(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->fv.kb.x98 != 0) {
            it_802C573C(fp->fv.kb.x98);
            fp->fv.kb.x98 = 0;
        }
        if (gobj != NULL) {
            Fighter* fp2 = GET_FIGHTER(gobj);
            efLib_DestroyAll(gobj);
            fp2->fv.kb.xA0 = 0;
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_MtSpecialAirNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    ftKb_SpecialNMt_801071FC(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (da->specialn_mt_freefall_toggle == 0.0F) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 0, 1, 1.0F, da->specialn_mt_freefall_toggle);
    }
}

void ftKb_MtSpecialNStart_IASA(Fighter_GObj* gobj) {}

/// #ftKb_MtSpecialNLoop_IASA

/// #ftKb_MtSpecialNLoopFull_IASA

void ftKb_MtSpecialNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_MtSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_MtSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

/// #ftKb_MtSpecialAirNLoop_IASA

/// #ftKb_MtSpecialAirNLoopFull_IASA

void ftKb_MtSpecialAirNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_MtSpecialAirNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_MtSpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_MtSpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_MtSpecialNLoopFull_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_MtSpecialNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_MtSpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_MtSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_MtSpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_MtSpecialAirNLoopFull_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_MtSpecialAirNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_MtSpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_MtSpecialNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialAirNStart,
                                  0x0C4C5080U, fp->cur_anim_frame, 1.0f, 0.0f,
                                  NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialAirNLoop, 0x0C4C5280U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialNLoopFull_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialAirNLoopFull,
                                  0x0C4C5280U, fp->cur_anim_frame, 1.0f, 0.0f,
                                  NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialNCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialAirNCancel,
                                  0x0C4C5080U, fp->cur_anim_frame, 1.0f, 0.0f,
                                  NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialAirNEnd, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Air) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialNStart, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Air) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialNLoop, 0x0C4C5280U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialAirNLoopFull_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Air) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialNLoopFull,
                                  0x0C4C5280U, fp->cur_anim_frame, 1.0f, 0.0f,
                                  NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialAirNCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Air) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialNCancel, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Air) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialNEnd, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SpecialNIc_80108CE8(Fighter_GObj* gobj, Item_GObj* it_gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (it_gobj == ft->fv.kb.xC0) {
        ft->fv.kb.xC0 = NULL;
    }
}

void ftKb_SpecialNIc_80108D04(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (fp->fv.kb.xC0 != NULL) {
        it_802C17DC(fp->fv.kb.xC0);
        {
            Fighter* fp2 = GET_FIGHTER(gobj);
            if (fp->fv.kb.xC0 == fp2->fv.kb.xC0) {
                fp2->fv.kb.xC0 = NULL;
            }
        }
    }
}

void ftKb_SpecialNIc_80108D64(Fighter_GObj* gobj)
{
    int new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    new_var = 0;
    fp->throw_flags = 0;
    fp->cmd_vars[0] = new_var;
    ((Fighter*) fp)->fv.kb.xC0 = NULL;
    Fighter_ChangeMotionState(gobj, ftKb_MS_PpSpecialN, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = fn_801090D4;
    {
        Fighter* fp2 = GET_FIGHTER(gobj);
        ftCommon_SetAccessory(
            fp2,
            (HSD_Joint*) (&ft_80459B88)->hats[FTKIND_PEACH]->hat_dynamics[1]);
        lb_8000C2F8(
            fp2->x20A0_accessory,
            fp2->parts[ftParts_GetBoneIndex(fp2, FtPart_LThumbNb)].joint);
    }
}

void ftKb_SpecialNIc_80108E14(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->throw_flags = 0;
    fp->cmd_vars[0] = 0;
    fp->fv.kb.xC0 = NULL;
    if ((s32) fp->fv.kb.xC4 == 0) {
        fp->self_vel.y = ((ftKb_DatAttrs*) fp->dat_attrs)
                             ->specialn_pp_air_vertical_momentum;
        fp->fv.kb.xC4 = true;
        fp->fv.kb.xC8 = 0.0F;
    } else {
        fp->fv.kb.xC8 = -10.0F;
    }
    Fighter_ChangeMotionState(gobj, ftKb_MS_PpSpecialAirN, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = fn_801090D4;
    {
        Fighter* fp2 = GET_FIGHTER(gobj);
        ftCommon_SetAccessory(
            fp2, (HSD_Joint*) ft_80459B88.hats[FTKIND_PEACH]->hat_dynamics[1]);
        lb_8000C2F8(
            fp2->x20A0_accessory,
            fp2->parts[ftParts_GetBoneIndex(fp2, FtPart_LThumbNb)].joint);
    }
}

void ftKb_PpSpecialN_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_PpSpecialAirN_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_PpSpecialN_IASA(Fighter_GObj* gobj) {}

void ftKb_PpSpecialAirN_IASA(Fighter_GObj* gobj) {}

void ftKb_PpSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_PpSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_PpSpecialN_Coll(Fighter_GObj* gobj)
{
    void* new_var;
    void* new_var2;
    if (!ft_800827A0(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->fv.kb.xC0 != NULL) {
            it_802C17DC(fp->fv.kb.xC0);
            {
                Fighter* fp2 = GET_FIGHTER(gobj);
                if (fp->fv.kb.xC0 == fp2->fv.kb.xC0) {
                    new_var2 = NULL;
                    new_var = new_var2;
                    fp2->fv.kb.xC0 = new_var;
                }
            }
        }
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_PpSpecialAirN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (ft_80081D0C(gobj) != GA_Ground) {
        Fighter* fp1 = GET_FIGHTER(gobj);
        if (fp1->fv.kb.xC0 != NULL) {
            it_802C17DC(fp1->fv.kb.xC0);
            {
                Fighter* fp2 = GET_FIGHTER(gobj);
                if (fp1->fv.kb.xC0 == fp2->fv.kb.xC0) {
                    fp2->fv.kb.xC0 = NULL;
                }
            }
        }
        fp->fv.kb.xC4 = 0;
        fp->fv.kb.xC8 = 0.0F;
        ftCo_LandingFallSpecial_Enter(gobj, false,
                                      da->specialn_pp_landing_lag);
    }
}

/// #fn_801090D4

Fighter_Part ftKb_SpecialNYs_80109238(Fighter_GObj* gobj)
{
    return ftParts_GetBoneIndex(GET_FIGHTER(gobj), FtPart_TransN2);
}

void ftKb_SpecialNYs_80109260(Fighter_GObj* gobj, Vec3* vec)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = ft->dat_attrs;
    vec->x = -ft->facing_dir * da->specialn_ys_initial_horizontal_momentum;
    vec->y = da->specialn_ys_initial_vertical_momentum;
    vec->z = 0.0f;
}
