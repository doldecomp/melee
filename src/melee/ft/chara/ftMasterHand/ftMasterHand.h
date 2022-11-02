#ifndef FT_CHARA_FTMASTERHAND_FTMASTERHAND_H
#define FT_CHARA_FTMASTERHAND_FTMASTERHAND_H

#include <sysdolphin/baselib/gobj.h>

typedef struct _MasterHandAttributes {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    f32 x28;
    f32 x2C;
    Vec2 x30_pos2;
    f32 x38;
    f32 x3C;
    Vec3 x40_pos;
    f32 x4C;
    Vec2 x50;
    f32 x58;
    f32 x5C;
    f32 x60;
    f32 x64;
    f32 x68;
    s32 x6C;
    s32 x70;
    s32 x74;
    f32 x78;
    s32 x7C;
    f32 x80;
    s32 x84;
    Vec2 x88_pos;
    s32 x90;
    s32 x94;
    f32 x98;
    f32 x9C;
    s32 xA0;
    f32 xA4;
    Vec2 xA8_pos;
    s32 xB0;
    s32 xB4;
    f32 xB8;
    Vec2 xBC_pos;
    Vec2 xC4_pos;
    Vec2 xCC_pos;
    f32 xD4;
    f32 xD8;
    f32 xDC;
    f32 xE0;
    f32 xE4;
    f32 xE8;
    s32 xEC;
    s32 xF0;
    f32 xF4;
    f32 xF8;
    f32 xFC;
    f32 x100;
    f32 x104;
    f32 x108;
    f32 x10C;
    Vec2 x110_pos;
    Vec2 x118_pos;
    f32 x120;
    Vec2 x124_pos;
    Vec2 x12C_pos;
    Vec2 x134_pos;
    Vec2 x13C_pos;
    s32 x144;
    s32 x148;
    f32 x14C;
    f32 x150;
    f32 x154;
    f32 x158;
    f32 x15C;
    s32 x160;
    s32 x164;
    s32 x168;
    s32 x16C;
    s32 x170;
    s32 x174;
    f32 x178;
} MasterHandAttributes;

typedef enum ftMasterHandAction {
    AS_MASTERHAND_UNK_341 = 341,
    AS_MASTERHAND_UNK_342,
    AS_MASTERHAND_UNK_343,
    AS_MASTERHAND_UNK_344,
    AS_MASTERHAND_UNK_345,
    AS_MASTERHAND_UNK_346,
    AS_MASTERHAND_UNK_347,
    AS_MASTERHAND_UNK_348,
    AS_MASTERHAND_UNK_349,
    AS_MASTERHAND_UNK_350,
    AS_MASTERHAND_UNK_351,
    AS_MASTERHAND_UNK_352,
    AS_MASTERHAND_UNK_353,
    AS_MASTERHAND_UNK_354,
    AS_MASTERHAND_UNK_355,
    AS_MASTERHAND_UNK_356,
    AS_MASTERHAND_UNK_357,
    AS_MASTERHAND_UNK_358,
    AS_MASTERHAND_UNK_359,
    AS_MASTERHAND_UNK_360,
    AS_MASTERHAND_UNK_361,
    AS_MASTERHAND_UNK_362,
    AS_MASTERHAND_UNK_363,
    AS_MASTERHAND_UNK_364,
    AS_MASTERHAND_UNK_365,
    AS_MASTERHAND_UNK_366,
    AS_MASTERHAND_UNK_367,
    AS_MASTERHAND_UNK_368,
    AS_MASTERHAND_UNK_369,
    AS_MASTERHAND_UNK_370,
    AS_MASTERHAND_UNK_371,
    AS_MASTERHAND_UNK_372,
    AS_MASTERHAND_UNK_373,
    AS_MASTERHAND_UNK_374,
    AS_MASTERHAND_UNK_375,
    AS_MASTERHAND_UNK_376,
    AS_MASTERHAND_UNK_377,
    AS_MASTERHAND_UNK_378,
    AS_MASTERHAND_UNK_379,
    AS_MASTERHAND_UNK_380,
    AS_MASTERHAND_UNK_381,
    AS_MASTERHAND_UNK_382,
    AS_MASTERHAND_UNK_383,
    AS_MASTERHAND_UNK_384,
    AS_MASTERHAND_UNK_385,
    AS_MASTERHAND_UNK_386,
    AS_MASTERHAND_UNK_387,
    AS_MASTERHAND_UNK_388,
    AS_MASTERHAND_UNK_389,
    AS_MASTERHAND_UNK_390,
} ftMasterHandAction;

#pragma region "ftMasterHand_1"
void ftMasterhand_OnDeath(HSD_GObj* fighter_gobj);
void ftMasterhand_OnLoad(HSD_GObj* fighter_gobj);
#pragma endregion

#pragma region "ftMasterHand_2"
void ftMasterHand_LoadSpecialAttrs(HSD_GObj* fighter_gobj);
void ftMasterHand_8014FE10(HSD_GObj* fighter_gobj);
void ftMasterHand_8014FE58(HSD_GObj* fighter_gobj);
void ftMasterHand_80150890(HSD_GObj* fighter_gobj);
#pragma endregion

#pragma region "ftMasterHand_3"
void lbl_80150F00(HSD_GObj* fighter_gobj);
void lbl_80150F68(HSD_GObj* fighter_gobj);
void ftMasterHand_80150FC8(HSD_GObj* fighter_gobj);
void ftMasterHand_80151018(HSD_GObj* fighter_gobj);
#pragma endregion

#pragma region "ftMasterHand_4"
void ftMasterHand_80151168(HSD_GObj* fighter_gobj);
void ftMasterHand_801511B0(HSD_GObj* fighter_gobj);
void ftMasterHand_801511F4(HSD_GObj* fighter_gobj);
void ftMasterHand_801511F8(HSD_GObj* fighter_gobj);
#pragma endregion

#pragma region "ftMasterHand 32"
void ftMasterHand_80155B7C(HSD_GObj* fighter_gobj);
void ftMasterHand_80155C20(HSD_GObj* fighter_gobj);
#pragma endregion

#pragma region "ftMasterHand 33"
void ftMasterHand_80155C88(HSD_GObj* fighter_gobj);
void ftMasterHand_80155C8C(HSD_GObj* fighter_gobj);
void ftMasterHand_80155C90(HSD_GObj* fighter_gobj);
#pragma endregion

#pragma region "ftMasterHand 34"
void ftMasterHand_80155D5C(HSD_GObj* fighter_gobj);
void ftMasterHand_80155D60(HSD_GObj* fighter_gobj);
void ftMasterHand_80155D64(HSD_GObj* fighter_gobj);
void ftMasterHand_80155D68(HSD_GObj* fighter_gobj);
void ftMasterHand_80155E08(HSD_GObj* fighter_gobj);
void ftMasterHand_80155E0C(HSD_GObj* fighter_gobj);
void ftMasterHand_80155E10(HSD_GObj* fighter_gobj);
void ftMasterHand_80155E14(HSD_GObj* fighter_gobj);
#pragma endregion

#endif
