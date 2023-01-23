struct _m2c_stack_test {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ s8 sp18;                             /* inferred */
    /* 0x19 */ char pad19[3];                       /* maybe part of sp18[4]? */
    /* 0x1C */ s32 sp1C;                            /* inferred */
    /* 0x20 */ s32 sp20;                            /* inferred */
    /* 0x24 */ s8 sp24;                             /* inferred */
    /* 0x25 */ char pad25[3];                       /* maybe part of sp24[4]? */
    /* 0x28 */ s8 sp28;                             /* inferred */
    /* 0x29 */ char pad29[3];                       /* maybe part of sp28[4]? */
    /* 0x2C */ s8 sp2C;                             /* inferred */
    /* 0x2D */ char pad2D[2];                       /* maybe part of sp2C[3]? */
    /* 0x2F */ s8 sp2F;                             /* inferred */
};                                                  /* size = 0x30 */

? func_00400090(s8 *);                              /* static */

s32 test(void *arg0) {
    s8 sp2F;
    s8 sp2C;
    s8 sp28;
    s8 sp24;                                        /* compiler-managed */
    s32 sp20;
    s32 sp1C;
    s8 sp18;

    func_00400090(&sp2F);
    func_00400090(&sp2C);
    func_00400090(&sp28);
    func_00400090(&sp24);
    func_00400090(&sp18);
    sp2F = arg0->unk0 + arg0->unk4;
    sp2C = arg0->unk0 + arg0->unk8;
    sp28 = arg0->unk4 + arg0->unk8;
    sp18 = arg0->unk0 * sp2F;
    sp1C = arg0->unk4 * (s16) sp2C;
    sp20 = arg0->unk8 * (s32) sp28;
    if (sp2F != 0) {
        sp24 = arg0;
    } else {
        sp24 = &sp18;
    }
    return sp2F + (s16) sp2C + (s32) sp28 + *sp24 + sp1C;
}
