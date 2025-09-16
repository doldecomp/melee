#include "ftswing.h"

#include "forward.h"

#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
#include "ft/chara/ftCommon/ftpickupitem.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0CD1.h"
#include "ft/ftlipstickswing.h"
#include "ft/ftstarrodswing.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include <baselib/debug.h>

int lbl_803C6D70[6][5] = {
    { 120, 121, 122, -1, 123 }, { 124, 125, 126, -1, 127 },
    { 128, 129, 130, -1, 131 }, { 132, 133, 134, -1, 135 },
    { 136, 137, 138, -1, 139 }, { 140, 141, 142, -1, 143 }
};

void ftCo_FallAerial_Coll(Fighter_GObj* gobj)
{
    ft_800831CC(gobj, ftCo_80096CC8, ft_80082B1C);
}

int fn_800CCEC4(int x);
int fn_800CCEC4(int x)
{
    switch (x) {
    case 12:
        return 0;
    case 11:
        return 1;
    case 13:
        return 2;
    case 24:
        return 3;
    case 22:
        return 4;
    case 23:
        return 5;
    default:
        OSReport("ellegal swing item!!!\n");
        __assert("ftswing.c", 82, "0");
    }
}

int get_anim_id(Fighter* fp, int swing_type, int arg1); // local-only inline
int get_anim_id(Fighter* fp, int swing_type, int arg1)
{
    if (arg1 != 3) {
        return lbl_803C6D70[swing_type][arg1];
    } else {
        switch (fp->kind) {
        case FTKIND_CAPTAIN:
            return swing_type + 341;
        default:
            OSReport("don't have swing42 motion!!!\n");
            HSD_ASSERT(97, 0);
        }
    }
}

void ftCo_Attack_800CCF58(Fighter_GObj* gobj, enum_t arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int swing_type;
    int anim_id;
    float f;
    switch (arg1) {
    case 0:
    case 1:
        RETURN_IF(ftpickupitem_80094790(gobj));
        break;
    }
    HSD_ASSERT(124, fp->item_gobj != NULL);
    swing_type = fn_800CCEC4(itGetKind(fp->item_gobj));
    anim_id = get_anim_id(fp, swing_type, arg1);
    f = Fighter_804D654C[swing_type][arg1];
    switch (swing_type) {
    case 0:
        ftCo_800CD350(gobj, anim_id, arg1, f);
        break;
    case 1:
        ftCo_800CD418(gobj, anim_id, arg1, f);
        break;
    case 2:
        ftCo_800CD4E0(gobj, anim_id, arg1, f);
        break;
    case 3:
        ftCo_800CD5A8(gobj, anim_id, arg1, f);
        break;
    case 4:
        ftCo_800CD82C(gobj, anim_id, arg1, f);
        break;
    case 5:
        ftCo_800CDAB4(gobj, anim_id, arg1, f);
        break;
    }
}
