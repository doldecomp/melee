#include <baselib/video.h>

HSD_VIInfo HSD_VIData;
static u8 garbage[HSD_ANTIALIAS_GARBAGE_SIZE] ATTRIBUTE_ALIGN(32);

#define _p ((HSD_VIInfo*) &HSD_VIData)

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

HSD_VIRetraceCallback HSD_VISetUserPreRetraceCallback(HSD_VIRetraceCallback cb)
{
    bool intr;
    HSD_VIRetraceCallback old = _p->pre_cb;

    intr = OSDisableInterrupts();
    _p->pre_cb = cb;
    OSRestoreInterrupts(intr);

    return old;
}

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

static void HSD_VIPreRetraceCB(u32 retraceCount)
{
    int idx;
    int flush = 0;
    int renew = 0;

    idx = HSD_VISearchXFBByStatus(HSD_VI_XFB_NEXT);
    if (idx != -1) {
        VISetNextFrameBuffer(_p->xfb[idx].buffer);
        if (_p->xfb[idx].vi_all.chg_flag) {
            VIConfigure(&_p->xfb[idx].vi_all.vi.rmode);
            VISetBlack(_p->xfb[idx].vi_all.vi.black);
        }
        flush = 1;
        renew = 1;
    } else if (HSD_VIGetNbXFB() == 1 && _p->efb.status == HSD_VI_EFB_DRAWDONE)
    {
        if ((idx = HSD_VISearchXFBByStatus(HSD_VI_XFB_DISPLAY)) == -1) {
            idx = HSD_VISearchXFBByStatus(HSD_VI_XFB_FREE);
            HSD_ASSERT(252, idx != -1);
            VISetNextFrameBuffer(_p->xfb[idx].buffer);
            flush = 1;
        }
        _p->xfb[idx].status = HSD_VI_XFB_COPYEFB;
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
