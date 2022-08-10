#include <melee/lb/lbcommand.h>

extern const f64 lbl_804D79E0;

void (*lbl_803B9840[16])(CommandInfo*) = {
                            Command_00, Command_01, Command_02, Command_03, Command_04, 
                            Command_05, Command_06, Command_07, Command_08, Command_09, 
                            NULL, NULL, NULL, NULL, NULL, NULL
                         };

// Reset
void Command_00(CommandInfo* info)
{
    info->u.data_position = 0;
}

// SynchronousTimer
void Command_01(CommandInfo* info)
{
    info->timer += *info->u.data_position & 0x3ffffff;
    info->u.data_position += 1;
}

// AsynchronousTimer
void Command_02(CommandInfo* info)
{
    info->timer = (*info->u.data_position & 0x3ffffff) - info->frame_count;
    info->u.data_position += 1;
}

// SetLoop
void Command_03(CommandInfo* info)
{
    info->event_return[info->loop_count++] = info->u.data_position + 1;
    info->event_return[info->loop_count++] = (u32*)(*info->u.data_position & 0x3ffffff);
    info->u.data_position += 1;
}

// Execute Loop
void Command_04(CommandInfo* info)
{
    u32* ptr = (u32*)info;
    ptr[info->loop_count + 3]-=1;

    if ((s32)info->event_return[info->loop_count-1]) {
        info->u.data_position = &info->u.Command_04.ptr[info->loop_count][0];
        return;
    }

    info->u.data_position += 1;
    info->loop_count-=2;
}

// Subroutine
void Command_05(CommandInfo* info) {
    info->u.data_position = info->u.data_position + 1;
    info->event_return[info->loop_count++] = info->u.data_position + 1;
    info->u.data_position = (u32*)(*info->u.data_position);
}

// Return
void Command_06(CommandInfo* info) {
    info->u.data_position = info->event_return[info->loop_count -= 1];
}

// GoTo
void Command_07(CommandInfo* info) {
    info->u.data_position += 1;
    info->u.data_position = (u32*)*info->u.data_position;
}

// SetTimerAnimation
void Command_08(CommandInfo* info) {
    info->u.data_position += 1;
    info->timer = FLT_MAX;
}

void Command_09(CommandInfo* info) {
    Command_09_Struct* cmd = info->u.Command_09;
    func_80021C48(cmd->param_1, cmd->param_2);
    info->u.data_position += 1;
}

BOOL Command_Execute(CommandInfo* info, u32 command) {
    if (command < 10) {
        lbl_803B9840[command](info);
        return TRUE;
    }
    return FALSE;
}
