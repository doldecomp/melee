#include "ftpikachu.h"

void func_801243AC(Fighter* fighter) {
    ftPikachuAttributes* pika_attr = (ftPikachuAttributes*) fighter->x2D8_specialAttributes2;
    ftPikachuAttributes* ext_attr = (ftPikachuAttributes*) fighter->x10C_ftData->ext_attr;
    *pika_attr = *ext_attr;
    fighter->x2D4_specialAttributes = pika_attr;
}




void ftPikachu_OnLoad(HSD_GObj* fighterObj) {
  void **item_list;
  ftData *fighter_data;
  ftPikachuAttributes *ext_attr;
  ftPikachuAttributes *pika_attr_;

  s32 unused[2];

  ftPikachuAttributes *pika_attr;

  Fighter *fighter = fighterObj->user_data;
    
  fighter_data = fighter->x10C_ftData;
  pika_attr_ = fighter->x2D8_specialAttributes2;
    
  item_list = fighter_data->x48_items;
  ext_attr = fighter_data->ext_attr;

  *pika_attr_ = *ext_attr;

  fighter->x2D4_specialAttributes = pika_attr_;
  pika_attr = fighter->x2D4_specialAttributes;
    
  func_8026B3F8(item_list[0], pika_attr->xDC);
  func_8026B3F8(item_list[1], pika_attr->x14);
  func_8026B3F8(item_list[2], pika_attr->x18);

}


/////  Match from samer
// void func_8012764C(HSD_GObj* arg0) {
//     Fighter* fighter = arg0->user_data;
//     fighter->x2344_stateVar2 = 3;
// }