#include "itzrshell.h"

#include "itnokonoko.h"
#include "itzgshell.h"

#include "gr/grzakogenerator.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/types.h"

#include <baselib/gobj.h>

ItemStateTable it_803F87F0[] = { { 0, itZrshell_UnkMotion0_Anim, itZrshell_UnkMotion0_Phys, itZrshell_UnkMotion0_Coll },
                                 { 0, itZrshell_UnkMotion1_Anim, itZrshell_UnkMotion1_Phys, itZrshell_UnkMotion1_Coll },
                                 { 0, itZrshell_UnkMotion2_Anim, itZrshell_UnkMotion2_Phys, NULL },
                                 { 1, itZrshell_UnkMotion3_Anim, itZrshell_UnkMotion3_Phys, itZrshell_UnkMotion3_Coll },
                                 { 1, itZrshell_UnkMotion4_Anim, itZrshell_UnkMotion4_Phys, itZrshell_UnkMotion4_Coll },
                                 { 1, itZrshell_UnkMotion6_Anim, itZrshell_UnkMotion6_Phys, itZrshell_UnkMotion6_Coll },
                                 { 0, itZrshell_UnkMotion6_Anim, itZrshell_UnkMotion6_Phys, itZrshell_UnkMotion6_Coll },
                                 { 1, itZrshell_UnkMotion8_Anim, itZrshell_UnkMotion8_Phys, itZrshell_UnkMotion8_Coll },
                                 { 0, itZrshell_UnkMotion8_Anim, itZrshell_UnkMotion8_Phys, itZrshell_UnkMotion8_Coll },
                                 { 0, itZrshell_UnkMotion9_Anim, itZrshell_UnkMotion9_Phys, itZrshell_UnkMotion9_Coll },
                                 { 2, itZrshell_UnkMotion10_Anim, itZrshell_UnkMotion10_Phys, itZrshell_UnkMotion10_Coll },
                                 { 3, itZrshell_UnkMotion11_Anim, itZrshell_UnkMotion11_Phys, itZrshell_UnkMotion11_Coll },
                                 { 4, NULL, NULL, NULL } };

void it_802E02E8(Item_GObj* gobj)
{
    it_802DE040(gobj);
}

void it_802E0308(Item_GObj* gobj)
{
    it_802DE434(gobj);
}

void it_802E0328(Item_GObj* gobj)
{
    it_802DE4FC(gobj);
}

void it_802E0348(Item_GObj* gobj)
{
    it_802DE648(gobj);
}

void it_802E0368(Item_GObj* gobj)
{
    it_802DEEF4(gobj);
}

void it_802E0388(Item_GObj* gobj)
{
    grZakoGenerator_801CACB8(gobj);
}

bool it_802E03A8(Item_GObj* gobj)
{
    return it_802DFC34(gobj);
}

bool it_802E03C8(Item_GObj* gobj)
{
    return it_802DFC58(gobj);
}

bool it_802E03E8(Item_GObj* gobj)
{
    return it_802DFC90(gobj);
}

bool it_802E0408(Item_GObj* gobj)
{
    return it_802DFCB0(gobj);
}

bool it_802E0428(Item_GObj* gobj)
{
    return it_802DFD60(gobj);
}

bool it_802E0448(Item_GObj* gobj)
{
    return it_802DFE40(gobj);
}

void it_802E0468(Item_GObj* gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

Item_GObj* it_802E0488(s32 arg0, Vec3* arg1, s32 arg2)
{
    Vec3 pos = { 0, 0, 0 };
    Item_GObj* it_gp;

    it_gp = it_8027B5B0(It_Kind_ZRShell, arg1, NULL, &pos, 1);
    if (it_gp != NULL) {
        Item* it = it_gp->user_data;
        PAD_STACK(4);

        it->facing_dir = arg2;
        it_8027C56C(it_gp, it->facing_dir);
        it->xDD4_itemVar.zrshell.xE10 = arg0;
        Item_80268E5C(it_gp, 0xC, ITEM_ANIM_UPDATE);
        HSD_JObjAnimAll((HSD_JObj*) it_gp->hsd_obj);
        if (it_802DDA84(it_gp) != false) {
            it_802762B0(it);
            if (it_80277040(it_gp) == false) {
                it_802DE0F0(it_gp);
            } else {
                it_802DEEF4(it_gp);
            }
        } else {
            it_802762BC(it);
            it_802DE320(it_gp);
        }
    }
    return it_gp;
}
