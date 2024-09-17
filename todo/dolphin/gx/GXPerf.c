#include <placeholder.h>

#include <dolphin/gx/__types.h>
#include <dolphin/gx/GXPerf.h>

// https://decomp.me/scratch/gAvJm // 3230 (94.13%)
void GXSetGPMetric(u32 arg0, u32 arg1)
{
    NOT_IMPLEMENTED;
}

void GXClearGPMetric(void)
{
    __cpReg[2] = 4;
}
