#include "ifstatus.h"

#include "ifall.h"
#include "m2c_macros.h"
#include "placeholder.h"

#include "gm/gm_unsplit.h"
#include "gm/types.h"
#include "if/if_2F72.h"
#include "if/ifstock.h"
#include "if/types.h"
#include "lb/lbarchive.h"
#include "pl/player.h"
#include "sc/types.h"

#include <baselib/gobj.h>
#include <baselib/gobjplink.h>
#include <baselib/mtx.h>
#include <baselib/random.h>

typedef struct FlagsX {
    u32 b80 : 1;
    u32 b40 : 1;
    u32 b20 : 1;
    u32 b10 : 1;
    u32 b8 : 1;
    u32 b4 : 2;
    u32 b1 : 1;
    u8 x;
    u16 y;
} FlagsX;

typedef struct UnkX {
    u8 filler1[0x10];
    FlagsX x10_flags;
    u8 filler2[0x34 - 0x14];
    Vec4 x34_vec; // or float[4] instead of Vec4
    Vec4 x44_vec;
    HSD_JObj* x54_jobj[4];
} UnkX; // HudIndex

/* 2F491C */ static void ifStatus_PercentOnDeathAnimationThink(UnkX* value,
                                                               s32, s32);
/* 3F9628 */ Element_803F9628 ifStatus_803F9628[8] = {
    { NULL, 0, if_802F74D0, 0x7C860U, 8, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F73C4, 0xC351U, 0, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F74D0, 0x7C85EU, 0, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F73C4, 0x7C85DU, 0, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F73C4, 0x7C857U, 10, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F74D0, 0x7C855U, 8, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F74D0, 0x9C48U, 0, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F74D0, 0x9C46U, 0, 0, { 0 }, 0, NULL, NULL, 0, 0 },
};
/* 4D6D60 */ static u8 ifStatus_804D6D60;
/* 4D6D61 */ static s8 ifStatus_804D6D61;

HudIndex* ifStatus_802F4910(void)
{
    return &ifStatus_HudInfo;
}

// "jobj.h" @ lbl_804D57B0
// "jobj" @ lbl_804D57B8
#define ASSERT_NOT_NULL(value, line)                                          \
    if (value == NULL) {                                                      \
        __assert("jobj.h", line, "jobj");                                     \
    }

static inline float foo(float a, float b)
{
    float result;
    if (ifStatus_804D6D61 != 0) {
        result = -a - b;
        ifStatus_804D6D61 = 0;
    } else {
        result = a + b;
        ifStatus_804D6D61 = 1;
    }
    return result;
}

static inline void
jobj_flagCheckSetMtxDirtySub(HSD_JObj* jobj) // jobj @ r30 when inlined
{
    //@12c
    if (!(jobj->flags & 0x02000000) && jobj) {
        //@140
        ASSERT_NOT_NULL(jobj, 0x234);
        //@154
        if ((!(jobj->flags & 0x800000) && (jobj->flags & 0x40)) == 0) {
            //@178
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

inline void jobj_translate_x(HSD_JObj* jobj, float dx);
inline void jobj_translate_y(HSD_JObj* jobj, float dy);

inline void jobj_unk_x(UnkX* value, s32 i)
{
    HSD_JObj* jobj_r30 = value->x54_jobj[i];
    //@c8
    ASSERT_NOT_NULL(jobj_r30, 993);
    //@e0
    if (fabsf_bitwise(jobj_r30->translate.x) < 100.0f)
    { // 100.0f @ lbl_804DDA6C
        //@100
        jobj_r30 = value->x54_jobj[i];
        //@108
        jobj_translate_x(jobj_r30, (&value->x34_vec.x)[i]);
        //@12c
        jobj_flagCheckSetMtxDirtySub(jobj_r30);
    }
}

inline void jobj_unk_y(UnkX* value, s32 i)
{
    HSD_JObj* jobj_r30 = value->x54_jobj[i];
    //@184
    ASSERT_NOT_NULL(jobj_r30, 1006);
    //@19c
    if (jobj_r30->translate.y > -100.0f) { // -100.0f @ lbl_804DDA8C
        //@1a8
        jobj_r30 = value->x54_jobj[i];
        //@1b0
        jobj_translate_y(jobj_r30, (&value->x44_vec.x)[i]);

        //@1d4
        jobj_flagCheckSetMtxDirtySub(jobj_r30);
        //@228
        (&value->x44_vec.x)[i] -= 0.2028f; // gravity that makes percent tokens
                                           // fall down? @ lbl_804DDA90
    }
}

inline void jobj_translate_x(HSD_JObj* jobj, float dx)
{
    //@108
    ASSERT_NOT_NULL(jobj, 1102);
    //@120
    jobj->translate.x += dx;
}

inline void jobj_translate_y(HSD_JObj* jobj, float dy)
{
    //@1b0
    ASSERT_NOT_NULL(jobj, 1114);
    //@1c8
    jobj->translate.y += dy;
}

inline void jobj_unk(UnkX* value)
{
    //@b0
    s32 i;
    for (i = 0; i < 4; i++) // i@r31
    {
        jobj_unk_x(value, i);
        jobj_unk_y(value, i);
        //@234 loop increment
    }
}

inline void* jobj_get(HSD_JObj* jobj_r30, UnkX* value, s32 i)
{
    return value->x54_jobj[i];
}

void ifStatus_PercentOnDeathAnimationThink(UnkX* value, s32 arg1, s32 arg2)
{
    s32 i;

    if (value->x10_flags.b40) {
        for (i = 0; i < 4; i++) // i@r28
        {
            (&value->x34_vec.x)[i] =
                foo(0.6083f * HSD_Randf(), 0.3041f); // var_f0;
            (&value->x44_vec.x)[i] = 0.811f * HSD_Randf() + 1.2165f;
        }
        value->x10_flags.b40 = 0;
        return;
    }

    for (i = 0; i < 4; i++) // i@r31
    {
        HSD_JObj* jobj_r30 = value->x54_jobj[i];
        ASSERT_NOT_NULL(jobj_r30, 993);
        if (fabsf_bitwise(jobj_r30->translate.x) < 100.0f)
        { // 100.0f @ lbl_804DDA6C
            float f = (&value->x34_vec.x)[i];
            jobj_r30 = (void*) jobj_get(jobj_r30, value, i);
            ASSERT_NOT_NULL(jobj_r30, 1102);
            jobj_r30->translate.x += f;
            jobj_flagCheckSetMtxDirtySub(jobj_r30);
        }
        jobj_r30 = (void*) jobj_get(jobj_r30, value, i);
        ASSERT_NOT_NULL(jobj_r30, 1006);

        if (jobj_r30->translate.y > -100.0f) {
            float f = (&value->x44_vec.x)[i];
            jobj_r30 = (void*) jobj_get(jobj_r30, value, i);
            jobj_r30 = (void*) jobj_get(jobj_r30, value, i);
            ASSERT_NOT_NULL(jobj_r30, 1114);
            jobj_r30->translate.y += f;
            jobj_flagCheckSetMtxDirtySub(jobj_r30);
            (&value->x44_vec.x)[i] -= 0.2028f; // @ lbl_804DDA90
        }
    }
}

void ifStatus_802F4B84(void)
{
    NOT_IMPLEMENTED;
}

void ifStatus_802F4EDC(void)
{
    NOT_IMPLEMENTED;
}

void ifStatus_802F5B48(void)
{
    NOT_IMPLEMENTED;
}

inline IfDamageState* getPlayerByHUDParent(HSD_GObj* parent)
{
    s32 var_ctr;
    for (var_ctr = 0; var_ctr < 6; var_ctr++) {
        if (ifStatus_HudInfo.players[var_ctr].HUD_parent_entity == parent) {
            return &ifStatus_HudInfo.players[var_ctr];
        }
    }
    return NULL;
}

void ifStatus_802F5DE0(HSD_GObj* player, s32 arg1)
{
    if (!getPlayerByHUDParent(player)->flags.hide_all_digits) {
        HSD_GObj_JObjCallback(player, arg1);
    }
}

static inline IfDamageState* getPlayerByNext(HSD_GObj* gobj)
{
    s32 i;
    for (i = 0; i < 6; i++) {
        if (ifStatus_HudInfo.players[i].next == gobj) {
            return &ifStatus_HudInfo.players[i];
        }
    }
    return NULL;
}

void ifStatus_802F5E50(HSD_GObj* gobj, s32 arg1)
{
    IfDamageState* player = getPlayerByNext(gobj);
    if (!player->flags.hide_all_digits) {
        HSD_GObj_JObjCallback(gobj, arg1);
    }
}

void ifStatus_802F5EC0(void)
{
    NOT_IMPLEMENTED;
}

static inline HSD_GObj* nth_node(HSD_GObj* node, s32 n)
{
    s32 i;
    HSD_GObj* cur = node;
    for (i = 0; i < n && node; i++) {
        if (cur == NULL) { // if (node == NULL)
            cur = NULL;
        } else {
            cur = node->next;
        }
        node = cur;
    }
    return node;
}

// 99.81% match
// https://decomp.me/scratch/XGFpw
HSD_GObj* ifStatus_802F6194(HSD_GObj* node, s32 n)
{
    HSD_GObj* gx;

    if ((node == NULL) || (n < 0)) {
        return NULL;
    }
    if (node == NULL) {
        gx = NULL;
    } else {
        gx = node->next_gx;
    }
    gx = nth_node(gx, n);
    return gx;
}

void ifStatus_802F61FC(void)
{
    NOT_IMPLEMENTED;
}

void ifStatus_802F6508(s32 arg0);

void ifStatus_802F665C(int arg0)
{
    int i;

    ifAll_802F343C(arg0);
    ifStatus_804D6D60 = arg0;
    for (i = 0; i < 6; i++) {
        ifStatus_802F6508(i);
    }
}

void ifStatus_802F66A4(void)
{
    NOT_IMPLEMENTED;
}

void ifStatus_802F6788(u8 player_idx)
{
    IfDamageState* player_hud;
    s8 p_idx = (u8) player_idx;
    player_hud = &ifStatus_HudInfo.players[p_idx & 0xFF];
    if (player_hud->HUD_parent_entity != NULL) {
        HSD_GObjPLink_80390228(player_hud->HUD_parent_entity);
        player_hud->HUD_parent_entity = NULL;
    }
    if (player_hud->next != NULL) {
        HSD_GObjPLink_80390228(player_hud->next);
        player_hud->next = NULL;
    }
    ifStock_802FB650(player_idx & 0xFF);
}

void ifStatus_802F6804(void)
{
    s32 i;
    IfDamageState* v;

    i = 0;
    do {
        v = &ifStatus_HudInfo.players[i & 0xFF];
        if (v->HUD_parent_entity != NULL) {
            HSD_GObjPLink_80390228(v->HUD_parent_entity);
            v->HUD_parent_entity = NULL;
        }
        if (v->next != NULL) {
            HSD_GObjPLink_80390228(v->next);
            v->next = NULL;
        }
        ifStock_802FB650((s8) i & 0xFF);
        i++;
    } while (i < 6);
}

// Hide Percentage Digits
void ifStatus_802F6898(void)
{
    s32 i;
    HudIndex* v = &ifStatus_HudInfo;
    for (i = 0; i < 6; i++) {
        v->players[i].flags.hide_all_digits = 1;
    }
}

// Show All Percentage Digits
void ifStatus_802F68F0(void)
{
    s32 i;
    HudIndex* v = &ifStatus_HudInfo;
    for (i = 0; i < 6; i++) {
        v->players[i].flags.hide_all_digits = 0;
    }
}

void ifStatus_802F6948(s32 player_idx)
{
    IfDamageState* hud_player;
    struct StartMeleeRules* small_thing;
    IfDamageFlags* hud_player_flags;

    small_thing = gm_8016AE50();
    hud_player = &ifStatus_HudInfo.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->randomize_velocity = 1;
        if (small_thing->x2_7 != 0) {
            hud_player->unk9 = 1;
        }
    }
}

void ifStatus_802F69C0(s32 player_idx, s32 arg1)
{
    IfDamageState* hud_player;
    IfDamageFlags* hud_player_flags;
    lbl_8046B6A0_t* big_thing;
    struct StartMeleeRules* small_thing;

    big_thing = gm_8016AE38();
    if (big_thing->x24C8.x0_0 != 1 && big_thing->x24C8.x2_5 != 0) {
        if_802F7C30(arg1);
    }

    big_thing = gm_8016AE38();
    big_thing->unk_D = player_idx;
    small_thing = gm_8016AE50();
    hud_player = &ifStatus_HudInfo.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->randomize_velocity = 1;
        if (small_thing->x2_7 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->x24C8.x2_0 != 0) &&
        ((Player_GetPlayerSlotType(player_idx) == Gm_PKind_Human) ||
         (Player_GetPlayerSlotType(player_idx) == Gm_PKind_Cpu)) &&
        (Player_GetStocks(player_idx) == 0))
    {
        gm_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx));
    }

    /// @todo Inline with callback arg
    if (big_thing->x24C8.x0_0 != 1 && big_thing->x24C8.x2_5 != 0 &&
        &if_802F7BB4 != NULL)
    {
        if_802F7BB4(player_idx);
    }
}

void ifStatus_802F6AF8(s32 player_idx)
{
    IfDamageState* hud_player;
    lbl_8046B6A0_t* big_thing;
    struct StartMeleeRules* small_thing;
    IfDamageFlags* hud_player_flags;

    big_thing = gm_8016AE38();
    big_thing->unk_D = player_idx;
    small_thing = gm_8016AE50();
    hud_player = &ifStatus_HudInfo.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->randomize_velocity = 1;
        if (small_thing->x2_7 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->x24C8.x2_0 != 0) &&
        ((Player_GetPlayerSlotType(player_idx) == Gm_PKind_Human) ||
         (Player_GetPlayerSlotType(player_idx) == Gm_PKind_Cpu)) &&
        (Player_GetStocks(player_idx) == 0))
    {
        gm_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx));
    }

    /// @todo Inline with callback arg
    if (big_thing->x24C8.x0_0 != 1 && big_thing->x24C8.x2_5 != 0 &&
        &if_802F7AF8 != NULL)
    {
        if_802F7AF8(player_idx);
    }
}

void ifStatus_802F6C04(s32 player_idx)
{
    IfDamageState* hud_player;
    IfDamageFlags* hud_player_flags;
    lbl_8046B6A0_t* big_thing;
    struct StartMeleeRules* small_thing;

    big_thing = gm_8016AE38();
    big_thing->unk_D = player_idx;
    small_thing = gm_8016AE50();
    hud_player = &ifStatus_HudInfo.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->randomize_velocity = 1;
        if (small_thing->x2_7 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->x24C8.x2_0 != 0) &&
        ((Player_GetPlayerSlotType(player_idx) == Gm_PKind_Human) ||
         (Player_GetPlayerSlotType(player_idx) == Gm_PKind_Cpu)) &&
        (Player_GetStocks(player_idx) == 0))
    {
        gm_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx));
    }

    /// @todo Inline with callback arg
    if (big_thing->x24C8.x0_0 != 1 && big_thing->x24C8.x2_5 != 0 &&
        &if_802F7C30 != NULL)
    {
        if_802F7C30(player_idx);
    }
}

void ifStatus_802F6D10(s32 player_idx)
{
    IfDamageState* hud_player;
    lbl_8046B6A0_t* big_thing;
    struct StartMeleeRules* small_thing;
    IfDamageFlags* hud_player_flags;

    big_thing = gm_8016AE38();
    big_thing->unk_D = player_idx;
    small_thing = gm_8016AE50();
    hud_player = &ifStatus_HudInfo.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->randomize_velocity = 1;
        if (small_thing->x2_7 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->x24C8.x2_0 != 0) &&
        ((Player_GetPlayerSlotType(player_idx) == Gm_PKind_Human) ||
         (Player_GetPlayerSlotType(player_idx) == Gm_PKind_Cpu)) &&
        (Player_GetStocks(player_idx) == 0))
    {
        gm_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx));
    }

    /// @todo Inline with callback arg
    if (big_thing->x24C8.x0_0 != 1 && big_thing->x24C8.x2_5 != 0 &&
        &if_802F7D08 != NULL)
    {
        if_802F7D08(player_idx);
    }
}

void ifStatus_802F6E1C(int slot)
{
    ifStatus_802F6508(slot);
}

void ifStatus_802F6E3C(s32 player_num)
{
    IfDamageState* player;

    player = &ifStatus_HudInfo.players[player_num];
    if (player->HUD_parent_entity != NULL) {
        HSD_GObj_80390CAC(player->HUD_parent_entity);
    }
    if (player->next != NULL) {
        HSD_GObj_80390CAC(player->next);
    }
    ifStock_802FB6AC(player_num);
}

/// #ifStatus_802F6EA4

/// #ifStatus_802F7034

void ifStatus_802F7134(void)
{
    u8 _[8];
    HSD_Archive** archive;
    DynamicModelDesc** volatile models;
    int i;

    for (i = 0; i < 8; i++) {
        ifStatus_803F9628[i].x0 = NULL;
        ifStatus_803F9628[i].x4 = 0;
    }

    archive = ifAll_802F3690();
    lbArchive_LoadSections(*archive, (void**) &models, "ScInfCnt_scene_models",
                           0);

    for (i = 0; i < 8; i++) {
        ifStatus_803F9628[i].x14 = models[i];
    }
}

// free
void ifStatus_802F7220(void)
{
    s32 i;
    for (i = 0; i < 8; i++) {
        if (ifStatus_803F9628[i].x0 != NULL) {
            HSD_GObjPLink_80390228(ifStatus_803F9628[i].x0);
            ifStatus_803F9628[i].x0 = NULL;
        }
    }
}
