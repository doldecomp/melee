#include "ftNess/ftNess_AttackS4.h"

#include "ft/code_80081B38.h"
#include "ft/ftcoll.h"
#include "ft/ftunk_04.h"
#include "ft/inlines.h"
#include "ftNess/ftNess.h"
#include "it/code_8027CF30.h"

// 0x80114BF4
void ftNess_AttackS4_OnReflect(
    HSD_GObj* gobj) // Ness's F-Smash OnReflect callback
{
    func_80088148(GET_FIGHTER(gobj), 0xE0U, 0x7FU, 0x40U);
};

// 0x80114C24
// https://decomp.me/scratch/66eaB
void ftNess_AttackS4_Action(
    HSD_GObj* gobj) // Ness's F-Smash Motion State handler
{
    Fighter* fp;
    HSD_GObj* baseballBatGObj;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp = GET_FIGHTER(gobj);

    fp->x2218_flag.bits.b0 = 0;

    fp->x2200_ftcmd_var0 = false;

    Fighter_ChangeMotionState(gobj, MS_NESS_ATTACKS4, 0, NULL, 0.0f, 1.0f,
                              0.0f);

    ftAnim_8006EBA4(gobj);

    baseballBatGObj = func_802AD478(gobj, &fp->cur_pos,
                                    0x2A /* Item Hold Bone */, fp->facing_dir);

    fp->fv.ns.bat_gobj = baseballBatGObj;

    if (baseballBatGObj != NULL) {
        fp->cb.x21E4_callback_OnDeath2 = ftNess_OnDamage;
        fp->cb.x21DC_callback_OnTakeDamage = ftNess_OnDamage;
    }
};

// 0x80114CC0
// https://decomp.me/scratch/E8Nsh
bool ftNess_CheckNessBatRemove(
    HSD_GObj* gobj) // Check if Ness is in F-Smash + has Baseball Bat item
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->motion_id != MS_NESS_ATTACKS4) {
        return true;
    }

    if (fp->fv.ns.bat_gobj == NULL) {
        return true;
    }

    return false;
};

// 0x80114CF4
// https://decomp.me/scratch/mpl3X
void ftNess_ItemNessBatRemove(HSD_GObj* gobj) // Remove Baseball Bat
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.ns.bat_gobj != NULL) {
        func_802AD6B8(fp->fv.ns.bat_gobj);
        fp->fv.ns.bat_gobj = NULL;
    }
};

// 0x80114D34
// https://decomp.me/scratch/6ulYB
void ftNess_ItemNessBatSetNULL(
    HSD_GObj* gobj) // Clear Baseball Bat GObj pointer
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.ns.bat_gobj != NULL) {
        fp->fv.ns.bat_gobj = NULL;
    }
};

// 0x80114D50
// https://decomp.me/scratch/M8dFk
void ftNess_AttackS4_Anim(HSD_GObj* gobj) // Ness's F-Smash Animation callback
{
    Fighter* fighter_data1 = GET_FIGHTER(gobj);
    ftNessAttributes* ness_attr;

    if (fighter_data1->x2218_flag.bits.b3 == 0) {
        if (fighter_data1->x2200_ftcmd_var0 !=
            false) // Check if reflect bubble flag is enabled in fp script
        {
            ness_attr = fighter_data1->x2D4_specialAttributes;
            ftColl_CreateReflectHit(
                gobj, &ness_attr->xB8_BASEBALL_BAT,
                ftNess_AttackS4_OnReflect); // Create reflect bubble
        }
    }

    else if (fighter_data1->x2200_ftcmd_var0 == false)
    {
        fighter_data1->x2218_flag.bits.b3 = 0; // Toggle reflect bubble OFF//
    }

    if (!ftAnim_IsFramesRemaining(
            gobj)) // Check if animation has frames remaining
    {
        Fighter* fighter_data2;
        fighter_data2 = GET_FIGHTER(gobj);
        if (fighter_data2->fv.ns.bat_gobj != NULL) {
            func_802AD6B8(
                fighter_data2->fv.ns.bat_gobj); // Despawn the Baseball Bat if
                                                // animation is over
            fighter_data2->fv.ns.bat_gobj = NULL;
        }
        func_8008A2BC(gobj);
    }
}

// 0x80114E04
// https://decomp.me/scratch/HTgCI
void ftNess_AttackS4_IASA(HSD_GObj* gobj) // Ness's F-Smash IASA Callback
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->x2218_flag.bits.b0 != 0) {
        if (fp->fv.ns.bat_gobj != NULL) {
            func_802AD6B8(fp->fv.ns.bat_gobj);
            fp->fv.ns.bat_gobj = NULL;
        }
        func_8008A4D4(gobj);
    }
};

// 0x80114E64
// https://decomp.me/scratch/wQc4r
void ftNess_AttackS4_Phys(HSD_GObj* gobj) // Ness's F-Smash Physics Callback

{
    func_80084FA8(gobj);
    ftColl_8007AEF8(gobj);
};

// 0x80114E98
// https://decomp.me/scratch/nJ4hj
void ftNess_AttackS4_Coll(HSD_GObj* gobj) // Ness's F-Smash Collision Callback
{
    func_80084104(gobj);
};
