extern u8 x;
extern u8 y;

void test(void *arg0) {
    x = (x & ~0x80) | ((arg0->unk0 << 7) & 0x80);
    x = (x & ~0x40) | ((arg0->unk1 << 6) & 0x40);
    x = (x & ~0x3E) | ((arg0->unk2 << 1) & 0x3E);
    y |= 0x80;
    x = (s16) (((u16) x & ~0x1F0) | (((s8) arg0->unk3 << 4) & 0x1F0));
    y &= ~0x40;
}
