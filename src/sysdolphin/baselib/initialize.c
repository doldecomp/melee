#include "sysdolphin/baselib/initialize.h"

#include <stdarg.h>

#include "dolphin/os/os.h"
#include "dolphin/os/OSArena.h"
#include "dolphin/os/OSMemory.h"
#include "sysdolphin/baselib/aobj.h"
#include "sysdolphin/baselib/displayfunc.h"
#include "sysdolphin/baselib/id.h"
#include "sysdolphin/baselib/leak.h"
#include "sysdolphin/baselib/mtx.h"
#include "sysdolphin/baselib/objalloc.h"
#include "sysdolphin/baselib/random.h"
#include "sysdolphin/baselib/robj.h"
#include "sysdolphin/baselib/shadow.h"
#include "sysdolphin/baselib/tev.h"

extern OSHeapHandle __OSCurrHeap;
extern OSHeapHandle lbl_804D6018;
extern GXRenderModeObj lbl_80401168;
extern GXRenderModeObj lbl_804C1D80;

static void* FrameBuffer[HSD_VI_XFB_MAX];
static HSD_MemReport memReport;
static void* lbl_804D76B8;
static void* lbl_804D76BC;
static HSD_RenderPass lbl_804D76C0;
static GXFifoObj* DefaultFifoObj;
static int lbl_804D76C8; // current_pix_fmt
static s32 init_done;
static s32 lbl_804D76D0;

static volatile OSHeapHandle lbl_804D5E00 = -1;
GXRenderModeObj* rmode = &lbl_80401168;
static int lbl_804D5E08 = 2; // current_z_fmt
u32 iparam_fifo_size = 0x40000;
int lbl_804D5E10 = 2;
int lbl_804D5E14 = 4;
u32 lbl_804D5E18 = 0x80000;
GXColor lbl_804D5E1C = { 0 };

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
    func_803881E4();
    init_done = TRUE;
}

void HSD_GXSetFifoObj(GXFifoObj* fifo) 
{
    memReport.gxfifo = iparam_fifo_size;
    DefaultFifoObj = fifo;
}

void HSD_DVDInit(void)
{
}

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
    FrameBuffer[5] = (void*) (fb_size * nbuffer);
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
            HSD_Panic(__FILE__, 0x109, "No memory space remains for XFB.\n");
        }
        OSSetArenaLo((void*) arena_lo);
    }
    for (i = nbuffer; i < HSD_VI_XFB_MAX; i++) {
        FrameBuffer[i] = NULL;
    }
    return FrameBuffer;
}

void* HSD_AllocateFIFO(u32 size)
{
    void* fifo;
    u32 arena_lo;
    u32 arena_hi;

    arena_lo = OSRoundUp32B(OSGetArenaLo());
    arena_hi = OSRoundDown32B(OSGetArenaHi());
    if (arena_lo == 0 && arena_hi == 0) {
        fifo = OSAllocFromHeap(__OSCurrHeap, size);
        if (fifo == NULL) {
            HSD_Panic("initialize.c", 0x127, "cannot allocate memory for gx fifo.\n");
        }
    } else {
        fifo = (void*) arena_lo;
        arena_lo += size;
        if (arena_lo > (u32) OSGetArenaHi()) {
            HSD_Panic("initialize.c", 0x12E, "no space remains for gx fifo.\n");
        }
        OSSetArenaLo((void*) arena_lo);
    }
    return fifo;
}

void HSD_GXInit(void)
{
    GXLightObj lightobj;
    int i;

    GXInitLightPos(&lightobj, 1, 0, 0);
    GXInitLightDir(&lightobj, 1, 0, 0);
    GXInitLightAttn(&lightobj, 1, 0, 0, 1, 0, 0);
    {
        GXColor color = lbl_804D5E1C;
        GXColor* arg = &color;
        func_8033E11C(&lightobj, arg);
    }
    for (i = 0; i < 8; i++) {
        func_8033E144(&lightobj, func_80366B64(i));
    }
    func_80361FC4(-1);
}

void HSD_OSInit(void)
{
    u32 thing;
    u32 arena_lo;
    u32 arena_hi;

    arena_lo = (u32) OSGetArenaLo();
    arena_hi = (u32) OSGetArenaHi();
    memReport.total = OSGetPhysicalMemSize();
    memReport.system = memReport.total - (u32) OSGetArenaHi() + (u32) OSGetArenaLo()
        - memReport.xfb - memReport.gxfifo;
    arena_lo = (u32) OSInitAlloc((void*) arena_lo, (void*) arena_hi, lbl_804D5E14);
    OSSetArenaLo((void*) arena_lo);

    arena_lo = OSRoundUp32B(arena_lo);
    thing = OSRoundDown32B(arena_hi);
    lbl_804D6018 = OSCreateHeap((void*) arena_lo, (void*) (arena_lo + lbl_804D5E18));
    arena_lo += lbl_804D5E18;
    lbl_804D76B8 = (void*) arena_lo;
    lbl_804D76BC = (void*) thing;
    lbl_804D5E00 = OSCreateHeap((void*) arena_lo, (void*) thing);
    OSSetCurrentHeap(lbl_804D5E00);
    memReport.heap = thing - arena_lo;
    HSD_ObjSetHeap(thing - arena_lo, NULL);
    OSSetArenaLo((void*) thing);
}

OSHeapHandle HSD_GetHeap(void)
{
    return lbl_804D5E00;
}

void HSD_SetHeap(OSHeapHandle handle)
{
    lbl_804D5E00 = handle;
}

void HSD_GetNextArena(void** lo, void** hi)
{
    *lo = lbl_804D76B8;
    *hi = lbl_804D76BC;
}

int func_80375428(void* lo, void* hi)
{
    int i;
    void (*cb_table[])() = {
        _HSD_AObjForgetMemory,
        _HSD_DispForgetMemory,
        _HSD_IDForgetMemory,
        _HSD_ObjAllocForgetMemory,
        _HSD_RandForgetMemory,
        _HSD_RObjForgetMemory,
        NULL,
    };
    func_80382718("sysdolphin_base_library");
    HSD_ObjInit();
    for (i = 0; cb_table[i] != NULL; i++) {
        cb_table[i](lbl_804D76B8, lbl_804D76BC);
    }
    if (lo != NULL) {
        lbl_804D76B8 = lo;
    }
    if (hi != NULL) {
        lbl_804D76BC = hi;
    }
    OSDestroyHeap(lbl_804D5E00);
    lbl_804D5E00 = OSCreateHeap(lbl_804D76B8, lbl_804D76BC);
    OSSetCurrentHeap(lbl_804D5E00);
    HSD_ObjSetHeap((u32) lbl_804D76BC - (u32) lbl_804D76B8, NULL);
    return lbl_804D5E00;
}

HSD_RenderPass HSD_GetCurrentRenderPass(void)
{
    return lbl_804D76C0;
}

void func_80375538(HSD_RenderPass pass)
{
    GXRenderModeObj* rmode = &lbl_804C1D80;
    lbl_804D76C0 = pass;
    if (rmode->aa) {
        GXSetPixelFmt(2, lbl_804D5E08);
    } else {
        GXSetPixelFmt(lbl_804D76C8, GX_ZC_LINEAR);
    }
    GXSetFieldMode(rmode->field_rendering, rmode->xfbHeight < rmode->viHeight);
}

void func_803755A8(void)
{
#ifndef NON_MATCHING
    if (lbl_804D76C0 == 3)
        lbl_804D76C0 == 0;
#endif
}

void HSD_ObjInit(void)
{
    HSD_ListInitAllocData();
    HSD_AObjInitAllocData();
    HSD_FObjInitAllocData();
    HSD_IDInitAllocData();
    func_8037A714();
    func_8037A750();
    HSD_RObjInitAllocData();
    HSD_RenderInitAllocData();
    HSD_ShadowInitAllocData();
    HSD_ZListInitAllocData();
}

static char unused[] = "pix_fmt != GX_PF_RGB565_Z16";

void func_803755F8(void) // HSD_ObjDumpStat
{
    HSD_ObjAllocInfo objs[] = {
        { HSD_AObjGetAllocData, "aobj", },
        { HSD_FObjGetAllocData, "fobj", },
        { HSD_IDGetAllocData, "id", },
        { HSD_SListGetAllocData, "slist", },
        { HSD_DListGetAllocData, "dlist", },
        { HSD_VecGetAllocData, "vec", },
        { HSD_MtxGetAllocData, "mtx", },
        { HSD_RObjGetAllocData, "robj", },
        { HSD_RvalueObjGetAllocData, "rval", },
        { HSD_ShadowGetAllocData, "shadow", },
        { HSD_RenderGetAllocData, "render", },
        { HSD_ChanGetAllocData, "chan", },
        { HSD_TevRegGetAllocData, "tevreg", },
        { NULL },
    };
    HSD_ObjAllocInfo* i;
    for (i = objs; i->name != NULL; i++) {
        OSReport("objalloc: %s\tusing %d\tfreed %d\tpeak %d\n", i->name,
            HSD_ObjAllocUsed(i), HSD_ObjAllocFree(i), HSD_ObjAllocPeak(i));
    }
}

BOOL HSD_SetInitParameter(HSD_InitParam param, ...)
{
    va_list ap;
    BOOL result = FALSE;
    if (init_done) {
        if (!lbl_804D76D0) {
            OSReport("init parameter should be set before invoking HSD_Init().\n");
            lbl_804D76D0 = TRUE;
        }
        return FALSE;
    }

    va_start(ap, param);
    switch (param) {
    case HSD_INIT_FIFO_SIZE: {
        u32 fifo_size = va_arg(ap, u32);
        if (fifo_size > 0) {
            iparam_fifo_size = fifo_size;
            result = TRUE;
        }
    } break;

    case HSD_INIT_XFB_MAX_NUM: {
        u32 xfb_max_num = va_arg(ap, u32);
        if (xfb_max_num > 0) {
            lbl_804D5E10 = xfb_max_num;
            result = TRUE;
        }
    } break;

    case HSD_INIT_HEAP_MAX_NUM: {
        u32 heap_size = va_arg(ap, u32);
        if (heap_size > 0) {
            lbl_804D5E14 = heap_size;
            result = TRUE;
        }
    } break;

    case HSD_INIT_AUDIO_HEAP_SIZE: {
        u32 heap_size = va_arg(ap, u32);
        if (heap_size > 0) {
            lbl_804D5E18 = heap_size;
            result = TRUE;
        }
    } break;

    case HSD_INIT_RENDER_MODE_OBJ:
        rmode = va_arg(ap, GXRenderModeObj*);
        break;
    }
    va_end(ap);

    return result;
}
