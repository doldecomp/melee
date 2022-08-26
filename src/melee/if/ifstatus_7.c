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
