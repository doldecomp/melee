#include <Runtime/platform.h>

#include <melee/ft/fighter.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/inlines.h>
#include <melee/ft/types.h>
#include <melee/it/it_26B1.h>
#include <sysdolphin/baselib/gobj.h>

/// Combo Count Logic
void ftColl_800763C0(Fighter_GObj* attacker, Fighter_GObj* victim,
                     enum_t attack_id)
{
    if (attacker != victim) {
        Fighter* fp = GET_FIGHTER(attacker);
        Fighter_GObj* fp_x2094 = fp->x2094;
        if (fp_x2094 == NULL) {
            fp->x208C = attack_id;
            fp->x2090 = 1;
            fp->x2094 = victim;
        } else if (fp_x2094 == victim) {
            if (attack_id != 1 && fp->x208C == attack_id) {
                ++fp->x2090;
                if (fp->x2090 >= p_ftCommonData->x4C4) {
                    fp->x2092 = p_ftCommonData->x4D8;
                }
            } else {
                fp->x2090 = 0;
                fp->x208C = attack_id;
            }
        }
    }
}

/// Combo Count Logic + Get Attack ID
void ftColl_80076444(Fighter_GObj* attacker, Fighter_GObj* victim)
{
    Fighter* fp = GET_FIGHTER(attacker);
    ftColl_800763C0(attacker, victim, fp->x2068_attackID);
}

/// Combo Count Logic w/ Item Owner
void ftColl_8007646C(Item_GObj* attackItem, Fighter_GObj* victim)
{
    Fighter_GObj* owner = itGetOwner(attackItem);
    enum_t msid = itGetAttackId(attackItem);

    if (ftLib_80086960(owner)) {
        ftColl_800763C0(owner, victim, msid);
    }
}

/// Check to end combo for victim
void ftColl_800764DC(Fighter_GObj* gobj)
{
    /// @todo #GET_FIGHTER adds an instruction
    Fighter* fp = gobj->user_data;
    if (fp->x2098 != 0) {
        fp->x2098--;
    }
    if (fp->x2094 != NULL) {
        Fighter* fp1 = fp->x2094->user_data;
        if (!fp1->x221C_b6 && fp1->x2098 == 0) {
            fp->x2094 = NULL;
        }
    }
}

static inline void comboCount_Push(Fighter* fp)
{
    Vec3* pos = &fp->coll_data.floor.normal;
    float temp_f2;
    float var_f2;
    if ((int) fp->x2090 < p_ftCommonData->x4C8) {
        var_f2 = p_ftCommonData->x4D0;
    } else {
        var_f2 = p_ftCommonData->x4D4;
    }
    temp_f2 = fp->facing_dir * var_f2;
    fp->cur_pos.x = -(pos->y * temp_f2 - fp->cur_pos.x);
    fp->cur_pos.y = -(-pos->x * temp_f2 - fp->cur_pos.y);
}

/// Combo count something + adjust FtPart_TopN
void ftColl_80076528(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u16 fp_x2092 = fp->x2092;
    if (fp_x2092 != 0) {
        fp->x2092 = (u16) (fp_x2092 - 1);
        if (fp->victim_gobj == NULL && fp->ground_or_air == GA_Ground) {
            comboCount_Push(fp);
        }
    }
}

/// Clear victim pointer from attacker upon freeing memory?
void ftColl_800765AC(Fighter_GObj* victim)
{
    Fighter_GObj* cur = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER];
    while (cur != NULL) {
        Fighter* fp = GET_FIGHTER(cur);
        if (victim == fp->x2094) {
            fp->x2094 = NULL;
        }
        cur = cur->next;
    }
}
