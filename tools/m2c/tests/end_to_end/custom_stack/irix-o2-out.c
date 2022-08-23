struct _m2c_stack_test {
    /* 0x00 */ char pad0[0x20];
    /* 0x20 */ struct Vec e;
    /* 0x2C */ struct Vec *d;
    /* 0x30 */ s32 c;
    /* 0x34 */ s16 b;
    /* 0x36 */ char pad36[1];
    /* 0x37 */ s8 a;
};                                                  /* size = 0x38 */

? func_00400090(s8 *);                              /* static */

s32 test(struct Vec *v) {
    s8 a;
    s16 b;
    s32 c;
    struct Vec *d;
    struct Vec e;
    s32 temp_t4;

    func_00400090(&a);
    func_00400090((s8 *) &b);
    func_00400090((s8 *) &c);
    func_00400090((s8 *) &d);
    func_00400090((s8 *) &e);
    a = v->x + v->y;
    b = v->x + v->z;
    temp_t4 = v->y + v->z;
    c = temp_t4;
    e = v->x * a;
    e.y = v->y * b;
    e.z = v->z * temp_t4;
    if (a != 0) {
        d = v;
    } else {
        d = &e;
    }
    return a + b + c + d->x + e.y;
}
