#ifndef MELEE_IT_ITEMS_TYPES_H
#define MELEE_IT_ITEMS_TYPES_H

#include "it/items/forward.h"

#include <placeholder.h>

struct itSword_UnkBytes {
    /*   +0 */ u8 x0;
    /*   +1 */ u8 x1;
    /*   +2 */ u8 x2;
    /*   +3 */ u8 x3;
    /*   +4 */ u8 x4;
    /*   +5 */ u8 x5;
    /*   +6 */ u8 x6;
    /*   +7 */ u8 x7;
    /*   +8 */ u8 x8;
    /*   +9 */ u8 x9;
    /*   +A */ u8 xA;
    /*   +B */ u8 xB;
    /*   +C */ u8 xC;
    /*   +D */ u8 xD;
    /*   +E */ u8 xE;
    /*   +F */ u8 xF;
    /*  +10 */ u8 x10;
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
