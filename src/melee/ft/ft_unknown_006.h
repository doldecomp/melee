/** @file
 * @todo Rename to @c ftUnk6.h
 */
#ifndef MELEE_FT_FT_UNKNOWN_006_H
#define MELEE_FT_FT_UNKNOWN_006_H

#include "ft/fighter.h"
#include "ft/forward.h"

#include <baselib/gobjproc.h>

/// @remarks Only used by Purin.
extern HSD_Joint* lbl_8045A1E0[6];

extern s32 lbl_80459B88[FTKIND_MAX];

extern char lbl_803C57D0[];
extern char lbl_803C57DC[];
extern Fighter_CostumeStrings ftMario_CostumeStrings[];
extern char lbl_803C595C[];

bool func_8007B868(HSD_GObj*);
bool func_8008A1FC(HSD_GObj*);
bool func_8008A9F8(HSD_GObj*);
bool func_8008B658(HSD_GObj*);
bool func_8008B980(HSD_GObj*);
bool func_8008BB44(HSD_GObj*);
bool func_8008BFC4(HSD_GObj*);
bool func_8008C830(HSD_GObj*);
bool func_8008CB44(HSD_GObj*);
bool func_800925A4(HSD_GObj* gobj);
bool func_800925A4(HSD_GObj*);
bool func_80094790(HSD_GObj*);
bool func_80094EA4(HSD_GObj*);
bool func_80096540(HSD_GObj*);
bool func_80096CC8(HSD_GObj*);
bool func_8009917C(HSD_GObj*);
bool func_80099794(HSD_GObj*);
bool func_80099F1C(HSD_GObj*);
bool func_8009A080(HSD_GObj*);
bool func_8009A134(HSD_GObj*);
bool func_800A2040(Fighter*);
bool func_800C0694(Fighter*);
bool func_800C5240(HSD_GObj*);
bool func_800C8B2C(Fighter*, bool, bool);
bool func_800C9468(HSD_GObj*);
bool func_800C97A8(HSD_GObj*);
bool func_800C97DC(HSD_GObj*);
bool func_800CA094(HSD_GObj*);
bool func_800CAED0(HSD_GObj*);
bool func_800CB870(HSD_GObj*);
bool func_800D5F58(HSD_GObj*);
bool func_800D6824(HSD_GObj*);
bool func_800D68C0(HSD_GObj*);
bool func_800D695C(HSD_GObj*);
bool func_800D8990(HSD_GObj*);
f32 func_80087A8C(HSD_GObj*);
f32 func_8008D7F0(Fighter*);
f32 func_80092ED8(s32, void*, f32);
f32 func_800A17E4(Fighter*);
f32 func_800A1874(Fighter*);
f32 func_800A1904(Fighter*);
f32 func_800A1948(Fighter*);
f32 func_800A1994(Fighter*);
f32 func_800A1A24(Fighter*);
f32 func_800DA824(Fighter*);
f32 scaleBy154_8008D8D8(f32);
HSD_GObj* func_800BE7E0(unk_t);
s32 func_800877F8(HSD_GObj*, s32);
s32 func_80087818(HSD_GObj*, s32);
s32 func_80087838(HSD_GObj*);
s32 func_80087858(HSD_GObj*);
s32 func_80087878(HSD_GObj*, s32);
s32 func_800878BC(HSD_GObj*);
s32 func_80087900(HSD_GObj*);
s32 func_80087944(HSD_GObj*);
s32 func_80087988(HSD_GObj*);
s32 func_800879D8(HSD_GObj*);
s32 func_800879F8(HSD_GObj*);
s32 func_80087A18(HSD_GObj*);
s32 func_80087A98(HSD_GObj*);
s32 func_80087AEC(HSD_GObj*);
s32 func_80087B34(HSD_GObj*);
s32 func_80087C1C(void);
s32 func_80087C58(HSD_GObj*);
s32 func_80087C70(Fighter*, s32);
s32 func_80087D0C(Fighter*, s32);
s32 func_8008CE68(Fighter*);
s32 func_8008D8E8(f32);
s32 func_8008E984(Fighter*);
s32 func_80093694(void);
s32 func_8009515C(HSD_GObj*);
s32 func_800964FC(Fighter*);
bool func_8009EF68(HSD_GObj*);
s32 func_800A198C(Fighter*);
s32 func_800CAE80(HSD_GObj*);
s32 func_800D67C4(Fighter*);
s32 func_800D688C(Fighter*);
s32 func_800D6928(Fighter*);
u32 func_80090690(Fighter*, Vec2*);
u32 func_800DEEE8(Fighter*, Vec2*);
u8 func_80087A80(HSD_GObj*);
u8 func_80087AA4(HSD_GObj*);
u8 func_80087AB4(HSD_GObj*);
unk_t func_8004B4B0(void);
unk_t func_80091D58(void);
unk_t func_80092450(void);
unk_t func_8009A3C8(void);
unk_t func_8009EDA4(void);
unk_t func_8009F39C(void);
unk_t func_800C703C(void);
unk_t func_800D0EC8(void);
void func_80081504(HSD_GObj*);
void func_80081540(HSD_GObj*);
void func_80081544(HSD_GObj*);
void func_800815E4(HSD_GObj*);
void func_80081644(HSD_GObj*);
void func_80087AC0(HSD_GObj*, s32);
void func_80087BAC(HSD_GObj*, s32);
void func_80087BC0(HSD_GObj*, s8);
void func_80087BEC(HSD_GObj*, u8);
void func_80087C64(HSD_GObj*, s32);
void func_8008805C(Fighter*, s32);
void func_80088080(Fighter*);
void func_800880AC(Fighter*);
void func_800880D8(Fighter*);
void func_80088110(Fighter*);

// SFX_PlayCharacterSFX
void func_80088148(Fighter*, enum_t, int, int);

void func_800881D8(Fighter*, u32, u32, u32);
void func_80088478(Fighter*, s32, s32, s32);
void func_80088510(Fighter*, s32, u8, u8);
void func_80088640(Fighter*, bool, bool, bool);
void func_80088770(Fighter*);
void func_800887CC(Fighter*);
void func_80088884(Fighter*);
void func_800888E0(Fighter*);
void func_80088A50(Fighter*);
void func_80088C5C(HSD_GObj*);
void func_800890BC(Fighter*);
void func_800890D0(Fighter*, u8);
void func_80089228(void);
void func_800892A0(HSD_GObj*);
void func_800892D4(Fighter*);
void func_800895E0(Fighter*, s32);
void func_80089824(HSD_GObj*);
void func_80089B08(HSD_GObj*);
void func_8008A2BC(HSD_GObj*);
void func_8008A324(HSD_GObj*);
void func_8008A494(HSD_GObj*);
void func_8008A4D4(HSD_GObj*);
void func_8008A644(HSD_GObj*);
void func_8008A678(HSD_GObj*);
void func_8008AC9C(HSD_GObj*);
void func_8008ACD8(HSD_GObj*);
void func_8008ADF0(HSD_GObj*);
void func_8008AE10(HSD_GObj*);
void func_8008B040(HSD_GObj*);
void func_8008B07C(HSD_GObj*);
void func_8008B354(HSD_GObj*);
void func_8008B390(HSD_GObj*);
void func_8008B548(HSD_GObj*);
void func_8008B5AC(HSD_GObj*);
void func_8008B600(HSD_GObj*);
void func_8008B638(HSD_GObj*);
void func_8008B8D4(HSD_GObj*);
void func_8008B910(HSD_GObj*);
void func_8008B940(HSD_GObj*);
void func_8008B960(HSD_GObj*);
void func_8008BA98(HSD_GObj*);
void func_8008BAD4(HSD_GObj*);
void func_8008BB04(HSD_GObj*);
void func_8008BB24(HSD_GObj*);
void func_8008BCFC(HSD_GObj*);
void func_8008BD80(HSD_GObj*);
void func_8008BF84(HSD_GObj*);
void func_8008BFA4(HSD_GObj*);
void func_8008C520(HSD_GObj*);
void func_8008C55C(HSD_GObj*);
void func_8008C7F0(HSD_GObj*);
void func_8008C810(HSD_GObj*);
void func_8008CA98(HSD_GObj*);
void func_8008CAD4(HSD_GObj*);
void func_8008CB04(HSD_GObj*);
void func_8008CB24(HSD_GObj*);
void func_8008CCBC(HSD_GObj*);
void func_8008CCF8(HSD_GObj*);
void func_8008CD28(HSD_GObj*);
void func_8008CD48(HSD_GObj*);
void func_8008CFAC(HSD_GObj*, s32);
void func_8008D010(HSD_GObj*);
void func_8008D08C(HSD_GObj*);
void func_8008D194(HSD_GObj*);
void func_8008D29C(HSD_GObj*);
void func_8008D3A4(HSD_GObj*);
void func_8008D4AC(HSD_GObj*);
void func_8008D5B4(HSD_GObj*);
void func_8008D5D4(HSD_GObj*);
void func_8008D708(HSD_GObj*, s32, f32);
void func_8008D78C(HSD_GObj*);
void func_8008D7AC(HSD_GObj*);
void func_8008D7B0(HSD_GObj*);
void func_8008D7D0(HSD_GObj*);
void func_8008D930(Fighter*);
void func_8008DCE0(HSD_GObj*, s32, f32);
void func_8008E908(HSD_GObj*, f32);
void func_8008E9D0(HSD_GObj*);
void func_8008EB58(HSD_GObj*);
void func_8008EC90(HSD_GObj*);
void func_8008F744(HSD_GObj*);
void func_8008F7F0(HSD_GObj*);
void func_8008FA44(HSD_GObj*);
void func_8008FB18(HSD_GObj*);
void func_8008FB64(HSD_GObj*);
void func_8008FD98(HSD_GObj*);
void func_8008FF48(HSD_GObj*);
void func_8008FF84(HSD_GObj*);
void func_800900EC(HSD_GObj*);
void func_800901D0(HSD_GObj*);
void func_80090324(HSD_GObj*);
void func_8009035C(HSD_GObj*);
void func_800904C0(HSD_GObj*);
void func_80090594(Fighter*, s32, bool, s32, s32, float);
void func_80090718(Fighter*);
void func_80090780(HSD_GObj*);
void func_80090824(HSD_GObj*);
void func_80090828(HSD_GObj*);
void func_8009093C(HSD_GObj*);
void func_8009095C(HSD_GObj*);
void func_800912A8(HSD_GObj*);
void func_800913DC(HSD_GObj*);
void func_800913E0(HSD_GObj*);
void func_8009144C(HSD_GObj*);
void func_80091988(HSD_GObj*);
void func_800919D8(HSD_GObj*);
void func_800919DC(HSD_GObj*);
void func_800919FC(HSD_GObj*);
void func_800926DC(HSD_GObj*);
void func_80092758(HSD_GObj*);
void func_80092870(HSD_GObj*);
void func_800928AC(HSD_GObj*);
void func_800928CC(HSD_GObj* gobj);
void func_800928CC(HSD_GObj*);
void func_80092A24(HSD_GObj*);
void func_80092A78(HSD_GObj*);
void func_80092B70(HSD_GObj*);
void func_80092BAC(HSD_GObj*);
void func_80092BCC(HSD_GObj* gobj);
void func_80092BCC(HSD_GObj*);
void func_80092BE8(HSD_GObj*);
void func_80092CAC(HSD_GObj*);
void func_80092CFC(HSD_GObj*);
void func_80092E10(HSD_GObj*);
void func_80092E30(HSD_GObj*);
void func_80093240(HSD_GObj*);
void func_800932DC(HSD_GObj*);
void func_80093354(HSD_GObj*);
void func_80093624(HSD_GObj*);
void func_80093628(HSD_GObj*);
void func_8009365C(HSD_GObj*);
void func_8009370C(HSD_GObj*, HSD_GObjEvent, struct _ftCommonData*);
void func_80093BC0(HSD_GObj*);
void func_80093CD0(HSD_GObj*);
void func_80093EC0(HSD_GObj*);
void func_8009403C(HSD_GObj*);
void func_80094078(HSD_GObj*);
void func_80094138(void);
void func_80094818(HSD_GObj* gobj, bool);
void func_80094818(HSD_GObj*, bool);
void func_80094A14(HSD_GObj*);
void func_80094B20(HSD_GObj*);
void func_80094B24(HSD_GObj*);
void func_80094B44(HSD_GObj*);
void func_80095744(HSD_GObj*, bool);
void func_80095E80(HSD_GObj*);
void func_80096120(HSD_GObj*);
void func_80096124(HSD_GObj*);
void func_80096144(HSD_GObj*);
void func_800961B0(HSD_GObj*);
void func_80096208(HSD_GObj*);
void func_80096228(HSD_GObj*);
void func_8009634C(HSD_GObj*);
void func_80096470(HSD_GObj*);
void func_800968C8(HSD_GObj*);
void func_80096900(HSD_GObj*, s32, s32, bool is_interruptable, f32, f32);
void func_800969D8(HSD_GObj*, s32, s32, s32, f32, f32, f32);
void func_80096AA0(HSD_GObj*);
void func_80096AF4(HSD_GObj*);
void func_80096B44(HSD_GObj*);
void func_80096C98(HSD_GObj*);
void func_80096DF4(HSD_GObj*);
void func_80096DF8(HSD_GObj*);
void func_80096E48(HSD_GObj*);
void func_80096ED0(HSD_GObj*);
void func_80096FD0(HSD_GObj*);
void func_80097074(HSD_GObj*);
void func_80097098(HSD_GObj*);
void func_800970B8(HSD_GObj*);
void func_800971B0(HSD_GObj*);
void func_80097458(HSD_GObj*);
void func_8009747C(HSD_GObj*);
void func_8009749C(HSD_GObj*);
void func_8009750C(HSD_GObj*);
void func_80097D40(HSD_GObj*);
void func_80097DC0(HSD_GObj*);
void func_80097E1C(HSD_GObj*);
void func_80097E20(HSD_GObj*);
void func_80097E40(HSD_GObj*);
void func_80097FC0(HSD_GObj*);
void func_8009802C(HSD_GObj*);
void func_8009807C(HSD_GObj*);
void func_8009809C(HSD_GObj*);
void func_80098194(HSD_GObj*);
void func_800981D0(HSD_GObj*);
void func_800981D4(HSD_GObj*);
void func_800981F4(HSD_GObj*);
void func_80098380(HSD_GObj*);
void func_800983BC(HSD_GObj*);
void func_800983C0(HSD_GObj*);
void func_800983E0(HSD_GObj*);
void func_800985B4(HSD_GObj*);
void func_800985F0(HSD_GObj*);
void func_800985F4(HSD_GObj*);
void func_80098614(HSD_GObj*);
void func_800988A8(HSD_GObj*);
void func_800988E4(HSD_GObj*);
void func_800988E8(HSD_GObj*);
void func_80098908(HSD_GObj*);
void func_80098AA0(HSD_GObj*);
void func_80098ADC(HSD_GObj*);
void func_80098AE0(HSD_GObj*);
void func_80098B00(HSD_GObj*);
void func_80098B20(HSD_GObj*);
void func_80098C14(HSD_GObj*);
void func_80098C50(HSD_GObj*);
void func_80098C54(HSD_GObj*);
void func_80098C74(HSD_GObj*);
void func_80098C9C(HSD_GObj*);
void func_80098DEC(HSD_GObj*);
void func_80098DF0(HSD_GObj*);
void func_80098DF4(HSD_GObj*);
void func_80098E14(HSD_GObj*);
void func_80098EBC(HSD_GObj*);
void func_80098EF8(HSD_GObj*);
void func_80098EFC(HSD_GObj*);
void func_80098F1C(HSD_GObj*);
void func_80098F90(HSD_GObj*);
void func_80098FCC(HSD_GObj*);
void func_80098FD0(HSD_GObj*);
void func_80098FF0(HSD_GObj*);
void func_800990B8(HSD_GObj*);
void func_80099138(HSD_GObj*);
void func_8009913C(HSD_GObj*);
void func_8009915C(HSD_GObj*);
void func_800994D8(HSD_GObj*);
void func_800996F0(HSD_GObj*);
void func_80099714(HSD_GObj*);
void func_80099734(HSD_GObj*);
void func_800999D8(HSD_GObj*);
void func_80099A14(HSD_GObj*);
void func_80099A18(HSD_GObj*);
void func_80099A38(HSD_GObj*);
void func_80099BD0(HSD_GObj*);
void func_80099C24(HSD_GObj*);
void func_80099CEC(HSD_GObj*);
void func_80099D48(HSD_GObj*);
void func_80099D9C(HSD_GObj*);
void func_80099E24(HSD_GObj*);
void func_80099E80(HSD_GObj*);
void func_80099EBC(HSD_GObj*);
void func_80099EC0(HSD_GObj*);
void func_80099EFC(HSD_GObj*);
void func_8009A184(HSD_GObj*, s32, u32, f32);
void func_8009A2A8(HSD_GObj*);
void func_8009A2E4(HSD_GObj*);
void func_8009A388(HSD_GObj*);
void func_8009A3A8(HSD_GObj*);
void func_8009A468(HSD_GObj*);
void func_8009A4A4(HSD_GObj*);
void func_8009A5F4(HSD_GObj*);
void func_8009A5F8(HSD_GObj*);
void func_8009A728(HSD_GObj*);
void func_8009A72C(HSD_GObj*);
void func_8009A74C(HSD_GObj*);
void func_8009A750(HSD_GObj*);
void func_8009A804(HSD_GObj*);
void func_8009A8D8(HSD_GObj*);
void func_8009A8FC(HSD_GObj*);
void func_8009A96C(HSD_GObj*);
void func_8009A98C(HSD_GObj*);
void func_8009AC68(HSD_GObj*);
void func_8009ACA4(HSD_GObj*);
void func_8009ACA8(HSD_GObj*);
void func_8009ADA4(HSD_GObj*);
void func_8009AF70(HSD_GObj*);
void func_8009AF90(HSD_GObj*);
void func_8009AF94(HSD_GObj*);
void func_8009AFB4(HSD_GObj*);
void func_8009B10C(HSD_GObj*);
void func_8009B12C(HSD_GObj*);
void func_8009B130(HSD_GObj*);
void func_8009B150(HSD_GObj*);
void func_8009B278(HSD_GObj*);
void func_8009B2B4(HSD_GObj*);
void func_8009B2B8(HSD_GObj*);
void func_8009B2D8(HSD_GObj*);
void func_8009B424(HSD_GObj*);
void func_8009B460(HSD_GObj*);
void func_8009B464(HSD_GObj*);
void func_8009B4A0(HSD_GObj*);
void func_8009B5C0(HSD_GObj*);
void func_8009B5C4(HSD_GObj*);
void func_8009B634(HSD_GObj*);
void func_8009B654(HSD_GObj*);
void func_8009B744(HSD_GObj*);
void func_8009B764(HSD_GObj*);
void func_8009B7D8(HSD_GObj*);
void func_8009B7F8(HSD_GObj*);
void func_8009B8B4(HSD_GObj*);
void func_8009B948(HSD_GObj*);
void func_8009B988(HSD_GObj*);
void func_8009B9A8(HSD_GObj*);
void func_8009BA50(HSD_GObj*);
void func_8009BAA0(HSD_GObj*);
void func_8009BADC(HSD_GObj*);
void func_8009BAFC(HSD_GObj*);
void func_8009BBF0(HSD_GObj*);
void func_8009BBF4(HSD_GObj*);
void func_8009BC18(HSD_GObj*);
void func_8009BC38(HSD_GObj*);
void func_8009BCDC(HSD_GObj*);
void func_8009BCE0(HSD_GObj*);
void func_8009BD04(HSD_GObj*);
void func_8009BD24(HSD_GObj*);
void func_8009BDC4(HSD_GObj*);
void func_8009BE14(HSD_GObj*);
void func_8009BE34(HSD_GObj*);
void func_8009BE54(HSD_GObj*);
void func_8009BEB8(HSD_GObj*);
void func_8009BED8(HSD_GObj*);
void func_8009C0EC(HSD_GObj*);
void func_8009C130(HSD_GObj*);
void func_8009C150(HSD_GObj*);
void func_8009C20C(HSD_GObj*);
void func_8009C234(HSD_GObj*);
void func_8009C254(HSD_GObj*);
void func_8009C274(HSD_GObj*);
void func_8009C294(HSD_GObj*);
void func_8009C2BC(HSD_GObj*);
void func_8009C2DC(HSD_GObj*);
void func_8009C2FC(HSD_GObj*);
void func_8009C31C(HSD_GObj*);
void func_8009C344(HSD_GObj*);
void func_8009C364(HSD_GObj*);
void func_8009C384(HSD_GObj*);
void func_8009C3A4(HSD_GObj*);
void func_8009C3CC(HSD_GObj*);
void func_8009C410(HSD_GObj*);
void func_8009C414(HSD_GObj*);
void func_8009C434(HSD_GObj*);
void func_8009C830(HSD_GObj*);
void func_8009CA00(HSD_GObj*);
void func_8009CA04(HSD_GObj*);
void func_8009CA08(HSD_GObj*);
void func_8009CB04(HSD_GObj*);
void func_8009CB08(HSD_GObj*);
void func_8009CB0C(HSD_GObj*);
void func_8009CB10(HSD_GObj*);
void func_8009CF84(Fighter*);
void func_8009DC54(Fighter*);
void func_8009E0A8(HSD_GObj*);
void func_8009E0D4(Fighter*);
void func_8009E7B4(Fighter*, u8*);
void func_8009EC08(HSD_GObj*);
void func_8009EC0C(HSD_GObj*);
void func_8009EC3C(HSD_GObj*);
void func_8009EC40(HSD_GObj*);
void func_8009EF04(HSD_GObj*);
void func_8009EF40(HSD_GObj*);
void func_8009EF44(HSD_GObj*);
void func_8009EF48(HSD_GObj*);
void func_8009F048(HSD_GObj*);
void func_8009F0B8(HSD_GObj*);
void func_8009F0BC(HSD_GObj*);
void func_8009F0C0(HSD_GObj*);
void func_8009F1E0(HSD_GObj*);
void func_8009F2B0(HSD_GObj*);
void func_8009F2B4(HSD_GObj*);
void func_8009F2D4(HSD_GObj*);
void func_8009F400(HSD_GObj*);
void func_8009F43C(HSD_GObj*);
void func_8009F440(HSD_GObj*);
void func_8009F460(HSD_GObj*);
void func_8009F4A4(void);
void func_8009F578(Fighter*);
void func_800A0DA4(Fighter*);
void func_800A101C(Fighter*, s8, s8, s32);
void func_800B3900(HSD_GObj*);
void func_800BBC78(HSD_GObj*);
void func_800BBC7C(HSD_GObj*);
void func_800BBC80(HSD_GObj*);
void func_800BBC84(HSD_GObj*);
void func_800BC1B0(HSD_GObj*);
void func_800BC304(HSD_GObj*);
void func_800BC308(HSD_GObj*);
void func_800BC340(HSD_GObj*);
void func_800BC7E0(HSD_GObj*, HSD_GObj*);
void func_800BC8C4(HSD_GObj*);
void func_800BC8C8(HSD_GObj*);
void func_800BC8CC(HSD_GObj*);
void func_800BC8D0(HSD_GObj*);
void func_800BC8D4(HSD_GObj*, HSD_GObj*);
void func_800BC9B8(HSD_GObj*);
void func_800BC9BC(HSD_GObj*);
void func_800BC9C0(HSD_GObj*);
void func_800BC9C4(HSD_GObj*);
void func_800BC9C8(HSD_GObj*);
void func_800BCA54(HSD_GObj*);
void func_800BCAE8(HSD_GObj*);
void func_800BCAEC(HSD_GObj*);
void func_800BCAF0(HSD_GObj*);
void func_800BCB80(HSD_GObj*);
void func_800BCC14(HSD_GObj*);
void func_800BCC18(HSD_GObj*);
void func_800BCC1C(HSD_GObj*);
void func_800BCC7C(HSD_GObj*);
void func_800BCCF4(HSD_GObj*);
void func_800BCCF8(HSD_GObj*);
void func_800BCCFC(HSD_GObj*);
void func_800BCD5C(HSD_GObj*);
void func_800BCDD4(HSD_GObj*);
void func_800BCDD8(HSD_GObj*);
void func_800BCDDC(HSD_GObj*);
void func_800BCE64(HSD_GObj*, enum_t asid);
void func_800BCED8(HSD_GObj*);
void func_800BCEDC(HSD_GObj*);
void func_800BCEE0(HSD_GObj*);
void func_800BCEE4(HSD_GObj*);
void func_800BCEE8(HSD_GObj*);
void func_800BCEEC(HSD_GObj*);
void func_800BCEF0(HSD_GObj*);
void func_800BCEF4(HSD_GObj*);
void func_800BCEF8(HSD_GObj*);
void func_800BCEFC(HSD_GObj*);
void func_800BCF00(HSD_GObj*);
void func_800BCF04(HSD_GObj*);
void func_800BCF08(HSD_GObj*);
void func_800BCF0C(HSD_GObj*);
void func_800BCF10(HSD_GObj*);
void func_800BCF14(HSD_GObj*);
void func_800BCF18(HSD_GObj*, HSD_GObj*);
void func_800BD000(HSD_GObj*, HSD_GObj*);
void func_800BD17C(HSD_GObj*);
void func_800BD180(HSD_GObj*);
void func_800BD184(HSD_GObj*);
void func_800BD188(HSD_GObj*);
void func_800BD18C(HSD_GObj*);
void func_800BD190(HSD_GObj*);
void func_800BD194(HSD_GObj*);
void func_800BD198(HSD_GObj*);
void func_800BD38C(HSD_GObj*);
void func_800BD390(HSD_GObj*);
void func_800BD394(HSD_GObj*);
void func_800BD398(HSD_GObj*);
void func_800BD6E8(HSD_GObj*);
void func_800BD7BC(HSD_GObj*);
void func_800BD9D8(HSD_GObj*);
void func_800BD9DC(HSD_GObj*);
void func_800BDDC4(HSD_GObj*);
void func_800BDDC8(HSD_GObj*);
void func_800BDDCC(HSD_GObj*);
void func_800BDF10(HSD_GObj*);
void func_800BE258(HSD_GObj*);
void func_800BE25C(HSD_GObj*);
void func_800BE260(HSD_GObj*);
void func_800BE3A4(HSD_GObj*);
void func_800BE618(HSD_GObj*);
void func_800BE61C(HSD_GObj*);
void func_800BE620(HSD_GObj*);
void func_800BE6A8(HSD_GObj*);
void func_800BEB60(int, int, int);
void func_800BED84(HSD_GObj*);
void func_800BEF00(HSD_GObj*);
void func_800BEFD0(HSD_GObj*);
void func_800BFB4C(HSD_GObj*, s32*);
void func_800BFD04(HSD_GObj*);
void func_800BFE6C(HSD_GObj*);
void func_800BFE70(HSD_GObj*);
void func_800BFFAC(Fighter*);
void func_800BFFD0(Fighter*, s32, s32);
void func_800C0074(Fighter*);
void func_800C0134(Fighter*);
void func_800C0200(Fighter*, s32);
void func_800C0358(Fighter*, Fighter*, s32);
void func_800C0408(HSD_GObj*);
void func_800C06C0(void);
void func_800C09B4(HSD_GObj*);
void func_800C0A98(HSD_GObj*);
void func_800C0F34(HSD_GObj*);
void func_800C0FC8(HSD_GObj*);
void func_800C1194(HSD_GObj*);
void func_800C11E4(HSD_GObj*);
void func_800C12D8(HSD_GObj*);
void func_800C134C(HSD_GObj*);
void func_800C1350(HSD_GObj*);
void func_800C1354(HSD_GObj*);
void func_800C1460(HSD_GObj*);
void func_800C14B0(HSD_GObj*);
void func_800C1574(HSD_GObj*);
void func_800C15B4(HSD_GObj*);
void func_800C1B2C(HSD_GObj*);
void func_800C1B64(HSD_GObj*);
void func_800C1B84(HSD_GObj*);
void func_800C1BA4(HSD_GObj*);
void func_800C2028(HSD_GObj*);
void func_800C2180(HSD_GObj*);
void func_800C22C0(HSD_GObj*);
void func_800C2348(HSD_GObj*);
void func_800C252C(HSD_GObj*);
void func_800C25AC(HSD_GObj*);
void func_800C25B0(HSD_GObj*);
void func_800C25D0(HSD_GObj*);
void func_800C2FD8(HSD_GObj*);
void func_800C32AC(HSD_GObj*);
void func_800C334C(HSD_GObj*);
void func_800C3350(HSD_GObj*);
void func_800C3370(HSD_GObj*);
void func_800C33C8(HSD_GObj*);
void func_800C343C(HSD_GObj*);
void func_800C3440(HSD_GObj*);
void func_800C3460(HSD_GObj*);
void func_800C34B8(HSD_GObj*);
void func_800C34F4(HSD_GObj*);
void func_800C34F8(HSD_GObj*);
void func_800C3518(HSD_GObj*);
void func_800C37A0(HSD_GObj*);
void func_800C3D6C(HSD_GObj*);
void func_800C4380(HSD_GObj*);
void func_800C4384(HSD_GObj*);
void func_800C4388(HSD_GObj*);
void func_800C438C(HSD_GObj*);
void func_800C4438(HSD_GObj*);
void func_800C447C(HSD_GObj*);
void func_800C466C(HSD_GObj*);
void func_800C46E0(HSD_GObj*);
void func_800C46E4(HSD_GObj*);
void func_800C4704(HSD_GObj*);
void func_800C4900(HSD_GObj*);
void func_800C4964(HSD_GObj*);
void func_800C4968(HSD_GObj*);
void func_800C4A14(HSD_GObj*);
void func_800C4A18(HSD_GObj*);
void func_800C4BA4(HSD_GObj*);
void func_800C4BA8(HSD_GObj*);
void func_800C4BAC(HSD_GObj*);
void func_800C4C30(HSD_GObj*);
void func_800C4E2C(HSD_GObj*);
void func_800C4FEC(HSD_GObj*);
void func_800C5074(HSD_GObj*);
void func_800C50D4(HSD_GObj*);
void func_800C50F4(HSD_GObj*);
void func_800C511C(HSD_GObj*);
void func_800C5500(HSD_GObj*);
void func_800C56BC(HSD_GObj*);
void func_800C56DC(HSD_GObj*);
void func_800C572C(HSD_GObj*);
void func_800C574C(HSD_GObj*);
void func_800C5848(HSD_GObj*);
void func_800C59EC(HSD_GObj*);
void func_800C5A10(HSD_GObj*);
void func_800C5A30(HSD_GObj*);
void func_800C5B24(HSD_GObj*);
void func_800C5B44(HSD_GObj*);
void func_800C5B48(HSD_GObj*);
void func_800C5B68(HSD_GObj*);
void func_800C5C10(HSD_GObj*);
void func_800C5C74(HSD_GObj*);
void func_800C5C94(HSD_GObj*);
void func_800C5CB4(HSD_GObj*);
void func_800C5DBC(HSD_GObj*);
void func_800C5E94(HSD_GObj*);
void func_800C5F40(HSD_GObj*);
void func_800C5F60(HSD_GObj*);
void func_800C6020(HSD_GObj*);
void func_800C6084(HSD_GObj*);
void func_800C6088(HSD_GObj*);
void func_800C60A8(HSD_GObj*);
void func_800C61B0(HSD_GObj*);
void func_800C6370(HSD_GObj*);
void func_800C63B4(HSD_GObj*);
void func_800C63B8(HSD_GObj*);
void func_800C6404(HSD_GObj*);
void func_800C6700(HSD_GObj*);
void func_800C673C(HSD_GObj*);
void func_800C6740(HSD_GObj*);
void func_800C6950(HSD_GObj*);
void func_800C6CC8(HSD_GObj*);
void func_800C6D34(HSD_GObj*);
void func_800C6D38(HSD_GObj*);
void func_800C6E90(HSD_GObj*);
void func_800C7158(HSD_GObj*);
void func_800C7200(HSD_GObj*);
void func_800C737C(HSD_GObj*);
void func_800C7414(HSD_GObj*);
void func_800C74AC(HSD_GObj*);
void func_800C7734(HSD_GObj*);
void func_800C77B0(HSD_GObj*);
void func_800C77B4(HSD_GObj*);
void func_800C77B8(HSD_GObj*);
void func_800C7A58(HSD_GObj*);
void func_800C7AD4(HSD_GObj*);
void func_800C7AD8(HSD_GObj*);
void func_800C7ADC(HSD_GObj*);
void func_800C7FC8(HSD_GObj*);
void func_800C8004(HSD_GObj*);
void func_800C8008(HSD_GObj*);
void func_800C8028(HSD_GObj*);
void func_800C8064(void);
void func_800C8348(HSD_GObj*, s32, s32);
void func_800C8438(HSD_GObj*);
void func_800C8540(HSD_GObj*);
void func_800C884C(HSD_GObj*);
void func_800C88A0(Fighter*);
void func_800C88D4(HSD_GObj*, s32, bool);
void func_800C89A0(HSD_GObj*);
void func_800C8A64(HSD_GObj*);
void func_800C8C04(HSD_GObj*);
void func_800C8C40(HSD_GObj*);
void func_800C8C44(HSD_GObj*);
void func_800C8C64(HSD_GObj*);
void func_800C8C84(HSD_GObj*);
void func_800C8D00(HSD_GObj*);
void func_800C8F6C(void);
void func_800C8FC4(HSD_GObj*);
void func_800C9034(HSD_GObj*);
void func_800C91C0(HSD_GObj*);
void func_800C9208(HSD_GObj*);
void func_800C925C(HSD_GObj*);
void func_800C9260(HSD_GObj*);
void func_800C95F4(HSD_GObj*);
void func_800C9614(HSD_GObj*);
void func_800C9768(HSD_GObj*);
void func_800C9788(HSD_GObj*);
void func_800C9840(HSD_GObj*, s32, s32, f32, f32, f32);
void func_800C9924(HSD_GObj*);
void func_800C9970(HSD_GObj*);
void func_800C99F8(HSD_GObj*);
void func_800C9BEC(HSD_GObj*);
void func_800C9C0C(HSD_GObj*);
void func_800C9E10(HSD_GObj*);
void func_800C9ED8(HSD_GObj*);
void func_800C9EFC(HSD_GObj*);
void func_800CA024(HSD_GObj*);
void func_800CA1F4(HSD_GObj*);
void func_800CA230(HSD_GObj*);
void func_800CA53C(HSD_GObj*);
void func_800CA5D0(HSD_GObj*);
void func_800CA77C(HSD_GObj*);
void func_800CA830(HSD_GObj*);
void func_800CA95C(HSD_GObj*);
void func_800CAA2C(HSD_GObj*);
void func_800CAA4C(HSD_GObj*);
void func_800CAA6C(HSD_GObj*);
void func_800CAB84(HSD_GObj*);
void func_800CABA4(HSD_GObj*);
void func_800CAC9C(HSD_GObj*);
void func_800CADB0(HSD_GObj*);
void func_800CAE18(HSD_GObj*);
void func_800CAE60(HSD_GObj*);
void func_800CB110(HSD_GObj*, s32, f32);
void func_800CB2F8(HSD_GObj*);
void func_800CB334(HSD_GObj*);
void func_800CB438(HSD_GObj*);
void func_800CB474(HSD_GObj*);
void func_800CB4B0(HSD_GObj*);
void func_800CB528(HSD_GObj*);
void func_800CB59C(HSD_GObj*);
void func_800CB5FC(HSD_GObj*);
void func_800CB6AC(HSD_GObj*);
void func_800CB6CC(HSD_GObj*);
void func_800CC388(HSD_GObj*);
void func_800CC4F8(HSD_GObj*);
void func_800CC634(HSD_GObj*);
void func_800CC700(HSD_GObj*);
void func_800CC730(HSD_GObj*);
void func_800CCA00(HSD_GObj*);
void func_800CCAAC(HSD_GObj*);
void func_800CCD34(HSD_GObj*);
void func_800CCD58(HSD_GObj*);
void func_800CCD78(HSD_GObj*);
void func_800CCDFC(HSD_GObj*);
void func_800CCE50(HSD_GObj*);
void func_800CCE74(HSD_GObj*);
void func_800CCE94(HSD_GObj*);
void func_800CD390(HSD_GObj*);
void func_800CD3B0(HSD_GObj*);
void func_800CD3D0(HSD_GObj*);
void func_800CD3F0(HSD_GObj*);
void func_800CD458(HSD_GObj*);
void func_800CD478(HSD_GObj*);
void func_800CD498(HSD_GObj*);
void func_800CD4B8(HSD_GObj*);
void func_800CD520(HSD_GObj*);
void func_800CD540(HSD_GObj*);
void func_800CD560(HSD_GObj*);
void func_800CD580(HSD_GObj*);
void func_800CD6A0(HSD_GObj*);
void func_800CD7C4(HSD_GObj*);
void func_800CD7E4(HSD_GObj*);
void func_800CD804(HSD_GObj*);
void func_800CD88C(HSD_GObj*);
void func_800CD8AC(HSD_GObj*);
void func_800CD8CC(HSD_GObj*);
void func_800CD8EC(HSD_GObj*);
void func_800CDB14(HSD_GObj*);
void func_800CDB34(HSD_GObj*);
void func_800CDB54(HSD_GObj*);
void func_800CDB74(HSD_GObj*);
void func_800CE308(HSD_GObj*);
void func_800CE328(HSD_GObj*);
void func_800CE348(HSD_GObj*);
void func_800CE34C(HSD_GObj*);
void func_800CE350(HSD_GObj*);
void func_800CE370(HSD_GObj*);
void func_800CE390(HSD_GObj*);
void func_800CE3B8(HSD_GObj*);
void func_800CEAF0(HSD_GObj*);
void func_800CEBA0(HSD_GObj*);
void func_800CEC50(HSD_GObj*);
void func_800CEC54(HSD_GObj*);
void func_800CEC58(HSD_GObj*);
void func_800CEC78(HSD_GObj*);
void func_800CEC98(HSD_GObj*);
void func_800CECC0(HSD_GObj*);
void func_800CEDE0(HSD_GObj*);
void func_800CEE00(HSD_GObj*);
void func_800CEE30(HSD_GObj*);
void func_800CEE50(HSD_GObj*);
void func_800CF0B8(HSD_GObj*);
void func_800CF118(HSD_GObj*);
void func_800CF1A0(HSD_GObj*);
void func_800CF258(HSD_GObj*);
void func_800CF2B8(HSD_GObj*);
void func_800CF2BC(HSD_GObj*);
void func_800CF380(HSD_GObj*);
void func_800CF3A0(HSD_GObj*);
void func_800CF424(HSD_GObj*);
void func_800CF428(HSD_GObj*);
void func_800CF494(HSD_GObj*);
void func_800CF4B4(HSD_GObj*);
void func_800CF528(HSD_GObj*);
void func_800CF52C(HSD_GObj*);
void func_800CF54C(HSD_GObj*);
void func_800CF56C(HSD_GObj*);
void func_800CF594(void);
void func_800D0FA0(HSD_GObj*);
void func_800D105C(HSD_GObj*);
void func_800D14E4(HSD_GObj*);
void func_800D1868(HSD_GObj*);
void func_800D18A4(HSD_GObj*);
void func_800D1A28(HSD_GObj*);
void func_800D1A64(HSD_GObj*);
void func_800D1A8C(HSD_GObj*);
void func_800D1CAC(HSD_GObj*);
void func_800D1CE8(HSD_GObj*);
void func_800D1E1C(HSD_GObj*);
void func_800D1E58(HSD_GObj*);
void func_800D1E80(HSD_GObj*);
void func_800D2158(HSD_GObj*);
void func_800D2194(HSD_GObj*);
void func_800D2318(HSD_GObj*);
void func_800D2354(HSD_GObj*);
void func_800D237C(HSD_GObj*);
void func_800D259C(HSD_GObj*);
void func_800D25D8(HSD_GObj*);
void func_800D270C(HSD_GObj*);
void func_800D2748(HSD_GObj*);
void func_800D2DD0(HSD_GObj*);
void func_800D2E0C(HSD_GObj*);
void func_800D2E2C(HSD_GObj*);
void func_800D2E4C(HSD_GObj*);
void func_800D2EF8(HSD_GObj*);
void func_800D2F34(HSD_GObj*);
void func_800D2F54(HSD_GObj*);
void func_800D2F74(HSD_GObj*);
void func_800D30C0(HSD_GObj*);
void func_800D30FC(HSD_GObj*);
void func_800D3100(HSD_GObj*);
void func_800D3120(HSD_GObj*);
void func_800D3158(HSD_GObj*);
void func_800D3910(HSD_GObj*);
void func_800D394C(HSD_GObj*);
void func_800D3B88(HSD_GObj*);
void func_800D3BC4(HSD_GObj*);
void func_800D3E00(HSD_GObj*);
void func_800D3E3C(HSD_GObj*);
void func_800D4078(HSD_GObj*);
void func_800D40B4(HSD_GObj*);
void func_800D42E4(HSD_GObj*);
void func_800D4560(HSD_GObj*);
void func_800D4A08(HSD_GObj*);
void func_800D4CE8(HSD_GObj*);
void func_800D4E30(HSD_GObj*);
void func_800D4F24(HSD_GObj*, s32);
void func_800D4FF4(HSD_GObj*);
void func_800D52F8(HSD_GObj*);
void func_800D5358(HSD_GObj*);
void func_800D535C(HSD_GObj*);
void func_800D5470(HSD_GObj*);
void func_800D56EC(HSD_GObj*);
void func_800D575C(HSD_GObj*);
void func_800D58F4(HSD_GObj*);
void func_800D5A08(HSD_GObj*);
void func_800D5A6C(HSD_GObj*);
void func_800D5AEC(HSD_GObj*, s32, s32, s32, Fighter*, f32, f32);
void func_800D5BF8(HSD_GObj*);
void func_800D5CB0(HSD_GObj*, s32, f32);
void func_800D5D3C(HSD_GObj*);
void func_800D5D78(HSD_GObj*);
void func_800D5F18(HSD_GObj*);
void func_800D5F38(HSD_GObj*);
void func_800D607C(HSD_GObj*);
void func_800D60B8(HSD_GObj*);
void func_800D623C(HSD_GObj*);
void func_800D625C(HSD_GObj*);
void func_800D638C(HSD_GObj*);
void func_800D6448(HSD_GObj*);
void func_800D6474(HSD_GObj*);
void func_800D6584(HSD_GObj*);
void func_800D65B8(HSD_GObj*);
void func_800D6658(HSD_GObj*);
void func_800D6694(HSD_GObj*);
void func_800D6784(HSD_GObj*);
void func_800D67A4(HSD_GObj*);
void func_800D6B00(HSD_GObj*, s32);
void func_800D6C0C(HSD_GObj*);
void func_800D6C60(HSD_GObj*, HSD_GObjEvent callback);
void func_800D6C60(HSD_GObj*, HSD_GObjEvent);
void func_800D6D48(HSD_GObj*);
void func_800D6E34(HSD_GObj* gobj);
void func_800D6E34(HSD_GObj*);
void func_800D6E70(HSD_GObj* gobj);
void func_800D6E70(HSD_GObj*);
void func_800D6E98(HSD_GObj*);
void func_800D6EB8(HSD_GObj*);
void func_800D6ED8(HSD_GObj*);
void func_800D6EF8(HSD_GObj*);
void func_800D6F18(HSD_GObj*);
void func_800D6F38(HSD_GObj*);
void func_800D71D8(HSD_GObj*);
void func_800D7590(HSD_GObj*);
void func_800D7614(HSD_GObj*);
void func_800D7634(HSD_GObj*);
void func_800D767C(HSD_GObj*);
void func_800D79AC(HSD_GObj*);
void func_800D79B0(HSD_GObj*);
void func_800D7AEC(HSD_GObj*);
void func_800D7B1C(HSD_GObj*);
void func_800D7B4C(HSD_GObj*);
void func_800D7B6C(HSD_GObj*);
void func_800D7B8C(HSD_GObj*);
void func_800D7BB4(HSD_GObj*);
void func_800D7DFC(HSD_GObj*);
void func_800D7F10(HSD_GObj*);
void func_800D8024(HSD_GObj*);
void func_800D8044(HSD_GObj*);
void func_800D8064(HSD_GObj*);
void func_800D8084(HSD_GObj*);
void func_800D80A4(HSD_GObj*);
void func_800D80CC(HSD_GObj*);
void func_800D83AC(HSD_GObj*);
void func_800D83F4(HSD_GObj*);
void func_800D843C(HSD_GObj*);
void func_800D8440(HSD_GObj*);
void func_800D8444(HSD_GObj*);
void func_800D8464(HSD_GObj*);
void func_800D8484(HSD_GObj*);
void func_800D84AC(HSD_GObj*);
void func_800D88B8(HSD_GObj*);
void func_800D88D8(HSD_GObj*);
void func_800D88F8(HSD_GObj*);
void func_800D88FC(HSD_GObj*);
void func_800D8900(HSD_GObj*);
void func_800D8920(HSD_GObj*);
void func_800D8940(HSD_GObj*);
void func_800D8968(HSD_GObj*);
void func_800D8CC8(HSD_GObj*);
void func_800D8D24(HSD_GObj*);
void func_800D8D80(HSD_GObj*);
void func_800D8D84(HSD_GObj*);
void func_800D8D88(HSD_GObj*);
void func_800D8DD0(HSD_GObj*);
void func_800D8E08(HSD_GObj*);
void func_800D8E6C(HSD_GObj*);
void func_800D94D8(HSD_GObj*);
void func_800D9C98(HSD_GObj* gobj);
void func_800D9C98(HSD_GObj*);
void func_800D9E80(HSD_GObj*);
void func_800D9F90(HSD_GObj*);
void func_800D9F94(HSD_GObj*);
void func_800D9FDC(HSD_GObj*);
void func_800DA318(HSD_GObj*);
void func_800DA31C(HSD_GObj*);
void func_800DA3D0(HSD_GObj*);
void func_800DA418(HSD_GObj*);
void func_800DA568(HSD_GObj*);
void func_800DA5A4(HSD_GObj*);
void func_800DA5A8(HSD_GObj*);
void func_800DA5F0(HSD_GObj*);
void func_800DA744(HSD_GObj*);
void func_800DA780(HSD_GObj*);
void func_800DA784(HSD_GObj*);
void func_800DA7E4(HSD_GObj*);
void func_800DAC70(HSD_GObj*);
void func_800DAC74(HSD_GObj*);
void func_800DADE8(HSD_GObj*);
void func_800DAE94(HSD_GObj*);
void func_800DB004(HSD_GObj*);
void func_800DB008(HSD_GObj*);
void func_800DB00C(HSD_GObj*);
void func_800DB1F8(HSD_GObj*);
void func_800DB368(Fighter*, Fighter*);
void func_800DB464(HSD_GObj*);
void func_800DB908(HSD_GObj*);
void func_800DBA4C(HSD_GObj*);
void func_800DBA6C(HSD_GObj*);
void func_800DBA8C(HSD_GObj*);
void func_800DBD10(HSD_GObj*);
void func_800DBD30(HSD_GObj*);
void func_800DBD50(HSD_GObj*);
void func_800DBE9C(HSD_GObj*);
void func_800DC110(HSD_GObj*);
void func_800DC160(HSD_GObj*);
void func_800DC224(HSD_GObj*);
void func_800DC264(HSD_GObj*);
void func_800DC2E4(HSD_GObj*);
void func_800DC328(HSD_GObj*);
void func_800DC32C(HSD_GObj*);
void func_800DC34C(HSD_GObj*);
void func_800DC468(HSD_GObj*);
void func_800DC4AC(HSD_GObj*);
void func_800DC4B0(HSD_GObj*);
void func_800DC5EC(HSD_GObj*);
void func_800DC750(HSD_GObj*);
void func_800DC7F0(HSD_GObj*);
void func_800DC82C(HSD_GObj*);
void func_800DC830(HSD_GObj*);
void func_800DC890(HSD_GObj*);
void func_800DC920(HSD_GObj*, HSD_GObj*);
void func_800DD168(HSD_GObj*);
void func_800DD8C4(HSD_GObj*);
void func_800DD92C(HSD_GObj*);
void func_800DD930(HSD_GObj*);
void func_800DD990(HSD_GObj*);
void func_800DDA10(HSD_GObj*);
void func_800DDA5C(HSD_GObj*);
void func_800DDA60(HSD_GObj*);
void func_800DDAC0(HSD_GObj*);
void func_800DDB40(HSD_GObj*);
void func_800DDB8C(HSD_GObj*);
void func_800DDB90(HSD_GObj*);
void func_800DDBF0(HSD_GObj*);
void func_800DDC70(HSD_GObj*);
void func_800DDCB4(HSD_GObj*);
void func_800DDD00(HSD_GObj*);
void func_800DDD04(HSD_GObj*);
void func_800DDD64(HSD_GObj*);
void func_800DE2A8(HSD_GObj*, HSD_GObj*);
void func_800DE508(HSD_GObj*);
void func_800DE69C(HSD_GObj*);
void func_800DE6BC(HSD_GObj*);
void func_800DE6C0(HSD_GObj*);
void func_800DE6C4(HSD_GObj*);
void func_800DE6C8(HSD_GObj*);
void func_800DE6E8(HSD_GObj*);
void func_800DE6EC(HSD_GObj*);
void func_800DE6F0(HSD_GObj*);
void func_800DE6F4(HSD_GObj*);
void func_800DE714(HSD_GObj*);
void func_800DE718(HSD_GObj*);
void func_800DE71C(HSD_GObj*);
void func_800DE720(HSD_GObj*);
void func_800DE76C(HSD_GObj*);
void func_800DE78C(HSD_GObj*);
void func_800DE790(HSD_GObj*);
void func_800DE794(HSD_GObj*);
void func_800DE7C0(HSD_GObj*, s32, s32);
void func_800DECF4(HSD_GObj*);
void func_800DED30(HSD_GObj*);
void func_800DEE44(HSD_GObj*);
void func_800DEE64(HSD_GObj*);
void func_800DEEA8(HSD_GObj*);
void func_800DEEB8(void);
void func_800DEF38(HSD_GObj*);
void func_800DF0D0(HSD_GObj*);
void func_SetEntityFacingDirection(HSD_GObj*, f32 facing_dir);

/// Interrupt_Wait
void func_8008A4D4(HSD_GObj*);

/// @todo UnclePunch Map file: MS_203_PassiveWalljump_Walljump
void func_800C1E64(HSD_GObj* pPlayerEntityStruct, s32, s32, u8, f32);

/// @todo enum params
void func_800DEAE8(HSD_GObj* gobj, enum_t asid0, enum_t asid1);

#endif
