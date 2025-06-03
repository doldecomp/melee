#include "particle.static.h"

#include <dolphin/gx.h>
#include <dolphin/gx/GXGeometry.h>

void DrawRectangle(f32 x_min, f32 y_min, f32 w, f32 h, GXColor* color)
{
    f32 x_max;
    f32 y_max;
    GXColor c;
    u8 r, g, b, a;

    GXBegin(0x80, 0, 4);

    x_max = x_min + w;
    y_max = y_min + h;

    // Send the corners in clockwise order, starting with top left

    GXWGFifo.f32 = x_min;
    GXWGFifo.f32 = y_min;
    a = color->a;
    b = color->b;
    g = color->g;
    r = color->r;
    GXWGFifo.u8 = r;
    GXWGFifo.u8 = g;
    GXWGFifo.u8 = b;
    GXWGFifo.u8 = a;

    GXWGFifo.f32 = x_max;
    GXWGFifo.f32 = y_min;
    GXWGFifo.u8 = r;
    GXWGFifo.u8 = g;
    GXWGFifo.u8 = b;
    GXWGFifo.u8 = a;

    GXWGFifo.f32 = x_max;
    GXWGFifo.f32 = y_max;
    GXWGFifo.u8 = r;
    GXWGFifo.u8 = g;
    GXWGFifo.u8 = b;
    GXWGFifo.u8 = a;

    GXWGFifo.f32 = x_min;
    GXWGFifo.f32 = y_max;
    GXWGFifo.u8 = r;
    GXWGFifo.u8 = g;
    GXWGFifo.u8 = b;
    GXWGFifo.u8 = a;

    GXEnd();
}

/// #DrawASCII

/// #hsd_80391A04

/// #hsd_80391AC8

/// #hsd_80391E18

/// #hsd_80391F28

/// #hsd_80392194

/// #hsd_803921B8

/// #hsd_803922FC

void hsd_80392474(void)
{
    hsd_804D7850 = 0;
}

/// #fn_80392480

/// #hsd_80392528

/// #hsd_8039254C

/// #fn_80392934

/// #fn_80392A08

/// #fn_80392A3C

s32 fn_80392CCC(s32 arg0)
{
    hsd_804D7894 = arg0;
    return 0;
}

/// #fn_80392CD8

/// #fn_80392E2C

/// #hsd_80392E80

/// #hsd_803931A4

/// #fn_803932D0

/// #hsd_80393328

/// #hsd_80393440

void hsd_80393840(void) {}

/// #hsd_80393844

/// #hsd_80393A04

void hsd_80393A54(int arg0)
{
    hsd_804D78C0 = arg0;
}

/// #hsd_80393A5C

/// #fn_80393C14

/// #hsd_80393D2C

/// #hsd_80393DA0

/// #hsd_80393E34

/// #hsd_80393E68

/// #hsd_80393EF4

/// #hsd_80394068

/// #hsd_80394128

/// #hsd_803941E8

/// #hsd_80394314

/// #hsd_80394434

/// #hsd_80394544

/// #hsd_80394668

/// #hsd_80394950

/// #Exception_ReportStackTrace

/// #Exception_ReportCodeline

/// #fn_80394DF4

/// #hsd_80394E8C

/// #hsd_80394F48

/// #hsd_80395550

/// #hsd_80395644

/// #hsd_803956D8

/// #hsd_803957C0

/// #hsd_80395970

/// #hsd_80395A78

/// #hsd_80395D88

/// #hsd_80396130

/// #hsd_80396188

/// #hsd_803962A8

/// #hsd_803966A0

/// #hsd_80396868

/// #hsd_80396884

/// #hsd_80396A20

/// #hsd_80396C78

/// #hsd_80396E40

void fn_803970D8(void) {}

void fn_803970DC(void) {}

void fn_803970E0(void) {}

void fn_803970E4(void) {}

void fn_803970E8(void) {}

void fn_803970EC(void) {}

void fn_803970F0(void) {}

void fn_803970F4(void) {}

void fn_803970F8(void) {}

void fn_803970FC(void) {}

void fn_80397100(void) {}

void fn_80397104(void) {}

void fn_80397108(void) {}

void fn_8039710C(void) {}

/// #hsd_80397110

/// #fn_80397374

/// #hsd_80397520

/// #hsd_803975D4

/// #fn_80397814

/// #hsd_80397DA4

void Exception_StoreDebugLevel(int arg0)
{
    hsd_804D78C8 = arg0;
}

void hsd_80397DFC(u32 arg0)
{
    hsd_804D78CC = (arg0 + 0xF) >> 4;
}

/// #baselib_mfspr

/// #fn_803982E4

/// #hsd_80398310

/// #hsd_803983A4

/// #psInitDataBankLoad

/// #psInitDataBankLocate

/// #psInitDataBank

/// #hsd_80398A08

/// #hsd_80398C04

/// #hsd_80398F0C

/// #hsd_80398F8C

/// #hsd_803991D8

/// #hsd_8039930C

/// #hsd_8039CEAC

/// #hsd_8039CF4C

/// #hsd_8039D048

/// #hsd_8039D0A0

void hsd_8039D1E4(UNK_T arg0, int arg1)
{
    M2C_FIELD(arg0, int*, 0x58) = arg1;
}

/// #hsd_8039D1EC

/// #hsd_8039D214

/// #hsd_8039D354

/// #hsd_8039D3AC

/// #hsd_8039D4DC

/// #hsd_8039D580

/// #hsd_8039D5DC

/// #hsd_8039D688

/// #hsd_8039D71C

/// #hsd_8039D9C8

/// #hsd_8039DAD4

/// #hsd_8039EE24

/// #hsd_8039EFAC

/// #hsd_8039F05C

/// #hsd_8039F6CC
