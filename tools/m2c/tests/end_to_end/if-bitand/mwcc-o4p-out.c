extern s32 glob;

void test(void) {
    if (glob & 1) {
        glob = 0;
    }
    if (glob & 0x10000) {
        glob = 0;
    }
    if (glob & 0x80000000) {
        glob = 0;
    }
    if (glob & 1) {
        glob = 0;
    }
    if (glob & 0x10000) {
        glob = 0;
    }
    if (glob & 0x80000000) {
        glob = 0;
    }
}
