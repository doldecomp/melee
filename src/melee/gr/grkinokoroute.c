#include "grkinokoroute.h"

#include "ground.h"

#include <platform.h>

#include "cm/camera.h"
#include "ef/efsync.h"
#include "ft/ftdevice.h"
#include "ft/ftlib.h"
#include "gm/gm_1601.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "it/it_26B1.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbvector.h"
#include "mp/mplib.h"

#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/psstructs.h>
#include <baselib/random.h>

static struct {
    int x0;
    grZakoGenerator_SpawnDesc x4;
}* grNKr_804D6A50;

typedef struct grNKr_Depths {
    s16 x[51];
} grNKr_Depths;

static const Vec3 grNKr_803B82E8 = { 0.0f, 0.0f, 0.0f };

static const grNKr_Depths grNKr_803B82F4 = {
    {
        1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,
        18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
        35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
    },
};

StageCallbacks grNKr_803E57F0[4] = {
    { grKinokoRoute_80207634, grKinokoRoute_802078E8, grKinokoRoute_802078F0,
      grKinokoRoute_80207A94, 0 },
    { grKinokoRoute_80207ADC, grKinokoRoute_80207B20, grKinokoRoute_80207B28,
      grKinokoRoute_80207B2C, 0 },
    { grKinokoRoute_80207A98, grKinokoRoute_80207ACC, grKinokoRoute_80207AD4,
      grKinokoRoute_80207AD8, 0 },
    { grKinokoRoute_80207B5C, grKinokoRoute_80207C80, grKinokoRoute_80207C88,
      grKinokoRoute_80208368, 0xC0000000 },
};

static char grNKr_803E5840[] = "/GrNKr.dat";

StageData grNKr_803E584C = {
    KINOKOROUTE,
    grNKr_803E57F0,
    grNKr_803E5840,
    grKinokoRoute_80207420,
    (void (*)(int)) grKinokoRoute_8020741C,
    grKinokoRoute_80207490,
    grKinokoRoute_802074D8,
    grKinokoRoute_80207544,
    grKinokoRoute_80208754,
    grKinokoRoute_8020875C,
    0,
    NULL,
    0,
};

void grKinokoRoute_8020741C(bool arg) {}

void grKinokoRoute_80207420(void)
{
    grNKr_804D6A50 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grKinokoRoute_8020754C(2);
    grKinokoRoute_8020754C(0);
    grKinokoRoute_8020754C(1);
    grKinokoRoute_8020754C(3);
}

void grKinokoRoute_80207490(void)
{
    Vec3 pos;
    HSD_GObj* gobj = Ground_801C57A4();
    if (gobj != NULL) {
        ftLib_80086644(gobj, &pos);
        Ground_801C38BC(pos.x, 20.0f + pos.y);
        Camera_8002F3AC();
    }
}

void grKinokoRoute_802074D8(void)
{
    int val;
    grZakoGenerator_801CAE04(&grNKr_804D6A50->x4);
    val = grNKr_804D6A50->x0;
    if (val != 0) {
        val = HSD_Randi(grNKr_804D6A50->x0);
    } else {
        val = 0;
    }
    if (val == 0) {
        grZakoGenerator_801CAEB0(Ground_801C5840(), Ground_801C5940());
    }
    grZakoGenerator_801CADE0();
}

bool grKinokoRoute_80207544(void)
{
    return false;
}

HSD_GObj* grKinokoRoute_8020754C(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grNKr_803E57F0[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 249, gobj_id);
    }

    return gobj;
}

void grKinokoRoute_80207634(Ground_GObj* gobj)
{
    Vec3 origin;
    Vec3 cam_offset;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj;

    jobj = Ground_801C2CF4(0x94);
    if (jobj != NULL) {
        HSD_JObjGetTranslation(jobj, &origin);

        gp->gv.kinokoroute.entries[0].jobj = Ground_801C2CF4(0x7F);
        if (gp->gv.kinokoroute.entries[0].jobj != NULL) {
            HSD_JObjGetTranslation(gp->gv.kinokoroute.entries[0].jobj,
                                   &gp->gv.kinokoroute.entries[0].pos);
            lbVector_Sub(&gp->gv.kinokoroute.entries[0].pos, &origin);
        }

        gp->gv.kinokoroute.entries[1].jobj = Ground_801C2CF4(0x80);
        if (gp->gv.kinokoroute.entries[1].jobj != NULL) {
            HSD_JObjGetTranslation(gp->gv.kinokoroute.entries[1].jobj,
                                   &gp->gv.kinokoroute.entries[1].pos);
            lbVector_Sub(&gp->gv.kinokoroute.entries[1].pos, &origin);
        }

        gp->gv.kinokoroute.entries[2].jobj = Ground_801C2CF4(0x81);
        if (gp->gv.kinokoroute.entries[2].jobj != NULL) {
            HSD_JObjGetTranslation(gp->gv.kinokoroute.entries[2].jobj,
                                   &gp->gv.kinokoroute.entries[2].pos);
            lbVector_Sub(&gp->gv.kinokoroute.entries[2].pos, &origin);
        }

        gp->gv.kinokoroute.entries[3].jobj = Ground_801C2CF4(0x82);
        if (gp->gv.kinokoroute.entries[3].jobj != NULL) {
            HSD_JObjGetTranslation(gp->gv.kinokoroute.entries[3].jobj,
                                   &gp->gv.kinokoroute.entries[3].pos);
            lbVector_Sub(&gp->gv.kinokoroute.entries[3].pos, &origin);
        }
    } else {
        gp->gv.kinokoroute.entries[0].jobj = NULL;
        gp->gv.kinokoroute.entries[1].jobj = NULL;
        gp->gv.kinokoroute.entries[2].jobj = NULL;
        gp->gv.kinokoroute.entries[3].jobj = NULL;
    }

    Ground_801C39C0();
    Ground_801C3BB4();
    Stage_UnkSetVec3TCam_Offset(&cam_offset);
    Ground_801C3880(1.5f * (Stage_GetCamBoundsTopOffset() - cam_offset.y));
    Ground_801C3890(1.5f * (Stage_GetCamBoundsBottomOffset() - cam_offset.y));
    Ground_801C38A0(1.5f * (Stage_GetCamBoundsLeftOffset() - cam_offset.x));
    Ground_801C38AC(1.5f * (Stage_GetCamBoundsRightOffset() - cam_offset.x));
}

bool grKinokoRoute_802078E8(Ground_GObj* arg)
{
    return false;
}

void grKinokoRoute_802078F0(Ground_GObj* gobj)
{
    struct grKinokoRoute_GroundVars_Entry* entry;
    Vec3 pos;
    Ground* gp = GET_GROUND(gobj);
    HSD_GObj* fighter = Ground_801C57A4();
    f32 scale;
    s32 i;

    if (fighter == NULL) {
        return;
    }

    ftLib_80086644(fighter, &pos);
    scale = Ground_801C0498();
    if (scale > 0.0001f) {
        scale = 1.0f / scale;
    } else {
        scale = 1.0f;
    }

    entry = &gp->gv.kinokoroute.entries[0];
    for (i = 0; i < 4; i++, entry++) {
        if (entry->jobj != NULL) {
            HSD_JObjSetTranslateX(entry->jobj, scale * (entry->pos.x + pos.x));
            HSD_JObjSetTranslateY(entry->jobj, scale * (entry->pos.y + pos.y));
        }
    }
}

void grKinokoRoute_80207A94(Ground_GObj* arg) {}

void grKinokoRoute_80207A98(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
    Ground_801C39C0();
    Ground_801C3BB4();
}

bool grKinokoRoute_80207ACC(Ground_GObj* arg)
{
    return false;
}

void grKinokoRoute_80207AD4(Ground_GObj* arg) {}

void grKinokoRoute_80207AD8(Ground_GObj* arg) {}

void grKinokoRoute_80207ADC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

bool grKinokoRoute_80207B20(Ground_GObj* arg)
{
    return false;
}

void grKinokoRoute_80207B28(Ground_GObj* arg) {}

void grKinokoRoute_80207B2C(Ground_GObj* arg) {}

void grKinokoRoute_80207B30(HSD_GObj* gobj)
{
    ftCo_800C07F8(gobj, 6, grKinokoRoute_80208660);
}

void grKinokoRoute_80207B5C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* reb0_jobj;

    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    gp->x10_flags.b2 = 1;
    gp->gv.kinokoroute2.phase = 0;
    gp->gv.kinokoroute2.zone_idx = 0;
    gp->gv.kinokoroute2.cam_timer = 0;
    gp->gv.kinokoroute2.spawn_idx = -1;
    Ground_801C10B8(gobj, grKinokoRoute_80207B30);
    grKinokoRoute_80208564(gobj);
    gp->gv.kinokoroute2.flags |= 0x80;
    reb0_jobj = Ground_801C2CF4(4);
    HSD_ASSERT(467, reb0_jobj);
    HSD_JObjGetTranslation(reb0_jobj, &gp->gv.kinokoroute2.reb0_pos);
}

bool grKinokoRoute_80207C80(Ground_GObj* arg)
{
    return false;
}

void grKinokoRoute_80207C88(Ground_GObj* gobj)
{
    Vec3 fighter_pos = grNKr_803B82E8;
    Vec3 cam_target;
    Vec3 cam_offset;
    Vec3 point;
    Vec3 diff;
    Vec3 translate;
    f32 scale;
    Ground* gp = GET_GROUND(gobj);
    HSD_GObj* fighter;
    HSD_GObj* ground_gobj;
    HSD_JObj* jobj;

    scale = Ground_801C0498();
    fighter = Ground_801C57A4();
    if (fighter == NULL) {
        return;
    }

    ftLib_80086644(fighter, &fighter_pos);
    if (gp->gv.kinokoroute2.phase != 2) {
        if (ftLib_80086EC0(fighter)) {
            Stage_UnkSetVec3TCam_Offset(&cam_target);
            gp->gv.kinokoroute2.cam_timer = 0x3C;
        } else if (ftLib_8008732C(fighter)) {
            Stage_UnkSetVec3TCam_Offset(&cam_target);
            gp->gv.kinokoroute2.cam_timer = 0;
        } else {
            if (fighter_pos.y < 20.0f * scale) {
                fighter_pos.y = 20.0f * scale;
            } else if (fighter_pos.y > 250.0f * scale) {
                fighter_pos.y = 250.0f * scale;
            }
            if (gp->gv.kinokoroute2.spawn_idx != -1) {
                Ground_801C2D24(gp->gv.kinokoroute2.spawn_idx, &point);
                if (fighter_pos.x < point.x) {
                    fighter_pos.x = point.x;
                }
            } else {
                Ground_801C2D24(0, &point);
                if (fighter_pos.x < point.x) {
                    fighter_pos.x = point.x;
                }
                Ground_801C2D24(0xBD, &point);
                if (fighter_pos.x > point.x) {
                    fighter_pos.x = point.x;
                }
            }
            cam_target = fighter_pos;
            Camera_80030AE0(true);
        }
        Ground_801C3D44(NULL, 30.0f, 10000.0f);
        if (gp->gv.kinokoroute2.phase < 2) {
            gp->gv.kinokoroute2.spawn_idx =
                Ground_801C3DB4(NULL, 60.0f, 10000.0f);
            if (gp->gv.kinokoroute2.spawn_idx != -1) {
                gp->gv.kinokoroute2.phase = 2;
                gp->gv.kinokoroute2.cam_timer = 0x3C;
                Ground_801C5750();
                gm_801674C4(0x11, 0xA, 3, 0xB3, grKinokoRoute_80208480);
                gp->gv.kinokoroute2.zone_idx = 2;
                ground_gobj = Ground_801C2BA4(0);
                if (ground_gobj != NULL) {
                    Ground_801C4A08(ground_gobj);
                }
                ground_gobj = Ground_801C2BA4(2);
                if (ground_gobj != NULL) {
                    Ground_801C4A08(ground_gobj);
                }
                grKinokoRoute_8020754C(0);
                grKinokoRoute_8020754C(2);
                Ground_801C38BC(cam_target.x, cam_target.y);
                grZakoGenerator_801CAF08();
                gp->gv.kinokoroute2.cam_timer = 0x3C;
            }
        }
        if (gp->gv.kinokoroute2.zone_idx + 5 < 7 &&
            Ground_801C2D24(gp->gv.kinokoroute2.zone_idx + 5, &point) &&
            fighter_pos.x > point.x)
        {
            gp->gv.kinokoroute2.zone_idx += 1;
        }
        stage_info.x6DC = gp->gv.kinokoroute2.zone_idx;
    } else {
        Ground_801C2D24(gp->gv.kinokoroute2.spawn_idx, &fighter_pos);
        fighter_pos.y += 30.0f;
        cam_target = fighter_pos;
        Camera_80030AE0(false);
        stage_info.x6DC = 0;
        jobj = Ground_801C2CF4(4);
        if (jobj == NULL || Ground_801C2CF4(0xBD) == NULL) {
            HSD_ASSERT(617, jobj != NULL && Ground_801C2CF4(0xBD) != NULL);
        }
        HSD_JObjGetTranslation(Ground_801C2CF4(0xBD), &translate);
        translate.y += 50.0f;
        HSD_JObjSetTranslate(jobj, &translate);
        if (gp->gv.kinokoroute2.cam_timer == 0) {
            grKinokoRoute_8020836C(gobj, 0);
        }
        if (Ground_801C5764() == 1) {
            gp->gv.kinokoroute2.phase = 3;
            gp->gv.kinokoroute2.cam_timer = 0x3C;
            grKinokoRoute_8020836C(gobj, 1);
            grZakoGenerator_801CAEF0(true);
            jobj = Ground_801C2CF4(4);
            HSD_ASSERT(654, jobj != NULL);
            HSD_JObjSetTranslate(jobj, &gp->gv.kinokoroute2.reb0_pos);
            ground_gobj = Ground_801C2BA4(0);
            if (ground_gobj != NULL) {
                Ground_801C4A08(ground_gobj);
            }
            ground_gobj = Ground_801C2BA4(2);
            if (ground_gobj != NULL) {
                Ground_801C4A08(ground_gobj);
            }
            grKinokoRoute_8020754C(2);
            grKinokoRoute_8020754C(0);
            Ground_801C38BC(cam_target.x, cam_target.y);
        }
    }

    Stage_UnkSetVec3TCam_Offset(&cam_offset);
    if (gp->gv.kinokoroute2.cam_timer == 0) {
        lbVector_Diff(&cam_offset, &cam_target, &diff);
        if (lbVector_Normalize(&diff) > 10.0f) {
            diff.x *= 10.0f;
            diff.y *= 10.0f;
            diff.z *= 10.0f;
            Ground_801C38BC(cam_target.x + diff.x, cam_target.y + diff.y);
        }
    } else {
        f32 step = 1.0f / gp->gv.kinokoroute2.cam_timer;
        lbVector_Sub(&cam_target, &cam_offset);
        cam_target.x *= step;
        cam_target.y *= step;
        cam_target.z *= step;
        lbVector_Add(&cam_offset, &cam_target);
        Ground_801C38BC(cam_offset.x, cam_offset.y);
        gp->gv.kinokoroute2.cam_timer -= 1;
    }

    lb_800115F4();
    Ground_801C2FE0(gobj);
    if (gp->gv.kinokoroute2.flags & 0x80) {
        mpLib_80058560();
        gp->gv.kinokoroute2.flags &= ~0x80;
    }
}

void grKinokoRoute_80208368(Ground_GObj* arg) {}

void grKinokoRoute_8020836C(HSD_GObj* gobj, s32 arg1)
{
    HSD_GObj* item;
    HSD_JObj* jobj = Ground_801C3FA4(gobj, 0x53);

    PAD_STACK(16);

    if (jobj == NULL) {
        return;
    }

    if (arg1 != 0) {
        HSD_JObjClearFlagsAll(jobj, 0x10);
        mpJointListAdd(0x3C);
        mpJointListAdd(0x33);
        item = HSD_GObj_Entities->items;
        while (item != NULL) {
            if (itGetKind((Item_GObj*) item) == 0xA0) {
                grMaterial_801C8E08((Item_GObj*) item);
            }
            item = item->next;
        }
        mpJointListAdd(0xC);
        mpJointListAdd(0xD);
        mpJointListAdd(0xE);
        mpJointListAdd(0xF);
        return;
    }

    HSD_JObjSetFlagsAll(jobj, 0x10);
    mpLib_80057BC0(0x3C);
    mpLib_80057BC0(0x33);
    item = HSD_GObj_Entities->items;
    while (item != NULL) {
        if (itGetKind((Item_GObj*) item) == 0xA0) {
            grMaterial_801C8E28(item);
        }
        item = item->next;
    }
    mpLib_80057BC0(0xC);
    mpLib_80057BC0(0xD);
    mpLib_80057BC0(0xE);
    mpLib_80057BC0(0xF);
}

bool grKinokoRoute_80208480(s32 arg)
{
    if (arg == 1) {
        Ground_801C5740(arg);
        return 1;
    }
    return 0;
}

void grKinokoRoute_802084B4(HSD_GObj* gobj)
{
    HSD_GObj* gobj2;
    Vec3 sp_vec;
    struct {
        char pad[0xDD8];
        HSD_JObj* jobj;
    }* gp = gobj->user_data;

    HSD_JObjSetFlagsAll(gp->jobj, 0x10);

    gobj2 = Ground_801C2BA4(3);
    if (gobj2 != NULL) {
        void* gp2 = gobj2->user_data;
        if (gp2 != NULL) {
            ((UnkFlagStruct*) ((u8*) gp2 + 0xC4))->b0 = 1;
        }
    }

    lb_8000B1CC(gp->jobj, NULL, &sp_vec);
    efSync_Spawn(0x442, gobj, &sp_vec);
    Camera_80030E44(2, NULL);
    Ground_801C5414(0x136, 0xBA);
    grMaterial_801C8CDC(gobj);
    PAD_STACK(20);
}

void grKinokoRoute_80208564(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    u32 i;
    grNKr_Depths depths = grNKr_803B82F4;

    for (i = 0; i < 0x33U; i++) {
        HSD_JObj* jobj = Ground_801C3FA4(gobj, depths.x[i]);
        Item_GObj* item = grMaterial_801C8CFC(
            8, 0, gp, jobj, NULL,
            (void (*)(Item_GObj*, Ground*, Vec3*, HSD_GObj*,
                      f32)) grKinokoRoute_802084B4,
            NULL);
        if (item != NULL) {
            grMaterial_801C8DE0(item, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
                                7.0F);
            grMaterial_801C8E08(item);
            grMaterial_801C8E68(item, GA_Ground);
        }
    }
}

bool grKinokoRoute_80208660(s32 arg0, HSD_GObj* gobj)
{
    Vec3 pos;
    Vec3 vel;

    ftLib_80086644(gobj, &pos);
    ftLib_80086684(gobj, &vel);

    if (pos.y < 5.5F && vel.y > 5.5F) {
        f32 scale = ftLib_80086B80(gobj) / 10.0F;
        pos.y = 5.5F;
        grKinokoRoute_802086EC(&pos, scale);
        Ground_801C53EC(0x77A10);
    }

    PAD_STACK(8);
    return false;
}

void grKinokoRoute_802086EC(Vec3* arg0, f32 arg8)
{
    HSD_Generator* gen = grLib_801C96F8(0x7530, 0x1E, arg0);
    if (gen != NULL) {
        HSD_psAppSRT* srt = gen->appsrt;
        srt->scale.x *= arg8;
        srt->scale.y *= arg8;
        srt->scale.z *= arg8;
    }
}

DynamicsDesc* grKinokoRoute_80208754(enum_t arg)
{
    return false;
}

bool grKinokoRoute_8020875C(Vec3* a, int b, HSD_JObj* jobj)
{
    Vec3 vec;
    lb_8000B1CC(jobj, NULL, &vec);
    if (a->y > vec.y) {
        return true;
    } else {
        return false;
    }
}
