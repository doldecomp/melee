int test(int a, int b, int c, int d) {
    int i;
    int ret = 0;

    while (a && (b || c)) {
        ret++;
    }

    while (a || (b && c)) {
        ret++;
    }

    while (a) {
        ret++;
        if (b && (c || d)) {
            continue;
        }
        ret++;
        if (b || (c && d)) {
            continue;
        }
        ret++;
        if (b && (c || d)) {
            break;
        }
        ret++;
        if (b || (c && d)) {
            break;
        }
        ret++;
    }

    for (i = 0; i < 10 && (a || b); i += c + d) {
        ret++; 
    }

    return ret;
}
