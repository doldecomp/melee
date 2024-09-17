#ifndef _DOLPHIN_HIO_H_

#include <platform.h>

#define HIO_DEV Dev

typedef void (*HIOCallback)(void);
typedef bool (*HIOEnumCallback)(s32 chan);

bool HIOEnumDevices(HIOEnumCallback callback);
bool HIOInit(s32 chan, HIOCallback callback);
bool HIOReadMailbox(u32* word);
bool HIOWriteMailbox(u32 word);
bool HIORead(u32 addr, void* buffer, s32 size);
bool HIOWrite(u32 addr, void* buffer, s32 size);
bool HIOReadAsync(u32 addr, void* buffer, s32 size, HIOCallback callback);
bool HIOWriteAsync(u32 addr, void* buffer, s32 size, HIOCallback callback);
bool HIOReadStatus(u32* status);

#endif
