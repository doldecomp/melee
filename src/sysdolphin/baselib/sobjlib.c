#include "sobjlib.h"

#include "cobj.h"
#include "gobj.h"
#include "gobjgxlink.h"
#include "gobjobject.h"
#include "objalloc.h"
#include "state.h"
#include "tev.h"

#include "dolphin/gx.h"

#include <dolphin/os.h>

/* 004DB670 */ extern const s32 HSD_SObjLib_804DEA90;
/* 004DB66C */ extern const s32 HSD_SObjLib_804DEA8C;
/* 004DB668 */ extern const s32 HSD_SObjLib_804DEA88;
/* 004DB664 */ extern const s32 HSD_SObjLib_804DEA84;
/* 004DB660 */ extern const s32 HSD_SObjLib_804DEA80;
/* 004D4540 */ extern u8 HSD_SObjLib_804D7960;
/* 004CDCC0 */ extern HSD_ObjAllocData HSD_SObjLib_804D10E0;
/* 00408F90 */ extern s8 HSD_SObjLib_8040C3B0[10];
typedef struct SObjLibData {
    /* 0x00 */ UNK_T x0;
    /* 0x04 */ GObjFuncs x4_funcs;
    /* 0x10 */ s8 x10_filename[10];
    /* 0x1A */ u8 pad1A[2];
    /* 0x1C */ char x1C_errmsg[32];
    /* 0x3C */ void* x3C_jumptable[15];
    /* 0x78 */ HSD_Chan x78_chan0;
    /* 0xA8 */ HSD_Chan xA8_chan1;
    /* 0xD8 */ char xD8_errmsg2[24];
} SObjLibData;

extern SObjLibData HSD_SObjLib_8040C3A0;
/* 003B6244 */ extern Vec3 HSD_SObjLib_803B9664;
/* 003B6238 */ extern Vec3 HSD_SObjLib_803B9658;
/* 00408F9C */ extern char HSD_SObjLib_8040C3BC[];

HSD_ObjAllocData HSD_SObjLib_804D10E0;

void HSD_SObjLib_803A44A4(void)
{
    HSD_ObjAllocInit(&HSD_SObjLib_804D10E0, 0x9C, 4);
}

/* @@todo: 99.56% match - needs register allocation fix (r4 vs r5 for cur) */
/* @@todo: 99.56% match - needs register allocation fix (r4 vs r5 for cur) */
void HSD_SObjLib_803A44D4(HSD_GObj* gobj, HSD_SObj* sobj, u8 priority)
{
    HSD_SObj* cur;
    HSD_SObj* next;

    PAD_STACK(16);

    cur = sobj->prev;
    if (cur != NULL || sobj->next != NULL) {
        if (cur != NULL) {
            cur->next = sobj->next;
        } else {
            HSD_GObjObject_80390ADC(gobj);
            HSD_GObjObject_80390A70(gobj, HSD_SObjLib_804D7960, sobj->next);
            sobj->next->prev = NULL;
        }

        if (sobj->next != NULL) {
            sobj->next->prev = sobj->prev;
        } else {
            sobj->prev->next = NULL;
        }

        sobj->next = NULL;
        sobj->prev = NULL;
    } else {
        if (gobj->hsd_obj == sobj) {
            HSD_GObjObject_80390ADC(gobj);
        }
    }

    cur = gobj->hsd_obj;
    if (cur == NULL) {
        HSD_GObjObject_80390ADC(gobj);
        HSD_GObjObject_80390A70(gobj, HSD_SObjLib_804D7960, sobj);
    } else {
        next = cur;
        while (next->next != NULL && next->x44 <= (u8) priority) {
            next = next->next;
        }

        if (next->next == NULL && next->x44 <= (u8) priority) {
            next->next = sobj;
            sobj->prev = next;
        } else if (next == cur) {
            sobj->next = cur;
            ((HSD_SObj*) gobj->hsd_obj)->prev = sobj;
            HSD_GObjObject_80390ADC(gobj);
            HSD_GObjObject_80390A70(gobj, HSD_SObjLib_804D7960, sobj);
        } else {
            next->prev->next = sobj;
            sobj->prev = next->prev;
            next->prev = sobj;
            sobj->next = next;
        }
    }

    sobj->x44 = priority;
}

void HSD_SObjLib_803A466C(HSD_SObj* sobj)
{
    PAD_STACK(8);

    if (sobj == NULL) {
        return;
    }

    if (sobj->prev != NULL || sobj->next != NULL) {
        if (sobj->prev != NULL) {
            sobj->prev->next = sobj->next;
        } else {
            HSD_GObjObject_80390ADC(sobj->gobj);
            HSD_GObjObject_80390A70(sobj->gobj, HSD_SObjLib_804D7960,
                                    sobj->next);
            sobj->next->prev = NULL;
        }

        if (sobj->next != NULL) {
            sobj->next->prev = sobj->prev;
        } else {
            sobj->prev->next = NULL;
        }

        sobj->next = NULL;
        sobj->prev = NULL;
    } else {
        if (sobj->gobj->hsd_obj == sobj) {
            HSD_GObjObject_80390ADC(sobj->gobj);
        }
    }

    HSD_ObjFree(&HSD_SObjLib_804D10E0, sobj);
}

void HSD_SObjLib_803A4740(HSD_SObj* sobj)
{
    HSD_SObj* next;

    while (sobj != NULL) {
        next = sobj->next;
        HSD_SObjLib_803A466C(sobj);
        sobj = next;
    }
}

/// #HSD_SObjLib_803A477C

void HSD_SObjLib_803A49E0(HSD_GObj* gobj, int unused)
{
    HSD_SObj* sobj;

    PAD_STACK(8);

    sobj = gobj->hsd_obj;
    while (sobj != NULL) {
        if (HSD_SObjLib_804D7960 != gobj->obj_kind) {
            OSReport(HSD_SObjLib_8040C3BC);
            return;
        }
        if (sobj->x4C_callback != NULL) {
            sobj->x4C_callback(sobj);
        }
        HSD_SObjLib_803A4A68(sobj);
        sobj = sobj->next;
    }
}

/// #HSD_SObjLib_803A4A68

void HSD_SObjLib_803A54EC(HSD_GObj* gobj, int unused)
{
    Mtx viewmtx;
    SObjLibData* data = &HSD_SObjLib_8040C3A0;

    if (HSD_CObjSetCurrent(gobj->hsd_obj)) {
        GXSetCurrentMtx(0);
        HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), viewmtx);
        GXLoadPosMtxImm(viewmtx, 0);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0,
                          GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0,
                          GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        HSD_SetupChannel(&data->x78_chan0);
        HSD_SetupChannel(&data->xA8_chan1);
        HSD_StateSetNumChans(1);
        HSD_GObj_80390ED0(gobj, 1);
        HSD_CObjEndCurrent();
    } else {
        OSReport(data->xD8_errmsg2);
    }
    HSD_StateInvalidate(-1);
    HSD_StateSetZMode(1, 3, 1);
}

/* @@todo: 99.84% match - near_val variable forces 6 FPR saves but adds
 * 4 bytes to stack, shifting local offsets by 4 */
void HSD_SObjLib_803A55DC(HSD_GObj* gobj, int width, int height, int priority)
{
    HSD_CObj* cobj;
    Vec3 eye = HSD_SObjLib_803B9658;
    Vec3 interest = HSD_SObjLib_803B9664;
    Scissor viewport;
    Scissor scissor;
    f32 roll = 0.0F;
    f32 near_val = roll;
    f32 far_val = 0.5F;
    f32 top = roll;
    f32 bottom = (f32) -(s32)(u16) height;
    f32 left = roll;
    f32 right = (f32)(u16) width;

    viewport.left = 0;
    viewport.right = width;
    viewport.top = 0;
    viewport.bottom = height;

    scissor.left = 0;
    scissor.right = width;
    scissor.top = 0;
    scissor.bottom = height;

    cobj = HSD_CObjAlloc();
    HSD_CObjSetProjectionType(cobj, PROJ_ORTHO);
    HSD_CObjSetViewport(cobj, (HSD_RectS16*) &viewport);
    HSD_CObjSetScissor(cobj, &scissor);
    HSD_CObjSetEyePosition(cobj, &eye);
    HSD_CObjSetInterest(cobj, &interest);
    HSD_CObjSetRoll(cobj, roll);
    HSD_CObjSetNear(cobj, near_val);
    HSD_CObjSetFar(cobj, far_val);
    HSD_CObjSetOrtho(cobj, top, bottom, left, right);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, HSD_SObjLib_803A54EC, priority);
}
