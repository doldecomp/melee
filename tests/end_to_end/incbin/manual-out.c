/*
Unable to find README.md in any of 1 search paths
*/
static s32 foo[2] = { 0x01020304, 0x05060708 };     /* const */
static s32 bar = 0x05060708;                        /* const */

s32 test(void) {
    return *foo + bar;
}
