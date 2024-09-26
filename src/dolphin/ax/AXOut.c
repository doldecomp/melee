#include "AXOut.h"

#include <dolphin/ax.h>

/* 4D7548 */ static void (*__AXUserFrameCallback)(void);
/* 4D754C */ static int __AXDSPInitFlag;
/* 4D7550 */ static int __AXDSPDoneFlag;

/// #__AXOutNewFrame

/// #__AXOutAiCallback

void __AXDSPInitCallback(void)
{
    __AXDSPInitFlag = 1;
}

/// #__AXDSPResumeCallback

void __AXDSPDoneCallback(void)
{
    __AXDSPDoneFlag = 1;
}

/// #__AXOutInitDSP

/// #__AXOutInit

void AXRegisterCallback(void (*callback)(void))
{
    __AXUserFrameCallback = callback;
}
