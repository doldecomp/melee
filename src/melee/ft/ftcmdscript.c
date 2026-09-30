/**
 * @file ftcmdscript.c
 * @brief Fighter CPU command script bytecode virtual machine implementation.
 * @details Implements the execution engine, opcode dispatcher, and bytecode assembly
 * routines for computer-controlled fighter controller simulation.
 *
 * System Architecture:
 * - Virtual Controller Macro Interpreter: Translates compact bytecode instructions
 *   into simulated GameCube controller hardware inputs (buttons, analog stick, C-stick,
 *   and analog triggers) stored in `fp->cpu`.
 * - Frame Timing & Synchronization: Supports multi-frame input holds (`CpuCmd_PressAFor`),
 *   delay timers (`CpuCmd_WaitFor`), and animation synchronization (`CpuCmd_WaitIfMotionId`)
 *   that polls fighter motion state IDs to synchronize input execution with move animations.
 * - Dynamic Script Assembly: Provides utility functions to emit instructions into the
 *   fighter's 256-byte script buffer or copy precompiled AI subroutines from `PlCo.dat`
 *   via `Fighter_804D64FC->cmdscripts`.
 *
 * Module prefix: ft / ftCo (Fighter Common)
 */

#include "ftcmdscript.h"

#include <math.h>

#include "fighter.h"
#include "types.h"
#include <melee/lb/lb_00CE.h>
#include <sysdolphin/baselib/debug.h>

/**
 * @brief Executes the CPU command script interpreter tick for a fighter.
 * @details Evaluates the active CPU script buffer for the fighter:
 * 1. Checks if a script is active (`cpu->csP != NULL`) and ticks `cpu->command_duration`.
 * 2. If the active delay has not expired, returns immediately to maintain input hold.
 * 3. Once duration reaches 0, enters the bytecode execution loop, consuming opcodes
 *    and updating virtual controller state until encountering a new duration delay,
 *    an animation synchronization wait (`CpuCmd_WaitIfMotionId`), or `CpuCmd_Done`.
 *
 * @param fp Pointer to the Fighter instance data
 */
void ftCo_800B3E04(Fighter* fp)
{
    struct CpuFighter* cpu;
    s8* script_ptr;
    int unused_r27;
    int magnitude;
    int clamp_mag;
    int step_mag;

    f32 angle;
    int clamp_x;
    int clamp_y;
    int new_stick_x;
    int new_stick_y;
    int fwd_stick_x;

    cpu = &fp->cpu;
    if (cpu->csP == NULL) {
        return;
    }

    // If the duration is already zero, there's nothing to do.
    if (cpu->command_duration == 0) {
        return;
    }

    // Decrement active frame delay counter
    cpu->command_duration--;

    // If duration hasn't reached zero, the previous command is still running
    if (cpu->command_duration != 0) {
        return;
    }

    script_ptr = cpu->csP;

    // Safety assertion: ensure instruction pointer resides within the 256-byte buffer
    if (cpu->csP < cpu->buffer) {
        HSD_ASSERTREPORT(0x21, 0, "csP is bad address\n");
    }
    if (cpu->csP >= cpu->buffer + sizeof(cpu->buffer)) {
        HSD_ASSERTREPORT(0x24, 0, "csP is bad address\n");
    }

    // Bytecode execution loop: consume instructions until a non-zero delay is encountered
    while (cpu->command_duration == 0) {
        switch ((u8) *script_ptr++) {
        /* ------------------------------------------------------------- */
        /* Zero-Operand Opcodes: Immediate Digital Button Operations    */
        /* ------------------------------------------------------------- */
        case CpuCmd_PressA:
            cpu->buttons |= HSD_PAD_A;
            break;
        case CpuCmd_ReleaseA:
            cpu->buttons &= ~HSD_PAD_A;
            break;
        case CpuCmd_PressB:
            cpu->buttons |= HSD_PAD_B;
            break;
        case CpuCmd_ReleaseB:
            cpu->buttons &= ~HSD_PAD_B;
            break;
        case CpuCmd_PressX:
            cpu->buttons |= HSD_PAD_X;
            break;
        case CpuCmd_ReleaseX:
            cpu->buttons &= ~HSD_PAD_X;
            break;
        case CpuCmd_PressY:
            cpu->buttons |= HSD_PAD_Y;
            break;
        case CpuCmd_ReleaseY:
            cpu->buttons &= ~HSD_PAD_Y;
            break;
        case CpuCmd_PressStart:
            cpu->buttons |= HSD_PAD_START;
            break;
        case CpuCmd_ReleaseStart:
            cpu->buttons &= ~HSD_PAD_START;
            break;

        /* R trigger full press: sets both maximum analog pressure and digital click */
        case CpuCmd_PressR:
            cpu->rtrigger = 0xFF; // Full analog shield pressure
            cpu->buttons |= HSD_PAD_R;
            break;
        case CpuCmd_ReleaseR:
            cpu->rtrigger = 0;
            cpu->buttons &= ~HSD_PAD_R;
            break;

        case CpuCmd_PressL:
            cpu->buttons |= HSD_PAD_L;
            break;
        case CpuCmd_ReleaseL:
            cpu->buttons &= ~HSD_PAD_L;
            break;
        case CpuCmd_PressZ:
            cpu->buttons |= HSD_PAD_Z;
            break;
        case CpuCmd_ReleaseZ:
            cpu->buttons &= ~HSD_PAD_Z;
            break;

        /* D-Pad inputs (used for taunts) */
        case CpuCmd_PressUp:
            cpu->buttons |= HSD_PAD_DPADUP;
            break;
        case CpuCmd_ReleaseUp:
            cpu->buttons &= ~HSD_PAD_DPADUP;
            break;
        case CpuCmd_PressDown:
            cpu->buttons |= HSD_PAD_DPADDOWN;
            break;
        case CpuCmd_ReleaseDown:
            cpu->buttons &= ~HSD_PAD_DPADDOWN;
            break;
        case CpuCmd_PressRight:
            cpu->buttons |= HSD_PAD_DPADRIGHT;
            break;
        case CpuCmd_ReleaseRight:
            cpu->buttons &= ~HSD_PAD_DPADRIGHT;
            break;
        case CpuCmd_PressLeft:
            cpu->buttons |= HSD_PAD_DPADLEFT;
            break;
        case CpuCmd_ReleaseLeft:
            cpu->buttons &= ~HSD_PAD_DPADLEFT;
            break;

        /* ------------------------------------------------------------- */
        /* One-Operand Opcodes: Timed Button Actions & Delays            */
        /* ------------------------------------------------------------- */
        case CpuCmd_PressAFor:
            cpu->buttons |= HSD_PAD_A;
            cpu->command_duration = (u8) *script_ptr++;
            break;
        case CpuCmd_ReleaseAFor:
            cpu->buttons &= ~HSD_PAD_A;
            cpu->command_duration = (u8) *script_ptr++;
            break;
        case CpuCmd_PressBFor:
            cpu->buttons |= HSD_PAD_B;
            cpu->command_duration = (u8) *script_ptr++;
            break;
        case CpuCmd_ReleaseBFor:
            cpu->buttons &= ~HSD_PAD_B;
            cpu->command_duration = (u8) *script_ptr++;
            break;
        case CpuCmd_PressXFor:
            cpu->buttons |= HSD_PAD_X;
            cpu->command_duration = (u8) *script_ptr++;
            break;
        case CpuCmd_ReleaseXFor:
            cpu->buttons &= ~HSD_PAD_X;
            cpu->command_duration = (u8) *script_ptr++;
            break;
        case CpuCmd_PressYFor:
            cpu->buttons |= HSD_PAD_Y;
            cpu->command_duration = (u8) *script_ptr++;
            break;
        case CpuCmd_ReleaseYFor:
            cpu->buttons &= ~HSD_PAD_Y;
            cpu->command_duration = (u8) *script_ptr++;
            break;

        /* Direct analog axis placements (-128 to 127) */
        case CpuCmd_SetLstickX:
            cpu->lstick.x = *script_ptr++;
            break;
        case CpuCmd_SetLstickY:
            cpu->lstick.y = *script_ptr++;
            break;
        case CpuCmd_SetCstickX:
            cpu->cstick.x = *script_ptr++;
            break;
        case CpuCmd_SetCstickY:
            cpu->cstick.y = *script_ptr++;
            break;

        /* Analog trigger values (0 to 255) for variable shield size */
        case CpuCmd_SetRtrigger:
            cpu->rtrigger = *script_ptr++;
            break;
        case CpuCmd_SetLtrigger:
            cpu->ltrigger = *script_ptr++;
            break;

        /* Clear all buttons simultaneously */
        case CpuCmd_ReleaseAll:
            cpu->buttons = 0;
            break;

        /* Standstill / pause delay for specified frame count */
        case CpuCmd_WaitFor:
            cpu->command_duration = (u8) *script_ptr++;
            break;

        /* Direct 2D control stick toward target destination vector (cpu->x54) */
        case CpuCmd_LstickTowardDestination:
            magnitude = *script_ptr;
            script_ptr++;
            angle = lb_8000D008(cpu->x54.y - fp->cur_pos.y,
                                cpu->x54.x - fp->cur_pos.x);
            cpu->lstick.x = magnitude * cosf(angle);
            cpu->lstick.y = magnitude * sinf(angle);
            break;

        /* Push stick horizontally toward destination X */
        case CpuCmd_LstickXTowardDestination:
            if (cpu->x54.x > fp->cur_pos.x) {
                cpu->lstick.x = *script_ptr;
            } else {
                cpu->lstick.x = -*script_ptr;
            }
            script_ptr++;
            break;

        /* Direct 2D control stick toward opponent fighter (cpu->x44) */
        case CpuCmd_LstickTowardFighter: {
            Fighter* target;
            magnitude = *script_ptr;
            script_ptr++;
            target = cpu->x44;
            if (target != NULL) {
                angle = lb_8000D008(target->cur_pos.y - fp->cur_pos.y,
                                    target->cur_pos.x - fp->cur_pos.x);
                cpu->lstick.x = magnitude * cosf(angle);
                cpu->lstick.y = magnitude * sinf(angle);
            }
            break;
        }

        /* Push stick horizontally toward opponent fighter X */
        case CpuCmd_LstickXTowardFighter: {
            Fighter* target = cpu->x44;
            s8 stick_x = *script_ptr++;
            if (target != NULL) {
                if (target->cur_pos.x < fp->cur_pos.x) {
                    stick_x = -stick_x;
                }
                if (target != NULL) {
                    cpu->lstick.x = stick_x;
                }
            }
            break;
        }

        /* Push stick horizontally in fighter's facing direction */
        case CpuCmd_LstickXForward:
            if (fp->facing_dir >= 0.0) {
                cpu->lstick.x = *script_ptr;
            } else {
                cpu->lstick.x = -*script_ptr;
            }
            script_ptr++;
            break;

        /*
         * Animation Synchronization:
         * If the fighter is currently executing the specified motion state ID,
         * yield execution for 1 frame and poll again next frame until the
         * animation/motion state finishes or transitions.
         */
        case CpuCmd_WaitIfMotionId: {
            u8 motion_id = *script_ptr++;
            if (fp->motion_id == motion_id) {
                cpu->command_duration = 1;
                return;
            }
            break;
        }

        /* Set AI tactic / scenario ID */
        case CpuCmd_Unk0x93:
            cpu->x18 = (u8) *script_ptr++;
            break;

        /* ------------------------------------------------------------- */
        /* Two-Operand Opcodes: Clamped Stick Steering                   */
        /* ------------------------------------------------------------- */

        /* Smooth 2D stick steering toward destination with step delta & clamp */
        case CpuCmd_LstickTowardDestinationClamped: {
            step_mag = *script_ptr;
            script_ptr++;
            clamp_mag = *script_ptr;
            script_ptr++;
            angle = lb_8000D008(cpu->x54.y - fp->cur_pos.y,
                                cpu->x54.x - fp->cur_pos.x);
            new_stick_x = cpu->lstick.x + (s8) (step_mag * cosf(angle));
            clamp_x = (s8) (clamp_mag * cosf(angle));
            if (new_stick_x > clamp_x) {
                new_stick_x = clamp_x;
            } else if (new_stick_x < -clamp_x) {
                new_stick_x = -clamp_x;
            }
            cpu->lstick.x = new_stick_x;
            new_stick_y = cpu->lstick.y + (s8) (step_mag * sinf(angle));
            clamp_y = (s8) (clamp_mag * sinf(angle));
            if (new_stick_y > clamp_y) {
                new_stick_y = clamp_y;
            }
            if (new_stick_y < -clamp_y) {
                new_stick_y = -clamp_y;
            }
            cpu->lstick.y = new_stick_y;
            break;
        }

        /* Steer stick X toward destination with step delta & clamp */
        case CpuCmd_LstickXTowardDestinationClamped: {
            int dx;
            int clamp_x;
            int stick_x;
            dx = *script_ptr;
            script_ptr++;
            clamp_x = *script_ptr;
            script_ptr++;
            if (cpu->x54.x > fp->cur_pos.x) {
                stick_x = cpu->lstick.x + dx;
            } else {
                stick_x = cpu->lstick.x - dx;
            }
            if (stick_x > clamp_x) {
                stick_x = clamp_x;
            } else if (stick_x < -clamp_x) {
                stick_x = -clamp_x;
            }
            cpu->lstick.x = stick_x;
            break;
        }

        /* Steer stick X forward with step delta & clamp */
        case CpuCmd_LstickForwardClamped: {
            int dx;
            int clamp_x;
            dx = *script_ptr;
            script_ptr++;
            clamp_x = *script_ptr;
            script_ptr++;
            if (fp->facing_dir > 0.0) {
                fwd_stick_x = cpu->lstick.x + dx;
            } else {
                fwd_stick_x = cpu->lstick.x - dx;
            }
            if (fwd_stick_x > clamp_x) {
                fwd_stick_x = clamp_x;
            } else if (fwd_stick_x < -clamp_x) {
                fwd_stick_x = -clamp_x;
            }
            cpu->lstick.x = fwd_stick_x;
            break;
        }

        /* End of command sequence: halt interpreter */
        case CpuCmd_Done:
            cpu->command_duration = 0;
            cpu->csP = NULL;
            return;
        }
    }
    cpu->csP = script_ptr;
}

/**
 * @brief Resets the script buffer write position to the beginning of the buffer.
 * @param fp Pointer to the Fighter instance data
 */
void ftCo_800B462C(Fighter* fp)
{
    struct CpuFighter* cpu = &fp->cpu;
    cpu->write_pos = cpu->buffer;
}

/**
 * @brief Appends a single command opcode byte to the fighter's script buffer.
 * @details Performs buffer overflow bounds checking against the 256-byte buffer capacity.
 * @param fp Pointer to the Fighter instance data
 * @param cmd Opcode byte to append
 */
void ftCo_800B463C(Fighter* fp, u8 cmd)
{
    struct CpuFighter* cpu = &fp->cpu;
    if (cpu->write_pos >= cpu->buffer + sizeof(cpu->buffer)) {
        HSD_ASSERTREPORT(501, 0, "command script buffer over flow!\n");
    }
    *cpu->write_pos = cmd;
    cpu->write_pos++;
}

/**
 * @brief Appends a one-operand command sequence (opcode + argument byte) to buffer.
 * @param fp Pointer to the Fighter instance data
 * @param cmd Opcode byte to append
 * @param arg Operand argument byte
 */
void ftCo_800B46B8(Fighter* fp, u8 cmd, u8 arg)
{
    ftCo_800B463C(fp, cmd);
    ftCo_800B463C(fp, arg);
}

/**
 * @brief Appends a two-operand command sequence (opcode + 2 argument bytes) to buffer.
 * @param fp Pointer to the Fighter instance data
 * @param cmd Opcode byte to append
 * @param arg1 First operand argument byte
 * @param arg2 Second operand argument byte
 */
void ftCo_800B4778(Fighter* fp, u8 cmd, u8 arg1, u8 arg2)
{
    ftCo_800B463C(fp, cmd);
    ftCo_800B463C(fp, arg1);
    ftCo_800B463C(fp, arg2);
}

/**
 * @brief Decodes and copies a precompiled command script subroutine from PlCo.dat.
 * @details Reads precompiled bytecode from `Fighter_804D64FC->cmdscripts[script_idx]`.
 * Uses opcode threshold bounds to dynamically copy 0, 1, or 2 argument bytes:
 * - If opcode > `CpuCmd_OneArgEnd` (0xBF): Copies 2 arguments (triggers both `if` checks).
 * - If opcode > `CpuCmd_ZeroArgEnd` (0x7F): Copies 1 argument (triggers second `if` check).
 * - Otherwise: Copies 0 arguments.
 * Appends instructions until `CpuCmd_Done` is reached, and finishes with `CpuCmd_Done`.
 *
 * @param fp Pointer to the Fighter instance data
 * @param script_idx Index of the script in the global AI script table
 */
void ftCo_800B4880(Fighter* fp, int script_idx)
{
    u8* script_cmd = Fighter_804D64FC->cmdscripts[script_idx];
    while (*script_cmd != CpuCmd_Done) {
        ftCo_800B463C(fp, *script_cmd);
        if (*script_cmd > CpuCmd_OneArgEnd) {
            script_cmd++;
            ftCo_800B463C(fp, *script_cmd);
        }
        if (*script_cmd > CpuCmd_ZeroArgEnd) {
            script_cmd++;
            ftCo_800B463C(fp, *script_cmd);
        }
        script_cmd++;
    }
    ftCo_800B463C(fp, *script_cmd);
}

/**
 * @brief Finalizes script assembly and arms the interpreter for execution.
 * @details Appends `CpuCmd_Done` terminator, sets instruction pointer `csP = buffer`,
 * and sets `command_duration = 1` so bytecode execution begins on the next frame tick.
 *
 * @param fp Pointer to the Fighter instance data
 */
void ftCo_800B49F4(Fighter* fp)
{
    struct CpuFighter* cpu = &fp->cpu;

    ftCo_800B463C(fp, CpuCmd_Done);

    cpu->csP = cpu->buffer;
    cpu->command_duration = 1;
}

/**
 * @brief Aborts script execution, clears virtual controller inputs, and resets VM.
 * @details Zeroes all button states, control stick coordinates, C-stick coordinates,
 * and analog triggers. Sets `csP = NULL` and `command_duration = 0` to halt the
 * interpreter, and resets the buffer write position via #ftCo_800B462C.
 *
 * @param fp Pointer to the Fighter instance data
 */
void ftCo_800B4A78(Fighter* fp)
{
    struct CpuFighter* cpu = &fp->cpu;
    cpu->buttons = 0;
    cpu->lstick.x = 0;
    cpu->lstick.y = 0;
    cpu->cstick.x = 0;
    cpu->cstick.y = 0;
    cpu->rtrigger = 0;
    cpu->ltrigger = 0;
    cpu->csP = NULL;
    cpu->command_duration = 0;
    ftCo_800B462C(fp);
}
