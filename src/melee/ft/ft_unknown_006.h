/** @file
 * @todo Rename to @c ftUnk6.h
 */
#ifndef MELEE_FT_FT_UNKNOWN_006_H
#define MELEE_FT_FT_UNKNOWN_006_H

#include <melee/ft/fighter.h>
#include <sysdolphin/baselib/gobjproc.h>

/// @remarks Only used by Purin.
extern HSD_Joint* lbl_8045A1E0[6];

s32 func_800877F8(HSD_GObj* fighter_gobj, s32 arg1);
s32 func_80087818(HSD_GObj* fighter_gobj, s32 arg1);
s32 func_80087838(HSD_GObj* fighter_gobj);
s32 func_80087858(HSD_GObj* fighter_gobj);
s32 func_80087878(HSD_GObj* fighter_gobj, s32 arg1);
s32 func_800878BC(HSD_GObj* fighter_gobj);
s32 func_80087900(HSD_GObj* fighter_gobj);
s32 func_80087944(HSD_GObj* fighter_gobj);
s32 func_80087988(HSD_GObj* fighter_gobj);
s32 func_800879D8(HSD_GObj* fighter_gobj);
s32 func_800879F8(HSD_GObj* fighter_gobj);
s32 func_80087A18(HSD_GObj* fighter_gobj);
u8 func_80087A80(HSD_GObj* fighter_gobj);
f32 func_80087A8C(HSD_GObj* fighter_gobj);
s32 func_80087A98(HSD_GObj* fighter_gobj);
u8 func_80087AA4(HSD_GObj* fighter_gobj);
u8 func_80087AB4(HSD_GObj* fighter_gobj);
void func_80087AC0(HSD_GObj* fighter_gobj, s32 arg1);
s32 func_80087AEC(HSD_GObj* fighter_gobj);
s32 func_80087B34(HSD_GObj* fighter_gobj);
void func_80087BAC(HSD_GObj* fighter_gobj, s32 arg1);
void func_80087BC0(HSD_GObj* fighter_gobj, s8 arg1);
void func_80087BEC(HSD_GObj* fighter_gobj, u8 arg1);
s32 func_80087C1C(void);
s32 func_80087C58(HSD_GObj* fighter_gobj);
void func_80087C64(HSD_GObj* fighter_gobj, s32 arg1);
s32 func_80087C70(Fighter* fp, s32 arg1);
s32 func_80087D0C(Fighter* fighter, s32 arg1);
void func_8008805C(Fighter* arg0, s32 arg1);
void func_80088080(Fighter* fp);
void func_800880AC(Fighter* fp);
void func_800880D8(Fighter* fp);
void func_80088110(Fighter* fp);
void func_800D5BF8(HSD_GObj* fighter_gobj);
unk_t func_800D0EC8(void);
unk_t func_8009A3C8(void);
unk_t func_8004B4B0(void);
unk_t func_8009EDA4(void);
unk_t func_8009F39C(void);
unk_t func_800C703C(void);

void func_80088148(Fighter*, u32, u32, u32);
void func_800881D8(Fighter*, u32, u32, u32);
void func_80088640(Fighter*, bool, bool, bool);
void func_800887CC(Fighter*);
void func_80088884(Fighter*);
void func_800888E0(Fighter*);
void func_80088A50(Fighter*);
void func_80088C5C(HSD_GObj*);
void func_800890BC(Fighter*);
void func_800890D0(Fighter*, u8);
void func_800892A0(HSD_GObj*);
void func_800892D4(Fighter*);
void func_800895E0(Fighter*, s32);
void func_80089824(HSD_GObj*);
void func_80089B08(HSD_GObj* pPlayerEntityStruct);
void func_8008A2BC(HSD_GObj* gobj);
f32 func_8008D7F0(Fighter*);
f32 scaleBy154_8008D8D8(f32);
s32 func_8008D8E8(f32);
void func_8008D930(Fighter*);
void func_8008DCE0(HSD_GObj*, s32, f32);
void func_8008E908(HSD_GObj*, f32);
s32 func_8008E984(Fighter*);
void func_8008E9D0(HSD_GObj*);
void func_8008EB58(HSD_GObj*);
void func_8008EC90(HSD_GObj*);
void func_80090594(Fighter*, s32, bool, s32, s32, float);
u32 func_80090690(Fighter*, struct _Vec2*);
void func_80090718(Fighter*);
f32 func_80092ED8(s32, void*, f32);
s32 func_80093694(void);
s32 func_8009515C(HSD_GObj*);
void func_80095744(HSD_GObj*, bool);
s32 func_800964FC(Fighter*);
void func_800968C8(HSD_GObj*);
void func_80096900(HSD_GObj*, s32, s32, s32, f32, f32);
void func_8009750C(HSD_GObj*);
void func_80098B20(HSD_GObj*);
void func_80098C9C(HSD_GObj*);
void func_80099D9C(HSD_GObj*);
bool func_8009A080(HSD_GObj*);
void func_8009A804(HSD_GObj*);
void func_8009CF84(Fighter*);
void func_8009E0A8(HSD_GObj*);
void func_8009E0D4(Fighter*);
void func_8009E7B4(Fighter*, u8*);
s32 func_8009EF68(HSD_GObj*);
void func_8009F4A4(void);
void func_8009F578(Fighter*);
void func_800A0DA4(Fighter*);
void func_800A101C(Fighter*, s8, s8, s32);
f32 func_800A17E4(Fighter*);
f32 func_800A1874(Fighter*);
f32 func_800A1904(Fighter*);
f32 func_800A1948(Fighter*);
s32 func_800A198C(Fighter*);
f32 func_800A1994(Fighter*);
f32 func_800A1A24(Fighter*);
bool func_800A2040(Fighter*);
void func_800B3900(HSD_GObj*);
void func_800BFD04(HSD_GObj*);
void func_800BFFAC(Fighter*);
void func_800BFFD0(Fighter*, s32, s32);
void func_800C0074(Fighter*);
void func_800C0134(Fighter*);
void func_800C0200(Fighter*, s32);
void func_800C0408(HSD_GObj*);
bool func_800C0694(Fighter*);
void func_800C09B4(HSD_GObj*);
void func_800C0A98(HSD_GObj* fighter_gobj);

/// @todo UnclePunch Map file: AS_203_PassiveWalljump_Walljump
void func_800C1E64(HSD_GObj* pPlayerEntityStruct, s32, s32, u8, f32);

void func_800C2FD8(HSD_GObj*);
void func_800C37A0(HSD_GObj*);
void func_800C511C(HSD_GObj*);
void func_800C61B0(HSD_GObj*);
void func_800C8064(void);
void func_800C8348(HSD_GObj*, s32, s32);
void func_800C8438(HSD_GObj*);
void func_800C8540(HSD_GObj*);
void func_800C884C(HSD_GObj*);
void func_800C88A0(Fighter*);
void func_800C89A0(HSD_GObj*);
void func_800C8A64(HSD_GObj*);
bool func_800C8B2C(Fighter*, bool, bool);
void func_800C8C84(HSD_GObj*);
void func_800C8D00(HSD_GObj*);
void func_800C8F6C(void);
void func_800C8FC4(HSD_GObj*);
void func_800C9034(HSD_GObj*);
void func_800C9840(HSD_GObj*, s32, s32, f32, f32, f32);
s32 func_800CAE80(HSD_GObj*);
void func_800CB110(HSD_GObj*, s32, f32);
void func_800CC730(HSD_GObj*);
void func_800D0FA0(HSD_GObj*);
void func_800D105C(HSD_GObj*);
void func_800D14E4(HSD_GObj*);
void func_800D1A8C(HSD_GObj*);
void func_800D1E80(HSD_GObj*);
void func_800D237C(HSD_GObj*);
void func_800D3158(HSD_GObj* fighter_gobj);
void func_800D4F24(HSD_GObj*, s32);
void func_800D5AEC(HSD_GObj*, s32, s32, s32, Fighter*, f32, f32);
void func_800D5CB0(HSD_GObj*, s32, f32);
s32 func_800D67C4(Fighter*);
s32 func_800D688C(Fighter*);
s32 func_800D6928(Fighter*);
void func_800D71D8(HSD_GObj*);
void func_800D94D8(HSD_GObj*);
f32 func_800DA824(Fighter*);
void func_800DB368(Fighter*, Fighter*);
void func_800DB464(HSD_GObj*);
void func_800DC750(HSD_GObj*);
void func_800DD168(HSD_GObj*);
void func_800DE2A8(HSD_GObj*, HSD_GObj*);
void func_800DE508(HSD_GObj*);
void func_800DE7C0(HSD_GObj*, s32, s32);
void func_800DEEA8(HSD_GObj* fighter_gobj);
u32 func_800DEEE8(Fighter*, struct _Vec2*);
void func_800DEF38(HSD_GObj*);
void func_800DF0D0(HSD_GObj*);
bool func_80096CC8(HSD_GObj*);

/// @todo enum params
void func_800DEAE8(HSD_GObj* gobj, enum_t asid0, enum_t asid1);

void func_800DED30(HSD_GObj*);
bool func_8008A1FC(HSD_GObj*);
bool func_80094EA4(HSD_GObj*);
bool func_800C97A8(HSD_GObj* fighter_gobj);
void func_800C9924(HSD_GObj*);
void func_800CB438(HSD_GObj* fighter_gobj);
void func_800CB59C(HSD_GObj* fighter_gobj);
void func_8008F744(HSD_GObj* fighter_gobj);
void func_8008FB18(HSD_GObj* fighter_gobj);
bool func_8009917C(HSD_GObj*);
void func_8008A324(HSD_GObj*);
bool func_8009A134(HSD_GObj*);
bool func_80099F1C(HSD_GObj*);
void func_8009A184(HSD_GObj*, s32, u32, f32);
bool func_800CAED0(HSD_GObj*);
bool func_800CB870(HSD_GObj*);
void func_800BFB4C(HSD_GObj* fighter_gobj, s32*);
void func_800D6B00(HSD_GObj*, s32);
bool func_80094790(HSD_GObj*);
void func_8008ACD8(HSD_GObj*);
void func_800D5F38(HSD_GObj*);
void func_800D5F18(HSD_GObj*);
void func_800D5D3C(HSD_GObj*);
void func_8008D708(HSD_GObj*, s32, f32);
void func_8008D3A4(HSD_GObj*);
void func_8008D29C(HSD_GObj*);

/// Interrupt_Wait
void func_8008A4D4(HSD_GObj*);

void func_80088510(Fighter*, s32, u8, u8);
void func_800BC7E0(HSD_GObj*, HSD_GObj*);
void func_800BC8D4(HSD_GObj*, HSD_GObj*);
void func_800DE7C0(HSD_GObj*, s32, s32);
void func_800DE2A8(HSD_GObj*, HSD_GObj*);
void func_800DC920(HSD_GObj*, HSD_GObj*);
void func_800BCE64(HSD_GObj*, s32 asid);
void func_800BC9C8(HSD_GObj*);
void func_800CCAAC(HSD_GObj*);
void func_8008A2BC(HSD_GObj*);
void func_800BCF18(HSD_GObj*, HSD_GObj*);
void func_800BD000(HSD_GObj*, HSD_GObj*);
void func_80090780(HSD_GObj*);
void func_80097D40(HSD_GObj*);
void func_800969D8(HSD_GObj*, s32, s32, s32, f32, f32, f32);
void func_80088478(Fighter*, s32, s32, s32);
void func_8009DC54(Fighter*);
unk_t func_80091D58(void);
unk_t func_80092450(void);
void func_80092BCC(HSD_GObj* fighter_gobj);
bool func_80099794(HSD_GObj*);
bool func_800D8990(HSD_GObj*);
bool func_800925A4(HSD_GObj* fighter_gobj);
void func_800928CC(HSD_GObj* fighter_gobj);
void func_80092870(void);
void func_800928AC(void);
void func_80094818(HSD_GObj* fighter_gobj, bool);
void func_800D6C60(HSD_GObj*, HSD_GObjEvent callback);
void func_800D6E70(HSD_GObj* fighter_gobj);
void func_800D6E34(HSD_GObj* fighter_gobj);
s32 func_8008CE68(Fighter*);
void func_8008CFAC(HSD_GObj*, s32);
void func_800D638C(HSD_GObj*);
bool func_8008A9F8(HSD_GObj*);
bool func_8008B658(HSD_GObj*);
bool func_8008B980(HSD_GObj*);
bool func_8008BB44(HSD_GObj*);
bool func_8008BFC4(HSD_GObj*);
bool func_8008C830(HSD_GObj*);
bool func_8008CB44(HSD_GObj*);
bool func_800C9468(HSD_GObj*);
bool func_800C97DC(HSD_GObj*);
bool func_800CA094(HSD_GObj*);
bool func_800CAED0(HSD_GObj*);
bool func_800D5F58(HSD_GObj*);
bool func_8008A9F8(HSD_GObj*);
bool func_8008B658(HSD_GObj*);
bool func_8008B980(HSD_GObj*);
bool func_8008BB44(HSD_GObj*);
bool func_8008BFC4(HSD_GObj*);
bool func_8008C830(HSD_GObj*);
bool func_8008CB44(HSD_GObj*);
bool func_80096540(HSD_GObj*);
void func_800D638C(HSD_GObj*);
bool func_800D6824(HSD_GObj*);
bool func_800D68C0(HSD_GObj*);
bool func_800D695C(HSD_GObj*);
bool func_8007B868(HSD_GObj*);
void func_8008D010(HSD_GObj*);
void func_8008D08C(HSD_GObj*);
void func_800D9C98(HSD_GObj* fighter_gobj);
void func_80088770(Fighter*);
bool func_800C5240(HSD_GObj*);
void func_800C5500(HSD_GObj*);
void func_800C0358(Fighter*, Fighter*, s32);
void func_800C88D4(HSD_GObj*, s32, bool);
void func_800C06C0(void);
HSD_GObj* func_800BE7E0(unk_t);
void func_800D4FF4(HSD_GObj*);
void func_SetEntityFacingDirection(HSD_GObj*, f32 facing_dir);
void func_800BEB60(int, int, int);
void func_8009B5C4(HSD_GObj*);
void func_8009B5C0(HSD_GObj*);
void func_8009B744(HSD_GObj*);
void func_8009B634(HSD_GObj*);
void func_8009B654(HSD_GObj*);
void func_8009B7F8(HSD_GObj*);
void func_8009B7D8(HSD_GObj*);
void func_8009B988(HSD_GObj*);
void func_8009B9A8(HSD_GObj*);
void func_8009B8B4(HSD_GObj*);
void func_8009BA50(HSD_GObj*);
void func_8009BBF0(HSD_GObj*);
void func_8009BCDC(HSD_GObj*);
void func_8009B764(HSD_GObj*);
void func_8009B948(HSD_GObj*);
void func_8009BAA0(HSD_GObj*);
void func_8009BCE0(HSD_GObj*);
void func_8009BBF4(HSD_GObj*);
void func_8009BDC4(HSD_GObj*);
void func_8009BE14(HSD_GObj*);
void func_8009BEB8(HSD_GObj*);
void func_8009BE54(HSD_GObj*);
void func_8009C0EC(HSD_GObj*);
void func_8009C130(HSD_GObj*);
void func_8009BAFC(HSD_GObj*);
void func_8009BD24(HSD_GObj*);
void func_8009BC38(HSD_GObj*);
void func_8009BC18(HSD_GObj*);
void func_8009BADC(HSD_GObj*);
void func_8009BD04(HSD_GObj*);
void func_8009BE34(HSD_GObj*);
void func_8009BED8(HSD_GObj*);
void func_8009C20C(HSD_GObj*);
void func_8009C150(HSD_GObj*);
void func_8009C274(HSD_GObj*);
void func_8009C294(HSD_GObj*);
void func_8009C234(HSD_GObj*);
void func_8009C2BC(HSD_GObj*);
void func_8009C2FC(HSD_GObj*);
void func_8009C31C(HSD_GObj*);
void func_8009C344(HSD_GObj*);
void func_8009C254(HSD_GObj*);
void func_8009C2DC(HSD_GObj*);
void func_8009C364(HSD_GObj*);
void func_8009C3A4(HSD_GObj*);
void func_8009C384(HSD_GObj*);
void func_8009C3CC(HSD_GObj*);
void func_8009C414(HSD_GObj*);
void func_8009C434(HSD_GObj*);
void func_8009C410(HSD_GObj*);
void func_800CD390(HSD_GObj*);
void func_800CD3D0(HSD_GObj*);
void func_800CD3F0(HSD_GObj*);
void func_800CD3B0(HSD_GObj*);
void func_800CD458(HSD_GObj*);
void func_800CD478(HSD_GObj*);
void func_800CD498(HSD_GObj*);
void func_800CD4B8(HSD_GObj*);
void func_800CD580(HSD_GObj*);
void func_800CD560(HSD_GObj*);
void func_800CD520(HSD_GObj*);
void func_800CD540(HSD_GObj*);
void func_800CD7C4(HSD_GObj*);
void func_800CD6A0(HSD_GObj*);
void func_800CD88C(HSD_GObj*);
void func_800CDB14(HSD_GObj*);
void func_800CD804(HSD_GObj*);
void func_800CD7E4(HSD_GObj*);
void func_800CD8AC(HSD_GObj*);
void func_800CD8CC(HSD_GObj*);
void func_800CD8EC(HSD_GObj*);
void func_800CDB34(HSD_GObj*);
void func_800CDB54(HSD_GObj*);
void func_800CDB74(HSD_GObj*);
void func_800CEDE0(HSD_GObj*);
void func_800CEE30(HSD_GObj*);
void func_800CEE50(HSD_GObj*);
void func_800CEE00(HSD_GObj*);
void func_800C3D6C(HSD_GObj*);
void func_800C4384(HSD_GObj*);
void func_800C438C(HSD_GObj*);
void func_800C447C(HSD_GObj*);
void func_800C4380(HSD_GObj*);
void func_800C4388(HSD_GObj*);
void func_800C4438(HSD_GObj*);
void func_800D7590(HSD_GObj*);
void func_800D7614(HSD_GObj*);
void func_800D7634(HSD_GObj*);
void func_800D767C(HSD_GObj*);

#endif
