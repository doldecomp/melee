#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/memory.h>

extern void MObjInfoInit(void);

HSD_MObjInfo hsdMObj = { MObjInfoInit };

extern HSD_MObjInfo* default_class;

extern HSD_MObj* current_mobj;

extern char lbl_804D5CE0[8];
extern char lbl_804D5CE8[8];

extern const f32 lbl_804DE430; // 1.0F

void HSD_MObjSetCurrent(HSD_MObj* mobj)
{
    current_mobj = mobj;
}

void HSD_MObjSetFlags(HSD_MObj* mobj, u32 flags)
{
    if (mobj != NULL) 
        mobj->rendermode |= flags;
}

void HSD_MObjClearFlags(HSD_MObj* mobj, u32 flags)
{
    if (mobj != NULL) 
        mobj->rendermode &= ~flags;
}

void HSD_MObjRemoveAnimByFlags(HSD_MObj* mobj, u32 flags)
{
    if (mobj == NULL)
        return;

    if (flags & MOBJ_ANIM) {
        HSD_AObjRemove(mobj->aobj);
        mobj->aobj = NULL;
    }
    if (flags & TOBJ_ANIM) {
        HSD_TObjRemoveAnimAll(mobj->tobj);
    }
}

void HSD_MObjAddAnim(HSD_MObj* mobj, HSD_MatAnim* matanim)
{
    if (mobj == NULL)
        return;

    if (matanim != NULL) {
        if (mobj->aobj != NULL) {
            HSD_AObjRemove(mobj->aobj);
        }
        mobj->aobj = HSD_AObjLoadDesc(matanim->aobjdesc);
        HSD_TObjAddAnimAll(mobj->tobj, matanim->texanim);
    }
}

void HSD_MObjReqAnimByFlags(HSD_MObj* mobj, f32 startframe, u32 flags)
{
    if (mobj == NULL)
        return;
    if (flags & MOBJ_ANIM) {
        HSD_AObjReqAnim(mobj->aobj, startframe);
    }
    HSD_TObjReqAnimAllByFlags(mobj->tobj, startframe, flags);
}

void HSD_MObjReqAnim(HSD_MObj *mobj, f32 startframe)
{
    HSD_MObjReqAnimByFlags(mobj, startframe, ALL_ANIM);
}

static void MObjUpdateFunc(void* obj, u32 type, FObjData* val)
{
    HSD_MObj* mobj = obj;

    if (mobj == NULL)
        return;

    switch (type) {
    case HSD_A_M_AMBIENT_R:
        mobj->mat->ambient.r = (u8)(255.0 * val->fv);
        break;
    case HSD_A_M_AMBIENT_G:
        mobj->mat->ambient.g = (u8)(255.0 * val->fv);
        break;
    case HSD_A_M_AMBIENT_B:
        mobj->mat->ambient.b = (u8)(255.0 * val->fv);
        break;
    case HSD_A_M_DIFFUSE_R:
        mobj->mat->diffuse.r = (u8)(255.0 * val->fv);
        break;
    case HSD_A_M_DIFFUSE_G:
        mobj->mat->diffuse.g = (u8)(255.0 * val->fv);
        break;
    case HSD_A_M_DIFFUSE_B:
        mobj->mat->diffuse.b = (u8)(255.0 * val->fv);
        break;
    case HSD_A_M_ALPHA:
        mobj->mat->alpha = lbl_804DE430 - val->fv;
        break;
    case HSD_A_M_SPECULAR_R:
        mobj->mat->specular.r = (u8)(255.0 * val->fv);
        break;
    case HSD_A_M_SPECULAR_G:
        mobj->mat->specular.g = (u8)(255.0 * val->fv);
        break;
    case HSD_A_M_SPECULAR_B:
        mobj->mat->specular.b = (u8)(255.0 * val->fv);
        break;
    case HSD_A_M_PE_REF0:
        if (mobj->pe) {
            mobj->pe->ref0 = (u8)(255.0 * val->fv);
        }
        break;
    case HSD_A_M_PE_REF1:
        if (mobj->pe) {
            mobj->pe->ref1 = (u8)(255.0 * val->fv);
        }
        break;
    case HSD_A_M_PE_DSTALPHA:
        if (mobj->pe) {
            mobj->pe->dst_alpha = (u8)(255.0 * val->fv);
        }
        break;
    }
}

void HSD_MObjAnim(HSD_MObj* mobj)
{
    if (mobj == NULL)
        return;
    HSD_AObjInterpretAnim(mobj->aobj, mobj, MObjUpdateFunc);
    HSD_TObjAnimAll(mobj->tobj);
}

/*static*/ int MObjLoad(HSD_MObj* mobj, HSD_MObjDesc* desc)
{
    mobj->rendermode = desc->rendermode;
    mobj->tobj = HSD_TObjLoadDesc(desc->texdesc);
    mobj->mat = HSD_MaterialAlloc();
    memcpy(mobj->mat, desc->mat, sizeof(HSD_Material));
    mobj->rendermode |= RENDER_TOON;
    if (desc->pedesc != NULL) {
        mobj->pe = hsdAllocMemPiece(sizeof(HSD_PEDesc));
        memcpy(mobj->pe, desc->pedesc, sizeof(HSD_PEDesc));
    }
    mobj->aobj = NULL;
    return 0;
}

HSD_MObj* HSD_MObjLoadDesc(HSD_MObjDesc* mobjdesc)
{
    if (mobjdesc) {
        HSD_MObj* mobj;
        HSD_ClassInfo* info;

        if (!mobjdesc->class_name || !(info = hsdSearchClassInfo(mobjdesc->class_name))) {
            mobj = HSD_MObjAlloc();
        } else {
            mobj = hsdNew(info);
            if (mobj == NULL) {
                __assert(lbl_804D5CE0, 353, lbl_804D5CE8);
            }
        }

        HSD_MOBJ_METHOD(mobj)->load(mobj, mobjdesc);
        HSD_MObjCompileTev(mobj);

        return mobj;
    } else {
        return NULL;
    }
}
