#include "tobj.h"

#include "aobj.h"
#include "cobj.h"
#include "debug.h"
#include "lobj.h"
#include "memory.h"
#include "mtx.h"
#include "tev.h"

#include <__mem.h>
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

#define FLT_EPSILON 1.00000001335e-10F

static void MakeTextureMtx(HSD_TObj* tobj);
static void TObjInfoInit(void);

HSD_TObjInfo hsdTObj = { TObjInfoInit };

static HSD_TObjInfo* default_class = NULL;

HSD_TObj* tobj_head;

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
        if (ta->id == (GXTexMapID) id) {
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
                    HSD_TlutRemove(tobj->tluttbl[i]);
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
        HSD_ASSERT(276, tobj->imagetbl);
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

static int TObjLoad(HSD_TObj* tobj, HSD_TObjDesc* td)
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
            tobj = HSD_TObjAlloc();
        } else {
            tobj = hsdNew(info);
            HSD_ASSERT(468, tobj);
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
        HSD_Panic(__FILE__, 574, "unexpected texmap id.\n");
    }
    return 0;
}

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
        __assert(__FILE__, 589, "tobj->repeat_s && tobj->repeat_t");
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

static void TObjSetupMtx(HSD_TObj* tobj)
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
            MTXMultVecSR(vmtx, &ldir, &ldir);
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

static void setupTextureCoordGen(HSD_TObj* tobj)
{
    u32 mtxid;
    GXTexGenSrc src;

    switch (tobj_coord(tobj)) {
    case TEX_COORD_SHADOW:
        GXSetTexCoordGen2(tobj->coord, GX_TG_MTX3x4, GX_TG_POS, GX_PNMTX0,
                          GX_DISABLE, tobj->mtxid);
        break;
    case TEX_COORD_REFLECTION:
    case TEX_COORD_HILIGHT:
        GXSetTexCoordGen2(tobj->coord, GX_TG_MTX3x4, GX_TG_NRM, GX_TEXMTX0,
                          GX_ENABLE, tobj->mtxid);
        break;
    default:
        if (tobj_bump(tobj)) {
            mtxid = tobj->mtxid;
            src = tobj->src;
            GXSetTexCoordGen(tobj->coord, GX_TG_MTX2x4, src, mtxid);
        } else {
            GXSetTexCoordGen2(tobj->coord, GX_TG_MTX2x4, tobj->src,
                              GX_IDENTITY, GX_DISABLE, tobj->mtxid);
        }
    }
}

static void setupTextureCoordGenBump(HSD_TObj* bump)
{
    u32 mask;
    int i;
    static GXTexGenType func[] = {
        GX_TG_BUMP0, GX_TG_BUMP1, GX_TG_BUMP2, GX_TG_BUMP3,
        GX_TG_BUMP4, GX_TG_BUMP5, GX_TG_BUMP6, GX_TG_BUMP7,
    };

    mask = HSD_LObjGetLightMaskDiffuse();

    for (i = 0; i < GX_MAX_LIGHT - 1; i++) {
        if (mask & (1 << i)) {
            break;
        }
    }
    if (i >= GX_MAX_LIGHT - 1) {
        i = 0;
    }

    GXSetTexCoordGen((GXTexCoordID) (bump->coord + 1), func[i],
                     HSD_TexCoordID2TexGenSrc(bump->coord), GX_IDENTITY);
}

static void setupTextureCoordGenToon(HSD_TObj* toon)
{
    GXTexGenSrc src = toon->src;
    GXSetTexCoordGen(toon->coord, GX_TG_SRTG, src, GX_IDENTITY);
}

void HSD_TObjSetupTextureCoordGen(HSD_TObj* tobj)
{
    for (; tobj != NULL; tobj = tobj->next) {
        if (tobj->id == GX_TEXMAP_NULL) {
            continue;
        }
        if (tobj_bump(tobj)) {
            setupTextureCoordGen(tobj);
            setupTextureCoordGenBump(tobj);
        } else if (tobj_coord(tobj) == TEX_COORD_TOON) {
            setupTextureCoordGenToon(tobj);
        } else {
            setupTextureCoordGen(tobj);
        }
    }
}

static void TObjSetupTevModulateShadow(HSD_TObj* shadow)
{
    static HSD_TevDesc tevdesc = {
        NULL,           TEVCONF_MODE,  (GXTevStageID) (-1), GX_TEXCOORD_NULL,
        GX_TEXMAP_NULL, GX_COLOR_NULL, GX_TEV_ADD,          GX_CC_ZERO,
        GX_CC_CPREV,    GX_CC_TEXC,    GX_CC_ZERO,          GX_CS_SCALE_1,
        GX_TB_ZERO,     GX_ENABLE,     GX_TEVPREV,          GX_TEV_ADD,
        GX_CA_ZERO,     GX_CA_ZERO,    GX_CA_ZERO,          GX_CA_APREV,
        GX_CS_SCALE_1,  GX_TB_ZERO,    GX_ENABLE,           GX_TEVPREV,
        GX_TC_LINEAR,
    };

    for (; shadow && tobj_coord(shadow) == TEX_COORD_SHADOW;
         shadow = shadow->next)
    {
        tevdesc.stage = HSD_StateAssignTev();
        tevdesc.coord = shadow->coord;
        tevdesc.map = shadow->id;
        HSD_SetupTevStage(&tevdesc);
    }
}

static void SetupEmbossBumpTev(HSD_TObj* bump)
{
    static HSD_TevDesc tevdesc = {
        NULL,           TEVCONF_MODE, (GXTevStageID) (-1), GX_TEXCOORD_NULL,
        GX_TEXMAP_NULL, GX_COLOR0A0,  GX_TEV_SUB,          GX_CC_ZERO,
        GX_CC_TEXC,     GX_CC_RASC,   GX_CC_CPREV,         GX_CS_SCALE_1,
        GX_TB_ZERO,     GX_ENABLE,    GX_TEVPREV,          GX_TEV_SUB,
        GX_CA_ZERO,     GX_CA_ZERO,   GX_CA_ZERO,          GX_CA_APREV,
        GX_CS_SCALE_1,  GX_TB_ZERO,   GX_ENABLE,           GX_TEVPREV,
        GX_TC_LINEAR,
    };

    tevdesc.stage = HSD_StateAssignTev();
    tevdesc.coord = bump->coord;
    tevdesc.map = bump->id;
    tevdesc.u.tevconf.clr_op = GX_TEV_ADD;
    tevdesc.u.tevconf.alpha_op = GX_TEV_ADD;
    tevdesc.u.tevconf.clr_clamp = GX_DISABLE;
    HSD_SetupTevStage(&tevdesc);
    tevdesc.stage = HSD_StateAssignTev();
    tevdesc.coord = (GXTexCoordID) (bump->coord + 1);
    tevdesc.u.tevconf.clr_op = GX_TEV_SUB;
    tevdesc.u.tevconf.alpha_op = GX_TEV_SUB;
    tevdesc.u.tevconf.clr_clamp = GX_ENABLE;
    HSD_SetupTevStage(&tevdesc);
}

void HSD_TObjSetupVolatileTev(HSD_TObj* tobj, u32 rendermode)
{
    for (; tobj; tobj = tobj->next) {
        if (tobj->id == GX_TEXMAP_NULL) {
            continue;
        }

        if (tobj_bump(tobj)) {
            SetupEmbossBumpTev(tobj);
        }

        if (tobj_lightmap(tobj) & TEX_LIGHTMAP_SHADOW) {
            TObjSetupTevModulateShadow(tobj);
            break;
        }
    }
}

static void MakeColorGenTExp(u32 lightmap, HSD_TObj* tobj, HSD_TExp** c,
                             HSD_TExp** a, HSD_TExp** list, int repeat)
{
    HSD_TObjTev* tev = tobj->tev;
    u8* in;
    HSD_TExp *e0, *tmp;
    int i;

    HSD_TExp* konst_rgb;
    HSD_TExp* konst_r;
    HSD_TExp* konst_g;
    HSD_TExp* konst_b;
    HSD_TExp* konst_a;
    HSD_TExp* reg0_rgb;
    HSD_TExp* reg0_a;
    HSD_TExp* reg1_rgb;
    HSD_TExp* reg1_a;

    int use_k_rgb = 0;
    int use_k_r = 0;
    int use_k_g = 0;
    int use_k_b = 0;
    int use_k_a = 0;
    int use_reg0_rgb = 0;
    int use_reg0_a = 0;
    int use_reg1_rgb = 0;
    int use_reg1_a = 0;

    in = &tev->color_a;
    for (i = 0; i < 4; i++) {
        switch (in[i]) {
        case TOBJ_TEV_CC_KONST_RGB:
            use_k_rgb = 1;
            break;
        case TOBJ_TEV_CC_KONST_RRR:
            use_k_r = 1;
            break;
        case TOBJ_TEV_CC_KONST_GGG:
            use_k_g = 1;
            break;
        case TOBJ_TEV_CC_KONST_BBB:
            use_k_b = 1;
            break;
        case TOBJ_TEV_CC_KONST_AAA:
            use_k_a = 1;
            break;
        case TOBJ_TEV_CC_TEX0_RGB:
            use_reg0_rgb = 1;
            break;
        case TOBJ_TEV_CC_TEX0_AAA:
            use_reg0_a = 1;
            break;
        case TOBJ_TEV_CC_TEX1_RGB:
            use_reg1_rgb = 1;
            break;
        case TOBJ_TEV_CC_TEX1_AAA:
            use_reg1_a = 1;
            break;
        default:
            break;
        }
    }
    in = &tev->alpha_a;
    for (i = 0; i < 4; i++) {
        switch (in[i]) {
        case TOBJ_TEV_CA_KONST_R:
            use_k_r = 1;
            break;
        case TOBJ_TEV_CA_KONST_G:
            use_k_g = 1;
            break;
        case TOBJ_TEV_CA_KONST_B:
            use_k_b = 1;
            break;
        case TOBJ_TEV_CA_KONST_A:
            use_k_a = 1;
            break;
        case TOBJ_TEV_CA_TEX0_A:
            use_reg0_a = 1;
            break;
        case TOBJ_TEV_CA_TEX1_A:
            use_reg1_a = 1;
            break;
        default:
            break;
        }
    }

    if (use_k_rgb) {
        konst_rgb =
            HSD_TExpCnst(&tobj->tev->konst, HSD_TE_RGB, HSD_TE_U8, list);
    }
    if (use_k_r) {
        konst_r = HSD_TExpCnst(&tobj->tev->konst.r, HSD_TE_X, HSD_TE_U8, list);
    }
    if (use_k_g) {
        konst_g = HSD_TExpCnst(&tobj->tev->konst.g, HSD_TE_X, HSD_TE_U8, list);
    }
    if (use_k_b) {
        konst_b = HSD_TExpCnst(&tobj->tev->konst.b, HSD_TE_X, HSD_TE_U8, list);
    }
    if (use_k_a) {
        konst_a = HSD_TExpCnst(&tobj->tev->konst.a, HSD_TE_X, HSD_TE_U8, list);
    }
    if (use_reg0_rgb) {
        reg0_rgb = HSD_TExpCnst(&tobj->tev->tev0, HSD_TE_RGB, HSD_TE_U8, list);
    }
    if (use_reg0_a) {
        reg0_a = HSD_TExpCnst(&tobj->tev->tev0.a, HSD_TE_X, HSD_TE_U8, list);
    }
    if (use_reg1_rgb) {
        reg1_rgb = HSD_TExpCnst(&tobj->tev->tev1, HSD_TE_RGB, HSD_TE_U8, list);
    }
    if (use_reg1_a) {
        reg1_a = HSD_TExpCnst(&tobj->tev->tev1.a, HSD_TE_X, HSD_TE_U8, list);
    }

    e0 = HSD_TExpTev(list);
    HSD_TExpOrder(e0, tobj, GX_COLOR_NULL);

    if (tev->active & TOBJ_TEVREG_ACTIVE_COLOR_TEV) {
        HSD_TEInput sel[4];
        HSD_TExp* exp[4];
        int i;

        in = &tev->color_a;
        for (i = 0; i < 4; i++) {
            switch (in[i]) {
            case GX_CC_ZERO:
                sel[i] = HSD_TE_0;
                exp[i] = HSD_TEXP_ZERO;
                break;
            case GX_CC_ONE:
                sel[i] = HSD_TE_1;
                exp[i] = HSD_TEXP_ZERO;
                break;
            case GX_CC_HALF:
                sel[i] = HSD_TE_4_8;
                exp[i] = HSD_TEXP_ZERO;
                break;
            case GX_CC_TEXC:
                sel[i] = HSD_TE_RGB;
                exp[i] = HSD_TEXP_TEX;
                break;
            case GX_CC_TEXA:
                sel[i] = HSD_TE_A;
                exp[i] = HSD_TEXP_TEX;
                break;
            case TOBJ_TEV_CC_KONST_RGB:
                sel[i] = HSD_TE_RGB;
                exp[i] = konst_rgb;
                break;
            case TOBJ_TEV_CC_KONST_RRR:
                sel[i] = HSD_TE_X;
                exp[i] = konst_r;
                break;
            case TOBJ_TEV_CC_KONST_GGG:
                sel[i] = HSD_TE_X;
                exp[i] = konst_g;
                break;
            case TOBJ_TEV_CC_KONST_BBB:
                sel[i] = HSD_TE_X;
                exp[i] = konst_b;
                break;
            case TOBJ_TEV_CC_KONST_AAA:
                sel[i] = HSD_TE_X;
                exp[i] = konst_a;
                break;
            case TOBJ_TEV_CC_TEX0_RGB:
                tmp = HSD_TExpTev(list);
                HSD_TExpOrder(tmp, NULL, GX_COLOR_NULL);
                HSD_TExpColorOp(tmp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                                GX_ENABLE);
                HSD_TExpColorIn(tmp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                                HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                                HSD_TE_RGB, reg0_rgb);
                sel[i] = HSD_TE_RGB;
                exp[i] = tmp;
                break;
            case TOBJ_TEV_CC_TEX0_AAA:
                tmp = HSD_TExpTev(list);
                HSD_TExpOrder(tmp, NULL, GX_COLOR_NULL);
                HSD_TExpColorOp(tmp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                                GX_ENABLE);
                HSD_TExpColorIn(tmp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                                HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                                HSD_TE_X, reg0_a);
                sel[i] = HSD_TE_RGB;
                exp[i] = tmp;
                break;
            case TOBJ_TEV_CC_TEX1_RGB:
                tmp = HSD_TExpTev(list);
                HSD_TExpOrder(tmp, NULL, GX_COLOR_NULL);
                HSD_TExpColorOp(tmp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                                GX_ENABLE);
                HSD_TExpColorIn(tmp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                                HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                                HSD_TE_RGB, reg1_rgb);
                sel[i] = HSD_TE_RGB;
                exp[i] = tmp;
                break;
            case TOBJ_TEV_CC_TEX1_AAA:
                tmp = HSD_TExpTev(list);
                HSD_TExpOrder(tmp, NULL, GX_COLOR_NULL);
                HSD_TExpColorOp(tmp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                                GX_ENABLE);
                HSD_TExpColorIn(tmp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                                HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                                HSD_TE_X, reg1_a);
                sel[i] = HSD_TE_RGB;
                exp[i] = tmp;
                break;
            default:
                HSD_ASSERT(0x4A7, 0);
                break;
            }
        }

        HSD_TExpColorOp(e0, (GXTevOp) tev->color_op,
                        (GXTevBias) tev->color_bias,
                        (GXTevScale) tev->color_scale, tev->color_clamp);
        HSD_TExpColorIn(e0, sel[0], exp[0], sel[1], exp[1], sel[2], exp[2],
                        sel[3], exp[3]);
        *c = e0;
    }

    if (tev->active & TOBJ_TEVREG_ACTIVE_ALPHA_TEV) {
        HSD_TEInput sel[4];
        HSD_TExp* exp[4];
        int i;

        in = &tev->alpha_a;
        for (i = 0; i < 4; i++) {
            switch (in[i]) {
            case GX_CA_ZERO:
                sel[i] = HSD_TE_0;
                exp[i] = HSD_TEXP_ZERO;
                break;
            case GX_CA_TEXA:
                sel[i] = HSD_TE_A;
                exp[i] = HSD_TEXP_TEX;
                break;
            case TOBJ_TEV_CA_KONST_R:
                sel[i] = HSD_TE_X;
                exp[i] = konst_r;
                break;
            case TOBJ_TEV_CA_KONST_G:
                sel[i] = HSD_TE_X;
                exp[i] = konst_g;
                break;
            case TOBJ_TEV_CA_KONST_B:
                sel[i] = HSD_TE_X;
                exp[i] = konst_b;
                break;
            case TOBJ_TEV_CA_KONST_A:
                sel[i] = HSD_TE_X;
                exp[i] = konst_a;
                break;
            case TOBJ_TEV_CA_TEX0_A:
                tmp = HSD_TExpTev(list);
                HSD_TExpOrder(tmp, NULL, GX_COLOR_NULL);
                HSD_TExpAlphaOp(tmp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                                GX_ENABLE);
                HSD_TExpAlphaIn(tmp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                                HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                                HSD_TE_X, reg0_a);
                sel[i] = HSD_TE_A;
                exp[i] = tmp;
                break;
            case TOBJ_TEV_CA_TEX1_A:
                tmp = HSD_TExpTev(list);
                HSD_TExpOrder(tmp, NULL, GX_COLOR_NULL);
                HSD_TExpAlphaOp(tmp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                                GX_ENABLE);
                HSD_TExpAlphaIn(tmp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                                HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                                HSD_TE_X, reg1_a);
                sel[i] = HSD_TE_A;
                exp[i] = tmp;
                break;
            default:
                HSD_ASSERT(0x4F0, 0);
                break;
            }
        }

        HSD_TExpAlphaOp(e0, (GXTevOp) tev->alpha_op,
                        (GXTevBias) tev->alpha_bias,
                        (GXTevScale) tev->alpha_scale, tev->alpha_clamp);
        HSD_TExpAlphaIn(e0, sel[0], exp[0], sel[1], exp[1], sel[2], exp[2],
                        sel[3], exp[3]);

        *a = e0;
    }
}

static void TObjMakeTExp(HSD_TObj* tobj, u32 lightmap, u32 lightmap_done,
                         HSD_TExp** c, HSD_TExp** a, HSD_TExp** list)
{
    HSD_TExp *e0, *e1;
    HSD_TExp *c_src, *a_src;
    HSD_TEInput c_sel, a_sel;
    int repeat = (lightmap_done & tobj_lightmap(tobj));

    c_src = HSD_TEXP_TEX;
    c_sel = HSD_TE_RGB;

    a_src = HSD_TEXP_TEX;
    a_sel = HSD_TE_A;

    e0 = HSD_TExpTev(list);

    if (tobj->tev && (tobj->tev->active & (TOBJ_TEVREG_ACTIVE_COLOR_TEV |
                                           TOBJ_TEVREG_ACTIVE_ALPHA_TEV)))
    {
        MakeColorGenTExp(lightmap, tobj, &c_src, &a_src, list, repeat);
    }

    HSD_TExpOrder(e0, tobj, GX_COLOR_NULL);

    switch (tobj_colormap(tobj)) {
    case TEX_COLORMAP_ALPHA_MASK:
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, HSD_TE_RGB, *c, c_sel, c_src, a_sel, a_src,
                        HSD_TE_0, HSD_TEXP_ZERO);
        break;
    case TEX_COLORMAP_RGB_MASK:
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, HSD_TE_RGB, *c, c_sel, c_src, c_sel, c_src,
                        HSD_TE_0, HSD_TEXP_ZERO);
        break;
    case TEX_COLORMAP_BLEND:
        e1 = HSD_TExpCnst(&tobj->blending, HSD_TE_X, HSD_TE_F32, list);
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, HSD_TE_RGB, *c, c_sel, c_src, HSD_TE_X, e1,
                        HSD_TE_0, HSD_TEXP_ZERO);
        break;
    case TEX_COLORMAP_MODULATE:
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, *c, c_sel,
                        c_src, HSD_TE_0, HSD_TEXP_ZERO);
        break;
    case TEX_COLORMAP_REPLACE:
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, c_sel, c_src);
        break;
    case TEX_COLORMAP_NONE:
    case TEX_COLORMAP_PASS:
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, *c);
        break;
    case TEX_COLORMAP_ADD:
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, c_sel, c_src, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                        HSD_TEXP_ZERO, HSD_TE_RGB, *c);
        break;
    case TEX_COLORMAP_SUB:
        HSD_TExpColorOp(e0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, c_sel, c_src, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                        HSD_TEXP_ZERO, HSD_TE_RGB, *c);
        break;
    default:
        HSD_ASSERT(1372, 0);
    }
    *c = e0;

    if (!repeat) {
        switch (tobj_alphamap(tobj)) {
        case TEX_ALPHAMAP_ALPHA_MASK:
            HSD_TExpAlphaOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, HSD_TE_A, *a, a_sel, a_src, a_sel, a_src,
                            HSD_TE_0, HSD_TEXP_ZERO);
            break;
        case TEX_ALPHAMAP_BLEND:
            e1 = HSD_TExpCnst(&tobj->blending, HSD_TE_X, HSD_TE_F32, list);
            HSD_TExpAlphaOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, HSD_TE_A, *a, a_sel, a_src, HSD_TE_X, e1,
                            HSD_TE_0, HSD_TEXP_ZERO);
            break;
        case TEX_ALPHAMAP_MODULATE:
            HSD_TExpAlphaOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, *a, a_sel,
                            a_src, HSD_TE_0, HSD_TEXP_ZERO);
            break;
        case TEX_ALPHAMAP_REPLACE:
            HSD_TExpAlphaOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                            HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, a_sel,
                            a_src);
            break;
        case TEX_ALPHAMAP_NONE:
        case TEX_ALPHAMAP_PASS:
            HSD_TExpAlphaOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                            HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A,
                            *a);
            break;
        case TEX_ALPHAMAP_ADD:
            HSD_TExpAlphaOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, a_sel, a_src, HSD_TE_0, HSD_TEXP_ZERO,
                            HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, *a);
            break;
        case TEX_ALPHAMAP_SUB:
            HSD_TExpAlphaOp(e0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, a_sel, a_src, HSD_TE_0, HSD_TEXP_ZERO,
                            HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, *a);
            break;
        default:
            HSD_ASSERT(1430, 0);
        }
        *a = e0;
    }
}

s32 HSD_TObjAssignResources(HSD_TObj* tobj_top)
{
    HSD_TObj* tobj;
    u32 texmap_no = 0;
    u32 texcoord_no = 0;
    u32 limit = 8;
    HSD_TObj* bump = NULL;
    HSD_TObj* toon = NULL;

    if (tobj_top == NULL) {
        return 0;
    }

    for (tobj = tobj_top; tobj; tobj = tobj->next) {
        if (tobj_coord(tobj) == TEX_COORD_TOON) {
            toon = tobj;
        } else if (tobj_bump(tobj)) {
            bump = tobj;
        }
    }

    if (toon) {
        limit -= 1;
    }
    if (bump) {
        limit -= 2;
    }

    for (tobj = tobj_top; tobj; tobj = tobj->next) {
        if (tobj_coord(tobj) == TEX_COORD_TOON) {
            if (tobj != toon) {
                tobj->id = GX_TEXMAP_NULL;
            }
        } else if (tobj_bump(tobj)) {
            if (tobj != bump) {
                tobj->id = GX_TEXMAP_NULL;
            }
        } else if (texmap_no < limit) {
            tobj->id = HSD_Index2TexMap(texmap_no++);
            tobj->mtxid = HSD_TexMapID2PTTexMtx(tobj->id);
            switch (tobj_coord(tobj)) {
            case TEX_COORD_REFLECTION:
            case TEX_COORD_HILIGHT:
            case TEX_COORD_SHADOW:
                tobj->coord = HSD_Index2TexCoord(texcoord_no++);
                break;
            default:
                break;
            }
        } else {
            tobj->id = GX_TEXMAP_NULL;
        }
    }

    for (tobj = tobj_top; tobj; tobj = tobj->next) {
        if (tobj->id != GX_TEXMAP_NULL && !tobj_bump(tobj)) {
            switch (tobj_coord(tobj)) {
            case TEX_COORD_UV:
                tobj->coord = HSD_Index2TexCoord(texcoord_no++);
                break;
            default:
                break;
            }
        }
    }

    if (bump) {
        bump->id = HSD_Index2TexMap(texmap_no++);
        bump->mtxid = GX_TEXMTX9;
        bump->coord = HSD_Index2TexCoord(texcoord_no);
        texcoord_no += 2;
    }
    if (toon) {
        toon->id = HSD_Index2TexMap(texmap_no++);
        toon->coord = HSD_Index2TexCoord(texcoord_no++);
    }

    return (int) texcoord_no;
}

static int DifferentTluts(HSD_Tlut* t0, HSD_Tlut* t1)
{
    return (t0->lut != t0->lut) || (t0->n_entries != t1->n_entries);
}

void HSD_TObjSetup(HSD_TObj* tobj)
{
    GXTlutObj tlutobj;
    GXTexObj texobj;
    int num;
    HSD_Tlut* tluts[8];
    int nb_tluts = 0;
    u32 tlut_name = GX_TLUT0;
    u32 big_tlut_name = GX_BIGTLUT0;
    int i;

    tobj_head = tobj;

    if (tobj == NULL) {
        return;
    }

    num = HSD_TObjAssignResources(tobj);
    if (num > 0) {
        HSD_StateRegisterTexGen(HSD_Index2TexCoord(num - 1));
    }

    for (; tobj; tobj = tobj->next) {
        static HSD_TexLODDesc default_lod = {
            GX_LIN_MIP_LIN, 0.0F, GX_FALSE, GX_FALSE, GX_ANISO_1,
        };
        HSD_TexLODDesc* lod;
        HSD_ImageDesc* imagedesc = tobj->imagedesc;
        GXTexFilter min_filter;

        if (tobj->id == GX_TEXMAP_NULL) {
            continue;
        }

        TObjSetupMtx(tobj);
        HSD_ASSERT(1578, imagedesc);
        HSD_ASSERT(1579, imagedesc->image_ptr);

        lod = tobj->lod != NULL ? tobj->lod : &default_lod;
        min_filter = lod->minFilt;

        switch (imagedesc->format) {
        case GX_TF_C4:
        case GX_TF_C8:
        case GX_TF_C14X2: {
            HSD_Tlut* tlut;

            if (tobj->tlut_no != (u8) -1) {
                tlut = tobj->tluttbl[tobj->tlut_no];
            } else {
                tlut = tobj->tlut;
            }

            HSD_ASSERT(1595, tlut);

            for (i = 0; i < nb_tluts; i++) {
                if (!DifferentTluts(tluts[i], tlut)) {
                    break;
                }
            }
            if (i < nb_tluts) {
                tlut->tlut_name = tluts[i]->tlut_name;
            } else if (nb_tluts < 8) {
                if (tlut->n_entries >= 256) {
                    tlut->tlut_name = big_tlut_name++;
                } else {
                    tlut->tlut_name = tlut_name++;
                }
                GXInitTlutObj(&tlutobj, tlut->lut, tlut->fmt, tlut->n_entries);
                GXLoadTlut(&tlutobj, tlut->tlut_name);
                tluts[nb_tluts++] = tlut;
            } else {
                tlut->tlut_name = GX_TLUT0;
            }

            GXInitTexObjCI(&texobj, imagedesc->image_ptr, imagedesc->width,
                           imagedesc->height, (GXCITexFmt) imagedesc->format,
                           tobj->wrap_s, tobj->wrap_t,
                           imagedesc->mipmap ? GX_TRUE : GX_FALSE,
                           tlut->tlut_name);
            if (min_filter == GX_LIN_MIP_LIN) {
                min_filter = GX_LIN_MIP_NEAR;
            }
        } break;

        case GX_TF_I4:
        case GX_TF_I8:
        case GX_TF_IA4:
        case GX_TF_IA8:
        case GX_TF_RGB565:
        case GX_TF_RGB5A3:
        case GX_TF_RGBA8:
        case GX_TF_CMPR:
            GXInitTexObj(&texobj, imagedesc->image_ptr, imagedesc->width,
                         imagedesc->height, imagedesc->format, tobj->wrap_s,
                         tobj->wrap_t, imagedesc->mipmap ? GX_TRUE : GX_FALSE);
            break;

        default:
            HSD_ASSERT(0x677, 0);
        }

        if (!imagedesc->mipmap) {
            min_filter &= 0x01;
        }
        GXInitTexObjLOD(&texobj, min_filter, tobj->magFilt, imagedesc->minLOD,
                        imagedesc->maxLOD, lod->LODBias, lod->bias_clamp,
                        lod->edgeLODEnable, lod->max_anisotropy);

        GXLoadTexObj(&texobj, tobj->id);
    }
}

u32 HSD_TGTex2Index(GXTexGenSrc tgtex)
{
    switch (tgtex) {
    case GX_TG_TEX0:
        return 0;
    case GX_TG_TEX1:
        return 1;
    case GX_TG_TEX2:
        return 2;
    case GX_TG_TEX3:
        return 3;
    case GX_TG_TEX4:
        return 4;
    case GX_TG_TEX5:
        return 5;
    case GX_TG_TEX6:
        return 6;
    case GX_TG_TEX7:
        return 7;
    default:
        HSD_ASSERT(1701, 0);
    }
    return GX_TG_TEX0;
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

u32 HSD_TexCoord2Index(GXTexCoordID coord_id)
{
    switch (coord_id) {
    case GX_TEXCOORD0:
        return 0;
    case GX_TEXCOORD1:
        return 1;
    case GX_TEXCOORD2:
        return 2;
    case GX_TEXCOORD3:
        return 3;
    case GX_TEXCOORD4:
        return 4;
    case GX_TEXCOORD5:
        return 5;
    case GX_TEXCOORD6:
        return 6;
    case GX_TEXCOORD7:
        return 7;
    default:
        HSD_ASSERT(1776, 0);
    }
    return GX_TEXCOORD0;
}

GXTexCoordID HSD_Index2TexCoord(u32 index)
{
    switch (index) {
    case 0:
        return GX_TEXCOORD0;
    case 1:
        return GX_TEXCOORD1;
    case 2:
        return GX_TEXCOORD2;
    case 3:
        return GX_TEXCOORD3;
    case 4:
        return GX_TEXCOORD4;
    case 5:
        return GX_TEXCOORD5;
    case 6:
        return GX_TEXCOORD6;
    case 7:
        return GX_TEXCOORD7;
    default:
        HSD_ASSERT(1800, 0);
    }
    return GX_TEXCOORD0;
}

u32 HSD_TexMtx2Index(GXTexMtx texmtx)
{
    switch (texmtx) {
    case GX_TEXMTX0:
        return 0;
    case GX_TEXMTX1:
        return 1;
    case GX_TEXMTX2:
        return 2;
    case GX_TEXMTX3:
        return 3;
    case GX_TEXMTX4:
        return 4;
    case GX_TEXMTX5:
        return 5;
    case GX_TEXMTX6:
        return 6;
    case GX_TEXMTX7:
        return 7;
    case GX_TEXMTX8:
        return 8;
    case GX_TEXMTX9:
        return 9;
    case GX_IDENTITY:
        return 10;
    default:
        HSD_Panic(__FILE__, 1845, "specified texmtx id desn't exist.\n");
    }
    return (u32) -1;
}

GXTexMtx HSD_Index2TexMtx(u32 index)
{
    switch (index) {
    case 0:
        return GX_TEXMTX0;
    case 1:
        return GX_TEXMTX1;
    case 2:
        return GX_TEXMTX2;
    case 3:
        return GX_TEXMTX3;
    case 4:
        return GX_TEXMTX4;
    case 5:
        return GX_TEXMTX5;
    case 6:
        return GX_TEXMTX6;
    case 7:
        return GX_TEXMTX7;
    case 8:
        return GX_TEXMTX8;
    case 9:
        return GX_TEXMTX9;
    case 10:
        return GX_IDENTITY;
    default:
        OSReport("texmtx index exceed hardware limit (%d).\n", index);
        HSD_Panic(__FILE__, 1877, "");
    }
    return GX_IDENTITY;
}

GXTexMapID HSD_Index2TexMap(u32 index)
{
    switch (index) {
    case 0:
        return GX_TEXMAP0;
    case 1:
        return GX_TEXMAP1;
    case 2:
        return GX_TEXMAP2;
    case 3:
        return GX_TEXMAP3;
    case 4:
        return GX_TEXMAP4;
    case 5:
        return GX_TEXMAP5;
    case 6:
        return GX_TEXMAP6;
    case 7:
        return GX_TEXMAP7;
    default:
        HSD_ASSERT(1915, 0);
    }
    return GX_TEXMAP0;
}

u32 HSD_TexMap2Index(GXTexMapID mapid)
{
    switch (mapid) {
    case GX_TEXMAP0:
        return 0;
    case GX_TEXMAP1:
        return 1;
    case GX_TEXMAP2:
        return 2;
    case GX_TEXMAP3:
        return 3;
    case GX_TEXMAP4:
        return 4;
    case GX_TEXMAP5:
        return 5;
    case GX_TEXMAP6:
        return 6;
    case GX_TEXMAP7:
        return 7;
    default:
        HSD_ASSERT(1939, 0);
    }
    return 0;
}

void HSD_TObjRemove(HSD_TObj* tobj)
{
    hsdDelete(tobj);
}

void HSD_TObjRemoveAll(HSD_TObj* tobj)
{
    while (tobj) {
        HSD_TObj* next = tobj->next;
        HSD_TObjRemove(tobj);
        tobj = next;
    }
}

HSD_TObj* HSD_TObjGetNext(HSD_TObj* tobj)
{
    if (tobj == NULL) {
        return NULL;
    }

    return tobj->next;
}

void HSD_TObjSetDefaultClass(HSD_TObjInfo* info)
{
    if (info) {
        HSD_ASSERT(2027, hsdIsDescendantOf(info, &hsdTObj));
    }
    default_class = info;
}

HSD_TObjInfo* HSD_TObjGetDefaultClass(void)
{
    return default_class ? default_class : &hsdTObj;
}

HSD_TObj* HSD_TObjAlloc(void)
{
    HSD_TObj* new = hsdNew((HSD_ClassInfo*) HSD_TObjGetDefaultClass());
    HSD_ASSERT(2040, new);
    return new;
}

void HSD_TObjFree(HSD_TObj* tobj)
{
    if (tobj) {
        HSD_CLASS_METHOD(tobj)->destroy((HSD_Class*) tobj);
    }
}

HSD_Tlut* HSD_TlutAlloc(void)
{
    HSD_Tlut* tlut = hsdAllocMemPiece(sizeof(HSD_Tlut));
    HSD_ASSERT(2069, tlut);
    memset(tlut, 0, sizeof(HSD_Tlut));
    return tlut;
}

void HSD_TlutFree(HSD_Tlut* tlut)
{
    hsdFreeMemPiece(tlut, sizeof(HSD_Tlut));
}

void HSD_TlutRemove(HSD_Tlut* tlut)
{
    if (tlut) {
        hsdFreeMemPiece(tlut, sizeof(HSD_Tlut));
    }
}

HSD_TObjTev* HSD_TObjTevAlloc(void)
{
    HSD_TObjTev* tev = hsdAllocMemPiece(sizeof(HSD_TObjTev));
    HSD_ASSERT(2112, tev);
    memset(tev, 0, sizeof(HSD_TObjTev));
    return tev;
}

void HSD_TObjTevFree(HSD_TObjTev* tev)
{
    hsdFreeMemPiece(tev, sizeof(HSD_TObjTev));
}

void HSD_TObjTevRemove(HSD_TObjTev* tev)
{
    if (tev) {
        HSD_TObjTevFree(tev);
    }
}

HSD_ImageDesc* HSD_ImageDescAlloc(void)
{
    HSD_ImageDesc* idesc = hsdAllocMemPiece(sizeof(HSD_ImageDesc));
    HSD_ASSERT(2155, idesc);
    memset(idesc, 0, sizeof(HSD_ImageDesc));
    return idesc;
}

void HSD_ImageDescFree(HSD_ImageDesc* idesc)
{
    hsdFreeMemPiece(idesc, sizeof(HSD_ImageDesc));
}

void HSD_ImageDescCopyFromEFB(HSD_ImageDesc* idesc, u16 origx, u16 origy,
                              GXBool clear, int sync)
{
    if (!idesc) {
        return;
    }

    GXSetTexCopySrc(origx, origy, idesc->width, idesc->height);
    GXSetTexCopyDst(idesc->width, idesc->height, idesc->format,
                    idesc->mipmap ? GX_TRUE : GX_FALSE);
    if (clear) {
        HSD_StateSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    }
    GXCopyTex(idesc->image_ptr, clear);
    if (sync) {
        GXPixModeSync();
        GXInvalidateTexAll();
    }
}

static void TObjRelease(HSD_Class* o)
{
    HSD_TObj* tobj = HSD_TOBJ(o);

    HSD_AObjRemove(tobj->aobj);
    HSD_TlutRemove(tobj->tlut);
    HSD_TObjTevRemove(tobj->tev);
    if (tobj->tluttbl) {
        int i;
        for (i = 0; tobj->tluttbl[i]; i++) {
            HSD_TlutRemove(tobj->tluttbl[i]);
        }
        HSD_Free(tobj->tluttbl);
    }

    HSD_PARENT_INFO(&hsdTObj)->release(o);
}

static void TObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    if (info == HSD_CLASS_INFO(&hsdTObj)) {
        tobj_head = NULL;
    }
    HSD_PARENT_INFO(&hsdTObj)->amnesia(info);
}

static void TObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdTObj), HSD_CLASS_INFO(&hsdObj),
                     "sysdolphin_base_library", "hsd_tobj",
                     sizeof(HSD_TObjInfo), sizeof(HSD_TObj));

    HSD_CLASS_INFO(&hsdTObj)->release = TObjRelease;
    HSD_CLASS_INFO(&hsdTObj)->amnesia = TObjAmnesia;
    HSD_TOBJ_INFO(&hsdTObj)->load = TObjLoad;
    HSD_TOBJ_INFO(&hsdTObj)->make_texp = TObjMakeTExp;

    hsdTObj.make_mtx = MakeTextureMtx;
}
