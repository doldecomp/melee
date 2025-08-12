#include "ft/ft_0C88.h"

#include <placeholder.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_0C31.h"
#include "ft/ftcolanim.h"
#include "ft/ftmetal.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "lb/lbrefract.h"

void ftCo_800C884C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2040 = HSD_ObjAlloc(&fighter_x2040_alloc_data);
    ftParts_80074148();
    ft_800C85B8(gobj);
    ftParts_80074170();
}

void ftCo_800C88A0(Fighter* fp)
{
    fp->x2226_b4 = false;
    fp->x2226_b5 = false;
    fp->smash_attrs.x2134_vibrateFrame = 0;
    fp->x2030 = 0;
    fp->x2226_b7 = false;
}

static inline void ftCo_800C88D4_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2226_b5 = true;
    fp->x2226_b7 = false;
    fn_800C8B1C(gobj);
    ft_800C80A4(fp);
    lbRefract_80022BB8();
    fp->x221F_b2 = true;
}

void ftCo_800C88D4(Fighter_GObj* gobj, int arg1, bool arg2)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->x2030 = arg1;
    if (!fp->x2226_b4 || fp->x2226_b7) {
        fp->x2226_b4 = true;
        ftCo_800C88D4_inline(gobj);

        if (arg2) {
            ftCo_800C8B2C(fp, 0x7C, 0);
        } else {
            ft_800C0098(fp);
        }
    }
}

void ftCo_800C89A0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCo_800C88A0(fp);
    fp->x2226_b4 = fp->x2226_b3;
    if (fp->x2226_b4) {
        ftCo_800C88D4_inline(gobj);
    }
    ft_800C0098(fp);
}

void ftCo_800C8A64(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->x2030 = 0;
    if (!fp->x2226_b3) {
        ftCo_800C88A0(fp);
        ft_800C0098(fp);
        ft_800C8170(fp);
        lbRefract_80022BD0();
        fp->x221F_b2 = false;
    }
}

void ftCo_800C8AF0(Fighter* fp)
{
    if (fp->x2226_b5) {
        lbRefract_800225D4();
    }
}

void fn_800C8B1C(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->smash_attrs.x2134_vibrateFrame = 0;
}

bool ftCo_800C8B2C(Fighter* gobj, int arg1, bool arg2)
{
    if (!gobj->x2226_b6) {
        return ftCo_800BFFD0(gobj, arg1, arg2);
    }
    return false;
}

void ftCo_800C8B60(Fighter* fp, int arg1, s8 arg2)
{
    fp->x2226_b5 = arg1;
    fp->smash_attrs.x2134_vibrateFrame = arg2;
}
