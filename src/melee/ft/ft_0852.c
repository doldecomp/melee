#include "ft_0852.h"

#include <placeholder.h>

#include "ft/inlines.h"
#include "ft/types.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

/* 4599F0 */ extern UnkCostumeStruct lbl_804599F0;
/* 459A98 */ extern UnkCostumeStruct ft_80459A98;
/* 459B28 */ extern UnkCostumeStruct ft_80459B28;
/* 459C10 */ extern UnkCostumeStruct ft_80459C10;
/* 459CA0 */ extern UnkCostumeStruct ft_80459CA0;
/* 45A090 */ extern UnkCostumeStruct ft_8045A090;
/* 3C82EC */ extern UnkCostumeStruct ftLk_Init_803C82EC;
/* 459D18 */ extern UnkCostumeStruct ft_80459D18;
/* 459D90 */ extern UnkCostumeStruct ft_80459D90;
/* 459DF0 */ extern UnkCostumeStruct ft_80459DF0;
/* 459E68 */ extern UnkCostumeStruct ft_80459E68;
/* 459EC8 */ extern UnkCostumeStruct ft_80459EC8;
/* 459F28 */ extern UnkCostumeStruct ft_80459F28;
/* 459F88 */ extern UnkCostumeStruct ft_80459F88;
/* 45A000 */ extern UnkCostumeStruct ft_8045A000;
/* 45A0F0 */ extern UnkCostumeStruct ft_8045A0F0;
/* 45A168 */ extern UnkCostumeStruct ft_8045A168;
/* 45A1F8 */ extern UnkCostumeStruct ft_8045A1F8;
/* 45A270 */ extern UnkCostumeStruct ft_8045A270;
/* 45A2D0 */ extern UnkCostumeStruct ft_8045A2D0;
/* 45A330 */ extern UnkCostumeStruct ft_8045A330;
/* 45A3A8 */ extern UnkCostumeStruct ft_8045A3A8;
/* 45A420 */ extern UnkCostumeStruct ft_8045A420;
/* 45A480 */ extern UnkCostumeStruct ft_8045A480;
/* 45A4E0 */ extern UnkCostumeStruct ft_8045A4E0;
/* 45A540 */ extern UnkCostumeStruct ft_8045A540;
/* 45A5B8 */ extern UnkCostumeStruct ft_8045A5B8;
/* 45A630 */ extern UnkCostumeStruct ft_8045A630;
/* 45A648 */ extern UnkCostumeStruct ft_8045A648;
/* 45A660 */ extern UnkCostumeStruct ft_8045A660;
/* 45A678 */ extern UnkCostumeStruct ft_8045A678;
/* 45A690 */ extern UnkCostumeStruct ft_8045A690;
/* 45A6A8 */ extern UnkCostumeStruct ft_8045A6A8;

/* 3C0EC0 */ struct UnkCostumeList CostumeListsForeachCharacter[FTKIND_MAX] = {
    {
        &lbl_804599F0,
        5,
    },
    {
        &ft_80459B28,
        4,
    },
    {
        &ft_80459A98,
        6,
    },
    {
        &ft_80459CA0,
        5,
    },
    {
        &ft_80459C10,
        6,
    },
    {
        &ft_8045A090,
        4,
    },
    {
        &ftLk_Init_803C82EC,
        5,
    },
    {
        &ft_80459D18,
        5,
    },
    {
        &ft_80459D90,
        4,
    },
    {
        &ft_80459DF0,
        5,
    },
    {
        &ft_80459E68,
        4,
    },
    {
        &ft_80459EC8,
        4,
    },
    {
        &ft_80459F28,
        4,
    },
    {
        &ft_80459F88,
        5,
    },
    {
        &ft_8045A000,
        6,
    },
    {
        &ft_8045A1F8,
        5,
    },
    {
        &ft_8045A2D0,
        4,
    },
    {
        &ft_8045A270,
        4,
    },
    {
        &ft_8045A0F0,
        5,
    },
    {
        &ft_8045A168,
        5,
    },
    {
        &ft_8045A330,
        5,
    },
    {
        &ft_8045A3A8,
        5,
    },
    {
        &ft_8045A420,
        4,
    },
    {
        &ft_8045A480,
        4,
    },
    {
        &ft_8045A4E0,
        4,
    },
    {
        &ft_8045A540,
        5,
    },
    {
        &ft_8045A5B8,
        5,
    },
    {
        &ft_8045A690,
        1,
    },
    {
        &ft_8045A6A8,
        1,
    },
    {
        &ft_8045A630,
        1,
    },
    {
        &ft_8045A648,
        1,
    },
    {
        &ft_8045A660,
        1,
    },
    {
        &ft_8045A678,
        1,
    },
};

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
