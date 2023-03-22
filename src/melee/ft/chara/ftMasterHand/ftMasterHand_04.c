#include "ftMasterHand_04.h"

#include "ftMasterHand_03.h"
#include "ftMasterHand_05.h"

#include "cm/camera.h"
#include "ft/ft_877.h"
#include "ft/ftbosslib.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"

static void ftMasterHand_801511FC(HSD_GObj* gobj);

// 801510B0 14DC90
// https://decomp.me/scratch/sIqel
void ftMasterHand_801510B0(HSD_GObj* gobj)
{
    Fighter* r31_fp;
    ftMasterHand_SpecialAttrs* r30_attributes;

    r31_fp = gobj->user_data;
    r30_attributes = r31_fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, 0x157, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    r31_fp->cur_pos.x = r30_attributes->x30_pos2.x;
    r31_fp->cur_pos.y = r30_attributes->x30_pos2.y;
    r31_fp->cur_pos.z = 0.0f;
    r31_fp->cb.x21BC_callback_Accessory4 = &ftMasterHand_801511FC;
    r31_fp->mv.mh.unk4.x0 = 0;

    /// @todo Probably same file if #ftMasterHand_801511FC is getting
    /// implicitly passed.
    ft_800881D8(r31_fp, 0x4E201, 0x7F, 0x40 /*, ftMasterHand_801511FC */);
    // ft_800881D8(r31_fp, 0x4E201, 0x7F, 0x40, ftMasterHand_801511FC);

    func_8015C09C(gobj, -1.0f);
}

// 80151168 14DD48
// https://decomp.me/scratch/896fc
void ftMasterHand_80151168(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* r4_fp = GET_FIGHTER(gobj);
        r4_fp->fv.mh.x2258 = 0x155;
        ftMasterHand_80151018(gobj);
    }
}

// 801511B0 14DD90
// https://decomp.me/scratch/lkMK2
void ftMasterHand_801511B0(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (!Player_GetPlayerSlotType(fp->xC_playerID))
        func_8015BD20(gobj);
}

// 801511F4 14DDD4
// https://decomp.me/scratch/xs8Nh
void ftMasterHand_801511F4(HSD_GObj* gobj)
{
    return;
}

// 801511F8 14DDD8
// https://decomp.me/scratch/5Mb62
void ftMasterHand_801511F8(HSD_GObj* gobj)
{
    return;
}

// 801511FC 14DDDC
static void ftMasterHand_801511FC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    switch (fp->mv.mh.unk4.x0) {
    case 0: {
        HSD_GObj* nearest_enemy = ftLib_8008627C(&fp->cur_pos, gobj);

        if (nearest_enemy != NULL)
            func_8002E6FC((s32) ftLib_80086BE0(nearest_enemy));
        else
            func_8002E6FC(0);

        func_8002ED9C(40.0f);
        func_8002EEC8(45.0f);
        func_8002EC7C(-M_PI);
        func_8002EF14();
        func_8002EC7C(0.0f);
        func_8002F0E4(0x78);
        fp->mv.mh.unk4.x0 = 1;
        break;
    }
    case 1:
        if (func_8002F260() != 0) {
            func_8002E948(&ftMasterHand_80151428);
            func_8002ED9C(120.0f);
            func_8002F0E4(0x14);
            fp->mv.mh.unk4.x0 = 2;
        }
        break;
    case 2:
        if (func_8002F260() != 0) {
            func_8002EC7C(1.5707963705062866f);
            func_8002F0E4(0x3C);
            fp->mv.mh.unk4.x0 = 3;
        }
        break;
    case 3:
        if (func_8002F260() != 0) {
            func_8002ED9C(90.0f);
            func_8002EC7C(-0.3490658402442932f);
            func_8002EB5C(-0.2617993950843811f);
            func_8002EF14();
            fp->mv.mh.unk4.x0 = 4;
        }
        break;
    case 4:
        func_8002F274();
        fp->mv.mh.unk4.x8 = 0x78;
        fp->mv.mh.unk4.x0 = 5;
        break;
    case 5:
        if (--fp->mv.mh.unk4.x8 == 0) {
            func_8002EC7C(-0.3490658402442932f);
            func_8002EF14();
            func_8002ED9C(120.0f);
            fp->mv.mh.unk4.x8 = 0x1E;
            fp->mv.mh.unk4.x0 = 6;
        }
        break;
    case 6:
        if (--fp->mv.mh.unk4.x8 == 0) {
            func_8002EC7C(0.3490658402442932f);
            func_8002EF14();
            fp->mv.mh.unk4.x8 = 0x1E;
            fp->mv.mh.unk4.x0 = 7;
        }
        break;
    case 7:
        if (--fp->mv.mh.unk4.x8 == 0) {
            func_8002ED9C(180.0f);
            func_8002EC7C(-1.5707963705062866f);
            func_8002EB5C(-0.3490658402442932f);
            func_8002EF14();
            fp->mv.mh.unk4.x8 = 0x32;
            fp->mv.mh.unk4.x0 = 8;
        }
        break;
    case 8:
        func_8002F274();
        fp->mv.mh.unk4.x0 = 9;
        break;
    case 9:
        if (--fp->mv.mh.unk4.x8 == 0) {
            func_8002F474();
            fp->mv.mh.unk4.x0 = 10;
        }
        break;
#ifndef MUST_MATCH
    default:
        HSD_ASSERT(__LINE__, false);
#endif
    }
}
