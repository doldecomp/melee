#include "ftcmdscript.h"

#include <placeholder.h>

#include <math.h>
#include <sysdolphin/baselib/debug.h>
#include <melee/ft/chara/ftCommon/ftCo_0A01.h>
#include <melee/ft/types.h>
#include <melee/ft/fighter.h>
#include <melee/lb/lb_00CE.h>

void ftCo_800B3E04(Fighter* fp)
{
    struct Fighter_x1A88_t* data;
    s8* cur;
    int temp_r27;
    int magnitude;
    int temp_r27_3;
    int temp_r25;

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

    // If the duration is already zero, there's nothing to do.
    if (data->command_duration == 0) {
        return;
    }

    data->command_duration--;

    // If duration hasn't reached zero, the previous command is still running
    if (data->command_duration != 0) {
        return;
    }

    cur = data->csP;
    if (data->csP < data->buffer) {
        HSD_ASSERTREPORT(0x21, 0, "csP is bad address\n");
    }
    if (data->csP >= data->buffer + sizeof(data->buffer)) {
        HSD_ASSERTREPORT(0x24, 0, "csP is bad address\n");
    }
    while (data->command_duration == 0) {
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
        case CpuCmd_PressAFor:
            data->x0 |= HSD_PAD_A;
            data->command_duration = (u8) *cur++;
            break;
        case CpuCmd_ReleaseAFor:
            data->x0 &= ~HSD_PAD_A;
            data->command_duration = (u8) *cur++;
            break;
        case CpuCmd_PressBFor:
            data->x0 |= HSD_PAD_B;
            data->command_duration = (u8) *cur++;
            break;
        case CpuCmd_ReleaseBFor:
            data->x0 &= ~HSD_PAD_B;
            data->command_duration = (u8) *cur++;
            break;
        case CpuCmd_PressXFor:
            data->x0 |= HSD_PAD_X;
            data->command_duration = (u8) *cur++;
            break;
        case CpuCmd_ReleaseXFor:
            data->x0 &= ~HSD_PAD_X;
            data->command_duration = (u8) *cur++;
            break;
        case CpuCmd_PressYFor:
            data->x0 |= HSD_PAD_Y;
            data->command_duration = (u8) *cur++;
            break;
        case CpuCmd_ReleaseYFor:
            data->x0 &= ~HSD_PAD_Y;
            data->command_duration = (u8) *cur++;
            break;
        case CpuCmd_SetLstickX:
            data->lstickX = *cur++;
            break;
        case CpuCmd_SetLstickY:
            data->lstickY = *cur++;
            break;
        case CpuCmd_SetCstickX:
            data->cstickX = *cur++;
            break;
        case CpuCmd_SetCstickY:
            data->cstickY = *cur++;
            break;
        case CpuCmd_SetRtrigger:
            data->rtrigger = *cur++;
            break;
        case CpuCmd_SetLtrigger:
            data->ltrigger = *cur++;
            break;
        case CpuCmd_ReleaseAll:
            data->x0 = 0;
            break;
        case CpuCmd_WaitFor:
            data->command_duration = (u8) *cur++;
            break;
        case CpuCmd_LstickTowardDestination:
            magnitude = *cur;
            cur++;
            angle = lb_8000D008(data->x54.y - fp->cur_pos.y,
                                data->x54.x - fp->cur_pos.x);
            data->lstickX = magnitude * cosf(angle);
            data->lstickY = magnitude * sinf(angle);
            break;
        case CpuCmd_LstickXTowardDestination:
            if (data->x54.x > fp->cur_pos.x) {
                data->lstickX = *cur;
            } else {
                data->lstickX = -*cur;
            }
            cur++;
            break;
        case CpuCmd_LstickTowardFighter: {
            Fighter* target;
            magnitude = *cur;
            cur++;
            target = data->x44;
            if (target != NULL) {
                angle = lb_8000D008(target->cur_pos.y - fp->cur_pos.y,
                                    target->cur_pos.x - fp->cur_pos.x);
                data->lstickX = magnitude * cosf(angle);
                data->lstickY = magnitude * sinf(angle);
            }
            break;
        }
        case CpuCmd_LstickXTowardFighter: {
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
        case CpuCmd_LstickXForward:
            if (fp->facing_dir >= 0.0) {
                data->lstickX = *cur;
            } else {
                data->lstickX = -*cur;
            }
            cur++;
            break;
        case CpuCmd_WaitIfMotionId: {
            u8 motion_id = *cur++;
            if (fp->motion_id == motion_id) {
                data->command_duration = 1;
                return;
            }
            break;
        }
        case CpuCmd_Unk0x93:
            data->x18 = (u8) *cur++;
            break;
        case CpuCmd_LstickTowardDestinationClamped: {
            temp_r25 = *cur;
            cur++;
            temp_r27_3 = *cur;
            cur++;
            angle = lb_8000D008(data->x54.y - fp->cur_pos.y,
                                data->x54.x - fp->cur_pos.x);
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
        case CpuCmd_LstickXTowardDestinationClamped: {
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
        case CpuCmd_LstickForwardClamped: {
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
        case CpuCmd_Done:
            data->command_duration = 0;
            data->csP = NULL;
            return;
        }
    }
    data->csP = cur;
}

/// Resets the write position to the start of the script buffer area
void ftCo_800B462C(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    data->write_pos = data->buffer;
}

/// Writes a command to the current location in the script buffer area
void ftCo_800B463C(Fighter* fp, u8 cmd)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (data->write_pos >= data->buffer + sizeof(data->buffer)) {
        HSD_ASSERTREPORT(501, 0, "command script buffer over flow!\n");
    }
    *data->write_pos = cmd;
    data->write_pos++;
}

void ftCo_800B46B8(Fighter* fp, u8 cmd, u8 arg)
{
    ftCo_800B463C(fp, cmd);
    ftCo_800B463C(fp, arg);
}

void ftCo_800B4778(Fighter* fp, u8 cmd, u8 arg1, u8 arg2)
{
    ftCo_800B463C(fp, cmd);
    ftCo_800B463C(fp, arg1);
    ftCo_800B463C(fp, arg2);
}

/**
 * Runs an existing command script from a table loaded from .dat
 */
void ftCo_800B4880(Fighter* fp, int script_idx)
{
    u8* cmd = Fighter_804D64FC->cmdscripts[script_idx];
    while (*cmd != CpuCmd_Done) {
        ftCo_800B463C(fp, *cmd);
        if (*cmd > CpuCmd_OneArgEnd) {
            cmd++;
            ftCo_800B463C(fp, *cmd);
        }
        if (*cmd > CpuCmd_ZeroArgEnd) {
            cmd++;
            ftCo_800B463C(fp, *cmd);
        }
        cmd++;
    }
    ftCo_800B463C(fp, *cmd);
}

void ftCo_800B49F4(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;

    ftCo_800B463C(fp, CpuCmd_Done);

    data->csP = data->buffer;
    data->command_duration = 1;
}

void ftCo_800B4A78(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    data->x0 = 0;
    data->lstickX = 0;
    data->lstickY = 0;
    data->cstickX = 0;
    data->cstickY = 0;
    data->rtrigger = 0;
    data->ltrigger = 0;
    data->csP = NULL;
    data->command_duration = 0;
    ftCo_800B462C(fp);
}
