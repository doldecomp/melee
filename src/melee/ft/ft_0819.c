#include "ft_0819.h"

#include "ft/types.h"
#include "lb/types.h"

#include <baselib/gobj.h>

void ft_80081938(HSD_GObj* gobj)
{
    f32 lx, rx;
    ftECB* new_var;
    u8 unused1[36];
    Vec3 sp44;
    u8 unused2[56];
    Fighter* fp = gobj->user_data;
    sp44 = fp->coll_data.cur_topn;
    new_var = &fp->coll_data.xA4_ecbCurrCorrect;
    lx = new_var->left.x;
    rx = new_var->right.x;
    fp->dmg.x193c.x = lx + sp44.x;
    fp->dmg.x193c.y = rx + sp44.x;
    fp->dmg.x193c.z = fp->cur_pos.y + fp->co_attrs.x15C;
    fp->dmg.x1930 = fp->dmg.x193c;
}

void ft_800819A8(HSD_GObj* gobj)
{
    f32 lx, rx;
    ftECB* p_var;
    u8 unused1[36];
    Vec3 sp44;
    u8 unused2[56];
    Fighter* fp = gobj->user_data;
    sp44 = fp->coll_data.cur_topn;
    p_var = &fp->coll_data.xA4_ecbCurrCorrect;
    lx = p_var->left.x;
    rx = p_var->right.x;
    fp->dmg.x1930.x = lx + sp44.x;
    fp->dmg.x1930.y = rx + sp44.x;
    fp->dmg.x1930.z = fp->cur_pos.y + fp->co_attrs.x15C;
}

/// #ft_80081A00
