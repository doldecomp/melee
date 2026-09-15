#ifndef SYSDOLPHIN_BASELIB_3B27_H
#define SYSDOLPHIN_BASELIB_3B27_H

#include <Runtime/platform.h>

#include <placeholder.h>

#include <sysdolphin/baselib/hsd_3A94.h>

/// Queues a header read into the non-NULL destination buffers. Returns 0
/// when queued, not when complete; a negative return does not queue a
/// request or invoke the callback. The same return contract applies to
/// the create, status, read and write request functions below.
/* 3B27F4 */ int hsd_803B27F4(CardState* state, void* comment, void* banner,
                              void* icons, CardCallback callback);
/// Queues file creation. Copies 0x40 bytes from comment into state even if
/// the queue is full; filename, banner and icons are borrowed.
/* 3B286C */ int hsd_803B286C(CardState* state, const char* filename,
                              const char* comment, void* banner, void* icons,
                              CardCallback callback);
/// Queues a header/status update. Copies 0x40 bytes from comment into state
/// even if the queue is full; banner and icons are borrowed.
/* 3B2928 */ int hsd_803B2928(CardState* state, const char* comment,
                              void* banner, void* icons,
                              CardCallback callback);
/// Queues a logical-file read into the borrowed destination buffer.
/* 3B29D8 */ int hsd_803B29D8(CardState* state, int file_idx, u8* buf,
                              CardCallback callback);
/// Queues a logical-file write from the borrowed source buffer.
/* 3B2A4C */ int hsd_803B2A4C(CardState* state, int file_idx, u8* buf,
                              CardCallback callback);
/* 3B2ADC */ int hsd_SetCardIconInfo(CardState* state,
                                     CardIconInfo* icon_info);

#endif
