#include "gm_18A5.h"

#include "gm_18A5.static.h"

#include "ft/forward.h"

#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/particle.h>
#include <sysdolphin/baselib/random.h>
#include <melee/gm/gm_1601.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmtou.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/lblanguage.h>
#include <melee/mn/mnmain.h>
#include <melee/mn/mnmainrule.h>
#include <melee/mn/mnname.h>
#include <melee/mn/mnnamenew.h>
#include <melee/mn/mnstagesel.h>
#include <melee/pl/player.h>

extern char* lbl_804DA6C4;
extern char* lbl_804DA6C8;
extern char* lbl_804DA6CC;
extern char* lbl_804DA6D0;

typedef void (*lbl_803D9FD8_fn)(s32*, u32, u32);

lbl_803D9FD8_fn lbl_803D9FD8[] = {
    fn_801937C4, fn_80193B58, fn_80193FCC, fn_80194658, fn_801949B4,
    fn_80194BC4, fn_80194D84, fn_80194D84, fn_80194D84, NULL,
    fn_80194F30, fn_801953C8, fn_80194F30, fn_80195AF0, fn_80195AF0,
    fn_80195CCC, fn_80194F30, fn_8019610C, fn_8019610C,
};

/// #fn_8018A514

void fn_8018A970(int arg0)
{
    int i;
    for (i = 0; i < 0x40; i++) {
        if (lbl_80473AB8[i].x0 != 0) {
            HSD_GObj* gobj = GObj_Create(0xE, 0x1B, 0);
            gobj->user_data = &lbl_80473AB8[i];
            if (i == 0) {
                HSD_GObjProc_8038FD54(gobj, fn_8018B090, 0);
            }
            GObj_SetupGXLink(gobj, fn_8018E46C, 4, 1);
        }
    }

    if (arg0 < 9) {
        if (arg0 == 1) {
            lbl_80473AB8[5].x5E = 1;
        } else if (arg0 == 3) {
            lbl_80473AB8[10].x32 = 1;
            lbl_80473AB8[11].x5E = 1;
        } else if (arg0 == 5) {
            lbl_80473AB8[23].x5E = 1;
        } else if (arg0 == 7) {
            lbl_80473AB8[46].x5E = 1;
            lbl_80473AB8[47].x5E = 1;
        }
    }
}

/// #fn_8018AA74

/// #fn_8018B090

static s32 lbl_804DA67C = (s32) 0xFFFF00FF;

/// Draws tournament bracket lines for different bracket types (0-3).
void fn_8018C8D4(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                 s32 arg5, s32 arg6, f32 farg0)
{
    u8* data = (u8*) arg0;
    f32 thickness;
    f32 neg_thickness;
    f32 total_width;
    s32 half, center, right;
    s32 half_h, third_h;
    s32 mid_y, bot_y, two_third_y;
    s32 c0, c1, c2, c3, c4, c5, c6, c7, c8, c9;
    s32 c10, c11, c12, c13, c14, c15, c16, c17, c18, c19;
    s32 c20, c21, c22, c23, c24, c25, c26, c27, c28, c29;
    s32 c30, c31, c32, c33;

    c0 = lbl_804DA67C;
    thickness = M2C_FIELD(data, f32*, 0x1C);

    switch ((s32) data[4]) {
    case 0:
        c1 = c0;
        DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) arg4,
                      (GXColor*) &c1);
        if (data[0x21] == 0) {
            c2 = M2C_FIELD(data, s32*, 0x20);
            DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) arg4,
                          (GXColor*) &c2);
        }
        return;

    case 1:
        c3 = c0;
        DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) arg4,
                      (GXColor*) &c3);
        if (data[0x21] == 0) {
            if (data[0x4C] == 0) {
                half_h = arg4 / 2;
                c4 = M2C_FIELD(data, s32*, 0x20);
                DrawRectangle((f32) arg1, (f32) (arg2 + half_h), thickness,
                              (f32) half_h, (GXColor*) &c4);
                return;
            }
            c5 = M2C_FIELD(data, s32*, 0x20);
            DrawRectangle((f32) arg1, (f32) arg2, thickness,
                          (f32) (arg4 / 2), (GXColor*) &c5);
        }
        break;

    case 2:
        half = arg3 / 2;
        center = arg1 + half;
        half_h = arg4 / 2;
        c6 = c0;
        DrawRectangle((f32) center, (f32) arg2, thickness, (f32) half_h,
                      (GXColor*) &c6);

        neg_thickness = -thickness;
        mid_y = arg2 + half_h;
        c7 = c0;
        DrawRectangle((f32) (arg1 + 0x2B), (f32) mid_y,
                      ((f32) arg3 + thickness) - 43.0f, neg_thickness,
                      (GXColor*) &c7);

        c8 = c0;
        DrawRectangle((f32) (arg1 + 0x2B), (f32) mid_y, thickness,
                      (f32) half_h, (GXColor*) &c8);

        right = arg1 + arg3;
        c9 = c0;
        DrawRectangle((f32) right, (f32) mid_y, thickness, (f32) half_h,
                      (GXColor*) &c9);

        if (data[0x21] == 0) {
            if (data[0x4C] == 0) {
                c10 = M2C_FIELD(data, s32*, 0x20);
                DrawRectangle((f32) (arg1 + 0x2B), (f32) mid_y, thickness,
                              (f32) half_h, (GXColor*) &c10);
                c11 = M2C_FIELD(data, s32*, 0x20);
                DrawRectangle((f32) (arg1 + 0x2B), (f32) mid_y,
                              (f32) (half - 0x2B), neg_thickness,
                              (GXColor*) &c11);
                return;
            }
            if (data[0x78] == 0) {
                c12 = M2C_FIELD(data, s32*, 0x20);
                DrawRectangle((f32) right, (f32) mid_y, thickness,
                              (f32) half_h, (GXColor*) &c12);
                c13 = M2C_FIELD(data, s32*, 0x20);
                DrawRectangle((f32) center, (f32) mid_y,
                              (f32) half + thickness, neg_thickness,
                              (GXColor*) &c13);
                return;
            }
            c14 = M2C_FIELD(data, s32*, 0x20);
            DrawRectangle((f32) center, (f32) arg2, thickness, (f32) half_h,
                          (GXColor*) &c14);
        }
        break;

    case 3:
        half = arg3 / 2;
        third_h = arg4 / 3;
        center = arg1 + half;
        mid_y = arg2 + third_h;

        c15 = c0;
        DrawRectangle((f32) center, (f32) mid_y, thickness,
                      (f32) (third_h - 2), (GXColor*) &c15);

        c16 = c0;
        DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) third_h,
                      (GXColor*) &c16);

        right = arg1 + arg3;
        c17 = c0;
        DrawRectangle((f32) right, (f32) arg2, thickness, (f32) third_h,
                      (GXColor*) &c17);

        bot_y = (arg2 + arg4) - third_h;
        c18 = c0;
        DrawRectangle((f32) arg1, (f32) bot_y, thickness, (f32) third_h,
                      (GXColor*) &c18);

        c19 = c0;
        DrawRectangle((f32) right, (f32) bot_y, thickness, (f32) third_h,
                      (GXColor*) &c19);

        neg_thickness = -thickness;
        total_width = (f32) arg3 + thickness;
        c20 = c0;
        DrawRectangle((f32) arg1, (f32) mid_y, total_width, neg_thickness,
                      (GXColor*) &c20);

        c21 = c0;
        DrawRectangle((f32) arg1, (f32) bot_y, total_width, neg_thickness,
                      (GXColor*) &c21);

        if (data[0x21] == 0) {
            if (data[0x4C] == 0) {
                two_third_y = arg2 + ((arg4 * 2) / 3);
                c22 = M2C_FIELD(data, s32*, 0x20);
                DrawRectangle((f32) arg1, (f32) two_third_y, thickness,
                              (f32) third_h, (GXColor*) &c22);
                c23 = M2C_FIELD(data, s32*, 0x20);
                DrawRectangle((f32) arg1, (f32) two_third_y, (f32) half,
                              neg_thickness, (GXColor*) &c23);
                c24 = M2C_FIELD(data, s32*, 0x20);
                DrawRectangle((f32) center, (f32) (arg2 + (arg4 / 2)),
                              thickness, (f32) ((arg4 / 6) - 1),
                              (GXColor*) &c24);
                return;
            }
            if (data[0x78] == 0) {
                two_third_y = arg2 + ((arg4 * 2) / 3);
                c25 = M2C_FIELD(data, s32*, 0x20);
                DrawRectangle((f32) right, (f32) two_third_y, thickness,
                              (f32) third_h, (GXColor*) &c25);
                c26 = M2C_FIELD(data, s32*, 0x20);
                DrawRectangle((f32) center, (f32) two_third_y, (f32) half,
                              neg_thickness, (GXColor*) &c26);
                c27 = M2C_FIELD(data, s32*, 0x20);
                DrawRectangle((f32) center, (f32) (arg2 + (arg4 / 2)),
                              thickness, (f32) ((arg4 / 6) - 1),
                              (GXColor*) &c27);
                return;
            }
            if (data[0xA4] == 0) {
                c28 = M2C_FIELD(data, s32*, 0x20);
                DrawRectangle((f32) arg1, (f32) arg2, thickness,
                              (f32) third_h, (GXColor*) &c28);
                c29 = M2C_FIELD(data, s32*, 0x20);
                DrawRectangle((f32) arg1, (f32) mid_y, (f32) half,
                              neg_thickness, (GXColor*) &c29);
                c30 = M2C_FIELD(data, s32*, 0x20);
                DrawRectangle((f32) center, (f32) mid_y, thickness,
                              (f32) ((arg4 / 6) - 1), (GXColor*) &c30);
                return;
            }
            c31 = M2C_FIELD(data, s32*, 0x20);
            DrawRectangle((f32) right, (f32) arg2, thickness,
                          (f32) third_h, (GXColor*) &c31);
            c32 = M2C_FIELD(data, s32*, 0x20);
            DrawRectangle((f32) center, (f32) mid_y, (f32) half,
                          neg_thickness, (GXColor*) &c32);
            c33 = M2C_FIELD(data, s32*, 0x20);
            DrawRectangle((f32) center, (f32) mid_y, thickness,
                          (f32) ((arg4 / 6) - 1), (GXColor*) &c33);
        }
        break;
    }
}

static s32 lbl_804DA684 = (s32) 0xFFFF00FF;

/// Draws tournament bracket connector lines with optional tail segments.
void fn_8018D50C(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                 s32 arg5, s32 arg6, f32 farg0)
{
    u8* data = (u8*) arg0;
    TmData* tm;
    f32 thickness;
    f32 neg_thickness;
    s32 right;
    s32 bottom;
    s32 c0, c1, c2, c3, c4, c5, c6, c7, c8, c9;
    s32 c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20;

    tm = gm_8018F634();
    c20 = lbl_804DA684;
    c0 = lbl_804DA684;
    thickness = M2C_FIELD(data, f32*, 0x1C);
    c1 = lbl_804DA684;
    DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) arg4,
                  (GXColor*) &c1);

    right = arg1 + arg3;
    c2 = c0;
    DrawRectangle((f32) right, (f32) arg2, thickness, (f32) arg4,
                  (GXColor*) &c2);

    neg_thickness = -thickness;
    c3 = c0;
    DrawRectangle((f32) arg1, (f32) arg5, (f32) arg3 + thickness,
                  neg_thickness, (GXColor*) &c3);

    if (data[0x21] == 0) {
        if (data[0x4C] == 0) {
            c4 = M2C_FIELD(data, s32*, 0x20);
            DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) arg4,
                          (GXColor*) &c4);
            c5 = M2C_FIELD(data, s32*, 0x20);
            DrawRectangle((f32) arg1, (f32) arg5,
                          (f32) (arg3 / 2) + thickness, neg_thickness,
                          (GXColor*) &c5);
        } else {
            c6 = M2C_FIELD(data, s32*, 0x20);
            DrawRectangle((f32) right, (f32) arg2, thickness, (f32) arg4,
                          (GXColor*) &c6);
            {
                s32 half2 = arg3 / 2;
                c7 = M2C_FIELD(data, s32*, 0x20);
                DrawRectangle((f32) (arg1 + half2), (f32) arg5,
                              (f32) half2 + thickness, neg_thickness,
                              (GXColor*) &c7);
            }
        }
    }

    switch (tm->entrants) {
    case 1:
        if (data[0x5E] != 0) {
            bottom = arg2 + arg4;
            c8 = c0;
            DrawRectangle((f32) right, (f32) bottom, thickness, -70.0f,
                          (GXColor*) &c8);
            if (data[0x21] == 0 && data[0x4C] != 0) {
                c9 = M2C_FIELD(data, s32*, 0x20);
                DrawRectangle((f32) right, (f32) bottom, thickness, -70.0f,
                              (GXColor*) &c9);
            }
        }
        return;

    case 3:
        if (data[0x32] != 0) {
            bottom = arg2 + arg4;
            c10 = c0;
            DrawRectangle((f32) arg1, (f32) bottom, thickness, -60.0f,
                          (GXColor*) &c10);
            if (data[0x21] == 0 && data[0x4C] == 0) {
                c11 = M2C_FIELD(data, s32*, 0x20);
                DrawRectangle((f32) arg1, (f32) bottom, thickness, -60.0f,
                              (GXColor*) &c11);
            }
        } else if (data[0x5E] != 0) {
            bottom = arg2 + arg4;
            c12 = c0;
            DrawRectangle((f32) right, (f32) bottom, thickness, -60.0f,
                          (GXColor*) &c12);
            if (data[0x21] == 0 && data[0x4C] != 0) {
                c13 = M2C_FIELD(data, s32*, 0x20);
                DrawRectangle((f32) right, (f32) bottom, thickness, -60.0f,
                              (GXColor*) &c13);
            }
        }
        break;

    case 5:
        if (data[0x5E] != 0) {
            bottom = arg2 + arg4;
            c14 = c0;
            DrawRectangle((f32) right, (f32) bottom, thickness, -40.0f,
                          (GXColor*) &c14);
            if (data[0x21] == 0 && data[0x4C] != 0) {
                c15 = M2C_FIELD(data, s32*, 0x20);
                DrawRectangle((f32) right, (f32) bottom, thickness, -40.0f,
                              (GXColor*) &c15);
            }
        }
        break;

    case 7:
        if (data[0x5E] != 0) {
            if (data[0x2] == 0) {
                bottom = arg2 + arg4;
                c16 = c0;
                DrawRectangle((f32) right, (f32) bottom, thickness, -30.0f,
                              (GXColor*) &c16);
                if (data[0x21] == 0 && data[0x4C] != 0) {
                    c17 = M2C_FIELD(data, s32*, 0x20);
                    DrawRectangle((f32) right, (f32) bottom, thickness,
                                  -30.0f, (GXColor*) &c17);
                }
            } else {
                bottom = arg2 + 0x1E;
                c18 = c0;
                DrawRectangle((f32) right, (f32) bottom, thickness, -30.0f,
                              (GXColor*) &c18);
                if (data[0x21] == 0 && data[0x4C] != 0) {
                    c19 = M2C_FIELD(data, s32*, 0x20);
                    DrawRectangle((f32) right, (f32) bottom, thickness,
                                  -30.0f, (GXColor*) &c19);
                }
            }
        }
        break;
    }
}

void fn_8018DC18(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                 s32 arg5, s32 arg6, f32 farg0)
{
    u8* data = (u8*) arg0;
    f32 thickness;
    f32 neg_thickness;
    s32 right;
    s32 half;
    s32 center;
    s32 c0, c1, c2, c3, c4, c5, c6, c7, c8;

    c0 = 0xFFFF00FF;
    c8 = 0xFFFF00FF;
    thickness = M2C_FIELD(data, f32*, 0x1C);
    c1 = 0xFFFF00FF;
    DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) arg4,
                  (GXColor*) &c1);

    right = arg1 + arg3;
    c2 = c8;
    DrawRectangle((f32) right, (f32) arg2, thickness, (f32) arg4,
                  (GXColor*) &c2);

    half = arg3 / 2;
    center = arg1 + half;
    c3 = c8;
    DrawRectangle((f32) center, (f32) arg2, thickness, (f32) arg4,
                  (GXColor*) &c3);

    neg_thickness = -thickness;
    c4 = c8;
    DrawRectangle((f32) arg1, (f32) arg5, (f32) arg3 + thickness,
                  neg_thickness, (GXColor*) &c4);

    if (data[0x21] == 0) {
        if (data[0x4C] == 0) {
            c5 = M2C_FIELD(data, s32*, 0x20);
            DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) arg4,
                          (GXColor*) &c5);
            c6 = M2C_FIELD(data, s32*, 0x20);
            DrawRectangle((f32) arg1, (f32) arg5,
                          (f32) half + thickness, neg_thickness,
                          (GXColor*) &c6);
            return;
        }
        if (data[0x78] == 0) {
            c7 = M2C_FIELD(data, s32*, 0x20);
            DrawRectangle((f32) center, (f32) arg2, thickness, (f32) arg4,
                          (GXColor*) &c7);
            return;
        }
        c0 = M2C_FIELD(data, s32*, 0x20);
        DrawRectangle((f32) right, (f32) arg2, thickness, (f32) arg4,
                      (GXColor*) &c0);
        c8 = M2C_FIELD(data, s32*, 0x20);
        DrawRectangle((f32) center, (f32) arg5,
                      (f32) half + thickness, neg_thickness,
                      (GXColor*) &c8);
    }
}

void fn_8018DF68(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                 s32 arg5, s32 arg6, f32 farg0)
{
    u8* data = (u8*) arg0;
    f32 thickness;
    f32 neg_thickness;
    s32 right;
    s32 third;
    s32 left_third;
    s32 right_third;
    s32 half;
    s32 c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10;

    PAD_STACK(8);

    c0 = 0xFFFF00FF;
    c10 = 0xFFFF00FF;
    thickness = M2C_FIELD(data, f32*, 0x1C);
    c1 = 0xFFFF00FF;
    DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) arg4,
                  (GXColor*) &c1);

    right = arg1 + arg3;
    c2 = c10;
    DrawRectangle((f32) right, (f32) arg2, thickness, (f32) arg4,
                  (GXColor*) &c2);

    third = arg3 / 3;
    left_third = arg1 + third;
    c3 = c10;
    DrawRectangle((f32) left_third, (f32) arg2, thickness, (f32) arg4,
                  (GXColor*) &c3);

    right_third = right - third;
    c4 = c10;
    DrawRectangle((f32) right_third, (f32) arg2, thickness, (f32) arg4,
                  (GXColor*) &c4);

    neg_thickness = -thickness;
    c5 = c10;
    DrawRectangle((f32) arg1, (f32) arg5, (f32) arg3 + thickness,
                  neg_thickness, (GXColor*) &c5);

    if (data[0x21] == 0) {
        if (data[0x4C] == 0) {
            c6 = M2C_FIELD(data, s32*, 0x20);
            DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) arg4,
                          (GXColor*) &c6);
            c7 = M2C_FIELD(data, s32*, 0x20);
            DrawRectangle((f32) arg1, (f32) arg5,
                          (f32) (arg3 / 2) + thickness, neg_thickness,
                          (GXColor*) &c7);
            return;
        }
        if (data[0x78] == 0) {
            c8 = M2C_FIELD(data, s32*, 0x20);
            DrawRectangle((f32) left_third, (f32) arg2, thickness,
                          (f32) arg4, (GXColor*) &c8);
            c0 = M2C_FIELD(data, s32*, 0x20);
            DrawRectangle((f32) left_third, (f32) arg5,
                          ((f32) (arg3 / 2) + thickness) - (f32) third,
                          neg_thickness, (GXColor*) &c0);
            return;
        }
        if (data[0xA4] == 0) {
            c9 = M2C_FIELD(data, s32*, 0x20);
            DrawRectangle((f32) right_third, (f32) arg2, thickness,
                          (f32) arg4, (GXColor*) &c9);
            half = arg3 / 2;
            c10 = M2C_FIELD(data, s32*, 0x20);
            DrawRectangle((f32) (arg1 + half), (f32) arg5,
                          ((f32) half + thickness) - (f32) third,
                          neg_thickness, (GXColor*) &c10);
            return;
        }
        c0 = M2C_FIELD(data, s32*, 0x20);
        DrawRectangle((f32) right, (f32) arg2, thickness, (f32) arg4,
                      (GXColor*) &c0);
        half = arg3 / 2;
        c10 = M2C_FIELD(data, s32*, 0x20);
        DrawRectangle((f32) (arg1 + half), (f32) arg5,
                      (f32) half + thickness, neg_thickness,
                      (GXColor*) &c10);
    }
}

/// @todo Currently 98.8% match - permuter couldn't improve beyond score 140
void fn_8018E46C(HSD_GObj* gobj, int unused)
{
    void* data;
    s32 temp;
    s32 r30;
    u8* data_u8;
    s32* data_s32;
    f32* data_f32;

    data = gobj->user_data;
    data_u8 = (u8*) data;
    data_s32 = (s32*) data;
    data_f32 = (f32*) data;

    if (data_u8[2] != 0) {
        temp = -(data_s32[0x10 / 4] + data_s32[0x18 / 4]);
    } else {
        temp = -data_s32[0x10 / 4];
    }
    r30 = temp;
    HSD_FogSet(NULL);
    hsd_80391A04(1.0F, 1.0F, 1);
    switch (data_u8[3]) {
    case 0:
        fn_8018C8D4(data,
                    data_s32[0xC / 4] - (s32) (0.5F * data_f32[0x1C / 4]),
                    -data_s32[0x10 / 4], data_s32[0x14 / 4],
                    -data_s32[0x18 / 4], r30, data_s32[0xC / 4], 0.5F);
        break;
    case 1:
        fn_8018D50C(data,
                    data_s32[0xC / 4] - (s32) (0.5F * data_f32[0x1C / 4]),
                    -data_s32[0x10 / 4], data_s32[0x14 / 4],
                    -data_s32[0x18 / 4], r30, data_s32[0xC / 4], 0.5F);
        break;
    case 2:
        fn_8018DC18(data,
                    data_s32[0xC / 4] - (s32) (0.5F * data_f32[0x1C / 4]),
                    -data_s32[0x10 / 4], data_s32[0x14 / 4],
                    -data_s32[0x18 / 4], r30, data_s32[0xC / 4], 0.5F);
        break;
    case 3:
        fn_8018DF68(data,
                    data_s32[0xC / 4] - (s32) (0.5F * data_f32[0x1C / 4]),
                    -data_s32[0x10 / 4], data_s32[0x14 / 4],
                    -data_s32[0x18 / 4], r30, data_s32[0xC / 4], 0.5F);
        break;
    }
}

typedef struct CamDesc { s32 d[14]; } CamDesc;
extern CamDesc lbl_803B7CA8;

/// Initializes the tournament bracket camera and optionally resets bracket data.
/// Removes all existing GObjs from two entity lists, inits lbl_80473AB8 entries,
/// creates camera GObj with CObjDesc loaded from lbl_803B7CA8 rodata.
#pragma push
#pragma auto_inline off
void fn_8018E618(int arg0, int arg1, f32 farg0)
{
    CamDesc cam;
    HSD_GObj* gobj;
    HSD_GObj* tmp;
    s32 i;
    PAD_STACK(8);

    cam = lbl_803B7CA8;

    while ((tmp = M2C_FIELD(HSD_GObj_Entities, HSD_GObj**, 0x6C)) != NULL) {
        HSD_GObjPLink_80390228(tmp);
    }
    while ((tmp = M2C_FIELD(HSD_GObj_Entities, HSD_GObj**, 0x50)) != NULL) {
        HSD_GObjPLink_80390228(tmp);
    }

    {
        u8* ptr = (u8*) &lbl_80473AB8[0];

        if (arg1 != 0) {
            for (i = 0; i < 8; i++) {
                ptr[0x000] = 0;
                ptr[0x04E] = 3;
                ptr[0x07A] = 3;
                ptr[0x0A6] = 3;
                ptr[0x0D2] = 3;
                ptr[0x0DC] = 0;
                ptr[0x12A] = 3;
                ptr[0x156] = 3;
                ptr[0x182] = 3;
                ptr[0x1AE] = 3;
                ptr[0x1B8] = 0;
                ptr[0x206] = 3;
                ptr[0x232] = 3;
                ptr[0x25E] = 3;
                ptr[0x28A] = 3;
                ptr[0x294] = 0;
                ptr[0x2E2] = 3;
                ptr[0x30E] = 3;
                ptr[0x33A] = 3;
                ptr[0x366] = 3;
                ptr[0x370] = 0;
                ptr[0x3BE] = 3;
                ptr[0x3EA] = 3;
                ptr[0x416] = 3;
                ptr[0x442] = 3;
                ptr[0x44C] = 0;
                ptr[0x49A] = 3;
                ptr[0x4C6] = 3;
                ptr[0x4F2] = 3;
                ptr[0x51E] = 3;
                ptr[0x528] = 0;
                ptr[0x576] = 3;
                ptr[0x5A2] = 3;
                ptr[0x5CE] = 3;
                ptr[0x5FA] = 3;
                ptr[0x604] = 0;
                ptr[0x652] = 3;
                ptr[0x67E] = 3;
                ptr[0x6AA] = 3;
                ptr[0x6D6] = 3;
                ptr += 0x6E0;
            }
        } else {
            for (i = 0; i < 8; i++) {
            }
        }
    }

    gobj = GObj_Create(9, 0x14, 1);
    lbl_803D9DD0.cobj = HSD_CObjLoadDesc((HSD_CObjDesc*) &cam);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, lbl_803D9DD0.cobj);
    GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 1);
    M2C_FIELD(gobj, u32*, 0x24) = 0x10;
    M2C_FIELD(gobj, u32*, 0x20) = 0;

    if (arg1 != 0) {
        fn_8018A514(arg0, farg0);
    }
    fn_8018A970(arg0);
}
#pragma pop

void fn_8018E85C(int model, s32 flag)
{
    TmData* td;
    u8* entry;
    u8* sub;
    s32 bracket_idx;
    s32 outer_idx;
    s32 inner_idx;
    s32 j;
    u8* ptr;
    HSD_JObj* jobj;
    HSD_GObj* gobj;
    DynamicModelDesc* mdl = (DynamicModelDesc*) model;
    s32 anim_frame;
    f32 pos_multiplier;
    f32 pos;
    f32 final_pos;

    td = gm_8018F634();
    bracket_idx = 0;
    entry = (u8*) lbl_80473AB8;

    for (outer_idx = 0; outer_idx < 0x40; outer_idx++) {
        if (entry[0] == 0) {
            goto next_entry;
        }
        sub = entry;
        for (inner_idx = 0; inner_idx < 4; inner_idx++) {
            if (sub[0x30] == 0) {
                goto next_sub;
            }

            if (flag != 0) {
                ptr = (u8*) td;
                for (j = 0; j < 64; j++) {
                    if (ptr[0x44 + j * 0x12] == bracket_idx) {
                        break;
                    }
                }
                sub[0x50] = (u8) j;
                ptr = (u8*) td + j * 0x12;
                sub[0x4D] = ptr[0x3A];
                sub[0x4E] = ptr[0x37];
                sub[0x4F] = ptr[0x3E];
                sub[0x51] = ptr[0x38];
                sub[0x52] = ptr[0x39];
                *(u16*) (sub + 0x54) = *(u16*) (ptr + 0x40);
                bracket_idx++;
            }

            gobj = GObj_Create(0xE, 0x1B, 0);
            *(HSD_GObj**) (sub + 0x2C) = gobj;
            gobj = *(HSD_GObj**) (sub + 0x2C);
            jobj = HSD_JObjLoadJoint(mdl->joint);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 2);
            gm_8016895C(jobj, mdl, 0);

            anim_frame = sub[0x4D] + sub[0x4F] * 0x1E;
            HSD_JObjReqAnimAll(jobj, (f32) anim_frame);
            HSD_JObjAnimAll(jobj);

            if (outer_idx == fn_8018F74C()) {
                pos_multiplier = 10.0f;
            } else {
                pos_multiplier = 7.0f;
            }

            pos = 0.0083f * (f32)(0x40 - (s32) td->x2E) + 1.0f;
            final_pos = pos_multiplier * pos;
            HSD_JObjSetTranslateX(jobj, final_pos);

            pos = 0.0083f * (f32)(0x40 - (s32) td->x2E) + 1.0f;
            final_pos = pos_multiplier * pos;
            HSD_JObjSetTranslateY(jobj, final_pos);

            if (td->cur_option < 0x1F) {
                fn_8018AA74(jobj, outer_idx, inner_idx);
            } else {
                fn_8018FDC4(jobj, (f32) *(s32*) (sub + 0x44),
                            -(f32) *(s32*) (sub + 0x48), 666.0f);
            }

        next_sub:
            sub += 0x2C;
        }
    next_entry:
        entry += 0xDC;
    }
}

#pragma push
#pragma auto_inline off
void fn_8018EC48(void)
{
    mn_8022F138(0x19, 0x1C);
    mn_8022F138(0x12, 0x15);
}
#pragma pop

#pragma push
#pragma auto_inline off
void fn_8018EC7C(void)
{
    mn_8022F0F0(0x1B);
    mn_8022F0F0(0x14);
}
#pragma pop

/// #fn_8018ECA8

/// Formats a tournament slot display name into a destination buffer.
void fn_8018F00C(char* dest, s32 slot_id)
{
    char* templates_800[2];
    char* templates_900[2];
    char* tmpl_800;
    char* tmpl_900;

    templates_800[0] = lbl_804DA6C4;
    templates_900[0] = lbl_804DA6CC;
    templates_800[1] = lbl_804DA6C8;
    templates_900[1] = lbl_804DA6D0;

    tmpl_800 = templates_800[!!lbLang_IsSavedLanguageUS()];
    tmpl_900 = templates_900[!!lbLang_IsSavedLanguageUS()];

    if (slot_id >= 0x320) {
        if (slot_id < 0x384) {
            /* Slot IDs 800-899: format as 2-digit number (00-99) */
            s32 diff = slot_id - 0x320;
            if (diff < 10) {
                /* Single digit: write digit + null terminator */
                tmpl_800[7] = (s8) (slot_id - 0x2F0);
                tmpl_800[8] = 0;
            } else {
                /* Double digit: write tens, ones, null terminator */
                tmpl_800[7] = (s8) (diff / 10 + 0x30);
                tmpl_800[8] = (s8) (diff % 10 + 0x30);
                tmpl_800[9] = 0;
            }
            strcpy(dest, tmpl_800);
        } else if (slot_id != 0x3E7) {
            /* Slot IDs 900-998: format as 2-digit number (00-98) */
            s32 diff = slot_id - 0x384;
            if (diff < 10) {
                /* Single digit: write digit + null terminator */
                tmpl_900[7] = (s8) (slot_id - 0x354);
                tmpl_900[8] = 0;
            } else {
                /* Double digit: write tens, ones, null terminator */
                tmpl_900[7] = (s8) (diff / 10 + 0x30);
                tmpl_900[8] = (s8) (diff % 10 + 0x30);
                tmpl_900[9] = 0;
            }
            strcpy(dest, tmpl_900);
        }
    } else {
        /* Slot IDs below 800: use player nametag text */
        strcpy(dest, GetNameText((u8) slot_id));
    }
}

s32 gm_8018F1B0(MatchEnd* me)
{
    TmData* tm;

    tm = gm_8018F634();

    switch (gm_804771C4.match_type) {
    case 0:
        return 1;

    case 1:
        switch (tm->hmn_cpu_count) {
        case 1:
            return 1;

        case 2:
            if (tm->x30 == 3) {
                if (me->n_winners == 3) {
                    return 1;
                }
            } else if (tm->x30 == 4) {
                if (me->n_winners >= 3) {
                    return 1;
                }
            }
            break;

        case 3:
            if (me->n_winners == 4) {
                return 1;
            }
            break;
        }
        break;

    case 2:
        switch (tm->hmn_cpu_count) {
        case 1:
            if (tm->x30 == me->n_winners) {
                return 1;
            }
            break;

        case 2:
            if (tm->x30 == 3) {
                return 1;
            } else if (tm->x30 == 4) {
                if (me->n_winners >= 3) {
                    return 1;
                }
            }
            break;

        case 3:
            return 1;
        }
        break;
    }

    return 0;
}

#pragma push
#pragma auto_inline off
int fn_8018F310(int arg0)
{
    int i;
    for (i = 0; i < ARRAY_SIZE(lbl_803D9D20.x59); i++) {
        if (lbl_803D9D20.x59[i] == arg0) {
            return i;
        }
    }
    return -1;
}
#pragma pop

#pragma push
#pragma auto_inline off
u8 fn_8018F3BC(s32 arg0)
{
    return lbl_803D9D20.x59[arg0];
}
#pragma pop

#pragma push
#pragma auto_inline off
int fn_8018F3D0(int arg0)
{
    if (arg0 == 0xE || (arg0 >= 0x10 && arg0 <= 0x13) || arg0 == 0xA) {
        return 1;
    }
    if (arg0 <= 0xD) {
        return 0;
    }
    return 2;
}
#pragma pop

int fn_8018F410(void)
{
    int temp_r3;
    int* temp_r30;
    int* temp_r29;

    temp_r30 = &lbl_803D9F0C.x8;
    temp_r29 = &lbl_803D9F0C.x4;
    do {
        temp_r3 = HSD_Randi(0x19);
    } while (lbl_803D9D20.x72[temp_r3] == 0 || lbl_803D9F0C.x0 == temp_r3 ||
             *temp_r29 == temp_r3 || *temp_r30 == temp_r3);
    *temp_r30 = *temp_r29;
    *temp_r29 = lbl_803D9F0C.x0;
    lbl_803D9F0C.x0 = temp_r3;
    return temp_r3;
}

/// #fn_8018F410

int fn_8018F4A0(void)
{
    int temp_r3 = mnStageSel_8025BBD4();
    if (!gm_80164430(temp_r3)) {
        printf("This is impossible stage num from mnSelStageRandom() -> stage "
               "%d \n",
               temp_r3);
        __assert("gmtoulib.c", 0x53D, "0");
    }
    return temp_r3;
}

/// Counts available tournament slots and returns the last found index.
#pragma push
#pragma auto_inline off
s32 fn_8018F508(s32* out_index)
{
    s32 count;
    u8* base_ptr;
    u8* slot_ptr;
    s32 i;

    count = 0;
    base_ptr = (u8*) &lbl_80473AB8[fn_8018F74C()];
    slot_ptr = base_ptr;

    if (slot_ptr[0x0] == 0) {
        return -1;
    }

    for (i = 0; i < 4; i++) {
        if (slot_ptr[0x4E] != 3) {
            if (out_index != NULL) {
                *out_index = i;
            }
            count++;
        }
        slot_ptr += 0x2C;
    }

    return count;
}
#pragma pop

#pragma push
#pragma dont_inline on
char* fn_8018F5F0(void)
{
    if (lbLang_IsSavedLanguageUS()) {
        return "SdTou.usd";
    } else {
        return "SdTou.dat";
    }
}
#pragma pop

/// ???
/// tournament uses the user data as just an int
/// it controls various menu jobj states ie animation state, visibility, etc
#pragma dont_inline on
u32 fn_8018F62C(HSD_GObj* gobj)
{
    return (u32) gobj->user_data;
}
#pragma dont_inline off

#pragma push
#pragma dont_inline on
TmData* gm_8018F634(void)
{
    return &gm_804771C4;
}
#pragma pop

#pragma dont_inline on
u32 fn_8018F640(int arg0)
{
    if (arg0 >= 4) {
        arg0 = 4;
    }
    return gm_801A36A0(arg0);
}

u32 fn_8018F674(int arg0)
{
    if (arg0 >= 4) {
        arg0 = 4;
    }
    return gm_801A36C0(arg0);
}
#pragma dont_inline off

u32 fn_8018F6A8(int arg0)
{
    if (arg0 >= 4) {
        arg0 = 4;
    }
    return gm_801A3680((u8) arg0);
}

#pragma push
#pragma auto_inline off
int fn_8018F6DC(int arg0)
{
    if (arg0 >= 0x13) {
        if (arg0 == 0x1D) {
            return 5;
        }
        return arg0 - 1;
    }
    return arg0;
}
#pragma pop

#pragma push
#pragma auto_inline off
CharacterKind fn_8018F6FC(CSSIconHud arg0)
{
    if (arg0 >= 0x13) {
        if (arg0 == 0x1D) {
            return 5;
        }
        return arg0 + 1;
    }
    return (CharacterKind) arg0;
}
#pragma pop

#pragma push
#pragma auto_inline off
float fn_8018F71C(int arg0, int arg1)
{
    return arg0 + arg1 * 0x1E;
}
#pragma pop

#pragma push
#pragma auto_inline off
int fn_8018F74C(void)
{
    int i;

    for (i = 0; i < 0x40; i++) {
        if (lbl_80473AB8[i].x1 != 0) {
            break;
        }
    }

    return i;
}
#pragma pop

#pragma push
#pragma auto_inline off
int fn_8018F808(void)
{
    int i;
    int noerrcount = 0;
    for (i = 0; i < 4; i++) {
        if (HSD_PadMasterStatus[(u8) i].err == 0) {
            noerrcount += 1;
        }
    }
    return noerrcount;
}
#pragma pop

/// @todo Currently 78.75% match - needs register allocation fix
void fn_8018F888(void)
{
    s32 idx;
    u8* ptr;
    u8* base;
    s32 ctr;
    u8 val;
    s32 idx2;

    base = (u8*) lbl_80473AB8;
    ctr = 8;
    ptr = base;
    idx = 0;

loop1:
    if (*(ptr + 0x1) != 0) {
        goto done1;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx += 1;
    if (val != 0) {
        goto done1;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx += 1;
    if (val != 0) {
        goto done1;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx += 1;
    if (val != 0) {
        goto done1;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx += 1;
    if (val != 0) {
        goto done1;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx += 1;
    if (val != 0) {
        goto done1;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx += 1;
    if (val != 0) {
        goto done1;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx += 1;
    if (val != 0) {
        goto done1;
    }
    ptr += 0xDC;
    idx += 1;
    ctr -= 1;
    if (ctr != 0) {
        goto loop1;
    }

done1:
    idx2 = 0;
    *(base + idx * 0xDC + 0x21) = 0;

    if (*(base + 0x373F) != 5) {
        return;
    }

    ctr = 8;
    ptr = base;

loop2:
    if (*(ptr + 0x1) != 0) {
        goto done2;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx2 += 1;
    if (val != 0) {
        goto done2;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx2 += 1;
    if (val != 0) {
        goto done2;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx2 += 1;
    if (val != 0) {
        goto done2;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx2 += 1;
    if (val != 0) {
        goto done2;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx2 += 1;
    if (val != 0) {
        goto done2;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx2 += 1;
    if (val != 0) {
        goto done2;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx2 += 1;
    if (val != 0) {
        goto done2;
    }
    ptr += 0xDC;
    idx2 += 1;
    ctr -= 1;
    if (ctr != 0) {
        goto loop2;
    }

done2:
    *(base + idx2 * 0xDC + 0xFD) = 0;
}

/// @todo Currently 84.63% match - needs loop pattern fix

void fn_8018FA24(void)
{
    s32 player_count;
    s32 player_idx;
    u8* tmdata;
    u8* dst;
    u8* ptr;
    s32 slot;
    s32 char_kind;
    s32 ctr;

    PAD_STACK(8);

    ptr = (u8*) lbl_80473AB8;
    tmdata = ptr + 0x370C;
    slot = 0;

    ctr = 8;
    do {
        if (ptr[0x01] != 0) {
            goto found;
        }
        ptr += 0xDC;
        slot += 1;
        if (ptr[0x01] != 0) {
            goto found;
        }
        ptr += 0xDC;
        slot += 1;
        if (ptr[0x01] != 0) {
            goto found;
        }
        ptr += 0xDC;
        slot += 1;
        if (ptr[0x01] != 0) {
            goto found;
        }
        ptr += 0xDC;
        slot += 1;
        if (ptr[0x01] != 0) {
            goto found;
        }
        ptr += 0xDC;
        slot += 1;
        if (ptr[0x01] != 0) {
            goto found;
        }
        ptr += 0xDC;
        slot += 1;
        if (ptr[0x01] != 0) {
            goto found;
        }
        ptr += 0xDC;
        slot += 1;
        if (ptr[0x01] != 0) {
            goto found;
        }
        ptr += 0xDC;
        slot += 1;
    } while (--ctr != 0);

found:
    dst = tmdata;
    ptr = (u8*) lbl_80473AB8 + slot * 0xDC;
    player_count = 0;
    player_idx = 0;

    do {
        dst[0x4B6] = ptr[0x30];
        dst[0x4B7] = ptr[0x50];
        *(u16*) (dst + 0x4BE) = *(u16*) (tmdata + 0x40 + ptr[0x50] * 0x12);
        dst[0x4BC] = ptr[0x51];
        dst[0x4BD] = ptr[0x52];
        dst[0x4B9] = ptr[0x4D];
        char_kind = dst[0x4B9];
        if (char_kind >= 0x13) {
            if (char_kind == 0x1D) {
                char_kind = 5;
            } else {
                char_kind += 1;
            }
        }
        Player_SetPlayerCharacter(player_idx, char_kind);
        dst[0x4B8] = ptr[0x4E];
        char_kind = dst[0x4B8];
        if (char_kind != 3) {
            player_count += 1;
        }
        Player_SetSlottype(player_idx, char_kind);
        dst[0x4BB] = ptr[0x4F];
        Player_SetCostumeId(player_idx, dst[0x4BB]);
        dst[0x4BC] = ptr[0x51];
        player_idx += 1;
        ptr += 0x2C;
        dst += 0xA;
    } while (player_idx < 4);

    tmdata[0x30] = player_count;
}

#pragma push
#pragma auto_inline off
void fn_8018FBD8(void* arg0, s32 arg1)
{
    M2C_FIELD(arg0, s32*, 0x2C) = arg1;
}
#pragma pop

void fn_8018FBE0(s32 arg0, s32 arg1, s32 arg2, s8 arg3, s8 arg4, s16 arg5,
                 s8 arg6)
{
    s32 i;
    u8* ptr;

    PAD_STACK(8);

    gm_804771C4.cur_option = arg0;
    *(s32*) &gm_804771C4._x1C = arg1;
    gm_804771C4.x20 = arg2;

    ptr = (u8*) &gm_804771C4.x37[0];
    for (i = 0; i < 64; i++) {
        ptr[0] = (u8) arg6;
        ptr[1] = (u8) arg4;
        ptr[2] = (u8) arg3;
        *(u16*) (ptr + 9) = (u16) arg5;
        ptr[13] = (u8) i;
        ptr += 0x12;
    }
}

#pragma push
#pragma auto_inline off
void fn_8018FDC4(HSD_JObj* jobj, float x, float y, float z)
{
    if ((int) x != 666) {
        HSD_JObjSetTranslateX(jobj, x);
    }
    if ((int) y != 666) {
        HSD_JObjSetTranslateY(jobj, y);
    }
    if ((int) z != 666) {
        HSD_JObjSetTranslateZ(jobj, z);
    }
}
#pragma pop

#pragma push
#pragma auto_inline off
void fn_8018FF9C(HSD_JObj* jobj, float x, float y, float z)
{
    if ((int) x != 666) {
        HSD_JObjSetScaleX(jobj, x);
    }
    if ((int) y != 666) {
        HSD_JObjSetScaleY(jobj, y);
    }
    if ((int) z != 666) {
        HSD_JObjSetScaleZ(jobj, z);
    }
}
#pragma pop

#pragma push
#pragma auto_inline off
HSD_GObj* fn_80190174(HSD_CObjDesc* cobjdesc)
{
    HSD_GObj* gobj = GObj_Create(0x13, 0x12, 0);
    HSD_CObj* cobj = HSD_CObjLoadDesc(cobjdesc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 0);
    gobj->gxlink_prios = 7;
    return gobj;
}
#pragma pop

#pragma push
#pragma auto_inline off
HSD_GObj* fn_801901F8(HSD_CObjDesc* cobjdesc)
{
    HSD_GObj* gobj = GObj_Create(0x13, 0x15, 2);
    HSD_CObj* cobj = HSD_CObjLoadDesc(cobjdesc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 2);
    gobj->gxlink_prios = 0xA;
    return gobj;
}
#pragma pop

#pragma push
#pragma auto_inline off
void fn_8019027C(UNK_T lights)
{
    HSD_GObj* gobj = GObj_Create(0xB, 0x1A, 0);
    HSD_LObj* lobj = lb_80011AC4(lights);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 1, 0);
}
#pragma pop

static HSD_GObj* lbl_804D663C;

/// Initializes SIS library text rendering for tournament mode.
#pragma push
#pragma auto_inline off
void fn_801902F0(int sis_param)
{
    s32 value;
    PAD_STACK(8);

    value = sis_param;
    HSD_SisLib_803A5E70();
    if (*(s32*) ((u8*) &gm_804771C4 + 0x1C) == 0) {
        value = 0;
    }
    lbl_804D663C = (HSD_GObj*) HSD_SisLib_803A611C(0, (HSD_GObj*) value, 9,
                                                   0x12, 0, 3, 0, 0x13);
}
#pragma pop

#pragma push
#pragma auto_inline off
HSD_GObj* fn_8019035C(bool arg0, DynamicModelDesc* model, int arg2, int arg3,
                      int arg4, bool arg5, void (*arg6)(HSD_GObj*), f32 arg8)
{
    HSD_GObj* gobj = GObj_Create(0xE, arg3, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(model->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, arg4, 0);
    if (arg6 != NULL) {
        HSD_GObjProc_8038FD54(gobj, arg6, 0);
    }
    if (arg5) {
        gm_8016895C(jobj, model, arg2);
        HSD_JObjReqAnimAll(jobj, arg8);
        HSD_JObjAnimAll(jobj);
        if (arg0) {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }
    }
    return gobj;
}
#pragma pop

#pragma dont_inline on
void fn_8019044C(HSD_JObj* jobj, float arg1)
{
    HSD_JObjReqAnimAll(jobj, arg1);
    HSD_JObjAnimAll(jobj);
}
#pragma dont_inline off

#pragma push
#pragma auto_inline off
void fn_80190480(float arg8)
{
    if ((int) arg8 == 0) {
        HSD_CObjSetFov(lbl_803D9DD0.cobj, lbl_803D9DD0.xD0);
        return;
    }
    HSD_CObjSetFov(lbl_803D9DD0.cobj, arg8);
}
#pragma pop

void fn_801904D0(void)
{
    struct lbl_803D9DD0_t* tmp = &lbl_803D9DD0;
    HSD_CObjSetInterest(tmp->cobj, &lbl_803D9DD0.interest);
    HSD_CObjSetEyePosition(tmp->cobj, &lbl_803D9DD0.eye_position);
}

#pragma push
#pragma auto_inline off
void fn_80190520(f32 x, f32 y, f32 z)
{
    Vec3 sp14;

    if (((s32) x == 0) && ((s32) y == 0) && ((s32) z == 0)) {
        struct lbl_803D9DD0_t* tmp = &lbl_803D9DD0;
        HSD_CObjSetInterest(tmp->cobj, &lbl_803D9DD0.interest);
        HSD_CObjSetEyePosition(tmp->cobj, &lbl_803D9DD0.eye_position);
        return;
    } else {
        struct lbl_803D9DD0_t* tmp = &lbl_803D9DD0;
        sp14.x = x;
        sp14.y = y;
        sp14.z = z;
        HSD_CObjSetInterest(tmp->cobj, &sp14);
        sp14.z = 415.6922f + z;
        HSD_CObjSetEyePosition(tmp->cobj, &sp14);
    }
}
#pragma pop

/// #fn_80190520

static inline int gm_801905F0_inline0(int c_kind)
{
    if (c_kind < CKIND_SEAK) {
        return c_kind;
    }
    if (c_kind == CKIND_GKOOPS) {
        return CKIND_KOOPA;
    }
    return c_kind + 1;
}

void gm_801905F0(StartMeleeData* arg0)
{
    GameRules* temp_r31 = gmMainLib_8015CC34();
    int i;
    TmVsData sp18;

    gm_80168FC4();
    gm_80167A64(&arg0->rules);
    arg0->rules.is_teams = false;
    arg0->rules.xE = gm_804771C4.x28;
    fn_801640B0(&arg0->rules.x20);
    arg0->rules.x0_0 = temp_r31->mode;
    if (temp_r31->mode != 1) {
        arg0->rules.x0_6 = true;
    } else if (temp_r31->stock_time_limit != 0) {
        arg0->rules.x0_6 = true;
    } else {
        arg0->rules.x0_6 = false;
    }
    if (arg0->rules.x0_6) {
        if (temp_r31->mode != 1) {
            if (temp_r31->time_limit == 0) {
                arg0->rules.x10 = 99 * 60;
            } else {
                arg0->rules.x10 = temp_r31->time_limit * 60;
            }
        } else {
            if (temp_r31->stock_time_limit == 0) {
                arg0->rules.x10 = 99 * 60;
            } else {
                arg0->rules.x10 = temp_r31->stock_time_limit * 60;
            }
        }
    }
    if (arg0->rules.x0_0 == 1) {
        arg0->rules.x2_0 = true;
    }
    arg0->rules.x0_7 = false;
    arg0->rules.x4_2 = false;
    arg0->rules.x4_4 = false;
    arg0->rules.xB = gmMainLib_8015CC58()->item_freq;
    arg0->rules.x2_2 = false;
    arg0->rules.x18 = 0;
    arg0->rules.x34 = 1.0f;
    arg0->rules.x30 = fn_801653E8(temp_r31->damage_ratio);
    arg0->rules.x3_4 = false;
    arg0->rules.x3_5 = false;
    arg0->rules.x3_2 = false;
    arg0->rules.x3_3 = false;
    switch (gmMainLib_8015ED30()) {
    case 1:
        arg0->rules.xC = 0;
        break;
    case 0:
        arg0->rules.xC = -1;
        break;
    case 2:
        arg0->rules.xC = -2;
        break;
    }
    if (temp_r31->pause != 0) {
        arg0->rules.x2_4 = false;
    } else {
        arg0->rules.x2_4 = true;
    }
    if (temp_r31->score_display != 0 && !arg0->rules.x0_3) {
        arg0->rules.x3_0 = true;
    } else {
        arg0->rules.x3_0 = false;
    }
    gm_80167A14(arg0->players);

    for (i = 0; i < 4; i++) {
        if (i < gm_804771C4.x30) {
            arg0->players[i].x20 = 1.0f;
            arg0->players[i].xA = (u8) MIN(gm_804771C4.x4B8[i].x6, 0x78);
            if (gm_804771C4.x4B8[i].x2 != 0) {
                arg0->players[i].c_kind = gm_801905F0_inline0(fn_8018F410());
                arg0->players[i].color =
                    HSD_Randi(gm_80169238(arg0->players[i].c_kind));
            } else {
                arg0->players[i].c_kind =
                    gm_801905F0_inline0(gm_804771C4.x4B8[i].x1);
                arg0->players[i].color = gm_804771C4.x4B8[i].x3;
            }
            arg0->players[i].slot_type = gm_804771C4.x4B8[i].x0;
            arg0->players[i].stocks = temp_r31->stock_count;
            arg0->players[i].sub_color = 0;
            arg0->players[i].team = 0xFF;
            arg0->players[i].xC_b0 = gm_801677F8(i, arg0->players[i].xA);
            if (gm_804771C4.x4B8[i].x0 == 1) {
                arg0->players[i].xC_b0 = false;
            }
            arg0->players[i].xE = 4;
            arg0->players[i].cpu_level = gm_804771C4.x4B8[i].x4;
            arg0->players[i].x12 = 0;
            if (gmMainLib_8015CC34()->handicap != 0) {
                arg0->players[i].x18 = fn_8016419C(gm_804771C4.x4B8[i].x5);
                arg0->players[i].x1C = fn_801641B4(gm_804771C4.x4B8[i].x5);
            } else {
                arg0->players[i].x18 = arg0->players[i].x1C = 1.0F;
            }
        } else {
            arg0->players[i].slot_type = Gm_PKind_NA;
        }
    }

    sp18.stage_id = arg0->rules.xE;
    for (i = 0; i < 4; i++) {
        sp18.slot_type[i] = arg0->players[i].slot_type;
        sp18.char_id[i] = arg0->players[i].c_kind;
        sp18.color[i] = arg0->players[i].color;
    }

    fn_8019EF08(&sp18);
}

/// #fn_80190ABC

#pragma push
#pragma dont_inline on
void gm_80190EA4(void)
{
    int i;
    TmData* tmdata = gm_8018F634();

    fn_80190174(lbl_804D664C->cameras->desc);
    fn_801902F0(0);
    fn_80193308();
    fn_8019027C(lbl_804D664C->lights);
    fn_80193230();
    tmdata->cur_option = 0;

    while (tmdata->cur_option < 7) {
        fn_80190ABC(0);
        fn_80190ABC(2);
        fn_80190ABC(3);
        fn_80190ABC(1);
        tmdata->cur_option += 1;
    }
    if (gm_804771C4.match_type == 0) {
        TmData* tmdata = gm_8018F634();
        fn_8018EC7C();
        fn_8018E618(tmdata->entrants, 1, 4.5f);
        fn_80190480(130.0f);
        fn_80190520(-278.0f, 255.0f, 0.0f);
    }
    tmdata->x20 = 0;

    for (i = 0; i < 64; i++) {
        if (gmMainLib_8015CC34()->handicap == 1) {
            tmdata->x37[i].x1 = 5;
        } else {
            tmdata->x37[i].x1 = 9;
        }
    }
}
#pragma pop

static struct {
    u8 x0;
    u8 x1;
    u8 x2;
    u8 x3;
    u8 x4;
    u8 x5;
    u8 x6;
    u8 x7;
    u8 x8;
    u8 x9;
    u8 xA;
    u8 xB;
    u16 xC_counter;
    u8 xE;
    u8 xF;
    u8 pad2[0x10];
} lbl_804799B8;

/// Initializes the time menu state when entering the time selection screen.
void gm_80190FE4(int arg0)
{
    TmData* tm = gm_8018F634();

    if (mn_8022F218() == 0) {
        fn_80190174(lbl_804D664C->cameras->desc);
        fn_801902F0(0);
        fn_80193308();
        fn_8019027C(lbl_804D664C->lights);
        fn_80193230();

        for (tm->cur_option = 0; tm->cur_option < 7; tm->cur_option++) {
            fn_80190ABC(0);
            fn_80190ABC(2);
            fn_80190ABC(3);
            fn_80190ABC(1);
        }

        tm->x20 = 0;
        tm->cur_option = 0xC;

        if (arg0 != 0x78) {
            tm->x37[lbl_804799B8.x2 + lbl_804799B8.x3].x9 =
                arg0;
        }

        fn_80190ABC(5);
        fn_80190ABC(6);
    }
}

void fn_801910E0(HSD_GObj* gobj)
{
    u16* counter = &lbl_804799B8.xC_counter;
    HSD_JObj* jobj = gobj->hsd_obj;

    if (*counter > 0x320U) {
        *counter = 0;
    }
    fn_8019044C(jobj, (f32) *counter);
    *counter = *counter + 1;
}

/// @todo Currently 83.05% match - compiler generates different register usage
void fn_80191154(HSD_GObj* gobj)
{
    TmData* tm;
    HSD_JObj* jobj;
    u8* xE_ptr;

    tm = gm_8018F634();
    jobj = gobj->hsd_obj;

    if (tm->cur_option < 9) {
        xE_ptr = &lbl_804799B8.xE;
        if (*xE_ptr > 0x27U) {
            *xE_ptr = 0xA;
        }
    } else {
        xE_ptr = &lbl_804799B8.xE;
        if (lbl_804799B8.xE == 0x31) {
            fn_80190ABC(6);
            fn_80190ABC(5);
            tm->cur_option = 0xA;
        }
        if (*xE_ptr > 0x4EU) {
            *xE_ptr = 0x32;
        }
    }
    xE_ptr = &lbl_804799B8.xE;
    fn_8019044C(jobj, (float) lbl_804799B8.xE);
    (*xE_ptr)++;
}

/// @todo Currently 78.85% match - needs register allocation fix
void fn_80191240(HSD_GObj* gobj)
{
    TmData* tm;
    s32 val;
    HSD_JObj* jobj;
    HSD_JObj* first_child;
    HSD_JObj* sibling;

    tm = gm_8018F634();
    val = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;
    if (tm->cur_option >= 9) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }
    HSD_JObjClearFlagsAll(jobj, 0x10);
    if (jobj == NULL) {
        first_child = NULL;
    } else {
        first_child = jobj->child;
    }
    if (first_child == NULL) {
        sibling = NULL;
    } else {
        sibling = first_child->next;
    }
    if (val == tm->cur_option) {
        if (lbl_804799B8.x7 != 0) {
            fn_8019044C(first_child, 1.0F);
            lbl_804799B8.x7 = lbl_804799B8.x7 - 1;
        } else {
            fn_8019044C(first_child, 0.0F);
        }
        if (lbl_804799B8.x8 != 0) {
            fn_8019044C(sibling, 1.0F);
            lbl_804799B8.x8 = lbl_804799B8.x8 - 1;
            return;
        }
        fn_8019044C(sibling, 0.0F);
        return;
    }
    if (val > tm->cur_option) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }
    if (val == 5 && gm_804771C4.match_type != 0) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
    }
    fn_8019044C(jobj, 0.0F);
}

/// Updates text visibility and menu state for tournament bracket options.
void fn_801913BC(HSD_GObj* gobj)
{
    TmData* tm;
    u32 idx;
    HSD_JObj* jobj;
    s32 cur;
    u8* counter_ptr;

    tm = gm_8018F634();
    idx = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (tm->cur_option < 9) {
        HSD_JObjClearFlagsAll(jobj, 0x10);

        if ((s32) idx == 0) {
            tm->x518[0]->hidden = 1;
            tm->x518[1]->hidden = 1;
            tm->x518[2]->hidden = 1;
            tm->x524[0]->hidden = 1;
            tm->x524[1]->hidden = 1;
            tm->x4E0->hidden = 0;
        }

        if ((s32) idx <= tm->cur_option) {
            tm->x4E8[idx]->hidden = 0;
            tm->x500[idx]->hidden = 0;
            if ((s32) idx < 3 && gm_804771C4.match_type == 0) {
                tm->x4E4->hidden = 1;
            } else {
                tm->x4E4->hidden = 0;
            }
            if ((s32) idx == 5 && gm_804771C4.match_type != 0) {
                tm->x4E8[idx]->hidden = 1;
                tm->x500[idx]->hidden = 1;
                HSD_JObjSetFlagsAll(jobj, 0x10);
            }
        } else {
            tm->x4E8[idx]->hidden = 1;
            tm->x500[idx]->hidden = 1;
        }

        if (tm->cur_option >= 3 && gm_804771C4.match_type == 0) {
            tm->x4E4->hidden = 0;
        } else {
            tm->x4E4->hidden = 1;
        }

        cur = tm->cur_option;
        if ((s32) idx == cur) {
            counter_ptr = &(&lbl_804799B8.x0)[0x10 + idx];
            if (*counter_ptr >= 0x14U) {
                *counter_ptr = 0xA;
            }
            fn_8019044C(jobj, (f32) *counter_ptr);
            *counter_ptr = *counter_ptr + 1;
            return;
        }
        if ((s32) idx > cur) {
            HSD_JObjSetFlagsAll(jobj, 0x10);
            return;
        }
        fn_8019044C(jobj, 0.0f);
        return;
    }

    HSD_JObjSetFlagsAll(jobj, 0x10);
    tm->x4E8[idx]->hidden = 1;
    tm->x500[idx]->hidden = 1;
    if ((s32) idx == 0) {
        if (tm->cur_option > 9) {
            tm->x518[1]->hidden = 0;
            tm->x518[2]->hidden = 0;
            tm->x524[0]->hidden = 0;
            tm->x524[1]->hidden = 0;
            if (tm->cur_option != 0xF) {
                tm->x518[0]->hidden = 1;
            } else {
                tm->x518[0]->hidden = 0;
            }
        }
        tm->x4E4->hidden = 1;
        tm->x4E0->hidden = 1;
    }
}

/// Updates the visibility and animation state of a Tournament Mode menu
/// option.
void fn_80191678(HSD_GObj* gobj)
{
    TmData* tmdata;
    s32 idx;
    HSD_JObj* jobj;
    u8* ptr;

    tmdata = gm_8018F634();
    idx = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (tmdata->cur_option >= 9) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, 0x10);

    if (idx == tmdata->cur_option) {
        ptr = ((u8*) &lbl_804799B8) + idx;
        if (*(ptr += 0x16) > 0x64) {
            *ptr = 0;
        }
        fn_8019044C(jobj, (f32) *ptr);
        *ptr = *ptr + 1;
        return;
    }

    HSD_JObjSetFlagsAll(jobj, 0x10);
}

/// @todo Currently 89.68% match - permuter couldn't improve
/// Updates menu option selection animation.
void fn_8019175C(void* gobj)
{
    HSD_JObj* first_child;
    HSD_JObj* option_jobj_a;
    HSD_JObj* option_jobj_b;
    u8* counter;
    s32 i;
    TmData* tm;
    HSD_JObj* jobj;
    HSD_JObj* root_jobj;
    HSD_JObj* child;
    HSD_JObj** base;

    PAD_STACK(8);

    tm = gm_8018F634();
    fn_8018F62C(gobj);
    root_jobj = *(HSD_JObj**) ((u8*) gobj + 0x28);
    jobj = root_jobj;

    if (tm->cur_option >= 9) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, 0x10);

    if (root_jobj == NULL) {
        first_child = NULL;
    } else {
        first_child = root_jobj->child;
    }

    if (first_child == NULL) {
        child = NULL;
    } else {
        child = first_child->next;
    }

    if (child == NULL) {
        child = NULL;
    } else {
        child = child->next;
    }

    if (child == NULL) {
        option_jobj_a = NULL;
    } else {
        option_jobj_a = child->next;
    }

    if (option_jobj_a == NULL) {
        option_jobj_b = NULL;
    } else {
        option_jobj_b = option_jobj_a->next;
    }

    if (tm->cur_option >= 6) {
        counter = &lbl_804799B8.xF;
        if (*counter >= 0x14U) {
            *counter = 0;
        }
        i = 0;
        base = &option_jobj_a;
        do {
            if (i != tm->cur_option - 6) {
                fn_8019044C(base[i], 0.0F);
            } else {
                fn_8019044C(base[i], (f32) *counter);
            }
            i += 1;
        } while (i <= 2);
        *counter = *counter + 1;
        return;
    }

    HSD_JObjSetFlagsAll(jobj, 0x10);
}

/// Updates visibility and animation frame of a Training Mode HUD element.
void fn_801918F0(HSD_GObj* gobj)
{
    TmData* tm;
    HSD_JObj* jobj;
    u8* counter;

    tm = gm_8018F634();
    jobj = gobj->hsd_obj;

    if (tm->cur_option <= 9) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, 0x10);

    switch (tm->cur_option) {
    case 0xB:
        counter = &lbl_804799B8.pad2[0xC];
        if (*counter > 5) {
            *counter = 0;
        }
        fn_8019044C(jobj, (float) *counter);
        if (*counter < 5) {
            *counter = *counter + 1;
        }
        break;
    case 0xD:
    case 0xE:
        counter = &lbl_804799B8.pad2[0xC];
        if (*counter < 10) {
            *counter = 10;
        }
        fn_8019044C(jobj, (float) *counter);
        if (*counter < 15) {
            *counter = *counter + 1;
        }
        break;
    case 0xF:
        fn_8019044C(jobj, 16.0F);
        break;
    default:
        fn_8019044C(jobj, 0.0F);
        break;
    }
}

/// Updates the tournament bracket display visibility and animation.
void fn_80191A54(HSD_GObj* gobj)
{
    TmData* td;
    HSD_JObj* jobj;
    HSD_JObj* jobj_copy;
    HSD_JObj* child;
    int cur_option;

    td = gm_8018F634();
    jobj = gobj->hsd_obj;
    jobj_copy = jobj;

    if (td->cur_option <= 9) {
        HSD_JObjSetFlagsAll(jobj_copy, 0x10);
        return;
    }

    HSD_JObjClearFlagsAll(jobj_copy, 0x10);

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    cur_option = td->cur_option;
    if (cur_option == 0xA || cur_option == 0xC || cur_option == 0x10) {
        fn_8019044C(child, (f32) lbl_804799B8.x2);
        HSD_MObjReqAnim(child->u.dobj->mobj, (f32) lbl_804799B8.xA);
    } else {
        HSD_MObjReqAnim(child->u.dobj->mobj, 6.0F);
    }
    HSD_MObjAnim(child->u.dobj->mobj);
}

static u8 lbl_804799B8_data[0x40];

/// Updates button highlight animation based on current menu option.
void fn_80191B5C(void* gobj)
{
    u8* timers;
    TmData* tm;
    HSD_JObj* jobj;

    timers = lbl_804799B8_data;
    tm = gm_8018F634();
    jobj = *(HSD_JObj**) ((u8*) gobj + 0x28);

    if (tm->cur_option <= 9) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
    } else {
        HSD_JObjClearFlagsAll(jobj, 0x10);
        switch (tm->cur_option) {
        case 10:
            fn_8019044C(jobj, (f32) timers[0xA]);
            break;
        case 11:
            fn_8019044C(jobj, 5.0F);
            break;
        case 12:
            fn_8019044C(jobj, (f32) (s32) (timers[0xA] + 0x14));
            break;
        case 13:
        case 14:
        case 15:
            fn_8019044C(jobj, 25.0F);
            break;
        case 16:
            fn_8019044C(jobj, (f32) (s32) (timers[0xA] + 0x28));
            break;
        }
    }
}

static s32 lbl_804D6658;

/// Updates JObj visibility based on current menu option selection.
void fn_80191CA4(HSD_GObj* gobj)
{
    TmData* tm;
    HSD_JObj* jobj;

    tm = gm_8018F634();
    jobj = gobj->hsd_obj;
    if (tm->cur_option <= 9) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }
    if (lbl_804D6658 < 10) {
        lbl_804D6658 += 1;
    }
    HSD_JObjClearFlagsAll(jobj, 0x10);
    fn_8019044C(jobj, (f32) lbl_804D6658);
}

/// GObj callback for tournament bracket slot UI elements.
void fn_80191D38(HSD_GObj* gobj)
{
    TmData* tm;
    s32 idx;
    HSD_JObj* jobj;

    tm = gm_8018F634();
    idx = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (tm->cur_option <= 9) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, 0x10);

    if ((s32) idx < (s32) lbl_804799B8.x3 ||
        (s32) idx >= (s32) tm->x2E ||
        (s32) idx > (s32) (lbl_804799B8.x3 + 0xB))
    {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    fn_8018FDC4(jobj, 666.0f,
                -((2.6200008f * (f32) (idx - lbl_804799B8.x3)) -
                  12.800008f),
                0.1f);

    if ((u8) tm->x37[idx].x4 != 0) {
        fn_8019044C(jobj, 201.0f);
    } else {
        fn_8019044C(jobj, fn_8018F71C((s32) tm->x37[idx].x2,
                                       (s32) tm->x37[idx].x6));
    }

    if (lbl_803D9D20.x72[tm->x37[idx].x2] != 0) {
        HSD_JObjClearFlagsAll(jobj, 0x10);
    } else {
        HSD_JObjSetFlagsAll(jobj, 0x10);
    }
}

/// Updates visibility and position of a tournament bracket player entry JObj.
void fn_80191E9C(HSD_GObj* gobj)
{
    TmData* tm;
    s32 idx;
    HSD_JObj* jobj;

    tm = gm_8018F634();
    idx = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (tm->cur_option <= 9) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, 0x10);

    if (lbl_804799B8.x0 == 0) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    if ((s32) idx < (s32) lbl_804799B8.x3 ||
        (s32) idx >= (s32) tm->x2E ||
        (s32) idx > (s32) (lbl_804799B8.x3 + 0xB))
    {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    fn_8018FDC4(jobj, 666.0f,
                -((2.6200008f * (f32) (idx - lbl_804799B8.x3)) -
                  12.800008f),
                0.1f);
    fn_8019044C(jobj, (f32) tm->x37[idx].x2);
}

void fn_80191FD4(HSD_GObj* gobj)
{
    TmData* tm;
    HSD_JObj* jobj;
    HSD_JObj* child;
    HSD_JObj* sibling;
    u32 idx;
    s32 slot;
    enum CSSIconHud hud;

    tm = gm_8018F634();
    jobj = gobj->hsd_obj;
    idx = fn_8018F62C(gobj);

    if ((s32) tm->cur_option <= 9) {
        HSD_JObjSetFlagsAll(jobj, 0x10U);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, 0x10U);

    if ((s32) idx == 0x19) {
        child = (jobj != NULL) ? jobj->child : NULL;
        fn_8019044C(child, 0.0f);

        sibling = (child != NULL) ? child->next : NULL;
        slot = lbl_804799B8.x2 + lbl_804799B8.x3;

        if ((u8) tm->x37[slot].x4 != 0) {
            fn_8019044C(sibling, 201.0f);
            return;
        }

        fn_8019044C(sibling,
                    fn_8018F71C((s32) tm->x37[slot].x2,
                                (s32) tm->x37[slot].x6));
        {
            u8 chr = tm->x37[lbl_804799B8.x2 + lbl_804799B8.x3].x2;
            if (lbl_803D9D20.x72[chr] != 0) {
                HSD_JObjClearFlagsAll(sibling, 0x10U);
                return;
            }
            if (fn_8018F3D0(fn_8018F310(fn_8018F6FC((enum CSSIconHud) chr))) ==
                1)
            {
                fn_8019044C(sibling, 200.0f);
                return;
            }
            HSD_JObjSetFlagsAll(sibling, 0x10U);
            return;
        }
    }

    if ((s32) tm->cur_option != 0xB) {
        HSD_JObjSetFlagsAll(jobj, 0x10U);
        return;
    }

    fn_8018FF9C(jobj, 0.9f, 0.9f, 666.0f);
    child = (jobj != NULL) ? jobj->child : NULL;

    slot = lbl_804799B8.x2 + lbl_804799B8.x3;
    if ((s32) tm->x37[slot].x2 ==
        fn_8018F6DC(fn_8018F3BC((s32) idx)))
    {
        fn_8019044C(child,
                    (f32) (lbl_804799B8.xA + 0xA));
    } else {
        hud = fn_8018F6DC(fn_8018F3BC((s32) idx));
        if ((lbl_803D9D20.x72[hud] != 0) ||
            (fn_8018F3D0(fn_8018F310(fn_8018F6FC(hud))) != 2))
        {
            fn_8019044C(child, 0.0f);
        } else {
            HSD_JObjSetFlagsAll(child, 0x10U);
        }
    }

    sibling = (child != NULL) ? child->next : NULL;
    HSD_JObjClearFlagsAll(sibling, 0x10U);

    hud = fn_8018F6DC(fn_8018F3BC((s32) idx));
    if (lbl_803D9D20.x72[hud] != 0) {
        slot = lbl_804799B8.x2 + lbl_804799B8.x3;
        if ((s32) tm->x37[slot].x2 ==
            fn_8018F6DC(fn_8018F3BC((s32) idx)))
        {
            fn_8019044C(sibling,
                        (f32) ((tm->x37[slot].x6 * 0x1E) +
                               fn_8018F6DC(fn_8018F3BC((s32) idx))));
            return;
        }
        fn_8019044C(sibling,
                    (f32) fn_8018F6DC(fn_8018F3BC((s32) idx)));
        return;
    }

    if (fn_8018F3D0(fn_8018F310(fn_8018F3BC((s32) idx))) == 1) {
        fn_8019044C(sibling, 200.0f);
        return;
    }
    HSD_JObjSetFlagsAll(sibling, 0x10U);
}

/// Updates tournament menu cursor JObj visibility and position.
void fn_8019237C(HSD_GObj* gobj)
{
    TmData* tm;
    HSD_JObj* jobj;

    tm = gm_8018F634();
    jobj = gobj->hsd_obj;

    if (tm->cur_option <= 9) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, 0x10);

    if (tm->cur_option != 0xF) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    fn_8019044C(jobj, (f32) lbl_804799B8.xA);
    fn_8018FDC4(jobj,
                (7.1899996f * (f32) (lbl_804799B8.x5 % 4)) + -1.8f,
                -((2.3f * (f32) ((s32) lbl_804799B8.x5 / 4)) - 2.7f),
                666.0f);
}

/// @todo Currently 92.46% match - permuter couldn't improve
void fn_8019249C(HSD_GObj* gobj)
{
    TmData* tmdata;
    HSD_JObj* jobj;
    HSD_JObj* child;
    int cur_option;

    tmdata = gm_8018F634();
    jobj = gobj->hsd_obj;

    if (tmdata->cur_option <= 9) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    cur_option = tmdata->cur_option;
    if (cur_option != 0xD && cur_option != 0xE) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    child = HSD_JObjGetChild(jobj);
    child = HSD_JObjGetNext(child);
    child = HSD_JObjGetNext(child);
    child = HSD_JObjGetNext(child);
    child = HSD_JObjGetNext(child);
    child = HSD_JObjGetNext(child);
    child = HSD_JObjGetNext(child);
    child = HSD_JObjGetNext(child);
    child = HSD_JObjGetNext(child);
    child = HSD_JObjGetNext(child);
    child = HSD_JObjGetNext(child);

    if (cur_option == 0xD) {
        fn_8019044C(child, 0.0F);
        fn_8019044C(child, (f32) (lbl_804799B8.xA + 10));
    } else {
        fn_8019044C(child, (f32) (lbl_804799B8.xA + 10));
        fn_8019044C(child, 0.0F);
    }
}

#pragma push
#pragma dont_inline on
void fn_80192690(HSD_GObj* gobj)
{
    TmData* tmdata = gm_8018F634();
    HSD_JObj* jobj = gobj->hsd_obj;

    if (tmdata->cur_option <= 9) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }
    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    if (tmdata->cur_option < 0x11 || tmdata->cur_option > 0x12) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }
    fn_8018FDC4(jobj, 666.0F, 666.0F, 0.3F);
    fn_8019044C(jobj, tmdata->cur_option - 0x11);
}
#pragma pop

/// @todo Currently 96.8% match - permuter couldn't improve
void fn_80192758(HSD_GObj* gobj)
{
    TmData* tmdata;
    HSD_JObj* jobj;
    u8* data;
    u8* data2;
    u8* data3;
    HSD_JObj* child;
    u8 val;

    data = (u8*) &lbl_804799B8;
    tmdata = gm_8018F634();
    jobj = gobj->hsd_obj;

    if (tmdata->cur_option <= 9) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    if (data[0] == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    data2 = data + 2;
    data3 = data + 3;
    fn_8019044C(jobj, (float) tmdata->x37[data2[0] + data3[0]].x2);

    if (data[1] != 0) {
        child = (jobj == NULL) ? NULL : jobj->child;
        HSD_JObjClearFlags(child, JOBJ_HIDDEN);

        child = (jobj == NULL) ? NULL : jobj->child;
        child = (child == NULL) ? NULL : child->next;
        HSD_JObjClearFlags(child, JOBJ_HIDDEN);

        val = tmdata->x37[data2[0] + data3[0]].x2;
        if (val == 9) {
            child = (jobj == NULL) ? NULL : jobj->child;
            HSD_JObjSetFlags(child, JOBJ_HIDDEN);
            return;
        }
        if (val == 1) {
            child = (jobj == NULL) ? NULL : jobj->child;
            child = (child == NULL) ? NULL : child->next;
            HSD_JObjSetFlags(child, JOBJ_HIDDEN);
            return;
        }
    } else {
        child = (jobj == NULL) ? NULL : jobj->child;
        HSD_JObjSetFlags(child, JOBJ_HIDDEN);

        child = (jobj == NULL) ? NULL : jobj->child;
        child = (child == NULL) ? NULL : child->next;
        HSD_JObjSetFlags(child, JOBJ_HIDDEN);
    }
}

extern s32 lbl_804D665C;

s32 fn_80192938(void)
{
    TmData* tm;
    s32 i;
    s32 j;
    s32 start;
    s32 a, b;
    u8 tmp;
    u8 handicap;

    tm = gm_8018F634();
    lbl_804D6658 = 0;
    tm->cur_option = 9;

    if ((s32) gm_804771C4.match_type == 0) {
        tm->x2E = lbl_803D9D20.x0[tm->entrants];
        tm->x2F = (u8) tm->hmn_cpu_count;
    } else {
        tm->x2E = (u8) tm->combatants;
        tm->x2F = (u8) tm->combatants;
        tm->x30 = (u8) tm->entrants;
    }

    for (i = 0; i < 0x40; i++) {
        tm->x37[i].x4 = 0;
        tm->x37[i].xB = (u8) i;

        if ((u8) gmMainLib_8015CC34()->handicap == 1) {
            if ((s32) gm_804771C4.match_type == 0) {
                gmMainLib_8015CC34()->handicap = 0;
                tm->x37[i].x1 = 9;
            } else {
                tm->x37[i].x1 = 5;
            }
        } else {
            tm->x37[i].x1 = 9;
        }

        tm->x37[i].x2 = fn_8018F410();
        tm->x37[i].x6 = HSD_Randi(
            (s32) gm_80169238(fn_8018F6FC((enum CSSIconHud) tm->x37[i].x2)));

        if ((s32) (u8) i < (s32) tm->x2E) {
            ((u8*) &tm->x37[i])[-1] = 1;
            if ((s32) (u8) i < (s32) tm->x2F) {
                tm->x37[i].x0 = 0;
                tm->x37[i].x9 = (u16) (i + 0x320);
            } else {
                tm->x37[i].x0 = 1;
                tm->x37[i].x9 = (u16) ((i + 0x384) - tm->x2F);
                if (((s32) gm_804771C4.match_type == 0) &&
                    ((s32) tm->cpu_level == 0))
                {
                    tm->x37[i].x0 = HSD_Randi(9) + 1;
                } else {
                    tm->x37[i].x0 = (u8) tm->cpu_level;
                }
            }
        } else {
            ((u8*) &tm->x37[i])[-1] = 0;
            tm->x37[i].x0 = 3;
            tm->x37[i].x9 = 0x3E7;
        }
    }

    start = 0;
    tm->x4B8[0].x2 = 0;
    tm->x4B8[1].x2 = 0;
    tm->x4B8[2].x2 = 0;
    tm->x4B8[3].x2 = 0;

    if ((s32) gm_804771C4.match_type == 0) {
        if ((s32) lbl_804D665C < 2) {
            start = 1;
        }
        for (j = 0; j < 0x3E8; j++) {
            a = start + HSD_Randi(tm->x2E - start);
            b = start + HSD_Randi(tm->x2E - start);
            tmp = tm->x37[a].xB;
            tm->x37[a].xB = tm->x37[b].xB;
            tm->x37[b].xB = tmp;
        }
    }

    lbl_804799B8.x2 = 0;
    lbl_804799B8.x3 = 0;
    lbl_804799B8.x4 = 0xB;
    lbl_804799B8.x5 = 0;
    lbl_804799B8.x6 = 0;
    handicap = gmMainLib_8015CC34()->handicap;
    lbl_804799B8.x0 = handicap;
    tm->x24 = 0;
    tm->pad_x34[0] = 0xFF;
    tm->x33 = 0xFF;
    return (s32) handicap;
}

void fn_80192BB0(void)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    s32 i;
    f32 y;

    fn_8019035C(1, lbl_804D664C->models[2], 0, 0x1A, 2, 1,
                (void (*)(HSD_GObj*)) fn_8019175C, 0.0f);

    for (i = 0; i < 6; i++) {
        gobj = fn_8019035C(1, lbl_804D664C->models[3], 0, 0x1A, 2, 1,
                           fn_80191240, 0.0f);
        jobj = (HSD_JObj*) gobj->hsd_obj;
        fn_8018FBD8((void*) gobj, i);
        y = -((3.5f * (f32) i) - 11.5f);
        HSD_JObjSetTranslateY(jobj, y);

        gobj = fn_8019035C(1, lbl_804D664C->models[0], 0, 0x1A, 2, 1,
                           fn_801913BC, 0.0f);
        jobj = (HSD_JObj*) gobj->hsd_obj;
        fn_8018FBD8((void*) gobj, i);
        HSD_JObjSetTranslateY(jobj, y);

        gobj = fn_8019035C(1, lbl_804D664C->models[1], 0, 0x1A, 2, 1,
                           fn_80191678, 0.0f);
        jobj = (HSD_JObj*) gobj->hsd_obj;
        fn_8018FBD8((void*) gobj, i);
        HSD_JObjSetTranslateY(jobj, y);
    }
}

s32 fn_80192E6C(void)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    s32 i;
    s32 j;
    PAD_STACK(16);

    fn_8019035C(1, lbl_804D6650->models[4], 0, 0x1A, 2, 1, fn_801918F0,
                0.0f);
    fn_8019035C(1, lbl_804D6650->models[7], 0, 0x1A, 2, 1, fn_80191A54,
                0.0f);
    fn_8019035C(1, lbl_804D6650->models[5], 0, 0x1A, 2, 1,
                (void (*)(HSD_GObj*)) fn_80191B5C, 0.0f);
    fn_8019035C(1, lbl_804D6650->models[0], 0, 0x1A, 2, 1, fn_80191CA4,
                0.0f);
    fn_8019035C(1, lbl_804D6650->models[6], 0, 0x1A, 2, 1, fn_8019237C,
                0.0f);
    fn_8019035C(1, lbl_804D6650->models[10], 0, 0x1A, 2, 1, fn_8019249C,
                0.0f);
    jobj = (HSD_JObj*) fn_8019035C(1, lbl_804D6650->models[2], 0, 0x1A, 2,
                                    1, fn_80192758, 0.0f)->hsd_obj;
    HSD_JObjSetFlagsAll(jobj, 0x10U);

    for (i = 0; i < 0x40; i++) {
        gobj = fn_8019035C(1, lbl_804D6650->models[8], 0, 0x1A, 2, 1,
                           fn_80191D38, 0.0f);
        fn_8018FDC4((HSD_JObj*) gobj->hsd_obj, -12.300001f, 12.800008f,
                    666.0f);
        fn_8018FBD8((void*) gobj, i);

        gobj = fn_8019035C(1, lbl_804D6650->models[3], 0, 0x1A, 2, 1,
                           fn_80191E9C, 0.0f);
        jobj = (HSD_JObj*) gobj->hsd_obj;
        HSD_JObjSetFlagsAll(jobj, 0x10U);
        fn_8018FDC4(jobj, -12.300001f, 666.0f, 666.0f);
        fn_8018FBD8((void*) gobj, i);
    }

    for (j = 0; j <= 0x19; j++) {
        gobj = fn_8019035C(1, lbl_804D6650->models[9], 0, 0x1A, 2, 1,
                           (void (*)(HSD_GObj*)) fn_80191FD4, (f32) j);
        jobj = (HSD_JObj*) gobj->hsd_obj;
        if (j != 0x19) {
            fn_8018FF9C(jobj, 0.65f, 0.66f, 666.0f);
            fn_8018FDC4(jobj,
                        (6.0f * (f32) (j % 5)) + -3.0f,
                        -((4.500006f * (f32) (j / 5)) - 2.3f),
                        0.2f);
        } else {
            fn_8018FDC4(jobj, -1.0f, 10.099993f, 0.2f);
        }
        fn_8018FBD8((void*) gobj, j);
    }

    return (s32) fn_8019035C(1, lbl_804D6650->models[1], 0, 0x1A, 2, 1,
                              fn_80192690, 0.0f);
}

#pragma push
#pragma dont_inline on
void fn_80193230(void)
{
    HSD_GObj* gobj;
    HSD_Fog* fog;
    PAD_STACK(4);

    fn_8019035C(0, lbl_804D664C->models[5], 0, 0x1A, 2, 1, fn_801910E0, 0.0F);
    fn_8019035C(0, lbl_804D664C->models[4], 0, 0x1A, 2, 1, fn_80191154, 0.0F);
    fn_80192BB0();
    fn_80192E6C();
    gobj = GObj_Create(0xE, 0x1A, 0);
    fog = HSD_FogLoadDesc(lbl_804D664C->fogs[0].desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848, fog);
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0, 0);
}
#pragma pop

static s32 lbl_804DA78C = 0x46DC46FF;

void fn_80193308(void)
{
    s32 color;
    TmData* tm;
    HSD_Text* text;
    HSD_Text** ptr;
    f32 y;
    s32 i;
    s32 idx;
    s32 count;

    color = lbl_804DA78C;
    tm = gm_8018F634();

    tm->x4E0 = HSD_SisLib_803A5ACC(0, (s32) lbl_804D663C, 124.5f, 45.0f,
                                     0.0f, 391.0f, 30.0f);
    tm->x4E0->default_fitting = 1;
    HSD_SisLib_803A6368(tm->x4E0, 0x4A);

    tm->x4E4 = HSD_SisLib_803A5ACC(0, (s32) lbl_804D663C, 393.0f, 221.7f,
                                     0.0f, 360.0f, 40.0f);
    tm->x4E4->hidden = 1;

    for (i = 0; i < 6; i++) {
        tm->x4E8[i] = HSD_SisLib_803A5ACC(0, (s32) lbl_804D663C, 160.0f,
                                            48.0f, 0.0f, 360.0f, 40.0f);
        text = tm->x4E8[i];
        text->pos_x = 123.0f;
        y = (35.7f * (f32) i) + 113.0f;
        text->pos_y = y;
        text->pos_z = 0.0f;
        tm->x4E8[i]->hidden = 1;
        HSD_SisLib_803A6368(tm->x4E8[i], 0x5C);

        tm->x500[i] = HSD_SisLib_803A5ACC(0, (s32) lbl_804D663C, 160.0f,
                                            48.0f, 0.0f, 360.0f, 40.0f);
        text = tm->x500[i];
        text->pos_x = 343.0f;
        text->pos_y = y;
        text->pos_z = 0.0f;
        tm->x500[i]->hidden = 1;
        HSD_SisLib_803A6368(tm->x500[i], 0x53);
    }

    tm->x518[0] = HSD_SisLib_803A6754(0, (s32) lbl_804D663C);
    text = tm->x518[0];
    text->font_size.x = 0.5f;
    text->font_size.y = 0.5f;
    tm->x518[0]->default_kerning = 1;

    count = 0;
    idx = 1;
    do {
        ptr = &tm->x518[idx];
        *ptr = HSD_SisLib_803A6754(0, (s32) lbl_804D663C);
        text = *ptr;
        text->font_size.x = 0.58f;
        text->font_size.y = 0.55f;
        (*ptr)->default_kerning = 1;
        if (count != 0) {
            *(s32*) &(*ptr)->text_color = color;
        }
        count += 1;
        idx = 2;
    } while (count < 2);

    count = 0;
    idx = 3;
    do {
        ptr = &tm->x518[idx];
        *ptr = HSD_SisLib_803A6754(0, (s32) lbl_804D663C);
        text = *ptr;
        text->font_size.x = 0.85f;
        text->font_size.y = 1.35f;
        (*ptr)->default_kerning = 1;
        (*ptr)->default_alignment = 1;
        if (count != 0) {
            *(s32*) &(*ptr)->text_color = color;
        }
        count += 1;
        idx = 4;
    } while (count < 2);
}

/// #fn_801935B8

/// #fn_801937C4

/// #fn_80193B58

/// #fn_80193FCC

/// #fn_80194658

extern u8 lbl_803D9F80[];

/// @todo Currently 87.58% match - permuter couldn't improve
void fn_801949B4(s32* arg0, u32 arg1, u32 arg2)
{
    u8* table;
    s32 idx;
    s32* ptr;
    s32 val;
    u8* entry;

    if (arg1 & 0x40001) {
        lbAudioAx_80024030(2);
        lbl_804799B8.x7 = 5;
        table = lbl_803D9F80;

        idx = *arg0;
        ptr = arg0 + idx;
        entry = table + (idx << 1) + (gm_804771C4.match_type != 0);
        val = *++ptr;

        if (val > (s32) entry[0x40]) {
            *ptr = val - 1;
        } else {
            *ptr = (s32) entry[0x4C];
        }
    } else if (arg1 & 0x80002) {
        lbAudioAx_80024030(2);
        lbl_804799B8.x8 = 5;
        table = lbl_803D9F80;

        idx = *arg0;
        ptr = arg0 + idx;
        entry = table + (idx << 1) + (gm_804771C4.match_type != 0);
        val = *++ptr;

        if (val < (s32) entry[0x4C]) {
            *ptr = val + 1;
        } else {
            *ptr = (s32) entry[0x40];
        }
    }

    if (arg1 != 0) {
        if ((arg1 | arg2) & 0x300) {
            fn_80190ABC(0);
            fn_80190ABC(2);
            fn_80190ABC(1);
        }
        fn_80190ABC(3);
    }

    if (arg2 & 0x100) {
        lbAudioAx_80024030(1);
        if (gm_804771C4.match_type == 0) {
            *arg0 = *arg0 + 1;
        } else {
            *arg0 = 6;
        }
    } else if (arg2 & 0x200) {
        lbAudioAx_80024030(0);
        *arg0 = *arg0 - 1;
    }

    if (arg2 != 0) {
        if ((arg1 | arg2) & 0x300) {
            fn_80190ABC(0);
            fn_80190ABC(2);
            fn_80190ABC(1);
        }
        fn_80190ABC(3);
    }
}

/// @todo Currently 84.75% match - needs register allocation fix
void fn_80194BC4(s32* arg0, u32 arg1, u32 arg2)
{
    int* match_type_ptr;
    s16* data_ptr;
    s32 option;
    s32 value;
    s32* arr_ptr;
    s16* opt_ptr;
    u8* lookup_ptr;
    int match_type;
    s32 opt_x4, opt_x2;

    data_ptr = (s16*) lbl_803D9F80;
    match_type_ptr = &gm_804771C4.match_type;

    if (*match_type_ptr != 0) {
        return;
    }

    if (arg1 & 0x40001) {
        lbAudioAx_80024030(2);
        lbl_804799B8.x7 = 5;
        match_type = *match_type_ptr;
        option = *arg0;
        opt_x4 = option << 2;
        opt_x2 = option << 1;
        arr_ptr = (s32*) ((u8*) arg0 + opt_x4);
        opt_ptr = (s16*) ((u8*) data_ptr + opt_x2);
        value = *(++arr_ptr);
        lookup_ptr = (u8*) opt_ptr + !!match_type;
        if (value > lookup_ptr[0x40]) {
            *arr_ptr = value - 1;
        } else {
            *arr_ptr = lookup_ptr[0x4C];
        }
    } else if (arg1 & 0x80002) {
        lbAudioAx_80024030(2);
        lbl_804799B8.x8 = 5;
        match_type = *match_type_ptr;
        option = *arg0;
        opt_x4 = option << 2;
        opt_x2 = option << 1;
        arr_ptr = (s32*) ((u8*) arg0 + opt_x4);
        opt_ptr = (s16*) ((u8*) data_ptr + opt_x2);
        value = *(++arr_ptr);
        lookup_ptr = (u8*) opt_ptr + !!match_type;
        if (value < lookup_ptr[0x4C]) {
            *arr_ptr = value + 1;
        } else {
            *arr_ptr = lookup_ptr[0x40];
        }
    }

    if (arg1 != 0) {
        if ((arg1 | arg2) & 0x300) {
            fn_80190ABC(0);
        }
        fn_80190ABC(3);
    }

    if (arg2 & 0x100) {
        lbAudioAx_80024030(1);
        *arg0 = *arg0 + 1;
    } else if (arg2 & 0x200) {
        lbAudioAx_80024030(0);
        *arg0 = *arg0 - 1;
    }

    if (arg2 != 0) {
        if ((arg1 | arg2) & 0x300) {
            fn_80190ABC(0);
        }
        fn_80190ABC(3);
    }
}

/// @todo Currently 97.2% match - permuter couldn't improve
/// Handles button input for tournament mode menu navigation.
void fn_80194D84(s32* state, u32 buttons, u32 trigger)
{
    s32 cur_state;
    TmData* tm;

    if (buttons & 0x40001) {
        if (*state > 6) {
            lbAudioAx_80024030(2);
            *state -= 1;
        }
    } else if ((buttons & 0x80002) && (*state < 8)) {
        lbAudioAx_80024030(2);
        *state += 1;
    }

    if ((buttons != 0) && ((buttons | trigger) & 0x300)) {
        fn_80190ABC(0);
    }

    if (trigger & 0x1100) {
        lbAudioAx_80024030(1);
        fn_8018EC7C();
        cur_state = *state;
        if (cur_state == 6) {
            fn_80192938();
        } else if (cur_state == 7) {
            tm = gm_8018F634();
            tm->x20 = 1;
            HSD_SisLib_803A5E70();
            mn_8022F138(0x19, 0x1C);
            mn_8022F138(0x12, 0x15);
            if (gm_804771C4.match_type == 0) {
                mn_802317E4(lbl_804D6648, 0);
            } else {
                mn_802317E4(lbl_804D6648, 1);
            }
            return;
        } else {
            *state = 0;
        }
    } else if (trigger & 0x200) {
        lbAudioAx_80024030(0);
        if (gm_804771C4.match_type == 0) {
            *state = 5;
        } else {
            *state = 4;
        }
    }

    if ((trigger != 0) && ((buttons | trigger) & 0x300)) {
        fn_80190ABC(0);
    }
}

static s32 lbl_804D6654;

/// Handles tournament settings menu input (entrant configuration).
void fn_80194F30(s32* state_ptr, u32 buttons, u32 trigger)
{
    TmData* tm = (TmData*) state_ptr;
    s32 idx;

    if (trigger & 0x1000) {
        lbAudioAx_80024030(1);
        lbl_804D6654 = tm->cur_option;
        tm->cur_option = 0x11;
        return;
    }

    if (buttons & 0x40001) {
        switch (tm->cur_option) {
        case 12:
            lbAudioAx_80024030(2);
            tm->cur_option = 0xA;
            break;
        case 16:
            lbAudioAx_80024030(2);
            tm->cur_option = 0xC;
            lbl_804799B8.x1 = 0;
            break;
        }
    } else if (buttons & 0x80002) {
        switch (tm->cur_option) {
        case 11:
            break;
        case 10:
            lbAudioAx_80024030(2);
            tm->cur_option = 0xC;
            break;
        case 12:
            if (lbl_804799B8.x0 != 0) {
                lbAudioAx_80024030(2);
                tm->cur_option = 0x10;
            }
            break;
        }
    } else if (buttons & 0x10008) {
        idx = lbl_804799B8.x2 + lbl_804799B8.x3;
        if (tm->cur_option != 0x10 || lbl_804799B8.x1 == 0) {
            if (lbl_804799B8.x2 != 0) {
                lbAudioAx_80024030(2);
                lbl_804799B8.x2 -= 1;
                fn_80190ABC(5);
            } else if (lbl_804799B8.x3 != 0) {
                lbAudioAx_80024030(2);
                lbl_804799B8.x3 -= 1;
                lbl_804799B8.x4 -= 1;
                fn_80190ABC(5);
                fn_80190ABC(6);
            }
        } else if (tm->x37[idx].x2 > 1) {
            lbAudioAx_80024030(2);
            tm->x37[idx].x2 -= 1;
        }
    } else if (buttons & 0x20004) {
        idx = lbl_804799B8.x2 + lbl_804799B8.x3;
        if (tm->cur_option != 0x10 || lbl_804799B8.x1 == 0) {
            if (lbl_804799B8.x2 < 0xB) {
                if (lbl_804799B8.x2 + lbl_804799B8.x3 < tm->x2E - 1) {
                    lbAudioAx_80024030(2);
                    lbl_804799B8.x2 += 1;
                    fn_80190ABC(5);
                }
            } else if (lbl_804799B8.x2 + lbl_804799B8.x3 < tm->x2E - 1) {
                lbAudioAx_80024030(2);
                lbl_804799B8.x3 += 1;
                lbl_804799B8.x4 += 1;
                fn_80190ABC(5);
                fn_80190ABC(6);
            }
        } else if (tm->x37[idx].x2 < 9) {
            lbAudioAx_80024030(2);
            tm->x37[idx].x2 += 1;
        }
    }

    if (trigger & 0x100) {
        idx = lbl_804799B8.x2 + lbl_804799B8.x3;
        switch (tm->cur_option) {
        case 12:
        case 10:
            lbAudioAx_80024030(1);
            tm->x37[idx].x4 = tm->x37[idx].x3;
            tm->x37[idx].x8 = tm->x37[idx].x7;
            tm->x37[idx].xB = tm->x37[idx].x9;
            tm->x37[idx].x6 = tm->x37[idx].x5;
            tm->cur_option += 1;
            return;
        case 16:
            if (lbl_804799B8.x0 != 1) {
                if (lbl_804799B8.x1 != 1) {
                    lbAudioAx_80024030(1);
                }
                lbl_804799B8.x1 = 1;
                return;
            }
            break;
        }
    } else if (trigger & 0x200) {
        lbAudioAx_80024030(0);
        if (tm->cur_option != 0x10 || lbl_804799B8.x1 == 0) {
            tm->cur_option = 6;
            lbl_804799B8.xE = 0;
            if (gm_804771C4.match_type == 0) {
                TmData* tmdata = gm_8018F634();
                fn_8018EC7C();
                fn_8018E618(tmdata->entrants, 1, 4.5f);
                fn_80190480(130.0f);
                fn_80190520(-278.0f, 255.0f, 0.0f);
            }
        } else {
            lbl_804799B8.x1 = 0;
        }
    }
}

/// Handles character selection input for tournament bracket.
void fn_801953C8(s32* state_ptr, u32 buttons, u32 trigger)
{
    TmData* tm = (TmData*) state_ptr;
    s32 idx;
    s32 cur_pos;
    s32 candidate;
    s32 group;
    s32 step;
    s32 adj;
    s32 occupied;
    s32 i;

    idx = lbl_804799B8.x2 + lbl_804799B8.x3;
    cur_pos = fn_8018F310(fn_8018F6FC(tm->x37[idx].x3));

    if (trigger & 0x1000) {
        lbAudioAx_80024030(0);
        idx = lbl_804799B8.x2 + lbl_804799B8.x3;
        tm->x37[idx].x3 = tm->x37[idx].x4;
        idx = lbl_804799B8.x2 + lbl_804799B8.x3;
        tm->x37[idx].x7 = tm->x37[idx].x8;
        idx = lbl_804799B8.x2 + lbl_804799B8.x3;
        tm->x37[idx].x5 = tm->x37[idx].x6;
        lbl_804D6654 = *state_ptr;
        *state_ptr = 0x11;
        return;
    }

    if (buttons & 0x40001) {
        group = (cur_pos / 5) * 5;
        for (i = 1; i < 5; i++) {
            candidate = cur_pos - i;
            if (candidate < group) {
                candidate += 5;
            }
            adj = fn_8018F6DC(fn_8018F3BC(candidate));
            if (lbl_803D9D20.x72[adj] != 0) {
                occupied = 1;
            } else if (fn_8018F3D0(fn_8018F310(fn_8018F6FC(adj))) == 2) {
                occupied = 0;
            } else {
                occupied = 1;
            }
            if (occupied) {
                lbAudioAx_80024030(2);
                idx = lbl_804799B8.x2 + lbl_804799B8.x3;
                tm->x37[idx].x7 = 0;
                idx = lbl_804799B8.x2 + lbl_804799B8.x3;
                tm->x37[idx].x5 = 0;
                idx = lbl_804799B8.x2 + lbl_804799B8.x3;
                tm->x37[idx].x3 = fn_8018F6DC(fn_8018F3BC(candidate));
                break;
            }
        }
    } else if (buttons & 0x80002) {
        group = ((cur_pos / 5) + 1) * 5;
        for (i = 1; i < 5; i++) {
            candidate = cur_pos + i;
            if (candidate >= group) {
                candidate -= 5;
            }
            adj = fn_8018F6DC(fn_8018F3BC(candidate));
            if (lbl_803D9D20.x72[adj] != 0) {
                occupied = 1;
            } else if (fn_8018F3D0(fn_8018F310(fn_8018F6FC(adj))) == 2) {
                occupied = 0;
            } else {
                occupied = 1;
            }
            if (occupied) {
                lbAudioAx_80024030(2);
                idx = lbl_804799B8.x2 + lbl_804799B8.x3;
                tm->x37[idx].x7 = 0;
                idx = lbl_804799B8.x2 + lbl_804799B8.x3;
                tm->x37[idx].x5 = 0;
                idx = lbl_804799B8.x2 + lbl_804799B8.x3;
                tm->x37[idx].x3 = fn_8018F6DC(fn_8018F3BC(candidate));
                break;
            }
        }
    } else if (buttons & 0x10008) {
        step = 5;
        for (i = 1; i < 5; i++) {
            candidate = cur_pos - step;
            if (candidate < 0) {
                candidate += 25;
            }
            adj = fn_8018F6DC(fn_8018F3BC(candidate));
            if (lbl_803D9D20.x72[adj] != 0) {
                occupied = 1;
            } else if (fn_8018F3D0(fn_8018F310(fn_8018F6FC(adj))) == 2) {
                occupied = 0;
            } else {
                occupied = 1;
            }
            if (occupied) {
                lbAudioAx_80024030(2);
                idx = lbl_804799B8.x2 + lbl_804799B8.x3;
                tm->x37[idx].x7 = 0;
                idx = lbl_804799B8.x2 + lbl_804799B8.x3;
                tm->x37[idx].x5 = 0;
                idx = lbl_804799B8.x2 + lbl_804799B8.x3;
                tm->x37[idx].x3 = fn_8018F6DC(fn_8018F3BC(candidate));
                break;
            }
            step += 5;
        }
    } else if (buttons & 0x20004) {
        step = cur_pos + 5;
        for (i = 1; i < 5; i++) {
            candidate = step;
            if (candidate >= 25) {
                candidate -= 25;
            }
            adj = fn_8018F6DC(fn_8018F3BC(candidate));
            if (lbl_803D9D20.x72[adj] != 0) {
                occupied = 1;
            } else if (fn_8018F3D0(fn_8018F310(fn_8018F6FC(adj))) == 2) {
                occupied = 0;
            } else {
                occupied = 1;
            }
            if (occupied) {
                lbAudioAx_80024030(2);
                idx = lbl_804799B8.x2 + lbl_804799B8.x3;
                tm->x37[idx].x7 = 0;
                idx = lbl_804799B8.x2 + lbl_804799B8.x3;
                tm->x37[idx].x5 = 0;
                idx = lbl_804799B8.x2 + lbl_804799B8.x3;
                tm->x37[idx].x3 = fn_8018F6DC(fn_8018F3BC(candidate));
                break;
            }
            step += 5;
        }
    }

    if (trigger & 0x100) {
        if ((fn_8018F6A8(4) & 0x40) && (fn_8018F6A8(4) & 0x20) &&
            gm_804771C4.match_type != 0)
        {
            idx = lbl_804799B8.x2 + lbl_804799B8.x3;
            if (lbl_803D9D20.x72[tm->x37[idx].x3] == 0) {
                lbAudioAx_80024030(3);
                return;
            }
            lbAudioAx_80024030(1);
            idx = lbl_804799B8.x2 + lbl_804799B8.x3;
            tm->x37[idx].x5 = 1;
            *state_ptr -= 1;
            return;
        }
        idx = lbl_804799B8.x2 + lbl_804799B8.x3;
        if (lbl_803D9D20.x72[tm->x37[idx].x3] == 0) {
            lbAudioAx_80024030(3);
            return;
        }
        lbAudioAx_80024030(1);
        *state_ptr -= 1;
        idx = lbl_804799B8.x2 + lbl_804799B8.x3;
        if (tm->x37[idx].x5 != 0) {
            tm->x37[idx].x5 = 0;
        }
    } else if (trigger & 0x200) {
        lbAudioAx_80024030(0);
        idx = lbl_804799B8.x2 + lbl_804799B8.x3;
        tm->x37[idx].x3 = tm->x37[idx].x4;
        idx = lbl_804799B8.x2 + lbl_804799B8.x3;
        tm->x37[idx].x7 = tm->x37[idx].x8;
        idx = lbl_804799B8.x2 + lbl_804799B8.x3;
        tm->x37[idx].x5 = tm->x37[idx].x6;
        *state_ptr -= 1;
    } else if (trigger & 0x400) {
        idx = lbl_804799B8.x2 + lbl_804799B8.x3;
        adj = (u8) gm_80169238((u8) fn_8018F6FC(tm->x37[idx].x3));
        idx = lbl_804799B8.x2 + lbl_804799B8.x3;
        if ((s32) tm->x37[idx].x7 < adj - 1) {
            lbAudioAx_80024030(2);
            idx = lbl_804799B8.x2 + lbl_804799B8.x3;
            tm->x37[idx].x7++;
        }
    } else if (trigger & 0x800) {
        idx = lbl_804799B8.x2 + lbl_804799B8.x3;
        if (tm->x37[idx].x7 != 0) {
            lbAudioAx_80024030(2);
            idx = lbl_804799B8.x2 + lbl_804799B8.x3;
            tm->x37[idx].x7--;
        }
    }
}

/// @todo Currently 93.5% match - permuter couldn't improve
/// Handles name entry/selection input for tournament mode.
void fn_80195AF0(s32* state_ptr, u32 buttons, u32 trigger)
{
    u8* ptr;
    u8* page_ptr;
    u8* row_ptr;
    u8* col_ptr;
    s32 cur_state;

    ptr = (u8*) &lbl_804799B8;

    if (trigger & 0x1000) {
        lbl_804D6654 = *state_ptr;
        *state_ptr = 0x11;
        return;
    }

    if (buttons & 0x40001) {
        if (*state_ptr == 0xE) {
            lbAudioAx_80024030(2);
            *state_ptr = 0xD;
        }
    } else if ((buttons & 0x80002) && (*state_ptr == 0xD)) {
        lbAudioAx_80024030(2);
        *state_ptr = 0xE;
    }

    if (trigger & 0x100) {
        u16* arr;

        lbAudioAx_80024030(1);
        col_ptr = &lbl_804799B8.x2;
        row_ptr = &lbl_804799B8.x3;
        arr = (u16*) ((u8*) state_ptr + (lbl_804799B8.x2 + lbl_804799B8.x3) * 0x12);
        arr[0x21] = arr[0x20];
        cur_state = *state_ptr;
        switch (cur_state) {
        case 0xD:
            if (IsNameListFull() == 0) {
                TmData* tm = gm_8018F634();
                tm->x20 = 1;
                HSD_SisLib_803A5E70();
                mn_8022F138(0x19, 0x1C);
                mn_8022F138(0x12, 0x15);
                mnNameNew_8023EA08((UNK_T) lbl_804D6648);
            }
            return;
        case 0xE:
            page_ptr = &lbl_804799B8.x6;
            if (GetNameText(lbl_804799B8.x5 + (lbl_804799B8.x6 * 4)) != NULL) {
                s32 idx = (*col_ptr + *row_ptr) * 0x12;
                s16 val = lbl_804799B8.x5 + (*page_ptr * 4);
                ((u16*) ((u8*) state_ptr + idx))[0x20] = val;
            }
            *state_ptr = 0xF;
            fn_80190ABC(4);
            return;
        }
        return;
    }

    if (trigger & 0x200) {
        u16* arr;

        lbAudioAx_80024030(0);
        arr = (u16*) ((u8*) state_ptr + (lbl_804799B8.x2 + lbl_804799B8.x3) * 0x12);
        arr[0x20] = arr[0x21];
        fn_80190ABC(5);
        fn_80190ABC(6);
        *state_ptr = 0xC;
    }
}

void fn_80195CCC(s32* arg, u32 buttons, u32 trigger)
{
    u8* ptr = (u8*) &lbl_804799B8;
    u16* arr;
    s32 selected;
    s32 slot;
    TmData* tm;
    u8 count;
    s32 i;
    s32 unique;

    PAD_STACK(16);

    if (buttons & 0x40001) {
        lbAudioAx_80024030(2);
        if ((ptr[5] % 4) != 0) {
            ptr[5] = (u8) (ptr[5] - 1);
            arr = (u16*) ((u8*) arg + (ptr[2] + ptr[3]) * 0x12);
            arr[0x20] = (s16) (ptr[5] + (ptr[6] * 4));
            fn_80190ABC(5);
            fn_80190ABC(4);
        }
    } else if (buttons & 0x80002) {
        lbAudioAx_80024030(2);
        if (((s32) (ptr[5] % 4) < 3) &&
            ((s32) (ptr[5] + ((ptr[6] * 4) + 1)) < GetNameCount()))
        {
            ptr[5] = (u8) (ptr[5] + 1);
            arr = (u16*) ((u8*) arg + (ptr[2] + ptr[3]) * 0x12);
            arr[0x20] = (s16) (ptr[5] + (ptr[6] * 4));
            fn_80190ABC(5);
            fn_80190ABC(4);
        }
    } else if (buttons & 0x10008) {
        lbAudioAx_80024030(2);
        if (((s32) ptr[5] / 4) != 0) {
            ptr[5] = (u8) (ptr[5] - 4);
            arr = (u16*) ((u8*) arg + (ptr[2] + ptr[3]) * 0x12);
            arr[0x20] = (s16) (ptr[5] + (ptr[6] * 4));
            fn_80190ABC(5);
            fn_80190ABC(4);
        } else if ((u8) ptr[6] != 0) {
            ptr[6] = (u8) (ptr[6] - 1);
            arr = (u16*) ((u8*) arg + (ptr[2] + ptr[3]) * 0x12);
            arr[0x20] = (s16) (ptr[5] + (ptr[6] * 4));
            fn_80190ABC(5);
            fn_80190ABC(4);
        }
    } else if (buttons & 0x20004) {
        lbAudioAx_80024030(2);
        if ((s32) ((s32) ptr[5] / 4) < 8) {
            if ((s32) (ptr[5] + ((ptr[6] * 4) + 4)) < GetNameCount()) {
                ptr[5] = (u8) (ptr[5] + 4);
                arr = (u16*) ((u8*) arg + (ptr[2] + ptr[3]) * 0x12);
                arr[0x20] = (s16) (ptr[5] + (ptr[6] * 4));
            }
            fn_80190ABC(5);
            fn_80190ABC(4);
        } else if ((s32) (ptr[5] + ((ptr[6] * 4) + 4)) < GetNameCount()) {
            ptr[6] = (u8) (ptr[6] + 1);
            arr = (u16*) ((u8*) arg + (ptr[2] + ptr[3]) * 0x12);
            arr[0x20] = (s16) (ptr[5] + (ptr[6] * 4));
            fn_80190ABC(5);
            fn_80190ABC(4);
        }
    }

    if (trigger & 0x100) {
        if (GetNameText(ptr[5] + (ptr[6] * 4)) != NULL) {
            selected = ptr[5] + (ptr[6] * 4);
            slot = ptr[2] + ptr[3];
            tm = gm_8018F634();
            count = tm->x2E;
            unique = 0;
            i = 0;
            if ((s32) count > 0) {
                for (;;) {
                    if ((i != slot) &&
                        (selected == (s32) tm->x37[unique].x9))
                    {
                        unique = 0;
                        break;
                    }
                    unique++;
                    i++;
                    count--;
                    if (count == 0) {
                        unique = 1;
                        break;
                    }
                }
            } else {
                unique = 1;
            }
            if (unique != 0) {
                lbAudioAx_80024030(1);
                arr = (u16*) ((u8*) arg +
                              (lbl_804799B8.x2 + lbl_804799B8.x3) *
                                  0x12);
                arr[0x20] =
                    (s16) (lbl_804799B8.x5 + (lbl_804799B8.x6 * 4));
                fn_80190ABC(5);
                fn_80190ABC(6);
                *arg = 0xC;
                return;
            }
            lbAudioAx_80024030(3);
            return;
        }
        lbAudioAx_80024030(3);
        return;
    }

    if (trigger & 0x200) {
        u16* arr2;

        lbAudioAx_80024030(0);
        arr2 = (u16*) ((u8*) arg +
                        (lbl_804799B8.x2 + lbl_804799B8.x3) * 0x12);
        arr2[0x20] = arr2[0x21];
        fn_80190ABC(5);
        fn_80190ABC(6);
        *arg = 0xE;
    }
}

/// @todo Currently 96.88% match - needs minor register allocation fix
/// Handles confirm/cancel input for tournament start.
/// Type casts used to match target sth instruction patterns.
void fn_8019610C(s32* state, u32 buttons, u32 trigger)
{
    TmData* td;
    s32 i;
    u8* src_ptr;
    u8* dst_ptr;
    s32 base_val;

    i = 1;

    if (buttons & 0x10008) {
        if (*state == 0x12) {
            lbAudioAx_80024030(2);
            *state = 0x11;
        }
    } else if ((buttons & 0x20004) != 0) {
        if (*state == 0x11) {
            lbAudioAx_80024030(2);
            *state = 0x12;
        }
    }

    if ((trigger & 0x1100) != 0) {
        if (*state == 0x11) {
            lbAudioAx_80024030(i);
            if (gm_804771C4.match_type == 0) {
                gm_SetScenePendingMinor(1);
            } else {
                td = gm_8018F634();
                i = 0;
                src_ptr = (u8*) td;
                dst_ptr = (u8*) td;
                base_val = i;
                while (i < td->x2E) {
                    src_ptr[0x45] = src_ptr[0x44];
                    src_ptr[0x46] = base_val;
                    if (i < td->x30) {
                        *(u16*) &dst_ptr[0x4BE] = *(u16*) &src_ptr[0x40];
                        dst_ptr[0x4BD] = src_ptr[0x39];
                        dst_ptr[0x4B9] = src_ptr[0x3A];
                        dst_ptr[0x4B8] = src_ptr[0x37];
                        dst_ptr[0x4BB] = src_ptr[0x3E];
                        dst_ptr[0x4BA] = src_ptr[0x3C];
                    }
                    src_ptr += 0x12;
                    dst_ptr += 0xA;
                    i++;
                }
                gm_SetScenePendingMinor(2);
            }
            gm_801A4B60();
        } else {
            lbAudioAx_80024030(0);
            *state = lbl_804D6654;
        }
    } else if ((trigger & 0x200) != 0) {
        lbAudioAx_80024030(0);
        *state = lbl_804D6654;
    }
}

/// Tournament Mode per-frame update handler.
void gm_8019628C_OnFrame(void)
{
    TmData* tm;
    u32 r30;
    u32 r29;
    s32 cur_option;

    tm = gm_8018F634();
    r30 = fn_8018F674(4);
    r29 = fn_8018F640(4);

    if (mn_8022F218() != 0) {
        lbAudioAx_80024030(0);
        HSD_SisLib_803A5E70();
        mn_8022F138(1, 8);
        mn_8022F138(0x19, 0x1C);
        mn_8022F138(0x12, 0x15);
        mn_8022F268();
        gm_801A4B60();
        gm_801A42F8(1);
        return;
    }

    if (tm->x20 != 0) {
        return;
    }

    lbl_804799B8.xA = (u8) ((lbl_804799B8.xA + 1) % 11);

    cur_option = tm->cur_option;
    if (cur_option >= 9 && cur_option <= 9) {
        return;
    }
    if (cur_option >= 0x13) {
        return;
    }
    lbl_803D9FD8[cur_option]((s32*) tm, r30, r29);
}

extern struct {
    UNK_T x0;
    UNK_T x4;
    UNK_T x8;
} lbl_804771B8;

void gm_801963B4_OnEnter(void* arg0)
{
    const char* filename;
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 8);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
    lbl_804D6640 = lbArchive_80016DBC("GmTou1p", &lbl_804D664C,
                                      "ScGamTour_scene_data", 0);
    lbl_804D6644 = lbArchive_80016DBC("GmTou2p", &lbl_804D6650,
                                      "ScGamTour_scene_data", 0);
    lbl_804D6648 = lbArchive_LoadArchive("MnExtAll");
    filename = "TmBox.dat";
    lbl_804D6638 = lbArchive_80016DBC(
        filename, &lbl_804771B8.x0, "tournament_box2_array", &lbl_804771B8.x4,
        "tournament_box3_array", &lbl_804771B8.x8, "tournament_box4_array", 0);
    HSD_SisLib_803A62A0(0, fn_8018F5F0(), "SIS_TournamentData");
    fn_801935B8();
    lbAudioAx_800237A8(0x7539, 0x7F, 0x40);
    lbAudioAx_80023F28(gmMainLib_8015ECB0());
}

/// Scene OnLeave callback for gm_18A5. Frees archive resources.
void gm_801964A4_OnLeave(UNK_T arg)
{
    (void) arg;
    lbArchive_80016EFC(lbl_804D6640);
    lbArchive_80016EFC(lbl_804D6644);
    lbArchive_80016EFC(lbl_804D6648);
    lbArchive_80016EFC(lbl_804D6638);
    gm_8018F634()->cur_option = 0x13;
    gm_8018F634()->x2C = 1;
    gm_8018F634()->x31 = lbl_804799B8.x0;
}

void fn_80196510(void)
{
    int stage;

    gm_8018F634();

    while (1) {
        stage = mnStageSel_8025BBD4();
        lbl_804D4190 = stage;
        if (lbl_804D4194 != lbl_804D4190) {
            break;
        }
        if (fn_801642A0() != 0) {
            break;
        }
    }

    lbl_804D4194 = lbl_804D4190;
}

s32 fn_8019655C(void)
{
    return lbl_804D4190;
}

bool fn_80196564(TmData* arg0)
{
    if ((arg0->stage_selection_type == 0 && arg0->x32 == 0) ||
        arg0->stage_selection_type == 1)
    {
        return true;
    }
    return false;
}

bool fn_80196594(TmData* arg0)
{
    if ((arg0->stage_selection_type == 2 && arg0->x32 == 0) ||
        arg0->stage_selection_type == 3)
    {
        return true;
    }
    return false;
}

void fn_801965C4(void)
{
    TmData* temp_r3;
    int temp_r4;

    temp_r3 = gm_8018F634();
    temp_r3->x2D = 1;
    temp_r4 = temp_r3->stage_selection_type;

    if (fn_80196594(temp_r3)) {
        temp_r3->x32 = 1;
        gm_SetScenePendingMinor(3);
        gm_801A4B60();
        return;
    }
    if (fn_80196564(temp_r3)) {
        temp_r3->x32 = 1;
        temp_r3->x28 = lbl_804D4190;
    }
    gm_SetScenePendingMinor(4);
    gm_801A4B60();
}

/// Randomly assigns bracket positions for tournament seeding.
void fn_80196684(s32 bracket_idx)
{
    s32 rand_val = HSD_Randi(lbl_80473AB8[bracket_idx].x51 +
                             lbl_80473AB8[bracket_idx].x7D +
                             lbl_80473AB8[bracket_idx].xA9);

    if (rand_val < (s32) lbl_80473AB8[bracket_idx].x51) {
        lbl_80473AB8[bracket_idx].x4C = 0;
        if (HSD_Randi(lbl_80473AB8[bracket_idx].x7D +
                      lbl_80473AB8[bracket_idx].xA9) <
            (s32) lbl_80473AB8[bracket_idx].x7D)
        {
            lbl_80473AB8[bracket_idx].x78 = 1;
            lbl_80473AB8[bracket_idx].xA4 = 2;
            return;
        }
        lbl_80473AB8[bracket_idx].x78 = 2;
        lbl_80473AB8[bracket_idx].xA4 = 1;
        return;
    }
    if (rand_val < (s32) (lbl_80473AB8[bracket_idx].x51 +
                          lbl_80473AB8[bracket_idx].x7D))
    {
        lbl_80473AB8[bracket_idx].x78 = 0;
        if (HSD_Randi(lbl_80473AB8[bracket_idx].x51 +
                      lbl_80473AB8[bracket_idx].xA9) <
            (s32) lbl_80473AB8[bracket_idx].x51)
        {
            lbl_80473AB8[bracket_idx].x4C = 1;
            lbl_80473AB8[bracket_idx].xA4 = 2;
            return;
        }
        lbl_80473AB8[bracket_idx].x4C = 2;
        lbl_80473AB8[bracket_idx].xA4 = 1;
        return;
    }
    lbl_80473AB8[bracket_idx].xA4 = 0;
    if (HSD_Randi(lbl_80473AB8[bracket_idx].x51 +
                  lbl_80473AB8[bracket_idx].x7D) <
        (s32) lbl_80473AB8[bracket_idx].x51)
    {
        lbl_80473AB8[bracket_idx].x4C = 1;
        lbl_80473AB8[bracket_idx].x78 = 2;
        return;
    }
    lbl_80473AB8[bracket_idx].x4C = 2;
    lbl_80473AB8[bracket_idx].x78 = 1;
}

/// #fn_801967E0

s32 fn_801967E0(s32 arg0)
{
    s32 rand;
    u8 w0, w1, w2, w3;

    w0 = lbl_80473AB8[arg0].x51;
    w1 = lbl_80473AB8[arg0].x7D;
    w2 = lbl_80473AB8[arg0].xA9;
    w3 = lbl_80473AB8[arg0].xD5;

    rand = HSD_Randi(w0 + w1 + w2 + w3);

    if (rand < (s32) w0) {
        lbl_80473AB8[arg0].x4C = 0;
        rand = HSD_Randi(w1 + w2 + w3);
        if (rand < (s32) w1) {
            lbl_80473AB8[arg0].x78 = 1;
            rand = HSD_Randi(w2 + w3);
            if (rand < (s32) w2) {
                lbl_80473AB8[arg0].xA4 = 2;
                lbl_80473AB8[arg0].xD0 = 3;
                return rand;
            }
            lbl_80473AB8[arg0].xA4 = 3;
            lbl_80473AB8[arg0].xD0 = 2;
            return rand;
        }
        if (rand < (s32) (w1 + w2)) {
            lbl_80473AB8[arg0].xA4 = 1;
            rand = HSD_Randi(w1 + w3);
            if (rand < (s32) w1) {
                lbl_80473AB8[arg0].x78 = 2;
                lbl_80473AB8[arg0].xD0 = 3;
                return rand;
            }
            lbl_80473AB8[arg0].x78 = 3;
            lbl_80473AB8[arg0].xD0 = 2;
            return rand;
        }
        lbl_80473AB8[arg0].xD0 = 1;
        rand = HSD_Randi(w1 + w2);
        if (rand < (s32) w2) {
            lbl_80473AB8[arg0].x78 = 2;
            lbl_80473AB8[arg0].xA4 = 3;
            return rand;
        }
        lbl_80473AB8[arg0].x78 = 3;
        lbl_80473AB8[arg0].xA4 = 2;
        return rand;
    }

    if (rand < (s32) (w0 + w1)) {
        lbl_80473AB8[arg0].x78 = 0;
        rand = HSD_Randi(w0 + w2 + w3);
        if (rand < (s32) w0) {
            lbl_80473AB8[arg0].x4C = 1;
            rand = HSD_Randi(w2 + w3);
            if (rand < (s32) w2) {
                lbl_80473AB8[arg0].xA4 = 2;
                lbl_80473AB8[arg0].xD0 = 3;
                return rand;
            }
            lbl_80473AB8[arg0].xA4 = 3;
            lbl_80473AB8[arg0].xD0 = 2;
            return rand;
        }
        if (rand < (s32) (w0 + w2)) {
            lbl_80473AB8[arg0].xA4 = 1;
            rand = HSD_Randi(w0 + w3);
            if (rand < (s32) w0) {
                lbl_80473AB8[arg0].x4C = 2;
                lbl_80473AB8[arg0].xD0 = 3;
                return rand;
            }
            lbl_80473AB8[arg0].x4C = 3;
            lbl_80473AB8[arg0].xD0 = 2;
            return rand;
        }
        lbl_80473AB8[arg0].xD0 = 1;
        rand = HSD_Randi(w0 + w2);
        if (rand < (s32) w0) {
            lbl_80473AB8[arg0].x4C = 2;
            lbl_80473AB8[arg0].xA4 = 3;
            return rand;
        }
        lbl_80473AB8[arg0].x4C = 3;
        lbl_80473AB8[arg0].xA4 = 2;
        return rand;
    }

    if (rand < (s32) (w2 + w0 + w1)) {
        lbl_80473AB8[arg0].xA4 = 0;
        rand = HSD_Randi(w0 + w1 + w3);
        if (rand < (s32) w0) {
            lbl_80473AB8[arg0].x4C = 1;
            rand = HSD_Randi(w1 + w3);
            if (rand < (s32) w1) {
                lbl_80473AB8[arg0].x78 = 2;
                lbl_80473AB8[arg0].xD0 = 3;
                return rand;
            }
            lbl_80473AB8[arg0].x78 = 3;
            lbl_80473AB8[arg0].xD0 = 2;
            return rand;
        }
        if (rand < (s32) (w0 + w1)) {
            lbl_80473AB8[arg0].x78 = 1;
            rand = HSD_Randi(w0 + w3);
            if (rand < (s32) w0) {
                lbl_80473AB8[arg0].x4C = 2;
                lbl_80473AB8[arg0].xD0 = 3;
                return rand;
            }
            lbl_80473AB8[arg0].x4C = 3;
            lbl_80473AB8[arg0].xD0 = 2;
            return rand;
        }
        lbl_80473AB8[arg0].xD0 = 1;
        rand = HSD_Randi(w0 + w1);
        if (rand < (s32) w0) {
            lbl_80473AB8[arg0].x4C = 2;
            lbl_80473AB8[arg0].x78 = 3;
            return rand;
        }
        lbl_80473AB8[arg0].x4C = 3;
        lbl_80473AB8[arg0].x78 = 2;
        return rand;
    }

    lbl_80473AB8[arg0].xD0 = 0;
    rand = HSD_Randi(w0 + w1 + w2);
    if (rand < (s32) w0) {
        lbl_80473AB8[arg0].x4C = 1;
        rand = HSD_Randi(w1 + w2);
        if (rand < (s32) w1) {
            lbl_80473AB8[arg0].x78 = 2;
            lbl_80473AB8[arg0].xA4 = 3;
            return rand;
        }
        lbl_80473AB8[arg0].x78 = 3;
        lbl_80473AB8[arg0].xA4 = 2;
        return rand;
    }
    if (rand < (s32) (w0 + w1)) {
        lbl_80473AB8[arg0].x78 = 1;
        rand = HSD_Randi(w0 + w2);
        if (rand < (s32) w0) {
            lbl_80473AB8[arg0].x4C = 2;
            lbl_80473AB8[arg0].xA4 = 3;
            return rand;
        }
        lbl_80473AB8[arg0].x4C = 3;
        lbl_80473AB8[arg0].xA4 = 2;
        return rand;
    }
    lbl_80473AB8[arg0].xA4 = 1;
    rand = HSD_Randi(w0 + w1);
    if (rand < (s32) w0) {
        lbl_80473AB8[arg0].x4C = 2;
        lbl_80473AB8[arg0].x78 = 3;
        return rand;
    }
    lbl_80473AB8[arg0].x4C = 3;
    lbl_80473AB8[arg0].x78 = 2;
    return rand;
}

extern u8 lbl_803DA0D0[];

/// @todo Currently 95.92% match - needs minor register allocation fix
s32 fn_80196CF8(void)
{
    TmData* tmdata;
    s32 offset;
    u8* ptr;
    s32 x24;
    s32 result;

    tmdata = gm_8018F634();
    offset = tmdata->entrants * 6;
    ptr = lbl_803DA0D0;
    x24 = tmdata->x24;
    ptr += offset;

    result = 0;
    if (x24 > (s32) ptr[0x23]) {
        return 6;
    }

    ptr += 5;

    if (x24 <= (s32) ptr[0x1E]) {
        result = 5;
    }

    if (x24 <= (s32) (--ptr)[0x1E]) {
        result = 4;
    }

    if (x24 <= (s32) (--ptr)[0x1E]) {
        result = 3;
    }

    if (x24 <= (s32) (--ptr)[0x1E]) {
        result = 2;
    }

    if (x24 <= (s32) (--ptr)[0x1E]) {
        result = 1;
    }

    if (x24 <= (s32) (--ptr)[0x1E]) {
        result = 0;
    }

    return result;
}

static union {
    u8 x0[0x80];
    struct {
        u8 _pad0[0x8];
        s32 x8;
        s32 xC;
        u16 x10;
        u8 _pad2[0x8];
        u8 x1A;
        u8 x1B;
        u8 x1C;
        u8 _pad3[0x48 - 0x1D];
        u8* x48;
        u8 x4C;
        u8 x4D;
        u8 x4E[20];
    };
} lbl_804799D8;

/// Cycles animation frame counter and updates JObj animation.
void fn_80196DBC(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    u16* counter = &lbl_804799D8.x10;

    jobj = gobj->hsd_obj;
    if (*counter > 0x320U) {
        *counter = 0;
    }
    fn_8019044C(jobj, (f32) *counter);
    *counter = *counter + 1;
}

/// Updates the tournament UI animation frame counter.
void fn_80196E30(HSD_GObj* gobj)
{
    u8* base_ptr;
    s32 cur_option;
    HSD_JObj* jobj;
    u8* x1A_ptr;
    u8 val;

    base_ptr = lbl_804799D8.x0;
    cur_option = gm_8018F634()->cur_option;
    jobj = gobj->hsd_obj;

    if (cur_option <= 0x1A || cur_option >= 0x1F) {
        if ((u8) * (x1A_ptr = base_ptr + 0x1A) > 0x77U) {
            *x1A_ptr = 0x5A;
        }
    } else if (cur_option <= 0x1E) {
        if ((u8) * (x1A_ptr = base_ptr + 0x1A) > 0x9FU) {
            *x1A_ptr = 0x82;
        }
    }

    val = *(base_ptr += 0x1A);
    fn_8019044C(jobj, (f32) val);
    *base_ptr = *base_ptr + 1;
}

/// Tournament mode JObj visibility/animation callback.
void fn_80196EEC(HSD_GObj* gobj)
{
    TmData* tmdata;
    HSD_JObj* jobj;
    u8* counter;
    int in_range;

    tmdata = gm_8018F634();
    jobj = gobj->hsd_obj;

    if (gm_8018F634()->cur_option >= 0x13 && gm_8018F634()->cur_option <= 0x1A)
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    counter = &lbl_804799D8.x1B;

    if (*counter != 0) {
        *counter = *counter - 1;
        HSD_JObjAnimAll(jobj);
        if (tmdata->x33 == tmdata->pad_x34[0]) {
            if (*counter > 2) {
                *counter = 2;
            }
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }
    } else {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        if (tmdata->cur_option == 0x14) {
            tmdata->cur_option = 0x15;
        }
    }
}

extern u8 lbl_803B7CE0[36];

void fn_80196FFC(HSD_GObj* gobj)
{
    TmData* tm;
    HSD_JObj* jobj;
    s32 pnum;    s32 in_range;
    f32 x;
    u8 players;
    u8 state;
    u8 start_frame, cur_frame, end_frame, loop_flag;
    s32 table[9];

    tm = gm_8018F634();
    jobj = gobj->hsd_obj;
    pnum = fn_8018F62C(gobj);

    table[0] = ((s32*) lbl_803B7CE0)[0];
    table[1] = ((s32*) lbl_803B7CE0)[1];
    table[2] = ((s32*) lbl_803B7CE0)[2];
    table[3] = ((s32*) lbl_803B7CE0)[3];
    table[4] = ((s32*) lbl_803B7CE0)[4];
    table[5] = ((s32*) lbl_803B7CE0)[5];
    table[6] = ((s32*) lbl_803B7CE0)[6];
    table[7] = ((s32*) lbl_803B7CE0)[7];
    table[8] = ((s32*) lbl_803B7CE0)[8];

    if ((s32) gm_8018F634()->cur_option >= 0x1B &&
        (s32) gm_8018F634()->cur_option <= 0x1E)
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    if ((s8)(u8) HSD_PadMasterStatus[(u8) pnum].err != 0 &&
        (u8) tm->x4B8[pnum].x0 != 1)
    {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        HSD_SisLib_803A7548(tm->x524[2], (s32) pnum, 0.0f, 0.0f);
        return;
    }

    state = lbl_804799D8.x0[pnum * 6 + 0x2D];
    if (state == 4) {
        HSD_SisLib_803A7548(tm->x524[2], (s32) pnum, 0.0f, 0.0f);
    } else {
        HSD_SisLib_803A7548(tm->x524[2], (s32) pnum, 1.0f, 1.0f);
    }

    players = tm->x30;
    if ((s32) players == 4) {
        x = (13.0f * (f32) pnum) + -19.5f;
    } else if ((s32) players == 3) {
        x = 6.5f + ((13.0f * (f32) pnum) - 19.5f);
    } else {
        x = 6.5f + ((13.0f * (2.0f * (f32) pnum)) - 19.5f);
    }

    HSD_JObjSetTranslateX(jobj, x);

    tm->x524[2]->hidden = 0;

    state = lbl_804799D8.x0[pnum * 6 + 0x2D];
    lbl_804799D8.x0[pnum * 6 + 0x2A] =
        ((u8*) table)[state * 6 + 0];
    lbl_804799D8.x0[pnum * 6 + 0x2C] =
        ((u8*) table)[state * 6 + 2];
    lbl_804799D8.x0[pnum * 6 + 0x2F] =
        ((u8*) table)[state * 6 + 4];

    start_frame = lbl_804799D8.x0[pnum * 6 + 0x2A];
    cur_frame = lbl_804799D8.x0[pnum * 6 + 0x2B];
    end_frame = lbl_804799D8.x0[pnum * 6 + 0x2C];
    loop_flag = lbl_804799D8.x0[pnum * 6 + 0x2F];

    if (cur_frame < start_frame) {
        lbl_804799D8.x0[pnum * 6 + 0x2B] = start_frame;
        cur_frame = start_frame;
    }

    if (cur_frame < end_frame) {
        lbl_804799D8.x0[pnum * 6 + 0x2B] = (u8)(cur_frame + 1);
    } else {
        lbl_804799D8.x0[pnum * 6 + 0x2E] = 1;
        if (loop_flag != 0) {
            lbl_804799D8.x0[pnum * 6 + 0x2B] = start_frame;
        } else {
            lbl_804799D8.x0[pnum * 6 + 0x2B] = end_frame;
        }
    }

    state = lbl_804799D8.x0[pnum * 6 + 0x2D];
    if (state == 0 && lbl_804799D8.x0[pnum * 6 + 0x44] == 6) {
        if (lbl_804799D8.x0[pnum * 6 + 0x2E] != 0 &&
            (u8) tm->x4B8[pnum].x0 != 0)
        {
            lbl_804799D8.x0[pnum * 6 + 0x2D] = 1;
            lbl_804799D8.x0[pnum * 6 + 0x2E] = 0;
        }
    }

    state = lbl_804799D8.x0[pnum * 6 + 0x2D];
    if (state == 1) {
        if (lbl_804799D8.x0[pnum * 6 + 0x2E] != 0) {
            lbl_804799D8.x0[pnum * 6 + 0x2D] = 2;
            lbl_804799D8.x0[pnum * 6 + 0x2E] = 0;
        }
    }

    fn_8019044C(jobj, (f32) lbl_804799D8.x0[pnum * 6 + 0x2B]);
}

/// Updates visibility and position of a tournament menu JObj.
void fn_801973F8(HSD_GObj* gobj)
{
    TmData* tm;
    s32 pnum;
    HSD_JObj* jobj;
    f32 x;
    s32 cond;
    u8 player_count;

    tm = gm_8018F634();
    pnum = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (gm_8018F634()->cur_option >= 0x1B &&
        gm_8018F634()->cur_option <= 0x1E)
    {
        cond = 1;
    } else {
        cond = 0;
    }

    if (cond == 0) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, 0x10);

    if ((s8) (u8) HSD_PadMasterStatus[(u8) pnum].err != 0 &&
        tm->x4B8[pnum].x0 != 1)
    {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    player_count = tm->x30;
    if ((s32) player_count == 4) {
        x = (13.0f * (f32) pnum) + -19.5f;
    } else if ((s32) player_count == 3) {
        x = 6.5f + ((13.0f * (f32) pnum) - 19.5f);
    } else {
        x = 6.5f + ((13.0f * (2.0f * (f32) pnum)) - 19.5f);
    }

    fn_8018FDC4(jobj, 4.5f + x, 5.5f, 666.0f);

    if (lbl_804799D8.x0[pnum * 6 + 0x2D] == 4) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
    }
}

/// Updates visibility of a tournament menu JObj based on current menu state.
void fn_801975C8(HSD_GObj* gobj)
{
    TmData* tmdata;
    u32 idx;
    HSD_JObj* jobj;
    s32 in_range;

    tmdata = gm_8018F634();
    idx = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    if (HSD_PadMasterStatus[(u8) idx].err != 0 && tmdata->x4B8[idx].x0 != 1) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    if (lbl_804799D8.x0[0x2D + idx * 6] == 4) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    }
}

/// Updates visibility and animation of tournament menu JObj.
void fn_801976D4(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    u8* counter;
    s32 is_in_range;
    PAD_STACK(8);

    gm_8018F634();
    jobj = gobj->hsd_obj;
    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        is_in_range = 1;
    } else {
        is_in_range = 0;
    }
    if (is_in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
    } else {
        HSD_JObjClearFlagsAll(jobj, 0x10);
        counter = &lbl_804799D8.x1C;
        if (*counter > 0x3C) {
            *counter = 0x3C;
        }
        fn_8019044C(jobj, (f32) *counter);
        *counter = *counter + 1;
    }
}

void fn_801977AC(HSD_GObj* gobj)
{
    TmData* tm;
    s32 pnum;
    HSD_JObj* jobj;
    s32 in_range;
    f32 x;
    u8 players;

    tm = gm_8018F634();
    pnum = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (gm_8018F634()->cur_option >= 0x1B &&
        gm_8018F634()->cur_option <= 0x1E)
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, 0x10);

    players = tm->x30;
    if ((s32) players == 4) {
        x = (13.0f * (f32) pnum) + -19.5f;
    } else if ((s32) players == 3) {
        x = 6.5f + ((13.0f * (f32) pnum) - 19.5f);
    } else {
        x = 6.5f + ((13.0f * (2.0f * (f32) pnum)) - 19.5f);
    }

    fn_8018FDC4(jobj, 0.3f + x, 12.6f, 666.0f);

    if (lbl_804799D8.x0[pnum * 6 + 0x2D] == 4) {
        u8* counter_ptr;
        u8 counter;

        counter_ptr = &lbl_804799D8.x0[pnum + 0x1D];
        counter = *counter_ptr;
        if (counter < 0x28) {
            *counter_ptr = counter + 1;
        }
        counter = *counter_ptr;

        HSD_JObjSetTranslateY(jobj,
            *(f32*) (lbl_803DA0D0 + counter * 4 + 0xE0));
    } else {
        lbl_804799D8.x0[pnum + 0x1D] = 0;
    }

    if ((s8) (u8) HSD_PadMasterStatus[(u8) pnum].err != 0 &&
        tm->x4B8[pnum].x0 != 1)
    {
        HSD_JObjClearFlagsAll(jobj, 0x10);

        players = tm->x30;
        if ((s32) players == 4) {
            x = (13.0f * (f32) pnum) + -19.5f;
        } else if ((s32) players == 3) {
            x = 6.5f + ((13.0f * (f32) pnum) - 19.5f);
        } else {
            x = 6.5f + ((13.0f * (2.0f * (f32) pnum)) - 19.5f);
        }

        fn_8018FDC4(jobj, 0.3f + x, 12.6f, 666.0f);
    }
}

void fn_80197AF0(HSD_GObj* gobj)
{
    TmData* tm;
    s32 pnum;
    HSD_JObj* jobj;
    s32 in_range;
    f32 x;
    u8 players;
    u8 state;
    u16* counter;

    tm = gm_8018F634();
    pnum = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (((s32) gm_8018F634()->cur_option >= 0x1B) &&
        ((s32) gm_8018F634()->cur_option <= 0x1E))
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, 0x10U);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, 0x10U);

    if (((s8) HSD_PadMasterStatus[(u8) pnum].err != 0) &&
        ((u8) tm->x4B8[pnum].x0 != 1))
    {
        HSD_JObjSetFlagsAll(jobj, 0x10U);
        return;
    }

    if ((u8) tm->x4B8[pnum].x0 == 1) {
        HSD_JObjSetFlagsAll(jobj, 0x10U);
    }

    players = tm->x30;
    if ((s32) players == 4) {
        x = (13.0f * (f32) pnum) + -19.5f;
    } else if ((s32) players == 3) {
        x = 6.5f + ((13.0f * (f32) pnum) - 19.5f);
    } else {
        x = 6.5f + ((13.0f * (2.0f * (f32) pnum)) - 19.5f);
    }

    fn_8018FDC4(jobj, x, 666.0f, 666.0f);

    if (lbl_804799D8.x0[pnum + 0x44] != 6 ||
        lbl_804799D8.x0[pnum * 6 + 0x2D] == 1 ||
        lbl_804799D8.x0[pnum * 6 + 0x2D] == 2 ||
        lbl_804799D8.x0[pnum * 6 + 0x2D] == 4)
    {
        HSD_JObjSetFlagsAll(jobj, 0x10U);
    }

    counter = (u16*) &lbl_804799D8.x0[pnum * 2 + 0x12];
    if (*counter < 0x258U) {
        *counter = (u16) (*counter + 1);
    } else {
        *counter = 0U;
    }
    fn_8019044C(jobj, (f32) *counter);
}

/// Updates visibility of a menu JObj based on current menu option.
void fn_80197D4C(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    u8* counter;
    int cond;
    PAD_STACK(8);

    gm_8018F634();
    jobj = gobj->hsd_obj;
    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        cond = 1;
    } else {
        cond = 0;
    }
    if (cond == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }
    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    counter = &lbl_804799D8.x0[0x29];
    fn_8019044C(jobj, (float) lbl_804799D8.x0[0x29]);
    if (*counter < 10U) {
        *counter = *counter + 1;
    }
}

/// @todo Currently 69.71% match - needs register allocation fix
/// Updates player HUD element visibility and position.
void fn_80197E18(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    TmData* data;
    s32 pnum;
    s32 in_range;
    f32 x_pos;

    data = gm_8018F634();
    pnum = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, 0x10);

    if (HSD_PadMasterStatus[(u8) pnum].err != 0 && data->x4B8[pnum].x0 != 1) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    if (data->x4B8[pnum].x0 != 1) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
    }

    if ((s32) data->x30 == 4) {
        x_pos = (13.0F * pnum) + (-19.5F);
    } else if ((s32) data->x30 == 3) {
        x_pos = 6.5F + ((13.0F * pnum) - 19.5F);
    } else {
        x_pos = 6.5F + ((13.0F * (2.0F * pnum)) - 19.5F);
    }
    fn_8018FDC4(jobj, x_pos, 666.0F, 666.0F);
}

/// @todo Currently 70.24% match - needs register allocation fix
/// Updates JObj visibility based on menu option and player state.
void fn_80197FD8(HSD_GObj* gobj)
{
    TmData* tm_data;
    s32 port;
    HSD_JObj* jobj;
    s32 option_in_range;
    u8 port_u8;

    tm_data = gm_8018F634();
    port = fn_8018F62C(gobj);
    jobj = *(HSD_JObj**) ((u8*) gobj + 0x28);

    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        option_in_range = 1;
    } else {
        option_in_range = 0;
    }

    if (option_in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, 0x10);

    port_u8 = (u8) port;
    if ((s8) HSD_PadMasterStatus[port_u8].err != 0) {
        if (tm_data->x4B8[port].x0 != 1) {
            HSD_JObjSetFlagsAll(jobj, 0x10);
            return;
        }
    } else {
        if (lbl_804799D8.x0[port * 6 + 0x2D] == 4) {
            HSD_JObjSetFlagsAll(jobj, 0x10);
        }
    }

    {
        f32 x_position;
        u8 num_players = tm_data->x30;

        if ((s32) num_players == 4) {
            x_position = (13.0F * (f32) port) + -19.5F;
        } else if ((s32) num_players == 3) {
            x_position = 6.5F + ((13.0F * (f32) port) - 19.5F);
        } else {
            x_position = 6.5F + ((13.0F * (2.0F * (f32) port)) - 19.5F);
        }

        fn_8018FDC4(jobj, x_position, 666.0F, 666.0F);
    }
}

/// @todo Currently 55.88% match - needs significant rework
/// Updates player cursor animation and position.
void fn_801981A0(HSD_GObj* gobj)
{
    TmData* data;
    u8* player_ptr;
    s32 pnum;
    HSD_JObj* jobj;
    u8* state_ptr;
    f32 x_pos;
    s32 in_range;
    u8 counter;

    data = gm_8018F634();
    pnum = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, 0x10);

    if (HSD_PadMasterStatus[(u8) pnum].err != 0 &&
        ((u8*) &lbl_804799D8)[pnum * 6 + 0x2D] != 4)
    {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    state_ptr = &((u8*) &lbl_804799D8)[pnum + 0x44];
    if (*state_ptr == 6) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
    }

    if ((s32) data->x30 == 4) {
        x_pos = (13.0F * (f32) pnum) + (-19.5F);
    } else if ((s32) data->x30 == 3) {
        x_pos = 6.5F + ((13.0F * (f32) pnum) - 19.5F);
    } else {
        x_pos = 6.5F + ((13.0F * (2.0F * (f32) pnum)) - 19.5F);
    }

    fn_8018FDC4(jobj, x_pos, 666.0F, 0.01F);

    player_ptr = (u8*) &lbl_804799D8 + pnum;
    counter = player_ptr[0x21];
    counter = (counter + 1) % 11;
    player_ptr[0x21] = counter;

    if (*state_ptr == 7) {
        fn_8019044C(jobj, (f32) player_ptr[0x21]);
        return;
    }

    fn_8019044C(jobj, (f32) (player_ptr[0x21] + 0x14));
}

/// Updates the visibility and position of a player's controller indicator.
void fn_801983E4(HSD_GObj* gobj)
{
    TmData* tm;
    s32 pnum;
    HSD_JObj* jobj;
    f32 x;
    s32 cond;
    u8 player_count;

    tm = gm_8018F634();
    pnum = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (gm_8018F634()->cur_option >= 0x1B &&
        gm_8018F634()->cur_option <= 0x1E)
    {
        cond = 1;
    } else {
        cond = 0;
    }

    if (cond == 0) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, 0x10);

    if ((s8) (u8) HSD_PadMasterStatus[(u8) pnum].err == 0 ||
        tm->x4B8[pnum].x0 == 1)
    {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    player_count = tm->x30;
    if ((s32) player_count == 4) {
        x = (13.0f * (f32) pnum) + -19.5f;
    } else if ((s32) player_count == 3) {
        x = 6.5f + ((13.0f * (f32) pnum) - 19.5f);
    } else {
        x = 6.5f + ((13.0f * (2.0f * (f32) pnum)) - 19.5f);
    }

    fn_8018FDC4(jobj, x, 666.0f, 0.01f);
}

void fn_80198584(ResultsData* results)
{
    HSD_JObj* jobj;
    int cur_option;

    cur_option = gm_8018F634()->cur_option;
    jobj = results->x28;
    if (cur_option == 0x1D) {
        HSD_JObjClearFlagsAll(jobj, 0x10);
    } else {
        HSD_JObjSetFlagsAll(jobj, 0x10);
    }
}

static s32 lbl_804D667C;

void fn_801985D4(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    HSD_JObj* child;
    s32 in_range;

    gm_8018F634();
    jobj = gobj->hsd_obj;

    if ((s32) gm_8018F634()->cur_option >= 0x1F &&
        (s32) gm_8018F634()->cur_option <= 0x27)
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetTranslateZ(jobj, 10000.0f);
    } else {
        HSD_JObjSetTranslateZ(jobj, 0.0f);

        if (*(u32*) &lbl_804799D8.x0[0] < 0xAU) {
            lbl_804D667C = 1;
            return;
        }

        HSD_JObjAnimAll(jobj);
        child = HSD_JObjGetChild(jobj);

        if (HSD_DObjGetFlags(HSD_JObjGetDObj(child)) & 1) {
            lbl_804D667C = 1;
        } else {
            lbl_804D667C = 0;
        }

        HSD_JObjGetTranslation(child, (Vec3*) &lbl_804799D8.x0[0x64]);
        HSD_JObjGetScale(child, (Vec3*) &lbl_804799D8.x0[0x70]);
    }
}

/// Animates and positions the tournament bracket results overlay JObj.
/// Uses HSD_JObjSetTranslateZ for visibility, HSD_JObjSetTranslate/SetScale
/// for positioning from lbl_804799D8 cached values.
void fn_80198824(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    s32 in_range;

    gm_8018F634();
    jobj = gobj->hsd_obj;

    if ((s32) gm_8018F634()->cur_option >= 0x1F &&
        (s32) gm_8018F634()->cur_option <= 0x27)
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetTranslateZ(jobj, 10000.0f);
    } else {
        HSD_JObjSetTranslateZ(jobj, 0.0f);

        if (lbl_804D667C == 0) {
            HSD_JObjSetTranslateZ(jobj, 10000.0f);
        } else {
            u32* frame_ctr = (u32*) &lbl_804799D8.x0[4];
            u32 min_frame = *(u32*) &lbl_804799D8.x0[8];
            u32 max_frame = *(u32*) &lbl_804799D8.x0[0xC];

            if (*frame_ctr < min_frame) {
                *frame_ctr = min_frame;
            }
            if (*frame_ctr < max_frame) {
                *frame_ctr = *frame_ctr + 1;
            }

            HSD_JObjReqAnimAll(jobj, (f32) *frame_ctr);
            HSD_JObjAnimAll(jobj);

            HSD_JObjSetTranslate(jobj, (Vec3*) &lbl_804799D8.x0[0x64]);
            HSD_JObjSetScale(jobj, (Vec3*) &lbl_804799D8.x0[0x70]);
        }
    }
}

/// Initializes tournament mode match data.
/// Initializes tournament mode match data structures.
/// Type casts used to match target instruction patterns (stw/sth vs stb).
#pragma push
#pragma auto_inline off
void fn_80198BA0(void)
{
    TmData* td;
    u8* ptr;
    u8* ptr7;
    u8* ptr8;
    s32 i;

    ptr = lbl_804799D8.x0;
    td = gm_8018F634();

    /* Clear first 4 bytes as word (stw instruction) */
    *(u32*) &ptr[0x00] = 0;
    if (td && td) {
        /* FAKE MATCH: Empty block affects register allocation */
    }
    /* Clear 2 bytes at offset 0x10 as halfword (sth instruction) */
    *(u16*) &ptr[0x10] = 0;

    if (td->x2C != 0) {
        ptr[0x1A] = 0x50;
    } else {
        ptr[0x1A] = 0x5A;
    }

    ptr[0x1C] = 0;
    ptr7 = ptr;
    ptr8 = ptr;

    for (i = 0; i < td->x30; i++) {
        ptr[0x25] = 0;
        /* Clear 2 bytes as halfword (sth instruction) */
        *(u16*) &ptr7[0x12] = 0;
        ptr7 += 2;
        ptr[0x1D] = 0;
        ptr8[0x2A] = 0;
        ptr8[0x2B] = 0;
        ptr8[0x2C] = 0x1E;
        ptr8[0x2E] = 0;
        ptr8[0x2F] = 0;
        ptr8[0x2D] = 0;
        ptr8 += 6;
        ptr[0x44] = 6;
        ptr++;
    }
}
#pragma pop

/// @todo Currently 99.63% match - permuter couldn't improve (instruction
/// scheduling)
/// Initializes tournament mode text displays.
#pragma push
#pragma auto_inline off
void fn_80198C60(void)
{
    TmData* td;
    HSD_Text* text;

    PAD_STACK(24);

    td = gm_8018F634();
    td->x524[2] = HSD_SisLib_803A6754(0, (s32) lbl_804D663C);
    text = td->x524[2];
    text->font_size.x = 0.054945F;
    text->font_size.y = 0.08F;
    td->x524[2]->default_alignment = 1;
    td->x524[2]->default_kerning = 1;

    td->x524[3] = HSD_SisLib_803A6754(0, (s32) lbl_804D663C);
    td->x524[3]->default_alignment = 1;
    td->x524[3]->default_kerning = 1;
    HSD_SisLib_803A6B98(td->x524[3], 320.0F, 250.0F, "    ");
    HSD_SisLib_803A7548(td->x524[3], 0, 1.5F, 1.5F);
}
#pragma pop

extern SceneDesc* lbl_804D666C;

/// Initializes the scene rendering components for the gm_18A5 game mode.
void fn_80198D18(void)
{
    TmData* td;
    HSD_Text* text;
    HSD_GObj* gobj;
    PAD_STACK(24);

    gm_8018F634();
    gobj = fn_80190174(lbl_804D666C->cameras->desc);
    fn_801901F8(lbl_804D666C->cameras->desc);
    fn_801902F0((int) gobj);
    fn_8019027C(lbl_804D666C->lights);
    fn_8019035C(0, lbl_804D666C->models[5], 0, 0x1A, 2, 1, fn_80196DBC,
                0.0f);
    fn_8019035C(0, lbl_804D666C->models[4], 0, 0x1A, 2, 1, fn_80196E30,
                80.0f);

    td = gm_8018F634();
    td->x524[2] = HSD_SisLib_803A6754(0, (s32) lbl_804D663C);
    text = td->x524[2];
    text->font_size.x = 0.054945f;
    text->font_size.y = 0.08f;
    td->x524[2]->default_alignment = 1;
    td->x524[2]->default_kerning = 1;

    td->x524[3] = HSD_SisLib_803A6754(0, (s32) lbl_804D663C);
    td->x524[3]->default_alignment = 1;
    td->x524[3]->default_kerning = 1;
    HSD_SisLib_803A6B98(td->x524[3], 320.0f, 250.0f, "    ");
    HSD_SisLib_803A7548(td->x524[3], 0, 1.5f, 1.5f);

    gobj = GObj_Create(0xE, 0x1A, 0);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848,
                            HSD_FogLoadDesc(lbl_804D666C->fogs[0].desc));
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0, 0);
    fn_80198BA0();
}

/// #fn_80198EBC

extern MatchEnd gm_80477738;
extern SceneDesc* lbl_804D6670;

void fn_80199AF0(void)
{
    TmData* td1;
    TmData* td2;
    HSD_JObj* jobj;
    HSD_JObj* next;
    HSD_GObj* gobj;
    s32 mode;
    s32 slot;
    s32 bracket_idx;
    s32 result;
    s32 i;
    s32 local1;
    s32 local2;
    PAD_STACK(16);

    td1 = gm_8018F634();
    td2 = gm_8018F634();

    result = fn_8018F508(&local1);
    if (result == 1) {
        result = 1;
    } else if (td2->x33 == 5) {
        result = 2;
    } else {
        result = 0;
    }
    mode = result;

    result = fn_8018F508(&local2);
    if (result == 1) {
        slot = local2;
    } else {
        u8* p = (u8*) &gm_80477738;
        if (p[0x58] != 3 && p[0x5E] == 0) {
            slot = 0;
        } else {
            p += 0xA8;
            if (p[0x58] != 3 && p[0x5E] == 0) {
                slot = 1;
            } else {
                p += 0xA8;
                if (p[0x58] != 3 && p[0x5E] == 0) {
                    slot = 2;
                } else {
                    p += 0xA8;
                    if (p[0x58] != 3 && p[0x5E] == 0) {
                        slot = 3;
                    } else {
                        slot = -1;
                    }
                }
            }
        }
    }

    bracket_idx = fn_8018F74C();
    gm_8018F634();

    gobj = fn_80190174(lbl_804D666C->cameras->desc);
    fn_801901F8(lbl_804D666C->cameras->desc);
    fn_801902F0((int) gobj);
    fn_8019027C(lbl_804D666C->lights);
    fn_8019035C(0, lbl_804D666C->models[5], 0, 0x1A, 2, 1, fn_80196DBC,
                0.0f);
    fn_8019035C(0, lbl_804D666C->models[4], 0, 0x1A, 2, 1, fn_80196E30,
                80.0f);

    fn_80198C60();

    gobj = GObj_Create(0xE, 0x1A, 0);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848,
                            HSD_FogLoadDesc(lbl_804D666C->fogs[0].desc));
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0, 0);
    fn_80198BA0();

    if (td1->x33 == 5) {
        mode = 2;
    }

    if (mode != 2) {
        if (lbl_80473AB8[bracket_idx].x18 == 0) {
            return;
        }
    }

    fn_8019035C(0, lbl_804D6670->models[0], mode, 0x1A, 3, 1, fn_801985D4,
                0.0f);
    gobj = fn_8019035C(0, lbl_804D6670->models[2], 0, 0x1A, 3, 1,
                       fn_80198824, 0.0f);

    if (gobj->hsd_obj == NULL) {
        jobj = NULL;
    } else {
        jobj = ((HSD_JObj*) gobj->hsd_obj)->child;
    }

    lbl_804799D8.x8 = mode * 0x14;
    if (mode == 2) {
        lbl_804799D8.xC = 0x96;
    } else {
        lbl_804799D8.xC = mode * 0x14 + 0x13;
    }

    HSD_JObjSetTranslateZ(jobj, 10000.0f);

    if (lbl_803DA0D0[td1->x4B8[slot].x1] == 0) {
        HSD_JObjSetTranslateZ(jobj, 0.0f);
        for (i = 1; i <= 12; i++) {
            if (jobj == NULL) {
                next = NULL;
            } else {
                next = jobj->next;
            }
            jobj = next;
            HSD_JObjSetTranslateZ(next, 10000.0f);
        }
    } else {
        for (i = 1; i <= 12; i++) {
            if (jobj == NULL) {
                next = NULL;
            } else {
                next = jobj->next;
            }
            jobj = next;
            HSD_JObjSetTranslateZ(next, 10000.0f);

            if ((s32) lbl_803DA0D0[td1->x4B8[slot].x1] == i) {
                HSD_JObjSetTranslateZ(next, 0.0f);
                for (slot = i + 1; slot <= 12; slot++) {
                    if (jobj == NULL) {
                        next = NULL;
                    } else {
                        next = jobj->next;
                    }
                    jobj = next;
                    HSD_JObjSetTranslateZ(next, 10000.0f);
                }
                break;
            }
        }
    }
}

void fn_8019A158(void)
{
    TmData* td1;
    TmData* td2;
    s32 mode;
    s32 slot;
    s32 bracket_idx;
    s32 result;
    s32 local1, local2;
    s32 i;
    s32 counter;
    u8* me;
    u8* cursor;
    PAD_STACK(16);

    td1 = gm_8018F634();
    lbl_804799D8.x48 = (u8*) &gm_80477738;
    mode = 0;
    *(u32*) lbl_804799D8.x0 = 0;

    td2 = gm_8018F634();

    result = fn_8018F508(&local1);
    if (result == 1) {
        mode = 1;
    } else if (td2->x33 == 5) {
        mode = 2;
    }

    me = lbl_804799D8.x48;
    result = fn_8018F508(&local2);
    if (result == 1) {
        slot = local2;
    } else {
        slot = -1;
        for (i = 0; i < 4; i++) {
            if (me[0x58] != 3 && me[0x5E] == 0) {
                slot = i;
                break;
            }
            me += 0xA8;
        }
    }

    bracket_idx = fn_8018F74C();

    for (i = 0; i < 20; i++) {
        lbl_804799D8.x4E[i] = 0;
    }

    if (mode == 1) {
        BracketEntry* bracket = &lbl_80473AB8[bracket_idx];
        u8* bp = (u8*) bracket;
        u8* matched = bp + slot * 0x2C;

        for (i = 0; i < 4; i++) {
            if (i == slot) {
                matched[0x4C] = 0;
            } else {
                bp[0x4C] = 3;
            }
            bp += 0x2C;
        }
    } else if (td1->x2D == 1) {
        BracketEntry* bracket = &lbl_80473AB8[bracket_idx];
        cursor = (u8*) bracket;

        if (bracket->x4E == 3) {
            bracket->x4C = 3;
        } else {
            me = lbl_804799D8.x48;
            me[0x5D] = me[0x5E];
            bracket->x4C = me[0x5E];
            me = lbl_804799D8.x48;
            if (me[0x5E] == 0) {
                slot = 0;
            }
        }

        {
            u8 check = bracket->x7A;
            cursor += 0x2C;
            if (check == 3) {
                cursor[0x4C] = 3;
            } else {
                me = lbl_804799D8.x48;
                me += 0xA8;
                me[0x5D] = me[0x5E];
                cursor[0x4C] = me[0x5E];
                me = lbl_804799D8.x48;
                if (me[0x106] == 0) {
                    slot = 1;
                }
            }
        }

        {
            u8 check = cursor[0x7A];
            cursor += 0x2C;
            if (check == 3) {
                cursor[0x4C] = 3;
            } else {
                me = lbl_804799D8.x48;
                me += 0x150;
                me[0x5D] = me[0x5E];
                cursor[0x4C] = me[0x5E];
                me = lbl_804799D8.x48;
                if (me[0x1AE] == 0) {
                    slot = 2;
                }
            }
        }

        {
            u8 check = cursor[0x7A];
            cursor += 0x2C;
            if (check == 3) {
                cursor[0x4C] = 3;
            } else {
                me = lbl_804799D8.x48;
                me += 0x1F8;
                me[0x5D] = me[0x5E];
                cursor[0x4C] = me[0x5E];
                me = lbl_804799D8.x48;
                if (me[0x256] == 0) {
                    slot = 3;
                }
            }
        }
    } else {
        BracketEntry* bracket = &lbl_80473AB8[bracket_idx];
        counter = 0;

        if (bracket->x4E == 3) {
            bracket->x4C = 4;
        } else {
            bracket->x4C = 0;
            counter = 1;
        }

        cursor = (u8*) bracket + 0x2C;
        if (bracket->x7A == 3) {
            cursor[0x4C] = 4;
        } else {
            cursor[0x4C] = counter;
            counter++;
        }

        {
            u8 check = cursor[0x7A];
            cursor += 0x2C;
            if (check == 3) {
                cursor[0x4C] = 4;
            } else {
                cursor[0x4C] = counter;
                counter++;
            }
        }

        {
            u8 check = cursor[0x7A];
            cursor += 0x2C;
            if (check == 3) {
                cursor[0x4C] = 4;
            } else {
                cursor[0x4C] = counter;
                counter++;
            }
        }

        switch (counter) {
        case 3:
            fn_80196684(bracket_idx);
            break;
        case 2: {
            s32 rand_val = HSD_Randi(bracket->x51 + bracket->x7D);
            if (rand_val < bracket->x51) {
                bracket->x4C = 0;
                bracket->x78 = 1;
            } else {
                bracket->x4C = 1;
                bracket->x78 = 0;
            }
            break;
        }
        case 4:
        case 5:
            fn_801967E0(bracket_idx);
            break;
        }

        me = lbl_804799D8.x48;
        cursor = (u8*) &lbl_80473AB8[bracket_idx];
        me[0x5D] = cursor[0x4C];
        me = lbl_804799D8.x48;
        me[0x5E] = cursor[0x4C];
        me[0x105] = cursor[0x78];
        me = lbl_804799D8.x48;
        me[0x106] = cursor[0x78];
        me[0x1AD] = cursor[0xA4];
        me = lbl_804799D8.x48;
        me[0x1AE] = cursor[0xA4];
        me[0x255] = cursor[0xD0];
        me = lbl_804799D8.x48;
        me[0x256] = cursor[0xD0];

        if (bracket->x4C == 0) {
            slot = 0;
        }
        if (bracket->x78 == 0) {
            slot = 1;
        }
        cursor = (u8*) bracket + 0x2C;
        if (cursor[0x78] == 0) {
            cursor += 0x2C;
            slot = 2;
        } else {
            cursor += 0x2C;
        }
        if (cursor[0x78] == 0) {
            slot = 3;
        }
    }

    {
        BracketEntry* bracket = &lbl_80473AB8[bracket_idx];
        lbl_804799D8.x4C = slot;
        cursor = (u8*) bracket + slot * 0x2C;
        lbl_804799D8.x4D = cursor[0x4E];

        if (lbl_804799D8.x4D == 0 && bracket->x18 != 0) {
            u8 s = lbl_804799D8.x4C;
            u16 val = td1->x4B8[s].x6;
            if (val <= 0x78) {
                gm_80167858(s, (s32) val, 0x1F, 0x78);
            } else {
                gm_80167858(s, 0x78, 0x1F, 0x78);
            }
        }

        cursor = (u8*) &lbl_80473AB8[bracket_idx] + slot * 0x2C;
        {
            u8 model_idx = cursor[0x50];
            fn_8018F00C((char*) lbl_804799D8.x4E,
                         td1->x37[model_idx].x9);
        }
    }
}

/// #fn_8019A158_end

/// @todo Currently 98.36% match - needs branch pattern fix (beq+b vs bne)
#pragma dont_inline on
void fn_8019A71C(s32* state, u32 unused1, u32 unused2)
{
    u32* counter = (u32*) &lbl_804799D8;

    if (*state == 0x13) {
        fn_8019B458(state);
    }

    if (*state > 0x14) {
        *counter = *counter + 1;
    }

    if (*counter >= 0x14U) {
        *state = 0x15;
    }

    if (*counter == 0x1EU) {
        *state = 0x16;
    }

    if (*counter > 0x1EU) {
        *state = 0x17;
    }

    if (*counter >= 0x3CU) {
        *state = 0x18;
    }

    if (*counter >= 0x46U) {
        *state = 0x19;
    }

    if (*counter >= 0x5AU) {
        fn_8018EC48();
        *state = 0x1A;
        fn_8018EC7C();
        if (fn_8018F508(0) == 1) {
            *state = 0x1F;
            return;
        }
        *state = 0x1B;
    }
}
#pragma dont_inline reset

s32 lbl_804D6678;

void gm_8019A828(void)
{
    gm_8018F634()->x32 = 0;
    lbl_804D6678 = 1;
    gm_8018F634()->cur_option = 0x1B;
}

/// #fn_8019A86C

void fn_8019A86C(s32* arg0, u32 arg1, u32 arg2)
{
    TmData* tm = (TmData*) arg0;
    s32 var_r26 = 0;
    s32 var_r28 = 0;
    u8* d8 = lbl_804799D8.x0;
    s32 i;

    if (tm->cur_option == 0x1B) {
        fn_8019B81C(arg0);
    }

    if (tm->cur_option == 0x1D) {
        *(u32*) d8 += 1;
        if ((arg2 & 0x600) || (*(u32*) d8 >= 0x12CU)) {
            lbAudioAx_80024030(0);
            mn_8022F138(0x19, 0x1C);
            mn_8022F138(0x12, 0x15);
            tm->x2D = 0;
            tm->cur_option = 0x1F;
        }
        if (arg2 & 0x1100) {
            TmData* t;
            s32 stype;
            s32 cond;

            lbAudioAx_80024030(1);
            t = gm_8018F634();
            t->x2D = 1;
            stype = t->stage_selection_type;
            if ((stype == 2 && (u8) t->x32 == 0) || stype == 3) {
                cond = 1;
            } else {
                cond = 0;
            }
            if (cond != 0) {
                t->x32 = 1;
                gm_SetScenePendingMinor(3U);
                gm_801A4B60();
                return;
            }
            if ((stype == 0 && (u8) t->x32 == 0) || stype == 1) {
                cond = 1;
            } else {
                cond = 0;
            }
            if (cond != 0) {
                t->x32 = 1;
                t->x28 = (u32) lbl_804D4190;
            }
            gm_SetScenePendingMinor(4U);
            gm_801A4B60();
        }
    } else {
        u8 n_players = tm->x30;
        u8* sel = (u8*) &tm->x4B8[0];
        u8* pd = d8;
        u8 pnum = 0;

        if ((s32) n_players > 0) {
            u8 cnt = n_players;
            do {
                if (sel[0] == 1) {
                    var_r26 += 1;
                } else {
                    u8 err = (u8) HSD_PadMasterStatus[pnum].err;
                    if ((s8) err != 0) {
                        var_r28 = 1;
                    }
                    {
                        u8 state = pd[0x2D];
                        if (((state == 2 && (u8) pd[0x2B] >= 0x3CU) ||
                             (state == 4 && (u8) pd[0x2B] == 0x82)) &&
                            (s8) err == 0)
                        {
                            var_r26 += 1;
                        }
                    }
                }
                sel += 0xA;
                pd += 6;
                pnum += 1;
                cnt -= 1;
            } while (cnt != 0);
        }

        {
            s32 cond3;
            if ((fn_8018F640(4) & 0x1160) &&
                ((u32)(fn_8018F6A8(4) & 0x1160) == 0x1160))
            {
                cond3 = 1;
            } else {
                cond3 = 0;
            }
            if (cond3 != 0 && var_r28 != 0) {
                lbAudioAx_80024030(0);
                HSD_SisLib_803A5E70();
                mn_8022F138(0x19U, 0x1CU);
                mn_8022F138(0x12U, 0x15U);
                mn_8022F268();
                gm_801A4B60();
                gm_801A42F8(1);
                return;
            }
        }

        if (var_r26 == (s32) tm->x30) {
            *(u32*) d8 += 1;
            if (*(u32*) d8 >= 0x1EU) {
                u8* sp = (u8*) &tm->x4B8[0];
                u8* ap = d8;

                for (i = 0; i < (s32) tm->x30; i++) {
                    if (sp[0] == 0 && ap[0x2D] == 4) {
                        sp[0] = 3;
                    }
                    sp += 0xA;
                    ap += 6;
                }

                {
                    TmData* t2 = gm_8018F634();
                    u8* ent = (u8*) &lbl_80473AB8[fn_8018F74C()];
                    s32 hmn_count = 0;
                    s32 active_count = 0;

                    ent[0x4E] = t2->x4B8[0].x0;
                    ent[0x7A] = t2->x4B8[1].x0;
                    ent[0xA6] = t2->x4B8[2].x0;
                    ent[0xD2] = t2->x4B8[3].x0;

                    {
                        u8 s0 = tm->x4B8[0].x0;
                        if (s0 == 0) hmn_count += 1;
                        if (s0 != 3) active_count += 1;
                    }
                    {
                        u8 s1 = tm->x4B8[1].x0;
                        if (s1 == 0) hmn_count += 1;
                        if (s1 != 3) active_count += 1;
                    }
                    {
                        u8 s2 = tm->x4B8[2].x0;
                        if (s2 == 0) hmn_count += 1;
                        if (s2 != 3) active_count += 1;
                    }
                    {
                        u8 s3 = tm->x4B8[3].x0;
                        if (s3 == 0) hmn_count += 1;
                        if (s3 != 3) active_count += 1;
                    }

                    if (active_count <= 1) {
                        mn_8022F138(0x19, 0x1C);
                        mn_8022F138(0x12, 0x15);
                        tm->x2D = 0;
                        tm->cur_option = 0x1F;
                        return;
                    }
                    if (hmn_count == 0) {
                        tm->cur_option = 0x1D;
                        return;
                    }

                    {
                        TmData* t3 = gm_8018F634();
                        s32 stype2 = t3->stage_selection_type;
                        s32 cond2;

                        t3->x2D = 1;
                        if ((stype2 == 2 && (u8) t3->x32 == 0) || stype2 == 3) {
                            cond2 = 1;
                        } else {
                            cond2 = 0;
                        }
                        if (cond2 != 0) {
                            t3->x32 = 1;
                            gm_SetScenePendingMinor(3U);
                            gm_801A4B60();
                            return;
                        }
                        if ((stype2 == 0 && (u8) t3->x32 == 0) || stype2 == 1) {
                            cond2 = 1;
                        } else {
                            cond2 = 0;
                        }
                        if (cond2 != 0) {
                            t3->x32 = 1;
                            t3->x28 = (u32) lbl_804D4190;
                        }
                        gm_SetScenePendingMinor(4U);
                        gm_801A4B60();
                    }
                }
            }
        } else {
            u8* sel2 = (u8*) &tm->x4B8[0];
            u8* anim = d8;
            u8* pdata = d8;

            *(u32*) d8 = 0;

            for (i = 0; i < (s32) tm->x30; i++) {
                if ((s8)(u8) HSD_PadMasterStatus[(u8) i].err == 0 &&
                    sel2[0] == 0)
                {
                    u32 buttons = fn_8018F640(i);

                    if (buttons & 0x1100) {
                        u8 astate = anim[0x44];

                        lbAudioAx_80024030(1);
                        if (astate == 7) {
                            anim[0x44] = 6;
                        } else if (astate == 8) {
                            u8 np = gm_8018F634()->x30;
                            u8* cp = d8;
                            s32 count4 = 0;
                            u8 cnt2 = np;

                            if ((s32) np > 0) {
                                do {
                                    if (cp[0x2D] == 4) {
                                        count4 += 1;
                                    }
                                    cp += 6;
                                    cnt2 -= 1;
                                } while (cnt2 != 0);
                            }
                            if (count4 < (s32)(tm->x30 - 1)) {
                                anim[0x44] = 6;
                                pdata[0x2D] = 4;
                            }
                        } else {
                            u8 pstate = pdata[0x2D];
                            switch (pstate) {
                            case 4:
                                pdata[0x2D] = 5;
                                break;
                            case 0:
                            case 3:
                            case 5:
                            {
                                u16 val = *(u16*)(sel2 + 6);
                                if (val <= 0x78U) {
                                    gm_80167858(i, (s32) val, 0xB, 0x14);
                                } else {
                                    gm_80167858(i, 0x78, 0xB, 0x14);
                                }
                                pdata[0x2D] = 1;
                                break;
                            }
                            }
                        }
                    } else if (buttons & 0x400) {
                        if (anim[0x44] != 6) {
                            lbAudioAx_80024030(0);
                            anim[0x44] = 6;
                        } else {
                            u8 pstate2 = pdata[0x2D];
                            switch (pstate2) {
                            case 0:
                            case 3:
                            case 5:
                            {
                                u8 np2 = gm_8018F634()->x30;
                                u8* cp2 = d8;
                                s32 count5 = 0;
                                u8 cnt3 = np2;

                                if ((s32) np2 > 0) {
                                    do {
                                        if (cp2[0x2D] == 4) {
                                            count5 += 1;
                                        }
                                        cp2 += 6;
                                        cnt3 -= 1;
                                    } while (cnt3 != 0);
                                }
                                if (count5 < (s32)(tm->x30 - 1)) {
                                    lbAudioAx_80024030(0);
                                    anim[0x44] = 7;
                                }
                                break;
                            }
                            case 2:
                                lbAudioAx_80024030(0);
                                pdata[0x2D] = 3;
                                pdata[0x2E] = 0;
                                break;
                            }
                        }
                    } else if ((buttons & 0x10000) || (buttons & 8)) {
                        if (anim[0x44] == 8) {
                            lbAudioAx_80024030(2);
                            anim[0x44] = 7;
                        }
                    } else if (((buttons & 0x20000) || (buttons & 4)) &&
                               anim[0x44] == 7)
                    {
                        lbAudioAx_80024030(2);
                        anim[0x44] = 8;
                    }
                }
                sel2 += 0xA;
                anim += 1;
                pdata += 6;
            }
        }
    }
}

/// #fn_8019AF50

extern u8 lbl_804D6680[8];
extern u8 lbl_803B7D04[20];

/// Tournament match timer display/audio state machine.
/// Handles match countdown, audio transitions, and end conditions.
void fn_8019AF50(s32* arg0, u32 arg1, u32 arg2)
{
    typedef struct { s32 d[5]; } TimerFmt;
    TimerFmt sp_buf;
    TmData* tm = (TmData*) arg0;
    u32* counter = (u32*) &lbl_804799D8;
    s32 bracketIdx;
    u32 buttons;

    sp_buf = *(TimerFmt*) lbl_803B7D04;
    bracketIdx = fn_8018F74C();

    if (*arg0 == 0x1F) {
        fn_8019B860(tm);
    }

    if (tm->x33 == 6) {
        if (lbl_804D6680[0] == 2) {
            if (lbAudioAx_80023730() == 0) {
                lbAudioAx_80023F28(
                    lbAudioAx_8002305C(fn_8018F6FC(lbl_804D6680[1]), 0));
                lbl_804D6680[0] = 3;
            }
        } else if (lbl_804D6680[0] == 0) {
            u8* bp = (u8*) &lbl_80473AB8[bracketIdx];
            s32 j;

            for (j = 0; j < 4; j++) {
                if (bp[0x30] != 0 && bp[0x4C] == 0) {
                    u8* entry = (u8*) &lbl_80473AB8[bracketIdx];
                    lbl_804D6680[1] = entry[j * 0x2C + 0x4D];
                    break;
                }
                bp += 0x2C;
            }

            lbAudioAx_80023F28(
                fn_80160400(fn_8018F6FC(lbl_804D6680[1])));
            lbl_804D6680[0] = 1;
        } else if (lbl_804D6680[0] == 1) {
            u8* timer_ptr = &lbl_804D6680[2];
            if (*timer_ptr > 0x3C) {
                lbl_804D6680[0] = 2;
            }
            (*timer_ptr)++;
        }
    }

    if (lbl_804799D8.x0[0x4D] != 1) {
        buttons = (u32) gm_801A36A0(lbl_804799D8.x0[0x4C]);
    } else {
        buttons = (u32) gm_801A36A0(4);
    }

    if (lbl_80473AB8[bracketIdx].x18 != 0) {
        if (*counter < 0xFAU) {
            (*counter)++;
            if (*counter >= 0x64U) {
                s32 count = (u32)(*counter - 0x64) / 15;
                u8* base = (u8*) counter;
                u8* dest = (u8*) &sp_buf;
                s32 i;
                for (i = 0; i < count; i++) {
                    dest[0] = base[0x4E];
                    dest[1] = base[0x4F];
                    base += 2;
                    dest += 2;
                }
            }
            HSD_SisLib_803A70A0((void*) tm->x524[3], 0, &sp_buf);
        } else {
            *counter += 2;
            if (lbl_804799D8.x0[0x4D] != 1) {
                if (*counter > 0xFAU) {
                    *counter = 0xFA;
                }
            }
            HSD_SisLib_803A70A0((void*) tm->x524[3], 0, (u8*) counter + 0x4E);
        }
    } else {
        if (*counter < 0xFAU) {
            *counter = 0xFA;
        }
    }

    if (*arg0 == 0x27) {
        if (*counter >= 0xFAU) {
            if (tm->x33 == 6) {
                if (*counter >= 0x1C20U || (buttons & 0x1100)) {
                    gm_801A42F8(1);
                    gm_801A4B60();
                }
            } else {
                fn_8018EC48();
                *arg0 = 0x13;
            }
        }
    }
}

/// @todo Currently 89.97% match - permuter couldn't improve
/// Per-frame update for tournament mode menu.
void gm_8019B2DC_OnFrame(void)
{
    s32 sp[13];
    u32 arg1;
    TmData* data;
    u32 arg2;
    s32 cond;
    s32 val;
    s32 i;
    s32* dest;
    TmData* ptr;
    s32 stage;
    PAD_STACK(4);

    data = gm_8018F634();
    arg1 = fn_8018F674(4);
    arg2 = fn_8018F640(4);

    if (gm_8018F634()->cur_option >= 0x13 && gm_8018F634()->cur_option <= 0x1A)
    {
        cond = 1;
    } else {
        cond = 0;
    }
    if (cond != 0) {
        fn_8019A71C((s32*) data, arg1, arg2);
    } else {
        if (gm_8018F634()->cur_option >= 0x1B &&
            gm_8018F634()->cur_option <= 0x1E)
        {
            cond = 1;
        } else {
            cond = 0;
        }
        if (cond != 0) {
            fn_8019A86C((s32*) data, arg1, arg2);
        } else {
            fn_8019AF50((s32*) data, arg1, arg2);
        }
    }

    val = data->stage_selection_type;
    if ((val == 0 && data->x32 == 0) || val == 1) {
        cond = 1;
    } else {
        cond = 0;
    }
    if (cond != 0) {
        stage = lbl_804D4190;
    } else {
        stage = data->x28;
    }
    sp[0] = stage;

    ptr = data;
    dest = sp;
    i = 0;
    do {
        dest[1] = ptr->x4B8[0].x0;
        dest[5] = fn_8018F6FC(ptr->x4B8[0].x1);
        i += 1;
        dest[9] = ptr->x4B8[0].x3;
        ptr = (TmData*) ((u8*) ptr + 0xA);
        dest += 1;
    } while (i < 4);

    fn_8019BA04(sp);
}

extern SceneDesc* lbl_804D6670;

/// Transitions to results screen after a tournament match.
/// Ranks players, preloads stage/character data, and starts audio.
void fn_8019B458(s32* arg0)
{
    TmData* tm = (TmData*) arg0;
    s32 i;
    u8 rank = 0;
    s32 x24;
    u8* ptr;
    TmData* td;

    s32 costumes[4];
    s32 charIDs[4];

    tm->x24++;
    *(u32*) &lbl_804799D8 = 0;
    tm->pad_x34[0] = tm->x33;

    td = gm_8018F634();
    x24 = td->x24;
    ptr = lbl_803DA0D0;
    ptr += td->entrants * 6;

    if (x24 > (s32) ptr[0x23]) {
        rank = 6;
    } else {
        ptr += 5;
        if (x24 <= (s32) ptr[0x1E]) {
            rank = 5;
        }
        if (x24 <= (s32) (--ptr)[0x1E]) {
            rank = 4;
        }
        if (x24 <= (s32) (--ptr)[0x1E]) {
            rank = 3;
        }
        if (x24 <= (s32) (--ptr)[0x1E]) {
            rank = 2;
        }
        if (x24 <= (s32) (--ptr)[0x1E]) {
            rank = 1;
        }
        if (x24 <= (s32) (--ptr)[0x1E]) {
            rank = 0;
        }
    }

    tm->x33 = rank;

    {
        s32 match = fn_80196CF8();
        TmData* td2 = gm_8018F634();
        fn_80198D18();

        {
            HSD_GObj* gobj = fn_8019035C(
                0, lbl_804D6670->models[3], match, 0x1A, 3, 1,
                fn_80196EEC, 0.0f);

            if ((s32) td2->pad_x34[0] == match) {
                HSD_JObjSetFlagsAll(gobj->hsd_obj, 0x10U);
            }
        }

        if (match < 4) {
            lbl_804799D8.x1B = 0x50;
        } else if (match == 4) {
            lbl_804799D8.x1B = 0x5F;
        } else {
            lbl_804799D8.x1B = 0x61;
        }

        fn_80198BA0();
        fn_8018E618(tm->entrants, (s32) tm->x2C, 4.5f);
        fn_8018E85C((int) lbl_804D6670->models[4], tm->x2C);
        fn_8018FA24();

        tm->cur_option = 0x14;
        tm->x2C = 0;

        for (i = 0; i < 4; i++) {
            if (tm->x4B8[i].x0 != 3) {
                charIDs[i] = fn_8018F6FC(tm->x4B8[i].x1);
                costumes[i] = tm->x4B8[i].x3;
            }
        }

        {
            InternalStageId stageID;

            if ((tm->stage_selection_type == 0 && tm->x32 == 0) ||
                tm->stage_selection_type == 1)
            {
                gm_8018F634();
                do {
                    lbl_804D4190 = fn_8018F4A0();
                    if (lbl_804D4194 == lbl_804D4190) {
                        if (fn_801642A0() != 0) {
                            break;
                        }
                    } else {
                        break;
                    }
                } while (true);
                lbl_804D4194 = lbl_804D4190;
                stageID = lbl_804D4190;
            } else {
                stageID = tm->x28;
            }

            {
                PreloadCacheScene* scene = lbDvd_8001822C();
                struct GameCache* gc = &scene->game_cache;
                lbDvd_800174BC();

                if (tm->x4B8[0].x0 != 3) {
                    gc->entries[0].char_id = charIDs[0];
                    gc->entries[0].color = costumes[0];
                }

                if (tm->x4B8[1].x0 != 3) {
                    gc->entries[1].char_id = charIDs[1];
                    gc->entries[1].color = costumes[1];
                }

                if (tm->x4B8[2].x0 != 3) {
                    gc->entries[2].char_id = charIDs[2];
                    gc->entries[2].color = costumes[2];
                }

                if (tm->x4B8[3].x0 != 3) {
                    gc->entries[3].char_id = charIDs[3];
                    gc->entries[3].color = costumes[3];
                }

                if (!((tm->stage_selection_type == 2 && tm->x32 == 0) ||
                      tm->stage_selection_type == 3))
                {
                    gc->stage_id = stageID;
                }

                lbDvd_80018254();
            }

            {
                u64 audio_mask = 0;
                for (i = 0; i < 4; i++) {
                    if (tm->x4B8[i].x0 != 3) {
                        audio_mask |= lbAudioAx_80026E84(charIDs[i]);
                    }
                }
                audio_mask |= lbAudioAx_80026EBC(stageID);
                lbAudioAx_80026F2C(0x1C);
                lbAudioAx_8002702C(0xC, audio_mask);
                lbAudioAx_80027168();
            }
        }
    }
}

/// Initializes match data and transitions to next state.
/// Type cast used to match target stw instruction pattern.
void fn_8019B81C(s32* state)
{
    fn_80198BA0();
    fn_80198EBC();
    *state = 0x1C;
    *(u32*) &lbl_804799D8 = 0;
}

extern SceneDesc* lbl_804D6670;

void fn_8019B860(TmData* tm)
{
    fn_8019A158();
    fn_80199AF0();
    fn_80198BA0();
    fn_8018F888();
    fn_8018E618(tm->entrants, (s32) tm->x2C, 4.5f);
    fn_8018E85C(*(int*) ((char*) lbl_804D6670->models + 0x10), tm->x2C);
    tm->cur_option = 0x20;
}
