#ifndef MELEE_FT_CHARA_FTLUIGI_TYPES_H
#define MELEE_FT_CHARA_FTLUIGI_TYPES_H

#include <platform.h>

#include "ft/forward.h"

struct ftLuigi_FighterVars {
    /* 0x222C */ bool x222C_cycloneCharge;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    u8 _[FIGHTERVARS_SIZE - 0xC];
};

typedef struct _ftLuigiAttributes {
    /// SIDE SPECIAL - GREEN MISSILE
    float x0_LUIGI_GREENMISSILE_UNK1;
    float x4_LUIGI_GREENMISSILE_SMASH;
    float x8_LUIGI_GREENMISSILE_CHARGE_RATE;
    float xC_LUIGI_GREENMISSILE_MAX_CHARGE_FRAMES;
    float x10_LUIGI_GREENMISSILE_DAMAGE_TILT;
    /// (base damage + charge duration) * this value?
    float x14_LUIGI_GREENMISSILE_DAMAGE_SLOPE;
    float x18_LUIGI_GREENMISSILE_TRACTION;
    float x1C_LUIGI_GREENMISSILE_UNK2;
    float x20_LUIGI_GREENMISSILE_FALLING_SPEED;
    float x24_LUIGI_GREENMISSILE_VEL_X;
    float x28_LUIGI_GREENMISSILE_MUL_X;
    float x2C_LUIGI_GREENMISSILE_VEL_Y;
    float x30_LUIGI_GREENMISSILE_MUL_Y;
    float x34_LUIGI_GREENMISSILE_GRAVITY_START;
    float x38_LUIGI_GREENMISSILE_FRICTION_END;
    float x3C_LUIGI_GREENMISSILE_X_DECEL;
    float x40_LUIGI_GREENMISSILE_GRAVITY_MUL;
    /// 1.0f divided by this value
    float x44_LUIGI_GREENMISSILE_MISFIRE_CHANCE;
    float x48_LUIGI_GREENMISSILE_MISFIRE_VEL_X;
    float x4C_LUIGI_GREENMISSILE_MISFIRE_VEL_Y;
    /// UP SPECIAL - SUPER JUMP PUNCH
    /// Multiplies Luigi's max horionztal aerial mobility
    float x50_LUIGI_SUPERJUMP_FREEFALL_MOBILITY;
    float x54_LUIGI_SUPERJUMP_LANDING_LAG;
    /// Minimum stick range required for turnaround
    float x58_LUIGI_SUPERJUMP_REVERSE_STICK_RANGE;
    /// Minimum stick range required for horionztal momentum?
    float x5C_LUIGI_SUPERJUMP_MOMENTUM_STICK_RANGE;
    float x60_LUIGI_SUPERJUMP_ANGLE_DIFF;
    float x64_LUIGI_SUPERJUMP_VEL_X;
    float x68_LUIGI_SUPERJUMP_GRAVITY_START;
    float x6C_LUIGI_SUPERJUMP_VEL_Y;
    /// DOWN SPECIAL - LUIGI CYCLONE
    /// Vertical momentum from (first?) B button tap
    float x70_LUIGI_CYCLONE_TAP_MOMENTUM;
    float x74_LUIGI_CYCLONE_MOMENTUM_X_GROUND;
    float x78_LUIGI_CYCLONE_MOMENTUM_X_AIR;
    float x7C_LUIGI_CYCLONE_MOMENTUM_X_MUL_GROUND;
    float x80_LUIGI_CYCLONE_MOMENTUM_X_MUL_AIR;
    float x84_LUIGI_CYCLONE_FRICTION_END;
    s32 x88_LUIGI_CYCLONE_UNK;
    float x8C_LUIGI_CYCLONE_TAP_Y_VEL_MAX;
    float x90_LUIGI_CYCLONE_TAP_GRAVITY;
    s32 x94_LUIGI_CYCLONE_LANDING_LAG;
} ftLuigiAttributes;

typedef struct ftLuigiSpecialS {
    /// 0x2340 - Number of frames Green Missile has been charged
    s32 chargeFrames;
    /// 0x2344 - Check if Green Missile will misfire
    bool isMisfire;
} ftLuigiSpecialS;

typedef struct ftLuigiSpecialLw {
    /// 0x2340 - Grounded momentum of Luigi Cyclone
    float groundVelX;
    /// 0x2344 - Set but never used?
    s32 unk;
    /// 0x2348 - Skipped entirely
    s32 _;
    /// 0x234C - Checked in collision, related to some angle calculation
    bool isUnkColl;
} ftLuigiSpecialLw;

typedef union ftLuigi_MotionVars {
    ftLuigiSpecialS SpecialS;
    ftLuigiSpecialLw SpecialLw;
} ftLuigi_MotionVars;

#endif
