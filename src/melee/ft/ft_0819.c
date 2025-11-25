#include "ft_0819.h"

#include <placeholder.h>

#include "ft/ft_0C31.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "lb/lb_00F9.h"
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
    sp44 = fp->coll_data.cur_pos;
    new_var = &fp->coll_data.ecb;
    lx = new_var->left.x;
    rx = new_var->right.x;
    fp->dmg.x1930.xC.x = lx + sp44.x;
    fp->dmg.x1930.xC.y = rx + sp44.x;
    fp->dmg.x1930.xC.z = fp->cur_pos.y + fp->co_attrs.x17C;
    fp->dmg.x1930.x0 = fp->dmg.x1930.xC;
}

void ft_800819A8(HSD_GObj* gobj)
{
    f32 lx, rx;
    ftECB* p_var;
    u8 unused1[36];
    Vec3 sp44;
    u8 unused2[56];
    Fighter* fp = gobj->user_data;
    sp44 = fp->coll_data.cur_pos;
    p_var = &fp->coll_data.ecb;
    lx = p_var->left.x;
    rx = p_var->right.x;
    fp->dmg.x1930.x0.x = lx + sp44.x;
    fp->dmg.x1930.x0.y = rx + sp44.x;
    fp->dmg.x1930.x0.z = fp->cur_pos.y + fp->co_attrs.x17C;
}

static inline void inlineA0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Item_GObj* cur;
    for (cur = HSD_GObj_Entities->items; cur != NULL;
         cur = HSD_GObjGetNext(cur))
    {
        if (it_8026BC68(cur)) {
            Item* ip = GET_ITEM(cur);
            if (lb_80014638(&fp->dmg.x1930, &ip->xB54)) {
                ip->xCD0 = ip->pos.x > fp->cur_pos.x ? -1.0f : +1.0f;
                ip->xCFC = gobj;
                ip->xCB0_source_ply = fp->player_id;
                fp->dmg.x1950 = true;
            }
        }
    }
}

bool ft_80081A00(Fighter_GObj* fp_gobj)
{
    f32 lx, rx;
    Fighter* fp = GET_FIGHTER(fp_gobj);
    PAD_STACK(8 * 4);
    if (!fp->x2219_b1 && !fp->x2223_b4) {
        Vec3 sp64;
        PAD_STACK(14 * 4);
        fp->x2223_b5 = true;
        sp64 = fp->coll_data.cur_pos;
        lx = fp->coll_data.ecb.left.x;
        rx = fp->coll_data.ecb.right.x;
        fp->dmg.x1930.xC.x = lx + sp64.x;
        fp->dmg.x1930.xC.y = rx + sp64.x;
        fp->dmg.x1930.xC.z = fp->cur_pos.y + fp->co_attrs.x17C;
        inlineA0(fp_gobj);
        if (fp->dmg.x1950) {
            ftCo_800C703C(fp_gobj);
            fp->dmg.x1950 = false;
            return true;
        }
    }

    return false;
}
