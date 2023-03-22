#include "forward.h"

#include "item.h"

#include "code_80266F3C.h"
#include "item2.h"

#include "cm/camera.h"
#include "db/db_2253.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ft/ftlib.h"
#include "gm/gm_1601.h"
#include "gr/grlib.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbunknown_001.h"
#include "lb/lbunknown_003.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <dolphin/mtx/types.h>
#include <dolphin/mtx/vec.h>
#include <dolphin/os/os.h>
#include <baselib/gobj.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>

/// Check if items are enabled
bool func_80266F3C(void)
{
    if (gm_8016AE80() != -1)
        return true;

    return false;
}

/// Check to load ItCo.dat/usd
void func_80266F70(void)
{
    func_8027870C(func_80266F3C());
}

/// ItCo prefunction with 0
void func_80266FA8(void)
{
    func_8027870C(false);
}

/// @private
HSD_ObjAllocData itemAllocData;

/// @private
HSD_ObjAllocData unkAllocData1;

HSD_ObjAllocData lbl_804A0C38;
HSD_ObjAllocUnk lbl_804A0C64;
HSD_ObjAllocUnk2 lbl_804A0CCC;
S32Vec3 lbl_804A0E24;

/// Init item struct?
void func_80266FCC(void)
{
    HSD_ObjAllocInit(&itemAllocData, sizeof(Item), 4);
    HSD_ObjAllocInit(&unkAllocData1, sizeof(DynamicBoneTable), 4);
    HSD_ObjAllocInit(&lbl_804A0C38, sizeof(ItemLink), 4);

    lbl_804A0C64.x0 = 0;
    lbl_804A0C64.x8 = 0;
    lbl_804A0C64.x10 = 0;
    lbl_804A0C64.x18 = 0;
    lbl_804A0C64.x1C = 0;
    lbl_804A0C64.x24 = 0;
    lbl_804A0C64.x2C = 0;
    lbl_804A0C64.x34 = 0;
    lbl_804A0C64.x3C = 0;
    lbl_804A0C64.x40 = 0;
    lbl_804A0C64.x48 = 0;
    lbl_804A0C64.x50 = 0;
    lbl_804A0C64.x58 = 0;
    lbl_804A0C64.x60 = 0;

    lbl_804A0C64.x4 = lbl_804D6D28->x0;
    lbl_804A0C64.xC = lbl_804D6D28->x4;
    lbl_804A0C64.x14 = lbl_804D6D28->x8;
    lbl_804A0C64.x20 = lbl_804D6D28->xC;
    lbl_804A0C64.x28 = lbl_804D6D28->x10;
    lbl_804A0C64.x30 = lbl_804D6D28->x14;
    lbl_804A0C64.x38 = lbl_804D6D28->x18;
    lbl_804A0C64.x44 = lbl_804D6D28->x1C;
    lbl_804A0C64.x4C = lbl_804D6D28->x24;
    lbl_804A0C64.x54 = lbl_804D6D28->x20;
    lbl_804A0C64.x5C = lbl_804D6D28->x28;
    lbl_804A0C64.x64 = lbl_804D6D28->x148;

    lbl_804A0CCC.x154.bits.b0 = true;
    lbl_804A0CCC.x150 = 1;

    lbl_804A0E24.x = -1;
    lbl_804A0E24.y = -1;
    lbl_804A0E24.z = 0;

    lbl_804D6D00 = -1;
    lbl_804D6D14 = 1;
    lbl_804D6D10 = 0;
    lbl_804D6D0C = 0;
    lbl_804D6D08 = 0;

    lbl_804A0E60.x8 = 0;
    lbl_804A0E50.x8 = 0;
    lbl_804A0E30.xC = 0;
    lbl_804A0E60.x0 = 0;
    lbl_804A0E50.x0 = 0;
    lbl_804A0E30.x4 = 0;
}

/// @private
void ItUnkHoldKind(HSD_GObj* item_gobj)
{
    Item* it = (Item*) HSD_GObjGetUserData(item_gobj);

    switch (it->hold_kind) {
    case 4:
    case 5:
    case 6:
    case 7: {
        int temp_r3 = gm_8017E068();
        if (temp_r3 >= 0)
            it->xC3C = lbl_804D6D28->x80_float[temp_r3];
    }
    }
}

/// @private
void HSD_JObjSetScaleItem(Item* it, HSD_JObj* jobj, Vec3* scl)
{
    scl->x = scl->y = scl->z = it->scl;
    HSD_JObjSetScale(jobj, scl);
}

/// @private
inline void HSD_JObjSetFacingDirItem(HSD_JObj* jobj, Item* it)
{
    if (it->xDC8_word.flags.x19 == true)
        HSD_JObjSetRotationY(jobj, M_PI / 2 * it->facing_dir);
}

/// @private
void func_80267130(HSD_GObj* item_gobj, SpawnItem* spawnItem)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    HSD_JObj* model = (HSD_JObj*) HSD_GObjGetHSDObj(item_gobj);

    item_data->pos = spawnItem->prev_pos;
    item_data->init_facing_dir = item_data->facing_dir = spawnItem->facing_dir;
    item_data->owner = spawnItem->x0_parent_gobj;

    {
        int facing_dir;

        if (item_data->facing_dir == -1.0F)
            facing_dir = -1;
        else
            facing_dir = 1;

        func_800436D8(&item_data->x378_itemColl, facing_dir);
    }

    HSD_JObjSetFacingDirItem(model, item_data);
    func_80273500(item_gobj, &spawnItem->vel);

    item_data->x5CC_currentAnimFrame = 0.0f;
    item_data->x5D0_animFrameSpeed = 1.0f;

    func_802753BC(item_gobj, spawnItem->x3C_damage);
    func_802753DC(item_gobj);

    item_data->xC64_reflectGObj = NULL;
    item_data->xDCC_flag.b0 = false;

    item_data->xC90_absorbGObj = NULL;
    item_data->xD0C = 0;

    func_8026B390(item_gobj);
    item_data->xDC8_word.flags.x13 = false;

    if (spawnItem->x48_ground_or_air == GA_Air)
        func_802762BC(item_data);
    else
        func_802762B0(item_data);

    func_80275E98(item_gobj, spawnItem);
    func_80274DAC(item_gobj);
    HSD_JObjSetTranslate(model, &item_data->pos);
    func_80274658(item_gobj, lbl_804D6D28->x6C_float);
    func_802725D4(item_gobj);
    func_80271508(item_gobj, 0);
    func_80272280(item_gobj);

    item_data->on_accessory = NULL;
    item_data->touched = NULL;
    item_data->entered_hitlag = NULL;
    item_data->exited_hitlag = NULL;
    item_data->jumped_on = NULL;

    if (item_data->owner != NULL)
        db_80225DD8(item_gobj, item_data->owner);
    else
        db_80225D64(item_gobj, item_data->owner);

    func_8027B0C4(item_gobj, spawnItem);
    func_80279B64(item_data);
    ItUnkHoldKind(item_gobj);
}

/// Remove Camera Box
void func_80267454(HSD_GObj* item_gobj)
{
    Item* item_data = item_gobj->user_data;

    if (item_data->xDCD_flag.bits.b01 != 0 &&

        (item_data->x520_cameraBox != NULL))
    {
        func_800290D4(item_data->x520_cameraBox);
        item_data->x520_cameraBox = NULL;
        item_data->xDCD_flag.bits.b01 = 0;
    }
}

/// @private
void func_802674AC(SpawnItem* spawnItem)
{
    ItemKind kind = spawnItem->kind;

    if (kind == It_Kind_Foods) {
        spawnItem->hold_kind = 2;
        return;
    }

    if (kind == Pokemon_Random) {
        spawnItem->hold_kind = 3;
        return;
    }

    if (kind < It_Kind_L_Gun_Ray) {
        spawnItem->hold_kind = 0;
        return;
    }

    if (kind < It_Kind_Kuriboh) {
        spawnItem->hold_kind = 1;
        return;
    }

    if (kind < It_Kind_Octarock_Stone) {
        spawnItem->hold_kind = 6;
        return;
    }

    if (kind < It_Kind_Mario_Fire) {
        spawnItem->hold_kind = 7;
        return;
    }

    if (kind < It_Kind_Unk4) {
        spawnItem->hold_kind = 8;
        return;
    }

    if (kind == It_Kind_Unk4) {
        spawnItem->hold_kind = 12;
        return;
    }

    if (kind < Pokemon_Random) {
        spawnItem->hold_kind = 11;
        return;
    }

    if (kind < Pokemon_Chicorita_Leaf) {
        spawnItem->hold_kind = 9;
        return;
    }

    if (kind < It_Kind_Old_Kuri) {
        spawnItem->hold_kind = 10;
        return;
    }

    if (kind < It_Kind_Arwing_Laser) {
        spawnItem->hold_kind = 4;
        return;
    }

    spawnItem->hold_kind = 5;
}

/// @private
void func_802675A8(HSD_GObj* item_gobj)
{
    Item* item_data = item_gobj->user_data;

    switch (item_data->hold_kind) {
    case 0:
        lbl_804A0C64.x0--;
        break;
    case 1:
        lbl_804A0C64.x8--;
        break;
    case 2:
        lbl_804A0C64.x10--;
        break;
    case 3:
        lbl_804A0C64.x58--;
        break;
    case 4:
        lbl_804A0C64.x3C--;
        break;
    case 5:
        lbl_804A0C64.x40--;
        break;
    case 6:
        lbl_804A0C64.x2C--;
        break;
    case 7:
        lbl_804A0C64.x34--;
        break;
    case 8:
        lbl_804A0C64.x18--;
        break;
    case 9:
        lbl_804A0C64.x1C--;
        break;
    case 10:
        lbl_804A0C64.x24--;
        break;
    case 11:
        lbl_804A0C64.x48--;
        break;
    case 12:
        lbl_804A0C64.x50--;
        break;
    }

    if (gm_8018841C() && item_data->x18 == 1)
        lbl_804A0C64.x60--;
}

/// @private
void func_802676F4(HSD_GObj* item_gobj)
{
    Item* item_data = item_gobj->user_data;
    switch (item_data->hold_kind) {
    case 0:
        lbl_804A0C64.x0++;

        if (item_data->kind == 34)
            lbl_804A0C64.x1C++;

        break;
    case 1:
        lbl_804A0C64.x8++;
        break;
    case 2:
        func_80274EE8(lbl_804A0C64.x10++);
        break;
    case 3:
        lbl_804A0C64.x58++;
        break;
    case 4:
        lbl_804A0C64.x3C++;
        break;
    case 5:
        lbl_804A0C64.x40++;
        break;
    case 6:
        lbl_804A0C64.x2C++;
        break;
    case 7:
        lbl_804A0C64.x34++;
        break;
    case 8:
        lbl_804A0C64.x18++;
        break;
    case 10:
        lbl_804A0C64.x24++;
        break;
    case 11:
        lbl_804A0C64.x48++;
        break;
    case 12:
        lbl_804A0C64.x50++;
        break;
    }

    if (gm_8018841C() && item_data->x18 == 1)
        lbl_804A0C64.x60++;
}

/// @private
/// @remarks #func_8026862C loads two integers into this,
///          but the second one goes _?
bool func_8026784C(enum_t dropItem, int _)
{
    bool result = false;

    switch (dropItem) {
    case 0:
        if (lbl_804A0C64.x0 >= lbl_804A0C64.x4)
            result = true;

        break;

    case 1:
        if (lbl_804A0C64.x8 >= lbl_804A0C64.xC)
            result = true;

        break;

    case 2:
        if (lbl_804A0C64.x10 >= lbl_804A0C64.x14)
            result = true;

        break;

    case 3:
        if (lbl_804A0C64.x58 >= lbl_804A0C64.x5C)
            result = true;

        break;

    case 5:
        if (lbl_804A0C64.x40 >= lbl_804A0C64.x44)
            result = true;

        break;

    case 7:
        if (lbl_804A0C64.x34 >= lbl_804A0C64.x38)
            result = true;

        break;

    case 9:
        if (lbl_804A0C64.x1C > lbl_804A0C64.x20) {
            lbl_804A0C64.x1C--;
            result = true;
        }

        break;

    case 10:
        if (lbl_804A0C64.x24 >= lbl_804A0C64.x28)
            result = true;

        break;

    case 11:
        if (lbl_804A0C64.x48 >= lbl_804A0C64.x4C)
            result = true;

        break;

    case 12:
        if (lbl_804A0C64.x50 >= lbl_804A0C64.x54)
            result = true;
    }

    return result;
}

extern CommonItemArticles* lbl_804D6D24;
extern UnkItemArticles* lbl_804D6D38;
extern UnkItemArticles2* lbl_804D6D30;
extern UnkItemArticles3 lbl_804A0F60[];

extern struct ItemLogicTable lbl_803F14C4[];
extern struct ItemLogicTable lbl_803F3100[];
extern struct ItemLogicTable lbl_803F23CC[];
extern struct ItemLogicTable lbl_803F4D20[];

void func_80267978(HSD_GObj* item_gobj)
{
    Item* item_data = item_gobj->user_data;
    if (item_data->kind < It_Kind_Kuriboh) {
        // Common items
        item_data->xC4_article_data =
            lbl_804D6D24->article_ptr[item_data->kind];
        item_data->xB8_itemLogicTable = &lbl_803F14C4[item_data->kind];
    } else if (item_data->kind < Pokemon_Tosakinto) {
        // Character items
        int idx = item_data->kind - It_Kind_Kuriboh;
        item_data->xC4_article_data = lbl_804D6D38->unkptr[idx];
        item_data->xB8_itemLogicTable = &lbl_803F3100[idx];
    } else if (item_data->kind < It_Kind_Old_Kuri) {
        // Pokemon
        int idx = item_data->kind - Pokemon_Tosakinto;
        item_data->xC4_article_data = lbl_804D6D30->unkptr[idx];
        item_data->xB8_itemLogicTable = &lbl_803F23CC[idx];
    } else {
        // Stage items
        int idx = item_data->kind - It_Kind_Old_Kuri;
        item_data->xC4_article_data = lbl_804A0F60->unkptr[idx];
        item_data->xB8_itemLogicTable = &lbl_803F4D20[idx];
        if (item_data->xC4_article_data == NULL) {
            OSReport("not found zako model data! check ground dat file!\n");
            __assert("item.c", 686, "0");
        }
    }
    item_data->xBC_itemStateContainer = item_data->xB8_itemLogicTable->states;
}

extern unk_t db_80225B20(void);

/// @private
void func_80267AA8(HSD_GObj* item_gobj, SpawnItem* spawnItem)
{
    ItemAttr* item_attr;
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    item_data->kind = spawnItem->kind;
    item_data->hold_kind = spawnItem->hold_kind;
    item_data->x18 = spawnItem->x10;
    item_data->x1C = lbl_804D6D10++;
    item_data->entity = item_gobj;
    func_80267978(item_gobj);
    item_data->msid = -1;
    item_data->xC8_joint =
        item_data->xC4_article_data->x10_modelDesc->x0_joint;
    item_data->xCC_item_attr = item_data->xC4_article_data->x0_common_attr;
    item_data->owner = NULL;
    item_data->xDC8_word.flags.x0 = 0;
    item_data->x378_itemColl.x19C = -1;
    item_data->xDC4 = 0;
    item_data->xDC8_word.flags.xF = 0;
    item_data->xCC4 = 0;
    item_data->xDCF_flag.bits.b6 = 0;
    item_data->xDCF_flag.bits.b7 = 0;
    item_data->xCB0_source_ply = 6;
    item_data->xCB4 = -1;
    item_data->xC38 = -1;
    item_data->xCE8 = 0.0f;
    item_data->xCE4 = 0.0f;
    item_data->xCE0 = 0.0f;
    item_data->xCDC = 0.0f;
    item_data->xCD8 = 0.0f;
    item_data->xCD4 = 0.0f;
    item_data->xDD0_flag.bits.b1 = 0;
    item_data->xDC8_word.flags.x14 = 0;
    item_data->xDC8_word.flags.xE = 0;
    item_data->xCEC_fighterGObj = NULL;
    item_data->xCF0_itemGObj = NULL;
    item_data->xCF4_fighterGObjUnk = NULL;
    item_data->toucher = NULL;
    item_data->xC64_reflectGObj = NULL;
    item_data->xCFC = 0;
    item_data->atk_victim = 0;
    item_data->grab_victim = 0;
    item_data->xCCC_incDamageDirection = 0.0f;
    item_data->xCB8_outDamageDirection = 0.0f;
    item_data->xC68 = 0.0f;
    item_data->xCD0 = 0.0f;
    func_80275158(item_gobj, lbl_804D6D28->x30);
    item_data->xDD0_flag.bits.b3 = false;
    item_data->spin_spd = item_data->xCC_item_attr->xC_spin_speed;
    item_data->xDC8_word.flags.x19 = item_data->xCC_item_attr->x1_3;
    item_data->xDC8_word.flags.x17 = item_data->xCC_item_attr->x1_1;
    item_attr = item_data->xCC_item_attr;
    item_data->xBCC_unk = item_attr->x30_unk;
    item_data->xBD4_grabRange = item_attr->x38_grab_range;
    item_data->xDC8_word.flags.x1A = item_data->xCC_item_attr->x1_4;
    item_attr = item_data->xCC_item_attr;
    item_data->xBEC = item_attr->x20;
    item_attr = item_data->xCC_item_attr;
    item_data->xBDC = item_attr->x20;
    item_data->xDC8_word.flags.x1C = 1;
    item_data->xDC8_word.flags.x1D = 1;
    item_data->xDC8_word.flags.x1E = 1;
    item_attr = item_data->xCC_item_attr;
    item_data->xC1C = item_attr->x40;
    item_data->xC0C = item_data->xC1C;
    item_data->xBFC = item_data->xC0C;
    item_data->xDC8_word.flags.xC = item_data->xCC_item_attr->x1_5;
    item_data->xDC8_word.flags.xD = 1;
    item_data->xDCD_flag.bits.b01 = item_data->xCC_item_attr->x1_67_cam_kind;
    item_data->xDCE_flag.bits.b3 = 0;
    item_data->xD54_throwNum = 0;
    item_data->xD50_landNum = 0;
    item_data->xD58 = 0;
    item_data->xD5C = 2;
    item_data->xDCC_flag.b3 = 1;
    item_data->xDCC_flag.b4567 = 15;
    item_data->xAC4_ignoreItemID = spawnItem->x40;
    item_data->destroy_type = 4;
    item_data->xDCE_flag.bits.b5 = 0;
    item_data->xDCE_flag.bits.b4 = 0;
    item_data->xC54 = 0.0f;
    item_data->xC58 = 0.0f;
    item_data->xC58 = 0.0f;
    item_data->xC58 = 0.0f;
    item_data->xDC8_word.flags.x9 = 0;
    item_data->xDC8_word.flags.x3 = 0;
    item_data->xDC8_word.flags.x4 = 0;
    item_data->xDC8_word.flags.x5 = 0;
    item_data->xDC8_word.flags.x6 = 0;
    item_data->xDC8_word.flags.x7 = 0;
    item_data->xDC8_word.flags.x8 = 0;
    item_data->xDD0_flag.bits.b5 = 0;
    item_data->xD09 = (s8) 0;
    item_data->xDD0_flag.bits.b4 = 0;
    item_data->xCA8 = 0;
    item_data->xCBC_hitlagFrames = 0.0f;
    item_data->xCC0 = 0.0f;
    item_data->xDC8_word.flags.xA = 0;
    item_data->xDC8_word.flags.xB = 0;
    item_data->xDCC_flag.b1 = 0;
    item_data->xC70 = 1.0f;
    item_data->xC6C = 1.0f;
    item_data->xDCC_flag.b2 = 0;
    item_data->xDD0_flag.bits.b0 = false;
    item_data->xDCE_flag.bits.b6 = false;
    item_data->xDCF_flag.bits.b0 = false;
    item_data->xDCF_flag.bits.b1 = false;
    item_data->xDCF_flag.bits.b2 = false;
    item_data->xDD1_flag.bits.b0 = false;
    item_data->xDCE_flag.bits.b7 = 1;
    item_data->scl = item_data->xCC_item_attr->x60_scale;
    item_data->x3C = 0.0f;
    item_data->xDCD_flag.bits.b3 = false;
    item_data->xDCD_flag.bits.b4 = false;
    item_data->xDD0_flag.bits.b7 = false;
    item_data->xBC0 = 0;
    item_data->xDD1_flag.bits.b1 = false;
    item_data->xDCD_flag.bits.b2 = false;
    item_data->xD6C = -1;
    item_data->sfx_unk2 = SFX_NONE;
    item_data->sfx_unk1 = SFX_NONE;
    item_data->xD70 = item_data->xCC_item_attr->x6C;
    item_data->xD74 = item_data->xCC_item_attr->x70;
    item_data->xD78 = item_data->xCC_item_attr->x74;
    item_data->destroy_sfx = item_data->xCC_item_attr->destroy_sfx;
    item_data->xD80 = item_data->xCC_item_attr->x7C;
    item_attr = item_data->xCC_item_attr;
    item_data->xD84 = item_attr->x80;

    func_80275474(item_gobj);
    func_80275504(item_gobj);
    func_80274EF8(item_gobj);

    if (ftLib_80086960(spawnItem->x0_parent_gobj))
        item_data->xDC8_word.flags.x1 = false;
    else
        item_data->xDC8_word.flags.x1 = true;

    item_data->x5C8 = 0;
    item_data->xBC7 = 0;
    item_data->xBC6 = 0;
    item_data->xBC5 = 0;
    item_data->xBC4 = 0;
    item_data->x5C9 = 255;

    func_80279B64(item_data);

    item_data->xDCF_flag.bits.b3 = false;
    item_data->xDCF_flag.bits.b4 = false;
    item_data->xDCF_flag.bits.b5 = false;

    item_data->xDAA_byte = 1;

    if (db_80225B20() != NULL)
        item_data->xDAA_flag.bits.b4 = true;

    if (spawnItem->x0_parent_gobj == NULL) {
        item_data->x20_team_id = -1;
    } else if (ftLib_80086960(spawnItem->x0_parent_gobj)) {
        item_data->x20_team_id = ftLib_80086EB4(spawnItem->x0_parent_gobj);
    } else if (func_80272D1C(spawnItem->x0_parent_gobj)) {
        item_data->x20_team_id = func_8026B7B0(spawnItem->x0_parent_gobj);
    } else {
        item_data->x20_team_id = -1;
    }
}

extern void PSMTXIdentity(Mtx); /* extern */
extern u8 lbl_804D7849;

/// Setup Item JObj
void func_802680CC(HSD_GObj* item_gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);

    if (item_data->xC8_joint != NULL) {
        HSD_JObj* jobj = HSD_JObjLoadJoint(item_data->xC8_joint);
        func_80390A70(item_gobj, lbl_804D7849, jobj);
    } else {
        HSD_JObj* jobj = HSD_JObjAlloc();
        PSMTXIdentity(jobj->mtx);
        jobj->scl = NULL;
        func_80390A70(item_gobj, lbl_804D7849, jobj);
    }
}

extern HSD_DObj* HSD_JObjGetDObj(HSD_JObj*);
extern void* lbl_803F1F90[];

/// @private
void func_8026814C(HSD_GObj* item_gobj)
{
#ifdef MUST_MATCH
    u8 _[8];
#endif
    HSD_MObj* temp_r0;
    HSD_DObj* var_r0;
    HSD_JObj* var_r0_2;
    HSD_JObj* var_r30;
    HSD_DObj* var_r29;
    HSD_JObj* var_r3;

    var_r30 = (HSD_JObj*) HSD_GObjGetHSDObj(item_gobj);
    while (var_r30 != NULL) {
        var_r29 = HSD_JObjGetDObj(var_r30);
    loop_2:
        if (var_r29 != NULL) {
            temp_r0 = var_r29->mobj;
            if (temp_r0 != NULL) {
                hsdChangeClass(temp_r0, &lbl_803F1F90);
            }
            var_r29 = var_r0 = (var_r29 != NULL) ? var_r29->next : NULL;
            goto loop_2;
        }
        if (var_r30 == NULL) {
            var_r0_2 = NULL;
        } else {
            var_r0_2 = var_r30->child;
        }
        if (var_r0_2 != NULL) {
            var_r30 = var_r0_2 = (var_r30 == NULL) ? NULL : var_r30->child;
        } else {
            var_r0_2 = (var_r30 == NULL) ? NULL : var_r30->next;
            if (var_r0_2 != NULL) {
                var_r30 = var_r0_2 = (var_r30 == NULL) ? NULL : var_r30->next;
            } else {
            loop_25:
                var_r0_2 = (var_r30 == NULL) ? NULL : var_r30->parent;
                if (var_r0_2 == NULL) {
                    var_r30 = NULL;
                } else {
                    var_r3 = (var_r30 == NULL) ? NULL : var_r30->parent;
                    var_r0_2 = (var_r3 == NULL) ? NULL : var_r3->next;
                    if (var_r0_2 != NULL) {
                        var_r3 = (var_r30 == NULL) ? NULL : var_r30->parent;
                        var_r30 = var_r0_2 =
                            (var_r3 == NULL) ? NULL : var_r3->next;
                    } else {
                        var_r30 = var_r0_2 =
                            (var_r30 == NULL) ? NULL : var_r30->parent;
                        goto loop_25;
                    }
                }
            }
        }
    }
}

/// @private
/// @todo Needs some serious cleaning.
bool func_802682F0(HSD_GObj* item_gobj)
{
    s32 var_r4;
    Item* item_data;
    HSD_JObj* var_r0;
    HSD_JObj* var_r3;
    HSD_JObj* var_r3_2;
    HSD_JObj* var_r5;

    item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    if (item_data->xC4_article_data->x10_modelDesc->x4_bone_count != 0) {
        item_data->xBBC_dynamicBoneTable = HSD_ObjAlloc(&unkAllocData1);
        if (item_data->xBBC_dynamicBoneTable == NULL) {
            return false;
        }
        var_r5 = item_gobj->hsd_obj;
        var_r4 = 0;
        while (var_r5 != NULL) {
            (item_data->xBBC_dynamicBoneTable->bones[var_r4]) = var_r5;
            var_r4++;
            var_r0 = (var_r5 == NULL) ? NULL : var_r5->child;
            if (var_r0 != NULL) {
                var_r5 = var_r0 = (var_r5 == NULL) ? NULL : var_r5->child;
            } else {
                var_r0 = (var_r5 == NULL) ? NULL : var_r5->next;
                if (var_r0 != NULL) {
                    var_r5 = var_r0 = (var_r5 == NULL) ? NULL : var_r5->next;
                } else {
                loop_20:
                    var_r0 = (var_r5 == NULL) ? NULL : var_r5->parent;
                    if (var_r0 == NULL) {
                        var_r5 = NULL;
                    } else {
                        var_r3 = (var_r5 == NULL) ? NULL : var_r5->parent;
                        var_r0 = (var_r3 == NULL) ? NULL : var_r3->next;
                        if (var_r0 != NULL) {
                            var_r3_2 =
                                (var_r5 == NULL) ? NULL : var_r5->parent;
                            var_r5 = var_r0 =
                                (var_r3_2 == NULL) ? NULL : var_r3_2->next;
                        } else {
                            var_r5 = var_r0 =
                                (var_r5 == NULL) ? NULL : var_r5->parent;
                            goto loop_20;
                        }
                    }
                }
            }
        }
    } else {
        item_data->xBBC_dynamicBoneTable = NULL;
    }
    return true;
}

/// Set item model scale
void func_8026849C(HSD_GObj* item_gobj)
{
    HSD_JObj* temp_jobj = (HSD_JObj*) HSD_GObjGetHSDObj(item_gobj);
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    f32 tmp = item_data->scl;
    Vec3 sp14;
    sp14.x = sp14.y = sp14.z = tmp;
    HSD_JObjSetScale(temp_jobj, &sp14);
}

extern void func_80011710(void*, void*);

/// @private
void func_80268560(HSD_GObj* item_gobj)
{
    int i;
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    Article* article_data = item_data->xC4_article_data;
    if (article_data->x14_dynamics == NULL) {
        item_data->x374_dynamicBonesNum = 0;
        item_data->xB68 = 0;
        return;
    }
    item_data->x374_dynamicBonesNum = article_data->x14_dynamics->count;
    for (i = 0; i < article_data->x14_dynamics->count; i++) {
        ItemDynamicsDesc* desc;
        HSD_JObj* jobj;
        desc = &article_data->x14_dynamics->dyn_descs[i];
        jobj = item_data->xBBC_dynamicBoneTable->bones[desc->x0_boneID];
        func_8000FD48(jobj, &item_data->xD4_dynamicBones[i].unk_ptr,
                      desc->child_count);
        item_data->xD4_dynamicBones[i].skeleton = jobj;
        item_data->xD4_dynamicBones[i].flags = 0;
        func_80011710(&article_data->x14_dynamics->dyn_descs[i].x4_params,
                      &item_data->xD4_dynamicBones[i].unk_ptr);
    }
}

extern CameraBox* func_80029044(s32);
extern void ftLib_8008702C(s32);
extern struct sdata_ItemGXLink lbl_803F1418[];
extern struct sdata_ItemGXLink lbl_803F2310[];
extern struct sdata_ItemGXLink lbl_803F2F28[];
extern struct sdata_ItemGXLink lbl_803F4CA8[];

void foobar(HSD_GObj* gobj)
{
    Item* it = (Item*) HSD_GObjGetUserData(gobj);
    switch (it->hold_kind) {
    case 0:
    case 6:
        if (it->xD0C == 2) {
            it->xDD0_flag.bits.b7 = 1;
        }
        it->xD40 = lbl_804D6D28->x2C;
        it->xDD0_flag.bits.b6 = 1;
        func_802756D0(gobj);
        func_80279B88(it, 3, 0);
        break;

    default:
        it->xD40 = 0.0f;
        it->xDD0_flag.bits.b6 = 0;
    }
}

void foobar2(HSD_GObj* gobj)
{
    Item* it = (Item*) HSD_GObjGetUserData(gobj);
    // Check if item is a character item with an owner
    if (it->kind >= It_Kind_Mario_Fire && it->kind < It_Kind_Unk4 &&
        ftLib_80086960(it->owner))
    {
        it->xDC8_word.flags.xE = 1;
        it->x378_itemColl.x19C = ftLib_800872A4(it->owner);
        ftLib_8008702C(it->x378_itemColl.x19C);
    }
}

void foobar3(HSD_GObj* gobj)
{
    Item* it = (Item*) HSD_GObjGetUserData(gobj);
    CameraBox* cam_box;
    if (it->xDCD_flag.bits.b01 != 0) {
        if (it->xDCD_flag.bits.b01 == 1) {
            it->x520_cameraBox = func_80029044(0);
        } else {
            it->x520_cameraBox = func_80029044(2);
        }
        cam_box = it->x520_cameraBox;
        if (cam_box != NULL) {
            cam_box->x40.x = lbl_804D6D28->x14C;
            cam_box->x40.y = lbl_804D6D28->x150;
            cam_box->x48.x = lbl_804D6D28->x154;
            cam_box->x48.y = lbl_804D6D28->x158;
        }
    }
}

/// @private
HSD_GObj* func_8026862C(SpawnItem* spawnItem)
{
    HSD_GObj* gobj;
    void* user_data;

    if (func_8026784C(spawnItem->hold_kind, spawnItem->kind) != 0) {
        return NULL;
    }
    gobj = GObj_Create(6, 9, 0);
    if (gobj == NULL) {
        return NULL;
    }
    if (spawnItem->kind < It_Kind_Kuriboh) {
        // Common items
        GObj_SetupGXLink(gobj, lbl_803F1418[spawnItem->kind].x0_renderFunc, 6,
                         0);
    } else if (spawnItem->kind < Pokemon_Tosakinto) {
        // Character items
        int idx = spawnItem->kind - It_Kind_Kuriboh;
        GObj_SetupGXLink(gobj, lbl_803F2F28[idx].x0_renderFunc, 6, 0);
    } else if (spawnItem->kind < It_Kind_Old_Kuri) {
        // Pokemon
        int idx = spawnItem->kind - Pokemon_Tosakinto;
        GObj_SetupGXLink(gobj, lbl_803F2310[idx].x0_renderFunc, 6, 0);
    } else {
        // Stage items
        int idx = spawnItem->kind - It_Kind_Old_Kuri;
        GObj_SetupGXLink(gobj, lbl_803F4CA8[idx].x0_renderFunc, 6, 0);
    }
    user_data = HSD_ObjAlloc(&itemAllocData);
    if (user_data == NULL) {
        func_80390228(gobj);
        return NULL;
    }
    GObj_InitUserData(gobj, 6, Item_OnUserDataRemove, user_data);
    func_80267AA8(gobj, spawnItem);
    func_802680CC(gobj);
    if (func_802682F0(gobj) != false) {
        func_8026814C(gobj);
        func_8026849C(gobj);
        func_8027163C(gobj);
        func_80268560(gobj);
        func_8038FD54(gobj, lbl_802693E4, 0);
        func_8038FD54(gobj, lbl_80269528, 1);
        func_8038FD54(gobj, func_802697D4, 4);
        func_8038FD54(gobj, func_80269978, 5);
        func_8038FD54(gobj, lbl_80269A9C, 9);
        func_8038FD54(gobj, lbl_80269B60, 11);
        func_8038FD54(gobj, lbl_80269BE4, 12);
        func_8038FD54(gobj, lbl_80269C5C, 13);
        func_8038FD54(gobj, lbl_8026A294, 14);
        func_8038FD54(gobj, lbl_8026A788, 16);
        func_80267130(gobj, spawnItem);
        func_8026A810(gobj);
        foobar(gobj);
        func_802676F4(gobj);
        foobar2(gobj);
        foobar3(gobj);
    } else {
        func_80390228(gobj);
        return NULL;
    }
    return gobj;
}

/// Item spawn prefunction - spawn airborne
void func_80268B18(SpawnItem* spawnItem)
{
    spawnItem->x48_ground_or_air = GA_Air;
    spawnItem->x10 = 0;
    func_802674AC(spawnItem);
    func_8026862C(spawnItem);
}

/// Item spawn prefunction - spawn grounded
void func_80268B5C(SpawnItem* spawnItem)
{
    spawnItem->x48_ground_or_air = GA_Ground;
    spawnItem->x10 = 0;
    func_802674AC(spawnItem);
    func_8026862C(spawnItem);
}

/// Item spawn prefunction - spawn grounded and toggle unknown true
void func_80268B9C(SpawnItem* spawnItem)
{
    spawnItem->x48_ground_or_air = GA_Ground;
    spawnItem->x10 = 1;
    func_802674AC(spawnItem);
    func_8026862C(spawnItem);
}

/// @private
void func_80268BE0(HSD_JObj* item_jobj, HSD_AnimJoint* anim_joint,
                   HSD_MatAnimJoint* matanim_joint,
                   HSD_ShapeAnimJoint* shapeanim_joint, Item* item_data)
{
    void* functionArg1;
    void* functionArg2;
    void* functionArg3;

    s32 temp_r0;

    if (item_jobj != NULL) {
        if (anim_joint != NULL) {
            for (temp_r0 = 0; temp_r0 < item_data->x374_dynamicBonesNum;
                 temp_r0++)
                if (item_jobj == item_data->xD4_dynamicBones[temp_r0].skeleton)
                {
                    if (anim_joint->next != NULL) {
                        functionArg1 = NULL;
                        functionArg2 = NULL;
                        functionArg3 = NULL;
                        if (anim_joint != NULL) {
                            functionArg1 = anim_joint->next;
                        }
                        if (matanim_joint != NULL) {
                            functionArg2 = matanim_joint->next;
                        }
                        if (shapeanim_joint != NULL) {
                            functionArg3 = shapeanim_joint->next;
                        }
                        func_80268BE0(item_jobj->next, functionArg1,
                                      functionArg2, functionArg3, item_data);
                    }
                    return;
                }
        }
        HSD_JObjAddAnim(item_jobj, anim_joint, matanim_joint, shapeanim_joint);
        if (item_jobj->child != NULL) {
            functionArg1 = NULL;
            functionArg2 = NULL;
            functionArg3 = NULL;
            if (anim_joint != NULL) {
                functionArg1 = anim_joint->child;
            }
            if (matanim_joint != NULL) {
                functionArg2 = matanim_joint->child;
            }
            if (shapeanim_joint != NULL) {
                functionArg3 = shapeanim_joint->child;
            }
            func_80268BE0(item_jobj->child, functionArg1, functionArg2,
                          functionArg3, item_data);
        }
        if (item_jobj->next != NULL) {
            functionArg1 = NULL;
            functionArg2 = NULL;
            functionArg3 = NULL;
            if (anim_joint != NULL) {
                functionArg1 = anim_joint->next;
            }
            if (matanim_joint != NULL) {
                functionArg2 = matanim_joint->next;
            }
            if (shapeanim_joint != NULL) {
                functionArg3 = shapeanim_joint->next;
            }
            func_80268BE0(item_jobj->next, functionArg1, functionArg2,
                          functionArg3, item_data);
        }
    }
}

/// Unk Item AObj-related function
void func_80268D34(HSD_GObj* item_gobj, struct ItemStateDesc* itemStateDesc)
{
    HSD_JObj* item_jobj = (HSD_JObj*) HSD_GObjGetHSDObj(item_gobj);
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    HSD_JObjRemoveAnimAll(item_jobj);
    if (item_data->xC8_joint != NULL) {
        unk_t bonestruct_arg;
        if (item_jobj == NULL) {
            bonestruct_arg = NULL;
        } else {
            bonestruct_arg = item_jobj->child;
        }
        func_8000B804(bonestruct_arg, item_data->xC8_joint->child);
    }
    func_80268BE0(item_jobj, itemStateDesc->x0_anim_joint,
                  itemStateDesc->x4_matanim_joint,
                  itemStateDesc->x8_parameters, item_data);
    func_8000BA0C(item_jobj, item_data->x5D0_animFrameSpeed);
    HSD_JObjReqAnimAll(item_jobj, 0.0f);
}

/// Advance item animation?
void func_80268DD4(HSD_GObj* item_gobj, f32 frame)
{
    HSD_JObj* item_jobj;
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    item_jobj = (HSD_JObj*) HSD_GObjGetHSDObj(item_gobj);
    func_8000BA0C(item_jobj, item_data->x5D0_animFrameSpeed);
    HSD_JObjReqAnimAll(item_jobj, frame);
    HSD_JObjAnimAll(item_jobj);
    item_data->x5CC_currentAnimFrame = func_8000BDB4(item_jobj);
}

/// Copy item script
void func_80268E40(Item* item_data, struct ItemStateDesc* itemStateDesc)
{
    item_data->x52C_item_script = itemStateDesc->xC_script;
    item_data->x530 = 0;
    item_data->x524 = 0.0f;
}

extern struct r13_ColAnimStruct* lbl_804D6D04;

void func_80268E5C(HSD_GObj* item_gobj, enum_t msid,
                   Item_StateChangeFlags flags)
{
    Vec3 sp4C;
    Vec3 scl;
    ItemStateTable* temp_r30;
    ItemStateDesc* temp_r29;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12];
#endif

    HSD_JObj* item_jobj1_2;

    unk_t new_var;
    unk_t new_var2;
    unk_t new_var3;
    Item* item_data3;
    HSD_JObj* item_jobj;
    Item* item_data;
    ItemAttr* item_attr;
    ItemStateDesc* temp_r23;
    s32 temp_r0;

    item_jobj = (HSD_JObj*) HSD_GObjGetHSDObj(item_gobj);
    item_data = (Item*) HSD_GObjGetUserData(item_gobj);

    item_data->msid = msid;
    item_data->xDC8_word.flags.x14 = 0;
    HSD_JObjSetTranslate(item_gobj->hsd_obj, &item_data->pos);
    func_80067624(item_gobj, &item_data->xBC0);

    if (item_data->xDC8_word.flags.x2 == 1) {
        func_8026BDCC(item_gobj);
        func_80274EF8(item_gobj);
    }

    if ((flags & ITEM_MODEL_UPDATE))
        func_80274740(item_gobj);

    if (!(flags & ITEM_COLANIM_PRESERVE) &&
        lbl_804D6D04[item_data->x548_colorOverlay.x28_colanim].x5_unk != 0)
    {
        func_80279BBC(item_data);
    }

    if (!(flags & ITEM_SFX_PRESERVE))
        func_8026B074(item_data);

    HSD_JObjSetFacingDirItem(item_jobj, item_data);

    if ((flags & ITEM_DROP_UPDATE))
        item_data->xC40 = item_data->xC44;
    else
        item_data->xC40 = 1.0F;

    if (!(flags & ITEM_HIT_PRESERVE) && item_data->xDC8_word.flags.x16)
        func_802725D4(item_gobj);

    item_data->xCC8_knockback = 0.0F;
    temp_r30 =
        (new_var = &item_data->xBC_itemStateContainer->stateTable[msid]);
    item_data->anim_id = temp_r30->msid;
    item_data->x5CC_currentAnimFrame = 0.0F;
    temp_r0 = item_data->anim_id;

    if (temp_r0 != -1) {
        item_data->xD0_itemStateDesc =
            (temp_r23 =
                 (temp_r29 =
                      (new_var2 = &item_data->xC4_article_data->xC_itemStates
                                       ->x0_itemStateDesc[temp_r0])));

        temp_r23 = (new_var3 = item_data->xD0_itemStateDesc);

        if (temp_r23 != NULL && (flags & ITEM_ANIM_UPDATE)) {
            func_80268D34(item_gobj, temp_r23);

            if ((flags & ITEM_UNK_UPDATE)) {
                item_jobj1_2 = item_gobj->hsd_obj;
                item_data3 = GetItemData(item_gobj);
                item_data3->scl = item_data3->xCC_item_attr->x60_scale;
                HSD_JObjSetScaleItem(item_data3, item_jobj1_2, &sp4C);
                item_attr = item_data3->xCC_item_attr;
                item_data3->xBCC_unk = item_attr->x30_unk;
                item_data3->xBD4_grabRange = item_attr->x38_grab_range;
                item_data3->xBEC = item_data3->xCC_item_attr->x20;
                item_data3->xBDC = item_data3->xCC_item_attr->x20;
            } else {
                HSD_JObjSetScaleItem(item_gobj->user_data, item_gobj->hsd_obj,
                                     &scl);
            }

            item_data->x52C_item_script = temp_r29->xC_script;
            item_data->x530 = 0;
            item_data->x524 = 0.0F;
        } else if (temp_r23 != NULL && (flags & ITEM_CMD_UPDATE)) {
            item_data->x52C_item_script = temp_r29->xC_script;
            item_data->x530 = 0U;
            item_data->x524 = 0.0f;
        }

        HSD_JObjAnimAll(item_jobj);
        func_80279BE0(item_gobj);
        func_802799E4(item_gobj);
    } else {
        HSD_JObjRemoveAnimAll(item_jobj);
        item_data->x52C_item_script = NULL;
    }

    item_data->animated = temp_r30->animated;
    item_data->physics_updated = temp_r30->physics_updated;
    item_data->collided = temp_r30->collided;
    item_data->on_accessory = NULL;
    item_data->touched = NULL;
    item_data->entered_hitlag = NULL;
    item_data->exited_hitlag = NULL;
    item_data->jumped_on = NULL;

    item_data->xDD0_flag.bits.b5 = false;
    item_data->xD09 = 0;

    func_802714C0(item_gobj);
}

void lbl_802693E4(HSD_GObj* item_gobj)
{
    Item* item_data = item_gobj->user_data;
    if (item_data->xDC8_word.flags.x5 != 0) {
        func_8026A0A0(item_gobj);
        item_data->xDC8_word.flags.x5 = 0;
    }
    if (item_data->xDC8_word.flags.x6 != 0) {
        func_8026A0FC(item_gobj);
        item_data->xDC8_word.flags.x6 = 0;
    }
    if (item_data->xCBC_hitlagFrames > 0.0f) {
        item_data->xCBC_hitlagFrames -= 1.0f;
        if (item_data->xCBC_hitlagFrames <= 0.0f) {
            item_data->xCBC_hitlagFrames = 0.0f;
            item_data->xDC8_word.flags.xB = 0;
            item_data->xDC8_word.flags.xA = 0;
            if ((item_data->xDC8_word.flags.x8 == 0) &&
                (item_data->xDC8_word.flags.x7 == 0))
            {
                func_8026A1E8(item_gobj);
            }
        }
    }
}

/// Advance item animation + script?
void func_802694CC(HSD_GObj* item_gobj)
{
    HSD_JObj* item_jobj = (HSD_JObj*) HSD_GObjGetHSDObj(item_gobj);
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    HSD_JObjAnimAll(item_jobj);
    item_data->x5CC_currentAnimFrame = func_8000BDB4(item_jobj);
    func_802799E4(item_gobj);
}

/// @private
void lbl_80269528(HSD_GObj* item_gobj)
{
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    if (item_data->xDC8_word.flags.x9 == 0) {
        func_802694CC(item_gobj);
        if (item_data->animated != NULL && item_data->animated(item_gobj)) {
            item_data->destroy_type = 0;
            func_8026A8EC(item_gobj);
            return;
        }
    }
    if (item_data->xDD0_flag.bits.b6 != 0) {
        item_data->xD40 -= 1.0f;
        if (item_data->xD40 <= 0.0f) {
            item_data->xDD0_flag.bits.b6 = 0;
            item_data->xD40 = 0.0f;
            func_80279BBC(item_data);
            if (item_data->xDD0_flag.bits.b7 == 0) {
                func_802756E0(item_gobj);
            }
        }
    }
    if (item_data->xDC8_word.flags.x15 != 0 &&
        item_data->kind < It_Kind_L_Gun_Ray && !item_data->xDD0_flag.bits.b3)
    {
        item_data->xD44_lifeTimer -= 1.0f;
        if (item_data->xD44_lifeTimer <= 0.0f) {
            item_data->destroy_type = 0;
            func_8026A8EC(item_gobj);
            return;
        }
        if (item_data->xD44_lifeTimer <= lbl_804D6D28->x34) {
            func_802728C8(item_gobj);
        }
    }
    func_802721B8(item_gobj);
    func_80272298(item_gobj);
    func_80279BE0(item_gobj);
}

/// @private
bool func_802696CC(HSD_GObj* item_gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    if ((item_data->xDCC_flag.b4567 & 8) &&
        item_data->pos.x > Stage_GetBlastZoneRightOffset())
    {
        item_data->destroy_type = 3;
        func_8026A8EC(item_gobj);
        return true;
    }
    if ((item_data->xDCC_flag.b4567 & 4) &&
        item_data->pos.x < Stage_GetBlastZoneLeftOffset())
    {
        item_data->destroy_type = 3;
        func_8026A8EC(item_gobj);
        return true;
    }
    if ((item_data->xDCC_flag.b4567 & 1) && item_data->pos.y > 10000.0f) {
        item_data->destroy_type = 3;
        func_8026A8EC(item_gobj);
        return true;
    }
    if ((item_data->xDCC_flag.b4567 & 2) &&
        item_data->pos.y < Stage_GetBlastZoneBottomOffset())
    {
        item_data->destroy_type = 3;
        func_8026A8EC(item_gobj);
        return true;
    }
    return false;
}

void func_802697D4(HSD_GObj* item_gobj)
{
    Vec3 sp1C;
#ifdef MUST_MATCH
    u8 _[12];
#endif

    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    if (item_data->xDC8_word.flags.x9 == 0 &&
        item_data->physics_updated != NULL)
    {
        item_data->physics_updated(item_gobj);
    }
    if (item_data->xDC8_word.flags.x13 == 0) {
        if (item_data->xDC8_word.flags.x9 == 0) {
            PSVECAdd(&item_data->x40_vel, &item_data->x70_nudge, &sp1C);
            if ((item_data->ground_or_air == 0) &&
                (item_data->xDCD_flag.bits.b3 == 0))
            {
                func_8027737C(item_gobj, &sp1C);
            }
            PSVECAdd(&item_data->pos, &sp1C, &item_data->pos);
        }
        if (item_data->xDCC_flag.b3 == 1 &&
            (item_data->xDCC_flag.b4567 & 0xF) && func_802696CC(item_gobj))
        {
            return;
        }
        if (item_data->xD3C_spinSpeed && item_data->ground_or_air == 1) {
            func_80274A64(item_gobj);
        }
    }
    if ((item_data->xDD1_flag.bits.b1 != 0) && (item_data->ground_or_air == 1))
    {
        grLib_801C9E60(&item_data->x58_vec_unk);
    }
    PSVECAdd(&item_data->pos, &item_data->x58_vec_unk, &item_data->pos);
    func_80273484(item_gobj);
    if (item_data->ground_or_air == 0) {
        if ((item_data->xDCE_flag.bits.b3 != 0) &&
            (func_8026D604(item_gobj) != 0))
        {
            func_800567C0(item_data->xC30, &item_data->pos,
                          &item_data->x64_vec_unk2);
        } else {
            func_800567C0(item_data->x378_itemColl.x14C_ground.index,
                          &item_data->pos, &item_data->x64_vec_unk2);
        }
    }
    PSVECAdd(&item_data->pos, &item_data->x64_vec_unk2, &item_data->pos);
    func_8027346C(item_gobj);
    func_802714C0(item_gobj);
}

void func_80269978(HSD_GObj* item_gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    if (item_data->collided != NULL && item_data->collided(item_gobj)) {
        item_data->destroy_type = 1;
        func_8026A8EC(item_gobj);
    } else {
        HSD_JObjSetTranslate((HSD_JObj*) HSD_GObjGetHSDObj(item_gobj),
                             &item_data->pos);
        func_8027574C(item_gobj);
        func_8026C368(item_gobj);
    }
}

/// @private
void lbl_80269A9C(HSD_GObj* item_gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    func_80067624(item_gobj, &item_data->xBC0);
    if (item_data->xDC8_word.flags.x9 == 0) {
        if (item_data->on_accessory != NULL) {
            item_data->on_accessory(item_gobj);
        }
    }
    item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    if (item_data->xDCD_flag.bits.b01 != 0) {
        CameraBox* cameraBox = item_data->x520_cameraBox;
        if (cameraBox != NULL) {
            cameraBox->x10 = item_data->pos;
            cameraBox->x1C = item_data->pos;
        }
    }
    func_80271A58(item_gobj);
    func_80272280(item_gobj);
    func_802722B0(item_gobj);
}

/// @private
void lbl_80269B60(HSD_GObj* item_gobj)
{
    Item* item_data = item_gobj->user_data;
    if (item_data->xCFC != 0 && item_data->jumped_on != NULL &&
        item_data->jumped_on(item_gobj))
    {
        item_data->destroy_type = 2;
        func_8026A8EC(item_gobj);
        return;
    }
    func_8027137C(item_gobj);
    func_8027146C(item_gobj);
}

/// @private
/// @remarks Somewhat arbitrary. Does not run on Hook Shot / Grapple Beam,
///          rather items such as the Barrel Cannon.
void lbl_80269BE4(HSD_GObj* this)
{
    Item* item_data = this->user_data;
    if (item_data->xDD0_flag.bits.b5) {
        func_802701BC(this);

        if (item_data->grab_victim != NULL) {
            item_data->grab_dealt(this);
            item_data->grabbed_for_victim(item_data->grab_victim, this);
        }
    }
}

/// @private
void lbl_80269C5C(HSD_GObj* item_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    func_8026F9A0();
    func_802703E8(item_gobj);
    func_802706D0(item_gobj);
    func_80270E30(item_gobj);
}

/// Add to damage taken
void func_80269CA0(Item* item_data, s32 damage)
{
    item_data->xC9C += damage;

    if (item_data->xC9C > 999)
        item_data->xC9C = 999;
}

/// @private
void func_80269CC4(HSD_GObj* item_gobj)
{
    Item* temp_item = item_gobj->user_data;

    temp_item->xCA0 = 0;
    temp_item->xCA4 = 0;
    temp_item->xC94 = 0;
    temp_item->xCC8_knockback = 0.0f;
    temp_item->xC34_damageDealt = 0;
    temp_item->xC48 = 0;
    temp_item->xC4C = 0;
    temp_item->xC50 = 0;
    temp_item->xCCC_incDamageDirection = 0.0f;
    temp_item->xCB8_outDamageDirection = 0.0f;
    temp_item->xC68 = 0.0f;
    temp_item->xCD0 = 0.0f;
    temp_item->xCC0 = 0.0f;
    temp_item->xDCF_flag.bits.b6 = false;
    temp_item->xCC4 = 0;
    temp_item->xCEC_fighterGObj = 0;
    temp_item->xCF0_itemGObj = 0;
    temp_item->xCF4_fighterGObjUnk = 0;
    temp_item->toucher = 0;
    temp_item->xC64_reflectGObj = 0;
    temp_item->xC90_absorbGObj = 0;
    temp_item->xCFC = 0;
    temp_item->xCB4 = -1;
    temp_item->xC38 = -1;
    temp_item->xCE8 = 0.0f;
    temp_item->xCE4 = 0.0f;
    temp_item->xCE0 = 0.0f;
    temp_item->xCDC = 0.0f;
    temp_item->xCD8 = 0.0f;
    temp_item->xCD4 = 0.0f;
    temp_item->xDCE_flag.bits.b5 = false;
    temp_item->xDCE_flag.bits.b4 = false;
    temp_item->xDCC_flag.b1 = false;
    temp_item->xC70 = 1.0f;
    temp_item->xC6C = 1.0f;
    temp_item->xDCC_flag.b2 = false;
    temp_item->xDC8_word.flags.xB = false;
    temp_item->xCA8 = 0;
    temp_item->xDC8_word.flags.x3 = false;
    temp_item->xDC8_word.flags.x4 = false;
    temp_item->xDCE_flag.bits.b6 = false;
}

/// @private
bool func_80269DC8(HSD_GObj* item_gobj)
{
    HSD_GObjPredicate shield_bounced;
    HSD_GObjPredicate hit_shield;
    Item* item_data = item_gobj->user_data;

    if (item_data->xDCE_flag.bits.b5 && item_data->ground_or_air == 1 &&
        (item_data->xDCE_flag.bits.b4 ||
         item_data->xC54 <
             (f32) M_PI / 180 * (90 + lbl_804D6D28->unk_degrees)))
    {
        if (item_data->xDCE_flag.bits.b4 == 0) {
            item_data->xC54 -= M_PI / 2;
            if (item_data->xC54 < 0.0f) {
                item_data->xC54 = 0.0f;
            }
        }

        shield_bounced = item_data->xB8_itemLogicTable->shield_bounced;

        if (shield_bounced != NULL && shield_bounced(item_gobj)) {
            item_data->destroy_type = 2;
            func_8026A8EC(item_gobj);
            return true;
        }
    } else {
        hit_shield = item_data->xB8_itemLogicTable->hit_shield;

        if (func_80274C78(item_gobj))
            item_data->xCA8 = item_data->xC50;

        if (hit_shield != NULL && hit_shield(item_gobj)) {
            item_data->destroy_type = 2;
            func_8026A8EC(item_gobj);
            return true;
        }
    }

    return false;
}

/// @private
bool func_80269F14(HSD_GObj* item_gobj)
{
    f32 temp_f30;
    bool (*cb_OnReflect)(HSD_GObj*);
    s32 i;
    uint var_r27;
    Item* temp_item = (Item*) HSD_GObjGetUserData(item_gobj);

    if (temp_item->xDCC_flag.b1 == 0) {
        if (temp_item->kind == 34) {
            if (temp_item->xDCC_flag.b2 == 0) {
                temp_item->owner = temp_item->xC64_reflectGObj;
                temp_item->x20_team_id = ftLib_80086EB4(temp_item->owner);
            }
        } else {
            temp_item->owner = temp_item->xC64_reflectGObj;
            temp_item->x20_team_id = ftLib_80086EB4(temp_item->owner);
        }
    }

    db_80225DD8(item_gobj, temp_item->owner);
    temp_item->xD90 = temp_item->xC74;
    temp_item->xD94 = temp_item->xC78;
    temp_item->xD9C = temp_item->xC80;
    temp_item->xDA4_word = temp_item->xC88;
    temp_item->xDA8_short = temp_item->xC8C;
    cb_OnReflect = temp_item->xB8_itemLogicTable->reflected;
    if (cb_OnReflect != NULL && cb_OnReflect(item_gobj)) {
        temp_item->destroy_type = 2;
        func_8026A8EC(item_gobj);
        return true;
    }
    if (temp_item->xDCC_flag.b0 == 0) {
        for (i = 0; i < 4; i++) // 4 here is the maximum amount of hitboxes
                                // available in the vanilla Item struct
        {
            if (temp_item->x5D4_hitboxes[i].x0_toggle) {
                temp_f30 = temp_item->x5D4_hitboxes[i].xC_damage_staled *
                               temp_item->xC6C +
                           0.99f;
                var_r27 = temp_f30;
                if (var_r27 > lbl_804D6D28->xD8) {
                    var_r27 = lbl_804D6D28->xD8;
                }
                func_80272460(&temp_item->x5D4_hitboxes[i], var_r27,
                              item_gobj);
            }
        }
    }
    return false;
}

/// @private
void func_8026A0A0(HSD_GObj* item_gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    if (item_data->xDC8_word.flags.x7 != 0) {
        if ((item_data->xDC8_word.flags.xA == 0) &&
            (item_data->xDC8_word.flags.x8 == 0))
        {
            func_8026A1E8(item_gobj);
        }
        item_data->xDC8_word.flags.x7 = 0;
    }
}

/// @private
void func_8026A0FC(HSD_GObj* item_gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    if (item_data->xDC8_word.flags.x8 != 0) {
        if ((item_data->xDC8_word.flags.xA == 0) &&
            (item_data->xDC8_word.flags.x7 == 0))
        {
            func_8026A1E8(item_gobj);
        }
        item_data->xDC8_word.flags.x8 = 0;
    }
}

/// @private
void func_8026A158_helper(HSD_GObj* atkCollGObj)
{
    Item* temp_item = (Item*) HSD_GObjGetUserData(atkCollGObj);
    temp_item->xDC8_word.flags.x8 = 1;
    func_8026A158(atkCollGObj);
}

/// @private
void func_8026A158(HSD_GObj* item_gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    if (item_data->entered_hitlag != NULL) {
        item_data->entered_hitlag(item_gobj);
    }
    item_data->xDC8_word.flags.x9 = 1;
    if (item_data->atk_victim != NULL &&
        func_80272D1C(item_data->atk_victim) &&
        item_data->xDC8_word.flags.x8 == 0)
    {
        func_8026A158_helper(item_data->atk_victim);
    }
}

/// @private
void func_8026A1E8_inline(HSD_GObj* atkCollGObj)
{
    Item* temp_item = (Item*) HSD_GObjGetUserData(atkCollGObj);
    if (temp_item->xDC8_word.flags.x8 != 0) {
        if ((temp_item->xDC8_word.flags.xA == 0) &&
            (temp_item->xDC8_word.flags.x7 == 0))
        {
            func_8026A1E8(atkCollGObj);
        }
        temp_item->xDC8_word.flags.x8 = 0;
    }
}

/// @private
void func_8026A1E8(HSD_GObj* item_gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    if (item_data->exited_hitlag != NULL) {
        item_data->exited_hitlag(item_gobj);
    }
    item_data->xDC8_word.flags.x9 = 0;
    if (item_data->atk_victim != NULL &&
        func_80272D1C(item_data->atk_victim) &&
        item_data->xDC8_word.flags.x8 == 0)
    {
        func_8026A1E8_inline(item_data->atk_victim);
    }
}

/// @private
bool processCallback(HSD_GObjPredicate cb, HSD_GObj* item_gobj,
                     Item* item_data)
{
    if (cb && cb(item_gobj)) {
        item_data->destroy_type = 2;
        func_8026A8EC(item_gobj);
        return true;
    }
    return false;
}

/// @private
bool OnTakeDamageThink(HSD_GObj* item_gobj, Item* item_data)
{
    item_data->xC9C += item_data->xCA0;
    if (item_data->xC9C > 999) {
        item_data->xC9C = 999;
    }
    item_data->xCA8 = item_data->xCA0;
    item_data->xDC8_word.flags.xB = 1;
    return processCallback(item_data->xB8_itemLogicTable->dmg_received,
                           item_gobj, item_data);
}

/// @private
bool OnClankThink(HSD_GObj* item_gobj, Item* item_data)
{
    bool (*cb_OnClank)(HSD_GObj*) = item_data->xB8_itemLogicTable->clanked;
    if (func_80274C78(item_gobj)) {
        item_data->xCA8 = item_data->xC48;
    }
    return processCallback(cb_OnClank, item_gobj, item_data);
}

/// @private
bool OnGiveDamageThink(HSD_GObj* item_gobj, Item* item_data)
{
    bool (*cb_OnGiveDamage)(HSD_GObj*) =
        item_data->xB8_itemLogicTable->dmg_dealt;
    if (func_80274C78(item_gobj)) {
        item_data->xCA8 = item_data->xC34_damageDealt;
    }
    return processCallback(cb_OnGiveDamage, item_gobj, item_data);
}

/// @private
void EnterHitlagThink(HSD_GObj* item_gobj, Item* item_data)
{
    if (!item_data->xDC8_word.flags.x9) {
        item_data = GetItemData(item_gobj);
        if (item_data->entered_hitlag)
            item_data->entered_hitlag(item_gobj);
        item_data->xDC8_word.flags.x9 = 1;

        if ((item_data->atk_victim) && func_80272D1C(item_data->atk_victim) &&
            !item_data->xDC8_word.flags.x8)
        {
            func_8026A158_helper(item_data->atk_victim);
        }
    }
}

/// @private
void checkHitLag(f32 min_value, Item* item_data)
{
    if (item_data->xCBC_hitlagFrames < min_value) {
        item_data->xCBC_hitlagFrames = min_value;
    }
    item_data->xDC8_word.flags.xA = 1;
}

/// @private
void lbl_8026A294(HSD_GObj* item_gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);

    if ((item_data->xCC8_knockback) || (item_data->xCA0)) {
        if (OnTakeDamageThink(item_gobj, item_data))
            return;
    } else if (item_data->xC50) {
        if (func_80269DC8(item_gobj))
            return;
    } else if (item_data->xC48) {
        if (OnClankThink(item_gobj, item_data))
            return;
    } else if ((item_data->xC34_damageDealt) || (item_data->xC4C)) {
        if (OnGiveDamageThink(item_gobj, item_data))
            return;
    } else if (item_data->xC64_reflectGObj != NULL) {
        if (func_80269F14(item_gobj))
            return;
    } else if (item_data->xC90_absorbGObj != NULL) {
        if (processCallback(item_data->xB8_itemLogicTable->absorbed, item_gobj,
                            item_data))
        {
            return;
        }
    } else if (item_data->xDCE_flag.bits.b6) {
        if (processCallback(item_data->touched, item_gobj, item_data)) {
            return;
        }
    }

    if ((item_data->xDC8_word.flags.xD) && (item_data->xCC0 > 0.0f)) {
        checkHitLag(item_data->xCC0, item_data);

        EnterHitlagThink(item_gobj, item_data);
    } else if (item_data->xCA8) {
        checkHitLag(func_8026B424(item_data->xCA8), item_data);

        EnterHitlagThink(item_gobj, item_data);
    }
    if ((item_data->xDC8_word.flags.x4) || (item_data->xDC8_word.flags.x3)) {
        EnterHitlagThink(item_gobj, item_data);

        if (item_data->xDC8_word.flags.x4) {
            item_data->xDC8_word.flags.x8 = 1;
            item_data->xDC8_word.flags.x4 = 0;
        } else {
            item_data->xDC8_word.flags.x7 = 1;
            item_data->xDC8_word.flags.x3 = 0;
        }
    }
    func_80269CC4(item_gobj);
}

/// @private
void lbl_8026A788(HSD_GObj* item_gobj)
{
    Item* item_data = item_gobj->user_data;
    int dynamicBonesNum = item_data->x374_dynamicBonesNum;
    Item_DynamicBones* dynamicBones = item_data->xD4_dynamicBones;
    int i;

    func_80272304(item_gobj);
    for (i = 0; i < dynamicBonesNum; i++, dynamicBones++) {
        func_8001044C(&dynamicBones->unk_ptr, &item_data->xB6C,
                      item_data->xB68, 0.0f, 0, dynamicBones->flags, 0, 1);
    }
}

/// @private
void func_8026A810(HSD_GObj* item_gobj)
{
    Item* temp_item = (Item*) HSD_GObjGetUserData(item_gobj);

    if (temp_item->xB8_itemLogicTable->spawned != NULL)
        temp_item->xB8_itemLogicTable->spawned(item_gobj);
}

void func_8026A848(HSD_GObj* item_gobj, HSD_GObj* gobj)
{
    Item* temp_item = (Item*) HSD_GObjGetUserData(item_gobj);

    if (temp_item->hold_kind == 8 && temp_item->kind != 58 &&
        temp_item->kind != 59 && temp_item->kind != 99 &&
        temp_item->kind != 103)
    {
        if (ftLib_800867CC(gobj) == item_gobj)
            ftLib_80086764(gobj);
    } else if (ftLib_800867A0(gobj, item_gobj)) {
        ftLib_80086724(gobj, item_gobj);
    }
}

/// @private
void DestroyItemInline(HSD_GObj* this, Item* other_ip)
{
    Item* ip = this->user_data;
    HSD_GObj* other = other_ip->owner;

    if (ip->hold_kind == 8 && ip->kind != 58 && ip->kind != 59 &&
        ip->kind != 99 && ip->kind != 103)
    {
        if (ftLib_800867CC(other) == this)
            ftLib_80086764(other);
    } else if (ftLib_800867A0(other, this)) {
        ftLib_80086724(other, this);
    }
}

/// @private
void ItemSwitch(HSD_GObj* item_gobj)
{
    Item* ip = item_gobj->user_data;
    enum_t destroy_type = ip->destroy_type;

    switch (destroy_type) {
    case 0:
        func_8027327C(item_gobj, ip->xCC_item_attr->destroy_gfx,
                      ip->destroy_sfx);
        break;

    case 2:
    case 1:
        func_8027327C(item_gobj, ip->xCC_item_attr->x68, ip->xD80);
        break;

    case 3:
    case 4:
        break;
    }
}

/// @private
/// @todo Could this be a higher-level inline in gobjproc.h or something?
void RunCallback(HSD_GObj* this, HSD_GObjEvent arg1)
{
    if (arg1 != NULL)
        arg1(this);
}

/// @private
/// @todo Decide on it vs ip vs data, gobj vs item_gobj vs this, etc.
void func_8026A8EC_inline1(HSD_GObj* this)
{
    Item* ip = (Item*) HSD_GObjGetUserData(this);

    if (ip->xDC8_word.flags.xE) {
        ftLib_80087050(ip->x378_itemColl.x19C);
        ip->xDC8_word.flags.xE = false;
        ip->x378_itemColl.x19C = -1;
    }
}

/// @private
void func_8026A8EC_inline2(HSD_GObj* item_gobj)
{
    Item* it = (Item*) HSD_GObjGetUserData(item_gobj);
    RunCallback(item_gobj, it->xB8_itemLogicTable->destroyed);
}

/// @private
void func_8026A8EC_inline3(HSD_GObj* item_gobj)
{
    Item* it = (Item*) HSD_GObjGetUserData(item_gobj);

    if (it->xDCD_flag.bits.b01 != 0 && it->x520_cameraBox != NULL) {
        func_800290D4(it->x520_cameraBox);
        it->x520_cameraBox = NULL;
        it->xDCD_flag.bits.b01 = 0;
    }
}

void func_8026A8EC(HSD_GObj* this)
{
    Item* ip = (Item*) HSD_GObjGetUserData(this);

    if (!func_80272D1C(this) || ip == NULL) {
        OSReport("===== Not Found Item_Struct!! =====\n");
        __assert("item.c", 2405, "0");
    }

    func_802725D4(this);
    func_802675A8(this);
    func_8026A8EC_inline1(this);
    efLib_DestroyAll(this);

    if (!ip->xDCF_flag.bits.b2 &&
        (!ip->xDC8_word.flags.x13 || ip->owner == NULL))
    {
        ItemSwitch(this);
    }

    func_8026A8EC_inline2(this);

    if (ip->xDC8_word.flags.x13 && ip->owner != NULL &&
        ftLib_80086960(ip->owner))
    {
        DestroyItemInline(this, ip);
    }

    ip->owner = NULL;
    func_8026A8EC_inline3(this);

    {
        int i;
        for (i = 0; i < ip->x374_dynamicBonesNum; i++)
            func_8000FD18(&ip->xD4_dynamicBones[i].unk_ptr);
    }

    func_8026B0B4(this);
    func_80067688(&ip->xBC0);
    func_80390228(this);
}

void func_8026AB54(HSD_GObj* item_gobj, HSD_GObj* pickup_gfx, u8 pickup_sfx)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);

    func_80273168(item_gobj);
    func_802742F4(item_gobj, pickup_gfx, pickup_sfx);
    RunCallback(item_gobj, item_data->xB8_itemLogicTable->picked_up);
    func_8026B074(item_data);
}

void func_8026ABD8(HSD_GObj* this, Vec3* pos, f32 arg2)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Item* item_data = (Item*) HSD_GObjGetUserData(this);

    item_data->xC44 = arg2;
    func_802731A4(this);
    func_80273B50(this, pos);
    RunCallback(this, item_data->xB8_itemLogicTable->dropped);
    func_80274198(this, 1);
    func_802754D4(this);

    if (func_8026B6C8(this))
        func_80275390(this);
}

void func_8026AC74(HSD_GObj* this, enum_t drop_gfx, enum_t drop_sfx, f32 arg3)
{
    Item* item_data = GetItemData(this);
    item_data->xC44 = arg3;
    func_802731A4(this);
    func_80273748(this, drop_gfx, drop_sfx);
    RunCallback(this, item_data->xB8_itemLogicTable->dropped);
    func_802741F4(this, 1);
    func_802754D4(this);

    if (func_8026B6C8(this))
        func_80275390(this);
}

void func_8026AD20(HSD_GObj* this, s32 drop_gfx, s32 drop_sfx, f32 arg8)
{
    Item* item_data = GetItemData(this);
    func_802731E0(this);
    item_data->xC44 = arg8;
    func_80273748(this, drop_gfx, drop_sfx);
    RunCallback(this, item_data->xB8_itemLogicTable->thrown);
    func_802741F4(this, 1);
    func_802754D4(this);
}

void func_8026ADC0(HSD_GObj* this)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(this);
    if (item_data->xB8_itemLogicTable->entered_air != NULL) {
        item_data->xB8_itemLogicTable->entered_air(this);
        item_data->xDC8_word.flags.x1F = true;
    }
}

void Item_OnUserDataRemove(any_t user_data)
{
    Item* item_data = (Item*) user_data;

    if (item_data->xBBC_dynamicBoneTable != NULL)
        HSD_ObjFree(&unkAllocData1, item_data->xBBC_dynamicBoneTable);

    HSD_ObjFree(&itemAllocData, item_data);
}

uint func_8026AE60(void)
{
    uint result = lbl_804D6D14++;

    if (lbl_804D6D14 == 0)
        lbl_804D6D14++;

    return result;
}

void func_8026AE84(Item* item_data, enum_t sfx, int pan, int volume)
{
    if (sfx != 540000) {
        if (sfx != 540001)
            item_data->xD6C = func_800237A8(func_800233EC(sfx), pan, volume);
        else
            item_data->xD6C = func_800237A8(540000, pan, volume);
    }
}

void func_8026AF0C(Item* item_data, enum_t sfx, int pan, int volume)
{
    if (sfx != 540000) {
        if (sfx != 540001) {
            if (item_data->sfx_unk1 != SFX_NONE) {
                func_800236B8(item_data->sfx_unk1);
            }
            item_data->sfx_unk1 =
                func_800237A8(func_800233EC(sfx), pan, volume);
        } else {
            func_8026B034(item_data);
        }
    }
}

void func_8026AFA0(Item* item_data, enum_t sfx, int pan, int volume)
{
    if (sfx != 540000) {
        if (sfx != 540001) {
            if (item_data->sfx_unk2 != SFX_NONE) {
                func_800236B8(item_data->sfx_unk2);
            }
            item_data->sfx_unk2 =
                func_800237A8(func_800233EC(sfx), pan, volume);
        } else {
            func_8026B074(item_data);
        }
    }
}

void func_8026B034(Item* item_data)
{
    if (item_data->sfx_unk1 != SFX_NONE)
        func_800236B8(item_data->sfx_unk1);

    item_data->sfx_unk1 = SFX_NONE;
}

void func_8026B074(Item* item_data)
{
    if (item_data->sfx_unk2 != SFX_NONE)
        func_800236B8(item_data->sfx_unk2);

    item_data->sfx_unk2 = SFX_NONE;
}

/// @private
void func_8026B0B4(HSD_GObj* item_gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    func_80026510(item_gobj);

    if (item_data->xD6C != SFX_NONE) {
        func_800265C4(item_gobj, item_data->xD6C);
        item_data->xD6C = SFX_NONE;
    }

    if (item_data->sfx_unk1 != SFX_NONE &&
        func_800265C4(item_gobj, item_data->sfx_unk1) == 1)
    {
        if (item_data->sfx_unk1 != SFX_NONE) {
            func_800236B8(item_data->sfx_unk1);
        }
        item_data->sfx_unk1 = SFX_NONE;
    }

    if (item_data->sfx_unk2 != SFX_NONE &&
        func_800265C4(item_gobj, item_data->sfx_unk2) == 1)
    {
        if (item_data->sfx_unk2 != SFX_NONE) {
            func_800236B8(item_data->sfx_unk2);
        }
        item_data->sfx_unk2 = SFX_NONE;
    }

    if (item_data->sfx_unk1 != SFX_NONE)
        func_800236B8(item_data->sfx_unk1);

    item_data->sfx_unk1 = SFX_NONE;

    if (item_data->sfx_unk2 != SFX_NONE)
        func_800236B8(item_data->sfx_unk2);

    item_data->sfx_unk2 = SFX_NONE;
    item_data->xD6C = SFX_NONE;
}

/// Check if item is grabbable
bool Item_IsGrabbable(HSD_GObj* item_gobj)
{
    Item* temp_item;

    temp_item = item_gobj->user_data;

    if ((temp_item->xDC8_word.flags.x15 != 0) &&
        (temp_item->xB8_itemLogicTable->picked_up != NULL))
    {
        return true;
    }

    return false;
}
