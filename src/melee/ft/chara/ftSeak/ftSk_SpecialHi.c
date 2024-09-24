#include "ft/forward.h"
#include "ftSeak/forward.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_0877.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "it/items/itseakvanish.h"
#include "lb/lb_00B0.h"

#include <math.h>
#include <placeholder.h>
#include <baselib/gobj.h>

/* 112F48 */ static void ftSk_SpecialHi_80112F48(Fighter_GObj* gobj);
/* 112FA8 */ static void ftSk_SpecialHi_80112FA8(Fighter_GObj* gobj);
/* 113038 */ static void fn_80113038(Fighter_GObj* gobj);

static float const ftSk_Init_804D9660 = 0;
static float const ftSk_Init_804D9664 = 1;
static double const ftSk_Init_804D9668 = S32_TO_F32;
static float const ftSk_Init_804D9670 = deg_to_rad;
static float const ftSk_Init_804D9674 = 90;
static double const ftSk_Init_804D9678 = 0.5;
static double const ftSk_Init_804D9680 = 3;
static float const ftSk_Init_804D9688 = M_PI / 2;
static float const ftSk_Init_804D968C = 35;
static float const ftSk_Init_804D9690 = 0.001;
static float const ftSk_Init_804D9694 = 10;

void fn_80112ED8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_b0) {
        ftSk_SpecialHi_80112F48(gobj);
        ftSk_SpecialHi_80112FA8(gobj);
        ft_80088148(fp, 115, 127, 64);
    }
    fp->accessory4_cb = NULL;
}

void ftSk_SpecialHi_80112F48(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[4];
    {
        Vec3 pos;
        u8 _[4];
        lb_8000B1CC(fp->parts[FtPart_HipN].joint, 0, &pos);
        pos.z = 0;
        it_802B1C60(gobj, &pos, fp->facing_dir);
    }
}

void ftSk_SpecialHi_80112FA8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    lb_8000B1CC(fp->parts[FtPart_HipN].joint, 0, &pos);
    if (!fp->x2219_b0) {
        efSync_Spawn(1284, gobj, &pos);
        fp->x2219_b0 = true;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

void fn_80113038(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    if (!fp->x2219_b0) {
        lb_8000B1CC(fp->parts[FtPart_HipN].joint, 0, &pos);
        efSync_Spawn(1285, gobj, &pos);
        fp->x2219_b0 = true;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

void ftSk_SpecialHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[20];
    fp->cmd_vars[0] = 0;
    fp->mv.sk.specialhi.xC = 0;
    Fighter_ChangeMotionState(gobj, ftSk_MS_SpecialHiStart_0, 0, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
}

void ftSk_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* da = fp->dat_attrs;
    u8 _[20];
    fp->cmd_vars[0] = 0;
    fp->mv.sk.specialhi.xC = 0;
    fp->self_vel.y = da->self_vel_y;
    Fighter_ChangeMotionState(gobj, ftSk_MS_SpecialAirHiStart_0, 0, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
}

/// #fn_80112ED8

/// #ftSk_SpecialHi_80112F48

/// #ftSk_SpecialHi_80112FA8

/// #fn_80113038

/// #ftSk_SpecialHi_Enter

/// #ftSk_SpecialAirHi_Enter

/// #ftSk_SpecialHiStart_0_Anim

/// #ftSk_SpecialAirHiStart_0_Anim

void ftSk_SpecialHiStart_0_IASA(HSD_GObj* gobj) {}

// Interrupt_SheikUpBStartAir
void ftSk_SpecialAirHiStart_0_IASA(HSD_GObj* gobj) {}

/// #ftSk_SpecialHiStart_0_Phys

/// #ftSk_SpecialAirHiStart_0_Phys

/// #ftSk_SpecialHiStart_0_Coll

/// #ftSk_SpecialAirHiStart_0_Coll

/// #ftSk_SpecialHi_80113324

/// #ftSk_SpecialHi_80113390

/// #ftSk_SpecialHiStart_1_Anim

// Animation_SheikUpBTravel
/// #ftSk_SpecialAirHiStart_1_Anim

void ftSk_SpecialHiStart_1_IASA(HSD_GObj* gobj) {}

// Interrupt_SheikUpBTravelAir
void ftSk_SpecialAirHiStart_1_IASA(HSD_GObj* gobj) {}

// Physics_SheikUpBTravelAir
/// #ftSk_SpecialHiStart_1_Phys

void ftSk_SpecialAirHiStart_1_Phys(HSD_GObj* gobj) {}

/// #ftSk_SpecialHiStart_1_Coll

/// #ftSk_SpecialAirHiStart_1_Coll

// AS_SheikUpBGroundtoAirFall?
/// #ftSk_SpecialHi_8011374C

// AS_SheikUpBLand
/// #ftSk_SpecialHi_801137C8

// AS_SheikUpBTravelGround
/// #ftSk_SpecialHi_80113838

// AS_SheikUpBTravelAir
/// #ftSk_SpecialHi_80113A30

/// #ftSk_SpecialHi_Anim

/// #ftSk_SpecialAirHi_Anim

void ftSk_SpecialHi_IASA(HSD_GObj* gobj) {}

// Interrupt_SheikUpBEndAir
void ftSk_SpecialAirHi_IASA(HSD_GObj* gobj) {}

/// #ftSk_SpecialHi_Phys

/// #ftSk_SpecialAirHi_Phys

/// #ftSk_SpecialHi_Coll

/// #ftSk_SpecialAirHi_Coll

/// #ftSk_SpecialHi_80113E40

/// #ftSk_SpecialHi_80113EAC

// AS_SheikUpBFall
/// #ftSk_SpecialHi_80113F68
