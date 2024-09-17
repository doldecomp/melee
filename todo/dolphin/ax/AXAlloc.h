#ifndef DOLPHIN_AX_AXALLOC_H
#define DOLPHIN_AX_AXALLOC_H

#include <platform.h>

#include <dolphin/ax.h>

AXVPB* __AXGetStackHead(u32 priority);
void __AXServiceCallbackStack(void);
void __AXInitVoiceStacks(void);
void __AXAllocInit(void);
void __AXAllocQuit(void);
void __AXPushFreeStack(AXVPB* p);
AXVPB* __AXPopFreeStack(void);
void __AXPushCallbackStack(AXVPB* p);
AXVPB* __AXPopCallbackStack(void);
void __AXRemoveFromStack(AXVPB* p);
void __AXPushStackHead(AXVPB* p, u32 priority);
AXVPB* __AXPopStackFromBottom(u32 priority);

#endif
