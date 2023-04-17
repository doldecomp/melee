#include <platform.h>

#include <dolphin/os/init/__ppc_eabi_init.h>
#include <MSL/abort_exit.h>

void __destroy_global_chain(void);
void __kill_critical_regions(void);

extern void (*MSL_AbortExit_803B7260[])(void);

void (*MSL_AbortExit_804A2F48[64])(void);
void (*MSL_AbortExit_804A3048[64])(void);
void (*MSL_AbortExit_804D7070)(void);
void (*MSL_AbortExit_804D706C)(void);
s32 MSL_AbortExit_804D7068;
s32 MSL_AbortExit_804D7064;
s32 MSL_AbortExit_804D7060;

void exit(int code)
{
    void (**dtor)(void);

    if (MSL_AbortExit_804D7060 == 0) {
        while (MSL_AbortExit_804D7064 > 0) {
            MSL_AbortExit_804A2F48[--MSL_AbortExit_804D7064]();
        }
        __destroy_global_chain();
        for (dtor = MSL_AbortExit_803B7260; *dtor != NULL; dtor += 1) {
            (*dtor)();
        }
        if (MSL_AbortExit_804D706C != NULL) {
            MSL_AbortExit_804D706C();
            MSL_AbortExit_804D706C = NULL;
        }
    }
    while (MSL_AbortExit_804D7068 > 0) {
        MSL_AbortExit_804A3048[--MSL_AbortExit_804D7068]();
    }
    __kill_critical_regions();
    if (MSL_AbortExit_804D7070 != NULL) {
        MSL_AbortExit_804D7070();
        MSL_AbortExit_804D7070 = NULL;
    }
    _ExitProcess();
}
