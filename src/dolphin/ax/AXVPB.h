#ifndef GALE01_35A250
#define GALE01_35A250

#include <platform.h>
#include <placeholder.h>

#include <dolphin/ax.h>

/* 35A250 */ u32 __AXGetNumVoices(void);
/* 35A258 */ void __AXServiceVPB(AXVPB* pvpb);
/* 35A934 */ void __AXSyncPBs(u32 lessDspCycles);
/* 35AB7C */ AXPB* __AXGetPBs(void);
/* 35AB88 */ void __AXSetPBDefault(AXVPB* p);
/* 35ABC4 */ void __AXVPBInit(void);
/* 35AE20 */ UNK_RET AXVPB_8035AE20(UNK_PARAMS);

#endif
