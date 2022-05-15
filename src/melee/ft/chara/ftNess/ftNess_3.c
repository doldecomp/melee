#include "ftness.h"

s32 func_80114CC0(HSD_GObj* fighter_gobj) 
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

void func_80114CF4(HSD_GObj* fighter_gobj) {

    Fighter* fighter_data = fighter_gobj->user_data;
    HSD_GObj* item_gobj = fighter_data->sa.ness.x2248;

    if (item_gobj != 0)
    {
        func_802AD6B8(item_gobj);
        fighter_data->sa.ness.x2248 = 0;
    }

};

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

void lbl_80114D50(HSD_GObj* fighter_gobj) //Ness's F-Smash Animation Callback//
{
    Fighter* fighter_data1 = fighter_gobj->user_data;
    Fighter* fighter_data2;
    NessAttr* ness_attr;
    u32* ReflectDesc;
    u32 item_gobj;

    if (fighter_data1->x2218_flag.bits.b3 == 0)
    {
        if (fighter_data1->x2200_ftcmd_var0 != 0)
        {
            ness_attr = fighter_data1->x2D4_specialAttributes;
            func_8007B23C(fighter_gobj, &ness_attr->REFLECTION_BUBBLE_BONE_ID, lbl_80114BF4); // Creates reflect bubble //
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
}

void func_8007AEF8(HSD_GObj*); // Enable Reflect Bubble Update //

void lbl_80114E64(HSD_GObj* fighter_gobj) // Ness's F-Smash Physics Callback //

{
    func_80084FA8(fighter_gobj);
    func_8007AEF8(fighter_gobj);
}

void func_80084104(HSD_GObj*); // CollisionCheck_StopLedge //

void lbl_80114E98(HSD_GObj* fighter_gobj) // Ness's F-Smash Collision Callback //
{
    func_80084104(fighter_gobj);
}