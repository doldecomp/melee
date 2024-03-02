#include "granime.h"
#include "grmaterial.h"
#include "ground.h"
#include "inlines.h"
#include "types.h"

#include "lb/lb_00B0.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

static inline void clearX10_b2(HSD_GObj* gobj)
{
    GET_GROUND(gobj)->x10_flags.b2 = false;
}

void grCorneria_801E0C3C(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    clearX10_b2(gobj);
    Ground_801C4E70(Ground_801C3FA4(gobj, 5), Ground_801C3FA4(gobj, 2),
                    Ground_801C3FA4(gobj, 4), Ground_801C3FA4(gobj, 3),
                    Ground_801C3FA4(gobj, 7), Ground_801C3FA4(gobj, 6));
    grMaterial_801C8A04(jobj, JOBJ_UNK_B27);
    grMaterial_801C8858(jobj, JOBJ_ROOT_XLU);
    gp->x11_flags.b012 = 2;
}

bool grCorneria_801E2EEC(Vec3* v, u32 arg1, HSD_JObj* jobj)
{
    Vec3 sp14;
    HSD_GObj* temp_r3;
    Ground* temp_r3_2;
    float temp_f31;
    float temp_f31_2;

    lb_8000B1CC(jobj, NULL, &sp14);
    temp_r3 = Ground_801C2BA4(3);
    if (temp_r3 != NULL) {
        temp_r3_2 = temp_r3->user_data;
        if ((temp_r3_2 != NULL) && temp_r3_2->gv.corneria.x68 == jobj) {
            temp_f31 = 106.0f * Ground_801C0498();
            temp_f31_2 =
                ((v->y - sp14.y) * ((107.0f * Ground_801C0498()) / temp_f31)) +
                sp14.x;
            if (v->x > -((107.0f * Ground_801C0498()) - temp_f31_2)) {
                return 0;
            }
        }
    }
    if (v->y > sp14.y) {
        return 1;
    }
    return 0;
}
