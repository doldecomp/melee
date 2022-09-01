#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>

#include <functions.h>
#include <melee/pl/player.h>
#include <melee/gr/stage.h>
#include <math.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/archive.h>
#include <common_structs.h>
#include <melee/ft/fighter.h>
#include <melee/it/item.h>

// 0x800763C0 //
// https://decomp.me/scratch/zSqbD //
void func_800763C0(HSD_GObj* attacker, HSD_GObj* victim, s32 attackID) // Combo Count Logic //
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

// 0x80076444 //
// https://decomp.me/scratch/PJyPr //
void func_80076444(HSD_GObj* attacker, HSD_GObj* victim) // Combo Count Logic + Get Attack ID //
{
    Fighter* fp = getFighter(attacker);
    func_800763C0(attacker, victim, fp->x2068_attackID);
}

extern BOOL func_80086960(HSD_GObj*);

// 0x8007646C //
// https://decomp.me/scratch/TDdx4 //
void func_8007646C(HSD_GObj* attackItem, HSD_GObj* victim) // Combo Count Logic w/ Item Owner //
{
    HSD_GObj* itemOwner = func_8026BC78(attackItem);
    s32 attackID = func_8026BC84(attackItem);

    if (func_80086960(itemOwner) != FALSE) // Check if item's owner is a fp //
    {
        func_800763C0(itemOwner, victim, attackID);
    }
}

// 0x800764DC //
// https://decomp.me/scratch/pOUFp //
void func_800764DC(HSD_GObj* fighter_gobj) // Check to end combo for victim //
{
    u16 hitstunTimer; // Hitstun timer, presumably? //
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

// 0x80076528 //
// https://decomp.me/scratch/qGiYU //
void func_80076528(HSD_GObj* fighter_gobj) // Combo count something + adjust TopN //
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

// 0x800765AC //
// https://decomp.me/scratch/IPBrx //
void func_800765AC(HSD_GObj* victim) // Clear victim pointer from attacker upon freeing memory? //
{
    Fighter* fp;
    HSD_GObj* gobj;

    gobj = lbl_804D782C->x20_fighterGObj; // Get fp GObj from global list of entities (?) //
    while (gobj != NULL)
    {
        fp = getFighter(gobj); 
        if (victim == fp->x2094)
        {
            fp->x2094 = NULL;
        }
        gobj = gobj->next; // Repeat until there are no more fp GObjs left //
    }
}

extern s32 lbl_804D6558;
extern s32 lbl_804D655C;

// 0x800765E0 //
// https://decomp.me/scratch/F1xnr
void func_800765E0(void) // Reset hitbox and phantom collision count? //
{
    lbl_804D6558 = 0;
    lbl_804D655C = 0;
}

// 0x800765F0 //
// https://decomp.me/scratch/9hcKb //
f32 func_800765F0(Fighter* fp, HSD_GObj* victim, f32 unk_floatvar) // Unk knockback related ? //
{
    HSD_GObj* currentVictim;

    currentVictim = fp->x1A58_interactedFighter;
    if ((currentVictim != NULL) && (fp->x221B_flag.bits.b5 == 0) && (currentVictim != victim))
    {
        unk_floatvar *= p_ftCommonData->x128;
    }
    if (fp->x10_action_state_index == ASID_DAMAGEICE)
    {
        unk_floatvar *= p_ftCommonData->x714;
    }
    return unk_floatvar * fp->dmg.x182c_behavior;
}
