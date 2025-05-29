#ifndef GALE01_0174BC
#define GALE01_0174BC

#include <placeholder.h>

#include "lb/forward.h"
#include <baselib/forward.h>

typedef void (*lbDvd_Callback)(int, int index, int, int);

/* 015BD0 */ void* lbDvd_80015BD0(s8, s32);
/* 01634C */ u32 lbDvd_8001634C(s16);
/* 0174BC */ UNK_RET lbDvd_800174BC(UNK_PARAMS);
/* 0174E8 */ void lbDvd_800174E8(s32 index);
/* 017598 */ bool lbDvd_80017598(bool cached);
/* 017644 */ UNK_RET lbDvd_80017644(UNK_PARAMS);
/* 017700 */ void lbDvd_80017700(int);
/* 017740 */ void* lbDvd_80017740(int type, s16 entry_num, s32 transient_heap,
                                  s32 heap, u32 size, s8 load_state,
                                  s16 load_score, s8, s32 effect_index);
/* 0178E8 */ void lbDvd_800178E8(s32, char*, s32, s32, s32, s32, s32, s32,
                                 s32);
/* 017960 */ UNK_RET lbDvd_80017960(UNK_PARAMS);
/* 017A80 */ UNK_RET lbDvd_80017A80(UNK_PARAMS);
/* 017AB0 */ void lbDvd_CachePreloadedFile(s32 index);
/* 017CC4 */ UNK_RET lbDvd_80017CC4(UNK_PARAMS);
/* 017E64 */ void lbDvd_80017E64(void*, int, void*, bool);
/* 017EBC */ HSD_Archive* lbDvd_GetPreloadedArchive(s32);
/* 01819C */ HSD_Archive* lbDvd_8001819C(const char* basename);
/* 01822C */ PreloadCacheScene* lbDvd_8001822C(void);
/* 01823C */ void lbDvd_8001823C(void);
/* 018254 */ void lbDvd_80018254(void);
/* 0187F4 */ UNK_RET lbDvd_800187F4(UNK_PARAMS);
/* 018A2C */ UNK_RET lbDvd_80018A2C(UNK_PARAMS);
/* 018C2C */ UNK_RET lbDvd_80018C2C(UNK_PARAMS);
/* 018C6C */ void lbDvd_80018C6C(void);
/* 018CF4 */ UNK_RET lbDvd_80018CF4(UNK_PARAMS);
/* 018F58 */ void lbDvd_80018F58(bool value);
/* 018F68 */ void lbDvd_80018F68(void);
/* 019100 */ UNK_RET lbDvd_80019100(UNK_PARAMS);

#endif
