#ifndef DOLPHIN_AX_AXVPB_H
#define DOLPHIN_AX_AXVPB_H

#include <platform.h>

#include <dolphin/ax.h>

void __AXDumpVPB(AXVPB* pvpb);
void __AXVPBQuit(void);

/* 35A250 */ u32 __AXGetNumVoices(void);
/* 35A258 */ void __AXServiceVPB(AXVPB* pvpb);
/* 35A934 */ void __AXSyncPBs(u32 lessDspCycles);
/* 35AB7C */ AXPB* __AXGetPBs(void);
/* 35AB88 */ void __AXSetPBDefault(AXVPB* p);
/* 35ABC4 */ void __AXVPBInit(void);
/* 35AE20 */ UNK_RET AXVPB_8035AE20(UNK_PARAMS);

#endif
