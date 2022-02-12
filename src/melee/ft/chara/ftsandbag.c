#include "ftsandbag.h"

typedef struct _PairStruct {
    u32 x0_first;
    u32 x4_second;
    u8 padding[0xB8];
} PairStruct;

void ftSandbag_OnLoad(HSD_GObj* gobj) {
    Fighter* fighter = gobj->user_data;
    ftData* fighterDataInfo = fighter->x10C_ftData;

    PairStruct* extAttrs = (PairStruct *) fighterDataInfo->ext_attr;

    u32 ext_attr_first = extAttrs->x0_first;
    u32 ext_attr_second = extAttrs->x4_second;

    PairStruct* special_attr_2 = fighter->x2D8_specialAttributes2;

    special_attr_2->x0_first = ext_attr_first;
    special_attr_2->x4_second = ext_attr_second;

    fighter->x2D4_specialAttributes = special_attr_2;

    fighter->x2228_flag.bits.b2 = 1;
    fighter->x2226_flag.bits.b0 = 1;

    func_8014FA30(fighter);
}
