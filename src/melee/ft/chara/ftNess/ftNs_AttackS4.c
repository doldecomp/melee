#include <platform.h>

#include "ftNess/ftNs_AttackS4.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Wait.h"
#include "ftNess/ftNs_Init.h"
#include "ftNess/types.h"
#include "it/items/itnessbat.h"

// 0x80114BF4
void ftNs_AttackS4_OnReflect(
    HSD_GObj* gobj) // Ness's F-Smash OnReflect callback
{
    ft_80088148(GET_FIGHTER(gobj), 0xE0U, 0x7FU, 0x40U);
};

// 0x80114C24
// https://decomp.me/scratch/66eaB
void ftNs_AttackS4_Enter(HSD_GObj* gobj) // Ness's F-Smash Motion State handler
{
    Fighter* fp;
    HSD_GObj* baseballBatGObj;

    u8 _[8];

    fp = GET_FIGHTER(gobj);

    fp->allow_interrupt = 0;

    fp->cmd_vars[0] = false;

    Fighter_ChangeMotionState(gobj, ftNs_MS_AttackS4, 0, 0.0f, 1.0f, 0.0f,
                              NULL);

    ftAnim_8006EBA4(gobj);

    baseballBatGObj = it_802AD478(gobj, &fp->cur_pos,
                                  0x2A /* Item Hold Bone */, fp->facing_dir);

    fp->fv.ns.bat_gobj = baseballBatGObj;

    if (baseballBatGObj != NULL) {
        fp->death2_cb = ftNs_Init_OnDamage;
        fp->take_dmg_cb = ftNs_Init_OnDamage;
    }
};

// 0x80114CC0
// https://decomp.me/scratch/E8Nsh
bool ftNs_AttackS4_CheckNessBatRemove(
    HSD_GObj* gobj) // Check if Ness is in F-Smash + has Baseball Bat item
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->motion_id != ftNs_MS_AttackS4) {
        return true;
    }

    if (fp->fv.ns.bat_gobj == NULL) {
        return true;
    }

    return false;
};

// 0x80114CF4
// https://decomp.me/scratch/mpl3X
void ftNs_AttackS4_ItemNessBatRemove(HSD_GObj* gobj) // Remove Baseball Bat
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.ns.bat_gobj != NULL) {
        it_802AD6B8(fp->fv.ns.bat_gobj);
        fp->fv.ns.bat_gobj = NULL;
    }
};

// 0x80114D34
// https://decomp.me/scratch/6ulYB
void ftNs_AttackS4_ItemNessBatSetNULL(
    HSD_GObj* gobj) // Clear Baseball Bat GObj pointer
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.ns.bat_gobj != NULL) {
        fp->fv.ns.bat_gobj = NULL;
    }
};

// 0x80114D50
// https://decomp.me/scratch/M8dFk
void ftNs_AttackS4_Anim(HSD_GObj* gobj) // Ness's F-Smash Animation callback
{
    Fighter* fighter_data1 = GET_FIGHTER(gobj);
    ftNessAttributes* ness_attr;

    if (fighter_data1->x2218_b3 == 0) {
        if (fighter_data1->cmd_vars[0] !=
            false) // Check if reflect bubble flag is enabled in fp script
        {
            ness_attr = fighter_data1->dat_attrs;
            ftColl_CreateReflectHit(
                gobj, &ness_attr->xB8_BASEBALL_BAT,
                ftNs_AttackS4_OnReflect); // Create reflect bubble
        }
    }

    else if (fighter_data1->cmd_vars[0] == false)
    {
        fighter_data1->x2218_b3 = 0; // Toggle reflect bubble OFF//
    }

    if (!ftAnim_IsFramesRemaining(
            gobj)) // Check if animation has frames remaining
    {
        Fighter* fighter_data2;
        fighter_data2 = GET_FIGHTER(gobj);
        if (fighter_data2->fv.ns.bat_gobj != NULL) {
            it_802AD6B8(
                fighter_data2->fv.ns.bat_gobj); // Despawn the Baseball Bat if
                                                // animation is over
            fighter_data2->fv.ns.bat_gobj = NULL;
        }
        ft_8008A2BC(gobj);
    }
}

// 0x80114E04
// https://decomp.me/scratch/HTgCI
void ftNs_AttackS4_IASA(HSD_GObj* gobj) // Ness's F-Smash IASA Callback
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    if (fp->allow_interrupt != 0) {
        if (fp->fv.ns.bat_gobj != NULL) {
            it_802AD6B8(fp->fv.ns.bat_gobj);
            fp->fv.ns.bat_gobj = NULL;
        }
        ftCo_Wait_IASA(gobj);
    }
};

// 0x80114E64
// https://decomp.me/scratch/wQc4r
void ftNs_AttackS4_Phys(HSD_GObj* gobj) // Ness's F-Smash Physics Callback

{
    ft_80084FA8(gobj);
    ftColl_8007AEF8(gobj);
};

// 0x80114E98
// https://decomp.me/scratch/nJ4hj
void ftNs_AttackS4_Coll(HSD_GObj* gobj) // Ness's F-Smash Collision Callback
{
    ft_80084104(gobj);
};
