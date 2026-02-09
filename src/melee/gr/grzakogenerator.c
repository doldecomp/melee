#include "grzakogenerator.h"

#include "it/it_26B1.h"

#include <baselib/gobj.h>
#include <baselib/memory.h>

#include "grzakogenerator.static.h"

int grZakoGenerator_801CA394(void* arg0, int arg1, void* arg2, f32 arg3)
{
    u8* result;
    void* arr;

    result = (u8*) HSD_MemAlloc(0x1C);
    if (result != NULL) {
        arr = HSD_MemAlloc(arg1 * 0x18);
        *(void**)(result + 0x04) = arr;
        if (arr != NULL) {
            *(void**)(result + 0x00) = arg0;
            *(int*)(result + 0x08) = arg1;
            *(void**)(result + 0x0C) = arg2;
            *(f32*)(result + 0x10) = arg3;
            *(int*)(result + 0x14) = 0;
            *(int*)(result + 0x18) = 0;
        } else {
            HSD_Free(result);
            result = NULL;
        }
    }
    return (int) result;
}

/// #grZakoGenerator_801CA43C

/// #grZakoGenerator_801CA67C

/// #grZakoGenerator_801CA8B4

void grZakoGenerator_801CAC14(HSD_GObj* gobj)
{
    void* ip = gobj->user_data;
    s32 kind = itGetKind(gobj);

    if (kind == 0x9F) {
        struct grZakoGenerator_Data* data = lbl_8049F030.x4;
        if (data->x3C4 == gobj) {
            data->x3C4 = NULL;
        }
    } else {
        s32 idx = *(s32*)((u8*) ip + 0xDD8);
        if (idx != -1) {
            lbl_8049F030.x4->entries[idx].x4 = 0;
            lbl_8049F030.x4->entries[idx].x2 = 2;
        }
    }
}

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
    lbl_8049F030.x4->x3C4 = NULL;
}

void grZakoGenerator_801CAEF0(bool arg0)
{
    lbl_8049F030.xA_b0 = arg0;
}

/// #grZakoGenerator_801CAF08
