#include "ft_0881.h"

#include "ft/ft_0877.h"
#include "ft/inlines.h"
#include "lb/lbaudio_ax.h"
#include "pl/pl_0371.h"
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

void ft_80088328(Fighter* fp, int arg1, int arg2, int arg3)
{
    NOT_IMPLEMENTED;
}

void ft_80088478(Fighter* fp, int arg0, int arg1, int arg2)
{
    NOT_IMPLEMENTED;
}

void ft_80088510(Fighter* fp, int arg1, int arg2, int arg3)
{
    NOT_IMPLEMENTED;
}

void ft_800885A8(Fighter* fp, int arg1, int arg2, int arg3)
{
    NOT_IMPLEMENTED;
}

void ft_80088640(Fighter* arg0, int arg1, int arg2, int arg3)
{
    NOT_IMPLEMENTED;
}

void ftCo_800886D8(Fighter* fp, int arg0, int arg1, int arg2)
{
    NOT_IMPLEMENTED;
}

void ft_80088770(Fighter* fp)
{
    NOT_IMPLEMENTED;
}

void ft_800887CC(Fighter* fp)
{
    NOT_IMPLEMENTED;
}

void ft_80088828(Fighter* fp)
{
    NOT_IMPLEMENTED;
}

void ft_80088884(Fighter* fp)
{
    NOT_IMPLEMENTED;
}

void ft_800888E0(Fighter* fp)
{
    NOT_IMPLEMENTED;
}

void ft_8008893C(Fighter* fp)
{
    NOT_IMPLEMENTED;
}

UNK_RET ft_80088998(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

void ft_800889F4(Fighter* fp, FtCollisionData* coll)
{
    if (coll != NULL) {
        ft_800881D8(fp, coll->x4[HSD_Randi(coll->x0)], 0x7F, 0x40);
    }
}

void ft_80088A50(Fighter* fp)
{
    NOT_IMPLEMENTED;
}

void ft_80088C5C(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_800890BC(Fighter* fp)
{
    fp->x2068_attackID = 1;
    fp->x206C = 0;
}

static inline void inlineB0(Fighter* fp, uint move_id)
{
    fp->x2068_attackID = move_id;
    fp->x206C = plStale_80037208();
}

void ft_800890D0(Fighter* fp, uint move_id)
{
    if (move_id == 1 || move_id != fp->x2068_attackID) {
        inlineB0(fp, move_id);
    }
}

UNK_RET ft_80089118(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ft_80089228(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

static void inlineC0(Fighter* fp, uint move_id)
{
    if (move_id == fp->x2068_attackID) {
        inlineB0(fp, move_id);
    }
}

void ft_800892A0(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);
    inlineC0(fp, fp->x2068_attackID);
}
