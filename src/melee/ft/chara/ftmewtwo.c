#include "ftmewtwo.h"

void ftMewtwo_OnDeath(HSD_GObj* gobj) {
    Fighter* ft = (Fighter*)gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    ft->sa.mewtwo.x222C = 0;
    ft->sa.mewtwo.x2230 = 0;
    ft->sa.mewtwo.x2234 = 0;
    ft->sa.mewtwo.x2238 = 0;
    ft->sa.mewtwo.x223C = 0;
}
