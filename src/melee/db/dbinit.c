#include "db.h"

#include <dolphin/card.h>
#include <dolphin/vi.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/ftlib.h>
#include <melee/lb/lbarchive.h>
#include <melee/un/types.h>

/* 4D6B30 */ u16 db_gameLaunchButtonState;
/* 4D6B2C */ char** db_bonus_names;
/* 4D6B28 */ char** db_motionstate_names;
/* 4D6B24 */ char** db_submotion_names;
/* 4D6B20 */ bool db_804D6B20;

int g_debugLevel = 1;

char db_build_timestamp[] = "DATE Feb 13 2002  TIME 22:06:27";

static struct {
    /*  +0 */ HSD_Pad current;
    /*  +4 */ HSD_Pad prev;
    /*  +8 */ HSD_Pad pressed;
    /*  +C */ HSD_Pad released;
    /* +10 */ HSD_Pad repeat;
} db_ButtonStates[4];

extern unsigned char _stack_end[];
extern unsigned char _stack_addr[];

void db_GetGameLaunchButtonState(void)
{
    PADStatus status[4];
    s32 memSize;
    s32 sectorSize;
    int done;
    int pad;

    do {
        VIWaitForRetrace();
        PADRead(status);
        done = 1;
        for (pad = 0; pad < 4; ++pad) {
            if (status[pad].err == -2 || status[pad].err == -3) {
                done = 0;
            }
        }
    } while (!done);

    for (pad = 0; pad < 4; ++pad) {
        if (status[pad].err == 0) {
            break;
        }
    }

    db_gameLaunchButtonState = (pad != 4) ? status[pad].button : 0;

    while (CARDProbeEx(0, &memSize, &sectorSize) == -1) {
        VIWaitForRetrace();
    }
}

void db_Setup(void)
{
    int i;
    struct {
        char** bonus_names;
        char** motionstate_names;
        char** submotion_names;
    }* commonData;

    if (g_debugLevel >= 3) {
        for (i = 0; i < 4; i++) {
            db_ButtonStates[i].repeat = 0;
            db_ButtonStates[i].released = 0;
            db_ButtonStates[i].pressed = 0;
            db_ButtonStates[i].current = 0;
        }

        lbArchive_LoadSymbols("DbCo.dat", (void**) &commonData,
                              "dbLoadCommonData", 0);

        db_bonus_names = commonData->bonus_names;
        db_motionstate_names = commonData->motionstate_names;
        db_submotion_names = commonData->submotion_names;

        fn_SetupCpuHandicapInfo();
        fn_SetupAnimationInfo();
        fn_SetupItemAndPokemonMenu();
        fn_SetupSoundInfo();
        fn_SetupMiscStageVisuals();
        fn_SetupCameraInfo();
        fn_SetupBonusInfo();
        fn_SetupObjAllocLimiter();
        fn_Setup5xSpeed();
    }
}

HSD_Pad db_ButtonsDown(int player)
{
    return db_ButtonStates[player].current;
}

HSD_Pad db_ButtonsPressed(int player)
{
    return db_ButtonStates[player].pressed;
}

HSD_Pad db_ButtonsRepeat(int player)
{
    return db_ButtonStates[player].repeat;
}

void db_PrintEntityCounts(void)
{
    int stack[4];
    int i;

    OSReport("[all PLink num] -- Report --\n");
    for (i = 0; i < 10; i++) {
        OSReport("%5d ", i);
    }
    OSReport("\n");
    OSReport("------------------------------------------------------------\n");

    for (i = 0; i < 64; i++) {
        int count = 0;
        HSD_GObj* var_r3 = ((HSD_GObj**) HSD_GObj_Entities)[i & 0xFF];
        while (var_r3 != NULL) {
            var_r3 = var_r3->next;
            count += 1;
        }
        OSReport("%5d ", count);
        if ((i % 10) == 9) {
            OSReport("\n");
        }
    }
    OSReport("\n");
}

void db_PrintThreadInfo(void)
{
    u8* peak = _stack_end + 4;
    while (*peak == 0xAA) {
        peak += 1;
    }
    OSReport("------ Thread info ------\n");
    OSReport("base:%x, end:%x, size:%d peak:%d \n", _stack_addr, _stack_end,
             _stack_addr - _stack_end, _stack_addr - peak);
    OSReport("\n");
}

static inline int db_get_pad_button(int i)
{
    return HSD_PadMasterStatus[i & 0xFF].button;
}

static inline int db_get_pad_repeat(int i)
{
    return HSD_PadMasterStatus[i & 0xFF].repeat;
}

void db_RunEveryFrame(void)
{
    int stack[4];
    int i;
    int num_players;
    if (g_debugLevel < 3) {
        return;
    }
    if (ftLib_IsMasterHandPresent() || ftLib_IsCrazyHandPresent()) {
        num_players = 2;
    } else {
        num_players = 4;
    }
    for (i = 0; i < num_players; i++) {
        int button = db_get_pad_button(i);
        int repeat = db_get_pad_repeat(i);
        if (button & HSD_PAD_DPADUP) {
            if (button & HSD_PAD_DPADLEFT) {
                button &= ~(HSD_PAD_DPADUP | HSD_PAD_DPADLEFT);
            }
            if (button & HSD_PAD_DPADRIGHT) {
                button &= ~(HSD_PAD_DPADUP | HSD_PAD_DPADRIGHT);
            }
        }
        if (button & HSD_PAD_DPADDOWN) {
            if (button & HSD_PAD_DPADLEFT) {
                button &= ~(HSD_PAD_DPADDOWN | HSD_PAD_DPADLEFT);
            }
            if (button & HSD_PAD_DPADRIGHT) {
                button &= ~(HSD_PAD_DPADDOWN | HSD_PAD_DPADRIGHT);
            }
        }
        if (repeat & HSD_PAD_DPADUP) {
            if (repeat & HSD_PAD_DPADLEFT) {
                repeat &= ~(HSD_PAD_DPADUP | HSD_PAD_DPADLEFT);
            }
            if (repeat & HSD_PAD_DPADRIGHT) {
                repeat &= ~(HSD_PAD_DPADUP | HSD_PAD_DPADRIGHT);
            }
        }
        if (repeat & HSD_PAD_DPADDOWN) {
            if (repeat & HSD_PAD_DPADLEFT) {
                repeat &= ~(HSD_PAD_DPADDOWN | HSD_PAD_DPADLEFT);
            }
            if (repeat & HSD_PAD_DPADRIGHT) {
                repeat &= ~(HSD_PAD_DPADDOWN | HSD_PAD_DPADRIGHT);
            }
        }
        db_ButtonStates[i].prev = db_ButtonStates[i].current;
        db_ButtonStates[i].current = button;
        db_ButtonStates[i].pressed =
            db_ButtonStates[i].current &
            (db_ButtonStates[i].prev ^ db_ButtonStates[i].current);
        db_ButtonStates[i].released =
            db_ButtonStates[i].prev &
            (db_ButtonStates[i].prev ^ db_ButtonStates[i].current);
        db_ButtonStates[i].repeat = repeat;
    }
    for (i = 0; i < 4; i++) {
        fn_CheckMiscVisualEffects(i);
    }
    for (i = 0; i < 4; i++) {
        fn_CheckCameraInfo(i, db_ButtonStates[i].current,
                           db_ButtonStates[i].pressed,
                           HSD_PadMasterStatus[i & 0xFF].nml_subStickX,
                           HSD_PadMasterStatus[i & 0xFF].nml_subStickY);
    }
    for (i = 0; i < 4; i++) {
        fn_CheckSoundInfo(i);
    }
    for (i = 0; i < 4; i++) {
        fn_UpdateObjAllocLimiter(i);
    }
    for (i = 0; i < 4; i++) {
        fn_CheckItemAndPokemonMenu(i);
    }
    for (i = 0; i < 4; i++) {
        fn_CheckCpuHandicapInfo(i);
    }
    fn_UpdateCpuHandicapInfo();
    for (i = 0; i < 4; i++) {
        fn_CheckAnimationInfo(i);
    }
    fn_UpdateAnimationInfo();
    for (i = 0; i < 4; i++) {
        fn_CheckMiscStageEffects(i);
    }
    for (i = 0; i < 4; i++) {
        fn_CheckBonusInfo(i);
    }
    for (i = 0; i < 4; i++) {
        fn_Check5xSpeed(i);
    }
}
