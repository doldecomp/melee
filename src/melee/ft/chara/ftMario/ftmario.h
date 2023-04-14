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

extern MotionState ftMario_MotionStateTable[];
extern MotionState lbl_803C7260[];

// ftmario1
void ftMario_OnDeath(HSD_GObj*);
void ftMario_OnLoadForDrMario(Fighter*);
void ftMario_OnLoad(HSD_GObj*);
void ftMario_OnTakeDamage(HSD_GObj*);
void ftMario_OnItemPickup(HSD_GObj*, bool);
void ftMario_OnItemInvisible(HSD_GObj*);
void ftMario_OnItemVisible(HSD_GObj*);
void ftMario_OnItemDrop(HSD_GObj*, bool);
void ftMario_LoadSpecialAttrs(HSD_GObj*);
void ftMario_OnKnockbackEnter(HSD_GObj*);
void ftMario_OnKnockbackExit(HSD_GObj*);
void ftMario_800E0CAC(s32, s32*, s32*);
unk_t ftMario_GetMotionFileString(enum_t arg0);

// ftmario2
int ftMario_SpecialN_VitaminRandom(HSD_GObj*);
void ftMario_SpecialN_StartMotion(HSD_GObj*);
void ftMario_SpecialN_Anim(HSD_GObj*);
void ftMario_SpecialN_IASA(HSD_GObj*);
void ftMario_SpecialN_Phys(HSD_GObj*);
void ftMario_SpecialN_Coll(HSD_GObj*);
void ftMario_SpecialN_ItemFireSpawn(HSD_GObj*);
void ftMario_SpecialAirN_StartMotion(HSD_GObj*);
void ftMario_SpecialAirN_Anim(HSD_GObj*);
void ftMario_SpecialAirN_IASA(HSD_GObj*);
void ftMario_SpecialAirN_Phys(HSD_GObj*);
void ftMario_SpecialAirN_Coll(HSD_GObj*);
void ftMario_SpecialN_GroundToAir(HSD_GObj*);
void ftMario_SpecialAirN_AirToGround(HSD_GObj*);

// ftmario3
void ftMario_SpecialS_CreateCape(HSD_GObj*);
void ftMario_SpecialS_SetNULL(HSD_GObj*);
void ftMario_SpecialS_RemoveCape(HSD_GObj*);
void ftMario_SpecialS_EnterHitlag(HSD_GObj*);
void ftMario_SpecialS_ExitHitlag(HSD_GObj*);
void ftMario_SpecialS_ExitHitlag(HSD_GObj*);
bool ftMario_SpecialS_CheckItemCapeRemove(HSD_GObj*);
void ftMario_SpecialS_StartMotion(HSD_GObj*);
void ftMario_SpecialAirS_StartMotion(HSD_GObj*);
void ftMario_SpecialS_Anim(HSD_GObj*);
void ftMario_SpecialAirS_Anim(HSD_GObj*);
void ftMario_SpecialS_IASA(HSD_GObj*);
void ftMario_SpecialAirS_IASA(HSD_GObj*);
void ftMario_SpecialS_Phys(HSD_GObj*);
void ftMario_SpecialAirS_Phys(HSD_GObj*);
void ftMario_SpecialS_Coll(HSD_GObj*);
void ftMario_SpecialAirS_Coll(HSD_GObj*);
void ftMario_SpecialS_GroundToAir(HSD_GObj*);
void ftMario_SpecialAirS_AirToGround(HSD_GObj*);

// ftmario4
void ftMario_SpecialHi_StartMotion(HSD_GObj*);
void ftMario_SpecialAirHi_StartMotion(HSD_GObj*);
void ftMario_SpecialHi_Anim(HSD_GObj*);
void ftMario_SpecialAirHi_Anim(HSD_GObj*);
void ftMario_SpecialHi_IASA(HSD_GObj*);
void ftMario_SpecialAirHi_IASA(HSD_GObj*);
void ftMario_SpecialHi_Phys(HSD_GObj*);
void ftMario_SpecialAirHi_Phys(HSD_GObj*);
void ftMario_SpecialHi_CheckLanding(HSD_GObj*);
void ftMario_SpecialHi_Coll(HSD_GObj*);
void ftMario_SpecialAirHi_Coll(HSD_GObj*);

// ftmario5
void ftMario_SpecialLw_UpdateRot(HSD_GObj*);
void ftMario_SpecialLw_StartMotion(HSD_GObj*);
void ftMario_SpecialAirLw_StartMotion(HSD_GObj*);
void ftMario_SpecialLw_Anim(HSD_GObj*);
void ftMario_SpecialAirLw_Anim(HSD_GObj*);
void ftMario_SpecialLw_IASA(HSD_GObj*);
void ftMario_SpecialAirLw_IASA(HSD_GObj*);
void ftMario_SpecialLw_Phys(HSD_GObj*);
void ftMario_SpecialAirLw_Phys(HSD_GObj*);
void ftMario_SpecialLw_Coll(HSD_GObj*);
void ftMario_SpecialAirLw_Coll(HSD_GObj*);

#endif
