static int read(int fd, void * buf, int count) {
    return count;
}
static int write(int fd, void * buf, int count) {
    return count;
}

int test(int in, int out) {
    char buf[0x123456];
    int count = sizeof(buf);

    count = read(in, buf, count);
    if (count < 0) {
        return count;
    }
    buf[0] ^= 0x55;
    buf[count - 1] ^= 0x55;
    return write(out, buf, count);
}
