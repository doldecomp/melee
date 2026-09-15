#include "__dsp.h"

#include <dolphin/dsp.h>

extern DSPTaskInfo* __DSP_curr_task;

void __DSP_debug_printf(const char* fmt, ...) {}

DSPTaskInfo* __DSPGetCurrentTask(void)
{
    return __DSP_curr_task;
}
