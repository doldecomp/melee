#ifndef _lbcommands_h_
#define _lbcommands_h_

#include <global.h>

#include <dolphin/types.h>

typedef struct _CommandInfo {
    f32 timer; //0x00
    f32 frame_count; //0x04
    u32* data_position; //0x08
    u32 loop_count; //0x0C
    u32* event_return[4]; //0x10 - Array Size is purely made-up for now
    u32 loop_count_dup; //0x14
    u32 unk_x18; //0x18
} CommandInfo;

void Command_00(CommandInfo* info);
void Command_01(CommandInfo* info);
void Command_02(CommandInfo* info);
void Command_03(CommandInfo* info);
void Command_04(CommandInfo* info);
void Command_05(CommandInfo* info);
void Command_14(CommandInfo* info);
void Command_06(CommandInfo* info);
void Command_07(CommandInfo* info);
void Command_08(CommandInfo* info);
void Command_09(CommandInfo* info);
BOOL Command_Execute(CommandInfo* info, u32 command);

#endif
