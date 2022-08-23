int test(int arg0, int arg1) {
    // Dummy variable, so the stack has non-zero size
    int x = 0;
    return &arg1 - &arg0;
}
