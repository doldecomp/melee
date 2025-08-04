#include <placeholder.h>

#include "if/iftime.h"

#include "dolphin/os.h"
#include "gm/gm_unsplit.h"
#include "if/ifall.h"
#include "lb/lb_00B0.h"
#include "lb/lbarchive.h"
#include "sc/types.h"

#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

static struct ifTime_data {
    HSD_GObj* match_timer;
    HSD_GObj* countdown_timer;
    HSD_JObj* digits[10];
    unsigned char countdown_seconds;
    char pad31[0x38 - 0x31];
    struct DynamicModelDesc** countdown_timer_models;
} ifTime_data;
static DynamicModelDesc ifTime_match_timer_models;

static bool ifTime_LoadModels(void)
{
    DynamicModelDesc** ScInfTim_scene_models;
    lbArchive_LoadSections(*ifAll_802F3690(), (void*) &ScInfTim_scene_models,
                           "ScInfTim_scene_models",
                           &ifTime_data.countdown_timer_models, "tdsce", 0);
    if (*ScInfTim_scene_models != NULL) {
        ifTime_match_timer_models.joint = (**ScInfTim_scene_models).joint;
        ifTime_match_timer_models.anims = (**ScInfTim_scene_models).anims;
        ifTime_match_timer_models.matanims =
            (**ScInfTim_scene_models).matanims;
        ifTime_match_timer_models.shapeanims =
            (**ScInfTim_scene_models).shapeanims;
    }
    return *ScInfTim_scene_models != NULL ? true : false;
}

static inline void ifTime_SetDigit(HSD_JObj* jobj, unsigned int frame)
{
    HSD_AObjReqAnim(jobj->u.dobj->mobj->tobj->aobj, frame & 0xFF);
    HSD_AObjSetRate(jobj->u.dobj->mobj->tobj->aobj, 0.0f);
}

#define IFTIME_HOUR_SEP 0
#define IFTIME_MINUTE_SEP 1
#define IFTIME_HOUR_TEN 2
#define IFTIME_HOUR_ONE 3
#define IFTIME_MINUTE_TEN 4
#define IFTIME_MINUTE_ONE 5
#define IFTIME_CENTISECOND_TEN 6
#define IFTIME_CENTISECOND_ONE 7
#define IFTIME_SECOND_TEN 8
#define IFTIME_SECOND_ONE 9

#define IFTIME_ONES_DIGIT(x) ((x) % 10)
#define IFTIME_TENS_DIGIT(x) (((x) % 100) / 10)

void ifTime_SetTime(HSD_JObj* jobj, int seconds, int centiseconds)
{
    StartMeleeRules* rules = gm_8016AE50();
    int hours;

    // minutes
    if (rules->timer_shows_hours) {
        ifTime_SetDigit(ifTime_data.digits[IFTIME_MINUTE_TEN],
                        IFTIME_TENS_DIGIT((seconds / 60) % 60));
        hours = (seconds / 60) / 60;
    } else {
        ifTime_SetDigit(ifTime_data.digits[IFTIME_MINUTE_TEN],
                        IFTIME_TENS_DIGIT(seconds / 60));
        hours = 0;
    }
    ifTime_SetDigit(ifTime_data.digits[IFTIME_MINUTE_ONE],
                    IFTIME_ONES_DIGIT((seconds / 60) % 60));

    // seconds
    ifTime_SetDigit(ifTime_data.digits[IFTIME_SECOND_TEN],
                    IFTIME_TENS_DIGIT(seconds % 60));
    ifTime_SetDigit(ifTime_data.digits[IFTIME_SECOND_ONE],
                    IFTIME_ONES_DIGIT(seconds % 60));

    // hours
    if (hours != 0) {
        u32 flags = ~HSD_JObjGetFlags(jobj) & JOBJ_HIDDEN;
        int hours_ten;
        HSD_JObjClearFlags(ifTime_data.digits[IFTIME_HOUR_SEP], flags);
        HSD_JObjClearFlags(ifTime_data.digits[IFTIME_HOUR_ONE], flags);
        ifTime_SetDigit(ifTime_data.digits[IFTIME_HOUR_ONE],
                        IFTIME_ONES_DIGIT(hours));
        hours_ten = IFTIME_TENS_DIGIT(hours);
        if (hours_ten > 0) {
            HSD_JObjClearFlags(ifTime_data.digits[IFTIME_HOUR_TEN], flags);
            ifTime_SetDigit(ifTime_data.digits[IFTIME_HOUR_TEN], hours_ten);
        } else {
            HSD_JObjSetFlags(ifTime_data.digits[IFTIME_HOUR_TEN], flags);
        }
    } else {
        HSD_JObjSetFlags(ifTime_data.digits[IFTIME_HOUR_ONE], JOBJ_HIDDEN);
        HSD_JObjSetFlags(ifTime_data.digits[IFTIME_HOUR_TEN], JOBJ_HIDDEN);
        HSD_JObjSetFlags(ifTime_data.digits[IFTIME_HOUR_SEP], JOBJ_HIDDEN);
    }

    // centiseconds
    ifTime_SetDigit(ifTime_data.digits[IFTIME_CENTISECOND_TEN],
                    IFTIME_TENS_DIGIT(centiseconds));
    ifTime_SetDigit(ifTime_data.digits[IFTIME_CENTISECOND_ONE],
                    IFTIME_ONES_DIGIT(centiseconds));
}

void ifTime_HideTimers(void)
{
    struct ifTime_data* x = &ifTime_data;
    PAD_STACK(0x18);
    if (x->match_timer != NULL) {
        HSD_JObjSetFlagsAll(x->match_timer->hsd_obj, JOBJ_HIDDEN);
    }
    if (x->countdown_timer != NULL) {
        HSD_JObjSetFlagsAll(x->countdown_timer->hsd_obj, JOBJ_HIDDEN);
    }
}

void ifTime_ShowTimers(void)
{
    struct ifTime_data* x = &ifTime_data;
    PAD_STACK(0x18);
    if (x->match_timer != NULL) {
        HSD_JObj* jobj = x->match_timer->hsd_obj;
        int seconds;
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        seconds = gm_8016AEEC();
        ifTime_SetTime(jobj, seconds, gm_8016AF0C());
    }
    if (x->countdown_timer != NULL) {
        HSD_JObjClearFlagsAll(x->countdown_timer->hsd_obj, JOBJ_HIDDEN);
    }
}

int ifTime_GetCountdownSeconds(void)
{
    int centiseconds = gm_8016AF0C();
    int seconds = gm_8016AEEC();
    if (centiseconds == 0) {
        seconds = 5 - seconds;
    } else {
        seconds = 4 - seconds;
    }
    if (seconds < 0) {
        seconds = 0;
    }
    return seconds;
}

void ifTime_UpdateCountdown(HSD_GObj* arg0)
{
    struct ifTime_data* x = &ifTime_data;
    HSD_JObj* jobj = arg0->hsd_obj;
    int f = ifTime_GetCountdownSeconds();
    if (f != x->countdown_seconds) {
        x->countdown_seconds = f;
        HSD_JObjRemoveAnimAll(jobj);
        lb_8000C0E8(jobj, x->countdown_seconds, x->countdown_timer_models[0]);
        HSD_JObjReqAnimAll(jobj, 0.0f);
        HSD_JObjAnimAll(jobj);
    }
    HSD_JObjAnimAll(jobj);
}

void ifTime_FreeCountdown(void)
{
    struct ifTime_data* x = &ifTime_data;
    if (x->countdown_timer != NULL) {
        HSD_GObjPLink_80390228(x->countdown_timer);
        x->countdown_timer = NULL;
    }
}

void ifTime_UpdateTimers(HSD_GObj* arg0)
{
    struct ifTime_data* x = &ifTime_data;
    HSD_JObj* jobj = arg0->hsd_obj;
    int seconds;
    int centiseconds;
    gm_8016AE50();
    seconds = gm_8016AEEC();
    centiseconds = gm_8016AF0C();
    ifTime_SetTime(jobj, seconds, centiseconds);
    if (gm_8016B110() == 0 && centiseconds == 0 && seconds == 5) {
        HSD_JObj* jobj2 =
            HSD_JObjLoadJoint(x->countdown_timer_models[0]->joint);
        if (jobj2 == NULL) {
            OSReport("Error : jobj dont't get (ifAddTimeDownModel)\n");
            OSPanic("iftime.c", 300, "");
        }
        HSD_GObjObject_80390A70(x->countdown_timer, HSD_GObj_804D7849, jobj2);
        GObj_SetupGXLink(x->countdown_timer, HSD_GObj_JObjCallback, 11, 0);
        x->countdown_seconds = ifTime_GetCountdownSeconds();
        lb_8000C0E8(jobj2, x->countdown_seconds, x->countdown_timer_models[0]);
        HSD_JObjReqAnimAll(jobj2, 0.0f);
        HSD_JObjAnimAll(jobj2);
        HSD_JObjSetTranslate(jobj2, ifAll_802F3414());
        HSD_GObjProc_8038FD54(x->countdown_timer, ifTime_UpdateCountdown, 17);
        if (x->match_timer) {
            HSD_GObjPLink_80390228(x->match_timer);
            x->match_timer = NULL;
        }
    }
    HSD_JObjAnimAll(jobj);
}

void ifTime_CreateTimers(void)
{
    StartMeleeRules* rules = gm_8016AE50();
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    int i;
    DynamicModelDesc** ScInfTim_scene_models;
    if (!rules->x1_0 && !rules->x0_6) {
        ifTime_data.match_timer = NULL;
        return;
    }
    if (ifTime_LoadModels()) {
        ifTime_data.countdown_timer = GObj_Create(HSD_GOBJ_CLASS_UI, 15, 0);
        if (ifTime_data.countdown_timer == NULL) {
            OSReport("Error : gobj dont't get (ifAddTime)\n");
            OSPanic("iftime.c", 379, "");
        }
        gobj = GObj_Create(HSD_GOBJ_CLASS_UI, 16, 0);
        if (gobj == NULL) {
            OSReport("Error : gobj dont't get (ifAddTime)\n");
            OSPanic("iftime.c", 383, "");
        }
        jobj = HSD_JObjLoadJoint(ifTime_match_timer_models.joint);
        if (jobj == NULL) {
            OSReport("Error : jobj dont't get (ifAddTime)\n");
            OSPanic("iftime.c", 389, "");
        }
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 11, 0);
        lb_8000C07C(jobj, 0, ifTime_match_timer_models.anims,
                    ifTime_match_timer_models.matanims,
                    ifTime_match_timer_models.shapeanims);
        HSD_JObjReqAnimAll(jobj, 0.0f);
        HSD_GObjProc_8038FD54(gobj, ifTime_UpdateTimers, 17);
        HSD_JObjSetTranslate(jobj, ifAll_802F3414());
        jobj = HSD_JObjGetChild(jobj);
        ifTime_data.digits[0] = jobj;
        for (i = 1; i < 10; i++) {
            jobj = HSD_JObjGetNext(jobj);
            ifTime_data.digits[i] = jobj;
        }
        ifTime_data.match_timer = gobj;
    }
}

void ifTime_Reset(void)
{
    struct ifTime_data* x = &ifTime_data;
    memzero(x, sizeof(*x));
}

void ifTime_FreeTimers(void)
{
    struct ifTime_data* x = &ifTime_data;
    if (x->match_timer != NULL) {
        HSD_GObjPLink_80390228(x->match_timer);
        x->match_timer = NULL;
    }
    if (x->countdown_timer != NULL) {
        HSD_GObjPLink_80390228(x->countdown_timer);
        x->countdown_timer = NULL;
    }
}

bool ifTime_IsTimerHidden(void)
{
    struct ifTime_data* x = &ifTime_data;
    PAD_STACK(0x18);
    if (x->match_timer != NULL &&
        (HSD_JObjGetFlags(x->match_timer->hsd_obj) & JOBJ_HIDDEN) != 0)
    {
        return true;
    }
    if (x->countdown_timer != NULL &&
        (HSD_JObjGetFlags(x->countdown_timer->hsd_obj) & JOBJ_HIDDEN) != 0)
    {
        return true;
    }
    return false;
}
