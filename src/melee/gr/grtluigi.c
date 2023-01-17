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

StageData lbl_803E8E4C = {
    51,
    lbl_803E8DF0,
    "/GrTLg.dat",
    lbl_80221C14,
    func_80221C10,
    lbl_80221C84,
    lbl_80221C88,
    lbl_80221CAC,
    lbl_80221EE4,
    lbl_80221EEC,
    1,
};

#ifdef MUST_MATCH
#pragma push
#pragma force_active on
char str0[] = "%s:%d: couldn t get gobj(id=%d)\n";
char str1[] = "grtluigi.c";
#endif

void func_80221C10(int arg0)
{
    return;
}
