#include "plattack.h"

#include "pl/player.h"
#include "pl/types.h"

u16 unk_804D6480;

void plAttack_80037590(void)
{
    unk_804D6480 = 1;
}

static inline void clearAttackStats(struct plAttackStats* s)
{
    int i;
    for (i = 0; i < StatsAttack_Count; i++) {
        s->by_attack_counts[i] = 0;
    }
    s->total = 0;
    s->thrown_item_count = 0;
    s->aerials_count = 0;
    s->specials_count = 0;
    s->x1A0_count = 0;
    s->x1A4_count = 0;
    s->x1A8 = 0;
}

///< brief resets the players stats
void plAttack_8003759C(u32 slot)
{
    plActionStats* stats;
    int i;

    stats = Player_GetActionStats((s32) slot);

    clearAttackStats(&stats->attacks);
    clearAttackStats(&stats->hits);
    clearAttackStats(&stats->x358_hits);

    for (i = 0; i < StatsAttack_Count; i++) {
        stats->x504[i] = 0;
    }
    stats->x568 = 0;
    stats->x570 = 0;
    stats->x56C = 0;
    stats->x574 = 0;
    stats->x578 = 0;
    stats->x57C = 0;
    stats->x580 = 0;
    stats->x584 = 0;
    stats->x588 = 0;
    stats->x58C = 0;
    stats->x590 = 0;
    stats->x594 = 0;

    for (i = 0; i < 8; i++) {
        stats->x598[i] = 0;
    }
    stats->x5BC_b0 = 0;
    stats->x5BC_b1 = 0;
    stats->x5BC_b2 = 0;
    stats->x5BC_b3 = 0;
}

u16 plAttack_80037B08(void)
{
    u16 before = unk_804D6480;
    unk_804D6480 += 1;
    if (unk_804D6480 == 0) {
        unk_804D6480 = 1;
    }
    return before;
}
