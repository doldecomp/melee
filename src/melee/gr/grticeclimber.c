#include <melee/gr/grticeclimber.h>

#include <melee/gr/types.h>
#include <sysdolphin/baselib/gobjproc.h>

/* static */ StageCallbacks lbl_803E8A98[4] = {
    {
        lbl_8022109C,
        lbl_802210C8,
        lbl_802210D0,
        lbl_802210D4,
        FLAGS_ZERO,
    },
    {
        lbl_8022118C,
        lbl_802211DC,
        lbl_802211E4,
        lbl_80221204,
        FLAGS_ZERO,
    },
    {
        lbl_802210D8,
        lbl_8022114C,
        lbl_80221154,
        lbl_80221188,
        (1 << 30) | (1 << 31),
    },
};

StageData lbl_803E8AF4 = {
    47,           lbl_803E8A98, "/GrTIc.dat", lbl_80220F14, func_80220F10,
    lbl_80220F84, lbl_80220F88, lbl_80220FAC, lbl_80221354, lbl_8022135C,
    (1 << 0),
};

char str0[] = "%s:%d: couldn t get gobj(id=%d)\n";
char str1[] = "grticeclimber.c";
