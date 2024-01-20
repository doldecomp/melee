typedef struct Base {
    /* 0x0 */ char pad0[4];
    /* 0x4 */ ? *unk4;                              /* inferred */
} Base;                                             /* size >= 0x8 */

typedef struct Derived {
    /* 0x0 */ s32 unk0;                             /* inferred */
    /* 0x4 */ struct __vt__7Derived *vtable4;       /* inferred */
} Derived;                                          /* size >= 0x8 */

struct __vt__7Derived {
    /* 0x0 */ struct RTTI *__RTTI;
    /* 0x4 */ s32 unk4;                             /* inferred */
    /* 0x8 */ u64 (*virtual_method)(Derived *, s32);
};                                                  /* size = 0xC */

void *__ct__4BaseFv(Base *this);                    /* static */
Derived *__ct__7DerivedFi(Derived *this, s32 arg0); /* static */
void compute__FR7Derivedi(Derived *arg0, s32 arg1); /* static */
s32 method__4BaseFi(Base *this, s32 arg0);          /* static */
s32 static_method__4BaseFi(Base *this, u32 arg0);   /* static */
u64 virtual_method__7DerivedFi(Derived *this, s32 arg0); /* static */
static struct RTTI __RTTI__7Derived;                /* unable to generate initializer: cannot parse $$210 as integer */

void test(s32 arg0) {
    Derived spC;

    __ct__7DerivedFi(&spC, arg0);
    compute__FR7Derivedi(&spC, arg0);
}

/* compute (Derived &, int) */
void compute__FR7Derivedi(Derived *arg0, s32 arg1) {
    u64 temp_ret;

    arg0->unk0 = arg1;
    temp_ret = arg0->vtable4->virtual_method(arg0, arg1);
    method__4BaseFi((Base *) arg0, static_method__4BaseFi(temp_ret, (u32) temp_ret));
}

/* Base::method (int) */
s32 method__4BaseFi(Base *this, s32 arg0) {
    return arg0 * 3;
}

/* Base::static_method (int) */
s32 static_method__4BaseFi(Base *this, u32 arg0) {
    return (s32) this * 2;
}

/* Derived::virtual_method (int) */
u64 virtual_method__7DerivedFi(Derived *this, s32 arg0) {
    return arg0 * 4;
}

/* Derived::Derived (int) */
Derived *__ct__7DerivedFi(Derived *this, s32 arg0) {
    __ct__4BaseFv((Base *) this);
    this->vtable4 = &__vt__7Derived;
    this->unk0 = arg0;
    return this;
}

/* Base::Base (void) */
void __ct__4BaseFv(Base *this) {
    this->unk4 = &__vt__4Base;
}
