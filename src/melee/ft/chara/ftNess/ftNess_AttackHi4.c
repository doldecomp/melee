#include <melee/ft/chara/ftNess/ftNess.h>

extern void func_8007B8A8(Hitbox*, Vec3*); // Update Hitbox Positions //

// 0x80114EB8 //
// https://decomp.me/scratch/ppemH //

void ftNess_YoyoUpdateHitPos(HSD_GObj* fighter_gobj)  // Ness Yo-Yo Hitbox Position Update //
{
    Fighter* fp = fighter_gobj->user_data;
    Hitbox* hitbox_data = &fp->x914[0];

    if (hitbox_data->x0 != FALSE)
    {
        if (fp->sa.ness.x2230_yoyoHitboxPos.x != 0.0f || fp->sa.ness.x2230_yoyoHitboxPos.y != 0.0f)
        {
            func_8007B8A8(&fp->x914[0], &fp->sa.ness.x2230_yoyoHitboxPos);
        }
    }
};

extern void func_80008440(Hitbox*);
extern void func_80008434(Hitbox*);

// 0x80114F0C
// https://decomp.me/scratch/YUdBB //

void ftNess_YoyoCheckTimedRehit(HSD_GObj* fighter_gobj) // Ness D-Smash Hitbox Refresh Timer //
{
    Fighter* fp = fighter_gobj->user_data;
    Hitbox* hitbox_data;

    if (fp->x2200_ftcmd_var0 == 0)
    {
        if (fp->nessVars[0].AttackHi4.yoyoRehitTimer > 0)
        {
            fp->nessVars[0].AttackHi4.yoyoRehitTimer--;
            if (fp->nessVars[0].AttackHi4.yoyoRehitTimer == 0)
            {
                func_80008440(&fp->x914[0]);
                func_80008434(&fp->x914[0]);
            }
        }
    }
};

#pragma dont_inline on

// 0x80114F70 //
// https://decomp.me/scratch/ylt9e //
void ftNess_YoyoApplyDamage(f32 unk_float, HSD_GObj* fighter_gobj) // Apply modified damage to D-Smash Yo-Yo hitbox after charge //
{
    Fighter* fp = fighter_gobj->user_data;
    ftNessAttributes* ness_attr = fp->x2D4_specialAttributes;
    f32 charge_duration;
    f32 charge_duration2;
    f32 damage_mul;
    f32 final_damage;

    if (unk_float != 0.0f)
    {
        if (fp->x914->x0 == TRUE) // Check if hitbox 0 is active //
        {
            charge_duration = ness_attr->xAC_YOYO_CHARGE_DURATION;
            charge_duration2 = unk_float / charge_duration;
            damage_mul = ness_attr->xB0_YOYO_DAMAGE_MUL * 0.0039059999398887157f - 1.0f; // likely 1/256, try this if it absolutely doesn't match //
            final_damage = fp->x914->xC * (damage_mul * charge_duration2 + 1.0f);

            func_8007ABD0(&fp->x914[0], final_damage, fighter_gobj);
        }
    }
};

#pragma dont_inline off

// 0x80114FF8 //
// https://decomp.me/scratch/omC8O //

inline void push_ecb(CollData* a, Vec3* b)
{
    a->x1C_vec = a->x4_vec; // old = curr
    a->x4_vec = *b; // curr = new
}

// 0x80114FF8 //
// https://decomp.me/scratch/NxhkZ //
s32 ftNess_YoyoCheckEnvColl(HSD_GObj* fighter_gobj, Vec3* ECBUnk, Vec3* ECBUnk2, f32 float_unk) // Check collision of Bone (Yo-Yo attach bone) - also used by Sheik??? //
{
    CollData sp34;
    f32 sp1C[6]; // This is probably some kind of struct, but I don't know which one. ECBVar_UnkFloat doesn't make sense.
    Fighter* fp = fighter_gobj->user_data;
    f32 y_scale;
    s32 retval;

    y_scale = float_unk * fp->x34_scale.y;

    sp1C[4] = y_scale;
    sp1C[0] = y_scale;
    sp1C[2] = -y_scale;
    sp1C[1] = -y_scale;
    sp1C[3] = 0.0f;
    sp1C[5] = 0.0f;

    func_80041EE4(&sp34); // Coll_InitECB

    // why do it like this?
    // original code:
    // sp34.x1C_vec = sp34.x4_vec;
    // sp34.x4_vec = ECBUnk->x0_vec;
    // sp34.x1C_vec = sp34.x4_vec;
    // sp34.x4_vec = ECBUnk2->x0_vec;
    // better code:
    // sp34.x1C_vec = ECBUnk->x0_vec;
    // sp34.x4_vec = ECBUnk2->x0_vec;
    // guess: there is a "push ECB" function that handles moving current to old, that got called twice and inlined.
    push_ecb(&sp34, ECBUnk);
    push_ecb(&sp34, ECBUnk2);

    sp34.x34_flags.bits.b1234 = 5;

    func_8004730C(&sp34, &sp1C); // EnvironmentCollisionCheck_NessYoYo

    // these might be bitfields
    retval = 0;
    if ((sp34.x134_envFlags & 0x18000) != 0) 
    {
        retval |= 0x8000;
    }
    if ((sp34.x134_envFlags & 0x3F) != 0) 
    {
        retval |= 1;
    }
    if ((sp34.x134_envFlags & 0xFC0) != 0) 
    {
        retval |= 0x40;
    }
    if ((sp34.x134_envFlags & 0x6000) != 0) 
    {
        retval |= 0x2000;
    }
    return retval;
}

#pragma dont_inline on

// 0x80115114 //
// https://decomp.me/scratch/TMsSU //
void ftNess_YoyoSetUnkPos(HSD_GObj* fighter_gobj, Vec3* pos) 
{
    Vec3 sp20;
    Vec3 sp14;
    Fighter* fp;
    CollData* collData;
    s32 filler;

    fp = fighter_gobj->user_data;
    collData = &fp->x6F0_collData;
    if ((s32)fp->nessVars[0].AttackHi4.isPosUpdateMod == FALSE)
    {
        func_8000B1CC(fp->x5E8_fighterBones[0x3D].x0_jobj, NULL, pos);
        return;
    }
    func_8000B1CC(fp->x5E8_fighterBones[0x3D].x0_jobj, NULL, &sp20);
    func_8000B1CC(fp->x5E8_fighterBones[0x2].x0_jobj, NULL, &sp14);
    *pos = sp20;
    lbvector_Sub(pos, &sp14);
    lbvector_Rotate(pos, 4, -atan2f(collData->x14C_ground.normal.x, collData->x14C_ground.normal.y));
    lbvector_Add(pos, &sp14);
}

#pragma dont_inline off

// 0x801151EC //
// https://decomp.me/scratch/OGmRW //
void ftNess_YoyoSetHitPos(HSD_GObj* fighter_gobj) // Set Yo-Yo hitbox position? // 
{
    Vec3 sp2C;
    Vec3 sp20;
    Vec3 sp14;
    Vec3* temp_r3; // Unused, not sure how to generate stack without regswaps caused by getFighter //
    CollData* collData;
    Fighter* fp;
    s32 filler;

    fp = fighter_gobj->user_data;
    collData = &fp->x6F0_collData;
    if ((s32)fp->nessVars[0].AttackHi4.isPosUpdateMod == 0) 
    {
        func_8000B1CC(fp->x5E8_fighterBones[0x3D].x0_jobj, NULL, &sp2C);
    }
    else
    {
        func_8000B1CC(fp->x5E8_fighterBones[0x3D].x0_jobj, NULL, &sp14);
        func_8000B1CC(fp->x5E8_fighterBones[0x2].x0_jobj, NULL, &sp20);
        sp2C = sp14;
        lbvector_Sub(&sp2C, &sp20);
        lbvector_Rotate(&sp2C, 4, -atan2f(collData->x14C_ground.normal.x, collData->x14C_ground.normal.y));
        lbvector_Add(&sp2C, &sp20);
    }
    fp->sa.ness.x2230_yoyoHitboxPos = sp2C;
}


// 0x801152D0 //
// https://decomp.me/scratch/GPLr4 //
void ftNess_YoyoSetHitPosUnk(HSD_GObj* fighter_gobj, f32 pos_unk) 
{

    Vec3 sp3C;
    Vec3 sp30;
    Vec3 sp24;
    Vec3 sp18;
    f32 pos_update;
    CollData* collData;
    Fighter* fp;
    s32 filler[2];

    fp = fighter_gobj->user_data;
    collData = &fp->x6F0_collData;
    if ((s32)fp->nessVars[0].AttackHi4.isPosUpdateMod == FALSE) 
    {
        func_8000B1CC(fp->x5E8_fighterBones[0x3D].x0_jobj, NULL, &sp3C);
    }
    else 
    {
        func_8000B1CC(fp->x5E8_fighterBones[0x3D].x0_jobj, NULL, &sp18);
        func_8000B1CC(fp->x5E8_fighterBones[0x2].x0_jobj, NULL, &sp24);
        sp3C = sp18;
        lbvector_Sub(&sp3C, &sp24);
        lbvector_Rotate(&sp3C, 4, -atan2f(collData->x14C_ground.normal.x, collData->x14C_ground.normal.y));
        lbvector_Add(&sp3C, &sp24);
    }
    sp30 = fp->sa.ness.x2230_yoyoHitboxPos;
    pos_update = 1.0f - pos_unk;
    fp->sa.ness.x2230_yoyoHitboxPos.x = (f32)((sp3C.x * pos_unk) + (sp30.x * pos_update));
    fp->sa.ness.x2230_yoyoHitboxPos.y = (f32)((sp3C.y * pos_unk) + (sp30.y * pos_update));
    fp->sa.ness.x2230_yoyoHitboxPos.z = (f32)((sp3C.z * pos_unk) + (sp30.z * pos_update));
}

// 0x80115404 //
// https://decomp.me/scratch/iSze8 //
BOOL ftNess_YoyoCheckNoObstruct(HSD_GObj* fighter_gobj) // Check if Yo-Yo is colliding with an obstacle (wall / air) 
{
    Vec3 sp20;
    Vec3 sp14;
    f32 ECB_MUL_Y;
    f32 ECB_X;
    Fighter* fp;

    fp = getFighter(fighter_gobj);
    ECB_X = 0.0f;
    ECB_MUL_Y = 0.5f;
    sp20.x = ECB_X;
    sp20.y = ECB_MUL_Y * (fp->x6F0_collData.xA4_ecbCurrCorrect.top.y + fp->x6F0_collData.xA4_ecbCurrCorrect.bottom.y);
    sp20.z = ECB_X;
    sp20.x += fp->xB0_pos.x;
    sp20.y += fp->xB0_pos.y;
    sp20.z += fp->xB0_pos.z;
    sp14 = fp->sa.ness.x2230_yoyoHitboxPos;

    if (ftNess_YoyoCheckEnvColl(fighter_gobj, &sp20, &sp14, ECB_MUL_Y) == FALSE) 
    {
        sp14 = fp->sa.ness.x2230_yoyoHitboxPos;
        sp20 = sp14;
        sp20.y += fp->x34_scale.y;
        sp14.y += -1.0f * fp->x34_scale.y;
        if ((ftNess_YoyoCheckEnvColl(fighter_gobj, &sp20, &sp14, 1.5f) & MPCOLL_GRPUSH) != FALSE) 
        {
            return TRUE;
        }
    }
    return FALSE;
}

// 0x80115534 //
// https://decomp.me/scratch/SAmhe //
void ftNess_YoyoSetVarAll(HSD_GObj* fighter_gobj) // Set ftcmd-, fp- and stateVars //
{
    Fighter* fp = getFighter(fighter_gobj);
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->nessVars[0].AttackHi4.yoyoCurrentFrame = 1;
    fp->nessVars[0].AttackHi4.yoyoRehitTimer = 0;
    fp->nessVars[0].AttackHi4.isPosUpdateMod = TRUE;
    fp->sa.ness.x2230_yoyoHitboxPos.z = 0.0f;
    fp->sa.ness.x2230_yoyoHitboxPos.y = 0.0f;
    fp->sa.ness.x2230_yoyoHitboxPos.x = 0.0f;
    fp->sa.ness.x223C = 0.0f;
}

struct Unknown {
    s32 x0;
    s32 x4;
};

extern void func_80088510(Fighter*, s32, s32, s32);
extern void func_802BFE5C(HSD_GObj*, Vec3*, f32);
const Vec3 AttackHi4Pos = { 0.0f, 0.0f, 0.0f };

// 0x8011556C //
// https://decomp.me/scratch/DYuTl // 
void ftNess_YoyoApplySmash(HSD_GObj* fighter_gobj)  // Applies Smash Charge attributes to Ness's Up/Down Smash //
{
    HSD_GObj* yoyo_GObj;
    s32 filler;
    Vec3 sp18;
    Fighter* fp;
    HSD_GObj* temp_yoyo;
    u32 colAnimID;
    f32 posX;
    Item* item_data;
    Article* article;
    itYoyoAttributes* yoyo_attr;
    SmashAttr* smash_attr;
    s32 smashColAnimID;

    fp = fighter_gobj->user_data;
    fp->nessVars[0].AttackHi4.yoyoCurrentFrame = 0;
    temp_yoyo = fp->sa.ness.x222C_yoyoGObj;
    yoyo_GObj = temp_yoyo;
    if (temp_yoyo != 0) 
    {
        item_data = yoyo_GObj->user_data;
        article = item_data->xC4_article_data;
        yoyo_attr = article->x4_specialAttributes;
        sp18 = AttackHi4Pos;
        sp18.x = yoyo_attr->x24_YOYO_RELEASE_VEL_X;
        posX = sp18.x;
        sp18.x = posX * fp->x2C_facing_direction;
        sp18.y = yoyo_attr->x30_YOYO_RELEASE_VEL_Y;
        func_802BFE5C(temp_yoyo, &sp18, posX);
    }
    colAnimID = 0x77;
    fp->x2114_SmashAttr.x2114_state = 4;
    fp->x2114_SmashAttr.x2124_frameSpeedMul = fp->x89C_frameSpeedMul;
    smash_attr = &fp->x2114_SmashAttr;
    fp->x2114_SmashAttr.x2118_frames = 0.0f;
    fp->x2114_SmashAttr.x211C_holdFrame = 60.0f;
    fp->x2114_SmashAttr.x212C = (u8)0;
    fp->x2114_SmashAttr.x212D = (u8)((struct Unknown*)lbl_804D6528)->x4;
    fp->x2114_SmashAttr.x2128 = colAnimID;
    smashColAnimID = smash_attr->x2128;
    if (smash_attr->x2128 != 0x7B) 
    {
        func_800BFFD0(fp, smashColAnimID, 0);
    }
    func_8007EBAC(fp, 0x24U, 0U);
    func_80088510(fp, 0x334A7, 0x7F, 0x40);
}

extern void func_802C0010(HSD_GObj*, void*);              /* extern */

const Vec3 YoyoChargePos = { 0.0f, 0.0f, 0.0f };

// 0x80115680 //
// https://decomp.me/scratch/gj6Zo //
void ftNess_YoyoSetChargeDamage(HSD_GObj* fighter_gobj) // the extremely specific float here is also likely 1/256 // 
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
    Hitbox* hitbox;
    s32 filler;

    fp = getFighterPlus(fighter_gobj);
    fp->nessVars[0].AttackHi4.yoyoCurrentFrame = 14; // Current animation frame, integer //
    yoyo_GObj = fp->sa.ness.x222C_yoyoGObj;
    if (yoyo_GObj != NULL)
    {
        item_data = yoyo_GObj->user_data;
        article = item_data->xC4_article_data;
        yoyo_attr = article->x4_specialAttributes;
        sp30 = YoyoChargePos;
        func_802C0010(yoyo_GObj, &sp30);
        fp->sa.ness.x223C = yoyo_attr->x18_SPIN_TEXANIM_SPEED;
    }
    func_80088510(fp, 0x334AA, 0x7F, 0x40);
    smashChargeFrames = fp->x2114_SmashAttr.x2118_frames;
    fighter_data2 = getFighterPlus(fighter_gobj);
    ness_attr = getFtSpecialAttrs(fighter_data2);
    if ((0.0f != smashChargeFrames) && ((s32)fighter_data2->x914->x0 == TRUE))
    {
        func_8007ABD0(fighter_data2->x914, (u32)(fighter_data2->x914->xC * ((((0.0039059999398887157f * ness_attr->xB0_YOYO_DAMAGE_MUL) - 1.0f) * (smashChargeFrames / ness_attr->xAC_YOYO_CHARGE_DURATION)) + 1.0f)), fighter_gobj);
    }
}

extern void func_802BE5D8(void*, f32);                        /* extern */
extern void func_802BE958(void*);                             /* extern */
extern void func_802BFEC4(void*);                             /* extern */
const Vec3 YoyoThinkPos = { 0.0f, 0.0f, 0.0f };

// 0x80115784 //
// https://decomp.me/scratch/Ns56L //
BOOL ftNess_YoyoThink_IsRemove(HSD_GObj* fighter_gobj) // Ness Yo-Yo Think //
{
    s32 ASID;
    s32 yoyoSmashFrameCurr;
    s32 yoyoSmashFrameCurr2;
    s32 yoyoSpawnFrame;
    HSD_GObj* yoyo_GObj;
    itYoyoAttributes* yoyo_attr;
    Fighter* fp;
    s32 yoyoDespawnFrame;
    Article* yoyo_article;
    Item* yoyo_itemdata;
    s32 yoyoRotFrame;
    s32 yoyoNudgeFrame;
    Vec3 sp14;
    s32 filler[2];

    fp = fighter_gobj->user_data;
    if ((u32)fp->x2200_ftcmd_var0 != 0U)
    {
        fp->nessVars[0].AttackHi4.isPosUpdateMod = 0;
    }
    ASID = fp->x10_action_state_index;
    if ((ASID >= AS_NESS_ATTACKHI4) && (ASID <= AS_NESS_ATTACKHI4_RELEASE))
    {
        yoyoSpawnFrame = 2;
        yoyoDespawnFrame = 49;
    }
    else
    {
        yoyoSpawnFrame = 2;
        yoyoDespawnFrame = 60;
    }
    yoyoSmashFrameCurr = fp->nessVars[0].AttackHi4.yoyoCurrentFrame;
    if ((yoyoSmashFrameCurr > yoyoSpawnFrame) && (yoyoSmashFrameCurr <= yoyoDespawnFrame))
    {
        yoyo_GObj = fp->sa.ness.x222C_yoyoGObj;
        yoyo_itemdata = yoyo_GObj->user_data;
        yoyo_article = yoyo_itemdata->xC4_article_data;
        yoyo_attr = yoyo_article->x4_specialAttributes;
        if ((u32)fp->x2204_ftcmd_var1 == 1U)
        {
            fp->x2204_ftcmd_var1 = 0U;
            func_802BE5D8(yoyo_GObj, 1.0f);
            fp->sa.ness.x223C = yoyo_attr->x18_SPIN_TEXANIM_SPEED;
        }
        if ((u32)fp->x2204_ftcmd_var1 == 2U)
        {
            fp->x2204_ftcmd_var1 = 0U;
            func_802BE5D8(yoyo_GObj, 0.0f);
            fp->sa.ness.x223C = 0.0f;
            func_80088510(fp, 0x334B0, SFX_VOLUME_MAX, SFX_PAN_MID);
        }
        ASID = fp->x10_action_state_index;
        if ((ASID >= AS_NESS_ATTACKHI4) && (ASID <= AS_NESS_ATTACKHI4_RELEASE))
        {
            yoyoRotFrame = yoyo_attr->x40_UPSMASH_YOYO_ROT_FRAME;
            yoyoNudgeFrame = yoyo_attr->x44_UPSMASH_YOYO_NUDGE_FRAME;
        }
        else
        {
            yoyoRotFrame = yoyo_attr->x48_DOWNSMASH_YOYO_ROT_FRAME;
            yoyoNudgeFrame = yoyo_attr->x4C_DOWNSMASH_YOYO_NUDGE_FRAME;
        }
        yoyoSmashFrameCurr2 = fp->nessVars[0].AttackHi4.yoyoCurrentFrame;
        if (yoyoSmashFrameCurr2 == yoyoRotFrame)
        {
            sp14 = YoyoThinkPos;
            func_802C0010(yoyo_GObj, &sp14);
            ASID = fp->x10_action_state_index;
            if ((ASID >= AS_NESS_ATTACKHI4) && (ASID <= AS_NESS_ATTACKHI4_RELEASE))
            {
                func_80088510(fp, 0x334B3, SFX_VOLUME_MAX, SFX_PAN_MID);
            }
            else
            {
                func_80088510(fp, 0x334AD, SFX_VOLUME_MAX, SFX_PAN_MID);
            }
        }
        else if (yoyoSmashFrameCurr2 == yoyoNudgeFrame)
        {
            func_802BFEC4(yoyo_GObj);
        }
        if ((s32)fp->nessVars[0].AttackHi4.yoyoCurrentFrame == yoyoDespawnFrame)
        {
            func_802BE958(fp->sa.ness.x222C_yoyoGObj);
        }
    }
    else if (yoyoSmashFrameCurr == yoyoSpawnFrame)
    {
        ftNess_YoyoCreateItem(fighter_gobj);
        if (fp->sa.ness.x222C_yoyoGObj == NULL)
        {
            func_8008A2BC(fighter_gobj);
            return TRUE;
        }
    }
    return FALSE;
}

// 0x8011599C //
// https://decomp.me/scratch/0m54b //
void ftNess_YoyoSetUnkRate(HSD_GObj* fighter_gobj) // Calculates Yo-Yo texture rotation speed? //
{
    f32 texanim_unk;
    Item* item_data;
    Article* item_article;
    itYoyoAttributes* yoyo_attr;
    HSD_GObj* yoyo_GObj;
    Fighter* fp;
    ftNessAttributes* ness_attr;
    f32 yoyo_float;

    fp = getFighterPlus(fighter_gobj);
    ness_attr = fp->x2D4_specialAttributes;
    yoyo_GObj = fp->sa.ness.x222C_yoyoGObj;
    if (yoyo_GObj != NULL) 
    {
        item_data = yoyo_GObj->user_data;
        item_article = item_data->xC4_article_data;
        yoyo_attr = item_article->x4_specialAttributes;

        texanim_unk = yoyo_attr->x20_UNK_TEXANIM_MOD;
        yoyo_float = ((texanim_unk - yoyo_attr->x1C_UNK_TEXANIM_SPEED));
        yoyo_float = yoyo_float * ((f32)fp->nessVars[0].AttackHi4.yoyoCurrentFrame / ness_attr->xAC_YOYO_CHARGE_DURATION);

        fp->sa.ness.x223C = texanim_unk - yoyo_float;
    }
}

extern HSD_GObj* func_802BE9D8(f32, HSD_GObj*, Vec3*, s32);

// 0x80115A08 //
// https://decomp.me/scratch/N4Tw9 //
void ftNess_YoyoCreateItem(HSD_GObj* fighter_gobj) // Creates Yo-Yo item and sets up callbacks // 
{
    Vec3 sp10;
    s32 ASID;
    Fighter* fp;

    fp = fighter_gobj->user_data;
    func_8000B1CC(fp->x5E8_fighterBones[0x2A].x0_jobj, NULL, &sp10);
    fp->sa.ness.x222C_yoyoGObj = func_802BE9D8(fp->x2C_facing_direction, fighter_gobj, &sp10, fp->x10_action_state_index);
    fp->x1984_heldItemSpec = fp->sa.ness.x222C_yoyoGObj;
    if (fp->sa.ness.x222C_yoyoGObj != NULL)
    {
        if (fp->cb.x21E4_callback_OnDeath2 == NULL)
        {
            fp->cb.x21E4_callback_OnDeath2 = ftNess_OnDamage;
        }
        if (fp->cb.x21DC_callback_OnTakeDamage == NULL)
        {
            fp->cb.x21DC_callback_OnTakeDamage = ftNess_OnDamage;
        }
    }
    fp->cb.x21D4_callback_EnterHitlag = ftNess_YoyoItemSetUnk;
    fp->cb.x21D8_callback_ExitHitlag = ftNess_YoyoItemSetUnk2;
}

// 0x80115AC4 //
// https://decomp.me/scratch/5me7O //
void ftNess_YoyoItemSetFlag(HSD_GObj* fighter_gobj) // Something to do with Yo-Yo flags //
{
    Fighter* fp = getFighter(fighter_gobj);

    ftNess_YoyoItemSetUnk2(fighter_gobj);
    fp->sa.ness.x222C_yoyoGObj = NULL;
}

// 0x80115AF8 //
// https://decomp.me/scratch/RP6Ek //
void ftNess_YoyoItemDespawn(HSD_GObj* fighter_gobj) // Despawn Yo-Yo item //
{
    Fighter* fp = getFighterPlus(fighter_gobj);

    if (fp->sa.ness.x222C_yoyoGObj != NULL)
    {
        func_802BE958(fp->sa.ness.x222C_yoyoGObj);
        fp = fighter_gobj->user_data;
        ftNess_YoyoItemSetUnk2(fighter_gobj);
        fp->sa.ness.x222C_yoyoGObj = NULL;
    }
}

extern void func_802BE598(HSD_GObj*); //* extern *//

// 0x80115B50 //
// https://decomp.me/scratch/OVYJD //
void ftNess_YoyoItemSetUnk(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    if (fp->sa.ness.x222C_yoyoGObj != NULL)
    {
        func_802BE598(fp->sa.ness.x222C_yoyoGObj);
    }
}

extern void func_802BE5B8(HSD_GObj*); //* extern *//

// 0x80115B80 //
// https://decomp.me/scratch/btS5m //
void ftNess_YoyoItemSetUnk2(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    if (fp->sa.ness.x222C_yoyoGObj != NULL) 
    {
        func_802BE5B8(fp->sa.ness.x222C_yoyoGObj);
    }
}

// 0x80115BB0 //
// https://decomp.me/scratch/s5VL2 //
void ftNess_AttackHi4_Action(HSD_GObj* fighter_gobj) // Ness's Up Smash Action State handler //
{
    Fighter* fp;
    Fighter* temp_fp;

    fp = getFighter(fighter_gobj);
    fp->x2218_flag.bits.b0 = 0;
    fp->nessVars[0].AttackHi4.isChargeDisable = FALSE;

    temp_fp = getFighter(fighter_gobj);
    temp_fp->x2204_ftcmd_var1 = 0;
    temp_fp->x2200_ftcmd_var0 = 0;
    temp_fp->nessVars[0].AttackHi4.yoyoCurrentFrame = 1;
    temp_fp->nessVars[0].AttackHi4.yoyoRehitTimer = 0;

    temp_fp->nessVars[0].AttackHi4.isPosUpdateMod = 1;
    temp_fp->sa.ness.x2230_yoyoHitboxPos.z = 0.0f;
    temp_fp->sa.ness.x2230_yoyoHitboxPos.y = 0.0f;
    temp_fp->sa.ness.x2230_yoyoHitboxPos.x = 0.0f;
    temp_fp->sa.ness.x223C = 0.0f;
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_ATTACKHI4, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    fp->x2222_flag.bits.b2 = 1;
    fp->cb.x21C0_callback_OnGiveDamage = ftNess_YoyoStartTimedRehit;
    fp->cb.x21BC_callback_Accessory4 = ftNess_YoyoUpdateHitPos;
}

// 0x80115C74 //
// https://decomp.me/scratch/HA1Fw //
void ftNess_YoyoStartTimedRehit(HSD_GObj* fighter_gobj) // Initiates rehit timer for Yo-Yo hitbox //
{
    Fighter* fp;
    ftNessAttributes* ness_attr;

    fp = getFighter(fighter_gobj);
    ness_attr = fp->x2D4_specialAttributes;
    fp->nessVars[0].AttackHi4.yoyoRehitTimer = (s32)ness_attr->xB4_YOYO_REHIT_RATE;
}

Fighter* GetFighterData(HSD_GObj* fighter_gobj)    // 0x80115C9C literally won't match under any circumstances unless this inline is used to get Fighter*. //
{
    Fighter* fp = fighter_gobj->user_data;
    return fp;
}

// 0x80115C9C //
// https://decomp.me/scratch/8RxlI //
void ftNess_AttackHi4_Anim(HSD_GObj* fighter_gobj) // Ness's Up Smash Animation Callback //
{
    Vec3 sp24;
    Vec3 sp18;
    Fighter* fighter_data2;
    Fighter* fp;
    s32 yoyoRehitTimer;
    s32 yoyoSmashFrameCurr;
    s32 phi_r0;

    fp = fighter_gobj->user_data;
    fighter_data2 = fighter_gobj->user_data;
    yoyoSmashFrameCurr = fighter_data2->nessVars[0].AttackHi4.yoyoCurrentFrame;
    fp->nessVars[0].AttackHi4.yoyoCurrentFrame = (s32)(yoyoSmashFrameCurr + 1);
    if (ftNess_YoyoThink_IsRemove(fighter_gobj) == FALSE) 
    {
        fp = fighter_gobj->user_data;
        if ((u32)fp->x2200_ftcmd_var0 == 0U) 
        {
            yoyoRehitTimer = fp->nessVars[0].AttackHi4.yoyoRehitTimer;
            if (yoyoRehitTimer > 0) 
            {
                fp->nessVars[0].AttackHi4.yoyoRehitTimer = (s32)(yoyoRehitTimer - 1);
                if ((s32)fp->nessVars[0].AttackHi4.yoyoRehitTimer == 0) 
                {
                    func_80008440(&fp->x914[0]);
                    func_80008434(&fp->x914[0]);
                }
            }
        }
        if (((s32)fighter_data2->nessVars[0].AttackHi4.yoyoCurrentFrame == 13) && ((s32)fighter_data2->nessVars[0].AttackHi4.isChargeDisable == FALSE)) 
        {
            fighter_data2 = getFighterPlus(fighter_gobj);
            sp18.x = 0.0f;
            sp18.y = 0.5f * (fighter_data2->x6F0_collData.xA4_ecbCurrCorrect.top.y + fighter_data2->x6F0_collData.xA4_ecbCurrCorrect.bottom.y);
            sp18.z = 0.0f;
            sp18.x += fighter_data2->xB0_pos.x;
            sp18.y += fighter_data2->xB0_pos.y;
            sp18.z += fighter_data2->xB0_pos.z;
            sp24 = fighter_data2->sa.ness.x2230_yoyoHitboxPos;
            if ((ftNess_YoyoCheckEnvColl(fighter_gobj, &sp18, &sp24, 0.5f) == 0) && (sp24 = fighter_data2->sa.ness.x2230_yoyoHitboxPos, sp18 = sp24, sp18.y += fighter_data2->x34_scale.y, sp24.y += -1.0f * fighter_data2->x34_scale.y, (((ftNess_YoyoCheckEnvColl(fighter_gobj, &sp18, &sp24, 1.5f) & MPCOLL_GRPUSH) == 0) == 0))) 
            {
                phi_r0 = TRUE;
            }
            else 
            {
                phi_r0 = FALSE;
            }
            if (phi_r0 != FALSE) 
            {
                ftNess_AttackHi4_Charge_Action(fighter_gobj);
            }
        }
        if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE) 
        {
            func_8008A2BC(fighter_gobj);
        }
    }
}

extern void func_8008A4D4(HSD_GObj*);

// 0x80115E74 //
// https://decomp.me/scratch/0Hcrg //
void ftNess_AttackHi4_IASA(HSD_GObj* fighter_gobj)   // Ness's Up Smash IASA callback //
{
    Fighter* fp = getFighter(fighter_gobj);

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_A) == FALSE)

    {
        fp->nessVars[0].AttackHi4.isChargeDisable = TRUE; // Toggle flag to disallow Yo-Yo charge until next Up Smash instance //
    }

    if (fp->x2218_flag.bits.b0 != 0) 
    {
        func_8008A4D4(fighter_gobj);
    }
}

// 0x80115EB8 //
// https://decomp.me/scratch/e4x3x //
void ftNess_AttackHi4_Phys(HSD_GObj* fighter_gobj)   // Ness's Up Smash Physics callback //
{
    Vec3 sp10;
    Fighter* fp;

    func_80084F3C(fighter_gobj);
    fp = getFighter(fighter_gobj);
    ftNess_YoyoSetUnkPos(fighter_gobj, &sp10);
    fp->sa.ness.x2230_yoyoHitboxPos = sp10;
}

inline HSD_GObj* GetFighterData_x222C(HSD_GObj* fighter_gobj)  // Yet another inline needed to match //
{
    Fighter* fp = fighter_gobj->user_data;
    HSD_GObj* yoyo_GObj = fp->sa.ness.x222C_yoyoGObj;
    return yoyo_GObj;
}

// 0x80115F14
// https://decomp.me/scratch/W7Ug6 // 
void ftNess_AttackHi4_Coll(HSD_GObj* fighter_gobj)   // Ness's Up Smash Collision callback //
{
    Fighter* fp;
    HSD_GObj* yoyo_GObj;

    fp = fighter_gobj->user_data;

    func_80084104(fighter_gobj);

    if (((s32)fp->xE0_ground_or_air == GA_Air) && ((yoyo_GObj = GetFighterData_x222C(fighter_gobj)) != NULL))
    {
        func_802BE958(yoyo_GObj);

        fp = fighter_gobj->user_data;

        if (fp->sa.ness.x222C_yoyoGObj != NULL) 
        {
            func_802BE5B8(fp->sa.ness.x222C_yoyoGObj);
        }
        fp->sa.ness.x222C_yoyoGObj = NULL;
    }
}

inline HSD_GObj* GetYoyoGObj(Fighter* fp)
{
    HSD_GObj* yoyo_GObj = fp->sa.ness.x222C_yoyoGObj;
    return yoyo_GObj;
};

// 0x80115F88 //
// https://decomp.me/scratch/3Af8Z // 
void ftNess_AttackHi4_Charge_Anim(HSD_GObj* fighter_gobj)   // Ness's Up Smash Charge Animation callback //
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

    fp = fighter_gobj->user_data;
    ness_attr = fp->x2D4_specialAttributes;
    fp->nessVars[0].AttackHi4.yoyoCurrentFrame++;
    temp_ness_attr = getFtSpecialAttrs(temp_fp = getFighterPlus(fighter_gobj));
    if ((yoyo_GObj = GetYoyoGObj(temp_fp = getFighterPlus(fighter_gobj))) != NULL)
    {
        item_data = yoyo_GObj->user_data;
        yoyo_attr = item_data->xC4_article_data->x4_specialAttributes;
        unk_float = (yoyo_attr->x20_UNK_TEXANIM_MOD - yoyo_attr->x1C_UNK_TEXANIM_SPEED);
        unk_float = unk_float * ((f32)temp_fp->nessVars[0].AttackHi4.yoyoCurrentFrame / temp_ness_attr->xAC_YOYO_CHARGE_DURATION);
        temp_fp->sa.ness.x223C = yoyo_attr->x20_UNK_TEXANIM_MOD - unk_float;
    }

    fighter_data2 = fighter_gobj->user_data;
    if ((u32)fighter_data2->x2200_ftcmd_var0 == 0U)
    {
        if ((s32)fighter_data2->nessVars[0].AttackHi4.yoyoRehitTimer > 0)
        {
            fighter_data2->nessVars[0].AttackHi4.yoyoRehitTimer--;
            if ((s32)fighter_data2->nessVars[0].AttackHi4.yoyoRehitTimer == 0)
            {
                func_80008440(fighter_data2->x914);
                func_80008434(fighter_data2->x914);
            }
        }
    }
    if ((f32)fp->nessVars[0].AttackHi4.yoyoCurrentFrame >= ness_attr->xAC_YOYO_CHARGE_DURATION) 
    {
        ftNess_AttackHi4_Release_Action(fighter_gobj);
    }
}

// 0x801160B4 //
// https://decomp.me/scratch/cU6sU //
void ftNess_AttackHi4_Charge_IASA(HSD_GObj* fighter_gobj)   // Ness's Up Smash Charge IASA callback //
{
    Fighter* fp = getFighter(fighter_gobj);
    if ((fp->input.x65C_heldInputs & HSD_BUTTON_A) == FALSE) 
    {
        ftNess_AttackHi4_Release_Action(fighter_gobj);
    }
}

// 0x801160E4 //
// https://decomp.me/scratch/Te2bU //
void ftNess_AttackHi4_Charge_Phys(HSD_GObj* fighter_gobj)  // Ness's Up Smash Charge Physics callback //
{
    func_80084F3C(fighter_gobj);
}

// 0x80116104 //
// https://decomp.me/scratch/TJd8i //
void ftNess_AttackHi4_Charge_Coll(HSD_GObj* fighter_gobj)   // Ness's Up Smash Charge Collision callback //
{
    Fighter* fp;
    Fighter* fighter_data2;
    HSD_GObj* yoyo_GObj;

    fp = getFighter(fighter_gobj);
    func_80084104(fighter_gobj);
    if (((s32)fp->xE0_ground_or_air == GA_Air) && ((yoyo_GObj = GetFighterData_x222C(fighter_gobj)) != NULL))

    {
        func_802BE958(yoyo_GObj);
        fighter_data2 = getFighter(fighter_gobj);
        if (fighter_data2->sa.ness.x222C_yoyoGObj != NULL)
        {
            func_802BE5B8(fighter_data2->sa.ness.x222C_yoyoGObj);
        }
        fighter_data2->sa.ness.x222C_yoyoGObj = NULL;
    }
}

// 0x80116178 //
// https://decomp.me/scratch/dY1wZ //
void ftNess_AttackHi4_Charge_Action(HSD_GObj* fighter_gobj)  // Ness's Up Smash Charge Action State handler //
{
    Fighter* fp = getFighter(fighter_gobj);

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_ATTACKHI4_CHARGE, FIGHTER_ITEMVIS_NOUPDATE, NULL, 12.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    ftAnim_SetAnimRate(fighter_gobj, 0.0f);
    ftNess_YoyoApplySmash(fighter_gobj);
    fp->x2222_flag.bits.b2 = 1;
    fp->cb.x21C0_callback_OnGiveDamage = ftNess_YoyoStartTimedRehit;
    fp->cb.x21BC_callback_Accessory4 = ftNess_YoyoUpdateHitPos;
}

// 0x8011620C //
// https://decomp.me/scratch/QRdS1 //
void ftNess_AttackHi4_Release_Anim(HSD_GObj* fighter_gobj)   // Ness's Up Smash Post-Charge Animation callback //
{
    s32 yoyoRehitTimer;
    s32 yoyoSmashFrameCurr;
    Fighter* fp;
    Fighter* temp_fp;

    temp_fp = getFighter(fighter_gobj);
    yoyoSmashFrameCurr = temp_fp->nessVars[0].AttackHi4.yoyoCurrentFrame;
    temp_fp->nessVars[0].AttackHi4.yoyoCurrentFrame = (s32)(yoyoSmashFrameCurr + 1);
    if (ftNess_YoyoThink_IsRemove(fighter_gobj) == FALSE) 
    {
        fp = getFighter(fighter_gobj);
        if ((u32)fp->x2200_ftcmd_var0 == 0U)
        {
            yoyoRehitTimer = fp->nessVars[0].AttackHi4.yoyoRehitTimer;
            if (yoyoRehitTimer > 0) 
            {
                fp->nessVars[0].AttackHi4.yoyoRehitTimer--;
                if ((s32)fp->nessVars[0].AttackHi4.yoyoRehitTimer == 0) 
                {
                    func_80008440(fp->x914);
                    func_80008434(fp->x914);
                }
            }
        }
        if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE) 
        {
            func_8008A2BC(fighter_gobj);
        }
    }
}

// 0x801162B0 //
// https://decomp.me/scratch/TowF9 //
void ftNess_AttackHi4_Release_IASA(HSD_GObj* fighter_gobj)   // Ness's Up Smash Post-Charge IASA 
{
    Fighter* fp = fighter_gobj->user_data;
    if (fp->x2218_flag.bits.b0 != 0) 
    {
        func_8008A4D4(fighter_gobj);
    }
}

// 0x801162E0 //
// https://decomp.me/scratch/U8Bk1 //
void ftNess_AttackHi4_Release_Phys(HSD_GObj* fighter_gobj) // Ness's Up Smash Post-Charge Physics callback //
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

    fp = getFighter(fighter_gobj);
    func_80084F3C(fighter_gobj);
    yoyoSmashFrameCurr = fp->nessVars[0].AttackHi4.yoyoCurrentFrame;
    if (yoyoSmashFrameCurr < 0x18)
    {

        phi_f31 = 0.10000000149011612f * ((f32)yoyoSmashFrameCurr - 14.0f);
        if (phi_f31 >= 1.0f)
        {
            phi_f31 = 1.0f;
        }
        else
        {
            if (phi_f31 <= 0.0f)
            {
                phi_f31 = 0.0f;
            }
        }
        fighter_data2 = getFighter(fighter_gobj);
        ftNess_YoyoSetUnkPos(fighter_gobj, &sp24);
        sp30 = fighter_data2->sa.ness.x2230_yoyoHitboxPos;
        temp_f2 = 1.0f - phi_f31;
        fighter_data2->sa.ness.x2230_yoyoHitboxPos.x = (f32)((sp24.x * phi_f31) + (sp30.x * temp_f2));
        fighter_data2->sa.ness.x2230_yoyoHitboxPos.y = (f32)((sp24.y * phi_f31) + (sp30.y * temp_f2));
        fighter_data2->sa.ness.x2230_yoyoHitboxPos.z = (f32)((sp24.z * phi_f31) + (sp30.z * temp_f2));
        return;
    }
    fighter_data3 = getFighter(fighter_gobj);
    ftNess_YoyoSetUnkPos(fighter_gobj, &sp18);
    fighter_data3->sa.ness.x2230_yoyoHitboxPos = sp18;
}

// 0x80116420 //
// https://decomp.me/scratch/TQPrT //
void ftNess_AttackHi4_Release_Coll(HSD_GObj* fighter_gobj)   // Ness's Up Smash Post-Charge Collision callback //
{
    Fighter* fp;
    Fighter* fighter_data2;
    HSD_GObj* yoyo_GObj;

    fp = getFighter(fighter_gobj);
    func_80084104(fighter_gobj);

    if (((s32)fp->xE0_ground_or_air == GA_Air) && ((yoyo_GObj = GetFighterData_x222C(fighter_gobj)) != NULL)) 
    {
        func_802BE958(yoyo_GObj);
        fighter_data2 = getFighter(fighter_gobj);
        if (fighter_data2->sa.ness.x222C_yoyoGObj != NULL) 
        {
            func_802BE5B8(fighter_data2->sa.ness.x222C_yoyoGObj);
        }
        fighter_data2->sa.ness.x222C_yoyoGObj = NULL;
    }
}

itYoyoAttributes* GetYoyoAttr(HSD_GObj* item_gobj) // Inline, may not be necessary //
{
    Item* item_data = item_gobj->user_data;
    itYoyoAttributes* yoyo_attr = item_data->xC4_article_data->x4_specialAttributes;
    return yoyo_attr;
}

// 0x80116494 //
// https://decomp.me/scratch/kR50M //
void ftNess_AttackHi4_Release_Action(HSD_GObj* fighter_gobj)  // Ness's Up Smash Post-Charge Action State handler //
{
    Vec3 sp34;
    Fighter* fighter_data2;
    Fighter* fp;
    itYoyoAttributes* yoyo_attr;
    HSD_GObj* yoyo_GObj;

    fp = fighter_gobj->user_data;
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_ATTACKHI4_RELEASE, FIGHTER_ITEMVIS_NOUPDATE, NULL, 13.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);

    fighter_data2 = getFighterPlus(fighter_gobj);
    fighter_data2 = getFighterPlus(fighter_gobj);
    fighter_data2->nessVars[0].AttackHi4.yoyoCurrentFrame = 14;

    if ((yoyo_GObj = fighter_data2->sa.ness.x222C_yoyoGObj) != NULL) 
    {
        yoyo_attr = GetYoyoAttr(yoyo_GObj);
        sp34 = YoyoChargePos;
        func_802C0010(yoyo_GObj, &sp34);
        fighter_data2->sa.ness.x223C = yoyo_attr->x18_SPIN_TEXANIM_SPEED;
    }

    func_80088510(fighter_data2, 0x334AA, SFX_VOLUME_MAX, SFX_PAN_MID);

    ftNess_YoyoApplyDamage(fighter_data2->x2114_SmashAttr.x2118_frames, fighter_gobj);

    fp->x2222_flag.bits.b2 = 1;

    fp->cb.x21C0_callback_OnGiveDamage = ftNess_YoyoStartTimedRehit;
    fp->cb.x21BC_callback_Accessory4 = ftNess_YoyoUpdateHitPos;
}
