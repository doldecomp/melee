#include "mplib.h"

#include "mpisland.h"

#include "mplib.static.h"

#include "types.h"

#include <math.h>
#include <dolphin/mtx.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/tev.h>
#include <sysdolphin/baselib/texp.h>
#include <melee/cm/camera.h>
#include <melee/cm/types.h>
#include <melee/gr/stage.h>
#include <melee/lb/types.h>

UNK_T mpLib_8004D164(void)
{
    return mpLib_804D64B4;
}

mpLib_Point* mpLib_8004D16C(void)
{
    return mpLib_Points;
}

mpLib_Line* mpLib_8004D174(void)
{
    return mpLib_Lines;
}

mpLib_804D64C0_t* mpLib_8004D17C(void)
{
    return mpLib_804D64C0;
}

/// #mpLib_8004D184

/// #mpLib_8004D288

int mpLib_8004DB78(int gr_idx)
{
    mpLib_LineInner* temp_r6 = mpLib_Lines[gr_idx].x0;
    s16 result = temp_r6->xA;

    if (result != -1) {
        u32 temp_r4 = mpLib_Lines[result].flags;

        if ((temp_r4 & 0x10000) && !(temp_r4 & 0x40000)) {
            mpLib_Point* temp_r4_2 = &mpLib_Points[temp_r6->p1_idx];
            mpLib_Point* temp_r5 =
                &mpLib_Points[mpLib_Lines[result].x0->p0_idx];

            float dx = temp_r4_2->pos.x - temp_r5->pos.x;
            float dy = temp_r4_2->pos.y - temp_r5->pos.y;
            float dx2 = dx * dx;
            float dy2 = dy * dy;

            if (dx2 + dy2 < 4.0) {
                return result;
            }
        }
    }

    return temp_r6->x6;
}

int mpLib_8004DC04(int gr_idx)
{
    mpLib_LineInner* temp_r6 = mpLib_Lines[gr_idx].x0;
    s16 result = temp_r6->x8;

    if (result != -1) {
        u32 temp_r4 = mpLib_Lines[result].flags;

        if ((temp_r4 & 0x10000) && !(temp_r4 & 0x40000)) {
            mpLib_Point* temp_r4_2 = &mpLib_Points[temp_r6->p0_idx];
            mpLib_Point* temp_r5 =
                &mpLib_Points[mpLib_Lines[result].x0->p1_idx];

            float dx = temp_r4_2->pos.x - temp_r5->pos.x;
            float dy = temp_r4_2->pos.y - temp_r5->pos.y;
            float dx2 = dx * dx;
            float dy2 = dy * dy;

            if (dx2 + dy2 < 4.0) {
                return result;
            }
        }
    }

    return temp_r6->x4;
}

/// #mpLib_8004DC90

/// #mpLib_8004DD90

/// #mpLib_8004E090

/// #mpLib_8004E398

/// #mpLib_8004E684

bool mpLib_8004E97C(float arg0, float arg1, float arg2, float arg3, float arg4,
                    float arg5, float arg6, float arg7, float* arg8,
                    float* arg9)
{
    bool r0 = false;
    bool r5 = false;

    if (arg0 <= arg2) {
        if ((arg4 < arg0 && arg6 < arg0) || (arg2 < arg4 && arg2 < arg6)) {
            return false;
        }
    } else if ((arg4 < arg2 && arg6 < arg2) || (arg0 < arg4 && arg0 < arg6)) {
        return false;
    }

    if (arg1 <= arg3) {
        if ((arg5 < arg1 && arg7 < arg1) || (arg3 < arg5 && arg3 < arg7)) {
            return false;
        }
    } else if ((arg5 < arg3 && arg7 < arg3) || (arg1 < arg5 && arg1 < arg7)) {
        return false;
    }

    {
        double f11 = arg3 - arg1;
        double f10 = arg4 - arg0;
        double f13 = arg2 - arg0;
        double f12 = arg5 - arg1;
        double f31 = (f13 * f12) - (f11 * f10);
        double f29;
        double f30;
        double f0;
        double f9;
        double f6;
        double f7;

        if (f31 < 0.0) {
            if (f31 < -0.1) {
                return false;
            }
            r0 = true;
        }

        f30 = arg6 - arg2;
        f29 = arg7 - arg3;

        f9 = (f13 * f29) - (f11 * f30);
        if (f9 > 0.0) {
            if (f9 > 0.1) {
                return false;
            }
            r5 = true;
        }

        if (f31 == 0.0 && f9 == 0.0) {
            return false;
        }

        f0 = (f10 * f29) - (f12 * f30);
        if (f0 < f31) {
            if (f0 < f9) {
                return false;
            }
        } else if (f0 > f31) {
            if (f0 > f9) {
                return false;
            }
        }

        f7 = arg6 - arg4;
        f6 = arg7 - arg5;
        if (!((f7 == 0.0 && f6 == 0.0) || (r0 && r5) || (f31 >= 0.0 && r5))) {
            double f5 = (f7 * f11) - (f6 * f13);

            if (ABS(f5) > 0.0001F) {
                double f5_2 = ((f7 * f12) - (f6 * f10)) / f5;
                if (f5_2 > 0.0) {
                    if (f5_2 < 1.0) {
                        *arg8 = (f13 * f5_2) + arg0;
                        *arg9 = (f11 * f5_2) + arg1;
                    } else {
                        *arg8 = arg2;
                        *arg9 = arg3;
                    }
                } else {
                    *arg8 = arg0;
                    *arg9 = arg1;
                }

                goto tlabel;
            }
        }
        return false;
    tlabel:
        return true;
    }
}

bool mpLib_8004EBF8(f32* arg0, f32* arg1, f32 arg8, f32 arg9, f32 argA,
                    f32 argB, f32 argC, f32 argD, f32 argE)
{
    f32 d2;
    f64 d1;
    f32 var_f3;
    f32 var_f8;
    f64 var_f5;

    var_f3 = argA;
    if (arg8 < var_f3) {
        if ((argB < arg8 && argD < arg8) || (var_f3 < argB && var_f3 < argD)) {
            return false;
        }
        if (argC - arg9 < -0.0001 || argE - arg9 > 0.0001) {
            return false;
        }
        var_f8 = arg8;
    } else {
        if ((argB < var_f3 && argD < var_f3) || (arg8 < argB && arg8 < argD)) {
            return false;
        }
        if (argE - arg9 < -0.0001 || argC - arg9 > 0.0001) {
            return false;
        }
        var_f8 = var_f3;
        var_f3 = arg8;
    }
    d1 = argE - argC;
    d2 = argD - argB;
    if (ABS(d1) < 0.0001) {
        return false;
    }
    var_f5 = d2 / d1 * (arg9 - argC) + argB;
    if (d2 / d1 * (arg9 - argC) + argB - var_f8 < 0.0) {
        if (d2 / d1 * (arg9 - argC) + argB - var_f8 < -0.1) {
            return false;
        }
        var_f5 = var_f8;
    }
    if (var_f5 - var_f3 > 0.0) {
        if (var_f5 - var_f3 > 0.1) {
            return false;
        }
        var_f5 = var_f3;
    }
    *arg0 = var_f5;
    *arg1 = arg9;
    return true;
}

/// #mpLib_8004ED5C

/// #mpLib_8004F008

/// #mpLib_8004F400

/// #mpLib_8004F8A4

/// #mpLib_8004FC2C

/// #mpLib_80050068

/// #mpLib_800501CC

/// #mpLib_8005057C

/// #mpLib_800509B8

/// #mpLib_80050D68

/// #mpLib_800511A4

/// #mpLib_800515A0

/// #mpLib_8005199C

int mpLib_80051BA8(Vec3* arg0, int arg1, int arg2, int arg3, int arg4,
                   f32 arg5, f32 arg6, f32 arg7, f32 arg8)
{
    f32 var_f31;
    f32 var_f30;
    f32 var_f29;
    f32 var_f26;

    f32 temp_f0;
    f32 temp_f6;
    f32 var_f6;
    f32 var_f6_2;
    f32 temp_f8;
    f32 temp_f10;
    f32 var_f11;
    f32 var_f12;
    f32 var_f13;

    int var_r30;
    int temp_r24;
    mpLib_LineInner* temp_r24_2;
    mpLib_Point* temp_r23;
    mpLib_Point* temp_r23_2;

    int var_r12;
    int var_r11;
    mpLib_Line* var_r10;
    int var_r9;
    mpLib_804D64C0_t* var_r8;
    int temp_r7;
    int temp_r6;
    struct mpLib_804D64C0_x4_t* temp_r6_2;
    bool temp_r3;

    var_r30 = -1;
    if (arg4 > 0) {
        var_f31 = +F32_MAX;
    } else if (arg4 < 0) {
        var_f31 = -F32_MAX;
    } else {
        __assert(__FILE__, 0xEED, "0");
    }
    temp_r3 = mpLib_800588C8();
    if (!temp_r3) {
        mpLib_800588D0(arg5, arg6, arg7, arg8);
    }
    var_r8 = mpLib_804D64C4;
    while (var_r8 != NULL) {
        if (!(var_r8->flags & 0x1000)) {
            temp_r6 = var_r8 - mpLib_804D64C0;
            if (arg2 != temp_r6 && (arg3 == -1 || arg3 == temp_r6)) {
                temp_r6_2 = var_r8->x4;
                var_r9 = 0;
                var_r11 = temp_r6_2->x2;
                var_r12 = temp_r6_2->x12;
                var_r10 = &mpLib_Lines[temp_r6_2->x0];
                while (var_r9 < var_r11) {
                block_13:
                    temp_r7 = var_r10 - mpLib_Lines;
                    if (arg1 != temp_r7) {
                        temp_r24 = var_r10->flags;
                        if ((temp_r24 & 1) && (temp_r24 & 0x10000) &&
                            !(temp_r24 & 0x80))
                        {
                            temp_r24_2 = var_r10->x0;
                            if (temp_r24_2->xE & 0x200) {
                                temp_r23 = &mpLib_Points[temp_r24_2->p0_idx];
                                temp_f6 = temp_r23->pos.x;
                                temp_f8 = temp_r23->pos.y;
                                temp_r23_2 = &mpLib_Points[temp_r24_2->p1_idx];
                                temp_f0 = temp_r23_2->pos.x;
                                temp_f10 = temp_r23_2->pos.y;
                                if (temp_f6 > temp_f0) {
                                    var_f13 = temp_f6;
                                    var_f11 = temp_f0;
                                } else {
                                    var_f11 = temp_f6;
                                    var_f13 = temp_f0;
                                }
                                if (temp_f8 > temp_f10) {
                                    var_f26 = temp_f8;
                                    var_f12 = temp_f10;
                                } else {
                                    var_f12 = temp_f8;
                                    var_f26 = temp_f10;
                                }
                                var_f6 =
                                    ABS((var_f13 + var_f11) - (arg7 + arg5));
                                if (var_f6 <
                                    ((var_f13 - var_f11) + (arg7 - arg5)))
                                {
                                    var_f6_2 = ABS((var_f26 + var_f12) -
                                                   (arg8 + arg6));
                                    if (var_f6_2 <
                                        ((var_f26 - var_f12) + (arg8 - arg6)))
                                    {
                                        if (arg4 > 0) {
                                            if (var_f31 > temp_f6) {
                                                var_f31 = temp_f6;
                                                var_r30 = temp_r7;
                                                if (arg0 != NULL) {
                                                    var_f30 = temp_f6;
                                                    var_f29 = temp_f8;
                                                }
                                            }
                                        } else if ((arg4 < 0) &&
                                                   (var_f31 < temp_f0))
                                        {
                                            var_f31 = temp_f0;
                                            var_r30 = temp_r7;
                                            if (arg0 != NULL) {
                                                var_f30 = temp_f0;
                                                var_f29 = temp_f10;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    var_r9 += 1;
                    var_r10 += 1;
                }
                if (var_r12 != 0) {
                    var_r11 = var_r12;
                    var_r9 = 0;
                    var_r10 = &mpLib_Lines[temp_r6_2->x10];
                    var_r12 = 0;
                    goto block_13;
                }
            }
        }
        var_r8 = var_r8->next;
    }
    if (!temp_r3) {
        mpLib_80058AA0();
    }
    if (var_r30 != -1 && arg0 != NULL) {
        if (var_f30 > arg7) {
            var_f30 = arg7;
        } else if (var_f30 < arg5) {
            var_f30 = arg5;
        }
        arg0->x = var_f30;
        arg0->y = var_f29;
        arg0->z = 0.0F;
    }
    return var_r30;
}

bool mpLib_80051EC8(Vec3* arg0, int* arg1, int* arg2, Vec3* arg3, u32 arg4,
                    s32 arg5, s32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA)
{
    f32 dx;
    f32 dy;

    f32 var_f31;
    bool temp_r3;

    s32 var_r30;
    s32 var_r29;

    Vec3 sp68;
    Vec3 sp5C;
    Vec3 sp50;
    Vec3 sp44;
    int sp40;
    int sp3C;

    var_f31 = F32_MAX;
    temp_r3 = mpLib_800588C8();
    if (!temp_r3) {
        mpLib_80058970(arg7, arg8, arg9, argA);
    }
    if (arg4 & 0x10) {
        if (arg4 & 1) {
            if (mpLib_8004F400(&sp68, &sp40, &sp3C, &sp5C, -1, arg5, arg6, 0,
                               0, arg7, arg8, arg9, argA, 0.0F))
            {
                dx = SQ(sp68.x - arg7);
                dy = SQ(sp68.y - arg8);
                sp50 = sp68;
                sp44 = sp5C;
                var_f31 = dx + dy;
                var_r30 = sp40;
                var_r29 = sp3C;
            }
        }
        if ((arg4 & 2) && (mpLib_8004FC2C(&sp68, &sp40, &sp3C, &sp5C, arg5,
                                          arg6, arg7, arg8, arg9, argA)))
        {
            dx = SQ(sp68.x - arg7);
            dy = SQ(sp68.y - arg8);
            if (var_f31 > dx + dy) {
                var_f31 = dx + dy;
                sp50 = sp68;
                sp44 = sp5C;
                var_r30 = sp40;
                var_r29 = sp3C;
            }
        }
        if ((arg4 & 4) && (mpLib_8005057C(&sp68, &sp40, &sp3C, &sp5C, arg5,
                                          arg6, arg7, arg8, arg9, argA)))
        {
            dx = SQ(sp68.x - arg7);
            dy = SQ(sp68.y - arg8);
            if (var_f31 > dx + dy) {
                var_f31 = dx + dy;
                sp50 = sp68;
                sp44 = sp5C;
                var_r30 = sp40;
                var_r29 = sp3C;
            }
        }
        if ((arg4 & 8) && (mpLib_80050D68(&sp68, &sp40, &sp3C, &sp5C, arg5,
                                          arg6, arg7, arg8, arg9, argA)))
        {
            dx = SQ(sp68.x - arg7);
            dy = SQ(sp68.y - arg8);
            if (var_f31 > dx + dy) {
                var_f31 = dx + dy;
                sp50 = sp68;
                sp44 = sp5C;
                var_r30 = sp40;
                var_r29 = sp3C;
            }
        }
    } else {
        if (arg4 & 1) {
            if (mpLib_8004F008(&sp68, &sp40, &sp3C, &sp5C, arg7, arg8, arg9,
                               argA, 0.0F, -1, arg5, arg6, 0, 0))
            {
                dx = SQ(sp68.x - arg7);
                dy = SQ(sp68.y - arg8);
                sp50 = sp68;
                sp44 = sp5C;
                var_f31 = dx + dy;
                var_r30 = sp40;
                var_r29 = sp3C;
            }
        }
        if ((arg4 & 2) && (mpLib_8004F8A4(&sp68, &sp40, &sp3C, &sp5C, arg5,
                                          arg6, arg7, arg8, arg9, argA)))
        {
            dx = SQ(sp68.x - arg7);
            dy = SQ(sp68.y - arg8);
            if (var_f31 > dx + dy) {
                var_f31 = dx + dy;
                sp50 = sp68;
                sp44 = sp5C;
                var_r30 = sp40;
                var_r29 = sp3C;
            }
        }
        if ((arg4 & 4) && (mpLib_800501CC(arg7, arg8, arg9, argA, &sp68, &sp40,
                                          &sp3C, &sp5C, arg5, arg6)))
        {
            dx = SQ(sp68.x - arg7);
            dy = SQ(sp68.y - arg8);
            if (var_f31 > dx + dy) {
                var_f31 = dx + dy;
                sp50 = sp68;
                sp44 = sp5C;
                var_r30 = sp40;
                var_r29 = sp3C;
            }
        }
        if ((arg4 & 8) && (mpLib_800509B8(arg7, arg8, arg9, argA, &sp68, &sp40,
                                          &sp3C, &sp5C, arg5, arg6)))
        {
            dx = SQ(sp68.x - arg7);
            dy = SQ(sp68.y - arg8);
            if (var_f31 > dx + dy) {
                var_f31 = dx + dy;
                sp50 = sp68;
                sp44 = sp5C;
                var_r30 = sp40;
                var_r29 = sp3C;
            }
        }
    }
    if (!temp_r3) {
        mpLib_80058AA0();
    }
    if (var_f31 < F32_MAX) {
        if (arg0 != NULL) {
            *arg0 = sp50;
        }
        if (arg1 != NULL) {
            *arg1 = var_r30;
        }
        if (arg2 != NULL) {
            *arg2 = var_r29;
        }
        if (arg3 != NULL) {
            *arg3 = sp44;
        }
        return true;
    }
    return false;
}

bool mpLib_800524DC(Vec3* arg0, int* arg1, int* arg2, Vec3* arg3, int arg4,
                    int arg5, f32 x, f32 y, f32 z, f32 arg9)
{
    return mpLib_80051EC8(arg0, arg1, arg2, arg3, 0x1F, arg4, arg5, x, y, z,
                          arg9);
}

bool mpLib_80052508(Vec3* arg0, int* arg1, int* arg2, Vec3* arg3, u32 arg4,
                    u32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9)
{
    return mpLib_80051EC8(arg0, arg1, arg2, arg3, 0xF, arg4, arg5, arg6, arg7,
                          arg8, arg9);
}

/// #mpLib_80052534

/// #mpLib_80052700

/// #mpLib_800528CC

/// #mpLib_80052A98

/// #mpLib_80052C64

/// #mpLib_80052E30

/// #mpLib_80052FFC

/// #mpLib_800531C8

/// #mpLib_80053394

/// #mpLib_80053448

/// #mpLib_800534FC

/// #mpLib_800536CC

int mpLib_8005389C(int line)
{
    mpLib_Line* temp_r5;
    int cur;

    if (line == -1 || line >= mpLib_804D64B4->xC) {
        OSReport("%s:%d:not found lineID=%d\n", __FILE__, 0x10DA, line);
        __assert(__FILE__, 0x10DA, "0");
    }
    cur = mpLib_Lines[line].x0->x4;
    while (cur != -1 && (mpLib_Lines[cur].flags & 2)) {
        cur = mpLib_Lines[cur].x0->x4;
    }
    if (cur != -1) {
        return cur;
    }
    return -1;
}

int mpLib_80053950(int line)
{
    int cur;
    if (line == -1 || line >= mpLib_804D64B4->xC) {
        OSReport("%s:%d:not found lineID=%d\n", __FILE__, 0x10E3, line);
        __assert(__FILE__, 0x10E3, "0");
    }
    cur = mpLib_Lines[line].x0->x6;
    while (cur != -1 && (mpLib_Lines[cur].flags & 2)) {
        cur = mpLib_Lines[cur].x0->x6;
    }
    if (cur != -1) {
        return cur;
    }
    return -1;
}

/// #mpLib_80053A04

/// #mpLib_80053BD4

/// #mpLib_80053DA4

/// #mpLib_80053ECC

/// #mpLib_80053FF4

/// #mpLib_80054158

/// #mpLib_800542BC

/// #mpLib_80054420

/// #mpLib_80054584

/// #mpLib_800546E8

/// #mpLib_8005484C

/// #mpLib_800549B0

void mpLib_80054B14(int line, Vec3* arg1)
{
    mpLib_Point* temp_r3;

    if (line == -1 || line >= mpLib_804D64B4->xC) {
        OSReport("%s:%d:not found lineID=%d\n", __FILE__, 0x11BC, line);
        __assert(__FILE__, 0x11BC, "0");
    }
    temp_r3 = &mpLib_Points[mpLib_Lines[line].x0->p1_idx];
    arg1->x = temp_r3->pos.x;
    arg1->y = temp_r3->pos.y;
    arg1->z = 0.0F;
}

void mpLib_80054BC0(int line, Vec3* arg1)
{
    mpLib_Point* temp_r3;

    if (line == -1 || line >= mpLib_804D64B4->xC) {
        OSReport("%s:%d:not found lineID=%d\n", __FILE__, 0x11CB, line);
        __assert(__FILE__, 0x11CB, "0");
    }
    temp_r3 = &mpLib_Points[mpLib_Lines[line].x0->p0_idx];
    arg1->x = temp_r3->pos.x;
    arg1->y = temp_r3->pos.y;
    arg1->z = 0.0F;
}

enum_t mpLib_80054C6C(int line)
{
    if (line == -1 || line >= mpLib_804D64B4->xC) {
        OSReport("%s:%d:not found lineID=%d\n", __FILE__, 0x11DD, line);
        __assert(__FILE__, 0x11DD, "0");
    }
    return mpLib_Lines[line].flags & 0xF;
}

u32 mpLib_80054CEC(int line)
{
    if (line == -1 || line >= mpLib_804D64B4->xC) {
        OSReport("%s:%d:not found lineID=%d\n", __FILE__, 0x11E7, line);
        __assert(__FILE__, 0x11E7, "0");
    }
    return mpLib_Lines[line].x0->xE;
}

void mpLib_80054D68(int line, u32 arg1)
{
    if (line == -1 || line >= mpLib_804D64B4->xC) {
        OSReport("%s:%d:not found lineID=%d\n", __FILE__, 0x11F3, line);
        __assert(__FILE__, 0x11F3, "0");
    }
    {
        mpLib_LineInner* temp_r3 = mpLib_Lines[line].x0;
        u16* tmp = &temp_r3->xE;
        *tmp = (*tmp & 0xFFFFFF00) | arg1;
    }
}

Vec3* mpLib_80054DFC(int line, Vec3* arg1)
{
    mpLib_LineInner* temp_r4;
    PAD_STACK(4);

    if (line == -1 || line >= mpLib_804D64B4->xC) {
        OSReport("%s:%d:not found lineID=%d\n", __FILE__, 0x1201, line);
        __assert(__FILE__, 0x1201, "0");
    }
    temp_r4 = mpLib_Lines[line].x0;
    {
        float y0 = mpLib_Points[temp_r4->p0_idx].pos.y;
        float y1 = mpLib_Points[temp_r4->p1_idx].pos.y;
        float x0 = mpLib_Points[temp_r4->p0_idx].pos.x;
        float x1 = mpLib_Points[temp_r4->p1_idx].pos.x;
        arg1->x = -(y1 - y0);
        arg1->y = +(x1 - x0);
        arg1->z = 0.0F;
    }
    PSVECNormalize(arg1, arg1);
    return arg1;
}

bool mpLib_80054ED8(int line)
{
    if (line == -1) {
        return false;
    }
    if (line < 0 || line >= mpLib_804D64B4->xC) {
        OSReport("%s:%d:not found lineID=%d\n", __FILE__, 0x121C, line);
        while (true) {
        };
    }
    if (!(mpLib_Lines[line].flags & 0x10000) ||
        (mpLib_Lines[line].flags & 0x40000))
    {
        return false;
    }
    return true;
}

/// #mpLib_80054F68

/// #mpLib_800552B0

/// #mpLib_8005541C

/// #mpLib_800557D0

void mpLib_80055C5C(int index)
{
    mpLib_804D64C0_t* temp_r31 = &mpLib_804D64C0[index];
    mpLib_Line* var_r30;
    int i;
    s16 temp_r28 = temp_r31->x4->x12;
    u32 var_r27;

    f32 temp_f0;
    f32 temp_f2;

    var_r30 = &mpLib_Lines[temp_r31->x4->x10];

    for (i = 0; i < temp_r28; i++, var_r30++) {
        mpLib_LineInner* temp_r5 = var_r30->x0;
        mpLib_Point* temp_r3 = &mpLib_Points[temp_r5->p1_idx];
        mpLib_Point* temp_r3_2 = &mpLib_Points[temp_r5->p0_idx];
        temp_f2 = temp_r3->pos.x - temp_r3_2->pos.x;
        temp_f0 = temp_r3->pos.y - temp_r3_2->pos.y;
        if (temp_f2 > 0.0F) {
            if (temp_f0 / temp_f2 > 1.7320508368950045) {
                var_r27 = 8;
            } else if (temp_f0 / temp_f2 < -1.7320508368950045) {
                var_r27 = 4;
            } else {
                var_r27 = 1;
            }
        } else if (temp_f2 < 0.0F) {
            if (temp_f0 / temp_f2 > 0.577350295784245) {
                var_r27 = 4;
            } else if (temp_f0 / temp_f2 < -0.577350295784245) {
                var_r27 = 8;
            } else {
                var_r27 = 2;
            }
        } else if (temp_f0 > 0.0F) {
            var_r27 = 8;
        } else if (temp_f0 < 0.0F) {
            var_r27 = 4;
        } else {
            __assert(__FILE__, 0x1314, "0");
        }
        var_r30->flags = (var_r30->flags & 0xFFFFFFF0) | var_r27;
        if ((temp_r31->flags & 0x10000) && (var_r30->x0->xE & 0x400)) {
            if (var_r27 & 1) {
                var_r30->flags |= 0x10000 | 0x100;
                var_r30->x0->xE |= 0x100;
            } else {
                var_r30->flags &= ~0x10000;
            }
        }
    }
}

void mpLib_80055E24(int index)
{
    bool var_r6;
    mpLib_804D64C0_t* temp_r31 = &mpLib_804D64C0[index];

    mpLib_80055C5C(index);
    var_r6 = false;
    if (!(temp_r31->flags & 0x40800) && (temp_r31->flags & 0x10000)) {
        var_r6 = true;
    }
    mpIsland_8005B334(index, temp_r31->x4->x24, temp_r31->x4->x26, var_r6);
}

/// #mpLib_80055E9C

void mpLib_800565DC(int index)
{
    mpLib_804D64C0_t* temp_r5 = &mpLib_804D64C0[index];
    mpLib_Point* cur = &mpLib_Points[temp_r5->x4->x24];
    int temp_r4_2 = temp_r5->x4->x26;

    int i;
    for (i = 0; i < temp_r4_2; i++) {
        if (temp_r5->x10 > cur->pos.x - 30.0F) {
            temp_r5->x10 = cur->pos.x - 30.0F;
        }
        if (temp_r5->x18 < cur->pos.x + 30.0F) {
            temp_r5->x18 = cur->pos.x + 30.0F;
        }
        if (temp_r5->x14 > cur->pos.y - 30.0F) {
            temp_r5->x14 = cur->pos.y - 30.0F;
        }
        if (temp_r5->x1C < cur->pos.y + 30.0F) {
            temp_r5->x1C = cur->pos.y + 30.0F;
        }
        cur += 1;
    }
}

void mpLib_8005667C(int index)
{
    bool var_r6 = false;
    mpLib_804D64C0_t* temp_r7 = &mpLib_804D64C0[index];

    if (!(temp_r7->flags & 0x40800) && (temp_r7->flags & 0x10000)) {
        var_r6 = true;
    }
    mpIsland_8005B334(index, temp_r7->x4->x24, temp_r7->x4->x26, var_r6);
}

void mpLib_800566D8(int index, f32* arg1, f32* arg2)
{
    mpLib_Point* temp_r3 = &mpLib_Points[index];
    *arg1 = temp_r3->pos.x;
    *arg2 = temp_r3->pos.y;
}

void mpLib_800566F8(int index, float arg1, float arg2)
{
    mpLib_Point* temp_r3 = &mpLib_Points[index];
    temp_r3->pos.x = arg1;
    temp_r3->pos.y = arg2;
}

void mpLib_80056710(int index, f32 arg8, f32 arg9, f32 argA, f32 argB)
{
    mpLib_Line* temp_r5 = &mpLib_Lines[index];
    mpLib_800566F8(temp_r5->x0->p0_idx, arg8, arg9);
    mpLib_800566F8(temp_r5->x0->p1_idx, argA, argB);
}

void mpLib_80056758(int index, f32 arg8, f32 arg9, f32 argA, f32 argB)
{
    mpLib_Line* temp_r5 = &mpLib_Lines[index];

    mpLib_Point* temp_r3 = &mpLib_Points[temp_r5->x0->p0_idx];
    temp_r3->pos.x = temp_r3->x0 + arg8;
    temp_r3->pos.y = temp_r3->x4 + arg9;

    temp_r3 = &mpLib_Points[temp_r5->x0->p1_idx];
    temp_r3->pos.x = temp_r3->x0 + argA;
    temp_r3->pos.y = temp_r3->x4 + argB;
}

/// #mpLib_800567C0

/// #mpLib_800569EC

/// #mpLib_80056A1C

/// #mpLib_80056A54

/// #mpLib_80056A8C

/// #mpLib_80056AC4

/// #mpLib_80056AFC

/// #mpLib_80056B34

int mpLib_80056B6C(int line)
{
    int i;
    int temp_r6_2;
    mpLib_804D64C0_t* var_r7;

    if (line != -1) {
        if (line == -1 || line >= mpLib_804D64B4->xC) {
            OSReport("%s:%d:not found lineID=%d\n", __FILE__, 0x1553, line);
            __assert(__FILE__, 0x1553, "0");
        }
        temp_r6_2 = mpLib_Lines[line].x0->p0_idx;
        var_r7 = mpLib_804D64C0;
        for (i = 0; i < mpLib_804D64B4->x28; i++) {
            if (var_r7->x4->x24 <= temp_r6_2 &&
                temp_r6_2 < var_r7->x4->x24 + var_r7->x4->x26)
            {
                return var_r7 - mpLib_804D64C0;
            }
            var_r7++;
        }
    }
    return -1;
}

/// #mpLib_80056C54

/// #mpLib_80057424

void mpLib_80057528(int index)
{
    int temp_r3 = mpLib_80056B6C(index);
    if (temp_r3 != -1) {
        mpLib_Line* tmp = &mpLib_Lines[index];
        mpLib_804D64C0_t* temp_r31 = &mpLib_804D64C0[temp_r3];
        tmp->flags |= 0x10000;
        mpIsland_8005B334(temp_r3, temp_r31->x4->x24, temp_r31->x4->x26,
                          !(temp_r31->flags & 0x800));
        temp_r31->xE = true;
    }
}

void mpLib_800575B0(int index)
{
    int temp_r3 = mpLib_80056B6C(index);
    if (temp_r3 != -1) {
        mpLib_Line* tmp = &mpLib_Lines[index];
        mpLib_804D64C0_t* temp_r31 = &mpLib_804D64C0[temp_r3];
        tmp->flags &= ~0x10000;
        mpIsland_8005B334(temp_r3, temp_r31->x4->x24, temp_r31->x4->x26,
                          !(temp_r31->flags & 0x800));
        temp_r31->xE = true;
    }
}

/// #mpLib_80057638

void mpLib_80057B4C(mpLib_804D64C0_t* arg0)
{
    mpLib_804D64C0_t* cur;

    if (arg0 == mpLib_804D64C4) {
        if (arg0 == mpLib_804D64C8) {
            mpLib_804D64C8 = NULL;
            mpLib_804D64C4 = NULL;
        } else {
            mpLib_804D64C4 = mpLib_804D64C4->next;
        }
        return;
    }

    for (cur = mpLib_804D64C4; cur != NULL; cur = cur->next) {
        if (cur->next == arg0) {
            if (arg0 == mpLib_804D64C8) {
                mpLib_804D64C8 = cur;
            }
            cur->next = cur->next->next;
            return;
        }
    }
}

/// #mpLib_80057BC0

void mpLib_80057FDC(int index)
{
    struct mpLib_804D64C0_x4_t* temp_r5;
    bool var_r6 = false;
    mpLib_804D64C0_t* temp_r7 = &mpLib_804D64C0[index];

    temp_r7->flags &= ~0x800;
    if (!(temp_r7->flags & 0x40800) && (temp_r7->flags & 0x10000)) {
        var_r6 = true;
    }
    temp_r5 = temp_r7->x4;
    mpIsland_8005B334(index, temp_r5->x24, temp_r5->x26, var_r6);
}

void mpLib_80058044(int index)
{
    struct mpLib_804D64C0_x4_t* temp_r5;
    bool var_r6 = false;
    mpLib_804D64C0_t* temp_r7 = &mpLib_804D64C0[index];

    temp_r7->flags |= 0x800;
    if (!(temp_r7->flags & 0x40800) && (temp_r7->flags & 0x10000)) {
        var_r6 = true;
    }
    temp_r5 = temp_r7->x4;
    mpIsland_8005B334(index, temp_r5->x24, temp_r5->x26, var_r6);
}

void mpLib_800580AC(int index)
{
    mpLib_804D64C0_t* temp_r3 = &mpLib_804D64C0[index];
    temp_r3->flags |= 0x400;
}

void mpLib_800580C8(int index, Ground* arg1, mpLib_Callback cb)
{
    mpLib_804D64C0_t* temp_r3 = &mpLib_804D64C0[index];
    temp_r3->x24 = cb;
    temp_r3->x28 = arg1;
}

void mpLib_800580E0(int index)
{
    mpLib_804D64C0_t* temp_r3 = &mpLib_804D64C0[index];
    temp_r3->x24 = NULL;
    temp_r3->x28 = NULL;
}

void mpLib_800580FC(int index, mpLib_Callback* arg1, Ground** arg2)
{
    mpLib_804D64C0_t* temp_r3 = &mpLib_804D64C0[index];
    *arg1 = temp_r3->x24;
    *arg2 = temp_r3->x28;
}

void mpLib_8005811C(CollData* coll, int ledge_id)
{
    if (ledge_id != -1) {
        int index = mpLib_80056B6C(ledge_id);
        if (index != -1) {
            mpLib_Callback cb = mpLib_804D64C0[index].x24;
            Ground* gp = mpLib_804D64C0[index].x28;
            if (cb != NULL) {
                cb(gp, index, coll, coll->x50, 3, 0.0F);
            }
        }
    }
}

void mpLib_800581A4(int index, int arg1, int arg2)
{
    mpLib_804D64C0_t* temp_r3 = &mpLib_804D64C0[index];
    temp_r3->unk_2C = arg2;
    temp_r3->unk_30 = arg1;
}

/// #mpLib_800581BC

/// #mpLib_800581DC

void mpLib_80058560(void)
{
    struct mpLib_804D64B4_t* temp_r29 = mpLib_804D64B4;
    int i;
    int j;
    mpLib_804D64C0_t* cur_i;
    mpLib_804D64C0_t* cur_j;

    for (i = 0; i < temp_r29->x28 - 1; i++) {
        for (j = i + 1; j < temp_r29->x28; j++) {
            cur_i = &mpLib_804D64C0[i];
            cur_j = &mpLib_804D64C0[j];
            if ((cur_i->flags & 0x10000) && !(cur_i->flags & 0x40000) &&
                (cur_j->flags & 0x10000) && !(cur_j->flags & 0x40000))
            {
                mpLib_800581DC(i, j);
            }
        }
    }
}

/// #mpLib_80058614

/// #fn_800587FC

static struct {
    float unk0;
    float unk4;
    float unk8;
    float unkC;
} mpLib_80458868[2];

void mpLib_80058820(void)
{
    HSD_GObj* gobj = GObj_Create(1, 6, 0);
    if (gobj == NULL) {
        __assert(__FILE__, 0x18AA, "gobj");
    }
    HSD_GObjProc_8038FD54(gobj, fn_800587FC, 4);
    mpLib_80458868[0].unkC = +10000.0F;
    mpLib_80458868[0].unk0 = +10000.0F;
    mpLib_80458868[0].unk8 = -10000.0F;
    mpLib_80458868[0].unk4 = -10000.0F;
    mpLib_80458868[1] = mpLib_80458868[0];
}

bool mpLib_800588C8(void)
{
    return mpLib_804D64B0;
}

void mpLib_800588D0(f32 left, f32 bottom, f32 right, f32 top)
{
    mpLib_804D64C0_t* curr = mpLib_804D64C4;

    while (curr != NULL) {
        s32 flags = curr->flags;

        if ((flags & 0x10000) && !(flags & 0x40000)) {
            if (flags & 0x400) {
                curr->flags = flags & 0xFFFFEFFF;
            } else if ((left > curr->x18) || (right < curr->x10) ||
                       (bottom > curr->x1C) || (top < curr->x14))
            {
                curr->flags |= 0x1000;
            } else {
                curr->flags = flags & 0xFFFFEFFF;
            }
        } else {
            curr->flags |= 0x1000;
        }

        curr = curr->next;
    }

    mpLib_804D64B0 = true;
}

void mpLib_80058970(float x1, float y1, float x2, float y2)
{
    float right;
    float left;
    float bottom;
    float top;

    if (x1 > x2) {
        left = x2;
        right = x1;
    } else {
        right = x2;
        left = x1;
    }
    if (y1 > y2) {
        bottom = y2;
        top = y1;
    } else {
        top = y2;
        bottom = y1;
    }
    mpLib_800588D0(left, bottom, right, top);
}

void mpLib_800589D0(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5,
                    f32 arg6, f32 arg7)
{
    f32 right;
    f32 left;
    f32 bottom;
    f32 top;

    left = arg2;
    bottom = arg3;
    if (arg0 > left) {
        right = arg0;
    } else {
        right = left;
        left = arg0;
    }
    if (arg1 > bottom) {
        top = arg1;
    } else {
        top = bottom;
        bottom = arg1;
    }
    if (right < arg4) {
        right = arg4;
    } else if (left > arg4) {
        left = arg4;
    }
    if (top < arg5) {
        top = arg5;
    } else if (bottom > arg5) {
        bottom = arg5;
    }
    if (right < arg6) {
        right = arg6;
    } else if (left > arg6) {
        left = arg6;
    }
    if (top < arg7) {
        top = arg7;
    } else if (bottom > arg7) {
        bottom = arg7;
    }
    mpLib_800588D0(left, bottom, right, top);
}

void mpLib_80058AA0(void)
{
    mpLib_804D64C0_t* curr = mpLib_804D64C4;

    while (curr != NULL) {
        curr->flags &= 0xFFFFEFFF;
        curr = curr->next;
    }

    mpLib_804D64B0 = false;
}

static HSD_Chan mpLib_803BF540 = {
    NULL,
    GX_COLOR0A0,
    0,
    { 0, 0, 0, 0 },
    { 0xFF, 0xA0, 0x30, 0xFF },
    0,
    GX_SRC_REG,
    GX_SRC_REG,
    GX_LIGHT_NULL,
    GX_DF_CLAMP,
    GX_AF_NONE,
    NULL,
};

void mpLib_80058ACC(GXColor color)
{
    HSD_TevDesc spC;
    HSD_StateInitTev();
    spC.flags = 0;
    spC.stage = HSD_StateAssignTev();
    spC.coord = 0xFF;
    spC.map = 0xFF;
    spC.color = 4;
    spC.u.tevop.tevmode = 4;
    HSD_SetupTevStage(&spC);
    HSD_SetupPEMode(1, NULL);
    HSD_SetTevRegAll();
    HSD_StateSetNumTevStages();
    HSD_StateSetNumTexGens();
    HSD_StateSetNumChans(1);
    mpLib_803BF540.mat_color = color;
    HSD_SetupChannel(&mpLib_803BF540);
}

/// #mpLib_80058B5C

/// #mpLib_800590F4

void mpLib_80059404(int arg0, int arg1, GXColor arg2)
{
    f32 temp_f1;
    f32 temp_f3;
    f32 temp_f4;
    f32 temp_f5;

    mpLib_Line* var_r31;
    int var_r28;
    int temp_r27;

    mpLib_Line* var_r6;
    int i;

    var_r28 = 0;
    temp_r27 = mpLib_804D64B4->xC;
    var_r6 = mpLib_Lines;
    for (i = 0; i < temp_r27; i++) {
        if ((var_r6->flags & 0x10000) && !(var_r6->flags & 0x40000) &&
            arg0 == (var_r6->x0->xE & arg1))
        {
            var_r28 += 1;
        }
        var_r6 += 1;
    }
    if (var_r28 != 0) {
        var_r31 = mpLib_Lines;
        mpLib_80058ACC(arg2);
        GXBegin(GX_QUADS, GX_VTXFMT0, var_r28 * 4);
        for (i = 0; i < temp_r27; i++) {
            if ((var_r31->flags & 0x10000) && !(var_r31->flags & 0x40000)) {
                if (arg0 == (var_r31->x0->xE & arg1)) {
                    u8 _[0x18];
                    temp_f4 = mpLib_Points[var_r31->x0->p0_idx].pos.y;
                    temp_f3 = mpLib_Points[var_r31->x0->p0_idx].pos.x;

                    GXWGFifo.f32 = temp_f3;
                    GXWGFifo.f32 = temp_f4;
                    GXWGFifo.f32 = 25.0f;

                    temp_f5 = mpLib_Points[var_r31->x0->p1_idx].pos.y;
                    temp_f1 = mpLib_Points[var_r31->x0->p1_idx].pos.x;

                    GXWGFifo.f32 = temp_f1;
                    GXWGFifo.f32 = temp_f5;
                    GXWGFifo.f32 = 25.0f;

                    GXWGFifo.f32 = temp_f1;
                    GXWGFifo.f32 = temp_f5;
                    GXWGFifo.f32 = -25.0f;

                    GXWGFifo.f32 = temp_f3;
                    GXWGFifo.f32 = temp_f4;
                    GXWGFifo.f32 = -25.0f;
                }
            }
            var_r31 += 1;
        }
        GXEnd();
    }
}

/// #mpLib_80059554

/// #mpLib_80059E60

/// #mpLib_80059FE0

/// #mpLib_8005A220

void mpLib_8005A2DC(void)
{
    f32 temp_f1;

    mpLib_800590F4();
    temp_f1 = mpLib_80059E60();
    if (mpLib_804D64D0 == 0) {
        mpLib_804D64D0 = 1;
        OSReport("map coll under=%d upper=%d left=%d right=%d bbox=%d\n",
                 mpLib_804D64D4, mpLib_804D64D8, mpLib_804D64DC,
                 mpLib_804D64E0, mpLib_804D64E4);
    }
    HSD_StateInvalidate(-1);
}

static const GXColor mpLib_804D8140 = { 0xFF, 0xFF, 0xC0, 0xFF };
static const GXColor mpLib_804D8144 = { 0xFF, 0xFF, 0xFF, 0x80 };
static const GXColor mpLib_804D8148 = { 0x80, 0xC0, 0xC0, 0xFF };
static const GXColor mpLib_804D814C = { 0xC0, 0xFF, 0xFF, 0x80 };
static const GXColor mpLib_804D8150 = { 0x40, 0x40, 0xFF, 0x00 };

void mpLib_8005A340(void)
{
    Mtx sp7C;
    u8 _44[0x7C - 0x44];
    GXColor sp40;
    u8 _38[8];
    GXColor sp34;
    u8 _30[4];
    GXColor sp2C;
    GXColor sp28;
    GXColor sp24;
    GXColor sp20;
    GXColor sp1C;
    CameraBox* var_r30;

    f32 temp_f0;
    f32 temp_f2;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f3;
    f32 temp_f4;

    f32 left;
    f32 right;
    f32 bottom;
    f32 top;

    PAD_STACK(0x14);

    HSD_LObjSetupInit(HSD_CObjGetCurrent());
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
    HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), sp7C);
    GXSetCurrentMtx(0);
    GXLoadPosMtxImm(sp7C, 0);

    left = Stage_GetBlastZoneLeftOffset();
    right = Stage_GetBlastZoneRightOffset();
    bottom = Stage_GetBlastZoneBottomOffset();
    top = Stage_GetBlastZoneTopOffset();

    sp40 = mpLib_804D8144;
    sp2C = mpLib_804D8140;
    mpLib_80058ACC(sp2C);
    GXSetZMode(1, GX_LEQUAL, 0);
    GXSetLineWidth(0x10, GX_TO_ZERO);

    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);

    GXWGFifo.f32 = left;
    GXWGFifo.f32 = bottom;
    GXWGFifo.f32 = 0.0F;

    GXWGFifo.f32 = right;
    GXWGFifo.f32 = bottom;
    GXWGFifo.f32 = 0.0F;

    GXWGFifo.f32 = right;
    GXWGFifo.f32 = top;
    GXWGFifo.f32 = 0.0F;

    GXWGFifo.f32 = left;
    GXWGFifo.f32 = top;
    GXWGFifo.f32 = 0.0F;

    GXWGFifo.f32 = left;
    GXWGFifo.f32 = bottom;
    GXWGFifo.f32 = 0.0F;

    GXEnd();

    sp28 = sp40;
    mpLib_80058ACC(sp28);
    GXSetZMode(1, GX_GREATER, 0);
    GXSetLineWidth(0x10, GX_TO_ZERO);

    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);

    GXWGFifo.f32 = left;
    GXWGFifo.f32 = bottom;
    GXWGFifo.f32 = 0.0F;

    GXWGFifo.f32 = right;
    GXWGFifo.f32 = bottom;
    GXWGFifo.f32 = 0.0F;

    GXWGFifo.f32 = right;
    GXWGFifo.f32 = top;
    GXWGFifo.f32 = 0.0F;

    GXWGFifo.f32 = left;
    GXWGFifo.f32 = top;
    GXWGFifo.f32 = 0.0F;

    GXWGFifo.f32 = left;
    GXWGFifo.f32 = bottom;
    GXWGFifo.f32 = 0.0F;

    GXEnd();

    left = Stage_GetCamBoundsLeftOffset();
    right = Stage_GetCamBoundsRightOffset();
    bottom = Stage_GetCamBoundsBottomOffset();
    top = Stage_GetCamBoundsTopOffset();

    sp34 = mpLib_804D814C;
    sp24 = mpLib_804D8148;
    mpLib_80058ACC(sp24);

    GXSetZMode(1, GX_LEQUAL, 0);
    GXSetLineWidth(0x10, GX_TO_ZERO);
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);

    sp20 = sp34;

    GXWGFifo.f32 = left;
    GXWGFifo.f32 = bottom;
    GXWGFifo.f32 = 0.0F;

    GXWGFifo.f32 = right;
    GXWGFifo.f32 = bottom;
    GXWGFifo.f32 = 0.0F;

    GXWGFifo.f32 = right;
    GXWGFifo.f32 = top;
    GXWGFifo.f32 = 0.0F;

    GXWGFifo.f32 = left;
    GXWGFifo.f32 = top;
    GXWGFifo.f32 = 0.0F;

    GXWGFifo.f32 = left;
    GXWGFifo.f32 = bottom;
    GXWGFifo.f32 = 0.0F;

    GXEnd();

    mpLib_80058ACC(sp20);

    GXSetZMode(1, GX_GREATER, 0);
    GXSetLineWidth(0x10, GX_TO_ZERO);
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);

    sp1C = mpLib_804D8150;

    GXWGFifo.f32 = left;
    GXWGFifo.f32 = bottom;
    GXWGFifo.f32 = 0.0F;

    GXWGFifo.f32 = right;
    GXWGFifo.f32 = bottom;
    GXWGFifo.f32 = 0.0F;

    GXWGFifo.f32 = right;
    GXWGFifo.f32 = top;
    GXWGFifo.f32 = 0.0F;

    GXWGFifo.f32 = left;
    GXWGFifo.f32 = top;
    GXWGFifo.f32 = 0.0F;

    GXWGFifo.f32 = left;
    GXWGFifo.f32 = bottom;
    GXWGFifo.f32 = 0.0F;

    GXEnd();

    mpLib_80058ACC(sp1C);

    GXSetZMode(0, GX_LEQUAL, 0);
    GXSetLineWidth(0x10, GX_TO_ZERO);

    var_r30 = cm_804D6468;
    while (var_r30 != NULL) {
        if (Camera_8002928C(var_r30)) {
            GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);

            temp_f1 = var_r30->x10.x;
            temp_f4 = var_r30->x10.y;
            temp_f3 = var_r30->x34.x;
            temp_f0 = var_r30->x2C.x;

            temp_f2 = temp_f1 + temp_f0;
            temp_f3 = temp_f4 + temp_f3;

            GXWGFifo.f32 = temp_f2;
            GXWGFifo.f32 = temp_f3;
            GXWGFifo.f32 = 0.0F;

            temp_f1_2 = temp_f1 + var_r30->x2C.y;
            GXWGFifo.f32 = temp_f1_2;
            GXWGFifo.f32 = temp_f3;
            GXWGFifo.f32 = 0.0F;

            temp_f0 = temp_f4 + var_r30->x34.y;
            GXWGFifo.f32 = temp_f1_2;
            GXWGFifo.f32 = temp_f0;
            GXWGFifo.f32 = 0.0F;

            GXWGFifo.f32 = temp_f2;
            GXWGFifo.f32 = temp_f0;
            GXWGFifo.f32 = 0.0F;

            GXWGFifo.f32 = temp_f2;
            GXWGFifo.f32 = temp_f3;
            GXWGFifo.f32 = 0.0F;

            GXEnd();
        }
        var_r30 = var_r30->prev;
    }
    HSD_StateInvalidate(-1);
}
