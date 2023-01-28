extern ? sym;

void test(void) {
    *NULL = 1;
    *(s32 *)0x10 = 0;
    *(s32 *)0x20 = 0;
    *(s32 *)0x40 = 0;
    *NULL = 0x50;
    *(&sym + 8) = 0;
}
