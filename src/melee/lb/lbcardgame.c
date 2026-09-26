#include "lbcardgame.h"

#include "lbarchive.h"
#include "lbcardnew.h"
#include "lblanguage.h"
#include <dolphin/card.h>
#include <dolphin/os.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/if/textlib.h>
#include <melee/sc/types.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>

typedef enum {
    stateStatus_0,
} stateStatus;

typedef enum {
    fileType_SaveData,
    fileType_NameTag,
    fileType_TrophyUnk,
    fileType_3,
} fileType;

typedef enum {
    statex10_0,
    statex10_1,
} statex10;

/* 433318 */ static struct {
    /* +0  */ bool probe_status;
    /* +4  */ bool unk_status;
    /* +8  */ LbCardStatus card_status;
    /* +C  */ bool dirty;
    /* +10 */ statex10 x10;
    /* +14 */ bool failed;
    /* +18 */ bool enable;
    /* +1C */ char comment[CARD_COMMENT_SIZE];
    /* +5C */ void** icon_data;

    /// Always set to 0 by ::lbCardGame_LoadArchive
    /* +60 */ ssize_t jobj_translate_idx;

    /* +64 */ SceneDesc* scene_data;
} state;

#define _p(x) (state.x)

static struct {
    u32 x0, x4, x8;
    u32 pad[2];
} lb_803BAB60 = {
    0x2000100,
    0,
    0x300,
};

static LbCardEntry manifest[] = {
    { 0, fileType_3, NULL },
    { sizeof(GmSaveData), fileType_SaveData, NULL },
    { sizeof(struct NameTagDataBank), fileType_NameTag, NULL },
    { sizeof(struct NameTagDataBank), fileType_NameTag, NULL },
    { sizeof(struct NameTagDataBank), fileType_NameTag, NULL },
    { sizeof(struct NameTagDataBank), fileType_NameTag, NULL },
    { sizeof(struct NameTagDataBank), fileType_NameTag, NULL },
    { sizeof(struct NameTagDataBank), fileType_NameTag, NULL },
    { sizeof(struct NameTagDataBank), fileType_NameTag, NULL },
    { -1 },
};

void lb_8001C600(void)
{
    int prev = _p(probe_status);
    _p(probe_status) = CARDProbe(0);
    if (_p(probe_status) != prev) {
        _p(unk_status) = 1;
    }
}

static char* lb_8001C658(void)
{
    OSCalendarTime time;
    const char* title;
    ssize_t i;

    OSTime ticks = OSGetTime();
    u32 seconds = OSTicksToSeconds(ticks);
    OSTicksToCalendarTime(OSSecondsToTicks((u64) seconds), &time);
    for (i = 0; i < CARD_COMMENT_SIZE; i++) {
        _p(comment)[i] = '\0';
    }
    if (lbLang_IsSettingJP()) {
        title = "大乱闘スマッシュブラザーズＤＸ  セーブデータ";
    } else {
        title = "Super Smash Bros. Melee         Game Data";
    }
    sprintf(_p(comment), "%s %4d/%02d/%02d", title, time.year, time.mon + 1,
            time.mday);
    return _p(comment);
}

static void* getCurrentIcon(void)
{
    ssize_t idx;
    if (un_80304470() != 0) {
        idx = 2;
    } else if (gm_80164ABC()) {
        idx = 1;
    } else {
        idx = 0;
    }
    return _p(icon_data)[idx];
}

char filename[] = "SuperSmashBros0110290334";

u32 lb_8001C87C(void)
{
    return lb_8001B7E0(0, filename, manifest, &lb_803BAB60, &_p(unk_status));
}

int lb_8001C8BC(void)
{
    HSD_ASSERT(320, _p(enable));

    return lb_8001BC18(0, filename, (void**) manifest, &lb_803BAB60,
                       lb_8001C658(), getCurrentIcon(), _p(icon_data)[3],
                       &_p(unk_status));
}

static LbCardStatus updateCardStatus(void)
{
    bool unk_status = _p(unk_status);
    _p(unk_status) = false;
    switch (_p(card_status)) {
    case LbCardStatus_0:
        if (unk_status) {
            _p(card_status) = LbCardStatus_1;
        }
        break;
    case LbCardStatus_1:
    case LbCardStatus_2:
        break;
    case LbCardStatus_3:
        if (lbCardNew_ProbeEx(0) != LbCardResult_Ready) {
            _p(card_status) = LbCardStatus_4;
        }
        break;
    case LbCardStatus_4:
        if (unk_status != 0 && lbCardNew_ProbeEx(0) == LbCardResult_Ready) {
            _p(card_status) = LbCardStatus_3;
        }
        break;
    default:
        break;
    }
    return _p(card_status);
}

void lbCardGame_SetCardStatus(LbCardStatus status)
{
    _p(card_status) = status;
}

lbCardResult lb_8001CBBC(void)
{
    lbCardResult result;

    if (updateCardStatus() != LbCardStatus_0) {
        return LbCardResult_Invalid;
    }
    result = lb_8001BD34(0, filename, manifest, &_p(unk_status));
    if (result != LbCardResult_Ready && result != LbCardResult_2) {
        _p(card_status) = LbCardStatus_2;
    }
    return result;
}

void fn_8001CC30(bool arg0)
{
    if (arg0 != 0) {
        _p(card_status) = LbCardStatus_2;
    }
}

int lb_8001CC4C(void)
{
    return lb_8001BA44(0, filename, &_p(unk_status));
}

static lbCardResult dont_inline_helper(void)
{
    void* icon;

    if (updateCardStatus() != 0) {
        return LbCardResult_Invalid;
    }

    icon = getCurrentIcon();
    return lb_8001BE30(0, filename, manifest, lb_8001C658(), icon,
                       _p(icon_data)[3], &_p(unk_status), fn_8001CC30);
}

void lb_8001CC84(void)
{
    PAD_STACK(4);

    do {
        switch (_p(x10)) {
        case statex10_0:
            if (!_p(dirty)) {
                break;
            }

            _p(dirty) = false;
            if (_p(card_status)) {
                break;
            }

            if (dont_inline_helper() != LbCardResult_Busy) {
                _p(failed) = true;
            } else {
                _p(x10) = true;
            }
            break;
        case statex10_1: {
            int result = lbCardNew_CompleteNextTask();
            if (result != LbCardResult_Busy) {
                if (result != 0) {
                    _p(failed) = true;
                }
                _p(x10) = result = 0;
            }
            break;
        }
        }
    } while (_p(x10) != statex10_1 && _p(dirty));
}

void lb_8001CDB4(void)
{
    while (_p(dirty) || _p(x10) != statex10_0) {
        lb_8001CC84();
    }
}

void lbCardGame_SaveChanges(void)
{
    HSD_ASSERT(675, _p(enable));
    *gm_GetPowerTime() += gmMainLib_8015FC74();
    _p(dirty) = true;
}

u8 lbCardGame_DecideGameMode(void)
{
    updateCardStatus();
    if (_p(card_status) != LbCardStatus_0 && _p(card_status) != LbCardStatus_4)
    {
        return GM_MEMCARD;
    }
    return GM_COUNT;
}

static void gobj1_Proc(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(gobj->hsd_obj);
}

static void gobj0_RenderFunc(HSD_GObj* gobj, intptr_t arg1)
{
    if (_p(x10) == 1) {
        HSD_GObj_803910D8(gobj, arg1);
    }
}

static Vec2 jobj_translate[] = { 21.5f, 16.5f };

void lbCardGame_InitScene(void)
{
    if (_p(scene_data) != NULL) {
        HSD_JObj* jobj;
        HSD_GObj* gobj =
            GObj_Create(HSD_GOBJ_CLASS_MEMCARD, HSD_GOBJ_PLINK_MEMCARD, 0);
        HSD_CObj* cobj = HSD_CObjLoadDesc(_p(scene_data)->cameras[0].desc);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_CameraKind, cobj);
        GObj_SetupGXLinkMax(gobj, gobj0_RenderFunc, 14);
        gobj->gxlink_prios = (1 << 19);

        gobj = GObj_Create(HSD_GOBJ_CLASS_MEMCARD, HSD_GOBJ_PLINK_MEMCARD, 0);
        jobj = HSD_JObjLoadJoint(_p(scene_data)->models[0]->joint);

        HSD_JObjSetTranslateX(jobj, jobj_translate[_p(jobj_translate_idx)].x);
        HSD_JObjSetTranslateY(jobj, jobj_translate[_p(jobj_translate_idx)].y);

        HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 19, 0);
        HSD_GObj_SetupProc(gobj, gobj1_Proc, 0);
        gm_8016895C(jobj, _p(scene_data)->models[0], 0);
        HSD_JObjReqAnimAll(jobj, 0.0F);
        HSD_JObjAnimAll(jobj);
    }
}

void lbCardGame_LoadArchive(int jobj_translate_idx)
{
    if (_p(icon_data) == NULL) {
        lbArchive_80016DBC("LbMcGame.", &_p(icon_data), "MemCardIconData", 0);
        lbArchive_80016DBC("NtMemAc", &_p(scene_data),
                           "ScNtcCommon_scene_data", 0);
        _p(jobj_translate_idx) = jobj_translate_idx;
        _p(enable) = true;
    }
}

void lbCardGame_Reset(void)
{
    _p(icon_data) = NULL;
    _p(scene_data) = NULL;
    _p(enable) = false;
    _p(dirty) = false;
    _p(x10) = 0;
    _p(failed) = false;
}

void lbCardGame_Init(void)
{
    ssize_t i;

    _p(probe_status) = CARDProbe(0);
    _p(unk_status) = false;
    _p(card_status) = LbCardStatus_0;
    lbCardGame_Reset();
    manifest[1].data = &gmMainLib_GetCardData()->save_data;

    for (i = 0; i < GM_NAMETAG_BANK_COUNT; i++) {
        manifest[2 + i].data = &gmMainLib_GetNameTagDataBanks()[i];
    }
}
