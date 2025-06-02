#include <dolphin.h>
#include <dolphin/odemu/odemu.h>

int Hu_IsStub()
{
    return 1;
}

void DBInitComm(int* inputFlagPtr, int* mtrCallback) {}

void DBInitInterrupts() {}

long DBQueryData()
{
    return 0;
}

unsigned long DBRead()
{
    return 0;
}

unsigned long DBWrite()
{
    return 0;
}

void DBOpen() {}

void DBClose() {}
