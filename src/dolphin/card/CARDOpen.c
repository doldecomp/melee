#include <dolphin/card.h>

extern DVDDiskID __CARDDiskNone;

#define CARDIsValidBlockNo(card, iBlock)                                       \
    (CARD_NUM_SYSTEM_BLOCK <= (iBlock) && (iBlock) < (card)->cBlock)

BOOL __CARDCompareFileName(CARDDir* ent, const char* filename)
{
    char* entName;
    char c1;
    char c2;
    int n;

    entName = (char*) ent->fileName;
    n = CARD_FILENAME_MAX;
    while (0 <= --n) {
        if ((c1 = *entName++) != (c2 = *filename++)) {
            return FALSE;
        } else if (c2 == '\0') {
            return TRUE;
        }
    }

    if (*filename == '\0') {
        return TRUE;
    }

    return FALSE;
}

s32 __CARDAccess(CARDControl* card, CARDDir* ent)
{
    if (ent->gameName[0] == 0xFF) {
        return CARD_RESULT_NOFILE;
    }

    if (card->diskID == &__CARDDiskNone ||
        (memcmp(ent->gameName, card->diskID->gameName, 4) == 0 &&
         memcmp(ent->company, card->diskID->company, 2) == 0))
    {
        return CARD_RESULT_READY;
    }

    return CARD_RESULT_NOPERM;
}

s32 __CARDIsPublic(CARDDir* ent)
{
    if (ent->gameName[0] == 0xFF) {
        return CARD_RESULT_NOFILE;
    }

    if ((ent->permission & CARD_ATTR_PUBLIC) != 0) {
        return CARD_RESULT_READY;
    }

    return CARD_RESULT_NOPERM;
}

s32 __CARDGetFileNo(CARDControl* card, const char* filename, s32* pfileno)
{
    CARDDir* dir;
    CARDDir* ent;
    s32 fileno;
    s32 result;

    if (!card->attached) {
        return CARD_RESULT_NOCARD;
    }

    dir = __CARDGetDirBlock(card);
    for (fileno = 0; fileno < CARD_MAX_FILE; fileno++) {
        ent = &dir[fileno];
        result = __CARDAccess(card, ent);
        if (result < 0) {
            continue;
        }
        if (__CARDCompareFileName(ent, filename)) {
            *pfileno = fileno;
            return CARD_RESULT_READY;
        }
    }

    return CARD_RESULT_NOFILE;
}

s32 CARDFastOpen(s32 chan, s32 fileno, CARDFileInfo* fileinfo)
{
    CARDControl* card;
    CARDDir* dir;
    s32 result;
    CARDDir* ent;

    if (fileno < 0 || fileno >= 127) {
        return -0x80;
    }
    fileinfo->chan = -1;
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileno];
    result = __CARDAccess(card, ent);
    if (result == CARD_RESULT_NOPERM) {
        result = __CARDIsPublic(ent);
    }

    if (result >= 0) {
        if (!CARDIsValidBlockNo(card, ent->startBlock)) {
            result = CARD_RESULT_BROKEN;
        } else {
            fileinfo->chan = chan;
            fileinfo->fileNo = fileno;
            fileinfo->offset = 0;
            fileinfo->iBlock = ent->startBlock;
        }
    }
    return __CARDPutControlBlock(card, result);
}

s32 CARDOpen(s32 chan, const char* filename, CARDFileInfo* fileinfo)
{
    CARDControl* card;
    CARDDir* dir;
    CARDDir* ent;
    s32 result;
    s32 fileno;

    fileinfo->chan = -1;
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }
    result = __CARDGetFileNo(card, filename, &fileno);
    if (result >= 0) {
        dir = __CARDGetDirBlock(card);
        ent = &dir[fileno];
        if (!CARDIsValidBlockNo(card, ent->startBlock)) {
            result = CARD_RESULT_BROKEN;
        } else {
            fileinfo->chan = chan;
            fileinfo->fileNo = fileno;
            fileinfo->offset = 0;
            fileinfo->iBlock = ent->startBlock;
        }
    }
    return __CARDPutControlBlock(card, result);
}

s32 CARDClose(CARDFileInfo* fileinfo)
{
    CARDControl* card;
    s32 result;

    result = __CARDGetControlBlock(fileinfo->chan, &card);
    if (result < 0) {
        return result;
    }

    fileinfo->chan = -1;
    return __CARDPutControlBlock(card, CARD_RESULT_READY);
}

BOOL __CARDIsOpened(CARDControl* card, s32 fileno)
{
    return FALSE;
}
