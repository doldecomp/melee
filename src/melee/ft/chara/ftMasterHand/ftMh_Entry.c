#include <platform.h>

#include "ftMh_Entry.h"

#include "ftMh_Damage_0.h"
#include "ftMh_Wait1_2.h"
#include "math.h"
#include "types.h"

#include "cm/camera.h"
#include "ft/fighter.h"
#include "ft/ft_0881.h"
#include "ft/ftanim.h"
#include "ft/ftbosslib.h"
#include "ft/ftlib.h"
#include "ft/types.h"
#include "pl/player.h"

#include <dolphin/mtx.h>
#include <baselib/debug.h>

static void ftMh_MS_343_801511FC(HSD_GObj* gobj);

void ftMh_MS_343_801510B0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, ftMh_MS_Entry, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    fp->cur_pos.x = da->x30_pos2.x;
    fp->cur_pos.y = da->x30_pos2.y;
    fp->cur_pos.z = 0;
    fp->accessory4_cb = ftMh_MS_343_801511FC;
    fp->mv.mh.unk4.x0 = ftMh_UnkEnum0_Unk00;

    /// @todo Probably same file if #ftMh_MS_343_801511FC is getting
    /// implicitly passed.
    ft_800881D8(fp, 320001, 127, 64 /*, ftMh_MS_343_801511FC */);

    ftBossLib_8015C09C(gobj, -1);
}

void ftMh_Entry_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->fv.mh.x2258 = ftMh_MS_Wait1_0;
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_Entry_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!Player_GetPlayerSlotType(fp->player_id)) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_Entry_Phys(HSD_GObj* gobj) {}

void ftMh_Entry_Coll(HSD_GObj* gobj) {}

static void ftMh_MS_343_801511FC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[16];
    switch (fp->mv.mh.unk4.x0) {
    case ftMh_UnkEnum0_Unk00: {
        HSD_GObj* enemy_gobj = ftLib_8008627C(&fp->cur_pos, gobj);
        if (enemy_gobj != NULL) {
            Camera_8002E6FC((int) ftLib_80086BE0(enemy_gobj));
        } else {
            Camera_8002E6FC(0);
        }
        Camera_8002ED9C(40);
        Camera_8002EEC8(45);
        Camera_8002EC7C(-M_PI);
        Camera_8002EF14();
        Camera_8002EC7C(0);
        Camera_8002F0E4(120);
        fp->mv.mh.unk4.x0 = ftMh_UnkEnum0_Unk01;
        return;
    }
    case ftMh_UnkEnum0_Unk01: {
        if (Camera_8002F260() != 0) {
            Camera_8002E948(ftMh_MS_343_80151428);
            Camera_8002ED9C(120);
            Camera_8002F0E4(20);
            fp->mv.mh.unk4.x0 = ftMh_UnkEnum0_Unk02;
        }
        return;
    }
    case ftMh_UnkEnum0_Unk02: {
        if (Camera_8002F260() != 0) {
            Camera_8002EC7C(M_PI / 2);
            Camera_8002F0E4(60);
            fp->mv.mh.unk4.x0 = 3;
        }
        return;
    }
    case ftMh_UnkEnum0_Unk03: {
        if (Camera_8002F260() != 0) {
            Camera_8002ED9C(90);
            Camera_8002EC7C(-M_PI / 9);
            Camera_8002EB5C(-M_PI / 12);
            Camera_8002EF14();
            fp->mv.mh.unk4.x0 = ftMh_UnkEnum0_Unk04;
        }
        return;
    }
    case ftMh_UnkEnum0_Unk04: {
        Camera_8002F274();
        fp->mv.mh.unk4.x8 = 120;
        fp->mv.mh.unk4.x0 = ftMh_UnkEnum0_Unk05;
        return;
    }
    case ftMh_UnkEnum0_Unk05: {
        if (--fp->mv.mh.unk4.x8 == 0) {
            Camera_8002EC7C(-M_PI / 9);
            Camera_8002EF14();
            Camera_8002ED9C(120);
            fp->mv.mh.unk4.x8 = 30;
            fp->mv.mh.unk4.x0 = ftMh_UnkEnum0_Unk06;
        }
        return;
    }
    case ftMh_UnkEnum0_Unk06: {
        if (--fp->mv.mh.unk4.x8 == 0) {
            Camera_8002EC7C(M_PI / 9);
            Camera_8002EF14();
            fp->mv.mh.unk4.x8 = 30;
            fp->mv.mh.unk4.x0 = ftMh_UnkEnum0_Unk07;
        }
        return;
    }
    case ftMh_UnkEnum0_Unk07: {
        if (--fp->mv.mh.unk4.x8 == 0) {
            Camera_8002ED9C(180);
            Camera_8002EC7C(-M_PI / 2);
            Camera_8002EB5C(-M_PI / 9);
            Camera_8002EF14();
            fp->mv.mh.unk4.x8 = 50;
            fp->mv.mh.unk4.x0 = ftMh_UnkEnum0_Unk08;
        }
        return;
    }
    case ftMh_UnkEnum0_Unk08: {
        Camera_8002F274();
        fp->mv.mh.unk4.x0 = ftMh_UnkEnum0_Unk09;
        return;
    }
    case ftMh_UnkEnum0_Unk09: {
        if (--fp->mv.mh.unk4.x8 == 0) {
            Camera_8002F474();
            fp->mv.mh.unk4.x0 = ftMh_UnkEnum0_Unk10;
        }
        return;
    }
#ifdef BUGFIX
    case ftMh_UnkEnum0_Unk10: {
        return;
    }
    default: {
        HSD_ASSERT(__LINE__, false);
    }
#endif
    }
}
