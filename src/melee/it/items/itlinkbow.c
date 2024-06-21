#include "it/items/itlinkbow.h"

#include "it/inlines.h"
#include "it/item.h"
#include "ft/ftlib.h"

#include "it/it_26B1.h"

#include "ft/chara/ftLink/ftLk_SpecialN.h"
#include "ft/chara/ftKirby/ftKb_Init.h"

#include <baselib/gobj.h>


ItemStateTable it_803F6E98[] = {
    { 0,  it_802AF64C, it_802AF844, it_802AF848 },
    { 1,  it_802AF64C, it_802AF844, it_802AF848 },
    { 2,  it_802AF64C, it_802AF844, it_802AF848 },
    { 3,  it_802AF64C, it_802AF844, it_802AF848},
    { 4,  it_802AF64C, it_802AF844, it_802AF848 },
    { 5,  it_802AF64C, it_802AF844, it_802AF848 },
    { -1, it_802AF90C, it_802AF914, it_802AF918 }
};



// s32 it_802AF64C(HSD_GObj *arg0);                    /* static */
// void it_802AF844();                                 /* static */
// s32 it_802AF848(void *arg0);                        /* static */
// s32 it_802AF90C();                                  /* static */
// void it_802AF914();                                 /* static */
// s32 it_802AF918();                                  /* static */
static s32 it_803F6F08[7] = { 0, 1, 2, 3, 4, 5, 6 };
static s32 it_803F6F24[7] = { 3, 4, 5, 0, 1, 2, 6 };
static s8 it_804D5438[8] = { 0x6A, 0x6F, 0x62, 0x6A, 0x2E, 0x68, 0, 0 };
static s8 it_804D5440[8] = { 0x6A, 0x6F, 0x62, 0x6A, 0, 0, 0, 0 };

HSD_GObj *it_802AF1A4(f32 facing_dir, Fighter_GObj *owner_gobj, Vec3 *vec, u8 arg3, int arg4) {
    Item_GObj* gobj;
    Item * item;
    SpawnItem spawn;
    f32 pad[1];

    spawn.kind = arg4;
    spawn.prev_pos = *vec;
    spawn.prev_pos.z = 0.0F;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.z = 0.0F;
    spawn.vel.y = 0.0F;
    spawn.vel.x = 0.0F;
    spawn.x0_parent_gobj = owner_gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.bits.b0 = true;
    spawn.x40 = 0.0F;

    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        item = GET_ITEM((HSD_GObj *) gobj);
        item->xDB8_itcmd_var3 = 0;
        item->xDB4_itcmd_var2 = 0;
        item->xDB0_itcmd_var1 = 0;
        item->xDAC_itcmd_var0 = 0;
        item->xDCC_flag.b3 = false;
        item->xDD4_itemVar.linkbow.x0 = ftLib_800869D4(item->owner);
        item->xDD4_itemVar.linkbow.x4 = owner_gobj;
        Item_8026AB54(gobj, (HSD_GObj *) owner_gobj, arg3);
    }
    return gobj;
}

void it_802AF298(Item_GObj *arg0) {
    // NOTE(fox): item_kind might be on its own variable if inlines don't match
    Item *item;
    if (arg0 != NULL)
    {
        item = GET_ITEM((HSD_GObj *)arg0);
        if (item->owner != NULL) {
            switch (item->kind) {
                case It_Kind_Link_Bow:
                case It_Kind_CLink_Bow:
                    ftKb_SpecialNLk800FB444(item->owner);
                    break;
                case It_Kind_Kirby_CLinkBow:
                case It_Kind_Kirby_LinkBow:
                    ftLk_SpecialN_UnsetFv14(item->owner);
                    break;
            }
        }
    }
}

void it_802AF304(Item_GObj *gobj) {
    if (gobj != NULL) {
        Item_8026A8EC(gobj);
    }
}

void it_802AF32C(HSD_GObj *arg0, enum ftLk_SpecialNIndex arg1) {
    f32 temp_f31;
    Item *item;

    item = arg0->user_data;

    if (item->xDD4_itemVar.linkbow.x4 != NULL)
    {
        if (item->owner == item->xDD4_itemVar.linkbow.x4) {
            switch (item->kind) {
                case It_Kind_Link_Bow:
                case It_Kind_CLink_Bow:
                    arg1 = ftLk_SpecialN_GetIndex(item->owner);
                    break;
                case It_Kind_Kirby_CLinkBow:
                case It_Kind_Kirby_LinkBow:
                    arg1 = ftKb_SpecialNLk800FB394(item->owner);
                    break;
            }
            if (item->msid != it_803F6F08[arg1]) {
                if (item->msid == it_803F6F24[arg1]) {
                    temp_f31 = item->x5CC_currentAnimFrame;
                    Item_80268E5C(arg0, arg1, ITEM_ANIM_UPDATE);
                    Item_802694CC(arg0);
                    Item_80268DD4(arg0, temp_f31);
                    return;
                }
                Item_80268E5C(arg0, arg1, ITEM_ANIM_UPDATE);
                Item_802694CC(arg0);
            }
        }
    }
}

void it_802AF434(Item_GObj *arg0) {
    HSD_GObj *temp_r3;
    Item *temp_r30;
    f32 temp_f0;

    Item *item;
    Vec3 scale;

    item = GET_ITEM((HSD_GObj *)arg0);

    if (item->xDD4_itemVar.linkbow.x4 != NULL)
    {
        if (item->owner == item->xDD4_itemVar.linkbow.x4) {
            switch (item->kind) {
                case It_Kind_Link_Bow:
                case It_Kind_CLink_Bow:
                    ftLk_SpecialN_GetIndex(item->owner);
                    break;
                case It_Kind_Kirby_CLinkBow:
                case It_Kind_Kirby_LinkBow:
                    ftKb_SpecialNLk800FB394(item->owner);
                    break;
            }

            switch (item->owner->classifier) {
                case 0:
                    Item_80268E5C((HSD_GObj *) arg0, ftLk_SpecialNIndex_Start, ITEM_ANIM_UPDATE);
                    Item_802694CC((HSD_GObj *) arg0);
                    scale.z = item->xDD4_itemVar.linkbow.x0;
                    scale.y = item->xDD4_itemVar.linkbow.x0;
                    scale.x = item->xDD4_itemVar.linkbow.x0;
                    HSD_JObjSetScale(arg0->hsd_obj, &scale);
                    break;
                case 3:
                case 6:
                    Item_80268E5C((HSD_GObj *) arg0, ftLk_SpecialNIndex_AirStart, ITEM_ANIM_UPDATE);
                    Item_802694CC((HSD_GObj *) arg0);
                    scale.z = scale.y = scale.x = item->xDD4_itemVar.linkbow.x0;
                    HSD_JObjSetScale(arg0->hsd_obj, &scale);
                    break;
                default:
                    break;
            }
        }
    }
}

int it_802AF64C(HSD_GObj *arg0) {
    HSD_GObj *temp_r3;
    HSD_GObj *temp_r3_2;
    HSD_JObj *temp_r31;
    f32 temp_f1;
    s32 temp_cr0_eq;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_4;
    s32 var_r3;
    u32 temp_r0_3;
    u32 temp_r4;
    void *temp_r4_2;

    Item *item;
    Vec3 scale;

    item = GET_ITEM((HSD_GObj *)arg0);

    temp_r31 = arg0->hsd_obj;
    scale.z = scale.y = scale.x = item->xDD4_itemVar.linkbow.x0;
    HSD_JObjSetScale(arg0->hsd_obj, &scale);

    switch (item->msid) {
        case 2:
            if ((item->x5CC_currentAnimFrame == 0.0f) || ((item->x5CC_currentAnimFrame <= 24.0f))) {
                it_802AF298(arg0);
                return 1;
            }
        case 0:
        case 1:
        case 3:
        case 4:
        case 5:
            // check second arg
            it_802AF32C(arg0, item->msid);

            if (item->xDD4_itemVar.linkbow.x4 == NULL) {
                return 1;
            }
            if (item->owner != item->xDD4_itemVar.linkbow.x4) {
                return 1;
            }
            if (item->owner != NULL) {
                switch (item->kind) {
                    case It_Kind_Link_Bow:
                    case It_Kind_CLink_Bow:
                        if (ftLk_SpecialN_IsActiveAnd2071b6(item->owner) != 0) {
                            return 1;
                        }
                        return 0;
                    case It_Kind_Kirby_CLinkBow:
                    case It_Kind_Kirby_LinkBow:
                        if (ftKb_SpecialNLk800FB470(item->owner) != 0) {
                            return 1;
                        }
                        return 0;
                    return 0;
                    default:
                        return 0;
                }
            }
    }
}

#if 0
    temp_r0 = item->unk24;
    if (temp_r0 != 5) {
        if (temp_r0 < 5) {
            if (temp_r0 != 2) {
                goto block_28;
            }
            goto block_15;
        }
block_28:
        it_802AF32C(arg0);
        goto block_29;
    }
block_15:
    temp_f1 = item->unk5CC;
    if ((temp_f1 == 0.0f) || (M2C_ERROR(/* unknown instruction: cror eq, gt, eq */), ((temp_f1 == 24.0f) != 0))) {
        if (arg0 != NULL) {
            temp_r4_2 = arg0->user_data;
            temp_r3 = temp_r4_2->unk518;
            if (temp_r3 != NULL) {
                temp_r0_2 = temp_r4_2->unk10;
                if (temp_r0_2 < 0x8E) {
                    if (temp_r0_2 < 0x4E) {
                        if (temp_r0_2 < 0x4C) {

                        } else {
                            ftLk_SpecialN_UnsetFv14(temp_r3);
                        }
                    }
                } else if (temp_r0_2 < 0x90) {
                    ftKb_SpecialNLk800FB444(temp_r3);
                }
            }
        }
        return 1;
    }
block_29:
    temp_r0_3 = item->unkDD8;
    if (temp_r0_3 == 0U) {
        return 1;
    }
    temp_r3_2 = item->unk518;
    if (temp_r3_2 != temp_r0_3) {
        return 1;
    }
    if (temp_r3_2 != NULL) {
        temp_r0_4 = item->unk10;
        if (temp_r0_4 < 0x8E) {
            if (temp_r0_4 < 0x4E) {
                if (temp_r0_4 < 0x4C) {
                    goto block_44;
                }
                if (ftLk_SpecialN_IsActiveAnd2071b6(temp_r3_2) != 0) {
                    return 1;
                }
                goto block_44;
            }
            goto block_44;
        }
        if (temp_r0_4 < 0x90) {
            ftKb_SpecialNLk800FB470(temp_r3_2);
            if ((s32) M2C_ERROR(/* Read from unset register $r3 */) != 0) {
                return 1;
            }
            goto block_44;
        }
        goto block_44;
    }
block_44:
    return 0;
#endif

void it_802AF844(HSD_GObj *) {
    return;
}

int it_802AF848(HSD_GObj *arg0) {
    Item *item;
    Vec3 scale;
    item = GET_ITEM(arg0);
    scale.z = scale.y = scale.x = item->xDD4_itemVar.linkbow.x0;
    HSD_JObjSetScale(arg0->hsd_obj, &scale);
    return 0;
}

int it_802AF90C(HSD_GObj *arg0) {
    return 1;
}

void it_802AF914(HSD_GObj *arg0) {
    return;
}

int it_802AF918(HSD_GObj *arg0) {
    return 1;
}

void it_802AF920(Item_GObj *arg0, Item_GObj *arg1) {
    it_8026B894(arg0, (HSD_GObj *) arg1);
}
