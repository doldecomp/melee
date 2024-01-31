#include "plstale.h"

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
