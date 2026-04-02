#include "mngallery.h"

#include "baselib/debug.h"
#include "mn/inlines.h"

#include <baselib/controller.h>
#include <baselib/displayfunc.h>
#include <baselib/dobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/sobjlib.h>
#include <melee/gm/gmhowto.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbmthp.h>

static void* mnGallery_804D6C88;
static void* mnGallery_804D6C8C;

void mnGallery_80258940(void)
{
    mnGallery_804D6C8C = HSD_MemAlloc(0x271000);
}

typedef struct mnGallery_t {
    HSD_Joint* x0;
    HSD_AnimJoint* x4;
    HSD_MatAnimJoint* x8;
    HSD_ShapeAnimJoint* xC;
} mnGallery_t;

static mnGallery_t mnGallery1;
static mnGallery_t mnGallery2;

void mnGallery_8025896C(HSD_GObj* gobj, int render_pass)
{
    struct {
        u8 pad[0x2C];
        struct {
            u8 pad2[0x14];
            u8 state;
        }* unk2C;
    }* data = mnGallery_804D6C88;
    HSD_CObj* cobj = gobj->hsd_obj;
    PAD_STACK(0x10);

    if (data->unk2C->state == 3) {
        if (HSD_CObjSetCurrent(cobj)) {
            HSD_SetEraseColor(0, 0, 0, 0xFF);
            HSD_CObjEraseScreen(cobj, 1, 0, 0);
            HSD_CObjEndCurrent();
        }
        HSD_SObjLib_803A54EC(gobj, render_pass);
    }
}
#pragma push
#pragma opt_propagation off
void mnGallery_80258A08(HSD_GObj* gobj, u16 width, u16 height, u32 priority)
{
    HSD_CObj* cobj;
    f32 zero = 0.0f;
    f32 far;
    f32 near_val = zero;
    f32 top;
    f32 bottom;
    f32 left;
    f32 right;
    HSD_RectS16 viewport;
    Scissor scissor;
    Vec3 eye = { 0, 0, 1 };
    Vec3 interest = { 0, 0, 0 };

    far = 2.0f;
    bottom = (f32) (s32) - (s32) height;
    right = (f32) width;
    top = zero;
    left = zero;

    viewport.xmin = 0;
    scissor.left = 0;
    viewport.xmax = width;
    scissor.right = width;
    viewport.ymin = 0;
    scissor.top = 0;
    viewport.ymax = height;
    scissor.bottom = height;

    cobj = HSD_CObjAlloc();
    HSD_CObjSetProjectionType(cobj, 3);
    HSD_CObjSetViewport(cobj, &viewport);
    HSD_CObjSetScissor(cobj, &scissor);
    HSD_CObjSetEyePosition(cobj, &eye);
    HSD_CObjSetInterest(cobj, &interest);
    HSD_CObjSetRoll(cobj, zero);
    HSD_CObjSetNear(cobj, near_val);
    HSD_CObjSetFar(cobj, far);
    HSD_CObjSetOrtho(cobj, top, bottom, left, right);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, mnGallery_8025896C, priority);
}
#pragma pop

void mnGallery_80258BC4(void* arg)
{
    struct {
        u8 unk0;
        u8 unk1;
        u8 unk2;
        u8 pad3;
        s32 unk4;
        HSD_GObj* gobj;
        HSD_SObj* sobj;
        u8 pad10[4];
        u8 unk14;
        u8 unk15;
    }* data = arg;
    HSD_GObj* gobj;
    s32 mode;

    mode = data->unk15;
    if (data->unk0 != 0) {
        return;
    }
    if (mode < 0 || mode >= 2) {
        return;
    }
    data->unk2 = mode;
    gobj = GObj_Create(6, 7, 0x80);
    data->gobj = gobj;
    GObj_SetupGXLink(gobj, lbMthp_8001F67C, 8, 0x80);
    if (data->unk2 == 0) {
        HSD_SObj* sobj = lbMthp_8001F624(gobj, 0x1C0, 0x150);
        data->sobj = sobj;
        sobj->x10 = 0.0f;
        sobj->x14 = 72.0f;
    } else if (data->unk2 == 1) {
        HSD_SObj* sobj;
        sobj = lbMthp_8001F624(gobj, 0x280, 0x1E0);
        data->sobj = sobj;
        sobj->x10 = 0.0f;
        sobj->x14 = 0.0f;
    }
    switch (mode) {
    case 0:
        lbAudioAx_800236DC();
        lbAudioAx_80023F28(0x52);
        lbAudioAx_80024E50(true);
        lbMthp_8001F410("MvOmake15.mth", 0, (int) mnGallery_804D6C8C, 0x271000,
                        0);
        lbAudioAx_80024E50(false);
        break;
    case 1:
        lbAudioAx_800236DC();
        lbAudioAx_80023F28(0x24);
        lbAudioAx_80024E50(true);
        lbMthp_8001F410("MvHowTo.mth", gm_801ACC94(), (int) mnGallery_804D6C8C,
                        0x271000, 0);
        lbAudioAx_80024E50(false);
        break;
    }
    data->unk0 = 1;
}

#pragma push
#pragma dont_inline on
void mnGallery_80258D50(void* arg)
{
    struct {
        u8 unk0;
        u8 unk1;
        u8 pad[6];
        HSD_GObj* gobj;
    }* data = arg;
    s32 zero;

    if (data->unk0 != 0) {
        lbMthp_8001F800();
        lbAudioAx_800236DC();
        lbAudioAx_80023F28(gmMainLib_8015ECB0());

        zero = 0;
        data->unk0 = zero;
        data->unk1 = zero;

        if (data->gobj != NULL) {
            HSD_GObjPLink_80390228(data->gobj);
            data->gobj = NULL;
        }
    }
}
#pragma pop

void mnGallery_80258DBC(HSD_GObj* gobj, void* arg)
{
    struct {
        u8 unk0;
        u8 unk1;
        u8 pad[6];
        HSD_GObj* gobj;
        u8 pad2[0x08];
        u8 unk14;
    }* data = arg;
    u32 buttons;
    u32 skip;
    u32 pressed;
    PAD_STACK(0x10);

    skip = 0;
    buttons = HSD_PadCopyStatus[0].trigger | HSD_PadCopyStatus[1].trigger;
    buttons |= HSD_PadCopyStatus[2].trigger;
    buttons |= HSD_PadCopyStatus[3].trigger;
    lbMthp_8001F578();
    if (lbMthp_8001F604() != 0) {
        data->unk1 = data->unk1 + 1;
    }
    if (gmMainLib_8046B0F0.xC != 0 && lbMthp_8001F604() == 0) {
        skip = 1;
    }
    pressed = buttons & 0x1300;
    if (pressed != 0 || data->unk1 > 0x32 || skip != 0) {
        if (pressed != 0) {
            lbAudioAx_80024030(0);
        }
        data->unk14 = 1;
        mn_8022BD8C();
        if (data->unk0 != 0) {
            lbMthp_8001F800();
            lbAudioAx_800236DC();
            lbAudioAx_80023F28(gmMainLib_8015ECB0());
            data->unk0 = 0;
            data->unk1 = 0;
            if (data->gobj != NULL) {
                HSD_GObjPLink_80390228(data->gobj);
                data->gobj = NULL;
            }
        }
    }
}

void fn_80258ED0(HSD_GObj* gobj)
{
    struct fn_80258ED0_inner {
        u8 unk0;
        u8 unk1;
        u8 pad2[2];
        HSD_GObj* gobj4;
        HSD_GObj* volatile gobj8;
        void* unkC;
        HSD_Text* text;
        u8 unk14;
        u8 unk15;
    };
    struct fn_80258ED0_outer {
        u8 pad[0x2C];
        struct fn_80258ED0_inner* unk2C;
    };
    struct fn_80258ED0_outer* gallery;
    struct fn_80258ED0_inner* data;
    u64 buttons;
    u8 state;

    gallery = mnGallery_804D6C88;
    data = gallery->unk2C;

    if (mn_804D6BC8.cooldown != 0) {
        Menu_DecrementAnimTimer();
        return;
    }

    state = data->unk14;
    if (state == 3) {
        mnGallery_80258DBC(gobj, data);
        return;
    }
    if (state == 2) {
        return;
    }

    buttons = Menu_GetAllInputs();

    if (buttons & MenuInput_Back) {
        struct fn_80258ED0_inner* orig;
        sfxBack();
        mn_804A04F0.entering_menu = 0;
        mn_80229894(5, 1, 3);
        HSD_SisLib_803A5CC4(data->text);
        orig = data;
        data = ((struct fn_80258ED0_outer*) mnGallery_804D6C88)->unk2C;
        if (data->gobj4 != NULL) {
            HSD_GObjPLink_80390228(data->gobj4);
        }
        if (data->gobj8 != NULL) {
            HSD_GObjPLink_80390228(data->gobj8);
        }
        data->gobj4 = NULL;
        data->gobj8 = NULL;
        mnGallery_80258D50(data);
        orig->unk14 = 2;
        return;
    }

    if (data->unk14 == 1) {
        if (buttons & MenuInput_Up) {
            if (data->unk15 != 0) {
                sfxMove();
                data->unk15 = data->unk15 - 1;
                HSD_SisLib_803A6368(data->text, 0xC7);
            }
        } else if (buttons & MenuInput_Down) {
            if (data->unk15 < 1) {
                sfxMove();
                data->unk15 = data->unk15 + 1;
                HSD_SisLib_803A6368(data->text, 0xC8);
            }
        } else if (buttons & (MenuInput_StartButton | MenuInput_AButton)) {
            data->unk14 = 3;
            mn_8022BD6C();
            mnGallery_80258BC4(data);
        }
    }
}
struct fn_802590C4_data {
    u8 pad[0x14];
    u8 state;
    u8 pad2[3];
    s32 frame;
    HSD_GObj* gobjs[2];
};

inline void* inline_fn(HSD_GObj* gobj)
{
    return gobj->user_data;
}

inline void fn_802590C4_inline(HSD_GObj* gobj)
{
    struct fn_802590C4_data* store;
    s32 i;
    struct fn_802590C4_data* tmp;
    store = (tmp = inline_fn(gobj));
    HSD_GObjPLink_80390228(gobj);
    for (i = 0; i < 2; i++) {
        HSD_GObjPLink_80390228((tmp->gobjs)[i]);
        tmp->gobjs[i] = NULL;
    };
}

void fn_802590C4(HSD_GObj* gobj)
{
    struct fn_802590C4_data* data;
    HSD_JObj* jobj;

    data = inline_fn(gobj);
    jobj = gobj->hsd_obj;

    if (data->state == 3) {
        return;
    }

    if (data->state == 0) {
        if (data->frame < 0x13) {
            data->frame = data->frame + 1;
        } else {
            data->state = 1;
        }
    } else if (data->state == 2) {
        if (data->frame < 0x1D) {
            data->frame = data->frame + 1;
        } else {
            data->state = 4;
            fn_802590C4_inline(gobj);
        }
    }

    HSD_JObjReqAnimAll(jobj, (f32) data->frame);
    HSD_JObjAnimAll(jobj);
}

void mnGallery_802591BC(HSD_GObj* gobj)
{
    struct mnGallery_inner {
        u8 pad[0x14];
        u8 unk14;
        u8 unk15;
    };
    struct {
        u8 pad[0x2C];
        struct mnGallery_inner* unk2C;
    }* gallery;
    struct {
        HSD_GObj* parent_gobj;
        s32 index;
    }* ud;
    struct mnGallery_inner* inner;
    HSD_JObj* jobj;
    s32 index;
    HSD_JObj* child;
    s32 i;
    PAD_STACK(24);

    ud = gobj->user_data;
    gallery = mnGallery_804D6C88;
    jobj = gobj->hsd_obj;
    inner = gallery->unk2C;
    index = ud->index;

    child = HSD_JObjGetChild(ud->parent_gobj->hsd_obj);
    for (i = 0; i < index; i++) {
        child = HSD_JObjGetNext(child);
    }

    if (child != NULL) {
        HSD_JObjSetTranslateX(jobj, HSD_JObjGetTranslationX(child));
        HSD_JObjSetTranslateY(jobj, HSD_JObjGetTranslationY(child));
        HSD_JObjSetTranslateZ(jobj, HSD_JObjGetTranslationZ(child));
    }

    if (inner->unk15 == index) {
        HSD_MObjReqAnim(HSD_JObjGetChild(jobj)->u.dobj->mobj, 0.0f);
        HSD_MObjAnim(HSD_JObjGetChild(jobj)->u.dobj->mobj);
        HSD_MObjReqAnim(HSD_JObjGetChild(jobj)->u.dobj->next->mobj, 0.0f);
        HSD_MObjAnim(HSD_JObjGetChild(jobj)->u.dobj->next->mobj);
    } else {
        HSD_MObjReqAnim(HSD_JObjGetChild(jobj)->u.dobj->mobj, 0.0f);
        HSD_MObjAnim(HSD_JObjGetChild(jobj)->u.dobj->mobj);
        HSD_MObjReqAnim(HSD_JObjGetChild(jobj)->u.dobj->next->mobj, 0.0f);
        HSD_MObjAnim(HSD_JObjGetChild(jobj)->u.dobj->next->mobj);
    }

    HSD_TObjReqAnim(HSD_JObjGetChild(jobj)->u.dobj->mobj->tobj, (f32) index);
    HSD_TObjAnim(HSD_JObjGetChild(jobj)->u.dobj->mobj->tobj);
    HSD_TObjReqAnim(HSD_JObjGetChild(jobj)->u.dobj->next->mobj->tobj,
                    (f32) index);
    HSD_TObjAnim(HSD_JObjGetChild(jobj)->u.dobj->next->mobj->tobj);
}

#pragma push
#pragma dont_inline on
void mnGallery_80259604(void* arg)
{
    struct {
        /* 0x00 */ u8 unk0;
        /* 0x01 */ u8 unk1;
        /* 0x02 */ u8 unk2;
        /* 0x03 */ u8 pad3;
        /* 0x04 */ s32 unk4;
        /* 0x08 */ s32 unk8;
        /* 0x0C */ s32 unkC;
        /* 0x10 */ s32 unk10;
        /* 0x14 */ u8 unk14;
        /* 0x15 */ u8 unk15;
        /* 0x16 */ u8 pad16[2];
        /* 0x18 */ s32 unk18;
        /* 0x1C */ s32 unk1C;
        /* 0x20 */ s32 unk20;
    }* data = arg;

    data->unk0 = 0;
    data->unk1 = 0;
    data->unk2 = 0;
    data->unk4 = 0;
    data->unk8 = 0;
    data->unkC = 0;
    data->unk10 = 0;
    data->unk14 = 0;
    data->unk15 = 0;
    data->unk18 = 0;
    data->unk1C = 0;
    data->unk20 = 0;
}
#pragma pop

void mnGallery_8025963C(void)
{
    extern void* mnGallery_804A0BA0[];
    extern void* mnGallery_804A0BB0[];

    struct mnGallery_data {
        u8 pad[0x1C];
        HSD_GObj* gobjs[2];
    };
    struct mnGallery_child_ud {
        HSD_GObj* parent_gobj;
        s32 index;
    };

    void** arr = mnGallery_804A0BA0;
    HSD_GObj* gobj;
    HSD_GObjProc* proc;
    struct mnGallery_child_ud* cursor_user_data;
    s32 i;
    HSD_GObj* child_gobj;
    HSD_JObj* jobj;
    struct mnGallery_data* user_data;

    gobj = GObj_Create(6, 7, 0x80);
    mnGallery_804D6C88 = gobj;
    jobj = HSD_JObjLoadJoint(arr[0]);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_JObjAddAnimAll(jobj, arr[1], arr[2], arr[3]);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);

    user_data = HSD_MemAlloc(0x24);
    HSD_ASSERTREPORT(0x214, user_data, "Can't get user_data.\n");

    mnGallery_80259604(user_data);
    GObj_InitUserData(gobj, 0, HSD_Free, user_data);
    proc = HSD_GObj_SetupProc(gobj, fn_802590C4, 0);
    proc->flags_3 = HSD_GObj_804D783C;

    arr = mnGallery_804A0BB0;
    for (i = 0; i < 2; i++) {
        child_gobj = GObj_Create(6, 7, 0x80);
        user_data->gobjs[i] = child_gobj;
        jobj = HSD_JObjLoadJoint(arr[0]);
        HSD_GObjObject_80390A70(child_gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(child_gobj, HSD_GObj_JObjCallback, 4, 0x80);
        HSD_JObjAddAnimAll(jobj, arr[1], arr[2], arr[3]);
        HSD_JObjReqAnimAll(jobj, 0.0f);
        HSD_JObjAnimAll(jobj);

        cursor_user_data = HSD_MemAlloc(8);
        HSD_ASSERTREPORT(0x22c, cursor_user_data, "Can't get user_data.\n");

        cursor_user_data->parent_gobj = gobj;
        cursor_user_data->index = i;
        GObj_InitUserData(child_gobj, 0, HSD_Free, cursor_user_data);
        proc = HSD_GObj_SetupProc(child_gobj, mnGallery_802591BC, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        mnGallery_802591BC(child_gobj);
    }
}

void mnGallery_80259868(void)
{
    HSD_Archive* archive;
    void** new_var;
    HSD_GObj* gobj;
    HSD_GObjProc* proc;
    HSD_Text* text;
    HSD_GObj* cam_gobj;
    struct {
        u8 unk0;
        u8 unk1;
        u8 pad2[2];
        HSD_GObj* gobj4;
        HSD_GObj* gobj8;
        void* unkC;
        HSD_Text* text;
    }* inner;
    PAD_STACK(0x30);

    mn_804D6BC8.cooldown = 5;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0x1A;
    mn_804A04F0.hovered_selection = 0;
    archive = mn_804D6BB8;

    lbArchive_LoadSections(archive, (void*) &mnGallery1,
                           "MenMainConGa_Top_joint", &mnGallery1.x4,
                           "MenMainConGa_Top_animjoint", &mnGallery1.x8,
                           "MenMainConGa_Top_matanim_joint", &mnGallery1.xC,
                           "MenMainConGa_Top_shapeanim_joint", &mnGallery2.x0,
                           "MenMainCursorGa_Top_joint", &mnGallery2.x4,
                           "MenMainCursorGa_Top_animjoint", &mnGallery2.x8,
                           "MenMainCursorGa_Top_matanim_joint", &mnGallery2.xC,
                           "MenMainCursorGa_Top_shapeanim_joint", 0);

    gobj = GObj_Create(0, 1, 0x80);
    proc = HSD_GObj_SetupProc(gobj, (HSD_GObjEvent) fn_80258ED0, 0);
    proc->flags_3 = HSD_GObj_804D783C;
    mnGallery_8025963C();

    inner = ((HSD_GObj*) mnGallery_804D6C88)->user_data;
    text =
        HSD_SisLib_803A5ACC(0, 1, -9.5F, 9.1F, 17.0F, 364.68332F, 38.38772F);
    text->font_size.x = 0.0521F;
    text->font_size.y = 0.0521F;
    HSD_SisLib_803A6368(text, 0xC7);
    inner->text = text;

    cam_gobj = GObj_Create(6, 3, 0x80);
    mnGallery_80258A08(cam_gobj, 0x280, 0x1E0, 1);
    cam_gobj->gxlink_prios = 0x100;
    inner->gobj4 = cam_gobj;
}
