#ifndef _player_h_
#define _player_h_

#include <global.h>

#include <dolphin/types.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>


typedef struct _StaticPlayer
{
    /*0x00*/ s32 player_state;  // 0x02 In-Game (includes dead). 0x00 Otherwise.
    /*0x04*/ s32 player_character; //(External ID)
    /*0x08*/ s32 slot_type; // (0x0000000 is HMN, 0x00000001 is CPU, 0x00000002 is Demo, 0x00000003 n/a)

    /*0x0C*/ u8 transformed[2]; // 0x0001 for normal, 0x0100 for transformed (Probably Zelda/Sheik only)
    /*0x0E*/ s16 unk0E;

    union {
        struct {
            /*0x10-0x1B*/ Vec nametag_pos;  ///Horizontal, Vertical, Depth (floats)
            /*0x1C-0x27*/ Vec transformed_player_pos; 
            /*0x28-0x33*/ Vec spawn_platform_final_pos;
            /*0x34-0x3f*/ Vec some_other_player_pos;
        } byVecName;

        Vec byIndex[4];
    } player_poses;

    /*0x40*/ f32 facing_direction;

    /*0x44*/ u8 costume_id;  // 00 = normal, 01 = red, 02 = blue, 03 = green (reflected in icon immediately)
    /*0x45*/ s8 unk45;
    /*0x46*/ s8 controller_index;
    /*0x47*/ u8 team;  /// 00 = red, 01 = blue, 02 = green
    /*0x48*/ s8 player_id;
    /*0x49*/ s8 cpu_level;
    /*0x4A*/ s8 cpu_type;
    /*0x4B*/ s8 handicap;

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

    /*0x68 - 0x6C*/ s32 falls[2];  /// other index for nana falls

    /*0x70-0x84*/ s32 kos_by_player[6];

    /*0x88*/ u32 match_frame_count; // If -1 in zz_0035184, then it's set to MatchInfo->frame_count
    /*0x8C*/ u16 suicide_count;

    /*0x8E*/ s8 stocks;
    /*0x8F*/ s8 unk8F;

    /*0x90*/ s32 current_coins;
    /*0x94*/ s32 total_coins;

    /*0x98*/ s32 unk98;
    /*0x9C*/ s32 unk9C;

    /*0xA0-A4*/ s32 joystick_direction_input_count[2]; // Incremented every time you move the joystick a different direction from neutral.

    /*0xA8*/ s32 nametag_slot_id;

    /*0xAC*/ struct {
                u8 b0 : 1;
                u8 b1 : 1;
                u8 b2 : 1;
                u8 b3 : 1;
                u8 b4 : 1;
                u8 b5 : 1;
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
    /*0xB4*/ /*void* sub_character_entity;*/ //Used for followers, such as Nana

    /*0xB8*/ void (*struct_func) (s32 slot);


    /*0xBC*/ s32 stale_move_table_current_write_index; // Zero-Indexed. Rolls over after 9. Increments after each write.


    /*0xC0*/ s32 stale_move_index_0;  //1st Short is the move ID,  2nd Short is the # of action states that character has gone through this game
    /*0xC4*/ s32 stale_move_index_1;
    /*0xC8*/ s32 stale_move_index_2;
    /*0xCC*/ s32 stale_move_index_3;
    /*0xD0*/ s32 stale_move_index_4;
    /*0xD4*/ s32 stale_move_index_5;
    /*0xD8*/ s32 stale_move_index_6;
    /*0xDC*/ s32 stale_move_index_7;
    /*0xE0*/ s32 stale_move_index_8;
    /*0xE4*/ s32 stale_move_index_9;

    /*0xE8*/ s32 total_attack_count;
    /*0xEC*/ s32 unkEC;

    /*0xF0*/ u8 buffer[0x5B8];
    /*0x6A8*/ s32 unk6A8;
    /*0x6AC*/ u8 more_buffer[0x7E4];

} StaticPlayer;

StaticPlayer* Player_GetPtrForSlot(s32 slot);
void Player_80031790(s32 slot);
void Player_80031848(s32 slot);
void Player_80031900();
BOOL Player_800319C4(s32 slot, BOOL arg1);
void Player_80031AD0(s32 slot);
void Player_80031CB0(s32 id, s32 slot);
void Player_80031D2C(s32 id, s32 slot);
void Player_80031DA8(s32 param_1, s32 param_2);
void Player_80031DC8(void func_arg(s32, s32));
void Player_80031EBC(s32 slot);
void Player_80031FB0(s32 slot, s32 entity_index);
void Player_80032070(s32 slot, BOOL bool_arg);
void Player_8003219C(s32 slot);
BOOL Player_8003221C(s32 slot);
s32 Player_GetPlayerState(s32 slot);
s32 Player_GetPlayerCharacter(s32 slot);
void Player_SetPlayerCharacter(s32 slot, s32 value);
s32 Player_GetPlayerSlotType(s32 slot);
s32 Player_8003248C(s32 slot, BOOL arg1);
void Player_SetSlottype(s32 slot, s32 value);
s8 Player_800325C8(s32 slot, BOOL b);
s8 Player_80032610(s32 slot, BOOL arg1);
void Player_LoadPlayerCoords(s32 slot, Vec* out_vec);
void Player_80032768(s32 slot, Vec* arg_vec);
void Player_80032828(s32 slot, s32 index, Vec* arg_vec);
void Player_800328D4(s32 slot, Vec* arg_vec);
void Player_80032A04(s32 slot, Vec* arg_vec);
void Player_SetPlayerAndEntityFacingDirection(s32 slot, f32 direction);
f32 Player_80032BB0(s32 slot);
void Player_SetScale(s32 slot, f32 scale);
void Player_GetSpawnPlatformPos(s32 slot, Vec* arg_vec);
void Player_SetSpawnPlatformPos(s32 slot, Vec* arg_vec);
void Player_GetSomePos(s32 slot, Vec* arg_vec);
void Player_SetSomePos(s32 slot, Vec* arg_vec);
s32 Player_80032F30(s32 slot);
void Player_80032FA4(s32 slot, s32 arg);
f32 Player_GetFacingDirection(s32 slot);
void Player_SetFacingDirection(s32 slot, f32 direction);
void Player_SetFacingDirectionConditional(s32 slot, BOOL b, f32 direction);
u32 Player_GetCostumeId(s32 slot);
void Player_SetCostumeId(s32 slot, s8 costume_id);
u8 Player_GetControllerIndex(s32 slot);
void Player_SetControllerIndex(s32 slot, s8 controller_index);
s8 Player_GetTeam(s32 slot);
void Player_SetTeam(s32 slot, s8 unk_color);
s8 Player_GetPlayerId(s32 slot);
void Player_SetPlayerId(s32 slot, s8 player_id);
s8 Player_GetCpuLevel(s32 slot);
void Player_SetPlayerAndEntityCpuLevel(s32 slot, s8 cpu_level);
s8 Player_GetCpuType(s32 slot);
void Player_SetPlayerAndEntityCpuType(s32 slot, s8 cpu_type);
s8 Player_GetHandicap(s32 slot);
void Player_SetHandicap(s32 slot, s8 handicap);
f32 Player_GetUnk50(s32 slot);
f32 Player_GetAttackRatio(s32 slot);
void Player_SetAttackRatio(s32 slot, f32 attack_ratio);
f32 Player_GetDefenseRatio(s32 slot);
void Player_SetDefenseRatio(s32 slot, f32 defense_ratio);
f32 Player_GetModelScale(s32 slot);
void Player_SetModelScale(s32 slot, f32 model_scale);
s32 Player_GetStocks(s32 slot);
s32 Player_GetP1Stock();
void Player_SetStocks(s32 slot, s32 stocks);
void Player_LoseStock(s32 slot);
s32 Player_GetCoins(s32 slot);
void Player_SetCoins(s32 slot, s32 current_coins);
s32 Player_GetTotalCoins(s32 slot);
void Player_SetTotalCoins(s32 slot, s32 coins);
s32 Player_GetUnk98(s32 slot);
void Player_SetUnk98(s32 slot, s32 unk98);
s32 Player_GetUnk9C(s32 slot);
void Player_SetUnk9C(s32 slot, s32 unk9C);
HSD_GObj* Player_GetEntity(s32 slot);
HSD_GObj* Player_GetEntityAtIndex(s32 slot, s32 index);
void Player_SwapTransformedStates(s32 slot, s32 arg1, s32 arg2);
s32 Player_GetDamage(s32 slot);
void Player_SetHUDDamage(s32 slot,s32 arg1);
void Player_SetHPByIndex(s32 slot, s32 arg1, s32 arg2);
s16 Player_GetOtherStamina(s32 slot);
u32 Player_GetRemainingHP(s32 slot);
u8 Player_GetMoreFlagsBit2(s32 slot);
void Player_SetMoreFlagsBit2(s32 slot, u8 bit2);
s32 Player_GetMoreFlagsBit3(s32 slot);
void Player_SetMoreFlagsBit3(s32 slot, u8 bit3);
void Player_SetMoreFlagsBit4(s32 slot, u8 bit4);
s32 Player_GetMoreFlagsBit4(s32 slot);
u8 Player_GetMoreFlagsBit5(s32 slot);
void Player_SetMoreFlagsBit5(s32 slot, u8 bit5);
u8 Player_GetMoreFlagsBit6(s32 slot);
void Player_SetMoreFlagsBit6(s32 slot, u8 bit6);
u8 Player_GetFlagsAEBit0(s32 slot);
u32 Player_GetRemainingHPByIndex(s32 slot, s32 index);
s32 Player_GetFalls(s32 slot);
s32 Player_GetFallsByIndex(s32 slot, s32 index);
void Player_SetFalls(s32 slot, s32 falls);
void Player_SetFallsByIndex(s32 slot, s32 index, s32 falls);
s32 Player_GetKOsByPlayerIndex(s32 slot, s32 index);
void Player_UpdateKOsBySlot(s32 slot, BOOL bool_arg, s32 other_slot);
u32 Player_GetMatchFrameCount(s32 slot);
void Player_UpdateMatchFrameCount(s32 slot, BOOL condition);
u16 Player_GetSuicideCount(s32 slot);
void Player_SetSuicideCount(s32 slot, u32 suicide_count);
void Player_IncSuicideCount(s32 slot, s32 condition);
BOOL Player_800353BC(s32 slot);
BOOL Player_8003544C(s32 slot, BOOL condition);
void Player_SetFlagsBit0(s32 slot, s32 bit0);
s8 Player_GetNametagSlotID(s32 slot);
void Player_SetNametagSlotID(s32 slot, s32 nametag_slot_id);
s32 Player_GetFlagsBit1(s32 slot);
void Player_SetFlagsBit1(s32 slot);
void Player_UnsetFlagsBit1(s32 slot);
s32 Player_GetFlagsBit3(s32 slot);
void Player_SetFlagsBit3(s32 slot, u8 bit3);
u8 Player_GetFlagsBit4(s32 slot);
u8 Player_GetFlagsBit5(s32 slot);
void Player_SetFlagsBit5(s32 slot, u8 bit5);
u8 Player_GetFlagsBit6(s32 slot);
void Player_SetFlagsBit6(s32 slot, u8 bit6);
u8 Player_GetFlagsBit7(s32 slot);
void Player_SetFlagsBit7(s32 slot, u8 bit7);
u8 Player_GetMoreFlagsBit0(s32 slot);
u8 Player_GetMoreFlagsBit1(s32 slot);
void Player_SetMoreFlagsBit1(s32 slot, u8 bit1);
s32 Player_GetUnk4D(s32 slot);
void Player_SetUnk4D(s32 slot, s8 unk4D);
u8 Player_GetFlagsAEBit1(s32 slot);
u8 Player_SetFlagsAEBit1(s32 slot, u8 bit1); ///actually returns void
u8 Player_GetUnk4C(s32 slot);
void Player_SetUnk4C(s32 slot, u8 unk4C);
void Player_80036058(s32 slot);
void Player_800360D8(s32 slot);
void Player_SetStructFunc(s32 slot, void* arg_func);
s32* Player_GetTotalAttackCountPtr(s32 slot);
s32* Player_GetStaleMoveTableIndexPtr(s32 slot);
s32* Player_GetUnk6A8Ptr(s32 slot);
s32* Player_GetStaleMoveTableIndexPtr2(s32 slot);
s32 Player_80036394(s32 slot);
s32 Player_80036428(s32 slot);
void Player_SetUnk45(s32 slot, s8 unk45);
u8 Player_GetUnk45(s32 slot);
void Player_UpdateJoystickCountByIndex(s32 slot, s32 index);
s32 Player_GetJoystickCountByIndex(s32 slot, s32 index);
void Player_800366DC(s32 slot, s32 arg1);
void Player_80036790(s32 slot, f32 arg1);
void Player_80036844(s32 slot, s32 arg1);
void Player_800368F8(s32 slot);
void Player_80036978(s32 slot, s32 arg1);
void Player_InitOrResetPlayer(s32 slot);
void Player_80036CF0(s32 slot);
void Player_80036D24(s32 slot);
void Player_InitAllPlayers();
void Player_80036DA4();
void Player_80036DD8();
void Player_80036E20(s32 arg0, s32 arg1, s32 arg2);
s32 Player_80036EA0(s32 slot);
void Player_80036F34(s32 slot, s32 arg1);
void Player_80037054(s32 slot, s32 arg1);

#endif
