#ifndef _player_h_
#define _player_h_

#include <global.h>

#include <dolphin/types.h>

typedef struct _StaticPlayer
{
    u8 data[0xE90];
} StaticPlayer;

StaticPlayer* Player_GetPtrForSlot(s32 slot);
void Player_80031790(s32 slot);
void Player_80031848(s32 slot);
void Player_80031900(s32 slot);
BOOL Player_800319C4(s32 slot, BOOL param_2);
void Player_80031AD0(s32 slot);
void Player_80031CB0(s32 id, s32 slot);
void Player_80031D2C(s32 id, s32 slot);
void Player_80031DA8(s32 param_1, s32 param_2);

#endif
