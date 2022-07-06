#include "fticeclimber.h"

/// TODO remove float externs when file is finished and float data is removed from asm
extern f32 lbl_804D9898;


void ftNana_OnLoad(HSD_GObj* fighterObj) {
    s32 unused[4];
    Fighter* fighter = fighterObj->user_data;
    fighter->x2222_flag.bits.b4 = 1;
    ftIceClimber_OnLoadForNana(fighter);

    {
        ftIceClimberAttributes* attr = fighter->x2D4_specialAttributes;
        fighter->x40 = attr->xC4;
    }

}

void ftNana_OnDeath(HSD_GObj* fighterObj) {
    s32 unused;
    Fighter* fighter = fighterObj->user_data;
    ftIceClimberAttributes* attr = fighter->x2D4_specialAttributes;
    fighter->dmg.x18B0 = attr->xC8;
    func_80074A4C(fighterObj, 0U, 0);
    func_80074A4C(fighterObj, 1U, 0);
    fighter->sa.nana.x2234 = 0;
    fighter->sa.nana.x222C = 0;
    fighter->sa.nana.x2230.bits.b0 = 0;
    fighter->sa.nana.x2238 = 0;
    fighter->sa.nana.x224C = 0;
    fighter->sa.nana.x2250 = lbl_804D9898;
}