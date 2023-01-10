#ifndef DOLPHIN_CARD_CARDOPEN_H
#define DOLPHIN_CARD_CARDOPEN_H

#include <dolphin/os/OSExi.h>
#include <dolphin/card.h>

BOOL __CARDCompareFileName(CARDDir* ent, const char* filename);
s32 __CARDAccess(CARDControl* card, CARDDir* ent);
BOOL __CARDIsOpened(CARDControl* card, s32 fileno);
s32 __CARDGetFileNo(CARDControl* card, const char* filename, s32* pfileno);
s32 CARDFastOpen(EXIChannel chan, s32 fileno, CARDFileInfo* fileinfo);
s32 CARDOpen(EXIChannel chan, const char* filename, CARDFileInfo* fileInfo);
s32 __CARDIsPublic(CARDDir* ent);

#endif
