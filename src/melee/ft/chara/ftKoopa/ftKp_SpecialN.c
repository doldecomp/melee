#include "ftKp_SpecialN.h"

#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftKoopa/ftKp_Init.h"

#include <trigf.h>
#include <melee/cm/camera.h>
#include <melee/ef/eflib.h>
#include <melee/ef/efsync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftcliffcommon.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/inlines.h>
#include <melee/it/item.h>
#include <melee/it/items/itkoopaflame.h>
#include <melee/lb/lb_00B0.h>

enum_t ftKp_Init_803CF2A0[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
    0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2,
};

static inline int ftKp_SpecialLw_80134ACC_inline(Fighter_GObj* gobj,
                                                 enum_t* dirs)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int new_facing;
    switch (fp->mv.kp.specials.facing_dir) {
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
    fp->mv.kp.specials.facing_dir = new_facing;
    return new_facing;
}

void ftKp_SpecialLw_80134ACC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    Vec3 v;
    enum_t* dirs = ftKp_Init_803CF2A0;
    PAD_STACK(12);
    lb_8000B1CC(fp->parts[48].joint, NULL, &v);
    v.x += fp->x34_scale.y * (da->x24 * fp->facing_dir);
    v.y += da->x28 * fp->x34_scale.y;
    itKoopaFlame_Spawn(gobj, &v, fp->facing_dir, fp->mv.kp.specials.x4,
                       ftKp_SpecialLw_80134ACC_inline(gobj, dirs),
                       fp->fv.kp.x222C, fp->fv.kp.x2230, 100);
    if (fp->mv.kp.specials.x14 == 0) {
        fp->mv.kp.unk1.x4 = Item_8026AE60();
        ft_80089824(gobj);
        ft_800892A0(gobj);
    }
    if ((fp->mv.kp.specials.x14 % 3) == 0) {
        f32 f = (fp->fv.kp.x2230 - da->x1C) / (da->x18 - da->x1C);
        if (f < 0.3333f) {
            if (fp->kind == FTKIND_KOOPA) {
                ft_PlaySFX(fp, 0x24A2B, 0x7F, 0x40);
            } else {
                ft_PlaySFX(fp, 0x1D4F3, 0x7F, 0x40);
            }
        } else if (f < 0.6666f) {
            if (fp->kind == FTKIND_KOOPA) {
                ft_PlaySFX(fp, 0x24A28, 0x7F, 0x40);
            } else {
                ft_PlaySFX(fp, 0x1D4F0, 0x7F, 0x40);
            }
        } else if (fp->kind == FTKIND_KOOPA) {
            ft_PlaySFX(fp, 0x24A25, 0x7F, 0x40);
        } else {
            ft_PlaySFX(fp, 0x1D4ED, 0x7F, 0x40);
        }
    }
    fp->mv.kp.specials.x14 += 1;
    fp->mv.kp.specials.x14 %= 0xC;
}

void ftKp_SpecialLw_80134D78(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    if ((fp->motion_id >= 0x15B) || (fp->motion_id < 0x155)) {
        fp->fv.kp.x222C = fp->fv.kp.x222C + da->x8;
        if (fp->fv.kp.x222C > da->x10) {
            fp->fv.kp.x222C = da->x10;
        }
        fp->fv.kp.x2230 = fp->fv.kp.x2230 + da->xC;
        if (fp->fv.kp.x2230 > da->x18) {
            fp->fv.kp.x2230 = da->x18;
        }
    }
}

s32 ftKp_SpecialLw_80134DE0(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL) {
            ftKoopaAttributes* da = fp->dat_attrs;
            return da->x10;
        }
    }
    return 1;
}

s32 ftKp_SpecialLw_80134E1C(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL) {
            ftKoopaAttributes* da = fp->dat_attrs;
            return da->x18;
        }
    }
    return 2;
}

static void ftKp_SpecialN_Enter_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.kp.specials.b_held = 0;
    fp->mv.kp.unk1.x4 = Item_8026AE60();
    fp->mv.kp.specials.facing_dir = 0;
    fp->mv.kp.specials.x10 = 1;
    fp->mv.kp.specials.x14 = 0;
    fp->mv.kp.specials.x18 = 0;
    fp->mv.kp.unk1.xC = 0;
}

void ftKp_SpecialN_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x155, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftKp_SpecialN_Enter_inline(gobj);
}

void ftKp_SpecialAirN_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x158, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftKp_SpecialN_Enter_inline(gobj);
}

void ftKp_SpecialNStart_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialN, Ft_MF_None, 0.0f,
                                  1.0f, 0.0f, NULL);
    }
}

static void ftKp_SpecialN_Anim_inline_1(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cur_anim_frame == 0.0f) {
        fp->mv.kp.specials.x10 -= 1;
        if (fp->mv.kp.specials.x10 <= 0) {
            fp->mv.kp.specials.x10 = 0;
        }
    }
}

static void ftKp_SpecialN_Anim_inline_2(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    if (fp->mv.kp.specials.x18 == 0) {
        Camera_80030E44(2, &fp->cur_pos);
    }
    fp->mv.kp.specials.x18 += 1;
    fp->mv.kp.specials.x18 %= da->x20;
}

void ftKp_SpecialN_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    ftKp_SpecialN_Anim_inline_1(gobj);
    ftKp_SpecialN_Anim_inline_2(gobj);
}

void ftKp_SpecialNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKp_SpecialAirNStart_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialAirN, Ft_MF_None, 0.0f,
                                  1.0f, 0.0f, NULL);
    }
}

void ftKp_SpecialAirN_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    ftKp_SpecialN_Anim_inline_1(gobj);
    ftKp_SpecialN_Anim_inline_2(gobj);
}

void ftKp_SpecialAirNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKp_SpecialNStart_IASA(HSD_GObj* gobj) {}

void ftKp_SpecialN_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(16);
    if (fp->mv.co.itemthrow.xC >= da->x4) {
        if (fp->input.held_inputs & HSD_PAD_B) {
            if (!fp->mv.kp.specials.b_held) {
                ftKp_SpecialLw_80134ACC(gobj);
            }
        } else if (fp->mv.kp.specials.x10 != 0) {
            if (!fp->mv.kp.specials.b_held) {
                ftKp_SpecialLw_80134ACC(gobj);
            }
        } else {
            Fighter_ChangeMotionState(gobj, 0x157, 0, 0.0f, 1.0f, 0.0f, NULL);
        }
    } else if (!fp->mv.kp.specials.b_held) {
        ftKp_SpecialLw_80134ACC(gobj);
    }
    fp->mv.co.throw.x0 += 1;
    if (fp->mv.co.throw.x0 >= 3) {
        fp->mv.co.throw.x0 = 0;
    }
    fp->fv.kp.x222C -= 1.0f;
    if (fp->fv.kp.x222C < da->x14) {
        fp->fv.kp.x222C = da->x14;
    }
    fp->fv.kp.x2230 -= 1.0f;
    if (fp->fv.kp.x2230 < da->x1C) {
        fp->fv.kp.x2230 = da->x1C;
    }
    fp->mv.co.itemthrow.xC += 1;
    if (fp->mv.co.itemthrow.xC > da->x4) {
        fp->mv.co.itemthrow.xC = da->x4;
    }
}

void ftKp_SpecialNEnd_IASA(HSD_GObj* gobj) {}

void ftKp_SpecialAirNStart_IASA(HSD_GObj* gobj) {}

void ftKp_SpecialAirN_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(16);
    if (fp->mv.co.itemthrow.xC >= da->x4) {
        if (fp->input.held_inputs & HSD_PAD_B) {
            if (!fp->mv.kp.specials.b_held) {
                ftKp_SpecialLw_80134ACC(gobj);
            }
        } else if (fp->mv.kp.specials.x10 != 0) {
            if (!fp->mv.kp.specials.b_held) {
                ftKp_SpecialLw_80134ACC(gobj);
            }
        } else {
            Fighter_ChangeMotionState(gobj, 0x15a, 0, 0.0f, 1.0f, 0.0f, NULL);
        }
    } else if (!fp->mv.kp.specials.b_held) {
        ftKp_SpecialLw_80134ACC(gobj);
    }
    fp->mv.co.throw.x0 += 1;
    if (fp->mv.co.throw.x0 >= 3) {
        fp->mv.co.throw.x0 = 0;
    }
    fp->fv.kp.x222C -= 1.0f;
    if (fp->fv.kp.x222C < da->x14) {
        fp->fv.kp.x222C = da->x14;
    }
    fp->fv.kp.x2230 -= 1.0f;
    if (fp->fv.kp.x2230 < da->x1C) {
        fp->fv.kp.x2230 = da->x1C;
    }
    fp->mv.co.itemthrow.xC += 1;
    if (fp->mv.co.itemthrow.xC > da->x4) {
        fp->mv.co.itemthrow.xC = da->x4;
    }
}

void ftKp_SpecialAirNEnd_IASA(HSD_GObj* gobj) {}

void ftKp_SpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKp_SpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKp_SpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKp_SpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftKp_SpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftKp_SpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftKp_SpecialNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialAirNStart, 0x0C4C5080,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    }
}

void ftKp_SpecialN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x159, 0x0C4C5880, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
    }
}

void ftKp_SpecialNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x15A, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
    }
}

void ftKp_SpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x155, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
    }
}

void ftKp_SpecialAirN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x156, 0x0C4C5880U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
    }
}

void ftKp_SpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x157, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
    }
}

static void ftKp_SpecialN_80135780_inline(Fighter_GObj* gobj)
{
    ftParts_80074B0C(gobj, 0, 1);
    ftColl_8007B128(gobj, 0x37, Intangible);
    ftColl_8007B128(gobj, 0x30, Intangible);
    ftColl_8007B128(gobj, 0x3C, Intangible);
    ftColl_8007B128(gobj, 0x21, Intangible);
    ftColl_8007B128(gobj, 0x3D, Intangible);
    ftColl_8007B128(gobj, 0x22, Intangible);
    ftColl_8007B128(gobj, 0xF, Intangible);
    ftColl_8007B128(gobj, 6, Intangible);
    ftColl_8007B128(gobj, 0x10, Intangible);
    ftColl_8007B128(gobj, 7, Intangible);
    ftColl_8007B128(gobj, 0x13, Intangible);
    ftColl_8007B128(gobj, 0xA, Intangible);
    ftCommon_8007F5CC(gobj, 0);
}

static void ftKp_SpecialN_80135780_inline_2(Fighter_GObj* gobj)
{
    ftParts_80074B0C(gobj, 0, 0);
    ftColl_8007B0C0(gobj, HurtCapsule_Enabled);
    ftCommon_8007F5CC(gobj, 1);
}

void ftKp_SpecialN_80135780(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (fp->ground_or_air == GA_Ground) {
        if (fp->cmd_vars[2] & 1) {
            ftKp_SpecialN_80135780_inline(gobj);
            fp->x221E_b4 = false;
        } else {
            ftKp_SpecialN_80135780_inline_2(gobj);
            fp->x221E_b4 = true;
        }
    } else {
        if (fp->cmd_vars[1] & 1) {
            ftKp_SpecialN_80135780_inline(gobj);
            fp->x221E_b4 = false;
        } else {
            ftKp_SpecialN_80135780_inline_2(gobj);
            fp->x221E_b4 = true;
        }
    }
}
