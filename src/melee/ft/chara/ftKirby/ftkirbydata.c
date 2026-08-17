#include "ftkirby.h"

char ftKb_Init_DatFilename[] = "PlKb.dat";
char ftKb_Init_DataName[] = "ftDataKirby";
char ftKb_Init_803CA320[] = "PlKbNr.dat";
char ftKb_Init_803CA32C[] = "PlyKirby5K_Share_joint";
char ftKb_Init_803CA344[] = "PlyKirby5K_Share_matanim_joint";
char ftKb_Init_803CA364[] = "PlKbYe.dat";
char ftKb_Init_803CA370[] = "PlyKirby5KYe_Share_joint";
char ftKb_Init_803CA38C[] = "PlyKirby5KYe_Share_matanim_joint";
char ftKb_Init_803CA3B0[] = "PlKbBu.dat";
char ftKb_Init_803CA3BC[] = "PlyKirby5KBu_Share_joint";
char ftKb_Init_803CA3D8[] = "PlyKirby5KBu_Share_matanim_joint";
char ftKb_Init_803CA3FC[] = "PlKbRe.dat";
char ftKb_Init_803CA408[] = "PlyKirby5KRe_Share_joint";
char ftKb_Init_803CA424[] = "PlyKirby5KRe_Share_matanim_joint";
char ftKb_Init_803CA448[] = "PlKbGr.dat";
char ftKb_Init_803CA454[] = "PlyKirby5KGr_Share_joint";
char ftKb_Init_803CA470[] = "PlyKirby5KGr_Share_matanim_joint";
char ftKb_Init_803CA494[] = "PlKbWh.dat";
char ftKb_Init_803CA4A0[] = "PlyKirby5KWh_Share_joint";
char ftKb_Init_803CA4BC[] = "PlyKirby5KWh_Share_matanim_joint";
char ftKb_Init_AnimDatFilename[] = "PlKbAJ.dat";

Fighter_DemoStrings ftKb_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileKirby",
    "ftDemoIntroMotionFileKirby",
    "ftDemoEndingMotionFileKirby",
    "ftDemoViWaitMotionFileKirby",
};

char* ftKb_Init_803CA5A4[] = {
    "ftDemoVi0501MotionFileKirby",
    NULL,
    NULL,
    "ftDemoVi0502MotionFileKirby",
};

Fighter_CostumeStrings ftKb_Init_CostumeStrings[] = {
    { ftKb_Init_803CA320, ftKb_Init_803CA32C, ftKb_Init_803CA344 },
    { ftKb_Init_803CA364, ftKb_Init_803CA370, ftKb_Init_803CA38C },
    { ftKb_Init_803CA3B0, ftKb_Init_803CA3BC, ftKb_Init_803CA3D8 },
    { ftKb_Init_803CA3FC, ftKb_Init_803CA408, ftKb_Init_803CA424 },
    { ftKb_Init_803CA448, ftKb_Init_803CA454, ftKb_Init_803CA470 },
    { ftKb_Init_803CA494, ftKb_Init_803CA4A0, ftKb_Init_803CA4BC },
};

ftKirby_CopyName ftKb_Init_803CA9D0[FTKIND_MAX] = {
    { "PlKbCpMr.dat", "ftDataKirbyCopyMario" },
    { "PlKbCpFx.dat", "ftDataKirbyCopyFox" },
    { "PlKbCpCa.dat", "ftDataKirbyCopyCaptain" },
    { "PlKbCpDk.dat", "ftDataKirbyCopyDonkey" },
    { NULL, NULL },
    { "PlKbCpKp.dat", "ftDataKirbyCopyKoopa" },
    { "PlKbCpLk.dat", "ftDataKirbyCopyLink" },
    { "PlKbCpSk.dat", "ftDataKirbyCopySeak" },
    { "PlKbCpNs.dat", "ftDataKirbyCopyNess" },
    { "PlKbCpPe.dat", "ftDataKirbyCopyPeach" },
    { "PlKbCpPp.dat", "ftDataKirbyCopyPopo" },
    { NULL, NULL },
    { "PlKbCpPk.dat", "ftDataKirbyCopyPikachu" },
    { "PlKbCpSs.dat", "ftDataKirbyCopySamus" },
    { "PlKbCpYs.dat", "ftDataKirbyCopyYoshi" },
    { "PlKbCpPr.dat", "ftDataKirbyCopyPurin" },
    { "PlKbCpMt.dat", "ftDataKirbyCopyMewtwo" },
    { "PlKbCpLg.dat", "ftDataKirbyCopyLuigi" },
    { "PlKbCpMs.dat", "ftDataKirbyCopyMars" },
    { "PlKbCpZd.dat", "ftDataKirbyCopyZelda" },
    { "PlKbCpCl.dat", "ftDataKirbyCopyClink" },
    { "PlKbCpDr.dat", "ftDataKirbyCopyDrmario" },
    { "PlKbCpFc.dat", "ftDataKirbyCopyFalco" },
    { "PlKbCpPc.dat", "ftDataKirbyCopyPichu" },
    { "PlKbCpGw.dat", "ftDataKirbyCopyGamewatch" },
    { "PlKbCpGn.dat", "ftDataKirbyCopyGanon" },
    { "PlKbCpFe.dat", "ftDataKirbyCopyEmblem" },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
};

char ftKb_Init_803CAAD8[] = "PlKbNrCpDk.dat";
char ftKb_Init_803CAAE8[] = "PlyKirbyDk_Share_joint";
char ftKb_Init_803CAB00[] = "PlyKirbyDk_Share_matanim_joint";
char ftKb_Init_803CAB20[] = "PlKbYeCpDk.dat";
char ftKb_Init_803CAB30[] = "PlyKirbyDkYe_Share_joint";
char ftKb_Init_803CAB4C[] = "PlyKirbyDkYe_Share_matanim_joint";
char ftKb_Init_803CAB70[] = "PlKbBuCpDk.dat";
char ftKb_Init_803CAB80[] = "PlyKirbyDkBu_Share_joint";
char ftKb_Init_803CAB9C[] = "PlyKirbyDkBu_Share_matanim_joint";
char ftKb_Init_803CABC0[] = "PlKbReCpDk.dat";
char ftKb_Init_803CABD0[] = "PlyKirbyDkRe_Share_joint";
char ftKb_Init_803CABEC[] = "PlyKirbyDkRe_Share_matanim_joint";
char ftKb_Init_803CAC10[] = "PlKbGrCpDk.dat";
char ftKb_Init_803CAC20[] = "PlyKirbyDkGr_Share_joint";
char ftKb_Init_803CAC3C[] = "PlyKirbyDkGr_Share_matanim_joint";
char ftKb_Init_803CAC60[] = "PlKbWhCpDk.dat";
char ftKb_Init_803CAC70[] = "PlyKirbyDkWh_Share_joint";
char ftKb_Init_803CAC8C[] = "PlyKirbyDkWh_Share_matanim_joint";

Fighter_CostumeStrings ftKb_Init_803CACB0[] = {
    { ftKb_Init_803CAAD8, ftKb_Init_803CAAE8, ftKb_Init_803CAB00 },
    { ftKb_Init_803CAB20, ftKb_Init_803CAB30, ftKb_Init_803CAB4C },
    { ftKb_Init_803CAB70, ftKb_Init_803CAB80, ftKb_Init_803CAB9C },
    { ftKb_Init_803CABC0, ftKb_Init_803CABD0, ftKb_Init_803CABEC },
    { ftKb_Init_803CAC10, ftKb_Init_803CAC20, ftKb_Init_803CAC3C },
    { ftKb_Init_803CAC60, ftKb_Init_803CAC70, ftKb_Init_803CAC8C },
};

char ftKb_Init_803CACF8[] = "PlKbNrCpPr.dat";
char ftKb_Init_803CAD08[] = "PlyKirbyPr_Share_joint";
char ftKb_Init_803CAD20[] = "PlyKirbyPr_Share_matanim_joint";
char ftKb_Init_803CAD40[] = "PlKbYeCpPr.dat";
char ftKb_Init_803CAD50[] = "PlyKirbyPrYe_Share_joint";
char ftKb_Init_803CAD6C[] = "PlyKirbyPrYe_Share_matanim_joint";
char ftKb_Init_803CAD90[] = "PlKbBuCpPr.dat";
char ftKb_Init_803CADA0[] = "PlyKirbyPrBu_Share_joint";
char ftKb_Init_803CADBC[] = "PlyKirbyPrBu_Share_matanim_joint";
char ftKb_Init_803CADE0[] = "PlKbReCpPr.dat";
char ftKb_Init_803CADF0[] = "PlyKirbyPrRe_Share_joint";
char ftKb_Init_803CAE0C[] = "PlyKirbyPrRe_Share_matanim_joint";
char ftKb_Init_803CAE30[] = "PlKbGrCpPr.dat";
char ftKb_Init_803CAE40[] = "PlyKirbyPrGr_Share_joint";
char ftKb_Init_803CAE5C[] = "PlyKirbyPrGr_Share_matanim_joint";
char ftKb_Init_803CAE80[] = "PlKbWhCpPr.dat";
char ftKb_Init_803CAE90[] = "PlyKirbyPrWh_Share_joint";
char ftKb_Init_803CAEAC[] = "PlyKirbyPrWh_Share_matanim_joint";

Fighter_CostumeStrings ftKb_Init_803CAED0[] = {
    { ftKb_Init_803CACF8, ftKb_Init_803CAD08, ftKb_Init_803CAD20 },
    { ftKb_Init_803CAD40, ftKb_Init_803CAD50, ftKb_Init_803CAD6C },
    { ftKb_Init_803CAD90, ftKb_Init_803CADA0, ftKb_Init_803CADBC },
    { ftKb_Init_803CADE0, ftKb_Init_803CADF0, ftKb_Init_803CAE0C },
    { ftKb_Init_803CAE30, ftKb_Init_803CAE40, ftKb_Init_803CAE5C },
    { ftKb_Init_803CAE80, ftKb_Init_803CAE90, ftKb_Init_803CAEAC },
};

char ftKb_Init_803CAF18[] = "PlKbNrCpMt.dat";
char ftKb_Init_803CAF28[] = "PlyKirbyMt_Share_joint";
char ftKb_Init_803CAF40[] = "PlyKirbyMt_Share_matanim_joint";
char ftKb_Init_803CAF60[] = "PlKbYeCpMt.dat";
char ftKb_Init_803CAF70[] = "PlyKirbyMtYe_Share_joint";
char ftKb_Init_803CAF8C[] = "PlyKirbyMtYe_Share_matanim_joint";
char ftKb_Init_803CAFB0[] = "PlKbBuCpMt.dat";
char ftKb_Init_803CAFC0[] = "PlyKirbyMtBu_Share_joint";
char ftKb_Init_803CAFDC[] = "PlyKirbyMtBu_Share_matanim_joint";
char ftKb_Init_803CB000[] = "PlKbReCpMt.dat";
char ftKb_Init_803CB010[] = "PlyKirbyMtRe_Share_joint";
char ftKb_Init_803CB02C[] = "PlyKirbyMtRe_Share_matanim_joint";
char ftKb_Init_803CB050[] = "PlKbGrCpMt.dat";
char ftKb_Init_803CB060[] = "PlyKirbyMtGr_Share_joint";
char ftKb_Init_803CB07C[] = "PlyKirbyMtGr_Share_matanim_joint";
char ftKb_Init_803CB0A0[] = "PlKbWhCpMt.dat";
char ftKb_Init_803CB0B0[] = "PlyKirbyMtWh_Share_joint";
char ftKb_Init_803CB0CC[] = "PlyKirbyMtWh_Share_matanim_joint";

Fighter_CostumeStrings ftKb_Init_803CB0F0[] = {
    { ftKb_Init_803CAF18, ftKb_Init_803CAF28, ftKb_Init_803CAF40 },
    { ftKb_Init_803CAF60, ftKb_Init_803CAF70, ftKb_Init_803CAF8C },
    { ftKb_Init_803CAFB0, ftKb_Init_803CAFC0, ftKb_Init_803CAFDC },
    { ftKb_Init_803CB000, ftKb_Init_803CB010, ftKb_Init_803CB02C },
    { ftKb_Init_803CB050, ftKb_Init_803CB060, ftKb_Init_803CB07C },
    { ftKb_Init_803CB0A0, ftKb_Init_803CB0B0, ftKb_Init_803CB0CC },
};

char ftKb_Init_803CB138[] = "PlKbNrCpFc.dat";
char ftKb_Init_803CB148[] = "PlyKirbyFc_Share_joint";
char ftKb_Init_803CB160[] = "PlyKirbyFc_Share_matanim_joint";
char ftKb_Init_803CB180[] = "PlKbYeCpFc.dat";
char ftKb_Init_803CB190[] = "PlyKirbyFcYe_Share_joint";
char ftKb_Init_803CB1AC[] = "PlyKirbyFcYe_Share_matanim_joint";
char ftKb_Init_803CB1D0[] = "PlKbBuCpFc.dat";
char ftKb_Init_803CB1E0[] = "PlyKirbyFcBu_Share_joint";
char ftKb_Init_803CB1FC[] = "PlyKirbyFcBu_Share_matanim_joint";
char ftKb_Init_803CB220[] = "PlKbReCpFc.dat";
char ftKb_Init_803CB230[] = "PlyKirbyFcRe_Share_joint";
char ftKb_Init_803CB24C[] = "PlyKirbyFcRe_Share_matanim_joint";
char ftKb_Init_803CB270[] = "PlKbGrCpFc.dat";
char ftKb_Init_803CB280[] = "PlyKirbyFcGr_Share_joint";
char ftKb_Init_803CB29C[] = "PlyKirbyFcGr_Share_matanim_joint";
char ftKb_Init_803CB2C0[] = "PlKbWhCpFc.dat";
char ftKb_Init_803CB2D0[] = "PlyKirbyFcWh_Share_joint";
char ftKb_Init_803CB2EC[] = "PlyKirbyFcWh_Share_matanim_joint";

Fighter_CostumeStrings ftKb_Init_803CB310[] = {
    { ftKb_Init_803CB138, ftKb_Init_803CB148, ftKb_Init_803CB160 },
    { ftKb_Init_803CB180, ftKb_Init_803CB190, ftKb_Init_803CB1AC },
    { ftKb_Init_803CB1D0, ftKb_Init_803CB1E0, ftKb_Init_803CB1FC },
    { ftKb_Init_803CB220, ftKb_Init_803CB230, ftKb_Init_803CB24C },
    { ftKb_Init_803CB270, ftKb_Init_803CB280, ftKb_Init_803CB29C },
    { ftKb_Init_803CB2C0, ftKb_Init_803CB2D0, ftKb_Init_803CB2EC },
};

char ftKb_Init_803CB358[] = "PlKbNrCpGw.dat";
char ftKb_Init_803CB368[] = "PlyKirbyGw_Share_joint";
char ftKb_Init_803CB380[] = "PlyKirbyGw_Share_matanim_joint";

Fighter_CostumeStrings ftKb_Init_803CB3A0[] = {
    { ftKb_Init_803CB358, ftKb_Init_803CB368, ftKb_Init_803CB380 },
    { ftKb_Init_803CB358, ftKb_Init_803CB368, ftKb_Init_803CB380 },
    { ftKb_Init_803CB358, ftKb_Init_803CB368, ftKb_Init_803CB380 },
    { ftKb_Init_803CB358, ftKb_Init_803CB368, ftKb_Init_803CB380 },
    { ftKb_Init_803CB358, ftKb_Init_803CB368, ftKb_Init_803CB380 },
    { ftKb_Init_803CB358, ftKb_Init_803CB368, ftKb_Init_803CB380 },
};

Fighter_CostumeStrings* ftKb_Init_803CB3E8[] = {
    NULL,
    NULL,
    NULL,
    ftKb_Init_803CACB0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKb_Init_803CAED0,
    ftKb_Init_803CB0F0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKb_Init_803CB310,
    NULL,
    ftKb_Init_803CB3A0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

u8 ftKb_Init_803CB46C[FTKIND_MAX] = {
    32, 33, 38, 39, -1, 41, 35, 21, 42, 45, 46, 46, 36, 34, 40, 43, 44,
    37, 20, 21, 35, 32, 33, 36, -1, 47, 48, -1, -1, -1, -1, -1, -1,
};
