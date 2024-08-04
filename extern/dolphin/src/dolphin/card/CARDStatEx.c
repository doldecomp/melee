#include <dolphin.h>
#include <dolphin/card.h>

#include "__card.h"

long __CARDGetStatusEx(long chan, long fileNo, struct CARDDir * dirent) {
    ASSERTLINE(0x45, 0 <= chan && chan < 2);
    ASSERTLINE(0x46, 0 <= fileNo && fileNo < CARD_MAX_FILE);

    if ((fileNo < 0) || (fileNo >= CARD_MAX_FILE)) {
        return CARD_RESULT_FATAL_ERROR;
    }

    {
        struct CARDControl * card;
        struct CARDDir * dir;
        struct CARDDir * ent;
        long result = __CARDGetControlBlock(chan, &card);

        if (result < 0) {
            return result;
        }
    
        dir = __CARDGetDirBlock(card);
        ent = &dir[fileNo];
        result = __CARDAccess(ent);
        if (result == CARD_RESULT_NOPERM) {
            result = __CARDIsPublic(ent);
        }
        if (result >= 0) {
            memcpy(dirent, ent, 0x40);
        }
        return __CARDPutControlBlock(card, result);
    }
}

long __CARDSetStatusExAsync(long chan, long fileNo, struct CARDDir * dirent, void (* callback)(long, long)) {
    struct CARDControl * card;
    struct CARDDir * dir;
    struct CARDDir * ent;
    long result;
    unsigned char * p;
    long i;

    ASSERTLINE(0x81, 0 <= fileNo && fileNo < CARD_MAX_FILE);
    ASSERTLINE(0x82, 0 <= chan && chan < 2);
    ASSERTLINE(0x83, *dirent->fileName != 0xff && *dirent->fileName != 0x00);

    if ((fileNo < 0) || (fileNo >= CARD_MAX_FILE) || ((u8) dirent->fileName[0] == 0xFF) || ((u8) dirent->fileName[0] == 0)) {
        return CARD_RESULT_FATAL_ERROR;
    }

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }
    dir = __CARDGetDirBlock(card);
    ent = &dir[fileNo];
    result = __CARDAccess(ent);
    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }
    for(p = dirent->fileName; p < (u8*)&dirent->time; p++) {
        if (*p != 0) {
            continue;
        }
        while ((++p) < (u8*)&dirent->time) {
            *p = 0;
        }
        break;
    }
    if ((memcmp(&ent->fileName, &dirent->fileName, 32) != 0) || (memcmp(ent->gameName, dirent->gameName, 4) != 0) || (memcmp(ent->company, dirent->company, 2) != 0)) {
        for(i = 0; i < CARD_MAX_FILE; i++) {
            if (i != fileNo) {
                struct CARDDir * ent = &dir[i]; // sure, just redeclare ent again...
                if (((u8) ent->gameName[0] != 0xFF) 
                    && (memcmp(&ent->gameName, &dirent->gameName, 4) == 0) 
                    && (memcmp(&ent->company, &dirent->company, 2) == 0) 
                    && (memcmp(&ent->fileName, &dirent->fileName, 0x20) == 0)) {
                        return __CARDPutControlBlock(card, -7);
                }
            }
        }
        memcpy(&ent->fileName, &dirent->fileName, 0x20);
        memcpy(&ent->gameName, &dirent->gameName, 4);
        memcpy(&ent->company, &dirent->company, 2);
    }
    ent->time = dirent->time;
    ent->bannerFormat = dirent->bannerFormat;
    ent->iconAddr = dirent->iconAddr;
    ent->iconFormat = dirent->iconFormat;
    ent->iconSpeed = dirent->iconSpeed;
    ent->commentAddr = dirent->commentAddr;
    ent->permission = dirent->permission;
    ent->copyTimes = dirent->copyTimes;
    result = __CARDUpdateDir(chan, callback);
    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }
    return result;
}

long __CARDSetStatusEx(long chan, long fileNo, struct CARDDir * dirent) {
    long result = __CARDSetStatusExAsync(chan, fileNo, dirent, &__CARDSyncCallback);

    if (result < 0) {
        return result;
    }
    return __CARDSync(chan);
}
