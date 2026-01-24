#include "gmallstar.h"
#include "gm/gmallstar.static.h"

#include "gm_unsplit.h"
#include "baselib/random.h"
#include "gr/ground.h"

#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lbdvd.h>

extern CSSData gm_80470708;
extern DebugGameOverData gm_80470850;
extern MatchExitInfo gm_8047086C;
extern StartMeleeData gm_80472AF8;

MinorScene gm_803DE930_MinorScenes[] = {
    {
        0,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        1,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        8,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        9,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x10,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x11,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x18,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x19,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x20,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x21,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x28,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x29,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x30,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x31,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x38,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x39,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x40,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x41,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x48,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x49,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x50,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x51,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x58,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x59,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x60,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x68,
        3,
        0,
        NULL,
        gm_801B607C,
        {
            MN_COMING_SOON,
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
            MN_GAMEOVER,
            &gm_80470850,
            &gm_80470850,
        },
    },
    {
        0x70,
        3,
        0,
        gm_801B5F50,
        gm_801B5FB4,
        {
            MN_CSS,
            &gm_80470708,
            &gm_80470708,
        },
    },
    {
        -1,
    },
};

/// #gm_801B5324

/// #gm_801B5624

/// #gm_801B59AC

void fn_801B5AA8(int arg0)
{
    lbBgFlash_8002063C(0x78);
}

/// #gm_801B5ACC

void gm_801B5E7C(MinorScene* arg0)
{
    MatchExitInfo* exit = gm_801A4284(arg0);
    gm_80473A18.x74 = exit->match_end.player_standings[0].percent;
    gm_8017D7AC(exit, &gm_80473A18.x0, 0x69);
}

void gm_801B5EB4(MinorScene* arg0)
{
    DebugGameOverData* data = gm_801A427C(arg0);
    gm_8017C9A8(data, &gm_80473A18.x0, 2);
}

void gm_801B5EE4(MinorScene* arg0)
{
    DebugGameOverData* data = gm_801A4284(arg0);
    UnkAllstarData* r30 = &gm_80473A18;
    gm_8017CA38(data, &r30->x0, gmMainLib_8015CDE0(), 2);
    if (data->xC != 0) {
        r30->x74 = 0;
    }
}

void gm_801B5F50(MinorScene* arg0)
{
    CSSData* temp_r31;
    struct gmm_x0_528_t* temp_r3;

    temp_r31 = gm_801A427C(arg0);
    temp_r3 = gmMainLib_8015CDE0();
    gm_801B06B0(temp_r31, 0xD, temp_r3->c_kind, temp_r3->stocks,
                temp_r3->color, temp_r3->x4, temp_r3->cpu_level,
                gm_80473A18.x0.slot);
    lbDvd_800174BC();
}

/// #gm_801B5F50

void gm_801B5FB4(MinorScene* arg0)
{
    CSSData* temp_r31 = gm_801A4284(arg0);
    struct gmm_x0_528_t* temp_r30 = gmMainLib_8015CDE0();
    UnkAllstarData* r29 = &gm_80473A18;

    if (temp_r31->pending_scene_change == 2) {
        gm_801A42F8(MJ_MENU);
        return;
    }
    gm_801B0730(temp_r31, &temp_r30->c_kind, &temp_r30->stocks,
                &temp_r30->color, &temp_r30->x4, &temp_r30->cpu_level);
    r29->x0.ckind = temp_r30->c_kind;
    r29->x0.color = temp_r30->color;
    r29->x0.cpu_level = temp_r30->cpu_level;
    r29->x0.stocks = temp_r30->stocks;
    r29->x0.x4 = temp_r30->x4;
    gm_SetScenePendingMinor((temp_r30->x5 * 8) & 0xF8);
    gm_80168F88();
    gm_801B5324(r29, temp_r30->x5);
}

void gm_801B607C(MinorScene* unused)
{
    gm_801A42E8(MJ_MENU);
    gm_801A42D4();
}

void gm_801B60A4_OnLoad(void)
{
    UnkAllstarData* data;
    gm_803DEBE8_t* var_r30;
    gm_803DEBE8_t* var_r29;
    u32 var_r28;
    int temp;
    PAD_STACK(8);

    data = &gm_80473A18;
    gmMainLib_8015CDE0();
    gm_8017C984(data);

    {
        gm_80490940_t* p = gm_80490940;
        char* pp = (char*)p;
        int i = 25;
        while(i--) {
            *(pp++) = 0;
        }
    }

    gm_8017DB58(data->x0.xC.x24);
    data->x0.slot = gm_801677F0();
    data->x48 = gm_8018A160;
    data->x4C = gm_8018A228;
    data->x50 = gm_8018A290;
    data->x54 = gm_8018A25C;
    data->x58 = 0;
    data->x64 = gm_8018A2C4;
    var_r29 = gm_803DEBE8;
    data->x68 = gm_8018A314;
    var_r30 = var_r29;
    for (var_r28 = 0; var_r28 < 25; var_r28++) {
        var_r30->x2 = *((&var_r30->x0) + HSD_Randi(2));
        var_r30++;
    }

    var_r30 = gm_803DEBE8;
    for (var_r28 = 0; var_r28 < 0x17; var_r28++) {
        gm_803DEBE8_t* swap = &var_r30[var_r28 + HSD_Randi(0x18 - var_r28)];
        gm_803DEBE8_t tmp = *var_r29;
        *var_r29 = *swap;
        var_r29++;
        *swap = tmp;
    }

    data->x74 = 0;
    {
        UnkAllstarData* p = &gm_80473A18;
        int i = 0x18;
        p->x9C = 0;
        temp = 0x21;
        p->x76[0] = temp;
        p->x76[1] = temp;
        p->x76[2] = temp;
        p->x76[3] = temp;
        p->x76[4] = temp;
        p->x76[5] = temp;
        p->x76[6] = temp;
        p->x76[7] = temp;
        p->x76[8] = temp;
        p->x76[9] = temp;
        p->x76[0xA] = temp;
        p->x76[0xB] = temp;
        p->x76[0xC] = temp;
        p->x76[0xD] = temp;
        p->x76[0xE] = temp;
        p->x76[0xF] = temp;
        p->x76[0x10] = temp;
        p->x76[0x11] = temp;
        p->x76[0x12] = temp;
        p->x76[0x13] = temp;
        p->x76[0x14] = temp;
        p->x76[0x15] = temp;
        p->x76[0x16] = temp;
        p->x76[0x17] = temp;

        temp = 0x1A;
        if (i < temp) {
            u8* q = ((u8*)p) + i;
            i = temp - i;
            do {
                *(q++ + 0x76) = temp;
            } while (--i != 0);
        }
    }

    {
        u8* p = gm_80473A18.x90;
        gm_80473A18.x90[0] = 1;
        p[1] = 1;
        p[2] = 1;
        p[3] = 1;
    }

    gm_SetSceneMinor(0x70U);
    gm_80172174();
    Ground_801C5A28();
}

void gm_801B62D8_OnInit(void)
{
    struct gmm_x0_528_t* temp_r3 = gmMainLib_8015CDE0();
    temp_r3->c_kind = CHKIND_NONE;
    temp_r3->color = 0;
    temp_r3->stocks = 1;
    temp_r3->cpu_level = 0;
    temp_r3->x4 = 0x78;
    temp_r3->x5 = 0;
}
