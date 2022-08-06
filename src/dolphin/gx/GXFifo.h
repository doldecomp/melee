#ifndef _GXFIFO_H_
#define _GXFIFO_H_

#include <dolphin/types.h>
#include <dolphin/gx/gxtypes.h>
#include <dolphin/os/OSThread.h>
#include <functions.h>


typedef struct {
    s16 unk0; // x00
    s16 unk1; // x02
    u8 filler[0x38 - 0x04];
} __GXGPFifo;

void GXCPInterruptHandler(); 
void GXSetCPUFifo(GXFifoObj *fifo);
void GXInitFifoLimits(void*, s32, s32);
void GXInitFifoBase(void*, void*, u32);
void __GXFifoLink(s8);
void GXSetGPFifo(__GXGPFifo* gp_fifo);
void __GXFifoReadEnable();
void __GXFifoReadDisable();
void __GXFifoInit();

// todo: private

// GXFifoObj private fields
typedef struct
{
    void *unk0;  // base
    void *unk4;  // end
    u32 unk8;  // size
    u32 unkC;  // hiWaterMark
    u32 unk10;  // loWaterMark
    void *unk14;  // readPtr
    void *unk18;  // writePtr
    s32 unk1C;
} __GXFifoObj;

typedef struct  {
    s32 unk0; // x00
    s32 unk1; // x04
    s32 unk2; // x08

    u8 filler[0x578 - 0x10];
} __GXFifoLinkObj;

typedef struct  {
    __GXFifoLinkObj* fifo_link;
    u32 unk;
} __GXFifoLinkDataContainer;


extern __GXFifoLinkDataContainer lbl_804D5BA8;
extern __GXFifoLinkObj lbl_804A76C8;
extern __GXGPFifo* lbl_804D72F4;

extern void* lbl_804D7300;
extern void* lbl_804D7304;
extern u32 lbl_804D7308;
extern void* lbl_804D7310;
extern void* lbl_804D72F8;

#endif