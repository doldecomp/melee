extern s32 glob;

s32 test(void *arg0) {
    glob = arg0->unk12348;
    return arg0 + 0x10000 + 0x2348;
}
