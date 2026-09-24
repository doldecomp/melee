#include "class.h"
#include "cobj.h"
#include "fog.h"
#include "gobj.h"
#include "jobj.h"
#include "lobj.h"
#include "object.h"

u8 HSD_GObj_CameraKind;
s8 HSD_GObj_LightKind;
u8 HSD_GObj_JObjKind;
s8 HSD_GObj_FogKind;

static GObjFunc HSD_GObj_80408600[] = {
    HSD_GObj_80391120,
    (GObjFunc) HSD_LObjRemoveAll,
    (GObjFunc) HSD_JObjRemoveAll,
    HSD_GObj_803911C0,
};

static GObjFuncs HSD_GObj_80408610 = {
    0,
    4,
    HSD_GObj_80408600,
};

void HSD_GObj_LObjCallback(HSD_GObj* gobj, intptr_t unused)
{
    HSD_LObj_803668EC(gobj->hsd_obj);
    HSD_LObjSetupInit(HSD_CObjGetCurrent());
}

void HSD_GObj_JObjCallback(HSD_GObj* gobj, intptr_t arg1)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    HSD_JObjDispAll(jobj, NULL, HSD_GObj_80390EB8(arg1), 0);
}

void HSD_GObj_FogCallback(HSD_GObj* gobj, intptr_t unused)
{
    HSD_FogSet(gobj->hsd_obj);
}

void HSD_GObj_803910D8(HSD_GObj* gobj, intptr_t renderpass)
{
    if (HSD_CObjSetCurrent(gobj->hsd_obj)) {
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

void HSD_GObj_80391120(HSD_Obj* obj)
{
    if (obj != NULL && ref_DEC(obj)) {
        hsdDelete(obj);
    }
}

void HSD_GObj_803911C0(HSD_Obj* obj)
{
    HSD_GObj_80391120(obj);
}

void HSD_GObj_80391260(HSD_GObjLibInitDataType* arg0)
{
    u8 count = HSD_GObj_803912A8(arg0, &HSD_GObj_80408610);
    HSD_GObj_CameraKind = count++;
    HSD_GObj_LightKind = count++;
    HSD_GObj_JObjKind = count++;
    HSD_GObj_FogKind = count;
}

u8 HSD_GObj_803912A8(HSD_GObjLibInitDataType* arg0, GObjFuncs* arg1)
{
    GObjFuncs* cur;
    GObjFuncs** pcur = &arg0->funcs;
    u8 var_r3 = 0;
    while ((cur = *pcur) != NULL) {
        pcur = &cur->next;
        var_r3 += cur->size;
    }
    *pcur = arg1;
    (*pcur)->next = NULL;
    return var_r3;
}
