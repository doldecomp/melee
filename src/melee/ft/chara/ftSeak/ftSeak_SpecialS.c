#include <melee/ft/chara/ftSeak/ftSeak_SpecialS.h>

#include <common_structs.h>
#include <math.h>
#include <melee/ft/chara/ftNess/ftNess.h>
#include <melee/ft/chara/ftSeak/ftSeak_Init.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftdata.h>
#include <melee/it/code_8027CF30.h>
#include <melee/lb/lbunknown_001.h>

/// @todo Fix common data struct
#define COMMON_DATA_F32 ((f32*) p_ftCommonData)

void ftSeak_80110490(Fighter* fp)
{
    f32 v2, v3, v5, v6, v8;

    v2 = atan2f(fp->input.x624_lstick_y,
                (fp->input.x620_lstick_x * fp->facing_dir));

    if (v2 < 0)
        v2 += (f32) M_PI * 2;

    v3 = v2 * RAD_TO_DEG;

    if (v3 < 0)
        v3 = 0;

    if (v3 > 359)
        v3 = 359;

    v5 = v3 - fp->x2358_stateVar7;

    if (v5 > 180)
        v5 -= 360;
    else if (v5 < -180)
        v5 += 360;

    v6 = v5 * COMMON_DATA_F32[275] + fp->x2358_stateVar7;

    if (v6 > 360)
        v6 -= 360;
    else if (v6 < 0)
        v6 += 360;

    fp->x2358_stateVar7 = v6;

    v8 = sqrtf(fp->input.x620_lstick_x * fp->input.x620_lstick_x +
               fp->input.x624_lstick_y * fp->input.x624_lstick_y);

    if (v8 > 1)
        v8 = 1;

    fp->x2354_stateVar6_f32 +=
        COMMON_DATA_F32[275] * (v8 - fp->x2354_stateVar6_f32);
}

void ftSeak_80110610(HSD_GObj* fighter_gobj, s32 arg1, f32 arg2)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    UNK_T* items = fp->x10C_ftData->x48_items;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[4];
#endif

    int* item;

    if (arg1 == 305)
        item = items[4];
    else
        item = items[5];

    ftSeak_80110490(fp);

    {
        f32 f = 0.0556F * fp->x2358_stateVar7 + 4;

        if (fp->x2354_stateVar6_f32) {
            HSD_JObj* bone = fp->x8AC_animSkeleton;
            func_8006F4C8(fp, 1, func_80085E50(fp, arg1));
            func_80070710(bone, f);
            func_8006FB88(fp, 1, fp->x108_costume_joint->child);
            HSD_JObjAnimAll(bone);

            if (fp->x2354_stateVar6_f32 < 1) {
                func_80070108(fp, 1, item[2], 1 - fp->x2354_stateVar6_f32,
                              fp->x2354_stateVar6_f32);
            }

            if (arg2 < 1) {
                func_8006FE9C(fp, 1, arg2, 1 - arg2);
                return;
            }

            func_8006FF74(fp, 1);
            return;
        }
    }

    if (arg2 < 1) {
        func_80070010(fp, 1, item[2], arg2, 1 - arg2);
        return;
    }

    func_8006FA58(fp, 1, item[2]);
}

void ftSeak_80110788(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    fp->sa.seak.lstick_delta.x =
        fp->input.x620_lstick_x - fp->input.x628_lstick_x2;
    fp->sa.seak.lstick_delta.y =
        fp->input.x624_lstick_y - fp->input.x62C_lstick_y2;

    {
        s32 stateVar3 = fp->x2348_stateVar3_s32;

        if (stateVar3 > 0) {
            fp->x2348_stateVar3_s32 = stateVar3 - 1;
        } else {
            const enum_t flags = (1 << 3) | (1 << 6) | (1 << 8) | (1 << 9) |
                                 (1 << 10) | (1 << 11) | (1 << 12) | (1 << 18);

            if ((fp->facing_dir == +1 && fp->sa.seak.lstick_delta.x > +0.3F) ||
                (fp->facing_dir == -1 && fp->sa.seak.lstick_delta.x < -0.3F))
            {
                func_80088148(fp, flags, 127, 64);
                fp->x2348_stateVar3_s32 = 6;
            } else if (fp->sa.seak.lstick_delta.y > 0.5F) {
                func_80088148(fp, flags, 127, 64);
                fp->x2348_stateVar3_s32 = 12;
            }
        }
    }

    {
        s32 stateVar4 = fp->x234C_stateVar4_s32;
        if (stateVar4 > 0) {
            fp->x234C_stateVar4_s32 = stateVar4 - 1;
        } else {
            const enum_t flags = (1 << 0) | (1 << 1) | (1 << 3) | (1 << 6) |
                                 (1 << 8) | (1 << 9) | (1 << 10) | (1 << 11) |
                                 (1 << 12) | (1 << 18);

            if ((fp->facing_dir == +1 && fp->sa.seak.lstick_delta.x < -0.3F &&
                 fp->input.x620_lstick_x < 0) ||
                (fp->facing_dir == -1 && fp->sa.seak.lstick_delta.x > +0.3F &&
                 fp->input.x620_lstick_x > 0))
            {
                func_80088148(fp, flags, 127, 64);
                fp->x234C_stateVar4_s32 = 6;
            }
        }
    }

    {
        HSD_GObj* item_gobj = fp->sa.seak.x2234;

        if (item_gobj == NULL)
            return;

        {
            f32 left_stick_x = fp->input.x620_lstick_x;
            Item* item_data = item_gobj->user_data;
            Article* article = item_data->xC4_article_data;
            itChainSegment* chainSegment = article->x4_specialAttributes;

            if (left_stick_x < 0)
                left_stick_x = -left_stick_x;

            if (left_stick_x < chainSegment->x48) {
                f32 left_stick_y = fp->input.x624_lstick_y;

                if (fp->input.x624_lstick_y < 0)
                    left_stick_y = -left_stick_y;

                if (left_stick_y < chainSegment->x48) {
                    f32 mul = 0.5F;
                    fp->sa.seak.lstick_delta.x *= mul;
                    fp->sa.seak.lstick_delta.y *= mul;
                }
            }
        }
    }
}

void ftSeak_8011097C(HSD_GObj* fighter_gobj)
{
    return;
}

void ftSeak_UpdateHitboxes(HSD_GObj* fighter_gobj, Vec3* new_pos, s32 hitbox_id)
{
    if (fighter_gobj == NULL)
        return;

    {
        Fighter* fp = GET_FIGHTER(fighter_gobj);

        if (!fp->x2200_ftcmd_var0)
            return;

        fp->sa.seak.x2238[hitbox_id] = *new_pos;

        if (new_pos->x != 0 || new_pos->y != 0) {
            func_8007B8A8(&fp->x914[hitbox_id], new_pos);

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

void ftSeak_ZeroHitboxPositions(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
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

void ftSeak_80110AEC(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    int i;

    for (i = 0; i < 4; i++)
        lbColl_80008434(&fp->x914[i]);

    {
        Fighter* fp_2 = GET_FIGHTER(fighter_gobj);

        /// @todo The inlines in this file are wrong; this block should be
        ///       #ftSeak_ZeroHitboxPositions.
        for (i = 0; i < 4; i++) {
            fp_2->x914[i].x58.x = 0;
            fp_2->x914[i].x58.y = 0;
            fp_2->x914[i].x58.z = 0;
            fp_2->x914[i].x4C.x = 0;
            fp_2->x914[i].x4C.y = 0;
            fp_2->x914[i].x4C.z = 0;
        }

        fp->x2219_flag.bits.b3 = true;
    }
}

inline void ftSeakSpecialS_LoopChainHitCollisions(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    int i;

    for (i = 0; i < (ssize_t) ARRAY_SIZE(fp->x914); i++) {
        lbColl_80008440(&fp->x914[i]);
        lbColl_80008428(&fp->x914[i]);
    }

    ftSeak_ZeroHitboxPositions(fighter_gobj);
}

inline void ftSeakSpecialS_LoopChainHitActivate(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    int i;

    for (i = 0; i < (ssize_t) ARRAY_SIZE(fp->x914); i++)
        lbColl_80008434(&fp->x914[i]);

    ftSeak_ZeroHitboxPositions(fighter_gobj);
    fp->x2219_flag.bits.b3 = true;
}

inline f32 sumOfSquares(f32 a, f32 b)
{
    f32 c;

    a = a * a;
    c = b * b;

    return a + c;
}

void ftSeak_80110BCC(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    HSD_GObj* item_gobj = fp->sa.seak.x2234;
    ftSeakAttributes* specialAttributes = fp->x2D4_specialAttributes;

    if (item_gobj == NULL)
        return;

    {
        Item* item_data = item_gobj->user_data;
        itChainSegment* chain =
            item_data->xC4_article_data->x4_specialAttributes;

        {
            f32 sums_of_squares[4];
            int i;
            for (i = 0; i < (ssize_t) ARRAY_SIZE(sums_of_squares); i++) {
                f32 x = fp->sa.seak.x2238[i].x - fp->sa.seak.x2268[i].x;
                f32 y = fp->sa.seak.x2238[i].y - fp->sa.seak.x2268[i].y;

                sums_of_squares[i] = sumOfSquares(x, y);

                fp->sa.seak.x2268[i].x = fp->sa.seak.x2238[i].x;
                fp->sa.seak.x2268[i].y = fp->sa.seak.x2238[i].y;
            }

            if (fp->seakVars.SpecialS.x235C > 0) {
                fp->seakVars.SpecialS.x235C--;

                if (fp->seakVars.SpecialS.x235C == 0)
                    ftSeakSpecialS_LoopChainHitCollisions(fighter_gobj);
            }

            {
                f32 chain_val = chain->x4C;
                f32 chain_val_sq = chain_val * chain_val;

                if (sums_of_squares[0] > chain_val_sq ||
                    sums_of_squares[1] > chain_val_sq ||
                    sums_of_squares[2] > chain_val_sq ||
                    sums_of_squares[3] > chain_val_sq)
                {
                    if (fp->seakVars.SpecialS.x235C <= 0) {
                        fp->seakVars.SpecialS.x235C = specialAttributes->x18;
                        ftSeakSpecialS_LoopChainHitActivate(fighter_gobj);
                    }
                } else {
                    s32 var = fp->seakVars.SpecialS.x2360;
                    if (var > 0) {
                        fp->seakVars.SpecialS.x2360--;
                    } else {
                        fp->seakVars.SpecialS.x235C = 0;
                        ftSeakSpecialS_LoopChainHitCollisions(fighter_gobj);
                    }
                }
            }
        }
    }
}

void ftSeak_80110E4C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    ftSeak_ChainSomething(fighter_gobj);

    fp->sa.seak.x2234 = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

void ftSeak_CheckAndDestroyChain(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    if (fp->sa.seak.x2234 == NULL)
        return;

    func_802BB20C(fp->sa.seak.x2234);

    fp = fighter_gobj->user_data;

    ftSeak_ChainSomething(fighter_gobj);

    fp->sa.seak.x2234 = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

void ftSeak_80110EE8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (fp->sa.seak.x2234)
        func_802BAEEC(fp->sa.seak.x2234);
}

void ftSeak_ChainSomething(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (fp->sa.seak.x2234) {
        func_802BAF0C(fp->sa.seak.x2234);
        fp->seakVars.SpecialS.x2360 = 2;
    }
}

f32 ftSeak_80110F58(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    return fp->input.x620_lstick_x;
}

f32 ftSeak_80110F64(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    return fp->input.x624_lstick_y;
}

void ftSeak_80110F70(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    fp->x2200_ftcmd_var0 = 0;

    fp->x2340_stateVar1 = 0;
    fp->x2344_stateVar2 = 0;
    fp->x2348_stateVar3 = 0;
    fp->x234C_stateVar4 = 0;

    {
        f32 var = 0.0;

        fp->x2350_stateVar5_f32 = var;
        fp->x2358_stateVar7 = 4.0;
        fp->x2354_stateVar6_f32 = var;

        fp->x235C_u32 = 0;
        fp->x2360_u32 = 0;
        fp->sa.seak.x2234 = 0;

        {
            int i;
            for (i = 0; i < 4; i++) {
                fp->sa.seak.x2238[i].z = var;
                fp->sa.seak.x2238[i].y = var;
                fp->sa.seak.x2238[i].x = var;

                fp->sa.seak.x2268[i].z = var;
                fp->sa.seak.x2268[i].y = var;
                fp->sa.seak.x2268[i].x = var;
            }
        }

        fp->sa.seak.lstick_delta.z = var;
        fp->sa.seak.lstick_delta.y = var;
        fp->sa.seak.lstick_delta.x = var;
    }

    fp->x2222_flag.bits.b2 = true;
    fp->cb.x21BC_callback_Accessory4 = &ftSeak_8011097C;
}

void ftSeak_SpecialS_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, 349, 0, NULL, 0.0, 1, 0);
    func_8006EBA4(fighter_gobj);
    ftSeak_80110F70(fighter_gobj);
}

void ftSeak_SpecialAirS_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    fp->x80_self_vel.y = 0;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 352, 0, NULL, 0.0, 1, 0);
    func_8006EBA4(fighter_gobj);
    ftSeak_80110F70(fighter_gobj);
}

bool ftSeak_SpecialS_CheckInitChain(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused0[4];
#endif

    Vec3 vec0;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused1[4];
#endif

    Vec3 vec1;

    Fighter* fp = fighter_gobj->user_data;
    ftSeakAttributes* specialAttributes = fp->x2D4_specialAttributes;
    fp->x2340_stateVar1 += 1;

    /// @todo Probably an inline.
    if (fp->x2340_stateVar1 == specialAttributes->x1C) {
        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 unused2[12];
#endif
        Fighter* fp2 = fighter_gobj->user_data;

        func_8000B1CC(fp2->x5E8_fighterBones[26].x0_jobj, NULL, &vec1);

        fp2->sa.seak.x2234 =
            func_802BB290(fighter_gobj, &vec1, fp2->facing_dir);

        fp2->x1984_heldItemSpec = fp2->sa.seak.x2234;

        if (fp2->sa.seak.x2234 != NULL) {
            fp2->cb.x21E4_callback_OnDeath2 = &ftSeak_80110198;
            fp2->cb.x21DC_callback_OnTakeDamage = &ftSeak_80110198;
        }

        fp2->cb.x21D4_callback_EnterHitlag = &ftSeak_80110EE8;
        fp2->cb.x21D8_callback_ExitHitlag = &ftSeak_ChainSomething;
        fp->seakVars.SpecialS.x235C = specialAttributes->x18;

        if (fp->sa.seak.x2234 == NULL) {
            if (fp->xE0_ground_or_air == GA_Air)
                func_800CC730(fighter_gobj);
            else
                func_8008A2BC(fighter_gobj);
        }
    }

    if (fp->x2340_stateVar1 == specialAttributes->x1C + 1) {
        static Vec3 const vec0_init = { 1.8, 0, 0 };

        vec0 = vec0_init;
        {
            HSD_GObj* item_gobj = fp->sa.seak.x2234;
            Item* item_data = item_gobj->user_data;
            Article* article = item_data->xC4_article_data;
            itChainSegment* chainSegment = article->x4_specialAttributes;

            vec0.x = chainSegment->x50;

            {
                f32 x;
                x = vec0.x;
                vec0.x *= item_data->facing_dir;
                func_802BCFC4(item_gobj, &vec0.x, chainSegment, item_data, x);
            }
        }
    }

    if (fp->x2340_stateVar1 > specialAttributes->x20)
        return true;

    return false;
}

void ftSeak_SpecialS_Anim(HSD_GObj* fighter_gobj)
{
    if (ftSeak_SpecialS_CheckInitChain(fighter_gobj))
        ftSeak_80111830(fighter_gobj);
}

void ftSeak_80111308(HSD_GObj* fighter_gobj)
{
    if (ftSeak_SpecialS_CheckInitChain(fighter_gobj))
        ftSeak_80111988(fighter_gobj);
}

void ftSeak_80111344(HSD_GObj* fighter_gobj)
{
    return;
}

void ftSeak_80111348(HSD_GObj* fighter_gobj)
{
    return;
}

void ftSeak_8011134C(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

void ftSeak_8011136C(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    attr* fighter_attr = &fp->x110_attr;

    if (fp->x2200_ftcmd_var0 != 0) {
        func_8007D494(fp, fighter_attr->x16C_Gravity,
                      fighter_attr->x170_TerminalVelocity);
    }

    func_8007CE94(fp, fighter_attr->x180_AerialFriction);
}

void ftSeak_801113C8(HSD_GObj* fighter_gobj)
{
    if (!func_800827A0(fighter_gobj))
        ftSeak_80111440(fighter_gobj);
}

void ftSeak_80111404(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj))
        ftSeak_801114E4(fighter_gobj);
}

static enum_t const transition_flags =
    FIGHTER_HIT_NOUPDATE | FIGHTER_MATANIM_NOUPDATE | FIGHTER_COLANIM_NOUPDATE |
    FIGHTER_CMD_UPDATE | FIGHTER_ITEMVIS_NOUPDATE | FIGHTER_SKIP_UNK_0x2222 |
    FIGHTER_MODELPART_VIS_NOUPDATE | FIGHTER_MODEL_FLAG_NOUPDATE |
    FIGHTER_UNK_0x2227;

void ftSeak_80111440(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    func_8007D5D4(fp);
    {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 352, transition_flags,
                                           NULL, fp->x894_currentAnimFrame, 1,
                                           0);
    }

    {
        Fighter* fp2 = GET_FIGHTER(fighter_gobj);

        if (fp2->sa.seak.x2234 != NULL) {
            fp2->cb.x21E4_callback_OnDeath2 = &ftSeak_80110198;
            fp2->cb.x21DC_callback_OnTakeDamage = &ftSeak_80110198;
        }

        fp2->cb.x21BC_callback_Accessory4 = &ftSeak_8011097C;
        fp2->cb.x21D4_callback_EnterHitlag = &ftSeak_80110EE8;
        fp2->cb.x21D8_callback_ExitHitlag = &ftSeak_ChainSomething;
    }
}

void ftSeak_801114E4(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 349, transition_flags,
                                       NULL, fp->x894_currentAnimFrame, 1.0,
                                       0.0);

    {
        Fighter* fp2 = GET_FIGHTER(fighter_gobj);

        if (fp2->sa.seak.x2234 != NULL) {
            fp2->cb.x21E4_callback_OnDeath2 = &ftSeak_80110198;
            fp2->cb.x21DC_callback_OnTakeDamage = &ftSeak_80110198;
        }

        fp2->cb.x21BC_callback_Accessory4 = &ftSeak_8011097C;
        fp2->cb.x21D4_callback_EnterHitlag = &ftSeak_80110EE8;
        fp2->cb.x21D8_callback_ExitHitlag = &ftSeak_ChainSomething;
    }
}

void ftSeak_80111588(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[16];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSeakAttributes* specialAttributes = fp->x2D4_specialAttributes;

    ftSeak_80110BCC(fighter_gobj);

    fp->x2340_stateVar1 += 1;

    {
        bool result;
        if (fp->x2340_stateVar1 > specialAttributes->x14 &&
            fp->x2344_stateVar2_s32)
        {
            fp->x2344_stateVar2_s32 = false;
            result = true;
        } else {
            result = false;
        }

        if (result) {
            ftSeak_80111DF8(fighter_gobj);
            return;
        }
    }

    ftSeak_80110610(fighter_gobj, 305, 1);
}

void ftSeak_80111648(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[16];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSeakAttributes* specialAttributes = fp->x2D4_specialAttributes;

    ftSeak_80110BCC(fighter_gobj);
    fp->x2340_stateVar1 += 1;

    {
        bool result;
        if (fp->x2340_stateVar1 > specialAttributes->x14 &&
            fp->x2344_stateVar2_s32)
        {
            fp->x2344_stateVar2_s32 = false;
            result = true;
        } else {
            result = false;
        }

        if (result) {
            ftSeak_80111EB4(fighter_gobj);
            return;
        }
    }

    ftSeak_80110610(fighter_gobj, 308, 1);
}

void ftSeak_80111708(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (FLAGS_NONE(fp->input.x65C_heldInputs, HSD_BUTTON_B))
        fp->x2344_stateVar2_s32 = true;

    ftSeak_80110788(fighter_gobj);
}

void ftSeak_80111740(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (FLAGS_NONE(fp->input.x65C_heldInputs, HSD_BUTTON_B))
        fp->x2344_stateVar2_s32 = true;

    ftSeak_80110788(fighter_gobj);
}

void ftSeak_80111778(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

void ftSeak_80111798(HSD_GObj* fighter_gobj)
{
    func_80084EEC(fighter_gobj);
}

void ftSeak_801117B8(HSD_GObj* fighter_gobj)
{
    if (!func_800827A0(fighter_gobj))
        ftSeak_80111DF8(fighter_gobj);
}

void ftSeak_801117F4(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj))
        ftSeak_80111EB4(fighter_gobj);
}

void ftSeak_80111830(HSD_GObj* fighter_gobj)
{
    /// @todo Split into two functions, one with @var fp and one with @var fp2
    Vec3 vec0;
    Vec3 vec1;
    Fighter* fp2;

    Fighter* fp = fighter_gobj->user_data;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 350, 8, NULL, 0.0, 1, 0);
    ftSeak_80110610(fighter_gobj, 305, 0);

    fp2 = fighter_gobj->user_data;
    fp2->x2340_stateVar1 = 0;

    ftSeak_80110AEC(fighter_gobj);

    if (fp2->sa.seak.x2234 != NULL) {
        fp2->cb.x21E4_callback_OnDeath2 = &ftSeak_80110198;
        fp2->cb.x21DC_callback_OnTakeDamage = &ftSeak_80110198;
    }

    fp2->x2222_flag.bits.b2 = true;
    fp2->cb.x21BC_callback_Accessory4 = &ftSeak_8011097C;
    fp2->cb.x21D4_callback_EnterHitlag = &ftSeak_80110EE8;
    fp2->cb.x21D8_callback_ExitHitlag = &ftSeak_ChainSomething;

    {
        f32 ecb_top;
        f32 ecb_bot;
        vec0.x = 0.0;
        ecb_top = fp->x6F0_collData.xA4_ecbCurrCorrect.top.y;
        ecb_bot = fp->x6F0_collData.xA4_ecbCurrCorrect.bottom.y;
        vec0.y = 0.5F * (ecb_top + ecb_bot);
        vec0.z = 0.0;
        vec0.x += fp->xB0_pos.x;
        vec0.y += fp->xB0_pos.y;
        vec0.z += fp->xB0_pos.z;

        func_8000B1CC(fp->x5E8_fighterBones[26].x0_jobj, NULL, &vec1);

        {
            s32 flags =
                ftNess_YoyoCheckEnvColl(fighter_gobj, &vec0, &vec1, 0.5F);

            if (flags != FLAGS_ZERO)
                ftSeak_80111DF8(fighter_gobj);
        }
    }
}

void ftSeak_80111988(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, 353, 8, NULL, 0.0, 1.0,
                                       0.0);
    ftSeak_80110610(fighter_gobj, 308, 0.0);

    {
        Fighter* fp = fighter_gobj->user_data;
        fp->x2340_stateVar1 = 0;

        ftSeak_80110AEC(fighter_gobj);

        if (fp->sa.seak.x2234 != NULL) {
            fp->cb.x21E4_callback_OnDeath2 = &ftSeak_80110198;
            fp->cb.x21DC_callback_OnTakeDamage = &ftSeak_80110198;
        }

        fp->x2222_flag.bits.b2 = true;
        fp->cb.x21BC_callback_Accessory4 = &ftSeak_8011097C;
        fp->cb.x21D4_callback_EnterHitlag = &ftSeak_80110EE8;
        fp->cb.x21D8_callback_ExitHitlag = &ftSeak_ChainSomething;
    }
}

void ftSeak_80111A48(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[36];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSeakAttributes* specialAttributes = fp->x2D4_specialAttributes;
    fp->x2340_stateVar1 += 1;

    {
        s32 temp_r3 = fp->x2340_stateVar1;
        f32 temp_f1 = specialAttributes->x28;

        HSD_GObj* item_gobj;

        if (temp_r3 < temp_f1) {
            item_gobj = fp->sa.seak.x2234;

            if (temp_r3 == specialAttributes->x24)
                func_802BCF84(item_gobj);

            /// @todo Split inner function
            goto inner_ret;
        }

        if (temp_r3 == temp_f1) {
            item_gobj = fp->sa.seak.x2234;
            func_802BB20C(item_gobj);
        } else {
        inner_ret:
            ftSeak_80110BCC(fighter_gobj);
        }
    }

    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        func_8008A2BC(fighter_gobj);
}

void ftSeak_80111B1C(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[36];
#endif

    Fighter* fp = fighter_gobj->user_data;
    ftSeakAttributes* specialAttributes = fp->x2D4_specialAttributes;
    fp->x2340_stateVar1 += 1;

    {
        s32 stateVar1 = fp->x2340_stateVar1;
        f32 temp_f1 = specialAttributes->x28;

        HSD_GObj* item_gobj;

        if (stateVar1 < temp_f1) {
            item_gobj = fp->sa.seak.x2234;
            if (stateVar1 == specialAttributes->x24) {
                func_802BCF84(item_gobj);
            }
            goto inner_ret;
        }
        if (stateVar1 == temp_f1) {
            item_gobj = fp->sa.seak.x2234;
            func_802BB20C(item_gobj);
        } else {
        inner_ret:
            ftSeak_80110BCC(fighter_gobj);
        }

        if (!ftAnim_IsFramesRemaining(fighter_gobj))
            func_800CC730(fighter_gobj);
    }
}

void ftSeak_80111BF0(HSD_GObj* fighter_gobj)
{
    return;
}

void ftSeak_80111BF4(HSD_GObj* fighter_gobj)
{
    return;
}

void ftSeak_80111BF8(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

void ftSeak_80111C18(HSD_GObj* fighter_gobj)
{
    func_80084EEC(fighter_gobj);
}

void ftSeak_80111C38(HSD_GObj* fighter_gobj)
{
    if (!func_800827A0(fighter_gobj))
        ftSeak_80111CB0(fighter_gobj);
}

// Collision_SheikChainAir
void ftSeak_80111C74(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj))
        ftSeak_80111D54(fighter_gobj);
}

void ftSeak_80111CB0(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_8007D5D4(fp);

    Fighter_ActionStateChange_800693AC(fighter_gobj, 354, transition_flags,
                                       NULL, fp->x894_currentAnimFrame, 1, 0);

    {
        Fighter* fp2 = fighter_gobj->user_data;

        if (fp2->sa.seak.x2234 != NULL) {
            fp2->cb.x21E4_callback_OnDeath2 = &ftSeak_80110198;
            fp2->cb.x21DC_callback_OnTakeDamage = &ftSeak_80110198;
        }

        fp2->cb.x21BC_callback_Accessory4 = &ftSeak_8011097C;
        fp2->cb.x21D4_callback_EnterHitlag = &ftSeak_80110EE8;
        fp2->cb.x21D8_callback_ExitHitlag = &ftSeak_ChainSomething;
    }
}

// AS_SheikRetractChainGround
void ftSeak_80111D54(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_8007D7FC(fp);

    Fighter_ActionStateChange_800693AC(fighter_gobj, 351, transition_flags,
                                       NULL, fp->x894_currentAnimFrame, 1, 0);

    {
        Fighter* fp2 = GET_FIGHTER(fighter_gobj);

        if (fp2->sa.seak.x2234 != NULL) {
            fp2->cb.x21E4_callback_OnDeath2 = &ftSeak_80110198;
            fp2->cb.x21DC_callback_OnTakeDamage = &ftSeak_80110198;
        }

        fp2->cb.x21BC_callback_Accessory4 = &ftSeak_8011097C;
        fp2->cb.x21D4_callback_EnterHitlag = &ftSeak_80110EE8;
        fp2->cb.x21D8_callback_ExitHitlag = &ftSeak_ChainSomething;
    }
}

void ftSeak_80111DF8(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, 351, 8, NULL, 0, 1, 0);

    {
        Fighter* fp = GET_FIGHTER(fighter_gobj);
        fp->x2340_stateVar1 = 0;

        if (fp->seakVars.SpecialS.x235C != 0)
            ftSeak_80110AEC(fighter_gobj);

        if (fp->sa.seak.x2234 != NULL) {
            fp->cb.x21E4_callback_OnDeath2 = &ftSeak_80110198;
            fp->cb.x21DC_callback_OnTakeDamage = &ftSeak_80110198;
        }

        fp->x2222_flag.bits.b2 = true;
        fp->cb.x21BC_callback_Accessory4 = &ftSeak_8011097C;
        fp->cb.x21D4_callback_EnterHitlag = &ftSeak_80110EE8;
        fp->cb.x21D8_callback_ExitHitlag = &ftSeak_ChainSomething;
    }
}

void ftSeak_80111EB4(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, 354, 8, NULL, 0, 1, 0);

    {
        Fighter* fp = fighter_gobj->user_data;
        fp->x2340_stateVar1 = 0;

        if (fp->seakVars.SpecialS.x235C != 0)
            ftSeak_80110AEC(fighter_gobj);

        if (fp->sa.seak.x2234 != NULL) {
            fp->cb.x21E4_callback_OnDeath2 = &ftSeak_80110198;
            fp->cb.x21DC_callback_OnTakeDamage = &ftSeak_80110198;
        }

        fp->x2222_flag.bits.b2 = true;
        fp->cb.x21BC_callback_Accessory4 = &ftSeak_8011097C;
        fp->cb.x21D4_callback_EnterHitlag = &ftSeak_80110EE8;
        fp->cb.x21D8_callback_ExitHitlag = &ftSeak_ChainSomething;
    }
}

bool ftSeak_80111F70(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (fighter_gobj != NULL) {
        if (fp->sa.seak.x2230 != 0)
            return false;

        return true;
    }

    return true;
}

int ftSeak_80111FA0(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fighter_gobj != NULL)
        return fp->sa.seak.x222C;

    return 0;
}
