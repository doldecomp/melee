#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "mn/mnmain.h"
#include "mn/types.h"

#include <baselib/gobj.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/sislib.h>

/// @todo: maybe rename to MenuInput?
typedef enum _MenuEvent {
    MenuEvent_Up = 1 << 0,
    MenuEvent_Down = 1 << 1,
    MenuEvent_Left = 1 << 2,
    MenuEvent_Right = 1 << 3,
    MenuEvent_Forward = 1 << 4,
    MenuEvent_Back = 1 << 5,
    MenuEvent_unk = 1 << 6,
    MenuEvent_unk2 = 1 << 7,
    MenuEvent_unk3 = 1 << 8,
    MenuEvent_unk4 = 1 << 9,
    MenuEvent_unk5 = 1 << 10,
    MenuEvent_unk6 = 1 << 11,
} MenuEvent;

#define GET_MENU(gobj) ((Menu*) HSD_GObjGetUserData(gobj))

static inline void Menu_DecrementAnimTimer(void)
{
    mn_804D6BC8.x0--;
    mn_804D6BC8.x2 = 0;
    mn_804D6BC8.x4 = 0;
}

static inline u64 Menu_GetAllEvents(void)
{
    return mn_804A04F0.x8 = mn_80229624(4);
}

static inline u64 Menu_GetEventsForPort(s32 i)
{
    return mn_804A04F0.x8 = mn_80229624(i);
}

// @todo: The functions `fn_8017435C`, `fn_80174338`, and `fn_80174380` are
// probably deduplicated clones of these.

static inline void sfxBack(void)
{
    lbAudioAx_80024030(0);
}

static inline void sfxForward(void)
{
    lbAudioAx_80024030(1);
}

static inline void sfxMove(void)
{
    lbAudioAx_80024030(2);
}

static inline void Menu_InitCenterText(Menu* menu, u8 val)
{
    HSD_Text* text =
        HSD_SisLib_803A5ACC(0, 1, -9.5F, 9.1F, 17.0F, 364.68332F, 38.38772F);
    menu->text = text;
    text->font_size.x = 0.0521F;
    text->font_size.y = 0.0521F;
    HSD_SisLib_803A6368(text, val);
}

// @todo: One of these inlines is probably correct

static inline void inline_test_3(HSD_JObj* jobj, f32 val, u8 loops,
                                 HSD_TypeMask type)
{
    HSD_JObjReqAnimAll(jobj, val);
    mn_8022F3D8(jobj, loops, type);
    HSD_JObjAnimAll(jobj);
}

static inline void inline_test_4(HSD_GObj* gobj, f32 val, u8 loops,
                                 HSD_TypeMask type)
{
    HSD_JObj* jobj;
    lb_80011E24(GET_JOBJ(gobj), &jobj, 5, -1);
    HSD_JObjReqAnimAll(jobj, val);
    mn_8022F3D8(jobj, loops, type);
    HSD_JObjAnimAll(jobj);
}
