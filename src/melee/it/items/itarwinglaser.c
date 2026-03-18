#include "itarwinglaser.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/efsync.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"

static void itArwinglaser_UnkMotion2_Anim(Item_GObj*);
static void itArwinglaser_UnkMotion3_Anim(Item_GObj*);

void it_802E79C8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    switch (ip->xDD4_itemVar.arwinglaser.xE38) {
    case 0:
    case 2: {
        Item* ip2;
        Item* ip3;

        ip->xDD4_itemVar.arwinglaser.xDF4 = NULL;

        if (ip->xDD4_itemVar.arwinglaser.xE40 != NULL) {
            ip2 = GET_ITEM(ip->xDD4_itemVar.arwinglaser.xE40);
            if (ip2->xDD4_itemVar.arwinglaser.xDF4 == gobj) {
                ip2->xDD4_itemVar.arwinglaser.xDF4 = NULL;
            }
        }
        ip->xDD4_itemVar.arwinglaser.xE40 = NULL;

        if (ip->xDD4_itemVar.arwinglaser.xE44 != NULL) {
            ip3 = GET_ITEM(ip->xDD4_itemVar.arwinglaser.xE44);
            if (ip3->xDD4_itemVar.arwinglaser.xDF4 == gobj) {
                ip3->xDD4_itemVar.arwinglaser.xDF4 = NULL;
            }
        }
        ip->xDD4_itemVar.arwinglaser.xE44 = NULL;
        return;
    }
    case 1:
        return;
    }
}

void it_802E7A4C(Item_GObj* gobj)
{
    Item* item;
    int unused[2];

    item = GET_ITEM(gobj);
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, item->xDD4_itemVar.arwinglaser.xE38, 2);
}

static void itArwinglaser_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    ip->xDD4_itemVar.arwinglaser.xE24 = ip->xDD4_itemVar.arwinglaser.xE18;
    if (it_80272C6C(gobj) == 0) {
        ip->xDD4_itemVar.arwinglaser.xE30 = 1;
    }
    it_80273130(gobj);
}

static void itArwinglaser_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    ip->xDD4_itemVar.arwinglaser.xE24 = ip->xDD4_itemVar.arwinglaser.xE18;
    ip->xDD4_itemVar.arwinglaser.xE30 = 1;
    it_80273130(gobj);
}

bool it_802E838C(Item_GObj* gobj)
{
    Vec3 sp10;
    Item* ip = GET_ITEM(gobj);

    lb_8000B1CC(ip->xBBC_dynamicBoneTable->bones[4], NULL, &sp10);
    ip->xDD4_itemVar.arwinglaser.xE18 = sp10;
    efSync_Spawn(0x40E, gobj, &sp10);
    Item_8026AE84(ip, 0x74, 0x7FU, 0x40U);
    return true;
}

bool it_802E8418(Item_GObj* gobj)
{
    return true;
}

bool it_802E8784(Item_GObj* gobj)
{
    return true;
}
