#include "ftNs_AttackHi4.h"

#include "ftNs_Init.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Wait.h"
#include "ftNess/types.h"
#include "it/items/itnessyoyo.h"
#include "it/itYoyo.h"
#include "it/types.h"

#include "lb/forward.h"

#include "lb/lb_00B0.h"
#include "lb/lbcollision.h"
#include "lb/lbvector.h"
#include "mp/mpcoll.h"

#include <common_structs.h>
#include <trigf.h>
#include <dolphin/mtx.h>

void ftNs_AttackHi4_YoyoUpdateHitPos(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    HitCapsule* hitbox_data = &fp->x914[0];

    if (hitbox_data->state != HitCapsule_Disabled) {
        if (fp->fv.ns.yoyo_hitbox_pos.x != 0.0f ||
            fp->fv.ns.yoyo_hitbox_pos.y != 0.0f)
        {
            ftColl_8007B8A8(&fp->x914[0], &fp->fv.ns.yoyo_hitbox_pos);
        }
    }
};

void ftNs_AttackHi4_YoyoCheckTimedRehit(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[0] == 0) {
        if (fp->mv.ns.attackhi4.yoyoRehitTimer > 0) {
            fp->mv.ns.attackhi4.yoyoRehitTimer--;
            if (fp->mv.ns.attackhi4.yoyoRehitTimer == 0) {
                lbColl_80008440(&fp->x914[0]);
                lbColl_80008434(&fp->x914[0]);
            }
        }
    }
};

#pragma push
#pragma dont_inline on
// Apply modified damage to D-Smash Yo-Yo hitbox after charge
static void ftNs_AttackHi4_YoyoApplyDamage(float unk_float, HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftNessAttributes* ness_attr = fp->dat_attrs;
    float charge_duration;
    float charge_duration2;
    float damage_mul;
    float final_damage;

    if (unk_float != 0.0f) {
        if (fp->x914->state == HitCapsule_Enabled) {
            // Likely 1/256 but won't match.
            // ((float) 1 / 256.0) does not match either.
            float const mul = 0.0039059999398887157f;

            charge_duration = ness_attr->xAC_YOYO_CHARGE_DURATION;
            charge_duration2 = unk_float / charge_duration;
            damage_mul = ness_attr->xB0_YOYO_DAMAGE_MUL * mul - 1.0f;

            final_damage =
                fp->x914->damage * (damage_mul * charge_duration2 + 1.0f);

            ftColl_8007ABD0(&fp->x914[0], final_damage, gobj);
        }
    }
};
#pragma pop

static inline void push_ecb(CollData* a, Vec3* b)
{
    a->last_pos = a->cur_pos; // old = curr
    a->cur_pos = *b;          // curr = new
}

s32 ftNs_AttackHi4_YoyoCheckEnvColl(HSD_GObj* gobj, Vec3* ECBUnk,
                                    Vec3* ECBUnk2, float float_unk)
{
    u8 pad[4];
    CollData coll;
    ftCollisionBox ecb;
    Fighter* fp = gobj->user_data;
    float y_scale;

    y_scale = float_unk * fp->x34_scale.y;

    ecb.top = ecb.right.x = y_scale;
    ecb.bottom = ecb.left.x = -y_scale;
    ecb.right.y = ecb.left.y = 0.0f;

    mpColl_80041EE4(&coll);

    // why do it like this?
    // original code:
    // sp34.prev_pos = sp34.cur_pos;
    // sp34.cur_pos = ECBUnk->x0_vec;
    // sp34.prev_pos = sp34.cur_pos;
    // sp34.cur_pos = ECBUnk2->x0_vec;
    // better code:
    // sp34.prev_pos = ECBUnk->x0_vec;
    // sp34.cur_pos = ECBUnk2->x0_vec;
    // guess: there is a "push ECB" function that handles moving current to
    // old, that got called twice and inlined.

    push_ecb(&coll, ECBUnk);
    push_ecb(&coll, ECBUnk2);

    coll.x34_flags.b1234 = 5;

    mpColl_8004730C(&coll, &ecb); // EnvironmentCollisionCheck_NessYoYo

    {
        s32 retval;
        /// @todo Define flags.
        retval = 0;
        if (coll.env_flags & Collide_FloorMask) {
            retval |= 32768;
        }

        if (coll.env_flags & Collide_LeftWallMask) {
            retval |= 1;
        }

        if (coll.env_flags & Collide_RightWallMask) {
            retval |= 64;
        }

        if (coll.env_flags & Collide_CeilingMask) {
            retval |= 8192;
        }

        return retval;
    }
}

/// @todo Remove @c dont_inline.
///       This is probably a result of incorrectly splitting out the function.
#pragma push
#pragma dont_inline on
void ftNs_AttackHi4_YoyoSetUnkPos(HSD_GObj* gobj, Vec3* pos)
{
    Vec3 sp20;
    Vec3 sp14;

    /// @todo #GET_FIGHTER is prevented by @c dont_inline.
    Fighter* fp = gobj->user_data;

    CollData* collData = &fp->coll_data;

    u8 _[4];

    if (!fp->mv.ns.attackhi4.isPosUpdateMod) {
        lb_8000B1CC(fp->parts[61].joint, NULL, pos);
        return;
    }

    lb_8000B1CC(fp->parts[61].joint, NULL, &sp20);
    lb_8000B1CC(fp->parts[FtPart_XRotN].joint, NULL, &sp14);
    *pos = sp20;
    lbVector_Sub(pos, &sp14);
    lbVector_Rotate(
        pos, 4, -atan2f(collData->floor.normal.x, collData->floor.normal.y));
    lbVector_Add(pos, &sp14);
}
#pragma pop

void ftNs_AttackHi4_YoyoSetHitPos(HSD_GObj* gobj)
{
    Vec3 sp2C;
    Vec3 sp20;
    Vec3 sp14;

    u8 _[4];

    /// @todo Can't move below @c fp.
    CollData* collData;

    Fighter* fp = GET_FIGHTER(gobj);
    collData = &fp->coll_data;

    if (!fp->mv.ns.attackhi4.isPosUpdateMod) {
        lb_8000B1CC(fp->parts[61].joint, NULL, &sp2C);
    } else {
        lb_8000B1CC(fp->parts[61].joint, NULL, &sp14);
        lb_8000B1CC(fp->parts[FtPart_XRotN].joint, NULL, &sp20);
        sp2C = sp14;
        lbVector_Sub(&sp2C, &sp20);
        lbVector_Rotate(
            &sp2C, 4,
            -atan2f(collData->floor.normal.x, collData->floor.normal.y));
        lbVector_Add(&sp2C, &sp20);
    }

    fp->fv.ns.yoyo_hitbox_pos = sp2C;
}

void ftNs_AttackHi4_YoyoSetHitPosUnk(HSD_GObj* gobj, float pos_unk)
{
    Vec3 sp3C;
    Vec3 sp30;
    Vec3 sp24;
    Vec3 sp18;
    float pos_update;

    /// @todo Can't move below @c fp.
    CollData* collData;

    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[4];

    collData = &fp->coll_data;

    if (!fp->mv.ns.attackhi4.isPosUpdateMod) {
        lb_8000B1CC(fp->parts[61].joint, NULL, &sp3C);
    } else {
        lb_8000B1CC(fp->parts[61].joint, NULL, &sp18);
        lb_8000B1CC(fp->parts[FtPart_XRotN].joint, NULL, &sp24);
        sp3C = sp18;
        lbVector_Sub(&sp3C, &sp24);
        lbVector_Rotate(
            &sp3C, 4,
            -atan2f(collData->floor.normal.x, collData->floor.normal.y));
        lbVector_Add(&sp3C, &sp24);
    }

    sp30 = fp->fv.ns.yoyo_hitbox_pos;
    pos_update = 1.0f - pos_unk;
    fp->fv.ns.yoyo_hitbox_pos.x =
        (float) ((sp3C.x * pos_unk) + (sp30.x * pos_update));
    fp->fv.ns.yoyo_hitbox_pos.y =
        (float) ((sp3C.y * pos_unk) + (sp30.y * pos_update));
    fp->fv.ns.yoyo_hitbox_pos.z =
        (float) ((sp3C.z * pos_unk) + (sp30.z * pos_update));
}

bool ftNs_AttackHi4_YoyoCheckNoObstruct(HSD_GObj* gobj)
{
    Vec3 sp20;
    Vec3 sp14;
    float ECB_MUL_Y;
    float ECB_X;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    ECB_X = 0.0f;
    ECB_MUL_Y = 0.5f;
    sp20.x = ECB_X;
    sp20.y =
        ECB_MUL_Y * (fp->coll_data.ecb.top.y + fp->coll_data.ecb.bottom.y);
    sp20.z = ECB_X;
    sp20.x += fp->cur_pos.x;
    sp20.y += fp->cur_pos.y;
    sp20.z += fp->cur_pos.z;
    sp14 = fp->fv.ns.yoyo_hitbox_pos;

    if (!ftNs_AttackHi4_YoyoCheckEnvColl(gobj, &sp20, &sp14, ECB_MUL_Y)) {
        sp14 = fp->fv.ns.yoyo_hitbox_pos;
        sp20 = sp14;
        sp20.y += fp->x34_scale.y;
        sp14.y += -1.0f * fp->x34_scale.y;
        if ((ftNs_AttackHi4_YoyoCheckEnvColl(gobj, &sp20, &sp14, 1.5f) &
             Collide_FloorPush) != 0)
        {
            return true;
        }
    }

    return false;
}

void ftNs_AttackHi4_YoyoSetVarAll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->mv.ns.attackhi4.yoyoCurrentFrame = 1;
    fp->mv.ns.attackhi4.yoyoRehitTimer = 0;
    fp->mv.ns.attackhi4.isPosUpdateMod = true;
    fp->fv.ns.yoyo_hitbox_pos.z = 0.0f;
    fp->fv.ns.yoyo_hitbox_pos.y = 0.0f;
    fp->fv.ns.yoyo_hitbox_pos.x = 0.0f;
    fp->fv.ns.x223C = 0.0f;
}

struct Unknown {
    s32 x0;
    s32 x4;
};

static Vec3 const AttackHi4Pos = { 0 };

void ftNs_AttackHi4_YoyoApplySmash(HSD_GObj* gobj)
{
    HSD_GObj* yoyo_GObj;

    u8 _[4];

    Vec3 sp18;

    /// @todo Stack is too messed up for #GET_FIGHTER.
    Fighter* fp = gobj->user_data;

    HSD_GObj* temp_yoyo;
    u32 colAnimID;
    float posX;
    Item* item_data;
    Article* article;
    itYoyoAttributes* yoyo_attr;
    SmashAttr* smash_attr;
    s32 smashColAnimID;

    fp->mv.ns.attackhi4.yoyoCurrentFrame = 0;
    temp_yoyo = fp->fv.ns.yoyo_gobj;
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

    colAnimID = 119;
    fp->smash_attrs.state = 4;
    fp->smash_attrs.x2124_frameSpeedMul = fp->frame_speed_mul;
    smash_attr = &fp->smash_attrs;
    fp->smash_attrs.x2118_frames = 0.0f;
    fp->smash_attrs.x211C_holdFrame = 60.0f;
    fp->smash_attrs.x212C = (u8) 0;
    fp->smash_attrs.x212D = (u8) ((struct Unknown*) Fighter_804D6528)->x4;
    fp->smash_attrs.x2128 = colAnimID;
    smashColAnimID = smash_attr->x2128;

    if (smash_attr->x2128 != 123) {
        ftCo_800BFFD0(fp, smashColAnimID, 0);
    }

    ftCommon_8007EBAC(fp, 36, 0U);
    ft_80088510(fp, 210087, 127, 64);
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
    float smashChargeFrames;
    HSD_GObj* yoyo_GObj;
    itYoyoAttributes* yoyo_attr;
    ftNessAttributes* ness_attr;

    u8 _[16];

    fp = GET_FIGHTER(gobj);

    // Current animation frame, integer
    fp->mv.ns.attackhi4.yoyoCurrentFrame = 14;

    yoyo_GObj = fp->fv.ns.yoyo_gobj;

    if (yoyo_GObj) {
        item_data = yoyo_GObj->user_data;
        article = item_data->xC4_article_data;
        yoyo_attr = article->x4_specialAttributes;
        sp30 = YoyoChargePos;
        it_802C0010(yoyo_GObj, &sp30);
        fp->fv.ns.x223C = yoyo_attr->x18_SPIN_TEXANIM_SPEED;
    }

    ft_80088510(fp, 210090, 127, 64);
    smashChargeFrames = fp->smash_attrs.x2118_frames;
    fighter_data2 = GET_FIGHTER(gobj);
    ness_attr = getFtSpecialAttrs(fighter_data2);

    if ((0.0f != smashChargeFrames) &&
        ((s32) fighter_data2->x914->state == HitCapsule_Enabled))
    {
        ftColl_8007ABD0(fighter_data2->x914,
                        (u32) (fighter_data2->x914->damage *
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
    s32 msid;
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

    u8 _[8];

    if ((u32) fp->cmd_vars[0] != 0U) {
        fp->mv.ns.attackhi4.isPosUpdateMod = 0;
    }
    msid = fp->motion_id;
    if ((msid >= ftNs_MS_AttackHi4) && (msid <= ftNs_MS_AttackHi4Release)) {
        yoyoSpawnFrame = 2;
        yoyoDespawnFrame = 49;
    } else {
        yoyoSpawnFrame = 2;
        yoyoDespawnFrame = 60;
    }
    yoyoSmashFrameCurr = fp->mv.ns.attackhi4.yoyoCurrentFrame;
    if ((yoyoSmashFrameCurr > yoyoSpawnFrame) &&
        (yoyoSmashFrameCurr <= yoyoDespawnFrame))
    {
        yoyo_GObj = fp->fv.ns.yoyo_gobj;
        yoyo_itemdata = yoyo_GObj->user_data;
        yoyo_article = yoyo_itemdata->xC4_article_data;
        yoyo_attr = yoyo_article->x4_specialAttributes;
        if ((u32) fp->cmd_vars[1] == 1U) {
            fp->cmd_vars[1] = 0U;
            it_802BE5D8(yoyo_GObj, 1.0f);
            fp->fv.ns.x223C = yoyo_attr->x18_SPIN_TEXANIM_SPEED;
        }
        if ((u32) fp->cmd_vars[1] == 2U) {
            fp->cmd_vars[1] = 0U;
            it_802BE5D8(yoyo_GObj, 0.0f);
            fp->fv.ns.x223C = 0.0f;
            ft_80088510(fp, 210096, SFX_VOLUME_MAX, SFX_PAN_MID);
        }
        msid = fp->motion_id;
        if ((msid >= ftNs_MS_AttackHi4) && (msid <= ftNs_MS_AttackHi4Release))
        {
            yoyoRotFrame = yoyo_attr->x40_UPSMASH_YOYO_ROT_FRAME;
            yoyoNudgeFrame = yoyo_attr->x44_UPSMASH_YOYO_NUDGE_FRAME;
        } else {
            yoyoRotFrame = yoyo_attr->x48_DOWNSMASH_YOYO_ROT_FRAME;
            yoyoNudgeFrame = yoyo_attr->x4C_DOWNSMASH_YOYO_NUDGE_FRAME;
        }
        yoyoSmashFrameCurr2 = fp->mv.ns.attackhi4.yoyoCurrentFrame;
        if (yoyoSmashFrameCurr2 == yoyoRotFrame) {
            sp14 = YoyoThinkPos;
            it_802C0010(yoyo_GObj, &sp14);
            msid = fp->motion_id;
            if ((msid >= ftNs_MS_AttackHi4) &&
                (msid <= ftNs_MS_AttackHi4Release))
            {
                ft_80088510(fp, 210099, SFX_VOLUME_MAX, SFX_PAN_MID);
            } else {
                ft_80088510(fp, 210093, SFX_VOLUME_MAX, SFX_PAN_MID);
            }
        } else if (yoyoSmashFrameCurr2 == yoyoNudgeFrame) {
            it_802BFEC4(yoyo_GObj);
        }
        if ((s32) fp->mv.ns.attackhi4.yoyoCurrentFrame == yoyoDespawnFrame) {
            it_802BE958(fp->fv.ns.yoyo_gobj);
        }
    } else if (yoyoSmashFrameCurr == yoyoSpawnFrame) {
        ftNs_AttackHi4_YoyoCreateItem(gobj);
        if (fp->fv.ns.yoyo_gobj == NULL) {
            ft_8008A2BC(gobj);
            return true;
        }
    }
    return false;
}

void ftNs_AttackHi4_YoyoSetUnkRate(HSD_GObj* gobj)
{
    float texanim_unk;
    Item* item_data;
    Article* item_article;
    itYoyoAttributes* yoyo_attr;
    HSD_GObj* yoyo_GObj;
    Fighter* fp;
    ftNessAttributes* ness_attr;
    float yoyo_float;

    u8 _[8];

    fp = GET_FIGHTER(gobj);
    ness_attr = fp->dat_attrs;
    yoyo_GObj = fp->fv.ns.yoyo_gobj;
    if (yoyo_GObj != NULL) {
        item_data = yoyo_GObj->user_data;
        item_article = item_data->xC4_article_data;
        yoyo_attr = item_article->x4_specialAttributes;

        texanim_unk = yoyo_attr->x20_UNK_TEXANIM_MOD;
        yoyo_float = ((texanim_unk - yoyo_attr->x1C_UNK_TEXANIM_SPEED));
        yoyo_float =
            yoyo_float * ((float) fp->mv.ns.attackhi4.yoyoCurrentFrame /
                          ness_attr->xAC_YOYO_CHARGE_DURATION);

        fp->fv.ns.x223C = texanim_unk - yoyo_float;
    }
}

void ftNs_AttackHi4_YoyoCreateItem(HSD_GObj* gobj)
{
    Vec3 sp10;
    Fighter* fp = GET_FIGHTER(gobj);

    lb_8000B1CC(fp->parts[FtPart_R2ndNa].joint, NULL, &sp10);
    fp->fv.ns.yoyo_gobj =
        it_802BE9D8(fp->facing_dir, gobj, &sp10, fp->motion_id);
    fp->x1984_heldItemSpec = fp->fv.ns.yoyo_gobj;
    if (fp->fv.ns.yoyo_gobj != NULL) {
        if (fp->death2_cb == NULL) {
            fp->death2_cb = ftNs_Init_OnDamage;
        }
        if (fp->take_dmg_cb == NULL) {
            fp->take_dmg_cb = ftNs_Init_OnDamage;
        }
    }
    fp->pre_hitlag_cb = ftNs_AttackHi4_YoyoItemSetUnk;
    fp->post_hitlag_cb = ftNs_AttackHi4_YoyoItemSetUnk2;
}

void ftNs_AttackHi4_YoyoItemSetFlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftNs_AttackHi4_YoyoItemSetUnk2(gobj);
    fp->fv.ns.yoyo_gobj = NULL;
}

void ftNs_AttackHi4_YoyoItemDespawn(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    if (fp->fv.ns.yoyo_gobj != NULL) {
        it_802BE958(fp->fv.ns.yoyo_gobj);
        fp = gobj->user_data;
        ftNs_AttackHi4_YoyoItemSetUnk2(gobj);
        fp->fv.ns.yoyo_gobj = NULL;
    }
}

void ftNs_AttackHi4_YoyoItemSetUnk(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.ns.yoyo_gobj != NULL) {
        it_802BE598(fp->fv.ns.yoyo_gobj);
    }
}

void ftNs_AttackHi4_YoyoItemSetUnk2(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.ns.yoyo_gobj) {
        it_802BE5B8(fp->fv.ns.yoyo_gobj);
    }
}

void ftNs_AttackHi4_Enter(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    fp->allow_interrupt = 0;
    fp->mv.ns.attackhi4.isChargeDisable = false;

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->cmd_vars[1] = 0;
        fp->cmd_vars[0] = 0;
        fp->mv.ns.attackhi4.yoyoCurrentFrame = 1;
        fp->mv.ns.attackhi4.yoyoRehitTimer = 0;

        fp->mv.ns.attackhi4.isPosUpdateMod = 1;
        fp->fv.ns.yoyo_hitbox_pos.z = 0.0f;
        fp->fv.ns.yoyo_hitbox_pos.y = 0.0f;
        fp->fv.ns.yoyo_hitbox_pos.x = 0.0f;
        fp->fv.ns.x223C = 0.0f;
    }

    Fighter_ChangeMotionState(gobj, ftNs_MS_AttackHi4, 0, 0.0f, 1.0f, 0.0f,
                              NULL);

    ftAnim_8006EBA4(gobj);
    fp->x2222_b2 = 1;
    fp->deal_dmg_cb = ftNs_AttackHi4_YoyoStartTimedRehit;
    fp->accessory4_cb = ftNs_AttackHi4_YoyoUpdateHitPos;
}

void ftNs_AttackHi4_YoyoStartTimedRehit(HSD_GObj* gobj)
{
    Fighter* fp;
    ftNessAttributes* ness_attr;

    fp = GET_FIGHTER(gobj);
    ness_attr = fp->dat_attrs;
    fp->mv.ns.attackhi4.yoyoRehitTimer = (s32) ness_attr->xB4_YOYO_REHIT_RATE;
}

/**
 * @todo #ftNs_AttackHi4_Anim literally won't match under any circumstances
 *       unless this inline is used to get @c Fighter*.
 */
static Fighter* GetFighterData(HSD_GObj* gobj)
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
    yoyoSmashFrameCurr = fighter_data2->mv.ns.attackhi4.yoyoCurrentFrame;
    fp->mv.ns.attackhi4.yoyoCurrentFrame = (s32) (yoyoSmashFrameCurr + 1);
    if (ftNs_AttackHi4_YoyoThink_IsRemove(gobj) == false) {
        fp = gobj->user_data;
        if ((u32) fp->cmd_vars[0] == 0U) {
            yoyoRehitTimer = fp->mv.ns.attackhi4.yoyoRehitTimer;
            if (yoyoRehitTimer > 0) {
                fp->mv.ns.attackhi4.yoyoRehitTimer =
                    (s32) (yoyoRehitTimer - 1);
                if ((s32) fp->mv.ns.attackhi4.yoyoRehitTimer == 0) {
                    lbColl_80008440(&fp->x914[0]);
                    lbColl_80008434(&fp->x914[0]);
                }
            }
        }
        if (((s32) fighter_data2->mv.ns.attackhi4.yoyoCurrentFrame == 13) &&
            ((s32) fighter_data2->mv.ns.attackhi4.isChargeDisable == false))
        {
            u8 _[8];

            fighter_data2 = getFighter(gobj);
            sp18.x = 0.0f;
            sp18.y = 0.5f * (fighter_data2->coll_data.ecb.top.y +
                             fighter_data2->coll_data.ecb.bottom.y);
            sp18.z = 0.0f;
            sp18.x += fighter_data2->cur_pos.x;
            sp18.y += fighter_data2->cur_pos.y;
            sp18.z += fighter_data2->cur_pos.z;
            sp24 = fighter_data2->fv.ns.yoyo_hitbox_pos;
            if ((ftNs_AttackHi4_YoyoCheckEnvColl(gobj, &sp18, &sp24, 0.5f) ==
                 0) &&
                (sp24 = fighter_data2->fv.ns.yoyo_hitbox_pos, sp18 = sp24,
                 sp18.y += fighter_data2->x34_scale.y,
                 sp24.y += -1.0f * fighter_data2->x34_scale.y,
                 (((ftNs_AttackHi4_YoyoCheckEnvColl(gobj, &sp18, &sp24, 1.5f) &
                    Collide_FloorPush) == 0) == 0)))
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

    if ((fp->input.held_inputs & HSD_PAD_A) == false) {
        fp->mv.ns.attackhi4.isChargeDisable =
            true; // Toggle flag to disallow Yo-Yo charge until next Up Smash
                  // instance
    }

    if (fp->allow_interrupt != 0) {
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
    fp->fv.ns.yoyo_hitbox_pos = sp10;
}

static inline HSD_GObj*
GetFighterData_x222C(HSD_GObj* gobj) // Yet another inline needed to match
{
    Fighter* fp = gobj->user_data;
    HSD_GObj* yoyo_GObj = fp->fv.ns.yoyo_gobj;
    return yoyo_GObj;
}

// 0x80115F14
// https://decomp.me/scratch/W7Ug6
void ftNs_AttackHi4_Coll(HSD_GObj* gobj) // Ness's Up Smash Collision callback
{
    Fighter* fp;
    HSD_GObj* yoyo_GObj;

    fp = gobj->user_data;

    ft_80084104(gobj);

    if (((s32) fp->ground_or_air == GA_Air) &&
        ((yoyo_GObj = GetFighterData_x222C(gobj)) != NULL))
    {
        it_802BE958(yoyo_GObj);

        fp = gobj->user_data;

        if (fp->fv.ns.yoyo_gobj != NULL) {
            it_802BE5B8(fp->fv.ns.yoyo_gobj);
        }
        fp->fv.ns.yoyo_gobj = NULL;
    }
}

static inline HSD_GObj* GetYoyoGObj(Fighter* fp)
{
    return fp->fv.ns.yoyo_gobj;
};

// 0x80115F88
// https://decomp.me/scratch/3Af8Z
void ftNs_AttackHi4Charge_Anim(
    HSD_GObj* gobj) // Ness's Up Smash Charge Animation callback
{
    float unk_float;
    Item* item_data;
    itYoyoAttributes* yoyo_attr;
    HSD_GObj* yoyo_GObj;
    Fighter* fp;
    Fighter* fighter_data2;
    Fighter* temp_fp;
    ftNessAttributes* ness_attr;
    ftNessAttributes* temp_ness_attr;

    fp = gobj->user_data;
    ness_attr = fp->dat_attrs;
    fp->mv.ns.attackhi4.yoyoCurrentFrame++;
    temp_ness_attr = getFtSpecialAttrs(temp_fp = getFighterPlus(gobj));
    if ((yoyo_GObj = GetYoyoGObj(temp_fp = getFighterPlus(gobj))) != NULL) {
        item_data = yoyo_GObj->user_data;
        yoyo_attr = item_data->xC4_article_data->x4_specialAttributes;
        unk_float = (yoyo_attr->x20_UNK_TEXANIM_MOD -
                     yoyo_attr->x1C_UNK_TEXANIM_SPEED);
        unk_float =
            unk_float * ((float) temp_fp->mv.ns.attackhi4.yoyoCurrentFrame /
                         temp_ness_attr->xAC_YOYO_CHARGE_DURATION);
        temp_fp->fv.ns.x223C = yoyo_attr->x20_UNK_TEXANIM_MOD - unk_float;
    }

    fighter_data2 = gobj->user_data;
    if ((u32) fighter_data2->cmd_vars[0] == 0U) {
        if ((s32) fighter_data2->mv.ns.attackhi4.yoyoRehitTimer > 0) {
            fighter_data2->mv.ns.attackhi4.yoyoRehitTimer--;
            if ((s32) fighter_data2->mv.ns.attackhi4.yoyoRehitTimer == 0) {
                lbColl_80008440(fighter_data2->x914);
                lbColl_80008434(fighter_data2->x914);
            }
        }
    }
    if ((float) fp->mv.ns.attackhi4.yoyoCurrentFrame >=
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
    if ((fp->input.held_inputs & HSD_PAD_A) == false) {
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
    if (((s32) fp->ground_or_air == GA_Air) &&
        ((yoyo_GObj = GetFighterData_x222C(gobj)) != NULL))

    {
        it_802BE958(yoyo_GObj);
        fp = GET_FIGHTER(gobj);
        if (fp->fv.ns.yoyo_gobj != NULL) {
            it_802BE5B8(fp->fv.ns.yoyo_gobj);
        }
        fp->fv.ns.yoyo_gobj = NULL;
    }
}

// 0x80116178
// https://decomp.me/scratch/dY1wZ
void ftNs_AttackHi4Charge_Enter(
    HSD_GObj* gobj) // Ness's Up Smash Charge Motion State handler
{
    Fighter* fp = GET_FIGHTER(gobj);

    Fighter_ChangeMotionState(gobj, ftNs_MS_AttackHi4Charge, Ft_MF_SkipItemVis,
                              12.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftAnim_SetAnimRate(gobj, 0.0f);
    ftNs_AttackHi4_YoyoApplySmash(gobj);
    fp->x2222_b2 = 1;
    fp->deal_dmg_cb = ftNs_AttackHi4_YoyoStartTimedRehit;
    fp->accessory4_cb = ftNs_AttackHi4_YoyoUpdateHitPos;
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
    yoyoSmashFrameCurr = temp_fp->mv.ns.attackhi4.yoyoCurrentFrame;
    temp_fp->mv.ns.attackhi4.yoyoCurrentFrame = (s32) (yoyoSmashFrameCurr + 1);
    if (ftNs_AttackHi4_YoyoThink_IsRemove(gobj) == false) {
        fp = GET_FIGHTER(gobj);
        if ((u32) fp->cmd_vars[0] == 0U) {
            yoyoRehitTimer = fp->mv.ns.attackhi4.yoyoRehitTimer;
            if (yoyoRehitTimer > 0) {
                fp->mv.ns.attackhi4.yoyoRehitTimer--;
                if ((s32) fp->mv.ns.attackhi4.yoyoRehitTimer == 0) {
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
    if (fp->allow_interrupt != 0) {
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
    float temp_f2;
    s32 yoyoSmashFrameCurr;
    Fighter* fp;
    Fighter* fighter_data2;
    Fighter* fighter_data3;
    float phi_f31;

    fp = GET_FIGHTER(gobj);
    ft_80084F3C(gobj);
    yoyoSmashFrameCurr = fp->mv.ns.attackhi4.yoyoCurrentFrame;
    if (yoyoSmashFrameCurr < 24) {
        phi_f31 = 0.10000000149011612f * ((float) yoyoSmashFrameCurr - 14.0f);
        if (phi_f31 >= 1.0f) {
            phi_f31 = 1.0f;
        } else {
            if (phi_f31 <= 0.0f) {
                phi_f31 = 0.0f;
            }
        }
        fighter_data2 = GET_FIGHTER(gobj);
        ftNs_AttackHi4_YoyoSetUnkPos(gobj, &sp24);
        sp30 = fighter_data2->fv.ns.yoyo_hitbox_pos;
        temp_f2 = 1.0f - phi_f31;
        fighter_data2->fv.ns.yoyo_hitbox_pos.x =
            (float) ((sp24.x * phi_f31) + (sp30.x * temp_f2));
        fighter_data2->fv.ns.yoyo_hitbox_pos.y =
            (float) ((sp24.y * phi_f31) + (sp30.y * temp_f2));
        fighter_data2->fv.ns.yoyo_hitbox_pos.z =
            (float) ((sp24.z * phi_f31) + (sp30.z * temp_f2));
        return;
    }
    fighter_data3 = GET_FIGHTER(gobj);
    ftNs_AttackHi4_YoyoSetUnkPos(gobj, &sp18);
    fighter_data3->fv.ns.yoyo_hitbox_pos = sp18;
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

    if (((s32) fp->ground_or_air == GA_Air) &&
        ((yoyo_GObj = GetFighterData_x222C(gobj)) != NULL))
    {
        it_802BE958(yoyo_GObj);
        fp = GET_FIGHTER(gobj);
        if (fp->fv.ns.yoyo_gobj != NULL) {
            it_802BE5B8(fp->fv.ns.yoyo_gobj);
        }
        fp->fv.ns.yoyo_gobj = NULL;
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

    u8 _[16];

    fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftNs_MS_AttackHi4Release,
                              Ft_MF_SkipItemVis, 13.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);

    fighter_data2 = getFighter(gobj);
    fighter_data2 = getFighter(gobj);
    fighter_data2->mv.ns.attackhi4.yoyoCurrentFrame = 14;

    if ((yoyo_GObj = fighter_data2->fv.ns.yoyo_gobj) != NULL) {
        yoyo_attr = GetYoyoAttr(yoyo_GObj);
        sp34 = YoyoChargePos;
        it_802C0010(yoyo_GObj, &sp34);
        fighter_data2->fv.ns.x223C = yoyo_attr->x18_SPIN_TEXANIM_SPEED;
    }

    ft_80088510(fighter_data2, 210090, SFX_VOLUME_MAX, SFX_PAN_MID);

    ftNs_AttackHi4_YoyoApplyDamage(fighter_data2->smash_attrs.x2118_frames,
                                   gobj);

    fp->x2222_b2 = 1;

    fp->deal_dmg_cb = ftNs_AttackHi4_YoyoStartTimedRehit;
    fp->accessory4_cb = ftNs_AttackHi4_YoyoUpdateHitPos;
}
