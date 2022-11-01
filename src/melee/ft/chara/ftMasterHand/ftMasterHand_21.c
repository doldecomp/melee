#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void lbl_801541C4(HSD_GObj* gobj)
{
    return;
}

void ftMasterHand_801541C8(HSD_GObj* fighter_gobj, GObjCallback callback)
{
    Fighter* fp;
    u32 unk[2];

    fp = fighter_gobj->user_data;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x174, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
    fp->x2344_callback = callback;
}
