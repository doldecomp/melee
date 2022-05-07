#include "ftpikachu.h"

void func_801243AC(Fighter* ft) {
    ftPikachuAttributes* sA2 = (ftPikachuAttributes*)ft->x2D8_specialAttributes2;
    ftPikachuAttributes* ext_attr = (ftPikachuAttributes*)ft->x10C_ftData->ext_attr;
    *sA2 = *ext_attr;
    ft->x2D4_specialAttributes = sA2;
}