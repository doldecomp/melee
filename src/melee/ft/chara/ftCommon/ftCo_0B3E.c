#include "ftCo_0B3E.h"

#include <melee/ft/types.h>
#include <melee/ft/chara/ftCommon/ftCo_0A01.h>
#include <melee/lb/lb_00CE.h>
#include <sysdolphin/baselib/debug.h>
#include <math.h>

typedef enum CPUCommand {
    CpuCmd_PressA = 1,
    CpuCmd_ReleaseA,
    CpuCmd_PressB,
    CpuCmd_ReleaseB,
    CpuCmd_PressX,
    CpuCmd_ReleaseX,
    CpuCmd_PressY,
    CpuCmd_ReleaseY,
    CpuCmd_PressR,
    CpuCmd_ReleaseR,
    CpuCmd_PressL,
    CpuCmd_ReleaseL,
    CpuCmd_PressZ,
    CpuCmd_ReleaseZ,
    CpuCmd_PressUp,
    CpuCmd_ReleaseUp,
    CpuCmd_PressDown,
    CpuCmd_ReleaseDown,
    CpuCmd_PressRight,
    CpuCmd_ReleaseRight,
    CpuCmd_PressLeft,
    CpuCmd_ReleaseLeft,
    CpuCmd_PressStart = 0x17,
    CpuCmd_ReleaseStart,
    CpuCmd_ReleaseAll,
} CPUCommand;

void ftCo_800B3E04(Fighter* fp)
{
    struct Fighter_x1A88_t* data;
    s8* cur;
    int temp_r27;
    int magnitude;
    int temp_r27_3;
    int temp_r25;

    Fighter* target;
    f32 angle;
    int clamp_x;
    int clamp_y;
    int var_r24;
    int var_r24_2;
    int var_r3_2;

    data = &fp->x1A88;
    if (data->csP == NULL) {
        return;
    }
    if (data->x44C == 0) {
        return;
    }
    data->x44C--;
    if (data->x44C != 0) {
        return;
    }
    cur = data->csP;
    if (data->csP < data->x454) {
        OSReport("csP is bad address\n");
        __assert("ftcmdscript.c", 0x21, "0");
    }
    if (data->csP >= data->x454 + sizeof(data->x454)) {
        OSReport("csP is bad address\n");
        __assert("ftcmdscript.c", 0x24, "0");
    }
    while (data->x44C == 0) {
        switch ((u8) *cur++) {
        case CpuCmd_PressA:
            data->x0 |= HSD_PAD_A;
            break;
        case CpuCmd_ReleaseA:
            data->x0 &= ~HSD_PAD_A;
            break;
        case CpuCmd_PressB:
            data->x0 |= HSD_PAD_B;
            break;
        case CpuCmd_ReleaseB:
            data->x0 &= ~HSD_PAD_B;
            break;
        case CpuCmd_PressX:
            data->x0 |= HSD_PAD_X;
            break;
        case CpuCmd_ReleaseX:
            data->x0 &= ~HSD_PAD_X;
            break;
        case CpuCmd_PressY:
            data->x0 |= HSD_PAD_Y;
            break;
        case CpuCmd_ReleaseY:
            data->x0 &= ~HSD_PAD_Y;
            break;
        case CpuCmd_PressStart:
            data->x0 |= HSD_PAD_START;
            break;
        case CpuCmd_ReleaseStart:
            data->x0 &= ~HSD_PAD_START;
            break;
        case CpuCmd_PressR:
            data->rtrigger = 0xFF;
            data->x0 |= HSD_PAD_R;
            break;
        case CpuCmd_ReleaseR:
            data->rtrigger = 0;
            data->x0 &= ~HSD_PAD_R;
            break;
        case CpuCmd_PressL:
            data->x0 |= HSD_PAD_L;
            break;
        case CpuCmd_ReleaseL:
            data->x0 &= ~HSD_PAD_L;
            break;
        case CpuCmd_PressZ:
            data->x0 |= HSD_PAD_Z;
            break;
        case CpuCmd_ReleaseZ:
            data->x0 &= ~HSD_PAD_Z;
            break;
        case CpuCmd_PressUp:
            data->x0 |= HSD_PAD_DPADUP;
            break;
        case CpuCmd_ReleaseUp:
            data->x0 &= ~HSD_PAD_DPADUP;
            break;
        case CpuCmd_PressDown:
            data->x0 |= HSD_PAD_DPADDOWN;
            break;
        case CpuCmd_ReleaseDown:
            data->x0 &= ~HSD_PAD_DPADDOWN;
            break;
        case CpuCmd_PressRight:
            data->x0 |= HSD_PAD_DPADRIGHT;
            break;
        case CpuCmd_ReleaseRight:
            data->x0 &= ~HSD_PAD_DPADRIGHT;
            break;
        case CpuCmd_PressLeft:
            data->x0 |= HSD_PAD_DPADLEFT;
            break;
        case CpuCmd_ReleaseLeft:
            data->x0 &= ~HSD_PAD_DPADLEFT;
            break;
        case 0x86:
            data->x0 |= HSD_PAD_A;
            data->x44C = (u8) *cur++;
            break;
        case 0x87:
            data->x0 &= ~HSD_PAD_A;
            data->x44C = (u8) *cur++;
            break;
        case 0x88:
            data->x0 |= HSD_PAD_B;
            data->x44C = (u8) *cur++;
            break;
        case 0x89:
            data->x0 &= ~HSD_PAD_B;
            data->x44C = (u8) *cur++;
            break;
        case 0x8A:
            data->x0 |= HSD_PAD_X;
            data->x44C = (u8) *cur++;
            break;
        case 0x8B:
            data->x0 &= ~HSD_PAD_X;
            data->x44C = (u8) *cur++;
            break;
        case 0x8C:
            data->x0 |= HSD_PAD_Y;
            data->x44C = (u8) *cur++;
            break;
        case 0x8D:
            data->x0 &= ~HSD_PAD_Y;
            data->x44C = (u8) *cur++;
            break;
        case 0x80:
            data->lstickX = *cur++;
            break;
        case 0x81:
            data->lstickY = *cur++;
            break;
        case 0x82:
            data->x6 = *cur++;
            break;
        case 0x83:
            data->x7 = *cur++;
            break;
        case 0x84:
            data->rtrigger = *cur++;
            break;
        case 0x85:
            data->x8 = *cur++;
            break;
        case CpuCmd_ReleaseAll:
            data->x0 = 0;
            break;
        case 0x8E:
            data->x44C = (u8) *cur++;
            break;
        case 0x8F:
            magnitude = *cur;
            cur++;
            angle = lb_8000D008(data->x54.y - fp->cur_pos.y, data->x54.x - fp->cur_pos.x);
            data->lstickX = magnitude * cosf(angle);
            data->lstickY = magnitude * sinf(angle);
            break;
        case 0x90:
            if (data->x54.x > fp->cur_pos.x) {
                data->lstickX = *cur;
            } else {
                data->lstickX = -*cur;
            }
            cur++;
            break;
        case 0x94:
            magnitude = *cur;
            cur++;
            target = data->x44;
            if (target != NULL) {
                angle = lb_8000D008(target->cur_pos.y - fp->cur_pos.y, target->cur_pos.x - fp->cur_pos.x);
                data->lstickX = magnitude * cosf(angle);
                data->lstickY = magnitude * sinf(angle);
            }
            break;
        case 0x95: {
            Fighter* target = data->x44;
            s8 stick_x = *cur++;
            if (target != NULL) {
                if (target->cur_pos.x < fp->cur_pos.x) {
                    stick_x = -stick_x;
                }
                if (target != NULL) {
                    data->lstickX = stick_x;
                }
            }
            break;
        }
        case 0x91:
            if (fp->facing_dir >= 0.0) {
                data->lstickX = *cur;
            } else {
                data->lstickX = -*cur;
            }
            cur++;
            break;
        case 0x92: {
            u8 motion_id = *cur++;
            if (fp->motion_id == motion_id) {
                data->x44C = 1;
                return;
            }
            break;
        }
        case 0x93:
            data->x18 = (u8) *cur++;
            break;
        case 0xC0: {
            temp_r25 = *cur;
            cur++;
            temp_r27_3 = *cur;
            cur++;
            angle = lb_8000D008(data->x54.y - fp->cur_pos.y, data->x54.x - fp->cur_pos.x);
            var_r24 = data->lstickX + (s8) (temp_r25 * cosf(angle));
            clamp_x = (s8) (temp_r27_3 * cosf(angle));
            if (var_r24 > clamp_x) {
                var_r24 = clamp_x;
            } else if (var_r24 < -clamp_x) {
                var_r24 = -clamp_x;
            }
            data->lstickX = var_r24;
            var_r24_2 = data->lstickY + (s8) (temp_r25 * sinf(angle));
            clamp_y = (s8) (temp_r27_3 * sinf(angle));
            if (var_r24_2 > clamp_y) {
                var_r24_2 = clamp_y;
            }
            if (var_r24_2 < -clamp_y) {
                var_r24_2 = -clamp_y;
            }
            data->lstickY = var_r24_2;
            break;
        }
        case 0xC1: {
            int dx;
            int clamp_x;
            int stick_x;
            dx = *cur;
            cur++;
            clamp_x = *cur;
            cur++;
            if (data->x54.x > fp->cur_pos.x) {
                stick_x = data->lstickX + dx;
            } else {
                stick_x = data->lstickX - dx;
            }
            if (stick_x > clamp_x) {
                stick_x = clamp_x;
            } else if (stick_x < -clamp_x) {
                stick_x = -clamp_x;
            }
            data->lstickX = stick_x;
            break;
        }
        case 0xC2: {
            int dx;
            int clamp_x;
            dx = *cur;
            cur++;
            clamp_x = *cur;
            cur++;
            if (fp->facing_dir > 0.0) {
                var_r3_2 = data->lstickX + dx;
            } else {
                var_r3_2 = data->lstickX - dx;
            }
            if (var_r3_2 > clamp_x) {
                var_r3_2 = clamp_x;
            } else if (var_r3_2 < -clamp_x) {
                var_r3_2 = -clamp_x;
            }
            data->lstickX = var_r3_2;
            break;
        }
        case 0x7F:
            data->x44C = 0;
            data->csP = NULL;
            return;
        }
    }
    data->csP = cur;
}

void ftCo_800B462C(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    data->x554 = data->x454;
}

void ftCo_800B463C(Fighter* fp, u8 arg1)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (data->x554 >= data->x454 + sizeof(data->x454)) {
        OSReport("command script buffer over flow!\n");
        __assert("ftcmdscript.c", 501, "0");
    }
    *data->x554 = arg1;
    data->x554++;
}

void ftCo_800B46B8(Fighter* fp, u8 arg1, u8 arg2)
{
    ftCo_800B463C(fp, arg1);
    ftCo_800B463C(fp, arg2);
}

void ftCo_800B4778(Fighter* fp, u8 arg1, u8 arg2, u8 arg3)
{
    ftCo_800B463C(fp, arg1);
    ftCo_800B463C(fp, arg2);
    ftCo_800B463C(fp, arg3);
}

extern u8*** Fighter_804D64FC;

void ftCo_800B4880(Fighter* fp, int arg1)
{
    u8* var_r29 = (*Fighter_804D64FC)[arg1];
    while (*var_r29 != 0x7F) {
        ftCo_800B463C(fp, *var_r29);
        if (*var_r29 > 0xBF) {
            var_r29++;
            ftCo_800B463C(fp, *var_r29);
        }
        if (*var_r29 > 0x7F) {
            var_r29++;
            ftCo_800B463C(fp, *var_r29);
        }
        var_r29++;
    }
    ftCo_800B463C(fp, *var_r29);
}

static s8 ftCo_804D3B68 = 0x30;

void ftCo_800B49F4(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;

    ftCo_800B463C(fp, 0x7F);

    data->csP = data->x454;
    data->x44C = 1;
}

void ftCo_800B4A78(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    data->x0 = 0;
    data->lstickX = 0;
    data->lstickY = 0;
    data->x6 = 0;
    data->x7 = 0;
    data->rtrigger = 0;
    data->x8 = 0;
    data->csP = NULL;
    data->x44C = 0;
    data->x554 = data->x454;
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

#pragma push
#pragma dont_inline on
void ftCo_800B92D4(Fighter* fp)
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
#pragma pop

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
