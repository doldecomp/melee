#ifndef MELEE_FT_CHARA_FTKIRBY_FTKIRBY_H
#define MELEE_FT_CHARA_FTKIRBY_FTKIRBY_H

#include "ft/ftcommon.h"
#include "ft/types.h"
#include "lb/lbvector.h"

typedef struct _ftKirbyAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    s32 x14;
    f32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C;
    u8 data_filler_1[0x168 - 0x30];
    f32 x168;
    u8 data_filler_2[0x190 - 0x16C];
    s32 x190;
    u8 data_filler_3[0x384 - 0x194];
    f32 x384;
    u8 data_filler_4[0x424 - 0x388];
} ftKirbyAttributes;

extern MotionState ftKirby_MotionStateTable[];
extern MotionState lbl_803CA04C[];
extern char lbl_803CA308[];
extern char lbl_803CA314[];
extern Fighter_CostumeStrings lbl_803CA5B4[];
extern char lbl_803CA4E0[];
extern Fighter_DemoStrings lbl_803CA55C;

void func_800EED50(s32, s32);
void func_800F1D24(HSD_GObj*);
void func_800F5BA4(Fighter*);
void func_800F5C34(Fighter*);
void func_800F5D04(HSD_GObj* gobj, bool);
void ftKirby_OnItemPickup(HSD_GObj* gobj, bool bool);
void func_800EEB00(HSD_GObj*, void*);
void func_800EEB1C(HSD_GObj*, void*);
void ftKirby_800EE74C(HSD_GObj* gobj);
void ftKirby_800EE7B8(HSD_GObj* gobj);
void func_800EE528(void);
void ftKirby_OnDeath(HSD_GObj* gobj);
void ftKirby_OnLoad(HSD_GObj* gobj);
void func_800F203C(HSD_GObj*);
void func_800F205C(HSD_GObj*);
void lbl_800F207C(HSD_GObj*);
void lbl_800F209C(HSD_GObj*);
void func_800F2124(HSD_GObj*);
void func_800F2160(HSD_GObj*);
void lbl_800F2164(HSD_GObj*);
void lbl_800F2198(HSD_GObj*);
void lbl_800F70A0(HSD_GObj*);
void lbl_800F8890(HSD_GObj*);
void lbl_800F8C10(HSD_GObj*);
void lbl_800F72F8(HSD_GObj*);
void lbl_800F7FA0(HSD_GObj*);
void lbl_800F88D0(HSD_GObj*);
void lbl_800F8C60(HSD_GObj*);
void lbl_800F7300(HSD_GObj*);
void lbl_800F8910(HSD_GObj*);
void lbl_800F8CB0(HSD_GObj*);
void lbl_800F7498(HSD_GObj*);
void lbl_800F8970(HSD_GObj*);
void func_800F8D28(HSD_GObj*);
void lbl_800F7378(HSD_GObj*);
void lbl_800F8950(HSD_GObj*);
void lbl_800F8D00(HSD_GObj*);
void lbl_800F75F8(HSD_GObj*);
void lbl_800F89D0(HSD_GObj*);
void lbl_800F8DA0(HSD_GObj*);
void lbl_800F76F8(HSD_GObj*);
void lbl_800F8060(HSD_GObj*);
void lbl_800F8A10(HSD_GObj*);
void lbl_800F8DF0(HSD_GObj*);
void lbl_800F7E78(HSD_GObj*);
void lbl_800F8770(HSD_GObj*);
void lbl_800F8B90(HSD_GObj*);
void lbl_800F8FD0(HSD_GObj*);
void lbl_800F7E78(HSD_GObj*);
void lbl_800F8770(HSD_GObj*);
void lbl_800F8B90(HSD_GObj*);
void lbl_800F7D58(HSD_GObj*);
void func_800F8B50(HSD_GObj*);
void func_800F8F80(HSD_GObj*);
void lbl_800F7E98(HSD_GObj*);
void lbl_800F8870(HSD_GObj*);
void lbl_800F8BB0(HSD_GObj*);
void lbl_800F8FF8(HSD_GObj*);
void lbl_800F7F20(HSD_GObj*);
void lbl_800F8BD0(HSD_GObj*);
void lbl_800F9020(HSD_GObj*);
void lbl_800F7F24(HSD_GObj*);
void lbl_800F8BF0(HSD_GObj*);
void lbl_800F9048(HSD_GObj*);
void lbl_800F7B20(HSD_GObj*);
void lbl_800F8AF0(HSD_GObj*);
void lbl_800F8F08(HSD_GObj*);
void lbl_800F7A70(HSD_GObj*);
void lbl_800F8AD0(HSD_GObj*);
void lbl_800F8EE0(HSD_GObj*);
void lbl_800F7808(HSD_GObj*);
void lbl_800F8A70(HSD_GObj*);
void lbl_800F8E68(HSD_GObj*);
void func_800F7700(HSD_GObj*);
void lbl_800F8A50(HSD_GObj*);
void lbl_800F8E40(HSD_GObj*);
void lbl_800F71CC(HSD_GObj*);
void lbl_800F88B0(HSD_GObj*);
void lbl_800F8C38(HSD_GObj*);
void lbl_800F72FC(HSD_GObj*);
void lbl_800F8000(HSD_GObj*);
void lbl_800F88F0(HSD_GObj*);
void lbl_800F8C88(HSD_GObj*);
void lbl_800F733C(HSD_GObj*);
void lbl_800F8930(HSD_GObj*);
void lbl_800F8CD8(HSD_GObj*);
void lbl_800F75D8(HSD_GObj*);
void lbl_800F89B0(HSD_GObj*);
void lbl_800F8D78(HSD_GObj*);
void lbl_800F75B8(HSD_GObj*);
void lbl_800F75B8(HSD_GObj*);
void lbl_800F8990(HSD_GObj*);
void lbl_800F8D50(HSD_GObj*);
void lbl_800F7674(HSD_GObj*);
void lbl_800F89F0(HSD_GObj*);
void lbl_800F8DC8(HSD_GObj*);
void func_800F76FC(HSD_GObj*);
void lbl_800F844C(HSD_GObj*);
void lbl_800F8A30(HSD_GObj*);
void lbl_800F8E18(HSD_GObj*);
void lbl_800F7C94(HSD_GObj*);
void lbl_800F8B30(HSD_GObj*);
void lbl_800F8F58(HSD_GObj*);
void lbl_800F7BE4(HSD_GObj*);
void lbl_800F8B10(HSD_GObj*);
void lbl_800F8F30(HSD_GObj*);
void lbl_800F79C0(HSD_GObj*);
void lbl_800F8AB0(HSD_GObj*);
void lbl_800F8EB8(HSD_GObj*);
void lbl_800F78B8(HSD_GObj*);
void lbl_800F8A90(HSD_GObj*);
void lbl_800F8E90(HSD_GObj*);
void lbl_800F7DE4(HSD_GObj*);
void lbl_800F8B70(HSD_GObj*);
void lbl_800F8FA8(HSD_GObj*);
void lbl_800F5660(HSD_GObj*);
void func_800F56D8(HSD_GObj*);
void func_800F5718(HSD_GObj*);
void lbl_800F569C(HSD_GObj*);
void lbl_800F56F8(HSD_GObj*);
void lbl_800F5778(HSD_GObj*);
void lbl_800F2470(HSD_GObj*);
void lbl_800F2758(HSD_GObj*);
void lbl_800F2910(HSD_GObj*);
void lbl_800F2BBC(HSD_GObj*);
void lbl_800F24F8(HSD_GObj*);
void lbl_800F2828(HSD_GObj*);
void lbl_800F2984(HSD_GObj*);
void lbl_800F2C5C(HSD_GObj*);
void lbl_800F2578(HSD_GObj*);
void lbl_800F282C(HSD_GObj*);
void lbl_800F29F8(HSD_GObj*);
void lbl_800F2D98(HSD_GObj*);
void lbl_800F257C(HSD_GObj*);
void func_800F2830(HSD_GObj*);
void lbl_800F2A48(HSD_GObj*);
void lbl_800F2EA0(HSD_GObj*);
void lbl_800F25EC(HSD_GObj*);
void lbl_800F2834(HSD_GObj*);
void lbl_800F2A68(HSD_GObj*);
void lbl_800F2F70(HSD_GObj*);
void lbl_800F266C(HSD_GObj*);
void lbl_800F2904(HSD_GObj*);
void lbl_800F2AE4(HSD_GObj*);
void lbl_800F3004(HSD_GObj*);
void lbl_800F26E4(HSD_GObj*);
void lbl_800F2908(HSD_GObj*);
void lbl_800F2B60(HSD_GObj*);
void lbl_800F3140(HSD_GObj*);
void lbl_800F26E8(HSD_GObj*);
void lbl_800F290C(HSD_GObj*);
void lbl_800F2B9C(HSD_GObj*);
void lbl_800F3248(HSD_GObj*);
void lbl_800F3F80(HSD_GObj*);
void lbl_800F42D8(HSD_GObj*);
void lbl_800F451C(HSD_GObj*);
void lbl_800F4628(HSD_GObj*);
void lbl_800F402C(HSD_GObj*);
void lbl_800F42DC(HSD_GObj*);
void lbl_800F453C(HSD_GObj*);
void lbl_800F4800(HSD_GObj*);
void lbl_800F4074(HSD_GObj*);
void lbl_800F43FC(HSD_GObj*);
void lbl_800F4584(HSD_GObj*);
void lbl_800F49E4(HSD_GObj*);
void lbl_800F412C(HSD_GObj*);
void func_800F4400(HSD_GObj*);
void func_800F45A4(HSD_GObj*);
void lbl_800F4B3C(HSD_GObj*);
void func_800F41D8(HSD_GObj*);
void lbl_800F4404(HSD_GObj*);
void lbl_800F45C4(HSD_GObj*);
void lbl_800F4E78(HSD_GObj*);
void lbl_800F4220(HSD_GObj*);
void lbl_800F4518(HSD_GObj*);
void lbl_800F4608(HSD_GObj*);
void lbl_800F51C0(HSD_GObj*);
void lbl_800F9198(HSD_GObj*);
void lbl_800F91D4(HSD_GObj*);
void lbl_800F9204(HSD_GObj*);
void lbl_800F9224(HSD_GObj*);
void lbl_800F9454(HSD_GObj*);
void lbl_800F9490(HSD_GObj*);
void lbl_800F94C0(HSD_GObj*);
void lbl_800F94E0(HSD_GObj*);
void lbl_800FBBC4(HSD_GObj*);
void lbl_800FC374(HSD_GObj*);
void lbl_800FC70C(HSD_GObj*);
void lbl_800FC7CC(HSD_GObj*);
void lbl_800FBDFC(HSD_GObj*);
void lbl_800FC46C(HSD_GObj*);
void lbl_800FC72C(HSD_GObj*);
void lbl_800FC880(HSD_GObj*);
void lbl_800FBED0(HSD_GObj*);
void lbl_800FC53C(HSD_GObj*);
void lbl_800FC74C(HSD_GObj*);
void lbl_800FC934(HSD_GObj*);
void lbl_800FBF34(HSD_GObj*);
void lbl_800FC540(HSD_GObj*);
void lbl_800FC76C(HSD_GObj*);
void lbl_800FC9F0(HSD_GObj*);
void lbl_800FC1A0(HSD_GObj*);
void lbl_800FC638(HSD_GObj*);
void lbl_800FC78C(HSD_GObj*);
void lbl_800FCAA4(HSD_GObj*);
void lbl_800FC274(HSD_GObj*);
void lbl_800FC708(HSD_GObj*);
void lbl_800FC7AC(HSD_GObj*);
void lbl_800FCB58(HSD_GObj*);
void lbl_800FD0BC(HSD_GObj*);
void lbl_800FD688(HSD_GObj*);
void lbl_800FD7F0(HSD_GObj*);
void lbl_800FD8B0(HSD_GObj*);
void lbl_800FD250(HSD_GObj*);
void lbl_800FD68C(HSD_GObj*);
void lbl_800FD810(HSD_GObj*);
void lbl_800FD938(HSD_GObj*);
void lbl_800FD418(HSD_GObj*);
void lbl_800FD7E0(HSD_GObj*);
void lbl_800FD830(HSD_GObj*);
void lbl_800FD9E0(HSD_GObj*);
void lbl_800FD49C(HSD_GObj*);
void lbl_800FD7E4(HSD_GObj*);
void lbl_800FD850(HSD_GObj*);
void lbl_800FDA68(HSD_GObj*);
void lbl_800FD4E0(HSD_GObj*);
void lbl_800FD7E8(HSD_GObj*);
void lbl_800FD870(HSD_GObj*);
void lbl_800FDAF0(HSD_GObj*);
void lbl_800FD608(HSD_GObj*);
void lbl_800FD7EC(HSD_GObj*);
void lbl_800FD890(HSD_GObj*);
void lbl_800FDB78(HSD_GObj*);
void func_80109D6C(HSD_GObj*);
void func_8010A5EC(HSD_GObj*);
void func_8010A72C(HSD_GObj*);
void func_80109EE8(HSD_GObj*);
void lbl_8010A64C(HSD_GObj*);
void lbl_8010A7A4(HSD_GObj*);
void lbl_80109E04(HSD_GObj*);
void lbl_8010A62C(HSD_GObj*);
void lbl_8010A77C(HSD_GObj*);
void func_8010A304(HSD_GObj*);
void func_8010A6CC(HSD_GObj*);
void func_8010A844(HSD_GObj*);
void func_8010A1A4(HSD_GObj*);
void lbl_8010A6AC(HSD_GObj*);
void lbl_8010A81C(HSD_GObj*);
void lbl_80109DB8(HSD_GObj*);
void lbl_8010A60C(HSD_GObj*);
void lbl_8010A754(HSD_GObj*);
void lbl_8010A0B8(HSD_GObj*);
void lbl_8010A66C(HSD_GObj*);
void lbl_8010A7F4(HSD_GObj*);
void lbl_80109FD4(HSD_GObj*);
void lbl_8010A68C(HSD_GObj*);
void lbl_8010A7CC(HSD_GObj*);
void lbl_8010A528(HSD_GObj*);
void lbl_8010A70C(HSD_GObj*);
void lbl_8010A894(HSD_GObj*);
void lbl_8010A3C8(HSD_GObj*);
void func_8010A6EC(HSD_GObj*);
void func_8010A86C(HSD_GObj*);
void lbl_800FE360(HSD_GObj*);
void lbl_800FEA50(HSD_GObj*);
void lbl_800FEAF8(HSD_GObj*);
void lbl_800FEBB8(HSD_GObj*);
void lbl_800FE450(HSD_GObj*);
void lbl_800FEA78(HSD_GObj*);
void lbl_800FEB18(HSD_GObj*);
void lbl_800FEBD8(HSD_GObj*);
void lbl_800FE5C8(HSD_GObj*);
void lbl_800FEAA0(HSD_GObj*);
void func_800FEB38(HSD_GObj*);
void lbl_800FEBF8(HSD_GObj*);
void lbl_800FE688(HSD_GObj*);
void lbl_800FEAA4(HSD_GObj*);
void lbl_800FEB58(HSD_GObj*);
void lbl_800FEC18(HSD_GObj*);
void lbl_800FE778(HSD_GObj*);
void lbl_800FEACC(HSD_GObj*);
void lbl_800FEB78(HSD_GObj*);
void lbl_800FEC38(HSD_GObj*);
void func_800FE928(HSD_GObj*);
void lbl_800FEAF4(HSD_GObj*);
void lbl_800FEB98(HSD_GObj*);
void lbl_800FEC58(HSD_GObj*);
void lbl_800FA0F4(HSD_GObj*);
void lbl_800FA418(HSD_GObj*);
void lbl_800FA420(HSD_GObj*);
void lbl_800FA460(HSD_GObj*);
void func_800FA254(HSD_GObj*);
void lbl_800FA41C(HSD_GObj*);
void lbl_800FA440(HSD_GObj*);
void lbl_800FA4F0(HSD_GObj*);
void lbl_800F96F4(HSD_GObj*);
void lbl_800F976C(HSD_GObj*);
void lbl_800F97CC(HSD_GObj*);
void lbl_800F980C(HSD_GObj*);
void lbl_800F9730(HSD_GObj*);
void lbl_800F979C(HSD_GObj*);
void lbl_800F97EC(HSD_GObj*);
void lbl_800F9880(HSD_GObj*);
void lbl_800F9AEC(HSD_GObj*);
void lbl_800F9B64(HSD_GObj*);
void lbl_800F9C58(HSD_GObj*);
void lbl_800F9E8C(HSD_GObj*);
void lbl_800F9B28(HSD_GObj*);
void lbl_800F9B68(HSD_GObj*);
void lbl_800F9D40(HSD_GObj*);
void lbl_800F9F34(HSD_GObj*);
void lbl_800FEE70(HSD_GObj*);
void lbl_800FF3DC(HSD_GObj*);
void lbl_800FF4CC(HSD_GObj*);
void lbl_800FF664(HSD_GObj*);
void lbl_800FEF58(HSD_GObj*);
void lbl_800FF3E0(HSD_GObj*);
void lbl_800FF504(HSD_GObj*);
void lbl_800FF6D0(HSD_GObj*);
void lbl_800FEF58(HSD_GObj*);
void lbl_800FF3E0(HSD_GObj*);
void lbl_800FF504(HSD_GObj*);
void lbl_800FF6D0(HSD_GObj*);
void lbl_800FF08C(HSD_GObj*);
void lbl_800FF450(HSD_GObj*);
void lbl_800FF524(HSD_GObj*);
void lbl_800FF73C(HSD_GObj*);
void lbl_800FF10C(HSD_GObj*);
void lbl_800FF454(HSD_GObj*);
void lbl_800FF544(HSD_GObj*);
void lbl_800FF7A8(HSD_GObj*);
void lbl_800FF1F4(HSD_GObj*);
void lbl_800FF458(HSD_GObj*);
void lbl_800FF5A4(HSD_GObj*);
void lbl_800FF814(HSD_GObj*);
void lbl_800FF1F4(HSD_GObj*);
void lbl_800FF458(HSD_GObj*);
void lbl_800FF5A4(HSD_GObj*);
void lbl_800FF814(HSD_GObj*);
void lbl_800FF328(HSD_GObj*);
void lbl_800FF4C8(HSD_GObj*);
void lbl_800FF604(HSD_GObj*);
void lbl_800FF880(HSD_GObj*);
void lbl_800FA9FC(HSD_GObj*);
void lbl_800FACAC(HSD_GObj*);
void lbl_800FAF74(HSD_GObj*);
void lbl_800FB034(HSD_GObj*);
void func_800FAA74(HSD_GObj*);
void lbl_800FACB0(HSD_GObj*);
void lbl_800FAF94(HSD_GObj*);
void lbl_800FB0C4(HSD_GObj*);
void lbl_800FAB18(HSD_GObj*);
void lbl_800FAE0C(HSD_GObj*);
void lbl_800FAFB4(HSD_GObj*);
void lbl_800FB154(HSD_GObj*);
void lbl_800FAB54(HSD_GObj*);
void lbl_800FAE10(HSD_GObj*);
void lbl_800FAFD4(HSD_GObj*);
void lbl_800FB1E4(HSD_GObj*);
void func_800FABCC(HSD_GObj*);
void func_800FAE14(HSD_GObj*);
void func_800FAFF4(HSD_GObj*);
void func_800FB274(HSD_GObj*);
void func_800FAC70(HSD_GObj*);
void func_800FAF70(HSD_GObj*);
void func_800FB014(HSD_GObj*);
void func_800FB304(HSD_GObj*);
void lbl_8010C5FC(HSD_GObj*);
void lbl_8010C774(HSD_GObj*);
void lbl_8010C77C(HSD_GObj*);
void lbl_8010C860(HSD_GObj*);
void lbl_8010CAB4(HSD_GObj*);
void lbl_8010CB7C(HSD_GObj*);
void lbl_8010CB84(HSD_GObj*);
void lbl_8010CBF4(HSD_GObj*);
void lbl_8010C6B8(HSD_GObj*);
void lbl_8010C778(HSD_GObj*);
void lbl_8010C7B0(HSD_GObj*);
void lbl_8010C89C(HSD_GObj*);
void lbl_8010CB18(HSD_GObj*);
void lbl_8010CB80(HSD_GObj*);
void lbl_8010CBA4(HSD_GObj*);
void lbl_8010CC30(HSD_GObj*);
void lbl_80108EFC(HSD_GObj*);
void lbl_80108F74(HSD_GObj*);
void lbl_80108F7C(HSD_GObj*);
void lbl_80108FBC(HSD_GObj*);
void lbl_80108F38(HSD_GObj*);
void lbl_80108F78(HSD_GObj*);
void lbl_80108F9C(HSD_GObj*);
void lbl_80109030(HSD_GObj*);
void lbl_800FFB24(HSD_GObj*);
void lbl_801003DC(HSD_GObj*);
void lbl_80100660(HSD_GObj*);
void lbl_801007A0(HSD_GObj*);
void lbl_800FFBAC(HSD_GObj*);
void lbl_801003E0(HSD_GObj*);
void lbl_80100680(HSD_GObj*);
void lbl_80100840(HSD_GObj*);
void lbl_800FFC48(HSD_GObj*);
void lbl_80100518(HSD_GObj*);
void lbl_801006A0(HSD_GObj*);
void lbl_801008E0(HSD_GObj*);
void lbl_800FFC94(HSD_GObj*);
void lbl_8010051C(HSD_GObj*);
void lbl_801006C0(HSD_GObj*);
void lbl_80100980(HSD_GObj*);
void lbl_800FFE6C(HSD_GObj*);
void lbl_80100520(HSD_GObj*);
void lbl_801006E0(HSD_GObj*);
void lbl_80100A20(HSD_GObj*);
void lbl_800FFFB8(HSD_GObj*);
void lbl_80100524(HSD_GObj*);
void lbl_80100700(HSD_GObj*);
void lbl_80100AC0(HSD_GObj*);
void lbl_80100040(HSD_GObj*);
void lbl_80100528(HSD_GObj*);
void lbl_80100720(HSD_GObj*);
void lbl_80100B60(HSD_GObj*);
void lbl_801000DC(HSD_GObj*);
void lbl_80100654(HSD_GObj*);
void lbl_80100740(HSD_GObj*);
void lbl_80100C00(HSD_GObj*);
void lbl_80100128(HSD_GObj*);
void lbl_80100658(HSD_GObj*);
void lbl_80100760(HSD_GObj*);
void lbl_80100CA0(HSD_GObj*);
void lbl_801002C8(HSD_GObj*);
void lbl_8010065C(HSD_GObj*);
void lbl_80100780(HSD_GObj*);
void lbl_80100D40(HSD_GObj*);
void lbl_80105C3C(HSD_GObj*);
void lbl_80105D64(HSD_GObj*);
void lbl_80105D6C(HSD_GObj*);
void lbl_80105E14(HSD_GObj*);
void lbl_80105CD0(HSD_GObj*);
void lbl_80105D68(HSD_GObj*);
void lbl_80105DA0(HSD_GObj*);
void lbl_80105E50(HSD_GObj*);
void lbl_8010629C(HSD_GObj*);
void lbl_8010672C(HSD_GObj*);
void lbl_801068FC(HSD_GObj*);
void lbl_801069FC(HSD_GObj*);
void lbl_80106334(HSD_GObj*);
void lbl_80106730(HSD_GObj*);
void lbl_8010691C(HSD_GObj*);
void lbl_80106A84(HSD_GObj*);
void lbl_801063E0(HSD_GObj*);
void lbl_8010680C(HSD_GObj*);
void lbl_8010693C(HSD_GObj*);
void lbl_80106B0C(HSD_GObj*);
void lbl_80106428(HSD_GObj*);
void lbl_80106810(HSD_GObj*);
void lbl_8010695C(HSD_GObj*);
void lbl_80106B84(HSD_GObj*);
void lbl_801064AC(HSD_GObj*);
void lbl_80106814(HSD_GObj*);
void lbl_8010697C(HSD_GObj*);
void lbl_80106C10(HSD_GObj*);
void lbl_80106544(HSD_GObj*);
void lbl_80106818(HSD_GObj*);
void lbl_8010699C(HSD_GObj*);
void lbl_80106C98(HSD_GObj*);
void lbl_801065F0(HSD_GObj*);
void lbl_801068F4(HSD_GObj*);
void lbl_801069BC(HSD_GObj*);
void lbl_80106D20(HSD_GObj*);
void lbl_80106670(HSD_GObj*);
void lbl_801068F8(HSD_GObj*);
void lbl_801069DC(HSD_GObj*);
void lbl_80106D5C(HSD_GObj*);
void lbl_801016CC(HSD_GObj*);
void lbl_801035C8(HSD_GObj*);
void lbl_80103D10(HSD_GObj*);
void lbl_801046A4(HSD_GObj*);
void lbl_801016CC(HSD_GObj*);
void lbl_801035C8(HSD_GObj*);
void lbl_80103D10(HSD_GObj*);
void lbl_801046A4(HSD_GObj*);
void lbl_801017B0(HSD_GObj*);
void lbl_801035CC(HSD_GObj*);
void lbl_80103D40(HSD_GObj*);
void lbl_8010475C(HSD_GObj*);
void lbl_80101960(HSD_GObj*);
void lbl_80103734(HSD_GObj*);
void lbl_80103D70(HSD_GObj*);
void lbl_80104864(HSD_GObj*);
void lbl_80101AD0(HSD_GObj*);
void lbl_8010389C(HSD_GObj*);
void lbl_80103DA0(HSD_GObj*);
void lbl_8010496C(HSD_GObj*);
void lbl_80101EA0(HSD_GObj*);
void lbl_80103A24(HSD_GObj*);
void lbl_80103FA8(HSD_GObj*);
void lbl_80104D14(HSD_GObj*);
void lbl_80102198(HSD_GObj*);
void lbl_80103A28(HSD_GObj*);
void lbl_801042AC(HSD_GObj*);
void lbl_80104DF8(HSD_GObj*);
void lbl_80102198(HSD_GObj*);
void lbl_80103A28(HSD_GObj*);
void lbl_801042AC(HSD_GObj*);
void lbl_80104DF8(HSD_GObj*);
void lbl_80102470(HSD_GObj*);
void lbl_80103A2C(HSD_GObj*);
void lbl_801042E8(HSD_GObj*);
void lbl_80104E58(HSD_GObj*);
void lbl_80102470(HSD_GObj*);
void lbl_80103A2C(HSD_GObj*);
void lbl_801042E8(HSD_GObj*);
void lbl_80104E58(HSD_GObj*);
void lbl_8010254C(HSD_GObj*);
void lbl_80103A30(HSD_GObj*);
void lbl_80104318(HSD_GObj*);
void lbl_80104F10(HSD_GObj*);
void lbl_801026FC(HSD_GObj*);
void lbl_80103B98(HSD_GObj*);
void lbl_80104348(HSD_GObj*);
void lbl_80105018(HSD_GObj*);
void lbl_8010286C(HSD_GObj*);
void lbl_80103D00(HSD_GObj*);
void lbl_80104378(HSD_GObj*);
void lbl_80105120(HSD_GObj*);
void lbl_80102DD0(HSD_GObj*);
void lbl_80103D04(HSD_GObj*);
void lbl_801044F8(HSD_GObj*);
void lbl_801056FC(HSD_GObj*);
void lbl_80103088(HSD_GObj*);
void lbl_80103D08(HSD_GObj*);
void lbl_80104610(HSD_GObj*);
void lbl_801057BC(HSD_GObj*);
void lbl_80103088(HSD_GObj*);
void lbl_80103D08(HSD_GObj*);
void lbl_80104610(HSD_GObj*);
void lbl_801057BC(HSD_GObj*);
void lbl_80103374(HSD_GObj*);
void lbl_80103D0C(HSD_GObj*);
void lbl_80104640(HSD_GObj*);
void lbl_8010581C(HSD_GObj*);
void func_8010B65C(HSD_GObj*);
void lbl_8010B72C(HSD_GObj*);
void lbl_8010B734(HSD_GObj*);
void lbl_8010B7F0(HSD_GObj*);
void lbl_8010B958(HSD_GObj*);
void lbl_8010BA28(HSD_GObj*);
void lbl_8010BA98(HSD_GObj*);
void lbl_8010BAD8(HSD_GObj*);
void func_8010BCE0(HSD_GObj*);
void lbl_8010BED0(HSD_GObj*);
void lbl_8010BED8(HSD_GObj*);
void lbl_8010BF18(HSD_GObj*);
void func_8010BCE0(HSD_GObj*);
void lbl_8010BED0(HSD_GObj*);
void lbl_8010BED8(HSD_GObj*);
void lbl_8010BF18(HSD_GObj*);
void lbl_8010B6C4(HSD_GObj*);
void lbl_8010B730(HSD_GObj*);
void lbl_8010B78C(HSD_GObj*);
void lbl_8010B82C(HSD_GObj*);
void lbl_8010B9C0(HSD_GObj*);
void lbl_8010BA60(HSD_GObj*);
void lbl_8010BAB8(HSD_GObj*);
void lbl_8010BB14(HSD_GObj*);
void lbl_8010BDD8(HSD_GObj*);
void func_8010BED4(HSD_GObj*);
void func_8010BEF8(HSD_GObj*);
void lbl_8010BF54(HSD_GObj*);
void lbl_8010BDD8(HSD_GObj*);
void func_8010BED4(HSD_GObj*);
void func_8010BEF8(HSD_GObj*);
void lbl_8010BF54(HSD_GObj*);
void lbl_80107700(HSD_GObj*);
void lbl_80108040(HSD_GObj*);
void lbl_80108658(HSD_GObj*);
void lbl_80108798(HSD_GObj*);
void lbl_80107884(HSD_GObj*);
void lbl_80108044(HSD_GObj*);
void lbl_80108678(HSD_GObj*);
void lbl_80108820(HSD_GObj*);
void lbl_80107A84(HSD_GObj*);
void lbl_801081F8(HSD_GObj*);
void lbl_80108698(HSD_GObj*);
void lbl_801088A8(HSD_GObj*);
void lbl_80107AB4(HSD_GObj*);
void lbl_80108394(HSD_GObj*);
void lbl_801086B8(HSD_GObj*);
void lbl_80108930(HSD_GObj*);
void lbl_80107B38(HSD_GObj*);
void lbl_80108398(HSD_GObj*);
void lbl_801086D8(HSD_GObj*);
void lbl_801089B8(HSD_GObj*);
void lbl_80107B7C(HSD_GObj*);
void lbl_8010839C(HSD_GObj*);
void lbl_801086F8(HSD_GObj*);
void lbl_80108A40(HSD_GObj*);
void lbl_80107D0C(HSD_GObj*);
void lbl_801083A0(HSD_GObj*);
void lbl_80108718(HSD_GObj*);
void lbl_80108AC8(HSD_GObj*);
void lbl_80107F0C(HSD_GObj*);
void lbl_80108504(HSD_GObj*);
void lbl_80108738(HSD_GObj*);
void lbl_80108B50(HSD_GObj*);
void lbl_80107F3C(HSD_GObj*);
void lbl_80108650(HSD_GObj*);
void lbl_80108758(HSD_GObj*);
void lbl_80108BD8(HSD_GObj*);
void lbl_80107FC0(HSD_GObj*);
void lbl_80108654(HSD_GObj*);
void lbl_80108778(HSD_GObj*);
void lbl_80108C60(HSD_GObj*);
void lbl_8010D280(HSD_GObj*);
void lbl_8010D3C0(HSD_GObj*);
void lbl_8010D4C8(HSD_GObj*);
void lbl_8010D508(HSD_GObj*);
void lbl_8010D320(HSD_GObj*);
void lbl_8010D444(HSD_GObj*);
void lbl_8010D4E8(HSD_GObj*);
void lbl_8010D544(HSD_GObj*);
void lbl_800F9198(HSD_GObj*);
void lbl_800F91D4(HSD_GObj*);
void lbl_800F9204(HSD_GObj*);
void lbl_800F9224(HSD_GObj*);
void lbl_800F9454(HSD_GObj*);
void lbl_800F9490(HSD_GObj*);
void lbl_800F94C0(HSD_GObj*);
void lbl_800F94E0(HSD_GObj*);
void lbl_800FBBC4(HSD_GObj*);
void lbl_800FC374(HSD_GObj*);
void lbl_800FC70C(HSD_GObj*);
void lbl_800FC7CC(HSD_GObj*);
void lbl_800FBDFC(HSD_GObj*);
void lbl_800FC46C(HSD_GObj*);
void lbl_800FC72C(HSD_GObj*);
void lbl_800FC880(HSD_GObj*);
void lbl_800FBED0(HSD_GObj*);
void lbl_800FC53C(HSD_GObj*);
void lbl_800FC74C(HSD_GObj*);
void lbl_800FC934(HSD_GObj*);
void lbl_800FBF34(HSD_GObj*);
void lbl_800FC540(HSD_GObj*);
void lbl_800FC76C(HSD_GObj*);
void lbl_800FC9F0(HSD_GObj*);
void lbl_800FC1A0(HSD_GObj*);
void lbl_800FC638(HSD_GObj*);
void lbl_800FC78C(HSD_GObj*);
void lbl_800FCAA4(HSD_GObj*);
void lbl_800FC274(HSD_GObj*);
void lbl_800FC708(HSD_GObj*);
void lbl_800FC7AC(HSD_GObj*);
void lbl_800FCB58(HSD_GObj*);
void lbl_800FE360(HSD_GObj*);
void lbl_800FEA50(HSD_GObj*);
void lbl_800FEAF8(HSD_GObj*);
void lbl_800FEBB8(HSD_GObj*);
void lbl_800FE450(HSD_GObj*);
void lbl_800FEA78(HSD_GObj*);
void lbl_800FEB18(HSD_GObj*);
void lbl_800FEBD8(HSD_GObj*);
void lbl_800FE5C8(HSD_GObj*);
void lbl_800FEAA0(HSD_GObj*);
void func_800FEB38(HSD_GObj*);
void lbl_800FEBF8(HSD_GObj*);
void lbl_800FE688(HSD_GObj*);
void lbl_800FEAA4(HSD_GObj*);
void lbl_800FEB58(HSD_GObj*);
void lbl_800FEC18(HSD_GObj*);
void lbl_800FE778(HSD_GObj*);
void lbl_800FEACC(HSD_GObj*);
void lbl_800FEB78(HSD_GObj*);
void lbl_800FEC38(HSD_GObj*);
void func_800FE928(HSD_GObj*);
void lbl_800FEAF4(HSD_GObj*);
void lbl_800FEB98(HSD_GObj*);
void lbl_800FEC58(HSD_GObj*);
void lbl_800FA0F4(HSD_GObj*);
void lbl_800FA418(HSD_GObj*);
void lbl_800FA420(HSD_GObj*);
void lbl_800FA460(HSD_GObj*);
void func_800FA254(HSD_GObj*);
void lbl_800FA41C(HSD_GObj*);
void lbl_800FA440(HSD_GObj*);
void lbl_800FA4F0(HSD_GObj*);
void lbl_800F9AEC(HSD_GObj*);
void lbl_800F9B64(HSD_GObj*);
void lbl_800F9C58(HSD_GObj*);
void lbl_800F9E8C(HSD_GObj*);
void lbl_800F9B28(HSD_GObj*);
void lbl_800F9B68(HSD_GObj*);
void lbl_800F9D40(HSD_GObj*);
void lbl_800F9F34(HSD_GObj*);
void func_8010B65C(HSD_GObj*);
void lbl_8010B72C(HSD_GObj*);
void lbl_8010B734(HSD_GObj*);
void lbl_8010B7F0(HSD_GObj*);
void lbl_8010B958(HSD_GObj*);
void lbl_8010BA28(HSD_GObj*);
void lbl_8010BA98(HSD_GObj*);
void lbl_8010BAD8(HSD_GObj*);
void func_8010BCE0(HSD_GObj*);
void lbl_8010BED0(HSD_GObj*);
void lbl_8010BED8(HSD_GObj*);
void lbl_8010BF18(HSD_GObj*);
void func_8010BCE0(HSD_GObj*);
void lbl_8010BED0(HSD_GObj*);
void lbl_8010BED8(HSD_GObj*);
void lbl_8010BF18(HSD_GObj*);
void lbl_8010B6C4(HSD_GObj*);
void lbl_8010B730(HSD_GObj*);
void lbl_8010B78C(HSD_GObj*);
void lbl_8010B82C(HSD_GObj*);
void lbl_8010B9C0(HSD_GObj*);
void lbl_8010BA60(HSD_GObj*);
void lbl_8010BAB8(HSD_GObj*);
void lbl_8010BB14(HSD_GObj*);
void lbl_8010BDD8(HSD_GObj*);
void func_8010BED4(HSD_GObj*);
void func_8010BEF8(HSD_GObj*);
void lbl_8010BF54(HSD_GObj*);
void lbl_8010BDD8(HSD_GObj*);
void func_8010BED4(HSD_GObj*);
void func_8010BEF8(HSD_GObj*);
void lbl_8010BF54(HSD_GObj*);
void lbl_800FA9FC(HSD_GObj*);
void lbl_800FACAC(HSD_GObj*);
void lbl_800FAF74(HSD_GObj*);
void lbl_800FB034(HSD_GObj*);
void func_800FAA74(HSD_GObj*);
void lbl_800FACB0(HSD_GObj*);
void lbl_800FAF94(HSD_GObj*);
void lbl_800FB0C4(HSD_GObj*);
void lbl_800FAB18(HSD_GObj*);
void lbl_800FAE0C(HSD_GObj*);
void lbl_800FAFB4(HSD_GObj*);
void lbl_800FB154(HSD_GObj*);
void lbl_800FAB54(HSD_GObj*);
void lbl_800FAE10(HSD_GObj*);
void lbl_800FAFD4(HSD_GObj*);
void lbl_800FB1E4(HSD_GObj*);
void func_800FABCC(HSD_GObj*);
void func_800FAE14(HSD_GObj*);
void func_800FAFF4(HSD_GObj*);
void func_800FB274(HSD_GObj*);
void func_800FAC70(HSD_GObj*);
void func_800FAF70(HSD_GObj*);
void func_800FB014(HSD_GObj*);
void func_800FB304(HSD_GObj*);
void func_800EFA40(HSD_GObj*);
void lbl_800EFAF0(HSD_GObj*);
void lbl_800EFB4C(HSD_GObj*);
void lbl_800EFBFC(HSD_GObj*);
void lbl_800EFC58(HSD_GObj*);
void lbl_800EFD08(HSD_GObj*);
void lbl_800F0FC0(HSD_GObj*);
void lbl_800F10A4(HSD_GObj*);
void lbl_800EFD64(HSD_GObj*);
void lbl_800EFE1C(HSD_GObj*);
void lbl_800EFE80(HSD_GObj*);
void lbl_800EFF38(HSD_GObj*);
void lbl_800EFF9C(HSD_GObj*);
void lbl_800F0054(HSD_GObj*);
void lbl_800F00B8(HSD_GObj*);
void lbl_800F0168(HSD_GObj*);
void lbl_800F01C4(HSD_GObj*);
void lbl_800F0274(HSD_GObj*);
void lbl_800F02D0(HSD_GObj*);
void lbl_800F0380(HSD_GObj*);
void lbl_800F03DC(HSD_GObj*);
void lbl_800F0494(HSD_GObj*);
void lbl_800F04F8(HSD_GObj*);
void lbl_800F05A8(HSD_GObj*);
void lbl_800F0604(HSD_GObj*);
void lbl_800F06B4(HSD_GObj*);
void lbl_800F10D4(HSD_GObj*);
void lbl_800F11AC(HSD_GObj*);
void lbl_800F11F0(HSD_GObj*);
void lbl_800F12C8(HSD_GObj*);
void lbl_800F0710(HSD_GObj*);
void lbl_800F07C0(HSD_GObj*);
void lbl_800F081C(HSD_GObj*);
void lbl_800F08D4(HSD_GObj*);
void lbl_800F0938(HSD_GObj*);
void lbl_800F09F0(HSD_GObj*);
void lbl_800F0A54(HSD_GObj*);
void lbl_800F0B0C(HSD_GObj*);
void lbl_800F0B70(HSD_GObj*);
void lbl_800F0C20(HSD_GObj*);
void lbl_800F130C(HSD_GObj*);
void lbl_800F13F0(HSD_GObj*);
void lbl_800F0C7C(HSD_GObj*);
void lbl_800F0D34(HSD_GObj*);
void lbl_800F14B4(HSD_GObj*);
void lbl_800F15D8(HSD_GObj*);
void lbl_800F0D98(HSD_GObj*);
void lbl_800F0E48(HSD_GObj*);
void lbl_800F0EA4(HSD_GObj*);
void lbl_800F0F5C(HSD_GObj*);
void lbl_800EFD64(HSD_GObj*);
void lbl_800EFE1C(HSD_GObj*);
void lbl_800F9110(HSD_GObj*);
void lbl_800FE100(HSD_GObj*);
void lbl_800F99BC(HSD_GObj*);
void lbl_800FF8EC(HSD_GObj*);
void func_800F5F68(HSD_GObj*);
void lbl_800FA8B4(HSD_GObj*);
void lbl_800FB880(HSD_GObj*);
void lbl_8010612C(HSD_GObj*);
void lbl_800FED38(HSD_GObj*);
void lbl_8010C4D4(HSD_GObj*);
void lbl_80108D64(HSD_GObj*);
void lbl_800F9FD4(HSD_GObj*);
void lbl_800FCF74(HSD_GObj*);
void lbl_8010941C(HSD_GObj*);
void lbl_80101560(HSD_GObj*);
void lbl_80107568(HSD_GObj*);
void lbl_800F9614(HSD_GObj*);
void lbl_8010B2FC(HSD_GObj*);
void lbl_80105B2C(HSD_GObj*);
void lbl_800FB880(HSD_GObj*);
void lbl_800F9110(HSD_GObj*);
void lbl_800FE100(HSD_GObj*);
void lbl_800F9FD4(HSD_GObj*);
void lbl_8010D188(HSD_GObj*);
void lbl_800F99BC(HSD_GObj*);
void lbl_8010B2FC(HSD_GObj*);
void lbl_800FA8B4(HSD_GObj*);
void lbl_800F93CC(HSD_GObj*);
void lbl_800FE240(HSD_GObj*);
void lbl_800F9A54(HSD_GObj*);
void lbl_800FFA10(HSD_GObj*);
void func_800F6070(HSD_GObj*);
void lbl_800FA958(HSD_GObj*);
void lbl_800FBA00(HSD_GObj*);
void lbl_801061E4(HSD_GObj*);
void lbl_800FEDD0(HSD_GObj*);
void lbl_8010C560(HSD_GObj*);
void lbl_80108E14(HSD_GObj*);
void lbl_800FA064(HSD_GObj*);
void lbl_800FD020(HSD_GObj*);
void lbl_801094FC(HSD_GObj*);
void lbl_80101618(HSD_GObj*);
void lbl_80107638(HSD_GObj*);
void lbl_800F9684(HSD_GObj*);
void lbl_8010B4A0(HSD_GObj*);
void lbl_80105BA8(HSD_GObj*);
void lbl_800FBA00(HSD_GObj*);
void lbl_800F93CC(HSD_GObj*);
void lbl_800FE240(HSD_GObj*);
void lbl_800FA064(HSD_GObj*);
void lbl_8010D204(HSD_GObj*);
void lbl_800F9A54(HSD_GObj*);
void lbl_8010B4A0(HSD_GObj*);
void lbl_800FA958(HSD_GObj*);
/* static */ s32 func_800F1BAC(HSD_GObj* gobj, s32, bool);
/* static */ void func_800F5524(HSD_GObj* gobj);
/* static */ void func_800F22D4(HSD_GObj* gobj);
/* static */ void func_800F5318(HSD_GObj* gobj);
/* static */ void func_800F9090(HSD_GObj* gobj);
/* static */ void func_800F19AC(HSD_GObj* gobj);
/* static */ void func_800F1A8C(HSD_GObj* gobj);
void func_800EE818(HSD_GObj* gobj);
void ftKirby_SpecialS_StartMotion(HSD_GObj*);
void ftKirby_SpecialAirHi_StartMotion(HSD_GObj*);
void ftKirby_SpecialAirLw_StartMotion(HSD_GObj*);
void ftKirby_SpecialAirS_StartMotion(HSD_GObj*);
void ftKirby_SpecialAirS_StartMotion(HSD_GObj*);
void ftKirby_SpecialAirN_StartMotion(HSD_GObj*);
void ftKirby_SpecialN_StartMotion(HSD_GObj*);
void ftKirby_SpecialLw_StartMotion(HSD_GObj*);
void ftKirby_SpecialHi_StartMotion(HSD_GObj*);
void ftKirby_OnItemInvisible(HSD_GObj*);
void ftKirby_OnItemVisible(HSD_GObj*);
void ftKirby_OnItemDrop(HSD_GObj*, bool);
void ftKirby_OnKnockbackEnter(HSD_GObj*);
void ftKirby_OnKnockbackExit(HSD_GObj*);
void func_800F1B6C(HSD_GObj*);
void ftKirby_LoadSpecialAttrs(HSD_GObj*);
void func_800EEE9C(HSD_GObj*);
void func_800EEF04(HSD_GObj*, int, Mtx);
void func_800EF87C(Fighter*, int, bool);
unk_t func_800EF028(HSD_GObj*);
void func_800EF9BC(HSD_GObj*);
void func_800EF9FC(HSD_GObj*);
char* ftKirby_GetMotionFileString(enum_t);
void func_800EEBC0(s32, s32*, s32*);
void func_8010AA1C(HSD_GObj*);
void func_8010AA20(HSD_GObj*);
void func_8010AA24(HSD_GObj*);
void func_8010AA28(HSD_GObj*);
void func_8010AF54(HSD_GObj*);
void func_8010B0A0(HSD_GObj*);
void func_8010B0A4(HSD_GObj*);
void func_8010B0DC(HSD_GObj*);

#endif
