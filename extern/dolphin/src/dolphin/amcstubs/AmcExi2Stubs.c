#include <dolphin.h>

// EXI error codes
typedef enum
{
	AMC_EXI_NO_ERROR	= 0,
	AMC_EXI_UNSELECTED
} AmcExiError;

void EXI2_Init();
void EXI2_EnableInterrupts();
int EXI2_Poll();
AmcExiError EXI2_ReadN();
AmcExiError EXI2_WriteN();
void EXI2_Reserve();
void EXI2_Unreserve();
int AMC_IsStub();

void EXI2_Init() {
    
}

void EXI2_EnableInterrupts() {
    
}

int EXI2_Poll() {
    return 0;
}

AmcExiError EXI2_ReadN() {
    return AMC_EXI_NO_ERROR;
}

AmcExiError EXI2_WriteN() { 
    return AMC_EXI_NO_ERROR;
}

void EXI2_Reserve() {
    
}

void EXI2_Unreserve() {
    
}

int AMC_IsStub() {
    return 1;
}
