#include <string.h>
#include <dolphin/card.h>
#include <dolphin/card/CARDBios.h>
#include <dolphin/card/CARDDir.h>
#include <dolphin/card/CARDOpen.h>
#include <dolphin/card/CARDRename.h>
#include <dolphin/dvd/dvd.h>
#include <dolphin/os/OSTime.h>

s32 CARDRenameAsync(s32 chan, const char* old, const char* new,
                    CARDCallback callback)
{
    CARDControl* card;
    CARDDir* dir;
    CARDDir* ent;
    s32 result;
    int fileNo;
    int newNo;
    int oldNo;

    if (*old == 0xff || *new == 0xff || *old == 0x00 || *new == 0x00) {
        return CARD_RESULT_FATAL_ERROR;
    }
    if (CARD_FILENAME_MAX < (u32) strlen(old) ||
        CARD_FILENAME_MAX < (u32) strlen(new))
    {
        return CARD_RESULT_NAMETOOLONG;
    }
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }

    newNo = oldNo = -1;
    dir = __CARDGetDirBlock(card);
    for (fileNo = 0; fileNo < CARD_MAX_FILE; fileNo++) {
        ent = &dir[fileNo];
        if (ent->gameName[0] == 0xff) {
            continue;
        }

        if (memcmp(ent->gameName, card->diskID->gameName,
                   sizeof(ent->gameName)) != 0 ||
            memcmp(ent->company, card->diskID->company,
                   sizeof(ent->company)) != 0)
        {
            continue;
        }

        if (__CARDCompareFileName(ent, old)) {
            oldNo = fileNo;
        }
        if (__CARDCompareFileName(ent, new)) {
            newNo = fileNo;
        }
    }

    if (oldNo == -1) {
        return __CARDPutControlBlock(card, CARD_RESULT_NOFILE);
    }
    if (newNo != -1) {
        return __CARDPutControlBlock(card, CARD_RESULT_EXIST);
    }

    ent = &dir[oldNo];
    result = __CARDAccess(card, ent);
    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }

    strncpy((char*) ent->fileName, new, CARD_FILENAME_MAX);

    ent->time = OSTicksToSeconds(OSGetTime());
    result = __CARDUpdateDir(chan, callback);
    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }
    return result;
}
