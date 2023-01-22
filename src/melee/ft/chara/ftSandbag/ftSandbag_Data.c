#include <melee/ft/chara/ftSandbag/ftsandbag.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/types.h>

ActionState as_table_sandbag[] = {
    { 295, FLAGS_ZERO, 0x01400000, func_8014FC20, func_8014FC24, func_8014FC28,
      func_8014FC48, func_800761C8 },
};

char lbl_803D39B8[] = "PlSb.dat";
char lbl_803D39C4[] = "ftDataSandbag";
char lbl_803D39D4[] = "PlSbNr.dat";
char lbl_803D39E0[] = "PlySandbag_Share_joint";
char lbl_803D39F8[] = "PlySandbag_Share_matanim_joint";
char lbl_803D3A18[] = "PlSbAJ.dat";

Fighter_CostumeStrings lbl_803D3A24[] = {
    { lbl_803D39D4, lbl_803D39E0, lbl_803D39F8 },
};
