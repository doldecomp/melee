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

inline void ftKirbyDmgInline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->death2_cb = (void (*)(HSD_GObj*)) ftKb_Init_800EE74C;
    fp->take_dmg_cb = (void (*)(HSD_GObj*)) ftKb_Init_800EE7B8;
}

void ftKb_SpecialNPk_800FA064(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid = ftKb_MS_PkSpecialAirN;
    PAD_STACK(8);
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_PIKACHU:
        break;
    case FTKIND_PICHU:
        msid = ftKb_MS_PcSpecialAirN;
        break;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0F, 1.0F, 0.0F, NULL);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    ftAnim_8006EBA4(gobj);
}

void ftKb_PkSpecialN_Anim(Fighter_GObj* gobj)
{
    Vec3 sp14;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    u8 _[4];

    if (fp->cmd_vars[0] == 1) {
        fp->cmd_vars[0] = 0;

        if (!fp->cmd_vars[1]) {
            fp->cmd_vars[1] = 1;
            switch (fp->fv.kb.hat.kind) {
            case FTKIND_PIKACHU:
                sp14.x =
                    (fp->x34_scale.y * (da->specialn_pk_ground_spawn_offset_x *
                                        fp->facing_dir)) +
                    fp->cur_pos.x;
                sp14.y =
                    (da->specialn_pk_ground_spawn_offset_y * fp->x34_scale.y) +
                    fp->cur_pos.y;
                sp14.z = 0.0F;
                it_802B338C(gobj, &sp14, fp->facing_dir,
                            da->specialn_pk_grounded_item_id);
                ft_PlaySFX(fp, 240076, 127, 64);
                break;
            case FTKIND_PICHU:
                sp14.x =
                    (fp->x34_scale.y * (da->specialn_pc_ground_spawn_offset_x *
                                        fp->facing_dir)) +
                    fp->cur_pos.x;
                sp14.y =
                    (da->specialn_pc_ground_spawn_offset_y * fp->x34_scale.y) +
                    fp->cur_pos.y;
                sp14.z = 0.0F;
                it_802B338C(gobj, &sp14, fp->facing_dir,
                            da->specialn_pc_grounded_item_id);
                ft_PlaySFX(fp, 230067, 127, 64);
                break;
            }
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_PkSpecialAirN_Anim(Fighter_GObj* gobj)
{
    Vec3 sp14;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    float freefall_toggle;

    u8 _[4];

    if (fp->cmd_vars[0] == 1) {
        fp->cmd_vars[0] = 0;

        if (!fp->cmd_vars[1]) {
            fp->cmd_vars[1] = 1;
            switch (fp->fv.kb.hat.kind) {
            case FTKIND_PIKACHU:
                sp14.x =
                    (fp->x34_scale.y *
                     (da->specialn_pk_air_spawn_offset_x * fp->facing_dir)) +
                    fp->cur_pos.x;
                sp14.y =
                    (da->specialn_pk_air_spawn_offset_y * fp->x34_scale.y) +
                    fp->cur_pos.y;
                sp14.z = 0.0F;
                it_802B338C(gobj, &sp14, fp->facing_dir,
                            da->specialn_pk_grounded_item_id);
                ft_PlaySFX(fp, 240076, 127, 64);
                break;
            case FTKIND_PICHU:
                sp14.x =
                    (fp->x34_scale.y *
                     (da->specialn_pc_air_spawn_offset_x * fp->facing_dir)) +
                    fp->cur_pos.x;
                sp14.y =
                    (da->specialn_pc_air_spawn_offset_y * fp->x34_scale.y) +
                    fp->cur_pos.y;
                sp14.z = 0.0F;
                it_802B338C(gobj, &sp14, fp->facing_dir,
                            da->specialn_pc_grounded_item_id);
                ft_PlaySFX(fp, 230067, 127, 64);
                break;
            }
        }
    }

    switch (fp->fv.kb.hat.kind) {
    case FTKIND_PIKACHU:
        freefall_toggle = da->specialn_pk_freefall_toggle;
        break;
    case FTKIND_PICHU:
        freefall_toggle = da->specialn_pc_freefall_toggle;
        break;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (0.0F == freefall_toggle) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 0, 1, 1.0F, freefall_toggle);
    }
}

void ftKb_PkSpecialN_IASA(Fighter_GObj* gobj) {}

void ftKb_PkSpecialAirN_IASA(Fighter_GObj* gobj) {}

void ftKb_PkSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_PkSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

/// #ftKb_PkSpecialN_Coll

/// #ftKb_PkSpecialAirN_Coll

/// #ftKb_SpecialNKp_800FA588

void ftKb_SpecialNKp_800FA7D4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (fp->motion_id >= 449 || fp->motion_id < 443) {
        fp->fv.kb.x84 = fp->fv.kb.x84 + da->specialn_kp_fuel_recharge_rate;
        if (fp->fv.kb.x84 > da->specialn_kp_max_fuel) {
            fp->fv.kb.x84 = da->specialn_kp_max_fuel;
        }
        fp->fv.kb.x88 =
            fp->fv.kb.x88 + da->specialn_kp_flame_size_recharge_rate;
        if (fp->fv.kb.x88 > da->specialn_kp_flame_scale) {
            fp->fv.kb.x88 = da->specialn_kp_flame_scale;
        }
    }
}

int ftKb_SpecialNKp_800FA83C(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL) {
            ftKb_DatAttrs* da = fp->dat_attrs;
            return da->specialn_kp_max_fuel;
        }
    }
    return 1;
}

int ftKb_SpecialNKp_800FA878(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL) {
            ftKb_DatAttrs* da = fp->dat_attrs;
            return da->specialn_kp_flame_scale;
        }
    }
    return 2;
}

void ftKb_SpecialNKp_800FA8B4(Fighter_GObj* gobj)
{
    Fighter* fp;
    s32 msid = ftKb_MS_KpSpecialNStart;
    switch ((s32) GET_FIGHTER(gobj)->fv.kb.hat.kind) {
    case FTKIND_KOOPA:
        break;
    case FTKIND_GKOOPS:
        msid = ftKb_MS_GkSpecialNStart;
        break;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0F, 1.0F, 0.0F, NULL);
    fp = GET_FIGHTER(gobj);
    fp->mv.kb.specialn_kp.x0[0] = 0;
    fp->mv.kb.specialn_kp.x0[1] = Item_8026AE60();
    fp->mv.kb.specialn_kp.x0[2] = -1;
    fp->mv.kb.specialn_kp.x10 = 1;
    fp->mv.kb.specialn_kp.x14 = 0;
    fp->mv.kb.specialn_kp.x18 = 0;
    fp->mv.kb.specialn_kp.x0[3] = 0;
}

void ftKb_SpecialNKp_800FA958(Fighter_GObj* gobj)
{
    Fighter* fp;
    s32 msid = ftKb_MS_KpSpecialAirNStart;
    switch ((s32) GET_FIGHTER(gobj)->fv.kb.hat.kind) {
    case FTKIND_KOOPA:
        break;
    case FTKIND_GKOOPS:
        msid = ftKb_MS_GkSpecialAirNStart;
        break;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0F, 1.0F, 0.0F, NULL);
    fp = GET_FIGHTER(gobj);
    fp->mv.kb.specialn_kp.x0[0] = 0;
    fp->mv.kb.specialn_kp.x0[1] = Item_8026AE60();
    fp->mv.kb.specialn_kp.x0[2] = -1;
    fp->mv.kb.specialn_kp.x10 = 1;
    fp->mv.kb.specialn_kp.x14 = 0;
    fp->mv.kb.specialn_kp.x18 = 0;
    fp->mv.kb.specialn_kp.x0[3] = 0;
}

void ftKb_KpSpecialNStart_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftKirby_MotionState msid = ftKb_MS_KpSpecialN;
        switch (fp->fv.kb.hat.kind) {
        case FTKIND_GKOOPS:
            msid = ftKb_MS_GkSpecialN;
            break;
        case FTKIND_KOOPA:
        default:
            break;
        }
        Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0.0F, 1.0F, 0.0F,
                                  NULL);
    }
}

void ftKb_KpSpecialN_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->cur_anim_frame == 0.0F) {
            fp->mv.kb.specialn_kp.x10 -= 1;
            if (fp->mv.kb.specialn_kp.x10 <= 0) {
                fp->mv.kb.specialn_kp.x10 = 0;
            }
        }
    }
    {
        Fighter* fp = GET_FIGHTER(gobj);
        ftKb_DatAttrs* da = fp->dat_attrs;
        if (fp->mv.kb.specialn_kp.x18 == 0) {
            Camera_80030E44(2, &fp->cur_pos);
        }
        fp->mv.kb.specialn_kp.x18 += 1;
        fp->mv.kb.specialn_kp.x18 %= da->specialn_kp_screen_shake_frequency;
    }
}

void ftKb_KpSpecialNEnd_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_KpSpecialAirNStart_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftKirby_MotionState msid = ftKb_MS_KpSpecialAirN;
        switch (fp->fv.kb.hat.kind) {
        case FTKIND_GKOOPS:
            msid = ftKb_MS_GkSpecialAirN;
            break;
        case FTKIND_KOOPA:
        default:
            break;
        }
        Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0.0F, 1.0F, 0.0F,
                                  NULL);
    }
}

void ftKb_KpSpecialAirN_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->cur_anim_frame == 0.0F) {
            fp->mv.kb.specialn_kp.x10 -= 1;
            if (fp->mv.kb.specialn_kp.x10 <= 0) {
                fp->mv.kb.specialn_kp.x10 = 0;
            }
        }
    }
    {
        Fighter* fp = GET_FIGHTER(gobj);
        ftKb_DatAttrs* da = fp->dat_attrs;
        if (fp->mv.kb.specialn_kp.x18 == 0) {
            Camera_80030E44(2, &fp->cur_pos);
        }
        fp->mv.kb.specialn_kp.x18 += 1;
        fp->mv.kb.specialn_kp.x18 %= da->specialn_kp_screen_shake_frequency;
    }
}

void ftKb_KpSpecialAirNEnd_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_KpSpecialNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_KpSpecialN_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if ((s32) fp->mv.kb.specialn_kp.x0[3] >=
        (s32) da->specialn_kp_b_button_check_frequency)
    {
        if (fp->input.held_inputs & HSD_PAD_B) {
            if ((s32) fp->mv.kb.specialn_kp.x0[0] == 0) {
                ftKb_SpecialNKp_800FA588(gobj);
            }
        } else if ((s32) fp->mv.kb.specialn_kp.x10 != 0) {
            if ((s32) fp->mv.kb.specialn_kp.x0[0] == 0) {
                ftKb_SpecialNKp_800FA588(gobj);
            }
        } else {
            s32 msid = ftKb_MS_KpSpecialNEnd;
            switch ((s32) fp->fv.kb.hat.kind) {
            case FTKIND_KOOPA:
                break;
            case FTKIND_GKOOPS:
                msid = ftKb_MS_GkSpecialNEnd;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0, 0.0F, 1.0F, 0.0F, NULL);
        }
    } else if ((s32) fp->mv.kb.specialn_kp.x0[0] == 0) {
        ftKb_SpecialNKp_800FA588(gobj);
    }
    fp->mv.kb.specialn_kp.x0[0] += 1;
    if ((s32) fp->mv.kb.specialn_kp.x0[0] >= 3) {
        fp->mv.kb.specialn_kp.x0[0] = 0;
    }
    fp->fv.kb.x84 -= 1.0F;
    if (fp->fv.kb.x84 < da->specialn_kp_spew_flame_velocity) {
        fp->fv.kb.x84 = da->specialn_kp_spew_flame_velocity;
    }
    fp->fv.kb.x88 -= 1.0F;
    if (fp->fv.kb.x88 < da->specialn_kp_lowest_charge_graphic_size) {
        fp->fv.kb.x88 = da->specialn_kp_lowest_charge_graphic_size;
    }
    fp->mv.kb.specialn_kp.x0[3] += 1;
    if ((s32) fp->mv.kb.specialn_kp.x0[3] >
        (s32) da->specialn_kp_b_button_check_frequency)
    {
        fp->mv.kb.specialn_kp.x0[3] = da->specialn_kp_b_button_check_frequency;
    }
}

void ftKb_KpSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_KpSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_KpSpecialAirN_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if ((s32) fp->mv.kb.specialn_kp.x0[3] >=
        (s32) da->specialn_kp_b_button_check_frequency)
    {
        if (fp->input.held_inputs & HSD_PAD_B) {
            if ((s32) fp->mv.kb.specialn_kp.x0[0] == 0) {
                ftKb_SpecialNKp_800FA588(gobj);
            }
        } else if ((s32) fp->mv.kb.specialn_kp.x10 != 0) {
            if ((s32) fp->mv.kb.specialn_kp.x0[0] == 0) {
                ftKb_SpecialNKp_800FA588(gobj);
            }
        } else {
            s32 msid = ftKb_MS_KpSpecialAirNEnd;
            switch ((s32) fp->fv.kb.hat.kind) {
            case FTKIND_KOOPA:
                break;
            case FTKIND_GKOOPS:
                msid = ftKb_MS_GkSpecialAirNEnd;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0, 0.0F, 1.0F, 0.0F, NULL);
        }
    } else if ((s32) fp->mv.kb.specialn_kp.x0[0] == 0) {
        ftKb_SpecialNKp_800FA588(gobj);
    }
    fp->mv.kb.specialn_kp.x0[0] += 1;
    if ((s32) fp->mv.kb.specialn_kp.x0[0] >= 3) {
        fp->mv.kb.specialn_kp.x0[0] = 0;
    }
    fp->fv.kb.x84 -= 1.0F;
    if (fp->fv.kb.x84 < da->specialn_kp_spew_flame_velocity) {
        fp->fv.kb.x84 = da->specialn_kp_spew_flame_velocity;
    }
    fp->fv.kb.x88 -= 1.0F;
    if (fp->fv.kb.x88 < da->specialn_kp_lowest_charge_graphic_size) {
        fp->fv.kb.x88 = da->specialn_kp_lowest_charge_graphic_size;
    }
    fp->mv.kb.specialn_kp.x0[3] += 1;
    if ((s32) fp->mv.kb.specialn_kp.x0[3] >
        (s32) da->specialn_kp_b_button_check_frequency)
    {
        fp->mv.kb.specialn_kp.x0[3] = da->specialn_kp_b_button_check_frequency;
    }
}

void ftKb_KpSpecialAirNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_KpSpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_KpSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_KpSpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_KpSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftKb_KpSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftKb_KpSpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

/// #ftKb_KpSpecialNStart_Coll

/// #ftKb_KpSpecialN_Coll

/// #ftKb_KpSpecialNEnd_Coll

/// #ftKb_KpSpecialAirNStart_Coll

/// #ftKb_KpSpecialAirN_Coll

/// #ftKb_KpSpecialAirNEnd_Coll

/// #ftKb_SpecialNLk800FB394

void ftKb_SpecialNLk800FB418(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* ft = GET_FIGHTER(gobj);
        if ((ft != NULL) && (ft->fv.kb.x74 != 0)) {
            ft->fv.kb.x74 = 0;
        }
    }
}

void ftKb_SpecialNLk800FB444(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* ft = GET_FIGHTER(gobj);
        if ((ft != NULL) && (ft->fv.kb.x78 != 0)) {
            ft->fv.kb.x78 = 0;
        }
    }
}

static struct ftLk_SpecialN_Vec3Group const ftKb_SpecialNLk_804D90A0 = { 0 };

static MotionFlags const ftKb_SpecialNLk_mf =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis;

static MotionFlags const ftKb_SpecialNLk_coll_mf =
    Ft_MF_SkipModel | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd |
    Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
    Ft_MF_SkipModelFlags | Ft_MF_Unk27;

static inline void ftKb_SpecialNLk_setCallbacks(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = ftKb_SpecialNLk800FB880;
    fp->death2_cb = ftKb_SpecialNLk800FBA00;
}

static inline void ftKb_SpecialNLk_inlineA2(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 a, b, c;
    a = ftKb_SpecialNLk_804D90A0.a;
    b = ftKb_SpecialNLk_804D90A0.b;
    c = ftKb_SpecialNLk_804D90A0.c;

    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_LThumbNb)].joint,
                NULL, &a);
    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_RThumbNb)].joint,
                NULL, &b);
    lb_8000B1CC(fp->parts->joint, NULL, &c);
    fp->mv.lk.specialn.x8.y = b.x - c.x;
    fp->mv.lk.specialn.x8.z = b.y - c.y;
    fp->mv.lk.specialn.x14 = 0.0F;
    fp->mv.lk.specialn.x8.x = atan2f(b.y - a.y, b.x - a.x);
    if (fp->fv.kb.x74 != 0) {
        it_802A8398((Item_GObj*) fp->fv.kb.x74, &b, &a);
    }
}

static inline float ftKb_SpecialNLk_GetMaxCharge(Fighter* fp)
{
    ftKb_DatAttrs* da = fp->dat_attrs;
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_LINK:
        return da->specialn_lk_max_charge;
    case FTKIND_CLINK:
        return da->specialn_cl_max_charge;
    }
    return 0;
}

static inline float ftKb_SpecialNLk_GetFreefallToggle(Fighter* fp)
{
    ftKb_DatAttrs* da = fp->dat_attrs;
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_LINK:
        return da->specialn_lk_freefall_toggle;
    case FTKIND_CLINK:
        return da->specialn_cl_freefall_toggle;
    }
    return 0;
}

static inline FtMotionId
ftKb_SpecialNLk_GetMsid(Fighter* fp, FtMotionId lk_msid, FtMotionId cl_msid)
{
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_CLINK:
        return cl_msid;
    case FTKIND_LINK:
    default:
        return lk_msid;
    }
}

static inline void ftKb_SpecialNLk_UnsetArrow(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.kb.x74 != 0) {
            fp->fv.kb.x74 = 0;
        }
    }
}

static inline void ftKb_SpecialNLk_UnsetBow(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.kb.x78 != 0) {
            fp->fv.kb.x78 = 0;
        }
    }
}

bool ftKb_SpecialNLk800FB470(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL) {
            switch (fp->fv.kb.hat.kind) {
            case FTKIND_LINK:
                switch (fp->motion_id) {
                case ftKb_MS_LkSpecialNStart:
                case ftKb_MS_LkSpecialNLoop:
                case ftKb_MS_LkSpecialNEnd:
                case ftKb_MS_LkSpecialAirNStart:
                case ftKb_MS_LkSpecialAirNLoop:
                case ftKb_MS_LkSpecialAirNEnd:
                    if (!fp->x2070.x2071_b6) {
                        return false;
                    }
                }
                break;
            case FTKIND_CLINK:
                switch (fp->motion_id) {
                case ftKb_MS_ClSpecialNStart:
                case ftKb_MS_ClSpecialNLoop:
                case ftKb_MS_ClSpecialNEnd:
                case ftKb_MS_ClSpecialAirNStart:
                case ftKb_MS_ClSpecialAirNLoop:
                case ftKb_MS_ClSpecialAirNEnd:
                    if (!fp->x2070.x2071_b6) {
                        return false;
                    }
                }
                break;
            }
        }
    }
    return true;
}

/// #ftKb_SpecialNLk800FB500

/// #ftKb_SpecialNLk800FB5F4

/// #ftKb_SpecialNLk800FB6DC

void ftKb_SpecialNLk800FB800(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (fp->fv.kb.x74 != 0) {
        it_802A8A7C((Item_GObj*) fp->fv.kb.x74);
        fp->fv.kb.x74 = 0;
    }
}

void ftKb_SpecialNLk800FB840(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (fp->fv.kb.x78 != 0) {
        it_802AF304((Item_GObj*) fp->fv.kb.x78);
        fp->fv.kb.x78 = 0;
    }
}

/// #ftKb_SpecialNLk800FB880

/// #ftKb_SpecialNLk800FBA00

/// #ftKb_LkSpecialNStart_Anim

/// #ftKb_LkSpecialNLoop_Anim

void ftKb_LkSpecialNEnd_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftKb_SpecialNLk_UnsetBow(gobj);
        ft_8008A2BC(gobj);
    }
}

/// #ftKb_LkSpecialAirNStart_Anim

/// #ftKb_LkSpecialAirNLoop_Anim

/// #ftKb_LkSpecialAirNEnd_Anim

/// #ftKb_LkSpecialNStart_IASA

/// #ftKb_LkSpecialNLoop_IASA

void ftKb_LkSpecialNEnd_IASA(Fighter_GObj* gobj) {}

/// #ftKb_LkSpecialAirNStart_IASA

/// #ftKb_LkSpecialAirNLoop_IASA

void ftKb_LkSpecialAirNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_LkSpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_LkSpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_LkSpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_LkSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_LkSpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_LkSpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/// #ftKb_LkSpecialNStart_Coll

/// #ftKb_LkSpecialNLoop_Coll

/// #ftKb_LkSpecialNEnd_Coll

/// #ftKb_LkSpecialAirNStart_Coll

/// #ftKb_LkSpecialAirNLoop_Coll

/// #ftKb_LkSpecialAirNEnd_Coll

/// #ftKb_SpecialNSs_800FCC14

/// #ftKb_SpecialNSs_800FCC6C

/// #ftKb_SpecialNSs_800FCCBC

void ftKb_SpecialNSs_800FCD04(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        void* new_var;
        int new_var2;
        Fighter* fp;
        fp = GET_FIGHTER(gobj);
        if (fp->fv.kb.xA4 != NULL) {
            new_var = NULL;
            fp->fv.kb.xA4 = new_var;
        }
        new_var2 = gobj != NULL;
        if (new_var2) {
            fp = GET_FIGHTER(gobj);
            efLib_DestroyAll(gobj);
            fp->fv.kb.xAC = 0;
        }
    }
}

void ftKb_SpecialNSs_800FCD60(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        /// FAKE MATCH: redundant NULL checks required for regalloc
        if (gobj != NULL) {
            if (fp->fv.kb.xA4 != 0) {
                it_802B5974(fp->fv.kb.xA4);
                fp->fv.kb.xA4 = 0;
            }
            if (gobj != NULL) {
                Fighter* fp2 = GET_FIGHTER(gobj);
                efLib_DestroyAll(gobj);
                fp2->fv.kb.xAC = 0;
            }
        }
        fp->fv.kb.xA8 = 0;
    }
}

/// #ftKb_SpecialNSs_800FCDE0

void ftKb_SpecialNSs_800FCF74(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialNStart, 0, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    ftCommon_8007D7FC(fp);
    fp->self_vel.y = 0.0F;
    fp = GET_FIGHTER(gobj);
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
    fp->mv.kb.specialhi.x0 = 0;
    fp->mv.kb.specialhi.x4 = 0;
    fp->mv.kb.specialhi.x8.f = 0.0F;
    ftAnim_8006EBA4(gobj);
}

void ftKb_SpecialNSs_800FD020(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialAirNStart, 0, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp = GET_FIGHTER(gobj);
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
    fp->mv.kb.specialhi.x0 = 1;
    fp->mv.kb.specialhi.x4 = 0;
    fp->mv.kb.specialhi.x8.f = 0.0F;
    ftAnim_8006EBA4(gobj);
}

/// #ftKb_SsSpecialNStart_Anim

/// #ftKb_SsSpecialNHold_Anim

void ftKb_SsSpecialNCancel_Anim(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->fv.kb.xA4 != 0) {
            it_802B5974(fp->fv.kb.xA4);
            fp->fv.kb.xA4 = 0;
        }
        if (gobj != NULL) {
            Fighter* fp2 = GET_FIGHTER(gobj);
            efLib_DestroyAll(gobj);
            fp2->fv.kb.xAC = 0;
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_SsSpecialN_Anim(Fighter_GObj* gobj)
{
    u8 _[24];

    ftKb_SpecialNSs_800FCDE0(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

/// #ftKb_SsSpecialAirNStart_Anim

void ftKb_SsSpecialAirN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    volatile unsigned long long pad;
    ftKb_SpecialNSs_800FCDE0(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (da->specialn_ss_freefall_toggle == 0.0F) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 0, 1, 1.0F, da->specialn_ss_freefall_toggle);
    }
}

void ftKb_SsSpecialNStart_IASA(Fighter_GObj* gobj) {}

/// #ftKb_SsSpecialNHold_IASA

void ftKb_SsSpecialNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_SsSpecialN_IASA(Fighter_GObj* gobj) {}

void ftKb_SsSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_SsSpecialAirN_IASA(Fighter_GObj* gobj) {}

void ftKb_SsSpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SsSpecialNHold_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SsSpecialNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SsSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SsSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SsSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SsSpecialNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialAirNStart,
                                  0x0C4C5080U, fp->cur_anim_frame, 1.0f, 0.0f,
                                  NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SsSpecialNHold_Coll(Fighter_GObj* gobj)
{
    int new_var;
    Fighter* new_var2;
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        Fighter* fp2;
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialAirN, 0x0C4C5080,
                                  fp->cur_anim_frame, 1.0F, 0.0F, NULL);
        fp2 = GET_FIGHTER(gobj);
        new_var2 = fp2;
        new_var2->death2_cb = ftKb_Init_800EE74C;
        fp2->take_dmg_cb = ftKb_Init_800EE7B8;
        ft_PlaySFX(fp, 0x3F7B5, 0x7F, 0x40);
        new_var = 1;
        fp->cmd_vars[new_var] = new_var;
    }
}

void ftKb_SsSpecialNCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialAirN, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SsSpecialN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialAirN, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SsSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Air) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialNStart, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SsSpecialAirN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Air) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialN, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

/// #ftKb_SpecialNFx_800FDC00
