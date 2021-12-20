#ifndef _AMCEXI2STUBS_H_
#define _AMCEXI2STUBS_H_

#include <dolphin/types.h>

void EXI2_Init();
void EXI2_EnableInterrupts();
BOOL EXI2_Poll();
BOOL EXI2_ReadN();
BOOL EXI2_WriteN();
void EXI2_Reserve();
void EXI2_Unreserve();
BOOL AMC_IsStub();

#endif
