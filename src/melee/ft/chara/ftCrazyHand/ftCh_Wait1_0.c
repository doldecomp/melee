#include "ftCh_Wait1_0.h"

#include "ftCh_GrabUnk1_B174.h"
#include "ftCh_Init.h"
#include "ftCh_TagCancel.h"
#include "types.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/fighter.h"
#include "ft/ft_084E.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCrazyHand/ftCh_BackCrush.h"
#include "ftCrazyHand/ftCh_BackDisappear.h"
#include "ftCrazyHand/ftCh_Damage_0.h"
#include "ftCrazyHand/ftCh_Drill.h"
#include "ftCrazyHand/ftCh_Entry.h"
#include "ftCrazyHand/ftCh_FingerBeam.h"
#include "ftCrazyHand/ftCh_FingerBeam_0.h"
#include "ftCrazyHand/ftCh_Grab.h"
#include "ftCrazyHand/ftCh_Poke.h"
#include "ftCrazyHand/ftCh_RockCrush_0.h"
#include "ftCrazyHand/ftCh_RockCrush_1.h"
#include "ftCrazyHand/ftCh_Sweep.h"
#include "ftCrazyHand/ftCh_SweepWait.h"
#include "ftCrazyHand/ftCh_TagRockPaper.h"
#include "ftCrazyHand/ftCh_Wait1_1.h"
#include "ftCrazyHand/ftCh_Walk.h"
#include "ftMasterHand/types.h"
#include "gr/stage.h"
#include "mp/mplib.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

static void ftCh_Init_80156310(HSD_GObj* gobj);
static void ftCh_Init_80156AD8(HSD_GObj* gobj);

typedef struct {
    u8 a;
    u8 b;
} u8_pair;

struct ftCh_Init_803D4878_t {
    s32 states[18];
    u8 x48[20];
    u8_pair x5C[6];
    u8 x68[32];
};

struct ftCh_Init_803D4878_t ftCh_Init_803D4878 = {
    { ftMh_MS_Entry, ftMh_MS_Damage2, ftMh_MS_SweepLoop, ftMh_MS_Slap,
      ftMh_MS_WalkLoop, ftMh_MS_Drill, ftMh_MS_RockCrushUp,
      ftMh_MS_RockCrushDown, ftMh_MS_BackDisappear, ftMh_MS_Wait1_1,
      ftMh_MS_Grab, ftMh_MS_Poke1, ftMh_MS_FingerBeamStart,
      ftMh_MS_BackAirplane2, ftMh_MS_BackAirplane3, ftMh_MS_Squeezing1,
      ftMh_MS_Squeeze, ftMh_MS_Throw },
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 0, 0 },
    { { 0, 4 }, { 4, 4 }, { 8, 3 }, { 11, 2 }, { 13, 2 }, { 15, 3 } },
    { 1, 2, 3, 4, 5, 0, 2, 3, 4, 5, 0, 1, 3, 4, 5, 0,
      1, 2, 4, 5, 0, 1, 2, 3, 5, 0, 1, 2, 3, 4, 0, 0 }
};

void ftCh_Init_80155FCC(HSD_GObj* gobj)
{
    if (Stage_80225194() == 0xFB) {
        ftCh_Init_80156310(gobj);
    } else {
        ftCh_GrabUnk1_8015B174(gobj);
    }
}

void ftCh_Init_80156014(HSD_GObj* gobj) {}

static void ftCh_Init_80156018(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->motion_id == ftMh_MS_Wait1_0 || fp->motion_id == ftMh_MS_Wait2_0) {
        fp->cur_pos = fp->fv.mh.x2240_pos;
    } else {
        fp->fv.mh.x2240_pos = fp->cur_pos;
    }
    if (fp->fv.mh.x2258 == 0x184) {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Wait1_0, 0, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Wait1_0, 0, 0, 1.0f, 0.0f,
                                  NULL);
    }
    fp->fv.mh.x2258 = ftMh_MS_Wait1_0;
}

static void ftCh_Init_801560D8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->motion_id == 0x155 || fp->motion_id == 0x156) {
        fp->cur_pos = fp->fv.mh.x2240_pos;
    } else {
        fp->fv.mh.x2240_pos = fp->cur_pos;
    }
    if (fp->fv.mh.x2258 == 0x185) {
        Fighter_ChangeMotionState(gobj, 0x156, 0, fp->cur_anim_frame, 1.0f,
                                  0.0f, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, 0x156, 0, 0, 1.0f, 0.0f, NULL);
    }
    fp->fv.mh.x2258 = 0x156;
}

void ftCh_Init_80156198(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[1] = 0;
    if (fp->fv.mh.x2258 == 0x185) {
        ftCh_Init_801560D8(gobj);
    } else {
        ftCh_Init_80156018(gobj);
    }
}

static void ftCh_Init_80156310(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    fp->cmd_vars[1] = 0;
    fp->fv.mh.x2258 = ftMh_MS_Wait1_0;
    fp->motion_id = 0x183;
    fp->cur_pos.x = da->x18;
    fp->cur_pos.y = da->x1C;
    ftCh_Init_80156018(gobj);
}

inline void doAnim0(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    if (fp->motion_id == 0x155 || fp->motion_id == 0x156) {
        fp->cur_pos = fp->fv.mh.x2240_pos;
    } else {
        fp->fv.mh.x2240_pos = fp->cur_pos;
    }
    if (fp->fv.mh.x2258 == 0x185) {
        Fighter_ChangeMotionState(gobj, 0x156, 0, fp->cur_anim_frame, 1.0f,
                                  0.0f, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, 0x156, 0, 0.0f, 1.0f, 0.0f, NULL);
    }
    fp->fv.mh.x2258 = 0x156;
}

inline void doAnim1(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    fp->cmd_vars[1] = 0;
    if (fp->fv.mh.x2258 == 0x185) {
        ftCh_Init_801560D8(gobj);
    } else {
        ftCh_Init_80156018(gobj);
    }
}

void ftCh_Wait1_0_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct ftCh_Init_803D4878_t* data = &ftCh_Init_803D4878;
    u8 _[4];
    s32 slot_type = Player_GetPlayerSlotType(fp->player_id);
    if (fp->cmd_vars[1] != 0) {
        ftBossLib_8015C5F8(gobj);
        fp->cmd_vars[1] = 0;
    }
    if (slot_type == 0) {
        ftCh_Init_80156AD8(gobj);
        if (!ftAnim_IsFramesRemaining(gobj)) {
            if (fp->motion_id == ftMh_MS_Wait1_0) {
                doAnim0(gobj);
            } else if (fp->motion_id == ftMh_MS_Wait2_0) {
                doAnim1(gobj);
            }
        }
    } else {
        if (--fp->fv.mh.x223C < 0) {
            ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
            Vec3 vec;

            u8 __[20];

            ftBossLib_8015BD24(fp->x1A88.level, &fp->fv.mh.x223C,
                               fp->fv.ch.x2238, da->x0, da->x8, da->x4);
            {
                s32 tmp;
                s32 tmp2;
                u8_pair* qwe;
                float rand;
                if (fp->fv.ch.x2254 == da->xC) {
                    fp->fv.ch.x2254 = 0;
                    tmp = 2;
                } else {
                    if (ftBossLib_8015C2E0()) {
                        tmp = data->x68[fp->fv.ch.x224C * 5 + HSD_Randi(4)];
                    } else {
                        tmp = data->x68[fp->fv.ch.x224C * 5 + HSD_Randi(5)];
                    }
                    if (tmp == 2) {
                        fp->fv.ch.x2254 = 0;
                    } else {
                        fp->fv.ch.x2254++;
                    }
                }
                qwe = &((u8_pair*) data->x5C)[tmp];
                tmp2 = data->states[data->x48[qwe->a + HSD_Randi(qwe->b)]];

                fp->fv.ch.x224C = tmp;
                fp->fv.ch.x2250 = tmp2;
                if (fp->x221D_b4) {
                    tmp2 = ftMh_MS_Wait1_0;
                }
                switch (tmp2) {
                case ftMh_MS_Damage2:
                    mpFloorGetLeft(0, &vec);
                    vec.y = da->x24;
                    ftCh_GrabUnk1_8015BA34(gobj, fn_80157080, &vec);
                    break;
                case ftMh_MS_Entry:
                    mpFloorGetLeft(0, &vec);
                    vec.y = da->x20;
                    ftCh_GrabUnk1_8015BA34(gobj, fn_80156F6C, &vec);
                    break;
                case ftMh_MS_SweepLoop:
                    vec.x = da->x2C;
                    vec.y = da->x30_pos2.x;
                    vec.z = 0;
                    ftCh_GrabUnk1_8015BA34(gobj, fn_8015746C, &vec);
                    break;
                case ftMh_MS_Slap:
                    vec.x = da->x30_pos2.y;
                    vec.y = da->x38;
                    vec.z = 0;
                    ftCh_GrabUnk1_8015BA34(gobj, fn_8015755C, &vec);
                    break;
                case ftMh_MS_WalkLoop:
                    vec.x = da->x6C;
                    vec.y = da->x70;
                    vec.z = 0;
                    ftCh_GrabUnk1_8015BA34(gobj, fn_801578E8, &vec);
                    break;
                case ftMh_MS_Drill:
                    vec.x = da->x80;
                    vec.y = da->x84;
                    vec.z = 0;
                    ftCh_GrabUnk1_8015BA34(gobj, fn_80157C50, &vec);
                    break;
                case ftMh_MS_RockCrushUp:
                    ftCh_Init_80157DF8(gobj);
                    break;
                case ftMh_MS_RockCrushDown:
                    vec.x = da->x4C;
                    vec.y = da->x50;
                    vec.z = 0;
                    ftCh_GrabUnk1_8015BA34(gobj, fn_80158144, &vec);
                    break;
                case ftMh_MS_Poke1:
                    rand = HSD_Randf();
                    vec.x = da->x90 * rand * 2 + da->x88_pos.x - da->x90;
                    rand = HSD_Randf();
                    vec.y = da->x94 * rand * 2 + da->x88_pos.y - da->x94;
                    vec.z = 0;
                    ftCh_GrabUnk1_8015BA34(gobj, fn_801582D8, &vec);
                    break;
                case ftMh_MS_FingerBeamStart:
                    vec.x = da->x98;
                    vec.y = da->x9C;
                    vec.z = 0;
                    ftCh_GrabUnk1_8015BA34(gobj, fn_801587B0, &vec);
                    break;
                case ftMh_MS_BackAirplane2:
                    ftCh_Init_80158B3C(gobj);
                    break;
                case ftMh_MS_BackAirplane3:
                    ftCh_Init_80158B3C(gobj);
                    break;
                case ftMh_MS_BackDisappear:
                    ftCh_Init_801597F0(gobj, fn_80159908);
                    break;
                case ftMh_MS_Wait1_1:
                    ftCh_Init_801597F0(gobj, fn_80159AA4);
                    break;
                case ftMh_MS_Grab:
                    ftCh_Init_80159F40(gobj);
                    break;
                case ftMh_MS_Squeezing1:
                    vec.x = da->x104;
                    vec.y = da->x108;
                    vec.z = 0;
                    ftCh_GrabUnk1_8015BA34(gobj, fn_8015AAC8, &vec);
                    break;
                case ftMh_MS_Squeeze:
                    vec.x = da->x10C;
                    vec.y = da->x110_pos.x;
                    vec.z = 0;
                    ftCh_GrabUnk1_8015BA34(gobj, fn_8015AAC8, &vec);
                    break;
                case ftMh_MS_Throw:
                    vec.x = da->x110_pos.y;
                    vec.y = da->x118_pos.x;
                    vec.z = 0;
                    ftCh_GrabUnk1_8015BA34(gobj, fn_8015AAC8, &vec);
                    break;
                case ftMh_MS_Slam:
                    vec.x = da->x118_pos.y;
                    vec.y = da->x120;
                    vec.z = 0;
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

void ftCh_Wait1_0_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Wait1_0_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Wait1_0_Coll(HSD_GObj* gobj) {}

static void ftCh_Init_80156AD8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u32 button;
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    u32 button_tmp = HSD_PadMasterStatus[3].button;
    Vec3 pos;
    button = button_tmp;

    if (button_tmp & (HSD_PAD_L) && button_tmp & (HSD_PAD_DPADUP)) {
        mpFloorGetLeft(0, &pos);
        pos.y = da->x24;
        ftCh_GrabUnk1_8015BA34(gobj, fn_80157080, &pos);
    } else if (button_tmp & (HSD_PAD_L) && button_tmp & (HSD_PAD_DPADRIGHT)) {
        mpFloorGetLeft(0, &pos);
        pos.y = da->x20;
        ftCh_GrabUnk1_8015BA34(gobj, fn_80156F6C, &pos);
    } else if (button_tmp & (HSD_PAD_L) && button_tmp & (HSD_PAD_DPADDOWN)) {
        pos.x = da->x2C;
        pos.y = da->x30_pos2.x;
        pos.z = 0;
        ftCh_GrabUnk1_8015BA34(gobj, fn_8015746C, &pos);
    } else if (button_tmp & (HSD_PAD_L) && button_tmp & (HSD_PAD_DPADLEFT)) {
        pos.x = da->x30_pos2.y;
        pos.y = da->x38;
        pos.z = 0;
        ftCh_GrabUnk1_8015BA34(gobj, fn_8015755C, &pos);
    } else if (button_tmp & (HSD_PAD_R) && button_tmp & (HSD_PAD_DPADUP)) {
        pos.x = da->x6C;
        pos.y = da->x70;
        pos.z = 0;
        ftCh_GrabUnk1_8015BA34(gobj, fn_801578E8, &pos);
    } else if (button_tmp & (HSD_PAD_R) && button_tmp & (HSD_PAD_DPADRIGHT)) {
        pos.x = da->x80;
        pos.y = da->x84;
        pos.z = 0;
        ftCh_GrabUnk1_8015BA34(gobj, fn_80157C50, &pos);
    } else if (button_tmp & (HSD_PAD_R) && button_tmp & (HSD_PAD_DPADDOWN)) {
        ftCh_Init_80157DF8(gobj);
    } else if ((button_tmp & (1 << 5)) && (button & (1 << 0))) {
        pos.x = da->x4C;
        pos.y = da->x50;
        pos.z = 0;
        ftCh_GrabUnk1_8015BA34(gobj, fn_80158144, &pos);
    } else if (button_tmp & (HSD_PAD_B) && button_tmp & (HSD_PAD_DPADUP)) {
        float rand = HSD_Randf();
        pos.x = da->x90 * rand * 2 + da->x88_pos.x - da->x90;
        rand = HSD_Randf();
        pos.y = da->x94 * rand * 2 + da->x88_pos.y - da->x94;
        pos.z = 0;
        ftCh_GrabUnk1_8015BA34(gobj, fn_801582D8, &pos);
    } else if (button_tmp & (HSD_PAD_B) && button_tmp & (HSD_PAD_DPADRIGHT)) {
        pos.x = da->x98;
        pos.y = da->x9C;
        pos.z = 0;
        ftCh_GrabUnk1_8015BA34(gobj, fn_801587B0, &pos);
    } else if (button_tmp & (HSD_PAD_Z) && button_tmp & (HSD_PAD_DPADUP)) {
        fp->fv.ch.x2250 = ftMh_MS_BackAirplane2;
        ftCh_Init_80158B3C(gobj);
    } else if (button_tmp & (HSD_PAD_Z) && button_tmp & (HSD_PAD_DPADRIGHT)) {
        fp->fv.ch.x2250 = ftMh_MS_BackAirplane3;
        ftCh_Init_80158B3C(gobj);
    } else if (button_tmp & (HSD_PAD_A) && button_tmp & (HSD_PAD_DPADUP)) {
        ftCh_Init_801597F0(gobj, fn_80159908);
    } else if (button_tmp & (HSD_PAD_A) && button_tmp & (HSD_PAD_DPADRIGHT)) {
        ftCh_Init_801597F0(gobj, fn_80159AA4);
    } else if (button_tmp & (HSD_PAD_A) && button_tmp & (HSD_PAD_DPADDOWN)) {
        ftCh_Init_80159F40(gobj);
    } else if (button_tmp & (HSD_PAD_Y) && button_tmp & (HSD_PAD_DPADUP)) {
        pos.x = da->x104;
        pos.y = da->x108;
        pos.z = 0;
        fp->fv.ch.x2250 = ftMh_MS_Squeezing1;
        ftCh_GrabUnk1_8015BA34(gobj, fn_8015AAC8, &pos);
    } else if (button_tmp & (HSD_PAD_Y) && button_tmp & (HSD_PAD_DPADRIGHT)) {
        pos.x = da->x10C;
        pos.y = da->x110_pos.x;
        pos.z = 0;
        fp->fv.ch.x2250 = ftMh_MS_Squeeze;
        ftCh_GrabUnk1_8015BA34(gobj, fn_8015AAC8, &pos);
    } else if (button_tmp & (HSD_PAD_Y) && button_tmp & (HSD_PAD_DPADDOWN)) {
        pos.x = da->x110_pos.y;
        pos.y = da->x118_pos.x;
        pos.z = 0;
        fp->fv.ch.x2250 = ftMh_MS_Throw;
        ftCh_GrabUnk1_8015BA34(gobj, fn_8015AAC8, &pos);
    } else if (button_tmp & (HSD_PAD_Y) && button_tmp & (HSD_PAD_DPADLEFT)) {
        pos.x = da->x118_pos.y;
        pos.y = da->x120;
        pos.z = 0;
        fp->fv.ch.x2250 = ftMh_MS_Slam;
        ftCh_GrabUnk1_8015BA34(gobj, fn_8015AAC8, &pos);
    }
}
