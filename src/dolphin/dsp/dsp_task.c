#include <dolphin/dsp/dsp.h>
#include <dolphin/os/OSInterrupt.h>
#include <Runtime/platform.h>
#include <stddef.h>

DSPTaskInfo* __DSP_curr_task;
DSPTaskInfo* __DSP_first_task;
DSPTaskInfo* __DSP_last_task;
DSPTaskInfo* __DSP_tmp_task;
DSPTaskInfo* __DSP_rude_task;
bool __DSP_rude_task_pending;

void __DSPHandler(__OSInterrupt intr, OSContext* ctx)
{
    u8 pad[8];
    OSContext sp10;
    u32 msg;
    u16 temp;

    temp = __DSPRegs[5];
    __DSPRegs[5] = (temp & -41) | 0x80;
    OSClearContext(&sp10);
    OSSetCurrentContext(&sp10);
    while (DSPCheckMailFromDSP() == 0)
        continue;
    msg = DSPReadMailFromDSP();
    if ((__DSP_curr_task->flags & (1 << 1)) && msg == 0xDCD10002)
        msg = 0xDCD10003;
    switch (msg) {
    case 0xDCD10000:
        __DSP_curr_task->state = 1;
        if (__DSP_curr_task->init_cb != NULL)
            __DSP_curr_task->init_cb(__DSP_curr_task);
        break;
    case 0xDCD10001:
        __DSP_curr_task->state = 1;
        if (__DSP_curr_task->res_cb != NULL)
            __DSP_curr_task->res_cb(__DSP_curr_task);
        break;
    case 0xDCD10002:
        if (__DSP_rude_task_pending) {
            if (__DSP_curr_task == __DSP_rude_task) {
                DSPSendMailToDSP(0xCDD10003);
                while (DSPCheckMailToDSP() != 0)
                    continue;
                __DSP_rude_task = NULL;
                __DSP_rude_task_pending = false;
                if (__DSP_curr_task->res_cb != NULL)
                    __DSP_curr_task->res_cb(__DSP_curr_task);
            } else {
                DSPSendMailToDSP(0xCDD10001);
                while (DSPCheckMailToDSP() != 0)
                    continue;
                __DSP_exec_task(__DSP_curr_task, __DSP_rude_task);
                __DSP_curr_task->state = 2;
                __DSP_curr_task = __DSP_rude_task;
                __DSP_rude_task_pending = false;
                __DSP_rude_task = NULL;
            }
        } else {
            if (__DSP_curr_task->next == NULL) {
                if (__DSP_curr_task == __DSP_first_task) {
                    DSPSendMailToDSP(0xCDD10003);
                    while (DSPCheckMailToDSP() != 0)
                        continue;
                    if (__DSP_curr_task->res_cb != NULL)
                        __DSP_curr_task->res_cb(__DSP_curr_task);
                } else {
                    DSPSendMailToDSP(0xCDD10001);
                    while (DSPCheckMailToDSP() != 0)
                        continue;
                    __DSP_exec_task(__DSP_curr_task, __DSP_first_task);
                    __DSP_curr_task->state = 2;
                    __DSP_curr_task = __DSP_first_task;
                }
            } else {
                DSPSendMailToDSP(0xCDD10001);
                while (DSPCheckMailToDSP() != 0)
                    continue;
                __DSP_exec_task(__DSP_curr_task, __DSP_curr_task->next);
                __DSP_curr_task->state = 2;
                __DSP_curr_task = __DSP_curr_task->next;
            }
        }
        break;
    case 0xDCD10003:
        if (__DSP_rude_task_pending) {
            if (__DSP_curr_task->done_cb != NULL)
                __DSP_curr_task->done_cb(__DSP_curr_task);
            DSPSendMailToDSP(0xCDD10001);
            while (DSPCheckMailToDSP() != 0)
                continue;
            __DSP_exec_task(NULL, __DSP_rude_task);
            __DSP_remove_task(__DSP_curr_task);
            __DSP_curr_task = __DSP_rude_task;
            __DSP_rude_task_pending = false;
            __DSP_rude_task = NULL;
        } else {
            if (__DSP_curr_task->next == NULL) {
                if (__DSP_curr_task == __DSP_first_task) {
                    if (__DSP_curr_task->done_cb != NULL)
                        __DSP_curr_task->done_cb(__DSP_curr_task);
                    DSPSendMailToDSP(0xCDD10002);
                    while (DSPCheckMailToDSP() != 0)
                        continue;
                    __DSP_curr_task->state = 3;
                    __DSP_remove_task(__DSP_curr_task);
                } else {
                    if (__DSP_curr_task->done_cb != NULL)
                        __DSP_curr_task->done_cb(__DSP_curr_task);
                    DSPSendMailToDSP(0xCDD10001);
                    while (DSPCheckMailToDSP() != 0)
                        continue;
                    __DSP_curr_task->state = 3;
                    __DSP_exec_task(NULL, __DSP_first_task);
                    __DSP_curr_task = __DSP_first_task;
                    __DSP_remove_task(__DSP_last_task);
                }
            } else {
                if (__DSP_curr_task->done_cb != NULL)
                    __DSP_curr_task->done_cb(__DSP_curr_task);
                DSPSendMailToDSP(0xCDD10001);
                while (DSPCheckMailToDSP() != 0)
                    continue;
                __DSP_curr_task->state = 3;
                __DSP_exec_task(NULL, __DSP_curr_task->next);
                __DSP_curr_task = __DSP_curr_task->next;
                __DSP_remove_task(__DSP_curr_task->prev);
            }
        }
        break;
    case 0xDCD10004:
        if (__DSP_curr_task->req_cb != NULL)
            __DSP_curr_task->req_cb(__DSP_curr_task);
        break;
    }
    OSClearContext(&sp10);
    OSSetCurrentContext(ctx);
}

void __DSP_exec_task(DSPTaskInfo* a, DSPTaskInfo* b)
{
    if (a != NULL) {
        DSPSendMailToDSP((u32) a->dram_mmem_addr);
        while (DSPCheckMailToDSP() != 0)
            continue;
        DSPSendMailToDSP(a->dram_length);
        while (DSPCheckMailToDSP() != 0)
            continue;
        DSPSendMailToDSP(a->dram_addr);
        while (DSPCheckMailToDSP() != 0)
            continue;
    } else {
        DSPSendMailToDSP(0);
        while (DSPCheckMailToDSP() != 0)
            continue;
        DSPSendMailToDSP(0);
        while (DSPCheckMailToDSP() != 0)
            continue;
        DSPSendMailToDSP(0);
        while (DSPCheckMailToDSP() != 0)
            continue;
    }
    DSPSendMailToDSP((u32) b->iram_mmem_addr);
    while (DSPCheckMailToDSP() != 0)
        continue;
    DSPSendMailToDSP(b->iram_length);
    while (DSPCheckMailToDSP() != 0)
        continue;
    DSPSendMailToDSP(b->iram_addr);
    while (DSPCheckMailToDSP() != 0)
        continue;
    if (b->state == 0) {
        DSPSendMailToDSP(b->dsp_init_vector);
        while (DSPCheckMailToDSP() != 0)
            continue;
        DSPSendMailToDSP(0);
        while (DSPCheckMailToDSP() != 0)
            continue;
        DSPSendMailToDSP(0);
        while (DSPCheckMailToDSP() != 0)
            continue;
        DSPSendMailToDSP(0);
        while (DSPCheckMailToDSP() != 0)
            continue;
    } else {
        DSPSendMailToDSP(b->dsp_resume_vector);
        while (DSPCheckMailToDSP() != 0)
            continue;
        DSPSendMailToDSP((u32) b->dram_mmem_addr);
        while (DSPCheckMailToDSP() != 0)
            continue;
        DSPSendMailToDSP(b->dram_length);
        while (DSPCheckMailToDSP() != 0)
            continue;
        DSPSendMailToDSP(b->dram_addr);
        while (DSPCheckMailToDSP() != 0)
            continue;
    }
}

void __DSP_boot_task(DSPTaskInfo* task)
{
    volatile u32 msg;

    while (DSPCheckMailFromDSP() == 0)
        continue;

    msg = DSPReadMailFromDSP();
    DSPSendMailToDSP(0x80F3A001);
    while (DSPCheckMailToDSP() != 0)
        continue;
    DSPSendMailToDSP((u32) task->iram_mmem_addr);
    while (DSPCheckMailToDSP() != 0)
        continue;
    DSPSendMailToDSP(0x80F3C002);
    while (DSPCheckMailToDSP() != 0)
        continue;
    DSPSendMailToDSP(task->iram_addr & 0xFFFF);
    while (DSPCheckMailToDSP() != 0)
        continue;
    DSPSendMailToDSP(0x80F3A002);
    while (DSPCheckMailToDSP() != 0)
        continue;
    DSPSendMailToDSP(task->iram_length);
    while (DSPCheckMailToDSP() != 0)
        continue;
    DSPSendMailToDSP(0x80F3B002);
    while (DSPCheckMailToDSP() != 0)
        continue;
    DSPSendMailToDSP(0);
    while (DSPCheckMailToDSP() != 0)
        continue;
    DSPSendMailToDSP(0x80F3D001);
    while (DSPCheckMailToDSP() != 0)
        continue;
    DSPSendMailToDSP(task->dsp_init_vector);
    while (DSPCheckMailToDSP() != 0)
        continue;
    __DSP_debug_printf("DSP is booting task: 0x%08X\n", task);
    __DSP_debug_printf("__DSP_boot_task()  : IRAM MMEM ADDR: 0x%08X\n",
                       task->iram_mmem_addr);
    __DSP_debug_printf("__DSP_boot_task()  : IRAM DSP ADDR : 0x%08X\n",
                       task->iram_addr);
    __DSP_debug_printf("__DSP_boot_task()  : IRAM LENGTH   : 0x%08X\n",
                       task->iram_length);
    __DSP_debug_printf("__DSP_boot_task()  : DRAM MMEM ADDR: 0x%08X\n",
                       task->dram_length);
    __DSP_debug_printf("__DSP_boot_task()  : Start Vector  : 0x%08X\n",
                       task->dsp_init_vector);
}

#ifdef MUST_MATCH
#pragma push
#pragma force_active on
static char unused[] = "__DSP_add_task() : Added task    : 0x%08X\n";
#pragma pop
#endif

void __DSP_insert_task(DSPTaskInfo* task)
{
    DSPTaskInfo* t;

    if (__DSP_first_task == NULL) {
        __DSP_curr_task = task;
        __DSP_first_task = __DSP_last_task = task;
        task->prev = NULL;
        task->next = NULL;
        return;
    }
    t = __DSP_first_task;
    while (t != NULL) {
        if (task->priority < t->priority) {
            task->prev = t->prev;
            t->prev = task;
            task->next = t;
            if (task->prev == NULL)
                __DSP_first_task = task;
            else
                task->prev->next = task;
            break;
        }
        t = t->next;
    }
    if (t == NULL) {
        __DSP_last_task->next = task;
        task->next = NULL;
        task->prev = __DSP_last_task;
        __DSP_last_task = task;
    }
}

void __DSP_remove_task(DSPTaskInfo* task)
{
    task->flags = 0;
    task->state = 3;
    if (__DSP_first_task == task) {
        if (task->next != NULL) {
            __DSP_first_task = task->next;
            task->next->prev = NULL;
        } else {
            __DSP_first_task = __DSP_last_task = __DSP_curr_task = NULL;
        }
    } else if (__DSP_last_task == task) {
        __DSP_last_task = task->prev;
        task->prev->next = NULL;
        __DSP_curr_task = __DSP_first_task;
    } else {
        __DSP_curr_task = task->next;
        task->prev->next = task->next;
        task->next->prev = task->prev;
    }
}
