#include <math.h>
#include <placeholder.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/mtx/mtxvec.h>
#include <dolphin/mtx/vec.h>
#include <dolphin/vi/vi.h>
#include <baselib/cobj.h>
#include <baselib/displayfunc.h>
#include <baselib/initialize.h>
#include <baselib/mtx.h>
#include <MSL/trigf.h>
#include <Runtime/runtime.h>

/// @todo doesn't seem like this file should be in melee/
#include <melee/lb/lbrefract.h>

static HSD_ClassInfo* default_class;
static HSD_CObj* current;

extern const float HSD_CObj_804DE474; // 0.01745329252F

#define DegToRad(a) ((a) *0.01745329252F)

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

bool makeProjectionMtx(HSD_CObj* cobj, Mtx mtx)
{
    bool is_ortho;
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        is_ortho = false;
        C_MTXPerspective(mtx, cobj->projection_param.perspective.fov,
                         cobj->projection_param.perspective.aspect, cobj->near,
                         cobj->far);
        break;
    case PROJ_FRUSTUM:
        is_ortho = false;
        C_MTXFrustum(mtx, cobj->projection_param.perspective.fov,
                     cobj->projection_param.perspective.aspect,
                     cobj->projection_param.frustum.left,
                     cobj->projection_param.frustum.right, cobj->near,
                     cobj->far);
        break;
    case PROJ_ORTHO:
        is_ortho = true;
        C_MTXOrtho(mtx, cobj->projection_param.perspective.fov,
                   cobj->projection_param.perspective.aspect,
                   cobj->projection_param.frustum.left,
                   cobj->projection_param.frustum.right, cobj->near,
                   cobj->far);
        break;
    }
    return is_ortho;
}

extern GXRenderModeObj HSD_VIData;
extern const f64 HSD_CObj_804DE480;
extern const float HSD_CObj_804DE478;
extern const float HSD_CObj_804DE47C;

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
#ifdef MUST_MATCH
#pragma push
asm bool setupNormalCamera(HSD_CObj* cobj)
{ // clang-format off
    nofralloc
/* 80367C28 00364808  7C 08 02 A6 */	mflr r0
/* 80367C2C 0036480C  3C 80 80 4C */	lis r4, HSD_VIData@ha
/* 80367C30 00364810  90 01 00 04 */	stw r0, 4(r1)
/* 80367C34 00364814  38 E4 1D 80 */	addi r7, r4, HSD_VIData@l
/* 80367C38 00364818  3C C0 43 30 */	lis r6, 0x4330
/* 80367C3C 0036481C  94 21 FF 38 */	stwu r1, -0xc8(r1)
/* 80367C40 00364820  DB E1 00 C0 */	stfd f31, 0xc0(r1)
/* 80367C44 00364824  DB C1 00 B8 */	stfd f30, 0xb8(r1)
/* 80367C48 00364828  DB A1 00 B0 */	stfd f29, 0xb0(r1)
/* 80367C4C 0036482C  DB 81 00 A8 */	stfd f28, 0xa8(r1)
/* 80367C50 00364830  DB 61 00 A0 */	stfd f27, 0xa0(r1)
/* 80367C54 00364834  DB 41 00 98 */	stfd f26, 0x98(r1)
/* 80367C58 00364838  BF 61 00 84 */	stmw r27, 0x84(r1)
/* 80367C5C 0036483C  7C 7E 1B 78 */	mr r30, r3
/* 80367C60 00364840  A0 07 00 04 */	lhz r0, 4(r7)
/* 80367C64 00364844  A0 A7 00 0E */	lhz r5, 0xe(r7)
/* 80367C68 00364848  90 01 00 7C */	stw r0, 0x7c(r1)
/* 80367C6C 0036484C  A0 87 00 06 */	lhz r4, 6(r7)
/* 80367C70 00364850  A0 67 00 10 */	lhz r3, 0x10(r7)
/* 80367C74 00364854  90 A1 00 74 */	stw r5, 0x74(r1)
/* 80367C78 00364858  C9 02 EA A0 */	lfd f8, HSD_CObj_804DE480(r2)
/* 80367C7C 0036485C  90 81 00 6C */	stw r4, 0x6c(r1)
/* 80367C80 00364860  88 07 00 18 */	lbz r0, 0x18(r7)
/* 80367C84 00364864  90 61 00 64 */	stw r3, 0x64(r1)
/* 80367C88 00364868  C0 7E 00 0C */	lfs f3, 0xc(r30)
/* 80367C8C 0036486C  28 00 00 00 */	cmplwi r0, 0
/* 80367C90 00364870  90 C1 00 78 */	stw r6, 0x78(r1)
/* 80367C94 00364874  C0 5E 00 14 */	lfs f2, 0x14(r30)
/* 80367C98 00364878  90 C1 00 70 */	stw r6, 0x70(r1)
/* 80367C9C 0036487C  C8 A1 00 78 */	lfd f5, 0x78(r1)
/* 80367CA0 00364880  C8 81 00 70 */	lfd f4, 0x70(r1)
/* 80367CA4 00364884  90 C1 00 68 */	stw r6, 0x68(r1)
/* 80367CA8 00364888  EC E5 40 28 */	fsubs f7, f5, f8
/* 80367CAC 0036488C  EC C4 40 28 */	fsubs f6, f4, f8
/* 80367CB0 00364890  C0 3E 00 10 */	lfs f1, 0x10(r30)
/* 80367CB4 00364894  90 C1 00 60 */	stw r6, 0x60(r1)
/* 80367CB8 00364898  C8 A1 00 68 */	lfd f5, 0x68(r1)
/* 80367CBC 0036489C  EF E7 30 24 */	fdivs f31, f7, f6
/* 80367CC0 003648A0  C8 81 00 60 */	lfd f4, 0x60(r1)
/* 80367CC4 003648A4  C0 1E 00 18 */	lfs f0, 0x18(r30)
/* 80367CC8 003648A8  EC 63 07 F2 */	fmuls f3, f3, f31
/* 80367CCC 003648AC  EC 21 07 F2 */	fmuls f1, f1, f31
/* 80367CD0 003648B0  EC A5 40 28 */	fsubs f5, f5, f8
/* 80367CD4 003648B4  EC 84 40 28 */	fsubs f4, f4, f8
/* 80367CD8 003648B8  FF 80 18 90 */	fmr f28, f3
/* 80367CDC 003648BC  EF 61 18 28 */	fsubs f27, f1, f3
/* 80367CE0 003648C0  EF C5 20 24 */	fdivs f30, f5, f4
/* 80367CE4 003648C4  EC 42 07 B2 */	fmuls f2, f2, f30
/* 80367CE8 003648C8  EC 00 07 B2 */	fmuls f0, f0, f30
/* 80367CEC 003648CC  FF A0 10 90 */	fmr f29, f2
/* 80367CF0 003648D0  EF 40 10 28 */	fsubs f26, f0, f2
/* 80367CF4 003648D4  41 82 00 28 */	beq lbl_80367D1C
/* 80367CF8 003648D8  4B FE 84 F5 */	bl VIGetNextField
/* 80367CFC 003648DC  FC 20 E0 90 */	fmr f1, f28
/* 80367D00 003648E0  C0 A2 EA 98 */	lfs f5, HSD_CObj_804DE478
/* 80367D04 003648E4  FC 40 E8 90 */	fmr f2, f29
/* 80367D08 003648E8  C0 C2 EA 9C */	lfs f6, HSD_CObj_804DE47C(r2)
/* 80367D0C 003648EC  FC 60 D8 90 */	fmr f3, f27
/* 80367D10 003648F0  FC 80 D0 90 */	fmr f4, f26
/* 80367D14 003648F4  4B FD 98 BD */	bl GXSetViewportJitter
/* 80367D18 003648F8  48 00 00 20 */	b lbl_80367D38
lbl_80367D1C:
/* 80367D1C 003648FC  FC 20 E0 90 */	fmr f1, f28
/* 80367D20 00364900  C0 A2 EA 98 */	lfs f5, HSD_CObj_804DE478
/* 80367D24 00364904  FC 40 E8 90 */	fmr f2, f29
/* 80367D28 00364908  C0 C2 EA 9C */	lfs f6, HSD_CObj_804DE47C(r2)
/* 80367D2C 0036490C  FC 60 D8 90 */	fmr f3, f27
/* 80367D30 00364910  FC 80 D0 90 */	fmr f4, f26
/* 80367D34 00364914  4B FD 99 B9 */	bl GXSetViewport
lbl_80367D38:
/* 80367D38 00364918  A0 7E 00 20 */	lhz r3, 0x20(r30)
/* 80367D3C 0036491C  3C 80 43 30 */	lis r4, 0x4330
/* 80367D40 00364920  A0 1E 00 22 */	lhz r0, 0x22(r30)
/* 80367D44 00364924  90 61 00 6C */	stw r3, 0x6c(r1)
/* 80367D48 00364928  A0 7E 00 1C */	lhz r3, 0x1c(r30)
/* 80367D4C 0036492C  90 01 00 7C */	stw r0, 0x7c(r1)
/* 80367D50 00364930  A0 1E 00 1E */	lhz r0, 0x1e(r30)
/* 80367D54 00364934  90 81 00 68 */	stw r4, 0x68(r1)
/* 80367D58 00364938  C8 82 EA A0 */	lfd f4, HSD_CObj_804DE480(r2)
/* 80367D5C 0036493C  90 81 00 78 */	stw r4, 0x78(r1)
/* 80367D60 00364940  C8 21 00 68 */	lfd f1, 0x68(r1)
/* 80367D64 00364944  90 61 00 64 */	stw r3, 0x64(r1)
/* 80367D68 00364948  C8 01 00 78 */	lfd f0, 0x78(r1)
/* 80367D6C 0036494C  EC 21 20 28 */	fsubs f1, f1, f4
/* 80367D70 00364950  90 01 00 74 */	stw r0, 0x74(r1)
/* 80367D74 00364954  EC 00 20 28 */	fsubs f0, f0, f4
/* 80367D78 00364958  90 81 00 60 */	stw r4, 0x60(r1)
/* 80367D7C 0036495C  EF A1 07 B2 */	fmuls f29, f1, f30
/* 80367D80 00364960  90 81 00 70 */	stw r4, 0x70(r1)
/* 80367D84 00364964  EC 00 07 B2 */	fmuls f0, f0, f30
/* 80367D88 00364968  C8 41 00 60 */	lfd f2, 0x60(r1)
/* 80367D8C 0036496C  C8 21 00 70 */	lfd f1, 0x70(r1)
/* 80367D90 00364970  EC 62 20 28 */	fsubs f3, f2, f4
/* 80367D94 00364974  EC 41 20 28 */	fsubs f2, f1, f4
/* 80367D98 00364978  EC 20 E8 28 */	fsubs f1, f0, f29
/* 80367D9C 0036497C  EF C3 07 F2 */	fmuls f30, f3, f31
/* 80367DA0 00364980  EC 02 07 F2 */	fmuls f0, f2, f31
/* 80367DA4 00364984  EF E0 F0 28 */	fsubs f31, f0, f30
/* 80367DA8 00364988  4B FB AB 19 */	bl __cvt_fp2unsigned
/* 80367DAC 0036498C  7C 7B 1B 78 */	mr r27, r3
/* 80367DB0 00364990  FC 20 F8 90 */	fmr f1, f31
/* 80367DB4 00364994  4B FB AB 0D */	bl __cvt_fp2unsigned
/* 80367DB8 00364998  7C 7C 1B 78 */	mr r28, r3
/* 80367DBC 0036499C  FC 20 E8 90 */	fmr f1, f29
/* 80367DC0 003649A0  4B FB AB 01 */	bl __cvt_fp2unsigned
/* 80367DC4 003649A4  7C 7D 1B 78 */	mr r29, r3
/* 80367DC8 003649A8  FC 20 F0 90 */	fmr f1, f30
/* 80367DCC 003649AC  4B FB AA F5 */	bl __cvt_fp2unsigned
/* 80367DD0 003649B0  38 9D 00 00 */	addi r4, r29, 0
/* 80367DD4 003649B4  38 BC 00 00 */	addi r5, r28, 0
/* 80367DD8 003649B8  38 DB 00 00 */	addi r6, r27, 0
/* 80367DDC 003649BC  4B FD 99 81 */	bl GXSetScissor
/* 80367DE0 003649C0  88 1E 00 50 */	lbz r0, 0x50(r30)
/* 80367DE4 003649C4  2C 00 00 02 */	cmpwi r0, 2
/* 80367DE8 003649C8  41 82 00 40 */	beq lbl_80367E28
/* 80367DEC 003649CC  40 80 00 10 */	bge lbl_80367DFC
/* 80367DF0 003649D0  2C 00 00 01 */	cmpwi r0, 1
/* 80367DF4 003649D4  40 80 00 14 */	bge lbl_80367E08
/* 80367DF8 003649D8  48 00 00 7C */	b lbl_80367E74
lbl_80367DFC:
/* 80367DFC 003649DC  2C 00 00 04 */	cmpwi r0, 4
/* 80367E00 003649E0  40 80 00 74 */	bge lbl_80367E74
/* 80367E04 003649E4  48 00 00 4C */	b lbl_80367E50
lbl_80367E08:
/* 80367E08 003649E8  C0 3E 00 40 */	lfs f1, 0x40(r30)
/* 80367E0C 003649EC  38 61 00 1C */	addi r3, r1, 0x1c
/* 80367E10 003649F0  C0 5E 00 44 */	lfs f2, 0x44(r30)
/* 80367E14 003649F4  3B E0 00 00 */	li r31, 0
/* 80367E18 003649F8  C0 7E 00 38 */	lfs f3, 0x38(r30)
/* 80367E1C 003649FC  C0 9E 00 3C */	lfs f4, 0x3c(r30)
/* 80367E20 00364A00  4B FD AD CD */	bl C_MTXPerspective
/* 80367E24 00364A04  48 00 00 50 */	b lbl_80367E74
lbl_80367E28:
/* 80367E28 00364A08  C0 3E 00 40 */	lfs f1, 0x40(r30)
/* 80367E2C 00364A0C  38 61 00 1C */	addi r3, r1, 0x1c
/* 80367E30 00364A10  C0 5E 00 44 */	lfs f2, 0x44(r30)
/* 80367E34 00364A14  3B E0 00 00 */	li r31, 0
/* 80367E38 00364A18  C0 7E 00 48 */	lfs f3, 0x48(r30)
/* 80367E3C 00364A1C  C0 9E 00 4C */	lfs f4, 0x4c(r30)
/* 80367E40 00364A20  C0 BE 00 38 */	lfs f5, 0x38(r30)
/* 80367E44 00364A24  C0 DE 00 3C */	lfs f6, 0x3c(r30)
/* 80367E48 00364A28  4B FD AD 09 */	bl C_MTXFrustum
/* 80367E4C 00364A2C  48 00 00 28 */	b lbl_80367E74
lbl_80367E50:
/* 80367E50 00364A30  C0 3E 00 40 */	lfs f1, 0x40(r30)
/* 80367E54 00364A34  38 61 00 1C */	addi r3, r1, 0x1c
/* 80367E58 00364A38  C0 5E 00 44 */	lfs f2, 0x44(r30)
/* 80367E5C 00364A3C  3B E0 00 01 */	li r31, 1
/* 80367E60 00364A40  C0 7E 00 48 */	lfs f3, 0x48(r30)
/* 80367E64 00364A44  C0 9E 00 4C */	lfs f4, 0x4c(r30)
/* 80367E68 00364A48  C0 BE 00 38 */	lfs f5, 0x38(r30)
/* 80367E6C 00364A4C  C0 DE 00 3C */	lfs f6, 0x3c(r30)
/* 80367E70 00364A50  4B FD AE 4D */	bl C_MTXOrtho
lbl_80367E74:
/* 80367E74 00364A54  38 9F 00 00 */	addi r4, r31, 0
/* 80367E78 00364A58  38 61 00 1C */	addi r3, r1, 0x1c
/* 80367E7C 00364A5C  4B FD 94 41 */	bl GXSetProjection
/* 80367E80 00364A60  BB 61 00 84 */	lmw r27, 0x84(r1)
/* 80367E84 00364A64  38 60 00 01 */	li r3, 1
/* 80367E88 00364A68  80 01 00 CC */	lwz r0, 0xcc(r1)
/* 80367E8C 00364A6C  CB E1 00 C0 */	lfd f31, 0xc0(r1)
/* 80367E90 00364A70  CB C1 00 B8 */	lfd f30, 0xb8(r1)
/* 80367E94 00364A74  CB A1 00 B0 */	lfd f29, 0xb0(r1)
/* 80367E98 00364A78  CB 81 00 A8 */	lfd f28, 0xa8(r1)
/* 80367E9C 00364A7C  CB 61 00 A0 */	lfd f27, 0xa0(r1)
/* 80367EA0 00364A80  CB 41 00 98 */	lfd f26, 0x98(r1)
/* 80367EA4 00364A84  38 21 00 C8 */	addi r1, r1, 0xc8
/* 80367EA8 00364A88  7C 08 03 A6 */	mtlr r0
/* 80367EAC 00364A8C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

int setupNormalCamera(HSD_CObj* cobj)
{
    Mtx44 sp1C;
    float height_scale;
    float top_scaled;
    float left_scaled;
    float width_scaled;
    float bottom_scaled;
    float width_scale;
    float height_scaled;
    float right_scaled;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif

    width_scale = (float) HSD_VIData.fbWidth / HSD_VIData.viWidth;
    height_scale = (float) HSD_VIData.efbHeight / HSD_VIData.viHeight;

    left_scaled = cobj->viewport.left * width_scale;
    right_scaled = cobj->viewport.right * width_scale;
    top_scaled = cobj->viewport.top * height_scale;
    bottom_scaled = cobj->viewport.bottom * height_scale;
    width_scaled = right_scaled - left_scaled;
    height_scaled = bottom_scaled - top_scaled;
    if (HSD_VIData.field_rendering) {
        GXSetViewportJitter(left_scaled, top_scaled, width_scaled,
                            height_scaled, HSD_CObj_804DE478,
                            HSD_CObj_804DE47C, VIGetNextField());
    } else {
        GXSetViewport(left_scaled, top_scaled, width_scaled, height_scaled,
                      HSD_CObj_804DE478, HSD_CObj_804DE47C);
    }
    left_scaled = cobj->scissor.left * width_scale;
    right_scaled = cobj->scissor.right * width_scale;
    top_scaled = cobj->scissor.top * height_scale;
    bottom_scaled = cobj->scissor.bottom * height_scale;
    width_scale = right_scaled - left_scaled;
    height_scale = bottom_scaled - top_scaled;
    GXSetScissor(left_scaled, top_scaled, width_scale, height_scale);
    GXSetProjection(sp1C, makeProjectionMtx(cobj, sp1C));
    return 1;
}
#endif

extern const f64 HSD_CObj_804DE488;
extern const float HSD_CObj_804DE490;
extern const float HSD_CObj_804DE494;

#ifdef MWERKS_GEKKO
#pragma push
asm bool setupTopHalfCamera()
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
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm bool setupBottomHalfCamera()
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

#ifdef MUST_MATCH
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

#ifndef MUST_MATCH
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
#else
#pragma push
asm int roll2upvec(HSD_CObj* cobj, Vec3* up, float roll)
{ // clang-format off
    nofralloc
/* 80368BC0 003657A0  7C 08 02 A6 */	mflr r0
/* 80368BC4 003657A4  90 01 00 04 */	stw r0, 4(r1)
/* 80368BC8 003657A8  94 21 FF 58 */	stwu r1, -0xa8(r1)
/* 80368BCC 003657AC  DB E1 00 A0 */	stfd f31, 0xa0(r1)
/* 80368BD0 003657B0  FF E0 08 90 */	fmr f31, f1
/* 80368BD4 003657B4  93 E1 00 9C */	stw r31, 0x9c(r1)
/* 80368BD8 003657B8  7C 9F 23 78 */	mr r31, r4
/* 80368BDC 003657BC  93 C1 00 98 */	stw r30, 0x98(r1)
/* 80368BE0 003657C0  7C 7E 1B 79 */	or. r30, r3, r3
/* 80368BE4 003657C4  41 82 00 C0 */	beq lbl_80368CA4
/* 80368BE8 003657C8  80 1E 00 24 */	lwz r0, 0x24(r30)
/* 80368BEC 003657CC  28 00 00 00 */	cmplwi r0, 0
/* 80368BF0 003657D0  41 82 00 B4 */	beq lbl_80368CA4
/* 80368BF4 003657D4  80 1E 00 28 */	lwz r0, 0x28(r30)
/* 80368BF8 003657D8  28 00 00 00 */	cmplwi r0, 0
/* 80368BFC 003657DC  41 82 00 A8 */	beq lbl_80368CA4
/* 80368C00 003657E0  28 1E 00 00 */	cmplwi r30, 0
/* 80368C04 003657E4  40 82 00 14 */	bne lbl_80368C18
/* 80368C08 003657E8  38 6D A6 A0 */	addi r3, r13, HSD_CObj_804D5D40
/* 80368C0C 003657EC  38 80 02 DD */	li r4, 0x2dd
/* 80368C10 003657F0  38 AD A6 A8 */	addi r5, r13, HSD_CObj_804D5D48
/* 80368C14 003657F4  48 01 F6 0D */	bl __assert
lbl_80368C18:
/* 80368C18 003657F8  28 1E 00 00 */	cmplwi r30, 0
/* 80368C1C 003657FC  40 82 00 14 */	bne lbl_80368C30
/* 80368C20 00365800  38 6D A6 A0 */	addi r3, r13, HSD_CObj_804D5D40
/* 80368C24 00365804  38 80 02 AD */	li r4, 0x2ad
/* 80368C28 00365808  38 AD A6 A8 */	addi r5, r13, HSD_CObj_804D5D48
/* 80368C2C 0036580C  48 01 F5 F5 */	bl __assert
lbl_80368C30:
/* 80368C30 00365810  80 7E 00 24 */	lwz r3, 0x24(r30)
/* 80368C34 00365814  38 81 00 28 */	addi r4, r1, 0x28
/* 80368C38 00365818  48 01 4A E9 */	bl HSD_WObjGetPosition
/* 80368C3C 0036581C  28 1E 00 00 */	cmplwi r30, 0
/* 80368C40 00365820  40 82 00 14 */	bne lbl_80368C54
/* 80368C44 00365824  38 6D A6 A0 */	addi r3, r13, HSD_CObj_804D5D40
/* 80368C48 00365828  38 80 02 C5 */	li r4, 0x2c5
/* 80368C4C 0036582C  38 AD A6 A8 */	addi r5, r13, HSD_CObj_804D5D48
/* 80368C50 00365830  48 01 F5 D1 */	bl __assert
lbl_80368C54:
/* 80368C54 00365834  28 1E 00 00 */	cmplwi r30, 0
/* 80368C58 00365838  40 82 00 14 */	bne lbl_80368C6C
/* 80368C5C 0036583C  38 6D A6 A0 */	addi r3, r13, HSD_CObj_804D5D40
/* 80368C60 00365840  38 80 02 95 */	li r4, 0x295
/* 80368C64 00365844  38 AD A6 A8 */	addi r5, r13, HSD_CObj_804D5D48
/* 80368C68 00365848  48 01 F5 B9 */	bl __assert
lbl_80368C6C:
/* 80368C6C 0036584C  80 7E 00 28 */	lwz r3, 0x28(r30)
/* 80368C70 00365850  38 81 00 34 */	addi r4, r1, 0x34
/* 80368C74 00365854  48 01 4A AD */	bl HSD_WObjGetPosition
/* 80368C78 00365858  38 61 00 34 */	addi r3, r1, 0x34
/* 80368C7C 0036585C  38 81 00 28 */	addi r4, r1, 0x28
/* 80368C80 00365860  38 A1 00 88 */	addi r5, r1, 0x88
/* 80368C84 00365864  4B FD A0 F5 */	bl PSVECSubtract
/* 80368C88 00365868  38 61 00 88 */	addi r3, r1, 0x88
/* 80368C8C 0036586C  38 83 00 00 */	addi r4, r3, 0
/* 80368C90 00365870  4B FF FE 7D */	bl vec_normalize_check
/* 80368C94 00365874  2C 03 00 00 */	cmpwi r3, 0
/* 80368C98 00365878  40 82 00 0C */	bne lbl_80368CA4
/* 80368C9C 0036587C  38 60 00 00 */	li r3, 0
/* 80368CA0 00365880  48 00 00 1C */	b lbl_80368CBC
lbl_80368CA4:
/* 80368CA4 00365884  C0 22 EA 98 */	lfs f1, HSD_CObj_804DE478
/* 80368CA8 00365888  38 60 FF FF */	li r3, -1
/* 80368CAC 0036588C  C0 02 EA B4 */	lfs f0, HSD_CObj_804DE494(r2)
/* 80368CB0 00365890  D0 21 00 88 */	stfs f1, 0x88(r1)
/* 80368CB4 00365894  D0 21 00 8C */	stfs f1, 0x8c(r1)
/* 80368CB8 00365898  D0 01 00 90 */	stfs f0, 0x90(r1)
lbl_80368CBC:
/* 80368CBC 0036589C  2C 03 00 00 */	cmpwi r3, 0
/* 80368CC0 003658A0  41 82 00 08 */	beq lbl_80368CC8
/* 80368CC4 003658A4  48 00 01 90 */	b lbl_80368E54
lbl_80368CC8:
/* 80368CC8 003658A8  C0 41 00 8C */	lfs f2, 0x8c(r1)
/* 80368CCC 003658AC  C8 22 EA D0 */	lfd f1, HSD_CObj_804DE4B0(r2)
/* 80368CD0 003658B0  FC 60 12 10 */	fabs f3, f2
/* 80368CD4 003658B4  C8 02 EA D8 */	lfd f0, HSD_CObj_804DE4B8(r2)
/* 80368CD8 003658B8  FC 21 18 28 */	fsub f1, f1, f3
/* 80368CDC 003658BC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80368CE0 003658C0  40 80 00 A4 */	bge lbl_80368D84
/* 80368CE4 003658C4  C0 21 00 90 */	lfs f1, 0x90(r1)
/* 80368CE8 003658C8  EC 42 00 B2 */	fmuls f2, f2, f2
/* 80368CEC 003658CC  C0 02 EA 98 */	lfs f0, HSD_CObj_804DE478
/* 80368CF0 003658D0  EC 21 00 72 */	fmuls f1, f1, f1
/* 80368CF4 003658D4  EC 82 08 2A */	fadds f4, f2, f1
/* 80368CF8 003658D8  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 80368CFC 003658DC  40 81 00 50 */	ble lbl_80368D4C
/* 80368D00 003658E0  FC 20 20 34 */	frsqrte f1, f4
/* 80368D04 003658E4  C8 62 EA 88 */	lfd f3, 0.5
/* 80368D08 003658E8  C8 42 EA E0 */	lfd f2, HSD_CObj_804DE4C0(r2)
/* 80368D0C 003658EC  FC 01 00 72 */	fmul f0, f1, f1
/* 80368D10 003658F0  FC 23 00 72 */	fmul f1, f3, f1
/* 80368D14 003658F4  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80368D18 003658F8  FC 21 00 32 */	fmul f1, f1, f0
/* 80368D1C 003658FC  FC 01 00 72 */	fmul f0, f1, f1
/* 80368D20 00365900  FC 23 00 72 */	fmul f1, f3, f1
/* 80368D24 00365904  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80368D28 00365908  FC 21 00 32 */	fmul f1, f1, f0
/* 80368D2C 0036590C  FC 01 00 72 */	fmul f0, f1, f1
/* 80368D30 00365910  FC 23 00 72 */	fmul f1, f3, f1
/* 80368D34 00365914  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80368D38 00365918  FC 01 00 32 */	fmul f0, f1, f0
/* 80368D3C 0036591C  FC 04 00 32 */	fmul f0, f4, f0
/* 80368D40 00365920  FC 00 00 18 */	frsp f0, f0
/* 80368D44 00365924  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80368D48 00365928  C0 81 00 24 */	lfs f4, 0x24(r1)
lbl_80368D4C:
/* 80368D4C 0036592C  C0 01 00 88 */	lfs f0, 0x88(r1)
/* 80368D50 00365930  D0 81 00 7C */	stfs f4, 0x7c(r1)
/* 80368D54 00365934  FC 40 00 50 */	fneg f2, f0
/* 80368D58 00365938  C0 01 00 7C */	lfs f0, 0x7c(r1)
/* 80368D5C 0036593C  C0 21 00 8C */	lfs f1, 0x8c(r1)
/* 80368D60 00365940  EC 02 00 24 */	fdivs f0, f2, f0
/* 80368D64 00365944  EC 01 00 32 */	fmuls f0, f1, f0
/* 80368D68 00365948  D0 01 00 80 */	stfs f0, 0x80(r1)
/* 80368D6C 0036594C  C0 01 00 7C */	lfs f0, 0x7c(r1)
/* 80368D70 00365950  C0 21 00 90 */	lfs f1, 0x90(r1)
/* 80368D74 00365954  EC 02 00 24 */	fdivs f0, f2, f0
/* 80368D78 00365958  EC 01 00 32 */	fmuls f0, f1, f0
/* 80368D7C 0036595C  D0 01 00 84 */	stfs f0, 0x84(r1)
/* 80368D80 00365960  48 00 00 A4 */	b lbl_80368E24
lbl_80368D84:
/* 80368D84 00365964  C0 01 00 88 */	lfs f0, 0x88(r1)
/* 80368D88 00365968  C0 21 00 90 */	lfs f1, 0x90(r1)
/* 80368D8C 0036596C  EC 40 00 32 */	fmuls f2, f0, f0
/* 80368D90 00365970  C0 02 EA 98 */	lfs f0, HSD_CObj_804DE478
/* 80368D94 00365974  EC 21 00 72 */	fmuls f1, f1, f1
/* 80368D98 00365978  EC 82 08 2A */	fadds f4, f2, f1
/* 80368D9C 0036597C  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 80368DA0 00365980  40 81 00 50 */	ble lbl_80368DF0
/* 80368DA4 00365984  FC 20 20 34 */	frsqrte f1, f4
/* 80368DA8 00365988  C8 62 EA 88 */	lfd f3, 0.5
/* 80368DAC 0036598C  C8 42 EA E0 */	lfd f2, HSD_CObj_804DE4C0(r2)
/* 80368DB0 00365990  FC 01 00 72 */	fmul f0, f1, f1
/* 80368DB4 00365994  FC 23 00 72 */	fmul f1, f3, f1
/* 80368DB8 00365998  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80368DBC 0036599C  FC 21 00 32 */	fmul f1, f1, f0
/* 80368DC0 003659A0  FC 01 00 72 */	fmul f0, f1, f1
/* 80368DC4 003659A4  FC 23 00 72 */	fmul f1, f3, f1
/* 80368DC8 003659A8  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80368DCC 003659AC  FC 21 00 32 */	fmul f1, f1, f0
/* 80368DD0 003659B0  FC 01 00 72 */	fmul f0, f1, f1
/* 80368DD4 003659B4  FC 23 00 72 */	fmul f1, f3, f1
/* 80368DD8 003659B8  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80368DDC 003659BC  FC 01 00 32 */	fmul f0, f1, f0
/* 80368DE0 003659C0  FC 04 00 32 */	fmul f0, f4, f0
/* 80368DE4 003659C4  FC 00 00 18 */	frsp f0, f0
/* 80368DE8 003659C8  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 80368DEC 003659CC  C0 81 00 20 */	lfs f4, 0x20(r1)
lbl_80368DF0:
/* 80368DF0 003659D0  D0 81 00 80 */	stfs f4, 0x80(r1)
/* 80368DF4 003659D4  C0 21 00 8C */	lfs f1, 0x8c(r1)
/* 80368DF8 003659D8  C0 01 00 80 */	lfs f0, 0x80(r1)
/* 80368DFC 003659DC  FC 40 08 50 */	fneg f2, f1
/* 80368E00 003659E0  C0 21 00 88 */	lfs f1, 0x88(r1)
/* 80368E04 003659E4  EC 02 00 24 */	fdivs f0, f2, f0
/* 80368E08 003659E8  EC 01 00 32 */	fmuls f0, f1, f0
/* 80368E0C 003659EC  D0 01 00 7C */	stfs f0, 0x7c(r1)
/* 80368E10 003659F0  C0 01 00 80 */	lfs f0, 0x80(r1)
/* 80368E14 003659F4  C0 21 00 90 */	lfs f1, 0x90(r1)
/* 80368E18 003659F8  EC 02 00 24 */	fdivs f0, f2, f0
/* 80368E1C 003659FC  EC 01 00 32 */	fmuls f0, f1, f0
/* 80368E20 00365A00  D0 01 00 84 */	stfs f0, 0x84(r1)
lbl_80368E24:
/* 80368E24 00365A04  FC 20 F8 50 */	fneg f1, f31
/* 80368E28 00365A08  38 61 00 40 */	addi r3, r1, 0x40
/* 80368E2C 00365A0C  38 81 00 88 */	addi r4, r1, 0x88
/* 80368E30 00365A10  4B FD 97 01 */	bl PSMTXRotAxisRad
/* 80368E34 00365A14  38 61 00 40 */	addi r3, r1, 0x40
/* 80368E38 00365A18  38 81 00 7C */	addi r4, r1, 0x7c
/* 80368E3C 00365A1C  38 A1 00 70 */	addi r5, r1, 0x70
/* 80368E40 00365A20  4B FD 9C BD */	bl PSMTXMultVecSR
/* 80368E44 00365A24  38 61 00 70 */	addi r3, r1, 0x70
/* 80368E48 00365A28  38 9F 00 00 */	addi r4, r31, 0
/* 80368E4C 00365A2C  4B FD 9F 6D */	bl PSVECNormalize
/* 80368E50 00365A30  38 60 00 00 */	li r3, 0
lbl_80368E54:
/* 80368E54 00365A34  80 01 00 AC */	lwz r0, 0xac(r1)
/* 80368E58 00365A38  CB E1 00 A0 */	lfd f31, 0xa0(r1)
/* 80368E5C 00365A3C  83 E1 00 9C */	lwz r31, 0x9c(r1)
/* 80368E60 00365A40  83 C1 00 98 */	lwz r30, 0x98(r1)
/* 80368E64 00365A44  38 21 00 A8 */	addi r1, r1, 0xa8
/* 80368E68 00365A48  7C 08 03 A6 */	mtlr r0
/* 80368E6C 00365A4C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void HSD_CObjGetUpVector()
{ // clang-format off
    nofralloc
/* 80368E70 00365A50  7C 08 02 A6 */	mflr r0
/* 80368E74 00365A54  7C 65 1B 79 */	or. r5, r3, r3
/* 80368E78 00365A58  90 01 00 04 */	stw r0, 4(r1)
/* 80368E7C 00365A5C  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 80368E80 00365A60  DB E1 00 78 */	stfd f31, 0x78(r1)
/* 80368E84 00365A64  93 E1 00 74 */	stw r31, 0x74(r1)
/* 80368E88 00365A68  3B E4 00 00 */	addi r31, r4, 0
/* 80368E8C 00365A6C  41 82 01 F0 */	beq lbl_8036907C
/* 80368E90 00365A70  28 1F 00 00 */	cmplwi r31, 0
/* 80368E94 00365A74  41 82 01 E8 */	beq lbl_8036907C
/* 80368E98 00365A78  80 05 00 08 */	lwz r0, 8(r5)
/* 80368E9C 00365A7C  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80368EA0 00365A80  41 82 00 24 */	beq lbl_80368EC4
/* 80368EA4 00365A84  80 85 00 2C */	lwz r4, 0x2c(r5)
/* 80368EA8 00365A88  38 60 00 00 */	li r3, 0
/* 80368EAC 00365A8C  80 05 00 30 */	lwz r0, 0x30(r5)
/* 80368EB0 00365A90  90 9F 00 00 */	stw r4, 0(r31)
/* 80368EB4 00365A94  90 1F 00 04 */	stw r0, 4(r31)
/* 80368EB8 00365A98  80 05 00 34 */	lwz r0, 0x34(r5)
/* 80368EBC 00365A9C  90 1F 00 08 */	stw r0, 8(r31)
/* 80368EC0 00365AA0  48 00 01 DC */	b lbl_8036909C
lbl_80368EC4:
/* 80368EC4 00365AA4  C3 E5 00 2C */	lfs f31, 0x2c(r5)
/* 80368EC8 00365AA8  38 65 00 00 */	addi r3, r5, 0
/* 80368ECC 00365AAC  38 81 00 1C */	addi r4, r1, 0x1c
/* 80368ED0 00365AB0  4B FF F9 8D */	bl HSD_CObjGetEyeVector
/* 80368ED4 00365AB4  2C 03 00 00 */	cmpwi r3, 0
/* 80368ED8 00365AB8  41 82 00 08 */	beq lbl_80368EE0
/* 80368EDC 00365ABC  48 00 01 90 */	b lbl_8036906C
lbl_80368EE0:
/* 80368EE0 00365AC0  C0 41 00 20 */	lfs f2, 0x20(r1)
/* 80368EE4 00365AC4  C8 22 EA D0 */	lfd f1, HSD_CObj_804DE4B0(r2)
/* 80368EE8 00365AC8  FC 60 12 10 */	fabs f3, f2
/* 80368EEC 00365ACC  C8 02 EA D8 */	lfd f0, HSD_CObj_804DE4B8(r2)
/* 80368EF0 00365AD0  FC 21 18 28 */	fsub f1, f1, f3
/* 80368EF4 00365AD4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80368EF8 00365AD8  40 80 00 A4 */	bge lbl_80368F9C
/* 80368EFC 00365ADC  C0 21 00 24 */	lfs f1, 0x24(r1)
/* 80368F00 00365AE0  EC 42 00 B2 */	fmuls f2, f2, f2
/* 80368F04 00365AE4  C0 02 EA 98 */	lfs f0, HSD_CObj_804DE478
/* 80368F08 00365AE8  EC 21 00 72 */	fmuls f1, f1, f1
/* 80368F0C 00365AEC  EC 82 08 2A */	fadds f4, f2, f1
/* 80368F10 00365AF0  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 80368F14 00365AF4  40 81 00 50 */	ble lbl_80368F64
/* 80368F18 00365AF8  FC 20 20 34 */	frsqrte f1, f4
/* 80368F1C 00365AFC  C8 62 EA 88 */	lfd f3, 0.5
/* 80368F20 00365B00  C8 42 EA E0 */	lfd f2, HSD_CObj_804DE4C0(r2)
/* 80368F24 00365B04  FC 01 00 72 */	fmul f0, f1, f1
/* 80368F28 00365B08  FC 23 00 72 */	fmul f1, f3, f1
/* 80368F2C 00365B0C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80368F30 00365B10  FC 21 00 32 */	fmul f1, f1, f0
/* 80368F34 00365B14  FC 01 00 72 */	fmul f0, f1, f1
/* 80368F38 00365B18  FC 23 00 72 */	fmul f1, f3, f1
/* 80368F3C 00365B1C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80368F40 00365B20  FC 21 00 32 */	fmul f1, f1, f0
/* 80368F44 00365B24  FC 01 00 72 */	fmul f0, f1, f1
/* 80368F48 00365B28  FC 23 00 72 */	fmul f1, f3, f1
/* 80368F4C 00365B2C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80368F50 00365B30  FC 01 00 32 */	fmul f0, f1, f0
/* 80368F54 00365B34  FC 04 00 32 */	fmul f0, f4, f0
/* 80368F58 00365B38  FC 00 00 18 */	frsp f0, f0
/* 80368F5C 00365B3C  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 80368F60 00365B40  C0 81 00 18 */	lfs f4, 0x18(r1)
lbl_80368F64:
/* 80368F64 00365B44  C0 01 00 1C */	lfs f0, 0x1c(r1)
/* 80368F68 00365B48  D0 81 00 28 */	stfs f4, 0x28(r1)
/* 80368F6C 00365B4C  FC 40 00 50 */	fneg f2, f0
/* 80368F70 00365B50  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 80368F74 00365B54  C0 21 00 20 */	lfs f1, 0x20(r1)
/* 80368F78 00365B58  EC 02 00 24 */	fdivs f0, f2, f0
/* 80368F7C 00365B5C  EC 01 00 32 */	fmuls f0, f1, f0
/* 80368F80 00365B60  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 80368F84 00365B64  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 80368F88 00365B68  C0 21 00 24 */	lfs f1, 0x24(r1)
/* 80368F8C 00365B6C  EC 02 00 24 */	fdivs f0, f2, f0
/* 80368F90 00365B70  EC 01 00 32 */	fmuls f0, f1, f0
/* 80368F94 00365B74  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 80368F98 00365B78  48 00 00 A4 */	b lbl_8036903C
lbl_80368F9C:
/* 80368F9C 00365B7C  C0 01 00 1C */	lfs f0, 0x1c(r1)
/* 80368FA0 00365B80  C0 21 00 24 */	lfs f1, 0x24(r1)
/* 80368FA4 00365B84  EC 40 00 32 */	fmuls f2, f0, f0
/* 80368FA8 00365B88  C0 02 EA 98 */	lfs f0, HSD_CObj_804DE478
/* 80368FAC 00365B8C  EC 21 00 72 */	fmuls f1, f1, f1
/* 80368FB0 00365B90  EC 82 08 2A */	fadds f4, f2, f1
/* 80368FB4 00365B94  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 80368FB8 00365B98  40 81 00 50 */	ble lbl_80369008
/* 80368FBC 00365B9C  FC 20 20 34 */	frsqrte f1, f4
/* 80368FC0 00365BA0  C8 62 EA 88 */	lfd f3, 0.5
/* 80368FC4 00365BA4  C8 42 EA E0 */	lfd f2, HSD_CObj_804DE4C0(r2)
/* 80368FC8 00365BA8  FC 01 00 72 */	fmul f0, f1, f1
/* 80368FCC 00365BAC  FC 23 00 72 */	fmul f1, f3, f1
/* 80368FD0 00365BB0  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80368FD4 00365BB4  FC 21 00 32 */	fmul f1, f1, f0
/* 80368FD8 00365BB8  FC 01 00 72 */	fmul f0, f1, f1
/* 80368FDC 00365BBC  FC 23 00 72 */	fmul f1, f3, f1
/* 80368FE0 00365BC0  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80368FE4 00365BC4  FC 21 00 32 */	fmul f1, f1, f0
/* 80368FE8 00365BC8  FC 01 00 72 */	fmul f0, f1, f1
/* 80368FEC 00365BCC  FC 23 00 72 */	fmul f1, f3, f1
/* 80368FF0 00365BD0  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80368FF4 00365BD4  FC 01 00 32 */	fmul f0, f1, f0
/* 80368FF8 00365BD8  FC 04 00 32 */	fmul f0, f4, f0
/* 80368FFC 00365BDC  FC 00 00 18 */	frsp f0, f0
/* 80369000 00365BE0  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 80369004 00365BE4  C0 81 00 14 */	lfs f4, 0x14(r1)
lbl_80369008:
/* 80369008 00365BE8  D0 81 00 2C */	stfs f4, 0x2c(r1)
/* 8036900C 00365BEC  C0 21 00 20 */	lfs f1, 0x20(r1)
/* 80369010 00365BF0  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 80369014 00365BF4  FC 40 08 50 */	fneg f2, f1
/* 80369018 00365BF8  C0 21 00 1C */	lfs f1, 0x1c(r1)
/* 8036901C 00365BFC  EC 02 00 24 */	fdivs f0, f2, f0
/* 80369020 00365C00  EC 01 00 32 */	fmuls f0, f1, f0
/* 80369024 00365C04  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 80369028 00365C08  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 8036902C 00365C0C  C0 21 00 24 */	lfs f1, 0x24(r1)
/* 80369030 00365C10  EC 02 00 24 */	fdivs f0, f2, f0
/* 80369034 00365C14  EC 01 00 32 */	fmuls f0, f1, f0
/* 80369038 00365C18  D0 01 00 30 */	stfs f0, 0x30(r1)
lbl_8036903C:
/* 8036903C 00365C1C  FC 20 F8 50 */	fneg f1, f31
/* 80369040 00365C20  38 61 00 40 */	addi r3, r1, 0x40
/* 80369044 00365C24  38 81 00 1C */	addi r4, r1, 0x1c
/* 80369048 00365C28  4B FD 94 E9 */	bl PSMTXRotAxisRad
/* 8036904C 00365C2C  38 61 00 40 */	addi r3, r1, 0x40
/* 80369050 00365C30  38 81 00 28 */	addi r4, r1, 0x28
/* 80369054 00365C34  38 A1 00 34 */	addi r5, r1, 0x34
/* 80369058 00365C38  4B FD 9A A5 */	bl PSMTXMultVecSR
/* 8036905C 00365C3C  38 61 00 34 */	addi r3, r1, 0x34
/* 80369060 00365C40  38 9F 00 00 */	addi r4, r31, 0
/* 80369064 00365C44  4B FD 9D 55 */	bl PSVECNormalize
/* 80369068 00365C48  38 60 00 00 */	li r3, 0
lbl_8036906C:
/* 8036906C 00365C4C  2C 03 00 00 */	cmpwi r3, 0
/* 80369070 00365C50  40 82 00 0C */	bne lbl_8036907C
/* 80369074 00365C54  38 60 00 00 */	li r3, 0
/* 80369078 00365C58  48 00 00 24 */	b lbl_8036909C
lbl_8036907C:
/* 8036907C 00365C5C  28 1F 00 00 */	cmplwi r31, 0
/* 80369080 00365C60  41 82 00 18 */	beq lbl_80369098
/* 80369084 00365C64  C0 22 EA 98 */	lfs f1, HSD_CObj_804DE478
/* 80369088 00365C68  D0 3F 00 00 */	stfs f1, 0(r31)
/* 8036908C 00365C6C  C0 02 EA 9C */	lfs f0, HSD_CObj_804DE47C(r2)
/* 80369090 00365C70  D0 1F 00 04 */	stfs f0, 4(r31)
/* 80369094 00365C74  D0 3F 00 08 */	stfs f1, 8(r31)
lbl_80369098:
/* 80369098 00365C78  38 60 FF FF */	li r3, -1
lbl_8036909C:
/* 8036909C 00365C7C  80 01 00 84 */	lwz r0, 0x84(r1)
/* 803690A0 00365C80  CB E1 00 78 */	lfd f31, 0x78(r1)
/* 803690A4 00365C84  83 E1 00 74 */	lwz r31, 0x74(r1)
/* 803690A8 00365C88  38 21 00 80 */	addi r1, r1, 0x80
/* 803690AC 00365C8C  7C 08 03 A6 */	mtlr r0
/* 803690B0 00365C90  4E 80 00 20 */	blr
} // clang-format on
#endif

#ifdef MWERKS_GEKKO
/* static */ extern const f64 HSD_CObj_804DE4A0;
/* static */ extern const f64 HSD_CObj_804DE4A8;

#pragma push
asm void HSD_CObjSetUpVector(void)
{ // clang-format off
    nofralloc
/* 803690B4 00365C94  7C 08 02 A6 */	mflr r0
/* 803690B8 00365C98  90 01 00 04 */	stw r0, 4(r1)
/* 803690BC 00365C9C  94 21 FF 58 */	stwu r1, -0xa8(r1)
/* 803690C0 00365CA0  93 E1 00 A4 */	stw r31, 0xa4(r1)
/* 803690C4 00365CA4  7C 7F 1B 79 */	or. r31, r3, r3
/* 803690C8 00365CA8  3C 60 80 40 */	lis r3, hsdCObj@ha
/* 803690CC 00365CAC  93 C1 00 A0 */	stw r30, 0xa0(r1)
/* 803690D0 00365CB0  3B C3 62 20 */	addi r30, r3, hsdCObj@l
/* 803690D4 00365CB4  93 A1 00 9C */	stw r29, 0x9c(r1)
/* 803690D8 00365CB8  3B A4 00 00 */	addi r29, r4, 0
/* 803690DC 00365CBC  41 82 01 F0 */	beq lbl_803692CC
/* 803690E0 00365CC0  28 1D 00 00 */	cmplwi r29, 0
/* 803690E4 00365CC4  40 82 00 08 */	bne lbl_803690EC
/* 803690E8 00365CC8  48 00 01 E4 */	b lbl_803692CC
lbl_803690EC:
/* 803690EC 00365CCC  80 1F 00 08 */	lwz r0, 8(r31)
/* 803690F0 00365CD0  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 803690F4 00365CD4  41 82 01 08 */	beq lbl_803691FC
/* 803690F8 00365CD8  28 1D 00 00 */	cmplwi r29, 0
/* 803690FC 00365CDC  41 82 00 08 */	beq lbl_80369104
/* 80369100 00365CE0  48 00 00 0C */	b lbl_8036910C
lbl_80369104:
/* 80369104 00365CE4  38 00 FF FF */	li r0, -1
/* 80369108 00365CE8  48 00 00 8C */	b lbl_80369194
lbl_8036910C:
/* 8036910C 00365CEC  C0 1D 00 00 */	lfs f0, 0(r29)
/* 80369110 00365CF0  C0 22 EA B8 */	lfs f1, HSD_CObj_804DE498(r2)
/* 80369114 00365CF4  D0 01 00 40 */	stfs f0, 0x40(r1)
/* 80369118 00365CF8  80 01 00 40 */	lwz r0, 0x40(r1)
/* 8036911C 00365CFC  54 00 00 7E */	clrlwi r0, r0, 1
/* 80369120 00365D00  90 01 00 40 */	stw r0, 0x40(r1)
/* 80369124 00365D04  C0 01 00 40 */	lfs f0, 0x40(r1)
/* 80369128 00365D08  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8036912C 00365D0C  4C 40 13 82 */	cror 2, 0, 2
/* 80369130 00365D10  40 82 00 54 */	bne lbl_80369184
/* 80369134 00365D14  C0 1D 00 04 */	lfs f0, 4(r29)
/* 80369138 00365D18  D0 01 00 3C */	stfs f0, 0x3c(r1)
/* 8036913C 00365D1C  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80369140 00365D20  54 00 00 7E */	clrlwi r0, r0, 1
/* 80369144 00365D24  90 01 00 3C */	stw r0, 0x3c(r1)
/* 80369148 00365D28  C0 01 00 3C */	lfs f0, 0x3c(r1)
/* 8036914C 00365D2C  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80369150 00365D30  4C 40 13 82 */	cror 2, 0, 2
/* 80369154 00365D34  40 82 00 30 */	bne lbl_80369184
/* 80369158 00365D38  C0 1D 00 08 */	lfs f0, 8(r29)
/* 8036915C 00365D3C  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 80369160 00365D40  80 01 00 38 */	lwz r0, 0x38(r1)
/* 80369164 00365D44  54 00 00 7E */	clrlwi r0, r0, 1
/* 80369168 00365D48  90 01 00 38 */	stw r0, 0x38(r1)
/* 8036916C 00365D4C  C0 01 00 38 */	lfs f0, 0x38(r1)
/* 80369170 00365D50  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80369174 00365D54  4C 40 13 82 */	cror 2, 0, 2
/* 80369178 00365D58  40 82 00 0C */	bne lbl_80369184
/* 8036917C 00365D5C  38 00 FF FF */	li r0, -1
/* 80369180 00365D60  48 00 00 14 */	b lbl_80369194
lbl_80369184:
/* 80369184 00365D64  38 7D 00 00 */	addi r3, r29, 0
/* 80369188 00365D68  38 81 00 8C */	addi r4, r1, 0x8c
/* 8036918C 00365D6C  4B FD 9C 2D */	bl PSVECNormalize
/* 80369190 00365D70  38 00 00 00 */	li r0, 0
lbl_80369194:
/* 80369194 00365D74  2C 00 00 00 */	cmpwi r0, 0
/* 80369198 00365D78  41 82 00 0C */	beq lbl_803691A4
/* 8036919C 00365D7C  3B BE 00 CC */	addi r29, r30, 0xcc
/* 803691A0 00365D80  48 00 00 08 */	b lbl_803691A8
lbl_803691A4:
/* 803691A4 00365D84  3B A1 00 8C */	addi r29, r1, 0x8c
lbl_803691A8:
/* 803691A8 00365D88  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 803691AC 00365D8C  C0 1D 00 00 */	lfs f0, 0(r29)
/* 803691B0 00365D90  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 803691B4 00365D94  40 82 00 24 */	bne lbl_803691D8
/* 803691B8 00365D98  C0 3F 00 30 */	lfs f1, 0x30(r31)
/* 803691BC 00365D9C  C0 1D 00 04 */	lfs f0, 4(r29)
/* 803691C0 00365DA0  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 803691C4 00365DA4  40 82 00 14 */	bne lbl_803691D8
/* 803691C8 00365DA8  C0 3F 00 34 */	lfs f1, 0x34(r31)
/* 803691CC 00365DAC  C0 1D 00 08 */	lfs f0, 8(r29)
/* 803691D0 00365DB0  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 803691D4 00365DB4  41 82 00 0C */	beq lbl_803691E0
lbl_803691D8:
/* 803691D8 00365DB8  7F E3 FB 78 */	mr r3, r31
/* 803691DC 00365DBC  48 00 03 89 */	bl HSD_CObjSetMtxDirty
lbl_803691E0:
/* 803691E0 00365DC0  80 7D 00 00 */	lwz r3, 0(r29)
/* 803691E4 00365DC4  80 1D 00 04 */	lwz r0, 4(r29)
/* 803691E8 00365DC8  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 803691EC 00365DCC  90 1F 00 30 */	stw r0, 0x30(r31)
/* 803691F0 00365DD0  80 1D 00 08 */	lwz r0, 8(r29)
/* 803691F4 00365DD4  90 1F 00 34 */	stw r0, 0x34(r31)
/* 803691F8 00365DD8  48 00 00 D4 */	b lbl_803692CC
lbl_803691FC:
/* 803691FC 00365DDC  38 7F 00 00 */	addi r3, r31, 0
/* 80369200 00365DE0  38 81 00 50 */	addi r4, r1, 0x50
/* 80369204 00365DE4  4B FF F6 59 */	bl HSD_CObjGetEyeVector
/* 80369208 00365DE8  2C 03 00 00 */	cmpwi r3, 0
/* 8036920C 00365DEC  41 82 00 0C */	beq lbl_80369218
/* 80369210 00365DF0  C0 22 EA 98 */	lfs f1, HSD_CObj_804DE478
/* 80369214 00365DF4  48 00 00 B0 */	b lbl_803692C4
lbl_80369218:
/* 80369218 00365DF8  38 7D 00 00 */	addi r3, r29, 0
/* 8036921C 00365DFC  38 81 00 50 */	addi r4, r1, 0x50
/* 80369220 00365E00  4B FD 9C 19 */	bl PSVECDotProduct
/* 80369224 00365E04  FC 40 0A 10 */	fabs f2, f1
/* 80369228 00365E08  C0 22 EA 9C */	lfs f1, HSD_CObj_804DE47C(r2)
/* 8036922C 00365E0C  C0 02 EA B8 */	lfs f0, HSD_CObj_804DE498(r2)
/* 80369230 00365E10  EC 21 10 28 */	fsubs f1, f1, f2
/* 80369234 00365E14  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80369238 00365E18  40 80 00 0C */	bge lbl_80369244
/* 8036923C 00365E1C  C0 22 EA 98 */	lfs f1, HSD_CObj_804DE478
/* 80369240 00365E20  48 00 00 84 */	b lbl_803692C4
lbl_80369244:
/* 80369244 00365E24  38 61 00 5C */	addi r3, r1, 0x5c
/* 80369248 00365E28  38 9E 00 B4 */	addi r4, r30, 0xb4
/* 8036924C 00365E2C  38 BE 00 C0 */	addi r5, r30, 0xc0
/* 80369250 00365E30  38 C1 00 50 */	addi r6, r1, 0x50
/* 80369254 00365E34  4B FD 94 E1 */	bl C_MTXLookAt
/* 80369258 00365E38  38 9D 00 00 */	addi r4, r29, 0
/* 8036925C 00365E3C  38 61 00 5C */	addi r3, r1, 0x5c
/* 80369260 00365E40  38 A1 00 44 */	addi r5, r1, 0x44
/* 80369264 00365E44  4B FD 98 99 */	bl PSMTXMultVecSR
/* 80369268 00365E48  C0 01 00 48 */	lfs f0, 0x48(r1)
/* 8036926C 00365E4C  C0 22 EA 98 */	lfs f1, HSD_CObj_804DE478
/* 80369270 00365E50  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 80369274 00365E54  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80369278 00365E58  54 00 00 7E */	clrlwi r0, r0, 1
/* 8036927C 00365E5C  90 01 00 34 */	stw r0, 0x34(r1)
/* 80369280 00365E60  C0 01 00 34 */	lfs f0, 0x34(r1)
/* 80369284 00365E64  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80369288 00365E68  40 82 00 2C */	bne lbl_803692B4
/* 8036928C 00365E6C  C0 01 00 44 */	lfs f0, 0x44(r1)
/* 80369290 00365E70  FC 00 00 50 */	fneg f0, f0
/* 80369294 00365E74  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80369298 00365E78  4C 41 13 82 */	cror 2, 1, 2
/* 8036929C 00365E7C  40 82 00 0C */	bne lbl_803692A8
/* 803692A0 00365E80  C8 02 EA C0 */	lfd f0, HSD_CObj_804DE4A0(r2)
/* 803692A4 00365E84  48 00 00 08 */	b lbl_803692AC
lbl_803692A8:
/* 803692A8 00365E88  C8 02 EA C8 */	lfd f0, HSD_CObj_804DE4A8(r2)
lbl_803692AC:
/* 803692AC 00365E8C  FC 20 00 18 */	frsp f1, f0
/* 803692B0 00365E90  48 00 00 14 */	b lbl_803692C4
lbl_803692B4:
/* 803692B4 00365E94  C0 01 00 44 */	lfs f0, 0x44(r1)
/* 803692B8 00365E98  C0 41 00 48 */	lfs f2, 0x48(r1)
/* 803692BC 00365E9C  FC 20 00 50 */	fneg f1, f0
/* 803692C0 00365EA0  4B CB 99 71 */	bl atan2f
lbl_803692C4:
/* 803692C4 00365EA4  7F E3 FB 78 */	mr r3, r31
/* 803692C8 00365EA8  48 00 06 F9 */	bl HSD_CObjSetRoll
lbl_803692CC:
/* 803692CC 00365EAC  80 01 00 AC */	lwz r0, 0xac(r1)
/* 803692D0 00365EB0  83 E1 00 A4 */	lwz r31, 0xa4(r1)
/* 803692D4 00365EB4  83 C1 00 A0 */	lwz r30, 0xa0(r1)
/* 803692D8 00365EB8  83 A1 00 9C */	lwz r29, 0x9c(r1)
/* 803692DC 00365EBC  38 21 00 A8 */	addi r1, r1, 0xa8
/* 803692E0 00365EC0  7C 08 03 A6 */	mtlr r0
/* 803692E4 00365EC4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
asm void HSD_CObjGetLeftVector(UNK_PARAMS)
{ // clang-format off
    nofralloc
/* 803692E8 00365EC8  7C 08 02 A6 */	mflr r0
/* 803692EC 00365ECC  90 01 00 04 */	stw r0, 4(r1)
/* 803692F0 00365ED0  94 21 FF 88 */	stwu r1, -0x78(r1)
/* 803692F4 00365ED4  93 E1 00 74 */	stw r31, 0x74(r1)
/* 803692F8 00365ED8  3B E4 00 00 */	addi r31, r4, 0
/* 803692FC 00365EDC  93 C1 00 70 */	stw r30, 0x70(r1)
/* 80369300 00365EE0  7C 7E 1B 79 */	or. r30, r3, r3
/* 80369304 00365EE4  41 82 02 28 */	beq lbl_8036952C
/* 80369308 00365EE8  28 1F 00 00 */	cmplwi r31, 0
/* 8036930C 00365EEC  41 82 02 20 */	beq lbl_8036952C
/* 80369310 00365EF0  28 1E 00 00 */	cmplwi r30, 0
/* 80369314 00365EF4  41 82 00 C0 */	beq lbl_803693D4
/* 80369318 00365EF8  80 1E 00 24 */	lwz r0, 0x24(r30)
/* 8036931C 00365EFC  28 00 00 00 */	cmplwi r0, 0
/* 80369320 00365F00  41 82 00 B4 */	beq lbl_803693D4
/* 80369324 00365F04  80 1E 00 28 */	lwz r0, 0x28(r30)
/* 80369328 00365F08  28 00 00 00 */	cmplwi r0, 0
/* 8036932C 00365F0C  41 82 00 A8 */	beq lbl_803693D4
/* 80369330 00365F10  28 1E 00 00 */	cmplwi r30, 0
/* 80369334 00365F14  40 82 00 14 */	bne lbl_80369348
/* 80369338 00365F18  38 6D A6 A0 */	addi r3, r13, HSD_CObj_804D5D40
/* 8036933C 00365F1C  38 80 02 DD */	li r4, 0x2dd
/* 80369340 00365F20  38 AD A6 A8 */	addi r5, r13, HSD_CObj_804D5D48
/* 80369344 00365F24  48 01 EE DD */	bl __assert
lbl_80369348:
/* 80369348 00365F28  28 1E 00 00 */	cmplwi r30, 0
/* 8036934C 00365F2C  40 82 00 14 */	bne lbl_80369360
/* 80369350 00365F30  38 6D A6 A0 */	addi r3, r13, HSD_CObj_804D5D40
/* 80369354 00365F34  38 80 02 AD */	li r4, 0x2ad
/* 80369358 00365F38  38 AD A6 A8 */	addi r5, r13, HSD_CObj_804D5D48
/* 8036935C 00365F3C  48 01 EE C5 */	bl __assert
lbl_80369360:
/* 80369360 00365F40  80 7E 00 24 */	lwz r3, 0x24(r30)
/* 80369364 00365F44  38 81 00 3C */	addi r4, r1, 0x3c
/* 80369368 00365F48  48 01 43 B9 */	bl HSD_WObjGetPosition
/* 8036936C 00365F4C  28 1E 00 00 */	cmplwi r30, 0
/* 80369370 00365F50  40 82 00 14 */	bne lbl_80369384
/* 80369374 00365F54  38 6D A6 A0 */	addi r3, r13, HSD_CObj_804D5D40
/* 80369378 00365F58  38 80 02 C5 */	li r4, 0x2c5
/* 8036937C 00365F5C  38 AD A6 A8 */	addi r5, r13, HSD_CObj_804D5D48
/* 80369380 00365F60  48 01 EE A1 */	bl __assert
lbl_80369384:
/* 80369384 00365F64  28 1E 00 00 */	cmplwi r30, 0
/* 80369388 00365F68  40 82 00 14 */	bne lbl_8036939C
/* 8036938C 00365F6C  38 6D A6 A0 */	addi r3, r13, HSD_CObj_804D5D40
/* 80369390 00365F70  38 80 02 95 */	li r4, 0x295
/* 80369394 00365F74  38 AD A6 A8 */	addi r5, r13, HSD_CObj_804D5D48
/* 80369398 00365F78  48 01 EE 89 */	bl __assert
lbl_8036939C:
/* 8036939C 00365F7C  80 7E 00 28 */	lwz r3, 0x28(r30)
/* 803693A0 00365F80  38 81 00 48 */	addi r4, r1, 0x48
/* 803693A4 00365F84  48 01 43 7D */	bl HSD_WObjGetPosition
/* 803693A8 00365F88  38 61 00 48 */	addi r3, r1, 0x48
/* 803693AC 00365F8C  38 81 00 3C */	addi r4, r1, 0x3c
/* 803693B0 00365F90  38 A1 00 60 */	addi r5, r1, 0x60
/* 803693B4 00365F94  4B FD 99 C5 */	bl PSVECSubtract
/* 803693B8 00365F98  38 61 00 60 */	addi r3, r1, 0x60
/* 803693BC 00365F9C  38 83 00 00 */	addi r4, r3, 0
/* 803693C0 00365FA0  4B FF F7 4D */	bl vec_normalize_check
/* 803693C4 00365FA4  2C 03 00 00 */	cmpwi r3, 0
/* 803693C8 00365FA8  40 82 00 0C */	bne lbl_803693D4
/* 803693CC 00365FAC  38 00 00 00 */	li r0, 0
/* 803693D0 00365FB0  48 00 00 1C */	b lbl_803693EC
lbl_803693D4:
/* 803693D4 00365FB4  C0 22 EA 98 */	lfs f1, HSD_CObj_804DE478
/* 803693D8 00365FB8  38 00 FF FF */	li r0, -1
/* 803693DC 00365FBC  C0 02 EA B4 */	lfs f0, HSD_CObj_804DE494(r2)
/* 803693E0 00365FC0  D0 21 00 60 */	stfs f1, 0x60(r1)
/* 803693E4 00365FC4  D0 21 00 64 */	stfs f1, 0x64(r1)
/* 803693E8 00365FC8  D0 01 00 68 */	stfs f0, 0x68(r1)
lbl_803693EC:
/* 803693EC 00365FCC  2C 00 00 00 */	cmpwi r0, 0
/* 803693F0 00365FD0  40 82 01 3C */	bne lbl_8036952C
/* 803693F4 00365FD4  28 1E 00 00 */	cmplwi r30, 0
/* 803693F8 00365FD8  41 82 00 58 */	beq lbl_80369450
/* 803693FC 00365FDC  34 01 00 54 */	addic. r0, r1, 0x54
/* 80369400 00365FE0  41 82 00 50 */	beq lbl_80369450
/* 80369404 00365FE4  80 1E 00 08 */	lwz r0, 8(r30)
/* 80369408 00365FE8  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8036940C 00365FEC  41 82 00 24 */	beq lbl_80369430
/* 80369410 00365FF0  80 7E 00 2C */	lwz r3, 0x2c(r30)
/* 80369414 00365FF4  38 80 00 00 */	li r4, 0
/* 80369418 00365FF8  80 1E 00 30 */	lwz r0, 0x30(r30)
/* 8036941C 00365FFC  90 61 00 54 */	stw r3, 0x54(r1)
/* 80369420 00366000  90 01 00 58 */	stw r0, 0x58(r1)
/* 80369424 00366004  80 1E 00 34 */	lwz r0, 0x34(r30)
/* 80369428 00366008  90 01 00 5C */	stw r0, 0x5c(r1)
/* 8036942C 0036600C  48 00 00 3C */	b lbl_80369468
lbl_80369430:
/* 80369430 00366010  C0 3E 00 2C */	lfs f1, 0x2c(r30)
/* 80369434 00366014  38 7E 00 00 */	addi r3, r30, 0
/* 80369438 00366018  38 81 00 54 */	addi r4, r1, 0x54
/* 8036943C 0036601C  4B FF F7 85 */	bl roll2upvec
/* 80369440 00366020  2C 03 00 00 */	cmpwi r3, 0
/* 80369444 00366024  40 82 00 0C */	bne lbl_80369450
/* 80369448 00366028  38 80 00 00 */	li r4, 0
/* 8036944C 0036602C  48 00 00 1C */	b lbl_80369468
lbl_80369450:
/* 80369450 00366030  C0 22 EA 98 */	lfs f1, HSD_CObj_804DE478
/* 80369454 00366034  38 80 FF FF */	li r4, -1
/* 80369458 00366038  C0 02 EA 9C */	lfs f0, HSD_CObj_804DE47C(r2)
/* 8036945C 0036603C  D0 21 00 54 */	stfs f1, 0x54(r1)
/* 80369460 00366040  D0 01 00 58 */	stfs f0, 0x58(r1)
/* 80369464 00366044  D0 21 00 5C */	stfs f1, 0x5c(r1)
lbl_80369468:
/* 80369468 00366048  2C 04 00 00 */	cmpwi r4, 0
/* 8036946C 0036604C  40 82 00 C0 */	bne lbl_8036952C
/* 80369470 00366050  38 BF 00 00 */	addi r5, r31, 0
/* 80369474 00366054  38 61 00 54 */	addi r3, r1, 0x54
/* 80369478 00366058  38 81 00 60 */	addi r4, r1, 0x60
/* 8036947C 0036605C  4B FD 99 DD */	bl PSVECCrossProduct
/* 80369480 00366060  28 1F 00 00 */	cmplwi r31, 0
/* 80369484 00366064  41 82 00 08 */	beq lbl_8036948C
/* 80369488 00366068  40 82 00 0C */	bne lbl_80369494
lbl_8036948C:
/* 8036948C 0036606C  38 00 FF FF */	li r0, -1
/* 80369490 00366070  48 00 00 8C */	b lbl_8036951C
lbl_80369494:
/* 80369494 00366074  C0 1F 00 00 */	lfs f0, 0(r31)
/* 80369498 00366078  C0 22 EA B8 */	lfs f1, HSD_CObj_804DE498(r2)
/* 8036949C 0036607C  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 803694A0 00366080  80 01 00 38 */	lwz r0, 0x38(r1)
/* 803694A4 00366084  54 00 00 7E */	clrlwi r0, r0, 1
/* 803694A8 00366088  90 01 00 38 */	stw r0, 0x38(r1)
/* 803694AC 0036608C  C0 01 00 38 */	lfs f0, 0x38(r1)
/* 803694B0 00366090  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 803694B4 00366094  4C 40 13 82 */	cror 2, 0, 2
/* 803694B8 00366098  40 82 00 54 */	bne lbl_8036950C
/* 803694BC 0036609C  C0 1F 00 04 */	lfs f0, 4(r31)
/* 803694C0 003660A0  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 803694C4 003660A4  80 01 00 34 */	lwz r0, 0x34(r1)
/* 803694C8 003660A8  54 00 00 7E */	clrlwi r0, r0, 1
/* 803694CC 003660AC  90 01 00 34 */	stw r0, 0x34(r1)
/* 803694D0 003660B0  C0 01 00 34 */	lfs f0, 0x34(r1)
/* 803694D4 003660B4  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 803694D8 003660B8  4C 40 13 82 */	cror 2, 0, 2
/* 803694DC 003660BC  40 82 00 30 */	bne lbl_8036950C
/* 803694E0 003660C0  C0 1F 00 08 */	lfs f0, 8(r31)
/* 803694E4 003660C4  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 803694E8 003660C8  80 01 00 30 */	lwz r0, 0x30(r1)
/* 803694EC 003660CC  54 00 00 7E */	clrlwi r0, r0, 1
/* 803694F0 003660D0  90 01 00 30 */	stw r0, 0x30(r1)
/* 803694F4 003660D4  C0 01 00 30 */	lfs f0, 0x30(r1)
/* 803694F8 003660D8  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 803694FC 003660DC  4C 40 13 82 */	cror 2, 0, 2
/* 80369500 003660E0  40 82 00 0C */	bne lbl_8036950C
/* 80369504 003660E4  38 00 FF FF */	li r0, -1
/* 80369508 003660E8  48 00 00 14 */	b lbl_8036951C
lbl_8036950C:
/* 8036950C 003660EC  38 7F 00 00 */	addi r3, r31, 0
/* 80369510 003660F0  38 9F 00 00 */	addi r4, r31, 0
/* 80369514 003660F4  4B FD 98 A5 */	bl PSVECNormalize
/* 80369518 003660F8  38 00 00 00 */	li r0, 0
lbl_8036951C:
/* 8036951C 003660FC  2C 00 00 00 */	cmpwi r0, 0
/* 80369520 00366100  40 82 00 0C */	bne lbl_8036952C
/* 80369524 00366104  38 60 00 00 */	li r3, 0
/* 80369528 00366108  48 00 00 24 */	b lbl_8036954C
lbl_8036952C:
/* 8036952C 0036610C  28 1F 00 00 */	cmplwi r31, 0
/* 80369530 00366110  41 82 00 18 */	beq lbl_80369548
/* 80369534 00366114  C0 02 EA 9C */	lfs f0, HSD_CObj_804DE47C(r2)
/* 80369538 00366118  D0 1F 00 00 */	stfs f0, 0(r31)
/* 8036953C 0036611C  C0 02 EA 98 */	lfs f0, HSD_CObj_804DE478
/* 80369540 00366120  D0 1F 00 04 */	stfs f0, 4(r31)
/* 80369544 00366124  D0 1F 00 08 */	stfs f0, 8(r31)
lbl_80369548:
/* 80369548 00366128  38 60 FF FF */	li r3, -1
lbl_8036954C:
/* 8036954C 0036612C  80 01 00 7C */	lwz r0, 0x7c(r1)
/* 80369550 00366130  83 E1 00 74 */	lwz r31, 0x74(r1)
/* 80369554 00366134  83 C1 00 70 */	lwz r30, 0x70(r1)
/* 80369558 00366138  38 21 00 78 */	addi r1, r1, 0x78
/* 8036955C 0036613C  7C 08 03 A6 */	mtlr r0
/* 80369560 00366140  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

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

MtxPtr HSD_CObjGetViewingMtxPtr(HSD_CObj* cobj)
{
#ifndef MUST_MATCH
    HSD_CObjSetupViewingMtx(cobj);
#else
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

MtxPtr HSD_CObjGetInvViewingMtxPtr(HSD_CObj* cobj)
{
#ifndef MUST_MATCH
    HSD_CObjGetViewingMtxPtr(cobj);
#else
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

#ifdef MWERKS_GEKKO
#pragma push
asm void HSD_CObjSetRoll(HSD_CObj* cobj, float)
{
    // clang-format off
    nofralloc
/* 803699C0 003665A0  7C 08 02 A6 */	mflr r0
/* 803699C4 003665A4  90 01 00 04 */	stw r0, 4(r1)
/* 803699C8 003665A8  94 21 FF 70 */	stwu r1, -0x90(r1)
/* 803699CC 003665AC  DB E1 00 88 */	stfd f31, 0x88(r1)
/* 803699D0 003665B0  FF E0 08 90 */	fmr f31, f1
/* 803699D4 003665B4  93 E1 00 84 */	stw r31, 0x84(r1)
/* 803699D8 003665B8  7C 7F 1B 79 */	or. r31, r3, r3
/* 803699DC 003665BC  41 82 01 D4 */	beq lbl_80369BB0
/* 803699E0 003665C0  80 7F 00 08 */	lwz r3, 8(r31)
/* 803699E4 003665C4  54 60 07 FF */	clrlwi. r0, r3, 0x1f
/* 803699E8 003665C8  41 82 01 B0 */	beq lbl_80369B98
/* 803699EC 003665CC  38 7F 00 00 */	addi r3, r31, 0
/* 803699F0 003665D0  38 81 00 1C */	addi r4, r1, 0x1c
/* 803699F4 003665D4  4B FF EE 69 */	bl HSD_CObjGetEyeVector
/* 803699F8 003665D8  2C 03 00 00 */	cmpwi r3, 0
/* 803699FC 003665DC  40 82 01 8C */	bne lbl_80369B88
/* 80369A00 003665E0  C0 41 00 20 */	lfs f2, 0x20(r1)
/* 80369A04 003665E4  C8 22 EA D0 */	lfd f1, HSD_CObj_804DE4B0(r2)
/* 80369A08 003665E8  FC 60 12 10 */	fabs f3, f2
/* 80369A0C 003665EC  C8 02 EA D8 */	lfd f0, HSD_CObj_804DE4B8(r2)
/* 80369A10 003665F0  FC 21 18 28 */	fsub f1, f1, f3
/* 80369A14 003665F4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80369A18 003665F8  40 80 00 A4 */	bge lbl_80369ABC
/* 80369A1C 003665FC  C0 21 00 24 */	lfs f1, 0x24(r1)
/* 80369A20 00366600  EC 42 00 B2 */	fmuls f2, f2, f2
/* 80369A24 00366604  C0 02 EA 98 */	lfs f0, HSD_CObj_804DE478
/* 80369A28 00366608  EC 21 00 72 */	fmuls f1, f1, f1
/* 80369A2C 0036660C  EC 82 08 2A */	fadds f4, f2, f1
/* 80369A30 00366610  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 80369A34 00366614  40 81 00 50 */	ble lbl_80369A84
/* 80369A38 00366618  FC 20 20 34 */	frsqrte f1, f4
/* 80369A3C 0036661C  C8 62 EA 88 */	lfd f3, 0.5
/* 80369A40 00366620  C8 42 EA E0 */	lfd f2, HSD_CObj_804DE4C0(r2)
/* 80369A44 00366624  FC 01 00 72 */	fmul f0, f1, f1
/* 80369A48 00366628  FC 23 00 72 */	fmul f1, f3, f1
/* 80369A4C 0036662C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80369A50 00366630  FC 21 00 32 */	fmul f1, f1, f0
/* 80369A54 00366634  FC 01 00 72 */	fmul f0, f1, f1
/* 80369A58 00366638  FC 23 00 72 */	fmul f1, f3, f1
/* 80369A5C 0036663C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80369A60 00366640  FC 21 00 32 */	fmul f1, f1, f0
/* 80369A64 00366644  FC 01 00 72 */	fmul f0, f1, f1
/* 80369A68 00366648  FC 23 00 72 */	fmul f1, f3, f1
/* 80369A6C 0036664C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80369A70 00366650  FC 01 00 32 */	fmul f0, f1, f0
/* 80369A74 00366654  FC 04 00 32 */	fmul f0, f4, f0
/* 80369A78 00366658  FC 00 00 18 */	frsp f0, f0
/* 80369A7C 0036665C  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 80369A80 00366660  C0 81 00 18 */	lfs f4, 0x18(r1)
lbl_80369A84:
/* 80369A84 00366664  C0 01 00 1C */	lfs f0, 0x1c(r1)
/* 80369A88 00366668  D0 81 00 28 */	stfs f4, 0x28(r1)
/* 80369A8C 0036666C  FC 40 00 50 */	fneg f2, f0
/* 80369A90 00366670  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 80369A94 00366674  C0 21 00 20 */	lfs f1, 0x20(r1)
/* 80369A98 00366678  EC 02 00 24 */	fdivs f0, f2, f0
/* 80369A9C 0036667C  EC 01 00 32 */	fmuls f0, f1, f0
/* 80369AA0 00366680  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 80369AA4 00366684  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 80369AA8 00366688  C0 21 00 24 */	lfs f1, 0x24(r1)
/* 80369AAC 0036668C  EC 02 00 24 */	fdivs f0, f2, f0
/* 80369AB0 00366690  EC 01 00 32 */	fmuls f0, f1, f0
/* 80369AB4 00366694  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 80369AB8 00366698  48 00 00 A4 */	b lbl_80369B5C
lbl_80369ABC:
/* 80369ABC 0036669C  C0 01 00 1C */	lfs f0, 0x1c(r1)
/* 80369AC0 003666A0  C0 21 00 24 */	lfs f1, 0x24(r1)
/* 80369AC4 003666A4  EC 40 00 32 */	fmuls f2, f0, f0
/* 80369AC8 003666A8  C0 02 EA 98 */	lfs f0, HSD_CObj_804DE478
/* 80369ACC 003666AC  EC 21 00 72 */	fmuls f1, f1, f1
/* 80369AD0 003666B0  EC 82 08 2A */	fadds f4, f2, f1
/* 80369AD4 003666B4  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 80369AD8 003666B8  40 81 00 50 */	ble lbl_80369B28
/* 80369ADC 003666BC  FC 20 20 34 */	frsqrte f1, f4
/* 80369AE0 003666C0  C8 62 EA 88 */	lfd f3, 0.5
/* 80369AE4 003666C4  C8 42 EA E0 */	lfd f2, HSD_CObj_804DE4C0(r2)
/* 80369AE8 003666C8  FC 01 00 72 */	fmul f0, f1, f1
/* 80369AEC 003666CC  FC 23 00 72 */	fmul f1, f3, f1
/* 80369AF0 003666D0  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80369AF4 003666D4  FC 21 00 32 */	fmul f1, f1, f0
/* 80369AF8 003666D8  FC 01 00 72 */	fmul f0, f1, f1
/* 80369AFC 003666DC  FC 23 00 72 */	fmul f1, f3, f1
/* 80369B00 003666E0  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80369B04 003666E4  FC 21 00 32 */	fmul f1, f1, f0
/* 80369B08 003666E8  FC 01 00 72 */	fmul f0, f1, f1
/* 80369B0C 003666EC  FC 23 00 72 */	fmul f1, f3, f1
/* 80369B10 003666F0  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80369B14 003666F4  FC 01 00 32 */	fmul f0, f1, f0
/* 80369B18 003666F8  FC 04 00 32 */	fmul f0, f4, f0
/* 80369B1C 003666FC  FC 00 00 18 */	frsp f0, f0
/* 80369B20 00366700  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 80369B24 00366704  C0 81 00 14 */	lfs f4, 0x14(r1)
lbl_80369B28:
/* 80369B28 00366708  D0 81 00 2C */	stfs f4, 0x2c(r1)
/* 80369B2C 0036670C  C0 21 00 20 */	lfs f1, 0x20(r1)
/* 80369B30 00366710  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 80369B34 00366714  FC 40 08 50 */	fneg f2, f1
/* 80369B38 00366718  C0 21 00 1C */	lfs f1, 0x1c(r1)
/* 80369B3C 0036671C  EC 02 00 24 */	fdivs f0, f2, f0
/* 80369B40 00366720  EC 01 00 32 */	fmuls f0, f1, f0
/* 80369B44 00366724  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 80369B48 00366728  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 80369B4C 0036672C  C0 21 00 24 */	lfs f1, 0x24(r1)
/* 80369B50 00366730  EC 02 00 24 */	fdivs f0, f2, f0
/* 80369B54 00366734  EC 01 00 32 */	fmuls f0, f1, f0
/* 80369B58 00366738  D0 01 00 30 */	stfs f0, 0x30(r1)
lbl_80369B5C:
/* 80369B5C 0036673C  FC 20 F8 50 */	fneg f1, f31
/* 80369B60 00366740  38 61 00 40 */	addi r3, r1, 0x40
/* 80369B64 00366744  38 81 00 1C */	addi r4, r1, 0x1c
/* 80369B68 00366748  4B FD 89 C9 */	bl PSMTXRotAxisRad
/* 80369B6C 0036674C  38 61 00 40 */	addi r3, r1, 0x40
/* 80369B70 00366750  38 81 00 28 */	addi r4, r1, 0x28
/* 80369B74 00366754  38 A1 00 34 */	addi r5, r1, 0x34
/* 80369B78 00366758  4B FD 8F 85 */	bl PSMTXMultVecSR
/* 80369B7C 0036675C  38 61 00 34 */	addi r3, r1, 0x34
/* 80369B80 00366760  38 81 00 70 */	addi r4, r1, 0x70
/* 80369B84 00366764  4B FD 92 35 */	bl PSVECNormalize
lbl_80369B88:
/* 80369B88 00366768  38 7F 00 00 */	addi r3, r31, 0
/* 80369B8C 0036676C  38 81 00 70 */	addi r4, r1, 0x70
/* 80369B90 00366770  4B FF F5 25 */	bl HSD_CObjSetUpVector
/* 80369B94 00366774  48 00 00 1C */	b lbl_80369BB0
lbl_80369B98:
/* 80369B98 00366778  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 80369B9C 0036677C  FC 00 F8 00 */	fcmpu cr0, f0, f31
/* 80369BA0 00366780  41 82 00 0C */	beq lbl_80369BAC
/* 80369BA4 00366784  64 60 C0 00 */	oris r0, r3, 0xc000
/* 80369BA8 00366788  90 1F 00 08 */	stw r0, 8(r31)
lbl_80369BAC:
/* 80369BAC 0036678C  D3 FF 00 2C */	stfs f31, 0x2c(r31)
lbl_80369BB0:
/* 80369BB0 00366790  80 01 00 94 */	lwz r0, 0x94(r1)
/* 80369BB4 00366794  CB E1 00 88 */	lfd f31, 0x88(r1)
/* 80369BB8 00366798  83 E1 00 84 */	lwz r31, 0x84(r1)
/* 80369BBC 0036679C  38 21 00 90 */	addi r1, r1, 0x90
/* 80369BC0 003667A0  7C 08 03 A6 */	mtlr r0
/* 80369BC4 003667A4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

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
    case 1:
        result =
            cobj->near * tanf(0.5F * (HSD_CObj_804DE474 *
                                      cobj->projection_param.perspective.fov));
        break;
    case 2:
        result = cobj->projection_param.perspective.fov;
        break;
    case 3:
        result = cobj->projection_param.perspective.fov;
        break;
    default:
        result = HSD_CObj_804DE478;
        break;
    }
    return result;
}

#ifndef MUST_MATCH
void HSD_CObjSetTop(HSD_CObj* cobj, float top)
{
    if (cobj == NULL) {
        return;
    }
    switch (cobj->projection_type) {
    case 2:
        cobj->projection_param.perspective.fov = top;
        break;
    case 3:
        cobj->projection_param.perspective.fov = top;
        break;
    }
}
#else
#pragma push
asm void HSD_CObjSetTop(HSD_CObj* cobj, float top)
{
    // clang-format off
    nofralloc
/* 80369CE4 003668C4  28 03 00 00 */	cmplwi r3, 0
/* 80369CE8 003668C8  4D 82 00 20 */	beqlr
/* 80369CEC 003668CC  88 03 00 50 */	lbz r0, 0x50(r3)
/* 80369CF0 003668D0  2C 00 00 02 */	cmpwi r0, 2
/* 80369CF4 003668D4  41 82 00 14 */	beq lbl_80369D08
/* 80369CF8 003668D8  4D 80 00 20 */	bltlr
/* 80369CFC 003668DC  2C 00 00 04 */	cmpwi r0, 4
/* 80369D00 003668E0  4C 80 00 20 */	bgelr
/* 80369D04 003668E4  48 00 00 0C */	b lbl_80369D10
lbl_80369D08:
/* 80369D08 003668E8  D0 23 00 40 */	stfs f1, 0x40(r3)
/* 80369D0C 003668EC  4E 80 00 20 */	blr
lbl_80369D10:
/* 80369D10 003668F0  D0 23 00 40 */	stfs f1, 0x40(r3)
/* 80369D14 003668F4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

float HSD_CObjGetBottom(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return HSD_CObj_804DE478;
    }
    switch (cobj->projection_type) {
    case 1:
        return -cobj->near *
               tanf(0.5F * (HSD_CObj_804DE474 *
                            cobj->projection_param.perspective.fov));
    case 2:
        return cobj->projection_param.perspective.aspect;
    case 3:
        return cobj->projection_param.perspective.aspect;
    default:
        return HSD_CObj_804DE478;
    }
}

#ifndef MUST_MATCH
void HSD_CObjSetBottom(HSD_CObj* cobj, float bottom)
{
    if (cobj == NULL) {
        return;
    }
    switch (cobj->projection_type) {
    case 2:
        cobj->projection_param.perspective.aspect = bottom;
        break;
    case 3:
        cobj->projection_param.perspective.aspect = bottom;
        break;
    }
}
#else
#pragma push
asm void HSD_CObjSetBottom(HSD_CObj* cobj, float bottom)
{
    // clang-format off
    nofralloc
/* 80369DB0 00366990  28 03 00 00 */    cmplwi r3, 0
/* 80369DB4 00366994  4D 82 00 20 */    beqlr
/* 80369DB8 00366998  88 03 00 50 */    lbz r0, 0x50(r3)
/* 80369DBC 0036699C  2C 00 00 02 */    cmpwi r0, 2
/* 80369DC0 003669A0  41 82 00 14 */    beq lbl_80369DD4
/* 80369DC4 003669A4  4D 80 00 20 */    bltlr
/* 80369DC8 003669A8  2C 00 00 04 */    cmpwi r0, 4
/* 80369DCC 003669AC  4C 80 00 20 */    bgelr
/* 80369DD0 003669B0  48 00 00 0C */    b lbl_80369DDC
lbl_80369DD4:
/* 80369DD4 003669B4  D0 23 00 44 */    stfs f1, 0x44(r3)
/* 80369DD8 003669B8  4E 80 00 20 */    blr
lbl_80369DDC:
/* 80369DDC 003669BC  D0 23 00 44 */    stfs f1, 0x44(r3)
/* 80369DE0 003669C0  4E 80 00 20 */    blr
} // clang-format on
#pragma pop
#endif

float HSD_CObjGetLeft(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return HSD_CObj_804DE478;
    }
    switch (cobj->projection_type) {
    case 1:
        return cobj->projection_param.perspective.aspect *
               (-cobj->near *
                tanf(0.5F * (HSD_CObj_804DE474 *
                             cobj->projection_param.perspective.fov)));
    case 2:
        return cobj->projection_param.frustum.left;
    case 3:
        return cobj->projection_param.frustum.left;
    default:
        return HSD_CObj_804DE478;
    }
}

#ifndef MUST_MATCH
void HSD_CObjSetLeft(HSD_CObj* cobj, float left)
{
    if (cobj != NULL) {
        return;
    }
    switch (cobj->projection_type) {
    case 2:
        cobj->projection_param.frustum.left = left;
        break;
    case 3:
        cobj->projection_param.frustum.left = left;
        break;
    }
}
#else
#pragma push
asm void HSD_CObjSetLeft(HSD_CObj* cobj, float left)
{
    // clang-format off
    nofralloc
/* 80369E84 00366A64  28 03 00 00 */    cmplwi r3, 0
/* 80369E88 00366A68  4D 82 00 20 */    beqlr
/* 80369E8C 00366A6C  88 03 00 50 */    lbz r0, 0x50(r3)
/* 80369E90 00366A70  2C 00 00 02 */    cmpwi r0, 2
/* 80369E94 00366A74  41 82 00 14 */    beq lbl_80369EA8
/* 80369E98 00366A78  4D 80 00 20 */    bltlr
/* 80369E9C 00366A7C  2C 00 00 04 */    cmpwi r0, 4
/* 80369EA0 00366A80  4C 80 00 20 */    bgelr
/* 80369EA4 00366A84  48 00 00 0C */    b lbl_80369EB0
lbl_80369EA8:
/* 80369EA8 00366A88  D0 23 00 48 */    stfs f1, 0x48(r3)
/* 80369EAC 00366A8C  4E 80 00 20 */    blr
lbl_80369EB0:
/* 80369EB0 00366A90  D0 23 00 48 */    stfs f1, 0x48(r3)
/* 80369EB4 00366A94  4E 80 00 20 */    blr
} // clang-format on
#pragma pop
#endif

float HSD_CObjGetRight(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return HSD_CObj_804DE478;
    }
    switch (cobj->projection_type) {
    case 1:
        return cobj->projection_param.perspective.aspect *
               (cobj->near *
                tanf(0.5F * (HSD_CObj_804DE474 *
                             cobj->projection_param.perspective.fov)));
    case 2:
        return cobj->projection_param.frustum.right;
    case 3:
        return cobj->projection_param.frustum.right;
    default:
        return HSD_CObj_804DE478;
    }
}

const float HSD_CObj_804DE474 = 0.01745329252F;

#ifndef MUST_MATCH
void HSD_CObjSetRight(HSD_CObj* cobj, float right)
{
    if (cobj != NULL) {
        return;
    }
    switch (cobj->projection_type) {
    case 2:
        cobj->projection_param.frustum.right = right;
        break;
    case 3:
        cobj->projection_param.frustum.right = right;
        break;
    }
}
#else
#pragma push
asm void HSD_CObjSetRight(HSD_CObj* cobj, float right)
{
    // clang-format off
    nofralloc
/* 80369F54 00366B34  28 03 00 00 */	cmplwi r3, 0
/* 80369F58 00366B38  4D 82 00 20 */	beqlr
/* 80369F5C 00366B3C  88 03 00 50 */	lbz r0, 0x50(r3)
/* 80369F60 00366B40  2C 00 00 02 */	cmpwi r0, 2
/* 80369F64 00366B44  41 82 00 14 */	beq lbl_80369F78
/* 80369F68 00366B48  4D 80 00 20 */	bltlr
/* 80369F6C 00366B4C  2C 00 00 04 */	cmpwi r0, 4
/* 80369F70 00366B50  4C 80 00 20 */	bgelr
/* 80369F74 00366B54  48 00 00 0C */	b lbl_80369F80
lbl_80369F78:
/* 80369F78 00366B58  D0 23 00 4C */	stfs f1, 0x4c(r3)
/* 80369F7C 00366B5C  4E 80 00 20 */	blr
lbl_80369F80:
/* 80369F80 00366B60  D0 23 00 4C */	stfs f1, 0x4c(r3)
/* 80369F84 00366B64  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

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

#ifdef MWERKS_GEKKO
static const float HSD_CObj_804DE478 = 0.0F;
static const float HSD_CObj_804DE47C = 1.0F;
#endif

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
#ifndef MUST_MATCH
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
#else
#pragma push
asm void HSD_CObjSetViewport(HSD_CObj* cobj, s16* viewport)
{ // clang-format off
    nofralloc
/* 8036A058 00366C38  28 03 00 00 */	cmplwi r3, 0
/* 8036A05C 00366C3C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8036A060 00366C40  41 82 00 7C */	beq lbl_8036A0DC
/* 8036A064 00366C44  A8 04 00 00 */	lha r0, 0(r4)
/* 8036A068 00366C48  3C A0 43 30 */	lis r5, 0x4330
/* 8036A06C 00366C4C  C8 22 EA E8 */	lfd f1, HSD_CObj_804DE4C8(r2)
/* 8036A070 00366C50  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8036A074 00366C54  90 01 00 2C */	stw r0, 0x2c(r1)
/* 8036A078 00366C58  90 A1 00 28 */	stw r5, 0x28(r1)
/* 8036A07C 00366C5C  C8 01 00 28 */	lfd f0, 0x28(r1)
/* 8036A080 00366C60  EC 00 08 28 */	fsubs f0, f0, f1
/* 8036A084 00366C64  D0 03 00 0C */	stfs f0, 0xc(r3)
/* 8036A088 00366C68  A8 04 00 02 */	lha r0, 2(r4)
/* 8036A08C 00366C6C  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8036A090 00366C70  90 01 00 24 */	stw r0, 0x24(r1)
/* 8036A094 00366C74  90 A1 00 20 */	stw r5, 0x20(r1)
/* 8036A098 00366C78  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 8036A09C 00366C7C  EC 00 08 28 */	fsubs f0, f0, f1
/* 8036A0A0 00366C80  D0 03 00 10 */	stfs f0, 0x10(r3)
/* 8036A0A4 00366C84  A8 04 00 04 */	lha r0, 4(r4)
/* 8036A0A8 00366C88  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8036A0AC 00366C8C  90 01 00 1C */	stw r0, 0x1c(r1)
/* 8036A0B0 00366C90  90 A1 00 18 */	stw r5, 0x18(r1)
/* 8036A0B4 00366C94  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 8036A0B8 00366C98  EC 00 08 28 */	fsubs f0, f0, f1
/* 8036A0BC 00366C9C  D0 03 00 14 */	stfs f0, 0x14(r3)
/* 8036A0C0 00366CA0  A8 04 00 06 */	lha r0, 6(r4)
/* 8036A0C4 00366CA4  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8036A0C8 00366CA8  90 01 00 14 */	stw r0, 0x14(r1)
/* 8036A0CC 00366CAC  90 A1 00 10 */	stw r5, 0x10(r1)
/* 8036A0D0 00366CB0  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 8036A0D4 00366CB4  EC 00 08 28 */	fsubs f0, f0, f1
/* 8036A0D8 00366CB8  D0 03 00 18 */	stfs f0, 0x18(r3)
lbl_8036A0DC:
/* 8036A0DC 00366CBC  38 21 00 30 */	addi r1, r1, 0x30
/* 8036A0E0 00366CC0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

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

#ifdef MWERKS_GEKKO
static Vec3 HSD_CObj_8040631C = { 0, 1, 0 };
static char HSD_CObj_804D5D50[3] = "0";

#pragma push
static asm int CObjLoad(HSD_CObj* cobj, HSD_CObjDesc* cobjdesc)
{ // clang-format off
    nofralloc
/* 8036A2EC 00366ECC  7C 08 02 A6 */	mflr r0
/* 8036A2F0 00366ED0  90 01 00 04 */	stw r0, 4(r1)
/* 8036A2F4 00366ED4  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 8036A2F8 00366ED8  93 E1 00 44 */	stw r31, 0x44(r1)
/* 8036A2FC 00366EDC  7C 9F 23 78 */	mr r31, r4
/* 8036A300 00366EE0  93 C1 00 40 */	stw r30, 0x40(r1)
/* 8036A304 00366EE4  7C 7E 1B 79 */	or. r30, r3, r3
/* 8036A308 00366EE8  A0 04 00 04 */	lhz r0, 4(r4)
/* 8036A30C 00366EEC  90 03 00 08 */	stw r0, 8(r3)
/* 8036A310 00366EF0  A0 64 00 04 */	lhz r3, 4(r4)
/* 8036A314 00366EF4  41 82 00 14 */	beq lbl_8036A328
/* 8036A318 00366EF8  80 1E 00 08 */	lwz r0, 8(r30)
/* 8036A31C 00366EFC  54 00 00 02 */	rlwinm r0, r0, 0, 0, 1
/* 8036A320 00366F00  7C 00 1B 78 */	or r0, r0, r3
/* 8036A324 00366F04  90 1E 00 08 */	stw r0, 8(r30)
lbl_8036A328:
/* 8036A328 00366F08  28 1E 00 00 */	cmplwi r30, 0
/* 8036A32C 00366F0C  41 82 00 7C */	beq lbl_8036A3A8
/* 8036A330 00366F10  A8 1F 00 08 */	lha r0, 8(r31)
/* 8036A334 00366F14  3C 60 43 30 */	lis r3, 0x4330
/* 8036A338 00366F18  C8 22 EA E8 */	lfd f1, HSD_CObj_804DE4C8(r2)
/* 8036A33C 00366F1C  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8036A340 00366F20  90 01 00 3C */	stw r0, 0x3c(r1)
/* 8036A344 00366F24  90 61 00 38 */	stw r3, 0x38(r1)
/* 8036A348 00366F28  C8 01 00 38 */	lfd f0, 0x38(r1)
/* 8036A34C 00366F2C  EC 00 08 28 */	fsubs f0, f0, f1
/* 8036A350 00366F30  D0 1E 00 0C */	stfs f0, 0xc(r30)
/* 8036A354 00366F34  A8 1F 00 0A */	lha r0, 0xa(r31)
/* 8036A358 00366F38  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8036A35C 00366F3C  90 01 00 34 */	stw r0, 0x34(r1)
/* 8036A360 00366F40  90 61 00 30 */	stw r3, 0x30(r1)
/* 8036A364 00366F44  C8 01 00 30 */	lfd f0, 0x30(r1)
/* 8036A368 00366F48  EC 00 08 28 */	fsubs f0, f0, f1
/* 8036A36C 00366F4C  D0 1E 00 10 */	stfs f0, 0x10(r30)
/* 8036A370 00366F50  A8 1F 00 0C */	lha r0, 0xc(r31)
/* 8036A374 00366F54  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8036A378 00366F58  90 01 00 2C */	stw r0, 0x2c(r1)
/* 8036A37C 00366F5C  90 61 00 28 */	stw r3, 0x28(r1)
/* 8036A380 00366F60  C8 01 00 28 */	lfd f0, 0x28(r1)
/* 8036A384 00366F64  EC 00 08 28 */	fsubs f0, f0, f1
/* 8036A388 00366F68  D0 1E 00 14 */	stfs f0, 0x14(r30)
/* 8036A38C 00366F6C  A8 1F 00 0E */	lha r0, 0xe(r31)
/* 8036A390 00366F70  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8036A394 00366F74  90 01 00 24 */	stw r0, 0x24(r1)
/* 8036A398 00366F78  90 61 00 20 */	stw r3, 0x20(r1)
/* 8036A39C 00366F7C  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 8036A3A0 00366F80  EC 00 08 28 */	fsubs f0, f0, f1
/* 8036A3A4 00366F84  D0 1E 00 18 */	stfs f0, 0x18(r30)
lbl_8036A3A8:
/* 8036A3A8 00366F88  28 1E 00 00 */	cmplwi r30, 0
/* 8036A3AC 00366F8C  41 82 00 14 */	beq lbl_8036A3C0
/* 8036A3B0 00366F90  80 7F 00 10 */	lwz r3, 0x10(r31)
/* 8036A3B4 00366F94  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8036A3B8 00366F98  90 7E 00 1C */	stw r3, 0x1c(r30)
/* 8036A3BC 00366F9C  90 1E 00 20 */	stw r0, 0x20(r30)
lbl_8036A3C0:
/* 8036A3C0 00366FA0  80 7E 00 24 */	lwz r3, 0x24(r30)
/* 8036A3C4 00366FA4  80 9F 00 18 */	lwz r4, 0x18(r31)
/* 8036A3C8 00366FA8  48 01 2F 85 */	bl HSD_WObjInit
/* 8036A3CC 00366FAC  80 7E 00 28 */	lwz r3, 0x28(r30)
/* 8036A3D0 00366FB0  80 9F 00 1C */	lwz r4, 0x1c(r31)
/* 8036A3D4 00366FB4  48 01 2F 79 */	bl HSD_WObjInit
/* 8036A3D8 00366FB8  28 1E 00 00 */	cmplwi r30, 0
/* 8036A3DC 00366FBC  C0 1F 00 28 */	lfs f0, 0x28(r31)
/* 8036A3E0 00366FC0  41 82 00 08 */	beq lbl_8036A3E8
/* 8036A3E4 00366FC4  D0 1E 00 38 */	stfs f0, 0x38(r30)
lbl_8036A3E8:
/* 8036A3E8 00366FC8  28 1E 00 00 */	cmplwi r30, 0
/* 8036A3EC 00366FCC  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8036A3F0 00366FD0  41 82 00 08 */	beq lbl_8036A3F8
/* 8036A3F4 00366FD4  D0 1E 00 3C */	stfs f0, 0x3c(r30)
lbl_8036A3F8:
/* 8036A3F8 00366FD8  A0 1F 00 04 */	lhz r0, 4(r31)
/* 8036A3FC 00366FDC  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8036A400 00366FE0  41 82 00 30 */	beq lbl_8036A430
/* 8036A404 00366FE4  80 9F 00 24 */	lwz r4, 0x24(r31)
/* 8036A408 00366FE8  28 04 00 00 */	cmplwi r4, 0
/* 8036A40C 00366FEC  41 82 00 10 */	beq lbl_8036A41C
/* 8036A410 00366FF0  7F C3 F3 78 */	mr r3, r30
/* 8036A414 00366FF4  4B FF EC A1 */	bl HSD_CObjSetUpVector
/* 8036A418 00366FF8  48 00 00 64 */	b lbl_8036A47C
lbl_8036A41C:
/* 8036A41C 00366FFC  3C 60 80 40 */	lis r3, HSD_CObj_8040631C@ha
/* 8036A420 00367000  38 83 63 1C */	addi r4, r3, HSD_CObj_8040631C@l
/* 8036A424 00367004  38 7E 00 00 */	addi r3, r30, 0
/* 8036A428 00367008  4B FF EC 8D */	bl HSD_CObjSetUpVector
/* 8036A42C 0036700C  48 00 00 50 */	b lbl_8036A47C
lbl_8036A430:
/* 8036A430 00367010  28 1E 00 00 */	cmplwi r30, 0
/* 8036A434 00367014  C0 3F 00 20 */	lfs f1, 0x20(r31)
/* 8036A438 00367018  41 82 00 44 */	beq lbl_8036A47C
/* 8036A43C 0036701C  80 7E 00 08 */	lwz r3, 8(r30)
/* 8036A440 00367020  54 60 07 FF */	clrlwi. r0, r3, 0x1f
/* 8036A444 00367024  41 82 00 20 */	beq lbl_8036A464
/* 8036A448 00367028  38 7E 00 00 */	addi r3, r30, 0
/* 8036A44C 0036702C  38 81 00 10 */	addi r4, r1, 0x10
/* 8036A450 00367030  4B FF E7 71 */	bl roll2upvec
/* 8036A454 00367034  38 7E 00 00 */	addi r3, r30, 0
/* 8036A458 00367038  38 81 00 10 */	addi r4, r1, 0x10
/* 8036A45C 0036703C  4B FF EC 59 */	bl HSD_CObjSetUpVector
/* 8036A460 00367040  48 00 00 1C */	b lbl_8036A47C
lbl_8036A464:
/* 8036A464 00367044  C0 1E 00 2C */	lfs f0, 0x2c(r30)
/* 8036A468 00367048  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8036A46C 0036704C  41 82 00 0C */	beq lbl_8036A478
/* 8036A470 00367050  64 60 C0 00 */	oris r0, r3, 0xc000
/* 8036A474 00367054  90 1E 00 08 */	stw r0, 8(r30)
lbl_8036A478:
/* 8036A478 00367058  D0 3E 00 2C */	stfs f1, 0x2c(r30)
lbl_8036A47C:
/* 8036A47C 0036705C  A0 1F 00 06 */	lhz r0, 6(r31)
/* 8036A480 00367060  2C 00 00 02 */	cmpwi r0, 2
/* 8036A484 00367064  41 82 00 78 */	beq lbl_8036A4FC
/* 8036A488 00367068  40 80 00 10 */	bge lbl_8036A498
/* 8036A48C 0036706C  2C 00 00 01 */	cmpwi r0, 1
/* 8036A490 00367070  40 80 00 14 */	bge lbl_8036A4A4
/* 8036A494 00367074  48 00 00 9C */	b lbl_8036A530
lbl_8036A498:
/* 8036A498 00367078  2C 00 00 04 */	cmpwi r0, 4
/* 8036A49C 0036707C  40 80 00 94 */	bge lbl_8036A530
/* 8036A4A0 00367080  48 00 00 28 */	b lbl_8036A4C8
lbl_8036A4A4:
/* 8036A4A4 00367084  28 1E 00 00 */	cmplwi r30, 0
/* 8036A4A8 00367088  C0 3F 00 34 */	lfs f1, 0x34(r31)
/* 8036A4AC 0036708C  C0 1F 00 30 */	lfs f0, 0x30(r31)
/* 8036A4B0 00367090  41 82 00 90 */	beq lbl_8036A540
/* 8036A4B4 00367094  38 00 00 01 */	li r0, 1
/* 8036A4B8 00367098  98 1E 00 50 */	stb r0, 0x50(r30)
/* 8036A4BC 0036709C  D0 1E 00 40 */	stfs f0, 0x40(r30)
/* 8036A4C0 003670A0  D0 3E 00 44 */	stfs f1, 0x44(r30)
/* 8036A4C4 003670A4  48 00 00 7C */	b lbl_8036A540
lbl_8036A4C8:
/* 8036A4C8 003670A8  28 1E 00 00 */	cmplwi r30, 0
/* 8036A4CC 003670AC  C0 7F 00 3C */	lfs f3, 0x3c(r31)
/* 8036A4D0 003670B0  C0 5F 00 38 */	lfs f2, 0x38(r31)
/* 8036A4D4 003670B4  C0 3F 00 34 */	lfs f1, 0x34(r31)
/* 8036A4D8 003670B8  C0 1F 00 30 */	lfs f0, 0x30(r31)
/* 8036A4DC 003670BC  41 82 00 64 */	beq lbl_8036A540
/* 8036A4E0 003670C0  38 00 00 03 */	li r0, 3
/* 8036A4E4 003670C4  98 1E 00 50 */	stb r0, 0x50(r30)
/* 8036A4E8 003670C8  D0 1E 00 40 */	stfs f0, 0x40(r30)
/* 8036A4EC 003670CC  D0 3E 00 44 */	stfs f1, 0x44(r30)
/* 8036A4F0 003670D0  D0 5E 00 48 */	stfs f2, 0x48(r30)
/* 8036A4F4 003670D4  D0 7E 00 4C */	stfs f3, 0x4c(r30)
/* 8036A4F8 003670D8  48 00 00 48 */	b lbl_8036A540
lbl_8036A4FC:
/* 8036A4FC 003670DC  28 1E 00 00 */	cmplwi r30, 0
/* 8036A500 003670E0  C0 7F 00 3C */	lfs f3, 0x3c(r31)
/* 8036A504 003670E4  C0 5F 00 38 */	lfs f2, 0x38(r31)
/* 8036A508 003670E8  C0 3F 00 34 */	lfs f1, 0x34(r31)
/* 8036A50C 003670EC  C0 1F 00 30 */	lfs f0, 0x30(r31)
/* 8036A510 003670F0  41 82 00 30 */	beq lbl_8036A540
/* 8036A514 003670F4  38 00 00 02 */	li r0, 2
/* 8036A518 003670F8  98 1E 00 50 */	stb r0, 0x50(r30)
/* 8036A51C 003670FC  D0 1E 00 40 */	stfs f0, 0x40(r30)
/* 8036A520 00367100  D0 3E 00 44 */	stfs f1, 0x44(r30)
/* 8036A524 00367104  D0 5E 00 48 */	stfs f2, 0x48(r30)
/* 8036A528 00367108  D0 7E 00 4C */	stfs f3, 0x4c(r30)
/* 8036A52C 0036710C  48 00 00 14 */	b lbl_8036A540
lbl_8036A530:
/* 8036A530 00367110  38 6D A6 A0 */	addi r3, r13, HSD_CObj_804D5D40
/* 8036A534 00367114  38 80 07 D0 */	li r4, 0x7d0
/* 8036A538 00367118  38 AD A6 B0 */	addi r5, r13, HSD_CObj_804D5D50
/* 8036A53C 0036711C  48 01 DC E5 */	bl __assert
lbl_8036A540:
/* 8036A540 00367120  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 8036A544 00367124  38 60 00 00 */	li r3, 0
/* 8036A548 00367128  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 8036A54C 0036712C  83 C1 00 40 */	lwz r30, 0x40(r1)
/* 8036A550 00367130  38 21 00 48 */	addi r1, r1, 0x48
/* 8036A554 00367134  7C 08 03 A6 */	mtlr r0
/* 8036A558 00367138  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static int CObjLoad(HSD_CObj* cobj, HSD_CObjDesc* cobjdesc)
{
    NOT_IMPLEMENTED;
}
#endif

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
