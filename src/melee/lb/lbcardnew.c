#include "lbcardnew.h"

#include "lbcardnew.static.h"

#include <dolphin/card.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/hsd_3AA7.h>
#include <sysdolphin/baselib/hsd_3B27.h>
#include <sysdolphin/baselib/memory.h>
#include <melee/lb/lb_0192.h>

int lb_80019BB8(int card_result)
{
    switch (card_result) {
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

int lb_80019CB0(int result)
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
        if (!(task->x4 & (1 << result))) {
            reset_task_array();
        } else {
            switch (task->x0) {
            case 0:
                result = lb_8001A184();
                break;
            case 1:
                result = lb_8001A3A4();
                break;
            case 2:
                result = lb_8001A594(task->xC, task->x8);
                break;
            case 3:
                result = lb_8001A860();
                break;
            case 4:
                result = lb_8001A8A4();
                break;
            case 5:
                result = lb_8001A9CC(task->x10);
                break;
            case 6:
                result = lb_8001AAE4(task->x10, task->x19);
                break;
            case 7:
                result = lb_8001AC04(&task->x10);
                break;
            case 8:
                result = lb_8001ACEC(task->x8);
                break;
            case 9:
                result = lb_8001AE38(task->x8);
                break;
            case 10:
                result = lb_8001AF84();
                break;
            case 11:
                result = lb_8001B068();
                break;
            case 12:
                result = lb_8001B14C();
                break;
            case 13:
                result = lb_8001B614(task->x10);
                break;
            }
            task->x0 = 0xE;
            if (result != 11) {
                goto again;
            }
        }
    }
    if (result != 11 && lb_80432A68.x50C != NULL) {
        lb_80432A68.x50C(result);
        lb_80432A68.x50C = NULL;
    }
    if (result != 11 && lb_80432A68.unk_80 != 0) {
        CARDUnmount(lb_80432A68.chan);
        lb_80432A68.unk_80 = 0;
    }
    return result;
}

void lb_80019EF0(int chan, UNK_T save_data, UNK_T status_out, UNK_T callback)
{
    int i;

    lb_80432A68.chan = chan;
    lb_80432A68.unk_C = save_data;
    lb_80432A68.unk_10 = status_out;
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
    lb_80432A68.x50C = callback;

    reset_task_array();
}

void fn_8001A008(s32 unused, s32 card_result)
{
    s32 error;

    error = lb_80019BB8(card_result);

    if (error != 0) {
        lb_80432A68.unk_34 = error;
    }
    lb_80432A68.x8AC -= 1;
}

static int convert_hsdcard_error(int hsd_error)
{
    int error;
    switch (hsd_error) {
    case 0:
    case 1:
        error = 0;
        break;
    case -0x105:
    case -0x104:
    case -0x103:
    case -0x102:
        error = 2;
        break;
    case -0x107:
    case -0x106:
    case -0x101:
        error = 3;
        break;
    case -0x108:
    case -0x109:
    case -0x10A:
    case -0x10B:
        error = 10;
        break;
    default:
        error = lb_80019BB8(hsd_error);
        break;
    }
    return error;
}

void fn_8001A0B0(int file_idx, int hsd_error)
{
    s32 error;

    error = convert_hsdcard_error(hsd_error);

    lb_80432A68.unk_38[file_idx].unk_0 = error;
    lb_80432A68.unk_38[file_idx].unk_4 = hsd_error;
    if (error != 0) {
        lb_80432A68.unk_34 = error;
    }
    lb_80432A68.x8AC -= 1;
}

int lb_8001A184(void)
{
    s32 pending_ops;
    s32 saved_error;
    s32 probe_result;
    s32 mount_result;
    s32 unused;
    s32 enabled;
    s32 did_disable;
    s32 result;
    u8 _[8];

    result = 0;
    did_disable = 0;
    lb_80432A68.x8AC = 0;
    probe_result = CARDProbeEx(lb_80432A68.chan, &lb_80432A68.memsize,
                               &lb_80432A68.sectorsize);
    lb_80432A68.unk_34 = lb_80019BB8(probe_result);
    if (lb_80432A68.unk_34 == 0) {
        if (lb_80432A68.unk_10 != NULL) {
            *(s32*) lb_80432A68.unk_10 = 0;
        }
        if (lb_80432A68.work_area == NULL) {
            __assert("lbcardnew.c", 0x23F, "_p(work_area)");
        }
        enabled = OSDisableInterrupts();
        did_disable = 1;
        mount_result = CARDMountAsync(lb_80432A68.chan, lb_80432A68.work_area,
                                      NULL, fn_8001A008);

        lb_80432A68.unk_34 = lb_80019BB8(mount_result);
        if (mount_result == 0 || mount_result == -6 || mount_result == -0xD) {
            lb_80432A68.unk_80 = 1;
        }
        if (lb_80432A68.unk_34 == 0) {
            lb_80432A68.x8AC += 1;
        }
    }
    pending_ops = lb_80432A68.x8AC;
    saved_error = lb_80432A68.unk_34;
    if (did_disable != 0) {
        OSRestoreInterrupts(enabled);
    }
    if (pending_ops != 0) {
        return 0xB;
    }
    return saved_error;
}

int lb_8001A3A4(void)
{
    int pending_ops;
    int saved_error;
    int unused;
    int enabled;
    int check_result;
    u8 _[8];

    unused = 0;
    lb_80432A68.x8AC = 0;
    enabled = OSDisableInterrupts();
    check_result = CARDCheckAsync(lb_80432A68.chan, fn_8001A008);
    lb_80432A68.unk_34 = lb_80019BB8(check_result);
    if (lb_80432A68.unk_34 == 0) {
        lb_80432A68.x8AC += 1;
    }
    pending_ops = lb_80432A68.x8AC;
    saved_error = lb_80432A68.unk_34;
    OSRestoreInterrupts(enabled);
    if (pending_ops != 0) {
        return 0xB;
    }
    return saved_error;
}

void lb_8001A4CC(const char* filename, UNK_T file_entries)
{
    struct CardTask* task = lb_80019C38();
    task->x0 = 2;
    task->x4 = 1;
    if (filename != NULL) {
        strncpy(task->xC = task->x10, filename, ARRAY_SIZE(task->x10));
    } else {
        task->xC = NULL;
    }
    task->x8 = file_entries;
}

int lb_8001A594(char* filename, void* file_entries)
{
    int open_result;
    int free_result;
    int hsd_result;
    int unused_1;
    int unused_2;
    int unused_3;
    int unused_4;
    int i;
    struct {
        int unk0, unk4, unk8;
    }* entry;
    u8 _[8];

    unused_2 = 0;
    lb_80432A68.x8AC = 0;
    if (lb_80432A68.sectorsize != 0x2000) {
        lb_80432A68.unk_34 = 0xC;
    } else {
        free_result =
            CARDFreeBlocks(lb_80432A68.chan, &lb_80432A68.unused_bytes,
                           &lb_80432A68.unused_files);

        lb_80432A68.unk_34 = lb_80019BB8(free_result);
        if (lb_80432A68.unk_34 == 0) {
            if (filename == NULL) {
                lb_80432A68.unk_34 = 7;
            } else {
                open_result = CARDOpen(lb_80432A68.chan, filename,
                                       &lb_80432A68.file_info);
                CARDClose(&lb_80432A68.file_info);
                if (lb_80432A68.lib_area == NULL) {
                    __assert("lbcardnew.c", 0x2C8, "_p(lib_area)");
                }
                hsd_803B24E4(&lb_80432A68.unk_A8, lb_80432A68.chan, 0x2000,
                             lb_80432A68.lib_area);
                if (open_result == 0) {
                    hsd_result = hsd_803B2550(&lb_80432A68.unk_A8, filename,
                                              fn_8001A0B0);

                    lb_80432A68.unk_34 = convert_hsdcard_error(hsd_result);
                    if (lb_80432A68.unk_34 == 0) {
                        lb_80432A68.x8AC += 1;
                    }
                } else if (file_entries == NULL) {
                    lb_80432A68.unk_34 = 4;
                } else if (lb_80432A68.unused_files == 0) {
                    lb_80432A68.unk_34 = 6;
                } else {
                    entry = file_entries;
                    hsd_803B2ADC(&lb_80432A68.unk_A8, lb_80432A68.unk_C);
                    i = 0;
                    while (entry->unk0 != -1) {
                        if (entry->unk0 != 0) {
                            hsd_803AC3E0((void*) &lb_80432A68.unk_A8, i,
                                         entry->unk0, entry->unk4,
                                         entry->unk8);
                        }
                        i++;
                        entry++;
                    }
                    if (lb_80432A68.unused_bytes <
                        (hsd_803B2674((void*) &lb_80432A68.unk_A8) << 0xD))
                    {
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
    int pending_ops;
    int saved_error;
    int format_result;
    int enabled;
    int did_disable;
    int unused;

    unused = 0;
    did_disable = 0;
    lb_80432A68.x8AC = 0;
    if (lb_80432A68.unk_80 != 0) {
        enabled = OSDisableInterrupts();
        did_disable = 1;
        format_result = CARDFormatAsync(lb_80432A68.chan, fn_8001A008);

        lb_80432A68.unk_34 = lb_80019BB8(format_result);
        if (lb_80432A68.unk_34 == 0) {
            lb_80432A68.x8AC += 1;
        }
    }
    pending_ops = lb_80432A68.x8AC;
    saved_error = lb_80432A68.unk_34;
    if (did_disable != 0) {
        OSRestoreInterrupts(enabled);
    }
    if (pending_ops != 0) {
        return 0xB;
    }
    return saved_error;
}

int lb_8001A9CC(char* filename)
{
    int unused;
    int pending_ops;
    int saved_error;
    int enabled;
    int delete_result;
    u8 _[8];

    unused = 0;
    lb_80432A68.x8AC = 0;
    enabled = OSDisableInterrupts();
    delete_result = CARDDeleteAsync(lb_80432A68.chan, filename, fn_8001A008);

    lb_80432A68.unk_34 = lb_80019BB8(delete_result);
    if (lb_80432A68.unk_34 == 0) {
        lb_80432A68.x8AC += 1;
    }
    pending_ops = lb_80432A68.x8AC;
    saved_error = lb_80432A68.unk_34;
    OSRestoreInterrupts(enabled);
    if (pending_ops != 0) {
        return 0xB;
    }
    return saved_error;
}

int lb_8001AAE4(const char* old_name, const char* new_name)
{
    int unused;
    int pending_ops;
    int saved_error;
    int enabled;
    int rename_result;
    u8 _[8];

    unused = 0;
    lb_80432A68.x8AC = 0;
    enabled = OSDisableInterrupts();
    rename_result =
        CARDRenameAsync(lb_80432A68.chan, old_name, new_name, fn_8001A008);
    lb_80432A68.unk_34 = lb_80019BB8(rename_result);
    if (lb_80432A68.unk_34 == 0) {
        lb_80432A68.x8AC += 1;
    }
    pending_ops = lb_80432A68.x8AC;
    saved_error = lb_80432A68.unk_34;
    OSRestoreInterrupts(enabled);
    if (pending_ops != 0) {
        return 0xB;
    }
    return saved_error;
}

int lb_8001AC04(UNK_T filename)
{
    int hsd_result;
    int unused;

    hsd_result =
        hsd_803B286C(&lb_80432A68.unk_A8, filename, lb_80432A68.unk_14,
                     lb_80432A68.unk_18, lb_80432A68.unk_1C, fn_8001A0B0);
    lb_80432A68.unk_34 = convert_hsdcard_error(hsd_result);
    if (lb_80432A68.unk_34 == 0) {
        lb_80432A68.x8AC += 1;
    }
    if (lb_80432A68.x8AC != 0) {
        return 0xB;
    }
    return lb_80432A68.unk_34;
}

int lb_8001ACEC(UNK_T file_entries)
{
    int file_error;
    int hsd_result;
    int unused;
    int i;
    struct {
        int unk0, unk4, unk8;
    }* entries = file_entries;

    // @todo this seems fake
    volatile int cached_flag;
    volatile int pad_stack;
    volatile int cached_data;

    lb_80432A68.unk_34 = 0;
    for (i = 0; i < 9; i++) {
        cached_flag = lb_80432A68.xF4[i];
        cached_data = lb_80432A68.xD0[i];
        if (lb_80432A68.xF4[i] != 0) {
            hsd_result = hsd_803B29D8(&lb_80432A68.unk_A8, i, entries[i].unk8,
                                      fn_8001A0B0);
            lb_80432A68.unk_38[i].unk_0 = convert_hsdcard_error(hsd_result);
            lb_80432A68.unk_38[i].unk_4 = hsd_result;
            file_error = lb_80432A68.unk_38[i].unk_0;
            if (file_error == 0) {
                lb_80432A68.x8AC += 1;
            } else {
                lb_80432A68.unk_34 = file_error;
            }
        }
    }
    if (lb_80432A68.x8AC != 0) {
        return 0xB;
    }
    return lb_80432A68.unk_34;
}

int lb_8001AE38(UNK_T file_entries)
{
    int file_error;
    int hsd_result;
    int unused;
    int i;
    struct {
        int unk0, unk4, unk8;
    }* entries = file_entries;

    // @todo this seems fake
    volatile int cached_flag;
    volatile int pad_stack;
    volatile int cached_data;

    lb_80432A68.unk_34 = 0;
    for (i = 0; i < 9; i++) {
        cached_flag = lb_80432A68.xF4[i];
        cached_data = lb_80432A68.xD0[i];
        if (lb_80432A68.xF4[i] != 0) {
            hsd_result = hsd_803B2A4C(&lb_80432A68.unk_A8, i, entries[i].unk8,
                                      fn_8001A0B0);
            lb_80432A68.unk_38[i].unk_0 = convert_hsdcard_error(hsd_result);
            lb_80432A68.unk_38[i].unk_4 = hsd_result;
            file_error = lb_80432A68.unk_38[i].unk_0;
            if (file_error == 0) {
                lb_80432A68.x8AC += 1;
            } else {
                lb_80432A68.unk_34 = file_error;
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
    int hsd_result =
        hsd_803B2928(&lb_80432A68.unk_A8, lb_80432A68.unk_14,
                     lb_80432A68.unk_18, lb_80432A68.unk_1C, fn_8001A0B0);

    lb_80432A68.unk_34 = convert_hsdcard_error(hsd_result);

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
    int hsd_result =
        hsd_803B27F4(&lb_80432A68.unk_A8, lb_80432A68.unk_14,
                     lb_80432A68.unk_18, lb_80432A68.unk_1C, fn_8001A0B0);

    lb_80432A68.unk_34 = convert_hsdcard_error(hsd_result);

    if (lb_80432A68.unk_34 == 0) {
        lb_80432A68.x8AC += 1;
    }
    if (lb_80432A68.x8AC != 0) {
        return 0xB;
    }
    return lb_80432A68.unk_34;
}

/// UnclePunch map calls this "MemoryCard_ScanForSnapshots"
/// Stubbing it out for now
int lb_8001B14C(void)
{
    lb_80432A68.unk_34 = 0;
    return lb_80432A68.unk_34;
}

int lb_8001B614(const char* filename)
{
    CARDStat card_stat;
    int fileno;

    fileno = 0;
    lb_80432A68.x8AC = 0;
loop_1:
    if (CARDGetStatus(lb_80432A68.chan, fileno, &card_stat) == 0 &&
        strncmp((const char*) card_stat.company, lb_80432A68.x2C, 2) == 0 &&
        strncmp((const char*) card_stat.gameName, lb_80432A68.x2F, 4) == 0 &&
        strcmp(card_stat.fileName, filename) == 0)
    {
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

s32 lb_8001B6E0(s32 file_idx)
{
    return lb_80432A68.unk_38[file_idx].unk_0;
}

int lb_8001B6F8(void)
{
    int enabled;
    int result;

    hsd_803AAA48();
    enabled = OSDisableInterrupts();
    if (lb_80432A68.x8AC != 0) {
        result = 0xB;
    } else {
        result = lb_80432A68.unk_34;
    }
    OSRestoreInterrupts(enabled);
    if (result != 0xB) {
        result = lb_80019CB0(result);
    }
    return result;
}

void lb_8001B760(int result)
{
    if (result == 0xB) {
        do {
            result = lb_8001B6F8();
        } while (result == 0xB);
    }
}

inline struct CardTask* setup_task(int a, int b)
{
    struct CardTask* task = lb_80019C38();
    task->x0 = a;
    task->x4 = b;
    return task;
}

inline void lb_8001A4CC_dontinline(const char* filename, void* file_entries)
{
    lb_8001A4CC(filename, file_entries);
}

u32 lb_8001B7E0(int chan, char* filename, void* file_entries, void* save_data,
                int* status_out)
{
    int enabled;
    s32 unused;
    s32 result;
    u8 _[0x10];

    lb_80019EF0(chan, save_data, status_out, NULL);
    setup_task(0, 0x10000);
    setup_task(1, 0x201);
    lb_8001A4CC_dontinline(filename, file_entries);
    setup_task(3, -1);

    result = lb_80019CB0(0x10);
    if (result == 0xB) {
        do {
            result = lb_8001B6F8();
        } while (result == 0xB);
    }
    return result;
}

int lb_8001B8C8(int chan)
{
    int unused_1;
    int unused_2;
    int result;
    u8 _[0x18];

    lb_80019EF0(chan, 0, 0, 0);
    setup_task(0, 0x10000);
    setup_task(1, 0x201);
    setup_task(4, -1);

    result = lb_80019CB0(0x10);
    if (result == 0xB) {
        do {
            result = lb_8001B6F8();
        } while (result == 0xB);
    }
    return result;
}

int lb_8001B99C(int chan, const char* filename, UNK_T status_out)
{
    lb_80019EF0(chan, 0, status_out, 0);
    setup_task(0, 0x10000);
    setup_task(1, 0x201);
    lb_8001A4CC_dontinline(filename, 0);
    setup_task(3, -1);
    strncpy(setup_task(5, 0xE)->x10, filename, 0x20);
    return lb_80019CB0(0x10);
}

int lb_8001BA44(int chan, const char* filename, UNK_T status_out)
{
    s32 result = lb_8001B99C(chan, filename, status_out);
    if (result == 0xB) {
        do {
            result = lb_8001B6F8();
        } while (result == 0xB);
    }
    return result;
}

int lb_8001BB48(int chan, char* filename, void* file_entries, void* save_data,
                const char* write_buf, int write_offset, int write_len,
                UNK_T status_out)
{
    lb_80019EF0(chan, save_data, status_out, 0);
    setup_task(0, 0x10000);
    setup_task(1, 0x201);
    lb_8001A4CC_dontinline(filename, file_entries);
    setup_task(3, -1);
    memcpy(setup_task(7, 0x10)->x10, filename, 0x20);
    lb_80432A68.unk_14 = write_buf;
    lb_80432A68.unk_18 = write_offset;
    lb_80432A68.unk_1C = write_len;
    return lb_80019CB0(0x10);
}

int lb_8001BC18(int chan, char* filename, void** file_entries, void* save_data,
                const char* write_buf, int write_offset, int write_len,
                UNK_T status_out)
{
    s32 result = lb_8001BB48(chan, filename, file_entries, save_data,
                             write_buf, write_offset, write_len, status_out);
    if (result == 0xB) {
        do {
            result = lb_8001B6F8();
        } while (result == 0xB);
    }
    return result;
}

int lb_8001BD34(int chan, const char* filename, UNK_T file_entries,
                UNK_T status_out)
{
    s32 unused_1;
    s32 unused_2;
    s32 result;
    struct CardTask* task;
    u8 _[4];

    lb_80019EF0(chan, NULL, status_out, NULL);

    setup_task(0, 0x10000);
    setup_task(1, 0x201);
    lb_8001A4CC_dontinline(filename, 0);
    setup_task(3, -1);
    setup_task(8, 3)->x8 = file_entries;

    result = lb_80019CB0(0x10);
    if (result == 0xB) {
        do {
            result = lb_8001B6F8();
        } while (result == 0xB);
    }
    return result;
}

int lb_8001BE30(int chan, const char* filename, UNK_T file_entries,
                const char* read_buf, int read_offset, int read_len,
                UNK_T status_out, UNK_T callback)
{
    lb_80019EF0(chan, 0, status_out, callback);
    setup_task(0, 0x10000);
    setup_task(1, 0x201);
    lb_8001A4CC_dontinline(filename, 0);
    setup_task(3, -1);
    setup_task(10, 2);
    lb_80432A68.unk_14 = read_buf;
    lb_80432A68.unk_18 = read_offset;
    lb_80432A68.unk_1C = read_len;
    setup_task(9, 3)->x8 = file_entries;
    return lb_80019CB0(0x10);
}

int lb_8001BF04(int chan, char* filename, void* file_entries,
                const char* write_buf, int write_offset, int write_len,
                UNK_T status_out)
{
    lb_80019EF0(chan, 0, status_out, 0);
    setup_task(0, 0x10000);
    setup_task(1, 0x201);
    lb_8001A4CC_dontinline(filename, 0);
    setup_task(3, -1);
    setup_task(11, 2);
    lb_80432A68.unk_14 = write_buf;
    lb_80432A68.unk_18 = write_offset;
    lb_80432A68.unk_1C = write_len;
    setup_task(8, 3)->x8 = file_entries;
    return lb_80019CB0(0x10);
}

int lb_8001BFD8(int chan, UNK_T snap_buf, UNK_T snap_count, UNK_T snap_max)
{
    s32 result;
    u8 _[0x18];

    lb_80019EF0(chan, 0, 0, 0);
    setup_task(0, 0x10000);
    setup_task(1, 0x201);
    lb_8001A4CC_dontinline(NULL, 0);
    setup_task(3, -1);
    setup_task(12, 0x80);
    lb_80432A68.unk_20 = snap_buf;
    lb_80432A68.unk_24 = snap_count;
    lb_80432A68.unk_28 = snap_max;
    result = lb_80019CB0(0x10);
    if (result == 0xB) {
        do {
            result = lb_8001B6F8();
        } while (result == 0xB);
    }
    return result;
}

int lb_8001C0F4(int chan, const char* name_a, const char* name_b,
                const char* name_c, UNK_T status_out)
{
    struct CardTask* task;

    lb_80019EF0(chan, 0, status_out, 0);
    setup_task(0, 0x10000);
    setup_task(1, 0x201);
    lb_8001A4CC_dontinline(name_a, 0);
    setup_task(3, -1);
    task = setup_task(6, 14);
    strncpy(task->x10, name_a, 0x20);
    strncpy(task->x19, name_c, 0x20);
    task = setup_task(2, 1);
    if (name_b != NULL) {
        task->xC = task->x10;
        strncpy(task->x10, name_b, 0x20);
    } else {
        task->xC = NULL;
    }
    task->x8 = 0;
    setup_task(3, -1);
    task = setup_task(6, 14);
    strncpy(task->x10, name_b, 0x20);
    strncpy(task->x19, name_a, 0x20);
    task = setup_task(2, 1);
    if (name_c != NULL) {
        task->xC = task->x10;
        strncpy(task->x10, name_c, 0x20);
    } else {
        task->xC = NULL;
    }
    task->x8 = 0;
    setup_task(3, -1);
    task = setup_task(6, 14);
    strncpy(task->x10, name_c, 0x20);
    strncpy(task->x19, name_b, 0x20);
    return lb_80019CB0(0x10);
}

int lb_8001C2D8(int chan, const char* company, const char* game_name,
                const char* filename)
{
    int enabled;
    int unused;
    s32 result;
    struct CardTask* task;
    struct CardTask* unused_1;
    struct CardTask* unused_2;
    struct CardTask* unused_3;

    lb_80019EF0(chan, 0, 0, 0);
    setup_task(0, 0x10000);
    setup_task(1, 0x201);
    lb_8001A4CC_dontinline(NULL, 0);
    setup_task(3, -1);
    task = setup_task(0xD, 0x80);
    strncpy(lb_80432A68.x2C, company, 2U);
    strncpy(lb_80432A68.x2F, game_name, 4U);
    strncpy(task->x10, filename, 0x20U);
    result = lb_80019CB0(0x10);
    if (result == 0xB) {
        do {
            result = lb_8001B6F8();
        } while (result == 0xB);
    }
    return result;
}

int lb_8001C404(int chan)
{
    s32 memsize;
    s32 sectorsize;
    return lb_80019BB8(CARDProbeEx(chan, &memsize, &sectorsize));
}

int lb_8001C4A8(void* file_entries, void* icon_data)
{
    struct {
        int unk0, unk4, unk8;
    }* entry;
    int i;

    entry = file_entries;
    hsd_803B24E4(&lb_80432A68.unk_A8, 0, 0x2000, lb_80432A68.lib_area);
    hsd_803B2ADC(&lb_80432A68.unk_A8, icon_data);
    i = 0;
    while (entry->unk0 != -1) {
        if (entry->unk0 != 0) {
            hsd_803AC3E0((struct hsd_803AC3E0_arg0_t*) &lb_80432A68.unk_A8, i,
                         entry->unk0, entry->unk4, entry->unk8);
        }
        i++;
        entry++;
    }
    return hsd_803B2674((CardState*) &lb_80432A68.unk_A8);
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
