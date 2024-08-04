#include <dolphin/dsp.h>

#include "__dsp.h"

// this is duplicated from dsp.c
DSPTaskInfo *__DSP_first_task;
DSPTaskInfo *__DSP_last_task;
DSPTaskInfo *__DSP_curr_task;
DSPTaskInfo *__DSP_tmp_task;

void __DSP_debug_printf(const char *fmt, ...) {}

DSPTaskInfo *__DSPGetCurrentTask(void)
{
    return __DSP_curr_task;
}
