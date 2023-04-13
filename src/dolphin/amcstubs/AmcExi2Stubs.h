#ifndef _AMCEXI2STUBS_H_
#define _AMCEXI2STUBS_H_

#include <platform.h>

void EXI2_Init(void);
void EXI2_EnableInterrupts(void);
bool EXI2_Poll(void);
bool EXI2_ReadN(void);
bool EXI2_WriteN(void);
void EXI2_Reserve(void);
void EXI2_Unreserve(void);
bool AMC_IsStub(void);

#endif
