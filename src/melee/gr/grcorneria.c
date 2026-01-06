#include "grcorneria.h"

#include "granime.h"

#include "grcorneria.static.h"

#include "grmaterial.h"
#include "ground.h"
#include "grzakogenerator.h"
#include "inlines.h"
#include "stage.h"
#include "types.h"

#include "lb/lb_00B0.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

/// #grCorneria_801DCCFC

/// #grCorneria_801DCE1C

/// #grCorneria_801DD2C0

/// #grCorneria_801DD350

/// #grCorneria_801DD478

/// #grCorneria_801DD508

bool grCorneria_801DD52C(void)
{
    return false;
}

/// #grCorneria_801DD534

void grCorneria_801DD620(Ground_GObj* gobj)
{
    grAnime_801C8138((HSD_GObj*) gobj, GET_GROUND(gobj)->map_id, 0);
}

bool grCorneria_801DD64C(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801DD654(Ground_GObj* arg) {}

void grCorneria_801DD658(Ground_GObj* arg) {}

void fn_801DD65C(Ground_GObj* gobj)
{
    GET_GROUND(gobj)->gv.corneria.xC4_flags.b0 = false;
}

extern int grCn_803E1FE8[];
extern int grCn_803E2000[];

void grCorneria_801DD674(Ground_GObj* ground_gobj)
{
    Vec3 translate;
    HSD_JObj* jobj;
    u32 unused;

    Ground* gr = GET_GROUND(ground_gobj);
    Ground_801C2ED0(ground_gobj->hsd_obj, gr->map_id);
    gr->gv.corneria.xC4_flags.b0 = 1;
    gr->gv.corneria.xC4_flags.b1 = 0;
    gr->gv.corneria.base_x = 0.0f;
    gr->gv.corneria.base_y = 250.0f;
    gr->gv.corneria.xD0 = 0.0f;
    gr->gv.corneria.offset_x = 0.0f;
    gr->gv.corneria.offset_y.val = 0.0f;
    gr->gv.corneria.xE4 = 0.0f;
    gr->gv.corneria.xE8 = 0.0f;
    gr->gv.corneria.xEC = 0.0f;
    gr->gv.corneria.xF0 = 0.0f;
    gr->gv.corneria.xF4 = 0.0f;
    gr->gv.corneria.xF8 = 0.0f;
    gr->gv.corneria.x104 = 0;
    gr->x10_flags.b5 = 1;
    grAnime_801C8138(ground_gobj, gr->map_id, 0);
    grAnime_801C8780(ground_gobj, 3, 0, 0.0f, 1.0f);
    gr->gv.corneria.x128 = grCorneria_801DD534(0);
    jobj = ground_gobj->hsd_obj;
    translate.x = gr->gv.corneria.base_x + gr->gv.corneria.offset_x;
    translate.y = gr->gv.corneria.base_y + gr->gv.corneria.offset_y.val;
    translate.z = 0.0f;
    HSD_JObjSetTranslate(jobj, &translate);
    grCorneria_801E1878(ground_gobj);
    Ground_801C39C0();
    Ground_801C3BB4();
    gr->gv.corneria.x108 = 0;
    gr->gv.corneria.x10C = 0;
    gr->gv.corneria.x118 = 0;
    gr->gv.corneria.x11A = 0;
    gr->gv.corneria.x110 = 0;
    gr->gv.corneria.x114 = 0.0f;
    gr->gv.corneria.left_cannon =
        grMaterial_801C8CFC(0, 0, gr, Ground_801C3FA4(ground_gobj, 2),
                            fn_801E12D0, fn_801E12D4, 0);
    grMaterial_801C8DE0(gr->gv.corneria.left_cannon, 4.0f, 0.0f, 0.0f, 16.0f,
                        0.0f, 0.0f, 4.0f);
    grMaterial_801C8E08(gr->gv.corneria.left_cannon);
    gr->gv.corneria.right_cannon =
        grMaterial_801C8CFC(0, 2, gr, Ground_801C3FA4(ground_gobj, 3),
                            fn_801E12D0, fn_801E12D4, 0);
    grMaterial_801C8E08(gr->gv.corneria.right_cannon);
    grMaterial_801C8DE0(gr->gv.corneria.right_cannon, 4.0f, 0.0f, 0.0f, 16.0f,
                        0.0f, 0.0f, 4.0f);
    HSD_JObjClearFlags(Ground_801C3FA4(ground_gobj, 6), JOBJ_HIDDEN);
    HSD_JObjSetFlags(Ground_801C3FA4(ground_gobj, 5), JOBJ_HIDDEN);
    gr->gv.corneria.xC8 =
        grZakoGenerator_801CA394(grCn_803E1FE8, 1, fn_801E2454, 0.3f);
    gr->gv.corneria.xCC =
        grZakoGenerator_801CA394(grCn_803E2000, 2, fn_801E2480, 0.3f);
    Ground_801C10B8(ground_gobj, fn_801DD65C);
    gr->x11_flags.b012 = 1;
    gr->gv.corneria.x12C = Ground_801C3FA4(ground_gobj, 8);
}

bool grCorneria_801DD9A0(Ground_GObj* arg)
{
    return false;
}

/// #grCorneria_801DD9A8

void grCorneria_801DDAC0(Ground_GObj* arg) {}

/// #grCorneria_801DDAC4

bool grCorneria_801DDCE8(Ground_GObj* arg)
{
    return false;
}

/// #grCorneria_801DDCF0

/// #grCorneria_801DDD4C

/// #grCorneria_801DDDA8

/// #grCorneria_801DDE88

/// #grCorneria_801DE024

void grCorneria_801DE4BC(Ground_GObj* arg) {}

/// #grCorneria_801DE4C0

bool grCorneria_801DE560(Ground_GObj* arg)
{
    return false;
}

/// #grCorneria_801DE568

void grCorneria_801DE8E0(Ground_GObj* arg) {}

/// #grCorneria_801DE8E4

bool grCorneria_801DEC00(Ground_GObj* arg)
{
    return false;
}

s32 grCorneria_801DEC08(Vec3* pos)
{
    if (pos->x > Stage_GetBlastZoneRightOffset()) {
        return 1;
    }
    if (pos->x < Stage_GetBlastZoneLeftOffset()) {
        return 1;
    }
    if (pos->y > Stage_GetBlastZoneTopOffset()) {
        return 1;
    }
    if (pos->y < Stage_GetBlastZoneBottomOffset()) {
        return 1;
    }
    return 0;
}
/// #grCorneria_801DEC94

/// #grCorneria_801DED50

void grCorneria_801DF8CC(Ground_GObj* arg) {}

/// #grCorneria_801DF8D0

bool grCorneria_801DFBC4(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801DFBCC(Ground_GObj* arg)
{
    grCorneria_801DED50(arg);
}

void grCorneria_801DFBEC(Ground_GObj* arg) {}

void grCorneria_801DFBF0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
}

bool grCorneria_801DFC1C(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801DFC24(Ground_GObj* arg) {}

void grCorneria_801DFC28(Ground_GObj* arg) {}

void grCorneria_801DFC2C(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    struct grCorneria_GroundVars* cn = &gp->gv.corneria;

    cn->xC6_flags.b0 = 0;
    cn->offset_y.flags.b0 = 0;
    cn->xC8 = 0;
    cn->xCC = 0;
    cn->xD0 = 0.0f;
    cn->base_x = 0.0f;
    cn->base_y = 0.0f;
    cn->offset_x = 0.0f;
    cn->xC4_flags.b0 = 0;
    cn->xC4_flags.b1 = 0;
    gp->x11_flags.b012 = 1;
}
bool grCorneria_801DFC90(Ground_GObj* arg)
{
    return false;
}

/// #grCorneria_801DFC98

void grCorneria_801DFEB4(Ground_GObj* arg) {}

void grCorneria_801DFEB8(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    struct grCorneria_GroundVars* cn = &gp->gv.corneria;

    cn->xC6_flags.b0 = 0;
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
    cn->xC4_flags.b0 = 0;
    cn->xC4_flags.b1 = 0;
    gp->x11_flags.b012 = 1;
}
bool grCorneria_801DFF18(Ground_GObj* arg)
{
    return false;
}

/// #grCorneria_801DFF20

void grCorneria_801E013C(Ground_GObj* arg) {}

/// #grCorneria_801E0140

bool grCorneria_801E01A0(Ground_GObj* arg)
{
    return false;
}

/// #grCorneria_801E01A8

void grCorneria_801E03C4(Ground_GObj* arg) {}

/// #grCorneria_801E03C8

/// #grCorneria_801E0678

/// #grCorneria_801E08CC

int grCorneria_801E0A74(f32* arg0)
{
    HSD_GObj* gobj;

    gobj = Ground_801C2BA4(8);
    if (gobj != NULL) {
        f32 x = HSD_JObjGetTranslationX(gobj->hsd_obj);
        if (*arg0 > x - 3200.0f * Ground_801C0498() / 2 &&
            *arg0 < x + 3200.0f * Ground_801C0498() / 2)
        {
            return 8;
        }
    }
    gobj = Ground_801C2BA4(9);
    if (gobj != NULL) {
        f32 x = HSD_JObjGetTranslationX(gobj->hsd_obj);
        if (*arg0 > x - 3200.0f * Ground_801C0498() / 2 &&
            *arg0 < x + 3200.0f * Ground_801C0498() / 2)
        {
            return 9;
        }
    }
    gobj = Ground_801C2BA4(4);
    if (gobj != NULL) {
        f32 x = HSD_JObjGetTranslationX(gobj->hsd_obj);
        if (*arg0 > x - 4800.0f * Ground_801C0498() / 2 &&
            *arg0 < x + 4800.0f * Ground_801C0498() / 2)
        {
            return 4;
        }
    }
    OSReport("grcorneria.c    grCorneriaGetPosMapKind2\n");
    __assert("grcorneria.c", 2507, "0");
    return -1;
}

static inline void clearX10_b2(HSD_GObj* gobj)
{
    GET_GROUND(gobj)->x10_flags.b2 = false;
}

void grCorneria_801E0C3C(Ground_GObj* gobj)
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

bool grCorneria_801E0D28(Ground_GObj* arg)
{
    return false;
}

/// #grCorneria_801E0D30

void grCorneria_801E0DE0(Ground_GObj* arg) {}

s32 grCorneria_801E0DE4(Ground_GObj* gobj)
{
    Ground* gr = GET_GROUND(gobj);
    return grCorneria_801E2550(gobj, &gr->gv.corneria);
}

bool grCorneria_801E0E0C(Ground_GObj* arg)
{
    return false;
}

/// #grCorneria_801E0E14

void grCorneria_801E0E3C(Ground_GObj* arg) {}

/// #grCorneria_801E0E40

void grCorneria_801E0F30(Ground_GObj* arg) {}

/// #grCorneria_801E0F34

bool grCorneria_801E0F64(Ground_GObj* arg)
{
    return false;
}

/// #grCorneria_801E0F6C

/// #grCorneria_801E1030

void grCorneria_801E1054(Ground_GObj* arg) {}

bool grCorneria_801E1058(Ground_GObj* arg)
{
    return false;
}

/// #grCorneria_801E1060

void grCorneria_801E12CC(Ground_GObj* arg) {}

void fn_801E12D0(Item_GObj* gobj, Ground* gr) {}

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

DynamicsDesc* grCorneria_801E2EE4(enum_t arg)
{
    return NULL;
}

bool grCorneria_801E2EEC(Vec3* v, int arg1, HSD_JObj* jobj)
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
        if (temp_r3_2 != NULL && temp_r3_2->gv.corneria.x12C == jobj) {
            temp_f31 = 106.0f * Ground_801C0498();
            temp_f31_2 =
                ((v->y - sp14.y) * ((107.0f * Ground_801C0498()) / temp_f31)) +
                sp14.x;
            if (v->x > -((107.0f * Ground_801C0498()) - temp_f31_2)) {
                return false;
            }
        }
    }
    if (v->y > sp14.y) {
        return true;
    }
    return false;
}

/// #grCorneria_801E2FCC
