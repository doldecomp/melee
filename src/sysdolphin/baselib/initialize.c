#include "initialize.h"

#include "aobj.h"
#include "class.h"
#include "debug.h"
#include "displayfunc.h"
#include "fobj.h"
#include "id.h"
#include "list.h"
#include "lobj.h"
#include "mtx.h"
#include "objalloc.h"
#include "random.h"
#include "robj.h"
#include "shadow.h"
#include "state.h"
#include "tev.h"
#include "video.h"

#include <stdarg.h>
#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <dolphin/vi.h>

extern OSHeapHandle HSD_Synth_804D6018;
extern GXRenderModeObj GXNtsc480IntDf;

static void* FrameBuffer[HSD_VI_XFB_MAX];
static HSD_MemReport memReport;
static void* hsd_heap_next_arena_lo;
static void* hsd_heap_next_arena_hi;
static HSD_RenderPass current_render_pass;
static GXFifoObj* DefaultFifoObj;
static int current_pix_fmt;
static s32 init_done;
static s32 shown;

static volatile OSHeapHandle current_heap = -1;
static GXRenderModeObj* rmode = &GXNtsc480IntDf;
static int current_z_fmt = GX_ZC_MID;
static u32 iparam_fifo_size = HSD_DEFAULT_FIFO_SIZE;
static int iparam_xfb_max_num = HSD_DEFAULT_XFB_MAX_NUM;
static int iparam_heap_max_num = 4;
static u32 iparam_audio_heap_size = HSD_DEFAULT_AUDIO_SIZE;
static GXColor HSD_Init_804D5E1C = { 0 };

void HSD_InitComponent(void)
{
    HSD_OSInit();
    {
        HSD_VIStatus vi_status;
        GXColor black = { 0, 0, 0, 0 };

        vi_status.rmode = *rmode;
        vi_status.black = GX_TRUE;
        vi_status.vf = GX_TRUE;
        vi_status.gamma = GX_GM_1_0;
        vi_status.clear_clr = black;
        vi_status.clear_z = GX_MAX_Z24;
        vi_status.update_clr = GX_ENABLE;
        vi_status.update_alpha = GX_ENABLE;
        vi_status.update_z = GX_ENABLE;

        HSD_VIInit(&vi_status, FrameBuffer[0], FrameBuffer[1], FrameBuffer[2]);
    }

    HSD_GXInit();
    HSD_DVDInit();
    HSD_IDSetup();
    VIWaitForRetrace();
    HSD_ObjInit();
    HSD_LogInit();
    init_done = true;
}

void HSD_GXSetFifoObj(GXFifoObj* fifo)
{
    memReport.gxfifo = iparam_fifo_size;
    DefaultFifoObj = fifo;
}

static void HSD_DVDInit(void) {}

void** HSD_AllocateXFB(s32 nbuffer, GXRenderModeObj* rm)
{
    u32 fb_size;
    u32 arena_lo;
    u32 arena_hi;
    s32 i;

    if (rm == NULL) {
        return NULL;
    }
    fb_size = ((rm->fbWidth + 0xF) & 0xFFF0) * rm->xfbHeight * 2;
    arena_lo = OSRoundUp32B(OSGetArenaLo());
    arena_hi = OSRoundDown32B(OSGetArenaHi());
    memReport.xfb = fb_size * nbuffer;
    if (arena_lo == arena_hi) {
        for (i = 0; i < nbuffer; i++) {
            FrameBuffer[i] = OSAllocFromHeap(__OSCurrHeap, fb_size);
        }
    } else {
        for (i = 0; i < nbuffer; i++) {
            FrameBuffer[i] = (void*) arena_lo;
            arena_lo = OSRoundUp32B(arena_lo + fb_size);
        }
        if (arena_lo > arena_hi) {
            HSD_Panic(__FILE__, 265, "No memory space remains for XFB.\n");
        }
        OSSetArenaLo((void*) arena_lo);
    }
    for (i = nbuffer; i < HSD_VI_XFB_MAX; i++) {
        FrameBuffer[i] = NULL;
    }
    return FrameBuffer;
}

GXFifoObj* HSD_AllocateFifo(u32 size)
{
    GXFifoObj* fifo;
    u32 arena_lo;
    u32 arena_hi;

    arena_lo = OSRoundUp32B(OSGetArenaLo());
    arena_hi = OSRoundDown32B(OSGetArenaHi());
    if (arena_lo == 0 && arena_hi == 0) {
        fifo = OSAllocFromHeap(__OSCurrHeap, size);
        if (fifo == NULL) {
            HSD_Panic(__FILE__, 295, "cannot allocate memory for gx fifo.\n");
        }
    } else {
        fifo = (void*) arena_lo;
        arena_lo += size;
        if (arena_lo > (u32) OSGetArenaHi()) {
            HSD_Panic(__FILE__, 302, "no space remains for gx fifo.\n");
        }
        OSSetArenaLo((void*) arena_lo);
    }
    return fifo;
}

static void HSD_GXInit(void)
{
    GXLightObj lightobj;
    int i;

    GXInitLightPos(&lightobj, 1, 0, 0);
    GXInitLightDir(&lightobj, 1, 0, 0);
    GXInitLightAttn(&lightobj, 1, 0, 0, 1, 0, 0);
    GXInitLightColor(&lightobj, HSD_Init_804D5E1C);

    for (i = 0; i < 8; i++) {
        GXLoadLightObjImm(&lightobj, HSD_Index2LightID(i));
    }
    HSD_StateInvalidate(-1);
}

static void HSD_OSInit(void)
{
    u32 new_arena_lo;
    u32 new_arena_hi;
    u32 old_arena_lo = (u32) OSGetArenaLo();
    u32 old_arena_hi = (u32) OSGetArenaHi();
    memReport.total = OSGetPhysicalMemSize();
    memReport.system = memReport.total - (u32) OSGetArenaHi() +
                       (u32) OSGetArenaLo() - memReport.xfb - memReport.gxfifo;
    old_arena_lo = (u32) OSInitAlloc(
        (void*) old_arena_lo, (void*) old_arena_hi, iparam_heap_max_num);
    OSSetArenaLo((void*) old_arena_lo);

    new_arena_lo = OSRoundUp32B(old_arena_lo);
    new_arena_hi = OSRoundDown32B(old_arena_hi);
    HSD_Synth_804D6018 = OSCreateHeap(
        (void*) new_arena_lo, (void*) (new_arena_lo + iparam_audio_heap_size));
    new_arena_lo += iparam_audio_heap_size;
    hsd_heap_next_arena_lo = (void*) new_arena_lo;
    hsd_heap_next_arena_hi = (void*) new_arena_hi;
    current_heap = OSCreateHeap((void*) new_arena_lo, (void*) new_arena_hi);
    OSSetCurrentHeap(current_heap);
    memReport.heap = new_arena_hi - new_arena_lo;
    HSD_ObjSetHeap(new_arena_hi - new_arena_lo, NULL);
    OSSetArenaLo((void*) new_arena_hi);
}

OSHeapHandle HSD_GetHeap(void)
{
    return current_heap;
}

void HSD_SetHeap(OSHeapHandle handle)
{
    current_heap = handle;
}

void HSD_GetNextArena(void** lo, void** hi)
{
    *lo = hsd_heap_next_arena_lo;
    *hi = hsd_heap_next_arena_hi;
}

OSHeapHandle HSD_CreateMainHeap(void* lo, void* hi)
{
    int i;
    void (*cb_table[])(void* lo, void* hi) = {
        _HSD_AObjForgetMemory,
        _HSD_DispForgetMemory,
        _HSD_IDForgetMemory,
        _HSD_ObjAllocForgetMemory,
        _HSD_RandForgetMemory,
        _HSD_RObjForgetMemory,
        NULL,
    };
    hsdForgetClassLibrary("sysdolphin_base_library");
    HSD_ObjInit();
    for (i = 0; cb_table[i] != NULL; i++) {
        cb_table[i](hsd_heap_next_arena_lo, hsd_heap_next_arena_hi);
    }
    if (lo != NULL) {
        hsd_heap_next_arena_lo = lo;
    }
    if (hi != NULL) {
        hsd_heap_next_arena_hi = hi;
    }
    OSDestroyHeap(current_heap);
    current_heap =
        OSCreateHeap(hsd_heap_next_arena_lo, hsd_heap_next_arena_hi);
    OSSetCurrentHeap(current_heap);
    HSD_ObjSetHeap((u32) hsd_heap_next_arena_hi - (u32) hsd_heap_next_arena_lo,
                   NULL);
    return current_heap;
}

HSD_RenderPass HSD_GetCurrentRenderPass(void)
{
    return current_render_pass;
}

void HSD_StartRender(HSD_RenderPass pass)
{
    GXRenderModeObj* rmode = HSD_VIGetRenderMode();
    current_render_pass = pass;
    if (rmode->aa) {
        GXSetPixelFmt(GX_PF_RGB565_Z16, current_z_fmt);
    } else {
        GXSetPixelFmt(current_pix_fmt, GX_ZC_LINEAR);
    }
    GXSetFieldMode(rmode->field_rendering, rmode->xfbHeight < rmode->viHeight);
}

void HSD_Init_803755A8(void)
{
    // Does nothing, but need to force a comparison to make this match
    if (current_render_pass == HSD_RP_OFFSCREEN) {
        current_render_pass == 0;
    }
}

static void HSD_ObjInit(void)
{
    HSD_ListInitAllocData();
    HSD_AObjInitAllocData();
    HSD_FObjInitAllocData();
    HSD_IDInitAllocData();
    HSD_VecInitAllocData();
    HSD_MtxInitAllocData();
    HSD_RObjInitAllocData();
    HSD_RenderInitAllocData();
    HSD_ShadowInitAllocData();
    HSD_ZListInitAllocData();
}

#ifndef BUGFIX
static char str_pix_fmt_neq_gx_pf_rgb565_z16[] = "pix_fmt != GX_PF_RGB565_Z16";
#endif

void HSD_ObjDumpStat(void)
{
    struct {
        HSD_ObjAllocData* (*func)(void);
        char* label;
    } types[] = { { HSD_AObjGetAllocData, "aobj" },
                  { HSD_FObjGetAllocData, "fobj" },
                  { HSD_IDGetAllocData, "id" },
                  { HSD_SListGetAllocData, "slist" },
                  { HSD_DListGetAllocData, "dlist" },
                  { HSD_VecGetAllocData, "vec" },
                  { HSD_MtxGetAllocData, "mtx" },
                  { HSD_RObjGetAllocData, "robj" },
                  { HSD_RvalueObjGetAllocData, "rval" },
                  { HSD_ShadowGetAllocData, "shadow" },
                  { HSD_RenderGetAllocData, "render" },
                  { HSD_ChanGetAllocData, "chan" },
                  { HSD_TevRegGetAllocData, "tevreg" },
                  { NULL, NULL } };
    int i;

    for (i = 0; types[i].label; i++) {
        OSReport("objalloc: %s\tusing %d\tfreed %d\tpeak %d\n", types[i].label,
                 HSD_ObjAllocGetUsing(types[i].func()),
                 HSD_ObjAllocGetFreed(types[i].func()),
                 HSD_ObjAllocGetPeak(types[i].func()));
    }
}

bool HSD_SetInitParameter(HSD_InitParam param, ...)
{
    va_list ap;
    bool ok = false;

    if (init_done) {
        if (!shown) {
            OSReport(
                "init parameter should be set before invoking HSD_Init().\n");
            shown = true;
        }
        return false;
    }

    va_start(ap, param);
    switch (param) {
    case HSD_INIT_FIFO_SIZE: {
        u32 fifo_size = va_arg(ap, u32);
        if (fifo_size > 0) {
            iparam_fifo_size = fifo_size;
            ok = true;
        }
    } break;

    case HSD_INIT_XFB_MAX_NUM: {
        u32 xfb_max_num = va_arg(ap, u32);
        if (xfb_max_num > 0) {
            iparam_xfb_max_num = xfb_max_num;
            ok = true;
        }
    } break;

    case HSD_INIT_HEAP_MAX_NUM: {
        u32 heap_size = va_arg(ap, u32);
        if (heap_size > 0) {
            iparam_heap_max_num = heap_size;
            ok = true;
        }
    } break;

    case HSD_INIT_AUDIO_HEAP_SIZE: {
        u32 heap_size = va_arg(ap, u32);
        if (heap_size > 0) {
            iparam_audio_heap_size = heap_size;
            ok = true;
        }
    } break;

    case HSD_INIT_RENDER_MODE_OBJ:
        rmode = va_arg(ap, GXRenderModeObj*);
        break;
    }
    va_end(ap);

    return ok;
}
