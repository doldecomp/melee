#include <placeholder.h>

#include "ftCommon/forward.h"

#include "ftCo_0B3E.h"

#include "ft/types.h"
#include "ftCommon/ftCo_0A01.h"

#include <baselib/debug.h>

double const ftCo_804D89C8 = 0;
double const ftCo_804D89D0 = S32_TO_F32;
float const ftCo_804D89D8 = 0;
double const ftCo_804D89E0 = 0.5;
double const ftCo_804D89E8 = 0;
float const ftCo_804D89F0 = +1e-5;
float const ftCo_804D89F4 = -1e-5;
float const ftCo_804D89F8 = 1000;
double const ftCo_804D8A00 = 3;
double const ftCo_804D8A08 = 1;
double const ftCo_804D8A10 = S32_TO_F32;
float const ftCo_804D8A18 = 40;
float const ftCo_804D8A1C = 35;
float const ftCo_804D8A20 = 30;
float const ftCo_804D8A24 = 25;
float const ftCo_804D8A28 = 20;
float const ftCo_804D8A2C = 15;
float const ftCo_804D8A30 = 10;
float const ftCo_804D8A34 = 5;
float const ftCo_804D8A38 = 0.05;
float const ftCo_804D8A3C = -10;
double const ftCo_804D8A40 = 10;
float const ftCo_804D8A48 = 100;
float const ftCo_804D8A4C = 0.5;
double const ftCo_804D8A50 = 30;
double const ftCo_804D8A58 = 0.25;
double const ftCo_804D8A60 = 0.75;
double const ftCo_804D8A68 = 5;
double const ftCo_804D8A70 = 1000;
float const ftCo_804D8A78 = 1.3089969158172607;
float const ftCo_804D8A7C = 4;
double const ftCo_804D8A80 = 0.7853981573134661;
double const ftCo_804D8A88 = 0.1;
double const ftCo_804D8A90 = 40;
double const ftCo_804D8A98 = -0.08726646192371845;
double const ftCo_804D8AA0 = +0.08726646192371845;
float const ftCo_804D8AA8 = 22;
float const ftCo_804D8AAC = 62;
float const ftCo_804D8AB0 = 102;
float const ftCo_804D8AB4 = 58;
float const ftCo_804D8AB8 = 57;
float const ftCo_804D8ABC = 27;
float const ftCo_804D8AC0 = 53;
float const ftCo_804D8AC4 = 16;
float const ftCo_804D8AC8 = 60;
float const ftCo_804D8ACC = 32;
float const ftCo_804D8AD0 = -25;
double const ftCo_804D8AD8 = +25;
float const ftCo_804D8AE0 = -100;
double const ftCo_804D8AE8 = 15;
double const ftCo_804D8AF0 = -0.6981316953897476;
double const ftCo_804D8AF8 = -0.8726646192371845;
double const ftCo_804D8B00 = 53;
double const ftCo_804D8B08 = 1.0471975430846214;
double const ftCo_804D8B10 = 80;
double const ftCo_804D8B18 = +1.3089969288557768;
double const ftCo_804D8B20 = -0.7853981573134661;
double const ftCo_804D8B28 = 60;
double const ftCo_804D8B30 = -1.3089969288557768;
double const ftCo_804D8B38 = 0.26179938577115536;
double const ftCo_804D8B40 = -0.26179938577115536;
float const ftCo_804D8B48 = 1;
double const ftCo_804D8B50 = 2;
float const ftCo_804D8B58 = 3;

char ftCo_803C5DB0[] = "csP is bad address\n";
char ftCo_803C5DC4[] = "ftcmdscript.c";

#pragma push
#pragma force_active on
/// @todo Is this <tt>\0\0\0\0</tt> a split?
///       Shouldn't be possible given #ftCo_804D89D8...
char ftCo_803C60E0[] = "command script buffer over flow!\n\0\0\0\0";
char ftCo_803C6108[] = "ftcpuattack.c";
#pragma pop

// .sdata
extern char* ftCo_804D3B68;
extern char* ftCo_804D3B70;
extern char* ftCo_804D3B74;
extern char* ftCo_804D3B7C;

#pragma force_active on

/// #ftCo_800B3E04

void ftCo_800B462C(ftCo_Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    data->x554.x0_p = &data->x454;
}

/// #ftCo_800B463C

void ftCo_800B463C(ftCo_Fighter* fp, int arg1)
{
    struct Fighter_x1A88_t* temp_r31 = (struct Fighter_x1A88_t*) &fp->x1A88;
    if (fp->x1A88.x554.x0_u32 >= temp_r31->x554.x0_u32) {
        OSReport("command script buffer over flow!\n");
        __assert("ftcmdscript.c", 501, "0");
    }

    {
        union Fighter_x1A88_x544_t* temp = &temp_r31->x554;
        temp->x0_u32 = arg1;
        ++temp->x0_u32;
    }
}

/// #ftCo_800B46B8

/// #ftCo_800B4778

/// #ftCo_800B4880

/// #ftCo_800B49F4

void ftCo_800B4A78(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    data->x0 = 0;
    data->x4 = 0;
    data->x5 = 0;
    data->x6 = 0;
    data->x7 = 0;
    data->x9 = 0;
    data->x8 = 0;
    data->x450 = 0;
    data->x44C = 0;
    data->x554.x0_p = &data->x454;
}

/// #ftCo_800B4AB0

/// #ftCo_800B52AC

/// #ftCo_800B5AB0

/// #ftCo_800B6208

/// #ftCo_800B630C

/// #ftCo_800B63D8

/// #ftCo_800B658C

/// #ftCo_800B683C

/// #ftCo_800B7180

/// #ftCo_800B732C

/// #ftCo_800B7638

/// #ftCo_800B77E8

/// #ftCo_800B885C

/// #ftCo_800B89CC

/// #ftCo_800B8A9C

/// #ftCo_800B9020

/// #ftCo_800B920C

void ftCo_800B92D4(ftCo_Fighter* fp)
{
    PAD_STACK(4 * 4);
    if (fp->x1A88.x44 == NULL) {
        fp->x1A88.x44 = NULL;
        fp->x1A88.x18 = fp->x1A88.x1C;
        ftCo_800A0C8C(fp);
    } else {
        ftCo_800B46B8(fp, 0x94, 0x7F);
        ftCo_800B463C(fp, 0x7F);
    }
}

/// #ftCo_800B9340

/// #ftCo_800B9504

/// #ftCo_800B9704

/// #ftCo_800B9790

/// #ftCo_800B98C8

/// #ftCo_800B9A04

/// #ftCo_800B9CBC

bool ftCo_800B9F6C(Fighter* fp)
{
    if (fp->motion_id == ftCo_MS_GuardOn || fp->motion_id == ftCo_MS_Guard) {
        return true;
    }
    return false;
}

/// #ftCo_800B9F90

/// #ftCo_800BA080

/// #ftCo_800BA160

/// #ftCo_800BA224

/// #ftCo_800BA2E8

/// #ftCo_800BA674

/// #ftCo_800BA9A0

/// #ftCo_800BB104

/// #ftCo_800BB220

/// #ftCo_800BB768

/// #ftCo_800BB9B4
