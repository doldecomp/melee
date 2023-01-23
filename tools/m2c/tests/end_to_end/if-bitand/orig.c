volatile int glob;

void test(void) {
    if (glob & 0x1) glob = 0;
    if (glob & 0x10000) glob = 0;
    if (glob & 0x80000000) glob = 0;
    if ((glob & 0x1) != 0) glob = 0;
    if ((glob & 0x10000) != 0) glob = 0;
    if ((glob & 0x80000000) != 0) glob = 0;
}
