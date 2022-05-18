#include "ftness.h"

#include "melee/lb/lbvector.h"

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

void lbl_80114EB8(HSD_GObj* fighter_gobj)  // Ness D-Smash Hitbox Position Update //
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
        if (fighter_data->x2344_s32 > 0)
        {
            fighter_data->x2344_s32 = fighter_data->x2344_s32 - 1;
            if (fighter_data->x2344_s32 == 0)
            {
                func_80008440(&fighter_data->x914->x0);
                func_80008434(&fighter_data->x914->x0);
            }
        }
    }
};


// 0x80114F70 //
// https://decomp.me/scratch/ylt9e //
void func_80114F70(HSD_GObj* fighter_gobj, f32 unk_float) // Apply modified damage to D-Smash Yo-Yo hitbox after charge //
{
    Fighter* fighter_data = fighter_gobj->user_data;
    ftNessAttributes* ness_attr = fighter_data->x2D4_specialAttributes;
    f32 charge_duration;
    f32 damage_mul;
    f32 new_damage1;
    f32 new_damage2;

    if (unk_float != 0.0f)
    {
        if (fighter_data->x914->x0 == 1)
        {
            charge_duration = unk_float / ness_attr->xAC_SMASH_CHARGE_DURATION;
            damage_mul = ness_attr->xB0_SMASH_CHARGE_DAMAGE_MULTIPLIER * 0.0039059999398887157f - 1.0f; // likely 1/256, try this if it absolutely doesn't match //
            new_damage1 = damage_mul * charge_duration + 1.0f;
            new_damage2 = fighter_data->x914->xC * new_damage1;

            func_8007ABD0(&fighter_data->x914[0], new_damage2, fighter_gobj);
        }
    }
};


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

// 0x80115114 //
// https://decomp.me/scratch/TMsSU //
void func_80115114(HSD_GObj* fighter_gobj, Point3d* arg1) {

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
    ItemData* itData;
    itYoyoAttributes* yoyo_attr;
    SmashAttr* temp_r4_2;
    s32 Cmp;

    temp_r31 = fighter_gobj->user_data;
    temp_r31->x2340_stateVar1 = 0;
    temp_r0 = temp_r31->sa.ness.x222C;
    temp_r3 = temp_r0;
    if (temp_r0 != 0) {
        temp_r7 = temp_r3->user_data;
        itData = temp_r7->xC4_data;
        yoyo_attr = itData->x4_ext_attr;
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