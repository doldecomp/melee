#ifndef GALE01_1F423C
#define GALE01_1F423C

#include <Runtime/platform.h>

#include <melee/gr/forward.h>
#include <melee/lb/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>

/* 1F423C */ void grGreatBay_801F423C(bool);
/* 1F4240 */ void grGreatBay_801F4240(void);
/* 1F42D0 */ void grGreatBay_801F42D0(void);
/* 1F42D4 */ void grGreatBay_801F42D4(void);
/* 1F42F8 */ bool grGreatBay_801F42F8(void);
/* 1F4300 */ HSD_GObj* grGreatBay_801F4300(int);
/* 1F4430 */ bool grGreatBay_801F4430(Ground_GObj*);
/* 1F4438 */ void grGreatBay_801F4438(Ground_GObj*);
/* 1F443C */ void grGreatBay_801F443C(Ground_GObj*);
/* 1F4440 */ void grGreatBay_801F4440(Ground_GObj*);
/* 1F44A0 */ bool grGreatBay_801F44A0(Ground_GObj*);
/* 1F44A8 */ void grGreatBay_801F44A8(Ground_GObj*);
/* 1F44AC */ void grGreatBay_801F44AC(Ground_GObj*);
/* 1F44B0 */ void grGreatBay_801F44B0(Ground_GObj*);
/* 1F4510 */ bool grGreatBay_801F4510(Ground_GObj*);
/* 1F4518 */ void grGreatBay_801F4518(Ground_GObj*);
/* 1F451C */ void grGreatBay_801F451C(Ground_GObj*);
/* 1F4520 */ void fn_801F4520(HSD_GObj*);
/* 1F454C */ void grGreatBay_801F454C(Ground_GObj*);
/* 1F4650 */ bool grGreatBay_801F4650(Ground_GObj*);
/* 1F4658 */ void grGreatBay_801F4658(Ground_GObj*);
/* 1F4690 */ void grGreatBay_801F4690(Ground_GObj*);
/* 1F4694 */ void grGreatBay_801F4694(Ground_GObj*);
/* 1F4994 */ bool grGreatBay_801F4994(Ground_GObj*);
/* 1F499C */ void grGreatBay_801F499C(Ground_GObj*);
/* 1F545C */ void grGreatBay_801F545C(Ground_GObj*);
/* 1F5460 */ void grGreatBay_801F5460(Ground_GObj*);
/* 1F55F8 */ bool grGreatBay_801F55F8(Ground_GObj*);
/* 1F5600 */ void grGreatBay_801F5600(Ground_GObj*);
/* 1F5988 */ void grGreatBay_801F5988(Ground_GObj*);
/* 1F598C */ void grGreatBay_801F598C(Ground_GObj*);
/* 1F59F0 */ bool grGreatBay_801F59F0(Ground_GObj*);
/* 1F59F8 */ void grGreatBay_801F59F8(Ground_GObj*);
/* 1F59FC */ void grGreatBay_801F59FC(Ground_GObj*);
/* 1F5A00 */ void grGreatBay_801F5A00(Ground_GObj*);
/* 1F5AF0 */ bool grGreatBay_801F5AF0(Ground_GObj*);
/* 1F5AF8 */ void grGreatBay_801F5AF8(Ground_GObj*);
/* 1F5D48 */ void grGreatBay_801F5D48(Ground_GObj*);
/* 1F5D4C */ void grGreatBay_801F5D4C(HSD_GObj*);
/* 1F5E28 */ void grGreatBay_801F5E28(HSD_GObj*);
/* 1F62F8 */ s32 grGreatBay_801F62F8(s32);
/* 1F63F4 */ bool grGreatBay_801F63F4(Ground_GObj*);
/* 1F660C */ void grGreatBay_801F660C(Ground_GObj*);
/* 1F66A4 */ bool grGreatBay_801F66A4(void);
/* 1F6708 */ bool grGreatBay_801F6708(u32, HSD_GObj*);
/* 1F67A4 */ void grGreatBay_801F67A4(Vec3*, f32);
/* 1F680C */ lbColl_80008D30_arg1* grGreatBay_801F680C(enum_t);
/* 1F6814 */ bool grGreatBay_801F6814(Vec3*, int _, HSD_JObj*);
/* 3E3F6C */ extern StageData grGb_StageData;

typedef struct grGreatBay_YakumonoParam {
    /* 0x00 */ s16 moon_fall_wait_a;
    /* 0x02 */ s16 moon_fall_wait_b;
    /* 0x04 */ f32 floatfloor_landing_rate;
    /* 0x08 */ f32 floatfloor_slant_mul;
    /* 0x0C */ f32 floatfloor_slant_add;
    /* 0x10 */ f32 floatfloor_slant_limit;
    /* 0x14 */ f32 floatfloor_slant_rate;
    /* 0x18 */ f32 floatfloor_slant_reb_rate;
    /* 0x1C */ f32 floatfloor_slide_mul;
    /* 0x20 */ f32 floatfloor_slide_add;
    /* 0x24 */ f32 floatfloor_slide_limit;
    /* 0x28 */ f32 floatfloor_slide_rate;
    /* 0x2C */ f32 floatfloor_slide_reb_rate;
    /* 0x30 */ f32 floatfloor_down_mul;
    /* 0x34 */ f32 floatfloor_down_add;
    /* 0x38 */ f32 floatfloor_down_limit;
    /* 0x3C */ f32 floatfloor_down_up_rate;
    /* 0x40 */ f32 floatfloor_down_down_rate;
    /* 0x44 */ s16 kame_wait_frame_a;
    /* 0x46 */ s16 kame_wait_frame_b;
    /* 0x48 */ s16 kame_rebirth_frame_a;
    /* 0x4A */ s16 kame_rebirth_frame_b;
    /* 0x4C */ f32 kame_x;
    /* 0x50 */ f32 kame_y;
    /* 0x54 */ f32 kame_x_offset_init;
    /* 0x58 */ f32 kame_x_lr_offset_a;
    /* 0x5C */ f32 kame_x_lr_offset_b;
    /* 0x60 */ f32 kame_x_fb_offset_a;
    /* 0x64 */ f32 kame_x_fb_offset_b;
    /* 0x68 */ f32 kame_scale;
    /* 0x6C */ f32 kame_ud_scale;
    /* 0x70 */ s16 kame_dir_prob[4];
    /* 0x78 */ f32 kame_item_prob;
    /* 0x7C */ struct grGreatBay_YakumonoParam_Item {
        s16 kind;
        s16 weight;
    } items[10];
} grGreatBay_YakumonoParam;

#endif
