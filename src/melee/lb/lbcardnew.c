#include "lbcardnew.h"

#include <Runtime/platform.h>

#include <ctype.h>
#include <placeholder.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include <dolphin/card.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/hsd_3A94.h>
#include <sysdolphin/baselib/memory.h>

#define SECTOR_SIZE 0x2000

typedef enum {
    error_ok = 0,
    error_null_filename = 7,
    error_bad_sector_size = 12,
} cardError;

typedef enum {
    result_pending_ops = 11,
} cardResult;

/// Operations dispatched by lb_80019CB0. Values describe observed behavior;
/// they are separate from task result codes and the HSD request/command tags.
typedef enum CardTaskType {
    CARD_TASK_MOUNT_CARD = 0x00,
    CARD_TASK_CHECK_CARD = 0x01,
    /// Checks free space and initializes the HSD state; opens/scans the
    /// named file when it exists.
    CARD_TASK_OPEN_FILE = 0x02,
    /// lb_8001A860 maps stored results 0 and 2 to 1. The intended meaning
    /// of this result-normalization step is not established.
    CARD_TASK_UNK_0x03 = 0x03,
    CARD_TASK_FORMAT_CARD = 0x04,
    CARD_TASK_DELETE_FILE = 0x05,
    CARD_TASK_RENAME_FILE = 0x06,
    CARD_TASK_CREATE_FILE = 0x07,
    /// Reads/writes the configured logical files using the entry buffers.
    CARD_TASK_READ_FILES = 0x08,
    CARD_TASK_WRITE_FILES = 0x09,
    /// Updates the comment/banner/icons header and CARD status.
    CARD_TASK_SET_STATUS = 0x0A,
    CARD_TASK_READ_HEADER = 0x0B,
    CARD_TASK_LIST_SNAPSHOTS = 0x0C,
    CARD_TASK_FIND_FILE = 0x0D,
    /// Unused task slot; zero is the mount task.
    CARD_TASK_NONE = 0x0E,
} CardTaskType;

struct CardTask {
    /* 0x00 */ CardTaskType type;
    /// Bit i permits this task to run after result i.
    /* 0x04 */ int result_mask;
    /* 0x08 */ void* file_entries;
    /* 0x0C */ char* filename_ptr;
    /// Copies are limited to CARD_FILENAME_MAX; the extra bytes stay zero
    /// in the static task storage to terminate full-length filenames.
    /* 0x10 */ char filename[CARD_FILENAME_MAX + 1];
    /* 0x31 */ char new_filename[CARD_FILENAME_MAX + 1];
    /* 0x52 */ char pad_52[2];
};
ASSERT_SIZE(struct CardTask, 0x54);
ASSERT_OFFSET(struct CardTask, filename, 0x10);
ASSERT_OFFSET(struct CardTask, new_filename, 0x31);

struct lb_80432A68_t {
    /* 0x000 */ UNK_T work_area;
    /* 0x004 */ UNK_T lib_area;
    /* 0x008 */ int chan;
    /* 0x00C */ UNK_T unk_C;
    /* 0x010 */ int* status;
    /* 0x014 */ char* comment;
    /* 0x018 */ void* banner;
    /* 0x01C */ void* icons;
    /* 0x020 */ lbCardNew_SnapshotEntry* snapshot_entries;
    /* 0x024 */ int* free_blocks;
    /* 0x028 */ int* free_files;
    /* 0x02C */ char x2C[2];
    /* 0x02E */ char x2E;
    /* 0x02F */ char x2F[4];
    /* 0x034 */ s32 saved_error;
    /* 0x038 */ struct lb_80432A68_38_t unk_38[9];
    /* 0x080 */ s32 unk_80;
    /* 0x084 */ s32 memsize;
    /* 0x088 */ s32 sectorsize;
    /* 0x08C */ s32 unused_bytes;
    /* 0x090 */ s32 unused_files;
    /* 0x094 */ CARDFileInfo file_info;
    /* 0x0A8 */ CardState card_state;
    /* 0x50C */ void (*x50C)(int);
    /* 0x510 */ struct CardTask task_array[LbCardNewTaskArray_Max];
    /* 0x8AC */ int pending_ops;
}; /* size = 0x8B0 */
ASSERT_SIZE(struct lb_80432A68_t, 0x8B0);
ASSERT_OFFSET(struct lb_80432A68_t, card_state, 0xA8);
ASSERT_OFFSET(struct lb_80432A68_t, x50C, 0x50C);

/* 019C38 */ static struct CardTask* lb_80019C38(void);

/* 432A68 */ static struct lb_80432A68_t lb_80432A68;

#define _p(x) (lb_80432A68.x)

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

static struct CardTask* lb_80019C38_noinline(void)
{
    return lb_80019C38();
}

struct CardTask* lb_80019C38(void)
{
    int i;
    struct CardTask* result;

    for (i = 0; i < LbCardNewTaskArray_Max; i++) {
        result = &_p(task_array)[i];
        if (result->type == CARD_TASK_NONE) {
            break;
        }
    }
    HSD_ASSERT(340, i != LbCardNewTaskArray_Max);
    return result;
}

static void reset_task_array(void)
{
    int i;
    for (i = 0; i < LbCardNewTaskArray_Max; i++) {
        _p(task_array)[i].type = CARD_TASK_NONE;
    }
}

int lb_80019CB0(int result)
{
    struct CardTask* task;
    int i;

    for (;;) {
        for (i = 0; i < LbCardNewTaskArray_Max; i++) {
            task = &_p(task_array)[i];
            if (_p(task_array)[i].type != CARD_TASK_NONE) {
                break;
            }
        }
        if (i != LbCardNewTaskArray_Max) {
            if (!(task->result_mask & (1 << result))) {
                reset_task_array();
            } else {
                switch (task->type) {
                case CARD_TASK_MOUNT_CARD:
                    result = lb_8001A184();
                    break;
                case CARD_TASK_CHECK_CARD:
                    result = lb_8001A3A4();
                    break;
                case CARD_TASK_OPEN_FILE:
                    result =
                        lb_8001A594(task->filename_ptr, task->file_entries);
                    break;
                case CARD_TASK_UNK_0x03:
                    result = lb_8001A860();
                    break;
                case CARD_TASK_FORMAT_CARD:
                    result = lb_8001A8A4();
                    break;
                case CARD_TASK_DELETE_FILE:
                    result = lb_8001A9CC(task->filename);
                    break;
                case CARD_TASK_RENAME_FILE:
                    result = lb_8001AAE4(task->filename, task->new_filename);
                    break;
                case CARD_TASK_CREATE_FILE:
                    result = lb_8001AC04(task->filename);
                    break;
                case CARD_TASK_READ_FILES:
                    result = lb_8001ACEC(task->file_entries);
                    break;
                case CARD_TASK_WRITE_FILES:
                    result = lb_8001AE38(task->file_entries);
                    break;
                case CARD_TASK_SET_STATUS:
                    result = lb_8001AF84();
                    break;
                case CARD_TASK_READ_HEADER:
                    result = lb_8001B068();
                    break;
                case CARD_TASK_LIST_SNAPSHOTS:
                    result = lb_8001B14C();
                    break;
                case CARD_TASK_FIND_FILE:
                    result = lb_8001B614(task->filename);
                    break;
                default:
                    break;
                }
                task->type = CARD_TASK_NONE;
                if (result != result_pending_ops) {
                    continue;
                }
            }
        }
        break;
    }
    if (result != result_pending_ops && _p(x50C) != NULL) {
        _p(x50C)(result);
        _p(x50C) = NULL;
    }
    if (result != result_pending_ops && _p(unk_80) != 0) {
        CARDUnmount(_p(chan));
        _p(unk_80) = 0;
    }
    return result;
}

void lb_80019EF0(int chan, UNK_T save_data, UNK_T status_out, UNK_T callback)
{
    int i;

    _p(chan) = chan;
    _p(unk_C) = save_data;
    _p(status) = status_out;
    _p(comment) = NULL;
    _p(banner) = NULL;
    _p(icons) = NULL;
    _p(snapshot_entries) = NULL;
    _p(free_blocks) = NULL;
    _p(free_files) = NULL;
    _p(saved_error) = 16;

    for (i = 0; i < (ssize_t) ARRAY_SIZE(_p(unk_38)); i++) {
        _p(unk_38)[i].card_error = 16;
        _p(unk_38)[i].unk_4 = -1;
    }

    _p(unk_80) = 0;
    _p(x50C) = callback;

    reset_task_array();
}

static void onCardComplete(UNUSED s32 chan, s32 result)
{
    s32 error = lb_80019BB8(result);

    if (error != 0) {
        _p(saved_error) = error;
    }
    _p(pending_ops) -= 1;
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

    _p(unk_38)[file_idx].card_error = error;
    _p(unk_38)[file_idx].unk_4 = hsd_error;
    if (error != 0) {
        _p(saved_error) = error;
    }
    _p(pending_ops) -= 1;
}

int lb_8001A184(void)
{
    int pending_ops;
    int saved_error;
    int probe_result;
    int mount_result;
    bool enabled;
    int did_disable;
    PAD_STACK(3 * 4);

    did_disable = 0;
    _p(pending_ops) = 0;
    probe_result = CARDProbeEx(_p(chan), &_p(memsize), &_p(sectorsize));
    _p(saved_error) = lb_80019BB8(probe_result);
    if (_p(saved_error) == 0) {
        if (_p(status) != NULL) {
            *_p(status) = 0;
        }
        HSD_ASSERT(575, _p(work_area));
        enabled = OSDisableInterrupts();
        did_disable = true;
        mount_result =
            CARDMountAsync(_p(chan), _p(work_area), NULL, onCardComplete);

        _p(saved_error) = lb_80019BB8(mount_result);
        if (mount_result == 0 || mount_result == -6 || mount_result == -0xD) {
            _p(unk_80) = true;
        }
        if (_p(saved_error) == 0) {
            _p(pending_ops) += 1;
        }
    }
    pending_ops = _p(pending_ops);
    saved_error = _p(saved_error);
    if (did_disable) {
        OSRestoreInterrupts(enabled);
    }
    if (pending_ops) {
        return result_pending_ops;
    }
    return saved_error;
}

int lb_8001A3A4(void)
{
    int pending_ops;
    int saved_error;
    int enabled;
    int check_result;
    PAD_STACK(4 * 4);
    _p(pending_ops) = 0;
    enabled = OSDisableInterrupts();
    check_result = CARDCheckAsync(_p(chan), onCardComplete);
    _p(saved_error) = lb_80019BB8(check_result);
    if (_p(saved_error) == error_ok) {
        _p(pending_ops) += 1;
    }
    pending_ops = _p(pending_ops);
    saved_error = _p(saved_error);
    OSRestoreInterrupts(enabled);
    if (pending_ops != 0) {
        return result_pending_ops;
    }
    return saved_error;
}

void lb_8001A4CC(const char* filename, void* file_entries)
{
    struct CardTask* task = lb_80019C38();
    task->type = CARD_TASK_OPEN_FILE;
    task->result_mask = 1;
    if (filename != NULL) {
        strncpy(task->filename_ptr = task->filename, filename,
                CARD_FILENAME_MAX);
    } else {
        task->filename_ptr = NULL;
    }
    task->file_entries = file_entries;
}

struct SnapshotNode {
    struct SnapshotNode* next;
    u32 time;
    s16 file_no;
    u16 blocks;
};

static inline void setupCardEntries(CardState* ctx, void* icon,
                                    struct CardEntry* entry)
{
    int i;

    hsd_SetCardIconInfo(ctx, icon);
    i = 0;
    while (entry->file_size != -1) {
        if (entry->file_size != 0) {
            hsd_803AC3E0(ctx, i, entry->file_size, entry->file_flags,
                         entry->data);
        }
        i++;
        entry++;
    }
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
    u8 _[8];

    unused_2 = 0;
    _p(pending_ops) = 0;
    if (_p(sectorsize) != SECTOR_SIZE) {
        _p(saved_error) = error_bad_sector_size;
    } else {
        free_result =
            CARDFreeBlocks(_p(chan), &_p(unused_bytes), &_p(unused_files));

        _p(saved_error) = lb_80019BB8(free_result);
        if (_p(saved_error) == 0) {
            if (filename == NULL) {
                _p(saved_error) = error_null_filename;
            } else {
                open_result = CARDOpen(_p(chan), filename, &_p(file_info));
                CARDClose(&_p(file_info));
                HSD_ASSERT(0x2C8, _p(lib_area));
                hsd_803B24E4(&_p(card_state), _p(chan), 0x2000, _p(lib_area));
                if (open_result == 0) {
                    hsd_result =
                        hsd_803B2550(&_p(card_state), filename, fn_8001A0B0);

                    _p(saved_error) = convert_hsdcard_error(hsd_result);
                    if (_p(saved_error) == 0) {
                        _p(pending_ops) += 1;
                    }
                } else if (file_entries == NULL) {
                    _p(saved_error) = 4;
                } else if (_p(unused_files) == 0) {
                    _p(saved_error) = 6;
                } else {
                    setupCardEntries(&_p(card_state), _p(unk_C), file_entries);
                    if (_p(unused_bytes) <
                        (hsd_803B2674(&_p(card_state)) << 0xD))
                    {
                        _p(saved_error) = 5;
                    } else {
                        _p(saved_error) = 4;
                    }
                }
            }
        }
    }
    if (_p(pending_ops) != 0) {
        return result_pending_ops;
    }
    return _p(saved_error);
}

int lb_8001A860(void)
{
    _p(pending_ops) = 0;
    switch (_p(saved_error)) {
    case 1:
        break;
    case 0:
    case 2:
        _p(saved_error) = 1;
        break;
    }
    return _p(saved_error);
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
    _p(pending_ops) = 0;
    if (_p(unk_80) != 0) {
        enabled = OSDisableInterrupts();
        did_disable = 1;
        format_result = CARDFormatAsync(_p(chan), onCardComplete);

        _p(saved_error) = lb_80019BB8(format_result);
        if (_p(saved_error) == 0) {
            _p(pending_ops) += 1;
        }
    }
    pending_ops = _p(pending_ops);
    saved_error = _p(saved_error);
    if (did_disable != 0) {
        OSRestoreInterrupts(enabled);
    }
    if (pending_ops != 0) {
        return result_pending_ops;
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
    _p(pending_ops) = 0;
    enabled = OSDisableInterrupts();
    delete_result = CARDDeleteAsync(_p(chan), filename, onCardComplete);

    _p(saved_error) = lb_80019BB8(delete_result);
    if (_p(saved_error) == 0) {
        _p(pending_ops) += 1;
    }
    pending_ops = _p(pending_ops);
    saved_error = _p(saved_error);
    OSRestoreInterrupts(enabled);
    if (pending_ops != 0) {
        return result_pending_ops;
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
    _p(pending_ops) = 0;
    enabled = OSDisableInterrupts();
    rename_result =
        CARDRenameAsync(_p(chan), old_name, new_name, onCardComplete);
    _p(saved_error) = lb_80019BB8(rename_result);
    if (_p(saved_error) == 0) {
        _p(pending_ops) += 1;
    }
    pending_ops = _p(pending_ops);
    saved_error = _p(saved_error);
    OSRestoreInterrupts(enabled);
    if (pending_ops != 0) {
        return result_pending_ops;
    }
    return saved_error;
}

int lb_8001AC04(const char* filename)
{
    int hsd_result;
    int unused;

    hsd_result = hsd_803B286C(&_p(card_state), filename, _p(comment),
                              _p(banner), _p(icons), fn_8001A0B0);
    _p(saved_error) = convert_hsdcard_error(hsd_result);
    if (_p(saved_error) == 0) {
        _p(pending_ops) += 1;
    }
    if (_p(pending_ops) != 0) {
        return result_pending_ops;
    }
    return _p(saved_error);
}

/// Preserve the volatile file-size reads in the request builders.
static inline int readCardFileSize(const volatile int* file_size)
{
    return *file_size;
}

int lb_8001ACEC(UNK_T file_entries)
{
    int file_error;
    int hsd_result;
    int unused;
    int i;
    struct CardEntry* entries = file_entries; ///< @todo this seems fake
    volatile int cached_flag;
    volatile int pad_stack;
    volatile int cached_data;

    _p(saved_error) = 0;
    for (i = 0; i < 9; i++) {
        cached_flag = readCardFileSize(&_p(card_state).file_sizes[i]);
        cached_data = _p(card_state).file_flags[i];
        if (readCardFileSize(&_p(card_state).file_sizes[i]) != 0) {
            hsd_result =
                hsd_803B29D8(&_p(card_state), i, entries[i].data, fn_8001A0B0);
            _p(unk_38)[i].card_error = convert_hsdcard_error(hsd_result);
            _p(unk_38)[i].unk_4 = hsd_result;
            file_error = _p(unk_38)[i].card_error;
            if (file_error == 0) {
                _p(pending_ops) += 1;
            } else {
                _p(saved_error) = file_error;
            }
        }
    }
    if (_p(pending_ops) != 0) {
        return result_pending_ops;
    }
    return _p(saved_error);
}

int lb_8001AE38(UNK_T file_entries)
{
    int file_error;
    int hsd_result;
    int unused;
    int i;
    struct CardEntry* entries = file_entries; ///< @todo this seems fake
    volatile int cached_flag;
    volatile int pad_stack;
    volatile int cached_data;

    _p(saved_error) = 0;
    for (i = 0; i < 9; i++) {
        cached_flag = readCardFileSize(&_p(card_state).file_sizes[i]);
        cached_data = _p(card_state).file_flags[i];
        if (readCardFileSize(&_p(card_state).file_sizes[i]) != 0) {
            hsd_result =
                hsd_803B2A4C(&_p(card_state), i, entries[i].data, fn_8001A0B0);
            _p(unk_38)[i].card_error = convert_hsdcard_error(hsd_result);
            _p(unk_38)[i].unk_4 = hsd_result;
            file_error = _p(unk_38)[i].card_error;
            if (file_error == 0) {
                _p(pending_ops) += 1;
            } else {
                _p(saved_error) = file_error;
            }
        }
    }
    if (_p(pending_ops) != 0) {
        return result_pending_ops;
    }
    return _p(saved_error);
}

int lb_8001AF84(void)
{
    int hsd_result = hsd_803B2928(&_p(card_state), _p(comment), _p(banner),
                                  _p(icons), fn_8001A0B0);

    _p(saved_error) = convert_hsdcard_error(hsd_result);

    if (_p(saved_error) == 0) {
        _p(pending_ops) += 1;
    }
    if (_p(pending_ops) != 0) {
        return result_pending_ops;
    }
    return _p(saved_error);
}

int lb_8001B068(void)
{
    int hsd_result = hsd_803B27F4(&_p(card_state), _p(comment), _p(banner),
                                  _p(icons), fn_8001A0B0);

    _p(saved_error) = convert_hsdcard_error(hsd_result);

    if (_p(saved_error) == 0) {
        _p(pending_ops) += 1;
    }
    if (_p(pending_ops) != 0) {
        return result_pending_ops;
    }
    return _p(saved_error);
}

int lb_8001B14C(void)
{
    struct SnapshotNode* head;
    CARDStat stat[1];
    struct SnapshotNode* node;
    char* company;
    char* game;
    struct SnapshotNode* nodes;
    DVDDiskID* disk_id;
    int file_no;
    int count;
    int i;
    struct SnapshotNode** scan;
    static size_t const nodes_len = 127;

    head = NULL;
    disk_id = DVDGetCurrentDiskID();
    _p(pending_ops) = 0;
    if (_p(free_blocks) != NULL) {
        *_p(free_blocks) = _p(unused_bytes) / 0x2000;
    }
    if (_p(free_files) != NULL) {
        *_p(free_files) = _p(unused_files);
    }
    nodes = HSD_MemAlloc(sizeof(*nodes) * nodes_len);
    node = nodes;
    company = (char*) stat[0].company;
    game = (char*) stat[0].gameName;
    count = 0;
    for (file_no = 0; file_no < 0x7F; file_no++) {
        if (CARDGetStatus(_p(chan), file_no, stat) == 0 &&
            strncmp(company, disk_id->company, 2) == 0 &&
            strncmp(game, disk_id->gameName, 4) == 0 &&
            isdigit(stat[0].fileName[0]))
        {
            node->time = strtoul(stat[0].fileName, NULL, 10);
            node->file_no = file_no;
            node->blocks = stat[0].length >> 13;
            scan = &head;
            while (*scan != NULL && (*scan)->time > node->time) {
                scan = &(*scan)->next;
            }
            node->next = *scan;
            count++;
            *scan = node;
            node++;
        }
    }
    scan = &head;
    for (file_no = 0; file_no < count; file_no++) {
        _p(snapshot_entries)[file_no].time = (*scan)->time;
        _p(snapshot_entries)[file_no].file_no = (*scan)->file_no;
        _p(snapshot_entries)[file_no].blocks = (*scan)->blocks;
        scan = &(*scan)->next;
    }
    for (i = count; i < 0x7F; i++) {
        _p(snapshot_entries)[i].file_no = -1;
    }
    HSD_Free(nodes);
    _p(saved_error) = 0;
    return _p(saved_error);
}

int lb_8001B614(const char* filename)
{
    CARDStat card_stat;
    int fileno;

    fileno = 0;
    _p(pending_ops) = 0;
    for (;;) {
        if (CARDGetStatus(_p(chan), fileno, &card_stat) == 0 &&
            strncmp((const char*) card_stat.company, _p(x2C), 2) == 0 &&
            strncmp((const char*) card_stat.gameName, _p(x2F), 4) == 0 &&
            strcmp(card_stat.fileName, filename) == 0)
        {
            _p(saved_error) = 0;
            break;
        } else {
            fileno += 1;
            if (fileno >= 0x7F) {
                _p(saved_error) = 0xD;
                break;
            }
        }
    }
    return _p(saved_error);
}

s32 lb_8001B6E0(s32 file_idx)
{
    return _p(unk_38)[file_idx].card_error;
}

int lb_8001B6F8(void)
{
    int enabled;
    int result;

    hsd_803AAA48();
    enabled = OSDisableInterrupts();
    if (_p(pending_ops) != 0) {
        result = result_pending_ops;
    } else {
        result = _p(saved_error);
    }
    OSRestoreInterrupts(enabled);
    if (result != result_pending_ops) {
        result = lb_80019CB0(result);
    }
    return result;
}

int lb_8001B760(int result)
{
    if (result == 11) {
        while ((result = lb_8001B6F8()) == 11) {
        }
    }
    return result;
}

static inline struct CardTask* setup_task(CardTaskType type, int result_mask)
{
    struct CardTask* task = lb_80019C38();
    task->type = type;
    task->result_mask = result_mask;
    return task;
}

static inline void lb_8001A4CC_dontinline(const char* filename,
                                          void* file_entries)
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
    setup_task(CARD_TASK_MOUNT_CARD, 0x10000);
    setup_task(CARD_TASK_CHECK_CARD, 0x201);
    lb_8001A4CC_dontinline(filename, file_entries);
    setup_task(CARD_TASK_UNK_0x03, -1);

    result = lb_80019CB0(0x10);
    if (result == result_pending_ops) {
        while ((result = lb_8001B6F8()) == 11) {
        }
    }
    return result;
}

int lb_8001B8C8(int chan)
{
    int unused_1;
    int unused_2;
    s32 result;
    u8 _[0x18];

    lb_80019EF0(chan, 0, 0, 0);
    setup_task(CARD_TASK_MOUNT_CARD, 0x10000);
    setup_task(CARD_TASK_CHECK_CARD, 0x201);
    setup_task(CARD_TASK_FORMAT_CARD, -1);

    result = lb_80019CB0(0x10);
    if (result == result_pending_ops) {
        while ((result = lb_8001B6F8()) == 11) {
        }
    }
    return result;
}

int lb_8001B99C(int chan, const char* filename, UNK_T status_out)
{
    int new_var;
    lb_80019EF0(chan, 0, status_out, 0);
    setup_task(CARD_TASK_MOUNT_CARD, 0x10000);
    setup_task(CARD_TASK_CHECK_CARD, 0x201);
    lb_8001A4CC_dontinline(filename, 0);
    setup_task(CARD_TASK_UNK_0x03, -1);
    new_var = 0x10;
    strncpy(setup_task(CARD_TASK_DELETE_FILE, 0xE)->filename, filename,
            CARD_FILENAME_MAX);
    return lb_80019CB0(new_var);
}

int lb_8001BA44(int chan, const char* filename, UNK_T status_out)
{
    s32 result;
    u8 _[0x10];

    lb_80019EF0(chan, 0, status_out, 0);
    setup_task(CARD_TASK_MOUNT_CARD, 0x10000);
    setup_task(CARD_TASK_CHECK_CARD, 0x201);
    lb_8001A4CC_dontinline(filename, 0);
    setup_task(CARD_TASK_UNK_0x03, -1);
    strncpy(setup_task(CARD_TASK_DELETE_FILE, 0xE)->filename, filename,
            CARD_FILENAME_MAX);
    result = lb_80019CB0(0x10);
    if (result == result_pending_ops) {
        while ((result = lb_8001B6F8()) == 11) {
        }
    }
    return result;
}

int lb_8001BB48(int chan, char* filename, void* file_entries, void* save_data,
                char* comment, void* banner, void* icons, UNK_T status_out)
{
    int new_var;
    struct CardTask* task;
    lb_80019EF0(chan, save_data, status_out, 0);

    task = lb_80019C38_noinline();
    task->type = CARD_TASK_MOUNT_CARD;
    task->result_mask = 0x10000;
    new_var = 0x20;
    task = lb_80019C38_noinline();
    task->type = CARD_TASK_CHECK_CARD;
    task->result_mask = 0x201;
    lb_8001A4CC_dontinline(filename, file_entries);
    task = lb_80019C38_noinline();
    task->type = CARD_TASK_UNK_0x03;
    task->result_mask = -1;

    task = lb_80019C38_noinline();
    task->type = CARD_TASK_CREATE_FILE;
    task->result_mask = 0x10;
    memcpy(task->filename, filename, new_var);
    _p(comment) = comment;
    _p(banner) = banner;
    _p(icons) = icons;
    return lb_80019CB0(0x10);
}

int lb_8001BC18(int chan, char* filename, void** file_entries, void* save_data,
                char* comment, void* banner, void* icons, UNK_T status_out)
{
    int new_var;
    s32 result;
    u8 _[0x18];

    lb_80019EF0(chan, save_data, status_out, 0);

    setup_task(CARD_TASK_MOUNT_CARD, 0x10000);
    new_var = 0x20;
    setup_task(CARD_TASK_CHECK_CARD, 0x201);
    lb_8001A4CC_dontinline(filename, file_entries);
    setup_task(CARD_TASK_UNK_0x03, -1);
    memcpy(setup_task(CARD_TASK_CREATE_FILE, 0x10)->filename, filename,
           new_var);
    _p(comment) = comment;
    _p(banner) = banner;
    _p(icons) = icons;
    result = lb_80019CB0(0x10);

    if (result == result_pending_ops) {
        while ((result = lb_8001B6F8()) == 11) {
        }
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

    setup_task(CARD_TASK_MOUNT_CARD, 0x10000);
    setup_task(CARD_TASK_CHECK_CARD, 0x201);
    lb_8001A4CC_dontinline(filename, 0);
    setup_task(CARD_TASK_UNK_0x03, -1);
    setup_task(CARD_TASK_READ_FILES, 3)->file_entries = file_entries;

    result = lb_80019CB0(0x10);
    if (result == result_pending_ops) {
        while ((result = lb_8001B6F8()) == 11) {
        }
    }
    return result;
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
int lb_8001BE30(int chan, const char* filename, UNK_T file_entries,
                char* comment, void* banner, void* icons, UNK_T status_out,
                UNK_T callback)
{
    struct CardTask* task;
    lb_80019EF0(chan, 0, status_out, callback);

    task = lb_80019C38();
    task->type = CARD_TASK_MOUNT_CARD;
    task->result_mask = 0x10000;
    task = lb_80019C38();
    task->type = CARD_TASK_CHECK_CARD;
    task->result_mask = 0x201;
    lb_8001A4CC(filename, 0);
    task = lb_80019C38();
    task->type = CARD_TASK_UNK_0x03;
    task->result_mask = -1;
    task = lb_80019C38();
    task->type = CARD_TASK_SET_STATUS;
    task->result_mask = 2;
    _p(comment) = comment;
    _p(banner) = banner;
    _p(icons) = icons;
    task = lb_80019C38();
    task->type = CARD_TASK_WRITE_FILES;
    task->result_mask = 3;
    task->file_entries = file_entries;
    return lb_80019CB0(0x10);
}
#ifdef MUST_MATCH
#pragma pop
#endif

int lb_8001BF04(int chan, char* filename, void* file_entries, char* comment,
                void* banner, void* icons, UNK_T status_out)
{
    struct CardTask* task;
    lb_80019EF0(chan, 0, status_out, 0);
    task = lb_80019C38_noinline();
    task->type = CARD_TASK_MOUNT_CARD;
    task->result_mask = 0x10000;
    task = lb_80019C38_noinline();
    task->type = CARD_TASK_CHECK_CARD;
    task->result_mask = 0x201;
    lb_8001A4CC_dontinline(filename, 0);
    task = lb_80019C38_noinline();
    task->type = CARD_TASK_UNK_0x03;
    task->result_mask = -1;
    task = lb_80019C38_noinline();
    task->type = CARD_TASK_READ_HEADER;
    task->result_mask = 2;
    _p(comment) = comment;
    _p(banner) = banner;
    _p(icons) = icons;
    task = lb_80019C38_noinline();
    task->type = CARD_TASK_READ_FILES;
    task->result_mask = 3;
    task->file_entries = file_entries;
    return lb_80019CB0(0x10);
}

int lb_8001BFD8(int chan, lbCardNew_SnapshotEntry* snapshot_entries,
                int* free_blocks, int* free_files)
{
    s32 result;
    u8 _[0x18];

    lb_80019EF0(chan, 0, 0, 0);
    setup_task(CARD_TASK_MOUNT_CARD, 0x10000);
    setup_task(CARD_TASK_CHECK_CARD, 0x201);
    lb_8001A4CC_dontinline(NULL, 0);
    setup_task(CARD_TASK_UNK_0x03, -1);
    setup_task(CARD_TASK_LIST_SNAPSHOTS, 0x80);
    _p(snapshot_entries) = snapshot_entries;
    _p(free_blocks) = free_blocks;
    _p(free_files) = free_files;
    result = lb_80019CB0(0x10);
    if (result == result_pending_ops) {
        while ((result = lb_8001B6F8()) == 11) {
        }
    }
    return result;
}

int lb_8001C0F4(int chan, const char* name_a, const char* name_b,
                const char* name_c, UNK_T status_out)
{
    struct CardTask* task;

    lb_80019EF0(chan, 0, status_out, 0);
    task = lb_80019C38_noinline();
    task->type = CARD_TASK_MOUNT_CARD;
    task->result_mask = 0x10000;
    task = lb_80019C38_noinline();
    task->type = CARD_TASK_CHECK_CARD;
    task->result_mask = 0x201;
    lb_8001A4CC_dontinline(name_a, 0);
    task = lb_80019C38_noinline();
    task->type = CARD_TASK_UNK_0x03;
    task->result_mask = -1;
    task = lb_80019C38_noinline();
    task->type = CARD_TASK_RENAME_FILE;
    task->result_mask = 14;
    strncpy(task->filename, name_a, CARD_FILENAME_MAX);
    strncpy(task->new_filename, name_c, CARD_FILENAME_MAX);
    task = lb_80019C38_noinline();
    task->type = CARD_TASK_OPEN_FILE;
    task->result_mask = 1;
    if (name_b != NULL) {
        task->filename_ptr = task->filename;
        strncpy(task->filename, name_b, CARD_FILENAME_MAX);
    } else {
        task->filename_ptr = NULL;
    }
    task->file_entries = 0;
    task = lb_80019C38_noinline();
    task->type = CARD_TASK_UNK_0x03;
    task->result_mask = -1;
    task = lb_80019C38_noinline();
    task->type = CARD_TASK_RENAME_FILE;
    task->result_mask = 14;
    strncpy(task->filename, name_b, CARD_FILENAME_MAX);
    strncpy(task->new_filename, name_a, CARD_FILENAME_MAX);
    task = lb_80019C38_noinline();
    task->type = CARD_TASK_OPEN_FILE;
    task->result_mask = 1;
    if (name_c != NULL) {
        task->filename_ptr = task->filename;
        strncpy(task->filename, name_c, CARD_FILENAME_MAX);
    } else {
        task->filename_ptr = NULL;
    }
    task->file_entries = 0;
    task = lb_80019C38_noinline();
    task->type = CARD_TASK_UNK_0x03;
    task->result_mask = -1;
    task = lb_80019C38_noinline();
    task->type = CARD_TASK_RENAME_FILE;
    task->result_mask = 14;
    strncpy(task->filename, name_c, CARD_FILENAME_MAX);
    strncpy(task->new_filename, name_b, CARD_FILENAME_MAX);
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
    setup_task(CARD_TASK_MOUNT_CARD, 0x10000);
    setup_task(CARD_TASK_CHECK_CARD, 0x201);
    lb_8001A4CC_dontinline(NULL, 0);
    setup_task(CARD_TASK_UNK_0x03, -1);
    task = setup_task(CARD_TASK_FIND_FILE, 0x80);
    strncpy(_p(x2C), company, 2U);
    strncpy(_p(x2F), game_name, 4U);
    strncpy(task->filename, filename, CARD_FILENAME_MAX);
    result = lb_80019CB0(0x10);
    if (result == result_pending_ops) {
        while ((result = lb_8001B6F8()) == 11) {
        }
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
    void* icon = icon_data;
    struct CardEntry* entry;
    CardState* ctx;

    entry = file_entries;
    ctx = &_p(card_state);
    hsd_803B24E4(ctx, 0, 0x2000, _p(lib_area));
    hsd_SetCardIconInfo(ctx, icon);
    {
        int i;

        i = 0;
        while (entry->file_size != -1) {
            if (entry->file_size != 0) {
                hsd_803AC3E0(ctx, i, entry->file_size, entry->file_flags,
                             entry->data);
            }
            i++;
            entry++;
        }
    }
    return hsd_803B2674(ctx);
}

void lbCardNew_AllocWorkArea(void)
{
    if (_p(work_area) == NULL) {
        _p(work_area) = HSD_MemAlloc(0xA000);
        _p(lib_area) = HSD_MemAlloc(0x2000);
    }
}

void lb_8001C5A4(void)
{
    _p(work_area) = _p(lib_area) = NULL;
}

void lb_8001C5BC(void)
{
    hsd_803B2374();
    lb_80019EF0(0, NULL, NULL, NULL);
    _p(pending_ops) = 0;
}
