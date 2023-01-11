#ifndef _video_h_
#define _video_h_

#include <dolphin/types.h>
#include <dolphin/gx/types.h>

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

void HSD_VIInit(struct _HSD_VIStatus* vi_status, void* xfb0, void* xfb1,
                void* xfb2);

void lbl_803762C4(void);
void func_80375934(Event);
void func_8037598C(Event);
void HSD_VISetBlack(s32);

#endif
