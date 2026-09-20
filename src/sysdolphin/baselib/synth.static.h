#ifndef SYSDOLPHIN_BASELIB_SYNTH_STATIC_H
#define SYSDOLPHIN_BASELIB_SYNTH_STATIC_H

#include <dolphin/ax.h>
#include <dolphin/os.h>
#include <sysdolphin/baselib/synth.h> // IWYU pragma: export

OSHeapHandle HSD_Synth_804D6018 = -1; // audio heap

/**
 * One voice of a sound, as a loaded SFX bank stores it: the AX playback
 * parameters for a single AX voice.
 */
typedef struct SfxVoice {
    /* 0x00 */ AXPBADDR addr;
    /* 0x10 */ AXPBADPCM adpcm;
    /* 0x38 */ AXPBADPCMLOOP adpcm_loop;
    /* 0x3E */ u8 pad3E[2];
} SfxVoice;

ASSERT_SIZE(SfxVoice, 0x40);

/// ::sizeof(SfxVoice) as a shift, for the one place that walks the voices of
/// a group as a byte offset.
enum {
    SFX_VOICE_SHIFT = 6
};

ASSERT_SIZE(SfxVoice, 1 << SFX_VOICE_SHIFT);

/**
 * One sound of a loaded SFX bank: its voices, preceded by the chain pointer
 * that links it into ::hsd_SynthSFXDataHash under its sound id. The voices
 * follow the header in memory, exactly as the bank file stores them.
 */
typedef struct SfxGroup {
    /* 0x00 */ struct SfxGroup* next;
    /* 0x04 */ s32 sfx_id;
    /* 0x08 */ s32 voice_count;
    /* 0x0C */ s32 sample_rate;
    /* 0x10 */ SfxVoice voices[];
} SfxGroup;

ASSERT_SIZE(SfxGroup, 0x10);

typedef union SfxBankBlock SfxBankBlock;

/**
 * One loaded SFX bank: where its samples live in ARAM and which sound ids it
 * provides. The bank's ::SfxGroup list follows the header in memory.
 */
typedef struct SfxBank {
    /* 0x00 */ SfxBankBlock* next;
    /* 0x04 */ s32 entrynum;
    /* 0x08 */ s32 first_sfx_id;
    /* 0x0C */ s32 group_count;
    /* 0x10 */ s32 aram_addr;
    /* 0x14 */ s32 aram_size;
} SfxBank;

ASSERT_SIZE(SfxBank, 0x18);

/**
 * One record of a loaded SFX bank's memory block: the ::SfxBank header at the
 * start of the block, or one of the packed ::SfxGroup records that follow it.
 */
union SfxBankBlock {
    SfxBank bank;
    SfxGroup group;
};

/// The loader steps past a bank header by one block, so the two must agree.
ASSERT_SIZE(SfxBankBlock, sizeof(SfxBank));

/// One voice's playback parameters, as a PStream header stores them.
typedef struct PStreamVoice {
    /* 0x00 */ AXPBADDR addr;
    /* 0x10 */ AXPBADPCM adpcm;
} PStreamVoice;

ASSERT_SIZE(PStreamVoice, 0x38);

/// The header at the start of a PStream, read before the first block.
typedef struct PStreamHeader {
    /* 0x00 */ u32 x0;
    /* 0x04 */ u32 x4;
    /* 0x08 */ u32 sample_rate;
    /* 0x0C */ u32 voice_count;
    /* 0x10 */ PStreamVoice voices[2];
} PStreamHeader;

ASSERT_SIZE(PStreamHeader, 0x80);

/// Where a voice's AX blocks sit in the header, counted in whole words.
enum {
    PSTREAM_VOICE_WORDS = sizeof(PStreamVoice) / sizeof(u32),
    PSTREAM_ADDR_WORD = offsetof(PStreamHeader, voices) / sizeof(u32),
    PSTREAM_ADPCM_WORD =
        (offsetof(PStreamHeader, voices) + offsetof(PStreamVoice, adpcm)) /
        sizeof(u32),
};

/// Named after the assertion text pooled in this TU's `.data`.
struct HSD_SynthSFXGroup {
    int arsize;
};

#define USERVOL_NUM 2

struct HSD_SynthSFXNode {
    /* 00 */ int x0;
    /* 04 */ int sfx_id;
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

static AXVPB* voicelist[0x100 / 4];
static SfxGroup* hsd_SynthSFXDataHash[0x80 / 4];
static struct {
    /* 00 */ int entrynum;
    /* 04 */ int bankID;
    /* 08 */ void (*x8)(int, int);
    /* 0C */ int xC;
} HSD_Synth_804C2A60[6];
/**
 * The start of the SFX bank file being loaded, read before the rest: the size
 * of its group records, the size of its sample data, its group count, its
 * first sound id, and the first four words of its first group record.
 */
static u32 hsd_SynthSFXLoadBuf[0x20 / 4];
static SfxBankBlock* HSD_Synth_804C2AE0[0x80 / 4];
static int hsd_SynthSFXBank[0x80 / 4];
static int hsd_SynthSFXBankHead[0x84 / 4];
static struct HSD_SynthSFXNode hsd_SynthSFXNodes[0x40];

static struct {
    float x1784;
    float x1788;
    int x178C;
} voicelist_1784[0xC0 / 0xC];

#define HSD_SYNTHSFXGROUP_MAX 0x100

static int voicelist_1844[HSD_SYNTHSFXGROUP_MAX];

static u8 lbl_804C4524[0x1C];

/**
 * One block of a playing PStream: where it sits in ARAM and the ADPCM loop
 * state each voice resumes from. The loop blocks are 8 bytes apart, which is
 * more than ::AXPBADPCMLOOP needs.
 */
typedef struct StreamBlockLoop {
    /* 0x0 */ AXPBADPCMLOOP adpcm_loop;
    /* 0x6 */ u16 pad6;
} StreamBlockLoop;

ASSERT_SIZE(StreamBlockLoop, 8);

/// One block of a playing PStream, as the stream's header records it.
typedef struct StreamBlockHeader {
    /* 0x00 */ s32 x0;
    /* 0x04 */ s32 x4;
    /* 0x08 */ s32 x8;
    /* 0x0C */ StreamBlockLoop loop[2];
    /* 0x1C */ char pad1C[4];
} StreamBlockHeader;

ASSERT_SIZE(StreamBlockHeader, 0x20);

/// Where a block's loop state sits in the header, counted in whole words.
enum {
    STREAM_BLOCK_LOOP_WORDS = sizeof(StreamBlockLoop) / sizeof(u32),
    STREAM_BLOCK_LOOP_WORD = offsetof(StreamBlockHeader, loop) / sizeof(u32),
};

static StreamBlockHeader pstHakoHeader[3];

/* 4D7720 */ static int HSD_Synth_804D7720;
/* 4D7724 */ static int hsd_SynthSFXBankNum;
/* 4D7728 */ static u32 hsd_SynthSFXBankAREnd;
/* 4D772C */ static volatile int HSD_Synth_804D772C;
/// The bank load cursor: the record of the block being filled.
/* 4D7730 */ static SfxBankBlock* HSD_Synth_804D7730;
/* 4D7734 */ static u32* HSD_Synth_804D7734;
/* 4D7738 */ static int HSD_Synth_804D7738;
/* 4D773C */ static volatile int sfxGroupDataReaddressCounter;
/* 4D7740 */ static void (*driverInactivatedCallback)(int);
/* 4D7744 */ static void (*driverMasterClockCallback)(int);
/* 4D7748 */ static void (*driverPauseCallback)(s32);
/* 4D774C */ static struct HSD_SynthSFXNode* HSD_Synth_804D774C;
/* 4D7750 */ static int HSD_Synth_804D7750;
/* 4D7754 */ static u32 HSD_Synth_804D7754; // sound mode
/* 4D7758 */ static u32 HSD_Synth_804D7758;
/* 4D7754 */ static int HSD_Synth_804D775C;
/* 4D7760 */ static int HSD_Synth_804D7760;
/* 4D7764 */ static s32 HSD_Synth_804D7764;
/* 4D7768 */ static u32 HSD_Synth_804D7768;
/* 4D776C */ static u32 HSD_Synth_804D776C;
/* 4D7770 */ static u32 HSD_Synth_804D7770;
/* 4D7774 */ static u32 HSD_Synth_804D7774;
/* 4D7778 */ static volatile u8 HSD_Synth_804D7778;
/* 4D777C */ static s32 HSD_Synth_804D777C;
/* 4D7780 */ static u32 HSD_Synth_804D7780;
/* 4D7784 */ static u32 HSD_Synth_804D7784;

#endif
