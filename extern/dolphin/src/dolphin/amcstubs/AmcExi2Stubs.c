#include <dolphin.h>
#include <dolphin/amc/AmcExi2Comm.h>

void EXI2_Init(volatile unsigned char** inputPendingPtrRef,
               EXICallback monitorCallback)
{
}

void EXI2_EnableInterrupts() {}

int EXI2_Poll()
{
    return 0;
}

AmcExiError EXI2_ReadN(void* bytes, unsigned long length)
{
    return AMC_EXI_NO_ERROR;
}

AmcExiError EXI2_WriteN(const void* bytes, unsigned long length)
{
    return AMC_EXI_NO_ERROR;
}

void EXI2_Reserve() {}

void EXI2_Unreserve() {}

int AMC_IsStub()
{
    return 1;
}
