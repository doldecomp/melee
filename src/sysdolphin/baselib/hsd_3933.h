#ifndef HSD_3933_H
#define HSD_3933_H

#include <Runtime/platform.h>

/// One 0x20-byte host-IO packet, as exchanged with the MCC server.
typedef struct _MCCPacket {
    /* 0x0 */ s32 x0;
    /* 0x4 */ u8 x4_b7 : 1;
    /* 0x4 */ u8 _x4_pad : 7;
    /* 0x5 */ u8 command;
    /* 0x6 */ u16 x6;
    /* 0x8 */ u8 payload[0x18];
} MCCPacket;

ASSERT_SIZE(MCCPacket, 0x20);

/* 3932D0 */ void fn_803932D0(s32, u32, s32);
/* 393328 */ s32 hsd_80393328(void);
/* 393440 */ void hsd_80393440(MCCPacket*, MCCPacket*);
/* 393840 */ void hsd_80393840(MCCPacket*, MCCPacket*);
/* 393844 */ void hsd_80393844(void);

/// Checks whether USB server is set up.
/* 393A04 */ bool hsd_80393A04(void);

/* 393A54 */ void hsd_80393A54(int);
/* 393A5C */ int hsd_80393A5C(char*, int, int);

#endif
