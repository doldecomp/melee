#include <sysdolphin/baselib/gobj.h>

#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/lobj.h>

extern HSD_GObj* lbl_804D7818;
extern HSD_GObj* lbl_804D781C;
extern HSD_GObjProc* lbl_804D7830;
extern HSD_GObjProc* lbl_804D7838;
extern HSD_GObjProc** lbl_804D7840;
extern s32 lbl_804D7834;
extern s32 lbl_804D783C;

inline u8 GObj_SetFlag1_inline(HSD_GObjProc* proc, u8 value)
{
    while (proc != NULL) {
        proc->flags_1 = value;
        proc = proc->child;
    }
}

inline u8 GObj_SetFlag2_inline(HSD_GObjProc* proc, u8 value)
{
    while (proc != NULL) {
        proc->flags_2 = value;
        proc = proc->child;
    }
}

void func_80390C5C(HSD_GObj* gobj)
{
    GObj_SetFlag1_inline(gobj->proc, 1);
}

void func_80390C84(HSD_GObj* gobj)
{
    GObj_SetFlag1_inline(gobj->proc, 0);
}

void func_80390CAC(HSD_GObj* gobj)
{
    GObj_SetFlag2_inline(gobj->proc, 0);
}

void func_80390CD4(HSD_GObj* gobj)
{
    HSD_GObjProc* p = gobj->proc;

    while (p != NULL) {
        p->flags_3 = lbl_804D783C;
        p = p->child;
    }
}

// GObj_RunProcs
void func_80390CFC(void)
{
    s32 i;
    HSD_GObjProc* proc;
    HSD_GObj* gobj;

    u64 var_r31 =
        HSD_GObjLibInitData.unk_2 != NULL ? *HSD_GObjLibInitData.unk_2 : 0;
    lbl_804D783C += 1;
    if (lbl_804D783C > 2) {
        lbl_804D783C = 0;
    }

    for (i = 0; i <= HSD_GObjLibInitData.gproc_pri_max; i++) {
        lbl_804D7834 = i;
        proc = lbl_804D7840[i];
        while (proc != NULL) {
            lbl_804D7830 = proc->next;
            if (proc->flags_3 != lbl_804D783C) {
                proc->flags_3 = lbl_804D783C;
                gobj = proc->gobj;
                if (!(var_r31 & (1LL << gobj->p_link)) && !(proc->flags_1) &&
                    !(proc->flags_2))
                {
                    lbl_804D781C = gobj;
                    lbl_804D7838 = proc;
                    proc->callback(proc->gobj);
                    lbl_804D7830 = proc->next;
                    if (lbl_804CE3E4.flags != 0) {
                        lbl_804CE3E4.b0 = 1;
                        if (lbl_804CE3E4.b1) {
                            func_80390228(proc->gobj);
                        } else {
                            if (lbl_804CE3E4.b3) {
                                func_8039032C(lbl_804CE3E4.type, proc->gobj,
                                              lbl_804CE3E4.p_link,
                                              lbl_804CE3E4.p_prio,
                                              lbl_804CE3E4.gobj);
                            }
                            if (lbl_804CE3E4.b2) {
                                func_8038FE24(proc);
                            }
                        }
                        lbl_804CE3E4.flags = 0;
                    }
                    lbl_804D781C = NULL;
                    lbl_804D7838 = NULL;
                }
            }
            proc = lbl_804D7830;
        }
    }
}

extern s32 lbl_804085F0[];

// GObj_GetFlagFromArray
u32 func_80390EB8(s32 i)
{
    return lbl_804085F0[i];
}

extern HSD_GObj* lbl_804D7814;

inline void render_gobj(HSD_GObj* cur, s32 i)
{
    HSD_GObj* saved = lbl_804D7814;
    lbl_804D7814 = cur;
    cur->render_cb(cur, i);
    lbl_804D7814 = saved;
}

// GObj_SetTextureCamera
void func_80390ED0(HSD_GObj* gobj, u32 mask)
{
    s32 i = 0;
    while (mask) {
        if (mask & 1) {
            u64 prios = gobj->gxlink_prios;
            s32 j = 0;
            while (prios) {
                if (prios & 1) {
                    HSD_GObj* cur;
                    for (cur = lbl_804D7824[j]; cur != NULL; cur = cur->next_gx)
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
void func_80390FC0(void)
{
    HSD_GObj* saved;
    HSD_GObj* cur = lbl_804D7824[HSD_GObjLibInitData.gx_link_max + 1];
    while (cur != NULL) {
        if (cur->render_cb != NULL) {
            saved = lbl_804D7818;
            lbl_804D7818 = cur;
            cur->render_cb(cur, 0);
            lbl_804D7818 = saved;
        }
        cur = cur->next_gx;
    }
}

void lbl_80391044(HSD_GObj* gobj)
{
    func_803668EC(gobj->hsd_obj);
    HSD_LObjSetupInit(HSD_CObjGetCurrent());
}

void func_80391070(HSD_GObj* gobj, s32 arg1)
{
    HSD_JObj* jobj = gobj->hsd_obj;

#ifdef MUST_MATCH
// don't inline func_80390EB8
// TODO is there a file boundary between func_80390EB8 and func_80391070?
#pragma push
#pragma dont_inline on
#endif

    HSD_JObjDispAll(jobj, NULL, func_80390EB8(arg1), 0);
}

#ifdef MUST_MATCH
#pragma pop
#endif

void lbl_803910B4(HSD_GObj* gobj)
{
    HSD_FogSet(gobj->hsd_obj);
}

void func_803910D8(HSD_GObj* gobj, s32 arg1)
{
    if (HSD_CObjSetCurrent(gobj->hsd_obj, (Event) arg1)) {
        func_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

void lbl_80391120(HSD_Obj* obj)
{
    if (obj != NULL && ref_DEC(obj)) {
        if (obj != NULL) {
            obj->parent.class_info->release((HSD_Class*) obj);
            obj->parent.class_info->destroy((HSD_Class*) obj);
        }
    }
}

void lbl_803911C0(HSD_Obj* obj)
{
    lbl_80391120(obj);
}

struct _GObjFuncs {
    struct _GObjFuncs* next;
    u8 size;
    void (**funcs)();
};

extern GObjFuncs lbl_80408610;
extern s8 lbl_804D7848;
extern s8 lbl_804D7849;
extern s8 lbl_804D784A;
extern GObjFuncs lbl_80408620;

void func_80391260(struct _GObjUnkStruct* arg0)
{
    u8 count = func_803912A8(arg0, &lbl_80408610);
    *lbl_804D784B = count++;
    lbl_804D784A = count++;
    lbl_804D7849 = count++;
    lbl_804D7848 = count;
}

typedef struct _GObjUnkStruct {
    u32 unused;
    GObjFuncs foo;
} GObjUnkStruct;

u8 func_803912A8(GObjUnkStruct* arg0, GObjFuncs* foo)
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

void func_803912E0(GObjFuncs* arg0)
{
    *arg0 = lbl_80408620;
}
