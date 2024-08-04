#include <dolphin.h>
#include <dolphin/mtx.h>
#include "fake_tgmath.h"

#define qr0 0

// unsorted externs
extern f32 sinf(f32);
extern f32 cosf(f32);

// .sbss
static float Unit01[2] = {
    0.0f,
    1.0f
};

void C_MTXIdentity(Mtx m) {
    ASSERTMSGLINE(0xA1, m, "MtxIdentity():  NULL Mtx 'm' ");
    m[0][0] = 1;
    m[0][1] = 0;
    m[0][2] = 0;
    m[0][3] = 0;
    m[1][0] = 0;
    m[1][1] = 1;
    m[1][2] = 0;
    m[1][3] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = 1;
    m[2][3] = 0;
}

void PSMTXIdentity(register Mtx m) {
    register f32 c_zero = 0.0f;
    register f32 c_one = 1.0f;
    register f32 c_01;
    register f32 c_10;

    asm {
        psq_st c_zero, 8(m), 0, qr0
        ps_merge01 c_01, c_zero, c_one
        psq_st c_zero, 24(m), 0, qr0
        ps_merge10 c_10, c_one, c_zero
        psq_st c_zero, 32(m), 0, qr0
        psq_st c_01, 16(m), 0, qr0
        psq_st c_10, 0(m), 0, qr0
        psq_st c_10, 40(m), 0, qr0
    }
}

void C_MTXCopy(Mtx src, Mtx dst) {
    ASSERTMSGLINE(0xDE, src, "MTXCopy():  NULL MtxPtr 'src' ");
    ASSERTMSGLINE(0xDF, dst, "MTXCopy():  NULL MtxPtr 'dst' ");
    if (src != dst) {
        dst[0][0] = src[0][0];
        dst[0][1] = src[0][1];
        dst[0][2] = src[0][2];
        dst[0][3] = src[0][3];
        dst[1][0] = src[1][0];
        dst[1][1] = src[1][1];
        dst[1][2] = src[1][2];
        dst[1][3] = src[1][3];
        dst[2][0] = src[2][0];
        dst[2][1] = src[2][1];
        dst[2][2] = src[2][2];
        dst[2][3] = src[2][3];
    }
}

asm void PSMTXCopy(register Mtx src, register Mtx dst) {
    psq_l f0, 0(src), 0, qr0
    psq_st f0, 0(dst), 0, qr0
    psq_l f1, 8(src), 0, qr0
    psq_st f1, 8(dst), 0, qr0
    psq_l f2, 16(src), 0, qr0
    psq_st f2, 16(dst), 0, qr0
    psq_l f3, 24(src), 0, qr0
    psq_st f3, 24(dst), 0, qr0
    psq_l f4, 32(src), 0, qr0
    psq_st f4, 32(dst), 0, qr0
    psq_l f5, 40(src), 0, qr0
    psq_st f5, 40(dst), 0, qr0
}

void C_MTXConcat(Mtx a, Mtx b, Mtx ab) {
    Mtx mTmp;
    f32 (*m)[4];

    ASSERTMSGLINE(0x128, a, "MTXConcat():  NULL MtxPtr 'a'  ");
    ASSERTMSGLINE(0x129, b, "MTXConcat():  NULL MtxPtr 'b'  ");
    ASSERTMSGLINE(0x12A, ab, "MTXConcat():  NULL MtxPtr 'ab' ");

    if (ab == a || ab == b) {
        m = mTmp;
    } else {
        m = ab;
    }

    m[0][0] =       0 +  a[0][2] * b[2][0] + ((a[0][0] * b[0][0]) + (a[0][1] * b[1][0]));
    m[0][1] =       0 +  a[0][2] * b[2][1] + ((a[0][0] * b[0][1]) + (a[0][1] * b[1][1]));
    m[0][2] =       0 +  a[0][2] * b[2][2] + ((a[0][0] * b[0][2]) + (a[0][1] * b[1][2]));
    m[0][3] = a[0][3] + (a[0][2] * b[2][3] +  (a[0][0] * b[0][3]  + (a[0][1] * b[1][3])));

    m[1][0] =       0 +  a[1][2] * b[2][0] + ((a[1][0] * b[0][0]) + (a[1][1] * b[1][0]));
    m[1][1] =       0 +  a[1][2] * b[2][1] + ((a[1][0] * b[0][1]) + (a[1][1] * b[1][1]));
    m[1][2] =       0 +  a[1][2] * b[2][2] + ((a[1][0] * b[0][2]) + (a[1][1] * b[1][2]));
    m[1][3] = a[1][3] + (a[1][2] * b[2][3] +  (a[1][0] * b[0][3]  + (a[1][1] * b[1][3])));

    m[2][0] =       0 +  a[2][2] * b[2][0] + ((a[2][0] * b[0][0]) + (a[2][1] * b[1][0]));
    m[2][1] =       0 +  a[2][2] * b[2][1] + ((a[2][0] * b[0][1]) + (a[2][1] * b[1][1]));
    m[2][2] =       0 +  a[2][2] * b[2][2] + ((a[2][0] * b[0][2]) + (a[2][1] * b[1][2]));
    m[2][3] = a[2][3] + (a[2][2] * b[2][3] +  (a[2][0] * b[0][3]  + (a[2][1] * b[1][3])));

    if (m == mTmp) {
        C_MTXCopy(mTmp, ab);
    }
}

asm void PSMTXConcat(register Mtx mA, register Mtx mB, register Mtx mAB) {
    nofralloc
    stwu r1, -64(r1)
    psq_l f0, 0(mA), 0, qr0
    stfd f14, 8(r1)
    psq_l f6, 0(mB), 0, qr0
    lis r6, Unit01@ha
    psq_l f7, 8(mB), 0, qr0
    stfd f15, 16(r1)
    addi r6, r6, Unit01@l
    stfd f31, 40(r1)
    psq_l f8, 16(mB), 0, qr0
    ps_muls0 f12, f6, f0
    psq_l f2, 16(mA), 0, qr0
    ps_muls0 f13, f7, f0
    psq_l f31, 0(r6), 0, qr0
    ps_muls0 f14, f6, f2
    psq_l f9, 24(mB), 0, qr0
    ps_muls0 f15, f7, f2
    psq_l f1, 8(mA), 0, qr0
    ps_madds1 f12, f8, f0, f12
    psq_l f3, 24(mA), 0, qr0
    ps_madds1 f14, f8, f2, f14
    psq_l f10, 32(mB), 0, qr0
    ps_madds1 f13, f9, f0, f13
    psq_l f11, 40(mB), 0, qr0
    ps_madds1 f15, f9, f2, f15
    psq_l f4, 32(mA), 0, qr0
    psq_l f5, 40(mA), 0, qr0
    ps_madds0 f12, f10, f1, f12
    ps_madds0 f13, f11, f1, f13
    ps_madds0 f14, f10, f3, f14
    ps_madds0 f15, f11, f3, f15
    psq_st f12, 0(mAB), 0, qr0
    ps_muls0 f2, f6, f4
    ps_madds1 f13, f31, f1, f13
    ps_muls0 f0, f7, f4
    psq_st f14, 16(mAB), 0, qr0
    ps_madds1 f15, f31, f3, f15
    psq_st f13, 8(mAB), 0, qr0
    ps_madds1 f2, f8, f4, f2
    ps_madds1 f0, f9, f4, f0
    ps_madds0 f2, f10, f5, f2
    lfd f14, 8(r1)
    psq_st f15, 24(mAB), 0, qr0
    ps_madds0 f0, f11, f5, f0
    psq_st f2, 32(mAB), 0, qr0
    ps_madds1 f0, f31, f5, f0
    lfd f15, 16(r1)
    psq_st f0, 40(mAB), 0, qr0
    lfd f31, 40(r1)
    addi r1, r1, 64
    blr
}

void C_MTXTranspose(Mtx src, Mtx xPose) {
    Mtx mTmp;
    f32 (* m)[4];

    ASSERTMSGLINE(0x22D, src, "MTXTranspose():  NULL MtxPtr 'src' ");
    ASSERTMSGLINE(0x22E, xPose, "MTXTranspose():  NULL MtxPtr 'xPose' ");

    if (src == xPose) {
        m = mTmp;
    } else {
        m = xPose;
    }

    m[0][0] = src[0][0];
    m[0][1] = src[1][0];
    m[0][2] = src[2][0];
    m[0][3] = 0;
    m[1][0] = src[0][1];
    m[1][1] = src[1][1];
    m[1][2] = src[2][1];
    m[1][3] = 0;
    m[2][0] = src[0][2];
    m[2][1] = src[1][2];
    m[2][2] = src[2][2];
    m[2][3] = 0;
    if (m == mTmp) {
        C_MTXCopy(mTmp, xPose);
    }
}

void PSMTXTranspose(register Mtx src, register Mtx xPose) {
    register f32 c_zero = 0;
    register f32 row0a;
    register f32 row1a;
    register f32 row0b;
    register f32 row1b;
    register f32 trns0;
    register f32 trns1;
    register f32 trns2;

    asm {
        psq_l row0a, 0(src), 0, qr0
    }
    xPose[2][3] = c_zero;
    asm {
        psq_l row1a, 16(src), 0, qr0
        ps_merge00 trns0, row0a, row1a
        psq_l row0b, 8(src), 1, qr0
        ps_merge11 trns1, row0a, row1a
        psq_l row1b, 24(src), 1, qr0
        psq_st trns0, 0(xPose), 0, qr0
        psq_l row0a, 32(src), 0, qr0
        ps_merge00 trns2, row0b, row1b
        psq_st trns1, 16(xPose), 0, qr0
        ps_merge00 trns0, row0a, c_zero
        psq_st trns2, 32(xPose), 0, qr0
        ps_merge10 trns1, row0a, c_zero
        psq_st trns0, 8(xPose), 0, qr0
    }
    row0b = src[2][2];
    asm {
        psq_st trns1, 24(xPose), 0, qr0
    }
    xPose[2][2] = row0b;
}

u32 C_MTXInverse(Mtx src, Mtx inv) {
    Mtx mTmp;
    f32 (*m)[4];
    f32 det;

    ASSERTMSGLINE(0x290, src, "MTXInverse():  NULL MtxPtr 'src' ");
    ASSERTMSGLINE(0x291, inv, "MTXInverse():  NULL MtxPtr 'inv' ");

    if (src == inv) {
        m = mTmp;
    } else {
        m = inv;
    }
    det = ((((src[2][1] * (src[0][2] * src[1][0])) 
          + ((src[2][2] * (src[0][0] * src[1][1])) 
           + (src[2][0] * (src[0][1] * src[1][2])))) 
           - (src[0][2] * (src[2][0] * src[1][1]))) 
           - (src[2][2] * (src[1][0] * src[0][1]))) 
           - (src[1][2] * (src[0][0] * src[2][1]));
    if (0 == det) {
        return 0;
    }
    det = 1 / det;
    m[0][0] = (det * +((src[1][1] * src[2][2]) - (src[2][1] * src[1][2])));
    m[0][1] = (det * -((src[0][1] * src[2][2]) - (src[2][1] * src[0][2])));
    m[0][2] = (det * +((src[0][1] * src[1][2]) - (src[1][1] * src[0][2])));

    m[1][0] = (det * -((src[1][0] * src[2][2]) - (src[2][0] * src[1][2])));
    m[1][1] = (det * +((src[0][0] * src[2][2]) - (src[2][0] * src[0][2])));
    m[1][2] = (det * -((src[0][0] * src[1][2]) - (src[1][0] * src[0][2])));

    m[2][0] = (det * +((src[1][0] * src[2][1]) - (src[2][0] * src[1][1])));
    m[2][1] = (det * -((src[0][0] * src[2][1]) - (src[2][0] * src[0][1])));
    m[2][2] = (det * +((src[0][0] * src[1][1]) - (src[1][0] * src[0][1])));

    m[0][3] = ((-m[0][0] * src[0][3]) - (m[0][1] * src[1][3])) - (m[0][2] * src[2][3]);
    m[1][3] = ((-m[1][0] * src[0][3]) - (m[1][1] * src[1][3])) - (m[1][2] * src[2][3]);
    m[2][3] = ((-m[2][0] * src[0][3]) - (m[2][1] * src[1][3])) - (m[2][2] * src[2][3]);

    if (m == mTmp) {
        C_MTXCopy(mTmp, inv);
    }
    return 1;
}

asm u32 PSMTXInverse(register Mtx src, register Mtx inv) {
    psq_l f0, 0(src), 1, qr0
    psq_l f1, 4(src), 0, qr0
    psq_l f2, 16(src), 1, qr0
    ps_merge10 f6, f1, f0
    psq_l f3, 20(src), 0, qr0
    psq_l f4, 32(src), 1, qr0
    ps_merge10 f7, f3, f2
    psq_l f5, 36(src), 0, qr0
    ps_mul f11, f3, f6
    ps_mul f13, f5, f7
    ps_merge10 f8, f5, f4
    ps_msub f11, f1, f7, f11
    ps_mul f12, f1, f8
    ps_msub f13, f3, f8, f13
    ps_mul f10, f3, f4
    ps_msub f12, f5, f6, f12
    ps_mul f9, f0, f5
    ps_mul f8, f1, f2
    ps_sub f6, f6, f6
    ps_msub f10, f2, f5, f10
    ps_mul f7, f0, f13
    ps_msub f9, f1, f4, f9
    ps_madd f7, f2, f12, f7
    ps_msub f8, f0, f3, f8
    ps_madd f7, f4, f11, f7
    ps_cmpo0 cr0, f7, f6
    bne skip_return
    li r3, 0
    blr
skip_return:
    ps_res f0, f7
    ps_add f6, f0, f0
    ps_mul f5, f0, f0
    ps_nmsub f0, f7, f5, f6
    ps_add f6, f0, f0
    ps_mul f5, f0, f0
    ps_nmsub f0, f7, f5, f6
    lfs f1, 12(src)
    ps_muls0 f13, f13, f0
    lfs f2, 28(src)
    ps_muls0 f12, f12, f0
    lfs f3, 44(src)
    ps_muls0 f11, f11, f0
    ps_merge00 f5, f13, f12
    ps_muls0 f10, f10, f0
    ps_merge11 f4, f13, f12
    ps_muls0 f9, f9, f0
    psq_st f5, 0(inv), 0, qr0
    ps_mul f6, f13, f1
    psq_st f4, 16(inv), 0, qr0
    ps_muls0 f8, f8, f0
    ps_madd f6, f12, f2, f6
    psq_st f10, 32(inv), 1, qr0
    ps_nmadd f6, f11, f3, f6
    psq_st f9, 36(inv), 1, qr0
    ps_mul f7, f10, f1
    ps_merge00 f5, f11, f6
    psq_st f8, 40(inv), 1, qr0
    ps_merge11 f4, f11, f6
    psq_st f5, 8(inv), 0, qr0
    ps_madd f7, f9, f2, f7
    psq_st f4, 24(inv), 0, qr0
    ps_nmadd f7, f8, f3, f7
    li r3, 1
    psq_st f7, 44(inv), 1, qr0
}

u32 C_MTXInvXpose(Mtx src, Mtx invX) {
    Mtx mTmp;
    f32 (*m)[4];
    f32 det;

    ASSERTMSGLINE(0x380, src, "MTXInvXpose(): NULL MtxPtr 'src' ");
    ASSERTMSGLINE(0x381, invX, "MTXInvXpose(): NULL MtxPtr 'invX' ");

    if (src == invX) {
        m = mTmp;
    } else {
        m = invX;
    }
    det = ((((src[2][1] * (src[0][2] * src[1][0])) 
          + ((src[2][2] * (src[0][0] * src[1][1])) 
          +  (src[2][0] * (src[0][1] * src[1][2])))) 
          -  (src[0][2] * (src[2][0] * src[1][1]))) 
          -  (src[2][2] * (src[1][0] * src[0][1]))) 
          -  (src[1][2] * (src[0][0] * src[2][1]));
    if (0 == det) {
        return 0;
    }
    det = 1 / det;
    m[0][0] = (det * +((src[1][1] * src[2][2]) - (src[2][1] * src[1][2])));
    m[0][1] = (det * -((src[1][0] * src[2][2]) - (src[2][0] * src[1][2])));
    m[0][2] = (det * +((src[1][0] * src[2][1]) - (src[2][0] * src[1][1])));

    m[1][0] = (det * -((src[0][1] * src[2][2]) - (src[2][1] * src[0][2])));
    m[1][1] = (det * +((src[0][0] * src[2][2]) - (src[2][0] * src[0][2])));
    m[1][2] = (det * -((src[0][0] * src[2][1]) - (src[2][0] * src[0][1])));

    m[2][0] = (det * +((src[0][1] * src[1][2]) - (src[1][1] * src[0][2])));
    m[2][1] = (det * -((src[0][0] * src[1][2]) - (src[1][0] * src[0][2])));
    m[2][2] = (det * +((src[0][0] * src[1][1]) - (src[1][0] * src[0][1])));

    m[0][3] = 0;
    m[1][3] = 0;
    m[2][3] = 0;

    if (m == mTmp) {
        C_MTXCopy(mTmp, invX);
    }
    return 1;
}

asm u32 PSMTXInvXpose(register Mtx src, register Mtx invX) {
	psq_l f0, 0(src), 1, qr0
	psq_l f1, 4(src), 0, qr0
	psq_l f2, 16(src), 1, qr0
	ps_merge10 f6, f1, f0
	psq_l f3, 20(src), 0, qr0
	psq_l f4, 32(src), 1, qr0
	ps_merge10 f7, f3, f2
	psq_l f5, 36(src), 0, qr0
	ps_mul f11, f3, f6
	ps_merge10 f8, f5, f4
	ps_mul f13, f5, f7
	ps_msub f11, f1, f7, f11
	ps_mul f12, f1, f8
	ps_msub f13, f3, f8, f13
	ps_msub f12, f5, f6, f12
	ps_mul f10, f3, f4
	ps_mul f9, f0, f5
	ps_mul f8, f1, f2
	ps_msub f10, f2, f5, f10
	ps_msub f9, f1, f4, f9
	ps_msub f8, f0, f3, f8
	ps_mul f7, f0, f13
	ps_sub f1, f1, f1
	ps_madd f7, f2, f12, f7
	ps_madd f7, f4, f11, f7
	ps_cmpo0 cr0, f7, f1
	bne skip_return
	li r3, 0
	blr
skip_return:
	ps_res f0, f7
	psq_st f1, 12(invX), 1, qr0
	ps_add f6, f0, f0
	ps_mul f5, f0, f0
	ps_nmsub f0, f7, f5, f6
	psq_st f1, 28(invX), 1, qr0
	ps_add f6, f0, f0
	ps_mul f5, f0, f0
	ps_nmsub f0, f7, f5, f6
	psq_st f1, 44(invX), 1, qr0
	ps_muls0 f13, f13, f0
	ps_muls0 f12, f12, f0
	psq_st f13, 0(invX), 0, qr0
	ps_muls0 f11, f11, f0
	psq_st f12, 16(invX), 0, qr0
	ps_muls0 f10, f10, f0
	psq_st f11, 32(invX), 0, qr0
	ps_muls0 f9, f9, f0
	psq_st f10, 8(invX), 1, qr0
	ps_muls0 f8, f8, f0
	psq_st f9, 24(invX), 1, qr0
	li r3, 1
	psq_st f8, 40(invX), 1, qr0
}

void MTXRotRad(Mtx m, char axis, f32 rad) {
    f32 sinA;
    f32 cosA;

    ASSERTMSGLINE(0x48B, m, "MTXRotRad():  NULL MtxPtr 'm' ");
    sinA = sinf(rad);
    cosA = cosf(rad);
    MTXRotTrig(m, axis, sinA, cosA);
}

void MTXRotTrig(Mtx m, char axis, f32 sinA, f32 cosA) {
    ASSERTMSGLINE(0x4AF, m, "MTXRotTrig():  NULL MtxPtr 'm' ");
    switch(axis) {
        case 120:
        case 88:
            m[0][0] = 1;
            m[0][1] = 0;
            m[0][2] = 0;
            m[0][3] = 0;
            m[1][0] = 0;
            m[1][1] = cosA;
            m[1][2] = -sinA;
            m[1][3] = 0;
            m[2][0] = 0;
            m[2][1] = sinA;
            m[2][2] = cosA;
            m[2][3] = 0;
            break;
        case 121:
        case 89:
            m[0][0] = cosA;
            m[0][1] = 0;
            m[0][2] = sinA;
            m[0][3] = 0;
            m[1][0] = 0;
            m[1][1] = 1;
            m[1][2] = 0;
            m[1][3] = 0;
            m[2][0] = -sinA;
            m[2][1] = 0;
            m[2][2] = cosA;
            m[2][3] = 0;
            break;
        case 122:
        case 90:
            m[0][0] = cosA;
            m[0][1] = -sinA;
            m[0][2] = 0;
            m[0][3] = 0;
            m[1][0] = sinA;
            m[1][1] = cosA;
            m[1][2] = 0;
            m[1][3] = 0;
            m[2][0] = 0;
            m[2][1] = 0;
            m[2][2] = 1;
            m[2][3] = 0;
            break;
        default:
            ASSERTMSGLINE(0x4CB, FALSE, "MTXRotTrig():  invalid 'axis' value ");
            break;
    }
}

void MTXRotAxisRad(Mtx m, Vec *axis, f32 rad) {
    Vec vN;
    f32 s;
    f32 c;
    f32 t;
    f32 x;
    f32 y;
    f32 z;
    f32 xSq;
    f32 ySq;
    f32 zSq;

    ASSERTMSGLINE(0x50B, m, "MTXRotAxisRad():  NULL MtxPtr 'm' ");
    ASSERTMSGLINE(0x50C, axis, "MTXRotAxisRad():  NULL VecPtr 'axis' ");

    s = sinf(rad);
    c = cosf(rad);
    t = 1 - c;
    VECNormalize(axis, &vN);
    x = vN.x;
    y = vN.y;
    z = vN.z;
    xSq = (x * x);
    ySq = (y * y);
    zSq = (z * z);
    m[0][0] = (c + (t * xSq));
    m[0][1] = (y * (t * x)) - (s * z);
    m[0][2] = (z * (t * x)) + (s * y);
    m[0][3] = 0;
    m[1][0] = ((y * (t * x)) + (s * z));
    m[1][1] = (c + (t * ySq));
    m[1][2] = ((z * (t * y)) - (s * x));
    m[1][3] = 0;
    m[2][0] = ((z * (t * x)) - (s * y));
    m[2][1] = ((z * (t * y)) + (s * x));
    m[2][2] = (c + (t * zSq));
    m[2][3] = 0;
}

void MTXTrans(Mtx m, f32 xT, f32 yT, f32 zT) {
    ASSERTMSGLINE(0x547, m, "MTXTrans():  NULL MtxPtr 'm' ");
    m[0][0] = 1;
    m[0][1] = 0;
    m[0][2] = 0;
    m[0][3] = xT;
    m[1][0] = 0;
    m[1][1] = 1;
    m[1][2] = 0;
    m[1][3] = yT;
    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = 1;
    m[2][3] = zT;
}

void MTXTransApply(Mtx src, Mtx dst, f32 xT, f32 yT, f32 zT) {
    ASSERTMSGLINE(0x567, src, "MTXTransApply(): NULL MtxPtr 'src' ");
    ASSERTMSGLINE(0x568, dst, "MTXTransApply(): NULL MtxPtr 'src' "); //! wrong assert string

    if (src != dst) {
        dst[0][0] = src[0][0];
        dst[0][1] = src[0][1];
        dst[0][2] = src[0][2];
        dst[1][0] = src[1][0];
        dst[1][1] = src[1][1];
        dst[1][2] = src[1][2];
        dst[2][0] = src[2][0];
        dst[2][1] = src[2][1];
        dst[2][2] = src[2][2];
    }
    dst[0][3] = (src[0][3] + xT);
    dst[1][3] = (src[1][3] + yT);
    dst[2][3] = (src[2][3] + zT);
}

void MTXScale(Mtx m, f32 xS, f32 yS, f32 zS) {
    ASSERTMSGLINE(0x58A, m, "MTXScale():  NULL MtxPtr 'm' ");
    m[0][0] = xS;
    m[0][1] = 0;
    m[0][2] = 0;
    m[0][3] = 0;
    m[1][0] = 0;
    m[1][1] = yS;
    m[1][2] = 0;
    m[1][3] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = zS;
    m[2][3] = 0;
}

void MTXScaleApply(Mtx src, Mtx dst, f32 xS, f32 yS, f32 zS) {
    ASSERTMSGLINE(0x5A8, src, "MTXScaleApply(): NULL MtxPtr 'src' ");
    ASSERTMSGLINE(0x5A9, dst, "MTXScaleApply(): NULL MtxPtr 'dst' ");
    dst[0][0] = (src[0][0] * xS);
    dst[0][1] = (src[0][1] * xS);
    dst[0][2] = (src[0][2] * xS);
    dst[0][3] = (src[0][3] * xS);
    dst[1][0] = (src[1][0] * yS);
    dst[1][1] = (src[1][1] * yS);
    dst[1][2] = (src[1][2] * yS);
    dst[1][3] = (src[1][3] * yS);
    dst[2][0] = (src[2][0] * zS);
    dst[2][1] = (src[2][1] * zS);
    dst[2][2] = (src[2][2] * zS);
    dst[2][3] = (src[2][3] * zS);
}

void MTXQuat(Mtx m, QuaternionPtr q) {
    f32 s;
    f32 xs;
    f32 ys;
    f32 zs;
    f32 wx;
    f32 wy;
    f32 wz;
    f32 xx;
    f32 xy;
    f32 xz;
    f32 yy;
    f32 yz;
    f32 zz;

    ASSERTMSGLINE(0x5C9, m, "MTXQuat():  NULL MtxPtr 'm' ");
    ASSERTMSGLINE(0x5CA, q, "MTXQuat():  NULL QuaternionPtr 'q' ");
    ASSERTMSGLINE(0x5CB, q->x || q->y || q->z || q->w, "MTXQuat():  zero-value quaternion ");
    s = 2 / ((q->w * q->w) + ((q->z * q->z) + ((q->x * q->x) + (q->y * q->y))));
    xs = q->x * s;
    ys = q->y * s;
    zs = q->z * s;
    wx = q->w * xs;
    wy = q->w * ys;
    wz = q->w * zs;
    xx = q->x * xs;
    xy = q->x * ys;
    xz = q->x * zs;
    yy = q->y * ys;
    yz = q->y * zs;
    zz = q->z * zs;
    m[0][0] = (1 - (yy + zz));
    m[0][1] = (xy - wz);
    m[0][2] = (xz + wy);
    m[0][3] = 0;
    m[1][0] = (xy + wz);
    m[1][1] = (1 - (xx + zz));
    m[1][2] = (yz - wx);
    m[1][3] = 0;
    m[2][0] = (xz - wy);
    m[2][1] = (yz + wx);
    m[2][2] = (1 - (xx + yy));
    m[2][3] = 0;
}

void MTXReflect(Mtx m, Vec *p, Vec *n) {
    f32 vxy;
    f32 vxz;
    f32 vyz;
    f32 pdotn;

    vxy = -2 * n->x * n->y;
    vxz = -2 * n->x * n->z;
    vyz = -2 * n->y * n->z;
    pdotn = 2 * VECDotProduct(p, n);
    m[0][0] = (1 - (2 * n->x * n->x));
    m[0][1] = vxy;
    m[0][2] = vxz;
    m[0][3] = (pdotn * n->x);
    m[1][0] = vxy;
    m[1][1] = (1 - (2 * n->y * n->y));
    m[1][2] = vyz;
    m[1][3] = (pdotn * n->y);
    m[2][0] = vxz;
    m[2][1] = vyz;
    m[2][2] = (1 - (2 * n->z * n->z));
    m[2][3] = (pdotn * n->z);
}

void MTXLookAt(Mtx m, Vec *camPos, Vec *camUp, Vec *target) {
    Vec vLook;
    Vec vRight;
    Vec vUp;

    ASSERTMSGLINE(0x63E, m, "MTXLookAt():  NULL MtxPtr 'm' ");
    ASSERTMSGLINE(0x63F, camPos, "MTXLookAt():  NULL VecPtr 'camPos' ");
    ASSERTMSGLINE(0x640, camUp, "MTXLookAt():  NULL VecPtr 'camUp' ");
    ASSERTMSGLINE(0x641, target, "MTXLookAt():  NULL Point3dPtr 'target' ");

    vLook.x = camPos->x - target->x;
    vLook.y = camPos->y - target->y;
    vLook.z = camPos->z - target->z;
    VECNormalize(&vLook, &vLook);
    VECCrossProduct(camUp, &vLook, &vRight);
    VECNormalize(&vRight, &vRight);
    VECCrossProduct(&vLook, &vRight, &vUp);
    m[0][0] = vRight.x;
    m[0][1] = vRight.y;
    m[0][2] = vRight.z;
    m[0][3] = -((camPos->z * vRight.z) + ((camPos->x * vRight.x) + (camPos->y * vRight.y)));
    m[1][0] = vUp.x;
    m[1][1] = vUp.y;
    m[1][2] = vUp.z;
    m[1][3] = -((camPos->z * vUp.z) + ((camPos->x * vUp.x) + (camPos->y * vUp.y)));
    m[2][0] = vLook.x;
    m[2][1] = vLook.y;
    m[2][2] = vLook.z;
    m[2][3] = -((camPos->z * vLook.z) + ((camPos->x * vLook.x) + (camPos->y * vLook.y)));
}

void MTXLightFrustum(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 scaleS, f32 scaleT, f32 transS, f32 transT) {
    f32 tmp;

    ASSERTMSGLINE(0x6A2, m, "MTXLightFrustum():  NULL MtxPtr 'm' ");
    ASSERTMSGLINE(0x6A3, (t != b), "MTXLightFrustum():  't' and 'b' clipping planes are equal ");
    ASSERTMSGLINE(0x6A4, (l != r), "MTXLightFrustum():  'l' and 'r' clipping planes are equal ");

    tmp = 1 / (r - l);
    m[0][0] = (scaleS * (2 * n * tmp));
    m[0][1] = 0;
    m[0][2] = (scaleS * (tmp * (r + l))) - transS;
    m[0][3] = 0;
    tmp = 1 / (t - b);
    m[1][0] = 0;
    m[1][1] = (scaleT * (2 * n * tmp));
    m[1][2] = (scaleT * (tmp * (t + b))) - transT;
    m[1][3] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = -1;
    m[2][3] = 0;
}

void MTXLightPerspective(Mtx m, f32 fovY, f32 aspect, f32 scaleS, f32 scaleT, f32 transS, f32 transT) {
    f32 angle;
    f32 cot;

    ASSERTMSGLINE(0x6DF, m, "MTXLightPerspective():  NULL MtxPtr 'm' ");
    ASSERTMSGLINE(0x6E0, (fovY > 0.0) && (fovY < 180.0), "MTXLightPerspective():  'fovY' out of range ");
    ASSERTMSGLINE(0x6E1, 0 != aspect, "MTXLightPerspective():  'aspect' is 0 ");

    angle = (0.5f * fovY);
    angle = angle * 0.017453293f;
    cot = 1 / tanf(angle);
    m[0][0] = (scaleS * (cot / aspect));
    m[0][1] = 0;
    m[0][2] = -transS;
    m[0][3] = 0;
    m[1][0] = 0;
    m[1][1] = (cot * scaleT);
    m[1][2] = -transT;
    m[1][3] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = -1;
    m[2][3] = 0;
}

void MTXLightOrtho(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 scaleS, f32 scaleT, f32 transS, f32 transT) {
    f32 tmp;

    ASSERTMSGLINE(0x720, m, "MTXLightOrtho():  NULL MtxPtr 'm' ");
    ASSERTMSGLINE(0x721, (t != b), "MTXLightOrtho():  't' and 'b' clipping planes are equal ");
    ASSERTMSGLINE(0x722, (l != r), "MTXLightOrtho():  'l' and 'r' clipping planes are equal ");
    tmp = 1 / (r - l);
    m[0][0] = (2 * tmp * scaleS);
    m[0][1] = 0;
    m[0][2] = 0;
    m[0][3] = (transS + (scaleS * (tmp * -(r + l))));
    tmp = 1/ (t - b);
    m[1][0] = 0;
    m[1][1] = (2 * tmp * scaleT);
    m[1][2] = 0;
    m[1][3] = (transT + (scaleT * (tmp * -(t + b))));
    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = 0;
    m[2][3] = 1;
}
