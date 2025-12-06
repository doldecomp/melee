#include "gr/grinishie2.h"

#include <platform.h>

#include "cm/camera.h"
#include "gm/gm_unsplit.h"
#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "gr/types.h"
#include "it/items/itkyasarin.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "mp/mplib.h"
#include "sysdolphin/baselib/gobjgxlink.h"
#include "sysdolphin/baselib/gobjproc.h"
#include "sysdolphin/baselib/random.h"

#include <baselib/jobj.h>

StageCallbacks grI2_803E4AB4[] = {
    {
        grInishie2_801FCDC8,
        grInishie2_801FCDF4,
        grInishie2_801FCDFC,
        grInishie2_801FCE00,
        0,
    },
    {
        grInishie2_801FDE8C,
        grInishie2_801FDED0,
        grInishie2_801FDED8,
        grInishie2_801FDFE4,
        0,
    },
    {
        grInishie2_801FCE04,
        grInishie2_801FCF24,
        grInishie2_801FCFCC,
        grInishie2_801FD014,
        0xC0000000,
    },
    {
        grInishie2_801FD198,
        grInishie2_801FD21C,
        grInishie2_801FD224,
        grInishie2_801FD364,
        0,
    },
    {
        grInishie2_801FD198,
        grInishie2_801FD21C,
        grInishie2_801FD224,
        grInishie2_801FD364,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        grInishie2_801FD4F0,
        grInishie2_801FD64C,
        grInishie2_801FD654,
        grInishie2_801FD740,
        0,
    },
};

typedef struct grInishie2_thing {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10[2];
    Vec3 unk14[2];
    s32 unk2C;
    Vec3 unk30[2];
} grInishie2_thing;

grInishie2_thing* grI2_804D6A00;

void grInishie2_801FCBC0(bool arg) {}

void grInishie2_801FCBC4(void)
{
    grI2_804D6A00 = Ground_801C49F8();

    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;

    grInishie2_801FCCDC(0);
    grInishie2_801FCCDC(2);

    mpLib_80057BC0(0);
    mpLib_80057BC0(0xC);
    mpLib_80057BC0(0xD);
    mpLib_80057BC0(0xE);
    mpLib_80057BC0(3);
    mpLib_80057BC0(4);
    mpLib_80057BC0(5);
    mpLib_80057BC0(6);
    mpLib_80057BC0(7);
    mpLib_80057BC0(8);
    mpLib_80057BC0(9);
    mpLib_80057BC0(0xA);
    mpLib_80057BC0(0xB);
    mpLib_80057BC0(2);

    Ground_801C39C0();
    Ground_801C3BB4();
    Camera_800311DC(1.0f);
    Camera_800311CC(4000.0f);
}

void grInishie2_801FCCAC(void) {}

void grInishie2_801FCCB0(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grInishie2_801FCCD4(void)
{
    return false;
}

HSD_GObj* grInishie2_801FCCDC(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grI2_803E4AB4[gobj_id];

    gobj = Ground_801C14D0(gobj_id);

    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);

        if (callbacks->callback3 != 0) {
            gp->x1C_callback = (HSD_GObjEvent) callbacks->callback3;
        }

        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }

        if (callbacks->callback2 != NULL) {
            HSD_GObjProc_8038FD54(gobj, callbacks->callback2, 4);
        }

    } else {
        OSReport("%s:%d: couldn’t get gobj(id=%d)\n", "grinishie2.c", 254,
                 gobj_id);
    }

    return gobj;
}

void grInishie2_801FCDC8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grInishie2_801FCDF4(Ground_GObj* gobj)
{
    return false;
}

void grInishie2_801FCDFC(Ground_GObj* gobj) {}

void grInishie2_801FCE00(Ground_GObj* gobj) {}

void grInishie2_801FCE04(Ground_GObj* arg0)
{
    HSD_JObj* temp_r27;
    HSD_JObj* temp_r28;
    HSD_JObj* temp_r29;
    HSD_JObj* temp_r30;
    HSD_JObj* temp_r31;
    Ground* gp;

    gp = arg0->user_data;
    grAnime_801C7FF8(arg0, 1, 7, 0, 0.0f, 1.0f);
    grAnime_801C7FF8(arg0, 6, 7, 1, 0.0f, 1.0f);
    grAnime_801C7FF8(arg0, 5, 7, 2, 0.0f, 1.0f);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    grInishie2_801FD018(arg0);
    grInishie2_801FD368(arg0);
    grInishie2_801FD744(arg0);
    temp_r27 = Ground_801C3FA4(arg0, 0xD);
    temp_r28 = Ground_801C3FA4(arg0, 0xA);
    temp_r29 = Ground_801C3FA4(arg0, 0xB);
    temp_r30 = Ground_801C3FA4(arg0, 8);
    temp_r31 = Ground_801C3FA4(arg0, 0xC);
    Ground_801C4E70(Ground_801C3FA4(arg0, 9), temp_r31, temp_r30, temp_r29,
                    temp_r28, temp_r27);
    gp->gv.inishie2.xC4_flags.b0 = 0;
}

bool grInishie2_801FCF24(Ground_GObj* gobj)
{
    return 0;
}

// TODO: this stage and mushroom kingdom 1 both change the music when there's
// less than 20 seconds, since this function is copy-pasted from
// grInishie1_801FCB10 then Ground_801C5A94 is probably getting a stage
// identifier of some kind
void grInishie2_801FCF2C(HSD_GObj* gobj)
{
    int time_remaining;
    s32 var_r3;

    Ground* gp = gobj->user_data;
    if (gp->gv.inishie2.xC4_flags.b0 == 0) {
        if (GetMatchTimer(&time_remaining) != 0) {
            if (time_remaining < 20) {
                s32 temp_r3 = Ground_801C5A94();
                if (temp_r3 == 0x29) {
                    var_r3 = 0x2A;
                } else if (temp_r3 == 0x2B) {
                    var_r3 = 0x2C;
                } else {
                    var_r3 = -1;
                }
                lbAudioAx_80023F28(var_r3);
                gp->gv.inishie2.xC4_flags.b0 = 1;
            }
        } else {
            gp->gv.inishie2.xC4_flags.b0 = 1;
        }
    }
}

void grInishie2_801FCFCC(Ground_GObj* arg0)
{
    grInishie2_801FD0B4(arg0);
    grInishie2_801FD3CC(arg0);
    grInishie2_801FD7A8(arg0);
    grInishie2_801FCF2C(arg0);
    lb_800115F4();
}

void grInishie2_801FD014(Ground_GObj* gobj) {}

#define test_random(val) ((val != 0) ? HSD_Randi(val) : 0)
#define sign_inline(val) ((val == 0) ? -1.0f : 1.0f)

void grInishie2_801FD018(HSD_GObj* gobj)
{
    Ground* gp;
    gp = gobj->user_data;

    gp->gv.inishie2.xC4_flags.b1 = 1;
    gp->gv.inishie2.xC4_flags.b2 = 1;
    gp->gv.inishie2.xC6 =
        grI2_804D6A00->unk0 + test_random(grI2_804D6A00->unk2);
    gp->gv.inishie2.xC8 =
        grI2_804D6A00->unk4 + test_random(grI2_804D6A00->unk6);
}

void grInishie2_801FD0B4(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;

    if (gp->gv.inishie2.xC4_flags.b1) {
        s16 timer = gp->gv.inishie2.xC6--;
        if (timer < 0) {
            HSD_GObj* new_gobj = grInishie2_801FCCDC(3);
            mpLib_80057BC0(12);
            gp->gv.inishie2.xC4_flags.b1 = 0;
            if (new_gobj != NULL) {
                Ground* new_gp = new_gobj->user_data;
                new_gp->gv.inishie22.xCC = gobj;
            }
        }
    }

    if (gp->gv.inishie2.xC4_flags.b2) {
        s16 timer = gp->gv.inishie2.xC8--;
        if (timer < 0) {
            HSD_GObj* new_gobj = grInishie2_801FCCDC(4);
            mpLib_80057BC0(13);
            gp->gv.inishie2.xC4_flags.b2 = 0;
            if (new_gobj != NULL) {
                Ground* new_gp = new_gobj->user_data;
                new_gp->gv.inishie22.xCC = gobj;
            }
        }
    }
}

void grInishie2_801FD198(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;

    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);

    gp->gv.inishie2.xC4_flags.b7 = 0;

    gp->gv.inishie2.xC8 = gp->map_id - 3;
    gp->gv.inishie2.xC6 = grI2_804D6A00->unk10[gp->gv.inishie2.xC8];
}

bool grInishie2_801FD21C(Ground_GObj* gobj)
{
    return 0;
}

void grInishie2_801FD224(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;

    if (!gp->gv.inishie2.xC4_flags.b1) {
        s16 counter = gp->gv.inishie2.xC6;
        gp->gv.inishie2.xC6 = counter - 1;

        if (counter < 0) {
            if (gp->gv.inishie2.xC8 == 0) {
                mpJointListAdd(0xC);
            } else {
                mpJointListAdd(0xD);
            }

            gp->gv.inishie2.xC4_flags.b1 = 1;
        }
    }

    Ground_801C2FE0(gobj);

    gp = gobj->user_data;
    if (grAnime_801C83D0(gobj, 0, 1)) {
        // TODO: union irregularity
        Ground* gp_2 = GET_GROUND(gp->gv.inishie22.xCC);
        if (gp->gv.inishie2.xC8 == 0) {
            gp_2->gv.inishie2.xC4_flags.b6 = 1;
            gp_2->gv.inishie2.xC6 =
                grI2_804D6A00->unk0 + test_random(grI2_804D6A00->unk2);
        } else {
            gp_2->gv.inishie2.xC4_flags.b5 = 1;
            gp_2->gv.inishie2.xC8 =
                grI2_804D6A00->unk4 + test_random(grI2_804D6A00->unk6);
        }

        Ground_801C4A08(gobj);
    }
}

void grInishie2_801FD364(Ground_GObj* gobj) {}

void grInishie2_801FD368(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    s32 rand_max;
    s32 rand_val;

    gp->gv.inishie2.xC4_flags.b3 = 1;

    rand_max = grI2_804D6A00->unkA;
    rand_val = test_random(rand_max);

    gp->gv.inishie2.xCA = grI2_804D6A00->unk8 + rand_val;
}

void grInishie2_801FD3CC(HSD_GObj* gobj)
{
    HSD_GObj* gobj_2;
    s16 counter;
    Ground* gp = gobj->user_data;

    if (gp->gv.inishie2.xC4_flags.b5) {
        counter = gp->gv.inishie2.xCA;
        gp->gv.inishie2.xCA = counter - 1;
        if (counter < 0) {
            gobj_2 = grInishie2_801FCCDC(0xF);
            gp->gv.inishie2.xC4_flags.b5 = 0;
            if (gobj_2 != NULL) {
                Ground* gp_2 = gobj_2->user_data;
                gp_2->gv.inishie22.xC8 = gobj;
            }
        }
    }
}

void grInishie2_801FD448(HSD_GObj* gobj)
{
    s32 rand_val;
    s32 rand_max;
    Ground* gp;
    Ground* gp_2;

    gp = GET_GROUND(gobj);
    gp_2 = GET_GROUND(gp->gv.inishie22.xC8);

    gp_2->gv.inishie2.xC4_flags.b3 = 1; // Set bit 4 (0x10)

    rand_max = grI2_804D6A00->unkA;
    rand_val = test_random(rand_max);

    gp_2->gv.inishie2.xCA = (s16) (grI2_804D6A00->unk8 + rand_val);

    Ground_801C4A08(gobj);
}

void grInishie2_801FD4CC(HSD_GObj* gobj)
{
    mpLib_80057BC0(0xE);
}

// probably chooses which side to spawn Birdo on
void grInishie2_801FD4F0(Ground_GObj* gobj)
{
    Vec3 vec;
    s32 spawn_side;
    HSD_JObj* temp_r28;
    HSD_JObj* temp_r29;
    void* temp_r30;
    void* temp_r3;
    Ground* gp;

    temp_r29 = GET_JOBJ(gobj);
    gp = GET_GROUND(gobj);
    temp_r28 = temp_r29;
    spawn_side = HSD_Randi(2);
    mpJointListAdd(0xE);
    if (spawn_side == 0) {
        vec.x = grI2_804D6A00->unk14[spawn_side].x +
                Stage_GetBlastZoneRightOffset();
    } else {
        vec.x = grI2_804D6A00->unk14[spawn_side].x +
                Stage_GetBlastZoneLeftOffset();
    }
    vec.y = grI2_804D6A00->unk14[spawn_side].y;
    vec.z = grI2_804D6A00->unk14[spawn_side].z;
    HSD_JObjSetTranslate(temp_r29, &vec);
    gp->gv.inishie22.xC4 = it_802ECD3C(gobj, &vec, sign_inline(spawn_side));
    Ground_801C2ED0(temp_r28, gp->map_id);
}

bool grInishie2_801FD64C(Ground_GObj* gobj)
{
    return 0;
}

void grInishie2_801FD654(Ground_GObj* arg0)
{
    Vec3 vec;
    Ground* gp;
    Item_GObj* birdo_gobj;
    HSD_JObj* temp_r31;
    temp_r31 = arg0->hsd_obj;
    gp = GET_GROUND(arg0);
    birdo_gobj = gp->gv.inishie22.xC4;
    if (birdo_gobj != 0U) {
        it_802ECD1C(birdo_gobj, &vec);
        vec.x += grI2_804D6A00->unk14[1].x;
        HSD_JObjSetTranslate(temp_r31, &vec);
    }
    Ground_801C2FE0(arg0);
}

void grInishie2_801FD740(Ground_GObj* gobj) {}

void grInishie2_801FD744(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    s32 rand_max;
    s32 rand_val;

    gp->gv.inishie2.xC4_flags.b3 = 1;

    rand_max = grI2_804D6A00->unkE;
    rand_val = test_random(rand_max);

    gp->gv.inishie2.xCC = grI2_804D6A00->unkC + rand_val;
}

void grInishie2_801FD7A8(HSD_GObj* gobj)
{
    Ground* gp;
    HSD_GObj* gobj_2;
    s16 counter;

    gp = GET_GROUND(gobj);

    if (gp->gv.inishie2.xC4_flags.b4) {
        counter = gp->gv.inishie2.xCC;
        gp->gv.inishie2.xCC = counter - 1;

        if (counter < 0) {
            gobj_2 = grInishie2_801FCCDC(1);
            gp->gv.inishie2.xC4_flags.b4 = 0;

            if (gobj_2 != NULL) {
                GET_GROUND(gobj_2)->gv.inishie22.xC4 = gobj;
            }
        }
    }
}

void grInishie2_801FD824(HSD_GObj* gobj)
{
    Vec3 spawn_pos;
    s32 spawn_side;
    HSD_JObj* jobj;
    Ground* gp;

    gp = gobj->user_data;
    spawn_side = HSD_Randi(2);

    mpJointListAdd(0);

    if (spawn_side == 0) {
        spawn_pos.x = grI2_804D6A00->unk30[spawn_side].x +
                      Stage_GetBlastZoneRightOffset();
    } else {
        spawn_pos.x = grI2_804D6A00->unk30[spawn_side].x +
                      Stage_GetBlastZoneLeftOffset();
    }

    spawn_pos.y = grI2_804D6A00->unk30[spawn_side].y;
    spawn_pos.z = grI2_804D6A00->unk30[spawn_side].z;

    if (spawn_side == 0) {
        gp->gv.inishie23.xC8_flags.b4 = 1;
    } else {
        gp->gv.inishie23.xC8_flags.b4 = 0;
    }

    grAnime_801C8138(gobj, gp->map_id, gp->gv.inishie23.xC8_flags.b4);

    gp->gv.inishie23.xC8_flags.b6 = 1;
    gp->gv.inishie23.xC8_flags.b7 = 0;
    gp->gv.inishie23.xC8_flags.b5 = 0;

    gp->gv.inishie2.xCA = 0;
    gp->gv.inishie2.xD8 = spawn_pos;

    jobj = Ground_801C3FA4(gobj, 0);
    HSD_JObjSetTranslate(jobj, &spawn_pos);
}

void grInishie2_801FD9EC(HSD_GObj* gobj)
{
    Ground* gp;
    u8 temp_u8;
    s32 var_r0;
    s32 var_r3;
    s32 var_r3_2;
    s16 temp_r0;
    HSD_JObj* jobj;
    Vec3* temp_vec;

    gp = gobj->user_data;

    if (grAnime_801C83D0(gobj, 1, 1) != 0) {
        if (gp->gv.inishie23.xC8_flags.b6) {
            f32 temp_f = gp->gv.inishie23.xD8.x + gp->gv.inishie23.xCC.x;

            if (temp_f > Stage_GetCamBoundsRightOffset()) {
                var_r0 = 2;
            } else if (temp_f < Stage_GetCamBoundsLeftOffset()) {
                var_r0 = 1;
            } else {
                var_r0 = 0;
            }

            if (var_r0 == 0) {
                gp->gv.inishie23.xC8_flags.b6 = 0;
            }

        } else {
            if (!gp->gv.inishie23.xC8_flags.b5) {
                if ((s16) gp->gv.inishie23.xCA < 2) {
                    gp->gv.inishie23.xC8_flags.b4 ^= 1;
                } else {
                    f32 temp_f =
                        gp->gv.inishie23.xD8.x + gp->gv.inishie23.xCC.x;

                    if (temp_f > Stage_GetCamBoundsRightOffset()) {
                        var_r3 = 2;
                    } else if (temp_f < Stage_GetCamBoundsLeftOffset()) {
                        var_r3 = 1;
                    } else {
                        var_r3 = 0;
                    }

                    if (var_r3 != 0) {
                        gp->gv.inishie23.xC8_flags.b5 = 1;
                        gp->gv.inishie23.xC8_flags.b4 = (var_r3 == 2);
                        gp->gv.inishie23.xC8_flags.b7 = 1;
                    } else {
                        temp_r0 = grI2_804D6A00->unk30[1].y +
                                  grI2_804D6A00->unk30[1].z;

                        var_r3_2 = test_random(temp_r0);

                        if (var_r3_2 >= (s16) grI2_804D6A00->unk30[1].x) {
                            gp->gv.inishie23.xC8_flags.b4 ^= 1;
                        }
                    }
                }
            }
            gp->gv.inishie23.xCA += 1;
        }

        grAnime_801C8138(gobj, gp->map_id, gp->gv.inishie23.xC8_flags.b4);

        jobj = Ground_801C3FA4(gobj, 0);
        HSD_JObjSetTranslate(jobj, &gp->gv.inishie23.xCC);
        HSD_JObjAddTranslationX(jobj, gp->gv.inishie23.xCC.x);
        HSD_JObjAddTranslationX(jobj, gp->gv.inishie23.xCC.y);
        HSD_JObjAddTranslationX(jobj, gp->gv.inishie23.xCC.z);
        HSD_JObjGetTranslation(jobj, &gp->gv.inishie23.xCC);

        return;
    }

    gp = gobj->user_data;
    jobj = Ground_801C3FA4(gobj, 1);
    HSD_JObjGetTranslation(jobj, &gp->gv.inishie23.xCC);
}

void grInishie2_801FDE8C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    grInishie2_801FD824(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
}

bool grInishie2_801FDED0(Ground_GObj* gobj)
{
    return 0;
}

void grInishie2_801FDED8(Ground_GObj* gobj)
{
    Vec3 sp1C;
    s32 var_r0;
    Ground* gp;
    void* temp_r4;
    Ground* parent_gp;

    Ground_801C2FE0(gobj);
    grInishie2_801FD9EC(gobj);

    gp = gobj->user_data;

    lb_8000B1CC(Ground_801C3FA4(gobj, 0), NULL, &sp1C);

    if (sp1C.x > Stage_GetBlastZoneRightOffset()) {
        var_r0 = 1;
    } else if (sp1C.x < Stage_GetBlastZoneLeftOffset()) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    // TODO: union irregularity
    if ((var_r0 != 0) && gp->gv.inishie23.xC8_flags.b0) {
        HSD_GObj* gobj_2 = gp->gv.inishie22.xC4;
        Ground* gp_2 = GET_GROUND(gobj_2);
        gp_2->gv.inishie2.xC4_flags.b4 = 1;
        gp_2->gv.inishie2.xCC =
            (s16) (grI2_804D6A00->unkC +
                   grInishie2_801FDFB4(grI2_804D6A00->unkE));
        Ground_801C4A08(gobj);
    }
}

s32 grInishie2_801FDFB4(s32 arg0)
{
    if (arg0 != 0) {
        return HSD_Randi(arg0);
    }
    return 0;
}

void grInishie2_801FDFE4(Ground_GObj* gobj) {}

DynamicsDesc* grInishie2_801FDFE8(enum_t arg)
{
    return 0;
}

bool grInishie2_801FDFF0(Vec3* arg, int arg0, HSD_JObj* jobj)
{
    return 1;
}
