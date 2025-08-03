#include "ftwaitanim.h"

#include "ftdynamics.h"

#include "ft/ftanim.h"
#include "ft/ftdata.h"
#include "ft/inlines.h"
#include "it/it_26B1.h"

#include <dolphin/mtx.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>

bool ftCo_8008A698(Fighter* fp)
{
    if (fp->item_gobj != NULL && it_8026B320(fp->item_gobj) != 2) {
        return true;
    }
    return false;
}

void ftCo_8008A6D8(Fighter_GObj* gobj, s32 anim_id)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (anim_id != -1) {
        struct S_TEMP4* anim = &fp->x24[anim_id];
        u8* blend_data = fp->x28 + (anim_id * 2);
        ftData_80085CD8(fp, fp, anim_id);
        fp->anim_id = anim_id;
        ftCo_8009E7B4(fp, blend_data);
        fp->x3E4_fighterCmdScript.x3EC_scriptCurrent = anim->xC;
        fp->x3E4_fighterCmdScript.x3F0_scriptLoopNum = 0;
        if (fp->x590 != NULL) {
            fp->x594_s32 = anim->x10_animCurrFlags;
            ftAnim_8006EBE8(gobj, 0.0f, 1.0f, *blend_data);
        }
        fp->x3E4_fighterCmdScript.x3E4_scriptEventTimer = 0.0f;
        ftAnim_8006EBA4(gobj);
    }
}

static inline bool inlineA0(Fighter* fp)
{
    if (fp->anim_id == 2 || fp->anim_id == 31) {
        return true;
    }
    return false;
}

static inline enum_t getAnimID(WaitStruct* arg1)
{
    WaitStruct* wait_data = arg1;
    int max = HSD_Randi(100) + 1;
    int count = 0;
    while (wait_data->u.i.x != -1) {
        count += wait_data->u.i.y;
        if (max <= count) {
            return (enum_t) wait_data->u.p.x;
        }
        wait_data += 1;
    }
    OSReport("wait anim data illegal!!\n", max);
    __assert("ftwaitanim.c", 86, "0");
}

void ftCo_8008A7A8(Fighter_GObj* gobj, WaitStruct* arg1)
{
    enum_t anim_id;
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (arg1 == NULL ||
            (fp->item_gobj != NULL && fp->kind != FTKIND_MEWTWO &&
             fp->kind != FTKIND_FOX))
        {
            ftCo_8008A6D8(gobj, fp->anim_id);
        } else {
            do {
                anim_id = getAnimID(arg1);
            } while (!inlineA0(fp) && fp->anim_id == anim_id);
            ftCo_8008A6D8(gobj, anim_id);
        }
    }
}
