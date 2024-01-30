#include <platform.h>

#include "ft/ftdrawcommon.h"

#include "ft/ftlib.h"

#include <placeholder.h>
#include <dolphin/mtx.h>
#include <dolphin/mtx/types.h>
#include <baselib/cobj.h>

static char ftDrawCommon_803C0EB0[] = "translate";
static s32 ftDrawCommon_804D3A88 = -128;
static s32 ftDrawCommon_804D3A8C = 0x8080FF80;
static s32 ftDrawCommon_804D3A90 = 0x80808080;
static char ftDrawCommon_804D3A94[] = "jobj.h";
static char ftDrawCommon_804D3A9C[] = "jobj";

extern float ftDrawCommon_804D8368;
extern s32 ftDrawCommon_804D836C[1];
extern s32 ftDrawCommon_804D8370[2];

extern void ftParts_800750C8(void);
extern void ftCo_800C8AF0(void);
extern void ftCo_8009F5AC(void);
extern void Camera_800310B8(void);
extern void Camera_80031060(void);
extern void ftCo_800C2600(void);
extern void lbGx_8001E2F8(void);
extern void lb_80014770(void);
extern void ftCo_800B395C(void);
extern void lb_800117F4(void);

static inline void mtx_thing(MtxPtr mtx, Vec3* ptr, float val, float val2)
{
    mtx[0][3] = ptr->x + val;
    mtx[1][3] = ptr->y + val;
    mtx[2][3] = ptr->z + val2;
}

MtxPtr ftDrawCommon_8008051C(HSD_GObj* arg1, MtxPtr arg2)
{
    u8 unused0[0x4];

    Vec3 sp54;

    u8 unused1[0xC];

    Mtx sp18;

    u8 unused2[0x8];

    float temp_f31;
    float temp_f0;

    MtxPtr temp_r31;

    temp_f31 = temp_f0 = 0.0F;
    sp54.z = temp_f31;
    sp54.y = temp_f31;
    sp54.x = temp_f31;

    if (ftLib_80087074(arg1, &sp54)) {
        temp_r31 = HSD_CObjGetCurrent()->view_mtx;
        PSMTXIdentity(sp18);

        mtx_thing(sp18, &sp54, temp_f31, temp_f0);

        PSMTXConcat(temp_r31, sp18, arg2);
        return arg2;
    }
    return NULL;
}

void ftDrawCommon_80080E18(HSD_GObj* arg0, int arg1)
{
    NOT_IMPLEMENTED;
}

void ftDrawCommon_80081118(void)
{
    NOT_IMPLEMENTED;
}

void ftDrawCommon_80081140(void)
{
    NOT_IMPLEMENTED;
}

void ftDrawCommon_80081168(void)
{
    NOT_IMPLEMENTED;
}

void ftDrawCommon_80081200(void)
{
    NOT_IMPLEMENTED;
}
