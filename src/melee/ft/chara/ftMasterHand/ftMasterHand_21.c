#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_801541C4(HSD_GObj* fighter_gobj)
{
    return;
}

#include <melee/ft/ftanim.h>

void ftMasterHand_801541C8(HSD_GObj* fighter_gobj, GObjCallback callback)
{
    Fighter* fp = fighter_gobj->user_data;
    u32 unused[2];

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x174, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);

    fp->x2344_callback = callback;
}
