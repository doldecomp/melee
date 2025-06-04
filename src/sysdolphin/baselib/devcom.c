#include "devcom.h"

#include <dolphin/ar.h>

ARQRequest devComARQR[2][2];
bool devComStatus[4];

s32 HSD_DevComIsBusy(s32 idx)
{
    return devComStatus[idx];
}
