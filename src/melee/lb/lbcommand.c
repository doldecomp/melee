#include "lbcommand.h"

#include "inlines.h"
#include "lb_0219.h"
#include "types.h"

void (*lbCommand_803B9840[16])(CommandInfo*) = {
    Command_00, Command_01, Command_02, Command_03, Command_04, Command_05,
    Command_06, Command_07, Command_08, Command_09, NULL,       NULL,
    NULL,       NULL,       NULL,       NULL
};

/// Reset
void Command_00(CommandInfo* info)
{
    info->u = NULL;
}

/// SynchronousTimer
void Command_01(CommandInfo* info)
{
    info->timer += info->u->Command_00.value;
    NEXT_CMD(info);
}

/// AsynchronousTimer
void Command_02(CommandInfo* info)
{
    info->timer = info->u->Command_02.value - info->frame_count;
    NEXT_CMD(info);
}

/// SetLoop
void Command_03(CommandInfo* info)
{
    info->event_return[info->loop_count++].command = info->u + 1;
    info->event_return[info->loop_count++].count = info->u->Command_03.value;
    NEXT_CMD(info);
}

/// Execute Loop
void Command_04(CommandInfo* info)
{
    info->event_return[info->loop_count - 1].count -= 1;

    if (info->event_return[info->loop_count - 1].count) {
        info->u = info->event_return[info->loop_count - 2].command;
        return;
    }
    NEXT_CMD(info);
    info->loop_count -= 2;
}

/// Subroutine
void Command_05(CommandInfo* info)
{
    NEXT_CMD(info);
    info->event_return[info->loop_count++].command = info->u + 1;
    info->u = info->u->Command_05.ptr;
}

/// Return
void Command_06(CommandInfo* info)
{
    info->u = info->event_return[info->loop_count -= 1].command;
}

/// Goto
void Command_07(CommandInfo* info)
{
    NEXT_CMD(info);
    info->u = info->u->Command_07.ptr;
}

/// SetTimerAnimation
void Command_08(CommandInfo* info)
{
    NEXT_CMD(info);
    info->timer = F32_MAX;
}

void Command_09(CommandInfo* info)
{
    lbBgFlash_80021C48(info->u->Command_09.param_1,
                       info->u->Command_09.param_2);
    NEXT_CMD(info);
}

bool Command_Execute(CommandInfo* info, u32 command)
{
    if (command < 10) {
        lbCommand_803B9840[command](info);
        return true;
    }
    return false;
}
