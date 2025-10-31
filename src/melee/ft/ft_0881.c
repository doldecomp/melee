#include "ft_0881.h"

#include <sysdolphin/baselib/random.h>
#include <melee/db/db.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/inlines.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/pl/player.h>
#include <melee/pl/plstale.h>

void ft_800881D8(Fighter* fp, int sfx_id, u8 sfx_vol, u8 sfx_pan)
{
    if (!fp->x2225_b6) {
        if (sfx_id != 0x83D60) {
            if (sfx_id != 0x83D61) {
                sfx_id = ft_80087D0C(fp, sfx_id);
                ft_80088770(fp);
                ft_800887CC(fp);
                fp->x2144 = lbAudioAx_80023870(sfx_id, sfx_vol, sfx_pan,
                                               fp->player_id * 2 + 0x1E +
                                                   fp->x221F_b4);
                return;
            }
            ft_80088770(fp);
        }
    } else {
        switch (fp->kind) {
        case FTKIND_GAMEWATCH:
        case FTKIND_SAMUS:
            if (sfx_id != 0x83D60) {
                if (sfx_id != 0x83D61) {
                    sfx_id = ft_80087D0C(fp, sfx_id);
                    ft_80088770(fp);
                    ft_800887CC(fp);
                    fp->x2144 = lbAudioAx_80023870(sfx_id, sfx_vol, sfx_pan,
                                                   fp->player_id * 2 + 0x1E +
                                                       fp->x221F_b4);
                    return;
                }
                ft_80088770(fp);
            }
        }
    }
}

void ft_80088328(Fighter* fp, int sfx_id, u8 sfx_vol, u8 sfx_pan)
{
    s32 temp_r30;

    if (!(fp->x2225_b6)) {
        if (sfx_id != 0x83D60) {
            if (sfx_id != 0x83D61) {
                temp_r30 = ft_80087D0C(fp, sfx_id);
                !sfx_id;
                ft_80088770(fp);
                ft_800887CC(fp);
                fp->x2148 = lbAudioAx_80023870(temp_r30, sfx_vol, sfx_pan,
                                               (fp->player_id * 2) + 42 +
                                                   fp->x221F_b4);
                return;
            }
            ft_800887CC(fp);
        }
    } else {
        switch (fp->kind) {
        case FTKIND_GAMEWATCH:
        case FTKIND_SAMUS:
            if (sfx_id != 0x83D60) {
                if (sfx_id != 0x83D61) {
                    temp_r30 = ft_80087D0C(fp, sfx_id);
                    ft_80088770(fp);
                    ft_800887CC(fp);
                    fp->x2148 = lbAudioAx_80023870(temp_r30, sfx_vol, sfx_pan,
                                                   (fp->player_id * 2) + 42 +
                                                       fp->x221F_b4);
                    return;
                }
                ft_800887CC(fp);
            }

        default:
            return;
        }
    }
}

void ft_80088478(Fighter* fp, int sfx_id, u8 sfx_vol, u8 sfx_pan)
{
    if (sfx_id != 0x83D60) {
        if (sfx_id != 0x83D61) {
            sfx_id = ft_80087D0C(fp, sfx_id);
            fp->x214C =
                lbAudioAx_80023870(sfx_id, sfx_vol, sfx_pan,
                                   0x36 + fp->player_id * 2 + fp->x221F_b4);
            return;
        }
        ft_80088828(fp);
    }
}

void ft_80088510(Fighter* fp, int sfx_id, u8 sfx_vol, u8 sfx_pan)
{
    if (sfx_id != 0x83D60) {
        if (sfx_id != 0x83D61) {
            sfx_id = ft_80087D0C(fp, sfx_id);
            fp->x2150 =
                lbAudioAx_80023870(sfx_id, sfx_vol, sfx_pan,
                                   0x42 + fp->player_id * 2 + fp->x221F_b4);
            return;
        }
        ft_80088884(fp);
    }
}

void ft_800885A8(Fighter* fp, int sfx_id, u8 sfx_vol, u8 sfx_pan)
{
    if (sfx_id != 0x83D60) {
        if (sfx_id != 0x83D61) {
            sfx_id = ft_80087D0C(fp, sfx_id);
            fp->x2154 =
                lbAudioAx_80023870(sfx_id, sfx_vol, sfx_pan,
                                   0x4E + fp->player_id * 2 + fp->x221F_b4);
            return;
        }
        ft_800888E0(fp);
    }
}

void ft_80088640(Fighter* fp, int sfx_id, u8 sfx_vol, u8 sfx_pan)
{
    if (sfx_id != 0x83D60) {
        if (sfx_id != 0x83D61) {
            sfx_id = ft_80087D0C(fp, sfx_id);
            fp->x2158 =
                lbAudioAx_80023870(sfx_id, sfx_vol, sfx_pan,
                                   0x5A + fp->player_id * 2 + fp->x221F_b4);
            return;
        }
        ft_8008893C(fp);
    }
}

static inline int inline0(Fighter* fp, int sfx_id, u8 sfx_vol, u8 sfx_pan)
{
    return lbAudioAx_80023870(sfx_id, sfx_vol, sfx_pan,
                              0x72 + fp->player_id * 2 + fp->x221F_b4);
}

void ftCo_800886D8(Fighter* fp, int sfx_id, u8 sfx_vol, u8 sfx_pan)
{
    if (sfx_id != 0x83D60) {
        if (sfx_id != 0x83D61) {
            sfx_id = ft_80087D0C(fp, sfx_id);
            fp->x215C = inline0(fp, sfx_id, sfx_vol, sfx_pan);
            return;
        }
        ft_80088998(fp);
    }
}

void ft_80088770(Fighter* fp)
{
    lbAudioAx_80023870(0x83D61, 0, 0x40,
                       0x1E + fp->player_id * 2 + fp->x221F_b4);
    fp->x2144 = -1;
}

void ft_800887CC(Fighter* fp)
{
    lbAudioAx_80023870(0x83D61, 0, 0x40,
                       0x2A + fp->player_id * 2 + fp->x221F_b4);
    fp->x2148 = -1;
}

void ft_80088828(Fighter* fp)
{
    lbAudioAx_80023870(0x83D61, 0, 0x40,
                       0x36 + fp->player_id * 2 + fp->x221F_b4);
    fp->x214C = -1;
}

void ft_80088884(Fighter* fp)
{
    lbAudioAx_80023870(0x83D61, 0, 0x40,
                       0x42 + fp->player_id * 2 + fp->x221F_b4);
    fp->x2150 = -1;
}

void ft_800888E0(Fighter* fp)
{
    lbAudioAx_80023870(0x83D61, 0, 0x40,
                       0x4E + fp->player_id * 2 + fp->x221F_b4);
    fp->x2154 = -1;
}

void ft_8008893C(Fighter* fp)
{
    lbAudioAx_80023870(0x83D61, 0, 0x40,
                       0x5A + fp->player_id * 2 + fp->x221F_b4);
    fp->x2158 = -1;
}

void ft_80088998(Fighter* fp)
{
    lbAudioAx_80023870(0x83D61, 0, 0x40,
                       0x72 + fp->player_id * 2 + fp->x221F_b4);
    fp->x215C = -1;
}

void ft_800889F4(Fighter* fp, FtSFXArr* sfx)
{
    if (sfx != NULL) {
        ft_800881D8(fp, sfx->sfx_ids[HSD_Randi(sfx->num)], 0x7F, 0x40);
    }
}

void ft_80088A50(Fighter* fp)
{
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x36);
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x37);
    fp->x214C = -1;
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x1E);
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x1F);
    fp->x2144 = -1;
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x2A);
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x2B);
    fp->x2148 = -1;
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x42);
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x43);
    fp->x2150 = -1;
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x4E);
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x4F);
    fp->x2154 = -1;
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x5A);
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x5B);
    fp->x2158 = -1;
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x72);
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x73);
    fp->x215C = -1;
    fp->x2160 = -1;
    lbAudioAx_8002500C(fp->x2164);
    fp->x2164 = 0;
    lbAudioAx_80025038(fp->x2168);
    fp->x2168 = 0;
    fp->x2168 = 0;
    fp->x2164 = 0;
}

void ft_80088C5C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    lbAudioAx_80026510(gobj);
    if (fp->x2160 != -1) {
        lbAudioAx_800265C4(gobj, fp->x2160);
        fp->x2160 = -1;
    }
    if (fp->x214C != -1 && lbAudioAx_800265C4(gobj, fp->x214C) == 1) {
        ft_80088828(fp);
    }
    if (fp->x2144 != -1 && lbAudioAx_800265C4(gobj, fp->x2144) == 1) {
        ft_80088770(fp);
    }
    if (fp->x2148 != -1 && lbAudioAx_800265C4(gobj, fp->x2148) == 1) {
        ft_800887CC(fp);
    }
    if (fp->x2150 != -1 && lbAudioAx_800265C4(gobj, fp->x2150) == 1) {
        ft_80088884(fp);
    }
    if (fp->x2154 != -1 && lbAudioAx_800265C4(gobj, fp->x2154) == 1) {
        ft_800888E0(fp);
    }
    if (fp->x2158 != -1 && lbAudioAx_800265C4(gobj, fp->x2158) == 1) {
        ft_8008893C(fp);
    }
    if (fp->x215C != -1 && lbAudioAx_800265C4(gobj, fp->x215C) == 1) {
        ft_80088998(fp);
    }
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x36);
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x37);
    fp->x214C = -1;
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x1E);
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x1F);
    fp->x2144 = -1;
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x2A);
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x2B);
    fp->x2148 = -1;
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x42);
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x43);
    fp->x2150 = -1;
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x4E);
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x4F);
    fp->x2154 = -1;
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x5A);
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x5B);
    fp->x2158 = -1;
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x72);
    lbAudioAx_80023870(0x83D61, 0, 0x40, fp->player_id * 2 + 0x73);
    fp->x215C = -1;
    fp->x2160 = -1;
    lbAudioAx_8002500C(fp->x2164);
    fp->x2164 = 0;
    lbAudioAx_80025038(fp->x2168);
    fp->x2168 = 0;
    fp->x2168 = 0;
    fp->x2164 = 0;
}

void ft_800890BC(Fighter* fp)
{
    fp->x2068_attackID = 1;
    fp->x206C_attack_instance = 0;
}

static inline void inlineB0(Fighter* fp, s32 move_id)
{
    fp->x2068_attackID = move_id;
    fp->x206C_attack_instance = plStale_IncrementAttackInstance();
}

void ft_800890D0(Fighter* fp, u32 move_id)
{
    if (move_id == 1 || move_id != fp->x2068_attackID) {
        inlineB0(fp, move_id);
    }
}

#pragma push
#pragma dont_inline on
/**
 * Seems to handle move staling damage reduction
 * Each time the move exists in the stale move table, decreases the result
 * by the staling value in Fighter_804D6548.
 */
static f32 ft_80089118(StaleMoveTable* table, int move_id, int arg2)
{
    f32 var_f1 = 1.0F;
    int i;
    int var_r8 = table->current_index != 0 ? table->current_index - 1 : 9;

    if (move_id == 1) {
        return 1.0F;
    }

    for (i = 0; i < 9; i++) {
        if (table->StaleMoves[var_r8].move_id == 0) {
            return var_f1;
        }
        if (move_id == table->StaleMoves[var_r8].move_id) {
            var_f1 -= Fighter_804D6548[i];
        }
        var_r8 = var_r8 != 0 ? var_r8 - 1 : 9;
    }
    return var_f1;
}
#pragma pop

f32 ft_80089228(Fighter* fp, int attack_id, int arg2, f32 arg3)
{
    f32 temp_f1;
    f32 var_f31;
    StaleMoveTable* tmp;

    if (g_debugLevel >= 3) {
        return arg3;
    }
    var_f31 = arg3;
    tmp = Player_GetStaleMoveTableIndexPtr(fp->player_id);
    temp_f1 = ft_80089118(tmp, attack_id, arg2);
    if (temp_f1 != 1.0F) {
        var_f31 *= temp_f1;
    }
    return var_f31;
}

static inline void inlineC0(Fighter* fp, u32 move_id)
{
    if (move_id == fp->x2068_attackID) {
        inlineB0(fp, move_id);
    }
}

void ft_800892A0(Fighter_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    inlineC0(fp, fp->x2068_attackID);
}
