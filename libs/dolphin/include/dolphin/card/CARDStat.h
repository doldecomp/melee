#ifndef _DOLPHIN_CARDSTAT_H_
#define _DOLPHIN_CARDSTAT_H_

typedef struct CARDStat
{
    /*0x00*/ char fileName[CARD_FILENAME_MAX];
    /*0x20*/ u32 length;
    /*0x24*/ u32 time;
    /*0x28*/ u8 gameName[4];
    /*0x2C*/ u8 company[2];
    /*0x2E*/ u8 bannerFormat;
    /*0x30*/ u32 iconAddr;
    /*0x34*/ u16 iconFormat;
    /*0x36*/ u16 iconSpeed;
    /*0x38*/ u32 commentAddr;
    /*0x3C*/ u32 offsetBanner;
    /*0x40*/ u32 offsetBannerTlut;
    /*0x44*/ u32 offsetIcon[CARD_ICON_MAX];
    /*0x64*/ u32 offsetIconTlut;
    /*0x68*/ u32 offsetData;
} CARDStat;

s32 CARDGetStatus(s32 chan, s32 fileNo, CARDStat *stat);
s32 CARDSetStatusAsync(s32 chan, s32 fileNo, CARDStat *stat, CARDCallback callback);
long CARDSetStatus(long chan, long fileNo, struct CARDStat * stat);

#endif // _DOLPHIN_CARDSTAT_H_
