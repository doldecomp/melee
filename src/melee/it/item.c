#include <melee/it/item.h>

#include <common_structs.h>
#include <dolphin/mtx/mtxtypes.h>
#include <dolphin/os/os.h>
#include <melee/ef/efasync.h>
#include <melee/gr/grlib.h>
#include <melee/lb/lbunknown_001.h>
#include <melee/lb/lbunknown_003.h>

extern s32 func_8016AE80(void);

// Check if items are enabled
BOOL func_80266F3C(void)
{
    if (func_8016AE80() != -1) {
        return TRUE;
    }
    return FALSE;
}

// Check to load ItCo.dat/usd
void func_80266F70(void)
{
    func_8027870C(func_80266F3C());
}

// ItCo prefunction with 0
void func_80266FA8(void)
{
    func_8027870C(FALSE);
}

HSD_ObjAllocData lbl_804A0BE0;
HSD_ObjAllocData lbl_804A0C0C;
HSD_ObjAllocData lbl_804A0C38;
HSD_ObjAllocUnk lbl_804A0C64;
HSD_ObjAllocUnk2 lbl_804A0CCC;
S32Vec3 lbl_804A0E24;

extern HSD_ObjAllocUnk4 lbl_804A0E30;
extern HSD_ObjAllocUnk5 lbl_804A0E50;
extern HSD_ObjAllocUnk6 lbl_804A0E60;
extern ItemCommonData* lbl_804D6D28;

// Init item struct?
void func_80266FCC(void)
{
    HSD_ObjAllocInit(&lbl_804A0BE0, sizeof(Item), 4);
    HSD_ObjAllocInit(&lbl_804A0C0C, sizeof(DynamicBoneTable), 4);
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
    lbl_804A0CCC.x154.bits.b0 = 1;
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

extern s32 func_8017E068();
extern void func_80225D64(HSD_GObj*, HSD_GObj*);
extern void func_80225DD8(HSD_GObj*, HSD_GObj*);
extern void func_8026B390(HSD_GObj*);
extern void func_80271508(HSD_GObj*, s32);
extern void func_80272280(HSD_GObj*);
extern void func_802725D4(HSD_GObj*);
extern void func_80273500(HSD_GObj*, Vec3*);
extern void func_80274658(HSD_GObj*, f32);
extern void func_80274DAC(HSD_GObj*);
extern void func_802753BC(HSD_GObj*, s16);
extern void func_802753DC(HSD_GObj*);
extern void func_80275E98(HSD_GObj*, SpawnItem*);
extern void func_802762B0(Item*);
extern void func_802762BC(Item*);
extern void func_80279B64(Item*);
extern void func_8027B0C4(HSD_GObj*, SpawnItem*);

static inline void HSD_JObjSetFacingDirItem(HSD_JObj* jobj, Item* it)
{
    if (it->xDC8_word.flags.x19 == 1) {
        HSD_JObjSetRotationY(jobj, M_PI / 2 * it->x2C_facing_direction);
    }
}

// TODO move to gobj.h
static inline void* HSD_GObjGetHSDObj(HSD_GObj* item_gobj)
{
    return item_gobj->hsd_obj;
}

static inline void ItUnkHoldKind(HSD_GObj* item_gobj)
{
    Item* it = (Item*) HSD_GObjGetUserData(item_gobj);
    s32 temp_r3;
    switch (it->x14_hold_kind) {
    case 4:
    case 5:
    case 6:
    case 7:
        temp_r3 = func_8017E068();
        if (temp_r3 >= 0) {
            it->itdmg.xC3C = lbl_804D6D28->x80_float[temp_r3];
        }
    }
}

// Initialize item coordinates?
void func_80267130(HSD_GObj* item_gobj, SpawnItem* spawnItem)
{
    Item* item_data;
    HSD_JObj* model;
    s32 temp_r4;

    item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    model = (HSD_JObj*) HSD_GObjGetHSDObj(item_gobj);
    item_data->x4C_pos = spawnItem->x20_pos_prev;
    item_data->x30_initial_facing_dir = item_data->x2C_facing_direction =
        spawnItem->x38_facing_direction;
    item_data->x518_ownerGObj = spawnItem->x0_parent_gobj;
    if (item_data->x2C_facing_direction == -1.0f) {
        temp_r4 = -1;
    } else {
        temp_r4 = 1;
    }
    func_800436D8(&item_data->x378_itemColl, temp_r4);
    HSD_JObjSetFacingDirItem(model, item_data);
    func_80273500(item_gobj, &spawnItem->x2C_vel);
    item_data->x5CC_currentAnimFrame = 0.0f;
    item_data->x5D0_animFrameSpeed = 1.0f;
    func_802753BC(item_gobj, spawnItem->x3C_damage);
    func_802753DC(item_gobj);
    item_data->itdmg.xC64_reflectGObj = 0;
    item_data->xDCC_flag.b0 = 0;
    item_data->itdmg.xC90_absorbGObj = 0;
    item_data->xD0C = 0;
    func_8026B390(item_gobj);
    item_data->xDC8_word.flags.x13 = 0;
    if (spawnItem->x48_ground_or_air == GA_Air) {
        func_802762BC(item_data);
    } else {
        func_802762B0(item_data);
    }
    func_80275E98(item_gobj, spawnItem);
    func_80274DAC(item_gobj);
    HSD_JObjSetTranslate(model, &item_data->x4C_pos);
    func_80274658(item_gobj, lbl_804D6D28->x6C_float);
    func_802725D4(item_gobj);
    func_80271508(item_gobj, 0);
    func_80272280(item_gobj);
    item_data->itcb.xD20_callback_Accessory = 0;
    item_data->itcb.xD24_callback_Inert = 0;
    item_data->itcb.xD28_callback_EnterHitlag = 0;
    item_data->itcb.xD2C_callback_ExitHitlag = 0;
    item_data->itcb.xD30_callback_JumpedOn = 0;
    if (item_data->x518_ownerGObj != NULL) {
        func_80225DD8(item_gobj, item_data->x518_ownerGObj);
    } else {
        func_80225D64(item_gobj, item_data->x518_ownerGObj);
    }
    func_8027B0C4(item_gobj, spawnItem);
    func_80279B64(item_data);
    ItUnkHoldKind(item_gobj);
}

// Remove Camera Box
void func_80267454(HSD_GObj* item_gobj)
{
    Item* item_data = item_gobj->user_data;
    if (((item_data->xDCD_flag.bits.b01) != 0) &&
        (item_data->x520_cameraBox != NULL))
    {
        func_800290D4(item_data->x520_cameraBox);
        item_data->x520_cameraBox = NULL;
        item_data->xDCD_flag.bits.b01 = 0;
    }
}

// Set Item Hold kind
void func_802674AC(SpawnItem* spawnItem)
{
    s32 ItemID = spawnItem->x8_item_id;
    if (ItemID == 0x12) {
        spawnItem->xC_hold_kind = 2;
        return;
    }
    if (ItemID == 0xA0) {
        spawnItem->xC_hold_kind = 3;
        return;
    }
    if (ItemID < 0x23) {
        spawnItem->xC_hold_kind = 0;
        return;
    }
    if (ItemID < 0x2B) {
        spawnItem->xC_hold_kind = 1;
        return;
    }
    if (ItemID < 0x2F) {
        spawnItem->xC_hold_kind = 6;
        return;
    }
    if (ItemID < 0x30) {
        spawnItem->xC_hold_kind = 7;
        return;
    }
    if (ItemID < 0x9E) {
        spawnItem->xC_hold_kind = 8;
        return;
    }
    if (ItemID == 0x9E) {
        spawnItem->xC_hold_kind = 12;
        return;
    }
    if (ItemID < 0xA0) {
        spawnItem->xC_hold_kind = 11;
        return;
    }
    if (ItemID < 0xBF) {
        spawnItem->xC_hold_kind = 9;
        return;
    }
    if (ItemID < 0xD0) {
        spawnItem->xC_hold_kind = 10;
        return;
    }
    if (ItemID < 0xEA) {
        spawnItem->xC_hold_kind = 4;
        return;
    }
    spawnItem->xC_hold_kind = 5;
}

extern BOOL func_8018841C(void);

void func_802675A8(HSD_GObj* item_gobj)
{
    Item* item_data = item_gobj->user_data;
    switch (item_data->x14_hold_kind) {
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
    if (func_8018841C() && item_data->x18 == 1) {
        lbl_804A0C64.x60--;
    }
}

extern void func_80274EE8(u32);

void func_802676F4(HSD_GObj* item_gobj)
{
    Item* item_data = item_gobj->user_data;
    switch (item_data->x14_hold_kind) {
    case 0:
        lbl_804A0C64.x0++;
        if (item_data->x10_item_kind == 0x22) {
            lbl_804A0C64.x1C++;
        }
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
    if (func_8018841C() && item_data->x18 == 1) {
        lbl_804A0C64.x60++;
    }
}

BOOL func_8026784C(s32 dropItem, s32 unused) // Decide drop item
{
    BOOL result = FALSE;
    switch (dropItem) {
    case 0:
        if (lbl_804A0C64.x0 >= lbl_804A0C64.x4) {
            result = TRUE;
        }
        break;

    case 1:
        if (lbl_804A0C64.x8 >= lbl_804A0C64.xC) {
            result = TRUE;
        }
        break;

    case 2:
        if (lbl_804A0C64.x10 >= lbl_804A0C64.x14) {
            result = TRUE;
        }
        break;

    case 3:
        if (lbl_804A0C64.x58 >= lbl_804A0C64.x5C) {
            result = TRUE;
        }
        break;

    case 5:
        if (lbl_804A0C64.x40 >= lbl_804A0C64.x44) {
            result = TRUE;
        }
        break;

    case 7:
        if (lbl_804A0C64.x34 >= lbl_804A0C64.x38) {
            result = TRUE;
        }
        break;

    case 9:
        if (lbl_804A0C64.x1C > lbl_804A0C64.x20) {
            lbl_804A0C64.x1C--;
            result = TRUE;
        }
        break;

    case 10:
        if (lbl_804A0C64.x24 >= lbl_804A0C64.x28) {
            result = TRUE;
        }
        break;

    case 11:
        if (lbl_804A0C64.x48 >= lbl_804A0C64.x4C) {
            result = TRUE;
        }
        break;

    case 12:
        if (lbl_804A0C64.x50 >= lbl_804A0C64.x54) {
            result = TRUE;
        }
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

// Store Item Pointers
void func_80267978(HSD_GObj* item_gobj)
{
    Item* item_data = item_gobj->user_data;
    if (item_data->x10_item_kind < It_Kind_Kuriboh) {
        // Common items
        item_data->xC4_article_data =
            lbl_804D6D24->article_ptr[item_data->x10_item_kind];
        item_data->xB8_itemLogicTable = &lbl_803F14C4[item_data->x10_item_kind];
    } else if (item_data->x10_item_kind < Pokemon_Tosakinto) {
        // Character items
        int idx = item_data->x10_item_kind - It_Kind_Kuriboh;
        item_data->xC4_article_data = lbl_804D6D38->unkptr[idx];
        item_data->xB8_itemLogicTable = &lbl_803F3100[idx];
    } else if (item_data->x10_item_kind < It_Kind_Old_Kuri) {
        // Pokemon
        int idx = item_data->x10_item_kind - Pokemon_Tosakinto;
        item_data->xC4_article_data = lbl_804D6D30->unkptr[idx];
        item_data->xB8_itemLogicTable = &lbl_803F23CC[idx];
    } else {
        // Stage items
        int idx = item_data->x10_item_kind - It_Kind_Old_Kuri;
        item_data->xC4_article_data = lbl_804A0F60->unkptr[idx];
        item_data->xB8_itemLogicTable = &lbl_803F4D20[idx];
        if (item_data->xC4_article_data == NULL) {
            OSReport("not found zako model data! check ground dat file!\n");
            __assert("item.c", 0x2AE, "0");
        }
    }
    item_data->xBC_itemStateContainer =
        item_data->xB8_itemLogicTable->x0_itemStatePtr;
}

extern s32 func_80086960(HSD_GObj*);
extern u8 func_80086EB4(HSD_GObj*);
extern u32 func_80225B20();

// Initialize item variables
void func_80267AA8(HSD_GObj* item_gobj, SpawnItem* spawnItem)
{
    ItemAttr* item_attr;
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    item_data->x10_item_kind = spawnItem->x8_item_id;
    item_data->x14_hold_kind = spawnItem->xC_hold_kind;
    item_data->x18 = spawnItem->x10;
    item_data->x1C = lbl_804D6D10++;
    item_data->x4_GObj = item_gobj;
    func_80267978(item_gobj);
    item_data->x24_item_state_index = -1;
    item_data->xC8_joint = item_data->xC4_article_data->x10_modelDesc->x0_joint;
    item_data->xCC_item_attr = item_data->xC4_article_data->x0_common_attr;
    item_data->x518_ownerGObj = NULL;
    item_data->xDC8_word.flags.x0 = 0;
    item_data->x378_itemColl.x19C = -1;
    item_data->xDC4 = 0;
    item_data->xDC8_word.flags.xF = 0;
    item_data->itdmg.xCC4 = 0;
    item_data->xDCF_flag.bits.b6 = 0;
    item_data->xDCF_flag.bits.b7 = 0;
    item_data->itdmg.xCB0_source_ply = 6;
    item_data->itdmg.xCB4 = -1;
    item_data->itdmg.xC38 = -1;
    item_data->itdmg.xCE8 = 0.0f;
    item_data->itdmg.xCE4 = 0.0f;
    item_data->itdmg.xCE0 = 0.0f;
    item_data->itdmg.xCDC = 0.0f;
    item_data->itdmg.xCD8 = 0.0f;
    item_data->itdmg.xCD4 = 0.0f;
    item_data->xDD0_flag.bits.b1 = 0;
    item_data->xDC8_word.flags.x14 = 0;
    item_data->xDC8_word.flags.xE = 0;
    item_data->itdmg.xCEC_fighterGObj = NULL;
    item_data->itdmg.xCF0_itemGObj = NULL;
    item_data->xCF4_fighterGObjUnk = NULL;
    item_data->xCF8_detectGObj = NULL;
    item_data->itdmg.xC64_reflectGObj = NULL;
    item_data->xCFC = 0;
    item_data->xD04_atkCollItem = 0;
    item_data->xD00_grabGObj = 0;
    item_data->itdmg.xCCC_incDamageDirection = 0.0f;
    item_data->itdmg.xCB8_outDamageDirection = 0.0f;
    item_data->itdmg.xC68 = 0.0f;
    item_data->itdmg.xCD0 = 0.0f;
    func_80275158(item_gobj, lbl_804D6D28->x30);
    item_data->xDD0_flag.bits.b3 = FALSE;
    item_data->x34_spin_speed = item_data->xCC_item_attr->xC_spin_speed;
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
    item_data->xD60_destroyType = 4;
    item_data->xDCE_flag.bits.b5 = 0;
    item_data->xDCE_flag.bits.b4 = 0;
    item_data->itdmg.xC54 = 0.0f;
    item_data->itdmg.xC58 = 0.0f;
    item_data->itdmg.xC58 = 0.0f;
    item_data->itdmg.xC58 = 0.0f;
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
    item_data->itdmg.xCA8 = 0;
    item_data->itdmg.xCBC_hitlagFrames = 0.0f;
    item_data->itdmg.xCC0 = 0.0f;
    item_data->xDC8_word.flags.xA = 0;
    item_data->xDC8_word.flags.xB = 0;
    item_data->xDCC_flag.b1 = 0;
    item_data->itdmg.xC70 = 1.0f;
    item_data->itdmg.xC6C = 1.0f;
    item_data->xDCC_flag.b2 = 0;
    item_data->xDD0_flag.bits.b0 = 0;
    item_data->xDCE_flag.bits.b6 = 0;
    item_data->xDCF_flag.bits.b0 = 0;
    item_data->xDCF_flag.bits.b1 = 0;
    item_data->xDCF_flag.bits.b2 = 0;
    item_data->xDD1_flag.bits.b0 = 0;
    item_data->xDCE_flag.bits.b7 = 1;
    item_data->x38_scale = item_data->xCC_item_attr->x60_scale;
    item_data->x3C = 0.0f;
    item_data->xDCD_flag.bits.b3 = 0;
    item_data->xDCD_flag.bits.b4 = 0;
    item_data->xDD0_flag.bits.b7 = 0;
    item_data->xBC0 = 0;
    item_data->xDD1_flag.bits.b1 = 0;
    item_data->xDCD_flag.bits.b2 = 0;
    item_data->xD6C = -1;
    item_data->xD68 = -1;
    item_data->xD64 = -1;
    item_data->xD70 = item_data->xCC_item_attr->x6C;
    item_data->xD74 = item_data->xCC_item_attr->x70;
    item_data->xD78 = item_data->xCC_item_attr->x74;
    item_data->xD7C_destroySFX = item_data->xCC_item_attr->x78_destroySFX;
    item_data->xD80 = item_data->xCC_item_attr->x7C;
    item_attr = item_data->xCC_item_attr;
    item_data->xD84 = item_attr->x80;
    func_80275474(item_gobj);
    func_80275504(item_gobj);
    func_80274EF8(item_gobj);
    if (func_80086960(spawnItem->x0_parent_gobj) != 0) {
        item_data->xDC8_word.flags.x1 = 0;
    } else {
        item_data->xDC8_word.flags.x1 = 1;
    }
    item_data->x5C8 = 0;
    item_data->xBC7 = 0;
    item_data->xBC6 = 0;
    item_data->xBC5 = 0;
    item_data->xBC4 = 0;
    item_data->x5C9 = 0xFF;
    func_80279B64(item_data);
    item_data->xDCF_flag.bits.b3 = 0;
    item_data->xDCF_flag.bits.b4 = 0;
    item_data->xDCF_flag.bits.b5 = 0;
    item_data->xDAA_byte = 1;
    if (func_80225B20() != 0U) {
        item_data->xDAA_flag.bits.b4 = 1;
    }
    if (spawnItem->x0_parent_gobj == NULL) {
        item_data->x20_team_id = -1;
    } else if (func_80086960(spawnItem->x0_parent_gobj) != 0) {
        item_data->x20_team_id = func_80086EB4(spawnItem->x0_parent_gobj);
    } else if (func_80272D1C(spawnItem->x0_parent_gobj)) {
        item_data->x20_team_id = func_8026B7B0(spawnItem->x0_parent_gobj);
    } else {
        item_data->x20_team_id = -1;
    }
}

extern HSD_JObj* HSD_JObjAlloc(); /* extern */
extern void PSMTXIdentity(Mtx);   /* extern */
extern u8 lbl_804D7849;

// Setup Item JObj
void func_802680CC(HSD_GObj* item_gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    if (item_data->xC8_joint != NULL) {
        HSD_JObj* jobj = HSD_JObjLoadJoint(item_data->xC8_joint);
        func_80390A70(item_gobj, lbl_804D7849, jobj);
    } else {
        HSD_JObj* jobj = HSD_JObjAlloc();
        PSMTXIdentity(jobj->mtx);
        jobj->scl = 0;
        func_80390A70(item_gobj, lbl_804D7849, jobj);
    }
}

extern HSD_DObj* HSD_JObjGetDObj(HSD_JObj*);
extern void* lbl_803F1F90[];

// Setup item render objects?
void func_8026814C(HSD_GObj* item_gobj)
{
    s32 filler[2];
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

BOOL func_802682F0(HSD_GObj* item_gobj) // needs some serious cleaning
{
    s32 var_r4;
    Item* item_data;
    HSD_JObj* var_r0;
    HSD_JObj* var_r3;
    HSD_JObj* var_r3_2;
    HSD_JObj* var_r5;

    item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    if (item_data->xC4_article_data->x10_modelDesc->x4_bone_count != 0) {
        item_data->xBBC_dynamicBoneTable = HSD_ObjAlloc(&lbl_804A0C0C);
        if (item_data->xBBC_dynamicBoneTable == NULL) {
            return FALSE;
        }
        var_r5 = item_gobj->hsd_obj;
        var_r4 = 0;
        while (var_r5 != NULL) {
            (item_data->xBBC_dynamicBoneTable->x0_jobj[var_r4]) = var_r5;
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
                            var_r3_2 = (var_r5 == NULL) ? NULL : var_r5->parent;
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
        item_data->xBBC_dynamicBoneTable = 0;
    }
    return TRUE;
}

// Set item model scale
void func_8026849C(HSD_GObj* item_gobj)
{
    HSD_JObj* temp_jobj = (HSD_JObj*) HSD_GObjGetHSDObj(item_gobj);
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    f32 tmp = item_data->x38_scale;
    Vec3 sp14;
    sp14.x = sp14.y = sp14.z = tmp;
    HSD_JObjSetScale(temp_jobj, &sp14);
}

extern void func_8000FD48(HSD_JObj*, void*, s32);
extern void func_80011710(void*, void*);

// Setup item dynamic bones
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
    item_data->x374_dynamicBonesNum =
        article_data->x14_dynamics->x0_dynamics_num;
    for (i = 0; i < article_data->x14_dynamics->x0_dynamics_num; i++) {
        ItemDynamicsDesc* desc;
        HSD_JObj* jobj;
        desc = &article_data->x14_dynamics->x4_dynamicsDesc[i];
        jobj = item_data->xBBC_dynamicBoneTable->x0_jobj[desc->x0_boneID];
        func_8000FD48(jobj, &item_data->xD4_dynamicBones[i].x8_dynamicBones,
                      desc->x8_num);
        item_data->xD4_dynamicBones[i].x4_root_jobj = jobj;
        item_data->xD4_dynamicBones[i].x0_apply_phys_num = 0;
        func_80011710(&article_data->x14_dynamics->x4_dynamicsDesc[i].x4_params,
                      &item_data->xD4_dynamicBones[i].x8_dynamicBones);
    }
}

extern HSD_JObj* HSD_JObjAlloc();
extern CameraBox* func_80029044(s32);
extern s32 func_80086960(HSD_GObj*);
extern void func_8008702C(s32);
extern struct sdata_ItemGXLink lbl_803F1418[];
extern struct sdata_ItemGXLink lbl_803F2310[];
extern struct sdata_ItemGXLink lbl_803F2F28[];
extern struct sdata_ItemGXLink lbl_803F4CA8[];

void foobar(HSD_GObj* gobj)
{
    Item* it = (Item*) HSD_GObjGetUserData(gobj);
    switch (it->x14_hold_kind) {
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
    if (it->x10_item_kind >= It_Kind_Mario_Fire &&
        it->x10_item_kind < It_Kind_Unk4 && func_80086960(it->x518_ownerGObj))
    {
        it->xDC8_word.flags.xE = 1;
        it->x378_itemColl.x19C = func_800872A4(it->x518_ownerGObj);
        func_8008702C(it->x378_itemColl.x19C);
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

// Create Item
HSD_GObj* func_8026862C(SpawnItem* spawnItem)
{
    HSD_GObj* gobj;
    void* user_data;

    if (func_8026784C(spawnItem->xC_hold_kind, spawnItem->x8_item_id) != 0) {
        return NULL;
    }
    gobj = GObj_Create(6, 9, 0);
    if (gobj == NULL) {
        return NULL;
    }
    if (spawnItem->x8_item_id < It_Kind_Kuriboh) {
        // Common items
        GObj_SetupGXLink(
            gobj, lbl_803F1418[spawnItem->x8_item_id].x0_renderFunc, 6, 0);
    } else if (spawnItem->x8_item_id < Pokemon_Tosakinto) {
        // Character items
        int idx = spawnItem->x8_item_id - It_Kind_Kuriboh;
        GObj_SetupGXLink(gobj, lbl_803F2F28[idx].x0_renderFunc, 6, 0);
    } else if (spawnItem->x8_item_id < It_Kind_Old_Kuri) {
        // Pokemon
        int idx = spawnItem->x8_item_id - Pokemon_Tosakinto;
        GObj_SetupGXLink(gobj, lbl_803F2310[idx].x0_renderFunc, 6, 0);
    } else {
        // Stage items
        int idx = spawnItem->x8_item_id - It_Kind_Old_Kuri;
        GObj_SetupGXLink(gobj, lbl_803F4CA8[idx].x0_renderFunc, 6, 0);
    }
    user_data = HSD_ObjAlloc(&lbl_804A0BE0);
    if (user_data == NULL) {
        func_80390228(gobj);
        return NULL;
    }
    GObj_InitUserData(gobj, 6, lbl_8026AE10, user_data);
    func_80267AA8(gobj, spawnItem);
    func_802680CC(gobj);
    if (func_802682F0(gobj) != FALSE) {
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

// Item spawn prefunction - spawn airborne
void func_80268B18(SpawnItem* spawnItem)
{
    spawnItem->x48_ground_or_air = GA_Air;
    spawnItem->x10 = 0;
    func_802674AC(spawnItem);
    func_8026862C(spawnItem);
}

// Item spawn prefunction - spawn grounded
void func_80268B5C(SpawnItem* spawnItem)
{
    spawnItem->x48_ground_or_air = GA_Ground;
    spawnItem->x10 = 0;
    func_802674AC(spawnItem);
    func_8026862C(spawnItem);
}

// Item spawn prefunction - spawn grounded and toggle unknown true
void func_80268B9C(SpawnItem* spawnItem)
{
    spawnItem->x48_ground_or_air = GA_Ground;
    spawnItem->x10 = 1;
    func_802674AC(spawnItem);
    func_8026862C(spawnItem);
}

extern void HSD_JObjAddAnim(void*, void*, void*, void*);

// Adds AObjs to item model
void func_80268BE0(HSD_JObj* item_jobj, HSD_AnimJoint* anim_joint,
                   HSD_MatAnimJoint* matanim_joint, ItemState_ParamStruct* arg3,
                   Item* item_data)
{
    void* functionArg1;
    void* functionArg2;
    void* functionArg3;

    s32 temp_r0;

    if (item_jobj != NULL) {
        if (anim_joint != NULL) {
            for (temp_r0 = 0; temp_r0 < item_data->x374_dynamicBonesNum;
                 temp_r0++)
                if (item_jobj ==
                    item_data->xD4_dynamicBones[temp_r0].x4_root_jobj)
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
                        if (arg3 != NULL) {
                            functionArg3 = arg3->x4_unk;
                        }
                        func_80268BE0(item_jobj->next, functionArg1,
                                      functionArg2, functionArg3, item_data);
                    }
                    return;
                }
        }
        HSD_JObjAddAnim(item_jobj, anim_joint, matanim_joint, arg3);
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
            if (arg3 != NULL) {
                functionArg3 = arg3->x0_unk;
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
            if (arg3 != NULL) {
                functionArg3 = arg3->x4_unk;
            }
            func_80268BE0(item_jobj->next, functionArg1, functionArg2,
                          functionArg3, item_data);
        }
    }
}

// Unk Item AObj-related function
void func_80268D34(HSD_GObj* item_gobj, struct ItemStateDesc* itemStateDesc)
{
    HSD_JObj* item_jobj = (HSD_JObj*) HSD_GObjGetHSDObj(item_gobj);
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    HSD_JObjRemoveAnimAll(item_jobj);
    if (item_data->xC8_joint != NULL) {
        void* bonestruct_arg;
        if (item_jobj == NULL) {
            bonestruct_arg = NULL;
        } else {
            bonestruct_arg = item_jobj->child;
        }
        func_8000B804(bonestruct_arg, item_data->xC8_joint->child);
    }
    func_80268BE0(item_jobj, itemStateDesc->x0_anim_joint,
                  itemStateDesc->x4_matanim_joint, itemStateDesc->x8_parameters,
                  item_data);
    func_8000BA0C(item_jobj, item_data->x5D0_animFrameSpeed);
    HSD_JObjReqAnimAll(item_jobj, 0.0f);
}

// Advance item animation?
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

// Copy item script
void func_80268E40(Item* item_data, struct ItemStateDesc* itemStateDesc)
{
    item_data->x52C_item_script = itemStateDesc->xC_script;
    item_data->x530 = 0;
    item_data->x524 = 0.0f;
}

extern struct r13_ColAnimStruct* lbl_804D6D04;

static inline void HSD_JObjSetScaleItem(Item* it, HSD_JObj* jobj, Vec3* scl)
{
    scl->x = scl->y = scl->z = it->x38_scale;
    HSD_JObjSetScale(jobj, scl);
}

// Item State Change
void func_80268E5C(HSD_GObj* item_gobj, s32 itemStateID, s32 itemStateFlags)
{
    Vec3 sp4C;
    Vec3 scl;
    struct ItemStateTable* temp_r30;
    struct ItemStateDesc* temp_r29;
    HSD_JObj* item_jobj1_3;
    HSD_JObj* item_jobj1_2;
    void* new_var;
    void* new_var2;
    void* new_var3;
    Item* item_data2;
    Item* item_data3;
    HSD_JObj* item_jobj;
    Item* item_data;
    ItemAttr* item_attr;
    HSD_JObj* boneCopyArg;
    struct ItemStateDesc* temp_r23;
    s32 temp_r0;

    item_jobj = (HSD_JObj*) HSD_GObjGetHSDObj(item_gobj);
    item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    item_data->x24_item_state_index = itemStateID;
    item_data->xDC8_word.flags.x14 = 0;
    HSD_JObjSetTranslate(item_gobj->hsd_obj, &item_data->x4C_pos);
    func_80067624(item_gobj, &item_data->xBC0);
    if (item_data->xDC8_word.flags.x2 == 1) {
        func_8026BDCC(item_gobj);
        func_80274EF8(item_gobj);
    }
    if ((itemStateFlags & ITEM_MODEL_UPDATE)) {
        func_80274740(item_gobj);
    }
    if (!(itemStateFlags & ITEM_COLANIM_PRESERVE) &&
        lbl_804D6D04[item_data->x548_colorOverlay.x28_colanim].x5_unk != 0)
    {
        func_80279BBC(item_data);
    }
    if (!(itemStateFlags & ITEM_SFX_PRESERVE)) {
        func_8026B074(item_data);
    }
    HSD_JObjSetFacingDirItem(item_jobj, item_data);
    if (itemStateFlags & ITEM_DROP_UPDATE) {
        item_data->itdmg.xC40 = item_data->itdmg.xC44;
    } else {
        item_data->itdmg.xC40 = 1.0f;
    }
    if (!(itemStateFlags & ITEM_HIT_PRESERVE) &&
        item_data->xDC8_word.flags.x16 != 0)
    {
        func_802725D4(item_gobj);
    }

    item_data->itdmg.xCC8_knockback = 0.0f;
    temp_r30 =
        (new_var = &item_data->xBC_itemStateContainer->stateTable[itemStateID]);
    item_data->x28_item_anim_index = temp_r30->x0_state_id;
    item_data->x5CC_currentAnimFrame = 0.0f;
    temp_r0 = item_data->x28_item_anim_index;
    if (temp_r0 != -1) {
        item_data->xD0_itemStateDesc =
            (temp_r23 =
                 (temp_r29 =
                      (new_var2 = &item_data->xC4_article_data->xC_itemStates
                                       ->x0_itemStateDesc[temp_r0])));
        temp_r23 = (new_var3 = item_data->xD0_itemStateDesc);
        if (temp_r23 != NULL && (itemStateFlags & ITEM_ANIM_UPDATE)) {
            func_80268D34(item_gobj, temp_r23);
            if (itemStateFlags & 0x80) {
                item_jobj1_2 = item_gobj->hsd_obj;
                item_data3 = GetItemData(item_gobj);
                item_data3->x38_scale = item_data3->xCC_item_attr->x60_scale;
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
            item_data->x530 = 0U;
            item_data->x524 = 0.0f;
        } else if (temp_r23 != NULL && (itemStateFlags & ITEM_CMD_UPDATE)) {
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
    item_data->itcb.xD14_callback_Anim = temp_r30->x4_callback_anim;
    item_data->itcb.xD18_callback_Phys = temp_r30->x8_callback_phys;
    item_data->itcb.xD1C_callback_Coll = temp_r30->xC_callback_coll;
    item_data->itcb.xD20_callback_Accessory = NULL;
    item_data->itcb.xD24_callback_Inert = NULL;
    item_data->itcb.xD28_callback_EnterHitlag = NULL;
    item_data->itcb.xD2C_callback_ExitHitlag = NULL;
    item_data->itcb.xD30_callback_JumpedOn = NULL;
    item_data->xDD0_flag.bits.b5 = 0;
    item_data->xD09 = 0;
    func_802714C0(item_gobj);
}

// Item Think - Hitlag
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
    if (item_data->itdmg.xCBC_hitlagFrames > 0.0f) {
        item_data->itdmg.xCBC_hitlagFrames -= 1.0f;
        if (item_data->itdmg.xCBC_hitlagFrames <= 0.0f) {
            item_data->itdmg.xCBC_hitlagFrames = 0.0f;
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

// Advance item animation + script?
void func_802694CC(HSD_GObj* item_gobj)
{
    HSD_JObj* item_jobj = (HSD_JObj*) HSD_GObjGetHSDObj(item_gobj);
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    HSD_JObjAnimAll(item_jobj);
    item_data->x5CC_currentAnimFrame = func_8000BDB4(item_jobj);
    func_802799E4(item_gobj);
}

// Item Think - Animation
void lbl_80269528(HSD_GObj* item_gobj)
{
    s32 filler[2];
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    if (item_data->xDC8_word.flags.x9 == 0) {
        func_802694CC(item_gobj);
        if (item_data->itcb.xD14_callback_Anim != NULL &&
            item_data->itcb.xD14_callback_Anim(item_gobj))
        {
            item_data->xD60_destroyType = 0;
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
        item_data->x10_item_kind < It_Kind_L_Gun_Ray &&
        !item_data->xDD0_flag.bits.b3)
    {
        item_data->xD44_lifeTimer -= 1.0f;
        if (item_data->xD44_lifeTimer <= 0.0f) {
            item_data->xD60_destroyType = 0;
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

// Item Think - Check for Blast Zones
BOOL func_802696CC(HSD_GObj* item_gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    if ((item_data->xDCC_flag.b4567 & 8) &&
        item_data->x4C_pos.x > Stage_GetBlastZoneRightOffset())
    {
        item_data->xD60_destroyType = 3;
        func_8026A8EC(item_gobj);
        return TRUE;
    }
    if ((item_data->xDCC_flag.b4567 & 4) &&
        item_data->x4C_pos.x < Stage_GetBlastZoneLeftOffset())
    {
        item_data->xD60_destroyType = 3;
        func_8026A8EC(item_gobj);
        return TRUE;
    }
    if ((item_data->xDCC_flag.b4567 & 1) && item_data->x4C_pos.y > 10000.0f) {
        item_data->xD60_destroyType = 3;
        func_8026A8EC(item_gobj);
        return TRUE;
    }
    if ((item_data->xDCC_flag.b4567 & 2) &&
        item_data->x4C_pos.y < Stage_GetBlastZoneBottomOffset())
    {
        item_data->xD60_destroyType = 3;
        func_8026A8EC(item_gobj);
        return TRUE;
    }
    return FALSE;
}

// Item Think - Physics
void func_802697D4(HSD_GObj* item_gobj)
{
    Vec3 sp1C;
    s32 filler[3];

    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    if (item_data->xDC8_word.flags.x9 == 0 &&
        item_data->itcb.xD18_callback_Phys != NULL)
    {
        item_data->itcb.xD18_callback_Phys(item_gobj);
    }
    if (item_data->xDC8_word.flags.x13 == 0) {
        if (item_data->xDC8_word.flags.x9 == 0) {
            PSVECAdd(&item_data->x40_vel, &item_data->x70_nudge, &sp1C);
            if ((item_data->xC0_unk_state == 0) &&
                (item_data->xDCD_flag.bits.b3 == 0))
            {
                func_8027737C(item_gobj, &sp1C);
            }
            PSVECAdd(&item_data->x4C_pos, &sp1C, &item_data->x4C_pos);
        }
        if (item_data->xDCC_flag.b3 == 1 &&
            (item_data->xDCC_flag.b4567 & 0xF) && func_802696CC(item_gobj))
        {
            return;
        }
        if (item_data->xD3C_spinSpeed && item_data->xC0_unk_state == 1) {
            func_80274A64(item_gobj);
        }
    }
    if ((item_data->xDD1_flag.bits.b1 != 0) && (item_data->xC0_unk_state == 1))
    {
        func_801C9E60(&item_data->x58_vec_unk);
    }
    PSVECAdd(&item_data->x4C_pos, &item_data->x58_vec_unk, &item_data->x4C_pos);
    func_80273484(item_gobj);
    if (item_data->xC0_unk_state == 0) {
        if ((item_data->xDCE_flag.bits.b3 != 0) &&
            (func_8026D604(item_gobj) != 0))
        {
            func_800567C0(item_data->xC30, &item_data->x4C_pos,
                          &item_data->x64_vec_unk2);
        } else {
            func_800567C0(item_data->x378_itemColl.x14C_ground.index,
                          &item_data->x4C_pos, &item_data->x64_vec_unk2);
        }
    }
    PSVECAdd(&item_data->x4C_pos, &item_data->x64_vec_unk2,
             &item_data->x4C_pos);
    func_8027346C(item_gobj);
    func_802714C0(item_gobj);
}

// Item Think - Collision
void func_80269978(HSD_GObj* item_gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    if (item_data->itcb.xD1C_callback_Coll != NULL &&
        item_data->itcb.xD1C_callback_Coll(item_gobj))
    {
        item_data->xD60_destroyType = 1;
        func_8026A8EC(item_gobj);
    } else {
        HSD_JObjSetTranslate((HSD_JObj*) HSD_GObjGetHSDObj(item_gobj),
                             &item_data->x4C_pos);
        func_8027574C(item_gobj);
        func_8026C368(item_gobj);
    }
}

// Item Think - Accessory + Camera Box
void lbl_80269A9C(HSD_GObj* item_gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    func_80067624(item_gobj, &item_data->xBC0);
    if (item_data->xDC8_word.flags.x9 == 0) {
        if (item_data->itcb.xD20_callback_Accessory != NULL) {
            item_data->itcb.xD20_callback_Accessory(item_gobj);
        }
    }
    item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    if (item_data->xDCD_flag.bits.b01 != 0) {
        CameraBox* cameraBox = item_data->x520_cameraBox;
        if (cameraBox != NULL) {
            cameraBox->x10 = item_data->x4C_pos;
            cameraBox->x1C = item_data->x4C_pos;
        }
    }
    func_80271A58(item_gobj);
    func_80272280(item_gobj);
    func_802722B0(item_gobj);
}

// Item Think - Yellow Bar Collision (cb_JumpedOn)
void lbl_80269B60(HSD_GObj* item_gobj)
{
    Item* item_data = item_gobj->user_data;
    if (item_data->xCFC != 0 &&
        item_data->itcb.xD30_callback_JumpedOn != NULL &&
        item_data->itcb.xD30_callback_JumpedOn(item_gobj))
    {
        item_data->xD60_destroyType = 2;
        func_8026A8EC(item_gobj);
        return;
    }
    func_8027137C(item_gobj);
    func_8027146C(item_gobj);
}

// Item Think - Grab
// Somewhat arbitrary. Does not run on Hook Shot / Grapple Beam, rather items
// such as the Barrel Cannon.
void lbl_80269BE4(HSD_GObj* item_gobj)
{
    Item* item_data = item_gobj->user_data;
    if (item_data->xDD0_flag.bits.b5 != 0) {
        func_802701BC(item_gobj);
        if (item_data->xD00_grabGObj != NULL) {
            item_data->itcb.xD34_callback_Grab_ItemCB(item_gobj);
            item_data->itcb.xD38_callback_Grab_VictimCB(
                item_data->xD00_grabGObj, item_gobj);
        }
    }
}

// Item Think - Hit Collision Logic
void lbl_80269C5C(HSD_GObj* item_gobj)
{
    s32 filler[2];
    func_8026F9A0();
    func_802703E8(item_gobj);
    func_802706D0(item_gobj);
    func_80270E30(item_gobj);
}

// Add to damage taken
void func_80269CA0(Item* item_data, s32 damage)
{
    item_data->itdmg.xC9C += damage;
    if (item_data->itdmg.xC9C > 999) {
        item_data->itdmg.xC9C = 999;
    }
}

// Set damage struct
void func_80269CC4(HSD_GObj* item_gobj)
{
    Item* temp_item;

    temp_item = item_gobj->user_data;
    temp_item->itdmg.xCA0 = 0;
    temp_item->itdmg.xCA4 = 0;
    temp_item->itdmg.xC94 = 0;
    temp_item->itdmg.xCC8_knockback = 0.0f;
    temp_item->itdmg.xC34_damageDealt = 0;
    temp_item->itdmg.xC48 = 0;
    temp_item->itdmg.xC4C = 0;
    temp_item->itdmg.xC50 = 0;
    temp_item->itdmg.xCCC_incDamageDirection = 0.0f;
    temp_item->itdmg.xCB8_outDamageDirection = 0.0f;
    temp_item->itdmg.xC68 = 0.0f;
    temp_item->itdmg.xCD0 = 0.0f;
    temp_item->itdmg.xCC0 = 0.0f;
    temp_item->xDCF_flag.bits.b6 = 0;
    temp_item->itdmg.xCC4 = 0;
    temp_item->itdmg.xCEC_fighterGObj = 0;
    temp_item->itdmg.xCF0_itemGObj = 0;
    temp_item->xCF4_fighterGObjUnk = 0;
    temp_item->xCF8_detectGObj = 0;
    temp_item->itdmg.xC64_reflectGObj = 0;
    temp_item->itdmg.xC90_absorbGObj = 0;
    temp_item->xCFC = 0;
    temp_item->itdmg.xCB4 = -1;
    temp_item->itdmg.xC38 = -1;
    temp_item->itdmg.xCE8 = 0.0f;
    temp_item->itdmg.xCE4 = 0.0f;
    temp_item->itdmg.xCE0 = 0.0f;
    temp_item->itdmg.xCDC = 0.0f;
    temp_item->itdmg.xCD8 = 0.0f;
    temp_item->itdmg.xCD4 = 0.0f;
    temp_item->xDCE_flag.bits.b5 = 0;
    temp_item->xDCE_flag.bits.b4 = 0;
    temp_item->xDCC_flag.b1 = 0;
    temp_item->itdmg.xC70 = 1.0f;
    temp_item->itdmg.xC6C = 1.0f;
    temp_item->xDCC_flag.b2 = 0;
    temp_item->xDC8_word.flags.xB = 0;
    temp_item->itdmg.xCA8 = 0;
    temp_item->xDC8_word.flags.x3 = 0;
    temp_item->xDC8_word.flags.x4 = 0;
    temp_item->xDCE_flag.bits.b6 = 0;
}

// Item Think - Shield Collision
BOOL func_80269DC8(HSD_GObj* item_gobj)
{
    BOOL (*cb_OnShieldBounce)(HSD_GObj*);
    BOOL (*cb_OnHitShield)(HSD_GObj*);
    Item* item_data;

    item_data = item_gobj->user_data;
    if (item_data->xDCE_flag.bits.b5 && item_data->xC0_unk_state == 1 &&
        (item_data->xDCE_flag.bits.b4 ||
         item_data->itdmg.xC54 <
             (f32) (M_PI / 180) * (90.0f + lbl_804D6D28->x80_float[0x18])))
    {
        if (item_data->xDCE_flag.bits.b4 == 0) {
            item_data->itdmg.xC54 -= M_PI / 2;
            if (item_data->itdmg.xC54 < 0.0f) {
                item_data->itdmg.xC54 = 0.0f;
            }
        }
        cb_OnShieldBounce =
            item_data->xB8_itemLogicTable->x30_callback_OnShieldBounce;
        if (cb_OnShieldBounce != NULL && cb_OnShieldBounce(item_gobj)) {
            item_data->xD60_destroyType = 2;
            func_8026A8EC(item_gobj);
            return TRUE;
        }
    } else {
        cb_OnHitShield =
            item_data->xB8_itemLogicTable->x34_callback_OnHitShield;
        if (func_80274C78(item_gobj)) {
            item_data->itdmg.xCA8 = item_data->itdmg.xC50;
        }
        if (cb_OnHitShield != NULL && cb_OnHitShield(item_gobj)) {
            item_data->xD60_destroyType = 2;
            func_8026A8EC(item_gobj);
            return TRUE;
        }
    }
    return FALSE;
}

// Item Think - On Reflect
BOOL func_80269F14(HSD_GObj* item_gobj)
{
    f32 temp_f30;
    BOOL (*cb_OnReflect)(HSD_GObj*);
    s32 i;
    u32 var_r27;
    Item* temp_item = (Item*) HSD_GObjGetUserData(item_gobj);

    if (temp_item->xDCC_flag.b1 == 0) {
        if (temp_item->x10_item_kind == 0x22) {
            if (temp_item->xDCC_flag.b2 == 0) {
                temp_item->x518_ownerGObj = temp_item->itdmg.xC64_reflectGObj;
                temp_item->x20_team_id =
                    func_80086EB4(temp_item->x518_ownerGObj);
            }
        } else {
            temp_item->x518_ownerGObj = temp_item->itdmg.xC64_reflectGObj;
            temp_item->x20_team_id = func_80086EB4(temp_item->x518_ownerGObj);
        }
    }
    func_80225DD8(item_gobj, temp_item->x518_ownerGObj);
    temp_item->xD90 = temp_item->itdmg.xC74;
    temp_item->xD94 = temp_item->itdmg.xC78;
    temp_item->xD9C = temp_item->itdmg.xC80;
    temp_item->xDA4_word = temp_item->itdmg.xC88;
    temp_item->xDA8_short = temp_item->itdmg.xC8C;
    cb_OnReflect = temp_item->xB8_itemLogicTable->x24_callback_OnReflect;
    if (cb_OnReflect != NULL && cb_OnReflect(item_gobj)) {
        temp_item->xD60_destroyType = 2;
        func_8026A8EC(item_gobj);
        return TRUE;
    }
    if (temp_item->xDCC_flag.b0 == 0) {
        for (i = 0; i < 4; i++) // 4 here is the maximum amount of hitboxes
                                // available in the vanilla Item struct
        {
            if (temp_item->x5D4_hitboxes[i].x0_toggle) {
                temp_f30 = temp_item->x5D4_hitboxes[i].xC_damage_staled *
                               temp_item->itdmg.xC6C +
                           0.99f;
                var_r27 = temp_f30;
                if (var_r27 > lbl_804D6D28->xD8) {
                    var_r27 = lbl_804D6D28->xD8;
                }
                func_80272460(&temp_item->x5D4_hitboxes[i], var_r27, item_gobj);
            }
        }
    }
    return FALSE;
}

// Item Think - Exit Hitlag Check
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

// Item Think - Exit Hitlag Check 2
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

static inline void func_8026A158_helper(HSD_GObj* atkCollGObj)
{
    Item* temp_item = (Item*) HSD_GObjGetUserData(atkCollGObj);
    temp_item->xDC8_word.flags.x8 = 1;
    func_8026A158(atkCollGObj);
}

void func_8026A158(HSD_GObj* item_gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    if (item_data->itcb.xD28_callback_EnterHitlag != NULL) {
        item_data->itcb.xD28_callback_EnterHitlag(item_gobj);
    }
    item_data->xDC8_word.flags.x9 = 1;
    if (item_data->xD04_atkCollItem != NULL &&
        func_80272D1C(item_data->xD04_atkCollItem) &&
        item_data->xDC8_word.flags.x8 == 0)
    {
        func_8026A158_helper(item_data->xD04_atkCollItem);
    }
}

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

// Item Think - Exit Hitlag
void func_8026A1E8(HSD_GObj* item_gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    if (item_data->itcb.xD2C_callback_ExitHitlag != NULL) {
        item_data->itcb.xD2C_callback_ExitHitlag(item_gobj);
    }
    item_data->xDC8_word.flags.x9 = 0;
    if (item_data->xD04_atkCollItem != NULL &&
        func_80272D1C(item_data->xD04_atkCollItem) &&
        item_data->xDC8_word.flags.x8 == 0)
    {
        func_8026A1E8_inline(item_data->xD04_atkCollItem);
    }
}

static inline BOOL processCallback(BOOL (*cb)(HSD_GObj*), HSD_GObj* item_gobj,
                            Item* item_data)
{
    if (cb && cb(item_gobj)) {
        item_data->xD60_destroyType = 2;
        func_8026A8EC(item_gobj);
        return TRUE;
    }
    return FALSE;
}

static inline BOOL OnTakeDamageThink(HSD_GObj* item_gobj, Item* item_data)
{
    item_data->itdmg.xC9C += item_data->itdmg.xCA0;
    if (item_data->itdmg.xC9C > 999) {
        item_data->itdmg.xC9C = 999;
    }
    item_data->itdmg.xCA8 = item_data->itdmg.xCA0;
    item_data->xDC8_word.flags.xB = 1;
    return processCallback(
        item_data->xB8_itemLogicTable->x1C_callback_OnTakeDamage, item_gobj,
        item_data);
}

static inline BOOL OnClankThink(HSD_GObj* item_gobj, Item* item_data)
{
    BOOL(*cb_OnClank)
    (HSD_GObj*) = item_data->xB8_itemLogicTable->x28_callback_OnClank;
    if (func_80274C78(item_gobj)) {
        item_data->itdmg.xCA8 = item_data->itdmg.xC48;
    }
    return processCallback(cb_OnClank, item_gobj, item_data);
}

static inline BOOL OnGiveDamageThink(HSD_GObj* item_gobj, Item* item_data)
{
    BOOL(*cb_OnGiveDamage)
    (HSD_GObj*) = item_data->xB8_itemLogicTable->x18_callback_OnGiveDamage;
    if (func_80274C78(item_gobj)) {
        item_data->itdmg.xCA8 = item_data->itdmg.xC34_damageDealt;
    }
    return processCallback(cb_OnGiveDamage, item_gobj, item_data);
}

static inline void EnterHitlagThink(HSD_GObj* item_gobj, Item* item_data)
{
    if (!item_data->xDC8_word.flags.x9) {
        item_data = GetItemData(item_gobj);
        if (item_data->itcb.xD28_callback_EnterHitlag)
            item_data->itcb.xD28_callback_EnterHitlag(item_gobj);
        item_data->xDC8_word.flags.x9 = 1;

        if ((item_data->xD04_atkCollItem) &&
            func_80272D1C(item_data->xD04_atkCollItem) &&
            !item_data->xDC8_word.flags.x8)
        {
            func_8026A158_helper(item_data->xD04_atkCollItem);
        }
    }
}

static inline void checkHitLag(f32 min_value, Item* item_data)
{
    if (item_data->itdmg.xCBC_hitlagFrames < min_value) {
        item_data->itdmg.xCBC_hitlagFrames = min_value;
    }
    item_data->xDC8_word.flags.xA = 1;
}

// Item Think - Hit Collision
void lbl_8026A294(HSD_GObj* item_gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);

    if ((item_data->itdmg.xCC8_knockback) || (item_data->itdmg.xCA0)) {
        if (OnTakeDamageThink(item_gobj, item_data))
            return;
    } else if (item_data->itdmg.xC50) {
        if (func_80269DC8(item_gobj))
            return;
    } else if (item_data->itdmg.xC48) {
        if (OnClankThink(item_gobj, item_data))
            return;
    } else if ((item_data->itdmg.xC34_damageDealt) || (item_data->itdmg.xC4C)) {
        if (OnGiveDamageThink(item_gobj, item_data))
            return;
    } else if (item_data->itdmg.xC64_reflectGObj != NULL) {
        if (func_80269F14(item_gobj))
            return;
    } else if (item_data->itdmg.xC90_absorbGObj != NULL) {
        if (processCallback(
                item_data->xB8_itemLogicTable->x2C_callback_OnAbsorb, item_gobj,
                item_data))
        {
            return;
        }
    } else if (item_data->xDCE_flag.bits.b6) {
        if (processCallback(item_data->itcb.xD24_callback_Inert, item_gobj,
                            item_data))
        {
            return;
        }
    }

    if ((item_data->xDC8_word.flags.xD) && (item_data->itdmg.xCC0 > 0.0f)) {
        checkHitLag(item_data->itdmg.xCC0, item_data);

        EnterHitlagThink(item_gobj, item_data);
    } else if (item_data->itdmg.xCA8) {
        checkHitLag(func_8026B424(item_data->itdmg.xCA8), item_data);

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

void lbl_8026A788(HSD_GObj* item_gobj) // Item Think - Process Dynamic Bones
{
    Item* item_data = item_gobj->user_data;
    int dynamicBonesNum = item_data->x374_dynamicBonesNum;
    ItemDynamicBones* dynamicBones = item_data->xD4_dynamicBones;
    int i;

    func_80272304(item_gobj);
    for (i = 0; i < dynamicBonesNum; i++, dynamicBones++) {
        func_8001044C(&dynamicBones->x8_dynamicBones, &item_data->xB6C,
                      item_data->xB68, 0.0f, 0, dynamicBones->x0_apply_phys_num,
                      0, 1);
    }
}

void func_8026A810(HSD_GObj* item_gobj) // Item Think - Spawn
{
    Item* temp_item = item_gobj->user_data;
    if (temp_item->xB8_itemLogicTable->x4_callback_OnSpawn != NULL) {
        temp_item->xB8_itemLogicTable->x4_callback_OnSpawn(item_gobj);
    }
}

extern void func_80086724(HSD_GObj*, HSD_GObj*);
extern void func_80086764(HSD_GObj*);
extern HSD_GObj* func_800867CC(HSD_GObj*);

void func_8026A848(HSD_GObj* item_gobj,
                   HSD_GObj* fighter_gobj) // Remove Item from Player
{
    Item* temp_item = GetItemDirect(item_gobj);

    if (temp_item->x14_hold_kind == 8 && temp_item->x10_item_kind != 0x3A &&
        temp_item->x10_item_kind != 0x3B && temp_item->x10_item_kind != 0x63 &&
        temp_item->x10_item_kind != 0x67)
    {
        if (func_800867CC(fighter_gobj) == item_gobj) {
            func_80086764(fighter_gobj);
        }
    } else if (func_800867A0(fighter_gobj, item_gobj)) {
        func_80086724(fighter_gobj, item_gobj);
    }
}

extern void efLib_DestroyAll(HSD_GObj*);
extern void func_8000FD18(void*);
extern void func_80086724(HSD_GObj*, HSD_GObj*);
extern void func_80086764(HSD_GObj*);
extern HSD_GObj* func_800867CC(HSD_GObj*);
extern s32 func_80086960(HSD_GObj*);
extern void func_80087050(s32);

static inline void DestroyItemInline(HSD_GObj* item_gobj, Item* item_data)
{
    Item* item_data3 = item_gobj->user_data;
    HSD_GObj* temp_gobj = item_data->x518_ownerGObj;
    if (item_data3->x14_hold_kind == 8 && item_data3->x10_item_kind != 0x3A &&
        item_data3->x10_item_kind != 0x3B &&
        item_data3->x10_item_kind != 0x63 && item_data3->x10_item_kind != 0x67)
    {
        if (func_800867CC(temp_gobj) == item_gobj) {
            func_80086764(temp_gobj);
        }
    } else if (func_800867A0(temp_gobj, item_gobj)) {
        func_80086724(temp_gobj, item_gobj);
    }
}

static inline void ItemSwitch(HSD_GObj* item_gobj)
{
    Item* temp_item = item_gobj->user_data;
    s32 destroyType = temp_item->xD60_destroyType;
    switch (destroyType) {
    case 0:
        func_8027327C(item_gobj, temp_item->xCC_item_attr->x64_destroy_gfx,
                      temp_item->xD7C_destroySFX);
        break;

    case 2:
    case 1:
        func_8027327C(item_gobj, temp_item->xCC_item_attr->x68,
                      temp_item->xD80);
        break;

    case 3:
    case 4:
        break;
    }
}

static inline void RunCallback(HSD_GObj* item_gobj, void (*cb_Process)(HSD_GObj*))
{
    if (cb_Process != NULL) {
        cb_Process(item_gobj);
    }
}

static inline void func_8026A8EC_inline1(HSD_GObj* item_gobj)
{
    Item* it = (Item*) HSD_GObjGetUserData(item_gobj);
    if (it->xDC8_word.flags.xE != 0) {
        func_80087050(it->x378_itemColl.x19C);
        it->xDC8_word.flags.xE = 0;
        it->x378_itemColl.x19C = -1;
    }
}

static inline void func_8026A8EC_inline2(HSD_GObj* item_gobj)
{
    Item* it = (Item*) HSD_GObjGetUserData(item_gobj);
    RunCallback(item_gobj, it->xB8_itemLogicTable->x8_callback_OnDestroy);
}

static inline void func_8026A8EC_inline3(HSD_GObj* item_gobj)
{
    Item* it = (Item*) HSD_GObjGetUserData(item_gobj);
    if (it->xDCD_flag.bits.b01 != 0 && it->x520_cameraBox != NULL) {
        func_800290D4(it->x520_cameraBox);
        it->x520_cameraBox = NULL;
        it->xDCD_flag.bits.b01 = 0;
    }
}

// Destroy Item
void func_8026A8EC(HSD_GObj* item_gobj)
{
    s32 i;
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);

    if (!func_80272D1C(item_gobj) || item_data == NULL) {
        OSReport("===== Not Found Item_Struct!! =====\n");
        __assert("item.c", 0x965, "0");
    }
    func_802725D4(item_gobj);
    func_802675A8(item_gobj);
    func_8026A8EC_inline1(item_gobj);
    efLib_DestroyAll(item_gobj);
    if (item_data->xDCF_flag.bits.b2 == 0 &&
        (item_data->xDC8_word.flags.x13 == 0 ||
         item_data->x518_ownerGObj == NULL))
    {
        ItemSwitch(item_gobj);
    }
    func_8026A8EC_inline2(item_gobj);
    if (item_data->xDC8_word.flags.x13 != 0 &&
        item_data->x518_ownerGObj != NULL &&
        func_80086960(item_data->x518_ownerGObj))
    {
        DestroyItemInline(item_gobj, item_data);
    }
    item_data->x518_ownerGObj = NULL;
    func_8026A8EC_inline3(item_gobj);
    for (i = 0; i < item_data->x374_dynamicBonesNum; i++) {
        func_8000FD18(&item_data->xD4_dynamicBones[i].x8_dynamicBones);
    }
    func_8026B0B4(item_gobj);
    func_80067688(&item_data->xBC0);
    func_80390228(item_gobj);
}

// Make Item Held
void func_8026AB54(HSD_GObj* item_gobj, HSD_GObj* pickupGFX, u8 pickupSFX)
{
    s32 filler[4];
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);

    func_80273168(item_gobj);
    func_802742F4(item_gobj, pickupGFX, pickupSFX);
    RunCallback(item_gobj, item_data->xB8_itemLogicTable->xC_callback_OnPickup);
    func_8026B074(item_data);
}

// Drop Item
void func_8026ABD8(HSD_GObj* item_gobj, Vec3* pos, f32 arg2)
{
    s32 filler[2];
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);

    item_data->itdmg.xC44 = arg2;
    func_802731A4(item_gobj);
    func_80273B50(item_gobj, pos);
    RunCallback(item_gobj, item_data->xB8_itemLogicTable->x10_callback_OnDrop);
    func_80274198(item_gobj, 1);
    func_802754D4(item_gobj);
    if (func_8026B6C8(item_gobj) != 0) {
        func_80275390(item_gobj);
    }
}

// This is actually another Item Drop function
void func_8026AC74(HSD_GObj* item_gobj, s32 dropGFX, s32 dropSFX, f32 arg8)
{
    Item* item_data = GetItemData(item_gobj);
    item_data->itdmg.xC44 = arg8;
    func_802731A4(item_gobj);
    func_80273748(item_gobj, dropGFX, dropSFX);
    RunCallback(item_gobj, item_data->xB8_itemLogicTable->x10_callback_OnDrop);
    func_802741F4(item_gobj, 1);
    func_802754D4(item_gobj);
    if (func_8026B6C8(item_gobj) != 0) {
        func_80275390(item_gobj);
    }
}

// Throw Item
void func_8026AD20(HSD_GObj* item_gobj, s32 dropGFX, s32 dropSFX, f32 arg8)
{
    Item* item_data = GetItemData(item_gobj);
    func_802731E0(item_gobj);
    item_data->itdmg.xC44 = arg8;
    func_80273748(item_gobj, dropGFX, dropSFX);
    RunCallback(item_gobj, item_data->xB8_itemLogicTable->x14_callback_OnThrow);
    func_802741F4(item_gobj, 1);
    func_802754D4(item_gobj);
}

// Make Item Airborne
void func_8026ADC0(HSD_GObj* item_gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    if (item_data->xB8_itemLogicTable->x20_callback_EnterAir != NULL) {
        item_data->xB8_itemLogicTable->x20_callback_EnterAir(item_gobj);
        item_data->xDC8_word.flags.x1F = 1;
    }
}

// Clear Item Struct ?
void lbl_8026AE10(void* user_data)
{
    Item* item_data = (Item*) user_data;
    if (item_data->xBBC_dynamicBoneTable != NULL) {
        HSD_ObjFree(&lbl_804A0C0C, item_data->xBBC_dynamicBoneTable);
    }
    HSD_ObjFree(&lbl_804A0BE0, item_data);
}

u32 func_8026AE60(void)
{
    u32 ret = lbl_804D6D14++;
    if (lbl_804D6D14 == 0) {
        lbl_804D6D14++;
    }
    return ret;
}

extern u32 func_800233EC(s32);

// Play Item SFX
void func_8026AE84(Item* item_data, enum_t sfxID, u8 pan, u8 volume)
{
    if (sfxID != 0x83D60) {
        if (sfxID != 0x83D61) {
            item_data->xD6C = func_800237A8(func_800233EC(sfxID), pan, volume);
        } else {
            item_data->xD6C = func_800237A8(0x83D60, pan, volume);
        }
    }
}

// Play Item SFX 2
void func_8026AF0C(Item* item_data, enum_t sfxID, u8 pan, u8 volume)
{
    if (sfxID != 0x83D60) {
        if (sfxID != 0x83D61) {
            if (item_data->xD64 != -1) {
                func_800236B8(item_data->xD64);
            }
            item_data->xD64 = func_800237A8(func_800233EC(sfxID), pan, volume);
        } else {
            func_8026B034(item_data);
        }
    }
}

// Play Item SFX 3
void func_8026AFA0(Item* item_data, enum_t sfxID, u8 pan, u8 volume)
{
    if (sfxID != 0x83D60) {
        if (sfxID != 0x83D61) {
            if (item_data->xD68 != -1) {
                func_800236B8(item_data->xD68);
            }
            item_data->xD68 = func_800237A8(func_800233EC(sfxID), pan, volume);
        } else {
            func_8026B074(item_data);
        }
    }
}

// Stop Item SFX
void func_8026B034(Item* item_data)
{
    if (item_data->xD64 != -1) {
        func_800236B8(item_data->xD64);
    }
    item_data->xD64 = -1;
}

// Stop Item SFX 2
void func_8026B074(Item* item_data)
{
    if (item_data->xD68 != -1) {
        func_800236B8(item_data->xD68);
    }
    item_data->xD68 = -1;
}

extern void func_80026510(HSD_GObj*);
extern s32 func_800265C4(HSD_GObj*, s32);

// TODO create enum for SFX IDs
#define SFX_NONE -1

// Stop All Item SFX
void func_8026B0B4(HSD_GObj* item_gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(item_gobj);
    func_80026510(item_gobj);
    if (item_data->xD6C != SFX_NONE) {
        func_800265C4(item_gobj, item_data->xD6C);
        item_data->xD6C = SFX_NONE;
    }
    if (item_data->xD64 != SFX_NONE &&
        func_800265C4(item_gobj, item_data->xD64) == 1)
    {
        if (item_data->xD64 != SFX_NONE) {
            func_800236B8(item_data->xD64);
        }
        item_data->xD64 = SFX_NONE;
    }
    if (item_data->xD68 != SFX_NONE &&
        func_800265C4(item_gobj, item_data->xD68) == 1)
    {
        if (item_data->xD68 != SFX_NONE) {
            func_800236B8(item_data->xD68);
        }
        item_data->xD68 = SFX_NONE;
    }
    if (item_data->xD64 != SFX_NONE) {
        func_800236B8(item_data->xD64);
    }
    item_data->xD64 = SFX_NONE;
    if (item_data->xD68 != SFX_NONE) {
        func_800236B8(item_data->xD68);
    }
    item_data->xD68 = SFX_NONE;
    item_data->xD6C = SFX_NONE;
}

// Check if item is grabbable
BOOL func_8026B1A4(HSD_GObj* item_gobj)
{
    Item* temp_item;

    temp_item = item_gobj->user_data;
    if ((temp_item->xDC8_word.flags.x15 != 0) &&
        (temp_item->xB8_itemLogicTable->xC_callback_OnPickup != NULL))
    {
        return TRUE;
    }
    return FALSE;
}
