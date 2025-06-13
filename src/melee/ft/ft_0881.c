#include "ft_0881.h"

#include "ft/ft_0877.h"
#include "ft/inlines.h"
#include "lb/lbaudio_ax.h"
#include "pl/plstale.h"

#include <baselib/random.h>

/* literal */ float const ft_804D83E0 = 1;

/* 089118 */ static UNK_RET ft_80089118(UNK_PARAMS);

static void inlineA0(Fighter* fp, int arg1, int arg2, int arg3)
{
    switch (arg1 + 0xFFF80000) {
    default: {
        int temp = ft_80087D0C(fp, arg1);
        ft_80088770(fp);
        ft_800887CC(fp);
        fp->x2144 =
            lbAudioAx_80023870(temp, (s8) arg2, (s8) arg3,
                               fp->player_id * 2 + fp->x221F_b4 + 0x1E);
        return;
    }
    case 0x3D60U:
        return;
    case 0x3D61U:
        ft_80088770(fp);
        return;
    }
}

void ft_800881D8(Fighter* fp, int arg1, int arg2, int arg3)
{
    if (!fp->x2225_b6) {
        inlineA0(fp, arg1, arg2, arg3);
    } else {
        switch (fp->kind) {
        case FTKIND_GAMEWATCH:
        case FTKIND_SAMUS:
            inlineA0(fp, arg1, arg2, arg3);
        }
    }
}

void ft_80088328(Fighter* fp, int sfx_id, int sfx_vol, int sfx_pan)
{
    s32 temp_r30;
    u32 temp_ID;

    if (!(fp->x2225_b6)) {
        temp_ID = sfx_id - 0x80000;
        if (temp_ID != 0x3D60U) {
            if (temp_ID != 0x3D61U) {
                temp_r30 = ft_80087D0C(fp, sfx_id);
                !sfx_id;
                ft_80088770(fp);
                ft_800887CC(fp);
                fp->x2148 = lbAudioAx_80023870(
                    temp_r30, (u8) sfx_vol, (u8) sfx_pan,
                    (fp->player_id * 2) + 42 + fp->x221F_b4);
                return;
            }
            ft_800887CC(fp);
        }
    } else {
        switch (fp->kind) {
        case FTKIND_GAMEWATCH:
        case FTKIND_SAMUS:
            temp_ID = sfx_id - 0x80000;
            if (temp_ID != 0x3D60U) {
                if (temp_ID != 0x3D61U) {
                    temp_r30 = ft_80087D0C(fp, sfx_id);
                    ft_80088770(fp);
                    ft_800887CC(fp);
                    fp->x2148 = lbAudioAx_80023870(
                        temp_r30, (u8) sfx_vol, (u8) sfx_pan,
                        (fp->player_id * 2) + 42 + fp->x221F_b4);
                    return;
                }
                ft_800887CC(fp);
            }

        default:
            return;
        }
    }
}

void ft_80088478(Fighter* fp, int sfx_id, int sfx_vol, int sfx_pan)
{
    if ((sfx_id - 0x80000) != 0x3D60U) {
        if ((sfx_id - 0x80000) != 0x3D61U) {
            sfx_id = ft_80087D0C(fp, sfx_id);
            fp->x214C = lbAudioAx_80023870(
                sfx_id, sfx_vol, sfx_pan,
                (0x36 + (fp->player_id * 2) + (fp->x221F_b4)));
            return;
        } else {
            ft_80088828(fp);
        }
    }
}

/// #ft_80088510

/// #ft_800885A8

/// #ft_80088640

/// #ftCo_800886D8

void ft_80088770(Fighter* fp)
{
    lbAudioAx_80023870(0x83D61, 0, 0x40,
                       fp->x221F_b4 + (0x1E + fp->player_id * 2));
    fp->x2144 = -1;
}

/// #ft_800887CC

/// #ft_80088828

/// #ft_80088884

/// #ft_800888E0

/// #ft_8008893C

/// #ft_80088998

void ft_800889F4(Fighter* fp, FtSFXArr* sfx)
{
    if (sfx != NULL) {
        ft_800881D8(fp, sfx->sfx_ids[HSD_Randi(sfx->num)], 0x7F, 0x40);
    }
}

/// #ft_80088A50

/// #ft_80088C5C

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
    if (move_id == 1 || move_id != (u32) fp->x2068_attackID) {
        inlineB0(fp, move_id);
    }
}

/// #ft_80089118

/// #ft_80089228

static void inlineC0(Fighter* fp, u32 move_id)
{
    if (move_id == (u32) fp->x2068_attackID) {
        inlineB0(fp, move_id);
    }
}

void ft_800892A0(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);
    inlineC0(fp, fp->x2068_attackID);
}
