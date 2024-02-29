#ifndef GALE01_0174BC
#define GALE01_0174BC

#include <platform.h>
#include <baselib/forward.h>

#include <placeholder.h>

typedef void (*lbDvd_Callback)(int, int index, int, int);

/* 015BD0 */ void* lbDvd_80015BD0(s8, s32);
/* 01634C */ u32 lbDvd_8001634C(s16);
/* 017598 */ bool lbDvd_80017598(bool cached);
/* 017700 */ void lbDvd_80017700(int);
/* 017740 */ void* lbDvd_80017740(int type, s16 entry_num, s32 transient_heap,
                                  s32 heap, u32 size, s8 load_state,
                                  s16 load_score, s8, s32 effect_index);
/* 0178E8 */ void lbDvd_800178E8(s32, char*, s32, s32, s32, s32, s32, s32,
                                 s32);
/* 017A80 */ UNK_RET lbDvd_80017A80(UNK_PARAMS);
/* 017E64 */ void lbDvd_80017E64(void*, int, void*, bool);
/* 01819C */ HSD_Archive* lbDvd_8001819C(const char* basename);
/* 018254 */ void lbDvd_80018254(void);
/* 018C6C */ void lbDvd_80018C6C(void);
/* 018F58 */ void lbDvd_80018F58(u8);
/* 018F68 */ void lbDvd_80018F68(void);

#endif
