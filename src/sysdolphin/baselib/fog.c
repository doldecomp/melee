#include "fog.h"

#include "aobj.h"
#include "class.h"
#include "cobj.h"
#include "debug.h"
#include "object.h"

#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/mtx.h>

static void FogInfoInit(void);
static void FogAdjInfoInit(void);

HSD_FogInfo hsdFog = { FogInfoInit };
HSD_ClassInfo hsdFogAdj = { FogAdjInfoInit };

const GXColor HSD_Fog_804DE6F0 = { 0 };

void HSD_FogSet(HSD_Fog* fog)
{
    GXFogAdjTable tbl;
    f32 v[6];
    HSD_CObj* cobj;
    s32 range;
    struct {
        f32 x0;
        f32 v[6];
    } proj;

    if (fog == NULL) {
        GXSetFog(0, 0.0F, 0.0F, 0.0F, 0.0F, HSD_Fog_804DE6F0);
        return;
    }
    cobj = HSD_CObjGetCurrent();
    if (cobj == NULL) {
        HSD_Panic(__FILE__, 0x4D, "You must specify CObj first.\n");
    }
    GXSetFog(fog->type, fog->start, fog->end, HSD_CObjGetNear(cobj),
             HSD_CObjGetFar(cobj), fog->color);

    if (fog->fog_adj != NULL) {
        GXGetViewportv(v);
        range = v[0] + v[2] * (fog->fog_adj->center + 320) / 640.0F;
        if (range < 0) {
            range = 0;
        }
        if (range > 640) {
            range = 640;
        }
        if (fog->fog_adj->width != 0) {
            GXInitFogAdjTable(&tbl, fog->fog_adj->width, fog->fog_adj->mtx);
        } else {
            Mtx44 mtx = { 0 };

            /// @todo Eliminate cast
            GXGetProjectionv((f32*) &proj);

            switch ((s32) proj.x0) {
            case 0:
                mtx[0][0] = proj.v[0];
                mtx[0][2] = proj.v[1];
                mtx[1][1] = proj.v[2];
                mtx[1][2] = proj.v[3];
                mtx[2][2] = proj.v[4];
                mtx[2][3] = proj.v[5];
                mtx[3][2] = -1.0F;
                break;
            case 1:
                mtx[0][0] = proj.v[0];
                mtx[0][3] = proj.v[1];
                mtx[1][1] = proj.v[2];
                mtx[1][3] = proj.v[3];
                mtx[2][2] = proj.v[4];
                mtx[2][3] = proj.v[5];
                mtx[3][3] = 1.0F;
                break;
            }
            GXInitFogAdjTable(&tbl, v[2], mtx);
        }
        GXSetFogRangeAdj(1, range, &tbl);
        return;
    }
    GXSetFogRangeAdj(0, 0, NULL);
}

HSD_Fog* HSD_FogAlloc(void)
{
    HSD_Fog* fog = hsdNew((HSD_ClassInfo*) &hsdFog);
    HSD_ASSERT(0x8C, fog);
    return fog;
}

HSD_Fog* HSD_FogLoadDesc(HSD_FogDesc* desc)
{
    HSD_Fog* fog = HSD_FogAlloc();
    HSD_ASSERT(0x99, fog);
    HSD_FogInit(fog, desc);
    if (desc->fogadjdesc != NULL) {
        fog->fog_adj = HSD_FogAdjLoadDesc(desc->fogadjdesc);
    }
    return fog;
}

void HSD_FogInit(HSD_Fog* fog, HSD_FogDesc* desc)
{
    if (fog != NULL) {
        if (desc != NULL) {
            fog->type = desc->type;
            fog->start = desc->start;
            fog->end = desc->end;
            fog->color = desc->color;
        } else {
            f32 v[6];
            GXGetViewportv(v);
            fog->type = 2;
            fog->start = v[4];
            fog->end = v[5];
            fog->color.r = 0xFF;
            fog->color.g = 0xFF;
            fog->color.b = 0xFF;
            fog->color.a = 0xFF;
        }
    }
}

HSD_FogAdj* HSD_FogAdjAlloc(void)
{
    HSD_FogAdj* adj = hsdNew(&hsdFogAdj);
    HSD_ASSERT(0xD6, adj);
    return adj;
}

HSD_FogAdj* HSD_FogAdjLoadDesc(HSD_FogAdjDesc* desc)
{
    HSD_FogAdj* adj = HSD_FogAdjAlloc();
    HSD_ASSERT(0xE6, adj);
    HSD_FogAdjInit(adj, desc);
    return adj;
}

void HSD_FogAdjInit(HSD_FogAdj* adj, HSD_FogAdjDesc* desc)
{
    if (adj != NULL) {
        if (desc != NULL) {
            adj->width = desc->width;
            adj->center = desc->center;
            PSMTXCopy(desc->mtx, adj->mtx);
        } else {
            f32 v[6];
            GXGetViewportv(v);
            adj->width = v[2];
            adj->center = adj->width / 2;
            PSMTXIdentity(adj->mtx);
            adj->mtx[3][0] = 0.0F;
            adj->mtx[3][1] = 0.0F;
            adj->mtx[3][2] = 0.0F;
            adj->mtx[3][3] = 1.0F;
        }
    }
}

/// HSD_FogAddAnim ?
void HSD_Fog_8037DE7C(HSD_Fog* fog, HSD_AObjDesc* desc)
{
    if (fog != NULL) {
        if (fog->aobj != NULL) {
            HSD_AObjRemove(fog->aobj);
        }
        fog->aobj = HSD_AObjLoadDesc(desc);
    }
}

void HSD_FogReqAnim(HSD_Fog* fog, f32 frame)
{
    HSD_FogReqAnimByFlags(fog, 0x7FF, frame);
}

void HSD_FogReqAnimByFlags(HSD_Fog* fog, u32 flags, f32 frame)
{
    if (fog == NULL || !(flags & 0x200)) {
        return;
    }
    HSD_AObjReqAnim(fog->aobj, frame);
}

void HSD_FogInterpretAnim(HSD_Fog* fog)
{
    if (fog != NULL) {
        HSD_AObjInterpretAnim(fog->aobj, fog, FogUpdateFunc);
    }
}

void FogUpdateFunc(void* obj, enum_t type, HSD_ObjData* val)
{
    HSD_Fog* fog = obj;
    if (fog != NULL) {
        switch (type) {
        case 1:
            fog->start = val->fv;
            return;
        case 2:
            fog->end = val->fv;
            return;
        case 5:
            fog->color.r = 255.0F * val->fv;
            return;
        case 6:
            fog->color.g = 255.0F * val->fv;
            return;
        case 7:
            fog->color.b = 255.0F * val->fv;
            return;
        case 8:
            fog->color.a = 255.0F * val->fv;
            return;
        case 20:
            if (fog->fog_adj != NULL) {
                fog->fog_adj->center = val->fv;
            }
            break;
        }
    }
}

static void FogRelease(HSD_Fog* fog)
{
    if (fog->fog_adj != NULL) {
        HSD_FogAdj* adj = fog->fog_adj;
        if (ref_DEC(adj)) {
            if (adj != NULL) {
                HSD_OBJECT_METHOD(adj)->release((HSD_Class*) adj);
                HSD_OBJECT_METHOD(adj)->destroy((HSD_Class*) adj);
            }
        }
    }
    HSD_AObjRemove(fog->aobj);
    HSD_OBJECT_PARENT_INFO(&hsdFog)->release((HSD_Class*) fog);
}

static void FogInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdFog), &hsdObj,
                     "sysdolphin_base_library", "hsd_fog", sizeof(HSD_FogInfo),
                     sizeof(HSD_Fog));
    HSD_CLASS_INFO(&hsdFog)->release = (void*) FogRelease;
}

static void FogAdjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdFogAdj), &hsdObj,
                     "sysdolphin_base_library", "hsd_fogadj",
                     sizeof(HSD_FogAdjInfo), sizeof(HSD_FogAdj));
}
