#include "lbcommand.h"

extern const f64 lbl_804D79E0;

// Reset
void Command_00(CommandInfo* info)
{
    info->data_position = 0;
}

//Set Timer
#ifdef NON_MATCHING
void Command_04(CommandInfo* info)
{
    info->timer += *info->data_position & 0x3ffffff;
    info->data_position += 1;
}
#else
asm void Command_04(CommandInfo* info)
{
    nofralloc
    stwu r1, -0x18(r1)
    lis r0, 0x4330
    lwz r4, 8(r3)
    lfd f1, lbl_804D79E0(r2)
    lwz r4, 0(r4)
    lfs f2, 0(r3)
    clrlwi r4, r4, 6
    stw r4, 0x14(r1)
    stw r0, 0x10(r1)
    lfd f0, 0x10(r1)
    fsubs f0, f0, f1
    fadds f0, f2, f0
    stfs f0, 0(r3)
    lwz r4, 8(r3)
    addi r0, r4, 4
    stw r0, 8(r3)
    addi r1, r1, 0x18
    blr 
}
#endif

//Adjust Timer
#ifdef NON_MATCHING
void Command_08(CommandInfo* info)
{
    info->timer = (*info->data_position & 0x3ffffff) - info->frame_count;
    info->data_position += 1;
}
#else
asm void Command_08(CommandInfo* info)
{
    nofralloc
    stwu r1, -0x18(r1)
    lis r0, 0x4330
    lwz r4, 8(r3)
    lfd f2, lbl_804D79E0(r2)
    lwz r4, 0(r4)
    lfs f0, 4(r3)
    clrlwi r4, r4, 6
    stw r4, 0x14(r1)
    stw r0, 0x10(r1)
    lfd f1, 0x10(r1)
    fsubs f1, f1, f2
    fsubs f0, f1, f0
    stfs f0, 0(r3)
    lwz r4, 8(r3)
    addi r0, r4, 4
    stw r0, 8(r3)
    addi r1, r1, 0x18
    blr 
}
#endif
