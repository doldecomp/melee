#include "db.h"

#include <melee/pl/player.h>
#include <melee/un/un_2FC9.h>
#include <melee/un/un_3028.h>

static struct {
    DevText* text;
    char buf[0x34C];
} db_CpuHandicapInfo;

UnkFlagStruct db_ShowCpuHandicapInfo;

void fn_SetupCpuHandicapInfo(void)
{
    HSD_GObj* gobj = DevText_GetGObj();
    db_ShowCpuHandicapInfo.b0 = 0;
    db_CpuHandicapInfo.text =
        DevText_Create(6, 20, 20, 60, 7, db_CpuHandicapInfo.buf);
    if (db_CpuHandicapInfo.text != NULL) {
        GXColor bg = { 0x00, 0x00, 0x00, 0x00 };
        GXColor fg = { 0xFF, 0xFF, 0xFF, 0xFF };
        DevText_Show(gobj, db_CpuHandicapInfo.text);
        DevText_HideCursor(db_CpuHandicapInfo.text);
        DevText_SetBGColor(db_CpuHandicapInfo.text, bg);
        DevText_SetTextColor(db_CpuHandicapInfo.text, fg);
        DevText_SetScale(db_CpuHandicapInfo.text, 9.0F, 12.0F);
    }
}

void fn_UpdateCpuHandicapInfo(void)
{
    int stack[2];
    DevText* text;
    StaticPlayer* player;
    s32 slot;

    if (db_ShowCpuHandicapInfo.b0) {
        text = db_CpuHandicapInfo.text;
        DevText_Erase(text);
        DevText_SetCursorXY(text, 0, 0);
        DevText_Printf(text, "A B  C D E    F    G");
        for (slot = 0; slot < 6; slot++) {
            player = Player_GetPtrForSlot(slot);
            DevText_Printf(text, "\n%d %d %2d %d %2.2f %2.2f %2.2f",
                           player->player_state, player->cpu_level,
                           player->cpu_type, player->handicap, player->unk50,
                           player->attack_ratio, player->defense_ratio);
        }
    }
}

void fn_CheckCpuHandicapInfo(int player)
{
    if ((db_ButtonsDown(player) & HSD_PAD_B) &&
        (db_ButtonsPressed(player) & HSD_PAD_DPADDOWN))
    {
        db_ShowCpuHandicapInfo.b0 ^= 1;
        if (db_ShowCpuHandicapInfo.b0 == 0) {
            DevText_HideBackground(db_CpuHandicapInfo.text);
            DevText_HideText(db_CpuHandicapInfo.text);
            return;
        }
        DevText_ShowBackground(db_CpuHandicapInfo.text);
        DevText_ShowText(db_CpuHandicapInfo.text);
    }
}
