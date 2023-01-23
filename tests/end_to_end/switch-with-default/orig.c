int glob;

int test(int x) {
    switch (x) {
    case 2:
        x--;
        // fallthrough
    case 3:
        glob++;
        break;
    case 9:
        break;
    case 13:
        x *= 2;
        break;
    default:
        x /= 2;
        break;
    }

    test(glob);
    if (!glob) {
        glob = x;
    }
    return 2;
}
