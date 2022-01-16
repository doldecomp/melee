#include "melee/ft/ftness.h"
void ftNess_Reset(struct _HSD_GObj* arg0, s32 arg1) // formerly func_801147C0
{
    struct Fighter* temp = (struct Fighter*)arg0->data;
    func_80074A4C(arg0, 0, 0);
    temp->x2240 = 0;
    temp->x2244 = 0;
    temp->x2248 = 0;
    temp->x222C = 0;
    temp->x224C = 0;
}
void func_8011493C(s32 arg) {
    func_8011B0F8(arg);
}
f32 func_8011495C(struct Fighter* arg0) {
    return ((struct ftAttributes2D4* )arg0->unk2D4)->unk94;
}
void func_80114A48(struct _HSD_GObj* arg0) {
    if (func_8026B2B4(((struct Fighter*)arg0->data)->x1974) == 0) {
        func_80070CC4(arg0, 1);
    }
}
void func_80114A90(struct _HSD_GObj* arg0) {
    if (func_8026B2B4(((struct Fighter*)arg0->data)->x1974) == 0) {
        func_80070C48(arg0, 1);
    }
}
void func_80114AD8(struct _HSD_GObj* arg0, s32 arg1) {
    func_80070FB4(arg0, 1, -1);
    if (arg1 != 0) {
        func_80070CC4(arg0, 1);
    }
}
void func_80114B6C(struct _HSD_GObj* arg0) {
    func_800704F0(arg0, 1, lbl_804D96B0);
    func_800704F0(arg0, 0, lbl_804D96B0);
}
