#include "grpushon.h"

#include "placeholder.h"
#include "types.h"

#include <platform.h>

#include "cm/camera.h"
#include "ft/ftdevice.h"
#include "ft/ftlib.h"

#include "gr/forward.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "lb/lbspdisplay.h"
#include "lb/lbvector.h"
#include "lb/types.h"
#include "mp/mplib.h"
#include "MSL/math.h"
#include "sysdolphin/baselib/lobj.h"

#include <math_ppc.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/random.h>

struct grPushOn_Entry {
    s32 x0;
    s16 x4;
    s16 x6;
};

struct grPushOn_Lookup {
    s32 key;
    s32 value;
};

struct grPushOn_LightConfig {
    GXColor color;
    Vec3 pos;
    f32 ref_br;
    f32 ref_dist;
    s32 dist_func;
};

static struct {
    s32 x0;
    DynamicsDesc* x4;
    DynamicsDesc* x8;
    DynamicsDesc* xC;
    DynamicsDesc* x10;
    DynamicsDesc* x14;
    bool x18;
    struct grPushOn_Entry x1c[0x1E];
    struct grPushOn_Lookup x10c[0x21];
}* grPushOn_804D6AB8;

/// @todo .sdata order hack
static void order_sdata(void)
{
    (void) "0";
}

Vec3 const grPushOn_803B8440 = { 0 };
Vec3 const grPushOn_803B844C = { 0 };
Vec3 const grPushOn_803B8458 = { 0.0f, 100.0f, 0.0f };
Vec3 const grPushOn_803B8464 = { 0.0f, 100.0f, 0.0f };
float grPushOn_804D4934 = 16.0f;

StageCallbacks grPushOn_803E7AC8[3] = {
    { grPushOn_802184CC, grPushOn_80218590, grPushOn_80218598,
      grPushOn_8021859C, 0 },
    { grPushOn_802185A0, grPushOn_80218670, grPushOn_802186C8,
      grPushOn_802187A4, 0xC0000000 },
    { grPushOn_802187A8, grPushOn_80218880, grPushOn_80218888,
      grPushOn_80218ED0, 0 },
};

StageData grPushOn_803E7B10 = {
    PUSHON,
    grPushOn_803E7AC8,
    "/GrNPo.dat",
    grPushOn_802182C8,
    grPushOn_802182C4,
    grPushOn_80218330,
    grPushOn_80218378,
    grPushOn_802183DC,
    grPushOn_80219458,
    grPushOn_80219528,
    (1 << 0),
    NULL,
    0,
};

void grPushOn_802182C4(bool arg) {}

void grPushOn_802182C8(void)
{
    grPushOn_804D6AB8 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grPushOn_802183E4(0);
    grPushOn_802183E4(1);
    mpLib_80057BC0(0);
}

void grPushOn_80218330(void)
{
    HSD_GObj* gobj;
    Vec3 vec;

    grPushOn_802183E4(2);
    gobj = Ground_801C57A4();
    if (gobj != NULL) {
        ftLib_80086644(gobj, &vec);
        Ground_801C38BC(vec.x, vec.y);
        Camera_8002F3AC();
    }
}

void grPushOn_80218378(void)
{
    bool val;
    grZakoGenerator_801CAE04(NULL);
    val = grPushOn_804D6AB8->x18;
    if (val) {
        val = HSD_Randi(grPushOn_804D6AB8->x18);
    } else {
        val = false;
    }
    if (!val) {
        grZakoGenerator_801CAEB0(Ground_801C5840(), Ground_801C5940());
    }
}

bool grPushOn_802183DC(void)
{
    return false;
}

HSD_GObj* grPushOn_802183E4(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grPushOn_803E7AC8[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grpushon.c", 222,
                 gobj_id);
    }

    return gobj;
}

HSD_LightDesc grPushOn_803E7B74 = {
    NULL,
    NULL,
    6,
    0,
    { 0xFF, 0xFF, 0xFF, 0xFF },
    NULL,
    NULL,
    { &grPushOn_804D4934 },
};

void grPushOn_802184CC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    Vec3 cam_offset;

    grAnime_801C8138(gobj, gp->map_id, 0);
    Ground_801C39C0();
    Ground_801C3BB4();
    Stage_UnkSetVec3TCam_Offset(&cam_offset);
    Ground_801C3880(0.5f * (Stage_GetCamBoundsTopOffset() +
                            Stage_GetBlastZoneTopOffset()) -
                    cam_offset.y);
    Ground_801C3890(0.5f * (Stage_GetCamBoundsBottomOffset() +
                            Stage_GetBlastZoneBottomOffset()) -
                    cam_offset.y);
    Ground_801C38A0(0.5f * (Stage_GetCamBoundsLeftOffset() +
                            Stage_GetBlastZoneLeftOffset()) -
                    cam_offset.x);
    Ground_801C38AC(0.5f * (Stage_GetCamBoundsRightOffset() +
                            Stage_GetBlastZoneRightOffset()) -
                    cam_offset.x);
}

bool grPushOn_80218590(Ground_GObj* arg)
{
    return false;
}

void grPushOn_80218598(Ground_GObj* arg) {}

void grPushOn_8021859C(Ground_GObj* arg) {}

void grPushOn_802185A0(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(8);

    ftCo_800C07F8(gobj, 3, fn_802192A4);
    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C752C(jobj, 1, 0x77A4, HSD_AObjSetFlags, 3, 0x20000000);
    gp->u.map.xC4_b0 = false;
    mpJointSetCb1(3, gp, fn_802190A0);
    mpJointSetCb1(4, gp, fn_802190A0);
    mpJointSetCb1(5, gp, fn_802190A0);
}

bool grPushOn_80218670(Ground_GObj* arg)
{
    return false;
}

bool fn_80218678(void)
{
    HSD_GObj* gobj = Ground_801C2BA4(1);
    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
        if (gp != NULL) {
            if (gp->u.map.xC4_b0) {
                return true;
            }
        }
    }
    return false;
}

void grPushOn_802186C8(Ground_GObj* gobj)
{
    Vec3 vec;
    Ground* gp = gobj->user_data;
    PAD_STACK(12);

    vec = grPushOn_803B8440;
    Ground_801C3D44(fn_80218678, 25.0f, 20.0f);
    {
        HSD_GObj* gobj2 = Ground_801C57A4();
        if (gobj2 != NULL) {
            ftLib_80086644(gobj2, &vec);
            Ground_801C0498();
            if (vec.y < 0.0f) {
                Ground_801C0498();
                vec.y = 0.0f;
            } else if (vec.y > 800.0f * Ground_801C0498()) {
                vec.y = 800.0f * Ground_801C0498();
            }
            Ground_801C38BC(vec.x, vec.y);
        }
    }
    lb_800115F4();
    gp->u.map.xC4_b0 = false;
}

void grPushOn_802187A4(Ground_GObj* arg) {}

void grPushOn_802187A8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_LObj* lobj;

    gp->u.pushon.gobj = ((HSD_GObj*) HSD_GObjGXLinkHead)->next_gx;
    PAD_STACK(16);
    grPushOn_802190D0(gp->u.pushon.gobj);
    lobj = ((HSD_GObj*) gp->u.pushon.gobj)->hsd_obj;
    gp->u.pushon.count = 0;
    while (lobj != NULL) {
        gp->u.pushon.lobjs[gp->u.pushon.count] = lobj;
        gp->u.pushon.lobj_flags[gp->u.pushon.count] = HSD_LObjGetFlags(lobj);
        lobj = lobj == NULL ? NULL : lobj->next;
        gp->u.pushon.count++;
    }
    gp->u.pushon.point_light = grPushOn_80218ED4(gp->u.pushon.gobj);
    gp->u.pushon.spot_light = grPushOn_80218FC0(gp->u.pushon.gobj);
    grPushOn_80218888(gobj);
}

bool grPushOn_80218880(Ground_GObj* arg)
{
    return false;
}

/// @todo Fake padding function
static inline void pad_stack(GXColor color) {}

void grPushOn_80218888(Ground_GObj* gobj)
{
    HSD_GObj* player;
    Vec3 player_pos;
    Vec3 light_pos;
    s32 sorted[20];
    f32 distances[20];
    Vec3 pos1;
    Vec3 pos2;
    Vec3 dir;
    GXColor color;
    Vec3 temp_pos;
    Ground* gp;
    s32 count;
    s32 i;
    s32 j;
    s32 best;
    f32 min_dist;
    f32 ref_dist;
    f32 weight;
    f32 dx;
    f32 dy;
    f32 dist_sq;
    GET_GROUND(0);
    GET_GROUND(0);

    gp = GET_GROUND(gobj);
    player = Ground_801C57A4();
    if (player != NULL) {
        ftLib_80086644(player, &player_pos);
    } else {
        player_pos.z = 0.0f;
        player_pos.y = 0.0f;
        player_pos.x = 0.0f;
    }

    if (gp->u.pushon.gobj != 0) {
        i = 0;
        while (i < (s32) gp->u.pushon.count) {
            HSD_LObj* lobj = gp->u.pushon.lobjs[i];
            s32 type = lobj->flags & 3;

            if (type == 0) {
                distances[i] = -100.0f;
            } else if (type == 1 || type == 2) {
                HSD_LObjGetPosition(lobj, &pos1);
                dx = player_pos.x - pos1.x;
                dy = player_pos.y - pos1.y;
                {
                    f32 dx2 = dx * dx;
                    f32 dy2 = dy * dy;
                    distances[i] = sqrtf(dx2 + dy2);
                }
            } else if (type == 3) {
                HSD_LObjGetPosition(lobj, &pos2);
                distances[i] = ABS(player_pos.x - pos2.x);
            } else {
                HSD_ASSERT(0x1C5, 0);
            }

            if (distances[i] < 10.0f) {
                distances[i] = 10.0f;
            }
            sorted[i] = i;
            i += 1;
        }

        /* Selection sort by distance */
        for (i = 0; i < (int) gp->u.pushon.count; i++) {
            count = gp->u.pushon.count;
            min_dist = 3.4028235e38f;
            best = 0;
            for (j = i; j < count; j++) {
                if (min_dist > distances[sorted[j]]) {
                    best = j;
                    min_dist = distances[sorted[j]];
                }
            }
            {
                s32 tmp = sorted[i];
                sorted[i] = sorted[best];
                sorted[best] = tmp;
            }
        }

        /* Enable first 5 lights, disable rest */
        for (i = 0; i < (int) gp->u.pushon.count; i++) {
            if (i < 5) {
                HSD_LObjClearFlags(gp->u.pushon.lobjs[sorted[i]], 0x20);
            } else {
                HSD_LObjSetFlags(gp->u.pushon.lobjs[sorted[i]], 0x20);
            }
        }

        /* Compute weighted direction */
        dir = grPushOn_803B844C;
        ref_dist = distances[sorted[1]];

        for (i = 1; i < (int) gp->u.pushon.count; i++) {
            if (HSD_LObjGetPosition(gp->u.pushon.lobjs[sorted[i]],
                                    &light_pos) != 0)
            {
                weight = ref_dist / distances[sorted[i]];
                lbVector_Sub(&light_pos, &player_pos);
                if (light_pos.y < 100.0f) {
                    if (light_pos.y < 0.0f) {
                        weight = 0.0f;
                    } else {
                        weight *= light_pos.y / 100.0f;
                    }
                }
                lbVector_Normalize(&light_pos);
                light_pos.x *= weight;
                light_pos.y *= weight;
                light_pos.z *= weight;
                lbVector_Add(&dir, &light_pos);
            }
        }

        /* Compute magnitude and normalize direction */
        dist_sq = sqrtf(dir.z * dir.z + (dir.x * dir.x + dir.y * dir.y));
        if (dist_sq < 0.01f) {
            dir.y = 100.0f;
        }
        lbVector_Normalize(&dir);
        dir.x *= 20.0f;
        dir.y *= 20.0f;
        dir.z *= 20.0f;
        lbVector_Add(&dir, &player_pos);

        /* Set spotlight */
        HSD_LObjSetPosition(gp->u.pushon.point_light, &dir);
        HSD_LObjSetInterest(gp->u.pushon.point_light, &player_pos);
        HSD_LObjSetFlags(gp->u.pushon.point_light, 0x400);

        /* Color from 2nd nearest */
        {
            f32 dist_diff;
            dist_diff = distances[sorted[2]] - distances[sorted[1]];
            HSD_LObjGetColor(gp->u.pushon.lobjs[sorted[1]], &color);
            if (distances[sorted[2]] - distances[sorted[1]] < 50.0f) {
                f32 ratio = dist_diff / 50.0f;
                color.r = color.r * ratio;
                color.g = color.g * ratio;
                color.b = color.b * ratio;
            }
        }
        HSD_LObjSetColor(gp->u.pushon.spot_light, color);
        pad_stack(color);

        /* Copy position from 2nd nearest */
        if (HSD_LObjGetPosition(gp->u.pushon.lobjs[sorted[1]], &temp_pos) == 0)
        {
            temp_pos.z = 0.0f;
            temp_pos.y = 0.0f;
            temp_pos.x = 0.0f;
        }
        HSD_LObjSetPosition(gp->u.pushon.spot_light, &temp_pos);

        /* Copy interest from 2nd nearest */
        if (HSD_LObjGetInterest(gp->u.pushon.lobjs[sorted[1]], &temp_pos) == 0)
        {
            temp_pos.z = 0.0f;
            temp_pos.y = 0.0f;
            temp_pos.x = 0.0f;
        }
        HSD_LObjSetInterest(gp->u.pushon.spot_light, &temp_pos);

        /* Copy and modify flags */
        gp->u.pushon.spot_light->flags = gp->u.pushon.lobjs[sorted[1]]->flags;
        gp->u.pushon.spot_light->flags &= ~4;
        gp->u.pushon.spot_light->flags |= 8;
    }
}

void grPushOn_80218ED0(Ground_GObj* arg) {}

HSD_LObj* grPushOn_80218ED4(HSD_GObj* gobj)
{
    HSD_LObj* new_lobj;
    HSD_LObj* lobj;
    Vec3 pos;
    PAD_STACK(8);

    if (gobj == NULL || (lobj = gobj->hsd_obj) == NULL) {
        return NULL;
    }
    while ((lobj == NULL ? NULL : lobj->next) != NULL) {
        lobj = lobj == NULL ? NULL : lobj->next;
    }
    new_lobj = HSD_LObjLoadDesc(&grPushOn_803E7B74);
    if (new_lobj != NULL) {
        pos = grPushOn_803B8458;
        HSD_LObjSetNext(lobj, new_lobj);
        HSD_LObjSetPosition(new_lobj, &pos);
        HSD_LObjSetFlags(new_lobj, 0x20);
    }
    return new_lobj;
}

float grPushOn_804D4948 = 16.0f;

HSD_LightDesc grPushOn_803E7B90 = {
    NULL,
    NULL,
    0xA,
    0,
    { 0xFF, 0xFF, 0xFF, 0xFF },
    NULL,
    NULL,
    { &grPushOn_804D4948 },
};

static struct grPushOn_LightConfig light_configs[9] = {
    { { 0xBE, 0xE6, 0xE6, 0xFF },
      { -12.0F, 735.0F, -20.0F },
      0.1F,
      800.0F,
      3 },
    { { 0xF0, 0xF0, 0xF0, 0xFF },
      { 250.0F, 708.0F, -30.0F },
      0.4F,
      500.0F,
      3 },
    { { 0xC3, 0x56, 0xCD, 0xFF },
      { 550.0F, 655.0F, -50.0F },
      0.2F,
      600.0F,
      3 },
    { { 0xF0, 0xF0, 0xF0, 0xFF },
      { 860.0F, 550.0F, -30.0F },
      0.1F,
      700.0F,
      3 },
    { { 0x7C, 0xE7, 0xFF, 0xFF },
      { 1150.0F, 675.0F, -60.0F },
      0.2F,
      800.0F,
      3 },
    { { 0xFF, 0x4B, 0x4B, 0xFF },
      { 1400.0F, 370.0F, -60.0F },
      0.01F,
      500.0F,
      3 },
    { { 0xE6, 0xE6, 0xE6, 0xFF },
      { 1580.0F, 20.0F, -30.0F },
      0.1F,
      500.0F,
      3 },
    { { 0xFF, 0x6E, 0x6E, 0xFF },
      { 2093.0F, 120.0F, -20.0F },
      0.3F,
      600.0F,
      3 },
    { { 0xBE, 0xE6, 0xFF, 0xFF },
      { 1700.0F, 630.0F, -20.0F },
      0.2F,
      800.0F,
      3 },
};

HSD_LObj* grPushOn_80218FC0(HSD_GObj* gobj)
{
    HSD_LObj* new_lobj;
    HSD_LObj* lobj;
    Vec3 pos;
    PAD_STACK(8);

    if (gobj == NULL || (lobj = gobj->hsd_obj) == NULL) {
        return NULL;
    }
    while ((lobj == NULL ? NULL : lobj->next) != NULL) {
        lobj = lobj == NULL ? NULL : lobj->next;
    }
    new_lobj = HSD_LObjLoadDesc(&grPushOn_803E7B90);
    if (new_lobj != NULL) {
        pos = grPushOn_803B8464;
        HSD_LObjSetNext(lobj, new_lobj);
        HSD_LObjSetPosition(new_lobj, &pos);
    }
    return new_lobj;
}

/// Ground collision callback for pushon stage elements.
/// Activates push behavior when collision flags indicate contact (b1234 == 1).
void fn_802190A0(Ground* gp, s32 joint_id, CollData* coll, s32 unk,
                 mpLib_GroundEnum ground_enum, f32 arg5)
{
    if (((*(u8*) &coll->x34_flags >> 3U) & 0xF) == 1 &&
        (ground_enum - 1) <= 1U)
    {
        gp->u.map.xC4_b0 = true;
    }
}

static inline GXColor get_light_color(struct grPushOn_LightConfig* entry)
{
    return entry->color;
}

void grPushOn_802190D0(HSD_GObj* gobj)
{
    HSD_LObj* cur = gobj->hsd_obj;
    f32 scale = Ground_801C0498();
    struct grPushOn_LightConfig* entry;
    Vec3 pos;
    HSD_LObj* lobj;
    u32 i;

    lobj = cur == NULL ? NULL : cur->next;
    entry = light_configs;
    i = 0;

    while (i < 9 && lobj != NULL) {
        HSD_ASSERTMSG(698, (u32) (lobj->flags & LOBJ_TYPE_MASK) == LOBJ_POINT,
                      "HSD_LObjGetType(lobj)==LOBJ_POINT");
        lobj->flags = LOBJ_POINT | LOBJ_DIFFUSE;
        HSD_LObjSetColor(lobj, get_light_color(entry));
        pos = entry->pos;
        pos.x *= scale;
        pos.y *= scale;
        pos.z *= scale;
        HSD_LObjSetPosition(lobj, &pos);
        HSD_LObjSetDistAttn(lobj, scale * entry->ref_dist, entry->ref_br,
                            entry->dist_func);
        entry++;
        i++;
        lobj = lobj == NULL ? NULL : lobj->next;
    }
}

f32 grPushOn_803E7CCC[13] = {
    1441.428955078125F,
    1645.62890625F,
    340.57470703125F,
    1306.4332275390625F,
    1361.6331787109375F,
    361.5741882324219F,
    1193.4345703125F,
    1268.634521484375F,
    367.57391357421875F,
    1121.16015625F,
    1157.6820068359375F,
    354.6068115234375F,
    0.0F,
};

void grPushOn_80219204(int arg0, int* out1, int* out2)
{
    int idx = arg0 - 0x99;
    *out1 = grPushOn_804D6AB8->x1c[idx].x0;
    *out2 = grPushOn_804D6AB8->x1c[idx].x4;
}

int grPushOn_80219230(int arg0)
{
    s32 i = 0;
    s32 key;

    while (i < 0x21 && (key = grPushOn_804D6AB8->x10c[i].key) != -1) {
        if (key == arg0) {
            return grPushOn_804D6AB8->x10c[i].value;
        }
        i++;
    }
    HSD_ASSERT(861, 0);
}

s32 fn_802192A4(void* arg0, HSD_GObj* gobj, s32* result)
{
    Vec3 sp14;
    f32 scale = Ground_801C0498();
    s32 i;

    ftLib_80086644(gobj, &sp14);
    for (i = 0; i < 4; i++) {
        if ((scale * grPushOn_803E7CCC[i * 3] < sp14.x) &&
            (scale * grPushOn_803E7CCC[i * 3 + 1] > sp14.x) &&
            (scale * (-50.0f + grPushOn_803E7CCC[i * 3 + 2]) < sp14.y) &&
            (scale * grPushOn_803E7CCC[i * 3 + 2] > sp14.y))
        {
            *result = grPushOn_804D6AB8->x0;
            return 1;
        }
    }
    return 0;
}

DynamicsDesc* grPushOn_80219458(enum_t arg0)
{
    s32 joint;
    s32 kind;

    if (arg0 != -1) {
        joint = mpJointFromLine(arg0);
        if (joint != -1) {
            if (joint == 1) {
                mpLineGetKind(arg0);
                return grPushOn_804D6AB8->x4;
            }
            if (joint == 2) {
                kind = mpLineGetKind(arg0);
                if (kind == 1) {
                    return grPushOn_804D6AB8->x8;
                }
                if (kind == 2) {
                    return grPushOn_804D6AB8->xC;
                }
                if (kind == 4) {
                    return grPushOn_804D6AB8->x10;
                }
                if (kind == 8) {
                    return grPushOn_804D6AB8->x14;
                }
                return NULL;
            }
            return NULL;
        }
    }
    return NULL;
}

bool grPushOn_80219528(Vec3* arg, int arg0, HSD_JObj* jobj)
{
    return true;
}
