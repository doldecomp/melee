#include <baselib/devcom.h>

bool devComStatus[4];

s32 HSD_DevComIsBusy(s32 idx) 
{
    return devComStatus[idx];
}