#include "debug.h"

#include "synth.h"

#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>

struct UnkStruct80400430 {
    char filler0[0x52];
    char unk52;
    char unk53[0x84 - 0x53];
    int (*unk84)(s32, s32, s32*, s32);
};

extern struct UnkStruct80400430 __files;

struct DebugContext {
    OSContext context;
    u8 unk[0x10];
} HSD_Debug_804C2608;

#ifdef MUST_MATCH
#pragma peephole off
#endif

int HSD_Debug_8038815C(s32 arg0, s32 arg1, s32* arg2, s32 arg3)
{
    if (HSD_Synth_804D7710 != NULL) {
        HSD_Synth_804D7710(arg1, *arg2);
    }
    HSD_Synth_804D7718(arg0, arg1, arg2, arg3);
    return 0;
}

void HSD_Debug_803881E4(void)
{
    if (HSD_Synth_804D7718 == NULL) {
        HSD_Synth_804D7718 = __files.unk84;
    }
    __files.unk84 = HSD_Debug_8038815C;
    __files.unk52 = 0;
}

void __assert(char* str, u32 arg1, char* arg2)
{
    OSReport("assertion \"%s\" failed", arg2);
    HSD_Panic(str, arg1, "");
}

void HSD_Panic(char* arg0, u32 line, char* arg2)
{
    if (HSD_Synth_804D7714 != NULL) {
        OSSaveContext(&HSD_Debug_804C2608.context);
        OSReport("%s in %s on line %d.\n", arg2, arg0, line);
        HSD_Synth_804D7714(&HSD_Debug_804C2608.context);
    }
    OSPanic(arg0, line, arg2);
}
