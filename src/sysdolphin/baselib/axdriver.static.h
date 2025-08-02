#include "axdriver.h" // IWYU pragma: export

#include <dolphin/axfx.h>

static HSD_SM AXDriver_804C45A0[0x60];
static HSD_SM* AXDriver_804C5920[0x40];

static u8 AXDriver_804C5A20[0x10]; // unknown type
static u8 AXDriver_804C5A30[0x10]; // unknown type
/* C5A40 */ static struct AXFX_REVERBHI
    AXDriver_804C5A40[2]; // 804C45A0 + 0x14A0
/* C5E00 */ static struct AXFX_REVERBSTD
    AXDriver_804C5E00[2]; // 804C45A0 + 0x1860
/* C60A8 */ static struct AXFX_CHORUS
    AXDriver_804C60A8[2];                                  // 804C45A0 + 0x1B08
/* C61E0 */ static struct AXFX_DELAY AXDriver_804C61E0[2]; // 804C45A0 + 0x1C40

/* 4D6038 */ static int AXDriver_804D6038 = -1;
/* 4D603C */ static u32 AXDriver_804D603C = 2;

/* 4D778C */ static int AXDriver_804D778C;
/* 4D7790 */ static HSD_SM* AXDriver_804D7790;
/* 4D7794 */ static HSD_SM* AXDriver_804D7794;
/* 4D77C8 */ static int AXDriver_804D77C8;
/* 4D77CC */ static u32 AXDriver_804D77CC;
/* 4D77D0 */ static int AXDriver_804D77D0;
/* 4D77D4 */ static u8* AXDriver_804D77D4;
/* 4D77D8 */ static u32 axfxallocsize;
/* 4D77DC */ static u32 axfxmaxsize;
/* 4D77E0 */ static int AXDriver_804D77E0;
/* 4D77E4 */ static int AXDriver_804D77E4;
/* 4D77E8 */ static int AXDriver_804D77E8;
/* 4D77EC */ static int AXDriver_804D77EC;

// External arrays referenced by AXDriver_8038CFF4
extern int AXDriver_804D7788;
extern int AXDriver_804D77B0;
extern u32* AXDriver_804D77B4;
extern int AXDriver_804D77B8;
extern u32** AXDriver_804D77BC;
