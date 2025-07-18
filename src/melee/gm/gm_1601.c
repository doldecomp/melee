#include <placeholder.h>

#include "gm_1601.static.h"
#include "gm_1601.h"

#include "gmmain_lib.h"

#include <melee/gm/gm_1A45.h>
#include <melee/pl/player.h>
#include <sysdolphin/baselib/controller.h>

#include "cm/camera.h"
#include "db/db.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lb_0192.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbtime.h"
#include "mp/mpcoll.h"
#include "pl/player.h"
#include "sc/types.h"

#include <m2c_macros.h>

/// #gm_801601C4

/// #gm_80160244

/// #gm_801602C0

/// #gm_801603B0

/// #fn_80160400

/// #gm_80160438

/// #gm_80160474

/// #gm_801604DC

/// #gm_80160564

/// #fn_801605EC

/// #gm_80160638

/// #fn_801606A8

/// #fn_80160710

/// #gm_8016075C

/// #fn_801607A8

/// #fn_801607F4

u8 fn_80160840(u8 arg0)
{
    if (arg0 >= 4) {
        return 4;
    }
    return arg0;
}

/// #gm_80160854

U8Vec4 gm_80160968(u8 arg0)
{
    return lbl_803B7864[arg0];
}

/// #gm_80160980

/// #fn_801609E0

/// #gm_80160A60

/// #gm_80160B40

/// #gm_80160C90

/// #fn_80160DE8

/// #fn_80160F58

/// #fn_80161004

/// #fn_80161154

/// #fn_80161C90

/// #fn_80162068

/// #fn_80162170

/// #gm_801623A4

/// #gm_801623D8

/// #gm_801623FC

/// #gm_8016247C

/// #gm_80162574

/// #gm_8016260C

/// #gm_8016279C

/// #gm_80162800

/// #gm_801628C4

/// #gm_80162968

/// #gm_801629B4

/// #gm_80162A00

/// #gm_80162A4C

/// #gm_80162A98

/// #gm_80162B4C

/// #gm_80162B98

/// #gm_80162BD8

/// #fn_80162BFC

/// #gm_80162C48

/// #fn_80162CCC

/// #gm_80162D1C

/// #gm_80162D6C

/// #gm_80162DD4

/// #fn_80162DF8

/// #gm_80162E44

/// #gm_80162EC8

/// #gm_80162F18

/// #gm_80162F68

/// #gm_80162FD0

/// #fn_80162FF4

/// #gm_80163040

/// #fn_801630C4

/// #gm_80163114

/// #gm_80163164

/// #gm_801631CC

/// #gm_801631F0

/// #gm_80163274

/// #gm_80163298

/// #gm_8016332C

/// #gm_80163374

/// #gm_801634D4

/// #gm_8016365C

/// #gm_80163690

/// #gm_801636D8

/// #gm_80163838

/// #gm_801639C0

/// #gm_801639F4

/// #gm_80163A3C

/// #gm_80163B9C

/// #fn_80163D24

/// #fn_80163D74

/// #gm_80163DC4

/// #gm_80163DE8

/// #gm_80163E3C

/// #gm_80163E60

/// #gm_80163EB4

/// #gm_80163ED8

/// #gm_80163F2C

/// #gm_80163F50

/// #fn_80163FA4

u8 gm_8016400C(u8 arg0)
{
    return lbl_803B7888[arg0];
}

u8 gm_80164024(u8 arg0)
{
    return lbl_803B78A4[arg0];
}

/// #gm_8016403C

/// #fn_801640B0

float fn_8016419C(u8 arg0)
{
    return lbl_803B7930[arg0 - 1].x;
}

float fn_801641B4(u8 arg0)
{
    return lbl_803B7930[arg0 - 1].y;
}

u16 gm_801641CC(u8 arg0)
{
    return lbl_803B7808[arg0];
}

/// #gm_801641E4

/// #gm_80164250

/// #fn_801642A0

/// #gm_80164330

/// #gm_80164430

/// #gm_80164504

/// #gm_80164600

/// #gm_8016468C

/// #gm_801647D0

/// #gm_801647F8

bool gm_80164840(u8 id)
{
    int i;
    u16* temp_r31;
    u8 var_r0 = 0;

    temp_r31 = gmMainLib_8015ED8C();
    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if (lbl_803B75F8.id[id] == lbl_803B75F8.thing[i].unk1) {
            var_r0 = lbl_803B75F8.thing[i].unk0;
            break;
        }
    }
    if ((var_r0 == 11) || (*temp_r31 & (1LL << var_r0))) {
        return true;
    }
    return false;
}

/// #gm_80164910

/// #gm_80164A0C

/// Are all unlockable characters unlocked?
bool gm_80164ABC(void)
{
    u16* unlockable_character_bitfield = gmMainLib_8015ED8C();
    int i;
    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if (!(*unlockable_character_bitfield & (1LL << i))) {
            /// @remarks Gekko codes which unlock all characters change this to
            ///          return @c true.
            return false;
        }
    }
    return true;
}

/// #fn_80164B48

/// #gm_80164F18

/// #gm_8016505C

/// #gm_80165084

/// #fn_801650E8

/// #fn_80165108

/// #fn_80165190

/// #fn_801651FC

/// #gm_80165268

/// #gm_80165290

/// #fn_801652B0

/// #fn_801652D8

/// #gm_80165388

/// #gm_801653C8

/// #fn_801653E8

/// #fn_80165418

/// #fn_801654A0

/// #fn_80165548

/// #fn_801656A8

/// #fn_8016588C

/// #fn_80165AC0

/// #fn_80165D60

/// #fn_80165E7C

/// #fn_80165FA4

/// #fn_801661E0

/// #gm_80166378

#ifdef MWERKS_GEKKO
float fn_80166A8C(register Vec3* src, register Vec3* dst)
{
    register float x = src->x;
    asm { psq_st x, Vec3.x(dst), 1, qr3 }
    return x;
}
#else
float fn_80166A8C(register Vec3* src, register Vec3* dst)
{
    NOT_IMPLEMENTED;
}
#endif

/// #gm_80166A98

u8 fn_80166CBC(struct fn_80166CBC_arg0_t* arg0, ssize_t index)
{
    return arg0[index].x5E;
}

/// #gm_80166CCC

/// #gm_80167140

u8 fn_80167194(void* arg0)
{
    return M2C_FIELD(arg0, u8*, 0xD);
}

/// #fn_8016719C

/// #gm_80167320

/// #gm_80167470

/// #gm_801674C4

/// #fn_8016758C

/// #fn_80167638

/// #gm_801677C0

void gm_801677E8(s8 arg0)
{
    lbl_804D6598 = arg0;
}

u8 gm_801677F0(void)
{
    return lbl_804D6598;
}

/// #gm_801677F8

/// #gm_80167858

/// #gm_801678F8

void gm_8016795C(struct PlayerInitData* arg0)
{
    memzero(arg0, sizeof(*arg0));
    arg0->x0 = 0x21;
    arg0->x1 = 3;
    arg0->x2 = 0;
    arg0->x3 = 0;
    arg0->x4 = 0;
    arg0->x5 = -1;
    arg0->x6 = 0;
    arg0->xB = 0;
    arg0->x7 = 0;
    arg0->x8 = 9;
    arg0->x9 = 0;
    arg0->xC_b0 = false;
    arg0->xA = 0x78;
    arg0->xC_b1 = true;
    arg0->xE = 4;
    arg0->xF = 0;
    arg0->x12 = 0;
    arg0->x14 = 0;
    arg0->x18 = 1.0F;
    arg0->x1C = 1.0F;
    arg0->x20 = 1.0F;
}

void gm_80167A14(struct PlayerInitData* arg0)
{
    int i;
    for (i = 0; i < 6; i++) {
        gm_8016795C(&arg0[i]);
    }
}

void gm_80167A64(struct StartMeleeRules* arg0)
{
    memzero(arg0, sizeof(*arg0));
    arg0->x0_3 = 4;

    arg0->xC = 0;
    arg0->xB = 2;

    arg0->x20 = -1;
    arg0->x28 = 0;

    arg0->x3_1 = 1;

    arg0->x3_5 = 1;
    arg0->x3_4 = 1;
    arg0->x4_0 = 1;

    arg0->x1_6 = 0;
    arg0->x2_5 = 1;
    arg0->x2_6 = 1;

    arg0->x2C = 1.0f;
    arg0->x30 = 1.0f;
    arg0->x34 = 1.0f;

    arg0->x4_6 = 1;
    arg0->x4_7 = 1;
    arg0->xD = 0x6E;
    arg0->xA = 0;
}

void gm_80167B50(VsModeData* arg0)
{
    gm_80167A64(&arg0->data.rules);
    gm_80167A14(arg0->data.players);
    arg0->loser = -1;
    arg0->ordered_stage_index = -1;
    arg0->winner = -1;
}

/// #gm_80167BC8

/// #gm_80167FC4

/// #gm_801685D4

/// #gm_80168638

/// #gm_80168710

/// #gm_801688AC

/// #gm_80168940

void gm_8016895C(HSD_JObj* arg0, DynamicModelDesc* arg1, int idx)
{
    HSD_AnimJoint* anim = arg1->anims != NULL ? arg1->anims[idx] : NULL;
    HSD_MatAnimJoint* matanim = arg1->matanims != NULL ? arg1->matanims[idx] : NULL;
    HSD_ShapeAnimJoint* shapeanim = arg1->shapeanims != NULL ? arg1->shapeanims[idx] : NULL;
    HSD_JObjAddAnimAll(arg0, anim, matanim, shapeanim);
}

/// #fn_801689E4

/// #fn_80168A6C

/// #gm_80168B34

/// #gm_80168BF8

/// #gm_80168C5C

/// #fn_80168E54

/// #fn_80168F2C

void fn_80168F7C(void)
{
    lbl_804D659A = 0;
}

void gm_80168F88(void)
{
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 0x10);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

// UnclePunch: Audio_LoadAnnouncer
void gm_80168FC4(void)
{
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 0x20);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

/// #fn_80169000

/// #gm_80169238

/// #gm_80169264

/// #gm_80169290

/// #gm_801692BC

void gm_801692E8(u32 ticks, datetime* datetime)
{
    OSCalendarTime tm;

    lbTime_8000B028(&tm, ticks);
    datetime->year = tm.year;
    datetime->month = tm.mon + 1;
    datetime->day = tm.mday;
    datetime->hour = tm.hour;
    datetime->minute = tm.min;
    if (tm.sec > 59) {
        datetime->second = 59;
    } else {
        datetime->second = tm.sec;
    }
}

UNK_T fn_80169364(void)
{
    return &lbl_8046B488;
}

u8 gm_80169370(s32 arg0)
{
    return lbl_8046B488.pad_0[arg0];
}

u8 gm_80169384(void)
{
    return M2C_FIELD(&lbl_8046B488, u8*, 7);
}

s32 gm_80169394(void)
{
    return lbl_8046B488.unk_10_b3;
}

s32 fn_801693A8(void)
{
    return lbl_8046B488.unk_10_b2;
}

/// #gm_801693BC

void fn_80169434(s32 arg0)
{
    M2C_FIELD(&lbl_8046B488, s32*, 0x1B8) = arg0;
}

/// #fn_80169444

/// #gm_801694A0

UNK_T gm_80169520(void)
{
    return &M2C_FIELD(&lbl_8046B488, UNK_T*, 0x20);
}

UNK_T gm_80169530(void)
{
    return &M2C_FIELD(&lbl_8046B488, UNK_T*, 0xA2);
}

UNK_T gm_80169540(void)
{
    return &M2C_FIELD(&lbl_8046B488, UNK_T*, 0x124);
}

/// #fn_80169550

/// #fn_80169574

/// #fn_801695BC

/// #fn_801697FC

/// #fn_8016989C

/// #fn_80169900

/// #fn_80169A84

/// #fn_80169C54

/// #fn_80169F50

/// #fn_8016A09C

/// #gm_8016A164

s32 fn_8016A1E4(void)
{
    return lbl_8046B488.unk_10_b0;
}

/// #gm_8016A1F8

void gm_8016A21C(StartMeleeRules* arg0)
{
    arg0->x54 = (void*) &lbl_8046B488;
}

/// #gm_8016A22C

void gm_8016A404(s32 arg0)
{
    M2C_FIELD(&lbl_8046B488, s32*, 0x1BC) = arg0;
}

void gm_8016A414(f32 arg8)
{
    M2C_FIELD(&lbl_8046B488, f32*, 0x1C) = arg8;
}

void gm_8016A424(s8 arg0)
{
    M2C_FIELD(&lbl_8046B488, s8*, 0xF) = arg0;
}

/// #gm_8016A434

/// #fn_8016A450

/// #fn_8016A46C

/// #fn_8016A488

/// #fn_8016A4C8

void gm_8016A92C(StartMeleeRules* arg0)
{
    lbl_8046B668.unk_1C = -2;
    arg0->x58 = (int) &lbl_8046B668;
}

/// #gm_8016A944

UNK_T gm_8016A97C(void)
{
    return &M2C_FIELD(&lbl_8046B668, UNK_T*, 0x1C);
}

UNK_T gm_8016A98C(void)
{
    return &lbl_8046B668;
}

/// #gm_8016A998

/// #gm_8016A9E8

/// #gm_8016AC44
