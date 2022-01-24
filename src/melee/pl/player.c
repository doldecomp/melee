#include "melee/pl/player.h"

#define NON_MATCHING 1

extern StaticPlayer player_slots[6];  // used to be [4] but I think should be 6?

extern struct Unk_Struct {  //lbl_803BCDC0
    char some_str[8+4];  //"PdPm.dat"
    char another_str[16+4]; 
    S8Vec vec_arr[30];  ///lbl_803BCDE0
} lbl_803BCDC0;

// extern char* lbl_803BCDC0;   ///probably part of struct
// extern S8Vec lbl_803BCDE0[];  ///probably part of struct

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

asm void Player_80031AD0(s32 slot) /// https://decomp.me/scratch/cW4md
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
    if ( lbl_803BCDC0.vec_arr[id].x != -1) {
        func_800855C8(lbl_803BCDC0.vec_arr[id].x, slot);
    }
    if ( lbl_803BCDC0.vec_arr[id].y != -1) {
        func_800855C8(lbl_803BCDC0.vec_arr[id].y, slot);
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
    if ( lbl_803BCDC0.vec_arr[id].x != -1) {
        func_8008578C(lbl_803BCDC0.vec_arr[id].x, slot);
    }
    if ( lbl_803BCDC0.vec_arr[id].y != -1) {
        func_8008578C(lbl_803BCDC0.vec_arr[id].y, slot);
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

void Player_80031DC8(void func_arg(s32, s32)) {
    s32 slot;
    for (slot = 0; slot < 6; slot++) {
        Player_CheckSlot(slot);

        if (player_slots[slot].player_state) {
            func_arg(lbl_803BCDC0.vec_arr[player_slots[slot].player_character].x, 0);
            if (checkNegOne(&lbl_803BCDC0.vec_arr[player_slots[slot].player_character].y)) {
                func_arg(lbl_803BCDC0.vec_arr[player_slots[slot].player_character].y, 0);
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
void Player_80032070(s32 slot, BOOL bool_arg) {   ////https://decomp.me/scratch/SP7Sh
    StaticPlayer* player;
    struct Unk_Struct* unkStruct = &lbl_803BCDC0;
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
