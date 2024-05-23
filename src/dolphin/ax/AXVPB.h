#ifndef DOLPHIN_AX_AXVPB_H
#define DOLPHIN_AX_AXVPB_H

#include <platform.h>

#include <dolphin/ax.h>

u32 __AXGetNumVoices(void);
void __AXServiceVPB(AXVPB* pvpb);
void __AXDumpVPB(AXVPB* pvpb);
void __AXSyncPBs(u32 lessDspCycles);
AXPB* __AXGetPBs(void);
void __AXSetPBDefault(AXVPB* p);
void __AXVPBInit(void);
void __AXVPBQuit(void);

#endif
