#include <dolphin.h>
#include <dolphin/card.h>

#include "__card.h"

BOOL __CARDCompareFileName(CARDDir *ent, const char *fileName) {
    char *entName = (char*)ent->fileName;
    char c1;
    char c2;
    int n = CARD_FILENAME_MAX;

    while (--n >= 0)
    {
        if ((c1 = *entName++) != (c2 = *fileName++))
            return FALSE;
        else if (c2 == '\0')
            return TRUE;
    }

    if (*fileName == '\0')
        return TRUE;
    return FALSE;
}

s32 __CARDAccess(CARDDir *ent) {
    if (ent->gameName[0] == 0xFF)
        return CARD_RESULT_NOFILE;

    if (__CARDDiskID == &__CARDDiskNone
     || (memcmp(ent->gameName, __CARDDiskID->gameName, sizeof(ent->gameName)) == 0
      && memcmp(ent->company, __CARDDiskID->company, sizeof(ent->company)) == 0))
        return CARD_RESULT_READY;

    return CARD_RESULT_NOPERM;
}

s32 __CARDIsPublic(CARDDir *ent) {
    if (ent->gameName[0] == 0xFF)
        return CARD_RESULT_NOFILE;
    if (ent->permission & CARD_ATTR_PUBLIC)
        return 0;
    return CARD_RESULT_NOPERM;
}

s32 __CARDGetFileNo(CARDControl* card, const char* fileName, s32* pfileNo) {
    CARDDir *dir;
    s32 fileNo;

    if (!card->attached)
        return CARD_RESULT_NOCARD;

    dir = __CARDGetDirBlock(card);
    for (fileNo = 0; fileNo < CARD_MAX_FILE; fileNo++)
    {
        CARDDir *ent = &dir[fileNo];
        s32 result = __CARDAccess(ent);

        if (result < 0)
            continue;
        if (__CARDCompareFileName(ent, fileName))
        {
            *pfileNo = fileNo;
            return CARD_RESULT_READY;
        }
    }
    return CARD_RESULT_NOFILE;
}

s32 CARDFastOpen(s32 chan, s32 fileNo, CARDFileInfo *fileInfo) {
    CARDControl *card;
    s32 result;
    CARDDir *dir;
    CARDDir *ent;

    ASSERTLINE(0xDC, 0 <= fileNo && fileNo < CARD_MAX_FILE);
    ASSERTLINE(0xDD, 0 <= chan && chan < 2);

    if (fileNo < 0 || fileNo >= CARD_MAX_FILE)
        return CARD_RESULT_FATAL_ERROR;

    fileInfo->chan = -1;
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0)
        return result;

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileNo];
    result = __CARDAccess(ent);
    if (result == CARD_RESULT_NOPERM)
        result = __CARDIsPublic(ent);
    if (result >= 0)
    {
        if (!CARDIsValidBlockNo(card, ent->startBlock))
            result = CARD_RESULT_BROKEN;
        else
        {
            fileInfo->chan = chan;
            fileInfo->fileNo = fileNo;
            fileInfo->offset = 0;
            fileInfo->iBlock = ent->startBlock;
        }
    }
    return __CARDPutControlBlock(card, result);
}

s32 CARDOpen(s32 chan, char *fileName, CARDFileInfo *fileInfo) {
    CARDControl *card;
    s32 result;
    CARDDir *dir;
    CARDDir *ent;
    s32 fileNo;

    ASSERTLINE(0x11A, 0 <= chan && chan < 2);

    fileInfo->chan = -1;
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0)
        return result;

    result = __CARDGetFileNo(card, fileName, &fileNo);
    if (result >= 0)
    {
        dir = __CARDGetDirBlock(card);
        ent = &dir[fileNo];
        if (!CARDIsValidBlockNo(card, ent->startBlock))
            result = CARD_RESULT_BROKEN;
        else
        {
            fileInfo->chan = chan;
            fileInfo->fileNo = fileNo;
            fileInfo->offset = 0;
            fileInfo->iBlock = ent->startBlock;
        }
    }
    return __CARDPutControlBlock(card, result);
}

s32 CARDClose(CARDFileInfo *fileInfo) {
    CARDControl *card;
    s32 result;

    ASSERTLINE(0x146, 0 <= fileInfo->chan && fileInfo->chan < 2);
    ASSERTLINE(0x147, 0 <= fileInfo->fileNo && fileInfo->fileNo < CARD_MAX_FILE);

    result = __CARDGetControlBlock(fileInfo->chan, &card);
    if (result < 0)
        return result;

    fileInfo->chan = -1;
    return __CARDPutControlBlock(card, CARD_RESULT_READY);
}

BOOL __CARDIsOpened(CARDControl *card, s32 fileNo) {
    return FALSE;
}
