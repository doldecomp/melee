#include "melee/ft/ftness.h"
void ftNess_Reset(struct _HSD_GObj* arg0, s32 arg1) // formerly func_801147C0
{
    struct Fighter* temp = (struct Fighter*)arg0->data;
    func_80074A4C(arg0, 0, 0);
    temp->unk2240 = 0;
    temp->unk2244 = 0;
    temp->unk2248 = 0;
    temp->unk222C = 0;
    temp->unk224C = 0;
}
void func_8011493C(s32 arg) {
    func_8011B0F8(arg);
}
f32 func_8011495C(struct Fighter* arg0) {
    return ((struct ftAttributes* )arg0->unk2D4)->unk94;
}
void func_80114A48(struct _HSD_GObj* arg0) {
    if (func_8026B2B4(((struct Fighter*)arg0->data)->unk1974) == 0) {
        func_80070CC4(arg0, 1);
    }
}
void func_80114A90(struct _HSD_GObj* arg0) {
    if (func_8026B2B4(((struct Fighter*)arg0->data)->unk1974) == 0) {
        func_80070C48(arg0, 1);
    }
}