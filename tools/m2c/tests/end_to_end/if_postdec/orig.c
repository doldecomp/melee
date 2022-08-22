int glob;
int test(void) {
    if (glob-- < 1) {
        return 4;
    }
    return 6;
}
