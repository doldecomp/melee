#include "ftfox.h"

// 0x800E83E0
// https://decomp.me/scratch/wfS8S // Create Reflector Loop GFX
void lbl_800E83E0(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->x2219_flag.bits.b0 == 0)
    {
        ef_Spawn(0x488, fighter_gobj, fp->x5E8_fighterBones[4].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x800E845C
// https://decomp.me/scratch/NNvPa // Create Reflector Start GFX
void lbl_800E845C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->x2219_flag.bits.b0 == 0)
    {
        ef_Spawn(0x489, fighter_gobj, fp->x5E8_fighterBones[4].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x800E84D8
// https://decomp.me/scratch/fVnTp // Create Reflector Deflect GFX
void lbl_800E84D8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->x2219_flag.bits.b0 == 0)
    {
        ef_Spawn(0x48A, fighter_gobj, fp->x5E8_fighterBones[4].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}
