#include "ft_0852.h"

#include "ft/forward.h"

#include "ft/inlines.h"
#include "ft/types.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

ftData* gFtDataList[FTKIND_MAX];

ft_8045993C_t ft_8045993C[6];

int ft_8045996C[FTKIND_MAX];

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

inline void ft_800852B0_Reset_ft_8045993C(int i)
{
    // Bitfields seem off but it is what it is
    ft_8045993C[i].pad_x0 = 0;
    ft_8045993C[i].x6_b0 = 0;
    ft_8045993C[i].x6_b1_b2 = 0;
}

void ft_800852B0(void)
{
    struct UnkCostumeList* var_r8 = CostumeListsForeachCharacter;
    ftData_UnkCountStruct* var_r9 = ftData_Table_Unk0;
    ftData_UnkCountStruct* var_r10 = ftData_UnkIntPairs;
    int i;

    for (i = 0; i < FTKIND_MAX; ++var_r8, ++var_r9, ++var_r10, ++i) {
        int costume_idx = 0;
        gFtDataList[i] = NULL;
        for (costume_idx = 0; costume_idx < (s32) var_r8->numCostumes;
             ++costume_idx)
        {
            var_r8->costume_list[costume_idx].joint = NULL;
            // Probably a pointer but no idea what kind of thing it points to.
            var_r8->costume_list[costume_idx].pad_x8 = NULL;
        }
        var_r9->data = NULL;
        var_r10->data = NULL;
    }
    ft_800852B0_Reset_ft_8045993C(0);
    ft_800852B0_Reset_ft_8045993C(1);
    ft_800852B0_Reset_ft_8045993C(2);
    ft_800852B0_Reset_ft_8045993C(3);
    ft_800852B0_Reset_ft_8045993C(4);
    ft_800852B0_Reset_ft_8045993C(5);
}

void ft_8008549C(void)
{
    int i;
    for (i = 0; i < 33; ++i) {
        ft_8045996C[i] = 0;
    }
}
