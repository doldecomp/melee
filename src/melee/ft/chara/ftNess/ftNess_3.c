#include "ftness.h"

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
extern f32 lbl_804D96C0;

// 0x80114EB8 //
// https://decomp.me/scratch/ppemH //

void lbl_80114EB8(HSD_GObj* fighter_gobj)  // Ness D-Smash Hitbox Position Update //
{
    Fighter* fighter_data = fighter_gobj->user_data;
    Hitbox* hitbox_data = fighter_data->x914;

    if (hitbox_data->x0 != 0)
    {
        if (fighter_data->sa.ness.x2230 != 0.0f || fighter_data->sa.ness.x2234 != 0.0f)
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


