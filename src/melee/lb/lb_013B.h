#ifndef GALE01_013C18
#define GALE01_013C18

#include <Runtime/platform.h>

#include <melee/ft/forward.h>
#include <melee/lb/forward.h>

#include <dat_macros.h>

/// An entry of `lbRumbleData` (LbRb.dat): the rumble patterns #lb_80014574
/// plays.
typedef struct lbRumbleEntry {
    /// A rumble script, for #HSD_PadRumbleAdd.
    /* +0 */ union HSD_Rumble* list DAT_TERMINATED(0);
    /* +4 */ u8 pri;
    /* +5 */ u8 x5;
} lbRumbleEntry;

bool lb_80014258(Fighter_GObj* gobj, void* arg1, FtCmd2 cmd);
void lb_80014498(ColorOverlay*);
bool lb_800144C8(ColorOverlay*, struct Fighter_804D653C_t*, int, int);
void lb_80014534(void);
void lb_80014574(u8, int, int, int);
void lb_800145C0(u8 slot);
void lb_800145F4(void);

#endif
