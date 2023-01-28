extern u8 a;
extern u8 b;
extern s16 c;
extern u16 d;
extern s32 e;
extern s32 f;
static ? ar;

void test(void) {
    ar.unk0 = (s32) (s8) a;
    ar.unk4 = (s32) b;
    ar.unk8 = (s32) c;
    ar.unkC = (s32) d;
    ar.unk10 = (s32) e;
    ar.unk14 = (s32) f;
}
