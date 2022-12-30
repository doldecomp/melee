#include <dolphin/dsp/dsp.h>

BOOL __DSP_init_flag;

extern DSPTaskInfo* __DSP_curr_task;
extern DSPTaskInfo* __DSP_first_task;
extern DSPTaskInfo* __DSP_last_task;
extern DSPTaskInfo* __DSP_tmp_task;
extern DSPTaskInfo* __DSP_rude_task;
extern BOOL __DSP_rude_task_pending;

u32 DSPCheckMailToDSP(void)
{
    return (__DSPRegs[0] >> 15) & 1;
}

u32 DSPCheckMailFromDSP(void)
{
    return (__DSPRegs[2] >> 15) & 1;
}

u32 DSPReadMailFromDSP(void)
{
    return (__DSPRegs[2] << 16) | __DSPRegs[3];
}

void DSPSendMailToDSP(u32 mail)
{
    __DSPRegs[0] = mail >> 16;
    __DSPRegs[1] = mail & 0xffff;
}

void DSPInit(void)
{
    BOOL intr;
    u16 tmp;

    __DSP_debug_printf("DSPInit(): Build Date: %s %s\n", "Sep  8 2001",
                       "01:51:48"); // __DATE__, __TIME__

    if (__DSP_init_flag == TRUE) {
        return;
    }

    intr = OSDisableInterrupts();

    __OSSetInterruptHandler(OS_INTR_DSP_DSP, __DSPHandler);
    __OSUnmaskInterrupts(0x80000000U >> OS_INTR_DSP_DSP);

    __DSPRegs[5] = (__DSPRegs[5] & ~0xA8) | 0x0800;
    tmp = __DSPRegs[5];
    __DSPRegs[5] = tmp & ~0xAC;

    __DSP_tmp_task = NULL;
    __DSP_curr_task = NULL;
    __DSP_last_task = NULL;
    __DSP_first_task = NULL;
    __DSP_init_flag = TRUE;

    OSRestoreInterrupts(intr);
}

BOOL DSPCheckInit(void)
{
    return __DSP_init_flag;
}

DSPTaskInfo* DSPAddTask(DSPTaskInfo* task)
{
    BOOL intrEnabled = OSDisableInterrupts();

    __DSP_insert_task(task);
    task->state = 0;
    task->flags = 1;

    OSRestoreInterrupts(intrEnabled);
    if (task == __DSP_first_task) {
        __DSP_boot_task(task);
    }
    return task;
}

// Unknown DSP command
// Similar to DSPReset, DSPHalt
void DSPSomething(void)
{
    BOOL enabled = OSDisableInterrupts();
    __DSPRegs[5] = (__DSPRegs[5] & ~0xA8) | 2;
    OSRestoreInterrupts(enabled);
}

void* DSPAssertTask(DSPTaskInfo* task)
{
    BOOL enabled = OSDisableInterrupts();
    if (__DSP_curr_task == task) {
        __DSP_rude_task = task;
        __DSP_rude_task_pending = 1;
        OSRestoreInterrupts(enabled);
        return task;
    }
    if (task->priority < __DSP_curr_task->priority) {
        __DSP_rude_task = task;
        __DSP_rude_task_pending = 1;
        if (__DSP_curr_task->state == 1) {
            DSPSomething();
        }
        OSRestoreInterrupts(enabled);
        return task;
    }
    OSRestoreInterrupts(enabled);
    return NULL;
}
