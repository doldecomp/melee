#include "gmtou.h"

#include "gm_unsplit.h"

#include "baselib/forward.h"
#include "gm/gmtou.static.h"
#include "placeholder.h"
#include "baselib/gobj.h"
#include "baselib/jobj.h"
#include "baselib/random.h"
#include "baselib/sislib.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "sc/types.h"
#include <melee/gm/types.h>

// Filename is just a guess, based on some strings in the file
// Seems to be Tournament game code

extern TmBoxArrays* lbl_804771B8;
extern HSD_Archive* lbl_804D6638;
extern HSD_Archive* lbl_804D6660;
extern HSD_Archive* lbl_804D6664;
extern HSD_Archive* lbl_804D6668;
extern SceneDesc* lbl_804D666C;
extern SceneDesc* lbl_804D6670;
extern SceneDesc* lbl_804D6674;
extern u8 lbl_804D6680[8];
static struct TmAnimTimers lbl_80479A58;
extern HSD_Archive* lbl_804D6688;
extern HSD_Archive* lbl_804D668C;

static inline TmData* GetTmData(void)
{
    return gm_8018F634();
}

void gm_8019B8C4_OnEnter(void* arg0)
{
    lbl_804D6668 = NULL;
    lbl_804D6664 = NULL;
    lbl_804D6680[0] = 0;
    lbl_804D6680[2] = 0;
    gm_8018F634();
    lbl_804D6660 = lbArchive_80016DBC("GmTou1p", &lbl_804D666C, "ScGamTour_scene_data", 0);
    lbl_804D6638 = lbArchive_80016DBC(
        "TmBox.dat", lbl_804771B8->box2, "tournament_box2_array",
        lbl_804771B8->box3, "tournament_box3_array", lbl_804771B8->box4,
        "tournament_box4_array", 0);
    lbl_804D6664 = lbArchive_80016DBC("GmTou3p", &lbl_804D6670, "ScGamTour_scene_data", 0);
    lbl_804D6668 = lbArchive_80016DBC("GmTou4p", &lbl_804D6674, "ScGamTour_scene_data", 0);
    HSD_SisLib_803A62A0(0, fn_8018F5F0(), "SIS_TournamentData");
    if (HSD_Randi(2) != 0) {
        lbAudioAx_80023F28(0x5D);
        return;
    }
    lbAudioAx_80023F28(0x5E);
}

void gm_8019B9C8_OnLeave(void* arg0)
{
    lbArchive_80016EFC(lbl_804D6660);
    lbArchive_80016EFC(lbl_804D6638);
    lbArchive_80016EFC(lbl_804D6664);
    lbArchive_80016EFC(lbl_804D6668);
}

void fn_8019BA04(void) {}

/// #fn_8019BA08

void fn_8019BF18(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);

    if (lbl_80479A58.x4 > 800) {
        lbl_80479A58.x4 = 0;
    }

    fn_8019044C(jobj, lbl_80479A58.x4);
    lbl_80479A58.x4++;
}

void fn_8019BF8C(HSD_GObj* gobj)
{
    s32 selection;
    HSD_JObj* jobj;

    selection = gm_8018F634()->x0;
    jobj = GET_JOBJ(gobj);
    if ((selection <= 0x1A) || (selection >= 0x1F)) {
        if (lbl_80479A58.xE > 0x77U) {
            lbl_80479A58.xE = 0x5A;
        }
    } else if ((selection <= 0x1E) && (lbl_80479A58.xE > 0x9FU)) {
        lbl_80479A58.xE = 0x82;
    }

    fn_8019044C(jobj, lbl_80479A58.xE);
    lbl_80479A58.xE++;
}

/// #fn_8019C048

/// #fn_8019C3EC

/// #fn_8019C570

void fn_8019C6AC(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    TmData* unused = GetTmData();

    jobj = GET_JOBJ(gobj);

    if (lbl_80479A58.xF > 0x3CU) {
        lbl_80479A58.xF = 0x3C;
    }

    fn_8019044C(jobj, (lbl_80479A58.xF + gm_804771C4.x4 * 100 + 100));
    lbl_80479A58.xF++;
}

/// #fn_8019C744

/// #fn_8019CA38


void fn_8019CBFC(HSD_GObj* gobj)
{
    TmData* unused = GetTmData();
    HSD_JObj* jobj = GET_JOBJ(gobj);

    fn_8019044C(jobj, lbl_80479A58.x1C + 0x14);
    if (lbl_80479A58.x1C < 0xAU) {
        lbl_80479A58.x1C++;
    }
}

/// #fn_8019CC74

/// #fn_8019CDBC

void fn_8019CFA4(HSD_GObj* gobj)
{
    TmData* data;
    HSD_JObj* jobj;

    data = GetTmData();
    jobj = GET_JOBJ(gobj);

    jobj = HSD_JObjGetChild(jobj);
    jobj = HSD_JObjGetNext(jobj);

    if (jobj == NULL) {
        jobj = NULL;
    } else {
        jobj = jobj->next;
    }

    fn_8019044C(jobj, data->pad_x8[0x26]);
    jobj = HSD_JObjGetNext(jobj);
    fn_8019044C(jobj, data->pad_x8[0x28]);
}

/// #fn_8019D074

/// #fn_8019D1BC

/// #fn_8019DD60

/// #gm_8019DF8C_OnFrame

/// #gm_8019E634

/// #gm_8019ECAC_OnEnter

void gm_8019EE54_OnLeave(void* arg0)
{
    lbArchive_80016EFC(lbl_804D6688);
    lbArchive_80016EFC(lbl_804D668C);
}

/// #fn_8019EE80

/// #fn_8019EF08
