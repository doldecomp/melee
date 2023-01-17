#include <melee/gr/grtluigi.h>

#include <melee/gr/ground.h>
#include <melee/gr/grzakogenerator.h>
#include <melee/gr/types.h>

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

void lbl_80221C14(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    func_80221CB4(0);
    func_80221CB4(1);
    func_80221CB4(2);
    func_801C39C0();
    func_801C3BB4();
    func_801C4210();
    func_801C42AC();
}

void lbl_80221C84(void)
{
    return;
}

void lbl_80221C88(void)
{
    func_801CAE04(0);
}

bool lbl_80221CAC(void)
{
    return false;
}
