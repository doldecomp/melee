#include "__dsp.h"

#include <dolphin.h>
#include <stddef.h>
#include <dolphin/hw_regs.h>

#define BUILD_DATE "Sep  8 2001"
#if DEBUG
#define BUILD_TIME "01:48:51"
#else
#define BUILD_TIME "01:51:48"
#endif

u32 DSPCheckMailToDSP(void)
{
    return (__DSPRegs[0] & (1 << 15)) >> 15;
}

u32 DSPCheckMailFromDSP(void)
{
    return (__DSPRegs[2] & (1 << 15)) >> 15;
}

u32 DSPReadCPUToDSPMbox(void)
{
    return (__DSPRegs[0] << 16) | __DSPRegs[1];
}

u32 DSPReadMailFromDSP(void)
{
    return (__DSPRegs[2] << 16) | __DSPRegs[3];
}

void DSPSendMailToDSP(u32 mail)
{
    __DSPRegs[0] = mail >> 16;
    __DSPRegs[1] = mail & 0xFFFF;
}

void DSPAssertInt(void)
{
    BOOL old;
    u16 tmp;

    old = OSDisableInterrupts();
    tmp = __DSPRegs[5];
    tmp = (tmp & ~0xA8) | 2;
    __DSPRegs[5] = tmp;
    OSRestoreInterrupts(old);
}

static int __DSP_init_flag;
extern DSPTaskInfo* __DSP_curr_task;
extern DSPTaskInfo* __DSP_last_task;
extern DSPTaskInfo* __DSP_first_task;
extern DSPTaskInfo* __DSP_tmp_task;

void DSPInit(void)
{
    BOOL old;
    u16 tmp;

    __DSP_debug_printf("DSPInit(): Build Date: %s %s\n", BUILD_DATE,
                       BUILD_TIME);

    if (__DSP_init_flag == 1) {
        return;
    }

    old = OSDisableInterrupts();
    __OSSetInterruptHandler(7, __DSPHandler);
    __OSUnmaskInterrupts(OS_INTERRUPTMASK_DSP_DSP);

    tmp = __DSPRegs[5];
    tmp = (tmp & ~0xA8) | 0x800;
    __DSPRegs[5] = tmp;

    tmp = __DSPRegs[5];
    __DSPRegs[5] = tmp = tmp & ~0xAC;

    __DSP_first_task = __DSP_last_task = __DSP_curr_task = __DSP_tmp_task =
        NULL;
    __DSP_init_flag = 1;

    OSRestoreInterrupts(old);
}

BOOL DSPCheckInit(void)
{
    return __DSP_init_flag;
}

void DSPReset(void)
{
    BOOL old;
    u16 tmp;

    old = OSDisableInterrupts();
    tmp = __DSPRegs[5];
    tmp = (tmp & ~0xA8) | 0x800 | 1;
    __DSPRegs[5] = tmp;
    __DSP_init_flag = 0;
    OSRestoreInterrupts(old);
}

void DSPHalt(void)
{
    BOOL old;
    u16 tmp;

    old = OSDisableInterrupts();
    tmp = __DSPRegs[5];
    tmp = (tmp & ~0xA8) | 4;
    __DSPRegs[5] = tmp;
    OSRestoreInterrupts(old);
}

void DSPUnhalt(void)
{
    BOOL old;
    u16 tmp;

    old = OSDisableInterrupts();
    tmp = __DSPRegs[5];
    tmp = (tmp & ~0xAC);
    __DSPRegs[5] = tmp;
    OSRestoreInterrupts(old);
}

u32 DSPGetDMAStatus(void)
{
    return (__DSPRegs[5] & (1 << 9));
}

DSPTaskInfo* DSPAddTask(DSPTaskInfo* task)
{
    BOOL old;

    ASSERTMSGLINE(0x21E, __DSP_init_flag == 1,
                  "DSPAddTask(): DSP driver not initialized!\n");

    old = OSDisableInterrupts();

    __DSP_insert_task(task);
    task->state = 0;
    task->flags = 1;

    OSRestoreInterrupts(old);
    if (task == __DSP_first_task) {
        __DSP_boot_task(task);
    }
    return task;
}

DSPTaskInfo* DSPCancelTask(DSPTaskInfo* task)
{
    BOOL old;

    ASSERTMSGLINE(0x242, __DSP_init_flag == 1,
                  "DSPCancelTask(): DSP driver not initialized!\n");

    old = OSDisableInterrupts();

    task->flags |= 2;

    OSRestoreInterrupts(old);
    return task;
}

extern DSPTaskInfo* __DSP_rude_task;
extern int __DSP_rude_task_pending;

DSPTaskInfo* DSPAssertTask(DSPTaskInfo* task)
{
    s32 old;

    ASSERTMSGLINE(0x261, __DSP_init_flag == 1,
                  "DSPAssertTask(): DSP driver not initialized!\n");
    ASSERTMSGLINE(
        0x262, task->flags & 1,
        "DSPAssertTask(): Specified task not in active task list!\n");

    old = OSDisableInterrupts();

    if (__DSP_curr_task == task) {
        __DSP_rude_task = task;
        __DSP_rude_task_pending = 1;
        OSRestoreInterrupts(old);
        return task;
    }
    if (task->priority < __DSP_curr_task->priority) {
        __DSP_rude_task = task;
        __DSP_rude_task_pending = 1;
        if (__DSP_curr_task->state == 1) {
            DSPAssertInt();
        }
        OSRestoreInterrupts(old);
        return task;
    }
    OSRestoreInterrupts(old);
    return NULL;
}
