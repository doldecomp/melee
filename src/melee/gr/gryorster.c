#include "gryorster.h"

#include <platform.h>

#include "forward.h"

#include "ft/ftlib.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "it/it_26B1.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "mp/mplib.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

StageCallbacks grYt_803E5198[2] = {
    { grYorster_80202124, grYorster_80202150, grYorster_80202158,
      grYorster_8020215C, NULL },
    { grYorster_802021AC, grYorster_8020224C, grYorster_80202254,
      grYorster_802022A0, 0xC0000000 }
};

StageData grYt_803E51CC = {
    YORSTER,
    grYt_803E5198,
    "/GrYt.dat",
    grYorster_80201FA4,
    grYorster_80201FA0,
    grYorster_8020200C,
    grYorster_80202010,
    grYorster_80202034,
    grYorster_80202B5C,
    grYorster_80202B64,
    (1 << 0),
    NULL,
    0,
};

typedef struct YorsterParams {
    f32 x00;
    f32 x04;
    f32 x08;
    f32 x0C;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
} YorsterParams;

typedef struct grYt_804D6A20_t {
    YorsterParams* x0;
    u8 pad_04[4];
} grYt_804D6A20_t;
grYt_804D6A20_t grYt_804D6A20;

void grYorster_80201FA0(bool unused)
{
    return;
}

void grYorster_80201FA4(void)
{
    grYt_804D6A20.x0 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grYorster_8020203C(0);
    grYorster_8020203C(1);

    Ground_801C39C0();
    Ground_801C3BB4();
}

void grYorster_8020200C(void)
{
    return;
}

void grYorster_80202010(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grYorster_80202034(void)
{
    return false;
}

HSD_GObj* grYorster_8020203C(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grYt_803E5198[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 221, gobj_id);
    }

    return gobj;
}

void grYorster_80202124(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grYorster_80202150(Ground_GObj* gobj)
{
    return false;
}

void grYorster_80202158(Ground_GObj* gobj)
{
    return;
}

void grYorster_8020215C(Ground_GObj* gobj)
{
    return;
}

void grYorster_80202160(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grYorster_802022A4(gobj);
    Ground_801C2FE0(gobj);
    mpLib_80058560();
    gp->gv.yorster.xC4 = 0;
}

void grYorster_802021AC(Ground_GObj* gobj)
{
    int _[2];

    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(GET_JOBJ(gobj), gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 4);
    grAnime_801C7FF8(gobj, 23, 7, 3, 0.0f, 1.0f);
    grAnime_801C7FF8(gobj, 26, 7, 3, 0.0f, 1.0f);
    Ground_801C10B8(gobj, grYorster_80202160);
    gp->gv.yorster.xC4 = 1;
}

bool grYorster_8020224C(Ground_GObj* gobj)
{
    return false;
}

void grYorster_80202254(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (gp->gv.yorster.xC4 == 0) {
        grYorster_8020266C(gobj);
    }
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grYorster_802022A0(HSD_GObj* gobj) {}

void grYorster_802022A4(HSD_GObj* gobj)
{
    s32 joints[9] = { 0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x10, 0x11, 0x12 };
    Ground* temp_r28;
    int i;

    temp_r28 = gobj->user_data;
    for (i = 0; i < 9; i++) {
        temp_r28->gv.yorster.elements[i].x00 = (s8) i;
        temp_r28->gv.yorster.elements[i].x01 = 0;
        temp_r28->gv.yorster.elements[i].x04 = 0.0f;
        temp_r28->gv.yorster.elements[i].x08 = 0.0f;
        temp_r28->gv.yorster.elements[i].x14 = joints[i];
        temp_r28->gv.yorster.elements[i].x18 =
            Ground_801C3FA4(gobj, joints[i]);
        temp_r28->gv.yorster.elements[i].x1C = grMaterial_801C8CFC(
            0, 0, temp_r28, temp_r28->gv.yorster.elements[i].x18, NULL,
            grYorster_80202428, NULL);
        grMaterial_801C8E68(temp_r28->gv.yorster.elements[i].x1C, GA_Ground);
        mpJointSetCb2(Ground_801C32D4(temp_r28->map_id,
                                      temp_r28->gv.yorster.elements[i].x14),
                      temp_r28, grYorster_802024F0);
        grMaterial_801C8DE0(temp_r28->gv.yorster.elements[i].x1C, 0.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 0.0f, 5.0f);
        grMaterial_801C8E08(temp_r28->gv.yorster.elements[i].x1C);
        grAnime_801C7FF8(gobj, temp_r28->gv.yorster.elements[i].x14, 7, 1,
                         0.0f, 0.0f);
    }
}

void grYorster_80202428(HSD_GObj* item_gobj, Ground* gp, Vec3* pos,
                        HSD_GObj* fighter_gobj, f32 value)
{
    s32 temp;
    int i;

    if (ftLib_80086960(fighter_gobj)) {
        ftLib_80086A4C(fighter_gobj, grYt_804D6A20.x0->x14);
    }

    for (i = (s32)0; i < 9;) { // Use a for loop with manual increment
        temp = *(s32*)&gp->gv.yorster.elements[i].x1C;
        if ((u32)item_gobj == (u32)temp) { // Cast to u32 for matching
            f32 newValue = gp->gv.yorster.elements[i].x04 + value;
            gp->gv.yorster.elements[i].x04 = newValue;
            break;
        }
        i++;
    }
}

void grYorster_802024F0(Ground* gp, s32 joint_id, CollData* coll_data,
                        s32 unused, mpLib_GroundEnum ground_kind, f32 value)
{
    HSD_GObj* gobj = coll_data->x0_gobj;
    s32 env = coll_data->x34_flags.b1234;
    s32 i;
    PAD_STACK(8);

    if (1 != env && env != 2 && env != 3) {
        return;
    }

    if (env == 1 && ftLib_800873F4((0, coll_data->x0_gobj))) {
        return;
    }

    switch (env) {
    case 1: {
        Vec3 pos;

        ftLib_80086BEC(gobj, &pos);
        value = pos.y;
        if (value >= grYt_804D6A20.x0->x00) {
            ftLib_80086A4C(gobj, (f32) grYt_804D6A20.x0->x10);
        }
        break;
    }
    case 2:
    case 3:
        if (value >= grYt_804D6A20.x0->x00) {
            it_8026B718(gobj, (f32) grYt_804D6A20.x0->x10);
        }
        break;
    }

    for (i = 0; i < 9; i++) {
        if (joint_id ==
            Ground_801C32D4(gp->map_id, gp->gv.yorster.elements[i].x14))
        {
            gp->gv.yorster.elements[i].x08 += value;
            break;
        }
    }
}

void grYorster_8020266C(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    s32 i;
    PAD_STACK(8);

    for (i = 0; i < 9; i++) {
        struct grYorster_TrackElement* entry = &gp->gv.yorster.elements[i];
        s32 joint = Ground_801C32D4(gp->map_id, entry->x14);

        switch ((s8) entry->x01) {
        default: {
            s32 advance = 0;

            if (entry->x04 >= grYt_804D6A20.x0->x08) {
                s32 frames_left;
                f32 end_frame = (f32) grYt_804D6A20.x0->x1C;

                grMaterial_801C8E28(entry->x1C);
                entry->x04 -= grYt_804D6A20.x0->x08;
                if (entry->x04 >= grYt_804D6A20.x0->x0C) {
                    frames_left = 0;
                } else {
                    frames_left = (s32) (grYt_804D6A20.x0->x0C - entry->x04);
                }
                if (end_frame >= lbGetJObjEndFrame(entry->x18)) {
                    end_frame = lbGetJObjEndFrame(entry->x18);
                }
                advance = 1;
                entry->x10 = (s32) ((f32) frames_left *
                                    (end_frame / grYt_804D6A20.x0->x0C));
            } else if (entry->x08 >= grYt_804D6A20.x0->x00) {
                s32 frames_left;
                f32 end_frame = (f32) grYt_804D6A20.x0->x1C;

                grMaterial_801C8E28(entry->x1C);
                entry->x08 -= grYt_804D6A20.x0->x00;
                if (entry->x08 <= grYt_804D6A20.x0->x00) {
                    entry->x08 = grYt_804D6A20.x0->x00;
                }
                if (entry->x08 >= grYt_804D6A20.x0->x04) {
                    frames_left = 0;
                } else {
                    frames_left =
                        (s32) (10.0f * (grYt_804D6A20.x0->x04 - entry->x08));
                }
                if (end_frame >= lbGetJObjEndFrame(entry->x18)) {
                    end_frame = lbGetJObjEndFrame(entry->x18);
                }
                advance = 1;
                entry->x10 =
                    (s32) ((f32) frames_left /
                           (10.0f * grYt_804D6A20.x0->x04) * end_frame);
                entry->x08 = 0.0f;
                Ground_801C53EC(0xE);
            }
            if (advance != 0) {
                entry->x0C = grYt_804D6A20.x0->x18;
                entry->x01 = 2;
            }
            break;
        }
        case 2:
            if (entry->x0C <= 0) {
                grAnime_801C7FF8(gobj, entry->x14, 7, 0, (f32) entry->x10,
                                 1.0f);
                mpLib_80057BC0(joint);
                entry->x01 = 3;
                entry->x0C = entry->x10;
            } else {
                entry->x0C--;
            }
            break;
        case 3:
            if (entry->x0C >= 0x143) {
                Vec3 pos;
                HSD_JObjGetTranslation(entry->x18, &pos);

                if (grLib_801C9EE8(&pos, 10.0f * Ground_801C0498() - 2.0f)) {
                    grAnime_801C7FF8(gobj, entry->x14, 7, 2, 0.0f, 0.3f);
                    entry->x0C = 0;
                    entry->x01 = 4;
                } else {
                    grAnime_801C7FF8(gobj, entry->x14, 7, 1, 0.0f, 1.0f);
                    mpJointListAdd(joint);
                    grMaterial_801C8E08(entry->x1C);
                    entry->x04 = 0.0f;
                    entry->x08 = 0.0f;
                    entry->x01 = 1;
                    OSReport("*** End Frame = %d\n", entry->x0C);
                }
            } else {
                entry->x0C++;
            }
            break;
        case 4:
            if (grAnime_801C84A4(gobj, entry->x14, 7) != 0 ||
                entry->x0C >= 0x19)
            {
                Vec3 pos;

                entry->x0C = 0;
                HSD_JObjGetTranslation(entry->x18, &pos);
                if (!grLib_801C9EE8(&pos, 10.0f * Ground_801C0498() * 0.5f)) {
                    grAnime_801C7FF8(gobj, entry->x14, 7, 1, 0.0f, 1.0f);
                    mpJointListAdd(joint);
                    grMaterial_801C8E08(entry->x1C);
                    entry->x04 = 0.0f;
                    entry->x08 = 0.0f;
                    entry->x01 = 1;
                }
            } else {
                entry->x0C++;
            }
            break;
        }
        entry->x08 = 0.0f;
    }
}

DynamicsDesc* grYorster_80202B5C(enum_t unused)
{
    return NULL;
}

bool grYorster_80202B64(Vec3* a, int _, HSD_JObj* joint)
{
    return true;
}
