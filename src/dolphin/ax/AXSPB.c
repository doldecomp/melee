#include <platform.h>

#include "AXSPB.h"

static AXSPB __AXStudio ATTRIBUTE_ALIGN(32);

AXSPB* __AXGetStudio(void)
{
    return &__AXStudio;
}

/// #__AXPrintStudio

/// #__AXSPBInit

/// #__AXDepopVoice
