#include "melee/pl/player.h"

#define NON_MATCHING 1

extern StaticPlayer player_slots[6];  // used to be [4] but I think should be 6?  ///lbl_80453080

struct Unk_Struct_w_Array {
    char some_str[8+4];  //"PdPm.dat"
    char another_str[16+4]; 
    S8Vec vec_arr[30];  ///lbl_803BCDE0
};

extern struct Unk_Struct {  //lbl_803BCDC0
    char some_str[8+4];  //"PdPm.dat"
    char another_str[16+4]; 
    //S8Vec vec_arr[30];  ///lbl_803BCDE0
} lbl_803BCDC0;

extern S8Vec lbl_803BCDE0[]; ///lbl_803BCDE0

extern char* lbl_803BCE44; //"cant get player struct! %d\n"  /// likely apart of lbl_803BCDC0 struct
extern char* lbl_803BCE60; //"player.c"

extern char* lbl_804D3940; //"0"

extern void func_800D4F24();
extern void func_80390228();
extern s32 func_8008701C(HSD_GObj*);
extern s32 func_800873CC();
extern void func_802F6E1C(s32);
extern void func_800D4FF4(HSD_GObj*);


void inline Player_CheckSlot(s32 slot)
{
    if (slot < 0 || 6 <= slot) {
        OSReport("cant get player struct! %d\n", slot);
        __assert(__FILE__, 102, "0");
    }
}

// Matches when everything is moved over
#ifdef NON_MATCHING
StaticPlayer* Player_GetPtrForSlot(s32 slot)
{
    Player_CheckSlot(slot);
    return &player_slots[slot];
}
#else
asm StaticPlayer* Player_GetPtrForSlot(s32 slot)
{
    nofralloc
/* 80031724 0002E304  7C 08 02 A6 */	mflr r0
/* 80031728 0002E308  90 01 00 04 */	stw r0, 4(r1)
/* 8003172C 0002E30C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80031730 0002E310  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80031734 0002E314  7C 7F 1B 79 */	or. r31, r3, r3
/* 80031738 0002E318  41 80 00 0C */	blt lbl_80031744
/* 8003173C 0002E31C  2C 1F 00 06 */	cmpwi r31, 6
/* 80031740 0002E320  41 80 00 2C */	blt lbl_8003176C
lbl_80031744:
/* 80031744 0002E324  3C 60 80 3C */	lis r3, lbl_803BCE44@ha
/* 80031748 0002E328  4C C6 31 82 */	crclr 6
/* 8003174C 0002E32C  38 63 CE 44 */	addi r3, r3, lbl_803BCE44@l
/* 80031750 0002E330  38 9F 00 00 */	addi r4, r31, 0
/* 80031754 0002E334  48 31 3F 55 */	bl OSReport
/* 80031758 0002E338  3C 60 80 3C */	lis r3, lbl_803BCE60@ha
/* 8003175C 0002E33C  38 63 CE 60 */	addi r3, r3, lbl_803BCE60@l
/* 80031760 0002E340  38 80 00 66 */	li r4, 0x66
/* 80031764 0002E344  38 AD 82 A0 */	addi r5, r13, lbl_804D3940
/* 80031768 0002E348  48 35 6A B9 */	bl __assert
lbl_8003176C:
/* 8003176C 0002E34C  1C 9F 0E 90 */	mulli r4, r31, 0xe90
/* 80031770 0002E350  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80031774 0002E354  3C 60 80 45 */	lis r3, player_slots@ha
/* 80031778 0002E358  38 03 30 80 */	addi r0, r3, player_slots@l
/* 8003177C 0002E35C  7C 60 22 14 */	add r3, r0, r4
/* 80031780 0002E360  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80031784 0002E364  38 21 00 18 */	addi r1, r1, 0x18
/* 80031788 0002E368  7C 08 03 A6 */	mtlr r0
/* 8003178C 0002E36C  4E 80 00 20 */	blr 
}
#endif

#ifdef NON_MATCHING
void Player_80031790(s32 slot) {

    StaticPlayer* player;
    int i;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    if ((player->slot_type == 0) || (player->slot_type == 1)) {
        for (i = 0; i < 2; i++) {  
            /// transformed will either be [1,0] (normal) or [0,1] (transformed)
            /// checks to see if the player is in a transformed state, and calls
            /// the function only once depending on the state
            if ((player->player_entity[player->transformed[i]])) {
                func_800867E8(player->player_entity[player->transformed[i]]);
            }
        }
    }
}
#else
asm void Player_80031790(s32 slot)
{
    nofralloc
/* 80031790 0002E370  7C 08 02 A6 */	mflr r0
/* 80031794 0002E374  90 01 00 04 */	stw r0, 4(r1)
/* 80031798 0002E378  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8003179C 0002E37C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800317A0 0002E380  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800317A4 0002E384  7C 7E 1B 79 */	or. r30, r3, r3
/* 800317A8 0002E388  41 80 00 0C */	blt lbl_800317B4
/* 800317AC 0002E38C  2C 1E 00 06 */	cmpwi r30, 6
/* 800317B0 0002E390  41 80 00 2C */	blt lbl_800317DC
lbl_800317B4:
/* 800317B4 0002E394  3C 60 80 3C */	lis r3, lbl_803BCE44@ha
/* 800317B8 0002E398  4C C6 31 82 */	crclr 6
/* 800317BC 0002E39C  38 63 CE 44 */	addi r3, r3, lbl_803BCE44@l
/* 800317C0 0002E3A0  38 9E 00 00 */	addi r4, r30, 0
/* 800317C4 0002E3A4  48 31 3E E5 */	bl OSReport
/* 800317C8 0002E3A8  3C 60 80 3C */	lis r3, lbl_803BCE60@ha
/* 800317CC 0002E3AC  38 63 CE 60 */	addi r3, r3, lbl_803BCE60@l
/* 800317D0 0002E3B0  38 80 00 66 */	li r4, 0x66
/* 800317D4 0002E3B4  38 AD 82 A0 */	addi r5, r13, lbl_804D3940
/* 800317D8 0002E3B8  48 35 6A 49 */	bl __assert
lbl_800317DC:
/* 800317DC 0002E3BC  1C 9E 0E 90 */	mulli r4, r30, 0xe90
/* 800317E0 0002E3C0  3C 60 80 45 */	lis r3, player_slots@ha
/* 800317E4 0002E3C4  38 03 30 80 */	addi r0, r3, player_slots@l
/* 800317E8 0002E3C8  7F E0 22 14 */	add r31, r0, r4
/* 800317EC 0002E3CC  80 1F 00 08 */	lwz r0, 8(r31)
/* 800317F0 0002E3D0  2C 00 00 00 */	cmpwi r0, 0
/* 800317F4 0002E3D4  41 82 00 0C */	beq lbl_80031800
/* 800317F8 0002E3D8  2C 00 00 01 */	cmpwi r0, 1
/* 800317FC 0002E3DC  40 82 00 34 */	bne lbl_80031830
lbl_80031800:
/* 80031800 0002E3E0  3B C0 00 00 */	li r30, 0
lbl_80031804:
/* 80031804 0002E3E4  38 1E 00 0C */	addi r0, r30, 0xc
/* 80031808 0002E3E8  7C 1F 00 AE */	lbzx r0, r31, r0
/* 8003180C 0002E3EC  54 03 10 3A */	slwi r3, r0, 2
/* 80031810 0002E3F0  38 03 00 B0 */	addi r0, r3, 0xb0
/* 80031814 0002E3F4  7C 7F 00 2E */	lwzx r3, r31, r0
/* 80031818 0002E3F8  28 03 00 00 */	cmplwi r3, 0
/* 8003181C 0002E3FC  41 82 00 08 */	beq lbl_80031824
/* 80031820 0002E400  48 05 4F C9 */	bl func_800867E8
lbl_80031824:
/* 80031824 0002E404  3B DE 00 01 */	addi r30, r30, 1
/* 80031828 0002E408  2C 1E 00 02 */	cmpwi r30, 2
/* 8003182C 0002E40C  41 80 FF D8 */	blt lbl_80031804
lbl_80031830:
/* 80031830 0002E410  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80031834 0002E414  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80031838 0002E418  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8003183C 0002E41C  38 21 00 18 */	addi r1, r1, 0x18
/* 80031840 0002E420  7C 08 03 A6 */	mtlr r0
/* 80031844 0002E424  4E 80 00 20 */	blr 
}
#endif

#ifdef NON_MATCHING
void Player_80031848(s32 slot) {
    StaticPlayer* player;
    int i;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    if ((player->slot_type == 0) || (player->slot_type == 1)) {
        for (i = 0; i < 2; i++) {  
            /// transformed will either be [1,0] (normal) or [0,1] (transformed)
            /// checks to see if the player is in a transformed state, and calls
            /// the function only once depending on the state
            if ((player->player_entity[player->transformed[i]])) {
                func_8008688C(player->player_entity[player->transformed[i]]);
            }
        }
    }
}
#else
asm void Player_80031848(s32 slot)
{
    nofralloc
/* 80031848 0002E428  7C 08 02 A6 */	mflr r0
/* 8003184C 0002E42C  90 01 00 04 */	stw r0, 4(r1)
/* 80031850 0002E430  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80031854 0002E434  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80031858 0002E438  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8003185C 0002E43C  7C 7E 1B 79 */	or. r30, r3, r3
/* 80031860 0002E440  41 80 00 0C */	blt lbl_8003186C
/* 80031864 0002E444  2C 1E 00 06 */	cmpwi r30, 6
/* 80031868 0002E448  41 80 00 2C */	blt lbl_80031894
lbl_8003186C:
/* 8003186C 0002E44C  3C 60 80 3C */	lis r3, lbl_803BCE44@ha
/* 80031870 0002E450  4C C6 31 82 */	crclr 6
/* 80031874 0002E454  38 63 CE 44 */	addi r3, r3, lbl_803BCE44@l
/* 80031878 0002E458  38 9E 00 00 */	addi r4, r30, 0
/* 8003187C 0002E45C  48 31 3E 2D */	bl OSReport
/* 80031880 0002E460  3C 60 80 3C */	lis r3, lbl_803BCE60@ha
/* 80031884 0002E464  38 63 CE 60 */	addi r3, r3, lbl_803BCE60@l
/* 80031888 0002E468  38 80 00 66 */	li r4, 0x66
/* 8003188C 0002E46C  38 AD 82 A0 */	addi r5, r13, lbl_804D3940
/* 80031890 0002E470  48 35 69 91 */	bl __assert
lbl_80031894:
/* 80031894 0002E474  1C 9E 0E 90 */	mulli r4, r30, 0xe90
/* 80031898 0002E478  3C 60 80 45 */	lis r3, player_slots@ha
/* 8003189C 0002E47C  38 03 30 80 */	addi r0, r3, player_slots@l
/* 800318A0 0002E480  7F E0 22 14 */	add r31, r0, r4
/* 800318A4 0002E484  80 1F 00 08 */	lwz r0, 8(r31)
/* 800318A8 0002E488  2C 00 00 00 */	cmpwi r0, 0
/* 800318AC 0002E48C  41 82 00 0C */	beq lbl_800318B8
/* 800318B0 0002E490  2C 00 00 01 */	cmpwi r0, 1
/* 800318B4 0002E494  40 82 00 34 */	bne lbl_800318E8
lbl_800318B8:
/* 800318B8 0002E498  3B C0 00 00 */	li r30, 0
lbl_800318BC:
/* 800318BC 0002E49C  38 1E 00 0C */	addi r0, r30, 0xc
/* 800318C0 0002E4A0  7C 1F 00 AE */	lbzx r0, r31, r0
/* 800318C4 0002E4A4  54 03 10 3A */	slwi r3, r0, 2
/* 800318C8 0002E4A8  38 03 00 B0 */	addi r0, r3, 0xb0
/* 800318CC 0002E4AC  7C 7F 00 2E */	lwzx r3, r31, r0
/* 800318D0 0002E4B0  28 03 00 00 */	cmplwi r3, 0
/* 800318D4 0002E4B4  41 82 00 08 */	beq lbl_800318DC
/* 800318D8 0002E4B8  48 05 4F B5 */	bl func_8008688C
lbl_800318DC:
/* 800318DC 0002E4BC  3B DE 00 01 */	addi r30, r30, 1
/* 800318E0 0002E4C0  2C 1E 00 02 */	cmpwi r30, 2
/* 800318E4 0002E4C4  41 80 FF D8 */	blt lbl_800318BC
lbl_800318E8:
/* 800318E8 0002E4C8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800318EC 0002E4CC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800318F0 0002E4D0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800318F4 0002E4D4  38 21 00 18 */	addi r1, r1, 0x18
/* 800318F8 0002E4D8  7C 08 03 A6 */	mtlr r0
/* 800318FC 0002E4DC  4E 80 00 20 */	blr 
}
#endif

#ifdef NON_MATCHING
void inline func_8008688C_wrapper(StaticPlayer* player)
{
    if ((player->slot_type == 0) || (player->slot_type == 1)) {
        s32 i;
        for (i = 0; i < 2; i++) {  
            if ((player->player_entity[player->transformed[i]])) {
                func_8008688C(player->player_entity[player->transformed[i]]);
            }
        }
    }
}

void Player_80031900() {
    s32 slot;
    for (slot = 0; slot < 6; slot++) {
        StaticPlayer* player = &player_slots[slot];
        Player_CheckSlot(slot);
        func_8008688C_wrapper(player);
    }
}
#else
asm void Player_80031900(s32 slot) 
{
    nofralloc
/* 80031900 0002E4E0  7C 08 02 A6 */	mflr r0
/* 80031904 0002E4E4  3C 60 80 45 */	lis r3, player_slots@ha
/* 80031908 0002E4E8  90 01 00 04 */	stw r0, 4(r1)
/* 8003190C 0002E4EC  3C 80 80 3C */	lis r4, lbl_803BCE44@ha
/* 80031910 0002E4F0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80031914 0002E4F4  BF 61 00 0C */	stmw r27, 0xc(r1)
/* 80031918 0002E4F8  3B 83 30 80 */	addi r28, r3, player_slots@l
/* 8003191C 0002E4FC  3C 60 80 3C */	lis r3, lbl_803BCE60@ha
/* 80031920 0002E500  3B C4 CE 44 */	addi r30, r4, lbl_803BCE44@l
/* 80031924 0002E504  3B E3 CE 60 */	addi r31, r3, lbl_803BCE60@l
/* 80031928 0002E508  3B 60 00 00 */	li r27, 0
lbl_8003192C:
/* 8003192C 0002E50C  2C 1B 00 00 */	cmpwi r27, 0
/* 80031930 0002E510  41 80 00 0C */	blt lbl_8003193C
/* 80031934 0002E514  2C 1B 00 06 */	cmpwi r27, 6
/* 80031938 0002E518  41 80 00 24 */	blt lbl_8003195C
lbl_8003193C:
/* 8003193C 0002E51C  38 7E 00 00 */	addi r3, r30, 0
/* 80031940 0002E520  4C C6 31 82 */	crclr 6
/* 80031944 0002E524  38 9B 00 00 */	addi r4, r27, 0
/* 80031948 0002E528  48 31 3D 61 */	bl OSReport
/* 8003194C 0002E52C  38 7F 00 00 */	addi r3, r31, 0
/* 80031950 0002E530  38 80 00 66 */	li r4, 0x66
/* 80031954 0002E534  38 AD 82 A0 */	addi r5, r13, lbl_804D3940
/* 80031958 0002E538  48 35 68 C9 */	bl __assert
lbl_8003195C:
/* 8003195C 0002E53C  80 1C 00 08 */	lwz r0, 8(r28)
/* 80031960 0002E540  2C 00 00 00 */	cmpwi r0, 0
/* 80031964 0002E544  41 82 00 0C */	beq lbl_80031970
/* 80031968 0002E548  2C 00 00 01 */	cmpwi r0, 1
/* 8003196C 0002E54C  40 82 00 34 */	bne lbl_800319A0
lbl_80031970:
/* 80031970 0002E550  3B A0 00 00 */	li r29, 0
lbl_80031974:
/* 80031974 0002E554  38 1D 00 0C */	addi r0, r29, 0xc
/* 80031978 0002E558  7C 1C 00 AE */	lbzx r0, r28, r0
/* 8003197C 0002E55C  54 03 10 3A */	slwi r3, r0, 2
/* 80031980 0002E560  38 03 00 B0 */	addi r0, r3, 0xb0
/* 80031984 0002E564  7C 7C 00 2E */	lwzx r3, r28, r0
/* 80031988 0002E568  28 03 00 00 */	cmplwi r3, 0
/* 8003198C 0002E56C  41 82 00 08 */	beq lbl_80031994
/* 80031990 0002E570  48 05 4E FD */	bl func_8008688C
lbl_80031994:
/* 80031994 0002E574  3B BD 00 01 */	addi r29, r29, 1
/* 80031998 0002E578  2C 1D 00 02 */	cmpwi r29, 2
/* 8003199C 0002E57C  41 80 FF D8 */	blt lbl_80031974
lbl_800319A0:
/* 800319A0 0002E580  3B 7B 00 01 */	addi r27, r27, 1
/* 800319A4 0002E584  2C 1B 00 06 */	cmpwi r27, 6
/* 800319A8 0002E588  3B 9C 0E 90 */	addi r28, r28, 0xe90
/* 800319AC 0002E58C  41 80 FF 80 */	blt lbl_8003192C
/* 800319B0 0002E590  BB 61 00 0C */	lmw r27, 0xc(r1)
/* 800319B4 0002E594  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800319B8 0002E598  38 21 00 20 */	addi r1, r1, 0x20
/* 800319BC 0002E59C  7C 08 03 A6 */	mtlr r0
/* 800319C0 0002E5A0  4E 80 00 20 */	blr 
}
#endif

#ifdef NON_MATCHING
BOOL Player_800319C4(s32 slot, BOOL arg1) {

    s32 unused;

    s32 i;
    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = (&player_slots[slot]);


    if (arg1) {
        for (i = 0; i < 2; i++) {
            if (!player->player_entity[player->transformed[i]]) {
                return FALSE;
            }
        }
        return TRUE;
    }

    for (i = 0; i < 2; i++) {
        if (player->player_entity[player->transformed[i]]) {
            return FALSE;
        } 
    }
    
    return TRUE;

}
#else
asm BOOL Player_800319C4(s32 slot, BOOL arg1)
{
    nofralloc
/* 800319C4 0002E5A4  7C 08 02 A6 */	mflr r0
/* 800319C8 0002E5A8  90 01 00 04 */	stw r0, 4(r1)
/* 800319CC 0002E5AC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800319D0 0002E5B0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800319D4 0002E5B4  3B E4 00 00 */	addi r31, r4, 0
/* 800319D8 0002E5B8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800319DC 0002E5BC  7C 7E 1B 79 */	or. r30, r3, r3
/* 800319E0 0002E5C0  41 80 00 0C */	blt lbl_800319EC
/* 800319E4 0002E5C4  2C 1E 00 06 */	cmpwi r30, 6
/* 800319E8 0002E5C8  41 80 00 2C */	blt lbl_80031A14
lbl_800319EC:
/* 800319EC 0002E5CC  3C 60 80 3C */	lis r3, lbl_803BCE44@ha
/* 800319F0 0002E5D0  4C C6 31 82 */	crclr 6
/* 800319F4 0002E5D4  38 63 CE 44 */	addi r3, r3, lbl_803BCE44@l
/* 800319F8 0002E5D8  38 9E 00 00 */	addi r4, r30, 0
/* 800319FC 0002E5DC  48 31 3C AD */	bl OSReport
/* 80031A00 0002E5E0  3C 60 80 3C */	lis r3, lbl_803BCE60@ha
/* 80031A04 0002E5E4  38 63 CE 60 */	addi r3, r3, lbl_803BCE60@l
/* 80031A08 0002E5E8  38 80 00 66 */	li r4, 0x66
/* 80031A0C 0002E5EC  38 AD 82 A0 */	addi r5, r13, lbl_804D3940
/* 80031A10 0002E5F0  48 35 68 11 */	bl __assert
lbl_80031A14:
/* 80031A14 0002E5F4  1C 9E 0E 90 */	mulli r4, r30, 0xe90
/* 80031A18 0002E5F8  3C 60 80 45 */	lis r3, player_slots@ha
/* 80031A1C 0002E5FC  38 03 30 80 */	addi r0, r3, player_slots@l
/* 80031A20 0002E600  2C 1F 00 00 */	cmpwi r31, 0
/* 80031A24 0002E604  7C 80 22 14 */	add r4, r0, r4
/* 80031A28 0002E608  41 82 00 4C */	beq lbl_80031A74
/* 80031A2C 0002E60C  88 04 00 0C */	lbz r0, 0xc(r4)
/* 80031A30 0002E610  54 03 10 3A */	slwi r3, r0, 2
/* 80031A34 0002E614  38 03 00 B0 */	addi r0, r3, 0xb0
/* 80031A38 0002E618  7C 04 00 2E */	lwzx r0, r4, r0
/* 80031A3C 0002E61C  28 00 00 00 */	cmplwi r0, 0
/* 80031A40 0002E620  40 82 00 0C */	bne lbl_80031A4C
/* 80031A44 0002E624  38 60 00 00 */	li r3, 0
/* 80031A48 0002E628  48 00 00 70 */	b lbl_80031AB8
lbl_80031A4C:
/* 80031A4C 0002E62C  88 04 00 0D */	lbz r0, 0xd(r4)
/* 80031A50 0002E630  54 03 10 3A */	slwi r3, r0, 2
/* 80031A54 0002E634  38 03 00 B0 */	addi r0, r3, 0xb0
/* 80031A58 0002E638  7C 04 00 2E */	lwzx r0, r4, r0
/* 80031A5C 0002E63C  28 00 00 00 */	cmplwi r0, 0
/* 80031A60 0002E640  40 82 00 0C */	bne lbl_80031A6C
/* 80031A64 0002E644  38 60 00 00 */	li r3, 0
/* 80031A68 0002E648  48 00 00 50 */	b lbl_80031AB8
lbl_80031A6C:
/* 80031A6C 0002E64C  38 60 00 01 */	li r3, 1
/* 80031A70 0002E650  48 00 00 48 */	b lbl_80031AB8
lbl_80031A74:
/* 80031A74 0002E654  88 04 00 0C */	lbz r0, 0xc(r4)
/* 80031A78 0002E658  54 03 10 3A */	slwi r3, r0, 2
/* 80031A7C 0002E65C  38 03 00 B0 */	addi r0, r3, 0xb0
/* 80031A80 0002E660  7C 04 00 2E */	lwzx r0, r4, r0
/* 80031A84 0002E664  28 00 00 00 */	cmplwi r0, 0
/* 80031A88 0002E668  41 82 00 0C */	beq lbl_80031A94
/* 80031A8C 0002E66C  38 60 00 00 */	li r3, 0
/* 80031A90 0002E670  48 00 00 28 */	b lbl_80031AB8
lbl_80031A94:
/* 80031A94 0002E674  88 04 00 0D */	lbz r0, 0xd(r4)
/* 80031A98 0002E678  54 03 10 3A */	slwi r3, r0, 2
/* 80031A9C 0002E67C  38 03 00 B0 */	addi r0, r3, 0xb0
/* 80031AA0 0002E680  7C 04 00 2E */	lwzx r0, r4, r0
/* 80031AA4 0002E684  28 00 00 00 */	cmplwi r0, 0
/* 80031AA8 0002E688  41 82 00 0C */	beq lbl_80031AB4
/* 80031AAC 0002E68C  38 60 00 00 */	li r3, 0
/* 80031AB0 0002E690  48 00 00 08 */	b lbl_80031AB8
lbl_80031AB4:
/* 80031AB4 0002E694  38 60 00 01 */	li r3, 1
lbl_80031AB8:
/* 80031AB8 0002E698  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80031ABC 0002E69C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80031AC0 0002E6A0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80031AC4 0002E6A4  38 21 00 20 */	addi r1, r1, 0x20
/* 80031AC8 0002E6A8  7C 08 03 A6 */	mtlr r0
/* 80031ACC 0002E6AC  4E 80 00 20 */	blr 
}
#endif

asm void Player_80031AD0(s32 slot) /// https://decomp.me/scratch/tfUzD
{
    nofralloc
/* 80031AD0 0002E6B0  7C 08 02 A6 */	mflr r0
/* 80031AD4 0002E6B4  90 01 00 04 */	stw r0, 4(r1)
/* 80031AD8 0002E6B8  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 80031ADC 0002E6BC  BF 61 00 34 */	stmw r27, 0x34(r1)
/* 80031AE0 0002E6C0  7C 7C 1B 79 */	or. r28, r3, r3
/* 80031AE4 0002E6C4  3C 60 80 3C */	lis r3, lbl_803BCDC0@ha
/* 80031AE8 0002E6C8  3B E3 CD C0 */	addi r31, r3, lbl_803BCDC0@l
/* 80031AEC 0002E6CC  41 80 00 0C */	blt lbl_80031AF8
/* 80031AF0 0002E6D0  2C 1C 00 06 */	cmpwi r28, 6
/* 80031AF4 0002E6D4  41 80 00 24 */	blt lbl_80031B18
lbl_80031AF8:
/* 80031AF8 0002E6D8  38 9C 00 00 */	addi r4, r28, 0
/* 80031AFC 0002E6DC  4C C6 31 82 */	crclr 6
/* 80031B00 0002E6E0  38 7F 00 84 */	addi r3, r31, 0x84
/* 80031B04 0002E6E4  48 31 3B A5 */	bl OSReport
/* 80031B08 0002E6E8  38 7F 00 A0 */	addi r3, r31, 0xa0
/* 80031B0C 0002E6EC  38 80 00 66 */	li r4, 0x66
/* 80031B10 0002E6F0  38 AD 82 A0 */	addi r5, r13, lbl_804D3940
/* 80031B14 0002E6F4  48 35 67 0D */	bl __assert
lbl_80031B18:
/* 80031B18 0002E6F8  1C 9C 0E 90 */	mulli r4, r28, 0xe90
/* 80031B1C 0002E6FC  3C 60 80 45 */	lis r3, player_slots@ha
/* 80031B20 0002E700  38 03 30 80 */	addi r0, r3, player_slots@l
/* 80031B24 0002E704  7F C0 22 14 */	add r30, r0, r4
/* 80031B28 0002E708  80 1E 00 04 */	lwz r0, 4(r30)
/* 80031B2C 0002E70C  3B BF 00 21 */	addi r29, r31, 0x21
/* 80031B30 0002E710  1C 00 00 03 */	mulli r0, r0, 3
/* 80031B34 0002E714  7C 1D 00 AE */	lbzx r0, r29, r0
/* 80031B38 0002E718  7C 00 07 74 */	extsb r0, r0
/* 80031B3C 0002E71C  2C 00 FF FF */	cmpwi r0, -1
/* 80031B40 0002E720  41 82 00 14 */	beq lbl_80031B54
/* 80031B44 0002E724  88 1E 00 AC */	lbz r0, 0xac(r30)
/* 80031B48 0002E728  38 60 00 01 */	li r3, 1
/* 80031B4C 0002E72C  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 80031B50 0002E730  98 1E 00 AC */	stb r0, 0xac(r30)
lbl_80031B54:
/* 80031B54 0002E734  80 1E 00 04 */	lwz r0, 4(r30)
/* 80031B58 0002E738  2C 1C 00 00 */	cmpwi r28, 0
/* 80031B5C 0002E73C  1C 00 00 03 */	mulli r0, r0, 3
/* 80031B60 0002E740  7C 7F 02 14 */	add r3, r31, r0
/* 80031B64 0002E744  8B 63 00 20 */	lbz r27, 0x20(r3)
/* 80031B68 0002E748  7F 7B 07 74 */	extsb r27, r27
/* 80031B6C 0002E74C  41 80 00 0C */	blt lbl_80031B78
/* 80031B70 0002E750  2C 1C 00 06 */	cmpwi r28, 6
/* 80031B74 0002E754  41 80 00 24 */	blt lbl_80031B98
lbl_80031B78:
/* 80031B78 0002E758  38 9C 00 00 */	addi r4, r28, 0
/* 80031B7C 0002E75C  4C C6 31 82 */	crclr 6
/* 80031B80 0002E760  38 7F 00 84 */	addi r3, r31, 0x84
/* 80031B84 0002E764  48 31 3B 25 */	bl OSReport
/* 80031B88 0002E768  38 7F 00 A0 */	addi r3, r31, 0xa0
/* 80031B8C 0002E76C  38 80 00 66 */	li r4, 0x66
/* 80031B90 0002E770  38 AD 82 A0 */	addi r5, r13, lbl_804D3940
/* 80031B94 0002E774  48 35 66 8D */	bl __assert
lbl_80031B98:
/* 80031B98 0002E778  93 61 00 24 */	stw r27, 0x24(r1)
/* 80031B9C 0002E77C  38 A0 00 00 */	li r5, 0
/* 80031BA0 0002E780  38 00 FF FF */	li r0, -1
/* 80031BA4 0002E784  9B 81 00 28 */	stb r28, 0x28(r1)
/* 80031BA8 0002E788  38 61 00 24 */	addi r3, r1, 0x24
/* 80031BAC 0002E78C  88 81 00 2A */	lbz r4, 0x2a(r1)
/* 80031BB0 0002E790  50 A4 3E 30 */	rlwimi r4, r5, 7, 0x18, 0x18
/* 80031BB4 0002E794  98 81 00 2A */	stb r4, 0x2a(r1)
/* 80031BB8 0002E798  88 81 00 2A */	lbz r4, 0x2a(r1)
/* 80031BBC 0002E79C  50 A4 36 72 */	rlwimi r4, r5, 6, 0x19, 0x19
/* 80031BC0 0002E7A0  98 81 00 2A */	stb r4, 0x2a(r1)
/* 80031BC4 0002E7A4  98 01 00 29 */	stb r0, 0x29(r1)
/* 80031BC8 0002E7A8  48 03 72 D1 */	bl func_80068E98
/* 80031BCC 0002E7AC  90 7E 00 B0 */	stw r3, 0xb0(r30)
/* 80031BD0 0002E7B0  38 00 00 02 */	li r0, 2
/* 80031BD4 0002E7B4  90 1E 00 00 */	stw r0, 0(r30)
/* 80031BD8 0002E7B8  80 1E 00 04 */	lwz r0, 4(r30)
/* 80031BDC 0002E7BC  1C 00 00 03 */	mulli r0, r0, 3
/* 80031BE0 0002E7C0  7C 7D 00 AE */	lbzx r3, r29, r0
/* 80031BE4 0002E7C4  7C 7D 07 74 */	extsb r29, r3
/* 80031BE8 0002E7C8  2C 1D FF FF */	cmpwi r29, -1
/* 80031BEC 0002E7CC  41 82 00 8C */	beq lbl_80031C78
/* 80031BF0 0002E7D0  7C 7F 02 14 */	add r3, r31, r0
/* 80031BF4 0002E7D4  8B 63 00 22 */	lbz r27, 0x22(r3)
/* 80031BF8 0002E7D8  2C 1C 00 00 */	cmpwi r28, 0
/* 80031BFC 0002E7DC  7F 7B 07 74 */	extsb r27, r27
/* 80031C00 0002E7E0  41 80 00 0C */	blt lbl_80031C0C
/* 80031C04 0002E7E4  2C 1C 00 06 */	cmpwi r28, 6
/* 80031C08 0002E7E8  41 80 00 24 */	blt lbl_80031C2C
lbl_80031C0C:
/* 80031C0C 0002E7EC  38 9C 00 00 */	addi r4, r28, 0
/* 80031C10 0002E7F0  4C C6 31 82 */	crclr 6
/* 80031C14 0002E7F4  38 7F 00 84 */	addi r3, r31, 0x84
/* 80031C18 0002E7F8  48 31 3A 91 */	bl OSReport
/* 80031C1C 0002E7FC  38 7F 00 A0 */	addi r3, r31, 0xa0
/* 80031C20 0002E800  38 80 00 66 */	li r4, 0x66
/* 80031C24 0002E804  38 AD 82 A0 */	addi r5, r13, lbl_804D3940
/* 80031C28 0002E808  48 35 65 F9 */	bl __assert
lbl_80031C2C:
/* 80031C2C 0002E80C  93 A1 00 18 */	stw r29, 0x18(r1)
/* 80031C30 0002E810  38 80 00 01 */	li r4, 1
/* 80031C34 0002E814  38 00 FF FF */	li r0, -1
/* 80031C38 0002E818  9B 81 00 1C */	stb r28, 0x1c(r1)
/* 80031C3C 0002E81C  88 61 00 1E */	lbz r3, 0x1e(r1)
/* 80031C40 0002E820  50 83 3E 30 */	rlwimi r3, r4, 7, 0x18, 0x18
/* 80031C44 0002E824  98 61 00 1E */	stb r3, 0x1e(r1)
/* 80031C48 0002E828  38 61 00 18 */	addi r3, r1, 0x18
/* 80031C4C 0002E82C  88 81 00 1E */	lbz r4, 0x1e(r1)
/* 80031C50 0002E830  53 64 36 72 */	rlwimi r4, r27, 6, 0x19, 0x19
/* 80031C54 0002E834  98 81 00 1E */	stb r4, 0x1e(r1)
/* 80031C58 0002E838  98 01 00 1D */	stb r0, 0x1d(r1)
/* 80031C5C 0002E83C  48 03 72 3D */	bl func_80068E98
/* 80031C60 0002E840  90 7E 00 B4 */	stw r3, 0xb4(r30)
/* 80031C64 0002E844  80 1E 00 00 */	lwz r0, 0(r30)
/* 80031C68 0002E848  2C 00 00 01 */	cmpwi r0, 1
/* 80031C6C 0002E84C  41 82 00 0C */	beq lbl_80031C78
/* 80031C70 0002E850  38 00 00 02 */	li r0, 2
/* 80031C74 0002E854  90 1E 00 00 */	stw r0, 0(r30)
lbl_80031C78:
/* 80031C78 0002E858  80 1E 00 00 */	lwz r0, 0(r30)
/* 80031C7C 0002E85C  2C 00 00 02 */	cmpwi r0, 2
/* 80031C80 0002E860  40 82 00 1C */	bne lbl_80031C9C
/* 80031C84 0002E864  81 9E 00 B8 */	lwz r12, 0xb8(r30)
/* 80031C88 0002E868  28 0C 00 00 */	cmplwi r12, 0
/* 80031C8C 0002E86C  41 82 00 10 */	beq lbl_80031C9C
/* 80031C90 0002E870  7D 88 03 A6 */	mtlr r12
/* 80031C94 0002E874  38 7C 00 00 */	addi r3, r28, 0
/* 80031C98 0002E878  4E 80 00 21 */	blrl 
lbl_80031C9C:
/* 80031C9C 0002E87C  BB 61 00 34 */	lmw r27, 0x34(r1)
/* 80031CA0 0002E880  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 80031CA4 0002E884  38 21 00 48 */	addi r1, r1, 0x48
/* 80031CA8 0002E888  7C 08 03 A6 */	mtlr r0
/* 80031CAC 0002E88C  4E 80 00 20 */	blr 
}

#ifdef NON_MATCHING
void Player_80031CB0(s32 id, s32 slot) {
    if (lbl_803BCDE0[id].x != -1) {
        func_800855C8(lbl_803BCDE0[id].x, slot);
    }
    if (lbl_803BCDE0[id].y != -1) {
        func_800855C8(lbl_803BCDE0[id].y, slot);
    }
}
#else
asm void Player_80031CB0(s32 id, s32 slot)
{
    nofralloc
/* 80031CB0 0002E890  7C 08 02 A6 */	mflr r0
/* 80031CB4 0002E894  90 01 00 04 */	stw r0, 4(r1)
/* 80031CB8 0002E898  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80031CBC 0002E89C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80031CC0 0002E8A0  1F E3 00 03 */	mulli r31, r3, 3
/* 80031CC4 0002E8A4  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80031CC8 0002E8A8  3C 60 80 3C */	lis r3, lbl_803BCDE0
/* 80031CCC 0002E8AC  38 03 CD E0 */	addi r0, r3, lbl_803BCDE0
/* 80031CD0 0002E8B0  7C 60 FA 14 */	add r3, r0, r31
/* 80031CD4 0002E8B4  88 03 00 00 */	lbz r0, 0(r3)
/* 80031CD8 0002E8B8  3B C4 00 00 */	addi r30, r4, 0
/* 80031CDC 0002E8BC  7C 03 07 74 */	extsb r3, r0
/* 80031CE0 0002E8C0  2C 03 FF FF */	cmpwi r3, -1
/* 80031CE4 0002E8C4  41 82 00 0C */	beq lbl_80031CF0
/* 80031CE8 0002E8C8  7F C4 F3 78 */	mr r4, r30
/* 80031CEC 0002E8CC  48 05 38 DD */	bl func_800855C8
lbl_80031CF0:
/* 80031CF0 0002E8D0  3C 60 80 3C */	lis r3, lbl_803BCDE0
/* 80031CF4 0002E8D4  38 03 CD E0 */	addi r0, r3, lbl_803BCDE0
/* 80031CF8 0002E8D8  7C 60 FA 14 */	add r3, r0, r31
/* 80031CFC 0002E8DC  88 03 00 01 */	lbz r0, 1(r3)
/* 80031D00 0002E8E0  7C 03 07 74 */	extsb r3, r0
/* 80031D04 0002E8E4  2C 03 FF FF */	cmpwi r3, -1
/* 80031D08 0002E8E8  41 82 00 0C */	beq lbl_80031D14
/* 80031D0C 0002E8EC  7F C4 F3 78 */	mr r4, r30
/* 80031D10 0002E8F0  48 05 38 B9 */	bl func_800855C8
lbl_80031D14:
/* 80031D14 0002E8F4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80031D18 0002E8F8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80031D1C 0002E8FC  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80031D20 0002E900  38 21 00 18 */	addi r1, r1, 0x18
/* 80031D24 0002E904  7C 08 03 A6 */	mtlr r0
/* 80031D28 0002E908  4E 80 00 20 */	blr 
}
#endif


#ifdef NON_MATCHING
void Player_80031D2C(s32 id, s32 slot) {
    if (lbl_803BCDE0[id].x != -1) {
        func_8008578C(lbl_803BCDE0[id].x, slot);
    }
    if (lbl_803BCDE0[id].y != -1) {
        func_8008578C(lbl_803BCDE0[id].y, slot);
    }
}
#else
asm void Player_80031D2C(s32 id, s32 slot)
{
    nofralloc
/* 80031D2C 0002E90C  7C 08 02 A6 */	mflr r0
/* 80031D30 0002E910  90 01 00 04 */	stw r0, 4(r1)
/* 80031D34 0002E914  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80031D38 0002E918  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80031D3C 0002E91C  1F E3 00 03 */	mulli r31, r3, 3
/* 80031D40 0002E920  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80031D44 0002E924  3C 60 80 3C */	lis r3, lbl_803BCDE0@ha
/* 80031D48 0002E928  38 03 CD E0 */	addi r0, r3, lbl_803BCDE0@l
/* 80031D4C 0002E92C  7C 60 FA 14 */	add r3, r0, r31
/* 80031D50 0002E930  88 03 00 00 */	lbz r0, 0(r3)
/* 80031D54 0002E934  3B C4 00 00 */	addi r30, r4, 0
/* 80031D58 0002E938  7C 03 07 74 */	extsb r3, r0
/* 80031D5C 0002E93C  2C 03 FF FF */	cmpwi r3, -1
/* 80031D60 0002E940  41 82 00 0C */	beq lbl_80031D6C
/* 80031D64 0002E944  7F C4 F3 78 */	mr r4, r30
/* 80031D68 0002E948  48 05 3A 25 */	bl func_8008578C
lbl_80031D6C:
/* 80031D6C 0002E94C  3C 60 80 3C */	lis r3, lbl_803BCDE0@ha
/* 80031D70 0002E950  38 03 CD E0 */	addi r0, r3, lbl_803BCDE0@l
/* 80031D74 0002E954  7C 60 FA 14 */	add r3, r0, r31
/* 80031D78 0002E958  88 03 00 01 */	lbz r0, 1(r3)
/* 80031D7C 0002E95C  7C 03 07 74 */	extsb r3, r0
/* 80031D80 0002E960  2C 03 FF FF */	cmpwi r3, -1
/* 80031D84 0002E964  41 82 00 0C */	beq lbl_80031D90
/* 80031D88 0002E968  7F C4 F3 78 */	mr r4, r30
/* 80031D8C 0002E96C  48 05 3A 01 */	bl func_8008578C
lbl_80031D90:
/* 80031D90 0002E970  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80031D94 0002E974  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80031D98 0002E978  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80031D9C 0002E97C  38 21 00 18 */	addi r1, r1, 0x18
/* 80031DA0 0002E980  7C 08 03 A6 */	mtlr r0
/* 80031DA4 0002E984  4E 80 00 20 */	blr 
}
#endif

void Player_80031DA8(s32 param_1, s32 param_2)
{
    func_800EED50(param_1, param_2);
}

#ifdef NON_MATCHING
inline checkNegOne(s8* num) { return *num != -1; }

void Player_80031DC8(void func_arg(s32, s32)) {   ////https://decomp.me/scratch/Iq3tA
    s32 slot;
    for (slot = 0; slot < 6; slot++) {
        Player_CheckSlot(slot);

        if (player_slots[slot].player_state) {
            func_arg(((struct Unk_Struct_w_Array*) &lbl_803BCDC0)->vec_arr[player_slots[slot].player_character].x, 0);
            if (checkNegOne(&((struct Unk_Struct_w_Array*) &lbl_803BCDC0)->vec_arr[player_slots[slot].player_character].y)) {
                func_arg(((struct Unk_Struct_w_Array*) &lbl_803BCDC0)->vec_arr[player_slots[slot].player_character].y, 0);
            }
        }
    }
}
#else
asm void Player_80031DC8()
{
    nofralloc
    /* 80031DC8 0002E9A8  7C 08 02 A6 */	mflr r0
    /* 80031DCC 0002E9AC  3C 80 80 45 */	lis r4, player_slots@ha
    /* 80031DD0 0002E9B0  90 01 00 04 */	stw r0, 4(r1)
    /* 80031DD4 0002E9B4  94 21 FF E0 */	stwu r1, -0x20(r1)
    /* 80031DD8 0002E9B8  93 E1 00 1C */	stw r31, 0x1c(r1)
    /* 80031DDC 0002E9BC  93 C1 00 18 */	stw r30, 0x18(r1)
    /* 80031DE0 0002E9C0  3B C4 30 80 */	addi r30, r4, player_slots@l
    /* 80031DE4 0002E9C4  3C 80 80 3C */	lis r4, lbl_803BCDC0@ha
    /* 80031DE8 0002E9C8  93 A1 00 14 */	stw r29, 0x14(r1)
    /* 80031DEC 0002E9CC  3B E4 CD C0 */	addi r31, r4, lbl_803BCDC0@l
    /* 80031DF0 0002E9D0  3B A0 00 00 */	li r29, 0
    /* 80031DF4 0002E9D4  93 81 00 10 */	stw r28, 0x10(r1)
    /* 80031DF8 0002E9D8  3B 83 00 00 */	addi r28, r3, 0
    lbl_80031DFC:
    /* 80031DFC 0002E9DC  2C 1D 00 00 */	cmpwi r29, 0
    /* 80031E00 0002E9E0  41 80 00 0C */	blt lbl_80031E0C
    /* 80031E04 0002E9E4  2C 1D 00 06 */	cmpwi r29, 6
    /* 80031E08 0002E9E8  41 80 00 24 */	blt lbl_80031E2C
    lbl_80031E0C:
    /* 80031E0C 0002E9EC  38 9D 00 00 */	addi r4, r29, 0
    /* 80031E10 0002E9F0  4C C6 31 82 */	crclr 6
    /* 80031E14 0002E9F4  38 7F 00 84 */	addi r3, r31, 0x84
    /* 80031E18 0002E9F8  48 31 38 91 */	bl OSReport
    /* 80031E1C 0002E9FC  38 7F 00 A0 */	addi r3, r31, 0xa0
    /* 80031E20 0002EA00  38 80 00 66 */	li r4, 0x66
    /* 80031E24 0002EA04  38 AD 82 A0 */	addi r5, r13, lbl_804D3940
    /* 80031E28 0002EA08  48 35 63 F9 */	bl __assert
    lbl_80031E2C:
    /* 80031E2C 0002EA0C  80 1E 00 00 */	lwz r0, 0(r30)
    /* 80031E30 0002EA10  2C 00 00 00 */	cmpwi r0, 0
    /* 80031E34 0002EA14  41 82 00 58 */	beq lbl_80031E8C
    /* 80031E38 0002EA18  80 1E 00 04 */	lwz r0, 4(r30)
    /* 80031E3C 0002EA1C  39 9C 00 00 */	addi r12, r28, 0
    /* 80031E40 0002EA20  7D 88 03 A6 */	mtlr r12
    /* 80031E44 0002EA24  38 80 00 00 */	li r4, 0
    /* 80031E48 0002EA28  1C 00 00 03 */	mulli r0, r0, 3
    /* 80031E4C 0002EA2C  7C 7F 02 14 */	add r3, r31, r0
    /* 80031E50 0002EA30  88 63 00 20 */	lbz r3, 0x20(r3)
    /* 80031E54 0002EA34  7C 63 07 74 */	extsb r3, r3
    /* 80031E58 0002EA38  4E 80 00 21 */	blrl 
    /* 80031E5C 0002EA3C  80 1E 00 04 */	lwz r0, 4(r30)
    /* 80031E60 0002EA40  1C 00 00 03 */	mulli r0, r0, 3
    /* 80031E64 0002EA44  7C 7F 02 14 */	add r3, r31, r0
    /* 80031E68 0002EA48  88 63 00 21 */	lbz r3, 0x21(r3)
    /* 80031E6C 0002EA4C  7C 60 07 74 */	extsb r0, r3
    /* 80031E70 0002EA50  2C 00 FF FF */	cmpwi r0, -1
    /* 80031E74 0002EA54  41 82 00 18 */	beq lbl_80031E8C
    /* 80031E78 0002EA58  39 9C 00 00 */	addi r12, r28, 0
    /* 80031E7C 0002EA5C  7D 88 03 A6 */	mtlr r12
    /* 80031E80 0002EA60  7C 63 07 74 */	extsb r3, r3
    /* 80031E84 0002EA64  38 80 00 00 */	li r4, 0
    /* 80031E88 0002EA68  4E 80 00 21 */	blrl 
    lbl_80031E8C:
    /* 80031E8C 0002EA6C  3B BD 00 01 */	addi r29, r29, 1
    /* 80031E90 0002EA70  2C 1D 00 06 */	cmpwi r29, 6
    /* 80031E94 0002EA74  3B DE 0E 90 */	addi r30, r30, 0xe90
    /* 80031E98 0002EA78  41 80 FF 64 */	blt lbl_80031DFC
    /* 80031E9C 0002EA7C  80 01 00 24 */	lwz r0, 0x24(r1)
    /* 80031EA0 0002EA80  83 E1 00 1C */	lwz r31, 0x1c(r1)
    /* 80031EA4 0002EA84  83 C1 00 18 */	lwz r30, 0x18(r1)
    /* 80031EA8 0002EA88  83 A1 00 14 */	lwz r29, 0x14(r1)
    /* 80031EAC 0002EA8C  83 81 00 10 */	lwz r28, 0x10(r1)
    /* 80031EB0 0002EA90  38 21 00 20 */	addi r1, r1, 0x20
    /* 80031EB4 0002EA94  7C 08 03 A6 */	mtlr r0
    /* 80031EB8 0002EA98  4E 80 00 20 */	blr 
}
#endif

#ifdef NON_MATCHING
void Player_80031EBC(s32 slot) { ///https://decomp.me/scratch/XYDYq

    s32 i;
    Player_CheckSlot(slot);

    for (i = 0; i < 2; i++) {
        StaticPlayer*player = &player_slots[slot];
        if ((player->player_entity[player->transformed[i]])) {
            if (!func_8008701C(player->player_entity[player->transformed[i]])) {
                func_800D4F24(player->player_entity[player->transformed[i]], 1);
            }
            func_80390228(player->player_entity[player->transformed[i]]);
        }
    }

}
#else
asm void Player_80031EBC()
{
    nofralloc
    /* 80031EBC 0002EA9C  7C 08 02 A6 */	mflr r0
    /* 80031EC0 0002EAA0  90 01 00 04 */	stw r0, 4(r1)
    /* 80031EC4 0002EAA4  94 21 FF E0 */	stwu r1, -0x20(r1)
    /* 80031EC8 0002EAA8  93 E1 00 1C */	stw r31, 0x1c(r1)
    /* 80031ECC 0002EAAC  93 C1 00 18 */	stw r30, 0x18(r1)
    /* 80031ED0 0002EAB0  93 A1 00 14 */	stw r29, 0x14(r1)
    /* 80031ED4 0002EAB4  7C 7D 1B 79 */	or. r29, r3, r3
    /* 80031ED8 0002EAB8  41 80 00 0C */	blt lbl_80031EE4
    /* 80031EDC 0002EABC  2C 1D 00 06 */	cmpwi r29, 6
    /* 80031EE0 0002EAC0  41 80 00 2C */	blt lbl_80031F0C
    lbl_80031EE4:
    /* 80031EE4 0002EAC4  3C 60 80 3C */	lis r3, lbl_803BCE44@ha
    /* 80031EE8 0002EAC8  4C C6 31 82 */	crclr 6
    /* 80031EEC 0002EACC  38 63 CE 44 */	addi r3, r3, lbl_803BCE44@l
    /* 80031EF0 0002EAD0  38 9D 00 00 */	addi r4, r29, 0
    /* 80031EF4 0002EAD4  48 31 37 B5 */	bl OSReport
    /* 80031EF8 0002EAD8  3C 60 80 3C */	lis r3, lbl_803BCE60@ha
    /* 80031EFC 0002EADC  38 63 CE 60 */	addi r3, r3, lbl_803BCE60@l
    /* 80031F00 0002EAE0  38 80 00 66 */	li r4, 0x66
    /* 80031F04 0002EAE4  38 AD 82 A0 */	addi r5, r13, lbl_804D3940
    /* 80031F08 0002EAE8  48 35 63 19 */	bl __assert
    lbl_80031F0C:
    /* 80031F0C 0002EAEC  1C 9D 0E 90 */	mulli r4, r29, 0xe90
    /* 80031F10 0002EAF0  3C 60 80 45 */	lis r3, player_slots@ha
    /* 80031F14 0002EAF4  38 03 30 80 */	addi r0, r3, player_slots@l
    /* 80031F18 0002EAF8  7F E0 22 14 */	add r31, r0, r4
    /* 80031F1C 0002EAFC  3B A0 00 00 */	li r29, 0
    lbl_80031F20:
    /* 80031F20 0002EB00  38 9D 00 0C */	addi r4, r29, 0xc
    /* 80031F24 0002EB04  7C 1F 20 AE */	lbzx r0, r31, r4
    /* 80031F28 0002EB08  54 03 10 3A */	slwi r3, r0, 2
    /* 80031F2C 0002EB0C  38 03 00 B0 */	addi r0, r3, 0xb0
    /* 80031F30 0002EB10  7C 1F 00 2E */	lwzx r0, r31, r0
    /* 80031F34 0002EB14  28 00 00 00 */	cmplwi r0, 0
    /* 80031F38 0002EB18  41 82 00 50 */	beq lbl_80031F88
    /* 80031F3C 0002EB1C  7F DF 22 14 */	add r30, r31, r4
    /* 80031F40 0002EB20  88 1E 00 00 */	lbz r0, 0(r30)
    /* 80031F44 0002EB24  54 03 10 3A */	slwi r3, r0, 2
    /* 80031F48 0002EB28  38 03 00 B0 */	addi r0, r3, 0xb0
    /* 80031F4C 0002EB2C  7C 7F 00 2E */	lwzx r3, r31, r0
    /* 80031F50 0002EB30  48 05 50 CD */	bl func_8008701C
    /* 80031F54 0002EB34  2C 03 00 00 */	cmpwi r3, 0
    /* 80031F58 0002EB38  40 82 00 1C */	bne lbl_80031F74
    /* 80031F5C 0002EB3C  88 1E 00 00 */	lbz r0, 0(r30)
    /* 80031F60 0002EB40  38 80 00 01 */	li r4, 1
    /* 80031F64 0002EB44  54 03 10 3A */	slwi r3, r0, 2
    /* 80031F68 0002EB48  38 03 00 B0 */	addi r0, r3, 0xb0
    /* 80031F6C 0002EB4C  7C 7F 00 2E */	lwzx r3, r31, r0
    /* 80031F70 0002EB50  48 0A 2F B5 */	bl func_800D4F24
    lbl_80031F74:
    /* 80031F74 0002EB54  88 1E 00 00 */	lbz r0, 0(r30)
    /* 80031F78 0002EB58  54 03 10 3A */	slwi r3, r0, 2
    /* 80031F7C 0002EB5C  38 03 00 B0 */	addi r0, r3, 0xb0
    /* 80031F80 0002EB60  7C 7F 00 2E */	lwzx r3, r31, r0
    /* 80031F84 0002EB64  48 35 E2 A5 */	bl func_80390228
    lbl_80031F88:
    /* 80031F88 0002EB68  3B BD 00 01 */	addi r29, r29, 1
    /* 80031F8C 0002EB6C  2C 1D 00 02 */	cmpwi r29, 2
    /* 80031F90 0002EB70  41 80 FF 90 */	blt lbl_80031F20
    /* 80031F94 0002EB74  80 01 00 24 */	lwz r0, 0x24(r1)
    /* 80031F98 0002EB78  83 E1 00 1C */	lwz r31, 0x1c(r1)
    /* 80031F9C 0002EB7C  83 C1 00 18 */	lwz r30, 0x18(r1)
    /* 80031FA0 0002EB80  83 A1 00 14 */	lwz r29, 0x14(r1)
    /* 80031FA4 0002EB84  38 21 00 20 */	addi r1, r1, 0x20
    /* 80031FA8 0002EB88  7C 08 03 A6 */	mtlr r0
    /* 80031FAC 0002EB8C  4E 80 00 20 */	blr 
}
#endif

#ifdef NON_MATCHING
void Player_80031FB0(s32 slot, s32 entity_index) { //https://decomp.me/scratch/5EHKN

    s32 unused;
    StaticPlayer* player;
    Player_CheckSlot(slot);

    player = &player_slots[slot];
    player->player_entity[player->transformed[entity_index]] = 0;
    if (((player->flags >> 5) & 0x1) == 0 || (Player_800319C4(slot, 0) != 0)) {
        player->player_state = 0;
    }
}
#else
asm void Player_80031FB0()
{
    nofralloc
    /* 80031FB0 0002EB90  7C 08 02 A6 */	mflr r0
    /* 80031FB4 0002EB94  90 01 00 04 */	stw r0, 4(r1)
    /* 80031FB8 0002EB98  94 21 FF D8 */	stwu r1, -0x28(r1)
    /* 80031FBC 0002EB9C  93 E1 00 24 */	stw r31, 0x24(r1)
    /* 80031FC0 0002EBA0  93 C1 00 20 */	stw r30, 0x20(r1)
    /* 80031FC4 0002EBA4  3B C4 00 00 */	addi r30, r4, 0
    /* 80031FC8 0002EBA8  93 A1 00 1C */	stw r29, 0x1c(r1)
    /* 80031FCC 0002EBAC  7C 7D 1B 79 */	or. r29, r3, r3
    /* 80031FD0 0002EBB0  41 80 00 0C */	blt lbl_80031FDC
    /* 80031FD4 0002EBB4  2C 1D 00 06 */	cmpwi r29, 6
    /* 80031FD8 0002EBB8  41 80 00 2C */	blt lbl_80032004
    lbl_80031FDC:
    /* 80031FDC 0002EBBC  3C 60 80 3C */	lis r3, lbl_803BCE44@ha
    /* 80031FE0 0002EBC0  4C C6 31 82 */	crclr 6
    /* 80031FE4 0002EBC4  38 63 CE 44 */	addi r3, r3, lbl_803BCE44@l
    /* 80031FE8 0002EBC8  38 9D 00 00 */	addi r4, r29, 0
    /* 80031FEC 0002EBCC  48 31 36 BD */	bl OSReport
    /* 80031FF0 0002EBD0  3C 60 80 3C */	lis r3, lbl_803BCE60@ha
    /* 80031FF4 0002EBD4  38 63 CE 60 */	addi r3, r3, lbl_803BCE60@l
    /* 80031FF8 0002EBD8  38 80 00 66 */	li r4, 0x66
    /* 80031FFC 0002EBDC  38 AD 82 A0 */	addi r5, r13, lbl_804D3940
    /* 80032000 0002EBE0  48 35 62 21 */	bl __assert
    lbl_80032004:
    /* 80032004 0002EBE4  1C 9D 0E 90 */	mulli r4, r29, 0xe90
    /* 80032008 0002EBE8  3C 60 80 45 */	lis r3, player_slots@ha
    /* 8003200C 0002EBEC  38 03 30 80 */	addi r0, r3, player_slots@l
    /* 80032010 0002EBF0  7F E0 22 14 */	add r31, r0, r4
    /* 80032014 0002EBF4  7C 7F F2 14 */	add r3, r31, r30
    /* 80032018 0002EBF8  88 03 00 0C */	lbz r0, 0xc(r3)
    /* 8003201C 0002EBFC  38 80 00 00 */	li r4, 0
    /* 80032020 0002EC00  54 00 10 3A */	slwi r0, r0, 2
    /* 80032024 0002EC04  7C 7F 02 14 */	add r3, r31, r0
    /* 80032028 0002EC08  90 83 00 B0 */	stw r4, 0xb0(r3)
    /* 8003202C 0002EC0C  88 1F 00 AC */	lbz r0, 0xac(r31)
    /* 80032030 0002EC10  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
    /* 80032034 0002EC14  41 82 00 18 */	beq lbl_8003204C
    /* 80032038 0002EC18  38 7D 00 00 */	addi r3, r29, 0
    /* 8003203C 0002EC1C  38 80 00 00 */	li r4, 0
    /* 80032040 0002EC20  4B FF F9 85 */	bl Player_800319C4
    /* 80032044 0002EC24  2C 03 00 00 */	cmpwi r3, 0
    /* 80032048 0002EC28  41 82 00 0C */	beq lbl_80032054
    lbl_8003204C:
    /* 8003204C 0002EC2C  38 00 00 00 */	li r0, 0
    /* 80032050 0002EC30  90 1F 00 00 */	stw r0, 0(r31)
    lbl_80032054:
    /* 80032054 0002EC34  80 01 00 2C */	lwz r0, 0x2c(r1)
    /* 80032058 0002EC38  83 E1 00 24 */	lwz r31, 0x24(r1)
    /* 8003205C 0002EC3C  83 C1 00 20 */	lwz r30, 0x20(r1)
    /* 80032060 0002EC40  83 A1 00 1C */	lwz r29, 0x1c(r1)
    /* 80032064 0002EC44  38 21 00 28 */	addi r1, r1, 0x28
    /* 80032068 0002EC48  7C 08 03 A6 */	mtlr r0
    /* 8003206C 0002EC4C  4E 80 00 20 */	blr 
}
#endif

#ifdef NON_MATCHING
void Player_80032070(s32 slot, BOOL bool_arg) {   ////https://decomp.me/scratch/HuE3T
    StaticPlayer* player;
    struct Unk_Struct_w_Array* unkStruct = (struct Unk_Struct_w_Array*) &lbl_803BCDC0;
    Player_CheckSlot(slot);
    player = &player_slots[slot];

    
    if (bool_arg == 0) {
        func_800D4FF4(player->player_entity[player->transformed[0]]);
        if(((player->flags >> 5) & 0x1) 
                && unkStruct->vec_arr[player->player_character].z == 0 
                && func_8008701C(player->player_entity[player->transformed[1]])) 
        {
            func_800D4FF4(player->player_entity[player->transformed[1]]);
        }
        func_802F6E1C(slot);
        return;
    }

    if (func_800873CC(player->player_entity[player->transformed[0]])) {
        func_800D4FF4(player->player_entity[player->transformed[1]]);
    }
}
#else
asm void Player_80032070()
{
    nofralloc
    /* 80032070 0002EC50  7C 08 02 A6 */	mflr r0
    /* 80032074 0002EC54  90 01 00 04 */	stw r0, 4(r1)
    /* 80032078 0002EC58  94 21 FF E0 */	stwu r1, -0x20(r1)
    /* 8003207C 0002EC5C  93 E1 00 1C */	stw r31, 0x1c(r1)
    /* 80032080 0002EC60  3B E4 00 00 */	addi r31, r4, 0
    /* 80032084 0002EC64  93 C1 00 18 */	stw r30, 0x18(r1)
    /* 80032088 0002EC68  7C 7E 1B 79 */	or. r30, r3, r3
    /* 8003208C 0002EC6C  3C 60 80 3C */	lis r3, lbl_803BCDC0@ha
    /* 80032090 0002EC70  93 A1 00 14 */	stw r29, 0x14(r1)
    /* 80032094 0002EC74  3B A3 CD C0 */	addi r29, r3, lbl_803BCDC0@l
    /* 80032098 0002EC78  41 80 00 0C */	blt lbl_800320A4
    /* 8003209C 0002EC7C  2C 1E 00 06 */	cmpwi r30, 6
    /* 800320A0 0002EC80  41 80 00 24 */	blt lbl_800320C4
    lbl_800320A4:
    /* 800320A4 0002EC84  38 9E 00 00 */	addi r4, r30, 0
    /* 800320A8 0002EC88  4C C6 31 82 */	crclr 6
    /* 800320AC 0002EC8C  38 7D 00 84 */	addi r3, r29, 0x84
    /* 800320B0 0002EC90  48 31 35 F9 */	bl OSReport
    /* 800320B4 0002EC94  38 7D 00 A0 */	addi r3, r29, 0xa0
    /* 800320B8 0002EC98  38 80 00 66 */	li r4, 0x66
    /* 800320BC 0002EC9C  38 AD 82 A0 */	addi r5, r13, lbl_804D3940
    /* 800320C0 0002ECA0  48 35 61 61 */	bl __assert
    lbl_800320C4:
    /* 800320C4 0002ECA4  1C 9E 0E 90 */	mulli r4, r30, 0xe90
    /* 800320C8 0002ECA8  3C 60 80 45 */	lis r3, player_slots@ha
    /* 800320CC 0002ECAC  38 03 30 80 */	addi r0, r3, player_slots@l
    /* 800320D0 0002ECB0  2C 1F 00 00 */	cmpwi r31, 0
    /* 800320D4 0002ECB4  7F E0 22 14 */	add r31, r0, r4
    /* 800320D8 0002ECB8  40 82 00 78 */	bne lbl_80032150
    /* 800320DC 0002ECBC  88 1F 00 0C */	lbz r0, 0xc(r31)
    /* 800320E0 0002ECC0  54 00 10 3A */	slwi r0, r0, 2
    /* 800320E4 0002ECC4  7C 7F 02 14 */	add r3, r31, r0
    /* 800320E8 0002ECC8  80 63 00 B0 */	lwz r3, 0xb0(r3)
    /* 800320EC 0002ECCC  48 0A 2F 09 */	bl func_800D4FF4
    /* 800320F0 0002ECD0  88 1F 00 AC */	lbz r0, 0xac(r31)
    /* 800320F4 0002ECD4  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
    /* 800320F8 0002ECD8  41 82 00 4C */	beq lbl_80032144
    /* 800320FC 0002ECDC  80 1F 00 04 */	lwz r0, 4(r31)
    /* 80032100 0002ECE0  1C 00 00 03 */	mulli r0, r0, 3
    /* 80032104 0002ECE4  7C 7D 02 14 */	add r3, r29, r0
    /* 80032108 0002ECE8  88 03 00 22 */	lbz r0, 0x22(r3)
    /* 8003210C 0002ECEC  7C 00 07 75 */	extsb. r0, r0
    /* 80032110 0002ECF0  40 82 00 34 */	bne lbl_80032144
    /* 80032114 0002ECF4  88 1F 00 0D */	lbz r0, 0xd(r31)
    /* 80032118 0002ECF8  54 00 10 3A */	slwi r0, r0, 2
    /* 8003211C 0002ECFC  7C 7F 02 14 */	add r3, r31, r0
    /* 80032120 0002ED00  80 63 00 B0 */	lwz r3, 0xb0(r3)
    /* 80032124 0002ED04  48 05 4E F9 */	bl func_8008701C
    /* 80032128 0002ED08  2C 03 00 00 */	cmpwi r3, 0
    /* 8003212C 0002ED0C  41 82 00 18 */	beq lbl_80032144
    /* 80032130 0002ED10  88 1F 00 0D */	lbz r0, 0xd(r31)
    /* 80032134 0002ED14  54 00 10 3A */	slwi r0, r0, 2
    /* 80032138 0002ED18  7C 7F 02 14 */	add r3, r31, r0
    /* 8003213C 0002ED1C  80 63 00 B0 */	lwz r3, 0xb0(r3)
    /* 80032140 0002ED20  48 0A 2E B5 */	bl func_800D4FF4
    lbl_80032144:
    /* 80032144 0002ED24  7F C3 F3 78 */	mr r3, r30
    /* 80032148 0002ED28  48 2C 4C D5 */	bl func_802F6E1C
    /* 8003214C 0002ED2C  48 00 00 34 */	b lbl_80032180
    lbl_80032150:
    /* 80032150 0002ED30  88 1F 00 0C */	lbz r0, 0xc(r31)
    /* 80032154 0002ED34  54 00 10 3A */	slwi r0, r0, 2
    /* 80032158 0002ED38  7C 7F 02 14 */	add r3, r31, r0
    /* 8003215C 0002ED3C  80 63 00 B0 */	lwz r3, 0xb0(r3)
    /* 80032160 0002ED40  48 05 52 6D */	bl func_800873CC
    /* 80032164 0002ED44  2C 03 00 00 */	cmpwi r3, 0
    /* 80032168 0002ED48  41 82 00 18 */	beq lbl_80032180
    /* 8003216C 0002ED4C  88 1F 00 0D */	lbz r0, 0xd(r31)
    /* 80032170 0002ED50  54 00 10 3A */	slwi r0, r0, 2
    /* 80032174 0002ED54  7C 7F 02 14 */	add r3, r31, r0
    /* 80032178 0002ED58  80 63 00 B0 */	lwz r3, 0xb0(r3)
    /* 8003217C 0002ED5C  48 0A 2E 79 */	bl func_800D4FF4
    lbl_80032180:
    /* 80032180 0002ED60  80 01 00 24 */	lwz r0, 0x24(r1)
    /* 80032184 0002ED64  83 E1 00 1C */	lwz r31, 0x1c(r1)
    /* 80032188 0002ED68  83 C1 00 18 */	lwz r30, 0x18(r1)
    /* 8003218C 0002ED6C  83 A1 00 14 */	lwz r29, 0x14(r1)
    /* 80032190 0002ED70  38 21 00 20 */	addi r1, r1, 0x20
    /* 80032194 0002ED74  7C 08 03 A6 */	mtlr r0
    /* 80032198 0002ED78  4E 80 00 20 */	blr 
}
#endif


#ifdef NON_MATCHING
void Player_8003219C(s32 slot) {   ///https://decomp.me/scratch/q6dzH
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    func_8008701C(player->player_entity[player->transformed[0]]);
}
#else
asm void Player_8003219C()
{
    nofralloc
    /* 8003219C 0002ED7C  7C 08 02 A6 */	mflr r0
    /* 800321A0 0002ED80  90 01 00 04 */	stw r0, 4(r1)
    /* 800321A4 0002ED84  94 21 FF E8 */	stwu r1, -0x18(r1)
    /* 800321A8 0002ED88  93 E1 00 14 */	stw r31, 0x14(r1)
    /* 800321AC 0002ED8C  7C 7F 1B 79 */	or. r31, r3, r3
    /* 800321B0 0002ED90  41 80 00 0C */	blt lbl_800321BC
    /* 800321B4 0002ED94  2C 1F 00 06 */	cmpwi r31, 6
    /* 800321B8 0002ED98  41 80 00 2C */	blt lbl_800321E4
    lbl_800321BC:
    /* 800321BC 0002ED9C  3C 60 80 3C */	lis r3, lbl_803BCE44@ha
    /* 800321C0 0002EDA0  4C C6 31 82 */	crclr 6
    /* 800321C4 0002EDA4  38 63 CE 44 */	addi r3, r3, lbl_803BCE44@l
    /* 800321C8 0002EDA8  38 9F 00 00 */	addi r4, r31, 0
    /* 800321CC 0002EDAC  48 31 34 DD */	bl OSReport
    /* 800321D0 0002EDB0  3C 60 80 3C */	lis r3, lbl_803BCE60@ha
    /* 800321D4 0002EDB4  38 63 CE 60 */	addi r3, r3, lbl_803BCE60@l
    /* 800321D8 0002EDB8  38 80 00 66 */	li r4, 0x66
    /* 800321DC 0002EDBC  38 AD 82 A0 */	addi r5, r13, lbl_804D3940
    /* 800321E0 0002EDC0  48 35 60 41 */	bl __assert
    lbl_800321E4:
    /* 800321E4 0002EDC4  1C 9F 0E 90 */	mulli r4, r31, 0xe90
    /* 800321E8 0002EDC8  3C 60 80 45 */	lis r3, player_slots@ha
    /* 800321EC 0002EDCC  38 03 30 80 */	addi r0, r3, player_slots@l
    /* 800321F0 0002EDD0  7C 60 22 14 */	add r3, r0, r4
    /* 800321F4 0002EDD4  88 03 00 0C */	lbz r0, 0xc(r3)
    /* 800321F8 0002EDD8  54 00 10 3A */	slwi r0, r0, 2
    /* 800321FC 0002EDDC  7C 63 02 14 */	add r3, r3, r0
    /* 80032200 0002EDE0  80 63 00 B0 */	lwz r3, 0xb0(r3)
    /* 80032204 0002EDE4  48 05 4E 19 */	bl func_8008701C
    /* 80032208 0002EDE8  80 01 00 1C */	lwz r0, 0x1c(r1)
    /* 8003220C 0002EDEC  83 E1 00 14 */	lwz r31, 0x14(r1)
    /* 80032210 0002EDF0  38 21 00 18 */	addi r1, r1, 0x18
    /* 80032214 0002EDF4  7C 08 03 A6 */	mtlr r0
    /* 80032218 0002EDF8  4E 80 00 20 */	blr 

}
#endif

#ifdef NON_MATCHING
BOOL Player_8003221C(s32 slot) {    //// https://decomp.me/scratch/jpxOM

    StaticPlayer* player;

    if (Player_GetPlayerState(slot) == 2) {   ///2 means in-game
        Player_CheckSlot(slot);
        player = &player_slots[slot];

        if (!func_8008701C(player->player_entity[player->transformed[0]])) {
            return 1;
        }

    }

    return 0;
}
#else
asm void Player_8003219C()
{
    nofralloc
    /* 8003221C 0002EDFC  7C 08 02 A6 */	mflr r0
    /* 80032220 0002EE00  90 01 00 04 */	stw r0, 4(r1)
    /* 80032224 0002EE04  94 21 FF E8 */	stwu r1, -0x18(r1)
    /* 80032228 0002EE08  93 E1 00 14 */	stw r31, 0x14(r1)
    /* 8003222C 0002EE0C  7C 7F 1B 78 */	mr r31, r3
    /* 80032230 0002EE10  48 00 00 91 */	bl Player_GetPlayerState
    /* 80032234 0002EE14  2C 03 00 02 */	cmpwi r3, 2
    /* 80032238 0002EE18  40 82 00 70 */	bne lbl_800322A8
    /* 8003223C 0002EE1C  2C 1F 00 00 */	cmpwi r31, 0
    /* 80032240 0002EE20  41 80 00 0C */	blt lbl_8003224C
    /* 80032244 0002EE24  2C 1F 00 06 */	cmpwi r31, 6
    /* 80032248 0002EE28  41 80 00 2C */	blt lbl_80032274
    lbl_8003224C:
    /* 8003224C 0002EE2C  3C 60 80 3C */	lis r3, lbl_803BCE44@ha
    /* 80032250 0002EE30  4C C6 31 82 */	crclr 6
    /* 80032254 0002EE34  38 63 CE 44 */	addi r3, r3, lbl_803BCE44@l
    /* 80032258 0002EE38  38 9F 00 00 */	addi r4, r31, 0
    /* 8003225C 0002EE3C  48 31 34 4D */	bl OSReport
    /* 80032260 0002EE40  3C 60 80 3C */	lis r3, lbl_803BCE60@ha
    /* 80032264 0002EE44  38 63 CE 60 */	addi r3, r3, lbl_803BCE60@l
    /* 80032268 0002EE48  38 80 00 66 */	li r4, 0x66
    /* 8003226C 0002EE4C  38 AD 82 A0 */	addi r5, r13, lbl_804D3940@sda21
    /* 80032270 0002EE50  48 35 5F B1 */	bl __assert
    lbl_80032274:
    /* 80032274 0002EE54  1C 9F 0E 90 */	mulli r4, r31, 0xe90
    /* 80032278 0002EE58  3C 60 80 45 */	lis r3, player_slots@ha
    /* 8003227C 0002EE5C  38 03 30 80 */	addi r0, r3, player_slots@l
    /* 80032280 0002EE60  7C 60 22 14 */	add r3, r0, r4
    /* 80032284 0002EE64  88 03 00 0C */	lbz r0, 0xc(r3)
    /* 80032288 0002EE68  54 00 10 3A */	slwi r0, r0, 2
    /* 8003228C 0002EE6C  7C 63 02 14 */	add r3, r3, r0
    /* 80032290 0002EE70  80 63 00 B0 */	lwz r3, 0xb0(r3)
    /* 80032294 0002EE74  48 05 4D 89 */	bl func_8008701C
    /* 80032298 0002EE78  2C 03 00 00 */	cmpwi r3, 0
    /* 8003229C 0002EE7C  40 82 00 0C */	bne lbl_800322A8
    /* 800322A0 0002EE80  38 60 00 01 */	li r3, 1
    /* 800322A4 0002EE84  48 00 00 08 */	b lbl_800322AC
    lbl_800322A8:
    /* 800322A8 0002EE88  38 60 00 00 */	li r3, 0
    lbl_800322AC:
    /* 800322AC 0002EE8C  80 01 00 1C */	lwz r0, 0x1c(r1)
    /* 800322B0 0002EE90  83 E1 00 14 */	lwz r31, 0x14(r1)
    /* 800322B4 0002EE94  38 21 00 18 */	addi r1, r1, 0x18
    /* 800322B8 0002EE98  7C 08 03 A6 */	mtlr r0
    /* 800322BC 0002EE9C  4E 80 00 20 */	blr 
}
#endif


#ifdef NON_MATCHING
s32 Player_GetPlayerState(s32 slot) {  //https://decomp.me/scratch/495kO
    s32 state;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    state = player->player_state;
    return state;
}
#else
asm void Player_GetPlayerState(s32 slot)
{
    nofralloc
    /* 800322C0 0002EEA0  7C 08 02 A6 */	mflr r0
    /* 800322C4 0002EEA4  90 01 00 04 */	stw r0, 4(r1)
    /* 800322C8 0002EEA8  94 21 FF E0 */	stwu r1, -0x20(r1)
    /* 800322CC 0002EEAC  93 E1 00 1C */	stw r31, 0x1c(r1)
    /* 800322D0 0002EEB0  7C 7F 1B 79 */	or. r31, r3, r3
    /* 800322D4 0002EEB4  41 80 00 0C */	blt lbl_800322E0
    /* 800322D8 0002EEB8  2C 1F 00 06 */	cmpwi r31, 6
    /* 800322DC 0002EEBC  41 80 00 2C */	blt lbl_80032308
    lbl_800322E0:
    /* 800322E0 0002EEC0  3C 60 80 3C */	lis r3, lbl_803BCE44@ha
    /* 800322E4 0002EEC4  4C C6 31 82 */	crclr 6
    /* 800322E8 0002EEC8  38 63 CE 44 */	addi r3, r3, lbl_803BCE44@l
    /* 800322EC 0002EECC  38 9F 00 00 */	addi r4, r31, 0
    /* 800322F0 0002EED0  48 31 33 B9 */	bl OSReport
    /* 800322F4 0002EED4  3C 60 80 3C */	lis r3, lbl_803BCE60@ha
    /* 800322F8 0002EED8  38 63 CE 60 */	addi r3, r3, lbl_803BCE60@l
    /* 800322FC 0002EEDC  38 80 00 66 */	li r4, 0x66
    /* 80032300 0002EEE0  38 AD 82 A0 */	addi r5, r13, lbl_804D3940@sda21
    /* 80032304 0002EEE4  48 35 5F 1D */	bl __assert
    lbl_80032308:
    /* 80032308 0002EEE8  1C 9F 0E 90 */	mulli r4, r31, 0xe90
    /* 8003230C 0002EEEC  3C 60 80 45 */	lis r3, player_slots@ha
    /* 80032310 0002EEF0  38 03 30 80 */	addi r0, r3, player_slots@l
    /* 80032314 0002EEF4  7C 60 22 14 */	add r3, r0, r4
    /* 80032318 0002EEF8  80 63 00 00 */	lwz r3, 0(r3)
    /* 8003231C 0002EEFC  80 01 00 24 */	lwz r0, 0x24(r1)
    /* 80032320 0002EF00  83 E1 00 1C */	lwz r31, 0x1c(r1)
    /* 80032324 0002EF04  38 21 00 20 */	addi r1, r1, 0x20
    /* 80032328 0002EF08  7C 08 03 A6 */	mtlr r0
    /* 8003232C 0002EF0C  4E 80 00 20 */	blr 
}
#endif

#ifdef NON_MATCHING
s32 Player_GetPlayerCharacter(s32 slot) {   ///https://decomp.me/scratch/3aykL
    s32 unused;
    StaticPlayer* player; 
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    return player->player_character;
}
#else
asm s32 Player_GetPlayerCharacter(s32 slot) 
{
    nofralloc
    /* 80032330 0002EF10  7C 08 02 A6 */	mflr r0
    /* 80032334 0002EF14  90 01 00 04 */	stw r0, 4(r1)
    /* 80032338 0002EF18  94 21 FF E0 */	stwu r1, -0x20(r1)
    /* 8003233C 0002EF1C  93 E1 00 1C */	stw r31, 0x1c(r1)
    /* 80032340 0002EF20  7C 7F 1B 79 */	or. r31, r3, r3
    /* 80032344 0002EF24  41 80 00 0C */	blt lbl_80032350
    /* 80032348 0002EF28  2C 1F 00 06 */	cmpwi r31, 6
    /* 8003234C 0002EF2C  41 80 00 2C */	blt lbl_80032378
    lbl_80032350:
    /* 80032350 0002EF30  3C 60 80 3C */	lis r3, lbl_803BCE44@ha
    /* 80032354 0002EF34  4C C6 31 82 */	crclr 6
    /* 80032358 0002EF38  38 63 CE 44 */	addi r3, r3, lbl_803BCE44@l
    /* 8003235C 0002EF3C  38 9F 00 00 */	addi r4, r31, 0
    /* 80032360 0002EF40  48 31 33 49 */	bl OSReport
    /* 80032364 0002EF44  3C 60 80 3C */	lis r3, lbl_803BCE60@ha
    /* 80032368 0002EF48  38 63 CE 60 */	addi r3, r3, lbl_803BCE60@l
    /* 8003236C 0002EF4C  38 80 00 66 */	li r4, 0x66
    /* 80032370 0002EF50  38 AD 82 A0 */	addi r5, r13, lbl_804D3940@sda21
    /* 80032374 0002EF54  48 35 5E AD */	bl __assert
    lbl_80032378:
    /* 80032378 0002EF58  1C 9F 0E 90 */	mulli r4, r31, 0xe90
    /* 8003237C 0002EF5C  3C 60 80 45 */	lis r3, player_slots@ha
    /* 80032380 0002EF60  38 03 30 80 */	addi r0, r3, player_slots@l
    /* 80032384 0002EF64  7C 60 22 14 */	add r3, r0, r4
    /* 80032388 0002EF68  80 63 00 04 */	lwz r3, 4(r3)
    /* 8003238C 0002EF6C  80 01 00 24 */	lwz r0, 0x24(r1)
    /* 80032390 0002EF70  83 E1 00 1C */	lwz r31, 0x1c(r1)
    /* 80032394 0002EF74  38 21 00 20 */	addi r1, r1, 0x20
    /* 80032398 0002EF78  7C 08 03 A6 */	mtlr r0
    /* 8003239C 0002EF7C  4E 80 00 20 */	blr 
}
#endif

#ifdef NON_MATCHING
void Player_SetPlayerCharacter(s32 slot, s32 value) {   ///https://decomp.me/scratch/zABz1
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->player_character = value;
}
#else
asm void Player_SetPlayerCharacter(s32 slot, s32 value)
{
    nofralloc
    /* 800323A0 0002EF80  7C 08 02 A6 */	mflr r0
    /* 800323A4 0002EF84  90 01 00 04 */	stw r0, 4(r1)
    /* 800323A8 0002EF88  94 21 FF E0 */	stwu r1, -0x20(r1)
    /* 800323AC 0002EF8C  93 E1 00 1C */	stw r31, 0x1c(r1)
    /* 800323B0 0002EF90  3B E4 00 00 */	addi r31, r4, 0
    /* 800323B4 0002EF94  93 C1 00 18 */	stw r30, 0x18(r1)
    /* 800323B8 0002EF98  7C 7E 1B 79 */	or. r30, r3, r3
    /* 800323BC 0002EF9C  41 80 00 0C */	blt lbl_800323C8
    /* 800323C0 0002EFA0  2C 1E 00 06 */	cmpwi r30, 6
    /* 800323C4 0002EFA4  41 80 00 2C */	blt lbl_800323F0
    lbl_800323C8:
    /* 800323C8 0002EFA8  3C 60 80 3C */	lis r3, lbl_803BCE44@ha
    /* 800323CC 0002EFAC  4C C6 31 82 */	crclr 6
    /* 800323D0 0002EFB0  38 63 CE 44 */	addi r3, r3, lbl_803BCE44@l
    /* 800323D4 0002EFB4  38 9E 00 00 */	addi r4, r30, 0
    /* 800323D8 0002EFB8  48 31 32 D1 */	bl OSReport
    /* 800323DC 0002EFBC  3C 60 80 3C */	lis r3, lbl_803BCE60@ha
    /* 800323E0 0002EFC0  38 63 CE 60 */	addi r3, r3, lbl_803BCE60@l
    /* 800323E4 0002EFC4  38 80 00 66 */	li r4, 0x66
    /* 800323E8 0002EFC8  38 AD 82 A0 */	addi r5, r13, lbl_804D3940@sda21
    /* 800323EC 0002EFCC  48 35 5E 35 */	bl __assert
    lbl_800323F0:
    /* 800323F0 0002EFD0  1C 9E 0E 90 */	mulli r4, r30, 0xe90
    /* 800323F4 0002EFD4  3C 60 80 45 */	lis r3, player_slots@ha
    /* 800323F8 0002EFD8  38 03 30 80 */	addi r0, r3, player_slots@l
    /* 800323FC 0002EFDC  7C 60 22 14 */	add r3, r0, r4
    /* 80032400 0002EFE0  93 E3 00 04 */	stw r31, 4(r3)
    /* 80032404 0002EFE4  80 01 00 24 */	lwz r0, 0x24(r1)
    /* 80032408 0002EFE8  83 E1 00 1C */	lwz r31, 0x1c(r1)
    /* 8003240C 0002EFEC  83 C1 00 18 */	lwz r30, 0x18(r1)
    /* 80032410 0002EFF0  38 21 00 20 */	addi r1, r1, 0x20
    /* 80032414 0002EFF4  7C 08 03 A6 */	mtlr r0
    /* 80032418 0002EFF8  4E 80 00 20 */	blr 
}
#endif

#ifdef NON_MATCHING
s32 Player_GetPlayerSlotType(s32 slot) {   ///https://decomp.me/scratch/1BMYo
    s32 slot_type;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    slot_type = player->slot_type;
    return slot_type;
}
#else
asm s32 Player_GetPlayerSlotType(s32 slot) {
    nofralloc
    /* 8003241C 0002EFFC  7C 08 02 A6 */	mflr r0
    /* 80032420 0002F000  90 01 00 04 */	stw r0, 4(r1)
    /* 80032424 0002F004  94 21 FF E0 */	stwu r1, -0x20(r1)
    /* 80032428 0002F008  93 E1 00 1C */	stw r31, 0x1c(r1)
    /* 8003242C 0002F00C  7C 7F 1B 79 */	or. r31, r3, r3
    /* 80032430 0002F010  41 80 00 0C */	blt lbl_8003243C
    /* 80032434 0002F014  2C 1F 00 06 */	cmpwi r31, 6
    /* 80032438 0002F018  41 80 00 2C */	blt lbl_80032464
    lbl_8003243C:
    /* 8003243C 0002F01C  3C 60 80 3C */	lis r3, lbl_803BCE44@ha
    /* 80032440 0002F020  4C C6 31 82 */	crclr 6
    /* 80032444 0002F024  38 63 CE 44 */	addi r3, r3, lbl_803BCE44@l
    /* 80032448 0002F028  38 9F 00 00 */	addi r4, r31, 0
    /* 8003244C 0002F02C  48 31 32 5D */	bl OSReport
    /* 80032450 0002F030  3C 60 80 3C */	lis r3, lbl_803BCE60@ha
    /* 80032454 0002F034  38 63 CE 60 */	addi r3, r3, lbl_803BCE60@l
    /* 80032458 0002F038  38 80 00 66 */	li r4, 0x66
    /* 8003245C 0002F03C  38 AD 82 A0 */	addi r5, r13, lbl_804D3940@sda21
    /* 80032460 0002F040  48 35 5D C1 */	bl __assert
    lbl_80032464:
    /* 80032464 0002F044  1C 9F 0E 90 */	mulli r4, r31, 0xe90
    /* 80032468 0002F048  3C 60 80 45 */	lis r3, player_slots@ha
    /* 8003246C 0002F04C  38 03 30 80 */	addi r0, r3, player_slots@l
    /* 80032470 0002F050  7C 60 22 14 */	add r3, r0, r4
    /* 80032474 0002F054  80 63 00 08 */	lwz r3, 8(r3)
    /* 80032478 0002F058  80 01 00 24 */	lwz r0, 0x24(r1)
    /* 8003247C 0002F05C  83 E1 00 1C */	lwz r31, 0x1c(r1)
    /* 80032480 0002F060  38 21 00 20 */	addi r1, r1, 0x20
    /* 80032484 0002F064  7C 08 03 A6 */	mtlr r0
    /* 80032488 0002F068  4E 80 00 20 */	blr 
}
#endif

#ifdef NON_MATCHING
s32 Player_8003248C(s32 slot, BOOL arg1) {   //https://decomp.me/scratch/3yC1W
    
    s32 slot_type;
    struct Unk_Struct_w_Array* unk_struct = (struct Unk_Struct_w_Array*) &lbl_803BCDC0;
    StaticPlayer* player;
 
    Player_CheckSlot(slot);

    player = &player_slots[slot];

    if (arg1 == 1) {

        if (unk_struct->vec_arr[player->player_character].z == 0) {
            if (player->slot_type == 0 || player->slot_type == 1) {
                return 1;
            }
        }
    }
    slot_type = player->slot_type;

    return slot_type;
}
#else
asm s32 Player_8003248C(s32 slot, BOOL arg1)
{
    nofralloc
    /* 8003248C 0002F06C  7C 08 02 A6 */	mflr r0
    /* 80032490 0002F070  90 01 00 04 */	stw r0, 4(r1)
    /* 80032494 0002F074  94 21 FF D8 */	stwu r1, -0x28(r1)
    /* 80032498 0002F078  93 E1 00 24 */	stw r31, 0x24(r1)
    /* 8003249C 0002F07C  93 C1 00 20 */	stw r30, 0x20(r1)
    /* 800324A0 0002F080  3B C4 00 00 */	addi r30, r4, 0
    /* 800324A4 0002F084  93 A1 00 1C */	stw r29, 0x1c(r1)
    /* 800324A8 0002F088  7C 7D 1B 79 */	or. r29, r3, r3
    /* 800324AC 0002F08C  3C 60 80 3C */	lis r3, lbl_803BCDC0@ha
    /* 800324B0 0002F090  3B E3 CD C0 */	addi r31, r3, lbl_803BCDC0@l
    /* 800324B4 0002F094  41 80 00 0C */	blt lbl_800324C0
    /* 800324B8 0002F098  2C 1D 00 06 */	cmpwi r29, 6
    /* 800324BC 0002F09C  41 80 00 24 */	blt lbl_800324E0
    lbl_800324C0:
    /* 800324C0 0002F0A0  38 9D 00 00 */	addi r4, r29, 0
    /* 800324C4 0002F0A4  4C C6 31 82 */	crclr 6
    /* 800324C8 0002F0A8  38 7F 00 84 */	addi r3, r31, 0x84
    /* 800324CC 0002F0AC  48 31 31 DD */	bl OSReport
    /* 800324D0 0002F0B0  38 7F 00 A0 */	addi r3, r31, 0xa0
    /* 800324D4 0002F0B4  38 80 00 66 */	li r4, 0x66
    /* 800324D8 0002F0B8  38 AD 82 A0 */	addi r5, r13, lbl_804D3940@sda21
    /* 800324DC 0002F0BC  48 35 5D 45 */	bl __assert
    lbl_800324E0:
    /* 800324E0 0002F0C0  1C 9D 0E 90 */	mulli r4, r29, 0xe90
    /* 800324E4 0002F0C4  3C 60 80 45 */	lis r3, player_slots@ha
    /* 800324E8 0002F0C8  38 03 30 80 */	addi r0, r3, player_slots@l
    /* 800324EC 0002F0CC  2C 1E 00 01 */	cmpwi r30, 1
    /* 800324F0 0002F0D0  7C 80 22 14 */	add r4, r0, r4
    /* 800324F4 0002F0D4  40 82 00 38 */	bne lbl_8003252C
    /* 800324F8 0002F0D8  80 04 00 04 */	lwz r0, 4(r4)
    /* 800324FC 0002F0DC  1C 00 00 03 */	mulli r0, r0, 3
    /* 80032500 0002F0E0  7C 7F 02 14 */	add r3, r31, r0
    /* 80032504 0002F0E4  88 03 00 22 */	lbz r0, 0x22(r3)
    /* 80032508 0002F0E8  7C 00 07 75 */	extsb. r0, r0
    /* 8003250C 0002F0EC  40 82 00 20 */	bne lbl_8003252C
    /* 80032510 0002F0F0  80 04 00 08 */	lwz r0, 8(r4)
    /* 80032514 0002F0F4  2C 00 00 00 */	cmpwi r0, 0
    /* 80032518 0002F0F8  41 82 00 0C */	beq lbl_80032524
    /* 8003251C 0002F0FC  2C 00 00 01 */	cmpwi r0, 1
    /* 80032520 0002F100  40 82 00 0C */	bne lbl_8003252C
    lbl_80032524:
    /* 80032524 0002F104  38 60 00 01 */	li r3, 1
    /* 80032528 0002F108  48 00 00 08 */	b lbl_80032530
    lbl_8003252C:
    /* 8003252C 0002F10C  80 64 00 08 */	lwz r3, 8(r4)
    lbl_80032530:
    /* 80032530 0002F110  80 01 00 2C */	lwz r0, 0x2c(r1)
    /* 80032534 0002F114  83 E1 00 24 */	lwz r31, 0x24(r1)
    /* 80032538 0002F118  83 C1 00 20 */	lwz r30, 0x20(r1)
    /* 8003253C 0002F11C  83 A1 00 1C */	lwz r29, 0x1c(r1)
    /* 80032540 0002F120  38 21 00 28 */	addi r1, r1, 0x28
    /* 80032544 0002F124  7C 08 03 A6 */	mtlr r0
    /* 80032548 0002F128  4E 80 00 20 */	blr 
}
#endif

#ifdef NON_MATCHING
void Player_SetSlottype(s32 slot, s32 value) {
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->slot_type = value;
}
#else
asm void Player_SetSlottype(s32 slot, s32 value) 
{
    nofralloc
    /* 8003254C 0002F12C  7C 08 02 A6 */	mflr r0
    /* 80032550 0002F130  90 01 00 04 */	stw r0, 4(r1)
    /* 80032554 0002F134  94 21 FF E0 */	stwu r1, -0x20(r1)
    /* 80032558 0002F138  93 E1 00 1C */	stw r31, 0x1c(r1)
    /* 8003255C 0002F13C  3B E4 00 00 */	addi r31, r4, 0
    /* 80032560 0002F140  93 C1 00 18 */	stw r30, 0x18(r1)
    /* 80032564 0002F144  7C 7E 1B 79 */	or. r30, r3, r3
    /* 80032568 0002F148  41 80 00 0C */	blt lbl_80032574
    /* 8003256C 0002F14C  2C 1E 00 06 */	cmpwi r30, 6
    /* 80032570 0002F150  41 80 00 2C */	blt lbl_8003259C
    lbl_80032574:
    /* 80032574 0002F154  3C 60 80 3C */	lis r3, lbl_803BCE44@ha
    /* 80032578 0002F158  4C C6 31 82 */	crclr 6
    /* 8003257C 0002F15C  38 63 CE 44 */	addi r3, r3, lbl_803BCE44@l
    /* 80032580 0002F160  38 9E 00 00 */	addi r4, r30, 0
    /* 80032584 0002F164  48 31 31 25 */	bl OSReport
    /* 80032588 0002F168  3C 60 80 3C */	lis r3, lbl_803BCE60@ha
    /* 8003258C 0002F16C  38 63 CE 60 */	addi r3, r3, lbl_803BCE60@l
    /* 80032590 0002F170  38 80 00 66 */	li r4, 0x66
    /* 80032594 0002F174  38 AD 82 A0 */	addi r5, r13, lbl_804D3940@sda21
    /* 80032598 0002F178  48 35 5C 89 */	bl __assert
    lbl_8003259C:
    /* 8003259C 0002F17C  1C 9E 0E 90 */	mulli r4, r30, 0xe90
    /* 800325A0 0002F180  3C 60 80 45 */	lis r3, player_slots@ha
    /* 800325A4 0002F184  38 03 30 80 */	addi r0, r3, player_slots@l
    /* 800325A8 0002F188  7C 60 22 14 */	add r3, r0, r4
    /* 800325AC 0002F18C  93 E3 00 08 */	stw r31, 8(r3)
    /* 800325B0 0002F190  80 01 00 24 */	lwz r0, 0x24(r1)
    /* 800325B4 0002F194  83 E1 00 1C */	lwz r31, 0x1c(r1)
    /* 800325B8 0002F198  83 C1 00 18 */	lwz r30, 0x18(r1)
    /* 800325BC 0002F19C  38 21 00 20 */	addi r1, r1, 0x20
    /* 800325C0 0002F1A0  7C 08 03 A6 */	mtlr r0
    /* 800325C4 0002F1A4  4E 80 00 20 */	blr 

}
#endif

#ifdef NON_MATCHING
s8 Player_800325C8(s32 slot, BOOL b) {
    
    
    if (!b) {
        return lbl_803BCDE0[slot].x;
    }
    else if (b == 1) {
        return lbl_803BCDE0[slot].y;
    }

    return -1;
}
#else
asm s8 Player_800325C8(s32 slot, BOOL b) 
{
    nofralloc
    /* 800325C8 0002F1A8  2C 04 00 00 */	cmpwi r4, 0
    /* 800325CC 0002F1AC  40 82 00 1C */	bne lbl_800325E8
    /* 800325D0 0002F1B0  1C 83 00 03 */	mulli r4, r3, 3
    /* 800325D4 0002F1B4  3C 60 80 3C */	lis r3, lbl_803BCDE0@ha
    /* 800325D8 0002F1B8  38 03 CD E0 */	addi r0, r3, lbl_803BCDE0@l
    /* 800325DC 0002F1BC  7C 60 22 14 */	add r3, r0, r4
    /* 800325E0 0002F1C0  88 63 00 00 */	lbz r3, 0(r3)
    /* 800325E4 0002F1C4  4E 80 00 20 */	blr 
    lbl_800325E8:
    /* 800325E8 0002F1C8  2C 04 00 01 */	cmpwi r4, 1
    /* 800325EC 0002F1CC  40 82 00 1C */	bne lbl_80032608
    /* 800325F0 0002F1D0  1C 03 00 03 */	mulli r0, r3, 3
    /* 800325F4 0002F1D4  3C 60 80 3C */	lis r3, lbl_803BCDE0@ha
    /* 800325F8 0002F1D8  38 63 CD E0 */	addi r3, r3, lbl_803BCDE0@l
    /* 800325FC 0002F1DC  7C 63 02 14 */	add r3, r3, r0
    /* 80032600 0002F1E0  88 63 00 01 */	lbz r3, 1(r3)
    /* 80032604 0002F1E4  4E 80 00 20 */	blr 
    lbl_80032608:
    /* 80032608 0002F1E8  38 60 FF FF */	li r3, -1
    /* 8003260C 0002F1EC  4E 80 00 20 */	blr 
}
#endif

#ifdef NON_MATCHING
s8 Player_80032610(s32 slot, BOOL arg1) {  ////https://decomp.me/scratch/pHTx2

    struct Unk_Struct_w_Array* some_struct = (struct Unk_Struct_w_Array*) &lbl_803BCDC0;
    StaticPlayer* player;
    s32 error_value = -1;


    Player_CheckSlot(slot);
    player = &player_slots[slot];

    if (arg1 == 0) {
        return some_struct->vec_arr[player->player_character].x;
    }
    if (arg1 == 1) {
        return some_struct->vec_arr[player->player_character].y;
    }

    return error_value;
}
#else
asm s8 Player_80032610(s32 slot, BOOL arg1) 
{
    nofralloc
    /* 80032610 0002F1F0  7C 08 02 A6 */	mflr r0
    /* 80032614 0002F1F4  90 01 00 04 */	stw r0, 4(r1)
    /* 80032618 0002F1F8  94 21 FF D8 */	stwu r1, -0x28(r1)
    /* 8003261C 0002F1FC  93 E1 00 24 */	stw r31, 0x24(r1)
    /* 80032620 0002F200  93 C1 00 20 */	stw r30, 0x20(r1)
    /* 80032624 0002F204  3B C4 00 00 */	addi r30, r4, 0
    /* 80032628 0002F208  93 A1 00 1C */	stw r29, 0x1c(r1)
    /* 8003262C 0002F20C  7C 7D 1B 79 */	or. r29, r3, r3
    /* 80032630 0002F210  3C 60 80 3C */	lis r3, lbl_803BCDC0@ha
    /* 80032634 0002F214  3B E3 CD C0 */	addi r31, r3, lbl_803BCDC0@l
    /* 80032638 0002F218  41 80 00 0C */	blt lbl_80032644
    /* 8003263C 0002F21C  2C 1D 00 06 */	cmpwi r29, 6
    /* 80032640 0002F220  41 80 00 24 */	blt lbl_80032664
    lbl_80032644:
    /* 80032644 0002F224  38 9D 00 00 */	addi r4, r29, 0
    /* 80032648 0002F228  4C C6 31 82 */	crclr 6
    /* 8003264C 0002F22C  38 7F 00 84 */	addi r3, r31, 0x84
    /* 80032650 0002F230  48 31 30 59 */	bl OSReport
    /* 80032654 0002F234  38 7F 00 A0 */	addi r3, r31, 0xa0
    /* 80032658 0002F238  38 80 00 66 */	li r4, 0x66
    /* 8003265C 0002F23C  38 AD 82 A0 */	addi r5, r13, lbl_804D3940@sda21
    /* 80032660 0002F240  48 35 5B C1 */	bl __assert
    lbl_80032664:
    /* 80032664 0002F244  1C 9D 0E 90 */	mulli r4, r29, 0xe90
    /* 80032668 0002F248  3C 60 80 45 */	lis r3, player_slots@ha
    /* 8003266C 0002F24C  38 03 30 80 */	addi r0, r3, player_slots@l
    /* 80032670 0002F250  2C 1E 00 00 */	cmpwi r30, 0
    /* 80032674 0002F254  7C 60 22 14 */	add r3, r0, r4
    /* 80032678 0002F258  40 82 00 18 */	bne lbl_80032690
    /* 8003267C 0002F25C  80 03 00 04 */	lwz r0, 4(r3)
    /* 80032680 0002F260  1C 00 00 03 */	mulli r0, r0, 3
    /* 80032684 0002F264  7C 7F 02 14 */	add r3, r31, r0
    /* 80032688 0002F268  88 63 00 20 */	lbz r3, 0x20(r3)
    /* 8003268C 0002F26C  48 00 00 24 */	b lbl_800326B0
    lbl_80032690:
    /* 80032690 0002F270  2C 1E 00 01 */	cmpwi r30, 1
    /* 80032694 0002F274  40 82 00 18 */	bne lbl_800326AC
    /* 80032698 0002F278  80 03 00 04 */	lwz r0, 4(r3)
    /* 8003269C 0002F27C  1C 00 00 03 */	mulli r0, r0, 3
    /* 800326A0 0002F280  7C 7F 02 14 */	add r3, r31, r0
    /* 800326A4 0002F284  88 63 00 21 */	lbz r3, 0x21(r3)
    /* 800326A8 0002F288  48 00 00 08 */	b lbl_800326B0
    lbl_800326AC:
    /* 800326AC 0002F28C  38 60 FF FF */	li r3, -1
    lbl_800326B0:
    /* 800326B0 0002F290  80 01 00 2C */	lwz r0, 0x2c(r1)
    /* 800326B4 0002F294  83 E1 00 24 */	lwz r31, 0x24(r1)
    /* 800326B8 0002F298  83 C1 00 20 */	lwz r30, 0x20(r1)
    /* 800326BC 0002F29C  83 A1 00 1C */	lwz r29, 0x1c(r1)
    /* 800326C0 0002F2A0  38 21 00 28 */	addi r1, r1, 0x28
    /* 800326C4 0002F2A4  7C 08 03 A6 */	mtlr r0
    /* 800326C8 0002F2A8  4E 80 00 20 */	blr 
}
#endif

#ifdef NON_MATCHING
void Player_800326CC(s32 slot, Vec* arg_vec) {
    StaticPlayer* player;
    Vec* player_vecs;

    Player_CheckSlot(slot);

    player = &player_slots[slot];
    player_vecs = player->player_poses.byIndex;
    *arg_vec = player_vecs[player->transformed[0]];
}

#else
asm void Player_800326CC(s32 slot, Vec* arg_vec)
{
    nofralloc
    /* 800326CC 0002F2AC  7C 08 02 A6 */	mflr r0
    /* 800326D0 0002F2B0  90 01 00 04 */	stw r0, 4(r1)
    /* 800326D4 0002F2B4  94 21 FF E0 */	stwu r1, -0x20(r1)
    /* 800326D8 0002F2B8  93 E1 00 1C */	stw r31, 0x1c(r1)
    /* 800326DC 0002F2BC  3B E4 00 00 */	addi r31, r4, 0
    /* 800326E0 0002F2C0  93 C1 00 18 */	stw r30, 0x18(r1)
    /* 800326E4 0002F2C4  7C 7E 1B 79 */	or. r30, r3, r3
    /* 800326E8 0002F2C8  41 80 00 0C */	blt lbl_800326F4
    /* 800326EC 0002F2CC  2C 1E 00 06 */	cmpwi r30, 6
    /* 800326F0 0002F2D0  41 80 00 2C */	blt lbl_8003271C
    lbl_800326F4:
    /* 800326F4 0002F2D4  3C 60 80 3C */	lis r3, lbl_803BCE44@ha
    /* 800326F8 0002F2D8  4C C6 31 82 */	crclr 6
    /* 800326FC 0002F2DC  38 63 CE 44 */	addi r3, r3, lbl_803BCE44@l
    /* 80032700 0002F2E0  38 9E 00 00 */	addi r4, r30, 0
    /* 80032704 0002F2E4  48 31 2F A5 */	bl OSReport
    /* 80032708 0002F2E8  3C 60 80 3C */	lis r3, lbl_803BCE60@ha
    /* 8003270C 0002F2EC  38 63 CE 60 */	addi r3, r3, lbl_803BCE60@l
    /* 80032710 0002F2F0  38 80 00 66 */	li r4, 0x66
    /* 80032714 0002F2F4  38 AD 82 A0 */	addi r5, r13, lbl_804D3940@sda21
    /* 80032718 0002F2F8  48 35 5B 09 */	bl __assert
    lbl_8003271C:
    /* 8003271C 0002F2FC  1C 9E 0E 90 */	mulli r4, r30, 0xe90
    /* 80032720 0002F300  3C 60 80 45 */	lis r3, player_slots@ha
    /* 80032724 0002F304  38 03 30 80 */	addi r0, r3, player_slots@l
    /* 80032728 0002F308  7C 60 22 14 */	add r3, r0, r4
    /* 8003272C 0002F30C  88 03 00 0C */	lbz r0, 0xc(r3)
    /* 80032730 0002F310  1C 00 00 0C */	mulli r0, r0, 0xc
    /* 80032734 0002F314  7C 83 02 14 */	add r4, r3, r0
    /* 80032738 0002F318  80 64 00 10 */	lwz r3, 0x10(r4)
    /* 8003273C 0002F31C  80 04 00 14 */	lwz r0, 0x14(r4)
    /* 80032740 0002F320  90 7F 00 00 */	stw r3, 0(r31)
    /* 80032744 0002F324  90 1F 00 04 */	stw r0, 4(r31)
    /* 80032748 0002F328  80 04 00 18 */	lwz r0, 0x18(r4)
    /* 8003274C 0002F32C  90 1F 00 08 */	stw r0, 8(r31)
    /* 80032750 0002F330  80 01 00 24 */	lwz r0, 0x24(r1)
    /* 80032754 0002F334  83 E1 00 1C */	lwz r31, 0x1c(r1)
    /* 80032758 0002F338  83 C1 00 18 */	lwz r30, 0x18(r1)
    /* 8003275C 0002F33C  38 21 00 20 */	addi r1, r1, 0x20
    /* 80032760 0002F340  7C 08 03 A6 */	mtlr r0
    /* 80032764 0002F344  4E 80 00 20 */	blr 
}
#endif

#ifdef NON_MATCHING
void Player_80032768(s32 slot, Vec* arg_vec) { //https://decomp.me/scratch/Acnkf
    StaticPlayer* player;
    Vec* player_vecs;

    Vec* dst_vec;
    Vec* dst_vec2;

    Player_CheckSlot(slot);

    player = &player_slots[slot];

    player_vecs = player->player_poses.byIndex;
    dst_vec = &player_vecs[player->transformed[0]];
    *dst_vec = *arg_vec;

    player_vecs = player->player_poses.byIndex;
    dst_vec2 = &player_vecs[player->transformed[1]];
    *dst_vec2 = *arg_vec;
}
#else
asm void Player_80032768(s32 slot, Vec* arg_vec)
{
    nofralloc
    /* 80032768 0002F348  7C 08 02 A6 */	mflr r0
    /* 8003276C 0002F34C  90 01 00 04 */	stw r0, 4(r1)
    /* 80032770 0002F350  94 21 FF D8 */	stwu r1, -0x28(r1)
    /* 80032774 0002F354  93 E1 00 24 */	stw r31, 0x24(r1)
    /* 80032778 0002F358  3B E4 00 00 */	addi r31, r4, 0
    /* 8003277C 0002F35C  93 C1 00 20 */	stw r30, 0x20(r1)
    /* 80032780 0002F360  7C 7E 1B 79 */	or. r30, r3, r3
    /* 80032784 0002F364  41 80 00 0C */	blt lbl_80032790
    /* 80032788 0002F368  2C 1E 00 06 */	cmpwi r30, 6
    /* 8003278C 0002F36C  41 80 00 2C */	blt lbl_800327B8
    lbl_80032790:
    /* 80032790 0002F370  3C 60 80 3C */	lis r3, lbl_803BCE44@ha
    /* 80032794 0002F374  4C C6 31 82 */	crclr 6
    /* 80032798 0002F378  38 63 CE 44 */	addi r3, r3, lbl_803BCE44@l
    /* 8003279C 0002F37C  38 9E 00 00 */	addi r4, r30, 0
    /* 800327A0 0002F380  48 31 2F 09 */	bl OSReport
    /* 800327A4 0002F384  3C 60 80 3C */	lis r3, lbl_803BCE60@ha
    /* 800327A8 0002F388  38 63 CE 60 */	addi r3, r3, lbl_803BCE60@l
    /* 800327AC 0002F38C  38 80 00 66 */	li r4, 0x66
    /* 800327B0 0002F390  38 AD 82 A0 */	addi r5, r13, lbl_804D3940@sda21
    /* 800327B4 0002F394  48 35 5A 6D */	bl __assert
    lbl_800327B8:
    /* 800327B8 0002F398  1C BE 0E 90 */	mulli r5, r30, 0xe90
    /* 800327BC 0002F39C  80 7F 00 00 */	lwz r3, 0(r31)
    /* 800327C0 0002F3A0  80 1F 00 04 */	lwz r0, 4(r31)
    /* 800327C4 0002F3A4  3C 80 80 45 */	lis r4, player_slots@ha
    /* 800327C8 0002F3A8  38 84 30 80 */	addi r4, r4, player_slots@l
    /* 800327CC 0002F3AC  7C A4 2A 14 */	add r5, r4, r5
    /* 800327D0 0002F3B0  88 85 00 0C */	lbz r4, 0xc(r5)
    /* 800327D4 0002F3B4  1C 84 00 0C */	mulli r4, r4, 0xc
    /* 800327D8 0002F3B8  7C 85 22 14 */	add r4, r5, r4
    /* 800327DC 0002F3BC  90 64 00 10 */	stw r3, 0x10(r4)
    /* 800327E0 0002F3C0  90 04 00 14 */	stw r0, 0x14(r4)
    /* 800327E4 0002F3C4  80 1F 00 08 */	lwz r0, 8(r31)
    /* 800327E8 0002F3C8  90 04 00 18 */	stw r0, 0x18(r4)
    /* 800327EC 0002F3CC  88 05 00 0D */	lbz r0, 0xd(r5)
    /* 800327F0 0002F3D0  80 7F 00 00 */	lwz r3, 0(r31)
    /* 800327F4 0002F3D4  1C 80 00 0C */	mulli r4, r0, 0xc
    /* 800327F8 0002F3D8  80 1F 00 04 */	lwz r0, 4(r31)
    /* 800327FC 0002F3DC  7C 85 22 14 */	add r4, r5, r4
    /* 80032800 0002F3E0  90 64 00 10 */	stw r3, 0x10(r4)
    /* 80032804 0002F3E4  90 04 00 14 */	stw r0, 0x14(r4)
    /* 80032808 0002F3E8  80 1F 00 08 */	lwz r0, 8(r31)
    /* 8003280C 0002F3EC  90 04 00 18 */	stw r0, 0x18(r4)
    /* 80032810 0002F3F0  80 01 00 2C */	lwz r0, 0x2c(r1)
    /* 80032814 0002F3F4  83 E1 00 24 */	lwz r31, 0x24(r1)
    /* 80032818 0002F3F8  83 C1 00 20 */	lwz r30, 0x20(r1)
    /* 8003281C 0002F3FC  38 21 00 28 */	addi r1, r1, 0x28
    /* 80032820 0002F400  7C 08 03 A6 */	mtlr r0
    /* 80032824 0002F404  4E 80 00 20 */	blr 
}
#endif