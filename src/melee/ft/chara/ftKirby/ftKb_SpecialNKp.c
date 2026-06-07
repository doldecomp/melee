#include "ftKb_Init.h"

#include "cm/camera.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ftCommon/ftCo_Fall.h"
#include "it/item.h"
#include "it/items/itkoopaflame.h"
#include "lb/lb_00B0.h"

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
