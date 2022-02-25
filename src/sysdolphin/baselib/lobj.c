#include "sysdolphin/baselib/lobj.h"

void LObjInfoInit(void);

HSD_LObjInfo hsdLObj = { LObjInfoInit };

extern s32 lightmask_diffuse;
extern s32 lightmask_attnfunc;
extern s32 lightmask_alpha;
extern s32 lightmask_specular;

extern s32 nb_active_lights;

extern HSD_LObj* active_lights[MAX_GXLIGHT];

u32 HSD_LObjGetFlags(HSD_LObj* lobj)
{
    return (lobj) ? lobj->flags : 0;
}

void HSD_LObjSetFlags(HSD_LObj* lobj, u32 flags)
{
    if (lobj == NULL)
        return;
    lobj->flags |= flags;
}

void HSD_LObjClearFlags(HSD_LObj* lobj, u32 flags)
{
    if (lobj == NULL)
        return;
    lobj->flags &= ~flags;
}

s32 HSD_LObjGetLightMaskDiffuse(void)
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

s32 HSD_LObjGetNbActive(void)
{
    return nb_active_lights;
}

HSD_LObj* HSD_LObjGetActiveByID(GXLightID id)
{
    s32 idx = HSD_LightID2Index(id);
    if (0 <= idx && idx < MAX_GXLIGHT) {
        return active_lights[idx];
    } else {
        return NULL;
    }
}

HSD_LObj* HSD_LObjGetActiveByIndex(s32 idx)
{
    if (0 <= idx && idx < MAX_GXLIGHT - 1) {
        return active_lights[idx];
    } else {
        return NULL;
    }
}
