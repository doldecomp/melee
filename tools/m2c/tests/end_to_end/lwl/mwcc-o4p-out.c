? strcpy(? *, ? *, s32);                            /* extern */
? foo(s32 *, u16);                                  /* static */
extern ? a1;
extern ? a2;
extern s32 a3;
static ? buf;
static ? $$24;                                      /* unable to generate initializer */
static s32 $$22 = 0x61626364;                       /* const */

void test(void) {
    u8 spE;
    u16 spC;
    s32 sp8;

    sp8 = $$22;
    spC = (u16) $$22;
    spE = (u8) $$22;
    foo(&sp8, (u16) $$22);
    a1.unk1 = (s32) a2.unk1;
    a3 = a1.unk0;
    a3 = (u8) a1.unk0;
    strcpy(&buf, &$$24, a1.unk0);
}
