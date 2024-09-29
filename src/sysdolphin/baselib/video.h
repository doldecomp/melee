#ifndef _video_h_
#define _video_h_

#include <platform.h>

#include <dolphin/gx/forward.h>

#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/types.h>

#define HSD_VI_XFB_MAX 3
#define HSD_ANTIALIAS_OVERLAP 4
#define VI_DISPLAY_PIX_SZ 2
#define HSD_ANTIALIAS_GARBAGE_SIZE                                            \
    (640 * HSD_ANTIALIAS_OVERLAP * VI_DISPLAY_PIX_SZ)

typedef void (*HSD_VIGXDrawDoneCallback)(int);
typedef void (*HSD_VIRetraceCallback)(u32);

typedef enum _HSD_VIXFBDrawDispStatus {
    HSD_VI_XFB_NONE,
    HSD_VI_XFB_NOUSE,
    HSD_VI_XFB_FREE,
    HSD_VI_XFB_DRAWING,
    HSD_VI_XFB_WAITDONE,
    HSD_VI_XFB_DRAWDONE,
    HSD_VI_XFB_NEXT,
    HSD_VI_XFB_DISPLAY,
    HSD_VI_XFB_COPYEFB,
    HSD_VI_XFB_TERMINATE
} HSD_VIXFBDrawDispStatus;

typedef enum _HSD_VIEFBDrawDispStatus {
    HSD_VI_EFB_FREE,
    HSD_VI_EFB_DRAWDONE,
    HSD_VI_EFB_TERMINATE
} HSD_VIEFBDrawDispStatus;

typedef enum _HSD_RenderPass {
    HSD_RP_SCREEN,
    HSD_RP_TOPHALF,
    HSD_RP_BOTTOMHALF,
    HSD_RP_OFFSCREEN,
    HSD_RP_NUM
} HSD_RenderPass;

typedef struct _HSD_VIStatus {
    GXRenderModeObj rmode;
    s32 black;
    u8 vf;
    GXGamma gamma;
    GXColor clear_clr;
    u32 clear_z;
    u8 update_clr;
    u8 update_alpha;
    u8 update_z;
} HSD_VIStatus;

typedef struct _current {
    struct _HSD_VIStatus vi;
    u8 chg_flag;
} Current;

typedef struct _XFB {
    void* buffer;
    HSD_VIXFBDrawDispStatus status;
    Current vi_all;
} XFB;

typedef struct _HSD_VIInfo {
    Current current;

    XFB xfb[HSD_VI_XFB_MAX];

    struct _EFB {
        HSD_VIEFBDrawDispStatus status;
        Current vi_all;
    } efb;

    s32 nb_xfb;

    HSD_VIRetraceCallback pre_cb;
    HSD_VIRetraceCallback post_cb;

    struct drawdone {
        s32 waiting;
        s32 arg;
        HSD_VIGXDrawDoneCallback cb;
    } drawdone;

    struct perf {
        s32 frame_period;
        s32 frame_renew;
    } perf;

} HSD_VIInfo;

extern HSD_VIInfo HSD_VIData;

void HSD_VIInit(struct _HSD_VIStatus* vi_status, void* xfb0, void* xfb1,
                void* xfb2);
void HSD_VISetConfigure(GXRenderModeObj* rmode);
void HSD_VISetBlack(bool);

HSD_VIRetraceCallback
HSD_VISetUserPreRetraceCallback(HSD_VIRetraceCallback cb);
HSD_VIRetraceCallback
HSD_VISetUserPostRetraceCallback(HSD_VIRetraceCallback cb);
HSD_VIGXDrawDoneCallback
HSD_VISetUserGXDrawDoneCallback(HSD_VIGXDrawDoneCallback cb);

int HSD_VIGetXFBDrawEnable(void);
int HSD_VIWaitXFBDrawEnable(void);
void HSD_VICopyEFB2XFBPtr(HSD_VIStatus* vi, void* buffer,
                          HSD_RenderPass rpass);

void HSD_VIGXDrawDone(int arg);
void HSD_VIGXSetDrawDone(int arg);
void HSD_VISetXFBWaitDone(int idx);
void HSD_VICopyXFBAsync(HSD_RenderPass rpass);
void HSD_VIDrawDoneXFB(int idx);
void HSD_VIWaitXFBFlush(void);
void HSD_VIWaitXFBFlushNoYield(void);
int HSD_VIGetXFBLastDrawDone(void);

static inline int HSD_VIGetNbXFB(void)
{
    return HSD_VIData.nb_xfb;
}

static inline void* HSD_VIGetXFBPtr(int idx)
{
    return HSD_VIData.xfb[idx].buffer;
}

static inline HSD_VIStatus* HSD_VIGetVIStatus(void)
{
    return &HSD_VIData.current.vi;
}

static inline GXRenderModeObj* HSD_VIGetRenderMode(void)
{
    return &HSD_VIData.current.vi.rmode;
}

#endif
