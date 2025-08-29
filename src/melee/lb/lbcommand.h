#ifndef _lbcommands_h_
#define _lbcommands_h_

#include <platform.h>

#include "lb/forward.h"

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
bool Command_Execute(CommandInfo* info, u32 command);

#endif
