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

int setupTopHalfCamera(HSD_CObj* cobj)
{
    NOT_IMPLEMENTED;
}

int setupBottomHalfCamera(HSD_CObj* cobj)
{
    NOT_IMPLEMENTED;
}

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
