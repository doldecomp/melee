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

#include "it/forward.h"

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
#include "it/items/itkoopaflame.h"
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

extern f32 ftKb_Init_804D9420;

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

void ftKb_PkSpecialN_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007D5D4(fp);
        {
            s32 msid = ftKb_MS_PkSpecialAirN;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_PIKACHU:
                break;
            case FTKIND_PICHU:
                msid = ftKb_MS_PcSpecialAirN;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5082, anim_frame, 1.0F,
                                      0.0F, NULL);
        }
    }
}

void ftKb_PkSpecialAirN_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) == GA_Air) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007D7FC(fp);
        fp->self_vel.y = 0.0f;
        {
            s32 msid = ftKb_MS_PkSpecialN;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_PIKACHU:
                break;
            case FTKIND_PICHU:
                msid = ftKb_MS_PcSpecialN;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5082, anim_frame, 1.0F,
                                      0.0F, NULL);
        }
    }
}

void ftKb_SpecialNKp_800FA588(Fighter_GObj* gobj)
{
    Vec3 pos;
    Vec3 offset;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    enum_t* dirs = ftKb_Init_803CB540;
    int new_facing;
    u8 _[4];
    PAD_STACK(8);

    offset.x = 0.0f;
    offset.y = 0.5f;
    offset.z = 3.0f;
    lb_8000B1CC(fp->parts[12].joint, &offset, &pos);
    pos.x +=
        fp->x34_scale.y * (da->specialn_kp_breath_x_offset * fp->facing_dir);
    pos.y += da->specialn_kp_breath_y_offset * fp->x34_scale.y;

    {
        Fighter* fp2 = GET_FIGHTER(gobj);
        switch (fp2->mv.kb.specialn_kp.x0[2]) {
        case 1:
        case 2:
            new_facing = dirs[HSD_Randi(0x20) + 0x20];
            break;
        case 0:
        case 3:
        default:
            if (dirs[HSD_Randi(0x20)] == 0) {
                new_facing = dirs[HSD_Randi(0x20) + 0x20];
            } else {
                new_facing = dirs[HSD_Randi(0x20) + 0x40];
            }
            break;
        }
        fp2->mv.kb.specialn_kp.x0[2] = new_facing;
    }

    itKoopaFlame_Spawn(gobj, &pos, fp->facing_dir, fp->mv.kb.specialn_kp.x0[1],
                       new_facing, fp->fv.kb.x84, fp->fv.kb.x88, 0x9A);

    if (fp->mv.kb.specialn_kp.x14 == 0) {
        fp->mv.kb.specialn_kp.x0[1] = Item_8026AE60();
        ft_80089824(gobj);
        ft_800892A0(gobj);
    }

    if ((fp->mv.kb.specialn_kp.x14 % 3) == 0) {
        f32 f = (fp->fv.kb.x88 - da->specialn_kp_lowest_charge_graphic_size) /
                (da->specialn_kp_flame_scale -
                 da->specialn_kp_lowest_charge_graphic_size);
        if (f < 0.3333f) {
            ft_PlaySFX(fp, 0x24A2B, 0x7F, 0x40);
        } else if (f < 0.6666f) {
            ft_PlaySFX(fp, 0x24A28, 0x7F, 0x40);
        } else {
            ft_PlaySFX(fp, 0x24A25, 0x7F, 0x40);
        }
    }

    fp->mv.kb.specialn_kp.x14 += 1;
    fp->mv.kb.specialn_kp.x14 %= 12;
}

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
    PAD_STACK(8);
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
    int new_var2;
    Fighter* fp;
    int new_var;
    s32 msid = ftKb_MS_KpSpecialAirNStart;
    switch ((s32) GET_FIGHTER(gobj)->fv.kb.hat.kind) {
    case FTKIND_KOOPA:
        break;
    case FTKIND_GKOOPS:
        msid = ftKb_MS_GkSpecialAirNStart;
        break;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0F, 1.0F, 0.0F, NULL);
    new_var2 = 0;
    fp = GET_FIGHTER(gobj);
    fp->mv.kb.specialn_kp.x0[0] = new_var2;
    fp->mv.kb.specialn_kp.x0[1] = Item_8026AE60();
    fp->mv.kb.specialn_kp.x0[2] = -1;
    fp->mv.kb.specialn_kp.x10 = 1;
    fp->mv.kb.specialn_kp.x14 = 0;
    fp->mv.kb.specialn_kp.x18 = new_var2;
    new_var = 3;
    fp->mv.kb.specialn_kp.x0[new_var] = new_var2;
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

inline ftKb_DatAttrs* ftKb_KpSpecialN_Anim_inline(Fighter* arg0)
{
    return arg0->dat_attrs;
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
        ftKb_DatAttrs* da;
        Fighter* fp = GET_FIGHTER(gobj);
        da = fp->dat_attrs;
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
        ftKb_DatAttrs* da;
        Fighter* fp = GET_FIGHTER(gobj);
        da = fp->dat_attrs;
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
    PAD_STACK(24);
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
    PAD_STACK(24);
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

void ftKb_KpSpecialNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        {
            s32 msid = ftKb_MS_KpSpecialAirNStart;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_KOOPA:
                break;
            case FTKIND_GKOOPS:
                msid = ftKb_MS_GkSpecialAirNStart;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5080, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
    }
}

void ftKb_KpSpecialN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        {
            s32 msid = ftKb_MS_KpSpecialAirN;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_KOOPA:
                break;
            case FTKIND_GKOOPS:
                msid = ftKb_MS_GkSpecialAirN;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5880, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
    }
}

void ftKb_KpSpecialNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        {
            s32 msid = ftKb_MS_KpSpecialAirNEnd;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_KOOPA:
                break;
            case FTKIND_GKOOPS:
                msid = ftKb_MS_GkSpecialAirNEnd;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5080, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
    }
}

void ftKb_KpSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        {
            s32 msid = ftKb_MS_KpSpecialN;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_KOOPA:
                break;
            case FTKIND_GKOOPS:
                msid = ftKb_MS_GkSpecialN;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5080, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
    }
}

void ftKb_KpSpecialAirN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        {
            s32 msid = ftKb_MS_KpSpecialN;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_KOOPA:
                break;
            case FTKIND_GKOOPS:
                msid = ftKb_MS_GkSpecialN;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5880, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
    }
}

void ftKb_KpSpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        {
            s32 msid = ftKb_MS_KpSpecialNEnd;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_KOOPA:
                break;
            case FTKIND_GKOOPS:
                msid = ftKb_MS_GkSpecialNEnd;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5080, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
    }
}

ftLk_SpecialNIndex ftKb_SpecialNLk800FB394(Fighter_GObj* gobj)
{
    ftLk_SpecialNIndex idx = ftLk_SpecialNIndex_None;
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.kb.x78 != 0) {
            switch (fp->fv.kb.hat.kind) {
            case FTKIND_LINK:
                switch (fp->motion_id) {
                case ftKb_MS_LkSpecialNStart:
                case ftKb_MS_LkSpecialNLoop:
                case ftKb_MS_LkSpecialNEnd:
                case ftKb_MS_LkSpecialAirNStart:
                case ftKb_MS_LkSpecialAirNLoop:
                case ftKb_MS_LkSpecialAirNEnd:
                    idx = fp->motion_id - ftKb_MS_LkSpecialNStart;
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
                    idx = fp->motion_id - ftKb_MS_ClSpecialNStart;
                }
                break;
            }
        }
    }
    return idx;
}

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

bool ftKb_SpecialNLk800FB500(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[0] == 1 && fp->fv.kb.x74 == 0) {
        Vec3 pos;
        s32 loader_id;
        u8 _[4];
        fp->cmd_vars[0] = 0;
        lb_8000B1CC(fp->parts[FtPart_RHandN].joint, NULL, &pos);
        switch (fp->fv.kb.hat.kind) {
        case FTKIND_LINK:
            loader_id = da->specialn_lk_bow_item_loader_id;
            break;
        case FTKIND_CLINK:
            loader_id = da->specialn_cl_bow_item_loader_id;
            break;
        }
        if ((fp->fv.kb.x74 = it_802A83E0(fp->facing_dir, gobj, &pos,
                                         FtPart_RHandN, loader_id)) != NULL)
        {
            ftKirbyDmgInline(gobj);
        } else {
            return true;
        }
    }
    return false;
}

bool ftKb_SpecialNLk800FB5F4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (fp->fv.kb.x78 == 0) {
        Vec3 pos;
        s32 item_id;
        u8 _[4];
        lb_8000B1CC(fp->parts[FtPart_R3rdNa].joint, NULL, &pos);
        switch (fp->fv.kb.hat.kind) {
        case FTKIND_LINK:
            item_id = da->specialn_lk_bow_item_id;
            break;
        case FTKIND_CLINK:
            item_id = da->specialn_cl_bow_item_id;
            break;
        }
        if ((fp->fv.kb.x78 = it_802AF1A4(fp->facing_dir, gobj, &pos,
                                         FtPart_R3rdNa, item_id)) != NULL)
        {
            ftKirbyDmgInline(gobj);
        } else {
            return true;
        }
    } else {
        return true;
    }
    return false;
}

void ftKb_SpecialNLk800FB6DC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    f32 max;
    PAD_STACK(24);

    if (fp->cmd_vars[1] == 1 && fp->fv.kb.x74 != NULL) {
        Vec3 pos1, pos2;
        Item_GObj* saved_item;
        u8 _[12];
        fp->cmd_vars[1] = 0;
        lb_8000B1CC(fp->parts[44].joint, NULL, &pos1);
        lb_8000B1CC(fp->parts[39].joint, NULL, &pos2);
        pos2.z = 0.0f;
        pos1.z = 0.0f;
        saved_item = fp->item_gobj;
        switch (fp->fv.kb.hat.kind) {
        case FTKIND_LINK:
            max = da->specialn_lk_max_charge;
            break;
        case FTKIND_CLINK:
            max = da->specialn_cl_max_charge;
            break;
        }
        it_802A850C(fp->fv.kb.x74, &pos1, &pos2, 0.08726646f,
                    fp->mv.lk.specialn.x0.y, max);
        ftKb_SpecialNLk_UnsetArrow(gobj);
        fp->item_gobj = saved_item;
        ftpickupitem_80094818(gobj, 0);
    }
}

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

void ftKb_SpecialNLk800FB880(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    ftKirby_MotionState msid;
    f32 anim_rate;
    PAD_STACK(24);
    fp->mv.lk.specialn.x0.y = 0.0F;
    fp->mv.lk.specialn.x0.x = 0.0F;
    fp->mv.lk.specialn.unk_timer = 0;
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    ftCommon_8007D7FC(fp);
    msid = ftKb_MS_LkSpecialNStart;
    fp->self_vel.y = 0.0F;
    switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
    case FTKIND_LINK:
        break;
    case FTKIND_CLINK:
        msid = ftKb_MS_ClSpecialNStart;
        break;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0F, 1.0F, 0.0F, NULL);
    ftKirbyDmgInline(gobj);
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_LINK:
        anim_rate = da->specialn_lk_arrow_charge_speed;
        break;
    case FTKIND_CLINK:
        anim_rate = da->specialn_cl_arrow_charge_speed;
        break;
    }
    ftAnim_SetAnimRate(gobj, anim_rate);
    ftAnim_8006EBA4(gobj);
    if (ftKb_SpecialNLk800FB5F4(gobj) == true) {
        ftKb_SpecialNLk_UnsetArrow(gobj);
        ftKb_SpecialNLk_UnsetBow(gobj);
        ft_8008A2BC(gobj);
    }
}

void ftKb_SpecialNLk800FBA00(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    ftKirby_MotionState msid = ftKb_MS_LkSpecialAirNStart;
    f32 anim_rate;
    PAD_STACK(24);
    fp->mv.lk.specialn.x0.y = 0.0F;
    fp->mv.lk.specialn.x0.x = 0.0F;
    fp->mv.lk.specialn.unk_timer = 0;
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
    case FTKIND_LINK:
        break;
    case FTKIND_CLINK:
        msid = ftKb_MS_ClSpecialAirNStart;
        break;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0F, 1.0F, 0.0F, NULL);
    ftKirbyDmgInline(gobj);
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_LINK:
        anim_rate = da->specialn_lk_arrow_charge_speed;
        break;
    case FTKIND_CLINK:
        anim_rate = da->specialn_cl_arrow_charge_speed;
        break;
    }
    ftAnim_SetAnimRate(gobj, anim_rate);
    ftAnim_8006EBA4(gobj);
    if (ftKb_SpecialNLk800FB5F4(gobj) == true) {
        ftKb_SpecialNLk_UnsetArrow(gobj);
        ftKb_SpecialNLk_UnsetBow(gobj);
        switch (fp->fv.kb.hat.kind) {
        case FTKIND_LINK:
            anim_rate = da->specialn_lk_freefall_toggle;
            break;
        case FTKIND_CLINK:
            anim_rate = da->specialn_cl_freefall_toggle;
            break;
        }
        if (anim_rate == 0.0F) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 0, 1, 1.0F, anim_rate);
    }
}

extern ftLk_SpecialN_Vec3Group const ftKb_Init_803B7548;

void ftKb_LkSpecialNStart_Anim(Fighter_GObj* gobj)
{
    const ftLk_SpecialN_Vec3Group* vg = &ftKb_Init_803B7548;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    f32 anim_rate;
    Vec3 c, b, a;
    PAD_STACK(24);
    if (fp->cmd_vars[2] != 0 && fp->mv.lk.specialn.x0.x == 0.0F) {
        fp->mv.lk.specialn.x0.x = 1.0F;
        fp->cmd_vars[2] = 0;
    }
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_LINK:
        anim_rate = da->specialn_lk_arrow_charge_speed;
        break;
    case FTKIND_CLINK:
        anim_rate = da->specialn_cl_arrow_charge_speed;
        break;
    }
    ftAnim_SetAnimRate(gobj, anim_rate);
    if (ftKb_SpecialNLk800FB500(gobj) == false) {
        Fighter* fp2 = GET_FIGHTER(gobj);
        a = vg->a;
        b = vg->b;
        c = vg->c;
        fp2->mv.lk.specialn.x8.y = b.x - c.x;
        fp2->mv.lk.specialn.x8.z = b.y - c.y;
        fp2->mv.lk.specialn.x14 = 0.0F;
        fp2->mv.lk.specialn.x8.x = atan2f(b.y - a.y, b.x - a.x);
        if (fp2->fv.kb.x74 != 0) {
            it_802A8398((Item_GObj*) fp2->fv.kb.x74, &b, &a);
        }
        if (!ftAnim_IsFramesRemaining(gobj)) {
            ftKirby_MotionState msid = ftKb_MS_LkSpecialNLoop;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_LINK:
                break;
            case FTKIND_CLINK:
                msid = ftKb_MS_ClSpecialNLoop;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x40010, 0.0F, 1.0F, 0.0F,
                                      NULL);
            ftKirbyDmgInline(gobj);
            ftAnim_8006EBA4(gobj);
        }
    } else {
        ftKb_SpecialNLk_UnsetArrow(gobj);
        ftKb_SpecialNLk_UnsetBow(gobj);
        ft_8008A2BC(gobj);
    }
}

extern ftLk_SpecialN_Vec3Group const ftKb_Init_803B7548;

void ftKb_LkSpecialNLoop_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 c, b, a;
    a = ftKb_Init_803B7548.a;
    b = ftKb_Init_803B7548.b;
    c = ftKb_Init_803B7548.c;
    fp->mv.lk.specialn.x8.y = b.x - c.x;
    fp->mv.lk.specialn.x8.z = b.y - c.y;
    fp->mv.lk.specialn.x14 = 0.0F;
    fp->mv.lk.specialn.x8.x = atan2f(b.y - a.y, b.x - a.x);
    if (fp->fv.kb.x74 != 0) {
        it_802A8398((Item_GObj*) fp->fv.kb.x74, &b, &a);
    }
}

void ftKb_LkSpecialNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter_GObj* new_var;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        new_var = gobj;
        ftKb_SpecialNLk_UnsetBow(new_var);
        ft_8008A2BC(gobj);
    }
}

void ftKb_LkSpecialAirNStart_Anim(Fighter_GObj* gobj)
{
    const ftLk_SpecialN_Vec3Group* vg = &ftKb_Init_803B7548;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    f32 anim_rate;
    Vec3 c, b, a;
    PAD_STACK(24);
    if (fp->cmd_vars[2] != 0 && fp->mv.lk.specialn.x0.x == 0.0F) {
        fp->mv.lk.specialn.x0.x = 1.0F;
        fp->cmd_vars[2] = 0;
    }
    if (ftKb_SpecialNLk800FB500(gobj) == false) {
        fp = GET_FIGHTER(gobj);
        a = vg->a;
        b = vg->b;
        c = vg->c;
        fp->mv.lk.specialn.x8.y = b.x - c.x;
        fp->mv.lk.specialn.x8.z = b.y - c.y;
        fp->mv.lk.specialn.x14 = 0.0F;
        fp->mv.lk.specialn.x8.x = atan2f(b.y - a.y, b.x - a.x);
        if (fp->fv.kb.x74 != 0) {
            it_802A8398((Item_GObj*) fp->fv.kb.x74, &b, &a);
        }
        if (!ftAnim_IsFramesRemaining(gobj)) {
            ftKirby_MotionState msid = ftKb_MS_LkSpecialAirNLoop;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_LINK:
                break;
            case FTKIND_CLINK:
                msid = ftKb_MS_ClSpecialAirNLoop;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x40010, 0.0F, 1.0F, 0.0F,
                                      NULL);
            ftKirbyDmgInline(gobj);
            ftAnim_8006EBA4(gobj);
        }
    } else {
        ftKb_SpecialNLk_UnsetArrow(gobj);
        ftKb_SpecialNLk_UnsetBow(gobj);
        switch (fp->fv.kb.hat.kind) {
        case FTKIND_LINK:
            anim_rate = da->specialn_lk_freefall_toggle;
            break;
        case FTKIND_CLINK:
            anim_rate = da->specialn_cl_freefall_toggle;
            break;
        }
        if (anim_rate == 0.0F) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 0, 1, 1.0F, anim_rate);
    }
}

void ftKb_LkSpecialAirNLoop_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 c, b, a;
    a = ftKb_Init_803B7548.a;
    b = ftKb_Init_803B7548.b;
    c = ftKb_Init_803B7548.c;
    fp->mv.lk.specialn.x8.y = b.x - c.x;
    fp->mv.lk.specialn.x8.z = b.y - c.y;
    fp->mv.lk.specialn.x14 = 0.0F;
    fp->mv.lk.specialn.x8.x = atan2f(b.y - a.y, b.x - a.x);
    if (fp->fv.kb.x74 != 0) {
        it_802A8398((Item_GObj*) fp->fv.kb.x74, &b, &a);
    }
}

void ftKb_LkSpecialAirNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftKb_DatAttrs* da = fp->dat_attrs;
    float freefall;
    PAD_STACK(24);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftKb_SpecialNLk_UnsetArrow(gobj);
        ftKb_SpecialNLk_UnsetBow(gobj);
        switch (fp->fv.kb.hat.kind) {
        case FTKIND_LINK:
            freefall = da->specialn_lk_freefall_toggle;
            break;
        case FTKIND_CLINK:
            freefall = da->specialn_cl_freefall_toggle;
            break;
        }
        if (freefall == 0.0f) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, true, 1.0f, freefall);
        }
    }
}

void ftKb_LkSpecialNStart_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    if (fp->mv.lk.specialn.x0.x != 0) {
        f32 max;
        fp->mv.lk.specialn.x0.y += 1.0f;
        switch (fp->fv.kb.hat.kind) {
        case FTKIND_LINK:
            max = da->specialn_lk_max_charge;
            break;
        case FTKIND_CLINK:
            max = da->specialn_cl_max_charge;
            break;
        }
        if (fp->mv.lk.specialn.x0.y > max) {
            fp->mv.lk.specialn.x0.y = max;
        }
        if (!(fp->input.held_inputs & HSD_PAD_B)) {
            s32 msid = ftKb_MS_LkSpecialNEnd;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_LINK:
                break;
            case FTKIND_CLINK:
                msid = ftKb_MS_ClSpecialNEnd;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x40010, 0.0f, 1.0f, 0.0f,
                                      NULL);
            ftKirbyDmgInline(gobj);
        }
    }
}

void ftKb_LkSpecialNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_LINK:
        fp->mv.lk.specialn.x0.y = da->specialn_lk_max_charge;
        break;
    case FTKIND_CLINK:
        fp->mv.lk.specialn.x0.y = da->specialn_cl_max_charge;
        break;
    }
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        s32 msid = ftKb_MS_LkSpecialNEnd;
        switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
        case FTKIND_LINK:
            break;
        case FTKIND_CLINK:
            msid = ftKb_MS_ClSpecialNEnd;
            break;
        }
        Fighter_ChangeMotionState(gobj, msid, 0x40010, 0.0f, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_LkSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_LkSpecialAirNStart_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    if (fp->mv.lk.specialn.x0.x != 0) {
        f32 max;
        fp->mv.lk.specialn.x0.y += 1.0f;
        switch (fp->fv.kb.hat.kind) {
        case FTKIND_LINK:
            max = da->specialn_lk_max_charge;
            break;
        case FTKIND_CLINK:
            max = da->specialn_cl_max_charge;
            break;
        }
        if (fp->mv.lk.specialn.x0.y > max) {
            fp->mv.lk.specialn.x0.y = max;
        }
        if (!(fp->input.held_inputs & HSD_PAD_B)) {
            s32 msid = ftKb_MS_LkSpecialAirNEnd;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_LINK:
                break;
            case FTKIND_CLINK:
                msid = ftKb_MS_ClSpecialAirNEnd;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x40010, 0.0f, 1.0f, 0.0f,
                                      NULL);
            ftKirbyDmgInline(gobj);
        }
    }
}

void ftKb_LkSpecialAirNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_LINK:
        fp->mv.lk.specialn.x0.y = da->specialn_lk_max_charge;
        break;
    case FTKIND_CLINK:
        fp->mv.lk.specialn.x0.y = da->specialn_cl_max_charge;
        break;
    }
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        s32 msid = ftKb_MS_LkSpecialAirNEnd;
        switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
        case FTKIND_LINK:
            break;
        case FTKIND_CLINK:
            msid = ftKb_MS_ClSpecialAirNEnd;
            break;
        }
        Fighter_ChangeMotionState(gobj, msid, 0x40010, 0.0f, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

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

void ftKb_LkSpecialNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        {
            s32 msid = ftKb_MS_LkSpecialAirNStart;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_LINK:
                break;
            case FTKIND_CLINK:
                msid = ftKb_MS_ClSpecialAirNStart;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5090, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
        ftKirbyDmgInline(gobj);
        ftAnim_8006EBA4(gobj);
    }
}

void ftKb_LkSpecialNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        {
            s32 msid = ftKb_MS_LkSpecialAirNLoop;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_LINK:
                break;
            case FTKIND_CLINK:
                msid = ftKb_MS_ClSpecialAirNLoop;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5090, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
        ftKirbyDmgInline(gobj);
        ftAnim_8006EBA4(gobj);
    }
}

void ftKb_LkSpecialNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    ftKb_SpecialNLk800FB6DC(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        {
            s32 msid = ftKb_MS_LkSpecialAirNEnd;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_LINK:
                break;
            case FTKIND_CLINK:
                msid = ftKb_MS_ClSpecialAirNEnd;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5090, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
        ftKirbyDmgInline(gobj);
        ftAnim_8006EBA4(gobj);
    }
}

void ftKb_LkSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        {
            s32 msid = ftKb_MS_LkSpecialNStart;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_LINK:
                break;
            case FTKIND_CLINK:
                msid = ftKb_MS_ClSpecialNStart;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5090, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
        ftKirbyDmgInline(gobj);
        ftAnim_8006EBA4(gobj);
    }
}

void ftKb_LkSpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        {
            s32 msid = ftKb_MS_LkSpecialNLoop;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_LINK:
                break;
            case FTKIND_CLINK:
                msid = ftKb_MS_ClSpecialNLoop;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5090, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
        ftKirbyDmgInline(gobj);
        ftAnim_8006EBA4(gobj);
    }
}

void ftKb_LkSpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    ftKb_SpecialNLk800FB6DC(gobj);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        {
            s32 msid = ftKb_MS_LkSpecialNEnd;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_LINK:
                break;
            case FTKIND_CLINK:
                msid = ftKb_MS_ClSpecialNEnd;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5090, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
        ftKirbyDmgInline(gobj);
        ftAnim_8006EBA4(gobj);
    }
}

long ftKb_SpecialNSs_800FCC14(Fighter_GObj* gobj, long* out1, long* out2)
{
    Fighter* fp;
    ftKb_DatAttrs* da;
    PAD_STACK(8);

    if (gobj == NULL) {
        goto return_error;
    }

    fp = GET_FIGHTER(gobj);
    da = fp->dat_attrs;

    if (fp->fv.kb.xA4 == NULL) {
        return -1;
    }

    *out1 = fp->fv.kb.xA8;
    *out2 = (long) da->specialn_ss_charge_time;

    return 0;

return_error:
    return -1;
}

bool ftKb_SpecialNSs_800FCC6C(Fighter_GObj* gobj)
{
    Fighter* fp;

    if (!gobj) {
        goto end_true;
    }

    fp = GET_FIGHTER(gobj);

    switch (fp->motion_id) {
    case 0x197:
    case 0x198:
    case 0x199:
    case 0x19A:
    case 0x19B:
    case 0x19C:
        if (fp->x2070.x2071_b6) {
            return true;
        }
        return false;
    default:
        return true;
    }

end_true:
    return true;
}

bool ftKb_SpecialNSs_800FCCBC(Fighter_GObj* gobj)
{
    Fighter* fp;
    s32 motion_id;

    if (!gobj) {
        goto end_true;
    }

    fp = GET_FIGHTER(gobj);
    motion_id = fp->motion_id;

    if (motion_id == 0x199) {
        goto ret_true;
    }

    if (motion_id >= 0x199) {
        goto check_upper;
    }

    if (motion_id >= 0x197) {
        goto ret_false;
    }
    goto ret_true;

check_upper:
    if (motion_id >= 0x19D) {
        goto ret_true;
    }

ret_false:
    return false;

ret_true:
    return true;

end_true:
    return true;
}

static inline void ftKb_SpecialNSs_it_802B5974(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xA4 != NULL) {
        it_802B5974(fp->fv.kb.xA4);
        fp->fv.kb.xA4 = NULL;
    }
}

static inline void ftKb_SpecialNSs_DestroyChargeShot(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        efLib_DestroyAll(gobj);
        fp->fv.kb.xAC = NULL;
    }
}

static inline void ftKb_ChargeShot_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (gobj != NULL) {
        ftKb_SpecialNSs_it_802B5974(gobj);
        ftKb_SpecialNSs_DestroyChargeShot(gobj);
    }
}

void ftKb_SpecialNSs_800FCD04(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->fv.kb.xA4 != NULL) {
            fp->fv.kb.xA4 = NULL;
        }
        ftKb_SpecialNSs_DestroyChargeShot(gobj);
    }
}

void ftKb_SpecialNSs_800FCD60(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftKb_ChargeShot_inline(gobj);
        fp->fv.kb.xA8 = 0;
    }
}

static inline void ftKb_SpecialNSs_800FCDE0_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    fp->self_vel.x =
        fp->facing_dir * (da->specialn_ss_aerial_shot_recoil * fp->fv.kb.xA8);
}

static inline f64 facing_to_angle(Fighter* fp)
{
    if (fp->facing_dir == 1.0F) {
        return 0.0;
    } else {
        return M_PI;
    }
}

static inline void ftKb_SpecialNSs_UnsetChargeShot(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xA4 != NULL) {
        fp->fv.kb.xA4 = NULL;
    }
}

void ftKb_SpecialNSs_800FCDE0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    Item_GObj* saved_item;
    PAD_STACK(20);
    if (fp->cmd_vars[1] == 1 && fp->fv.kb.xA4 != NULL) {
        Vec3 pos;
        Vec3 offset;
        PAD_STACK(16);
        fp->cmd_vars[1] = 2;
        offset.x = offset.y = offset.z = 0.0F;
        lb_8000B1CC(fp->parts[FtPart_R3rdNa].joint, &offset, &pos);
        pos.z = 0.0F;
        saved_item = fp->item_gobj;
        it_802B56E4(fp->fv.kb.xA4, &pos, facing_to_angle(fp),
                    (u32) fp->fv.kb.xA8, da->specialn_ss_charge_time);
        if (fp->motion_id == ftKb_MS_SsSpecialAirN ||
            fp->ground_or_air == GA_Air)
        {
            ftKb_SpecialNSs_800FCDE0_inline(gobj);
        }
        fp->fv.kb.xA8 = 0;

        if (gobj != NULL) {
            ftKb_SpecialNSs_UnsetChargeShot(gobj);
            ftKb_SpecialNSs_DestroyChargeShot(gobj);
        }
        efSync_Spawn(0x4A4, gobj, &pos, &fp->facing_dir);
        fp->item_gobj = saved_item;
    }
}

void ftKb_SpecialNSs_800FCF74(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialNStart, 0, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    ftCommon_8007D7FC(fp);
    fp->self_vel.y = 0.0F;
    ftKirbyDmgInline(gobj);
    fp->mv.kb.specialhi.x0 = 0;
    fp->mv.kb.specialhi.x4 = 0;
    fp->mv.kb.specialhi.x8.f = 0.0F;
    ftAnim_8006EBA4(gobj);
}

void ftKb_SpecialNSs_800FD020(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialAirNStart, 0, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    ftKirbyDmgInline(gobj);
    fp->mv.kb.specialhi.x0 = 1;
    fp->mv.kb.specialhi.x4 = 0;
    fp->mv.kb.specialhi.x8.f = 0.0F;
    ftAnim_8006EBA4(gobj);
}

void ftKb_SsSpecialNStart_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[0] == 1 && fp->fv.kb.xA4 == 0) {
        Vec3 offset;
        Vec3 pos;
        PAD_STACK(12);
        fp->cmd_vars[0] = 0;
        offset.z = ftKb_Init_804D9420;
        offset.y = 0.0F;
        offset.x = 0.0F;
        lb_8000B1CC(fp->parts[FtPart_R3rdNa].joint, &offset, &pos);
        pos.z = 0.0F;
        if ((fp->fv.kb.xA4 = it_802B55C8(gobj, &pos, FtPart_R3rdNa, 0x97,
                                         fp->facing_dir)) != NULL)
        {
            ftKirbyDmgInline(gobj);
        } else {
            fp->fv.kb.xA4 = 0;
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->mv.kb.specialhi.x0 == 1 ||
            fp->fv.kb.xA8 == da->specialn_ss_charge_time)
        {
            Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialN, 0, 0.0F, 1.0F,
                                      0.0F, NULL);
        } else {
            Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialNHold, 0, 0.0F,
                                      1.0F, 0.0F, NULL);
            GET_FIGHTER(gobj)->fv.kb.xAC = 0;
        }
        ftKirbyDmgInline(gobj);
    }
}

extern u32 ftKb_Init_803CB6C0[];
extern f32 ftKb_Init_804D9448;

void ftKb_SsSpecialNHold_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    f32 ratio;
    int i;
    PAD_STACK(28);
    if (fp->cmd_vars[2] != 0) {
        fp->cmd_vars[2] = 0;
        if (fp->fv.kb.xA8 != 0) {
            ratio = fp->fv.kb.xA8 / da->specialn_ss_charge_time;
        } else {
            ratio = 0.0F;
        }
        i = ftKb_Init_804D9448 * ratio;
        ft_80088510(fp, ftKb_Init_803CB6C0[i], 0x7F, 0x40);
    }
    fp->mv.kb.specialhi.x4 += 1;
    if (fp->mv.kb.specialhi.x4 > da->specialn_ss_frames_per_charge_level) {
        fp->mv.kb.specialhi.x4 = 0;
        fp->fv.kb.xA8 += 1;
        if (fp->fv.kb.xA8 >= da->specialn_ss_charge_time) {
            ftCo_800BFFD0(fp, 0x36, 0);
            fp->fv.kb.xA8 = da->specialn_ss_charge_time;
            Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialNCancel, 0, 0.0F,
                                      1.0F, 0.0F, NULL);
            ftKb_ChargeShot_inline(gobj);
            ftKirbyDmgInline(gobj);
        }
    }
}

void ftKb_SsSpecialNCancel_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    ftKb_ChargeShot_inline(gobj);
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

void ftKb_SsSpecialAirNStart_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0] == 1 && fp->fv.kb.xA4 == 0) {
        Vec3 offset;
        Vec3 pos;
        u8 _[4];
        fp->cmd_vars[0] = 0;
        offset.z = ftKb_Init_804D9420;
        offset.y = 0.0F;
        offset.x = 0.0F;
        lb_8000B1CC(fp->parts[FtPart_R3rdNa].joint, &offset, &pos);
        pos.z = 0.0F;
        if ((fp->fv.kb.xA4 = it_802B55C8(gobj, &pos, FtPart_R3rdNa, 0x97,
                                         fp->facing_dir)) != NULL)
        {
            ftKirbyDmgInline(gobj);
        } else {
            fp->fv.kb.xA4 = 0;
        }
    }
    fp->mv.kb.specialhi.x0 = 1;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialAirN, 0, 0.0F, 1.0F,
                                  0.0F, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SsSpecialAirN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
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

void ftKb_SsSpecialNHold_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (ftCo_8009917C(gobj) != 0) {
        ftKb_ChargeShot_inline(gobj);
    } else {
        if (fp->input.x668 & 0x200) {
            Fighter_ChangeMotionState(gobj, 0x19A, 0U, 0.0f, 1.0f, 0.0f, NULL);
            ftKirbyDmgInline(gobj);
            return;
        }
        if (fp->input.x668 & 0x80000000) {
            Fighter_ChangeMotionState(gobj, 0x199, 0U, 0.0f, 1.0f, 0.0f, NULL);
            ftKb_ChargeShot_inline(gobj);
            ftKirbyDmgInline(gobj);
        }
    }
}

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
    Fighter* fp = HSD_GObjGetUserData(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        Fighter* fp2;
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialAirN, 0x0C4C5080,
                                  fp->cur_anim_frame, 1.0F, 0.0F, NULL);
        ftKirbyDmgInline(gobj);
        ft_PlaySFX(fp, 0x3F7B5, 0x7F, 0x40);
        fp->cmd_vars[1] = 1;
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
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialNStart, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SsSpecialAirN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialN, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

extern f32 ftKb_Init_804D9450;
extern f32 ftKb_Init_804D9454;
extern f32 ftKb_Init_804D9458;

void ftKb_SpecialNFx_800FDC00(Fighter_GObj* gobj, Vec3* vec)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL) {
            Vec3 offset;
            offset.x = ftKb_Init_804D9450;
            offset.y = ftKb_Init_804D9454;
            offset.z = ftKb_Init_804D9458;
            lb_8000B1CC(fp->parts[44].joint, &offset, vec);
            return;
        }
    }
    vec->x = vec->y = vec->z = ftKb_Init_804D9450;
}
