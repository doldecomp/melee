#include "ft_0892.h"

#include "ft/chara/ftFox/ftFx_AppealS.h"
#include "ft/fighter.h"
#include "ft/inlines.h"
#include "it/it_26B1.h"
#include "pl/plattack.h"
#include "pl/pltrick.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <MSL/math_ppc.h>
#include <MSL/trigf.h>

void lbBgFlash_80020E38(HSD_JObj*, Vec3*, f32, f32, f32);
void lbBgFlash_80021410(IKState*);

/// Local struct with bitfields - reversed order for MWCC big-endian
typedef struct {
    s32 x0;
    s32 x4;
    float x8;
    s32 xC;
    u8 x10_b7 : 1; // bit 7 (MSB)
    u8 x10_b6 : 1;
    u8 x10_b5 : 1;
    u8 x10_b4 : 1;
    u8 x10_b3 : 1;
    u8 x10_b2 : 1;
    u8 x10_b1 : 1;
    u8 x10_b0 : 1; // bit 0 (LSB)
    u8 x11_b7 : 1;
    u8 x11_b6 : 1;
    u8 x11_b5 : 1;
    u8 x11_b4 : 1;
    u8 x11_b3 : 1;
    u8 x11_b2 : 1;
    u8 x11_b1 : 1;
    u8 x11_b0 : 1;
} UnkStruct89768;

/// #ft_800892D4

void ft_800892D4(Fighter* arg0)
{
    union Struct2070 spC;

    spC.x2070_int = 0;
    arg0->dmg.x18d4 = *(UnkPlBonusBits*) &spC;
    arg0->x2070.x2070_int = *(s32*) &arg0->dmg.x18d4;
    *(s32*) &arg0->x2074.x2074_vec.x = 0;
    *(s32*) &arg0->x2074.x2074_vec.y = 0;
    *(f32*) &arg0->x2074.x207C.x = 0.0f;
    arg0->x2074.x207C.y = 6;
    arg0->x2074.x2084_b0 = 0;
    arg0->x2074.x2085_b3 = 0;
    arg0->x2074.x2084_b1 = 0;
    arg0->x2074.x2084_b2 = 0;
    arg0->x2074.x2084_b3 = 0;
    arg0->x2074.x2084_b4 = 0;
    arg0->x2074.x2084_b5 = 0;
    arg0->x2074.x2084_b6 = 0;
    arg0->x2074.x2084_b7 = 0;
    arg0->x2074.x2085_b0 = 0;
    arg0->x2074.x2085_b1 = 0;
    arg0->x2074.x2085_b2 = 0;
    arg0->x2074.x2085_b4 = 0;
    arg0->dmg.x18d8.x0 = 0;
    arg0->dmg.x18d8.x4 = 0;
    arg0->dmg.x18d8.kb_applied1 = 0.0f;
    arg0->dmg.x18d8.xC = 6;
    arg0->dmg.x18d8.x10_b0 = 0;
    arg0->dmg.x18d8.x11_b3 = 0;
    arg0->dmg.x18d8.x10_b1 = 0;
    arg0->dmg.x18d8.x10_b2 = 0;
    arg0->dmg.x18d8.x10_b3 = 0;
    arg0->dmg.x18d8.x10_b4 = 0;
    arg0->dmg.x18d8.x10_b5 = 0;
    arg0->dmg.x18d8.x10_b6 = 0;
    arg0->dmg.x18d8.x10_b7 = 0;
    arg0->dmg.x18d8.x11_b0 = 0;
    arg0->dmg.x18d8.x11_b1 = 0;
    arg0->dmg.x18d8.x11_b2 = 0;
    arg0->dmg.x18d8.x11_b4 = 0;
    arg0->dmg.x18ec_instancehitby = 0;
    arg0->x2074.x2088 = 0;
}

/// #ft_80089460

void ft_80089460(Fighter* fp)
{
    *(s32*) &fp->x2074.x2074_vec.x = 0;
    *(s32*) &fp->x2074.x2074_vec.y = 0;
    *(f32*) &fp->x2074.x207C.x = 0.0f;
    fp->x2074.x207C.y = 6;
    fp->x2074.x2084_b0 = 0;
    fp->x2074.x2085_b3 = 0;
    fp->x2074.x2084_b1 = 0;
    fp->x2074.x2084_b2 = 0;
    fp->x2074.x2084_b3 = 0;
    fp->x2074.x2084_b4 = 0;
    fp->x2074.x2084_b5 = 0;
    fp->x2074.x2084_b6 = 0;
    fp->x2074.x2084_b7 = 0;
    fp->x2074.x2085_b0 = 0;
    fp->x2074.x2085_b1 = 0;
    fp->x2074.x2085_b2 = 0;
    fp->x2074.x2085_b4 = 0;
    *(s32*) &fp->x2074.x2074_vec.x = (s32) fp->dmg.x1830_percent;
    if (fp->is_metal) {
        fp->x2074.x2084_b1 = 1;
    }
    if (fp->x197C != NULL) {
        fp->x2074.x2084_b2 = 1;
    }
    if (fp->x221D_b6) {
        fp->x2074.x2084_b3 = 1;
    }
    if (fp->x2226_b4) {
        fp->x2074.x2084_b4 = 1;
    }
    if (fp->x2220_b5) {
        fp->x2074.x2084_b5 = 1;
    }
    if (fp->x2220_b6) {
        fp->x2074.x2084_b6 = 1;
    }
}

// TODO: is arg1 not just a Struct2070?
void ft_800895E0(Fighter* fp, int arg1)
{
    union Struct2070 val;
    union Struct2070 sp18;
    union Struct2070 sp14;
    union Struct2070 spC;

    val = *(union Struct2070*) &arg1;
    if (val.x2073 == 0 || val.x2073 != fp->x2070.x2073) {
        fp->x2074.x2088 = plAttack_80037B08();
    }
    if (fp->kind == FTKIND_LUIGI && val.x2073 == 0x71) {
        sp18.x2070_int = 0x240063;
        val = sp18;
    }
    if (val.x2073 == 0x62) {
        if (fp->item_gobj != NULL && it_8026B6C8(fp->item_gobj) != 0) {
            sp14.x2070_int = 0x44003D;
            val = sp14;
        }
    }
    fp->x2070.x2070_int = val.x2070_int;
    ft_80089768(&fp->x2074.x2074_vec);
    *(s32*) &fp->x2074.x2074_vec.x = (s32) fp->dmg.x1830_percent;
    if (fp->is_metal) {
        fp->x2074.x2084_b1 = 1;
    }
    if (fp->x197C != NULL) {
        fp->x2074.x2084_b2 = 1;
    }
    if (fp->x221D_b6) {
        fp->x2074.x2084_b3 = 1;
    }
    if (fp->x2226_b4) {
        fp->x2074.x2084_b4 = 1;
    }
    if (fp->x2220_b5) {
        fp->x2074.x2084_b5 = 1;
    }
    if (fp->x2220_b6) {
        fp->x2074.x2084_b6 = 1;
    }
}

void ft_80089768(Vec2* ptr)
{
    UnkStruct89768* s = (UnkStruct89768*) ptr;
    s->x0 = 0;
    s->x4 = 0;
    s->x8 = 0.0f;
    s->xC = 6;
    s->x10_b7 = 0;
    s->x11_b4 = 0;
    s->x10_b6 = 0;
    s->x10_b5 = 0;
    s->x10_b4 = 0;
    s->x10_b3 = 0;
    s->x10_b2 = 0;
    s->x10_b1 = 0;
    s->x10_b0 = 0;
    s->x11_b7 = 0;
    s->x11_b6 = 0;
    s->x11_b5 = 0;
    s->x11_b3 = 0;
}

void ft_80089824(Fighter_GObj* gobj)
{
    Fighter* fp;
    s32 temp;

    fp = GET_FIGHTER(gobj);
    ((s32*) &temp)[0] = fp->x2070.x2070_int;
    fp->x2070.x2070_int = ((s32*) &temp)[0];
    ft_80089460(fp);
    fp->x2074.x2088 = plAttack_80037B08();
    pl_80037C60(gobj, 0);
}

union Struct2070* ft_80089884(Fighter_GObj* gobj)
{
    return &GET_FIGHTER(gobj)->x2070;
}

UnkPlBonusBits* ft_80089890(Fighter_GObj* gobj)
{
    return &GET_FIGHTER(gobj)->dmg.x18d4;
}

u16 ft_8008989C(Fighter_GObj* gobj)
{
    return GET_FIGHTER(gobj)->dmg.x18ec_instancehitby;
}

struct Struct2074* ft_800898A8(Fighter_GObj* gobj)
{
    return &GET_FIGHTER(gobj)->x2074;
}

ft_800898B4_t* ft_800898B4(Fighter_GObj* gobj)
{
    return &GET_FIGHTER(gobj)->dmg.x18d8;
}

bool ft_800898C0(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if ((ft->x2070.x2073 == 113 || ft->x2070.x2073 == 114 ||
         ft->x2070.x2073 == 99) ||
        ftFx_AppealS_CheckIfUsed(ft))
    {
        return true;
    }
    return false;
}

s32 ft_80089914(HSD_GObj* gobj, int msid)
{
    Fighter* fp = gobj->user_data;

    if (msid < ftCo_MS_AttackS3Hi || msid > ftCo_MS_AttackS4LwS) {
        return false;
    }

    if (fp->kind == FTKIND_FOX) {
        if ((u32) (msid - ftCo_MS_AttackS3LwS) <= 2) {
            return false;
        }
    }

    if (fp->kind == FTKIND_FALCO) {
        if ((u32) (msid - ftCo_MS_AttackS3LwS) <= 2) {
            return false;
        }
    }

    if (fp->kind == FTKIND_MEWTWO) {
        if (msid == ftCo_MS_AttackS3S) {
            return false;
        }
    }

    return true;
}
