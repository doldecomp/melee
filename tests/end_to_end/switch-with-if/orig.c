volatile int glob;

void test(int x) {
    switch (x) {
    case 1:
    case 2:
    case 3:
    case 4:
        glob = 1;
        if (x == 1) glob = 2;
        break;
    case 5:
    case 6:
        if (x == 1) glob = 1;
        else glob = 2;
        break;
    }

    // again with break being compiled to "jr ra"
    switch (x) {
    case 1:
    case 2:
    case 3:
    case 4:
        glob = 1;
        if (x == 1) glob = 2;
        break;
    case 5:
    case 6:
        if (x == 1) glob = 1;
        else glob = 2;
        break;
    }
}
