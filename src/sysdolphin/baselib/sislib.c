#include "sislib.h"

#include "cobj.h"
#include "gobj.h"
#include "gobjgxlink.h"
#include "gobjobject.h"
#include "gobjplink.h"
#include "gobjuserdata.h"
#include "memory.h"
#include "state.h"
#include "tev.h"
#include "wobj.h"

#include "dolphin/gx.h"
#include "dolphin/mtx.h"

#include <stdarg.h>
#include <stdio.h>
#include <printf.h>
#include <dolphin/os.h>

static HSD_WObjDesc HSD_SisLib_8040C490 = { NULL, { 0, 0, 1 }, NULL, };

static HSD_WObjDesc HSD_SisLib_8040C4A4 = { NULL, { 0, 0, 0 }, NULL, };

static HSD_CameraDescPerspective HSD_SisLib_8040C4B8 = {
    0,
    0,
    1,
    0,
    0x280,
    0,
    0x1E0,
    0,
    0x280,
    0,
    0x1E0,
    &HSD_SisLib_8040C490,
    &HSD_SisLib_8040C4A4,
    0,
    0,
    0,
    65535,
    30,
    1.3333,
};

sislib_UnkAllocData* HSD_SisLib_804D7970;
sislib_UnkAllocData* HSD_SisLib_804D7974;
HSD_Text* HSD_SisLib_804D7978;
sislib_UnkAlloc3* HSD_SisLib_804D797C;

// extern ? *HSD_SisLib_804D796C;
// extern u8 *HSD_SisLib_804D7978;
// sislib_UnknownType001 HSD_SisLib_8040C490 = { 0, 1.0f };

//u8 HSD_SisLib_8040C490[0x60] = { 0 };

static f32
    HSD_SisLib_8040CB00; /* unable to generate initializer: unknown type */
static u8
    HSD_SisLib_8040CD40; /* unable to generate initializer: unknown type */

static HSD_Archive* HSD_SisLib_804D1110[5];
SIS* HSD_SisLib_804D1124[5];
s8 HSD_SisLib_804D6390[4] = { 0, 0, 0, 0 };

// a generic allocator used by multiple
// data types
void* HSD_SisLib_803A5798(s32 size)
{
    sislib_UnkAllocData* var_r31;
    sislib_UnkAllocData* var_r30;
    s32 temp_r0;
    s32 var_r29;
    sislib_UnkAllocData* var_r27;
    sislib_UnkAllocData* var_r26;
    sislib_UnkAllocData* var_r4;

    var_r31 = NULL;
    var_r30 = NULL;
    var_r27 = HSD_SisLib_804D7970;
    var_r26 = HSD_SisLib_804D7974;
    if (size == 0) {
        OSReport("ZERO byte alloc\n");
        OSPanic("sislib.c", 0x3C, "");
    }
    temp_r0 = size % 4;
    if (temp_r0 != 0) {
        size += 4 - temp_r0;
    }
    while (var_r26 != NULL) {
        var_r30 = var_r26;
        var_r26 = var_r26->data_0;
    }
    for (;;) {
        if (var_r27->size == size) {
            var_r31 = var_r27;
            break;
        }
        if (var_r27->size > size) {
            if (var_r31 != NULL) {
                if (var_r31->size > var_r27->size) {
                    var_r31 = var_r27;
                }
            } else {
                var_r31 = var_r27;
            }
        }
        var_r27 = var_r27->data_0;
        if (var_r27 == NULL) {
            break;
        }
    }
    if (var_r31 == NULL) {
        OSReport("Memory Empty\n");
        OSPanic("sislib.c", 0x56, "");
    }

    var_r4 = HSD_SisLib_804D7970;

    if (var_r4 == var_r31) {
        int temp_r27;
        u8* temp_r26;
        sislib_UnkAllocData* temp_r25;

        temp_r26 = (u8*) HSD_SisLib_804D7970->data_1;
        temp_r25 = HSD_SisLib_804D7970->data_0;
        temp_r27 = HSD_SisLib_804D7970->size - size - sizeof(sislib_UnkAllocData);
        if (temp_r27 < 0) {
            OSReport("Memory Empty\n");
            OSPanic("sislib.c", 0x5F, "");
        }

        HSD_SisLib_804D7970 = (sislib_UnkAllocData*) (temp_r26 + size);
        HSD_SisLib_804D7970->data_0 = temp_r25;
        HSD_SisLib_804D7970->data_1 = (HSD_Text*) (HSD_SisLib_804D7970 + 1);
        HSD_SisLib_804D7970->size = temp_r27;
        var_r31->size = size;
    } else {
        while (var_r4->data_0 != var_r31) {
            var_r4 = var_r4->data_0;
        }
        var_r4->data_0 = var_r31->data_0;
    }
    var_r31->data_0 = NULL;
    if (var_r30 != NULL) {
        var_r30->data_0 = var_r31;
    }
    if (HSD_SisLib_804D7974 == NULL) {
        HSD_SisLib_804D7974 = var_r31;
    }
    return var_r31->data_1;
}

void HSD_SisLib_803A594C(void* arg0)
{
    sislib_UnkAllocData* var_r4;
    sislib_UnkAllocData* var_r5;
    sislib_UnkAllocData* var_r6;
    sislib_UnkAllocData* var_r7;
    u32 temp_r3;

    var_r4 = HSD_SisLib_804D7970;
    var_r5 = NULL;
    var_r7 = HSD_SisLib_804D7974;
    var_r6 = NULL;
    while (var_r7 != NULL) {
        if ((void*) var_r7->data_1 != (void*) arg0) {
            var_r6 = var_r7;
            var_r7 = var_r7->data_0;
        }
    }
    if (var_r7 != NULL) {
        if (var_r4 == (void*) ((u8*) var_r7->data_1 + var_r7->size)) {
            s32 new_size = var_r4->size + (var_r7->size + 0xC);
            if (var_r6 != NULL) {
                var_r6->data_0 = var_r7->data_0;
            } else {
                HSD_SisLib_804D7974 = var_r7->data_0;
            }
            arg0 = var_r7;
            HSD_SisLib_804D7970->data_0 = var_r4->data_0;
            HSD_SisLib_804D7970->data_1 =
                (HSD_Text*) (HSD_SisLib_804D7970 + 1);
            HSD_SisLib_804D7970->size = new_size;
            return;
        }
        while (var_r4 != NULL) {
            var_r5 = var_r4;
            var_r4 = var_r4->data_0;
        }
        if (var_r5 != NULL) {
            var_r5->data_0 = var_r7;
        }
        if (var_r6 != NULL) {
            var_r6->data_0 = var_r7->data_0;
        } else {
            HSD_SisLib_804D7974 = var_r7->data_0;
        }
        var_r7->data_0 = NULL;
    }
}

void HSD_SisLib_803A5A2C(void* arg0)
{
    HSD_Text* temp_r0;
    sislib_UnkAllocData* temp_r3;
    HSD_Text* curr;
    HSD_Text* last;

    last = NULL;
    curr = HSD_SisLib_804D7978;
    while (curr != NULL) {
        temp_r0 = curr->x50;
        if (curr == arg0) {
            if (last != NULL) {
                last->x50 = temp_r0;
            } else {
                HSD_SisLib_804D7978 = temp_r0;
            }
            temp_r3 = curr->x64;
            if (temp_r3 != NULL) {
                if (temp_r3->data_1 != NULL) {
                    HSD_SisLib_803A594C(temp_r3->data_1);
                }
                HSD_SisLib_803A594C(curr->x64);
            }
            if (curr->x68 != NULL) {
                HSD_SisLib_803A594C(curr->x68);
            }
            HSD_SisLib_803A594C(curr);
            return;
        }
        last = curr;
        curr = temp_r0;
    }
}

void HSD_SisLib_803A5CC4(HSD_Text* arg0)
{
    HSD_Text* curr = HSD_SisLib_804D7978;
    while (curr != NULL) {
        HSD_Text* next = curr->x50;
        if (curr == arg0) {
            if (curr->x54 != NULL) {
                HSD_GObjPLink_80390228(curr->x54);
                curr->x54 = NULL;
            } else {
                HSD_SisLib_803A5A2C(curr);
            }
            return;
        }
        curr = next;
    }
}

void HSD_SisLib_803A5D30(void)
{
    HSD_Text* curr = HSD_SisLib_804D7978;
    while (curr != NULL) {
        HSD_Text* next = curr->x50;
        if (curr->x54 != NULL) {
            HSD_GObjPLink_80390228(curr->x54);
            curr->x54 = NULL;
        } else {
            HSD_SisLib_803A5A2C(curr);
        }
        curr = next;
    }
}

static inline void HSD_SisLib_803A5DA0_inline0(s32 arg0)
{
    HSD_Text* curr = HSD_SisLib_804D7978;
    while (curr != NULL) {
        HSD_Text* next = curr->x50;
        if (curr->x4F == arg0) {
            if (curr->x54 != NULL) {
                HSD_GObjPLink_80390228(curr->x54);
                curr->x54 = NULL;
            } else {
                HSD_SisLib_803A5A2C(curr);
            }
        }
        curr = next;
    }
}

void HSD_SisLib_803A5DA0(s32 arg0)
{
    sislib_UnkAlloc3* last = NULL;
    sislib_UnkAlloc3* curr;

    HSD_SisLib_803A5DA0_inline0(arg0);

    curr = HSD_SisLib_804D797C;
    while (curr != NULL) {
        sislib_UnkAlloc3* next = curr->x0;
        if (curr->xA == arg0) {
            if (curr->x4 != 0U) {
                HSD_GObjPLink_80390228(curr->x4);
                curr->x4 = 0;
            }
            if (last != NULL) {
                last->x0 = next;
            } else {
                HSD_SisLib_804D797C = next;
            }
            HSD_SisLib_803A594C(curr);
        }
        last = curr;
        curr = next;
    }
}

HSD_Text* HSD_SisLib_803A5ACC(int arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                              f32 arg5, f32 arg6)
{
    HSD_Text* var_r30;
    HSD_Text* var_r29;
    sislib_UnkAlloc3* var_r28;
    HSD_GObj* gobj;
    int var_r4;
    HSD_Text* temp_r30;

    var_r4 = arg1;
    var_r29 = NULL;
    var_r28 = NULL;
    gobj = NULL;
    var_r30 = HSD_SisLib_804D7978;
    if (var_r4 >= 0) {
        var_r28 = HSD_SisLib_804D797C;
        while (1) {
            if (var_r28->xA == arg0 && --var_r4 < 0) {
                break;
            }

            if (var_r28 == NULL) {
                OSReport("unknow camera\n");
                return NULL;
            }
            var_r28 = var_r28->x0;
        }
        gobj = GObj_Create(var_r28->x8, var_r28->xC, var_r28->xD);
        GObj_SetupGXLink(gobj, HSD_SisLib_803A84BC, var_r28->xE, var_r28->xF);
    }
    while (var_r30 != NULL) {
        var_r29 = var_r30;
        var_r30 = var_r30->x50;
    }
    temp_r30 = HSD_SisLib_803A5798(0xA0);
    if (HSD_SisLib_804D7978 == NULL) {
        HSD_SisLib_804D7978 = temp_r30;
    }
    if (var_r29 != NULL) {
        var_r29->x50 = temp_r30;
    }
    if (gobj != NULL) {
        GObj_InitUserData(gobj, var_r28->x8, HSD_SisLib_803A5A2C, temp_r30);
    }
    temp_r30->x50 = NULL;
    temp_r30->x54 = gobj;
    temp_r30->x0 = arg2;
    temp_r30->x4 = arg3;
    temp_r30->x8 = arg4;
    temp_r30->xC = arg5;
    temp_r30->x10 = arg6;
    temp_r30->x14.w = 0.0f;
    temp_r30->x14.z = 0.0f;
    temp_r30->x14.y = 0.0f;
    temp_r30->x14.x = 0.0f;
    temp_r30->x24.y = 1.0f;
    temp_r30->x24.x = 1.0f;
    temp_r30->x64 = NULL;
    temp_r30->x68 = 0;
    temp_r30->x5C = 0;
    temp_r30->x2C.w = 0;
    temp_r30->x2C.z = 0;
    temp_r30->x2C.y = 0;
    temp_r30->x2C.x = 0;
    temp_r30->x30.w = 0xFF;
    temp_r30->x30.z = 0xFF;
    temp_r30->x30.y = 0xFF;
    temp_r30->x30.x = 0xFF;
    temp_r30->x34.y = 1.0f;
    temp_r30->x34.x = 1.0f;
    temp_r30->x3C.y = 0.0f;
    temp_r30->x3C.x = 0.0f;
    temp_r30->x46 = 0;
    temp_r30->x44 = 0;
    temp_r30->x4A = 0;
    temp_r30->x48 = 0;
    temp_r30->x49 = 0;
    temp_r30->x6E = 0;
    temp_r30->x6C = 0;
    temp_r30->x4E = 0;
    temp_r30->x4D = 0;
    temp_r30->x4C = 0;
    temp_r30->x58 = 0;
    temp_r30->x4F = arg0;
    return temp_r30;
}

extern sislib_UnkAllocData* HSD_SisLib_804D796C;

void HSD_SisLib_803A5E70(void)
{
    sislib_UnkAlloc3* curr;

    HSD_SisLib_803A5D30();

    curr = HSD_SisLib_804D797C;
    while (curr != NULL) {
        sislib_UnkAlloc3* next = curr->x0;
        if (curr->x4 != 0) {
            HSD_GObjPLink_80390228(curr->x4);
            curr->x4 = 0;
        }
        HSD_SisLib_803A594C(curr);
        curr = next;
    }

    HSD_SisLib_804D797C = NULL;
    HSD_SisLib_804D7970 = HSD_SisLib_804D796C;
    HSD_SisLib_804D7974 = NULL;
    HSD_SisLib_804D7970->data_0 = NULL;
    HSD_SisLib_804D7970->data_1 = (HSD_Text*) (HSD_SisLib_804D7970 + 1);
    HSD_SisLib_804D7970->size = HSD_SisLib_804D7968 - 0xC;
}

void HSD_SisLib_803A5F50(s32 arg0)
{
    HSD_Archive** temp_r31;

    HSD_SisLib_803A5DA0(arg0);
    temp_r31 = &HSD_SisLib_804D1110[arg0];
    if (*temp_r31 != NULL) {
        HSD_SisLib_803A947C(*temp_r31);
        *temp_r31 = NULL;
        HSD_SisLib_804D1124[arg0] = NULL;
    }
}

void HSD_SisLib_803A5FBC(void)
{
    int i;
    HSD_SisLib_803A5E70();
    for (i = 0; i < 5; i++) {
        if (HSD_SisLib_804D1110[i] != NULL) {
            HSD_SisLib_803A947C(HSD_SisLib_804D1110[i]);
            HSD_SisLib_804D1110[i] = NULL;
            HSD_SisLib_804D1124[i] = NULL;
        }
    }
    HSD_Free(HSD_SisLib_804D796C);
}

void HSD_SisLib_803A6048(u32 size)
{
    sislib_UnkAllocData* alloc;
    int i;

    HSD_SisLib_804D7968 = size;
    HSD_SisLib_804D7974 = NULL;
    alloc = HSD_MemAlloc(HSD_SisLib_804D7968);
    HSD_SisLib_804D7970 = alloc;
    HSD_SisLib_804D796C = HSD_SisLib_804D7970;
    HSD_SisLib_804D7970->data_0 = NULL;
    HSD_SisLib_804D7970->data_1 = (HSD_Text*) (HSD_SisLib_804D7970 + 1);
    HSD_SisLib_804D7970->size = HSD_SisLib_804D7968 - 0xC;
    HSD_SisLib_804D7978 = NULL;
    HSD_SisLib_804D797C = NULL;

    for (i = 0; i < 5; i++) {
        HSD_SisLib_804D1110[i] = NULL;
        HSD_SisLib_804D1124[i] = NULL;
    }
}

// GObj "remove" function callback
void fn_803A60EC(void* arg0)
{
    sislib_UnkAlloc3* curr = HSD_SisLib_804D797C;
    while (curr != NULL) {
        if (curr->x4 == arg0) {
            curr->x4 = 0U;
            return;
        }
        curr = curr->x0;
    }
}

s32 HSD_SisLib_803A611C(int arg0, u32 arg1, u16 arg2, u8 arg3, u8 arg4,
                        u8 arg5, u8 arg6, u32 arg7)
{
    int count;
    sislib_UnkAlloc3* var_r28;
    sislib_UnkAlloc3* temp_r27;
    sislib_UnkAlloc3* var_r11;

    var_r28 = NULL;
    count = 0;
    var_r11 = HSD_SisLib_804D797C;
    while (var_r11 != NULL) {
        var_r28 = var_r11;
        if (var_r11->xA == arg0) {
            count += 1;
        }
        var_r11 = var_r11->x0;
    }
    temp_r27 = HSD_SisLib_803A5798(0x10);
    if (HSD_SisLib_804D797C == NULL) {
        HSD_SisLib_804D797C = temp_r27;
    }
    if (var_r28 != NULL) {
        var_r28->x0 = temp_r27;
    }
    temp_r27->x8 = arg2;
    temp_r27->xC = arg3;
    temp_r27->xD = arg4;
    temp_r27->xE = arg5;
    temp_r27->xF = arg6;
    temp_r27->xA = arg0;
    temp_r27->x0 = NULL;
    if (arg1 != 0) {
        temp_r27->x4 = NULL;
    } else {
        temp_r27->x4 = GObj_Create(arg2, arg3, arg4);
        if (temp_r27->x4 != NULL) {
            HSD_CObj* temp_r3 = HSD_CObjLoadDesc((HSD_CObjDesc*) &HSD_SisLib_8040C4B8);
            if (temp_r3 != NULL) {
                HSD_CObjSetOrtho(temp_r3, 0.0f, -480.0f, 0.0f, 640.0f);
                {
                    u8 tmp = *HSD_GObj_804D784B;
                    HSD_GObjObject_80390A70(temp_r27->x4, tmp, temp_r3);
                }
                GObj_SetupGXLinkMax(temp_r27->x4, HSD_GObj_803910D8, arg7);
                temp_r27->x4->gxlink_prios = (u64) 1 << arg5;
                GObj_InitUserData(temp_r27->x4, arg2, fn_803A60EC,
                                  temp_r27->x4);
            } else {
                HSD_GObjPLink_80390228(temp_r27->x4);
                temp_r27->x4 = NULL;
            }
        }
    }
    return count;
}

void HSD_SisLib_803A62A0(s32 arg0, char* arg1, char* arg2)
{

    HSD_Archive* tmp = HSD_SisLib_803A945C(arg1);
    HSD_SisLib_804D1110[arg0] = tmp;
    if (tmp == NULL) {
        OSReport("Cannot open archive %s.\n", arg1);
        OSPanic("sislib.c", 0x24A, "");
    }
    {
        SIS* sis = HSD_ArchiveGetPublicAddress(HSD_SisLib_804D1110[arg0], arg2);
        HSD_SisLib_804D1124[arg0] = sis;
        if (sis == NULL) {
            OSReport("Cannot find symbol %s.\n", arg2);
            OSPanic("sislib.c", 0x24F, "");
        }
    }
}

void HSD_SisLib_803A6368(HSD_Text* arg0, s32 arg1)
{
    SIS** temp_r3;
    s32 var_r5;

    temp_r3 = (SIS**) HSD_SisLib_804D1124[arg0->x4F];
    if (temp_r3 != NULL) {
        arg0->x5C = temp_r3[arg1];
    }
    arg0->x60 = NULL;
    arg0->x74 = 0.0f;
    arg0->x70 = 0.0f;
    arg0->x8C = arg0->x30;
    arg0->x80.x = arg0->x34.x;
    arg0->x80.y = arg0->x34.y;
    arg0->x78.x = arg0->x3C.x;
    arg0->x78.y = arg0->x3C.y;
    arg0->x90 = arg0->x44;
    arg0->x92 = arg0->x46;
    arg0->x9E = arg0->x4A;
    arg0->x9D = arg0->x49;
    arg0->x9C = arg0->x48;
    arg0->x6C = 0;
    arg0->x98 = 0;
    arg0->x94 = 0;
    arg0->x4B = 0;
    if (arg0->x68 != NULL) {
        HSD_SisLib_803A594C(arg0->x68);
    }
    arg0->x68 = HSD_SisLib_803A5798(0x10);
    var_r5 = 0;
    arg0->x6E = 0x10;
    while (var_r5 < arg0->x6E) {
        arg0->x68[var_r5] = 0;
        var_r5 += 1;
    }
}

void HSD_SisLib_803A6478(u8* arg0, u8* arg1)
{
    while (*arg1 != 0) {
        if (*arg1 >= 0x20) {
            *arg0++ = *arg1++;
            *arg0++ = *arg1++;
        } else {
            switch (*arg0++ = *arg1++) {
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 14:
                *arg0++ = *arg1++;
            case 12:
                *arg0++ = *arg1++;
            case 5:
                *arg0++ = *arg1++;
                *arg0++ = *arg1++;
            }
        }
    }
    *arg0 = 0;
}

void HSD_SisLib_803A6530(s32 arg0, s32 arg1, s32 arg2)
{
    u8** temp_r6 = (u8**) HSD_SisLib_804D1124[arg0];
    HSD_SisLib_803A6478(temp_r6[arg1], temp_r6[arg2]);
}

void HSD_SisLib_803A660C(s32 arg0, s32 arg1, s32 arg2)
{
    u8** temp_r6 = (u8**) HSD_SisLib_804D1124[arg0];
    u8* var_r3 = temp_r6[arg1];
    u8* var_r4 = temp_r6[arg2];

    while (*var_r3 != 0) {
        if (*var_r3 >= 0x20) {
            var_r3 += 2;
        } else {
            switch (*var_r3) {
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 14:
                var_r3 += 5;
                break;
            case 12:
                var_r3 += 4;
                break;
            case 5:
                var_r3 += 3;
                break;
            default:
                var_r3 += 1;
            }
        }
    }
    HSD_SisLib_803A6478(var_r3, var_r4);
}

HSD_Text* HSD_SisLib_803A6754(int arg0, s32 arg1)
{
    sislib_UnkAllocData* temp_r3;
    HSD_Text* temp_r30;
    HSD_Text* temp_r3_2;

    temp_r30 =
        HSD_SisLib_803A5ACC(arg0, arg1, 0.0f, 0.0f, 0.0f, 640.0f, 480.0f);
    temp_r3 = HSD_SisLib_803A5798(0x10);
    temp_r30->x64 = temp_r3;
    temp_r3_2 = HSD_SisLib_803A5798(0x80);
    temp_r3->data_1 = temp_r3_2;
    temp_r3->data_0 = (sislib_UnkAllocData*) temp_r3_2;
    temp_r3->size = 0x80;
    // @todo: This being a byte store means one of my assumptions is wrong;
    // maybe this is a different struct.
    *(u8*) &temp_r3->data_0->data_0 = 0;
    // @todo: Do any other Data struct usages have a 0xC member?
    *(&temp_r3->size + 1) = 0;
    HSD_SisLib_803A6368(temp_r30, 0);
    temp_r30->x5C = (SIS*) temp_r3->data_1;
    return temp_r30;
}

s32 HSD_SisLib_803A67EC(u8* data, u8* string)
{
    s32 sp10;
    s32 temp_r10_2;
    s32 temp_r10_3;
    s32 temp_r10_4;
    s32 temp_r8_2;
    s32 temp_r9;
    s32 temp_r9_10;
    s32 temp_r9_2;
    s32 temp_r9_3;
    s32 temp_r9_4;
    s32 temp_r9_5;
    s32 temp_r9_6;
    s32 temp_r9_7;
    s32 temp_r9_8;
    s32 temp_r9_9;
    s32 var_ctr;
    s32 var_r10;
    s32 var_r10_3;
    s32 var_r10_4;
    s32 var_r10_5;
    s32 var_r11;
    s32 var_r31_2;
    s32 var_r5;
    s32 var_r9;
    u8* temp_r8;
    u8* var_r6;
    u32* var_r12;
    u8 temp_r10;
    u8 var_r10_2;
    u8 var_r31;
    void* temp_r11;

    var_r6 = string;
    sp10 = 0;
    var_r9 = 0;
    var_r5 = 0;
loop_42:
    if (var_r5 < 0x80) {
        temp_r8 = &string[var_r5];
        temp_r10 = (u8) *temp_r8;
        if (temp_r10 == '\0') {
            if (sp10 != 0) {
                data[var_r9] = 0xB;
                var_r9 += 1;
            }
        } else {
            if (temp_r10 == ' ') {
                var_r10 = sp10;
                if (var_r10 == 0) {
                    data[var_r9++] = 0xA;
                    data[var_r9++] = 0xF4;
                    data[var_r9++] = 0x0;
                    var_r10_3 += 1;
                    data[var_r9++] = 0x0;
                    data[var_r9++] = 0x0;
                    var_r9++;
                }
                sp10 = var_r10;
                var_r10_2 = 0x81;
                var_r31 = 0x40;
            } else if (temp_r10 == '"') {
                data[var_r9] = 0xB;
                var_r9 += 1;
                sp10 = 0;
                var_r10_2 = 0x81;
                var_r31 = 0x68;
            } else if (temp_r10 == '\'') {
                data[var_r9] = 0xB;
                var_r9 += 1;
                sp10 = 0;
                var_r10_2 = 0x81;
                var_r31 = 0x66;
            } else if (temp_r10 == ',') {
                data[var_r9] = 0xB;
                var_r9 += 1;
                sp10 = 0;
                var_r10_2 = 0x81;
                var_r31 = 0x43;
            } else if (temp_r10 == '-') {
                data[var_r9] = 0xB;
                var_r9 += 1;
                sp10 = 0;
                var_r10_2 = 0x81;
                var_r31 = 0x7C;
            } else if (temp_r10 == '.') {
                var_r10_3 = sp10;
                if (var_r10_3 == 0) {
#if 0
                    data[var_r9] = 0xA;
                    temp_r9_4 = var_r9 + 1;
                    data[var_r9].unk1 = 0xF4;
                    temp_r9_5 = temp_r9_4 + 1;
                    data[temp_r9_4].unk1 = 0;
                    temp_r9_6 = temp_r9_5 + 1;
                    var_r10_3 += 1;
                    data[temp_r9_5].unk1 = 0;
                    data[temp_r9_6].unk1 = 0;
                    var_r9 = temp_r9_6 + 1 + 1;
#endif
                }
                sp10 = var_r10_3;
                var_r10_2 = 0x81;
                var_r31 = 0x44;
            } else if ((temp_r10 >= '0') && (temp_r10 <= '9')) {
                var_r11 = sp10;
                var_r10_4 = var_r9;
                if (var_r11 == 0) {
#if 0
                    data[var_r10_4] = 0xA;
                    temp_r10_2 = var_r10_4 + 1;
                    data[var_r10_4].unk1 = 0xF4;
                    temp_r10_3 = temp_r10_2 + 1;
                    data[temp_r10_2].unk1 = 0;
                    temp_r10_4 = temp_r10_3 + 1;
                    var_r11 += 1;
                    data[temp_r10_3].unk1 = 0;
                    data[temp_r10_4].unk1 = 0;
                    var_r10_4 = temp_r10_4 + 1 + 1;
#endif
                }
                sp10 = var_r11;
                var_r9 = var_r10_4;
                var_r10_2 = 0x82;
                var_r31 = (u8) *temp_r8 + 0x1F;
            } else if (temp_r10 == ':') {
                var_r10_5 = sp10;
                if (var_r10_5 == 0) {
#if 0
                    data[var_r9] = 0xA;
                    temp_r9_7 = var_r9 + 1;
                    data[var_r9].unk1 = 0xF4;
                    temp_r9_8 = temp_r9_7 + 1;
                    data[temp_r9_7].unk1 = 0;
                    temp_r9_9 = temp_r9_8 + 1;
                    var_r10_5 += 1;
                    data[temp_r9_8].unk1 = 0;
                    data[temp_r9_9].unk1 = 0;
                    var_r9 = temp_r9_9 + 1 + 1;
#endif
                }
                sp10 = var_r10_5;
                var_r10_2 = 0x81;
                var_r31 = 0x46;
            } else if ((temp_r10 >= 'A') && (temp_r10 <= 'Z')) {
                data[var_r9] = 0xB;
                sp10 = 0;
                var_r9 += 1;
                var_r10_2 = 0x82;
                var_r31 = (u8) *temp_r8 + 0x1F;
            } else if ((temp_r10 >= 'a') && (temp_r10 <= 'z')) {
                data[var_r9] = 0xB;
                sp10 = 0;
                var_r9 += 1;
                var_r10_2 = 0x82;
                var_r31 = (u8) *temp_r8 + 0x20;
            } else {
                data[var_r9] = 0xB;
                var_r9 += 1;
                sp10 = 0;
                var_r10_2 = (u8) string[var_r5];
                var_r5 += 1;
                var_r31 = var_r6[1];
                var_r6 += 1;
            }
            var_ctr = 0x11F;
            var_r12 = lbl_8040C8C0;
            var_r31_2 = 0;
#if 0
loop_37:
            if ((var_r10_2 == (u8) var_r12->unk0) && (var_r31 == (u8) var_r12->unk1)) {
                temp_r11 = HSD_SisLib_8040C680 + (var_r31_2 * 2);
                temp_r9_10 = var_r9 + 1;
                data[var_r9] = temp_r11->unk0;
                temp_r8_2 = temp_r9_10;
                var_r9 = temp_r9_10 + 1;
                data[temp_r8_2] = temp_r11->unk1;
            } else {
                var_r12 += 2;
                var_r31_2 += 1;
                var_ctr -= 1;
                if (var_ctr != 0) {
                    goto loop_37;
                }
            }
#endif
            var_r5 += 1;
            var_r6 += 1;
            goto loop_42;
        }
    }
    data[var_r9] = 0;
    return var_r9;
}

void HSD_SisLib_803A6B98(HSD_Text* arg0, void* arg1, ...)
{
    s8 sp10C;
    HSD_Text** sp88;
    f64* sp84;
    s32 sp80;
    f64 sp60;
    f64 sp58;
    f64 sp50;
    f64 sp48;
    f64 sp40;
    f64 sp38;
    f64 sp30;
    f64 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    void* spC;
    HSD_Text* sp8;
    s16 temp_r0_3;
    s16 temp_r7;
    s32 temp_r3_16;
    s32 var_ctr_2;
    s32 var_r29;
    s32 var_r4_2;
    s32 var_r7;
    sislib_UnkAllocData* temp_r30;
    sislib_UnkAllocData* temp_r3_10;
    sislib_UnkAllocData* temp_r3_11;
    sislib_UnkAllocData* temp_r3_12;
    sislib_UnkAllocData* temp_r3_13;
    sislib_UnkAllocData* temp_r3_14;
    sislib_UnkAllocData* temp_r3_15;
    sislib_UnkAllocData* temp_r3_17;
    sislib_UnkAllocData* temp_r3_18;
    sislib_UnkAllocData* temp_r3_2;
    sislib_UnkAllocData* temp_r3_3;
    sislib_UnkAllocData* temp_r3_4;
    sislib_UnkAllocData* temp_r3_5;
    sislib_UnkAllocData* temp_r3_6;
    sislib_UnkAllocData* temp_r3_7;
    sislib_UnkAllocData* temp_r3_8;
    sislib_UnkAllocData* temp_r3_9;
    sislib_UnkAllocData* temp_r4_3;
    sislib_UnkAllocData* temp_r5;
    sislib_UnkAllocData* temp_r5_2;
    sislib_UnkAllocData* temp_r5_3;
    sislib_UnkAllocData* temp_r5_4;
    sislib_UnkAllocData* temp_r5_5;
    sislib_UnkAllocData* temp_r5_6;
    sislib_UnkAllocData* temp_r5_7;
    sislib_UnkAllocData* temp_r5_8;
    HSD_Text* temp_r31;
    u8* temp_r3;
    u8* var_r4;
    u8* var_r5;
    u32 temp_r0;
    u32 temp_r4;
    u32 var_ctr;
    u8* var_r3;
    u8* var_r5_2;
    u8 temp_r0_2;
    u8 temp_r4_2;
    u8 temp_r6;
    u8* playhead;
    va_list args;

    // @todo: what size is this?
    u8 sp8C;

    var_r29 = 0; // some type of size
    temp_r30 = arg0->x64;
    sp8C = 0;
    if (arg1) {
        // @todo: is this the correct usage of vaargs?
        u8 buffer[256];
        va_start(args, arg1);
        vsnprintf((char*) buffer, -1, arg1, args);
        va_end(args);
        var_r29 = HSD_SisLib_803A67EC(&sp8C, buffer);
    }

    // some sort of copy of a dynamically-sized struct
    {
        // It would appear that data_1 is allocated right after data_0 in
        // memory.
        u8* temp_r31 = (u8*) temp_r30->data_1;
        temp_r4 = temp_r30->size;
        temp_r0 = var_r29 + (((u8*) temp_r30->data_0 - temp_r31) + 0x11);
        if (temp_r4 < temp_r0) {
            // make sure that this unsigned subtract doesn't overflow?
            temp_r30->size =
                temp_r4 + ((((u32) (temp_r0 - temp_r4) >> 7U) + 1) << 7);
            temp_r3 = HSD_SisLib_803A5798((s32) temp_r30->size);
            // clearly a handwritten memory copy
            {
                var_r5 = temp_r31;
                var_r4 = temp_r3;
                var_r7 = 0;
                while (var_r7 < (s32) (((u8*) temp_r30->data_0 -
                                        (u8*) temp_r30->data_1) +
                                       1))
                {
                    temp_r0_2 = *var_r5;
                    var_r7 += 1;
                    var_r5 += 1;
                    *var_r4 = temp_r0_2;
                    var_r4 += 1;
                }
            }
            temp_r30->data_1 = (HSD_Text*) temp_r3;
            arg0->x5C = (SIS*) temp_r3;
            temp_r30->data_0 =
                (sislib_UnkAllocData*) (temp_r3 +
                                        ((u8*) temp_r30->data_0 - temp_r31));
            HSD_SisLib_803A594C(temp_r31);
        }
    }

    playhead = (u8*) temp_r30;
    *(playhead++) = 7;
    var_r4_2 = 0;

    // @note: Is it just assuming these are always passed in?
    temp_r7 = *((s16*) args + 8);
    *((s16*) playhead++) = temp_r7 >> 8;
    *playhead++ = temp_r7;

    temp_r0_3 = *((s16*) arg1 + 9);
    // *((s16 *)playhead)++ = temp_r0_3 >> 8;
    *playhead++ = temp_r0_3;

    *playhead++ = 0xC;

    *playhead++ = arg0->x30.x;
    *playhead++ = arg0->x30.y;
    *playhead++ = arg0->x30.z;
    *playhead++ = 0xE;
    *playhead++ = arg0->x30.w;
    *playhead++ = (u8) (s32) (arg0->x34.x);
    *playhead++ = (u8) (s32) (256.0f * arg0->x34.x);
    *playhead++ = (u8) (s32) (arg0->x34.y);
    *playhead++ = (u8) (s32) (256.0f * arg0->x34.y);

    if (var_r29 > 0) {
        /*
        This copies sets of 8 bytes individually, presumably from
        whatever HSD_SisLib_803A67EC returned. The second part of
        the loop copies any remaining bytes that aren't modulo 8.
        Maybe they had intended for the first part to be a "fast"
        copy, only for the compiler to output essentially the
        same operations for both?
        */
        temp_r3_16 = var_r29 - 8;
        if (var_r29 > 8) {
            var_ctr = (u32) (temp_r3_16 + 7) >> 3U;
            var_r3 = &sp8C;
            if (temp_r3_16 > 0) {
                do {
                    int i;
                    var_r4_2 += 8;
                    for (i = 0; i < 8; i++) {
                        *playhead++ = var_r3[i];
                    }
                    var_r3 += 8;
                    var_ctr -= 1;
                } while (var_ctr != 0);
            }
        }
        var_r5_2 = &sp8C + var_r4_2;
        var_ctr_2 = var_r29 - var_r4_2;
        if (var_r4_2 < var_r29) {
            do {
                *playhead++ = *var_r5_2++;
                var_ctr_2 -= 1;
            } while (var_ctr_2 != 0);
        }
    }
    *playhead++ = 0xF;
    *playhead++ = 0xD;
    *playhead = 0;
    *((s32*) playhead + 2) = *((s32*) playhead + 2) + 1;
}

// TODO there seems to be a file boundary before this function,
// because its data section is 8-byte aligned after the previous C strings
u8* fn_803A6FEC(u8* arg0, s32 arg1, s32* arg2)
{
    s32 var_r4;
    u8 var_r4_2;
    u8* var_r3;
    u8* var_r6;
    u8 temp_r0;
    u8 temp_r0_2;

    for (;;) {
        switch (*arg0) {
        case 0:
            return NULL;
        case 12:
            arg0 += 3;
        case 11:
        case 13:
        case 15:
            break;
        case 7:
            arg1 -= 1;
            if (arg1 < 0) {
                goto end;
            }
        /* fallthrough */
        case 10:
        case 14:
            arg0 += 4;
            break;
        default:
            arg0 += 1;
            break;
        }
        arg0 += 1;
    }
end:
    if (arg2 != NULL) {
        *arg2 = 0;
        var_r6 = arg0 + 0xE;
        do {
            var_r4_2 = 0;
            if (*var_r6 >= 32) {
                var_r4_2 = 2;
            } else if (*var_r6 == 10) {
                var_r4_2 = 5;
            } else if (*var_r6 == 11) {
                var_r4_2 = 1;
            }
            *arg2 += var_r4_2;
            var_r6 += var_r4_2;
        } while (var_r4_2 != 0);
    }
    return arg0;
}

void HSD_SisLib_803A746C(HSD_Text* arg0, s32 arg1, f32 arg2, f32 arg3)
{
    s16 temp_r0;
    s16 temp_r0_2;
    u8* temp_r3;
    u8* temp_r3_2;

    temp_r3 = fn_803A6FEC((u8*) arg0->x5C, arg1, NULL);
    if (temp_r3 != NULL) {
        temp_r0 = arg2;
        temp_r0_2 = arg3;
        temp_r3_2 = temp_r3 + 1;
        temp_r3_2[0] = (u8) (temp_r0 >> 8);
        temp_r3_2[1] = (u8) temp_r0;
        temp_r3_2[2] = (u8) (temp_r0_2 >> 8);
        temp_r3_2[3] = (u8) temp_r0_2;
    }
}

void HSD_SisLib_803A74F0(HSD_Text* arg0, s32 arg1, u8* arg2)
{
    u8* temp_r3;
    u8* temp_r3_2;
    void* temp_r31;

    temp_r3 = fn_803A6FEC((u8*) arg0->x5C, arg1, NULL);
    if (temp_r3 != NULL) {
        temp_r3_2 = temp_r3 + 5;
        temp_r3_2[1] = arg2[0];
        temp_r3_2[2] = arg2[1];
        temp_r3_2[3] = arg2[2];
    }
}

void HSD_SisLib_803A7548(HSD_Text *arg0, int arg1, float arg2, float arg3)
{
    u8* temp_r3 = fn_803A6FEC((u8*) arg0->x5C, arg1, NULL);
    u8* temp_r4;
    if (temp_r3 != NULL) {
        temp_r4 = temp_r3 + 9;
        temp_r4[0] = arg2;
        temp_r4[1] = 256.0F * arg2;
        temp_r4[2] = arg3;
        temp_r4[3] = 256.0F * arg3;
    }
}

void HSD_SisLib_803A8134(void* arg0, HSD_Text* arg1, f32* arg2, f32* arg3)
{
    SIS* temp_r4;
    TextGlyphTexture* var_r29;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f24;
    f32 temp_f25;
    f32 temp_f26;
    u16 temp_r0;
    u16 temp_r27;
    u16 temp_r3_3;
    u16 var_r5;
    u32 temp_r3_2;
    u8* temp_r4_3;
    u8 temp_r3;
    u8 var_r28;
    u8* temp_r4_2;
    u8* var_r23;
    PAD_STACK(8);

    var_r23 = arg0;
    temp_f26 = arg1->x80.x;
    temp_f25 = arg1->x80.y;
    temp_f24 = arg1->x78.x;
    var_r28 = arg1->x9D;
    temp_r4 = HSD_SisLib_804D1124[arg1->x4F];
    temp_r27 = arg1->x6C;
    if (temp_r4 != NULL) {
        var_r29 = temp_r4->textures;
    }
    *arg2 = 0.0f;
    *arg3 = 32.0f * arg1->x80.y;
loop_3:
    temp_r3 = *var_r23;
    switch (temp_r3) {
    case 0:
        temp_r3_2 = HSD_SisLib_803A7F0C(arg1, 0x85);
        if (temp_r3_2 != 0U) {
            *var_r23 = temp_r3_2 + 4;
        block_33:
            var_r23 += 1;
            goto loop_3;
        }
        break;
    case 9:
        HSD_SisLib_803A7684(arg1, *var_r23, 0x85U);
        /* fallthrough */
    case 8:
        var_r23 = var_r23 - 1;
        goto block_33;
    case 14:
        HSD_SisLib_803A7684(arg1, *var_r23, 0x83U);
        arg1->x80.x = *((f32*) ((u16*) var_r23 + 1)) * 0.00390625f;
        temp_r0 = *(u16*) (var_r23 + 3);
        var_r23 += 4;
        arg1->x80.y = (f32) temp_r0 * 0.00390625f;
        goto block_33;
    case 15:
        HSD_SisLib_803A7F0C(arg1, 0x83);
        goto block_33;
    case 6:
        var_r23 += 4;
        goto block_33;
    case 10:
        if (((sislib_UnkAllocData*) arg1->x64 == NULL) || ((s16) var_r28 == 0))
        {
            HSD_SisLib_803A7684(arg1, *var_r23, 0x81U);
            arg1->x78.x = (f32) (s16) * (var_r23 + 1) * 0.00390625f;
        }
        var_r23 += 4;
        goto block_33;
    case 11:
        if (((sislib_UnkAllocData*) arg1->x64 == NULL) || ((s16) var_r28 == 0))
        {
            HSD_SisLib_803A7F0C(arg1, 0x81);
        }
        goto block_33;
    case 12:
        var_r23 += 3;
        goto block_33;
    case 5:
        var_r23 += 2;
        goto block_33;
    case 22:
        var_r28 = 1;
        goto block_33;
    case 23:
        var_r28 = 0;
        goto block_33;
    case 26:
        *arg2 += arg1->x80.x * (16.0f + arg1->x78.x);
        temp_f0 = 32.0f * arg1->x80.y;
        if (*arg3 < temp_f0) {
            *arg3 = temp_f0;
        }
        goto block_33;
    default:
        if (temp_r3 >= 0x20U) {
            *arg2 += arg1->x80.x * (32.0f + arg1->x78.x);
            if ((s16) var_r28 != 0) {
                temp_r3_3 = (u16) *var_r23;
                if (temp_r3_3 < 0x4000U) {
                    temp_r4_2 = (u8*) &HSD_SisLib_8040CB00 +
                                (((temp_r3_3 - 0x2000) * 2) & 0x1FFFE);
                    *arg2 = -((arg1->x80.x *
                               (f32) (*temp_r4_2 + (temp_r4_2[1] - 2))) -
                              *arg2);
                } else {
                    temp_r4_3 =
                        &var_r29->data[((temp_r3_3 - 0x4000) * 2) & 0x1FFFE];
                    *arg2 = -((arg1->x80.x *
                               (f32) (*temp_r4_3 + (temp_r4_3[1] - 2))) -
                              *arg2);
                }
            }
            temp_f0_2 = 32.0f * arg1->x80.y;
            if (*arg3 < temp_f0_2) {
                *arg3 = temp_f0_2;
            }
            var_r23 += 1;
        }
        goto block_33;
    }
    *arg2 -= arg1->x78.x;
    arg1->x80.x = temp_f26;
    arg1->x80.y = temp_f25;
    arg1->x78.x = temp_f24;
    arg1->x6C = temp_r27;
    var_r5 = arg1->x6C;
loop_36:
    if ((s32) var_r5 < (s32) arg1->x6E) {
        *((u8*) arg1->x68 + var_r5) = 0;
        var_r5 += 1;
        goto loop_36;
    }
}

void static inline HSD_SisLib_803A7F0C_inline(HSD_Text* arg0, s32 arg1,
                                              s32* var_r4, u32* var_r5,
                                              s32* var_r0)
{
    s32* temp_r8;
    u8 temp_r7;
    s32 temp_r6;
    s32 temp_r10;
    s32 temp_r11;
    s32 temp_r9;
    temp_r9 = arg1 & 0x80;
    temp_r11 = arg1 & 0x7F;
    while (*var_r5 >= 0) {
        temp_r8 = (s32*) arg0->x68;
        temp_r7 = *(temp_r8 + *var_r5);
        temp_r6 = temp_r7 & 0x7F;
        temp_r10 = temp_r7 & 0x80;
        switch (temp_r6) { /* irregular */
        case 1:
            *var_r5 -= 4;
            if (temp_r11 == 1) {
                arg0->x78.x = (f32) * (temp_r8 + *var_r5) * 0.00390625f;
                arg0->x78.y = (f32) * (temp_r8 + (*var_r5 + 2)) * 0.00390625f;
                if (temp_r9 == temp_r10) {
                    *var_r4 = 5;
                }
            } else {
                break;
            }
            return;
        case 2:
            *var_r5 -= 3;
            if (temp_r11 == 2) {
                arg0->x8C.x = ((U8Vec4*) arg0->x68 + *var_r5)->x;
                arg0->x8C.y = ((U8Vec4*) arg0->x68 + *var_r5)->y;
                arg0->x8C.z = ((U8Vec4*) arg0->x68 + *var_r5)->z;
                if (temp_r9 == temp_r10) {
                    *var_r4 = 4;
                }
            } else {
                break;
            }
            return;
        case 3:
            *var_r5 -= 4;
            if (temp_r11 == 3) {
                arg0->x80.x = (f32) * (temp_r8 + *var_r5) * 0.00390625f;
                arg0->x80.y = (f32) * (temp_r8 + (*var_r5 + 2)) * 0.00390625f;
                if (temp_r9 == temp_r10) {
                    *var_r4 = 5;
                }
            } else {
                break;
            }
            return;
        case 4:
            *var_r5 -= 1;
            if (temp_r11 == 4) {
                arg0->x9E = *(temp_r8 + *var_r5);
                if (temp_r9 == temp_r10) {
                    *var_r4 = 2;
                }
            } else {
                break;
            }
            return;
        case 5:
            *var_r5 -= 4;
            if (temp_r11 == 5) {
                *var_r0 = *(temp_r8 + *var_r5);
                if (temp_r9 == temp_r10) {
                    *var_r4 = 5;
                }
            } else {
                break;
            }
            return;
        }
        *var_r5 -= 1;
    }
}

s32 HSD_SisLib_803A7F0C(HSD_Text* arg0, s32 arg1)
{
    s32 temp_r7_2;
    s32 var_r0;
    s32 var_r4;
    u16 temp_r6_2;
    u32 var_r5;

    var_r5 = arg0->x6C;
    var_r0 = 0;
    var_r4 = 0;
    HSD_SisLib_803A7F0C_inline(arg0, arg1, &var_r4, &var_r5, &var_r0);
    if (var_r4 != 0) {
        while ((s32) (var_r5 + var_r4) < (s32) arg0->x6C) {
            *((s32*) arg0->x68 + var_r5) =
                *((s32*) arg0->x68 + var_r5 + var_r4);
            var_r5 += 1;
        }
        while ((s32) var_r5 < (s32) arg0->x6C) {
            *((s32*) arg0->x68 + var_r5) = 0;
            var_r5 += 1;
        }
        arg0->x6C -= var_r4;
    }
    return var_r0;
}

void HSD_SisLib_803A84BC(HSD_GObj* gobj, int arg1)
{
    // clang-format off
    HSD_Text *var_r31;
    Mtx m;
    TextGlyphTexture *textures = NULL;
    TextKerning *kerning = NULL;

    Vec2 min;
    Vec2 max;

    u8 spB8;
    u8 spB9;
    u8 spBA;
    u8 spBB;
    u8 spBC;
    f32 spC0;
    Vec2 spC4;
    Vec2 spCC;
    u16 var_r23;
    u16 var_r19;
    u32 var_r28;
    u16 temp_r14;
    u8 temp_r22;

    u8 *data = &HSD_SisLib_8040CD40;


    if (gobj != NULL) {
        if (arg1 == 2) {
            var_r31 = gobj->user_data;
        } else {
            var_r31 = NULL;
        }
    } else {
        var_r31 = (HSD_Text*) arg1;
    }
    if (var_r31->x4D == 0 && var_r31->x5C != NULL) {
        u8 *var_r30 = (u8 *)var_r31->x5C;
        if (gobj != NULL) {
            SIS *temp_r3 = HSD_SisLib_804D1124[var_r31->x4F];
            if (temp_r3 != NULL) {
                kerning = temp_r3->kerning;
                textures = temp_r3->textures;
            }
        }
        if (gobj != NULL) {
            if (var_r31->x4C != 0) {
                HSD_StateSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
            } else {
                HSD_StateSetZMode(GX_FALSE, GX_NEVER, GX_FALSE);
            }
            HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), (MtxPtr)&m);
        } else {
            GXSetZMode(0U, 0U, 0U);
            GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
            GXSetScissor(0, 0, 0x280, 0x1E0);
            MTXOrtho((MtxPtr)&m, 0.0f, -480.0f, 0.0f, 640.0f, 0.0f, 2.0f);
            GXSetProjection((MtxPtr)&m, 0);
            m[0][0] = 1.0f;
            m[0][1] = 0.0f;
            m[0][2] = 0.0f;
            m[0][3] = 0.0f;
            m[1][0] = 0.0f;
            m[1][1] = 1.0f;
            m[1][2] = 0.0f;
            m[1][3] = 0.0f;
            m[2][0] = 0.0f;
            m[2][1] = 0.0f;
            m[2][2] = 1.0f;
            m[2][3] = -1.0f;
        }
        GXSetCurrentMtx(0);
        GXLoadPosMtxImm((MtxPtr)&m, 0);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_DISABLE, GX_PTIDENTITY);
        if (gobj != NULL) {
            HSD_StateSetNumChans(0);
        } else {
            GXSetNumChans(0U);
        }
        GXClearVtxDesc();
        GXSetCullMode(GX_CULL_NONE);
        GXSetNumTexGens(1U);
        GXSetNumTevStages(1U);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_RGBA6, 0);
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_POS_XYZ, GX_RGBA6, 0);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
        GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_OR, GX_GREATER, GX_NEVER);
        GXSetColorUpdate(GX_ENABLE);
        GXSetAlphaUpdate(GX_DISABLE);
        if (gobj != NULL) {
            if (var_r31->x58 != NULL) {
                var_r31->x58(gobj);
            }
        }
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        // @todo: What is this first quad for?
        if (var_r31->x2C.w != 0) {
            f32 temp_f4 = var_r31->x0;
            f32 temp_f5 = var_r31->x4;
            min.x = temp_f4;
            min.y = temp_f5;
            max.x = (var_r31->xC  * var_r31->x24.x) + temp_f4;
            max.y = (var_r31->x10 * var_r31->x24.y) + temp_f5;
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
            GXSetTevColor(GX_TEVREG0, *(GXColor *)&var_r31->x2C);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4U);
            // @note: could be inlined
            {
                f32 temp_f2 = var_r31->x8;
                f32 temp_f3 = -min.y;
                f32 temp_f4_2 = -max.y;
                GXPosition3f32(min.x, temp_f3, temp_f2);
                GXTexCoord2f32(0.0F, 0.0F);
                GXPosition3f32(max.x, temp_f3, temp_f2);
                GXTexCoord2f32(1.0F, 0.0F);
                GXPosition3f32(max.x, temp_f4_2, temp_f2);
                GXTexCoord2f32(1.0F, 1.0F);
                GXPosition3f32(min.x, temp_f4_2, temp_f2);
                GXTexCoord2f32(1.0F, 1.0F);
            }
        }
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
        if (var_r31->x4E != 0) {
            min.x = (var_r31->x14.z * var_r31->x24.x) + var_r31->x0;
            max.x = (var_r31->x24.x * (var_r31->xC - var_r31->x14.w)) + var_r31->x0;
            min.y = (var_r31->x14.x * var_r31->x24.y) + var_r31->x4;
            max.y = (var_r31->x24.y * (var_r31->x10 - var_r31->x14.y)) + var_r31->x4;
        }
        if (var_r31->x64 != NULL) {
            var_r31->x78.x = var_r31->x3C.x;
            var_r31->x78.y = var_r31->x3C.y;
            // interesting pattern... is there a U8Vec3?
            var_r31->x9E = var_r31->x4A;
            var_r31->x9D = var_r31->x49;
            var_r31->x9C = var_r31->x48;
        }
        {
            f32 sp60;
            f32 sp64 = 0;
            f64 spD8 = 16.0;

            u32 var_r26 = 0U;
            temp_r22 = var_r31->x9D;
            var_r31->x74 = 0.0f;
            spCC = var_r31->x80;
            spBC = var_r31->x8C.x;
            spBB = var_r31->x8C.y;
            spBA = var_r31->x8C.z;
            spC4.y = var_r31->x80.y;
            spC4.x = var_r31->x78.x;
            spB8 = var_r31->x9E;
            spC0 = var_r31->x78.y;
            spB9 = var_r31->x9C;
            var_r23 = var_r31->x90;
            var_r19 = var_r31->x92;
            var_r28 = var_r31->x98;
            temp_r14 = var_r31->x6C;
            // this is the compare for the loop
            while ((var_r30 != var_r31->x60) || ((u8) var_r31->x4B == 0)) {
                if ((var_r30 == var_r31->x60) && var_r31->x94) {
                    var_r31->x94--;
                } else {
                    u32 temp_r3_4;
                    s32 var_r3;
                    f32 temp_f0;
                    s16 temp_r0_4;
                    u8 temp_r0_2 = *var_r30;
                    switch (*var_r30) {
                        case 0:
                            temp_r3_4 = HSD_SisLib_803A7F0C(var_r31, 5);
                            if (temp_r3_4 != 0U) {
                                *(u32 *)var_r30 = temp_r3_4 + 4;
                            }
                            break;
                        case 1:
                            var_r31->x60 = NULL;
                            var_r3 = 0;
                            var_r31->x8C = var_r31->x30;
                            var_r31->x80.x = var_r31->x34.x;
                            var_r31->x80.y = var_r31->x34.y;
                            var_r31->x78.x = var_r31->x3C.x;
                            var_r31->x78.y = var_r31->x3C.y;
                            var_r31->x90 = var_r31->x44;
                            var_r31->x92 = var_r31->x46;
                            var_r31->x9E = var_r31->x4A;
                            var_r31->x9D = var_r31->x49;
                            var_r31->x9C = var_r31->x48;
                            var_r31->x94 = 0U;
                            var_r31->x4B = 0U;
                            while (var_r3 < (s32) var_r31->x6E) {
                                *((u8 *)var_r31->x68 + var_r3) = 0;
                                var_r3 += 1;
                            }
                            var_r31->x6C = 0;
                            /* fallthrough */
                        case 2:
                            var_r31->x98 = 0;
                            var_r30 += 1;
                            var_r31->x5C = (SIS *)var_r30;
                            break;
                        case 3:
                            if (var_r26 == 0U) {
                                sp60 = 32.0f * var_r31->x80.x;
                            }
                            var_r26 = 0U;
                            var_r31->x74 = (f32) ((var_r31->x24.x * ((var_r31->x80.x * var_r31->x78.y) + sp60)) + var_r31->x74);
                            if (var_r28 != 0U) {
                                var_r28 -= 1;
                            } else {
                                var_r31->x98 = (u32) (var_r31->x98 + 1);
                                var_r31->x94 = (u32) var_r19;
                                var_r31->x60 = (void *) (var_r30 + 1);
                            }
                            break;
                        case 4:
                            if (var_r28 != 0U) {
                                var_r28 -= 1;
                            } else {
                                var_r31->x98 = (u32) (var_r31->x98 + 1);
                                var_r31->x4B = 1U;
                                var_r31->x60 = (void *) (var_r30 + 1);
                            }
                            break;
                        case 5:
                            if (var_r28 != 0U) {
                                var_r28 -= 1;
                            } else {
                                var_r31->x98 = (u32) (var_r31->x98 + 1);
                                var_r31->x94 = *((u8 *)var_r30 + 1);
                                var_r31->x60 = (void *) (var_r30 + 3);
                            }
                            var_r30 += 2;
                            break;
                        case 6:
                            var_r23 = *((u8 *)var_r30 + 1);
                            var_r19 = *((u8 *)var_r30 + 3);
                            var_r30 += 4;
                            break;
                        case 7:
                            var_r26 = 1U;
                            // HSD_SisLib_803A8134();
                            temp_f0 = (f32) *((u8 *)var_r30 + 1);
                            if (((u8) var_r31->x9C == 1) && (var_r31->xC < sp64) != 0) {
                                var_r31->x88 = (f32) (var_r31->xC / sp64);
                            } else {
                                var_r31->x88 = 1.0f;
                            }
                            switch ((s32) var_r31->x9E) {
                            case 1:
                                var_r31->x70 = (f32) -((0.5f * (sp64 * var_r31->x88)) - temp_f0);
                                break;
                            case 2:
                                var_r31->x70 = (f32) -((sp64 * var_r31->x88) - temp_f0);
                                break;
                            default:
                                var_r31->x70 = temp_f0;
                                break;
                            }
                            temp_r0_4 = *((u8 *)var_r30 + 3);
                            var_r30 += 4;
                            var_r31->x74 = (f32) ((f32) temp_r0_4 * var_r31->x24.y);
                            break;
                        case 9:
                            HSD_SisLib_803A7684(var_r31, *var_r30, 5U);
                            /* fallthrough */
                        case 8:
                            var_r30 -= 4;
                            break;
                        case 10:
                            if (((u32) var_r31->x64 == 0U) || (temp_r22 == 0)) {
                                HSD_SisLib_803A7684(var_r31, *var_r30, 1U);
                                var_r31->x78.x = (f32) ((f32) (s16)var_r30[1] * 0.00390625f);
                                var_r31->x78.y = (f32) ((f32) (s16)var_r30[3] * 0.00390625f);
                            }
                            var_r30 += 4;
                            break;
                        case 11:
                            if (((u32) var_r31->x64 == 0U) || (temp_r22 == 0)) {
                                HSD_SisLib_803A7F0C(var_r31, 1);
                            }
                            break;
                        case 12:
                            HSD_SisLib_803A7684(var_r31, *var_r30, 2U);
                            var_r31->x8C.x = var_r30[1];
                            var_r31->x8C.y = var_r30[2];
                            var_r31->x8C.z = var_r30[3];
                            var_r30 += 3;
                            break;
                        case 13:
                            HSD_SisLib_803A7F0C(var_r31, 2);
                            break;
                        case 14:
                            HSD_SisLib_803A7684(var_r31, *var_r30, 3U);
                            var_r31->x80.x = (f32) ((f32) (s16)var_r30[1] * 0.00390625f);
                            var_r31->x80.y = (f32) ((f32) (s16)var_r30[2] * 0.00390625f);
                            var_r30 += 4;
                            break;
                        case 15:
                            HSD_SisLib_803A7F0C(var_r31, 3);
                            break;
                        case 16:
                            HSD_SisLib_803A7684(var_r31, *var_r30, 4U);
                            var_r31->x9E = 1U;
                            break;
                        case 18:
                            HSD_SisLib_803A7684(var_r31, *var_r30, 4U);
                            var_r31->x9E = 0U;
                            break;
                        case 20:
                            HSD_SisLib_803A7684(var_r31, *var_r30, 4U);
                            var_r31->x9E = 2U;
                            break;
                        case 17:
                        case 19:
                        case 21:
                            HSD_SisLib_803A7F0C(var_r31, 4);
                            break;
                        case 22:
                            var_r31->x9D = 1U;
                            break;
                        case 23:
                            var_r31->x9D = 0U;
                            break;
                        case 24:
                            var_r31->x9C = 1U;
                            break;
                        case 25:
                            var_r31->x9C = 0U;
                            break;
                        case 26:
                            if (var_r26 == 0U) {
                                var_r26 += 1;
                                // HSD_SisLib_803A8134();
                                if (((u8) var_r31->x9C == 1) && (var_r31->xC < sp64)) {
                                    var_r31->x70 = 0.0f;
                                    var_r31->x88 = (f32) (var_r31->xC / sp64);
                                } else {
                                    var_r31->x88 = 1.0f;
                                    switch ((s32) var_r31->x9E) {
                                    case 1:
                                        var_r31->x70 = (f32) (0.5f * (var_r31->xC - sp64));
                                        break;
                                    case 2:
                                        var_r31->x70 = (f32) (var_r31->xC - sp64);
                                        break;
                                    default:
                                        var_r31->x70 = 0.0f;
                                        break;
                                    }
                                }
                            }
                            var_r31->x70 = (f32) (((f64) var_r31->x88 * ((f64) var_r31->x80.x *
                                            (spD8 + (f64) var_r31->x78.x))) + (f64) var_r31->x70);
                            if (var_r28 != 0U) {
                                var_r28 -= 1;
                            } else {
                                var_r31->x98 = (u32) (var_r31->x98 + 1);
                                var_r31->x94 = (u32) var_r23;
                                var_r31->x60 = (void *) (var_r30 + 1);
                            }
                            break;
                        default:
                            if (temp_r0_2 >= 0x20U) {
                                u16 temp_r24;
                                s32 var_r25;
                                f32 temp_f2_3;
                                f32 var_f31;
                                if (var_r26 == 0U) {
                                    var_r26 += 1;
                                    // HSD_SisLib_803A8134();
                                    if (((u8) var_r31->x9C == 1) && (var_r31->xC < sp64)) {
                                        var_r31->x70 = 0.0f;
                                        var_r31->x88 = (f32) (var_r31->xC / sp64);
                                    } else {
                                        var_r31->x88 = 1.0f;
                                        switch (var_r31->x9E) {
                                        case 1:
                                            var_r31->x70 = (f32) (0.5f * (var_r31->xC - sp64));
                                            break;
                                        case 2:
                                            var_r31->x70 = (f32) (var_r31->xC - sp64);
                                            break;
                                        default:
                                            var_r31->x70 = 0.0f;
                                            break;
                                        }
                                    }
                                }
                                temp_r24 = *(u16 *)var_r30;
                                if (temp_r24 < 0x4000U) {
                                    var_r25 = temp_r24 - 0x2000;
                                } else {
                                    var_r25 = temp_r24 - 0x4000;
                                }
                                temp_f2_3 = var_r31->x24.x;
                                var_f31 = (var_r31->x70 * temp_f2_3) + var_r31->x0;
                                if ((u8) var_r31->x9D != 0) {
                                    if (temp_r24 < 0x4000U) {
                                        var_f31 = -((temp_f2_3 * (var_r31->x80.x * (f32) (*(&HSD_SisLib_8040CB00 + ((var_r25 * 2) & 0x1FFFE)) - 1))) - var_f31);
                                    } else {
                                        var_f31 = -((temp_f2_3 * (var_r31->x80.x * (f32) (textures->data[(var_r25 * 2) & 0x1FFFE] - 1))) - var_f31);
                                    }
                                }
                                {
                                    GXTexObj sp98;
                                    f32 temp_f4_4 = 32.0f * var_r31->x80.x;
                                    f32 temp_f0_2 = var_r31->x24.y;
                                    f32 var_f21 = 0.0f;
                                    f32 temp_f1 = 32.0f * var_r31->x80.x * temp_f2_3;
                                    f32 temp_f3_2 = (temp_f0_2 * (sp60 - temp_f4_4)) + (var_r31->x4 + var_r31->x74);
                                    f32 temp_f0_3 = temp_f4_4 * temp_f0_2;
                                    f32 var_f22 = 1.0f;
                                    f32 var_f18 = 0.0f;
                                    f32 var_f27 = temp_f3_2;
                                    f32 var_f20 = 1.0f;
                                    f32 var_f29 = (var_r31->x88 * temp_f1) + var_f31;
                                    f32 var_f28 = temp_f3_2 + temp_f0_3;
                                    if ((u8) var_r31->x4E != 0) {
                                        if (!(min.x > var_f29) && !(max.x < var_f31) && !(min.y > var_f28) && !(max.y < var_f27)) {
                                            if (min.x > var_f31) {
                                                f32 temp_f2_4 = min.x - var_f31;
                                                var_f18 = temp_f2_4 / temp_f1;
                                                var_f31 += temp_f2_4;
                                            }
                                            if (max.x < var_f29) {
                                                f32 temp_f2_5 = var_f29 - max.x;
                                                var_f20 = 1.0f - (temp_f2_5 / temp_f1);
                                                var_f29 -= temp_f2_5;
                                            }
                                            if (min.y > var_f27) {
                                                f32 temp_f1_2 = min.y - var_f27;
                                                var_f21 = temp_f1_2 / temp_f0_3;
                                                var_f27 += temp_f1_2;
                                            }
                                            if (max.y < var_f28) {
                                                f32 temp_f1_3 = var_f28 - max.y;
                                                var_f22 = 1.0f - (temp_f1_3 / temp_f0_3);
                                                var_f28 -= temp_f1_3;
                                            }
                                        }
                                    }
                                    if (temp_r24 < 0x4000U) {
                                        GXInitTexObj(&sp98, &data + ((var_r25 << 9) & 0x01FFFE00), 0x20U, 0x20U, GX_TF_I4, GX_CLAMP, GX_CLAMP, 0U);
                                    } else {
                                        GXInitTexObj(&sp98, kerning + ((var_r25 << 9) & 0x01FFFE00), 0x20U, 0x20U, GX_TF_I4, GX_CLAMP, GX_CLAMP, 0U);
                                    }
                                    GXLoadTexObj(&sp98, GX_TEXMAP0);
                                    GXSetTevColor(GX_TEVREG0, *(GXColor*)&var_r31->x8C);
                                    GXBegin(GX_QUADS, GX_VTXFMT0, 4U);
                                    {
                                        f32 temp_f0_4 = var_r31->x8;
                                        f32 temp_f1_4 = -var_f27;
                                        f32 temp_f2_6 = -var_f28;
                                        GXPosition3f32(var_f31, temp_f1_4, temp_f0_4);
                                        GXTexCoord2f32(var_f18, var_f21);
                                        GXPosition3f32(var_f29, temp_f1_4, temp_f0_4);
                                        GXTexCoord2f32(var_f20, var_f21);
                                        GXPosition3f32(var_f29, temp_f2_6, temp_f0_4);
                                        GXTexCoord2f32(var_f20, var_f22);
                                        GXPosition3f32(var_f31, temp_f2_6, temp_f0_4);
                                        GXTexCoord2f32(var_f18, var_f22);
                                    }

                                    var_r31->x70 = (f32) ((var_r31->x80.y * (var_r31->x80.x * (32.0f + var_r31->x78.x))) + var_r31->x70);
                                    if ((u8) var_r31->x9D != 0) {
                                        if (temp_r24 < 0x4000U) {
                                            f32 *temp_r4 = &HSD_SisLib_8040CB00 + ((var_r25 * 2) & 0x1FFFE);
                                            var_r31->x70 = (f32) -((var_r31->x88 * (var_r31->x80.x * (f32) (temp_r4[0] + (temp_r4[1] - 2)))) - var_r31->x70);
                                        } else {
                                            u8 *temp_r4 = &textures->data[(var_r25 * 2) & 0x1FFFE];
                                            var_r31->x70 = (f32) -((var_r31->x88 * (var_r31->x80.x * (f32) (temp_r4[0] + (temp_r4[1] - 2)))) - var_r31->x70);
                                        }
                                    }
                                    if (var_r28 != 0U) {
                                        var_r28 -= 1;
                                    } else {
                                        var_r31->x98 = (u32) (var_r31->x98 + 1);
                                        var_r31->x94 = (u32) var_r23;
                                        var_r31->x60 = (void *) (var_r30 + 2);
                                    }
                                    var_r30 += 1;
                            }
                        }
                    }
                }
                var_r30++;
            }
            HSD_StateInvalidate(-1);
            var_r31->x8C.x = spBC;
            var_r31->x8C.y = spBB;
            var_r31->x8C.z = spBA;
            var_r31->x80.x = spCC.x;
            var_r31->x80.y = spCC.y;
            var_r31->x78.x = spC4.x;
            var_r31->x78.y = spC4.y;
            var_r31->x9E = spB8;
            var_r31->x9D = temp_r22;
            var_r31->x9C = spB9;
            var_r31->x6C = temp_r14;
            {
                s32 var_r5 = var_r31->x6C;
                while ((s32) var_r5 < (s32) var_r31->x6E) {
                    *((u8 *)var_r31->x68 + var_r5) = 0;
                    var_r5 += 1;
                }
            }
        }
    }
    // clang-format on
}
