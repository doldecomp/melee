#ifndef _lbcommands_h_
#define _lbcommands_h_

#include "dolphin/types.h"

typedef struct _CommandInfo {
    f32 timer; //0x00
    f32 frame_count; //0x04
    u32* data_position; //0x08
    u32 loop_count; //0x0C
    u32* unk_x10; //0x10
    u32 loop_count_dup; //0x14
    u32 unk_x18; //0x18
} CommandInfo;

void Command_00(CommandInfo* info);
void Command_04(CommandInfo* info);
void Command_08(CommandInfo* info);

#endif
