#include "tydisplay.h"

#include "gm/gm_1A3F.h"
#include "gm/gm_1A45.h"
#include "if/textdraw.h"
#include "if/textlib.h"
#include "lb/lblanguage.h"
#include "ty/toy.h"
#include "ty/tyfigupon.h"
#include "ty/tylist.h"
#include "ty/types.h"

#include <baselib/archive.h>
#include <baselib/debug.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/random.h>

#include <dolphin/os.h>

#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"

extern char un_804D5AC0[2];
extern DevText* un_804D6F24;
extern s32 un_804A2DE8[];
extern char un_804A2D98[0x38];

typedef struct TyDspBgData {
    /* 0x00 */ HSD_GObj* gobj0;
    /* 0x04 */ HSD_GObj* gobj4;
    /* 0x08 */ u8 pad8[4];
    /* 0x0C */ HSD_JObj* jobj;
    /* 0x10 */ u8 pad10[0x3C];
    /* 0x4C */ HSD_Archive* archive;
} TyDspBgData;

extern TyDspBgData* un_804D6F1C;
extern s32 un_804D6F20;
extern HSD_GObj** un_804D6F18;
extern HSD_GObj* un_804D6F2C;
extern u8 un_804A2DD0[0x18];

/// #un_803181BC

void un_803182D4_OnFrame(void)
{
    TyModeState* state = (TyModeState*) un_804A284C;

    if (state->x4 != 0) {
        un_803181BC();
        gm_801A4B60();
    }
}

/// #un_8031830C

/// #un_80318714

/// #un_80318B1C

/// #un_80318CB4

/// #un_80319540

/// #un_80319994

/// #un_80319EF0

/// #fn_8031A4EC

/// #fn_8031A94C

/// #un_8031B1FC

static char un_804D5AA8[] = "0";
static u16 un_804D5ABC = 0x15;

void un_8031B1FC(void)
{
    TyDspBgData* ptr = un_804D6F1C;
    HSD_GObj* gobj;
    HSD_Joint* joint;
    HSD_JObj* jobj;


    if (ptr->archive == NULL) {
        OSReport("*** BG data aren't being loaded!\n");
        __assert("tydisplay.c", 0x3FD, un_804D5AA8);
    }

    gobj = ptr->gobj0;
    if (gobj != NULL) {
        HSD_GObjPLink_80390228(gobj);
        ptr->gobj0 = NULL;
    }

    gobj = ptr->gobj4;
    if (gobj != NULL) {
        HSD_GObjPLink_80390228(gobj);
        ptr->gobj4 = NULL;
    }

    joint = HSD_ArchiveGetPublicAddress(ptr->archive,
                                        "ToyDspBg_Top_joint");
    if (joint != NULL) {
        ptr->gobj4 = GObj_Create(9, 9, 0);
        jobj = HSD_JObjLoadJoint(joint);
        HSD_GObjObject_80390A70(ptr->gobj4, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(ptr->gobj4, HSD_GObj_JObjCallback, 0x3C, 0);
        lb_8001204C(jobj, &ptr->jobj, &un_804D5ABC, 1);
        return;
    }

    OSReport("*** Can not Load Panel Label(%s)\n",
             "ToyDspBg_Top_joint");
    __assert("tydisplay.c", 0x43E, un_804D5AA8);
}

/// #un_8031B328

static s32 un_804DE018 = (s32) 0xC8C8C8FF;

void un_8031B328(void)
{
    TyDspBgData* ptr = un_804D6F1C;
    u8* scene = un_804D6ED4;
    HSD_LObj* lobj;
    void* lightData;
    HSD_FogDesc* fogDesc;

    PAD_STACK(24);






    if (ptr->archive == NULL) {
        OSReport("*** BG data aren't being loaded!\n");
        OSPanic("tydisplay.c", 0x459, un_804D5AC0);
    }

    lightData = HSD_ArchiveGetPublicAddress(ptr->archive,
                                            "ScMenDisplay_scene_lights");
    if (lightData != NULL) {
        *(HSD_GObj**)(scene + 0x00) = GObj_Create(2, 3, 0);
        lobj = un_80306EEC(lightData, 0);
        HSD_GObjObject_80390A70(*(HSD_GObj**)(scene + 0x00),
                                HSD_GObj_804D784A, lobj);
        GObj_SetupGXLink(*(HSD_GObj**)(scene + 0x00),
                         HSD_GObj_LObjCallback, 0x34, 0);
    }

    if (un_804D6F20 != 0) {
        HSD_LObjSetColor(lobj, *(GXColor*) &un_804DE018);
    }

    fogDesc = HSD_ArchiveGetPublicAddress(ptr->archive,
                                          "ScMenDisplay_fog");
    if (fogDesc != NULL) {
        *(HSD_GObj**)(scene + 0x08) = GObj_Create(3, 4, 0);
        HSD_GObjObject_80390A70(*(HSD_GObj**)(scene + 0x08),
                                HSD_GObj_804D7848,
                                HSD_FogLoadDesc(fogDesc));
        GObj_SetupGXLink(*(HSD_GObj**)(scene + 0x08),
                         un_80306930, 0x35, 0);
    }
}

/// #un_8031B460_OnEnter

/// #un_8031B850

void un_8031B850(void)
{
    ToyAnimState* anim = &un_804A2AA8;
    TyDspBgData* ptr = un_804D6F1C;
    HSD_GObj** pgobj = un_804D6F18;
    u8* scene = un_804D6ED4;
    HSD_GObj* gobj;

    if (ptr->archive != NULL) {
        ptr->archive = NULL;
    }

    if (un_804D6EC8 != NULL) {
        un_804D6EC8 = NULL;
    }

    if (anim->gobj != NULL) {
        anim->gobj = NULL;
        anim->jobj[1] = NULL;
        anim->jobj[0] = NULL;
    }

    if (ptr->gobj0 != NULL) {
        ptr->gobj0 = NULL;
    }

    if (ptr->gobj4 != NULL) {
        ptr->gobj4 = NULL;
    }

    if (*(HSD_GObj**)(scene + 0x00) != NULL) {
        *(HSD_GObj**)(scene + 0x00) = NULL;
    }

    if (*(HSD_GObj**)(scene + 0x04) != NULL) {
        *(HSD_GObj**)(scene + 0x04) = NULL;
    }

    if (*(HSD_GObj**)(scene + 0x08) != NULL) {
        *(HSD_GObj**)(scene + 0x08) = NULL;
    }

    gobj = *pgobj;
    if (gobj != NULL) {
        HSD_GObjProc_8038FED4(gobj);
        *pgobj = NULL;
    }

    if (un_804D6F2C != NULL) {
        if (*(HSD_Archive**)(un_804A2DD0 + 0x14) != NULL) {
            lbArchive_80016EFC(*(HSD_Archive**)(un_804A2DD0 + 0x14));
            *(HSD_Archive**)(un_804A2DD0 + 0x14) = NULL;
        }
        HSD_GObjPLink_80390228(un_804D6F2C);
        un_804D6F2C = NULL;
    }

    if (un_804D6F24 != NULL) {
        DevText_Remove(&un_804D6F24);
        un_804D6F24 = NULL;
    }
}

void un_8031B9A4_OnFrame(void)
{
    TyModeState* state = (TyModeState*) un_804A284C;

    if (state->x4 != 0) {
        un_8031B850();
        gm_801A4B60();
    }
}

void* un_8031B9DC(s32 id)
{
    s32* p;
    s32 val;
    bool found = false;

    if (lbLang_IsSettingUS()) {
        p = un_804D6EAC;
        while (val = *p, val != -1) {
            if (val == id) {
                found = true;
                break;
            }
            p = (s32*) ((u8*) p + 0x10);
        }
    }

    if (!found) {
        p = un_804D6EB0;
        while (val = *p, val != -1) {
            if (val == id) {
                break;
            }
            p = (s32*) ((u8*) p + 0x10);
        }
    }

    return p;
}

static char un_803FF19C[] = "X  %3.2f\nZ  %3.2f";
static f32 un_804DE020 = 12.0f;
static s32 un_804DE024 = (s32) 0xE2E2E2FF;
static s32 un_804DE028 = (s32) 0x4080D060;
static f32 un_804DE02C = 18.0f;
static f64 un_804DE030 = 0.0;

/// #un_8031BA78
void un_8031BA78(s32 arg0, s32 arg1, f32 farg0)
{
    char buf[24];
    u8* data;

    data = (u8*) un_8031B9DC(arg0);
    switch (arg1) {
    case 1:
        break;
    case 0:
        *(f32*) (data + 8) = farg0;
        break;
    case 2:
        *(f32*) (data + 0xC) = farg0;
        break;
    }
    if (un_804D6F24 != NULL) {
        DevText_Erase(un_804D6F24);
        DevText_SetCursorXY(un_804D6F24, 0, 0);
        sprintf(buf, un_803FF19C, *(f32*) (data + 8),
                *(f32*) (data + 0xC));
        DevText_Print(un_804D6F24, buf);
    }
}

s32 un_8031BB34(s8 idx)
{
    char* table[] = {
        "ToyDspQues_Top_joint",       "ToyDspMycharaCmA_Top_joint",
        "ToyDspMycharaCmB_Top_joint", "ToyDspMycharaCmC_Top_joint",
        "ToyDspMycharaCmD_Top_joint", "ToyDspMycharaCmE_Top_joint",
        "ToyDspMycharaR1A_Top_joint", "ToyDspMycharaR1B_Top_joint",
        "ToyDspMycharaR1C_Top_joint", "ToyDspMycharaR1D_Top_joint",
        "ToyDspMycharaR1E_Top_joint", "ToyDspMycharaR2A_Top_joint",
        "ToyDspMycharaR2B_Top_joint", "ToyDspMycharaR2C_Top_joint",
        "ToyDspMycharaR2D_Top_joint", "ToyDspMycharaR2E_Top_joint",
        "ToyDspMapA_Top_joint",       "ToyDspMapB_Top_joint",
        "ToyDspMapC_Top_joint",       "ToyDspMapD_Top_joint",
        "ToyDspMapE_Top_joint",       "ToyDspFgseriesA_Top_joint",
        "ToyDspFgseriesB_Top_joint",  "ToyDspFgseriesC_Top_joint",
        "ToyDspFgseriesD_Top_joint",  "ToyDspFgseriesE_Top_joint",
        "ToyDspFgetcA_Top_joint",     "ToyDspFgetcB_Top_joint",
        "ToyDspFgetcC_Top_joint",     "ToyDspFgetcD_Top_joint",
        "ToyDspFgetcE_Top_joint",     "ToyDspPokemonA_Top_joint",
        "ToyDspPokemonB_Top_joint",   "ToyDspPokemonC_Top_joint",
        "ToyDspPokemonD_Top_joint",   "ToyDspPokemonE_Top_joint",
        "ToyDspItemA_Top_joint",      "ToyDspItemB_Top_joint",
        "ToyDspItemC_Top_joint",      "ToyDspItemD_Top_joint",
        "ToyDspItemE_Top_joint",      "ToyDspStand_Top_joint",
        "ToyDspQues_Top_joint",
    };

    if (idx == -1) {
        idx = 0;
    }

    return (s32) table[idx];
}

char* un_8031BB94(s8 idx)
{
    char* table[] = {
        un_804D5AC0,
        "ToyDspMycharaCmA_Top_matanim_joint",
        "ToyDspMycharaCmB_Top_matanim_joint",
        "ToyDspMycharaCmC_Top_matanim_joint",
        "ToyDspMycharaCmD_Top_matanim_joint",
        "ToyDspMycharaCmE_Top_matanim_joint",
        "ToyDspMycharaR1A_Top_matanim_joint",
        "ToyDspMycharaR1B_Top_matanim_joint",
        "ToyDspMycharaR1C_Top_matanim_joint",
        "ToyDspMycharaR1D_Top_matanim_joint",
        "ToyDspMycharaR1E_Top_matanim_joint",
        "ToyDspMycharaR2A_Top_matanim_joint",
        "ToyDspMycharaR2B_Top_matanim_joint",
        "ToyDspMycharaR2C_Top_matanim_joint",
        "ToyDspMycharaR2D_Top_matanim_joint",
        "ToyDspMycharaR2E_Top_matanim_joint",
        "ToyDspMapA_Top_matanim_joint",
        "ToyDspMapB_Top_matanim_joint",
        "ToyDspMapC_Top_matanim_joint",
        "ToyDspMapD_Top_matanim_joint",
        "ToyDspMapE_Top_matanim_joint",
        "ToyDspFgseriesA_Top_matanim_joint",
        "ToyDspFgseriesB_Top_matanim_joint",
        "ToyDspFgseriesC_Top_matanim_joint",
        "ToyDspFgseriesD_Top_matanim_joint",
        "ToyDspFgseriesE_Top_matanim_joint",
        "ToyDspFgetcA_Top_matanim_joint",
        "ToyDspFgetcB_Top_matanim_joint",
        "ToyDspFgetcC_Top_matanim_joint",
        "ToyDspFgetcD_Top_matanim_joint",
        "ToyDspFgetcE_Top_matanim_joint",
        "ToyDspPokemonA_Top_matanim_joint",
        "ToyDspPokemonB_Top_matanim_joint",
        "ToyDspPokemonC_Top_matanim_joint",
        "ToyDspPokemonD_Top_matanim_joint",
        "ToyDspPokemonE_Top_matanim_joint",
        "ToyDspItemA_Top_matanim_joint",
        "ToyDspItemB_Top_matanim_joint",
        "ToyDspItemC_Top_matanim_joint",
        "ToyDspItemD_Top_matanim_joint",
        "ToyDspItemE_Top_matanim_joint",
        un_804D5AC0,
        un_804D5AC0,
    };

    if (idx == -1) {
        idx = 0;
    }

    return table[idx];
}

s32 un_8031BBF4(s8 arg0)
{
    char* table[] = {
        "TyQuesD.dat",  "TyMycCmA.dat", "TyMycCmB.dat", "TyMycCmC.dat",
        "TyMycCmD.dat", "TyMycCmE.dat", "TyMycR1A.dat", "TyMycR1B.dat",
        "TyMycR1C.dat", "TyMycR1D.dat", "TyMycR1E.dat", "TyMycR2A.dat",
        "TyMycR2B.dat", "TyMycR2C.dat", "TyMycR2D.dat", "TyMycR2E.dat",
        "TyMapA.dat",   "TyMapB.dat",   "TyMapC.dat",   "TyMapD.dat",
        "TyMapE.dat",   "TySeriA.dat",  "TySeriB.dat",  "TySeriC.dat",
        "TySeriD.dat",  "TySeriE.dat",  "TyEtcA.dat",   "TyEtcB.dat",
        "TyEtcC.dat",   "TyEtcD.dat",   "TyEtcE.dat",   "TyPokeA.dat",
        "TyPokeB.dat",  "TyPokeC.dat",  "TyPokeD.dat",  "TyPokeE.dat",
        "TyItemA.dat",  "TyItemB.dat",  "TyItemC.dat",  "TyItemD.dat",
        "TyItemE.dat",  "TyStandD.dat", "TyQuesD.dat",
    };
    if (arg0 == -1) {
        arg0 = 0;
    }
    return (s32) table[arg0];
}

/// #un_8031BC54

/// #un_8031BF34

/// #un_8031C1D0
void un_8031C1D0(void)
{
    s32 savedColor;
    s32 bgColor;
    char buf[28];
    HSD_GObj* gobj;

    savedColor = un_804DE024;
    un_804D6F24 = DevText_Create(1, 0x28, 0x28, 9, 3, un_804A2D98);
    if (un_804D6F24 != NULL) {
        gobj = DevText_GetGObj();
        bgColor = un_804DE028;
        DevText_Show(gobj, un_804D6F24);
        DevText_HideCursor(un_804D6F24);
        DevText_80302AC0(un_804D6F24);
        DevText_SetBGColor(un_804D6F24, *(GXColor*) &bgColor);
        DevText_SetScale(un_804D6F24, un_804DE020, un_804DE02C);
        DevText_Erase(un_804D6F24);
        DevText_SetCursorXY(un_804D6F24, 0, 0);
        DevText_StoreColorIndex(un_804D6F24, 0);
        DevText_SetTextColor(un_804D6F24, *(GXColor*) &savedColor);
        sprintf(buf, un_803FF19C, un_804DE030, un_804DE030);
        DevText_Print(un_804D6F24, buf);
    }
}

void tyDisplay_8031C2CC(void)
{
    un_803124BC();
}

s32 tyDisplay_8031C2EC(void)
{
    if (un_80304B0C(5) != 0) {
        if (HSD_Randi(2) == 0) {
            return un_80305058(2, 5, 1, 65.0f);
        }
    }
    return un_80305058(2, 0, 1, 60.0f);
}

s32 un_8031C354(s32 id, s32 (*buf)[], s32 max, s32 kind)
{
    void* data;
    void* other;
    s32 i;
    s32 count;
    s32 val;


    if (id == -1) {
        return 0;
    }

    data = un_8031B9DC(id);

    if (kind == 99) {
        kind = (s32) un_803060BC(id, 6);
    }

    count = 0;
    for (i = 0; i < 0x125; i++) {
        if (i == id) {
            continue;
        }
        if (un_80304CC8(i) == 0) {
            continue;
        }
        if (un_803049F4(i) == 0) {
            continue;
        }
        other = un_8031B9DC(i);
        val = (s32) un_803060BC(i, 6);
        if (((u8*) other)[4] != ((u8*) data)[4]) {
            continue;
        }
        if (val != kind) {
            continue;
        }
        count++;
        (*buf)[0] = i;
        buf = (s32(*)[])((u8*) buf + 4);
        if (count >= max) {
            break;
        }
    }

    return count;
}

/// #un_8031C454

/// #un_8031C5E4

/// #un_8031C8B8
void un_8031C8B8(void)
{
    s32 i;

    for (i = 0; i < 0x2B; i++) {
        un_804A2DE8[i] = 0;
    }
}
