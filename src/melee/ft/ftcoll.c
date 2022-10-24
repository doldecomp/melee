#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/fighter.h>
#include <melee/it/item.h>

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

void func_80076444(HSD_GObj* attacker, HSD_GObj* victim) // Combo Count Logic + Get Attack ID //
{
    Fighter* fp = getFighter(attacker);
    func_800763C0(attacker, victim, fp->x2068_attackID);
}

extern BOOL func_80086960(HSD_GObj*);

void func_8007646C(HSD_GObj* attackItem, HSD_GObj* victim) // Combo Count Logic w/ Item Owner //
{
    HSD_GObj* itemOwner = func_8026BC78(attackItem);
    s32 attackID = func_8026BC84(attackItem);

    if (func_80086960(itemOwner) != FALSE) // Check if item's owner is a fp //
    {
        func_800763C0(itemOwner, victim, attackID);
    }
}