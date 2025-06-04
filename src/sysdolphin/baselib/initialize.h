#ifndef _initialize_h_
#define _initialize_h_

#include <platform.h>

#include "baselib/video.h"

#include <dolphin/gx.h>
#include <dolphin/os/OSAlloc.h>

#define HSD_DEFAULT_FIFO_SIZE (256 * 1024)
#define HSD_DEFAULT_XFB_MAX_NUM 2
#define HSD_DEFAULT_AUDIO_SIZE (512 * 1024)

typedef struct _HSD_MemReport {
    u32 total;
    u32 system;
    u32 xfb;
    u32 gxfifo;
    u32 heap;
    u8 x14_pad[0x2C - 0x14];
} HSD_MemReport;

typedef enum _HSD_InitParam {
    HSD_INIT_FIFO_SIZE,
    HSD_INIT_XFB_MAX_NUM,
    HSD_INIT_HEAP_MAX_NUM,
    HSD_INIT_AUDIO_HEAP_SIZE,
    HSD_INIT_RENDER_MODE_OBJ
} HSD_InitParam;

void HSD_InitComponent(void);
void HSD_GXSetFifoObj(GXFifoObj* fifo);
static void HSD_DVDInit(void);
void** HSD_AllocateXFB(s32 nbuffer, GXRenderModeObj* rm);
GXFifoObj* HSD_AllocateFifo(u32 size);
static void HSD_GXInit(void);
static void HSD_OSInit(void);
OSHeapHandle HSD_GetHeap(void);
void HSD_SetHeap(OSHeapHandle handle);
void HSD_GetNextArena(void** lo, void** hi);
OSHeapHandle HSD_CreateMainHeap(void* lo, void* hi);
HSD_RenderPass HSD_GetCurrentRenderPass(void);
void HSD_StartRender(HSD_RenderPass pass);
void HSD_Init_803755A8(void);
static void HSD_ObjInit(void);
void HSD_ObjDumpStat(void);
bool HSD_SetInitParameter(HSD_InitParam param, ...);

#endif
