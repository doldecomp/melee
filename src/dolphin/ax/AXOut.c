#include "AXOut.h"

#include <dolphin/ax.h>

static void (*__AXUserFrameCallback)(void);

/// #__AXOutNewFrame

/// #__AXOutAiCallback

/// #__AXDSPInitCallback

/// #__AXDSPResumeCallback

/// #__AXDSPDoneCallback

/// #__AXOutInitDSP

/// #__AXOutInit

void AXRegisterCallback(void (*callback)(void))
{
    __AXUserFrameCallback = callback;
}
