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