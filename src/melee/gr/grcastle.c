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
#include "gm/gm_16AE.h"
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
#include <MetroTRK/intrinsics.h>
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

typedef struct grCastleParams_Entry {
    /* 0x00 */ s16 x0;
    /* 0x02 */ u8 pad_x2[2];
    /* 0x04 */ f32 x4;
    /* 0x08 */ f32 x8;
    /* 0x0C */ f32 xC;
    /* 0x10 */ f32 x10;
} grCastleParams_Entry;

typedef struct grCastleParams {
    /* 0x000 */ s16 x0;
    /* 0x002 */ s16 x2;
    /* 0x004 */ s16 x4;
    /* 0x006 */ s16 x6;
    /* 0x008 */ s16 x8;
    /* 0x00A */ s16 xA;
    /* 0x00C */ s16 xC;
    /* 0x00E */ s16 xE;
    /* 0x010 */ f32 x10;
    /* 0x014 */ f32 x14;
    /* 0x018 */ f32 x18;
    /* 0x01C */ u8 pad_x1C[4];
    /* 0x020 */ f32 x20;
    /* 0x024 */ f32 x24;
    /* 0x028 */ f32 x28;
    /* 0x02C */ f32 x2C;
    /* 0x030 */ f32 x30;
    /* 0x034 */ f32 x34;
    /* 0x038 */ f32 x38;
    /* 0x03C */ f32 x3C;
    /* 0x040 */ s16 x40;
    /* 0x042 */ s16 x42;
    /* 0x044 */ s16 x44;
    /* 0x046 */ u8 pad_x46[2];
    /* 0x048 */ f32 x48;
    /* 0x04C */ f32 x4C;
    /* 0x050 */ f32 x50;
    /* 0x054 */ s16 x54;
    /* 0x056 */ u8 pad_x56[2];
    /* 0x058 */ s16 x58;
    /* 0x05A */ u8 pad_x5A[2];
    /* 0x05C */ grCastleParams_Entry entries[9];
    /* 0x110 */ f32 x110;
    /* 0x114 */ s32 x114;
    /* 0x118 */ f32 x118;
    /* 0x11C */ f32 x11C;
    /* 0x120 */ f32 x120;
    /* 0x124 */ f32 x124;
    /* 0x128 */ u8 pad_x128[4];
    /* 0x12C */ s16 x12C[4];
    /* 0x134 */ f32 x134;
    /* 0x138 */ f32 x138;
    /* 0x13C */ f32 x13C;
    /* 0x140 */ f32 x140;
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

typedef struct grCastle_BlinkTable {
    s16 data[19];
} grCastle_BlinkTable;

static const grCastle_BlinkTable grCs_803B7EC8 = {{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0
}};

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

void grCastle_801CDA0C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    f32 val;

    Ground_801C2ED0(jobj, gp->map_id);
    gp->x10_flags.b5 = 1;

    gp->gv.castle8.plat[0].jobj = Ground_801C3FA4(gobj, 1);
    if (grCs_804D6970->x18 != 0.0f) {
        val = grCs_804D6970->x14;
    } else {
        val = grCs_804D6970->x10;
    }
    gp->gv.castle8.plat[0].pos = val;
    gp->gv.castle8.plat[0].state = 0;

    HSD_JObjSetTranslateY(gp->gv.castle8.plat[0].jobj, gp->gv.castle8.plat[0].pos);
    mpLib_80057424(4);

    gp->gv.castle8.plat[0].timer = (s16) grCs_804D6970->x38;
    gp->gv.castle8.plat[0].wind = 0.0f;

    gp->gv.castle8.plat[1].jobj = Ground_801C3FA4(gobj, 4);
    if (grCs_804D6970->x18 != 0.0f) {
        val = grCs_804D6970->x14;
    } else {
        val = grCs_804D6970->x10;
    }
    gp->gv.castle8.plat[1].pos = val;
    gp->gv.castle8.plat[1].state = 0;

    HSD_JObjSetTranslateY(gp->gv.castle8.plat[1].jobj, gp->gv.castle8.plat[1].pos);
    mpLib_80057424(5);

    gp->gv.castle8.plat[1].timer = (s16) grCs_804D6970->x38;
    gp->gv.castle8.plat[1].wind = 0.0f;

    Ground_801C10B8(gobj, grCastle_801CD9B4);
    Ground_801C2FE0(gobj);
}

bool grCastle_801CDC3C(Ground_GObj* gobj)
{
    return false;
}

void grCastle_801CDC44(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    s32 i = 0;

    do {
        struct grCastle_Platform* plat = &gp->gv.castle8.plat[i];
        switch (plat->state) {
        case 0:
            if (plat->wind > 0.0f) {
                s16 cnt = plat->timer;
                plat->timer = cnt + 1;
                if ((f32) cnt > grCs_804D6970->x38) {
                    plat->state = 2;
                }
            } else {
                plat->timer = 0;
                plat->state = 1;
            }
            break;
        case 1:
            if (plat->wind > 0.0f) {
                plat->timer = 0;
                plat->state = 0;
            } else {
                s16 cnt = plat->timer;
                plat->timer = cnt + 1;
                if ((f32) cnt > grCs_804D6970->x3C) {
                    plat->state = 3;
                }
            }
            break;
        case 2: {
            f32 wind = plat->wind;
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
                cur = plat->pos;
                if ((max_val - cur) < speed) {
                    plat->pos = max_val;
                } else {
                    plat->pos = cur + speed;
                }
                HSD_JObjSetTranslateY(plat->jobj,
                                      plat->pos);
            } else {
                plat->timer = 0;
                plat->state = 1;
            }
            break;
        }
        case 3: {
            f32 wind = plat->wind;
            if (wind > 0.0f) {
                plat->timer = 0;
                plat->state = 0;
            } else {
                f32 speed_cap = grCs_804D6970->x34;
                f32 speed =
                    wind * grCs_804D6970->x2C + grCs_804D6970->x30;
                f32 cur;
                f32 min_val;

                if (speed > speed_cap) {
                    speed = speed_cap;
                }
                cur = plat->pos;
                min_val = grCs_804D6970->x14;
                if ((cur - min_val) < speed) {
                    plat->pos = min_val;
                } else {
                    plat->pos = cur - speed;
                }
                HSD_JObjSetTranslateY(plat->jobj,
                                      plat->pos);
            }
            break;
        }
        }
        i++;
        plat->wind = 0.0f;
    } while (i < 2);
    Ground_801C2FE0(gobj);
}

void grCastle_801CDF50(Ground_GObj* gobj) {}

#pragma push
#pragma dont_inline on
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
#pragma pop

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
    byte = gp->gv.castle9.xDE;
#ifdef MWERKS_GEKKO
    asm { rlwimi byte, one, 7, 24, 24 }
#else
    NOT_IMPLEMENTED;
#endif
    gp->gv.castle9.xDE = byte;

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

    gp->gv.castle9.xD4 = final_value;
    gp->gv.castle9.xDC = neg_one;
    gp->gv.castle9.xDA = neg_one;
    gp->gv.castle9.xD8 = neg_one;
    gp->gv.castle9.xD6 = zero;
}

s32 grCastle_801CE054(Ground_GObj* gobj)
{
    s16 arr[9];
    s32 count = 0;
    s32 ctr;
    s32 val = 0;
    Ground* gp = GET_GROUND(gobj);
    s16 picked;
    s32 idx;
    s32 i;

    for (ctr = 3; ctr != 0; ctr--) {
        for (i = 0; i < 3; i++) {
            if (val != gp->gv.castle4.xD8 && val != gp->gv.castle4.xDA &&
                val != gp->gv.castle4.xDC)
            {
                arr[count] = (s16) val;
                count++;
            }
            val++;
        }
    }

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

void grCastle_801CE19C(Ground_GObj* gobj)
{
    Ground* gp;
    Ground* tmp = GET_GROUND(gobj);
    PAD_STACK(8);
    gp = tmp;
    if (tmp->gv.castle9.xDE >> 7 & 1) {
        s16 timer;
        timer = gp->gv.castle9.xD4;
        gp->gv.castle9.xD4 = timer - 1;
        if (timer < 0) {
            HSD_GObj* new_gobj =
                grCastle_801CD4D0(grCastle_801CE054(gobj) + 8);
            {
                register u8 byte = gp->gv.castle9.xDE;
                register s32 zero = 0;
#ifdef MWERKS_GEKKO
                asm { rlwimi byte, zero, 7, 24, 24 }
#else
                NOT_IMPLEMENTED;
#endif
                gp->gv.castle9.xDE = byte;
            }
            if (new_gobj != NULL) {
                Ground* new_gp = new_gobj->user_data;
                Ground_801C5440(gp, 0, 0x53021U);
                Ground_801C5694(
                    gp, 0,
                    grCs_804D6970->entries[new_gp->gv.castle5.xC6].x4);
                new_gp->gv.castle11.xD4 = (u32) gobj;
            }
        }
    }
}

void grCastle_801CE260(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    Ground* gp2;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    CmSubject* subject;
    PAD_STACK(8);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);

    gp->gv.castle11.xC4.b0 = 0;
    gp->gv.icemt.xC6 = gp->map_id - 8;
    gp->gv.arwing.xCC = 0;
    gp->gv.flatzone.xCA = grCs_804D6970->entries[gp->gv.icemt.xC6].x0;

    gp2 = GET_GROUND(gobj);
    *(u32*) &gp2->gv.arwing.xD8 = (u32) Camera_80029044(2);
    subject = (CmSubject*) *(u32*) &gp2->gv.arwing.xD8;
    if (subject != NULL) {
        subject->x40.x = grCs_804D6970->x118;
        subject->x40.y = grCs_804D6970->x11C;
        subject->x48.x = grCs_804D6970->x120;
        subject->x48.y = grCs_804D6970->x124;
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

        offset.z = 0.0f;
        offset.x = 0.0f;
        offset.y = grCs_804D6970->x110;

        lb_8000B1CC(Ground_801C3FA4(gobj, 1), &offset, &pos);

        HSD_JObjSetTranslate(jobj, &pos);

        rot.x = grCs_804D6970->entries[gp->gv.castle5.xC6].x8;
        rot.y = grCs_804D6970->entries[gp->gv.castle5.xC6].xC;
        rot.z = grCs_804D6970->entries[gp->gv.castle5.xC6].x10;

        HSD_JObjSetRotation(jobj, &rot);
    }
}

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
            gp->gv.castle11.xC8 = grCs_804D6970->x58;
            gp->gv.castle11.xC4.b0 = 1;
            grMaterial_801C9604(gobj, grCs_804D6970->x114, 0);
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
                            (void*) &sat->gv.castle9.xDE;
                        flags->b0 = 1;
                    }

                    range = grCs_804D6970->xE;
                    if (range != 0) {
                        rand = HSD_Randi(range);
                    } else {
                        rand = 0;
                    }
                    sat->gv.castle9.xD4 =
                        (s16) (grCs_804D6970->xC + rand);
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
            gp->gv.castle.xC4++;
            grAnime_801C8138(gobj, gp->map_id, gp->gv.castle.xC4);
            gp->gv.castle.xC8 = grCs_804D6970->x12C[gp->gv.castle.xC4];
        }
    }
    Camera_80030E44(1, NULL);
}

void grCastle_801CE8E4(Ground_GObj* gobj) {}

void grCastle_801CE8E8(Ground_GObj* gobj)
{
    Ground* gp2;
    Ground* gp = GET_GROUND(gobj);
    CmSubject* subject;
    PAD_STACK(8);

    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);

    gp2 = GET_GROUND(gobj);
    gp2->gv.arwing.xC8 = (u32) Camera_80029044(2);
    subject = (CmSubject*) gp2->gv.arwing.xC8;
    if (subject != NULL) {
        subject->x40.x = grCs_804D6970->x134;
        subject->x40.y = grCs_804D6970->x138;
        subject->x48.x = grCs_804D6970->x13C;
        subject->x48.y = grCs_804D6970->x140;
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

void grCastle_801CE9E8(Ground_GObj* gobj)
{
    Vec3 pos;
    Ground* tmp;
    Ground* gp = GET_GROUND(gobj);
    CmSubject* subject = (CmSubject*) gp->gv.arwing.xC8;
    PAD_STACK(8);
    if (subject != NULL) {
        lb_8000B1CC(Ground_801C3FA4(gobj, 0), NULL, &pos);
        subject->x10 = pos;
        subject->x1C = pos;
    }
    if (grAnime_801C83D0(gobj, 0, 1)) {
        HSD_GObj* mat = (HSD_GObj*) (tmp = gp)->gv.arwing.xC4;
        if (mat != NULL) {
            grMaterial_801C8CDC(mat);
        }
        gp->gv.arwing.xC4 = 0;
        {
            Ground* gp2 = gobj->user_data;
            CmSubject* subj2 = (CmSubject*) (tmp = gp2)->gv.arwing.xC8;
            if (subj2 != NULL) {
                Camera_800290D4(subj2);
                gp2->gv.arwing.xC8 = 0;
            }
        }
        Ground_801C4A08(gobj);
    }
}

void grCastle_801CEAC8(Ground_GObj* gobj) {}

void grCastle_801CEACC(Ground_GObj* gobj)
{
    Ground* gp = (Ground*) gobj->user_data;
    HSD_JObj* jobj = (HSD_JObj*) gobj->hsd_obj;
    s32 i;

    Ground_801C2ED0(jobj, gp->map_id);
    gp->x10_flags.b5 = 1;
    gp->gv.castle10.xC4 = 0;
    HSD_JObjSetFlagsAll(jobj, 0x10);
    gp->gv.castle10.xC8 = 0;

    for (i = 0; i < 5; i++) {
        gp->gv.castle10.jobjs[i] = NULL;
        gp->gv.castle10.effect_a[i] = NULL;
        gp->gv.castle10.effect_b[i] = NULL;
        gp->gv.castle10.x10C[i] = 0;
        gp->gv.castle10.x120[i] = -1;
        gp->gv.castle10.state[i] = 0;
        gp->gv.castle10.idx[i] = 0;
        gp->gv.castle10.baseY[i] = 0.0f;
    }

    switch (gp->map_id) {
    case PURA:
        gp->gv.castle10.jobjs[0] =
            Ground_801C3FA4((HSD_GObj*) gobj, 1);
        gp->gv.castle10.effect_a[0] =
            Ground_801C3FA4((HSD_GObj*) gobj, 2);
        gp->gv.castle10.effect_b[0] =
            Ground_801C3FA4((HSD_GObj*) gobj, 3);
        gp->gv.castle10.baseY[0] =
            HSD_JObjGetTranslationY(gp->gv.castle10.jobjs[0]);
        gp->gv.castle10.x120[0] = 0xB;

        gp->gv.castle10.jobjs[1] =
            Ground_801C3FA4((HSD_GObj*) gobj, 4);
        gp->gv.castle10.effect_a[1] =
            Ground_801C3FA4((HSD_GObj*) gobj, 5);
        gp->gv.castle10.effect_b[1] =
            Ground_801C3FA4((HSD_GObj*) gobj, 6);
        gp->gv.castle10.baseY[1] =
            HSD_JObjGetTranslationY(gp->gv.castle10.jobjs[1]);
        gp->gv.castle10.x120[1] = 0xC;

        gp->gv.castle10.jobjs[2] =
            Ground_801C3FA4((HSD_GObj*) gobj, 7);
        gp->gv.castle10.effect_a[2] = NULL;
        gp->gv.castle10.effect_b[2] = NULL;
        gp->gv.castle10.x120[2] = 0xD;

        gp->gv.castle10.jobjs[3] =
            Ground_801C3FA4((HSD_GObj*) gobj, 8);
        gp->gv.castle10.effect_a[3] = NULL;
        gp->gv.castle10.effect_b[3] = NULL;
        gp->gv.castle10.x120[3] = 0xE;
        break;

    case SHRINE:
        gp->gv.castle10.jobjs[0] =
            Ground_801C3FA4((HSD_GObj*) gobj, 1);
        gp->gv.castle10.effect_a[0] =
            Ground_801C3FA4((HSD_GObj*) gobj, 2);
        gp->gv.castle10.effect_b[0] =
            Ground_801C3FA4((HSD_GObj*) gobj, 3);
        gp->gv.castle10.baseY[0] =
            HSD_JObjGetTranslationY(gp->gv.castle10.jobjs[0]);
        gp->gv.castle10.x120[0] = 6;

        gp->gv.castle10.jobjs[1] =
            Ground_801C3FA4((HSD_GObj*) gobj, 4);
        gp->gv.castle10.effect_a[1] =
            Ground_801C3FA4((HSD_GObj*) gobj, 5);
        gp->gv.castle10.effect_b[1] =
            Ground_801C3FA4((HSD_GObj*) gobj, 6);
        gp->gv.castle10.baseY[1] =
            HSD_JObjGetTranslationY(gp->gv.castle10.jobjs[1]);
        gp->gv.castle10.x120[1] = 7;

        HSD_JObjSetFlagsAll(Ground_801C3FA4((HSD_GObj*) gobj, 7),
                            0x10);
        gp->gv.castle10.jobjs[2] = NULL;
        gp->gv.castle10.effect_a[2] = NULL;
        gp->gv.castle10.effect_b[2] = NULL;
        mpLib_80057BC0(8);

        gp->gv.castle10.jobjs[3] =
            Ground_801C3FA4((HSD_GObj*) gobj, 0xA);
        gp->gv.castle10.effect_a[3] = NULL;
        gp->gv.castle10.effect_b[3] = NULL;
        gp->gv.castle10.x120[3] = 9;

        gp->gv.castle10.jobjs[4] =
            Ground_801C3FA4((HSD_GObj*) gobj, 0xB);
        gp->gv.castle10.effect_a[4] = NULL;
        gp->gv.castle10.effect_b[4] = NULL;
        gp->gv.castle10.x120[4] = 0xA;
        break;

    case GARDEN:
        gp->gv.castle10.jobjs[0] =
            Ground_801C3FA4((HSD_GObj*) gobj, 1);
        gp->gv.castle10.effect_a[0] =
            Ground_801C3FA4((HSD_GObj*) gobj, 2);
        gp->gv.castle10.effect_b[0] =
            Ground_801C3FA4((HSD_GObj*) gobj, 3);
        gp->gv.castle10.baseY[0] =
            HSD_JObjGetTranslationY(gp->gv.castle10.jobjs[0]);
        gp->gv.castle10.x120[0] = 0;

        gp->gv.castle10.jobjs[1] =
            Ground_801C3FA4((HSD_GObj*) gobj, 4);
        gp->gv.castle10.effect_a[1] = NULL;
        gp->gv.castle10.effect_b[1] = NULL;
        gp->gv.castle10.x120[1] = 1;

        gp->gv.castle10.jobjs[2] =
            Ground_801C3FA4((HSD_GObj*) gobj, 5);
        gp->gv.castle10.effect_a[2] = NULL;
        gp->gv.castle10.effect_b[2] = NULL;
        gp->gv.castle10.x120[2] = 2;
        break;
    }

    grCastle_801D0298(gobj, 0);
    Ground_801C2FE0(gobj);
    ((HSD_GObj*) gobj)->render_cb = (GObj_RenderFunc) grCastle_801D0520;
}

bool grCastle_801CEEFC(Ground_GObj* gobj)
{
    return false;
}

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
        hi = grCs_804D6970->x42;
        lo = grCs_804D6970->x40;

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
                if (gp->gv.castle10.x10C[i] != 0) {
                    grMaterial_801C8CDC(
                        (HSD_GObj*) gp->gv.castle10.x10C[i]);
                    gp->gv.castle10.x10C[i] = 0;
                }
            }
        }
        grCastle_801D02B8(gobj);
        break;
    }
    case 3: {
        s32 temp = gp->gv.castle6.xCC;
        gp->gv.castle6.xCC = temp + 1;
        if (temp > grCs_804D6970->x44) {
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

void grCastle_801CF308(Ground_GObj* gobj)
{
    s32 var_r6 = 0;
    Ground* gp = (Ground*) gobj->user_data;
    HSD_JObj* jobj = (HSD_JObj*) gobj->hsd_obj;
    grCastle_BlinkTable tbl = grCs_803B7EC8;
    Vec3 pos;
    Quaternion quat;
    PAD_STACK(40);

    switch (gp->gv.castle5.xC4) {
    case 1:
        gp->gv.castle.xC8 = -1;
        gp->gv.castle11.xCA = 0;
        HSD_JObjClearFlagsAll(jobj, 0x10);
        grAnime_801C86D4(gp->map_id, (HSD_GObj*) gobj, 0);
        gp->gv.castle5.xC4 = 2;
        /* fallthrough */
    case 2: {
        s32 delay = gp->gv.castle11.xCA;
        if (delay > 0) {
            gp->gv.castle11.xCA = delay - 1;
        } else {
            s8 val;
            gp->gv.castle.xC8 += 1;
            if (HSD_JObjGetFlags(jobj) & 0x10) {
                HSD_JObjClearFlagsAll(jobj, 0x10);
            } else {
                HSD_JObjSetFlagsAll(jobj, 0x10);
            }
            val = ((s8*) &tbl)[gp->gv.castle.xC8];
            if (val != -1) {
                gp->gv.castle11.xCA = (s16) (2.0 * (f64) val);
            } else {
                gp->gv.castle5.xC4 = 3;
                gp->gv.castle11.xD8 = (u32) grMaterial_801C8CFC(
                    0, 1, gp, jobj, NULL,
                    (void (*)(Item_GObj*, Ground*, Vec3*, HSD_GObj*,
                              f32)) fn_801CFAFC,
                    (void (*)(Item_GObj*, Ground*, HSD_GObj*)) fn_801CFB68);
                grMaterial_801C8DE0(
                    (Item_GObj*) gp->gv.castle11.xD8, 0.0f, -1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 4.0f);
                grMaterial_801C8E08(
                    (Item_GObj*) gp->gv.castle11.xD8);
                gp->gv.castle8.plat[0].state = grCs_804D6970->x54;
            }
        }
        var_r6 = 1;
        break;
    }
    case 3:
        var_r6 = 1;
        break;
    case 4: {
        if (gp->gv.castle11.xD8 != 0) {
            grMaterial_801C8CDC((HSD_GObj*) gp->gv.castle11.xD8);
            gp->gv.castle11.xD8 = 0;
        }
        ((Ground*) ((HSD_GObj*) gp->gv.castle7.xD0)->user_data)
            ->gv.castle5.xC4 = 1;
        gp->gv.castle5.xC4 = 5;
        grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
        Ground_801C5440(gp, 0, 0x53027U);
        Camera_80030E44(2, NULL);
        /* fallthrough */
    }
    case 5: {
        if (grAnime_801C83D0((HSD_GObj*) gobj, 0, 7) != 0) {
            s16 cnt = gp->gv.castle8.plat[0].state;
            gp->gv.castle8.plat[0].state = cnt - 1;
            if (cnt < 0) {
                HSD_JObjSetFlagsAll(jobj, 0x10);
            }
        }
        if ((s16) ((Ground*) ((HSD_GObj*) gp->gv.castle7.xD0)->user_data)
                ->gv.castle5.xC4 == 0) {
            gp->gv.castle5.xC4 = 0;
            HSD_JObjSetFlagsAll(jobj, 0x10);
        }
        var_r6 = 1;
        break;
    }
    }

    if (var_r6 != 0) {
        lb_8000B1CC((HSD_JObj*) gp->gv.castle11.xD4, NULL, &pos);
        HSD_JObjSetTranslate(jobj, &pos);

        HSD_JObjGetRotation((HSD_JObj*) gp->gv.castle11.xD4, &quat);
        HSD_JObjSetRotation(jobj, &quat);
    }
}

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
        gp->gv.castle8.plat[idx].wind += (f32) arg3;
    }
}

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
            s16 base = grCs_804D6970->x2;
            s16 range_end = grCs_804D6970->x0;

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
                        grCs_804D6970->x6;
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
                        sat_gp->gv.castle7.xD4 =
                            (u32) Ground_801C3FA4(
                                entity, (s32) targets.e[idx].jobj_idx);
                        sat_gp->gv.castle7.xC4 = 1;
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

s32 grCastle_801CFBD4(Ground_GObj* gobj, s32 arg1)
{
    s32 i = 0;
    s32 result = 1;
    Ground* gp = (Ground*) gobj->user_data;
    u8 _pad_top[8];
    unkCastleCallback cb1[5];
    unkCastleCallback2 cb2[5];
    Vec3 pos;
    Vec3 target_pos;
    PAD_STACK(12);

    do {
        HSD_JObj* jobj = gp->gv.castle10.jobjs[i];
        if (jobj != NULL) {
            HSD_JObj* eff_a = gp->gv.castle10.effect_a[i];
            HSD_JObj* eff_b = gp->gv.castle10.effect_b[i];

            if (arg1 != 0) {
                if (HSD_JObjGetFlags(jobj) & 0x10) {
                    s32 close;

                    if (grCastle_801CDF54(&target_pos) != 0 &&
                        (lb_8000B1CC(jobj, NULL, &pos),
                         sqrtf__Ff((pos.x - target_pos.x) *
                                       (pos.x - target_pos.x) +
                                   (pos.y - target_pos.y) *
                                       (pos.y - target_pos.y)) <
                             40.0f))
                    {
                        close = 1;
                    } else {
                        close = 0;
                    }

                    if (close == 0) {
                        HSD_JObjClearFlags(jobj, 0x10);
                        if (eff_a != NULL && eff_b != NULL) {
                            if (gm_8016AE80() != -1 &&
                                gm_8016B238() == 0)
                            {
                                HSD_JObjClearFlags(eff_a, 0x10);
                                HSD_JObjSetScaleY(eff_a, 0.0001f);
                                HSD_JObjSetFlags(eff_b, 0x10);
                                HSD_JObjSetScaleY(eff_b, 1.0f);
                            } else {
                                HSD_JObjSetFlags(eff_a, 0x10);
                                HSD_JObjSetScaleY(eff_a, 1.0f);
                                HSD_JObjClearFlags(eff_b, 0x10);
                                HSD_JObjSetScaleY(eff_b, 0.0001f);
                            }
                        } else {
                            HSD_JObjSetScaleY(jobj, 0.0001f);
                        }
                    }
                    gp->gv.castle10.state[i] = 0;
                    result = 0;
                    gp->gv.castle10.idx[i] = 0;
                } else {
                    HSD_JObj* target;
                    f32 newScale;

                    if (eff_a != NULL && eff_b != NULL) {
                        if (HSD_JObjGetFlags(eff_a) & 0x10) {
                            target = eff_b;
                        } else {
                            target = eff_a;
                        }
                    } else {
                        target = jobj;
                    }

                    newScale = HSD_JObjGetScaleY(target);
                    if (newScale < 1.0f) {
                        newScale += grCs_804D6970->x48;
                        if (newScale >= 1.0f) {
                            newScale = 1.0f;
                            mpJointListAdd(gp->gv.castle10.x120[i]);
                            if (eff_a != NULL &&
                                !(HSD_JObjGetFlags(eff_a) & 0x10))
                            {
                                cb1[0] = grCs_803B7F28[0];
                                cb1[1] = grCs_803B7F28[1];
                                cb1[2] = grCs_803B7F28[2];
                                cb1[3] = grCs_803B7F28[3];
                                cb1[4] = grCs_803B7F28[4];
                                cb2[0] = grCs_803B7F3C[0];
                                cb2[1] = grCs_803B7F3C[1];
                                cb2[2] = grCs_803B7F3C[2];
                                cb2[3] = grCs_803B7F3C[3];
                                cb2[4] = grCs_803B7F3C[4];
                                gp->gv.castle10.x10C[i] =
                                    (u32) grMaterial_801C8CFC(
                                        0, 2, gp, target, NULL,
                                        (void (*)(Item_GObj*, Ground*,
                                                  Vec3*, HSD_GObj*,
                                                  f32)) cb1[i],
                                        (void (*)(Item_GObj*, Ground*,
                                                  HSD_GObj*)) cb2[i]);
                                grMaterial_801C8DE0(
                                    (Item_GObj*) gp->gv.castle10.x10C[i],
                                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                    8.0f);
                                grMaterial_801C8E08(
                                    (Item_GObj*) gp->gv.castle10.x10C[i]);
                            }
                        }
                        HSD_JObjSetScaleY(target, newScale);
                        result = 0;
                    }
                }
            } else {
                if (!(HSD_JObjGetFlags(jobj) & 0x10)) {
                    HSD_JObj* target;
                    f32 newScale;

                    if (eff_a != NULL && eff_b != NULL) {
                        if (HSD_JObjGetFlags(eff_a) & 0x10) {
                            target = eff_b;
                        } else {
                            target = eff_a;
                        }
                    } else {
                        target = jobj;
                    }

                    newScale = HSD_JObjGetScaleY(target);
                    if (newScale > 0.0001f) {
                        newScale -= grCs_804D6970->x4C;
                        if (newScale <= 0.0001f) {
                            newScale = 0.0001f;
                            HSD_JObjSetFlags(jobj, 0x10);
                            if (eff_a != NULL) {
                                HSD_JObjSetFlags(eff_a, 0x10);
                            }
                            if (eff_b != NULL) {
                                HSD_JObjSetFlags(eff_b, 0x10);
                            }
                        }
                        HSD_JObjSetScaleY(target, newScale);
                        result = 0;
                    }
                }
                mpLib_80057BC0(gp->gv.castle10.x120[i]);
            }
        }
        i++;
    } while (i < 5);

    return result;
}


bool grCastle_801D0298(Ground_GObj* gobj, s32 arg1)
{
    return grCastle_801CFBD4(gobj, arg1);
}

void grCastle_801D02B8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    s32 i;

    i = 0;
    do {
        if (gp->gv.castle10.state[i] == 1) {
            grCastle_YOffsets offsets = grCs_803B7F50;
            f32 yoff = offsets.v[gp->gv.castle10.idx[i]];

            if (yoff != -1.0f) {
                f32 newY = gp->gv.castle10.baseY[i] + yoff;
                HSD_JObjSetTranslateY(gp->gv.castle10.jobjs[i], newY);

                if ((gp->gv.castle10.xC4 == 1 ||
                     (u16)(gp->gv.castle10.xC4 - 2) <= 1U) &&
                    gp->gv.castle10.idx[i] == 3)
                {
                    HSD_JObj* eff = gp->gv.castle10.effect_a[i];
                    if (eff != NULL) {
                        Vec3 pos;
                        Vec3 vel;
                        lb_8000B1CC(eff, NULL, &pos);
                        vel.z = 0.0f;
                        vel.x = 0.0f;
                        pos.y += 5.0f;
                        vel.y = grCs_804D6970->x50;
                        it_8026F7C8(&pos, &vel, 1);
                        HSD_JObjSetFlags(gp->gv.castle10.effect_a[i],
                                         0x10);
                        HSD_JObjClearFlags(gp->gv.castle10.effect_b[i],
                                           0x10);
                    }
                }
            } else {
                HSD_JObjSetTranslateY(gp->gv.castle10.jobjs[i],
                                      gp->gv.castle10.baseY[i]);
                gp->gv.castle10.state[i] = 0;
            }
            gp->gv.castle10.idx[i]++;
        }
        i++;
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

// Weird parameter stuff, but it matches?
bool grCastle_801D09B8(void* unused, HSD_GObj* gobj, Vec3* arg2)
{
    Vec3 sp2C;
    Vec3 sp20;
    Vec3 sp14;
    f32 temp_f31;

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
        return true;
    }
    return false;
}


DynamicsDesc* grCastle_801D0B04(enum_t arg)
{
    return false;
}

bool grCastle_801D0B0C(Vec3* v, int arg1, HSD_JObj* jobj)
{
    Vec3 pos;
    f32 x = 192.0f;
    f32 y = 137.0f;

    x *= Ground_801C0498();
    y *= Ground_801C0498();
    if ((v->x > x) && (v->y < y)) {
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

void grCastle_801D0BBC()
{
    f32 angle;
    angle = atan2f(grCs_804D6974->x4.z, grCs_804D6974->x4.x);
    angle = angle + grCs_804D45E0;
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
        return;
    }
    grCs_804D6974->unk_scale = 0.05 * HSD_Randf();
    return;
}

void grCastle_801D0D24()
{
    if (grCs_804D45E4 != 0) {
        grCs_804D6974->unk_scale = 0.3 * HSD_Randf() + 0.2;
    } else {
        grCs_804D6974->unk_scale = 0.05 * HSD_Randf();
    }
}

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
