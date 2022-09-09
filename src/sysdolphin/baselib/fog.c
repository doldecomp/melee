#include <sysdolphin/baselib/fog.h>

#include <dolphin/gx/GX_unknown_001.h>
#include <sysdolphin/baselib/cobj.h>

static void FogInfoInit(void);
static void FogAdjInfoInit(void);
HSD_FogInfo hsdFog = { FogInfoInit };
HSD_ClassInfo hsdFogAdj = { FogAdjInfoInit };

typedef struct _GXFogAdjTbl {
	u16 r[10];
} GXFogAdjTbl;

const GXColor lbl_804DE6F0 = { 0 };

void HSD_FogSet(HSD_Fog* fog)
{
    GXFogAdjTbl sp88;
    f32 sp70[6];
    HSD_CObj* cobj;
    s32 var_r31;
    struct {
        f32 x0;
        f32 arr[6];
    } sp54;

    if (fog == NULL) {
        GXSetFog(0, lbl_804DE6F0, 0.0F, 0.0F, 0.0F, 0.0F);
        return;
    }
    cobj = HSD_CObjGetCurrent();
    if (cobj == NULL) {
        HSD_Panic(__FILE__, 0x4D, "You must specify CObj first.\n");
    }
    GXSetFog(fog->type, fog->color, fog->start, fog->end,
        HSD_CObjGetNear(cobj), HSD_CObjGetFar(cobj));

    if (fog->fog_adj != NULL) {
        GXGetViewportv(sp70);
        var_r31 = sp70[0] + sp70[2] * (fog->fog_adj->center + 320) / 640.0F;
        if (var_r31 < 0) {
            var_r31 = 0;
        }
        if (var_r31 > 640) {
            var_r31 = 640;
        }
        if (fog->fog_adj->width != 0) {
            GXInitFogAdjTable(&sp88, fog->fog_adj->width, fog->fog_adj->mtx);
        } else {
            Mtx44 sp14 = { 0 };
            GXGetProjectionv(&sp54);
            switch ((s32) sp54.x0) {
            case 0:
                sp14[0][0] = sp54.arr[0];
                sp14[0][2] = sp54.arr[1];
                sp14[1][1] = sp54.arr[2];
                sp14[1][2] = sp54.arr[3];
                sp14[2][2] = sp54.arr[4];
                sp14[2][3] = sp54.arr[5];
                sp14[3][2] = -1.0F;
                break;
            case 1:
                sp14[0][0] = sp54.arr[0];
                sp14[0][3] = sp54.arr[1];
                sp14[1][1] = sp54.arr[2];
                sp14[1][3] = sp54.arr[3];
                sp14[2][2] = sp54.arr[4];
                sp14[2][3] = sp54.arr[5];
                sp14[3][3] = 1.0F;
                break;
            }
            GXInitFogAdjTable(&sp88, sp70[2], sp14);
        }
        GXSetFogRangeAdj(1, var_r31, &sp88);
        return;
    }
    GXSetFogRangeAdj(0, 0, NULL);
}

HSD_Fog* HSD_FogAlloc(void)
{
    HSD_Fog* fog = hsdNew((HSD_ClassInfo*) &hsdFog);
    assert_line(0x8C, fog);
    return fog;
}

HSD_Fog* HSD_FogLoadDesc(HSD_FogDesc* desc)
{
    HSD_Fog* fog = HSD_FogAlloc();
    assert_line(0x99, fog);
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
            f32 sp10[6];
            GXGetViewportv(sp10);
            fog->type = 2;
            fog->start = sp10[4];
            fog->end = sp10[5];
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
    adj ? (void) 0 : __assert("fog.c", 0xD6, "adj");
    return adj;
}

HSD_FogAdj* HSD_FogAdjLoadDesc(HSD_FogAdjDesc* desc)
{
    HSD_FogAdj* adj = HSD_FogAdjAlloc();
    adj ? (void) 0 : __assert("fog.c", 0xE6, "adj");
    HSD_FogAdjInit(adj, desc);
    return adj;
}

void HSD_FogAdjInit(HSD_FogAdj* adj, HSD_FogAdjDesc* desc)
{
    f32 sp10[6];

    if (adj != NULL) {
        if (desc != NULL) {
            adj->width = desc->width;
            adj->center = desc->center;
            PSMTXCopy(desc->mtx, adj->mtx);
        } else {
            GXGetViewportv(sp10);
            adj->width = sp10[2];
            adj->center = adj->width / 2;
            PSMTXIdentity(adj->mtx);
            adj->mtx[3][0] = 0.0F;
            adj->mtx[3][1] = 0.0F;
            adj->mtx[3][2] = 0.0F;
            adj->mtx[3][3] = 1.0F;
        }
    }
}

// HSD_FogAddAnim ?
void func_8037DE7C(HSD_Fog* fog, HSD_AObjDesc* desc)
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

void FogUpdateFunc(HSD_Fog* fog, u32 type, FObjData* fv)
{
    if (fog != NULL) {
        switch (type) {
        case 1:
            fog->start = fv->fv;
            return;
        case 2:
            fog->end = fv->fv;
            return;
        case 5:
            fog->color.r = 255.0F * fv->fv;
            return;
        case 6:
            fog->color.g = 255.0F * fv->fv;
            return;
        case 7:
            fog->color.b = 255.0F * fv->fv;
            return;
        case 8:
            fog->color.a = 255.0F * fv->fv;
            return;
        case 20:
            if (fog->fog_adj != NULL) {
                fog->fog_adj->center = fv->fv;
            }
            break;
        }
    }
}

inline BOOL ref_DEC(void* o)
{
    BOOL ret = (u64) (HSD_OBJ(o)->ref_count == (u16) -1);
    if (ret)
        return ret;
    return HSD_OBJ(o)->ref_count-- == 0;
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
        "sysdolphin_base_library", "hsd_fog",
        sizeof(HSD_FogInfo), sizeof(HSD_Fog));
    HSD_CLASS_INFO(&hsdFog)->release = (void*) FogRelease;
}

static void FogAdjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdFogAdj), &hsdObj,
        "sysdolphin_base_library", "hsd_fogadj",
        sizeof(HSD_FogAdjInfo), sizeof(HSD_FogAdj));
}
