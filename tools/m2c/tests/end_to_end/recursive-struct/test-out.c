typedef struct {
    /* 0x0000 */ char pad0[0xC];
    /* 0x000C */ ? unkC;                            /* inferred */
    /* 0x000C */ char padC[4];
    /* 0x0010 */ s32 whatever[0x1000];
} SomeStruct;                                       /* size = 0x4010 */

extern SomeStruct *glob2;

s16 test(void) {
    glob2 = &glob;
    glob2 = (SomeStruct *) &glob.unkC;
    return glob.unk100;
}
