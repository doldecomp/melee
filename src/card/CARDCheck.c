#include <dolphin.h>
#include <dolphin/card.h>

#include "os/__os.h"
#include "__card.h"

static s32 VerifyID(CARDControl *card);
static s32 VerifyDir(CARDControl *card, int *outCurrent);
static s32 VerifyFAT(CARDControl *card, int *outCurrent);

void __CARDCheckSum(void *ptr, int length, u16 *checksum, u16 *checksumInv) {
    u16 *p;
    int i;

    ASSERTLINE(0x44, length % sizeof(u16) == 0);

    length /= sizeof(u16);
    *checksum = *checksumInv = 0;
    for (i = 0, p = ptr; i < length; i++, p++)
    {
        *checksum += *p;
        *checksumInv += ~*p;
    }
    if (*checksum == 0xffff)
        *checksum = 0;
    if (*checksumInv == 0xffff)
        *checksumInv = 0;
}

static s32 VerifyID(CARDControl *card) {
    CARDID *id;
    u16 checksum;
    u16 checksumInv;
    OSSramEx *sramEx;
    OSTime rand;
    int i;

    id = card->workArea;

    if (id->deviceID != 0 || id->size != card->size)
        return CARD_RESULT_BROKEN;

    __CARDCheckSum(id, sizeof(CARDID) - sizeof(u32), &checksum, &checksumInv);
    if (id->checkSum != checksum || id->checkSumInv != checksumInv)
        return CARD_RESULT_BROKEN;

    if (id->encode != OSGetFontEncode())
        return CARD_RESULT_ENCODING;

    rand = *(OSTime *)&id->serial[12];
    sramEx = __OSLockSramEx();
    for (i = 0; i < 12; i++)
    {
        rand = (rand * 1103515245 + 12345) >> 16;
        if (id->serial[i] != (u8)(sramEx->flashID[card - __CARDBlock][i] + rand))
        {
            __OSUnlockSramEx(FALSE);
            return CARD_RESULT_BROKEN;
        }
        rand = ((rand * 1103515245 + 12345) >> 16) & 0x7FFF;
    }

    __OSUnlockSramEx(FALSE);

    return CARD_RESULT_READY;
}

static s32 VerifyDir(CARDControl *card, int *outCurrent) {
    CARDDir *dir[2];
    CARDDirCheck *check[2];
    u16 checkSum;
    u16 checkSumInv;
    int i;
    int errors;
    int current;

    current = errors = 0;
    for (i = 0; i < 2; i++)
    {
        dir[i] = (CARDDir *)((u8 *)card->workArea + (1 + i) * CARD_SYSTEM_BLOCK_SIZE);
        check[i] = CARDGetDirCheck(dir[i]);
        __CARDCheckSum(dir[i], CARD_SYSTEM_BLOCK_SIZE - sizeof(u32), &checkSum, &checkSumInv);
        if (check[i]->checkSum != checkSum || check[i]->checkSumInv != checkSumInv)
        {
            ++errors;
            current = i;
            card->currentDir = 0;
        }
    }

    if (0 == errors)
    {
        if (card->currentDir == 0)
        {
            if ((check[0]->checkCode - check[1]->checkCode) < 0)
                current = 0;
            else
                current = 1;
            card->currentDir = dir[current];
            memcpy(dir[current], dir[current ^ 1], CARD_SYSTEM_BLOCK_SIZE);
        }
        else
        {
            current = (card->currentDir == dir[0]) ? 0 : 1;
        }
    }
    if (outCurrent)
        *outCurrent = current;
    return errors;
}

static s32 VerifyFAT(CARDControl *card, int *outCurrent) {
    u16 *fat[2];
    u16 *fatp;
    u16 nBlock;
    u16 cFree;
    int i;
    u16 checkSum;
    u16 checkSumInv;
    int errors;
    int current;

    current = errors = 0;
    for (i = 0; i < 2; i++)
    {
        fatp = fat[i] = (u16 *)((u8 *)card->workArea + (3 + i) * CARD_SYSTEM_BLOCK_SIZE);

        __CARDCheckSum(&fatp[CARD_FAT_CHECKCODE], CARD_SYSTEM_BLOCK_SIZE - sizeof(u32), &checkSum, &checkSumInv);
        if (fatp[CARD_FAT_CHECKSUM] != checkSum || fatp[CARD_FAT_CHECKSUMINV] != checkSumInv)
        {
            ++errors;
            current = i;
            card->currentFat = 0;
            continue;
        }

        cFree = 0;
        for (nBlock = CARD_NUM_SYSTEM_BLOCK; nBlock < card->cBlock; nBlock++)
        {
            if (fatp[nBlock] == CARD_FAT_AVAIL)
                cFree++;
        }
        if (cFree != fatp[CARD_FAT_FREEBLOCKS])
        {
            ++errors;
            current = i;
            card->currentFat = 0;
            continue;
        }
    }

    if (0 == errors)
    {
        if (card->currentFat == 0)
        {
            if (((s16)fat[0][CARD_FAT_CHECKCODE] - (s16)fat[1][CARD_FAT_CHECKCODE]) < 0)
                current = 0;
            else
                current = 1;
            card->currentFat = fat[current];
            memcpy(fat[current], fat[current ^ 1], CARD_SYSTEM_BLOCK_SIZE);
        }
        else
            current = (card->currentFat == fat[0]) ? 0 : 1;
    }
    if (outCurrent)
        *outCurrent = current;
    return errors;
}

s32 __CARDVerify(CARDControl *card) {
    s32 result;
    int errors;

    result = VerifyID(card);
    if (result < 0)
        return result;

    errors = VerifyDir(card, NULL);
    errors += VerifyFAT(card, NULL);
    switch (errors)
    {
    case 0: 
        ASSERTLINE(0x11F, card->currentDir);
        ASSERTLINE(0x120, card->currentFat);
        return CARD_RESULT_READY;
    case 1: return CARD_RESULT_BROKEN;
    default: return CARD_RESULT_BROKEN;
    }
}

s32 CARDCheckAsync(s32 chan, CARDCallback callback) {
    CARDControl *card;
    CARDDir *dir[2];
    u16 *fat[2];
    u16 *map;
    s32 result;
    int errors;
    int currentFat;
    int currentDir;
    s32 fileNo;
    u16 iBlock;
    u16 cBlock;
    u16 cFree;
    BOOL updateFat = FALSE;
    BOOL updateDir = FALSE;
    BOOL updateOrphan = FALSE;

    ASSERTLINE(0x14A, 0 <= chan && chan < 2);
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0)
        return result;

    result = VerifyID(card);
    if (result < 0)
        return __CARDPutControlBlock(card, result);

    errors = VerifyDir(card, &currentDir);
    errors += VerifyFAT(card, &currentFat);
    if (1 < errors)
        return __CARDPutControlBlock(card, CARD_RESULT_BROKEN);

    dir[0] = (CARDDir *)((u8 *)card->workArea + (1 + 0) * CARD_SYSTEM_BLOCK_SIZE);
    dir[1] = (CARDDir *)((u8 *)card->workArea + (1 + 1) * CARD_SYSTEM_BLOCK_SIZE);
    fat[0] = (u16 *)((u8 *)card->workArea + (3 + 0) * CARD_SYSTEM_BLOCK_SIZE);
    fat[1] = (u16 *)((u8 *)card->workArea + (3 + 1) * CARD_SYSTEM_BLOCK_SIZE);

    ASSERTLINE(0x163, errors == 0 || errors == 1);
    
    switch (errors)
    {
    case 0: 
        ASSERTLINE(0x167, card->currentDir);
        ASSERTLINE(0x168, card->currentFat);
        break;
    case 1:
        if (!card->currentDir)
        {
            ASSERTLINE(0x16D, card->currentFat);
            card->currentDir = dir[currentDir];
            memcpy(dir[currentDir], dir[currentDir ^ 1], CARD_SYSTEM_BLOCK_SIZE);
            updateDir = TRUE;
        }
        else
        {
            ASSERTLINE(0x174, !card->currentFat);
            card->currentFat = fat[currentFat];
            memcpy(fat[currentFat], fat[currentFat ^ 1], CARD_SYSTEM_BLOCK_SIZE);
            updateFat = TRUE;
        }
        break;
    }

    map = fat[currentFat ^ 1];
    memset(map, 0, CARD_SYSTEM_BLOCK_SIZE);

    for (fileNo = 0; fileNo < CARD_MAX_FILE; fileNo++)
    {
        CARDDir *ent;

        ent = &card->currentDir[fileNo];
        if (ent->gameName[0] == 0xff)
            continue;

        for (iBlock = ent->startBlock, cBlock = 0; iBlock != 0xFFFF && cBlock < ent->length;
             iBlock = card->currentFat[iBlock], ++cBlock)
        {
            if (!CARDIsValidBlockNo(card, iBlock) || 1 < ++map[iBlock])
                return __CARDPutControlBlock(card, CARD_RESULT_BROKEN);
        }
        if (cBlock != ent->length || iBlock != 0xFFFF)
            return __CARDPutControlBlock(card, CARD_RESULT_BROKEN);
    }

    cFree = 0;
    for (iBlock = CARD_NUM_SYSTEM_BLOCK; iBlock < card->cBlock; iBlock++)
    {
        u16 nextBlock;

        nextBlock = card->currentFat[iBlock];
        if (map[iBlock] == 0)
        {
            if (nextBlock != CARD_FAT_AVAIL)
            {
                card->currentFat[iBlock] = CARD_FAT_AVAIL;
                updateOrphan = TRUE;
            }
            cFree++;
        }
        else if (!CARDIsValidBlockNo(card, nextBlock) && nextBlock != 0xFFFF)
            return __CARDPutControlBlock(card, CARD_RESULT_BROKEN);
    }
    if (cFree != card->currentFat[CARD_FAT_FREEBLOCKS])
    {
        card->currentFat[CARD_FAT_FREEBLOCKS] = cFree;
        updateOrphan = TRUE;
    }
    if (updateOrphan)
    {
        __CARDCheckSum(&card->currentFat[CARD_FAT_CHECKCODE], CARD_SYSTEM_BLOCK_SIZE - sizeof(u32),
                       &card->currentFat[CARD_FAT_CHECKSUM], &card->currentFat[CARD_FAT_CHECKSUMINV]);
    }

    memcpy(fat[currentFat ^ 1], fat[currentFat], CARD_SYSTEM_BLOCK_SIZE);

    if (updateDir)
    {
        return __CARDUpdateDir(chan, callback);
    }

    if (updateFat | updateOrphan)
    {
        return __CARDUpdateFatBlock(chan, card->currentFat, callback);
    }

    return __CARDPutControlBlock(card, CARD_RESULT_READY);
}

long CARDCheck(long chan) {
    long result = CARDCheckAsync(chan, __CARDSyncCallback);

    if (result < 0) {
        return result;
    }
    return __CARDSync(chan);
}
