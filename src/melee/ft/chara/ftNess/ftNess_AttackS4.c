#include <melee/ft/chara/ftNess/ftNess.h>

// 0x80114BF4 //
void ftNess_AttackS4_OnReflect(HSD_GObj* fighter_gobj) // Ness's F-Smash OnReflect callback //
{
    func_80088148(fighter_gobj->user_data, 0xE0U, 0x7FU, 0x40U);
};

extern HSD_GObj* func_802AD478(HSD_GObj*, Vec3*, s32, f32);

// 0x80114C24 //
// https://decomp.me/scratch/66eaB //
void ftNess_AttackS4_Action(HSD_GObj* fighter_gobj) // Ness's F-Smash Action State handler //
{
    Fighter* fp;
    HSD_GObj* baseballBatGObj;

    fp = getFighterPlus(fighter_gobj);

    fp->x2218_flag.bits.b0 = 0;

    fp->x2200_ftcmd_var0 = FALSE;

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_ATTACKS4, 0, NULL, 0.0f, 1.0f, 0.0f);

    func_8006EBA4(fighter_gobj);

    baseballBatGObj = func_802AD478(fighter_gobj, &fp->xB0_pos, 0x2A /* Item Hold Bone */, fp->x2C_facing_direction);

    fp->sa.ness.x2248_baseballBatGObj = baseballBatGObj;

    if (baseballBatGObj != NULL)
    {
        fp->cb.x21E4_callback_OnDeath2 = ftNess_OnDamage;
        fp->cb.x21DC_callback_OnTakeDamage = ftNess_OnDamage;
    }
};

// 0x80114CC0
// https://decomp.me/scratch/E8Nsh //
BOOL ftNess_CheckNessBatRemove(HSD_GObj* fighter_gobj) // Check if Ness is in F-Smash + has Baseball Bat item //
{

    Fighter* fp = fighter_gobj->user_data;

    if (fp->x10_action_state_index != AS_NESS_ATTACKS4)

    {
        return TRUE;
    }

    if (fp->sa.ness.x2248_baseballBatGObj == NULL)

    {
        return TRUE;
    }

    return FALSE;
};

extern void func_802AD6B8(HSD_GObj*);

// 0x80114CF4 //
// https://decomp.me/scratch/mpl3X //
void ftNess_ItemNessBatRemove(HSD_GObj* fighter_gobj) // Remove Baseball Bat //
{

    Fighter* fp = fighter_gobj->user_data;

    if (fp->sa.ness.x2248_baseballBatGObj != NULL)
    {
        func_802AD6B8(fp->sa.ness.x2248_baseballBatGObj);
        fp->sa.ness.x2248_baseballBatGObj = NULL;
    }

};

// 0x80114D34
// https://decomp.me/scratch/6ulYB //
void ftNess_ItemNessBatSetNULL(HSD_GObj* fighter_gobj) // Clear Baseball Bat GObj pointer //
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->sa.ness.x2248_baseballBatGObj != NULL)
    {
        fp->sa.ness.x2248_baseballBatGObj = NULL;
    }
};

extern void ftColl_CreateReflectHit(HSD_GObj*, ReflectDesc*, void(*cb_OnReflect)(HSD_GObj*)); // Create Reflect Bubble //

// 0x80114D50
// https://decomp.me/scratch/M8dFk //
void ftNess_AttackS4_Anim(HSD_GObj* fighter_gobj) // Ness's F-Smash Animation callback //
{
    Fighter* fighter_data1 = getFighterPlus(fighter_gobj);
    Fighter* fighter_data2;
    ftNessAttributes* ness_attr;

    if (fighter_data1->x2218_flag.bits.b3 == 0)
    {
        if (fighter_data1->x2200_ftcmd_var0 != FALSE) // Check if reflect bubble flag is enabled in fp script //
        {
            ness_attr = fighter_data1->x2D4_specialAttributes;
            ftColl_CreateReflectHit(fighter_gobj, &ness_attr->xB8_BASEBALL_BAT, ftNess_AttackS4_OnReflect); // Create reflect bubble //
        }
    }

    else if (fighter_data1->x2200_ftcmd_var0 == FALSE)
    {
        fighter_data1->x2218_flag.bits.b3 = 0; // Toggle reflect bubble OFF//
    }

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE) // Check if animation has frames remaining //
    {

        fighter_data2 = getFighter(fighter_gobj);
        if (fighter_data2->sa.ness.x2248_baseballBatGObj != NULL)
        {
            func_802AD6B8(fighter_data2->sa.ness.x2248_baseballBatGObj); // Despawn the Baseball Bat if animation is over //
            fighter_data2->sa.ness.x2248_baseballBatGObj = NULL;
        }
        func_8008A2BC(fighter_gobj);
    }
}

extern void func_8008A4D4(HSD_GObj*); // Interrupt_Wait //

// 0x80114E04
// https://decomp.me/scratch/HTgCI //
void ftNess_AttackS4_IASA(HSD_GObj* fighter_gobj) // Ness's F-Smash IASA Callback //
{
    Fighter* fp = getFighterPlus(fighter_gobj);

    if (fp->x2218_flag.bits.b0 != 0)
    {
        if (fp->sa.ness.x2248_baseballBatGObj != NULL)
        {
            func_802AD6B8(fp->sa.ness.x2248_baseballBatGObj);
            fp->sa.ness.x2248_baseballBatGObj = NULL;
        }
        func_8008A4D4(fighter_gobj);
    }
};

extern void func_8007AEF8(HSD_GObj*); // Enable Reflect Bubble Update //

// 0x80114E64 //
// https://decomp.me/scratch/wQc4r //
void ftNess_AttackS4_Phys(HSD_GObj* fighter_gobj) // Ness's F-Smash Physics Callback //

{
    func_80084FA8(fighter_gobj);
    func_8007AEF8(fighter_gobj);
};

extern void func_80084104(HSD_GObj*); // CollisionCheck_StopLedge //

// 0x80114E98 //
// https://decomp.me/scratch/nJ4hj //
void ftNess_AttackS4_Coll(HSD_GObj* fighter_gobj) // Ness's F-Smash Collision Callback //
{
    func_80084104(fighter_gobj);
};
