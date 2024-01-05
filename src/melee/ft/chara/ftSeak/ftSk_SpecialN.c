#include "ftSeak/ftSk_Init.h"
#include "ftSeak/ftSk_SpecialN.h"

#include <placeholder.h>
#include "ft/fighter.h"
#include "ft/inlines.h"
#include "ft/ft_0877.h"
#include "ft/ftcolanim.h"

// HSD_GObj* it_802AFD8C(HSD_GObj*, Vec3*, u32, f32);             /* extern */

// f32 ftSk_SpecialN_803CC598[] = {
//     -1, -0.75, -0.5, -0.25, 0, +0.25, +0.5, +0.75, +1,
// };

// /* static */ void ftSk_SpecialN_80112418(void);
// /* static */ void ftSk_SpecialN_80112418(void);
// /* static */ void ftSk_SpecialN_80112408(void);
// /* static */ void ftSk_SpecialN_80112418(void);
// /* static */ void ftSk_SpecialN_80112418(void);
// /* static */ void ftSk_SpecialN_80112408(void);
// /* static */ void ftSk_SpecialN_80112418(void);
// /* static */ void ftSk_SpecialN_80112418(void);
// /* static */ void ftSk_SpecialN_80112408(void);
// /* static */ void ftSk_SpecialN_80112418(void);
// /* static */ void ftSk_SpecialN_80112418(void);
// /* static */ void ftSk_SpecialN_80112408(void);
// /* static */ void ftSk_SpecialN_80112418(void);
// /* static */ void ftSk_SpecialN_80112418(void);
// /* static */ void ftSk_SpecialN_80112408(void);
// /* static */ void ftSk_SpecialN_80112418(void);

// /* static */ void ftSk_SpecialN_80112418(void);
// /* static */ void ftSk_SpecialN_80112408(void);

// jtbl_t ftSk_SpecialN_803CC5BC = {
//     ftSk_SpecialN_80112418, ftSk_SpecialN_80112418, ftSk_SpecialN_80112408,
//     ftSk_SpecialN_80112418, ftSk_SpecialN_80112418, ftSk_SpecialN_80112408,
//     ftSk_SpecialN_80112418, ftSk_SpecialN_80112418, ftSk_SpecialN_80112408,
//     ftSk_SpecialN_80112418, ftSk_SpecialN_80112418, ftSk_SpecialN_80112408,
//     ftSk_SpecialN_80112418, ftSk_SpecialN_80112418, ftSk_SpecialN_80112408,
//     ftSk_SpecialN_80112418, ftSk_SpecialN_80112418, ftSk_SpecialN_80112408,
// };

// /* static */ void ftSk_SpecialN_80112660(void);
// /* static */ void ftSk_SpecialN_80112660(void);
// /* static */ void ftSk_SpecialN_80112650(void);
// /* static */ void ftSk_SpecialN_80112660(void);
// /* static */ void ftSk_SpecialN_80112660(void);
// /* static */ void ftSk_SpecialN_80112650(void);
// /* static */ void ftSk_SpecialN_80112660(void);
// /* static */ void ftSk_SpecialN_80112660(void);
// /* static */ void ftSk_SpecialN_80112650(void);
// /* static */ void ftSk_SpecialN_80112660(void);
// /* static */ void ftSk_SpecialN_80112660(void);
// /* static */ void ftSk_SpecialN_80112650(void);
// /* static */ void ftSk_SpecialN_80112660(void);
// /* static */ void ftSk_SpecialN_80112660(void);
// /* static */ void ftSk_SpecialN_80112650(void);
// /* static */ void ftSk_SpecialN_80112660(void);
// /* static */ void ftSk_SpecialN_80112660(void);
// /* static */ void ftSk_SpecialN_80112650(void);

// jtbl_t ftSk_SpecialN_803CC604 = {
//     ftSk_SpecialN_80112660, ftSk_SpecialN_80112660, ftSk_SpecialN_80112650,
//     ftSk_SpecialN_80112660, ftSk_SpecialN_80112660, ftSk_SpecialN_80112650,
//     ftSk_SpecialN_80112660, ftSk_SpecialN_80112660, ftSk_SpecialN_80112650,
//     ftSk_SpecialN_80112660, ftSk_SpecialN_80112660, ftSk_SpecialN_80112650,
//     ftSk_SpecialN_80112660, ftSk_SpecialN_80112660, ftSk_SpecialN_80112650,
//     ftSk_SpecialN_80112660, ftSk_SpecialN_80112660, ftSk_SpecialN_80112650,
// };

// f32 const ftSk_Init_804D9650 = 0;
// f32 const ftSk_Init_804D9654 = 1;
// f32 const ftSk_Init_804D9658 = 2;


// Sheik_CheckAndDestroyNeedles
// 80111FBC - 801120D4 (0x118 bytes)
// https://decomp.me/scratch/rKi8R (initial work; old context)
// https://decomp.me/scratch/5rjkN
void ftSk_SpecialN_80111FBC(Fighter_GObj* fighter_gobj)
{
    Fighter* fp; // r31
    Fighter_GObj* fighter_gobj2;
    ftSeakAttributes* specialAttributes; // r29
    Vec3 sp14;
    f32 temp_f31;
    f32 var_f2;

    fp = GET_FIGHTER(fighter_gobj);
    specialAttributes = fp->dat_attrs;
    
    if ((u32) fp->fv.sk.x2230 != 0U) {
        fp->fv.sk.x2230 = 0U;
        //temp_f31 = ftSk_SpecialN_803CC598[4];
        temp_f31 = 0;
        
        while (fp->fv.sk.x222C != 0) {
            sp14 = fp->cur_pos;
            
            if (fp->ground_or_air == 0) {
                var_f2 = specialAttributes->x4;
            } else {
                var_f2 = specialAttributes->xC;
            }
            sp14.y += fp->x34_scale.y * var_f2;
            sp14.z = temp_f31;
            
            fighter_gobj2 = it_802AFD8C(fighter_gobj, &sp14, 0x4F, fp->facing_dir);
            if (fighter_gobj2 != 0U) {
                it_802AFEA8(fighter_gobj2, fighter_gobj, 1);
            }
            fp->fv.sk.x222C -= 1;
        }
        if ((fp->death2_cb == ftSk_Init_80110198) || (fp->take_dmg_cb == ftSk_Init_80110198)) {
            ftSk_SpecialN_801120D4(fighter_gobj);
        }
    }
    fp->fv.sk.x222C = 0;
}


// 801120D4 - 801120E8 (0x14 bytes)
// https://decomp.me/scratch/IJZbn
void ftSk_SpecialN_801120D4(Fighter_GObj* fighter_gobj)
{
    Fighter* fp;

    fp = fighter_gobj->user_data;
    fp->take_dmg_cb = 0;
    fp->death2_cb = 0;
}


// AS_SheikChargeNeedlesStartGround
// 801120E8 - 80112198 (0xB0 bytes)
// https://decomp.me/scratch/86XVe
// https://decomp.me/scratch/X0h7H
void ftSk_SpecialN_Enter(Fighter_GObj* fighter_gobj)
{
    // Fighter* fp = GET_FIGHTER(fighter_gobj);
    Fighter* fp2;
    Fighter* fp;
    //u32 unused[1];
    
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u32 _[1];
#endif

    fp = GET_FIGHTER(fighter_gobj);

    Fighter_ChangeMotionState(fighter_gobj, 0x155, 0, 1.0, 0, 1.0, 0);

    fp->throw_flags_b0 = 0;
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0; // x2200
    fp->mv.sk.specialn.x0 = 0; // x2340
    
    if (fp->fv.sk.x222C == 0) {
        fp->fv.sk.x222C = 1;
    }
    
    fp->mv.sk.specialn.x4 = 0;
    fp->mv.sk.specialn.x8 = 0;
    
    fp2 = fighter_gobj->user_data;
    fp2->take_dmg_cb = ftSk_Init_80110198;
    fp2->death2_cb = ftSk_Init_80110198;
    
    ftAnim_8006EBA4(fighter_gobj);
}


// 80112198 - 80112248 (0xB0 bytes)
// https://decomp.me/scratch/i6fz7
// https://decomp.me/scratch/pBB3D
void ftSk_SpecialAirN_Enter(Fighter_GObj* fighter_gobj)
{
    Fighter* fp;
    Fighter* fp2;
    //u32 unused[1];
    
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u32 _[1];
#endif
    
    fp = GET_FIGHTER(fighter_gobj);
    
    Fighter_ChangeMotionState(fighter_gobj, 0x159, 0, 1.0, 0.0, 1.0, 0);
    
    fp->throw_flags_b0 = 0;
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0; // x2200
    fp->mv.sk.specialn.x0 = 0; // x2340
    
    if (fp->fv.sk.x222C == 0) {
        fp->fv.sk.x222C = 1;
    }
    
    fp->mv.sk.specialn.x4 = 0;
    fp->mv.sk.specialn.x8 = 0;
    
    fp2 = fighter_gobj->user_data;
    fp2->take_dmg_cb = ftSk_Init_80110198;
    fp2->death2_cb = ftSk_Init_80110198;
    
    ftAnim_8006EBA4(fighter_gobj);
}


// 80112248 - 801122D8 (0x90 bytes)
// https://decomp.me/scratch/NUVmH
void ftSk_SpecialNStart_Anim(Fighter_GObj* fighter_gobj)
{
    Fighter* fp;
    Fighter* fp2;

    fp = getFighterPlus(fighter_gobj);
    
    if (ftAnim_IsFramesRemaining(fighter_gobj) == 0)
    {
        fp->fv.sk.x2230 = it_802B19AC(fighter_gobj, &fp->cur_pos, 0x17, 0x50, fp->facing_dir);
        Fighter_ChangeMotionState(fighter_gobj, 0x156, 0, 0, 0, 1.0, 0);
        
        fp2 = getFighter(fighter_gobj);
        fp2->take_dmg_cb = ftSk_Init_80110198;
        fp2->death2_cb = ftSk_Init_80110198;
    }
}


// Sheik_ChargeNeedlesIncrementer
// 801122D8 - 80112384 (0xAC bytes)
// https://decomp.me/scratch/fctpe (old/incomplete)
// https://decomp.me/scratch/tnaEG
void ftSk_SpecialNLoop_Anim(Fighter_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    switch (fp->mv.sk.specialn.x8) 
    {
        case 0:
            ft_80088148(getFighterPlus(fighter_gobj), 0x41F36, 0x7F, 0x40);
    }

    fp->mv.sk.specialn.x8 += 1;

    if (fp->cur_anim_frame == 0) {
        fp->fv.sk.x222C += 1;
        fp->mv.sk.specialn.x8 = 0;
        
        if ((s32) fp->fv.sk.x222C > 6) {
            fp->fv.sk.x222C = 6;
            fp->mv.sk.specialn.x8 = 0x64;
            ftCo_800BFFD0(fp, 0x56, 0);
        }
    }
}


// Animation_SheikNeedleCancelGround
// 80112384 - 801123CC (0x48 bytes)
// https://decomp.me/scratch/39tsN
void ftSk_SpecialNCancel_Anim(Fighter_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    fp->fv.sk.x2230 = 0;

    if (ftAnim_IsFramesRemaining(fighter_gobj) == 0){
        ft_8008A2BC(fighter_gobj);
    }
}


// 801123CC - 80112408 (0x3C bytes)
// 80112408 - 80112418 (0x10 bytes)
// 80112418 - 80112450 (0x38 bytes)
// https://decomp.me/scratch/sFuUX
// https://decomp.me/scratch/QoA5Q
void ftSk_SpecialNEnd_Anim(Fighter_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    s32 specialN_x0 = fp->mv.sk.specialn.x0;
    // s32 unused[6];
    
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u32 _[6];
#endif

    switch (specialN_x0)
    {
        case 0: // % 3 == 0
        case 3:
        case 6:
        case 9:
        case 12:
        case 15:
            // fallthrough
    
        case 1: // % 3 == 1
        case 4:
        case 7:
        case 10:
        case 13:
        case 16:
            fp->mv.sk.specialn.x4 = 1; //2344
            fp->fv.sk.x2230 = 0;
            // fallthrough again
    
        case 2: // % 3 == 2
        case 5:
        case 8:
        case 11:
        case 14:
        case 17:
            fp->mv.sk.specialn.x0 += 1;
            
            if (ftAnim_IsFramesRemaining(fighter_gobj) == 0)
            {
                ft_8008A2BC(fighter_gobj);
            }
    }
}


// 80112450 - 801124E0 (0x90 bytes)
// https://decomp.me/scratch/Wx7qX
void ftSk_SpecialAirNStart_Anim(Fighter_GObj* fighter_gobj) {
    Fighter* fp; // r31
    Fighter* fp2; // r4
    // s32 unused[2];
    
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u32 _[2];
#endif

    fp = GET_FIGHTER(fighter_gobj);

    if (ftAnim_IsFramesRemaining(fighter_gobj) == 0)
    {
        fp->fv.sk.x2230 = it_802B19AC(fighter_gobj, &fp->cur_pos, 0x17, 0x50, fp->facing_dir);
        Fighter_ChangeMotionState((Fighter_GObj* ) fighter_gobj, 0x15A, 0U, 0.0, 1.0, 0.0, 0);
        fp2 = fighter_gobj->user_data;
        fp2->take_dmg_cb = ftSk_Init_80110198;
        fp2->death2_cb = ftSk_Init_80110198;
    }
}

// 801124E0 - 8011258C (0xAC bytes)
// https://decomp.me/scratch/u10kG
void ftSk_SpecialAirNLoop_Anim(Fighter_GObj* fighter_gobj) {
    Fighter* fp = GET_FIGHTER(fighter_gobj); // r3
    s32 specialN_x8 = fp->mv.sk.specialn.x8;
    
    switch (specialN_x8) 
    {
        case 0:
            ft_80088148(fighter_gobj->user_data, 0x41F36, 0x7F, 0x40);
    }
    
    fp->mv.sk.specialn.x8 += 1;
    
    if (fp->cur_anim_frame == 0) {
        fp->fv.sk.x222C += 1;
        fp->mv.sk.specialn.x8 = 0;
        
        if (fp->fv.sk.x222C > 6) {
            fp->fv.sk.x222C = 6;
            fp->mv.sk.specialn.x8 = 0x64;
            ftCo_800BFFD0(fp, 0x56, 0);
        }
    }
}

// 8011258C - 8011260C (0x80 bytes)

// 8011260C - 80112650 (0x44 bytes)

// 80112650 - 80112660 (0x10 bytes)

// 80112660 - 801126C8 (0x68 bytes)

// 801126C8 - 801126CC (0x4 bytes)

// 801126CC - 80112798 (0xCC bytes)

// 80112798 - 8011279C (0x4 bytes)

// 8011279C - 801127A0 (0x4 bytes)

// 801127A0 - 801127A4 (0x4 bytes)

// 801127A4 - 80112870 (0xCC bytes)

// 80112870 - 80112874 (0x4 bytes)

// 80112874 - 80112878 (0x4 bytes)

// 80112878 - 80112898 (0x20 bytes)

// 80112898 - 801128B8 (0x20 bytes)

// 801128B8 - 801128D8 (0x20 bytes)

// 801128D8 - 801128F8 (0x20 bytes)

// 801128F8 - 80112918 (0x20 bytes)

// 80112918 - 80112938 (0x20 bytes)

// 80112938 - 80112958 (0x20 bytes)

// 80112958 - 80112978 (0x20 bytes)

// 80112978 - 801129F8 (0x80 bytes)

// 801129F8 - 80112A78 (0x80 bytes)

// 80112A78 - 80112B00 (0x88 bytes)

// 80112B00 - 80112B98 (0x98 bytes)

// Collision_SheikNeedleStartupAir
// 80112B98 - 80112C18 (0x80 bytes)

// Collision_SheikNeedleChargeAir
// 80112C18 - 80112C98 (0x80 bytes)

// 80112C98 - 80112CE4 (0x4C bytes)

// Collision_SheikNeedleThrowAir
// 80112CE4 - 80112D44 (0x60 bytes)

// Sheik_ShootNeedles
// 80112D44 - 80112ED8 (0x194 bytes)
