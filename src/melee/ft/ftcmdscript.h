#ifndef MELEE_FT_CMDSCRIPT_H
#define MELEE_FT_CMDSCRIPT_H

#include <melee/ft/forward.h>

/**
 * @file ftcmdscript.h
 * @brief Fighter CPU command script bytecode virtual machine definitions.
 * @details Declares the instruction set architecture (ISA), bytecode opcodes,
 * and VM functions for the fighter CPU controller script engine. This system
 * acts as an input synthesizer / virtual controller macro interpreter: it translates
 * compact bytecode sequences (loaded from PlCo.dat or generated procedurally by AI)
 * into precise GameCube controller inputs (digital buttons, analog stick X/Y, C-stick X/Y,
 * and analog triggers).
 *
 * Bytecode Architecture:
 * - Variable-length instruction encoding partitioned by opcode range:
 *   - [0x01 .. 0x7E]: 0 operands. Immediate button presses/releases, trigger clicks,
 *                     D-pad directions, and input resets.
 *   - 0x7F (CpuCmd_Done / CpuCmd_ZeroArgEnd): Script termination sentinel.
 *   - [0x80 .. 0xBE]: 1 operand (u8/s8). Stick coordinates, trigger pressure, timed button
 *                     actions, frame delay timers, directional navigation toward destinations
 *                     or targets, and animation state synchronization (CpuCmd_WaitIfMotionId).
 *   - 0xBF (CpuCmd_OneArgEnd): 1-operand range boundary delimiter.
 *   - [0xC0 .. 0xC2]: 2 operands (s8 step_delta, s8 max_clamp). Smooth clamped stick steering.
 *
 * Integration with Fighter Engine:
 * - VM State: Stored in Fighter->cpu (CpuFighter struct), containing a 256-byte circular/linear
 *   bytecode buffer, write head, instruction pointer (csP), and frame delay counter.
 * - Animation Sync: CpuCmd_WaitIfMotionId halts bytecode execution until the fighter
 *   transitions out of a specified Motion State ID, coordinating input timing with frame data.
 * - Contrast: While ftaction.c interprets subaction animation event scripts (hitboxes, hurtboxes,
 *   SFX, GFX embedded in PlXx.dat motion trees), ftcmdscript.c interprets CPU controller input
 *   scripts that pilot the fighter through those actions.
 *
 * Module prefix: ft / ftCo (Fighter Common)
 */

/**
 * @brief CPU command script bytecode instruction opcodes.
 * @details Categorized into three opcode ranges based on operand count:
 * - Zero operands: 0x01 through 0x7E (bounded by #CpuCmd_ZeroArgEnd = 0x7F)
 * - One operand:   0x80 through 0xBE (bounded by #CpuCmd_OneArgEnd = 0xBF)
 * - Two operands:  0xC0 through 0xC2
 */
typedef enum CPUCommand {
    /* ------------------------------------------------------------- */
    /* Zero-Operand Opcodes (0x01 - 0x7E): Immediate Button Actions  */
    /* ------------------------------------------------------------- */

    /// @brief Simulates pressing the A button (bitwise OR with HSD_PAD_A).
    CpuCmd_PressA = 1,

    /// @brief Simulates releasing the A button (bitwise AND with ~HSD_PAD_A).
    CpuCmd_ReleaseA,

    /// @brief Simulates pressing the B button (bitwise OR with HSD_PAD_B).
    CpuCmd_PressB,

    /// @brief Simulates releasing the B button (bitwise AND with ~HSD_PAD_B).
    CpuCmd_ReleaseB,

    /// @brief Simulates pressing the X jump button (bitwise OR with HSD_PAD_X).
    CpuCmd_PressX,

    /// @brief Simulates releasing the X jump button (bitwise AND with ~HSD_PAD_X).
    CpuCmd_ReleaseX,

    /// @brief Simulates pressing the Y jump button (bitwise OR with HSD_PAD_Y).
    CpuCmd_PressY,

    /// @brief Simulates releasing the Y jump button (bitwise AND with ~HSD_PAD_Y).
    CpuCmd_ReleaseY,

    /// @brief Presses R button and sets analog R trigger to full pressure (0xFF / 255).
    CpuCmd_PressR,

    /// @brief Releases R button and resets analog R trigger to zero.
    CpuCmd_ReleaseR,

    /// @brief Simulates pressing the L shield button (bitwise OR with HSD_PAD_L).
    CpuCmd_PressL,

    /// @brief Simulates releasing the L shield button (bitwise AND with ~HSD_PAD_L).
    CpuCmd_ReleaseL,

    /// @brief Simulates pressing the Z grab button (bitwise OR with HSD_PAD_Z).
    CpuCmd_PressZ,

    /// @brief Simulates releasing the Z grab button (bitwise AND with ~HSD_PAD_Z).
    CpuCmd_ReleaseZ,

    /// @brief Simulates pressing D-Pad Up (bitwise OR with HSD_PAD_DPADUP).
    CpuCmd_PressUp,

    /// @brief Simulates releasing D-Pad Up (bitwise AND with ~HSD_PAD_DPADUP).
    CpuCmd_ReleaseUp,

    /// @brief Simulates pressing D-Pad Down (bitwise OR with HSD_PAD_DPADDOWN).
    CpuCmd_PressDown,

    /// @brief Simulates releasing D-Pad Down (bitwise AND with ~HSD_PAD_DPADDOWN).
    CpuCmd_ReleaseDown,

    /// @brief Simulates pressing D-Pad Right (bitwise OR with HSD_PAD_DPADRIGHT).
    CpuCmd_PressRight,

    /// @brief Simulates releasing D-Pad Right (bitwise AND with ~HSD_PAD_DPADRIGHT).
    CpuCmd_ReleaseRight,

    /// @brief Simulates pressing D-Pad Left (bitwise OR with HSD_PAD_DPADLEFT).
    CpuCmd_PressLeft,

    /// @brief Simulates releasing D-Pad Left (bitwise AND with ~HSD_PAD_DPADLEFT).
    CpuCmd_ReleaseLeft,

    /// @brief Simulates pressing the Start button (bitwise OR with HSD_PAD_START).
    CpuCmd_PressStart,

    /// @brief Simulates releasing the Start button (bitwise AND with ~HSD_PAD_START).
    CpuCmd_ReleaseStart,

    /// @brief Clears all digital button states simultaneously (cpu.buttons = 0).
    CpuCmd_ReleaseAll,

    /// @brief Signifies end of script sequence; halts VM (csP = NULL, duration = 0).
    CpuCmd_Done = 0x7F,

#ifndef M2CTX
    /// @brief Upper bound delimiter for zero-argument opcodes (0x01 - 0x7F).
    CpuCmd_ZeroArgEnd = 0x7F, ///< Previous commands take zero arguments
#endif

    /* ------------------------------------------------------------- */
    /* One-Operand Opcodes (0x80 - 0xBE): Stick, Timers, Navigation  */
    /* ------------------------------------------------------------- */

    /// @brief Sets left analog control stick horizontal axis (-128 to 127).
    CpuCmd_SetLstickX,

    /// @brief Sets left analog control stick vertical axis (-128 to 127).
    CpuCmd_SetLstickY,

    /// @brief Sets C-stick horizontal axis (-128 to 127) for smashes/aerials.
    CpuCmd_SetCstickX,

    /// @brief Sets C-stick vertical axis (-128 to 127) for smashes/aerials.
    CpuCmd_SetCstickY,

    /// @brief Sets R trigger analog value (0 to 255) for variable shield size.
    CpuCmd_SetRtrigger,

    /// @brief Sets L trigger analog value (0 to 255) for variable shield size.
    CpuCmd_SetLtrigger,

    /// @brief Presses A button and sets active duration to N frames.
    CpuCmd_PressAFor,

    /// @brief Releases A button and sets active duration to N frames.
    CpuCmd_ReleaseAFor,

    /// @brief Presses B button and sets active duration to N frames.
    CpuCmd_PressBFor,

    /// @brief Releases B button and sets active duration to N frames.
    CpuCmd_ReleaseBFor,

    /// @brief Presses X button and sets active duration to N frames.
    CpuCmd_PressXFor,

    /// @brief Releases X button and sets active duration to N frames.
    CpuCmd_ReleaseXFor,

    /// @brief Presses Y button and sets active duration to N frames.
    CpuCmd_PressYFor,

    /// @brief Releases Y button and sets active duration to N frames.
    CpuCmd_ReleaseYFor,

    /// @brief Waits for specified frame duration without changing button states.
    CpuCmd_WaitFor,

    /// @brief Directs 2D control stick vector toward target destination (cpu.x54).
    CpuCmd_LstickTowardDestination,

    /// @brief Pushes stick horizontally (+mag or -mag) toward destination X.
    CpuCmd_LstickXTowardDestination,

    /// @brief Pushes stick horizontally in fighter's facing direction.
    CpuCmd_LstickXForward,

    /// @brief Waits 1 frame if current motion matches operand, stalling until state changes.
    CpuCmd_WaitIfMotionId,

    /// @brief Sets CPU AI scenario / tactic identifier field (cpu.x18).
    CpuCmd_Unk0x93, ///< Set scenario ID?

    /// @brief Directs 2D control stick vector toward target fighter (cpu.x44).
    CpuCmd_LstickTowardFighter,

    /// @brief Pushes stick horizontally (+mag or -mag) toward target fighter X.
    CpuCmd_LstickXTowardFighter,

    /// @brief Upper bound delimiter for one-argument opcodes (0x80 - 0xBF).
    CpuCmd_OneArgEnd = 0xBF, ///< Previous commands take one argument

    /* ------------------------------------------------------------- */
    /* Two-Operand Opcodes (0xC0 - 0xC2): Clamped Stick Steering     */
    /* ------------------------------------------------------------- */

    /// @brief Steers stick 2D vector toward destination with step delta and max clamp.
    CpuCmd_LstickTowardDestinationClamped,

    /// @brief Steps stick X toward destination with delta, clamped to max absolute value.
    CpuCmd_LstickXTowardDestinationClamped,

    /// @brief Steps stick X forward with delta, clamped to max absolute value.
    CpuCmd_LstickForwardClamped,

    /// @brief Total count of CPU command opcodes.
    CpuCmd_Count,
} CPUCommand;

/// CPU commands must fit in a u8!
STATIC_ASSERT(CpuCmd_Count <= U8_MAX);

#ifdef M2CTX
typedef CPUCommand cmd_t;
typedef s8 arg_t;
#else
typedef u8 cmd_t;
typedef u8 arg_t;
#endif

/**
 * @brief Executes the CPU command script interpreter tick for a fighter.
 * @details Decrements active frame delay timer (command_duration). When expired,
 * executes sequential bytecode instructions starting from csP until encountering
 * a new duration delay, motion state wait condition, or CpuCmd_Done.
 * @param fp Pointer to the Fighter instance data
 */
/* 0B3E04 */ void ftCo_800B3E04(Fighter* fp); ///< Run any pending CPU commands

/**
 * @brief Emits a single zero-operand command byte to the fighter's script buffer.
 * @details Asserts against buffer overflow if write head exceeds 256-byte capacity.
 * @param fp Pointer to the Fighter instance data
 * @param cmd Opcode to write
 */
/* 0B463C */ void ftCo_800B463C(Fighter* fp, cmd_t cmd);

/**
 * @brief Emits a one-operand command sequence (opcode + argument byte) to buffer.
 * @param fp Pointer to the Fighter instance data
 * @param cmd Opcode to write
 * @param arg Operand argument byte
 */
/* 0B46B8 */ void ftCo_800B46B8(Fighter* fp, cmd_t cmd, arg_t arg);

/**
 * @brief Resets the script buffer write head to the beginning of the buffer.
 * @param fp Pointer to the Fighter instance data
 */
/* 0B462C */ void ftCo_800B462C(Fighter* fp);

/**
 * @brief Emits a two-operand command sequence (opcode + 2 argument bytes) to buffer.
 * @param fp Pointer to the Fighter instance data
 * @param cmd Opcode to write
 * @param arg1 First operand argument byte
 * @param arg2 Second operand argument byte
 */
/* 0B4778 */ void ftCo_800B4778(Fighter* fp, cmd_t cmd, arg_t arg1, arg_t arg2);

/**
 * @brief Copies and decodes a precompiled command script subroutine from PlCo.dat.
 * @details Reads bytecode from Fighter_804D64FC->cmdscripts[script_idx], dynamically
 * determining operand count per instruction using opcode boundary markers, and appends
 * the sequence to the fighter's script buffer until CpuCmd_Done.
 * @param fp Pointer to the Fighter instance data
 * @param script_idx Index into the global AI script table
 */
/* 0B4880 */ void ftCo_800B4880(Fighter* fp, int script_idx);

/**
 * @brief Finalizes script recording and arms the interpreter for execution.
 * @details Appends CpuCmd_Done terminator, resets instruction pointer (csP = buffer),
 * and sets command_duration to 1 so execution starts on the next frame.
 * @param fp Pointer to the Fighter instance data
 */
/* 0B49F4 */ void ftCo_800B49F4(Fighter* fp);

/**
 * @brief Aborts script execution, clears virtual controller inputs, and resets VM.
 * @details Zeroes buttons, control sticks, and triggers; resets csP to NULL and
 * duration to 0; and rewinds buffer write head via #ftCo_800B462C.
 * @param fp Pointer to the Fighter instance data
 */
/* 0B4A78 */ void ftCo_800B4A78(Fighter* fp);

#endif
