#include "gm_1BFA.h"

#include "gm_unsplit.h"

#include "baselib/memory.h"
#include "gm/gmmain_lib.h"
#include "if/textlib.h"
#include "lb/lb_00B0.h"
#include "lb/lbcardgame.h"
#include "lb/lbcardnew.h"
#include "lb/lbtime.h"
#include "ty/toy.h"
#include "ty/tylist.h"

#include <melee/gm/types.h>

/// @remarks this file seems to deal with the challenger approaching functions.

extern UNK_T gm_804D6860[];
extern StartMeleeData gm_80480530;
extern MatchExitInfo gm_80479D98;
extern struct un_804A1F48_t un_804A1F48[];

MinorScene gm_803DFE48_MinorScenes[] = {
    {
        0,
        2,
        0,
        gm_801BFA6C,
        NULL,
        {
            MN_APPROACH,
            gm_804D6860,
            gm_804D6860,
        },
    },
    {
        1,
        2,
        0,
        gm_801BFABC,
        gm_801BFBA8,
        {
            MN_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    {
        2,
        2,
        0,
        gm_801BFCFC,
        gm_801BFF7C,
        {
            MN_PRIZE_INTERFACE,
            un_804A1F48,
            NULL,
        },
    },
    { -1 },
};

void gm_801BFA6C(MinorScene* arg0)
{
    lbl_8046DBD8_t* temp_r3;
    VsApproachData* temp_r31;

    temp_r31 = gm_801A427C(arg0);
    temp_r3 = gm_801736DC();
    temp_r31->x0 = (u8) temp_r3->x4;
    temp_r31->x1 = (u8) temp_r3->x2;
    lb_8001C550();
    lb_8001D164(0);
    lb_8001CE00();
}

void gm_801BFABC(MinorScene* arg0)
{
    lbl_8046DBD8_t* temp_r31;
    StartMeleeData* temp_r30;
    u8 tmp;

    temp_r30 = gm_801A427C(arg0);
    temp_r31 = gm_801736DC();
    gm_80167A64(&temp_r30->rules);
    gm_80167A14(temp_r30->players);
    temp_r30->rules.x0_6 = false;
    temp_r30->rules.x0_0 = 1;
    temp_r30->rules.x0_3 = 2;
    temp_r30->rules.xE = gm_8016075C(gm_80164024(temp_r31->x4));
    gm_801B0620(&temp_r30->players[0], temp_r31->x0, temp_r31->x1, 1,
                temp_r31->x2);
    gm_801B0664(&temp_r30->players[1], temp_r31->x4, 0, 1, 1);
    tmp = temp_r31->x3;
    temp_r30->players[0].xA = tmp;
    temp_r30->players[1].xA = 0x78;
    temp_r30->players[1].xE = 4;
    temp_r30->players[1].cpu_level = gm_80172CC0(temp_r31->x4, tmp);
    gm_8016F088(temp_r30);
}

void gm_801BFBA8(MinorScene* arg0)
{
    lbl_8046DBD8_t* temp_r31;
    u8 temp_r0;
    MatchExitInfo* mei;

    mei = gm_801A4284(arg0);
    temp_r31 = gm_801736DC();
    gm_80162968(mei->match_end.frame_count / 60);
    gm_8016247C((s32) mei->match_end.player_standings[0].xE);
    temp_r0 = mei->match_end.result;
    if ((temp_r0 != 7) && (temp_r0 != 8) &&
        ((s8) mei->match_end.player_standings[0].stocks != 0))
    {
        gm_80164910((s32) temp_r31->x4);
    } else {
        gmMainLib_8015DB2C(gm_80160638((s32) temp_r31->x4));
    }
    gm_80173EEC();
    gm_80172898(0x100U);
    if (gm_801721EC() == 0) {
        gm_801A42E8((s8) temp_r31->x5);
        gm_801A42D4();
    }
}

/// @remarks unsure about this return type.
s32** gm_801BFC60(s16 arg0, s32 arg1, s16 arg2, s32 arg3, void** arg4)
{
    struct un_804A1F48_t* temp_r3;

    if (arg1 == 0) {
        un_804A1F48->x0 = arg0;
        un_804A1F48->x4 = arg3;
        un_804A1F48->x2 = arg2;
        return (&un_804A1F48->x8);
    }
    temp_r3 = HSD_MemAlloc(0xC);
    if (temp_r3 != NULL) {
        temp_r3->x0 = arg0;
        temp_r3->x4 = arg3;
        temp_r3->x2 = arg2;
        *arg4 = temp_r3;
        return (&temp_r3->x8);
    }
    return (s32**) arg4;
}

static u8 gm_8049E558[0x170];

void gm_801BFCFC(MinorScene* arg0)
{
    s32 var_r27_2;
    s32 var_r30;
    u32 var_r25;
    u32 var_r25_2;
    u32 var_r28_3;
    u32* temp_r29;
    u32* temp_r29_2;
    u8* var_r26;
    u8* var_r27;
    u8* var_r28;
    u8* var_r28_2;
    s32** temp_r3;
    s32** var_r31;

    var_r27 = gm_8049E558;
    gm_801A427C(arg0);
    var_r31 = NULL;
    gm_801736DC();
    var_r30 = 0;
    memzero(gm_8049E558, 0x42);
    memzero(&gm_8049E558[0x44], 0x125);
    un_803124BC();

    /// @remarks these for loops were converted from the do-whiles with very
    /// little scrutiny... take them with a grain of salt
    var_r28 = gm_8049E558;
    for (var_r25 = 0; (s32) var_r25 < 0x42; var_r25++) {
        if (gm_8017219C(var_r25) != 0) {
            temp_r3 = gm_801BFC60((s16) var_r25, var_r30, 0,
                                  *gmMainLib_8015D804((s32) var_r25),
                                  (void*) var_r31);
            *var_r28 = 1;
            var_r31 = temp_r3;
            var_r30 += 1;
        }
        var_r28 += 1;
    }

    var_r26 = &gm_8049E558[0x44];
    var_r28_2 = var_r26;
    for (var_r25_2 = 0; (s32) var_r25_2 < 0x125; var_r25_2++) {
        if (gmMainLib_8015DA1C(var_r25_2) != 0) {
            if (gmMainLib_8015DA90(var_r25_2) == 0) {
                temp_r29 = gmMainLib_8015D970((s32) var_r25_2);
                *temp_r29 = lbTime_8000AFBC();
                gmMainLib_8015DA40(var_r25_2);
                Trophy_SetUnlockState((s32) (s16) var_r25_2, 1);
            }
            *var_r28_2 = un_803048C0((s32) var_r25_2);
            var_r31 = gm_801BFC60(0x3E, var_r30, (s16) var_r25_2,
                                  *gmMainLib_8015D970((s32) var_r25_2),
                                  (void*) var_r31);
            var_r30 += 1;
        }
        var_r28_2 += 1;
    }

    gm_80173EEC();
    gm_80172898(0xFFFFU);

    for (var_r28_3 = 0; (s32) var_r28_3 < 0x42; var_r28_3++) {
        if (((u8) *var_r27 == 0) && (gm_8017219C(var_r28_3) != 0)) {
            var_r31 = gm_801BFC60((s16) var_r28_3, var_r30, 0,
                                  *gmMainLib_8015D804((s32) var_r28_3),
                                  (void*) var_r31);
            var_r30 += 1;
        }
        var_r27 += 1;
    }

    for (var_r27_2 = 0; var_r27_2 < 0x125; var_r27_2++) {
        if ((((s32) *var_r26 < un_803048C0(var_r27_2)) ||
             (un_803048C0(var_r27_2) == 0)) &&
            (gmMainLib_8015DA1C((u32) var_r27_2) != 0))
        {
            if (gmMainLib_8015DA90((u32) var_r27_2) == 0) {
                temp_r29_2 = gmMainLib_8015D970(var_r27_2);
                *temp_r29_2 = lbTime_8000AFBC();
                gmMainLib_8015DA40((u32) var_r27_2);
                Trophy_SetUnlockState((s32) (s16) var_r27_2, 1);
            }
            var_r31 =
                gm_801BFC60(0x3E, var_r30, (s16) var_r27_2,
                            *gmMainLib_8015D970(var_r27_2), (void*) var_r31);
            var_r30 += 1;
        }
        var_r26 += 1;
    }

    gm_80172174();
    gm_80174180();
    if (var_r31 != NULL) {
        *var_r31 = 0;
    }
    lb_8001C550();
    lb_8001D164(0);
    lb_8001CE00();
}

void gm_801BFF7C(MinorScene* arg0)
{
    gm_801A42E8((s8) gm_801736DC()->x5);
    gm_801A42D4();
}
