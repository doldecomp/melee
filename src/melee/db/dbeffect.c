#include "db.h"

#include <melee/if/ifall.h>

int db_MiscVisualEffectsStatus;

void fn_CheckMiscVisualEffects(int player)
{
    if ((db_ButtonsDown(player) & HSD_PAD_X) &&
        (db_ButtonsPressed(player) & HSD_PAD_DPADDOWN))
    {
        db_MiscVisualEffectsStatus++;
        if (db_MiscVisualEffectsStatus > 3) {
            db_MiscVisualEffectsStatus = 0;
        }
        if (db_MiscVisualEffectsStatus == 0) {
            ifAll_ShowHUD();
        } else if (!ifAll_IsHUDHidden()) {
            ifAll_HideHUD();
        }
    }
}
