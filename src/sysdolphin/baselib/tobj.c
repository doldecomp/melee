#include "tobj.h"

#include "aobj.h"
#include "cobj.h"
#include "debug.h"
#include "lobj.h"
#include "memory.h"
#include "mtx.h"

#include <__mem.h>
#include <math.h> // IWYU pragma: keep
#include <dolphin/gx/GXAttr.h>
#include <dolphin/mtx.h>
#include <dolphin/mtx/mtxvec.h>
#include <dolphin/mtx/types.h>
#include <MetroTRK/intrinsics.h>

static void MakeTextureMtx(HSD_TObj* tobj);
static void TObjInfoInit(void);

HSD_TObjInfo hsdTObj = { TObjInfoInit };

extern HSD_TObj* tobj_head;

extern char lbl_804055B8[];

char HSD_TObj_804D5C90[7] = "tobj.c\0";
char HSD_TObj_804D5C98[5] = "tobj\0";

void HSD_TObjRemoveAnim(HSD_TObj* tobj)
{
    if (tobj == NULL) {
        return;
    }

    HSD_AObjRemove(tobj->aobj);
    tobj->aobj = NULL;
}

void HSD_TObjRemoveAnimAll(HSD_TObj* tobj)
{
    HSD_TObj* tp;

    if (tobj != NULL) {
        for (tp = tobj; tp != NULL; tp = tp->next) {
            HSD_TObjRemoveAnim(tp);
        }
    }
}

static HSD_TexAnim* lookupTextureAnim(s32 id, HSD_TexAnim* texanim)
{
    HSD_TexAnim* ta;
    for (ta = texanim; ta; ta = ta->next) {
        if (ta->id == id) {
            return ta;
        }
    }
    return NULL;
}

void HSD_TObjAddAnim(HSD_TObj* tobj, HSD_TexAnim* texanim)
{
    s32 i;
    HSD_TexAnim* ta;

    if (tobj != NULL) {
        if ((ta = lookupTextureAnim(tobj->id, texanim)) != NULL) {
            if (tobj->aobj != NULL) {
                HSD_AObjRemove(tobj->aobj);
            }
            tobj->aobj = HSD_AObjLoadDesc(ta->aobjdesc);
            tobj->imagetbl = ta->imagetbl;

            if (tobj->tluttbl != NULL) {
                for (i = 0; tobj->tluttbl[i]; i++) {
                    HSD_TlutFree(tobj->tluttbl[i]);
                }
                HSD_Free(tobj->tluttbl);
            }

            if (ta->n_tluttbl) {
                tobj->tluttbl = (HSD_Tlut**) HSD_MemAlloc(
                    (s32) sizeof(HSD_Tlut*) * (ta->n_tluttbl + 1));
                for (i = 0; i < ta->n_tluttbl; i++) {
                    tobj->tluttbl[i] = HSD_TlutLoadDesc(ta->tluttbl[i]);
                }
                tobj->tluttbl[i] = NULL;
            } else {
                tobj->tluttbl = NULL;
            }
            tobj->tlut_no = -1;
        }
    }
}

void HSD_TObjAddAnimAll(HSD_TObj* tobj, HSD_TexAnim* texanim)
{
    HSD_TObj* tp;

    if (tobj != NULL) {
        for (tp = tobj; tp; tp = tp->next) {
            HSD_TObjAddAnim(tp, texanim);
        }
    }
}

void HSD_TObjReqAnimByFlags(HSD_TObj* tobj, f32 startframe, u32 flags)
{
    if (tobj != NULL) {
        if (flags & TOBJ_ANIM) {
            HSD_AObjReqAnim(tobj->aobj, startframe);
        }
    }
}

void HSD_TObjReqAnimAllByFlags(HSD_TObj* tobj, f32 startframe, u32 flags)
{
    HSD_TObj* tp;

    if (tobj != NULL) {
        for (tp = tobj; tp != NULL; tp = tp->next) {
            HSD_TObjReqAnimByFlags(tp, startframe, flags);
        }
    }
}

void HSD_TObjReqAnim(HSD_TObj* tobj, f32 startframe)
{
    HSD_TObjReqAnimByFlags(tobj, startframe, TOBJ_ANIM);
}

void HSD_TObjReqAnimAll(HSD_TObj* tobj, f32 startframe)
{
    HSD_TObjReqAnimAllByFlags(tobj, startframe, TOBJ_ANIM);
}

static void TObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val)
{
    HSD_TObj* tobj = obj;

    if (tobj == NULL) {
        return;
    }

    switch (type) {
    case HSD_A_T_TIMG: {
        int n;
        if (tobj->imagetbl == NULL) {
            __assert(HSD_TObj_804D5C90, 276, "tobj->imagetbl");
        }
        n = (int) val->fv;
        if (tobj->imagetbl[n]) {
            tobj->imagedesc = tobj->imagetbl[n];
        }
    } break;
    case HSD_A_T_TCLT: {
        if (tobj->tluttbl) {
            tobj->tlut_no = (u8) val->fv;
        }
    } break;
    case HSD_A_T_BLEND:
        tobj->blending = val->fv;
        break;
    case HSD_A_T_ROTX:
        tobj->rotate.x = val->fv;
        goto mtxdirty;
    case HSD_A_T_ROTY:
        tobj->rotate.y = val->fv;
        goto mtxdirty;
    case HSD_A_T_ROTZ:
        tobj->rotate.z = val->fv;
        goto mtxdirty;
    case HSD_A_T_TRAU:
        tobj->translate.x = val->fv;
        goto mtxdirty;
    case HSD_A_T_TRAV:
        tobj->translate.y = val->fv;
        goto mtxdirty;
    case HSD_A_T_SCAU:
        tobj->scale.x = val->fv;
        goto mtxdirty;
    case HSD_A_T_SCAV:
        tobj->scale.y = val->fv;
        goto mtxdirty;
    mtxdirty:
        tobj->flags |= TEX_MTX_DIRTY;
        break;
    case HSD_A_T_LOD_BIAS:
        tobj->lod->LODBias = val->fv;
        break;
    case HSD_A_T_KONST_R:
        tobj->tev->konst.r = (u8) (255.0 * val->fv);
        break;
    case HSD_A_T_KONST_G:
        tobj->tev->konst.g = (u8) (255.0 * val->fv);
        break;
    case HSD_A_T_KONST_B:
        tobj->tev->konst.b = (u8) (255.0 * val->fv);
        break;
    case HSD_A_T_KONST_A:
        tobj->tev->konst.a = (u8) (255.0 * val->fv);
        break;
    case HSD_A_T_TEV0_R:
        tobj->tev->tev0.r = (u8) (255.0 * val->fv);
        break;
    case HSD_A_T_TEV0_G:
        tobj->tev->tev0.g = (u8) (255.0 * val->fv);
        break;
    case HSD_A_T_TEV0_B:
        tobj->tev->tev0.b = (u8) (255.0 * val->fv);
        break;
    case HSD_A_T_TEV0_A:
        tobj->tev->tev0.a = (u8) (255.0 * val->fv);
        break;
    case HSD_A_T_TEV1_R:
        tobj->tev->tev1.r = (u8) (255.0 * val->fv);
        break;
    case HSD_A_T_TEV1_G:
        tobj->tev->tev1.g = (u8) (255.0 * val->fv);
        break;
    case HSD_A_T_TEV1_B:
        tobj->tev->tev1.b = (u8) (255.0 * val->fv);
        break;
    case HSD_A_T_TEV1_A:
        tobj->tev->tev1.a = (u8) (255.0 * val->fv);
        break;
    case HSD_A_T_TS_BLEND:
        tobj->blending = val->fv;
        break;
    }
}

void HSD_TObjAnim(HSD_TObj* tobj)
{
    if (tobj == NULL) {
        return;
    }

    HSD_AObjInterpretAnim(tobj->aobj, tobj, TObjUpdateFunc);
}

void HSD_TObjAnimAll(HSD_TObj* tobj)
{
    HSD_TObj* i;

    if (tobj == NULL) {
        return;
    }

    for (i = tobj; i != NULL; i = i->next) {
        HSD_TObjAnim(i);
    }
}

/*static*/ int TObjLoad(HSD_TObj* tobj, HSD_TObjDesc* td)
{
    tobj->next = HSD_TObjLoadDesc(td->next);
    tobj->id = td->id;
    tobj->src = td->src;
    tobj->mtxid = GX_IDENTITY;
    tobj->rotate.x = td->rotate.x;
    tobj->rotate.y = td->rotate.y;
    tobj->rotate.z = td->rotate.z;
    tobj->scale = td->scale;
    tobj->translate = td->translate;
    tobj->wrap_s = td->wrap_s;
    tobj->wrap_t = td->wrap_t;
    tobj->repeat_s = td->repeat_s;
    tobj->repeat_t = td->repeat_t;
    tobj->flags = td->blend_flags;
    tobj->blending = td->blending;
    tobj->magFilt = td->magFilt;
    tobj->imagedesc = td->imagedesc;
    tobj->tlut = HSD_TlutLoadDesc(td->tlutdesc);
    tobj->lod = td->lod;
    tobj->aobj = NULL;
    tobj->flags |= TEX_MTX_DIRTY;
    tobj->tlut_no = (u8) -1;
    tobj->tev = HSD_TObjTevLoadDesc(td->tev);

    return 0;
}

HSD_TObj* HSD_TObjLoadDesc(HSD_TObjDesc* td)
{
    if (td != NULL) {
        HSD_TObj* tobj;
        HSD_ClassInfo* info;

        if (!td->class_name || !(info = hsdSearchClassInfo(td->class_name))) {
            tobj = allocShadowTObj();
        } else {
            tobj = hsdNew(info);
            if (tobj == NULL) {
                __assert(HSD_TObj_804D5C90, 468, HSD_TObj_804D5C98);
            }
        }
        HSD_TOBJ_METHOD(tobj)->load(tobj, td);
        return tobj;
    } else {
        return NULL;
    }
}

HSD_Tlut* HSD_TlutLoadDesc(HSD_TlutDesc* tlutdesc)
{
    if (tlutdesc != NULL) {
        HSD_Tlut* tlut = HSD_TlutAlloc();
        memcpy(tlut, tlutdesc, sizeof(HSD_Tlut));
        return tlut;
    }
    return NULL;
}

HSD_TObjTev* HSD_TObjTevLoadDesc(HSD_TObjTevDesc* tevdesc)
{
    if (tevdesc != NULL) {
        HSD_TObjTev* new = HSD_TObjTevAlloc();
        memcpy(new, tevdesc, sizeof(HSD_TObjTev));
        return new;
    }
    return NULL;
}

HSD_TObj* _HSD_TObjGetCurrentByType(HSD_TObj* from, u32 mapping)
{
    HSD_TObj* tp;

    if (from == NULL) {
        tp = tobj_head;
    } else {
        tp = from->next;
    }

    for (; tp != NULL; tp = tp->next) {
        if (tobj_coord(tp) == mapping) {
            goto END;
        }
    }

    tp = NULL;
END:
    return tp;
}

char HSD_TObj_8040562C[23] = "unexpected texmap id.\n\0";

#pragma push
#pragma force_active on
static u32 HSD_TexMapID2PTTexMtx(GXTexMapID id)
{
    switch (id) {
    case GX_TEXMAP0:
        return GX_PTTEXMTX0;
    case GX_TEXMAP1:
        return GX_PTTEXMTX1;
    case GX_TEXMAP2:
        return GX_PTTEXMTX2;
    case GX_TEXMAP3:
        return GX_PTTEXMTX3;
    case GX_TEXMAP4:
        return GX_PTTEXMTX4;
    case GX_TEXMAP5:
        return GX_PTTEXMTX5;
    case GX_TEXMAP6:
        return GX_PTTEXMTX6;
    case GX_TEXMAP7:
        return GX_PTTEXMTX7;
    default:
        HSD_Panic(HSD_TObj_804D5C90, 574, HSD_TObj_8040562C);
    }
    return 0;
}
#pragma pop

static void MakeTextureMtx(HSD_TObj* tobj)
{
    Vec3 scale;
    Mtx m;
    Vec3 trans;
    Quaternion rot;

    u8 _[8];

    bool no_assert = false;

    if (tobj->repeat_s && tobj->repeat_t) {
        no_assert = true;
    }

    if (!no_assert) {
        __assert(HSD_TObj_804D5C90, 589, "tobj->repeat_s && tobj->repeat_t");
    }

    scale.x = __fabsf(tobj->scale.x) < FLT_EPSILON
                  ? 0.0F
                  : (f32) tobj->repeat_s / tobj->scale.x;
    scale.y = __fabsf(tobj->scale.y) < FLT_EPSILON
                  ? 0.0F
                  : (f32) tobj->repeat_t / tobj->scale.y;
    scale.z = tobj->scale.z;
    rot.x = tobj->rotate.x;
    rot.y = tobj->rotate.y;
    rot.z = -tobj->rotate.z;
    trans.x = -tobj->translate.x;
    trans.y =
        -(tobj->translate.y + (tobj->wrap_t == GX_MIRROR
                                   ? 1.0F / (tobj->repeat_t / tobj->scale.y)
                                   : 0.0F));
    trans.z = tobj->translate.z;

    MTXTrans(tobj->mtx, trans.x, trans.y, trans.z);
    HSD_MkRotationMtx(m, (Vec3*) &rot);
    MTXConcat(m, tobj->mtx, tobj->mtx);
    MTXScale(m, scale.x, scale.y, scale.z);
    MTXConcat(m, tobj->mtx, tobj->mtx);
}

void TObjSetupMtx(HSD_TObj* tobj)
{
    int i;

    if (tobj_coord(tobj) == TEX_COORD_TOON) {
        return;
    }

    if (tobj->flags & TEX_MTX_DIRTY) {
        HSD_TOBJ_METHOD(tobj)->make_mtx(tobj);
        tobj->flags &= ~TEX_MTX_DIRTY;
    }

    switch (tobj_coord(tobj)) {
    case TEX_COORD_REFLECTION: {
        Mtx mtx;

        for (i = 0; i < 3; i++) {
            mtx[i][0] = 0.5F * tobj->mtx[i][0];
            mtx[i][1] = -0.5F * tobj->mtx[i][1];
            mtx[i][2] = 0.0F;
            mtx[i][3] = 0.5F * tobj->mtx[i][0] + 0.5F * tobj->mtx[i][1] +
                        tobj->mtx[i][2] + tobj->mtx[i][3];
        }
        GXLoadTexMtxImm(mtx, tobj->mtxid, GX_MTX3x4);
    } break;

    case TEX_COORD_HILIGHT: {
        HSD_LObj* lobj;

        if ((lobj = HSD_LObjGetCurrentByType(LOBJ_INFINITE)) != NULL) {
            HSD_CObj* cobj;
            Vec3 ldir, half;
            Mtx mtx;
            MtxPtr vmtx;

            cobj = HSD_CObjGetCurrent();
            HSD_ASSERT(0x2A8, cobj);
            vmtx = HSD_CObjGetViewingMtxPtrDirect(cobj);
            HSD_LObjGetLightVector(lobj, &ldir);
            PSMTXMultVecSR(vmtx, &ldir, &ldir);
            ldir.z += -1.0F;

            PSVECNormalize(&ldir, &half);

            half.x *= -0.5;
            half.y *= -0.5;
            half.z *= -0.5;

            mtx[0][0] = tobj->mtx[0][0] * half.x;
            mtx[0][1] = tobj->mtx[0][0] * half.y;
            mtx[0][2] = tobj->mtx[0][0] * half.z;
            mtx[0][3] = tobj->mtx[0][0] * 0.5F + tobj->mtx[0][3];
            mtx[1][0] = tobj->mtx[1][0] * half.x;
            mtx[1][1] = tobj->mtx[1][0] * half.y;
            mtx[1][2] = tobj->mtx[1][0] * half.z;
            mtx[1][3] = tobj->mtx[1][0] * 0.5F + tobj->mtx[1][3];
            mtx[2][0] = mtx[2][1] = mtx[2][2] = 0.0F;
            mtx[2][3] = 1.0F;

            GXLoadTexMtxImm(mtx, tobj->mtxid, GX_MTX3x4);
        } else {
            static Mtx zero = { 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F,
                                0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F };
            GXLoadTexMtxImm(zero, tobj->mtxid, GX_MTX3x4);
        }
    } break;

    case TEX_COORD_SHADOW: {
        HSD_CObj* cobj = HSD_CObjGetCurrent();
        Mtx mtx;

        PSMTXConcat(tobj->mtx, HSD_CObjGetInvViewingMtxPtrDirect(cobj), mtx);
        GXLoadTexMtxImm(mtx, tobj->mtxid, GX_MTX3x4);
    } break;

    default:
        if (tobj_bump(tobj)) {
            GXLoadTexMtxImm(tobj->mtx, tobj->mtxid, GX_MTX2x4);
        } else {
            GXLoadTexMtxImm(tobj->mtx, tobj->mtxid, GX_MTX3x4);
        }
        break;
    }
}

GXTexGenSrc HSD_TexCoordID2TexGenSrc(GXTexCoordID coord)
{
    switch (coord) {
    case GX_TEXCOORD0:
        return GX_TG_TEXCOORD0;
    case GX_TEXCOORD1:
        return GX_TG_TEXCOORD1;
    case GX_TEXCOORD2:
        return GX_TG_TEXCOORD2;
    case GX_TEXCOORD3:
        return GX_TG_TEXCOORD3;
    case GX_TEXCOORD4:
        return GX_TG_TEXCOORD4;
    case GX_TEXCOORD5:
        return GX_TG_TEXCOORD5;
    case GX_TEXCOORD6:
        return GX_TG_TEXCOORD6;
    case GX_TEXCOORD7:
    default:
        HSD_ASSERT(1738, 0);
    }
    return GX_TG_TEXCOORD0;
}
