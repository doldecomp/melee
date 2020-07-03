#include "initialize.h"

#include "video.h"

extern void* lbl_804C0948[3]; // FrameBuffer

extern u32 lbl_804C0954[11]; // memReport

extern u32 lbl_804D5E0C; // iparam_fifo_size

extern GXFifoObj* lbl_804D76C4; // DefaultFifoObj

extern BOOL lbl_804D76CC; // init_done

extern GXRenderModeObj* lbl_804D5E04; // rmode

extern const GXColor lbl_804DE590;

void HSD_InitComponent(void)
{
    HSD_OSInit();
    {
        HSD_VIStatus vi_status;
        GXColor black = lbl_804DE590; // GXColor black = {0, 0, 0, 0};

        vi_status.rmode = *lbl_804D5E04; // vi_status.rmode = *rmode;
        vi_status.black = GX_TRUE;
        vi_status.vf = GX_TRUE;
        vi_status.gamma = GX_GM_1_0;
        vi_status.clear_clr = black;
        vi_status.clear_z = GX_MAX_Z24;
        vi_status.update_clr = GX_ENABLE;
        vi_status.update_alpha = GX_ENABLE;
        vi_status.update_z = GX_ENABLE;

        HSD_VIInit(&vi_status, lbl_804C0948[0], lbl_804C0948[1], lbl_804C0948[2]); // HSD_VIInit(&vi_status, FrameBuffer[0], FrameBuffer[1], FrameBuffer[2]);
    }

    HSD_GXInit();
    HSD_DVDInit();
    HSD_IDSetup();
    VIWaitForRetrace();
    HSD_ObjInit();
    func_803881E4();
    lbl_804D76CC = TRUE; // init_done = TRUE;
}

void HSD_GXSetFifoObj(GXFifoObj* fifo)
{
    lbl_804C0954[3] = lbl_804D5E0C; // memReport.gxfifo = iparam_fifo_size;
    lbl_804D76C4 = fifo; // DefaultFifoObj = fifo;
}

void HSD_DVDInit(void) { }