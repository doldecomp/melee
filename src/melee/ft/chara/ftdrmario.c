#include "ftdrmario.h"

void ftDrMario_OnDeath(HSD_GObj* gobj) {
    Fighter* ft = (Fighter*)gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    ft->x2234 = 0;
    ft->x2238 = 0;
    ft->x223C = 0;
    ft->x2240 = 0;
}
