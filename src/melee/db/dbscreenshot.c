#include "db.h"

#include <melee/gm/gm_1601.h>
#include <melee/un/un_2FC9.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/particle.h>

/* 4D6B94 */ int db_ScreenshotNumber;
/* 4D6B90 */ unsigned int db_ScreenshotPending;
/* 4D6B8C */ UnkFlagStruct db_5xSpeedStatus;
/* 4D6B88 */ int db_804D6B88;

void fn_Setup5xSpeed(void)
{
    db_5xSpeedStatus.b0 = false;
}

void fn_Check5xSpeed(int player)
{
    if ((db_ButtonsDown(player) & HSD_PAD_A) &&
        (db_ButtonsPressed(player) & HSD_PAD_DPADRIGHT))
    {
        fn_Toggle5xSpeed();
    }
}

void fn_Toggle5xSpeed(void)
{
    db_5xSpeedStatus.b0 ^= 1;
    if (db_5xSpeedStatus.b0) {
        gm_SetGameSpeed(5.0f);
    } else {
        gm_ResetGameSpeed();
    }
}

void db_InitScreenshot(void)
{
    db_ScreenshotNumber = 0;
    db_ScreenshotPending = 0;
}

static inline HSD_PadStatus* get_pad(u8 i)
{
    return &HSD_PadMasterStatus[i];
}

void db_CheckScreenshot(void)
{
    int i;

    for (i = 0; i < 4; i++) {
        if ((get_pad(i)->button & HSD_PAD_Y) &&
            (get_pad(i)->trigger & HSD_PAD_DPADUP))
        {
            db_ScreenshotPending = 1;
        }
    }
}

void db_TakeScreenshotIfPending(void)
{
    char spC[32];
    int temp_r3;
    int temp_r5;
    int temp_ret;
    void* var_r30;

    if (db_ScreenshotPending != 0) {
        HSD_VIWaitXFBFlush();
        temp_ret = HSD_VIGetXFBLastDrawDone();
        temp_r3 = temp_ret;
        if (temp_r3 != -1) {
            var_r30 = HSD_VIData.xfb[temp_r3].buffer;
        } else {
            OSReport("cant find xfb!\n");
            ((0) ? ((void) 0) : __assert("dbscreenshot.c", 61, "0"));
        }
        temp_r5 = db_ScreenshotNumber;
        db_ScreenshotNumber = temp_r5 + 1;
        sprintf(spC, "USB:shot/screenshot%02d.frb", temp_r5);
        fn_802289F8(spC, (int) var_r30,
                    HSD_VIData.current.vi.rmode.fbWidth *
                        HSD_VIData.current.vi.rmode.xfbHeight * 2);
        db_ScreenshotPending = 0;
    }
}

static int fn_802289F8(char* arg0, int arg1, int arg2)
{
    if (strncmp(arg0, "USB:", 4) == 0) {
        return hsd_80393A5C(arg0 + 4, arg1, arg2);
    } else {
        return -1;
    }
}
