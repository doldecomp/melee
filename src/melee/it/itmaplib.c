#include "itmaplib.h"

#include "it_2725.h"
#include "iteffect.h"
#include "ithitbox.h"
#include "math.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "lb/lbvector.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"

#include <math_ppc.h>

extern const Vec3 it_803B8570;
extern const Vec3 it_803B857C;

void it_80275BC8(Item_GObj* item_gobj, HSD_GObj* arg_gobj)
{
    Item* ip = GET_ITEM(item_gobj);
    itECB sp24;
    f32* scale;
    Vec3 sp14;

    sp24 = ip->xBFC;
    it_802762BC(ip);
    ip->x378_itemColl.cur_pos = ip->pos;
    if (arg_gobj != NULL) {
        switch (it_80272D40(arg_gobj)) {
        case 0:
            it_8026BB68(arg_gobj, &sp14);
            break;
        case 1:
            it_8026BB88(arg_gobj, &sp14);
            break;
        default:
            OSReport("couldn't get Owner_GObj_Kind!!");
            __assert("itmaplib.c", 0x7FU, "0");
            break;
        }
    } else {
        sp14 = ip->pos;
    }

    sp24.top *= it_804D6D28->xE8;
    sp24.bottom *= it_804D6D28->xE8;
    sp24.right *= it_804D6D28->xE8;
    sp24.left *= it_804D6D28->xE8;

    ip->xC0C = ip->xC1C;

    if (ip->xDCE_flag.b7 == 1) {
        it_80275D5C(item_gobj, &sp24);
    }
    it_80276100(item_gobj, &sp14);
}

void it_80275D5C(Item_GObj* item_gobj, itECB* arg_ecb)
{
    f32 scale;
    s32 int_dir;
    Item* item;
    PAD_STACK(8);

    item = GET_ITEM(item_gobj);
    scale = item->scl;
    item->xC1C = *arg_ecb;
    mpColl_SetECBSource_Fixed(
        &item->x378_itemColl, item_gobj, item->xC1C.top * scale,
        item->xC1C.bottom * scale, item->xC1C.right * scale,
        item->xC1C.left * scale);
    if (-1.0f == item->facing_dir) {
        int_dir = -1;
    } else {
        int_dir = 1;
    }
    mpCollSetFacingDir(&item->x378_itemColl, int_dir);
}

void it_80275DFC(Item_GObj* item_gobj)
{
    Item* item;
    f32 scale;
    s32 int_dir;
    PAD_STACK(14);

    // item = GET_ITEM( item_gobj);
    item = item_gobj->user_data;
    scale = item->scl;
    item->xC1C = item->xC0C;
    mpColl_SetECBSource_Fixed(
        &item->x378_itemColl, item_gobj, item->xC1C.top * scale,
        item->xC1C.bottom * scale, item->xC1C.right * scale,
        item->xC1C.left * scale);
    if (-1.0f == item->facing_dir) {
        int_dir = -1;
    } else {
        int_dir = 1;
    }
    mpCollSetFacingDir(&item->x378_itemColl, int_dir);
}

void it_80275E98(Item_GObj* item_gobj, SpawnItem* spawn)
{
    Item* item1;
    Item* item2;
    CollData* coll;
    ItemAttr* attr;
    ItemKind kind;
    f32 scale;
    s32 int_dir;
    PAD_STACK(18);

    item1 = item_gobj->user_data;
    attr = item1->xCC_item_attr;
    coll = &item1->x378_itemColl;
    item1->x378_itemColl.cur_pos = item1->pos;
    mpColl_80041EE4(coll);
    kind = item1->kind;
    if (kind < It_Kind_L_Gun_Ray) {
        coll->x34_flags.b1234 = 2;
    } else if (kind < It_Kind_Kuriboh) {
        coll->x34_flags.b1234 = 4;
    } else if (kind < It_Kind_Octarock_Stone) {
        coll->x34_flags.b1234 = 3;
    } else if (kind < It_Kind_Mario_Fire) {
        coll->x34_flags.b1234 = 4;
    } else if (kind < It_Kind_Unk4) {
        coll->x34_flags.b1234 = 5;
    } else if (kind < Pokemon_Random) {
        coll->x34_flags.b1234 = 5;
    } else if (kind < Pokemon_Tosakinto) {
        coll->x34_flags.b1234 = 5;
    } else if (kind < Pokemon_Chicorita_Leaf) {
        coll->x34_flags.b1234 = 5;
    } else if (kind < It_Kind_Old_Kuri) {
        coll->x34_flags.b1234 = 4;
    } else if (kind < It_Kind_Arwing_Laser) {
        coll->x34_flags.b1234 = 3;
    } else if (kind < 238) {
        coll->x34_flags.b1234 = 4;
    }

    item2 = item_gobj->user_data;
    scale = item2->scl;
    item2->xC1C = item1->xC1C;
    mpColl_SetECBSource_Fixed(
        &item2->x378_itemColl, item_gobj, item2->xC1C.top * scale,
        item2->xC1C.bottom * scale, item2->xC1C.right * scale,
        item2->xC1C.left * scale);
    if (-1.0f == item2->facing_dir) {
        int_dir = -1;
    } else {
        int_dir = 1;
    }
    mpCollSetFacingDir(&item2->x378_itemColl, int_dir);
    coll->x50 = attr->x1C_damage_mul;
    if (spawn->x44_flag.b0 == 1) {
        if (spawn->x48_ground_or_air == GA_Air) {
            it_80276100(item_gobj, &spawn->pos);
            return;
        }
        it_80276174(item_gobj, &spawn->pos);
        return;
    }
    coll->last_pos = spawn->pos;
    mpColl_80043670(coll);
}

void it_80276100(Item_GObj* item_gobj, Vec3* pos)
{
    Item* item = GET_ITEM(item_gobj);
    CollData* coll = &item->x378_itemColl;
    coll->last_pos = *pos;
    mpColl_80043670(coll);
    mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
}

void it_80276174(Item_GObj* item_gobj, Vec3* pos)
{
    f32 unused1;
    f32 unused2;
    Vec3 temp_pos;
    Item* item;

    item = GET_ITEM(item_gobj);
    item->x378_itemColl.last_pos = *pos;
    mpColl_80043670(&item->x378_itemColl);
    if (mpCheckMultiple(item->pos.x, item->pos.y, item->pos.x,
                        item->pos.y - it_804D6D28->xF4, &temp_pos, NULL, NULL,
                        NULL, 1, -1, -1))
    {
        item->pos = temp_pos;
    }
}

/// bool it_80276214(Item_GObj* item_gobj) {}
void it_80276214(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->x378_itemColl.last_pos = item->x378_itemColl.cur_pos;
    item->x378_itemColl.cur_pos = item->pos;
    if (item->xDCE_flag.b7 == 1) {
        it_80276278(item_gobj);
    }
}

void it_80276278(Item_GObj* item_gobj)
{
    Item* item;
    CollData* coll_data;

    item = GET_ITEM(item_gobj);
    coll_data = &item->x378_itemColl;

    mpColl_800436E4(coll_data, it_80274990(item_gobj));
}

void it_802762B0(Item* item)
{
    item->ground_or_air = GA_Ground;
}

void it_802762BC(Item* item)
{
    item->ground_or_air = GA_Air;
    item->xDC8_word.flags.x1F = 0;
}

bool it_802762D8(Item_GObj* item_gobj)
{
    CollData* coll;
    bool chk;

    chk = false;
    coll = &((Item*) item_gobj->user_data)->x378_itemColl;
    if (coll->env_flags & Collide_LeftEdge) {
        chk = true;
    }
    if (coll->env_flags & Collide_RightEdge) {
        return true;
    }
    return chk;
}

s32 it_80276308(Item_GObj* item_gobj)
{
    Item* item;
    CollData* coll;
    s32 ret_val;

    item = item_gobj->user_data;
    ret_val = 0;
    coll = &item->x378_itemColl;
    if (item->x378_itemColl.env_flags & Collide_LeftWallMask) {
        ret_val = 8;
        item->xC30 = coll->left_facing_wall.index;
    }
    if (coll->env_flags & Collide_RightWallMask) {
        item->xC30 = coll->right_facing_wall.index;
        ret_val = 4;
    }
    return ret_val;
}

s32 it_80276348(Item_GObj* item_gobj, Vec3* vec)
{
    s32 ret_val;
    Item* item;
    CollData* coll;

    item = item_gobj->user_data;
    ret_val = 0;
    coll = &item->x378_itemColl;
    if (coll->env_flags & Collide_LeftWallMask) {
        ret_val = 8;
        item->xC30 = coll->left_facing_wall.index;
        *vec = coll->left_facing_wall.normal;
    }
    if (coll->env_flags & Collide_RightWallMask) {
        item->xC30 = coll->right_facing_wall.index;
        *vec = coll->right_facing_wall.normal;
        ret_val = 4;
    }
    return ret_val;
}

bool it_802763B8(Item_GObj* item_gobj)
{
    Item* item;
    CollData* coll;
    bool chk = false;

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    if (coll->env_flags & Collide_FloorMask) {
        item->xC30 = coll->floor.index;
        chk = true;
    }
    return chk;
}

s32 it_802763E0(Item_GObj* item_gobj)
{
    int result = 0;
    Item* item = GET_ITEM(item_gobj);
    CollData* colldata = &item->x378_itemColl;
    if ((item->x378_itemColl.env_flags & Collide_CeilingMask)) {
        item->xC30 = colldata->ceiling.index;
        result = 2;
    }
    return result;
}

#pragma push
#pragma dont_inline on
void it_80276408(Item_GObj* item_gobj, CollData* coll, Vec3* vec)
{
    if (coll->env_flags & Collide_LeftWallMask) {
        *vec = coll->left_facing_wall.normal;
    }
    if (coll->env_flags & Collide_RightWallMask) {
        *vec = coll->right_facing_wall.normal;
    }
    if (coll->env_flags & Collide_CeilingMask) {
        *vec = coll->ceiling.normal;
    }
    if (coll->env_flags & Collide_FloorMask) {
        *vec = coll->floor.normal;
    }
}
#pragma pop

f32 it_8027649C(Item_GObj* item_gobj)
{
    Vec3 sp20;
    Vec3 sp14;
    f32 angle;
    s32 int_dir;
    Item* item = GET_ITEM(item_gobj);
    f32 ret; // permuterslop
    CollData* coll = &item->x378_itemColl;
    PAD_STACK(4);

    sp14.z = 0.0f;
    sp14.x = 0.0f;
    sp14.y = 1.0f;
    if (coll->env_flags & Collide_LeftWallMask) {
        sp20 = coll->left_facing_wall.normal;
    }
    if (coll->env_flags & Collide_RightWallMask) {
        sp20 = coll->right_facing_wall.normal;
    }
    if (coll->env_flags & Collide_CeilingMask) {
        sp20 = coll->ceiling.normal;
    }
    if (coll->env_flags & Collide_FloorMask) {
        sp20 = coll->floor.normal;
    }
    angle = lbVector_Angle(&sp20, &sp14);
    if (sp20.x < 0.0f) {
        int_dir = -1;
    } else {
        int_dir = 1;
    }

    return ret = item->facing_dir * (angle * int_dir);
}

void it_802765BC(Item_GObj* item_gobj, enum_t arg1)
{
    u8 pad[16];
    Vec3 sp74;
    Vec3 sp68;
    Vec3 sp5C;
    Vec3 sp50;
    Vec3 sp44;
    Vec3 sp38;
    HSD_JObj* jobj;
    Item* item1;
    Item* item2;
    Item* item3;
    Item* item4;
    f32 angle1;
    f32 angle2;
    f32 angle3;
    f32 rotate_angle1;
    f32 rotate_angle2;
    f32 rotate_angle3;
    s32 dir1;
    s32 dir2;
    s32 dir3;
    u32 bit_chk;
    PAD_STACK(40);

    item1 = item_gobj->user_data;
    jobj = it_80272CC0(item_gobj, arg1);
    bit_chk = item1->xDC8_word.flags.x17;
    if (bit_chk == 0) {
        item2 = item_gobj->user_data;
        sp74.z = 0.0f;
        sp74.x = 0.0f;
        sp74.y = 1.0f;
        it_80276408(item_gobj, &item2->x378_itemColl, &sp68);
        angle1 = lbVector_Angle(&sp68, &sp74);
        if (sp68.x < 0.0f) {
            dir1 = -1;
        } else {
            dir1 = 1;
        }
        rotate_angle1 =
            -item1->facing_dir * (item2->facing_dir * (angle1 * dir1));
        HSD_JObjSetRotationZ(jobj, rotate_angle1);
    } else if (bit_chk == 1) {
        item3 = item_gobj->user_data;
        sp5C.z = 0.0f;
        sp5C.x = 0.0f;
        sp5C.y = 1.0f;
        it_80276408(item_gobj, &item3->x378_itemColl, &sp50);
        angle2 = lbVector_Angle(&sp50, &sp5C);
        if (sp50.x < 0.0f) {
            dir2 = -1;
        } else {
            dir2 = 1;
        }
        rotate_angle2 = item3->facing_dir * (angle2 * dir2);
        HSD_JObjSetRotationX(jobj, rotate_angle2);
    } else {
        item4 = item_gobj->user_data;
        sp44.z = 0.0f;
        sp44.x = 0.0f;
        sp44.y = 1.0f;
        it_80276408(item_gobj, &item4->x378_itemColl, &sp38);
        angle3 = lbVector_Angle(&sp38, &sp44);
        if (sp38.x < 0.0f) {
            dir3 = -1;
        } else {
            dir3 = 1;
        }
        rotate_angle3 = item4->facing_dir * (angle3 * dir3);
        HSD_JObjSetRotationY(jobj, rotate_angle3);
    }
}

void it_80276934(Item_GObj* item_gobj, enum_t arg1)
{
    u8 _pad0[12];
    Vec3 sp80;
    Vec3 sp74;
    u8 _pad1[4];
    Vec3 sp64;
    Vec3 sp58;
    Vec3 sp48;
    Vec3 sp3C;
    HSD_JObj* jobj;
    Item* item2;
    Item* item3;
    Item* item4;
    f32 angle1;
    Item* item1;
    f32 angle2;
    f32 angle3;
    f32 rotate_angle1;
    f32 rotate_angle2;
    f32 rotate_angle3;
    s32 dir1;
    s32 dir2;
    s32 dir3;
    u32 bit_chk;
    PAD_STACK(48);

    item1 = item_gobj->user_data;
    jobj = it_80272CC0(item_gobj, arg1);
    bit_chk = item1->xDC8_word.flags.x17;
    if (bit_chk == 0) {
        item2 = item_gobj->user_data;
        sp80.z = 0.0f;
        sp80.x = 0.0f;
        sp80.y = 1.0f;
        mpLineGetNormal(item2->xC30, &sp74);
        angle1 = lbVector_Angle(&sp74, &sp80);
        if (sp74.x < 0.0f) {
            dir1 = -1;
        } else {
            dir1 = 1;
        }
        rotate_angle1 =
            -item1->facing_dir * (item2->facing_dir * (angle1 * dir1));
        HSD_JObjSetRotationZ(jobj, rotate_angle1);
    } else if (bit_chk == 1) {
        item3 = item_gobj->user_data;
        sp64.z = 0.0f;
        sp64.x = 0.0f;
        sp64.y = 1.0f;
        mpLineGetNormal(item3->xC30, &sp58);
        angle2 = lbVector_Angle(&sp58, &sp64);
        if (sp58.x < 0.0f) {
            dir2 = -1;
        } else {
            dir2 = 1;
        }
        rotate_angle2 = item3->facing_dir * (angle2 * dir2);
        HSD_JObjSetRotationX(jobj, rotate_angle2);
    } else {
        item4 = item_gobj->user_data;
        sp48.z = 0.0f;
        sp48.x = 0.0f;
        sp48.y = 1.0f;
        mpLineGetNormal(item4->xC30, &sp3C);
        angle3 = lbVector_Angle(&sp3C, &sp48);
        if (sp3C.x < 0.0f) {
            dir3 = -1;
        } else {
            dir3 = 1;
        }
        rotate_angle3 = item4->facing_dir * (angle3 * dir3);
        HSD_JObjSetRotationY(jobj, rotate_angle3);
    }
}

void it_80276CB8(Item_GObj* item_gobj)
{
    if (GET_ITEM(item_gobj)->x378_itemColl.env_flags & Collide_FloorMask) {
        it_802765BC(item_gobj, 0);
    }
}

void it_80276CEC(Item_GObj* item_gobj)
{
    CollData* coll;
    Item* item;
    u32 coll_index;

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    if (coll->env_flags & Collide_LeftWallMask) {
        item->xAC_unk = coll->left_facing_wall.normal;
        coll_index = coll->left_facing_wall.index;
    }
    if (coll->env_flags & Collide_RightWallMask) {
        item->xAC_unk = coll->right_facing_wall.normal;
        coll_index = coll->right_facing_wall.index;
    }
    if (coll->env_flags & Collide_CeilingMask) {
        item->xAC_unk = coll->ceiling.normal;
        coll_index = coll->ceiling.index;
    }
    if (coll->env_flags & Collide_FloorMask) {
        item->xAC_unk = coll->floor.normal;
        coll_index = coll->floor.index;
    }
    item->xC2C = coll_index;
}

bool it_80276D9C(Item_GObj* item_gobj, enum_t arg1)
{
    itECB sp34;
    CollData* coll;
    Item* item;
    u32 flags;
    s32 dir1;
    s32 dir2;
    f32 scale;
    f32 top;
    bool ret_val;
    PAD_STACK(36);

    ret_val = true;
    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    flags = coll->env_flags;
    if ((flags & Collide_LeftWallMask) && (flags & Collide_RightWallMask)) {
        // if (coll->env_flags & Collide_WallMask) {
        dir1 = 1;
    } else {
        dir1 = 0;
    }
    if (dir1 != 0) {
        sp34 = item->xC1C;
        if (coll->facing_dir == 1) {
            sp34.right = ABS(coll->ecb.right.x - 1.0f);
            sp34.left = ABS(1.0f + coll->ecb.left.x);
        } else {
            sp34.right = ABS(1.0f + coll->ecb.left.x);
            sp34.left = ABS(coll->ecb.right.x - 1.0f);
        }
        item->xC1C = sp34;
        top = item->xC1C.top;
        scale = 1.0f;
        mpColl_SetECBSource_Fixed(&item->x378_itemColl, item_gobj, top * scale,
                                  item->xC1C.bottom * scale,
                                  item->xC1C.right * scale,
                                  item->xC1C.left * scale);
        if (-1.0f == item->facing_dir) {
            dir2 = -1;
        } else {
            dir2 = 1;
        }
        mpCollSetFacingDir(&item->x378_itemColl, dir2);
        return false;
    }
    if ((arg1 & 4) && (coll->prev_env_flags & Collide_RightWallMask)) {
        ret_val = false;
        item->pos.x += 1.5f;
    }
    if ((arg1 & 8) && (coll->prev_env_flags & Collide_LeftWallMask)) {
        ret_val = false;
        item->pos.x -= 1.5f;
    }
    if ((arg1 & 2) && (coll->prev_env_flags & Collide_CeilingMask)) {
        ret_val = false;
        item->pos.y -= 1.5f;
    }
    if ((arg1 & 1) && (coll->prev_env_flags & Collide_FloorMask)) {
        ret_val = false;
        item->pos.y += 1.5f;
    }
    return ret_val;
}

#pragma push
#pragma dont_inline on

void it_80276FC4(Item_GObj* item_gobj, s32 arg1)
{
    Item* it = item_gobj->user_data;
    ItemAttr* attr = it->xCC_item_attr;
    it_8027781C(item_gobj);
    if (it_80276D9C(item_gobj, arg1)) {
        it_8027321C(item_gobj);
        it_80277C40(item_gobj, arg1);
        it_80275640(item_gobj, attr->x58);
    }
}

#pragma pop

bool it_80277040(Item_GObj* item_gobj)
{
    UNUSED u8 frame_pad[8];
    Vec3 sp5C;
    Vec3 sp50;
    Vec3 sp44;
    Vec3 sp38;
    UNUSED u8 pad[12];
    Vec3 sp20;
    Vec3 sp14;
    CollData* coll;
    Item* item2;
    Item* item1;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f3;
    f32 angle1;
    f32 angle2;
    bool chk;
    s32 int_dir1;
    s32 int_dir3;
    bool ret_val;
    s32 int_dir2;
    s32 int_dir4;
    PAD_STACK(4);

    ret_val = true;
    item1 = GET_ITEM(item_gobj);
    coll = &item1->x378_itemColl;
    if (ABS(item1->xCC_item_attr->x50) < 0.00001f) {
        item1->x88.y = 0.0f;
        item1->x88.x = 0.0f;
        return false;
    }
    sp20.z = 0.0f;
    sp20.x = 0.0f;
    sp20.y = 1.0f;
    if (coll->env_flags & Collide_LeftWallMask) {
        sp5C = coll->left_facing_wall.normal;
    }
    if (coll->env_flags & Collide_RightWallMask) {
        sp5C = coll->right_facing_wall.normal;
    }
    if (coll->env_flags & Collide_CeilingMask) {
        sp5C = coll->ceiling.normal;
    }
    if (coll->env_flags & Collide_FloorMask) {
        sp5C = coll->floor.normal;
    }
    item1->x94 = item1->x88;
    // item1->x98 = item1->x8C;
    // item1->x9C = item1->x90;
    angle1 = lbVector_AngleXY(&sp5C, &sp20);
    if (angle1 < 0.0f) {
        angle1 = -angle1;
    }
    if (angle1 >= it_804D6D28->xC0) {
        sp50.z = 0.0f;
        sp50.x = 0.0f;
        sp50.y = -1.0f;
        lbVector_CrossprodNormalized(&sp5C, &sp50, &sp44);
        lbVector_CrossprodNormalized(&sp44, &sp5C, &sp38);
        temp_f3 = item1->xCC_item_attr->x50;
        temp_f31 = item1->x94.x / temp_f3;
        temp_f30 = item1->x94.y / temp_f3;
        item1->x88.x = sp38.x * temp_f3;
        item1->x88.y = sp38.y * item1->xCC_item_attr->x50;
        item2 = item_gobj->user_data;
        it_80276408(item_gobj, &item2->x378_itemColl, &sp14);
        angle2 = lbVector_Angle(&sp14, &item2->xAC_unk);
        if (angle2 < 0.0f) {
            angle2 = -angle2;
        }
        if ((angle2 >= it_804D6D28->xC4) && (item2->xC30 == item2->xC2C)) {
            chk = true;
        } else {
            chk = false;
        }
        if (!chk) {
            if (item1->x94.x || item1->x94.y) {
                if (sp38.x < 0.0f) {
                    int_dir1 = -1;
                } else {
                    int_dir1 = 1;
                }
                if (temp_f31 < 0.0f) {
                    int_dir2 = -1;
                } else {
                    int_dir2 = 1;
                }
                if (int_dir2 == int_dir1) {
                    if (sp38.y < 0.0f) {
                        int_dir3 = -1;
                    } else {
                        int_dir3 = 1;
                    }
                    if (temp_f30 < 0.0f) {
                        int_dir4 = -1;
                    } else {
                        int_dir4 = 1;
                    }
                    if (int_dir4 != int_dir3) {
                        goto block_38;
                    }
                } else {
                block_38:
                    item1->xD58++;
                    if (item1->xD58 >= it_804D6D28->x38_float) {
                        item1->xD58 = 0;
                        ret_val = false;
                        item1->x88.y = 0.0f;
                        item1->x88.x = 0.0f;
                    }
                }
            }
        } else {
            item1->xD5C = 2;
        }
    } else {
        ret_val = false;
        item1->x88.y = 0.0f;
        item1->x88.x = 0.0f;
    }
    return ret_val;
}

static inline float sqrtf_accurate_store(float x, volatile float* y)
{
    if (x > 0.0f) {
        double guess = __frsqrte((double) x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        *y = (float) (x * guess);
        return *y;
    }
    return x;
}

void it_8027737C(Item_GObj* item_gobj, Vec3* pos)
{
    Vec3 sp1C;
    Item* item;
    f32 temp_f1;
    volatile f32 sqrt_0;
    u8 _[4];

    item = GET_ITEM(item_gobj);
    if (item->xDC8_word.flags.x1F && item->xD5C != 0U) {
        PSVECAdd(&item->x88, &item->x7C, &item->x7C);
        item->x7C.x *= item->xCC_item_attr->x54;
        item->x7C.y *= item->xCC_item_attr->x54;
        if (sqrtf_accurate_store(SQ(item->x7C.x) + SQ(item->x7C.y), &sqrt_0) >
            it_804D6D28->xC8)
        {
            lbVector_NormalizeXY(&item->x7C);
            temp_f1 = it_804D6D28->xC8;
            item->x7C.x *= temp_f1;
            item->x7C.y *= temp_f1;
        }
        if (SQ(item->x7C.x) + SQ(item->x7C.y) < it_804D6D28->xCC) {
            item->xDC8_word.flags.x1F = 0;
            item->x7C.y = 0.0f;
            item->x7C.x = 0.0f;
            return;
        }

        it_802775F0(item_gobj, &item->x7C);
        it_80274A64(item_gobj);
        PSVECAdd(&item->x7C, pos, &sp1C);
        *pos = sp1C;
    }
}

bool it_80277544(Item_GObj* item_gobj)
{
    Vec3 sp10;
    Item* item;
    bool ret_val;

    ret_val = false;
    item = GET_ITEM(item_gobj);
    if (item->xD5C != 0U && it_80277040(item_gobj) != 0 &&
        ((PSVECAdd(&item->x40_vel, &item->x70_nudge, &sp10),
          ((SQ(sp10.x) + SQ(sp10.y))) >= it_804D6D28->xCC) ||
         (item->xD5C == 2U)))
    {
        item->xDC8_word.flags.x1F = 1;
        ret_val = true;
        item->xD5C = 1;
    }
    return ret_val;
}

static inline float sqrtf_accurate_sp18(float x)
{
    volatile float y[2];

    if (x > 0.0f) {
        double guess = __frsqrte((double) x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        y[1] = (float) (x * guess);
        return y[1];
    }
    return x;
}

void it_802775F0(Item_GObj* item_gobj, Vec3* arg1)
{
    f32 temp_sqrt;
    Item* item = GET_ITEM(item_gobj);

    if (item->spin_spd) {
        temp_sqrt = sqrtf_accurate_sp18(SQ(arg1->x) + SQ(arg1->y));
        item->xD3C_spinSpeed = 0.85f * (temp_sqrt / item->xC1C.bottom);
        if ((arg1->x < 0 ? -1 : 1) != (item->facing_dir < 0 ? -1 : 1)) {
            item->xD3C_spinSpeed = -item->xD3C_spinSpeed;
        }
        if (item->xDC8_word.flags.x19 != 1) {
            item->xD3C_spinSpeed *= -item->facing_dir;
        }
    }
}

bool it_8027770C(Item_GObj* item_gobj)
{
    Vec3 sp38;
    f32 mult;
    bool ret_val;
    enum_t var_r5;
    Item* item;
    ItemAttr* attr;
    CollData* coll;
    PAD_STACK(44);

    var_r5 = 0;
    item = item_gobj->user_data;
    ret_val = false;
    coll = &item->x378_itemColl;
    attr = item->xCC_item_attr;
    if (coll->env_flags & Collide_LeftWallMask) {
        var_r5 = 8;
        item->xC30 = coll->left_facing_wall.index;
        sp38 = coll->left_facing_wall.normal;
    }
    if (coll->env_flags & Collide_RightWallMask) {
        var_r5 = 4;
        item->xC30 = coll->right_facing_wall.index;
        sp38 = coll->right_facing_wall.normal;
    }
    if (var_r5 != 0) {
        if (((item->x40_vel.z * sp38.z) +
             ((item->x40_vel.x * sp38.x) + (item->x40_vel.y * sp38.y))) < 0.0f)
        {
            lbVector_Mirror(&item->x40_vel, &sp38);
        }
        mult = attr->x58;
        ret_val = true;
        item->x40_vel.x *= mult;
        item->x40_vel.y *= mult;
        item->x40_vel.z *= mult;
    }
    return ret_val;
}

static inline float product_xy(Vec3* a, Vec3* b)
{
    return (a->x * b->x + a->y * b->y);
}

static inline float return_sqrt_value(Vec3* v)
{
    return sqrtf_accurate(product_xy(v, v));
}

bool it_8027781C(Item_GObj* item_gobj)
{
    Item* item;
    CollData* coll;
    ItemAttr* attr;
    // PAD_STACK(8);
    s32 stack[2];

    f32 speed;
    bool chk;
    Vec3 sp48;
    Vec3 sp3C;
    Vec3 sp30;

    item = GET_ITEM(item_gobj);
    attr = item->xCC_item_attr;
    coll = &item->x378_itemColl;
    sp3C = it_803B8570;
    // sp3C.x = sp3C.y = sp3C.z = 0.0f;
    chk = false;
    sp30 = it_803B857C;

    speed = return_sqrt_value(&item->x40_vel);
    if ((coll->env_flags & Collide_LeftWallMask) &&
        product_xy(&item->x40_vel, &coll->left_facing_wall.normal) < 0.0f)
    {
        sp48 = item->x40_vel;
        lbVector_Mirror(&sp48, &coll->left_facing_wall.normal);
        lbVector_Add_xy(&sp30, &sp48);
        if (mpCollGetSpeedLeftWall(coll, &sp48)) {
            lbVector_Add_xy(&sp3C, &sp48);
        }
        chk = true;
    }
    if ((coll->env_flags & Collide_RightWallMask) &&
        product_xy(&item->x40_vel, &coll->right_facing_wall.normal) < 0.0f)
    {
        sp48 = item->x40_vel;
        lbVector_Mirror(&sp48, &coll->right_facing_wall.normal);
        lbVector_Add_xy(&sp30, &sp48);
        if (mpCollGetSpeedRightWall(coll, &sp48)) {
            lbVector_Add_xy(&sp3C, &sp48);
        }
        chk = true;
    }
    if ((coll->env_flags & Collide_CeilingMask) &&
        product_xy(&item->x40_vel, &coll->ceiling.normal) < 0.0f)
    {
        sp48 = item->x40_vel;
        lbVector_Mirror(&sp48, &coll->ceiling.normal);
        lbVector_Add_xy(&sp30, &sp48);
        if (mpCollGetSpeedCeiling(coll, &sp48)) {
            lbVector_Add_xy(&sp3C, &sp48);
        }
        chk = true;
    }
    if ((coll->env_flags & Collide_FloorMask) &&
        product_xy(&item->x40_vel, &coll->floor.normal) < 0.0f)
    {
        sp48 = item->x40_vel;
        lbVector_Mirror(&sp48, &coll->floor.normal);
        lbVector_Add_xy(&sp30, &sp48);
        if (mpCollGetSpeedFloor(coll, &sp48)) {
            lbVector_Add_xy(&sp3C, &sp48);
        }
        chk = true;
    }
    if (chk) {
        if (return_sqrt_value(&sp30) < 0.01f) {
            sp30.x = item->x40_vel.x;
            sp30.y = -1.0f * item->x40_vel.y;
        }
        lbVector_NormalizeXY(&sp30);
        speed *= attr->x58;
        sp30.x *= speed;
        sp30.y *= speed;
        item->x64_vec_unk2 = sp3C;
        item->x40_vel = sp30;

        return true;
    }
    return false;
}

void it_80277C40(Item_GObj* item_gobj, s32 arg1)
{
    Vec3 sp20;
    Vec3 sp14;
    CollData* coll;
    Item* item;

    item = GET_ITEM(item_gobj);
    coll = &item->x378_itemColl;
    sp14.z = 0.0f;
    sp14.y = 0.0f;
    sp14.x = 0.0f;
    sp20.z = 0.0f;
    sp20.y = 0.0f;
    sp20.x = 0.0f;
    if (arg1 & 8) {
        sp20.x = coll->ecb.right.x;
        sp20.y = coll->ecb.right.y;
    }
    if (arg1 & 4) {
        sp20.x = coll->ecb.left.x;
        sp20.y = coll->ecb.left.y;
    }
    if (arg1 & 2) {
        sp20.x = coll->ecb.top.x;
        sp20.y = coll->ecb.top.y;
    }
    if (arg1 & 1) {
        sp20.x = coll->ecb.bottom.x;
        sp20.y = coll->ecb.bottom.y;
    }
    if (!item->xDCF_flag.b0) {
        it_80278800(item_gobj, 0x405, 0, &sp20, &sp14, 0U, 0.0f);
    }
}
