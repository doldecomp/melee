#include <dolphin.h>
#include <dolphin/mtx.h>
#include "fake_tgmath.h"

#define qr0 0

void C_MTXMultVec(Mtx44 m, Vec *src, Vec *dst) {
    Vec vTmp;

    ASSERTMSGLINE(0x39, m, "MTXMultVec():  NULL MtxPtr 'm' ");
    ASSERTMSGLINE(0x3A, src, "MTXMultVec():  NULL MtxPtr 'src' ");
    ASSERTMSGLINE(0x3B, dst, "MTXMultVec():  NULL MtxPtr 'dst' ");

    vTmp.x = m[0][3] + ((m[0][2] * src->z) + ((m[0][0] * src->x) + (m[0][1] * src->y)));
    vTmp.y = m[1][3] + ((m[1][2] * src->z) + ((m[1][0] * src->x) + (m[1][1] * src->y)));
    vTmp.z = m[2][3] + ((m[2][2] * src->z) + ((m[2][0] * src->x) + (m[2][1] * src->y)));
    dst->x = vTmp.x;
    dst->y = vTmp.y;
    dst->z = vTmp.z;
}

asm void PSMTXMultVec(register Mtx44 m, register Vec *src, register Vec *dst) {
    nofralloc
    psq_l f0, Vec.x(src), 0, qr0
    psq_l f2, 0(m), 0, qr0
    psq_l f1, Vec.z(src), 1, qr0
    ps_mul f4, f2, f0
    psq_l f3, 8(m), 0, qr0
    ps_madd f5, f3, f1, f4
    psq_l f8, 16(m), 0, qr0
    ps_sum0 f6, f5, f6, f5
    psq_l f9, 24(m), 0, qr0
    ps_mul f10, f8, f0
    psq_st f6, Vec.x(dst), 1, qr0
    ps_madd f11, f9, f1, f10
    psq_l f2, 32(m), 0, qr0
    ps_sum0 f12, f11, f12, f11
    psq_l f3, 40(m), 0, qr0
    ps_mul f4, f2, f0
    psq_st f12, Vec.y(dst), 1, qr0
    ps_madd f5, f3, f1, f4
    ps_sum0 f6, f5, f6, f5
    psq_st f6, Vec.z(dst), 1, qr0
    blr
}

void C_MTXMultVecArray(Mtx m, Vec *srcBase, Vec *dstBase, u32 count) {
    u32 i;
    Vec vTmp;

    ASSERTMSGLINE(0x9F, m, "MTXMultVecArray():  NULL MtxPtr 'm' ");
    ASSERTMSGLINE(0xA0, srcBase, "MTXMultVecArray():  NULL MtxPtr 'srcBase' ");
    ASSERTMSGLINE(0xA1, dstBase, "MTXMultVecArray():  NULL MtxPtr 'dstBase' ");

    for(i = 0; i < count; i++) {
        vTmp.x = m[0][3] + ((m[0][2] * srcBase->z) + ((m[0][0] * srcBase->x) + (m[0][1] * srcBase->y)));
        vTmp.y = m[1][3] + ((m[1][2] * srcBase->z) + ((m[1][0] * srcBase->x) + (m[1][1] * srcBase->y)));
        vTmp.z = m[2][3] + ((m[2][2] * srcBase->z) + ((m[2][0] * srcBase->x) + (m[2][1] * srcBase->y)));
        dstBase->x = vTmp.x;
        dstBase->y = vTmp.y;
        dstBase->z = vTmp.z;
        srcBase++;
        dstBase++;
    }
}

asm void PSMTXMultVecArray(register Mtx m, register Vec *srcBase, register Vec *dstBase, register u32 count) {
	psq_l f0, 0(m), 0, qr0
	subi count, count, 1
	psq_l f6, Vec.x(srcBase), 0, qr0
	mtctr count
	psq_l f7, Vec.z(srcBase), 1, qr0
	psq_l f1, 8(m), 0, qr0
	addi srcBase, srcBase, 8
	psq_l f2, 16(m), 0, qr0
	subi dstBase, dstBase, 4
    
	psq_l f3, 24(m), 0, qr0
	ps_mul f8, f0, f6
	psq_l f4, 32(m), 0, qr0
	ps_mul f10, f2, f6
	psq_l f5, 40(m), 0, qr0
	ps_mul f12, f4, f6
	psq_lu f6, Vec.y(srcBase), 0, qr0
	ps_madd f8, f1, f7, f8
	ps_madd f10, f3, f7, f10
	ps_madd f12, f5, f7, f12
	psq_lu f7, Vec.z(srcBase), 1, qr0
	ps_sum0 f9, f8, f8, f8
loop:
	ps_sum0 f11, f10, f10, f10
	ps_mul f8, f0, f6
	ps_sum0 f13, f12, f12, f12
	ps_mul f10, f2, f6
	psq_stu f9, Vec.y(dstBase), 1, qr0
	ps_mul f12, f4, f6
	psq_stu f11, Vec.y(dstBase), 1, qr0
	ps_madd f8, f1, f7, f8
	psq_stu f13, Vec.y(dstBase), 1, qr0
	ps_madd f10, f3, f7, f10
	psq_lu f6, Vec.y(srcBase), 0, qr0
	ps_madd f12, f5, f7, f12
	psq_lu f7, Vec.z(srcBase), 1, qr0
	ps_sum0 f9, f8, f8, f8
	bdnz loop
	ps_sum0 f11, f10, f10, f10
	ps_sum0 f13, f12, f12, f12
	psq_stu f9, Vec.y(dstBase), 1, qr0
	psq_stu f11, Vec.y(dstBase), 1, qr0
	psq_stu f13, Vec.y(dstBase), 1, qr0
}

void MTXMultVecSR(Mtx44 m, Vec *src, Vec *dst) {
    Vec vTmp;

    ASSERTMSGLINE(0x13A, m, "MTXMultVecSR():  NULL MtxPtr 'm' ");
    ASSERTMSGLINE(0x13B, src, "MTXMultVecSR():  NULL MtxPtr 'src' ");
    ASSERTMSGLINE(0x13C, dst, "MTXMultVecSR():  NULL MtxPtr 'dst' ");
    vTmp.x = (m[0][2] * src->z) + ((m[0][0] * src->x) + (m[0][1] * src->y));
    vTmp.y = (m[1][2] * src->z) + ((m[1][0] * src->x) + (m[1][1] * src->y));
    vTmp.z = (m[2][2] * src->z) + ((m[2][0] * src->x) + (m[2][1] * src->y));
    dst->x = vTmp.x;
    dst->y = vTmp.y;
    dst->z = vTmp.z;
}

void MTXMultVecArraySR(Mtx44 m, Vec *srcBase, Vec *dstBase, u32 count) {
    u32 i;
    Vec vTmp;

    ASSERTMSGLINE(0x161, m, "MTXMultVecArraySR():  NULL MtxPtr 'm' ");
    ASSERTMSGLINE(0x162, srcBase, "MTXMultVecArraySR():  NULL MtxPtr 'srcBase' ");
    ASSERTMSGLINE(0x163, dstBase, "MTXMultVecArraySR():  NULL MtxPtr 'dstBase' ");

    for(i = 0; i < count; i++) {
        vTmp.x = (m[0][2] * srcBase->z) + ((m[0][0] * srcBase->x) + (m[0][1] * srcBase->y));
        vTmp.y = (m[1][2] * srcBase->z) + ((m[1][0] * srcBase->x) + (m[1][1] * srcBase->y));
        vTmp.z = (m[2][2] * srcBase->z) + ((m[2][0] * srcBase->x) + (m[2][1] * srcBase->y));
        dstBase->x = vTmp.x;
        dstBase->y = vTmp.y;
        dstBase->z = vTmp.z;
        srcBase++;
        dstBase++;
    }
}
