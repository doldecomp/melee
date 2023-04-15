#ifndef MELEE_FT_CHARA_FTPIKACHU_FTPIKACHU_H
#define MELEE_FT_CHARA_FTPIKACHU_FTPIKACHU_H

#include "ft/ftcommon.h"
#include "lb/lbvector.h"

/// pika1
void ftPk_Init_OnLoadForPichu(Fighter* fp);
void ftPk_Init_OnLoad(HSD_GObj* gobj);
void ftPk_Init_OnDeath(HSD_GObj* gobj);
void ftPk_Init_OnItemPickup(HSD_GObj* gobj, bool arg1);
void ftPk_Init_OnItemInvisible(HSD_GObj* gobj);
void ftPk_Init_OnItemVisible(HSD_GObj* gobj);
void ftPk_Init_OnItemDrop(HSD_GObj* gobj, bool arg1);
void ftPk_Init_UnkMotionStates1(HSD_GObj* gobj);
void ftPk_Init_UnkMotionStates2(HSD_GObj* gobj);
void ftPk_Init_LoadSpecialAttrs(HSD_GObj* gobj);
void ftPk_Init_OnKnockbackEnter(HSD_GObj* gobj);
void ftPk_Init_OnKnockbackExit(HSD_GObj* gobj);

/// pika2
void ftPk_SpecialN_StartMotion(HSD_GObj* gobj);
void ftPk_SpecialAirN_StartMotion(HSD_GObj* gobj);
void ftPk_SpecialN_80124908(HSD_GObj* gobj);
void ftPk_SpecialN_80124A20(HSD_GObj* gobj);
void ftPk_SpecialN_80124B74(HSD_GObj* gobj);
void ftPk_SpecialN_80124B94(HSD_GObj* gobj);
void ftPk_SpecialN_ChangeMotion_Unk0(HSD_GObj* gobj);
void ftPk_SpecialN_ChangeMotion_Unk1(HSD_GObj* gobj);
void ftPk_SpecialN_SpawnEffect0(HSD_GObj* gobj);
void ftPk_SpecialN_SpawnEffect1(HSD_GObj* gobj);
void ftPk_SpecialN_80124DC8(HSD_GObj* gobj);

// pika3
void ftPk_SpecialS_StartMotion(HSD_GObj* gobj);
void ftPk_SpecialAirS_StartMotion(HSD_GObj* gobj);
void ftPk_SpecialS_ZeroVelocity(HSD_GObj* gobj);
void ftPk_SpecialS_80124F64(HSD_GObj* gobj);
void ftPk_SpecialS_80124FA0(HSD_GObj* gobj);
void ftPk_SpecialS_80124FE4(HSD_GObj* gobj);
void ftPk_SpecialS_80125024(HSD_GObj* gobj);
void ftPk_SpecialS_80125084(HSD_GObj* gobj);
void ftPk_SpecialS_801250C0(HSD_GObj* gobj);
void ftPk_SpecialS_ChangeMotion_Unk00(HSD_GObj* gobj);
void ftPk_SpecialS_ChangeMotion_Unk01(HSD_GObj* gobj);
void ftPk_SpecialS_801251BC(HSD_GObj* gobj);
void ftPk_SpecialS_8012525C(HSD_GObj* gobj);
void ftPk_SpecialS_801252FC(HSD_GObj* gobj);
void ftPk_SpecialS_8012532C(HSD_GObj* gobj);
void ftPk_SpecialS_8012535C(HSD_GObj* gobj);
void ftPk_SpecialS_8012537C(HSD_GObj* gobj);
void ftPk_SpecialS_8012539C(HSD_GObj* gobj);
void ftPk_SpecialS_801253D8(HSD_GObj* gobj);
void ftPk_SpecialS_ChangeMotion_Unk02(HSD_GObj* gobj);
void ftPk_SpecialS_ChangeMotion_Unk03(HSD_GObj* gobj);
void ftPk_SpecialS_ChangeMotion_Unk04(HSD_GObj* gobj);
void ftPk_SpecialS_ChangeMotion_Unk05(HSD_GObj* gobj);
void ftPk_SpecialS_8012557C(HSD_GObj* gobj);
void ftPk_SpecialS_8012561C(HSD_GObj* gobj);
void ftPk_SpecialS_801256BC(HSD_GObj* gobj);
void ftPk_SpecialS_801256DC(HSD_GObj* gobj);
void ftPk_SpecialS_801256FC(HSD_GObj* gobj);
void ftPk_SpecialS_80125738(HSD_GObj* gobj);
void ftPk_SpecialS_ChangeMotion_Unk06(HSD_GObj* gobj);
void ftPk_SpecialS_ChangeMotion_Unk07(HSD_GObj* gobj);
void ftPk_SpecialS_ChangeMotion_Unk08(HSD_GObj* gobj);
void ftPk_SpecialS_ChangeMotion_Unk09(HSD_GObj* gobj);
void ftPk_SpecialS_80125910(HSD_GObj* gobj);
void ftPk_SpecialS_80125958(HSD_GObj* gobj);
void ftPk_SpecialS_801259D8(HSD_GObj* gobj);
void ftPk_SpecialS_ChangeMotion_Unk10(HSD_GObj* gobj);
void ftPk_SpecialS_80125B34(HSD_GObj* gobj);
void ftPk_SpecialS_80125B70(HSD_GObj* gobj);
void ftPk_SpecialS_80125BB4(HSD_GObj* gobj);
void ftPk_SpecialS_80125BF4(HSD_GObj* gobj);
void ftPk_SpecialS_80125C44(HSD_GObj* gobj);
void ftPk_SpecialS_80125C80(HSD_GObj* gobj);
void ftPk_SpecialS_ChangeMotion_Unk11(HSD_GObj* gobj);
void ftPk_SpecialS_ChangeMotion_Unk12(HSD_GObj* gobj);

/// pika4
void ftPk_SpecialHi_UpdateVel(HSD_GObj* gobj);
void ftPk_SpecialHi_StartMotion(HSD_GObj* gobj);
void ftPk_SpecialAirHi_StartMotion(HSD_GObj* gobj);
void ftPk_SpecialHi_80125ED8(HSD_GObj* gobj);
void ftPk_SpecialHi_80125F14(HSD_GObj* gobj);
void ftPk_SpecialHi_80125F58(HSD_GObj* gobj);
void ftPk_SpecialHi_80125F78(HSD_GObj* gobj);
void ftPk_SpecialHi_80125FD8(HSD_GObj* gobj);
void ftPk_SpecialHi_80126014(HSD_GObj* gobj);
void ftPk_SpecialHi_ChangeMotion_Unk00(HSD_GObj* gobj);
void ftPk_SpecialHi_ChangeMotion_Unk01(HSD_GObj* gobj);
void ftPk_SpecialHi_80126144(HSD_GObj* gobj);
void ftPk_SpecialHi_801262B4(HSD_GObj* gobj);
void ftPk_SpecialHi_8012642C(HSD_GObj* gobj);
void ftPk_SpecialHi_801265D4(HSD_GObj* gobj);
void ftPk_SpecialHi_801265F4(HSD_GObj* gobj);
void ftPk_SpecialHi_80126614(HSD_GObj* gobj);
void ftPk_SpecialHi_801267C8(HSD_GObj* gobj);
void ftPk_SpecialHi_ChangeMotion_Unk02(HSD_GObj* gobj);
void ftPk_SpecialHi_ChangeMotion_Unk03(HSD_GObj* gobj);
void ftPk_SpecialHi_80126C0C(HSD_GObj* gobj);
void ftPk_SpecialHi_80126E1C(HSD_GObj* gobj);
bool ftPk_SpecialHi_80127064(HSD_GObj* gobj);
void ftPk_SpecialHi_80127198(HSD_GObj* gobj);
void ftPk_SpecialHi_80127228(HSD_GObj* gobj);
void ftPk_SpecialHi_801272E0(HSD_GObj* gobj);
void ftPk_SpecialHi_80127310(HSD_GObj* gobj);
void ftPk_SpecialHi_8012738C(HSD_GObj* gobj);
void ftPk_SpecialHi_801273D4(HSD_GObj* gobj);
void ftPk_SpecialHi_ChangeMotion_Unk04(HSD_GObj* gobj);
void ftPk_SpecialHi_MotionChangeUpdateVel_Unk0(HSD_GObj* gobj);
void ftPk_SpecialHi_MotionChangeUpdateVel_Unk1(HSD_GObj* gobj);

// pika5
bool ftPk_SpecialLw_CheckProperty(HSD_GObj* gobj);
void ftPk_SpecialLw_80127608(HSD_GObj* gobj);
void ftPk_SpecialLw_SetState_Unk0(HSD_GObj* gobj);
bool ftPk_SpecialLw_8012765C(HSD_GObj* gobj);
void ftPk_SpecialLw_SetState_Unk1(HSD_GObj* gobj);
void ftPk_SpecialLw_SpawnEffect(HSD_GObj* gobj);
void ftPk_SpecialLw_StartMotion(HSD_GObj* gobj);
void ftPk_SpecialAirLw_StartMotion(HSD_GObj* gobj);
void ftPk_SpecialLw_ChangeMotion_Unk00(HSD_GObj* gobj);
void ftPk_SpecialLw_ChangeMotion_Unk01(HSD_GObj* gobj);
void ftPk_SpecialLw_ChangeMotion_Unk02(HSD_GObj* gobj);
void ftPk_SpecialLw_ChangeMotion_Unk03(HSD_GObj* gobj);
void ftPk_SpecialLw_ChangeMotion_Unk04(HSD_GObj* gobj);
void ftPk_SpecialLw_ChangeMotion_Unk05(HSD_GObj* gobj);
void ftPk_SpecialLw_ChangeMotion_Unk06(HSD_GObj* gobj);
void ftPk_SpecialLw_ChangeMotion_Unk07(HSD_GObj* gobj);
void ftPk_SpecialLw_ChangeMotion_Unk08(HSD_GObj* gobj);
void ftPk_SpecialLw_ChangeMotion_Unk09(HSD_GObj* gobj);
void ftPk_SpecialLw_ChangeMotion_Unk10(HSD_GObj* gobj);
void ftPk_SpecialLw_ChangeMotion_Unk11(HSD_GObj* gobj);
void ftPk_SpecialLw_ChangeMotion_Unk12(HSD_GObj* gobj);
void ftPk_SpecialLw_ChangeMotion_Unk13(HSD_GObj* gobj);
void ftPk_SpecialLw_80128050(HSD_GObj* gobj);
void ftPk_SpecialLw_8012808C(HSD_GObj* gobj);
void ftPk_SpecialLw_801280C8(HSD_GObj* gobj);
void ftPk_SpecialLw_801280E8(HSD_GObj* gobj);
void ftPk_SpecialLw_80128108(HSD_GObj* gobj);
void ftPk_SpecialLw_80128128(HSD_GObj* gobj);
void ftPk_SpecialLw_80128148(HSD_GObj* gobj);
void ftPk_SpecialLw_80128168(HSD_GObj* gobj);
void ftPk_SpecialLw_801281AC(HSD_GObj* gobj);
void ftPk_SpecialLw_801281CC(HSD_GObj* gobj);
void ftPk_SpecialLw_PrepCallMotionChange_Unk0(HSD_GObj* gobj);
void ftPk_SpecialLw_PrepCallMotionChange_Unk1(HSD_GObj* gobj);
void ftPk_SpecialLw_PrepCallMotionChange_Unk2(HSD_GObj* gobj);
void ftPk_SpecialLw_PrepCallMotionChange_Unk3(HSD_GObj* gobj);
void ftPk_SpecialLw_PrepCallMotionChange_Unk4(HSD_GObj* gobj);
void ftPk_SpecialLw_PrepCallMotionChange_Unk5(HSD_GObj* gobj);
void ftPk_SpecialLw_PrepCallMotionChange_Unk6(HSD_GObj* gobj);
void ftPk_SpecialLw_PrepCallMotionChange_Unk7(HSD_GObj* gobj);

void ftPk_SpecialN_80124908(HSD_GObj*);
void ftPk_SpecialN_80124B6C(HSD_GObj*);
void ftPk_SpecialN_80124B74(HSD_GObj*);
void ftPk_SpecialN_ChangeMotion_Unk0(HSD_GObj*);
void ftPk_SpecialN_80124A20(HSD_GObj*);
void ftPk_SpecialN_80124B70(HSD_GObj*);
void ftPk_SpecialN_80124B94(HSD_GObj*);
void ftPk_SpecialN_ChangeMotion_Unk1(HSD_GObj*);
void ftPk_SpecialS_80124F64(HSD_GObj*);
void ftPk_SpecialS_80124FDC(HSD_GObj*);
void ftPk_SpecialS_80124FE4(HSD_GObj*);
void ftPk_SpecialS_80125084(HSD_GObj*);
void ftPk_SpecialS_801251BC(HSD_GObj*);
void ftPk_SpecialS_801252FC(HSD_GObj*);
void ftPk_SpecialS_8012535C(HSD_GObj*);
void ftPk_SpecialS_8012539C(HSD_GObj*);
void ftPk_SpecialS_8012590C(HSD_GObj*);
void ftPk_SpecialS_8012594C(HSD_GObj*);
void ftPk_SpecialS_80125954(HSD_GObj*);
void ftPk_SpecialS_801259D4(HSD_GObj*);
void ftPk_SpecialS_80125B34(HSD_GObj*);
void ftPk_SpecialS_80125BAC(HSD_GObj*);
void ftPk_SpecialS_80125BB4(HSD_GObj*);
void ftPk_SpecialS_80125C44(HSD_GObj*);
void ftPk_SpecialS_8012557C(HSD_GObj*);
void ftPk_SpecialS_801256B4(HSD_GObj*);
void ftPk_SpecialS_801256BC(HSD_GObj*);
void ftPk_SpecialS_801256FC(HSD_GObj*);
void ftPk_SpecialS_80124FA0(HSD_GObj*);
void ftPk_SpecialS_80124FE0(HSD_GObj*);
void ftPk_SpecialS_80125024(HSD_GObj*);
void ftPk_SpecialS_801250C0(HSD_GObj*);
void ftPk_SpecialS_8012525C(HSD_GObj*);
void ftPk_SpecialS_8012532C(HSD_GObj*);
void ftPk_SpecialS_8012537C(HSD_GObj*);
void ftPk_SpecialS_801253D8(HSD_GObj*);
void ftPk_SpecialS_80125910(HSD_GObj*);
void ftPk_SpecialS_80125950(HSD_GObj*);
void ftPk_SpecialS_80125958(HSD_GObj*);
void ftPk_SpecialS_801259D8(HSD_GObj*);
void ftPk_SpecialS_80125B70(HSD_GObj*);
void ftPk_SpecialS_80125BB0(HSD_GObj*);
void ftPk_SpecialS_80125BF4(HSD_GObj*);
void ftPk_SpecialS_80125C80(HSD_GObj*);
void ftPk_SpecialS_8012561C(HSD_GObj*);
void ftPk_SpecialS_801256B8(HSD_GObj*);
void ftPk_SpecialS_801256DC(HSD_GObj*);
void ftPk_SpecialS_80125738(HSD_GObj*);
void ftPk_SpecialHi_80125ED8(HSD_GObj*);
void ftPk_SpecialHi_80125F50(HSD_GObj*);
void ftPk_SpecialHi_80125F58(HSD_GObj*);
void ftPk_SpecialHi_80125FD8(HSD_GObj*);
void ftPk_SpecialHi_80126144(HSD_GObj*);
void ftPk_SpecialHi_80126424(HSD_GObj*);
void ftPk_SpecialHi_801265D4(HSD_GObj*);
void ftPk_SpecialHi_80126614(HSD_GObj*);
void ftPk_SpecialHi_80127198(HSD_GObj*);
void ftPk_SpecialHi_801272D8(HSD_GObj*);
void ftPk_SpecialHi_801272E0(HSD_GObj*);
void ftPk_SpecialHi_8012738C(HSD_GObj*);
void ftPk_SpecialHi_80125F14(HSD_GObj*);
void ftPk_SpecialHi_80125F54(HSD_GObj*);
void ftPk_SpecialHi_80125F78(HSD_GObj*);
void ftPk_SpecialHi_80126014(HSD_GObj*);
void ftPk_SpecialHi_801262B4(HSD_GObj*);
void ftPk_SpecialHi_80126428(HSD_GObj*);
void ftPk_SpecialHi_801265F4(HSD_GObj*);
void ftPk_SpecialHi_801267C8(HSD_GObj*);
void ftPk_SpecialHi_80127228(HSD_GObj*);
void ftPk_SpecialHi_801272DC(HSD_GObj*);
void ftPk_SpecialHi_80127310(HSD_GObj*);
void ftPk_SpecialHi_801273D4(HSD_GObj*);
void ftPk_SpecialLw_ChangeMotion_Unk08(HSD_GObj*);
void ftPk_SpecialLw_801280C8(HSD_GObj*);
void ftPk_SpecialLw_PrepCallMotionChange_Unk0(HSD_GObj*);
void ftPk_SpecialLw_ChangeMotion_Unk10(HSD_GObj*);
void ftPk_SpecialLw_80128108(HSD_GObj*);
void ftPk_SpecialLw_PrepCallMotionChange_Unk2(HSD_GObj*);
void ftPk_SpecialLw_ChangeMotion_Unk12(HSD_GObj*);
void ftPk_SpecialLw_80128148(HSD_GObj*);
void ftPk_SpecialLw_PrepCallMotionChange_Unk4(HSD_GObj*);
void ftPk_SpecialLw_80128050(HSD_GObj*);
void ftPk_SpecialLw_801281AC(HSD_GObj*);
void ftPk_SpecialLw_PrepCallMotionChange_Unk6(HSD_GObj*);
void ftPk_SpecialLw_ChangeMotion_Unk09(HSD_GObj*);
void ftPk_SpecialLw_801280E8(HSD_GObj*);
void ftPk_SpecialLw_PrepCallMotionChange_Unk1(HSD_GObj*);
void ftPk_SpecialLw_ChangeMotion_Unk11(HSD_GObj*);
void ftPk_SpecialLw_80128128(HSD_GObj*);
void ftPk_SpecialLw_PrepCallMotionChange_Unk3(HSD_GObj*);
void ftPk_SpecialLw_ChangeMotion_Unk13(HSD_GObj*);
void ftPk_SpecialLw_80128168(HSD_GObj*);
void ftPk_SpecialLw_PrepCallMotionChange_Unk5(HSD_GObj*);
void ftPk_SpecialLw_8012808C(HSD_GObj*);
void ftPk_SpecialLw_801281CC(HSD_GObj*);
void ftPk_SpecialLw_PrepCallMotionChange_Unk7(HSD_GObj*);

#endif
