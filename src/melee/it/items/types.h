#ifndef MELEE_IT_ITEMS_TYPES_H
#define MELEE_IT_ITEMS_TYPES_H

#include "it/items/forward.h"

#include <placeholder.h>

struct itSword_UnkBytes {
    /*  +0 */ u8 x0;
};

struct itSword_UnkArticle1 {
    /*  +0 */ UNK_T x0;
    /*  +4 */ UNK_T x4;
    /*  +8 */ UNK_T x8;
    /*  +C */ float xC;
    /* +10 */ float x10;
    /* +14 */ float x14;
    /* +18 */ int x18;
    /* +1C */ itSword_UnkBytes x1C;
};

#endif
