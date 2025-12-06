#include "ftMh_Wait1_0.h"

#include "ftMh_BackAirplane3.h"
#include "ftMh_BackCrush_0.h"
#include "ftMh_BackCrush_1.h"
#include "ftMh_BackDisappear.h"
#include "ftMh_Drill.h"
#include "ftMh_Entry.h"
#include "ftMh_FingerBeam.h"
#include "ftMh_FingerGun.h"
#include "ftMh_FingerGun3.h"
#include "ftMh_PaperCrush.h"
#include "ftMh_Poke.h"
#include "ftMh_RockCrush.h"
#include "ftMh_Slam.h"
#include "ftMh_Sweep.h"
#include "ftMh_SweepWait.h"
#include "ftMh_TagApplaud.h"
#include "ftMh_TagCrush.h"
#include "ftMh_Wait1_2.h"
#include "ftMh_Walk.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftbosslib.h"
#include "ft/types.h"
#include "ftMasterHand/types.h"
#include "gr/stage.h"
#include "mp/mplib.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <baselib/controller.h>
#include <baselib/random.h>

static void ifStage251(HSD_GObj* gobj);

void ftMh_MS_341_8014FE10(HSD_GObj* gobj)
{
    if (Stage_80225194() == 251) {
        ifStage251(gobj);
    } else {
        ftMh_MS_343_801510B0(gobj);
    }
}

void ftMh_MS_341_8014FE58(HSD_GObj* gobj) {}

static void ftMh_MS_341_8014FE5C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->motion_id == ftMh_MS_Wait1_0 || fp->motion_id == ftMh_MS_Wait2_0) {
        fp->cur_pos = fp->fv.mh.x2240_pos;
    } else {
        fp->fv.mh.x2240_pos = fp->cur_pos;
    }
    if (fp->fv.mh.x2258 == ftMh_MS_Wait1_2) {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Wait1_0, 0, fp->cur_anim_frame,
                                  1, 0, 0);
    } else {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Wait1_0, 0, 0, 1, 0, 0);
    }
    fp->fv.mh.x2258 = ftMh_MS_Wait1_0;
}

void ftMh_MS_341_8014FF1C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->motion_id == ftMh_MS_Wait1_0 || fp->motion_id == ftMh_MS_Wait2_0) {
        fp->cur_pos = fp->fv.mh.x2240_pos;
    } else {
        fp->fv.mh.x2240_pos = fp->cur_pos;
    }
    if (fp->fv.mh.x2258 == ftMh_MS_Wait2_1) {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Wait2_0, 0, fp->cur_anim_frame,
                                  1, 0, 0);
    } else {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Wait2_0, 0, 0, 1, 0, 0);
    }
    fp->fv.mh.x2258 = ftMh_MS_Wait2_0;
}

void ftMh_MS_341_8014FFDC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[16];
    if (fp->fv.mh.x2258 == ftMh_MS_Wait2_1) {
        if (fp->motion_id == ftMh_MS_Wait1_0 ||
            fp->motion_id == ftMh_MS_Wait2_0)
        {
            fp->cur_pos = fp->fv.mh.x2240_pos;
        } else {
            fp->fv.mh.x2240_pos = fp->cur_pos;
        }
        if (fp->fv.mh.x2258 == ftMh_MS_Wait2_1) {
            Fighter_ChangeMotionState(gobj, ftMh_MS_Wait2_0, 0,
                                      fp->cur_anim_frame, 1, 0, 0);
        } else {
            Fighter_ChangeMotionState(gobj, ftMh_MS_Wait2_0, 0, 0, 1, 0, 0);
        }
        fp->fv.mh.x2258 = ftMh_MS_Wait2_0;
    } else {
        if (fp->motion_id == ftMh_MS_Wait1_0 ||
            fp->motion_id == ftMh_MS_Wait2_0)
        {
            fp->cur_pos = fp->fv.mh.x2240_pos;
        } else {
            fp->fv.mh.x2240_pos = fp->cur_pos;
        }
        if (fp->fv.mh.x2258 == ftMh_MS_Wait1_2) {
            Fighter_ChangeMotionState(gobj, ftMh_MS_Wait1_0, 0,
                                      fp->cur_anim_frame, 1, 0, 0);
        } else {
            Fighter_ChangeMotionState(gobj, ftMh_MS_Wait1_0, 0, 0, 1, 0, 0);
        }
        fp->fv.mh.x2258 = ftMh_MS_Wait1_0;
    }
}

static void ifStage251(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    fp->fv.mh.x2258 = ftMh_MS_Wait1_0;
    fp->motion_id = ftMh_MS_Entry;
    fp->cur_pos.x = da->x30_pos2.x;
    fp->cur_pos.y = da->x30_pos2.y;
    {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->motion_id == ftMh_MS_Wait1_0 ||
            fp->motion_id == ftMh_MS_Wait2_0)
        {
            fp->cur_pos = fp->fv.mh.x2240_pos;
        } else {
            fp->fv.mh.x2240_pos = fp->cur_pos;
        }
        if (fp->fv.mh.x2258 == ftMh_MS_Wait1_2) {
            Fighter_ChangeMotionState(gobj, ftMh_MS_Wait1_0, 0,
                                      fp->cur_anim_frame, 1, 0, 0);
        } else {
            Fighter_ChangeMotionState(gobj, ftMh_MS_Wait1_0, 0, 0, 1, 0, 0);
        }
        fp->fv.mh.x2258 = ftMh_MS_Wait1_0;
    }
}

typedef struct {
    u8 a;
    u8 b;
} u8_pair;

struct MasterHandDataStuff {
    ftMasterhand_MotionState states[14];
    u8 x38[4 * 4];
    u8_pair x48[6];
    u8 x54[6 * 5];
};

struct MasterHandDataStuff ftMh_Init_803D40D0 = {
    { ftMh_MS_Slap, ftMh_MS_SweepLoop, ftMh_MS_WalkLoop, ftMh_MS_RockCrushUp,
      ftMh_MS_PaperCrush, ftMh_MS_Poke1, ftMh_MS_Drill, ftMh_MS_BackPunch,
      ftMh_MS_BackCrush, ftMh_MS_BackAirplane1, ftMh_MS_FingerBeamLoop,
      ftMh_MS_FingerGun2, ftMh_MS_Throw, ftMh_MS_Slam },
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 0 },
    { { 0, 3 }, { 3, 4 }, { 7, 3 }, { 10, 2 }, { 12, 2 }, { 0, 0 } },
    { 1, 2, 3, 4, 0, 0, 2, 3, 4, 0, 0, 1, 3, 4, 0,
      0, 1, 2, 4, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0 }
};

inline void doAnim0(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    if (fp->motion_id == ftMh_MS_Wait1_0 || fp->motion_id == ftMh_MS_Wait2_0) {
        fp->cur_pos = fp->fv.mh.x2240_pos;
    } else {
        fp->fv.mh.x2240_pos = fp->cur_pos;
    }
    if (fp->fv.mh.x2258 == ftMh_MS_Wait2_1) {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Wait2_0, 0, fp->cur_anim_frame,
                                  1, 0, 0);
    } else {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Wait2_0, 0, 0, 1, 0, 0);
    }
    fp->fv.mh.x2258 = ftMh_MS_Wait2_0;
}

inline void doAnim1(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    if (fp->fv.mh.x2258 == ftMh_MS_Wait2_1) {
        ftMh_MS_341_8014FF1C(gobj);
    } else {
        ftMh_MS_341_8014FE5C(gobj);
    }
}

void ftMh_Wait1_0_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[4];
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftMh_MS_341_80150894(gobj);
        if (!ftAnim_IsFramesRemaining(gobj)) {
            if (fp->motion_id == ftMh_MS_Wait1_0) {
                doAnim0(gobj);
            } else if (fp->motion_id == ftMh_MS_Wait2_0) {
                doAnim1(gobj);
            }
        }
    } else {
        if (--fp->fv.mh.x223C < 0) {
            ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
            Vec3 vec;

            u8 _[20];

            ftBossLib_8015BD24(fp->x1A88.level, &fp->fv.mh.x223C,
                               fp->fv.mh.x2238, da->x18, da->x20, da->x1C);
            if (ftBossLib_8015C44C(28) == ftMh_MS_TagRockPaper) {
                // Crazy Hand Combo Attack
                switch (ftBossLib_8015C4C4()) {
                case ftMh_MS_Squeezing1:
                    vec.x = da->x124_pos.x;
                    vec.y = da->x124_pos.y;
                    vec.z = 0;
                    ftMh_MS_389_80150DC4(gobj, ftMh_MS_380_80155194, &vec);
                    break;
                case ftMh_MS_Squeeze:
                    vec.x = da->x12C_pos.x;
                    vec.y = da->x12C_pos.y;
                    vec.z = 0;
                    ftMh_MS_389_80150DC4(gobj, ftMh_MS_382_801552F8, &vec);
                    break;
                case ftMh_MS_Throw:
                    vec.x = da->x134_pos.x;
                    vec.y = da->x134_pos.y;
                    vec.z = 0;
                    ftMh_MS_389_80150DC4(gobj, ftMh_MS_383_80155484, &vec);
                    break;
                case ftMh_MS_Slam:
                    vec.x = da->x13C_pos.x;
                    vec.y = da->x13C_pos.y;
                    vec.z = 0;
                    break;
                }
            } else {
                s32 tmp;
                s32 tmp2;
                u8_pair* qwe;
                float rand;
                if (fp->fv.mh.x2254 == da->x24) {
                    fp->fv.mh.x2254 = 0;
                    tmp = 2;
                } else {
                    s32 qwe4 = ftMh_Init_803D40D0
                                   .x54[fp->fv.mh.x224C * 5 + HSD_Randi(5)];
                    tmp = qwe4;
                    if (qwe4 == 2) {
                        fp->fv.mh.x2254 = 0;
                    } else {
                        fp->fv.mh.x2254++;
                    }
                }
                // cast required, don't know why
                qwe = &((u8_pair*) ftMh_Init_803D40D0.x48)[tmp];
                tmp2 = ftMh_Init_803D40D0
                           .states[ftMh_Init_803D40D0
                                       .x38[qwe->a + HSD_Randi(qwe->b)]];

                fp->fv.mh.x224C = tmp;
                fp->fv.mh.x2250 = tmp2;
                if (fp->x221D_b4) {
                    tmp2 = ftMh_MS_Wait1_0;
                }
                switch (tmp2) {
                case ftMh_MS_SweepLoop: // Stage-Wide Slap
                    mpFloorGetRight(0, &vec);
                    vec.y = da->x38;
                    ftMh_MS_389_80150DC4(gobj, &ftMh_MS_344_80151828, &vec);
                    break;
                case ftMh_MS_Slap: // Sweep
                    mpFloorGetRight(0, &vec);
                    vec.y = da->x50.y;
                    ftMh_MS_389_80150DC4(gobj, &ftMh_MS_348_80151BB8, &vec);
                    break;
                case ftMh_MS_WalkLoop: // Walk
                    vec.x = da->x40_pos.x;
                    vec.y = da->x40_pos.y;
                    vec.z = 0;
                    ftMh_MS_389_80150DC4(gobj, &ftMh_MS_353_80151DC4, &vec);
                    break;
                case ftMh_MS_Drill: // Drill
                    vec.x = da->x88_pos.x;
                    vec.y = da->x88_pos.y;
                    vec.z = 0;
                    ftMh_MS_389_80150DC4(gobj, &ftMh_MS_352_801521DC, &vec);
                    break;
                case ftMh_MS_RockCrushUp: // Punch
                    vec.x = da->xA8_pos.x;
                    vec.y = da->xA8_pos.y;
                    vec.z = 0;
                    ftMh_MS_389_80150DC4(gobj, &ftMh_MS_354_80152370, &vec);
                    break;
                case ftMh_MS_PaperCrush: // Ground Slap
                    vec.x = da->xBC_pos.x;
                    vec.y = da->xBC_pos.y;
                    vec.z = 0;
                    ftMh_MS_389_80150DC4(gobj, &ftMh_MS_357_801526D8, &vec);
                    break;
                case ftMh_MS_Poke1: // Poke
                    ftMh_MS_358_80152880(gobj);
                    break;
                case ftMh_MS_BackAirplane1: // Jet
                    ftMh_MS_366_80153820(gobj);
                    break;
                case ftMh_MS_BackPunch: // Ram
                    ftMh_MS_371_801541C8(gobj, &ftMh_MS_369_80153B90);
                    break;
                case ftMh_MS_BackCrush: // Crush
                    ftMh_MS_371_801541C8(gobj, &ftMh_MS_370_80153D2C);
                    break;
                case ftMh_MS_FingerBeamLoop: // Lasers
                    rand = HSD_Randf();
                    vec.x = da->xCC_pos.x * rand * 2 + da->xC4_pos.x -
                            da->xCC_pos.x;
                    rand = HSD_Randf();
                    vec.y = da->xCC_pos.y * rand * 2 + da->xC4_pos.y -
                            da->xCC_pos.y;
                    vec.z = 0;
                    ftMh_MS_389_80150DC4(gobj, &ftMh_MS_359_80152BCC, &vec);
                    break;
                case ftMh_MS_FingerGun2: // Gun
                    ftMh_MS_363_801530A4(gobj);
                    break;
                case ftMh_MS_Throw: // Grab
                    ftMh_MS_372_801542E0(gobj);
                    break;
                case ftMh_MS_Slam: // Grab
                    ftMh_MS_372_801542E0(gobj);
                    break;
                }
            }
        } else if (!ftAnim_IsFramesRemaining(gobj)) {
            if (fp->motion_id == ftMh_MS_Wait1_0) {
                doAnim0(gobj);
            } else if (fp->motion_id == ftMh_MS_Wait2_0) {
                doAnim1(gobj);
            }
        }
    }
}

void ftMh_Wait1_0_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_Wait1_0_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_Wait1_0_Coll(HSD_GObj* gobj) {}

#define buttons (HSD_PadMasterStatus[2].button)
void ftMh_MS_341_80150894(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    Vec3 pos;
    u32 l_pressed = buttons & HSD_PAD_L;
    // why just l_pressed and not temps for the others?

    if (l_pressed && (buttons & HSD_PAD_DPADUP)) {
        // Stage-Wide Slap
        mpFloorGetRight(0, &pos);
        pos.y = da->x38;
        ftMh_MS_389_80150DC4(gobj, ftMh_MS_344_80151828, &pos);
    } else if (l_pressed && (buttons & HSD_PAD_DPADRIGHT)) {
        // Sweep
        mpFloorGetRight(0, &pos);
        pos.y = da->x50.y;
        ftMh_MS_389_80150DC4(gobj, ftMh_MS_348_80151BB8, &pos);
    } else if (l_pressed && (buttons & HSD_PAD_DPADDOWN)) {
        // Walk
        pos.x = da->x40_pos.x;
        pos.y = da->x40_pos.y;
        pos.z = 0;
        ftMh_MS_389_80150DC4(gobj, &ftMh_MS_353_80151DC4, &pos);
    } else if ((buttons & HSD_PAD_R) && (buttons & HSD_PAD_DPADUP)) {
        // Drill
        pos.x = da->x88_pos.x;
        pos.y = da->x88_pos.y;
        pos.z = 0;
        ftMh_MS_389_80150DC4(gobj, &ftMh_MS_352_801521DC, &pos);
    } else if ((buttons & HSD_PAD_R) && (buttons & HSD_PAD_DPADRIGHT)) {
        // Punch
        pos.x = da->xA8_pos.x;
        pos.y = da->xA8_pos.y;
        pos.z = 0;
        ftMh_MS_389_80150DC4(gobj, ftMh_MS_354_80152370, &pos);
    } else if ((buttons & HSD_PAD_R) && (buttons & HSD_PAD_DPADDOWN)) {
        // Ground Slap
        pos.x = da->xBC_pos.x;
        pos.y = da->xBC_pos.y;
        pos.z = 0;
        ftMh_MS_389_80150DC4(gobj, &ftMh_MS_357_801526D8, &pos);
    } else if ((buttons & HSD_PAD_R) && (buttons & HSD_PAD_DPADLEFT)) {
        // Poke
        ftMh_MS_358_80152880(gobj);
    } else if ((buttons & HSD_PAD_A) && (buttons & HSD_PAD_DPADUP)) {
        // Jet
        ftMh_MS_366_80153820(gobj);
    } else if ((buttons & HSD_PAD_A) && (buttons & HSD_PAD_DPADRIGHT)) {
        // Ram
        ftMh_MS_371_801541C8(gobj, &ftMh_MS_369_80153B90);
    } else if ((buttons & HSD_PAD_A) && (buttons & HSD_PAD_DPADDOWN)) {
        // Crush
        ftMh_MS_371_801541C8(gobj, &ftMh_MS_370_80153D2C);
    } else if ((buttons & HSD_PAD_B) && (buttons & HSD_PAD_DPADUP)) {
        // Lasers
        float rand = HSD_Randf();
        pos.x = da->xCC_pos.x * rand * 2 + da->xC4_pos.x - da->xCC_pos.x;
        rand = HSD_Randf();
        pos.y = da->xCC_pos.y * rand * 2 + da->xC4_pos.y - da->xCC_pos.y;
        pos.z = 0;
        ftMh_MS_389_80150DC4(gobj, &ftMh_MS_359_80152BCC, &pos);
    } else if ((buttons & HSD_PAD_B) && (buttons & HSD_PAD_DPADRIGHT)) {
        // Gun
        ftMh_MS_363_801530A4(gobj);
    } else if ((buttons & HSD_PAD_Z) && (buttons & HSD_PAD_DPADUP)) {
        // Grab
        fp->fv.mh.x2250 = ftMh_MS_Throw;
        ftMh_MS_372_801542E0(gobj);
    } else if ((buttons & HSD_PAD_Z) && (buttons & HSD_PAD_DPADRIGHT)) {
        // Grab
        fp->fv.mh.x2250 = ftMh_MS_Slam;
        ftMh_MS_372_801542E0(gobj);
    } else if ((buttons & HSD_PAD_Y) && (buttons & HSD_PAD_DPADUP)) {
        // Crazy Hand Combo Attack
        switch (ftBossLib_8015C4C4()) {
        case ftMh_MS_Squeezing1: {
            pos.x = da->x124_pos.x;
            pos.y = da->x124_pos.y;
            pos.z = 0;
            ftMh_MS_389_80150DC4(gobj, ftMh_MS_380_80155194, &pos);
            break;
        }
        case ftMh_MS_Squeeze: {
            pos.x = da->x12C_pos.x;
            pos.y = da->x12C_pos.y;
            pos.z = 0;
            ftMh_MS_389_80150DC4(gobj, ftMh_MS_382_801552F8, &pos);
            break;
        }
        case ftMh_MS_Throw: {
            pos.x = da->x134_pos.x;
            pos.y = da->x134_pos.y;
            pos.z = 0;
            ftMh_MS_389_80150DC4(gobj, ftMh_MS_383_80155484, &pos);
            break;
        }
        case ftMh_MS_Slam: {
            pos.x = da->x13C_pos.x;
            pos.y = da->x13C_pos.y;
            pos.z = 0;
            break;
        }
        }
    }
}
