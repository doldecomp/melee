#include <dolphin/ax/AX.h>

#include <dolphin/ax/AXAlloc.h>
#include <dolphin/ax/AXCL.h>
#include <dolphin/ax/AXInit.h>
#include <dolphin/ax/AXSPB.h>
#include <dolphin/ax/AXVPB.h>
#include <dolphin/ax/AXOut.h>

void AXInitEx(void)
{
    __AXAllocInit();
    __AXVPBInit();
    __AXSPBInit();
    __AXAuxInit();
    __AXClInit();
    __AXOutInit();
}
