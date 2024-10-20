#include "mp/forward.h"

#include "mplib.h"

#include "mp/types.h"

#include <dolphin/mtx/types.h>
#include <baselib/tev.h>
#include <baselib/texp.h>

/* 4D64B0 */ static int mpLib_804D64B0;
/* 4D64B4 */ static int mpLib_804D64B4;
/* 4D64B8 */ static int mpLib_804D64B8;
/* 4D64BC */ static mp_UnkStruct2* mpLib_804D64BC;
/* 4D64C0 */ static int mpLib_804D64C0;
/* 4D64C4 */ static mp_UnkStruct7* mpLib_804D64C4;
/* 4D64C8 */ static s32 mpLib_804D64C8;
/* 4D64CC */ static s32 mpLib_804D64CC;
/* 4D64D0 */ static s32 mpLib_804D64D0;
/* 4D64D4 */ static s32 mpLib_804D64D4;
/* 4D64D8 */ static s32 mpLib_804D64D8;
/* 4D64DC */ static s32 mpLib_804D64DC;
/* 4D64E0 */ static s32 mpLib_804D64E0;
/* 4D64E4 */ static s32 mpLib_804D64E4;

int mpLib_8004D164(void)
{
    return mpLib_804D64B4;
}

int mpLib_8004D16C(void)
{
    return mpLib_804D64B8;
}

mp_UnkStruct2* mpLib_8004D174(void)
{
    return mpLib_804D64BC;
}

int mpLib_8004D17C(void)
{
    return mpLib_804D64C0;
}

/// #mpLib_8004D184

/// #mpLib_8004D288

/// #mpLib_8004DB78

/// #mpLib_8004DC04

/// #mpLib_8004DC90

/// #mpLib_8004DD90

/// #mpLib_8004E090

/// #mpLib_8004E398

/// #mpLib_8004E684

bool mpLib_8004E97C(double arg0, double arg1, double arg2, double arg3,
                    double arg4, double arg5, double arg6, double arg7,
                    float* arg8, float* arg9)

{
    bool b0 = false;
    bool b1 = false;

    if (arg2 <= arg0) {
        if (((arg4 < arg2) && (arg6 < arg2)) ||
            ((arg0 < arg4 && (arg0 < arg6))))
        {
            return false;
        }
    } else if (((arg4 < arg0) && (arg6 < arg0)) ||
               ((arg2 < arg4 && (arg2 < arg6))))
    {
        return false;
    }
    if (arg3 < arg1) {
        if (((arg5 < arg3) && (arg7 < arg3)) ||
            ((arg1 < arg5 && (arg1 < arg7))))
        {
            return false;
        }
    } else if (((arg5 < arg1) && (arg7 < arg1)) ||
               ((arg3 < arg5 && (arg3 < arg7))))
    {
        return false;
    }
    {
        double n6 = arg3 - arg1;
        double n5 = arg4 - arg0;
        double n8 = arg2 - arg0;
        double n7 = arg5 - arg1;
        double n9 = n8 * n7 - n6 * n5;
        if (n9 < 0) {
            if (n9 < -0.1) {
                return false;
            }
            b0 = true;
        }
        {
            double n4 = n8 * (arg7 - arg3) - n6 * (arg6 - arg2);
            if (0 < n4) {
                if (0.1 < n4) {
                    return false;
                }
                b1 = true;
            }
            if ((0 != n9) || (0 != n4)) {
                double n2 = n5 * (arg7 - arg3) - n7 * (arg6 - arg2);
                if (n9 <= n2) {
                    if ((n9 < n2) && (n4 < n2)) {
                        return false;
                    }
                } else if (n2 < n4) {
                    return false;
                }
                n2 = (arg6 - arg4);
                n4 = (arg7 - arg5);
                if ((((0 != n2) || (0 != n4)) && ((!b0 || (!b1)))) &&
                    ((n9 < 0 || (!b1))))
                {
                    double n3 = n2 * n6 - n4 * n8;
                    n9 = n3;
                    if (n3 < 0) {
                        n9 = -n3;
                    }
                    if (1e-4 < n9) {
                        n3 = (n2 * n7 - n4 * n5) / n3;
                        if (n3 <= 0) {
                            *arg8 = arg0;
                            *arg9 = arg1;
                        } else if (1 <= n3) {
                            *arg8 = arg2;
                            *arg9 = arg3;
                        } else {
                            *arg8 = (n8 * n3 + arg0);
                            *arg9 = (n6 * n3 + arg1);
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/// #mpLib_8004EBF8

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

/// #mpLib_80051BA8

/// #mpLib_80051EC8

/// #mpLib_800524DC

/// #mpLib_80052508

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

/// #mpLib_8005389C

/// #mpLib_80053950

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

/// #mpLib_80054B14

/// #mpLib_80054BC0

/// #mpLib_80054C6C

/// #mpLib_80054CEC

/// #mpLib_80054D68

/// #mpLib_80054DFC

bool mpLib_80054ED8(int line)
{
    if (line == -1) {
        return false;
    }
    if (line < 0 || line >= mpLib_804D64BC[0].x0->x0) {
        OSReport("%s:%d:not found lineID=%d\n", __FILE__, 4636);
        while (true) {
            continue;
        };
    }
    if (!(mpLib_804D64BC[line].x4 & 0x10000) ||
        (mpLib_804D64BC[line].x4 & 0x40000))
    {
        return false;
    }
    return true;
}

/// #mpLib_80054F68

/// #mpLib_800552B0

/// #mpLib_8005541C

/// #mpLib_800557D0

/// #mpLib_80055C5C

/// #mpLib_80055E24

/// #mpLib_80055E9C

/// #mpLib_800565DC

/// #mpLib_8005667C

/// #mpLib_800566D8

/// #mpLib_800566F8

/// #mpLib_80056710

/// #mpLib_80056758

/// #mpLib_800567C0

/// #mpLib_800569EC

/// #mpLib_80056A1C

/// #mpLib_80056A54

/// #mpLib_80056A8C

/// #mpLib_80056AC4

/// #mpLib_80056AFC

/// #mpLib_80056B34

/// #mpLib_80056B6C

/// #mpLib_80056C54

/// #mpLib_80057424

/// #mpLib_80057528

/// #mpLib_800575B0

/// #mpLib_80057638

/// #mpLib_80057B4C

/// #mpLib_80057BC0

/// #mpLib_80057FDC

/// #mpLib_80058044

/// #mpLib_800580AC

/// #mpLib_800580C8

/// #mpLib_800580E0

/// #mpLib_800580FC

/// #mpLib_8005811C

/// #mpLib_800581A4

/// #mpLib_800581BC

/// #mpLib_800581DC

/// #mpLib_80058560

/// #mpLib_80058614

/// #fn_800587FC

/// #mpLib_80058820

int mpLib_800588C8(void)
{
    return mpLib_804D64B0;
}

void mpLib_800588D0(f32 left, f32 bottom, f32 right, f32 top)
{
    mp_UnkStruct7* curr = mpLib_804D64C4;

    while (curr != NULL) {
        s32 flags = curr->x8;

        if ((flags & 0x10000) && !(flags & 0x40000)) {
            if (flags & 0x400) {
                curr->x8 = flags & 0xFFFFEFFF;
            } else if ((left > curr->x18) || (right < curr->x10) ||
                       (bottom > curr->x1C) || (top < curr->x14))
            {
                curr->x8 |= 0x1000;
            } else {
                curr->x8 = flags & 0xFFFFEFFF;
            }
        } else {
            curr->x8 |= 0x1000;
        }

        curr = curr->next;
    }

    mpLib_804D64B0 = 1;
}

void mpLib_80058970(f32 arg8, f32 arg9, f32 argA, f32 argB)
{
    f32 right;
    f32 left;
    f32 bottom;
    f32 var_f5;

    left = argA;
    bottom = argB;
    if (arg8 > left) {
        right = arg8;
    } else {
        right = left;
        left = arg8;
    }
    if (arg9 > bottom) {
        var_f5 = arg9;
    } else {
        var_f5 = bottom;
        bottom = arg9;
    }
    mpLib_800588D0(left, bottom, right, var_f5);
}

void mpLib_800589D0(f32 arg8, f32 arg9, f32 argA, f32 argB, f32 argC, f32 argD,
                    f32 argE, f32 argF)
{
    f32 right;
    f32 left;
    f32 bottom;
    f32 top;

    left = argA;
    bottom = argB;
    if (arg8 > left) {
        right = arg8;
    } else {
        right = left;
        left = arg8;
    }
    if (arg9 > bottom) {
        top = arg9;
    } else {
        top = bottom;
        bottom = arg9;
    }
    if (right < argC) {
        right = argC;
    } else if (left > argC) {
        left = argC;
    }
    if (top < argD) {
        top = argD;
    } else if (bottom > argD) {
        bottom = argD;
    }
    if (right < argE) {
        right = argE;
    } else if (left > argE) {
        left = argE;
    }
    if (top < argF) {
        top = argF;
    } else if (bottom > argF) {
        bottom = argF;
    }
    mpLib_800588D0(left, bottom, right, top);
}

void mpLib_80058AA0(void)
{
    mp_UnkStruct7* curr = mpLib_804D64C4;

    while (curr != NULL) {
        curr->x8 = curr->x8 & 0xFFFFEFFF;
        curr = curr->next;
    }

    mpLib_804D64B0 = 0;
}

/// #mpLib_80058ACC

/// #mpLib_80058B5C

/// #mpLib_800590F4

/// #mpLib_80059404

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
        //                                           sic
        OSReport("]ap coll unddr=%d upper=$d left=%d rhght=%d bbox-%d",
                 mpLib_804D64D4, mpLib_804D64D8, mpLib_804D64DC,
                 mpLib_804D64E0, mpLib_804D64E4);
    }
    HSD_StateInvalidate(-1);
}

/// #mpLib_8005A340
