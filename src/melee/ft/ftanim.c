#include "ftanim.h"

#include "types.h"

#include "ft/inlines.h"

#include <baselib/aobj.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/object.h>

void ftAnim_8006EBE8(HSD_GObj* gobj, float arg1, float anim_rate,
                     float anim_blend_frames)
{
    static u32 const mask = AOBJ_MASK | COBJ_MASK | DOBJ_MASK | FOBJ_MASK |
                            FOG_MASK | JOBJ_MASK | LOBJ_MASK | POBJ_MASK |
                            ROBJ_MASK | WOBJ_MASK | RENDER_MASK | CHAN_MASK |
                            TEVREG_MASK | CBOBJ_MASK;
    HSD_JObj* root_jobj = GET_JOBJ(gobj);
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* anim_jobj = fp->x8AC_animSkeleton;
    ftAnim_80070758(root_jobj);
    ftAnim_80070758(anim_jobj);
    if (anim_blend_frames == 0) {
        ftAnim_8006FA58(fp, true, fp->x108_costume_joint->child);
        ftAnim_8006FE08(fp, false);
        ftAnim_80070710(root_jobj, arg1);
        if (fp->x594_b1) {
            HSD_ForeachAnim(root_jobj, JOBJ_TYPE, mask, HSD_AObjSetFlags,
                            AOBJ_ARG_AU, AOBJ_LOOP);
        }
        HSD_ForeachAnim(root_jobj, JOBJ_TYPE, mask, HSD_AObjSetRate,
                        AOBJ_ARG_AF, anim_rate);
    } else {
        ftAnim_8006FB88(fp, true, fp->x108_costume_joint->child);
        ftAnim_8006FE08(fp, true);
        ftAnim_80070710(anim_jobj, arg1);
        ftAnim_80070710(root_jobj, arg1);
        if (fp->x594_b1) {
            HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, mask, HSD_AObjSetFlags,
                            AOBJ_ARG_AU, AOBJ_LOOP);
            HSD_ForeachAnim(root_jobj, JOBJ_TYPE, mask, HSD_AObjSetFlags,
                            AOBJ_ARG_AU, AOBJ_LOOP);
        }
        HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, mask, HSD_AObjSetRate,
                        AOBJ_ARG_AF, anim_rate);
        HSD_ForeachAnim(root_jobj, JOBJ_TYPE, mask, HSD_AObjSetRate,
                        AOBJ_ARG_AF, anim_rate);
    }
    fp->x8A4_animBlendFrames = anim_blend_frames;
    fp->x8A8_unk = 0;
}
