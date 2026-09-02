#include "hsd_397E.h"

#include <platform.h>

#include <dolphin/os.h>

#ifdef MWERKS_GEKKO
#include <MetroTRK/ppc_reg.h>
#endif

int baselib_mfspr(int spr)
{
    register int result;
    switch (spr) {
#ifdef MWERKS_GEKKO
    case 0x1:
        asm { mfxer result }
        break;
    case 0x8:
        asm { mflr result }
        break;
    case 0x9:
        asm { mfctr result }
        break;
    case 0x12:
        asm { mfdsisr result }
        break;
    case 0x13:
        asm { mfdar result }
        break;
    case 0x16:
        asm { mfdec result }
        break;
    case 0x19:
        asm { mfsdr1 result }
        break;
    case 0x1A:
        asm { mfsrr0 result }
        break;
    case 0x1B:
        asm { mfsrr1 result }
        break;
    case 0x110:
        asm { mfsprg result, 0 }
        break;
    case 0x111:
        asm { mfsprg result, 1 }
        break;
    case 0x112:
        asm { mfsprg result, 2 }
        break;
    case 0x113:
        asm { mfsprg result, 3 }
        break;
    case 0x118:
        asm { mfspr result, 0x118 } ///< unknown spr?
        break;
    case 0x11A:
        asm { mfear result }
        break;
    case 0x11F:
        asm { mfspr result, pvr }
        break;
    case 0x210:
        asm { mfibatu result, 0 }
        break;
    case 0x211:
        asm { mfibatl result, 0 }
        break;
    case 0x212:
        asm { mfibatu result, 1 }
        break;
    case 0x213:
        asm { mfibatl result, 1 }
        break;
    case 0x214:
        asm { mfibatu result, 2 }
        break;
    case 0x215:
        asm { mfibatl result, 2 }
        break;
    case 0x216:
        asm { mfibatu result, 3 }
        break;
    case 0x217:
        asm { mfibatl result, 3 }
        break;
    case 0x218:
        asm { mfdbatu result, 0 }
        break;
    case 0x219:
        asm { mfdbatl result, 0 }
        break;
    case 0x21A:
        asm { mfdbatu result, 1 }
        break;
    case 0x21B:
        asm { mfdbatl result, 1 }
        break;
    case 0x21C:
        asm { mfdbatu result, 2 }
        break;
    case 0x21D:
        asm { mfdbatl result, 2 }
        break;
    case 0x21E:
        asm { mfdbatu result, 3 }
        break;
    case 0x21F:
        asm { mfdbatl result, 3 }
        break;
    case 0x390:
        asm { mfspr result, gqr0 }
        break;
    case 0x391:
        asm { mfspr result, gqr1 }
        break;
    case 0x392:
        asm { mfspr result, gqr2 }
        break;
    case 0x393:
        asm { mfspr result, gqr3 }
        break;
    case 0x394:
        asm { mfspr result, gqr4 }
        break;
    case 0x395:
        asm { mfspr result, gqr5 }
        break;
    case 0x396:
        asm { mfspr result, gqr6 }
        break;
    case 0x397:
        asm { mfspr result, gqr7 }
        break;
    case 0x398:
        asm { mfspr result, SPR_HID2
        } ///< hid2 gives incorrect codegen? compiler bug?
        break;
    case 0x399:
        asm { mfspr result, wpar }
        break;
    case 0x39A:
        asm { mfspr result, dma_u }
        break;
    case 0x39B:
        asm { mfspr result, dma_l }
        break;
    case 0x3A8:
        asm { mfspr result, ummcr0 }
        break;
    case 0x3A9:
        asm { mfspr result, upmc1 }
        break;
    case 0x3AA:
        asm { mfspr result, upmc2 }
        break;
    case 0x3AB:
        asm { mfspr result, usia }
        break;
    case 0x3AC:
        asm { mfspr result, ummcr1 }
        break;
    case 0x3AD:
        asm { mfspr result, upmc3 }
        break;
    case 0x3AE:
        asm { mfspr result, upmc4 }
        break;
    case 0x3AF:
        asm { mfspr result, SPR_USDA } ///< usda not recognized by compiler?
        break;
    case 0x3B8:
        asm { mfspr result, mmcr0 }
        break;
    case 0x3B9:
        asm { mfspr result, pmc1 }
        break;
    case 0x3BA:
        asm { mfspr result, pmc2 }
        break;
    case 0x3BB:
        asm { mfspr result, sia }
        break;
    case 0x3BC:
        asm { mfspr result, mmcr1 }
        break;
    case 0x3BD:
        asm { mfspr result, pmc3 }
        break;
    case 0x3BE:
        asm { mfspr result, pmc4 }
        break;
    case 0x3BF:
        asm { mfspr result, sda }
        break;
    case 0x3F0:
        asm { mfspr result, hid0 }
        break;
    case 0x3F1:
        asm { mfspr result, hid1 }
        break;
    case 0x3F2:
        asm { mfspr result, iabr }
        break;
    case 0x3F5:
        asm { mfspr result, dabr }
        break;
    case 0x3F9:
        asm { mfspr result, l2cr }
        break;
    case 0x3FB:
        asm { mfspr result, ictc }
        break;
    case 0x3FC:
        asm { mfspr result, thrm1 }
        break;
    case 0x3FD:
        asm { mfspr result, thrm2 }
        break;
    case 0x3FE:
        asm { mfspr result, thrm3 }
        break;
#endif
    default:
        OSReport("unsupported no. of special purpose register (%d).", spr);
        return 0;
    }
    return result;
}
