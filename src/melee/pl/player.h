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

#endif
