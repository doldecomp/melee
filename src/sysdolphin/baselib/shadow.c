#include <sysdolphin/baselib/shadow.h>

#include <string.h>

extern HSD_ObjAllocData shadow_alloc_data;

extern const f32 lbl_804DE768;
extern const f32 lbl_804DE76C;
extern const f32 lbl_804DE770;
extern const f32 lbl_804DE774;

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

    hack = lbl_804DE770;
    HSD_CObjSetViewportfx4(shadow->camera, hack, lbl_804DE774, hack,
                           lbl_804DE774); // 0f, 256f, 0f, 256f
    HSD_CObjSetScissorx4(shadow->camera, 0, 256, 0, 256);

    return shadow;
}

inline BOOL dec_refcount(u16* ref_count)
{
    u16 current = *ref_count;
    s32 cond = current == (u16) HSD_OBJ_NOREF;
    if (cond != FALSE) {
        return cond;
    }
    *ref_count = current - 1;
    return current == 0;
}

void HSD_ShadowRemove(HSD_Shadow* shadow)
{
    HSD_CObj* cobj;
    HSD_TObj* tobj;

    if (shadow == NULL) {
        return;
    }
    if ((cobj = shadow->camera) != NULL) {
        u16* ref_count = &cobj->parent.ref_count;
        if (dec_refcount(ref_count) && cobj != NULL) {
            cobj->parent.parent.class_info->release(&cobj->parent.parent);
            cobj->parent.parent.class_info->destroy(&cobj->parent.parent);
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

extern char lbl_80407310[9];
extern char lbl_804D5F78[7];

void HSD_ShadowInit(HSD_Shadow* shadow)
{
    HSD_ImageDesc* imagedesc;

    if (shadow == NULL) {
        __assert(lbl_80407310, 0xF5, lbl_804D5F78);
    }
    imagedesc = shadow->texture->imagedesc;
    GXSetTexCopySrc(0, 0, imagedesc->width, imagedesc->height);
    GXSetTexCopyDst(imagedesc->width, imagedesc->height, 0x20, 0);
}
