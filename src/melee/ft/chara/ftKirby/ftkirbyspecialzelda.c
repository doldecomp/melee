#include "ftkirbyspecialzelda.h"

#include <placeholder.h>

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_Throw.h"
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

#include "ftKirby/ftkirbyspecialdonkey.h"

#include <common_structs.h>
#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

extern f32 ftKb_Init_804D9558;
extern float ftKb_Init_803CB770[];

/// Forward declarations for functions called before definition
/* 105AB0 */ static void fn_80105AB0(Fighter_GObj*);
/* 105A34 */ static void fn_80105A34(Fighter_GObj*);
/* 1095DC */ static void fn_801095DC(HSD_GObj*);
/* 109680 */ static void fn_80109680(HSD_GObj*);
/* 109714 */ static void fn_80109714(HSD_GObj*);
/* 1097B8 */ static void fn_801097B8(HSD_GObj*);

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

void fn_80105A34(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!fp->x2219_b0) {
        FighterBone* bone = fp->parts;
        efSync_Spawn(0x4B6, gobj, bone[1].joint);
        fp->x2219_b0 = true;
    }

    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

void fn_80105AB0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_b0) {
        efSync_Spawn(0x4B7, gobj, fp->parts[1].joint);
        fp->x2219_b0 = true;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

void ftKb_SpecialNZd_80105B2C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, ftKb_MS_ZdSpecialN, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    ftKb_SpecialNZd_Helper(gobj);
    fp->accessory4_cb = fn_80105A34;
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
