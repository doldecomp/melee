#include "synth.h" // IWYU pragma: export

static int HSD_Synth_804D6018 = -1; // audio heap
static int HSD_Synth_804D6028[2] = { 0 };

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
    /* 18 */ float x18[2];
    /* 20 */ struct HSD_SynthSFXNode* x20;
    /* 24 */ u16 x24;
    /* 26 */ u8 volume_update_pending;
    /* 27 */ u8 x27;
    /* 28 */ float unk28;
    /* 2C */ struct {
        /* 2C */ float volume;
        /* 30 */ int x4;
        union {
            /* 34 */ u8 x8;
            /* 34 */ float x8_float;
        };
    } user_vol[USERVOL_NUM];
    /* 44 */ float x44;
    /* 48 */ float x48;
    /* 4C */ float x4C;
};

static AXVPB* HSD_Synth_804C28E0[0x100 / 4];
static void* HSD_Synth_804C29E0[0x80 / 4];
static struct {
    /* 00 */ int entrynum;
    /* 04 */ int bankID;
    /* 08 */ int x8;
    /* 0C */ int xC;
} HSD_Synth_804C2A60[6];
static u32 hsd_SynthSFXLoadBuf[0x20 / 4];
static AXVPB* HSD_Synth_804C2AE0[0x80 / 4];
static int hsd_SynthSFXBank[0x80 / 4];
static int hsd_SynthSFXBankHead[0x84 / 4];
static struct HSD_SynthSFXNode hsd_SynthSFXNodes[0x40];

static float HSD_Synth_804D6030 = 1.0f;

static struct {
    float x1784;
    float x1788;
    int x178C;
} HSD_Synth_804C28E0_1784[0xC0 / 0xC];

#define HSD_SYNTHSFXGROUP_MAX 0x100

static int HSD_Synth_804C28E0_1844[HSD_SYNTHSFXGROUP_MAX];

static struct {
    /* 00 */ s32 x0;
    /* 04 */ char pad[0x1C];
} lbl_804C4540[3];

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
/* 4D7750 */ static int HSD_Synth_804D7750;
/* 4D7754 */ static u32 HSD_Synth_804D7754; // sound mode
/* 4D7758 */ static u32 HSD_Synth_804D7758;
/* 4D7754 */ static int HSD_Synth_804D775C;
/* 4D7760 */ static int HSD_Synth_804D7760;
/* 4D7768 */ static int HSD_Synth_804D7768;
/* 4D776C */ static int HSD_Synth_804D776C;
/* 4D7778 */ static volatile u8 HSD_Synth_804D7778;
/* 4D777C */ static s32 HSD_Synth_804D777C;
/* 4D7780 */ static u32 HSD_Synth_804D7780;
/* 4D7784 */ static u32 HSD_Synth_804D7784;
