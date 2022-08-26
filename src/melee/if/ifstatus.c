#include <melee/if/ifstatus.h>

extern s8 lbl_804D6D60;

extern unk_t lbl_802F74D0();
extern unk_t lbl_802F73C4();

extern Thing_803F9628 lbl_803F9628;

void func_802F6788(s32 player_idx) {
    HudValue* player_hud;
    s8 p_idx = (u8)player_idx;
    player_hud = &lbl_804A10C8.players[p_idx & 0xFF];
    if (player_hud->HUD_parent_entity != NULL) {
        func_80390228(player_hud->HUD_parent_entity);
        player_hud->HUD_parent_entity = NULL;
    }
    if (player_hud->next != NULL) {
        func_80390228(player_hud->next);
        player_hud->next = NULL;
    }
    func_802FB650(player_idx & 0xFF);
}

void func_802F6804(void) {
    s32 i;
    HudValue* v;

    i = 0;
    do {
        v = &lbl_804A10C8.players[i & 0xFF];
        if (v->HUD_parent_entity != NULL) {
            func_80390228(v->HUD_parent_entity);
            v->HUD_parent_entity = NULL;
        }
        if (v->next != NULL) {
            func_80390228(v->next);
            v->next = NULL;
        }
        func_802FB650((s8)i & 0xFF);
        i++;
    } while (i < 6);
}

// Hide Percentage Digits
void func_802F6898() {
    s32 i;
    HudIndex* v = &lbl_804A10C8;
    for (i = 0; i < 6; i++) {
        v->players[i].flags.hide_all_digits = 1;
    }
}

// Show All Percentage Digits
void func_802F68F0(void) {
    s32 i;
    HudIndex* v = &lbl_804A10C8;
    for (i = 0; i < 6; i++) {
        v->players[i].flags.hide_all_digits = 0;
    }
}

void func_802F6948(s32 player_idx) {
    HudValue* hud_player;
    Placeholder_8016AE50_ret_val* small_thing;
    HudFlags* hud_player_flags;

    small_thing = func_8016AE50();
    hud_player = &lbl_804A10C8.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->unk40 = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
}

// 99.94% complete
// https://decomp.me/scratch/in6rt
void func_802F69C0(s32 player_idx, s32 arg1) {
    HudValue* hud_player;
    HudFlags* hud_player_flags;
    Placeholder_8016AE38_ret_val* big_thing;
    Placeholder_8016AE50_ret_val* small_thing;

    big_thing = func_8016AE38();
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0)) {
        func_802F7C30(arg1);
    }
    
    big_thing = func_8016AE38();
    big_thing->unkD = player_idx;
    small_thing = func_8016AE50();
    hud_player = &lbl_804A10C8.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->unk40 = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->unk24CA.unk80 != 0) && ((Player_GetPlayerSlotType(player_idx) == 0) || (Player_GetPlayerSlotType(player_idx) == 1)) && (Player_GetStocks(player_idx) == 0)) {
        func_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx) & 0xFF);
    }
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0) && (func_802F7BB4 != NULL)) {
        func_802F7BB4(player_idx);
    }
}

// 99.93% complete
// https://decomp.me/scratch/SDDvF
void func_802F6AF8(s32 player_idx) {
    HudValue* hud_player;
    Placeholder_8016AE38_ret_val* big_thing;
    Placeholder_8016AE50_ret_val* small_thing;
    HudFlags* hud_player_flags;

    big_thing = func_8016AE38();
    big_thing->unkD = player_idx;
    small_thing = func_8016AE50();
    hud_player = &lbl_804A10C8.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->unk40 = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->unk24CA.unk80 != 0) && ((Player_GetPlayerSlotType(player_idx) == 0) || (Player_GetPlayerSlotType(player_idx) == 1)) && (Player_GetStocks(player_idx) == 0)) {
        func_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx) & 0xFF);
    }
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0) && (func_802F7AF8 != NULL)) {
        func_802F7AF8(player_idx);
    }
}

// 99.93% complete
// https://decomp.me/scratch/qmpwG
void func_802F6C04(s32 player_idx) {
    HudValue* hud_player;
    HudFlags* hud_player_flags;
    Placeholder_8016AE38_ret_val* big_thing;
    Placeholder_8016AE50_ret_val* small_thing;

    big_thing = func_8016AE38();
    big_thing->unkD = player_idx;
    small_thing = func_8016AE50();
    hud_player = &lbl_804A10C8.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->unk40 = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->unk24CA.unk80 != 0) && ((Player_GetPlayerSlotType(player_idx) == 0) || (Player_GetPlayerSlotType(player_idx) == 1)) && (Player_GetStocks(player_idx) == 0)) {
        func_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx) & 0xFF);
    }
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0) && (func_802F7C30 != NULL)) {
        func_802F7C30(player_idx);
    }
}

// 99.93% complete
// https://decomp.me/scratch/cFb6Y
void func_802F6D10(s32 player_idx) {
    HudValue* hud_player;
    Placeholder_8016AE38_ret_val* big_thing;
    Placeholder_8016AE50_ret_val* small_thing;
    HudFlags* hud_player_flags;

    big_thing = func_8016AE38();
    big_thing->unkD = player_idx;
    small_thing = func_8016AE50();
    hud_player = &lbl_804A10C8.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->unk40 = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->unk24CA.unk80 != 0) && ((Player_GetPlayerSlotType(player_idx) == 0) || (Player_GetPlayerSlotType(player_idx) == 1)) && (Player_GetStocks(player_idx) == 0)) {
        func_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx) & 0xFF);
    }
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0) && (func_802F7D08 != NULL)) {
        func_802F7D08(player_idx);
    }
}

void func_802F6E1C(void) {
    func_802F6508();
}

void func_802F6E3C(s32 player_num) {
    HudValue* player;

    player = &lbl_804A10C8.players[player_num];
    if (player->HUD_parent_entity != NULL) {
        func_80390CAC(player->HUD_parent_entity);
    }
    if (player->next != NULL) {
        func_80390CAC(player->next);
    }
    func_802FB6AC(player_num);
}

asm unk_t func_802F6EA4()
{
/* 802F6EA4 002F3A84  7C 08 02 A6 */	mflr r0
/* 802F6EA8 002F3A88  2C 03 00 08 */	cmpwi r3, 8
/* 802F6EAC 002F3A8C  90 01 00 04 */	stw r0, 4(r1)
/* 802F6EB0 002F3A90  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 802F6EB4 002F3A94  BF 61 00 24 */	stmw r27, 0x24(r1)
/* 802F6EB8 002F3A98  3B A4 00 00 */	addi r29, r4, 0
/* 802F6EBC 002F3A9C  3B 85 00 00 */	addi r28, r5, 0
/* 802F6EC0 002F3AA0  3B C7 00 00 */	addi r30, r7, 0
/* 802F6EC4 002F3AA4  3B E8 00 00 */	addi r31, r8, 0
/* 802F6EC8 002F3AA8  40 82 00 68 */	bne lbl_802F6F30
/* 802F6ECC 002F3AAC  28 1E 00 00 */	cmplwi r30, 0
/* 802F6ED0 002F3AB0  41 82 00 14 */	beq lbl_802F6EE4
/* 802F6ED4 002F3AB4  39 9E 00 00 */	addi r12, r30, 0
/* 802F6ED8 002F3AB8  7D 88 03 A6 */	mtlr r12
/* 802F6EDC 002F3ABC  38 60 FF FF */	li r3, -1
/* 802F6EE0 002F3AC0  4E 80 00 21 */	blrl 
lbl_802F6EE4:
/* 802F6EE4 002F3AC4  28 1F 00 00 */	cmplwi r31, 0
/* 802F6EE8 002F3AC8  41 82 00 14 */	beq lbl_802F6EFC
/* 802F6EEC 002F3ACC  39 9F 00 00 */	addi r12, r31, 0
/* 802F6EF0 002F3AD0  7D 88 03 A6 */	mtlr r12
/* 802F6EF4 002F3AD4  38 60 FF FF */	li r3, -1
/* 802F6EF8 002F3AD8  4E 80 00 21 */	blrl 
lbl_802F6EFC:
/* 802F6EFC 002F3ADC  2C 1D 00 00 */	cmpwi r29, 0
/* 802F6F00 002F3AE0  41 80 00 14 */	blt lbl_802F6F14
/* 802F6F04 002F3AE4  38 7D 00 00 */	addi r3, r29, 0
/* 802F6F08 002F3AE8  38 80 00 7F */	li r4, 0x7f
/* 802F6F0C 002F3AEC  38 A0 00 40 */	li r5, 0x40
/* 802F6F10 002F3AF0  4B D2 C8 99 */	bl func_800237A8
lbl_802F6F14:
/* 802F6F14 002F3AF4  2C 1D 00 00 */	cmpwi r29, 0
/* 802F6F18 002F3AF8  41 80 01 08 */	blt lbl_802F7020
/* 802F6F1C 002F3AFC  38 7C 00 00 */	addi r3, r28, 0
/* 802F6F20 002F3B00  38 80 00 7F */	li r4, 0x7f
/* 802F6F24 002F3B04  38 A0 00 40 */	li r5, 0x40
/* 802F6F28 002F3B08  4B D2 C8 81 */	bl func_800237A8
/* 802F6F2C 002F3B0C  48 00 00 F4 */	b lbl_802F7020
lbl_802F6F30:
/* 802F6F30 002F3B10  1C 83 00 28 */	mulli r4, r3, 0x28
/* 802F6F34 002F3B14  3C 60 80 40 */	lis r3, lbl_803F9628@ha
/* 802F6F38 002F3B18  38 03 96 28 */	addi r0, r3, lbl_803F9628@l
/* 802F6F3C 002F3B1C  7F 60 22 14 */	add r27, r0, r4
/* 802F6F40 002F3B20  93 BB 00 20 */	stw r29, 0x20(r27)
/* 802F6F44 002F3B24  93 9B 00 24 */	stw r28, 0x24(r27)
/* 802F6F48 002F3B28  98 DB 00 11 */	stb r6, 0x11(r27)
/* 802F6F4C 002F3B2C  80 7B 00 00 */	lwz r3, 0(r27)
/* 802F6F50 002F3B30  28 03 00 00 */	cmplwi r3, 0
/* 802F6F54 002F3B34  41 82 00 08 */	beq lbl_802F6F5C
/* 802F6F58 002F3B38  48 09 92 D1 */	bl func_80390228
lbl_802F6F5C:
/* 802F6F5C 002F3B3C  38 60 00 0E */	li r3, 0xe
/* 802F6F60 002F3B40  38 80 00 0E */	li r4, 0xe
/* 802F6F64 002F3B44  38 A0 00 00 */	li r5, 0
/* 802F6F68 002F3B48  48 09 92 89 */	bl func_803901F0
/* 802F6F6C 002F3B4C  80 9B 00 14 */	lwz r4, 0x14(r27)
/* 802F6F70 002F3B50  7C 7D 1B 78 */	mr r29, r3
/* 802F6F74 002F3B54  80 64 00 00 */	lwz r3, 0(r4)
/* 802F6F78 002F3B58  48 07 9E CD */	bl HSD_JObjLoadJoint
/* 802F6F7C 002F3B5C  3B 83 00 00 */	addi r28, r3, 0
/* 802F6F80 002F3B60  3C 80 08 00 */	lis r4, 0x800
/* 802F6F84 002F3B64  4B D1 AC 95 */	bl func_80011C18
/* 802F6F88 002F3B68  88 8D C1 A9 */	lbz r4, lbl_804D7849@sda21(r13)
/* 802F6F8C 002F3B6C  38 7D 00 00 */	addi r3, r29, 0
/* 802F6F90 002F3B70  38 BC 00 00 */	addi r5, r28, 0
/* 802F6F94 002F3B74  48 09 9A DD */	bl func_80390A70
/* 802F6F98 002F3B78  3C 60 80 39 */	lis r3, func_80391070@ha
/* 802F6F9C 002F3B7C  38 83 10 70 */	addi r4, r3, func_80391070@l
/* 802F6FA0 002F3B80  38 7D 00 00 */	addi r3, r29, 0
/* 802F6FA4 002F3B84  38 A0 00 0B */	li r5, 0xb
/* 802F6FA8 002F3B88  38 C0 00 00 */	li r6, 0
/* 802F6FAC 002F3B8C  48 09 96 F1 */	bl GObj_SetupGXLink
/* 802F6FB0 002F3B90  80 9B 00 08 */	lwz r4, 8(r27)
/* 802F6FB4 002F3B94  28 04 00 00 */	cmplwi r4, 0
/* 802F6FB8 002F3B98  41 82 00 10 */	beq lbl_802F6FC8
/* 802F6FBC 002F3B9C  38 7D 00 00 */	addi r3, r29, 0
/* 802F6FC0 002F3BA0  38 A0 00 00 */	li r5, 0
/* 802F6FC4 002F3BA4  48 09 8D 91 */	bl func_8038FD54
lbl_802F6FC8:
/* 802F6FC8 002F3BA8  80 BB 00 14 */	lwz r5, 0x14(r27)
/* 802F6FCC 002F3BAC  38 7C 00 00 */	addi r3, r28, 0
/* 802F6FD0 002F3BB0  38 80 00 00 */	li r4, 0
/* 802F6FD4 002F3BB4  4B D1 51 15 */	bl func_8000C0E8
/* 802F6FD8 002F3BB8  7F 83 E3 78 */	mr r3, r28
/* 802F6FDC 002F3BBC  C0 22 E0 C8 */	lfs f1, lbl_804DDAA8@sda21(r2)
/* 802F6FE0 002F3BC0  48 07 88 DD */	bl HSD_JObjReqAnimAll
/* 802F6FE4 002F3BC4  7F 83 E3 78 */	mr r3, r28
/* 802F6FE8 002F3BC8  48 07 99 41 */	bl HSD_JObjAnimAll
/* 802F6FEC 002F3BCC  88 1B 00 12 */	lbz r0, 0x12(r27)
/* 802F6FF0 002F3BD0  38 60 00 00 */	li r3, 0
/* 802F6FF4 002F3BD4  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 802F6FF8 002F3BD8  98 1B 00 12 */	stb r0, 0x12(r27)
/* 802F6FFC 002F3BDC  88 1B 00 12 */	lbz r0, 0x12(r27)
/* 802F7000 002F3BE0  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 802F7004 002F3BE4  98 1B 00 12 */	stb r0, 0x12(r27)
/* 802F7008 002F3BE8  88 1B 00 12 */	lbz r0, 0x12(r27)
/* 802F700C 002F3BEC  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 802F7010 002F3BF0  98 1B 00 12 */	stb r0, 0x12(r27)
/* 802F7014 002F3BF4  93 BB 00 00 */	stw r29, 0(r27)
/* 802F7018 002F3BF8  93 DB 00 18 */	stw r30, 0x18(r27)
/* 802F701C 002F3BFC  93 FB 00 1C */	stw r31, 0x1c(r27)
lbl_802F7020:
/* 802F7020 002F3C00  BB 61 00 24 */	lmw r27, 0x24(r1)
/* 802F7024 002F3C04  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 802F7028 002F3C08  38 21 00 38 */	addi r1, r1, 0x38
/* 802F702C 002F3C0C  7C 08 03 A6 */	mtlr r0
/* 802F7030 002F3C10  4E 80 00 20 */	blr 
}

asm unk_t func_802F7034()
{
/* 802F7034 002F3C14  7C 08 02 A6 */	mflr r0
/* 802F7038 002F3C18  90 01 00 04 */	stw r0, 4(r1)
/* 802F703C 002F3C1C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802F7040 002F3C20  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802F7044 002F3C24  7C 7F 1B 78 */	mr r31, r3
/* 802F7048 002F3C28  4B E7 3D F1 */	bl func_8016AE38
/* 802F704C 002F3C2C  80 83 00 10 */	lwz r4, 0x10(r3)
/* 802F7050 002F3C30  2C 04 00 00 */	cmpwi r4, 0
/* 802F7054 002F3C34  41 82 00 0C */	beq lbl_802F7060
/* 802F7058 002F3C38  38 84 FF FF */	addi r4, r4, -1
/* 802F705C 002F3C3C  48 00 00 08 */	b lbl_802F7064
lbl_802F7060:
/* 802F7060 002F3C40  38 80 FF FF */	li r4, -1
lbl_802F7064:
/* 802F7064 002F3C44  80 A3 00 14 */	lwz r5, 0x14(r3)
/* 802F7068 002F3C48  2C 05 00 00 */	cmpwi r5, 0
/* 802F706C 002F3C4C  41 82 00 0C */	beq lbl_802F7078
/* 802F7070 002F3C50  38 A5 FF FF */	addi r5, r5, -1
/* 802F7074 002F3C54  48 00 00 08 */	b lbl_802F707C
lbl_802F7078:
/* 802F7078 002F3C58  38 A0 FF FF */	li r5, -1
lbl_802F707C:
/* 802F707C 002F3C5C  88 03 00 18 */	lbz r0, 0x18(r3)
/* 802F7080 002F3C60  28 00 00 00 */	cmplwi r0, 0
/* 802F7084 002F3C64  41 82 00 0C */	beq lbl_802F7090
/* 802F7088 002F3C68  7C 06 03 78 */	mr r6, r0
/* 802F708C 002F3C6C  48 00 00 08 */	b lbl_802F7094
lbl_802F7090:
/* 802F7090 002F3C70  38 C0 00 00 */	li r6, 0
lbl_802F7094:
/* 802F7094 002F3C74  89 03 00 0B */	lbz r8, 0xb(r3)
/* 802F7098 002F3C78  28 08 00 00 */	cmplwi r8, 0
/* 802F709C 002F3C7C  41 82 00 18 */	beq lbl_802F70B4
/* 802F70A0 002F3C80  38 68 FF FF */	addi r3, r8, -1
/* 802F70A4 002F3C84  38 FF 00 00 */	addi r7, r31, 0
/* 802F70A8 002F3C88  39 00 00 00 */	li r8, 0
/* 802F70AC 002F3C8C  4B FF FD F9 */	bl func_802F6EA4
/* 802F70B0 002F3C90  48 00 00 70 */	b lbl_802F7120
lbl_802F70B4:
/* 802F70B4 002F3C94  88 E3 00 08 */	lbz r7, 8(r3)
/* 802F70B8 002F3C98  28 07 00 01 */	cmplwi r7, 1
/* 802F70BC 002F3C9C  40 82 00 18 */	bne lbl_802F70D4
/* 802F70C0 002F3CA0  38 FF 00 00 */	addi r7, r31, 0
/* 802F70C4 002F3CA4  38 60 00 00 */	li r3, 0
/* 802F70C8 002F3CA8  39 00 00 00 */	li r8, 0
/* 802F70CC 002F3CAC  4B FF FD D9 */	bl func_802F6EA4
/* 802F70D0 002F3CB0  48 00 00 50 */	b lbl_802F7120
lbl_802F70D4:
/* 802F70D4 002F3CB4  88 03 24 CD */	lbz r0, 0x24cd(r3)
/* 802F70D8 002F3CB8  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 802F70DC 002F3CBC  41 82 00 34 */	beq lbl_802F7110
/* 802F70E0 002F3CC0  28 07 00 06 */	cmplwi r7, 6
/* 802F70E4 002F3CC4  40 82 00 18 */	bne lbl_802F70FC
/* 802F70E8 002F3CC8  38 FF 00 00 */	addi r7, r31, 0
/* 802F70EC 002F3CCC  38 60 00 07 */	li r3, 7
/* 802F70F0 002F3CD0  39 00 00 00 */	li r8, 0
/* 802F70F4 002F3CD4  4B FF FD B1 */	bl func_802F6EA4
/* 802F70F8 002F3CD8  48 00 00 28 */	b lbl_802F7120
lbl_802F70FC:
/* 802F70FC 002F3CDC  38 FF 00 00 */	addi r7, r31, 0
/* 802F7100 002F3CE0  38 60 00 06 */	li r3, 6
/* 802F7104 002F3CE4  39 00 00 00 */	li r8, 0
/* 802F7108 002F3CE8  4B FF FD 9D */	bl func_802F6EA4
/* 802F710C 002F3CEC  48 00 00 14 */	b lbl_802F7120
lbl_802F7110:
/* 802F7110 002F3CF0  38 FF 00 00 */	addi r7, r31, 0
/* 802F7114 002F3CF4  38 60 00 05 */	li r3, 5
/* 802F7118 002F3CF8  39 00 00 00 */	li r8, 0
/* 802F711C 002F3CFC  4B FF FD 89 */	bl func_802F6EA4
lbl_802F7120:
/* 802F7120 002F3D00  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802F7124 002F3D04  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802F7128 002F3D08  38 21 00 18 */	addi r1, r1, 0x18
/* 802F712C 002F3D0C  7C 08 03 A6 */	mtlr r0
/* 802F7130 002F3D10  4E 80 00 20 */	blr 
}

// in progress
// https://decomp.me/scratch/XzfAH
asm unk_t func_802F7134()
{
/* 802F7134 002F3D14  7C 08 02 A6 */	mflr r0
/* 802F7138 002F3D18  3C 60 80 40 */	lis r3, lbl_803F9628@ha
/* 802F713C 002F3D1C  90 01 00 04 */	stw r0, 4(r1)
/* 802F7140 002F3D20  38 00 00 00 */	li r0, 0
/* 802F7144 002F3D24  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 802F7148 002F3D28  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 802F714C 002F3D2C  3B E3 96 28 */	addi r31, r3, lbl_803F9628@l
/* 802F7150 002F3D30  90 1F 00 00 */	stw r0, 0(r31)
/* 802F7154 002F3D34  90 1F 00 04 */	stw r0, 4(r31)
/* 802F7158 002F3D38  90 1F 00 28 */	stw r0, 0x28(r31)
/* 802F715C 002F3D3C  90 1F 00 2C */	stw r0, 0x2c(r31)
/* 802F7160 002F3D40  90 1F 00 50 */	stw r0, 0x50(r31)
/* 802F7164 002F3D44  90 1F 00 54 */	stw r0, 0x54(r31)
/* 802F7168 002F3D48  90 1F 00 78 */	stw r0, 0x78(r31)
/* 802F716C 002F3D4C  90 1F 00 7C */	stw r0, 0x7c(r31)
/* 802F7170 002F3D50  90 1F 00 A0 */	stw r0, 0xa0(r31)
/* 802F7174 002F3D54  90 1F 00 A4 */	stw r0, 0xa4(r31)
/* 802F7178 002F3D58  90 1F 00 C8 */	stw r0, 0xc8(r31)
/* 802F717C 002F3D5C  90 1F 00 CC */	stw r0, 0xcc(r31)
/* 802F7180 002F3D60  90 1F 00 F0 */	stw r0, 0xf0(r31)
/* 802F7184 002F3D64  90 1F 00 F4 */	stw r0, 0xf4(r31)
/* 802F7188 002F3D68  90 1F 01 18 */	stw r0, 0x118(r31)
/* 802F718C 002F3D6C  90 1F 01 1C */	stw r0, 0x11c(r31)
/* 802F7190 002F3D70  4B FF C5 01 */	bl func_802F3690
/* 802F7194 002F3D74  80 63 00 00 */	lwz r3, 0(r3)
/* 802F7198 002F3D78  38 81 00 1C */	addi r4, r1, 0x1c
/* 802F719C 002F3D7C  38 BF 01 40 */	addi r5, r31, 0x140
/* 802F71A0 002F3D80  4C C6 31 82 */	crclr 6
/* 802F71A4 002F3D84  38 C0 00 00 */	li r6, 0
/* 802F71A8 002F3D88  4B D1 F9 49 */	bl func_80016AF0
/* 802F71AC 002F3D8C  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71B0 002F3D90  80 03 00 00 */	lwz r0, 0(r3)
/* 802F71B4 002F3D94  90 1F 00 14 */	stw r0, 0x14(r31)
/* 802F71B8 002F3D98  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71BC 002F3D9C  80 03 00 04 */	lwz r0, 4(r3)
/* 802F71C0 002F3DA0  90 1F 00 3C */	stw r0, 0x3c(r31)
/* 802F71C4 002F3DA4  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71C8 002F3DA8  80 03 00 08 */	lwz r0, 8(r3)
/* 802F71CC 002F3DAC  90 1F 00 64 */	stw r0, 0x64(r31)
/* 802F71D0 002F3DB0  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71D4 002F3DB4  80 03 00 0C */	lwz r0, 0xc(r3)
/* 802F71D8 002F3DB8  90 1F 00 8C */	stw r0, 0x8c(r31)
/* 802F71DC 002F3DBC  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71E0 002F3DC0  80 03 00 10 */	lwz r0, 0x10(r3)
/* 802F71E4 002F3DC4  90 1F 00 B4 */	stw r0, 0xb4(r31)
/* 802F71E8 002F3DC8  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71EC 002F3DCC  80 03 00 14 */	lwz r0, 0x14(r3)
/* 802F71F0 002F3DD0  90 1F 00 DC */	stw r0, 0xdc(r31)
/* 802F71F4 002F3DD4  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71F8 002F3DD8  80 03 00 18 */	lwz r0, 0x18(r3)
/* 802F71FC 002F3DDC  90 1F 01 04 */	stw r0, 0x104(r31)
/* 802F7200 002F3DE0  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F7204 002F3DE4  80 03 00 1C */	lwz r0, 0x1c(r3)
/* 802F7208 002F3DE8  90 1F 01 2C */	stw r0, 0x12c(r31)
/* 802F720C 002F3DEC  80 01 00 34 */	lwz r0, 0x34(r1)
/* 802F7210 002F3DF0  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 802F7214 002F3DF4  38 21 00 30 */	addi r1, r1, 0x30
/* 802F7218 002F3DF8  7C 08 03 A6 */	mtlr r0
/* 802F721C 002F3DFC  4E 80 00 20 */	blr 
}

// free
void func_802F7220(void) {
    s32 i;
    for (i = 0; i < 8; i++) {
        if (lbl_803F9628.things[i].unk0 != NULL) {
            func_80390228(lbl_803F9628.things[i].unk0);
            lbl_803F9628.things[i].unk0 = NULL;
        }
    }
}


