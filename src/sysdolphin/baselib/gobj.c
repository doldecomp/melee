#include <sysdolphin/baselib/gobj.h>

extern u32 lbl_804D783C;

inline u8 GObj_SetFlag1_inline(HSD_GObjProc* proc, u8 value)
{
    while (proc != NULL) {
        proc->flags_1 = value & 0x7F;
        proc = proc->child;
    }
}

inline u8 GObj_SetFlag2_inline(HSD_GObjProc* proc, u8 value)
{
    while (proc != NULL) {
        proc->flags_2 = value & 0x7F;
        proc = proc->child;
    }
}

void func_80390C5C(HSD_GObj* gobj) {
    GObj_SetFlag1_inline(gobj->proc, 1);
}

void func_80390C84(HSD_GObj* gobj) {
    GObj_SetFlag1_inline(gobj->proc, 0);
}

void func_80390CAC(HSD_GObj* gobj) {
    GObj_SetFlag2_inline(gobj->proc, 0);
}

void func_80390CD4(HSD_GObj* gobj) {
    HSD_GObjProc* p = gobj->proc;

    while (p != NULL) {
        p->flags_3 = lbl_804D783C;
        p = p->child;
    }
}
