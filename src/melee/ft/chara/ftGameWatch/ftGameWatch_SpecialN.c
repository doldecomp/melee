#include <ftgamewatch.h>

/* https://decomp.me/scratch/P7Z9j - first function of SpecialN.c; terrifying code
   https://decomp.me/scratch/kFkx6 - closer match, but just what is going on in this one? temp_fp suggests there is an inline somewhere in the function,
								     but an inline depth of 2 causes the compiler to start using branch link; no combination of inlines / lack thereof I have tried fully match */

HSD_GObj* func_802C837C(HSD_GObj*, Vec3*, s32, u32, f32);

void lbl_8014E4F0(HSD_GObj* fighter_gobj)
{
    Vec3 sp44;
    Vec3 sp38;
    Fighter* fp;
    Fighter* temp_fp;
    s32 i;
    s32 temp_r5;
    s32 temp_r6;
    s32 randomInt;
    ftGameWatchChef* lol;
    ftGameWatchChef chefStruct;
    s32 var;
    ftGameWatchAttributes* gawAttrs;

    fp = getFighter(fighter_gobj);
    gawAttrs = getFtSpecialAttrs(fp);
    if (fp->x2200_ftcmd_var0 != 0)
    {
        fp->x2200_ftcmd_var0 = randomInt = 0;
        if (((f32)fp->x2344_stateVar2_s32) < gawAttrs->x1C_GAMEWATCH_CHEF_MAX)
        {
            fp->x2344_stateVar2_s32 += 1;
            sp38.x = 2.5f;
            sp38.y = 6.5f;
            sp38.z = 0.0f;
            func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 0x1F)].x0_jobj, &sp38, &sp44);
            temp_fp = getFighter(fighter_gobj);
            i = 5;
            for (i -= 5; i < 5; i++)
            {
                if ((i != temp_fp->sa.gaw.x2240_chefVar1) && (i != temp_fp->sa.gaw.x2244_chefVar2))
                {
                    (&chefStruct)->sausageCount[randomInt] = i;
                    randomInt++;
                }
            }
            temp_r5 = (&chefStruct)->sausageCount[HSD_Randi(randomInt)];
            temp_fp->sa.gaw.x2244_chefVar2 = temp_fp->sa.gaw.x2240_chefVar1;
            temp_r6 = temp_r5;
            temp_fp->sa.gaw.x2240_chefVar1 = temp_r5;
            func_802C837C(fighter_gobj, &sp44, 0x7A, temp_r6, fp->x2C_facing_direction);
        }
        fp->cb.x21BC_callback_Accessory4 = NULL;
    }
}