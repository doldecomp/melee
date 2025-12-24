#include "db.h"

#include "ftCommon/ftCo_KinokoGiantEnd.h"
#include "ftCommon/ftCo_KinokoGiantStart.h"
#include "ftCommon/ftCo_KinokoSmallEnd.h"
#include "ftCommon/ftCo_KinokoSmallStart.h"

#include <melee/ft/ftlib.h>
#include <melee/ft/inlines.h>
#include <melee/if/textdraw.h>
#include <melee/if/textlib.h>
#include <melee/pl/player.h>

static struct {
    DevText* text;
    char buf[0x5A4];
} db_AnimationInfo;

static struct {
    u32 ShowFighterCollisionBubbles : 3;
    u32 MiscFighterVisualsStatus : 6;
    u32 ShowAnimationInfo : 1;
} db_804D6B48;

void fn_SetupAnimationInfo(void)
{
    HSD_GObj* temp_r3;

    temp_r3 = DevText_GetGObj();
    db_804D6B48.ShowFighterCollisionBubbles = 1;
    db_804D6B48.ShowAnimationInfo = 0;
    db_804D6B48.MiscFighterVisualsStatus = 0;
    db_AnimationInfo.text =
        DevText_Create(7, 20, 20, 60, 12, db_AnimationInfo.buf);
    if (db_AnimationInfo.text) {
        GXColor bg = { 0x00, 0x00, 0x00, 0x00 };
        GXColor fg = { 0xFF, 0xFF, 0xFF, 0xFF };
        DevText_Show(temp_r3, db_AnimationInfo.text);
        DevText_HideCursor(db_AnimationInfo.text);
        DevText_SetBGColor(db_AnimationInfo.text, bg);
        DevText_SetTextColor(db_AnimationInfo.text, fg);
        DevText_SetScale(db_AnimationInfo.text, 9.0F, 12.0F);
    }
}

void fn_ToggleMiscFighterVisuals(void)
{
    HSD_GObj* fighter;
    if (db_804D6B48.MiscFighterVisualsStatus != 0) {
        db_804D6B48.MiscFighterVisualsStatus =
            (db_804D6B48.MiscFighterVisualsStatus << 1) & 0x3F;
    } else {
        db_804D6B48.MiscFighterVisualsStatus = 1;
    }
    for (fighter = HSD_GObj_Entities->fighters; fighter != NULL;
         fighter = fighter->next)
    {
        Fighter* ft = GET_FIGHTER(fighter);
        // ft->x21FC_flag.grouped_bits.b0_to_5 =
        // db_804D6B48.MiscFighterVisualsStatus;
        ft->x21FC_flag.u8 = (ft->x21FC_flag.u8 & 3) |
                            ((db_804D6B48.MiscFighterVisualsStatus << 2) & ~3);
    }
    if ((db_804D6B48.MiscFighterVisualsStatus & 0x02) != 0) {
        fn_EnableShowEnemyStompRange();
    } else {
        fn_DisableShowEnemyStompRange();
    }
    if ((db_804D6B48.MiscFighterVisualsStatus & 0x08) != 0) {
        fn_EnableShowItemPickupRange();
    } else {
        fn_DisableShowItemPickupRange();
    }
    if ((db_804D6B48.MiscFighterVisualsStatus & 0x20) != 0) {
        fn_EnableShowCoinPickupRange();
    } else {
        fn_DisableShowCoinPickupRange();
    }
}

u8 fn_8022697C(Fighter_GObj* owner)
{
    if (ftLib_80086960(owner) != 0) {
        Fighter* ft = GET_FIGHTER(owner);
        return ft->x21FC_flag.u8;
    } else {
        return 0;
    }
}

void fn_UpdateAnimationInfo(void)
{
    Fighter_GObj* gobj;
    Fighter* ft;
    DevText* text;
    s32 print_newline;
    int stack[4];

    if (db_804D6B48.ShowAnimationInfo) {
        text = db_AnimationInfo.text;
        print_newline = 0;
        DevText_Erase(text);
        DevText_SetCursorXY(text, 0, 0);
        for (gobj = HSD_GObj_Entities->fighters; gobj != NULL;
             gobj = gobj->next)
        {
            ft = gobj->user_data;
            if (print_newline == 0) {
                print_newline = 1;
            } else {
                DevText_Printf(text, "\n");
            }
            if (ft->motion_id < 0x155) {
                DevText_Printf(text, "%d %s", ft->player_id,
                               db_motionstate_names[ft->motion_id]);
            } else {
                DevText_Printf(text, "%d %d", ft->player_id, ft->motion_id);
            }
            DevText_SetCursorX(text, 23);
            if (ft->anim_id != -1) {
                if (ft->anim_id < 0x127) {
                    DevText_Printf(text, "%s",
                                   db_submotion_names[ft->anim_id]);
                } else {
                    DevText_Printf(text, "%d", ft->anim_id);
                }
            }
            DevText_SetCursorX(text, 44);
            DevText_Printf(text, "%03.2f", ft->cur_anim_frame);
            if (ft->x221C_u16_y) {
                DevText_SetCursorX(text, 52);
                if (ft->x221C_u16_y & 1) {
                    DevText_Printf(text, "L", ft->x221C_u16_y);
                } else {
                    DevText_Printf(text, " ");
                }
                if (ft->x221C_u16_y & 2) {
                    DevText_Printf(text, "R", ft->x221C_u16_y);
                } else {
                    DevText_Printf(text, " ");
                }
                if (ft->x221C_u16_y & 4) {
                    DevText_Printf(text, "T", ft->x221C_u16_y);
                } else {
                    DevText_Printf(text, " ");
                }
            }
        }
    }
}

void fn_CheckAnimationInfo(int player)
{
    HSD_GObj* gobj;
    Fighter* ft;
    u8 _[0x20];

    if (db_ButtonsDown(player) & HSD_PAD_R) {
        if (db_ButtonsPressed(player) & HSD_PAD_DPADUP) {
            db_804D6B48.ShowFighterCollisionBubbles++;
            if (db_804D6B48.ShowFighterCollisionBubbles > 3) {
                db_804D6B48.ShowFighterCollisionBubbles = 1;
            }
            for (gobj = HSD_GObj_Entities->fighters; gobj != NULL;
                 gobj = gobj->next)
            {
                GET_FIGHTER(gobj)->x21FC_flag.u8 =
                    db_804D6B48.ShowFighterCollisionBubbles;
            }
        }
        if ((db_ButtonsPressed(player) & HSD_PAD_DPADRIGHT) &&
            Player_GetPlayerSlotType(player) != 3)
        {
            unsigned int x;
            gobj = Player_GetEntity(player);
            ft = GET_FIGHTER(gobj);
            x = (ft->x21FC_flag.u8 & 3) + 1;
            if (x > 3) {
                ft->x21FC_flag.u8 = 1;
            } else {
                ft->x21FC_flag.u8 = x;
            }
            fn_80225E6C(gobj, ft);
        }
        if (db_ButtonsPressed(player) & HSD_PAD_DPADLEFT) {
            fn_ToggleMiscFighterVisuals();
        }
    }
    if ((db_ButtonsDown(player) & HSD_PAD_Y) &&
        (db_ButtonsPressed(player) & HSD_PAD_DPADDOWN))
    {
        db_804D6B48.ShowAnimationInfo ^= 1;
        if (!db_804D6B48.ShowAnimationInfo) {
            DevText_HideBackground(db_AnimationInfo.text);
            DevText_HideText(db_AnimationInfo.text);
        } else {
            DevText_ShowBackground(db_AnimationInfo.text);
            DevText_ShowText(db_AnimationInfo.text);
        }
    }
    if (db_ButtonsDown(player) & HSD_PAD_Y) {
        if ((db_ButtonsPressed(player) & HSD_PAD_DPADLEFT) &&
            (Player_GetPlayerSlotType(player) != 3))
        {
            gobj = Player_GetEntity(player);
            if (db_ButtonsDown(player) & HSD_PAD_A) {
                Fighter_PoisonMushroomApply(gobj);
            } else {
                Fighter_SuperMushroomApply(gobj);
            }
        }
        if ((db_ButtonsPressed(player) & HSD_PAD_DPADRIGHT) &&
            (Player_GetPlayerSlotType(player) != 3))
        {
            gobj = Player_GetEntity(player);
            if (db_ButtonsDown(player) & HSD_PAD_A) {
                Fighter_PoisonMushroomEnd(gobj);
            } else {
                Fighter_SuperMushroomEnd(gobj);
            }
        }
    }
}
