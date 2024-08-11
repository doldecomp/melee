#include "plstale.h"

#include "ft/inlines.h"
#include "ft/types.h"
#include "pl/player.h"
#include "pl/types.h"

u16 unk_804D6478;

void plStale_8003715C(void)
{
    unk_804D6478 = 1;
}

void plStale_80037168(s32 slot)
{
    int i;
    StaleMoveTable* stale_table = Player_GetStaleMoveTableIndexPtr(slot);
    stale_table->current_index = 0;
    for (i = 0; i < 10; i++) {
        stale_table->StaleMoves[i].move_id = 0;
        stale_table->StaleMoves[i].num_action_states = 0;
    }
}

u16 plStale_80037208(void)
{
    u16 before = unk_804D6478;
    unk_804D6478 += 1;
    if (unk_804D6478 == 0) {
        unk_804D6478 = 1;
    }
    return before;
}

void plStale_8003722C(HSD_GObj* gobj, HSD_GObj* gobj_2)
{
    int i;
    s32 attack_id;
    u16 num_states;
    StaleMoveTable* smtp;

    if (gobj != gobj_2) {
        Fighter* ft = GET_FIGHTER(gobj);

        num_states = ft->x206C_num_action_states;
        attack_id = ft->x2068_attackID;
        smtp = Player_GetStaleMoveTableIndexPtr(ft->player_id);
        if (attack_id != 1) {
            for (i = 0; i < 10; i++) {
                if (attack_id == smtp->StaleMoves[i].move_id &&
                    num_states == smtp->StaleMoves[i].num_action_states)
                {
                    return;
                }
            }
            smtp->StaleMoves[smtp->current_index].move_id = attack_id;
            smtp->StaleMoves[smtp->current_index].num_action_states =
                num_states;
            smtp->current_index =
                smtp->current_index == 9 ? 0 : smtp->current_index + 1;
        }
    }
}
