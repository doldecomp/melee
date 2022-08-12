#include <sysdolphin/baselib/__baselib.h>
#include <sysdolphin/baselib/psdisp.h>

#include <dolphin/gx/GXAttr.h>
#include <dolphin/gx/GXLight.h>
#include <dolphin/gx/GXMisc.h>
#include <dolphin/gx/GX.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/util.h>
#include <melee/lb/lbrefract.h>
#include <sysdolphin/baselib/state.h>
#include <sysdolphin/baselib/mtx.h>

typedef struct
{
    u8 filename[9];
    u8 message[39];
    unk_t pointers[3];
    u32 bitfields[8];
} psdisp_UnknownType001;

typedef struct
{
    unk_t pointers[4];
    u8 message[36];
    u8 filename[9];
} psdisp_UnknownType002;

/* 004D4528 */ extern s32 lbl_804D7948;
/* 004D4524 */ extern unk_t lbl_804D7944;
/* 004D4520 */ extern unk_t lbl_804D7940;
/* 004D451C */ extern unk_t lbl_804D793C;
/* 004D4518 */ extern unk_t lbl_804D7938;
/* 004D4514 */ extern unk_t lbl_804D7934;
/* 004D4510 */ extern s32 lbl_804D7930;
/* 004D450C */ extern s32 lbl_804D792C;
/* 004D4508 */ extern f32 lbl_804D7928;
/* 004D4504 */ extern f32 lbl_804D7924;
/* 004D4500 */ extern f32 lbl_804D7920;
/* 004D44FC */ extern f32 lbl_804D791C;
/* 004D44F8 */ extern f32 lbl_804D7918;
/* 004D44F4 */ extern f32 lbl_804D7914;
/* 004D44F0 */ extern s32 lbl_804D7910;
/* 004D44EC */ extern s32 lbl_804D790C;
/* 004D44E8 */ extern s32 lbl_804D7908;
/* 004D2F64 */ extern u8 lbl_804D6384[2];
/* 004D2F60 */ extern u8 lbl_804D6380[2];
/* 00408F40 */ extern psdisp_UnknownType002 lbl_8040C360;
/* 00408EE0 */ extern psdisp_UnknownType001 lbl_8040C300;
/* 003B6208 */ extern f32 lbl_803B9628[12];
/* 0039CC68 */ void psDispParticles(s32, u32);
/* 0039C850 */ unk_t func_8039FC70(s32, u8, unk_t *, unk_t *);
/* 0039C754 */ void func_8039FB74(unk_t, unk_t, unk_t);
/* 0039C608 */ void func_8039FA28(unk_t, unk_t, unk_t);
/* 0039C47C */ void func_8039F89C(unk_t, f32 *, f32 *, f32 *);
/* 0039C36C */ void func_8039F78C(s32);