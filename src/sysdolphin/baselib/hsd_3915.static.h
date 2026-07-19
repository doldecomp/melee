#include <sysdolphin/baselib/psstructs.h>

// types

// .bss

typedef struct {
    /* 0x00 */ void* next;
    /* 0x04 */ s32 type;
    /* 0x08 */ union {
        u8 bytes[0x80];
        char text[0x80];
        struct {
            s32 count;
            u32 color;
        } bars[16];
        struct {
            f32 pos;
            u32 color;
        } gradient[16];
    } content;
} PerfDispItem;

static PerfDispItem hsd_804CE3F8[6];

extern int psNumTexGroup[65];
static HSD_PSFormGroup** psFormGroupArray[65];

/* 4D0908 */ static void* hsd_804D0908[146];
/* 4D0B50 */ static HSD_PSTexGroup** psTexGroupArray[65];
/* 4D0C54 */ static HSD_PSCmdList** psCmdListArray[65];
/* 4D0D58 */ static int psNumCmdList[65];
/* 4D0E5C */ static u32* ptclref_804D0E5C[65];

/* 4D0F60 */ struct hsd_804D0F60_t hsd_804D0F60;
/* 4D0F90 */ struct hsd_804D0F60_t hsd_804D0F90;

/* 4D7850 */ static HSD_SList* hsd_804D7850;
/* 4D7858 */ static f32 hsd_804D7858;
/* 4D785C */ static f32 hsd_804D785C;
/* 4D7860 */ static f32 hsd_804D7860;
/* 4D7864 */ static f32 hsd_804D7864;
/* 4D7868 */ static f32 hsd_804D7868;
/* 4D786C */ static f32 hsd_804D786C;
/* 4D7870 */ static s32 hsd_804D7870;
/* 4D7874 */ static s32 hsd_804D7874;
/* 4D7878 */ static s32 hsd_804D7878;
/* 4D787C */ static f32 hsd_804D787C;
/* 4D7880 */ static f32 hsd_804D7880;
/* 4D7884 */ static f32 hsd_804D7884;
/* 4D7888 */ static s32 hsd_804D7888;
