#include <sysdolphin/baselib/mobj.h>

#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/texp.h>

static HSD_MObjInfo* default_class;
static HSD_MObj* current_mobj;
HSD_TObj* tobj_shadows;
HSD_TObj* tobj_toon;

static void MObjInfoInit(void);
HSD_MObjInfo hsdMObj = { MObjInfoInit };

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
        mobj->mat->alpha = 1.0F - val->fv;
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

static int MObjLoad(HSD_MObj* mobj, HSD_MObjDesc* desc)
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
            assert_line(353, mobj);
        }

        HSD_MOBJ_METHOD(mobj)->load(mobj, mobjdesc);
        HSD_MObjCompileTev(mobj);

        return mobj;
    } else {
        return NULL;
    }
}

HSD_TExp* MObjMakeTExp(HSD_MObj* mobj, HSD_TObj* tobj_top, HSD_TExp** list)
{
    HSD_TExp* sp3C;
    HSD_TExp* texptev_3;
    HSD_TExp* sp38;
    HSD_TExp* result;
    HSD_TExp* sp30;
    HSD_TExp* texptev;
    HSD_TExp* texptev_2;
    HSD_TExp* texptev_4;
    HSD_TExp* texptev_5;
    HSD_TExp* texptev_6;
    HSD_TExp* texptev_7;
    HSD_TObj* cur;
    HSD_TObj* cur_2;
    HSD_TObj* cur_3;
    HSD_TObj* tobj;
    HSD_TObj* cur_4;
    u32 flags;
    u32 unused[5];

    tobj = NULL;
    flags = 0;
    assert_line(0x1A0, list);
    *list = NULL;
    cur_4 = tobj_top;
    while (cur_4 != NULL) {
        if ((cur_4->flags & 0xF) == 4) {
            tobj = cur_4;
        }
        cur_4 = cur_4->next;
    }
    if (mobj->rendermode & 2) {
        texptev_2 = HSD_TExpTev(list);
        HSD_TExpOrder(texptev_2, NULL, 4);
        HSD_TExpColorOp(texptev_2, 0, 0, 0, 1);
        HSD_TExpColorIn(texptev_2, 7, NULL, 7, NULL, 7, NULL, 1, -2);
        HSD_TExpAlphaOp(texptev_2, 0, 0, 0, 1);
        HSD_TExpAlphaIn(texptev_2, 7, NULL, 7, NULL, 7, NULL, 5, -2);
        sp3C = texptev_2;
        sp30 = texptev_2;
    } else {
        HSD_TExp* temp_r25 = HSD_TExpCnst(&mobj->mat->diffuse, 1, 0, list);
        HSD_TExp* temp_r26 = HSD_TExpCnst(&mobj->mat->alpha, 6, 3, list);
        texptev_3 = HSD_TExpTev(list);
        HSD_TExpColorOp(texptev_3, 0, 0, 0, 1);
        HSD_TExpColorIn(texptev_3, 7, NULL, 7, NULL, 7, 0, 1, temp_r25);
        HSD_TExpAlphaOp(texptev_3, 0, 0, 0, 1);
        HSD_TExpAlphaIn(texptev_3, 7, 0, 7, NULL, 7, 0, 6, temp_r26);
        sp3C = texptev_3;
        sp30 = texptev_3;
    }
    cur = tobj_top;
    while (cur != NULL) {
        if ((cur->flags & 0x50) && cur->id != 0xFF) {
            HSD_TOBJ_METHOD(cur)->make_texp(cur, 0x50, 0, &sp3C, &sp30, list);
        }
        cur = cur->next;
    }
    flags |= 0x50;
    if (mobj->rendermode & 4) {
        texptev_4 = HSD_TExpTev(list);
        if (tobj != NULL) {
            HSD_TExpOrder(texptev_4, tobj, 4);
            HSD_TExpColorOp(texptev_4, 0, 0, 0, 1);
            HSD_TExpColorIn(texptev_4, 7, NULL, 1, sp3C, 1, -1, 7, NULL);
        } else {
            HSD_TExpOrder(texptev_4, NULL, 4);
            HSD_TExpColorOp(texptev_4, 0, 0, 0, 1);
            HSD_TExpColorIn(texptev_4, 7, NULL, 1, sp3C, 1, -2, 7, NULL);
        }
        sp3C = texptev_4;
        HSD_TExpAlphaOp(texptev_4, 0, 0, 0, 1);
        HSD_TExpAlphaIn(texptev_4, 7, 0, 5, sp30, 5, -2, 7, 0);
        sp30 = texptev_4;
    }
    if (mobj->rendermode & 8) {
        HSD_TExp* temp_r27 = HSD_TExpCnst(&mobj->mat->specular, 1, 0, list);
        texptev_5 = HSD_TExpTev(list);
        HSD_TExpColorOp(texptev_5, 0, 0, 0, 1);
        HSD_TExpColorIn(texptev_5, 7, NULL, 7, NULL, 7, NULL, 1, temp_r27);
        sp38 = texptev_5;
        cur_2 = tobj_top;
        while (cur_2 != NULL) {
            if ((cur_2->flags & 0x20) && cur_2->id != 0xFF) {
                HSD_TOBJ_METHOD(cur_2)->make_texp(cur_2, 0x20, flags, &sp38, &sp30, list);
            }
            cur_2 = cur_2->next;
        }
        flags |= 0x20;
        texptev_6 = HSD_TExpTev(list);
        HSD_TExpOrder(texptev_6, NULL, 5);
        HSD_TExpColorOp(texptev_6, 0, 0, 0, 1);
        HSD_TExpColorIn(texptev_6, 7, NULL, 1, sp38, 1, -2, 7, NULL);
        sp38 = texptev_6;
        texptev_7 = HSD_TExpTev(list);
        HSD_TExpColorOp(texptev_7, 0, 0, 0, 1);
        HSD_TExpColorIn(texptev_7, 1, sp38, 7, NULL, 7, NULL, 1, sp3C);
        sp3C = texptev_7;
    }
    cur_3 = tobj_top;
    result = sp3C;
    while (cur_3 != NULL) {
        if ((cur_3->flags & 0x80) && cur_3->id != 0xFF) {
            HSD_TOBJ_METHOD(cur_3)->make_texp(cur_3, 0x80, flags, &result, &sp30, list);
        }
        cur_3 = cur_3->next;
    }
    if (result != sp30 || HSD_TExpGetType(result) != HSD_TE_TEV || HSD_TExpGetType(sp30) != HSD_TE_TEV) {
        texptev = HSD_TExpTev(list);
        HSD_TExpColorOp(texptev, 0, 0, 0, 1);
        HSD_TExpColorIn(texptev, 7, NULL, 7, NULL, 7, NULL, 1, result);
        HSD_TExpAlphaOp(texptev, 0, 0, 0, 1);
        HSD_TExpAlphaIn(texptev, 7, NULL, 7, NULL, 7, NULL, 5, sp30);
        return texptev;
    }
    return result;
}

void HSD_MObjCompileTev(HSD_MObj* mobj)
{
    HSD_TObj* tobj;
    HSD_TObj** tobj_list;
    HSD_TExp* texp;

    tobj_list = NULL;
    if (mobj != NULL) {
        if (mobj->tevdesc != NULL) {
            HSD_TExpFreeTevDesc(mobj->tevdesc);
            mobj->tevdesc = NULL;
        }
        if (mobj->texp != NULL) {
            HSD_TExpFreeList(mobj->texp, 7, 1);
            mobj->texp = NULL;
        }
        tobj = mobj->tobj;
        if (mobj->rendermode & 0x04000000) {
            if (tobj_shadows != NULL) {
                tobj_list = &tobj;
                while (*tobj_list != NULL) {
                    tobj_list = &(*tobj_list)->next;
                }
                *tobj_list = tobj_shadows;
            }
        }
        if (mobj->rendermode & 0x1000) {
            if (tobj_toon != NULL && tobj_toon->imagedesc != NULL) {
                tobj_toon->next = tobj;
                tobj = tobj_toon;
            }
        }
        HSD_TObjAssignResources(tobj);
        texp = HSD_MOBJ_METHOD(mobj)->make_texp(mobj, tobj, &mobj->texp);
        HSD_TExpCompile(texp, &mobj->tevdesc, &mobj->texp);
        if (tobj_list != NULL) {
            *tobj_list = NULL;
        }
    }
}

#pragma push
#pragma force_active on
static char unused1[] = "hsdIsDescendantOf(info, &hsdMObj)";
#pragma pop

void MObjSetupTev(HSD_MObj* mobj, HSD_TObj* tobj, u32 arg2)
{
    assert_line(0x270, mobj->tevdesc);
    HSD_TExpSetupTev(mobj->tevdesc, mobj->texp);
    HSD_TObjSetupVolatileTev(tobj, arg2);
}

void HSD_MObjSetup(HSD_MObj* mobj, u32 rendermode)
{
    HSD_TObj* tobj;
    HSD_TObj** var_r29;

    HSD_StateInitTev();
    rendermode = mobj->rendermode;
    HSD_SetMaterialColor(mobj->mat->ambient, mobj->mat->diffuse, mobj->mat->specular,
                         mobj->mat, mobj->mat->alpha);
    if (rendermode & 8) {
        HSD_SetMaterialShininess(mobj->mat, mobj->mat->shininess);
    }
    var_r29 = NULL;
    tobj = mobj->tobj;
    if ((rendermode & 0x4000000) && tobj_shadows != NULL) {
        var_r29 = &tobj;
        while (*var_r29 != NULL) {
            var_r29 = &(*var_r29)->next;
        }
        *var_r29 = tobj_shadows;
    }
    if ((rendermode & 0x1000) && tobj_toon != NULL && tobj_toon->imagedesc != NULL) {
        tobj_toon->next = tobj;
        tobj = tobj_toon;
    }
    HSD_TObjSetup(tobj);
    HSD_TObjSetupTextureCoordGen(tobj);
    HSD_MOBJ_METHOD(mobj)->setup_tev(mobj, tobj, rendermode);
    HSD_SetupRenderModeWithCustomPE(rendermode, mobj->pe);
    if (var_r29 != NULL) {
        *var_r29 = NULL;
    }
}

void HSD_MObjUnset(HSD_MObj* mobj, u32 rendermode)
{
    HSD_TObjSetup(NULL);
}

static HSD_TObjDesc tobj_toon_desc = {
    NULL,
    NULL,
    GX_TEXMAP7,
    GX_TG_COLOR0,
    { 0.0F, 0.0F, 0.0F },
    { 0.0F, 0.0F, 0.0F },
    { 0.0F, 0.0F, 0.0F },
    GX_CLAMP,
    GX_CLAMP,
    0,
    0,
    TEX_COORD_TOON,
    1.0F,
    GX_LINEAR,
    0,
    NULL,
    NULL
};

void HSD_MObjSetToonTextureImage(HSD_ImageDesc* imagedesc)
{
    if (tobj_toon == NULL) {
        tobj_toon_desc.imagedesc = imagedesc;
        tobj_toon = HSD_TObjLoadDesc(&tobj_toon_desc);
        if (tobj_toon == NULL) {
            OSReport("cannot allocate tobj for toon.");
            __assert(__FILE__, 0x2F8, "tobj_toon");
        }
    }
    tobj_toon->imagedesc = imagedesc;
}

void HSD_MObjSetDiffuseColor(HSD_MObj* mobj, u8 r, u8 g, u8 b)
{
    mobj->mat->diffuse.r = r;
    mobj->mat->diffuse.g = g;
    mobj->mat->diffuse.b = b;
}

void HSD_MObjSetAlpha(HSD_MObj* mobj, f32 alpha)
{
    mobj->mat->alpha = alpha;
}

HSD_TObj* HSD_MObjGetTObj(HSD_MObj* mobj)
{
    if (mobj == NULL) {
        return NULL;
    }
    return mobj->tobj;
}

void HSD_MObjRemove(HSD_MObj* mobj)
{
    if (mobj != NULL) {
        HSD_CLASS_METHOD(mobj)->release((HSD_Class*) mobj);
        HSD_CLASS_METHOD(mobj)->destroy((HSD_Class*) mobj);
    }
}

HSD_MObj* HSD_MObjAlloc(void)
{
    HSD_MObj* mobj = hsdNew((HSD_ClassInfo*) (default_class != NULL ? default_class : &hsdMObj));
    assert_line(0x393, mobj);
    return mobj;
}

HSD_Material* HSD_MaterialAlloc(void)
{
    HSD_Material* mat = hsdAllocMemPiece(sizeof(HSD_Material));
    assert_line(0x3AF, mat);
    memset(mat, 0, sizeof(HSD_Material));
    mat->alpha = 1.0F;
    return mat;
}

void HSD_MObjAddShadowTexture(HSD_TObj* tobj)
{
    HSD_TObj* cur;
    assert_line(0x3DE, tobj);
    for (cur = tobj_shadows; cur != NULL; cur = cur->next) {
        if (cur == tobj) {
            return;
        }
    }
    tobj->next = tobj_shadows;
    tobj_shadows = tobj;
}

#pragma push
#pragma force_active on
static char unused2[] = "mobj->rendermode&RENDER_SPECULAR";
#pragma pop

void HSD_MObjDeleteShadowTexture(HSD_TObj* tobj)
{
    if (tobj != NULL) {
        HSD_TObj** cur = &tobj_shadows;
        while (*cur != NULL) {
            if (*cur == tobj) {
                *cur = tobj->next;
                tobj->next = NULL;
                return;
            }
            cur = &(*cur)->next;
        }
    } else {
        HSD_TObj* next;
        for (next = NULL; tobj_shadows != NULL; tobj_shadows = next) {
            next = tobj_shadows->next;
            tobj_shadows->next = NULL;
        }
    }
}

static void MObjRelease(HSD_Class* o)
{
    HSD_MObj* mobj = HSD_MOBJ(o);

    HSD_AObjRemove(mobj->aobj);
    hsdFreeMemPiece(mobj->mat, sizeof(HSD_Material));
    HSD_TObjRemoveAll(mobj->tobj);

    if (mobj->tevdesc != NULL) {
        HSD_TExpFreeTevDesc(mobj->tevdesc);
    }
    if (mobj->texp != NULL) {
        HSD_TExpFreeList(mobj->texp, HSD_TE_ALL, 1);
    }
    if (mobj->pe != NULL) {
        hsdFreeMemPiece(mobj->pe, sizeof(HSD_PEDesc));
    }
    HSD_PARENT_INFO(&hsdMObj)->release(o);
}

static void MObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    if (info == HSD_CLASS_INFO(&hsdMObj)) {
        tobj_toon = NULL;
        tobj_shadows = NULL;
    }
    HSD_PARENT_INFO(&hsdMObj)->amnesia(info);
}

static void MObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdMObj), HSD_CLASS_INFO(&hsdClass),
                     "sysdolphin_base_library", "hsd_mobj",
                     sizeof(HSD_MObjInfo), sizeof(HSD_MObj));

    HSD_CLASS_INFO(&hsdMObj)->release = MObjRelease;
    HSD_CLASS_INFO(&hsdMObj)->amnesia = MObjAmnesia;
    HSD_MOBJ_INFO(&hsdMObj)->setup = HSD_MObjSetup;
    HSD_MOBJ_INFO(&hsdMObj)->unset = HSD_MObjUnset;
    HSD_MOBJ_INFO(&hsdMObj)->load = MObjLoad;
    HSD_MOBJ_INFO(&hsdMObj)->make_texp = MObjMakeTExp;
    HSD_MOBJ_INFO(&hsdMObj)->setup_tev = MObjSetupTev;
}
