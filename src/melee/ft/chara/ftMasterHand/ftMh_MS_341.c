#include "ftMh_MS_341.h"

#include "ftMh_CaptureMasterHand_0.h"
#include "ftMh_MS_343.h"
#include "ftMh_MS_346.h"
#include "ftMh_MS_348.h"
#include "ftMh_MS_352.h"
#include "ftMh_MS_353.h"
#include "ftMh_MS_355.h"
#include "ftMh_MS_357.h"
#include "ftMh_MS_359.h"
#include "ftMh_MS_361.h"
#include "ftMh_MS_363.h"
#include "ftMh_MS_366.h"
#include "ftMh_MS_369.h"
#include "ftMh_MS_371_0.h"
#include "ftMh_MS_371_1.h"
#include "ftMh_MS_372.h"
#include "ftMh_MS_380.h"
#include "ftMh_MS_382.h"
#include "ftMh_MS_383.h"
#include "ftMh_MS_389.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"
#include "mp/mplib.h"

// 8014FDD0 0014C9B0
// https://decomp.me/scratch/HWef2
void ftMh_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftMasterHand_SpecialAttrs);
}

// 8014FE10 0014C9F0
// https://decomp.me/scratch/JL2E5
void ftMh_MS_341_8014FE10(HSD_GObj* gobj)
{
    if (Stage_80225194() == 0xFB) {
        ifStage251(gobj);
        return;
    }
    ftMh_MS_343_801510B0(gobj);
}

// 8014FE58 0014CA38
// https://decomp.me/scratch/kfqG6
void ftMh_MS_341_8014FE58(HSD_GObj* gobj)
{
    return;
}

void ftMh_MS_341_8014FE5C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->action_id == 341) || (fp->action_id == 342)) {
        fp->cur_pos = fp->ev.mh.x2240_pos;
    } else {
        fp->ev.mh.x2240_pos = fp->cur_pos;
    }
    if (fp->ev.mh.x2258 == 389) {
        Fighter_ChangeMotionState(gobj, 341, 0, 0, fp->x894_currentAnimFrame,
                                  1.0f, 0.0f);
    } else {
        Fighter_ChangeMotionState(gobj, 341, 0, 0, 0.0f, 1.0f, 0.0f);
    }
    fp->ev.mh.x2258 = 341;
}

void ftMh_MS_341_8014FF1C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->action_id == 341) || (fp->action_id == 342)) {
        fp->cur_pos = fp->ev.mh.x2240_pos;
    } else {
        fp->ev.mh.x2240_pos = fp->cur_pos;
    }
    if (fp->ev.mh.x2258 == 390) {
        Fighter_ChangeMotionState(gobj, 342, 0, 0, fp->x894_currentAnimFrame,
                                  1.0f, 0.0f);
    } else {
        Fighter_ChangeMotionState(gobj, 342, 0, 0, 0.0f, 1.0f, 0.0f);
    }
    fp->ev.mh.x2258 = 342;
}

void ftMh_MS_341_8014FFDC(HSD_GObj* gobj)
{
    Fighter* r31_fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    if (r31_fp->ev.mh.x2258 == 0x186) {
        if ((r31_fp->action_id == 0x155) || (r31_fp->action_id == 0x156)) {
            r31_fp->cur_pos = r31_fp->ev.mh.x2240_pos;
        } else {
            r31_fp->ev.mh.x2240_pos = r31_fp->cur_pos;
        }
        if (r31_fp->ev.mh.x2258 == 0x186) {
            Fighter_ChangeMotionState(
                gobj, 0x156, 0, 0, r31_fp->x894_currentAnimFrame, 1.0f, 0.0f);
        } else {
            Fighter_ChangeMotionState(gobj, 0x156, 0, 0, 0.0f, 1.0f, 0.0f);
        }
        r31_fp->ev.mh.x2258 = 0x156;
        return;
    }
    if ((r31_fp->action_id == 0x155) || (r31_fp->action_id == 0x156)) {
        r31_fp->cur_pos = r31_fp->ev.mh.x2240_pos;
    } else {
        r31_fp->ev.mh.x2240_pos = r31_fp->cur_pos;
    }
    if (r31_fp->ev.mh.x2258 == 0x185) {
        Fighter_ChangeMotionState(gobj, 0x155, 0, 0,
                                  r31_fp->x894_currentAnimFrame, 1.0f, 0.0f);
    } else {
        Fighter_ChangeMotionState(gobj, 0x155, 0, 0, 0.0f, 1.0f, 0.0f);
    }
    r31_fp->ev.mh.x2258 = 0x155;
}

void ifStage251(HSD_GObj* gobj)
{
    ftMasterHand_SpecialAttrs* r5_attributes;
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* fp_1;

    r5_attributes = fp->x10C_ftData->ext_attr;
    fp->ev.mh.x2258 = 341;
    fp->action_id = 343;
    fp->cur_pos.x = r5_attributes->x30_pos2.x;
    fp->cur_pos.y = r5_attributes->x30_pos2.y;
    fp_1 = GET_FIGHTER(gobj);
    if ((fp_1->action_id == 341) || (fp_1->action_id == 342)) {
        fp_1->cur_pos = fp_1->ev.mh.x2240_pos;
    } else {
        fp_1->ev.mh.x2240_pos = fp_1->cur_pos;
    }
    if (fp_1->ev.mh.x2258 == 389) {
        Fighter_ChangeMotionState(gobj, 341, 0, 0, fp_1->x894_currentAnimFrame,
                                  1.0f, 0.0f);
    } else {
        Fighter_ChangeMotionState(gobj, 341, 0, 0, 0.0f, 1.0f, 0.0f);
    }
    fp_1->ev.mh.x2258 = 341;
}

typedef struct {
    u8 a;
    u8 b;
} u8_pair;

struct MasterHandDataStuff {
    u32 x0[14];
    u8 x38[4 * 4];
    u8_pair x48[6];
    u8 x54[6 * 5];
};

struct MasterHandDataStuff ftMh_Init_803D40D0 = {
    { 0x0000015D, 0x0000015B, 0x0000015F, 0x00000163, 0x00000166, 0x00000167,
      0x00000162, 0x00000172, 0x00000173, 0x0000016F, 0x0000016A, 0x0000016D,
      0x0000017B, 0x0000017C },
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
      0x0C, 0x0D, 0x00, 0x00 },
    { { 0x00, 0x03 },
      { 0x03, 0x04 },
      { 0x07, 0x03 },
      { 0x0A, 0x02 },
      { 0x0C, 0x02 },
      { 0x00, 0x00 } },
    { 0x01, 0x02, 0x03, 0x04, 0x00, 0x00, 0x02, 0x03, 0x04, 0x00,
      0x00, 0x01, 0x03, 0x04, 0x00, 0x00, 0x01, 0x02, 0x04, 0x00,
      0x00, 0x01, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
};

inline void lbl_80150230_inline_1(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->action_id == 0x155 || fp->action_id == 0x156) {
        fp->cur_pos = fp->ev.mh.x2240_pos;
    } else {
        fp->ev.mh.x2240_pos = fp->cur_pos;
    }
    if (fp->ev.mh.x2258 == 0x186) {
        Fighter_ChangeMotionState(gobj, 0x156, 0, 0, fp->x894_currentAnimFrame,
                                  1.0f, 0.0f);
    } else {
        Fighter_ChangeMotionState(gobj, 0x156, 0, 0, 0.0f, 1.0f, 0.0f);
    }
    fp->ev.mh.x2258 = 0x156;
}

inline void lbl_80150230_inline_2(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->ev.mh.x2258 == 0x186) {
        ftMh_MS_341_8014FF1C(gobj);
    } else {
        ftMh_MS_341_8014FE5C(gobj);
    }
}

void ftMh_MS_341_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftMh_MS_341_80150894(gobj);
        if (!ftAnim_IsFramesRemaining(gobj)) {
            if (fp->action_id == 0x155) {
                lbl_80150230_inline_1(gobj);
            } else if (fp->action_id == 0x156) {
                lbl_80150230_inline_2(gobj);
            }
        }
    } else {
        if (--fp->ev.mh.x223C < 0.0f) {
            ftMasterHand_SpecialAttrs* attr = fp->x10C_ftData->ext_attr;
            Vec3 vec;

            /// @todo Unused stack.
#ifdef MUST_MATCH
            u8 _[20];
#endif

            ftBossLib_8015BD24(fp->x1A98, &fp->ev.mh.x223C, fp->ev.mh.x2238,
                               attr->x18, attr->x20, attr->x1C);
            if (ftBossLib_8015C44C(0x1C) == 0x180) {
                // Crazy Hand Combo Attack
                switch (ftBossLib_8015C4C4()) {
                case 0x179:
                    vec.x = attr->x124_pos.x;
                    vec.y = attr->x124_pos.y;
                    vec.z = 0.0f;
                    ftMh_MS_389_80150DC4(gobj, &ftMh_MS_380_80155194, &vec);
                    break;
                case 0x17A:
                    vec.x = attr->x12C_pos.x;
                    vec.y = attr->x12C_pos.y;
                    vec.z = 0.0f;
                    ftMh_MS_389_80150DC4(gobj, &ftMh_MS_382_801552F8, &vec);
                    break;
                case 0x17B:
                    vec.x = attr->x134_pos.x;
                    vec.y = attr->x134_pos.y;
                    vec.z = 0.0f;
                    ftMh_MS_389_80150DC4(gobj, &ftMh_MS_383_80155484, &vec);
                    break;
                case 0x17C:
                    vec.x = attr->x13C_pos.x;
                    vec.y = attr->x13C_pos.y;
                    vec.z = 0.0f;
                    break;
                }
            } else {
                s32 tmp;
                s32 tmp2;
                u8_pair* qwe;
                f32 rand;
                if (fp->ev.mh.x2254 == attr->x24) {
                    fp->ev.mh.x2254 = 0;
                    tmp = 2;
                } else {
                    s32 qwe4 = ftMh_Init_803D40D0
                                   .x54[fp->ev.mh.x224C * 5 + HSD_Randi(5)];
                    tmp = qwe4;
                    if (qwe4 == 2) {
                        fp->ev.mh.x2254 = 0;
                    } else {
                        fp->ev.mh.x2254++;
                    }
                }
                // cast required, don't know why
                qwe = &((u8_pair*) ftMh_Init_803D40D0.x48)[tmp];
                tmp2 = ftMh_Init_803D40D0
                           .x0[ftMh_Init_803D40D0
                                   .x38[qwe->a + HSD_Randi(qwe->b)]];

                fp->ev.mh.x224C = tmp;
                fp->ev.mh.x2250 = tmp2;
                if (fp->x221D_flag.bits.b4) {
                    tmp2 = 0x155;
                }
                switch (tmp2) {
                case 0x15B: // Stage-Wide Slap
                    mpLib_80053FF4(0, &vec);
                    vec.y = attr->x38;
                    ftMh_MS_389_80150DC4(gobj, &ftMh_MS_344_80151828, &vec);
                    break;
                case 0x15D: // Sweep
                    mpLib_80053FF4(0, &vec);
                    vec.y = attr->x50.y;
                    ftMh_MS_389_80150DC4(gobj, &ftMh_MS_348_80151BB8, &vec);
                    break;
                case 0x15F: // Walk
                    vec.x = attr->x40_pos.x;
                    vec.y = attr->x40_pos.y;
                    vec.z = 0.0f;
                    ftMh_MS_389_80150DC4(gobj, &ftMh_MS_353_80151DC4, &vec);
                    break;
                case 0x162: // Drill
                    vec.x = attr->x88_pos.x;
                    vec.y = attr->x88_pos.y;
                    vec.z = 0.0f;
                    ftMh_MS_389_80150DC4(gobj, &ftMh_MS_352_801521DC, &vec);
                    break;
                case 0x163: // Punch
                    vec.x = attr->xA8_pos.x;
                    vec.y = attr->xA8_pos.y;
                    vec.z = 0.0f;
                    ftMh_MS_389_80150DC4(gobj, &ftMh_MS_354_80152370, &vec);
                    break;
                case 0x166: // Ground Slap
                    vec.x = attr->xBC_pos.x;
                    vec.y = attr->xBC_pos.y;
                    vec.z = 0.0f;
                    ftMh_MS_389_80150DC4(gobj, &ftMh_MS_357_801526D8, &vec);
                    break;
                case 0x167: // Poke
                    ftMh_MS_358_80152880(gobj);
                    break;
                case 0x16F: // Jet
                    ftMh_MS_366_80153820(gobj);
                    break;
                case 0x172: // Ram
                    ftMh_MS_371_801541C8(gobj, &ftMh_MS_369_80153B90);
                    break;
                case 0x173: // Crush
                    ftMh_MS_371_801541C8(gobj, &ftMh_MS_370_80153D2C);
                    break;
                case 0x16A: // Lasers
                    rand = HSD_Randf();
                    vec.x = attr->xCC_pos.x * rand * 2.0f + attr->xC4_pos.x -
                            attr->xCC_pos.x;
                    rand = HSD_Randf();
                    vec.y = attr->xCC_pos.y * rand * 2.0f + attr->xC4_pos.y -
                            attr->xCC_pos.y;
                    vec.z = 0.0f;
                    ftMh_MS_389_80150DC4(gobj, &ftMh_MS_359_80152BCC, &vec);
                    break;
                case 0x16D: // Gun
                    ftMh_MS_363_801530A4(gobj);
                    break;
                case 0x17B: // Grab
                    ftMh_MS_372_801542E0(gobj);
                    break;
                case 0x17C: // Grab
                    ftMh_MS_372_801542E0(gobj);
                    break;
                }
            }
        } else if (!ftAnim_IsFramesRemaining(gobj)) {
            if (fp->action_id == 0x155) {
                lbl_80150230_inline_1(gobj);
            } else if (fp->action_id == 0x156) {
                lbl_80150230_inline_2(gobj);
            }
        }
    }
}

// 8015082C 0014D40C
// https://decomp.me/scratch/rgMOD
void ftMh_MS_341_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

// 80150870 0014D450
// https://decomp.me/scratch/7A7RI
void ftMh_MS_341_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

// 80150890 0014D470
void ftMh_MS_341_Coll(HSD_GObj* gobj)
{
    return;
}

// 80150894 0014D474
// https://decomp.me/scratch/nuumS
#define r6_button (HSD_PadMasterStatus[2].button)
#include <baselib/controller.h>
extern HSD_PadStatus HSD_PadMasterStatus[4];
void ftMh_MS_341_80150894(HSD_GObj* gobj)
{
    Fighter* r4_fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* r31_attributes = r4_fp->x10C_ftData->ext_attr;
    Vec3 sp10_pos;
    u32 l_pressed = r6_button & HSD_BUTTON_L;
    // why just l_pressed and not temps for the others?

    if (l_pressed && (r6_button & HSD_BUTTON_DPAD_UP)) {
        // Stage-Wide Slap
        mpLib_80053FF4(0, &sp10_pos);
        sp10_pos.y = r31_attributes->x38;
        ftMh_MS_389_80150DC4(gobj, &ftMh_MS_344_80151828, &sp10_pos);
    } else if (l_pressed && (r6_button & HSD_BUTTON_DPAD_RIGHT)) {
        // Sweep
        mpLib_80053FF4(0, &sp10_pos);
        sp10_pos.y = r31_attributes->x50.y;
        ftMh_MS_389_80150DC4(gobj, &ftMh_MS_348_80151BB8, &sp10_pos);
    } else if (l_pressed && (r6_button & HSD_BUTTON_DPAD_DOWN)) {
        // Walk
        sp10_pos.x = r31_attributes->x40_pos.x;
        sp10_pos.y = r31_attributes->x40_pos.y;
        sp10_pos.z = 0.0f;
        ftMh_MS_389_80150DC4(gobj, &ftMh_MS_353_80151DC4, &sp10_pos);
    } else if ((r6_button & HSD_BUTTON_R) && (r6_button & HSD_BUTTON_DPAD_UP))
    {
        // Drill
        sp10_pos.x = r31_attributes->x88_pos.x;
        sp10_pos.y = r31_attributes->x88_pos.y;
        sp10_pos.z = 0.0f;
        ftMh_MS_389_80150DC4(gobj, &ftMh_MS_352_801521DC, &sp10_pos);
    } else if ((r6_button & HSD_BUTTON_R) &&
               (r6_button & HSD_BUTTON_DPAD_RIGHT))
    {
        // Punch
        sp10_pos.x = r31_attributes->xA8_pos.x;
        sp10_pos.y = r31_attributes->xA8_pos.y;
        sp10_pos.z = 0.0f;
        ftMh_MS_389_80150DC4(gobj, &ftMh_MS_354_80152370, &sp10_pos);
    } else if ((r6_button & HSD_BUTTON_R) &&
               (r6_button & HSD_BUTTON_DPAD_DOWN))
    {
        // Ground Slap
        sp10_pos.x = r31_attributes->xBC_pos.x;
        sp10_pos.y = r31_attributes->xBC_pos.y;
        sp10_pos.z = 0.0f;
        ftMh_MS_389_80150DC4(gobj, &ftMh_MS_357_801526D8, &sp10_pos);
    } else if ((r6_button & HSD_BUTTON_R) &&
               (r6_button & HSD_BUTTON_DPAD_LEFT))
    {
        // Poke
        ftMh_MS_358_80152880(gobj);
    } else if ((r6_button & HSD_BUTTON_A) && (r6_button & HSD_BUTTON_DPAD_UP))
    {
        // Jet
        ftMh_MS_366_80153820(gobj);
    } else if ((r6_button & HSD_BUTTON_A) &&
               (r6_button & HSD_BUTTON_DPAD_RIGHT))
    {
        // Ram
        ftMh_MS_371_801541C8(gobj, &ftMh_MS_369_80153B90);
    } else if ((r6_button & HSD_BUTTON_A) &&
               (r6_button & HSD_BUTTON_DPAD_DOWN))
    {
        // Crush
        ftMh_MS_371_801541C8(gobj, &ftMh_MS_370_80153D2C);
    } else if ((r6_button & HSD_BUTTON_B) && (r6_button & HSD_BUTTON_DPAD_UP))
    {
        // Lasers
        f32 rand;
        rand = HSD_Randf();
        sp10_pos.x = r31_attributes->xCC_pos.x * rand * 2.0f +
                     r31_attributes->xC4_pos.x - r31_attributes->xCC_pos.x;
        rand = HSD_Randf();
        sp10_pos.y = r31_attributes->xCC_pos.y * rand * 2.0f +
                     r31_attributes->xC4_pos.y - r31_attributes->xCC_pos.y;
        sp10_pos.z = 0.0f;
        ftMh_MS_389_80150DC4(gobj, &ftMh_MS_359_80152BCC, &sp10_pos);
    } else if ((r6_button & HSD_BUTTON_B) &&
               ((r6_button & HSD_BUTTON_DPAD_RIGHT)))
    {
        // Gun
        ftMh_MS_363_801530A4(gobj);
    } else if ((r6_button & HSD_BUTTON_Z) &&
               ((r6_button & HSD_BUTTON_DPAD_UP)))
    {
        // Grab
        r4_fp->ev.mh.x2250 = 0x17B;
        ftMh_MS_372_801542E0(gobj);
    } else if ((r6_button & HSD_BUTTON_Z) &&
               ((r6_button & HSD_BUTTON_DPAD_RIGHT)))
    {
        // Grab
        r4_fp->ev.mh.x2250 = 0x17C;
        ftMh_MS_372_801542E0(gobj);
    } else if (((r6_button & HSD_BUTTON_Y)) &&
               ((r6_button & HSD_BUTTON_DPAD_UP)))
    {
        // Crazy Hand Combo Attack
        switch (ftBossLib_8015C4C4()) {
        case 0x179: {
            sp10_pos.x = r31_attributes->x124_pos.x;
            sp10_pos.y = r31_attributes->x124_pos.y;
            sp10_pos.z = 0.0f;
            ftMh_MS_389_80150DC4(gobj, &ftMh_MS_380_80155194, &sp10_pos);
            break;
        }
        case 0x17A: {
            sp10_pos.x = r31_attributes->x12C_pos.x;
            sp10_pos.y = r31_attributes->x12C_pos.y;
            sp10_pos.z = 0.0f;
            ftMh_MS_389_80150DC4(gobj, &ftMh_MS_382_801552F8, &sp10_pos);
            break;
        }
        case 0x17B: {
            sp10_pos.x = r31_attributes->x134_pos.x;
            sp10_pos.y = r31_attributes->x134_pos.y;
            sp10_pos.z = 0.0f;
            ftMh_MS_389_80150DC4(gobj, &ftMh_MS_383_80155484, &sp10_pos);
            break;
        }
        case 0x17C: {
            sp10_pos.x = r31_attributes->x13C_pos.x;
            sp10_pos.y = r31_attributes->x13C_pos.y;
            sp10_pos.z = 0.0f;
            break;
        }
        }
    }
}
