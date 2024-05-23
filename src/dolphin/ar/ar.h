#ifndef DOLPHIN_AR_AR_H
#define DOLPHIN_AR_AR_H

#include <platform.h>

// offsets for __DSPRegs[i]
#define DSP_MAILBOX_IN_HI  (0)
#define DSP_MAILBOX_IN_LO  (1)
#define DSP_MAILBOX_OUT_HI (2)
#define DSP_MAILBOX_OUT_LO (3)
#define DSP_CONTROL_STATUS (5)

#define DSP_ARAM_SIZE        (9)
#define DSP_ARAM_MODE        (11)
#define DSP_ARAM_REFRESH     (13)
#define DSP_ARAM_DMA_MM_HI   (16) // Main mem address
#define DSP_ARAM_DMA_MM_LO   (17)
#define DSP_ARAM_DMA_ARAM_HI (18) // ARAM address
#define DSP_ARAM_DMA_ARAM_LO (19)
#define DSP_ARAM_DMA_SIZE_HI (20) // DMA buffer size
#define DSP_ARAM_DMA_SIZE_LO (21)

#define DSP_DMA_START_HI    (24) // DMA start address
#define DSP_DMA_START_LO    (25)
#define DSP_DMA_CONTROL_LEN (27)
#define DSP_DMA_BYTES_LEFT  (29)

#define DSP_DMA_START_FLAG (0x8000) // set to start DSP

void ARStartDMA(u32 type, u32 source, u32 dest, u32 length);
Event ARRegisterDMACallback(Event callback);
void __ARChecksize(void);
u32 ARGetBaseAddress(void);
u32 ARGetSize(void);
u32 ARGetDMAStatus(void);
u32 ARAlloc(u32 length);
u32 ARFree(u32* length);
bool ARCheckInit(void);
u32 ARInit(u32* stack_index_addr, u32 num_entries);

#endif
