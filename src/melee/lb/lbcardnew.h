#ifndef MELEE_LB_CARDNEW_H
#define MELEE_LB_CARDNEW_H

#include <Runtime/platform.h>

#include <melee/lb/forward.h>

#include <placeholder.h>

typedef enum {
    LbCardResult_Ready,
    LbCardResult_2 = 2,
    LbCardResult_NoFile = 4,
    LbCardResult_NullFilename = 7,
    LbCardResult_Malformed = 9,
    LbCardResult_Busy = 11,
    LbCardResult_BadSectorSize,
    LbCardResult_Invalid,
    LbCardResult_FatalError,
    LbCardResult_DeviceError,
    LbCardResult_16,
} lbCardResult;

typedef struct {
    int file_size;
    int file_flags;
    void* data;
} LbCardEntry;

/* 019EF0 */ void lb_80019EF0(int chan, UNK_T save_data, UNK_T status_out,
                              UNK_T callback);
/* 01A0B0 */ void fn_8001A0B0(int file_idx, int hsd_error);
/* 01A184 */ int taskMount(void);
/* 01A3A4 */ int taskCheck(void);
/* 01A4CC */ void lb_8001A4CC(const char* filename, UNK_T file_entries);
/* 01A860 */ int taskUnk3(void);
/* 01A8A4 */ int taskFormat(void);
/* 01A9CC */ int taskDelete(char* filename);
/* 01AAE4 */ int taskRename(const char* old_name, const char* new_name);
/* 01AC04 */ int taskCreate(const char* filename);
/* 01ACEC */ int taskRead(LbCardEntry* file_entries);
/* 01AE38 */ int taskWrite(LbCardEntry* file_entries);
/* 01AF84 */ int taskSetStatus(void);
/* 01B068 */ int taskReadHeader(void);
/* 01B14C */ int taskListSnapshots(void);
/* 01B614 */ int taskFindFile(const char* filename);
/* 01B6E0 */ s32 lb_8001B6E0(s32 file_idx);
/* 01B6F8 */ enum_t lbCardNew_CompleteNextTask(void);
/* 01B760 */ int lbCardNew_CompleteAllTasks(int result);
/* 01B7E0 */ u32 lb_8001B7E0(int chan, char* filename, void* file_entries,
                             void* save_data, int* status_out);
/* 01B8C8 */ bool lb_8001B8C8(int chan);
/* 01B99C */ int lb_8001B99C(int chan, const char* filename, UNK_T status_out);
/* 01BA44 */ bool lb_8001BA44(int chan, const char* filename,
                              UNK_T status_out);
/* 01BB48 */ int lb_8001BB48(int chan, char* filename, void* file_entries,
                             void* save_data, char* comment, void* banner,
                             void* icons, UNK_T status_out);
/* 01BC18 */ int lb_8001BC18(int chan, char* filename, void** file_entries,
                             void* save_data, char* comment, void* banner,
                             void* icons, bool* status_out);
/* 01BD34 */ enum_t lb_8001BD34(int chan, const char* filename,
                                UNK_T file_entries, UNK_T status_out);
/* 01BE30 */ int lb_8001BE30(int chan, const char* filename,
                             UNK_T file_entries, char* comment, void* banner,
                             void* icons, UNK_T status_out, UNK_T callback);
/* 01BF04 */ int lb_8001BF04(int chan, char* filename, void* file_entries,
                             char* comment, void* banner, void* icons,
                             UNK_T status_out);
/* 01BFD8 */ int lb_8001BFD8(int chan,
                             lbCardNew_SnapshotEntry* snapshot_entries,
                             int* free_blocks, int* free_files);
/* 01C0F4 */ int lb_8001C0F4(int chan, const char* name_a, const char* name_b,
                             const char* name_c, UNK_T status_out);
/* 01C2D8 */ int lb_8001C2D8(int chan, const char* company,
                             const char* game_name, const char* filename);
/* 01C404 */ int lbCardNew_ProbeEx(int chan);
/* 01C4A8 */ int lb_8001C4A8(void* file_entries, void* icon_data);
/* 01C550 */ void lbCardNew_AllocWorkArea(void);
/* 01C5A4 */ void lb_8001C5A4(void);
/* 01C5BC */ void lb_8001C5BC(void);

#endif
