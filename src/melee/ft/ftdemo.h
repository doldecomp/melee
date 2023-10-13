#ifndef GALE01_0BE7E0
#define GALE01_0BE7E0

#include "ftCommon/forward.h"
#include "pl/forward.h"

#include <placeholder.h>

/* 0BE7E0 */ Fighter_GObj* ftDemo_CreateFighter(plAllocInfo2* alloc_info);
/* 0BEB28 */ void ftDemo_ObjAllocInit(void);
/* 0BEB60 */ void ftDemo_SetArchiveData(int pairs_idx, HSD_Archive* arg1,
                                        int arr_idx);
/* 0BEC08 */ char* ftDemo_GetMotionFileString(int arg0, int arg1);
/* 0BEC74 */ void ftDemo_SetFacingDirection(Fighter_GObj* gobj,
                                            float facing_dir);

#endif
