#include "plstale.h"

#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "it/inlines.h"
#include "it/types.h"
#include "pl/player.h"
#include "pl/types.h"

u16 staleAttackInstance;

void plStale_InitAttackInstance(void)
{
    staleAttackInstance = 1;
}

void plStale_80037168(s32 slot)
{
    int i;
    StaleMoveTable* stale_table = Player_GetStaleMoveTableIndexPtr(slot);
    stale_table->current_index = 0;
    for (i = 0; i < 10; i++) {
        stale_table->StaleMoves[i].move_id = 0;
        stale_table->StaleMoves[i].attack_instance = 0;
    }
}

u16 plStale_IncrementAttackInstance(void)
{
    u16 before = staleAttackInstance;
    staleAttackInstance += 1;
    if (staleAttackInstance == 0) {
        staleAttackInstance = 1;
    }
    return before;
}

void plStale_UpdateStaleMovesFromFighter(HSD_GObj* gobj, HSD_GObj* gobj_2)
{
    int i;
    s32 attack_id;
    u16 instance;
    StaleMoveTable* smtp;

    if (gobj != gobj_2) {
        Fighter* ft = GET_FIGHTER(gobj);

        instance = ft->x206C_attack_instance;
        attack_id = ft->x2068_attackID;
        smtp = Player_GetStaleMoveTableIndexPtr(ft->player_id);
        if (attack_id != 1) {
            for (i = 0; i < 10; i++) {
                if (attack_id == smtp->StaleMoves[i].move_id &&
                    instance == smtp->StaleMoves[i].attack_instance)
                {
                    return;
                }
            }
            smtp->StaleMoves[smtp->current_index].move_id = attack_id;
            smtp->StaleMoves[smtp->current_index].attack_instance = instance;
            smtp->current_index =
                smtp->current_index == 9 ? 0 : smtp->current_index + 1;
        }
    }
}

void plStale_UpdateStaleMovesFromItem(HSD_GObj* gobj, HSD_GObj* gobj_2)
{
    int i;
    s32 attack_id;
    u16 instance;
    StaleMoveTable* smtp;
    HSD_GObj* owner;
    Item* it;

    it = GET_ITEM(gobj);
    owner = it->owner;
    if (ftLib_80086960(owner) && owner != gobj_2) {
        instance = it->xD8C_attack_instance;
        attack_id = it->xD88_attackID;
        smtp = Player_GetStaleMoveTableIndexPtr(GET_FIGHTER(owner)->player_id);
        if (attack_id != 1) {
            for (i = 0; i < 10; i++) {
                if (attack_id == smtp->StaleMoves[i].move_id &&
                    instance == smtp->StaleMoves[i].attack_instance)
                {
                    return;
                }
            }
            smtp->StaleMoves[smtp->current_index].move_id = attack_id;
            smtp->StaleMoves[smtp->current_index].attack_instance = instance;
            smtp->current_index =
                smtp->current_index == 9 ? 0 : smtp->current_index + 1;
        }
    }
}
