#include "gmresultplayer.h"

#include <placeholder.h>

#include "forward.h"
#include "gm_1601.h"
#include "gm_1798.h"
#include "gm_1A45.h"
#include "gm_unsplit.h"
#include "gmresult.h"
#include "gmresultplayer.static.h"
#include "types.h"
#include <melee/if/ifcoget.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbspdisplay.h>
#include <melee/mn/mnmain.h>
#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/tobj.h>
#include <sysdolphin/baselib/wobj.h>

extern ResultsData lbl_8046DBE8;

/* 3D6A08 */ u32 gmResultPlayerColors[4] = {
    0x013C59FF,
    0x064E01FF,
    0x54010BFF,
    0x408080FF,
};

/* 3D6A18 */ CharScaleEntry gmResultCharacterScaleData[] = {
    {
        { 0.2F, 0.0F, 2.8F, 0.0F, 10.0F, 13.5F, 24.0F, 7.0F },
        { 3.6F, 4.0F, 3.8F, 1.5F },
    },
    {
        { -3.0F, 0.0F, -0.8F, 0.0F, 12.0F, 11.0F, 12.0F, 1.0F },
        { 2.3F, 2.0F, 2.5F, 1.0F },
    },
    {
        { 3.5F, -3.0F, 1.0F, 0.0F, 17.0F, 16.0F, 18.0F, 5.0F },
        { 3.5F, 3.3F, 3.5F, 1.5F },
    },
    {
        { 2.5F, -7.0F, -2.0F, -0.5F, 3.5F, -4.5F, -7.0F, 3.0F },
        { 1.8F, 0.9F, 0.9F, 1.3F },
    },
    {
        { 0.0F, -1.0F, 0.0F, 0.0F, 0.0F, 7.0F, -4.0F, 1.5F },
        { 2.0F, 3.2F, 1.5F, 1.2F },
    },
    {
        { 0.0F, -8.0F, 5.0F, 0.0F, 20.0F, 10.0F, 13.0F, 1.0F },
        { 3.2F, 3.6F, 2.8F, 1.1F },
    },
    {
        { -1.0F, -4.5F, 3.0F, 1.0F, 22.0F, 22.0F, 23.0F, 6.0F },
        { 3.6F, 3.7F, 3.7F, 1.5F },
    },
    {
        { 11.0F, 2.0F, 0.0F, 0.0F, -3.0F, 11.0F, 13.5F, 5.0F },
        { 3.0F, 2.5F, 3.0F, 1.5F },
    },
    {
        { 0.0F, -3.0F, 0.0F, 0.1F, 12.5F, 10.0F, 15.0F, 4.0F },
        { 3.0F, 3.0F, 4.0F, 1.4F },
    },
    {
        { -2.0F, 0.0F, 3.0F, 0.0F, 20.0F, 23.0F, 23.0F, 7.0F },
        { 3.5F, 4.0F, 3.8F, 1.6F },
    },
    {
        { -1.0F, 4.0F, -1.0F, -0.6F, 12.0F, 13.5F, 23.0F, 3.5F },
        { 2.8F, 3.0F, 3.0F, 1.3F },
    },
    {
        { 0.0F, 0.0F, 0.0F, 0.0F, 7.0F, 4.0F, 6.0F, 4.0F },
        { 3.0F, 2.0F, 2.5F, 1.4F },
    },
    {
        { 0.0F, 0.0F, 0.0F, 0.0F, 18.0F, 18.0F, 20.0F, 7.0F },
        { 3.5F, 3.5F, 4.0F, 1.6F },
    },
    {
        { 0.0F, 2.0F, -8.0F, 0.0F, 0.0F, 9.0F, -4.0F, 1.5F },
        { 1.5F, 3.2F, 2.2F, 1.2F },
    },
    {
        { -8.0F, -9.0F, -5.0F, -2.0F, 10.0F, 6.5F, 0.8F, 2.0F },
        { 2.35F, 3.0F, 2.0F, 1.3F },
    },
    {
        { 0.0F, 0.0F, 0.0F, 0.0F, -2.0F, 0.0F, -7.0F, 0.0F },
        { 1.6F, 2.8F, 1.0F, 1.1F },
    },
    {
        { 0.0F, 1.0F, -2.0F, 0.0F, 18.0F, 12.5F, 25.0F, 6.5F },
        { 3.2F, 3.8F, 4.2F, 1.5F },
    },
    {
        { 3.0F, -1.0F, 2.5F, 0.1F, 13.0F, 9.5F, 13.0F, 2.8F },
        { 2.6F, 2.2F, 2.3F, 1.2F },
    },
    {
        { -1.0F, 1.0F, 0.0F, 0.2F, 23.5F, 22.0F, 23.0F, 8.0F },
        { 4.0F, 4.0F, 4.0F, 1.6F },
    },
    {
        { 1.0F, 0.0F, 1.0F, 0.0F, 20.0F, 25.0F, 16.0F, 7.0F },
        { 3.5F, 4.0F, 4.0F, 1.5F },
    },
    {
        { -11.0F, -9.0F, -3.0F, 0.5F, 9.0F, 7.0F, 24.0F, 5.0F },
        { 3.0F, 3.5F, 3.8F, 1.5F },
    },
    {
        { 1.0F, -5.5F, -0.5F, 1.0F, 18.0F, 19.0F, 20.0F, 6.5F },
        { 3.3F, 4.0F, 3.8F, 1.5F },
    },
    {
        { 0.0F, 0.5F, 0.0F, 0.2F, 10.0F, 13.0F, 14.0F, 5.0F },
        { 3.0F, 3.0F, 3.6F, 1.5F },
    },
    {
        { -15.0F, 3.5F, -0.3F, 0.0F, 15.0F, 23.0F, 22.0F, 5.5F },
        { 4.0F, 3.5F, 4.0F, 1.5F },
    },
    {
        { 0.0F, 2.0F, 0.0F, 0.0F, -3.0F, 1.0F, 1.0F, 0.5F },
        { 1.3F, 2.5F, 2.0F, 1.3F },
    },
    {
        { 0.5F, 0.0F, 0.0F, 0.0F, 19.0F, 27.0F, 25.0F, 7.5F },
        { 4.1F, 4.0F, 4.0F, 1.5F },
    },
    {
        { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F },
        { 1.0F, 1.0F, 1.0F, 1.0F },
    },
    {
        { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F },
        { 1.0F, 1.0F, 1.0F, 1.0F },
    },
    {
        { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F },
        { 1.0F, 1.0F, 1.0F, 1.0F },
    },
    {
        { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F },
        { 1.0F, 1.0F, 1.0F, 1.0F },
    },
    {
        { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F },
        { 1.0F, 1.0F, 1.0F, 1.0F },
    },
    {
        { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F },
        { 1.0F, 1.0F, 1.0F, 1.0F },
    },
};

/* 3D7018 */ u32 gmResultX22F4Init[0x20 / sizeof(u32)] = {
    0x00180000, 0x00000000, 0x00150015, 0x00000000,
    0x00120012, 0x00120000, 0x000E000E, 0x000E000E,
};

/* 3D7038 */ u32 gmResultScoreTableInit[0x20 / sizeof(u32)] = {
    0x00000000, 0x00000000, 0xFFF2000E, 0x00000000,
    0xFFEE0000, 0x00120000, 0xFFEAFFF9, 0x00070016,
};

/* 3D7058 */ ResultsCharacterData gmResultCharacterData = {
    {
        0.85F, 0.8F, 1.0F, 1.0F,  1.0F, 0.7F, 0.9F, 1.0F, 1.0F, 0.88F, 0.8F,
        1.0F,  0.9F, 1.0F, 0.9F,  1.0F, 0.9F, 0.9F, 0.9F, 0.9F, 1.0F,  1.0F,
        1.0F,  1.0F, 1.0F, 0.79F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    },
    {
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -3.5F, -4.0F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -3.0F, -2.3F, -1.5F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -3.3F, -3.5F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -2.7F, -2.0F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -2.4F, -1.5F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -2.4F, -1.2F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, -0.3F, -0.6F },
            { 0.0F, -2.7F, -3.1F, -3.5F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -2.9F, -3.2F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -2.7F, -2.7F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, -0.2F, -0.4F },
            { 0.0F, -2.7F, -3.1F, -3.5F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -2.7F, -2.7F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -2.7F, -2.7F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.3F, -2.9F, -3.5F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -2.7F, -2.0F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.4F, 0.9F },
            { 0.0F, -3.3F, -2.9F, -2.0F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -2.0F, -1.0F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -2.9F, -3.3F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -2.7F, -2.1F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -3.5F, -3.9F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -3.3F, -3.9F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.5F, -2.6F, -2.7F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, -0.1F, -0.3F, -0.6F },
            { 0.0F, -2.7F, -2.9F, -3.2F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -2.9F, -3.1F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, -0.2F, -0.4F, -0.5F },
            { 0.0F, -2.7F, -3.0F, -3.3F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -2.0F, -0.7F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -3.3F, -3.9F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -2.7F, -2.7F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -2.7F, -2.7F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -2.7F, -2.7F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -2.7F, -2.7F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -2.7F, -2.7F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
        {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, -2.7F, -2.7F, -2.7F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
        },
    },
    {
        { 0x17 }, { 0x29 }, { 0x27 }, { 0x2C }, { 0x05 }, { 0x17 }, { 0x28 },
        { 0x24 }, { 0x18 }, { 0x57 }, { 0x13 }, { 0x13 }, { 0x17 }, { 0x17 },
        { 0x17 }, { 0x17 }, { 0x17 }, { 0x17 }, { 0x17 }, { 0x17 }, { 0x17 },
        { 0x17 }, { 0x17 }, { 0x17 }, { 0x17 }, { 0x17 }, { 0x17 },
    },
    { 0 },
};

/* 3D78E8 */ HSD_WObjDesc gmResultCameraEyeDesc = { NULL,
                                                    { 0.0F, 0.0F, 62.0F },
                                                    NULL };
/* 3D78FC */ HSD_WObjDesc gmResultCameraInterestDesc = { NULL,
                                                         { 0.0F, 0.0F, 0.0F },
                                                         NULL };

/* 3D7910 */ HSD_CameraDescPerspective gmResultCameraDesc = {
    NULL,
    0,
    PROJ_PERSPECTIVE,
    { 0, 640, 0, 480 },
    { 0, 640, 0, 480 },
    &gmResultCameraEyeDesc,
    &gmResultCameraInterestDesc,
    0.0F,
    NULL,
    1.0F,
    5000.0F,
    19.999998F,
    1.216667F,
};

/* 3D7948 */ char gmResultMissingGObjMessage[] =
    "Error : model gobj dont't find at gmResultSetViewPos\n";
/* 3D7980 */ char gmResultSourceFileName[] = "gmresultplayer.c";
/* 3D7994 */ char gmResultMissingJObjMessage[] =
    "Error : model jobj dont't find at gmResultSetViewPos\n";

ResultsPlayerConfig const lbl_803B7B68 = {
    { 0.0F, 1.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, -100.0F },
    { 0.0F, 100.0F, 62.0F },
    { 0.0F, 100.0F, 0.0F },
    { { fn_80179DCC, fn_80179E34, fn_80179E9C, fn_80179F04 } },
    { 0.0F, 100.0F, 62.0F },
    { 0.0F, 100.0F, 0.0F },
    { { fn_80179D3C, fn_80179D60, fn_80179D84, fn_80179DA8 } },
    0.0F,
    0.0F,
    -100.0F,
    0.0F,
    0.0F,
    -100.0F,
    0.75F,
    0.48F,
    0.4F,
    0.307F,
    0.0F,
};

/// @todo .sdata2 order hack
void gm_80177724(struct ResultsMatchInfo* arg0)
{
#ifdef MUST_MATCH
    (void) 0.0;
    (void) S32_TO_F32;
    (void) 10.0f;
    (void) 40.0f;
    (void) 0.0f;
    (void) 1.0f;
    (void) 0.2f;
    (void) 0.3f;
    (void) 0.05f;
    (void) 50.0f;
    (void) 1.0;
    (void) 29.0f;
    (void) 30.0f;
    (void) 120.0f;
    (void) U32_TO_F32;
#endif
    memzero(arg0, sizeof(*arg0));
}

static inline void inline0(HSD_JObj* jobj, float f)
{
    HSD_ForeachAnim(jobj, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetRate,
                    AOBJ_ARG_AF, 0.0);
    HSD_ForeachAnim(jobj, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetCurrentFrame,
                    AOBJ_ARG_AF, f);
    HSD_JObjAnimAll(jobj);
}

void fn_80177748(void)
{
    MatchEnd* temp_r3;
    int i;
    CharacterKind ckind;
    int var_r24;

    ResultsData* data = &lbl_8046DBE8;

    temp_r3 = fn_80174274();

    for (i = 0; i < 4; i++) {
        if (temp_r3->player_standings[i].slot_type != Gm_PKind_NA) {
            ckind = temp_r3->player_standings[i].ckind;
            HSD_JObjClearFlagsAll(data->player_data[i].jobjs[0], JOBJ_HIDDEN);
            inline0(data->player_data[i].jobjs[0], gm_80168B34(ckind, 0, 0));
            HSD_JObjClearFlagsAll(data->player_data[i].jobjs[4], JOBJ_HIDDEN);
            if (gm_WasMatchCanceled(temp_r3->outcome) != 0) {
                var_r24 = 4;
            } else if (temp_r3->is_teams == 0) {
                if (temp_r3->player_standings[i].is_small_loser == 0) {
                    var_r24 = 5;
                } else {
                    var_r24 = temp_r3->player_standings[i].is_big_loser;
                }
            } else if (temp_r3->is_teams == 1) {
                if (data->x6 == i) {
                    var_r24 = 5;
                } else {
                    var_r24 =
                        temp_r3
                            ->team_standings[temp_r3->player_standings[i].team]
                            .is_big_loser;
                }
            }
            inline0(data->player_data[i].jobjs[4], var_r24);
        }
    }
}

void fn_80177920(HSD_GObj* gobj)
{
    MatchEnd* end;
    int human_controller_count;
    int i;

    ResultsData* data = &lbl_8046DBE8;

    PAD_STACK(8);

    end = fn_80174274();
    human_controller_count = 0;

    for (i = 0; i < 4; i++) {
        if (end->player_standings[i].slot_type == Gm_PKind_Human &&
            HSD_PadMasterStatus[(u8) i].err == 0)
        {
            human_controller_count++;
            if (HSD_PadCopyStatus[(u8) i].trigger != 0) {
                data->x1 = 3;
                break;
            }
        }
    }

    if (human_controller_count == 0) {
        for (i = 0; i < 4; i++) {
            if (HSD_PadMasterStatus[(u8) i].err == 0 &&
                HSD_PadCopyStatus[(u8) i].trigger != 0)
            {
                data->x1 = 3;
                break;
            }
        }
    }
    if (data->x1 == 3) {
        lb_8000BA0C(gobj->hsd_obj, 1.0F);
        fn_80177748();
    }
}

extern UNK_T lbl_803D6878[];

static inline bool pagePrev(int slot)
{
    ResultsData* data = &lbl_8046DBE8;
    if (data->player_data[slot].page != 0) {
        data->player_data[slot].page--;
        data->player_data[slot].scroll_offset = 0.0F;
        fn_80174380();
        return true;
    } else {
        return false;
    }
}

static inline bool pageNext(int slot)
{
    ResultsData* data = &lbl_8046DBE8;
    if (data->player_data[slot].page < data->num_pages - 1) {
        data->player_data[slot].page++;
        data->player_data[slot].scroll_offset = 0.0F;
        fn_80174380();
        return true;
    } else {
        return false;
    }
}

static const float scroll_speed = 0.2F;

static inline bool scrollDown(int slot, float amount)
{
    int scroll_max;
    // Preserve the original register move for the nested call.
    int arg = slot;
    ResultsData* data = &lbl_8046DBE8;
    amount *= scroll_speed;

    scroll_max =
        fn_80174A60(fn_801748EC(&lbl_803D6878, data->player_data[slot].page,
                                slot | arg),
                    slot) -
        10;
    if (data->player_data[slot].scroll_offset < scroll_max) {
        data->player_data[slot].scroll_offset += amount;
        if (data->player_data[slot].scroll_offset > scroll_max) {
            data->player_data[slot].scroll_offset = scroll_max;
        }
        return true;
    } else {
        return false;
    }
}

static inline bool scrollUp(int slot, float amount)
{
    ResultsData* data = &lbl_8046DBE8;
    amount *= scroll_speed;

    if (data->player_data[slot].scroll_offset > 0) {
        data->player_data[slot].scroll_offset -= amount;
        if (data->player_data[slot].scroll_offset < 0) {
            data->player_data[slot].scroll_offset = 0;
        }
        return true;
    } else {
        return false;
    }
}

/**
 * Handles result screen controller input for a given player slot.
 *
 * Pressing triggers moves to next/previous page, and moving the
 * stick up/down scrolls within the current page.
 *
 * @returns True if the input was handled and the screen needs updating;
 * false if nothing changed.
 */
bool fn_80177B7C(int slot)
{
    static const float scroll_deadzone = 0.3F;

    {
        float stick_y = HSD_PadCopyStatus[(u8) slot].nml_stickY;
        float abs_stick_y = stick_y;
        u32 trigger;
        bool result = false;
        PAD_STACK(16);

        *(u32*) &abs_stick_y &= ~0x80000000;
        if (abs_stick_y < scroll_deadzone) {
            stick_y = 0;
        }
        trigger = HSD_PadCopyStatus[(u8) slot].trigger;
        if (trigger & (PAD_BUTTON_B | PAD_STICK_LEFT)) {
            result = pagePrev(slot);
        } else if (trigger & (PAD_BUTTON_A | PAD_STICK_RIGHT)) {
            result = pageNext(slot);
        } else if (stick_y < 0) {
            result = scrollDown(slot, -stick_y);
        } else if (stick_y > 0) {
            result = scrollUp(slot, stick_y);
        }
        return result;
    }
}

bool fn_80177DD0(int slot)
{
    ResultsData* data;
    void* unk;
    int result;
    int scroll_max;

    data = &lbl_8046DBE8;
    unk = &lbl_803D6878;

    result = false;
    if (HSD_PadCopyStatus[slot].err == 0) {
        return fn_80177B7C(slot);
    }
    // The cast here is permuter slop.
    scroll_max =
        fn_80174A60(fn_801748EC(unk, data->player_data[slot].page, (u64) slot),
                    slot) -
        10;
    if (scroll_max < 0) {
        scroll_max = 0;
    }
    switch (data->player_data[slot].page) {
    case 0:
        if (data->player_data[slot].x2++ > 180) {
            data->player_data[slot].x2 = 0;
            data->player_data[slot].scroll_offset = 0.0F;
            data->player_data[slot].page = 1;
            result = true;
        } else {
            data->player_data[slot].scroll_offset += 0.05F;
            if (data->player_data[slot].scroll_offset > scroll_max) {
                data->player_data[slot].scroll_offset = scroll_max;
            } else {
                result = true;
            }
        }
        break;
    case 1:
        if (data->player_data[slot].x2++ > 1000) {
            if (data->player_data[slot].page < data->num_pages - 1) {
                data->player_data[slot].x2 = 0;
                data->player_data[slot].scroll_offset = 0.0F;
                data->player_data[slot].page = 2;
                result = true;
            } else {
                data->player_data[slot].x2--;
            }
        } else {
            data->player_data[slot].scroll_offset += 0.05F;
            if (data->player_data[slot].scroll_offset > scroll_max) {
                data->player_data[slot].scroll_offset = scroll_max;
            } else {
                result = true;
            }
        }
        break;
    case 2:
        if (data->player_data[slot].x2 < 1000) {
            data->player_data[slot].scroll_offset += 0.05F;
            if (data->player_data[slot].scroll_offset > scroll_max) {
                data->player_data[slot].scroll_offset = scroll_max;
            } else {
                result = true;
            }
            data->player_data[slot].x2++;
        }
        break;
    }
    return result;
}

static s32 lbl_804D3FC8 = 1;

void fn_80178050(HSD_GObj* arg0)
{
    s32 k2;
    HSD_JObj* jobj;
    ResultsData* data = &lbl_8046DBE8;
    MatchEnd* match_end;
    s32 var_r24;

    PAD_STACK(16);

    match_end = fn_80174274();
    jobj = arg0->hsd_obj;
    var_r24 = 0;

    if (lbGetJObjCurrFrame(jobj) >= 50.0f && !data->x0_23) {
        lb_8000BA0C(jobj, 0.0f);
        data->x0_23 = 1;
        lbl_804D3FC8 = 1;
        {
            s32 j;
            for (j = 0; j < 4; j++) {
                if (match_end->player_standings[j].slot_type == 0) {
                    lbl_804D3FC8 = 0;
                    break;
                }
            }
        }
        if (lbl_804D3FC8 != 0) {
            data->x3 = 0x14;
        } else {
            data->x3 = 0x0A;
        }
    }

    fn_80175D34();

    {
        u32 phase = data->x0_23;
        if (phase != 0) {
            if (phase == 1) {
                data->x0_23 = 2;
                {
                    s32 k = 0;
                    do {
                        switch ((s32) match_end->player_standings[k].slot_type)
                        {
                        case 2:
                            break;
                        case 3:
                            data->player_data[k].x0_0 = 1;
                            break;
                        case 0:
                            fn_80174B4C(data, k);
                            break;
                        case 1:
                            fn_80174B4C(data, k);
                            data->player_data[k].x0_0 = 1;
                            break;
                        }
                        k++;
                    } while (k < 4);
                }
            }

            {
                k2 = 0;
                do {
                    u8 slot = match_end->player_standings[k2].slot_type;
                    if (slot == 0) {
                        if (!data->player_data[k2].x0_0) {
                            if (fn_80177B7C(k2) != 0) {
                                fn_80174B4C(data, k2);
                            }
                            if ((HSD_PadCopyStatus[k2].err != 0) ||
                                (HSD_PadCopyStatus[(u8) k2].trigger &
                                 PAD_BUTTON_START))
                            {
                                data->player_data[k2].x0_0 = 1;
                                fn_80174920(&data->player_data[k2]);
                                lbDObjSetRateAll(
                                    HSD_JObjGetDObj(
                                        data->player_data[k2].jobjs[6]),
                                    1.0f);
                                lbDObjReqAnimAll(
                                    HSD_JObjGetDObj(
                                        data->player_data[k2].jobjs[6]),
                                    50.0f);
                                HSD_AObjSetRate(
                                    data->player_data[k2].jobjs[1]->aobj,
                                    1.0f);
                                HSD_AObjReqAnim(
                                    data->player_data[k2].jobjs[1]->aobj,
                                    50.0f);
                                HSD_JObjAnimAll(
                                    data->player_data[k2].jobjs[6]);
                                HSD_JObjAnimAll(
                                    data->player_data[k2].jobjs[1]);
                                HSD_JObjSetFlagsAll(
                                    data->player_data[k2].jobjs[0],
                                    JOBJ_HIDDEN);
                                HSD_JObjSetFlagsAll(
                                    data->player_data[k2].jobjs[4],
                                    JOBJ_HIDDEN);
                                data->player_data[k2].x0_1 = 0;
                                data->player_data[k2].x0_2 = 0;
                                data->player_data[k2].x0_3 = 0;
                                data->player_data[k2].x0_4 = 0;
                                fn_80174338();
                            }
                        } else if (HSD_PadCopyStatus[(u8) k2].trigger &
                                   PAD_BUTTON_START)
                        {
                            fn_80174920(&data->player_data[k2]);
                            data->player_data[k2].x0_0 = 0;
                            fn_80174B4C(data, k2);
                            lbDObjSetRateAll(
                                HSD_JObjGetDObj(
                                    data->player_data[k2].jobjs[6]),
                                0.0f);
                            lbDObjReqAnimAll(
                                HSD_JObjGetDObj(
                                    data->player_data[k2].jobjs[6]),
                                50.0f);
                            HSD_AObjSetRate(
                                data->player_data[k2].jobjs[1]->aobj, 0.0f);
                            HSD_AObjReqAnim(
                                data->player_data[k2].jobjs[1]->aobj, 50.0f);
                            HSD_JObjAnimAll(data->player_data[k2].jobjs[6]);
                            HSD_JObjAnimAll(data->player_data[k2].jobjs[1]);
                            HSD_JObjClearFlagsAll(
                                data->player_data[k2].jobjs[0], JOBJ_HIDDEN);
                            HSD_JObjClearFlagsAll(
                                data->player_data[k2].jobjs[4], JOBJ_HIDDEN);
                            fn_8017435C();
                        }
                    } else if (slot == 1) {
                        if (fn_80177DD0(k2) != 0) {
                            fn_80174B4C(data, k2);
                        }
                        if (lbl_804D3FC8 != 0) {
                            data->player_data[k2].x0_0 = 0;
                            if ((HSD_PadCopyStatus[k2].err == 0) &&
                                (HSD_PadCopyStatus[(u8) k2].trigger &
                                 PAD_BUTTON_START))
                            {
                                fn_80174338();
                                var_r24 = 1;
                            }
                        }
                    } else if (slot == 3) {
                        if ((lbl_804D3FC8 != 0) &&
                            (HSD_PadCopyStatus[k2].err == 0) &&
                            (HSD_PadCopyStatus[(u8) k2].trigger &
                             PAD_BUTTON_START))
                        {
                            fn_80174338();
                            var_r24 = 1;
                        }
                    }
                    k2++;
                } while (k2 < 4);
            }

            {
                s32 k3 = 0;
                do {
                    if (match_end->player_standings[k3].slot_type != 3) {
                        if (!data->player_data[k3].x0_1) {
                            HSD_JObjSetFlagsAll(data->player_data[k3].jobjs[8],
                                                JOBJ_HIDDEN);
                        } else {
                            HSD_JObjClearFlagsAll(
                                data->player_data[k3].jobjs[8], JOBJ_HIDDEN);
                        }
                        if (!data->player_data[k3].x0_2) {
                            HSD_JObjSetFlagsAll(data->player_data[k3].jobjs[9],
                                                JOBJ_HIDDEN);
                        } else {
                            HSD_JObjClearFlagsAll(
                                data->player_data[k3].jobjs[9], JOBJ_HIDDEN);
                        }
                        if (!data->player_data[k3].x0_3) {
                            HSD_JObjSetFlagsAll(
                                data->player_data[k3].jobjs[0xA], JOBJ_HIDDEN);
                        } else {
                            HSD_JObjClearFlagsAll(
                                data->player_data[k3].jobjs[0xA], JOBJ_HIDDEN);
                        }
                        if (!data->player_data[k3].x0_4) {
                            HSD_JObjSetFlagsAll(
                                data->player_data[k3].jobjs[0xB], JOBJ_HIDDEN);
                        } else {
                            HSD_JObjClearFlagsAll(
                                data->player_data[k3].jobjs[0xB], JOBJ_HIDDEN);
                        }
                    }
                    k3++;
                } while (k3 < 4);
            }

            {
                s32 all_done = 0;
                s32 i;
                for (i = 0; i < 4; i++) {
                    if (!data->player_data[i].x0_0) {
                        all_done = 1;
                        break;
                    }
                }
                if (all_done == 0) {
                    var_r24 = 1;
                }
                if (var_r24 != 0) {
                    data->x1 = 4;
                }
            }
        }
    }
}

void fn_801785B0(HSD_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    HSD_JObj* child;
    HSD_JObj* node;
    MatchEnd* match_end = fn_80174274();
    u8 mode = match_end->match_kind;
    int frame_val;
    f32 fv;

    if (mode == 2) {
        lb_80011E24(jobj, &child, 0x15, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0x11, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0x10, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0xC, -1);
        node = child;
        {
            s8 raw = fn_80174274()->xC;
            frame_val = ABS(raw);
        }
        fv = (f32) frame_val;
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetRate,
                        AOBJ_ARG_AF, 0.0f);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK,
                        HSD_AObjSetCurrentFrame, AOBJ_ARG_AF, fv);
        HSD_JObjAnimAll(node);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK,
                        HSD_AObjSetCurrentFrame, AOBJ_ARG_AF, 0.0f);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetRate,
                        AOBJ_ARG_AF, 1.0f);
        mn_8022F3D8(node, 1, TOBJ_MASK);
        return;
    } else if (mode == 1) {
        lb_80011E24(jobj, &child, 0x15, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0xC, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0x10, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0x11, -1);
        node = child;
        {
            s8 raw = fn_80174274()->xC;
            frame_val = ABS(raw);
        }
        fv = (f32) frame_val;
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetRate,
                        AOBJ_ARG_AF, 0.0f);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK,
                        HSD_AObjSetCurrentFrame, AOBJ_ARG_AF, fv);
        HSD_JObjAnimAll(node);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK,
                        HSD_AObjSetCurrentFrame, AOBJ_ARG_AF, 0.0f);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetRate,
                        AOBJ_ARG_AF, 1.0f);
        mn_8022F3D8(node, 1, TOBJ_MASK);
        return;
    } else if (mode == 3) {
        lb_80011E24(jobj, &child, 0x11, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0xC, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0x15, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0x10, -1);
        node = child;
        {
            s8 raw = fn_80174274()->xC;
            frame_val = ABS(raw);
        }
        fv = (f32) frame_val;
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetRate,
                        AOBJ_ARG_AF, 0.0f);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK,
                        HSD_AObjSetCurrentFrame, AOBJ_ARG_AF, fv);
        HSD_JObjAnimAll(node);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK,
                        HSD_AObjSetCurrentFrame, AOBJ_ARG_AF, 0.0f);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetRate,
                        AOBJ_ARG_AF, 1.0f);
        mn_8022F3D8(node, 1, TOBJ_MASK);
        return;
    } else {
        lb_80011E24(jobj, &child, 0x11, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0xC, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0x10, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0x15, -1);
        node = child;
        {
            s8 raw = fn_80174274()->xC;
            frame_val = ABS(raw);
        }
        fv = (f32) frame_val;
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetRate,
                        AOBJ_ARG_AF, 0.0f);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK,
                        HSD_AObjSetCurrentFrame, AOBJ_ARG_AF, fv);
        HSD_JObjAnimAll(node);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK,
                        HSD_AObjSetCurrentFrame, AOBJ_ARG_AF, 0.0f);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetRate,
                        AOBJ_ARG_AF, 1.0f);
        mn_8022F3D8(node, 1, TOBJ_MASK);
        return;
    }
}

static inline void fn_80178BB4_init_players(ResultsData* data,
                                            MatchEnd* match_end, int* i,
                                            int* ko_count)
{
    for (; *i < 6; (*i)++) {
        HSD_JObjSetFlagsAll(data->player_data[(*i)].jobjs[0], JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(data->player_data[(*i)].jobjs[4], JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(data->player_data[(*i)].jobjs[8], JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(data->player_data[(*i)].jobjs[9], JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(data->player_data[(*i)].jobjs[10], JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(data->player_data[(*i)].jobjs[11], JOBJ_HIDDEN);
        lbDObjSetRateAll(HSD_JObjGetDObj(data->player_data[(*i)].jobjs[6]),
                         0.0f);

        {
            u8 slot_type = match_end->player_standings[(*i)].slot_type;

            if (slot_type == 0) {
                (*ko_count) += match_end->player_standings[(*i)].xE;
            }

            if (slot_type != 3) {
                int cid;
                int ckind;
                u8 is_big_loser;
                ckind = match_end->player_standings[(*i)].ckind;
                cid = match_end->player_standings[(*i)].ftkind;
                is_big_loser = match_end->player_standings[(*i)].is_big_loser;

                if (gm_WasMatchCanceled(match_end->outcome) == 0 &&
                    match_end->is_teams == 0 && (s32) is_big_loser == 0)
                {
                    ResultsData* d2 = &lbl_8046DBE8;
                    int tex_id =
                        (int) gm_80168B34((CharacterKind) ckind, cid, 0);
                    HSD_TObj* tobj = d2->x30->u.dobj->next->mobj->tobj;
                    HSD_AObj* aobj = tobj->aobj;
                    HSD_TObjReqAnim(tobj, (f32) tex_id);
                    HSD_TObjAnim(d2->x30->u.dobj->next->mobj->tobj);
                    if (tex_id < 0x19) {
                        HSD_AObjSetCurrentFrame(aobj, 0.0f);
                        HSD_AObjSetEndFrame(aobj, 29.0f);
                    } else {
                        int start = (int) (30.0f * (f32) (tex_id - 0xB4));
                        HSD_AObjSetCurrentFrame(aobj, (f32) start);
                        HSD_AObjSetEndFrame(aobj,
                                            (30.0f + (f32) start) - 1.0f);
                    }
                    mn_8022F3D8(d2->x30, 1, TOBJ_MASK);
                }

                fn_80174FD0(data->player_data[(*i)].jobjs[5],
                            (s32) gm_80168B34((CharacterKind) ckind, cid, 0));

                {
                    u32 rank_val;
                    HSD_AObj* rank_aobj;
                    rank_val = gm_80160854(
                        (*i), match_end->player_standings[(*i)].team,
                        (u8) (match_end->is_teams == 1),
                        match_end->player_standings[(*i)].slot_type);
                    rank_aobj =
                        data->player_data[(*i)].jobjs[2]->u.dobj->mobj->aobj;
                    HSD_AObjSetCurrentFrame(rank_aobj,
                                            1.0f + (f32) (u8) rank_val);
                    HSD_AObjSetRate(rank_aobj, 0.0f);
                }

                if (match_end->match_kind != 3) {
                    f32 taunt_frame = gm_80168B34(
                        (CharacterKind) (s8) (u8) match_end
                            ->player_standings[(*i)]
                            .ckind,
                        (int) (s8) (u8) match_end->player_standings[(*i)]
                            .ftkind,
                        match_end->player_standings[(*i)].x3);
                    HSD_JObj* taunt_jobj = data->player_data[(*i)].jobjs[7];
                    HSD_ForeachAnim(taunt_jobj, JOBJ_TYPE, ALL_TYPE_MASK,
                                    HSD_AObjSetRate, AOBJ_ARG_AF, 0.0);
                    HSD_ForeachAnim(taunt_jobj, JOBJ_TYPE, ALL_TYPE_MASK,
                                    HSD_AObjSetCurrentFrame, AOBJ_ARG_AF,
                                    taunt_frame);
                    HSD_JObjAnimAll(taunt_jobj);
                    HSD_AObjSetRate(data->player_data[(*i)].jobjs[7]->aobj,
                                    1.0f);
                    HSD_AObjSetCurrentFrame(
                        data->player_data[(*i)].jobjs[7]->aobj, 0.0f);
                } else {
                    HSD_JObj* taunt_jobj = data->player_data[(*i)].jobjs[7];
                    HSD_ForeachAnim(taunt_jobj, JOBJ_TYPE, ALL_TYPE_MASK,
                                    HSD_AObjSetRate, AOBJ_ARG_AF, 0.0);
                    HSD_ForeachAnim(taunt_jobj, JOBJ_TYPE, ALL_TYPE_MASK,
                                    HSD_AObjSetCurrentFrame, AOBJ_ARG_AF, 0.0);
                    HSD_JObjAnimAll(taunt_jobj);
                    HSD_JObjSetFlagsAll(data->player_data[(*i)].jobjs[7],
                                        JOBJ_HIDDEN);
                }

                HSD_JObjRemoveAnimAll(data->player_data[(*i)].jobjs[3]);
                HSD_JObjSetFlagsAll(data->player_data[(*i)].jobjs[3],
                                    JOBJ_HIDDEN);
            } else {
                HSD_JObjSetFlagsAll(data->player_data[(*i)].jobjs[1],
                                    JOBJ_HIDDEN);
                HSD_JObjRemoveAnimAll(data->player_data[(*i)].jobjs[1]);
                HSD_JObjSetFlagsAll(data->player_data[(*i)].jobjs[5],
                                    JOBJ_HIDDEN);
                HSD_JObjSetFlagsAll(data->player_data[(*i)].jobjs[7],
                                    JOBJ_HIDDEN);
            }
        }
    }
}

void fn_80178BB4(HSD_GObj* gobj)
{
    ResultsData* data = &lbl_8046DBE8;
    MatchEnd* match_end = fn_80174274();
    int ko_count = 0;
    int i;

    fn_80179854();
    fn_80175DC8(gobj);
    fn_80175C5C();

    if (gm_WasMatchCanceled(match_end->outcome) != 0) {
        int anim_n = 0xB8;
        HSD_TObj* tobj = data->x30->u.dobj->next->mobj->tobj;
        HSD_AObj* aobj = tobj->aobj;
        int start;
        HSD_TObjReqAnim(tobj, (f32) anim_n);
        HSD_TObjAnim(data->x30->u.dobj->next->mobj->tobj);
        start = (int) (30.0f * (f32) (anim_n - 0xB4));
        HSD_AObjSetCurrentFrame(aobj, (f32) start);
        HSD_AObjSetEndFrame(aobj, (30.0f + (f32) start) - 1.0f);
        mn_8022F3D8(data->x30, 1, TOBJ_MASK);
    } else if (match_end->is_teams == 1) {
        int tex_id = data->x5 + 0xB5;
        HSD_TObj* tobj = data->x30->u.dobj->next->mobj->tobj;
        HSD_AObj* aobj = tobj->aobj;
        HSD_TObjReqAnim(tobj, (f32) tex_id);
        HSD_TObjAnim(data->x30->u.dobj->next->mobj->tobj);
        if (tex_id < 0x19) {
            HSD_AObjSetCurrentFrame(aobj, 0.0f);
            HSD_AObjSetEndFrame(aobj, 29.0f);
        } else {
            int start = (int) (30.0f * (f32) (tex_id - 0xB4));
            HSD_AObjSetCurrentFrame(aobj, (f32) start);
            HSD_AObjSetEndFrame(aobj, (30.0f + (f32) start) - 1.0f);
        }
        mn_8022F3D8(data->x30, 1, TOBJ_MASK);
    }

    i = 0;
    fn_80178BB4_init_players(data, match_end, &i, &ko_count);

    if (ko_count > 0) {
        un_802FF128(0x6C, 0x78, ko_count, 5);
    }

    data->x1 = 1;
}

bool fn_801791E4(void)
{
    ResultsData* data = &lbl_8046DBE8;
    MatchEnd* end = fn_80174274();
    int i;

    PAD_STACK(8);

    if (gm_WasMatchCanceled(end->outcome) != 0) {
        for (i = 0; i < 4; i++) {
            if (end->player_standings[i].slot_type == Gm_PKind_Human &&
                HSD_PadMasterStatus[(u8) i].err == 0 &&
                (HSD_PadCopyStatus[(u8) i].trigger & PAD_BUTTON_START))
            {
                return true;
            }
        }
    }

    if ((u32) data->x8 == 0xA0U) {
        return true;
    }
    return false;
}

static inline int fn_80179350_inline(void)
{
    return fn_801791E4();
}

static inline void fn_80179350_update(ResultsData* data, MatchEnd* match_end,
                                      HSD_GObj* arg0)
{
    PAD_STACK(8);

    if ((u32) data->x8 == 0 && data->x0_4) {
        gm_801A4634(0);
    }

    if ((u32) data->x8 == 0xA2) {
        if (gm_WasMatchCanceled(match_end->outcome) == 0) {
            lbAudioAx_800237A8(0xB5, 0x7F, 0x40);
        }
    } else if ((u32) data->x8 == 0x2) {
        if (gm_WasMatchCanceled(match_end->outcome) == 0) {
            lbAudioAx_800237A8(0xC355, 0x7F, 0x40);
            lbAudioAx_800237A8(0x144, 0x7F, 0x40);
        } else {
            lbAudioAx_800237A8(0x148, 0x7F, 0x40);
        }
    } else if ((u32) data->x8 == 0x9A) {
        if (gm_WasMatchCanceled(match_end->outcome) != 0) {
            lbAudioAx_800237A8(0xC350, 0x7F, 0x40);
        } else {
            fn_80168E54(match_end->player_standings[data->x6].ckind,
                        match_end->player_standings[data->x6].ftkind,
                        match_end->player_standings[data->x6].team,
                        (match_end->is_teams == 1));
        }
    }

    if (data->x1 < 1) {
        if (fn_80179350_inline() != 0) {
            fn_80178BB4(arg0);
        }
    } else {
        HSD_JObjAnimAll((HSD_JObj*) arg0->hsd_obj);
        switch (data->x1) {
        case 1: {
            ResultsData* d = &lbl_8046DBE8;
            HSD_JObj* jobj = (HSD_JObj*) arg0->hsd_obj;
            float frame = lbGetJObjCurrFrame(jobj);
            if (frame >= 10.0f && !d->x0_1) {
                fn_80177748();
                d->x0_1 = 1;
            }
            if (frame >= 40.0f) {
                lb_8000BA0C(jobj, 0.0f);
                d->x1 = 2;
            }
            break;
        }
        case 2:
            fn_80177920(arg0);
            break;
        case 3:
            fn_80178050(arg0);
            break;
        case 4:
            if (data->x3 != 0) {
                data->x3 = (char) (data->x3 - 1);
            } else {
                gm_801A4B60();
            }
            break;
        }
    }
}
void fn_80179350(HSD_GObj* arg0)
{
    ResultsData* data = &lbl_8046DBE8;
    MatchEnd* match_end;
    int i;
    PAD_STACK(8);
    match_end = fn_80174274();
    for (i = 0; i < 6; i++) {
        if (data->player_data[i].jobjs[12] != NULL) {
            lb_8000B1CC(data->player_data[i].jobjs[12], NULL,
                        &data->player_data[i].stats_position);
        }
    }
    fn_80179350_update(data, match_end, arg0);

    if ((u32) data->x8 < (u32) -1) {
        data->x8++;
    }
}

int fn_801795D4(void)
{
    MatchEnd* match_end = &lbl_8046E3AC.match_end;
    int count = 0;
    int i;

    for (i = 0; i < 4; i++) {
        int lookup;

        if (match_end->is_teams == 0) {
            lookup = match_end->player_standings[i].is_big_loser;
        } else {
            int idx = match_end->player_standings[i].team;
            lookup = match_end->team_standings[idx].is_big_loser;
        }

        if (match_end->player_standings[i].slot_type != 3 && lookup == 0) {
            count++;
        }
    }

    if (count != 0) {
        return count - 1;
    }
    return count;
}

int fn_801796F0(int arg0)
{
    MatchEnd* match_end = &lbl_8046E3AC.match_end;
    int i;
    int count = 0;

    for (i = 0; i < 4; i++) {
        int lookup;

        if (match_end->is_teams == 0) {
            lookup = match_end->player_standings[i].is_big_loser;
        } else {
            int idx = match_end->player_standings[i].team;
            lookup = match_end->team_standings[idx].is_big_loser;
        }

        if (match_end->player_standings[i].slot_type != 3 && lookup == 0) {
            if (arg0 == i) {
                return count;
            }
            count++;
        }
    }

    return count;
}
