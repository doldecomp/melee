#include "grzakogenerator.h"

#include "grzakogenerator.static.h"

/// #grZakoGenerator_801CA394

/// #grZakoGenerator_801CA43C

/// #grZakoGenerator_801CA67C

/// #grZakoGenerator_801CA8B4

/// #grZakoGenerator_801CAC14

/// #grZakoGenerator_801CACB8

s32 fn_801CADBC(void)
{
    return grZakoGenerator_801CA8B4(0);
}

s32 grZakoGenerator_801CADE0(void)
{
    return grZakoGenerator_801CA8B4(1);
}

/// #grZakoGenerator_801CAE04

void grZakoGenerator_801CAEB0(int arg0, int arg1)
{
    struct grZakoGenerator_Data* data = lbl_8049F030.x4;
    s16 val = (s16) arg1;

    if (data->x3C0 != -1) {
        return;
    }
    data->x3C0 = val;
    lbl_8049F030.x4->x3C8 = arg0;
    lbl_8049F030.x4->x3C4 = 0;
}

void grZakoGenerator_801CAEF0(bool arg0)
{
    lbl_8049F030.xA_b0 = arg0;
}

/// #grZakoGenerator_801CAF08
