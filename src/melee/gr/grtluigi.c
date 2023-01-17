#include <melee/gr/grtluigi.h>

#include <melee/gr/types.h>

// .4byte NULL
// .4byte NULL
// .4byte NULL
// .4byte NULL
// .4byte NULL

/* static */ StageCallbacks lbl_803E8DF0[4] = {
    {
        lbl_80221D9C,
        lbl_80221DC8,
        lbl_80221DD0,
        lbl_80221DD4,
        FLAGS_ZERO,
    },
    {
        lbl_80221E68,
        lbl_80221EB8,
        lbl_80221EC0,
        lbl_80221EE0,
        FLAGS_ZERO,
    },
    {
        lbl_80221DD8,
        lbl_80221E28,
        lbl_80221E30,
        lbl_80221E64,
        (1 << 30) | (1 << 31),
    },
};

char lbl_803E8E40[] = "/GrTLg.dat";

void func_80221C10(void)
{
    return;
}
