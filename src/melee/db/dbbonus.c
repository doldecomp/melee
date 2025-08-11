#include "db.h"

#include <sysdolphin/baselib/memory.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonus.h>
#include <melee/un/un_2FC9.h>
#include <melee/un/un_3028.h>

static struct {
    GXColor bg;
    GXColor fg;
} db_TextColors[2] = {
    { { 0x00, 0x00, 0x00, 0x00 }, { 0xFF, 0x00, 0x00, 0xFF } },
    { { 0x80, 0x40, 0xFF, 0x80 }, { 0x00, 0x00, 0x00, 0xFF } }
};

static struct {
    u8 x0;
    UnkFlagStruct x1;
} db_804D6B98;

static struct {
    DevText* text;
    char buffer[1500];
}* db_804D6B9C;

void fn_SetupBonusInfo(void)
{
    fn_80228D18();
    fn_80228D38();
}

static void fn_80228D18(void)
{
    db_804D6B98.x0 = 0xFF;
    db_804D6B98.x1.b0 = 0;
}

static void fn_80228D38(void)
{
    HSD_GObj* gobj;
    int i;
    gobj = DevText_GetGObj();
    db_804D6B9C = HSD_MemAlloc(sizeof(*db_804D6B9C) * 2);
    for (i = 0; i < 2; i++) {
        db_804D6B9C[i].text =
            DevText_Create(i + 10, i * 300, 0, 25, 30, db_804D6B9C[i].buffer);
        if (db_804D6B9C[i].text != NULL) {
            DevText_Show(gobj, db_804D6B9C[i].text);
            DevText_HideCursor(db_804D6B9C[i].text);
            DevText_SetBGColor(db_804D6B9C[i].text,
                               db_TextColors[db_804D6B98.x1.b0].bg);
            DevText_SetTextColor(db_804D6B9C[i].text,
                                 db_TextColors[db_804D6B98.x1.b0].fg);
            DevText_SetScale(db_804D6B9C[i].text, 12.0F, 16.0F);
        }
    }
}

static void fn_80228E54(int arg0, int arg1, int arg2)
{
    DevText* text;
    s32 temp_r4;
    s32 bonus;
    s32 y_pos;

    y_pos = 0;
    text = db_804D6B9C[arg1].text;
    DevText_Erase(text);
    DevText_SetCursorXY(text, 0, 0);
    if (arg1 == 0) {
        DevText_Printf(text, "1P %7d 2P %7d\n", gm_8016C658(0),
                       gm_8016C658(1));
        DevText_Printf(text, "3P %7d 4P %7d\n", gm_8016C658(2),
                       gm_8016C658(3));
        DevText_Printf(text, "%dP screen %d", arg0 + 1, arg1);
        y_pos = 3;
    }
    DevText_SetCursorXY(text, 0, y_pos);
    for (bonus = arg2; bonus < 0xD7; bonus++) {
        if (pl_80039418(arg0, bonus) != 0) {
            if (y_pos >= 0x1E) {
                temp_r4 = arg1 + 1;
                if (temp_r4 < 2) {
                    fn_80228E54(arg0, temp_r4, bonus);
                    return;
                }
                DevText_Printf(text, "screen over!!");
                return;
            }
            if (gmDecisionGetType(bonus) == 0) {
                DevText_Printf(text, "%s", db_bonus_names[bonus]);
            } else {
                DevText_Printf(text, "%s : %d", db_bonus_names[bonus],
                               pl_80039418(arg0, bonus));
            }
            y_pos += 1;
            DevText_SetCursorXY(text, 0, y_pos);
        }
    }
}

static void fn_8022900C(int arg0)
{
    int i;

    if (db_804D6B98.x0 == arg0) {
        if (db_804D6B98.x1.b0) {
            db_804D6B98.x0 = 0xFF;
            db_804D6B98.x1.b0 = 0;
            for (i = 0; i < 2; i++) {
                DevText_HideBackground(db_804D6B9C[i].text);
                DevText_HideText(db_804D6B9C[i].text);
            }
        } else {
            db_804D6B98.x1.b0 = 1;
            for (i = 0; i < 2; i++) {
                DevText_SetBGColor(db_804D6B9C[i].text,
                                   db_TextColors[db_804D6B98.x1.b0].bg);
                DevText_SetTextColor(db_804D6B9C[i].text,
                                     db_TextColors[db_804D6B98.x1.b0].fg);
            }
        }
    } else {
        db_804D6B98.x0 = arg0;
        for (i = 0; i < 2; i++) {
            DevText_ShowBackground(db_804D6B9C[i].text);
            DevText_ShowText(db_804D6B9C[i].text);
            DevText_SetBGColor(db_804D6B9C[i].text,
                               db_TextColors[db_804D6B98.x1.b0].bg);
            DevText_SetTextColor(db_804D6B9C[i].text,
                                 db_TextColors[db_804D6B98.x1.b0].fg);
        }
    }
}

void fn_CheckBonusInfo(int player)
{
    if ((db_ButtonsDown(player) & HSD_PAD_B) &&
        (db_ButtonsPressed(player) & HSD_PAD_DPADLEFT))
    {
        fn_8022900C(player);
    }
    if (db_804D6B98.x0 == player) {
        if (Player_GetEntity(player) != NULL) {
            pl_80039450(player);
        }
        fn_80228E54(player, 0, 0);
    }
}
