#include <dolphin/types.h>
#include <dolphin/dvd/dvd.h>
#include <dolphin/os/os.h>
#include <dolphin/os/OSArena.h>

static u32 status;
static struct bb2struct *bb2;
static DVDDiskID *idTmp;
static u8 bb2Buf[64];
static u8 block[48];

struct DiskInfo
{
    DVDDiskID diskId;
    u8 filler20[0x38-0x20];
    void *FSTLocationInRam;
    u32 FSTMaxLength;
};

static void cb(s32 param_1, void* param_2) // param_2 is probably a struct
{
    if (param_1 > 0)
    {
        switch (status)
        {
        case 0:
            status = 1;
            DVDReadAbsAsyncForBS(param_2, bb2, 0x20, 0x420, cb);
            break;
        case 1:
            status = 2;
            DVDReadAbsAsyncForBS(param_2, bb2->FSTLocationInRam, OSRoundUp32B(bb2->_08), bb2->_04, cb);
            break;
        }
    }
    else if (param_1 == -1)
        ;  // nothing
    else if (param_1 == -4)
    {
        status = 0;
        DVDReset();
        DVDReadDiskID(param_2, idTmp, cb);
    }
}

void __fstLoad(void)
{
    u8 auStack64[64];
    void *arenaHi;
    struct DiskInfo *info;

    arenaHi = OSGetArenaHi();  // not used
    idTmp   = (void *)OSRoundUp32B(auStack64);
    bb2     = (void *)OSRoundUp32B(bb2Buf);
    DVDReset();
    DVDReadDiskID(&block, idTmp, cb);
    while (DVDGetDriveStatus() != 0)
        ;

    info                   = (void*)0x80000000;
    info->FSTLocationInRam = bb2->FSTLocationInRam;
    info->FSTMaxLength     = bb2->FSTMaxLength;
    memcpy(&info->diskId, idTmp, sizeof(info->diskId));

    OSReport("\n");
    OSReport("  Game Name ... %c%c%c%c\n",
        info->diskId.gameName[0],
        info->diskId.gameName[1],
        info->diskId.gameName[2],
        info->diskId.gameName[3]);
    OSReport("  Company ..... %c%c\n",
        info->diskId.company[0],
        info->diskId.company[1]);
    OSReport("  Disk # ...... %d\n", info->diskId.diskNumber);
    OSReport("  Game ver .... %d\n", info->diskId.gameVersion);
    OSReport("  Streaming ... %s\n", !info->diskId.streaming ? "OFF" : "ON");
    OSReport("\n");

    OSSetArenaHi(bb2->FSTLocationInRam);
}
