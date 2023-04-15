#include "ftpikachu.h"
#include "types.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftlib.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "it/it_27CF.h"

#include <dolphin/mtx/types.h>

void ftPk_SpecialN_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x155, 0, 0, 0.0f, 1.0f, 0.0f);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    ftAnim_8006EBA4(gobj);
}

void ftPk_SpecialAirN_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x156, 0, 0, 0.0f, 1.0f, 0.0f);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    ftAnim_8006EBA4(gobj);
}

void ftPk_SpecialN_80124908(HSD_GObj* gobj)
{
    Vec3 sp14;
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (fp->x2200_ftcmd_var0 == 1) {
        fp->x2200_ftcmd_var0 = 0;

        if (!fp->x2204_ftcmd_var1) {
            fp->x2204_ftcmd_var1 = 1;
            sp14.x = (fp->x34_scale.y * (pika_attr->x0 * fp->facing_dir)) +
                     fp->cur_pos.x;
            sp14.y = (pika_attr->x4 * fp->x34_scale.y) + fp->cur_pos.y;
            sp14.z = 0.0f;
            it_802B338C(gobj, &sp14, fp->facing_dir, pika_attr->x14);
            switch (ftLib_800872A4(gobj)) {
            case 12:
                ft_80088148(fp, 0x3a9cc, 0x7F, 0x40);
                break;
            case 23:
                ft_80088148(fp, 0x382b3, 0x7F, 0x40);
                break;
            }
        }
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftPk_SpecialN_80124A20(HSD_GObj* gobj)
{
    Vec3 sp14;
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (fp->x2200_ftcmd_var0 == 1) {
        fp->x2200_ftcmd_var0 = 0;

        if (!fp->x2204_ftcmd_var1) {
            fp->x2204_ftcmd_var1 = 1;
            sp14.x = (fp->x34_scale.y * (pika_attr->x8 * fp->facing_dir)) +
                     fp->cur_pos.x;
            sp14.y = (pika_attr->xC * fp->x34_scale.y) + fp->cur_pos.y;
            sp14.z = 0.0f;
            it_802B338C(gobj, &sp14, fp->facing_dir, pika_attr->x14);
            switch (ftLib_800872A4(gobj)) {
            case 12:
                ft_80088148(fp, 0x3a9cc, 0x7F, 0x40);
                break;
            case 23:
                ft_80088148(fp, 0x382b3, 0x7F, 0x40);
                break;
            }
        }
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (0.0f == pika_attr->x10) {
            ft_800CC730(gobj);
            return;
        }
        ft_80096900(gobj, 1, 0, 1, 1.0f, pika_attr->x10);
    }
}

void ftPk_SpecialN_80124B6C(HSD_GObj* arg0) {}

void ftPk_SpecialN_80124B70(HSD_GObj* arg0) {}

void ftPk_SpecialN_80124B74(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPk_SpecialN_80124B94(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftPk_SpecialN_ChangeMotion_Unk0(HSD_GObj* gobj)
{
    Fighter* fp;
    if (!ft_80082708(gobj)) {
        fp = GET_FIGHTER(gobj);
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x156, 0xc4c5082, 0,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

void ftPk_SpecialN_ChangeMotion_Unk1(HSD_GObj* gobj)
{
    Fighter* fp;
    if (ft_80081D0C(gobj) == 1) {
        fp = GET_FIGHTER(gobj);
        ftCommon_8007D7FC(fp);
        fp->x80_self_vel.y = 0.0f;
        Fighter_ChangeMotionState(gobj, 0x155, 0xc4c5082, 0,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

void ftPk_SpecialN_SpawnEffect0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    HSD_GObj* tempObj;
    HSD_GObj* tempObj2;

    if (!fp->x2219_flag.bits.b0) {
        s32 index = ftParts_8007500C(fp, 4);
        tempObj = gobj;
        efSync_Spawn(0x4BE, tempObj2 = tempObj, fp->ft_bones[index].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
}

void ftPk_SpecialN_SpawnEffect1(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    HSD_GObj* tempObj;
    HSD_GObj* tempObj2;

    if (!fp->x2219_flag.bits.b0) {
        s32 index = ftParts_8007500C(fp, 4);
        tempObj = gobj;
        efSync_Spawn(0x4BF, tempObj2 = tempObj, fp->ft_bones[index].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
}

void ftPk_SpecialN_80124DC8(HSD_GObj* gobj)
{
    u8 fighter_x673_byte;
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;
    f32 pika_attr_1C;

    fp->x2200_ftcmd_var0 = 0;
    fighter_x673_byte = fp->x673;

    pika_attr_1C = pika_attr->x1C;
    if (fighter_x673_byte < pika_attr_1C) {
        fp->mv.pk.unk2.x0 = pika_attr->x20;
        fp->x2070.x2072_b4 = 1;
    } else {
        fp->mv.pk.unk2.x0 = 0;
    }
}
