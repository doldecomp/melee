#include "itnessyoyo.h"

#include <placeholder.h>

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/item.h"

void it_802BE598(Item_GObj* gobj)
{
    it_8026B724(gobj);
}

void it_802BE5B8(Item_GObj* gobj)
{
    it_8026B73C(gobj);
}

/// #it_802BE5D8

/// #it_802BE65C

/// #it_802BE958

/// #it_802BE9D8

void itNessyoyo_UnkMotion0_Phys(Item_GObj* gobj)
{
    it_802BF900(GET_ITEM(gobj));
}

/// #itNessyoyo_UnkMotion1_Phys

/// #itNessyoyo_UnkMotion2_Phys

/// #itNessyoyo_UnkMotion3_Phys

/// #itNessyoyo_UnkMotion3_Anim

/// #it_802BF030

/// #it_802BF180

/// #it_802BF28C

/// #it_802BF4A0

/// #it_802BF800

/// #it_802BF900

/// #it_802BFAFC

void itNessYoyo_Logic59_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

/// #it_802BFE5C

/// #it_802BFEC4

/// #it_802C0010

#ifdef MWERKS_GEKKO

#pragma push
asm void it_2725_Logic59_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    // clang-format off
    nofralloc
    mflr r0
    stw r0, 0x4(r1)
    stwu r1, -0x20(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r4
    lwz r31, 0x2c(r3)
    bl it_8026B894
    lwz r0, 0xde4(r31)
    cmplw r0, r30
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    addi r1, r1, 0x20
    mtlr r0
    blr
    // clang-format on
}
#pragma pop

#else

void it_2725_Logic59_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    NOT_IMPLEMENTED;
}

#endif
