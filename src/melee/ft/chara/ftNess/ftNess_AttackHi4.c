#include "lb/forward.h"

#include "ftNess_AttackHi4.h"

#include "ftNess.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"
#include "lb/lbcollision.h"
#include "mp/mpcoll.h"

#include <baselib/gobj.h>

void ftNs_AttackHi4_YoyoUpdateHitPos(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    HitCapsule* hitbox_data = &fp->x914[0];

    if (hitbox_data->state != HitCapsule_Disabled) {
        if (fp->ev.ns.x2230_yoyoHitboxPos.x != 0.0f ||
            fp->ev.ns.x2230_yoyoHitboxPos.y != 0.0f)
        {
            ftColl_8007B8A8(&fp->x914[0], &fp->ev.ns.x2230_yoyoHitboxPos);
        }
    }
};

void ftNs_AttackHi4_YoyoCheckTimedRehit(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2200_ftcmd_var0 == 0) {
        if (fp->sv.ns.attackhi4.yoyoRehitTimer > 0) {
            fp->sv.ns.attackhi4.yoyoRehitTimer--;
            if (fp->sv.ns.attackhi4.yoyoRehitTimer == 0) {
                lbColl_80008440(&fp->x914[0]);
                lbColl_80008434(&fp->x914[0]);
            }
        }
    }
};

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif

// Apply modified damage to D-Smash Yo-Yo hitbox after charge
static void ftNs_AttackHi4_YoyoApplyDamage(f32 unk_float, HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftNessAttributes* ness_attr = fp->x2D4_specialAttributes;
    f32 charge_duration;
    f32 charge_duration2;
    f32 damage_mul;
    f32 final_damage;

    if (unk_float != 0.0f) {
        if (fp->x914->state == HitCapsule_Enabled) {
            // Likely 1/256 but won't match.
            // ((f32) 1 / 256.0) does not match either.
            f32 const mul = 0.0039059999398887157f;

            charge_duration = ness_attr->xAC_YOYO_CHARGE_DURATION;
            charge_duration2 = unk_float / charge_duration;
            damage_mul = ness_attr->xB0_YOYO_DAMAGE_MUL * mul - 1.0f;

            final_damage =
                fp->x914->a_offset.z * (damage_mul * charge_duration2 + 1.0f);

            ftColl_8007ABD0(&fp->x914[0], final_damage, gobj);
        }
    }
};

#ifdef MUST_MATCH
#pragma pop
#endif

static inline void push_ecb(CollData* a, Vec3* b)
{
    a->x1C_vec = a->x4_vec; // old = curr
    a->x4_vec = *b;         // curr = new
}

s32 ftNs_AttackHi4_YoyoCheckEnvColl(HSD_GObj* gobj, Vec3* ECBUnk, Vec3* ECBUnk2,
                            f32 float_unk)
{
    CollData sp34;
    f32 sp1C[6]; // This is probably some kind of struct, but I don't know
                 // which one. ECBVar_UnkFloat doesn't make sense.
    Fighter* fp = gobj->user_data;
    f32 y_scale;
    s32 retval;

    y_scale = float_unk * fp->x34_scale.y;

    sp1C[4] = y_scale;
    sp1C[0] = y_scale;
    sp1C[2] = -y_scale;
    sp1C[1] = -y_scale;
    sp1C[3] = 0.0f;
    sp1C[5] = 0.0f;

    mpColl_80041EE4(&sp34);

    // why do it like this?
    // original code:
    // sp34.x1C_vec = sp34.x4_vec;
    // sp34.x4_vec = ECBUnk->x0_vec;
    // sp34.x1C_vec = sp34.x4_vec;
    // sp34.x4_vec = ECBUnk2->x0_vec;
    // better code:
    // sp34.x1C_vec = ECBUnk->x0_vec;
    // sp34.x4_vec = ECBUnk2->x0_vec;
    // guess: there is a "push ECB" function that handles moving current to
    // old, that got called twice and inlined.
    push_ecb(&sp34, ECBUnk);
    push_ecb(&sp34, ECBUnk2);

    sp34.x34_flags.bits.b1234 = 5;

    mpColl_8004730C(&sp34, &sp1C); // EnvironmentCollisionCheck_NessYoYo

    /// @todo Define flags.
    retval = 0;
    if ((sp34.x134_envFlags & 0x18000) != 0) {
        retval |= 0x8000;
    }

    if ((sp34.x134_envFlags & 0x3F) != 0) {
        retval |= 1;
    }

    if ((sp34.x134_envFlags & 0xFC0) != 0) {
        retval |= 0x40;
    }

    if ((sp34.x134_envFlags & 0x6000) != 0) {
        retval |= 0x2000;
    }

    return retval;
}

/// @todo Remove @c dont_inline.
///       This is probably a result of incorrectly splitting out the function.
#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void ftNs_AttackHi4_YoyoSetUnkPos(HSD_GObj* gobj, Vec3* pos)
{
    Vec3 sp20;
    Vec3 sp14;

    /// @todo #GET_FIGHTER is prevented by @c dont_inline.
    Fighter* fp = gobj->user_data;

    CollData* collData = &fp->x6F0_collData;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (!fp->sv.ns.attackhi4.isPosUpdateMod) {
        lb_8000B1CC(fp->x5E8_fighterBones[0x3D].x0_jobj, NULL, pos);
        return;
    }

    lb_8000B1CC(fp->x5E8_fighterBones[0x3D].x0_jobj, NULL, &sp20);
    lb_8000B1CC(fp->x5E8_fighterBones[0x2].x0_jobj, NULL, &sp14);
    *pos = sp20;
    lbVector_Sub(pos, &sp14);
    lbVector_Rotate(pos, 4,
                    -atan2f(collData->x14C_ground.normal.x,
                            collData->x14C_ground.normal.y));
    lbVector_Add(pos, &sp14);
}
#ifdef MUST_MATCH
#pragma pop
#endif

void ftNs_AttackHi4_YoyoSetHitPos(HSD_GObj* gobj)
{
    Vec3 sp2C;
    Vec3 sp20;
    Vec3 sp14;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    /// @todo Can't move below @c fp.
    CollData* collData;

    Fighter* fp = GET_FIGHTER(gobj);
    collData = &fp->x6F0_collData;

    if (!fp->sv.ns.attackhi4.isPosUpdateMod) {
        lb_8000B1CC(fp->x5E8_fighterBones[0x3D].x0_jobj, NULL, &sp2C);
    } else {
        lb_8000B1CC(fp->x5E8_fighterBones[0x3D].x0_jobj, NULL, &sp14);
        lb_8000B1CC(fp->x5E8_fighterBones[0x2].x0_jobj, NULL, &sp20);
        sp2C = sp14;
        lbVector_Sub(&sp2C, &sp20);
        lbVector_Rotate(&sp2C, 4,
                        -atan2f(collData->x14C_ground.normal.x,
                                collData->x14C_ground.normal.y));
        lbVector_Add(&sp2C, &sp20);
    }

    fp->ev.ns.x2230_yoyoHitboxPos = sp2C;
}

void ftNs_AttackHi4_YoyoSetHitPosUnk(HSD_GObj* gobj, f32 pos_unk)
{
    Vec3 sp3C;
    Vec3 sp30;
    Vec3 sp24;
    Vec3 sp18;
    f32 pos_update;

    /// @todo Can't move below @c fp.
    CollData* collData;

    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    collData = &fp->x6F0_collData;

    if (!fp->sv.ns.attackhi4.isPosUpdateMod) {
        lb_8000B1CC(fp->x5E8_fighterBones[0x3D].x0_jobj, NULL, &sp3C);
    } else {
        lb_8000B1CC(fp->x5E8_fighterBones[0x3D].x0_jobj, NULL, &sp18);
        lb_8000B1CC(fp->x5E8_fighterBones[0x2].x0_jobj, NULL, &sp24);
        sp3C = sp18;
        lbVector_Sub(&sp3C, &sp24);
        lbVector_Rotate(&sp3C, 4,
                        -atan2f(collData->x14C_ground.normal.x,
                                collData->x14C_ground.normal.y));
        lbVector_Add(&sp3C, &sp24);
    }

    sp30 = fp->ev.ns.x2230_yoyoHitboxPos;
    pos_update = 1.0f - pos_unk;
    fp->ev.ns.x2230_yoyoHitboxPos.x =
        (f32) ((sp3C.x * pos_unk) + (sp30.x * pos_update));
    fp->ev.ns.x2230_yoyoHitboxPos.y =
        (f32) ((sp3C.y * pos_unk) + (sp30.y * pos_update));
    fp->ev.ns.x2230_yoyoHitboxPos.z =
        (f32) ((sp3C.z * pos_unk) + (sp30.z * pos_update));
}

bool ftNs_AttackHi4_YoyoCheckNoObstruct(HSD_GObj* gobj)
{
    Vec3 sp20;
    Vec3 sp14;
    f32 ECB_MUL_Y;
    f32 ECB_X;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    ECB_X = 0.0f;
    ECB_MUL_Y = 0.5f;
    sp20.x = ECB_X;
    sp20.y = ECB_MUL_Y * (fp->x6F0_collData.xA4_ecbCurrCorrect.top.y +
                          fp->x6F0_collData.xA4_ecbCurrCorrect.bottom.y);
    sp20.z = ECB_X;
    sp20.x += fp->cur_pos.x;
    sp20.y += fp->cur_pos.y;
    sp20.z += fp->cur_pos.z;
    sp14 = fp->ev.ns.x2230_yoyoHitboxPos;

    if (!ftNs_AttackHi4_YoyoCheckEnvColl(gobj, &sp20, &sp14, ECB_MUL_Y)) {
        sp14 = fp->ev.ns.x2230_yoyoHitboxPos;
        sp20 = sp14;
        sp20.y += fp->x34_scale.y;
        sp14.y += -1.0f * fp->x34_scale.y;
        if ((ftNs_AttackHi4_YoyoCheckEnvColl(gobj, &sp20, &sp14, 1.5f) &
             MPCOLL_GRPUSH) != 0)
        {
            return true;
        }
    }

    return false;
}

void ftNs_AttackHi4_YoyoSetVarAll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->sv.ns.attackhi4.yoyoCurrentFrame = 1;
    fp->sv.ns.attackhi4.yoyoRehitTimer = 0;
    fp->sv.ns.attackhi4.isPosUpdateMod = true;
    fp->ev.ns.x2230_yoyoHitboxPos.z = 0.0f;
    fp->ev.ns.x2230_yoyoHitboxPos.y = 0.0f;
    fp->ev.ns.x2230_yoyoHitboxPos.x = 0.0f;
    fp->ev.ns.x223C = 0.0f;
}

struct Unknown {
    s32 x0;
    s32 x4;
};

static Vec3 const AttackHi4Pos = { 0 };

void ftNs_AttackHi4_YoyoApplySmash(HSD_GObj* gobj)
{
    HSD_GObj* yoyo_GObj;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Vec3 sp18;

    /// @todo Stack is too messed up for #GET_FIGHTER.
    Fighter* fp = gobj->user_data;

    HSD_GObj* temp_yoyo;
    u32 colAnimID;
    f32 posX;
    Item* item_data;
    Article* article;
    itYoyoAttributes* yoyo_attr;
    SmashAttr* smash_attr;
    s32 smashColAnimID;

    fp->sv.ns.attackhi4.yoyoCurrentFrame = 0;
    temp_yoyo = fp->ev.ns.x222C_yoyoGObj;
    yoyo_GObj = temp_yoyo;

    if (temp_yoyo) {
        item_data = yoyo_GObj->user_data;
        article = item_data->xC4_article_data;
        yoyo_attr = article->x4_specialAttributes;
        sp18 = AttackHi4Pos;
        sp18.x = yoyo_attr->x24_YOYO_RELEASE_VEL_X;
        posX = sp18.x;
        sp18.x = posX * fp->facing_dir;
        sp18.y = yoyo_attr->x30_YOYO_RELEASE_VEL_Y;
        it_802BFE5C(temp_yoyo, &sp18, posX);
    }

    colAnimID = 0x77;
    fp->x2114_SmashAttr.x2114_state = 4;
    fp->x2114_SmashAttr.x2124_frameSpeedMul = fp->x89C_frameSpeedMul;
    smash_attr = &fp->x2114_SmashAttr;
    fp->x2114_SmashAttr.x2118_frames = 0.0f;
    fp->x2114_SmashAttr.x211C_holdFrame = 60.0f;
    fp->x2114_SmashAttr.x212C = (u8) 0;
    fp->x2114_SmashAttr.x212D = (u8) ((struct Unknown*) Fighter_804D6528)->x4;
    fp->x2114_SmashAttr.x2128 = colAnimID;
    smashColAnimID = smash_attr->x2128;

    if (smash_attr->x2128 != 0x7B) {
        ft_800BFFD0(fp, smashColAnimID, 0);
    }

    ftCommon_8007EBAC(fp, 0x24U, 0U);
    ft_80088510(fp, 0x334A7, 0x7F, 0x40);
}

static Vec3 const YoyoChargePos = { 0 };

/// @remarks The extremely specific float here is also likely 1/256.
void ftNs_AttackHi4_YoyoSetChargeDamage(HSD_GObj* gobj)
{
    Item* item_data;
    Article* article;
    Fighter* fp;
    Fighter* fighter_data2;
    Vec3 sp30;
    f32 smashChargeFrames;
    HSD_GObj* yoyo_GObj;
    itYoyoAttributes* yoyo_attr;
    ftNessAttributes* ness_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    fp = GET_FIGHTER(gobj);

    // Current animation frame, integer
    fp->sv.ns.attackhi4.yoyoCurrentFrame = 14;

    yoyo_GObj = fp->ev.ns.x222C_yoyoGObj;

    if (yoyo_GObj) {
        item_data = yoyo_GObj->user_data;
        article = item_data->xC4_article_data;
        yoyo_attr = article->x4_specialAttributes;
        sp30 = YoyoChargePos;
        it_802C0010(yoyo_GObj, &sp30);
        fp->ev.ns.x223C = yoyo_attr->x18_SPIN_TEXANIM_SPEED;
    }

    ft_80088510(fp, 0x334AA, 0x7F, 0x40);
    smashChargeFrames = fp->x2114_SmashAttr.x2118_frames;
    fighter_data2 = GET_FIGHTER(gobj);
    ness_attr = getFtSpecialAttrs(fighter_data2);

    if ((0.0f != smashChargeFrames) &&
        ((s32) fighter_data2->x914->state == HitCapsule_Enabled))
    {
        ftColl_8007ABD0(fighter_data2->x914,
                        (u32) (fighter_data2->x914->a_offset.z *
                               ((((0.0039059999398887157f *
                                   ness_attr->xB0_YOYO_DAMAGE_MUL) -
                                  1.0f) *
                                 (smashChargeFrames /
                                  ness_attr->xAC_YOYO_CHARGE_DURATION)) +
                                1.0f)),
                        gobj);
    }
}

static Vec3 const YoyoThinkPos = { 0 };

bool ftNs_AttackHi4_YoyoThink_IsRemove(HSD_GObj* gobj)
{
    s32 ASID;
    s32 yoyoSmashFrameCurr;
    s32 yoyoSmashFrameCurr2;
    s32 yoyoSpawnFrame;
    HSD_GObj* yoyo_GObj;
    itYoyoAttributes* yoyo_attr;

    /// @todo Stack is too messed up for #GET_FIGHTER.
    Fighter* fp = gobj->user_data;

    s32 yoyoDespawnFrame;
    Article* yoyo_article;
    Item* yoyo_itemdata;
    s32 yoyoRotFrame;
    s32 yoyoNudgeFrame;
    Vec3 sp14;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if ((u32) fp->x2200_ftcmd_var0 != 0U) {
        fp->sv.ns.attackhi4.isPosUpdateMod = 0;
    }
    ASID = fp->action_id;
    if ((ASID >= AS_NESS_ATTACKHI4) && (ASID <= AS_NESS_ATTACKHI4_RELEASE)) {
        yoyoSpawnFrame = 2;
        yoyoDespawnFrame = 49;
    } else {
        yoyoSpawnFrame = 2;
        yoyoDespawnFrame = 60;
    }
    yoyoSmashFrameCurr = fp->sv.ns.attackhi4.yoyoCurrentFrame;
    if ((yoyoSmashFrameCurr > yoyoSpawnFrame) &&
        (yoyoSmashFrameCurr <= yoyoDespawnFrame))
    {
        yoyo_GObj = fp->ev.ns.x222C_yoyoGObj;
        yoyo_itemdata = yoyo_GObj->user_data;
        yoyo_article = yoyo_itemdata->xC4_article_data;
        yoyo_attr = yoyo_article->x4_specialAttributes;
        if ((u32) fp->x2204_ftcmd_var1 == 1U) {
            fp->x2204_ftcmd_var1 = 0U;
            it_802BE5D8(yoyo_GObj, 1.0f);
            fp->ev.ns.x223C = yoyo_attr->x18_SPIN_TEXANIM_SPEED;
        }
        if ((u32) fp->x2204_ftcmd_var1 == 2U) {
            fp->x2204_ftcmd_var1 = 0U;
            it_802BE5D8(yoyo_GObj, 0.0f);
            fp->ev.ns.x223C = 0.0f;
            ft_80088510(fp, 0x334B0, SFX_VOLUME_MAX, SFX_PAN_MID);
        }
        ASID = fp->action_id;
        if ((ASID >= AS_NESS_ATTACKHI4) && (ASID <= AS_NESS_ATTACKHI4_RELEASE))
        {
            yoyoRotFrame = yoyo_attr->x40_UPSMASH_YOYO_ROT_FRAME;
            yoyoNudgeFrame = yoyo_attr->x44_UPSMASH_YOYO_NUDGE_FRAME;
        } else {
            yoyoRotFrame = yoyo_attr->x48_DOWNSMASH_YOYO_ROT_FRAME;
            yoyoNudgeFrame = yoyo_attr->x4C_DOWNSMASH_YOYO_NUDGE_FRAME;
        }
        yoyoSmashFrameCurr2 = fp->sv.ns.attackhi4.yoyoCurrentFrame;
        if (yoyoSmashFrameCurr2 == yoyoRotFrame) {
            sp14 = YoyoThinkPos;
            it_802C0010(yoyo_GObj, &sp14);
            ASID = fp->action_id;
            if ((ASID >= AS_NESS_ATTACKHI4) &&
                (ASID <= AS_NESS_ATTACKHI4_RELEASE))
            {
                ft_80088510(fp, 0x334B3, SFX_VOLUME_MAX, SFX_PAN_MID);
            } else {
                ft_80088510(fp, 0x334AD, SFX_VOLUME_MAX, SFX_PAN_MID);
            }
        } else if (yoyoSmashFrameCurr2 == yoyoNudgeFrame) {
            it_802BFEC4(yoyo_GObj);
        }
        if ((s32) fp->sv.ns.attackhi4.yoyoCurrentFrame == yoyoDespawnFrame) {
            it_802BE958(fp->ev.ns.x222C_yoyoGObj);
        }
    } else if (yoyoSmashFrameCurr == yoyoSpawnFrame) {
        ftNs_AttackHi4_YoyoCreateItem(gobj);
        if (fp->ev.ns.x222C_yoyoGObj == NULL) {
            ft_8008A2BC(gobj);
            return true;
        }
    }
    return false;
}

void ftNs_AttackHi4_YoyoSetUnkRate(HSD_GObj* gobj)
{
    f32 texanim_unk;
    Item* item_data;
    Article* item_article;
    itYoyoAttributes* yoyo_attr;
    HSD_GObj* yoyo_GObj;
    Fighter* fp;
    ftNessAttributes* ness_attr;
    f32 yoyo_float;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp = GET_FIGHTER(gobj);
    ness_attr = fp->x2D4_specialAttributes;
    yoyo_GObj = fp->ev.ns.x222C_yoyoGObj;
    if (yoyo_GObj != NULL) {
        item_data = yoyo_GObj->user_data;
        item_article = item_data->xC4_article_data;
        yoyo_attr = item_article->x4_specialAttributes;

        texanim_unk = yoyo_attr->x20_UNK_TEXANIM_MOD;
        yoyo_float = ((texanim_unk - yoyo_attr->x1C_UNK_TEXANIM_SPEED));
        yoyo_float = yoyo_float * ((f32) fp->sv.ns.attackhi4.yoyoCurrentFrame /
                                   ness_attr->xAC_YOYO_CHARGE_DURATION);

        fp->ev.ns.x223C = texanim_unk - yoyo_float;
    }
}

void ftNs_AttackHi4_YoyoCreateItem(HSD_GObj* gobj)
{
    Vec3 sp10;
    Fighter* fp = GET_FIGHTER(gobj);

    lb_8000B1CC(fp->x5E8_fighterBones[0x2A].x0_jobj, NULL, &sp10);
    fp->ev.ns.x222C_yoyoGObj =
        it_802BE9D8(fp->facing_dir, gobj, &sp10, fp->action_id);
    fp->x1984_heldItemSpec = fp->ev.ns.x222C_yoyoGObj;
    if (fp->ev.ns.x222C_yoyoGObj != NULL) {
        if (fp->cb.x21E4_callback_OnDeath2 == NULL) {
            fp->cb.x21E4_callback_OnDeath2 = ftNs_Init_OnDamage;
        }
        if (fp->cb.x21DC_callback_OnTakeDamage == NULL) {
            fp->cb.x21DC_callback_OnTakeDamage = ftNs_Init_OnDamage;
        }
    }
    fp->cb.x21D4_callback_EnterHitlag = ftNs_AttackHi4_YoyoItemSetUnk;
    fp->cb.x21D8_callback_ExitHitlag = ftNs_AttackHi4_YoyoItemSetUnk2;
}

void ftNs_AttackHi4_YoyoItemSetFlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftNs_AttackHi4_YoyoItemSetUnk2(gobj);
    fp->ev.ns.x222C_yoyoGObj = NULL;
}

void ftNs_AttackHi4_YoyoItemDespawn(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->ev.ns.x222C_yoyoGObj != NULL) {
        it_802BE958(fp->ev.ns.x222C_yoyoGObj);
        fp = gobj->user_data;
        ftNs_AttackHi4_YoyoItemSetUnk2(gobj);
        fp->ev.ns.x222C_yoyoGObj = NULL;
    }
}

void ftNs_AttackHi4_YoyoItemSetUnk(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ev.ns.x222C_yoyoGObj != NULL) {
        it_802BE598(fp->ev.ns.x222C_yoyoGObj);
    }
}

void ftNs_AttackHi4_YoyoItemSetUnk2(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ev.ns.x222C_yoyoGObj) {
        it_802BE5B8(fp->ev.ns.x222C_yoyoGObj);
    }
}

void ftNs_AttackHi4_Enter(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    fp->x2218_flag.bits.b0 = 0;
    fp->sv.ns.attackhi4.isChargeDisable = false;

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->x2204_ftcmd_var1 = 0;
        fp->x2200_ftcmd_var0 = 0;
        fp->sv.ns.attackhi4.yoyoCurrentFrame = 1;
        fp->sv.ns.attackhi4.yoyoRehitTimer = 0;

        fp->sv.ns.attackhi4.isPosUpdateMod = 1;
        fp->ev.ns.x2230_yoyoHitboxPos.z = 0.0f;
        fp->ev.ns.x2230_yoyoHitboxPos.y = 0.0f;
        fp->ev.ns.x2230_yoyoHitboxPos.x = 0.0f;
        fp->ev.ns.x223C = 0.0f;
    }

    Fighter_ChangeMotionState(gobj, AS_NESS_ATTACKHI4, 0, NULL, 0.0f, 1.0f,
                              0.0f);

    ftAnim_8006EBA4(gobj);
    fp->x2222_flag.bits.b2 = 1;
    fp->cb.x21C0_callback_OnGiveDamage = ftNs_AttackHi4_YoyoStartTimedRehit;
    fp->cb.x21BC_callback_Accessory4 = ftNs_AttackHi4_YoyoUpdateHitPos;
}

void ftNs_AttackHi4_YoyoStartTimedRehit(HSD_GObj* gobj)
{
    Fighter* fp;
    ftNessAttributes* ness_attr;

    fp = GET_FIGHTER(gobj);
    ness_attr = fp->x2D4_specialAttributes;
    fp->sv.ns.attackhi4.yoyoRehitTimer = (s32) ness_attr->xB4_YOYO_REHIT_RATE;
}

/**
 * @todo #ftNs_AttackHi4_Anim literally won't match under any circumstances
 *       unless this inline is used to get @c Fighter*.
 */
Fighter* GetFighterData(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp;
}

void ftNs_AttackHi4_Anim(HSD_GObj* gobj)
{
    Vec3 sp24;
    Vec3 sp18;
    Fighter* fighter_data2;
    Fighter* fp;
    s32 yoyoRehitTimer;
    s32 yoyoSmashFrameCurr;
    s32 phi_r0;

    fp = gobj->user_data;
    fighter_data2 = gobj->user_data;
    yoyoSmashFrameCurr = fighter_data2->sv.ns.attackhi4.yoyoCurrentFrame;
    fp->sv.ns.attackhi4.yoyoCurrentFrame = (s32) (yoyoSmashFrameCurr + 1);
    if (ftNs_AttackHi4_YoyoThink_IsRemove(gobj) == false) {
        fp = gobj->user_data;
        if ((u32) fp->x2200_ftcmd_var0 == 0U) {
            yoyoRehitTimer = fp->sv.ns.attackhi4.yoyoRehitTimer;
            if (yoyoRehitTimer > 0) {
                fp->sv.ns.attackhi4.yoyoRehitTimer =
                    (s32) (yoyoRehitTimer - 1);
                if ((s32) fp->sv.ns.attackhi4.yoyoRehitTimer == 0) {
                    lbColl_80008440(&fp->x914[0]);
                    lbColl_80008434(&fp->x914[0]);
                }
            }
        }
        if (((s32) fighter_data2->sv.ns.attackhi4.yoyoCurrentFrame == 13) &&
            ((s32) fighter_data2->sv.ns.attackhi4.isChargeDisable == false))
        {
            /// @todo Unused stack.
#ifdef MUST_MATCH
            u8 _[8];
#endif

            fighter_data2 = getFighter(gobj);
            sp18.x = 0.0f;
            sp18.y =
                0.5f *
                (fighter_data2->x6F0_collData.xA4_ecbCurrCorrect.top.y +
                 fighter_data2->x6F0_collData.xA4_ecbCurrCorrect.bottom.y);
            sp18.z = 0.0f;
            sp18.x += fighter_data2->cur_pos.x;
            sp18.y += fighter_data2->cur_pos.y;
            sp18.z += fighter_data2->cur_pos.z;
            sp24 = fighter_data2->ev.ns.x2230_yoyoHitboxPos;
            if ((ftNs_AttackHi4_YoyoCheckEnvColl(gobj, &sp18, &sp24, 0.5f) == 0) &&
                (sp24 = fighter_data2->ev.ns.x2230_yoyoHitboxPos, sp18 = sp24,
                 sp18.y += fighter_data2->x34_scale.y,
                 sp24.y += -1.0f * fighter_data2->x34_scale.y,
                 (((ftNs_AttackHi4_YoyoCheckEnvColl(gobj, &sp18, &sp24, 1.5f) &
                    MPCOLL_GRPUSH) == 0) == 0)))
            {
                phi_r0 = true;
            } else {
                phi_r0 = false;
            }
            if (phi_r0 != false) {
                ftNs_AttackHi4Charge_Enter(gobj);
            }
        }
        if (!ftAnim_IsFramesRemaining(gobj)) {
            ft_8008A2BC(gobj);
        }
    }
}

// 0x80115E74
// https://decomp.me/scratch/0Hcrg
void ftNs_AttackHi4_IASA(HSD_GObj* gobj) // Ness's Up Smash IASA callback
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_A) == false) {
        fp->sv.ns.attackhi4.isChargeDisable =
            true; // Toggle flag to disallow Yo-Yo charge until next Up Smash
                  // instance
    }

    if (fp->x2218_flag.bits.b0 != 0) {
        ftCo_Wait_IASA(gobj);
    }
}

// 0x80115EB8
// https://decomp.me/scratch/e4x3x
void ftNs_AttackHi4_Phys(HSD_GObj* gobj) // Ness's Up Smash Physics callback
{
    Vec3 sp10;
    Fighter* fp;

    ft_80084F3C(gobj);
    fp = GET_FIGHTER(gobj);
    ftNs_AttackHi4_YoyoSetUnkPos(gobj, &sp10);
    fp->ev.ns.x2230_yoyoHitboxPos = sp10;
}

static inline HSD_GObj*
GetFighterData_x222C(HSD_GObj* gobj) // Yet another inline needed to match
{
    Fighter* fp = gobj->user_data;
    HSD_GObj* yoyo_GObj = fp->ev.ns.x222C_yoyoGObj;
    return yoyo_GObj;
}

// 0x80115F14
// https://decomp.me/scratch/W7Ug6
void ftNs_AttackHi4_Coll(
    HSD_GObj* gobj) // Ness's Up Smash Collision callback
{
    Fighter* fp;
    HSD_GObj* yoyo_GObj;

    fp = gobj->user_data;

    ft_80084104(gobj);

    if (((s32) fp->xE0_ground_or_air == GA_Air) &&
        ((yoyo_GObj = GetFighterData_x222C(gobj)) != NULL))
    {
        it_802BE958(yoyo_GObj);

        fp = gobj->user_data;

        if (fp->ev.ns.x222C_yoyoGObj != NULL) {
            it_802BE5B8(fp->ev.ns.x222C_yoyoGObj);
        }
        fp->ev.ns.x222C_yoyoGObj = NULL;
    }
}

static inline HSD_GObj* GetYoyoGObj(Fighter* fp)
{
    return fp->ev.ns.x222C_yoyoGObj;
};

// 0x80115F88
// https://decomp.me/scratch/3Af8Z
void ftNs_AttackHi4Charge_Anim(
    HSD_GObj* gobj) // Ness's Up Smash Charge Animation callback
{
    f32 unk_float;
    Item* item_data;
    itYoyoAttributes* yoyo_attr;
    HSD_GObj* yoyo_GObj;
    Fighter* fp;
    Fighter* fighter_data2;
    Fighter* temp_fp;
    ftNessAttributes* ness_attr;
    ftNessAttributes* temp_ness_attr;

    fp = gobj->user_data;
    ness_attr = fp->x2D4_specialAttributes;
    fp->sv.ns.attackhi4.yoyoCurrentFrame++;
    temp_ness_attr = getFtSpecialAttrs(temp_fp = getFighterPlus(gobj));
    if ((yoyo_GObj = GetYoyoGObj(temp_fp = getFighterPlus(gobj))) != NULL) {
        item_data = yoyo_GObj->user_data;
        yoyo_attr = item_data->xC4_article_data->x4_specialAttributes;
        unk_float = (yoyo_attr->x20_UNK_TEXANIM_MOD -
                     yoyo_attr->x1C_UNK_TEXANIM_SPEED);
        unk_float =
            unk_float * ((f32) temp_fp->sv.ns.attackhi4.yoyoCurrentFrame /
                         temp_ness_attr->xAC_YOYO_CHARGE_DURATION);
        temp_fp->ev.ns.x223C = yoyo_attr->x20_UNK_TEXANIM_MOD - unk_float;
    }

    fighter_data2 = gobj->user_data;
    if ((u32) fighter_data2->x2200_ftcmd_var0 == 0U) {
        if ((s32) fighter_data2->sv.ns.attackhi4.yoyoRehitTimer > 0) {
            fighter_data2->sv.ns.attackhi4.yoyoRehitTimer--;
            if ((s32) fighter_data2->sv.ns.attackhi4.yoyoRehitTimer == 0) {
                lbColl_80008440(fighter_data2->x914);
                lbColl_80008434(fighter_data2->x914);
            }
        }
    }
    if ((f32) fp->sv.ns.attackhi4.yoyoCurrentFrame >=
        ness_attr->xAC_YOYO_CHARGE_DURATION)
    {
        ftNs_AttackHi4Release_Enter(gobj);
    }
}

// 0x801160B4
// https://decomp.me/scratch/cU6sU
void ftNs_AttackHi4Charge_IASA(
    HSD_GObj* gobj) // Ness's Up Smash Charge IASA callback
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->input.x65C_heldInputs & HSD_BUTTON_A) == false) {
        ftNs_AttackHi4Release_Enter(gobj);
    }
}

// 0x801160E4
// https://decomp.me/scratch/Te2bU
void ftNs_AttackHi4Charge_Phys(
    HSD_GObj* gobj) // Ness's Up Smash Charge Physics callback
{
    ft_80084F3C(gobj);
}

// 0x80116104
// https://decomp.me/scratch/TJd8i
void ftNs_AttackHi4Charge_Coll(
    HSD_GObj* gobj) // Ness's Up Smash Charge Collision callback
{
    Fighter* fp;
    HSD_GObj* yoyo_GObj;

    fp = getFighter(gobj);
    ft_80084104(gobj);
    if (((s32) fp->xE0_ground_or_air == GA_Air) &&
        ((yoyo_GObj = GetFighterData_x222C(gobj)) != NULL))

    {
        it_802BE958(yoyo_GObj);
        fp = GET_FIGHTER(gobj);
        if (fp->ev.ns.x222C_yoyoGObj != NULL) {
            it_802BE5B8(fp->ev.ns.x222C_yoyoGObj);
        }
        fp->ev.ns.x222C_yoyoGObj = NULL;
    }
}

// 0x80116178
// https://decomp.me/scratch/dY1wZ
void ftNs_AttackHi4Charge_Enter(
    HSD_GObj* gobj) // Ness's Up Smash Charge Motion State handler
{
    Fighter* fp = GET_FIGHTER(gobj);

    Fighter_ChangeMotionState(gobj, AS_NESS_ATTACKHI4_CHARGE,
                              FtStateChange_SkipUpdateItemVis, NULL, 12.0f,
                              1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    ftAnim_SetAnimRate(gobj, 0.0f);
    ftNs_AttackHi4_YoyoApplySmash(gobj);
    fp->x2222_flag.bits.b2 = 1;
    fp->cb.x21C0_callback_OnGiveDamage = ftNs_AttackHi4_YoyoStartTimedRehit;
    fp->cb.x21BC_callback_Accessory4 = ftNs_AttackHi4_YoyoUpdateHitPos;
}

// 0x8011620C
// https://decomp.me/scratch/QRdS1
void ftNs_AttackHi4Release_Anim(
    HSD_GObj* gobj) // Ness's Up Smash Post-Charge Animation callback
{
    s32 yoyoRehitTimer;
    s32 yoyoSmashFrameCurr;
    Fighter* fp;
    Fighter* temp_fp;

    temp_fp = GET_FIGHTER(gobj);
    yoyoSmashFrameCurr = temp_fp->sv.ns.attackhi4.yoyoCurrentFrame;
    temp_fp->sv.ns.attackhi4.yoyoCurrentFrame = (s32) (yoyoSmashFrameCurr + 1);
    if (ftNs_AttackHi4_YoyoThink_IsRemove(gobj) == false) {
        fp = GET_FIGHTER(gobj);
        if ((u32) fp->x2200_ftcmd_var0 == 0U) {
            yoyoRehitTimer = fp->sv.ns.attackhi4.yoyoRehitTimer;
            if (yoyoRehitTimer > 0) {
                fp->sv.ns.attackhi4.yoyoRehitTimer--;
                if ((s32) fp->sv.ns.attackhi4.yoyoRehitTimer == 0) {
                    lbColl_80008440(fp->x914);
                    lbColl_80008434(fp->x914);
                }
            }
        }
        if (!ftAnim_IsFramesRemaining(gobj)) {
            ft_8008A2BC(gobj);
        }
    }
}

// 0x801162B0
// https://decomp.me/scratch/TowF9
void ftNs_AttackHi4Release_IASA(
    HSD_GObj* gobj) // Ness's Up Smash Post-Charge IASA
{
    Fighter* fp = gobj->user_data;
    if (fp->x2218_flag.bits.b0 != 0) {
        ftCo_Wait_IASA(gobj);
    }
}

// 0x801162E0
// https://decomp.me/scratch/U8Bk1
void ftNs_AttackHi4Release_Phys(
    HSD_GObj* gobj) // Ness's Up Smash Post-Charge Physics callback
{
    Vec3 sp30;
    Vec3 sp24;
    Vec3 sp18;
    f32 temp_f2;
    s32 yoyoSmashFrameCurr;
    Fighter* fp;
    Fighter* fighter_data2;
    Fighter* fighter_data3;
    f32 phi_f31;

    fp = GET_FIGHTER(gobj);
    ft_80084F3C(gobj);
    yoyoSmashFrameCurr = fp->sv.ns.attackhi4.yoyoCurrentFrame;
    if (yoyoSmashFrameCurr < 0x18) {
        phi_f31 = 0.10000000149011612f * ((f32) yoyoSmashFrameCurr - 14.0f);
        if (phi_f31 >= 1.0f) {
            phi_f31 = 1.0f;
        } else {
            if (phi_f31 <= 0.0f) {
                phi_f31 = 0.0f;
            }
        }
        fighter_data2 = GET_FIGHTER(gobj);
        ftNs_AttackHi4_YoyoSetUnkPos(gobj, &sp24);
        sp30 = fighter_data2->ev.ns.x2230_yoyoHitboxPos;
        temp_f2 = 1.0f - phi_f31;
        fighter_data2->ev.ns.x2230_yoyoHitboxPos.x =
            (f32) ((sp24.x * phi_f31) + (sp30.x * temp_f2));
        fighter_data2->ev.ns.x2230_yoyoHitboxPos.y =
            (f32) ((sp24.y * phi_f31) + (sp30.y * temp_f2));
        fighter_data2->ev.ns.x2230_yoyoHitboxPos.z =
            (f32) ((sp24.z * phi_f31) + (sp30.z * temp_f2));
        return;
    }
    fighter_data3 = GET_FIGHTER(gobj);
    ftNs_AttackHi4_YoyoSetUnkPos(gobj, &sp18);
    fighter_data3->ev.ns.x2230_yoyoHitboxPos = sp18;
}

// 0x80116420
// https://decomp.me/scratch/TQPrT
void ftNs_AttackHi4Release_Coll(
    HSD_GObj* gobj) // Ness's Up Smash Post-Charge Collision callback
{
    Fighter* fp;
    HSD_GObj* yoyo_GObj;

    fp = getFighter(gobj);
    ft_80084104(gobj);

    if (((s32) fp->xE0_ground_or_air == GA_Air) &&
        ((yoyo_GObj = GetFighterData_x222C(gobj)) != NULL))
    {
        it_802BE958(yoyo_GObj);
        fp = GET_FIGHTER(gobj);
        if (fp->ev.ns.x222C_yoyoGObj != NULL) {
            it_802BE5B8(fp->ev.ns.x222C_yoyoGObj);
        }
        fp->ev.ns.x222C_yoyoGObj = NULL;
    }
}

static itYoyoAttributes* GetYoyoAttr(HSD_GObj* gobj)
{
    Item* item_data = gobj->user_data;
    itYoyoAttributes* yoyo_attr =
        item_data->xC4_article_data->x4_specialAttributes;
    return yoyo_attr;
}

void ftNs_AttackHi4Release_Enter(HSD_GObj* gobj)
{
    Vec3 sp34;
    Fighter* fighter_data2;
    Fighter* fp;
    itYoyoAttributes* yoyo_attr;
    HSD_GObj* yoyo_GObj;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, AS_NESS_ATTACKHI4_RELEASE,
                              FtStateChange_SkipUpdateItemVis, NULL, 13.0f,
                              1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);

    fighter_data2 = getFighter(gobj);
    fighter_data2 = getFighter(gobj);
    fighter_data2->sv.ns.attackhi4.yoyoCurrentFrame = 14;

    if ((yoyo_GObj = fighter_data2->ev.ns.x222C_yoyoGObj) != NULL) {
        yoyo_attr = GetYoyoAttr(yoyo_GObj);
        sp34 = YoyoChargePos;
        it_802C0010(yoyo_GObj, &sp34);
        fighter_data2->ev.ns.x223C = yoyo_attr->x18_SPIN_TEXANIM_SPEED;
    }

    ft_80088510(fighter_data2, 0x334AA, SFX_VOLUME_MAX, SFX_PAN_MID);

    ftNs_AttackHi4_YoyoApplyDamage(fighter_data2->x2114_SmashAttr.x2118_frames, gobj);

    fp->x2222_flag.bits.b2 = 1;

    fp->cb.x21C0_callback_OnGiveDamage = ftNs_AttackHi4_YoyoStartTimedRehit;
    fp->cb.x21BC_callback_Accessory4 = ftNs_AttackHi4_YoyoUpdateHitPos;
}
