#include "itkabigon.h"

#include "cm/camera.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "gr/stage.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

#include <baselib/random.h>

ItemStateTable it_803F7AD8[] = {
    { 0, itKabigon_UnkMotion0_Anim, itKabigon_UnkMotion0_Phys,
      itKabigon_UnkMotion0_Coll },
    { 1, itKabigon_UnkMotion1_Anim, itKabigon_UnkMotion1_Phys,
      itKabigon_UnkMotion1_Coll },
    { -1, itKabigon_UnkMotion2_Anim, itKabigon_UnkMotion2_Phys,
      itKabigon_UnkMotion2_Coll },
};

void it_802C9D40(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itKabigonAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.kabigon.timer = attrs->x4;
    ip->xDD4_itemVar.kabigon.x64 = attrs->x8;
    ip->xDD4_itemVar.kabigon.x68 = attrs->xC;
    ip->xDD4_itemVar.kabigon.x6C = attrs->x10;
    ip->xDD4_itemVar.kabigon.xE44 = attrs->x14;
    ip->xDD4_itemVar.kabigon.xE48 = (s32) attrs->x18;
    ip->xDCC_flag.b3 = 1;
    ip->xDAC_itcmd_var0 = 0;
    ip->xDB0_itcmd_var1 = 0;
    ip->xDB4_itcmd_var2 = 1;
    it_80279CDC(gobj, attrs->x0);
    Item_8026AE84(ip, 0x2723, 0x7F, 0x40);
    it_802CA324(gobj);
}

void it_802C9DFC(Item_GObj* gobj) {}

void itKabigon_Logic2_Destroyed(Item_GObj* gobj)
{
    Camera_80031044(2);
}

void it_802C9E24(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802C9E44(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDCC_flag.b4567 = 0xE;
    it_80273454(gobj);
    it_802C9E8C(gobj);
}

void it_802C9E8C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    ip->on_accessory = (HSD_GObjEvent) it_802CA014;
    Camera_80030E44(3, NULL);
}

bool itKabigon_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xDB0_itcmd_var1 != 0) {
        ip->x40_vel.y = ip->xDD4_itemVar.kabigon.timer;
        it_802762BC(ip);
        if (ip->xDB4_itcmd_var2 != 0) {
            ip->xDB4_itcmd_var2 = 0;
        }
    }

    if (ip->pos.y > Stage_GetBlastZoneTopOffset()) {
        it_802CA074(gobj);
    }

    return false;
}

void itKabigon_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xDB0_itcmd_var1 == 0) {
        if (ip->ground_or_air == 1) {
            ItemAttr* attrs = ip->xCC_item_attr;
            it_80272860(gobj, attrs->x10_fall_speed,
                        attrs->x14_fall_speed_max);
        }
    }
}

bool itKabigon_UnkMotion0_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xDB0_itcmd_var1 == 0) {
        if (ip->ground_or_air == GA_Air) {
            it_8026E15C(gobj, it_802C9DFC);
        } else {
            it_8026D62C(gobj, it_802C9DFC);
        }
    }
    return false;
}

void it_802CA014(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    if (ip->xDB0_itcmd_var1 != 0) {
        s32 timer;
        timer = --ip->xDD4_itemVar.kabigon.xE44;
        if (timer == 0) {
            itPokemonAttributes* attr =
                ip->xC4_article_data->x4_specialAttributes;
            it_802CA3F4(gobj);
            ip->xDD4_itemVar.kabigon.xE44 = attr->x14;
        }
    }
}

void it_802CA074(Item_GObj* gobj)
{
    HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj);
    Item* ip = GET_ITEM(gobj);
    Vec3 scale;

    HSD_JObjSetFlagsAll(jobj, 0x10);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    ip->x40_vel.y = 0.0F;
    scale.z = ip->xDD4_itemVar.kabigon.x68;
    scale.y = ip->xDD4_itemVar.kabigon.x68;
    scale.x = ip->xDD4_itemVar.kabigon.x68;
    HSD_JObjSetScale(jobj, &scale);
    Item_8026AE84(ip, 0x2724, 0x7F, 0x40);
}

static inline void itKabigon_UnkMotion1_Anim_inline(Item_GObj* gobj, Item* ip)
{
    Vec3 scale;
    if (!it_80272C6C(gobj)) {
        HSD_JObj* jobj = GET_JOBJ(gobj);
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        ip->entered_hitlag = efLib_PauseAll;
        ip->exited_hitlag = efLib_ResumeAll;
        scale.x = scale.y = scale.z = ip->xDD4_itemVar.kabigon.x68;
        HSD_JObjSetScale(jobj, &scale);
    }
}

bool itKabigon_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    if (ip->xDAC_itcmd_var0 == 0) {
        if (ip->xDD4_itemVar.kabigon.x6C <= 0) {
            HSD_JObj* jobj = GET_JOBJ(gobj);
            ip->xDAC_itcmd_var0 = 1;
            HSD_JObjClearFlagsAll(jobj, 0x10);
            ip->pos.y = Stage_GetBlastZoneTopOffset();
            ip->x40_vel.y = ip->xDD4_itemVar.kabigon.x64;
            Camera_80030E44(2, NULL);
        } else {
            ip->xDD4_itemVar.kabigon.x6C--;
        }
    } else if (ip->pos.y < Stage_GetBlastZoneBottomOffset()) {
        return true;
    }
    itKabigon_UnkMotion1_Anim_inline(gobj, ip);
    return false;
}

void itKabigon_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itKabigon_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802CA324(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool itKabigon_UnkMotion2_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itKabigon_UnkMotion2_Phys(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

bool itKabigon_UnkMotion2_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802C9E44);
}

void it_802CA3F4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itKabigonAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    Vec3 pos = ip->pos;
    f32 r;

    r = HSD_Randf();
    pos.x += 2.0F * attr->x18 * r - attr->x18;
    r = HSD_Randf();
    pos.y += 2.0F * attr->x18 * r - attr->x18;

    efSync_Spawn(0x405, gobj, &pos);
}
