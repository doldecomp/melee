#include <sysdolphin/baselib/baselib_unknown_002.h>

#include <sysdolphin/baselib/__baselib.h>
#include <sysdolphin/baselib/list.h>
#include <sysdolphin/baselib/debug.h>
#include <melee/lb/lbrefract.h>
#include <sysdolphin/baselib/psstructs.h>
#include <sysdolphin/baselib/psappsrt.h>
#include <sysdolphin/baselib/mtx.h>
#include <sysdolphin/baselib/jobj.h>
#include <dolphin/os/os.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/cobj.h>
#include <dolphin/os/OSThread.h>
#include <dolphin/pad/pad.h>
#include <dolphin/vi/vi.h>

STRUCT_PLACEHOLDER(baselib, 1)
STRUCT_PLACEHOLDER(baselib, 2)
STRUCT_PLACEHOLDER(baselib, 3)
STRUCT_PLACEHOLDER(baselib, 4)
STRUCT_PLACEHOLDER(baselib, 5)
STRUCT_PLACEHOLDER(baselib, 6)
STRUCT_PLACEHOLDER(baselib, 7)
STRUCT_PLACEHOLDER(baselib, 8)
STRUCT_PLACEHOLDER(baselib, 9)
STRUCT_PLACEHOLDER(baselib, 10)
STRUCT_PLACEHOLDER(baselib, 11)

typedef struct _baselib_Unk12
{
    u8 x0_pad[0x1000];
} baselib_Unk12;

typedef struct _baselib_Unk13
{
    u8 x0_pad[0xD8];
} baselib_Unk13;

STRUCT_PLACEHOLDER(baselib, 14)
STRUCT_PLACEHOLDER(baselib, 15)

typedef void (*baselib_UnkCallback1)(baselib_Unk14 *, s32, baselib_Unk15);

typedef struct _baselib_UnkCallbackContainer1
{
    u32 x0_flags;
    baselib_UnkCallback1 x4_callback;
    u32 x8_flags;
    baselib_UnkCallback1 xC_callback;
    u32 x10_flags;
    baselib_UnkCallback1 x14_callback;
    u32 x18_flags;
    baselib_UnkCallback1 x1C_callback;
} baselib_UnkCallbackContainer1;

typedef struct _baselib_Unk16
{
    u32 x0_data[0x1C0];
} baselib_Unk16;

/* 004D44E0 */ extern HSD_JObj *lbl_804D7900;
/* 004D44DC */ extern HSD_JObj *lbl_804D78FC;
/* 004D44D8 */ extern HSD_JObj *lbl_804D78F8;
/* 004D44D4 */ extern HSD_SList *lbl_804D78F4;
/* 004D44D0 */ extern HSD_JObj *lbl_804D78F0;
/* 004D44CC */ extern HSD_JObj *lbl_804D78EC;
/* 004D44C8 */ extern HSD_JObj *lbl_804D78E8;
/* 004D44C2 */ extern baselib_Unk2 lbl_804D78E2;
/* 004D44C0 */ extern u16 lbl_804D78E0;
/* 004D44BC */ extern s16 lbl_804D78DC;
/* 004D44BA */ extern u16 lbl_804D78DA;
/* 004D44B4 */ extern HSD_Obj *lbl_804D78D4;
/* 004D44AC */ extern u32 lbl_804D78CC;
/* 004D44A8 */ extern s32 lbl_804D78C8;
/* 004D2F48 */ extern u16 lbl_804D6368[2];
/* 004CDB70 */ extern HSD_ObjAllocData lbl_804D0F90;
/* 004CD4E8 */ extern u32 *lbl_804D0908[146];
/* 004CD4C8 */ extern HSD_Obj *lbl_804D08E8[8];
/* 004CD4C8 */ extern HSD_Obj *lbl_804D08E8[8];
/* 004CC4C8 */ extern baselib_Unk12 lbl_804CF8E8;
/* 00408B50 */ extern cobj_Unk1 lbl_8040BF70;
/* 004076E0 */ extern baselib_UnkCallbackContainer1 lbl_8040AB00;
/* 00405498 */ extern baselib_Unk16 lbl_804088B8;
/* 00405478 */ extern baselib_UnkCallbackContainer1 lbl_80408898;
/* 0039C2AC */ extern UnkGeneratorStruct *func_8039F6CC(UnkGeneratorStruct *);
/* 0039C23C */ extern unk_t lbl_8039F65C(s32);
/* 0039BC3C */ extern UnkGeneratorStruct *func_8039F05C();
/* 0039BC3C */ extern UnkGeneratorStruct *func_8039F05C(s32, s32, s32);
/* 0039BB8C */ extern UnkGeneratorStruct *func_8039EFAC(UnkGeneratorStruct *);
/* 0039A6B4 */ extern f32 func_8039DAD4(unk_t);
/* 0039A5A8 */ extern UnkGeneratorStruct *func_8039D9C8();
/* 0039A2FC */ extern void func_8039D71C(unk_t);
/* 0039A2FC */ extern void func_8039D71C(unk_t);
/* 0039A268 */ extern void lbl_8039D688(u32);
/* 0039A1BC */ extern void func_8039D5DC(unk_t);
/* 0039A160 */ extern void func_8039D580(u32);
/* 0039A0BC */ extern void func_8039D4DC(HSD_JObj *);
/* 00399F8C */ extern HSD_JObj *func_8039D3AC(HSD_JObj *, HSD_JObj *);
/* 00399F34 */ extern void func_8039D354();
/* 00399DF4 */ extern void func_8039D214(HSD_JObj *);
/* 00399DCC */ extern u16 func_8039D1EC();
/* 00399DC4 */ extern void func_8039D1E4(baselib_Unk3 *, s32);
/* 00399C80 */ extern void func_8039D0A0(baselib_Unk4);
/* 00399C28 */ extern void func_8039D048(HSD_JObj *);
/* 00399B2C */ extern void func_8039CF4C(s32, HSD_Obj *);
/* 00399A8C */ extern void func_8039CEAC(u32);
/* 00395EEC */ extern u32 *func_8039930C(u32 *, u32 *);
/* 00395DB8 */ extern BOOL func_803991D8(HSD_JObj *, HSD_JObj *, f32, f32);
/* 00395B6C */ extern void func_80398F8C(HSD_JObj *, f32);
/* 00395AEC */ extern void func_80398F0C(s32, s32, f32, s32, s32, s32, s32, s32);
/* 003957E4 */ extern void func_80398C04(BOOL, s32, s32, s32, s32, s32, s32, s32);
/* 003955E8 */ extern void func_80398A08();
/* 003951F4 */ extern void func_80398614(baselib_Unk5 *, s32 *, u32, s32, baselib_Unk6 *);
/* 003950D4 */ extern void func_803984F4(s32, baselib_Unk8 *, baselib_Unk9 *, s32, baselib_Unk10 *);
/* 00394F84 */ extern void func_803983A4(HSD_JObj *);
/* 00394F84 */ extern void func_803983A4(HSD_JObj *);
/* 00394EF0 */ extern HSD_GObj *func_80398310(s32, s32, s32, u32);
/* 00394EC4 */ extern void lbl_803982E4(HSD_GObj *, s32);
/* 003949EC */ extern u32 baselib_mfspr(register u32 reg);
/* 003949D4 */ extern void Exception_StoreDebugLevel(s32);
/* 00394984 */ extern void func_80397DA4(OSThread_Unk1 *);
/* 00394984 */ extern void func_80397DA4(OSThread_Unk1 *);
/* 003943F4 */ extern OSThread_Unk3 lbl_80397814(OSThread_Unk4 *);
/* 003941B4 */ extern void func_803975D4();
/* 00394100 */ extern void func_80397520();
/* 00391248 */ extern void func_80394668(s32, s32);
/* 00391124 */ extern void func_80394544(s32, s32, s32, s32, s32, s32, s32, s32);
/* 00390EF4 */ extern void func_80394314();
/* 0039090C */ extern void func_80393D2C(BOOL, baselib_Unk13 *, baselib_UnkCallbackContainer1 *);
/* 0038F61C */ extern baselib_Unk11 lbl_80392A3C;
/* 0038F5E8 */ extern void func_80392A08(u32, BOOL, BOOL);
/* 0038F514 */ extern void func_80392934();
/* 0038F12C */ extern void func_8039254C();
/* 0038F108 */ extern void func_80392528(baselib_Unk11 *);
/* 0038ED74 */ extern void func_80392194(baselib_Unk14 *, s32, baselib_Unk15 *);
