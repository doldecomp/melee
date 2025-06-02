#include "forward.h"

#include "lobj.h"

#include "aobj.h"
#include "class.h"
#include "cobj.h"
#include "list.h"
#include "object.h"
#include "wobj.h"

#include <dolphin/mtx.h>
#include <dolphin/os.h>

static void LObjInfoInit(void);

HSD_LObjInfo hsdLObj = { LObjInfoInit };

static HSD_LObjInfo* default_class = NULL;

static HSD_SList* current_lights;
static HSD_LObj* active_lights[GX_MAX_LIGHT];
static s32 nb_active_lights = 0;

static s32 lightmask_diffuse;
static s32 lightmask_specular;
static s32 lightmask_attnfunc;
static s32 lightmask_alpha;

u32 HSD_LObjGetFlags(HSD_LObj* lobj)
{
    return (lobj) ? lobj->flags : 0;
}

void HSD_LObjSetFlags(HSD_LObj* lobj, u32 flags)
{
    if (lobj == NULL) {
        return;
    }
    lobj->flags |= flags;
}

void HSD_LObjClearFlags(HSD_LObj* lobj, u32 flags)
{
    if (lobj == NULL) {
        return;
    }
    lobj->flags &= ~flags;
}

GXLightID HSD_LObjGetLightMaskDiffuse(void)
{
    return lightmask_diffuse;
}

s32 HSD_LObjGetLightMaskAttnFunc(void)
{
    return lightmask_attnfunc;
}

s32 HSD_LObjGetLightMaskAlpha(void)
{
    return lightmask_alpha;
}

s32 HSD_LObjGetLightMaskSpecular(void)
{
    return lightmask_specular;
}

u32 HSD_LObjGetType(HSD_LObj* lobj)
{
    return lobj->flags & 0x3;
}

void HSD_LObjSetActive(HSD_LObj* lobj)
{
    int idx;

    if (HSD_LObjGetType(lobj) == LOBJ_AMBIENT) {
        idx = GX_MAX_LIGHT - 1;
        if (active_lights[idx]) {
            return;
        }
    } else {
        idx = nb_active_lights++;
    }
    active_lights[idx] = lobj;
    lobj->id = HSD_Index2LightID(idx);
}

s32 HSD_LObjGetNbActive(void)
{
    return nb_active_lights;
}

HSD_LObj* HSD_LObjGetActiveByID(GXLightID id)
{
    s32 idx = HSD_LightID2Index(id);
    if (0 <= idx && idx < GX_MAX_LIGHT) {
        return active_lights[idx];
    } else {
        return NULL;
    }
}

HSD_LObj* HSD_LObjGetActiveByIndex(s32 idx)
{
    if (0 <= idx && idx < GX_MAX_LIGHT - 1) {
        return active_lights[idx];
    } else {
        return NULL;
    }
}

void HSD_LObjClearActive(void)
{
    int i;

    for (i = 0; i < GX_MAX_LIGHT; i++) {
        active_lights[i] = NULL;
    }
    nb_active_lights = 0;
}

/// @private
void LObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val)
{
    HSD_LObj* lobj = obj;

    if (lobj == NULL) {
        return;
    }

    switch (type) {
    case HSD_A_L_VIS:
        if (val->fv < 0.5) {
            lobj->flags &= ~LOBJ_HIDDEN;
        } else {
            lobj->flags |= LOBJ_HIDDEN;
        }
        break;
    case HSD_A_L_A0:
    case HSD_A_L_CUTOFF:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.a0 = val->fv;
        } else {
            lobj->u.spot.cutoff = val->fv;
        }
        break;
    case HSD_A_L_A1:
    case HSD_A_L_REFDIST:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.a1 = val->fv;
        } else {
            lobj->u.spot.ref_dist = val->fv;
        }
        break;
    case HSD_A_L_A2:
    case HSD_A_L_REFBRIGHT:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.a2 = val->fv;
        } else {
            lobj->u.spot.ref_br = val->fv;
        }
        break;
    case HSD_A_L_K0:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.k0 = val->fv;
        }
        break;
    case HSD_A_L_K1:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.k1 = val->fv;
        }
        break;
    case HSD_A_L_K2:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.k2 = val->fv;
        }
        break;
    case HSD_A_L_LITC_R:
        lobj->color.r = 255.0 * val->fv;
        break;
    case HSD_A_L_LITC_G:
        lobj->color.g = 255.0 * val->fv;
        break;
    case HSD_A_L_LITC_B:
        lobj->color.b = 255.0 * val->fv;
        break;
    case HSD_A_L_LITC_A:
        lobj->color.a = 255.0 * val->fv;
        break;
    }
}

void HSD_LObjAnim(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        HSD_AObjInterpretAnim(lobj->aobj, lobj, &LObjUpdateFunc);
        HSD_WObjInterpretAnim(HSD_LObjGetPositionWObj(lobj));
        HSD_WObjInterpretAnim(HSD_LObjGetInterestWObj(lobj));
    }
}

void HSD_LObjAnimAll(HSD_LObj* lobj)
{
    HSD_LObj* lp;

    if (lobj == NULL) {
        return;
    }

    for (lp = lobj; lp; lp = lp->next) {
        HSD_LObjAnim(lp);
    }
}

void HSD_LObjReqAnim(HSD_LObj* lobj, f32 startframe)
{
    if (lobj == NULL) {
        return;
    }

    HSD_AObjReqAnim(lobj->aobj, startframe);
    HSD_WObjReqAnim(HSD_LObjGetPositionWObj(lobj), startframe);
    HSD_WObjReqAnim(HSD_LObjGetInterestWObj(lobj), startframe);
}

void HSD_LObjReqAnimAll(HSD_LObj* lobj, f32 startframe)
{
    HSD_LObj* lp;

    if (lobj == NULL) {
        return;
    }

    for (lp = lobj; lp; lp = lp->next) {
        HSD_LObjReqAnim(lp, startframe);
    }
}

Vec3 const HSD_LObj_803B94A0 = { 0.0F, 0.0F, 0.0F };
Vec3 const HSD_LObj_803B94AC = { 0.0F, 0.0F, 0.0F };

void HSD_LObjGetLightVector(HSD_LObj* lobj, Vec3* dir)
{
    Vec3 position = HSD_LObj_803B94A0;
    Vec3 interest = HSD_LObj_803B94AC;

    if (lobj == NULL) {
        return;
    }

    HSD_LObjGetPosition(lobj, &position);
    HSD_LObjGetInterest(lobj, &interest);
    PSVECSubtract(&interest, &position, dir);
    PSVECNormalize(dir, dir);
}

f32 const lbl_804DE450 = 0.5F;
f32 const lbl_804DE454 = 0.0F;
f32 const lbl_804DE458 = 1.0F;

void HSD_LObjSetup(HSD_LObj* lobj, GXColor color, f32 shininess)
{
    f32 k0 = shininess;

    if (lobj->flags & LOBJ_HIDDEN || HSD_LObjGetType(lobj) == LOBJ_AMBIENT) {
        return;
    }

    if ((lobj->flags & LOBJ_DIFFUSE) != 0) {
        if (lobj->hw_color.r != color.r || lobj->hw_color.g != color.g ||
            lobj->hw_color.b != color.b || lobj->hw_color.a != color.a)
        {
            GXInitLightColor(&lobj->lightobj, color);
            lobj->hw_color = color;
            lobj->flags |= LOBJ_DIFF_DIRTY;
        }

        if (lobj->flags & LOBJ_DIFF_DIRTY) {
            GXLoadLightObjImm(&lobj->lightobj, lobj->id);
            lobj->flags &= ~LOBJ_DIFF_DIRTY;
        }
    }

    if (lobj->spec_id != GX_LIGHT_NULL) {
        if (lobj->shininess != shininess) {
            lobj->shininess = shininess;
            k0 *= 0.5F;
            GXInitLightAttn(&lobj->spec_lightobj, 0.0F, 0.0F, 1.0F, k0, 0.0F,
                            1.0F - k0);
            lobj->flags |= LOBJ_SPEC_DIRTY;
        }

        if (lobj->flags & LOBJ_SPEC_DIRTY) {
            GXLoadLightObjImm(&lobj->spec_lightobj, lobj->spec_id);
            lobj->flags &= ~LOBJ_SPEC_DIRTY;
        }
    }
}

void HSD_LObjSetupSpecularInit(Mtx pmtx)
{
    int i;
    s32 num;
    Vec3 cdir;
    Vec3 jpos;

    jpos.x = pmtx[0][3];
    jpos.y = pmtx[1][3];
    jpos.z = pmtx[2][3];
    PSVECNormalize(&jpos, &cdir);

    num = HSD_LObjGetNbActive();
    for (i = 0; i < num; i++) {
        Vec3 half, ldir;
        HSD_LObj* lobj = HSD_LObjGetActiveByIndex(i);

        if (lobj->spec_id == GX_LIGHT_NULL) {
            continue;
        }

        switch (HSD_LObjGetType(lobj)) {
        case LOBJ_POINT:
        case LOBJ_SPOT:
            PSVECSubtract(&jpos, &lobj->lvec, &ldir);
            PSVECNormalize(&ldir, &ldir);
            PSVECAdd(&ldir, &cdir, &half);
            break;

        case LOBJ_INFINITE:
            PSVECAdd(&lobj->lvec, &cdir, &half);
            break;

        default:
            __assert(__FILE__, 617, "0");
        }
        PSVECNormalize(&half, &half);
        GXInitLightDir(&lobj->spec_lightobj, half.x, half.y, half.z);
        lobj->flags |= LOBJ_SPEC_DIRTY;
    }
}

static void setup_diffuse_lightobj(HSD_LObj* lobj)
{
    u32 _ = lobj->flags;

    GXInitLightColor(&lobj->lightobj, lobj->color);
    lobj->hw_color = lobj->color;
    lobj->flags |= LOBJ_DIFF_DIRTY;
    lightmask_diffuse |= lobj->id;

    switch (HSD_LObjGetType(lobj)) {
    case LOBJ_SPOT:
    case LOBJ_POINT:
        lightmask_attnfunc |= lobj->id;
        break;
    case LOBJ_INFINITE:
        break;
    default:
        __assert(__FILE__, 642, "0");
    }

    if (lobj->flags & LOBJ_ALPHA) {
        lightmask_alpha |= lobj->id;
    }
}

static void setup_spec_lightobj(HSD_LObj* lobj, Mtx mtx, s32 spec_id)
{
    f32 x;

    lobj->spec_id = spec_id;
    if (spec_id != 0) {
        GXInitLightColor(&lobj->spec_lightobj, lobj->color);
        lobj->shininess = 50.0F;

        x = x = lobj->shininess;

        x *= 0.5F;
        GXInitLightAttn(&lobj->spec_lightobj, 0.0F, 0.0F, 1.0F, x, 0.0F,
                        1.0F - x);
        switch (HSD_LObjGetType(lobj)) {
        case 2:
        case 3:
            HSD_LObjGetPosition(lobj, &lobj->lvec);
            MTXMultVec(mtx, &lobj->lvec, &lobj->lvec);
            break;
        case 1:
            HSD_LObjGetLightVector(lobj, &lobj->lvec);
            PSMTXMultVecSR(mtx, &lobj->lvec, &lobj->lvec);
            VECNormalize(&lobj->lvec, &lobj->lvec);
            break;
        default:
            __assert(__FILE__, 680, "0");
        }
        lobj->flags |= 0x100;
        lightmask_specular |= spec_id;
    }
}

static void setup_infinite_lightobj(HSD_LObj* lobj, MtxPtr vmtx)
{
    Vec3 lpos;

    HSD_LObjGetPosition(lobj, &lpos);
    lpos.x *= 1048576.0F;
    lpos.y *= 1048576.0F;
    lpos.z *= 1048576.0F;
    MTXMultVec(vmtx, &lpos, &lpos);
    if (lobj->flags & LOBJ_DIFFUSE) {
        GXInitLightPos(&lobj->lightobj, lpos.x, lpos.y, lpos.z);
        GXInitLightAttn(&lobj->lightobj, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    }
    if (lobj->flags & LOBJ_SPECULAR) {
        GXInitLightPos(&lobj->spec_lightobj, lpos.x, lpos.y, lpos.z);
    }
}

static void setup_point_lightobj(HSD_LObj* lobj, Mtx mtx)
{
    Vec3 lpos;

    GXInitLightColor(&lobj->lightobj, lobj->color);
    lobj->hw_color = lobj->color;
    HSD_LObjGetPosition(lobj, &lpos);
    MTXMultVec(mtx, &lpos, &lpos);
    GXInitLightPos(&lobj->lightobj, lpos.x, lpos.y, lpos.z);
    GXInitLightPos(&lobj->spec_lightobj, lpos.x, lpos.y, lpos.z);
    if (lobj->flags & 0x40) {
        GXInitLightAttn(&lobj->lightobj, 1.0F, 0.0F, 0.0F, lobj->u.attn.k0,
                        lobj->u.attn.k1, lobj->u.attn.k2);
    } else {
        f32 ref_br = lobj->u.spot.ref_br;
        f32 ref_dist = lobj->u.spot.ref_dist;
        s32 dist_func = lobj->u.spot.dist_func;
        GXInitLightDistAttn(&lobj->lightobj, ref_dist, ref_br, dist_func);
        GXInitLightSpot(&lobj->lightobj, 0.0F, 0);
        GXInitLightDistAttn(&lobj->spec_lightobj, ref_dist, ref_br, dist_func);
    }
}

static void setup_spot_lightobj(HSD_LObj* lobj, Mtx mtx)
{
    Vec3 lpos;
    Vec3 ldir;

    HSD_LObjGetPosition(lobj, &lpos);
    MTXMultVec(mtx, &lpos, &lpos);
    HSD_LObjGetLightVector(lobj, &ldir);
    PSMTXMultVecSR(mtx, &ldir, &ldir);
    PSVECNormalize(&ldir, &ldir);
    GXInitLightPos(&lobj->lightobj, lpos.x, lpos.y, lpos.z);
    GXInitLightPos(&lobj->spec_lightobj, lpos.x, lpos.y, lpos.z);
    GXInitLightDir(&lobj->lightobj, ldir.x, ldir.y, ldir.z);
    if (lobj->flags & 0x40) {
        GXInitLightAttn(&lobj->lightobj, lobj->u.attn.a0, lobj->u.attn.a1,
                        lobj->u.attn.a2, lobj->u.attn.k0, lobj->u.attn.k1,
                        lobj->u.attn.k2);
    } else {
        f32 ref_br = lobj->u.point.ref_br;
        f32 ref_dist = lobj->u.point.ref_dist;
        f32 cutoff = lobj->u.point.cutoff;
        s32 spot_func = lobj->u.spot.spot_func;
        s32 dist_func = lobj->u.spot.dist_func;

        GXInitLightDistAttn(&lobj->lightobj, ref_dist, ref_br, dist_func);
        GXInitLightDistAttn(&lobj->spec_lightobj, ref_dist, ref_br, dist_func);
        GXInitLightSpot(&lobj->lightobj, cutoff, spot_func);
    }
}

void HSD_LObjSetupInit(HSD_CObj* cobj)
{
    MtxPtr vmtx;
    int i, num, idx;
    HSD_SList* list;

    idx = 0;
    num = 0;

    lightmask_diffuse = GX_LIGHT_NULL;
    lightmask_specular = GX_LIGHT_NULL;
    lightmask_attnfunc = GX_LIGHT_NULL;
    lightmask_alpha = GX_LIGHT_NULL;
    vmtx = cobj->view_mtx;

    HSD_LObjClearActive();

    for (list = current_lights; idx < GX_MAX_LIGHT - 1 && list;
         list = list->next)
    {
        HSD_LObj* lobj = list->data;
        u32 flags;
        u32 type;
        int ref_type;

        HSD_ASSERT(0x334, lobj);
        flags = lobj->flags;

        if (flags & LOBJ_HIDDEN) {
            continue;
        }

        type = HSD_LObjGetType(lobj);
        ref_type = flags & (LOBJ_DIFFUSE | LOBJ_SPECULAR);

        if (type != 0) {
            switch (ref_type) {
            case 8:
                if (num >= 8) {
                    continue;
                }
                break;
            case 4:
            case 12:
                break;
            default:
                continue;
            }
        }

        HSD_LObjSetActive(lobj);
        idx = HSD_LObjGetNbActive();

        lobj->spec_id = GX_LIGHT_NULL;

        switch (type) {
        case LOBJ_INFINITE:
            setup_infinite_lightobj(lobj, vmtx);
            break;
        case LOBJ_POINT:
            setup_point_lightobj(lobj, vmtx);
            break;
        case LOBJ_SPOT:
            setup_spot_lightobj(lobj, vmtx);
            break;
        case LOBJ_AMBIENT:
            continue;
        }

        switch (ref_type) {
        case LOBJ_DIFFUSE | LOBJ_SPECULAR:
        case LOBJ_DIFFUSE:
            setup_diffuse_lightobj(lobj);
            break;
        case LOBJ_SPECULAR:
            setup_spec_lightobj(lobj, vmtx, lobj->id);
            num++;
            break;
        }
    }

    if (!HSD_LObjGetActiveByID(256)) {
        for (; list; list = list->next) {
            HSD_LObj* lobj = list->data;
            HSD_ASSERT(0x372, lobj);

            if (HSD_LObjGetType(lobj) == LOBJ_AMBIENT &&
                !(lobj->flags & LOBJ_HIDDEN))
            {
                HSD_LObjSetActive(lobj);
                break;
            }
        }
    }

    for (list = current_lights;
         list != NULL && num < GX_MAX_LIGHT - 1 && idx < GX_MAX_LIGHT - 1;
         list = list->next)
    {
        HSD_LObj* lobj = list->data;
        u32 flags = lobj->flags;

        if ((flags & 0x2C) != (LOBJ_SPECULAR | LOBJ_DIFFUSE)) {
            continue;
        }
        setup_spec_lightobj(lobj, vmtx, HSD_Index2LightID(idx++));
        num++;
    }

    for (i = 0; i < GX_MAX_LIGHT - 1; i++) {
        HSD_LObj* lobj;

        if (!(lobj = HSD_LObjGetActiveByIndex(i))) {
            return;
        }
        HSD_LObjSetup(lobj, lobj->color, lobj->shininess);
    }
}

void HSD_LObjAddCurrent(HSD_LObj* lobj)
{
    HSD_SList* node;
    HSD_SList** p;

    if (lobj != NULL) {
        node = current_lights;
        while (node != NULL) {
            if (node->data == lobj) {
                HSD_LObjDeleteCurrent(lobj);
                break;
            }
            node = node->next;
        }
        ref_INC(lobj);
        for (p = &current_lights; *p != NULL; p = &(*p)->next) {
            if (HSD_LObjGetPriority((*p)->data) > HSD_LObjGetPriority(lobj)) {
                break;
            }
        }
        *p = HSD_SListAllocAndPrepend(*p, lobj);
    }
}

void HSD_LObjUnrefThis(HSD_LObj* lobj)
{
    if (lobj != NULL && ref_DEC(lobj)) {
        if (lobj != NULL) {
            HSD_OBJECT_METHOD(lobj)->release((HSD_Class*) lobj);
            HSD_OBJECT_METHOD(lobj)->destroy((HSD_Class*) lobj);
        }
    }
}

void HSD_LObjDeleteCurrent(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        HSD_SList** p;
        for (p = &current_lights; *p != NULL; p = &(*p)->next) {
            if ((*p)->data == lobj) {
                int i;
                for (i = 0; i < GX_MAX_LIGHT; i++) {
                    if (lobj == active_lights[i]) {
                        active_lights[i] = NULL;
                    }
                }
                *p = HSD_SListRemove(*p);
                HSD_LObjUnrefThis(lobj);
                return;
            }
        }
    }
}

inline void LObjRemoveAll(void)
{
    int i;
    for (i = 0; i < GX_MAX_LIGHT; i++) {
        active_lights[i] = NULL;
    }
    nb_active_lights = 0;
    while (current_lights != NULL) {
        HSD_LObjUnrefThis(current_lights->data);
        current_lights = HSD_SListRemove(current_lights);
    }
}

void HSD_LObjDeleteCurrentAll(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        while (lobj != NULL) {
            HSD_LObjDeleteCurrent(lobj);
            lobj = lobj->next;
        }
        return;
    }
    LObjRemoveAll();
}

void HSD_LObjSetCurrentAll(HSD_LObj* lobj)
{
    u32 _;

    LObjRemoveAll();
    HSD_LObjAddCurrent(lobj);
}

inline void LObjReplaceAll(HSD_LObj* lobj)
{
    int i;
    HSD_LObj* cur;
    for (i = 0; i < GX_MAX_LIGHT; i++) {
        active_lights[i] = NULL;
    }
    nb_active_lights = 0;
    while (current_lights != NULL) {
        HSD_LObjUnrefThis(current_lights->data);
        current_lights = HSD_SListRemove(current_lights);
    }
    for (cur = lobj; cur != NULL; cur = cur->next) {
        HSD_LObjAddCurrent(cur);
    }
}

void HSD_LObj_803668EC(HSD_LObj* lobj)
{
    PAD_STACK(4);

    LObjReplaceAll(lobj);
}

HSD_LObj* HSD_LObjGetCurrentByType(u16 flags)
{
    HSD_SList* cur = current_lights;
    u32 type = flags & LOBJ_TYPE_MASK;
    while (cur != NULL) {
        HSD_LObj* lobj = cur->data;
        if (type == (lobj->flags & LOBJ_TYPE_MASK)) {
            return lobj;
        }
        cur = cur->next;
    }
    return NULL;
}

u32 HSD_LightID2Index(GXLightID id)
{
    u32 index;
    switch (id) {
    case GX_LIGHT0:
        index = 0;
        break;
    case GX_LIGHT1:
        index = 1;
        break;
    case GX_LIGHT2:
        index = 2;
        break;
    case GX_LIGHT3:
        index = 3;
        break;
    case GX_LIGHT4:
        index = 4;
        break;
    case GX_LIGHT5:
        index = 5;
        break;
    case GX_LIGHT6:
        index = 6;
        break;
    case GX_LIGHT7:
        index = 7;
        break;
    case GX_MAX_LIGHT:
        index = 8;
        break;
    default:
        HSD_ASSERT(1170, 0);
        break;
    }
    return index;
}

s32 HSD_Index2LightID(u32 index)
{
    switch (index) {
    case 0:
        return GX_LIGHT0;
    case 1:
        return GX_LIGHT1;
    case 2:
        return GX_LIGHT2;
    case 3:
        return GX_LIGHT3;
    case 4:
        return GX_LIGHT4;
    case 5:
        return GX_LIGHT5;
    case 6:
        return GX_LIGHT6;
    case 7:
        return GX_LIGHT7;
    case 8:
        return GX_MAX_LIGHT;
    default:
        return GX_LIGHT_NULL;
    }
}

void HSD_LObjRemoveAll(HSD_LObj* lobj)
{
    HSD_LObj* next;
    HSD_LObj* cur;

    cur = lobj;
    while (cur != NULL) {
        next = cur->next;
        HSD_LObjDeleteCurrent(cur);
        HSD_LObjUnrefThis(cur);
        cur = next;
    }
}

void HSD_LObjSetColor(HSD_LObj* lobj, GXColor color)
{
    lobj->color = color;
}

void HSD_LObjGetColor(HSD_LObj* lobj, GXColor* color)
{
    *color = lobj->color;
}

void HSD_LObjSetSpot(HSD_LObj* lobj, f32 cutoff, s32 point_func)
{
    if (lobj != NULL) {
        lobj->u.point.cutoff = cutoff;
        lobj->u.point.point_func = point_func;
    }
}

void HSD_LObjSetDistAttn(HSD_LObj* lobj, f32 ref_dist, f32 ref_br,
                         s32 dist_func)
{
    if (lobj != NULL) {
        lobj->u.point.ref_dist = ref_dist;
        lobj->u.point.ref_br = ref_br;
        lobj->u.point.dist_func = dist_func;
    }
}

void HSD_LObjSetAttnA(HSD_LObj* lobj, f32 a0, f32 a1, f32 a2)
{
    if (lobj == NULL) {
        return;
    }

    lobj->u.attn.a0 = a0;
    lobj->u.attn.a1 = a1;
    lobj->u.attn.a2 = a2;
}

void HSD_LObjSetAttnK(HSD_LObj* lobj, f32 k0, f32 k1, f32 k2)
{
    if (lobj == NULL) {
        return;
    }

    lobj->u.attn.k0 = k0;
    lobj->u.attn.k1 = k1;
    lobj->u.attn.k2 = k2;
}

void HSD_LObjSetAttn(HSD_LObj* lobj, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1,
                     f32 k2)
{
    HSD_LObjSetAttnA(lobj, a0, a1, a2);
    HSD_LObjSetAttnK(lobj, k0, k1, k2);
}

extern char lbl_80406190[10];

void HSD_LObjSetPosition(HSD_LObj* lobj, Vec3* position)
{
    HSD_ASSERT(1369, lobj);
    if (lobj->position == NULL) {
        lobj->position = HSD_WObjAlloc();
        HSD_ASSERT(1372, lobj->position);
    }
    HSD_WObjSetPosition(lobj->position, position);
}

bool HSD_LObjGetPosition(HSD_LObj* lobj, Vec3* position)
{
    if (lobj != NULL && lobj->position != NULL) {
        HSD_WObjGetPosition(lobj->position, position);
        return true;
    }
    return false;
}

void HSD_LObjSetInterest(HSD_LObj* lobj, Vec3* interest)
{
    HSD_ASSERT(1405, lobj);
    if (lobj->interest == NULL) {
        lobj->interest = HSD_WObjAlloc();
        HSD_ASSERT(1408, lobj->interest);
    }
    HSD_WObjSetPosition(lobj->interest, interest);
}

bool HSD_LObjGetInterest(HSD_LObj* lobj, Vec3* interest)
{
    if (lobj != NULL && lobj->interest != NULL) {
        HSD_WObjGetPosition(lobj->interest, interest);
        return true;
    }
    return false;
}

void HSD_LObjSetDefaultClass(HSD_LObjInfo* info)
{
    if (info != NULL) {
        HSD_ASSERT(1420, hsdIsDescendantOf(info, &hsdLObj));
    }
    default_class = info;
}

HSD_LObjInfo* HSD_LObjGetDefaultClass(void)
{
    return default_class ? default_class : &hsdLObj;
}

HSD_LObj* HSD_LObjAlloc(void)
{
    HSD_LObj* new = hsdNew((HSD_ClassInfo*) HSD_LObjGetDefaultClass());
    HSD_ASSERT(1478, new);
    return new;
}

HSD_WObj* HSD_LObjGetPositionWObj(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        return lobj->position;
    }
    return NULL;
}

HSD_WObj* HSD_LObjGetInterestWObj(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        return lobj->interest;
    }
    return NULL;
}

void HSD_LObjSetPositionWObj(HSD_LObj* lobj, HSD_WObj* wobj)
{
    if (lobj == NULL) {
        return;
    }

    HSD_WObjUnref(lobj->position);
    lobj->position = wobj;
}

void HSD_LObjSetInterestWObj(HSD_LObj* lobj, HSD_WObj* wobj)
{
    if (lobj == NULL) {
        return;
    }

    HSD_WObjUnref(lobj->interest);
    lobj->interest = wobj;
}

static int LObjLoad(HSD_LObj* lobj, HSD_LightDesc* ldesc)
{
    HSD_LObjSetColor(lobj, ldesc->color);
    HSD_LObjSetFlags(lobj, ldesc->flags);
    switch (ldesc->flags & LOBJ_TYPE_MASK) {
    case LOBJ_AMBIENT:
        break;
    case LOBJ_INFINITE:
        HSD_LObjSetPositionWObj(lobj, HSD_WObjLoadDesc(ldesc->position));
        break;
    case LOBJ_POINT:
        HSD_LObjSetPositionWObj(lobj, HSD_WObjLoadDesc(ldesc->position));
        if (ldesc->attnflags & LOBJ_LIGHT_ATTN) {
            HSD_LObjSetFlags(lobj, LOBJ_RAW_PARAM);
            HSD_LObjSetAttnK(lobj, ldesc->u.attn->k0, ldesc->u.attn->k1,
                             ldesc->u.attn->k2);
        } else {
            HSD_LObjSetDistAttn(lobj, ldesc->u.point->ref_dist,
                                ldesc->u.point->ref_br,
                                ldesc->u.point->dist_func);
        }
        break;
    case LOBJ_SPOT:
        HSD_LObjSetPositionWObj(lobj, HSD_WObjLoadDesc(ldesc->position));
        HSD_LObjSetInterestWObj(lobj, HSD_WObjLoadDesc(ldesc->interest));
        if (ldesc->attnflags != 0) {
            HSD_LObjSetFlags(lobj, LOBJ_RAW_PARAM);
            HSD_LObjSetAttn(lobj, ldesc->u.attn->a0, ldesc->u.attn->a1,
                            ldesc->u.attn->a2, ldesc->u.attn->k0,
                            ldesc->u.attn->k1, ldesc->u.attn->k2);
        } else {
            HSD_LObjSetDistAttn(lobj, ldesc->u.spot->ref_dist,
                                ldesc->u.spot->ref_br,
                                ldesc->u.spot->dist_func);
            HSD_LObjSetSpot(lobj, ldesc->u.spot->cutoff,
                            ldesc->u.spot->spot_func);
        }
        break;
    default:
        OSReport("unexpected lightdesc flags (%x)\n", ldesc->flags);
        HSD_Panic(__FILE__, 1610, "");
        break;
    }
    return 0;
}

HSD_LObj* HSD_LObjLoadDesc(HSD_LightDesc* ldesc)
{
    HSD_LObj *top, **p = &top;

    for (; ldesc; ldesc = ldesc->next) {
        HSD_ClassInfo* info;

        if (!ldesc->class_name ||
            !(info = hsdSearchClassInfo(ldesc->class_name)))
        {
            *p = HSD_LObjAlloc();
        } else {
            *p = hsdNew(info);
            HSD_ASSERT(1644, *p);
        }
        HSD_LOBJ_METHOD(*p)->load(*p, ldesc);
        p = &(*p)->next;
    }
    *p = NULL;

    return top;
}

void HSD_LObjAddAnim(HSD_LObj* lobj, HSD_LightAnim* lanim)
{
    if (lobj == NULL) {
        return;
    }

    if (lanim != NULL) {
        if (lobj->aobj) {
            HSD_AObjRemove(lobj->aobj);
        }
        lobj->aobj = HSD_AObjLoadDesc(lanim->aobjdesc);
        HSD_WObjAddAnim(HSD_LObjGetPositionWObj(lobj), lanim->position_anim);
        HSD_WObjAddAnim(HSD_LObjGetInterestWObj(lobj), lanim->interest_anim);
    }
}

void HSD_LObjAddAnimAll(HSD_LObj* lobj, HSD_LightAnim* lanim)
{
    HSD_LObj* lp;
    HSD_LightAnim* la;

    if (lobj == NULL) {
        return;
    }

    for (lp = lobj, la = lanim; lp; lp = next_p(lp), la = next_p(la)) {
        HSD_LObjAddAnim(lp, la);
    }
}

static void LObjRelease(HSD_Class* o)
{
    HSD_LObj* lobj = HSD_LOBJ(o);
    ///@todo Unused stack
    u8 _[8];

    HSD_AObjRemove(lobj->aobj);
    HSD_WObjUnref(HSD_LObjGetPositionWObj(lobj));
    HSD_WObjUnref(HSD_LObjGetInterestWObj(lobj));

    HSD_OBJECT_PARENT_INFO(&hsdLObj)->release(o);
}

static void LObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    if (info == HSD_CLASS_INFO(&hsdLObj)) {
        current_lights = NULL;
    }
    HSD_OBJECT_PARENT_INFO(&hsdLObj)->amnesia(info);
}

static void LObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdLObj), HSD_CLASS_INFO(&hsdObj),
                     "sysdolphin_base_library", "hsd_lobj",
                     sizeof(HSD_LObjInfo), sizeof(HSD_LObj));
    HSD_CLASS_INFO(&hsdLObj)->release = LObjRelease;
    HSD_CLASS_INFO(&hsdLObj)->amnesia = LObjAmnesia;
    HSD_LOBJ_INFO(&hsdLObj)->load = LObjLoad;
}
