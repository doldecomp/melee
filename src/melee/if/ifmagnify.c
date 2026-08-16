#include "ifmagnify.h"

#include "baselib/gobjuserdata.h"
#include "cm/camera.h"
#include "ft/ftdrawcommon.h"
#include "ft/ftlib.h"
#include "gm/gm_1601.h"
#include "gm/gm_16AE.h"
#include "gm/types.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "if/if_2FD9.h"
#include "if/ifall.h"
#include "lb/lb_00B0.h"
#include "lb/lbarchive.h"
#include "lb/lbrefract.h"
#include "lb/lbspdisplay.h"
#include "pl/player.h"
#include "sc/types.h"

#include <math.h>
#include <baselib/cobj.h>
#include <baselib/displayfunc.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/mobj.h>
#include <baselib/tobj.h>
#include <baselib/wobj.h>

static HSD_WObjDesc ifMagnify_803F97C0 = { NULL,
                                           { 0.0F, 0.0F, 300.0F },
                                           NULL };
static HSD_WObjDesc ifMagnify_803F97D4 = { NULL, { 0.0F, 0.0F, 0.0F }, NULL };

static HSD_CameraDescFrustum ifMagnify_803F97E8 = {
    NULL,
    0,
    PROJ_ORTHO,
    { 0, 640, 0, 480 },
    { 0, 640, 0, 480 },
    &ifMagnify_803F97C0,
    &ifMagnify_803F97D4,
    0.0F,
    NULL,
    0.1F,
    32768.0F,
};

static char ifMagnify_804D57E8[] = "lupe";
static const int ifMagnify_804DDB60 = 0;

ifMagnify ifMagnify_804A1DE0;

static GXColor* (*ifMagnify_803F9828[])(void) = {
    Ground_801C0604, Ground_801C0690, Ground_801C0618,
    Ground_801C0654, Ground_801C06A4, Ground_801C0668,
    Ground_801C062C, Ground_801C067C, Ground_801C0640,
};

static u8 ifMagnify_803F984C[16][4] = {
    { 0, 0, 0, 0 }, { 0, 1, 0, 1 }, { 1, 2, 1, 2 }, { 2, 2, 2, 2 },
    { 0, 0, 3, 3 }, { 0, 1, 3, 4 }, { 1, 2, 4, 5 }, { 2, 2, 5, 5 },
    { 3, 3, 6, 6 }, { 3, 4, 6, 7 }, { 4, 5, 7, 8 }, { 5, 5, 8, 8 },
    { 6, 6, 6, 6 }, { 6, 7, 6, 7 }, { 7, 8, 7, 8 }, { 8, 8, 8, 8 },
};

static inline void ifMagnify_GetPlayerColor(GXColor* color, s32 slot)
{
    *color =
        gm_80160968(gm_80160854((u8) slot, Player_GetTeam(slot), gm_8016B168(),
                                Player_GetPlayerSlotType(slot)));
}

s32 ifMagnify_802FB6E8(s32 slot)
{
    (void) 0.0f;
    (void) 3.0f;
    (void) 0.5f;
    (void) 1.0f;
    (void) 2.0f;
    (void) 4503599627370496.0;
    if (ifMagnify_802FC998(slot) != 0) {
        return ifMagnify_804A1DE0.player[slot].state.unk;
    }
    return 0;
}

ifMagnifyPlayer* ifMagnify_802FB73C(ifMagnifyPlayer* arg0, Vec2* arg1,
                                    Vec2* arg2)
{
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f2;
    f32 temp_f3;
    f32 temp_f4;

    temp_f2 = arg1->x;
    temp_f4 = arg1->y;
    if (0.0f == temp_f2) {
        if (temp_f4 > 0.0f) {
            arg2->y = 162.7f;
        } else {
            arg2->y = -162.7f;
        }
        arg2->x = 0.0f;
    } else {
        temp_f3 = temp_f4 / temp_f2;
        if ((temp_f3 > 0.6438464f) || (temp_f3 < -0.6438464f)) {
            if (temp_f4 > 0.0f) {
                arg2->y = 162.7f;
            } else {
                arg2->y = -162.7f;
            }
            temp_f1 = arg2->y;
            temp_f1 = temp_f1 * temp_f2;
            temp_f1 /= temp_f4;
            if (temp_f1 < -252.70001f) {
                arg2->x = -252.70001f;
            } else if (temp_f1 > 252.70001f) {
                arg2->x = 252.70001f;
            } else {
                arg2->x = temp_f1;
            }
        } else {
            if (temp_f2 > 0.0f) {
                arg2->x = 252.70001f;
            } else {
                arg2->x = -252.70001f;
            }
            temp_f1_2 = arg2->x;
            temp_f1_2 = temp_f1_2 * temp_f4;
            temp_f1_2 /= temp_f2;
            if (temp_f1_2 < -162.7f) {
                arg2->y = -162.7f;
            } else if (temp_f1_2 > 162.7f) {
                arg2->y = 162.7f;
            } else {
                arg2->y = temp_f1_2;
            }
        }
    }

    temp_f1_3 = arg2->x;
    temp_f2 = -252.70001f;
    if (temp_f1_3 == temp_f2) {
        arg0->state.unk = 2;
        return arg0;
    }
    temp_f2 = 252.70001f;
    if (temp_f1_3 == temp_f2) {
        arg0->state.unk = 4;
        return arg0;
    }
    temp_f2 = 162.7f;
    if (arg2->y == temp_f2) {
        arg0->state.unk = 1;
        return arg0;
    }
    arg0->state.unk = 3;
    return arg0;
}

void ifMagnify_802FB8C0(HSD_GObj* arg0, s32 arg1)
{
    UNUSED u8 top_pad[8];
    S32Vec2 screen_pos;
    Vec2 out;
    Vec2 pos;
    Vec3 translate;
    GXColor color;
    GXColor color_copy;
    GXColor* cp;
    ifMagnifyPlayer* player;
    HSD_GObj* fighter_gobj;
    s32 slot;
    bool is_colored;
    bool should_display;
    s32 arrow_kind;
    u8 operand_pad[12];

    if (arg1 != 0) {
        return;
    }

    player = arg0->user_data;
    slot = player - ifMagnify_804A1DE0.player;
    is_colored = false;
    if ((gm_16AE_GetUnkData_0()->hud_enabled == 0) || ifAll_IsHUDHidden() ||
        Camera_80030130())
    {
        should_display = false;
    } else {
        should_display = true;
    }
    if (should_display && player->state.is_offscreen) {
        fighter_gobj = Player_GetEntity(slot);
        if (fighter_gobj != NULL) {
            ftLib_80086A58(fighter_gobj, &screen_pos);
            pos.x = screen_pos.x - 320.0f;
            pos.y = -((f32) screen_pos.y - 240.0f);

            HSD_JObjSetRotationZ(player->jobj, atan2f(pos.y, pos.x));

            ifMagnify_802FB73C(player, &pos, &out);
            translate.x = 0.09125f * out.x;
            translate.y = 0.1f * out.y;
            translate.z = 0.0f;
            HSD_JObjSetTranslate((HSD_JObj*) player->gobj->hsd_obj,
                                 &translate);

            HSD_GObj_JObjCallback(arg0, arg1);
            if ((player->state.unk == 4) || (player->state.unk == 2)) {
                ifMagnify_GetPlayerColor(&color, slot);
                cp = &color_copy;
                color_copy = color;
                if (player->state.unk == 2) {
                    arrow_kind = 1;
                } else {
                    arrow_kind = 2;
                }
                un_802FD928((u8) slot, arrow_kind, cp);
                is_colored = true;
            }
        }
    }
    if (!is_colored) {
        un_802FD9D8((u8) slot);
    }
}

static inline void ifMagnify_GetCornerColors(GXColor* colors, Vec3* world_pos)
{
    int j;
    u8* color_ids;
    f32 x_class;
    f32 y_class;

    for (j = 0; j < 4; j++) {
        if (world_pos->y > Stage_GetCamBoundsTopOffset()) {
            y_class = 0.0f;
        } else if (world_pos->y < Stage_GetCamBoundsBottomOffset()) {
            y_class = 3.0f;
        } else if (world_pos->y > (0.5f * (Stage_GetCamBoundsTopOffset() +
                                           Stage_GetCamBoundsBottomOffset())))
        {
            y_class = 1.0f;
        } else {
            y_class = 2.0f;
        }
        if (world_pos->x < Stage_GetCamBoundsLeftOffset()) {
            x_class = 0.0f;
        } else if (world_pos->x > Stage_GetCamBoundsRightOffset()) {
            x_class = 3.0f;
        } else if (world_pos->x < (0.5f * (Stage_GetCamBoundsLeftOffset() +
                                           Stage_GetCamBoundsRightOffset())))
        {
            x_class = 1.0f;
        } else {
            x_class = 2.0f;
        }
        color_ids = ifMagnify_803F984C[((s32) y_class * 4) + (s32) x_class];
        colors[j] = *ifMagnify_803F9828[color_ids[j]]();
    }
}

void ifMagnify_802FBBDC(HSD_GObj* arg0)
{
    UNUSED u8 top_pad[8];
    int i;
    ifMagnify* magnify;
    HSD_CObj* cobj;
    ifMagnifyPlayer* player;
    HSD_GObj* fighter_gobj;
    f32 top;
    f32 bottom;
    f32 left;
    f32 right;
    Vec3 interest_pos;
    GXColor result;
    GXColor colors[4];
    Vec3 world_pos;
    f32 x_blend;
    f32 y_blend;
    f32 x_inv;
    f32 y_inv;
    f32 scale;
    f32 x_class;
    f32 y_class;
    f32 mix0;
    f32 mix1;
    f32 mix2;
    f32 mix3;
    bool should_display;
    bool is_outside;

    magnify = &ifMagnify_804A1DE0;
    for (i = 0; i < 6; i++) {
        magnify->player[i].state.is_offscreen = 0;
    }

    if ((gm_16AE_GetUnkData_0()->hud_enabled == 0) || ifAll_IsHUDHidden() ||
        Camera_80030130())
    {
        should_display = false;
    } else {
        should_display = true;
    }
    if (should_display) {
        cobj = arg0->hsd_obj;
        HSD_CObjGetOrtho(cobj, &top, &bottom, &left, &right);
        if (HSD_CObjSetCurrent(cobj) != 0) {
            HSD_GObj_80390ED0(arg0, 7);
            HSD_CObjEndCurrent();
        }

        for (i = 0; i < 6; i++) {
            player = &magnify->player[i];
            fighter_gobj = Player_GetEntity(i);
            if (player->state.ignore_offscreen || fighter_gobj == NULL ||
                !ftLib_80086B64(fighter_gobj) || !ftLib_80086ED0(fighter_gobj))
            {
                continue;
            }

            scale = ftLib_80086B80(fighter_gobj) / 8.0f;
            HSD_CObjSetOrtho(cobj, top * scale, bottom * scale, left * scale,
                             right * scale);
            ftLib_80086B90(fighter_gobj, &interest_pos);
            HSD_CObjSetInterest(cobj, &interest_pos);
            interest_pos.z = 300.0f;
            HSD_CObjSetEyePosition(cobj, &interest_pos);
            if (HSD_CObjSetCurrent(cobj) == 0) {
                continue;
            }

            Player_80036978(i, (s32) &world_pos);
            is_outside = true;
            if (!(world_pos.x < Stage_GetCamBoundsLeftOffset()) &&
                !(world_pos.x > Stage_GetCamBoundsRightOffset()))
            {
                is_outside = false;
            }
            if (is_outside) {
                x_blend = 0.0f;
            } else {
                if (world_pos.x < Stage_GetCamBoundsLeftOffset()) {
                    x_class = 0.0f;
                } else if (world_pos.x > Stage_GetCamBoundsRightOffset()) {
                    x_class = 3.0f;
                } else if (world_pos.x <
                           (0.5f * (Stage_GetCamBoundsLeftOffset() +
                                    Stage_GetCamBoundsRightOffset())))
                {
                    x_class = 1.0f;
                } else {
                    x_class = 2.0f;
                }
                if (((s32) x_class - 1) == 0) {
                    x_blend = 1.0f -
                              ((world_pos.x - Stage_GetCamBoundsLeftOffset()) /
                               ((0.5f * (Stage_GetCamBoundsLeftOffset() +
                                         Stage_GetCamBoundsRightOffset())) -
                                Stage_GetCamBoundsLeftOffset()));
                } else {
                    x_blend =
                        1.0f - ((world_pos.x -
                                 (0.5f * (Stage_GetCamBoundsLeftOffset() +
                                          Stage_GetCamBoundsRightOffset()))) /
                                (Stage_GetCamBoundsRightOffset() -
                                 (0.5f * (Stage_GetCamBoundsLeftOffset() +
                                          Stage_GetCamBoundsRightOffset()))));
                }
            }
            x_inv = 1.0f - x_blend;
            is_outside = true;
            if (!(world_pos.y > Stage_GetCamBoundsTopOffset()) &&
                !(world_pos.y < Stage_GetCamBoundsBottomOffset()))
            {
                is_outside = false;
            }
            if (is_outside) {
                y_blend = 0.0f;
            } else {
                if (world_pos.y > Stage_GetCamBoundsTopOffset()) {
                    y_class = 0.0f;
                } else if (world_pos.y < Stage_GetCamBoundsBottomOffset()) {
                    y_class = 3.0f;
                } else if (world_pos.y >
                           (0.5f * (Stage_GetCamBoundsTopOffset() +
                                    Stage_GetCamBoundsBottomOffset())))
                {
                    y_class = 1.0f;
                } else {
                    y_class = 2.0f;
                }
                if (((s32) y_class - 1) == 0) {
                    y_blend =
                        1.0f - ((Stage_GetCamBoundsTopOffset() - world_pos.y) /
                                -((0.5f * (Stage_GetCamBoundsTopOffset() +
                                           Stage_GetCamBoundsBottomOffset())) -
                                  Stage_GetCamBoundsTopOffset()));
                } else {
                    y_blend =
                        1.0f - (((0.5f * (Stage_GetCamBoundsTopOffset() +
                                          Stage_GetCamBoundsBottomOffset())) -
                                 world_pos.y) /
                                ((0.5f * (Stage_GetCamBoundsTopOffset() +
                                          Stage_GetCamBoundsBottomOffset())) -
                                 Stage_GetCamBoundsBottomOffset()));
                }
            }
            y_inv = 1.0f - y_blend;
            (void) y_inv;
            ifMagnify_GetCornerColors(colors, &world_pos);

            y_blend = 1.0f - y_inv;
            x_blend = 1.0f - x_inv;
            mix0 = x_inv * y_blend;
            mix1 = x_blend * y_blend;
            mix2 = x_blend * y_inv;
            mix3 = x_inv * y_inv;
            result.a = (u8) ((colors[0].a * mix1) + (colors[1].a * mix0) +
                             (colors[2].a * mix2) + (colors[3].a * mix3));
            result.r = (u8) ((colors[0].r * mix1) + (colors[1].r * mix0) +
                             (colors[2].r * mix2) + (colors[3].r * mix3));
            result.g = (u8) ((colors[0].g * mix1) + (colors[1].g * mix0) +
                             (colors[2].g * mix2) + (colors[3].g * mix3));
            result.b = (u8) ((colors[0].b * mix1) + (colors[1].b * mix0) +
                             (colors[2].b * mix2) + (colors[3].b * mix3));

            HSD_SetEraseColor(result.r, result.g, result.b, result.a);
            HSD_CObjEraseScreen(cobj, 1, 0, 1);
            HSD_GObj_804D7814 = fighter_gobj;
            ftDrawCommon_80080C28(fighter_gobj, 0);
            ftDrawCommon_80080C28(fighter_gobj, 1);
            ftDrawCommon_80080C28(fighter_gobj, 2);
            HSD_GObj_804D7814 = NULL;
            lb_800122C8(player->idesc, 0, 0, true);
            HSD_CObjEndCurrent();
            player->state.is_offscreen = 1;
        }

        HSD_CObjSetOrtho(cobj, top, bottom, left, right);
    }
    PAD_STACK(4);
}

void ifMagnify_802FC3BC(void) {}

void ifMagnify_802FC3C0(s32 slot)
{
    ifMagnifyPlayer* player;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    HSD_JObj* child;
    HSD_MObj* mobj;

    player = &ifMagnify_804A1DE0.player[slot];
    if (player->gobj != NULL) {
        HSD_GObjPLink_80390228(player->gobj);
    }

    gobj = GObj_Create(HSD_GOBJ_CLASS_UI, 15, 0);
    GObj_InitUserData(gobj, 0xE, (void (*)(void*)) ifMagnify_802FC3BC, player);

    jobj = HSD_JObjLoadJoint(
        (*(DynamicModelDesc**) ifMagnify_804A1DE0.model_desc)->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, (void (*)(HSD_GObj*, int)) ifMagnify_802FB8C0, 0xB,
                     0);

    lb_80011E24(jobj, &child, 2, -1);
    if (slot == 0) {
        player->idesc = child->u.dobj->next->mobj->tobj->imagedesc;
    } else {
        ifMagnify* base = &ifMagnify_804A1DE0;

        base->image_descs[slot - 1] = *ifMagnify_804A1DE0.player[0].idesc;
        player->idesc =
            (base = (ifMagnify*) ((HSD_ImageDesc*) &ifMagnify_804A1DE0 +
                                  (slot - 1)))
                ->image_descs;
        player->idesc->image_ptr = HSD_MemAlloc(
            (GXGetTexBufferSize(player->idesc->width, player->idesc->height,
                                player->idesc->format, 0, 0) +
             0x1F) &
            ~0x1F);
        child->u.dobj->next->mobj->tobj->imagedesc = player->idesc;
    }

    lb_80011E24(jobj, &player->jobj, 1, -1);

    {
        GXColor color;
        ifMagnify_GetPlayerColor(&color, slot);

        mobj = player->jobj->u.dobj->mobj;
        mobj->mat->diffuse.r = color.r;
        mobj->mat->diffuse.g = color.g;
        mobj->mat->diffuse.b = color.b;

        mobj = child->u.dobj->mobj;
        mobj->mat->diffuse.r = color.r;
        mobj->mat->diffuse.g = color.g;
        mobj->mat->diffuse.b = color.b;
    }

    player->gobj = gobj;
    player->state.is_offscreen = 0;
    player->state.ignore_offscreen = 0;
}

void ifMagnify_802FC618(void)
{
    ifMagnifyPlayer* player0 = &ifMagnify_804A1DE0.player[0];
    HSD_GObj* gobj;
    HSD_CObj* cobj;
    HSD_ImageDesc* idesc;
    f32 half_height;
    f32 half_width;
    int pad;
    HSD_RectS16 viewport;

    gobj = GObj_Create(HSD_GOBJ_CLASS_UI, 15, 0);
    cobj = lb_80013B14((HSD_CameraDescPerspective*) &ifMagnify_803F97E8);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, (GObj_RenderFunc) (Event) ifMagnify_802FBBDC, 0);
    gobj->gxlink_prios = 0x10;

    idesc = player0->idesc;
    half_height = 0.1f * idesc->height;
    half_width = 0.1f * idesc->width;
    HSD_CObjSetOrtho(cobj, half_height, -half_height, -half_width, half_width);

    viewport.xmin = 0;
    viewport.xmax = player0->idesc->width;
    viewport.ymin = 0;
    viewport.ymax = player0->idesc->height;
    HSD_CObjSetViewport(cobj, &viewport);
    HSD_CObjSetScissorx4(cobj, (u16) viewport.xmin, (u16) viewport.xmax,
                         (u16) viewport.ymin, (u16) viewport.ymax);
}

void ifMagnify_802FC750(void)
{
    ifMagnify* base = &ifMagnify_804A1DE0;
    s32 i;

    for (i = 0; i < 6; i++) {
        if (*(HSD_GObj**) ((u8*) base + (i << 4) + 0x14) != NULL) {
            HSD_GObjPLink_80390228(
                *(HSD_GObj**) ((u32) base + (i << 4) + 0x14));
            *(HSD_GObj**) ((u32) base + (i << 4) + 0x14) = NULL;
        }
    }
}

void ifMagnify_802FC7C0(ifMagnify* magnify)
{
    volatile int default_val = *(volatile int*) &ifMagnify_804DDB60;
    GXColor* result;

    result = Ground_801C0604();
    if (result != NULL) {
        magnify->x4 = *(int*) result;
    } else {
        magnify->x4 = default_val;
    }

    result = Ground_801C0618();
    if (result != NULL) {
        magnify->x8 = *(int*) result;
    } else {
        magnify->x8 = default_val;
    }

    result = Ground_801C062C();
    if (result != NULL) {
        magnify->xC = *(int*) result;
    } else {
        magnify->xC = default_val;
    }

    result = Ground_801C0640();
    if (result != NULL) {
        magnify->x10 = *(int*) result;
    } else {
        magnify->x10 = default_val;
    }
}

void ifMagnify_802FC870(void)
{
    HSD_Archive** archive;
    s32 i;

    memzero(&ifMagnify_804A1DE0, 0x74);
    ifMagnify_802FC7C0(&ifMagnify_804A1DE0);
    archive = ifAll_GetArchive();
    lbArchive_LoadSections(*archive, (void**) &ifMagnify_804A1DE0,
                           ifMagnify_804D57E8, 0);
    i = 0;
    do {
        ifMagnify_802FC3C0(i);
        i++;
    } while (i < 6);
    ifMagnify_802FC618();
}

void ifMagnify_802FC8E8(void)
{
    int i;
    for (i = 0; i < 6; i++) {
        ifMagnify_804A1DE0.player[i].state.ignore_offscreen = 1;
    }
}

void ifMagnify_802FC940(void)
{
    int i;
    for (i = 0; i < 6; i++) {
        ifMagnify_804A1DE0.player[i].state.ignore_offscreen = 0;
    }
}

bool ifMagnify_802FC998(s32 ply_slot)
{
    return ifMagnify_804A1DE0.player[ply_slot].state.is_offscreen;
}
