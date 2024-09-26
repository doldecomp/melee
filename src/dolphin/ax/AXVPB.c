#include "AXVPB.h"

/* 4B09E0 */ static AXPB __AXPB;
/* 4D7588 */ static u32 __AXNumVoices;

u32 __AXGetNumVoices(void)
{
    return __AXNumVoices;
}

/// #__AXServiceVPB

/// #__AXSyncPBs

AXPB* __AXGetPBs(void)
{
    return &__AXPB;
}

/// #__AXSetPBDefault

/// #__AXVPBInit

/// #AXSetVoiceState

/// #AXVPB_8035AE20

/// #AXSetVoiceItdOn

/// #AXSetVoiceItdTarget

/// #AXSetVoiceVe

/// #AXSetVoiceVeDelta

/// #AXSetVoiceAddr

/// #AXSetVoiceLoop

/// #AXSetVoiceLoopAddr

/// #AXSetVoiceEndAddr

/// #AXSetVoiceCurrentAddr

/// #AXSetVoiceAdpcm

/// #AXSetVoiceSrc

/// #AXSetVoiceSrcRatio

/// #AXSetVoiceAdpcmLoop
