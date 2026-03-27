#include "grcastle.h"

#include "placeholder.h"
#include "types.h"

#include "cm/camera.h"
#include "ft/ftdevice.h"
#include "ft/ftlib.h"
#include "gr/grdisplay.h"
#include "gr/granime.h"
#include "gr/grdatfiles.h"
#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "it/it_26B1.h"
#include "it/it_266F.h"
#include "it/it_2725.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbvector.h"
#include "lb/types.h"
#include "mp/mplib.h"

#include <dolphin/mtx.h>
#include <baselib/archive.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/psstructs.h>
#include <baselib/random.h>
#include <baselib/spline.h>
#include <MSL/trigf.h>

const unkCastleCallback grCs_803B7F28[5] = {
    grCastle_801D0550, grCastle_801D059C, grCastle_801D05E8,
    grCastle_801D0634, grCastle_801D0680,
};

const unkCastleCallback2 grCs_803B7F3C[5] = {
    grCastle_801D06CC, grCastle_801D0744, grCastle_801D07BC,
    grCastle_801D0834, grCastle_801D08AC,
};

S16Vec3 grCs_803E0FE8[] = {
    { 4, 6, 1 },
    { 5, 6, 4 },
};

StageCallbacks grCs_803E0FF4[21] = {
    { NULL, NULL, NULL, NULL, 0 },
    { grCastle_801CE8E8, grCastle_801CE9E0, grCastle_801CE9E8,
      grCastle_801CEAC8, 0 },
    { grCastle_801CE7E8, grCastle_801CE858, grCastle_801CE860,
      grCastle_801CE8E4, 0 },
    { grCastle_801CD658, grCastle_801CD8A0, grCastle_801CD8A8,
      grCastle_801CD960, 0 },
    { grCastle_801CD5BC, grCastle_801CD600, grCastle_801CD608,
      grCastle_801CD60C, 0 },
    { grCastle_801CEACC, grCastle_801CEEFC, grCastle_801CEF04,
      grCastle_801CF0F0, 0 },
    { grCastle_801CDA0C, grCastle_801CDC3C, grCastle_801CDC44,
      grCastle_801CDF50, 0 },
    { grCastle_801CEACC, grCastle_801CEEFC, grCastle_801CEF04,
      grCastle_801CF0F0, 0 },
    { grCastle_801CE260, grCastle_801CE3A4, grCastle_801CE578,
      grCastle_801CE7E4, 0 },
    { grCastle_801CE260, grCastle_801CE3A4, grCastle_801CE578,
      grCastle_801CE7E4, 0 },
    { grCastle_801CE260, grCastle_801CE3A4, grCastle_801CE578,
      grCastle_801CE7E4, 0 },
    { grCastle_801CE260, grCastle_801CE3A4, grCastle_801CE578,
      grCastle_801CE7E4, 0 },
    { grCastle_801CE260, grCastle_801CE3A4, grCastle_801CE578,
      grCastle_801CE7E4, 0 },
    { grCastle_801CE260, grCastle_801CE3A4, grCastle_801CE578,
      grCastle_801CE7E4, 0 },
    { grCastle_801CE260, grCastle_801CE3A4, grCastle_801CE578,
      grCastle_801CE7E4, 0 },
    { grCastle_801CE260, grCastle_801CE3A4, grCastle_801CE578,
      grCastle_801CE7E4, 0 },
    { grCastle_801CE260, grCastle_801CE3A4, grCastle_801CE578,
      grCastle_801CE7E4, 0 },
    { grCastle_801CEACC, grCastle_801CEEFC, grCastle_801CEF04,
      grCastle_801CF0F0, 0 },
    { grCastle_801CF0F4, grCastle_801CF300, grCastle_801CF308,
      grCastle_801CF74C, 0 },
    { grCastle_801CF0F4, grCastle_801CF300, grCastle_801CF308,
      grCastle_801CF74C, 0 },
    { grCastle_801CF0F4, grCastle_801CF300, grCastle_801CF308,
      grCastle_801CF74C, 0 },
};

StageData grCs_803E11A4 = {
    CASTLE,
    grCs_803E0FF4,
    "/GrCs.dat",
    grCastle_801CD37C,
    grCastle_801CD338,
    grCastle_801CD4A0,
    grCastle_801CD4A4,
    grCastle_801CD4C8,
    grCastle_801D0B04,
    grCastle_801D0B0C,
    (1 << 0),
    grCs_803E0FE8,
    2,
};

typedef struct grCastleParams {
    /* 0x000 */ s16 x0;
    /* 0x002 */ s16 x2;
    /* 0x004 */ s16 x4;
    /* 0x006 */ s16 x6;
    /* 0x008 */ s16 x8;
    /* 0x00A */ s16 xA;
    /* 0x00C */ s32 xC;
    /* 0x010 */ f32 x10;
    /* 0x014 */ f32 x14;
    /* 0x018 */ u8 pad_x18[8];
    /* 0x020 */ f32 x20;
    /* 0x024 */ f32 x24;
    /* 0x028 */ f32 x28;
    /* 0x02C */ f32 x2C;
    /* 0x030 */ f32 x30;
    /* 0x034 */ f32 x34;
    /* 0x038 */ f32 x38;
    /* 0x03C */ f32 x3C;
    /* 0x040 */ u8 pad_x40[0x12C - 0x40];
    /* 0x12C */ s16 x12C[]; // TODO: How big is this array?
} grCastleParams;

typedef struct grCastle_PlatSubObj {
    /* 0x00 */ HSD_JObj* jobj;
    /* 0x04 */ f32 current;
    /* 0x08 */ s16 state;
    /* 0x0A */ s16 counter;
    /* 0x0C */ f32 wind;
} grCastle_PlatSubObj;

static f32 grCs_804D45E0 = 0.017453292f;
static u8 grCs_804D45E4 = 1;

static grCastleParams* grCs_804D6970;
static struct lb_80011A50_t* grCs_804D6974;

static const Quaternion grCs_803B7EB8 = { 0.0f, 0.0f, 0.0f, 1.0f };

static const Vec3 grCs_803B7E9C = { -257.0f, 13.5f, -252.0f };

typedef struct grCastle_DynEntry {
    s16 depth;
    s16 type;
} grCastle_DynEntry;

typedef struct grCastle_DynEntries {
    grCastle_DynEntry e[4];
} grCastle_DynEntries;

static const grCastle_DynEntries grCs_803B7EA8 = {{
    { 66, 6 },
    { 76, 6 },
    { 85, 6 },
    { 94, 6 },
}};

typedef struct grCastle_YOffsets {
    f32 v[6];
} grCastle_YOffsets;

static const grCastle_YOffsets grCs_803B7F50 = {{
    4.0f, 6.0f, 7.0f, 6.0f, 4.0f, -1.0f,
}};

typedef struct grCastle_WeightTable {
    s32 w[3];
} grCastle_WeightTable;

static const grCastle_WeightTable grCs_803B7EF0 = {{ 0, 0, 0 }};

typedef struct grCastle_TargetEntry {
    s16 map_id;
    s16 jobj_idx;
} grCastle_TargetEntry;

typedef struct grCastle_TargetTable {
    grCastle_TargetEntry e[11];
} grCastle_TargetTable;

static const grCastle_TargetTable grCs_803B7EFC = {{
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 },
}};

void grCastle_801CD338(bool arg0)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;

    gobj = Ground_801C2BA4(6);
    if (gobj != NULL) {
        jobj = Ground_801C3FA4(gobj, 4);
        if (jobj != NULL) {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }
    }
}

void grCastle_801CD37C(void)
{
    PAD_STACK(4);
    grCs_804D6970 = Ground_801C49F8();

    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;

    grCastle_801CD4D0(0);
    grCastle_801CD4D0(4);
    grCastle_801CD4D0(3);
    grCastle_801CD4D0(6);

    mpLib_80057BC0(0);
    mpLib_80057BC0(1);
    mpLib_80057BC0(2);
    mpLib_80057BC0(6);
    mpLib_80057BC0(7);
    mpLib_80057BC0(8);
    mpLib_80057BC0(9);
    mpLib_80057BC0(10);
    mpLib_80057BC0(11);
    mpLib_80057BC0(12);
    mpLib_80057BC0(13);
    mpLib_80057BC0(14);

    Ground_801C39C0();
    Ground_801C3BB4();
    {
        Vec3 vec = { 1.0f, 0.0f, 0.0f };
        PAD_STACK(4);
        grCs_804D6974 = lb_80011A50(&vec, -1, 0.5f, 0.0f, 1.0471976f,
                                    -10000.0f, 10000.0f, 10000.0f, -10000.0f);
    }
}

void grCastle_801CD4A0(void) {}

void grCastle_801CD4A4(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grCastle_801CD4C8(void)
{
    return false;
}

HSD_GObj* grCastle_801CD4D0(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grCs_803E0FF4[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

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
            HSD_GObj_SetupProc(gobj, callbacks->callback2, 4);
        }

    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grcastle.c", 297,
                 gobj_id);
    }

    return gobj;
}

void grCastle_801CD5BC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

bool grCastle_801CD600(Ground_GObj* gobj)
{
    return false;
}

void grCastle_801CD608(Ground_GObj* gobj) {}

void grCastle_801CD60C(Ground_GObj* gobj) {}

void grCastle_801CD610(Ground_GObj* gobj)
{
    ftCo_800C06E8(gobj, 6, grCastle_801D09B8);
    grCastle_801CF7B0(gobj);
    grCastle_801CDFD8(gobj);
}

/// #grCastle_801CD658
void grCastle_801CD658(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    UnkArchiveStruct* archive;
    DynamicsDesc* flag3;
    DynamicsDesc* flag4;
    DynamicsDesc* flag6;
    Vec3 pos;
    grCastle_DynEntries entries_s;
    s32 i;
    s32 pad;

    grAnime_801C8138(gobj, gp->map_id, 0);

    pos = grCs_803B7E9C;
    {
        f32 scale = Ground_801C0498();
        pos.x *= scale;
        pos.y *= scale;
        pos.z *= scale;
    }
    grLib_801C96F8(0x7536, 0x1E, &pos);

    gp->gv.castle9.dynamics[0].data = NULL;
    gp->gv.castle9.dynamics[1].data = NULL;
    gp->gv.castle9.dynamics[2].data = NULL;
    gp->gv.castle9.dynamics[3].data = NULL;
    gp->gv.castle9.dynamics[4].data = NULL;
    gp->gv.castle9.dynamics[5].data = NULL;
    gp->gv.castle9.dynamics[6].data = NULL;
    gp->gv.castle9.dynamics[7].data = NULL;

    for (i = 8; i < 12; i++) {
        gp->gv.castle9.dynamics[i].data = NULL;
    }

    archive = grDatFiles_801C6324();
    if (archive != NULL) {
        flag3 = HSD_ArchiveGetPublicAddress(archive->unk0,
                                            "dynamicsdata_flag3");
        if (flag3 != NULL) {
            flag4 = HSD_ArchiveGetPublicAddress(archive->unk0,
                                                "dynamicsdata_flag4");
            if (flag4 != NULL) {
                flag6 = HSD_ArchiveGetPublicAddress(archive->unk0,
                                                    "dynamicsdata_flag6");
                if (flag6 != NULL) {
                    grCastle_DynEntry* ep;
                    DynamicsDesc* dp;

                    entries_s = grCs_803B7EA8;
                    ep = entries_s.e;
                    dp = &gp->gv.castle9.dynamics[0];

                    i = 0;
                    do {
                        HSD_JObj* jobj =
                            Ground_801C3FA4(gobj, ep->depth);
                        if (jobj != NULL) {
                            if (ep->type == 3) {
                                grLib_801C9B20(jobj, flag3, dp);
                            } else if (ep->type == 4) {
                                grLib_801C9B20(jobj, flag4, dp);
                            } else if (ep->type == 6) {
                                grLib_801C9B20(jobj, flag6, dp);
                            } else {
                                dp->data = NULL;
                            }
                        } else {
                            dp->data = NULL;
                        }
                        i++;
                        ep++;
                        dp++;
                    } while ((u32)i < 4);
                }
            }
        }
    }

    gobj->render_cb = fn_801D0924;
    Ground_801C10B8(gobj, grCastle_801CD610);
    gp->gv.castle9.xC4 = 0;
    gp->gv.castle9.xC8 = 0;
    gp->gv.castle9.xCC = 0;
    gp->gv.castle9.xDE &= ~0x80;
    gp->x10_flags.b5 = 1;
}

bool grCastle_801CD8A0(Ground_GObj* gobj)
{
    return false;
}

void grCastle_801CD8A8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    int i;

    grCastle_801CF868(gobj);
    grCastle_801CE19C(gobj);
    Ground_801C2FE0(gobj);
    lb_800115F4();
    grCastle_801D0BBC();
    for (i = 0; i < 12; i++) {
        if (gp->gv.castle3.x1C[i].data != NULL) {
            grCastle_801D0D84(gp->gv.castle3.x1C[i].data->desc.ft_unk.jobj->parent);
        }
    }
    for (i = 0; i < 12; i++) {
        if (gp->gv.castle3.x1C[i].data != NULL) {
            grLib_801C9B8C(&gp->gv.castle3.x1C[i]);
            grCastle_801D0D24();
        }
    }
}

void grCastle_801CD960(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    s32 i;

    for (i = 0; i < 12; i++) {
        grLib_801C9B6C(&gp->gv.castle3.x1C[i]);
    }
}

void grCastle_801CD9B4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    mpJointSetCb1(4, gp, grCastle_801CF750);
    mpJointSetCb1(5, gp, grCastle_801CF750);
}

/// #grCastle_801CDA0C
void grCastle_801CDA0C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    f32 val;

    Ground_801C2ED0(jobj, gp->map_id);
    gp->x10_flags.b5 = 1;

    gp->gv.castle8.xC4 = Ground_801C3FA4(gobj, 1);
    if (*(f32*)((u8*)grCs_804D6970 + 0x18) != 0.0f) {
        val = *(f32*)((u8*)grCs_804D6970 + 0x14);
    } else {
        val = *(f32*)((u8*)grCs_804D6970 + 0x10);
    }
    gp->gv.castle8.xC8 = val;
    gp->gv.castle8.xCC = 0;

    HSD_JObjSetTranslateY(gp->gv.castle8.xC4, gp->gv.castle8.xC8);
    mpLib_80057424(4);

    gp->gv.castle8.xCE = (s16)*(f32*)((u8*)grCs_804D6970 + 0x38);
    gp->gv.castle8.xD0 = 0.0f;

    gp->gv.castle8.xD4 = Ground_801C3FA4(gobj, 4);
    if (*(f32*)((u8*)grCs_804D6970 + 0x18) != 0.0f) {
        val = *(f32*)((u8*)grCs_804D6970 + 0x14);
    } else {
        val = *(f32*)((u8*)grCs_804D6970 + 0x10);
    }
    gp->gv.castle8.xD8 = val;
    gp->gv.castle8.xDC = 0;

    HSD_JObjSetTranslateY(gp->gv.castle8.xD4, gp->gv.castle8.xD8);
    mpLib_80057424(5);

    gp->gv.castle8.xDE = (s16)*(f32*)((u8*)grCs_804D6970 + 0x38);
    gp->gv.castle8.xE0 = 0.0f;

    Ground_801C10B8(gobj, grCastle_801CD9B4);
    Ground_801C2FE0(gobj);
}

bool grCastle_801CDC3C(Ground_GObj* gobj)
{
    return false;
}

/// #grCastle_801CDC44
void grCastle_801CDC44(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    Ground* gp2 = gp;
    s32 i = 0;

    do {
        switch (gp2->gv.castle8.xCC) {
        case 0:
            if (gp2->gv.castle8.xD0 > 0.0f) {
                s16 cnt = gp2->gv.castle8.xCE;
                gp2->gv.castle8.xCE = cnt + 1;
                if ((f32) cnt > grCs_804D6970->x38) {
                    gp2->gv.castle8.xCC = 2;
                }
            } else {
                gp2->gv.castle8.xCE = 0;
                gp2->gv.castle8.xCC = 1;
            }
            break;
        case 1:
            if (gp2->gv.castle8.xD0 > 0.0f) {
                gp2->gv.castle8.xCE = 0;
                gp2->gv.castle8.xCC = 0;
            } else {
                s16 cnt = gp2->gv.castle8.xCE;
                gp2->gv.castle8.xCE = cnt + 1;
                if ((f32) cnt > grCs_804D6970->x3C) {
                    gp2->gv.castle8.xCC = 3;
                }
            }
            break;
        case 2: {
            f32 wind = gp2->gv.castle8.xD0;
            if (wind > 0.0f) {
                f32 speed_cap = grCs_804D6970->x28;
                f32 speed =
                    wind * grCs_804D6970->x20 + grCs_804D6970->x24;
                f32 max_val;
                f32 cur;

                if (speed > speed_cap) {
                    speed = speed_cap;
                }
                max_val = grCs_804D6970->x10;
                cur = gp2->gv.castle8.xC8;
                if ((max_val - cur) < speed) {
                    gp2->gv.castle8.xC8 = max_val;
                } else {
                    gp2->gv.castle8.xC8 = cur + speed;
                }
                HSD_JObjSetTranslateY(gp2->gv.castle8.xC4,
                                      gp2->gv.castle8.xC8);
            } else {
                gp2->gv.castle8.xCE = 0;
                gp2->gv.castle8.xCC = 1;
            }
            break;
        }
        case 3: {
            f32 wind = gp2->gv.castle8.xD0;
            if (wind > 0.0f) {
                gp2->gv.castle8.xCE = 0;
                gp2->gv.castle8.xCC = 0;
            } else {
                f32 speed_cap = grCs_804D6970->x34;
                f32 speed =
                    wind * grCs_804D6970->x2C + grCs_804D6970->x30;
                f32 cur;
                f32 min_val;

                if (speed > speed_cap) {
                    speed = speed_cap;
                }
                cur = gp2->gv.castle8.xC8;
                min_val = grCs_804D6970->x14;
                if ((cur - min_val) < speed) {
                    gp2->gv.castle8.xC8 = min_val;
                } else {
                    gp2->gv.castle8.xC8 = cur - speed;
                }
                HSD_JObjSetTranslateY(gp2->gv.castle8.xC4,
                                      gp2->gv.castle8.xC8);
            }
            break;
        }
        }
        i++;
        gp2->gv.castle8.xD0 = 0.0f;
        gp2 = (Ground*) ((u8*) gp2 + 0x10);
    } while (i < 2);
    Ground_801C2FE0(gobj);
}

void grCastle_801CDF50(Ground_GObj* gobj) {}

bool grCastle_801CDF54(Vec3* vec)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    int i;

    i = 0;
    if (stage_info.internal_stage_id == 0x2) {
        for (i = 0; i < 9; i += 1) {
            gobj = Ground_801C2BA4(i + 8);
            if (gobj != NULL) {
                jobj = Ground_801C3FA4(gobj, 0);
                lb_8000B1CC(jobj, NULL, vec);
                return true;
            }
        }
    }
    return false;
}

void grCastle_801CDFD8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    register u8 byte;
    register s32 one;
    grCastleParams* params;
    s32 random_range;
    s32 rand_result;
    grCastleParams* params2;
    s32 neg_one;
    s32 zero;
    s32 base_value;
    s16 final_value;

    // Set bit 7 at offset 0xDE
    one = 1;
    byte = ((u8*) gp)[0xDE];
#ifdef MWERKS_GEKKO
    asm { rlwimi byte, one, 7, 24, 24 }
#else
    NOT_IMPLEMENTED;
#endif
    ((u8*) gp)[0xDE] = byte;

    // Get random range from params
    params = grCs_804D6970;
    random_range = params->xA;

    if (random_range != 0) {
        rand_result = HSD_Randi(random_range);
    } else {
        rand_result = 0;
    }

    // Add base value and set various shorts
    params2 = grCs_804D6970;
    neg_one = -1;
    zero = 0;
    base_value = params2->x8;
    final_value = (s16) (base_value + rand_result);

    *(s16*) ((u8*) gp + 0xD4) = final_value;
    *(s16*) ((u8*) gp + 0xDC) = neg_one;
    *(s16*) ((u8*) gp + 0xDA) = neg_one;
    *(s16*) ((u8*) gp + 0xD8) = neg_one;
    *(s16*) ((u8*) gp + 0xD6) = zero;
}

/// #grCastle_801CE054
s32 grCastle_801CE054(Ground_GObj* gobj)
{
    s16 arr[9];
    s32 count = 0;
    s32 ctr;
    s32 val = 0;
    Ground* gp = GET_GROUND(gobj);
    s16* dst = arr + count;
    s16 picked;
    s32 idx;

    ctr = 3;
    do {
        if (val != gp->gv.castle4.xD8 &&
            val != gp->gv.castle4.xDA &&
            val != gp->gv.castle4.xDC)
        {
            *dst++ = (s16) val;
            count++;
        }
        val++;
        if (val != gp->gv.castle4.xD8 &&
            val != gp->gv.castle4.xDA &&
            val != gp->gv.castle4.xDC)
        {
            *dst++ = (s16) val;
            count++;
        }
        val++;
        if (val != gp->gv.castle4.xD8 &&
            val != gp->gv.castle4.xDA &&
            val != gp->gv.castle4.xDC)
        {
            *dst++ = (s16) val;
            count++;
        }
        val++;
    } while (--ctr != 0);

    if (count != 0) {
        idx = HSD_Randi(count);
    } else {
        idx = 0;
    }

    picked = arr[idx];
    (&gp->gv.castle4.xD8)[gp->gv.castle4.xD6] = picked;

    if (gp->gv.castle4.xD6 == 2) {
        gp->gv.castle4.xD6 = 0;
    } else {
        gp->gv.castle4.xD6 = gp->gv.castle4.xD6 + 1;
    }

    return (s32) picked;
}

/// #grCastle_801CE19C
void grCastle_801CE19C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    PAD_STACK(8);
    if (((u8*) gp)[0xDE] >> 7 & 1) {
        s16 timer = *(s16*) ((u8*) gp + 0xD4);
        *(s16*) ((u8*) gp + 0xD4) = timer - 1;
        if (timer < 0) {
            HSD_GObj* new_gobj =
                grCastle_801CD4D0(grCastle_801CE054(gobj) + 8);
            ((u8*) gp)[0xDE] &= ~0x80;
            if (new_gobj != NULL) {
                Ground* new_gp = new_gobj->user_data;
                Ground_801C5440(gp, 0, 0x53021U);
                Ground_801C5694(
                    gp, 0,
                    *(f32*) ((u8*) grCs_804D6970 +
                             *(s16*) ((u8*) new_gp + 0xC6) * 0x14 + 0x60));
                *(Ground_GObj**) ((u8*) new_gp + 0xD4) = gobj;
            }
        }
    }
}

/// #grCastle_801CE260
void grCastle_801CE260(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground* gp2;
    CmSubject* subject;
    u8* p;

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);

    {
        struct { u8 b : 1; } *bp = (void*) ((u8*) gp + 0xC4);
        bp->b = 0;
    }
    gp->gv.icemt.xC6 = gp->map_id - 8;
    gp->gv.arwing.xCC = 0;
    p = (u8*) grCs_804D6970 + gp->gv.icemt.xC6 * 0x14;
    gp->gv.flatzone.xCA = *(s16*) (p + 0x5C);

    gp2 = GET_GROUND(gobj);
    *(u32*) &gp2->gv.arwing.xD8 = (u32) Camera_80029044(2);
    subject = (CmSubject*) *(u32*) &gp2->gv.arwing.xD8;
    if (subject != NULL) {
        subject->x40.x = *(f32*) ((u8*) grCs_804D6970 + 0x118);
        subject->x40.y = *(f32*) ((u8*) grCs_804D6970 + 0x11C);
        subject->x48.x = *(f32*) ((u8*) grCs_804D6970 + 0x120);
        subject->x48.y = *(f32*) ((u8*) grCs_804D6970 + 0x124);
    }

    grMaterial_801C94D8(jobj);
    gp->gv.arwing.xD0 = (u32) grMaterial_801C8CFC(
        0, 3, gp, Ground_801C3FA4((HSD_GObj*) gobj, 0),
        (void (*)(Item_GObj*, Ground*)) fn_801CE3A0, NULL, NULL);
    it_80275414((Item_GObj*) gp->gv.arwing.xD0);
    Ground_801C5440(gp, 0, 0x53025U);
}

void fn_801CE3A0(void) {}

bool grCastle_801CE3A4(Ground_GObj* gobj)
{
    return false;
}

/// #grCastle_801CE3AC
void grCastle_801CE3AC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_GObj* entity_gobj = gp->gv.castle5.xCC;

    if (entity_gobj != NULL) {
        HSD_JObj* jobj = GET_JOBJ(entity_gobj);
        Quaternion rot;
        Vec3 pos;
        Vec3 offset;
        PAD_STACK(4);

        rot = grCs_803B7EB8;

        offset.x = 0.0f;
        offset.y = *(f32*)((u8*)grCs_804D6970 + 0x110);
        offset.z = 0.0f;

        lb_8000B1CC(Ground_801C3FA4(gobj, 1), &offset, &pos);

        HSD_JObjSetTranslate(jobj, &pos);

        rot.x = *(f32*)((u8*)grCs_804D6970 + gp->gv.castle5.xC6 * 0x14 + 0x64);
        rot.y = *(f32*)((u8*)grCs_804D6970 + gp->gv.castle5.xC6 * 0x14 + 0x68);
        rot.z = *(f32*)((u8*)grCs_804D6970 + gp->gv.castle5.xC6 * 0x14 + 0x6C);

        HSD_JObjSetRotation(jobj, &rot);
    }
}

/// #grCastle_801CE578
#pragma push
#pragma dont_inline on
void grCastle_801CE578(Ground_GObj* gobj)
{
    Ground* gp = (Ground*) gobj->user_data;
    Vec3 pos;
    Vec3 jpos;
    PAD_STACK(44);

    {
        CmSubject* cam = (CmSubject*) gp->gv.castle11.xD8;
        if (cam != NULL) {
            lb_8000B1CC(Ground_801C3FA4(gobj, 0), NULL, &pos);
            cam->x10 = pos;
            cam->x1C = pos;
        }
    }

    gp = (Ground*) gobj->user_data;
    if (gp->gv.castle11.xCC == 0) {
        s16 timer = gp->gv.castle11.xCA;
        gp->gv.castle11.xCA = timer - 1;
        if (timer < 0) {
            gp->gv.castle11.xCC = (u32) grCastle_801CD4D0(2);
            Ground_801C53EC(0x53026);
            grCastle_801CE3AC(gobj);
        }
    }

    if (!gp->gv.castle11.xC4.b0) {
        gp = (Ground*) gobj->user_data;
        if (grAnime_801C83D0(gobj, 0, 1)) {
            gp->gv.castle11.xC8 =
                *(s16*) ((u8*) grCs_804D6970 + 0x58);
            gp->gv.castle11.xC4.b0 = 1;
            grMaterial_801C9604(gobj,
                                *(s32*) ((u8*) grCs_804D6970 + 0x114), 0);
            if (gp->gv.castle11.xCC != 0) {
                Ground_801C4A08((HSD_GObj*) gp->gv.castle11.xCC);
            }
            Ground_801C5544(gp, 0);
        }
    } else {
        gp = (Ground*) gobj->user_data;
        {
            s16 timer = gp->gv.castle11.xC8;
            gp->gv.castle11.xC8 = timer - 1;
            if (timer < 0) {
                if (gp->gv.castle11.xD0 != 0) {
                    grMaterial_801C8CDC((HSD_GObj*) gp->gv.castle11.xD0);
                }
                gp->gv.castle11.xD0 = 0;

                {
                    HSD_GObj* newobj = grCastle_801CD4D0(1);
                    if (newobj != NULL) {
                        HSD_JObj* jobj = (HSD_JObj*) newobj->hsd_obj;
                        lb_8000B1CC(Ground_801C3FA4(gobj, 0), NULL, &jpos);
                        if (jobj == NULL) {
                            __assert("jobj.h", 0x394, "jobj");
                        }
                        jobj->translate = jpos;
                        if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
                            HSD_JObjSetMtxDirtySub(jobj);
                        }
                        lb_800119DC(&jpos, 0xB4, 20.0f, 0.1f, 1.0471976f);
                    }
                }

                {
                    Ground* sat =
                        (Ground*) ((HSD_GObj*) gp->gv.castle11.xD4)
                            ->user_data;
                    s32 rand;
                    s32 range;

                    {
                        struct { u8 b0:1; u8:7; } *flags =
                            (void*)((u8*) sat + 0xDE);
                        flags->b0 = 1;
                    }

                    range = *(s16*) ((u8*) grCs_804D6970 + 0xE);
                    if (range != 0) {
                        rand = HSD_Randi(range);
                    } else {
                        rand = 0;
                    }
                    *(s16*) ((u8*) sat + 0xD4) =
                        (s16) (*(s16*) ((u8*) grCs_804D6970 + 0xC) + rand);
                }

                gp = (Ground*) gobj->user_data;
                if (gp->gv.castle11.xD8 != 0) {
                    Camera_800290D4(
                        (CmSubject*) gp->gv.castle11.xD8);
                    gp->gv.castle11.xD8 = 0;
                }
                Ground_801C4A08(gobj);
            }
        }
    }
}
#pragma pop

void grCastle_801CE7E4(Ground_GObj* gobj) {}

void grCastle_801CE7E8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    PAD_STACK(8);
    Ground_801C2ED0(GET_JOBJ(gobj), gp->map_id);
    gp->gv.castle.xC4 = 0;
    gp->gv.castle.xC8 = grCs_804D6970->x12C[gp->gv.castle.xC4];
    grAnime_801C8138(gobj, gp->map_id, gp->gv.castle.xC4);
}

bool grCastle_801CE858(Ground_GObj* gobj)
{
    return false;
}

void grCastle_801CE860(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;

    if ((s32) gp->gv.castle.xC4 < 3) {
        s16 timer = gp->gv.castle.xC8;
        gp->gv.castle.xC8 = timer - 1;
        if (timer < 0) {
            u8* ptr;
            gp->gv.castle.xC4++;
            grAnime_801C8138(gobj, gp->map_id, gp->gv.castle.xC4);
            ptr = (u8*) grCs_804D6970;
            ptr += gp->gv.castle.xC4 * 2;
            gp->gv.castle.xC8 = *(s16*) (ptr + 0x12C);
        }
    }
    Camera_80030E44(1, NULL);
}

void grCastle_801CE8E4(Ground_GObj* gobj) {}

/// #grCastle_801CE8E8
void grCastle_801CE8E8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    Ground* gp2;
    CmSubject* subject;
    PAD_STACK(8);

    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);

    gp2 = GET_GROUND(gobj);
    gp2->gv.arwing.xC8 = (u32) Camera_80029044(2);
    subject = (CmSubject*) gp2->gv.arwing.xC8;
    if (subject != NULL) {
        subject->x40.x = *(f32*) ((u8*) grCs_804D6970 + 0x134);
        subject->x40.y = *(f32*) ((u8*) grCs_804D6970 + 0x138);
        subject->x48.x = *(f32*) ((u8*) grCs_804D6970 + 0x13C);
        subject->x48.y = *(f32*) ((u8*) grCs_804D6970 + 0x140);
    }
    gp->gv.arwing.xC4 = (u32) grMaterial_801C8CFC(
        0, 4, gp, Ground_801C3FA4((HSD_GObj*) gobj, 0),
        (void (*)(Item_GObj*, Ground*)) fn_801CE9DC, NULL, NULL);
    it_80275414((Item_GObj*) gp->gv.arwing.xC4);
    Ground_801C5440(gp, 0, 0x53024U);
}

void fn_801CE9DC(void) {}

bool grCastle_801CE9E0(Ground_GObj* gobj)
{
    return false;
}

/// #grCastle_801CE9E8
void grCastle_801CE9E8(Ground_GObj* gobj)
{
    Vec3 pos;
    Ground* gp = GET_GROUND(gobj);
    CmSubject* subject = (CmSubject*) gp->gv.arwing.xC8;
    PAD_STACK(8);
    if (subject != NULL) {
        lb_8000B1CC(Ground_801C3FA4(gobj, 0), NULL, &pos);
        subject->x10 = pos;
        subject->x1C = pos;
    }
    if (grAnime_801C83D0(gobj, 0, 1)) {
        HSD_GObj* mat = (HSD_GObj*) gp->gv.arwing.xC4;
        if (mat != NULL) {
            grMaterial_801C8CDC(mat);
        }
        gp->gv.arwing.xC4 = 0;
        {
            Ground* gp2 = gobj->user_data;
            CmSubject* subj2 = (CmSubject*) gp2->gv.arwing.xC8;
            if (subj2 != NULL) {
                Camera_800290D4(subj2);
                gp2->gv.arwing.xC8 = 0;
            }
        }
        Ground_801C4A08(gobj);
    }
}

void grCastle_801CEAC8(Ground_GObj* gobj) {}

/// #grCastle_801CEACC

bool grCastle_801CEEFC(Ground_GObj* gobj)
{
    return false;
}

/// #grCastle_801CEF04
void grCastle_801CEF04(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    PAD_STACK(8);

    switch (gp->gv.castle6.xC4) {
    case 0:
        break;
    case 1: {
        s32 hi, lo, range;

        gp->gv.castle6.xC8 = 0;
        hi = *(s16*)((u8*)grCs_804D6970 + 0x42);
        lo = *(s16*)((u8*)grCs_804D6970 + 0x40);

        if (hi > lo) {
            range = hi - lo;
            hi = lo + (range != 0 ? HSD_Randi(range) : 0);
        } else if (hi < lo) {
            range = lo - hi;
            hi += (range != 0 ? HSD_Randi(range) : 0);
        }
        gp->gv.castle6.xCC = hi;
        if (grCastle_801D0298(gobj, 1) != 0) {
            gp->gv.castle6.xC4 = 2;
        }
        grCastle_801D02B8(gobj);
        break;
    }
    case 2: {
        s32 temp = gp->gv.castle6.xCC;
        gp->gv.castle6.xCC = temp - 1;
        if (temp < 0) {
            s32 i;
            gp->gv.castle6.xC4 = 3;
            gp->gv.castle6.xCC = 0;
            for (i = 0; i < 5; i++) {
                if (gp->gv.castle3.x1C[2].count != 0) {
                    grMaterial_801C8CDC(
                        (HSD_GObj*)gp->gv.castle3.x1C[2].count);
                    gp->gv.castle3.x1C[2].count = 0;
                }
                gp = (Ground*)((u8*)gp + 4);
            }
        }
        grCastle_801D02B8(gobj);
        break;
    }
    case 3: {
        s32 temp = gp->gv.castle6.xCC;
        gp->gv.castle6.xCC = temp + 1;
        if (temp > *(s16*)((u8*)grCs_804D6970 + 0x44)) {
            gp->gv.castle6.xC4 = 4;
        } else {
            s32 val;
            if (gp->gv.castle6.xC8 != 0) {
                val = 0;
            } else {
                val = 1;
            }
            gp->gv.castle6.xC8 = (s16)val;
        }
        grCastle_801D02B8(gobj);
        break;
    }
    case 4: {
        s32 val;
        if (gp->gv.castle6.xC8 != 0) {
            val = 0;
        } else {
            val = 1;
        }
        gp->gv.castle6.xC8 = (s16)val;
        if (grCastle_801D0298(gobj, 0) != 0) {
            gp->gv.castle6.xC8 = 0;
            gp->gv.castle6.xC4 = 0;
        }
        break;
    }
    }
    Ground_801C2FE0(gobj);
}

void grCastle_801CF0F0(Ground_GObj* gobj) {}

/// #grCastle_801CF0F4
void grCastle_801CF0F4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    f32 scale;

    Ground_801C2ED0(jobj, gp->map_id);
    gp->gv.castle7.xC4 = 0;
    gp->gv.castle7.xD8 = 0;
    HSD_JObjSetFlagsAll(jobj, 0x10);
    scale = 1.5f * Ground_801C0498();
    HSD_JObjSetScaleX(jobj, scale);
    HSD_JObjSetScaleY(jobj, scale);
    HSD_JObjSetScaleZ(jobj, scale);

    switch (gp->map_id) {
    case ONETT:
        gp->gv.castle7.xD0 = grCastle_801CD4D0(0x11);
        return;
    case BIGBLUE:
        gp->gv.castle7.xD0 = grCastle_801CD4D0(7);
        return;
    case MUTECITY:
        gp->gv.castle7.xD0 = grCastle_801CD4D0(5);
        return;
    }
}

bool grCastle_801CF300(Ground_GObj* gobj)
{
    return false;
}

/// #grCastle_801CF308

void grCastle_801CF74C(Ground_GObj* gobj) {}

void grCastle_801CF750(Ground* gp, s32 arg1, CollData* cd, s32 arg3,
                       mpLib_GroundEnum arg4, f32 arg5)
{
    s32 idx;
    PAD_STACK(16);

    if (arg1 == 4) {
        idx = 0;
    } else {
        idx = 1;
    }

    if ((s32) cd->x34_flags.b1234 == 1) {
        gp = (Ground*) ((u8*) gp + idx * 16);
        *(f32*) ((u8*) gp + 0xD0) += (f32) arg3;
    }
}

/// #grCastle_801CF7B0
void grCastle_801CF7B0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    s16 x0, x2;

    gp->gv.castle2.xC4 = grCastle_801CD4D0(20);
    gp->gv.castle2.xC8 = grCastle_801CD4D0(19);
    gp->gv.castle2.xCC = grCastle_801CD4D0(18);
    gp->gv.castle2.xD0 = -1;

    x2 = grCs_804D6970->x2;
    x0 = grCs_804D6970->x0;
    gp->gv.castle2.xD2 = x2 > x0 ? x0 + (x2 - x0 != 0 ? HSD_Randi(x2 - x0) : 0)
                         : x2 < x0
                             ? x2 + (x0 - x2 != 0 ? HSD_Randi(x0 - x2) : 0)
                             : x2;
}

/// #grCastle_801CF868
HSD_JObj* grCastle_801CF868(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    if ((gp->gv.castle12.xC4[0] != 0 || gp->gv.castle12.xC4[1] != 0 ||
         gp->gv.castle12.xC4[2] != 0) &&
        (gp->gv.castle12.xD0 == -1 ||
         (((HSD_GObj*) gp->gv.castle12.xC4[gp->gv.castle12.xD0]) != NULL &&
          ((Ground*) ((HSD_GObj*) gp->gv.castle12.xC4[gp->gv.castle12.xD0])
               ->user_data) != NULL &&
          *(s16*) &((Ground*) ((HSD_GObj*) gp->gv.castle12
                                    .xC4[gp->gv.castle12.xD0])
                         ->user_data)
                        ->gv.castle2.xC4 == 0)))
    {
        s16 timer = gp->gv.castle12.xD2;
        gp->gv.castle12.xD2 = timer - 1;
        if ((s16) gp->gv.castle12.xD2 < 0) {
            s16 base = *(s16*) ((u8*) grCs_804D6970 + 0x2);
            s16 range_end = *(s16*) ((u8*) grCs_804D6970 + 0x0);

            if (base > range_end) {
                s32 diff = base - range_end;
                base = range_end + (diff != 0 ? HSD_Randi(diff) : 0);
            } else if (base < range_end) {
                s32 diff = range_end - base;
                base = base + (diff != 0 ? HSD_Randi(diff) : 0);
            }
            gp->gv.castle12.xD2 = base;

            {
                grCastle_WeightTable weights = grCs_803B7EF0;
                s16 cur_slot = gp->gv.castle12.xD0;
                s32 total;
                s32 rand;
                s32 slot;
                s32* wp;
                Ground* sat_gp;

                if (cur_slot != -1) {
                    weights.w[cur_slot] =
                        weights.w[cur_slot] /
                        *(s16*) ((u8*) grCs_804D6970 + 0x6);
                }

                total = weights.w[0] + weights.w[1] + weights.w[2];
                rand = total != 0 ? HSD_Randi(total) : 0;

                wp = weights.w;
                slot = 0;
                rand -= wp[0];
                if (rand >= 0) {
                    slot = 1;
                    rand -= wp[1];
                    if (rand >= 0) {
                        slot = 2;
                        rand -= wp[2];
                        if (rand >= 0) {
                            slot = 3;
                        }
                    }
                }
                if (slot == 3) {
                    slot = 0;
                }
                gp->gv.castle12.xD0 = slot;

                sat_gp = (Ground*) ((HSD_GObj*) gp->gv.castle12
                                         .xC4[gp->gv.castle12.xD0])
                              ->user_data;

                {
                    grCastle_TargetTable targets = grCs_803B7EFC;
                    s32 idx;
                    HSD_GObj* entity;

                    PAD_STACK(52);
                    idx = HSD_Randi(11);
                    entity = HSD_GObj_Entities->x14;

                    while (entity != NULL) {
                        if ((s32) ((Ground*) entity->user_data)->map_id ==
                            (s16) targets.e[idx].map_id)
                        {
                            break;
                        }
                        entity = entity->next;
                    }
                    if (entity != NULL) {
                        *(u32*) ((u8*) sat_gp + 0xD4) =
                            (u32) Ground_801C3FA4(
                                entity, (s32) targets.e[idx].jobj_idx);
                        *(s16*) ((u8*) sat_gp + 0xC4) = 1;
                    }
                }
            }
        }
    }
}

void fn_801CFAFC(Item_GObj* item, Ground* gp, Vec3* pos, HSD_GObj* gobj,
                 f32 arg4)
{
    *(s16*) &gp->gv.castle2.xC4 = 4;
    if (ftLib_80086960(gobj)) {
        ftLib_80086A4C(gobj, (f32) grCs_804D6970->x4);
    }
}

void fn_801CFB68(Item_GObj* item_gobj, Ground* gp, HSD_GObj* gobj)
{
    gp->gv.pura.xC4 = 4;
    if (ftLib_80086960(gobj) != 0) {
        ftLib_80086A4C(gobj, (f32) grCs_804D6970->x4);
    }
}

/// #grCastle_801CFBD4

/// #grCastle_801D0298

bool grCastle_801D0298(Ground_GObj* gobj, s32 arg1)
{
    grCastle_801CFBD4();
    return false;
}

/// #grCastle_801D02B8
void grCastle_801D02B8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    Ground* base = gp;
    s32 i;

    i = 0;
    do {
        if (gp->gv.castle10.state[i] == 1) {
            grCastle_YOffsets offsets = grCs_803B7F50;
            f32 yoff = offsets.v[gp->gv.castle10.idx[i]];

            if (yoff != -1.0f) {
                f32 newY = base->gv.castle10.baseY[0] + yoff;
                HSD_JObjSetTranslateY(base->gv.castle10.jobjs[0], newY);

                if ((gp->gv.castle10.xC4 == 1 ||
                     (u16)(gp->gv.castle10.xC4 - 2) <= 1U) &&
                    gp->gv.castle10.idx[i] == 3)
                {
                    HSD_JObj* eff = base->gv.castle10.effect_a[0];
                    if (eff != NULL) {
                        Vec3 pos;
                        Vec3 vel;
                        lb_8000B1CC(eff, NULL, &pos);
                        vel.z = 0.0f;
                        vel.x = 0.0f;
                        pos.y += 5.0f;
                        vel.y = *(f32*)((u8*)grCs_804D6970 + 0x50);
                        it_8026F7C8(&pos, &vel, 1);
                        HSD_JObjSetFlags(base->gv.castle10.effect_a[0],
                                         0x10);
                        HSD_JObjClearFlags(base->gv.castle10.effect_b[0],
                                           0x10);
                    }
                }
            } else {
                HSD_JObjSetTranslateY(base->gv.castle10.jobjs[0],
                                      base->gv.castle10.baseY[0]);
                gp->gv.castle10.state[i] = 0;
            }
            gp->gv.castle10.idx[i]++;
        }
        i++;
        base = (Ground*)((u8*)base + 4);
    } while (i < 5);
}

void grCastle_801D0520(Ground_GObj* gobj, int renderpass)
{
    Ground* gp = GET_GROUND(gobj);
    if (gp->gv.castle.xC8 == 0) {
        grDisplay_801C5DB0(gobj, renderpass);
    }
}

static inline void grCastle_801D0550_sub(unkCastle* arg0, s32 i)
{
    arg0->x134[i] = 1;
    grMaterial_801C8CDC(arg0->x10C[i]);
    arg0->x10C[i] = NULL;
    Ground_801C53EC(0x53020U);
}

void grCastle_801D0550(void* arg0, unkCastle* arg1)
{
    PAD_STACK(16);
    grCastle_801D0550_sub(arg1, 0);
}

void grCastle_801D059C(void* arg0, unkCastle* arg1)
{
    PAD_STACK(16);
    grCastle_801D0550_sub(arg1, 1);
}

void grCastle_801D05E8(void* arg0, unkCastle* arg1)
{
    PAD_STACK(16);
    grCastle_801D0550_sub(arg1, 2);
}

void grCastle_801D0634(void* arg0, unkCastle* arg1)
{
    PAD_STACK(16);
    grCastle_801D0550_sub(arg1, 3);
}

void grCastle_801D0680(void* arg0, unkCastle* arg1)
{
    PAD_STACK(16);
    grCastle_801D0550_sub(arg1, 4);
}

static void grCastle_801D06CC_sub(unkCastle* arg0, Ground_GObj* gobj, s32 i)
{
    if (ftLib_80086960(gobj) || itGetKind(gobj) != Pokemon_Random) {
        arg0->x134[i] = 1;
        grMaterial_801C8CDC(arg0->x10C[i]);
        arg0->x10C[i] = NULL;
        Ground_801C53EC(0x53020U);
    }
}

void grCastle_801D06CC(void* arg0, unkCastle* arg1, Ground_GObj* gobj)
{
    grCastle_801D06CC_sub(arg1, gobj, 0);
}

void grCastle_801D0744(void* arg0, unkCastle* arg1, Ground_GObj* gobj)
{
    grCastle_801D06CC_sub(arg1, gobj, 1);
}

void grCastle_801D07BC(void* arg0, unkCastle* arg1, Ground_GObj* gobj)
{
    grCastle_801D06CC_sub(arg1, gobj, 2);
}

void grCastle_801D0834(void* arg0, unkCastle* arg1, Ground_GObj* gobj)
{
    grCastle_801D06CC_sub(arg1, gobj, 3);
}

void grCastle_801D08AC(void* arg0, unkCastle* arg1, Ground_GObj* gobj)
{
    grCastle_801D06CC_sub(arg1, gobj, 4);
}

void fn_801D0924(HSD_GObj* gobj, int renderpass)
{
    Ground* gp = gobj->user_data;
    int i;

    grDisplay_801C5DB0(gobj, renderpass);

    if (gp->x10_flags.b7) {
        GXColor color1 = { 0xFF, 0xFF, 0xFF, 0xFE };
        GXColor color2 = { 0xFF, 0xFF, 0xFF, 0xFF };
        PAD_STACK(4);

        for (i = 0; i < 12; i++) {
            if (gp->gv.castle3.x1C[i].data != NULL) {
                lb_800117F4(&gp->gv.castle3.x1C[i], &color1, &color2, 999,
                            renderpass);
            }
        }
    }
}

/// #grCastle_801D09B8
s32 grCastle_801D09B8(HSD_GObj* gobj, Vec3* arg2)
{
    Vec3 sp2C;
    Vec3 sp20;
    Vec3 sp14;
    f32 temp_f31;
    PAD_STACK(4);

    temp_f31 = 14.0f * Ground_801C0498();
    ftLib_80086644(gobj, &sp2C);
    ftLib_80086684(gobj, &sp20);
    if (sp2C.y < temp_f31) {
        if (sp20.y > temp_f31) {
            f32 temp_f1 = ftLib_80086B80(gobj) / 10.0f;
            sp2C.y = temp_f31;
            grCastle_801D0A9C(&sp2C, temp_f1);
        }
        ftLib_80086BEC(gobj, &sp14);
        if (sp14.y < -0.5f) {
            arg2->x = 0.0f;
            arg2->y = 0.1f;
            arg2->z = 0.0f;
        } else {
            arg2->z = 0.0f;
            arg2->y = 0.0f;
            arg2->x = 0.0f;
        }
        return 1;
    }
    return 0;
}

/// #grCastle_801D0A9C

DynamicsDesc* grCastle_801D0B04(enum_t arg)
{
    return false;
}

bool grCastle_801D0B0C(Vec3* v, int arg1, HSD_JObj* jobj)
{
    Vec3 pos;
    f32 temp_f30;
    f32 temp_f31;

    temp_f31 = 192.0f;
    temp_f30 = 137.0f;
    temp_f31 *= Ground_801C0498();
    temp_f30 *= Ground_801C0498();
    if ((v->x > temp_f31) && (v->y < temp_f30)) {
        return 0;
    }
    lb_8000B1CC(jobj, NULL, &pos);
    if ((1.0f + v->y) > pos.y) {
        return 1;
    }
    return 0;
}

void grCastle_801D0A9C(Vec3* arg0, f32 arg8)
{
    HSD_Generator* gen = grLib_801C96F8(0x7530, 0x1E, arg0);
    if (gen != NULL) {
        HSD_psAppSRT* srt = gen->appsrt;
        srt->scale.x *= arg8;
        srt->scale.y *= arg8;
        srt->scale.z *= arg8;
    }
}

/// #grCastle_801D0BBC
struct lb_80011A50_t* grCastle_801D0BBC(void)
{
    f32 angle;

    angle = atan2f(grCs_804D6974->x4.z, grCs_804D6974->x4.x) + grCs_804D45E0;
    if (angle > 1.0471975430846214) {
        angle = 1.0471976f;
    }
    if (angle < -1.0471975430846214) {
        angle = -1.0471976f;
    }
    grCs_804D6974->x4.x = cosf(angle);
    grCs_804D6974->x4.z = sinf(angle);
    if ((grCs_804D6974->unk_angle_int % 30) == 0 &&
        HSD_Randf() > 0.5)
    {
        grCs_804D45E0 = -grCs_804D45E0;
    }
    if ((grCs_804D6974->unk_angle_int % 300) == 0) {
        if (grCs_804D45E4 != 0) {
            grCs_804D45E4 = 0;
        } else if (HSD_Randf() > 0.5) {
            grCs_804D45E4 = 1;
        }
    }
    if (grCs_804D45E4 != 0) {
        grCs_804D6974->unk_scale = 0.3 * HSD_Randf() + 0.2;
        return grCs_804D6974;
    }
    grCs_804D6974->unk_scale = 0.05 * HSD_Randf();
    return grCs_804D6974;
}

void grCastle_801D0D24()
{
    if (grCs_804D45E4 != 0) {
        grCs_804D6974->unk_scale = 0.3 * HSD_Randf() + 0.2;
    } else {
        grCs_804D6974->unk_scale = 0.05 * HSD_Randf();
    }
}

/// #grCastle_801D0D84
void grCastle_801D0D84(HSD_JObj* jobj)
{
    Vec3 pos;
    Vec3 dir;
    Vec3 fwd;
    Vec3 cross;
    Quaternion rot;
    f32 rot_y;
    f32 len;
    f32 wind_len;
    f32 angle;
    f32 correction;

    if (jobj == NULL) {
        return;
    }

    HSD_JObjSetupMatrix(jobj);
    pos.x = jobj->mtx[0][3];
    pos.y = jobj->mtx[1][3];
    pos.z = jobj->mtx[2][3];

    rot = jobj->rotate;
    rot_y = rot.y;

    wind_len = lb_800103B8(&pos, &dir);
    dir.y = 0.0f;
    len = lbVector_Normalize(&dir);

    fwd.x = cosf(rot_y);
    fwd.y = 0.0f;
    fwd.z = -sinf(rot_y);

    angle = lbVector_Angle(&fwd, &dir);
    {
        s32 near_zero;
        if (angle < 0.00001f && angle > -0.00001f) {
            near_zero = 1;
        } else {
            near_zero = 0;
        }
        if (near_zero == 0) {
            correction = len * (wind_len * sinf(angle));
            if (correction < 0.0f) {
                correction = -correction;
            }
            PSVECCrossProduct(&fwd, &dir, &cross);
            if (cross.y > 0.0) {
                rot.y = rot_y + correction;
            } else {
                rot.y = rot_y - correction;
            }
        }
    }

    if (rot.y > 3.1415926535897931) {
        rot.y = (f32) ((f64) rot.y - 6.2831853071795862);
    } else if (rot.y < -3.1415926535897931) {
        rot.y = (f32) ((f64) rot.y + 6.2831853071795862);
    }

    HSD_JObjSetRotation(jobj, &rot);
    HSD_JObjClearFlagsAll(jobj, JOBJ_USE_QUATERNION);
}

f32 grCastle_801D0FF0(void)
{
    return 50.0f * Ground_801C0498();
}
