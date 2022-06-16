#include "ftNess.h"

// 0x80114CC0
// https://decomp.me/scratch/E8Nsh //
s32 func_80114CC0(HSD_GObj* fighter_gobj) // Check if Ness is in F-Smash + has Baseball Bat item //
{

    Fighter* fighter_data = fighter_gobj->user_data;

    if (fighter_data->x10_action_state_index != 0x155)

    {
        return 1;
    }

    if (fighter_data->sa.ness.x2248 == 0)

    {
        return 1;
    }

    return 0;
};

void func_802AD6B8(HSD_GObj*);

// 0x80114CF4 //
// https://decomp.me/scratch/mpl3X //
void func_80114CF4(HSD_GObj* fighter_gobj) // Remove Baseball Bat //
{

    Fighter* fighter_data = fighter_gobj->user_data;

    if (fighter_data->sa.ness.x2248 != 0)
    {
        func_802AD6B8(fighter_data->sa.ness.x2248);
        fighter_data->sa.ness.x2248 = 0;
    }

};

// 0x80114D34
// https://decomp.me/scratch/6ulYB //
void func_80114D34(HSD_GObj* fighter_gobj)
{
    Fighter* fighter_data = fighter_gobj->user_data;

    if (fighter_data->sa.ness.x2248 != 0)
    {
        fighter_data->sa.ness.x2248 = 0;
    }
};

void func_8007B23C(HSD_GObj*, void*, void*); // Create Reflect Bubble //
void lbl_80114BF4(HSD_GObj*); //OnReflect Callback //

// 0x80114D50
// https://decomp.me/scratch/M8dFk //
void lbl_80114D50(HSD_GObj* fighter_gobj) //Ness's F-Smash Animation Callback//
{
    Fighter* fighter_data1 = fighter_gobj->user_data;
    Fighter* fighter_data2;
    ftNessAttributes* ness_attr;
    u32* ReflectDesc;
    u32 item_gobj;

    if (fighter_data1->x2218_flag.bits.b3 == 0)
    {
        if (fighter_data1->x2200_ftcmd_var0 != 0)
        {
            ness_attr = fighter_data1->x2D4_specialAttributes;
            func_8007B23C(fighter_gobj, &ness_attr->xB8_REFLECTION_BUBBLE_BONE_ID, lbl_80114BF4); // Creates reflect bubble //
        }
    }
    else if (fighter_data1->x2200_ftcmd_var0 == 0)
    {
        fighter_data1->x2218_flag.bits.b3 = 0; //Toggles reflect bubble off//
    }
    if (func_8006F238(fighter_gobj) == 0)
    {

        fighter_data2 = fighter_gobj->user_data;
        if (fighter_data2->sa.ness.x2248 != 0)
        {
            func_802AD6B8(fighter_data2->sa.ness.x2248); // Despawns the Baseball Bat//
            fighter_data2->sa.ness.x2248 = 0;
        }
        func_8008A2BC(fighter_gobj);
    }
}
void func_8008A4D4(HSD_GObj*); // Interrupt_Wait //

// 0x80114E04
// https://decomp.me/scratch/HTgCI //
void lbl_80114E04(HSD_GObj* fighter_gobj) // Ness's F-Smash IASA Callback //
{
    Fighter* fighter_data = fighter_gobj->user_data;
    u32 filler[2];

    if (fighter_data->x2218_flag.bits.b0 != 0)
    {
        if (fighter_data->sa.ness.x2248 != 0)
        {
            func_802AD6B8(fighter_data->sa.ness.x2248);
            fighter_data->sa.ness.x2248 = 0;
        }
        func_8008A4D4(fighter_gobj);
    }
};

void func_8007AEF8(HSD_GObj*); // Enable Reflect Bubble Update //


// 0x80114E64 //
// https://decomp.me/scratch/wQc4r //
void lbl_80114E64(HSD_GObj* fighter_gobj) // Ness's F-Smash Physics Callback //

{
    func_80084FA8(fighter_gobj);
    func_8007AEF8(fighter_gobj);
};

void func_80084104(HSD_GObj*); // CollisionCheck_StopLedge //


// 0x80114E98 //
// https://decomp.me/scratch/nJ4hj //
void lbl_80114E98(HSD_GObj* fighter_gobj) // Ness's F-Smash Collision Callback //
{
    func_80084104(fighter_gobj);
};


void func_8007B8A8(void*, void*); // Update Hitbox Positions //

// 0x80114EB8 //
// https://decomp.me/scratch/ppemH //

void lbl_80114EB8(HSD_GObj* fighter_gobj)  // Ness Yo-Yo Hitbox Position Update //
{
    Fighter* fighter_data = fighter_gobj->user_data;
    Hitbox* hitbox_data = fighter_data->x914;

    if (hitbox_data->x0 != 0)
    {
        if (fighter_data->sa.ness.x2230.x != 0.0f || fighter_data->sa.ness.x2230.y != 0.0f)
        {
            func_8007B8A8(&fighter_data->x914, &fighter_data->sa.ness.x2230);
        }
    }
};

void func_80008440(void*);
void func_80008434(void*);

// 0x80114F0C
// https://decomp.me/scratch/YUdBB //

void func_80114F0C(HSD_GObj* fighter_gobj) // Ness D-Smash Hitbox Refresh Timer //
{
    Fighter* fighter_data = fighter_gobj->user_data;
    Hitbox* hitbox_data;

    if (fighter_data->x2200_ftcmd_var0 == 0)
    {
        if (fighter_data->x2344_stateVar2_s32 > 0)
        {
            fighter_data->x2344_stateVar2_s32 = fighter_data->x2344_stateVar2_s32 - 1;
            if (fighter_data->x2344_stateVar2_s32 == 0)
            {
                func_80008440(&fighter_data->x914->x0);
                func_80008434(&fighter_data->x914->x0);
            }
        }
    }
};

#pragma dont_inline on

// 0x80114F70 //
// https://decomp.me/scratch/ylt9e //
void func_80114F70(f32 unk_float, HSD_GObj* fighter_gobj) // Apply modified damage to D-Smash Yo-Yo hitbox after charge //
{
    Fighter* fighter_data = fighter_gobj->user_data;
    ftNessAttributes* ness_attr = fighter_data->x2D4_specialAttributes;
    f32 charge_duration;
    f32 charge_duration2;
    f32 damage_mul;
    f32 final_damage;

    if (unk_float != 0.0f)
    {
        if (fighter_data->x914->x0 == 1)
        {
            charge_duration = ness_attr->xAC_SMASH_CHARGE_DURATION;
            charge_duration2 = unk_float / charge_duration;
            damage_mul = ness_attr->xB0_SMASH_CHARGE_DAMAGE_MULTIPLIER * 0.0039059999398887157f - 1.0f; // likely 1/256, try this if it absolutely doesn't match //
            final_damage = fighter_data->x914->xC * (damage_mul * charge_duration2 + 1.0f);

            func_8007ABD0(&fighter_data->x914[0], final_damage, fighter_gobj);
        }
    }
};

#pragma dont_inline off

// 0x80114FF8 //
// https://decomp.me/scratch/omC8O //

void func_80041EE4(CollData*);
void func_8004730C(CollData*, f32(*x)[6]);

void push_ecb(CollData* a, Vec3* b)
{
    a->x1C_vec = a->x4_vec; // old = curr
    a->x4_vec = *b; // curr = new
}

// Ness_CreateYoYoTempECB+CheckCollision
// https://decomp.me/scratch/NxhkZ //
s32 func_80114FF8(HSD_GObj* fighter_gobj, Vec3* ECBUnk, Vec3* ECBUnk2, f32 float_unk) {
    CollData sp34;
    f32 sp1C[6]; // This is probably some kind of struct, but I don't know which one. ECBVar_UnkFloat doesn't make sense.
    Fighter* fighter_data = fighter_gobj->user_data;
    f32 y_scale;
    s32 retval;

    y_scale = float_unk * fighter_data->x34_scale.y;

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

    sp34.x34_flags_1 = 5;

    func_8004730C(&sp34, &sp1C); // EnvironmentCollisionCheck_NessYoYo

    // these might be bitfields
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

#pragma dont_inline on

// 0x80115114 //
// https://decomp.me/scratch/TMsSU //
void func_80115114(HSD_GObj* fighter_gobj, Point3d* arg1) 
{
    Point3d sp20;
    Point3d sp14;
    Fighter* temp_r31;
    CollData* temp_r30;
    u32 filler[1];

    temp_r31 = fighter_gobj->user_data;
    temp_r30 = &temp_r31->x6F0_collData;
    if ((s32)temp_r31->x234C_stateVar4 == 0) {
        func_8000B1CC(temp_r31->x5E8_fighterBones[0x3D].x0_jobj, 0, arg1);
        return;
    }
    func_8000B1CC(temp_r31->x5E8_fighterBones[0x3D].x0_jobj, 0, &sp20);
    func_8000B1CC(temp_r31->x5E8_fighterBones[0x2].x0_jobj, 0, &sp14);
    *arg1 = sp20;
    lbvector_Sub(arg1, &sp14);
    lbvector_Rotate(arg1, 4, -func_someCalcAngle_80022C30(temp_r30->x154_groundNormal.x, temp_r30->x154_groundNormal.y));
    lbvector_Add(arg1, &sp14);
}

#pragma dont_inline off

// 0x801151EC //
// https://decomp.me/scratch/OGmRW //
void func_801151EC(HSD_GObj* fighter_gobj) {
    Point3d sp2C;
    Point3d sp20;
    Point3d sp14;
    Point3d* temp_r3;
    CollData* temp_r31;
    Fighter* temp_r30;
    s32 filler;

    temp_r30 = fighter_gobj->user_data;
    temp_r31 = &temp_r30->x6F0_collData;
    if ((s32)temp_r30->x234C_stateVar4 == 0) {
        func_8000B1CC(temp_r30->x5E8_fighterBones[0x3D].x0_jobj, 0, &sp2C);
    }
    else
    {
        func_8000B1CC(temp_r30->x5E8_fighterBones[0x3D].x0_jobj, 0, &sp14);
        func_8000B1CC(temp_r30->x5E8_fighterBones[0x2].x0_jobj, 0, &sp20);
        sp2C = sp14;
        lbvector_Sub(&sp2C, &sp20);
        lbvector_Rotate(&sp2C, 4, -func_someCalcAngle_80022C30(temp_r31->x154_groundNormal.x, temp_r31->x154_groundNormal.y));
        lbvector_Add(&sp2C, &sp20);
    }
    temp_r30->sa.ness.x2230 = sp2C;
}


// 0x801152D0 //
// https://decomp.me/scratch/GPLr4 //
void func_801152D0(HSD_GObj* fighter_gobj, f32 arg8) {

    Point3d sp3C;
    Vec3 sp30;
    Point3d sp24;
    Point3d sp18;
    Vec2 filler;
    f32 temp_f2;
    CollData* temp_r31;
    Fighter* temp_r30;

    temp_r30 = fighter_gobj->user_data;
    temp_r31 = &temp_r30->x6F0_collData;
    if ((s32)temp_r30->x234C_stateVar4 == 0) {
        func_8000B1CC(temp_r30->x5E8_fighterBones[0x3D].x0_jobj, 0, &sp3C);
    }
    else {
        func_8000B1CC(temp_r30->x5E8_fighterBones[0x3D].x0_jobj, 0, &sp18);
        func_8000B1CC(temp_r30->x5E8_fighterBones[0x2].x0_jobj, 0, &sp24);
        sp3C = sp18;
        lbvector_Sub(&sp3C, &sp24);
        lbvector_Rotate(&sp3C, 4, -func_someCalcAngle_80022C30(temp_r31->x154_groundNormal.x, temp_r31->x154_groundNormal.y));
        lbvector_Add(&sp3C, &sp24);
    }
    sp30 = temp_r30->sa.ness.x2230;
    temp_f2 = 1.0f - arg8;
    temp_r30->sa.ness.x2230.x = (f32)((sp3C.x * arg8) + (sp30.x * temp_f2));
    temp_r30->sa.ness.x2230.y = (f32)((sp3C.y * arg8) + (sp30.y * temp_f2));
    temp_r30->sa.ness.x2230.z = (f32)((sp3C.z * arg8) + (sp30.z * temp_f2));
}

// 0x80115404 //
// https://decomp.me/scratch/iSze8 //
s32 func_80115404(HSD_GObj* fighter_gobj) {
    Vec3 sp20;
    Vec3 sp14;
    f32 temp_f1;
    f32 temp_f3;
    f32 temp_r0;
    Fighter* temp_r31;

    temp_r31 = fighter_gobj->user_data;
    temp_f3 = 0.0f;
    temp_f1 = 0.5f;
    sp20.x = temp_f3;
    sp20.y = temp_f1 * (temp_r31->x6F0_collData.xA8 + temp_r31->x6F0_collData.xB0);
    sp20.z = temp_f3;
    sp20.x += temp_r31->xB0_pos.x;
    sp20.y += temp_r31->xB0_pos.y;
    sp20.z += temp_r31->xB0_pos.z;
    sp14 = temp_r31->sa.ness.x2230;

    if (func_80114FF8(fighter_gobj, &sp20, &sp14, temp_f1) == 0) {
        sp14 = temp_r31->sa.ness.x2230;
        sp20 = sp14;
        sp20.y += temp_r31->x34_scale.y;
        sp14.y += -1.0f * temp_r31->x34_scale.y;
        if ((func_80114FF8(fighter_gobj, &sp20, &sp14, 1.5f) & 0x8000) != 0) {
            return 1;
        }
    }
    return 0;
}

// 0x80115534 //
// https://decomp.me/scratch/SAmhe //
void func_80115534(HSD_GObj* fighter_gobj) // Set ftcmd-, fighter- and stateVars //
{
    Fighter* fighter_data = fighter_gobj->user_data;
    fighter_data->x2204_ftcmd_var1 = 0;
    fighter_data->x2200_ftcmd_var0 = 0;
    fighter_data->x2340_stateVar1 = 1;
    fighter_data->x2344_stateVar2 = 0;
    fighter_data->x234C_stateVar4 = 1;
    fighter_data->sa.ness.x2230.z = 0.0f;
    fighter_data->sa.ness.x2230.y = 0.0f;
    fighter_data->sa.ness.x2230.x = 0.0f;
    fighter_data->sa.ness.x223C = 0.0f;
}

struct Unknown {
    s32 x0;
    s32 x4;
};

void func_80088510(Fighter*, s32, s32, s32);
void func_802BFE5C(void*, void*, f32);
extern const Vec3 lbl_803B7598;

// 0x8011556C //
// https://decomp.me/scratch/DYuTl // 
void func_8011556C(HSD_GObj* fighter_gobj)  // Applies Smash Charge attributes to Ness's Up/Down Smash //
{

    HSD_GObj* temp_r3;
    s32 filler;
    Vec3 sp18;
    Fighter* temp_r31;
    HSD_GObj* temp_r0;
    u32 temp_r5;
    f32 temp_f1;
    Item* temp_r7;
    Article* itData;
    itYoyoAttributes* yoyo_attr;
    SmashAttr* temp_r4_2;
    s32 Cmp;

    temp_r31 = fighter_gobj->user_data;
    temp_r31->x2340_stateVar1 = 0;
    temp_r0 = temp_r31->sa.ness.x222C;
    temp_r3 = temp_r0;
    if (temp_r0 != 0) {
        temp_r7 = temp_r3->user_data;
        itData = temp_r7->xC4_article_data;
        yoyo_attr = itData->x4_specialAttributes;
        sp18 = lbl_803B7598;
        sp18.x = yoyo_attr->x24_YOYO_RELEASE_VEL_X;
        temp_f1 = sp18.x;
        sp18.x = temp_f1 * temp_r31->x2C_facing_direction;
        sp18.y = yoyo_attr->x30_YOYO_RELEASE_VEL_Y;
        func_802BFE5C(temp_r0, &sp18, temp_f1);
    }
    temp_r5 = 0x77;
    temp_r31->x2114_SmashAttr.x2114_state = 4;
    temp_r31->x2114_SmashAttr.x2124_frameSpeedMul = temp_r31->x89C;
    temp_r4_2 = &temp_r31->x2114_SmashAttr;
    temp_r31->x2114_SmashAttr.x2118_frames = 0.0f;
    temp_r31->x2114_SmashAttr.x211C_holdFrame = 60.0f;
    temp_r31->x2114_SmashAttr.x212C = (u8)0;
    temp_r31->x2114_SmashAttr.x212D = (u8)((struct Unknown*)lbl_804D6528)->x4;
    temp_r31->x2114_SmashAttr.x2128 = temp_r5;
    Cmp = temp_r4_2->x2128;
    if (temp_r4_2->x2128 != 0x7B) {
        func_800BFFD0(temp_r31, Cmp, 0);
    }
    func_8007EBAC(temp_r31, 0x24U, 0U);
    func_80088510(temp_r31, 0x334A7, 0x7F, 0x40);
}

void func_802C0010(HSD_GObj*, void*);              /* extern */
extern const Vec3 lbl_803B75A4;

// 0x80115680 //
// https://decomp.me/scratch/gj6Zo //
void func_80115680(HSD_GObj* fighter_gobj) // the extremely specific float here is also likely 1/256 //
{
    u32 filler[2];
    Vec3 sp30;
    u32 filler2[6];
    f32 temp_f1;
    HSD_GObj* temp_r0;
    Fighter* fighter_data;
    itYoyoAttributes* temp_r29;
    Article* item_data;
    ftNessAttributes* temp_r3;
    Item* temp_r7;
    Fighter* temp_r30_2;
    Hitbox* hitbox;

    fighter_data = fighter_gobj->user_data;
    fighter_data->x2340_stateVar1 = 0xE;
    temp_r0 = fighter_data->sa.ness.x222C;
    if (temp_r0 != 0U) {
        temp_r7 = temp_r0->user_data;
        item_data = temp_r7->xC4_article_data;
        temp_r29 = item_data->x4_specialAttributes;
        sp30 = lbl_803B75A4;
        func_802C0010(temp_r0, &sp30);
        fighter_data->sa.ness.x223C = temp_r29->x18_SPIN_TEXANIM_SPEED;
    }
    func_80088510(fighter_data, 0x334AA, 0x7F, 0x40);
    temp_f1 = fighter_data->x2114_SmashAttr.x2118_frames;
    temp_r30_2 = fighter_gobj->user_data;
    temp_r3 = temp_r30_2->x2D4_specialAttributes;
    if ((0.0f != temp_f1) && ((s32)temp_r30_2->x914->x0 == 1)) {
        func_8007ABD0(temp_r30_2->x914, (u32)(temp_r30_2->x914->xC * ((((0.0039059999398887157f * temp_r3->xB0_SMASH_CHARGE_DAMAGE_MULTIPLIER) - 1.0f) * (temp_f1 / temp_r3->xAC_SMASH_CHARGE_DURATION)) + 1.0f)), fighter_gobj);
    }
}

void func_80115A08(HSD_GObj*);                         /* extern */
void func_802BE5D8(void*, f32);                        /* extern */
void func_802BE958(void*);                             /* extern */
void func_802BFEC4(void*);                             /* extern */
extern const Vec3 lbl_803B75B0;
s32 func_80115784(HSD_GObj* fighter_gobj) { //Ness Yo-Yo Think //

    s32 ASID;
    s32 yoyoSmashFrameCurr;
    s32 yoyoSmashFrameCurr2;
    s32 yoyoSpawnFrame;
    HSD_GObj* yoyo_GObj;
    itYoyoAttributes* yoyo_attr;
    Fighter* fighter_data;
    s32 yoyoDespawnFrame;
    Article* yoyo_article;
    Item* yoyo_itemdata;
    s32 yoyoRotFrame;
    s32 yoyoNudgeFrame;
    Vec3 sp14;
    s32 filler[2];

    fighter_data = fighter_gobj->user_data;
    if ((u32)fighter_data->x2200_ftcmd_var0 != 0U) 
    {
        fighter_data->x234C_stateVar4 = 0;
    }
    ASID = fighter_data->x10_action_state_index;
    if ((ASID >= 0x156) && (ASID <= 0x158))
    {
        yoyoSpawnFrame = 0x2;
        yoyoDespawnFrame = 0x31;
    }
    else
    {
        yoyoSpawnFrame = 0x2;
        yoyoDespawnFrame = 0x3C;
    }
    yoyoSmashFrameCurr = fighter_data->x2340_stateVar1;
    if ((yoyoSmashFrameCurr > yoyoSpawnFrame) && (yoyoSmashFrameCurr <= yoyoDespawnFrame)) 
    {
        yoyo_GObj = fighter_data->sa.ness.x222C;
        yoyo_itemdata = yoyo_GObj->user_data;
        yoyo_article = yoyo_itemdata->xC4_article_data;
        yoyo_attr = yoyo_article->x4_specialAttributes;
        if ((u32)fighter_data->x2204_ftcmd_var1 == 1U) 
        {
            fighter_data->x2204_ftcmd_var1 = 0U;
            func_802BE5D8(yoyo_GObj, 1.0f);
            fighter_data->sa.ness.x223C = yoyo_attr->x18_SPIN_TEXANIM_SPEED;
        }
        if ((u32)fighter_data->x2204_ftcmd_var1 == 2U) 
        {
            fighter_data->x2204_ftcmd_var1 = 0U;
            func_802BE5D8(yoyo_GObj, 0.0f);
            fighter_data->sa.ness.x223C = 0.0f;
            func_80088510(fighter_data, 0x334B0, 0x7F, 0x40);
        }
        ASID = fighter_data->x10_action_state_index;
        if ((ASID >= 0x156) && (ASID <= 0x158)) 
        {
            yoyoRotFrame = yoyo_attr->x40_UPSMASH_YOYO_ROT_FRAME;
            yoyoNudgeFrame = yoyo_attr->x44_UPSMASH_YOYO_NUDGE_FRAME;
        }
        else 
        {
            yoyoRotFrame = yoyo_attr->x48_DOWNSMASH_YOYO_ROT_FRAME;
            yoyoNudgeFrame = yoyo_attr->x4C_DOWNSMASH_YOYO_NUDGE_FRAME;
        }
        yoyoSmashFrameCurr2 = fighter_data->x2340_stateVar1;
        if (yoyoSmashFrameCurr2 == yoyoRotFrame) 
        {
            sp14 = lbl_803B75B0;
            func_802C0010(yoyo_GObj, &sp14);
            ASID = fighter_data->x10_action_state_index;
            if ((ASID >= 0x156) && (ASID <= 0x158)) 
            {
                func_80088510(fighter_data, 0x334B3, 0x7F, 0x40);
            }
            else {
                func_80088510(fighter_data, 0x334AD, 0x7F, 0x40);
            }
        }
        else if (yoyoSmashFrameCurr2 == yoyoNudgeFrame) 
        {
            func_802BFEC4(yoyo_GObj);
        }
        if ((s32)fighter_data->x2340_stateVar1 == yoyoDespawnFrame) 
        {
            func_802BE958(fighter_data->sa.ness.x222C);
        }
        goto block_end;
    }
    if (yoyoSmashFrameCurr == yoyoSpawnFrame) 
    {
        func_80115A08(fighter_gobj);
        if ((void*)fighter_data->sa.ness.x222C == 0U) 
        {
            func_8008A2BC(fighter_gobj);
            return 1;
        }
    }
block_end:
    return 0;
}

// 0x8011599C //
// https://decomp.me/scratch/0m54b //
void func_8011599C(HSD_GObj* fighter_gobj) // Calculates Yo-Yo texture rotation speed? //
{
    f32 texanim_unk;
    Item* item_data;
    Article* item_article;
    itYoyoAttributes* yoyo_attr;
    HSD_GObj* yoyo_GObj;
    Fighter* fighter_data;
    ftNessAttributes* ness_attr;
    f32 yoyo_float;
    f32 filler[2];

    fighter_data = fighter_gobj->user_data;
    ness_attr = fighter_data->x2D4_specialAttributes;
    yoyo_GObj = fighter_data->sa.ness.x222C;
    if (yoyo_GObj != 0U) {
        item_data = yoyo_GObj->user_data;
        item_article = item_data->xC4_article_data;
        yoyo_attr = item_article->x4_specialAttributes;
        texanim_unk = yoyo_attr->x20_UNK_TEXANIM_MOD;
        yoyo_float = ((texanim_unk - yoyo_attr->x1C_UNK_TEXANIM_SPEED));
        yoyo_float = yoyo_float * ((f32)fighter_data->x2340_stateVar1 / ness_attr->xAC_SMASH_CHARGE_DURATION);
        fighter_data->sa.ness.x223C = texanim_unk - yoyo_float;
    }
}

HSD_GObj* func_802BE9D8(f32, HSD_GObj*, Vec3*, s32);       /* extern */
void func_80115B80();
void lbl_80115B50();

// 0x80115A08 //
// https://decomp.me/scratch/N4Tw9 //
void func_80115A08(HSD_GObj* fighter_gobj) // Creates Yo-Yo item and sets up callbacks // 
{
    Vec3 sp10;
    s32 ASID;
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    func_8000B1CC(fighter_data->x5E8_fighterBones[0x2A].x0_jobj, 0, &sp10);
    fighter_data->sa.ness.x222C = (void*)func_802BE9D8(fighter_data->x2C_facing_direction, fighter_gobj, &sp10, fighter_data->x10_action_state_index);
    fighter_data->x1984_heldItemSpec = (void*)fighter_data->sa.ness.x222C;
    if ((u32)fighter_data->sa.ness.x222C != 0U)
    {
        if (fighter_data->cb.x21E4_callback_OnDeath2 == 0U)
        {
            fighter_data->cb.x21E4_callback_OnDeath2 = func_801148F8;
        }
        if (fighter_data->cb.x21DC_callback_OnTakeDamage == 0U)
        {
            fighter_data->cb.x21DC_callback_OnTakeDamage = func_801148F8;
        }
    }
    fighter_data->cb.x21D4_callback_EnterHitlag = lbl_80115B50;
    fighter_data->cb.x21D8_callback_ExitHitlag = func_80115B80;
}

// 0x80115AC4 //
// https://decomp.me/scratch/5me7O //
void func_80115AC4(HSD_GObj* fighter_gobj) // Something to do with Yo-Yo flags //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    func_80115B80(fighter_gobj);
    fighter_data->sa.ness.x222C = 0U;
}

// 0x80115AF8 //
// https://decomp.me/scratch/RP6Ek //
void func_80115AF8(HSD_GObj* fighter_gobj) // Despawns Yo-Yo item //
{
    Fighter* fighter_data;
    s32 filler[2];

    fighter_data = fighter_gobj->user_data;
    if ((u32)fighter_data->sa.ness.x222C != 0U)
    {
        func_802BE958(fighter_data->sa.ness.x222C);
        fighter_data = fighter_gobj->user_data;
        func_80115B80(fighter_gobj);
        fighter_data->sa.ness.x222C = 0U;
    }
}

void func_802BE598(HSD_GObj*); //* extern *//

// 0x80115B50 //
// https://decomp.me/scratch/OVYJD //
void lbl_80115B50(HSD_GObj* fighter_gobj)
{
    Fighter* fighter_data = fighter_gobj->user_data;
    if ((u32)fighter_data->sa.ness.x222C != 0U)
    {
        func_802BE598(fighter_data->sa.ness.x222C);
    }
}

void func_802BE5B8(HSD_GObj*); //* extern *//

// 0x80115B80 //
// https://decomp.me/scratch/btS5m //
void func_80115B80(HSD_GObj* fighter_gobj)
{
    Fighter* fighter_data = fighter_gobj->user_data;
    if ((u32)fighter_data->sa.ness.x222C != 0U) 
    {
        func_802BE5B8(fighter_data->sa.ness.x222C);
    }
}

// 0x80115BB0 //
// https://decomp.me/scratch/s5VL2 //
void func_80115BB0(HSD_GObj* fighter_gobj)
{
    f32 temp_f1;
    Fighter* fighter_data;
    Fighter* temp_ft;
    s32 filler[2];

    fighter_data = fighter_gobj->user_data;
    fighter_data->x2218_flag.bits.b0 = 0;
    fighter_data->x2348_stateVar3 = 0;
    temp_ft = fighter_gobj->user_data;
    temp_ft->x2204_ftcmd_var1 = 0;
    temp_ft->x2200_ftcmd_var0 = 0;
    temp_ft->x2340_stateVar1 = 1;
    temp_ft->x2344_stateVar2 = 0;
    temp_ft->x234C_stateVar4 = 1;
    temp_f1 = 0.0f;
    temp_ft->sa.ness.x2230.z = temp_f1;
    temp_ft->sa.ness.x2230.y = temp_f1;
    temp_ft->sa.ness.x2230.x = temp_f1;
    temp_ft->sa.ness.x223C = temp_f1;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x156, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    fighter_data->x2222_flag.bits.b2 = 1;
    fighter_data->cb.x21C0_callback_OnGiveDamage = lbl_80115C74;
    fighter_data->cb.x21BC_callback_Accessory4 = lbl_80114EB8;
}

// 0x80115C74 //
// https://decomp.me/scratch/HA1Fw //
void lbl_80115C74(HSD_GObj* fighter_gobj) // Initiates rehit timer for Yo-Yo hitbox //
{
    Fighter* fighter_data;
    ftNessAttributes* ness_attr;
    s32 filler[2];

    fighter_data = fighter_gobj->user_data;
    ness_attr = fighter_data->x2D4_specialAttributes;
    fighter_data->x2344_stateVar2 = (s32)ness_attr->xB4_SMASH_CHARGE_REHIT_RATE;
}

Fighter* GetFighterData(HSD_GObj* fighter_gobj)    // 0x80115C9C literally won't match under any circumstances unless this inline is used to get Fighter*. //
{
    Fighter* fighter = fighter_gobj->user_data;
    return fighter;
}

// 0x80115C9C //
// https://decomp.me/scratch/8RxlI //
void lbl_80115C9C(HSD_GObj* fighter_gobj) // Ness's Up Smash Animation Callback //
{
    Vec3 sp24;
    Vec3 sp18;
    Fighter* fighter_data2;
    Fighter* fighter_data;
    s32 yoyoRehitTimer;
    s32 yoyoSmashFrameCurr;
    s32 phi_r0;

    fighter_data = fighter_gobj->user_data;
    fighter_data2 = fighter_gobj->user_data;
    yoyoSmashFrameCurr = fighter_data2->x2340_stateVar1;
    fighter_data->x2340_stateVar1 = (s32)(yoyoSmashFrameCurr + 1);
    if (func_80115784(fighter_gobj) == 0) 
    {
        fighter_data = fighter_gobj->user_data;
        if ((u32)fighter_data->x2200_ftcmd_var0 == 0U) 
        {
            yoyoRehitTimer = fighter_data->x2344_stateVar2;
            if (yoyoRehitTimer > 0) {
                fighter_data->x2344_stateVar2 = (s32)(yoyoRehitTimer - 1);
                if ((s32)fighter_data->x2344_stateVar2 == 0) 
                {
                    func_80008440(&fighter_data->x914);
                    func_80008434(&fighter_data->x914);
                }
            }
        }
        if (((s32)fighter_data2->x2340_stateVar1 == 0xD) && ((s32)fighter_data2->x2348_stateVar3 == 0)) 
        {
            fighter_data2 = GetFighterData(fighter_gobj);
            sp18.x = 0.0f;
            sp18.y = 0.5f * (fighter_data2->x6F0_collData.xA8 + fighter_data2->x6F0_collData.xB0);
            sp18.z = 0.0f;
            sp18.x += fighter_data2->xB0_pos.x;
            sp18.y += fighter_data2->xB0_pos.y;
            sp18.z += fighter_data2->xB0_pos.z;
            sp24 = fighter_data2->sa.ness.x2230;
            if ((func_80114FF8(fighter_gobj, &sp18, &sp24, 0.5f) == 0) && (sp24 = fighter_data2->sa.ness.x2230, sp18 = sp24, sp18.y += fighter_data2->x34_scale.y, sp24.y += -1.0f * fighter_data2->x34_scale.y, (((func_80114FF8(fighter_gobj, &sp18, &sp24, 1.5f) & 0x8000) == 0) == 0))) {
                phi_r0 = 1;
            }
            else {
                phi_r0 = 0;
            }
            if (phi_r0 != 0) {
                func_80116178(fighter_gobj);
            }
        }
        if (func_8006F238(fighter_gobj) == 0) 
        {
            func_8008A2BC(fighter_gobj);
        }
    }
}

// 0x80115E74 //
// https://decomp.me/scratch/0Hcrg //
void lbl_80115E74(HSD_GObj* fighter_gobj)   // Ness's Up Smash IASA callback //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    if ((fighter_data->input.x65C & 0x100) == 0)

    {
        fighter_data->x2348_stateVar3 = 1;
    }

    if (fighter_data->x2218_flag.bits.b0 != 0) 
    {
        func_8008A4D4(fighter_gobj);
    }
}

// 0x80115EB8 //
// https://decomp.me/scratch/e4x3x //
void lbl_80115EB8(HSD_GObj* fighter_gobj)   // Ness's Up Smash Physics callback //
{
    Point3d sp10;
    Fighter* fighter_data;
    s32 filler;

    func_80084F3C(fighter_gobj);
    fighter_data = fighter_gobj->user_data;
    func_80115114(fighter_gobj, &sp10);
    fighter_data->sa.ness.x2230 = sp10;
}

HSD_GObj* GetFighterData_x222C(HSD_GObj* fighter_gobj)  // Yet another inline needed to match //
{
    Fighter* fighter_data = fighter_gobj->user_data;
    HSD_GObj* yoyo_GObj = fighter_data->sa.ness.x222C;
    return yoyo_GObj;
}

// 0x80115F14
// https://decomp.me/scratch/W7Ug6 // 
void lbl_80115F14(HSD_GObj* fighter_gobj)   // Ness's Up Smash Collision callback //
{
    Fighter* fighter_data;
    HSD_GObj* yoyo_GObj;

    fighter_data = fighter_gobj->user_data;

    func_80084104(fighter_gobj);

    if (((s32)fighter_data->xE0_ground_or_air == 1) && ((yoyo_GObj = GetFighterData_x222C(fighter_gobj)) != 0U))
    {
        func_802BE958(yoyo_GObj);

        fighter_data = fighter_gobj->user_data;

        if ((u32)fighter_data->sa.ness.x222C != 0U) 
        {
            func_802BE5B8(fighter_data->sa.ness.x222C);
        }
        fighter_data->sa.ness.x222C = 0U;
    }
}

ftNessAttributes* GetNessAttr(Fighter* fighter_data)
{
    ftNessAttributes* ness_attr = fighter_data->x2D4_specialAttributes;
    return ness_attr;
};

HSD_GObj* GetYoyoGObj(Fighter* fighter_data)
{
    HSD_GObj* yoyo_GObj = fighter_data->sa.ness.x222C;
    return yoyo_GObj;
};

// 0x80115F88 //
// https://decomp.me/scratch/3Af8Z // 
void lbl_80115F88(HSD_GObj* fighter_gobj)   // Ness's Up Smash Charge Animation callback //
{
    f32 unk_float;
    Item* item_data;
    itYoyoAttributes* yoyo_attr;
    HSD_GObj* yoyo_GObj;
    Fighter* fighter_data;
    Fighter* fighter_data2;
    Fighter* temp_fighter;
    ftNessAttributes* ness_attr;
    ftNessAttributes* temp_ness_attr;

    fighter_data = fighter_gobj->user_data;
    ness_attr = fighter_data->x2D4_specialAttributes;
    fighter_data->x2340_stateVar1 = fighter_data->x2340_stateVar1 + 1;
    temp_ness_attr = GetNessAttr(temp_fighter = GetFighterData(fighter_gobj));
    if ((yoyo_GObj = GetYoyoGObj(temp_fighter = GetFighterData(fighter_gobj))) != 0U)
    {
        item_data = yoyo_GObj->user_data;
        yoyo_attr = item_data->xC4_article_data->x4_specialAttributes;
        unk_float = (yoyo_attr->x20_UNK_TEXANIM_MOD - yoyo_attr->x1C_UNK_TEXANIM_SPEED);
        unk_float = unk_float * ((f32)temp_fighter->x2340_stateVar1 / temp_ness_attr->xAC_SMASH_CHARGE_DURATION);
        temp_fighter->sa.ness.x223C = yoyo_attr->x20_UNK_TEXANIM_MOD - unk_float;
    }

    fighter_data2 = fighter_gobj->user_data;
    if ((u32)fighter_data2->x2200_ftcmd_var0 == 0U)
    {
        if ((s32)fighter_data2->x2344_stateVar2 > 0)
        {
            fighter_data2->x2344_stateVar2 = (s32)(fighter_data2->x2344_stateVar2 - 1);
            if ((s32)fighter_data2->x2344_stateVar2 == 0)
            {
                func_80008440(fighter_data2->x914);
                func_80008434(fighter_data2->x914);
            }
        }
    }
    if ((f32)fighter_data->x2340_stateVar1 >= ness_attr->xAC_SMASH_CHARGE_DURATION) {
        func_80116494(fighter_gobj);
    }
}

// 0x801160B4 //
// https://decomp.me/scratch/cU6sU //
void lbl_801160B4(HSD_GObj* fighter_gobj)   // Ness's Up Smash Charge IASA callback //
{
    Fighter* fighter_data = fighter_gobj->user_data;
    if ((fighter_data->input.x65C & 0x100) == 0) 
    {
        func_80116494(fighter_gobj);
    }
}

// 0x801160E4 //
// https://decomp.me/scratch/Te2bU //
void lbl_801160E4(HSD_GObj* fighter_gobj)  // Ness's Up Smash Charge Physics callback //
{
    func_80084F3C(fighter_gobj);
}

// 0x80116104 //
// https://decomp.me/scratch/TJd8i //
void lbl_80116104(HSD_GObj* fighter_gobj)   // Ness's Up Smash Charge Collision callback //
{
    Fighter* fighter_data;
    Fighter* fighter_data2;
    HSD_GObj* yoyo_GObj;

    fighter_data = fighter_gobj->user_data;
    func_80084104(fighter_gobj);
    if (((s32)fighter_data->xE0_ground_or_air == 1) && ((yoyo_GObj = GetFighterData_x222C(fighter_gobj)) != 0U)) 

    {
        func_802BE958(yoyo_GObj);
        fighter_data2 = fighter_gobj->user_data;
        if ((u32)fighter_data2->sa.ness.x222C != 0U) 
        {
            func_802BE5B8(fighter_data2->sa.ness.x222C);
        }
        fighter_data2->sa.ness.x222C = 0U;
    }
}

// 0x80116178 //
// https://decomp.me/scratch/dY1wZ //
void func_80116178(HSD_GObj* fighter_gobj)  // Ness's Up Smash Charge Action State handler //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x157, 0x40000, 0, 12.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    ftAnim_SetAnimRate(fighter_gobj, 0.0f);
    func_8011556C(fighter_gobj);
    fighter_data->x2222_flag.bits.b2 = 1;
    fighter_data->cb.x21C0_callback_OnGiveDamage = lbl_80115C74;
    fighter_data->cb.x21BC_callback_Accessory4 = lbl_80114EB8;
}

// 0x8011620C //
// https://decomp.me/scratch/QRdS1 //
void lbl_8011620C(HSD_GObj* fighter_gobj)   // Ness's Up Smash Post-Charge Animation callback //
{
    s32 yoyoRehitTimer;
    s32 yoyoSmashFrameCurr;
    Fighter* fighter_data;
    Fighter* temp_fighter;
    s32 filler[2];

    temp_fighter = fighter_gobj->user_data;
    yoyoSmashFrameCurr = temp_fighter->x2340_stateVar1;
    temp_fighter->x2340_stateVar1 = (s32)(yoyoSmashFrameCurr + 1);
    if (func_80115784(fighter_gobj) == 0) 
    {
        fighter_data = fighter_gobj->user_data;
        if ((u32)fighter_data->x2200_ftcmd_var0 == 0U)
        {
            yoyoRehitTimer = fighter_data->x2344_stateVar2;
            if (yoyoRehitTimer > 0) {
                fighter_data->x2344_stateVar2 = (s32)(yoyoRehitTimer - 1);
                if ((s32)fighter_data->x2344_stateVar2 == 0) 
                {
                    func_80008440(fighter_data->x914);
                    func_80008434(fighter_data->x914);
                }
            }
        }
        if (func_8006F238(fighter_gobj) == 0) 
        {
            func_8008A2BC(fighter_gobj);
        }
    }
}

// 0x801162B0 //
// https://decomp.me/scratch/TowF9 //
void lbl_801162B0(HSD_GObj* fighter_gobj)   // Ness's Up Smash Post-Charge IASA 
{
    Fighter* fighter_data = fighter_gobj->user_data;
    if (fighter_data->x2218_flag.bits.b0 != 0) 
    {
        func_8008A4D4(fighter_gobj);
    }
}

// 0x801162E0 //
// https://decomp.me/scratch/U8Bk1 //
void lbl_801162E0(HSD_GObj* fighter_gobj) // Ness's Up Smash Post-Charge Physics callback //
{
    Point3d sp30;
    Point3d sp24;
    Point3d sp18;
    s32 filler;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f2;
    s32 yoyoSmashFrameCurr;
    Fighter* fighter_data;
    Fighter* fighter_data2;
    Fighter* fighter_data3;
    f32 phi_f31;

    fighter_data = fighter_gobj->user_data;
    func_80084F3C(fighter_gobj);
    yoyoSmashFrameCurr = fighter_data->x2340_stateVar1;
    if (yoyoSmashFrameCurr < 0x18) 

    {
        phi_f31 = 0.10000000149011612f * ((f32)yoyoSmashFrameCurr - 14.0f); // Loooong number likely the result of a local division //
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
        fighter_data2 = fighter_gobj->user_data;
        func_80115114(fighter_gobj, &sp24);
        sp30 = fighter_data2->sa.ness.x2230;
        temp_f2 = 1.0f - phi_f31;
        fighter_data2->sa.ness.x2230.x = (f32)((sp24.x * phi_f31) + (sp30.x * temp_f2));
        fighter_data2->sa.ness.x2230.y = (f32)((sp24.y * phi_f31) + (sp30.y * temp_f2));
        fighter_data2->sa.ness.x2230.z = (f32)((sp24.z * phi_f31) + (sp30.z * temp_f2));
        return;
    }
    fighter_data3 = fighter_gobj->user_data;
    func_80115114(fighter_gobj, &sp18);
    fighter_data3->sa.ness.x2230 = sp18;
}

// 0x80116420 //
// https://decomp.me/scratch/TQPrT //
void lbl_80116420(HSD_GObj* fighter_gobj)   // Ness's Up Smash Post-Charge Collision callback //
{
    Fighter* fighter_data;
    Fighter* fighter_data2;
    HSD_GObj* yoyo_GObj;

    fighter_data = fighter_gobj->user_data;
    func_80084104(fighter_gobj);

    if (((s32)fighter_data->xE0_ground_or_air == 1) && ((yoyo_GObj = GetFighterData_x222C(fighter_gobj)) != 0U)) 
    {
        func_802BE958(yoyo_GObj);
        fighter_data2 = fighter_gobj->user_data;
        if (fighter_data2->sa.ness.x222C != 0U) 
        {
            func_802BE5B8(fighter_data2->sa.ness.x222C);
        }
        fighter_data2->sa.ness.x222C = 0U;
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
void func_80116494(HSD_GObj* fighter_gobj)  // Ness's Up Smash Post-Charge Action State handler //

{
    Vec3 sp34;
    Fighter* fighter_data2;
    Fighter* fighter_data;
    itYoyoAttributes* yoyo_attr;
    HSD_GObj* yoyo_GObj;

    fighter_data = fighter_gobj->user_data;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x158, 0x40000, 0, 13.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    fighter_data2 = GetFighterData(fighter_gobj);
    fighter_data2 = GetFighterData(fighter_gobj);
    fighter_data2->x2340_stateVar1 = 0xE;
    if ((yoyo_GObj = fighter_data2->sa.ness.x222C) != 0U) {
        yoyo_attr = GetYoyoAttr(yoyo_GObj);
        sp34 = lbl_803B75A4;
        func_802C0010(yoyo_GObj, &sp34);
        fighter_data2->sa.ness.x223C = yoyo_attr->x18_SPIN_TEXANIM_SPEED;
    }

    func_80088510(fighter_data2, 0x334AA, 0x7F, 0x40);
    func_80114F70(fighter_data2->x2114_SmashAttr.x2118_frames, fighter_gobj);
    fighter_data->x2222_flag.bits.b2 = 1;
    fighter_data->cb.x21C0_callback_OnGiveDamage = lbl_80115C74;
    fighter_data->cb.x21BC_callback_Accessory4 = lbl_80114EB8;
}