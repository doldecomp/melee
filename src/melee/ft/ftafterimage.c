/// @file Creates trailing "afterimages" for swords in motion

#include "ftafterimage.h"

#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/inlines.h>
#include <melee/it/it_26B1.h>
#include <melee/it/item.h>
#include <melee/it/items/itsword.h>
#include <melee/lb/lb_00B0.h>

void ftCo_800C2600(Fighter_GObj* gobj, u32 arg1)
{
    NOT_IMPLEMENTED;
}

void ftCo_800C2FD8(Fighter_GObj* gobj)
{
    Fighter* fp;
    HSD_JObj* jobj;
    struct Fighter_x20B0_t* temp_r30;
    int var_r29;
    struct SwordAttrs* var_r5;
    int var_r0;
    PAD_STACK(0x8);

    fp = GET_FIGHTER(gobj);
    if (fp->x2100 == -1) {
        return;
    }

    temp_r30 = &fp->x20B0[fp->x2101_bits_0to6];
    if (fp->x2101_bits_8) {
        if (fp->item_gobj == NULL) {
            fp->x2100 = -1;
            return;
        }
        if (itGetKind(fp->item_gobj) == It_Kind_Sword) {
            it_802852B8(fp->item_gobj, &fp->x20F8, &fp->x20FC);
            var_r29 = 1;
        } else {
            OSReport("no afterimage item!\n");
            __assert("ftafterimage.c", 0x16D, "0");
        }
        jobj = it_80285314(fp->item_gobj);
    } else {
        switch (fp->kind) {
        case FTKIND_SEAK:
        case FTKIND_NESS:
        case FTKIND_PEACH:
        case FTKIND_POPO:
        case FTKIND_NANA:
        case FTKIND_PIKACHU:
        case FTKIND_SAMUS:
        case FTKIND_YOSHI:
        case FTKIND_PURIN:
        case FTKIND_MEWTWO:
        case FTKIND_LUIGI:
        case FTKIND_ZELDA:
        case FTKIND_DRMARIO:
        case FTKIND_FALCO:
        case FTKIND_PICHU:
        case FTKIND_GAMEWATCH:
        case FTKIND_GANON:
            /// @bug Undefined behavior if the fighter doesn't have a sword!
            break;
        case FTKIND_LINK:
        case FTKIND_CLINK: {
            ftLk_DatAttrs* da = fp->dat_attrs;
            var_r5 = &da->x64;
            break;
        }
        case FTKIND_MARS:
        case FTKIND_EMBLEM: {
            MarsAttributes* da = fp->dat_attrs;
            var_r5 = &da->x78;
            break;
        }
        }
        var_r29 = 0;
        fp->x20F8 = var_r5->x18;
        fp->x20FC = var_r5->x1C;
        jobj = fp->parts[var_r5->x14].joint;
    }
    lb_8000B1CC(jobj, NULL, &temp_r30->x0);
    temp_r30->xC.x = jobj->mtx[0][var_r29];
    temp_r30->xC.y = jobj->mtx[1][var_r29];
    temp_r30->xC.z = jobj->mtx[2][var_r29];
    if (fp->x2101_bits_0to6 == 2) {
        var_r0 = 0;
    } else {
        var_r0 = fp->x2101_bits_0to6 + 1;
    }
    fp->x2101_bits_0to6 = var_r0;
    if (fp->x2100 < 3) {
        fp->x2100++;
    }
}
