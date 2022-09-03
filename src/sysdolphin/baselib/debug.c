#include "global.h"

#include <dolphin/os/os.h>
#include <dolphin/os/OSContext.h>

struct UnkStruct80400430 {
    char filler0[0x52];
    char unk52;
    char unk53[0x84 - 0x53];
    int (*unk84)(s32, s32, s32*, s32);
};

extern void (*lbl_804D7710)(s32, s32);
extern void (*lbl_804D7714)(OSContext*, ...);
extern int (*lbl_804D7718)(s32, s32, s32*, s32);

extern struct UnkStruct80400430 lbl_80400430;

OSContext lbl_804C2608;

/*
 * Unused symbol probably used by the myStrippedFunction below, but since it got stripped
 * there's no telling what it was for.
 * 
 * Regarding the pragma, normally this works, but in this case the Metrowerks toolchain is
 * out for fuckin' blood or something. See the FORCEACTIVE section we had to add in the
 * LCF just to get the compiler to stop removing this.
 */
#pragma push
#pragma force_active on
extern char lbl_804C28D0[0x10];

char lbl_804C28D0[0x10]; // unk space. what is this?
#pragma pop

static char lbl_804D6010[1] = "";

// required stripped asm function to get the peephole off behavior in early
// CW versions to occur.
static void asm myStrippedFunction() {
    nop
    nop
    nop
    nop
}

int lbl_8038815C(s32 arg0, s32 arg1, s32* arg2, s32 arg3) {
    if (lbl_804D7710 != NULL) {
        lbl_804D7710(arg1, *arg2);
    }
    lbl_804D7718(arg0, arg1, arg2, arg3);
    return 0;
}

void func_803881E4(void) {
    if (lbl_804D7718 == NULL) {
        lbl_804D7718 = lbl_80400430.unk84;
    }
    lbl_80400430.unk84 = lbl_8038815C;
    lbl_80400430.unk52 = 0;
}

void __assert(char* str, u32 arg1, char* arg2) {
    OSReport("assertion \"%s\" failed", arg2);
    HSD_Panic(str, arg1, lbl_804D6010);
}

void HSD_Panic(char* arg0, u32 line, char* arg2) {
    if (lbl_804D7714 != NULL) {
        OSSaveContext(&lbl_804C2608);
        OSReport("%s in %s on line %d.\n", arg2, arg0, line);
        lbl_804D7714(&lbl_804C2608);
    }
    OSPanic(arg0, line, arg2);
}
