#include "ftNess.h"

// Setup float order //
f32 return_float1(void) // -0x62B0 //
{
    return 5.0f;
}

f32 return_float2(void) // -0x62AC //
{
    return 0.0f;
}

f32 return_float3(void) // -0x62A8 //
{
    return 8.333333015441895f;
}

f32 return_float4(void) // -0x62A4 //
{
    return 12.333333015441895f;
}

f32 return_float5(void) // -0x62A0 // 
{
    return 1.5707963705062866f;
}

f64 return_float6(void) // -0x6294 //
{
    return 6.283185307179586;
}

f64 return_float7(void) // -0x628C //
{
    return 3.141592653589793;
}

f64 return_float8(void) // -0x6284 //
{
    return 1.5707963267948966;
}

f32 return_float9(void) // -0x6280 //
{
    return 1.0f;
}

f64 return_float10(void) // -0x6278 //
{
    return 0.0;
}

f32 return_float12(void) // -0x6270 //
{
    return 0.01745329238474369f;
}

f32 return_float13(void)
{
    return 90.0f;
}

f32 return_float14(void)
{
    return -1.0f;
}

f32 return_float15(void)
{
    return 0.5f;
}

f64 return_float16(void)
{
    return 0.5;
}

f64 return_float17(void)
{
    return 3.0;
}

f32 return_float18(void)
{
    return 9.999999747378752e-05f;
}

f32 return_float19(void)
{
    return -9.999999747378752e-05f;
}

f64 return_float20(void)
{
    return -1.5707963267948966;
}

extern void efLib_DestroyAll(HSD_GObj*);

#pragma dont_inline on

// 0x80117B70 //
// https://decomp.me/scratch/242L6 //
void ftNess_SpecialHiStopGFX(HSD_GObj* fighter_gobj)  // Removes GFX //
{
    s32 ASID;
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    ASID = fighter_data->x10_action_state_index;
    switch (ASID)
    {
    case AS_NESS_SPECIALHI_START:
    case AS_NESS_SPECIALHI_HOLD:
    case AS_NESS_SPECIALHI_END:
    case AS_NESS_SPECIALHI:
    case AS_NESS_SPECIALAIRHI_START:
    case AS_NESS_SPECIALAIRHI_HOLD:
    case AS_NESS_SPECIALAIRHI_END:
    case AS_NESS_SPECIALAIRHI:
    case AS_NESS_SPECIALAIRHI_HITWALL:
        efLib_DestroyAll(fighter_gobj);
        fighter_data->sa.ness.x224C_thunderGFX = FALSE;
    default:
        return;
    }
}

#pragma dont_inline off

extern void func_802AB3F0(HSD_GObj*, void*, s32);

inline f32 fabs_inline_ness(f32 x)
{
    if (x < 0)
    {
        return -x;
    }
    else
    {
        return x;
    }
}

inline BOOL check_distance(Vec3* pos, Vec2* pair)
{

    if ((fabs_inline_ness(pos->x - pair->x) < 8.333333015441895f) &&
        (fabs_inline_ness(pos->y - pair->y) < 12.333333015441895f))
    {
        return TRUE;
    }
    return FALSE;
}

// 0x80117BBC //
// https://decomp.me/scratch/xTtbs // Very confusing and fabricated match based on auto-decomp //
// https://decomp.me/scratch/hwphL // Proper match //
BOOL ftNess_ItemPKThunder_CheckNessCollide(HSD_GObj* fighter_gobj) 
{
    s32 topfiller[2];

    Vec2 pair;
    Vec3 pos;

    s32 middlefiller[3];

    Vec2 pair2;
    Vec3 pos2;

    s32 bottom_filler[10];

    Fighter* fighter_data = getFighter(fighter_gobj);
    s32 ret = FALSE;

    if (!fighter_data->sa.ness.x2244_pkThunderGObj) return 0;

    switch (fighter_data->x2340_stateVar1)
    {
    case FALSE:
        pos = fighter_data->xB0_pos;
        pos.y += 5.0f * fighter_data->x34_scale.y;
        func_802AB3F0(fighter_data->sa.ness.x2244_pkThunderGObj, &pair, 0);
        if (check_distance(&pos, &pair) == TRUE) 
        {
            fighter_data->x2340_stateVar1 = 2;
            func_802AB3F0(fighter_data->sa.ness.x2244_pkThunderGObj, &fighter_data->x2350_stateVar5, 0);
            func_802AB3F0(fighter_data->sa.ness.x2244_pkThunderGObj, &fighter_data->x235C_s32, 1);
            ret = TRUE;
        }
        break;

    case TRUE:
        pos2 = fighter_data->xB0_pos;
        pos2.y += 5.0f * fighter_data->x34_scale.y;
        func_802AB3F0(fighter_data->sa.ness.x2244_pkThunderGObj, &pair2, 0);
        if (!check_distance(&pos2, &pair2))
        {
            fighter_data->x2340_stateVar1 = FALSE;
        }
    }
    return ret;
}

// 0x80117D9C //
// https://decomp.me/scratch/QeIRL //
BOOL ftNess_CheckSpecialHiHold(HSD_GObj* fighter_gobj) // Checks if Ness is in SpecialHiHold/SpecialAirHiHold (PK Thunder control loop) //
{
    s32 ASID;
    Fighter* fighter_data;
    s32 phi_r3;
    Fighter* new_var;

    fighter_data = (new_var = getFighter(fighter_gobj));
    ASID = fighter_data->x10_action_state_index;

    phi_r3 = TRUE;

    if ((ASID != AS_NESS_SPECIALHI_HOLD) && (ASID != AS_NESS_SPECIALAIRHI_HOLD))
    {
        phi_r3 = FALSE;
    }

    if (phi_r3 != FALSE)
    {
        return TRUE;
    }

    return FALSE;
}

// 0x80117DD4 //
// https://decomp.me/scratch/e00Cp //
void ftNess_ItemPKThunderRemove(HSD_GObj* fighter_gobj)  // OnTakeDamage? //
{
    Fighter* fighter_data;
    Fighter* temp_fighter;
    s32 ASID;

    temp_fighter = fighter_gobj->user_data;
    if (temp_fighter->sa.ness.x2244_pkThunderGObj != NULL)
    {
        temp_fighter->sa.ness.x2244_pkThunderGObj = NULL;
    }
    fighter_data = getFighter(fighter_gobj);
    ASID = fighter_data->x10_action_state_index;
    switch (ASID)
    {
    case AS_NESS_SPECIALHI_START:
    case AS_NESS_SPECIALHI_HOLD:
    case AS_NESS_SPECIALHI_END:
    case AS_NESS_SPECIALHI:
    case AS_NESS_SPECIALAIRHI_START:
    case AS_NESS_SPECIALAIRHI_HOLD:
    case AS_NESS_SPECIALAIRHI_END:
    case AS_NESS_SPECIALAIRHI:
    case AS_NESS_SPECIALAIRHI_HITWALL:
        efLib_DestroyAll(fighter_gobj);
        fighter_data->sa.ness.x224C_thunderGFX = FALSE;

    default:
        temp_fighter->cb.x21E4_callback_OnDeath2 = NULL;
        temp_fighter->cb.x21DC_callback_OnTakeDamage = NULL;
        func_8007592C(temp_fighter, 0, 0.0f);
    }
}

extern void func_802AB9C0(HSD_GObj*);

// 0x80117E60 //
// https://decomp.me/scratch/MTTJq //
void ftNess_SpecialHiTakeDamage(HSD_GObj* fighter_gobj)  // OnTakeDamage again? //
{
    s32 ASID;
    Fighter* fighter_data;
    Fighter* fighter_data2;
    Fighter* temp_fighter;

    temp_fighter = fighter_gobj->user_data;
    fighter_data = temp_fighter;
    if (temp_fighter->sa.ness.x2244_pkThunderGObj != NULL)
    {
        func_802AB9C0(temp_fighter->sa.ness.x2244_pkThunderGObj);
        fighter_data->sa.ness.x2244_pkThunderGObj = NULL;
    }
    fighter_data2 = getFighter(fighter_gobj);
    ASID = fighter_data2->x10_action_state_index;
    switch (ASID)
    {
    case AS_NESS_SPECIALHI_START:
    case AS_NESS_SPECIALHI_HOLD:
    case AS_NESS_SPECIALHI_END:
    case AS_NESS_SPECIALHI:
    case AS_NESS_SPECIALAIRHI_START:
    case AS_NESS_SPECIALAIRHI_HOLD:
    case AS_NESS_SPECIALAIRHI_END:
    case AS_NESS_SPECIALAIRHI:
    case AS_NESS_SPECIALAIRHI_HITWALL:
        efLib_DestroyAll(fighter_gobj);
        fighter_data2->sa.ness.x224C_thunderGFX = FALSE;
    default:
        temp_fighter->cb.x21E4_callback_OnDeath2 = NULL;
        temp_fighter->cb.x21DC_callback_OnTakeDamage = NULL;
        func_8007592C(temp_fighter, 0, 0.0f);
    }
}

// 0x80117F00 //
// https://decomp.me/scratch/1nlBY //
void ftNess_ItemPKThunderCheckOwn(HSD_GObj* fighter_gobj, HSD_GObj* thunder_gobj) // Run from PK Thunder's OnReflect callback. Sets Ness's reference to PK Thunder to NULL if he is reflecting his own PK Thunder. //
{
    HSD_GObj* temp_thunder;
    Fighter* temp_fighter = getFighter(fighter_gobj);

    temp_thunder = temp_fighter->sa.ness.x2244_pkThunderGObj;
    if ((temp_thunder != NULL) && (temp_thunder == thunder_gobj))
    {
        temp_fighter->sa.ness.x2244_pkThunderGObj = NULL;
    }
}

// 0x80117F24 //
// https://decomp.me/scratch/3URl3 //
void ftNess_SpecialAirHi_CollisionModVel(HSD_GObj* fighter_gobj, CollData* coll_data) // Adjusts Ness's velocity upon interacting with collisions during SpecialAirHi //
{
    Vec3 sp14;
    Fighter* fighter_data;
    f32 phi_f1;
    f32 phi_f3;
    f32 unused;

    fighter_data = getFighter(fighter_gobj);
    while (fighter_data->x2368_f32 < 0.0f)
    {
        fighter_data->x2368_f32 += (f64)6.283185307179586;
    }
    while (fighter_data->x2368_f32 > (f64)6.283185307179586)
    {
        fighter_data->x2368_f32 -= (f64)6.283185307179586;
    }
    if ((coll_data->x134_envFlags & 0x3F) != 0)
    {
        phi_f1 = func_someCalcAngle_80022C30(coll_data->x168_vec.y, coll_data->x168_vec.x);
        while (phi_f1 < 0.0f)
        {
            phi_f1 += (f64)6.283185307179586;
        }

        while (phi_f1 > (f64)6.283185307179586)
        {
            phi_f1 -= (f64)6.283185307179586;
        }
        phi_f3 = ((f64)3.141592653589793 + (f64)fighter_data->x2368_f32);

        while (phi_f3 < 0.0f)
        {
            phi_f3 += (f64)6.283185307179586;
        }

        while (phi_f3 > (f64)6.283185307179586)
        {
            phi_f3 -= (f64)6.283185307179586;
        }
        if ((phi_f3 - phi_f1) < 0.0f)
        {
            phi_f1 += (f64)1.5707963267948966;
        }
        else
        {
            phi_f1 -= (f64)1.5707963267948966;
        }
    }
    if ((coll_data->x134_envFlags & 0xFC0) != 0)
    {
        phi_f1 = func_someCalcAngle_80022C30(coll_data->x17C_vec.y, coll_data->x17C_vec.x);
        phi_f3 = (f64)3.141592653589793 + phi_f1;

        while (phi_f3 < 0.0f)
        {
            phi_f3 += (f64)6.283185307179586;
        }

        while (phi_f3 > (f64)6.283185307179586)
        {
            phi_f3 -= (f64)6.283185307179586;
        }
        if ((fighter_data->x2368_f32 - phi_f3) < 0.0f)
        {
            phi_f1 += (f64)1.5707963267948966;
        }
        else
        {
            phi_f1 -= (f64)1.5707963267948966;
        }
    }
    sp14.y = 0.0f;
    sp14.x = 0.0f;
    sp14.z = 1.0f;
    lbvector_RotateAboutUnitAxis(&fighter_data->x80_self_vel, &sp14, phi_f1 - fighter_data->x2368_f32);
    fighter_data->x2368_f32 = func_someCalcAngle_80022C30(fighter_data->x80_self_vel.y, fighter_data->x80_self_vel.x);
}

// 0x80118120 //
// https://decomp.me/scratch/ARLRd //
void ftNess_SpecialHi_StartAction(HSD_GObj* fighter_gobj)  // Ness's grounded PK Thunder Start Action State handler //
{
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f1_2;
    Fighter* fighter_data;
    ftNessAttributes* ness_attr;
    Fighter* temp_fighter;
    ftNessAttributes* temp_attr;
    f64 phi_f0;

    temp_f1 = 0.0f;
    fighter_data = getFighter(fighter_gobj);
    ness_attr = fighter_data->x2D4_specialAttributes;
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALHI_START, 0, NULL, 0.0f, 1.0f, 0.0f);
    fighter_data->x220C_ftcmd_var3 = 0;
    fighter_data->x2208_ftcmd_var2 = 0;
    fighter_data->x2204_ftcmd_var1 = 0;
    fighter_data->x2200_ftcmd_var0 = 0;
    temp_fighter = fighter_gobj->user_data;
    temp_attr = getFtSpecialAttrs(temp_fighter);
    temp_fighter->x2344_stateVar2 = (s32)temp_attr->x40_PK_THUNDER_LOOP1;
    temp_fighter->x2348_stateVar3 = (s32)temp_attr->x44_PK_THUNDER_LOOP2;
    temp_fighter->x234C_stateVar4 = (s32)temp_attr->x48_PK_THUNDER_FALLING_ACCEL_DELAY;
    temp_f1_2 = 0.0f;
    temp_fighter->x2384_f32 = 0.0f;
    temp_fighter->x237C_f32 = 0.0f;
    temp_fighter->x2378_f32 = 0.0f;
    temp_fighter->x2374_f32 = 0.0f;
    temp_fighter->x238C_f32 = 0.0f;
    temp_fighter->x2388_f32 = 0.0f;
    temp_fighter->cb.x21E4_callback_OnDeath2 = NULL;
    temp_fighter->cb.x21DC_callback_OnTakeDamage = NULL;
    func_8007592C(temp_fighter, 0, 0.0f);
    fighter_data->x2340_stateVar1 = TRUE;
    fighter_data->x234C_stateVar4 = (s32)ness_attr->x48_PK_THUNDER_FALLING_ACCEL_DELAY;
    fighter_data->x2380 = 0;
    fighter_data->x2350_stateVar5_f32 = 0.0f;
    fighter_data->x2350_stateVar5_f32 = 0.0f;
    fighter_data->x2350_stateVar5_f32 = 0.0f;
    fighter_data->x235C_f32 = 0.0f;
    fighter_data->x235C_f32 = 0.0f;
    fighter_data->x235C_f32 = 0.0f;
    if (1.0f == fighter_data->x2C_facing_direction) 
    {
        phi_f0 = (f64)0.0;
    }
    else 
    {
        phi_f0 = (f64)3.141592653589793;
    }
    fighter_data->x2368_f32 = (f32)phi_f0;
    fighter_data->x2370_f32 = (f32)1.0f;
    fighter_data->x236C_f32 = (f32)0.0f;
    func_8006EBA4(fighter_gobj);
}

// 0x80118250 //
// https://decomp.me/scratch/D08nX //
void ftNess_SpecialAirHiStart_Action(HSD_GObj* fighter_gobj)  // Ness's aerial PK Thunder Start Action State handler //
{
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f1_2;
    Fighter* fighter_data;
    ftNessAttributes* ness_attr;
    Fighter* temp_fighter;
    ftNessAttributes* temp_attr;
    f64 phi_f0;

    temp_f1 = 0.0f;
    fighter_data = getFighterPlus(fighter_gobj);
    ness_attr = fighter_data->x2D4_specialAttributes;
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRHI_START, 0, NULL, 0.0f, 1.0f, 0.0f);
    fighter_data->x220C_ftcmd_var3 = 0;
    fighter_data->x2208_ftcmd_var2 = 0;
    fighter_data->x2204_ftcmd_var1 = 0;
    fighter_data->x2200_ftcmd_var0 = 0;
    temp_fighter = fighter_gobj->user_data;
    temp_attr = temp_fighter->x2D4_specialAttributes;
    temp_fighter->x2344_stateVar2 = (s32)temp_attr->x40_PK_THUNDER_LOOP1;
    temp_fighter->x2348_stateVar3 = (s32)temp_attr->x44_PK_THUNDER_LOOP2;
    temp_fighter->x234C_stateVar4 = (s32)temp_attr->x48_PK_THUNDER_FALLING_ACCEL_DELAY;
    temp_f1_2 = 0.0f;
    temp_fighter->x2384_f32 = 0.0f;
    temp_fighter->x237C_f32 = 0.0f;
    temp_fighter->x2378_f32 = 0.0f;
    temp_fighter->x2374_f32 = 0.0f;
    temp_fighter->x238C_f32 = 0.0f;
    temp_fighter->x2388_f32 = 0.0f;
    temp_fighter->cb.x21E4_callback_OnDeath2 = NULL;
    temp_fighter->cb.x21DC_callback_OnTakeDamage = NULL;
    func_8007592C(temp_fighter, 0, 0.0f);
    fighter_data->x2340_stateVar1 = TRUE;
    fighter_data->x234C_stateVar4 = (s32)ness_attr->x48_PK_THUNDER_FALLING_ACCEL_DELAY;
    fighter_data->x2380 = 0;
    fighter_data->x2350_stateVar5_f32 = 0.0f;
    fighter_data->x2350_stateVar5_f32 = 0.0f;
    fighter_data->x2350_stateVar5_f32 = 0.0f;
    fighter_data->x235C_f32 = 0.0f;
    fighter_data->x235C_f32 = 0.0f;
    fighter_data->x235C_f32 = 0.0f;
    if (1.0f == fighter_data->x2C_facing_direction) 
    {
        phi_f0 = (f64)0.0;
    }
    else {
        phi_f0 = (f64)3.141592653589793;
    }
    fighter_data->x2368_f32 = (f32)phi_f0;
    fighter_data->x2370_f32 = (f32)1.0f;
    fighter_data->x236C_f32 = (f32)0.0f;
    fighter_data->x80_self_vel.y = 0.0f;
    func_8006EBA4(fighter_gobj);
}

extern void func_8007D60C(Fighter*);
extern void func_80097D40(HSD_GObj*);

// 0x80118384 //
// https://decomp.me/scratch/nOcOo // The link itself agrees with how ramen noodles this function is //
void ftNess_SpecialHi_Action(HSD_GObj* fighter_gobj)  // Ness's grounded PK Thunder 2 Action State handler //
{
    Vec3 sp40;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f2;
    f32 temp_f3;
    s32 ASID;
    Fighter* fighter_data;
    Fighter* fighter_data2;
    Fighter* fighter_data3;
    ftNessAttributes* ness_attr;
    ftNessAttributes* ness_attr2;
    f32 phi_f0;
    f32 phi_f0_2;

    fighter_data = getFighterPlus(fighter_gobj);
    ness_attr = fighter_data->x2D4_specialAttributes;
    if ((fighter_data->x6F0_collData.filler_x150 & 0x100) == 0)
    {
        temp_f3 = 5.0f;
        sp40.x = fighter_data->xB0_pos.x - fighter_data->x2350_stateVar5_f32;
        temp_f2 = fighter_data->x34_scale.y;
        temp_f1 = (temp_f3 * temp_f2) + fighter_data->xB0_pos.y;
        sp40.y = temp_f1 - fighter_data->x2354_stateVar6;
        sp40.z = 0.0f;
        temp_f1_2 = lbvector_Angle(&fighter_data->x6F0_collData.x154_groundNormal, &sp40);

        if (!(temp_f1_2 < 1.5707963705062866f))
        {
            if (!(temp_f1_2 > (0.01745329238474369f * (90.0f + ness_attr->x60_PK_THUNDER_2_KNOCKDOWN_ANGLE))))
            {
                if (sp40.x >= 0.0f)
                {
                    phi_f0 = 1.0f;
                }
                else
                {
                    phi_f0 = -1.0f;
                }
                fighter_data->x2C_facing_direction = phi_f0;
                if (sp40.y >= 0.0f)
                {
                    phi_f0_2 = 1.0f;
                }
                else
                {
                    phi_f0_2 = -1.0f;
                }
                fighter_data->x2370_f32 = phi_f0_2;
                fighter_data->x2368_f32 = func_someCalcAngle_80022C30(sp40.y, sp40.x);
                temp_f1_3 = 0.0f;
                Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALHI, 0, NULL, 0.0f, 1.0f, 0.0f);
                fighter_data->xEC_ground_vel = (f32)(ness_attr->x54_PK_THUNDER_2_MOMENTUM * fighter_data->x2C_facing_direction);
                fighter_data = getFighter(fighter_gobj);
                ness_attr2 = getFtSpecialAttrs(fighter_data);
                fighter_data->x236C_f32 = (f32)ness_attr2->x58_PK_THUNDER_2_UNK1;
                fighter_data2 = getFighter(fighter_gobj);
                func_8007592C(fighter_data2, 0, (fighter_data2->x2C_facing_direction * func_someCalcAngle_80022C30(fighter_data2->x80_self_vel.x, fighter_data2->x80_self_vel.y)) - 1.5707963705062866f);
                fighter_data2 = fighter_data;
                fighter_data2->cb.x21E4_callback_OnDeath2 = NULL;
                fighter_data2->cb.x21DC_callback_OnTakeDamage = NULL;
                fighter_data2->x1968_jumpsUsed = fighter_data2->x110_attr.x168_MaxJumps;
                return;
            }
            goto block_stuff;
        }
    }
    fighter_data->x1968_jumpsUsed = fighter_data->x110_attr.x168_MaxJumps;
    func_8007D60C(fighter_data);
    ftNess_SpecialAirHi_Action(fighter_gobj);
    return;

block_stuff:
    fighter_data3 = fighter_data3 = getFighter(fighter_gobj);
    ASID = fighter_data3->x10_action_state_index;
    switch (ASID)
    {
    case AS_NESS_SPECIALHI_START:
    case AS_NESS_SPECIALHI_HOLD:
    case AS_NESS_SPECIALHI_END:
    case AS_NESS_SPECIALHI:
    case AS_NESS_SPECIALAIRHI_START:
    case AS_NESS_SPECIALAIRHI_HOLD:
    case AS_NESS_SPECIALAIRHI_END:
    case AS_NESS_SPECIALAIRHI:
    case AS_NESS_SPECIALAIRHI_HITWALL:
        efLib_DestroyAll(fighter_gobj);
        fighter_data3->sa.ness.x224C_thunderGFX = FALSE;
    default:
        func_8007592C(fighter_data, 0, 0.0f);
        func_80097D40(fighter_gobj);
        return;
    }
}

inline void NessFloatMath_PKThunder2(HSD_GObj* fighter_gobj)    // Required for 0x80118570 to match //
{
    Fighter* fighter_data;
    ftNessAttributes* ness_attr;
    f32 temp_f2;
    f32 temp_f1;
    f32 phi_f0;

    fighter_data = getFighter(fighter_gobj);
    temp_f2 = fighter_data->xB0_pos.x - fighter_data->x2350_stateVar5_f32;
    ness_attr = getFtSpecialAttrs(fighter_data);
    temp_f1 = ((5.0f * fighter_data->x34_scale.y) + fighter_data->xB0_pos.y) - fighter_data->x2354_stateVar6;
    if (temp_f2 >= 0.0f)
    {
        phi_f0 = 1.0f;
    }
    else
    {
        phi_f0 = -1.0f;
    }
    fighter_data->x2C_facing_direction = phi_f0;
    if (temp_f1 >= 0.0f)
    {
        phi_f0 = 1.0f;
    }
    else
    {
        phi_f0 = -1.0f;
    }
    fighter_data->x2370_f32 = phi_f0;
    fighter_data->x2368_f32 = func_someCalcAngle_80022C30(temp_f1, temp_f2);
    fighter_data->x80_self_vel.x = (f32)(ness_attr->x54_PK_THUNDER_2_MOMENTUM * cosf(fighter_data->x2368_f32));
    fighter_data->x80_self_vel.y = (f32)(ness_attr->x54_PK_THUNDER_2_MOMENTUM * sinf(fighter_data->x2368_f32));
}

// 0x80118570 //
// https://decomp.me/scratch/dMpYH //
void ftNess_SpecialAirHi_Action(HSD_GObj* fighter_gobj)  // Ness's PK Thunder 2 Action State handler if Ness is launching into SpecialAirHi from SpecialHiHold //
{
    ftNessAttributes* ness_attr;
    ftNessAttributes* temp_attr;
    Fighter* fighter_data;
    Fighter* fighter_data3;
    Fighter* fighter_data2;
    f32 temp_f2;
    f32 temp_f1;
    f32 phi_f0;
    f32 phi_f0_2;

    NessFloatMath_PKThunder2(fighter_gobj);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRHI, 0, NULL, 0.0f, 1.0f, 0.0f);
    fighter_data2 = fighter_gobj->user_data;
    temp_attr = getFtSpecialAttrs(fighter_data2);
    fighter_data2->x236C_f32 = temp_attr->x58_PK_THUNDER_2_UNK1;
    fighter_data3 = fighter_gobj->user_data;
    func_8007592C(fighter_data3, 0, (fighter_data3->x2C_facing_direction * func_someCalcAngle_80022C30(fighter_data3->x80_self_vel.x, fighter_data3->x80_self_vel.y)) - 1.5707963705062866f);
    fighter_data2->cb.x21E4_callback_OnDeath2 = NULL;
    fighter_data2->cb.x21DC_callback_OnTakeDamage = NULL;
    fighter_data2->x1968_jumpsUsed = fighter_data2->x110_attr.x168_MaxJumps;
}

extern HSD_GObj* func_802AB58C(HSD_GObj*, Vec3*, f32);

// 0x801186B0 //
// https://decomp.me/scratch/B2vQL //
void ftNess_SpecialHiStart_Anim(HSD_GObj* fighter_gobj) // PK Thunder Grounded Startup Animation //
{
    Vec3 PKThunderSpawn;
    Vec3 Unk;
    Vec3 Unk2;
    Vec2 Unk3;
    HSD_GObj* PKThunderPtr;
    Fighter* fighter_data = fighter_gobj->user_data;
    Fighter* fighter_data2;

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALHI_HOLD, 0, NULL, 0.0f, 1.0f, 0.0f);

        fighter_data2 = fighter_gobj->user_data;
        PKThunderPtr = fighter_data2->sa.ness.x2244_pkThunderGObj;
        if (PKThunderPtr == NULL)
        {
            func_8000B1CC(fighter_data2->x5E8_fighterBones[24].x0_jobj, NULL, &PKThunderSpawn);

            PKThunderSpawn.z = 0.0f;

            PKThunderPtr = func_802AB58C(fighter_gobj, &PKThunderSpawn, fighter_data2->x2C_facing_direction);

            fighter_data2->sa.ness.x2244_pkThunderGObj = PKThunderPtr;

            if (PKThunderPtr != NULL)
            {
                fighter_data2->cb.x21E4_callback_OnDeath2 = ftNess_OnDamage;
                fighter_data2->cb.x21DC_callback_OnTakeDamage = ftNess_OnDamage;
            }
        }

        fighter_data->x1968_jumpsUsed = fighter_data->x110_attr.x168_MaxJumps;

        fighter_data = fighter_gobj->user_data;

        ftNess_SpecialHiStopGFX(fighter_gobj);

        ef_Spawn(0x4EE, fighter_gobj, fighter_data->x5E8_fighterBones[4].x0_jobj);

        fighter_data->sa.ness.x224C_thunderGFX = TRUE;
    }
}

extern HSD_GObj* func_802AB568(HSD_GObj*);

// 0x801187A4 //
// https://decomp.me/scratch/Xm3tt //
void ftNess_SpecialHiHold_Anim(HSD_GObj* fighter_gobj) // Ness's grounded PK Thunder Control Loop Animation callback //
{
    s32 ASID;
    s32 ASID2;
    s32 thunderTimer;
    s32 thunderTimer2;
    Fighter* fighter_data;
    Fighter* fighter_data2;
    Fighter* fighter_data3;

    fighter_data = fighter_gobj->user_data;
    thunderTimer = fighter_data->x2344_stateVar2;
    if (thunderTimer > 0)
    {
        fighter_data->x2344_stateVar2 = (s32)(thunderTimer - 1);
    }
    if (fighter_data->sa.ness.x2244_pkThunderGObj == NULL)
    {
        thunderTimer2 = fighter_data->x2348_stateVar3;
        if (thunderTimer2 > 0)
        {
            fighter_data->x2348_stateVar3 = (s32)(thunderTimer2 - 1);
        }
    }
    if (fighter_data->sa.ness.x2244_pkThunderGObj == NULL) 
    {
        if (((s32)fighter_data->x2344_stateVar2 <= 0) && ((s32)fighter_data->x2348_stateVar3 <= 0))
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALHI_END, 0, NULL, 0.0f, 1.0f, 0.0f);
            fighter_data2 = fighter_gobj->user_data;
            ASID = fighter_data2->x10_action_state_index;
            switch (ASID)
            {
            case AS_NESS_SPECIALHI_START:
            case AS_NESS_SPECIALHI_HOLD:
            case AS_NESS_SPECIALHI_END:
            case AS_NESS_SPECIALHI:
            case AS_NESS_SPECIALAIRHI_START:
            case AS_NESS_SPECIALAIRHI_HOLD:
            case AS_NESS_SPECIALAIRHI_END:
            case AS_NESS_SPECIALAIRHI:
            case AS_NESS_SPECIALAIRHI_HITWALL:
                efLib_DestroyAll(fighter_gobj);
                fighter_data2->sa.ness.x224C_thunderGFX = FALSE;
            }
        }
    }
    else if (func_802AB568(fighter_data->sa.ness.x2244_pkThunderGObj) == fighter_gobj)
    {
        if (ftNess_ItemPKThunder_CheckNessCollide(fighter_gobj) == TRUE)
        {
            ftNess_SpecialHi_Action(fighter_gobj);
        }
    }
    else
    {
        fighter_data->sa.ness.x2244_pkThunderGObj = NULL;
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALHI_END, 0, NULL, 0.0f, 1.0f, 0.0f);
        fighter_data3 = fighter_gobj->user_data;
        ASID2 = fighter_data3->x10_action_state_index;
        switch (ASID2)
        {
        case AS_NESS_SPECIALHI_START:
        case AS_NESS_SPECIALHI_HOLD:
        case AS_NESS_SPECIALHI_END:
        case AS_NESS_SPECIALHI:
        case AS_NESS_SPECIALAIRHI_START:
        case AS_NESS_SPECIALAIRHI_HOLD:
        case AS_NESS_SPECIALAIRHI_END:
        case AS_NESS_SPECIALAIRHI:
        case AS_NESS_SPECIALAIRHI_HITWALL:
            efLib_DestroyAll(fighter_gobj);
            fighter_data3->sa.ness.x224C_thunderGFX = FALSE;
        }
    }
}

// 0x80118900 //
// https://decomp.me/scratch/to1Tc //
void ftNess_SpecialHiEnd_Anim(HSD_GObj* fighter_gobj) // Ness's grounded PK Thunder End Animation callback //
{
    s32 filler[2];
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_8008A2BC(fighter_gobj);
    }
}

// 0x8011893C //
// https://decomp.me/scratch/TxjqG //
void ftNess_SpecialHi_Anim(HSD_GObj* fighter_gobj) // Ness's grounded PK Thunder 2 Animation callback //
{
    f32 temp_f1;
    s32 ASID;
    Fighter* fighter_data;
    Fighter* fighter_data2;
    Fighter* temp_fighter;

    temp_fighter = fighter_gobj->user_data;
    temp_fighter->x2380 = (s32)(temp_fighter->x2380 + 1);
    if ((s32)temp_fighter->x2380 == 1)
    {
        fighter_data = fighter_gobj->user_data;
        ftNess_SpecialHiStopGFX(fighter_gobj);
        ef_Spawn(0x4EF, fighter_gobj, fighter_data->x5E8_fighterBones[4].x0_jobj);
        fighter_data->sa.ness.x224C_thunderGFX = TRUE;
    }
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALHI_END, 0, NULL, 0.0f, 1.0f, 0.0f);
        fighter_data2 = fighter_gobj->user_data;
        ASID = fighter_data2->x10_action_state_index;
        switch (ASID)
        {
        case AS_NESS_SPECIALHI_START:
        case AS_NESS_SPECIALHI_HOLD:
        case AS_NESS_SPECIALHI_END:
        case AS_NESS_SPECIALHI:
        case AS_NESS_SPECIALAIRHI_START:
        case AS_NESS_SPECIALAIRHI_HOLD:
        case AS_NESS_SPECIALAIRHI_END:
        case AS_NESS_SPECIALAIRHI:
        case AS_NESS_SPECIALAIRHI_HITWALL:
            efLib_DestroyAll(fighter_gobj);
            fighter_data2->sa.ness.x224C_thunderGFX = FALSE;
        }
    }
}

// 0x80118A10 //
// https://decomp.me/scratch/A2zUx //
void ftNess_SpecialAirHiStart_Anim(HSD_GObj* fighter_gobj) // Ness's aerial PK Thunder Start Animation callback //
{
    Vec3 PKThunderSpawn;
    Vec3 Unk;
    Vec3 Unk2;
    Vec2 Unk3;
    HSD_GObj* PKThunderPtr;
    Fighter* fighter_data = fighter_gobj->user_data;
    Fighter* fighter_data2;

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRHI_HOLD, 0, NULL, 0.0f, 1.0f, 0.0f);

        fighter_data2 = fighter_gobj->user_data;
        PKThunderPtr = fighter_data2->sa.ness.x2244_pkThunderGObj;
        if (PKThunderPtr == 0)
        {
            func_8000B1CC(fighter_data2->x5E8_fighterBones[24].x0_jobj, NULL, &PKThunderSpawn);

            PKThunderSpawn.z = 0.0f;

            PKThunderPtr = func_802AB58C(fighter_gobj, &PKThunderSpawn, fighter_data2->x2C_facing_direction);

            fighter_data2->sa.ness.x2244_pkThunderGObj = PKThunderPtr;

            if (PKThunderPtr != NULL)
            {
                fighter_data2->cb.x21E4_callback_OnDeath2 = ftNess_OnDamage;
                fighter_data2->cb.x21DC_callback_OnTakeDamage = ftNess_OnDamage;
            }
        }

        fighter_data->x1968_jumpsUsed = fighter_data->x110_attr.x168_MaxJumps;

        fighter_data = fighter_gobj->user_data;

        ftNess_SpecialHiStopGFX(fighter_gobj);

        ef_Spawn(0x4EE, fighter_gobj, fighter_data->x5E8_fighterBones[4].x0_jobj);

        fighter_data->sa.ness.x224C_thunderGFX = TRUE;
    }
}

// 0x80118B04 //
// https://decomp.me/scratch/3PGI5 //
void ftNess_SpecialAirHiHold_Anim(HSD_GObj* fighter_gobj) // Ness's aerial PK Thunder Control Loop Animation callback //
{
    s32 filler[11];
    s32 ASID;
    s32 ASID2;
    s32 thunderTimer1;
    s32 thunderTimer2;
    ftNessAttributes* temp_attr;
    Fighter* fighter_data;
    Fighter* fighter_data2;
    Fighter* fighter_data3;
    Fighter* fighter_data4;
    Fighter* fighter_data5;
    Fighter* fighter_data_r30;

    fighter_data = fighter_gobj->user_data;
    thunderTimer1 = fighter_data->x2344_stateVar2;
    if (thunderTimer1 > 0)
    {
        fighter_data->x2344_stateVar2 = (s32)(thunderTimer1 - 1);
    }
    if (fighter_data->sa.ness.x2244_pkThunderGObj == NULL) 
    {
        thunderTimer2 = fighter_data->x2348_stateVar3;
        if (thunderTimer2 > 0)
        {
            fighter_data->x2348_stateVar3 = (s32)(thunderTimer2 - 1);
        }
    }
    if (fighter_data->sa.ness.x2244_pkThunderGObj == NULL)
    {
        if (((s32)fighter_data->x2344_stateVar2 <= 0) && ((s32)fighter_data->x2348_stateVar3 <= 0))
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRHI_END, 0, NULL, 0.0f, 1.0f, 0.0f);
            fighter_data2 = fighter_gobj->user_data;
            ASID = fighter_data2->x10_action_state_index;
            switch (ASID)
            {
            case AS_NESS_SPECIALHI_START:
            case AS_NESS_SPECIALHI_HOLD:
            case AS_NESS_SPECIALHI_END:
            case AS_NESS_SPECIALHI:
            case AS_NESS_SPECIALAIRHI_START:
            case AS_NESS_SPECIALAIRHI_HOLD:
            case AS_NESS_SPECIALAIRHI_END:
            case AS_NESS_SPECIALAIRHI:
            case AS_NESS_SPECIALAIRHI_HITWALL:
                efLib_DestroyAll(fighter_gobj);
                fighter_data2->sa.ness.x224C_thunderGFX = FALSE;
            }
        }
    }
    else if (func_802AB568(fighter_data->sa.ness.x2244_pkThunderGObj) == fighter_gobj)
    {
        if (ftNess_ItemPKThunder_CheckNessCollide(fighter_gobj) == TRUE)
        {
            NessFloatMath_PKThunder2(fighter_gobj);
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRHI, 0, NULL, 0.0f, 1.0f, 0.0f);
            fighter_data4 = fighter_gobj->user_data;
            temp_attr = fighter_data4->x2D4_specialAttributes;
            fighter_data4->x236C_f32 = temp_attr->x58_PK_THUNDER_2_UNK1;
            fighter_data_r30 = fighter_gobj->user_data;
            func_8007592C(fighter_data_r30, 0, (fighter_data_r30->x2C_facing_direction * func_someCalcAngle_80022C30(fighter_data_r30->x80_self_vel.x, fighter_data_r30->x80_self_vel.y)) - 1.5707963705062866f);
            fighter_data4->cb.x21E4_callback_OnDeath2 = NULL;
            fighter_data4->cb.x21DC_callback_OnTakeDamage = NULL;
            fighter_data4->x1968_jumpsUsed = fighter_data4->x110_attr.x168_MaxJumps;
        }
    }
    else
    {
        fighter_data->sa.ness.x2244_pkThunderGObj = NULL;
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRHI_END, 0, NULL, 0.0f, 1.0f, 0.0f);
        fighter_data5 = fighter_gobj->user_data;
        ASID2 = fighter_data5->x10_action_state_index;
        switch (ASID2)
        {
        case AS_NESS_SPECIALHI_START:
        case AS_NESS_SPECIALHI_HOLD:
        case AS_NESS_SPECIALHI_END:
        case AS_NESS_SPECIALHI:
        case AS_NESS_SPECIALAIRHI_START:
        case AS_NESS_SPECIALAIRHI_HOLD:
        case AS_NESS_SPECIALAIRHI_END:
        case AS_NESS_SPECIALAIRHI:
        case AS_NESS_SPECIALAIRHI_HITWALL:
            efLib_DestroyAll(fighter_gobj);
            fighter_data5->sa.ness.x224C_thunderGFX = FALSE;
        }
    }
}

extern void func_800969D8(HSD_GObj*, s32, s32, s32, f32, f32, f32);

// 0x80118D60 //
// https://decomp.me/scratch/JyNWd //
void ftNess_SpecialAirHiEnd_Anim(HSD_GObj* fighter_gobj) // Ness's aerial PK Thunder End Animation callback //
{
    s32 filler[2];
    Fighter* fighter_data;
    Fighter* temp_fighter;
    ftNessAttributes* ness_attr;

    fighter_data = temp_fighter = fighter_gobj->user_data;
    ness_attr = temp_fighter->x2D4_specialAttributes;
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        fighter_data->x1968_jumpsUsed = fighter_data->x110_attr.x168_MaxJumps;
        func_8007D60C(fighter_data);
        if (0.0f == ness_attr->x70_PK_THUNDER_2_LANDING_LAG)
        {
            func_800CC730(fighter_gobj);
            return;
        }
        func_800969D8(fighter_gobj, 1, 0, 1, 1.0f, ness_attr->x70_PK_THUNDER_2_LANDING_LAG, ness_attr->x6C_PK_THUNDER_2_FREEFALL_ANIM_BLEND);
    }
}

// 0x80118DF8 //
// https://decomp.me/scratch/RmY8b //
void ftNess_SpecialAirHi_Anim(HSD_GObj* fighter_gobj) // Ness's aerial PK Thunder 2 Animation callback //
{
    s32 filler[2];
    f32 temp_f1;
    Fighter* fighter_data2;
    Fighter* fighter_data;
    ftNessAttributes* ness_attr;
    f32 phi_f1;

    fighter_data = fighter_gobj->user_data;
    ness_attr = fighter_data->x2D4_specialAttributes;
    fighter_data->x2380 = (s32)(fighter_data->x2380 + 1);
    if ((s32)fighter_data->x2380 == 1)
    {
        fighter_data2 = fighter_gobj->user_data;
        ftNess_SpecialHiStopGFX(fighter_gobj);
        ef_Spawn(0x4EF, fighter_gobj, fighter_data2->x5E8_fighterBones[4].x0_jobj);
        fighter_data2->sa.ness.x224C_thunderGFX = TRUE;
    }
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        temp_f1 = fighter_data->x2384_f32;
        phi_f1 = temp_f1;
        if (temp_f1 < 0.0f)
        {
            phi_f1 = -temp_f1;
        }
        fighter_data->x80_self_vel.y = (f32)-phi_f1;
        func_8007D60C(fighter_data);
        if (0.0f == ness_attr->x70_PK_THUNDER_2_LANDING_LAG)
        {
            func_800CC730(fighter_gobj);
            return;
        }
        func_800969D8(fighter_gobj, 1, 0, 1, 1.0f, ness_attr->x70_PK_THUNDER_2_LANDING_LAG, ness_attr->x6C_PK_THUNDER_2_FREEFALL_ANIM_BLEND);
    }
}

// 0x80118EF0 //
// https://decomp.me/scratch/bDQOo //
void ftNess_SpecialAirHiRebound_Anim(HSD_GObj* fighter_gobj) // Ness's PK Thunder 2 Wall Rebound Animation callback //
{
    s32 filler[2];
    Fighter* fighter_data;
    Fighter* temp_fighter;
    ftNessAttributes* ness_attr;

    fighter_data = temp_fighter = fighter_gobj->user_data;
    ness_attr = temp_fighter->x2D4_specialAttributes;
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_8007D60C(fighter_data);
        if (0.0f == ness_attr->x70_PK_THUNDER_2_LANDING_LAG)
        {
            func_800CC730(fighter_gobj);
            return;
        }
        func_800969D8(fighter_gobj, 1, 0, 1, 1.0f, ness_attr->x70_PK_THUNDER_2_LANDING_LAG, ness_attr->x6C_PK_THUNDER_2_FREEFALL_ANIM_BLEND);
    }
}

// 0x80118F80 //
void ftNess_SpecialHiStart_IASA(HSD_GObj* fighter_gobj) // Ness's PK Thunder IASA callbacks //
{
    return;
}

// 0x80118F84 //
void ftNess_SpecialHiHold_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80118F88 //
void ftNess_SpecialHiEnd_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80118F8C //
void ftNess_SpecialHi_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80118F90 //
void ftNess_SpecialAirHiStart_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80118F94 //
void ftNess_SpecialAirHiHold_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80118F98 //
void ftNess_SpecialAirHiEnd_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80118F9C //
void ftNess_SpecialAirHi_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80118FA0 //
void ftNess_SpecialAirHiRebound_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

inline void ThunderPhysTimer(HSD_GObj* fighter_gobj)
{
    Fighter* temp_fighter;
    s32 thunderPhysTimer;

    temp_fighter = fighter_gobj->user_data;
    thunderPhysTimer = temp_fighter->x234C_stateVar4;
    if (thunderPhysTimer != 0)
    {
        temp_fighter->x234C_stateVar4 = (s32)(thunderPhysTimer - 1);
    }
}

// 0x80118FA4 //
// https://decomp.me/scratch/5RSqi //
void ftNess_SpecialHiStart_Phys(HSD_GObj* fighter_gobj) // Ness's grounded PK Thunder Start Physics callback //
{
    ThunderPhysTimer(fighter_gobj);
    func_80084F3C(fighter_gobj);
}

// 0x80118FDC //
// https://decomp.me/scratch/3o65K //
void ftNess_SpecialHiHold_Phys(HSD_GObj* fighter_gobj) // Ness's grounded PK Thunder Control Loop Physics callback //
{
    func_80084F3C(fighter_gobj);
}

// 0x80118FFC //
// This is identical to 0x80118FDC so there's no link bruh //
void ftNess_SpecialHiEnd_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

// 0x8011901C //
// https://decomp.me/scratch/Xm7Fl //
void ftNess_SpecialHi_Phys(HSD_GObj* fighter_gobj) // Ness's grounded PK Thunder 2 Physics callback //
{
    s32 filler[4];
    f32 temp_f2;
    f32 temp_f3;
    Fighter* fighter_data;
    Fighter* temp_fighter;
    ftNessAttributes* ness_attr;

    temp_fighter = fighter_gobj->user_data;
    temp_f2 = temp_fighter->xEC_ground_vel;
    temp_f3 = temp_fighter->x80_self_vel.y;
    ness_attr = temp_fighter->x2D4_specialAttributes;
    temp_fighter->xEC_ground_vel = (f32)-((ness_attr->x5C_PK_THUNDER_2_DECELERATION_RATE * temp_fighter->x2C_facing_direction) - temp_f2);
    if (1.0f == temp_fighter->x2C_facing_direction)
    {
        if (temp_fighter->xEC_ground_vel <= 9.999999747378752e-05f)
        {
            temp_fighter->xEC_ground_vel = temp_f2;
        }
    }
    else if (temp_fighter->xEC_ground_vel >= -9.999999747378752e-05f)
    {
        temp_fighter->xEC_ground_vel = temp_f2;
    }
    if (1.0f == temp_fighter->x2370_f32)
    {
        if (temp_fighter->x80_self_vel.y <= 9.999999747378752e-05f)
        {
            temp_fighter->x80_self_vel.y = temp_f3;
        }
    }
    else if (temp_fighter->x80_self_vel.y >= -9.999999747378752e-05f)
    {
        temp_fighter->x80_self_vel.y = temp_f3;
    }
    temp_fighter->x2374_Vec3 = temp_fighter->x80_self_vel;
    func_8007CB74(fighter_gobj);
    fighter_data = fighter_gobj->user_data;
    func_8007592C(fighter_data, 0, (fighter_data->x2C_facing_direction * func_someCalcAngle_80022C30(fighter_data->x80_self_vel.x, fighter_data->x80_self_vel.y)) - 1.5707963705062866f);
}

// 0x80119134 //
// https://decomp.me/scratch/s2U1l //
void ftNess_SpecialAirHiStart_Phys(HSD_GObj* fighter_gobj) // Ness's aerial PK Thunder Start Physics callback //
{
    s32 filler[2];
    f32 friction;
    s32 thunderPhysTimer;
    Fighter* fighter_data;
    ftNessAttributes* ness_attr;

    fighter_data = fighter_gobj->user_data;
    thunderPhysTimer = fighter_data->x234C_stateVar4;
    ness_attr = fighter_data->x2D4_specialAttributes;
    if (thunderPhysTimer != 0)
    {
        fighter_data->x234C_stateVar4 = thunderPhysTimer - 1;
        goto block_friction;
    }
    func_8007D494(fighter_data, ness_attr->x50_PK_THUNDER_FALL_ACCEL, fighter_data->x110_attr.x170_TerminalVelocity);

block_friction:
    friction = fighter_data->x110_attr.x180_AerialFriction;
    func_8007CE94(fighter_data, friction);
}

// 0x80119194 //
// https://decomp.me/scratch/nvI07 //
void ftNess_SpecialAirHiHold_Phys(HSD_GObj* fighter_gobj) // Ness's aerial PK Thunder Control Loop Physics callback //
{
    s32 filler[2];
    f32 friction;
    s32 thunderPhysTimer;
    Fighter* fighter_data;
    ftNessAttributes* ness_attr;

    fighter_data = fighter_gobj->user_data;
    thunderPhysTimer = fighter_data->x234C_stateVar4;
    ness_attr = fighter_data->x2D4_specialAttributes;
    if (thunderPhysTimer != 0)
    {
        fighter_data->x234C_stateVar4 = thunderPhysTimer - 1;
        goto block_friction;
    }
    func_8007D494(fighter_data, ness_attr->x50_PK_THUNDER_FALL_ACCEL, fighter_data->x110_attr.x170_TerminalVelocity);
block_friction:
    friction = fighter_data->x110_attr.x180_AerialFriction;
    func_8007CE94(fighter_data, friction);
}

// 0x801191F4 //
// https://decomp.me/scratch/KEcQx //
void ftNess_SpecialAirHiEnd_Phys(HSD_GObj* fighter_gobj) // Ness's aerial PK Thunder End Physics callback //
{
    s32 filler[2];
    f32 friction;
    s32 thunderPhysTimer;
    Fighter* fighter_data;
    ftNessAttributes* ness_attr;

    fighter_data = fighter_gobj->user_data;
    thunderPhysTimer = fighter_data->x234C_stateVar4;
    ness_attr = fighter_data->x2D4_specialAttributes;
    if (thunderPhysTimer != 0)
    {
        fighter_data->x234C_stateVar4 = thunderPhysTimer - 1;
        goto block_friction;
    }
    func_8007D494(fighter_data, ness_attr->x50_PK_THUNDER_FALL_ACCEL, fighter_data->x110_attr.x170_TerminalVelocity);
block_friction:
    friction = fighter_data->x110_attr.x180_AerialFriction;
    func_8007CE94(fighter_data, friction);
}

extern f32 sqrtf__Ff(f32 arg0);

inline f32 _sqrtf2(f32 x)
{
    f64 _half = .5;
    static const f64 _three = 3.0;
    volatile f32 y;
    if (x > 0.0f)
    {

        f64 guess = __frsqrte((f64)x);   // returns an approximation to
        guess = _half * guess * (_three - guess * guess * x);  // now have 12 sig bits
        guess = _half * guess * (_three - guess * guess * x);  // now have 24 sig bits
        guess = _half * guess * (_three - guess * guess * x);  // now have 32 sig bits
        y = (f32)(x * guess);
        return y;
    }
    return x;
}

// 0x80119254 //
// https://decomp.me/scratch/h3nb5 //
void ftNess_SpecialAirHi_Phys(HSD_GObj* fighter_gobj) // Ness's aerial PK Thunder 2 Physics callback //
{
    s32 filler[2];
    f32 temp_sqrt;
    Fighter* fighter_data2; // r31 //
    Fighter* fighter_data; // r30 //
    ftNessAttributes* ness_attr;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1;
    f32 temp_f1_5;
    f32 temp_f1_6;
    f32 temp_f2;
    f32 temp_f2_3;
    f32 phi_f1;
    f32 phi_f31;
    f32 temp_fmuls;
    f32 temp_fmuls2;
    f32 temp_fmuls3;
    f32 temp_fmuls4;
    f32 temp_add;

    fighter_data = fighter_gobj->user_data;
    temp_f2 = fighter_data->x80_self_vel.x;
    temp_f1 = fighter_data->x80_self_vel.y;
    ness_attr = fighter_data->x2D4_specialAttributes;
    temp_fmuls = temp_f2 * temp_f2;
    temp_fmuls2 = temp_f1 * temp_f1;

    temp_sqrt = _sqrtf2(temp_fmuls + temp_fmuls2);
    if (temp_sqrt < 0.0f)
    {
        temp_f1_5 = fighter_data->x80_self_vel.x;
        temp_f0 = fighter_data->x80_self_vel.y;
        temp_fmuls3 = temp_f1_5 * temp_f1_5;
        temp_fmuls4 = temp_f0 * temp_f0;
        temp_add = temp_fmuls3 + temp_fmuls4;
        phi_f1 = -sqrtf__Ff(temp_add);
    }
    else
    {
        temp_f1_6 = fighter_data->x80_self_vel.x;
        temp_f0_2 = fighter_data->x80_self_vel.y;
        temp_fmuls3 = temp_f1_6 * temp_f1_6;
        temp_fmuls4 = temp_f0_2 * temp_f0_2;
        temp_add = temp_fmuls3 + temp_fmuls4;
        phi_f1 = sqrtf__Ff(temp_add);
    }
    temp_f2_3 = phi_f1 - ness_attr->x5C_PK_THUNDER_2_DECELERATION_RATE;
    phi_f31 = temp_f2_3;
    if (temp_f2_3 <= 9.999999747378752e-05f)
    {
        phi_f31 = phi_f1;
    }
    fighter_data->x80_self_vel.x = phi_f31 * cosf(fighter_data->x2368_f32);
    fighter_data->x80_self_vel.y = phi_f31 * sinf(fighter_data->x2368_f32);
    fighter_data2 = fighter_gobj->user_data;
    func_8007592C(fighter_data2, 0, (fighter_data2->x2C_facing_direction * func_someCalcAngle_80022C30(fighter_data2->x80_self_vel.x, fighter_data2->x80_self_vel.y)) - 1.5707963705062866f);
    fighter_data->x2374_Vec3 = fighter_data->x80_self_vel;
    if ((u32)fighter_data->x2200_ftcmd_var0 == 1U)
    {
        fighter_data->x2384_f32 = (f32)fighter_data->x2384_f32 - ness_attr->x50_PK_THUNDER_FALL_ACCEL;
        if ((f32)fighter_data->x2384_f32 < -ness_attr->x54_PK_THUNDER_2_MOMENTUM)
        {
            fighter_data->x2384_f32 = -ness_attr->x54_PK_THUNDER_2_MOMENTUM;
        }
        fighter_data->xB0_pos.y += (f32)fighter_data->x2384_f32;
    }
}

// 0x80119410 //
// https://decomp.me/scratch/HLUCz //
void ftNess_SpecialAirHiRebound_Phys(HSD_GObj* fighter_gobj) // Ness's PK Thunder 2 Wall Rebound Physics callback //
{
    attr* fighter_attr;
    Fighter* fighter_data = fighter_gobj->user_data;

    fighter_attr = &fighter_data->x110_attr;
    fighter_attr == NULL;
    func_8007D494(fighter_data, fighter_data->x110_attr.x16C_Gravity, fighter_data->x110_attr.x170_TerminalVelocity);
    func_8007CE94(fighter_data, fighter_attr->x180_AerialFriction);
}

// 0x80119460 //
// https://decomp.me/scratch/YDYwL //
void ftNess_SpecialHiStart_Coll(HSD_GObj* fighter_gobj) // Ness's grounded PK Thunder Start Collision callback //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    if (func_80082708(fighter_gobj) == FALSE)
    {
        func_8007D60C(fighter_data);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRHI_START, NESS_SPECIALHI_COLL_FLAG, NULL, fighter_data->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

// 0x801194CC //
// https://decomp.me/scratch/oOw2I //
void ftNess_SpecialHiHold_Coll(HSD_GObj* fighter_gobj) // Ness's grounded PK Thunder Control Loop Collision callback //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    if (func_80082708(fighter_gobj) == FALSE)
    {
        func_8007D60C(fighter_data);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRHI_HOLD, NESS_SPECIALHI_COLL_FLAG, NULL, fighter_data->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

// 0x80119538 //
// https://decomp.me/scratch/3bhjz //
void ftNess_SpecialHiEnd_Coll(HSD_GObj* fighter_gobj) // Ness's grounded PK Thunder End Collision callback //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    if (func_80082708(fighter_gobj) == FALSE)
    {
        func_8007D60C(fighter_data);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRHI_END, NESS_SPECIALHI_COLL_FLAG, NULL, fighter_data->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

// 0x801195A4 //
// https://decomp.me/scratch/7ZmrD //
void ftNess_SpecialHi_Coll(HSD_GObj* fighter_gobj) // Ness's grounded PK Thunder 2 Collision callback //
{
    s32 filler[4];
    f32 temp_f1_2;
    s32 ASID;
    s32 ecbFlag;
    s32 ecbFlag2;
    Fighter* fighter_data2;
    Fighter* fighter_data;
    Fighter* temp_fighter;
    ftNessAttributes* temp_attr;
    f64 phi_f31;
    f64 phi_f31_2;

    fighter_data = fighter_gobj->user_data;
    if (func_80082708(fighter_gobj) == FALSE)
    {
        ecbFlag = fighter_data->x6F0_collData.x134_envFlags;
        if (((ecbFlag & 0x3F) != 0) || ((ecbFlag & 0xFC0) != 0))
        {
            func_8007D60C(fighter_data);
            temp_fighter = fighter_gobj->user_data;
            temp_attr = temp_fighter->x2D4_specialAttributes;
            temp_fighter->x2344_stateVar2 = (s32)temp_attr->x40_PK_THUNDER_LOOP1;
            temp_fighter->x2348_stateVar3 = (s32)temp_attr->x44_PK_THUNDER_LOOP2;
            temp_fighter->x234C_stateVar4 = (s32)temp_attr->x48_PK_THUNDER_FALLING_ACCEL_DELAY;
            temp_fighter->x2384_f32 = 0.0f;
            temp_fighter->x237C_f32 = 0.0f;
            temp_fighter->x2378_f32 = 0.0f;
            temp_fighter->x2374_f32 = 0.0f;
            temp_fighter->x238C_f32 = 0.0f;
            temp_fighter->x2388_f32 = 0.0f;
            temp_fighter->cb.x21E4_callback_OnDeath2 = NULL;
            temp_fighter->cb.x21DC_callback_OnTakeDamage = NULL;
            func_8007592C(temp_fighter, 0, 0.0f);
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRHI_END, NESS_SPECIALHI_COLL_FLAG, NULL, fighter_data->x894_currentAnimFrame, 1.0f, 0.0f);
            return;
        }
        func_8007D60C(fighter_data);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRHI, NESS_JIBAKU_COLL_FLAG, NULL, fighter_data->x894_currentAnimFrame, 1.0f, 0.0f);
        return;
    }
    ecbFlag2 = fighter_data->x6F0_collData.x134_envFlags;
    if (((ecbFlag2 & 0x6000) != 0) || ((ecbFlag2 & 0x3F) != 0) || ((ecbFlag2 & 0xFC0) != 0))
    {
        fighter_data->xEC_ground_vel = (f32)0.0f;
        fighter_data2 = fighter_gobj->user_data;
        ASID = fighter_data2->x10_action_state_index;
        switch (ASID)
        {
        case AS_NESS_SPECIALHI_START:
        case AS_NESS_SPECIALHI_HOLD:
        case AS_NESS_SPECIALHI_END:
        case AS_NESS_SPECIALHI:
        case AS_NESS_SPECIALAIRHI_START:
        case AS_NESS_SPECIALAIRHI_HOLD:
        case AS_NESS_SPECIALAIRHI_END:
        case AS_NESS_SPECIALAIRHI:
        case AS_NESS_SPECIALAIRHI_HITWALL:
            efLib_DestroyAll(fighter_gobj);
            fighter_data2->sa.ness.x224C_thunderGFX = FALSE;
        }
        func_8007592C(fighter_data, 0, 0.0f);
        func_80097D40(fighter_gobj);
        return;
    }
    temp_f1_2 = fighter_data->x6F0_collData.x154_groundNormal.y;
    if (fighter_data->x6F0_collData.x154_groundNormal.y > 0.0f)
    {
        if (1.0f == fighter_data->x2C_facing_direction)
        {
            phi_f31 = -1.5707963267948966;
        }
        else
        {
            phi_f31 = 1.5707963267948966;
        }
        fighter_data->x2368_f32 = (f32)(phi_f31 + func_someCalcAngle_80022C30(fighter_data->x6F0_collData.x154_groundNormal.y, fighter_data->x6F0_collData.x154_groundNormal.x));
        return;
    }
    if (1.0f == fighter_data->x2C_facing_direction)
    {
        phi_f31_2 = 1.5707963267948966;
    }
    else
    {
        phi_f31_2 = -1.5707963267948966;
    }
    fighter_data->x2368_f32 = (f32)(phi_f31_2 + func_someCalcAngle_80022C30(fighter_data->x6F0_collData.x154_groundNormal.y, fighter_data->x6F0_collData.x154_groundNormal.x));
}

// 0x80119798 //
// https://decomp.me/scratch/zd3TZ //
void ftNess_SpecialAirHiStart_Coll(HSD_GObj* fighter_gobj) // Ness's aerial PK Thunder Start Collision callback //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        func_8007D7FC(fighter_data);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALHI_START, NESS_SPECIALHI_COLL_FLAG, NULL, fighter_data->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

// 0x80119804 //
// https://decomp.me/scratch/mu2vM //
void ftNess_SpecialAirHiHold_Coll(HSD_GObj* fighter_gobj) // Ness's aerial PK Thunder Control Loop Collision callback //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        func_8007D7FC(fighter_data);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALHI_HOLD, NESS_SPECIALHI_COLL_FLAG, NULL, fighter_data->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

// 0x80119870 //
// https://decomp.me/scratch/ELLSL //
void ftNess_SpecialAirHiEnd_Coll(HSD_GObj* fighter_gobj) // Ness's aerial PK Thunder End Collision callback //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        func_8007D7FC(fighter_data);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALHI_END, NESS_SPECIALHI_COLL_FLAG, NULL, fighter_data->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

extern BOOL EnvColl_CheckGroundAndLedge(HSD_GObj*, s32); // 0x800822A4 //
extern BOOL func_80081298(HSD_GObj*);
extern void func_80081370(HSD_GObj*);

extern void func_8007D440(Fighter*, f32);

void ftNess_SpecialAirHi_Coll(HSD_GObj* fighter_gobj) // Ness's aerial PK Thunder 2 Collision callback //
{
    Fighter* new_var;

    f32 unkFloat;
    Vec3 spC4;
    Vec3 spB8;
    Vec3 spAC;
    s32 topfiller[35];
    s32 ledgeGrabDir;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 fmuls1;
    f32 fmuls2;
    f32 fmuls3;
    f32 fmuls4;
    f32 fmuls5;
    f32 fmuls6;
    f32 temp_f1_2;
    f32 temp_f1_5;
    f32 temp_f1_8;
    f32 temp_f1_9;
    f32 DriftMax;
    s32 ASID;
    s32 ecbFlag;
    ftNessAttributes* ness_attr;
    Fighter* fighter_data2;
    Fighter* fighter_data3;
    Fighter* fighter_data4;
    Fighter* fighter_data5;
    Fighter* fighter_r31;
    f32 phi_f0;
    f32 phi_f0_2;
    f32 phi_f0_3;
    fighter_r31 = fighter_gobj->user_data;
    ness_attr = fighter_r31->x2D4_specialAttributes;
    fighter_r31->x80_self_vel = fighter_r31->x2374_Vec3;

    if (1.0f == fighter_r31->x2C_facing_direction)
    {
        ledgeGrabDir = 1;
    }
    else
    {
        ledgeGrabDir = -1;
    }
    if (EnvColl_CheckGroundAndLedge(fighter_gobj, ledgeGrabDir) != FALSE)
    {
        if (lbvector_Angle(&fighter_r31->x6F0_collData.x154_groundNormal, &fighter_r31->x80_self_vel) > (0.01745329238474369f * (90.0f + ness_attr->x64_PK_THUNDER_2_WALLHUG_ANGLE)))
        {
            fighter_r31->x80_self_vel.z = 0.0f;
            fighter_r31->x80_self_vel.y = 0.0f;
            fighter_r31->x80_self_vel.x = 0.0f;
            fighter_data2 = fighter_gobj->user_data;
            ASID = fighter_data2->x10_action_state_index;
            switch (ASID)
            {
            case AS_NESS_SPECIALHI_START:

            case AS_NESS_SPECIALHI_HOLD:

            case AS_NESS_SPECIALHI_END:

            case AS_NESS_SPECIALHI:

            case AS_NESS_SPECIALAIRHI_START:

            case AS_NESS_SPECIALAIRHI_HOLD:

            case AS_NESS_SPECIALAIRHI_END:

            case AS_NESS_SPECIALAIRHI:

            case AS_NESS_SPECIALAIRHI_HITWALL:
                efLib_DestroyAll(fighter_gobj);
                fighter_data2->sa.ness.x224C_thunderGFX = FALSE;

            }

            func_8007592C(fighter_r31, 0, 0.0f);
            func_80097D40(fighter_gobj);
            return;
        }
        func_8007D7FC(fighter_r31);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALHI, NESS_JIBAKU_COLL_FLAG, NULL, fighter_r31->x894_currentAnimFrame, 1.0f, 0.0f);
        return;
    }
    if (func_80081298(fighter_gobj) != 0)
    {
        func_80081370(fighter_gobj);
        return;
    }

    ecbFlag = fighter_r31->x6F0_collData.x134_envFlags;
    if ((ecbFlag & 0x6000) != 0)
    {
        if (lbvector_Angle(&fighter_r31->x6F0_collData.x190_vec, &fighter_r31->x80_self_vel) > (0.01745329238474369f * (90.0f + ness_attr->x64_PK_THUNDER_2_WALLHUG_ANGLE)))
        {
            fighter_data3 = fighter_gobj->user_data;
            lbvector_Mirror(&fighter_data3->x80_self_vel, &fighter_r31->x6F0_collData.x190_vec);
            (new_var = fighter_data3)->x80_self_vel.x *= 0.5f;
            new_var->x80_self_vel.y *= 0.5f;
            temp_f1_2 = new_var->x80_self_vel.x;
            temp_f0_2 = new_var->x80_self_vel.y;
            fmuls1 = temp_f1_2 * temp_f1_2;
            fmuls2 = temp_f0_2 * temp_f0_2;
            lbvector_sqrtf_accurate(fmuls1 + fmuls2);
            DriftMax = new_var->x110_attr.x17C_AerialDriftMax;
            DriftMax == 0.0f;
            func_8007D440(new_var, new_var->x110_attr.x17C_AerialDriftMax);
            if (new_var->x80_self_vel.x >= 0.0f)
            {
                phi_f0 = 1.0f;
            }
            else
            {
                phi_f0 = -1.0f;
            }
            new_var->x2C_facing_direction = phi_f0;
            ftNess_SpecialHiStopGFX(fighter_gobj);
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRHI_HITWALL, FIGHTER_GFX_PRESERVE, NULL, 0.0f, 1.0f, 0.0f);
            func_8006EBA4(fighter_gobj);
            spC4.x = func_someCalcAngle_80022C30(-fighter_r31->x6F0_collData.x190_vec.x, fighter_r31->x6F0_collData.x190_vec.y);
            ef_Spawn(0x406, fighter_gobj, &new_var->xB0_pos, &spC4);
        }

    }
    else
    {
        if ((ecbFlag & 0x3F) != 0)
        {
            if (lbvector_Angle(&fighter_r31->x6F0_collData.x168_vec, &fighter_r31->x80_self_vel) > (0.01745329238474369f * (90.0f + ness_attr->x64_PK_THUNDER_2_WALLHUG_ANGLE)))
            {
                fighter_data4 = fighter_gobj->user_data;
                lbvector_Mirror(&fighter_data4->x80_self_vel, &fighter_r31->x6F0_collData.x168_vec);
                (new_var = fighter_data4)->x80_self_vel.x *= 0.5f;
                new_var->x80_self_vel.y *= 0.5f;
                temp_f1_5 = new_var->x80_self_vel.x;
                temp_f0_3 = new_var->x80_self_vel.y;
                fmuls3 = temp_f1_5 * temp_f1_5;
                fmuls4 = temp_f0_3 * temp_f0_3;
                lbvector_sqrtf_accurate(fmuls3 + fmuls4);
                DriftMax = new_var->x110_attr.x17C_AerialDriftMax;
                DriftMax == 0.0f;
                func_8007D440(new_var, new_var->x110_attr.x17C_AerialDriftMax);
                if (fighter_data4->x80_self_vel.x >= 0.0f)
                {
                    phi_f0 = 1.0f;
                }
                else
                {
                    phi_f0 = -1.0f;
                }
                fighter_data4->x2C_facing_direction = phi_f0;
                ftNess_SpecialHiStopGFX(fighter_gobj);
                Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRHI_HITWALL, FIGHTER_GFX_PRESERVE, NULL, 0.0f, 1.0f, 0.0f);
                func_8006EBA4(fighter_gobj);
                spB8.x = func_someCalcAngle_80022C30(-fighter_r31->x6F0_collData.x168_vec.x, fighter_r31->x6F0_collData.x168_vec.y);
                ef_Spawn(0x406, fighter_gobj, &fighter_data4->xB0_pos, &spB8);
                return;
            }
            ftNess_SpecialAirHi_CollisionModVel(fighter_gobj, &fighter_r31->x6F0_collData);
            return;
        }
        if ((ecbFlag & 0xFC0) != 0)
        {
            if (lbvector_Angle(&fighter_r31->x6F0_collData.x17C_vec, &fighter_r31->x80_self_vel) > (0.01745329238474369f * (90.0f + ness_attr->x64_PK_THUNDER_2_WALLHUG_ANGLE)))
            {
                fighter_data5 = fighter_gobj->user_data;
                lbvector_Mirror(&fighter_data5->x80_self_vel, &fighter_r31->x6F0_collData.x17C_vec);
                (new_var = fighter_data5)->x80_self_vel.x *= 0.5f;
                new_var->x80_self_vel.y *= 0.5f;
                temp_f1_8 = new_var->x80_self_vel.x;
                temp_f0_4 = new_var->x80_self_vel.y;
                fmuls5 = temp_f1_8 * temp_f1_8;
                fmuls6 = temp_f0_4 * temp_f0_4;
                lbvector_sqrtf_accurate(fmuls5 + fmuls6);
                DriftMax = new_var->x110_attr.x17C_AerialDriftMax;
                DriftMax == 0.0f;
                func_8007D440(new_var, new_var->x110_attr.x17C_AerialDriftMax);
                if (fighter_data5->x80_self_vel.x >= 0.0f)
                {
                    phi_f0 = 1.0f;
                }
                else
                {
                    phi_f0 = -1.0f;
                }
                fighter_data5->x2C_facing_direction = phi_f0;
                ftNess_SpecialHiStopGFX(fighter_gobj);
                Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRHI_HITWALL, FIGHTER_GFX_PRESERVE, NULL, 0.0f, 1.0f, 0.0f);
                func_8006EBA4(fighter_gobj);
                spAC.x = func_someCalcAngle_80022C30(-fighter_r31->x6F0_collData.x17C_vec.x, fighter_r31->x6F0_collData.x17C_vec.y);
                ef_Spawn(0x406, fighter_gobj, &fighter_data5->xB0_pos, &spAC);
                return;
            }
            ftNess_SpecialAirHi_CollisionModVel(fighter_gobj, &fighter_r31->x6F0_collData);
        }
    }
}


// 0x80119D58 //
// https://decomp.me/scratch/pEPo1 //
void ftNess_SpecialAirHiRebound_Coll(HSD_GObj* fighter_gobj) // Ness's PK Thunder 2 Wall Rebound Collision callback //
{
    s32 filler[2];
    Fighter* fighter_data;
    Fighter* fighter_data2;
    s32 ASID;

    fighter_data = fighter_gobj->user_data;
    if (EnvColl_CheckGroundAndLedge(fighter_gobj, 0) == TRUE)
    {
        fighter_data->x80_self_vel.z = 0.0f;
        fighter_data->x80_self_vel.y = 0.0f;
        fighter_data->x80_self_vel.x = 0.0f;
        fighter_data2 = fighter_gobj->user_data;
        ASID = fighter_data2->x10_action_state_index;
        switch (ASID)
        {
        case AS_NESS_SPECIALHI_START:
        case AS_NESS_SPECIALHI_HOLD:
        case AS_NESS_SPECIALHI_END:
        case AS_NESS_SPECIALHI:
        case AS_NESS_SPECIALAIRHI_START:
        case AS_NESS_SPECIALAIRHI_HOLD:
        case AS_NESS_SPECIALAIRHI_END:
        case AS_NESS_SPECIALAIRHI:
        case AS_NESS_SPECIALAIRHI_HITWALL:
            efLib_DestroyAll(fighter_gobj);
            fighter_data2->sa.ness.x224C_thunderGFX = FALSE;

        }
        func_8007592C(fighter_data, 0, 0.0f);
        func_80097D40(fighter_gobj);
        return;
    }
    if (func_80081298(fighter_gobj) != FALSE)
    {
        func_80081370(fighter_gobj);
    }
}


