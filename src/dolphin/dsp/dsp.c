#include <dolphin/dsp/dsp.h>

BOOL __DSP_init_flag;

extern void* __DSP_curr_task;
extern void* __DSP_first_task;
extern void* __DSP_last_task;
extern void* __DSP_tmp_task;

extern char lbl_80400C08[]; //"DSPInit(): Build Date: %s %s\n"

u32 DSPCheckMailToDSP(void)
{
    return (HW_REG(0xCC005000, u16) >> 15) & 1;
}

u32 DSPCheckMailFromDSP(void)
{
    return (HW_REG(0xCC005004, u16) >> 15) & 1;
    ;
}

u32 DSPReadMailFromDSP(void)
{
    return (__DSPRegs[2] << 16) | __DSPRegs[3];
}

void DSPSendMailToDSP(u32 mail)
{
    __DSPRegs[0] = (u16) ((mail >> 16) & 0xffff);
    __DSPRegs[1] = (u16) (mail & 0xffff);
}

void DSPInit(void)
{
    BOOL intr;
    u16 tmp;

    __DSP_debug_printf("DSPInit(): Build Date: %s %s\n", "Sep  8 2001", "01:51:48"); // __DATE__, __TIME__

    if (TRUE == __DSP_init_flag) {
        return;
    }

    intr = OSDisableInterrupts();

    __OSSetInterruptHandler(7, __DSPHandler);
    __OSUnmaskInterrupts(0x80000000u >> 7);

    tmp = __DSPRegs[5];
    tmp = (u16) ((tmp & ~(0xA8)) | 0x0800);
    __DSPRegs[5] = tmp;

    tmp = __DSPRegs[5];
    tmp = (u16) (tmp & ~(0xAC));
    __DSPRegs[5] = tmp;

    __DSP_first_task = __DSP_last_task = __DSP_curr_task = __DSP_tmp_task = NULL;

    __DSP_init_flag = TRUE;

    OSRestoreInterrupts(intr);
}

BOOL DSPCheckInit(void)
{
    return (__DSP_init_flag);
}

DSPTaskInfo* DSPAddTask(DSPTaskInfo* task)
{
    BOOL intrEnabled = OSDisableInterrupts();

    __DSP_insert_task(task);
    task->state = 0;
    task->flags = 1;

    OSRestoreInterrupts(intrEnabled);
    if (task == __DSP_first_task)
        __DSP_boot_task(task);
    return task;
}
