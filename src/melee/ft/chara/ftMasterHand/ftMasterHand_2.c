#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_LoadSpecialAttrs(HSD_GObj* fighter_gobj)
{
    COPY_ATTRS(fighter_gobj, MasterHandAttributes);
}

static void ftMasterHand_80150144(HSD_GObj* fighter_gobj);

void ftMasterHand_8014FE10(HSD_GObj* fighter_gobj)
{
    if (Stage_80225194() == 251)
        ftMasterHand_80150144(fighter_gobj);
    else
        ftMasterHand_801510B0(fighter_gobj);
}

void ftMasterHand_8014FE58(HSD_GObj* fighter_gobj)
{
    return;
}

// todo: can maybe be an inline func, but max depth makes it difficult
#define DO_TRANSITION(check_action, result_action)                                                                    \
    if ((fp->x10_action_state_index == AS_MASTERHAND_UNK_341) || fp->x10_action_state_index == AS_MASTERHAND_UNK_342) \
        fp->xB0_pos = fp->sa.masterhand.x2240_pos;                                                                    \
    else                                                                                                              \
        fp->sa.masterhand.x2240_pos = fp->xB0_pos;                                                                    \
                                                                                                                      \
    if (fp->sa.masterhand.x2258 == check_action)                                                                      \
        Fighter_ActionStateChange_800693AC(fighter_gobj, result_action, 0, 0, fp->x894_currentAnimFrame, 1.0F, 0.0F); \
    else                                                                                                              \
        Fighter_ActionStateChange_800693AC(fighter_gobj, result_action, 0, 0, 0.0F, 1.0F, 0.0F);                      \
                                                                                                                      \
    fp->sa.masterhand.x2258 = result_action;

static void ftMasterHand_8014FE5C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    DO_TRANSITION(AS_MASTERHAND_UNK_389, AS_MASTERHAND_UNK_341)
}

static void ftMasterHand_8014FF1C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    DO_TRANSITION(AS_MASTERHAND_UNK_390, AS_MASTERHAND_UNK_342)
}

void ftMasterHand_8014FFDC(HSD_GObj* fighter_gobj)
{
    u32 args_unused[4];

    Fighter* fp = fighter_gobj->user_data;

    if (fp->sa.masterhand.x2258 == AS_MASTERHAND_UNK_390) {
        DO_TRANSITION(AS_MASTERHAND_UNK_390, AS_MASTERHAND_UNK_342);
    } else {
        DO_TRANSITION(AS_MASTERHAND_UNK_389, AS_MASTERHAND_UNK_341);
    }
}

static void ftMasterHand_80150144(HSD_GObj* fighter_gobj)
{
    u32 args_unused[2];

    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    fp->sa.masterhand.x2258 = AS_MASTERHAND_UNK_341;
    fp->x10_action_state_index = AS_MASTERHAND_UNK_343;
    fp->xB0_pos.x = ext_attr->x30_pos2.x;
    fp->xB0_pos.y = ext_attr->x30_pos2.y;

    ftMasterHand_8014FE5C(fighter_gobj);
}

typedef struct {
    u8 a;
    u8 b;
} u8_pair;

typedef struct _MasterHandDataStuff {
    ftMasterHandAction action_states[14];
    u8 x38[4 * 4];
    u8_pair x48[6];
    u8 x54[6 * 5];
} MasterHandDataStuff;

/* todo
 * This is unlikely to be a struct at all.
 * Probably just embedded data within ftMasterHand_80150230.
 */
static MasterHandDataStuff data_stuff = {
    { AS_MASTERHAND_UNK_349,
      AS_MASTERHAND_UNK_347,
      AS_MASTERHAND_UNK_351,
      AS_MASTERHAND_UNK_355,
      AS_MASTERHAND_UNK_358,
      AS_MASTERHAND_UNK_359,
      AS_MASTERHAND_UNK_354,
      AS_MASTERHAND_UNK_370,
      AS_MASTERHAND_UNK_371,
      AS_MASTERHAND_UNK_367,
      AS_MASTERHAND_UNK_362,
      AS_MASTERHAND_UNK_365,
      AS_MASTERHAND_UNK_379,
      AS_MASTERHAND_UNK_380 },
    { 0x00, 0x01, 0x02, 0x03,
      0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0A, 0x0B,
      0x0C, 0x0D, 0x00, 0x00 },
    { { 0x00, 0x03 },
      { 0x03, 0x04 },
      { 0x07, 0x03 },
      { 0x0A, 0x02 },
      { 0x0C, 0x02 },
      { 0x00, 0x00 } },
    { 0x01, 0x02, 0x03, 0x04,
      0x00, 0x00, 0x02, 0x03,
      0x04, 0x00, 0x00, 0x01,
      0x03, 0x04, 0x00, 0x00,
      0x01, 0x02, 0x04, 0x00,
      0x00, 0x01, 0x02, 0x03,
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00 }
};

inline void ftMasterHand_80150230_inline_1(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    DO_TRANSITION(AS_MASTERHAND_UNK_390, AS_MASTERHAND_UNK_342);
}

inline void ftMasterHand_80150230_inline_2(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->sa.masterhand.x2258 == AS_MASTERHAND_UNK_390)
        ftMasterHand_8014FF1C(fighter_gobj);
    else
        ftMasterHand_8014FE5C(fighter_gobj);
}

#include <melee/pl/player.h>

static void ftMasterHand_80150894(HSD_GObj* fighter_gobj);

void ftMasterHand_80150230(HSD_GObj* fighter_gobj)
{
    u32 args_unused[2];

    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftMasterHand_80150894(fighter_gobj);

        /* todo: duplicate branch in this func */ {
            if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
                if (fp->x10_action_state_index == AS_MASTERHAND_UNK_341)
                    ftMasterHand_80150230_inline_1(fighter_gobj);
                else if (fp->x10_action_state_index == AS_MASTERHAND_UNK_342)
                    ftMasterHand_80150230_inline_2(fighter_gobj);
            }
        }
        return;
    }

    if (--fp->sa.masterhand.x223C < 0.0F) {
        MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;
        Vec3 vec;
        s32 unused[6];
        ftbosslib_8015BD24(fp->x1A98, &fp->sa.masterhand.x223C, fp->sa.masterhand.x2238, ext_attr->x18, ext_attr->x20, ext_attr->x1C);
        if (ftbosslib_8015C44C(FTKIND_CREZYH) == AS_MASTERHAND_UNK_384) {
            // Crazy Hand Combo Attack
            switch (ftbosslib_8015C4C4()) {
            case AS_MASTERHAND_UNK_377:
                vec.x = ext_attr->x124_pos.x;
                vec.y = ext_attr->x124_pos.y;
                vec.z = 0.0F;
                ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80155194, &vec);
                break;
            case AS_MASTERHAND_UNK_378:
                vec.x = ext_attr->x12C_pos.x;
                vec.y = ext_attr->x12C_pos.y;
                vec.z = 0.0F;
                ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_801552F8, &vec);
                break;
            case AS_MASTERHAND_UNK_379:
                vec.x = ext_attr->x134_pos.x;
                vec.y = ext_attr->x134_pos.y;
                vec.z = 0.0F;
                ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80155484, &vec);
                break;
            case AS_MASTERHAND_UNK_380:
                vec.x = ext_attr->x13C_pos.x;
                vec.y = ext_attr->x13C_pos.y;
                vec.z = 0.0F;
                break;
            }
        } else {
            s32 tmp;
            s32 tmp2;
            u8_pair* qwe;
            f32 rand;
            if (fp->sa.masterhand.x2254 == ext_attr->x24) {
                fp->sa.masterhand.x2254 = 0;
                tmp = 2;
            } else {
                s32 qwe4 = data_stuff.x54[fp->sa.masterhand.x224C * 5 + HSD_Randi(5)];
                tmp = qwe4;
                if (qwe4 == 2) {
                    fp->sa.masterhand.x2254 = 0;
                } else {
                    fp->sa.masterhand.x2254++;
                }
            }
            // cast required, don't know why
            qwe = &((u8_pair*) data_stuff.x48)[tmp];
            tmp2 = data_stuff.action_states[data_stuff.x38[qwe->a + HSD_Randi(qwe->b)]];

            fp->sa.masterhand.x224C = tmp;
            fp->sa.masterhand.x2250 = tmp2;
            if (fp->x221D_flag.bits.b4) {
                tmp2 = AS_MASTERHAND_UNK_341;
            }
            switch (tmp2) {
            case AS_MASTERHAND_UNK_347: // Stage-Wide Slap
                func_80053FF4(0, &vec);
                vec.y = ext_attr->x38;
                ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80151828, &vec);
                break;
            case AS_MASTERHAND_UNK_349: // Sweep
                func_80053FF4(0, &vec);
                vec.y = ext_attr->x50.y;
                ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80151BB8, &vec);
                break;
            case AS_MASTERHAND_UNK_351: // Walk
                vec.x = ext_attr->x40_pos.x;
                vec.y = ext_attr->x40_pos.y;
                vec.z = 0.0F;
                ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80151DC4, &vec);
                break;
            case AS_MASTERHAND_UNK_354: // Drill
                vec.x = ext_attr->x88_pos.x;
                vec.y = ext_attr->x88_pos.y;
                vec.z = 0.0F;
                ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_801521DC, &vec);
                break;
            case AS_MASTERHAND_UNK_355: // Punch
                vec.x = ext_attr->xA8_pos.x;
                vec.y = ext_attr->xA8_pos.y;
                vec.z = 0.0F;
                ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80152370, &vec);
                break;
            case AS_MASTERHAND_UNK_358: // Ground Slap
                vec.x = ext_attr->xBC_pos.x;
                vec.y = ext_attr->xBC_pos.y;
                vec.z = 0.0F;
                ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_801526D8, &vec);
                break;
            case AS_MASTERHAND_UNK_359: // Poke
                ftMasterHand_80152880(fighter_gobj);
                break;
            case AS_MASTERHAND_UNK_367: // Jet
                ftMasterHand_80153820(fighter_gobj);
                break;
            case AS_MASTERHAND_UNK_370: // Ram
                ftMasterHand_801541C8(fighter_gobj, &ftMasterHand_80153B90);
                break;
            case AS_MASTERHAND_UNK_371: // Crush
                ftMasterHand_801541C8(fighter_gobj, &ftMasterHand_80153D2C);
                break;
            case AS_MASTERHAND_UNK_362: // Lasers
                rand = HSD_Randf();
                vec.x = ext_attr->xCC_pos.x * rand * 2.0F + ext_attr->xC4_pos.x - ext_attr->xCC_pos.x;
                rand = HSD_Randf();
                vec.y = ext_attr->xCC_pos.y * rand * 2.0F + ext_attr->xC4_pos.y - ext_attr->xCC_pos.y;
                vec.z = 0.0F;
                ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80152BCC, &vec);
                break;
            case AS_MASTERHAND_UNK_365: // Gun
                ftMasterHand_801530A4(fighter_gobj);
                break;
            case AS_MASTERHAND_UNK_379: // Grab
                ftMasterHand_801542E0(fighter_gobj);
                break;
            case AS_MASTERHAND_UNK_380: // Grab
                ftMasterHand_801542E0(fighter_gobj);
                break;
            }
        }
    } else {
        /* todo: duplicate branch in this func */ {
            if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
                if (fp->x10_action_state_index == AS_MASTERHAND_UNK_341)
                    ftMasterHand_80150230_inline_1(fighter_gobj);
                else if (fp->x10_action_state_index == AS_MASTERHAND_UNK_342)
                    ftMasterHand_80150230_inline_2(fighter_gobj);
            }
        }
    }
}

void ftMasterHand_8015082C(HSD_GObj* fighter_gobj)
{
    ftMasterHand_CheckPlayerSlotBossStub(fighter_gobj);
}

void ftMasterHand_80150870(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_80150890(HSD_GObj* fighter_gobj)
{
    return;
}

#pragma region "pad.h or something"
#define DPAD_LEFT (1 << 0)
#define DPAD_RIGHT (1 << 1)
#define DPAD_DOWN (1 << 2)
#define DPAD_UP (1 << 3)
#define BUTTON_Z (1 << 4)
#define BUTTON_R (1 << 5)
#define BUTTON_L (1 << 6)
#define BUTTON_A (1 << 8)
#define BUTTON_B (1 << 9)
#define BUTTON_X (1 << 10)
#define BUTTON_Y (1 << 11)
#define BUTTON_START (1 << 12)
#define r6_button (HSD_PadMasterStatus[2].button)
#include <sysdolphin/baselib/controller.h>
extern HSD_PadStatus HSD_PadMasterStatus[4];
#pragma endregion

static void ftMasterHand_80150894(HSD_GObj* fighter_gobj)
{
    Vec3 arg_pos;
    s32 arg_unused;

    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;
    u32 l_pressed = r6_button & BUTTON_L;
    // why just l_pressed and not temps for the others?

    if (l_pressed && (r6_button & DPAD_UP)) {
        // Stage-Wide Slap
        func_80053FF4(0, &arg_pos);
        arg_pos.y = ext_attr->x38;
        ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80151828, &arg_pos);
    } else if (l_pressed && (r6_button & DPAD_RIGHT)) {
        // Sweep
        func_80053FF4(0, &arg_pos);
        arg_pos.y = ext_attr->x50.y;
        ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80151BB8, &arg_pos);
    } else if (l_pressed && (r6_button & DPAD_DOWN)) {
        // Walk
        arg_pos.x = ext_attr->x40_pos.x;
        arg_pos.y = ext_attr->x40_pos.y;
        arg_pos.z = 0.0F;
        ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80151DC4, &arg_pos);
    } else if ((r6_button & BUTTON_R) && (r6_button & DPAD_UP)) {
        // Drill
        arg_pos.x = ext_attr->x88_pos.x;
        arg_pos.y = ext_attr->x88_pos.y;
        arg_pos.z = 0.0F;
        ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_801521DC, &arg_pos);
    } else if ((r6_button & BUTTON_R) && (r6_button & DPAD_RIGHT)) {
        // Punch
        arg_pos.x = ext_attr->xA8_pos.x;
        arg_pos.y = ext_attr->xA8_pos.y;
        arg_pos.z = 0.0F;
        ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80152370, &arg_pos);
    } else if ((r6_button & BUTTON_R) && (r6_button & DPAD_DOWN)) {
        // Ground Slap
        arg_pos.x = ext_attr->xBC_pos.x;
        arg_pos.y = ext_attr->xBC_pos.y;
        arg_pos.z = 0.0F;
        ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_801526D8, &arg_pos);
    } else if ((r6_button & BUTTON_R) && (r6_button & DPAD_LEFT)) {
        // Poke
        ftMasterHand_80152880(fighter_gobj);
    } else if ((r6_button & BUTTON_A) && (r6_button & DPAD_UP)) {
        // Jet
        ftMasterHand_80153820(fighter_gobj);
    } else if ((r6_button & BUTTON_A) && (r6_button & DPAD_RIGHT)) {
        // Ram
        ftMasterHand_801541C8(fighter_gobj, &ftMasterHand_80153B90);
    } else if ((r6_button & BUTTON_A) && (r6_button & DPAD_DOWN)) {
        // Crush
        ftMasterHand_801541C8(fighter_gobj, &ftMasterHand_80153D2C);
    } else if ((r6_button & BUTTON_B) && (r6_button & DPAD_UP)) {
        // Lasers
        f32 rand;
        rand = HSD_Randf();
        arg_pos.x = ext_attr->xCC_pos.x * rand * 2.0F + ext_attr->xC4_pos.x - ext_attr->xCC_pos.x;
        rand = HSD_Randf();
        arg_pos.y = ext_attr->xCC_pos.y * rand * 2.0F + ext_attr->xC4_pos.y - ext_attr->xCC_pos.y;
        arg_pos.z = 0.0F;
        ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80152BCC, &arg_pos);
    } else if ((r6_button & BUTTON_B) && ((r6_button & DPAD_RIGHT))) {
        // Gun
        ftMasterHand_801530A4(fighter_gobj);
    } else if ((r6_button & BUTTON_Z) && ((r6_button & DPAD_UP))) {
        // Grab
        fp->sa.masterhand.x2250 = AS_MASTERHAND_UNK_379;
        ftMasterHand_801542E0(fighter_gobj);
    } else if ((r6_button & BUTTON_Z) && ((r6_button & DPAD_RIGHT))) {
        // Grab
        fp->sa.masterhand.x2250 = AS_MASTERHAND_UNK_380;
        ftMasterHand_801542E0(fighter_gobj);
    } else if (((r6_button & BUTTON_Y)) && ((r6_button & DPAD_UP))) {
        // Crazy Hand Combo Attack
        switch (ftbosslib_8015C4C4()) {
        case AS_MASTERHAND_UNK_377: {
            arg_pos.x = ext_attr->x124_pos.x;
            arg_pos.y = ext_attr->x124_pos.y;
            arg_pos.z = 0.0F;
            ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80155194, &arg_pos);
            break;
        }
        case AS_MASTERHAND_UNK_378: {
            arg_pos.x = ext_attr->x12C_pos.x;
            arg_pos.y = ext_attr->x12C_pos.y;
            arg_pos.z = 0.0F;
            ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_801552F8, &arg_pos);
            break;
        }
        case AS_MASTERHAND_UNK_379: {
            arg_pos.x = ext_attr->x134_pos.x;
            arg_pos.y = ext_attr->x134_pos.y;
            arg_pos.z = 0.0F;
            ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80155484, &arg_pos);
            break;
        }
        case AS_MASTERHAND_UNK_380: {
            arg_pos.x = ext_attr->x13C_pos.x;
            arg_pos.y = ext_attr->x13C_pos.y;
            arg_pos.z = 0.0F;
            break;
        }
        }
    }
}
