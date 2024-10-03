#include "it/forward.h"

#include "it_2E6A.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "it/items/types.h"
#include "it/types.h"
#include "lb/lb_00B0.h"

// static void it_802E6D60(Item_GObj* arg0);                       /* static */
static void it_802E6D60(HSD_GObj* arg0); /* static */
// static bool it_802E7054(Item_GObj* gobj);                    /* static */
static bool it_802E7054(HSD_GObj* gobj); /* static */
// static Article it_803F8C08 = {

static ItemAttr it_803F8C08 = {
    // 0x31080000
    0,          // x0_is_heavy?
    6,          // x0_78?
    1,          // x0_hold_kind?
    0,          // x1_1?
    0,          // x1_3?
    0,          // x1_4?
    1,          // x1_5?
    0,          // x1_67_cam_kind?
    0,          // x1_8?
    0,          // x3?
    0,          // x4_throw_speed_mul
    0,          // x8
    0,          // xC_spin_speed
    0,          // x10_fall_speed
    0,          // x14_fall_speed_max
    0,          // x18
    0,          // x1C_damage_mul
    0,          // x20.top?
    0,          // x20.bottom?
    0,          // x20.right?
    0,          // x20.left?
    0,          // x30_unk.x?
    0,          // x30_unk.y?
    0,          // x38_grab_range.x?
    0,          // x38_grab_range.y?
    2.0f,       // x40.top?
    2.0f,       // x40.bottom?
    2.0f,       // x40.right?
    2.0f,       // x40.left?
    0,          // x50?
    0,          // x54?
    0,          // x58?
    0,          // x5C?
    1.0f,       // x60_scale?
    0,          // destroy_gfx? - 0xFFFFFFFF
    0,          // x68? - 0xFFFFFFFF
    0x00083D60, // x6C?
    0x00083D60, // x70?
    0x00083D60, // x74?
    0x00083D60, // destroy_sfx?
    0x00083D60, // x7C?
    0x00083D60, // x80?
    // Missing 0x84 - 0x9C?
};

ItemStateTable it_803F8C8C[] = {
    { 0, NULL, it_802E6D60, NULL },  { 1, NULL, it_802E6D60, NULL },
    { 2, NULL, it_802E6D60, NULL },  { 3, NULL, it_802E6D60, NULL },
    { 4, NULL, it_802E6D60, NULL },  { 5, NULL, it_802E6D60, NULL },
    { 6, NULL, it_802E6D60, NULL },  { 7, NULL, it_802E6D60, NULL },
    { 8, NULL, it_802E6D60, NULL },  { 9, NULL, it_802E6D60, NULL },
    { 10, NULL, it_802E6D60, NULL }, { 11, NULL, it_802E6D60, NULL },
    { 12, NULL, it_802E6D60, NULL }, { 13, NULL, it_802E6D60, NULL },
    { 14, NULL, it_802E6D60, NULL }, { 15, NULL, it_802E6D60, NULL },
    { 16, NULL, it_802E6D60, NULL }, { 17, NULL, it_802E6D60, NULL },
    { 18, NULL, it_802E6D60, NULL }, { 19, NULL, it_802E6D60, NULL },
};

// static s8 it_803F8DCC[0x10] = "%s:%d: oioi...\n";
// static u8 it_803F8DDC[9] = "ityaku.c";
// static s8 it_804D56B8[7] = "jobj.h";
// static s8 it_804D56C0[5] = "jobj";
static Vec3 it_803B8730 = { 1.0f, 1.0f, 1.0f };

HSD_GObj* it_802E6AEC(Ground* arg0, int arg1, int arg2, HSD_JObj* arg3,
                      Vec3 pos, int arg5, int arg6, HSD_GObjEvent arg7,
                      int arg8)
{
    // bool it_802E6AEC(Ground* arg0, int arg1, int arg2, HSD_JObj* arg3, Vec3
    // pos, int arg5, int arg6, HSD_GObjEvent arg7, int arg8) { bool
    // it_802E6AEC(int arg0, int arg1, int arg2, HSD_JObj* arg3, Vec3 pos, int
    // arg5, int arg6, int arg7, int arg8) {
    SpawnItem spawn;
    Vec3 sp30;
    HSD_JObj* item_jobj;
    Item* item;
    Item_GObj* item_gobj;
    s32 var_r4;

    spawn.kind = Pokemon_Random; // 44
    if (arg3) {
        lb_8000B1CC(arg3, 0, &spawn.prev_pos);
    } else {
        if (&pos != NULL) {
            spawn.prev_pos = pos;
        } else {
            return NULL;
        }
    }
    var_r4 = 0;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = 0.0f;
    spawn.x3C_damage = 0;
    // spawn.x3C_damage = var_r4;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = 0;
    // spawn.x0_parent_gobj = (HSD_GObj*) var_r4;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    if (arg5 != 0) {
        var_r4 = 1;
    }
    spawn.x44_flag.b0 = var_r4;
    // spawn.x44_flag.b0 = 1 | ((var_r4 << 7) & 0x80);
    spawn.x40 = 0;
    // *it_804D6D38[spawn.kind].unk-AC = &it_803F8C08;
    it_804D6D38[spawn.kind - 0x2B]->x0_common_attr = &it_803F8C08;
    // it_804D6D38[Pokemon_Random] = &it_803F8C08;

    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        item = GET_ITEM((HSD_GObj*) item_gobj);
        if (arg3 != 0) {
            item->xDD4_itemVar.it_2E6A_1.x2 = 1;
            item->xDD4_itemVar.it_2E6A_1.x4 = arg3;
        } else if (&pos != 0) {
            item->xDD4_itemVar.it_2E6A_2.x2 = 2;
            item->xDD4_itemVar.it_2E6A_2.x4 = pos;
        }

        item->xDD4_itemVar.it_2E6A_1.x0 = arg1;
        item->xDD4_itemVar.it_2E6A_1.x10 = arg0;
        item->xDD4_itemVar.it_2E6A_1.x14 = (void*) arg6;
        item->xDD4_itemVar.it_2E6A_1.x18 = arg7;
        item->xDD4_itemVar.it_2E6A_1.x1C = (void*) arg8;
        item_jobj = GET_JOBJ((HSD_GObj*) item_gobj);
        sp30 = it_803B8730;
        HSD_JObjSetScale(item_jobj, &sp30);
        item->xDCC_flag.b3 = 0;
        it_802756D0(item_gobj);
        Item_80268E5C((HSD_GObj*) item_gobj, arg2, ITEM_ANIM_UPDATE);
        item->touched = it_802E7054;
        item->x378_itemColl.x34_flags.b1234 = 5;
    }
    return (HSD_GObj*) item_gobj;
}

// void it_802E6D60(Item_GObj* item_gobj) {
void it_802E6D60(HSD_GObj* item_gobj)
{
    Vec3 sp24;
    Quaternion sp14;
    HSD_JObj* jobj1;
    HSD_JObj* jobj2;
    HSD_JObj* item_jobj;
    Item* item;
    PAD_STACK(4);

    item = GET_ITEM((HSD_GObj*) item_gobj);
    item_jobj = item_gobj->hsd_obj;
    if (item->xDD4_itemVar.it_2E6A_1.x2 == 1) {
        lb_8000B1CC(item->xDD4_itemVar.it_2E6A_1.x4, NULL, &sp24);
        item->pos = sp24;
        jobj1 = item->xDD4_itemVar.it_2E6A_1.x4;
        HSD_JObjGetScale(jobj1, &sp24);
        HSD_JObjSetScale(item_jobj, &sp24);
        jobj2 = item->xDD4_itemVar.it_2E6A_1.x4;
        HSD_JObjGetRotation(jobj2, &sp14);
        HSD_JObjSetRotation(item_jobj, &sp14);
    } else if (item->xDD4_itemVar.it_2E6A_1.x2 != 2) {
        OSReport("%s:%d: oioi...\n", "ityaku.c", 0xD7);
        // while (false) {}
    loop_29:
        goto loop_29;
    }
}

bool it_802E6F7C(Item_GObj* item_gobj)
{
    Item* item;
    // void (*temp_r12)();

    item = item_gobj->user_data;
    // temp_r12 = item->xDD4_itemVar.it_2E6A_1.x14;
    if ((item->xDD4_itemVar.it_2E6A_1.x14 != 0U) &&
        (item->xDD4_itemVar.it_2E6A_1.x10 != 0U))
    {
        // temp_r12();
        ((void (*)(HSD_GObj*)) item->xDD4_itemVar.it_2E6A_1.x14)(
            (HSD_GObj*) item_gobj);
    }
    return false;
}

bool it_802E6FC0(Item_GObj* item_gobj)
{
    Vec3 sp10;
    Item* item;
    // void (*temp_r12)(Item_GObj*, Vec3*, HSD_GObj*, f32);
    HSD_GObj* fighter_gobj;

    item = GET_ITEM((HSD_GObj*) item_gobj);
    item->xC9C = 0;
    it_8027B798(item_gobj, &sp10);
    // temp_r12 = item->xDD4_itemVar.it_2E6A_1.x18;
    fighter_gobj = item->xCEC_fighterGObj;
    if ((item->xDD4_itemVar.it_2E6A_1.x18 != 0U) &&
        (item->xDD4_itemVar.it_2E6A_1.x10 != 0U))
    {
        ((void (*)(Item_GObj*, Vec3*, HSD_GObj*,
                   f32)) item->xDD4_itemVar.it_2E6A_1.x18)(
            item_gobj, &sp10, fighter_gobj, item->xCA0);
        // temp_r12(item_gobj, &sp10, fighter_gobj, item->xCA0);
    }
    return false;
}

// bool it_802E7054(Item_GObj* item_gobj) {
bool it_802E7054(HSD_GObj* item_gobj)
{
    // void (*temp_r12)(HSD_GObj*);
    Item* item;

    item = GET_ITEM(item_gobj);
    // temp_r12 = item->xDD4_itemVar.it_2E6A_1.x1C;
    if ((item->xDD4_itemVar.it_2E6A_1.x1C != NULL) &&
        (item->xDD4_itemVar.it_2E6A_1.x10 != 0U))
    {
        // temp_r12(item->toucher)
        ((void (*)(HSD_GObj*)) item->xDD4_itemVar.it_2E6A_1.x1C)(
            item->toucher);
    }
    return false;
}

void it_802E709C(Item_GObj* item_gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(item_gobj, ref_gobj);
}
