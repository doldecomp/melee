#include <dolphin/os.h>
#include <dolphin/os/OSFont.h>

static u16 FontEncode = -1;

#define TV_TYPE 0xCC

extern vu16 __VIRegs[59] AT_ADDRESS(0xCC002000);

u16 OSGetFontEncode(void)
{
    if (FontEncode <= 1) {
        return FontEncode;
    }

    switch (*(u32*) OSPhysicalToCached(TV_TYPE)) {
    case 0:
        FontEncode = (__VIRegs[0x37] & 2) ? 1 : 0;
        break;
    case 1:
    case 2:
    default:
        FontEncode = 0;
        break;
    }
    return FontEncode;
}
