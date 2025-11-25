#ifndef _player_h_
#define _player_h_

#include <platform.h>

#include "ft/forward.h"
#include "pl/forward.h"

#include "pl/types.h"

#include <baselib/forward.h>
#include <melee/pl/forward.h>

#include <dolphin/mtx.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

typedef struct _StaticPlayer {
    /// @at{0} @sz{4}
    /// @todo 0x02 In-Game (includes dead). 0x00 Otherwise.
    enum_t player_state;

    /// @at{4} @sz{4}
    /// @todo External ID.
    CharacterKind player_character;

    /// @at{8} @sz{4}
    Gm_PKind slot_type;

    /*0x0C*/ u8 transformed[2]; // 0x0001 for normal, 0x0100 for transformed
                                // (Probably Zelda/Sheik only)
    /*0x0E*/ s16 unk0E;

    union {
        struct {
            /*0x10-0x1B*/ Vec3
                nametag_pos; /// Horizontal, Vertical, Depth (floats)
            /*0x1C-0x27*/ Vec3 transformed_player_pos;
            /*0x28-0x33*/ Vec3 spawn_platform_final_pos;
            /*0x34-0x3f*/ Vec3 some_other_player_pos;
        } byVecName;

        Vec3 byIndex[4];
    } player_poses;

    /*0x40*/ f32 facing_direction;

    /*0x44*/ u8 costume_id; // 00 = normal, 01 = red, 02 = blue, 03 = green
                            // (reflected in icon immediately)
    /*0x45*/ u8 unk45;
    /*0x46*/ s8 controller_index;
    /*0x47*/ u8 team; /// 00 = red, 01 = blue, 02 = green
    /*0x48*/ u8 player_id;
    /*0x49*/ u8 cpu_level;
    /*0x4A*/ u8 cpu_type;
    /*0x4B*/ u8 handicap;

    /*0x4C*/ s8 unk4C;
    /*0x4D*/ s8 unk4D;
    /*0x4E*/ s8 unk4E;
    /*0x4F*/ s8 unk4F;

    /*0x50*/ f32 unk50;

    /*0x54*/ f32 attack_ratio;
    /*0x58*/ f32 defense_ratio;

    /*0x5C*/ f32 model_scale;

    union {
        struct {
            /*0x60*/ s16 damage_percent;
            /*0x62*/ s16 damage_percent_alt_or_start_hp;
            /*0x64*/ s16 stamina;
            /*0x66*/ s16 unk66;
        } byName;
        s16 byIndex[4];
    } staminas;

    /*0x68 - 0x6C*/ s32 falls[2]; /// other index for nana falls

    /*0x70-0x84*/ u32 kos_by_player[6];

    /// @at{88} @sz{4}
    /// @remarks If -1 in zz_0035184, then it's set to MatchInfo->frame_count
    u32 match_frame_count;

    /*0x8C*/ u16 suicide_count;

    /*0x8E*/ s8 stocks;
    /*0x8F*/ s8 unk8F;

    /*0x90*/ int current_coins;
    /*0x94*/ s32 total_coins;

    /*0x98*/ s32 unk98;
    /*0x9C*/ s32 unk9C;

    /*0xA0-A4*/ s32
        joystick_direction_input_count[2]; // Incremented every time you move
                                           // the joystick a different
                                           // direction from neutral.

    /*0xA8*/ int nametag_slot_id;

    /*0xAC*/ struct {
        u8 b0 : 1; // rumble enabled
        u8 b1 : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 is_metal : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    } flags;

    /*0xAD*/ struct {
        u8 b0 : 1;
        u8 b1 : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 2;
    } more_flags;

    /*0xAE*/ struct {
        u8 b0 : 1;
        u8 b1 : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    } flagsAE;

    /*0xAF*/ s8 unkAF;

    /*0xB0*/ HSD_GObj* player_entity[2];
    /*0xB4*/ /*void* sub_character_entity;*/ // Used for followers, such as
                                             // Nana

    /*0xB8*/ void (*struct_func)(s32 slot);

    /*0xBC*/ StaleMoveTable stale_moves;

    /*0xDB0*/ u8 xDB0[0xE90 - 0xDB0];

} StaticPlayer;

StaticPlayer* Player_GetPtrForSlot(int slot);
void Player_80031790(int slot);
void Player_80031848(int slot);
void Player_80031900(void);
bool Player_800319C4(int slot, bool arg1);
void Player_80031AD0(int slot);
void Player_80031CB0(CharacterKind kind, u8 color);
void Player_80031D2C(CharacterKind kind, u8 color);
void Player_80031DA8(s32 param_1, s32 param_2);
void Player_80031DC8(void func_arg(s32, s32));
void Player_80031EBC(int slot);
void Player_80031FB0(int slot, s32 entity_index);
void Player_80032070(int slot, bool bool_arg);
bool Player_8003219C(int slot);
bool Player_8003221C(int slot);
s32 Player_GetPlayerState(s32 slot);
CharacterKind Player_GetPlayerCharacter(int slot);
void Player_SetPlayerCharacter(s32 slot, CharacterKind value);
Gm_PKind Player_GetPlayerSlotType(s32 slot);
Gm_PKind Player_8003248C(s32 slot, bool arg1);
void Player_SetSlottype(s32 slot, Gm_PKind value);
s8 Player_800325C8(CharacterKind, bool b);
s8 Player_80032610(s32 slot, bool arg1);
void Player_LoadPlayerCoords(s32 slot, Vec3* out_vec);
void Player_80032768(s32 slot, Vec3* arg_vec);
void Player_80032828(s32 slot, s32 index, Vec3* arg_vec);
void Player_800328D4(int slot, Vec3* arg_vec);
void Player_80032A04(int slot, Vec3* arg_vec);
void Player_SetPlayerAndEntityFacingDirection(s32 slot, f32 direction);
f32 Player_80032BB0(s32 slot);
void Player_SetScale(s32 slot, f32 scale);
void Player_GetSpawnPlatformPos(s32 slot, Vec3* arg_vec);
void Player_SetSpawnPlatformPos(s32 slot, Vec3* arg_vec);
void Player_GetSomePos(s32 slot, Vec3* arg_vec);
void Player_SetSomePos(s32 slot, Vec3* arg_vec);
s32 Player_80032F30(s32 slot);
void Player_80032FA4(s32 slot, s32 arg);
f32 Player_GetFacingDirection(s32 slot);
void Player_SetFacingDirection(s32 slot, f32 direction);
void Player_SetFacingDirectionConditional(s32 slot, bool b, f32 direction);
u32 Player_GetCostumeId(int slot);
void Player_SetCostumeId(int slot, int costume_id);
u8 Player_GetControllerIndex(int slot);
void Player_SetControllerIndex(int slot, s8 controller_index);
int Player_GetTeam(int slot);
void Player_SetTeam(int slot, s8 unk_color);
int Player_GetPlayerId(int slot);
void Player_SetPlayerId(int slot, int player_id);
int Player_GetCpuLevel(int slot);
void Player_SetPlayerAndEntityCpuLevel(int slot, int cpu_level);
int Player_GetCpuType(int slot);
void Player_SetPlayerAndEntityCpuType(int slot, int cpu_type);
int Player_GetHandicap(int slot);
void Player_SetHandicap(int slot, s8 handicap);
f32 Player_GetUnk50(int slot);
f32 Player_GetAttackRatio(int slot);
void Player_SetAttackRatio(int slot, f32 attack_ratio);
f32 Player_GetDefenseRatio(int slot);
void Player_SetDefenseRatio(int slot, f32 defense_ratio);
f32 Player_GetModelScale(int slot);
void Player_SetModelScale(int slot, f32 model_scale);
s32 Player_GetStocks(int slot);
int Player_GetP1Stock(void);
void Player_SetStocks(int slot, int stocks);
void Player_LoseStock(int slot);
int Player_GetCoins(int slot);
void Player_SetCoins(int slot, int current_coins);
int Player_GetTotalCoins(int slot);
void Player_SetTotalCoins(int slot, int coins);
s32 Player_GetUnk98(s32 slot);
void Player_SetUnk98(s32 slot, s32 unk98);
s32 Player_GetUnk9C(s32 slot);
void Player_SetUnk9C(s32 slot, s32 unk9C);
HSD_GObj* Player_GetEntity(s32 slot);
HSD_GObj* Player_GetEntityAtIndex(int slot, int index);
void Player_SwapTransformedStates(s32 slot, s32 arg1, s32 arg2);
s32 Player_GetDamage(s32 slot);
void Player_SetHUDDamage(s32 slot, s32 arg1);
void Player_SetHPByIndex(s32 slot, s32 arg1, s32 arg2);
int Player_GetOtherStamina(s32 slot);
int Player_GetRemainingHP(s32 slot);
bool Player_GetMoreFlagsBit2(s32 slot);
void Player_SetMoreFlagsBit2(s32 slot, u8 bit2);
bool Player_GetMoreFlagsBit3(s32 slot);
void Player_SetMoreFlagsBit3(s32 slot, u8 bit3);
void Player_SetMoreFlagsBit4(s32 slot, u8 bit4);
bool Player_GetMoreFlagsBit4(s32 slot);
bool Player_GetMoreFlagsBit5(s32 slot);
void Player_SetMoreFlagsBit5(s32 slot, u8 bit5);
bool Player_GetMoreFlagsBit6(s32 slot);
void Player_SetMoreFlagsBit6(s32 slot, u8 bit6);
u8 Player_GetFlagsAEBit0(s32 slot);
s32 Player_GetRemainingHPByIndex(s32 slot, s32 index);
s32 Player_GetFalls(s32 slot);
s32 Player_GetFallsByIndex(s32 slot, s32 index);
void Player_SetFalls(int slot, s32 falls);
void Player_SetFallsByIndex(int slot, enum_t index, s32 falls);
s32 Player_GetKOsByPlayerIndex(int slot, int idx);
void Player_UpdateKOsBySlot(int slot, bool bool_arg, int other_slot);
u32 Player_GetMatchFrameCount(int slot);
void Player_UpdateMatchFrameCount(int slot, bool condition);
u32 Player_GetSuicideCount(int slot);
void Player_SetSuicideCount(s32 slot, u32 suicide_count);
void Player_IncSuicideCount(s32 slot, s32 condition);
bool Player_800353BC(s32 slot);
bool Player_8003544C(s32 slot, bool condition);
void Player_SetFlagsBit0(int slot, bool bit0);
u8 Player_GetNametagSlotID(int slot);
void Player_SetNametagSlotID(int slot, int nametag_slot_id);
s32 Player_GetFlagsBit1(s32 slot);
void Player_SetFlagsBit1(s32 slot);
void Player_UnsetFlagsBit1(int slot);
s32 Player_GetFlagsBit3(s32 slot);
void Player_SetFlagsBit3(s32 slot, u8 bit3);
int Player_GetFlagsBit4(int slot);
u8 Player_GetFlagsBit5(s32 slot); ///< player is metal
void Player_SetFlagsBit5(s32 slot, u8 is_metal); ///< player is metal
u8 Player_GetFlagsBit6(s32 slot);
void Player_SetFlagsBit6(s32 slot, u8 bit6);
u8 Player_GetFlagsBit7(s32 slot);
void Player_SetFlagsBit7(s32 slot, u8 bit7);
bool Player_GetMoreFlagsBit0(s32 slot);
bool Player_GetMoreFlagsBit1(s32 slot);
void Player_SetMoreFlagsBit1(s32 slot, u8 bit1);
s32 Player_GetUnk4D(s32 slot);
void Player_SetUnk4D(s32 slot, s8 unk4D);
u8 Player_GetFlagsAEBit1(s32 slot);

#ifdef BUGFIX
void Player_SetFlagsAEBit1(int slot, u8 bit1);
#else
u8 Player_SetFlagsAEBit1(int slot, u8 bit1);
#endif

int Player_GetUnk4C(s32 slot);
void Player_SetUnk4C(s32 slot, u8 unk4C);
bool Player_80036058(s32 slot);
float Player_800360D8(s32 slot);
void Player_SetStructFunc(s32 slot, void* arg_func);
plActionStats* Player_GetActionStats(int slot);
StaleMoveTable* Player_GetStaleMoveTableIndexPtr(s32 slot);
struct pl_x5EC_t* Player_GetUnk6A8Ptr(int slot);
pl_StaleMoveTableExt_t* Player_GetStaleMoveTableIndexPtr2(s32 slot);
FighterKind Player_80036394(s32 slot);
s32 Player_80036428(s32 slot);
void Player_SetUnk45(s32 slot, int unk45);
u8 Player_GetUnk45(s32 slot);
void Player_UpdateJoystickCountByIndex(s32 slot, s32 index);
s32 Player_GetJoystickCountByIndex(s32 slot, s32 index);
void Player_800366DC(s32 slot, s32 arg1);
void Player_80036790(s32 slot, f32 arg1);
void Player_80036844(s32 slot, s32 arg1);
bool Player_800368F8(int slot);
void Player_80036978(s32 slot, s32 arg1);
void Player_InitOrResetPlayer(s32 slot);
void Player_80036CF0(s32 slot);
void Player_80036D24(s32 slot);
void Player_InitAllPlayers(void);
void Player_80036DA4(void);
void Player_80036DD8(void);
void Player_80036E20(CharacterKind ckind, HSD_Archive* archive, s32 arg2);
s32 Player_80036EA0(s32 slot);
void Player_80036F34(s32 slot, s32 arg1);
void Player_80037054(s32 slot, s32 arg1);
void Player_SetOtherStamina(s32 slot, s32 stamina);
void Player_SetFlagsAEBit0(s32 slot, u8 bit0);
s32 Player_80033BB8(int slot);
/* 4D6470 */ extern pl_804D6470_t* pl_804D6470;

#endif
