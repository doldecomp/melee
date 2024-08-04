#ifndef _DOLPHIN_CARDOPEN_H_
#define _DOLPHIN_CARDOPEN_H_

s32 CARDFastOpen(s32 chan, s32 fileNo, CARDFileInfo *fileInfo);
s32 CARDOpen(s32 chan, char *fileName, CARDFileInfo *fileInfo);
s32 CARDClose(CARDFileInfo *fileInfo);

#endif // _DOLPHIN_CARDOPEN_H_
