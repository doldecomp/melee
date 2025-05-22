#include "gobj.h"

#include "class.h"
#include "cobj.h"
#include "fog.h"
#include "gobjplink.h"
#include "gobjproc.h"
#include "jobj.h"
#include "lobj.h"
#include "object.h"

inline void GObj_SetFlag1_inline(HSD_GObjProc* proc, u8 value)
{
    while (proc != NULL) {
        proc->flags_1 = value;
        proc = proc->child;
    }
}

inline void GObj_SetFlag2_inline(HSD_GObjProc* proc, u8 value)
{
    while (proc != NULL) {
        proc->flags_2 = value;
        proc = proc->child;
    }
}

void HSD_GObj_80390C5C(HSD_GObj* gobj)
{
    GObj_SetFlag1_inline(gobj->proc, 1);
}

void HSD_GObj_80390C84(HSD_GObj* gobj)
{
    GObj_SetFlag1_inline(gobj->proc, 0);
}

void HSD_GObj_80390CAC(HSD_GObj* gobj)
{
    GObj_SetFlag2_inline(gobj->proc, 0);
}

void HSD_GObj_80390CD4(HSD_GObj* gobj)
{
    HSD_GObjProc* p = gobj->proc;

    while (p != NULL) {
        p->flags_3 = HSD_GObj_804D783C;
        p = p->child;
    }
}

// GObj_RunProcs
void HSD_GObj_80390CFC(void)
{
    s32 i;
    HSD_GObjProc* proc;
    HSD_GObj* gobj;

    u64 var_r31 =
        HSD_GObjLibInitData.unk_2 != NULL ? *HSD_GObjLibInitData.unk_2 : 0;
    HSD_GObj_804D783C += 1;
    if (HSD_GObj_804D783C > 2) {
        HSD_GObj_804D783C = 0;
    }

    for (i = 0; i <= HSD_GObjLibInitData.gproc_pri_max; i++) {
        HSD_GObj_804D7834 = i;
        proc = HSD_GObj_804D7840[i];
        while (proc != NULL) {
            HSD_GObj_804D7830 = proc->next;
            if (proc->flags_3 != HSD_GObj_804D783C) {
                proc->flags_3 = HSD_GObj_804D783C;
                gobj = proc->gobj;
                if (!(var_r31 & (1LL << gobj->p_link)) && !(proc->flags_1) &&
                    !(proc->flags_2))
                {
                    HSD_GObj_804D781C = gobj;
                    HSD_GObj_804D7838 = proc;
                    proc->on_invoke(proc->gobj);
                    HSD_GObj_804D7830 = proc->next;
                    if (HSD_GObj_804CE3E4.flags != 0) {
                        HSD_GObj_804CE3E4.b0 = 1;
                        if (HSD_GObj_804CE3E4.b1) {
                            HSD_GObjPLink_80390228(proc->gobj);
                        } else {
                            if (HSD_GObj_804CE3E4.b3) {
                                HSD_GObjPLink_8039032C(
                                    HSD_GObj_804CE3E4.type, proc->gobj,
                                    HSD_GObj_804CE3E4.p_link,
                                    HSD_GObj_804CE3E4.p_prio,
                                    HSD_GObj_804CE3E4.gobj);
                            }
                            if (HSD_GObj_804CE3E4.b2) {
                                HSD_GObjProc_8038FE24(proc);
                            }
                        }
                        HSD_GObj_804CE3E4.flags = 0;
                    }
                    HSD_GObj_804D781C = NULL;
                    HSD_GObj_804D7838 = NULL;
                }
            }
            proc = HSD_GObj_804D7830;
        }
    }
}

extern s32 HSD_GObj_804085F0[];

// GObj_GetFlagFromArray
u32 HSD_GObj_80390EB8(s32 i)
{
    return HSD_GObj_804085F0[i];
}

inline void render_gobj(HSD_GObj* cur, int i)
{
    HSD_GObj* saved = HSD_GObj_804D7814;
    HSD_GObj_804D7814 = cur;
    cur->render_cb(cur, i);
    HSD_GObj_804D7814 = saved;
}

// GObj_SetTextureCamera
void HSD_GObj_80390ED0(HSD_GObj* gobj, u32 mask)
{
    s32 i = 0;
    while (mask) {
        if (mask & 1) {
            u64 prios = gobj->gxlink_prios;
            s32 j = 0;
            while (prios) {
                if (prios & 1) {
                    HSD_GObj* cur;
                    for (cur = HSD_GObj_804D7824[j]; cur != NULL;
                         cur = cur->next_gx)
                    {
                        if (cur->render_cb != NULL) {
                            render_gobj(cur, i);
                        }
                    }
                }
                j++;
                prios >>= 1;
            }
        }
        i++;
        mask >>= 1;
    }
}

// GObj_RunGXLinkMaxCallbacks
void HSD_GObj_80390FC0(void)
{
    HSD_GObj* saved;
    HSD_GObj* cur = HSD_GObj_804D7824[HSD_GObjLibInitData.gx_link_max + 1];
    while (cur != NULL) {
        if (cur->render_cb != NULL) {
            saved = HSD_GObj_804D7818;
            HSD_GObj_804D7818 = cur;
            cur->render_cb(cur, 0);
            HSD_GObj_804D7818 = saved;
        }
        cur = cur->next_gx;
    }
}

void HSD_GObj_LObjCallback(HSD_GObj* gobj, int unused)
{
    HSD_LObj_803668EC(gobj->hsd_obj);
    HSD_LObjSetupInit(HSD_CObjGetCurrent());
}

void HSD_GObj_JObjCallback(HSD_GObj* gobj, int arg1)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    /// @todo don't inline #HSD_GObj_80390EB8
    ///       is there a file boundary between #HSD_GObj_80390EB8 and
    ///       #HSD_GObj_JObjCallback?
#pragma push
#pragma dont_inline on
    HSD_JObjDispAll(jobj, NULL, HSD_GObj_80390EB8(arg1), 0);
}
#pragma pop

void HSD_GObj_FogCallback(HSD_GObj* gobj, int unused)
{
    HSD_FogSet(gobj->hsd_obj);
}

void HSD_GObj_803910D8(HSD_GObj* gobj)
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

struct _GObjFuncs {
    struct _GObjFuncs* next;
    u8 size;
    void (**funcs)(void);
};

void HSD_GObj_80391260(struct _GObjUnkStruct* arg0)
{
    u8 count = HSD_GObj_803912A8(arg0, &HSD_GObj_80408610);
    *HSD_GObj_804D784B = count++;
    HSD_GObj_804D784A = count++;
    HSD_GObj_804D7849 = count++;
    HSD_GObj_804D7848 = count;
}

struct _GObjUnkStruct {
    u32 _;
    GObjFuncs foo;
};

u8 HSD_GObj_803912A8(GObjUnkStruct* arg0, GObjFuncs* foo)
{
    GObjFuncs* cur = &arg0->foo;
    u8 var_r3 = 0;
    while (cur->next != NULL) {
        cur = cur->next;
        var_r3 += cur->size;
    }
    cur->next = foo;
    cur->next->next = NULL;
    return var_r3;
}

void HSD_GObj_803912E0(GObjFuncs* arg0)
{
    *arg0 = HSD_GObj_80408620;
}
