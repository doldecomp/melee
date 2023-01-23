int globals[10];

void test(int lim) {
    int i;
    for (i = 0; i < lim; i++) {
        globals[0] = 1;
        if (globals[1] == 2) {
            globals[2] = 3;
            break;
        }
        if (globals[2] == 2) {
            globals[3] = 3;
            continue;
        }
        if (globals[4] == 2) {
            globals[5] = 3;
            break;
        }
        if (globals[5] == 2) {
            globals[6] = 3;
            continue;
        }
        globals[3] = 4;
    }
    globals[4] = 5;
}
