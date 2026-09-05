#include "targcont.h"

#include "dolphin_trk_glue.h"
#include "targimpl.h"

DSError TRKTargetContinue(void)
{
    TRKTargetSetStopped(false);
    UnreserveEXI2Port();
    TRKSwapAndGo();
    ReserveEXI2Port();
    return kNoError;
}
