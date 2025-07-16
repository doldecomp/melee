#include <placeholder.h>

#include "ft/inlines.h"
#include "ft/types.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

extern UnkCostumeStruct lbl_804599F0;
extern UnkCostumeStruct ft_80459A98;
extern UnkCostumeStruct ft_80459B28;
extern UnkCostumeStruct ft_80459C10;
extern UnkCostumeStruct ft_80459CA0;
extern UnkCostumeStruct ft_8045A090;
extern UnkCostumeStruct ftLk_Init_803C82EC;
extern UnkCostumeStruct ft_80459D18;
extern UnkCostumeStruct ft_80459D90;
extern UnkCostumeStruct ft_80459DF0;
extern UnkCostumeStruct ft_80459E68;
extern UnkCostumeStruct ft_80459EC8;
extern UnkCostumeStruct ft_80459F28;
extern UnkCostumeStruct ft_80459F88;
extern UnkCostumeStruct ft_8045A000;
extern UnkCostumeStruct ft_8045A0F0;
extern UnkCostumeStruct ft_8045A168;
extern UnkCostumeStruct ft_8045A1F8;
extern UnkCostumeStruct ft_8045A270;
extern UnkCostumeStruct ft_8045A2D0;
extern UnkCostumeStruct ft_8045A330;
extern UnkCostumeStruct ft_8045A3A8;
extern UnkCostumeStruct ft_8045A420;
extern UnkCostumeStruct ft_8045A480;
extern UnkCostumeStruct ft_8045A4E0;
extern UnkCostumeStruct ft_8045A540;
extern UnkCostumeStruct ft_8045A5B8;
extern UnkCostumeStruct ft_8045A630;
extern UnkCostumeStruct ft_8045A648;
extern UnkCostumeStruct ft_8045A660;
extern UnkCostumeStruct ft_8045A678;
extern UnkCostumeStruct ft_8045A690;
extern UnkCostumeStruct ft_8045A6A8;

struct UnkCostumeList CostumeListsForeachCharacter[FTKIND_MAX] = {
    {
        &lbl_804599F0,
        0x05,
    },
    {
        &ft_80459B28,
        0x04,
    },
    {
        &ft_80459A98,
        0x06,
    },
    {
        &ft_80459CA0,
        0x05,
    },
    {
        &ft_80459C10,
        0x06,
    },
    {
        &ft_8045A090,
        0x04,
    },
    {
        &ftLk_Init_803C82EC,
        0x05,
    },
    {
        &ft_80459D18,
        0x05,
    },
    {
        &ft_80459D90,
        0x04,
    },
    {
        &ft_80459DF0,
        0x05,
    },
    {
        &ft_80459E68,
        0x04,
    },
    {
        &ft_80459EC8,
        0x04,
    },
    {
        &ft_80459F28,
        0x04,
    },
    {
        &ft_80459F88,
        0x05,
    },
    {
        &ft_8045A000,
        0x06,
    },
    {
        &ft_8045A1F8,
        0x05,
    },
    {
        &ft_8045A2D0,
        0x04,
    },
    {
        &ft_8045A270,
        0x04,
    },
    {
        &ft_8045A0F0,
        0x05,
    },
    {
        &ft_8045A168,
        0x05,
    },
    {
        &ft_8045A330,
        0x05,
    },
    {
        &ft_8045A3A8,
        0x05,
    },
    {
        &ft_8045A420,
        0x04,
    },
    {
        &ft_8045A480,
        0x04,
    },
    {
        &ft_8045A4E0,
        0x04,
    },
    {
        &ft_8045A540,
        0x05,
    },
    {
        &ft_8045A5B8,
        0x05,
    },
    {
        &ft_8045A690,
        0x01,
    },
    {
        &ft_8045A6A8,
        0x01,
    },
    {
        &ft_8045A630,
        0x01,
    },
    {
        &ft_8045A648,
        0x01,
    },
    {
        &ft_8045A660,
        0x01,
    },
    {
        &ft_8045A678,
        0x01,
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
