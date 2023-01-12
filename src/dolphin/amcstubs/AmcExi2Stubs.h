#ifndef _AMCEXI2STUBS_H_
#define _AMCEXI2STUBS_H_

#include <Runtime/platform.h>

void EXI2_Init(void);
void EXI2_EnableInterrupts(void);
BOOL EXI2_Poll(void);
BOOL EXI2_ReadN(void);
BOOL EXI2_WriteN(void);
void EXI2_Reserve(void);
void EXI2_Unreserve(void);
BOOL AMC_IsStub(void);

#endif
