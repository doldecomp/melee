#include "ftSeak/ftSk_SpecialS.h"

#include <placeholder.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftNess/ftNs_AttackHi4.h"
#include "ftSeak/ftSk_Init.h"
#include "ftSeak/types.h"
#include "it/items/itseakchain.h"
#include "it/types.h"

#include "lb/forward.h"

#include "lb/lb_00B0.h"
#include "lb/lbcollision.h"

#include <common_structs.h>
#include <math.h>
#include <math_ppc.h>
#include <trigf.h>
#include <baselib/jobj.h>

/// @todo Fix common data struct
#define COMMON_DATA_F32 ((float*) p_ftCommonData)

void ftSk_SpecialS_80110490(Fighter* fp)
{
    float v2, v3, v5, v6, v8;

    v2 = atan2f(fp->input.lstick.y, (fp->input.lstick.x * fp->facing_dir));

    if (v2 < 0) {
        v2 += (float) M_PI * 2;
    }

    v3 = v2 * rad_to_deg;

    if (v3 < 0) {
        v3 = 0;
    }

    if (v3 > 359) {
        v3 = 359;
    }

    v5 = v3 - fp->mv.sk.specials.x18;

    if (v5 > 180) {
        v5 -= 360;
    } else if (v5 < -180) {
        v5 += 360;
    }

    v6 = v5 * COMMON_DATA_F32[275] + fp->mv.sk.specials.x18;

    if (v6 > 360) {
        v6 -= 360;
    } else if (v6 < 0) {
        v6 += 360;
    }

    fp->mv.sk.specials.x18 = v6;

    v8 = sqrtf(fp->input.lstick.x * fp->input.lstick.x +
               fp->input.lstick.y * fp->input.lstick.y);

    if (v8 > 1) {
        v8 = 1;
    }

    fp->mv.sk.specials.x14 +=
        COMMON_DATA_F32[275] * (v8 - fp->mv.sk.specials.x14);
}

void ftSk_SpecialS_80110610(HSD_GObj* gobj, s32 arg1, float arg2)
{
    Fighter* fp = GET_FIGHTER(gobj);
    UNK_T* items = fp->ft_data->x48_items;

    u8 _[4];

    HSD_Joint** item;

    if (arg1 == 305) {
        item = items[4];
    } else {
        item = items[5];
    }

    ftSk_SpecialS_80110490(fp);

    {
        float f = 0.0556F * fp->mv.sk.specials.x18 + 4;

        if (fp->mv.sk.specials.x14) {
            HSD_JObj* bone = fp->x8AC_animSkeleton;
            ftAnim_8006F4C8(fp, 1, ftData_80085E50(fp, arg1));
            ftAnim_80070710(bone, f);
            ftAnim_8006FB88(fp, 1, fp->x108_costume_joint->child);
            HSD_JObjAnimAll(bone);

            if (fp->mv.sk.specials.x14 < 1) {
                ftAnim_80070108(fp, 1, item[2], 1 - fp->mv.sk.specials.x14,
                                fp->mv.sk.specials.x14);
            }

            if (arg2 < 1) {
                ftAnim_8006FE9C(fp, 1, arg2, 1 - arg2);
                return;
            }

            ftAnim_8006FF74(fp, 1);
            return;
        }
    }

    if (arg2 < 1) {
        ftAnim_80070010(fp, 1, item[2], arg2, 1 - arg2);
        return;
    }

    ftAnim_8006FA58(fp, 1, item[2]);
}

void ftSk_SpecialS_80110788(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->fv.sk.lstick_delta.x = fp->input.lstick.x - fp->input.lstick1.x;
    fp->fv.sk.lstick_delta.y = fp->input.lstick.y - fp->input.lstick1.y;

    {
        s32 stateVar3 = fp->mv.sk.specials.x8;

        if (stateVar3 > 0) {
            fp->mv.sk.specials.x8 = stateVar3 - 1;
        } else {
            const enum_t flags = (1 << 3) | (1 << 6) | (1 << 8) | (1 << 9) |
                                 (1 << 10) | (1 << 11) | (1 << 12) | (1 << 18);

            if ((fp->facing_dir == +1 && fp->fv.sk.lstick_delta.x > +0.3F) ||
                (fp->facing_dir == -1 && fp->fv.sk.lstick_delta.x < -0.3F))
            {
                ft_PlaySFX(fp, flags, 127, 64);
                fp->mv.sk.specials.x8 = 6;
            } else if (fp->fv.sk.lstick_delta.y > 0.5F) {
                ft_PlaySFX(fp, flags, 127, 64);
                fp->mv.sk.specials.x8 = 12;
            }
        }
    }

    {
        s32 stateVar4 = fp->mv.sk.specials.xC;
        if (stateVar4 > 0) {
            fp->mv.sk.specials.xC = stateVar4 - 1;
        } else {
            const enum_t flags = (1 << 0) | (1 << 1) | (1 << 3) | (1 << 6) |
                                 (1 << 8) | (1 << 9) | (1 << 10) | (1 << 11) |
                                 (1 << 12) | (1 << 18);

            if ((fp->facing_dir == +1 && fp->fv.sk.lstick_delta.x < -0.3F &&
                 fp->input.lstick.x < 0) ||
                (fp->facing_dir == -1 && fp->fv.sk.lstick_delta.x > +0.3F &&
                 fp->input.lstick.x > 0))
            {
                ft_PlaySFX(fp, flags, 127, 64);
                fp->mv.sk.specials.xC = 6;
            }
        }
    }

    {
        HSD_GObj* item_gobj = fp->fv.sk.x8;

        if (item_gobj == NULL) {
            return;
        }

        {
            float left_stick_x = fp->input.lstick.x;
            Item* item_data = item_gobj->user_data;
            Article* article = item_data->xC4_article_data;
            itChainSegment* chainSegment = article->x4_specialAttributes;

            if (left_stick_x < 0) {
                left_stick_x = -left_stick_x;
            }

            if (left_stick_x < chainSegment->x48) {
                float left_stick_y = fp->input.lstick.y;

                if (fp->input.lstick.y < 0) {
                    left_stick_y = -left_stick_y;
                }

                if (left_stick_y < chainSegment->x48) {
                    float mul = 0.5F;
                    fp->fv.sk.lstick_delta.x *= mul;
                    fp->fv.sk.lstick_delta.y *= mul;
                }
            }
        }
    }
}

void ftSk_SpecialS_8011097C(HSD_GObj* gobj)
{
    return;
}

void ftSk_SpecialS_UpdateHitboxes(HSD_GObj* gobj, Vec3* new_pos, s32 hitbox_id)
{
    if (gobj == NULL) {
        return;
    }

    {
        Fighter* fp = GET_FIGHTER(gobj);

        if (!fp->cmd_vars[0]) {
            return;
        }

        fp->fv.sk.xC[hitbox_id] = *new_pos;

        if (new_pos->x != 0 || new_pos->y != 0) {
            ftColl_8007B8A8(&fp->x914[hitbox_id], new_pos);

            fp->x914[hitbox_id].x4C = *new_pos;

            if (fp->x914[hitbox_id].x58.x == 0 &&
                fp->x914[hitbox_id].x58.y == 0 &&
                fp->x914[hitbox_id].x58.z == 0)
            {
                fp->x914[hitbox_id].x58 = *new_pos;
            }
        }
    }
}

void ftSk_SpecialS_ZeroHitboxPositions(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;

    // Zero out the position and last position of 4 hitboxes
    for (i = 0; i < 4; i++) {
        fp->x914[i].x58.x = 0;
        fp->x914[i].x58.y = 0;
        fp->x914[i].x58.z = 0;
        fp->x914[i].x4C.x = 0;
        fp->x914[i].x4C.y = 0;
        fp->x914[i].x4C.z = 0;
    }
}

void ftSk_SpecialS_80110AEC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;

    for (i = 0; i < 4; i++) {
        lbColl_80008434(&fp->x914[i]);
    }

    {
        Fighter* fp_2 = GET_FIGHTER(gobj);

        /// @todo The inlines in this file are wrong; this block should be
        ///       #ftSk_SpecialS_ZeroHitboxPositions.
        for (i = 0; i < 4; i++) {
            fp_2->x914[i].x58.x = 0;
            fp_2->x914[i].x58.y = 0;
            fp_2->x914[i].x58.z = 0;
            fp_2->x914[i].x4C.x = 0;
            fp_2->x914[i].x4C.y = 0;
            fp_2->x914[i].x4C.z = 0;
        }

        fp->x2219_b3 = true;
    }
}

inline void ftSeakSpecialS_LoopChainHitCollisions(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;

    for (i = 0; i < (ssize_t) ARRAY_SIZE(fp->x914); i++) {
        lbColl_80008440(&fp->x914[i]);
        lbColl_80008428(&fp->x914[i]);
    }

    ftSk_SpecialS_ZeroHitboxPositions(gobj);
}

inline void ftSeakSpecialS_LoopChainHitActivate(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;

    for (i = 0; i < (ssize_t) ARRAY_SIZE(fp->x914); i++) {
        lbColl_80008434(&fp->x914[i]);
    }

    ftSk_SpecialS_ZeroHitboxPositions(gobj);
    fp->x2219_b3 = true;
}

inline float sumOfSquares(float a, float b)
{
    float c;

    a = a * a;
    c = b * b;

    return a + c;
}

void ftSk_SpecialS_80110BCC(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    HSD_GObj* item_gobj = fp->fv.sk.x8;
    ftSeakAttributes* specialAttributes = fp->dat_attrs;

    if (item_gobj == NULL) {
        return;
    }

    {
        Item* item_data = item_gobj->user_data;
        itChainSegment* chain =
            item_data->xC4_article_data->x4_specialAttributes;

        {
            float sums_of_squares[4];
            int i;
            for (i = 0; i < (ssize_t) ARRAY_SIZE(sums_of_squares); i++) {
                float x = fp->fv.sk.xC[i].x - fp->fv.sk.x3C[i].x;
                float y = fp->fv.sk.xC[i].y - fp->fv.sk.x3C[i].y;

                sums_of_squares[i] = sumOfSquares(x, y);

                fp->fv.sk.x3C[i].x = fp->fv.sk.xC[i].x;
                fp->fv.sk.x3C[i].y = fp->fv.sk.xC[i].y;
            }

            if (fp->mv.sk.specials.x1C > 0) {
                fp->mv.sk.specials.x1C--;

                if (fp->mv.sk.specials.x1C == 0) {
                    ftSeakSpecialS_LoopChainHitCollisions(gobj);
                }
            }

            {
                float chain_val = chain->x4C;
                float chain_val_sq = chain_val * chain_val;

                if (sums_of_squares[0] > chain_val_sq ||
                    sums_of_squares[1] > chain_val_sq ||
                    sums_of_squares[2] > chain_val_sq ||
                    sums_of_squares[3] > chain_val_sq)
                {
                    if (fp->mv.sk.specials.x1C <= 0) {
                        fp->mv.sk.specials.x1C = specialAttributes->x18;
                        ftSeakSpecialS_LoopChainHitActivate(gobj);
                    }
                } else {
                    s32 var = fp->mv.sk.specials.x20;
                    if (var > 0) {
                        fp->mv.sk.specials.x20--;
                    } else {
                        fp->mv.sk.specials.x1C = 0;
                        ftSeakSpecialS_LoopChainHitCollisions(gobj);
                    }
                }
            }
        }
    }
}

void ftSk_SpecialS_80110E4C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftSk_SpecialS_ChainSomething(gobj);

    fp->fv.sk.x8 = NULL;
    fp->death2_cb = NULL;
    fp->take_dmg_cb = NULL;
}

void ftSk_SpecialS_CheckAndDestroyChain(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    if (fp->fv.sk.x8 == NULL) {
        return;
    }

    it_802BB20C(fp->fv.sk.x8);

    fp = gobj->user_data;

    ftSk_SpecialS_ChainSomething(gobj);

    fp->fv.sk.x8 = NULL;
    fp->death2_cb = NULL;
    fp->take_dmg_cb = NULL;
}

void ftSk_SpecialS_80110EE8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.sk.x8) {
        it_802BAEEC(fp->fv.sk.x8);
    }
}

void ftSk_SpecialS_ChainSomething(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.sk.x8) {
        it_802BAF0C(fp->fv.sk.x8);
        fp->mv.sk.specials.x20 = 2;
    }
}

float ftSk_SpecialS_80110F58(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->input.lstick.x;
}

float ftSk_SpecialS_80110F64(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->input.lstick.y;
}

void ftSk_SpecialS_80110F70(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->cmd_vars[0] = 0;

    fp->mv.sk.specials.x0 = 0;
    fp->mv.sk.specials.x4 = 0;
    fp->mv.sk.specials.x8 = 0;
    fp->mv.sk.specials.xC = 0;

    {
        float var = 0.0;

        fp->mv.sk.specials.x10 = var;
        fp->mv.sk.specials.x18 = 4.0;
        fp->mv.sk.specials.x14 = var;

        fp->mv.sk.specials.x1C = 0;
        fp->mv.sk.specials.x20 = 0;
        fp->fv.sk.x8 = 0;

        {
            int i;
            for (i = 0; i < 4; i++) {
                fp->fv.sk.xC[i].z = var;
                fp->fv.sk.xC[i].y = var;
                fp->fv.sk.xC[i].x = var;

                fp->fv.sk.x3C[i].z = var;
                fp->fv.sk.x3C[i].y = var;
                fp->fv.sk.x3C[i].x = var;
            }
        }

        fp->fv.sk.lstick_delta.z = var;
        fp->fv.sk.lstick_delta.y = var;
        fp->fv.sk.lstick_delta.x = var;
    }

    fp->x2222_b2 = true;
    fp->accessory4_cb = &ftSk_SpecialS_8011097C;
}

void ftSk_SpecialS_Enter(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 349, 0, 0.0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    ftSk_SpecialS_80110F70(gobj);
}

void ftSk_SpecialAirS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.y = 0;

    Fighter_ChangeMotionState(gobj, 352, 0, 0.0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    ftSk_SpecialS_80110F70(gobj);
}

bool ftSk_SpecialS_CheckInitChain(HSD_GObj* gobj)
{
    u8 unused0[4];

    Vec3 vec0;

    u8 unused1[4];

    Vec3 vec1;

    Fighter* fp = gobj->user_data;
    ftSeakAttributes* specialAttributes = fp->dat_attrs;
    fp->mv.sk.specials.x0 += 1;

    /// @todo Probably an inline.
    if (fp->mv.sk.specials.x0 == specialAttributes->x1C) {
        u8 unused2[12];
        Fighter* fp2 = gobj->user_data;

        lb_8000B1CC(fp2->parts[FtPart_L3rdNa].joint, NULL, &vec1);

        fp2->fv.sk.x8 = it_802BB290(gobj, &vec1, fp2->facing_dir);

        fp2->x1984_heldItemSpec = fp2->fv.sk.x8;

        if (fp2->fv.sk.x8 != NULL) {
            fp2->death2_cb = &ftSk_Init_80110198;
            fp2->take_dmg_cb = &ftSk_Init_80110198;
        }

        fp2->pre_hitlag_cb = &ftSk_SpecialS_80110EE8;
        fp2->post_hitlag_cb = &ftSk_SpecialS_ChainSomething;
        fp->mv.sk.specials.x1C = specialAttributes->x18;

        if (fp->fv.sk.x8 == NULL) {
            if (fp->ground_or_air == GA_Air) {
                ftCo_Fall_Enter(gobj);
            } else {
                ft_8008A2BC(gobj);
            }
        }
    }

    if (fp->mv.sk.specials.x0 == specialAttributes->x1C + 1) {
        static Vec3 const vec0_init = { 1.8, 0, 0 };

        vec0 = vec0_init;
        {
            HSD_GObj* item_gobj = fp->fv.sk.x8;
            Item* item_data = item_gobj->user_data;
            Article* article = item_data->xC4_article_data;
            itChainSegment* chainSegment = article->x4_specialAttributes;

            vec0.x = chainSegment->x50;

            {
                float x;
                x = vec0.x;
                vec0.x *= item_data->facing_dir;
                it_802BCFC4(item_gobj, &vec0.x, chainSegment, item_data, x);
            }
        }
    }

    if (fp->mv.sk.specials.x0 > specialAttributes->x20) {
        return true;
    }

    return false;
}

void ftSk_SpecialSStart_Anim(HSD_GObj* gobj)
{
    if (ftSk_SpecialS_CheckInitChain(gobj)) {
        ftSk_SpecialS_80111830(gobj);
    }
}

void ftSk_SpecialAirSStart_Anim(HSD_GObj* gobj)
{
    if (ftSk_SpecialS_CheckInitChain(gobj)) {
        ftSk_SpecialS_80111988(gobj);
    }
}

void ftSk_SpecialSStart_IASA(HSD_GObj* gobj)
{
    return;
}

void ftSk_SpecialAirSStart_IASA(HSD_GObj* gobj)
{
    return;
}

void ftSk_SpecialSStart_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSk_SpecialAirSStart_Phys(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* fighter_attr = &fp->co_attrs;

    if (fp->cmd_vars[0] != 0) {
        ftCommon_Fall(fp, fighter_attr->grav, fighter_attr->terminal_vel);
    }

    ftCommon_ApplyFrictionAir(fp, fighter_attr->aerial_friction);
}

void ftSk_SpecialSStart_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftSk_SpecialS_80111440(gobj);
    }
}

void ftSk_SpecialAirSStart_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftSk_SpecialS_801114E4(gobj);
    }
}

static u32 const transition_flags =
    Ft_MF_SkipHit | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd |
    Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
    Ft_MF_SkipModelFlags | Ft_MF_Unk27;

void ftSk_SpecialS_80111440(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    {
        Fighter_ChangeMotionState(gobj, 352, transition_flags,
                                  fp->cur_anim_frame, 1, 0, NULL);
    }

    {
        Fighter* fp2 = GET_FIGHTER(gobj);

        if (fp2->fv.sk.x8 != NULL) {
            fp2->death2_cb = &ftSk_Init_80110198;
            fp2->take_dmg_cb = &ftSk_Init_80110198;
        }

        fp2->accessory4_cb = &ftSk_SpecialS_8011097C;
        fp2->pre_hitlag_cb = &ftSk_SpecialS_80110EE8;
        fp2->post_hitlag_cb = &ftSk_SpecialS_ChainSomething;
    }
}

void ftSk_SpecialS_801114E4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 349, transition_flags, fp->cur_anim_frame,
                              1.0, 0.0, NULL);

    {
        Fighter* fp2 = GET_FIGHTER(gobj);

        if (fp2->fv.sk.x8 != NULL) {
            fp2->death2_cb = &ftSk_Init_80110198;
            fp2->take_dmg_cb = &ftSk_Init_80110198;
        }

        fp2->accessory4_cb = &ftSk_SpecialS_8011097C;
        fp2->pre_hitlag_cb = &ftSk_SpecialS_80110EE8;
        fp2->post_hitlag_cb = &ftSk_SpecialS_ChainSomething;
    }
}

void ftSk_SpecialS_Anim(HSD_GObj* gobj)
{
    u8 _[16];

    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* specialAttributes = fp->dat_attrs;

    ftSk_SpecialS_80110BCC(gobj);

    fp->mv.sk.specials.x0 += 1;

    {
        bool result;
        if (fp->mv.sk.specials.x0 > specialAttributes->x14 &&
            fp->mv.sk.specials.x4)
        {
            fp->mv.sk.specials.x4 = false;
            result = true;
        } else {
            result = false;
        }

        if (result) {
            ftSk_SpecialS_80111DF8(gobj);
            return;
        }
    }

    ftSk_SpecialS_80110610(gobj, 305, 1);
}

void ftSk_SpecialAirS_Anim(HSD_GObj* gobj)
{
    u8 _[16];

    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* specialAttributes = fp->dat_attrs;

    ftSk_SpecialS_80110BCC(gobj);
    fp->mv.sk.specials.x0 += 1;

    {
        bool result;
        if (fp->mv.sk.specials.x0 > specialAttributes->x14 &&
            fp->mv.sk.specials.x4)
        {
            fp->mv.sk.specials.x4 = false;
            result = true;
        } else {
            result = false;
        }

        if (result) {
            ftSk_SpecialS_80111EB4(gobj);
            return;
        }
    }

    ftSk_SpecialS_80110610(gobj, 308, 1);
}

void ftSk_SpecialS_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->mv.sk.specials.x4 = true;
    }

    ftSk_SpecialS_80110788(gobj);
}

void ftSk_SpecialAirS_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->mv.sk.specials.x4 = true;
    }

    ftSk_SpecialS_80110788(gobj);
}

void ftSk_SpecialS_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSk_SpecialAirS_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftSk_SpecialS_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftSk_SpecialS_80111DF8(gobj);
    }
}

void ftSk_SpecialAirS_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftSk_SpecialS_80111EB4(gobj);
    }
}

void ftSk_SpecialS_80111830(HSD_GObj* gobj)
{
    /// @todo Split into two functions, one with @var fp and one with @var fp2
    Vec3 vec0;
    Vec3 vec1;
    Fighter* fp2;

    Fighter* fp = gobj->user_data;

    Fighter_ChangeMotionState(gobj, 350, 8, 0.0, 1, 0, NULL);
    ftSk_SpecialS_80110610(gobj, 305, 0);

    fp2 = gobj->user_data;
    fp2->mv.sk.specials.x0 = 0;

    ftSk_SpecialS_80110AEC(gobj);

    if (fp2->fv.sk.x8 != NULL) {
        fp2->death2_cb = &ftSk_Init_80110198;
        fp2->take_dmg_cb = &ftSk_Init_80110198;
    }

    fp2->x2222_b2 = true;
    fp2->accessory4_cb = &ftSk_SpecialS_8011097C;
    fp2->pre_hitlag_cb = &ftSk_SpecialS_80110EE8;
    fp2->post_hitlag_cb = &ftSk_SpecialS_ChainSomething;

    {
        float ecb_top;
        float ecb_bot;
        vec0.x = 0.0;
        ecb_top = fp->coll_data.ecb.top.y;
        ecb_bot = fp->coll_data.ecb.bottom.y;
        vec0.y = 0.5F * (ecb_top + ecb_bot);
        vec0.z = 0.0;
        vec0.x += fp->cur_pos.x;
        vec0.y += fp->cur_pos.y;
        vec0.z += fp->cur_pos.z;

        lb_8000B1CC(fp->parts[FtPart_L3rdNa].joint, NULL, &vec1);

        {
            s32 flags =
                ftNs_AttackHi4_YoyoCheckEnvColl(gobj, &vec0, &vec1, 0.5F);

            if (flags != 0) {
                ftSk_SpecialS_80111DF8(gobj);
            }
        }
    }
}

void ftSk_SpecialS_80111988(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 353, 8, 0.0, 1.0, 0.0, NULL);
    ftSk_SpecialS_80110610(gobj, 308, 0.0);

    {
        Fighter* fp = gobj->user_data;
        fp->mv.sk.specials.x0 = 0;

        ftSk_SpecialS_80110AEC(gobj);

        if (fp->fv.sk.x8 != NULL) {
            fp->death2_cb = &ftSk_Init_80110198;
            fp->take_dmg_cb = &ftSk_Init_80110198;
        }

        fp->x2222_b2 = true;
        fp->accessory4_cb = &ftSk_SpecialS_8011097C;
        fp->pre_hitlag_cb = &ftSk_SpecialS_80110EE8;
        fp->post_hitlag_cb = &ftSk_SpecialS_ChainSomething;
    }
}

void ftSk_SpecialSEnd_Anim(HSD_GObj* gobj)
{
    u8 _[36];

    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* specialAttributes = fp->dat_attrs;
    fp->mv.sk.specials.x0 += 1;

    {
        s32 temp_r3 = fp->mv.sk.specials.x0;
        float temp_f1 = specialAttributes->x28;

        HSD_GObj* item_gobj;

        if (temp_r3 < temp_f1) {
            item_gobj = fp->fv.sk.x8;

            if (temp_r3 == specialAttributes->x24) {
                it_802BCF84(item_gobj);
            }

            /// @todo Split inner function
            goto inner_ret;
        }

        if (temp_r3 == temp_f1) {
            item_gobj = fp->fv.sk.x8;
            it_802BB20C(item_gobj);
        } else {
        inner_ret:
            ftSk_SpecialS_80110BCC(gobj);
        }
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftSk_SpecialAirSEnd_Anim(HSD_GObj* gobj)
{
    u8 _[36];

    Fighter* fp = gobj->user_data;
    ftSeakAttributes* specialAttributes = fp->dat_attrs;
    fp->mv.sk.specials.x0 += 1;

    {
        s32 stateVar1 = fp->mv.sk.specials.x0;
        float temp_f1 = specialAttributes->x28;

        HSD_GObj* item_gobj;

        if (stateVar1 < temp_f1) {
            item_gobj = fp->fv.sk.x8;
            if (stateVar1 == specialAttributes->x24) {
                it_802BCF84(item_gobj);
            }
            goto inner_ret;
        }
        if (stateVar1 == temp_f1) {
            item_gobj = fp->fv.sk.x8;
            it_802BB20C(item_gobj);
        } else {
        inner_ret:
            ftSk_SpecialS_80110BCC(gobj);
        }

        if (!ftAnim_IsFramesRemaining(gobj)) {
            ftCo_Fall_Enter(gobj);
        }
    }
}

void ftSk_SpecialSEnd_IASA(HSD_GObj* gobj)
{
    return;
}

void ftSk_SpecialAirSEnd_IASA(HSD_GObj* gobj)
{
    return;
}

void ftSk_SpecialSEnd_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSk_SpecialAirSEnd_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftSk_SpecialSEnd_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftSk_SpecialS_80111CB0(gobj);
    }
}

// Collision_SheikChainAir
void ftSk_SpecialAirSEnd_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftSk_SpecialS_80111D54(gobj);
    }
}

void ftSk_SpecialS_80111CB0(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, 354, transition_flags, fp->cur_anim_frame,
                              1, 0, NULL);

    {
        Fighter* fp2 = gobj->user_data;

        if (fp2->fv.sk.x8 != NULL) {
            fp2->death2_cb = &ftSk_Init_80110198;
            fp2->take_dmg_cb = &ftSk_Init_80110198;
        }

        fp2->accessory4_cb = &ftSk_SpecialS_8011097C;
        fp2->pre_hitlag_cb = &ftSk_SpecialS_80110EE8;
        fp2->post_hitlag_cb = &ftSk_SpecialS_ChainSomething;
    }
}

// AS_SheikRetractChainGround
void ftSk_SpecialS_80111D54(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, 351, transition_flags, fp->cur_anim_frame,
                              1, 0, NULL);

    {
        Fighter* fp2 = GET_FIGHTER(gobj);

        if (fp2->fv.sk.x8 != NULL) {
            fp2->death2_cb = &ftSk_Init_80110198;
            fp2->take_dmg_cb = &ftSk_Init_80110198;
        }

        fp2->accessory4_cb = &ftSk_SpecialS_8011097C;
        fp2->pre_hitlag_cb = &ftSk_SpecialS_80110EE8;
        fp2->post_hitlag_cb = &ftSk_SpecialS_ChainSomething;
    }
}

void ftSk_SpecialS_80111DF8(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 351, 8, 0, 1, 0, NULL);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->mv.sk.specials.x0 = 0;

        if (fp->mv.sk.specials.x1C != 0) {
            ftSk_SpecialS_80110AEC(gobj);
        }

        if (fp->fv.sk.x8 != NULL) {
            fp->death2_cb = &ftSk_Init_80110198;
            fp->take_dmg_cb = &ftSk_Init_80110198;
        }

        fp->x2222_b2 = true;
        fp->accessory4_cb = &ftSk_SpecialS_8011097C;
        fp->pre_hitlag_cb = &ftSk_SpecialS_80110EE8;
        fp->post_hitlag_cb = &ftSk_SpecialS_ChainSomething;
    }
}

void ftSk_SpecialS_80111EB4(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 354, 8, 0, 1, 0, NULL);

    {
        Fighter* fp = gobj->user_data;
        fp->mv.sk.specials.x0 = 0;

        if (fp->mv.sk.specials.x1C != 0) {
            ftSk_SpecialS_80110AEC(gobj);
        }

        if (fp->fv.sk.x8 != NULL) {
            fp->death2_cb = &ftSk_Init_80110198;
            fp->take_dmg_cb = &ftSk_Init_80110198;
        }

        fp->x2222_b2 = true;
        fp->accessory4_cb = &ftSk_SpecialS_8011097C;
        fp->pre_hitlag_cb = &ftSk_SpecialS_80110EE8;
        fp->post_hitlag_cb = &ftSk_SpecialS_ChainSomething;
    }
}

bool ftSk_SpecialS_80111F70(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (gobj != NULL) {
        if (fp->fv.sk.x4 != 0) {
            return false;
        }

        return true;
    }

    return true;
}

int ftSk_SpecialS_80111FA0(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (gobj != NULL) {
        return fp->fv.sk.x0;
    }

    return 0;
}
