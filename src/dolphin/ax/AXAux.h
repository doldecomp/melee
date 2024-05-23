#ifndef DOLPHIN_AX_AXAUX_H
#define DOLPHIN_AX_AXAUX_H

#include <platform.h>

#include <dolphin/ax.h>

void __AXAuxInit(void);
void __AXAuxQuit(void);
void __AXGetAuxAInput(u32* p);
void __AXGetAuxAOutput(u32* p);
void __AXGetAuxBInput(u32* p);
void __AXGetAuxBOutput(u32* p);
void __AXProcessAux(void);

#endif
