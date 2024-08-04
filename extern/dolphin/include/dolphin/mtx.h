#ifndef _DOLPHIN_MTX_H_
#define _DOLPHIN_MTX_H_

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	f32 x, y, z;
} Vec, *VecPtr, Point3d, *Point3dPtr;

typedef struct
{
    s16 x, y, z;
} S16Vec, *S16VecPtr;

typedef struct
{
	f32 x, y, z, w;
} Quaternion, *QuaternionPtr, Qtrn, *QtrnPtr;

typedef f32 Mtx[3][4];
typedef f32 Mtx44[4][4];

typedef f32 (*MtxPtr)[4];
typedef f32 (*Mtx44Ptr)[4];

typedef f32 ROMtx[4][3];
typedef f32 (*ROMtxPtr)[3];

void MTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void MTXOrtho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);

void C_MTXFrustum(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void C_MTXPerspective(Mtx44 m, f32 fovY, f32 aspect, f32 n, f32 f);
void C_MTXLookAt(Mtx m, Point3dPtr camPos, VecPtr camUp, Point3dPtr target);

#ifdef DEBUG
#define VECSquareMag C_VECSquareMag
#define VECNormalize C_VECNormalize
#define VECAdd C_VECAdd
#define VECDotProduct C_VECDotProduct
#define VECSquareDistance C_VECSquareDistance
#define VECCrossProduct C_VECCrossProduct
#define MTXMultVec C_MTXMultVec
#define MTXMultVecArray C_MTXMultVecArray
#define MTXCopy C_MTXCopy
#define MTXConcat C_MTXConcat
#define MTXInverse C_MTXInverse
#define MTXTranspose C_MTXTranspose
#define MTXIdentity  C_MTXIdentity
#else
#define VECSquareMag PSVECSquareMag
#define VECNormalize PSVECNormalize
#define VECAdd PSVECAdd
#define VECDotProduct PSVECDotProduct
#define VECSquareDistance PSVECSquareDistance
#define VECCrossProduct PSVECCrossProduct
#define MTXMultVec PSMTXMultVec
#define MTXMultVecArray PSMTXMultVecArray
#define MTXCopy PSMTXCopy
#define MTXConcat PSMTXConcat
#define MTXInverse PSMTXInverse
#define MTXTranspose PSMTXTranspose
#define MTXIdentity  PSMTXIdentity
#endif

// asm only
#define MTXReorder PSMTXReorder
#define MTXROMultVecArray PSMTXROMultVecArray
#define MTXROSkin2VecArray PSMTXROSkin2VecArray
#define MTXROMultS16VecArray PSMTXROMultS16VecArray
#define MTXMultS16VecArray PSMTXMultS16VecArray

// mtx.c
// functions
void MTXRotRad(Mtx m, char axis, f32 rad);
void MTXRotTrig(Mtx m, char axis, f32 sinA, f32 cosA);
void MTXRotAxisRad(Mtx m, Vec *axis, f32 rad);
void MTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void MTXTransApply(Mtx src, Mtx dst, f32 xT, f32 yT, f32 zT);
void MTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void MTXScaleApply(Mtx src, Mtx dst, f32 xS, f32 yS, f32 zS);
void MTXQuat(Mtx m, QuaternionPtr q);
void MTXReflect(Mtx m, Vec *p, Vec *n);
void MTXLookAt(Mtx m, Vec *camPos, Vec *camUp, Vec *target);
void MTXLightFrustum(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 scaleS, f32 scaleT, f32 transS, f32 transT);
void MTXLightPerspective(Mtx m, f32 fovY, f32 aspect, f32 scaleS, f32 scaleT, f32 transS, f32 transT);
void MTXLightOrtho(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 scaleS, f32 scaleT, f32 transS, f32 transT);

// C functions
void C_MTXIdentity(Mtx m);
void C_MTXCopy(Mtx src, Mtx dst);
void C_MTXConcat(Mtx a, Mtx b, Mtx ab);
void C_MTXTranspose(Mtx src, Mtx xPose);
u32 C_MTXInverse(Mtx src, Mtx inv);
u32 C_MTXInvXpose(Mtx src, Mtx invX);

// asm functions
void PSMTXIdentity(Mtx m);
void PSMTXCopy(Mtx src, Mtx dst);
void PSMTXConcat(Mtx mA, Mtx mB, Mtx mAB);
void PSMTXTranspose(Mtx src, Mtx xPose);
u32 PSMTXInverse(Mtx src, Mtx inv);
u32 PSMTXInvXpose(Mtx src, Mtx invX);

// mtxstack.c
typedef struct {
    u32 numMtx;
    Mtx *stackBase;
    Mtx *stackPtr;
} MTXStack;

void MTXInitStack(MTXStack *sPtr, u32 numMtx);
Mtx *MTXPush(MTXStack *sPtr, Mtx m);
Mtx *MTXPushFwd(MTXStack *sPtr, Mtx m);
Mtx *MTXPushInv(MTXStack *sPtr, Mtx m);
Mtx *MTXPushInvXpose(MTXStack *sPtr, Mtx m);
Mtx *MTXPop(MTXStack *sPtr);
Mtx *MTXGetStackPtr(MTXStack *sPtr);

// mtxvec.c
void MTXMultVecSR(Mtx44 m, Vec *src, Vec *dst);
void MTXMultVecArraySR(Mtx44 m, Vec *srcBase, Vec *dstBase, u32 count); 

// C functions
void C_MTXMultVec(Mtx44 m, Vec *src, Vec *dst);
void C_MTXMultVecArray(Mtx m, Vec *srcBase, Vec *dstBase, u32 count);

// asm functions
void PSMTXMultVec(Mtx44 m, Vec *src, Vec *dst);
void PSMTXMultVecArray(Mtx m, Vec *srcBase, Vec *dstBase, u32 count);

// psmtx.c
void PSMTXReorder(Mtx src, ROMtx dest);
void PSMTXROMultVecArray(ROMtx *m, Vec *srcBase, Vec *dstBase, u32 count);
void PSMTXROSkin2VecArray(ROMtx *m0, ROMtx *m1, f32 * wtBase, Vec *srcBase, Vec *dstBase, u32 count);
void PSMTXROMultS16VecArray(ROMtx *m, S16Vec *srcBase, Vec *dstBase, u32 count);
void PSMTXMultS16VecArray(Mtx44 *m, S16Vec *srcBase, Vec *dstBase, u32 count);

// vec.c
f32 VECMag(Vec *v);
void VECHalfAngle(Vec *a, Vec *b, Vec *half);
void VECReflect(Vec *src, Vec *normal, Vec *dst);
f32 VECDistance(Vec *a, Vec *b);

// C functions
void C_VECAdd(Vec *a, Vec *b, Vec *c);
void C_VECSubtract(Vec *a, Vec *b, Vec *c);
void C_VECScale(Vec *src, Vec *dst, f32 scale);
void C_VECNormalize(Vec *src, Vec *unit);
f32 C_VECSquareMag(Vec *v);
f32 C_VECDotProduct(Vec *a, Vec *b);
void C_VECCrossProduct(Vec *a, Vec *b, Vec *axb);
f32 C_VECSquareDistance(Vec *a, Vec *b);

// Asm functions
void PSVECAdd(Vec *a, Vec *b, Vec *c); 
void PSVECSubtract(Vec *a, Vec *b, Vec *c);
void PSVECScale(Vec *src, Vec *dst, f32 scale);
void PSVECNormalize(Vec *vec1, Vec *dst);
f32 PSVECSquareMag(Vec *vec1);
f32 PSVECDotProduct(Vec *vec1, Vec *vec2);
void PSVECCrossProduct(Vec *vec1, Vec *vec2, Vec *dst);
f32 PSVECSquareDistance(Vec *vec1, Vec *vec2);

#ifdef __cplusplus
}
#endif

#endif
