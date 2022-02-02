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
        } byVecName;

        Vec byIndex[3];
    } player_poses;


    /*0x34*/ s32 unk34;  /// maybe this is another Vec?
    /*0x38*/ s32 unk38;
    /*0x3C*/ s32 unk3C;

    /*0x40*/ f32 facing_direction;

    /*0x44*/ s8 costume_id;  // 00 = normal, 01 = red, 02 = blue, 03 = green (reflected in icon immediately)
    /*0x45*/ s8 unk45;
    /*0x46*/ s8 controller_index;
    /*0x47*/ s8 unk47;  /// 00 = red, 01 = blue, 02 = green
    /*0x48*/ s8 player_id;
    /*0x49*/ s8 cpu_level;
    /*0x4A*/ s8 cpu_type;
    /*0x4B*/ s8 handicap;

    /*0x4C*/ s32 unk4C;
    /*0x50*/ f32 unk50;

    /*0x54*/ f32 attack_ratio;
    /*0x58*/ f32 damage_defense_ratio;

    /*0x5C*/ f32 model_scale;
    /*0x60*/ s16 stamina_hp_lost_percent;
    /*0x62*/ s16 starting_stamina;  //Used in modes like Sudden Death to set your starting Percentage. Otherwise Nana's or Sheik's %
    /*0x64*/ s16 stamina_hp;
    /*0x66*/ s16 unk66;

    /*0x68*/ s32 falls;
    /*0x6C*/ s32 nana_falls;

    /*0x70*/ s32 p1_KOs;
    /*0x74*/ s32 p2_KOs;
    /*0x78*/ s32 p3_KOs;
    /*0x7C*/ s32 p4_KOs;
    /*0x80*/ s32 p5_KOs;
    /*0x84*/ s32 p6_KOs;

    /*0x88*/ s32 match_frame_count; // If -1 in zz_0035184, then it's set to MatchInfo->frame_count
    /*0x8C*/ s16 suicide_count;

    /*0x8E*/ s8 stocks;
    /*0x8F*/ s8 unk8F;

    /*0x90*/ s32 current_coins;
    /*0x94*/ s32 total_coins_collected;

    /*0x98*/ s32 unk98;
    /*0x9C*/ s32 unk9C;

    /*0xA0*/ s32 joystick_direction_input_count; // Incremented every time you move the joystick a different direction from neutral.
    /*0xA4*/ s32 unkA4;

    /*0xA8*/ s32 nametag_slot_id;

    /*0xAC*/ s8 flags;

    /*0xAD*/ s8 unkAD;
    /*0xAE*/ s8 unkAE;
    /*0xAF*/ s8 unkAF;

    /*0xB0*/ HSD_GObj* player_entity[2];
    /*0xB4*/ /*void* sub_character_entity;*/ //Used for followers, such as Nana

    /*0xB8*/ s8 unkB8;


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

    /*0xE8*/ s32 total_player_attack_count;
    /*0xEC*/ s32 unkEC;

    /*0xF0*/ u8 buffer[0xDA0];  ///3488 bytes total

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
void Player_800326CC(s32 slot, Vec* arg_vec);
void Player_80032768(s32 slot, Vec* arg_vec);
void Player_80032828(s32 slot, s32 index, Vec* arg_vec);
void Player_800328D4(s32 slot, Vec* arg_vec);
void Player_80032A04(s32 slot, Vec* arg_vec);
void Player_SetFacingDirection(s32 slot, f32 direction);

#endif
