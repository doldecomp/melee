#include "ftpikachu.h"


extern f32 lbl_804D9910;  /// DELETE ME - remove once the whole file is finished and data is moved over
extern f32 lbl_804D9914;  /// DELETE ME - remove once the whole file is finished and data is moved over

void func_80124E38(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;

    fighter->cb.x21EC_callback = func_80124DC8;

    fighter->xEC_ground_vel /= pika_attr->x30;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x157, 0, 0, lbl_804D9910, lbl_804D9914, lbl_804D9910);
    func_8006EBA4(fighterObj);
}

/////  Match from samer
// void func_8012764C(HSD_GObj* fighterObj) {
//     Fighter* fighter = fighterObj->user_data;
//     fighter->x2344_stateVar2 = 3;
// }