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
#include "it/items/itnesspkflash.h"
#include "it/items/itpeachtoad.h"
#include "it/items/itpeachtoadspore.h"
#include "it/items/itpikachutjoltground.h"
#include "it/items/itsamuschargeshot.h"
#include "it/items/itseakneedleheld.h"
#include "it/items/itseakneedlethrown.h"
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

extern f32 ftKb_Init_804D9558;
extern Vec3 const ftKb_Init_803B7570;
extern Vec3 const ftKb_Init_803B757C;
extern float ftKb_Init_803CB770[];

/// Forward declarations for functions called before definition
void fn_80105AB0(Fighter_GObj*);
void fn_80105A34(Fighter_GObj*);
void fn_80106DB0(Fighter_GObj*);
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
    volatile unsigned int pad;
    ftKb_DatAttrs* da;
    int new_var;
    fp = (Fighter*) HSD_GObjGetUserData(gobj);
    da = fp->dat_attrs;
    new_var = 0;
    if (fp->cmd_vars[new_var] == 1U) {
        fp->cmd_vars[0] = 2U;
        ftColl_CreateReflectHit(gobj, &da->specialn_zd_reflectdesc,
                                fn_80105FEC);
    }
    if (fp->cmd_vars[0] == ((0, 0))) {
        fp->reflecting = new_var;
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
    void* new_var; // Permuter slop
    PAD_STACK(8);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_ZdSpecialAirN, 0x0C4C508E,
                              fp->cur_anim_frame, 1.0F, 0.0F, NULL);
    fp = (Fighter*) (new_var = HSD_GObjGetUserData(gobj));
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
    void* new_var; // Permuter slop
    PAD_STACK(8);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_ZdSpecialN, 0x0C4C508E,
                              fp->cur_anim_frame, 1.0F, 0.0F, NULL);
    fp = (Fighter*) (new_var = HSD_GObjGetUserData(gobj));
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

void fn_80105FEC(Fighter_GObj* gobj) {}

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

void ftKb_SpecialNSk_8010603C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;

    if (fp->fv.kb.xB8 != NULL) {
        fp->fv.kb.xB8 = NULL;

        while (fp->fv.kb.xB4 != 0) {
            Vec3 pos = fp->cur_pos;
            PAD_STACK(4);
            {
                f32 y_offset;
                if (fp->ground_or_air == GA_Ground) {
                    y_offset = da->specialn_sk_graphic_y_offset_ground;
                } else {
                    y_offset = da->specialn_sk_graphic_y_offset_air;
                }
                pos.y += fp->x34_scale.y * y_offset;
            }
            pos.z = 0.0f;
            {
                Item_GObj* needle =
                    it_802AFD8C(gobj, &pos, 0x98, fp->facing_dir);
                if (needle != NULL) {
                    it_802AFEA8(needle, gobj, 1);
                }
            }
            fp->fv.kb.xB4 -= 1;
        }
    }

    fp->fv.kb.xB4 = 0;
}

static inline void ftKb_SpecialN_set_cbs(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
}

void ftKb_SpecialNSk_8010612C(Fighter_GObj* gobj)
{
    int new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialNStart, 0, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->throw_flags_b0 = false;
    new_var = 0;
    fp->cmd_vars[3] = new_var;
    fp->cmd_vars[2] = new_var;
    fp->cmd_vars[1] = new_var;
    fp->cmd_vars[new_var] = new_var;
    fp->mv.kb.specialhi.x0 = 0;
    if (fp->fv.kb.xB4 == new_var) {
        fp->fv.kb.xB4 = 1;
    }
    fp->mv.kb.specialhi.x4 = 0;
    fp->mv.kb.specialhi.x8.i = 0;
    ftKb_SpecialN_set_cbs(gobj);
    ftAnim_8006EBA4(gobj);
}

void ftKb_SpecialNSk_801061E4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int new_var2;
    int new_var;
    Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialAirNStart, 0, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->throw_flags_b0 = (new_var2 = 0);
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
    ftKb_SpecialN_set_cbs(gobj);
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
    switch (fp->mv.kb.specialhi.x8.i) {
    case 0: {
        Fighter* fp = GET_FIGHTER(gobj);
        ft_PlaySFX(fp, 270134, 127, 64);
    }
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

void ftKb_SkSpecialNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4 * 8);
    switch (fp->mv.kb.specialhi.x0) {
    case 2:
    case 5:
    case 8:
    case 11:
    case 14:
    case 17:
        fp->mv.kb.specialhi.x4 = 1;
        fp->fv.kb.xB8 = 0;
    }
    ++fp->mv.kb.specialhi.x0;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

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
    Fighter* fp = GET_FIGHTER(gobj);
    switch (fp->mv.kb.specialhi.x8.i) {
    case 0: {
        Fighter* fp = GET_FIGHTER(gobj);
        ft_PlaySFX(fp, 270134, 127, 64);
    }
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

void ftKb_SkSpecialAirNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4 * 8);
    switch (fp->mv.kb.specialhi.x0) {
    case 2:
    case 5:
    case 8:
    case 11:
    case 14:
    case 17:
        fp->mv.kb.specialhi.x4 = 1;
        fp->fv.kb.xB8 = NULL;
    }
    ++fp->mv.kb.specialhi.x0;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (da->specialn_sk_freefall_toggle == 0.0F) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1.0F,
                          da->specialn_sk_freefall_toggle);
        }
    }
}

void ftKb_SkSpecialNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_SkSpecialNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->mv.kb.specialhi.x0 = 0;
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialNEnd, Ft_MF_None,
                                  0.0F, 1.0F, 0.0F, NULL);
        ftKirbyDmgInline(gobj);
        fp->accessory4_cb = fn_80106DB0;
    } else if (fp->input.x668 & HSD_PAD_LR) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialNCancel, Ft_MF_None,
                                  0.0F, 1.0F, 0.0F, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SkSpecialNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_SkSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_SkSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_SkSpecialAirNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->mv.kb.specialhi.x0 = 0;
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialAirNEnd, Ft_MF_None,
                                  0, 1, 0, NULL);
        ftKirbyDmgInline(gobj);
        fp->accessory4_cb = fn_80106DB0;
    } else if (fp->input.x668 & HSD_PAD_LR) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialAirNCancel,
                                  Ft_MF_None, 0, 1, 0, NULL);
        ftKirbyDmgInline(gobj);
    }
}

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
    PAD_STACK(8);
    if (ft_80082708(gobj) == GA_Ground) {
        if (da->specialn_sk_freefall_toggle == 0.0F) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1.0F,
                          da->specialn_sk_freefall_toggle);
        }
    }
}

void ftKb_SkSpecialNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(16);
    if (ft_80082708(gobj) == GA_Ground) {
        fp->fv.kb.xB4 = 0;
        fp->mv.kb.specialhi.x4 = 0;
        if (da->specialn_sk_freefall_toggle == 0.0F) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1.0F,
                          da->specialn_sk_freefall_toggle);
        }
    }
}

void ftKb_SkSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialNStart, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SkSpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
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
        ftCo_Landing_Enter_Basic(gobj);
    }
}

// permuter-generated helper, almost certainly fake
static inline s32 perm_randi(int n)
{
    return HSD_Randi(n);
}

void fn_80106DB0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;

    if (fp->mv.kb.specialhi.x4 != 0) {
        fp->mv.kb.specialhi.x4 = 0;
        if (fp->fv.kb.xB4 > 0) {
            Vec3 pos = fp->cur_pos;
            PAD_STACK(4);
            if (fp->ground_or_air == GA_Ground) {
                pos.x +=
                    fp->x34_scale.y *
                    (da->specialn_sk_graphic_x_offset_ground * fp->facing_dir);
                pos.y += fp->x34_scale.y *
                         (da->specialn_sk_graphic_y_offset_ground +
                          ftKb_Init_803CB770[perm_randi(9)]);
            } else {
                pos.x +=
                    fp->x34_scale.y *
                    (da->specialn_sk_graphic_x_offset_air * fp->facing_dir);
                pos.y += fp->x34_scale.y *
                         (2.0f * ftKb_Init_803CB770[perm_randi(9)] +
                          da->specialn_sk_graphic_y_offset_air);
            }
            pos.z = 0.0f;
            {
                Item_GObj* needle =
                    it_802AFD8C(gobj, &pos, 0x98, fp->facing_dir);
                if (needle != NULL) {
                    it_802AFEA8(needle, gobj, 0);
                }
            }
            fp->fv.kb.xB4 -= 1;
            efSync_Spawn(0x503, gobj, &pos);
            ft_PlaySFX(fp, 0x41F3C, 127, 64);
        }
    }
}

/// @brief Returns Mewtwo copy charge info if active.
/// @param gobj Fighter game object
/// @param out_charge Output: current charge value
/// @param out_max Output: max charge time (integer)
/// @return 0 if valid, -1 if invalid/inactive
s32 ftKb_SpecialNMt_80106F44(Fighter_GObj* gobj, s32* out_charge, s32* out_max)
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

bool ftKb_SpecialNMt_80106F9C(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = gobj->user_data;
        s32 msid = fp->motion_id;

        switch (msid) {
        case ftKb_MS_MtSpecialNStart:
        case ftKb_MS_MtSpecialNLoop:
        case ftKb_MS_MtSpecialNLoopFull:
        case ftKb_MS_MtSpecialNCancel:
        case ftKb_MS_MtSpecialNEnd:
        case ftKb_MS_MtSpecialAirNStart:
        case ftKb_MS_MtSpecialAirNLoop:
        case ftKb_MS_MtSpecialAirNLoopFull:
        case ftKb_MS_MtSpecialAirNCancel:
        case ftKb_MS_MtSpecialAirNEnd:
            if (fp->x2070.x2071_b6) {
                return true;
            }
            return false;
        }
        return true;
    }
    return true;
}

bool ftKb_SpecialNMt_80106FEC(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = gobj->user_data;
        switch (fp->motion_id) {
        case ftKb_MS_MtSpecialNStart:
        case ftKb_MS_MtSpecialNLoop:
        case ftKb_MS_MtSpecialNLoopFull:
        case ftKb_MS_MtSpecialNEnd:
        case ftKb_MS_MtSpecialAirNStart:
        case ftKb_MS_MtSpecialAirNLoop:
        case ftKb_MS_MtSpecialAirNLoopFull:
        case ftKb_MS_MtSpecialAirNEnd:
            return false;
        default:
            return true;
        }
    }
    return true;
}

/// @brief Clears Mewtwo copy ability state and effects.
void ftKb_SpecialNMt_80107040(Fighter_GObj* gobj)
{
    Fighter* fp;

    if (gobj == NULL) {
        return;
    }

    fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.x98 != NULL) {
        fp->fv.kb.x98 = NULL;
    }

    if (gobj == NULL) {
        return;
    }

    fp = GET_FIGHTER(gobj);
    efLib_DestroyAll(gobj);
    fp->fv.kb.xA0 = NULL;
}

/// @brief Full cleanup of Mewtwo copy ability state.
void ftKb_SpecialNMt_8010709C(Fighter_GObj* gobj)
{
    Vec3 unused;
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
    if (gobj == (NULL & 0xFFFFFFFFu)) {
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
    fp2->fv.kb.x9C = (unused2 = 0);
    ftCo_800BFFAC(fp2);
    efLib_DestroyAll(gobj);
}

inline void ftKb_SpecialNMt_SetRecoil(Fighter_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = da = fp->dat_attrs;

    if (fp->motion_id == ftKb_MS_MtSpecialAirNEnd ||
        fp->ground_or_air == GA_Air)
    {
        fp->self_vel.x =
            fp->facing_dir *
            (da->specialn_mt_air_horizontal_momentum * fp->fv.kb.x9C);
    }
    if (fp->motion_id == ftKb_MS_MtSpecialNEnd ||
        fp->ground_or_air == GA_Ground)
    {
        fp->gr_vel =
            fp->facing_dir *
            (da->specialn_mt_ground_horizontal_momentum * fp->fv.kb.x9C);
    }
}

void ftKb_SpecialNMt_801071FC(Fighter_GObj* gobj)
{
    f64 _pad1;
    f64 _pad2;
    Vec3 sp38;
    Vec3 sp2C;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(0x10);

    if (fp->cmd_vars[1] == 1 && fp->fv.kb.x98 != NULL) {
        Item_GObj* saved_item;
        f64 launchAngle;

        fp->cmd_vars[1] = 2;
        sp2C.z = 2.0f;
        sp2C.y = 0.0f;
        sp2C.x = 0.0f;
        lb_8000B1CC(fp->parts[FtPart_RHandN].joint, &sp2C, &sp38);
        sp38.z = 0.0f;
        saved_item = fp->item_gobj;

        launchAngle = (fp->facing_dir == 1.0f) ? 0.0f : M_PI;

        it_802C53F0(fp->fv.kb.x98, &sp38, launchAngle, (u32) fp->fv.kb.x9C,
                    da->specialn_mt_charge_time);

        ftKb_SpecialNMt_SetRecoil(gobj);

        fp->fv.kb.x9C = 0;

        ftKb_SpecialNMt_80107040(gobj);

        fp->item_gobj = saved_item;

        if (fp->fv.kb.x9C == da->specialn_mt_charge_time) {
            ft_PlaySFX(fp, 0x30DB6, 0x7F, 0x40);
            return;
        }
        ft_PlaySFX(fp, 0x30DB3, 0x7F, 0x40);
    }
}

extern u32 ftKb_Init_803CB828[];

void ftKb_SpecialNMt_80107410(Fighter_GObj* gobj)
{
    u32* sfx_table = ftKb_Init_803CB828;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);

    if (fp->cmd_vars[2] != 0) {
        s32 charge = fp->fv.kb.x9C;
        f32 chargeRatio;
        f32 prevRatio;

        if (charge != 0) {
            chargeRatio = (f32) charge / da->specialn_mt_charge_time;
        } else {
            chargeRatio = 0.0f;
        }

        prevRatio = fp->mv.kb.specialhi.x10.f;

        if (prevRatio > 0.0f) {
            if (chargeRatio > 0.75f) {
                if (prevRatio <= 0.75f) {
                    fp->mv.kb.specialhi.x10.f = chargeRatio;
                    ft_80088510(fp, sfx_table[3], 0x7F, 0x40);
                    return;
                }
            }
            if (chargeRatio > 0.5f) {
                if (prevRatio <= 0.5f) {
                    fp->mv.kb.specialhi.x10.f = chargeRatio;
                    ft_80088510(fp, sfx_table[2], 0x7F, 0x40);
                    return;
                }
            }
            if (chargeRatio > 0.25f) {
                if (prevRatio <= 0.25f) {
                    fp->mv.kb.specialhi.x10.f = chargeRatio;
                    ft_80088510(fp, sfx_table[1], 0x7F, 0x40);
                    return;
                }
            }
            if (chargeRatio > 0.0f) {
                if (prevRatio <= 0.0f) {
                    fp->mv.kb.specialhi.x10.f = chargeRatio;
                    ft_80088510(fp, sfx_table[0], 0x7F, 0x40);
                }
            }
        } else {
            fp->mv.kb.specialhi.x10.f = 0.0001f;
            ft_80088510(fp, sfx_table[0], 0x7F, 0x40);
        }
    }
}

void ftKb_SpecialNMt_80107568(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;

    Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialNStart, 0, 0.0F, 1.0F,
                              0.0F, NULL);

    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;

    ftCommon_8007D7FC(fp);

    fp->self_vel.y = 0.0F;

    ftKb_SpecialN_set_cbs(gobj);

    fp->mv.kb.specialhi.x0 = 0;
    fp->mv.kb.specialhi.x4 = 0;

    fp->mv.kb.specialhi.xC =
        (fp->fv.kb.x9C == 0) ? da->specialn_mt_frames_to_transition : 0;
    fp->mv.kb.specialhi.x10.f = 0.0F;

    ftAnim_8006EBA4(gobj);
}

void ftKb_SpecialNMt_80107638(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialAirNStart, 0, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;

    ftKb_SpecialN_set_cbs(gobj);
    fp->mv.kb.specialhi.x0 = 0;
    fp->mv.kb.specialhi.x4 = 0;
    fp->mv.kb.specialhi.xC =
        (fp->fv.kb.x9C == 0) ? da->specialn_mt_frames_to_transition : 0;
    fp->mv.kb.specialhi.x10.f = 0.0F;
    fp->self_vel.y *= 0.5F;
    ftAnim_8006EBA4(gobj);
}

void ftKb_MtSpecialNStart_Anim(Fighter_GObj* gobj)
{
    Vec3 sp2C;
    Vec3 sp20;
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = da = fp->dat_attrs;
    HSD_GObj* shadowHeldGObj;

    u8 _[8];

    if (fp->cmd_vars[3] == 1 && fp->fv.kb.x98 == NULL) {
        sp2C.z = 2.0f;
        sp2C.y = 0.0f;
        sp2C.x = 0.0f;
        lb_8000B1CC(fp->parts[FtPart_RHandN].joint, &sp2C, &sp20);
        sp20.z = 0.0f;
        shadowHeldGObj =
            it_802C5000(gobj, &sp20, FtPart_RHandN, 0x90, fp->facing_dir);
        fp->fv.kb.x98 = shadowHeldGObj;
        if (shadowHeldGObj != NULL) {
            ftKirbyDmgInline(gobj);
        } else {
            fp->fv.kb.x98 = NULL;
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->mv.kb.specialhi.x0 == 1 ||
            (f32) fp->fv.kb.x9C == da->specialn_mt_charge_time)
        {
            Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialNEnd, 0, 0.0f,
                                      1.0f, 0.0f, NULL);
        } else {
            Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialNLoop, 0, 0.0f,
                                      1.0f, 0.0f, NULL);
            fp->mv.kb.specialhi.x8.i = 0;
        }
        ftKirbyDmgInline(gobj);
    }
}

static inline void ftKb_SpecialNMt_CreateHeldShadow(Fighter_GObj* gobj,
                                                    Vec3* pos1, Vec3* pos2)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[3] == 1 && fp->fv.kb.x98 == NULL) {
        HSD_GObj* shadowHeldGObj;

        pos1->z = 2.0f;
        pos1->y = 0.0f;
        pos1->x = 0.0f;
        lb_8000B1CC(fp->parts[FtPart_RHandN].joint, pos1, pos2);
        pos2->z = 0.0f;
        shadowHeldGObj =
            it_802C5000(gobj, pos2, FtPart_RHandN, 0x90, fp->facing_dir);
        fp->fv.kb.x98 = shadowHeldGObj;
        if (shadowHeldGObj != NULL) {
            ftKirbyDmgInline(gobj);
        } else {
            fp->fv.kb.x98 = NULL;
        }
    }
}

void ftKb_MtSpecialNLoop_Anim(Fighter_GObj* gobj)
{
    Vec3 sp40;
    Vec3 sp34;
    Vec3 sp28;
    Vec3 sp1C;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4);

    sp34 = ftKb_Init_803B7570;

    fp->mv.kb.specialhi.xC--;
    if (fp->mv.kb.specialhi.xC <= 0) {
        fp->mv.kb.specialhi.xC = 0;
        ftKb_SpecialNMt_CreateHeldShadow(gobj, &sp28, &sp1C);
        ftKb_SpecialNMt_80107410(gobj);
        if (fp->mv.kb.specialhi.x8.i == 0) {
            fp->mv.kb.specialhi.x4++;
            if (fp->mv.kb.specialhi.x4 >
                (s32) da->specialn_mt_loops_to_full_charge)
            {
                fp->mv.kb.specialhi.x4 = 0;
                fp->fv.kb.x9C++;
                if ((f32) fp->fv.kb.x9C >= da->specialn_mt_charge_time) {
                    Fighter_ChangeMotionState(
                        gobj, ftKb_MS_MtSpecialNLoopFull,
                        Ft_MF_SkipMatAnim | Ft_MF_KeepSfx | Ft_MF_UpdateCmd |
                            Ft_MF_SkipItemVis | Ft_MF_Unk19,
                        fp->cur_anim_frame, 1.0f, 0.0f, NULL);
                    fp->fv.kb.x9C = da->specialn_mt_charge_time;
                    fp->mv.kb.specialhi.x8.i = 1;
                    ftCommon_8007EBAC(fp, 0xC, 0);
                    lb_8000B1CC(fp->parts[FtPart_TopN].joint, &sp34, &sp40);
                    efSync_Spawn(0x1B, gobj, &sp40);
                    ftCo_800BFFD0(fp, 0x5D, 0);
                }
            }
        }
    }
}

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
    PAD_STACK(16);
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

void ftKb_MtSpecialAirNStart_Anim(Fighter_GObj* gobj)
{
    Vec3 sp2C;
    Vec3 sp20;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    HSD_GObj* shadowHeldGObj;

    u8 _[8];

    if (fp->cmd_vars[3] == 1 && fp->fv.kb.x98 == NULL) {
        sp2C.z = 2.0f;
        sp2C.y = 0.0f;
        sp2C.x = 0.0f;
        lb_8000B1CC(fp->parts[FtPart_RHandN].joint, &sp2C, &sp20);
        sp20.z = 0.0f;
        shadowHeldGObj =
            it_802C5000(gobj, &sp20, FtPart_RHandN, 0x90, fp->facing_dir);
        fp->fv.kb.x98 = shadowHeldGObj;
        if (shadowHeldGObj != NULL) {
            ftKirbyDmgInline(gobj);
        } else {
            fp->fv.kb.x98 = NULL;
        }
    }
    fp->mv.kb.specialhi.x0 = 0;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->mv.kb.specialhi.x0 == 1 ||
            (f32) fp->fv.kb.x9C == da->specialn_mt_charge_time)
        {
            Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialAirNEnd, 0, 0.0f,
                                      1.0f, 0.0f, NULL);
        } else {
            Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialAirNLoop, 0, 0.0f,
                                      1.0f, 0.0f, NULL);
            fp->mv.kb.specialhi.x8.i = 0;
        }
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialAirNLoop_Anim(Fighter_GObj* gobj)
{
    Vec3 sp40;
    Vec3 sp34;
    Vec3 sp28;
    Vec3 sp1C;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4);

    sp34 = ftKb_Init_803B757C;

    fp->mv.kb.specialhi.xC--;
    if (fp->mv.kb.specialhi.xC <= 0) {
        fp->mv.kb.specialhi.xC = 0;
        ftKb_SpecialNMt_CreateHeldShadow(gobj, &sp28, &sp1C);
        ftKb_SpecialNMt_80107410(gobj);
        if (fp->mv.kb.specialhi.x8.i == 0) {
            fp->mv.kb.specialhi.x4++;
            if (fp->mv.kb.specialhi.x4 >
                (s32) da->specialn_mt_loops_to_full_charge)
            {
                fp->mv.kb.specialhi.x4 = 0;
                fp->fv.kb.x9C++;
                if ((f32) fp->fv.kb.x9C >= da->specialn_mt_charge_time) {
                    Fighter_ChangeMotionState(
                        gobj, ftKb_MS_MtSpecialAirNLoopFull,
                        Ft_MF_SkipMatAnim | Ft_MF_KeepSfx | Ft_MF_UpdateCmd |
                            Ft_MF_SkipItemVis | Ft_MF_Unk19,
                        fp->cur_anim_frame, 1.0f, 0.0f, NULL);
                    fp->fv.kb.x9C = da->specialn_mt_charge_time;
                    fp->mv.kb.specialhi.x8.i = 1;
                    ftCommon_8007EBAC(fp, 0xC, 0);
                    lb_8000B1CC(fp->parts[FtPart_TopN].joint, &sp34, &sp40);
                    efSync_Spawn(0x1B, gobj, &sp40);
                    ftCo_800BFFD0(fp, 0x5D, 0);
                }
            }
        }
    }
}

void ftKb_MtSpecialAirNLoopFull_Anim(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = ft->dat_attrs;
    PAD_STACK(4);
    ft->mv.kb.specialhi.x8.i = 0;
    ft->fv.kb.x9C = da->specialn_mt_charge_time;
}

inline Item_GObj* ftKb_MtSpecialAirNCancel_Anim_inline(Item_GObj* arg0)
{
    return arg0;
}

void ftKb_MtSpecialAirNCancel_Anim(Fighter_GObj* gobj)
{
    int new_var;
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        new_var = ftKb_MtSpecialAirNCancel_Anim_inline(fp->fv.kb.x98) != 0;
        if (new_var) {
            it_802C573C(fp->fv.kb.x98);
            fp->fv.kb.x98 = 0;
        }
        if (gobj != NULL) {
            Fighter* fp2 = fp = GET_FIGHTER(gobj);
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
    PAD_STACK(8);
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

void ftKb_MtSpecialNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(24);

    if (ftCo_8009917C(gobj)) {
        if (gobj != NULL) {
            Fighter* fp2 = GET_FIGHTER(gobj);
            if (fp2->fv.kb.x98 != NULL) {
                it_802C573C(fp2->fv.kb.x98);
                fp2->fv.kb.x98 = NULL;
            }
            if (gobj != NULL) {
                Fighter* fp3 = GET_FIGHTER(gobj);
                efLib_DestroyAll(gobj);
                fp3->fv.kb.xA0 = NULL;
            }
        }
    } else {
        u32 input = fp->input.x668;

        if ((input & HSD_PAD_A) && fp->mv.kb.specialhi.xC <= 0) {
            Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialNEnd, 0, 0.0f,
                                      1.0f, 0.0f, NULL);
            ftKirbyDmgInline(gobj);
            return;
        }
        if (input & HSD_PAD_B) {
            if (fp->mv.kb.specialhi.xC <= 0) {
                Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialNEnd, 0, 0.0f,
                                          1.0f, 0.0f, NULL);
                ftKirbyDmgInline(gobj);
            }
        } else if (input & 0x80000000) {
            Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialNCancel, 0, 0.0f,
                                      1.0f, 0.0f, NULL);
            if (gobj != NULL) {
                Fighter* fp2 = GET_FIGHTER(gobj);
                if (fp2->fv.kb.x98 != NULL) {
                    it_802C573C(fp2->fv.kb.x98);
                    fp2->fv.kb.x98 = NULL;
                }
                if (gobj != NULL) {
                    Fighter* fp3 = GET_FIGHTER(gobj);
                    efLib_DestroyAll(gobj);
                    fp3->fv.kb.xA0 = NULL;
                }
            }
            ftKirbyDmgInline(gobj);
        }
    }
}

void ftKb_MtSpecialNLoopFull_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(24);

    if (ftCo_8009917C(gobj)) {
        if (gobj != NULL) {
            Fighter* fp2 = GET_FIGHTER(gobj);
            if (fp2->fv.kb.x98 != NULL) {
                it_802C573C(fp2->fv.kb.x98);
                fp2->fv.kb.x98 = NULL;
            }
            if (gobj != NULL) {
                Fighter* fp3 = GET_FIGHTER(gobj);
                efLib_DestroyAll(gobj);
                fp3->fv.kb.xA0 = NULL;
            }
        }
    } else {
        u32 input = fp->input.x668;

        if (input & HSD_PAD_A) {
            Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialNEnd, 0, 0.0f,
                                      1.0f, 0.0f, NULL);
            ftKirbyDmgInline(gobj);
            return;
        }
        if (input & HSD_PAD_B) {
            Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialNEnd, 0, 0.0f,
                                      1.0f, 0.0f, NULL);
            ftKirbyDmgInline(gobj);
            return;
        }
        if (input & 0x80000000) {
            Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialNCancel, 0, 0.0f,
                                      1.0f, 0.0f, NULL);
            if (gobj != NULL) {
                Fighter* fp2 = GET_FIGHTER(gobj);
                if (fp2->fv.kb.x98 != NULL) {
                    it_802C573C(fp2->fv.kb.x98);
                    fp2->fv.kb.x98 = NULL;
                }
                if (gobj != NULL) {
                    Fighter* fp3 = GET_FIGHTER(gobj);
                    efLib_DestroyAll(gobj);
                    fp3->fv.kb.xA0 = NULL;
                }
            }
            ftKirbyDmgInline(gobj);
        }
    }
}

void ftKb_MtSpecialNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_MtSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_MtSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_MtSpecialAirNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* fp2;
    u32 input;
    PAD_STACK(16);

    fp2 = fp;
    input = fp->input.x668;

    if ((input & HSD_PAD_A) && fp2->mv.kb.specialhi.xC <= 0) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialAirNEnd, 0, 0.0f,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
        return;
    }
    if (input & HSD_PAD_B) {
        if (fp2->mv.kb.specialhi.xC <= 0) {
            Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialAirNEnd, 0, 0.0f,
                                      1.0f, 0.0f, NULL);
            ftKirbyDmgInline(gobj);
        }
    } else if (input & 0x80000000) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialAirNCancel, 0, 0.0f,
                                  1.0f, 0.0f, NULL);
        if (gobj != NULL) {
            Fighter* fp2 = GET_FIGHTER(gobj);
            if (fp2->fv.kb.x98 != NULL) {
                it_802C573C(fp2->fv.kb.x98);
                fp2->fv.kb.x98 = NULL;
            }
            if (gobj != NULL) {
                Fighter* fp3 = GET_FIGHTER(gobj);
                efLib_DestroyAll(gobj);
                fp3->fv.kb.xA0 = NULL;
            }
        }
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialAirNLoopFull_IASA(Fighter_GObj* gobj)
{
    u32 input = GET_FIGHTER(gobj)->input.x668;
    PAD_STACK(16);

    if (input & HSD_PAD_A) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialAirNEnd, 0, 0.0f,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
        return;
    }
    if (input & HSD_PAD_B) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialAirNEnd, 0, 0.0f,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
        return;
    }
    if (input & 0x80000000) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialAirNCancel, 0, 0.0f,
                                  1.0f, 0.0f, NULL);
        if (gobj != NULL) {
            Fighter* fp2 = GET_FIGHTER(gobj);
            if (fp2->fv.kb.x98 != NULL) {
                it_802C573C(fp2->fv.kb.x98);
                fp2->fv.kb.x98 = NULL;
            }
            if (gobj != NULL) {
                Fighter* fp3 = GET_FIGHTER(gobj);
                efLib_DestroyAll(gobj);
                fp3->fv.kb.xA0 = NULL;
            }
        }
        ftKirbyDmgInline(gobj);
    }
}

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
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialNStart, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialNLoop, 0x0C4C5280U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialAirNLoopFull_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialNLoopFull,
                                  0x0C4C5280U, fp->cur_anim_frame, 1.0f, 0.0f,
                                  NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialAirNCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_MtSpecialNCancel, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
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
    Fighter* fp = HSD_GObjGetUserData(gobj);
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
    ftKb_DatAttrs* da = fp->dat_attrs;
    fp->throw_flags = 0;
    fp->cmd_vars[0] = 0;
    fp->fv.kb.xC0 = NULL;
    if ((s32) fp->fv.kb.xC4 == 0) {
        fp->self_vel.y = da->specialn_pp_air_vertical_momentum;
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
    if (!ft_80082708(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->fv.kb.xC0 != NULL) {
            it_802C17DC(fp->fv.kb.xC0);
            {
                Fighter* fp2 = GET_FIGHTER(gobj);
                if (fp->fv.kb.xC0 == fp2->fv.kb.xC0) {
                    fp2->fv.kb.xC0 = NULL;
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
                if (fp1->fv.kb.xC0 == ((0, fp2->fv.kb.xC0))) {
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

void fn_801090D4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u32 cmd = fp->cmd_vars[0];
    if (cmd == 0) {
        return;
    }
    if (cmd == 1) {
        ftKb_DatAttrs* da = fp->dat_attrs;
        Vec3 pos;
        PAD_STACK(8);
        lb_8000B1CC(fp->parts[0].joint, NULL, &pos);
        pos.x += da->specialn_pp_x_spawn * fp->facing_dir;
        pos.y += da->specialn_pp_y_spawn + fp->fv.kb.xC8;
        fp->fv.kb.xC0 = it_802C1590(gobj, &pos, 0x85, fp->facing_dir);
        ft_PlaySFX(fp, 0x1FBE5, 127, 64);
        if (fp->fv.kb.xC0 != NULL) {
            fp->death2_cb = (HSD_GObjEvent) ftKb_Init_800EE74C;
            fp->take_dmg_cb = (HSD_GObjEvent) ftKb_Init_800EE7B8;
        }
        fp->cmd_vars[0] = 0;
        return;
    }
    if (cmd == 2) {
        if (fp->fv.kb.xC0 != NULL) {
            it_802C16F8(fp->fv.kb.xC0);
            fp->cmd_vars[0] = 0;
            ft_800881D8(fp, 0x2233B, 127, 64);
            ft_PlaySFX(fp, 0x1FBE8, 127, 64);
            {
                Fighter* fp2 = GET_FIGHTER(gobj);
                if (fp->fv.kb.xC0 == fp2->fv.kb.xC0) {
                    fp2->fv.kb.xC0 = NULL;
                }
            }
        }
    }
}

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
    vec->z = ftKb_Init_804D9558;
}
