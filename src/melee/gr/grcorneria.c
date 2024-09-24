#include "granime.h"
#include "grmaterial.h"
#include "ground.h"
#include "inlines.h"
#include "types.h"

#include "lb/lb_00B0.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

/* 1DD654 */ static void grCorneria_801DD654(void);
/* 1DD658 */ static void grCorneria_801DD658(void);
/* 1DDAC0 */ static void grCorneria_801DDAC0(void);
/* 1DE4BC */ static void grCorneria_801DE4BC(void);
/* 1DE8E0 */ static void grCorneria_801DE8E0(void);
/* 1DF8CC */ static void grCorneria_801DF8CC(void);
/* 1DFBEC */ static void grCorneria_801DFBEC(void);
/* 1DFC24 */ static void grCorneria_801DFC24(void);
/* 1DFC28 */ static void grCorneria_801DFC28(void);
/* 1DFEB4 */ static void grCorneria_801DFEB4(void);
/* 1E013C */ static void grCorneria_801E013C(void);
/* 1E03C4 */ static void grCorneria_801E03C4(void);
/* 1E0DE0 */ static void grCorneria_801E0DE0(void);
/* 1E0E3C */ static void grCorneria_801E0E3C(void);
/* 1E0F30 */ static void grCorneria_801E0F30(void);
/* 1E1054 */ static void grCorneria_801E1054(void);
/* 1E12CC */ static void grCorneria_801E12CC(void);

/// #grCorneria_801DCCFC

/// #grCorneria_801DCE1C

/// #grCorneria_801DD2C0

/// #grCorneria_801DD350

/// #grCorneria_801DD478

/// #grCorneria_801DD508

/// #grCorneria_801DD52C

/// #grCorneria_801DD534

/// #grCorneria_801DD620

/// #grCorneria_801DD64C

void grCorneria_801DD654(void) {}

void grCorneria_801DD658(void) {}

/// #fn_801DD65C

/// #grCorneria_801DD674

/// #grCorneria_801DD9A0

/// #grCorneria_801DD9A8

void grCorneria_801DDAC0(void) {}

/// #grCorneria_801DDAC4

/// #grCorneria_801DDCE8

/// #grCorneria_801DDCF0

/// #grCorneria_801DDD4C

/// #grCorneria_801DDDA8

/// #grCorneria_801DDE88

/// #grCorneria_801DE024

void grCorneria_801DE4BC(void) {}

/// #grCorneria_801DE4C0

/// #grCorneria_801DE560

/// #grCorneria_801DE568

void grCorneria_801DE8E0(void) {}

/// #grCorneria_801DE8E4

/// #grCorneria_801DEC00

/// #grCorneria_801DEC08

/// #grCorneria_801DEC94

/// #grCorneria_801DED50

void grCorneria_801DF8CC(void) {}

/// #grCorneria_801DF8D0

/// #grCorneria_801DFBC4

/// #grCorneria_801DFBCC

void grCorneria_801DFBEC(void) {}

/// #grCorneria_801DFBF0

/// #grCorneria_801DFC1C

void grCorneria_801DFC24(void) {}

void grCorneria_801DFC28(void) {}

/// #grCorneria_801DFC2C

/// #grCorneria_801DFC90

/// #grCorneria_801DFC98

void grCorneria_801DFEB4(void) {}

/// #grCorneria_801DFEB8

/// #grCorneria_801DFF18

/// #grCorneria_801DFF20

void grCorneria_801E013C(void) {}

/// #grCorneria_801E0140

/// #grCorneria_801E01A0

/// #grCorneria_801E01A8

void grCorneria_801E03C4(void) {}

/// #grCorneria_801E03C8

/// #grCorneria_801E0678

/// #grCorneria_801E08CC

/// #grCorneria_801E0A74

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

/// #grCorneria_801E0D28

/// #grCorneria_801E0D30

void grCorneria_801E0DE0(void) {}

/// #grCorneria_801E0DE4

/// #grCorneria_801E0E0C

/// #grCorneria_801E0E14

void grCorneria_801E0E3C(void) {}

/// #grCorneria_801E0E40

void grCorneria_801E0F30(void) {}

/// #grCorneria_801E0F34

/// #grCorneria_801E0F64

/// #grCorneria_801E0F6C

/// #grCorneria_801E1030

void grCorneria_801E1054(void) {}

/// #grCorneria_801E1058

/// #grCorneria_801E1060

void grCorneria_801E12CC(void) {}

void fn_801E12D0(void) {}

/// #fn_801E12D4

/// #grCorneria_801E1348

/// #grCorneria_801E1878

/// #grCorneria_801E1970

/// #grCorneria_801E1BF0

/// #grCorneria_801E2110

/// #grCorneria_801E2228

/// #fn_801E2454

/// #fn_801E2480

/// #fn_801E24AC

/// #grCorneria_801E2550

/// #grCorneria_801E2598

/// #grCorneria_801E25C4

/// #grCorneria_801E2738

/// #grCorneria_801E277C

/// #grCorneria_801E2A6C

/// #grCorneria_801E2AF4

/// #grCorneria_801E2B80

/// #grCorneria_801E2C34

/// #grCorneria_801E2CE8

/// #grCorneria_801E2D14

/// #grCorneria_801E2D90

/// #grCorneria_801E2E50

/// #grCorneria_801E2EA0

/// #grCorneria_801E2EE4

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

/// #grCorneria_801E2FCC
