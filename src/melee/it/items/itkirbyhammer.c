#include "itkirbyhammer.h"

#include "db/db.h"
#include "ef/efasync.h"
#include "ft/chara/ftKirby/ftKb_Init.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

ItemStateTable it_803F6C98[] = {
    { 0, NULL, NULL, NULL },
};

void it_802ADC04(Item_GObj* gobj)
{
    Item* it = GET_ITEM((HSD_GObj*) gobj);

    if (it->owner == NULL) {
        return;
    }
    ftKb_SpecialAirLw_800F539C((ftKb_GObj*) it->owner);
}

void it_802ADC34(Item_GObj* gobj)
{
    Item_8026A8EC(gobj);
}

static void setupHammerParticles(HSD_GObj* parent, Item_GObj* item_gobj,
                                 Fighter_Part sfx, u32 vars)
{
    HSD_JObj* jobj;
    u32 particle_id;
    Item* it = GET_ITEM((HSD_GObj*) item_gobj);

    it->xDD4_itemVar.kirbyhammer.x0 = vars;
    db_80225DD8((HSD_GObj*) item_gobj, parent);
    Item_8026AB54((HSD_GObj*) item_gobj, parent, sfx);
    if (((Item*) item_gobj->user_data)->xDD4_itemVar.kirbyhammer.x0 == 1) {
        particle_id = 1177;
    } else {
        particle_id = 1176;
    }
    jobj = it_80272C90(item_gobj);
    efAsync_Spawn((HSD_GObj*) item_gobj, &((Item*) item_gobj->user_data)->xBC0,
                  0, particle_id, jobj);
}

Item_GObj* it_802ADC54(HSD_GObj* parent, Vec3* pos, Fighter_Part sfx, u32 vars,
                       f32 dir)
{
    Item_GObj* item_gobj;
    SpawnItem spawn;
    PAD_STACK(12);

    spawn.kind = It_Kind_Kirby_Hammer;
    spawn.prev_pos = *pos;
    it_8026BB68((Item_GObj*) parent, &spawn.pos);
    spawn.facing_dir = dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
    spawn.x0_parent_gobj = parent;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;

    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        setupHammerParticles(parent, item_gobj, sfx, vars);
    }
    return item_gobj;
}

void it_802ADD88(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

void it_802ADDB0(Item_GObj* gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
