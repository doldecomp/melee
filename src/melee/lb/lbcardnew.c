#include "lbcardnew.h"

#include <Runtime/platform.h>

#include <ctype.h>
#include <placeholder.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include <dolphin/card.h>
#include <sysdolphin/baselib/card.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/memory.h>

#define SECTOR_SIZE 0x2000

typedef enum {
    resultMask_Ready = 1 << LbCardResult_Ready,
    resultMask_2 = 1 << LbCardResult_2,
    resultMask_NoFile = 1 << LbCardResult_NoFile,
    resultMask_NullFilename = 1 << LbCardResult_NullFilename,
    resultMask_Malformed = 1 << LbCardResult_Malformed,
    resultMask_Busy = 1 << LbCardResult_Busy,
    resultMask_BadSectorSize = 1 << LbCardResult_BadSectorSize,
    resultMask_Invalid = 1 << LbCardResult_Invalid,
    resultMask_FatalError = 1 << LbCardResult_FatalError,
    resultMask_DeviceError = 1 << LbCardResult_DeviceError,
    resultMask_16 = 1 << LbCardResult_16,
} resultMask;

/// Operations dispatched by lb_80019CB0. Values describe observed behavior;
/// they are separate from task result codes and the HSD request/command tags.
typedef enum {
    LbCardNewTask_Mount,
    LbCardNewTask_Check,

    /// Checks free space and initializes the HSD state; opens/scans the
    /// named file when it exists.
    LbCardNewTask_Open,

    /// lb_8001A860 maps stored results 0 and 2 to 1. The intended meaning
    /// of this result-normalization step is not established.
    LbCardNewTask_Unk3,

    LbCardNewTask_Format,
    LbCardNewTask_Delete,
    LbCardNewTask_Rename,
    LbCardNewTask_Create,

    /// Reads/writes the configured logical files using the entry buffers.
    LbCardNewTask_Read,

    LbCardNewTask_Write,

    /// Updates the comment/banner/icons header and CARD status.
    LbCardNewTask_SetStatus,

    LbCardNewTask_ReadHeader,
    LbCardNewTask_ListSnapshots,
    LbCardNewTask_FindFile,

    /// Unused task slot; zero is the mount task.
    LbCardNewTask_None,
} CardTaskType;

typedef struct {
    /* 0x00 */ CardTaskType type;

    /// Bit i permits this task to run after result i.
    /* 0x04 */ int result_mask;

    /* 0x08 */ void* file_entries;
    /* 0x0C */ char* filename_ptr;

    /// Copies are limited to CARD_FILENAME_MAX; the extra bytes stay zero
    /// in the static task storage to terminate full-length filenames.
    /* 0x10 */ char filename[CARD_FILENAME_MAX + 1];

    /* 0x31 */ char new_filename[CARD_FILENAME_MAX + 1];
} CardTask;
ASSERT_SIZE(CardTask, 0x54);
ASSERT_OFFSET(CardTask, filename, 0x10);
ASSERT_OFFSET(CardTask, new_filename, 0x31);

/* 019C38 */ static CardTask* getNewTask(void);
/* 019CB0 */ static int executeNextTask(lbCardResult result);
/* 01A0B0 */ static void fn_8001A0B0(int file_idx, int hsd_error);
/* 01A184 */ static int taskMount(void);
/* 01A3A4 */ static int taskCheck(void);
/* 01A594 */ static int taskOpen(const char* filename,
                                 LbCardEntry* file_entries);
/* 01A860 */ static int taskUnk3(void);
/* 01A8A4 */ static int taskFormat(void);
/* 01A9CC */ static int taskDelete(char* filename);
/* 01AAE4 */ static int taskRename(const char* old_name, const char* new_name);
/* 01AC04 */ static int taskCreate(const char* filename);
/* 01ACEC */ static int taskRead(LbCardEntry* file_entries);
/* 01AE38 */ static int taskWrite(LbCardEntry* file_entries);
/* 01AF84 */ static int taskSetStatus(void);
/* 01B068 */ static int taskReadHeader(void);
/* 01B14C */ static int taskListSnapshots(void);
/* 01B614 */ static int taskFindFile(const char* filename);
/* 432A68 */ static struct {
    /* 0x000 */ void* work_area;
    /* 0x004 */ void* lib_area;
    /* 0x008 */ int chan;
    /* 0x00C */ void* save_data;
    /* 0x010 */ int* status;
    /* 0x014 */ char* comment;
    /* 0x018 */ void* banner;
    /* 0x01C */ void* icons;
    /* 0x020 */ lbCardNew_SnapshotEntry* snapshot_entries;
    /* 0x024 */ int* free_blocks;
    /* 0x028 */ int* free_files;
    /* 0x02C */ char company[2];
    /* 0x02E */ char x2E;
    /* 0x02F */ char game_name[4];
    /* 0x034 */ s32 saved_error;
    /* 0x038 */ struct lb_80432A68_38_t unk_38[9];
    /* 0x080 */ bool mounted;
    /* 0x084 */ s32 memsize;
    /* 0x088 */ s32 sectorsize;
    /* 0x08C */ s32 unused_bytes;
    /* 0x090 */ s32 unused_files;
    /* 0x094 */ CARDFileInfo file_info;
    /* 0x0A8 */ CardState card_state;
    /* 0x50C */ LbCardOnFinishedCallback on_finished;
    /* 0x510 */ CardTask task_array[LbCardNewTaskArray_Max];
    /* 0x8AC */ int tasks_remaining;
} state;

#define _p(x) (state.x)

static lbCardResult convertSdkResult(int sdk_result)
{
    switch (sdk_result) {
    case CARD_RESULT_BUSY:
    case CARD_RESULT_WRONGDEVICE:
    case CARD_RESULT_NOCARD:
        return LbCardResult_DeviceError;
    case CARD_RESULT_NOFILE:
        return LbCardResult_NoFile;
    case CARD_RESULT_READY:
        return LbCardResult_Ready;
    case CARD_RESULT_IOERROR:
    case CARD_RESULT_FATAL_ERROR:
        return LbCardResult_FatalError;
    case CARD_RESULT_BROKEN:
    case CARD_RESULT_ENCODING:
        return LbCardResult_Malformed;
    case CARD_RESULT_UNLOCKED:
    case CARD_RESULT_CANCELED:
    default:
        return LbCardResult_Invalid;
    }
}

static CardTask* lb_80019C38_noinline(void)
{
    return getNewTask();
}

CardTask* getNewTask(void)
{
    ssize_t i;
    CardTask* result;

    for (i = 0; i < LbCardNewTaskArray_Max; i++) {
        result = &_p(task_array)[i];
        if (result->type == LbCardNewTask_None) {
            break;
        }
    }
    HSD_ASSERT(340, i != LbCardNewTaskArray_Max);
    return result;
}

static void resetTaskArray(void)
{
    ssize_t i;
    for (i = 0; i < LbCardNewTaskArray_Max; i++) {
        _p(task_array)[i].type = LbCardNewTask_None;
    }
}

int executeNextTask(lbCardResult result)
{
    CardTask* task;
    int i;

    while (true) {
        for (i = 0; i < LbCardNewTaskArray_Max; i++) {
            task = &_p(task_array)[i];
            if (_p(task_array)[i].type != LbCardNewTask_None) {
                break;
            }
        }
        if (i != LbCardNewTaskArray_Max) {
            if (!(task->result_mask & (1 << result))) {
                resetTaskArray();
            } else {
                switch (task->type) {
                case LbCardNewTask_Mount:
                    result = taskMount();
                    break;
                case LbCardNewTask_Check:
                    result = taskCheck();
                    break;
                case LbCardNewTask_Open:
                    result = taskOpen(task->filename_ptr, task->file_entries);
                    break;
                case LbCardNewTask_Unk3:
                    result = taskUnk3();
                    break;
                case LbCardNewTask_Format:
                    result = taskFormat();
                    break;
                case LbCardNewTask_Delete:
                    result = taskDelete(task->filename);
                    break;
                case LbCardNewTask_Rename:
                    result = taskRename(task->filename, task->new_filename);
                    break;
                case LbCardNewTask_Create:
                    result = taskCreate(task->filename);
                    break;
                case LbCardNewTask_Read:
                    result = taskRead(task->file_entries);
                    break;
                case LbCardNewTask_Write:
                    result = taskWrite(task->file_entries);
                    break;
                case LbCardNewTask_SetStatus:
                    result = taskSetStatus();
                    break;
                case LbCardNewTask_ReadHeader:
                    result = taskReadHeader();
                    break;
                case LbCardNewTask_ListSnapshots:
                    result = taskListSnapshots();
                    break;
                case LbCardNewTask_FindFile:
                    result = taskFindFile(task->filename);
                    break;
                default:
                    break;
                }
                task->type = LbCardNewTask_None;
                if (result != LbCardResult_Busy) {
                    continue;
                }
            }
        }
        break;
    }
    if (result != LbCardResult_Busy && _p(on_finished) != NULL) {
        _p(on_finished)(result);
        _p(on_finished) = NULL;
    }
    if (result != LbCardResult_Busy && _p(mounted) != 0) {
        CARDUnmount(_p(chan));
        _p(mounted) = 0;
    }
    return result;
}

static void resetState(int chan, void* save_data, int* status_out,
                       LbCardOnFinishedCallback callback)
{
    int i;

    _p(chan) = chan;
    _p(save_data) = save_data;
    _p(status) = status_out;
    _p(comment) = NULL;
    _p(banner) = NULL;
    _p(icons) = NULL;
    _p(snapshot_entries) = NULL;
    _p(free_blocks) = NULL;
    _p(free_files) = NULL;
    _p(saved_error) = LbCardResult_16;

    for (i = 0; i < (ssize_t) ARRAY_SIZE(_p(unk_38)); i++) {
        _p(unk_38)[i].lb_error = LbCardResult_16;
        _p(unk_38)[i].hsd_result = -1;
    }

    _p(mounted) = false;
    _p(on_finished) = callback;

    resetTaskArray();
}

static void onCardComplete(UNUSED s32 chan, s32 result)
{
    s32 error = convertSdkResult(result);

    if (error != 0) {
        _p(saved_error) = error;
    }
    _p(tasks_remaining) -= 1;
}

static int convertHsdResult(int hsd_result)
{
    int lb_result;
    switch (hsd_result) {
    case 0:
    case 1:
        lb_result = LbCardResult_Ready;
        break;
    case -261:
    case -260:
    case -259:
    case -258:
        lb_result = LbCardResult_2;
        break;
    case -263:
    case -262:
    case -257:
        lb_result = 3;
        break;
    case -264:
    case -265:
    case -266:
    case -267:
        lb_result = LbCardResult_10;
        break;
    default:
        lb_result = convertSdkResult(hsd_result);
        break;
    }
    return lb_result;
}

void fn_8001A0B0(int file_idx, int hsd_error)
{
    s32 error;

    error = convertHsdResult(hsd_error);

    _p(unk_38)[file_idx].lb_error = error;
    _p(unk_38)[file_idx].hsd_result = hsd_error;
    if (error != 0) {
        _p(saved_error) = error;
    }
    _p(tasks_remaining) -= 1;
}

int taskMount(void)
{
    int pending_ops;
    int saved_error;
    int probe_result;
    int mount_result;
    bool enabled;
    int did_disable;
    PAD_STACK(3 * 4);

    did_disable = 0;
    _p(tasks_remaining) = 0;
    probe_result = CARDProbeEx(_p(chan), &_p(memsize), &_p(sectorsize));
    _p(saved_error) = convertSdkResult(probe_result);
    if (_p(saved_error) == 0) {
        if (_p(status) != NULL) {
            *_p(status) = 0;
        }
        HSD_ASSERT(575, _p(work_area));
        enabled = OSDisableInterrupts();
        did_disable = true;
        mount_result =
            CARDMountAsync(_p(chan), _p(work_area), NULL, onCardComplete);

        _p(saved_error) = convertSdkResult(mount_result);
        if (mount_result == 0 || mount_result == -6 || mount_result == -0xD) {
            _p(mounted) = true;
        }
        if (_p(saved_error) == 0) {
            _p(tasks_remaining) += 1;
        }
    }
    pending_ops = _p(tasks_remaining);
    saved_error = _p(saved_error);
    if (did_disable) {
        OSRestoreInterrupts(enabled);
    }
    if (pending_ops) {
        return LbCardResult_Busy;
    }
    return saved_error;
}

int taskCheck(void)
{
    int pending_ops;
    int saved_error;
    int enabled;
    int check_result;
    PAD_STACK(4 * 4);
    _p(tasks_remaining) = 0;
    enabled = OSDisableInterrupts();
    check_result = CARDCheckAsync(_p(chan), onCardComplete);
    _p(saved_error) = convertSdkResult(check_result);
    if (_p(saved_error) == LbCardResult_Ready) {
        _p(tasks_remaining) += 1;
    }
    pending_ops = _p(tasks_remaining);
    saved_error = _p(saved_error);
    OSRestoreInterrupts(enabled);
    if (pending_ops != 0) {
        return LbCardResult_Busy;
    }
    return saved_error;
}

static void setTaskFilename(const char* filename, void* file_entries)
{
    CardTask* task = getNewTask();
    task->type = LbCardNewTask_Open;
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
                                    LbCardEntry* entry)
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

int taskOpen(const char* filename, LbCardEntry* entries)
{
    int open_result;
    int free_result;
    int hsd_result;
    PAD_STACK(6 * 4);

    _p(tasks_remaining) = 0;
    if (_p(sectorsize) != SECTOR_SIZE) {
        _p(saved_error) = LbCardResult_BadSectorSize;
    } else {
        free_result =
            CARDFreeBlocks(_p(chan), &_p(unused_bytes), &_p(unused_files));

        _p(saved_error) = convertSdkResult(free_result);
        if (_p(saved_error) == 0) {
            if (filename == NULL) {
                _p(saved_error) = LbCardResult_NullFilename;
            } else {
                open_result = CARDOpen(_p(chan), filename, &_p(file_info));
                CARDClose(&_p(file_info));
                HSD_ASSERT(712, _p(lib_area));
                hsd_803B24E4(&_p(card_state), _p(chan), SECTOR_SIZE,
                             _p(lib_area));
                if (open_result == LbCardResult_Ready) {
                    hsd_result =
                        hsd_803B2550(&_p(card_state), filename, fn_8001A0B0);

                    _p(saved_error) = convertHsdResult(hsd_result);
                    if (_p(saved_error) == LbCardResult_Ready) {
                        _p(tasks_remaining) += 1;
                    }
                } else if (entries == NULL) {
                    _p(saved_error) = 4;
                } else if (_p(unused_files) == 0) {
                    _p(saved_error) = 6;
                } else {
                    setupCardEntries(&_p(card_state), _p(save_data), entries);
                    if (_p(unused_bytes) <
                        (hsd_803B2674(&_p(card_state)) << 13))
                    {
                        _p(saved_error) = 5;
                    } else {
                        _p(saved_error) = 4;
                    }
                }
            }
        }
    }
    if (_p(tasks_remaining) != 0) {
        return LbCardResult_Busy;
    }
    return _p(saved_error);
}

int taskUnk3(void)
{
    _p(tasks_remaining) = 0;
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

int taskFormat(void)
{
    int pending_ops;
    int saved_error;
    int format_result;
    int enabled;
    int did_disable;
    int unused;

    unused = 0;
    did_disable = 0;
    _p(tasks_remaining) = 0;
    if (_p(mounted) != 0) {
        enabled = OSDisableInterrupts();
        did_disable = 1;
        format_result = CARDFormatAsync(_p(chan), onCardComplete);

        _p(saved_error) = convertSdkResult(format_result);
        if (_p(saved_error) == 0) {
            _p(tasks_remaining) += 1;
        }
    }
    pending_ops = _p(tasks_remaining);
    saved_error = _p(saved_error);
    if (did_disable != 0) {
        OSRestoreInterrupts(enabled);
    }
    if (pending_ops != 0) {
        return LbCardResult_Busy;
    }
    return saved_error;
}

int taskDelete(char* filename)
{
    int unused;
    int pending_ops;
    int saved_error;
    int enabled;
    int delete_result;
    u8 _[8];

    unused = 0;
    _p(tasks_remaining) = 0;
    enabled = OSDisableInterrupts();
    delete_result = CARDDeleteAsync(_p(chan), filename, onCardComplete);

    _p(saved_error) = convertSdkResult(delete_result);
    if (_p(saved_error) == 0) {
        _p(tasks_remaining) += 1;
    }
    pending_ops = _p(tasks_remaining);
    saved_error = _p(saved_error);
    OSRestoreInterrupts(enabled);
    if (pending_ops != 0) {
        return LbCardResult_Busy;
    }
    return saved_error;
}

int taskRename(const char* old_name, const char* new_name)
{
    int unused;
    int pending_ops;
    int saved_error;
    int enabled;
    int rename_result;
    u8 _[8];

    unused = 0;
    _p(tasks_remaining) = 0;
    enabled = OSDisableInterrupts();
    rename_result =
        CARDRenameAsync(_p(chan), old_name, new_name, onCardComplete);
    _p(saved_error) = convertSdkResult(rename_result);
    if (_p(saved_error) == 0) {
        _p(tasks_remaining) += 1;
    }
    pending_ops = _p(tasks_remaining);
    saved_error = _p(saved_error);
    OSRestoreInterrupts(enabled);
    if (pending_ops != 0) {
        return LbCardResult_Busy;
    }
    return saved_error;
}

int taskCreate(const char* filename)
{
    int hsd_result;
    PAD_STACK(4);

    hsd_result = hsd_803B286C(&_p(card_state), filename, _p(comment),
                              _p(banner), _p(icons), fn_8001A0B0);
    _p(saved_error) = convertHsdResult(hsd_result);
    if (_p(saved_error) == 0) {
        _p(tasks_remaining) += 1;
    }
    if (_p(tasks_remaining) != 0) {
        return LbCardResult_Busy;
    }
    return _p(saved_error);
}

/// Preserve the volatile file-size reads in the request builders.
static inline int readCardFileSize(const volatile int* file_size)
{
    return *file_size;
}

int taskRead(LbCardEntry* entries)
{
    int file_error;
    int hsd_result;
    int i;
    UNUSED volatile int cached_size;
    PAD_STACK(4);
    _p(saved_error) = LbCardResult_Ready;
    for (i = 0; i < HSD_CARD_MAX_FILES; i++) {
        UNUSED volatile int cached_data;
        cached_size = readCardFileSize(&_p(card_state).file_sizes[i]);
        cached_data = _p(card_state).file_flags[i];
        if (readCardFileSize(&_p(card_state).file_sizes[i]) != 0) {
            hsd_result =
                hsd_803B29D8(&_p(card_state), i, entries[i].data, fn_8001A0B0);
            _p(unk_38)[i].lb_error = convertHsdResult(hsd_result);
            _p(unk_38)[i].hsd_result = hsd_result;
            file_error = _p(unk_38)[i].lb_error;
            if (file_error == LbCardResult_Ready) {
                _p(tasks_remaining) += 1;
            } else {
                _p(saved_error) = file_error;
            }
        }
    }
    if (_p(tasks_remaining) != 0) {
        return LbCardResult_Busy;
    }
    return _p(saved_error);
}

int taskWrite(LbCardEntry* entries)
{
    int file_error;
    int hsd_result;
    int i;
    UNUSED volatile int cached_flag;
    PAD_STACK(4);

    _p(saved_error) = LbCardResult_Ready;
    for (i = 0; i < HSD_CARD_MAX_FILES; i++) {
        UNUSED volatile int cached_data;
        cached_flag = readCardFileSize(&_p(card_state).file_sizes[i]);
        cached_data = _p(card_state).file_flags[i];
        if (readCardFileSize(&_p(card_state).file_sizes[i]) != 0) {
            hsd_result =
                hsd_803B2A4C(&_p(card_state), i, entries[i].data, fn_8001A0B0);
            _p(unk_38)[i].lb_error = convertHsdResult(hsd_result);
            _p(unk_38)[i].hsd_result = hsd_result;
            file_error = _p(unk_38)[i].lb_error;
            if (file_error == LbCardResult_Ready) {
                _p(tasks_remaining) += 1;
            } else {
                _p(saved_error) = file_error;
            }
        }
    }
    if (_p(tasks_remaining) != 0) {
        return LbCardResult_Busy;
    }
    return _p(saved_error);
}

int taskSetStatus(void)
{
    int hsd_result = hsd_803B2928(&_p(card_state), _p(comment), _p(banner),
                                  _p(icons), fn_8001A0B0);

    _p(saved_error) = convertHsdResult(hsd_result);

    if (_p(saved_error) == 0) {
        _p(tasks_remaining) += 1;
    }
    if (_p(tasks_remaining) != 0) {
        return LbCardResult_Busy;
    }
    return _p(saved_error);
}

int taskReadHeader(void)
{
    int hsd_result = hsd_803B27F4(&_p(card_state), _p(comment), _p(banner),
                                  _p(icons), fn_8001A0B0);

    _p(saved_error) = convertHsdResult(hsd_result);

    if (_p(saved_error) == 0) {
        _p(tasks_remaining) += 1;
    }
    if (_p(tasks_remaining) != 0) {
        return LbCardResult_Busy;
    }
    return _p(saved_error);
}

int taskListSnapshots(void)
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
    _p(tasks_remaining) = 0;
    if (_p(free_blocks) != NULL) {
        *_p(free_blocks) = _p(unused_bytes) / SECTOR_SIZE;
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

int taskFindFile(const char* filename)
{
    CARDStat card_stat;
    int fileno;

    fileno = 0;
    _p(tasks_remaining) = 0;
    while (true) {
        if (CARDGetStatus(_p(chan), fileno, &card_stat) == 0 &&
            strncmp((const char*) card_stat.company, _p(company), 2) == 0 &&
            strncmp((const char*) card_stat.gameName, _p(game_name), 4) == 0 &&
            strcmp(card_stat.fileName, filename) == 0)
        {
            _p(saved_error) = LbCardResult_Ready;
            break;
        } else {
            fileno += 1;
            if (fileno >= 0x7F) {
                _p(saved_error) = LbCardResult_Invalid;
                break;
            }
        }
    }
    return _p(saved_error);
}

s32 lb_8001B6E0(s32 file_idx)
{
    return _p(unk_38)[file_idx].lb_error;
}

int lbCardNew_CompleteNextTask(void)
{
    int enabled;
    int result;

    hsd_803AAA48();
    enabled = OSDisableInterrupts();
    if (_p(tasks_remaining) != 0) {
        result = LbCardResult_Busy;
    } else {
        result = _p(saved_error);
    }
    OSRestoreInterrupts(enabled);
    if (result != LbCardResult_Busy) {
        result = executeNextTask(result);
    }
    return result;
}

int lbCardNew_CompleteAllTasks(int result)
{
    if (result == LbCardResult_Busy) {
        while ((result = lbCardNew_CompleteNextTask()) == LbCardResult_Busy);
    }
    return result;
}

static inline CardTask* setupTask(CardTaskType type, int result_mask)
{
    CardTask* task = getNewTask();
    task->type = type;
    task->result_mask = result_mask;
    return task;
}

static inline void lb_8001A4CC_dontinline(const char* filename,
                                          void* file_entries)
{
    setTaskFilename(filename, file_entries);
}

u32 lb_8001B7E0(int chan, char* filename, void* file_entries, void* save_data,
                int* status_out)
{
    s32 result;
    PAD_STACK(20);

    resetState(chan, save_data, status_out, NULL);
    setupTask(LbCardNewTask_Mount, resultMask_16);
    setupTask(LbCardNewTask_Check, resultMask_Ready | resultMask_Malformed);
    lb_8001A4CC_dontinline(filename, file_entries);
    setupTask(LbCardNewTask_Unk3, U32_MAX);

    result = executeNextTask(LbCardResult_16);
    if (result == LbCardResult_Busy) {
        while ((result = lbCardNew_CompleteNextTask()) == LbCardResult_Busy);
    }
    return result;
}

int lb_8001B8C8(int chan)
{
    int unused_1;
    int unused_2;
    s32 result;
    u8 _[0x18];

    resetState(chan, 0, 0, 0);
    setupTask(LbCardNewTask_Mount, resultMask_16);
    setupTask(LbCardNewTask_Check, resultMask_Ready | resultMask_Malformed);
    setupTask(LbCardNewTask_Format, U32_MAX);

    result = executeNextTask(LbCardResult_16);
    if (result == LbCardResult_Busy) {
        while ((result = lbCardNew_CompleteNextTask()) == LbCardResult_Busy);
    }
    return result;
}

int lbCardNew_DeleteSnap(int chan, const char* filename, UNK_T status_out)
{
    int result;
    resetState(chan, 0, status_out, 0);
    setupTask(LbCardNewTask_Mount, resultMask_16);
    setupTask(LbCardNewTask_Check, resultMask_Ready | resultMask_Malformed);
    lb_8001A4CC_dontinline(filename, 0);
    setupTask(LbCardNewTask_Unk3, U32_MAX);
    result = LbCardResult_16;
    strncpy(setupTask(LbCardNewTask_Delete, 0xE)->filename, filename,
            CARD_FILENAME_MAX);
    return executeNextTask(result);
}

int lb_8001BA44(int chan, const char* filename, UNK_T status_out)
{
    s32 result;
    u8 _[0x10];

    resetState(chan, 0, status_out, 0);
    setupTask(LbCardNewTask_Mount, 0x10000);
    setupTask(LbCardNewTask_Check, 0x201);
    lb_8001A4CC_dontinline(filename, 0);
    setupTask(LbCardNewTask_Unk3, -1);
    strncpy(setupTask(LbCardNewTask_Delete, 0xE)->filename, filename,
            CARD_FILENAME_MAX);
    result = executeNextTask(0x10);
    if (result == LbCardResult_Busy) {
        while ((result = lbCardNew_CompleteNextTask()) == 11) {
        }
    }
    return result;
}

int lb_8001BB48(int chan, char* filename, void* file_entries, void* save_data,
                char* comment, void* banner, void* icons, UNK_T status_out)
{
    int new_var;
    CardTask* task;
    resetState(chan, save_data, status_out, 0);

    task = lb_80019C38_noinline();
    task->type = LbCardNewTask_Mount;
    task->result_mask = 0x10000;
    new_var = 0x20;
    task = lb_80019C38_noinline();
    task->type = LbCardNewTask_Check;
    task->result_mask = 0x201;
    lb_8001A4CC_dontinline(filename, file_entries);
    task = lb_80019C38_noinline();
    task->type = LbCardNewTask_Unk3;
    task->result_mask = -1;

    task = lb_80019C38_noinline();
    task->type = LbCardNewTask_Create;
    task->result_mask = 0x10;
    memcpy(task->filename, filename, new_var);
    _p(comment) = comment;
    _p(banner) = banner;
    _p(icons) = icons;
    return executeNextTask(0x10);
}

int lb_8001BC18(int chan, char* filename, void** file_entries, void* save_data,
                char* comment, void* banner, void* icons, bool* status_out)
{
    size_t size;
    s32 result;
    u8 _[0x18];

    resetState(chan, save_data, status_out, 0);

    setupTask(LbCardNewTask_Mount, 0x10000);
    size = 0x20;
    setupTask(LbCardNewTask_Check, 0x201);
    lb_8001A4CC_dontinline(filename, file_entries);
    setupTask(LbCardNewTask_Unk3, -1);
    memcpy(setupTask(LbCardNewTask_Create, 0x10)->filename, filename, size);
    _p(comment) = comment;
    _p(banner) = banner;
    _p(icons) = icons;
    result = executeNextTask(0x10);

    if (result == LbCardResult_Busy) {
        while ((result = lbCardNew_CompleteNextTask()) == 11) {
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
    CardTask* task;
    u8 _[4];

    resetState(chan, NULL, status_out, NULL);

    setupTask(LbCardNewTask_Mount, 0x10000);
    setupTask(LbCardNewTask_Check, 0x201);
    lb_8001A4CC_dontinline(filename, 0);
    setupTask(LbCardNewTask_Unk3, U32_MAX);
    setupTask(LbCardNewTask_Read, 3)->file_entries = file_entries;

    result = executeNextTask(LbCardResult_16);
    if (result == LbCardResult_Busy) {
        while ((result = lbCardNew_CompleteNextTask()) == LbCardResult_Busy);
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
    CardTask* task;
    resetState(chan, 0, status_out, callback);

    task = getNewTask();
    task->type = LbCardNewTask_Mount;
    task->result_mask = 0x10000;
    task = getNewTask();
    task->type = LbCardNewTask_Check;
    task->result_mask = 0x201;
    setTaskFilename(filename, 0);
    task = getNewTask();
    task->type = LbCardNewTask_Unk3;
    task->result_mask = -1;
    task = getNewTask();
    task->type = LbCardNewTask_SetStatus;
    task->result_mask = 2;
    _p(comment) = comment;
    _p(banner) = banner;
    _p(icons) = icons;
    task = getNewTask();
    task->type = LbCardNewTask_Write;
    task->result_mask = 3;
    task->file_entries = file_entries;
    return executeNextTask(0x10);
}
#ifdef MUST_MATCH
#pragma pop
#endif

int lb_8001BF04(int chan, char* filename, void* file_entries, char* comment,
                void* banner, void* icons, UNK_T status_out)
{
    CardTask* task;
    resetState(chan, 0, status_out, 0);
    task = lb_80019C38_noinline();
    task->type = LbCardNewTask_Mount;
    task->result_mask = 0x10000;
    task = lb_80019C38_noinline();
    task->type = LbCardNewTask_Check;
    task->result_mask = resultMask_Ready | resultMask_Malformed;
    lb_8001A4CC_dontinline(filename, 0);
    task = lb_80019C38_noinline();
    task->type = LbCardNewTask_Unk3;
    task->result_mask = U32_MAX;
    task = lb_80019C38_noinline();
    task->type = LbCardNewTask_ReadHeader;
    task->result_mask = 2;
    _p(comment) = comment;
    _p(banner) = banner;
    _p(icons) = icons;
    task = lb_80019C38_noinline();
    task->type = LbCardNewTask_Read;
    task->result_mask = 3;
    task->file_entries = file_entries;
    return executeNextTask(0x10);
}

int lb_8001BFD8(int chan, lbCardNew_SnapshotEntry* snapshot_entries,
                int* free_blocks, int* free_files)
{
    s32 result;
    u8 _[0x18];

    resetState(chan, 0, 0, 0);
    setupTask(LbCardNewTask_Mount, resultMask_16);
    setupTask(LbCardNewTask_Check, resultMask_Ready | resultMask_Malformed);
    lb_8001A4CC_dontinline(NULL, 0);
    setupTask(LbCardNewTask_Unk3, U32_MAX);
    setupTask(LbCardNewTask_ListSnapshots, resultMask_NullFilename);
    _p(snapshot_entries) = snapshot_entries;
    _p(free_blocks) = free_blocks;
    _p(free_files) = free_files;
    result = executeNextTask(LbCardResult_16);
    if (result == LbCardResult_Busy) {
        while ((result = lbCardNew_CompleteNextTask()) == LbCardResult_Busy);
    }
    return result;
}

int lb_8001C0F4(int chan, const char* name_a, const char* name_b,
                const char* name_c, UNK_T status_out)
{
    CardTask* task;

    resetState(chan, 0, status_out, 0);
    task = lb_80019C38_noinline();
    task->type = LbCardNewTask_Mount;
    task->result_mask = 0x10000;
    task = lb_80019C38_noinline();
    task->type = LbCardNewTask_Check;
    task->result_mask = 0x201;
    lb_8001A4CC_dontinline(name_a, 0);
    task = lb_80019C38_noinline();
    task->type = LbCardNewTask_Unk3;
    task->result_mask = -1;
    task = lb_80019C38_noinline();
    task->type = LbCardNewTask_Rename;
    task->result_mask = 14;
    strncpy(task->filename, name_a, CARD_FILENAME_MAX);
    strncpy(task->new_filename, name_c, CARD_FILENAME_MAX);
    task = lb_80019C38_noinline();
    task->type = LbCardNewTask_Open;
    task->result_mask = 1;
    if (name_b != NULL) {
        task->filename_ptr = task->filename;
        strncpy(task->filename, name_b, CARD_FILENAME_MAX);
    } else {
        task->filename_ptr = NULL;
    }
    task->file_entries = 0;
    task = lb_80019C38_noinline();
    task->type = LbCardNewTask_Unk3;
    task->result_mask = -1;
    task = lb_80019C38_noinline();
    task->type = LbCardNewTask_Rename;
    task->result_mask = 14;
    strncpy(task->filename, name_b, CARD_FILENAME_MAX);
    strncpy(task->new_filename, name_a, CARD_FILENAME_MAX);
    task = lb_80019C38_noinline();
    task->type = LbCardNewTask_Open;
    task->result_mask = 1;
    if (name_c != NULL) {
        task->filename_ptr = task->filename;
        strncpy(task->filename, name_c, CARD_FILENAME_MAX);
    } else {
        task->filename_ptr = NULL;
    }
    task->file_entries = 0;
    task = lb_80019C38_noinline();
    task->type = LbCardNewTask_Unk3;
    task->result_mask = -1;
    task = lb_80019C38_noinline();
    task->type = LbCardNewTask_Rename;
    task->result_mask = 14;
    strncpy(task->filename, name_c, CARD_FILENAME_MAX);
    strncpy(task->new_filename, name_b, CARD_FILENAME_MAX);
    return executeNextTask(0x10);
}

int lb_8001C2D8(int chan, const char* company, const char* game_name,
                const char* filename)
{
    int enabled;
    int unused;
    s32 result;
    CardTask* task;
    CardTask* unused_1;
    CardTask* unused_2;
    CardTask* unused_3;

    resetState(chan, 0, 0, 0);
    setupTask(LbCardNewTask_Mount, 0x10000);
    setupTask(LbCardNewTask_Check, 0x201);
    lb_8001A4CC_dontinline(NULL, 0);
    setupTask(LbCardNewTask_Unk3, -1);
    task = setupTask(LbCardNewTask_FindFile, 0x80);
    strncpy(_p(company), company, 2U);
    strncpy(_p(game_name), game_name, 4U);
    strncpy(task->filename, filename, CARD_FILENAME_MAX);
    result = executeNextTask(0x10);
    if (result == LbCardResult_Busy) {
        while ((result = lbCardNew_CompleteNextTask()) == 11) {
        }
    }
    return result;
}

int lbCardNew_ProbeEx(int chan)
{
    s32 memsize;
    s32 sectorsize;
    return convertSdkResult(CARDProbeEx(chan, &memsize, &sectorsize));
}

int lb_8001C4A8(void* file_entries, void* icon_data)
{
    void* icon = icon_data;
    LbCardEntry* entry;
    CardState* ctx;

    entry = file_entries;
    ctx = &_p(card_state);
    hsd_803B24E4(ctx, 0, SECTOR_SIZE, _p(lib_area));
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

void lbCardNew_ForgetMemory(void)
{
    _p(work_area) = _p(lib_area) = NULL;
}

void lbCardNew_Init(void)
{
    hsd_803B2374();
    resetState(0, NULL, NULL, NULL);
    _p(tasks_remaining) = 0;
}
