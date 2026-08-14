#include "ft_0852.h"

#include "ft/forward.h"

#include "ft/ftdata.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

ftData* gFtDataList[FTKIND_MAX];

ft_8045993C_t ft_8045993C[6];

int ft_8045996C[FTKIND_MAX];
UnkCostumeStruct lbl_804599F0[5];

/// @todo bss order hack
static void order_bss(void)
{
    (void) gFtDataList;
    (void) ft_8045993C;
    (void) ft_8045996C;
    (void) lbl_804599F0;
}

void ft_8008521C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Vec3 pos;

    HSD_JObjGetTranslation(jobj, &pos);
    fp->self_vel.x = pos.x - fp->cur_pos.x;
    fp->self_vel.y = pos.y - fp->cur_pos.y;
    fp->self_vel.z = pos.z - fp->cur_pos.z;
}

inline void ft_800852B0_Reset_ft_8045993C(ftData** list, int i)
{
    // Bitfields seem off but it is what it is
    ((ft_8045993C_t*) &list[FTKIND_MAX])[i].pad_x0 = 0;
    ((ft_8045993C_t*) &list[FTKIND_MAX])[i].x6_b0 = 0;
    ((ft_8045993C_t*) &list[FTKIND_MAX])[i].x6_b1_b2 = 0;
}

void ft_800852B0(void)
{
    ftData** list;
    ftData_UnkCountStruct* unk0 =
        (ftData_UnkCountStruct*) &CostumeListsForeachCharacter[FTKIND_MAX];
    ftData_UnkCountStruct* pairs =
        (ftData_UnkCountStruct*) ((u8*) CostumeListsForeachCharacter + 5940);
    int i;
    int new_var = 0;

    for (i = 0; i < FTKIND_MAX; ++i) {
        int costume_idx = new_var;
        list = gFtDataList;
        list[i] = NULL;
        for (costume_idx = new_var;
             costume_idx < (s32) CostumeListsForeachCharacter[i].numCostumes;
             ++costume_idx)
        {
            CostumeListsForeachCharacter[i].costume_list[costume_idx].joint =
                NULL;
            CostumeListsForeachCharacter[i].costume_list[costume_idx].pad_x8 =
                NULL;
        }
        unk0[i].data = NULL;
        pairs[i].data = NULL;
    }
    ft_800852B0_Reset_ft_8045993C(list, new_var);
    ft_800852B0_Reset_ft_8045993C(list, 1);
    ft_800852B0_Reset_ft_8045993C(list, 2);
    ft_800852B0_Reset_ft_8045993C(list, 3);
    ft_800852B0_Reset_ft_8045993C(list, 4);
    ft_800852B0_Reset_ft_8045993C(list, 5);
}

void ft_8008549C(void)
{
    int i;
    for (i = 0; i < 33; ++i) {
        ft_8045996C[i] = 0;
    }
}
