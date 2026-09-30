/**
 * @file video.h
 * @brief Video frame buffer and GX display configuration
 * @details Handles XFB (External Frame Buffer) and EFB (Embedded Frame Buffer) copying, rendering resolution, V-sync callbacks, and display state transitions.
 */

#ifndef _video_h_
#define _video_h_

#include <Runtime/platform.h>

#include <dolphin/gx.h>
#include <dolphin/gx/GXEnum.h>

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

/**
 * @brief Initializes the video subsystem with the specified external framebuffers
 * @param vi_status The video status configuration to apply
 * @param xfb0 Pointer to the first XFB
 * @param xfb1 Pointer to the second XFB
 * @param xfb2 Pointer to the third XFB
 */
void HSD_VIInit(struct _HSD_VIStatus* vi_status, void* xfb0, void* xfb1,
                void* xfb2);

/**
 * @brief Configures the GX render mode for the next frame
 * @param rmode Pointer to the GXRenderModeObj
 */
void HSD_VISetConfigure(GXRenderModeObj* rmode);

/**
 * @brief Sets the VI black flag to clear the screen or disable display output
 * @param black Boolean indicating whether to output black
 */
void HSD_VISetBlack(bool black);

/**
 * @brief Sets the user callback executed before a V-sync retrace
 * @param cb The callback function
 * @return The previously set callback
 */
HSD_VIRetraceCallback
HSD_VISetUserPreRetraceCallback(HSD_VIRetraceCallback cb);

/**
 * @brief Sets the user callback executed after a V-sync retrace
 * @param cb The callback function
 * @return The previously set callback
 */
HSD_VIRetraceCallback
HSD_VISetUserPostRetraceCallback(HSD_VIRetraceCallback cb);

/**
 * @brief Sets the callback executed when GX finishes a draw operation
 * @param cb The callback function
 * @return The previously set callback
 */
HSD_VIGXDrawDoneCallback
HSD_VISetUserGXDrawDoneCallback(HSD_VIGXDrawDoneCallback cb);

/**
 * @brief Attempts to find and lock a free XFB for drawing
 * @return The index of the acquired XFB, or -1 if none are free
 */
int HSD_VIGetXFBDrawEnable(void);

/**
 * @brief Blocks until a free XFB becomes available for drawing
 * @return The index of the acquired XFB
 */
int HSD_VIWaitXFBDrawEnable(void);

/**
 * @brief Copies the EFB contents to the given XFB buffer pointer using hardware GX copy
 * @param vi The current video status context
 * @param buffer Pointer to the target XFB memory
 * @param rpass The render pass (screen, top half, bottom half, etc.)
 */
void HSD_VICopyEFB2XFBPtr(HSD_VIStatus* vi, void* buffer,
                          HSD_RenderPass rpass);

/**
 * @brief Internal GX draw done handler routine
 * @param arg Callback argument
 */
void HSD_VIGXDrawDone(int arg);

/**
 * @brief Tells GX to wait for draw completion and signals the draw done event
 * @param arg Argument to pass to the user draw done callback
 */
void HSD_VIGXSetDrawDone(int arg);

/**
 * @brief Marks an XFB as waiting for draw completion
 * @param idx The index of the XFB
 */
void HSD_VISetXFBWaitDone(int idx);

/**
 * @brief Asynchronously queues a copy from the EFB to the next available XFB
 * @param rpass The render pass context
 */
void HSD_VICopyXFBAsync(HSD_RenderPass rpass);

/**
 * @brief Marks a waiting XFB as finished drawing
 * @param idx The index of the XFB
 */
void HSD_VIDrawDoneXFB(int idx);

/**
 * @brief Blocks and yields until all waiting XFBs have flushed
 */
void HSD_VIWaitXFBFlush(void);

/**
 * @brief Blocks in a spin-wait without yielding until all waiting XFBs have flushed
 */
void HSD_VIWaitXFBFlushNoYield(void);

/**
 * @brief Retrieves the index of the XFB that most recently finished drawing
 * @return The index of the XFB, or -1 if none
 */
int HSD_VIGetXFBLastDrawDone(void);

/**
 * @brief Gets the number of XFBs in use
 * @return The number of framebuffers
 */
static inline int HSD_VIGetNbXFB(void)
{
    return HSD_VIData.nb_xfb;
}

/**
 * @brief Gets the buffer pointer for a specific XFB index
 * @param idx The index of the XFB
 * @return The pointer to the framebuffer memory
 */
static inline void* HSD_VIGetXFBPtr(int idx)
{
    return HSD_VIData.xfb[idx].buffer;
}

/**
 * @brief Gets the current VI status context
 * @return Pointer to the current HSD_VIStatus
 */
static inline HSD_VIStatus* HSD_VIGetVIStatus(void)
{
    return &HSD_VIData.current.vi;
}

/**
 * @brief Gets the current GX render mode object
 * @return Pointer to the GXRenderModeObj
 */
static inline GXRenderModeObj* HSD_VIGetRenderMode(void)
{
    return &HSD_VIData.current.vi.rmode;
}

#endif
