#ifndef MELEE_GM_ALLSTAR_STATIC_H
#define MELEE_GM_ALLSTAR_STATIC_H

// IWYU pragma: begin_exports
#include "gm_18A1.h"
#include "gm_unsplit.h"
#include "gmallstar.h"
#include "gmregcommon.h"

#include "dolphin/types.h"
#include "gr/ground.h"

#include <sysdolphin/baselib/random.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lbdvd.h>

typedef struct gm_80490940_t {
    /* +0 */ u8 x0;
    /* +1 */ u8 x1;
    /* +2 */ u8 x2;
    /* +3 */ u8 x3;
    /* +4 */ u8 x4;
} gm_80490940_t;

typedef struct gm_803DEBE8_t {
    /* +0 */ u8 x0;
    /* +1 */ u8 x1;
    /* +2 */ u8 x2;
    /* +3 */ u8 x3;
} gm_803DEBE8_t;

typedef struct AllstarRoundInfo {
    /* +0 */ s32 start;
    /* +4 */ s32 count;
} AllstarRoundInfo;

extern CSSData gmClassic_80470708;
extern DebugGameOverData gmClassic_80470850;
extern MatchExitInfo gmClassic_8047086C;
extern StartMeleeData gmClassic_80472AF8;

GameModeState gm_Mode_AllStar_States[] = {
    {
        0,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        1,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        8,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        9,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x10,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x11,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x18,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x19,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x20,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x21,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x28,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x29,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x30,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x31,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x38,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x39,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x40,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x41,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x48,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x49,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x50,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x51,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x58,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x59,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x60,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x68,
        3,
        0,
        NULL,
        gm_801B607C,
        {
            GS_COMING_SOON,
            NULL,
            NULL,
        },
    },
    {
        0x69,
        3,
        0,
        gm_801B5EB4,
        gm_801B5EE4,
        {
            GS_GAMEOVER,
            &gmClassic_80470850,
            &gmClassic_80470850,
        },
    },
    {
        0x70,
        3,
        0,
        gm_801B5F50,
        gm_801B5FB4,
        {
            GS_CSS,
            &gmClassic_80470708,
            &gmClassic_80470708,
        },
    },
    {
        -1,
    },
};

/// @todo Should be length ::CKIND_PLAYABLE_COUNT
static gm_803DEBE8_t gm_803DEBE8[CKIND_PLAYABLE_COUNT - 1] = {
    { 0xB1, 0xB1, 0, 8 },    { 0xB2, 0xB2, 0, 1 },    { 0xB3, 0xB3, 0, 6 },
    { 0xB4, 0xB4, 0, 0x10 }, { 0xB5, 0xB5, 0, 0x11 }, { 0xB6, 0xB6, 0, 4 },
    { 0xB7, 0xB7, 0, 2 },    { 0xB8, 0xB8, 0, 0xD },  { 0xB9, 0xB9, 0, 7 },
    { 0xBA, 0xBA, 0, 0 },    { 0xBB, 0xBB, 0, 0xB },  { 0xBC, 0xBC, 0, 0xF },
    { 0xBD, 0xBD, 0, 0xE },  { 0xBE, 0xBE, 0, 0xC },  { 0xBF, 0xBF, 0, 0x12 },
    { 0xC0, 0xC0, 0, 9 },    { 0xC1, 0xC1, 0, 0xA },  { 0xC2, 0xC2, 0, 5 },
    { 0xC3, 0xC3, 0, 0x16 }, { 0xC4, 0xC4, 0, 0x15 }, { 0xC5, 0xC5, 0, 0x14 },
    { 0xC6, 0xC6, 0, 0x18 }, { 0xC7, 0xC7, 0, 0x17 }, { 0xC9, 0xC9, 0, 0x19 },
    { 0xC8, 0xC8, 0, 3 }
};

static AllstarRoundInfo gm_803DEC4C[13] = {
    { 0, 1 },  { 1, 1 },  { 2, 1 },  { 3, 1 },  { 4, 2 },  { 6, 2 },  { 8, 2 },
    { 10, 2 }, { 12, 3 }, { 15, 3 }, { 18, 3 }, { 21, 3 }, { 24, 1 },
};

gm_80490940_t gm_80490940[5];

#endif
