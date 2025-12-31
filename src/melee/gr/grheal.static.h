#include <platform.h>

#include "dolphin/types.h"
#include "gr/grheal.h"
#include "gr/types.h"

struct yaku {
    int x0;
    int x4;
};

static s32 grHeal_803E83B8[0x27] = {
    0x1D001E, 0x1F0020, 0x210022, 0x230024, 0x250026, 0x270028, 0x29002A,
    0x2B002C, 0x2D002E, 0x2F0030, 0x310032, 0x330034, 0x350036, 0,
    0x15,     1,        0x16,     0x14,     2,        0x19,     3,
    0xE,      4,        5,        7,        6,        8,        9,
    0xA,      0xB,      0x18,     0xC,      0xD,      0xF,      0x10,
    0x11,     0x12,     0x17,     -1,
};

static StageCallbacks grHeal_803E8454[] = { {
                                                grHeal_8021F0D8,
                                                grHeal_8021F170,
                                                grHeal_8021F178,
                                                grHeal_8021F17C,
                                                0,
                                            },
                                            {
                                                grHeal_8021F180,
                                                grHeal_8021F41C,
                                                grHeal_8021F474,
                                                grHeal_8021F4BC,
                                                0xC0000000,
                                            },
                                            {
                                                grHeal_8021F5C8,
                                                grHeal_8021F5CC,
                                                grHeal_8021F5D4,
                                                grHeal_8021F5D8,
                                                0,
                                            },
                                            {
                                                grHeal_8021F5DC,
                                                grHeal_8021F618,
                                                grHeal_8021F620,
                                                grHeal_8021F624,
                                                0,
                                            },
                                            {
                                                grHeal_8021F6F8,
                                                grHeal_8021F6FC,
                                                grHeal_8021F704,
                                                grHeal_8021F708,
                                                0,
                                            } };

static StageData grHeal_803E84C4 = {
    0x42,
    grHeal_803E8454,
    "/GrHe.dat",
    grHeal_8021EF3C,
    grHeal_8021EF38,
    grHeal_8021EFBC,
    grHeal_8021EFC0,
    grHeal_8021EFE4,
    grHeal_8021F830,
    grHeal_8021F838,
    1,
    0,
    0,
};

static char grHeal_803E851C[0x2C] = {
    0x67, 0x72, 0x68, 0x65, 0x61, 0x6C, 0x2E, 0x63, 0,    0,    0,
    0,    0x2A, 0x2A, 0x2A, 0x20, 0x4E, 0x6F, 0x74, 0x20, 0x66, 0x6F,
    0x75, 0x6E, 0x64, 0x20, 0x4E, 0x65, 0x78, 0x74, 0x20, 0x50, 0x6C,
    0x61, 0x79, 0x65, 0x72, 0x21, 0x28, 0x25, 0x64, 0x29, 0xA,  0,
};

extern struct yaku* grHeal_804D6AF0;
