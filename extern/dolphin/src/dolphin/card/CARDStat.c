#include <dolphin.h>
#include <dolphin/os.h>
#include <dolphin/card.h>

#include "__card.h"

// functions
static void UpdateIconOffsets(CARDDir *ent, CARDStat *stat);

static void UpdateIconOffsets(CARDDir *ent, CARDStat *stat) {
    u32 offset;
    BOOL iconTlut;
    int i;

    offset = ent->iconAddr;
    if (offset == 0xffffffff)
    {
        stat->bannerFormat = 0;
        stat->iconFormat = 0;
        stat->iconSpeed = 0;
    }

    iconTlut = FALSE;
    switch (CARDGetBannerFormat(ent))
    {
    case CARD_STAT_BANNER_C8:
        stat->offsetBanner = offset;
        offset += CARD_BANNER_WIDTH * CARD_BANNER_HEIGHT;
        stat->offsetBannerTlut = offset;
        offset += 2 * 256;
        break;
    case CARD_STAT_BANNER_RGB5A3:
        stat->offsetBanner = offset;
        offset += 2 * CARD_BANNER_WIDTH * CARD_BANNER_HEIGHT;
        stat->offsetBannerTlut = 0xffffffff;
        break;
    default:
        stat->offsetBanner = 0xffffffff;
        stat->offsetBannerTlut = 0xffffffff;
        break;
    }
    for (i = 0; i < CARD_ICON_MAX; ++i)
    {
        switch (CARDGetIconFormat(ent, i))
        {
        case CARD_STAT_ICON_C8:
            stat->offsetIcon[i] = offset;
            offset += CARD_ICON_WIDTH * CARD_ICON_HEIGHT;
            iconTlut = TRUE;
            break;
        case CARD_STAT_ICON_RGB5A3:
            stat->offsetIcon[i] = offset;
            offset += 2 * CARD_ICON_WIDTH * CARD_ICON_HEIGHT;
            break;
        default:
            stat->offsetIcon[i] = 0xffffffff;
            break;
        }
    }
    if (iconTlut)
    {
        stat->offsetIconTlut = offset;
        offset += 2 * 256;
    }
    else
    {
        stat->offsetIconTlut = 0xffffffff;
    }
    stat->offsetData = offset;
}

s32 CARDGetStatus(s32 chan, s32 fileNo, CARDStat *stat) {
    CARDControl *card;
    CARDDir *dir;
    CARDDir *ent;
    s32 result;

    ASSERTLINE(0x97, 0 <= chan && chan < 2);
    ASSERTLINE(0x98, 0 <= fileNo && fileNo < CARD_MAX_FILE);

    if (fileNo < 0 || CARD_MAX_FILE <= fileNo)
        return CARD_RESULT_FATAL_ERROR;

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
        memcpy(stat->gameName, ent->gameName, sizeof(stat->gameName));
        memcpy(stat->company, ent->company, sizeof(stat->company));
        stat->length = (u32)ent->length * card->sectorSize;
        memcpy(stat->fileName, ent->fileName, CARD_FILENAME_MAX);
        stat->time = ent->time;

        stat->bannerFormat = ent->bannerFormat;
        stat->iconAddr = ent->iconAddr;
        stat->iconFormat = ent->iconFormat;
        stat->iconSpeed = ent->iconSpeed;
        stat->commentAddr = ent->commentAddr;

        UpdateIconOffsets(ent, stat);
    }
    return __CARDPutControlBlock(card, result);
}

s32 CARDSetStatusAsync(s32 chan, s32 fileNo, CARDStat *stat, CARDCallback callback) {
    CARDControl *card;
    CARDDir *dir;
    CARDDir *ent;
    s32 result;

    ASSERTLINE(0xD5, 0 <= fileNo && fileNo < CARD_MAX_FILE);
    ASSERTLINE(0xD6, 0 <= chan && chan < 2);

    if (fileNo < 0 || CARD_MAX_FILE <= fileNo)
        return CARD_RESULT_FATAL_ERROR;

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0)
        return result;

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileNo];
    result = __CARDAccess(ent);
    if (result < 0)
        return __CARDPutControlBlock(card, result);

    ent->bannerFormat = stat->bannerFormat;
    ent->iconAddr = stat->iconAddr;
    ent->iconFormat = stat->iconFormat;
    ent->iconSpeed = stat->iconSpeed;
    ent->commentAddr = stat->commentAddr;
    UpdateIconOffsets(ent, stat);

    ent->time = (u32)OSTicksToSeconds(OSGetTime());
    result = __CARDUpdateDir(chan, callback);
    if (result < 0)
        __CARDPutControlBlock(card, result);
    return result;
}

long CARDSetStatus(long chan, long fileNo, struct CARDStat * stat) {
    long result = CARDSetStatusAsync(chan, fileNo, stat, __CARDSyncCallback);

    if (result < 0) {
        return result;
    }
    return __CARDSync(chan);
}
