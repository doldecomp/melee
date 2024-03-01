#include <platform.h>

#include "gr/ground.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx/types.h>
#include <baselib/jobj.h>

bool grCastle_801D0B0C(Vec3* v, u32 arg1, HSD_JObj* jobj)
{
    Vec3 pos;
    float temp_f30;
    float temp_f31;
    float temp_f31_2;

    temp_f31 = 192.0f;
    temp_f30 = 137.0f;
    temp_f31_2 = temp_f31 * Ground_801C0498();
    if ((v->x > temp_f31_2) && (v->y < (temp_f30 * Ground_801C0498()))) {
        return 0;
    }
    lb_8000B1CC(jobj, NULL, &pos);
    if ((1 + v->y) > pos.y) {
        return 1;
    }
    return 0;
}
