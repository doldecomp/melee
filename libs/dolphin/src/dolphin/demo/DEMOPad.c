#include <dolphin.h>
#include <dolphin/pad.h>
#include <dolphin/demo.h>

#include "__demo.h"

// .data
static unsigned long PadChanMask[4] = {
    0x80000000,
    0x40000000,
    0x20000000,
    0x10000000,
};

// .bss
static struct PADStatus Pad[4];
DEMODMPad DemoPad[4];

// .sbss
u32 DemoNumValidPads;

// functions
static void DEMOPadCopy(struct PADStatus * pad, DEMODMPad *dmpad);
void DEMOPadRead();
void DEMOPadInit();

static void DEMOPadCopy(struct PADStatus * pad, DEMODMPad *dmpad) {
    unsigned short dirs;

    dirs = 0;
    if (pad->stickX < -0x30) {
        dirs |= 0x4000;
    }
    if (pad->stickX > 0x30) {
        dirs |= 0x8000;
    }
    if (pad->stickY < -0x30) {
        dirs |= 0x2000;
    }
    if (pad->stickY > 0x30) {
        dirs |= 0x1000;
    }
    if (pad->substickX < -0x30) {
        dirs |= 0x400;
    }
    if (pad->substickX > 0x30) {
        dirs |= 0x800;
    }
    if (pad->substickY < -0x30) {
        dirs |= 0x200;
    }
    if (pad->substickY > 0x30) {
        dirs |= 0x100;
    }
    dmpad->dirsNew = (dirs & (dmpad->dirs ^ dirs));
    dmpad->dirsReleased = (dmpad->dirs & (dmpad->dirs ^ dirs));
    dmpad->dirs = dirs;
    dmpad->buttonDown = (pad->button & (dmpad->pst.button ^ pad->button));
    dmpad->buttonUp = (dmpad->pst.button & (dmpad->pst.button ^ pad->button));
    dmpad->stickDeltaX = (pad->stickX - dmpad->pst.stickX);
    dmpad->stickDeltaY = (pad->stickY - dmpad->pst.stickY);
    dmpad->substickDeltaX = (pad->substickX - dmpad->pst.substickX);
    dmpad->substickDeltaY = (pad->substickY - dmpad->pst.substickY);
    dmpad->pst = *pad;
}

void DEMOPadRead() {
    long i;
    unsigned long ResetReq;

    ResetReq = 0;
    PADRead(&Pad[0]);
    PADClamp(&Pad[0]);
    DemoNumValidPads = 0;
    for(i = 0; i < 4; i++) {
        if (Pad[i].err == 0 || Pad[i].err == -3) {
            DemoNumValidPads += 1;
        } else if (Pad[i].err == -1) {
            ResetReq |= PadChanMask[i];
        }
        if (Pad[i].err != -3) {
            DEMOPadCopy(&Pad[i], &DemoPad[i]);
        }
    }
    if (ResetReq != 0) {
        PADReset(ResetReq);
    }
}

void DEMOPadInit() {
    long i;

    PADInit();
    for(i = 0; i < 4; i++) {
        DemoPad[i].pst.button = 0;
        DemoPad[i].pst.stickX = 0;
        DemoPad[i].pst.stickY = 0;
        DemoPad[i].pst.substickX = 0;
        DemoPad[i].pst.substickY = 0;
        DemoPad[i].pst.triggerLeft = 0;
        DemoPad[i].pst.triggerRight = 0;
        DemoPad[i].pst.analogA = 0;
        DemoPad[i].pst.analogB = 0;
        DemoPad[i].pst.err = 0;
        DemoPad[i].buttonDown = 0;
        DemoPad[i].buttonUp = 0;
        DemoPad[i].dirs = 0;
        DemoPad[i].dirsNew = 0;
        DemoPad[i].dirsReleased = 0;
        DemoPad[i].stickDeltaX = 0;
        DemoPad[i].stickDeltaY = 0;
        DemoPad[i].substickDeltaX = 0;
        DemoPad[i].substickDeltaY = 0;
    }
}
