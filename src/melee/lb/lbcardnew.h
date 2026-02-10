#ifndef MELEE_LB_CARDNEW_H
#define MELEE_LB_CARDNEW_H

#include <placeholder.h>
#include <platform.h>

#include <sysdolphin/baselib/gobj.h>

/* 019BB8 */ int lb_80019BB8(int card_result);
/* 019C38 */ struct CardTask* lb_80019C38(void);
/* 019CB0 */ int lb_80019CB0(int result);
/* 019EF0 */ void lb_80019EF0(int chan, UNK_T save_data, UNK_T status_out,
                              UNK_T callback);
/* 01A008 */ void fn_8001A008(s32 unused, s32 card_result);
/* 01A0B0 */ void fn_8001A0B0(int file_idx, int hsd_error);
/* 01A184 */ int lb_8001A184(void);
/* 01A3A4 */ int lb_8001A3A4(void);
/* 01A4CC */ void lb_8001A4CC(const char* filename, UNK_T file_entries);
/* 01A594 */ int lb_8001A594(char* filename, void* file_entries);
/* 01A860 */ int lb_8001A860(void);
/* 01A8A4 */ int lb_8001A8A4(void);
/* 01A9CC */ int lb_8001A9CC(char* filename);
/* 01AAE4 */ int lb_8001AAE4(const char* old_name, const char* new_name);
/* 01AC04 */ int lb_8001AC04(UNK_T filename);
/* 01ACEC */ int lb_8001ACEC(UNK_T file_entries);
/* 01AE38 */ int lb_8001AE38(UNK_T file_entries);
/* 01AF84 */ int lb_8001AF84(void);
/* 01B068 */ int lb_8001B068(void);
/* 01B14C */ int lb_8001B14C(void);
/* 01B614 */ int lb_8001B614(const char* filename);
/* 01B6E0 */ s32 lb_8001B6E0(s32 file_idx);
/* 01B6F8 */ enum_t lb_8001B6F8(void);
/* 01B760 */ void lb_8001B760(int result);
/* 01B7E0 */ u32 lb_8001B7E0(int chan, char* filename, void* file_entries,
                             void* save_data, int* status_out);
/* 01B8C8 */ bool lb_8001B8C8(int chan);
/* 01B99C */ int lb_8001B99C(int chan, const char* filename, UNK_T status_out);
/* 01BA44 */ bool lb_8001BA44(int chan, const char* filename,
                              UNK_T status_out);
/* 01BB48 */ int lb_8001BB48(int chan, char* filename, void* file_entries,
                             void* save_data, const char* write_buf,
                             int write_offset, int write_len,
                             UNK_T status_out);
/* 01BC18 */ int lb_8001BC18(int chan, char* filename, void** file_entries,
                             void* save_data, const char* write_buf,
                             int write_offset, int write_len,
                             UNK_T status_out);
/* 01BD34 */ enum_t lb_8001BD34(int chan, const char* filename,
                                UNK_T file_entries, UNK_T status_out);
/* 01BE30 */ int lb_8001BE30(int chan, const char* filename,
                             UNK_T file_entries, const char* read_buf,
                             int read_offset, int read_len, UNK_T status_out,
                             UNK_T callback);
/* 01BF04 */ int lb_8001BF04(int chan, char* filename, void* file_entries,
                             const char* write_buf, int write_offset,
                             int write_len, UNK_T status_out);
/* 01BFD8 */ int lb_8001BFD8(int chan, UNK_T snap_buf, UNK_T snap_count,
                             UNK_T snap_max);
/* 01C0F4 */ int lb_8001C0F4(int chan, const char* name_a, const char* name_b,
                             const char* name_c, UNK_T status_out);
/* 01C2D8 */ int lb_8001C2D8(int chan, const char* company,
                             const char* game_name, const char* filename);
/* 01C404 */ int lb_8001C404(int chan);
/* 01C4A8 */ int lb_8001C4A8(void* file_entries, void* icon_data);
/* 01C550 */ void lb_8001C550(void);
/* 01C5A4 */ void lb_8001C5A4(void);
/* 01C5BC */ void lb_8001C5BC(void);

#endif
