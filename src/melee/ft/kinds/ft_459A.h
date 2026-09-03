/** @file
 * Each of these belong in their respective character file. They are all in
 * .bss, except for Link's, which is initialized to zero and so appears in
 * .data. See #CostumeListsForeachCharacter to determine indices. They are of
 * variable size, but the data is used uniformly across all characters, so the
 * first 0x18 bytes are probably used by #UnkCostumeStruct and then the rest is
 * character-specific .bss data used elsewhere.
 */
#ifndef GALE01_4599F0
#define GALE01_4599F0

#include "ft/forward.h"

/* 4599F0 */ extern UnkCostumeStruct lbl_804599F0;
/* 459A98 */ extern UnkCostumeStruct ft_80459A98;
/* 459B28 */ extern UnkCostumeStruct ft_80459B28;
/* 459C10 */ extern UnkCostumeStruct ft_80459C10;
/* 459CA0 */ extern UnkCostumeStruct ft_80459CA0;
/* 459D18 */ extern UnkCostumeStruct ft_80459D18;
/* 459D90 */ extern UnkCostumeStruct ft_80459D90;
/* 459DF0 */ extern UnkCostumeStruct ft_80459DF0;
/* 459E68 */ extern UnkCostumeStruct ft_80459E68;
/* 459EC8 */ extern UnkCostumeStruct ft_80459EC8;
/* 459F28 */ extern UnkCostumeStruct ft_80459F28;
/* 459F88 */ extern UnkCostumeStruct ft_80459F88;
/* 45A000 */ extern UnkCostumeStruct ft_8045A000;
/* 45A090 */ extern UnkCostumeStruct ft_8045A090;
/* 45A0F0 */ extern UnkCostumeStruct ft_8045A0F0;
/* 45A168 */ extern UnkCostumeStruct ft_8045A168;
/* 45A1F8 */ extern UnkCostumeStruct ft_8045A1F8;
/* 45A270 */ extern UnkCostumeStruct ft_8045A270;
/* 45A2D0 */ extern UnkCostumeStruct ft_8045A2D0;
/* 45A330 */ extern UnkCostumeStruct ft_8045A330;
/* 45A3A8 */ extern UnkCostumeStruct ft_8045A3A8;
/* 45A420 */ extern UnkCostumeStruct ft_8045A420;
/* 45A480 */ extern UnkCostumeStruct ft_8045A480;
/* 45A4E0 */ extern UnkCostumeStruct ft_8045A4E0;
/* 45A540 */ extern UnkCostumeStruct ft_8045A540;
/* 45A5B8 */ extern UnkCostumeStruct ft_8045A5B8;
/* 45A630 */ extern UnkCostumeStruct ft_8045A630;
/* 45A648 */ extern UnkCostumeStruct ft_8045A648;
/* 45A660 */ extern UnkCostumeStruct ft_8045A660;
/* 45A678 */ extern UnkCostumeStruct ft_8045A678;
/* 45A690 */ extern UnkCostumeStruct ft_8045A690;
/* 45A6A8 */ extern UnkCostumeStruct ft_8045A6A8;

#endif
