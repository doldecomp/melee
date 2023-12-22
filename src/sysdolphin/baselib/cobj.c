#include <dolphin/gx/forward.h>

#include "cobj.h"

#include "aobj.h"
#include "class.h"
#include "debug.h"
#include "displayfunc.h"
#include "initialize.h"
#include "mtx.h"
#include "video.h"
#include "wobj.h"

#include <math.h>
#include <placeholder.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/types.h>
#include <dolphin/mtx.h>
#include <dolphin/mtx/mtxvec.h>
#include <dolphin/mtx/vec.h>
#include <dolphin/vi/vi.h>
#include <MetroTRK/intrinsics.h>
#include <MSL/trigf.h>

static HSD_ClassInfo* default_class;
static HSD_CObj* current;

extern const float HSD_CObj_804DE474; // 0.01745329252F

#define DegToRad(a) ((a) * 0.01745329252F)

static int CObjInit(HSD_Class* o);
static int CObjLoad(HSD_CObj* cobj, HSD_CObjDesc* cobjdesc);
static void CObjInfoInit(void);
static void CObjUpdateFunc(void* obj, int type, HSD_ObjData* val);
static void CObjRelease(HSD_Class* o);
static void CObjAmnesia(HSD_ClassInfo* info);

#ifdef MUST_MATCH

#pragma push
asm void HSD_CObjEraseScreen(HSD_CObj* cobj, s32 enable_color,
                             s32 enable_alpha, s32 enable_depth)
{ // clang-format off
    nofralloc
/* 803676F8 003642D8  7C 08 02 A6 */	mflr r0
/* 803676FC 003642DC  90 01 00 04 */	stw r0, 4(r1)
/* 80367700 003642E0  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 80367704 003642E4  DB E1 00 48 */	stfd f31, 0x48(r1)
/* 80367708 003642E8  DB C1 00 40 */	stfd f30, 0x40(r1)
/* 8036770C 003642EC  DB A1 00 38 */	stfd f29, 0x38(r1)
/* 80367710 003642F0  DB 81 00 30 */	stfd f28, 0x30(r1)
/* 80367714 003642F4  DB 61 00 28 */	stfd f27, 0x28(r1)
/* 80367718 003642F8  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8036771C 003642FC  3B E6 00 00 */	addi r31, r6, 0
/* 80367720 00364300  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80367724 00364304  3B C5 00 00 */	addi r30, r5, 0
/* 80367728 00364308  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 8036772C 0036430C  3B A4 00 00 */	addi r29, r4, 0
/* 80367730 00364310  93 81 00 18 */	stw r28, 0x18(r1)
/* 80367734 00364314  7C 7C 1B 79 */	or. r28, r3, r3
/* 80367738 00364318  41 82 01 08 */	beq lbl_80367840
/* 8036773C 0036431C  2C 1D 00 00 */	cmpwi r29, 0
/* 80367740 00364320  40 82 00 18 */	bne lbl_80367758
/* 80367744 00364324  2C 1E 00 00 */	cmpwi r30, 0
/* 80367748 00364328  40 82 00 10 */	bne lbl_80367758
/* 8036774C 0036432C  2C 1F 00 00 */	cmpwi r31, 0
/* 80367750 00364330  40 82 00 08 */	bne lbl_80367758
/* 80367754 00364334  48 00 00 EC */	b lbl_80367840
lbl_80367758:
/* 80367758 00364338  7F 83 E3 78 */	mr r3, r28
/* 8036775C 0036433C  48 00 28 55 */	bl HSD_CObjGetFar
/* 80367760 00364340  FF E0 08 90 */	fmr f31, f1
/* 80367764 00364344  7F 83 E3 78 */	mr r3, r28
/* 80367768 00364348  48 00 28 21 */	bl HSD_CObjGetNear
/* 8036776C 0036434C  EC 21 F8 2A */	fadds f1, f1, f31
/* 80367770 00364350  C8 02 EA 88 */	lfd f0, 0.5
/* 80367774 00364354  7F 83 E3 78 */	mr r3, r28
/* 80367778 00364358  FF E0 00 72 */	fmul f31, f0, f1
/* 8036777C 0036435C  FF E0 F8 18 */	frsp f31, f31
/* 80367780 00364360  48 00 29 AD */	bl HSD_CObjGetProjectionType
/* 80367784 00364364  2C 03 00 02 */	cmpwi r3, 2
/* 80367788 00364368  41 82 00 54 */	beq lbl_803677DC
/* 8036778C 0036436C  40 80 00 10 */	bge lbl_8036779C
/* 80367790 00364370  2C 03 00 01 */	cmpwi r3, 1
/* 80367794 00364374  40 80 00 14 */	bge lbl_803677A8
/* 80367798 00364378  48 00 00 84 */	b lbl_8036781C
lbl_8036779C:
/* 8036779C 0036437C  2C 03 00 04 */	cmpwi r3, 4
/* 803677A0 00364380  40 80 00 7C */	bge lbl_8036781C
/* 803677A4 00364384  48 00 00 68 */	b lbl_8036780C
lbl_803677A8:
/* 803677A8 00364388  C0 22 EA 94 */	lfs f1, HSD_CObj_804DE474
/* 803677AC 0036438C  C0 1C 00 40 */	lfs f0, 0x40(r28)
/* 803677B0 00364390  C0 42 EA 90 */	lfs f2, 0.5F
/* 803677B4 00364394  EC 01 00 32 */	fmuls f0, f1, f0
/* 803677B8 00364398  EC 22 00 32 */	fmuls f1, f2, f0
/* 803677BC 0036439C  4B FB EA 01 */	bl tanf
/* 803677C0 003643A0  EF 9F 00 72 */	fmuls f28, f31, f1
/* 803677C4 003643A4  C0 1C 00 44 */	lfs f0, 0x44(r28)
/* 803677C8 003643A8  EC 1C 00 32 */	fmuls f0, f28, f0
/* 803677CC 003643AC  FF 60 E0 50 */	fneg f27, f28
/* 803677D0 003643B0  FF A0 00 90 */	fmr f29, f0
/* 803677D4 003643B4  FF C0 00 50 */	fneg f30, f0
/* 803677D8 003643B8  48 00 00 44 */	b lbl_8036781C
lbl_803677DC:
/* 803677DC 003643BC  7F 83 E3 78 */	mr r3, r28
/* 803677E0 003643C0  48 00 27 A9 */	bl HSD_CObjGetNear
/* 803677E4 003643C4  EC 9F 08 24 */	fdivs f4, f31, f1
/* 803677E8 003643C8  C0 7C 00 4C */	lfs f3, 0x4c(r28)
/* 803677EC 003643CC  C0 5C 00 48 */	lfs f2, 0x48(r28)
/* 803677F0 003643D0  C0 3C 00 40 */	lfs f1, 0x40(r28)
/* 803677F4 003643D4  C0 1C 00 44 */	lfs f0, 0x44(r28)
/* 803677F8 003643D8  EF A4 00 F2 */	fmuls f29, f4, f3
/* 803677FC 003643DC  EF C4 00 B2 */	fmuls f30, f4, f2
/* 80367800 003643E0  EF 84 00 72 */	fmuls f28, f4, f1
/* 80367804 003643E4  EF 64 00 32 */	fmuls f27, f4, f0
/* 80367808 003643E8  48 00 00 14 */	b lbl_8036781C
lbl_8036780C:
/* 8036780C 003643EC  C3 BC 00 4C */	lfs f29, 0x4c(r28)
/* 80367810 003643F0  C3 DC 00 48 */	lfs f30, 0x48(r28)
/* 80367814 003643F4  C3 9C 00 40 */	lfs f28, 0x40(r28)
/* 80367818 003643F8  C3 7C 00 44 */	lfs f27, 0x44(r28)
lbl_8036781C:
/* 8036781C 003643FC  FC 20 E0 90 */	fmr f1, f28
/* 80367820 00364400  7F A3 EB 78 */	mr r3, r29
/* 80367824 00364404  FC 40 D8 90 */	fmr f2, f27
/* 80367828 00364408  7F C4 F3 78 */	mr r4, r30
/* 8036782C 0036440C  FC 60 F0 90 */	fmr f3, f30
/* 80367830 00364410  FC 80 E8 90 */	fmr f4, f29
/* 80367834 00364414  7F E5 FB 78 */	mr r5, r31
/* 80367838 00364418  FC A0 F8 50 */	fneg f5, f31
/* 8036783C 0036441C  48 00 D2 65 */	bl HSD_EraseRect
lbl_80367840:
/* 80367840 00364420  80 01 00 54 */	lwz r0, 0x54(r1)
/* 80367844 00364424  CB E1 00 48 */	lfd f31, 0x48(r1)
/* 80367848 00364428  CB C1 00 40 */	lfd f30, 0x40(r1)
/* 8036784C 0036442C  CB A1 00 38 */	lfd f29, 0x38(r1)
/* 80367850 00364430  CB 81 00 30 */	lfd f28, 0x30(r1)
/* 80367854 00364434  CB 61 00 28 */	lfd f27, 0x28(r1)
/* 80367858 00364438  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8036785C 0036443C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80367860 00364440  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80367864 00364444  83 81 00 18 */	lwz r28, 0x18(r1)
/* 80367868 00364448  38 21 00 50 */	addi r1, r1, 0x50
/* 8036786C 0036444C  7C 08 03 A6 */	mtlr r0
/* 80367870 00364450  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

// Only non-matching because there's a swapped lfs operation if using extern on
// the float constants
void HSD_CObjEraseScreen(HSD_CObj* cobj, s32 enable_color, s32 enable_alpha,
                         s32 enable_depth)
{
    float m_val, z_val, left_res, right_res, top_res, bottom_res;

    if (cobj != NULL &&
        ((enable_color != 0 || enable_alpha != 0 || enable_depth == 0)))
    {
        z_val = (0.5F * (HSD_CObjGetNear(cobj) + HSD_CObjGetFar(cobj)));

        switch (HSD_CObjGetProjectionType(cobj)) {
        case PROJ_PERSPECTIVE:
            top_res = (z_val *
                       tanf(0.5F *
                            DegToRad(cobj->projection_param.perspective.fov)));
            bottom_res = -top_res;
            right_res = top_res * cobj->projection_param.perspective.aspect;
            left_res = -right_res;
            break;
        case PROJ_FRUSTUM:
            m_val = z_val / HSD_CObjGetNear(cobj);
            right_res = m_val * cobj->projection_param.frustum.right;
            left_res = m_val * cobj->projection_param.frustum.left;
            top_res = m_val * cobj->projection_param.frustum.top;
            bottom_res = m_val * cobj->projection_param.frustum.bottom;
            break;
        case PROJ_ORTHO:
            right_res = cobj->projection_param.ortho.right;
            left_res = cobj->projection_param.ortho.left;
            top_res = cobj->projection_param.ortho.top;
            bottom_res = cobj->projection_param.ortho.bottom;
            break;
        }

        HSD_EraseRect(top_res, bottom_res, left_res, right_res, -z_val,
                      enable_color, enable_alpha, enable_depth);
    }
}

#endif

void HSD_CObjRemoveAnimByFlags(HSD_CObj* cobj, u32 flags)
{
    HSD_WObj* wobj;

    if (cobj == NULL) {
        return;
    }

    HSD_AObjRemove(cobj->aobj);
    cobj->aobj = NULL;
    wobj = HSD_CObjGetEyePositionWObj(cobj);
    HSD_WObjRemoveAnim(wobj);
    wobj = HSD_CObjGetInterestWObj(cobj);
    HSD_WObjRemoveAnim(wobj);
}

void HSD_CObjRemoveAnim(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return;
    }

    HSD_CObjRemoveAnimByFlags(cobj, 0x7FF);
}

void HSD_CObjAddAnim(HSD_CObj* cobj, HSD_CameraAnim* canim)
{
    if (cobj == NULL) {
        return;
    }

    if (canim == NULL) {
        return;
    }

    if (cobj->aobj != NULL) {
        HSD_AObjRemove(cobj->aobj);
    }
    cobj->aobj = HSD_AObjLoadDesc(canim->aobjdesc);
    HSD_WObjAddAnim(HSD_CObjGetEyePositionWObj(cobj), canim->eye_anim);
    HSD_WObjAddAnim(HSD_CObjGetInterestWObj(cobj), canim->interest_anim);
}

HSD_CObjInfo hsdCObj = { CObjInfoInit };

typedef struct _HSD_FObjData {
    float fv;
    s32 iv;
    Vec3 p;
} FObjData;

static void CObjUpdateFunc(void* obj, int type, HSD_ObjData* val)
{
    HSD_CObj* cobj = obj;
    Vec3 vec;

    if (cobj == NULL) {
        return;
    }

    switch (type) {
    case 1:
        HSD_CObjGetEyePosition(cobj, &vec);
        vec.x = val->fv;
        HSD_CObjSetEyePosition(cobj, &vec);
        break;
    case 2:
        HSD_CObjGetEyePosition(cobj, &vec);
        vec.y = val->fv;
        HSD_CObjSetEyePosition(cobj, &vec);
        break;
    case 3:
        HSD_CObjGetEyePosition(cobj, &vec);
        vec.z = val->fv;
        HSD_CObjSetEyePosition(cobj, &vec);
        break;
    case 5:
        HSD_CObjGetInterest(cobj, &vec);
        vec.x = val->fv;
        HSD_CObjSetInterest(cobj, &vec);
        break;
    case 6:
        HSD_CObjGetInterest(cobj, &vec);
        vec.x = val->fv;
        HSD_CObjSetInterest(cobj, &vec);
        break;
    case 7:
        HSD_CObjGetInterest(cobj, &vec);
        vec.x = val->fv;
        HSD_CObjSetInterest(cobj, &vec);
        break;
    case 9:
        HSD_CObjSetRoll(cobj, val->fv);
        break;
    case 10:
        HSD_CObjSetFov(cobj, val->fv);
        break;
    case 11:
        HSD_CObjSetNear(cobj, val->fv);
        break;
    case 12:
        HSD_CObjSetFar(cobj, val->fv);
        break;
    }
}

void HSD_CObjAnim(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return;
    }

    HSD_AObjInterpretAnim(cobj->aobj, cobj, CObjUpdateFunc);
    HSD_WObjInterpretAnim(cobj->eyepos);
    HSD_WObjInterpretAnim(cobj->interest);
}

void HSD_CObjReqAnim(HSD_CObj* cobj, float startframe)
{
    if (cobj == NULL) {
        return;
    }

    if (cobj == NULL) {
        return;
    }

    HSD_AObjReqAnim(cobj->aobj, startframe);
    HSD_WObjReqAnim(cobj->eyepos, startframe);
    HSD_WObjReqAnim(cobj->interest, startframe);
}

GXProjectionType makeProjectionMtx(HSD_CObj* cobj, Mtx mtx)
{
    GXProjectionType projection_type;
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        projection_type = GX_PERSPECTIVE;
        C_MTXPerspective(mtx, cobj->projection_param.perspective.fov,
                         cobj->projection_param.perspective.aspect, cobj->near,
                         cobj->far);
        break;
    case PROJ_FRUSTUM:
        projection_type = GX_PERSPECTIVE;
        C_MTXFrustum(mtx, cobj->projection_param.perspective.fov,
                     cobj->projection_param.perspective.aspect,
                     cobj->projection_param.frustum.left,
                     cobj->projection_param.frustum.right, cobj->near,
                     cobj->far);
        break;
    case PROJ_ORTHO:
        projection_type = GX_ORTHOGRAPHIC;
        C_MTXOrtho(mtx, cobj->projection_param.perspective.fov,
                   cobj->projection_param.perspective.aspect,
                   cobj->projection_param.frustum.left,
                   cobj->projection_param.frustum.right, cobj->near,
                   cobj->far);
        break;
    }
    return projection_type;
}

static const float HSD_CObj_804DE478 = 0.0F;
static const float HSD_CObj_804DE47C = 1.0F;

static bool setupOffscreenCamera(HSD_CObj* cobj)
{
    Mtx44 mtx;

    GXSetViewport(cobj->viewport.left, cobj->viewport.top,
                  cobj->viewport.right - cobj->viewport.left,
                  cobj->viewport.bottom - cobj->viewport.top,
                  HSD_CObj_804DE478, HSD_CObj_804DE47C);
    GXSetScissor(cobj->scissor.left, cobj->scissor.top,
                 cobj->scissor.right - cobj->scissor.left,
                 cobj->scissor.bottom - cobj->scissor.top);
    GXSetProjection(mtx, makeProjectionMtx(cobj, mtx));
    return true;
}

// Matching, but references extern float conversion value
int setupNormalCamera(HSD_CObj* cobj)
{
#ifdef MUST_MATCH
    int unused[4];
#endif

    GXProjectionType projection_type;
    Mtx p;

    f32 x_scale;
    f32 y_scale;

    f32 top;
    f32 bottom;
    f32 left;
    f32 right;

    f32 width;
    f32 height;

    GXRenderModeObj* rmode = HSD_VIGetRenderMode();

    x_scale = (f32) rmode->fbWidth / (f32) rmode->viWidth;
    y_scale = (f32) rmode->efbHeight / (f32) rmode->viHeight;

    left = cobj->viewport.left * x_scale;
    right = cobj->viewport.right * x_scale;
    top = cobj->viewport.top * y_scale;
    bottom = cobj->viewport.bottom * y_scale;

    width = right - left;
    height = bottom - top;

    if (rmode->field_rendering) {
        GXSetViewportJitter(left, top, width, height, HSD_CObj_804DE478,
                            HSD_CObj_804DE47C, VIGetNextField());
    } else {
        GXSetViewport(left, top, width, height, HSD_CObj_804DE478,
                      HSD_CObj_804DE47C);
    }

    left = cobj->scissor.left * x_scale;
    right = cobj->scissor.right * x_scale;
    top = cobj->scissor.top * y_scale;
    bottom = cobj->scissor.bottom * y_scale;
    width = right - left;
    height = bottom - top;
    GXSetScissor((u32) left, (u32) top, (u32) width, (u32) height);

    projection_type = makeProjectionMtx(cobj, p);
    GXSetProjection(p, projection_type);

    return 1;
}

extern const f64 HSD_CObj_804DE488;
extern const float HSD_CObj_804DE490;
extern const float HSD_CObj_804DE494;

#ifdef MUST_MATCH
#pragma push
asm int setupTopHalfCamera()
{ // clang-format off
    nofralloc
/* 80367EB0 00364A90  7C 08 02 A6 */	mflr r0
/* 80367EB4 00364A94  3C 80 80 4C */	lis r4, HSD_VIData@ha
/* 80367EB8 00364A98  90 01 00 04 */	stw r0, 4(r1)
/* 80367EBC 00364A9C  3C 00 43 30 */	lis r0, 0x4330
/* 80367EC0 00364AA0  94 21 FF 78 */	stwu r1, -0x88(r1)
/* 80367EC4 00364AA4  DB E1 00 80 */	stfd f31, 0x80(r1)
/* 80367EC8 00364AA8  DB C1 00 78 */	stfd f30, 0x78(r1)
/* 80367ECC 00364AAC  DB A1 00 70 */	stfd f29, 0x70(r1)
/* 80367ED0 00364AB0  BF 41 00 58 */	stmw r26, 0x58(r1)
/* 80367ED4 00364AB4  3B 84 1D 80 */	addi r28, r4, HSD_VIData@l
/* 80367ED8 00364AB8  3B 43 00 00 */	addi r26, r3, 0
/* 80367EDC 00364ABC  A0 9C 00 06 */	lhz r4, 6(r28)
/* 80367EE0 00364AC0  C8 22 EA A0 */	lfd f1, HSD_CObj_804DE480(r2)
/* 80367EE4 00364AC4  90 81 00 54 */	stw r4, 0x54(r1)
/* 80367EE8 00364AC8  C0 43 00 14 */	lfs f2, 0x14(r3)
/* 80367EEC 00364ACC  90 01 00 50 */	stw r0, 0x50(r1)
/* 80367EF0 00364AD0  C8 01 00 50 */	lfd f0, 0x50(r1)
/* 80367EF4 00364AD4  EC 00 08 28 */	fsubs f0, f0, f1
/* 80367EF8 00364AD8  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80367EFC 00364ADC  4C 41 13 82 */	cror 2, 1, 2
/* 80367F00 00364AE0  40 82 00 0C */	bne lbl_80367F0C
/* 80367F04 00364AE4  38 60 00 00 */	li r3, 0
/* 80367F08 00364AE8  48 00 01 D0 */	b lbl_803680D8
lbl_80367F0C:
/* 80367F0C 00364AEC  90 81 00 54 */	stw r4, 0x54(r1)
/* 80367F10 00364AF0  FF E0 10 90 */	fmr f31, f2
/* 80367F14 00364AF4  C0 7A 00 18 */	lfs f3, 0x18(r26)
/* 80367F18 00364AF8  90 01 00 50 */	stw r0, 0x50(r1)
/* 80367F1C 00364AFC  C3 DA 00 0C */	lfs f30, 0xc(r26)
/* 80367F20 00364B00  C8 01 00 50 */	lfd f0, 0x50(r1)
/* 80367F24 00364B04  C0 9A 00 10 */	lfs f4, 0x10(r26)
/* 80367F28 00364B08  EC 00 08 28 */	fsubs f0, f0, f1
/* 80367F2C 00364B0C  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 80367F30 00364B10  40 80 00 08 */	bge lbl_80367F38
/* 80367F34 00364B14  48 00 00 14 */	b lbl_80367F48
lbl_80367F38:
/* 80367F38 00364B18  90 81 00 54 */	stw r4, 0x54(r1)
/* 80367F3C 00364B1C  90 01 00 50 */	stw r0, 0x50(r1)
/* 80367F40 00364B20  C8 01 00 50 */	lfd f0, 0x50(r1)
/* 80367F44 00364B24  EC 60 08 28 */	fsubs f3, f0, f1
lbl_80367F48:
/* 80367F48 00364B28  EC 23 10 28 */	fsubs f1, f3, f2
/* 80367F4C 00364B2C  EF A4 F0 28 */	fsubs f29, f4, f30
/* 80367F50 00364B30  4B FB A9 71 */	bl __cvt_fp2unsigned
/* 80367F54 00364B34  7C 7D 1B 78 */	mr r29, r3
/* 80367F58 00364B38  FC 20 E8 90 */	fmr f1, f29
/* 80367F5C 00364B3C  4B FB A9 65 */	bl __cvt_fp2unsigned
/* 80367F60 00364B40  7C 7E 1B 78 */	mr r30, r3
/* 80367F64 00364B44  FC 20 F8 90 */	fmr f1, f31
/* 80367F68 00364B48  4B FB A9 59 */	bl __cvt_fp2unsigned
/* 80367F6C 00364B4C  7C 7F 1B 78 */	mr r31, r3
/* 80367F70 00364B50  FC 20 F0 90 */	fmr f1, f30
/* 80367F74 00364B54  4B FB A9 4D */	bl __cvt_fp2unsigned
/* 80367F78 00364B58  38 9F 00 00 */	addi r4, r31, 0
/* 80367F7C 00364B5C  38 BE 00 00 */	addi r5, r30, 0
/* 80367F80 00364B60  38 DD 00 00 */	addi r6, r29, 0
/* 80367F84 00364B64  4B FD 97 D9 */	bl GXSetScissor
/* 80367F88 00364B68  A0 7C 00 06 */	lhz r3, 6(r28)
/* 80367F8C 00364B6C  3C 00 43 30 */	lis r0, 0x4330
/* 80367F90 00364B70  C8 62 EA A0 */	lfd f3, HSD_CObj_804DE480(r2)
/* 80367F94 00364B74  90 61 00 54 */	stw r3, 0x54(r1)
/* 80367F98 00364B78  C0 DA 00 18 */	lfs f6, 0x18(r26)
/* 80367F9C 00364B7C  90 01 00 50 */	stw r0, 0x50(r1)
/* 80367FA0 00364B80  C0 5A 00 14 */	lfs f2, 0x14(r26)
/* 80367FA4 00364B84  C8 01 00 50 */	lfd f0, 0x50(r1)
/* 80367FA8 00364B88  C0 3A 00 0C */	lfs f1, 0xc(r26)
/* 80367FAC 00364B8C  EC 00 18 28 */	fsubs f0, f0, f3
/* 80367FB0 00364B90  C0 FA 00 10 */	lfs f7, 0x10(r26)
/* 80367FB4 00364B94  FC 06 00 40 */	fcmpo cr0, f6, f0
/* 80367FB8 00364B98  40 80 00 0C */	bge lbl_80367FC4
/* 80367FBC 00364B9C  FC 00 30 90 */	fmr f0, f6
/* 80367FC0 00364BA0  48 00 00 14 */	b lbl_80367FD4
lbl_80367FC4:
/* 80367FC4 00364BA4  90 61 00 54 */	stw r3, 0x54(r1)
/* 80367FC8 00364BA8  90 01 00 50 */	stw r0, 0x50(r1)
/* 80367FCC 00364BAC  C8 01 00 50 */	lfd f0, 0x50(r1)
/* 80367FD0 00364BB0  EC 00 18 28 */	fsubs f0, f0, f3
lbl_80367FD4:
/* 80367FD4 00364BB4  EC 80 10 28 */	fsubs f4, f0, f2
/* 80367FD8 00364BB8  C0 A2 EA 98 */	lfs f5, HSD_CObj_804DE478
/* 80367FDC 00364BBC  EC 06 10 28 */	fsubs f0, f6, f2
/* 80367FE0 00364BC0  C0 C2 EA 9C */	lfs f6, HSD_CObj_804DE47C(r2)
/* 80367FE4 00364BC4  EC 67 08 28 */	fsubs f3, f7, f1
/* 80367FE8 00364BC8  EF E4 00 24 */	fdivs f31, f4, f0
/* 80367FEC 00364BCC  4B FD 97 01 */	bl GXSetViewport
/* 80367FF0 00364BD0  88 1A 00 50 */	lbz r0, 0x50(r26)
/* 80367FF4 00364BD4  2C 00 00 02 */	cmpwi r0, 2
/* 80367FF8 00364BD8  41 82 00 74 */	beq lbl_8036806C
/* 80367FFC 00364BDC  40 80 00 10 */	bge lbl_8036800C
/* 80368000 00364BE0  2C 00 00 01 */	cmpwi r0, 1
/* 80368004 00364BE4  40 80 00 14 */	bge lbl_80368018
/* 80368008 00364BE8  48 00 00 C0 */	b lbl_803680C8
lbl_8036800C:
/* 8036800C 00364BEC  2C 00 00 04 */	cmpwi r0, 4
/* 80368010 00364BF0  40 80 00 B8 */	bge lbl_803680C8
/* 80368014 00364BF4  48 00 00 88 */	b lbl_8036809C
lbl_80368018:
/* 80368018 00364BF8  C8 22 EA 88 */	lfd f1, 0.5
/* 8036801C 00364BFC  3B 60 00 00 */	li r27, 0
/* 80368020 00364C00  C0 1A 00 40 */	lfs f0, 0x40(r26)
/* 80368024 00364C04  C8 42 EA A8 */	lfd f2, HSD_CObj_804DE488(r2)
/* 80368028 00364C08  FC 01 00 32 */	fmul f0, f1, f0
/* 8036802C 00364C0C  FC 22 00 32 */	fmul f1, f2, f0
/* 80368030 00364C10  FC 20 08 18 */	frsp f1, f1
/* 80368034 00364C14  4B FB E1 89 */	bl tanf
/* 80368038 00364C18  C0 BA 00 38 */	lfs f5, 0x38(r26)
/* 8036803C 00364C1C  38 61 00 10 */	addi r3, r1, 0x10
/* 80368040 00364C20  C0 42 EA B0 */	lfs f2, HSD_CObj_804DE490(r2)
/* 80368044 00364C24  EC 25 00 72 */	fmuls f1, f5, f1
/* 80368048 00364C28  C0 02 EA 9C */	lfs f0, HSD_CObj_804DE47C(r2)
/* 8036804C 00364C2C  C0 7A 00 44 */	lfs f3, 0x44(r26)
/* 80368050 00364C30  EC 02 07 FC */	fnmsubs f0, f2, f31, f0
/* 80368054 00364C34  C0 DA 00 3C */	lfs f6, 0x3c(r26)
/* 80368058 00364C38  EC 81 00 F2 */	fmuls f4, f1, f3
/* 8036805C 00364C3C  EC 41 00 32 */	fmuls f2, f1, f0
/* 80368060 00364C40  FC 60 20 50 */	fneg f3, f4
/* 80368064 00364C44  4B FD AA ED */	bl C_MTXFrustum
/* 80368068 00364C48  48 00 00 60 */	b lbl_803680C8
lbl_8036806C:
/* 8036806C 00364C4C  C0 3A 00 40 */	lfs f1, 0x40(r26)
/* 80368070 00364C50  38 61 00 10 */	addi r3, r1, 0x10
/* 80368074 00364C54  C0 1A 00 44 */	lfs f0, 0x44(r26)
/* 80368078 00364C58  3B 60 00 00 */	li r27, 0
/* 8036807C 00364C5C  C0 7A 00 48 */	lfs f3, 0x48(r26)
/* 80368080 00364C60  EC 01 00 28 */	fsubs f0, f1, f0
/* 80368084 00364C64  C0 9A 00 4C */	lfs f4, 0x4c(r26)
/* 80368088 00364C68  C0 BA 00 38 */	lfs f5, 0x38(r26)
/* 8036808C 00364C6C  C0 DA 00 3C */	lfs f6, 0x3c(r26)
/* 80368090 00364C70  EC 5F 08 3C */	fnmsubs f2, f31, f0, f1
/* 80368094 00364C74  4B FD AA BD */	bl C_MTXFrustum
/* 80368098 00364C78  48 00 00 30 */	b lbl_803680C8
lbl_8036809C:
/* 8036809C 00364C7C  C0 3A 00 40 */	lfs f1, 0x40(r26)
/* 803680A0 00364C80  38 61 00 10 */	addi r3, r1, 0x10
/* 803680A4 00364C84  C0 1A 00 44 */	lfs f0, 0x44(r26)
/* 803680A8 00364C88  3B 60 00 01 */	li r27, 1
/* 803680AC 00364C8C  C0 7A 00 48 */	lfs f3, 0x48(r26)
/* 803680B0 00364C90  EC 01 00 28 */	fsubs f0, f1, f0
/* 803680B4 00364C94  C0 9A 00 4C */	lfs f4, 0x4c(r26)
/* 803680B8 00364C98  C0 BA 00 38 */	lfs f5, 0x38(r26)
/* 803680BC 00364C9C  C0 DA 00 3C */	lfs f6, 0x3c(r26)
/* 803680C0 00364CA0  EC 5F 08 3C */	fnmsubs f2, f31, f0, f1
/* 803680C4 00364CA4  4B FD AB F9 */	bl C_MTXOrtho
lbl_803680C8:
/* 803680C8 00364CA8  38 61 00 10 */	addi r3, r1, 0x10
/* 803680CC 00364CAC  38 9B 00 00 */	addi r4, r27, 0
/* 803680D0 00364CB0  4B FD 91 ED */	bl GXSetProjection
/* 803680D4 00364CB4  38 60 00 01 */	li r3, 1
lbl_803680D8:
/* 803680D8 00364CB8  BB 41 00 58 */	lmw r26, 0x58(r1)
/* 803680DC 00364CBC  80 01 00 8C */	lwz r0, 0x8c(r1)
/* 803680E0 00364CC0  CB E1 00 80 */	lfd f31, 0x80(r1)
/* 803680E4 00364CC4  CB C1 00 78 */	lfd f30, 0x78(r1)
/* 803680E8 00364CC8  CB A1 00 70 */	lfd f29, 0x70(r1)
/* 803680EC 00364CCC  38 21 00 88 */	addi r1, r1, 0x88
/* 803680F0 00364CD0  7C 08 03 A6 */	mtlr r0
/* 803680F4 00364CD4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

int setupTopHalfCamera(HSD_CObj* cobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    int unused[3];
#endif

    GXProjectionType projection_type;
    Mtx p;

    f32 h_scale;
    f32 t;
    f32 b;
    f32 w;

    f32 top;
    f32 bottom;
    f32 left;
    f32 right;

    f32 width;
    f32 height;

    GXRenderModeObj* rmode = HSD_VIGetRenderMode();

    if (cobj->viewport.top >= rmode->efbHeight) {
        return 0;
    }
    left = cobj->viewport.left;
    right = cobj->viewport.right;
    top = cobj->viewport.top;
    bottom = bottom = cobj->viewport.bottom;
    bottom = bottom < rmode->efbHeight ? bottom : rmode->efbHeight;
    width = right - left;
    height = bottom - top;
    GXSetScissor((u32) left, (u32) top, (u32) width, (u32) height);
    top = cobj->viewport.top;
    bottom = cobj->viewport.bottom;
    left = cobj->viewport.left;
    right = cobj->viewport.right;
    height = (bottom < rmode->efbHeight ? bottom : rmode->efbHeight) - top;
    h_scale = height / (bottom - top);
    width = right - left;

    GXSetViewport(left, top, width, height, 0.0f, 1.0f);

    {
        /// @todo Unused stack.
#ifdef MUST_MATCH
        int unused[1];
#endif

        switch (cobj->projection_type) {
        case PROJ_PERSPECTIVE:
            projection_type = GX_PERSPECTIVE;
            t = cobj->near *
                tanf(HSD_CObj_804DE488 *
                     (0.5 * cobj->projection_param.perspective.fov));
            w = t * cobj->projection_param.perspective.aspect;
            b = t * -(HSD_CObj_804DE490 * h_scale - HSD_CObj_804DE47C);
            C_MTXFrustum(p, t, b, -w, w, cobj->near, cobj->far);
            break;
        case PROJ_FRUSTUM:
            projection_type = GX_PERSPECTIVE;
            C_MTXFrustum(
                p, cobj->projection_param.perspective.fov,
                -(h_scale * (cobj->projection_param.perspective.fov -
                             cobj->projection_param.perspective.aspect) -
                  cobj->projection_param.perspective.fov),
                cobj->projection_param.frustum.left,
                cobj->projection_param.frustum.right, cobj->near, cobj->far);
            break;
        case PROJ_ORTHO:
            projection_type = GX_ORTHOGRAPHIC;
            C_MTXOrtho(
                p, cobj->projection_param.perspective.fov,
                -(h_scale * (cobj->projection_param.perspective.fov -
                             cobj->projection_param.perspective.aspect) -
                  cobj->projection_param.perspective.fov),
                cobj->projection_param.frustum.left,
                cobj->projection_param.frustum.right, cobj->near, cobj->far);
            break;
        }
    }

    GXSetProjection(p, projection_type);

    return 1;
}

#endif

#ifdef MUST_MATCH
#pragma push
asm int setupBottomHalfCamera()
{ // clang-format off
    nofralloc
/* 803680F8 00364CD8  7C 08 02 A6 */	mflr r0
/* 803680FC 00364CDC  3C 80 80 4C */	lis r4, HSD_VIData@ha
/* 80368100 00364CE0  90 01 00 04 */	stw r0, 4(r1)
/* 80368104 00364CE4  38 84 1D 80 */	addi r4, r4, HSD_VIData@l
/* 80368108 00364CE8  94 21 FF 58 */	stwu r1, -0xa8(r1)
/* 8036810C 00364CEC  DB E1 00 A0 */	stfd f31, 0xa0(r1)
/* 80368110 00364CF0  DB C1 00 98 */	stfd f30, 0x98(r1)
/* 80368114 00364CF4  DB A1 00 90 */	stfd f29, 0x90(r1)
/* 80368118 00364CF8  BF 21 00 74 */	stmw r25, 0x74(r1)
/* 8036811C 00364CFC  3B C3 00 00 */	addi r30, r3, 0
/* 80368120 00364D00  A0 A4 00 06 */	lhz r5, 6(r4)
/* 80368124 00364D04  3C 80 43 30 */	lis r4, 0x4330
/* 80368128 00364D08  C8 42 EA A0 */	lfd f2, HSD_CObj_804DE480(r2)
/* 8036812C 00364D0C  38 05 FF F8 */	addi r0, r5, -8
/* 80368130 00364D10  C0 23 00 18 */	lfs f1, 0x18(r3)
/* 80368134 00364D14  90 01 00 6C */	stw r0, 0x6c(r1)
/* 80368138 00364D18  7C 19 03 78 */	mr r25, r0
/* 8036813C 00364D1C  90 81 00 68 */	stw r4, 0x68(r1)
/* 80368140 00364D20  C8 01 00 68 */	lfd f0, 0x68(r1)
/* 80368144 00364D24  EC 00 10 28 */	fsubs f0, f0, f2
/* 80368148 00364D28  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8036814C 00364D2C  40 80 00 0C */	bge lbl_80368158
/* 80368150 00364D30  38 60 00 00 */	li r3, 0
/* 80368154 00364D34  48 00 02 30 */	b lbl_80368384
lbl_80368158:
/* 80368158 00364D38  A0 7E 00 1C */	lhz r3, 0x1c(r30)
/* 8036815C 00364D3C  A0 1E 00 1E */	lhz r0, 0x1e(r30)
/* 80368160 00364D40  90 61 00 6C */	stw r3, 0x6c(r1)
/* 80368164 00364D44  A0 7E 00 20 */	lhz r3, 0x20(r30)
/* 80368168 00364D48  90 01 00 64 */	stw r0, 0x64(r1)
/* 8036816C 00364D4C  7C 03 C8 40 */	cmplw r3, r25
/* 80368170 00364D50  90 81 00 68 */	stw r4, 0x68(r1)
/* 80368174 00364D54  90 81 00 60 */	stw r4, 0x60(r1)
/* 80368178 00364D58  C8 21 00 68 */	lfd f1, 0x68(r1)
/* 8036817C 00364D5C  C8 01 00 60 */	lfd f0, 0x60(r1)
/* 80368180 00364D60  EF C1 10 28 */	fsubs f30, f1, f2
/* 80368184 00364D64  EC 00 10 28 */	fsubs f0, f0, f2
/* 80368188 00364D68  40 81 00 08 */	ble lbl_80368190
/* 8036818C 00364D6C  48 00 00 08 */	b lbl_80368194
lbl_80368190:
/* 80368190 00364D70  7F 23 CB 78 */	mr r3, r25
lbl_80368194:
/* 80368194 00364D74  A0 1E 00 22 */	lhz r0, 0x22(r30)
/* 80368198 00364D78  7C 79 18 50 */	subf r3, r25, r3
/* 8036819C 00364D7C  90 61 00 64 */	stw r3, 0x64(r1)
/* 803681A0 00364D80  3F 40 43 30 */	lis r26, 0x4330
/* 803681A4 00364D84  7C 19 00 50 */	subf r0, r25, r0
/* 803681A8 00364D88  90 01 00 6C */	stw r0, 0x6c(r1)
/* 803681AC 00364D8C  EF A0 F0 28 */	fsubs f29, f0, f30
/* 803681B0 00364D90  C8 42 EA A0 */	lfd f2, HSD_CObj_804DE480(r2)
/* 803681B4 00364D94  93 41 00 60 */	stw r26, 0x60(r1)
/* 803681B8 00364D98  93 41 00 68 */	stw r26, 0x68(r1)
/* 803681BC 00364D9C  C8 21 00 60 */	lfd f1, 0x60(r1)
/* 803681C0 00364DA0  C8 01 00 68 */	lfd f0, 0x68(r1)
/* 803681C4 00364DA4  EF E1 10 28 */	fsubs f31, f1, f2
/* 803681C8 00364DA8  EC 00 10 28 */	fsubs f0, f0, f2
/* 803681CC 00364DAC  EC 20 F8 28 */	fsubs f1, f0, f31
/* 803681D0 00364DB0  4B FB A6 F1 */	bl __cvt_fp2unsigned
/* 803681D4 00364DB4  7C 7B 1B 78 */	mr r27, r3
/* 803681D8 00364DB8  FC 20 E8 90 */	fmr f1, f29
/* 803681DC 00364DBC  4B FB A6 E5 */	bl __cvt_fp2unsigned
/* 803681E0 00364DC0  7C 7C 1B 78 */	mr r28, r3
/* 803681E4 00364DC4  FC 20 F8 90 */	fmr f1, f31
/* 803681E8 00364DC8  4B FB A6 D9 */	bl __cvt_fp2unsigned
/* 803681EC 00364DCC  7C 7D 1B 78 */	mr r29, r3
/* 803681F0 00364DD0  FC 20 F0 90 */	fmr f1, f30
/* 803681F4 00364DD4  4B FB A6 CD */	bl __cvt_fp2unsigned
/* 803681F8 00364DD8  38 9D 00 00 */	addi r4, r29, 0
/* 803681FC 00364DDC  38 BC 00 00 */	addi r5, r28, 0
/* 80368200 00364DE0  38 DB 00 00 */	addi r6, r27, 0
/* 80368204 00364DE4  4B FD 95 59 */	bl GXSetScissor
/* 80368208 00364DE8  93 21 00 5C */	stw r25, 0x5c(r1)
/* 8036820C 00364DEC  C8 42 EA A0 */	lfd f2, HSD_CObj_804DE480(r2)
/* 80368210 00364DF0  93 41 00 58 */	stw r26, 0x58(r1)
/* 80368214 00364DF4  C0 9E 00 14 */	lfs f4, 0x14(r30)
/* 80368218 00364DF8  C8 01 00 58 */	lfd f0, 0x58(r1)
/* 8036821C 00364DFC  C0 3E 00 0C */	lfs f1, 0xc(r30)
/* 80368220 00364E00  EC 00 10 28 */	fsubs f0, f0, f2
/* 80368224 00364E04  C0 7E 00 10 */	lfs f3, 0x10(r30)
/* 80368228 00364E08  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8036822C 00364E0C  40 81 00 0C */	ble lbl_80368238
/* 80368230 00364E10  FD 20 20 90 */	fmr f9, f4
/* 80368234 00364E14  48 00 00 14 */	b lbl_80368248
lbl_80368238:
/* 80368238 00364E18  93 21 00 5C */	stw r25, 0x5c(r1)
/* 8036823C 00364E1C  93 41 00 58 */	stw r26, 0x58(r1)
/* 80368240 00364E20  C8 01 00 58 */	lfd f0, 0x58(r1)
/* 80368244 00364E24  ED 20 10 28 */	fsubs f9, f0, f2
lbl_80368248:
/* 80368248 00364E28  93 21 00 5C */	stw r25, 0x5c(r1)
/* 8036824C 00364E2C  3C 00 43 30 */	lis r0, 0x4330
/* 80368250 00364E30  C1 5E 00 18 */	lfs f10, 0x18(r30)
/* 80368254 00364E34  EC 63 08 28 */	fsubs f3, f3, f1
/* 80368258 00364E38  93 21 00 64 */	stw r25, 0x64(r1)
/* 8036825C 00364E3C  C9 02 EA A0 */	lfd f8, HSD_CObj_804DE480(r2)
/* 80368260 00364E40  EC 0A 20 28 */	fsubs f0, f10, f4
/* 80368264 00364E44  90 01 00 58 */	stw r0, 0x58(r1)
/* 80368268 00364E48  C0 A2 EA 98 */	lfs f5, HSD_CObj_804DE478
/* 8036826C 00364E4C  90 01 00 60 */	stw r0, 0x60(r1)
/* 80368270 00364E50  C8 81 00 58 */	lfd f4, 0x58(r1)
/* 80368274 00364E54  C8 41 00 60 */	lfd f2, 0x60(r1)
/* 80368278 00364E58  EC E4 40 28 */	fsubs f7, f4, f8
/* 8036827C 00364E5C  C0 C2 EA 9C */	lfs f6, HSD_CObj_804DE47C(r2)
/* 80368280 00364E60  EC 82 40 28 */	fsubs f4, f2, f8
/* 80368284 00364E64  EC 49 38 28 */	fsubs f2, f9, f7
/* 80368288 00364E68  EC 8A 20 28 */	fsubs f4, f10, f4
/* 8036828C 00364E6C  EC 84 10 28 */	fsubs f4, f4, f2
/* 80368290 00364E70  EF A4 00 24 */	fdivs f29, f4, f0
/* 80368294 00364E74  4B FD 94 59 */	bl GXSetViewport
/* 80368298 00364E78  88 1E 00 50 */	lbz r0, 0x50(r30)
/* 8036829C 00364E7C  2C 00 00 02 */	cmpwi r0, 2
/* 803682A0 00364E80  41 82 00 78 */	beq lbl_80368318
/* 803682A4 00364E84  40 80 00 10 */	bge lbl_803682B4
/* 803682A8 00364E88  2C 00 00 01 */	cmpwi r0, 1
/* 803682AC 00364E8C  40 80 00 14 */	bge lbl_803682C0
/* 803682B0 00364E90  48 00 00 C4 */	b lbl_80368374
lbl_803682B4:
/* 803682B4 00364E94  2C 00 00 04 */	cmpwi r0, 4
/* 803682B8 00364E98  40 80 00 BC */	bge lbl_80368374
/* 803682BC 00364E9C  48 00 00 8C */	b lbl_80368348
lbl_803682C0:
/* 803682C0 00364EA0  C8 22 EA 88 */	lfd f1, 0.5
/* 803682C4 00364EA4  3B E0 00 00 */	li r31, 0
/* 803682C8 00364EA8  C0 1E 00 40 */	lfs f0, 0x40(r30)
/* 803682CC 00364EAC  C8 42 EA A8 */	lfd f2, HSD_CObj_804DE488(r2)
/* 803682D0 00364EB0  FC 01 00 32 */	fmul f0, f1, f0
/* 803682D4 00364EB4  FC 22 00 32 */	fmul f1, f2, f0
/* 803682D8 00364EB8  FC 20 08 18 */	frsp f1, f1
/* 803682DC 00364EBC  4B FB DE E1 */	bl tanf
/* 803682E0 00364EC0  C0 BE 00 38 */	lfs f5, 0x38(r30)
/* 803682E4 00364EC4  38 61 00 14 */	addi r3, r1, 0x14
/* 803682E8 00364EC8  C0 42 EA B0 */	lfs f2, HSD_CObj_804DE490(r2)
/* 803682EC 00364ECC  EC 65 00 72 */	fmuls f3, f5, f1
/* 803682F0 00364ED0  C0 02 EA B4 */	lfs f0, HSD_CObj_804DE494(r2)
/* 803682F4 00364ED4  C0 3E 00 44 */	lfs f1, 0x44(r30)
/* 803682F8 00364ED8  EC 02 07 7A */	fmadds f0, f2, f29, f0
/* 803682FC 00364EDC  C0 DE 00 3C */	lfs f6, 0x3c(r30)
/* 80368300 00364EE0  EC 83 00 72 */	fmuls f4, f3, f1
/* 80368304 00364EE4  FC 40 18 50 */	fneg f2, f3
/* 80368308 00364EE8  EC 23 00 32 */	fmuls f1, f3, f0
/* 8036830C 00364EEC  FC 60 20 50 */	fneg f3, f4
/* 80368310 00364EF0  4B FD A8 41 */	bl C_MTXFrustum
/* 80368314 00364EF4  48 00 00 60 */	b lbl_80368374
lbl_80368318:
/* 80368318 00364EF8  C0 5E 00 44 */	lfs f2, 0x44(r30)
/* 8036831C 00364EFC  38 61 00 14 */	addi r3, r1, 0x14
/* 80368320 00364F00  C0 1E 00 40 */	lfs f0, 0x40(r30)
/* 80368324 00364F04  3B E0 00 00 */	li r31, 0
/* 80368328 00364F08  C0 7E 00 48 */	lfs f3, 0x48(r30)
/* 8036832C 00364F0C  EC 00 10 28 */	fsubs f0, f0, f2
/* 80368330 00364F10  C0 9E 00 4C */	lfs f4, 0x4c(r30)
/* 80368334 00364F14  C0 BE 00 38 */	lfs f5, 0x38(r30)
/* 80368338 00364F18  C0 DE 00 3C */	lfs f6, 0x3c(r30)
/* 8036833C 00364F1C  EC 3D 10 3A */	fmadds f1, f29, f0, f2
/* 80368340 00364F20  4B FD A8 11 */	bl C_MTXFrustum
/* 80368344 00364F24  48 00 00 30 */	b lbl_80368374
lbl_80368348:
/* 80368348 00364F28  C0 5E 00 44 */	lfs f2, 0x44(r30)
/* 8036834C 00364F2C  38 61 00 14 */	addi r3, r1, 0x14
/* 80368350 00364F30  C0 1E 00 40 */	lfs f0, 0x40(r30)
/* 80368354 00364F34  3B E0 00 01 */	li r31, 1
/* 80368358 00364F38  C0 7E 00 48 */	lfs f3, 0x48(r30)
/* 8036835C 00364F3C  EC 00 10 28 */	fsubs f0, f0, f2
/* 80368360 00364F40  C0 9E 00 4C */	lfs f4, 0x4c(r30)
/* 80368364 00364F44  C0 BE 00 38 */	lfs f5, 0x38(r30)
/* 80368368 00364F48  C0 DE 00 3C */	lfs f6, 0x3c(r30)
/* 8036836C 00364F4C  EC 3D 10 3A */	fmadds f1, f29, f0, f2
/* 80368370 00364F50  4B FD A9 4D */	bl C_MTXOrtho
lbl_80368374:
/* 80368374 00364F54  38 61 00 14 */	addi r3, r1, 0x14
/* 80368378 00364F58  38 9F 00 00 */	addi r4, r31, 0
/* 8036837C 00364F5C  4B FD 8F 41 */	bl GXSetProjection
/* 80368380 00364F60  38 60 00 01 */	li r3, 1
lbl_80368384:
/* 80368384 00364F64  BB 21 00 74 */	lmw r25, 0x74(r1)
/* 80368388 00364F68  80 01 00 AC */	lwz r0, 0xac(r1)
/* 8036838C 00364F6C  CB E1 00 A0 */	lfd f31, 0xa0(r1)
/* 80368390 00364F70  CB C1 00 98 */	lfd f30, 0x98(r1)
/* 80368394 00364F74  CB A1 00 90 */	lfd f29, 0x90(r1)
/* 80368398 00364F78  38 21 00 A8 */	addi r1, r1, 0xa8
/* 8036839C 00364F7C  7C 08 03 A6 */	mtlr r0
/* 803683A0 00364F80  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

inline void HSD_WObjClearFlags(HSD_WObj* wobj, u32 flags)
{
    wobj->flags &= ~flags;
}

void HSD_CObjSetupViewingMtx(HSD_CObj* cobj)
{
    Vec3 eyepos;
    Vec3 up_vec;
    Vec3 interest;

    if (!(cobj->flags & 2) && HSD_CObjMtxIsDirty(cobj)) {
        HSD_CObjGetEyePosition(cobj, &eyepos);
        HSD_CObjGetUpVector(cobj, &up_vec);
        HSD_CObjGetInterest(cobj, &interest);
        C_MTXLookAt(cobj->view_mtx, &eyepos, &up_vec, &interest);
        HSD_WObjClearFlags(cobj->eyepos, 2);
        HSD_WObjClearFlags(cobj->interest, 2);
        HSD_CObjClearFlags(cobj, 0x40000000);
        HSD_CObjSetFlags(cobj, 0x80000000);
    }
}

static char HSD_CObj_804D5D40[7] = "cobj.c";
static char HSD_CObj_80406294[] = "unkown type of render pass.\n";

static void setNewProjection(HSD_CObj* cobj, Mtx44 mtx)
{
    GXSetProjection(mtx, makeProjectionMtx(cobj, mtx));
}

bool HSD_CObjSetCurrent(HSD_CObj* cobj)
{
    HSD_RenderPass render_pass;
    bool result;

    if (cobj == NULL) {
        return false;
    }
    render_pass = HSD_GetCurrentRenderPass();
    _HSD_ZListClear();
    current = cobj;
    switch (render_pass) {
    case HSD_RP_OFFSCREEN:
        result = setupOffscreenCamera(cobj);
        break;
    case HSD_RP_SCREEN:
        result = setupNormalCamera(cobj);
        break;
    case HSD_RP_TOPHALF:
        result = setupTopHalfCamera(cobj);
        break;
    case HSD_RP_BOTTOMHALF:
        result = setupBottomHalfCamera(cobj);
        break;
    default:
        HSD_Panic(HSD_CObj_804D5D40,
                  //"cobj.c",
                  0x270, HSD_CObj_80406294);
        //"unkown type of render pass.\n");
        return false;
    }
    if (!result) {
        return false;
    } else {
        HSD_CObjSetupViewingMtx(cobj);
        return true;
    }
}

void HSD_CObjEndCurrent(void)
{
    _HSD_ZListSort();
    _HSD_ZListDisp();
}

#define HSD_ASSERT3(line, msg, cond)                                          \
    ((cond) ? (void) 0 : __assert(HSD_CObj_804D5D40, line, msg))

#define HSD_ASSERT4(line, cond)                                               \
    ((cond) ? (void) 0 : __assert(HSD_CObj_804D5D40, line, #cond))

char HSD_CObj_804D5D48[8] = "cobj";

HSD_WObj* HSD_CObjGetInterestWObj(HSD_CObj* cobj)
{
    HSD_ASSERT3(0x295, HSD_CObj_804D5D48, cobj);
    return cobj->interest;
}

HSD_WObj* HSD_CObjGetEyePositionWObj(HSD_CObj* cobj)
{
    HSD_ASSERT3(0x2AD, HSD_CObj_804D5D48, cobj);
    return cobj->eyepos;
}

void HSD_CObjGetInterest(HSD_CObj* cobj, Vec3* interest)
{
    HSD_ASSERT3(0x2C5, HSD_CObj_804D5D48, cobj);
    HSD_WObjGetPosition(HSD_CObjGetInterestWObj(cobj), interest);
}

void HSD_CObjSetInterest(HSD_CObj* cobj, Vec3* interest)
{
    HSD_ASSERT3(0x2D1, HSD_CObj_804D5D48, cobj);
    HSD_WObjSetPosition(HSD_CObjGetInterestWObj(cobj), interest);
}

void HSD_CObjGetEyePosition(HSD_CObj* cobj, Vec3* position)
{
    HSD_ASSERT3(0x2DD, HSD_CObj_804D5D48, cobj);
    HSD_WObjGetPosition(HSD_CObjGetEyePositionWObj(cobj), position);
}

void HSD_CObjSetEyePosition(HSD_CObj* cobj, Vec3* position)
{
    HSD_ASSERT3(0x2E9, HSD_CObj_804D5D48, cobj);
    HSD_WObjSetPosition(HSD_CObjGetEyePositionWObj(cobj), position);
}

static inline float fabsf(float x)
{
    *(u32*) &x &= 0x7FFFFFFF;
    return x;
}

extern float HSD_CObj_804DE498;
#define FLT_MIN HSD_CObj_804DE498

static inline int _vec_normalize_check(Vec3* src, Vec3* dst)
{
    if (src == NULL || dst == NULL) {
        return -1;
    }
    if (fabsf(src->x) <= FLT_MIN && fabsf(src->y) <= FLT_MIN &&
        fabsf(src->z) <= FLT_MIN)
    {
        return -1;
    } else {
        PSVECNormalize(src, dst);
        return 0;
    }
}

int HSD_CObjGetEyeVector(HSD_CObj* cobj, Vec3* eye)
{
    Vec3 sp48;
    Vec3 sp3C;

    if (cobj != NULL && cobj->eyepos != NULL && cobj->interest != NULL &&
        eye != NULL)
    {
        HSD_CObjGetEyePosition(cobj, &sp48);
        HSD_CObjGetInterest(cobj, &sp3C);
        PSVECSubtract(&sp3C, &sp48, eye);
        if (_vec_normalize_check(eye, eye) == 0) {
            return 0;
        }
    }
    if (eye != NULL) {
        eye->y = eye->x = HSD_CObj_804DE478;
        eye->z = HSD_CObj_804DE494;
    }
    return -1;
}

float HSD_CObjGetEyeDistance(HSD_CObj* cobj)
{
    Vec3 position;
    Vec3 interest;
    Vec3 look_vector;

    if (cobj == NULL) {
        return HSD_CObj_804DE478;
    }
    HSD_ASSERT4(0x327, cobj->eyepos);
    HSD_ASSERT4(0x328, cobj->interest);
    HSD_CObjGetEyePosition(cobj, &position);
    HSD_CObjGetInterest(cobj, &interest);
    PSVECSubtract(&interest, &position, &look_vector);
    return PSVECMag(&look_vector);
}

#ifndef BUGFIX
#pragma push
#pragma force_active on
static float unused1[] = {
    0.0F, 0.0F, 0.0F,

    0.0F, 1.0F, 0.0F,

    0.0F, 1.0F, 0.0F,
};

static char unused2[] = "hsdIsDescendantOf(info, &hsdCObj)";
#pragma pop
#endif

int vec_normalize_check(Vec3* src, Vec3* dst);

int vec_normalize_check(Vec3* src, Vec3* dst)
{
    return _vec_normalize_check(src, dst);
}

int roll2upvec(HSD_CObj* cobj, Vec3* up, float roll);

extern const f64 HSD_CObj_804DE4B0;
extern const f64 HSD_CObj_804DE4B8;
extern const f64 HSD_CObj_804DE4C0;

int roll2upvec(HSD_CObj* cobj, Vec3* up, float roll)
{
    Vec3 sp88;
    Vec3 sp7C;
    Vec3 sp70;
    Mtx sp40;
    float var_f4;
    s32 var_r3;

    var_r3 = HSD_CObjGetEyeVector(cobj, &sp88);
    if (var_r3 != 0) {
        return var_r3;
    }

    if (HSD_CObj_804DE4B0 - __fabs(sp88.y) < HSD_CObj_804DE4B8) {
        var_f4 = sqrtf(sp88.y * sp88.y + sp88.z * sp88.z);
        sp7C.x = var_f4;
        sp7C.y = sp88.y * (-sp88.x / sp7C.x);
        sp7C.z = sp88.z * (-sp88.x / sp7C.x);
    } else {
        var_f4 = sqrtf(sp88.x * sp88.x + sp88.z * sp88.z);
        sp7C.y = var_f4;
        sp7C.x = sp88.x * (-sp88.y / sp7C.y);
        sp7C.z = sp88.z * (-sp88.y / sp7C.y);
    }
    PSMTXRotAxisRad(sp40, &sp88, -roll);
    PSMTXMultVecSR(sp40, &sp7C, &sp70);
    PSVECNormalize(&sp70, up);
    return 0;
}

void HSD_CObjGetUpVector(HSD_CObj* cobj, Vec3* up)
{
    NOT_IMPLEMENTED;
}

void HSD_CObjSetUpVector(void)
{
    NOT_IMPLEMENTED;
}

void HSD_CObjGetLeftVector(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

void HSD_CObjSetMtxDirty(HSD_CObj* cobj)
{
    cobj->flags |= (1 << 30) | (1 << 31);
}

bool HSD_CObjMtxIsDirty(HSD_CObj* cobj)
{
    return (cobj->flags & (1 << 30)) ||
           (cobj->eyepos != NULL && (cobj->eyepos->flags & 2)) ||
           (cobj->interest != NULL && (cobj->interest->flags & 2));
}

void HSD_CObjGetViewingMtx(HSD_CObj* cobj, Mtx mtx)
{
    PSMTXCopy(HSD_CObjGetViewingMtxPtr(cobj), mtx);
}

MtxPtr HSD_CObjGetInvViewingMtxPtrDirect(HSD_CObj* cobj)
{
    if (cobj->flags & (1 << 31)) {
        if (cobj->proj_mtx == NULL) {
            cobj->proj_mtx = HSD_MtxAlloc();
        }
        PSMTXInverse(cobj->view_mtx, *cobj->proj_mtx);
        HSD_CObjClearFlags(cobj, (1 << 31));
    }
    return *cobj->proj_mtx;
}

#define SOLUTION 1
MtxPtr HSD_CObjGetViewingMtxPtr(HSD_CObj* cobj)
{
#if SOLUTION == 0
    HSD_CObjSetupViewingMtx(cobj);
#elif SOLUTION == 1
    Vec3 interest;
    Vec3 up_vec;
    Vec3 eyepos;
    u32 unused[6];

    if (!(cobj->flags & 2) && HSD_CObjMtxIsDirty(cobj)) {
        HSD_CObjGetEyePosition(cobj, &eyepos);
        HSD_CObjGetUpVector(cobj, &up_vec);
        HSD_CObjGetInterest(cobj, &interest);
        C_MTXLookAt(cobj->view_mtx, &eyepos, &up_vec, &interest);
        HSD_WObjClearFlags(cobj->eyepos, 2);
        HSD_WObjClearFlags(cobj->interest, 2);
        HSD_CObjClearFlags(cobj, 0x40000000);
        HSD_CObjSetFlags(cobj, 0x80000000);
    }
#endif
    return cobj->view_mtx;
}
#undef SOLUTION

#define SOLUTION 1
MtxPtr HSD_CObjGetInvViewingMtxPtr(HSD_CObj* cobj)
{
#if SOLUTION == 0
    HSD_CObjGetViewingMtxPtr(cobj);
#elif SOLUTION == 1
    Vec3 interest;
    Vec3 up_vec;
    Vec3 eyepos;
    u32 unused[6];

    if (!(cobj->flags & 2) && HSD_CObjMtxIsDirty(cobj)) {
        HSD_CObjGetEyePosition(cobj, &eyepos);
        HSD_CObjGetUpVector(cobj, &up_vec);
        HSD_CObjGetInterest(cobj, &interest);
        C_MTXLookAt(cobj->view_mtx, &eyepos, &up_vec, &interest);
        HSD_WObjClearFlags(cobj->eyepos, 2);
        HSD_WObjClearFlags(cobj->interest, 2);
        HSD_CObjClearFlags(cobj, 0x40000000);
        HSD_CObjSetFlags(cobj, 0x80000000);
    }
#endif
    return HSD_CObjGetInvViewingMtxPtrDirect(cobj);
}
#undef SOLUTION

void HSD_CObjSetRoll(HSD_CObj* cobj, float arg1)
{
    NOT_IMPLEMENTED;
}

float HSD_CObjGetFov(HSD_CObj* cobj)
{
    if (cobj == NULL || cobj->projection_type != 1) {
        return HSD_CObj_804DE478;
    }
    return cobj->projection_param.perspective.fov;
}

void HSD_CObjSetFov(HSD_CObj* cobj, float fov)
{
    if (cobj == NULL || cobj->projection_type != 1) {
        return;
    }
    cobj->projection_param.perspective.fov = fov;
}

float HSD_CObjGetAspect(HSD_CObj* cobj)
{
    if (cobj == NULL || cobj->projection_type != 1) {
        return HSD_CObj_804DE478;
    }
    return cobj->projection_param.perspective.aspect;
}

void HSD_CObjSetAspect(HSD_CObj* cobj, float aspect)
{
    if (cobj == NULL || cobj->projection_type != 1) {
        return;
    }
    cobj->projection_param.perspective.aspect = aspect;
}

float HSD_CObjGetTop(HSD_CObj* cobj)
{
    float result;

    if (cobj == NULL) {
        return HSD_CObj_804DE478;
    }
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        result =
            cobj->near * tanf(0.5F * (HSD_CObj_804DE474 *
                                      cobj->projection_param.perspective.fov));
        break;
    case PROJ_FRUSTUM:
        result = cobj->projection_param.perspective.fov;
        break;
    case PROJ_ORTHO:
        result = cobj->projection_param.perspective.fov;
        break;
    default:
        result = HSD_CObj_804DE478;
        break;
    }
    return result;
}

void HSD_CObjSetTop(HSD_CObj* cobj, float top)
{
    if (cobj == NULL) {
        return;
    }
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        break;
    case PROJ_FRUSTUM:
        cobj->projection_param.frustum.top = top;
        break;
    case PROJ_ORTHO:
        cobj->projection_param.ortho.top = top;
        break;
    }
}

float HSD_CObjGetBottom(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return HSD_CObj_804DE478;
    }
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        return -cobj->near *
               tanf(0.5F * (HSD_CObj_804DE474 *
                            cobj->projection_param.perspective.fov));
    case PROJ_FRUSTUM:
        return cobj->projection_param.frustum.bottom;
    case PROJ_ORTHO:
        return cobj->projection_param.ortho.bottom;
    default:
        return HSD_CObj_804DE478;
    }
}

void HSD_CObjSetBottom(HSD_CObj* cobj, float bottom)
{
    if (cobj == NULL) {
        return;
    }
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        break;
    case PROJ_FRUSTUM:
        cobj->projection_param.frustum.bottom = bottom;
        break;
    case PROJ_ORTHO:
        cobj->projection_param.ortho.bottom = bottom;
        break;
    }
}

float HSD_CObjGetLeft(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return HSD_CObj_804DE478;
    }
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        return cobj->projection_param.perspective.aspect *
               (-cobj->near *
                tanf(0.5F * (HSD_CObj_804DE474 *
                             cobj->projection_param.perspective.fov)));
    case PROJ_FRUSTUM:
        return cobj->projection_param.frustum.left;
    case PROJ_ORTHO:
        return cobj->projection_param.ortho.left;
    default:
        return HSD_CObj_804DE478;
    }
}

void HSD_CObjSetLeft(HSD_CObj* cobj, float left)
{
    if (cobj == NULL) {
        return;
    }
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        break;
    case PROJ_FRUSTUM:
        cobj->projection_param.frustum.left = left;
        break;
    case PROJ_ORTHO:
        cobj->projection_param.ortho.left = left;
        break;
    }
}

float HSD_CObjGetRight(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return HSD_CObj_804DE478;
    }
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        return cobj->projection_param.perspective.aspect *
               (cobj->near *
                tanf(0.5F * (HSD_CObj_804DE474 *
                             cobj->projection_param.perspective.fov)));
    case PROJ_FRUSTUM:
        return cobj->projection_param.frustum.right;
    case PROJ_ORTHO:
        return cobj->projection_param.ortho.right;
    default:
        return HSD_CObj_804DE478;
    }
}

const float HSD_CObj_804DE474 = 0.01745329252F;

void HSD_CObjSetRight(HSD_CObj* cobj, float right)
{
    if (cobj == NULL) {
        return;
    }
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        break;
    case PROJ_FRUSTUM:
        cobj->projection_param.frustum.right = right;
        break;
    case PROJ_ORTHO:
        cobj->projection_param.ortho.right = right;
        break;
    }
}

float HSD_CObjGetNear(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return HSD_CObj_804DE478;
    }
    return cobj->near;
}

void HSD_CObjSetNear(HSD_CObj* cobj, float near)
{
    if (cobj != NULL) {
        cobj->near = near;
    }
}

float HSD_CObjGetFar(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return HSD_CObj_804DE478;
    }
    return cobj->far;
}

void HSD_CObjSetFar(HSD_CObj* cobj, float far)
{
    if (cobj != NULL) {
        cobj->far = far;
    }
}

void HSD_CObjGetScissor(HSD_CObj* cobj, struct Scissor* scissor)
{
    if (cobj == NULL) {
        return;
    }
    *scissor = cobj->scissor;
}

void HSD_CObjSetScissor(HSD_CObj* cobj, struct Scissor* scissor)
{
    if (cobj == NULL) {
        return;
    }
    cobj->scissor = *scissor;
}

void HSD_CObjSetScissorx4(HSD_CObj* cobj, u16 left, u16 right, u16 top,
                          u16 bottom)
{
    if (cobj == NULL) {
        return;
    }
    cobj->scissor.left = left;
    cobj->scissor.right = right;
    cobj->scissor.top = top;
    cobj->scissor.bottom = bottom;
}

void HSD_CObjGetViewportf(HSD_CObj* cobj, struct Viewport* viewport)
{
    if (cobj == NULL) {
        return;
    }
    *viewport = cobj->viewport;
}

extern const f64 HSD_CObj_804DE4C8;

// Uses s16 -> float cast literal
void HSD_CObjSetViewport(HSD_CObj* cobj, s16* viewport)
{
    if (cobj == NULL) {
        return;
    }
    cobj->viewport.left = viewport[0];
    cobj->viewport.right = viewport[1];
    cobj->viewport.top = viewport[2];
    cobj->viewport.bottom = viewport[3];
}

void HSD_CObjSetViewportf(HSD_CObj* cobj, struct Viewport* viewport)
{
    if (cobj == NULL) {
        return;
    }
    cobj->viewport = *viewport;
}

void HSD_CObjSetViewportfx4(HSD_CObj* cobj, float left, float right, float top,
                            float bottom)
{
    if (cobj == NULL) {
        return;
    }
    cobj->viewport.left = left;
    cobj->viewport.right = right;
    cobj->viewport.top = top;
    cobj->viewport.bottom = bottom;
}

u32 HSD_CObjGetProjectionType(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return 1;
    }
    return cobj->projection_type;
}

void HSD_CObjSetProjectionType(HSD_CObj* cobj, u32 proj_type)
{
    if (cobj == NULL) {
        return;
    }
    cobj->projection_type = proj_type;
}

void HSD_CObjSetPerspective(HSD_CObj* cobj, float fov, float aspect)
{
    if (cobj == NULL) {
        return;
    }
    cobj->projection_type = PROJ_PERSPECTIVE;
    cobj->projection_param.perspective.fov = fov;
    cobj->projection_param.perspective.aspect = aspect;
}

void HSD_CObjSetFrustum(HSD_CObj* cobj, float top, float bottom, float left,
                        float right)
{
    if (cobj == NULL) {
        return;
    }
    cobj->projection_type = PROJ_FRUSTUM;
    cobj->projection_param.frustum.top = top;
    cobj->projection_param.frustum.bottom = bottom;
    cobj->projection_param.frustum.left = left;
    cobj->projection_param.frustum.right = right;
}

void HSD_CObjSetOrtho(HSD_CObj* cobj, float top, float bottom, float left,
                      float right)
{
    if (cobj == NULL) {
        return;
    }
    cobj->projection_type = PROJ_ORTHO;
    cobj->projection_param.ortho.top = top;
    cobj->projection_param.ortho.bottom = bottom;
    cobj->projection_param.ortho.left = left;
    cobj->projection_param.ortho.right = right;
}

void HSD_CObjGetPerspective(HSD_CObj* cobj, float* top, float* bottom)
{
    if (cobj == NULL || cobj->projection_type != PROJ_PERSPECTIVE) {
        return;
    }
    if (top != NULL) {
        *top = cobj->projection_param.perspective.fov;
    }
    if (bottom != NULL) {
        *bottom = cobj->projection_param.perspective.aspect;
    }
}

void HSD_CObjGetOrtho(HSD_CObj* cobj, float* top, float* bottom, float* left,
                      float* right)
{
    if (cobj == NULL || cobj->projection_type != PROJ_ORTHO) {
        return;
    }
    if (top != NULL) {
        *top = cobj->projection_param.ortho.top;
    }
    if (bottom != NULL) {
        *bottom = cobj->projection_param.ortho.bottom;
    }
    if (left != NULL) {
        *left = cobj->projection_param.ortho.left;
    }
    if (right != NULL) {
        *right = cobj->projection_param.ortho.right;
    }
}

u32 HSD_CObjGetFlags(HSD_CObj* cobj)
{
    return cobj->flags;
}

void HSD_CObjSetFlags(HSD_CObj* cobj, u32 flags)
{
    if (cobj == NULL) {
        return;
    }
    cobj->flags |= flags;
}

void HSD_CObjClearFlags(HSD_CObj* cobj, u32 flags)
{
    if (cobj == NULL) {
        return;
    }
    cobj->flags &= ~flags;
}

HSD_CObj* HSD_CObjGetCurrent(void)
{
    return current;
}

HSD_CObj* HSD_CObjAlloc(void)
{
    HSD_CObj* cobj = (HSD_CObj*) hsdNew(
        default_class ? default_class : &hsdCObj.parent.parent);
    HSD_ASSERT3(1954, HSD_CObj_804D5D48, cobj);
    return cobj;
}

static Vec3 HSD_CObj_8040631C = { 0, 1, 0 };
static char HSD_CObj_804D5D50[3] = "0";

static int CObjLoad(HSD_CObj* cobj, HSD_CObjDesc* cobjdesc)
{
    NOT_IMPLEMENTED;
}

void HSD_CObjInit(HSD_CObj* cobj, HSD_CObjDesc* desc)
{
    if (cobj == NULL || desc == NULL) {
        return;
    }
    CObjLoad(cobj, desc);
}

#define HSD_COBJ(o) ((HSD_CObj*) (o))
#define HSD_COBJ_INFO(i) ((HSD_CObjInfo*) (i))
#define HSD_COBJ_METHOD(o) HSD_COBJ_INFO(HSD_OBJECT_METHOD(o))

HSD_CObj* HSD_CObjLoadDesc(HSD_CObjDesc* desc)
{
    HSD_ClassInfo* info;
    HSD_CObj* cobj;

    if (desc != NULL) {
        if (desc->class_name == NULL ||
            (info = hsdSearchClassInfo(desc->class_name)) == NULL)
        {
            cobj = HSD_CObjAlloc();
        } else {
            cobj = hsdNew(info);
            HSD_ASSERT3(0x7F7, HSD_CObj_804D5D48, cobj);
        }
        HSD_COBJ_METHOD(cobj)->load(cobj, desc);
        return cobj;
    }
    return NULL;
}

static int CObjInit(HSD_Class* o)
{
    HSD_CObj* cobj;
    int status = HSD_OBJECT_PARENT_INFO(&hsdCObj)->init(o);
    if (status < 0) {
        return status;
    }
    cobj = (HSD_CObj*) o;
    if (cobj != NULL) {
        HSD_CObjSetMtxDirty(cobj);
    }
    cobj->eyepos = HSD_WObjAlloc();
    cobj->interest = HSD_WObjAlloc();
    return 0;
}

void CObjRelease(HSD_Class* o)
{
    HSD_WObj* eyepos;
    HSD_WObj* interest;
    HSD_CObj* cobj = (HSD_CObj*) o;

    HSD_AObjRemove(cobj->aobj);
    eyepos = HSD_CObjGetEyePositionWObj(cobj);
    if (eyepos != NULL) {
        if (ref_DEC(eyepos) && eyepos != NULL) {
            HSD_CLASS_METHOD(eyepos)->release((HSD_Class*) eyepos);
            HSD_CLASS_METHOD(eyepos)->destroy((HSD_Class*) eyepos);
        }
    }
    interest = HSD_CObjGetInterestWObj(cobj);
    if (interest != NULL) {
        if (ref_DEC(interest) && interest != NULL) {
            HSD_CLASS_METHOD(interest)->release((HSD_Class*) interest);
            HSD_CLASS_METHOD(interest)->destroy((HSD_Class*) interest);
        }
    }
    if (cobj->proj_mtx != NULL) {
        HSD_MtxFree(cobj->proj_mtx);
    }
    HSD_OBJECT_PARENT_INFO(&hsdCObj)->release(o);
}

static void CObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    if (info == HSD_CLASS_INFO(&hsdCObj)) {
        current = NULL;
    }
    HSD_OBJECT_PARENT_INFO(&hsdCObj)->amnesia(info);
}

static void CObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdCObj), &hsdObj,
                     "sysdolphin_base_library", "hsd_cobj",
                     sizeof(HSD_CObjInfo), sizeof(HSD_CObj));

    HSD_CLASS_INFO(&hsdCObj)->init = CObjInit;
    HSD_CLASS_INFO(&hsdCObj)->release = CObjRelease;
    HSD_CLASS_INFO(&hsdCObj)->amnesia = CObjAmnesia;
    hsdCObj.load = CObjLoad;
}
