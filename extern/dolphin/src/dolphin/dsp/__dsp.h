#ifndef _DOLPHIN__DSP_H_
#define _DOLPHIN__DSP_H_

#include <dolphin/dsp.h>

void __DSPHandler(__OSInterrupt, OSContext*);
void __DSP_exec_task(DSPTaskInfo*, DSPTaskInfo*);
void __DSP_boot_task(DSPTaskInfo*);
void __DSP_insert_task(DSPTaskInfo*);
void __DSP_add_task(DSPTaskInfo* task);
void __DSP_remove_task(DSPTaskInfo* task);
void __DSP_debug_printf(const char* fmt, ...);

#endif
