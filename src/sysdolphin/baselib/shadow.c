/**
 * @file shadow.c
 * @brief Circular shadow rendering system
 * @details Handles the projection of circular shadows beneath characters and items onto the ground.
 */

#include "shadow.h"

#include <math.h>
#include <string.h>

#include "class.h"
#include "cobj.h"
#include "debug.h"
#include "jobj.h"
#include "list.h"
#include "memory.h"
#include "mobj.h"
#include "mtx.h"
#include "object.h"
#include "perf.h"
#include "pobj.h"
#include "state.h"
#include "tev.h"
#include "tobj.h"
#include "util.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

HSD_ObjAllocData shadow_alloc_data;

/**
 * @brief Generates the projection matrix mapping the shadow texture onto the surface
 * @param shadow The shadow instance
 */
static void makeMatrix(HSD_Shadow* shadow);

/**
 * @brief Retrieves the shadow allocation data object
 * @return Pointer to the shadow HSD_ObjAllocData
 */
HSD_ObjAllocData* HSD_ShadowGetAllocData(void)
{
    return &shadow_alloc_data;
}

/**
 * @brief Initializes the shadow memory allocator
 */
void HSD_ShadowInitAllocData(void)
{
    HSD_ObjAllocInit(HSD_ShadowGetAllocData(), sizeof(HSD_Shadow), 4);
}

/**
 * @brief Internal helper to allocate a generic texture object for shadows
 * @return A new HSD_TObj for the shadow
 */
HSD_TObj* makeShadowTObj(void)
{
    HSD_TObj* shadowTObj;
    shadowTObj = HSD_TObjAlloc();
    shadowTObj->src = 0;
    shadowTObj->wrap_s = 0;
    shadowTObj->wrap_t = 0;
    shadowTObj->flags = 0x540103;
    shadowTObj->imagedesc = HSD_ImageDescAlloc();
    return shadowTObj;
}

/**
 * @brief Allocates and initializes a new HSD_Shadow instance
 * @return A new shadow instance
 */
HSD_Shadow* HSD_ShadowAlloc(void)
{
    HSD_Shadow* shadow;

    shadow = HSD_ObjAlloc(HSD_ShadowGetAllocData());
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

    HSD_CObjSetViewportfx4(shadow->camera, 0.0f, 256.f, 0.0f, 256.f);
    HSD_CObjSetScissorx4(shadow->camera, 0, 256, 0, 256);

    return shadow;
}

/**
 * @brief Frees a shadow instance and cleans up its camera and textures
 * @param shadow The shadow instance
 */
void HSD_ShadowRemove(HSD_Shadow* shadow)
{
    HSD_CObj* camera;
    HSD_TObj* texture;

    if (shadow == NULL) {
        return;
    }
    if ((camera = shadow->camera) != NULL) {
        if (ref_DEC(camera)) {
            hsdDelete(camera);
        }
    }
    HSD_ShadowDeleteObject(shadow, 0);
    if (shadow->active) {
        HSD_MObjDeleteShadowTexture(shadow->texture);
    }
    if (shadow->texture->imagedesc->image_ptr != NULL) {
        HSD_Free(shadow->texture->imagedesc->image_ptr);
    }
    texture = shadow->texture;
    HSD_ImageDescFree(texture->imagedesc);
    HSD_TObjFree(texture);
    HSD_ObjFree(HSD_ShadowGetAllocData(), shadow);
}

/**
 * @brief Configures GX hardware copying state for the shadow texture
 * @param shadow The shadow instance
 */
void HSD_ShadowInit(HSD_Shadow* shadow)
{
    HSD_ImageDesc* image_desc;

    HSD_ASSERT(245, shadow);
    image_desc = shadow->texture->imagedesc;
    GXSetTexCopySrc(0, 0, image_desc->width, image_desc->height);
    GXSetTexCopyDst(image_desc->width, image_desc->height, 0x20, 0);
}

/**
 * @brief Updates the shadow texture resolution
 * @param shadow The shadow instance
 * @param width New width
 * @param height New height
 */
void HSD_ShadowSetSize(HSD_Shadow* shadow, u16 width, u16 height)
{
    u32 size;
    HSD_ImageDesc* image_desc;

    HSD_ASSERT(277, shadow);
    HSD_ASSERT(278, width > 0);
    HSD_ASSERT(279, height > 0);

    image_desc = shadow->texture->imagedesc;
    if (!image_desc->image_ptr || image_desc->width != width || image_desc->height != height)
    {
        if (image_desc->image_ptr) {
            HSD_Free(image_desc->image_ptr);
        }

        size = GXGetTexBufferSize(width, height, GX_TF_I4, GX_FALSE, 0);
        HSD_ASSERT(0x122, size > 0);
        image_desc->image_ptr = HSD_MemAlloc(size);
        image_desc->width = width;
        image_desc->height = height;

        HSD_CObjSetViewportfx4(shadow->camera, 0, width, 0, height);
        HSD_CObjSetScissorx4(shadow->camera, 0, width, 0, height);
    }
}

/**
 * @brief Draws a background quad to act as a backstop/clear color for the shadow pass
 * @param shadow The shadow instance
 */
static void drawBackgroundRect(HSD_Shadow* shadow)
{
    f32 top, bottom, left, right, near;
    HSD_CObj* camera = shadow->camera;

    GXLoadPosMtxImm(HSD_identityMtx, GX_PNMTX0);
    HSD_PerfCountMtxLoad();
    GXSetCurrentMtx(GX_PNMTX0);
    HSD_ClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    HSD_StateSetCullMode(GX_CULL_BACK);

    top = HSD_CObjGetTop(camera);
    bottom = HSD_CObjGetBottom(camera);
    left = HSD_CObjGetLeft(camera);
    right = HSD_CObjGetRight(camera);
    near = HSD_CObjGetNear(camera);

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

/**
 * @brief Begins the shadow rendering pass, configuring the TEV and rendering objects
 * @param shadow The shadow instance
 */
void HSD_ShadowStartRender(HSD_Shadow* shadow)
{
    HSD_CObj* camera;
    HSD_ImageDesc* image_desc;
    HSD_SList* current_node;

    HSD_ASSERT(359, shadow);
    HSD_ASSERT(360, shadow->camera);
    HSD_ASSERT(361, shadow->texture);
    HSD_ASSERT(362, shadow->texture->imagedesc);

    current_node = shadow->objects;
    camera = shadow->camera;
    image_desc = shadow->texture->imagedesc;

    if (current_node != NULL) {
        HSD_CObjSetCurrent(camera);
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
                9, // ENABLE_COLOR_UPDATE | BEFORE_TEX,
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
            GXSetScissor(0, 0, image_desc->width, image_desc->height);

            drawBackgroundRect(shadow);

            chan.mat_color.r = shadow->intensity;
            chan.mat_color.g = shadow->intensity;
            chan.mat_color.b = shadow->intensity;

            HSD_SetupChannelAll(&chan);
            GXSetScissor(2, 2, image_desc->width - 4, image_desc->height - 4);
        }

        for (current_node = shadow->objects; current_node != NULL; current_node = current_node->next) {
            HSD_JObjDispAll(current_node->data, NULL,
                            (HSD_TrspMask) (HSD_TRSP_OPA | HSD_TRSP_TEXEDGE),
                            RENDER_SHADOW);
        }

        HSD_CObjEndCurrent();
    }
}

/**
 * @brief Ends the shadow rendering pass, syncing GX pixels and copying to the texture
 * @param shadow The shadow instance
 */
void HSD_ShadowEndRender(HSD_Shadow* shadow)
{
    HSD_ImageDesc* image_desc;

    HSD_ASSERT(501, shadow);

    image_desc = shadow->texture->imagedesc;
    if (!image_desc->image_ptr) {
        HSD_ShadowSetSize(shadow, image_desc->width, image_desc->height);
    }

    GXCopyTex(image_desc->image_ptr, GX_TRUE);
    GXPixModeSync();

    GXInvalidateTexAll();

    makeMatrix(shadow);
}

/**
 * @brief Toggles the active state of a shadow
 * @param shadow The shadow instance
 * @param active Non-zero to activate, zero to deactivate
 */
void HSD_ShadowSetActive(HSD_Shadow* shadow, int active)
{
    HSD_ImageDesc* image_desc;

    HSD_ASSERT(580, shadow);

    if ((shadow->active && active) || (!shadow->active && !active)) {
        return;
    }

    shadow->active = active;
    if (active) {
        image_desc = shadow->texture->imagedesc;
        if (!image_desc->image_ptr) {
            HSD_ShadowSetSize(shadow, image_desc->width, image_desc->height);
        }

        HSD_MObjAddShadowTexture(shadow->texture);
    } else {
        HSD_MObjDeleteShadowTexture(shadow->texture);
    }
}

static char distAssert[16] = "distance > 0.0F";

/**
 * @brief Adds a JObj (joint object) to the list of objects receiving this shadow
 * @param shadow The shadow instance
 * @param jobj The JObj to cast the shadow on
 */
void HSD_ShadowAddObject(HSD_Shadow* shadow, HSD_JObj* jobj)
{
    HSD_SList* current_node;

    if (!shadow || !jobj) {
        return;
    }

    for (current_node = shadow->objects; current_node; current_node = current_node->next) {
        if (current_node->data == jobj) {
            return;
        }
    }
    shadow->objects = HSD_SListAllocAndPrepend(shadow->objects, jobj);
    HSD_JObjRef(jobj);
}

/**
 * @brief Removes a JObj from the list of objects receiving this shadow
 * @param shadow The shadow instance
 * @param jobj The JObj to remove, or NULL to clear all
 */
void HSD_ShadowDeleteObject(HSD_Shadow* shadow, HSD_JObj* jobj)
{
    if (!shadow) {
        return;
    }

    if (jobj) {
        HSD_SList** current_node = &(shadow->objects);
        for (; *current_node; current_node = &((*current_node)->next)) {
            if ((*current_node)->data == jobj) {
                HSD_JObjUnref(jobj);
                (*current_node) = HSD_SListRemove(*current_node);
                return;
            }
        }
    } else {
        while (shadow->objects) {
            HSD_JObjUnref(shadow->objects->data);
            shadow->objects = HSD_SListRemove(shadow->objects);
        }
    }
}

/**
 * @brief Generates the projection matrix mapping the shadow texture onto the surface
 * @param shadow The shadow instance
 */
static void makeMatrix(HSD_Shadow* shadow)
{
    Mtx Mprj;

    switch (HSD_CObjGetProjectionType(shadow->camera)) {
    case PROJ_PERSPECTIVE:
        MTXLightPerspective(
            Mprj, shadow->camera->projection_param.perspective.fov,
            shadow->camera->projection_param.perspective.aspect,
            shadow->scaleS, shadow->scaleT, shadow->transS, shadow->transT);
        break;

    case PROJ_FRUSTUM:
        MTXLightFrustum(Mprj, shadow->camera->projection_param.frustum.top,
                        shadow->camera->projection_param.frustum.bottom,
                        shadow->camera->projection_param.frustum.left,
                        shadow->camera->projection_param.frustum.right,
                        shadow->camera->near, shadow->scaleS, shadow->scaleT,
                        shadow->transS, shadow->transT);
        break;

    case PROJ_ORTHO:
        MTXLightOrtho(Mprj, shadow->camera->projection_param.ortho.top,
                      shadow->camera->projection_param.ortho.bottom,
                      shadow->camera->projection_param.ortho.left,
                      shadow->camera->projection_param.ortho.right,
                      shadow->scaleS, shadow->scaleT, shadow->transS,
                      shadow->transT);
        break;

    default:
        HSD_ASSERT(698, 0);
    }

    MTXConcat(Mprj, HSD_CObjGetViewingMtxPtrDirect(shadow->camera),
              shadow->texture->mtx);
}

#define HSD_ASSERT2(line, text, cond)                                         \
    ((cond) ? ((void) 0) : __assert(__FILE__, line, text))

/**
 * @brief Adjusts the shadow camera viewing volume (frustum/ortho/perspective)
 * @param shadow The shadow instance
 * @param top Top bound
 * @param bottom Bottom bound
 * @param left Left bound
 * @param right Right bound
 */
void HSD_ShadowSetViewingRect(HSD_Shadow* shadow, float top, float bottom,
                              float left, float right)
{
    HSD_CObj* camera;
    float distance;

    HSD_ASSERT(721, shadow);

    camera = shadow->camera;
    distance = HSD_CObjGetEyeDistance(camera);
    HSD_ASSERT2(725, distAssert, distance > 0.0F);

    switch (HSD_CObjGetProjectionType(camera)) {
    case PROJ_PERSPECTIVE: {
        float width, height;

        if (fabsf_bitwise(top) > fabsf_bitwise(bottom)) {
            width = fabsf_bitwise(top);
        } else {
            width = fabsf_bitwise(bottom);
        }
        if (fabsf_bitwise(left) > fabsf_bitwise(right)) {
            height = fabsf_bitwise(left);
        } else {
            height = fabsf_bitwise(right);
        }
        HSD_CObjSetAspect(camera, height / width);
        HSD_CObjSetFov(camera, atan2f(height, distance));
    } break;

    case PROJ_ORTHO:
        HSD_CObjSetOrtho(camera, top, bottom, left, right);
        break;

    case PROJ_FRUSTUM: {
        float scale = HSD_CObjGetNear(camera) / distance;
        HSD_ASSERT(754, scale > 0.0F);
        HSD_CObjSetFrustum(camera, scale * top, scale * bottom, scale * left,
                           scale * right);
    } break;

    default:
        HSD_ASSERT(762, 0);
    }
}

/**
 * @brief Initializes a viewing rect structure based on camera properties
 * @param rect Pointer to the viewing rect to initialize
 * @param position Camera position
 * @param interest Camera interest/look-at point
 * @param upvector Camera up vector
 * @param perspective Perspective mode indicator
 */
void HSD_ViewingRectInit(HSD_ViewingRect* rect, Vec3* position, Vec3* interest,
                         Vec3* upvector, int perspective)
{
    Vec3 v;
    HSD_ASSERT(795, rect);

    rect->origin = *position;
    VECSubtract(interest, position, &rect->eye_v);
    VECNormalize(&rect->eye_v, &rect->eye_vn);
    VECNormalize(upvector, &v);
    VECCrossProduct(&rect->eye_vn, &v, &rect->right_v);
    VECCrossProduct(&rect->right_v, &rect->eye_vn, &rect->up_v);
    rect->distance = VECMag(&rect->eye_v);

    rect->top = rect->right = -F32_MAX;
    rect->bottom = rect->left = F32_MAX;
    rect->perspective = perspective;
}

/**
 * @brief Checks if a viewing rect is valid (top > bottom and right > left)
 * @param rect Pointer to the viewing rect
 * @return Non-zero if valid, zero if invalid
 */
int HSD_ViewingRectCheck(HSD_ViewingRect* rect)
{
    HSD_ASSERT(818, rect);
    return rect->top > rect->bottom && rect->right > rect->left;
}

/**
 * @brief Expands the viewing rect boundaries to encompass the provided rectangle
 * @param rect Pointer to the viewing rect
 * @param position Local origin of the sub-rect
 * @param top Local top
 * @param bottom Local bottom
 * @param left Local left
 * @param right Local right
 */
void HSD_ViewingRectAddRect(HSD_ViewingRect* rect, Vec3* position, float top,
                            float bottom, float left, float right)
{
    float x, y, dot, scale;
    Vec3 o2p, e2p;

    HSD_ASSERT(855, rect);
    HSD_ASSERT(856, position);

    VECSubtract(position, &rect->origin, &o2p);
    dot = VECDotProduct(&o2p, &rect->eye_vn);
    if (rect->perspective) {
        if (dot <= 0.0F) {
            return;
        }
        scale = rect->distance / dot;
        VECScale(&o2p, &o2p, scale);
        VECSubtract(&o2p, &rect->eye_v, &e2p);
        x = VECDotProduct(&rect->right_v, &e2p);
        y = VECDotProduct(&rect->up_v, &e2p);

        top *= scale;
        bottom *= scale;
        left *= scale;
        right *= scale;
    } else {
        Vec3 tmp;
        VECScale(&rect->eye_vn, &tmp, dot);
        VECSubtract(&o2p, &tmp, &e2p);
        x = VECDotProduct(&rect->right_v, &e2p);
        y = VECDotProduct(&rect->up_v, &e2p);
    }

    if (x + right > rect->right) {
        rect->right = x + right;
    }
    if (x + left < rect->left) {
        rect->left = x + left;
    }
    if (y + top > rect->top) {
        rect->top = y + top;
    }
    if (y + bottom < rect->bottom) {
        rect->bottom = y + bottom;
    }
}

static char radiusAssert[14] = "radius > 0.0F";
static char aAssert[9] = "a > 0.0F";
