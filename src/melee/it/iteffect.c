#include "iteffect.h"

#include "forward.h"
#include "it_2725.h"
#include "it_3F14.h"
#include "types.h"
#include <melee/ef/efasync.h>
#include <melee/ef/efsync.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lblanguage.h>
#include <sysdolphin/baselib/random.h>

void it_8027870C(s32 arg0)
{
    if (lbLang_IsSettingUS()) {
        lbArchive_80017040(NULL, it_803F1EE4, &it_804D6D20, it_803F1EF0, 0);
    } else {
        lbArchive_80017040(NULL, it_803F1ED8, &it_804D6D20, it_803F1EF0, 0);
    }
    it_804D6D28 = it_804D6D20->x0;
    it_804D6D24 = it_804D6D20->x4;
    it_804D6D38 = it_804D6D20->x8;
    it_804D6D30 = it_804D6D20->xC;
    it_804D6D40 = it_804D6D20->x10;
    it_804D6D04 = it_804D6D20->x14;
}

void it_802787B4(Item_GObj* item_gobj, s32 arg1)
{
    Vec3 sp1C;
    Vec3 sp10;
    sp1C.x = sp1C.y = sp1C.z = 0.0F;
    sp10.x = sp10.y = sp10.z = 0.0F;
    it_80278800(item_gobj, arg1, 0, &sp1C, &sp10, 1, 0.0F);
}

static inline void it_80278800_rand_vec(Vec3* out, Vec3* v)
{
    f32 f = HSD_Randf();
    out->x += 2.0f * v->x * (f - 0.5f);
    f = HSD_Randf();
    out->y += 2.0f * v->y * (f - 0.5f);
    f = HSD_Randf();
    out->z += 2.0f * v->z * (f - 0.5f);
}

void it_80278800(Item_GObj* item_gobj, s32 ef_id, s32 arg2, Vec3* arg3,
                 Vec3* arg4, s32 arg5, f32 arg6)
{
    f32 sp88;
    f32 sp84;
    f32 sp80;
    Vec3 sp74;
    Vec3 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    HSD_JObj* jobj;
    Item* item;
    f64 var_f0;
    PAD_STACK(56);

    item = item_gobj->user_data;

    switch (ef_id) {
    case 0x402:
    case 0x403:
    case 0x409:
    case 0x412:
    case 0x413:
    case 0x414:
    case 0x41B:
    case 0x422:
    case 0x433:
    case 0x449:
    case 0x473:
        if (arg5 == 1) {
            jobj = it_80272CC0(item_gobj, arg2);
            efSync_Spawn(ef_id, item_gobj, jobj);
            return;
        }
        jobj = it_80272CC0(item_gobj, arg2);
        efAsync_Spawn(item_gobj, &((Item*) item_gobj->user_data)->xBC0, 0U,
                      ef_id, jobj);
        return;
    case 0x446:
    case 0x448:
        if (arg5 == 1) {
            jobj = it_80272CC0(item_gobj, arg2);
            efSync_Spawn(ef_id, item_gobj, jobj, arg3);
            return;
        }
        jobj = it_80272CC0(item_gobj, arg2);
        efAsync_Spawn(item_gobj, &((Item*) item_gobj->user_data)->xBC0, 7U,
                      ef_id, jobj, arg3);
        return;
    case 0x417:
    case 0x418:
    case 0x419:
    case 0x41A:
        jobj = it_80272CC0(item_gobj, arg2);
        efSync_Spawn(ef_id, item_gobj, jobj, 0xF25959);
        return;
    case 0x415:
    case 0x41E:
    case 0x428:
    case 0x429:
    case 0x42A:
    case 0x438:
    case 0x439:
    case 0x43E:
    case 0x44D:
    case 0x45B:
    case 0x45C:
    case 0x45F:
    case 0x460:
    case 0x461:
    case 0x462:
    case 0x463:
    case 0x464:
    case 0x465:
    case 0x466:
    case 0x467:
    case 0x468:
    case 0x469:
    case 0x46A:
    case 0x46B:
    case 0x46C:
    case 0x46D:
    case 0x46E:
    case 0x46F:
    case 0x470:
    case 0x471:
    case 0x472:
        sp88 = 1.0f;
        if (arg5 == 1) {
            jobj = it_80272CC0(item_gobj, arg2);
            efSync_Spawn(ef_id, item_gobj, jobj, &sp88);
            return;
        }
        jobj = it_80272CC0(item_gobj, arg2);
        efAsync_Spawn(item_gobj, &((Item*) item_gobj->user_data)->xBC0, 3U,
                      ef_id, jobj, &sp88);
        return;
    case 0x44E:
    case 0x44F:
    case 0x450:
    case 0x451:
    case 0x452:
    case 0x457:
    case 0x458:
    case 0x459:
    case 0x45A:
        sp84 = 1.0f;
        jobj = it_80272CC0(item_gobj, arg2);
        efSync_Spawn(ef_id, item_gobj, jobj, &item->facing_dir, &sp84);
        return;
    case 0x423:
    case 0x424:
        sp80 = 0.0f;
        jobj = it_80272CC0(item_gobj, arg2);
        efAsync_Spawn(item_gobj, &((Item*) item_gobj->user_data)->xBC0, 3U,
                      ef_id, jobj, &sp80);
        return;
    }
    sp74 = *arg3;
    it_80278800_rand_vec(&sp74, arg4);
    lb_8000B1CC(it_80272CC0(item_gobj, arg2), &sp74, &sp68);
    if (ef_id < 0x250) {
        if (arg5 == 1) {
            efSync_Spawn(ef_id, item_gobj, &sp68);
            return;
        }
        jobj = it_80272CC0(item_gobj, arg2);
        efAsync_Spawn(item_gobj, &((Item*) item_gobj->user_data)->xBC0, 2U,
                      ef_id, jobj, &sp74);
        return;
    }

    switch (ef_id) {
    case 0x3E9:
    case 0x3EA:
    case 0x3EB:
    case 0x3EC:
    case 0x3EE:
    case 0x3F3:
    case 0x3F4:
    case 0x3F6:
    case 0x3FA:
    case 0x3FB:
    case 0x3FC:
    case 0x405:
    case 0x407:
    case 0x40C:
    case 0x40D:
    case 0x40E:
    case 0x40F:
    case 0x410:
    case 0x411:
    case 0x416:
    case 0x41C:
    case 0x41D:
    case 0x41F:
    case 0x420:
    case 0x421:
    case 0x425:
    case 0x426:
    case 0x427:
    case 0x42D:
    case 0x434:
    case 0x441:
    case 0x442:
    case 0x444:
    case 0x445:
    case 0x44A:
    case 0x44B:
    case 0x44C:
    case 0x4D0:
        if (arg5 == 1) {
            efSync_Spawn(ef_id, item_gobj, &sp68);
            return;
        }
        jobj = it_80272CC0(item_gobj, arg2);
        efAsync_Spawn(item_gobj, &((Item*) item_gobj->user_data)->xBC0, 2U,
                      ef_id, jobj, &sp74);
        return;
    case 0x3ED:
    case 0x3EF:
    case 0x3F0:
    case 0x3F1:
    case 0x3F2:
    case 0x3F5:
    case 0x3FE:
    case 0x400:
    case 0x401:
    case 0x42E:
    case 0x42F:
    case 0x430:
    case 0x431:
    case 0x43A:
    case 0x43B:
    case 0x43C:
    case 0x443:
        if (arg5 == 1) {
            efSync_Spawn(ef_id, item_gobj, &sp68, &item->facing_dir);
            return;
        }
        jobj = it_80272CC0(item_gobj, arg2);
        efAsync_Spawn(item_gobj, &((Item*) item_gobj->user_data)->xBC0, 5U,
                      ef_id, jobj, &sp74, &item->facing_dir);
        return;
    case 0x3F7:
    case 0x3F8:
    case 0x3F9:
    case 0x3FD:
    case 0x3FF:
        sp64 = 0.0f;
        jobj = it_80272CC0(item_gobj, arg2);
        efAsync_Spawn(item_gobj, &((Item*) item_gobj->user_data)->xBC0, 6U,
                      ef_id, jobj, &sp74, &item->facing_dir, &sp64);
        return;
    case 0x435:
    case 0x436:
    case 0x437:
    case 0x440:
        if (item->facing_dir < 0.0f) {
            var_f0 = M_PI;
        } else {
            var_f0 = 0.0f;
        }
        sp60 = var_f0;
        if (arg5 == 1) {
            efSync_Spawn(ef_id, item_gobj, &sp68, &sp60);
            return;
        }
        jobj = it_80272CC0(item_gobj, arg2);
        efAsync_Spawn(item_gobj, &((Item*) item_gobj->user_data)->xBC0, 5U,
                      ef_id, jobj, &sp74, &sp60);
        return;
    case 0x404:
    case 0x406:
    case 0x408:
        sp5C = 0.0f;
        if (arg5 == 1) {
            efSync_Spawn(ef_id, item_gobj, &sp68, &sp5C);
            return;
        }
        jobj = it_80272CC0(item_gobj, arg2);
        efAsync_Spawn(item_gobj, &((Item*) item_gobj->user_data)->xBC0, 5U,
                      ef_id, jobj, &sp74, &sp5C);
        return;
    case 0x513:
        jobj = it_80272CC0(item_gobj, arg2);
        efAsync_Spawn(item_gobj, &((Item*) item_gobj->user_data)->xBC0, 8U, 2U,
                      jobj, &sp74);
        return;
    case 0x514:
        jobj = it_80272CC0(item_gobj, arg2);
        efAsync_Spawn(item_gobj, &((Item*) item_gobj->user_data)->xBC0, 8U, 3U,
                      jobj, &sp74);
        return;
    case 0x515:
        jobj = it_80272CC0(item_gobj, arg2);
        efAsync_Spawn(item_gobj, &((Item*) item_gobj->user_data)->xBC0, 8U, 4U,
                      jobj, &sp74);
        return;
    }
}
