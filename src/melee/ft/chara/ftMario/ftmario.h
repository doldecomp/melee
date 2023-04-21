#ifndef _ftmario_h_
#define _ftmario_h_

#include "ft/fighter.h"
#include "ft/ftcommon.h"

#include <baselib/gobj.h>

typedef enum ftMarioAction {
    AS_MARIO_UNK1 = ASID_MAX,
    AS_MARIO_UNK2,
    AS_MARIO_SPECIALN,
    AS_MARIO_SPECIALAIRN,
    AS_MARIO_SPECIALS,
    AS_MARIO_SPECIALAIRS,
    AS_MARIO_SPECIALHI,
    AS_MARIO_SPECIALAIRHI,
    AS_MARIO_SPECIALLW,
    AS_MARIO_SPECIALAIRLW,
} ftMarioAction;

// Flags used by Mario & Dr. Mario in Motion State Change //

// SpecialN/SpecialAirN (Fireball / Megavitamin) //

// SpecialS/SpecialAirS (Cape / Super Sheet) //

#define FTMARIO_SPECIALS_COLL_FLAG                                            \
    FtStateChange_PreserveColAnimHitStatus | FtStateChange_SkipUpdateHit |    \
        FtStateChange_SkipUpdateMatAnim | FtStateChange_UpdateCmd |           \
        FtStateChange_SkipUpdateColAnim | FtStateChange_SkipUpdateItemVis |   \
        FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |         \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

// SpecialLw/SpecialAirLw (Mario / Dr. Tornado ) //

#define FTMARIO_SPECIALLW_COLL_FLAG                                           \
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateHit |                 \
        FtStateChange_SkipUpdateMatAnim | FtStateChange_UpdateCmd |           \
        FtStateChange_SkipUpdateColAnim | FtStateChange_SkipUpdateItemVis |   \
        FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |         \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

typedef struct _ftMarioAttributes {
    // SIDE SPECIAL - CAPE / SUPER SHEET //

    /* 0x00 */ f32 vel_x_decay;
    /* 0x04 */ f32 x4_MARIO_CAPE_VEL_X;
    /* 0x08 */ f32 x8_MARIO_CAPE_VEL_Y;
    /* 0x0C */ f32 xC_MARIO_CAPE_GRAVITY;
    /* 0x10 */ f32 x10_MARIO_CAPE_TERMINAL_VELOCITY;
    /* 0x14 */ s32 x14_MARIO_CAPE_IT_KIND;

    // UP SPECIAL - SUPER JUMP PUNCH //

    /* 0x18 */ f32 x18_MARIO_SUPERJUMP_FREEFALL_MOBILITY;
    /* 0x1C */ f32 x1C_MARIO_SUPERJUMP_LANDING_LAG;
    /* 0x20 */ f32 x20_MARIO_SUPERJUMP_REVERSE_STICK_RANGE;
    /* 0x24 */ f32 x24_MARIO_SUPERJUMP_MOMENTUM_STICK_RANGE;
    /* 0x28 */ f32 x28_MARIO_SUPERJUMP_ANGLE_DIFF;
    /* 0x2C */ f32 x2C_MARIO_SUPERJUMP_VEL_X;
    /* 0x30 */ f32 x30_MARIO_SUPERJUMP_GRAVITY;
    /* 0x34 */ f32 x34_MARIO_SUPERJUMP_VEL_MUL;

    // DOWN SPECIAL - MARIO TORNADO / DR. TORNADO //

    /* 0x38 */ f32 x38_MARIO_TORNADO_GROUND_VEL_Y; // Vertical momentum from
                                                   // inital grounded B-tap
    /* 0x3C */ f32 x3C_MARIO_TORNADO_MOMENTUM_X_GROUND;
    /* 0x40 */ f32 x40_MARIO_TORNADO_MOMENTUM_X_AIR;
    /* 0x44 */ f32 x44_MARIO_TORNADO_MOMENTUM_X_MUL_GROUND;
    /* 0x48 */ f32 x48_MARIO_TORNADO_MOMENTUM_X_MUL_AIR;
    /* 0x4C */ f32 x4C_MARIO_TORNADO_FRICTION_END;
    /* 0x50 */ s32 x50_MARIO_TORNADO_UNK;
    /* 0x54 */ f32 x54_MARIO_TORNADO_TAP_Y_VEL_MAX;
    /* 0x58 */ f32 x58_MARIO_TORNADO_TAP_GRAVITY;
    /* 0x5C */ s32 x5C_MARIO_TORNADO_LANDING_LAG;

    // CAPE / SUPER SHEET REFLECTION //

    /* 0x60 */ ReflectDesc x60_MARIO_CAPE_REFLECTION;

} ftMarioAttributes;

typedef struct ftMario_SpecialLw_ECB {
    u8 x0_str_arr[3];
    u8 x3_balign;
    u32 x4;
    u32 x8;
    u32 xC;
    u32 x10;
    u32 x14;
} ftMario_SpecialLw_ECB;

static inline ftMarioAttributes* GetMarioAttr(Fighter* fp)
{
    ftMarioAttributes* mario_attr = fp->x2D4_specialAttributes;
    return mario_attr;
}

extern MotionState ftMr_Init_MotionStateTable[];
extern MotionState ftMr_Init_UnkMotionStates0[];

// ftmario1
void ftMr_Init_OnDeath(HSD_GObj*);
void ftMr_Init_OnLoadForDrMario(Fighter*);
void ftMr_Init_OnLoad(HSD_GObj*);
void ftMr_Init_OnTakeDamage(HSD_GObj*);
void ftMr_Init_OnItemPickup(HSD_GObj*, bool);
void ftMr_Init_OnItemInvisible(HSD_GObj*);
void ftMr_Init_OnItemVisible(HSD_GObj*);
void ftMr_Init_OnItemDrop(HSD_GObj*, bool);
void ftMr_Init_LoadSpecialAttrs(HSD_GObj*);
void ftMr_Init_OnKnockbackEnter(HSD_GObj*);
void ftMr_Init_OnKnockbackExit(HSD_GObj*);
void ftMr_Init_UnkDemoCallbacks0(s32, s32*, s32*);
unk_t ftMr_Init_GetMotionFileString(enum_t arg0);

// ftmario2
int ftMr_SpecialN_VitaminRandom(HSD_GObj*);
void ftMr_SpecialN_Enter(HSD_GObj*);
void ftMr_SpecialN_Anim(HSD_GObj*);
void ftMr_SpecialN_IASA(HSD_GObj*);
void ftMr_SpecialN_Phys(HSD_GObj*);
void ftMr_SpecialN_Coll(HSD_GObj*);
void ftMr_SpecialN_ItemFireSpawn(HSD_GObj*);
void ftMr_SpecialAirN_Enter(HSD_GObj*);
void ftMr_SpecialAirN_Anim(HSD_GObj*);
void ftMr_SpecialAirN_IASA(HSD_GObj*);
void ftMr_SpecialAirN_Phys(HSD_GObj*);
void ftMr_SpecialAirN_Coll(HSD_GObj*);
void ftMr_SpecialN_GroundToAir(HSD_GObj*);
void ftMr_SpecialAirN_AirToGround(HSD_GObj*);

// ftmario3
void ftMr_SpecialS_CreateCape(HSD_GObj*);
void ftMr_SpecialS_Reset(HSD_GObj*);
void ftMr_SpecialS_RemoveCape(HSD_GObj*);
void ftMr_SpecialS_EnterHitlag(HSD_GObj*);
void ftMr_SpecialS_ExitHitlag(HSD_GObj*);
void ftMr_SpecialS_ExitHitlag(HSD_GObj*);
bool ftMr_SpecialS_CheckItemCapeRemove(HSD_GObj*);
void ftMr_SpecialS_Enter(HSD_GObj*);
void ftMr_SpecialAirS_Enter(HSD_GObj*);
void ftMr_SpecialS_Anim(HSD_GObj*);
void ftMr_SpecialAirS_Anim(HSD_GObj*);
void ftMr_SpecialS_IASA(HSD_GObj*);
void ftMr_SpecialAirS_IASA(HSD_GObj*);
void ftMr_SpecialS_Phys(HSD_GObj*);
void ftMr_SpecialAirS_Phys(HSD_GObj*);
void ftMr_SpecialS_Coll(HSD_GObj*);
void ftMr_SpecialAirS_Coll(HSD_GObj*);
void ftMr_SpecialS_GroundToAir(HSD_GObj*);
void ftMr_SpecialAirS_AirToGround(HSD_GObj*);

// ftmario4
void ftMr_SpecialHi_Enter(HSD_GObj*);
void ftMr_SpecialAirHi_Enter(HSD_GObj*);
void ftMr_SpecialHi_Anim(HSD_GObj*);
void ftMr_SpecialAirHi_Anim(HSD_GObj*);
void ftMr_SpecialHi_IASA(HSD_GObj*);
void ftMr_SpecialAirHi_IASA(HSD_GObj*);
void ftMr_SpecialHi_Phys(HSD_GObj*);
void ftMr_SpecialAirHi_Phys(HSD_GObj*);
void ftMr_SpecialHi_CheckLanding(HSD_GObj*);
void ftMr_SpecialHi_Coll(HSD_GObj*);
void ftMr_SpecialAirHi_Coll(HSD_GObj*);

// ftmario5
void updateRot(HSD_GObj*);
void ftMr_SpecialLw_Enter(HSD_GObj*);
void ftMr_SpecialAirLw_Enter(HSD_GObj*);
void ftMr_SpecialLw_Anim(HSD_GObj*);
void ftMr_SpecialAirLw_Anim(HSD_GObj*);
void ftMr_SpecialLw_IASA(HSD_GObj*);
void ftMr_SpecialAirLw_IASA(HSD_GObj*);
void ftMr_SpecialLw_Phys(HSD_GObj*);
void ftMr_SpecialAirLw_Phys(HSD_GObj*);
void ftMr_SpecialLw_Coll(HSD_GObj*);
void ftMr_SpecialAirLw_Coll(HSD_GObj*);

#endif
