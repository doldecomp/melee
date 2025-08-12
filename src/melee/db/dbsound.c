#include "db.h"

#include "un/un_3028.h"

#include <melee/lb/lbaudio_ax.h>
#include <melee/un/un_2FC9.h>

static char db_SoundInfoText_buf[0x70];

int db_804D4AF8 = 1;

static int db_SoundToggles;
static int db_ShowSoundInfo;
static int db_SoundRelated_6B68;
static int db_SoundRelated_6B6C;
static int db_SoundRelated_6B70;
static int db_SoundRelated_6B74;
static DevText* db_SoundInfoText;
static HSD_GObj* db_804D6B7C;

static int db_SoundToggleOrder[4] = { 3, 2, 0, 1 };

void fn_SetupSoundInfo(void)
{
    GXColor bg = { 0x80, 0x80, 0x80, 0x80 };
    GXColor fg = { 0xFF, 0xFF, 0xFF, 0xFF };
    db_804D6B7C = DevText_GetGObj();
    db_SoundToggles = 0;
    db_ShowSoundInfo = 0;
    db_SoundRelated_6B68 = 0;
    db_SoundRelated_6B6C = 0;
    db_SoundRelated_6B70 = 0;
    db_SoundRelated_6B74 = 0;
    if ((db_SoundInfoText =
             DevText_Create(9, 420, 60, 18, 3, db_SoundInfoText_buf)))
    {
        DevText_Show(db_804D6B7C, db_SoundInfoText);
        DevText_HideCursor(db_SoundInfoText);
        DevText_SetBGColor(db_SoundInfoText, bg);
        DevText_SetTextColor(db_SoundInfoText, fg);
        DevText_SetScale(db_SoundInfoText, 12, 16);
        DevText_HideBackground(db_SoundInfoText);
        DevText_HideText(db_SoundInfoText);
    }
}

void fn_UpdateSoundInfo(void)
{
    int x;
    lbAudioAx_80025098(3 < db_ShowSoundInfo ? 1 : 0);
    if (db_SoundInfoText) {
        switch (db_ShowSoundInfo) {
        case 0:
        case 1:
        case 2:
        case 3:
            DevText_HideBackground(db_SoundInfoText);
            DevText_HideText(db_SoundInfoText);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            x = lbAudioAx_80028B2C();
            if (db_SoundRelated_6B68 < x) {
                db_SoundRelated_6B68 = x;
                db_SoundRelated_6B6C = 0xF0;
            }
            db_SoundRelated_6B6C--;
            if (db_SoundRelated_6B6C <= 0) {
                db_SoundRelated_6B68 = x;
                db_SoundRelated_6B6C = 0;
            }
            x = lbAudioAx_80028B4C();
            if (db_SoundRelated_6B70 < x) {
                db_SoundRelated_6B70 = x;
                db_SoundRelated_6B74 = 0xF0;
            }
            db_SoundRelated_6B74--;
            if (db_SoundRelated_6B74 <= 0) {
                db_SoundRelated_6B70 = x;
                db_SoundRelated_6B74 = 0;
            }
            DevText_Erase(db_SoundInfoText);
            DevText_SetCursorXY(db_SoundInfoText, 1, 0);
            switch (db_SoundToggleOrder[db_SoundToggles] & 3) {
            case 0:
                DevText_Printf(db_SoundInfoText, "FGM:OFF  BGM:OFF");
                break;
            case 1:
                DevText_Printf(db_SoundInfoText, "FGM:OFF  BGM:ON ");
                break;
            case 2:
                DevText_Printf(db_SoundInfoText, "FGM:ON   BGM:OFF");
                break;
            case 3:
                DevText_Printf(db_SoundInfoText, "FGM:ON   BGM:ON ");
                break;
            }
            DevText_SetCursorXY(db_SoundInfoText, 1, 1);
            DevText_Printf(db_SoundInfoText, "PVoice  %3d  %3d\n", x,
                           db_SoundRelated_6B68);
            DevText_SetCursorXY(db_SoundInfoText, 1, 2);
            DevText_Printf(db_SoundInfoText, "VVoice  %3d  %3d", x,
                           db_SoundRelated_6B70);
            DevText_ShowBackground(db_SoundInfoText);
            DevText_ShowText(db_SoundInfoText);
            break;
        }
    } else {
        db_SoundRelated_6B68 = lbAudioAx_80028B2C();
        db_SoundRelated_6B6C = 0;
        db_SoundRelated_6B70 = lbAudioAx_80028B4C();
        db_SoundRelated_6B74 = 0;
    }
}

void fn_CheckSoundInfo(int player)
{
    int orig = db_SoundToggles;
    if (player == 0) {
        if (db_ButtonsPressed(player) & HSD_PAD_X) {
            if (db_ButtonsDown(player) & HSD_PAD_DPADLEFT) {
                db_SoundToggles = (db_SoundToggles + 1) % 4;
                db_ShowSoundInfo = (db_ShowSoundInfo + 1) % 8;
            }
        } else if ((db_ButtonsPressed(player) & HSD_PAD_DPADLEFT)) {
            if (db_ButtonsDown(player) & HSD_PAD_X) {
                db_SoundToggles = (db_SoundToggles + 1) % 4;
                db_ShowSoundInfo = (db_ShowSoundInfo + 1) % 8;
            }
        }
        if (db_SoundToggles != orig) {
            int temp = db_SoundToggleOrder[db_SoundToggles];
            lbAudioAx_80025064(temp & 1, temp & 2);
        }
    }
    fn_UpdateSoundInfo();
}
