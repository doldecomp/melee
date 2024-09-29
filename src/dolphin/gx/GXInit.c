#include <placeholder.h>

#include <dolphin/gx/__types.h>
#include <dolphin/gx/GXInit.h>
#include <dolphin/gx/types.h>

static void __GXInitGX(void);

GXContext __GXContext;
GXContexts __GXContexts = { &__GXContext, NULL };

volatile u32* __memReg; // todo: OSPhysicalToUncached (?)
volatile u16* __peReg;  // todo: OSPhysicalToUncached (0x0C001000)
volatile u16* __cpReg;  // todo: OSPhysicalToUncached (0x0C000000)
volatile u32* __piReg;  // todo: OSPhysicalToUncached (0x0C003000)

GXColor const GXInit_804DE200 = { 0x40, 0x40, 0x40, 0xFF };
GXColor const GXInit_804DE204 = { 0x00, 0x00, 0x00, 0x00 };
GXColor const GXInit_804DE208 = { 0xFF, 0xFF, 0xFF, 0xFF };

f32 const GXInit_804DE20C = 1.0F;
f32 const GXInit_804DE210 = 0.0F;
f32 const GXInit_804DE214 = 0.10000000149011612F;
f64 const GXInit_804DE218 = 4503599627370496.0L;

void __GXDefaultTexRegionCallback(void)
{
    NOT_IMPLEMENTED;
}

#pragma push
#pragma peephole off
UNK_T __GXDefaultTlutRegionCallback(u32 arg0)
{
    if (arg0 >= 0x14) {
        return NULL;
    } else {
        return &__GXContexts.main->x2D0[arg0];
    }
}
#pragma pop

GXFifoObj* GXInit(GXFifoObj* fifo, u32 size)
{
    NOT_IMPLEMENTED;
}

// https://decomp.me/scratch/zVpOX // 7812 (85.26%)
void __GXInitGX(void)
{
    NOT_IMPLEMENTED;
}
