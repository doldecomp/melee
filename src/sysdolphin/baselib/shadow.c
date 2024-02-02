#include "shadow.h"

#include "class.h"
#include "cobj.h"
#include "debug.h"
#include "jobj.h"
#include "memory.h"
#include "mobj.h"
#include "object.h"
#include "perf.h"
#include "pobj.h"
#include "state.h"
#include "tobj.h"
#include "util.h"

#include <__mem.h>
#include <dolphin/gx/GXAttr.h>
#include <dolphin/gx/GXFrameBuf.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXVert.h>

extern HSD_ObjAllocData shadow_alloc_data;

extern const f32 lbl_804DE768;
extern const f32 lbl_804DE76C;
extern const f32 HSD_Shadow_804DE770;
extern const f32 HSD_Shadow_804DE774;

HSD_ObjAllocData* HSD_ShadowGetAllocData(void)
{
    return &shadow_alloc_data;
}

void HSD_ShadowInitAllocData(void)
{
    HSD_ObjAllocInit(&shadow_alloc_data, sizeof(HSD_Shadow), 4);
}

HSD_TObj* makeShadowTObj(void)
{
    HSD_TObj* shadowTObj;
    shadowTObj = allocShadowTObj();
    shadowTObj->src = 0;
    shadowTObj->wrap_s = 0;
    shadowTObj->wrap_t = 0;
    shadowTObj->flags = 0x540103;
    shadowTObj->imagedesc = HSD_ImageDescAlloc();
    return shadowTObj;
}

HSD_Shadow* HSD_ShadowAlloc(void)
{
    HSD_Shadow* shadow;
    f32 hack; // TODO: remove once the whole file is converted and we can use
              // float constants

    shadow = HSD_ObjAlloc(&shadow_alloc_data);
    memset(shadow, 0, sizeof(HSD_Shadow));
    shadow->camera = HSD_CObjAlloc();
    shadow->texture = makeShadowTObj();

    shadow->scaleS = 0.5F;
    shadow->scaleT = -0.5F;
    shadow->transS = 0.5F;
    shadow->transT = 0.5F;
    shadow->intensity = 0;

    shadow->texture->imagedesc->format = 0;
    shadow->texture->imagedesc->width = 256;
    shadow->texture->imagedesc->height = 256;

    hack = HSD_Shadow_804DE770;
    HSD_CObjSetViewportfx4(shadow->camera, hack, HSD_Shadow_804DE774, hack,
                           HSD_Shadow_804DE774); // 0f, 256f, 0f, 256f
    HSD_CObjSetScissorx4(shadow->camera, 0, 256, 0, 256);

    return shadow;
}

void HSD_ShadowRemove(HSD_Shadow* shadow)
{
    HSD_CObj* cobj;
    HSD_TObj* tobj;

    if (shadow == NULL) {
        return;
    }
    if ((cobj = shadow->camera) != NULL) {
        if (ref_DEC(cobj)) {
            hsdDelete(cobj);
        }
    }
    HSD_ShadowDeleteObject(shadow, 0);
    if (shadow->active) {
        HSD_MObjDeleteShadowTexture(shadow->texture);
    }
    if (shadow->texture->imagedesc->img_ptr != NULL) {
        HSD_Free(shadow->texture->imagedesc->img_ptr);
    }
    tobj = shadow->texture;
    HSD_ImageDescFree(tobj->imagedesc);
    HSD_TObjFree(tobj);
    HSD_ObjFree(&shadow_alloc_data, shadow);
}

extern char HSD_Shadow_80407310[9];
extern char HSD_Shadow_804D5F78[7];

void HSD_ShadowInit(HSD_Shadow* shadow)
{
    HSD_ImageDesc* imagedesc;

    if (shadow == NULL) {
        __assert(HSD_Shadow_80407310, 0xF5, HSD_Shadow_804D5F78);
    }
    imagedesc = shadow->texture->imagedesc;
    GXSetTexCopySrc(0, 0, imagedesc->width, imagedesc->height);
    GXSetTexCopyDst(imagedesc->width, imagedesc->height, 0x20, 0);
}

void HSD_ShadowSetSize(HSD_Shadow* shadow, u16 width, u16 height)
{
    u32 size;
    HSD_ImageDesc* idesc;

    HSD_ASSERT(0x115, shadow);
    HSD_ASSERT(0x116, width > 0);
    HSD_ASSERT(0x117, height > 0);

    idesc = shadow->texture->imagedesc;
    if (!idesc->img_ptr || idesc->width != width || idesc->height != height) {
        if (idesc->img_ptr) {
            HSD_Free(idesc->img_ptr);
        }

        size = GXGetTexBufferSize(width, height, GX_TF_I4, GX_FALSE, 0);
        HSD_ASSERT(0x122, size > 0);
        idesc->img_ptr = HSD_MemAlloc(size);
        idesc->width = width;
        idesc->height = height;

        HSD_CObjSetViewportfx4(shadow->camera, 0, width, 0, height);
        HSD_CObjSetScissorx4(shadow->camera, 0, width, 0, height);
    }
}

static void drawBackgroundRect(HSD_Shadow* shadow)
{
    f32 top, bottom, left, right, near;
    HSD_CObj* cobj = shadow->camera;

    GXLoadPosMtxImm(HSD_identityMtx, GX_PNMTX0);
    HSD_PerfCountMtxLoad();
    GXSetCurrentMtx(GX_PNMTX0);
    HSD_ClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    HSD_StateSetCullMode(GX_CULL_BACK);

    top = HSD_CObjGetTop(cobj);
    bottom = HSD_CObjGetBottom(cobj);
    left = HSD_CObjGetLeft(cobj);
    right = HSD_CObjGetRight(cobj);
    near = HSD_CObjGetNear(cobj);

    top *= 1.20000004768f;
    bottom *= 1.20000004768f;
    left *= 1.20000004768f;
    right *= 1.20000004768f;
    near *= -1.10000002384f;

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition2f32(left, top);
    GXPosition2f32(near, right);
    GXPosition2f32(top, near);
    GXPosition2f32(right, bottom);
    GXPosition2f32(near, left);
    GXPosition2f32(bottom, near);
    GXEnd();
}

void HSD_ShadowStartRender(HSD_Shadow* shadow)
{
    HSD_CObj* cobj;
    HSD_ImageDesc* idesc;
    HSD_SList* list;

    HSD_ASSERT(0x167, shadow);
    HSD_ASSERT(0x168, shadow->camera);
    HSD_ASSERT(0x169, shadow->texture);
    HSD_ASSERT(0x16A, shadow->texture->imagedesc);

    list = shadow->objects;
    cobj = shadow->camera;
    idesc = shadow->texture->imagedesc;

    if (list != NULL) {
        HSD_CObjSetCurrent(cobj);
        {
            static HSD_Chan chan = {
                NULL,           GX_COLOR0A0,      0,
                { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, GX_FALSE,
                GX_SRC_REG,     GX_SRC_REG,       GX_LIGHT_NULL,
                GX_DF_CLAMP,    GX_AF_NONE,       NULL,
            };
            static HSD_TevDesc tev = {
                NULL,
                TEVCONF_MODE,
                GX_TEVSTAGE0,
                GX_TEXCOORD_NULL,
                GX_TEXMAP_NULL,
                GX_COLOR0A0,
                {
                    GX_TEV_ADD, GX_CC_ZERO,    GX_CC_ZERO,    GX_CC_ZERO,
                    GX_CC_RASC, GX_CS_SCALE_1, GX_TB_ZERO,    GX_TRUE,
                    GX_TEVPREV, GX_TEV_ADD,    GX_CA_ZERO,    GX_CA_ZERO,
                    GX_CA_ZERO, GX_CA_RASA,    GX_CS_SCALE_1, GX_TB_ZERO,
                    GX_TRUE,    GX_TEVPREV,    GX_TC_LINEAR,
                }
            };
            static HSD_PEDesc pedesc = {
                1 << 0 | 1 << 1, // ENABLE_COLOR_UPDATE | BEFORE_TEX,
                0,
                0,
                0,
                GX_BM_NONE,
                GX_BL_SRCALPHA,
                GX_BL_INVSRCALPHA,
                GX_LO_SET,
                GX_ALWAYS,
                GX_ALWAYS,
                GX_AOP_AND,
                GX_ALWAYS
            };

            HSD_StateInitTev();
            HSD_SetupTevStageAll(&tev);

            HSD_StateSetNumTexGens();

            HSD_SetupPEMode(0, &pedesc);

            chan.mat_color.r = 255;
            chan.mat_color.g = 255;
            chan.mat_color.b = 255;

            HSD_SetupChannelAll(&chan);
            GXSetScissor(0, 0, idesc->width, idesc->height);

            drawBackgroundRect(shadow);

            chan.mat_color.r = shadow->intensity;
            chan.mat_color.g = shadow->intensity;
            chan.mat_color.b = shadow->intensity;

            HSD_SetupChannelAll(&chan);
            GXSetScissor(2, 2, idesc->width - 4, idesc->height - 4);
        }

        for (list = shadow->objects; list != NULL; list = list->next) {
            HSD_JObjDispAll(list->data, NULL,
                            (HSD_TrspMask) (HSD_TRSP_OPA | HSD_TRSP_TEXEDGE),
                            RENDER_SHADOW);
        }

        HSD_CObjEndCurrent();
    }
}
