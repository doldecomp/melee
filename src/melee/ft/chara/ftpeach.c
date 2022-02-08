#include "ftpeach.h"

void func_8011B51C(HSD_GObj* gobj) 
{
    Fighter* ft;

    ft = gobj->user_data;
    ft->x222C = 1;
    ft->x2234 = -1;
    ft->x2240 = 0;
    ft->x223C = 0;
    ft->x2238 = 0;
    ft->x2244 = 0;
    ft->x2248 = 0;
    func_80074A4C(gobj, 0, 0);
    func_80074A4C(gobj, 2, 0);
    func_80074A4C(gobj, 3, -1);
    func_80074A4C(gobj, 4, 0);

    switch (ft->x619_flag)
    {
        case 1:
            func_80074A4C(gobj, 1, -1);
            func_80074A4C(gobj, 5, 0);
            func_80074A4C(gobj, 6, -1);
            break;

        default:
            func_80074A4C(gobj, 1, 0);
            func_80074A4C(gobj, 5, -1);
            func_80074A4C(gobj, 6, 0);
            break;
    }
}

void ftPeach_OnLoad(HSD_GObj* gobj)
{
    
}
