#include <dolphin.h>
#include <dolphin/dsp.h>
#include <dolphin/ax.h>

#include "__ax.h"

static s16 __AXOutBuffer[2][320];
static long __AXOutSBuffer[160];
AXPROFILE __AXLocalProfile;
DSPTaskInfo task;
u16 ax_dram_image[8192];

volatile static unsigned long __AXOutFrame;
volatile static unsigned long __AXOutDspReady;
volatile static long long __AXOsTime;
static void (* __AXUserFrameCallback)();
volatile static int __AXDSPInitFlag;
static int __AXDSPDoneFlag;

// functions
static void __AXDSPInitCallback(void *task);
static void __AXDSPResumeCallback(void *task);
static void __AXDSPDoneCallback(void *task);

void __AXOutNewFrame(u32 lessDspCycles) {
    u32 cl;
    int old;
    AXPROFILE * profile;

    __AXLocalProfile.axFrameStart = OSGetTime();
    __AXSyncPBs(lessDspCycles);
    __AXPrintStudio();
    cl = __AXGetCommandListAddress();
    DSPSendMailToDSP(0xBABE0180);
    do {} while (DSPCheckMailToDSP() != 0U);
    DSPSendMailToDSP(cl);
    do {} while (DSPCheckMailToDSP() != 0U);
    old = OSEnableInterrupts();
    __AXServiceCallbackStack();
    __AXLocalProfile.auxProcessingStart = OSGetTime();
    __AXProcessAux();
    __AXLocalProfile.auxProcessingEnd = OSGetTime();
    __AXLocalProfile.userCallbackStart = OSGetTime();
    if (__AXUserFrameCallback) {
        __AXUserFrameCallback();
    }
    __AXLocalProfile.userCallbackEnd = OSGetTime();
    __AXNextFrame(__AXOutSBuffer, &__AXOutBuffer[__AXOutFrame][0]);
    __AXOutFrame += 1;
    __AXOutFrame &= 1;
    AIInitDMA((u32)&__AXOutBuffer[__AXOutFrame][0], 0x280);
    __AXLocalProfile.axFrameEnd = OSGetTime();
    __AXLocalProfile.axNumVoices = __AXGetNumVoices();
    profile = (void*)__AXGetCurrentProfile();
    if (profile) {
        memcpy(profile, &__AXLocalProfile, sizeof(AXPROFILE));
    }
    OSRestoreInterrupts(old);
}

void __AXOutAiCallback(void) {
    if (__AXOutDspReady == 0) {
        __AXOsTime = OSGetTime();
    }
    if (__AXOutDspReady == 1) {
        __AXOutNewFrame(0);
        __AXOutDspReady = 0;
        return;
    }
    __AXOutDspReady = 2;
    DSPAssertTask(&task);
}

static void __AXDSPInitCallback(void *task) {
    __AXDSPInitFlag = 1;
}

static void __AXDSPResumeCallback(void *task) {
    if (__AXOutDspReady == 2) {
        __AXOutDspReady = 0;
        __AXOutNewFrame((u32)(OSGetTime() - __AXOsTime) / 4);
        return;
    }
    __AXOutDspReady = 1U;
}

static void __AXDSPDoneCallback(void *task) {
    __AXDSPDoneFlag = 1;
}

void __AXOutInitDSP(void) {
    task.iram_mmem_addr = axDspSlave;
    task.iram_length = axDspSlaveLength;
    task.iram_addr = 0;
    task.dram_mmem_addr = ax_dram_image;
    task.dram_length = 0x2000;
    task.dram_addr = 0;
    task.dsp_init_vector = 0x10;
    task.dsp_resume_vector = 0x30;
    task.init_cb = __AXDSPInitCallback;
    task.res_cb = __AXDSPResumeCallback;
    task.done_cb = __AXDSPDoneCallback;
    task.req_cb = NULL;
    task.priority = 0;
    __AXDSPInitFlag = 0;
    __AXDSPDoneFlag = 0;
    if (DSPCheckInit() == 0) {
        DSPInit();
    }
    DSPAddTask(&task);
    do {} while (__AXDSPInitFlag == 0);
}

void __AXOutInit(void) {
#ifdef DEBUG
    OSReport("Initializing AXOut code module\n");
#endif
    ASSERTLINE(0x13B, ((u32)&__AXOutBuffer[0][0] & 0x1F) == 0);
    ASSERTLINE(0x13C, ((u32)&__AXOutBuffer[1][0] & 0x1F) == 0);
    ASSERTLINE(0x13D, ((u32)&__AXOutSBuffer[0] & 0x1F) == 0);
    __AXOutFrame = 0;
    memset(__AXOutBuffer, 0, sizeof(__AXOutBuffer));
    DCFlushRange(__AXOutBuffer, sizeof(__AXOutBuffer));
    memset(__AXOutSBuffer, 0, sizeof(__AXOutSBuffer));
    DCFlushRange(__AXOutSBuffer, sizeof(__AXOutSBuffer));
    __AXOutInitDSP();
    AIRegisterDMACallback(__AXOutAiCallback);
    __AXNextFrame(__AXOutSBuffer, &__AXOutBuffer[1][0]);
    __AXOutDspReady = 1;
    __AXUserFrameCallback = NULL;
    AIInitDMA((u32)&__AXOutBuffer[__AXOutFrame][0], sizeof(__AXOutBuffer[0]));
    AIStartDMA();
}

void __AXOutQuit(void) {
    int old;

#ifdef DEBUG
    OSReport("Shutting down AXOut code module\n");
#endif
    old = OSDisableInterrupts();
    __AXUserFrameCallback = NULL;
    AIStopDMA();
    DSPHalt();
    do {} while (DSPGetDMAStatus() != 0U);
    DSPReset();
    OSRestoreInterrupts(old);
}

void AXRegisterCallback(void (* callback)()) {
    __AXUserFrameCallback = callback;
}
