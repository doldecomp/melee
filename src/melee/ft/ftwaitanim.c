#include <dolphin/mtx/forward.h>

#include "ftwaitanim.h"

#include "ft/ftanim.h"
#include "ft/ftdata.h"
#include "ft/inlines.h"
#include "ftCommon/ftCo_09CB.h"
#include "it/it_26B1.h"

#include <dolphin/mtx/types.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>

bool ftCo_8008A698(ftCo_Fighter* fp)
{
    if (fp->item_gobj != NULL && it_8026B320(fp->item_gobj) != 2) {
        return true;
    }
    return false;
}

void ftCo_8008A6D8(Fighter_GObj* gobj, enum_t anim_id)
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
        if (fp->x590 != 0) {
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

void ftCo_8008A7A8(Fighter_GObj* gobj, IntVec2* arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (arg1 == NULL ||
            (fp->item_gobj != NULL && fp->kind != FTKIND_MEWTWO &&
             fp->kind != FTKIND_FOX))
        {
            ftCo_8008A6D8(gobj, fp->anim_id);
        } else {
            enum_t anim_id;
            do {
                IntVec2* var_r25 = arg1;
                int randi = HSD_Randi(100);
                int max = randi + 1;
                int count = 0;
                while (true) {
                    if (var_r25->x != -1) {
                        count += var_r25->y;
                        if (max <= count) {
                            anim_id = var_r25->x;
                        } else {
                            var_r25 += 1;
                            continue;
                        }
                    } else {
                        OSReport("wait anim data illegal!!\n", max, randi);
                        HSD_ASSERT(86, 0);
                    }
                    break;
                }
            } while (!inlineA0(fp) && fp->anim_id == anim_id);
            ftCo_8008A6D8(gobj, anim_id);
        }
    }
}
