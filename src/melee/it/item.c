#include <melee/it/item.h>
#include <common_structs.h>

extern s32 func_8016AE80();

// 0x80266F3C //
// https://decomp.me/scratch/QfPX7 //
s32 func_80266F3C(void)                 // Check if items are enabled //
{
    if (func_8016AE80() != -1)
    {
        return 1;
    }
    return 0;
}

// 0x80266F70 //
// https://decomp.me/scratch/e1TwW //
void func_80266F70(void)                // Check to load ItCo.dat/usd
{
    s32 ItemFreqCheck;
    if (func_8016AE80() != -1)
    {
        ItemFreqCheck = 1;
    }
    else ItemFreqCheck = 0;
    func_8027870C(ItemFreqCheck);
}

// 0x80266FA8 //
// https://decomp.me/scratch/UbSpT //
void func_80266FA8(void)                // ItCo prefunction with 0 
{
    func_8027870C(0);
}

extern HSD_ObjAllocUnkStruct lbl_804A0BE0;
extern HSD_ObjAllocData lbl_804A0C0C;
extern HSD_ObjAllocData lbl_804A0C38;
extern HSD_ObjAllocUnk lbl_804A0C64;
extern HSD_ObjAllocUnk2 lbl_804A0CCC;
extern HSD_ObjAllocUnk3 lbl_804A0E24;
extern HSD_ObjAllocUnk4 lbl_804A0E30;
extern HSD_ObjAllocUnk5 lbl_804A0E50;
extern HSD_ObjAllocUnk6 lbl_804A0E60;
extern s8 lbl_804D6D00;
extern s32 lbl_804D6D08;
extern s32 lbl_804D6D0C;
extern s32 lbl_804D6D10;
extern s32 lbl_804D6D14;
extern ItemCommonData* lbl_804D6D28;

void func_80266FCC(void) // Init item struct? //
{
    HSD_ObjAllocUnkStruct* lbl = &lbl_804A0BE0;

    HSD_ObjAllocInit(&lbl->x0, 0xFCCU, 4U);
    HSD_ObjAllocInit(&lbl->x2C, 0x190U, 4U);
    HSD_ObjAllocInit(&lbl->x58, 0x1D8U, 4U);
    lbl->x84.x0 = 0;
    lbl->x84.x8 = 0;
    lbl->x84.x10 = 0;
    lbl->x84.x18 = 0;
    lbl->x84.x1C_struct.x1C = 0;
    lbl->x84.x24 = 0;
    lbl->x84.x2C = 0;
    lbl->x84.x34 = 0;
    lbl->x84.x3C = 0;
    lbl->x84.x40 = 0;
    lbl->x84.x48 = 0;
    lbl->x84.x50 = 0;
    lbl->x84.x58 = 0;
    lbl->x84.x60 = 0;
    lbl->x84.x4 = lbl_804D6D28->x0;
    lbl->x84.xC = lbl_804D6D28->x4;
    lbl->x84.x14 = lbl_804D6D28->x8;
    lbl->x84.x20 = lbl_804D6D28->xC;
    lbl->x84.x28 = lbl_804D6D28->x10;
    lbl->x84.x30 = lbl_804D6D28->x14;
    lbl->x84.x38 = lbl_804D6D28->x18;
    lbl->x84.x44 = lbl_804D6D28->x1C;
    lbl->x84.x4C = lbl_804D6D28->x24;
    lbl->x84.x54 = lbl_804D6D28->x20;
    lbl->x84.x5C = lbl_804D6D28->x28;
    lbl->x84.x64 = lbl_804D6D28->x148;
    lbl->xEC.x150.bits.b0 = 1;
    lbl->xEC.x14C = 1;
    lbl->xEC.x154 = -1;
    lbl->xEC.x158 = -1;
    lbl->xEC.x15C = 0;
    lbl_804D6D00 = (s8)-1;
    lbl_804D6D14 = 1;
    lbl_804D6D10 = 0;
    lbl_804D6D0C = 0;
    lbl_804D6D08 = 0;
    lbl_804A0E60.x8 = (s16)0;
    lbl_804A0E50.x8 = (s16)0;
    lbl_804A0E30.xC = (s16)0;
    lbl_804A0E60.x0 = (s8)0;
    lbl_804A0E50.x0 = (s8)0;
    lbl_804A0E30.x4 = (s8)0;
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

// 0x80267130 //
// https://decomp.me/scratch/eaaVC //
void func_80267130(HSD_GObj* item_gobj, SpawnItem* spawnItem) // Initialize item coordinates?
{
    Item* item_data;
    HSD_JObj* model;
    f32 temp_f0;
    f32 temp_f31;
    s32 temp_r0;
    s32 temp_r3;
    s32 temp_r4;
    Item* item_data2;
    ItemCommonData* temp_lbl;
    s32 filler[2];

    item_data = item_gobj->user_data;
    model = item_gobj->hsd_obj;
    item_data->x4C_pos = spawnItem->x20_pos_prev;
    temp_f0 = spawnItem->x38_facing_direction;
    item_data->x2C_facing_direction = temp_f0;
    item_data->x30_initial_facing_dir = temp_f0;
    item_data->x518_ownerGObj = spawnItem->x0_parent_gobj;
    if (-1.0f == item_data->x2C_facing_direction)
    {
        temp_r4 = -1;
    }
    else
    {
        temp_r4 = 1;
    }
    func_800436D8(&item_data->x378_itemColl, temp_r4);
    if (item_data->xDC8_word.flags.x19 == 1)
    {
        temp_f31 = (f32)(1.5707963267948966 * (f64)item_data->x2C_facing_direction);
        HSD_JObjSetRotationY(model, temp_f31);
    }
    func_80273500(item_gobj, &spawnItem->x2C_vel);
    item_data->x5CC_currentAnimFrame = (f32)0.0f;
    item_data->x5D0_animFrameSpeed = (f32)1.0f;
    func_802753BC(item_gobj, spawnItem->x3C_damage);
    func_802753DC(item_gobj);
    item_data->itdmg.xC64_reflectGObj = 0;
    item_data->xDCC_flag.b0 = 0;
    item_data->itdmg.xC90_absorbGObj = 0;
    item_data->xD0C = 0;
    func_8026B390(item_gobj);
    item_data->xDC8_word.flags.x13 = 0;
    if ((s32)spawnItem->x48_ground_or_air == 1)
    {
        func_802762BC(item_data);
    }
    else
    {
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
    if (item_data->x518_ownerGObj != 0U)
    {
        func_80225DD8(item_gobj, item_data->x518_ownerGObj);
    }
    else
    {
        func_80225D64(item_gobj, item_data->x518_ownerGObj);
    }
    func_8027B0C4(item_gobj, spawnItem);
    func_80279B64(item_data);
    item_data2 = item_gobj->user_data;
    temp_r0 = item_data2->x14_hold_kind;
    switch (temp_r0)
    {
    case 4:
    case 5:
    case 6:
    case 7:
        temp_r3 = func_8017E068();
        if (temp_r3 >= 0)
        {
            item_data2->itdmg.xC3C = lbl_804D6D28->x80_float[temp_r3];
        }
    }
}

// 0x80267454 //
// https://decomp.me/scratch/OhwTH //
void func_80267454(HSD_GObj* item_gobj) // Remove Camera Box //
{
    Item* item_data;

    item_data = item_gobj->user_data;
    if (((item_data->xDCD_flag.bits.b01) != 0) && (item_data->x520_cameraBox != 0U))
    {
        func_800290D4(item_data->x520_cameraBox);
        item_data->x520_cameraBox = 0U;
        item_data->xDCD_flag.bits.b01 = 0;
    }
}

// 0x802674AC //
// https://decomp.me/scratch/EzEg7 //
void func_802674AC(SpawnItem* spawnItem) // Set Item Hold kind //
{
    s32 ItemID; // Item ID

    ItemID = spawnItem->x8_item_id;
    if (ItemID == 0x12)
    {
        spawnItem->xC_hold_kind = 2;
        return;
    }
    if (ItemID == 0xA0)
    {
        spawnItem->xC_hold_kind = 3;
        return;
    }
    if (ItemID < 0x23)
    {
        spawnItem->xC_hold_kind = 0;
        return;
    }
    if (ItemID < 0x2B)
    {
        spawnItem->xC_hold_kind = 1;
        return;
    }
    if (ItemID < 0x2F)
    {
        spawnItem->xC_hold_kind = 6;
        return;
    }
    if (ItemID < 0x30)
    {
        spawnItem->xC_hold_kind = 7;
        return;
    }
    if (ItemID < 0x9E)
    {
        spawnItem->xC_hold_kind = 8;
        return;
    }
    if (ItemID == 0x9E)
    {
        spawnItem->xC_hold_kind = 0xC;
        return;
    }
    if (ItemID < 0xA0)
    {
        spawnItem->xC_hold_kind = 0xB;
        return;
    }
    if (ItemID < 0xBF)
    {
        spawnItem->xC_hold_kind = 9;
        return;
    }
    if (ItemID < 0xD0)
    {
        spawnItem->xC_hold_kind = 0xA;
        return;
    }
    if (ItemID < 0xEA)
    {
        spawnItem->xC_hold_kind = 4;
        return;
    }
    spawnItem->xC_hold_kind = 5;
}

extern s32 func_8018841C();

// 0x802675A8 //
// https://decomp.me/scratch/90UMw //
void func_802675A8(HSD_GObj* item_gobj)
{
    u32 HoldKind;
    Item* item_data;
    HSD_ObjAllocUnkStruct* unk_struct = &lbl_804A0BE0;

    item_data = item_gobj->user_data;
    HoldKind = item_data->x14_hold_kind;
    switch (HoldKind)
    {
    case 0:
        unk_struct->x84.x0 += -1;
        break;
    case 1:
        unk_struct->x84.x8 += -1;
        break;
    case 2:
        unk_struct->x84.x10 += -1;
        break;
    case 3:
        unk_struct->x84.x58 += -1;
        break;
    case 4:
        unk_struct->x84.x3C += -1;
        break;
    case 5:
        unk_struct->x84.x40 += -1;
        break;
    case 6:
        unk_struct->x84.x2C += -1;
        break;
    case 7:
        unk_struct->x84.x34 += -1;
        break;
    case 8:
        unk_struct->x84.x18 += -1;
        break;
    case 9:
        unk_struct->x84.x1C_struct.x1C += -1;
        break;
    case 10:
        unk_struct->x84.x24 += -1;
        break;
    case 11:
        unk_struct->x84.x48 += -1;
        break;
    case 12:
        unk_struct->x84.x50 += -1;
        break;
    }
    if ((func_8018841C() != 0) && ((s32)item_data->x18 == 1))
    {
        unk_struct->x84.x60 += -1;
    }
}

extern void func_80274EE8(u32);

// 0x802676F4 //
// https://decomp.me/scratch/hLqWo //
void func_802676F4(HSD_GObj* item_gobj) // 
{
    u32 HoldKind;
    u32 temp_r3;
    Item* item_data;
    HSD_ObjAllocUnkStruct* unk_label = &lbl_804A0BE0;

    item_data = item_gobj->user_data;
    HoldKind = item_data->x14_hold_kind;
    switch (HoldKind)
    {
    case 0:
        unk_label->x84.x0 += 1;
        if ((s32)item_data->x10_item_kind == 0x22)
        {
            unk_label->x84.x1C_struct.x1C += 1;
        }
        break;
    case 1:
        unk_label->x84.x8 += 1;
        break;
    case 2:
        temp_r3 = unk_label->x84.x10;
        unk_label->x84.x10 = temp_r3 + 1;
        func_80274EE8(temp_r3);
        break;
    case 3:
        unk_label->x84.x58 += 1;
        break;
    case 4:
        unk_label->x84.x3C += 1;
        break;
    case 5:
        unk_label->x84.x40 += 1;
        break;
    case 6:
        unk_label->x84.x2C += 1;
        break;
    case 7:
        unk_label->x84.x34 += 1;
        break;
    case 8:
        unk_label->x84.x18 += 1;
        break;
    case 10:
        unk_label->x84.x24 += 1;
        break;
    case 11:
        unk_label->x84.x48 += 1;
        break;
    case 12:
        unk_label->x84.x50 += 1;
        break;
    }
    if ((func_8018841C() != 0) && ((s32)item_data->x18 == 1))
    {
        unk_label->x84.x60 += 1;
    }
}

// 0x8026784C //
// https://decomp.me/scratch/0VC6C //
s32 func_8026784C(s32 dropItem, s32 unused) // Decide drop item //
{
    HSD_ObjAllocUnkStruct* unk_label = &lbl_804A0BE0;
    u32 temp_r3;
    x1C_struct* temp_r4;
    u32* new_var;
    s32 phi_r6 = 0;
    switch (dropItem)
    {
    case 0:
        if (((s32)unk_label->x84.x0) >= ((s32)unk_label->x84.x4))
        {
            phi_r6 = 1;
        }
        goto block_default;

    case 1:
        if (((s32)unk_label->x84.x8) >= ((s32)unk_label->x84.xC))
        {
            phi_r6 = 1;
        }
        goto block_default;

    case 2:
        if (((s32)unk_label->x84.x10) >= ((s32)unk_label->x84.x14))
        {
            phi_r6 = 1;
        }
        goto block_default;

    case 3:
        if (((s32)unk_label->x84.x58) >= ((s32)unk_label->x84.x5C))
        {
            phi_r6 = 1;
        }
        goto block_default;

    case 5:
        if (((s32)unk_label->x84.x40) >= ((s32)unk_label->x84.x44))
        {
            phi_r6 = 1;
        }
        goto block_default;

    case 7:
        if (((s32)unk_label->x84.x34) >= ((s32)unk_label->x84.x38))
        {
            phi_r6 = 1;
        }
        goto block_default;

    case 9:
        temp_r4 = &unk_label->x84.x1C_struct;
        temp_r3 = *(new_var = &unk_label->x84.x1C_struct.x1C);
        if (((s32)temp_r3) > ((s32)unk_label->x84.x20))
        {
            temp_r4->x1C = temp_r3 - 1;
            phi_r6 = 1;
        }
        goto block_default;

    case 10:
        if (((s32)unk_label->x84.x24) >= ((s32)unk_label->x84.x28))
        {
            phi_r6 = 1;
        }
        goto block_default;

    case 11:
        if (((s32)unk_label->x84.x48) >= ((s32)unk_label->x84.x4C))
        {
            phi_r6 = 1;
        }
        goto block_default;

    case 12:
        if (((s32)unk_label->x84.x50) >= ((s32)unk_label->x84.x54))
        {
            phi_r6 = 1;
        }
    block_default:
    default:
        return phi_r6;
    }
}

extern CommonItemArticles* lbl_804D6D24;
extern UnkItemArticles* lbl_804D6D38;
extern UnkItemArticles2* lbl_804D6D30;
extern UnkItemArticles3 lbl_804A0F60[];

extern struct ItemLogicTable lbl_803F14C4[];

extern struct ItemLogicTable lbl_803F3100[];

extern struct ItemLogicTable lbl_803F23CC[];

extern struct ItemLogicTable lbl_803F4D20[];

// 0x80267978 //
// https://decomp.me/scratch/LnIJJ //
void func_80267978(HSD_GObj* item_gobj) // Store Item Pointers //
{
    s32 ItemID;
    s32 ItemID2;
    unsigned int new_var;
    Item* item_data;
    item_data = item_gobj->user_data;
    ItemID = item_data->x10_item_kind;
    if (ItemID < It_Kind_Kuriboh)
    {
        item_data->xC4_article_data = &(*lbl_804D6D24->article_ptr[ItemID]);
        item_data->xB8_itemLogicTable = &lbl_803F14C4[item_data->x10_item_kind];
        goto block_end;
    }
    if (ItemID < Pokemon_Tosakinto)
    {
        ItemID -= It_Kind_Kuriboh;
        new_var = ItemID;
        ItemID2 = new_var;
        item_data->xC4_article_data = &(*lbl_804D6D38->unkptr[new_var]);
        item_data->xB8_itemLogicTable = &lbl_803F3100[new_var];
        goto block_end;
    }
    if (ItemID < It_Kind_Old_Kuri)
    {
        ItemID -= Pokemon_Tosakinto;
        new_var = ItemID;
        ItemID2 = new_var;
        item_data->xC4_article_data = &(*lbl_804D6D30->unkptr[new_var]);
        item_data->xB8_itemLogicTable = &lbl_803F23CC[new_var];
        goto block_end;
    }
    ItemID -= It_Kind_Old_Kuri;
    item_data->xC4_article_data = &(*lbl_804A0F60->unkptr[ItemID]);
    item_data->xB8_itemLogicTable = &lbl_803F4D20[ItemID];
    if (item_data->xC4_article_data == NULL)
    {
        OSReport("not found zako model data! check ground dat file!\n");
        __assert("item.c", 0x2AEU, "0");
    }
block_end:
    item_data->xBC_itemStateContainer = item_data->xB8_itemLogicTable->x0_itemStatePtr;
}

extern s32 func_80086960(HSD_GObj*);
extern u8 func_80086EB4(HSD_GObj*);
extern u32 func_80225B20();

// Thanks to Altafen for matching the bitshifts! //
// 0x80267AA8 //
// https://decomp.me/scratch/eitPf //
void func_80267AA8(HSD_GObj* item_gobj, SpawnItem* spawnItem) // Initialize item variables //
{
    Item* item_data;
    ItemAttr* item_attr;
    u32 temp_r4;
    u32 temp_r4_2;
    u8 temp_r5;

    item_data = item_gobj->user_data;
    item_data->x10_item_kind = spawnItem->x8_item_id;
    item_data->x14_hold_kind = spawnItem->xC_hold_kind;
    item_data->x18 = spawnItem->x10;
    temp_r4 = lbl_804D6D10;
    lbl_804D6D10 = temp_r4 + 1;
    item_data->x1C = temp_r4;
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
    temp_r4_2 = lbl_804D6D28->x30;
    func_80275158(item_gobj, temp_r4_2);
    item_data->xDD0_flag.bits.b3 = 0;
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
    item_data->xD60 = 4;
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
    item_data->xD09 = (s8)0;
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
    if (func_80086960(spawnItem->x0_parent_gobj) != 0)
    {
        item_data->xDC8_word.flags.x1 = 0;
    }
    else
    {
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
    if (func_80225B20() != 0U)
    {
        item_data->xDAA_flag.bits.b4 = 1;
    }
    if (spawnItem->x0_parent_gobj == NULL)
    {
        item_data->x20_team_id = 0xFF;
        return;
    }
    if (func_80086960(spawnItem->x0_parent_gobj) != 0)
    {
        item_data->x20_team_id = func_80086EB4(spawnItem->x0_parent_gobj);
        return;
    }
    if (func_80272D1C(spawnItem->x0_parent_gobj) != 0)
    {
        item_data->x20_team_id = func_8026B7B0(spawnItem->x0_parent_gobj);
        return;
    }
    item_data->x20_team_id = 0xFF;
}

extern HSD_JObj* HSD_JObjAlloc();                              /* extern */
extern void PSMTXIdentity(Mtx);                               /* extern */
extern u8 lbl_804D7849;

// 0x802680CC //
// https://decomp.me/scratch/hnkV9 //
void func_802680CC(HSD_GObj* item_gobj) // Setup Item JObj //
{
    Item* item_data;
    HSD_JObj* jobj;
    HSD_Joint* joint;

    item_data = item_gobj->user_data;
    joint = item_data->xC8_joint;
    if (joint != NULL) 
    {
        jobj = HSD_JObjLoadJoint(item_data->xC8_joint);
        func_80390A70(item_gobj, lbl_804D7849, jobj);
        return;
    }
    jobj = HSD_JObjAlloc();
    PSMTXIdentity(jobj->mtx);
    jobj->scl = 0;
    func_80390A70(item_gobj, lbl_804D7849, jobj);
}

extern HSD_DObj* HSD_JObjGetDObj(HSD_JObj*);
extern void* lbl_803F1F90[];

// 0x8026814C //
// https://decomp.me/scratch/abHa0 //
void func_8026814C(HSD_GObj* item_gobj) // Setup item render objects? //
{
    s32 filler[4];
    HSD_MObj* temp_r0;
    HSD_DObj* var_r0;
    HSD_JObj* var_r0_2;
    HSD_JObj* var_r30;
    HSD_DObj* var_r29;
    HSD_JObj* var_r3;

    var_r30 = item_gobj->hsd_obj;
    while (var_r30 != NULL)
    {
        var_r29 = HSD_JObjGetDObj(var_r30);
    loop_2:
        if (var_r29 != NULL)
        {
            temp_r0 = var_r29->mobj;
            if (temp_r0 != NULL)
            {
                hsdChangeClass(temp_r0, &lbl_803F1F90);
            }
            var_r29 = var_r0 = (var_r29 != NULL) ? var_r29->next : NULL;
            goto loop_2;
        }
        if (var_r30 == NULL)
        {
            var_r0_2 = NULL;
        }
        else
        {
            var_r0_2 = var_r30->child;
        }
        if (var_r0_2 != NULL)
        {
            var_r30 = var_r0_2 = (var_r30 == NULL) ? NULL : var_r30->child;
        }
        else
        {
            var_r0_2 = (var_r30 == NULL) ? NULL : var_r30->next;
            if (var_r0_2 != NULL)
            {
                var_r30 = var_r0_2 = (var_r30 == NULL) ? NULL : var_r30->next;
            }
            else
            {
            loop_25:
                var_r0_2 = (var_r30 == NULL) ? NULL : var_r30->parent;
                if (var_r0_2 == NULL)
                {
                    var_r30 = NULL;
                }
                else
                {
                    var_r3 = (var_r30 == NULL) ? NULL : var_r30->parent;
                    var_r0_2 = (var_r3 == NULL) ? NULL : var_r3->next;
                    if (var_r0_2 != NULL)
                    {
                        var_r3 = (var_r30 == NULL) ? NULL : var_r30->parent;
                        var_r30 = var_r0_2 = (var_r3 == NULL) ? NULL : var_r3->next;
                    }
                    else
                    {
                        var_r30 = var_r0_2 = (var_r30 == NULL) ? NULL : var_r30->parent;
                        goto loop_25;
                    }
                }
            }
        }
    }
}

// 0x802682F0 //
// https://decomp.me/scratch/Rs4HS //
s32 func_802682F0(HSD_GObj* item_gobj) // Initialize item bones - needs some serious cleaning //
{
    s32 unused;
    s32 var_r4;
    Item* item_data;
    HSD_JObj* var_r0;
    HSD_JObj* var_r3;
    HSD_JObj* var_r3_2;
    HSD_JObj* var_r5;

    item_data = item_gobj->user_data;
    if (item_data->xC4_article_data->x10_modelDesc->x4_bone_count != 0U)
    {
        item_data->xBBC_dynamicBoneTable = HSD_ObjAlloc(&lbl_804A0C0C);
        if (item_data->xBBC_dynamicBoneTable == NULL)
        {
            return FALSE;
        }
        var_r5 = item_gobj->hsd_obj;
        var_r4 = 0;
        while (var_r5 != NULL)
        {
            (item_data->xBBC_dynamicBoneTable->x0_jobj[var_r4]) = var_r5;
            var_r4 += 1;
            var_r0 = (var_r5 == NULL) ? NULL : var_r5->child;
            if (var_r0 != NULL)
            {
                var_r5 = var_r0 = (var_r5 == NULL) ? NULL : var_r5->child;
            }
            else
            {
                var_r0 = (var_r5 == NULL) ? NULL : var_r5->next;
                if (var_r0 != NULL)
                {
                    var_r5 = var_r0 = (var_r5 == NULL) ? NULL : var_r5->next;
                }
                else
                {
                loop_20:
                    var_r0 = (var_r5 == NULL) ? NULL : var_r5->parent;
                    if (var_r0 == NULL)
                    {
                        var_r5 = NULL;
                    }
                    else
                    {
                        var_r3 = (var_r5 == NULL) ? NULL : var_r5->parent;
                        var_r0 = (var_r3 == NULL) ? NULL : var_r3->next;
                        if (var_r0 != NULL)
                        {
                            var_r3_2 = (var_r5 == NULL) ? NULL : var_r5->parent;
                            var_r5 = var_r0 = (var_r3_2 == NULL) ? NULL : var_r3_2->next;
                        }
                        else
                        {
                            var_r5 = var_r0 = (var_r5 == NULL) ? NULL : var_r5->parent;
                            goto loop_20;
                        }
                    }
                }
            }
        }
        goto block_46;
    }
    item_data->xBBC_dynamicBoneTable = 0;
block_46:
    return 1;
}

// 0x8026849C //
// https://decomp.me/scratch/Ayb2X //
void func_8026849C(HSD_GObj* item_gobj) // Set item model scale //
{
    s32 filler;
    Vec3 sp14;
    s32 filler2;
    Item* item_data;
    HSD_JObj* temp_jobj;
    f32 temp_f0;

    temp_jobj = item_gobj->hsd_obj;
    item_data = item_gobj->user_data;
    temp_f0 = item_data->x38_scale;
    sp14.z = temp_f0;
    sp14.y = temp_f0;
    sp14.x = temp_f0;
    HSD_JObjSetScale(temp_jobj, &sp14);
}

extern void func_8000FD48(HSD_JObj*, void*, s32);
extern void func_80011710(void*, void*);

// 0x80268560 //
// https://decomp.me/scratch/d3ZmY //
void func_80268560(HSD_GObj* item_gobj) // Setup item dynamic bones //
{
    s32 i;
    Item* item_data;
    HSD_JObj* temp_r26;
    Article* article_data;
    ItemDynamics* temp_dynamics;
    ItemDynamicsDesc* temp_r5;
    ItemDynamics* temp_r5_2;

    item_data = item_gobj->user_data;
    article_data = item_data->xC4_article_data;
    temp_dynamics = article_data->x14_dynamics;
    if (temp_dynamics == NULL)
    {
        item_data->x374_dynamicBonesNum = 0;
        item_data->xB68 = (s8)0;
        return;
    }
    item_data->x374_dynamicBonesNum = (s32)temp_dynamics->x0_dynamics_num;
    for (i = 0; i < article_data->x14_dynamics->x0_dynamics_num; i++)
    {
        temp_r5 = &article_data->x14_dynamics->x4_dynamicsDesc[i];
        temp_r26 = (item_data->xBBC_dynamicBoneTable->x0_jobj[temp_r5->x0_boneID]);
        func_8000FD48(temp_r26, &item_data->xD4_dynamicBones[i].x8_dynamicBones, temp_r5->x8_num);
        item_data->xD4_dynamicBones[i].x4_root_jobj = temp_r26;
        item_data->xD4_dynamicBones[i].x0_apply_phys_num = 0;
        temp_r5_2 = article_data->x14_dynamics;
        func_80011710(&temp_r5_2->x4_dynamicsDesc[i].x4_params, &item_data->xD4_dynamicBones[i].x8_dynamicBones);
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

// 0x8026862C //
// https://decomp.me/scratch/6h8Z5 //
HSD_GObj* func_8026862C(SpawnItem* spawnItem) // Create Item //
{
    Vec3 sp2C;
    s32 filler[5];
    HSD_GObj* temp_r3;
    HSD_JObj* temp_r29;
    HSD_Joint* temp_joint;
    f32 temp_f0;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r4;
    u32 temp_r5;
    u32 temp_r0_3;
    HSD_JObj* temp_jobj;
    Item* item_data;
    Item* item_data2;
    Item* item_data3;
    void* temp_r3_2;
    CameraBox* cam_box;

    if (func_8026784C(spawnItem->xC_hold_kind, spawnItem->x8_item_id) != 0)
    {
        return NULL;
    }
    temp_r3 = func_803901F0(6, 9, 0);
    if (temp_r3 == NULL)
    {
        return NULL;
    }
    temp_r4 = spawnItem->x8_item_id;
    if (temp_r4 < It_Kind_Kuriboh) // Check if item is a common item (IDs 0 through 42) //
    {
        GObj_SetupGXLink(temp_r3, lbl_803F1418[temp_r4].x0_renderFunc, 6U, 0U);
    }
    else if (temp_r4 < Pokemon_Tosakinto) // Check if item is common item- or character-related? //
    {
        temp_r4 -= It_Kind_Kuriboh;
        GObj_SetupGXLink(temp_r3, lbl_803F2F28[temp_r4].x0_renderFunc, 6U, 0U);
    }
    else if (temp_r4 < It_Kind_Old_Kuri) // Check if item is a Pokémon //
    {
        temp_r4 -= Pokemon_Tosakinto;
        GObj_SetupGXLink(temp_r3, lbl_803F2310[temp_r4].x0_renderFunc, 6U, 0U);
    }
    else
    {
        temp_r4 -= It_Kind_Old_Kuri; // Otherwise item is a stage item //
        GObj_SetupGXLink(temp_r3, lbl_803F4CA8[temp_r4].x0_renderFunc, 6U, 0U);
    }
    temp_r3_2 = HSD_ObjAlloc((HSD_ObjAllocData*)(&lbl_804A0BE0));
    if (temp_r3_2 == NULL)
    {
        func_80390228(temp_r3);
        return 0;
    }
    GObj_InitUserData(temp_r3, 6U, lbl_8026AE10, temp_r3_2);
    func_80267AA8(temp_r3, spawnItem);
    item_data = temp_r3->user_data;
    temp_joint = item_data->xC8_joint;
    if (temp_joint != NULL)
    {
        temp_r29 = HSD_JObjLoadJoint(item_data->xC8_joint);
        func_80390A70(temp_r3, lbl_804D7849, temp_r29);
    }
    else
    {
        temp_r29 = HSD_JObjAlloc();
        PSMTXIdentity(temp_r29->mtx);
        temp_r29->scl = 0;
        func_80390A70(temp_r3, lbl_804D7849, temp_r29);
    }
    if (func_802682F0(temp_r3) != FALSE)
    {
        func_8026814C(temp_r3);
        temp_jobj = temp_r3->hsd_obj;
        temp_jobj == 0;
        item_data = temp_r3->user_data;
        temp_f0 = item_data->x38_scale;
        sp2C.z = temp_f0;
        sp2C.y = temp_f0;
        sp2C.x = temp_f0;
        HSD_JObjSetScale(temp_jobj, &sp2C);
        func_8027163C(temp_r3);
        func_80268560(temp_r3);
        func_8038FD54(temp_r3, lbl_802693E4, 0);
        func_8038FD54(temp_r3, lbl_80269528, 1);
        func_8038FD54(temp_r3, func_802697D4, 4);
        func_8038FD54(temp_r3, func_80269978, 5);
        func_8038FD54(temp_r3, lbl_80269A9C, 9);
        func_8038FD54(temp_r3, lbl_80269B60, 0xB);
        func_8038FD54(temp_r3, lbl_80269BE4, 0xC);
        func_8038FD54(temp_r3, lbl_80269C5C, 0xD);
        func_8038FD54(temp_r3, lbl_8026A294, 0xE);
        func_8038FD54(temp_r3, lbl_8026A788, 0x10);
        func_80267130(temp_r3, spawnItem);
        func_8026A810(temp_r3);
        item_data = temp_r3->user_data;
        temp_r0 = item_data->x14_hold_kind;
        switch (temp_r0)
        {
        case 0:
        case 6:
            if (((s32)item_data->xD0C) == 2)
            {
                item_data->xDD0_flag.bits.b7 = 1;
            }
            temp_r5 = lbl_804D6D28->x2C;
            item_data->xD40 = (f32)temp_r5;
            item_data->xDD0_flag.bits.b6 = 1;
            func_802756D0(temp_r3);
            func_80279B88(item_data, 3, 0);
            break;

        default:
            item_data->xD40 = 0.0f;
            item_data->xDD0_flag.bits.b6 = 0;
        }
        func_802676F4(temp_r3);
        item_data2 = temp_r3->user_data;
        temp_r0_2 = item_data2->x10_item_kind;
        if ((temp_r0_2 >= It_Kind_Mario_Fire) && (temp_r0_2 < It_Kind_Unk4) && (func_80086960(item_data2->x518_ownerGObj) != FALSE)) // Check if item is a character item + owner != NULL
        {
            item_data2->xDC8_word.flags.xE = 1;
            item_data2->x378_itemColl.x19C = func_800872A4(item_data2->x518_ownerGObj);
            func_8008702C(item_data2->x378_itemColl.x19C);
        }
        item_data3 = temp_r3->user_data;
        temp_r0_3 = item_data3->xDCD_flag.bits.b01;
        if (temp_r0_3 != 0)
        {
            if (temp_r0_3 == 1)
            {
                item_data3->x520_cameraBox = func_80029044(0);
            }
            else
            {
                item_data3->x520_cameraBox = func_80029044(2);
            }
            cam_box = item_data3->x520_cameraBox;
            if (cam_box != 0)
            {
                cam_box->x40.x = (f32)lbl_804D6D28->x14C;
                cam_box->x40.y = (f32)lbl_804D6D28->x150;
                cam_box->x48.x = (f32)lbl_804D6D28->x154;
                cam_box->x48.y = (f32)lbl_804D6D28->x158;
            }
        }
        goto block_returnGObj;
    }
    func_80390228(temp_r3);
    return 0;
block_returnGObj:
    !spawnItem;
    return temp_r3;
}

// 0x80268B18 //
// https://decomp.me/scratch/YyUEI //
void func_80268B18(SpawnItem* spawnItem) // Item spawn prefunction - spawn airborne //
{
    spawnItem->x48_ground_or_air = GA_Air;
    spawnItem->x10 = 0;
    func_802674AC(spawnItem);
    func_8026862C(spawnItem);
}

// 0x80268B5C //
// https://decomp.me/scratch/cN7Fn //
void func_80268B5C(SpawnItem* spawnItem) // Item spawn prefunction - spawn grounded //
{
    spawnItem->x48_ground_or_air = GA_Ground;
    spawnItem->x10 = 0;
    func_802674AC(spawnItem);
    func_8026862C(spawnItem);
}

// 0x80268B9C //
// https://decomp.me/scratch/V7AgZ //
void func_80268B9C(SpawnItem* spawnItem) // Item spawn prefunction - spawn grounded and toggle unknown true //
{
    spawnItem->x48_ground_or_air = GA_Ground;
    spawnItem->x10 = 1;
    func_802674AC(spawnItem);
    func_8026862C(spawnItem);
}

extern void HSD_JObjAddAnim(void*, void*, void*, void*);

// 0x80268BE0 //
// https://decomp.me/scratch/gL9Td //
void func_80268BE0(HSD_JObj* item_jobj, HSD_AnimJoint* anim_joint, HSD_MatAnimJoint* matanim_joint, ItemState_ParamStruct* arg3, Item* item_data) // Adds AObjs to item model //
{

    void* functionArg1;
    void* functionArg2;
    void* functionArg3;

    s32 temp_r0;

    if (item_jobj != NULL)
    {
        if (anim_joint != NULL)
        {
            for (temp_r0 = 0; temp_r0 < item_data->x374_dynamicBonesNum; temp_r0++)
                if (item_jobj == item_data->xD4_dynamicBones[temp_r0].x4_root_jobj)
                {
                    if (anim_joint->next != NULL)
                    {
                        functionArg1 = NULL;
                        functionArg2 = NULL;
                        functionArg3 = NULL;
                        if (anim_joint != NULL)
                        {
                            functionArg1 = anim_joint->next;
                        }
                        if (matanim_joint != NULL)
                        {
                            functionArg2 = matanim_joint->next;
                        }
                        if (arg3 != NULL)
                        {
                            functionArg3 = arg3->x4_unk;
                        }
                        func_80268BE0(item_jobj->next, functionArg1, functionArg2, functionArg3, item_data);
                    }
                    return;
                }
        }
        HSD_JObjAddAnim(item_jobj, anim_joint, matanim_joint, arg3);
        if (item_jobj->child != NULL)
        {
            functionArg1 = NULL;
            functionArg2 = NULL;
            functionArg3 = NULL;
            if (anim_joint != NULL)
            {
                functionArg1 = anim_joint->child;
            }
            if (matanim_joint != NULL)
            {
                functionArg2 = matanim_joint->child;
            }
            if (arg3 != NULL)
            {
                functionArg3 = arg3->x0_unk;
            }
            func_80268BE0(item_jobj->child, functionArg1, functionArg2, functionArg3, item_data);
        }
        if (item_jobj->next != NULL)
        {
            functionArg1 = NULL;
            functionArg2 = NULL;
            functionArg3 = NULL;
            if (anim_joint != NULL)
            {
                functionArg1 = anim_joint->next;
            }
            if (matanim_joint != NULL)
            {
                functionArg2 = matanim_joint->next;
            }
            if (arg3 != NULL)
            {
                functionArg3 = arg3->x4_unk;
            }
            func_80268BE0(item_jobj->next, functionArg1, functionArg2, functionArg3, item_data);
        }
    }
}

extern void func_8000B804(HSD_JObj*, HSD_Joint*);
extern void func_8000BA0C(HSD_JObj*, f32);
extern void HSD_JObjRemoveAnimAll(HSD_JObj*);

// 0x80268D34 //
// https://decomp.me/scratch/BiAE9 //
void func_80268D34(HSD_GObj* item_gobj, struct ItemStateDesc* itemStateDesc) // Unk Item AObj-related function //
{
    HSD_JObj* item_jobj;
    Item* item_data;
    void* bonestruct_arg;
    HSD_Joint* temp_joint;
    s32 filler[2];

    item_jobj = item_gobj->hsd_obj;
    item_data = item_gobj->user_data;
    HSD_JObjRemoveAnimAll(item_jobj);
    temp_joint = item_data->xC8_joint;
    if (temp_joint != 0)
    {
        if (item_jobj == NULL)
        {
            bonestruct_arg = NULL;
        }
        else bonestruct_arg = item_jobj->child;
        func_8000B804(bonestruct_arg, temp_joint->child);
    }
    func_80268BE0(item_jobj, itemStateDesc->x0_anim_joint, itemStateDesc->x4_matanim_joint, itemStateDesc->x8_parameters, item_data);
    func_8000BA0C(item_jobj, item_data->x5D0_animFrameSpeed);
    HSD_JObjReqAnimAll(item_jobj, 0.0f);
}

// 0x80268DD4 //
// https://decomp.me/scratch/1G591 //
void func_80268DD4(HSD_GObj* item_gobj, f32 arg8) // Advance item animation? //
{
    HSD_JObj* item_jobj;
    Item* item_data;
    s32 filler[2];

    item_data = item_gobj->user_data;
    item_jobj = item_gobj->hsd_obj;
    func_8000BA0C(item_jobj, item_data->x5D0_animFrameSpeed);
    HSD_JObjReqAnimAll(item_jobj, arg8);
    HSD_JObjAnimAll(item_jobj);
    item_data->x5CC_currentAnimFrame = func_8000BDB4(item_jobj);
}

// 0x80268E40 //
// https://decomp.me/scratch/a3Je2 //
void func_80268E40(Item* item_data, struct ItemStateDesc* itemStateDesc) // Copy item script //
{
    item_data->x52C_item_script = itemStateDesc->xC_script;
    item_data->x530 = 0;
    item_data->x524 = 0.0f;
}

extern s8 lbl_803F11B0;
extern s8 lbl_803F11D8;
extern s8 lbl_804D5148;
extern s8 lbl_804D5150;
extern struct r13_ColAnimStruct* lbl_804D6D04;
extern f64 lbl_804DC630;
extern f32 lbl_804DC638;
extern f32 lbl_804DC63C;

inline void HSD_JObjSetFacingDirItem(HSD_JObj* item_jobj2, Item* item_data)
{
    HSD_JObjSetRotationY(item_jobj2, (M_PI / 2) * item_data->x2C_facing_direction);
}

inline void HSD_JObjSetScaleItem(Item* item_data3, HSD_JObj* item_jobj1_2, Vec3* sp4C)
{
    item_data3->x38_scale = (f32)item_data3->xCC_item_attr->x60_scale;
    sp4C->z = item_data3->x38_scale;
    sp4C->y = item_data3->x38_scale;
    sp4C->x = item_data3->x38_scale;
    HSD_JObjSetScale(item_jobj1_2, sp4C);
}

inline void HSD_JObjSetScaleItem2(Item* item_data4, HSD_JObj* item_jobj1_4, Vec3* sp40)
{
    sp40->z = item_data4->x38_scale;
    sp40->y = item_data4->x38_scale;
    sp40->x = item_data4->x38_scale;
    HSD_JObjSetScale(item_jobj1_4, sp40);
}

inline HSD_JObj* GetItemJObj(HSD_GObj* item_gobj)
{
    return item_gobj->hsd_obj;
}

// 0x80268E5C //
// https://decomp.me/scratch/cSrfX
void func_80268E5C(HSD_GObj* item_gobj, s32 itemStateID, s32 itemStateFlags) // Item State Change //
{
    Vec3 sp4C;
    Vec3 sp40;
    s32 filler;
    struct ItemStateTable* temp_r30;
    struct ItemStateDesc* temp_r29;
    HSD_JObj* item_jobj1_3;
    HSD_JObj* item_jobj1_2;
    void* new_var;
    void* new_var2;
    void* new_var3;
    Item* item_data2;
    Item* item_data3;
    Item* item_data4;
    HSD_JObj* item_jobj2;
    Item* item_data;
    ItemAttr* item_attr;
    ItemAttr* item_attr2;
    ItemAttr* item_attr3;
    HSD_JObj* boneCopyArg;
    HSD_JObj* new_var4;
    HSD_Joint* boneCopyArg2;
    struct ItemStateDesc* temp_r23;
    s32 temp_r0;

    item_jobj2 = item_gobj->hsd_obj;
    item_data = item_gobj->user_data;
    item_data->x24_item_state_index = itemStateID;
    item_data->xDC8_word.flags.x14 = 0;
    HSD_JObjSetTranslate(item_gobj->hsd_obj, &item_data->x4C_pos);
    func_80067624(item_gobj, &item_data->xBC0);
    if (item_data->xDC8_word.flags.x2 == 1)
    {
        func_8026BDCC(item_gobj);
        func_80274EF8(item_gobj);
    }
    if ((itemStateFlags & ITEM_MODEL_UPDATE) != FALSE)
    {
        func_80274740(item_gobj);
    }
    if (((itemStateFlags & ITEM_COLANIM_PRESERVE) == FALSE) && ((lbl_804D6D04[item_data->x548_colorOverlay.x28_colanim].x5_unk != 0)))
    {
        func_80279BBC(item_data);
    }
    if ((itemStateFlags & ITEM_SFX_PRESERVE) == FALSE)
    {
        func_8026B074(item_data);
    }
    if (item_data->xDC8_word.flags.x19 == 1)
    {
        HSD_JObjSetFacingDirItem(item_jobj2, item_data);
    }
    if ((itemStateFlags & ITEM_DROP_UPDATE) != FALSE)
    {
        item_data->itdmg.xC40 = (f32)item_data->itdmg.xC44;
    }
    else
    {
        item_data->itdmg.xC40 = 1.0f;
    }
    if (((itemStateFlags & ITEM_HIT_PRESERVE) == FALSE) && (item_data->xDC8_word.flags.x16 != 0))
    {
        func_802725D4(item_gobj);
    }

    item_data->itdmg.xCC8_knockback = 0.0f;
    temp_r30 = (new_var = &item_data->xBC_itemStateContainer->stateTable[itemStateID]);
    item_data->x28_item_anim_index = temp_r30->x0_state_id;
    item_data->x5CC_currentAnimFrame = 0.0f;
    temp_r0 = item_data->x28_item_anim_index;
    if (temp_r0 != -1)
    {
        item_data->xD0_itemStateDesc = (temp_r23 = (temp_r29 = (new_var2 = &item_data->xC4_article_data->xC_itemStates->x0_itemStateDesc[temp_r0])));
        temp_r23 = (new_var3 = item_data->xD0_itemStateDesc);
        if (temp_r23 != NULL && (itemStateFlags & ITEM_ANIM_UPDATE)) {
            item_jobj1_2 = GetItemJObj(item_gobj);
            item_data2 = GetItemData(item_gobj);
            HSD_JObjRemoveAnimAll(item_jobj1_2);
            new_var4 = item_jobj1_2;
            boneCopyArg2 = item_data2->xC8_joint;
            if (boneCopyArg2 != NULL)
            {
                if (item_jobj1_2 == NULL) {
                    boneCopyArg = NULL;
                } else {
                    boneCopyArg = new_var4->child;
                }
                func_8000B804(boneCopyArg, boneCopyArg2->child);
            }
            func_80268BE0(new_var4, temp_r23->x0_anim_joint, temp_r23->x4_matanim_joint, temp_r23->x8_parameters, item_data2);
            func_8000BA0C(new_var4, item_data2->x5D0_animFrameSpeed);
            HSD_JObjReqAnimAll(new_var4, 0.0f);
            if (itemStateFlags & 0x80) {
                item_jobj1_2 = item_gobj->hsd_obj;
                item_data3 = GetItemData(item_gobj);
                HSD_JObjSetScaleItem(item_data3, item_jobj1_2, &sp4C);
                item_attr = item_data3->xCC_item_attr;
                item_data3->xBCC_unk = item_attr->x30_unk;
                item_data3->xBD4_grabRange = item_attr->x38_grab_range;
                item_attr2 = item_data3->xCC_item_attr;
                item_data3->xBEC = item_attr2->x20;
                item_attr3 = item_data3->xCC_item_attr;
                item_data3->xBDC = item_attr3->x20;
            } else {
                item_data4 = item_gobj->user_data;
                item_jobj1_3 = GetItemJObj(item_gobj);
                HSD_JObjSetScaleItem2(item_data4, item_gobj->hsd_obj, &sp40);
            }
            item_data->x52C_item_script = temp_r29->xC_script;
            item_data->x530 = 0U;
            item_data->x524 = 0.0f;
        } else if (temp_r23 != NULL && (itemStateFlags & ITEM_CMD_UPDATE)) {
            item_data->x52C_item_script = temp_r29->xC_script;
            item_data->x530 = 0U;
            item_data->x524 = 0.0f;
        }
        HSD_JObjAnimAll(item_jobj2);
        func_80279BE0(item_gobj);
        func_802799E4(item_gobj);
    }
    else
    {
        HSD_JObjRemoveAnimAll(item_jobj2);
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
    item_data->xD09 = (s8)0;
    func_802714C0(item_gobj);
}

// 0x802693E4 //
// https://decomp.me/scratch/v3rQP //
void lbl_802693E4(HSD_GObj* item_gobj) // Item Think - Hitlag //
{
    f32 hitlagFrames;
    Item* item_data;

    item_data = item_gobj->user_data;
    if (item_data->xDC8_word.flags.x5 != 0)
    {
        func_8026A0A0(item_gobj);
        item_data->xDC8_word.flags.x5 = 0;
    }
    if (item_data->xDC8_word.flags.x6 != 0)
    {
        func_8026A0FC(item_gobj);
        item_data->xDC8_word.flags.x6 = 0;
    }
    hitlagFrames = item_data->itdmg.xCBC_hitlagFrames;
    if (hitlagFrames > 0.0f)
    {
        item_data->itdmg.xCBC_hitlagFrames = (f32)(hitlagFrames - 1.0f);
        if (item_data->itdmg.xCBC_hitlagFrames <= 0.0f)
        {
            item_data->itdmg.xCBC_hitlagFrames = 0.0f;
            item_data->xDC8_word.flags.xB = 0;
            item_data->xDC8_word.flags.xA = 0;
            if ((item_data->xDC8_word.flags.x8 == 0) && (item_data->xDC8_word.flags.x7 == 0))
            {
                func_8026A1E8(item_gobj);
            }
        }
    }
}

// 0x802694CC //
// https://decomp.me/scratch/RSwz3 //
void func_802694CC(HSD_GObj* item_gobj) // Advance item animation + script? //
{
    s32 filler[2];
    HSD_JObj* item_jobj;
    Item* item_data;

    item_jobj = item_gobj->hsd_obj;
    item_data = item_gobj->user_data;
    HSD_JObjAnimAll(item_jobj);
    item_data->x5CC_currentAnimFrame = func_8000BDB4(item_jobj);
    func_802799E4(item_gobj);
}

// 0x80269528 //
// https://decomp.me/scratch/FGX2f //
void lbl_80269528(HSD_GObj* item_gobj) // Item Think - Animation //
{
    s32 filler[6];
    HSD_JObj* item_jobj;
    f32 lifeTimer;
    s32(*cb_Anim)(HSD_GObj*);
    Item* item_data;

    item_data = item_gobj->user_data;
    !item_data;
    if (item_data->xDC8_word.flags.x9 == 0)
    {
        item_jobj = item_gobj->hsd_obj;
        HSD_JObjAnimAll(item_jobj);
        item_data->x5CC_currentAnimFrame = func_8000BDB4(item_jobj);
        func_802799E4(item_gobj);
        cb_Anim = item_data->itcb.xD14_callback_Anim;
        !cb_Anim;
        if ((cb_Anim != 0) && (cb_Anim(item_gobj) != 0))
        {
            item_data->xD60 = 0;
            func_8026A8EC(item_gobj);
            return;
        }
    }
    if (item_data->xDD0_flag.bits.b6 != 0)
    {
        item_data->xD40 -= 1.0f;
        if (item_data->xD40 <= 0.0f)
        {
            item_data->xDD0_flag.bits.b6 = 0;
            item_data->xD40 = 0.0f;
            func_80279BBC(item_data);
            if (item_data->xDD0_flag.bits.b7 == 0)
            {
                func_802756E0(item_gobj);
            }
        }
    }
    if ((item_data->xDC8_word.flags.x15 != 0) && (item_data->x10_item_kind < 0x23) && (item_data->xDD0_flag.bits.b3 == 0))
    {
        item_data->xD44_lifeTimer -= 1.0f;
        lifeTimer = item_data->xD44_lifeTimer;
        if (lifeTimer <= 0.0f)
        {
            item_data->xD60 = 0;
            func_8026A8EC(item_gobj);
            return;
        }
        if (lifeTimer <= (f32)lbl_804D6D28->x34)
        {
            func_802728C8(item_gobj);
        }
    }
    func_802721B8(item_gobj);
    func_80272298(item_gobj);
    func_80279BE0(item_gobj);
}

// 0x802696CC //
// https://decomp.me/scratch/fTxLC //
s32 func_802696CC(HSD_GObj* item_gobj) // Item Think - Check for Blast Zones //
{
    s32 temp_r0;
    s32 temp_r3;
    Item* item_data;

    item_data = item_gobj->user_data;
    temp_r0 = item_data->xDCC_flag.b4567;
    if ((temp_r0 & 8) && (item_data->x4C_pos.x > Stage_GetBlastZoneRightOffset()))
    {
        item_data->xD60 = 3;
        func_8026A8EC(item_gobj);
        return 1;
    }
    temp_r0 = item_data->xDCC_flag.b4567;
    if ((temp_r0 & 4) && (item_data->x4C_pos.x < Stage_GetBlastZoneLeftOffset()))
    {
        item_data->xD60 = 3;
        func_8026A8EC(item_gobj);
        return 1;
    }
    temp_r3 = item_data->xDCC_flag.b4567;
    if (((temp_r3 & 1) != 0) && (item_data->x4C_pos.y > 10000.0f))
    {
        item_data->xD60 = 3;
        func_8026A8EC(item_gobj);
        return 1;
    }
    if (((temp_r3 & 2) != 0) && (item_data->x4C_pos.y < Stage_GetBlastZoneBottomOffset())) 
    {
        item_data->xD60 = 3;
        func_8026A8EC(item_gobj);
        return 1;
    }
    return 0;
}

extern void func_801C9E60(Vec3*);                          /* extern */

// 0x802697D4 //
// https://decomp.me/scratch/iJ7xS //
void func_802697D4(HSD_GObj* item_gobj) // Item Think - Physics //
{
    Vec3 sp1C;
    s32 filler[4];
    void (*cb_Phys)(HSD_GObj*);
    Item* item_data;

    item_data = item_gobj->user_data;
    if (item_data->xDC8_word.flags.x9 == 0)
    {
        cb_Phys = item_data->itcb.xD18_callback_Phys;
        !cb_Phys;
        if (cb_Phys != 0)
        {
            cb_Phys(item_gobj);
        }
    }
    if (item_data->xDC8_word.flags.x13 == 0)
    {
        if (item_data->xDC8_word.flags.x9 == 0)
        {
            PSVECAdd(&item_data->x40_vel, &item_data->x70_nudge, &sp1C);
            if ((item_data->xC0_unk_state == 0) && (item_data->xDCD_flag.bits.b3 == 0))
            {
                func_8027737C(item_gobj, &sp1C);
            }
            PSVECAdd(&item_data->x4C_pos, &sp1C, &item_data->x4C_pos);
        }
        if ((item_data->xDCC_flag.b3 == 1) && ((item_data->xDCC_flag.b4567 & 0xF) != 0))
        {
            if (func_802696CC(item_gobj) != 0)
            {
                return;
            }
        }
        {
            if ((item_data->xD3C_spinSpeed) && (item_data->xC0_unk_state == 1))
            {
                func_80274A64(item_gobj);
            }
        }
    }
    if ((item_data->xDD1_flag.bits.b1 != 0) && (item_data->xC0_unk_state == 1))
    {
        func_801C9E60(&item_data->x58_vec_unk);
    }
    PSVECAdd(&item_data->x4C_pos, &item_data->x58_vec_unk, &item_data->x4C_pos);
    func_80273484(item_gobj);
    if ((s32)item_data->xC0_unk_state == 0)
    {
        if ((item_data->xDCE_flag.bits.b3 != 0) && (func_8026D604(item_gobj) != 0))
        {
            func_800567C0(item_data->xC30, &item_data->x4C_pos, &item_data->x64_vec_unk2);
        }
        else
        {
            func_800567C0(item_data->x378_itemColl.x14C_ground.index, &item_data->x4C_pos, &item_data->x64_vec_unk2);
        }
    }
    PSVECAdd(&item_data->x4C_pos, &item_data->x64_vec_unk2, &item_data->x4C_pos);
    func_8027346C(item_gobj);
    func_802714C0(item_gobj);
}

// 0x80269978 //
// https://decomp.me/scratch/luVc4 //
void func_80269978(HSD_GObj* item_gobj) // Item Think - Collision //
{
    s32 filler[2];
    Item* item_data;
    HSD_JObj* item_jobj;
    s32(*cb_Coll)(HSD_GObj*);

    item_data = item_gobj->user_data;
    cb_Coll = item_data->itcb.xD1C_callback_Coll;
    !cb_Coll;
    if ((cb_Coll != 0) && (cb_Coll(item_gobj) != 0))
    {
        item_data->xD60 = 1;
        func_8026A8EC(item_gobj);
        return;
    }
    item_jobj = item_gobj->hsd_obj;
    !item_jobj;
    HSD_JObjSetTranslate(item_jobj, &item_data->x4C_pos);
    func_8027574C(item_gobj);
    func_8026C368(item_gobj);
}

extern void func_80067624(HSD_GObj*, void*);

// 0x80269A9C //
// https://decomp.me/scratch/uI7DN //
void lbl_80269A9C(HSD_GObj* item_gobj) // Item Think - Accessory + Camera Box //
{
    s32 filler[2];
    void (*cb_Accessory)(HSD_GObj*);
    Item* item_data;
    Item* temp_item;
    CameraBox* cameraBox;

    item_data = item_gobj->user_data;
    func_80067624(item_gobj, &item_data->xBC0);
    if (item_data->xDC8_word.flags.x9 == 0)
    {
        cb_Accessory = item_data->itcb.xD20_callback_Accessory;
        !cb_Accessory;
        if (cb_Accessory != 0)
        {
            cb_Accessory(item_gobj);
        }
    }
    temp_item = item_gobj->user_data;
    if (temp_item->xDCD_flag.bits.b01 != 0)
    {

        cameraBox = temp_item->x520_cameraBox;
        if (cameraBox != 0)
        {
            cameraBox->x10 = temp_item->x4C_pos;
            cameraBox->x1C = temp_item->x4C_pos;
        }
    }
    func_80271A58(item_gobj);
    func_80272280(item_gobj);
    func_802722B0(item_gobj);
}

void func_8027137C(HSD_GObj*);                             /* extern */
void func_8027146C(HSD_GObj*);

// 0x80269B60 //
// https://decomp.me/scratch/Nqid5 //
void lbl_80269B60(HSD_GObj* item_gobj) // Item Think - Yellow Bar Collision (cb_JumpedOn) //
{
    s32(*cb_JumpedOn)(HSD_GObj*);
    Item* item_data;

    item_data = item_gobj->user_data;
    if ((u32)item_data->xCFC != 0U)
    {
        cb_JumpedOn = item_data->itcb.xD30_callback_JumpedOn;
        !cb_JumpedOn;
        if ((cb_JumpedOn != 0) && (cb_JumpedOn(item_gobj) != 0))
        {
            item_data->xD60 = 2;
            func_8026A8EC(item_gobj);
            return;
        }
    }
    func_8027137C(item_gobj);
    func_8027146C(item_gobj);
}

// 0x80269BE4 //
// https://decomp.me/scratch/qMNDq //
void lbl_80269BE4(HSD_GObj* item_gobj) // Item Think - Grab //
// Somewhat arbitrary. Does not run on Hook Shot / Grapple Beam, rather items such as the Barrel Cannon. //
{
    Item* item_data;
    void (*cb_GrabItem)(HSD_GObj*);
    void (*cb_GrabVictim)(HSD_GObj*, HSD_GObj*);

    item_data = item_gobj->user_data;
    if (item_data->xDD0_flag.bits.b5 != 0)
    {
        func_802701BC(item_gobj);
        if (item_data->xD00_grabGObj != 0U)
        {
            cb_GrabItem = item_data->itcb.xD34_callback_Grab_ItemCB;
            !cb_GrabItem;
            cb_GrabItem(item_gobj);
            cb_GrabVictim = item_data->itcb.xD38_callback_Grab_VictimCB;
            !cb_GrabVictim;
            cb_GrabVictim(item_data->xD00_grabGObj, item_gobj);
        }
    }
}

// 0x80269C5C //
// https://decomp.me/scratch/ui7Ut //
void lbl_80269C5C(HSD_GObj* item_gobj) // Item Think - Hit Collision Logic //
{
    s32 filler[2];
    func_8026F9A0();
    func_802703E8(item_gobj);
    func_802706D0(item_gobj);
    func_80270E30(item_gobj);
}

// 0x80269CA0 //
// https://decomp.me/scratch/R5aaH //
void func_80269CA0(Item* item_data, s32 damage) // Set damage taken //
{
    item_data->itdmg.xC9C = (s32)(item_data->itdmg.xC9C + damage);
    if ((s32)item_data->itdmg.xC9C > 999)
    {
        item_data->itdmg.xC9C = 999;
    }
}

// 0x80269CC4 //
// https://decomp.me/scratch/lBljA //
void func_80269CC4(HSD_GObj* item_gobj) // Set damage struct //
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

// 0x80269DC8 //
// https://decomp.me/scratch/btcQS //
s32 func_80269DC8(HSD_GObj* item_gobj) // Item Think - Shield Collision //
{
    s32(*cb_OnShieldBounce)(HSD_GObj*);
    s32(*cb_OnHitShield)(HSD_GObj*);
    Item* item_data;
    struct ItemLogicTable* temp_logicTable;

    item_data = item_gobj->user_data;
    if ((item_data->xDCE_flag.bits.b5 != 0) && ((s32)item_data->xC0_unk_state == 1) && ((item_data->xDCE_flag.bits.b4 != 0) || (item_data->itdmg.xC54 < (0.01745329238474369f * (90.0f + lbl_804D6D28->x80_float[0x18])))))
    {
        if (item_data->xDCE_flag.bits.b4 == 0)
        {
            item_data->itdmg.xC54 = (item_data->itdmg.xC54 - 1.5707963267948966);
            if (item_data->itdmg.xC54 < 0.0f)
            {
                item_data->itdmg.xC54 = 0.0f;
            }
        }
        cb_OnShieldBounce = item_data->xB8_itemLogicTable->x30_callback_OnShieldBounce;
        if ((cb_OnShieldBounce != 0) && (cb_OnShieldBounce(item_gobj) != 0))
        {
            item_data->xD60 = 2;
            func_8026A8EC(item_gobj);
            return 1;
        }
        goto block_return;
    }
    temp_logicTable = item_data->xB8_itemLogicTable;
    cb_OnHitShield = temp_logicTable->x34_callback_OnHitShield;
    if (func_80274C78(item_gobj) != 0)
    {
        item_data->itdmg.xCA8 = (s32)item_data->itdmg.xC50;
    }
    if ((cb_OnHitShield != 0) && (cb_OnHitShield(item_gobj) != 0))
    {
        item_data->xD60 = 2;
        func_8026A8EC(item_gobj);
        return 1;
    }
block_return:
    return 0;
}

// 0x80269F14 //
// https://decomp.me/scratch/r1YTR //
s32 func_80269F14(HSD_GObj* item_gobj) // Item Think - On Reflect //
{
    f32 temp_f30;
    s32(*cb_OnReflect)(HSD_GObj*);
    s32 i;
    u32 var_r27;
    u8 temp_r3;
    Item* temp_item;

    temp_item = item_gobj->user_data;
    if (temp_item->xDCC_flag.b1 == 0)
    {
        if ((s32)temp_item->x10_item_kind == 0x22)
        {
            if (temp_item->xDCC_flag.b2 == 0)
            {
                temp_item->x518_ownerGObj = temp_item->itdmg.xC64_reflectGObj;
                temp_item->x20_team_id = func_80086EB4(temp_item->x518_ownerGObj);
            }
        }
        else
        {
            temp_item->x518_ownerGObj = temp_item->itdmg.xC64_reflectGObj;
            temp_item->x20_team_id = func_80086EB4(temp_item->x518_ownerGObj);
        }
    }
    func_80225DD8(item_gobj, temp_item->x518_ownerGObj);
    temp_item->xD90 = (s32)temp_item->itdmg.xC74;
    temp_item->xD94 = temp_item->itdmg.xC78;
    temp_item->xD9C = temp_item->itdmg.xC80;
    temp_item->xDA4_word = (s32)temp_item->itdmg.xC88;
    temp_item->xDA8_short = (u16)temp_item->itdmg.xC8C;
    cb_OnReflect = temp_item->xB8_itemLogicTable->x24_callback_OnReflect;
    if ((cb_OnReflect != 0) && (cb_OnReflect(item_gobj) != 0))
    {
        temp_item->xD60 = 2;
        func_8026A8EC(item_gobj);
        return 1;
    }
    if (temp_item->xDCC_flag.b0 == 0)
    {
        for (i = 0; i < 4; i++) // 4 here is the maximum amount of hitboxes available in the vanilla Item struct //
        {
            if ((s32)temp_item->x5D4_hitboxes[i].x0_toggle != 0)
            {
                temp_f30 = (temp_item->x5D4_hitboxes[i].xC_damage_staled * temp_item->itdmg.xC6C) + 0.9900000095367432f;
                var_r27 = (u32)temp_f30;
                if (var_r27 > lbl_804D6D28->xD8)
                {
                    var_r27 = lbl_804D6D28->xD8;
                }
                func_80272460(&temp_item->x5D4_hitboxes[i], var_r27, item_gobj);
            }
        }
    }
    return 0;
}

// 0x8026A0A0 //
// https://decomp.me/scratch/9CDfn //
void func_8026A0A0(HSD_GObj* item_gobj) // Item Think - Exit Hitlag Check //
{
    Item* item_data;

    item_data = item_gobj->user_data;
    if (item_data->xDC8_word.flags.x7 != 0)
    {
        if ((item_data->xDC8_word.flags.xA == 0) && (item_data->xDC8_word.flags.x8 == 0))
        {
            func_8026A1E8(item_gobj);
        }
        item_data->xDC8_word.flags.x7 = 0;
    }
}

// 0x8026A0FC //
// https://decomp.me/scratch/y8uBJ //
void func_8026A0FC(HSD_GObj* item_gobj) // Item Think - Exit Hitlag Check 2 //
{
    Item* item_data;

    item_data = item_gobj->user_data;
    if (item_data->xDC8_word.flags.x8 != 0)
    {
        if ((item_data->xDC8_word.flags.xA == 0) && (item_data->xDC8_word.flags.x7 == 0))
        {
            func_8026A1E8(item_gobj);
        }
        item_data->xDC8_word.flags.x8 = 0;
    }
}

#pragma dont_inline on

// 0x8026A158 //
// https://decomp.me/scratch/W12dC //
void func_8026A158(HSD_GObj* item_gobj) // Item Think - Enter Hitlag //
{
    void (*cb_EnterHitlag)(HSD_GObj*);
    Item* item_data;
    HSD_GObj* atkCollGObj;
    Item* temp_item;
    s32 filler;

    item_data = item_gobj->user_data;
    cb_EnterHitlag = item_data->itcb.xD28_callback_EnterHitlag;
    !cb_EnterHitlag;
    if (cb_EnterHitlag != 0)
    {
        cb_EnterHitlag(item_gobj);
    }
    item_data->xDC8_word.flags.x9 = 1;
    if ((item_data->xD04_atkCollItem != 0) && (func_80272D1C(item_data->xD04_atkCollItem) != 0) && (item_data->xDC8_word.flags.x8 == 0))
    {
        atkCollGObj = item_data->xD04_atkCollItem;
        temp_item = atkCollGObj->user_data;
        temp_item->xDC8_word.flags.x8 = 1;
        func_8026A158(atkCollGObj);
    }
}

// 0x8026A1E8 //
// https://decomp.me/scratch/cgRLZ //
void func_8026A1E8(HSD_GObj* item_gobj) // Item Think - Exit Hitlag //
{
    void (*cb_ExitHitlag)(HSD_GObj*);
    Item* item_data;
    HSD_GObj* atkCollGObj;
    Item* temp_item;
    s32 filler[2];

    item_data = item_gobj->user_data;
    cb_ExitHitlag = item_data->itcb.xD2C_callback_ExitHitlag;
    !cb_ExitHitlag;
    if (cb_ExitHitlag != 0)
    {
        cb_ExitHitlag(item_gobj);
    }
    item_data->xDC8_word.flags.x9 = 0;
    if ((item_data->xD04_atkCollItem != 0) && (func_80272D1C(item_data->xD04_atkCollItem) != 0) && (item_data->xDC8_word.flags.x8 == 0))
    {
        atkCollGObj = item_data->xD04_atkCollItem;
        temp_item = atkCollGObj->user_data;
        if (temp_item->xDC8_word.flags.x8 != 0)
        {
            if ((temp_item->xDC8_word.flags.xA == 0) && (temp_item->xDC8_word.flags.x7 == 0))
            {
                func_8026A1E8(atkCollGObj);
            }
            temp_item->xDC8_word.flags.x8 = 0;
        }
    }
}

#pragma dont_inline off

inline s32 processCallback(s32(*cb)(HSD_GObj*), HSD_GObj* item_gobj, Item* item_data) 
{
    if (cb && cb(item_gobj))
    {
        item_data->xD60 = 2;
        func_8026A8EC(item_gobj);
        return 1;
    }
    return 0;
}

inline s32 OnTakeDamageThink(HSD_GObj* item_gobj, Item* item_data)
{
    item_data->itdmg.xC9C = (s32)(item_data->itdmg.xC9C + item_data->itdmg.xCA0);
    if (item_data->itdmg.xC9C > 999)
    {
        item_data->itdmg.xC9C = 999;
    }
    item_data->itdmg.xCA8 = item_data->itdmg.xCA0;
    item_data->xDC8_word.flags.xB = 1;
    return processCallback(item_data->xB8_itemLogicTable->x1C_callback_OnTakeDamage, item_gobj, item_data);
}

inline s32 OnClankThink(HSD_GObj* item_gobj, Item* item_data)
{
    s32(*cb_OnClank)(HSD_GObj*) = item_data->xB8_itemLogicTable->x28_callback_OnClank;
    if (func_80274C78(item_gobj))
    {
        item_data->itdmg.xCA8 = item_data->itdmg.xC48;
    }
    return processCallback(cb_OnClank, item_gobj, item_data);

}

inline s32 OnGiveDamageThink(HSD_GObj* item_gobj, Item* item_data)
{
    s32(*cb_OnGiveDamage)(HSD_GObj*) = item_data->xB8_itemLogicTable->x18_callback_OnGiveDamage;
    if (func_80274C78(item_gobj))
    {
        item_data->itdmg.xCA8 = item_data->itdmg.xC34_damageDealt;
    }
    return processCallback(cb_OnGiveDamage, item_gobj, item_data);
}


inline void EnterHitlagThink(HSD_GObj* item_gobj, Item* item_data)
{
    flag32 flags = item_data->xDC8_word;
    void (*cb_EnterHitlag)(HSD_GObj*);

    if (!item_data->xDC8_word.flags.x9) {


        item_data = GetItemData(item_gobj);
        cb_EnterHitlag = item_data->itcb.xD28_callback_EnterHitlag;

        if (cb_EnterHitlag) cb_EnterHitlag(item_gobj);
        item_data->xDC8_word.flags.x9 = 1;

        if ((item_data->xD04_atkCollItem) && func_80272D1C(item_data->xD04_atkCollItem) && !item_data->xDC8_word.flags.x8)
        {
            HSD_GObj* new_gobj = item_data->xD04_atkCollItem;
            Item* new_item = new_gobj->user_data;
            new_item->xDC8_word.flags.x8 = 1;
            func_8026A158(new_gobj);
        }
    }

}


inline void checkHitLag(f32 min_value, Item* item_data)
{
    if (item_data->itdmg.xCBC_hitlagFrames < min_value)
    {
        item_data->itdmg.xCBC_hitlagFrames = min_value;
    }
    item_data->xDC8_word.flags.xA = 1;
}

// 0x8026A294 //
// https://decomp.me/scratch/ZRhI3 //
void lbl_8026A294(HSD_GObj* item_gobj) // Item Think - Hit Collision //
{
    Item* item_data = GetItemData(item_gobj);

    if ((item_data->itdmg.xCC8_knockback) || (item_data->itdmg.xCA0))
    {
        if (OnTakeDamageThink(item_gobj, item_data)) return;
    }
    else if (item_data->itdmg.xC50)
    {
        if (func_80269DC8(item_gobj)) return;
    }
    else if (item_data->itdmg.xC48)
    {
        if (OnClankThink(item_gobj, item_data)) return;
    }
    else if ((item_data->itdmg.xC34_damageDealt) || (item_data->itdmg.xC4C))
    {
        if (OnGiveDamageThink(item_gobj, item_data)) return;
    }
    else if (item_data->itdmg.xC64_reflectGObj)
    {
        if (func_80269F14(item_gobj)) return;
    }
    else if (item_data->itdmg.xC90_absorbGObj)
    {
        if (processCallback(item_data->xB8_itemLogicTable->x2C_callback_OnAbsorb, item_gobj, item_data))
        {
            return;
        }
    }
    else if (item_data->xDCE_flag.bits.b6)
    {
        if (processCallback(item_data->itcb.xD24_callback_Inert, item_gobj, item_data))
        {
            return;
        }
    }

    if ((item_data->xDC8_word.flags.xD) && (item_data->itdmg.xCC0 > 0.0f))
    {
        checkHitLag(item_data->itdmg.xCC0, item_data);

        EnterHitlagThink(item_gobj, item_data);
    }
    else if (item_data->itdmg.xCA8)
    {
        checkHitLag(func_8026B424(item_data->itdmg.xCA8), item_data);

        EnterHitlagThink(item_gobj, item_data);
    }
    if ((item_data->xDC8_word.flags.x4) || (item_data->xDC8_word.flags.x3))
    {
        EnterHitlagThink(item_gobj, item_data);

        if (item_data->xDC8_word.flags.x4)
        {
            item_data->xDC8_word.flags.x8 = 1;
            item_data->xDC8_word.flags.x4 = 0;
        }
        else
        {
            item_data->xDC8_word.flags.x7 = 1;
            item_data->xDC8_word.flags.x3 = 0;
        }
    }
    func_80269CC4(item_gobj);
}

// 0x8026A788 //
// https://decomp.me/scratch/MJJDV //
void lbl_8026A788(HSD_GObj* item_gobj) // Item Think - Process Dynamic Bones //
{
    Item* item_data = item_gobj->user_data;
    int dynamicBonesNum = item_data->x374_dynamicBonesNum;
    ItemDynamicBones* dynamicBones = item_data->xD4_dynamicBones;
    int i;

    func_80272304(item_gobj);
    for (i = 0; i < dynamicBonesNum; i++, dynamicBones++)
    {
        func_8001044C(&dynamicBones->x8_dynamicBones, &item_data->xB6C, item_data->xB68, 0.0f, 0, dynamicBones->x0_apply_phys_num, 0, 1);
    }
}

// 0x8026A810 //
// https://decomp.me/scratch/KiRDa //
void func_8026A810(HSD_GObj* item_gobj) // Item Think - Spawn //
{
    Item* temp_item = item_gobj->user_data;
    void (*cb_OnSpawn)(HSD_GObj*) = temp_item->xB8_itemLogicTable->x4_callback_OnSpawn;
    !cb_OnSpawn;

    if (cb_OnSpawn != 0)
    {
        cb_OnSpawn(item_gobj);
    }
}

extern void func_80086724(HSD_GObj*, HSD_GObj*);
extern void func_80086764(HSD_GObj*);
extern s32 func_800867A0(HSD_GObj*, HSD_GObj*);
extern HSD_GObj* func_800867CC(HSD_GObj*);

// 0x8026A848 //
// https://decomp.me/scratch/OcqKi //
void func_8026A848(HSD_GObj* item_gobj, HSD_GObj* fighter_gobj) // Remove Item from Player //
{
    s32 itemID;
    Item* temp_item;

    temp_item = GetItemDirect(item_gobj);

    if (((s32)temp_item->x14_hold_kind == 8) && (itemID = temp_item->x10_item_kind, ((itemID == 0x3A) == 0)) && (itemID != 0x3B) && (itemID != 0x63) && (itemID != 0x67)) 
    {
        if (func_800867CC(fighter_gobj) == item_gobj)
        {
            func_80086764(fighter_gobj);
        }
    }
    else if (func_800867A0(fighter_gobj, item_gobj) != 0)
    {
        func_80086724(fighter_gobj, item_gobj);
    }
}

extern void efLib_DestroyAll(HSD_GObj*);
extern void func_8000FD18(void*);
extern void func_80086724(HSD_GObj*, HSD_GObj*);
extern void func_80086764(HSD_GObj*);
extern s32 func_800867A0(HSD_GObj*, HSD_GObj*);
extern HSD_GObj* func_800867CC(HSD_GObj*);
extern s32 func_80086960(HSD_GObj*);
extern void func_80087050(s32);

inline void DestroyItemInline(HSD_GObj* item_gobj, Item* item_data)
{
    Item* item_data3 = item_gobj->user_data;
    HSD_GObj* temp_gobj = item_data->x518_ownerGObj;
    s32 itemID;
    if ((item_data3->x14_hold_kind == 8) && (itemID = item_data3->x10_item_kind, ((itemID == 0x3A) == 0)) && (itemID != 0x3B) && (itemID != 0x63) && (itemID != 0x67))
    {
        if (func_800867CC(temp_gobj) == item_gobj)
        {
            func_80086764(temp_gobj);
        }
    }
    else if (func_800867A0(temp_gobj, item_gobj) != 0)
    {
        func_80086724(temp_gobj, item_gobj);
    }
}

inline void ItemSwitch(HSD_GObj* item_gobj)
{
    Item* temp_item = item_gobj->user_data;
    s32 destroyType = temp_item->xD60;
    switch (destroyType)
    {
    case 0:
        func_8027327C(item_gobj, temp_item->xCC_item_attr->x64_destroy_gfx, temp_item->xD7C_destroySFX);
        break;

    case 2:
    case 1:
        func_8027327C(item_gobj, temp_item->xCC_item_attr->x68, temp_item->xD80);
        break;

    case 3:
    case 4:
        break;
    }
}

inline void RunCallback(HSD_GObj* item_gobj, void(*cb_Process)(HSD_GObj*))
{
    if (cb_Process != 0)
    {
        cb_Process(item_gobj);
    }
}

// 0x8026A8EC //
// https://decomp.me/scratch/CWnUq //
void func_8026A8EC(HSD_GObj* item_gobj) // Destroy Item //
{
    void (*cb_OnDestroy)(HSD_GObj*);
    s32 destroyType;
    s32 itemID;
    s32 i;
    Item* item_data4;
    HSD_GObj* temp_gobj;
    Item* item_data2;
    Item* item_data;
    Item* item_data3;
    Item* temp_item;

    item_data = item_gobj->user_data;
    if ((func_80272D1C(item_gobj) == 0) || (item_data == NULL))
    {
        OSReport("===== Not Found Item_Struct!! =====\n");
        __assert("item.c", 0x965U, "0");
    }
    func_802725D4(item_gobj);
    func_802675A8(item_gobj);
    item_data2 = item_gobj->user_data;
    if (item_data2->xDC8_word.flags.xE != 0)
    {
        func_80087050(item_data2->x378_itemColl.x19C);
        item_data2->xDC8_word.flags.xE = 0;
        item_data2->x378_itemColl.x19C = -1;
    }
    efLib_DestroyAll(item_gobj);
    if (item_data->xDCF_flag.bits.b2 == 0)
    {
        if ((item_data->xDC8_word.flags.x13 == 0) || ((u32)item_data->x518_ownerGObj == 0U))
        {
            ItemSwitch(item_gobj);
        }
    }
    temp_item = item_gobj->user_data;
    RunCallback(item_gobj, temp_item->xB8_itemLogicTable->x8_callback_OnDestroy);
    if ((item_data->xDC8_word.flags.x13 != 0) && (item_data->x518_ownerGObj != 0U) && (func_80086960(item_data->x518_ownerGObj) != 0))
    {
        DestroyItemInline(item_gobj, item_data);
    }
    item_data->x518_ownerGObj = NULL;
    item_data4 = item_gobj->user_data;
    if ((item_data4->xDCD_flag.bits.b01 != 0) && ((u32)item_data4->x520_cameraBox != 0U))
    {
        func_800290D4(item_data4->x520_cameraBox);
        item_data4->x520_cameraBox = 0U;
        item_data4->xDCD_flag.bits.b01 = 0;
    }
    for (i = 0; i < item_data->x374_dynamicBonesNum; i++)
    {
        func_8000FD18(&item_data->xD4_dynamicBones[i].x8_dynamicBones);
    }
    func_8026B0B4(item_gobj);
    func_80067688(&item_data->xBC0);
    func_80390228(item_gobj);
}

void func_8026AB54(HSD_GObj* item_gobj, s32 pickupGFX, s32 pickupSFX) // Make Item Held //
{
    void (*cb_OnPickup)(HSD_GObj*);
    Item* item_data;
    s32 filler[2];

    item_data = GetItemData(item_gobj);
    func_80273168(item_gobj);
    func_802742F4(item_gobj, pickupGFX, pickupSFX);
    RunCallback(item_gobj, item_data->xB8_itemLogicTable->xC_callback_OnPickup);
    func_8026B074(item_data);
}

// 0x8026ABD8 //
// https://decomp.me/scratch/sMVJ7 //
void func_8026ABD8(HSD_GObj* item_gobj, Vec3* pos, f32 arg2) // Drop Item //
{
    Item* item_data;

    item_data = GetItemData(item_gobj);
    item_data->itdmg.xC44 = arg2;
    func_802731A4(item_gobj);
    func_80273B50(item_gobj, pos);
    RunCallback(item_gobj, item_data->xB8_itemLogicTable->x10_callback_OnDrop);
    func_80274198(item_gobj, 1);
    func_802754D4(item_gobj);
    if (func_8026B6C8(item_gobj) != 0)
    {
        func_80275390(item_gobj);
    }
}

// 0x8026AC74 //
// https://decomp.me/scratch/hiqy7 //
void func_8026AC74(HSD_GObj* item_gobj, s32 dropGFX, s32 dropSFX, f32 arg8) // This is actually another Item Drop function //
{
    Item* item_data;

    item_data = GetItemData(item_gobj);
    item_data->itdmg.xC44 = arg8;
    func_802731A4(item_gobj);
    func_80273748(item_gobj, dropGFX, dropSFX);
    RunCallback(item_gobj, item_data->xB8_itemLogicTable->x10_callback_OnDrop);
    func_802741F4(item_gobj, 1);
    func_802754D4(item_gobj);
    if (func_8026B6C8(item_gobj) != 0)
    {
        func_80275390(item_gobj);
    }
}

// 0x8026AD20 //
// https://decomp.me/scratch/1O8Je //
void func_8026AD20(HSD_GObj* item_gobj, s32 dropGFX, s32 dropSFX, f32 arg8) // Throw Item //
{
    Item* item_data;

    item_data = GetItemData(item_gobj);
    func_802731E0(item_gobj);
    item_data->itdmg.xC44 = arg8;
    func_80273748(item_gobj, dropGFX, dropSFX);
    RunCallback(item_gobj, item_data->xB8_itemLogicTable->x14_callback_OnThrow);
    func_802741F4(item_gobj, 1);
    func_802754D4(item_gobj);
}

// 0x8026ADC0 //
// https://decomp.me/scratch/OcHJR //
void func_8026ADC0(HSD_GObj* item_gobj) // Make Item Airborne //
{
    Item* item_data;
    void (*cb_EnterAir)(HSD_GObj*);

    item_data = item_gobj->user_data;
    cb_EnterAir = item_data->xB8_itemLogicTable->x20_callback_EnterAir;
    !cb_EnterAir;
    if (cb_EnterAir != NULL)
    {
        cb_EnterAir(item_gobj);
        item_data->xDC8_word.flags.x1F = 1;
    }
}

// 0x8026AE10 //
// https://decomp.me/scratch/9jSrP //
void lbl_8026AE10(Item* item_data) // Clear Item Struct ? //
{
    Item* item_data2 = item_data;
    if (item_data->xBBC_dynamicBoneTable != NULL)
    {
        do { HSD_ObjFree(&lbl_804A0C0C, item_data2->xBBC_dynamicBoneTable); } while (0);
    }
    HSD_ObjFree(&lbl_804A0BE0.x0, item_data2);
}

// 0x8026AE60 //
// https://decomp.me/scratch/g2h93 //
u32 func_8026AE60(void) // Increment something //
{
    u32 temp_r4 = lbl_804D6D14; // This label might be U32 entirely, don't remember why it's s32 //

    lbl_804D6D14 += 1;
    if (lbl_804D6D14 == 0U)
    {
        lbl_804D6D14 += 1;
    }
    return temp_r4;
}

extern u32 func_800233EC(s32);

// 0x8026AE84 //
// https://decomp.me/scratch/zBNtM //
void func_8026AE84(Item* item_data, s32 sfxID, u8 pan, u8 volume) // Play Item SFX //
{
    s32 sfxID_new;

    sfxID_new = sfxID - 0x80000;
    if (sfxID_new != 0x3D60U)
    {
        if (sfxID_new != 0x3D61U)
        {
            item_data->xD6C = func_800237A8(func_800233EC(sfxID), (u32)pan, (u32)volume);
            return;
        }
        item_data->xD6C = func_800237A8(0x83D60U, (u32)pan, (u32)volume);
    }
}

// 0x8026AF0C //
// https://decomp.me/scratch/2TNx6 //
void func_8026AF0C(Item* item_data, s32 sfxID, u8 pan, u8 volume) // Play Item SFX 2 //
{
    s32 sfxID2;
    u32 sfxID_new;

    sfxID_new = sfxID - 0x80000;
    if (sfxID_new != 0x3D60U)
    {
        if (sfxID_new != 0x3D61U)
        {
            sfxID2 = item_data->xD64;
            if (sfxID2 != -1)
            {
                func_800236B8(sfxID2);
            }
            item_data->xD64 = func_800237A8(func_800233EC(sfxID), (u32)pan, (u32)volume);
            return;
        }
        func_8026B034(item_data);
    }
}

// 0x8026AFA0 //
// https://decomp.me/scratch/6i5MP //
void func_8026AFA0(Item* item_data, s32 sfxID, u8 pan, u8 volume) // Play Item SFX 3 //
{
    s32 sfxID2;
    u32 sfxID_new;

    sfxID_new = sfxID - 0x80000;
    if (sfxID_new != 0x3D60U)
    {
        if (sfxID_new != 0x3D61U)
        {
            sfxID2 = item_data->xD68;
            if (sfxID2 != -1)
            {
                func_800236B8(sfxID2);
            }
            item_data->xD68 = func_800237A8(func_800233EC(sfxID), (u32)pan, (u32)volume);
            return;
        }
        func_8026B074(item_data);
    }
}

// 0x8026B034 //
// https://decomp.me/scratch/vv88E //
void func_8026B034(Item* item_data) // Stop Item SFX //
{
    s32 itemSFX;

    itemSFX = item_data->xD64;
    if (itemSFX != -1)
    {
        func_800236B8(itemSFX);
    }
    item_data->xD64 = -1;
}

// 0x8026B074 //
// https://decomp.me/scratch/vrHap // 
void func_8026B074(Item* item_data) // Stop Item SFX 2 //
{
    s32 itemSFX;

    itemSFX = item_data->xD68;
    if (itemSFX != -1)
    {
        func_800236B8(itemSFX);
    }
    item_data->xD68 = -1;
}

extern void func_80026510(HSD_GObj*);
extern s32 func_800265C4(HSD_GObj*, s32);

// 0x8026B0B4 //
// https://decomp.me/scratch/Guevq //
void func_8026B0B4(HSD_GObj* item_gobj) // Stop All Item SFX // 
{
    s32 itemSFX;
    s32 itemSFX_2;
    s32 itemSFX_3;
    s32 itemSFX_4;
    Item* item_data;

    item_data = item_gobj->user_data;
    func_80026510(item_gobj);
    if ((s32)item_data->xD6C != -1)
    {
        func_800265C4(item_gobj, item_data->xD6C);
        item_data->xD6C = -1;
    }
    if (((s32)item_data->xD64 != -1) && (func_800265C4(item_gobj, item_data->xD64) == 1))
    {
        itemSFX = item_data->xD64;
        if (itemSFX != -1)
        {
            func_800236B8(itemSFX);
        }
        item_data->xD64 = -1;
    }
    if (((s32)item_data->xD68 != -1) && (func_800265C4(item_gobj, item_data->xD68) == 1))
    {
        itemSFX_2 = item_data->xD68;
        if (itemSFX_2 != -1)
        {
            func_800236B8(itemSFX_2);
        }
        item_data->xD68 = -1;
    }
    itemSFX_3 = item_data->xD64;
    if (itemSFX_3 != -1)
    {
        func_800236B8(itemSFX_3);
    }
    item_data->xD64 = -1;
    itemSFX_4 = item_data->xD68;
    if (itemSFX_4 != -1)
    {
        func_800236B8(itemSFX_4);
    }
    item_data->xD68 = -1;
    item_data->xD6C = -1;
}

// 0x8026B1A4 //
// https://decomp.me/scratch/54RbZ //
s32 func_8026B1A4(HSD_GObj* item_gobj) // Check if item is grabbable //
{
    Item* temp_item;

    temp_item = item_gobj->user_data;
    if ((temp_item->xDC8_word.flags.x15 != 0) && (temp_item->xB8_itemLogicTable->xC_callback_OnPickup != NULL))
    {
        return 1;
    }
    return 0;
}
