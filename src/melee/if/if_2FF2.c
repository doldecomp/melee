#include "ifall.h"
#include "ifcoget.h"
#include "textdraw.h"
#include "textlib.h"
#include <dolphin/mtx.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/lb/lb_00B0.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/sislib.h>
#include <sysdolphin/baselib/wobj.h>

/* 3F9E38 */ static HSD_WObjDesc eyepos = {
    NULL,
    { 0.0f, 40.241425f, 100.24099f },
    NULL,
};

static HSD_WObjDesc interest = {
    NULL,
    { 0.0f, 10.0f, 0.0f },
    NULL,
};

/* 3F9E60 */ static HSD_CameraDescPerspective un_803F9E60 = {
    NULL,
    0,
    (1 << 0),
    { 0, 640, 0, 480 },
    { 0, 640, 0, 480 },
    &eyepos,
    &interest,
    0.0f,
    NULL,
    0.1f,
    32.0f * 1024,
    30.0f,
    1.18f,
};
ASSERT_SIZE(un_803F9E60, 0x38);

/// @todo Clean up @c pos values; x and y seem like portions of 20
/* 3F9E98 */ static HSD_WObjDesc light_position = {
    NULL,
    { 6.360198974609375f, 14.9432392120f, 59.982383728027344f },
};

/* 3F9EAC */ static HSD_LightPointDesc light_point = {
    0.99f,
    10000.0f,
    GX_DA_STEEP,
};

/* 3F9EB8 */ static HSD_LightDesc light0 = {
    NULL,
    NULL,
    (1 << 3),
    0,
    { 0xFF, 0xFF, 0xFF, 0xFF },
    &light_position,
    NULL,
    &light_point,
};
/* 3F9ED4 */ static HSD_LightDesc light1 = {
    NULL, &light0, (1 << 0), 0, { 0xFF, 0xFF, 0xFF, 0xFF }, NULL, NULL, NULL,
};
/* 3F9EF0 */ char lbl_803F9EF0[0x20] = "Remove Target %x (n %x) Id %d\n";
/* 3F9F10 */ char lbl_803F9F10[0x18] = "Remove All Over\n";

/// .bss
struct un_804A1F58_x8_t {
    HSD_GObj* x0;
    HSD_Text* x4;
    unsigned int x8;
    unsigned int xC;
    unsigned char x10;
};

/* 4A1F58 */ static struct un_804A1F58_t {
    unsigned int x0;
    char pad_x4[4];
    struct un_804A1F58_x8_t x8[6];
} un_804A1F58;

static inline struct un_804A1F58_x8_t* getEntry(int slot)
{
    return &un_804A1F58.x8[slot];
}

static inline int findSlot(HSD_GObj* gobj)
{
    int i;
    for (i = 0; i < 6; i++) {
        if (getEntry(i)->x0 == gobj) {
            return i;
        }
    }
    return -1;
}

static inline int getScore(int slot)
{
    int score;

    gm_8016B774();
    score = gm_GetMatchEndPlayerScore(slot);
    if (score > 9999) {
        score = 9999;
    }
    return score;
}

void fn_802FF218(HSD_GObj* gobj)
{
    int slot;
    struct un_804A1F58_x8_t* thing;
    PAD_STACK(16);

    slot = findSlot(gobj);
    if (slot >= 0) {
        thing = getEntry(slot);
        if (thing->x10 == 1) {
            HSD_SisLib_803A70A0(thing->x4, thing->x8, "  ");
        } else {
            int score = getScore(slot);
            if (thing->xC != score) {
                HSD_SisLib_803A70A0(thing->x4, thing->x8, "%d", score);
                thing->xC = score;
            }
        }
    }
}

void fn_802FF360(void* arg0) {}

static inline void freeEntry(struct un_804A1F58_x8_t* thing)
{
    if (thing->x0 != NULL) {
        HSD_GObjFree(thing->x0);
    }
    if (thing->x4 != NULL) {
        HSD_SisLib_803A5CC4(thing->x4);
    }
}

void un_802FF364(int slot)
{
    int score;
    Vec3* pos;
    struct un_804A1F58_x8_t* thing;
    struct un_804A1F58_t* base = &un_804A1F58;
    PAD_STACK(0x10);
    thing = &base->x8[slot];
    pos = ifAll_GetPlayerHUDPosition(slot);
    freeEntry(thing);
    thing->x4 = HSD_SisLib_803A6754(2, base->x0);
    thing->x4->default_alignment = 1;
    thing->x4->default_kerning = 1;
    gm_8016B774();
    score = gm_GetMatchEndPlayerScore(slot);
    if (score > 9999) {
        score = 9999;
    }
    thing->x8 =
        HSD_SisLib_803A6B98(thing->x4, pos->x, 3.2f + pos->y, "%d", score);
    HSD_SisLib_803A7548(thing->x4, thing->x8, 0.06f, 0.06f);
    thing->x4->render_callback = fn_802FF360;
    thing->x0 = GObj_Create(HSD_GOBJ_CLASS_UI, 15, 0);
    HSD_GObj_SetupProc(thing->x0, fn_802FF218, 17);
}

void un_802FF498(void)
{
    PAD_STACK(8);
    memzero(&un_804A1F58, sizeof(un_804A1F58));
    un_804A1F58.x0 =
        HSD_SisLib_803A611C(2, ifAll_GetHUDGObj(), 14, 15, 0, 11, 0, 19);
}

void un_802FF4FC(void)
{
    int i;
    for (i = 0; i < 6; i++) {
        freeEntry(getEntry(i));
    }
}

void un_802FF570(void)
{
    int i;
    struct un_804A1F58_x8_t* thing;
    HSD_Text* text;
    for (i = 0; i < 6; i++) {
        thing = getEntry(i);
        thing->x10 = 1;
        text = thing->x4;
        if (text) {
            text->hidden = 1;
        }
    }
}

void un_802FF620(void)
{
    int i;
    struct un_804A1F58_x8_t* thing;
    for (i = 0; i < 6; i++) {
        thing = getEntry(i);
        thing->x10 = 0;
        if (thing->x4 != NULL) {
            un_802FF364(i);
            thing->x4->hidden = 0;
        }
    }
}

void un_802FF6A0(void)
{
    HSD_GObj* gobj = GObj_Create(HSD_GOBJ_CLASS_LIGHT, 3, 0);
    HSD_LObj* new_var;
    new_var = HSD_LObjLoadDesc(&light1);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_LightKind, new_var);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);
}

void un_802FF710(void)
{
    HSD_CObj* new_var;
    HSD_GObj* gobj = GObj_Create(0x13, 20, 0);
    if (gobj) {
        new_var = HSD_CObjLoadDesc((HSD_CObjDesc*) &un_803F9E60);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_CameraKind, new_var);
        GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 11);
        gobj->gxlink_prios = 0x20000;
    }
}

HSD_GObj* un_802FF78C(void)
{
    HSD_GObj* gobj = DevText_Setup(21, 24, 0, 17, 0, 11);
    if (gobj) {
        un_80304138();
    }
    return gobj;
}
