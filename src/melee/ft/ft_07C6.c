#include "ft_07C6.h"

#include <placeholder.h>

#include <sysdolphin/baselib/gobj.h>
#include <melee/ef/efsync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/types.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/it/inlines.h>
#include <melee/it/item.h>
#include <melee/it/items/it_2E5A.h>
#include <melee/it/types.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbcollision.h>
#include <melee/pl/player.h>

void ft_8007C630(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;
    for (i = 0; i < (signed) ARRAY_SIZE(fp->x1614); i++) {
        struct ftData_x38* temp_r6 = &fp->ft_data->x38[i];
        struct Fighter_x1614_t* temp_r27 = &fp->x1614[i];
        fp->x1614[i].x4 = fp->parts[temp_r6->x0].joint;
        fp->x1614[i].x0 = temp_r6->x10;
        lb_8000B1CC(temp_r27->x4, &temp_r6->x4, &temp_r27->x8);
        temp_r27->x8.z = 0.0F;
        temp_r27->x14 = temp_r27->x8;
    }
}

void ft_8007C6DC(Fighter_GObj* gobj)
{
    Fighter* fp;
    int i;

    if (gm_8016B0B4()) {
        fp = GET_FIGHTER(gobj);
        for (i = 0; i < (signed) ARRAY_SIZE(fp->x1614); i++) {
            struct ftData_x38* temp_r6 = &fp->ft_data->x38[i];
            struct Fighter_x1614_t* temp_r27 = &fp->x1614[i];
            temp_r27->x14 = temp_r27->x8;
            lb_8000B1CC(temp_r27->x4, &temp_r6->x4, &temp_r27->x8);
            temp_r27->x8.z = 0.0F;
        }
    }
}

void ft_8007C77C(Fighter_GObj* gobj)
{
    Fighter* fp;
    s32 temp_r29;
    bool var_r29;
    HSD_GObj* next;
    Item* ip;
    HSD_GObj* cur_gobj;
    f32(*temp_r26)[4];
    int i;

    f32 temp_f1;
    int var_r0;

    f32 sp18;

    if (!gm_8016B0B4()) {
        return;
    }
    {
        u32 a, b;
        fp = GET_FIGHTER(gobj);
        a = gm_801A4BB8() & 1;
        b = fp->player_id & 1;
        if (a == b) {
            var_r0 = 0;
        } else {
            var_r0 = 1;
        }
    }
    fp->x2229_b4 = var_r0;
    if (fp->x2229_b4) {
        return;
    }
    if (ftColl_8007B868(gobj) == 2) {
        return;
    }
    for (cur_gobj = HSD_GObj_Entities->items; cur_gobj != NULL;
         cur_gobj = next)
    {
        next = HSD_GObjGetNext(cur_gobj);
        ip = GET_ITEM(cur_gobj);
        if (ip->kind != It_Kind_Unk4) {
            continue;
        }
        var_r29 = 0;
        if (ftLib_80086FD4(gobj, ip->owner) != 0) {
            if (ip->xDD4_itemVar.unk4.xDEC_b1) {
                var_r29 = 1;
            }
        } else if (ip->xDD4_itemVar.unk4.xDEC_b0) {
            var_r29 = 1;
        }
        if (!var_r29) {
            continue;
        }
        temp_r26 = ip->xDD4_itemVar.unk4.xDF0;
        for (i = 0; i < 2; i++) {
            struct Fighter_x1614_t* tmp = &fp->x1614[i];
            if (lbColl_80007B78(temp_r26, tmp, ip->scl, fp->x34_scale.y)) {
                temp_r29 = it_802E5EF4(ip->entity);
                Player_SetCoins(fp->player_id,
                                temp_r29 + Player_GetCoins(fp->player_id));
                Player_SetTotalCoins(fp->player_id,
                                     temp_r29 +
                                         Player_GetTotalCoins(fp->player_id));
                lbAudioAx_80023870(0x93, 0x7F, 0x40, 0x1A);
                sp18 = 1.0f;
                efSync_Spawn(0x432, NULL, temp_r26[2], &sp18);
                Item_8026A8EC(ip->entity);
                break;
            }
        }
    }
}
