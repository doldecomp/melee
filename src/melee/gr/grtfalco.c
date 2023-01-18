#include <melee/gr/grtfalco.h>

#include <melee/gr/ground.h>

/* static */ StageCallbacks lbl_803E8918[4] = {
    {
        lbl_80220984,
        lbl_802209B0,
        lbl_802209B8,
        lbl_802209BC,
        FLAGS_ZERO,
    },
    {
        lbl_80220A50,
        lbl_80220AA0,
        lbl_80220AA8,
        lbl_80220AC8,
        FLAGS_ZERO,
    },
    {
        lbl_802209C0,
        lbl_80220A10,
        lbl_80220A18,
        lbl_80220A4C,
        (1 << 30) | (1 << 31),
    },
};

StageData lbl_803E8974 = {
    45,
    lbl_803E8918,
    "/GrTFc.dat",
    lbl_802207F4,
    func_802207F0,
    lbl_8022086C,
    lbl_80220870,
    lbl_80220894,
    lbl_80220ACC,
    lbl_80220B78,
    1,
};

char str0[] = "%s:%d: couldn t get gobj(id=%d)\n";
char str1[] = "grtfalco.c";

unk_t lbl_804D6AF8;
