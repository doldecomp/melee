#include "ftkirby.h"

//// TODO remove externs
extern struct S_KIRBY1* lbl_803C9FC8[0x21];
extern s32 lbl_80459B88[0x21];

//// TODO find real struct / array
struct S_KIRBY1 {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C;
};

//https://decomp.me/scratch/6dL9q
void func_800EE528() {
    s32* number_list = lbl_80459B88;
    struct S_KIRBY1** struct_list = lbl_803C9FC8;

    s32 i;
    for (i = 0; i < 0x21; i++) {
        struct S_KIRBY1* unk_struct;
        number_list[i] = 0; 
        unk_struct = struct_list[i];
        if (unk_struct) {
            unk_struct->x0 = 0;
            unk_struct = struct_list[i];
            unk_struct->x4 = 0;
            unk_struct = struct_list[i];
            unk_struct->x8 = 0;
            unk_struct = struct_list[i];
            unk_struct->xC = 0;
            unk_struct = struct_list[i];
            unk_struct->x10 = 0;
            unk_struct = struct_list[i];
            unk_struct->x14 = 0;
            unk_struct = struct_list[i];
            unk_struct->x18 = 0;
            unk_struct = struct_list[i];
            unk_struct->x1C = 0;
            unk_struct = struct_list[i];
            unk_struct->x20 = 0;
            unk_struct = struct_list[i];
            unk_struct->x24 = 0;
            unk_struct = struct_list[i];
            unk_struct->x28 = 0;
            unk_struct = struct_list[i];
            unk_struct->x2C = 0;
        }
    }
}

void ftKirby_OnDeath(HSD_GObj* fighterObj) {
    Fighter *fighter = fighterObj->user_data;
    func_80074A4C(fighterObj, 0, 0);
    func_80074A4C(fighterObj, 1, 0);
    fighter->sa.kirby.x222C = 0;
    fighter->sa.kirby.x2230 = (s32) (HSD_Randi(5) + 1);
    fighter->sa.kirby.x223C = 0;
    fighter->sa.kirby.x2238 = 4;
    fighter->sa.kirby.x2244 = 0;
    fighter->sa.kirby.x228C = 0;
    fighter->sa.kirby.x2290 = 0;
    if (Player_GetFlagsBit1(fighter->xC_playerID) && Player_GetUnk4D(fighter->xC_playerID) != 4) {
        func_800F1BAC(fighterObj, Player_GetUnk4D(fighter->xC_playerID), 0);
    }
}

void ftKirby_OnLoad(HSD_GObj* fighterObj) {


    Fighter* fighter = fighterObj->user_data;
    void** item_list = fighter->x10C_ftData->x48_items;

    PUSH_ATTRS(fighter, ftKirbyAttributes);
    
    fighter->x2222_flag.bits.b1 = 1;
    fighter->x2D0 = fighter->x2D4_specialAttributes;
    fighter->sa.kirby.x2234.bits.b0 = Player_GetFlagsAEBit1(fighter->xC_playerID);
    func_8026B3F8(item_list[0], 0x32);
    func_8026B3F8(item_list[1], 0x33);
    func_8026B3F8(item_list[2], 0x34);
    func_8026B3F8(item_list[3], 0x35);
    

}

void ftKirby_800EE74C(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_800F5524(fighterObj);
    func_800F22D4(fighterObj);
    func_800F5318(fighterObj);
    func_800F9090(fighterObj);
    func_800F19AC(fighterObj);
    func_800F5D04(fighterObj, 0);
    fighter->cb.x21E8_callback_OnDeath3 = 0;
}

void ftKirby_800EE7B8(HSD_GObj* fighterObj) {
    Fighter* fighter= fighterObj->user_data;
    func_800F5524(fighterObj);
    func_800F22D4(fighterObj);
    func_800F5318(fighterObj);
    func_800F9090(fighterObj);
    func_800F1A8C(fighterObj);
    fighter->cb.x21E0_callback_OnDeath = 0;
}

//// Matching, but needs more data moved over for DOL match
// void func_800EE818(HSD_GObj* fighterObj) {
//     s32 unused[2];
//     Fighter* fighter = getFighter(fighterObj);
//     ftKirbyAttributes* attr = fighter->x2D4_specialAttributes;
//     switch (fighter->sa.kirby.x2238) {
//         case 3:
//             if (fighter->sa.kirby.x22E8 == attr->x190) {
//                 func_800BFFD0(fighter, 0x3A, 0);
//             }
//             break;
//         case 13:
//             if (fighter->sa.kirby.x22D4 == attr->x168) {
//                 func_800BFFD0(fighter, 0x36, 0);
//             }
//             break;
//         case 16:
//             if (fighter->sa.kirby.x22C8 == attr->x384) {
//                 func_800BFFD0(fighter, 0x5D, 0);
//                 return;
//             }
//             break;
//         case 7:
//             if (fighter->sa.kirby.x22E0 == 6) {
//                 func_800BFFD0(fighter, 0x57, 0);
//             }
//             break;
//     }
// }

///void ftKirby_OnItemPickup(HSD_GObj* fighterObj, BOOL bool)

// void ftKirby_OnItemInvisible(HSD_GObj* fighterObj) {
//     Fighter_OnItemInvisible(fighterObj, 1);
// }

// void ftKirby_OnItemVisible(HSD_GObj* fighterObj) {
//     Fighter_OnItemVisible(fighterObj, 1);
// }

// void ftKirby_OnItemDrop(HSD_GObj* gobj, BOOL bool1)
// {
//     Fighter_OnItemDrop(gobj, bool1, 1, 1);
// }
