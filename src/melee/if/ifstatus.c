#include "if/ifstatus.h"

#include "ifall.h"

#include "gm/gm_1601.h"
#include "gm/types.h"
#include "if/if_2F72.h"
#include "if/ifstock.h"
#include "if/types.h"
#include "pl/player.h"

#include <placeholder.h>
#include <baselib/gobj.h>
#include <baselib/gobjplink.h>

Thing_803F9628 ifStatus_803F9628;
s8 ifStatus_804D6D60;

HudIndex* ifStatus_802F4910(void)
{
    return &ifStatus_HudInfo;
}

void ifStatus_802F491C(void)
{
    NOT_IMPLEMENTED;
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

inline HudValue* getPlayerByHUDParent(HSD_GObj* parent)
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
        HSD_GObj_80391070(player, arg1);
    }
}

void ifStatus_802F5E50(void)
{
    NOT_IMPLEMENTED;
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

void ifStatus_802F6508(s32 arg0)
{
    NOT_IMPLEMENTED;
}

void ifStatus_802F665C(s8 arg0)
{
    s32 i;

    ifAll_802F343C();
    ifStatus_804D6D60 = arg0;
    for (i = 0; i < 6; i++) {
        ifStatus_802F6508(i);
    }
}

void ifStatus_802F66A4(void)
{
    NOT_IMPLEMENTED;
}

void ifStatus_802F6788(s32 player_idx)
{
    HudValue* player_hud;
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
    HudValue* v;

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
    HudValue* hud_player;
    Placeholder_8016AE50_ret_val* small_thing;
    HudFlags* hud_player_flags;

    small_thing = gm_8016AE50();
    hud_player = &ifStatus_HudInfo.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->unk40 = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
}

void ifStatus_802F69C0(s32 player_idx, s32 arg1)
{
    HudValue* hud_player;
    HudFlags* hud_player_flags;
    Placeholder_8016AE38_ret_val* big_thing;
    Placeholder_8016AE50_ret_val* small_thing;

    big_thing = gm_8016AE38();
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0)) {
        if_802F7C30(arg1);
    }

    big_thing = gm_8016AE38();
    big_thing->unkD = player_idx;
    small_thing = gm_8016AE50();
    hud_player = &ifStatus_HudInfo.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->unk40 = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->unk24CA.unk80 != 0) &&
        ((Player_GetPlayerSlotType(player_idx) == 0) ||
         (Player_GetPlayerSlotType(player_idx) == 1)) &&
        (Player_GetStocks(player_idx) == 0))
    {
        gm_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx) & 0xFF);
    }

    /// @todo Weird check on a known function addr
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0) &&
        (&if_802F7BB4 != NULL))
    {
        if_802F7BB4(player_idx);
    }
}

void ifStatus_802F6AF8(s32 player_idx)
{
    HudValue* hud_player;
    Placeholder_8016AE38_ret_val* big_thing;
    Placeholder_8016AE50_ret_val* small_thing;
    HudFlags* hud_player_flags;

    big_thing = gm_8016AE38();
    big_thing->unkD = player_idx;
    small_thing = gm_8016AE50();
    hud_player = &ifStatus_HudInfo.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->unk40 = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->unk24CA.unk80 != 0) &&
        ((Player_GetPlayerSlotType(player_idx) == 0) ||
         (Player_GetPlayerSlotType(player_idx) == 1)) &&
        (Player_GetStocks(player_idx) == 0))
    {
        gm_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx) & 0xFF);
    }

    /// @todo Weird check on a known function addr
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0) &&
        (&if_802F7AF8 != NULL))
    {
        if_802F7AF8(player_idx);
    }
}

void ifStatus_802F6C04(s32 player_idx)
{
    HudValue* hud_player;
    HudFlags* hud_player_flags;
    Placeholder_8016AE38_ret_val* big_thing;
    Placeholder_8016AE50_ret_val* small_thing;

    big_thing = gm_8016AE38();
    big_thing->unkD = player_idx;
    small_thing = gm_8016AE50();
    hud_player = &ifStatus_HudInfo.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->unk40 = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->unk24CA.unk80 != 0) &&
        ((Player_GetPlayerSlotType(player_idx) == 0) ||
         (Player_GetPlayerSlotType(player_idx) == 1)) &&
        (Player_GetStocks(player_idx) == 0))
    {
        gm_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx) & 0xFF);
    }

    /// @todo Weird check on a known function addr
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0) &&
        (&if_802F7C30 != NULL))
    {
        if_802F7C30(player_idx);
    }
}

void ifStatus_802F6D10(s32 player_idx)
{
    HudValue* hud_player;
    Placeholder_8016AE38_ret_val* big_thing;
    Placeholder_8016AE50_ret_val* small_thing;
    HudFlags* hud_player_flags;

    big_thing = gm_8016AE38();
    big_thing->unkD = player_idx;
    small_thing = gm_8016AE50();
    hud_player = &ifStatus_HudInfo.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->unk40 = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->unk24CA.unk80 != 0) &&
        ((Player_GetPlayerSlotType(player_idx) == 0) ||
         (Player_GetPlayerSlotType(player_idx) == 1)) &&
        (Player_GetStocks(player_idx) == 0))
    {
        gm_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx) & 0xFF);
    }

    /// @todo Weird check on a known function addr
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0) &&
        (&if_802F7D08 != NULL))
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
    HudValue* player;

    player = &ifStatus_HudInfo.players[player_num];
    if (player->HUD_parent_entity != NULL) {
        HSD_GObj_80390CAC(player->HUD_parent_entity);
    }
    if (player->next != NULL) {
        HSD_GObj_80390CAC(player->next);
    }
    ifStock_802FB6AC(player_num);
}

void ifStatus_802F6EA4(void)
{
    NOT_IMPLEMENTED;
}

void ifStatus_802F7034(void)
{
    NOT_IMPLEMENTED;
}

void ifStatus_802F7134(void)
{
    NOT_IMPLEMENTED;
}

// free
void ifStatus_802F7220(void)
{
    s32 i;
    for (i = 0; i < 8; i++) {
        if (ifStatus_803F9628.things[i].unk0 != NULL) {
            HSD_GObjPLink_80390228(ifStatus_803F9628.things[i].unk0);
            ifStatus_803F9628.things[i].unk0 = NULL;
        }
    }
}
