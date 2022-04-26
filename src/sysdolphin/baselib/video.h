#ifndef _video_h_
#define _video_h_

#include <global.h>

#define HSD_VI_XFB_MAX 3

#define VI_DISPLAY_PIX_SZ 2

typedef enum _HSD_RenderPass {
    HSD_RP_SCREEN,
    HSD_RP_TOPHALF,
    HSD_RP_BOTTOMHALF,
    HSD_RP_OFFSCREEN,
    HSD_RP_NUM
} HSD_RenderPass;

typedef struct _HSD_VIStatus {
    GXRenderModeObj rmode;
    u32 black;
    u8 vf;
    u32 gamma;
    GXColor clear_clr;
    u32 clear_z;
    u8 update_clr;
    u8 update_alpha;
    u8 update_z;
} HSD_VIStatus;

#endif
