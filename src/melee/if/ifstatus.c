#include <melee/if/ifstatus.h>

extern s8 lbl_804D6D60;

extern unk_t lbl_802F74D0();
extern unk_t lbl_802F73C4();

extern Thing_803F9628 lbl_803F9628;

// free
void func_802F7220(void) {
    s32 i;
    for (i = 0; i < 8; i++) {
        if (lbl_803F9628.things[i].unk0 != NULL) {
            func_80390228(lbl_803F9628.things[i].unk0);
            lbl_803F9628.things[i].unk0 = NULL;
        }
    }
}


