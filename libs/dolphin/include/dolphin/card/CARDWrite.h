#ifndef _DOLPHIN_CARDWRITE_H_
#define _DOLPHIN_CARDWRITE_H_

s32 CARDWriteAsync(CARDFileInfo* fileInfo, void* buf, s32 length, s32 offset,
                   CARDCallback callback);
s32 CARDWrite(CARDFileInfo* fileInfo, void* buf, s32 length, s32 offset);

#endif // _DOLPHIN_CARDWRITE_H_
