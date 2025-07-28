#include "ft_0877.h"

#include "ftcommon.h"
#include "ftdevice.h"

#include "ft/fighter.h"
#include "ft/types.h"
#include "ftCommon/ftCo_0A01.h"
#include "it/it_26B1.h"
#include "lb/lbaudio_ax.h"

#include <dolphin/mtx.h>
#include <baselib/gobj.h>
#include <baselib/random.h>

#define TEST(expr) (expr) ? true : false

s32 ft_800877F8(HSD_GObj* gobj, s32 arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return TEST(fp->input.held_inputs & arg1);
}

s32 ft_80087818(HSD_GObj* gobj, s32 arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return TEST(fp->input.x668 & arg1);
}

s32 ft_80087838(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return TEST(fp->x221D_b7 & 1);
}

s32 ft_80087858(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return TEST(fp->x2227_b1 & 1);
}

s32 ft_80087878(HSD_GObj* gobj, s32 arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->x1968_jumpsUsed <= 1) && (fp->motion_id == 0) && (arg1 != 0x23) &&
        (arg1 != 0x24) && (arg1 != 0x25))
    {
        return true;
    }

    return false;
}

s32 ft_800878BC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->item_gobj != NULL) && (it_8026B2B4(fp->item_gobj) == 1)) {
        return true;
    }

    return false;
}

s32 ft_80087900(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->item_gobj != NULL) && (itGetKind(fp->item_gobj) == 0x1E)) {
        return true;
    }

    return false;
}

s32 ft_80087944(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->item_gobj != NULL) && (itGetKind(fp->item_gobj) == 0x7)) {
        return true;
    }

    return false;
}

s32 ft_80087988(HSD_GObj* gobj)
{
    if ((ftGetParasolStatus(gobj) == 4) || (ftGetParasolStatus(gobj) == 5)) {
        return true;
    }

    return false;
}

s32 ft_800879D8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x1980 != 0) {
        return true;
    }

    return false;
}

s32 ft_800879F8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x221D_b6 & 1) {
        return true;
    }

    return false;
}

s32 ft_80087A18(HSD_GObj* gobj)
{
    s32 var1;
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->x2226_b4) &&
        ((var1 = ftCo_800C06B4(fp), ((var1 == 0x7B) != 0)) ||
         (var1 == 0x80)) &&
        ((fp->x2226_b5)))
    {
        return true;
    }

    return false;
}

s8 ft_80087A80(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->smash_attrs.x2134_vibrateFrame;
}

float ft_80087A8C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->smash_attrs.x2138_smashSinceHitbox;
}

s32 ft_80087A98(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x213C;
}

s32 ft_80087AA4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x2227_b5;
}

u8 ft_80087AB4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x1968_jumpsUsed;
}

void ft_80087AC0(HSD_GObj* gobj, s32 arg1)
{
    s32 var0;
    u8 var1;
    u8 var2;
    Fighter* fp = GET_FIGHTER(gobj);
    if (arg1 != 0) {
        var1 = false;
    } else {
        var1 = true;
    }
    var0 = var1;
    var2 = fp->x221E_b7;
    var2 = var0;
    fp->x221E_b0 = var2;
}

s32 ft_80087AEC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->x34_scale.y != fp->x34_scale.x) ||
        ((fp->x2226_b4) || (fp->x2223_b7) || (fp->x197C != 0)))
    {
        return true;
    }

    return false;
}

s32 ft_80087B34(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float atk_shield_kb_x = fp->x98_atk_shield_kb.x;
    float fVar1 =
        (fp->self_vel.x * fp->self_vel.x) + (fp->self_vel.y * fp->self_vel.y);
    float* atk_shield_kb_y = &fp->x98_atk_shield_kb.y;
    float fVar2 = (atk_shield_kb_x * atk_shield_kb_x) +
                  ((*atk_shield_kb_y) * (*atk_shield_kb_y));

    if (fVar1 > ((fp->x8c_kb_vel.x * fp->x8c_kb_vel.x) +
                 (fp->x8c_kb_vel.y * fp->x8c_kb_vel.y)))
    {
        if (fVar1 > ((atk_shield_kb_x * atk_shield_kb_x) +
                     (fp->x98_atk_shield_kb.y * fp->x98_atk_shield_kb.y)))
        {
            return 0;
        }

        return 2;
    }

    if ((fp->x8c_kb_vel.x * fp->x8c_kb_vel.x) +
            (fp->x8c_kb_vel.y * fp->x8c_kb_vel.y) >
        fVar2)
    {
        return 1;
    }

    return 2;
}

void ft_80087BAC(HSD_GObj* gobj, s32 arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2228_b5 = arg1;
}

void ft_80087BC0(HSD_GObj* gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800A101C(fp, arg1, fp->x1A88.x10, fp->x1A88.x14);
}

void ft_80087BEC(HSD_GObj* gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800A101C(fp, fp->x1A88.xC, arg1, fp->x1A88.x14);
}

s32 ft_80087C1C(void)
{
    HSD_GObj* gobj;
    s32 ftKind;
    u32 result = 0;

    for (gobj = HSD_GObj_Entities->fighters; gobj != 0; gobj = gobj->next) {
        ftKind = (GET_FIGHTER(gobj))->kind;
        if (ftKind < 27) {
            result = result | 1 << ftKind;
        }
    }
    return result;
}

s32 ft_80087C58(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x1988;
}

void ft_80087C64(HSD_GObj* gobj, s32 arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x1988 = arg1;
}

/// Player_AdjustSFXIDForSizeModifier(r3=fighter,r4=sfx)
s32 ft_80087C70(Fighter* fp, s32 arg1)
{
    u8 temp_r3;
    u8 temp_r3_2;
    u8 temp_r3_3;

    s32 var_r4 = arg1;
    s32 temp_r0 = (fp->x2228_b3) & 3;

    switch (temp_r0) {
    case 0:
        temp_r3 = fp->x2220_flag.flags;
        if ((temp_r3 >> 2U) & 1) {
            var_r4 += 1;
        } else if ((temp_r3 >> 1U) & 1) {
            var_r4 += 2;
        }
        break;
    case 1:
        temp_r3_2 = fp->x2220_flag.flags;
        if (!((temp_r3_2 >> 2U) & 1)) {
            if ((temp_r3_2 >> 1U) & 1) {
                var_r4 += 2;
            } else {
                var_r4 += 2;
            }
        }
        break;
    case 2:
        temp_r3_3 = fp->x2220_flag.flags;
        if ((temp_r3_3 >> 2U) & 1) {
            var_r4 += 1;
        } else if (!((temp_r3_3 >> 1U) & 1)) {
            var_r4 += 1;
        }
        break;
    }
    return var_r4;
}

s32 ft_80087D0C(Fighter* fighter, s32 sfx_id)
{
    enum_t sfx = lbAudioAx_800233EC(sfx_id);
    enum_t ssm_id = lbAudioAx_80023130(sfx);

    switch (ssm_id) {
    case 0:
        switch (sfx) {
        case 407:
        case 467:
        case 503:
        case 515:
        case 290051:
        case 509:
        case 485:
        case 491:
        case 479:
        case 473:
        case 437:
        case 455:
        case 461:
        case 449:
        case 443:
        case 425:
        case 431:
        case 419:
        case 413:
        case 377:
        case 395:
        case 401:
        case 389:
        case 383:
        case 371:
            sfx_id = ft_80087C70(fighter, sfx);
            if (fighter->x2223_b7) {
                sfx_id += 3;
            }
            sfx = sfx_id;
            break;
        case 359:
        case 368:
        case 365:
        case 362:
        case 344:
        case 353:
        case 356:
        case 350:
        case 347:
        case 338:
        case 341:
        case 335:
        case 332:
            sfx = ft_80087C70(fighter, sfx);
            break;
        }
        break;
    case 13: {
        switch (fighter->kind) {
        case FTKIND_POPO:
        case FTKIND_NANA:
            if (0x1FBFD <= sfx && sfx <= 0x1FC62 &&
                ftCommon_80080144(fighter) == true)
            {
                sfx += 0x66;
            }

            if (0x1FC63 <= sfx && sfx <= 0x1FCC8 &&
                ftCommon_80080144(fighter) != true)
            {
                sfx -= 0x66;
            }
            break;
        }
    }
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 33: {
        int sfx_offset;
        int unused_output;
        int _[1];

        if (lbAudioAx_800230C8(ssm_id, &sfx_offset, &unused_output) == 0 &&
            sfx >= sfx_offset + lbAudioAx_80023220(ssm_id))
        {
            sfx = ft_80087C70(fighter, sfx);
        }
        break;
    }
    default:
        break;
    }

    return sfx;
}

void ft_8008805C(Fighter* arg0, s32 arg1)
{
    lbAudioAx_80024DC4(ft_80087D0C(arg0, arg1));
}

void ft_80088080(Fighter* fp)
{
    fp->x2164 += 1;
    lbAudioAx_80024FDC();
}

void ft_800880AC(Fighter* fp)
{
    fp->x2168 += 1;
    lbAudioAx_80024FF4();
}

void ft_800880D8(Fighter* fp)
{
    lbAudioAx_8002500C(fp->x2164);
    fp->x2164 = 0;
}

void ft_80088110(Fighter* fp)
{
    lbAudioAx_80025038(fp->x2168);
    fp->x2168 = 0;
}

void ft_80088148(Fighter* fp, enum_t sfx_id, int sfx_vol, int sfx_pan)
{
    sfx_id = ft_80087D0C(fp, sfx_id);
    fp->x2160 = lbAudioAx_800237A8(sfx_id, sfx_vol, sfx_pan);

    {
        int rand;
        if (sfx_id >= 332 && sfx_id <= 370) {
            rand = HSD_Randi(200) - 100;
        } else {
            rand = 0;
        }

        lbAudioAx_80024B94(fp->x2160, rand);
    }
}
