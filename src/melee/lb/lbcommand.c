#include "lbcommand.h"

extern const f64 lbl_804D79E0;

// Reset
void Command_00(CommandInfo* info)
{
    info->data_position = 0;
}

//Set Timer
void Command_04(CommandInfo* info)
{
    info->timer += *info->data_position & 0x3ffffff;
    info->data_position += 1;
}

//Adjust Timer
void Command_08(CommandInfo* info)
{
    info->timer = (*info->data_position & 0x3ffffff) - info->frame_count;
    info->data_position += 1;
}
