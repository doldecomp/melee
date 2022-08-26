#include <melee/if/ifstatus.h>

void func_802F6788(s32 player_idx)
{
    HudValue* player_hud;
    s8 p_idx = (u8) player_idx;
    player_hud = &lbl_804A10C8.players[p_idx & 0xFF];
    if (player_hud->HUD_parent_entity != NULL) {
        func_80390228(player_hud->HUD_parent_entity);
        player_hud->HUD_parent_entity = NULL;
    }
    if (player_hud->next != NULL) {
        func_80390228(player_hud->next);
        player_hud->next = NULL;
    }
    func_802FB650(player_idx & 0xFF);
}

void func_802F6804(void)
{
    s32 i;
    HudValue* v;

    i = 0;
    do {
        v = &lbl_804A10C8.players[i & 0xFF];
        if (v->HUD_parent_entity != NULL) {
            func_80390228(v->HUD_parent_entity);
            v->HUD_parent_entity = NULL;
        }
        if (v->next != NULL) {
            func_80390228(v->next);
            v->next = NULL;
        }
        func_802FB650((s8) i & 0xFF);
        i++;
    } while (i < 6);
}

// Hide Percentage Digits
void func_802F6898()
{
    s32 i;
    HudIndex* v = &lbl_804A10C8;
    for (i = 0; i < 6; i++) {
        v->players[i].flags.hide_all_digits = 1;
    }
}

// Show All Percentage Digits
void func_802F68F0(void)
{
    s32 i;
    HudIndex* v = &lbl_804A10C8;
    for (i = 0; i < 6; i++) {
        v->players[i].flags.hide_all_digits = 0;
    }
}

void func_802F6948(s32 player_idx)
{
    HudValue* hud_player;
    Placeholder_8016AE50_ret_val* small_thing;
    HudFlags* hud_player_flags;

    small_thing = func_8016AE50();
    hud_player = &lbl_804A10C8.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->unk40 = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
}

void func_802F69C0(s32 player_idx, s32 arg1)
{
    HudValue* hud_player;
    HudFlags* hud_player_flags;
    Placeholder_8016AE38_ret_val* big_thing;
    Placeholder_8016AE50_ret_val* small_thing;

    big_thing = func_8016AE38();
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0)) {
        func_802F7C30(arg1);
    }

    big_thing = func_8016AE38();
    big_thing->unkD = player_idx;
    small_thing = func_8016AE50();
    hud_player = &lbl_804A10C8.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->unk40 = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->unk24CA.unk80 != 0) && ((Player_GetPlayerSlotType(player_idx) == 0) || (Player_GetPlayerSlotType(player_idx) == 1)) && (Player_GetStocks(player_idx) == 0)) {
        func_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx) & 0xFF);
    }
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0) && (func_802F7BB4 != NULL)) {
        func_802F7BB4(player_idx);
    }
}

void func_802F6AF8(s32 player_idx)
{
    HudValue* hud_player;
    Placeholder_8016AE38_ret_val* big_thing;
    Placeholder_8016AE50_ret_val* small_thing;
    HudFlags* hud_player_flags;

    big_thing = func_8016AE38();
    big_thing->unkD = player_idx;
    small_thing = func_8016AE50();
    hud_player = &lbl_804A10C8.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->unk40 = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->unk24CA.unk80 != 0) && ((Player_GetPlayerSlotType(player_idx) == 0) || (Player_GetPlayerSlotType(player_idx) == 1)) && (Player_GetStocks(player_idx) == 0)) {
        func_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx) & 0xFF);
    }
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0) && (func_802F7AF8 != NULL)) {
        func_802F7AF8(player_idx);
    }
}

void func_802F6C04(s32 player_idx)
{
    HudValue* hud_player;
    HudFlags* hud_player_flags;
    Placeholder_8016AE38_ret_val* big_thing;
    Placeholder_8016AE50_ret_val* small_thing;

    big_thing = func_8016AE38();
    big_thing->unkD = player_idx;
    small_thing = func_8016AE50();
    hud_player = &lbl_804A10C8.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->unk40 = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->unk24CA.unk80 != 0) && ((Player_GetPlayerSlotType(player_idx) == 0) || (Player_GetPlayerSlotType(player_idx) == 1)) && (Player_GetStocks(player_idx) == 0)) {
        func_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx) & 0xFF);
    }
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0) && (func_802F7C30 != NULL)) {
        func_802F7C30(player_idx);
    }
}

void func_802F6D10(s32 player_idx)
{
    HudValue* hud_player;
    Placeholder_8016AE38_ret_val* big_thing;
    Placeholder_8016AE50_ret_val* small_thing;
    HudFlags* hud_player_flags;

    big_thing = func_8016AE38();
    big_thing->unkD = player_idx;
    small_thing = func_8016AE50();
    hud_player = &lbl_804A10C8.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->unk40 = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->unk24CA.unk80 != 0) && ((Player_GetPlayerSlotType(player_idx) == 0) || (Player_GetPlayerSlotType(player_idx) == 1)) && (Player_GetStocks(player_idx) == 0)) {
        func_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx) & 0xFF);
    }
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0) && (func_802F7D08 != NULL)) {
        func_802F7D08(player_idx);
    }
}

void func_802F6E1C(s32 player_num)
{
    func_802F6508(player_num);
}

void func_802F6E3C(s32 player_num)
{
    HudValue* player;

    player = &lbl_804A10C8.players[player_num];
    if (player->HUD_parent_entity != NULL) {
        func_80390CAC(player->HUD_parent_entity);
    }
    if (player->next != NULL) {
        func_80390CAC(player->next);
    }
    func_802FB6AC(player_num);
}
