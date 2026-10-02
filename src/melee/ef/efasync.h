#ifndef MELEE_EF_EFASYNC_H
#define MELEE_EF_EFASYNC_H

#include <melee/ef/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <stdarg.h>

#include <melee/ef/types.h>

/* 063930 */ void* efAsync_Dispatch(s32 gfx_id, HSD_GObj* gobj, va_list vlist);
/* 06729C */ void efAsync_LoadAsync(int index);
/* 06730C */ void efAsync_OnLoad(HSD_Archive* archive, u8* data, u32 length,
                                 int index);
/* 06737C */ void efAsync_LoadSync(int index);
/* 06744C */ void efAsync_QueueProcessDeferred(HSD_GObj* gobj,
                                               EF_QueuedEffect* queued_effect);
/* 067624 */ void efAsync_QueueFlush(HSD_GObj* gobj, EF_QueuedEffect** head);
/* 067688 */ void efAsync_QueueClear(EF_QueuedEffect** head);
/* 0676F0 */ void efAsync_Spawn(HSD_GObj* gobj, EF_QueuedEffect** queue_head,
                                u32 spawn_kind, u32 gfx_id, HSD_JObj* jobj,
                                ...);
/* 0676F0 */ void efAsync_QueueInit(void);

extern EF_DAT_Entry efAsync_DatEntries[51];

#endif
