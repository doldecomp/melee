#include <dolphin/types.h>

void _ExitProcess(void);
void __destroy_global_chain(void);
void __kill_critical_regions(void);

extern void (*lbl_803B7260[])(void);

void (*lbl_804A2F48[64])(void);
void (*lbl_804A3048[64])(void);
void (*lbl_804D7070)(void);
void (*lbl_804D706C)(void);
s32 lbl_804D7068;
s32 lbl_804D7064;
s32 lbl_804D7060;

void exit(int) {
    void (**dtor)();

    if (lbl_804D7060 == 0) {
        while (lbl_804D7064 > 0) {
            lbl_804A2F48[--lbl_804D7064 ]();
        }
        __destroy_global_chain();
        for (dtor = lbl_803B7260; *dtor != NULL; dtor += 1) {
            (*dtor)();
        }
        if (lbl_804D706C != NULL) {
            lbl_804D706C();
            lbl_804D706C = NULL;
        }
    }
    while (lbl_804D7068 > 0) {
        lbl_804A3048[--lbl_804D7068]();
    }
    __kill_critical_regions();
    if (lbl_804D7070 != NULL) {
        lbl_804D7070();
        lbl_804D7070 = NULL;
    }
    _ExitProcess();
}

