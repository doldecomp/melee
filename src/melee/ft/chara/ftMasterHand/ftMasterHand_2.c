#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_LoadSpecialAttrs(HSD_GObj* fighter_gobj)
{
    COPY_ATTRS(fighter_gobj, MasterHandAttributes);
}

static void ftMasterHand_80150144(HSD_GObj* fighter_gobj);

void ftMasterHand_8014FE10(HSD_GObj* fighter_gobj)
{
    if (Stage_80225194() == 0xFB) {
        ftMasterHand_80150144(fighter_gobj);
        return;
    }

    ftMasterHand_801510B0(fighter_gobj);
}

void ftMasterHand_8014FE58(HSD_GObj* fighter_gobj)
{
    return;
}

static void ftMasterHand_8014FE5C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if ((fp->x10_action_state_index == 341) || (fp->x10_action_state_index == 342))
        fp->xB0_pos = fp->sa.masterhand.x2240_pos;
    else
        fp->sa.masterhand.x2240_pos = fp->xB0_pos;

    if (fp->sa.masterhand.x2258 == 389)
        Fighter_ActionStateChange_800693AC(fighter_gobj, 341, 0, 0, fp->x894_currentAnimFrame, 1.0F, 0.0F);
    else
        Fighter_ActionStateChange_800693AC(fighter_gobj, 341, 0, 0, 0.0F, 1.0F, 0.0F);

    fp->sa.masterhand.x2258 = 341;
}

static void ftMasterHand_8014FF1C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if ((fp->x10_action_state_index == 341) || (fp->x10_action_state_index == 342))
        fp->xB0_pos = fp->sa.masterhand.x2240_pos;
    else
        fp->sa.masterhand.x2240_pos = fp->xB0_pos;

    if (fp->sa.masterhand.x2258 == 390)
        Fighter_ActionStateChange_800693AC(fighter_gobj, 342, 0, 0, fp->x894_currentAnimFrame, 1.0F, 0.0F);
    else
        Fighter_ActionStateChange_800693AC(fighter_gobj, 342, 0, 0, 0.0F, 1.0F, 0.0F);

    fp->sa.masterhand.x2258 = 342;
}

void ftMasterHand_8014FFDC(HSD_GObj* gobj)
{
    u32 unused[4];

    Fighter* fp = gobj->user_data;

    // todo inline ftMasterHand_80150230_inline_1
    if (fp->sa.masterhand.x2258 == 0x186) {
        if ((fp->x10_action_state_index == 0x155) || (fp->x10_action_state_index == 0x156))
            fp->xB0_pos = fp->sa.masterhand.x2240_pos;
        else
            fp->sa.masterhand.x2240_pos = fp->xB0_pos;

        if (fp->sa.masterhand.x2258 == 0x186)
            Fighter_ActionStateChange_800693AC(gobj, 0x156, 0, 0, fp->x894_currentAnimFrame, 1.0F, 0.0F);
        else
            Fighter_ActionStateChange_800693AC(gobj, 0x156, 0, 0, 0.0F, 1.0F, 0.0F);

        fp->sa.masterhand.x2258 = 0x156;
    } else {
        if ((fp->x10_action_state_index == 0x155) || (fp->x10_action_state_index == 0x156))
            fp->xB0_pos = fp->sa.masterhand.x2240_pos;
        else
            fp->sa.masterhand.x2240_pos = fp->xB0_pos;

        if (fp->sa.masterhand.x2258 == 0x185)
            Fighter_ActionStateChange_800693AC(gobj, 0x155, 0, 0, fp->x894_currentAnimFrame, 1.0F, 0.0F);
        else
            Fighter_ActionStateChange_800693AC(gobj, 0x155, 0, 0, 0.0F, 1.0F, 0.0F);

        fp->sa.masterhand.x2258 = 0x155;
    }
}

static void ftMasterHand_80150144(HSD_GObj* fighter_gobj)
{
    u32 unused[2];
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    fp->sa.masterhand.x2258 = 341;
    fp->x10_action_state_index = 343;
    fp->xB0_pos.x = ext_attr->x30_pos2.x;
    fp->xB0_pos.y = ext_attr->x30_pos2.y;

    ftMasterHand_8014FE5C(fighter_gobj);
}

typedef struct {
    u8 a;
    u8 b;
} u8_pair;

typedef struct _MasterHandDataStuff {
    u32 x0[14];
    u8 x38[4 * 4];
    u8_pair x48[6];
    u8 x54[6 * 5];
} MasterHandDataStuff;

static MasterHandDataStuff data_stuff = {
    { 0x15D, 0x15B, 0x15F, 0x163,
      0x166, 0x167, 0x162, 0x172,
      0x173, 0x16F, 0x16A, 0x16D,
      0x17B, 0x17C },
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
    { 0x01, 0x02, 0x03, 0x04, 0x00,
      0x00, 0x02, 0x03, 0x04, 0x00,
      0x00, 0x01, 0x03, 0x04, 0x00,
      0x00, 0x01, 0x02, 0x04, 0x00,
      0x00, 0x01, 0x02, 0x03, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00 }
};

inline void ftMasterHand_80150230_inline_1(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->x10_action_state_index == 0x155 || fp->x10_action_state_index == 0x156)
        fp->xB0_pos = fp->sa.masterhand.x2240_pos;
    else
        fp->sa.masterhand.x2240_pos = fp->xB0_pos;

    if (fp->sa.masterhand.x2258 == 0x186)
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x156, 0, 0, fp->x894_currentAnimFrame, 1.0F, 0.0F);
    else
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x156, 0, 0, 0.0F, 1.0F, 0.0F);

    fp->sa.masterhand.x2258 = 0x156;
}

inline void ftMasterHand_80150230_inline_2(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->sa.masterhand.x2258 == 0x186)
        ftMasterHand_8014FF1C(fighter_gobj);
    else
        ftMasterHand_8014FE5C(fighter_gobj);
}

static void ftMasterHand_80150894(HSD_GObj* fighter_gobj);

void ftMasterHand_80150230(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    s32 unused[2];
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftMasterHand_80150894(fighter_gobj);
        if (ftAnim_IsFramesRemaining(fighter_gobj) == 0) {
            if (fp->x10_action_state_index == 0x155)
                ftMasterHand_80150230_inline_1(fighter_gobj);
            else if (fp->x10_action_state_index == 0x156)
                ftMasterHand_80150230_inline_2(fighter_gobj);
        }
    } else {
        if (--fp->sa.masterhand.x223C < 0.0F) {
            MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;
            Vec3 vec;
            s32 unused[6];
            ftbosslib_8015BD24(fp->x1A98, &fp->sa.masterhand.x223C, fp->sa.masterhand.x2238, ext_attr->x18, ext_attr->x20, ext_attr->x1C);
            if (ftbosslib_8015C44C(0x1C) == 0x180) {
                // Crazy Hand Combo Attack
                switch (ftbosslib_8015C4C4()) {
                case 0x179:
                    vec.x = ext_attr->x124_pos.x;
                    vec.y = ext_attr->x124_pos.y;
                    vec.z = 0.0F;
                    ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80155194, &vec);
                    break;
                case 0x17A:
                    vec.x = ext_attr->x12C_pos.x;
                    vec.y = ext_attr->x12C_pos.y;
                    vec.z = 0.0F;
                    ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_801552F8, &vec);
                    break;
                case 0x17B:
                    vec.x = ext_attr->x134_pos.x;
                    vec.y = ext_attr->x134_pos.y;
                    vec.z = 0.0F;
                    ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80155484, &vec);
                    break;
                case 0x17C:
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
                tmp2 = data_stuff.x0[data_stuff.x38[qwe->a + HSD_Randi(qwe->b)]];

                fp->sa.masterhand.x224C = tmp;
                fp->sa.masterhand.x2250 = tmp2;
                if (fp->x221D_flag.bits.b4) {
                    tmp2 = 0x155;
                }
                switch (tmp2) {
                case 0x15B: // Stage-Wide Slap
                    func_80053FF4(0, &vec);
                    vec.y = ext_attr->x38;
                    ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80151828, &vec);
                    break;
                case 0x15D: // Sweep
                    func_80053FF4(0, &vec);
                    vec.y = ext_attr->x50.y;
                    ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80151BB8, &vec);
                    break;
                case 0x15F: // Walk
                    vec.x = ext_attr->x40_pos.x;
                    vec.y = ext_attr->x40_pos.y;
                    vec.z = 0.0F;
                    ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80151DC4, &vec);
                    break;
                case 0x162: // Drill
                    vec.x = ext_attr->x88_pos.x;
                    vec.y = ext_attr->x88_pos.y;
                    vec.z = 0.0F;
                    ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_801521DC, &vec);
                    break;
                case 0x163: // Punch
                    vec.x = ext_attr->xA8_pos.x;
                    vec.y = ext_attr->xA8_pos.y;
                    vec.z = 0.0F;
                    ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80152370, &vec);
                    break;
                case 0x166: // Ground Slap
                    vec.x = ext_attr->xBC_pos.x;
                    vec.y = ext_attr->xBC_pos.y;
                    vec.z = 0.0F;
                    ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_801526D8, &vec);
                    break;
                case 0x167: // Poke
                    ftMasterHand_80152880(fighter_gobj);
                    break;
                case 0x16F: // Jet
                    ftMasterHand_80153820(fighter_gobj);
                    break;
                case 0x172: // Ram
                    ftMasterHand_801541C8(fighter_gobj, &ftMasterHand_80153B90);
                    break;
                case 0x173: // Crush
                    ftMasterHand_801541C8(fighter_gobj, &ftMasterHand_80153D2C);
                    break;
                case 0x16A: // Lasers
                    rand = HSD_Randf();
                    vec.x = ext_attr->xCC_pos.x * rand * 2.0F + ext_attr->xC4_pos.x - ext_attr->xCC_pos.x;
                    rand = HSD_Randf();
                    vec.y = ext_attr->xCC_pos.y * rand * 2.0F + ext_attr->xC4_pos.y - ext_attr->xCC_pos.y;
                    vec.z = 0.0F;
                    ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80152BCC, &vec);
                    break;
                case 0x16D: // Gun
                    ftMasterHand_801530A4(fighter_gobj);
                    break;
                case 0x17B: // Grab
                    ftMasterHand_801542E0(fighter_gobj);
                    break;
                case 0x17C: // Grab
                    ftMasterHand_801542E0(fighter_gobj);
                    break;
                }
            }
        } else if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
            if (fp->x10_action_state_index == 0x155)
                ftMasterHand_80150230_inline_1(fighter_gobj);
            else if (fp->x10_action_state_index == 0x156)
                ftMasterHand_80150230_inline_2(fighter_gobj);
        }
    }
}

void ftMasterHand_8015082C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_80150870(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_80150890(HSD_GObj* fighter_gobj)
{
    return;
}

#define DPAD_LEFT 1
#define DPAD_RIGHT 2
#define DPAD_DOWN 4
#define DPAD_UP 8
#define BUTTON_Z 0x10
#define BUTTON_R 0x20
#define BUTTON_L 0x40
#define BUTTON_A 0x100
#define BUTTON_B 0x200
#define BUTTON_X 0x400
#define BUTTON_Y 0x800
#define BUTTON_START 0x1000
#define r6_button (HSD_PadMasterStatus[2].button)
#include <sysdolphin/baselib/controller.h>
extern HSD_PadStatus HSD_PadMasterStatus[4];

static void ftMasterHand_80150894(HSD_GObj* fighter_gobj)
{
    Vec3 pos;
    s32 unused;

    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;
    u32 l_pressed = r6_button & BUTTON_L;
    // why just l_pressed and not temps for the others?

    if (l_pressed && (r6_button & DPAD_UP)) {
        // Stage-Wide Slap
        func_80053FF4(0, &pos);
        pos.y = ext_attr->x38;
        ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80151828, &pos);
    } else if (l_pressed && (r6_button & DPAD_RIGHT)) {
        // Sweep
        func_80053FF4(0, &pos);
        pos.y = ext_attr->x50.y;
        ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80151BB8, &pos);
    } else if (l_pressed && (r6_button & DPAD_DOWN)) {
        // Walk
        pos.x = ext_attr->x40_pos.x;
        pos.y = ext_attr->x40_pos.y;
        pos.z = 0.0F;
        ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80151DC4, &pos);
    } else if ((r6_button & BUTTON_R) && (r6_button & DPAD_UP)) {
        // Drill
        pos.x = ext_attr->x88_pos.x;
        pos.y = ext_attr->x88_pos.y;
        pos.z = 0.0F;
        ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_801521DC, &pos);
    } else if ((r6_button & BUTTON_R) && (r6_button & DPAD_RIGHT)) {
        // Punch
        pos.x = ext_attr->xA8_pos.x;
        pos.y = ext_attr->xA8_pos.y;
        pos.z = 0.0F;
        ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80152370, &pos);
    } else if ((r6_button & BUTTON_R) && (r6_button & DPAD_DOWN)) {
        // Ground Slap
        pos.x = ext_attr->xBC_pos.x;
        pos.y = ext_attr->xBC_pos.y;
        pos.z = 0.0F;
        ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_801526D8, &pos);
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
        pos.x = ext_attr->xCC_pos.x * rand * 2.0F + ext_attr->xC4_pos.x - ext_attr->xCC_pos.x;
        rand = HSD_Randf();
        pos.y = ext_attr->xCC_pos.y * rand * 2.0F + ext_attr->xC4_pos.y - ext_attr->xCC_pos.y;
        pos.z = 0.0F;
        ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80152BCC, &pos);
    } else if ((r6_button & BUTTON_B) && ((r6_button & DPAD_RIGHT))) {
        // Gun
        ftMasterHand_801530A4(fighter_gobj);
    } else if ((r6_button & BUTTON_Z) && ((r6_button & DPAD_UP))) {
        // Grab
        fp->sa.masterhand.x2250 = 0x17B;
        ftMasterHand_801542E0(fighter_gobj);
    } else if ((r6_button & BUTTON_Z) && ((r6_button & DPAD_RIGHT))) {
        // Grab
        fp->sa.masterhand.x2250 = 0x17C;
        ftMasterHand_801542E0(fighter_gobj);
    } else if (((r6_button & BUTTON_Y)) && ((r6_button & DPAD_UP))) {
        // Crazy Hand Combo Attack
        switch (ftbosslib_8015C4C4()) {
        case 0x179: {
            pos.x = ext_attr->x124_pos.x;
            pos.y = ext_attr->x124_pos.y;
            pos.z = 0.0F;
            ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80155194, &pos);
            break;
        }
        case 0x17A: {
            pos.x = ext_attr->x12C_pos.x;
            pos.y = ext_attr->x12C_pos.y;
            pos.z = 0.0F;
            ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_801552F8, &pos);
            break;
        }
        case 0x17B: {
            pos.x = ext_attr->x134_pos.x;
            pos.y = ext_attr->x134_pos.y;
            pos.z = 0.0F;
            ftMasterHand_80150DC4(fighter_gobj, &ftMasterHand_80155484, &pos);
            break;
        }
        case 0x17C: {
            pos.x = ext_attr->x13C_pos.x;
            pos.y = ext_attr->x13C_pos.y;
            pos.z = 0.0F;
            break;
        }
        }
    }
}
