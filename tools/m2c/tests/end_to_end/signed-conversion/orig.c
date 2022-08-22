volatile int glob;
void test(int x) {
    glob = (char)x;
    glob = (char)(x * 2);
    glob = (char)(x * 3);
    glob = (short)x;
    glob = (short)(x * 2);
    glob = (short)(x * 3);
}
