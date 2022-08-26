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
