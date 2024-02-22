#include <platform.h>

#include "inlines.h"
#include "it_2725.h"
#include "types.h"

#include "mp/mpcoll.h"

#include <baselib/gobj.h>

bool it_8026D9A0(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    CollData* coll_data = &item->x378_itemColl;
    it_80276214(gobj);
    {
        u8 _[4];
        bool temp = mpColl_800477E0(coll_data);
        item->pos = coll_data->cur_topn;
        if (temp) {
            item->xC30 = coll_data->floor.index;
        }
        return temp;
    }
}
