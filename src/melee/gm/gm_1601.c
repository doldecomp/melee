#include "gm_1601.h"

#include "gmmain_lib.h"

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "gm/types.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/item.h"
#include "lb/lb_00F9.h"
#include "lb/lbtime.h"
#include "mp/mpcoll.h"

struct gmMainLib_8015ED8C_arg0_t lbl_803B75F8 = { 0 };

#define NUM_UNLOCKABLE_CHARACTERS 11

bool gm_80164840(u8 id)
{
    int i;
    u16* temp_r31;
    u8 var_r0 = 0;

    temp_r31 = gmMainLib_8015ED8C(&lbl_803B75F8);
    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if (lbl_803B75F8.id[id] == lbl_803B75F8.thing[i].unk1) {
            var_r0 = lbl_803B75F8.thing[i].unk0;
            break;
        }
    }
    if ((var_r0 == 11) || (*temp_r31 & (1LL << var_r0))) {
        return true;
    }
    return false;
}

/// Are all unlockable characters unlocked?
bool gm_80164ABC(struct gmMainLib_8015ED8C_arg0_t* arg0)
{
    u16* unlockable_character_bitfield = gmMainLib_8015ED8C(arg0);
    int i;
    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if (!(*unlockable_character_bitfield & (1LL << i))) {
            /// @remarks Gekko codes which unlock all characters change this to
            ///          return @c true.
            return false;
        }
    }
    return true;
}

void gm_801692E8(uint ticks, struct datetime* datetime)
{
    OSCalendarTime tm;

    lbTime_8000B028(&tm, ticks);
    datetime->year = tm.year;
    datetime->month = tm.mon + 1;
    datetime->day = tm.mday;
    datetime->hour = tm.hour;
    datetime->minute = tm.min;
    if (tm.sec > 59) {
        datetime->second = 59;
    } else {
        datetime->second = tm.sec;
    }
}

void fn_80187714(void)
{
    Camera_80028B9C(6);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(64);
    Stage_802251E8(0, NULL);
    Stage_8022524C();
    Item_80266FA8();
    Item_80266FCC();
    efLib_8005B4B8();
    efAsync_8006737C(0);
}
