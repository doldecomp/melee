#include <sysdolphin/baselib/fobj.h>

HSD_ObjAllocData fobj_alloc_data;

HSD_ObjAllocData* HSD_FObjGetAllocData(void)
{
    return &fobj_alloc_data;
}

void HSD_FObjInitAllocData(void)
{
    HSD_ObjAllocInit(&fobj_alloc_data, sizeof(HSD_FObj), 4);
}

void HSD_FObjRemove(HSD_FObj* fobj)
{
    if (!fobj)
        return;

    HSD_FObjFree(fobj);
}

void HSD_FObjRemoveAll(HSD_FObj* fobj) 
{
    if (fobj == NULL)
        return;
    HSD_FObjRemoveAll(fobj->next);
    HSD_FObjRemove(fobj);
}

u8 HSD_FObjSetState(HSD_FObj* fobj, u8 state)
{
    if (fobj)
        fobj->flags = (state & 0xF) | (fobj->flags & 0xF0);
    return state;
}

u32 HSD_FObjGetState(HSD_FObj* fobj)
{
    if (!fobj)
        return 0;
    return fobj->flags & 0xF;
}

inline void HSD_FObjReqAnim(HSD_FObj* fobj, f32 startframe)
{
    if (fobj == NULL)
        return;

    fobj->ad = fobj->ad_head;
    fobj->time = (f32)fobj->startframe + startframe;
    fobj->op = 0;
    fobj->op_intrp = 0;
    fobj->flags &= ~0x40;
    fobj->nb_pack = 0;
    fobj->fterm = 0;
    fobj->p0 = 0.f;
    fobj->p1 = 0.f;
    fobj->d0 = 0.f;
    fobj->d1 = 0.f;
    if (fobj != NULL)
        fobj->flags = (1 & 0xF) | (fobj->flags & 0xF0);
}

void HSD_FObjReqAnimAll(HSD_FObj* fobj, f32 startframe)
{
    HSD_FObj* fp;

    if (fobj == NULL)
        return;

    for (fp = fobj; fp != NULL; fp = fp->next) {
        HSD_FObjReqAnim(fp, startframe);
    }
}

inline void FObj_FlushKeyData(HSD_FObj* fobj, void* obj, void (*obj_update)(), f32 rate)
{
    if (fobj->op_intrp == HSD_A_OP_KEY) {
        HSD_FObjInterpretAnim(fobj, obj, obj_update, rate);
    }
}

void HSD_FObjStopAnim(HSD_FObj* fobj, void* obj, void (*obj_update)(), f32 rate) {
    if (fobj == NULL)
        return;
    
    FObj_FlushKeyData(fobj, obj, obj_update, rate);
    
    if (fobj)
        fobj->flags = (0 & 0xF) | (fobj->flags & 0xF0);
}

void HSD_FObjStopAnimAll(HSD_FObj* fobj, void* obj, void (*obj_update)(), f32 rate)
{
    for (; fobj != NULL; fobj = fobj->next) {
        HSD_FObjStopAnim(fobj, obj, obj_update, rate);
    }
}

/*static*/ f32 parseFloat(u8** pos, u8 frac)
{
    union {
        f32 f;
        u32 d;
    } u;
    f32 numer;
    s32 denom;

    if (frac == HSD_A_FRAC_FLOAT) {
        u.d = (s32) ((*pos)++)[0];
        u.d |= ((*pos)++)[0] << 8;
        u.d |= ((*pos)++)[0] << 16;
        u.d |= ((*pos)++)[0] << 24;
        return u.f;
    }

    denom = (1 << (frac & 0x1F));
    switch (frac & 0xE0) {
    case HSD_A_FRAC_S8:
        numer = (s8) (*pos)[0];
        *pos += 1;
        break;
    case HSD_A_FRAC_U8:
        numer = (*pos)[0];
        *pos += 1;
        break;
    case HSD_A_FRAC_S16:
        numer = ((s8) (*pos)[1] << 8) | (*pos)[0];
        *pos += 2;
        break;
    case HSD_A_FRAC_U16:
        numer = ((*pos)[1] << 8) | (*pos)[0];
        *pos += 2;
        break;
    default:
        return 0.0f;
    }
    return numer / denom;
}

/*static*/ s32 parsePackInfo(u8** pos)
{
    u8 val;
    s32 result;
    s32 i;

    val = *(*pos)++;
    result = ((val >> 4) & 7) + 1;
    i = 3;
    if (!(val & 0x80)) {
        return result;
    }
    do {
        val = *(*pos)++;
        result += (val & 0x7F) << i;
        i += 7;
    } while (val & 0x80);
    return result;
}

/*static*/ void FObjLaunchKeyData(HSD_FObj* fobj)
{
    if ((fobj->flags & 0x40) != 0) {
        fobj->op_intrp = fobj->op;
        fobj->flags &= ~0x40;
        fobj->flags |= 0x80;
        fobj->p0 = fobj->p1;
    }
}

void FObjUpdateAnim(HSD_FObj* fobj, void* obj, void (*obj_update)(void*, s32, FObjData*))
{
    f32 phi_f0;
    FObjData fobjdata;

    if (obj_update == NULL) {
        return;
    }
    switch (fobj->op_intrp) {
        case HSD_A_OP_KEY:
            if (fobj->flags & 0x80) {
                fobjdata.fv = fobj->p0;
                fobj->flags &= 0xFFFFFF7F;
            } else {
                return;
            }
            break;
        case HSD_A_OP_CON:
            if (fobj->time >= fobj->fterm) {
                phi_f0 = fobj->p1;
            } else {
                phi_f0 = fobj->p0;
            }
            fobjdata.fv = phi_f0;
            break;
        case HSD_A_OP_LIN:
            if (fobj->flags & 0x20) {
                fobj->flags = fobj->flags & 0xFFFFFFDF;
                if (fobj->fterm != 0) {
                    fobj->d0 = (fobj->p1 - fobj->p0) / fobj->fterm;
                } else {
                    fobj->d0 = 0;
                    fobj->p0 = fobj->p1;
                }
            }
            fobjdata.fv = fobj->d0 * fobj->time + fobj->p0;
            break;
        case HSD_A_OP_SPL0:
        case HSD_A_OP_SPL:
        case HSD_A_OP_SLP:
            if (fobj->fterm != 0) {
                fobjdata.fv = splGetHelmite(1.0 / fobj->fterm,
                    fobj->time, fobj->p0, fobj->p1, fobj->d0, fobj->d1);
            } else {
                fobjdata.fv = fobj->p1;
            }
            break;
        default:
            break;
    }
    obj_update(obj, fobj->obj_type, &fobjdata);
}
