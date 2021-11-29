#include "gobj.h"

void func_80390C5C(HSD_GObj* gobj) {
    HSD_GObjProc* p = gobj->proc;

    while (p != NULL) {
        p->flags_1 = 1 & 0x7F;
        p = p->child;
    }
}

void func_80390C84(HSD_GObj* gobj) {
    HSD_GObjProc* p = gobj->proc;

    while (p != NULL) {
        p->flags_1 = 0 & 0x7F;
        p = p->child;
    }
}
