#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/fighter.h>
#include <melee/it/item.h>
 
// Combo Count Logic
void func_800763C0(HSD_GObj* attacker, HSD_GObj* victim, s32 attackID)
{
    HSD_GObj* temp_GObj;
    Fighter* fp;

    if (attacker != victim)
    {
        fp = getFighter(attacker);
        temp_GObj = fp->x2094;
        if (temp_GObj == NULL)
        {
            fp->x208C = attackID;
            fp->x2090 = 1U;
            fp->x2094 = victim;
            return;
        }
        if (temp_GObj == victim)
        {
            if ((attackID != 1) && ((s32)fp->x208C == attackID))
            {
                fp->x2090 = (u16)(fp->x2090 + 1);
                if (fp->x2090 >= p_ftCommonData->x4C4)
                {
                    fp->x2092 = p_ftCommonData->x4D8;
                }
            }
            else
            {
                fp->x2090 = 0U;
                fp->x208C = attackID;
            }
        }
    }
}

// Combo Count Logic + Get Attack ID
void func_80076444(HSD_GObj* attacker, HSD_GObj* victim)
{
    Fighter* fp = getFighter(attacker);
    func_800763C0(attacker, victim, fp->x2068_attackID);
}

extern BOOL func_80086960(HSD_GObj*);

// Combo Count Logic w/ Item Owner
void func_8007646C(HSD_GObj* attackItem, HSD_GObj* victim)
{
    HSD_GObj* itemOwner = func_8026BC78(attackItem);
    s32 attackID = func_8026BC84(attackItem);
 
    // Check if item's owner is a fp
    if (func_80086960(itemOwner) != FALSE)
    {
        func_800763C0(itemOwner, victim, attackID);
    }
}

// Check to end combo for victim
void func_800764DC(HSD_GObj* fighter_gobj)
{
    u16 hitstunTimer;
    HSD_GObj* temp_gobj;
    Fighter* temp_fp;
    Fighter* fp;

    fp = getFighter(fighter_gobj);
    hitstunTimer = fp->x2098;
    if (hitstunTimer != 0)
    {
        fp->x2098 = (u16)(hitstunTimer - 1);
    }
    temp_gobj = fp->x2094;
    if (temp_gobj != NULL)
    {
        temp_fp = getFighter(temp_gobj);
        if ((temp_fp->x221C_flag.bits.b6 == 0) && ((u16)temp_fp->x2098 == 0))
        {
            fp->x2094 = NULL;
        }
    }
}

inline void comboCount_Push(Fighter* fp)
{

    Vec3* pos = &fp->x6F0_collData.x14C_ground.normal;
    f32 temp_f2;
    f32 var_f2;
    if ((s32)fp->x2090 < (s32)p_ftCommonData->x4C8)
    {
        var_f2 = p_ftCommonData->x4D0;
    }
    else
    {
        var_f2 = p_ftCommonData->x4D4;
    }
    temp_f2 = fp->x2C_facing_direction * var_f2;
    fp->xB0_pos.x = -((pos->y * temp_f2) - fp->xB0_pos.x);
    fp->xB0_pos.y = -((-pos->x * temp_f2) - fp->xB0_pos.y);
}

// Combo count something + adjust TopN
void func_80076528(HSD_GObj* fighter_gobj)
{
    u16 temp_r3;
    Fighter* fp;

    fp = fighter_gobj->user_data;
    temp_r3 = fp->x2092;
    if (temp_r3 != 0)
    {
        fp->x2092 = (u16)(temp_r3 - 1);
        if ((fp->x1A58_interactedFighter == NULL) && (fp->xE0_ground_or_air == GA_Ground))
        {
            comboCount_Push(fp);
        }
    }
}