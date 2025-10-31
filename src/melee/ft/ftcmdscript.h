#ifndef MELEE_FT_CMDSCRIPT_H
#define MELEE_FT_CMDSCRIPT_H

#include <melee/ft/forward.h>

typedef enum CPUCommand {
    // These commands press or release buttons
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
    CpuCmd_PressStart,
    CpuCmd_ReleaseStart,
    CpuCmd_ReleaseAll,

    // Signifies the end of a command sequence
    CpuCmd_Done = 0x7F,

#ifndef M2CTX
    CpuCmd_ZeroArgEnd = 0x7F, ///< Previous commands take zero arguments
#endif

    // These commands set analog stick/trigger values
    CpuCmd_SetLstickX,
    CpuCmd_SetLstickY,
    CpuCmd_SetCstickX,
    CpuCmd_SetCstickY,
    CpuCmd_SetRtrigger,
    CpuCmd_SetLtrigger,

    // These commands press/release a button and wait a specified duration
    CpuCmd_PressAFor,
    CpuCmd_ReleaseAFor,
    CpuCmd_PressBFor,
    CpuCmd_ReleaseBFor,
    CpuCmd_PressXFor,
    CpuCmd_ReleaseXFor,
    CpuCmd_PressYFor,
    CpuCmd_ReleaseYFor,
    CpuCmd_WaitFor,

    CpuCmd_LstickTowardDestination,
    CpuCmd_LstickXTowardDestination,
    CpuCmd_LstickXForward,

    CpuCmd_WaitIfMotionId,
    CpuCmd_Unk0x93, ///< Set scenario ID?

    CpuCmd_LstickTowardFighter,
    CpuCmd_LstickXTowardFighter,

    CpuCmd_OneArgEnd = 0xBF, ///< Previous commands take one argument

    CpuCmd_LstickTowardDestinationClamped,
    CpuCmd_LstickXTowardDestinationClamped,
    CpuCmd_LstickForwardClamped,

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

/* 0B3E04 */ void ftCo_800B3E04(Fighter*); ///< Run any pending CPU commands
/* 0B463C */ void ftCo_800B463C(Fighter*, cmd_t cmd);
/* 0B46B8 */ void ftCo_800B46B8(Fighter*, cmd_t cmd, arg_t arg);
/* 0B462C */ void ftCo_800B462C(Fighter*);
/* 0B4778 */ void ftCo_800B4778(Fighter*, cmd_t cmd, arg_t arg1, arg_t arg2);
/* 0B4880 */ void ftCo_800B4880(Fighter*, int script_idx);
/* 0B49F4 */ void ftCo_800B49F4(Fighter*);
/* 0B4A78 */ void ftCo_800B4A78(Fighter*);

#endif
