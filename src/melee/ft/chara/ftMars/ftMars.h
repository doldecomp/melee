#ifndef _ftmars_h_
#define _ftmars_h_

#include <platform.h>

#include "ft/fighter.h"

#include <baselib/gobj.h>

extern MotionState ftMs_Init_MotionStateTable[];
extern char ftMs_Init_DatFilename[];
extern char ftMs_Init_DataName[];
extern Fighter_CostumeStrings ftMs_Init_CostumeStrings[];
extern char ftMs_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftMs_Init_DemoMotionFilenames;

void ftMs_Init_OnDeath(HSD_GObj* gobj);
void ftMs_Init_OnItemPickup(HSD_GObj* gobj, bool arg1);
void ftMs_Init_OnItemInvisible(HSD_GObj* gobj);
void ftMs_Init_OnItemVisible(HSD_GObj* gobj);
void ftMs_Init_OnItemDrop(HSD_GObj* gobj, bool arg1);
void ftMs_OnLoadForRoy(Fighter* fp);
void ftMs_Init_OnLoad(HSD_GObj* gobj);
void ftMs_Init_LoadSpecialAttrs(HSD_GObj* gobj);
void ftMs_Init_OnKnockbackEnter(HSD_GObj* gobj);
void ftMs_Init_OnKnockbackExit(HSD_GObj* gobj);
void ftMs_Init_801365A8(HSD_GObj* gobj);
void ftMs_Init_8013666C(HSD_GObj* gobj);
void ftMs_Init_80136730(HSD_GObj* gobj);

void ftMs_SpecialN_StartMotion(HSD_GObj* gobj);
void ftMs_SpecialAirN_StartMotion(HSD_GObj* gobj);
void ftMs_SpecialN_80136844(HSD_GObj* gobj);
void ftMs_SpecialN_801368AC(HSD_GObj* gobj);
void ftMs_SpecialN_80136914(HSD_GObj* gobj);
void ftMs_SpecialN_80136918(HSD_GObj* gobj);
void ftMs_SpecialN_8013691C(HSD_GObj* gobj);
void ftMs_SpecialN_8013695C(HSD_GObj* gobj);
void ftMs_SpecialN_801369A4(HSD_GObj* gobj);
void ftMs_SpecialN_801369E0(HSD_GObj* gobj);
void ftMs_SpecialN_80136A1C(HSD_GObj* gobj);
void ftMs_SpecialN_80136A7C(HSD_GObj* gobj);
void ftMs_SpecialN_80136ADC(HSD_GObj* gobj);
void ftMs_SpecialN_80136BB4(HSD_GObj* gobj);
void ftMs_SpecialN_80136C8C(HSD_GObj* gobj);
void ftMs_SpecialN_80136CC4(HSD_GObj* gobj);
void ftMs_SpecialN_80136CFC(HSD_GObj* gobj);
void ftMs_SpecialN_80136D1C(HSD_GObj* gobj);
void ftMs_SpecialN_80136D3C(HSD_GObj* gobj);
void ftMs_SpecialN_80136D78(HSD_GObj* gobj);
void ftMs_SpecialN_80136DB4(HSD_GObj* gobj);
void ftMs_SpecialN_80136E14(HSD_GObj* gobj);
void ftMs_SpecialN_80136E74(HSD_GObj* gobj);
void ftMs_SpecialN_80136EAC(HSD_GObj* gobj);
void ftMs_SpecialN_80136EE4(HSD_GObj* gobj);
void ftMs_SpecialN_80137010(HSD_GObj* gobj);
void ftMs_SpecialN_8013713C(HSD_GObj* gobj);
void ftMs_SpecialN_80137140(HSD_GObj* gobj);
void ftMs_SpecialN_80137144(HSD_GObj* gobj);
void ftMs_SpecialN_80137164(HSD_GObj* gobj);
void ftMs_SpecialN_80137184(HSD_GObj* gobj);
void ftMs_SpecialN_801371C0(HSD_GObj* arg0);
void ftMs_SpecialN_801371FC(HSD_GObj* gobj);
void ftMs_SpecialN_801372A8(HSD_GObj* gobj);
void ftMs_SpecialN_80137354(HSD_GObj* gobj);
void ftMs_SpecialN_801373B8(HSD_GObj* gobj);

void ftMs_SpecialS_StartMotion(HSD_GObj* gobj);
void ftMs_SpecialAirS_StartMotion(HSD_GObj* gobj);
void ftMs_SpecialS_80137558(HSD_GObj* gobj);
void ftMs_SpecialS_801375B8(HSD_GObj* gobj);
void ftMs_SpecialS_80137618(HSD_GObj* gobj);
void ftMs_SpecialS_8013767C(HSD_GObj* gobj);
void ftMs_SpecialS_801376E8(HSD_GObj* gobj);
void ftMs_SpecialS_80137748(HSD_GObj* gobj);
void ftMs_SpecialS_801377B0(HSD_GObj* gobj);
void ftMs_SpecialS_80137810(HSD_GObj* gobj);
void ftMs_SpecialS_80137870(HSD_GObj* gobj);
void ftMs_SpecialS_801378D4(HSD_GObj* gobj);
void ftMs_SpecialS_80137940(HSD_GObj* gobj);
void ftMs_SpecialS_801379D0(HSD_GObj* gobj);
void ftMs_SpecialS_80137A68(HSD_GObj* gobj);
void ftMs_SpecialS_80137A9C(HSD_GObj* gobj);
void ftMs_SpecialS_80137B34(HSD_GObj* gobj);
void ftMs_SpecialS_80137B94(HSD_GObj* gobj);
void ftMs_SpecialS_80137BF4(HSD_GObj* gobj);
void ftMs_SpecialS_80137C50(HSD_GObj* gobj);
void ftMs_SpecialS_80137CBC(HSD_GObj* gobj);
void ftMs_SpecialS_80137D60(HSD_GObj* gobj);
void ftMs_SpecialS_80137E0C(HSD_GObj* gobj);
void ftMs_SpecialS_80137ECC(HSD_GObj* gobj);
void ftMs_SpecialS_80137F2C(HSD_GObj* gobj);
void ftMs_SpecialS_80137F30(HSD_GObj* gobj);
void ftMs_SpecialS_80137F8C(HSD_GObj* gobj);
void ftMs_SpecialS_80137FF8(HSD_GObj* gobj);
void ftMs_SpecialS_8013809C(HSD_GObj* gobj);
void ftMs_SpecialS_80138148(HSD_GObj* gobj);

void ftMs_SpecialHi_StartMotion(HSD_GObj* gobj);
void ftMs_SpecialAirHi_StartMotion(HSD_GObj* gobj);
void ftMs_SpecialHi_801382E8(HSD_GObj* gobj);
void ftMs_SpecialHi_80138348(HSD_GObj* gobj);
void ftMs_SpecialHi_801383A8(HSD_GObj* gobj);
void ftMs_SpecialHi_801384F0(HSD_GObj* gobj);
void ftMs_SpecialHi_80138638(HSD_GObj* gobj);
void ftMs_SpecialHi_8013873C(HSD_GObj* gobj);
void ftMs_SpecialHi_80138884(HSD_GObj* gobj);
void ftMs_SpecialHi_801388B4(HSD_GObj* gobj);
void ftMs_SpecialHi_80138940(HSD_GObj* gobj);

void ftMs_SpecialLw_StartMotion(HSD_GObj* gobj);
void ftMs_SpecialAirLw_StartMotion(HSD_GObj* gobj);
void ftMs_SpecialLw_80138AA8(HSD_GObj* gobj);
void ftMs_SpecialLw_80138B64(HSD_GObj* gobj);
void ftMs_SpecialLw_80138C20(HSD_GObj* gobj);
void ftMs_SpecialLw_80138C24(HSD_GObj* gobj);
void ftMs_SpecialLw_80138C28(HSD_GObj* gobj);
void ftMs_SpecialLw_80138C5C(HSD_GObj* gobj);
void ftMs_SpecialLw_80138CC0(HSD_GObj* gobj);
void ftMs_SpecialLw_80138CFC(HSD_GObj* gobj);
void ftMs_SpecialLw_80138D38(HSD_GObj* gobj);
void ftMs_SpecialLw_80138DD0(HSD_GObj* gobj);
void ftMs_SpecialLw_80138E68(HSD_GObj* gobj);
void ftMs_SpecialLw_80138F14(HSD_GObj* gobj);
void ftMs_SpecialLw_80138FC0(HSD_GObj* gobj);
void ftMs_SpecialLw_80138FC4(HSD_GObj* gobj);
void ftMs_SpecialLw_80138FC8(HSD_GObj* gobj);
void ftMs_SpecialLw_80138FE8(HSD_GObj* gobj);
void ftMs_SpecialLw_80139008(HSD_GObj* gobj);
void ftMs_SpecialLw_80139044(HSD_GObj* gobj);
void ftMs_SpecialLw_80139080(HSD_GObj* gobj);
void ftMs_SpecialLw_801390E0(HSD_GObj* gobj);
void ftMs_SpecialLw_80139140(HSD_GObj* gobj);
void ftMs_OnLoadForRoy(Fighter*);
void ftMs_Init_LoadSpecialAttrs(HSD_GObj*);

void ftMs_SpecialN_80136844(HSD_GObj*);
void ftMs_SpecialN_80136914(HSD_GObj*);
void ftMs_SpecialN_8013691C(HSD_GObj*);
void ftMs_SpecialN_801369A4(HSD_GObj*);
void ftMs_SpecialN_80136ADC(HSD_GObj*);
void ftMs_SpecialN_80136C8C(HSD_GObj*);
void ftMs_SpecialN_80136CFC(HSD_GObj*);
void ftMs_SpecialN_80136D3C(HSD_GObj*);
void ftMs_SpecialN_80136EE4(HSD_GObj*);
void ftMs_SpecialN_8013713C(HSD_GObj*);
void ftMs_SpecialN_80137144(HSD_GObj*);
void ftMs_SpecialN_80137184(HSD_GObj*);
void ftMs_SpecialN_80136EE4(HSD_GObj*);
void ftMs_SpecialN_8013713C(HSD_GObj*);
void ftMs_SpecialN_80137144(HSD_GObj*);
void ftMs_SpecialN_80137184(HSD_GObj*);
void ftMs_SpecialN_801368AC(HSD_GObj*);
void ftMs_SpecialN_80136918(HSD_GObj*);
void ftMs_SpecialN_8013695C(HSD_GObj*);
void ftMs_SpecialN_801369E0(HSD_GObj*);
void ftMs_SpecialN_80136BB4(HSD_GObj*);
void ftMs_SpecialN_80136CC4(HSD_GObj*);
void ftMs_SpecialN_80136D1C(HSD_GObj*);
void ftMs_SpecialN_80136D78(HSD_GObj*);
void ftMs_SpecialN_80137010(HSD_GObj*);
void ftMs_SpecialN_80137140(HSD_GObj*);
void ftMs_SpecialN_80137164(HSD_GObj*);
void ftMs_SpecialN_801371C0(HSD_GObj*);
void ftMs_SpecialN_80137010(HSD_GObj*);
void ftMs_SpecialN_80137140(HSD_GObj*);
void ftMs_SpecialN_80137164(HSD_GObj*);
void ftMs_SpecialN_801371C0(HSD_GObj*);
void ftMs_SpecialS_80137558(HSD_GObj*);
void ftMs_SpecialS_801375B8(HSD_GObj*);
void ftMs_SpecialS_80137618(HSD_GObj*);
void ftMs_SpecialS_8013767C(HSD_GObj*);
void ftMs_SpecialS_801377B0(HSD_GObj*);
void ftMs_SpecialS_80137810(HSD_GObj*);
void ftMs_SpecialS_80137870(HSD_GObj*);
void ftMs_SpecialS_801378D4(HSD_GObj*);
void ftMs_SpecialS_801377B0(HSD_GObj*);
void ftMs_SpecialS_80137810(HSD_GObj*);
void ftMs_SpecialS_80137870(HSD_GObj*);
void ftMs_SpecialS_801378D4(HSD_GObj*);
void ftMs_SpecialS_80137B34(HSD_GObj*);
void ftMs_SpecialS_80137B94(HSD_GObj*);
void ftMs_SpecialS_80137BF4(HSD_GObj*);
void ftMs_SpecialS_80137C50(HSD_GObj*);
void ftMs_SpecialS_80137B34(HSD_GObj*);
void ftMs_SpecialS_80137B94(HSD_GObj*);
void ftMs_SpecialS_80137BF4(HSD_GObj*);
void ftMs_SpecialS_80137C50(HSD_GObj*);
void ftMs_SpecialS_80137B34(HSD_GObj*);
void ftMs_SpecialS_80137B94(HSD_GObj*);
void ftMs_SpecialS_80137BF4(HSD_GObj*);
void ftMs_SpecialS_80137C50(HSD_GObj*);
void ftMs_SpecialS_80137ECC(HSD_GObj*);
void ftMs_SpecialS_80137F2C(HSD_GObj*);
void ftMs_SpecialS_80137F30(HSD_GObj*);
void ftMs_SpecialS_80137F8C(HSD_GObj*);
void ftMs_SpecialS_80137ECC(HSD_GObj*);
void ftMs_SpecialS_80137F2C(HSD_GObj*);
void ftMs_SpecialS_80137F30(HSD_GObj*);
void ftMs_SpecialS_80137F8C(HSD_GObj*);
void ftMs_SpecialS_80137ECC(HSD_GObj*);
void ftMs_SpecialS_80137F2C(HSD_GObj*);
void ftMs_SpecialS_80137F30(HSD_GObj*);
void ftMs_SpecialS_80137F8C(HSD_GObj*);
void ftMs_SpecialS_80137558(HSD_GObj*);
void ftMs_SpecialS_801375B8(HSD_GObj*);
void ftMs_SpecialS_80137618(HSD_GObj*);
void ftMs_SpecialS_8013767C(HSD_GObj*);
void ftMs_SpecialS_801377B0(HSD_GObj*);
void ftMs_SpecialS_80137810(HSD_GObj*);
void ftMs_SpecialS_80137870(HSD_GObj*);
void ftMs_SpecialS_801378D4(HSD_GObj*);
void ftMs_SpecialS_801377B0(HSD_GObj*);
void ftMs_SpecialS_80137810(HSD_GObj*);
void ftMs_SpecialS_80137870(HSD_GObj*);
void ftMs_SpecialS_801378D4(HSD_GObj*);
void ftMs_SpecialS_80137B34(HSD_GObj*);
void ftMs_SpecialS_80137B94(HSD_GObj*);
void ftMs_SpecialS_80137BF4(HSD_GObj*);
void ftMs_SpecialS_80137C50(HSD_GObj*);
void ftMs_SpecialS_80137B34(HSD_GObj*);
void ftMs_SpecialS_80137B94(HSD_GObj*);
void ftMs_SpecialS_80137BF4(HSD_GObj*);
void ftMs_SpecialS_80137C50(HSD_GObj*);
void ftMs_SpecialS_80137B34(HSD_GObj*);
void ftMs_SpecialS_80137B94(HSD_GObj*);
void ftMs_SpecialS_80137BF4(HSD_GObj*);
void ftMs_SpecialS_80137C50(HSD_GObj*);
void ftMs_SpecialS_80137ECC(HSD_GObj*);
void ftMs_SpecialS_80137F2C(HSD_GObj*);
void ftMs_SpecialS_80137F30(HSD_GObj*);
void ftMs_SpecialS_80137F8C(HSD_GObj*);
void ftMs_SpecialS_80137ECC(HSD_GObj*);
void ftMs_SpecialS_80137F2C(HSD_GObj*);
void ftMs_SpecialS_80137F30(HSD_GObj*);
void ftMs_SpecialS_80137F8C(HSD_GObj*);
void ftMs_SpecialS_80137ECC(HSD_GObj*);
void ftMs_SpecialS_80137F2C(HSD_GObj*);
void ftMs_SpecialS_80137F30(HSD_GObj*);
void ftMs_SpecialS_80137F8C(HSD_GObj*);
void ftMs_SpecialHi_801382E8(HSD_GObj*);
void ftMs_SpecialHi_801383A8(HSD_GObj*);
void ftMs_SpecialHi_80138638(HSD_GObj*);
void ftMs_SpecialHi_801388B4(HSD_GObj*);
void ftMs_SpecialHi_80138348(HSD_GObj*);
void ftMs_SpecialHi_801384F0(HSD_GObj*);
void ftMs_SpecialHi_8013873C(HSD_GObj*);
void ftMs_SpecialHi_80138940(HSD_GObj*);
void ftMs_SpecialLw_80138AA8(HSD_GObj*);
void ftMs_SpecialLw_80138C20(HSD_GObj*);
void ftMs_SpecialLw_80138C28(HSD_GObj*);
void ftMs_SpecialLw_80138CC0(HSD_GObj*);
void ftMs_SpecialLw_80138E68(HSD_GObj*);
void ftMs_SpecialLw_80138FC0(HSD_GObj*);
void ftMs_SpecialLw_80138FC8(HSD_GObj*);
void ftMs_SpecialLw_80139008(HSD_GObj*);
void ftMs_SpecialLw_80138B64(HSD_GObj*);
void ftMs_SpecialLw_80138C24(HSD_GObj*);
void ftMs_SpecialLw_80138C5C(HSD_GObj*);
void ftMs_SpecialLw_80138CFC(HSD_GObj*);
void ftMs_SpecialLw_80138F14(HSD_GObj*);
void ftMs_SpecialLw_80138FC4(HSD_GObj*);
void ftMs_SpecialLw_80138FE8(HSD_GObj*);
void ftMs_SpecialLw_80139044(HSD_GObj*);

#endif
