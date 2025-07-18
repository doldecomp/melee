#include "lbcardnew.h"

#include "lbcardnew.static.h"

#include <dolphin/card.h>
#include <melee/lb/lb_0192.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/hsd_3AA7.h>
#include <sysdolphin/baselib/hsd_3B27.h>

int lb_80019BB8(int arg0)
{
    switch (arg0) {
    case -1:
    case -2:
    case -3:
        return 0xF;
    case -4:
        return 4;
    case 0:
        return 0;
    case -5:
    case -128:
        return 0xE;
    case -6:
    case -13:
        return 9;
    case 1:
    case -14:
    default:
        return 0xD;
    }
}

struct CardTask* lb_80019C38(void)
{
    int i;
    struct CardTask* result;

    for (i = 0; i < 0xB; i++) {
        result = &lb_80432A68.task_array[i];
        if (result->x0 == 0xE) {
            break;
        }
    }
    if (i == 0xB) {
        __assert("lbcardnew.c", 0x154, "i != LbCardNewTaskArray_Max");
    }
    return result;
}

static void reset_task_array(void)
{
    int i;
    for (i = 0; i < 11; i++) {
        lb_80432A68.task_array[i].x0 = 0xE;
    }
}

int lb_80019CB0(int var_r28)
{
    struct CardTask* task;
    int i;

again:

    i = 0;
    for (i = 0; i < 11; i++) {
        task = &lb_80432A68.task_array[i];
        if (lb_80432A68.task_array[i].x0 != 0xE) {
            break;
        }
    }
    if (i != 0xB) {
        if (!(task->x4 & (1 << var_r28))) {
            reset_task_array();
        } else {
            switch (task->x0) {
            case 0:
                var_r28 = lb_8001A184();
                break;
            case 1:
                var_r28 = lb_8001A3A4();
                break;
            case 2:
                var_r28 = lb_8001A594(task->xC, task->x8);
                break;
            case 3:
                var_r28 = lb_8001A860();
                break;
            case 4:
                var_r28 = lb_8001A8A4();
                break;
            case 5:
                var_r28 = lb_8001A9CC(task->x10);
                break;
            case 6:
                var_r28 = lb_8001AAE4(task->x10, task->x19);
                break;
            case 7:
                var_r28 = lb_8001AC04(&task->x10);
                break;
            case 8:
                var_r28 = lb_8001ACEC(task->x8);
                break;
            case 9:
                var_r28 = lb_8001AE38(task->x8);
                break;
            case 10:
                var_r28 = lb_8001AF84();
                break;
            case 11:
                var_r28 = lb_8001B068();
                break;
            case 12:
                var_r28 = lb_8001B14C();
                break;
            case 13:
                var_r28 = lb_8001B614(task->x10);
                break;
            }
            task->x0 = 0xE;
            if (var_r28 != 11) {
                goto again;
            }
        }
    }
    if (var_r28 != 11 && lb_80432A68.x50C != NULL) {
        lb_80432A68.x50C(var_r28);
        lb_80432A68.x50C = NULL;
    }
    if (var_r28 != 11 && lb_80432A68.unk_80 != 0) {
        CARDUnmount(lb_80432A68.chan);
        lb_80432A68.unk_80 = 0;
    }
    return var_r28;
}

void lb_80019EF0(int chan, UNK_T arg1, UNK_T arg2, UNK_T arg3)
{
    int i;

    lb_80432A68.chan = chan;
    lb_80432A68.unk_C = arg1;
    lb_80432A68.unk_10 = arg2;
    lb_80432A68.unk_14 = NULL;
    lb_80432A68.unk_18 = 0;
    lb_80432A68.unk_1C = 0;
    lb_80432A68.unk_20 = 0;
    lb_80432A68.unk_24 = NULL;
    lb_80432A68.unk_28 = NULL;
    lb_80432A68.unk_34 = 0x10;

    for (i = 0; i < 9; i++) {
        lb_80432A68.unk_38[i].unk_0 = 0x10;
        lb_80432A68.unk_38[i].unk_4 = -1;
    }

    lb_80432A68.unk_80 = 0;
    lb_80432A68.x50C = arg3;

    reset_task_array();
}

void fn_8001A008(s32 unused, s32 arg0)
{
    s32 var_r0;

    var_r0 = lb_80019BB8(arg0);

    if (var_r0 != 0) {
        lb_80432A68.unk_34 = var_r0;
    }
    lb_80432A68.x8AC -= 1;
}

static int convert_hsdcard_error(int arg1)
{
    int var_r3;
    switch (arg1) {
    case 0:
    case 1:
        var_r3 = 0;
        break;
    case -0x105:
    case -0x104:
    case -0x103:
    case -0x102:
        var_r3 = 2;
        break;
    case -0x107:
    case -0x106:
    case -0x101:
        var_r3 = 3;
        break;
    case -0x108:
    case -0x109:
    case -0x10A:
    case -0x10B:
        var_r3 = 10;
        break;
    default:
        var_r3 = lb_80019BB8(arg1);
        break;
    }
    return var_r3;
}

void fn_8001A0B0(int arg0, int arg1)
{
    s32 var_r3;

    var_r3 = convert_hsdcard_error(arg1);

    lb_80432A68.unk_38[arg0].unk_0 = var_r3;
    lb_80432A68.unk_38[arg0].unk_4 = arg1;
    if (var_r3 != 0) {
        lb_80432A68.unk_34 = var_r3;
    }
    lb_80432A68.x8AC -= 1;
}

int lb_8001A184(void)
{
    s32 temp_r27;
    s32 temp_r28;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 var_r0;
    s32 var_r26;
    s32 var_r25;
    s32 var_r28;
    u8 _[8];

    var_r28 = 0;
    var_r25 = 0;
    lb_80432A68.x8AC = 0;
    temp_r3 = CARDProbeEx(lb_80432A68.chan, &lb_80432A68.memsize,
            &lb_80432A68.sectorsize);
    lb_80432A68.unk_34 = lb_80019BB8(temp_r3);
    if (lb_80432A68.unk_34 == 0) {
        if (lb_80432A68.unk_10 != NULL) {
            *(s32*) lb_80432A68.unk_10 = 0;
        }
        if (lb_80432A68.work_area == NULL) {
            __assert("lbcardnew.c", 0x23F, "_p(work_area)");
        }
        var_r26 = OSDisableInterrupts();
        var_r25 = 1;
        temp_r3_2 = CARDMountAsync(lb_80432A68.chan,
                lb_80432A68.work_area, NULL, fn_8001A008);

        lb_80432A68.unk_34 = lb_80019BB8(temp_r3_2);
        if (temp_r3_2 == 0 || temp_r3_2 == -6 || temp_r3_2 == -0xD) {
            lb_80432A68.unk_80 = 1;
        }
        if (lb_80432A68.unk_34 == 0) {
            lb_80432A68.x8AC += 1;
        }
    }
    temp_r27 = lb_80432A68.x8AC;
    temp_r28 = lb_80432A68.unk_34;
    if (var_r25 != 0) {
        OSRestoreInterrupts(var_r26);
    }
    if (temp_r27 != 0) {
        return 0xB;
    }
    return temp_r28;
}

int lb_8001A3A4(void)
{
    int temp_r29;
    int temp_r30;
    int var_r30;
    int temp_r28;
    int temp_r3;
    u8 _[8];

    var_r30 = 0;
    lb_80432A68.x8AC = 0;
    temp_r28 = OSDisableInterrupts();
    temp_r3 = CARDCheckAsync(lb_80432A68.chan, fn_8001A008);
    lb_80432A68.unk_34 = lb_80019BB8(temp_r3);
    if (lb_80432A68.unk_34 == 0) {
        lb_80432A68.x8AC += 1;
    }
    temp_r29 = lb_80432A68.x8AC;
    temp_r30 = lb_80432A68.unk_34;
    OSRestoreInterrupts(temp_r28);
    if (temp_r29 != 0) {
        return 0xB;
    }
    return temp_r30;
}

void lb_8001A4CC(const char* arg0, UNK_T arg1)
{
    struct CardTask* task = lb_80019C38();
    task->x0 = 2;
    task->x4 = 1;
    if (arg0 != NULL) {
        strncpy(task->xC = task->x10, arg0, ARRAY_SIZE(task->x10));
    } else {
        task->xC = NULL;
    }
    task->x8 = arg1;
}

int lb_8001A594(char* filename, void* arg1)
{
    int temp_r24;
    int temp_r3;
    int temp_r3_2;
    int temp_r5;
    int var_r24;
    int var_r24_2;
    int var_r3;
    int i;
    struct {
        int unk0, unk4, unk8;
    }* var_r25;
    u8 _[8];

    var_r24 = 0;
    lb_80432A68.x8AC = 0;
    if (lb_80432A68.sectorsize != 0x2000) {
        lb_80432A68.unk_34 = 0xC;
    } else {
        temp_r3 = CARDFreeBlocks(lb_80432A68.chan, &lb_80432A68.unused_bytes,
                &lb_80432A68.unused_files);

        lb_80432A68.unk_34 = lb_80019BB8(temp_r3);
        if (lb_80432A68.unk_34 == 0) {
            if (filename == NULL) {
                lb_80432A68.unk_34 = 7;
            } else {
                temp_r24 = CARDOpen(lb_80432A68.chan, filename,
                        &lb_80432A68.file_info);
                CARDClose(&lb_80432A68.file_info);
                if (lb_80432A68.lib_area == NULL) {
                    __assert("lbcardnew.c", 0x2C8, "_p(lib_area)");
                }
                hsd_803B24E4(&lb_80432A68.unk_A8, lb_80432A68.chan, 0x2000, lb_80432A68.lib_area);
                if (temp_r24 == 0) {
                    temp_r3_2 = hsd_803B2550(&lb_80432A68.unk_A8, filename,
                            fn_8001A0B0);

                    lb_80432A68.unk_34 = convert_hsdcard_error(temp_r3_2);
                    if (lb_80432A68.unk_34 == 0) {
                        lb_80432A68.x8AC += 1;
                    }
                } else if (arg1 == NULL) {
                    lb_80432A68.unk_34 = 4;
                } else if (lb_80432A68.unused_files == 0) {
                    lb_80432A68.unk_34 = 6;
                } else {
                    var_r25 = arg1;
                    hsd_803B2ADC(&lb_80432A68.unk_A8, lb_80432A68.unk_C);
                    i = 0;
                    while (var_r25->unk0 != -1) {
                        if (var_r25->unk0 != 0) {
                            hsd_803AC3E0((void*) &lb_80432A68.unk_A8, i,
                                var_r25->unk0, var_r25->unk4, var_r25->unk8);
                        }
                        i++;
                        var_r25++;
                    }
                    if (lb_80432A68.unused_bytes < (hsd_803B2674((void*) &lb_80432A68.unk_A8) << 0xD)) {
                        lb_80432A68.unk_34 = 5;
                    } else {
                        lb_80432A68.unk_34 = 4;
                    }
                }
            }
        }
    }
    if (lb_80432A68.x8AC != 0) {
        return 0xB;
    }
    return lb_80432A68.unk_34;
}

int lb_8001A860(void)
{
    lb_80432A68.x8AC = 0;
    switch (lb_80432A68.unk_34) {
    case 1:
        break;
    case 0:
    case 2:
        lb_80432A68.unk_34 = 1;
        break;
    }
    return lb_80432A68.unk_34;
}

int lb_8001A8A4(void)
{
    int temp_r29;
    int temp_r30;
    int temp_r3;
    int var_r28;
    int var_r27;
    int var_r30;

    var_r30 = 0;
    var_r27 = 0;
    lb_80432A68.x8AC = 0;
    if (lb_80432A68.unk_80 != 0) {
        var_r28 = OSDisableInterrupts();
        var_r27 = 1;
        temp_r3 = CARDFormatAsync(lb_80432A68.chan, fn_8001A008);

        lb_80432A68.unk_34 = lb_80019BB8(temp_r3);
        if (lb_80432A68.unk_34 == 0) {
            lb_80432A68.x8AC += 1;
        }
    }
    temp_r29 = lb_80432A68.x8AC;
    temp_r30 = lb_80432A68.unk_34;
    if (var_r27 != 0) {
        OSRestoreInterrupts(var_r28);
    }
    if (temp_r29 != 0) {
        return 0xB;
    }
    return temp_r30;
}

int lb_8001A9CC(char* filename)
{
    int var_r30;
    int temp_r29;
    int temp_r30;
    int temp_r28;
    int temp_r3;
    u8 _[8];

    var_r30 = 0;
    lb_80432A68.x8AC = 0;
    temp_r28 = OSDisableInterrupts();
    temp_r3 = CARDDeleteAsync(lb_80432A68.chan, filename, fn_8001A008);

    lb_80432A68.unk_34 = lb_80019BB8(temp_r3);
    if (lb_80432A68.unk_34 == 0) {
        lb_80432A68.x8AC += 1;
    }
    temp_r29 = lb_80432A68.x8AC;
    temp_r30 = lb_80432A68.unk_34;
    OSRestoreInterrupts(temp_r28);
    if (temp_r29 != 0) {
        return 0xB;
    }
    return temp_r30;
}

int lb_8001AAE4(const char* old_name, const char* new_name)
{
    int var_r30;
    int temp_r29;
    int temp_r30;
    int temp_r28;
    int temp_r3;
    u8 _[8];

    var_r30 = 0;
    lb_80432A68.x8AC = 0;
    temp_r28 = OSDisableInterrupts();
    temp_r3 = CARDRenameAsync(lb_80432A68.chan, old_name, new_name,
            fn_8001A008);
    lb_80432A68.unk_34 = lb_80019BB8(temp_r3);
    if (lb_80432A68.unk_34 == 0) {
        lb_80432A68.x8AC += 1;
    }
    temp_r29 = lb_80432A68.x8AC;
    temp_r30 = lb_80432A68.unk_34;
    OSRestoreInterrupts(temp_r28);
    if (temp_r29 != 0) {
        return 0xB;
    }
    return temp_r30;
}

int lb_8001AC04(UNK_T arg0)
{
    int temp_r3;
    int var_r3;

    temp_r3 = hsd_803B286C(&lb_80432A68.unk_A8, arg0,
            lb_80432A68.unk_14, lb_80432A68.unk_18,
            lb_80432A68.unk_1C, fn_8001A0B0);
    lb_80432A68.unk_34 = convert_hsdcard_error(temp_r3);
    if (lb_80432A68.unk_34 == 0) {
        lb_80432A68.x8AC += 1;
    }
    if (lb_80432A68.x8AC != 0) {
        return 0xB;
    }
    return lb_80432A68.unk_34;
}

int lb_8001ACEC(UNK_T arg0)
{
    int temp_r0;
    int temp_r3;
    int var_r3;
    int i;
    struct {
        int unk0, unk4, unk8;
    }* var_r30 = arg0;

    // TODO this seems fake
    volatile int sp18;
    volatile int sp14;
    volatile int sp10;

    //var_r30 = arg0 + (0 * 0xC);
    lb_80432A68.unk_34 = 0;
    for (i = 0; i < 9; i++) {
        sp18 = lb_80432A68.xF4[i];
        sp10 = lb_80432A68.xD0[i];
        if (lb_80432A68.xF4[i] != 0) {
            temp_r3 = hsd_803B29D8(&lb_80432A68.unk_A8, i,
                    var_r30[i].unk8, fn_8001A0B0);
            lb_80432A68.unk_38[i].unk_0 = convert_hsdcard_error(temp_r3);
            lb_80432A68.unk_38[i].unk_4 = temp_r3;
            temp_r0 = lb_80432A68.unk_38[i].unk_0;
            if (temp_r0 == 0) {
                lb_80432A68.x8AC += 1;
            } else {
                lb_80432A68.unk_34 = temp_r0;
            }
        }
    }
    if (lb_80432A68.x8AC != 0) {
        return 0xB;
    }
    return lb_80432A68.unk_34;
}

int lb_8001AE38(UNK_T arg0)
{
    int temp_r0;
    int temp_r3;
    int var_r3;
    int i;
    struct {
        int unk0, unk4, unk8;
    }* var_r30 = arg0;

    // TODO this seems fake
    volatile int sp18;
    volatile int sp14;
    volatile int sp10;

    //var_r30 = arg0 + (0 * 0xC);
    lb_80432A68.unk_34 = 0;
    for (i = 0; i < 9; i++) {
        sp18 = lb_80432A68.xF4[i];
        sp10 = lb_80432A68.xD0[i];
        if (lb_80432A68.xF4[i] != 0) {
            temp_r3 = hsd_803B2A4C(&lb_80432A68.unk_A8, i,
                    var_r30[i].unk8, fn_8001A0B0);
            lb_80432A68.unk_38[i].unk_0 = convert_hsdcard_error(temp_r3);
            lb_80432A68.unk_38[i].unk_4 = temp_r3;
            temp_r0 = lb_80432A68.unk_38[i].unk_0;
            if (temp_r0 == 0) {
                lb_80432A68.x8AC += 1;
            } else {
                lb_80432A68.unk_34 = temp_r0;
            }
        }
    }
    if (lb_80432A68.x8AC != 0) {
        return 0xB;
    }
    return lb_80432A68.unk_34;
}

int lb_8001AF84(void)
{
    int temp_r3 = hsd_803B2928(&lb_80432A68.unk_A8,
            lb_80432A68.unk_14, lb_80432A68.unk_18,
            lb_80432A68.unk_1C, fn_8001A0B0);

    lb_80432A68.unk_34 = convert_hsdcard_error(temp_r3);

    if (lb_80432A68.unk_34 == 0) {
        lb_80432A68.x8AC += 1;
    }
    if (lb_80432A68.x8AC != 0) {
        return 0xB;
    }
    return lb_80432A68.unk_34;
}

int lb_8001B068(void)
{
    int temp_r3 = hsd_803B27F4(&lb_80432A68.unk_A8,
            lb_80432A68.unk_14, lb_80432A68.unk_18,
            lb_80432A68.unk_1C, fn_8001A0B0);

    lb_80432A68.unk_34 = convert_hsdcard_error(temp_r3);

    if (lb_80432A68.unk_34 == 0) {
        lb_80432A68.x8AC += 1;
    }
    if (lb_80432A68.x8AC != 0) {
        return 0xB;
    }
    return lb_80432A68.unk_34;
}

// UnclePunch map calls this "MemoryCard_ScanForSnapshots"
// Stubbing it out for now
int lb_8001B14C()
{
    lb_80432A68.unk_34 = 0;
    return lb_80432A68.unk_34;
}

int lb_8001B614(const char* arg0)
{
    CARDStat spC;
    int fileno;

    fileno = 0;
    lb_80432A68.x8AC = 0;
loop_1:
    if (CARDGetStatus(lb_80432A68.chan, fileno, &spC) == 0 &&
        strncmp((const char*) spC.company, lb_80432A68.x2C, 2) == 0 &&
        strncmp((const char*) spC.gameName, lb_80432A68.x2F, 4) == 0 &&
        strcmp(spC.fileName, arg0) == 0) {
        lb_80432A68.unk_34 = 0;
    } else {
        fileno += 1;
        if (fileno >= 0x7F) {
            lb_80432A68.unk_34 = 0xD;
        } else {
            goto loop_1;
        }
    }
    return lb_80432A68.unk_34;
}

s32 lb_8001B6E0(s32 arg0)
{
    return lb_80432A68.unk_38[arg0].unk_0;
}

int lb_8001B6F8(void)
{
    int enabled;
    int var_r31;

    hsd_803AAA48();
    enabled = OSDisableInterrupts();
    if (lb_80432A68.x8AC != 0) {
        var_r31 = 0xB;
    } else {
        var_r31 = lb_80432A68.unk_34;
    }
    OSRestoreInterrupts(enabled);
    if (var_r31 != 0xB) {
        var_r31 = lb_80019CB0(var_r31);
    }
    return var_r31;
}

void lb_8001B760(int arg0)
{
    if (arg0 == 0xB) {
        do {
            arg0 = lb_8001B6F8();
        } while (arg0 == 0xB);
    }
}

inline struct CardTask* setup_task(int a, int b)
{
    struct CardTask* temp_r3 = lb_80019C38();
    temp_r3->x0 = a;
    temp_r3->x4 = b;
    return temp_r3;
}

inline void lb_8001A4CC_dontinline(const char* arg1, void* arg2)
{
    lb_8001A4CC(arg1, arg2);
}

u32 lb_8001B7E0(int chan, char* arg1, void* arg2, void* arg3, int* arg4)
{
    int enabled;
    s32 var_r30;
    s32 var_r3;
    u8 _[0x10];

    lb_80019EF0(chan, arg3, arg4, NULL);
    setup_task(0, 0x10000);
    setup_task(1, 0x201);
    lb_8001A4CC_dontinline(arg1, arg2);
    setup_task(3, -1);

    var_r3 = lb_80019CB0(0x10);
    if (var_r3 == 0xB) {
        do {
            var_r3 = lb_8001B6F8();
        } while (var_r3 == 0xB);
    }
    return var_r3;
}

int lb_8001B8C8(int arg0)
{
    int temp_r3_4;
    int var_r30;
    int var_r3;
    u8 _[0x18];

    lb_80019EF0(arg0, 0, 0, 0);
    setup_task(0, 0x10000);
    setup_task(1, 0x201);
    setup_task(4, -1);

    var_r3 = lb_80019CB0(0x10);
    if (var_r3 == 0xB) {
        do {
            var_r3 = lb_8001B6F8();
        } while (var_r3 == 0xB);
    }
    return var_r3;
}

int lb_8001B99C(int arg0, const char* arg1, UNK_T arg2)
{
    lb_80019EF0(arg0, 0, arg2, 0);
    setup_task(0, 0x10000);
    setup_task(1, 0x201);
    lb_8001A4CC_dontinline(arg1, 0);
    setup_task(3, -1);
    strncpy(setup_task(5, 0xE)->x10, arg1, 0x20);
    return lb_80019CB0(0x10);
}

int lb_8001BA44(int arg0, const char* arg1, UNK_T arg2)
{
    s32 var_r3 = lb_8001B99C(arg0, arg1, arg2);
    if (var_r3 == 0xB) {
        do {
            var_r3 = lb_8001B6F8();
        } while (var_r3 == 0xB);
    }
    return var_r3;
}

int lb_8001BB48(int arg0, char* arg1, void* arg2, void* arg3, const char* arg4, int arg5, int arg6, UNK_T arg7)
{
    lb_80019EF0(arg0, arg3, arg7, 0);
    setup_task(0, 0x10000);
    setup_task(1, 0x201);
    lb_8001A4CC_dontinline(arg1, arg2);
    setup_task(3, -1);
    memcpy(setup_task(7, 0x10)->x10, arg1, 0x20);
    lb_80432A68.unk_14 = arg4;
    lb_80432A68.unk_18 = arg5;
    lb_80432A68.unk_1C = arg6;
    return lb_80019CB0(0x10);
}

int lb_8001BC18(int arg0, char* arg1, void** arg2, void* arg3, const char* arg4, int arg5, int arg6, UNK_T arg7)
{
    s32 var_r3 = lb_8001BB48(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    if (var_r3 == 0xB) {
        do {
            var_r3 = lb_8001B6F8();
        } while (var_r3 == 0xB);
    }
    return var_r3;
}

int lb_8001BD34(int chan, const char* arg1, UNK_T arg2, UNK_T arg3)
{
    s32 temp_r3_5;
    s32 var_r30;
    s32 var_r3;
    struct CardTask* temp_r3;
    u8 _[4];

    lb_80019EF0(chan, NULL, arg3, NULL);

    setup_task(0, 0x10000);
    setup_task(1, 0x201);
    lb_8001A4CC_dontinline(arg1, 0);
    setup_task(3, -1);
    setup_task(8, 3)->x8 = arg2;

    var_r3 = lb_80019CB0(0x10);
    if (var_r3 == 0xB) {
        do {
            var_r3 = lb_8001B6F8();
        } while (var_r3 == 0xB);
    }
    return var_r3;
}

int lb_8001BE30(int arg0, const char* arg1, UNK_T arg2, const char* arg3, int arg4, int arg5, UNK_T arg6, UNK_T arg7)
{
    lb_80019EF0(arg0, 0, arg6, arg7);
    setup_task(0, 0x10000);
    setup_task(1, 0x201);
    lb_8001A4CC_dontinline(arg1, 0);
    setup_task(3, -1);
    setup_task(10, 2);
    lb_80432A68.unk_14 = arg3;
    lb_80432A68.unk_18 = arg4;
    lb_80432A68.unk_1C = arg5;
    setup_task(9, 3)->x8 = arg2;
    return lb_80019CB0(0x10);
}

int lb_8001BF04(int arg0, char* arg1, void* arg2, const char* arg3, int arg4, int arg5, UNK_T arg6)
{
    lb_80019EF0(arg0, 0, arg6, 0);
    setup_task(0, 0x10000);
    setup_task(1, 0x201);
    lb_8001A4CC_dontinline(arg1, 0);
    setup_task(3, -1);
    setup_task(11, 2);
    lb_80432A68.unk_14 = arg3;
    lb_80432A68.unk_18 = arg4;
    lb_80432A68.unk_1C = arg5;
    setup_task(8, 3)->x8 = arg2;
    return lb_80019CB0(0x10);
}

int lb_8001BFD8(int arg0, UNK_T arg1, UNK_T arg2, UNK_T arg3)
{
    s32 var_r3;
    u8 _[0x18];

    lb_80019EF0(arg0, 0, 0, 0);
    setup_task(0, 0x10000);
    setup_task(1, 0x201);
    lb_8001A4CC_dontinline(NULL, 0);
    setup_task(3, -1);
    setup_task(12, 0x80);
    lb_80432A68.unk_20 = arg1;
    lb_80432A68.unk_24 = arg2;
    lb_80432A68.unk_28 = arg3;
    var_r3 = lb_80019CB0(0x10);
    if (var_r3 == 0xB) {
        do {
            var_r3 = lb_8001B6F8();
        } while (var_r3 == 0xB);
    }
    return var_r3;
}

int lb_8001C0F4(int arg0, const char* arg1, const char* arg2, const char* arg3, UNK_T arg4)
{
    struct CardTask* task;

    lb_80019EF0(arg0, 0, arg4, 0);
    setup_task(0, 0x10000);
    setup_task(1, 0x201);
    lb_8001A4CC_dontinline(arg1, 0);
    setup_task(3, -1);
    task = setup_task(6, 14);
    strncpy(task->x10, arg1, 0x20);
    strncpy(task->x19, arg3, 0x20);
    task = setup_task(2, 1);
    if (arg2 != NULL) {
        task->xC = task->x10;
        strncpy(task->x10, arg2, 0x20);
    } else {
        task->xC = NULL;
    }
    task->x8 = 0;
    setup_task(3, -1);
    task = setup_task(6, 14);
    strncpy(task->x10, arg2, 0x20);
    strncpy(task->x19, arg1, 0x20);
    task = setup_task(2, 1);
    if (arg3 != NULL) {
        task->xC = task->x10;
        strncpy(task->x10, arg3, 0x20);
    } else {
        task->xC = NULL;
    }
    task->x8 = 0;
    setup_task(3, -1);
    task = setup_task(6, 14);
    strncpy(task->x10, arg3, 0x20);
    strncpy(task->x19, arg2, 0x20);
    return lb_80019CB0(0x10);
}

int lb_8001C2D8(int arg0, const char* arg1, const char* arg2, const char* arg3)
{
    int enabled;
    int var_r31;
    s32 var_r3;
    struct CardTask* temp_r3;
    struct CardTask* temp_r3_2;
    struct CardTask* temp_r3_3;
    struct CardTask* temp_r3_4;

    lb_80019EF0(arg0, 0, 0, 0);
    setup_task(0, 0x10000);
    setup_task(1, 0x201);
    lb_8001A4CC_dontinline(NULL, 0);
    setup_task(3, -1);
    temp_r3_4 = setup_task(0xD, 0x80);
    strncpy(lb_80432A68.x2C, arg1, 2U);
    strncpy(lb_80432A68.x2F, arg2, 4U);
    strncpy(temp_r3_4->x10, arg3, 0x20U);
    var_r3 = lb_80019CB0(0x10);
    if (var_r3 == 0xB) {
        do {
            var_r3 = lb_8001B6F8();
        } while (var_r3 == 0xB);
    }
    return var_r3;
}

int lb_8001C404(int arg0)
{
    s32 sp10;
    s32 spC;
    return lb_80019BB8(CARDProbeEx(arg0, &sp10, &spC));
}

void lb_8001C4A8(void* arg0, void* arg1)
{
    struct {
        int unk0, unk4, unk8;
    }* var_r30;
    int i;

    var_r30 = arg0;
    hsd_803B24E4(&lb_80432A68.unk_A8, 0, 0x2000, lb_80432A68.lib_area);
    hsd_803B2ADC(&lb_80432A68.unk_A8, arg1);
    i = 0;
    while (var_r30->unk0 != -1) {
        if (var_r30->unk0 != 0) {
            hsd_803AC3E0((struct hsd_803AC3E0_arg0_t*) &lb_80432A68.unk_A8,
                    i, var_r30->unk0, var_r30->unk4, var_r30->unk8);
        }
        i++;
        var_r30++;
    }
    hsd_803B2674(&lb_80432A68.unk_A8);
}

void lb_8001C550(void)
{
    if (lb_80432A68.work_area == NULL) {
        lb_80432A68.work_area = HSD_MemAlloc(0xA000);
        lb_80432A68.lib_area = HSD_MemAlloc(0x2000);
    }
}

void lb_8001C5A4(void)
{
    lb_80432A68.work_area = lb_80432A68.lib_area = NULL;
}

void lb_8001C5BC(void)
{
    hsd_803B2374();
    lb_80019EF0(NULL, NULL, NULL, NULL);
    lb_80432A68.x8AC = 0;
}
