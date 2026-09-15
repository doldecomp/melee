#ifndef _DOLPHIN_CARDREAD_H_
#define _DOLPHIN_CARDREAD_H_

s32 CARDReadAsync(CARDFileInfo *fileInfo, void *buf, s32 length, s32 offset, CARDCallback callback);
long CARDRead(struct CARDFileInfo * fileInfo, void * buf, long length, long offset);
s32 CARDCancel(CARDFileInfo *fileInfo);

#endif // _DOLPHIN_CARDREAD_H_
