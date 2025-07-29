#include "synth.h" // IWYU pragma: export

static int HSD_Synth_804D6018 = -1; // audio heap
static int HSD_Synth_804D6028[2] = { 0 };
static AXVPB* HSD_Synth_804DE7F0 = NULL; /* const */

#define USERVOL_NUM 2

struct HSD_SynthSFXNode {
    /* 00 */ int x0;
    /* 04 */ struct HSD_SynthSFXNode* next;
    /* 08 */ u8 pad8;
    /* 09 */ u8 flags;
    /* 0A */ u8 voice_count;
    /* 0B */ u8 xB;
    /* 0C */ AXVPB* voice[2];
    /* 14 */ float x14;
    /* 18 */ float x18;
    /* 1C */ float x1C;
    /* 20 */ struct HSD_SynthSFXNode* x20;
    /* 24 */ u8 pad24[2];
    /* 26 */ u8 volume_update_pending;
    /* 27 */ u8 x27;
    /* 28 */ u8 pad28[4];
    /* 2C */ struct {
        /* 2C */ float x0;
        /* 30 */ int x4;
        /* 34 */ int x8;
    } x2C[USERVOL_NUM];
    /* 44 */ float x44;
    /* 48 */ float x48;
    /* 4C */ float x4C;
};

static AXVPB* HSD_Synth_804C28E0[0x100 / 4];
static u8 HSD_Synth_804C29E0[0x80];
static struct {
    /* 00 */ int entrynum;
    /* 04 */ int bankID;
    /* 08 */ int x8;
    /* 0C */ int xC;
} HSD_Synth_804C2A60[6];
static u8 HSD_Synth_804C2AC0[0x20];
static AXVPB* HSD_Synth_804C2AE0[0x80 / 4];
static int HSD_Synth_804C2B60[0x80 / 4];
static int hsd_SynthSFXBankHead[0x84 / 4];
static struct HSD_SynthSFXNode HSD_SynthSFXNodes[0x40];

static struct {
    float x1784;
    float x1788;
    int x178C;
} HSD_Synth_804C28E0_1784[0x24];

static AXPBMIX lbl_80407FB4 = { 0 };
static AXPBSRC HSD_Synth_80407FD8 = { 1, 0, 0, { 0, 0, 0, 0 } };

static int hsd_SynthSFXBankNum;

/* 4D7720 */ static int HSD_Synth_804D7720;
/* 4D7728 */ static u32 hsd_SynthSFXBankAREnd;
/* 4D772C */ static volatile int HSD_Synth_804D772C;
/* 4D7738 */ static int HSD_Synth_804D7738;
/* 4D773C */ static volatile int sfxGroupDataReaddressCounter;
/* 4D7740 */ static void (*driverInactivatedCallback)(int);
/* 4D7744 */ static void (*driverMasterClockCallback)(int);
/* 4D7748 */ static UNK_T driverPauseCallback;
/* 4D774C */ static struct HSD_SynthSFXNode* HSD_Synth_804D774C;
/* 4D7754 */ static u32 HSD_Synth_804D7754; // sound mode
/* 4D7758 */ static u32 HSD_Synth_804D7758;
/* 4D7754 */ static int HSD_Synth_804D775C;
/* 4D7760 */ static int HSD_Synth_804D7760;
/* 4D7768 */ static int HSD_Synth_804D7768;
/* 4D776C */ static int HSD_Synth_804D776C;
/* 4D7778 */ static s8 HSD_Synth_804D7778;
