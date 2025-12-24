#include "if_2FC93.h"

#include "gm/gm_unsplit.h"
#include "if/ifall.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "pl/player.h"
#include "sc/types.h"

#include <printf.h>
#include <dolphin/mtx.h>
#include <baselib/cobj.h>
#include <baselib/dobj.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/memory.h>
#include <baselib/particle.h>
#include <baselib/sislib.h>
#include <MSL/stdio.h>
#include <MSL/string.h>

// .bss
/* 4A1F10 */ static struct {
    DynamicModelDesc** x0;
    HSD_GObj* x4[4];
    GXColor x14[4];
    unsigned char x24[4];
    unsigned char x28[4];
    unsigned char x2C[4];
    unsigned char x30;
    unsigned char x31;
    unsigned char x32;
} un_804A1F10;

// .sdata2
/* 4DDBA8 */ static char un_804DDBA8[4] = { 0, 1, 2, 3 };

// .sbss
/* 4D6D90 */ static int un_804D6D90;

void un_802FD910(void)
{
    un_804D6D90 = 1;
}

void un_802FD91C(void)
{
    un_804D6D90 = 0;
}

void un_802FD928(unsigned char slot, int arg1, GXColor* arg2)
{
    if (slot < 4) {
        int i;
        for (i = 0; i < 4; i++) {
            Gm_PKind type = Player_GetPlayerSlotType(slot);
            if (type != Gm_PKind_Cpu && !un_804A1F10.x28[i] &&
                !un_804A1F10.x24[slot])
            {
                un_804A1F10.x24[slot] = 1;
                un_804A1F10.x2C[i] = slot;
                un_804A1F10.x28[i] = arg1;
                un_804A1F10.x14[i] = *arg2;
                return;
            }
        }
    }
}

void un_802FD9D8(unsigned char slot)
{
    int i;
    for (i = 0; i < 4; i++) {
        if (un_804A1F10.x2C[i] == slot) {
            un_804A1F10.x24[slot] = 0;
            un_804A1F10.x28[i] = 0;
        }
    }
}

void fn_802FDA4C(HSD_GObj* gobj, int pass)
{
    if (un_804D6D90 == 0) {
        HSD_GObj_JObjCallback(gobj, pass);
    }
}

void fn_802FDA78(HSD_GObj* gobj)
{
    int i, j, k;
    float v[] = { 0.0, -1.3, -2.6, -3.9 };
    HSD_JObj* jobj = gobj->hsd_obj;
    unsigned char* pslot = gobj->user_data;
    unsigned char slot = *pslot;
    HSD_JObjSetTranslateZ(jobj, 0.0);
    jobj->child->u.dobj->mobj->mat->diffuse = un_804A1F10.x14[slot];
    jobj->child->u.dobj->next->mobj->mat->diffuse = un_804A1F10.x14[slot];
    jobj->child->u.dobj->next->next->mobj->mat->diffuse =
        un_804A1F10.x14[slot];
    if (!un_804A1F10.x28[0] && !un_804A1F10.x28[1] && !un_804A1F10.x28[2] &&
        !un_804A1F10.x28[3])
    {
        un_804A1F10.x31 = 0xFF;
        un_804A1F10.x32 = 0;
    }
    switch (un_804A1F10.x28[slot]) {
    case 0:
        HSD_JObjSetTranslateZ(jobj, 10000.0);
        break;
    case 1:
        if (un_804A1F10.x31 == 0xFF) {
            un_804A1F10.x31 = slot;
        } else if (un_804A1F10.x28[un_804A1F10.x31] == 1) {
            if (un_804A1F10.x32 == 0 && un_804A1F10.x30 == 0) {
                lbAudioAx_80024030(4);
            }
            un_804A1F10.x32 = (un_804A1F10.x32 + 1) % 51;
        }
        j = 0;
        for (i = 0; i < slot; i++) {
            if (un_804A1F10.x28[i] == 1) {
                j++;
            }
        }
        k = 0;
        for (i = 0; i < 4; i++) {
            if (un_804A1F10.x28[i] == 1) {
                k++;
            }
        }
        HSD_JObjSetRotationZ(jobj, 0.0);
        HSD_JObjSetTranslateY(jobj, 2.6 * j + v[k == 0 ? 0 : k - 1]);
        HSD_JObjSetTranslateX(jobj, -25.0);
        break;
    case 2:
        if (un_804A1F10.x31 == 0xFF) {
            un_804A1F10.x31 = slot;
        } else if (un_804A1F10.x28[un_804A1F10.x31] == 2) {
            if (un_804A1F10.x32 == 0 && un_804A1F10.x30 == 0) {
                lbAudioAx_80024030(4);
            }
            un_804A1F10.x32 = (un_804A1F10.x32 + 1) % 51;
        }
        j = 0;
        for (i = 0; i < slot; i++) {
            if (un_804A1F10.x28[i] == 2) {
                j++;
            }
        }
        k = 0;
        for (i = 0; i < 4; i++) {
            if (un_804A1F10.x28[i] == 2) {
                k++;
            }
        }
        HSD_JObjSetRotationZ(jobj, 3.1415927);
        HSD_JObjSetTranslateY(jobj, 2.6 * j + v[k == 0 ? 0 : k - 1]);
        HSD_JObjSetTranslateX(jobj, 25.0);
        break;
    }
    HSD_JObjAnimAll(jobj);
}

void un_802FE260(void)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    int i;

    un_804D6D90 = 0;
    lbArchive_LoadSections(*ifAll_802F3690(), (void*) &un_804A1F10.x0,
                           "Stc_rarwmdls", 0);
    for (i = 0; i < 4; i++) {
        gobj = GObj_Create(HSD_GOBJ_CLASS_UI, 15, 0);
        jobj = HSD_JObjLoadJoint(un_804A1F10.x0[0]->joint);
        gobj->user_data = &un_804DDBA8[i];
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, fn_802FDA4C, 11, 0);
        gm_8016895C(jobj, un_804A1F10.x0[0], 0);
        HSD_GObjProc_8038FD54(gobj, fn_802FDA78, 17);
        HSD_JObjReqAnimAll(jobj, 0.0);
        HSD_JObjAnimAll(jobj);
        un_804A1F10.x24[i] = 0;
        un_804A1F10.x28[i] = 0;
        un_804A1F10.x4[i] = gobj;
    }
    un_804A1F10.x31 = -1;
    un_804A1F10.x32 = 0;
    un_804A1F10.x30 = gm_8016B124();
}

void un_802FE390(void)
{
    int i;
    PAD_STACK(8);
    for (i = 0; i < 4; i++) {
        if (un_804A1F10.x4[i] != 0) {
            HSD_GObjPLink_80390228(un_804A1F10.x4[i]);
            un_804A1F10.x4[i] = 0;
        }
    }
}
