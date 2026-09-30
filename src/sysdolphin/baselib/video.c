/**
 * @file video.c
 * @brief Video frame buffer and GX display configuration
 * @details Handles XFB (External Frame Buffer) and EFB (Embedded Frame Buffer) copying, rendering resolution, V-sync callbacks, and display state transitions.
 */

#include "video.h"

#include "debug.h"
#include "state.h"
#include <dolphin/gx.h>
#include <dolphin/vi.h>

HSD_VIInfo HSD_VIData;
static u8 garbage[HSD_ANTIALIAS_GARBAGE_SIZE] ATTRIBUTE_ALIGN(32);

#define _p ((HSD_VIInfo*) &HSD_VIData)

/**
 * @brief Internal helper to find an XFB by its state
 * @param status The status enum to search for
 * @return The index of the XFB if found, otherwise -1
 */
static int HSD_VISearchXFBByStatus(HSD_VIXFBDrawDispStatus status)
{
    int i;

    for (i = 0; i < HSD_VI_XFB_MAX; i++) {
        if (_p->xfb[i].status == status) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Sets the user callback executed before a V-sync retrace
 * @param cb The callback function
 * @return The previously set callback
 */
HSD_VIRetraceCallback HSD_VISetUserPreRetraceCallback(HSD_VIRetraceCallback cb)
{
    bool intr;
    HSD_VIRetraceCallback old = _p->pre_cb;

    intr = OSDisableInterrupts();
    _p->pre_cb = cb;
    OSRestoreInterrupts(intr);

    return old;
}

/**
 * @brief Sets the user callback executed after a V-sync retrace
 * @param cb The callback function
 * @return The previously set callback
 */
HSD_VIRetraceCallback
HSD_VISetUserPostRetraceCallback(HSD_VIRetraceCallback cb)
{
    bool intr;
    HSD_VIRetraceCallback old = _p->post_cb;

    intr = OSDisableInterrupts();
    _p->post_cb = cb;
    OSRestoreInterrupts(intr);

    return old;
}

/**
 * @brief Sets the callback executed when GX finishes a draw operation
 * @param cb The callback function
 * @return The previously set callback
 */
HSD_VIGXDrawDoneCallback
HSD_VISetUserGXDrawDoneCallback(HSD_VIGXDrawDoneCallback cb)
{
    bool intr;
    HSD_VIGXDrawDoneCallback old = _p->drawdone.cb;

    intr = OSDisableInterrupts();
    _p->drawdone.cb = cb;
    OSRestoreInterrupts(intr);

    return old;
}

/**
 * @brief Internal VI Pre-Retrace callback. Sets up the next framebuffer for display and handles V-sync timing.
 * @param retraceCount Number of retraces
 */
static void HSD_VIPreRetraceCB(u32 retraceCount)
{
    int xfb_index;
    int flush = 0;
    int renew = 0;

    xfb_index = HSD_VISearchXFBByStatus(HSD_VI_XFB_NEXT);
    if (xfb_index != -1) {
        VISetNextFrameBuffer(_p->xfb[xfb_index].buffer);
        if (_p->xfb[xfb_index].vi_all.chg_flag) {
            VIConfigure(&_p->xfb[xfb_index].vi_all.vi.rmode);
            VISetBlack(_p->xfb[xfb_index].vi_all.vi.black);
        }
        flush = 1;
        renew = 1;
    } else if (HSD_VIGetNbXFB() == 1 && _p->efb.status == HSD_VI_EFB_DRAWDONE)
    {
        if ((xfb_index = HSD_VISearchXFBByStatus(HSD_VI_XFB_DISPLAY)) == -1) {
            xfb_index = HSD_VISearchXFBByStatus(HSD_VI_XFB_FREE);
            HSD_ASSERT(252, xfb_index != -1);
            VISetNextFrameBuffer(_p->xfb[xfb_index].buffer);
            flush = 1;
        }
        _p->xfb[xfb_index].status = HSD_VI_XFB_COPYEFB;
        if (_p->efb.vi_all.chg_flag) {
            VIConfigure(&_p->efb.vi_all.vi.rmode);
            VISetBlack(_p->efb.vi_all.vi.black);
            flush = 1;
        }
        renew = 1;
    }

    if (flush) {
        VIFlush();
    }

    {
        static int vr_count = 0;
        static int renew_count = 0;

        if (renew) {
            renew_count++;
        }
        if (++vr_count >= _p->perf.frame_period) {
            _p->perf.frame_renew = renew_count;
            vr_count = renew_count = 0;
        }
    }

    if (_p->pre_cb) {
        _p->pre_cb(retraceCount);
    }
}

/**
 * @brief Internal VI Post-Retrace callback. Propagates XFB statuses (e.g., from DISPLAY to FREE or NEXT to DISPLAY).
 * @param retraceCount Number of retraces
 */
static void HSD_VIPostRetraceCB(u32 retraceCount)
{
    int xfb_index;
    int next;

    if ((next = HSD_VISearchXFBByStatus(HSD_VI_XFB_NEXT)) != -1) {
        if ((xfb_index = HSD_VISearchXFBByStatus(HSD_VI_XFB_DISPLAY)) != -1) {
            _p->xfb[xfb_index].status = HSD_VI_XFB_FREE;
        }
        _p->xfb[next].status = HSD_VI_XFB_DISPLAY;
        if ((xfb_index = HSD_VISearchXFBByStatus(HSD_VI_XFB_DRAWDONE)) != -1) {
            _p->xfb[xfb_index].status = HSD_VI_XFB_NEXT;
        }
    } else if ((xfb_index = HSD_VISearchXFBByStatus(HSD_VI_XFB_COPYEFB)) != -1) {
        HSD_VICopyEFB2XFBPtr(&_p->efb.vi_all.vi, _p->xfb[xfb_index].buffer,
                             HSD_RP_SCREEN);
        _p->xfb[xfb_index].status = HSD_VI_XFB_DISPLAY;
        _p->efb.status = HSD_VI_EFB_FREE;
    }

    if (_p->post_cb) {
        _p->post_cb(retraceCount);
    }
}

/**
 * @brief Internal GX Draw Done Callback that relays the signal to the user callback and clears the waiting flag
 */
static void HSD_VIGXDrawDoneCB(void)
{
    _p->drawdone.waiting = 0;

    if (_p->drawdone.cb) {
        _p->drawdone.cb(_p->drawdone.arg);
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
/**
 * @brief Returns the boolean waiting flag from the internal drawdone struct
 */
static int HSD_VIGetDrawDoneWaitingFlag(void)
{
    return _p->drawdone.waiting;
}
#ifdef MUST_MATCH
#pragma pop
#endif

/**
 * @brief Attempts to find and lock a free XFB for drawing
 * @return The index of the acquired XFB, or -1 if none are free
 */
int HSD_VIGetXFBDrawEnable(void)
{
    bool intr;
    int xfb_index = -1;

    if (HSD_VIGetNbXFB() < 2) {
        goto ret;
    }

    intr = OSDisableInterrupts();

    if ((xfb_index = HSD_VISearchXFBByStatus(HSD_VI_XFB_DRAWING)) == -1) {
        if ((xfb_index = HSD_VISearchXFBByStatus(HSD_VI_XFB_FREE)) != -1) {
            _p->xfb[xfb_index].status = HSD_VI_XFB_DRAWING;
        }
    }

    OSRestoreInterrupts(intr);

ret:
    return xfb_index;
}

/**
 * @brief Blocks until a free XFB becomes available for drawing
 * @return The index of the acquired XFB
 */
int HSD_VIWaitXFBDrawEnable(void)
{
    int xfb_index = -1;

    if (HSD_VIGetNbXFB() < 2) {
        goto ret;
    }

    while ((xfb_index = HSD_VIGetXFBDrawEnable()) == -1) {
        VIWaitForRetrace();
    }

ret:
    return xfb_index;
}

/**
 * @brief Internal helper to copy hi-resolution anti-aliased EFB data
 * @param rmode The active GX render mode
 */
static void HSD_VICopyEFB2XFBHiResoAA(GXRenderModeObj* rmode)
{
    int n_xfb_lines;

    GXSetDispCopySrc(0, 0, rmode->fbWidth,
                     rmode->efbHeight - HSD_ANTIALIAS_OVERLAP);
    n_xfb_lines = GXSetDispCopyYScale(1.0);
    GXSetDispCopyDst(rmode->fbWidth, n_xfb_lines);
}

/**
 * @brief Copies the EFB contents to the given XFB buffer pointer using hardware GX copy
 * @param vi The current video status context
 * @param buffer Pointer to the target XFB memory
 * @param rpass The render pass (screen, top half, bottom half, etc.)
 */
void HSD_VICopyEFB2XFBPtr(HSD_VIStatus* vi, void* buffer, HSD_RenderPass rpass)
{
    GXRenderModeObj* rmode = &vi->rmode;
    int n_xfb_lines;
    u16 lines;
    u32 offset;

    GXSetCopyFilter(rmode->aa, rmode->sample_pattern, vi->vf, rmode->vfilter);
    GXSetDispCopyGamma(vi->gamma);

    HSD_StateSetColorUpdate(vi->update_clr);
    HSD_StateSetAlphaUpdate(vi->update_alpha);
    HSD_StateSetZMode(vi->update_z, GX_LEQUAL, GX_TRUE);

    GXSetCopyClear(vi->clear_clr, vi->clear_z);

    switch (rpass) {
    case HSD_RP_SCREEN:
        GXSetCopyClamp((GXFBClamp) (GX_CLAMP_TOP | GX_CLAMP_BOTTOM));
        GXSetDispCopySrc(0, 0, rmode->fbWidth, rmode->efbHeight);
        n_xfb_lines = GXSetDispCopyYScale((f32) (rmode->xfbHeight) /
                                          (f32) (rmode->efbHeight));
        GXSetDispCopyDst(rmode->fbWidth, n_xfb_lines);
        GXCopyDisp(buffer, GX_TRUE);
        break;

    case HSD_RP_TOPHALF:
        HSD_VICopyEFB2XFBHiResoAA(rmode);
        GXSetCopyClamp(GX_CLAMP_TOP);
        lines = rmode->efbHeight - HSD_ANTIALIAS_OVERLAP;
        GXSetDispCopySrc(0, 0, rmode->fbWidth, lines);
        GXCopyDisp(buffer, GX_TRUE);
        GXPixModeSync();
        return;

    case HSD_RP_BOTTOMHALF:
        HSD_VICopyEFB2XFBHiResoAA(rmode);
        GXSetCopyClamp(GX_CLAMP_BOTTOM);
        lines = rmode->efbHeight - HSD_ANTIALIAS_OVERLAP;
        GXSetDispCopySrc(0, HSD_ANTIALIAS_OVERLAP, rmode->fbWidth, lines);
        offset = (VIPadFrameBufferWidth(rmode->fbWidth) * lines *
                  (u32) VI_DISPLAY_PIX_SZ);
        GXCopyDisp((void*) ((u32) buffer + offset), GX_TRUE);
        GXSetDispCopySrc(0, 0, rmode->fbWidth, HSD_ANTIALIAS_OVERLAP);
        GXSetCopyClamp((GXFBClamp) (GX_CLAMP_TOP | GX_CLAMP_BOTTOM));
        GXCopyDisp((void*) garbage, GX_TRUE);
        break;

    default:
        HSD_Panic(__FILE__, 0x207, "unexpected type of render pass.\n");
    }

    GXPixModeSync();
}

/**
 * @brief Tells GX to wait for draw completion and signals the draw done event
 * @param arg Argument to pass to the user draw done callback
 */
void HSD_VIGXSetDrawDone(int arg)
{
    while (HSD_VIGetDrawDoneWaitingFlag()) {
        GXWaitDrawDone();
    }
    _p->drawdone.waiting = 1;
    _p->drawdone.arg = arg;
    GXSetDrawDone();
}

/**
 * @brief Marks an XFB as waiting for draw completion
 * @param idx The index of the XFB
 */
void HSD_VISetXFBWaitDone(int idx)
{
    bool intr;

    intr = OSDisableInterrupts();

    HSD_ASSERT(590, _p->xfb[idx].status == HSD_VI_XFB_DRAWING);

    _p->xfb[idx].status = HSD_VI_XFB_WAITDONE;
    _p->xfb[idx].vi_all = _p->current;
    _p->current.chg_flag = 0;

    OSRestoreInterrupts(intr);
}

/**
 * @brief Asynchronously queues a copy from the EFB to the next available XFB
 * @param rpass The render pass context
 */
void HSD_VICopyXFBAsync(HSD_RenderPass rpass)
{
    int idx;

    if (HSD_VIGetNbXFB() < 2) {
        return;
    }

    idx = HSD_VIWaitXFBDrawEnable();
    HSD_VICopyEFB2XFBPtr(HSD_VIGetVIStatus(), HSD_VIGetXFBPtr(idx), rpass);
    HSD_VISetXFBWaitDone(idx);

    HSD_VIGXSetDrawDone(idx);
}

/**
 * @brief Marks a waiting XFB as finished drawing
 * @param idx The index of the XFB
 */
void HSD_VIDrawDoneXFB(int idx)
{
    bool intr;

    intr = OSDisableInterrupts();

    HSD_ASSERT(722, _p->xfb[idx].status == HSD_VI_XFB_WAITDONE);

    _p->xfb[idx].status = HSD_VISearchXFBByStatus(HSD_VI_XFB_NEXT) != -1
                              ? HSD_VI_XFB_DRAWDONE
                              : HSD_VI_XFB_NEXT;

    OSRestoreInterrupts(intr);
}

/**
 * @brief Subroutine that checks if any XFB is currently in a state that indicates drawing/waiting is still ongoing
 */
static int HSD_VIWaitXFBFlush_sub(void)
{
    bool intr;
    int val;

    intr = OSDisableInterrupts();

    val = (HSD_VISearchXFBByStatus(HSD_VI_XFB_WAITDONE) != -1 ||
           HSD_VISearchXFBByStatus(HSD_VI_XFB_DRAWDONE) != -1 ||
           HSD_VISearchXFBByStatus(HSD_VI_XFB_NEXT) != -1)
              ? 1
              : 0;

    OSRestoreInterrupts(intr);

    return val;
}

/**
 * @brief Blocks and yields until all waiting XFBs have flushed
 */
void HSD_VIWaitXFBFlush(void)
{
    if (HSD_VIGetNbXFB() < 2) {
        return;
    }

    while (HSD_VIWaitXFBFlush_sub()) {
        VIWaitForRetrace();
    }
}

/**
 * @brief Blocks in a spin-wait without yielding until all waiting XFBs have flushed
 */
void HSD_VIWaitXFBFlushNoYield(void)
{
    if (HSD_VIGetNbXFB() < 2) {
        return;
    }

    while (HSD_VIWaitXFBFlush_sub()) {
    }
}

/**
 * @brief Retrieves the index of the XFB that most recently finished drawing
 * @return The index of the XFB, or -1 if none
 */
int HSD_VIGetXFBLastDrawDone(void)
{
    bool intr;
    int idx = -1;

    intr = OSDisableInterrupts();

    if ((idx = HSD_VISearchXFBByStatus(HSD_VI_XFB_WAITDONE)) == -1) {
        if ((idx = HSD_VISearchXFBByStatus(HSD_VI_XFB_DRAWDONE)) == -1) {
            if ((idx = HSD_VISearchXFBByStatus(HSD_VI_XFB_NEXT)) == -1) {
                idx = HSD_VISearchXFBByStatus(HSD_VI_XFB_DISPLAY);
            }
        }
    }

    OSRestoreInterrupts(intr);

    return idx;
}

/**
 * @brief Configures the GX render mode for the next frame
 * @param rmode Pointer to the GXRenderModeObj
 */
void HSD_VISetConfigure(GXRenderModeObj* rmode)
{
    _p->current.vi.rmode = *rmode;
    _p->current.chg_flag = 1;
}

/**
 * @brief Sets the VI black flag to clear the screen or disable display output
 * @param black Boolean indicating whether to output black
 */
void HSD_VISetBlack(bool black)
{
    _p->current.vi.black = black;
    _p->current.chg_flag = 1;
}

/**
 * @brief Initializes the video subsystem with the specified external framebuffers
 * @param vi_status The video status configuration to apply
 * @param xfb0 Pointer to the first XFB
 * @param xfb1 Pointer to the second XFB
 * @param xfb2 Pointer to the third XFB
 */
void HSD_VIInit(HSD_VIStatus* vi_status, void* xfb0, void* xfb1, void* xfb2)
{
    int i, fbnum, idx;

    VIInit();

    _p->current.vi = *vi_status;
    _p->current.chg_flag = 0;
    _p->xfb[0].buffer = xfb0;
    _p->xfb[1].buffer = xfb1;
    _p->xfb[2].buffer = xfb2;

    for (i = 0, fbnum = 0; i < HSD_VI_XFB_MAX; i++) {
        _p->xfb[i].vi_all = _p->current;
        if (_p->xfb[i].buffer) {
            fbnum++;
            _p->xfb[i].status = HSD_VI_XFB_FREE;
        } else {
            _p->xfb[i].status = HSD_VI_XFB_NONE;
        }
    }

    _p->nb_xfb = fbnum;

    _p->efb.status = HSD_VI_EFB_FREE;
    _p->efb.vi_all = _p->current;

    VISetPreRetraceCallback(HSD_VIPreRetraceCB);
    VISetPostRetraceCallback(HSD_VIPostRetraceCB);

    _p->pre_cb = NULL;
    _p->post_cb = NULL;

    _p->drawdone.waiting = 0;
    _p->drawdone.arg = 0;

    GXSetDrawDoneCallback(HSD_VIGXDrawDoneCB);
    _p->drawdone.cb = NULL;

    _p->perf.frame_period = VIGetTvFormat() == VI_NTSC ? 60 : 50;
    _p->perf.frame_renew = 0;

    VIConfigure(&_p->current.vi.rmode);
    VISetBlack(_p->current.vi.black);
    VIFlush();

    idx = HSD_VISearchXFBByStatus(HSD_VI_XFB_FREE);
    HSD_VICopyEFB2XFBPtr(HSD_VIGetVIStatus(), HSD_VIGetXFBPtr(idx),
                         HSD_RP_SCREEN);
}
