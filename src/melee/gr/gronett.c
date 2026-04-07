#include "gronett.h"

#include "placeholder.h"
#include "types.h"

#include <platform.h>

#include "cm/camera.h"

#include "cm/forward.h"

#include "cm/types.h"

#include "forward.h"

#include "ft/ftlib.h"
#include "gm/gm_16AE.h"
#include "gr/grdatfiles.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "if/ifhazard.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/types.h"
#include "mp/mplib.h"

#include "sc/forward.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

StageCallbacks grOt_803E27E0[6] = {
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { grOnett_801E38DC, grOnett_801E3920, grOnett_801E3928, grOnett_801E392C,
      0 },
    { grOnett_801E41C8, grOnett_801E43D8, grOnett_801E43E0, grOnett_801E502C,
      0 },
    { grOnett_801E3CE4, grOnett_801E3D98, grOnett_801E3DA0, grOnett_801E40E0,
      0 },
    { grOnett_801E3A34, grOnett_801E3C58, grOnett_801E3C60, grOnett_801E3CE0,
      0xC0000000 },
};

StageData grOt_803E2858 = {
    0x14,
    grOt_803E27E0,
    "/GrOt",
    grOnett_801E3738,
    grOnett_801E3734,
    grOnett_801E37C4,
    grOnett_801E37C8,
    grOnett_801E37EC,
    grOnett_801E5760,
    grOnett_801E5768,
    1,
    NULL,
    0,
};

/// Onett stage yakumono parameters
static struct grOnett_StageParam {
    /* 0x00 */ f32 awning_initial;
    /* 0x04 */ f32 max_velocity;
    /* 0x08 */ f32 vel_threshold;
    /* 0x0C */ f32 pos_threshold;
    /* 0x10 */ f32 damping;
    /* 0x14 */ f32 spring_force;
    /* 0x18 */ f32 spring_constant;
    /* 0x1C */ f32 max_displacement;
    /* 0x20 */ f32 awning_delta;
    /* 0x24 */ f32 x24;
    /* 0x28 */ f32 x28;
    /* 0x2C */ f32 x2C;
    /* 0x30 */ f32 x30;
    /* 0x34 */ f32 x34;
    /* 0x38 */ f32 x38;
    /* 0x3C */ f32 x3C;
    /* 0x40 */ f32 x40;
    /* 0x44 */ s32 x44;
    /* 0x48 */ s32 x48;
    /* 0x4C */ s32 x4C;
    /* 0x50 */ s32 x50;
    /* 0x54 */ f32 x54;
    /* 0x58 */ f32 x58;
    /* 0x5C */ f32 x5C;
    /* 0x60 */ f32 x60;
    /* 0x64 */ f32 x64;
}* grOt_804D69C0;

static s32 grOt_804D69C4;

void grOnett_801E3734(bool arg) {}

void grOnett_801E3738(void)
{
    grOt_804D69C0 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grOnett_801E37F4(0);
    grOnett_801E37F4(2);
    grOnett_801E37F4(5);
    grOnett_801E37F4(4);
    grOnett_801E37F4(3);
    un_802FD8A0(grOnett_801E56FC());
    un_802FD65C();
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grOnett_801E37C4(void) {}

void grOnett_801E37C8(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grOnett_801E37EC(void)
{
    return false;
}

HSD_GObj* grOnett_801E37F4(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grOt_803E27E0[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (callbacks->callback3 != NULL) {
            gp->x1C_callback = callbacks->callback3;
        }
        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }
        if (callbacks->callback2 != NULL) {
            HSD_GObj_SetupProc(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 235, gobj_id);
    }

    return gobj;
}

void grOnett_801E38DC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

bool grOnett_801E3920(Ground_GObj* gobj)
{
    return false;
}

void grOnett_801E3928(Ground_GObj* gobj) {}

void grOnett_801E392C(Ground_GObj* gobj) {}

void grOnett_801E3930(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    mpJointSetCb1(0, gp, grOnett_801E54B4);
    mpJointSetCb1(1, gp, grOnett_801E54B4);
    gp->gv.onett.subject = Camera_80029020();
    if (gp->gv.onett.subject == NULL) {
        __assert("gronett.c", 331, "gp->u.map.subject");
    }
    gp->gv.onett.subject->x40.x = -40.0f;
    gp->gv.onett.subject->x40.y = 40.0f;
    gp->gv.onett.subject->x48.x = 20.0f;
    gp->gv.onett.subject->x48.y = -20.0f;
    gp->gv.onett.subject->x48.z = 1.0f;
    gp->gv.onett.subject->x10.x = 0.0f;
    gp->gv.onett.subject->x10.y = 0.0f;
    gp->gv.onett.subject->x10.z = 0.0f;
    gp->gv.onett.subject->x1C = gp->gv.onett.subject->x10;
    gp->gv.onett.subject->x8 = true;
}

void grOnett_801E3A34(Ground_GObj* gobj)
{
    HSD_JObj* jobj;
    Ground* gp;
    PAD_STACK(24);
    gp = GET_GROUND(gobj);
    jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x10_flags.b5 = 1;

    gp->gv.onett.awnings[0].initial = 0.0f;
    gp->gv.onett.awnings[0].jobj = Ground_801C3FA4(gobj, 0xE);
    {
        HSD_JObj* awj = gp->gv.onett.awnings[0].jobj;
        HSD_ASSERT(1006, awj);
        gp->gv.onett.awnings[0].initial_y = awj->translate.y;
    }
    gp->gv.onett.awnings[0].accumulator = 0.0f;
    gp->gv.onett.awnings[0].velocity = 0.0f;
    gp->gv.onett.awnings[0].counter_prev = 0;
    gp->gv.onett.awnings[0].counter = 0;
    gp->gv.onett.awnings[0].flag = 0;
    gp->gv.onett.awnings[0].cooldown = 0;

    gp->gv.onett.awnings[1].initial = 0.0f;
    gp->gv.onett.awnings[1].jobj = Ground_801C3FA4(gobj, 0xF);
    {
        HSD_JObj* awj = gp->gv.onett.awnings[1].jobj;
        HSD_ASSERT(1006, awj);
        gp->gv.onett.awnings[1].initial_y = awj->translate.y;
    }
    gp->gv.onett.awnings[1].accumulator = 0.0f;
    gp->gv.onett.awnings[1].velocity = 0.0f;
    gp->gv.onett.awnings[1].counter_prev = 0;
    gp->gv.onett.awnings[1].counter = 0;
    gp->gv.onett.awnings[1].flag = 0;
    gp->gv.onett.awnings[1].cooldown = 0;

    gp->gv.onett.subject = NULL;

    gp->gv.onett.timer = rand_range(grOt_804D69C0->x24, grOt_804D69C0->x28);
    gp->gv.onett.gen = NULL;

    Ground_801C4E70(Ground_801C3FA4(gobj, 16), Ground_801C3FA4(gobj, 17),
                    Ground_801C3FA4(gobj, 19), Ground_801C3FA4(gobj, 20),
                    Ground_801C3FA4(gobj, 18), Ground_801C3FA4(gobj, 21));

    Ground_801C10B8(gobj, grOnett_801E3930);
    Ground_801C2FE0(gobj);
}

bool grOnett_801E3C58(Ground_GObj* gobj)
{
    return false;
}

void grOnett_801E3C60(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    PAD_STACK(8);

    grOnett_801E5214(gobj);
    grOnett_801E5538(gobj);
    if (gp->gv.onett.subject != NULL) {
        if (Ground_801C5794() != 0) {
            gp->gv.onett.subject->x8 = false;
        } else {
            gp->gv.onett.subject->x8 = true;
        }
    }
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grOnett_801E3CE0(Ground_GObj* gobj) {}

void grOnett_801E3CE4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    PAD_STACK(8);

    Ground_801C2ED0(GET_JOBJ(gobj), gp->map_id);
    grAnime_801C7FF8(gobj, 0, 7, 0, 0.0f, 0.0f);

    gp->gv.onett_building.state = -1;
    gp->gv.onett_building.next_state = 0;
    gp->gv.onett_building.hit_count = 0;
    gp->gv.onett_building.frame = 0;

    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    gp->x10_flags.b5 = 1;

    mpJointSetCb1(3, gp, grOnett_801E40E4);
    mpJointSetCb1(4, gp, grOnett_801E40E4);
}

bool grOnett_801E3D98(Ground_GObj* gobj)
{
    return false;
}

void grOnett_801E3DA0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    s32 tmp;

    gp->gv.onett_building.frame += 1;

    switch (gp->gv.onett_building.state) {
    case 7:
        if (gp->gv.onett_building.timer & 2) {
            HSD_JObjSetFlagsAll(Ground_801C3FA4(gobj, 5), JOBJ_HIDDEN);
            HSD_JObjSetFlagsAll(Ground_801C3FA4(gobj, 2), JOBJ_HIDDEN);
            HSD_JObjSetFlagsAll(Ground_801C3FA4(gobj, 4), JOBJ_HIDDEN);
        } else {
            HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        }
        tmp = gp->gv.onett_building.timer;
        gp->gv.onett_building.timer = tmp - 1;
        if (tmp < 0) {
            HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
            gp->gv.onett_building.next_state = 0;
        }
        break;
    case 1:
        if (grAnime_801C83D0(gobj, 0, 7)) {
            gp->gv.onett_building.next_state = 0;
        }
        break;
    case 2:
        if (gp->gv.onett_building.frame == 0x8C) {
            Ground_801C5440(gp, 0, 0x5F373);
        }
        if (grAnime_801C83D0(gobj, 0, 7)) {
            gp->gv.onett_building.next_state = 3;
        }
        break;
    case 4:
        if (grAnime_801C83D0(gobj, 0, 7)) {
            gp->gv.onett_building.next_state = 3;
        }
        break;
    case 5:
        if (gp->gv.onett_building.frame == 0x46 ||
            gp->gv.onett_building.frame == 0x82)
        {
            Ground_801C5440(gp, 0, 0x5F374);
        }
        if (grAnime_801C83D0(gobj, 0, 7)) {
            f32 rand = HSD_Randf();
            f32 lo = grOt_804D69C0->x3C;
            f32 range = grOt_804D69C0->x40 - lo;
            gp->gv.onett_building.timer = (s32) (range * rand + lo);
            gp->gv.onett_building.next_state = 6;
        }
        if (gp->gv.onett_building.frame == 0x14) {
            mpLib_80057BC0(3);
        } else if (gp->gv.onett_building.frame == 0x5A) {
            mpLib_80057BC0(4);
        }
        break;
    case 6:
        tmp = gp->gv.onett_building.timer;
        gp->gv.onett_building.timer = tmp - 1;
        if (tmp < 0) {
            gp->gv.onett_building.next_state = 7;
            gp->gv.onett_building.timer = 0x3C;
        }
        break;
    }

    if (gp->gv.onett_building.state != gp->gv.onett_building.next_state) {
        gp->gv.onett_building.state = gp->gv.onett_building.next_state;
        switch (gp->gv.onett_building.state) {
        case 7:
            grAnime_801C7FF8(gobj, 0, 7, 0, 0.0f, 1.0f);
            mpJointListAdd(3);
            mpJointListAdd(4);
            break;
        case 1:
            grAnime_801C7FF8(gobj, 0, 7, 1, 0.0f, 1.0f);
            break;
        case 2:
            grAnime_801C7FF8(gobj, 0, 7, 3, 0.0f, 1.0f);
            break;
        case 4:
            grAnime_801C7FF8(gobj, 0, 7, 4, 0.0f, 1.0f);
            break;
        case 5:
            grAnime_801C7FF8(gobj, 0, 7, 5, 0.0f, 1.0f);
            break;
        case 6:
            gp->gv.onett_building.hit_count = 0;
            break;
        }
        gp->gv.onett_building.frame = 0;
    }

    Ground_801C2FE0(gobj);
}

void grOnett_801E40E0(Ground_GObj* gobj) {}

void grOnett_801E40E4(Ground* gp, s32 arg1, CollData* cd, s32 arg3,
                      mpLib_GroundEnum arg4, f32 arg5)
{
    PAD_STACK(8);

    if (arg4 == 1) {
        gp->gv.onett_building.hit_count += 1;
        switch (gp->gv.onett_building.state) {
        case 0:
            if (gp->gv.onett_building.hit_count < grOt_804D69C0->x34) {
                gp->gv.onett_building.next_state = 1;
                return;
            }
            gp->gv.onett_building.next_state = 2;
            return;
        case 3:
            if (gp->gv.onett_building.hit_count < grOt_804D69C0->x38) {
                gp->gv.onett_building.next_state = 4;
                return;
            }
            gp->gv.onett_building.next_state = 5;
            break;
        }
    }
}

void grOnett_801E41B0(HSD_GObj* gobj)
{
    GET_GROUND(gobj)->gv.onettcar.x0_b0 = false;
}

void grOnett_801E41C8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    int i;
    PAD_STACK(16);

    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;

    gp->gv.onettcar.car_jobjs[0] = Ground_801C3FA4(gobj, 0xB);
    gp->gv.onettcar.car_jobjs[1] = Ground_801C3FA4(gobj, 0x1);
    gp->gv.onettcar.car_jobjs[2] = Ground_801C3FA4(gobj, 0x6);
    gp->gv.onettcar.car_jobjs[3] = Ground_801C3FA4(gobj, 0x10);
    gp->gv.onettcar.unk_jobj = Ground_801C3FA4(gobj, 0x10);

    gp->gv.onettcar.car_jobjs2[0] = Ground_801C3FA4(gobj, 0xF);
    gp->gv.onettcar.car_jobjs2[1] = Ground_801C3FA4(gobj, 0x5);
    gp->gv.onettcar.car_jobjs2[2] = Ground_801C3FA4(gobj, 0xA);
    gp->gv.onettcar.car_jobjs2[3] = Ground_801C3FA4(gobj, 0x14);
    gp->gv.onettcar.unk_jobj2 = Ground_801C3FA4(gobj, 0x14);

    for (i = 0; i < 4; i++) {
        HSD_JObj* jobj = gp->gv.onettcar.car_jobjs[i];
        HSD_JObjSetTranslateX(jobj, 726.0f);
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        gp->gv.onettcar.car_items[i] =
            grMaterial_801C8CFC(0, 0, gp, gp->gv.onettcar.car_jobjs[i],
                                grOnett_801E5030, NULL, NULL);
        grMaterial_801C8E08(gp->gv.onettcar.car_items[i]);
        it_80274C60(gp->gv.onettcar.car_items[i]);
    }

    gp->gv.onettcar.curr_car = (s8) HSD_Randi(4);
    gp->gv.onettcar.next_car = 4;
    gp->gv.onettcar.curr_car = 4;
    gp->gv.onettcar.state_b = 0;
    gp->gv.onettcar.state_a = 0;
    grOt_804D69C4 = 0;

    Ground_801C10B8(gobj, grOnett_801E41B0);
    gp->gv.onettcar.x0_b0 = 1;
}

bool grOnett_801E43D8(Ground_GObj* gobj)
{
    return false;
}

void grOnett_801E43E0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    s8 saved_car = gp->gv.onettcar.curr_car;
    Vec3 pos = { 0.0f, 0.0f, 0.0f };
    f32 cam_x, cam_y, cam_z;
    PAD_STACK(32);

    if (!gp->gv.onettcar.x0_b0) {
        HSD_JObj* car_jobj;
        HSD_JObj* car_jobj2;

        Camera_800307D0(&cam_x, &cam_y, &cam_z);

        car_jobj = gp->gv.onettcar.car_jobjs[saved_car];
        car_jobj2 = gp->gv.onettcar.car_jobjs2[saved_car];

        switch (gp->gv.onettcar.state_a) {
        case 0: {
            s8 old_car = gp->gv.onettcar.curr_car;
            HSD_JObj* new_jobj;
            do {
                gp->gv.onettcar.curr_car = HSD_Randi(4);
            } while (gp->gv.onettcar.curr_car == old_car ||
                     gp->gv.onettcar.curr_car == gp->gv.onettcar.next_car);

            new_jobj = gp->gv.onettcar.car_jobjs[gp->gv.onettcar.curr_car];
            HSD_JObjSetTranslateX(new_jobj, 726.0f);
            HSD_JObjSetTranslateZ(new_jobj, 30.0f);
            HSD_JObjSetRotationY(new_jobj->child, 0.0f);
            gp->gv.onettcar.state_a = 1;
            gp->gv.onettcar.x108 = grOt_804D69C0->x44;
            Ground_801C5784(0);
            break;
        }
        case 1: {
            s32 t = gp->gv.onettcar.x108;
            if (t != 0) {
                gp->gv.onettcar.x108 = t - 1;
            } else {
                s8 car = gp->gv.onettcar.curr_car;
                gp->gv.onettcar.x108 = grOt_804D69C0->x48;
                gp->gv.onettcar.car_speed =
                    grOt_804D69C0->x58 * HSD_Randf() + grOt_804D69C0->x54;
                if (gp->gv.onettcar.car_speed > 0.0f) {
                    gp->gv.onettcar.car_speed *= -1.0f;
                }
                gp->gv.onettcar.state_a = 2;
                Item_80268E5C(gp->gv.onettcar.car_items[car], saved_car + 2,
                              ITEM_ANIM_UPDATE);
            }
            break;
        }
        case 2:
            if (gp->gv.onettcar.x108 != 0) {
                int fighter_count = 0;
                HSD_GObj* iter = HSD_GObj_Entities->fighters;
                while (iter != NULL) {
                    iter = iter->next;
                    fighter_count++;
                }
                gp->gv.onettcar.x108 -= 1;
                iter = HSD_GObj_Entities->fighters;
                while (iter != NULL) {
                    ftLib_80086644(iter, &pos);
                    if (pos.y <= 1.0f) {
                        s32 rank = gm_8016C6C0(iter);
                        if (fighter_count == 1 || rank == 0) {
                            gp->gv.onettcar.x108 = 0;
                            HSD_JObjClearFlagsAll(car_jobj, JOBJ_HIDDEN);
                            gp->gv.onettcar.state_a = 5;
                        } else if (fighter_count == rank + 1) {
                            gp->gv.onettcar.x108 = grOt_804D69C0->x50;
                            gp->gv.onettcar.state_a = 3;
                        } else {
                            gp->gv.onettcar.x108 = grOt_804D69C0->x4C;
                            gp->gv.onettcar.state_a = 3;
                        }
                        gp->gv.onettcar.x110 = 0;
                    }
                    iter = iter->next;
                }
            } else {
                gp->gv.onettcar.x108 = 0;
                gp->gv.onettcar.x110 = 0;
                HSD_JObjClearFlagsAll(car_jobj, JOBJ_HIDDEN);
                gp->gv.onettcar.state_a = 5;
                Ground_801C5784(1);
            }
            break;
        case 3: {
            s32 t = gp->gv.onettcar.x108;
            if (t != 0) {
                gp->gv.onettcar.x108 = t - 1;
            } else {
                gp->gv.onettcar.x108 = 0;
                gp->gv.onettcar.x110 = 0;
                HSD_JObjClearFlagsAll(car_jobj, JOBJ_HIDDEN);
                gp->gv.onettcar.state_a = 5;
                Ground_801C5784(1);
            }
            break;
        }
        case 4:
            HSD_JObjAddRotationY(car_jobj->child,
                                 0.017453292f * grOt_804D69C0->x5C);
            grLib_801C9808(0x2C, 0, car_jobj2);
            HSD_JObjAddTranslationX(car_jobj, gp->gv.onettcar.car_speed);
            if (HSD_JObjGetTranslationX(car_jobj) <= -642.0f) {
                HSD_JObjSetFlagsAll(car_jobj, JOBJ_HIDDEN);
                gp->gv.onettcar.state_a = 0;
                Item_80268E5C(gp->gv.onettcar.car_items[saved_car], 0,
                              ITEM_ANIM_UPDATE);
                return;
            }
            break;
        case 5:
        case 6:
            HSD_JObjAddTranslationX(car_jobj, gp->gv.onettcar.car_speed);
            switch (gp->gv.onettcar.x110) {
            case 0:
                if (HSD_JObjGetTranslationX(car_jobj) <= 580.0f) {
                    grOnett_801E5194(gp, gp->gv.onettcar.curr_car, 5);
                    un_802FD604(grOt_804D69C0->x60);
                    gp->gv.onettcar.x110 = 1;
                }
                break;
            case 1:
                if (HSD_JObjGetTranslationX(car_jobj) <=
                    cam_z + grOt_804D69C0->x64)
                {
                    HSD_GObj* fiter = HSD_GObj_Entities->fighters;
                    while (fiter != NULL) {
                        ftLib_80086644(fiter, &pos);
                        if (pos.y <= 1.0f) {
                            HSD_Randi(3);
                            grOnett_801E5140(saved_car);
                            gp->gv.onettcar.x110 = 2;
                            Ground_801C5784(2);
                            break;
                        }
                        fiter = fiter->next;
                    }
                }
                /* fallthrough */
            case 2:
                if (HSD_JObjGetTranslationX(car_jobj) <= 100.0f + cam_y) {
                    gp->gv.onettcar.x110 = 4;
                }
                break;
            case 4:
                break;
            }
            if (HSD_JObjGetTranslationX(car_jobj) <= -642.0f) {
                HSD_JObjSetFlagsAll(car_jobj, JOBJ_HIDDEN);
                gp->gv.onettcar.state_a = 0;
                Item_80268E5C(gp->gv.onettcar.car_items[saved_car], 0,
                              ITEM_ANIM_UPDATE);
                return;
            }
            break;
        }

        /* State machine B: left-to-right car */
        {
            u8 state_b = gp->gv.onettcar.state_b;
            s8 next = gp->gv.onettcar.next_car;
            HSD_JObj* b_jobj = gp->gv.onettcar.car_jobjs[next];

            switch (state_b) {
            case 0: {
                HSD_JObj* new_jobj;
                do {
                    gp->gv.onettcar.next_car = HSD_Randi(4);
                } while (gp->gv.onettcar.next_car == next ||
                         gp->gv.onettcar.next_car == gp->gv.onettcar.curr_car);

                new_jobj = gp->gv.onettcar.car_jobjs[gp->gv.onettcar.next_car];
                HSD_JObjSetTranslateX(new_jobj, -642.0f);
                HSD_JObjSetTranslateZ(new_jobj, 56.0f);
                HSD_JObjSetRotationY(new_jobj->child, M_PI);
                gp->gv.onettcar.state_b = 1;
                gp->gv.onettcar.timer_b = grOt_804D69C0->x44;
                return;
            }
            case 1: {
                s32 t = gp->gv.onettcar.timer_b;
                if (t != 0) {
                    gp->gv.onettcar.timer_b = t - 1;
                    return;
                }
                gp->gv.onettcar.timer_b = grOt_804D69C0->x48;
                gp->gv.onettcar.speed_b =
                    grOt_804D69C0->x58 * HSD_Randf() + grOt_804D69C0->x54;
                gp->gv.onettcar.state_b = 2;
                return;
            }
            case 2: {
                s32 t = gp->gv.onettcar.timer_b;
                if (t != 0) {
                    gp->gv.onettcar.timer_b = t - 1;
                    return;
                }
                gp->gv.onettcar.timer_b = 0;
                HSD_JObjClearFlagsAll(b_jobj, JOBJ_HIDDEN);
                gp->gv.onettcar.sub_state_b = 0;
                gp->gv.onettcar.state_b = 5;
                Item_80268E5C(gp->gv.onettcar.car_items[next], 0,
                              ITEM_ANIM_UPDATE);
                return;
            }
            case 5:
                HSD_JObjAddTranslationX(b_jobj, gp->gv.onettcar.speed_b);
                switch (gp->gv.onettcar.sub_state_b) {
                case 0:
                    if (HSD_JObjGetTranslationX(b_jobj) >= -513.0f) {
                        grOnett_801E5194(gp, gp->gv.onettcar.next_car, 4);
                        gp->gv.onettcar.sub_state_b = 4;
                    }
                    break;
                case 4:
                    break;
                }
                if (HSD_JObjGetTranslationX(b_jobj) >= 726.0f) {
                    HSD_JObjSetFlagsAll(b_jobj, JOBJ_HIDDEN);
                    gp->gv.onettcar.state_b = 0;
                }
                break;
            }
        }
    }
}

void grOnett_801E502C(Ground_GObj* gobj) {}

void grOnett_801E5030(Item_GObj* igobj, Ground* gp)
{
    if ((int) gp->gv.onettcar.state_a == 4) {
        s32 s = HSD_Randi(2) != 0 ? 0x5F37C : 0x5F37D;
        Ground_801C53EC(s);
    } else if (HSD_Randi(2)) {
        u32 sfx;
        f32 rand = HSD_Randf();
        gp->gv.onettcar.car_speed += 0.5f + rand;
        if (ABS(gp->gv.onettcar.car_speed) < 0.5f) {
            gp->gv.onettcar.car_speed = 0.5f;
        }
        gp->gv.onettcar.state_a = 4;
        gp->gv.onettcar.x110 = 4;
        gp->gv.onettcar.x108 = 1;
        if (HSD_Randi(2) != 0) {
            sfx = 0x5F37C;
        } else {
            sfx = 0x5F37D;
        }
        Ground_801C5544(gp, 5);
        Ground_801C53EC(sfx);
    } else {
        gp->gv.onettcar.state_a = 6;
    }
}

void grOnett_801E5140(s32 idx)
{
    u32 table[] = { 0x5F370, 0x5F370, 0x5F371, 0x5F372 };
    Ground_801C53EC(table[idx]);
}

static inline s32 grOnett_SfxLookup(s32 (*table)[2], s32 idx, s32 type)
{
    return table[idx][type - 4];
}

void grOnett_801E5194(Ground* gp, s32 car_idx, s32 sound_type)
{
    s32 sfx_table[4][2] = {
        { 0x5F377, 0x5F376 },
        { 0x5F377, 0x5F376 },
        { 0x5F379, 0x5F378 },
        { 0x5F37B, 0x5F37A },
    };
    Ground* tmp = gp;
    Ground_801C5440(tmp, sound_type,
                    grOnett_SfxLookup(sfx_table, car_idx, sound_type));
}

void grOnett_801E5214(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    int i;
    for (i = 0; i < 2; i++) {
        struct grOnett_AwningData* awn = &gp->gv.onett.awnings[i];
        f32 disp, vel, error, abs_ratio, accel, force;
        f32 max_disp;
        HSD_JObj* jobj;

        max_disp = -grOt_804D69C0->max_displacement;
        if (awn->accumulator < max_disp) {
            awn->accumulator = max_disp;
        }

        disp = awn->accumulator;
        vel = awn->velocity;
        error = disp - vel;
        accel = awn->initial + grOt_804D69C0->spring_constant;

        if (error < 0.0f) {
            abs_ratio = -error;
        } else {
            abs_ratio = error;
        }
        abs_ratio /= grOt_804D69C0->max_displacement;

        if (error < 0.0f) {
            force = -(grOt_804D69C0->spring_force * abs_ratio - accel);
        } else {
            force = grOt_804D69C0->spring_force * abs_ratio + accel;
        }

        force = (force - grOt_804D69C0->spring_constant) *
                (1.0f - grOt_804D69C0->damping);

        if (force > grOt_804D69C0->max_velocity) {
            force = grOt_804D69C0->max_velocity;
        } else if (force < -grOt_804D69C0->max_velocity) {
            force = -grOt_804D69C0->max_velocity;
        }

        if ((ABS(vel - disp) < grOt_804D69C0->pos_threshold) &&
            (ABS(force) < grOt_804D69C0->vel_threshold))
        {
            awn->velocity = disp;
            awn->initial = 0.0f;
        } else {
            awn->initial = force;
            awn->velocity += force;
            {
                f32 lim = grOt_804D69C0->max_displacement;
                if (awn->velocity > lim) {
                    awn->velocity = lim;
                } else if (awn->velocity < -lim) {
                    awn->velocity = -lim;
                }
            }
        }

        jobj = awn->jobj;
        HSD_JObjSetTranslateY(jobj, awn->velocity +
                                        (awn->initial_y + awn->accumulator));

        if (awn->cooldown == 0 &&
            (awn->counter_prev != awn->counter || awn->flag != 0))
        {
            grLib_801C9808(0x7533, 0x1E, awn->jobj);
            Ground_801C5440(gp, 0, 0x5F375);
            awn->cooldown = 0xA;
        }

        awn->accumulator = 0.0f;
        awn->counter_prev = awn->counter;
        awn->counter = 0;
        awn->flag = 0;

        if (awn->cooldown != 0) {
            awn->cooldown--;
        }
    }
}

/// Updates awning collision tracking data
void grOnett_801E54B4(Ground* gp, s32 arg1, CollData* cd, s32 arg3,
                      mpLib_GroundEnum arg4, f32 arg5)
{
    int temp = cd->x34_flags.b1234;
    int idx;

    if (temp != 1 && temp != 2 && temp != 3) {
        return;
    }

    idx = (arg1 == 0) ? 0 : 1;
    if (arg4 == 1) {
        gp->gv.onett.awnings[idx].flag = 1;
        gp->gv.onett.awnings[idx].initial = grOt_804D69C0->awning_initial;
    }

    gp->gv.onett.awnings[idx].accumulator += grOt_804D69C0->awning_delta;
    gp->gv.onett.awnings[idx].counter++;
}

void grOnett_801E5538(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (gp->gv.onett.timer-- < 0) {
        if (gp->gv.onett.gen != NULL) {
            gp->gv.onett.timer =
                rand_range(grOt_804D69C0->x24, grOt_804D69C0->x28);
            grLib_801C9834(gp->gv.onett.gen);
            gp->gv.onett.gen = NULL;
            return;
        }
        gp->gv.onett.timer =
            rand_range(grOt_804D69C0->x2C, grOt_804D69C0->x30);
        {
            HSD_JObj* jobj = Ground_801C3FA4(gobj, 6);
            if (jobj != NULL) {
                Vec3 pos;
                Vec3 rot = { 15.75f, 40.0f, 28.25f };
                lb_8000B1CC(jobj, &rot, &pos);
                gp->gv.onett.gen = grLib_801C96F8(0x7530, 0x1E, &pos);
            }
        }
    }
}

/// #grOnett_801E56FC
DynamicModelDesc* grOnett_801E56FC(void)
{
    UnkArchiveStruct* archive = grDatFiles_801C6330(0x1);
    UnkStageDat* dat;
    HSD_ASSERT(1319, archive);
    dat = archive->unk4;
    if (dat != NULL) {
        return (DynamicModelDesc*) ((char*) dat->unk8 + 0x34);
    }
    return NULL;
}

DynamicsDesc* grOnett_801E5760(enum_t arg)
{
    return false;
}

bool grOnett_801E5768(Vec3* a, int b, HSD_JObj* jobj)
{
    Vec3 vec;
    lb_8000B1CC(jobj, NULL, &vec);
    if (a->y > vec.y) {
        return true;
    } else {
        return false;
    }
}
