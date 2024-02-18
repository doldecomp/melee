#include "mplib.h"

#include <dolphin/mtx/types.h>

static int mpLib_804D64B4;
static IntVec2* mpLib_804D64BC;

int mpLib_8004D164(void)
{
    return mpLib_804D64B4;
}

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

bool mpLib_80054ED8(int line)
{
    if (line == -1) {
        return false;
    }
    if (line < 0 || line >= mpLib_804D64BC[0].x) {
        OSReport("%s:%d:not found lineID=%d\n", __FILE__, 4636);
        while (true) {
            continue;
        };
    }
    if (!(mpLib_804D64BC[line].y & 0x10000) ||
        (mpLib_804D64BC[line].y & 0x40000))
    {
        return false;
    }
    return true;
}
