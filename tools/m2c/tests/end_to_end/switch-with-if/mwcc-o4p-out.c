extern s32 glob;

void test(s32 arg0) {
    if (arg0 < 5) {
        if (arg0 < 1) {

        } else {
            glob = 1;
            if (arg0 == 1) {
                glob = 2;
            }
        }
    } else if (arg0 < 7) {
        if (arg0 == 1) {
            glob = 1;
        } else {
            glob = 2;
        }
    }
    if (arg0 < 5) {
        if (arg0 < 1) {
            return;
        }
        glob = 1;
        if (arg0 == 1) {
            glob = 2;
        }
    } else if (arg0 < 7) {
        if (arg0 == 1) {
            glob = 1;
            return;
        }
        glob = 2;
    }
}
