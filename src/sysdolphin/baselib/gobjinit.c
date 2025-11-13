#include "gobj.h"
#include "gobjplink.h"
#include "gobjproc.h"
#include "memory.h"

static HSD_GObjLibInitDataType HSD_GObj_80408620 = {
    0x3F,
    0x3F,
    2,
};

void HSD_GObj_803912E0(HSD_GObjLibInitDataType* arg0)
{
    *arg0 = HSD_GObj_80408620;
}

extern HSD_ObjAllocData gobj_alloc_data;
extern HSD_ObjAllocData gobjproc_alloc_data;
extern struct _unk_gobj_struct HSD_GObj_804CE3E4;

void HSD_GObj_80391304(HSD_GObjLibInitDataType* arg0)
{
    GObjFuncs* cur;
    int i;
    int var_r8;
    int nfuncs;
    struct _GObjFuncs* var_r4_2;

    HSD_GObj_80391260(arg0);

    HSD_GObjLibInitData = *arg0;

    HSD_GObj_Entities =
        HSD_MemAlloc(sizeof(HSD_GObj*) * (arg0->p_link_max + 1));
    plinklow_gobjs = HSD_MemAlloc(sizeof(HSD_GObj*) * (arg0->p_link_max + 1));
    for (i = 0; i < arg0->p_link_max + 1; i++) {
        ((HSD_GObj**) HSD_GObj_Entities)[i] = plinklow_gobjs[i] = NULL;
    }

    HSD_GObj_804D7824 =
        HSD_MemAlloc(sizeof(HSD_GObj*) * (arg0->gx_link_max + 2));
    HSD_GObj_804D7820 =
        HSD_MemAlloc(sizeof(HSD_GObj*) * (arg0->gx_link_max + 2));

    for (i = 0; i < arg0->gx_link_max + 2; i++) {
        HSD_GObj_804D7824[i] = HSD_GObj_804D7820[i] = 0;
    }

    HSD_GObj_804D7840 =
        HSD_MemAlloc(sizeof(HSD_GObjProc*) * (arg0->gproc_pri_max + 1));

    for (i = 0; i < arg0->gproc_pri_max + 1; i++) {
        HSD_GObj_804D7840[i] = 0;
    }

    HSD_GObj_804D7844 =
        HSD_MemAlloc(sizeof(HSD_GObjProc*) * (arg0->gproc_pri_max + 1) *
                     (arg0->p_link_max + 1));

    for (i = 0; i < (arg0->gproc_pri_max + 1) * (arg0->p_link_max + 1); i++) {
        HSD_GObj_804D7844[i] = 0;
    }

    HSD_ObjAllocInit(&gobj_alloc_data, sizeof(HSD_GObj), 4);
    HSD_ObjAllocInit(&gobjproc_alloc_data, sizeof(HSD_GObjProc), 4);

    var_r4_2 = arg0->funcs;
    nfuncs = 0;
    while (var_r4_2 != NULL) {
        nfuncs += var_r4_2->size;
        var_r4_2 = var_r4_2->next;
    }

    if (nfuncs != 0) {
        var_r8 = (sizeof(GObjFunc)) * nfuncs;
        HSD_GObj_804D7810 = HSD_MemAlloc(var_r8);

        var_r8 = 0;
        for (cur = arg0->funcs; cur != NULL; cur = cur->next) {
            for (i = 0; i < cur->size; i++, var_r8++) {
                HSD_GObj_804D7810[var_r8] = cur->funcs[i];
            }
        }
    } else {
        HSD_GObj_804D7810 = NULL;
    }

    HSD_GObj_804D783C = 0;
    HSD_GObj_804D781C = NULL;
    HSD_GObj_804D7838 = NULL;
    HSD_GObj_804CE3E4.flags = 0;
    HSD_GObj_804D7818 = NULL;
    HSD_GObj_804D7814 = NULL;
}
