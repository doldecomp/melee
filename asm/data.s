.section .data  # 0x803B9840 - 0x804316C0

.include "macros.inc"

.global lbl_803B9840
lbl_803B9840:
	.incbin "baserom.dol", 0x3B6840, 0x40
.global lbl_803B9880
lbl_803B9880:
	.incbin "baserom.dol", 0x3B6880, 0xA8
.global lbl_803B9928
lbl_803B9928:
	.incbin "baserom.dol", 0x3B6928, 0x698
.global lbl_803B9FC0
lbl_803B9FC0:
	.incbin "baserom.dol", 0x3B6FC0, 0x20
.global lbl_803B9FE0
lbl_803B9FE0:
	.incbin "baserom.dol", 0x3B6FE0, 0x10
.global lbl_803B9FF0
lbl_803B9FF0:
	.incbin "baserom.dol", 0x3B6FF0, 0x10
.global lbl_803BA000
lbl_803BA000:
	.incbin "baserom.dol", 0x3B7000, 0x20
.global lbl_803BA020
lbl_803BA020:
	.incbin "baserom.dol", 0x3B7020, 0x10
.global lbl_803BA030
lbl_803BA030:
	.incbin "baserom.dol", 0x3B7030, 0x10
.global lbl_803BA040
lbl_803BA040:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3B704C, 0x4
.global lbl_803BA050
lbl_803BA050:
    .asciz "lbvector.c"
    .balign 4
    .asciz "pos3d->x>-50000.0F&&pos3d->x<50000.0F"
    .balign 4
    .asciz "pos3d->y>-50000.0F&&pos3d->y<50000.0F"
    .balign 4
    .asciz "pos3d->z>-50000.0F&&pos3d->z<50000.0F"
    .balign 4
    .incbin "baserom.dol", 0x3B70D4, 0x4
.global lbl_803BA0D8
lbl_803BA0D8:
    .asciz "lbshadow.c"
    .balign 4
.global lbl_803BA0E4
lbl_803BA0E4:
    .asciz "lbshadow"
    .balign 4
    .asciz "shadow.h"
    .balign 4
.global lbl_803BA0FC
lbl_803BA0FC:
	.incbin "baserom.dol", 0x3B70FC, 0x54
.global lbl_803BA150
lbl_803BA150:
    .asciz "active deffect:"
    .balign 4
    .asciz "[NULL]\n\n"
    .balign 4
    .asciz "free deffect:"
    .balign 4
    .asciz "[NULL]\n\n\n"
    .balign 4
    .asciz "translate"
    .balign 4
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3B71BC, 0x4
.global lbl_803BA1C0
lbl_803BA1C0:
    .asciz "lbspdisplay.c"
    .balign 4
.global lbl_803BA1D0
lbl_803BA1D0:
    .asciz "!image_desc->image_ptr"
    .balign 4
    .incbin "baserom.dol", 0x3B71E8, 0x60
.global lbl_803BA248
lbl_803BA248:
	.incbin "baserom.dol", 0x3B7248, 0x58
.global lbl_803BA2A0
lbl_803BA2A0:
    .asciz "LbRb.dat"
    .balign 4
.global lbl_803BA2AC
lbl_803BA2AC:
    .asciz "lbRumbleData"
    .balign 4
    .incbin "baserom.dol", 0x3B72BC, 0x4
.global lbl_803BA2C0
lbl_803BA2C0:
    .asciz "lbmemory.c"
    .balign 4
    .asciz "_p(free_heap)"
    .balign 4
    .asciz "(u32)arenaLo >= (u32)_p(a_arenaLo) && (u32)arenaHi <= (u32)_p(a_arenaHi)"
    .balign 4
    .asciz "_p(free_mem)"
    .balign 4
    .asciz "memp_kouho"
    .balign 4
.global lbl_803BA344
lbl_803BA344:
    .asciz "[LbMem] Error: lbMemFreeToHeap %x.\n"
    .balign 4
    .asciz "!p->size"
    .balign 4
    .asciz "!cancelflag"
    .balign 4
.global lbl_803BA380
lbl_803BA380:
	.incbin "baserom.dol", 0x3B7380, 0x50
.global lbl_803BA3D0
lbl_803BA3D0:
    .asciz "lbheap.c"
    .balign 4
.global lbl_803BA3DC
lbl_803BA3DC:
    .asciz "p->status == LbHeapStatus_Create"
    .balign 4
    .asciz "     Hsd"
    .balign 4
    .asciz "    ARAM"
    .balign 4
    .asciz "     Seq"
    .balign 4
    .asciz "    Stay"
    .balign 4
    .asciz "    AllM"
    .balign 4
    .asciz "    AllA"
    .balign 4
    .incbin "baserom.dol", 0x3B7448, 0xC0
.global lbl_803BA508
lbl_803BA508:
    .asciz "lbfile.c"
    .balign 4
.global lbl_803BA514
lbl_803BA514:
    .asciz "!cancelflag"
    .balign 4
.global lbl_803BA520
lbl_803BA520:
    .asciz "Error : file name too long %s."
    .balign 4
.global lbl_803BA540
lbl_803BA540:
    .asciz "Cannot open file no=%d."
    .balign 4
    .asciz "file isn't exist %s = %d\n"
    .balign 4
    .asciz "entry_num != -1"
    .balign 4
    .incbin "baserom.dol", 0x3B7584, 0x4
.global lbl_803BA588
lbl_803BA588:
    .asciz "HSD_ArchiveParse error!\n"
    .balign 4
.global lbl_803BA5A4
lbl_803BA5A4:
    .asciz "lbarchive.c"
    .balign 4
.global lbl_803BA5B0
lbl_803BA5B0:
    .asciz "Cannot find symbol %s.\n"
    .balign 4
    .asciz "archive->flags & HSD_ARCHIVE_DONT_FREE"
    .balign 4
.global lbl_803BA5F0
lbl_803BA5F0:
    .asciz "lbArchiveRelocate: byte-order mismatch! Please check data format %x %x\n"
    .balign 4
.global lbl_803BA638
lbl_803BA638:
	.incbin "baserom.dol", 0x3B7638, 0x54
.global lbl_803BA68C
lbl_803BA68C:
	.incbin "baserom.dol", 0x3B768C, 0x1C
.global lbl_803BA6A8
lbl_803BA6A8:
    .asciz "free_index != -1"
    .balign 4
    .asciz "LbRb.dat"
    .balign 4
    .asciz "EfMnData.dat"
    .balign 4
    .asciz "EfCoData.dat"
    .balign 4
.global lbl_803BA6E8
lbl_803BA6E8:
    .asciz "[LbDvd] %s is not PRELOADed.\n"
    .balign 4
.global lbl_803BA708
lbl_803BA708:
	.incbin "baserom.dol", 0x3B7708, 0x3A0
.global jtbl_803BAAA8
jtbl_803BAAA8:
	.incbin "baserom.dol", 0x3B7AA8, 0x38
.global lbl_803BAAE0
lbl_803BAAE0:
    .asciz "lbcardnew.c"
    .balign 4
.global lbl_803BAAEC
lbl_803BAAEC:
    .asciz "i != LbCardNewTaskArray_Max"
    .balign 4
.global lbl_803BAB08
lbl_803BAB08:
	.incbin "baserom.dol", 0x3B7B08, 0x38
.global lbl_803BAB40
lbl_803BAB40:
    .asciz "_p(work_area)"
    .balign 4
.global lbl_803BAB50
lbl_803BAB50:
    .asciz "_p(lib_area)"
    .balign 4
.global lbl_803BAB60
lbl_803BAB60:
	.incbin "baserom.dol", 0x3B7B60, 0x14
.global lbl_803BAB74
lbl_803BAB74:
	.incbin "baserom.dol", 0x3B7B74, 0xE8
.global lbl_803BAC5C
lbl_803BAC5C:
    .asciz "SuperSmashBros0110290334"
    .balign 4
.global lbl_803BAC78
lbl_803BAC78:
    .asciz "lbcardgame.c"
    .balign 4
.global lbl_803BAC88
lbl_803BAC88:
    .asciz "_p(enable)"
    .balign 4
    .asciz "LbMcGame."
    .balign 4
    .asciz "MemCardIconData"
    .balign 4
    .asciz "ScNtcCommon_scene_data"
    .balign 4
.global lbl_803BACC8
lbl_803BACC8:
	.incbin "baserom.dol", 0x3B7CC8, 0x2C
.global lbl_803BACF4
lbl_803BACF4:
    .asciz "lbsnap.c"
    .balign 4
.global lbl_803BAD00
lbl_803BAD00:
    .asciz "index < _p(slot)[chan].num"
    .balign 4
    .incbin "baserom.dol", 0x3B7D1C, 0x74
.global lbl_803BAD90
lbl_803BAD90:
    .asciz "LbMcSnap."
    .balign 4
.global lbl_803BAD9C
lbl_803BAD9C:
    .asciz "MemSnapIconData"
    .balign 4
    .incbin "baserom.dol", 0x3B7DAC, 0x4
.global lbl_803BADB0
lbl_803BADB0:
    .asciz "lbmthp.c"
    .balign 4
    .asciz "!cancelflag"
    .balign 4
    .asciz "filnum = %d, ofs = %d, by sugano."
    .balign 4
    .asciz "(u32)streamPlayer->currPackedSize != 0"
    .balign 4
.global lbl_803BAE14
lbl_803BAE14:
    .asciz "Warning : frame offsets not supported\n"
    .balign 4
.global lbl_803BAE3C
lbl_803BAE3C:
    .asciz "Warning : file format is newer than player\n"
    .balign 4
    .asciz "by sugano & yoshiki.\n"
    .balign 4
    .asciz "base %x\n"
    .balign 4
    .asciz "size %d\n"
    .balign 4
    .asciz "count %d\n"
    .balign 4
    .asciz "csizep %x\n"
    .balign 4
    .asciz "[LbMthp] magic = %s\n"
    .balign 4
    .asciz "[LbMthp] version = %d\n"
    .balign 4
    .asciz "[LbMthp] bufSize = %d\n"
    .balign 4
    .asciz "[LbMthp] xSize = %d\n"
    .balign 4
    .asciz "[LbMthp] ySize = %d\n"
    .balign 4
    .asciz "[LbMthp] framerate = %d\n"
    .balign 4
    .asciz "[LbMthp] numFrames = %d\n"
    .balign 4
    .asciz "[LbMthp] firstFrame = %d\n"
    .balign 4
    .asciz "[LbMthp] frameOffsets = %d\n"
    .balign 4
    .asciz "[LbMthp] firstFrameSize = %d\n"
    .balign 4
    .asciz "!MoviePlayer.power"
    .balign 4
    .asciz "heap_size >= memoryRequired"
    .balign 4
    .incbin "baserom.dol", 0x3B7FE8, 0x40
.global lbl_803BB028
lbl_803BB028:
	.incbin "baserom.dol", 0x3B8028, 0x38
.global lbl_803BB060
lbl_803BB060:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803BB088
lbl_803BB088:
    .asciz "LbBf.dat"
    .balign 4
.global lbl_803BB094
lbl_803BB094:
    .asciz "lbBgFlashColAnimData"
    .balign 4
    .incbin "baserom.dol", 0x3B80AC, 0x4
.global lbl_803BB0B0
lbl_803BB0B0:
    .asciz "?"
    .balign 4
    .incbin "baserom.dol", 0x3B80B4, 0x2C
.global lbl_803BB0E0
lbl_803BB0E0:
	.incbin "baserom.dol", 0x3B80E0, 0x1FC
.global lbl_803BB2DC
lbl_803BB2DC:
    .asciz "lbRefSetUnuse error!\n"
    .balign 4
.global lbl_803BB2F4
lbl_803BB2F4:
    .asciz "lbrefract.c"
    .balign 4
.global lbl_803BB300
lbl_803BB300:
	.incbin "baserom.dol", 0x3B8300, 0xC0
.global lbl_803BB3C0
lbl_803BB3C0:
	.incbin "baserom.dol", 0x3B83C0, 0x210
.global lbl_803BB5D0
lbl_803BB5D0:
	.incbin "baserom.dol", 0x3B85D0, 0xE0
.global lbl_803BB6B0
lbl_803BB6B0:
	.incbin "baserom.dol", 0x3B86B0, 0x150
.global lbl_803BB800
lbl_803BB800:
	.incbin "baserom.dol", 0x3B8800, 0xD4
.global lbl_803BB8D4
lbl_803BB8D4:
	.incbin "baserom.dol", 0x3B88D4, 0xBCC
.global lbl_803BC4A0
lbl_803BC4A0:
	.incbin "baserom.dol", 0x3B94A0, 0x44
.global lbl_803BC4E4
lbl_803BC4E4:
	.incbin "baserom.dol", 0x3B94E4, 0x418
.global lbl_803BC8FC
lbl_803BC8FC:
    .asciz "LbAd.dat"
    .balign 4
.global lbl_803BC908
lbl_803BC908:
    .asciz "lbAudioLoadData"
    .balign 4
    .incbin "baserom.dol", 0x3B9918, 0x84
.global jtbl_803BC99C
jtbl_803BC99C:
	.incbin "baserom.dol", 0x3B999C, 0x88
.global lbl_803BCA24
lbl_803BCA24:
	.incbin "baserom.dol", 0x3B9A24, 0xF4
.global lbl_803BCB18
lbl_803BCB18:
	.incbin "baserom.dol", 0x3B9B18, 0x4C
.global lbl_803BCB64
lbl_803BCB64:
	.incbin "baserom.dol", 0x3B9B64, 0x38
.global lbl_803BCB9C
lbl_803BCB9C:
	.incbin "baserom.dol", 0x3B9B9C, 0x14
.global lbl_803BCBB0
lbl_803BCBB0:
    .asciz "couldn't get CmSubject struct.\n"
    .balign 4
.global lbl_803BCBD0
lbl_803BCBD0:
    .asciz "camera.c"
    .balign 4
    .asciz "fov_u<MTXDegToRad(90.0F)"
    .balign 4
    .asciz "fov_d<MTXDegToRad(90.0F)"
    .balign 4
    .asciz "fov_r<MTXDegToRad(90.0F)"
    .balign 4
    .asciz "fov_l<MTXDegToRad(90.0F)"
    .balign 4
.global jtbl_803BCC4C
jtbl_803BCC4C:
	.incbin "baserom.dol", 0x3B9C4C, 0x54
.global lbl_803BCCA0
lbl_803BCCA0:
	.incbin "baserom.dol", 0x3B9CA0, 0xF0
.global lbl_803BCD90
lbl_803BCD90:
    .asciz "cmsnap.c"
    .balign 4
.global lbl_803BCD9C
lbl_803BCD9C:
    .asciz "_p(status) == CmSnapStatus_Sleep"
    .balign 4
.global lbl_803BCDC0
lbl_803BCDC0:
    .asciz "PdPm.dat"
    .balign 4
.global lbl_803BCDCC
lbl_803BCDCC:
    .asciz "plLoadCommonData"
    .balign 4
.global lbl_803BCDE0
lbl_803BCDE0:
	.incbin "baserom.dol", 0x3B9DE0, 0x64
.global lbl_803BCE44
lbl_803BCE44:
    .asciz "cant get player struct! %d\n"
    .balign 4
.global lbl_803BCE60
lbl_803BCE60:
    .asciz "player.c"
    .balign 4
    .incbin "baserom.dol", 0x3B9E6C, 0x4
.global lbl_803BCE70
lbl_803BCE70:
	.incbin "baserom.dol", 0x3B9E70, 0x40
.global lbl_803BCEB0
lbl_803BCEB0:
    .asciz "pltrick.c"
    .balign 4
.global lbl_803BCEBC
lbl_803BCEBC:
    .asciz "0 <= h_player && h_player < 8"
    .balign 4
    .asciz "PlATK_AttackNormal_Start <= kind && kind <= PlATK_AttackNormal_End"
    .balign 4
.global lbl_803BCF20
lbl_803BCF20:
    .asciz "plbonus.c"
    .balign 4
    .asciz "player != Gm_Player_Other"
    .balign 4
    .asciz "gmDecisionGetType(kind) == Gm_DecType_Flag"
    .balign 4
.global lbl_803BCF74
lbl_803BCF74:
    .asciz "gmDecisionGetType(kind) == Gm_DecType_Point"
    .balign 4
    .asciz "plbonusinline.h"
    .balign 4
    .asciz "total != 0.0F"
    .balign 4
.global lbl_803BCFC0
lbl_803BCFC0:
	.incbin "baserom.dol", 0x3B9FC0, 0x54
.global lbl_803BD014
lbl_803BD014:
	.incbin "baserom.dol", 0x3BA014, 0x9C
.global jtbl_803BD0B0
jtbl_803BD0B0:
	.incbin "baserom.dol", 0x3BA0B0, 0x7C
.global lbl_803BD12C
lbl_803BD12C:
    .asciz "plbonuslib.c"
    .balign 4
.global lbl_803BD13C
lbl_803BD13C:
    .asciz "pl_itemlog_kind < Pl_ItemLog_Terminate"
    .balign 4
.global lbl_803BD164
lbl_803BD164:
    .asciz "It_PKind_Start <= itGetKind(igobj) && itGetKind(igobj) < It_PKind_Terminate"
    .balign 4
.global lbl_803BD1B0
lbl_803BD1B0:
    .asciz "It_PKind_Start <= kind && kind < It_PKind_Terminate"
    .balign 4
.global lbl_803BD1E4
lbl_803BD1E4:
    .asciz "plbonusinline.h"
    .balign 4
.global lbl_803BD1F4
lbl_803BD1F4:
    .asciz "total != 0.0F"
    .balign 4
    .asciz "zako ko player illegal ! :%d\n"
    .balign 4
    .asciz "0 <= player && player < Gm_Player_NumMax"
    .balign 4
.global lbl_803BD250
lbl_803BD250:
    .asciz "plbonusinline.h"
    .balign 4
.global lbl_803BD260
lbl_803BD260:
    .asciz "total != 0.0F"
    .balign 4
.global lbl_803BD270
lbl_803BD270:
    .asciz "%s:%d: Error: mpCollPrev() pos(%f,%f) player=%d ms=%d\n"
    .balign 4
.global lbl_803BD2A8
lbl_803BD2A8:
    .asciz "mpcoll.c"
    .balign 4
    .asciz "%s:%d: Error: mpCollPrev() pos(%f,%f) gobj_id=%d\n"
    .balign 4
    .asciz "itkind=%d\n"
    .balign 4
    .asciz "i<MPCOLL_WALLID_MAX"
    .balign 4
    .asciz "%s:%d: Error: mpCollEnd() last(%f,%f) pos(%f,%f) ply=%d ms=%d\n"
    .balign 4
    .asciz "%s:%d: Error: mpCollEnd() last(%f,%f) pos(%f,%f) gobjid=%d\n"
    .balign 4
.global lbl_803BD384
lbl_803BD384:
    .asciz "not support rotate at JObj type coll\n"
    .balign 4
.global lbl_803BD3AC
lbl_803BD3AC:
    .asciz "%s:%d: Error:oioi... id=%d\n"
    .balign 4
.global lbl_803BD3C8
lbl_803BD3C8:
    .asciz "%s:%d: oioi...\n"
    .balign 4
.global lbl_803BD3D8
lbl_803BD3D8:
	.incbin "baserom.dol", 0x3BA3D8, 0x1E70
.global lbl_803BF248
lbl_803BF248:
	.incbin "baserom.dol", 0x3BC248, 0x268
.global lbl_803BF4B0
lbl_803BF4B0:
    .asciz "%s:%d:not found lineID=%d\n"
    .balign 4
    .asciz "%s:%d: Error: mpGetSpeed() x=%f y=%f\n"
    .balign 4
    .asciz "!(ABS(speed->x)>10000.0F||ABS(speed->y)>10000.0F)"
    .balign 4
    .incbin "baserom.dol", 0x3BC528, 0x18
.global lbl_803BF540
lbl_803BF540:
	.incbin "baserom.dol", 0x3BC540, 0x1A0
.global lbl_803BF6E0
lbl_803BF6E0:
    .asciz "map coll under=%d upper=%d left=%d right=%d bbox=%d\n"
    .balign 4
    .incbin "baserom.dol", 0x3BC718, 0x48
.global lbl_803BF760
lbl_803BF760:
	.incbin "baserom.dol", 0x3BC760, 0x30
.global lbl_803BF790
lbl_803BF790:
    .asciz "mpisland.c"
    .balign 4
    .incbin "baserom.dol", 0x3BC79C, 0x4
.global lbl_803BF7A0
lbl_803BF7A0:
    .asciz "Duplicate Free %08X\n"
    .balign 4
.global lbl_803BF7B8
lbl_803BF7B8:
    .asciz "can't remove no force effect!\n"
    .balign 4
    .asciz "error no parent gobj!\n"
    .balign 4
    .asciz "Over Anime Call\n"
    .balign 4
.global lbl_803BF804
lbl_803BF804:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3BC810, 0xC
.global lbl_803BF81C
lbl_803BF81C:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3BC844, 0x4
.global lbl_803BF848
lbl_803BF848:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global jtbl_803BF870
jtbl_803BF870:
	.incbin "baserom.dol", 0x3BC870, 0x160
.global lbl_803BF9D0
lbl_803BF9D0:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global jtbl_803BF9F8
jtbl_803BF9F8:
	.incbin "baserom.dol", 0x3BC9F8, 0x108
.global lbl_803BFB00
lbl_803BFB00:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global jtbl_803BFB28
jtbl_803BFB28:
	.incbin "baserom.dol", 0x3BCB28, 0x4DC
.global lbl_803C0004
lbl_803C0004:
    .asciz "uigiDataTable"
    .balign 4
    .asciz "EfGnData.dat"
    .balign 4
    .asciz "effGanonDataTable"
    .balign 4
    .asciz "EfKbMs.dat"
    .balign 4
    .asciz "effKirbyMarsDataTable"
    .balign 4
    .asciz "EfKbZd.dat"
    .balign 4
    .asciz "effKirbyZeldaDataTable"
    .balign 4
    .asciz "EfMnData.dat"
    .balign 4
    .asciz "effMenuDataTable"
    .balign 4
    .asciz "EfKbMr.dat"
    .balign 4
    .asciz "effKirbyMarioDataTable"
    .balign 4
    .asciz "EfKbFx.dat"
    .balign 4
    .asciz "effKirbyFoxDataTable"
    .balign 4
    .asciz "EfKbSs.dat"
    .balign 4
    .asciz "effKirbySamusDataTable"
    .balign 4
    .asciz "EfKbPk.dat"
    .balign 4
    .asciz "effKirbyPikachuDataTable"
    .balign 4
    .asciz "EfKbLg.dat"
    .balign 4
    .asciz "effKirbyLuigiDataTable"
    .balign 4
    .asciz "EfKbCa.dat"
    .balign 4
    .asciz "effKirbyCaptainDataTable"
    .balign 4
    .asciz "EfKbDk.dat"
    .balign 4
    .asciz "effKirbyDonkeyDataTable"
    .balign 4
    .asciz "EfKbKp.dat"
    .balign 4
    .asciz "effKirbyKoopaDataTable"
    .balign 4
    .asciz "EfKbIc.dat"
    .balign 4
    .asciz "effKirbyIceDataTable"
    .balign 4
    .asciz "EfKbGn.dat"
    .balign 4
    .asciz "effKirbyGanonDataTable"
    .balign 4
    .asciz "EfKbFe.dat"
    .balign 4
    .asciz "effKirbyEmblemDataTable"
    .balign 4
    .asciz "EfFeData.dat"
    .balign 4
    .asciz "effEmblemDataTable"
    .balign 4
.global lbl_803C025C
lbl_803C025C:
	.incbin "baserom.dol", 0x3BD25C, 0x264
.global lbl_803C04C0
lbl_803C04C0:
    .asciz "[EfASync] unknown type %d\n"
    .balign 4
.global lbl_803C04DC
lbl_803C04DC:
    .asciz "efasync.c"
    .balign 4
.global jtbl_803C04E8
jtbl_803C04E8:
	.incbin "baserom.dol", 0x3BD4E8, 0x24
.global jtbl_803C050C
jtbl_803C050C:
	.incbin "baserom.dol", 0x3BD50C, 0x24
.global lbl_803C0530
lbl_803C0530:
    .asciz "PlCo.dat"
    .balign 4
.global lbl_803C053C
lbl_803C053C:
    .asciz "ftLoadCommonData"
    .balign 4
.global lbl_803C0550
lbl_803C0550:
    .asciz "translate"
    .balign 4
.global lbl_803C055C
lbl_803C055C:
    .asciz "fighter sub color num over!\n"
    .balign 4
.global lbl_803C057C
lbl_803C057C:
    .asciz "fighter.c"
    .balign 4
.global lbl_803C0588
lbl_803C0588:
    .asciz "ellegal flag fp->no_normal_motion\n"
    .balign 4
.global lbl_803C05AC
lbl_803C05AC:
    .asciz "fighter procUpdate pos error.\tpos.x=%f\tpos.y=%f\n"
    .balign 4
    .asciz "fighter procMap pos error.\tpos.x=%f\tpos.y=%f\n"
    .balign 4
.global lbl_803C0610
lbl_803C0610:
    .asciz "ellegal flag fp->no_reaction_always\n"
    .balign 4
.global lbl_803C0638
lbl_803C0638:
    .asciz "fighter joint depth num over!\n"
    .balign 4
.global lbl_803C0658
lbl_803C0658:
    .asciz "ftanim.c"
    .balign 4
.global lbl_803C0664
lbl_803C0664:
    .asciz "translate"
    .balign 4
.global lbl_803C0670
lbl_803C0670:
    .asciz "atree data error! player %d\n"
    .balign 4
    .asciz "fighter tobj num over!\n"
    .balign 4
    .asciz "can't find fighter texture anim!\n"
    .balign 4
.global lbl_803C06CC
lbl_803C06CC:
    .asciz "texture no exist! %d %d\n"
    .balign 4
.global lbl_803C06E8
lbl_803C06E8:
    .4byte 0x80071028
    .4byte 0x8007121C
    .4byte 0x8007162C
    .4byte 0x8007169C
    .4byte 0x80071708
    .4byte 0x80071784
    .4byte 0x800717D8
    .4byte 0x80071B50
    .4byte 0x80071CCC
    .4byte 0x80071820
    .4byte 0x800718A4
    .4byte 0x80071908
    .4byte 0x8007192C
    .4byte 0x80071950
    .4byte 0x80071974
    .4byte 0x80071998
    .4byte 0x80071A14
    .4byte 0x80071A58
    .4byte 0x80071A9C
    .4byte 0x80071AE8
    .4byte 0x80071B28
    .4byte 0x80071D40
    .4byte 0x80071D94
    .4byte 0x80071DCC
    .4byte 0x80071E04
    .4byte 0x80071F34
    .4byte 0x80071F78
    .4byte 0x80071FA0
    .4byte 0x80071FC8
    .4byte 0x80072320
    .4byte 0x800726F4
    .4byte 0x800727C8
    .4byte 0x80072894
    .4byte 0x800728F8
    .4byte 0x8007297C
    .4byte 0x800729D4
    .4byte 0x80072A5C
    .4byte 0x80072ABC
    .4byte 0x80072B14
    .4byte 0x80072B3C
    .4byte 0x80072B94
    .4byte 0x80072BF4
    .4byte 0x80072C6C
    .4byte 0x80072CB0
    .4byte 0x80072CD8
    .4byte 0x80072E4C
    .4byte 0x80073008
    .4byte 0x800730B8
    .4byte 0x80073118

.global lbl_803C07AC
lbl_803C07AC:
    .4byte 0x800711DC
    .4byte 0x800715EC
    .4byte 0x8007168C
    .4byte 0x800716F8
    .4byte 0x80071774
    .4byte 0x800717C8
    .4byte 0x80071810
    .4byte 0x80071CA4
    .4byte 0x80071D30
    .4byte 0x80071820
    .4byte 0x800718A4
    .4byte 0x80071908
    .4byte 0x8007192C
    .4byte 0x80071950
    .4byte 0x80071974
    .4byte 0x80071998
    .4byte 0x80071A14
    .4byte 0x80071A58
    .4byte 0x80071A9C
    .4byte 0x80071AE8
    .4byte 0x80071B28
    .4byte 0x80071D40
    .4byte 0x80071D94
    .4byte 0x80071DCC
    .4byte 0x80071F0C
    .4byte 0x80071F34
    .4byte 0x80071F78
    .4byte 0x80071FA0
    .4byte 0x800722C8
    .4byte 0x800726C0
    .4byte 0x800726F4
    .4byte 0x8007283C
    .4byte 0x80072894
    .4byte 0x8007296C
    .4byte 0x800729C4
    .4byte 0x80072A4C
    .4byte 0x80072AAC
    .4byte 0x80072B04
    .4byte 0x80072B14
    .4byte 0x80072B84
    .4byte 0x80072BE4
    .4byte 0x80072C5C
    .4byte 0x80072C6C
    .4byte 0x80072CB0
    .4byte 0x80072E24
    .4byte 0x80072FE0
    .4byte 0x8007309C
    .4byte 0x80073108
    .4byte 0x8007320C

.global lbl_803C0870
lbl_803C0870:
	.incbin "baserom.dol", 0x3BD870, 0x34
.global jtbl_803C08A4
jtbl_803C08A4:
	.incbin "baserom.dol", 0x3BD8A4, 0x1C
.global jtbl_803C08C0
jtbl_803C08C0:
	.incbin "baserom.dol", 0x3BD8C0, 0x1C
.global jtbl_803C08DC
jtbl_803C08DC:
	.incbin "baserom.dol", 0x3BD8DC, 0x1C
.global lbl_803C08F8
lbl_803C08F8:
	.incbin "baserom.dol", 0x3BD8F8, 0x50
.global lbl_803C0948
lbl_803C0948:
	.incbin "baserom.dol", 0x3BD948, 0x50
.global lbl_803C0998
lbl_803C0998:
	.incbin "baserom.dol", 0x3BD998, 0x70
.global lbl_803C0A08
lbl_803C0A08:
    .asciz "ftparts.c"
    .balign 4
    .asciz "envelope"
    .balign 4
    .asciz "envelope->jobj"
    .balign 4
    .asciz "jp->envelopemtx"
    .balign 4
    .asciz "fighter parts model dobj num over! player %d\n"
    .balign 4
    .asciz "fighter dobj num over! player %d\n"
    .balign 4
    .asciz "fighter parts num over! player %d\n"
    .balign 4
.global lbl_803C0AB8
lbl_803C0AB8:
    .asciz "fighter parts num not match! player %d\n"
    .balign 4
.global lbl_803C0AE0
lbl_803C0AE0:
    .asciz "fighter parts model num over!\n"
    .balign 4
.global lbl_803C0B00
lbl_803C0B00:
    .asciz "can't find tobj!\n"
    .balign 4
.global lbl_803C0B14
lbl_803C0B14:
    .asciz "fighter parts model dobj num over!\n"
    .balign 4
    .asciz "cant set fighter rot x!\n"
    .balign 4
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .asciz "cant set fighter rot y!\n"
    .balign 4
    .asciz "cant set fighter rot z!\n"
    .balign 4
.global lbl_803C0BB4
lbl_803C0BB4:
    .asciz "cant get fighter rot x!\n"
    .balign 4
.global lbl_803C0BD0
lbl_803C0BD0:
    .asciz "cant get fighter rot y!\n"
    .balign 4
    .asciz "cant get fighter rot z!\n"
    .balign 4
.global lbl_803C0C08
lbl_803C0C08:
    .asciz "ftcamera.c"
    .balign 4
.global lbl_803C0C14
lbl_803C0C14:
    .asciz "stGetPlyDeadUp() - center_pos.y != 0.0F"
    .balign 4
    .incbin "baserom.dol", 0x3BDC3C, 0x4
.global lbl_803C0C40
lbl_803C0C40:
	.incbin "baserom.dol", 0x3BDC40, 0xC
.global lbl_803C0C4C
lbl_803C0C4C:
	.incbin "baserom.dol", 0x3BDC4C, 0xC
.global lbl_803C0C58
lbl_803C0C58:
    .asciz "attack power over 500!! %f\n"
    .balign 4
.global lbl_803C0C74
lbl_803C0C74:
    .asciz "ftcoll.c"
    .balign 4
.global lbl_803C0C80
lbl_803C0C80:
    .asciz "damage log over %d!!\n"
    .balign 4
    .asciz "tip log over %d!!\n"
    .balign 4
.global lbl_803C0CAC
lbl_803C0CAC:
	.incbin "baserom.dol", 0x3BDCAC, 0x44
.global lbl_803C0CF0
lbl_803C0CF0:
    .asciz "in ftCollisionSetHitStatus illegal parts!\n"
    .balign 4
    .asciz "fighter hit num over!\n"
    .balign 4
    .asciz "fighter dynamics hit num over!\n"
    .balign 4
    .incbin "baserom.dol", 0x3BDD54, 0x4
.global lbl_803C0D58
lbl_803C0D58:
    .asciz "ftcommon.c"
    .balign 4
.global lbl_803C0D64
lbl_803C0D64:
    .asciz "fp->kind == Ft_Kind_Sandbag"
    .balign 4
.global lbl_803C0D80
lbl_803C0D80:
    .asciz "fighter ground no under Id! %d %d\n"
    .balign 4
.global lbl_803C0DA4
lbl_803C0DA4:
    .asciz "translate"
    .balign 4
.global lbl_803C0DB0
lbl_803C0DB0:
    .asciz "fp->ground_or_air == GA_Ground"
    .balign 4
.global lbl_803C0DD0
lbl_803C0DD0:
    .asciz "fighter accessory already exsist!\n"
    .balign 4
    .incbin "baserom.dol", 0x3BDDF4, 0x9C
.global jtbl_803C0E90
jtbl_803C0E90:
	.incbin "baserom.dol", 0x3BDE90, 0x20
.global lbl_803C0EB0
lbl_803C0EB0:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3BDEBC, 0x4
.global lbl_803C0EC0
lbl_803C0EC0:
	.incbin "baserom.dol", 0x3BDEC0, 0x108
.global lbl_803C0FC8
lbl_803C0FC8:
	.incbin "baserom.dol", 0x3BDFC8, 0x108
.global lbl_803C10D0
lbl_803C10D0:
	.incbin "baserom.dol", 0x3BE0D0, 0x84

    .balign 4
.global lbl_803C1154
lbl_803C1154:
    .4byte func_800E0960
    .4byte func_800E57AC
    .4byte func_800E2AEC
    .4byte func_8010D9AC
    .4byte func_800EE680
    .4byte func_80132ABC
    .4byte func_800EAE44
    .4byte func_801100EC
    .4byte func_8011480C
    .4byte FighterOnLoad_Peach
    .4byte func_8011EF3C
    .4byte func_80122EDC
    .4byte func_801243E4
    .4byte func_8012837C
    .4byte func_8012B99C
    .4byte func_8013C67C
    .4byte func_80144E48
    .4byte func_80142324
    .4byte func_801364AC
    .4byte func_80139334
    .4byte func_80148CE4
    .4byte func_801494E4
    .4byte func_80149CC4
    .4byte func_80149E34
    .4byte func_8014A37C
    .4byte func_8014EE1C
    .4byte func_8014F124
    .4byte func_8014FC6C
    .4byte func_80155E1C
    .4byte func_8014F3DC
    .4byte func_8014F440
    .4byte func_8014F6B8
    .4byte func_8014F9D0

    .balign 4
.global lbl_803C11D8
lbl_803C11D8:
    .4byte 0x800E08CC
    .4byte 0x800E5554
    .4byte 0x800E2888
    .4byte 0x8010D740
    .4byte 0x800EE5C0
    .4byte 0x80132A0C
    .4byte 0x800EAD84
    .4byte 0x80110094
    .4byte 0x801147C0
    .4byte 0x8011B51C
    .4byte 0x8011EFE8
    .4byte 0x80122F28
    .4byte 0x80124474
    .4byte 0x8012832C
    .4byte 0x8012B960
    .4byte 0x8013C318
    .4byte 0x80144DFC
    .4byte 0x801422E8
    .4byte 0x80136258
    .4byte 0x801392DC
    .4byte 0x80148C64
    .4byte 0x8014949C
    .4byte 0x80149ACC
    .4byte 0x80149EAC
    .4byte 0x8014A250
    .4byte 0x8014EBFC
    .4byte 0x8014EEF8
    .4byte 0x8014FC68
    .4byte 0x80155E18
    .4byte 0x8014F1F0
    .4byte 0x8014F418
    .4byte 0x8014F640
    .4byte 0x8014F9CC

    .balign 4
.global lbl_803C125C
lbl_803C125C:
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8013C340
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL

    .balign 4
.global lbl_803C12E0
lbl_803C12E0:
    .4byte 0x803C7120
    .4byte 0x803C7788
    .4byte 0x803C72B8
    .4byte 0x803CB838
    .4byte 0x803C8368
    .4byte 0x803CEDC0
    .4byte 0x803C7E18
    .4byte 0x803CC060
    .4byte 0x803CC650
    .4byte 0x803CCCB8
    .4byte 0x803CD2D0
    .4byte 0x803CD838
    .4byte 0x803CDD78
    .4byte 0x803CE2D0
    .4byte 0x803CE6D0
    .4byte 0x803CFEF0
    .4byte 0x803D0B00
    .4byte 0x803D0628
    .4byte 0x803CF420
    .4byte 0x803CFA58
    .4byte 0x803D0FA0
    .4byte 0x803D1498
    .4byte 0x803D1848
    .4byte 0x803D1EA8
    .4byte 0x803D23E8
    .4byte 0x803D29F8
    .4byte 0x803D2E80
    .4byte 0x803D3A30
    .4byte 0x803D41F8
	.4byte NULL
	.4byte NULL
    .4byte 0x803D35E8
    .4byte 0x803D3998

    .balign 4
.global lbl_803C1364
lbl_803C1364:
    .4byte 0x803C7260
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x803CA04C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x803D0868
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x803D38C8
    .4byte NULL

    .balign 4
.global lbl_803C13E8
lbl_803C13E8:
    .4byte 0x800E1450
    .4byte 0x800E9EE8
    .4byte 0x800E32B0
    .4byte 0x8010E1C4
    .4byte 0x800F5564
    .4byte 0x80132EFC
    .4byte 0x800EC354
    .4byte 0x80111038
    .4byte 0x80116C94
    .4byte 0x8011C34C
    .4byte 0x8011F99C
    .4byte NULL
    .4byte 0x80124E38
    .4byte 0x8012A1D8
    .4byte 0x8012F4B4
    .4byte 0x8013D234
    .4byte 0x801466C4
    .4byte 0x80142B14
    .4byte 0x8013741C
    .4byte 0x8013B638
    .4byte 0x800EC354
    .4byte 0x800E1450
    .4byte 0x800E9EE8
    .4byte 0x80124E38
    .4byte 0x8014C7A0
    .4byte 0x800E32B0
    .4byte 0x8013741C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80132EFC
    .4byte NULL

    .balign 4
.global lbl_803C146C
lbl_803C146C:
    .4byte 0x800E1AB0
    .4byte 0x800E72C4
    .4byte 0x800E4CF4
    .4byte 0x8010FBFC
    .4byte 0x800F23B8
    .4byte 0x80135B04
    .4byte 0x800EBB80
    .4byte 0x8011312C
    .4byte 0x80118250
    .4byte 0x8011D7F0
    .4byte 0x8012122C
    .4byte NULL
    .4byte 0x80125E60
    .4byte 0x8012A738
    .4byte 0x8012E33C
    .4byte 0x8013CA98
    .4byte 0x80145258
    .4byte 0x80144024
    .4byte 0x8013826C
    .4byte 0x801398E8
    .4byte 0x800EBB80
    .4byte 0x800E1AB0
    .4byte 0x800E72C4
    .4byte 0x80125E60
    .4byte 0x8014E158
    .4byte 0x800E4CF4
    .4byte 0x8013826C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80135B04
    .4byte NULL

    .balign 4
.global lbl_803C14F0
lbl_803C14F0:
    .4byte 0x800E2194
    .4byte 0x800E85EC
    .4byte 0x800E40D8
    .4byte NULL
    .4byte 0x800F3E68
    .4byte 0x801346A4
    .4byte 0x800EB6DC
    .4byte 0x80114224
    .4byte 0x80119E90
    .4byte 0x8011D1C4
    .4byte 0x80122988
    .4byte 0x80122988
    .4byte 0x80127924
    .4byte 0x8012B09C
    .4byte 0x8012E78C
    .4byte 0x8013CF2C
    .4byte 0x80146264
    .4byte 0x80144708
    .4byte 0x80138A30
    .4byte 0x8013AFA4
    .4byte 0x800EB6DC
    .4byte 0x800E2194
    .4byte 0x800E85EC
    .4byte 0x80127924
    .4byte 0x8014CF78
    .4byte 0x800E40D8
    .4byte 0x80138A30
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x801346A4
    .4byte NULL

    .balign 4
.global lbl_803C1574
lbl_803C1574:
    .4byte 0x800E14C8
    .4byte 0x800E9F6C
    .4byte 0x800E33E0
    .4byte 0x8010E234
    .4byte 0x800F55D0
    .4byte 0x80132F94
    .4byte 0x800EC404
    .4byte 0x8011108C
    .4byte 0x80116D04
    .4byte 0x8011C3C4
    .4byte 0x8011FB08
    .4byte NULL
    .4byte 0x80124EAC
    .4byte 0x8012A2AC
    .4byte 0x8012F588
    .4byte 0x8013D2A0
    .4byte 0x8014677C
    .4byte 0x80142B88
    .4byte 0x801374A0
    .4byte 0x8013B6D8
    .4byte 0x800EC404
    .4byte 0x800E14C8
    .4byte 0x800E9F6C
    .4byte 0x80124EAC
    .4byte 0x8014C828
    .4byte 0x800E33E0
    .4byte 0x801374A0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80132F94
    .4byte NULL

    .balign 4
.global lbl_803C15F8
lbl_803C15F8:
    .4byte 0x800E1040
    .4byte 0x800E61A8
    .4byte 0x800E2C00
    .4byte 0x8010E69C
    .4byte 0x800F1680
    .4byte 0x80134ED0
    .4byte 0x800ECF78
    .4byte 0x80112198
    .4byte 0x80117034
    .4byte 0x8011E45C
    .4byte 0x8011F26C
    .4byte 0x8011F26C
    .4byte 0x8012489C
    .4byte 0x801295F0
    .4byte 0x8012CE64
    .4byte 0x8013DF60
    .4byte 0x801473F4
    .4byte 0x801426EC
    .4byte 0x801367B8
    .4byte 0x8013A9A4
    .4byte 0x800ECF78
    .4byte 0x800E1040
    .4byte 0x800E61A8
    .4byte 0x8012489C
    .4byte 0x8014E6C0
    .4byte 0x800E2C00
    .4byte 0x801367B8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80134ED0
    .4byte NULL

    .balign 4
.global lbl_803C167C
lbl_803C167C:
    .4byte 0x800E0DA8
    .4byte 0x800E608C
    .4byte 0x800E2B80
    .4byte 0x8010E574
    .4byte 0x800F1630
    .4byte 0x80134E58
    .4byte 0x800ECDAC
    .4byte 0x801120E8
    .4byte 0x80116F94
    .4byte 0x8011E3D0
    .4byte 0x8011F1F8
    .4byte 0x8011F1F8
    .4byte 0x80124830
    .4byte 0x8012954C
    .4byte 0x8012CDE8
    .4byte 0x8013DEA8
    .4byte 0x80147320
    .4byte 0x8014267C
    .4byte 0x80136744
    .4byte 0x8013A928
    .4byte 0x800ECDAC
    .4byte 0x800E0DA8
    .4byte 0x800E608C
    .4byte 0x80124830
    .4byte 0x8014E644
    .4byte 0x800E2B80
    .4byte 0x80136744
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80134E58
    .4byte NULL

    .balign 4
.global lbl_803C1700
lbl_803C1700:
    .4byte 0x800E207C
    .4byte 0x800E8560
    .4byte 0x800E4040
    .4byte 0x8010DC80
    .4byte 0x800F3D50
    .4byte 0x8013460C
    .4byte 0x800EB65C
    .4byte 0x80114160
    .4byte 0x80119E14
    .4byte 0x8011D11C
    .4byte 0x80122904
    .4byte 0x80122904
    .4byte 0x801278BC
    .4byte 0x8012AF5C
    .4byte 0x8012E6F8
    .4byte 0x8013CE8C
    .4byte 0x801461F0
    .4byte 0x801445F0
    .4byte 0x801389CC
    .4byte 0x8013AEE0
    .4byte 0x800EB65C
    .4byte 0x800E207C
    .4byte 0x800E8560
    .4byte 0x801278BC
    .4byte 0x8014CEF0
    .4byte 0x800E4040
    .4byte 0x801389CC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8013460C
    .4byte NULL

    .balign 4
.global lbl_803C1784
lbl_803C1784:
    .4byte 0x800E1A54
    .4byte 0x800E7238
    .4byte 0x800E4A78
    .4byte 0x8010FB1C
    .4byte 0x800F2300
    .4byte 0x80135A2C
    .4byte 0x800EBB1C
    .4byte 0x801130D0
    .4byte 0x80118120
    .4byte 0x8011D72C
    .4byte 0x801211B4
    .4byte NULL
    .4byte 0x80125DE8
    .4byte 0x8012A674
    .4byte 0x8012E2C4
    .4byte 0x8013C9C8
    .4byte 0x801451DC
    .4byte 0x80143FC8
    .4byte 0x80138208
    .4byte 0x80139834
    .4byte 0x800EBB1C
    .4byte 0x800E1A54
    .4byte 0x800E7238
    .4byte 0x80125DE8
    .4byte 0x8014E0AC
    .4byte 0x800E4A78
    .4byte 0x80138208
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80135A2C
    .4byte NULL

    .balign 4
.global lbl_803C1808
lbl_803C1808:
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8011493C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8014A828
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL

.global lbl_803C188C
lbl_803C188C:
    .4byte 0x800E0A20
    .4byte 0x800E55A8
    .4byte 0x800E28E8
    .4byte 0x8010D7A8
    .4byte 0x800EE914
    .4byte 0x80132B3C
    .4byte 0x800EAFA4
    .4byte 0x80110204
    .4byte 0x80114968
    .4byte 0x8011B740
    .4byte 0x8011ED38
    .4byte 0x8011ED38
    .4byte 0x801244B8
    .4byte 0x80128464
    .4byte 0x8012BACC
    .4byte 0x8013C6EC
    .4byte 0x80144EE0
    .4byte 0x80142388
    .4byte 0x801362B0
    .4byte 0x801393CC
    .4byte 0x80148DC0
    .4byte 0x80149560
    .4byte 0x80149B00
    .4byte 0x80149FE4
    .4byte 0x8014A5B8
    .4byte 0x8014EC58
    .4byte 0x8014EF60
    .4byte NULL
    .4byte NULL
    .4byte 0x8014F218
    .4byte 0x8014F460
    .4byte 0x8014F720
    .4byte NULL

.global lbl_803C1910
lbl_803C1910:
    .4byte 0x800E0B00
    .4byte 0x800E5688
    .4byte 0x800E29C8
    .4byte 0x8010D888
    .4byte 0x800EE9DC
    .4byte 0x80132C1C
    .4byte 0x800EB018
    .4byte 0x801102E4
    .4byte 0x80114A48
    .4byte 0x8011B820
    .4byte 0x8011EE18
    .4byte 0x8011EE18
    .4byte 0x80124598
    .4byte 0x80128544
    .4byte 0x8012BBAC
    .4byte 0x8013C798
    .4byte 0x80144F50
    .4byte 0x80142468
    .4byte 0x80136390
    .4byte 0x801394AC
    .4byte 0x80148E34
    .4byte 0x80149640
    .4byte 0x80149BE0
    .4byte 0x8014A0C4
    .4byte 0x8014A698
    .4byte 0x8014ED38
    .4byte 0x8014F040
    .4byte NULL
    .4byte NULL
    .4byte 0x8014F2F8
    .4byte 0x8014F540
    .4byte 0x8014F800
    .4byte NULL

.global lbl_803C1994
lbl_803C1994:
    .4byte 0x800E0B48
    .4byte 0x800E56D0
    .4byte 0x800E2A10
    .4byte 0x8010D8D0
    .4byte 0x800EEA24
    .4byte 0x80132C64
    .4byte 0x800EB060
    .4byte 0x8011032C
    .4byte 0x80114A90
    .4byte 0x8011B868
    .4byte 0x8011EE60
    .4byte 0x8011EE60
    .4byte 0x801245E0
    .4byte 0x8012858C
    .4byte 0x8012BBF4
    .4byte 0x8013C7E8
    .4byte 0x80144F54
    .4byte 0x801424B0
    .4byte 0x801363D8
    .4byte 0x801394F4
    .4byte 0x80148E7C
    .4byte 0x80149688
    .4byte 0x80149C28
    .4byte 0x8014A10C
    .4byte 0x8014A6E0
    .4byte 0x8014ED80
    .4byte 0x8014F088
    .4byte NULL
    .4byte NULL
    .4byte 0x8014F340
    .4byte 0x8014F588
    .4byte 0x8014F848
    .4byte NULL

.global lbl_803C1A18
lbl_803C1A18:
    .4byte 0x800E0B90
    .4byte 0x800E5718
    .4byte 0x800E2A58
    .4byte 0x8010D918
    .4byte 0x800EEA6C
    .4byte 0x80132CAC
    .4byte 0x800EB0A8
    .4byte 0x80110374
    .4byte 0x80114AD8
    .4byte 0x8011B8B0
    .4byte 0x8011EEA8
    .4byte 0x8011EEA8
    .4byte 0x80124628
    .4byte 0x801285D4
    .4byte 0x8012BC3C
    .4byte 0x8013C838
    .4byte 0x80144F4C
    .4byte 0x801424F8
    .4byte 0x80136420
    .4byte 0x8013953C
    .4byte 0x80148EC4
    .4byte 0x801496D0
    .4byte 0x80149C70
    .4byte 0x8014A154
    .4byte 0x8014A728
    .4byte 0x8014EDC8
    .4byte 0x8014F0D0
    .4byte NULL
    .4byte NULL
    .4byte 0x8014F388
    .4byte 0x8014F5D0
    .4byte 0x8014F890
    .4byte NULL

.global lbl_803C1A9C
lbl_803C1A9C:
    .4byte 0x800E0A20
    .4byte 0x800E55A8
    .4byte 0x800E28E8
    .4byte 0x8010D7A8
    .4byte 0x800EE914
    .4byte 0x80132B3C
    .4byte 0x800EB11C
    .4byte 0x80110204
    .4byte 0x80114968
    .4byte 0x8011B740
    .4byte 0x8011ED38
    .4byte 0x8011ED38
    .4byte 0x801244B8
    .4byte 0x80128464
    .4byte 0x8012BACC
    .4byte 0x8013C6EC
    .4byte 0x80144EE0
    .4byte 0x80142388
    .4byte 0x801362B0
    .4byte 0x801393CC
    .4byte 0x80148F38
    .4byte 0x80149560
    .4byte 0x80149B00
    .4byte 0x80149FE4
    .4byte 0x8014A5B8
    .4byte 0x8014EC58
    .4byte 0x8014EF60
    .4byte NULL
    .4byte NULL
    .4byte 0x8014F218
    .4byte 0x8014F460
    .4byte 0x8014F720
    .4byte NULL

.global lbl_803C1B20
lbl_803C1B20:
    .4byte 0x800E0B90
    .4byte 0x800E5718
    .4byte 0x800E2A58
    .4byte 0x8010D918
    .4byte 0x800EEA6C
    .4byte 0x80132CAC
    .4byte 0x800EB1FC
    .4byte 0x80110374
    .4byte 0x80114AD8
    .4byte 0x8011B8B0
    .4byte 0x8011EEA8
    .4byte 0x8011EEA8
    .4byte 0x80124628
    .4byte 0x801285D4
    .4byte 0x8012BC3C
    .4byte 0x8013C838
    .4byte 0x80144F4C
    .4byte 0x801424F8
    .4byte 0x80136420
    .4byte 0x8013953C
    .4byte 0x80149018
    .4byte 0x801496D0
    .4byte 0x80149C70
    .4byte 0x8014A154
    .4byte 0x8014A728
    .4byte 0x8014EDC8
    .4byte 0x8014F0D0
    .4byte NULL
    .4byte NULL
    .4byte 0x8014F388
    .4byte 0x8014F5D0
    .4byte 0x8014F890
    .4byte NULL

.global lbl_803C1BA4
lbl_803C1BA4:
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8012467C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL

.global lbl_803C1C28
lbl_803C1C28:
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x801246C0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL

.global lbl_803C1CAC
lbl_803C1CAC:
    .4byte 0x800E0C24
    .4byte 0x800E5898
    .4byte NULL
    .4byte 0x8010DAB4
    .4byte 0x800EEB38
    .4byte 0x80132D38
    .4byte 0x800EB2AC
    .4byte 0x80110408
    .4byte 0x80114B6C
    .4byte 0x8011B998
    .4byte 0x8011F0E4
    .4byte 0x8011F0E4
    .4byte 0x801247A8
    .4byte NULL
    .4byte 0x8012BCC8
    .4byte 0x8013C8C4
    .4byte 0x80145018
    .4byte 0x80142584
    .4byte 0x80136520
    .4byte 0x80139624
    .4byte 0x8014908C
    .4byte 0x80149744
    .4byte 0x80149D5C
    .4byte 0x8014A1C8
    .4byte NULL
    .4byte 0x8014EE60
    .4byte 0x8014F168
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8014F904
    .4byte 0x8014FB9C

.global lbl_803C1D30
lbl_803C1D30:
    .4byte 0x800E0C68
    .4byte 0x800E5904
    .4byte NULL
    .4byte 0x8010DAF8
    .4byte 0x800EEB7C
    .4byte 0x80132D7C
    .4byte 0x800EB2F0
    .4byte 0x8011044C
    .4byte 0x80114BB0
    .4byte 0x8011B9DC
    .4byte 0x8011F128
    .4byte 0x8011F128
    .4byte 0x801247EC
    .4byte NULL
    .4byte 0x8012BD34
    .4byte 0x8013C908
    .4byte 0x8014505C
    .4byte 0x801425C8
    .4byte 0x80136564
    .4byte 0x80139668
    .4byte 0x801490D0
    .4byte 0x80149788
    .4byte 0x80149DC8
    .4byte 0x8014A20C
    .4byte NULL
    .4byte 0x8014EEAC
    .4byte 0x8014F1AC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8014F948
    .4byte 0x8014FBA0

.global lbl_803C1DB4
lbl_803C1DB4:
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x800F1B6C
    .4byte 0x80132A64
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8014F698
    .4byte NULL

.global lbl_803C1E38
lbl_803C1E38:
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8010D96C
    .4byte 0x800EE818
    .4byte NULL
    .4byte NULL
    .4byte 0x801101CC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80128628
    .4byte NULL
    .4byte NULL
    .4byte 0x80144F58
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8014A77C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL

.global lbl_803C1EBC
lbl_803C1EBC:
    .4byte 0x800E0BE4
    .4byte 0x800E5858
    .4byte 0x800E2B40
    .4byte 0x8010DA74
    .4byte 0x800EEAC0
    .4byte 0x80132D00
    .4byte 0x800EB250
    .4byte 0x801103C8
    .4byte 0x80114B2C
    .4byte 0x8011B904
    .4byte 0x8011F0A4
    .4byte 0x80122FCC
    .4byte 0x80124704
    .4byte 0x80128684
    .4byte 0x8012BC90
    .4byte 0x8013C88C
    .4byte 0x80144FB4
    .4byte 0x8014254C
    .4byte 0x801364E8
    .4byte 0x80139590
    .4byte 0x8014906C
    .4byte 0x80149724
    .4byte 0x80149D3C
    .4byte 0x8014A1A8
    .4byte 0x8014A7B4
    .4byte 0x8014EE40
    .4byte 0x8014F148
    .4byte 0x8014FDD0
    .4byte 0x80155F8C
    .4byte 0x8014F3FC
    .4byte 0x8014F624
    .4byte 0x8014F8E4
    .4byte 0x8014FB78

.global lbl_803C1F40
lbl_803C1F40:
    .4byte 0x803C57D0
    .4byte 0x803C57DC
    .4byte 0x803C7BE8
    .4byte 0x803C7BF4
    .4byte 0x803C7598
    .4byte 0x803C75A4
    .4byte 0x803CBDF8
    .4byte 0x803CBE04
    .4byte 0x803CA308
    .4byte 0x803CA314
    .4byte 0x803CF0A0
    .4byte 0x803CF0AC
    .4byte 0x803C80B8
    .4byte 0x803C80C4
    .4byte 0x803CC360
    .4byte 0x803CC36C
    .4byte 0x803CCAD0
    .4byte 0x803CCADC
    .4byte 0x803CD078
    .4byte 0x803CD084
    .4byte 0x803CD610
    .4byte 0x803CD61C
    .4byte 0x803CDB78
    .4byte 0x803CDB84
    .4byte 0x803CE0B8
    .4byte 0x803CE0C4
    .4byte 0x803CE510
    .4byte 0x803CE51C
    .4byte 0x803CEA98
    .4byte 0x803CEAA4
    .4byte 0x803D02F0
    .4byte 0x803D02FC
    .4byte 0x803D0D80

    # TODO: What is this table?
    .4byte 0x803D0D8C
    .4byte 0x803D08A8
    .4byte 0x803D08B4
    .4byte 0x803CF820
    .4byte 0x803CF82C
    .4byte 0x803CFC98
    .4byte 0x803CFCA4
    .4byte 0x803D1240
    .4byte 0x803D124C
    .4byte 0x803D15D8
    .4byte 0x803D15E4
    .4byte 0x803D1CA8
    .4byte 0x803D1CB4
    .4byte 0x803D21E8
    .4byte 0x803D21F4
    .4byte 0x803D28E8
    .4byte 0x803D28F4
    .4byte 0x803D2CD8
    .4byte 0x803D2CE4
    .4byte 0x803D3280
    .4byte 0x803D328C
    .4byte 0x803D4070
    .4byte 0x803D407C
    .4byte 0x803D4818
    .4byte 0x803D4824
    .4byte 0x803D34E8
    .4byte 0x803D34F4
    .4byte 0x803D3568
    .4byte 0x803D3574
    .4byte 0x803D38E8
    .4byte 0x803D38F4
    .4byte 0x803D39B8
    .4byte 0x803D39C4

.global lbl_803C2048
lbl_803C2048:
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x800EEE9C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL

.global lbl_803C20CC
lbl_803C20CC:
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x800EEF04
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8013C4F0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL

.global lbl_803C2150
lbl_803C2150:
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x800EF87C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8013C614
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL

    # TODO: What is this table?
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x800EF028
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8013C664
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL

.global lbl_803C2258
lbl_803C2258:
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x800EF9BC
    .4byte 0x800EF9FC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL

    # TODO: What is this table?
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL

.global lbl_803C2360
lbl_803C2360:
    .4byte 0x803C5A28
    .4byte 0x803C7D9C
    .4byte 0x803C773C
    .4byte 0x803CC020
    .4byte 0x803CA5B4
    .4byte 0x803CF26C
    .4byte 0x803C82B0
    .4byte 0x803CC558
    .4byte 0x803CCC84
    .4byte 0x803CD290
    .4byte 0x803CD7C4
    .4byte 0x803CDD2C
    .4byte 0x803CE2A0
    .4byte 0x803CE678
    .4byte 0x803CECFC
    .4byte 0x803D0508
    .4byte 0x803D0F5C
    .4byte 0x803D0AB4
    .4byte 0x803CFA18
    .4byte 0x803CFEB0
    .4byte 0x803D1458
    .4byte 0x803D180C
    .4byte 0x803D1E74
    .4byte 0x803D23B4
    .4byte 0x803D29C8
    .4byte 0x803D2E40
    .4byte 0x803D34A8
    .4byte 0x803D40C4
    .4byte 0x803D4868
    .4byte 0x803D3558
    .4byte 0x803D35D8
    .4byte 0x803D3988
    .4byte 0x803D3A24

    # TODO: What is this table?
    .4byte 0x803C595C
    .4byte 0x803C7D10
    .4byte 0x803C76A0
    .4byte 0x803CBF88
    .4byte 0x803CA4E0
    .4byte 0x803CF1E0
    .4byte 0x803C8224
    .4byte 0x803CC4CC
    .4byte 0x803CCBF8
    .4byte 0x803CD204
    .4byte 0x803CD738
    .4byte 0x803CDCA0
    .4byte 0x803CE204
    .4byte 0x803CE5EC
    .4byte 0x803CEC70
    .4byte 0x803D047C
    .4byte 0x803D0EC4
    .4byte 0x803D09E8
    .4byte 0x803CF98C
    .4byte 0x803CFE24
    .4byte 0x803D13CC
    .4byte 0x803D1770
    .4byte 0x803D1DE8
    .4byte 0x803D2328
    .4byte 0x803D292C
    .4byte 0x803D2DB4
    .4byte 0x803D3410
    .4byte 0x803D40B8
    .4byte 0x803D485C
    .4byte 0x803D3520
    .4byte 0x803D35A0
    .4byte 0x803D3948
    .4byte 0x803D3A18

.global lbl_803C2468
lbl_803C2468:
    .4byte 0x803C59D8
    .4byte 0x803C7D8C
    .4byte 0x803C772C
    .4byte 0x803CC010
    .4byte 0x803CA55C
    .4byte 0x803CF25C
    .4byte 0x803C82A0
    .4byte 0x803CC548
    .4byte 0x803CCC74
    .4byte 0x803CD280
    .4byte 0x803CD7B4
    .4byte 0x803CDD1C
    .4byte 0x803CE290
    .4byte 0x803CE668
    .4byte 0x803CECEC
    .4byte 0x803D04F8
    .4byte 0x803D0F4C
    .4byte 0x803D0A64
    .4byte 0x803CFA08
    .4byte 0x803CFEA0
    .4byte 0x803D1448
    .4byte 0x803D17FC
    .4byte 0x803D1E64
    .4byte 0x803D23A4
    .4byte 0x803D29B8
    .4byte 0x803D2E30
    .4byte 0x803D3498
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x803D3954
    .4byte NULL

.global lbl_803C24EC
lbl_803C24EC:
    .4byte 0x800E0CE0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x800EEBF8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80142640
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8014F9A4
    .4byte NULL

.global lbl_803C2570
lbl_803C2570:
    .4byte 0x800E0CAC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x800EEBC0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8014260C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8014F98C
    .4byte NULL

.global lbl_803C25F4
lbl_803C25F4:
	.incbin "baserom.dol", 0x3BF5F4, 0x108
.global lbl_803C26FC
lbl_803C26FC:
	.incbin "baserom.dol", 0x3BF6FC, 0x24
.global lbl_803C2720
lbl_803C2720:
    .asciz "fighter reference counter error!\n"
    .balign 4
.global lbl_803C2744
lbl_803C2744:
    .asciz "ftdata.c"
    .balign 4
    .asciz "cant get corps model array!\n"
    .balign 4
    .asciz "HSD_ArchiveParse error!\n"
    .balign 4
    .asciz "fighter figatree over! %x\n"
    .balign 4
    .asciz "Demo Status error! %d\n"
    .balign 4
    .asciz "lbArchiveRelocate error! %x\n"
    .balign 4
    .asciz "HSD_ArchiveParse error! %x\n"
    .balign 4
    .incbin "baserom.dol", 0x3BF7FC, 0x4

    .balign 4
.global lbl_803C2800
lbl_803C2800:
    # Entry 0
    # ID
    .4byte -1

    # Flags
    .4byte 0x00D00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D3E00
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x800D3E3C

    # Entry 1
    # ID
    .4byte -1

    # Flags
    .4byte 0x00D00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D3910
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x800D394C

    # Entry 2
    # ID
    .4byte -1

    # Flags
    .4byte 0x00D00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D3B88
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x800D3BC4

    # Entry 3
    # ID
    .4byte -1

    # Flags
    .4byte 0x00D00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D4078
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x800D40B4

    # Entry 4
    # ID
    .4byte 29

    # Flags
    .4byte 0x00D00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D42E4
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x800D4560

    # Entry 5
    # ID
    .4byte -1

    # Flags
    .4byte 0x00D00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D42E4
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x800D4560

    # Entry 6
    # ID
    .4byte 29

    # Flags
    .4byte 0x00D00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D4A08
    .4byte NULL
    .4byte 0x800D4CE8
    .4byte NULL
    .4byte 0x800D4E30

    # Entry 7
    # ID
    .4byte 0

    # Flags
    .4byte 0x00D00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D4A08
    .4byte NULL
    .4byte 0x800D4CE8
    .4byte NULL
    .4byte 0x800D4E30

    # Entry 8
    # ID
    .4byte 1

    # Flags
    .4byte 0x00D00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D4A08
    .4byte NULL
    .4byte 0x800D4CE8
    .4byte NULL
    .4byte 0x800D4E30

    # Entry 9
    # ID
    .4byte -1

    # Flags
    .4byte 0x00D00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D4A08
    .4byte NULL
    .4byte 0x800D4CE8
    .4byte NULL
    .4byte 0x800D4E30

    # Entry 10
    # ID
    .4byte -1

    # Flags
    .4byte 0x00D00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D4A08
    .4byte NULL
    .4byte 0x800D4CE8
    .4byte NULL
    .4byte 0x800D4E30

    # Entry 11
    # ID
    .4byte -1

    # Flags
    .4byte 0x00D20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800BFE6C
    .4byte 0x800BFE70
    .4byte NULL
    .4byte NULL
    .4byte NULL

    # Entry 12
    # ID
    .4byte 2

    # Flags
    .4byte 0x00C00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D52F8
    .4byte 0x800D5358
    .4byte 0x800D535C
    .4byte 0x800D5470
    .4byte 0x800D5A6C

    # Entry 13
    # ID
    .4byte 2

    # Flags
    .4byte 0x00C00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D56EC
    .4byte 0x800D575C
    .4byte 0x800D58F4
    .4byte 0x800D5A08
    .4byte 0x800761C8

    # Entry 14
    # ID
    .4byte 2

    # Flags
    .4byte 0x00000000
    .4byte 0x01C00000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008A494
    .4byte 0x8008A4D4
    .4byte 0x8008A644
    .4byte 0x8008A678
    .4byte 0x800761C8

    # Entry 15
    # ID
    .4byte 7

    # Flags
    .4byte 0x00004066
    .4byte 0x01C00000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C95F4
    .4byte 0x800C9614
    .4byte 0x800C9768
    .4byte 0x800C9788
    .4byte 0x800761C8

    # Entry 16
    # ID
    .4byte 8

    # Flags
    .4byte 0x00004066
    .4byte 0x01C00000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C95F4
    .4byte 0x800C9614
    .4byte 0x800C9768
    .4byte 0x800C9788
    .4byte 0x800761C8

    # Entry 17
    # ID
    .4byte 9

    # Flags
    .4byte 0x00004066
    .4byte 0x01C00000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C95F4
    .4byte 0x800C9614
    .4byte 0x800C9768
    .4byte 0x800C9788
    .4byte 0x800761C8

    # Entry 18
    # ID
    .4byte 10

    # Flags
    .4byte 0x00002064
    .4byte 0x01C00000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C9970
    .4byte 0x800C99F8
    .4byte 0x800C9BEC
    .4byte 0x800C9C0C
    .4byte 0x800761C8

    # Entry 19
    # ID
    .4byte 11

    # Flags
    .4byte 0x00002064
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C9E10
    .4byte 0x800C9ED8
    .4byte 0x800C9EFC
    .4byte 0x800CA024
    .4byte 0x800761C8

    # Entry 20
    # ID
    .4byte 12

    # Flags
    .4byte 0x00000067
    .4byte 0x01C00000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CA1F4
    .4byte 0x800CA230
    .4byte 0x800CA53C
    .4byte 0x800CA5D0
    .4byte 0x800761C8

    # Entry 21
    # ID
    .4byte 13

    # Flags
    .4byte 0x00000068
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CA77C
    .4byte 0x800CA830
    .4byte 0x800CA95C
    .4byte 0x800CAA2C
    .4byte 0x800761C8

    # Entry 22
    # ID
    .4byte 13

    # Flags
    .4byte 0x00000068
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CAA4C
    .4byte 0x800CAA6C
    .4byte 0x800CAB84
    .4byte 0x800CABA4
    .4byte 0x800761C8

    # Entry 23
    # ID
    .4byte 14

    # Flags
    .4byte 0x00000000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CAC9C
    .4byte 0x800CADB0
    .4byte 0x800CAE18
    .4byte 0x800CAE60
    .4byte 0x800761C8

    # Entry 24
    # ID
    .4byte 15

    # Flags
    .4byte 0x00000000
    .4byte 0x01C00000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CB528
    .4byte 0x800CB5FC
    .4byte 0x800CB6AC
    .4byte 0x800CB6CC
    .4byte 0x800761C8

    # Entry 25
    # ID
    .4byte 16

    # Flags
    .4byte 0x00008069
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CB2F8
    .4byte 0x800CB334
    .4byte 0x800CB474
    .4byte 0x800CB4B0
    .4byte 0x800761C8

    # Entry 26
    # ID
    .4byte 17

    # Flags
    .4byte 0x00008069
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CB2F8
    .4byte 0x800CB334
    .4byte 0x800CB474
    .4byte 0x800CB4B0
    .4byte 0x800761C8

    # Entry 27
    # ID
    .4byte 18

    # Flags
    .4byte 0x0001006A
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CC388
    .4byte 0x800CC4F8
    .4byte 0x800CC634
    .4byte 0x800CC700
    .4byte 0x800761C8

    # Entry 28
    # ID
    .4byte 19

    # Flags
    .4byte 0x0001006A
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CC388
    .4byte 0x800CC4F8
    .4byte 0x800CC634
    .4byte 0x800CC700
    .4byte 0x800761C8

    # Entry 29
    # ID
    .4byte 20

    # Flags
    .4byte 0x00000000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CCA00
    .4byte 0x800CCD34
    .4byte 0x800CCD58
    .4byte 0x800CCD78
    .4byte 0x800761C8

    # Entry 30
    # ID
    .4byte -1

    # Flags
    .4byte 0x00000000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CCA00
    .4byte 0x800CCD34
    .4byte 0x800CCD58
    .4byte 0x800CCD78
    .4byte 0x800761C8

    # Entry 31
    # ID
    .4byte -1

    # Flags
    .4byte 0x00000000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CCA00
    .4byte 0x800CCD34
    .4byte 0x800CCD58
    .4byte 0x800CCD78
    .4byte 0x800761C8

    # Entry 32
    # ID
    .4byte 23

    # Flags
    .4byte 0x00000000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CCDFC
    .4byte 0x800CCE50
    .4byte 0x800CCE74
    .4byte 0x800CCE94
    .4byte 0x800761C8

    # Entry 33
    # ID
    .4byte 24

    # Flags
    .4byte 0x00000000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CCA00
    .4byte 0x800CCE50
    .4byte 0x800CCD58
    .4byte 0x800CCD78
    .4byte 0x800761C8

    # Entry 34
    # ID
    .4byte 25

    # Flags
    .4byte 0x00000000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CCA00
    .4byte 0x800CCE50
    .4byte 0x800CCD58
    .4byte 0x800CCD78
    .4byte 0x800761C8

    # Entry 35
    # ID
    .4byte 26

    # Flags
    .4byte 0x00000000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80096AA0
    .4byte 0x80096AF4
    .4byte 0x80096B44
    .4byte 0x80096C98
    .4byte 0x800761C8

    # Entry 36
    # ID
    .4byte 27

    # Flags
    .4byte 0x00000000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80096AA0
    .4byte 0x80096AF4
    .4byte 0x80096B44
    .4byte 0x80096C98
    .4byte 0x800761C8

    # Entry 37
    # ID
    .4byte 28

    # Flags
    .4byte 0x00000000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80096AA0
    .4byte 0x80096AF4
    .4byte 0x80096B44
    .4byte 0x80096C98
    .4byte 0x800761C8

    # Entry 38
    # ID
    .4byte 29

    # Flags
    .4byte 0x00520000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80090824
    .4byte 0x80090828
    .4byte 0x8009093C
    .4byte 0x8009095C
    .4byte 0x800761C8

    # Entry 39
    # ID
    .4byte 30

    # Flags
    .4byte 0x00000065
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D607C
    .4byte 0x800D60B8
    .4byte 0x800D623C
    .4byte 0x800D625C
    .4byte 0x800761C8

    # Entry 40
    # ID
    .4byte 31

    # Flags
    .4byte 0x00000065
    .4byte 0x01400000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D6448
    .4byte 0x800D6474
    .4byte 0x800D6584
    .4byte 0x800D65B8
    .4byte 0x800761C8

    # Entry 41
    # ID
    .4byte 34

    # Flags
    .4byte 0x00000065
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D6658
    .4byte 0x800D6694
    .4byte 0x800D6784
    .4byte 0x800D67A4
    .4byte 0x800761C8

    # Entry 42
    # ID
    .4byte 35

    # Flags
    .4byte 0x00000000
    .4byte 0x01400000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D5D3C
    .4byte 0x800D5D78
    .4byte 0x800D5F18
    .4byte 0x800D5F38
    .4byte 0x800761C8

    # Entry 43
    # ID
    .4byte 36

    # Flags
    .4byte 0x00000000
    .4byte 0x01400000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D5D3C
    .4byte 0x800D5D78
    .4byte 0x800D5F18
    .4byte 0x800D5F38
    .4byte 0x800761C8

    # Entry 44
    # ID
    .4byte 46

    # Flags
    .4byte 0x002C0201
    .4byte 0x02800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008AC9C
    .4byte 0x8008ACD8
    .4byte 0x8008ADF0
    .4byte 0x8008AE10
    .4byte 0x800761C8

    # Entry 45
    # ID
    .4byte 47

    # Flags
    .4byte 0x002C0202
    .4byte 0x03800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008B040
    .4byte 0x8008B07C
    .4byte 0x8008ADF0
    .4byte 0x8008AE10
    .4byte 0x800761C8

    # Entry 46
    # ID
    .4byte 48

    # Flags
    .4byte 0x002C0203
    .4byte 0x04800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008B354
    .4byte 0x8008B390
    .4byte 0x8008ADF0
    .4byte 0x8008AE10
    .4byte 0x800761C8

    # Entry 47
    # ID
    .4byte 49

    # Flags
    .4byte 0x002C0204
    .4byte 0x05800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D6C0C
    .4byte NULL
    .4byte 0x800D6E98
    .4byte 0x800D6EF8
    .4byte 0x800761C8

    # Entry 48
    # ID
    .4byte 50

    # Flags
    .4byte 0x002C0204
    .4byte 0x05800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D6D48
    .4byte 0x800D6E70
    .4byte 0x800D6EB8
    .4byte 0x800D6F18
    .4byte 0x800761C8

    # Entry 49
    # ID
    .4byte 51

    # Flags
    .4byte 0x002C0204
    .4byte 0x05800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D6E34
    .4byte NULL
    .4byte 0x800D6ED8
    .4byte 0x800D6F38
    .4byte 0x800761C8

    # Entry 50
    # ID
    .4byte 52

    # Flags
    .4byte 0x00240205
    .4byte 0x06800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008B548
    .4byte 0x8008B5AC
    .4byte 0x8008B600
    .4byte 0x8008B638
    .4byte 0x800761C8

    # Entry 51
    # ID
    .4byte 53

    # Flags
    .4byte 0x00240206
    .4byte 0x07800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008B8D4
    .4byte 0x8008B910
    .4byte 0x8008B940
    .4byte 0x8008B960
    .4byte 0x800761C8

    # Entry 52
    # ID
    .4byte 54

    # Flags
    .4byte 0x00240206
    .4byte 0x07800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008B8D4
    .4byte 0x8008B910
    .4byte 0x8008B940
    .4byte 0x8008B960
    .4byte 0x800761C8

    # Entry 53
    # ID
    .4byte 55

    # Flags
    .4byte 0x00240206
    .4byte 0x07800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008B8D4
    .4byte 0x8008B910
    .4byte 0x8008B940
    .4byte 0x8008B960
    .4byte 0x800761C8

    # Entry 54
    # ID
    .4byte 56

    # Flags
    .4byte 0x00240206
    .4byte 0x07800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008B8D4
    .4byte 0x8008B910
    .4byte 0x8008B940
    .4byte 0x8008B960
    .4byte 0x800761C8

    # Entry 55
    # ID
    .4byte 57

    # Flags
    .4byte 0x00240206
    .4byte 0x07800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008B8D4
    .4byte 0x8008B910
    .4byte 0x8008B940
    .4byte 0x8008B960
    .4byte 0x800761C8

    # Entry 56
    # ID
    .4byte 58

    # Flags
    .4byte 0x00240207
    .4byte 0x08800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008BA98
    .4byte 0x8008BAD4
    .4byte 0x8008BB04
    .4byte 0x8008BB24
    .4byte 0x800761C8

    # Entry 57
    # ID
    .4byte 59

    # Flags
    .4byte 0x00240208
    .4byte 0x09800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008BCFC
    .4byte 0x8008BD80
    .4byte 0x8008BF84
    .4byte 0x8008BFA4
    .4byte 0x800761C8

    # Entry 58
    # ID
    .4byte 60

    # Flags
    .4byte 0x00240A09
    .4byte 0x0A800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008C520
    .4byte 0x8008C55C
    .4byte 0x8008C7F0
    .4byte 0x8008C810
    .4byte 0x800761C8

    # Entry 59
    # ID
    .4byte 61

    # Flags
    .4byte 0x00240A09
    .4byte 0x0A800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008C520
    .4byte 0x8008C55C
    .4byte 0x8008C7F0
    .4byte 0x8008C810
    .4byte 0x800761C8

    # Entry 60
    # ID
    .4byte 62

    # Flags
    .4byte 0x00240A09
    .4byte 0x0A800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008C520
    .4byte 0x8008C55C
    .4byte 0x8008C7F0
    .4byte 0x8008C810
    .4byte 0x800761C8

    # Entry 61
    # ID
    .4byte 63

    # Flags
    .4byte 0x00240A09
    .4byte 0x0A800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008C520
    .4byte 0x8008C55C
    .4byte 0x8008C7F0
    .4byte 0x8008C810
    .4byte 0x800761C8

    # Entry 62
    # ID
    .4byte 64

    # Flags
    .4byte 0x00240A09
    .4byte 0x0A800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008C520
    .4byte 0x8008C55C
    .4byte 0x8008C7F0
    .4byte 0x8008C810
    .4byte 0x800761C8

    # Entry 63
    # ID
    .4byte 66

    # Flags
    .4byte 0x00240A0A
    .4byte 0x0B800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008CA98
    .4byte 0x8008CAD4
    .4byte 0x8008CB04
    .4byte 0x8008CB24
    .4byte 0x800761C8

    # Entry 64
    # ID
    .4byte 67

    # Flags
    .4byte 0x00240A0B
    .4byte 0x0C800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008CCBC
    .4byte 0x8008CCF8
    .4byte 0x8008CD28
    .4byte 0x8008CD48
    .4byte 0x800761C8

    # Entry 65
    # ID
    .4byte 68

    # Flags
    .4byte 0x0024060C
    .4byte 0x0D800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008D010
    .4byte 0x8008D08C
    .4byte 0x8008D5B4
    .4byte 0x8008D5D4
    .4byte 0x800761C8

    # Entry 66
    # ID
    .4byte 69

    # Flags
    .4byte 0x0024060D
    .4byte 0x0E800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008D010
    .4byte 0x8008D194
    .4byte 0x8008D5B4
    .4byte 0x8008D5D4
    .4byte 0x800761C8

    # Entry 67
    # ID
    .4byte 70

    # Flags
    .4byte 0x0024060E
    .4byte 0x0F800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008D010
    .4byte 0x8008D29C
    .4byte 0x8008D5B4
    .4byte 0x8008D5D4
    .4byte 0x800761C8

    # Entry 68
    # ID
    .4byte 71

    # Flags
    .4byte 0x0024060F
    .4byte 0x10800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008D010
    .4byte 0x8008D3A4
    .4byte 0x8008D5B4
    .4byte 0x8008D5D4
    .4byte 0x800761C8

    # Entry 69
    # ID
    .4byte 72

    # Flags
    .4byte 0x00240610
    .4byte 0x11800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008D010
    .4byte 0x8008D4AC
    .4byte 0x8008D5B4
    .4byte 0x8008D5D4
    .4byte 0x800761C8

    # Entry 70
    # ID
    .4byte 73

    # Flags
    .4byte 0x0000060C
    .4byte 0x0DC00000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008D78C
    .4byte 0x8008D7AC
    .4byte 0x8008D7B0
    .4byte 0x8008D7D0
    .4byte 0x800761C8

    # Entry 71
    # ID
    .4byte 74

    # Flags
    .4byte 0x0000060D
    .4byte 0x0EC00000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008D78C
    .4byte 0x8008D7AC
    .4byte 0x8008D7B0
    .4byte 0x8008D7D0
    .4byte 0x800761C8

    # Entry 72
    # ID
    .4byte 75

    # Flags
    .4byte 0x0000060E
    .4byte 0x0FC00000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008D78C
    .4byte 0x8008D7AC
    .4byte 0x8008D7B0
    .4byte 0x8008D7D0
    .4byte 0x800761C8

    # Entry 73
    # ID
    .4byte 76

    # Flags
    .4byte 0x0000060F
    .4byte 0x10C00000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008D78C
    .4byte 0x8008D7AC
    .4byte 0x8008D7B0
    .4byte 0x8008D7D0
    .4byte 0x800761C8

    # Entry 74
    # ID
    .4byte 77

    # Flags
    .4byte 0x00000610
    .4byte 0x11C00000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008D78C
    .4byte 0x8008D7AC
    .4byte 0x8008D7B0
    .4byte 0x8008D7D0
    .4byte 0x800761C8

    # Entry 75
    # ID
    .4byte 165

    # Flags
    .4byte 0x00520000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008F7F0
    .4byte 0x8008FA44
    .4byte 0x8008FB18
    .4byte 0x8008FB64
    .4byte 0x800761C8

    # Entry 76
    # ID
    .4byte 166

    # Flags
    .4byte 0x00520000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008F7F0
    .4byte 0x8008FA44
    .4byte 0x8008FB18
    .4byte 0x8008FB64
    .4byte 0x800761C8

    # Entry 77
    # ID
    .4byte 167

    # Flags
    .4byte 0x00520000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008F7F0
    .4byte 0x8008FA44
    .4byte 0x8008FB18
    .4byte 0x8008FB64
    .4byte 0x800761C8

    # Entry 78
    # ID
    .4byte 168

    # Flags
    .4byte 0x00520000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008F7F0
    .4byte 0x8008FA44
    .4byte 0x8008FB18
    .4byte 0x8008FB64
    .4byte 0x800761C8

    # Entry 79
    # ID
    .4byte 169

    # Flags
    .4byte 0x00520000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008F7F0
    .4byte 0x8008FA44
    .4byte 0x8008FB18
    .4byte 0x8008FB64
    .4byte 0x800761C8

    # Entry 80
    # ID
    .4byte 170

    # Flags
    .4byte 0x00520000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008F7F0
    .4byte 0x8008FA44
    .4byte 0x8008FB18
    .4byte 0x8008FB64
    .4byte 0x800761C8

    # Entry 81
    # ID
    .4byte 171

    # Flags
    .4byte 0x00520000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008F7F0
    .4byte 0x8008FA44
    .4byte 0x8008FB18
    .4byte 0x8008FB64
    .4byte 0x800761C8

    # Entry 82
    # ID
    .4byte 172

    # Flags
    .4byte 0x00520000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008F7F0
    .4byte 0x8008FA44
    .4byte 0x8008FB18
    .4byte 0x8008FB64
    .4byte 0x800761C8

    # Entry 83
    # ID
    .4byte 173

    # Flags
    .4byte 0x00520000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008F7F0
    .4byte 0x8008FA44
    .4byte 0x8008FB18
    .4byte 0x8008FB64
    .4byte 0x800761C8

    # Entry 84
    # ID
    .4byte 174

    # Flags
    .4byte 0x00520000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008F7F0
    .4byte 0x8008FA44
    .4byte 0x8008FB18
    .4byte 0x8008FB64
    .4byte 0x800761C8

    # Entry 85
    # ID
    .4byte 175

    # Flags
    .4byte 0x00520000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008F7F0
    .4byte 0x8008FA44
    .4byte 0x8008FB18
    .4byte 0x8008FB64
    .4byte 0x800761C8

    # Entry 86
    # ID
    .4byte 176

    # Flags
    .4byte 0x00520000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008F7F0
    .4byte 0x8008FA44
    .4byte 0x8008FB18
    .4byte 0x8008FB64
    .4byte 0x800761C8

    # Entry 87
    # ID
    .4byte 177

    # Flags
    .4byte 0x00520000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008FD98
    .4byte 0x8008FF48
    .4byte 0x8008FF84
    .4byte 0x800900EC
    .4byte 0x800761C8

    # Entry 88
    # ID
    .4byte 178

    # Flags
    .4byte 0x00520000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008FD98
    .4byte 0x8008FF48
    .4byte 0x8008FF84
    .4byte 0x800900EC
    .4byte 0x800761C8

    # Entry 89
    # ID
    .4byte 179

    # Flags
    .4byte 0x00520000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008FD98
    .4byte 0x8008FF48
    .4byte 0x8008FF84
    .4byte 0x800900EC
    .4byte 0x800761C8

    # Entry 90
    # ID
    .4byte 180

    # Flags
    .4byte 0x00520000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8008FD98
    .4byte 0x8008FF48
    .4byte 0x8008FF84
    .4byte 0x800900EC
    .4byte 0x800761C8

    # Entry 91
    # ID
    .4byte 181

    # Flags
    .4byte 0x00520000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800901D0
    .4byte 0x80090324
    .4byte 0x8009035C
    .4byte 0x800904C0
    .4byte 0x800761C8

    # Entry 92
    # ID
    .4byte 78

    # Flags
    .4byte 0x00400000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80094A14
    .4byte 0x80094B20
    .4byte 0x80094B24
    .4byte 0x80094B44
    .4byte 0x800761C8

    # Entry 93
    # ID
    .4byte 89

    # Flags
    .4byte 0x00400000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80094A14
    .4byte 0x80094B20
    .4byte 0x80094B24
    .4byte 0x80094B44
    .4byte 0x800761C8

    # Entry 94
    # ID
    .4byte 79

    # Flags
    .4byte 0x00440062
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x80096124
    .4byte 0x80096228
    .4byte 0x800761C8

    # Entry 95
    # ID
    .4byte 80

    # Flags
    .4byte 0x00440062
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x80096124
    .4byte 0x80096228
    .4byte 0x800761C8

    # Entry 96
    # ID
    .4byte 81

    # Flags
    .4byte 0x00440062
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x80096124
    .4byte 0x80096228
    .4byte 0x800761C8

    # Entry 97
    # ID
    .4byte 82

    # Flags
    .4byte 0x00440062
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x80096124
    .4byte 0x80096228
    .4byte 0x800761C8

    # Entry 98
    # ID
    .4byte 83

    # Flags
    .4byte 0x00440062
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x80096144
    .4byte 0x80096208
    .4byte 0x800761C8

    # Entry 99
    # ID
    .4byte 84

    # Flags
    .4byte 0x00440062
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x80096124
    .4byte 0x80096208
    .4byte 0x800761C8

    # Entry 100
    # ID
    .4byte 85

    # Flags
    .4byte 0x00440462
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x800961B0
    .4byte 0x8009634C
    .4byte 0x800761C8

    # Entry 101
    # ID
    .4byte 86

    # Flags
    .4byte 0x00440462
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x800961B0
    .4byte 0x8009634C
    .4byte 0x800761C8

    # Entry 102
    # ID
    .4byte 87

    # Flags
    .4byte 0x00440462
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x800961B0
    .4byte 0x8009634C
    .4byte 0x800761C8

    # Entry 103
    # ID
    .4byte 88

    # Flags
    .4byte 0x00440462
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x800961B0
    .4byte 0x8009634C
    .4byte 0x800761C8

    # Entry 104
    # ID
    .4byte 92

    # Flags
    .4byte 0x00440062
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x80096124
    .4byte 0x80096470
    .4byte 0x800761C8

    # Entry 105
    # ID
    .4byte 93

    # Flags
    .4byte 0x00440062
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x80096124
    .4byte 0x80096470
    .4byte 0x800761C8

    # Entry 106
    # ID
    .4byte 94

    # Flags
    .4byte 0x00440062
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x80096124
    .4byte 0x80096470
    .4byte 0x800761C8

    # Entry 107
    # ID
    .4byte 95

    # Flags
    .4byte 0x00440062
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x80096124
    .4byte 0x80096470
    .4byte 0x800761C8

    # Entry 108
    # ID
    .4byte 96

    # Flags
    .4byte 0x00440862
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x80096124
    .4byte 0x80096228
    .4byte 0x800761C8

    # Entry 109
    # ID
    .4byte 97

    # Flags
    .4byte 0x00440862
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x80096124
    .4byte 0x80096228
    .4byte 0x800761C8

    # Entry 110
    # ID
    .4byte 98

    # Flags
    .4byte 0x00440862
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x80096124
    .4byte 0x80096228
    .4byte 0x800761C8

    # Entry 111
    # ID
    .4byte 99

    # Flags
    .4byte 0x00440862
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x80096124
    .4byte 0x80096228
    .4byte 0x800761C8

    # Entry 112
    # ID
    .4byte 100

    # Flags
    .4byte 0x00440C62
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x800961B0
    .4byte 0x8009634C
    .4byte 0x800761C8

    # Entry 113
    # ID
    .4byte 101

    # Flags
    .4byte 0x00440C62
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x800961B0
    .4byte 0x8009634C
    .4byte 0x800761C8

    # Entry 114
    # ID
    .4byte 102

    # Flags
    .4byte 0x00440C62
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x800961B0
    .4byte 0x8009634C
    .4byte 0x800761C8

    # Entry 115
    # ID
    .4byte 103

    # Flags
    .4byte 0x00440C62
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x800961B0
    .4byte 0x8009634C
    .4byte 0x800761C8

    # Entry 116
    # ID
    .4byte 104

    # Flags
    .4byte 0x00440862
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x80096124
    .4byte 0x80096470
    .4byte 0x800761C8

    # Entry 117
    # ID
    .4byte 105

    # Flags
    .4byte 0x00440862
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x80096124
    .4byte 0x80096470
    .4byte 0x800761C8

    # Entry 118
    # ID
    .4byte 106

    # Flags
    .4byte 0x00440862
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x80096124
    .4byte 0x80096470
    .4byte 0x800761C8

    # Entry 119
    # ID
    .4byte 107

    # Flags
    .4byte 0x00440862
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80095E80
    .4byte 0x80096120
    .4byte 0x80096124
    .4byte 0x80096470
    .4byte 0x800761C8

    # Entry 120
    # ID
    .4byte 108

    # Flags
    .4byte 0x00440040
    .4byte 0x3F800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CD390
    .4byte 0x800CD3B0
    .4byte 0x800CD3D0
    .4byte 0x800CD3F0
    .4byte 0x800761C8

    # Entry 121
    # ID
    .4byte 109

    # Flags
    .4byte 0x00440041
    .4byte 0x40800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CD390
    .4byte 0x800CD3B0
    .4byte 0x800CD3D0
    .4byte 0x800CD3F0
    .4byte 0x800761C8

    # Entry 122
    # ID
    .4byte 110

    # Flags
    .4byte 0x00440842
    .4byte 0x41800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CD390
    .4byte 0x800CD3B0
    .4byte 0x800CD3D0
    .4byte 0x800CD3F0
    .4byte 0x800761C8

    # Entry 123
    # ID
    .4byte 111

    # Flags
    .4byte 0x00440043
    .4byte 0x42800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CD390
    .4byte 0x800CD3B0
    .4byte 0x800CD3D0
    .4byte 0x800CD3F0
    .4byte 0x800761C8

    # Entry 124
    # ID
    .4byte 112

    # Flags
    .4byte 0x00440044
    .4byte 0x43800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CD458
    .4byte 0x800CD478
    .4byte 0x800CD498
    .4byte 0x800CD4B8
    .4byte 0x800761C8

    # Entry 125
    # ID
    .4byte 113

    # Flags
    .4byte 0x00440045
    .4byte 0x44800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CD458
    .4byte 0x800CD478
    .4byte 0x800CD498
    .4byte 0x800CD4B8
    .4byte 0x800761C8

    # Entry 126
    # ID
    .4byte 114

    # Flags
    .4byte 0x00440846
    .4byte 0x45800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CD458
    .4byte 0x800CD478
    .4byte 0x800CD498
    .4byte 0x800CD4B8
    .4byte 0x800761C8

    # Entry 127
    # ID
    .4byte 115

    # Flags
    .4byte 0x00440047
    .4byte 0x46800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CD458
    .4byte 0x800CD478
    .4byte 0x800CD498
    .4byte 0x800CD4B8
    .4byte 0x800761C8

    # Entry 128
    # ID
    .4byte 116

    # Flags
    .4byte 0x00440048
    .4byte 0x47800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CD520
    .4byte 0x800CD540
    .4byte 0x800CD560
    .4byte 0x800CD580
    .4byte 0x800761C8

    # Entry 129
    # ID
    .4byte 117

    # Flags
    .4byte 0x00440049
    .4byte 0x48800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CD520
    .4byte 0x800CD540
    .4byte 0x800CD560
    .4byte 0x800CD580
    .4byte 0x800761C8

    # Entry 130
    # ID
    .4byte 118

    # Flags
    .4byte 0x0044084A
    .4byte 0x49800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CD520
    .4byte 0x800CD540
    .4byte 0x800CD560
    .4byte 0x800CD580
    .4byte 0x800761C8

    # Entry 131
    # ID
    .4byte 119

    # Flags
    .4byte 0x0044004B
    .4byte 0x4A800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CD520
    .4byte 0x800CD540
    .4byte 0x800CD560
    .4byte 0x800CD580
    .4byte 0x800761C8

    # Entry 132
    # ID
    .4byte 120

    # Flags
    .4byte 0x0044004C
    .4byte 0x4B800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CD6A0
    .4byte 0x800CD7C4
    .4byte 0x800CD7E4
    .4byte 0x800CD804
    .4byte 0x800761C8

    # Entry 133
    # ID
    .4byte 121

    # Flags
    .4byte 0x0044004D
    .4byte 0x4C800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CD6A0
    .4byte 0x800CD7C4
    .4byte 0x800CD7E4
    .4byte 0x800CD804
    .4byte 0x800761C8

    # Entry 134
    # ID
    .4byte 122

    # Flags
    .4byte 0x0044084E
    .4byte 0x4D800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CD6A0
    .4byte 0x800CD7C4
    .4byte 0x800CD7E4
    .4byte 0x800CD804
    .4byte 0x800761C8

    # Entry 135
    # ID
    .4byte 123

    # Flags
    .4byte 0x0044004F
    .4byte 0x4E800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CD6A0
    .4byte 0x800CD7C4
    .4byte 0x800CD7E4
    .4byte 0x800CD804
    .4byte 0x800761C8

    # Entry 136
    # ID
    .4byte 124

    # Flags
    .4byte 0x00440050
    .4byte 0x4F800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CD88C
    .4byte 0x800CD8AC
    .4byte 0x800CD8CC
    .4byte 0x800CD8EC
    .4byte 0x800761C8

    # Entry 137
    # ID
    .4byte 125

    # Flags
    .4byte 0x00440051
    .4byte 0x50800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CD88C
    .4byte 0x800CD8AC
    .4byte 0x800CD8CC
    .4byte 0x800CD8EC
    .4byte 0x800761C8

    # Entry 138
    # ID
    .4byte 126

    # Flags
    .4byte 0x00440852
    .4byte 0x51800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CD88C
    .4byte 0x800CD8AC
    .4byte 0x800CD8CC
    .4byte 0x800CD8EC
    .4byte 0x800761C8

    # Entry 139
    # ID
    .4byte 127

    # Flags
    .4byte 0x00440053
    .4byte 0x52800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CD88C
    .4byte 0x800CD8AC
    .4byte 0x800CD8CC
    .4byte 0x800CD8EC
    .4byte 0x800761C8

    # Entry 140
    # ID
    .4byte 128

    # Flags
    .4byte 0x00440054
    .4byte 0x53800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CDB14
    .4byte 0x800CDB34
    .4byte 0x800CDB54
    .4byte 0x800CDB74
    .4byte 0x800761C8

    # Entry 141
    # ID
    .4byte 129

    # Flags
    .4byte 0x00440055
    .4byte 0x54800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CDB14
    .4byte 0x800CDB34
    .4byte 0x800CDB54
    .4byte 0x800CDB74
    .4byte 0x800761C8

    # Entry 142
    # ID
    .4byte 130

    # Flags
    .4byte 0x00440856
    .4byte 0x55800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CDB14
    .4byte 0x800CDB34
    .4byte 0x800CDB54
    .4byte 0x800CDB74
    .4byte 0x800761C8

    # Entry 143
    # ID
    .4byte 131

    # Flags
    .4byte 0x00440057
    .4byte 0x56800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CDB14
    .4byte 0x800CDB34
    .4byte 0x800CDB54
    .4byte 0x800CDB74
    .4byte 0x800761C8

    # Entry 144
    # ID
    .4byte 134

    # Flags
    .4byte 0x00440058
    .4byte 0x57800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CF0B8
    .4byte 0x800CF118
    .4byte 0x800CF1A0
    .4byte 0x800CF258
    .4byte 0x800761C8

    # Entry 145
    # ID
    .4byte 135

    # Flags
    .4byte 0x004C0058
    .4byte 0x57800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CF2B8
    .4byte 0x800CF2BC
    .4byte 0x800CF380
    .4byte 0x800CF3A0
    .4byte 0x800761C8

    # Entry 146
    # ID
    .4byte 136

    # Flags
    .4byte 0x004C0058
    .4byte 0x57800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CF424
    .4byte 0x800CF428
    .4byte 0x800CF494
    .4byte 0x800CF4B4
    .4byte 0x800761C8

    # Entry 147
    # ID
    .4byte 137

    # Flags
    .4byte 0x004C0058
    .4byte 0x57800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CF528
    .4byte 0x800CF52C
    .4byte 0x800CF54C
    .4byte 0x800CF56C
    .4byte 0x800761C8

    # Entry 148
    # ID
    .4byte 138

    # Flags
    .4byte 0x00440159
    .4byte 0x58800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CE308
    .4byte 0x800CE348
    .4byte 0x800CE350
    .4byte 0x800CE390
    .4byte 0x800761C8

    # Entry 149
    # ID
    .4byte 139

    # Flags
    .4byte 0x00440559
    .4byte 0x58800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CE328
    .4byte 0x800CE34C
    .4byte 0x800CE370
    .4byte 0x800CE3B8
    .4byte 0x800761C8

    # Entry 150
    # ID
    .4byte 140

    # Flags
    .4byte 0x00440159
    .4byte 0x58800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CE308
    .4byte 0x800CE348
    .4byte 0x800CE350
    .4byte 0x800CE390
    .4byte 0x800761C8

    # Entry 151
    # ID
    .4byte 141

    # Flags
    .4byte 0x00440559
    .4byte 0x58800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CE328
    .4byte 0x800CE34C
    .4byte 0x800CE370
    .4byte 0x800CE3B8
    .4byte 0x800761C8

    # Entry 152
    # ID
    .4byte 142

    # Flags
    .4byte 0x004C015A
    .4byte 0x59800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CEAF0
    .4byte 0x800CEC50
    .4byte 0x800CEC58
    .4byte 0x800CEC98
    .4byte 0x800761C8

    # Entry 153
    # ID
    .4byte 143

    # Flags
    .4byte 0x004C055A
    .4byte 0x59800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800CEBA0
    .4byte 0x800CEC54
    .4byte 0x800CEC78
    .4byte 0x800CECC0
    .4byte 0x800761C8

    # Entry 154
    # ID
    .4byte 144

    # Flags
    .4byte 0x0044825B
    .4byte 0x5A800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D2DD0
    .4byte 0x800D2E0C
    .4byte 0x800D2E2C
    .4byte 0x800D2E4C
    .4byte 0x800761C8

    # Entry 155
    # ID
    .4byte 145

    # Flags
    .4byte 0x0045065B
    .4byte 0x5A800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D2EF8
    .4byte 0x800D2F34
    .4byte 0x800D2F54
    .4byte 0x800D2F74
    .4byte 0x800761C8

    # Entry 156
    # ID
    .4byte 146

    # Flags
    .4byte 0x00528000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D30C0
    .4byte 0x800D30FC
    .4byte 0x800D3100
    .4byte 0x800D3120
    .4byte 0x800761C8

    # Entry 157
    # ID
    .4byte 147

    # Flags
    .4byte 0x00530000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D30C0
    .4byte 0x800D30FC
    .4byte 0x800D3100
    .4byte 0x800D3120
    .4byte 0x800761C8

    # Entry 158
    # ID
    .4byte 149

    # Flags
    .4byte 0x00440000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D79AC
    .4byte 0x800D7AEC
    .4byte 0x800D7B4C
    .4byte 0x800D7B8C
    .4byte 0x800761C8

    # Entry 159
    # ID
    .4byte 150

    # Flags
    .4byte 0x004C015C
    .4byte 0x5B800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D7DFC
    .4byte 0x800D8024
    .4byte 0x800D8064
    .4byte 0x800D80A4
    .4byte 0x800761C8

    # Entry 160
    # ID
    .4byte 151

    # Flags
    .4byte 0x0044015D
    .4byte 0x5C800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D83AC
    .4byte 0x800D843C
    .4byte 0x800D8444
    .4byte 0x800D8484
    .4byte 0x800761C8

    # Entry 161
    # ID
    .4byte 152

    # Flags
    .4byte 0x00440000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D88B8
    .4byte 0x800D88F8
    .4byte 0x800D8900
    .4byte 0x800D8940
    .4byte 0x800761C8

    # Entry 162
    # ID
    .4byte 153

    # Flags
    .4byte 0x00440000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D79B0
    .4byte 0x800D7B1C
    .4byte 0x800D7B6C
    .4byte 0x800D7BB4
    .4byte 0x800761C8

    # Entry 163
    # ID
    .4byte 154

    # Flags
    .4byte 0x004C055C
    .4byte 0x5B800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D7F10
    .4byte 0x800D8044
    .4byte 0x800D8084
    .4byte 0x800D80CC
    .4byte 0x800761C8

    # Entry 164
    # ID
    .4byte 155

    # Flags
    .4byte 0x0044055D
    .4byte 0x5C800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D83F4
    .4byte 0x800D8440
    .4byte 0x800D8464
    .4byte 0x800D84AC
    .4byte 0x800761C8

    # Entry 165
    # ID
    .4byte 156

    # Flags
    .4byte 0x00440000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D88D8
    .4byte 0x800D88FC
    .4byte 0x800D8920
    .4byte 0x800D8968
    .4byte 0x800761C8

    # Entry 166
    # ID
    .4byte 157

    # Flags
    .4byte 0x00440000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D79AC
    .4byte 0x800D7AEC
    .4byte 0x800D7B4C
    .4byte 0x800D7B8C
    .4byte 0x800761C8

    # Entry 167
    # ID
    .4byte 158

    # Flags
    .4byte 0x004C015C
    .4byte 0x5B800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D7DFC
    .4byte 0x800D8024
    .4byte 0x800D8064
    .4byte 0x800D80A4
    .4byte 0x800761C8

    # Entry 168
    # ID
    .4byte 159

    # Flags
    .4byte 0x0044015D
    .4byte 0x5C800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D83AC
    .4byte 0x800D843C
    .4byte 0x800D8444
    .4byte 0x800D8484
    .4byte 0x800761C8

    # Entry 169
    # ID
    .4byte 160

    # Flags
    .4byte 0x00440000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D88B8
    .4byte 0x800D88F8
    .4byte 0x800D8900
    .4byte 0x800D8940
    .4byte 0x800761C8

    # Entry 170
    # ID
    .4byte 161

    # Flags
    .4byte 0x00440000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D79B0
    .4byte 0x800D7B1C
    .4byte 0x800D7B6C
    .4byte 0x800D7BB4
    .4byte 0x800761C8

    # Entry 171
    # ID
    .4byte 162

    # Flags
    .4byte 0x004C055C
    .4byte 0x5B800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D7F10
    .4byte 0x800D8044
    .4byte 0x800D8084
    .4byte 0x800D80CC
    .4byte 0x800761C8

    # Entry 172
    # ID
    .4byte 163

    # Flags
    .4byte 0x0044055D
    .4byte 0x5C800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D83F4
    .4byte 0x800D8440
    .4byte 0x800D8464
    .4byte 0x800D84AC
    .4byte 0x800761C8

    # Entry 173
    # ID
    .4byte 164

    # Flags
    .4byte 0x00440000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D88D8
    .4byte 0x800D88FC
    .4byte 0x800D8920
    .4byte 0x800D8968
    .4byte 0x800761C8

    # Entry 174
    # ID
    .4byte -1

    # Flags
    .4byte 0x00480000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80096DF4
    .4byte 0x80096DF8
    .4byte 0x80096E48
    .4byte 0x80096ED0
    .4byte 0x800761C8

    # Entry 175
    # ID
    .4byte 90

    # Flags
    .4byte 0x00484066
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80096FD0
    .4byte 0x80097074
    .4byte 0x80097098
    .4byte 0x800970B8
    .4byte 0x800761C8

    # Entry 176
    # ID
    .4byte 91

    # Flags
    .4byte 0x00484066
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80096FD0
    .4byte 0x80097074
    .4byte 0x80097098
    .4byte 0x800970B8
    .4byte 0x800761C8

    # Entry 177
    # ID
    .4byte -1

    # Flags
    .4byte 0x00482064
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800971B0
    .4byte 0x80097458
    .4byte 0x8009747C
    .4byte 0x8009749C
    .4byte 0x800761C8

    # Entry 178
    # ID
    .4byte 37

    # Flags
    .4byte 0x00100000
    .4byte 0x01C00000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800926DC
    .4byte 0x80092758
    .4byte 0x80092870
    .4byte 0x800928AC
    .4byte 0x800761C8

    # Entry 179
    # ID
    .4byte 38

    # Flags
    .4byte 0x00180000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80092A24
    .4byte 0x80092A78
    .4byte 0x80092B70
    .4byte 0x80092BAC
    .4byte 0x800761C8

    # Entry 180
    # ID
    .4byte 39

    # Flags
    .4byte 0x00100000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80092CAC
    .4byte 0x80092CFC
    .4byte 0x80092E10
    .4byte 0x80092E30
    .4byte 0x800761C8

    # Entry 181
    # ID
    .4byte 40

    # Flags
    .4byte 0x00100000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80093354
    .4byte 0x80093624
    .4byte 0x80093628
    .4byte 0x8009365C
    .4byte 0x800761C8

    # Entry 182
    # ID
    .4byte 37

    # Flags
    .4byte 0x00101073
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80093CD0
    .4byte 0x80093EC0
    .4byte 0x8009403C
    .4byte 0x80094078
    .4byte 0x800761C8

    # Entry 183
    # ID
    .4byte 183

    # Flags
    .4byte 0x0060006C
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80097DC0
    .4byte 0x80097E1C
    .4byte 0x80097E20
    .4byte 0x80097E40
    .4byte 0x800761C8

    # Entry 184
    # ID
    .4byte 184

    # Flags
    .4byte 0x0060006C
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80097FC0
    .4byte 0x8009802C
    .4byte 0x8009807C
    .4byte 0x8009809C
    .4byte 0x800761C8

    # Entry 185
    # ID
    .4byte 185

    # Flags
    .4byte 0x0062006C
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009F1E0
    .4byte 0x8009F2B0
    .4byte 0x8009F2B4
    .4byte 0x8009F2D4
    .4byte 0x800761C8

    # Entry 186
    # ID
    .4byte 186

    # Flags
    .4byte 0x0060006C
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80098194
    .4byte 0x800981D0
    .4byte 0x800981D4
    .4byte 0x800981F4
    .4byte 0x800761C8

    # Entry 187
    # ID
    .4byte 187

    # Flags
    .4byte 0x00640231
    .4byte 0x32000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800985B4
    .4byte 0x800985F0
    .4byte 0x800985F4
    .4byte 0x80098614
    .4byte 0x800761C8

    # Entry 188
    # ID
    .4byte 188

    # Flags
    .4byte 0x0060006C
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80098380
    .4byte 0x800983BC
    .4byte 0x800983C0
    .4byte 0x800983E0
    .4byte 0x800761C8

    # Entry 189
    # ID
    .4byte 189

    # Flags
    .4byte 0x0060006C
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80098380
    .4byte 0x800983BC
    .4byte 0x800983C0
    .4byte 0x800983E0
    .4byte 0x800761C8

    # Entry 190
    # ID
    .4byte 190

    # Flags
    .4byte 0x0060006C
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C8C04
    .4byte 0x800C8C40
    .4byte 0x800C8C44
    .4byte 0x800C8C64
    .4byte 0x800761C8

    # Entry 191
    # ID
    .4byte 191

    # Flags
    .4byte 0x0060006D
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80097DC0
    .4byte 0x80097E1C
    .4byte 0x80097E20
    .4byte 0x80097E40
    .4byte 0x800761C8

    # Entry 192
    # ID
    .4byte 192

    # Flags
    .4byte 0x0060006D
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80097FC0
    .4byte 0x8009802C
    .4byte 0x8009807C
    .4byte 0x8009809C
    .4byte 0x800761C8

    # Entry 193
    # ID
    .4byte 193

    # Flags
    .4byte 0x0062006D
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009F1E0
    .4byte 0x8009F2B0
    .4byte 0x8009F2B4
    .4byte 0x8009F2D4
    .4byte 0x800761C8

    # Entry 194
    # ID
    .4byte 194

    # Flags
    .4byte 0x0060006D
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80098194
    .4byte 0x800981D0
    .4byte 0x800981D4
    .4byte 0x800981F4
    .4byte 0x800761C8

    # Entry 195
    # ID
    .4byte 195

    # Flags
    .4byte 0x00640232
    .4byte 0x33000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800985B4
    .4byte 0x800985F0
    .4byte 0x800985F4
    .4byte 0x80098614
    .4byte 0x800761C8

    # Entry 196
    # ID
    .4byte 196

    # Flags
    .4byte 0x0060006D
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80098380
    .4byte 0x800983BC
    .4byte 0x800983C0
    .4byte 0x800983E0
    .4byte 0x800761C8

    # Entry 197
    # ID
    .4byte 197

    # Flags
    .4byte 0x0060006D
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80098380
    .4byte 0x800983BC
    .4byte 0x800983C0
    .4byte 0x800983E0
    .4byte 0x800761C8

    # Entry 198
    # ID
    .4byte 198

    # Flags
    .4byte 0x0060006D
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C8C04
    .4byte 0x800C8C40
    .4byte 0x800C8C44
    .4byte 0x800C8C64
    .4byte 0x800761C8

    # Entry 199
    # ID
    .4byte 199

    # Flags
    .4byte 0x0070006E
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800988A8
    .4byte 0x800988E4
    .4byte 0x800988E8
    .4byte 0x80098908
    .4byte 0x800761C8

    # Entry 200
    # ID
    .4byte 200

    # Flags
    .4byte 0x0070006E
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80098AA0
    .4byte 0x80098ADC
    .4byte 0x80098AE0
    .4byte 0x80098B00
    .4byte 0x800761C8

    # Entry 201
    # ID
    .4byte 201

    # Flags
    .4byte 0x0070006E
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80098AA0
    .4byte 0x80098ADC
    .4byte 0x80098AE0
    .4byte 0x80098B00
    .4byte 0x800761C8

    # Entry 202
    # ID
    .4byte 202

    # Flags
    .4byte 0x00700000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C2028
    .4byte 0x800C2180
    .4byte 0x800C22C0
    .4byte 0x800C2348
    .4byte 0x800761C8

    # Entry 203
    # ID
    .4byte 203

    # Flags
    .4byte 0x00700000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C2028
    .4byte 0x800C2180
    .4byte 0x800C22C0
    .4byte 0x800C2348
    .4byte 0x800761C8

    # Entry 204
    # ID
    .4byte 204

    # Flags
    .4byte 0x00700000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C252C
    .4byte 0x800C25AC
    .4byte 0x800C25B0
    .4byte 0x800C25D0
    .4byte 0x800761C8

    # Entry 205
    # ID
    .4byte 286

    # Flags
    .4byte 0x00500000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80098C14
    .4byte 0x80098C50
    .4byte 0x80098C54
    .4byte 0x80098C74
    .4byte 0x800761C8

    # Entry 206
    # ID
    .4byte 287

    # Flags
    .4byte 0x00500000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80098DEC
    .4byte 0x80098DF0
    .4byte 0x80098DF4
    .4byte 0x80098E14
    .4byte 0x800761C8

    # Entry 207
    # ID
    .4byte 288

    # Flags
    .4byte 0x00500000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80098EBC
    .4byte 0x80098EF8
    .4byte 0x80098EFC
    .4byte 0x80098F1C
    .4byte 0x800761C8

    # Entry 208
    # ID
    .4byte 289

    # Flags
    .4byte 0x00500000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80098EBC
    .4byte 0x80098EF8
    .4byte 0x80098EFC
    .4byte 0x80098F1C
    .4byte 0x800761C8

    # Entry 209
    # ID
    .4byte 290

    # Flags
    .4byte 0x00500000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80098F90
    .4byte 0x80098FCC
    .4byte 0x80098FD0
    .4byte 0x80098FF0
    .4byte 0x800761C8

    # Entry 210
    # ID
    .4byte 291

    # Flags
    .4byte 0x00500000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80098F90
    .4byte 0x80098FCC
    .4byte 0x80098FD0
    .4byte 0x80098FF0
    .4byte 0x800761C8

    # Entry 211
    # ID
    .4byte 205

    # Flags
    .4byte 0x00500000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800990B8
    .4byte 0x80099138
    .4byte 0x8009913C
    .4byte 0x8009915C
    .4byte 0x800761C8

    # Entry 212
    # ID
    .4byte 242

    # Flags
    .4byte 0x00A00033
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D8CC8
    .4byte 0x800D8D80
    .4byte 0x800D8D88
    .4byte 0x800D8E08
    .4byte 0x800761C8

    # Entry 213
    # ID
    .4byte 242

    # Flags
    .4byte 0x00A00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D9E80
    .4byte 0x800D9F90
    .4byte 0x800D9F94
    .4byte 0x800D9FDC
    .4byte 0x800761C8

    # Entry 214
    # ID
    .4byte 243

    # Flags
    .4byte 0x00A00033
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D8D24
    .4byte 0x800D8D84
    .4byte 0x800D8DD0
    .4byte 0x800D8E6C
    .4byte 0x800761C8

    # Entry 215
    # ID
    .4byte 243

    # Flags
    .4byte 0x00A00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D9E80
    .4byte 0x800D9F90
    .4byte 0x800D9F94
    .4byte 0x800D9FDC
    .4byte 0x800761C8

    # Entry 216
    # ID
    .4byte 244

    # Flags
    .4byte 0x00A00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DA318
    .4byte 0x800DA31C
    .4byte 0x800DA3D0
    .4byte 0x800DA418
    .4byte 0x800761C8

    # Entry 217
    # ID
    .4byte 245

    # Flags
    .4byte 0x00A40034
    .4byte 0x34000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DA568
    .4byte 0x800DA5A4
    .4byte 0x800DA5A8
    .4byte 0x800DA5F0
    .4byte 0x800761C8

    # Entry 218
    # ID
    .4byte 246

    # Flags
    .4byte 0x00A00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DA744
    .4byte 0x800DA780
    .4byte 0x800DA784
    .4byte 0x800DA7E4
    .4byte 0x800761C8

    # Entry 219
    # ID
    .4byte 247

    # Flags
    .4byte 0x00A40035
    .4byte 0x35000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DD8C4
    .4byte 0x800DD92C
    .4byte 0x800DD930
    .4byte 0x800DD990
    .4byte 0x800761C8

    # Entry 220
    # ID
    .4byte 248

    # Flags
    .4byte 0x00A40036
    .4byte 0x36000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DDA10
    .4byte 0x800DDA5C
    .4byte 0x800DDA60
    .4byte 0x800DDAC0
    .4byte 0x800761C8

    # Entry 221
    # ID
    .4byte 249

    # Flags
    .4byte 0x00A40037
    .4byte 0x37000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DDB40
    .4byte 0x800DDB8C
    .4byte 0x800DDB90
    .4byte 0x800DDBF0
    .4byte 0x800DDC70

    # Entry 222
    # ID
    .4byte 250

    # Flags
    .4byte 0x00A40038
    .4byte 0x38000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DDCB4
    .4byte 0x800DDD00
    .4byte 0x800DDD04
    .4byte 0x800DDD64
    .4byte 0x800761C8

    # Entry 223
    # ID
    .4byte 251

    # Flags
    .4byte 0x00B00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DAC70
    .4byte 0x800DAC74
    .4byte 0x800DADE8
    .4byte 0x800DAE94
    .4byte 0x800761C8

    # Entry 224
    # ID
    .4byte 252

    # Flags
    .4byte 0x00B00000
    .4byte 0x01400000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DB908
    .4byte 0x800DBA4C
    .4byte 0x800DBA6C
    .4byte 0x800DBA8C
    .4byte 0x800761C8

    # Entry 225
    # ID
    .4byte 253

    # Flags
    .4byte 0x00B20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DC2E4
    .4byte 0x800DC328
    .4byte 0x800DC32C
    .4byte 0x800DC34C
    .4byte 0x800761C8

    # Entry 226
    # ID
    .4byte 254

    # Flags
    .4byte 0x00B00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DB004
    .4byte 0x800DB008
    .4byte 0x800DB00C
    .4byte 0x800DB1F8
    .4byte 0x800761C8

    # Entry 227
    # ID
    .4byte 255

    # Flags
    .4byte 0x00B00000
    .4byte 0x01400000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DBD10
    .4byte 0x800DBD30
    .4byte 0x800DBD50
    .4byte 0x800DBE9C
    .4byte 0x800761C8

    # Entry 228
    # ID
    .4byte 256

    # Flags
    .4byte 0x00B20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DC468
    .4byte 0x800DC4AC
    .4byte 0x800DC4B0
    .4byte 0x800DC5EC
    .4byte 0x800761C8

    # Entry 229
    # ID
    .4byte 257

    # Flags
    .4byte 0x00B00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DC7F0
    .4byte 0x800DC82C
    .4byte 0x800DC830
    .4byte 0x800DC890
    .4byte 0x800761C8

    # Entry 230
    # ID
    .4byte 258

    # Flags
    .4byte 0x00B00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DC110
    .4byte 0x800DC160
    .4byte 0x800DC224
    .4byte 0x800DC264
    .4byte 0x800761C8

    # Entry 231
    # ID
    .4byte 259

    # Flags
    .4byte 0x00B00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x800761C8

    # Entry 232
    # ID
    .4byte 260

    # Flags
    .4byte 0x00B00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x800761C8

    # Entry 233
    # ID
    .4byte 42

    # Flags
    .4byte 0x00100000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800994D8
    .4byte 0x800996F0
    .4byte 0x80099714
    .4byte 0x80099734
    .4byte 0x800761C8

    # Entry 234
    # ID
    .4byte 43

    # Flags
    .4byte 0x00100000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800994D8
    .4byte 0x800996F0
    .4byte 0x80099714
    .4byte 0x80099734
    .4byte 0x800761C8

    # Entry 235
    # ID
    .4byte 41

    # Flags
    .4byte 0x00100000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800999D8
    .4byte 0x80099A14
    .4byte 0x80099A18
    .4byte 0x80099A38
    .4byte 0x800761C8

    # Entry 236
    # ID
    .4byte 44

    # Flags
    .4byte 0x00100000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80099BD0
    .4byte 0x80099C24
    .4byte 0x80099CEC
    .4byte 0x80099D48
    .4byte 0x800761C8

    # Entry 237
    # ID
    .4byte -1

    # Flags
    .4byte 0x00100000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80099E24
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL

    # Entry 238
    # ID
    .4byte 45

    # Flags
    .4byte 0x00100000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80099E80
    .4byte 0x80099EBC
    .4byte 0x80099EC0
    .4byte 0x80099EFC
    .4byte 0x800761C8

    # Entry 239
    # ID
    .4byte 262

    # Flags
    .4byte 0x00B20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DE69C
    .4byte 0x800DE6BC
    .4byte 0x800DE6C0
    .4byte 0x800DE6C4
    .4byte 0x800761C8

    # Entry 240
    # ID
    .4byte 263

    # Flags
    .4byte 0x00B20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DE6C8
    .4byte 0x800DE6E8
    .4byte 0x800DE6EC
    .4byte 0x800DE6F0
    .4byte 0x800761C8

    # Entry 241
    # ID
    .4byte 264

    # Flags
    .4byte 0x00B20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DE6F4
    .4byte 0x800DE714
    .4byte 0x800DE718
    .4byte 0x800DE71C
    .4byte 0x800DE720

    # Entry 242
    # ID
    .4byte 265

    # Flags
    .4byte 0x00B20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DE76C
    .4byte 0x800DE78C
    .4byte 0x800DE790
    .4byte 0x800DE794
    .4byte 0x800761C8

    # Entry 243
    # ID
    .4byte 266

    # Flags
    .4byte 0x00B20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DE76C
    .4byte 0x800DE78C
    .4byte 0x800DE790
    .4byte 0x800DE794
    .4byte 0x800761C8

    # Entry 244
    # ID
    .4byte 209

    # Flags
    .4byte 0x0080006F
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009A2A8
    .4byte 0x8009A2E4
    .4byte 0x8009A388
    .4byte 0x8009A3A8
    .4byte 0x800761C8

    # Entry 245
    # ID
    .4byte 210

    # Flags
    .4byte 0x00800000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009A468
    .4byte 0x8009A4A4
    .4byte 0x8009A5F4
    .4byte 0x8009A5F8
    .4byte 0x800761C8

    # Entry 246
    # ID
    .4byte 211

    # Flags
    .4byte 0x00880000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009A728
    .4byte 0x8009A72C
    .4byte 0x8009A74C
    .4byte 0x8009A750
    .4byte 0x800761C8

    # Entry 247
    # ID
    .4byte 212

    # Flags
    .4byte 0x0080006B
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C1B2C
    .4byte 0x800C1B64
    .4byte 0x800C1B84
    .4byte 0x800C1BA4
    .4byte 0x800761C8

    # Entry 248
    # ID
    .4byte 214

    # Flags
    .4byte 0x00800000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C1B2C
    .4byte 0x800C1B64
    .4byte 0x800C1B84
    .4byte 0x800C1BA4
    .4byte 0x800761C8

    # Entry 249
    # ID
    .4byte 213

    # Flags
    .4byte 0x0080006B
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009EF04
    .4byte 0x8009EF40
    .4byte 0x8009EF44
    .4byte 0x8009EF48
    .4byte 0x800761C8

    # Entry 250
    # ID
    .4byte 214

    # Flags
    .4byte 0x00800000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009F048
    .4byte 0x8009F0B8
    .4byte 0x8009F0BC
    .4byte 0x8009F0C0
    .4byte 0x800761C8

    # Entry 251
    # ID
    .4byte 215

    # Flags
    .4byte 0x00800000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009F400
    .4byte 0x8009F43C
    .4byte 0x8009F440
    .4byte 0x8009F460
    .4byte 0x800761C8

    # Entry 252
    # ID
    .4byte 216

    # Flags
    .4byte 0x00900070
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80081504
    .4byte 0x80081540
    .4byte 0x80081544
    .4byte 0x800815E4
    .4byte 0x80081644

    # Entry 253
    # ID
    .4byte 217

    # Flags
    .4byte 0x00980000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009A8D8
    .4byte 0x8009A8FC
    .4byte 0x8009A96C
    .4byte 0x8009A98C
    .4byte 0x80081644

    # Entry 254
    # ID
    .4byte 219

    # Flags
    .4byte 0x00900000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009AC68
    .4byte 0x8009ACA4
    .4byte 0x8009ACA8
    .4byte 0x8009ADA4
    .4byte 0x80081644

    # Entry 255
    # ID
    .4byte 220

    # Flags
    .4byte 0x00900000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009AC68
    .4byte 0x8009ACA4
    .4byte 0x8009ACA8
    .4byte 0x8009ADA4
    .4byte 0x80081644

    # Entry 256
    # ID
    .4byte 221

    # Flags
    .4byte 0x0094023E
    .4byte 0x3D000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009AF70
    .4byte 0x8009AF90
    .4byte 0x8009AF94
    .4byte 0x8009AFB4
    .4byte 0x80081644

    # Entry 257
    # ID
    .4byte 222

    # Flags
    .4byte 0x0024023F
    .4byte 0x3E000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009AF70
    .4byte 0x8009AF90
    .4byte 0x8009AF94
    .4byte 0x8009AFB4
    .4byte 0x80081644

    # Entry 258
    # ID
    .4byte 223

    # Flags
    .4byte 0x00900000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009B10C
    .4byte 0x8009B12C
    .4byte 0x8009B130
    .4byte 0x8009B150
    .4byte 0x80081644

    # Entry 259
    # ID
    .4byte 224

    # Flags
    .4byte 0x00900000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009B10C
    .4byte 0x8009B12C
    .4byte 0x8009B130
    .4byte 0x8009B150
    .4byte 0x80081644

    # Entry 260
    # ID
    .4byte 225

    # Flags
    .4byte 0x00900000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009B278
    .4byte 0x8009B2B4
    .4byte 0x8009B2B8
    .4byte 0x8009B2D8
    .4byte 0x800761C8

    # Entry 261
    # ID
    .4byte 226

    # Flags
    .4byte 0x00900000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009B424
    .4byte 0x8009B460
    .4byte 0x8009B464
    .4byte 0x8009B4A0
    .4byte 0x800761C8

    # Entry 262
    # ID
    .4byte 227

    # Flags
    .4byte 0x00900000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009B278
    .4byte 0x8009B2B4
    .4byte 0x8009B2B8
    .4byte 0x8009B2D8
    .4byte 0x800761C8

    # Entry 263
    # ID
    .4byte 228

    # Flags
    .4byte 0x00900000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009B424
    .4byte 0x8009B460
    .4byte 0x8009B464
    .4byte 0x8009B4A0
    .4byte 0x800761C8

    # Entry 264
    # ID
    .4byte 239

    # Flags
    .4byte 0x00000071
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DECF4
    .4byte 0x800DED30
    .4byte 0x800DEE44
    .4byte 0x800DEE64
    .4byte 0x800761C8

    # Entry 265
    # ID
    .4byte 240

    # Flags
    .4byte 0x00000071
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DECF4
    .4byte 0x800DED30
    .4byte 0x800DEE44
    .4byte 0x800DEE64
    .4byte 0x800761C8

    # Entry 266
    # ID
    .4byte 267

    # Flags
    .4byte 0x00B80000
    .4byte 0x01400000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009C830
    .4byte 0x8009CA00
    .4byte 0x8009CA04
    .4byte 0x8009CA08
    .4byte 0x800761C8

    # Entry 267
    # ID
    .4byte 268

    # Flags
    .4byte 0x00B80000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009C830
    .4byte 0x8009CA00
    .4byte 0x8009CA04
    .4byte 0x8009CA08
    .4byte 0x800761C8

    # Entry 268
    # ID
    .4byte 269

    # Flags
    .4byte 0x00B80000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009C830
    .4byte 0x8009CA00
    .4byte 0x8009CA04
    .4byte 0x8009CA08
    .4byte 0x800761C8

    # Entry 269
    # ID
    .4byte 270

    # Flags
    .4byte 0x00B80000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009C830
    .4byte 0x8009CA00
    .4byte 0x8009CA04
    .4byte 0x8009CA08
    .4byte 0x800761C8

    # Entry 270
    # ID
    .4byte 271

    # Flags
    .4byte 0x00B80000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009C830
    .4byte 0x8009CA00
    .4byte 0x8009CA04
    .4byte 0x8009CA08
    .4byte 0x800761C8

    # Entry 271
    # ID
    .4byte 272

    # Flags
    .4byte 0x00B20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DE69C
    .4byte 0x800DE6BC
    .4byte 0x800DE6C0
    .4byte 0x800DE6C4
    .4byte 0x800761C8

    # Entry 272
    # ID
    .4byte 273

    # Flags
    .4byte 0x00B20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DE6C8
    .4byte 0x800DE6E8
    .4byte 0x800DE6EC
    .4byte 0x800DE6F0
    .4byte 0x800761C8

    # Entry 273
    # ID
    .4byte 274

    # Flags
    .4byte 0x00B20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DE6F4
    .4byte 0x800DE714
    .4byte 0x800DE718
    .4byte 0x800DE71C
    .4byte 0x800761C8

    # Entry 274
    # ID
    .4byte 275

    # Flags
    .4byte 0x00B20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800DE76C
    .4byte 0x800DE78C
    .4byte 0x800DE790
    .4byte 0x800DE794
    .4byte 0x800761C8

    # Entry 275
    # ID
    .4byte 276

    # Flags
    .4byte 0x00B00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009CB04
    .4byte 0x8009CB08
    .4byte 0x8009CB0C
    .4byte 0x8009CB10
    .4byte 0x800761C8

    # Entry 276
    # ID
    .4byte 254

    # Flags
    .4byte 0x00B00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800BBC78
    .4byte 0x800BBC7C
    .4byte 0x800BBC80
    .4byte 0x800BBC84
    .4byte 0x800761C8

    # Entry 277
    # ID
    .4byte 277

    # Flags
    .4byte 0x00C00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800BC1B0
    .4byte 0x800BC304
    .4byte 0x800BC308
    .4byte 0x800BC340
    .4byte 0x800761C8

    # Entry 278
    # ID
    .4byte -1

    # Flags
    .4byte 0x00B00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800BC8C4
    .4byte 0x800BC8C8
    .4byte 0x800BC8CC
    .4byte 0x800BC8D0
    .4byte 0x800761C8

    # Entry 279
    # ID
    .4byte 278

    # Flags
    .4byte 0x00B20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800BCA54
    .4byte 0x800BCAE8
    .4byte 0x800BCAEC
    .4byte 0x800BCAF0
    .4byte 0x800761C8

    # Entry 280
    # ID
    .4byte -1

    # Flags
    .4byte 0x00B00000
    .4byte 0x01400000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800BCC7C
    .4byte 0x800BCCF4
    .4byte 0x800BCCF8
    .4byte 0x800BCCFC
    .4byte 0x800761C8

    # Entry 281
    # ID
    .4byte 279

    # Flags
    .4byte 0x00B20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800BCED8
    .4byte 0x800BCEDC
    .4byte 0x800BCEE0
    .4byte 0x800BCEE4
    .4byte 0x800761C8

    # Entry 282
    # ID
    .4byte 280

    # Flags
    .4byte 0x00B20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800BCEE8
    .4byte 0x800BCEEC
    .4byte 0x800BCEF0
    .4byte 0x800BCEF4
    .4byte 0x800761C8

    # Entry 283
    # ID
    .4byte -1

    # Flags
    .4byte 0x00B00400
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800BC9B8
    .4byte 0x800BC9BC
    .4byte 0x800BC9C0
    .4byte 0x800BC9C4
    .4byte 0x800761C8

    # Entry 284
    # ID
    .4byte 281

    # Flags
    .4byte 0x00B20400
    .4byte 0x01400000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800BCB80
    .4byte 0x800BCC14
    .4byte 0x800BCC18
    .4byte 0x800BCC1C
    .4byte 0x800761C8

    # Entry 285
    # ID
    .4byte -1

    # Flags
    .4byte 0x00B00400
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800BCD5C
    .4byte 0x800BCDD4
    .4byte 0x800BCDD8
    .4byte 0x800BCDDC
    .4byte 0x800761C8

    # Entry 286
    # ID
    .4byte 282

    # Flags
    .4byte 0x00B20400
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800BCEF8
    .4byte 0x800BCEFC
    .4byte 0x800BCF00
    .4byte 0x800BCF04
    .4byte 0x800761C8

    # Entry 287
    # ID
    .4byte 283

    # Flags
    .4byte 0x00B20400
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800BCF08
    .4byte 0x800BCF0C
    .4byte 0x800BCF10
    .4byte 0x800BCF14
    .4byte 0x800761C8

    # Entry 288
    # ID
    .4byte 29

    # Flags
    .4byte 0x00B00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800BD38C
    .4byte 0x800BD390
    .4byte 0x800BD394
    .4byte 0x800BD398
    .4byte 0x800761C8

    # Entry 289
    # ID
    .4byte -1

    # Flags
    .4byte 0x00B00000
    .4byte 0x01400000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800BD6E8
    .4byte 0x800BD7BC
    .4byte 0x800BD9D8
    .4byte 0x800BD9DC
    .4byte 0x800761C8

    # Entry 290
    # ID
    .4byte 285

    # Flags
    .4byte 0x00C20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800BDDC4
    .4byte 0x800BDDC8
    .4byte 0x800BDDCC
    .4byte 0x800BDF10
    .4byte 0x800761C8

    # Entry 291
    # ID
    .4byte 284

    # Flags
    .4byte 0x00C20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800BE258
    .4byte 0x800BE25C
    .4byte 0x800BE260
    .4byte 0x800BE3A4
    .4byte 0x800761C8

    # Entry 292
    # ID
    .4byte 29

    # Flags
    .4byte 0x00B20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800BE618
    .4byte 0x800BE61C
    .4byte 0x800BE620
    .4byte 0x800BE6A8
    .4byte 0x800761C8

    # Entry 293
    # ID
    .4byte -1

    # Flags
    .4byte 0x00C00000
    .4byte 0x01400000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8009EC08
    .4byte 0x8009EC0C
    .4byte 0x8009EC3C
    .4byte 0x8009EC40
    .4byte 0x800761C8

    # Entry 294
    # ID
    .4byte -1

    # Flags
    .4byte 0x00C00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C0F34
    .4byte 0x800C0FC8
    .4byte 0x800C1194
    .4byte 0x800C11E4
    .4byte 0x800761C8

    # Entry 295
    # ID
    .4byte -1

    # Flags
    .4byte 0x00C00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C12D8
    .4byte 0x800C134C
    .4byte 0x800C1350
    .4byte 0x800C1354
    .4byte 0x800761C8

    # Entry 296
    # ID
    .4byte 16

    # Flags
    .4byte 0x00000000
    .4byte 0x01800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C1460
    .4byte 0x800C14B0
    .4byte 0x800C1574
    .4byte 0x800C15B4
    .4byte 0x800761C8

    # Entry 297
    # ID
    .4byte 206

    # Flags
    .4byte 0x00C00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C32AC
    .4byte 0x800C334C
    .4byte 0x800C3350
    .4byte 0x800C3370
    .4byte 0x800761C8

    # Entry 298
    # ID
    .4byte 207

    # Flags
    .4byte 0x00C00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C33C8
    .4byte 0x800C343C
    .4byte 0x800C3440
    .4byte 0x800C3460
    .4byte 0x800761C8

    # Entry 299
    # ID
    .4byte 208

    # Flags
    .4byte 0x00C00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C34B8
    .4byte 0x800C34F4
    .4byte 0x800C34F8
    .4byte 0x800C3518
    .4byte 0x800761C8

    # Entry 300
    # ID
    .4byte 205

    # Flags
    .4byte 0x00500000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C466C
    .4byte 0x800C46E0
    .4byte 0x800C46E4
    .4byte 0x800C4704
    .4byte 0x800761C8

    # Entry 301
    # ID
    .4byte -1

    # Flags
    .4byte 0x00B00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x800761C8

    # Entry 302
    # ID
    .4byte -1

    # Flags
    .4byte 0x00B00400
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x800761C8

    # Entry 303
    # ID
    .4byte 292

    # Flags
    .4byte 0x00B20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800BD17C
    .4byte 0x800BD180
    .4byte 0x800BD184
    .4byte 0x800BD188
    .4byte 0x800761C8

    # Entry 304
    # ID
    .4byte 293

    # Flags
    .4byte 0x00B20400
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800BD18C
    .4byte 0x800BD190
    .4byte 0x800BD194
    .4byte 0x800BD198
    .4byte 0x800761C8

    # Entry 305
    # ID
    .4byte 30

    # Flags
    .4byte 0x00C00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C4900
    .4byte 0x800C4964
    .4byte 0x800C4968
    .4byte 0x800C4A14
    .4byte 0x800C4A18

    # Entry 306
    # ID
    .4byte 31

    # Flags
    .4byte 0x0044005F
    .4byte 0x5E000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C4BA4
    .4byte 0x800C4BA8
    .4byte 0x800C4BAC
    .4byte 0x800C4C30
    .4byte 0x800C4E2C

    # Entry 307
    # ID
    .4byte 132

    # Flags
    .4byte 0x0044005E
    .4byte 0x5DC00000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C4FEC
    .4byte 0x800C5074
    .4byte 0x800C50D4
    .4byte 0x800C50F4
    .4byte 0x800761C8

    # Entry 308
    # ID
    .4byte 133

    # Flags
    .4byte 0x0044405E
    .4byte 0x5D800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C56BC
    .4byte 0x800C56DC
    .4byte 0x800C572C
    .4byte 0x800C574C
    .4byte 0x800761C8

    # Entry 309
    # ID
    .4byte 133

    # Flags
    .4byte 0x0044205E
    .4byte 0x5D800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C5848
    .4byte 0x800C59EC
    .4byte 0x800C5A10
    .4byte 0x800C5A30
    .4byte 0x800761C8

    # Entry 310
    # ID
    .4byte 133

    # Flags
    .4byte 0x0044005E
    .4byte 0x5D800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C5C10
    .4byte 0x800C5C74
    .4byte 0x800C5C94
    .4byte 0x800C5CB4
    .4byte 0x800761C8

    # Entry 311
    # ID
    .4byte 133

    # Flags
    .4byte 0x0044045E
    .4byte 0x5D800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C5DBC
    .4byte 0x800C5E94
    .4byte 0x800C5F40
    .4byte 0x800C5F60
    .4byte 0x800761C8

    # Entry 312
    # ID
    .4byte 133

    # Flags
    .4byte 0x0044845E
    .4byte 0x5D800000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C5B24
    .4byte 0x800C5B44
    .4byte 0x800C5B48
    .4byte 0x800C5B68
    .4byte 0x800761C8

    # Entry 313
    # ID
    .4byte 133

    # Flags
    .4byte 0x0044005E
    .4byte 0x5D400000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C6020
    .4byte 0x800C6084
    .4byte 0x800C6088
    .4byte 0x800C60A8
    .4byte 0x800761C8

    # Entry 314
    # ID
    .4byte -1

    # Flags
    .4byte 0x00400000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D1868
    .4byte NULL
    .4byte NULL
    .4byte 0x800D18A4
    .4byte 0x800761C8

    # Entry 315
    # ID
    .4byte -1

    # Flags
    .4byte 0x00400000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D1A28
    .4byte NULL
    .4byte NULL
    .4byte 0x800D1A64
    .4byte 0x800761C8

    # Entry 316
    # ID
    .4byte -1

    # Flags
    .4byte 0x00400000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D1CAC
    .4byte NULL
    .4byte NULL
    .4byte 0x800D1CE8
    .4byte 0x800761C8

    # Entry 317
    # ID
    .4byte -1

    # Flags
    .4byte 0x00400000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D1E1C
    .4byte NULL
    .4byte NULL
    .4byte 0x800D1E58
    .4byte 0x800761C8

    # Entry 318
    # ID
    .4byte -1

    # Flags
    .4byte 0x00400000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D2158
    .4byte NULL
    .4byte NULL
    .4byte 0x800D2194
    .4byte 0x800761C8

    # Entry 319
    # ID
    .4byte -1

    # Flags
    .4byte 0x00400000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D2318
    .4byte NULL
    .4byte NULL
    .4byte 0x800D2354
    .4byte 0x800761C8

    # Entry 320
    # ID
    .4byte -1

    # Flags
    .4byte 0x00400000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D259C
    .4byte NULL
    .4byte NULL
    .4byte 0x800D25D8
    .4byte 0x800761C8

    # Entry 321
    # ID
    .4byte -1

    # Flags
    .4byte 0x00400000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800D270C
    .4byte NULL
    .4byte NULL
    .4byte 0x800D2748
    .4byte 0x800761C8

    # Entry 322
    # ID
    .4byte -1

    # Flags
    .4byte 0x00C00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C6370
    .4byte 0x800C63B4
    .4byte 0x800C63B8
    .4byte 0x800C6404
    .4byte 0x800761C8

    # Entry 323
    # ID
    .4byte 238

    # Flags
    .4byte 0x00C00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C6700
    .4byte 0x800C673C
    .4byte 0x800C6740
    .4byte 0x800C6950
    .4byte 0x800761C8

    # Entry 324
    # ID
    .4byte -1

    # Flags
    .4byte 0x00C00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C6CC8
    .4byte 0x800C6D34
    .4byte 0x800C6D38
    .4byte 0x800C6E90
    .4byte 0x800761C8

    # Entry 325
    # ID
    .4byte -1

    # Flags
    .4byte 0x00520000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800912A8
    .4byte 0x800913DC
    .4byte 0x800913E0
    .4byte 0x8009144C
    .4byte 0x800761C8

    # Entry 326
    # ID
    .4byte 20

    # Flags
    .4byte 0x00000000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80091988
    .4byte 0x800919D8
    .4byte 0x800919DC
    .4byte 0x800919FC
    .4byte 0x800761C8

    # Entry 327
    # ID
    .4byte -1

    # Flags
    .4byte 0x00B00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80155B70
    .4byte 0x80155B74
    .4byte 0x80155B78
    .4byte 0x80155B7C
    .4byte 0x800761C8

    # Entry 328
    # ID
    .4byte -1

    # Flags
    .4byte 0x00B20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80155C20
    .4byte 0x80155C88
    .4byte 0x80155C8C
    .4byte 0x80155C90
    .4byte 0x800761C8

    # Entry 329
    # ID
    .4byte -1

    # Flags
    .4byte 0x00B00000
    .4byte 0x01400000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80155D5C
    .4byte 0x80155D60
    .4byte 0x80155D64
    .4byte 0x80155D68
    .4byte 0x800761C8

    # Entry 330
    # ID
    .4byte -1

    # Flags
    .4byte 0x00B20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x80155E08
    .4byte 0x80155E0C
    .4byte 0x80155E10
    .4byte 0x80155E14
    .4byte 0x800761C8

    # Entry 331
    # ID
    .4byte 254

    # Flags
    .4byte 0x00B00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8010AA1C
    .4byte 0x8010AA20
    .4byte 0x8010AA24
    .4byte 0x8010AA28
    .4byte 0x800761C8

    # Entry 332
    # ID
    .4byte 294

    # Flags
    .4byte 0x00C00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8010AF54
    .4byte 0x8010B0A0
    .4byte 0x8010B0A4
    .4byte 0x8010B0DC
    .4byte 0x800761C8

    # Entry 333
    # ID
    .4byte -1

    # Flags
    .4byte 0x00B00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C7734
    .4byte 0x800C77B0
    .4byte 0x800C77B4
    .4byte 0x800C77B8
    .4byte 0x800761C8

    # Entry 334
    # ID
    .4byte -1

    # Flags
    .4byte 0x00C00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C7A58
    .4byte 0x800C7AD4
    .4byte 0x800C7AD8
    .4byte 0x800C7ADC
    .4byte 0x800761C8

    # Entry 335
    # ID
    .4byte 212

    # Flags
    .4byte 0x00800000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C7FC8
    .4byte 0x800C8004
    .4byte 0x800C8008
    .4byte 0x800C8028
    .4byte 0x800761C8

    # Entry 336
    # ID
    .4byte -1

    # Flags
    .4byte 0x00B00000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8015B660
    .4byte 0x8015B664
    .4byte 0x8015B668
    .4byte 0x8015B66C
    .4byte 0x800761C8

    # Entry 337
    # ID
    .4byte -1

    # Flags
    .4byte 0x00B20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8015B704
    .4byte 0x8015B76C
    .4byte 0x8015B770
    .4byte 0x8015B774
    .4byte 0x800761C8

    # Entry 338
    # ID
    .4byte -1

    # Flags
    .4byte 0x00B00000
    .4byte 0x01400000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8015B840
    .4byte 0x8015B844
    .4byte 0x8015B848
    .4byte 0x8015B84C
    .4byte 0x800761C8

    # Entry 339
    # ID
    .4byte -1

    # Flags
    .4byte 0x00B20000
    .4byte 0x01000000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x8015B8EC
    .4byte 0x8015B8F0
    .4byte 0x8015B8F4
    .4byte 0x8015B8F8
    .4byte 0x800761C8

    # Entry 340
    # ID
    .4byte -1

    # Flags
    .4byte 0x00C00000
    .4byte 0x01400000

    # Functions (Anim, Input, Action, Collision, Camera)
    .4byte 0x800C91C0
    .4byte 0x800C9208
    .4byte 0x800C925C
    .4byte 0x800C9260
    .4byte 0x800761C8

.global lbl_803C52A0
lbl_803C52A0:
	.incbin "baserom.dol", 0x3C22A0, 0x1C0
.global lbl_803C5460
lbl_803C5460:
    .asciz "itGetKind(item_gobj) == It_Kind_MetalB"
    .balign 4
.global lbl_803C5488
lbl_803C5488:
    .asciz "fp->ground_or_air == GA_Ground"
    .balign 4
.global lbl_803C54A8
lbl_803C54A8:
    .asciz "wait anim data illegal!!\n"
    .balign 4
.global lbl_803C54C4
lbl_803C54C4:
    .asciz "ftwaitanim.c"
    .balign 4
    .incbin "baserom.dol", 0x3C24D4, 0x4
.global jtbl_803C54D8
jtbl_803C54D8:
	.incbin "baserom.dol", 0x3C24D8, 0x48
.global lbl_803C5520
lbl_803C5520:
	.incbin "baserom.dol", 0x3C2520, 0x60
.global lbl_803C5580
lbl_803C5580:
    .asciz "ftGetImmItem item_gobj is NULL!!\n"
    .balign 4
    .asciz "ftpickupitem.c"
    .balign 4
    .asciz "item_gobj"
    .balign 4
.global jtbl_803C55C0
jtbl_803C55C0:
	.incbin "baserom.dol", 0x3C25C0, 0x5C
.global jtbl_803C561C
jtbl_803C561C:
	.incbin "baserom.dol", 0x3C261C, 0x5C
.global jtbl_803C5678
jtbl_803C5678:
	.incbin "baserom.dol", 0x3C2678, 0x60
.global lbl_803C56D8
lbl_803C56D8:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803C5700
lbl_803C5700:
	.incbin "baserom.dol", 0x3C2700, 0x10
.global lbl_803C5710
lbl_803C5710:
    .asciz "A`"
    .balign 4
    .incbin "baserom.dol", 0x3C2714, 0xC
.global lbl_803C5720
lbl_803C5720:
    .asciz "translate"
    .balign 4
.global lbl_803C572C
lbl_803C572C:
    .asciz "fighter dynamics num over!\n"
    .balign 4
.global lbl_803C5748
lbl_803C5748:
    .asciz "ftdynamics.c"
    .balign 4
    .asciz "fp->dynamics_num < Ft_Dynamics_NumMax"
    .balign 4
    .incbin "baserom.dol", 0x3C2780, 0x14
.global lbl_803C5794
lbl_803C5794:
	.incbin "baserom.dol", 0x3C2794, 0x1C
.global lbl_803C57B0
lbl_803C57B0:
    .asciz "no effect from animlist %d\n"
    .balign 4
    .incbin "baserom.dol", 0x3C27CC, 0x254
.global lbl_803C5A20
lbl_803C5A20:
	.incbin "baserom.dol", 0x3C2A20, 0x48
.global lbl_803C5A68
lbl_803C5A68:
	.incbin "baserom.dol", 0x3C2A68, 0x8C
.global jtbl_803C5AF4
jtbl_803C5AF4:
	.incbin "baserom.dol", 0x3C2AF4, 0x68
.global jtbl_803C5B5C
jtbl_803C5B5C:
	.incbin "baserom.dol", 0x3C2B5C, 0x8C
.global jtbl_803C5BE8
jtbl_803C5BE8:
	.incbin "baserom.dol", 0x3C2BE8, 0x28
.global jtbl_803C5C10
jtbl_803C5C10:
	.incbin "baserom.dol", 0x3C2C10, 0x60
.global jtbl_803C5C70
jtbl_803C5C70:
	.incbin "baserom.dol", 0x3C2C70, 0x28
.global jtbl_803C5C98
jtbl_803C5C98:
	.incbin "baserom.dol", 0x3C2C98, 0x50
.global jtbl_803C5CE8
jtbl_803C5CE8:
	.incbin "baserom.dol", 0x3C2CE8, 0x78
.global jtbl_803C5D60
jtbl_803C5D60:
	.incbin "baserom.dol", 0x3C2D60, 0x50
.global lbl_803C5DB0
lbl_803C5DB0:
    .asciz "csP is bad address\n"
    .balign 4
.global lbl_803C5DC4
lbl_803C5DC4:
    .asciz "ftcmdscript.c"
    .balign 4
.global lbl_803C5DD4
lbl_803C5DD4:
	.incbin "baserom.dol", 0x3C2DD4, 0x30C
.global lbl_803C60E0
lbl_803C60E0:
    .asciz "command script buffer over flow!\n"
    .balign 4
    .incbin "baserom.dol", 0x3C3104, 0x4
.global lbl_803C6108
lbl_803C6108:
    .asciz "ftcpuattack.c"
    .balign 4
.global jtbl_803C6118
jtbl_803C6118:
	.incbin "baserom.dol", 0x3C3118, 0x24
.global jtbl_803C613C
jtbl_803C613C:
	.incbin "baserom.dol", 0x3C313C, 0x80
.global jtbl_803C61BC
jtbl_803C61BC:
	.incbin "baserom.dol", 0x3C31BC, 0x3D8
.global lbl_803C6594
lbl_803C6594:
	.incbin "baserom.dol", 0x3C3594, 0x374
.global lbl_803C6908
lbl_803C6908:
	.incbin "baserom.dol", 0x3C3908, 0x40
.global lbl_803C6948
lbl_803C6948:
	.incbin "baserom.dol", 0x3C3948, 0x14
.global lbl_803C695C
lbl_803C695C:
    .asciz "no demo vi anim! %d\n"
    .balign 4
.global lbl_803C6974
lbl_803C6974:
    .asciz "ftdemo.c"
    .balign 4
.global lbl_803C6980
lbl_803C6980:
	.incbin "baserom.dol", 0x3C3980, 0x150
.global lbl_803C6AD0
lbl_803C6AD0:
	.incbin "baserom.dol", 0x3C3AD0, 0xC
.global lbl_803C6ADC
lbl_803C6ADC:
	.incbin "baserom.dol", 0x3C3ADC, 0xC
.global lbl_803C6AE8
lbl_803C6AE8:
    .asciz "don't reset spycloak colanim!\n"
    .balign 4
.global lbl_803C6B08
lbl_803C6B08:
    .asciz "ftcolanimlist.c"
    .balign 4
.global lbl_803C6B18
lbl_803C6B18:
    .asciz "fighter chk device wind func num over!\n"
    .balign 4
.global lbl_803C6B40
lbl_803C6B40:
    .asciz "ftdevice.c"
    .balign 4
.global lbl_803C6B4C
lbl_803C6B4C:
    .asciz "fighter chk device catch func num over!\n"
    .balign 4
.global lbl_803C6B78
lbl_803C6B78:
    .asciz "fighter chk device coll func num over!\n"
    .balign 4
.global lbl_803C6BA0
lbl_803C6BA0:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803C6BC8
lbl_803C6BC8:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3C3BD4, 0x4
.global lbl_803C6BD8
lbl_803C6BD8:
    .asciz "no afterimage item!\n"
    .balign 4
.global lbl_803C6BF0
lbl_803C6BF0:
    .asciz "ftafterimage.c"
    .balign 4
.global jtbl_803C6C00
jtbl_803C6C00:
	.incbin "baserom.dol", 0x3C3C00, 0x54
.global jtbl_803C6C54
jtbl_803C6C54:
	.incbin "baserom.dol", 0x3C3C54, 0x54
.global lbl_803C6CA8
lbl_803C6CA8:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803C6CD0
lbl_803C6CD0:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803C6CF8
lbl_803C6CF8:
    .asciz "mobj has unexpected blending flags (0x%x)."
    .balign 4
.global lbl_803C6D24
lbl_803C6D24:
    .asciz "ftmetal.c"
    .balign 4
    .asciz "fighter parts model dobj num over!\n"
    .balign 4
    .asciz "fighter dobj num over!\n"
    .balign 4
    .incbin "baserom.dol", 0x3C3D6C, 0x4
.global lbl_803C6D70
lbl_803C6D70:
	.incbin "baserom.dol", 0x3C3D70, 0x78
.global lbl_803C6DE8
lbl_803C6DE8:
    .asciz "ellegal swing item!!!\n"
    .balign 4
.global lbl_803C6E00
lbl_803C6E00:
    .asciz "ftswing.c"
    .balign 4
.global jtbl_803C6E0C
jtbl_803C6E0C:
	.incbin "baserom.dol", 0x3C3E0C, 0x70
.global jtbl_803C6E7C
jtbl_803C6E7C:
	.incbin "baserom.dol", 0x3C3E7C, 0x3C
.global lbl_803C6EB8
lbl_803C6EB8:
    .asciz "ftstarrodswing.c"
    .balign 4
.global lbl_803C6ECC
lbl_803C6ECC:
    .asciz "itGetKind(fp->item_gobj) == It_Kind_StarRod"
    .balign 4
.global lbl_803C6EF8
lbl_803C6EF8:
    .asciz "ftlipstickswing.c"
    .balign 4
.global lbl_803C6F0C
lbl_803C6F0C:
    .asciz "itGetKind(fp->item_gobj) == It_Kind_LipStick"
    .balign 4
    .incbin "baserom.dol", 0x3C3F3C, 0x4
.global lbl_803C6F40
lbl_803C6F40:
    .asciz "don't have smash42 motion!!!\n"
    .balign 4
.global lbl_803C6F60
lbl_803C6F60:
    .asciz "ftattacks4combo.c"
    .balign 4
    .incbin "baserom.dol", 0x3C3F74, 0x4
.global lbl_803C6F78
lbl_803C6F78:
    .asciz "ftchangeparam.c"
    .balign 4
.global lbl_803C6F88
lbl_803C6F88:
    .asciz "scale != 0.0F"
    .balign 4
    .asciz "don't set ftKindCalcIndiviParamTable!!\n"
    .balign 4
    .asciz "ftKindCalcIndiviParamTable[fp->kind] != NULL"
    .balign 4
.global lbl_803C6FF0
lbl_803C6FF0:
	.incbin "baserom.dol", 0x3C3FF0, 0x40
.global jtbl_803C7030
jtbl_803C7030:
	.incbin "baserom.dol", 0x3C4030, 0x70
.global lbl_803C70A0
lbl_803C70A0:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3C40AC, 0x4
.global lbl_803C70B0
lbl_803C70B0:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3C40BC, 0x4
.global lbl_803C70C0
lbl_803C70C0:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3C40CC, 0x4
.global lbl_803C70D0
lbl_803C70D0:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3C40DC, 0x4
.global lbl_803C70E0
lbl_803C70E0:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3C40EC, 0x4
.global lbl_803C70F0
lbl_803C70F0:
    .asciz "couldn't get walk frame\n"
    .balign 4
.global lbl_803C710C
lbl_803C710C:
    .asciz "ftwalkcommon.c"
    .balign 4
    .incbin "baserom.dol", 0x3C411C, 0x184
.global lbl_803C72A0
lbl_803C72A0:
    .asciz "A@"
    .balign 4
    .incbin "baserom.dol", 0x3C42A4, 0xB2C
.global lbl_803C7DD0
lbl_803C7DD0:
	.incbin "baserom.dol", 0x3C4DD0, 0x18
.global lbl_803C7DE8
lbl_803C7DE8:
    .asciz "ftToSpecialNFox::Caution!!!\n"
    .balign 4
.global lbl_803C7E08
lbl_803C7E08:
    .asciz "ftfoxspecialn.c"
    .balign 4
    .incbin "baserom.dol", 0x3C4E18, 0x550
.global as_table_kirby
as_table_kirby:
	.incbin "baserom.dol", 0x3C5368, 0x1960
.global lbl_803C9CC8
lbl_803C9CC8:
	.incbin "baserom.dol", 0x3C6CC8, 0x108
.global lbl_803C9DD0
lbl_803C9DD0:
	.incbin "baserom.dol", 0x3C6DD0, 0x84
.global lbl_803C9E54
lbl_803C9E54:
	.incbin "baserom.dol", 0x3C6E54, 0x174
.global lbl_803C9FC8
lbl_803C9FC8:
	.incbin "baserom.dol", 0x3C6FC8, 0x104
.global jtbl_803CA0CC
jtbl_803CA0CC:
	.incbin "baserom.dol", 0x3C70CC, 0x80
.global jtbl_803CA14C
jtbl_803CA14C:
	.incbin "baserom.dol", 0x3C714C, 0x80
.global jtbl_803CA1CC
jtbl_803CA1CC:
	.incbin "baserom.dol", 0x3C71CC, 0x64
.global jtbl_803CA230
jtbl_803CA230:
	.incbin "baserom.dol", 0x3C7230, 0x64
.global jtbl_803CA294
jtbl_803CA294:
	.incbin "baserom.dol", 0x3C7294, 0x38
.global jtbl_803CA2CC
jtbl_803CA2CC:
	.incbin "baserom.dol", 0x3C72CC, 0x2D8
.global lbl_803CA5A4
lbl_803CA5A4:
	.incbin "baserom.dol", 0x3C75A4, 0x42C
.global lbl_803CA9D0
lbl_803CA9D0:
	.incbin "baserom.dol", 0x3C79D0, 0xA18
.global lbl_803CB3E8
lbl_803CB3E8:
	.incbin "baserom.dol", 0x3C83E8, 0x84
.global lbl_803CB46C
lbl_803CB46C:
	.incbin "baserom.dol", 0x3C846C, 0x24
.global lbl_803CB490
lbl_803CB490:
	.incbin "baserom.dol", 0x3C8490, 0x5C
.global lbl_803CB4EC
lbl_803CB4EC:
	.incbin "baserom.dol", 0x3C84EC, 0x24
.global lbl_803CB510
lbl_803CB510:
    .asciz "Other Dead_Proc Existence"
    .balign 4
.global lbl_803CB52C
lbl_803CB52C:
    .asciz "ftkirbyspecials.c"
    .balign 4
.global lbl_803CB540
lbl_803CB540:
	.incbin "baserom.dol", 0x3C8540, 0x180
.global lbl_803CB6C0
lbl_803CB6C0:
	.incbin "baserom.dol", 0x3C86C0, 0x18
.global lbl_803CB6D8
lbl_803CB6D8:
    .asciz "ftToSpecialNFox::Caution!!!\n"
    .balign 4
.global lbl_803CB6F8
lbl_803CB6F8:
    .asciz "ftkirbyspecialfox.c"
    .balign 4
    .incbin "baserom.dol", 0x3C870C, 0x4
.global lbl_803CB710
lbl_803CB710:
	.incbin "baserom.dol", 0x3C8710, 0x10
.global lbl_803CB720
lbl_803CB720:
	.incbin "baserom.dol", 0x3C8720, 0x38
.global lbl_803CB758
lbl_803CB758:
	.incbin "baserom.dol", 0x3C8758, 0x18
.global lbl_803CB770
lbl_803CB770:
	.incbin "baserom.dol", 0x3C8770, 0x24
.global jtbl_803CB794
jtbl_803CB794:
	.incbin "baserom.dol", 0x3C8794, 0x48
.global jtbl_803CB7DC
jtbl_803CB7DC:
	.incbin "baserom.dol", 0x3C87DC, 0x4C
.global lbl_803CB828
lbl_803CB828:
	.incbin "baserom.dol", 0x3C8828, 0xD70
.global lbl_803CC598
lbl_803CC598:
	.incbin "baserom.dol", 0x3C9598, 0x24
.global jtbl_803CC5BC
jtbl_803CC5BC:
	.incbin "baserom.dol", 0x3C95BC, 0x48
.global jtbl_803CC604
jtbl_803CC604:
	.incbin "baserom.dol", 0x3C9604, 0x11F4
.global lbl_803CD7F8
lbl_803CD7F8:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803CD820
lbl_803CD820:
	.incbin "baserom.dol", 0x3CA820, 0x540
.global lbl_803CDD60
lbl_803CDD60:
	.incbin "baserom.dol", 0x3CAD60, 0x958
.global lbl_803CE6B8
lbl_803CE6B8:
	.incbin "baserom.dol", 0x3CB6B8, 0x398
.global lbl_803CEA50
lbl_803CEA50:
    .asciz "yoshi matanim frame not same\n"
    .balign 4
.global lbl_803CEA70
lbl_803CEA70:
    .asciz "ftyoshi.c"
    .balign 4
.global lbl_803CEA7C
lbl_803CEA7C:
    .asciz "yoshi parts_model NULL!!\n"
    .balign 4
    .asciz "PlYs.dat"
    .balign 4
    .asciz "ftDataYoshi"
    .balign 4
    .asciz "PlYsNr.dat"
    .balign 4
    .asciz "PlyYoshi5K_Share_joint"
    .balign 4
    .asciz "PlyYoshi5K_Share_matanim_joint"
    .balign 4
    .asciz "PlYsRe.dat"
    .balign 4
    .asciz "PlyYoshi5KRe_Share_joint"
    .balign 4
    .asciz "PlyYoshi5KRe_Share_matanim_joint"
    .balign 4
    .asciz "PlYsBu.dat"
    .balign 4
    .asciz "PlyYoshi5KBu_Share_joint"
    .balign 4
    .asciz "PlyYoshi5KBu_Share_matanim_joint"
    .balign 4
    .asciz "PlYsYe.dat"
    .balign 4
    .asciz "PlyYoshi5KYe_Share_joint"
    .balign 4
    .asciz "PlyYoshi5KYe_Share_matanim_joint"
    .balign 4
    .asciz "PlYsPi.dat"
    .balign 4
    .asciz "PlyYoshi5KPi_Share_joint"
    .balign 4
    .asciz "PlyYoshi5KPi_Share_matanim_joint"
    .balign 4
    .asciz "PlYsAq.dat"
    .balign 4
    .asciz "PlyYoshi5KAq_Share_joint"
    .balign 4
    .asciz "PlyYoshi5KAq_Share_matanim_joint"
    .balign 4
    .asciz "PlYsAJ.dat"
    .balign 4
    .asciz "ftDemoResultMotionFileYoshi"
    .balign 4
    .asciz "ftDemoIntroMotionFileYoshi"
    .balign 4
    .asciz "ftDemoEndingMotionFileYoshi"
    .balign 4
    .asciz "ftDemoViWaitMotionFileYoshi"
    .balign 4
    .incbin "baserom.dol", 0x3CBCEC, 0x5C
.global lbl_803CED48
lbl_803CED48:
	.incbin "baserom.dol", 0x3CBD48, 0x3C
.global lbl_803CED84
lbl_803CED84:
	.incbin "baserom.dol", 0x3CBD84, 0x10
.global lbl_803CED94
lbl_803CED94:
	.incbin "baserom.dol", 0x3CBD94, 0x10
.global lbl_803CEDA4
lbl_803CEDA4:
	.incbin "baserom.dol", 0x3CBDA4, 0x4FC
.global lbl_803CF2A0
lbl_803CF2A0:
	.incbin "baserom.dol", 0x3CC2A0, 0x1314
.global lbl_803D05B4
lbl_803D05B4:
	.incbin "baserom.dol", 0x3CD5B4, 0x14
.global lbl_803D05C8
lbl_803D05C8:
	.incbin "baserom.dol", 0x3CD5C8, 0x10
.global lbl_803D05D8
lbl_803D05D8:
	.incbin "baserom.dol", 0x3CD5D8, 0x38
.global lbl_803D0610
lbl_803D0610:
	.incbin "baserom.dol", 0x3CD610, 0x49C
.global lbl_803D0AAC
lbl_803D0AAC:
	.incbin "baserom.dol", 0x3CDAAC, 0x3C
.global lbl_803D0AE8
lbl_803D0AE8:
	.incbin "baserom.dol", 0x3CDAE8, 0x4A8
.global lbl_803D0F90
lbl_803D0F90:
	.incbin "baserom.dol", 0x3CDF90, 0x29F4
.global lbl_803D3984
lbl_803D3984:
	.incbin "baserom.dol", 0x3D0984, 0x74C
.global lbl_803D40D0
lbl_803D40D0:
	.incbin "baserom.dol", 0x3D10D0, 0x74
.global jtbl_803D4144
jtbl_803D4144:
	.incbin "baserom.dol", 0x3D1144, 0x8C
.global jtbl_803D41D0
jtbl_803D41D0:
	.incbin "baserom.dol", 0x3D11D0, 0x6A8
.global lbl_803D4878
lbl_803D4878:
	.incbin "baserom.dol", 0x3D1878, 0x88
.global jtbl_803D4900
jtbl_803D4900:
	.incbin "baserom.dol", 0x3D1900, 0x98
.global jtbl_803D4998
jtbl_803D4998:
	.incbin "baserom.dol", 0x3D1998, 0x28
.global lbl_803D49C0
lbl_803D49C0:
    .asciz "boss is human or boss!\n"
    .balign 4
    .asciz "ftbosslib.c"
    .balign 4
    .asciz "kind == Gm_PKind_Human || kind == Gm_PKind_Boss || kind == Gm_PKind_Cpu"
    .balign 4
.global jtbl_803D4A2C
jtbl_803D4A2C:
	.incbin "baserom.dol", 0x3D1A2C, 0x1C
.global lbl_803D4A48
lbl_803D4A48:
	.incbin "baserom.dol", 0x3D1A48, 0x18
.global lbl_803D4A60
lbl_803D4A60:
	.incbin "baserom.dol", 0x3D1A60, 0x20
.global lbl_803D4A80
lbl_803D4A80:
	.incbin "baserom.dol", 0x3D1A80, 0x3C
.global lbl_803D4ABC
lbl_803D4ABC:
    .asciz "/usa.ini"
    .balign 4
.global lbl_803D4AC8
lbl_803D4AC8:
    .asciz "/develop.ini"
    .balign 4
    .asciz "gmmain.c"
    .balign 4
    .asciz "DbLevel == DbLKind_NoDebugRom"
    .balign 4
    .asciz "Data %lx\n"
    .balign 4
    .asciz "please setup server for USB\n"
    .balign 4
    .asciz "# ---------------------------------------------\n"
    .balign 4
    .asciz "#    Super Smash Bros. Melee\n"
    .balign 4
    .asciz "# Distribution %d\n"
    .balign 4
    .asciz "# Language %d\n"
    .balign 4
    .asciz "# DbLevel %d\n"
    .balign 4
    .asciz "# Arena Size %d MB\n"
    .balign 4
    .asciz "# ARAM Free Size %d MB\n"
    .balign 4
    .asciz "# GC Calendar Year %d Month %d Day %d\n"
    .balign 4
    .asciz "#             Hour %d Min %d Sec %d \n"
    .balign 4
    .incbin "baserom.dol", 0x3D1C34, 0x4
.global lbl_803D4C38
lbl_803D4C38:
	.incbin "baserom.dol", 0x3D1C38, 0x13C
.global lbl_803D4D74
lbl_803D4D74:
	.incbin "baserom.dol", 0x3D1D74, 0x268
.global lbl_803D4FDC
lbl_803D4FDC:
	.incbin "baserom.dol", 0x3D1FDC, 0x84
.global lbl_803D5060
lbl_803D5060:
	.incbin "baserom.dol", 0x3D2060, 0x84
.global lbl_803D50E4
lbl_803D50E4:
	.incbin "baserom.dol", 0x3D20E4, 0x84
.global lbl_803D5168
lbl_803D5168:
	.incbin "baserom.dol", 0x3D2168, 0x38
.global lbl_803D51A0
lbl_803D51A0:
	.incbin "baserom.dol", 0x3D21A0, 0x208
.global lbl_803D53A8
lbl_803D53A8:
	.incbin "baserom.dol", 0x3D23A8, 0xD8
.global lbl_803D5480
lbl_803D5480:
	.incbin "baserom.dol", 0x3D2480, 0xD8
.global lbl_803D5558
lbl_803D5558:
    .asciz "RandomStageSwitch All-Off!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
    .balign 4
.global lbl_803D5590
lbl_803D5590:
    .asciz "\\cffff00%2d"
    .balign 4
.global lbl_803D559C
lbl_803D559C:
    .asciz "\\ce0e0ff%5d"
    .balign 4
.global jtbl_803D55A8
jtbl_803D55A8:
	.incbin "baserom.dol", 0x3D25A8, 0x78
.global lbl_803D5620
lbl_803D5620:
	.incbin "baserom.dol", 0x3D2620, 0x10
.global lbl_803D5630
lbl_803D5630:
	.incbin "baserom.dol", 0x3D2630, 0x18
.global lbl_803D5648
lbl_803D5648:
	.incbin "baserom.dol", 0x3D2648, 0x404
.global lbl_803D5A4C
lbl_803D5A4C:
	.incbin "baserom.dol", 0x3D2A4C, 0x80C
.global jtbl_803D6258
jtbl_803D6258:
	.incbin "baserom.dol", 0x3D3258, 0xA8
.global lbl_803D6300
lbl_803D6300:
	.incbin "baserom.dol", 0x3D3300, 0x150
.global lbl_803D6450
lbl_803D6450:
	.incbin "baserom.dol", 0x3D3450, 0x1C
.global lbl_803D646C
lbl_803D646C:
	.incbin "baserom.dol", 0x3D346C, 0x1C
.global lbl_803D6488
lbl_803D6488:
	.incbin "baserom.dol", 0x3D3488, 0x3F0
.global lbl_803D6878
lbl_803D6878:
	.incbin "baserom.dol", 0x3D3878, 0x54
.global lbl_803D68CC
lbl_803D68CC:
	.incbin "baserom.dol", 0x3D38CC, 0x12C
.global lbl_803D69F8
lbl_803D69F8:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3D3A04, 0x4
.global lbl_803D6A08
lbl_803D6A08:
	.incbin "baserom.dol", 0x3D3A08, 0x10
.global lbl_803D6A18
lbl_803D6A18:
	.incbin "baserom.dol", 0x3D3A18, 0x600
.global lbl_803D7018
lbl_803D7018:
	.incbin "baserom.dol", 0x3D4018, 0x20
.global lbl_803D7038
lbl_803D7038:
	.incbin "baserom.dol", 0x3D4038, 0x20
.global lbl_803D7058
lbl_803D7058:
	.incbin "baserom.dol", 0x3D4058, 0x8B8
.global lbl_803D7910
lbl_803D7910:
	.incbin "baserom.dol", 0x3D4910, 0xC0
.global lbl_803D79D0
lbl_803D79D0:
	.incbin "baserom.dol", 0x3D49D0, 0x10
.global lbl_803D79E0
lbl_803D79E0:
	.incbin "baserom.dol", 0x3D49E0, 0x10
.global lbl_803D79F0
lbl_803D79F0:
	.incbin "baserom.dol", 0x3D49F0, 0x18
.global lbl_803D7A08
lbl_803D7A08:
    .asciz "Error : not find color in gmRegSetupEnemyColorTable()\n"
    .balign 4
.global lbl_803D7A40
lbl_803D7A40:
    .asciz "gmregcommon.c"
    .balign 4
.global jtbl_803D7A50
jtbl_803D7A50:
	.incbin "baserom.dol", 0x3D4A50, 0x20
.global jtbl_803D7A70
jtbl_803D7A70:
	.incbin "baserom.dol", 0x3D4A70, 0x50
.global lbl_803D7AC0
lbl_803D7AC0:
	.incbin "baserom.dol", 0x3D4AC0, 0xB30
.global lbl_803D85F0
lbl_803D85F0:
	.incbin "baserom.dol", 0x3D55F0, 0x598
.global lbl_803D8B88
lbl_803D8B88:
	.incbin "baserom.dol", 0x3D5B88, 0x150
.global lbl_803D8CD8
lbl_803D8CD8:
    .asciz "IfHrNoCn"
    .balign 4
    .asciz "ScInfCnt_scene_models"
    .balign 4
    .asciz "IfHrReco"
    .balign 4
.global lbl_803D8D08
lbl_803D8D08:
	.incbin "baserom.dol", 0x3D5D08, 0x540
.global lbl_803D9248
lbl_803D9248:
	.incbin "baserom.dol", 0x3D6248, 0x1CC
.global lbl_803D9414
lbl_803D9414:
	.incbin "baserom.dol", 0x3D6414, 0x48
.global lbl_803D945C
lbl_803D945C:
    .asciz "SdIntro.dat"
    .balign 4
.global lbl_803D9468
lbl_803D9468:
    .asciz "SIS_IntroData"
    .balign 4
    .asciz "GmIntEz.dat"
    .balign 4
    .asciz "gmIntroEasyTable"
    .balign 4
.global lbl_803D9498
lbl_803D9498:
	.incbin "baserom.dol", 0x3D6498, 0x2A0
.global lbl_803D9738
lbl_803D9738:
    .asciz "ScItrAllstar_scene_data"
    .balign 4
.global lbl_803D9750
lbl_803D9750:
	.incbin "baserom.dol", 0x3D6750, 0xD8
.global lbl_803D9828
lbl_803D9828:
	.incbin "baserom.dol", 0x3D6828, 0x7C
.global jtbl_803D98A4
jtbl_803D98A4:
	.incbin "baserom.dol", 0x3D68A4, 0x6C
.global lbl_803D9910
lbl_803D9910:
	.incbin "baserom.dol", 0x3D6910, 0x410
.global lbl_803D9D20
lbl_803D9D20:
	.incbin "baserom.dol", 0x3D6D20, 0x8C
.global lbl_803D9DAC
lbl_803D9DAC:
	.incbin "baserom.dol", 0x3D6DAC, 0xF0
.global jtbl_803D9E9C
jtbl_803D9E9C:
	.incbin "baserom.dol", 0x3D6E9C, 0x7C
.global lbl_803D9F18
lbl_803D9F18:
    .asciz "This is impossible stage num from mnSelStageRandom() -> stage %d \n"
    .balign 4
.global lbl_803D9F5C
lbl_803D9F5C:
    .asciz "gmtoulib.c"
    .balign 4
.global lbl_803D9F68
lbl_803D9F68:
    .asciz "SdTou.usd"
    .balign 4
.global lbl_803D9F74
lbl_803D9F74:
    .asciz "SdTou.dat"
    .balign 4
.global lbl_803D9F80
lbl_803D9F80:
	.incbin "baserom.dol", 0x3D6F80, 0x58
.global lbl_803D9FD8
lbl_803D9FD8:
	.incbin "baserom.dol", 0x3D6FD8, 0x4C
.global jtbl_803DA024
jtbl_803DA024:
	.incbin "baserom.dol", 0x3D7024, 0xAC
.global lbl_803DA0D0
lbl_803DA0D0:
	.incbin "baserom.dol", 0x3D70D0, 0x184
.global lbl_803DA254
lbl_803DA254:
    .asciz "translate"
    .balign 4
    .asciz "ScGamTour_scene_data"
    .balign 4
    .asciz "TmBox.dat"
    .balign 4
    .asciz "tournament_box2_array"
    .balign 4
    .asciz "tournament_box3_array"
    .balign 4
    .asciz "tournament_box4_array"
    .balign 4
    .asciz "SIS_TournamentData"
    .balign 4
.global lbl_803DA2E0
lbl_803DA2E0:
	.incbin "baserom.dol", 0x3D72E0, 0xF0
.global lbl_803DA3D0
lbl_803DA3D0:
    .asciz "ckind:%d\n"
    .balign 4
    .incbin "baserom.dol", 0x3D73DC, 0x4
.global lbl_803DA3E0
lbl_803DA3E0:
    .asciz "GmGover.dat"
    .balign 4
    .asciz "ScGamRegGover_scene_data"
    .balign 4
    .asciz "GmGoCoin.dat"
    .balign 4
    .asciz "GmGoAnim.dat"
    .balign 4
    .asciz "GmRgStnd.dat"
    .balign 4
    .asciz "standScene"
    .balign 4
    .asciz "SdIntro.dat"
    .balign 4
    .asciz "SIS_IntroData"
    .balign 4
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803DA488
lbl_803DA488:
    .asciz "IfComSn.dat"
    .balign 4
.global lbl_803DA494
lbl_803DA494:
    .asciz "ScComSoon_scene_data"
    .balign 4
    .incbin "baserom.dol", 0x3D74AC, 0x4
.global lbl_803DA4B0
lbl_803DA4B0:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803DA4D8
lbl_803DA4D8:
    .asciz "ScGamPause_scene_data"
    .balign 4
.global lbl_803DA4F0
lbl_803DA4F0:
	.incbin "baserom.dol", 0x3D74F0, 0xC
.global lbl_803DA4FC
lbl_803DA4FC:
	.incbin "baserom.dol", 0x3D74FC, 0x134
.global lbl_803DA630
lbl_803DA630:
	.incbin "baserom.dol", 0x3D7630, 0x30
.global jtbl_803DA660
jtbl_803DA660:
	.incbin "baserom.dol", 0x3D7660, 0x40
.global lbl_803DA6A0
lbl_803DA6A0:
    .asciz "SIS_VsCameraData"
    .balign 4
.global lbl_803DA6B4
lbl_803DA6B4:
	.incbin "baserom.dol", 0x3D76B4, 0x6C

    .balign 4
    .asciz "IfCameraInfo_Top_model_set"
    .balign 4
    .asciz "IfCamera_Top_model_set"

    .balign 8 # Hmm...
.global lbl_803DA758
lbl_803DA758:
    .asciz "?333?333C("
    .balign 4
    .incbin "baserom.dol", 0x3D7764, 0x24
.global lbl_803DA788
lbl_803DA788:
	.incbin "baserom.dol", 0x3D7788, 0x100
.global lbl_803DA888
lbl_803DA888:
	.incbin "baserom.dol", 0x3D7888, 0x40
.global lbl_803DA8C8
lbl_803DA8C8:
	.incbin "baserom.dol", 0x3D78C8, 0x10
.global lbl_803DA8D8
lbl_803DA8D8:
    .asciz "[hsdDumpClassStat] -- Report --\n"
    .balign 4
.global lbl_803DA8FC
lbl_803DA8FC:
    .asciz "[HSD_ObjDumpStat] -- Report --\n"
    .balign 4
    .incbin "baserom.dol", 0x3D791C, 0x4
.global lbl_803DA920
lbl_803DA920:
	.incbin "baserom.dol", 0x3D7920, 0x384
.global lbl_803DACA4
lbl_803DACA4:
	.incbin "baserom.dol", 0x3D7CA4, 0x39C
.global lbl_803DB040
lbl_803DB040:
    .asciz "gmvsmelee.c"
    .balign 4
    .incbin "baserom.dol", 0x3D804C, 0x1A8
.global lbl_803DB1F4
lbl_803DB1F4:
	.incbin "baserom.dol", 0x3D81F4, 0x68
.global lbl_803DB25C
lbl_803DB25C:
	.incbin "baserom.dol", 0x3D825C, 0x6C
.global lbl_803DB2C8
lbl_803DB2C8:
	.incbin "baserom.dol", 0x3D82C8, 0xC
.global lbl_803DB2D4
lbl_803DB2D4:
	.incbin "baserom.dol", 0x3D82D4, 0x18
.global lbl_803DB2EC
lbl_803DB2EC:
	.incbin "baserom.dol", 0x3D82EC, 0x144
.global lbl_803DB430
lbl_803DB430:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803DB458
lbl_803DB458:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .asciz "gmregenddisp.c"
    .balign 4
    .asciz "transJobj"
    .balign 4
    .asciz "Captain  "
    .balign 4
    .asciz "Donkey   "
    .balign 4
    .asciz "Fox      "
    .balign 4
    .asciz "GameWatch"
    .balign 4
    .asciz "Kirby    "
    .balign 4
    .asciz "Koopa    "
    .balign 4
    .asciz "Link     "
    .balign 4
    .asciz "Luigi    "
    .balign 4
    .asciz "Mario    "
    .balign 4
    .asciz "Mars     "
    .balign 4
    .asciz "Mewtwo   "
    .balign 4
    .asciz "Ness     "
    .balign 4
    .asciz "Peach    "
    .balign 4
    .asciz "Pikachu  "
    .balign 4
    .asciz "PopoNana "
    .balign 4
    .asciz "Purin    "
    .balign 4
    .asciz "Samus    "
    .balign 4
    .asciz "Yoshi    "
    .balign 4
    .asciz "Ze->Se   "
    .balign 4
    .asciz "Se->Ze   "
    .balign 4
    .asciz "Falco    "
    .balign 4
    .asciz "Clink    "
    .balign 4
    .asciz "Drmario  "
    .balign 4
    .asciz "Emblem   "
    .balign 4
    .asciz "Pichu    "
    .balign 4
    .asciz "Ganon    "
    .balign 4
    .asciz "MasterH  "
    .balign 4
    .asciz "Boy      "
    .balign 4
    .asciz "Girl     "
    .balign 4
    .asciz "GKoops   "
    .balign 4
    .asciz "CrezyH   "
    .balign 4
    .asciz "Sandbag  "
    .balign 4
    .asciz "POPO     "
    .balign 4
    .asciz "ToyDspStand_Top_joint"
    .balign 4
.global lbl_803DB640
lbl_803DB640:
    .asciz "GmRegendSimpleCaptain.thp"
    .balign 4
    .asciz "GmRegendSimpleDonkey.thp"
    .balign 4
    .asciz "GmRegendSimpleFox.thp"
    .balign 4
    .asciz "GmRegendSimpleGamewatch.thp"
    .balign 4
    .asciz "GmRegendSimpleKirby.thp"
    .balign 4
    .asciz "GmRegendSimpleKoopa.thp"
    .balign 4
    .asciz "GmRegendSimpleLink.thp"
    .balign 4
    .asciz "GmRegendSimpleLuigi.thp"
    .balign 4
    .asciz "GmRegendSimpleMario.thp"
    .balign 4
    .asciz "GmRegendSimpleMarth.thp"
    .balign 4
    .asciz "GmRegendSimpleMewtwo.thp"
    .balign 4
    .asciz "GmRegendSimpleNess.thp"
    .balign 4
    .asciz "GmRegendSimplePeach.thp"
    .balign 4
    .asciz "GmRegendSimplePikachu.thp"
    .balign 4
    .asciz "GmRegendSimplePoponana.thp"
    .balign 4
    .asciz "GmRegendSimplePurin.thp"
    .balign 4
    .asciz "GmRegendSimpleSamus.thp"
    .balign 4
    .asciz "GmRegendSimpleYoshi.thp"
    .balign 4
    .asciz "GmRegendSimpleZeldaseak.thp"
    .balign 4
    .asciz "GmRegendSimpleFalco.thp"
    .balign 4
    .asciz "GmRegendSimpleClink.thp"
    .balign 4
    .asciz "GmRegendSimpleDrmario.thp"
    .balign 4
    .asciz "GmRegendSimpleRoy.thp"
    .balign 4
    .asciz "GmRegendSimplePichu.thp"
    .balign 4
    .asciz "GmRegendSimpleGanon.thp"
    .balign 4
    .incbin "baserom.dol", 0x3D88B8, 0x6C0
.global lbl_803DBF78
lbl_803DBF78:
	.incbin "baserom.dol", 0x3D8F78, 0x3C
.global lbl_803DBFB4
lbl_803DBFB4:
	.incbin "baserom.dol", 0x3D8FB4, 0x18
.global lbl_803DBFCC
lbl_803DBFCC:
    .asciz "MvOpen.mth"
    .balign 4
.global lbl_803DBFD8
lbl_803DBFD8:
	.incbin "baserom.dol", 0x3D8FD8, 0x12E8
.global lbl_803DD2C0
lbl_803DD2C0:
	.incbin "baserom.dol", 0x3DA2C0, 0x128
.global lbl_803DD3E8
lbl_803DD3E8:
    .asciz "MvHowto.mth"
    .balign 4
    .incbin "baserom.dol", 0x3DA3F4, 0x4
.global lbl_803DD3F8
lbl_803DD3F8:
    .asciz "MvOmake15.mth"
    .balign 4
.global lbl_803DD408
lbl_803DD408:
    .asciz "NtProge.dat"
    .balign 4
    .asciz "ScNtcProgressive_scene_data"
    .balign 4
    .asciz "SdProge.usd"
    .balign 4
    .asciz "SIS_ProgeData"
    .balign 4
    .asciz "SdProge.dat"
    .balign 4
.global jtbl_803DD458
jtbl_803DD458:
	.incbin "baserom.dol", 0x3DA458, 0x5C
.global lbl_803DD4B4
lbl_803DD4B4:
    .asciz "ScNtcApproach_scene_data"
    .balign 4
.global lbl_803DD4D0
lbl_803DD4D0:
	.incbin "baserom.dol", 0x3DA4D0, 0x80
.global lbl_803DD550
lbl_803DD550:
	.incbin "baserom.dol", 0x3DA550, 0xB8
.global jtbl_803DD608
jtbl_803DD608:
	.incbin "baserom.dol", 0x3DA608, 0x40
.global jtbl_803DD648
jtbl_803DD648:
	.incbin "baserom.dol", 0x3DA648, 0x208
.global jtbl_803DD850
jtbl_803DD850:
	.incbin "baserom.dol", 0x3DA850, 0x98
.global jtbl_803DD8E8
jtbl_803DD8E8:
	.incbin "baserom.dol", 0x3DA8E8, 0x370
.global lbl_803DDC58
lbl_803DDC58:
	.incbin "baserom.dol", 0x3DAC58, 0x270
.global lbl_803DDEC8
lbl_803DDEC8:
	.incbin "baserom.dol", 0x3DAEC8, 0x2F0
.global lbl_803DE1B8
lbl_803DE1B8:
	.incbin "baserom.dol", 0x3DB1B8, 0x498
.global lbl_803DE650
lbl_803DE650:
	.incbin "baserom.dol", 0x3DB650, 0x2E0
.global lbl_803DE930
lbl_803DE930:
	.incbin "baserom.dol", 0x3DB930, 0x2B8
.global lbl_803DEBE8
lbl_803DEBE8:
	.incbin "baserom.dol", 0x3DBBE8, 0xA78
.global lbl_803DF660
lbl_803DF660:
    .asciz "GmEvent.dat"
    .balign 4
.global lbl_803DF66C
lbl_803DF66C:
    .asciz "sqEventInitDataLevelTbl"
    .balign 4
.global jtbl_803DF684
jtbl_803DF684:
	.incbin "baserom.dol", 0x3DC684, 0xA0
.global jtbl_803DF724
jtbl_803DF724:
	.incbin "baserom.dol", 0x3DC724, 0xA0
.global jtbl_803DF7C4
jtbl_803DF7C4:
	.incbin "baserom.dol", 0x3DC7C4, 0xA0
.global jtbl_803DF864
jtbl_803DF864:
	.incbin "baserom.dol", 0x3DC864, 0xB4
.global lbl_803DF918
lbl_803DF918:
	.incbin "baserom.dol", 0x3DC918, 0x34
.global lbl_803DF94C
lbl_803DF94C:
	.incbin "baserom.dol", 0x3DC94C, 0x4BC
.global lbl_803DFE08
lbl_803DFE08:
    .asciz "Pikmin dataFile"
    .balign 4
    .incbin "baserom.dol", 0x3DCE18, 0x90
.global lbl_803DFEA8
lbl_803DFEA8:
	.incbin "baserom.dol", 0x3DCEA8, 0x34

    .balign 4
.global lbl_803DFEDC
lbl_803DFEDC:
    .4byte 0x803DFEA8
    .4byte 0x803E5764
    .4byte 0x803E11A4
    .4byte 0x803E4ECC
    .4byte 0x803E1800
    .4byte 0x803E52E0
    .4byte 0x803E3F6C
    .4byte 0x803E5130
    .4byte 0x803E1B2C
    .4byte 0x803E4D0C
    .4byte 0x803E274C
    .4byte 0x803E51CC
    .4byte 0x803E0E5C
    .4byte 0x803E76D0
    .4byte 0x803E1F08
    .4byte 0x803E54CC
    .4byte 0x803E1334
    .4byte 0x803E6A3C
    .4byte 0x803E33DC
    .4byte 0x803E2D20
    .4byte 0x803E2858
    .4byte 0x803E3D94
    .4byte 0x803E4800
    .4byte NULL
    .4byte 0x803E4950
    .4byte 0x803E4C00
    .4byte NULL
    .4byte 0x803E7A00
    .4byte 0x803E6748
    .4byte 0x803E650C
    .4byte 0x803E65E8
    .4byte 0x803E584C
    .4byte 0x803E5988
    .4byte 0x803E5E0C
    .4byte 0x803E617C
    .4byte 0x803E5764
    .4byte 0x803E7E38
    .4byte 0x803E7F90
    .4byte 0x803E7D34
    .4byte 0x803E7B10
    .4byte 0x803E85A4
    .4byte 0x803E8664
    .4byte 0x803E872C
    .4byte 0x803E87EC
    .4byte 0x803E88AC
    .4byte 0x803E8974
    .4byte 0x803E8A34
    .4byte 0x803E8AF4
    .4byte 0x803E8C0C
    .4byte 0x803E8CCC
    .4byte 0x803E8D8C
    .4byte 0x803E8E4C
    .4byte 0x803E8F0C
    .4byte 0x803E8FCC
    .4byte 0x803E908C
    .4byte 0x803E914C
    .4byte 0x803E920C
    .4byte 0x803E92CC
    .4byte 0x803E9394
    .4byte 0x803E9454
    .4byte 0x803E9514
    .4byte 0x803E95D4
    .4byte 0x803E9694
    .4byte 0x803E9754
    .4byte 0x803E981C
    .4byte 0x803E98DC
    .4byte 0x803E84C4
    .4byte 0x803E821C
    .4byte 0x803E62C0
    .4byte 0x803E6370
    .4byte 0x803E6420
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764
    .4byte 0x803E5764

    .balign 4
    .asciz "%s:%d: couldn t get user data(Ground)\n"

    .balign 4
.global lbl_803E00C0
lbl_803E00C0:
    .asciz "ground.c"
    .balign 4
    .asciz "%s:%d: assert\n"
    .balign 4
    .asciz "%s:%d: couldn t get jobj\n"
    .balign 4
    .asciz "%s:%d: couldn t get gobj!\n"
    .balign 4
    .asciz "lightset"
    .balign 4
    .asciz "*lightset"
    .balign 4
.global lbl_803E012C
lbl_803E012C:
    .asciz "bgm!=BGM_Undefined"
    .balign 4
.global jtbl_803E0140
jtbl_803E0140:
	.incbin "baserom.dol", 0x3DD140, 0xB8
.global lbl_803E01F8
lbl_803E01F8:
    .asciz "%s:%d: not found stage param in DAT\n"
    .balign 4
.global lbl_803E0220
lbl_803E0220:
    .asciz "i!=Gr_CObj_Max"
    .balign 4
    .incbin "baserom.dol", 0x3DD230, 0x31C
.global lbl_803E054C
lbl_803E054C:
    .asciz "use dummy CamRange ...!\n"
    .balign 4
.global jtbl_803E0568
jtbl_803E0568:
	.incbin "baserom.dol", 0x3DD568, 0x6C
.global lbl_803E05D4
lbl_803E05D4:
    .asciz "use dummy DeadRange ...\n"
    .balign 4
.global jtbl_803E05F0
jtbl_803E05F0:
	.incbin "baserom.dol", 0x3DD5F0, 0xD8
.global lbl_803E06C8
lbl_803E06C8:
	.incbin "baserom.dol", 0x3DD6C8, 0x68
.global lbl_803E0730
lbl_803E0730:
    .asciz "grdisplay.c"
    .balign 4
.global lbl_803E073C
lbl_803E073C:
    .asciz "oioi... %08x\n"
    .balign 4
    .incbin "baserom.dol", 0x3DD74C, 0x4
.global lbl_803E0750
lbl_803E0750:
    .asciz "map_ptcl"
    .balign 4
.global lbl_803E075C
lbl_803E075C:
    .asciz "map_texg"
    .balign 4
    .asciz "map_head"
    .balign 4
    .asciz "coll_data"
    .balign 4
    .asciz "grGroundParam"
    .balign 4
    .asciz "itemdata"
    .balign 4
    .asciz "ALDYakuAll"
    .balign 4
    .asciz "yakumono_param"
    .balign 4
    .asciz "map_plit"
    .balign 4
    .asciz "quake_model_set"
    .balign 4
.global lbl_803E07D4
lbl_803E07D4:
    .asciz "grdatfiles.c"
    .balign 4
    .incbin "baserom.dol", 0x3DD7E4, 0x64
.global lbl_803E0848
lbl_803E0848:
	.incbin "baserom.dol", 0x3DD848, 0xDC
.global lbl_803E0924
lbl_803E0924:
	.incbin "baserom.dol", 0x3DD924, 0x34
.global lbl_803E0958
lbl_803E0958:
    .asciz "granime.c"
    .balign 4
.global lbl_803E0964
lbl_803E0964:
    .asciz "pobj_type(pobj) == POBJ_SHAPEANIM && pobj->u.shape_set"
    .balign 4
.global jtbl_803E099C
jtbl_803E099C:
	.incbin "baserom.dol", 0x3DD99C, 0x50
.global jtbl_803E09EC
jtbl_803E09EC:
	.incbin "baserom.dol", 0x3DD9EC, 0x34
.global lbl_803E0A20
lbl_803E0A20:
	.incbin "baserom.dol", 0x3DDA20, 0x160
.global lbl_803E0B80
lbl_803E0B80:
    .asciz "grdynamicattr.c"
    .balign 4
.global lbl_803E0B90
lbl_803E0B90:
    .asciz "floor_id!=GC_Id_None"
    .balign 4
.global lbl_803E0BA8
lbl_803E0BA8:
    .asciz "grzakogenerator.c"
    .balign 4
.global lbl_803E0BBC
lbl_803E0BBC:
    .asciz "%s:%d: couldn t get gobj!\n"
    .balign 4
.global lbl_803E0BD8
lbl_803E0BD8:
	.incbin "baserom.dol", 0x3DDBD8, 0x188
.global lbl_803E0D60
lbl_803E0D60:
	.incbin "baserom.dol", 0x3DDD60, 0x154
.global lbl_803E0EB4
lbl_803E0EB4:
    .asciz "grizumi.c"
    .balign 4
.global lbl_803E0EC0
lbl_803E0EC0:
    .asciz "%s:%d:Warning: not found tobj !\n"
    .balign 4
.global lbl_803E0EE4
lbl_803E0EE4:
    .asciz "GrdIzumiStar_TopN_joint"
    .balign 4
.global lbl_803E0EFC
lbl_803E0EFC:
    .asciz "%s:%d:oioi...\n"
    .balign 4
    .incbin "baserom.dol", 0x3DDF0C, 0xDC
.global lbl_803E0FE8
lbl_803E0FE8:
	.incbin "baserom.dol", 0x3DDFE8, 0x260
.global lbl_803E1248
lbl_803E1248:
	.incbin "baserom.dol", 0x3DE248, 0x144
.global lbl_803E138C
lbl_803E138C:
    .asciz "grpstadium.c"
    .balign 4
    .asciz "GrdPStadiumBG_OVDummy_mat6962_GrdPStadiumDummy_0_image_desc"
    .balign 4
    .asciz "no such image desc!\n"
    .balign 4
    .asciz "no such tobj!\n"
    .balign 4
.global jtbl_803E1400
jtbl_803E1400:
	.incbin "baserom.dol", 0x3DE400, 0x48
.global jtbl_803E1448
jtbl_803E1448:
	.incbin "baserom.dol", 0x3DE448, 0x44
.global jtbl_803E148C
jtbl_803E148C:
	.incbin "baserom.dol", 0x3DE48C, 0x70
.global lbl_803E14FC
lbl_803E14FC:
	.incbin "baserom.dol", 0x3DE4FC, 0x38
.global lbl_803E1534
lbl_803E1534:
    .asciz "SIS_GrPStadiumData"
    .balign 4
    .asciz "vision_gobj"
    .balign 4
    .asciz "gp2->win_static_p"
    .balign 4
    .asciz "gp2->win_dynamic_p"
    .balign 4
    .asciz "00:00 00"
    .balign 4
    .asciz "%02d:%02d %02d"
    .balign 4
    .incbin "baserom.dol", 0x3DE598, 0x128
.global jtbl_803E16C0
jtbl_803E16C0:
	.incbin "baserom.dol", 0x3DE6C0, 0x20
.global lbl_803E16E0
lbl_803E16E0:
	.incbin "baserom.dol", 0x3DE6E0, 0x178
.global lbl_803E1858
lbl_803E1858:
    .asciz "grkongo.c"
    .balign 4
.global lbl_803E1864
lbl_803E1864:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803E188C
lbl_803E188C:
	.incbin "baserom.dol", 0x3DE88C, 0x168
.global lbl_803E19F4
lbl_803E19F4:
    .asciz "translate"
    .balign 4
.global lbl_803E1A00
lbl_803E1A00:
    .asciz "gp->u.taru.keep"
    .balign 4
.global lbl_803E1A10
lbl_803E1A10:
	.incbin "baserom.dol", 0x3DEA10, 0x174
.global lbl_803E1B84
lbl_803E1B84:
    .asciz "grzebes.c"
    .balign 4
.global lbl_803E1B90
lbl_803E1B90:
	.incbin "baserom.dol", 0x3DEB90, 0xF0
.global lbl_803E1C80
lbl_803E1C80:
	.incbin "baserom.dol", 0x3DEC80, 0x6C
.global lbl_803E1CEC
lbl_803E1CEC:
    .asciz "map_a_gobj"
    .balign 4
    .incbin "baserom.dol", 0x3DECF8, 0x30
.global lbl_803E1D28
lbl_803E1D28:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3DED34, 0x4
.global lbl_803E1D38
lbl_803E1D38:
	.incbin "baserom.dol", 0x3DED38, 0x48
.global lbl_803E1D80
lbl_803E1D80:
	.incbin "baserom.dol", 0x3DED80, 0x1E0
.global lbl_803E1F60
lbl_803E1F60:
    .asciz "grcorneria.c"
    .balign 4
.global lbl_803E1F70
lbl_803E1F70:
	.incbin "baserom.dol", 0x3DEF70, 0x3C
.global lbl_803E1FAC
lbl_803E1FAC:
	.incbin "baserom.dol", 0x3DEFAC, 0x3C
.global lbl_803E1FE8
lbl_803E1FE8:
	.incbin "baserom.dol", 0x3DEFE8, 0x18
.global lbl_803E2000
lbl_803E2000:
	.incbin "baserom.dol", 0x3DF000, 0x190
.global lbl_803E2190
lbl_803E2190:
	.incbin "baserom.dol", 0x3DF190, 0x34
.global lbl_803E21C4
lbl_803E21C4:
    .asciz "grcorneria.c    grCorneriaGetPosMapKind2\n"
    .balign 4
    .incbin "baserom.dol", 0x3DF1F0, 0x14
.global lbl_803E2204
lbl_803E2204:
	.incbin "baserom.dol", 0x3DF204, 0x4B0
.global lbl_803E26B4
lbl_803E26B4:
    .asciz "talk no = %d\n"
    .balign 4
.global lbl_803E26C4
lbl_803E26C4:
    .asciz "*** Beam Damage! %f\n"
    .balign 4
.global lbl_803E26DC
lbl_803E26DC:
    .asciz "SIS_GrCorneriaData"
    .balign 4
.global lbl_803E26F0
lbl_803E26F0:
	.incbin "baserom.dol", 0x3DF6F0, 0xF0
.global lbl_803E27E0
lbl_803E27E0:
	.incbin "baserom.dol", 0x3DF7E0, 0xD0
.global lbl_803E28B0
lbl_803E28B0:
    .asciz "gronett.c"
    .balign 4
.global lbl_803E28BC
lbl_803E28BC:
    .asciz "gp->u.map.subject"
    .balign 4
.global jtbl_803E28D0
jtbl_803E28D0:
	.incbin "baserom.dol", 0x3DF8D0, 0x20
.global jtbl_803E28F0
jtbl_803E28F0:
	.incbin "baserom.dol", 0x3DF8F0, 0x20
.global lbl_803E2910
lbl_803E2910:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803E2938
lbl_803E2938:
	.incbin "baserom.dol", 0x3DF938, 0x440
.global lbl_803E2D78
lbl_803E2D78:
    .asciz "grbigblue.c"
    .balign 4
    .incbin "baserom.dol", 0x3DFD84, 0x134
.global lbl_803E2EB8
lbl_803E2EB8:
    .asciz "*** Not Set Position!(Tyukei)\n"
    .balign 4
    .incbin "baserom.dol", 0x3DFED8, 0x108
.global jtbl_803E2FE0
jtbl_803E2FE0:
	.incbin "baserom.dol", 0x3DFFE0, 0x58
.global jtbl_803E3038
jtbl_803E3038:
	.incbin "baserom.dol", 0x3E0038, 0x2C
.global jtbl_803E3064
jtbl_803E3064:
	.incbin "baserom.dol", 0x3E0064, 0x4C
.global lbl_803E30B0
lbl_803E30B0:
	.incbin "baserom.dol", 0x3E00B0, 0x384
.global lbl_803E3434
lbl_803E3434:
    .asciz "grmutecity.c"
    .balign 4
    .asciz "not found car spline (R)\n"
    .balign 4
    .asciz "not found car spline (L)\n"
    .balign 4
.global lbl_803E347C
lbl_803E347C:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803E34A4
lbl_803E34A4:
	.incbin "baserom.dol", 0x3E04A4, 0x3C
.global lbl_803E34E0
lbl_803E34E0:
	.incbin "baserom.dol", 0x3E04E0, 0x630
.global lbl_803E3B10
lbl_803E3B10:
	.incbin "baserom.dol", 0x3E0B10, 0x6C
.global lbl_803E3B7C
lbl_803E3B7C:
	.incbin "baserom.dol", 0x3E0B7C, 0x16C
.global lbl_803E3CE8
lbl_803E3CE8:
	.incbin "baserom.dol", 0x3E0CE8, 0x114
.global lbl_803E3DFC
lbl_803E3DFC:
    .asciz "pos = %f : tgrpos = %f\n"
    .balign 4
.global jtbl_803E3E14
jtbl_803E3E14:
	.incbin "baserom.dol", 0x3E0E14, 0x4C
.global lbl_803E3E60
lbl_803E3E60:
	.incbin "baserom.dol", 0x3E0E60, 0x164
.global lbl_803E3FC4
lbl_803E3FC4:
    .asciz "grgreatbay.c"
    .balign 4
    .asciz "trans_jobj"
    .balign 4
.global lbl_803E3FE0
lbl_803E3FE0:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803E4008
lbl_803E4008:
    .asciz "translate"
    .balign 4
.global jtbl_803E4014
jtbl_803E4014:
	.incbin "baserom.dol", 0x3E1014, 0x34
.global lbl_803E4048
lbl_803E4048:
	.incbin "baserom.dol", 0x3E1048, 0x20
.global lbl_803E4068
lbl_803E4068:
	.incbin "baserom.dol", 0x3E1068, 0x4DC
.global lbl_803E4544
lbl_803E4544:
	.incbin "baserom.dol", 0x3E1544, 0x1B4
.global lbl_803E46F8
lbl_803E46F8:
    .asciz "gricemt.c"
    .balign 4
    .asciz "i<ICEMT_FIELD_MAX"
    .balign 4
    .incbin "baserom.dol", 0x3E1718, 0x1B0
.global lbl_803E48C8
lbl_803E48C8:
	.incbin "baserom.dol", 0x3E18C8, 0xE0
.global lbl_803E49A8
lbl_803E49A8:
    .asciz "grinishie1.c"
    .balign 4
    .incbin "baserom.dol", 0x3E19B8, 0x78
.global lbl_803E4A30
lbl_803E4A30:
    .asciz "!mapgp->u.map.block[ix].hatena_gobj"
    .balign 4
.global lbl_803E4A54
lbl_803E4A54:
    .asciz "map_gobj"
    .balign 4
.global lbl_803E4A60
lbl_803E4A60:
	.incbin "baserom.dol", 0x3E1A60, 0x218
.global lbl_803E4C78
lbl_803E4C78:
	.incbin "baserom.dol", 0x3E1C78, 0xF8
.global lbl_803E4D70
lbl_803E4D70:
    .asciz "*** Req Effect Anime %d\n"
    .balign 4
.global lbl_803E4D8C
lbl_803E4D8C:
    .asciz "Kraid Hand Pos = %f\n"
    .balign 4
    .incbin "baserom.dol", 0x3E1DA4, 0x4
.global lbl_803E4DA8
lbl_803E4DA8:
	.incbin "baserom.dol", 0x3E1DA8, 0x17C
.global lbl_803E4F24
lbl_803E4F24:
    .asciz "grrcruise.c"
    .balign 4
.global lbl_803E4F30
lbl_803E4F30:
    .asciz "gp->u.map.chikuwa"
    .balign 4
.global lbl_803E4F44
lbl_803E4F44:
    .asciz "dynamicsdata_shipflag"
    .balign 4
    .asciz "gp->u.scroll.int_jobj"
    .balign 4
    .asciz "gp->u.scroll.cam_jobj"
    .balign 4
    .asciz "gp->u.scroll.ctr_jobj"
    .balign 4
    .asciz "translate"
    .balign 4
.global lbl_803E4FB0
lbl_803E4FB0:
    .asciz "gp->u.scroll.anim_gobj"
    .balign 4
.global lbl_803E4FC8
lbl_803E4FC8:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803E4FF0
lbl_803E4FF0:
	.incbin "baserom.dol", 0x3E1FF0, 0xF8
.global lbl_803E50E8
lbl_803E50E8:
	.incbin "baserom.dol", 0x3E20E8, 0xB0
.global lbl_803E5198
lbl_803E5198:
	.incbin "baserom.dol", 0x3E2198, 0x98
.global lbl_803E5230
lbl_803E5230:
    .asciz "*** End Frame = %d\n"
    .balign 4
    .incbin "baserom.dol", 0x3E2244, 0x4
.global lbl_803E5248
lbl_803E5248:
	.incbin "baserom.dol", 0x3E2248, 0x100
.global lbl_803E5348
lbl_803E5348:
	.incbin "baserom.dol", 0x3E2348, 0x38
.global lbl_803E5380
lbl_803E5380:
	.incbin "baserom.dol", 0x3E2380, 0x1A4
.global lbl_803E5524
lbl_803E5524:
    .asciz "grvenom.c"
    .balign 4
    .incbin "baserom.dol", 0x3E2530, 0x150
.global lbl_803E5680
lbl_803E5680:
	.incbin "baserom.dol", 0x3E2680, 0x38
.global lbl_803E56B8
lbl_803E56B8:
	.incbin "baserom.dol", 0x3E26B8, 0x110
.global lbl_803E57C8
lbl_803E57C8:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803E57F0
lbl_803E57F0:
	.incbin "baserom.dol", 0x3E27F0, 0xF0
.global lbl_803E58E0
lbl_803E58E0:
	.incbin "baserom.dol", 0x3E28E0, 0x100
.global lbl_803E59E0
lbl_803E59E0:
    .asciz "grshrineroute.c"
    .balign 4
.global lbl_803E59F0
lbl_803E59F0:
    .asciz "translate"
    .balign 4
.global lbl_803E59FC
lbl_803E59FC:
    .asciz "gp->u.map.symbol[ix]"
    .balign 4
.global jtbl_803E5A14
jtbl_803E5A14:
	.incbin "baserom.dol", 0x3E2A14, 0x44
.global lbl_803E5A58
lbl_803E5A58:
	.incbin "baserom.dol", 0x3E2A58, 0x30C
.global lbl_803E5D64
lbl_803E5D64:
    .asciz "%s:%d: oioi...\n"
    .balign 4
.global lbl_803E5D74
lbl_803E5D74:
	.incbin "baserom.dol", 0x3E2D74, 0x1C
.global lbl_803E5D90
lbl_803E5D90:
	.incbin "baserom.dol", 0x3E2D90, 0x20
.global lbl_803E5DB0
lbl_803E5DB0:
	.incbin "baserom.dol", 0x3E2DB0, 0xB4
.global lbl_803E5E64
lbl_803E5E64:
    .asciz "grzebesroute.c"
    .balign 4
    .incbin "baserom.dol", 0x3E2E74, 0x4
.global lbl_803E5E78
lbl_803E5E78:
	.incbin "baserom.dol", 0x3E2E78, 0x35C
.global lbl_803E61D4
lbl_803E61D4:
    .asciz "grbigblueroute.c"
    .balign 4
    .asciz "translate"
    .balign 4
    .asciz "reb0_jobj"
    .balign 4
.global lbl_803E6200
lbl_803E6200:
	.incbin "baserom.dol", 0x3E3200, 0x3C
.global lbl_803E623C
lbl_803E623C:
    .asciz "gp->u.car.car_info"
    .balign 4
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803E6278
lbl_803E6278:
	.incbin "baserom.dol", 0x3E3278, 0xB0
.global lbl_803E6328
lbl_803E6328:
	.incbin "baserom.dol", 0x3E3328, 0xB0
.global lbl_803E63D8
lbl_803E63D8:
	.incbin "baserom.dol", 0x3E33D8, 0xB0
.global lbl_803E6488
lbl_803E6488:
	.incbin "baserom.dol", 0x3E3488, 0xEC
.global lbl_803E6574
lbl_803E6574:
	.incbin "baserom.dol", 0x3E3574, 0xC
.global lbl_803E6580
lbl_803E6580:
	.incbin "baserom.dol", 0x3E3580, 0xC0
.global lbl_803E6640
lbl_803E6640:
    .asciz "groldkongo.c"
    .balign 4
.global lbl_803E6650
lbl_803E6650:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803E6678
lbl_803E6678:
    .asciz "gp->u.taru.keep"
    .balign 4
.global lbl_803E6688
lbl_803E6688:
	.incbin "baserom.dol", 0x3E3688, 0x178
.global lbl_803E6800
lbl_803E6800:
	.incbin "baserom.dol", 0x3E3800, 0x2A0
.global lbl_803E6AA0
lbl_803E6AA0:
	.incbin "baserom.dol", 0x3E3AA0, 0x16C
.global lbl_803E6C0C
lbl_803E6C0C:
	.incbin "baserom.dol", 0x3E3C0C, 0xA14
.global lbl_803E7620
lbl_803E7620:
	.incbin "baserom.dol", 0x3E4620, 0x18
.global lbl_803E7638
lbl_803E7638:
	.incbin "baserom.dol", 0x3E4638, 0xF0
.global lbl_803E7728
lbl_803E7728:
    .asciz "grgreens.c"
    .balign 4
    .incbin "baserom.dol", 0x3E4734, 0xF0
.global jtbl_803E7824
jtbl_803E7824:
	.incbin "baserom.dol", 0x3E4824, 0x1C
.global lbl_803E7840
lbl_803E7840:
	.incbin "baserom.dol", 0x3E4840, 0x100
.global lbl_803E7940
lbl_803E7940:
	.incbin "baserom.dol", 0x3E4940, 0x128
.global lbl_803E7A68
lbl_803E7A68:
	.incbin "baserom.dol", 0x3E4A68, 0x60
.global lbl_803E7AC8
lbl_803E7AC8:
	.incbin "baserom.dol", 0x3E4AC8, 0xA0
.global lbl_803E7B68
lbl_803E7B68:
    .asciz "grpushon.c"
    .balign 4
.global lbl_803E7B74
lbl_803E7B74:
	.incbin "baserom.dol", 0x3E4B74, 0x1C
.global lbl_803E7B90
lbl_803E7B90:
	.incbin "baserom.dol", 0x3E4B90, 0x13C
.global lbl_803E7CCC
lbl_803E7CCC:
	.incbin "baserom.dol", 0x3E4CCC, 0x34
.global lbl_803E7D00
lbl_803E7D00:
	.incbin "baserom.dol", 0x3E4D00, 0xA0
.global lbl_803E7DA0
lbl_803E7DA0:
	.incbin "baserom.dol", 0x3E4DA0, 0x110
.global lbl_803E7EB0
lbl_803E7EB0:
    .asciz "grlast.c"
    .balign 4
    .incbin "baserom.dol", 0x3E4EBC, 0x12C
.global lbl_803E7FE8
lbl_803E7FE8:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3E5010, 0x30
.global jtbl_803E8040
jtbl_803E8040:
	.incbin "baserom.dol", 0x3E5040, 0x40
.global jtbl_803E8080
jtbl_803E8080:
	.incbin "baserom.dol", 0x3E5080, 0x78
.global jtbl_803E80F8
jtbl_803E80F8:
	.incbin "baserom.dol", 0x3E50F8, 0x48
.global lbl_803E8140
lbl_803E8140:
	.incbin "baserom.dol", 0x3E5140, 0x278
.global lbl_803E83B8
lbl_803E83B8:
	.incbin "baserom.dol", 0x3E53B8, 0x164
.global lbl_803E851C
lbl_803E851C:
    .asciz "grheal.c"
    .balign 4
    .asciz "*** Not found Next Player!(%d)\n"
    .balign 4
.global lbl_803E8548
lbl_803E8548:
	.incbin "baserom.dol", 0x3E5548, 0xC0
.global lbl_803E8608
lbl_803E8608:
	.incbin "baserom.dol", 0x3E5608, 0xC8
.global lbl_803E86D0
lbl_803E86D0:
	.incbin "baserom.dol", 0x3E56D0, 0xC0
.global lbl_803E8790
lbl_803E8790:
	.incbin "baserom.dol", 0x3E5790, 0xC0
.global lbl_803E8850
lbl_803E8850:
	.incbin "baserom.dol", 0x3E5850, 0xC8
.global lbl_803E8918
lbl_803E8918:
	.incbin "baserom.dol", 0x3E5918, 0xC0
.global lbl_803E89D8
lbl_803E89D8:
	.incbin "baserom.dol", 0x3E59D8, 0xC0
.global lbl_803E8A98
lbl_803E8A98:
	.incbin "baserom.dol", 0x3E5A98, 0xC4
.global lbl_803E8B5C
lbl_803E8B5C:
	.incbin "baserom.dol", 0x3E5B5C, 0x54
.global lbl_803E8BB0
lbl_803E8BB0:
	.incbin "baserom.dol", 0x3E5BB0, 0xC0
.global lbl_803E8C70
lbl_803E8C70:
	.incbin "baserom.dol", 0x3E5C70, 0xC0
.global lbl_803E8D30
lbl_803E8D30:
	.incbin "baserom.dol", 0x3E5D30, 0xC0
.global lbl_803E8DF0
lbl_803E8DF0:
	.incbin "baserom.dol", 0x3E5DF0, 0xC0
.global lbl_803E8EB0
lbl_803E8EB0:
	.incbin "baserom.dol", 0x3E5EB0, 0xC0
.global lbl_803E8F70
lbl_803E8F70:
	.incbin "baserom.dol", 0x3E5F70, 0xC0
.global lbl_803E9030
lbl_803E9030:
	.incbin "baserom.dol", 0x3E6030, 0xC0
.global lbl_803E90F0
lbl_803E90F0:
	.incbin "baserom.dol", 0x3E60F0, 0xC0
.global lbl_803E91B0
lbl_803E91B0:
	.incbin "baserom.dol", 0x3E61B0, 0xC0
.global lbl_803E9270
lbl_803E9270:
	.incbin "baserom.dol", 0x3E6270, 0xC8
.global lbl_803E9338
lbl_803E9338:
	.incbin "baserom.dol", 0x3E6338, 0xC0
.global lbl_803E93F8
lbl_803E93F8:
	.incbin "baserom.dol", 0x3E63F8, 0xC0
.global lbl_803E94B8
lbl_803E94B8:
	.incbin "baserom.dol", 0x3E64B8, 0xC0
.global lbl_803E9578
lbl_803E9578:
	.incbin "baserom.dol", 0x3E6578, 0xC0
.global lbl_803E9638
lbl_803E9638:
	.incbin "baserom.dol", 0x3E6638, 0xC0
.global lbl_803E96F8
lbl_803E96F8:
	.incbin "baserom.dol", 0x3E66F8, 0xC8
.global lbl_803E97C0
lbl_803E97C0:
	.incbin "baserom.dol", 0x3E67C0, 0xC0
.global lbl_803E9880
lbl_803E9880:
	.incbin "baserom.dol", 0x3E6880, 0xC0
.global lbl_803E9940
lbl_803E9940:
    .asciz "no!=St_Player_InitPos_None"
    .balign 4
    .incbin "baserom.dol", 0x3E695C, 0x4
.global lbl_803E9960
lbl_803E9960:
	.incbin "baserom.dol", 0x3E6960, 0xD68
.global lbl_803EA6C8
lbl_803EA6C8:
    .asciz "DATE Feb 13 2002  TIME 22:06:27"
    .balign 4
.global lbl_803EA6E8
lbl_803EA6E8:
    .asciz "DbCo.dat"
    .balign 4
.global lbl_803EA6F4
lbl_803EA6F4:
    .asciz "dbLoadCommonData"
    .balign 4
.global lbl_803EA708
lbl_803EA708:
    .asciz "[all PLink num] -- Report --\n"
    .balign 4
.global lbl_803EA728
lbl_803EA728:
    .asciz "------------------------------------------------------------\n"
    .balign 4
.global lbl_803EA768
lbl_803EA768:
    .asciz "------ Thread info ------\n"
    .balign 4
.global lbl_803EA784
lbl_803EA784:
    .asciz "base:%x, end:%x, size:%d peak:%d \n"
    .balign 4
.global lbl_803EA7A8
lbl_803EA7A8:
    .asciz "Capsule "
    .balign 4
    .asciz "Box     "
    .balign 4
    .asciz "Taru    "
    .balign 4
    .asciz "Egg     "
    .balign 4
    .asciz "Kusudama"
    .balign 4
    .asciz "TaruCann"
    .balign 4
    .asciz "BombHei "
    .balign 4
    .asciz "Dosei   "
    .balign 4
    .asciz "Heart   "
    .balign 4
    .asciz "Tomato  "
    .balign 4
    .asciz "Star    "
    .balign 4
    .asciz "Bat     "
    .balign 4
    .asciz "Sword   "
    .balign 4
    .asciz "Parasol "
    .balign 4
    .asciz "G Shell "
    .balign 4
    .asciz "R Shell "
    .balign 4
    .asciz "L Gun   "
    .balign 4
    .asciz "Freeze  "
    .balign 4
    .asciz "Foods   "
    .balign 4
    .asciz "MSBomb  "
    .balign 4
    .asciz "Flipper "
    .balign 4
    .asciz "S Scope "
    .balign 4
    .asciz "StarRod "
    .balign 4
    .asciz "LipStick"
    .balign 4
    .asciz "Harisen "
    .balign 4
    .asciz "F Flower"
    .balign 4
    .asciz "Kinoko  "
    .balign 4
    .asciz "DKinoko "
    .balign 4
    .asciz "Hammer  "
    .balign 4
    .asciz "WStar   "
    .balign 4
    .asciz "ScBall  "
    .balign 4
    .asciz "RabbitC "
    .balign 4
    .asciz "MetalB  "
    .balign 4
    .asciz "Spycloak"
    .balign 4
    .asciz "M Ball  "
    .balign 4
    .incbin "baserom.dol", 0x3E794C, 0x354
.global lbl_803EACA0
lbl_803EACA0:
    .asciz "Item Max Over.\n"
    .balign 4
.global lbl_803EACB0
lbl_803EACB0:
    .asciz "couldn't get Item struct.(CZako)\n"
    .balign 4
    .incbin "baserom.dol", 0x3E7CD4, 0x4
.global lbl_803EACD8
lbl_803EACD8:
    .asciz "A B  C D E    F    G"
    .balign 4
.global lbl_803EACF0
lbl_803EACF0:
    .asciz "\n%d %d %2d %d %2.2f %2.2f %2.2f"
    .balign 4
.global lbl_803EAD10
lbl_803EAD10:
    .asciz "EYE %d,%d,%d"
    .balign 4
    .asciz "INT %d,%d,%d"
    .balign 4
    .asciz "FOV %d  ANG %d"
    .balign 4
.global lbl_803EAD40
lbl_803EAD40:
	.incbin "baserom.dol", 0x3E7D40, 0x88
.global lbl_803EADC8
lbl_803EADC8:
    .asciz "cant find xfb!\n"
    .balign 4
    .asciz "dbscreenshot.c"
    .balign 4
    .asciz "USB:shot/screenshot%02d.frb"
    .balign 4
    .incbin "baserom.dol", 0x3E7E04, 0x4
.global lbl_803EAE08
lbl_803EAE08:
	.incbin "baserom.dol", 0x3E7E08, 0x50
.global lbl_803EAE58
lbl_803EAE58:
    .asciz "objalloc.h"
    .balign 4
    .incbin "baserom.dol", 0x3E7E64, 0x4
.global lbl_803EAE68
lbl_803EAE68:
	.incbin "baserom.dol", 0x3E7E68, 0x540
.global lbl_803EB3A8
lbl_803EB3A8:
	.incbin "baserom.dol", 0x3E83A8, 0x18
.global lbl_803EB3C0
lbl_803EB3C0:
	.incbin "baserom.dol", 0x3E83C0, 0x2F0
.global lbl_803EB6B0
lbl_803EB6B0:
	.incbin "baserom.dol", 0x3E86B0, 0x300
.global jtbl_803EB9B0
jtbl_803EB9B0:
	.incbin "baserom.dol", 0x3E89B0, 0x88
.global jtbl_803EBA38
jtbl_803EBA38:
	.incbin "baserom.dol", 0x3E8A38, 0x88
.global jtbl_803EBAC0
jtbl_803EBAC0:
	.incbin "baserom.dol", 0x3E8AC0, 0x88
.global jtbl_803EBB48
jtbl_803EBB48:
	.incbin "baserom.dol", 0x3E8B48, 0xAB8
.global lbl_803EC600
lbl_803EC600:
	.incbin "baserom.dol", 0x3E9600, 0x134
.global lbl_803EC734
lbl_803EC734:
	.incbin "baserom.dol", 0x3E9734, 0x3C
.global lbl_803EC770
lbl_803EC770:
	.incbin "baserom.dol", 0x3E9770, 0x6C
.global lbl_803EC7DC
lbl_803EC7DC:
	.incbin "baserom.dol", 0x3E97DC, 0x3C
.global lbl_803EC818
lbl_803EC818:
	.incbin "baserom.dol", 0x3E9818, 0x9B8
.global lbl_803ED1D0
lbl_803ED1D0:
	.incbin "baserom.dol", 0x3EA1D0, 0xA0
.global lbl_803ED270
lbl_803ED270:
	.incbin "baserom.dol", 0x3EA270, 0x24
.global lbl_803ED294
lbl_803ED294:
	.incbin "baserom.dol", 0x3EA294, 0x54
.global lbl_803ED2E8
lbl_803ED2E8:
	.incbin "baserom.dol", 0x3EA2E8, 0x58
.global lbl_803ED340
lbl_803ED340:
	.incbin "baserom.dol", 0x3EA340, 0x30
.global lbl_803ED370
lbl_803ED370:
	.incbin "baserom.dol", 0x3EA370, 0xC8
.global lbl_803ED438
lbl_803ED438:
	.incbin "baserom.dol", 0x3EA438, 0x50
.global lbl_803ED488
lbl_803ED488:
	.incbin "baserom.dol", 0x3EA488, 0x3C
.global lbl_803ED4C4
lbl_803ED4C4:
	.incbin "baserom.dol", 0x3EA4C4, 0x74
.global lbl_803ED538
lbl_803ED538:
	.incbin "baserom.dol", 0x3EA538, 0xC8
.global lbl_803ED600
lbl_803ED600:
	.incbin "baserom.dol", 0x3EA600, 0x18
.global lbl_803ED618
lbl_803ED618:
	.incbin "baserom.dol", 0x3EA618, 0x440
.global lbl_803EDA58
lbl_803EDA58:
	.incbin "baserom.dol", 0x3EAA58, 0x24
.global lbl_803EDA7C
lbl_803EDA7C:
	.incbin "baserom.dol", 0x3EAA7C, 0x268
.global lbl_803EDCE4
lbl_803EDCE4:
	.incbin "baserom.dol", 0x3EACE4, 0x64C
.global lbl_803EE330
lbl_803EE330:
	.incbin "baserom.dol", 0x3EB330, 0xC
.global jtbl_803EE33C
jtbl_803EE33C:
	.incbin "baserom.dol", 0x3EB33C, 0x3E4
.global lbl_803EE720
lbl_803EE720:
	.incbin "baserom.dol", 0x3EB720, 0x4
.global lbl_803EE724
lbl_803EE724:
	.incbin "baserom.dol", 0x3EB724, 0x4
.global lbl_803EE728
lbl_803EE728:
	.incbin "baserom.dol", 0x3EB728, 0x24
.global lbl_803EE74C
lbl_803EE74C:
	.incbin "baserom.dol", 0x3EB74C, 0x1C
.global lbl_803EE768
lbl_803EE768:
	.incbin "baserom.dol", 0x3EB768, 0xC
.global lbl_803EE774
lbl_803EE774:
	.incbin "baserom.dol", 0x3EB774, 0x35C
.global lbl_803EEAD0
lbl_803EEAD0:
	.incbin "baserom.dol", 0x3EBAD0, 0x90
.global lbl_803EEB60
lbl_803EEB60:
	.incbin "baserom.dol", 0x3EBB60, 0x18
.global jtbl_803EEB78
jtbl_803EEB78:
	.incbin "baserom.dol", 0x3EBB78, 0x98
.global lbl_803EEC10
lbl_803EEC10:
	.incbin "baserom.dol", 0x3EBC10, 0xC
.global lbl_803EEC1C
lbl_803EEC1C:
	.incbin "baserom.dol", 0x3EBC1C, 0xC
.global lbl_803EEC28
lbl_803EEC28:
	.incbin "baserom.dol", 0x3EBC28, 0x24
.global lbl_803EEC4C
lbl_803EEC4C:
	.incbin "baserom.dol", 0x3EBC4C, 0x94
.global lbl_803EECE0
lbl_803EECE0:
	.incbin "baserom.dol", 0x3EBCE0, 0xC
.global lbl_803EECEC
lbl_803EECEC:
	.incbin "baserom.dol", 0x3EBCEC, 0xC
.global lbl_803EECF8
lbl_803EECF8:
	.incbin "baserom.dol", 0x3EBCF8, 0xC
.global lbl_803EED04
lbl_803EED04:
	.incbin "baserom.dol", 0x3EBD04, 0x1D4
.global lbl_803EEED8
lbl_803EEED8:
	.incbin "baserom.dol", 0x3EBED8, 0x3C
.global lbl_803EEF14
lbl_803EEF14:
	.incbin "baserom.dol", 0x3EBF14, 0xC
.global lbl_803EEF20
lbl_803EEF20:
	.incbin "baserom.dol", 0x3EBF20, 0xB8
.global lbl_803EEFD8
lbl_803EEFD8:
	.incbin "baserom.dol", 0x3EBFD8, 0xC
.global lbl_803EEFE4
lbl_803EEFE4:
	.incbin "baserom.dol", 0x3EBFE4, 0xC
.global lbl_803EEFF0
lbl_803EEFF0:
	.incbin "baserom.dol", 0x3EBFF0, 0xB8
.global lbl_803EF0A8
lbl_803EF0A8:
	.incbin "baserom.dol", 0x3EC0A8, 0x18
.global lbl_803EF0C0
lbl_803EF0C0:
	.incbin "baserom.dol", 0x3EC0C0, 0xC
.global lbl_803EF0CC
lbl_803EF0CC:
	.incbin "baserom.dol", 0x3EC0CC, 0x3C
.global lbl_803EF108
lbl_803EF108:
	.incbin "baserom.dol", 0x3EC108, 0x498
.global lbl_803EF5A0
lbl_803EF5A0:
	.incbin "baserom.dol", 0x3EC5A0, 0xC
.global lbl_803EF5AC
lbl_803EF5AC:
	.incbin "baserom.dol", 0x3EC5AC, 0xBC
.global lbl_803EF668
lbl_803EF668:
	.incbin "baserom.dol", 0x3EC668, 0xC
.global lbl_803EF674
lbl_803EF674:
	.incbin "baserom.dol", 0x3EC674, 0xC
.global lbl_803EF680
lbl_803EF680:
	.incbin "baserom.dol", 0x3EC680, 0xC0
.global lbl_803EF740
lbl_803EF740:
	.incbin "baserom.dol", 0x3EC740, 0xC
.global lbl_803EF74C
lbl_803EF74C:
	.incbin "baserom.dol", 0x3EC74C, 0xC
.global lbl_803EF758
lbl_803EF758:
	.incbin "baserom.dol", 0x3EC758, 0x30
.global lbl_803EF788
lbl_803EF788:
    .asciz "translate"
    .balign 4
.global lbl_803EF794
lbl_803EF794:
    .asciz "%s:%s %s"
    .balign 4
.global lbl_803EF7A0
lbl_803EF7A0:
	.incbin "baserom.dol", 0x3EC7A0, 0xD0
.global lbl_803EF870
lbl_803EF870:
	.incbin "baserom.dol", 0x3EC870, 0x30
.global lbl_803EF8A0
lbl_803EF8A0:
	.incbin "baserom.dol", 0x3EC8A0, 0xC
.global lbl_803EF8AC
lbl_803EF8AC:
	.incbin "baserom.dol", 0x3EC8AC, 0x1DC
.global lbl_803EFA88
lbl_803EFA88:
	.incbin "baserom.dol", 0x3ECA88, 0x18
.global lbl_803EFAA0
lbl_803EFAA0:
	.incbin "baserom.dol", 0x3ECAA0, 0xC
.global lbl_803EFAAC
lbl_803EFAAC:
	.incbin "baserom.dol", 0x3ECAAC, 0x3C
.global jtbl_803EFAE8
jtbl_803EFAE8:
	.incbin "baserom.dol", 0x3ECAE8, 0x28
.global jtbl_803EFB10
jtbl_803EFB10:
	.incbin "baserom.dol", 0x3ECB10, 0xF8
.global lbl_803EFC08
lbl_803EFC08:
	.incbin "baserom.dol", 0x3ECC08, 0xE0
.global lbl_803EFCE8
lbl_803EFCE8:
	.incbin "baserom.dol", 0x3ECCE8, 0x480
.global lbl_803F0168
lbl_803F0168:
    .asciz "mnsnap.c"
    .balign 4
    .asciz "jobj->u.dobj"
    .balign 4
    .asciz "jobj->u.dobj->mobj"
    .balign 4
    .asciz "jobj->u.dobj->mobj->tobj"
    .balign 4
    .asciz "jobj->u.dobj->mobj->tobj->imagedesc"
    .balign 4
    .asciz "jobj->u.dobj->next"
    .balign 4
    .asciz "jobj->u.dobj->next->next"
    .balign 4
    .asciz "jobj->u.dobj->next->next->mobj"
    .balign 4
    .asciz "jobj->u.dobj->next->next->mobj->tobj"
    .balign 4
    .asciz "jobj->u.dobj->next->next->mobj->tobj->imagedesc"
    .balign 4
    .asciz "translate"
    .balign 4
.global jtbl_803F028C
jtbl_803F028C:
	.incbin "baserom.dol", 0x3ED28C, 0x2E4
.global lbl_803F0570
lbl_803F0570:
    .asciz "MvOmake15.mth"
    .balign 4
.global lbl_803F0580
lbl_803F0580:
    .asciz "MvHowTo.mth"
    .balign 4
    .asciz "Can't get user_data.\n"
    .balign 4
    .asciz "mngallery.c"
    .balign 4
    .asciz "user_data"
    .balign 4
    .asciz "cursor_user_data"
    .balign 4
    .asciz "MenMainConGa_Top_joint"
    .balign 4
    .asciz "MenMainConGa_Top_animjoint"
    .balign 4
    .asciz "MenMainConGa_Top_matanim_joint"
    .balign 4
    .asciz "MenMainConGa_Top_shapeanim_joint"
    .balign 4
    .asciz "MenMainCursorGa_Top_joint"
    .balign 4
    .asciz "MenMainCursorGa_Top_animjoint"
    .balign 4
    .asciz "MenMainCursorGa_Top_matanim_joint"
    .balign 4
    .asciz "MenMainCursorGa_Top_shapeanim_joint"
    .balign 4
    .incbin "baserom.dol", 0x3ED6CC, 0x4
.global lbl_803F06D0
lbl_803F06D0:
	.incbin "baserom.dol", 0x3ED6D0, 0x378
.global lbl_803F0A48
lbl_803F0A48:
	.incbin "baserom.dol", 0x3EDA48, 0x3B4
.global lbl_803F0DFC
lbl_803F0DFC:
	.incbin "baserom.dol", 0x3EDDFC, 0x1D0
.global jtbl_803F0FCC
jtbl_803F0FCC:
	.incbin "baserom.dol", 0x3EDFCC, 0xD4
.global jtbl_803F10A0
jtbl_803F10A0:
	.incbin "baserom.dol", 0x3EE0A0, 0x34
.global lbl_803F10D4
lbl_803F10D4:
	.incbin "baserom.dol", 0x3EE0D4, 0xDC
.global lbl_803F11B0
lbl_803F11B0:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803F11D8
lbl_803F11D8:
    .asciz "translate"
    .balign 4
.global jtbl_803F11E4
jtbl_803F11E4:
	.incbin "baserom.dol", 0x3EE1E4, 0x34
.global jtbl_803F1218
jtbl_803F1218:
	.incbin "baserom.dol", 0x3EE218, 0x34
.global jtbl_803F124C
jtbl_803F124C:
	.incbin "baserom.dol", 0x3EE24C, 0x34
.global lbl_803F1280
lbl_803F1280:
    .asciz "not found zako model data! check ground dat file!\n"
    .balign 4
.global lbl_803F12B4
lbl_803F12B4:
    .asciz "===== Not Found Item_Struct!! =====\n"
    .balign 4
    .incbin "baserom.dol", 0x3EE2DC, 0x4
.global jtbl_803F12E0
jtbl_803F12E0:
	.incbin "baserom.dol", 0x3EE2E0, 0x80
.global lbl_803F1360
lbl_803F1360:
    .asciz "damage log over %d!!\n"
    .balign 4
.global lbl_803F1378
lbl_803F1378:
    .asciz "itcoll.c"
    .balign 4
.global lbl_803F1384
lbl_803F1384:
	.incbin "baserom.dol", 0x3EE384, 0x94
.global lbl_803F1418
lbl_803F1418:
	.incbin "baserom.dol", 0x3EE418, 0xAC

    .balign 4
.global lbl_803F14C4
lbl_803F14C4:
    .4byte 0x803F5468
    .4byte 0x8027CF00
    .4byte NULL
    .4byte 0x8027D1D4
    .4byte 0x8027D208
    .4byte 0x8027D230
    .4byte 0x8027D338
    .4byte 0x8027D414
    .4byte 0x8027D450
    .4byte 0x8027D4F4
    .4byte 0x8027D4B8
    .4byte NULL
    .4byte 0x8027D614
    .4byte 0x8027D530
    .4byte 0x8027D650
    .4byte 0x803F5850
    .4byte 0x802861CC
    .4byte 0x80286208
    .4byte 0x80286780
    .4byte 0x80286964
    .4byte 0x802867B4
    .4byte 0x80286CB4
    .4byte 0x80286F04
    .4byte 0x80286FC8
    .4byte 0x80286E70
    .4byte 0x80286D48
    .4byte NULL
    .4byte NULL
    .4byte 0x80286DDC
    .4byte 0x80287084
    .4byte 0x803F58E0
    .4byte 0x80287458
    .4byte NULL
    .4byte 0x80287E68
    .4byte 0x80287EA8
    .4byte 0x80287EC8
    .4byte 0x80288818
    .4byte 0x80288A98
    .4byte NULL
    .4byte 0x802889F8
    .4byte 0x802888B8
    .4byte NULL
    .4byte NULL
    .4byte 0x80288958
    .4byte 0x80288C68
    .4byte 0x803F5988
    .4byte 0x80288D98
    .4byte NULL
    .4byte 0x80288F88
    .4byte 0x80288FBC
    .4byte 0x80288FDC
    .4byte 0x80289218
    .4byte 0x802895A8
    .4byte 0x80289644
    .4byte 0x8028950C
    .4byte 0x802893D4
    .4byte NULL
    .4byte NULL
    .4byte 0x80289470
    .4byte 0x802896AC
    .4byte 0x803F59F8
    .4byte 0x80289784
    .4byte NULL
    .4byte 0x8028A93C
    .4byte 0x8028AB28
    .4byte 0x8028A970
    .4byte 0x8028AEA4
    .4byte 0x8028AFC4
    .4byte NULL
    .4byte 0x8028AF8C
    .4byte 0x8028AF1C
    .4byte NULL
    .4byte NULL
    .4byte 0x8028AF54
    .4byte 0x8028B06C
    .4byte 0x803F63C0
    .4byte 0x80296120
    .4byte 0x802960E0
    .4byte 0x8029683C
    .4byte 0x802968D8
    .4byte 0x80296930
    .4byte 0x8029789C
    .4byte NULL
    .4byte NULL
    .4byte 0x802978B4
    .4byte 0x802978A4
    .4byte NULL
    .4byte NULL
    .4byte 0x802978AC
    .4byte 0x802978BC
    .4byte 0x803F54D8
    .4byte 0x8027D76C
    .4byte NULL
    .4byte 0x8027E0B4
    .4byte 0x8027E648
    .4byte 0x80280380
    .4byte 0x80280DF0
    .4byte 0x80280E30
    .4byte 0x80280E9C
    .4byte 0x802810A4
    .4byte 0x80281070
    .4byte NULL
    .4byte 0x80281104
    .4byte 0x802810C4
    .4byte 0x80281144
    .4byte 0x803F55D0
    .4byte 0x80281164
    .4byte NULL
    .4byte 0x8028218C
    .4byte 0x802826F8
    .4byte 0x802829FC
    .4byte 0x802839BC
    .4byte 0x80283588
    .4byte 0x80282B14
    .4byte 0x80283A3C
    .4byte 0x80283A5C
    .4byte NULL
    .4byte 0x80283AA4
    .4byte 0x80283A80
    .4byte 0x80283AC4
    .4byte 0x803F56C8
    .4byte 0x80283BEC
    .4byte 0x80283C48
    .4byte 0x80283F28
    .4byte 0x8028402C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8028412C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80284194
    .4byte 0x803F5740
    .4byte 0x802842A4
    .4byte 0x80284324
    .4byte 0x802844E4
    .4byte 0x8028454C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802845BC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80284624
    .4byte 0x803F57A0
    .4byte 0x80284644
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8028482C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80284834
    .4byte 0x803F57B0
    .4byte 0x80284910
    .4byte NULL
    .4byte 0x80284AAC
    .4byte 0x80284B30
    .4byte 0x80284BA0
    .4byte 0x80284C78
    .4byte NULL
    .4byte 0x80284C10
    .4byte 0x80284CAC
    .4byte 0x80284CCC
    .4byte NULL
    .4byte 0x80284D14
    .4byte 0x80284CF0
    .4byte 0x80284D34
    .4byte 0x803F5800
    .4byte 0x80285338
    .4byte NULL
    .4byte 0x80285804
    .4byte 0x80285B00
    .4byte 0x80285C78
    .4byte 0x80285FAC
    .4byte NULL
    .4byte 0x80285DF0
    .4byte 0x80285FE0
    .4byte 0x80286000
    .4byte NULL
    .4byte 0x80286048
    .4byte 0x80286024
    .4byte 0x80286068
    .4byte 0x803F5AB0
    .4byte 0x8028B0B8
    .4byte NULL
    .4byte 0x8028B5E8
    .4byte 0x8028B3C0
    .4byte 0x8028B3E0
    .4byte 0x8028B4D4
    .4byte NULL
    .4byte 0x8028B580
    .4byte 0x8028B540
    .4byte 0x8028B4F8
    .4byte NULL
    .4byte 0x8028B560
    .4byte 0x8028B51C
    .4byte 0x8028B8B8
    .4byte 0x803F5BA8
    .4byte 0x8028BDAC
    .4byte NULL
    .4byte 0x8028C148
    .4byte 0x8028C300
    .4byte 0x8028C1AC
    .4byte 0x8028CCA8
    .4byte 0x8028CCCC
    .4byte 0x8028CB24
    .4byte 0x8028CD04
    .4byte 0x8028CD3C
    .4byte NULL
    .4byte 0x8028CF2C
    .4byte 0x8028CE1C
    .4byte 0x8028CFC0
    .4byte 0x803F5C48
    .4byte 0x8028D59C
    .4byte NULL
    .4byte 0x8028D898
    .4byte 0x8028D9F4
    .4byte 0x8028D8E0
    .4byte 0x8028E540
    .4byte 0x8028E584
    .4byte 0x8028E3CC
    .4byte 0x8028E5C8
    .4byte 0x8028E600
    .4byte NULL
    .4byte 0x8028E684
    .4byte 0x8028E624
    .4byte 0x8028E718
    .4byte 0x803F5CC8
    .4byte 0x8028E738
    .4byte NULL
    .4byte 0x8028E904
    .4byte 0x8028E9B8
    .4byte 0x8028E9E0
    .4byte 0x8028EA54
    .4byte NULL
    .4byte 0x8028EB00
    .4byte 0x8028EAC0
    .4byte 0x8028EA78
    .4byte NULL
    .4byte 0x8028EAE0
    .4byte 0x8028EA9C
    .4byte 0x8028EB68
    .4byte 0x803F5D28
    .4byte 0x8028ED50
    .4byte 0x8028ED10
    .4byte 0x8028F2B4
    .4byte 0x8028F318
    .4byte 0x8028F340
    .4byte 0x8028F3CC
    .4byte 0x8028F42C
    .4byte NULL
    .4byte 0x8028F3EC
    .4byte 0x8028F3D4
    .4byte 0x8028F3E4
    .4byte 0x8028F40C
    .4byte 0x8028F3DC
    .4byte 0x8028F8C4
    .4byte 0x803F5DB0
    .4byte 0x8028FBE4
    .4byte NULL
    .4byte 0x8028FD7C
    .4byte 0x8028FDE4
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8028FE70
    .4byte 0x803F5E00
    .4byte 0x8028FED4
    .4byte NULL
    .4byte 0x802900CC
    .4byte 0x802900F4
    .4byte 0x80290114
    .4byte 0x802906E4
    .4byte 0x80290738
    .4byte 0x80290794
    .4byte 0x80290830
    .4byte 0x802907F0
    .4byte NULL
    .4byte 0x802908A4
    .4byte 0x80290850
    .4byte 0x80290918
    .4byte 0x803F5EA8
    .4byte 0x80290A20
    .4byte NULL
    .4byte 0x80290F8C
    .4byte 0x80290FC0
    .4byte 0x80290FE0
    .4byte 0x802915E8
    .4byte 0x802919B8
    .4byte 0x80291B58
    .4byte 0x80291978
    .4byte 0x802917C8
    .4byte NULL
    .4byte 0x80291998
    .4byte 0x802918A0
    .4byte 0x80291BC0
    .4byte 0x803F5F40
    .4byte 0x80291C98
    .4byte NULL
    .4byte 0x8029215C
    .4byte 0x80292190
    .4byte 0x802921B8
    .4byte 0x8029222C
    .4byte NULL
    .4byte 0x802922D8
    .4byte 0x80292298
    .4byte 0x80292250
    .4byte NULL
    .4byte 0x802922B8
    .4byte 0x80292274
    .4byte 0x80292340
    .4byte 0x803F5F90
    .4byte 0x80292360
    .4byte NULL
    .4byte 0x80292514
    .4byte 0x80292548
    .4byte 0x802925B4
    .4byte 0x8029266C
    .4byte NULL
    .4byte 0x802926A8
    .4byte 0x8029274C
    .4byte 0x80292710
    .4byte NULL
    .4byte 0x802927A8
    .4byte 0x8029276C
    .4byte 0x802927C8
    .4byte 0x803F6310
    .4byte 0x8029570C
    .4byte NULL
    .4byte 0x802958C8
    .4byte 0x80295908
    .4byte 0x80295974
    .4byte 0x80295ACC
    .4byte NULL
    .4byte 0x80295B08
    .4byte 0x80295BAC
    .4byte 0x80295B70
    .4byte NULL
    .4byte 0x80295C08
    .4byte 0x80295BCC
    .4byte 0x80295C28
    .4byte 0x803F5FF0
    .4byte 0x8029285C
    .4byte NULL
    .4byte 0x80292A5C
    .4byte 0x80292A90
    .4byte 0x80292B2C
    .4byte 0x80292BCC
    .4byte NULL
    .4byte 0x80292C08
    .4byte 0x80292CAC
    .4byte 0x80292C70
    .4byte NULL
    .4byte 0x80292D08
    .4byte 0x80292CCC
    .4byte 0x80292D28
    .4byte 0x803F6090
    .4byte 0x80292E04
    .4byte NULL
    .4byte 0x80293284
    .4byte 0x802933C4
    .4byte 0x802933EC
    .4byte 0x80293488
    .4byte NULL
    .4byte 0x80293534
    .4byte 0x802934F4
    .4byte 0x802934AC
    .4byte NULL
    .4byte 0x80293514
    .4byte 0x802934D0
    .4byte 0x80293640
    .4byte 0x803F6110
    .4byte 0x8029367C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802939E0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802939E8
    .4byte 0x803F6130
    .4byte 0x80293A08
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80293D6C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80293D74
    .4byte 0x803F6150
    .4byte 0x80293F58
    .4byte NULL
    .4byte 0x802940FC
    .4byte 0x802941F8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802942B0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80294344
    .4byte 0x803F61B0
    .4byte 0x8029451C
    .4byte NULL
    .4byte 0x80294728
    .4byte 0x80294790
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80294A28
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80294A90
    .4byte 0x803F6220
    .4byte 0x80294AB0
    .4byte NULL
    .4byte 0x80294BE4
    .4byte 0x80294C14
    .4byte 0x80294C3C
    .4byte 0x80294D4C
    .4byte NULL
    .4byte 0x80294CE4
    .4byte 0x80294D5C
    .4byte 0x80294D54
    .4byte NULL
    .4byte 0x80294DA0
    .4byte 0x80294D7C
    .4byte 0x80294A90
    .4byte 0x803F6270
    .4byte 0x80295118
    .4byte NULL
    .4byte 0x8029524C
    .4byte 0x80295298
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80295340
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802953A8
    .4byte 0x803F62C0
    .4byte 0x802953C8
    .4byte NULL
    .4byte 0x80295524
    .4byte 0x80295554
    .4byte NULL
    .4byte NULL
    .4byte 0x802955E0
    .4byte 0x80295684
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802956EC
    .4byte 0x803F6370
    .4byte 0x80295C48
    .4byte NULL
    .4byte 0x80295D90
    .4byte 0x80295DC0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80295E4C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80295EB4
    .4byte 0x803F6488
    .4byte 0x80297904
    .4byte 0x802978DC
    .4byte 0x80297ABC
    .4byte 0x80297AF0
    .4byte 0x80297B18
    .4byte 0x80297BB8
    .4byte NULL
    .4byte 0x80297BF8
    .4byte 0x802980A0
    .4byte 0x80298060
    .4byte NULL
    .4byte 0x80298114
    .4byte 0x802980D4
    .4byte 0x80298148
    .4byte 0x803F64F8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80298634
    .4byte NULL
    .4byte NULL
    .4byte 0x80298654
    .4byte 0x8029863C
    .4byte 0x8029864C
    .4byte 0x80298828
    .4byte 0x80298644
    .4byte 0x802988C4
    .4byte 0x803F6530
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80298BE4
    .4byte NULL
    .4byte NULL
    .4byte 0x80298C04
    .4byte 0x80298BEC
    .4byte 0x80298BFC
    .4byte 0x80298CE8
    .4byte 0x80298BF4
    .4byte 0x80298DCC
    .4byte 0x803F6680
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8029A600
    .4byte NULL
    .4byte NULL
    .4byte 0x8029A620
    .4byte 0x8029A608
    .4byte 0x8029A618
    .4byte 0x8029A704
    .4byte 0x8029A610
    .4byte 0x8029A728
    .4byte 0x803F6568
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80299360
    .4byte NULL
    .4byte NULL
    .4byte 0x802993A0
    .4byte 0x80299368
    .4byte 0x80299378
    .4byte 0x80299380
    .4byte 0x80299370
    .4byte 0x802993C0
    .4byte 0x803F6630
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x80299B6C
    .4byte NULL
    .4byte NULL
    .4byte 0x80299B74
    .4byte 0x80299C08
    .4byte 0x80299C10
    .4byte 0x80299C18
    .4byte 0x80299C20
    .4byte 0x80299C28
    .4byte 0x803F6640
    .4byte 0x80299D4C
    .4byte NULL
    .4byte 0x80299DD0
    .4byte 0x80299E28
    .4byte 0x80299E48
    .4byte 0x8029A0B0
    .4byte 0x8029A0EC
    .4byte NULL
    .4byte 0x8029A0C8
    .4byte 0x8029A0B8
    .4byte NULL
    .4byte NULL
    .4byte 0x8029A0C0
    .4byte 0x8029A0F4
    .4byte 0x803F66C8
    .4byte 0x8029A9FC
    .4byte NULL
    .4byte 0x8029AD1C
    .4byte 0x8029AD94
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8029AF34
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8029B0A8
    .4byte 0x803F6728
    .4byte 0x8029B1AC
    .4byte 0x8029B188
    .4byte 0x8029B2F4
    .4byte 0x8029B328
    .4byte 0x8029B348
    .4byte 0x8029B46C
    .4byte 0x8029B56C
    .4byte 0x8029B670
    .4byte 0x8029B52C
    .4byte 0x8029B4AC
    .4byte NULL
    .4byte NULL
    .4byte 0x8029B4EC
    .4byte 0x8029B6D8

.global lbl_803F1ED8
lbl_803F1ED8:
    .asciz "ItCo.dat"
    .balign 4
.global lbl_803F1EE4
lbl_803F1EE4:
    .asciz "ItCo.usd"
    .balign 4
.global lbl_803F1EF0
lbl_803F1EF0:
    .asciz "itPublicData"
    .balign 4
.global lbl_803F1F00
lbl_803F1F00:
    .asciz "translate"
    .balign 4
.global lbl_803F1F0C
lbl_803F1F0C:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3EEF34, 0x4
.global lbl_803F1F38
lbl_803F1F38:
    .asciz "couldn't get Owner_GObj_Kind!!"
    .balign 4
.global lbl_803F1F58
lbl_803F1F58:
    .asciz "itmaplib.c"
    .balign 4
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3EEF8C, 0x4
.global lbl_803F1F90
lbl_803F1F90:
	.incbin "baserom.dol", 0x3EEF90, 0x150
.global jtbl_803F20E0
jtbl_803F20E0:
	.incbin "baserom.dol", 0x3EF0E0, 0x1C8
.global lbl_803F22A8
lbl_803F22A8:
	.incbin "baserom.dol", 0x3EF2A8, 0x40
.global lbl_803F22E8
lbl_803F22E8:
    .asciz "item can't set attack!\n"
    .balign 4
.global lbl_803F2300
lbl_803F2300:
    .asciz "itanimlist.c"
    .balign 4
.global lbl_803F2310
lbl_803F2310:
	.incbin "baserom.dol", 0x3EF310, 0xBC
.global lbl_803F23CC
lbl_803F23CC:
    .4byte 0x803F7A48
    .4byte 0x802C8F4C
    .4byte 0x802C9504
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C8FC4
    .4byte 0x803F7A98
    .4byte 0x802C9588
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C961C
    .4byte 0x803F7AD8
    .4byte 0x802C9D40
    .4byte 0x802C9E00
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C9E24
    .4byte 0x803F7B08
    .4byte 0x802CA49C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CA538
    .4byte 0x803F7B58
    .4byte 0x802CAFD4
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CB0F8
    .4byte 0x803F7BC0
    .4byte 0x802CB8AC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CB940
    .4byte 0x803F7C10
    .4byte 0x802CC6E4
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CC744
    .4byte 0x803F7C40
    .4byte 0x802CCAB4
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CCB14
    .4byte 0x803F7C70
    .4byte 0x802CCF9C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CD000
    .4byte 0x803F7CA0
    .4byte 0x802CD44C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CD7B8
    .4byte 0x802CD7D4
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CD4DC
    .4byte 0x803F7CF8
    .4byte 0x802CDBE0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CDC60
    .4byte 0x803F7D60
    .4byte 0x802CE710
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CE7D0
    .4byte 0x803F7DC8
    .4byte 0x802CF3E0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CF450
    .4byte 0x803F7DE8
    .4byte 0x802CF814
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CF884
    .4byte 0x803F7E08
    .4byte 0x802CFC48
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CFCB8
    .4byte 0x803F7E28
    .4byte 0x802D007C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D0118
    .4byte 0x803F7E78
    .4byte 0x802D0A0C
    .4byte NULL
    .4byte 0x802D0D18
    .4byte 0x802D0E30
    .4byte 0x802D0E90
    .4byte 0x802D0AD0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D0AB0
    .4byte 0x803F7EE8
    .4byte 0x802D1438
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D14D4
    .4byte 0x803F7F58
    .4byte 0x802D251C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D25BC
    .4byte 0x803F7FC8
    .4byte 0x802D3008
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D3070
    .4byte 0x803F7FF8
    .4byte 0x802D3260
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D32DC
    .4byte 0x803F8058
    .4byte 0x802D36B0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D372C
    .4byte 0x803F80C8
    .4byte 0x802D3B18
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D3B6C
    .4byte 0x803F80F8
    .4byte 0x802D3EF8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D3F4C
    .4byte 0x803F8128
    .4byte 0x802D42C4
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D43B0
    .4byte 0x803F8190
    .4byte 0x802D5050
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D5648
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D56F0
    .4byte 0x803F8250
    .4byte 0x802D5ABC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D5CD8
    .4byte 0x803F8270
    .4byte 0x802D5CF8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D6100
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D61A8
    .4byte 0x803F82B0
    .4byte 0x802D6870
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D6F00
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D6FB0
    .4byte 0x803F82F0
    .4byte 0x802D6FD0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D73D0
    .4byte 0x803F7AC8
    .4byte 0x802C9C20
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C9C78
    .4byte NULL
    .4byte NULL
    .4byte 0x802C9CA0
    .4byte 0x802C9C78
    .4byte 0x802C9C78
    .4byte NULL
    .4byte 0x802C9C78
    .4byte 0x802C9C80
    .4byte 0x803F7B48
    .4byte 0x802CACD0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CADC8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CADC0
    .4byte 0x802CADD0
    .4byte 0x803F7BB0
    .4byte 0x802CB690
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CB778
    .4byte 0x803F7BB0
    .4byte 0x802CB704
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CB778
    .4byte 0x803F7C00
    .4byte 0x802CC3D4
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CC5A4
    .4byte NULL
    .4byte 0x802CC5CC
    .4byte NULL
    .4byte 0x802CC5C4
    .4byte 0x802CC584
    .4byte 0x803F7C00
    .4byte 0x802CC440
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CC5A4
    .4byte NULL
    .4byte 0x802CC5CC
    .4byte NULL
    .4byte 0x802CC5C4
    .4byte 0x802CC584
    .4byte 0x803F7C00
    .4byte 0x802CC4AC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CC5A4
    .4byte NULL
    .4byte 0x802CC5CC
    .4byte NULL
    .4byte 0x802CC5C4
    .4byte 0x802CC584
    .4byte 0x803F7C00
    .4byte 0x802CC518
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CC5A4
    .4byte NULL
    .4byte 0x802CC5CC
    .4byte NULL
    .4byte 0x802CC5C4
    .4byte 0x802CC584
    .4byte 0x803F7D90
    .4byte 0x802CEEC8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802CF0B4
    .4byte 0x803F7F48
    .4byte 0x802D2308
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D23D4
    .4byte 0x803F7F48
    .4byte 0x802D234C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D23D4
    .4byte 0x803F7F48
    .4byte 0x802D2390
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D23D4
    .4byte 0x803F7FB8
    .4byte 0x802D2E80
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D2ED0
    .4byte 0x803F8180
    .4byte 0x802D4DE0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D4EF4
    .4byte NULL
    .4byte NULL
    .4byte 0x802D4F28
    .4byte NULL
    .4byte 0x802D4F48
    .4byte 0x802D4F08
    .4byte 0x802D4F50
    .4byte 0x802D4F58
    .4byte 0x803F8200
    .4byte 0x802D57D0
    .4byte NULL
    .4byte 0x802D59A8
    .4byte 0x802D59DC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D5A04
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D5A9C
    .4byte 0x803F82A0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D6808
    .4byte NULL
    .4byte NULL
    .4byte 0x802D6810
    .4byte 0x802D6830
    .4byte 0x802D6838
    .4byte 0x802D6840
    .4byte 0x802D6848
    .4byte 0x802D6850
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL

    .4byte 0x000000A1
    .4byte 0x000000A2
    .4byte 0x000000A3
    .4byte 0x000000A4
    .4byte 0x000000A5
    .4byte 0x000000A6
    .4byte 0x000000AA
    .4byte 0x000000AB
    .4byte 0x000000AC
    .4byte 0x000000B0
    .4byte 0x000000B1
    .4byte 0x000000B4
    .4byte 0x000000B5
    .4byte 0x000000B6
    .4byte 0x000000B9
    .4byte 0x000000BA
    .4byte 0x000000BB
    .4byte 0x000000BC
    .4byte 0x000000BD
    .4byte 0x000000BE
    .4byte 0x000000BF
    .4byte 0x00000000

.global lbl_803F2F28
lbl_803F2F28:
	.incbin "baserom.dol", 0x3EFF28, 0x1D8

    .balign 4
.global lbl_803F3100
lbl_803F3100:
    .4byte 0x803F8320
    .4byte 0x802D73F0
    .4byte 0x8027C8B0
    .4byte 0x802D7C14
    .4byte 0x802D7CB4
    .4byte 0x802D7D18
    .4byte NULL
    .4byte 0x802D7F38
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x803F8EB0
    .4byte 0x802E8BCC
    .4byte 0x802EA41C
    .4byte 0x802EA0E0
    .4byte 0x802EA154
    .4byte 0x802EA1B4
    .4byte NULL
    .4byte 0x802E8CD8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x803F8B48
    .4byte 0x802E4A44
    .4byte 0x8027C8B0
    .4byte 0x802E561C
    .4byte 0x802E5690
    .4byte 0x802E56E8
    .4byte NULL
    .4byte 0x802E4B00
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802E5AA4
    .4byte 0x803F89C8
    .4byte 0x802E2470
    .4byte 0x802E34DC
    .4byte 0x802E31F8
    .4byte 0x802E32B4
    .4byte 0x802E3314
    .4byte NULL
    .4byte 0x802E257C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802E3784
    .4byte 0x803F8E90
    .4byte 0x802E878C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802E87D8
    .4byte NULL
    .4byte NULL
    .4byte 0x802E87F8
    .4byte 0x802E87E0
    .4byte 0x802E87F0
    .4byte 0x802E881C
    .4byte 0x802E87E8
    .4byte 0x802E89B0
    .4byte 0x803F6788
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8029BA38
    .4byte NULL
    .4byte NULL
    .4byte 0x8029BA40
    .4byte 0x8029BA60
    .4byte 0x8029BA70
    .4byte 0x8029BA78
    .4byte 0x8029BA68
    .4byte 0x8029BA98
    .4byte 0x803F75D0
    .4byte NULL
    .4byte NULL
    .4byte 0x802C11E0
    .4byte NULL
    .4byte NULL
    .4byte 0x802C1384
    .4byte NULL
    .4byte NULL
    .4byte 0x802C13CC
    .4byte 0x802C1400
    .4byte 0x802C14B8
    .4byte 0x802C1514
    .4byte 0x802C145C
    .4byte 0x802C1570
    .4byte 0x803F6798
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8029BFB4
    .4byte NULL
    .4byte NULL
    .4byte 0x8029BFCC
    .4byte 0x8029BFBC
    .4byte 0x8029BFC4
    .4byte 0x8029C208
    .4byte 0x8029C4AC
    .4byte 0x8029C4B4
    .4byte 0x803F6C98
    .4byte NULL
    .4byte 0x802ADC04
    .4byte 0x802ADD88
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802ADDB0
    .4byte 0x803F6C88
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802ADBE4
    .4byte 0x803F9470
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802F2BDC
    .4byte 0x803F67D0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8029CA78
    .4byte NULL
    .4byte NULL
    .4byte 0x8029CA80
    .4byte 0x8029CA78
    .4byte 0x8029CC4C
    .4byte 0x8029CC54
    .4byte 0x8029CCF0
    .4byte 0x8029CCF8
    .4byte 0x803F67D0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8029CA78
    .4byte NULL
    .4byte NULL
    .4byte 0x8029CA80
    .4byte 0x8029CA78
    .4byte 0x8029CC4C
    .4byte 0x8029CC54
    .4byte 0x8029CCF0
    .4byte 0x8029CCF8
    .4byte 0x803F6818
    .4byte NULL
    .4byte 0x8029CFA0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8029CF8C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8029D948
    .4byte 0x803F6818
    .4byte NULL
    .4byte 0x8029CFA0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8029CF8C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8029D948
    .4byte 0x803F6888
    .4byte NULL
    .4byte NULL
    .4byte 0x8029DEB0
    .4byte 0x8029EC34
    .4byte 0x8029E5D0
    .4byte 0x8029F960
    .4byte 0x8029FA30
    .4byte 0x8029FB24
    .4byte 0x8029FD20
    .4byte NULL
    .4byte NULL
    .4byte 0x8029FD64
    .4byte 0x8029FD40
    .4byte 0x8029FD84
    .4byte 0x803F6888
    .4byte NULL
    .4byte NULL
    .4byte 0x8029DEB0
    .4byte 0x8029EC34
    .4byte 0x8029E5D0
    .4byte 0x8029F960
    .4byte 0x8029FA30
    .4byte 0x8029FB24
    .4byte 0x8029FD20
    .4byte NULL
    .4byte NULL
    .4byte 0x8029FD64
    .4byte 0x8029FD40
    .4byte 0x8029FD84
    .4byte 0x803F6920
    .4byte NULL
    .4byte 0x802A087C
    .4byte 0x802A0E70
    .4byte 0x802A0F84
    .4byte 0x802A0F88
    .4byte 0x802A1F08
    .4byte NULL
    .4byte NULL
    .4byte 0x802A20E8
    .4byte 0x802A1FA8
    .4byte 0x802A2048
    .4byte 0x802A2320
    .4byte 0x802A2288
    .4byte 0x802A23CC
    .4byte 0x803F6920
    .4byte NULL
    .4byte 0x802A087C
    .4byte 0x802A0E70
    .4byte 0x802A0F84
    .4byte 0x802A0F88
    .4byte 0x802A1F08
    .4byte NULL
    .4byte NULL
    .4byte 0x802A20E8
    .4byte 0x802A1FA8
    .4byte 0x802A2048
    .4byte 0x802A2320
    .4byte 0x802A2288
    .4byte 0x802A23CC
    .4byte 0x803F6998
    .4byte 0x802A2418
    .4byte NULL
    .4byte 0x802A7688
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802A7D40
    .4byte 0x803F6998
    .4byte NULL
    .4byte NULL
    .4byte 0x802A7688
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802A7D40
    .4byte 0x803F6A28
    .4byte NULL
    .4byte 0x802A8984
    .4byte 0x802A8AF8
    .4byte NULL
    .4byte NULL
    .4byte 0x802A9A80
    .4byte NULL
    .4byte NULL
    .4byte 0x802A9D4C
    .4byte 0x802A9CE0
    .4byte NULL
    .4byte NULL
    .4byte 0x802A9B08
    .4byte 0x802AA034
    .4byte 0x803F6A28
    .4byte NULL
    .4byte 0x802A8984
    .4byte 0x802A8AF8
    .4byte NULL
    .4byte NULL
    .4byte 0x802A9A80
    .4byte NULL
    .4byte NULL
    .4byte 0x802A9D4C
    .4byte 0x802A9CE0
    .4byte NULL
    .4byte NULL
    .4byte 0x802A9B08
    .4byte 0x802AA034
    .4byte 0x803F6B28
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802AA284
    .4byte NULL
    .4byte NULL
    .4byte 0x802AA35C
    .4byte 0x802AA2E8
    .4byte 0x802AA34C
    .4byte 0x802AA37C
    .4byte 0x802AA354
    .4byte 0x802AA474
    .4byte 0x803F6B60
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802AA75C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802AA7C4
    .4byte 0x803F6B70
    .4byte NULL
    .4byte 0x802AA9CC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802AB2AC
    .4byte 0x802AB3C0
    .4byte 0x802AB3C8
    .4byte NULL
    .4byte NULL
    .4byte 0x802AB3D0
    .4byte 0x803F6BC8
    .4byte NULL
    .4byte 0x802AB90C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802AC050
    .4byte NULL
    .4byte NULL
    .4byte 0x802AC098
    .4byte 0x802AC074
    .4byte 0x802AC338
    .4byte 0x802AC35C
    .4byte 0x802AC3F8
    .4byte 0x802AC41C
    .4byte 0x803F6C08
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x803F6C08
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x803F6C08
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x803F6C08
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x803F6CA8
    .4byte NULL
    .4byte NULL
    .4byte 0x802AEB00
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802AF184
    .4byte 0x803F6CA8
    .4byte NULL
    .4byte NULL
    .4byte 0x802AEB00
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802AF184
    .4byte 0x803F6E98
    .4byte NULL
    .4byte 0x802AF298
    .4byte 0x802AF434
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802AF920
    .4byte 0x803F6E98
    .4byte NULL
    .4byte 0x802AF298
    .4byte 0x802AF434
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802AF920
    .4byte 0x803F6F40
    .4byte NULL
    .4byte 0x802AFA2C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802AFD4C
    .4byte 0x802AFD54
    .4byte 0x802AFD5C
    .4byte 0x802AFD64
    .4byte 0x802AFD6C
    .4byte 0x803F6F50
    .4byte NULL
    .4byte 0x802AFEF8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B0D84
    .4byte 0x802B10E4
    .4byte NULL
    .4byte 0x802B1294
    .4byte 0x802B0F34
    .4byte NULL
    .4byte 0x802B14DC
    .4byte 0x802B16E4
    .4byte 0x802B1890
    .4byte 0x803F70A8
    .4byte NULL
    .4byte NULL
    .4byte 0x802B1AAC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B1C40
    .4byte 0x803F70C8
    .4byte NULL
    .4byte 0x802B202C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B2508
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B2518
    .4byte 0x802B2520
    .4byte NULL
    .4byte 0x802B2510
    .4byte 0x802B2528
    .4byte 0x803F70C8
    .4byte NULL
    .4byte 0x802B202C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B2508
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B2518
    .4byte 0x802B2520
    .4byte NULL
    .4byte 0x802B2510
    .4byte 0x802B2528
    .4byte 0x803F70F8
    .4byte NULL
    .4byte 0x802B2644
    .4byte 0x802B2700
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B2870
    .4byte 0x803F70F8
    .4byte NULL
    .4byte 0x802B2644
    .4byte 0x802B2700
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B2870
    .4byte 0x803F70B8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B1D38
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B1DCC
    .4byte 0x803F7118
    .4byte NULL
    .4byte NULL
    .4byte 0x802B2AE0
    .4byte NULL
    .4byte NULL
    .4byte 0x802B2C04
    .4byte NULL
    .4byte NULL
    .4byte 0x802B2E5C
    .4byte 0x802B2D50
    .4byte NULL
    .4byte 0x802B2F88
    .4byte 0x802B2E7C
    .4byte 0x802B2FA8
    .4byte 0x803F94A0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802F3330
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802F3374
    .4byte 0x803F7158
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B309C
    .4byte NULL
    .4byte NULL
    .4byte 0x802B314C
    .4byte 0x802B30C0
    .4byte 0x802B3108
    .4byte 0x802B312C
    .4byte 0x802B30E4
    .4byte 0x802B3348
    .4byte 0x803F7190
    .4byte NULL
    .4byte 0x802B34E4
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B3A94
    .4byte NULL
    .4byte NULL
    .4byte 0x802B3AF8
    .4byte 0x802B3C44
    .4byte 0x802B3CA8
    .4byte 0x802B3D70
    .4byte 0x802B3D0C
    .4byte 0x802B3EDC
    .4byte 0x803F71D8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B45F0
    .4byte NULL
    .4byte NULL
    .4byte 0x802B46C8
    .4byte 0x802B4638
    .4byte 0x802B4680
    .4byte 0x802B4A60
    .4byte 0x802B4A18
    .4byte 0x802B4AA8
    .4byte 0x803F7190
    .4byte NULL
    .4byte 0x802B34E4
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B3A94
    .4byte NULL
    .4byte NULL
    .4byte 0x802B3AF8
    .4byte 0x802B3C44
    .4byte 0x802B3CA8
    .4byte 0x802B3D70
    .4byte 0x802B3D0C
    .4byte 0x802B3EDC
    .4byte 0x803F71D8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B45F0
    .4byte NULL
    .4byte NULL
    .4byte 0x802B46C8
    .4byte 0x802B4638
    .4byte 0x802B4680
    .4byte 0x802B4A60
    .4byte 0x802B4A18
    .4byte 0x802B4AA8
    .4byte 0x803F7220
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B52B8
    .4byte NULL
    .4byte 0x802B4F78
    .4byte 0x802B5374
    .4byte 0x802B52EC
    .4byte NULL
    .4byte 0x802B5354
    .4byte 0x802B5320
    .4byte 0x802B54E4
    .4byte 0x803F7288
    .4byte NULL
    .4byte 0x802B58D8
    .4byte 0x802B59C4
    .4byte NULL
    .4byte NULL
    .4byte 0x802B5FD8
    .4byte NULL
    .4byte NULL
    .4byte 0x802B5FF0
    .4byte 0x802B5FE0
    .4byte 0x802B5FE8
    .4byte 0x802B6144
    .4byte 0x802B613C
    .4byte 0x802B62B0
    .4byte 0x803F7340
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B6C28
    .4byte NULL
    .4byte NULL
    .4byte 0x802B6E4C
    .4byte 0x802B6C7C
    .4byte NULL
    .4byte 0x802B6D24
    .4byte 0x802B6CD0
    .4byte 0x802B7104
    .4byte 0x803F73A8
    .4byte 0x802B7150
    .4byte NULL
    .4byte 0x802BA97C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802BAEA0
    .4byte 0x803F7438
    .4byte NULL
    .4byte NULL
    .4byte 0x802BCE94
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802BD10C
    .4byte 0x803F7488
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802BD240
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802BD30C
    .4byte 0x803F74A8
    .4byte NULL
    .4byte 0x802BD47C
    .4byte 0x802BD628
    .4byte 0x802BD8CC
    .4byte 0x802BD748
    .4byte 0x802BD938
    .4byte NULL
    .4byte NULL
    .4byte 0x802BD99C
    .4byte 0x802BD978
    .4byte NULL
    .4byte 0x802BD9E4
    .4byte 0x802BD9C0
    .4byte 0x802BDA08
    .4byte 0x803F6C58
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802AD2E8
    .4byte NULL
    .4byte NULL
    .4byte 0x802AD2F0
    .4byte 0x802AD384
    .4byte 0x802AD38C
    .4byte 0x802AD3B0
    .4byte 0x802AD450
    .4byte 0x802AD458
    .4byte 0x803F6C68
    .4byte NULL
    .4byte NULL
    .4byte 0x802AD6F0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802AD9FC
    .4byte 0x803F7558
    .4byte NULL
    .4byte NULL
    .4byte 0x802BFE34
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C016C
    .4byte 0x803F74F8
    .4byte NULL
    .4byte 0x802BDB4C
    .4byte 0x802BDC74
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802BDDF8
    .4byte 0x803F7528
    .4byte NULL
    .4byte 0x802BDEFC
    .4byte 0x802BDFE0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802BE1F4
    .4byte 0x803F75C0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C0490
    .4byte NULL
    .4byte NULL
    .4byte 0x802C0498
    .4byte 0x802C04B8
    .4byte 0x802C04C8
    .4byte 0x802C04D0
    .4byte 0x802C04C0
    .4byte 0x802C04F0
    .4byte 0x803F7668
    .4byte NULL
    .4byte 0x802C17FC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C1FC8
    .4byte NULL
    .4byte NULL
    .4byte 0x802C1FD0
    .4byte 0x802C1FF0
    .4byte 0x802C20E4
    .4byte 0x802C20EC
    .4byte 0x802C1FF8
    .4byte 0x802C210C
    .4byte 0x803F76A8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C2424
    .4byte NULL
    .4byte NULL
    .4byte 0x802C242C
    .4byte 0x802C244C
    .4byte 0x802C245C
    .4byte 0x802C2464
    .4byte 0x802C2454
    .4byte 0x802C246C
    .4byte 0x803F76F8
    .4byte NULL
    .4byte 0x802C3CBC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C443C
    .4byte 0x802C4550
    .4byte 0x802C4558
    .4byte NULL
    .4byte NULL
    .4byte 0x802C4560
    .4byte 0x803F7740
    .4byte NULL
    .4byte 0x802C4670
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C49A0
    .4byte 0x802C49A8
    .4byte 0x802C49B0
    .4byte 0x802C49B8
    .4byte 0x802C49C0
    .4byte 0x803F7750
    .4byte NULL
    .4byte 0x802C4A00
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C4C90
    .4byte NULL
    .4byte NULL
    .4byte 0x802C4C98
    .4byte 0x802C4CB8
    .4byte 0x802C4CC8
    .4byte 0x802C4CD0
    .4byte 0x802C4CC0
    .4byte 0x802C4CD8
    .4byte 0x803F7548
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802BE488
    .4byte NULL
    .4byte NULL
    .4byte 0x802BE538
    .4byte 0x802BE4AC
    .4byte 0x802BE4F4
    .4byte 0x802BE518
    .4byte 0x802BE4D0
    .4byte 0x802BE578
    .4byte 0x803F7760
    .4byte NULL
    .4byte 0x802C56A0
    .4byte 0x802C578C
    .4byte NULL
    .4byte NULL
    .4byte 0x802C60B4
    .4byte NULL
    .4byte NULL
    .4byte 0x802C60CC
    .4byte 0x802C60BC
    .4byte 0x802C60C4
    .4byte 0x802C6140
    .4byte 0x802C6138
    .4byte 0x802C61D4
    .4byte 0x803F76B8
    .4byte NULL
    .4byte NULL
    .4byte 0x802C37BC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C3AA4
    .4byte 0x803F7898
    .4byte NULL
    .4byte 0x802C62F8
    .4byte 0x802C63B4
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C65C4
    .4byte 0x803F78D8
    .4byte NULL
    .4byte 0x802C66E8
    .4byte 0x802C67A4
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C68D8
    .4byte 0x803F78E8
    .4byte NULL
    .4byte 0x802C69FC
    .4byte 0x802C6AB8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C6C18
    .4byte 0x803F78F8
    .4byte NULL
    .4byte 0x802C6D3C
    .4byte 0x802C6DF8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C6F20
    .4byte 0x803F7918
    .4byte NULL
    .4byte 0x802C7044
    .4byte 0x802C7100
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C71EC
    .4byte 0x803F7938
    .4byte NULL
    .4byte 0x802C7310
    .4byte 0x802C73CC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C74B8
    .4byte 0x803F7968
    .4byte NULL
    .4byte 0x802C7A54
    .4byte 0x802C7B10
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C7D40
    .4byte 0x803F79A0
    .4byte NULL
    .4byte 0x802C7E64
    .4byte 0x802C7F20
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C8018
    .4byte 0x803F79E0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C847C
    .4byte NULL
    .4byte NULL
    .4byte 0x802C8A28
    .4byte 0x802C88E4
    .4byte 0x802C899C
    .4byte 0x802C8A08
    .4byte 0x802C8940
    .4byte 0x802C8B08
    .4byte 0x803F7A28
    .4byte NULL
    .4byte NULL
    .4byte 0x802C8C74
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C8F2C
    .4byte 0x803F79C0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C835C
    .4byte 0x803F9378
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802F044C
    .4byte 0x803F9388
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802F0F0C
    .4byte NULL
    .4byte NULL
    .4byte 0x802F0F14
    .4byte 0x802F0F34
    .4byte 0x802F0F3C
    .4byte 0x802F0F44
    .4byte 0x802F0F64
    .4byte 0x802F0BC8
    .4byte 0x803F9378
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802F044C
    .4byte 0x803F9388
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802F0BC8
    .4byte 0x803F93A8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802F10B4
    .4byte NULL
    .4byte NULL
    .4byte 0x802F10D8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802F1094
    .4byte 0x803F6788
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8029BA38
    .4byte NULL
    .4byte NULL
    .4byte 0x8029BA40
    .4byte 0x8029BA60
    .4byte 0x8029BA70
    .4byte 0x8029BA78
    .4byte 0x8029BA68
    .4byte 0x8029BA98
    .4byte 0x803F75D0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C1384
    .4byte NULL
    .4byte NULL
    .4byte 0x802C13CC
    .4byte 0x802C1400
    .4byte 0x802C14B8
    .4byte 0x802C1514
    .4byte 0x802C145C
    .4byte 0x802C1570
    .4byte 0x803F75C0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C0490
    .4byte NULL
    .4byte NULL
    .4byte 0x802C0498
    .4byte 0x802C04B8
    .4byte 0x802C04C8
    .4byte 0x802C04D0
    .4byte 0x802C04C0
    .4byte 0x802C04F0
    .4byte 0x803F7668
    .4byte NULL
    .4byte 0x802C17FC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C1FC8
    .4byte NULL
    .4byte NULL
    .4byte 0x802C1FD0
    .4byte 0x802C1FF0
    .4byte 0x802C20E4
    .4byte 0x802C20EC
    .4byte 0x802C1FF8
    .4byte 0x802C210C
    .4byte 0x803F7528
    .4byte NULL
    .4byte 0x802BDEFC
    .4byte 0x802BDFE0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802BE1F4
    .4byte 0x803F7548
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802BE488
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802BE578
    .4byte 0x803F67D0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8029CA78
    .4byte NULL
    .4byte NULL
    .4byte 0x8029CA80
    .4byte 0x8029CA78
    .4byte 0x8029CC4C
    .4byte 0x8029CC54
    .4byte 0x8029CCF0
    .4byte 0x8029CCF8
    .4byte 0x803F67D0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x8029CA78
    .4byte NULL
    .4byte NULL
    .4byte 0x8029CA80
    .4byte 0x8029CA78
    .4byte 0x8029CC4C
    .4byte 0x8029CC54
    .4byte 0x8029CCF0
    .4byte 0x8029CCF8
    .4byte 0x803F6CA8
    .4byte NULL
    .4byte NULL
    .4byte 0x802AEB00
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802AF184
    .4byte 0x803F6CA8
    .4byte NULL
    .4byte NULL
    .4byte 0x802AEB00
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802AF184
    .4byte 0x803F6A28
    .4byte NULL
    .4byte 0x802A8984
    .4byte 0x802A8AF8
    .4byte NULL
    .4byte NULL
    .4byte 0x802A9A80
    .4byte NULL
    .4byte NULL
    .4byte 0x802A9D4C
    .4byte 0x802A9CE0
    .4byte NULL
    .4byte NULL
    .4byte 0x802A9B08
    .4byte 0x802AA034
    .4byte 0x803F6A28
    .4byte NULL
    .4byte 0x802A8984
    .4byte 0x802A8AF8
    .4byte NULL
    .4byte NULL
    .4byte 0x802A9A80
    .4byte NULL
    .4byte NULL
    .4byte 0x802A9D4C
    .4byte 0x802A9CE0
    .4byte NULL
    .4byte NULL
    .4byte 0x802A9B08
    .4byte 0x802AA034
    .4byte 0x803F6E98
    .4byte NULL
    .4byte 0x802AF298
    .4byte 0x802AF434
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802AF920
    .4byte 0x803F6E98
    .4byte NULL
    .4byte 0x802AF298
    .4byte 0x802AF434
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802AF920
    .4byte 0x803F7760
    .4byte NULL
    .4byte 0x802C56A0
    .4byte 0x802C578C
    .4byte NULL
    .4byte NULL
    .4byte 0x802C60B4
    .4byte NULL
    .4byte NULL
    .4byte 0x802C60CC
    .4byte 0x802C60BC
    .4byte 0x802C60C4
    .4byte 0x802C6140
    .4byte 0x802C6138
    .4byte 0x802C61D4
    .4byte 0x803F6B70
    .4byte NULL
    .4byte 0x802AA9CC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802AB2AC
    .4byte 0x802AB3C0
    .4byte 0x802AB3C8
    .4byte NULL
    .4byte NULL
    .4byte 0x802AB3D0
    .4byte 0x803F6F40
    .4byte NULL
    .4byte 0x802AFA2C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802AFD4C
    .4byte 0x802AFD54
    .4byte 0x802AFD5C
    .4byte 0x802AFD64
    .4byte 0x802AFD6C
    .4byte 0x803F7190
    .4byte NULL
    .4byte 0x802B34E4
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B3A94
    .4byte NULL
    .4byte NULL
    .4byte 0x802B3AF8
    .4byte 0x802B3C44
    .4byte 0x802B3CA8
    .4byte 0x802B3D70
    .4byte 0x802B3D0C
    .4byte 0x802B3EDC
    .4byte 0x803F71D8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B45F0
    .4byte NULL
    .4byte NULL
    .4byte 0x802B46C8
    .4byte 0x802B4638
    .4byte 0x802B4680
    .4byte 0x802B4A60
    .4byte 0x802B4A18
    .4byte 0x802B4AA8
    .4byte 0x803F7190
    .4byte NULL
    .4byte 0x802B34E4
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B3A94
    .4byte NULL
    .4byte NULL
    .4byte 0x802B3AF8
    .4byte 0x802B3C44
    .4byte 0x802B3CA8
    .4byte 0x802B3D70
    .4byte 0x802B3D0C
    .4byte 0x802B3EDC
    .4byte 0x803F71D8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B45F0
    .4byte NULL
    .4byte NULL
    .4byte 0x802B46C8
    .4byte 0x802B4638
    .4byte 0x802B4680
    .4byte 0x802B4A60
    .4byte 0x802B4A18
    .4byte 0x802B4AA8
    .4byte 0x803F7288
    .4byte NULL
    .4byte 0x802B58D8
    .4byte 0x802B59C4
    .4byte NULL
    .4byte NULL
    .4byte 0x802B5FD8
    .4byte NULL
    .4byte NULL
    .4byte 0x802B5FF0
    .4byte 0x802B5FE0
    .4byte 0x802B5FE8
    .4byte 0x802B6144
    .4byte 0x802B613C
    .4byte 0x802B62B0
    .4byte 0x803F6F50
    .4byte NULL
    .4byte 0x802AFEF8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B0D84
    .4byte 0x802B10E4
    .4byte NULL
    .4byte 0x802B1294
    .4byte 0x802B0F34
    .4byte NULL
    .4byte 0x802B14DC
    .4byte 0x802B16E4
    .4byte 0x802B1890
    .4byte 0x803F70A8
    .4byte NULL
    .4byte NULL
    .4byte 0x802B1AAC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802B1C40
    .4byte 0x803F6C58
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802AD2E8
    .4byte NULL
    .4byte NULL
    .4byte 0x802AD2F0
    .4byte 0x802AD384
    .4byte 0x802AD38C
    .4byte 0x802AD3B0
    .4byte 0x802AD450
    .4byte 0x802AD458
    .4byte 0x803F79E0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C847C
    .4byte NULL
    .4byte NULL
    .4byte 0x802C8A28
    .4byte 0x802C88E4
    .4byte 0x802C899C
    .4byte 0x802C8A08
    .4byte 0x802C8940
    .4byte 0x802C8B08
    .4byte 0x803F7958
    .4byte NULL
    .4byte 0x802C75DC
    .4byte 0x802C7698
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802C7754
    .4byte 0x803F94A0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802F3330
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802F3374
    .4byte 0x803F8BD8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802E6A40
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802E6ACC
    .4byte 0x803F93C8
    .4byte 0x802F14E4
    .4byte 0x802F1518
    .4byte 0x802F1888
    .4byte 0x802F1CE0
    .4byte 0x802F1CE0
    .4byte NULL
    .4byte 0x802F1910
    .4byte 0x802F1F48
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802F18F0
    .4byte 0x803F8C8C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802E6F7C
    .4byte 0x802E6FC0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802E709C

.global lbl_803F4CA8
lbl_803F4CA8:
	.incbin "baserom.dol", 0x3F1CA8, 0x78

    .balign 4
.global lbl_803F4D20
lbl_803F4D20:
    .4byte 0x803F8320
    .4byte 0x802D73F0
    .4byte 0x8027C8B0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D7F38
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D84D8
    .4byte 0x803F83E0
    .4byte 0x802D84F8
    .4byte 0x8027C8B0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D85F4
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x803F83F0
    .4byte 0x802D8688
    .4byte 0x8027C8B0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D8EC8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802D9A0C
    .4byte 0x803F85F0
    .4byte 0x802DC69C
    .4byte 0x8027C8B0
    .4byte 0x802DD4F4
    .4byte 0x802DD59C
    .4byte 0x802DD67C
    .4byte NULL
    .4byte 0x802DC774
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802DD7D0
    .4byte 0x803F88C0
    .4byte 0x802E05A0
    .4byte 0x8027C8B0
    .4byte 0x802E0F70
    .4byte 0x802E0FE4
    .4byte 0x802E10C8
    .4byte NULL
    .4byte 0x802E0EE0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802E16D8
    .4byte 0x803F8468
    .4byte 0x802D9BA8
    .4byte 0x802DC480
    .4byte 0x802DBE90
    .4byte 0x802DBF30
    .4byte 0x802DC000
    .4byte NULL
    .4byte 0x802D9CC4
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802E16D8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x803F89C8
    .4byte 0x802E2470
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802E257C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x803F8A88
    .4byte 0x802E37BC
    .4byte 0x8027C8B0
    .4byte 0x802E468C
    .4byte 0x802E4700
    .4byte 0x802E47C0
    .4byte NULL
    .4byte 0x802E3884
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802E4A24
    .4byte 0x803F8940
    .4byte 0x802E1820
    .4byte 0x802E1874
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802E1E5C
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802E2450
    .4byte 0x803F86C8
    .4byte 0x802DE040
    .4byte 0x802DFEF4
    .4byte 0x802DE434
    .4byte 0x802DE648
    .4byte 0x802DE4FC
    .4byte 0x802DFC34
    .4byte 0x802DFC58
    .4byte 0x802DEEF4
    .4byte 0x802DFC90
    .4byte 0x802DFCB0
    .4byte NULL
    .4byte 0x802DFE40
    .4byte 0x802DFD60
    .4byte 0x802DFED4
    .4byte 0x803F87F0
    .4byte 0x802E02E8
    .4byte 0x802E0388
    .4byte 0x802E0308
    .4byte 0x802E0348
    .4byte 0x802E0328
    .4byte 0x802E03A8
    .4byte 0x802E03C8
    .4byte 0x802E0368
    .4byte 0x802E03E8
    .4byte 0x802E0408
    .4byte NULL
    .4byte 0x802E0448
    .4byte 0x802E0428
    .4byte 0x802E0468
    .4byte 0x803F9000
    .4byte 0x802EB5C8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802EB6A8
    .4byte 0x802EB684
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802EC850
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x803F91D0
    .4byte NULL
    .4byte NULL
    .4byte 0x802EEA08
    .4byte 0x802EEA70
    .4byte 0x802EEB28
    .4byte 0x802EEED0
    .4byte NULL
    .4byte 0x802EEBB0
    .4byte 0x802EEF10
    .4byte 0x802EEED8
    .4byte NULL
    .4byte 0x802EEF68
    .4byte 0x802EEF30
    .4byte 0x802EEF88
    .4byte 0x803F91D0
    .4byte NULL
    .4byte NULL
    .4byte 0x802EEA08
    .4byte 0x802EEA70
    .4byte 0x802EEB28
    .4byte 0x802EEED0
    .4byte NULL
    .4byte 0x802EEBB0
    .4byte 0x802EEF10
    .4byte 0x802EEED8
    .4byte NULL
    .4byte 0x802EEF68
    .4byte 0x802EEF30
    .4byte 0x802EEF88
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x803F9260
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802EF074
    .4byte 0x802EF700
    .4byte NULL
    .4byte 0x802EF944
    .4byte 0x802EF724
    .4byte 0x802EF874
    .4byte 0x802EF924
    .4byte 0x802EF7CC
    .4byte 0x802EFA24
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x803F90D0
    .4byte 0x802ECE90
    .4byte 0x802ECCDC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802EDDC0
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802EE1E0
    .4byte 0x803F8DE8
    .4byte NULL
    .4byte 0x802E79C8
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802E838C
    .4byte NULL
    .4byte NULL
    .4byte 0x802E8420
    .4byte 0x802E838C
    .4byte 0x802E8418
    .4byte 0x802E85F4
    .4byte 0x802E8784
    .4byte NULL
    .4byte 0x803F8FD0
    .4byte 0x802EB1EC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x802EB444
    .4byte NULL
    .4byte NULL
    .4byte 0x802EB45C
    .4byte 0x802EB44C
    .4byte 0x802EB454
    .4byte NULL
    .4byte NULL
    .4byte 0x802EB5A8
    .4byte 0x803F9328
    .4byte NULL
    .4byte NULL
    .4byte 0x802EFBC0
    .4byte 0x802EFBE8
    .4byte 0x802EFC08
    .4byte 0x802EFE28
    .4byte 0x802F022C
    .4byte NULL
    .4byte 0x802F0104
    .4byte 0x802EFF1C
    .4byte NULL
    .4byte 0x802F01F8
    .4byte 0x802F0010
    .4byte 0x802F0320
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL

.global lbl_803F5428
lbl_803F5428:
    .asciz "can t init zako pos\n"
    .balign 4
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F2468, 0x140
.global lbl_803F55A8
lbl_803F55A8:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803F55D0
lbl_803F55D0:
	.incbin "baserom.dol", 0x3F25D0, 0xC0
.global lbl_803F5690
lbl_803F5690:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803F56B8
lbl_803F56B8:
	.incbin "baserom.dol", 0x3F26B8, 0x60
.global lbl_803F5718
lbl_803F5718:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F2740, 0x1A0
.global lbl_803F58E0
lbl_803F58E0:
	.incbin "baserom.dol", 0x3F28E0, 0x80
.global lbl_803F5960
lbl_803F5960:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F2988, 0x100
.global lbl_803F5A88
lbl_803F5A88:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803F5AB0
lbl_803F5AB0:
	.incbin "baserom.dol", 0x3F2AB0, 0xB0
.global lbl_803F5B60
lbl_803F5B60:
	.incbin "baserom.dol", 0x3F2B60, 0x20
.global lbl_803F5B80
lbl_803F5B80:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F2BA8, 0x1E0
.global lbl_803F5D88
lbl_803F5D88:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F2DB0, 0x40
.global lbl_803F5DF0
lbl_803F5DF0:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3F2DFC, 0x84
.global lbl_803F5E80
lbl_803F5E80:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F2EA8, 0x70
.global lbl_803F5F18
lbl_803F5F18:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F2F40, 0x2D0
.global lbl_803F6210
lbl_803F6210:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3F321C, 0x244
.global lbl_803F6460
lbl_803F6460:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F3488, 0x80
.global lbl_803F6508
lbl_803F6508:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F3530, 0x10
.global lbl_803F6540
lbl_803F6540:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F3568, 0xA0
.global jtbl_803F6608
jtbl_803F6608:
	.incbin "baserom.dol", 0x3F3608, 0x98
.global lbl_803F66A0
lbl_803F66A0:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F36C8, 0x50
.global lbl_803F6718
lbl_803F6718:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3F3724, 0x84
.global lbl_803F67A8
lbl_803F67A8:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F37D0, 0x20
.global lbl_803F67F0
lbl_803F67F0:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F3818, 0x30
.global lbl_803F6848
lbl_803F6848:
    .asciz "illusion add twice.\n"
    .balign 4
.global lbl_803F6860
lbl_803F6860:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F3888, 0x70
.global lbl_803F68F8
lbl_803F68F8:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803F6920
lbl_803F6920:
	.incbin "baserom.dol", 0x3F3920, 0x40
.global lbl_803F6960
lbl_803F6960:
    .asciz "translate"
    .balign 4
.global lbl_803F696C
lbl_803F696C:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F3994, 0x94
.global lbl_803F6A28
lbl_803F6A28:
	.incbin "baserom.dol", 0x3F3A28, 0x50
.global lbl_803F6A78
lbl_803F6A78:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3F3A84, 0x40
.global lbl_803F6AC4
lbl_803F6AC4:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global jtbl_803F6AEC
jtbl_803F6AEC:
	.incbin "baserom.dol", 0x3F3AEC, 0x1C
.global jtbl_803F6B08
jtbl_803F6B08:
	.incbin "baserom.dol", 0x3F3B08, 0x30
.global lbl_803F6B38
lbl_803F6B38:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F3B60, 0x40
.global lbl_803F6BA0
lbl_803F6BA0:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F3BC8, 0x10
.global jtbl_803F6BD8
jtbl_803F6BD8:
	.incbin "baserom.dol", 0x3F3BD8, 0x40
.global lbl_803F6C18
lbl_803F6C18:
	.incbin "baserom.dol", 0x3F3C18, 0x18
.global lbl_803F6C30
lbl_803F6C30:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F3C58, 0x50
.global lbl_803F6CA8
lbl_803F6CA8:
	.incbin "baserom.dol", 0x3F3CA8, 0x180
.global lbl_803F6E28
lbl_803F6E28:
	.incbin "baserom.dol", 0x3F3E28, 0x14
.global lbl_803F6E3C
lbl_803F6E3C:
	.incbin "baserom.dol", 0x3F3E3C, 0x2C
.global lbl_803F6E68
lbl_803F6E68:
	.incbin "baserom.dol", 0x3F3E68, 0xA0
.global lbl_803F6F08
lbl_803F6F08:
	.incbin "baserom.dol", 0x3F3F08, 0x1C
.global lbl_803F6F24
lbl_803F6F24:
	.incbin "baserom.dol", 0x3F3F24, 0x2C
.global lbl_803F6F50
lbl_803F6F50:
	.incbin "baserom.dol", 0x3F3F50, 0x130
.global lbl_803F7080
lbl_803F7080:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F40A8, 0xA0
.global lbl_803F7148
lbl_803F7148:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3F4154, 0x14
.global lbl_803F7168
lbl_803F7168:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F4190, 0x20
.global lbl_803F71B0
lbl_803F71B0:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803F71D8
lbl_803F71D8:
	.incbin "baserom.dol", 0x3F41D8, 0x10
.global lbl_803F71E8
lbl_803F71E8:
    .asciz "translate"
    .balign 4
.global lbl_803F71F4
lbl_803F71F4:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F421C, 0x44
.global lbl_803F7260
lbl_803F7260:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F4288, 0x90
.global lbl_803F7318
lbl_803F7318:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F4340, 0x40
.global lbl_803F7380
lbl_803F7380:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F43A8, 0x150
.global lbl_803F74F8
lbl_803F74F8:
	.incbin "baserom.dol", 0x3F44F8, 0xA0
.global lbl_803F7598
lbl_803F7598:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F45C0, 0x80
.global lbl_803F7640
lbl_803F7640:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F4668, 0xB0
.global lbl_803F7718
lbl_803F7718:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F4740, 0x140
.global lbl_803F7880
lbl_803F7880:
	.incbin "baserom.dol", 0x3F4880, 0xC
.global lbl_803F788C
lbl_803F788C:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3F4898, 0xE0
.global lbl_803F7978
lbl_803F7978:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F49A0, 0x60
.global lbl_803F7A00
lbl_803F7A00:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F4A28, 0x160
.global lbl_803F7B88
lbl_803F7B88:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F4BB0, 0x120
.global lbl_803F7CD0
lbl_803F7CD0:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F4CF8, 0x40
.global lbl_803F7D38
lbl_803F7D38:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803F7D60
lbl_803F7D60:
	.incbin "baserom.dol", 0x3F4D60, 0x3F8
.global lbl_803F8158
lbl_803F8158:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F5180, 0x2C0
.global lbl_803F8440
lbl_803F8440:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F5468, 0x160
.global lbl_803F85C8
lbl_803F85C8:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F55F0, 0xB0
.global lbl_803F86A0
lbl_803F86A0:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803F86C8
lbl_803F86C8:
	.incbin "baserom.dol", 0x3F56C8, 0x2C8
.global lbl_803F8990
lbl_803F8990:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803F89B8
lbl_803F89B8:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3F59C4, 0x244
.global lbl_803F8C08
lbl_803F8C08:
	.incbin "baserom.dol", 0x3F5C08, 0x1C4
.global lbl_803F8DCC
lbl_803F8DCC:
    .asciz "%s:%d: oioi...\n"
    .balign 4
.global lbl_803F8DDC
lbl_803F8DDC:
    .asciz "ityaku.c"
    .balign 4
.global lbl_803F8DE8
lbl_803F8DE8:
	.incbin "baserom.dol", 0x3F5DE8, 0x60
.global lbl_803F8E48
lbl_803F8E48:
	.incbin "baserom.dol", 0x3F5E48, 0x20
.global lbl_803F8E68
lbl_803F8E68:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F5E90, 0x160
.global lbl_803F8FF0
lbl_803F8FF0:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3F5FFC, 0xD4
.global lbl_803F90D0
lbl_803F90D0:
	.incbin "baserom.dol", 0x3F60D0, 0xB0
.global lbl_803F9180
lbl_803F9180:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global jtbl_803F91A8
jtbl_803F91A8:
	.incbin "baserom.dol", 0x3F61A8, 0xA8
.global lbl_803F9250
lbl_803F9250:
	.incbin "baserom.dol", 0x3F6250, 0xB0
.global lbl_803F9300
lbl_803F9300:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F6328, 0xA0
.global lbl_803F93C8
lbl_803F93C8:
	.incbin "baserom.dol", 0x3F63C8, 0x88
.global lbl_803F9450
lbl_803F9450:
	.incbin "baserom.dol", 0x3F6450, 0x30
.global lbl_803F9480
lbl_803F9480:
	.incbin "baserom.dol", 0x3F6480, 0x10
.global lbl_803F9490
lbl_803F9490:
	.incbin "baserom.dol", 0x3F6490, 0x40
.global lbl_803F94D0
lbl_803F94D0:
    .asciz "ScInfDmg_scene_data"
    .balign 4
    .incbin "baserom.dol", 0x3F64E4, 0x4
.global lbl_803F94E8
lbl_803F94E8:
    .asciz "ScInfTim_scene_models"
    .balign 4
    .asciz "Error : jobj dont't get (ifAddTimeDownModel)\n"
    .balign 4
    .asciz "iftime.c"
    .balign 4
    .asciz "translate"
    .balign 4
    .asciz "Error : gobj dont't get (ifAddTime)\n"
    .balign 4
    .asciz "Error : jobj dont't get (ifAddTime)\n"
    .balign 4
.global lbl_803F9598
lbl_803F9598:
    .asciz "DmgNum_scene_models"
    .balign 4
.global lbl_803F95AC
lbl_803F95AC:
    .asciz "DmgMrk_scene_models"
    .balign 4
.global lbl_803F95C0
lbl_803F95C0:
    .asciz "translate"
    .balign 4
    .asciz "Error : gobj dont't get (ifAddMark)\n"
    .balign 4
    .asciz "ifstatus.c"
    .balign 4
    .asciz "Error : jobj dont't get (ifAddMark)\n"
    .balign 4
.global lbl_803F9628
lbl_803F9628:
	.incbin "baserom.dol", 0x3F6628, 0x158
.global lbl_803F9780
lbl_803F9780:
    .asciz "ScInfStc_scene_models"
    .balign 4
.global lbl_803F9798
lbl_803F9798:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3F67A4, 0x4
.global lbl_803F97A8
lbl_803F97A8:
    .asciz "Stc_scemdls"
    .balign 4
.global lbl_803F97B4
lbl_803F97B4:
    .asciz "translate"
    .balign 4
    .incbin "baserom.dol", 0x3F67C0, 0x28
.global lbl_803F97E8
lbl_803F97E8:
	.incbin "baserom.dol", 0x3F67E8, 0x40
.global lbl_803F9828
lbl_803F9828:
	.incbin "baserom.dol", 0x3F6828, 0x24
.global lbl_803F984C
lbl_803F984C:
	.incbin "baserom.dol", 0x3F684C, 0x40
.global lbl_803F988C
lbl_803F988C:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3F68B4, 0x4
.global lbl_803F98B8
lbl_803F98B8:
	.incbin "baserom.dol", 0x3F68B8, 0xDC
.global lbl_803F9994
lbl_803F9994:
    .asciz "ScInfPnm_scene_models"
    .balign 4
    .asciz "SdIntro.dat"
    .balign 4
    .asciz "SIS_IntroData"
    .balign 4
.global lbl_803F99C8
lbl_803F99C8:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global lbl_803F99F0
lbl_803F99F0:
    .asciz "Stc_rarwmdls"
    .balign 4
.global lbl_803F9A00
lbl_803F9A00:
	.incbin "baserom.dol", 0x3F6A00, 0x130
.global lbl_803F9B30
lbl_803F9B30:
	.incbin "baserom.dol", 0x3F6B30, 0x2D8
.global lbl_803F9E08
lbl_803F9E08:
	.incbin "baserom.dol", 0x3F6E08, 0x58
.global lbl_803F9E60
lbl_803F9E60:
	.incbin "baserom.dol", 0x3F6E60, 0x74
.global lbl_803F9ED4
lbl_803F9ED4:
	.incbin "baserom.dol", 0x3F6ED4, 0x54
.global lbl_803F9F28
lbl_803F9F28:
    .asciz "Sound Test Menu"
    .balign 4
    .asciz "Sound Mode "
    .balign 4
    .asciz "Mas Volume"
    .balign 4
    .asciz "FGM Volume"
    .balign 4
    .asciz "BGM Volume"
    .balign 4
    .asciz "DSP Level"
    .balign 4
    .asciz "FGM Group"
    .balign 4
    .asciz "FGM Name"
    .balign 4
    .asciz "BGM Name"
    .balign 4
    .asciz "-- EXIT --"
    .balign 4
.global lbl_803F9FA4
lbl_803F9FA4:
	.incbin "baserom.dol", 0x3F6FA4, 0x184
.global lbl_803FA128
lbl_803FA128:
	.incbin "baserom.dol", 0x3F7128, 0x130
.global lbl_803FA258
lbl_803FA258:
	.incbin "baserom.dol", 0x3F7258, 0x288
.global lbl_803FA4E0
lbl_803FA4E0:
	.incbin "baserom.dol", 0x3F74E0, 0x178
.global lbl_803FA658
lbl_803FA658:
	.incbin "baserom.dol", 0x3F7658, 0x138
.global lbl_803FA790
lbl_803FA790:
	.incbin "baserom.dol", 0x3F7790, 0x158
.global lbl_803FA8E8
lbl_803FA8E8:
	.incbin "baserom.dol", 0x3F78E8, 0x15C
.global lbl_803FAA44
lbl_803FAA44:
	.incbin "baserom.dol", 0x3F7A44, 0x724
.global lbl_803FB168
lbl_803FB168:
	.incbin "baserom.dol", 0x3F8168, 0x4A4
.global lbl_803FB60C
lbl_803FB60C:
	.incbin "baserom.dol", 0x3F860C, 0x11C
.global lbl_803FB728
lbl_803FB728:
	.incbin "baserom.dol", 0x3F8728, 0x148
.global lbl_803FB870
lbl_803FB870:
	.incbin "baserom.dol", 0x3F8870, 0x11C
.global lbl_803FB98C
lbl_803FB98C:
	.incbin "baserom.dol", 0x3F898C, 0x110
.global lbl_803FBA9C
lbl_803FBA9C:
	.incbin "baserom.dol", 0x3F8A9C, 0xFC
.global lbl_803FBB98
lbl_803FBB98:
	.incbin "baserom.dol", 0x3F8B98, 0x114
.global lbl_803FBCAC
lbl_803FBCAC:
	.incbin "baserom.dol", 0x3F8CAC, 0x114
.global lbl_803FBDC0
lbl_803FBDC0:
	.incbin "baserom.dol", 0x3F8DC0, 0x23C
.global lbl_803FBFFC
lbl_803FBFFC:
	.incbin "baserom.dol", 0x3F8FFC, 0x100
.global lbl_803FC0FC
lbl_803FC0FC:
	.incbin "baserom.dol", 0x3F90FC, 0x130
.global lbl_803FC22C
lbl_803FC22C:
	.incbin "baserom.dol", 0x3F922C, 0x2A0
.global lbl_803FC4CC
lbl_803FC4CC:
	.incbin "baserom.dol", 0x3F94CC, 0x170
.global lbl_803FC63C
lbl_803FC63C:
	.incbin "baserom.dol", 0x3F963C, 0xD0
.global lbl_803FC70C
lbl_803FC70C:
	.incbin "baserom.dol", 0x3F970C, 0x11C
.global lbl_803FC828
lbl_803FC828:
	.incbin "baserom.dol", 0x3F9828, 0xA0
.global lbl_803FC8C8
lbl_803FC8C8:
	.incbin "baserom.dol", 0x3F98C8, 0x178
.global lbl_803FCA40
lbl_803FCA40:
	.incbin "baserom.dol", 0x3F9A40, 0x1F8
.global lbl_803FCC38
lbl_803FCC38:
	.incbin "baserom.dol", 0x3F9C38, 0xFC
.global lbl_803FCD34
lbl_803FCD34:
	.incbin "baserom.dol", 0x3F9D34, 0x118
.global lbl_803FCE4C
lbl_803FCE4C:
	.incbin "baserom.dol", 0x3F9E4C, 0x218
.global lbl_803FD064
lbl_803FD064:
	.incbin "baserom.dol", 0x3FA064, 0x1C0
.global lbl_803FD224
lbl_803FD224:
    .asciz "<Format>\n"
    .balign 4
.global lbl_803FD230
lbl_803FD230:
    .asciz "result %d\n"
    .balign 4
.global lbl_803FD23C
lbl_803FD23C:
    .asciz "<Accessable>\n"
    .balign 4
.global lbl_803FD24C
lbl_803FD24C:
    .asciz "<Create>\n"
    .balign 4
.global lbl_803FD258
lbl_803FD258:
    .asciz "<Delete>\n"
    .balign 4
.global lbl_803FD264
lbl_803FD264:
    .asciz "<SnapMount0>\n"
    .balign 4
.global lbl_803FD274
lbl_803FD274:
	.incbin "baserom.dol", 0x3FA274, 0x18
.global lbl_803FD28C
lbl_803FD28C:
    .asciz "<SnapLoad0>\n"
    .balign 4
.global lbl_803FD29C
lbl_803FD29C:
    .asciz "<SnapDelete0>\n"
    .balign 4
.global lbl_803FD2AC
lbl_803FD2AC:
    .asciz "<SnapSwap0>\n"
    .balign 4
    .asciz "< Yoshiki Test >"
    .balign 4
    .asciz "Accessable"
    .balign 4
    .asciz "SnapMount0"
    .balign 4
    .asciz "SnapLoad0 "
    .balign 4
    .asciz "SnapDelete0 "
    .balign 4
    .asciz "SnapSwap0 "
    .balign 4
.global lbl_803FD310
lbl_803FD310:
	.incbin "baserom.dol", 0x3FA310, 0x27C
.global lbl_803FD58C
lbl_803FD58C:
	.incbin "baserom.dol", 0x3FA58C, 0x2D8
.global lbl_803FD864
lbl_803FD864:
	.incbin "baserom.dol", 0x3FA864, 0x294
.global lbl_803FDAF8
lbl_803FDAF8:
	.incbin "baserom.dol", 0x3FAAF8, 0xA4
.global lbl_803FDB9C
lbl_803FDB9C:
	.incbin "baserom.dol", 0x3FAB9C, 0xAC
.global lbl_803FDC48
lbl_803FDC48:
	.incbin "baserom.dol", 0x3FAC48, 0x38
.global lbl_803FDC80
lbl_803FDC80:
    .asciz "TW : Screen alloc Fail\n"
    .balign 4
.global lbl_803FDC98
lbl_803FDC98:
    .asciz "textlib.c"
    .balign 4
    .incbin "baserom.dol", 0x3FACA4, 0x4
.global lbl_803FDCA8
lbl_803FDCA8:
	.incbin "baserom.dol", 0x3FACA8, 0x24
.global jtbl_803FDCCC
jtbl_803FDCCC:
	.incbin "baserom.dol", 0x3FACCC, 0x24
.global jtbl_803FDCF0
jtbl_803FDCF0:
	.incbin "baserom.dol", 0x3FACF0, 0x28
.global lbl_803FDD18
lbl_803FDD18:
    .asciz "TyLight.dat"
    .balign 4
    .asciz "ScToyLightMaster0_scene_lights"
    .balign 4
    .asciz "ScToyLightMaster1_scene_lights"
    .balign 4
    .asciz "ScToyLightMaster2_scene_lights"
    .balign 4
    .asciz "ScToyLightMaster4_scene_lights"
    .balign 4
    .asciz "ScToyLightMaster5_scene_lights"
    .balign 4
    .asciz "ScToyLightMaster6_scene_lights"
    .balign 4
    .incbin "baserom.dol", 0x3FADE4, 0x478
.global jtbl_803FE25C
jtbl_803FE25C:
	.incbin "baserom.dol", 0x3FB25C, 0x24
.global jtbl_803FE280
jtbl_803FE280:
	.incbin "baserom.dol", 0x3FB280, 0x24
.global lbl_803FE2A4
lbl_803FE2A4:
    .asciz "X   %3.2f\nY   %3.2f\nZ   %3.2f\nMS  %3.2f\nSS  %3.2f\nMD  %3.2f"
    .balign 4
.global jtbl_803FE2E0
jtbl_803FE2E0:
	.incbin "baserom.dol", 0x3FB2E0, 0xD8
.global lbl_803FE3B8
lbl_803FE3B8:
    .asciz "*** BG data aren't being loaded!\n"
    .balign 4
.global lbl_803FE3DC
lbl_803FE3DC:
    .asciz "ScMenFigure_scene_lights"
    .balign 4
    .incbin "baserom.dol", 0x3FB3F8, 0x5C
.global lbl_803FE454
lbl_803FE454:
    .asciz "**** Not Found Toy Model!(%d)\n"
    .balign 4
.global lbl_803FE474
lbl_803FE474:
    .asciz "*** Error : Not Found Model Name!(To Idx %d)\n"
    .balign 4
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .asciz "*** Cann't Show Model!\n"
    .balign 4
    .asciz "3DPos X = %f, Y = %f, Z = %f\n"
    .balign 4
    .asciz "2DPos X = %f, Y = %f\n\n"
    .balign 4
    .asciz "Pos : %f, %f,%f\n"
    .balign 4
    .asciz "WinSize = %f, %f\n"
    .balign 4
    .asciz "WinScale = %f, %f\n"
    .balign 4
    .asciz "FontSize = %f, %f\n"
    .balign 4
    .asciz "RotY = %f\n"
    .balign 4
    .asciz "*** Pad = %d\n"
    .balign 4
    .asciz "top = %f, bottom = %f, right = %f, left = %f\n"
    .balign 4
    .asciz "top = %f, bottom = %f\n"
    .balign 4
    .asciz "right = %f, left = %f\n"
    .balign 4
.global lbl_803FE5E8
lbl_803FE5E8:
    .asciz "ScMenFigure_cam_int1_camera"
    .balign 4
    .incbin "baserom.dol", 0x3FB604, 0x19C
.global lbl_803FE7A0
lbl_803FE7A0:
    .asciz "Rea_%c %3d/%3d"
    .balign 4
.global lbl_803FE7B0
lbl_803FE7B0:
    .asciz "Rea_%c %3d/%3d\n"
    .balign 4
.global lbl_803FE7C0
lbl_803FE7C0:
    .asciz "*** Couldn't Open Debug Window2!\n"
    .balign 4
.global lbl_803FE7E4
lbl_803FE7E4:
    .asciz "*** Couldn't Open Debug Window!\n"
    .balign 4
    .asciz "SdToy.dat"
    .balign 4
    .asciz "SIS_ToyData"
    .balign 4
    .asciz "SdToyExp.dat"
    .balign 4
    .asciz "SIS_ToyDataExp"
    .balign 4
    .asciz "SdToy.usd"
    .balign 4
    .asciz "SIS_ToyData_E"
    .balign 4
    .asciz "SdToyExp.usd"
    .balign 4
    .asciz "SIS_ToyDataExp_E"
    .balign 4
.global lbl_803FE880
lbl_803FE880:
    .asciz "Pos : %f, %f,%f\n"
    .balign 4
    .asciz "WinSize = %f, %f\n"
    .balign 4
    .asciz "WinScale = %f, %f\n"
    .balign 4
    .asciz "FontSize = %f, %f\n"
    .balign 4
.global lbl_803FE8D0
lbl_803FE8D0:
    .asciz "ToyFigureListMarkN_Top_joint"
    .balign 4
.global lbl_803FE8F0
lbl_803FE8F0:
    .asciz "tylist.c"
    .balign 4
.global lbl_803FE8FC
lbl_803FE8FC:
    .asciz "*** Can't Get Public Address!(tyList Model)\n"
    .balign 4
    .asciz "ToyFigurePanel_listpos01_joint"
    .balign 4
    .asciz "ToyFigureListBase_Top_joint"
    .balign 4
    .asciz "ToyFigureListBase_Top_matanim_joint"
    .balign 4
    .asciz "ToyFigureListBaseend_Top_joint"
    .balign 4
    .asciz "ToyFigureListCursor_Top_joint"
    .balign 4
    .asciz "*** BG data aren't being loaded!\n"
    .balign 4
    .asciz "ScMenFigure_scene_lights"
    .balign 4
    .incbin "baserom.dol", 0x3FBA0C, 0x4
.global lbl_803FEA10
lbl_803FEA10:
    .asciz "ToyFigurePonPanel_Top_joint"
    .balign 4
    .asciz "ToyFigurePonBg_Top_joint"
    .balign 4
    .asciz "TyMnFigp.dat"
    .balign 4
    .asciz "TyMnFigp.usd"
    .balign 4
    .asciz "ToyFigurePonCoin_Top_joint"
    .balign 4
    .asciz "ToyFigurePonCoin_Top_animjoint"
    .balign 4
    .asciz "ToyFigurePonCoin_Top_matanim_joint"
    .balign 4
    .asciz "ToyFigurePonCoin_Top_shapeanim_joint"
    .balign 4
.global jtbl_803FEAF0
jtbl_803FEAF0:
	.incbin "baserom.dol", 0x3FBAF0, 0x4C
.global jtbl_803FEB3C
jtbl_803FEB3C:
	.incbin "baserom.dol", 0x3FBB3C, 0x24
.global lbl_803FEB60
lbl_803FEB60:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .incbin "baserom.dol", 0x3FBB88, 0x468
.global lbl_803FEFF0
lbl_803FEFF0:
    .asciz "ToyDspPanel_Top_joint"
    .balign 4
    .asciz "ToyDspBg_Top_joint"
    .balign 4
.global lbl_803FF01C
lbl_803FF01C:
    .asciz "ToyDspStand_Top_joint"
    .balign 4
    .asciz "ScMenDisplay_fog"
    .balign 4
.global lbl_803FF048
lbl_803FF048:
    .asciz "*** tyDisplay Atari Irregul!\n"
    .balign 4
.global lbl_803FF068
lbl_803FF068:
    .asciz "tydisplay.c"
    .balign 4
.global lbl_803FF074
lbl_803FF074:
    .asciz "*** tyDisplay Table Scale Irregul!\n"
    .balign 4
    .asciz "TyMnDisp.dat"
    .balign 4
    .asciz "TyMnDisp.usd"
    .balign 4
    .asciz "*** BG data aren't being loaded!\n"
    .balign 4
    .asciz "*** Can not Load Panel Label(%s)\n"
    .balign 4
    .asciz "ScMenDisplay_scene_lights"
    .balign 4
    .incbin "baserom.dol", 0x3FC11C, 0x80
.global lbl_803FF19C
lbl_803FF19C:
    .asciz "X  %3.2f\nZ  %3.2f"
    .balign 4
    .asciz "ToyDspQues_Top_joint"
    .balign 4
    .asciz "ToyDspMycharaCmA_Top_joint"
    .balign 4
    .asciz "ToyDspMycharaCmB_Top_joint"
    .balign 4
    .asciz "ToyDspMycharaCmC_Top_joint"
    .balign 4
    .asciz "ToyDspMycharaCmD_Top_joint"
    .balign 4
    .asciz "ToyDspMycharaCmE_Top_joint"
    .balign 4
    .asciz "ToyDspMycharaR1A_Top_joint"
    .balign 4
    .asciz "ToyDspMycharaR1B_Top_joint"
    .balign 4
    .asciz "ToyDspMycharaR1C_Top_joint"
    .balign 4
    .asciz "ToyDspMycharaR1D_Top_joint"
    .balign 4
    .asciz "ToyDspMycharaR1E_Top_joint"
    .balign 4
    .asciz "ToyDspMycharaR2A_Top_joint"
    .balign 4
    .asciz "ToyDspMycharaR2B_Top_joint"
    .balign 4
    .asciz "ToyDspMycharaR2C_Top_joint"
    .balign 4
    .asciz "ToyDspMycharaR2D_Top_joint"
    .balign 4
    .asciz "ToyDspMycharaR2E_Top_joint"
    .balign 4
    .asciz "ToyDspMapA_Top_joint"
    .balign 4
    .asciz "ToyDspMapB_Top_joint"
    .balign 4
    .asciz "ToyDspMapC_Top_joint"
    .balign 4
    .asciz "ToyDspMapD_Top_joint"
    .balign 4
    .asciz "ToyDspMapE_Top_joint"
    .balign 4
    .asciz "ToyDspFgseriesA_Top_joint"
    .balign 4
    .asciz "ToyDspFgseriesB_Top_joint"
    .balign 4
    .asciz "ToyDspFgseriesC_Top_joint"
    .balign 4
    .asciz "ToyDspFgseriesD_Top_joint"
    .balign 4
    .asciz "ToyDspFgseriesE_Top_joint"
    .balign 4
    .asciz "ToyDspFgetcA_Top_joint"
    .balign 4
    .asciz "ToyDspFgetcB_Top_joint"
    .balign 4
    .asciz "ToyDspFgetcC_Top_joint"
    .balign 4
    .asciz "ToyDspFgetcD_Top_joint"
    .balign 4
    .asciz "ToyDspFgetcE_Top_joint"
    .balign 4
    .asciz "ToyDspPokemonA_Top_joint"
    .balign 4
    .asciz "ToyDspPokemonB_Top_joint"
    .balign 4
    .asciz "ToyDspPokemonC_Top_joint"
    .balign 4
    .asciz "ToyDspPokemonD_Top_joint"
    .balign 4
    .asciz "ToyDspPokemonE_Top_joint"
    .balign 4
    .asciz "ToyDspItemA_Top_joint"
    .balign 4
    .asciz "ToyDspItemB_Top_joint"
    .balign 4
    .asciz "ToyDspItemC_Top_joint"
    .balign 4
    .asciz "ToyDspItemD_Top_joint"
    .balign 4
    .asciz "ToyDspItemE_Top_joint"
    .balign 4
    .asciz "ToyDspStand_Top_joint"
    .balign 4
    .asciz "ToyDspMycharaCmA_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspMycharaCmB_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspMycharaCmC_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspMycharaCmD_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspMycharaCmE_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspMycharaR1A_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspMycharaR1B_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspMycharaR1C_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspMycharaR1D_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspMycharaR1E_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspMycharaR2A_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspMycharaR2B_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspMycharaR2C_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspMycharaR2D_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspMycharaR2E_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspMapA_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspMapB_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspMapC_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspMapD_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspMapE_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspFgseriesA_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspFgseriesB_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspFgseriesC_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspFgseriesD_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspFgseriesE_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspFgetcA_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspFgetcB_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspFgetcC_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspFgetcD_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspFgetcE_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspPokemonA_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspPokemonB_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspPokemonC_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspPokemonD_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspPokemonE_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspItemA_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspItemB_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspItemC_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspItemD_Top_matanim_joint"
    .balign 4
    .asciz "ToyDspItemE_Top_matanim_joint"
    .balign 4
    .asciz "TyQuesD.dat"
    .balign 4
    .asciz "TyMycCmA.dat"
    .balign 4
    .asciz "TyMycCmB.dat"
    .balign 4
    .asciz "TyMycCmC.dat"
    .balign 4
    .asciz "TyMycCmD.dat"
    .balign 4
    .asciz "TyMycCmE.dat"
    .balign 4
    .asciz "TyMycR1A.dat"
    .balign 4
    .asciz "TyMycR1B.dat"
    .balign 4
    .asciz "TyMycR1C.dat"
    .balign 4
    .asciz "TyMycR1D.dat"
    .balign 4
    .asciz "TyMycR1E.dat"
    .balign 4
    .asciz "TyMycR2A.dat"
    .balign 4
    .asciz "TyMycR2B.dat"
    .balign 4
    .asciz "TyMycR2C.dat"
    .balign 4
    .asciz "TyMycR2D.dat"
    .balign 4
    .asciz "TyMycR2E.dat"
    .balign 4
    .asciz "TyMapA.dat"
    .balign 4
    .asciz "TyMapB.dat"
    .balign 4
    .asciz "TyMapC.dat"
    .balign 4
    .asciz "TyMapD.dat"
    .balign 4
    .asciz "TyMapE.dat"
    .balign 4
    .asciz "TySeriA.dat"
    .balign 4
    .asciz "TySeriB.dat"
    .balign 4
    .asciz "TySeriC.dat"
    .balign 4
    .asciz "TySeriD.dat"
    .balign 4
    .asciz "TySeriE.dat"
    .balign 4
    .asciz "TyEtcA.dat"
    .balign 4
    .asciz "TyEtcB.dat"
    .balign 4
    .asciz "TyEtcC.dat"
    .balign 4
    .asciz "TyEtcD.dat"
    .balign 4
    .asciz "TyEtcE.dat"
    .balign 4
    .asciz "TyPokeA.dat"
    .balign 4
    .asciz "TyPokeB.dat"
    .balign 4
    .asciz "TyPokeC.dat"
    .balign 4
    .asciz "TyPokeD.dat"
    .balign 4
    .asciz "TyPokeE.dat"
    .balign 4
    .asciz "TyItemA.dat"
    .balign 4
    .asciz "TyItemB.dat"
    .balign 4
    .asciz "TyItemC.dat"
    .balign 4
    .asciz "TyItemD.dat"
    .balign 4
    .asciz "TyItemE.dat"
    .balign 4
    .asciz "TyStandD.dat"
    .balign 4
    .asciz "PlCaDViWaitAJ.dat"
    .balign 4
    .asciz "PlDkDViWaitAJ.dat"
    .balign 4
    .asciz "PlFxDViWaitAJ.dat"
    .balign 4
    .asciz "PlGwDViWaitAJ.dat"
    .balign 4
    .asciz "PlKbDViWaitAJ.dat"
    .balign 4
    .asciz "PlKpDViWaitAJ.dat"
    .balign 4
    .asciz "PlLkDViWaitAJ.dat"
    .balign 4
    .asciz "PlLgDViWaitAJ.dat"
    .balign 4
    .asciz "PlMrDViWaitAJ.dat"
    .balign 4
    .asciz "PlMsDViWaitAj.dat"
    .balign 4
    .asciz "PlMtDViWaitAJ.dat"
    .balign 4
    .asciz "PlNsDViWaitAJ.dat"
    .balign 4
    .asciz "PlPeDViWaitAJ.dat"
    .balign 4
    .asciz "PlPkDViWaitAJ.dat"
    .balign 4
    .asciz "PlPpDViWaitAJ.dat"
    .balign 4
    .asciz "PlPrDViWaitAJ.dat"
    .balign 4
    .asciz "PlSsDViWaitAJ.dat"
    .balign 4
    .asciz "PlYsDViWaitAJ.dat"
    .balign 4
    .asciz "PlZdDViWaitAJ.dat"
    .balign 4
    .asciz "PlSkDViWaitAJ.dat"
    .balign 4
    .asciz "PlFcDViWaitAJ.dat"
    .balign 4
    .asciz "PlClDViWaitAJ.dat"
    .balign 4
    .asciz "PlDrDViWaitAJ.dat"
    .balign 4
    .asciz "PlFeDViWaitAJ.dat"
    .balign 4
    .asciz "PlPcDViWaitAJ.dat"
    .balign 4
    .asciz "PlGnDViWaitAJ.dat"
    .balign 4
.global lbl_803FFFA8
lbl_803FFFA8:
	.incbin "baserom.dol", 0x3FCFA8, 0x68
.global lbl_80400010
lbl_80400010:
	.incbin "baserom.dol", 0x3FD010, 0xC
.global lbl_8040001C
lbl_8040001C:
    .asciz "Vi0102.dat"
    .balign 4
.global lbl_80400028
lbl_80400028:
    .asciz "visual0102Scene"
    .balign 4
.global lbl_80400038
lbl_80400038:
    .asciz "Vi0401.dat"
    .balign 4
    .asciz "visual0401Scene"
    .balign 4
    .asciz "visual0401InfoScene"
    .balign 4
    .asciz "IfAll.dat"
    .balign 4
    .asciz "ScInfDmg_scene_data"
    .balign 4
.global lbl_80400088
lbl_80400088:
    .asciz "Vi0402.dat"
    .balign 4
.global lbl_80400094
lbl_80400094:
    .asciz "visual0402Scene"
    .balign 4
    .incbin "baserom.dol", 0x3FD0A4, 0x4
.global lbl_804000A8
lbl_804000A8:
	.incbin "baserom.dol", 0x3FD0A8, 0xC
.global lbl_804000B4
lbl_804000B4:
    .asciz "Vi0501.dat"
    .balign 4
.global lbl_804000C0
lbl_804000C0:
    .asciz "visual0501Scene"
    .balign 4
.global lbl_804000D0
lbl_804000D0:
	.incbin "baserom.dol", 0x3FD0D0, 0x38
.global lbl_80400108
lbl_80400108:
    .asciz "Vi0601.dat"
    .balign 4
.global lbl_80400114
lbl_80400114:
    .asciz "visual0601Scene"
    .balign 4
    .incbin "baserom.dol", 0x3FD124, 0x4
.global lbl_80400128
lbl_80400128:
	.incbin "baserom.dol", 0x3FD128, 0xB8
.global lbl_804001E0
lbl_804001E0:
    .asciz "Vi0801.dat"
    .balign 4
.global lbl_804001EC
lbl_804001EC:
    .asciz "visual0801Scene"
    .balign 4
    .incbin "baserom.dol", 0x3FD1FC, 0x4
.global lbl_80400200
lbl_80400200:
	.incbin "baserom.dol", 0x3FD200, 0x58
.global lbl_80400258
lbl_80400258:
	.incbin "baserom.dol", 0x3FD258, 0xA0
.global lbl_804002F8
lbl_804002F8:
	.incbin "baserom.dol", 0x3FD2F8, 0xC
.global lbl_80400304
lbl_80400304:
	.incbin "baserom.dol", 0x3FD304, 0x9C
.global lbl_804003A0
lbl_804003A0:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
    .asciz "Vi1202.dat"
    .balign 4
    .asciz "visual1202Scene"
    .balign 4
    .asciz "TyKoopaR.dat"
    .balign 4
    .asciz "ToyKoopaRModel_TopN_joint"
    .balign 4
    .asciz "GmRgStnd.dat"
    .balign 4
    .asciz "standScene"
    .balign 4
    .incbin "baserom.dol", 0x3FD42C, 0x4
.global lbl_80400430
lbl_80400430:
	.incbin "baserom.dol", 0x3FD430, 0xD8
.global jtbl_80400508
jtbl_80400508:
	.incbin "baserom.dol", 0x3FD508, 0x84
.global jtbl_8040058C
jtbl_8040058C:
	.incbin "baserom.dol", 0x3FD58C, 0x84
.global jtbl_80400610
jtbl_80400610:
	.incbin "baserom.dol", 0x3FD610, 0xD0
.global lbl_804006E0
lbl_804006E0:
	.incbin "baserom.dol", 0x3FD6E0, 0x48
.global lbl_80400728
lbl_80400728:
	.incbin "baserom.dol", 0x3FD728, 0x48
.global lbl_80400770
lbl_80400770:
	.incbin "baserom.dol", 0x3FD770, 0x4
.global lbl_80400774
lbl_80400774:
	.incbin "baserom.dol", 0x3FD774, 0x4
.global lbl_80400778
lbl_80400778:
	.incbin "baserom.dol", 0x3FD778, 0x10
.global lbl_80400788
lbl_80400788:
	.incbin "baserom.dol", 0x3FD788, 0x88
.global jtbl_80400810
jtbl_80400810:
	.incbin "baserom.dol", 0x3FD810, 0x1C
.global jtbl_8040082C
jtbl_8040082C:
	.incbin "baserom.dol", 0x3FD82C, 0x1C
.global lbl_80400848
lbl_80400848:
	.incbin "baserom.dol", 0x3FD848, 0xC
.global lbl_80400854
lbl_80400854:
	.incbin "baserom.dol", 0x3FD854, 0x10
.global lbl_80400864
lbl_80400864:
	.incbin "baserom.dol", 0x3FD864, 0x14
.global lbl_80400878
lbl_80400878:
	.incbin "baserom.dol", 0x3FD878, 0x40
.global lbl_804008B8
lbl_804008B8:
	.incbin "baserom.dol", 0x3FD8B8, 0x20
.global lbl_804008D8
lbl_804008D8:
    .asciz "HUDSON/USB2EXI/INITCODE/TARGET"
    .balign 4
.global lbl_804008F8
lbl_804008F8:
    .asciz "HUDSON/USB2EXI/INITCODE/HOST"
    .balign 4
.global lbl_80400918
lbl_80400918:
    .asciz "Error:Time is over.\n"
    .balign 4
    .asciz "UNLOCKED"
    .balign 4
    .asciz "DISCONNECT"
    .balign 4
    .asciz "HOST_OPEN"
    .balign 4
    .asciz "TARGET_OPEN"
    .balign 4
    .asciz "CONNECTED"
    .balign 4
    .asciz "%2d: FirstBlock:%02d,BlockLength:%02d,Connect:%s,Lock:%s.\n"
    .balign 4
    .asciz "[fio] Error: %s\n"
    .balign 4
    .asciz "fioPacketSendPacket.MCCWrite.NG"
    .balign 4
    .asciz "fioPacketSendPacket.MCCNotify.NG"
    .balign 4
    .asciz "fioPacketResultRead.MCCClose.NG"
    .balign 4
    .asciz "fioPacketResultRead.MCCStreamOpen.NG"
    .balign 4
    .asciz "fioPacketResultRead.MCCStreamRead.NG(Err:%d)"
    .balign 4
    .asciz "MCCStream:MCCStreamClose.NG\n"
    .balign 4
    .asciz "MCCStream:MCCOpen.NG\n"
    .balign 4
    .asciz "fioPacketResultWrite.MCCClose.NG"
    .balign 4
    .asciz "fioPacketResultWrite.MCCStreamOpen.NG"
    .balign 4
    .asciz "fioPacketResultWrite.MCCStreamWrite.NG"
    .balign 4
    .incbin "baserom.dol", 0x3FDB24, 0x4
.global lbl_80400B28
lbl_80400B28:
    .asciz "ERROR: THP only supports 4:2:0!!!\n"
    .balign 4
.global lbl_80400B4C
lbl_80400B4C:
    .asciz "THP does not support anything other than 4:2:0!\n"
    .balign 4
.global lbl_80400B80
lbl_80400B80:
	.incbin "baserom.dol", 0x3FDB80, 0x28
.global lbl_80400BA8
lbl_80400BA8:
	.incbin "baserom.dol", 0x3FDBA8, 0x48
.global lbl_80400BF0
lbl_80400BF0:
    .asciz "DBExceptionDestination\n"
    .balign 4
.global lbl_80400C08
lbl_80400C08:
    .asciz "DSPInit(): Build Date: %s %s\n"
    .balign 4
    .asciz "Sep  8 2001"
    .balign 4
    .asciz "01:51:48"
    .balign 4
.global lbl_80400C40
lbl_80400C40:
    .asciz "DSP is booting task: 0x%08X\n"
    .balign 4
    .asciz "__DSP_boot_task()  : IRAM MMEM ADDR: 0x%08X\n"
    .balign 4
    .asciz "__DSP_boot_task()  : IRAM DSP ADDR : 0x%08X\n"
    .balign 4
    .asciz "__DSP_boot_task()  : IRAM LENGTH   : 0x%08X\n"
    .balign 4
    .asciz "__DSP_boot_task()  : DRAM MMEM ADDR: 0x%08X\n"
    .balign 4
    .asciz "__DSP_boot_task()  : Start Vector  : 0x%08X\n"
    .balign 4
    .asciz "__DSP_add_task() : Added task    : 0x%08X\n"
    .balign 4
    .incbin "baserom.dol", 0x3FDD7C, 0x4
.global lbl_80400D80
lbl_80400D80:
    .asciz "DVDConvertEntrynumToPath(possibly DVDOpen or DVDChangeDir or DVDOpenDir): specified directory or file (%s) doesn't match standard 8.3 format. This is a temporary restriction and will be removed soon\n"
    .balign 4
.global lbl_80400E48
lbl_80400E48:
    .asciz "DVDReadAsync(): specified area is out of the file  "
    .balign 4
    .incbin "baserom.dol", 0x3FDE7C, 0x4
.global lbl_80400E80
lbl_80400E80:
    .asciz "app booted via JTAG\n"
    .balign 4
    .asciz "load fst\n"
    .balign 4
    .asciz "app booted from bootrom\n"
    .balign 4
    .asciz "bootrom\n"
    .balign 4
.global jtbl_80400ECC
jtbl_80400ECC:
	.incbin "baserom.dol", 0x3FDECC, 0x20
.global jtbl_80400EEC
jtbl_80400EEC:
	.incbin "baserom.dol", 0x3FDEEC, 0x40
.global jtbl_80400F2C
jtbl_80400F2C:
	.incbin "baserom.dol", 0x3FDF2C, 0x34
.global jtbl_80400F60
jtbl_80400F60:
	.incbin "baserom.dol", 0x3FDF60, 0x38
.global lbl_80400F98
lbl_80400F98:
	.incbin "baserom.dol", 0x3FDF98, 0x40
.global lbl_80400FD8
lbl_80400FD8:
    .asciz "  Game Name ... %c%c%c%c\n"
    .balign 4
    .asciz "  Company ..... %c%c\n"
    .balign 4
    .asciz "  Disk # ...... %d\n"
    .balign 4
    .asciz "  Game ver .... %d\n"
    .balign 4
    .asciz "  Streaming ... %s\n"
    .balign 4
.global jtbl_80401048
jtbl_80401048:
	.incbin "baserom.dol", 0x3FE048, 0x68
.global jtbl_804010B0
jtbl_804010B0:
	.incbin "baserom.dol", 0x3FE0B0, 0x44
.global jtbl_804010F4
jtbl_804010F4:
	.incbin "baserom.dol", 0x3FE0F4, 0x1C
.global jtbl_80401110
jtbl_80401110:
	.incbin "baserom.dol", 0x3FE110, 0x58
.global lbl_80401168
lbl_80401168:
	.incbin "baserom.dol", 0x3FE168, 0x3C
.global lbl_804011A4
lbl_804011A4:
	.incbin "baserom.dol", 0x3FE1A4, 0x3C
.global lbl_804011E0
lbl_804011E0:
	.incbin "baserom.dol", 0x3FE1E0, 0x3C
.global lbl_8040121C
lbl_8040121C:
	.incbin "baserom.dol", 0x3FE21C, 0x3C
.global lbl_80401258
lbl_80401258:
	.incbin "baserom.dol", 0x3FE258, 0x40
.global jtbl_80401298
jtbl_80401298:
	.incbin "baserom.dol", 0x3FE298, 0x20
.global jtbl_804012B8
jtbl_804012B8:
	.incbin "baserom.dol", 0x3FE2B8, 0xF4
.global jtbl_804013AC
jtbl_804013AC:
	.incbin "baserom.dol", 0x3FE3AC, 0xF4
.global jtbl_804014A0
jtbl_804014A0:
	.incbin "baserom.dol", 0x3FE4A0, 0x40
.global lbl_804014E0
lbl_804014E0:
	.incbin "baserom.dol", 0x3FE4E0, 0x28
.global lbl_80401508
lbl_80401508:
	.incbin "baserom.dol", 0x3FE508, 0x20
.global jtbl_80401528
jtbl_80401528:
	.incbin "baserom.dol", 0x3FE528, 0x5C
.global jtbl_80401584
jtbl_80401584:
	.incbin "baserom.dol", 0x3FE584, 0x94
.global lbl_80401618
lbl_80401618:
    .asciz "\nDolphin OS $Revision: 47 $.\n"
    .balign 4
    .asciz "Kernel built : %s %s\n"
    .balign 4
    .asciz "Nov 12 2001"
    .balign 4
    .asciz "01:46:17"
    .balign 4
    .asciz "Console Type : "
    .balign 4
    .asciz "Retail %d\n"
    .balign 4
    .asciz "Mac Emulator\n"
    .balign 4
    .asciz "PC Emulator\n"
    .balign 4
    .asciz "EPPC Arthur\n"
    .balign 4
    .asciz "EPPC Minnow\n"
    .balign 4
    .asciz "Development HW%d\n"
    .balign 4
    .asciz "Memory %d MB\n"
    .balign 4
    .asciz "Arena : 0x%x - 0x%x\n"
    .balign 4
    .incbin "baserom.dol", 0x3FE700, 0xD8
.global lbl_804017D8
lbl_804017D8:
    .asciz "OSCheckHeap: Failed HeapArray in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed 0 <= heap && heap < NumHeaps in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed 0 <= hd->size in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed hd->allocated == NULL || hd->allocated->prev == NULL in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed InRange(cell, ArenaStart, ArenaEnd) in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed OFFSET(cell, ALIGNMENT) == 0 in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed cell->next == NULL || cell->next->prev == cell in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed MINOBJSIZE <= cell->size in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed OFFSET(cell->size, ALIGNMENT) == 0 in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed 0 < total && total <= hd->size in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed hd->free == NULL || hd->free->prev == NULL in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed cell->next == NULL || (char*) cell + cell->size < (char*) cell->next in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed total == hd->size in %d"
    .balign 4
    .asciz "\nOSDumpHeap(%d):\n"
    .balign 4
    .asciz "--------Inactive\n"
    .balign 4
    .asciz "addr\tsize\t\tend\tprev\tnext\n"
    .balign 4
    .asciz "--------Allocated\n"
    .balign 4
    .asciz "%x\t%d\t%x\t%x\t%x\n"
    .balign 4
    .asciz "--------Free\n"
    .balign 4
    .incbin "baserom.dol", 0x3FEB6C, 0x4
.global lbl_80401B70
lbl_80401B70:
	.incbin "baserom.dol", 0x3FEB70, 0x80
.global lbl_80401BF0
lbl_80401BF0:
    .asciz ">>> L2 INVALIDATE : SHOULD NEVER HAPPEN\n"
    .balign 4
    .asciz "Machine check received\n"
    .balign 4
    .asciz "HID2 = 0x%x   SRR1 = 0x%x\n"
    .balign 4
    .asciz "Machine check was not DMA/locked cache related\n"
    .balign 4
    .asciz "DMAErrorHandler(): An error occurred while processing DMA.\n"
    .balign 4
    .asciz "The following errors have been detected and cleared :\n"
    .balign 4
    .asciz "\t- Requested a locked cache tag that was already in the cache\n"
    .balign 4
    .asciz "\t- DMA attempted to access normal cache\n"
    .balign 4
    .asciz "\t- DMA missed in data cache\n"
    .balign 4
    .asciz "\t- DMA queue overflowed\n"
    .balign 4
    .asciz "L1 i-caches initialized\n"
    .balign 4
    .asciz "L1 d-caches initialized\n"
    .balign 4
    .asciz "L2 cache initialized\n"
    .balign 4
    .asciz "Locked cache machine check handler installed\n"
    .balign 4
    .incbin "baserom.dol", 0x3FEE1C, 0x4
.global lbl_80401E20
lbl_80401E20:
    .asciz "------------------------- Context 0x%08x -------------------------\n"
    .balign 4
    .asciz "r%-2d  = 0x%08x (%14d)  r%-2d  = 0x%08x (%14d)\n"
    .balign 4
    .asciz "LR   = 0x%08x                   CR   = 0x%08x\n"
    .balign 4
    .asciz "SRR0 = 0x%08x                   SRR1 = 0x%08x\n"
    .balign 4
    .asciz "\nGQRs----------\n"
    .balign 4
    .asciz "gqr%d = 0x%08x \t gqr%d = 0x%08x\n"
    .balign 4
    .asciz "\n\nFPRs----------\n"
    .balign 4
    .asciz "fr%d \t= %d \t fr%d \t= %d\n"
    .balign 4
    .asciz "\n\nPSFs----------\n"
    .balign 4
    .asciz "ps%d \t= 0x%x \t ps%d \t= 0x%x\n"
    .balign 4
    .asciz "\nAddress:      Back Chain    LR Save\n"
    .balign 4
    .asciz "0x%08x:   0x%08x    0x%08x\n"
    .balign 4
.global lbl_80401FD4
lbl_80401FD4:
    .asciz "FPU-unavailable handler installed\n"
    .balign 4
.global lbl_80401FF8
lbl_80401FF8:
    .asciz " in \"%s\" on line %d.\n"
    .balign 4
    .asciz "\nAddress:      Back Chain    LR Save\n"
    .balign 4
    .asciz "0x%08x:   0x%08x    0x%08x\n"
    .balign 4
    .asciz "Non-recoverable Exception %d"
    .balign 4
    .asciz "Unhandled Exception %d"
    .balign 4
    .asciz "\nDSISR = 0x%08x                   DAR  = 0x%08x\n"
    .balign 4
    .asciz "TB = 0x%016llx\n"
    .balign 4
    .asciz "\nInstruction at 0x%x (read from SRR0) attempted to access invalid address 0x%x (read from DAR)\n"
    .balign 4
    .asciz "\nAttempted to fetch instruction from invalid address 0x%x (read from SRR0)\n"
    .balign 4
    .asciz "\nInstruction at 0x%x (read from SRR0) attempted to access unaligned address 0x%x (read from DAR)\n"
    .balign 4
    .asciz "\nProgram exception : Possible illegal instruction/operation at or around 0x%x (read from SRR0)\n"
    .balign 4
    .asciz "AI DMA Address =   0x%04x%04x\n"
    .balign 4
    .asciz "ARAM DMA Address = 0x%04x%04x\n"
    .balign 4
    .asciz "DI DMA Address =   0x%08x\n"
    .balign 4
    .asciz "\nLast interrupt (%d): SRR0 = 0x%08x  TB = 0x%016llx\n"
    .balign 4
.global jtbl_804022D4
jtbl_804022D4:
	.incbin "baserom.dol", 0x3FF2D4, 0x44
.global lbl_80402318
lbl_80402318:
	.incbin "baserom.dol", 0x3FF318, 0x30
.global lbl_80402348
lbl_80402348:
	.incbin "baserom.dol", 0x3FF348, 0x10
.global lbl_80402358
lbl_80402358:
	.incbin "baserom.dol", 0x3FF358, 0x14
.global lbl_8040236C
lbl_8040236C:
	.incbin "baserom.dol", 0x3FF36C, 0xB4
.global lbl_80402420
lbl_80402420:
    .asciz "OSCheckActiveThreads: Failed RunQueue[prio].head != NULL && RunQueue[prio].tail != NULL in %d\n"
    .balign 4
    .asciz "OSThread.c"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed RunQueue[prio].head == NULL && RunQueue[prio].tail == NULL in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed CheckThreadQueue(&RunQueue[prio]) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed __OSActiveThreadQueue.head == NULL || __OSActiveThreadQueue.head->linkActive.prev == NULL in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed __OSActiveThreadQueue.tail == NULL || __OSActiveThreadQueue.tail->linkActive.next == NULL in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->linkActive.next == NULL || thread == thread->linkActive.next->linkActive.prev in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->linkActive.prev == NULL || thread == thread->linkActive.prev->linkActive.next in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed *(thread->stackEnd) == OS_THREAD_STACK_MAGIC in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed OS_PRIORITY_MIN <= thread->priority && thread->priority <= OS_PRIORITY_MAX+1 in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed 0 <= thread->suspend in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed CheckThreadQueue(&thread->queueJoin) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->queue == &RunQueue[thread->priority] in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed IsMember(&RunQueue[thread->priority], thread) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->priority == __OSGetEffectivePriority(thread) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed !IsSuspended(thread->suspend) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->queue == NULL in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->queue != NULL in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed CheckThreadQueue(thread->queue) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed IsMember(thread->queue, thread) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->priority == 32 in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed !__OSCheckDeadLock(thread) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->queueMutex.head == NULL && thread->queueMutex.tail == NULL in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed. unkown thread state (%d) of thread %p\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed __OSCheckMutexes(thread) in %d\n"
    .balign 4
.global lbl_80402C30
lbl_80402C30:
	.incbin "baserom.dol", 0x3FFC30, 0x30
.global lbl_80402C60
lbl_80402C60:
	.incbin "baserom.dol", 0x3FFC60, 0x30
.global lbl_80402C90
lbl_80402C90:
	.incbin "baserom.dol", 0x3FFC90, 0x98
.global lbl_80402D28
lbl_80402D28:
	.incbin "baserom.dol", 0x3FFD28, 0x164
.global jtbl_80402E8C
jtbl_80402E8C:
	.incbin "baserom.dol", 0x3FFE8C, 0x164
.global lbl_80402FF0
lbl_80402FF0:
	.incbin "baserom.dol", 0x3FFFF0, 0x10
.global lbl_80403000
lbl_80403000:
	.incbin "baserom.dol", 0x400000, 0x160
.global lbl_80403160
lbl_80403160:
	.incbin "baserom.dol", 0x400160, 0x20
.global lbl_80403180
lbl_80403180:
	.incbin "baserom.dol", 0x400180, 0x20
.global lbl_804031A0
lbl_804031A0:
	.incbin "baserom.dol", 0x4001A0, 0x14
.global lbl_804031B4
lbl_804031B4:
	.incbin "baserom.dol", 0x4001B4, 0x8C
.global lbl_80403240
lbl_80403240:
	.incbin "baserom.dol", 0x400240, 0x19E0
.global lbl_80404C20
lbl_80404C20:
	.incbin "baserom.dol", 0x401C20, 0x20
.global lbl_80404C40
lbl_80404C40:
	.incbin "baserom.dol", 0x401C40, 0x10
.global lbl_80404C50
lbl_80404C50:
	.incbin "baserom.dol", 0x401C50, 0x800
.global lbl_80405450
lbl_80405450:
	.incbin "baserom.dol", 0x402450, 0x44
.global lbl_80405494
lbl_80405494:
    .asciz "mobj has unexpected blending flags (0x%x)."
    .balign 4
    .asciz "hsdIsDescendantOf(info, &hsdDObj)"
    .balign 4
    .asciz "can not find specified pobj in link.\n"
    .balign 4
    .asciz "can not find specified pobj in link."
    .balign 4
    .asciz "dobj->mobj == mobj"
    .balign 4
    .asciz "sysdolphin_base_library"
    .balign 4
    .asciz "hsd_dobj"
    .balign 4
    .incbin "baserom.dol", 0x40256C, 0x4
.global lbl_80405570
lbl_80405570:
	.incbin "baserom.dol", 0x402570, 0x48
.global lbl_804055B8
lbl_804055B8:
    .asciz "tobj->imagetbl"
    .balign 4
.global jtbl_804055C8
jtbl_804055C8:
	.incbin "baserom.dol", 0x4025C8, 0x64
.global lbl_8040562C
lbl_8040562C:
    .asciz "unexpected texmap id.\n"
    .balign 4
.global jtbl_80405644
jtbl_80405644:
	.incbin "baserom.dol", 0x402644, 0x20
.global lbl_80405664
lbl_80405664:
    .asciz "tobj->repeat_s && tobj->repeat_t"
    .balign 4
.global lbl_80405688
lbl_80405688:
	.incbin "baserom.dol", 0x402688, 0x30
.global lbl_804056B8
lbl_804056B8:
	.incbin "baserom.dol", 0x4026B8, 0x108
.global lbl_804057C0
lbl_804057C0:
	.incbin "baserom.dol", 0x4027C0, 0x24
.global lbl_804057E4
lbl_804057E4:
	.incbin "baserom.dol", 0x4027E4, 0x54
.global jtbl_80405838
jtbl_80405838:
	.incbin "baserom.dol", 0x402838, 0x20
.global jtbl_80405858
jtbl_80405858:
	.incbin "baserom.dol", 0x402858, 0x20
.global jtbl_80405878
jtbl_80405878:
	.incbin "baserom.dol", 0x402878, 0x20
.global jtbl_80405898
jtbl_80405898:
	.incbin "baserom.dol", 0x402898, 0x20
.global lbl_804058B8
lbl_804058B8:
    .asciz "specified texmtx id desn't exist.\n"
    .balign 4
.global jtbl_804058DC
jtbl_804058DC:
	.incbin "baserom.dol", 0x4028DC, 0x7C
.global lbl_80405958
lbl_80405958:
    .asciz "texmtx index exceed hardware limit (%d).\n"
    .balign 4
.global jtbl_80405984
jtbl_80405984:
	.incbin "baserom.dol", 0x402984, 0x2C
.global jtbl_804059B0
jtbl_804059B0:
	.incbin "baserom.dol", 0x4029B0, 0x20
.global jtbl_804059D0
jtbl_804059D0:
	.incbin "baserom.dol", 0x4029D0, 0x68
.global lbl_80405A38
lbl_80405A38:
	.incbin "baserom.dol", 0x402A38, 0x120
.global lbl_80405B58
lbl_80405B58:
	.incbin "baserom.dol", 0x402B58, 0x40
.global lbl_80405B98
lbl_80405B98:
	.incbin "baserom.dol", 0x402B98, 0x30
.global lbl_80405BC8
lbl_80405BC8:
	.incbin "baserom.dol", 0x402BC8, 0xC0
.global jtbl_80405C88
jtbl_80405C88:
	.incbin "baserom.dol", 0x402C88, 0x40
.global jtbl_80405CC8
jtbl_80405CC8:
	.incbin "baserom.dol", 0x402CC8, 0x40
.global jtbl_80405D08
jtbl_80405D08:
	.incbin "baserom.dol", 0x402D08, 0x40
.global jtbl_80405D48
jtbl_80405D48:
	.incbin "baserom.dol", 0x402D48, 0x20
.global lbl_80405D68
lbl_80405D68:
	.incbin "baserom.dol", 0x402D68, 0xC0
.global lbl_80405E28
lbl_80405E28:
	.incbin "baserom.dol", 0x402E28, 0x50
.global jtbl_80405E78
jtbl_80405E78:
	.incbin "baserom.dol", 0x402E78, 0x5C
.global lbl_80405ED4
lbl_80405ED4:
    .asciz "mobj->tevdesc"
    .balign 4
    .incbin "baserom.dol", 0x402EE4, 0xD4
.global lbl_80405FB8
lbl_80405FB8:
    .asciz "object.h"
    .balign 4
.global lbl_80405FC4
lbl_80405FC4:
    .asciz "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF"
    .balign 4
.global jtbl_80405FEC
jtbl_80405FEC:
	.incbin "baserom.dol", 0x402FEC, 0x30
.global lbl_8040601C
lbl_8040601C:
    .asciz "unexpected argument format.\n"
    .balign 4
.global lbl_8040603C
lbl_8040603C:
    .asciz "unexpected type of object.\n"
    .balign 4
.global jtbl_80406058
jtbl_80406058:
	.incbin "baserom.dol", 0x403058, 0x34
.global jtbl_8040608C
jtbl_8040608C:
	.incbin "baserom.dol", 0x40308C, 0x34
.global lbl_804060C0
lbl_804060C0:
	.incbin "baserom.dol", 0x4030C0, 0x40
.global jtbl_80406100
jtbl_80406100:
	.incbin "baserom.dol", 0x403100, 0x38
.global lbl_80406138
lbl_80406138:
    .asciz "object.h"
    .balign 4
.global lbl_80406144
lbl_80406144:
    .asciz "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF"
    .balign 4
.global jtbl_8040616C
jtbl_8040616C:
	.incbin "baserom.dol", 0x40316C, 0x24
.global lbl_80406190
lbl_80406190:
    .asciz "lobj->position"
    .balign 4
.global lbl_804061A0
lbl_804061A0:
    .asciz "lobj->interest"
    .balign 4
    .asciz "hsdIsDescendantOf(info, &hsdLObj)"
    .balign 4
.global lbl_804061D4
lbl_804061D4:
    .asciz "unexpected lightdesc flags (%x)\n"
    .balign 4
    .asciz "sysdolphin_base_library"
    .balign 4
    .asciz "hsd_lobj"
    .balign 4
    .incbin "baserom.dol", 0x40321C, 0x4
.global lbl_80406220
lbl_80406220:
	.incbin "baserom.dol", 0x403220, 0x40
.global jtbl_80406260
jtbl_80406260:
	.incbin "baserom.dol", 0x403260, 0x34
.global lbl_80406294
lbl_80406294:
    .asciz "unkown type of render pass.\n"
    .balign 4
.global lbl_804062B4
lbl_804062B4:
    .asciz "cobj->eyepos"
    .balign 4
.global lbl_804062C4
lbl_804062C4:
    .asciz "cobj->interest"
    .balign 4
    .incbin "baserom.dol", 0x4032D4, 0x48
.global lbl_8040631C
lbl_8040631C:
	.incbin "baserom.dol", 0x40331C, 0x34
.global lbl_80406350
lbl_80406350:
    .asciz "st == FOBJ_LOAD_WAIT"
    .balign 4
    .asciz "st == FOBJ_LOAD_DATA0 || st == FOBJ_LOAD_DATA"
    .balign 4
.global lbl_80406398
lbl_80406398:
	.incbin "baserom.dol", 0x403398, 0x48
.global lbl_804063E0
lbl_804063E0:
    .asciz "pobj_type(pobj) == POBJ_SHAPEANIM && pobj->u.shape_set"
    .balign 4
.global lbl_80406418
lbl_80406418:
    .asciz "envelope"
    .balign 4
.global lbl_80406424
lbl_80406424:
    .asciz "shape_set"
    .balign 4
.global lbl_80406430
lbl_80406430:
    .asciz "pobj: unexected type.\n"
    .balign 4
.global lbl_80406448
lbl_80406448:
    .asciz "hsdIsDescendantOf(info, &hsdPObj)"
    .balign 4
    .asciz "env->jobj"
    .balign 4
    .asciz "object.h"
    .balign 4
    .asciz "HSD_OBJ(o)->ref_count_individual != 0"
    .balign 4
    .asciz "pobj->u.jobj"
    .balign 4
.global lbl_804064BC
lbl_804064BC:
    .asciz "shape_set->vertex_desc->comp_cnt == GX_POS_XYZ"
    .balign 4
.global lbl_804064EC
lbl_804064EC:
    .asciz "unexpected vertex type.\n"
    .balign 4
.global lbl_80406508
lbl_80406508:
    .asciz "shape_set->normal_desc->comp_cnt == GX_NRM_XYZ"
    .balign 4
.global lbl_80406538
lbl_80406538:
    .asciz "unexpected normal type."
    .balign 4
    .asciz "shape_set->normal_desc->attr == GX_VA_NBT"
    .balign 4
.global lbl_8040657C
lbl_8040657C:
    .asciz "attr(%d) is not supported by sysdolphin\n"
    .balign 4
.global lbl_804065A8
lbl_804065A8:
	.incbin "baserom.dol", 0x4035A8, 0x128
.global lbl_804066D0
lbl_804066D0:
    .asciz "pobj->u.shape_set"
    .balign 4
    .asciz "sysdolphin_base_library"
    .balign 4
    .asciz "hsd_pobj"
    .balign 4
.global lbl_80406708
lbl_80406708:
	.incbin "baserom.dol", 0x403708, 0x50
.global lbl_80406758
lbl_80406758:
    .asciz "jobj->parent"
    .balign 4
    .asciz "jobj->aobj"
    .balign 4
    .asciz "jp->u.spline"
    .balign 4
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global jtbl_804067AC
jtbl_804067AC:
	.incbin "baserom.dol", 0x4037AC, 0xE8
.global lbl_80406894
lbl_80406894:
    .asciz "hsdIsDescendantOf(info, &hsdJObj)"
    .balign 4
    .asciz "jobj_root"
    .balign 4
    .asciz "jobj_root == NULL"
    .balign 4
    .asciz "jobj->child"
    .balign 4
.global lbl_804068E4
lbl_804068E4:
    .asciz "object.h"
    .balign 4
    .asciz "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF"
    .balign 4
.global lbl_80406918
lbl_80406918:
    .asciz "HSD_OBJ(o)->ref_count_individual != 0"
    .balign 4
    .asciz "child->next == NULL"
    .balign 4
    .asciz "child should be a orphan.\n"
    .balign 4
    .asciz "child->parent == NULL"
    .balign 4
    .asciz "child should not have siblings"
    .balign 4
    .asciz "!(jobj->flags & JOBJ_INSTANCE)"
    .balign 4
    .asciz "last != child"
    .balign 4
.global lbl_804069D8
lbl_804069D8:
    .asciz "can not find specified jobj. maybe jobj tree is broken.\n"
    .balign 4
    .asciz "jobj[%d,%d]"
    .balign 4
    .asciz "SKELETON_ROOT "
    .balign 4
    .asciz "SKELETON "
    .balign 4
    .asciz "ENVELOPE_MODEL "
    .balign 4
    .asciz "EFFECTOR "
    .balign 4
    .asciz "  rot(L): "
    .balign 4
    .asciz "  sca(L): "
    .balign 4
    .asciz "  tra(L): "
    .balign 4
    .asciz "  rot(G): "
    .balign 4
    .asciz "  sca(G): "
    .balign 4
    .asciz "  tra(G): "
    .balign 4
    .asciz "sysdolphin_base_library"
    .balign 4
    .asciz "hsd_jobj"
    .balign 4
    .incbin "baserom.dol", 0x403AC4, 0x1C
.global lbl_80406AE0
lbl_80406AE0:
	.incbin "baserom.dol", 0x403AE0, 0xC
.global lbl_80406AEC
lbl_80406AEC:
	.incbin "baserom.dol", 0x403AEC, 0x18
.global lbl_80406B04
lbl_80406B04:
    .asciz "displayfunc.c"
    .balign 4
.global lbl_80406B14
lbl_80406B14:
    .asciz "unkown type of billboard.\n"
    .balign 4
    .incbin "baserom.dol", 0x403B30, 0x10
.global lbl_80406B40
lbl_80406B40:
	.incbin "baserom.dol", 0x403B40, 0x80
.global lbl_80406BC0
lbl_80406BC0:
    .asciz "initialize.c"
    .balign 4
.global lbl_80406BD0
lbl_80406BD0:
    .asciz "No memory space remains for XFB.\n"
    .balign 4
    .asciz "cannot allocate memory for gx fifo.\n"
    .balign 4
    .asciz "no space remains for gx fifo.\n"
    .balign 4
.global lbl_80406C3C
lbl_80406C3C:
    .asciz "sysdolphin_base_library"
    .balign 4
    .asciz "pix_fmt != GX_PF_RGB565_Z16"
    .balign 4
    .asciz "objalloc.h"
    .balign 4
    .asciz "objalloc: %s\tusing %d\tfreed %d\tpeak %d\n"
    .balign 4
.global lbl_80406CA4
lbl_80406CA4:
    .asciz "init parameter should be set before invoking HSD_Init().\n"
    .balign 4
.global lbl_80406CE0
lbl_80406CE0:
    .asciz "idx != -1"
    .balign 4
.global lbl_80406CEC
lbl_80406CEC:
    .asciz "unexpected type of render pass.\n"
    .balign 4
.global lbl_80406D10
lbl_80406D10:
    .asciz "_p->xfb[idx].status == HSD_VI_XFB_DRAWING"
    .balign 4
.global lbl_80406D3C
lbl_80406D3C:
    .asciz "_p->xfb[idx].status == HSD_VI_XFB_WAITDONE"
    .balign 4
.global lbl_80406D68
lbl_80406D68:
	.incbin "baserom.dol", 0x403D68, 0x44
.global lbl_80406DAC
lbl_80406DAC:
	.incbin "baserom.dol", 0x403DAC, 0x34
.global lbl_80406DE0
lbl_80406DE0:
	.incbin "baserom.dol", 0x403DE0, 0x10
.global lbl_80406DF0
lbl_80406DF0:
	.incbin "baserom.dol", 0x403DF0, 0x30
.global jtbl_80406E20
jtbl_80406E20:
	.incbin "baserom.dol", 0x403E20, 0x28
.global lbl_80406E48
lbl_80406E48:
	.incbin "baserom.dol", 0x403E48, 0x10
.global lbl_80406E58
lbl_80406E58:
    .asciz "objalloc.c"
    .balign 4
    .incbin "baserom.dol", 0x403E64, 0x4
.global lbl_80406E68
lbl_80406E68:
    .asciz "rp->u.jobj"
    .balign 4
.global lbl_80406E74
lbl_80406E74:
	.incbin "baserom.dol", 0x403E74, 0xC
.global lbl_80406E80
lbl_80406E80:
	.incbin "baserom.dol", 0x403E80, 0x78
.global lbl_80406EF8
lbl_80406EF8:
    .asciz "unexpected type of robj.\n"
    .balign 4
    .asciz "(ptr && nitems) || !ptr"
    .balign 4
.global lbl_80406F2C
lbl_80406F2C:
    .asciz "Number of argment of expression exceeds the argument buffer\nsize. (requested num of arg %d, allocated %d)\n"
    .balign 4
    .asciz "rvalue->jobj"
    .balign 4
    .asciz "constraint only support jobj target.\n"
    .balign 4
.global lbl_80406FD0
lbl_80406FD0:
	.incbin "baserom.dol", 0x403FD0, 0x40
.global lbl_80407010
lbl_80407010:
    .asciz "wobj->aobj"
    .balign 4
.global lbl_8040701C
lbl_8040701C:
    .asciz "jp->u.spline"
    .balign 4
    .asciz "hsdIsDescendantOf(info, &hsdWObj)"
    .balign 4
    .asciz "sysdolphin_base_library"
    .balign 4
    .asciz "had_wobj"
    .balign 4
    .incbin "baserom.dol", 0x404074, 0x4
.global lbl_80407078
lbl_80407078:
	.incbin "baserom.dol", 0x404078, 0x3C
.global lbl_804070B4
lbl_804070B4:
	.incbin "baserom.dol", 0x4040B4, 0x3C
.global lbl_804070F0
lbl_804070F0:
    .asciz "You must specify CObj first.\n"
    .balign 4
.global jtbl_80407110
jtbl_80407110:
	.incbin "baserom.dol", 0x404110, 0x78
.global lbl_80407188
lbl_80407188:
	.incbin "baserom.dol", 0x404188, 0x90
.global lbl_80407218
lbl_80407218:
	.incbin "baserom.dol", 0x404218, 0x90
.global lbl_804072A8
lbl_804072A8:
	.incbin "baserom.dol", 0x4042A8, 0x3C
.global lbl_804072E4
lbl_804072E4:
    .asciz "sysdolphin_base_library"
    .balign 4
    .incbin "baserom.dol", 0x4042FC, 0x4
.global lbl_80407300
lbl_80407300:
    .asciz "memory.c"
    .balign 4
    .incbin "baserom.dol", 0x40430C, 0x4
.global lbl_80407310
lbl_80407310:
    .asciz "shadow.c"
    .balign 4
    .asciz "width > 0"
    .balign 4
    .asciz "height > 0"
    .balign 4
    .asciz "size > 0"
    .balign 4
    .incbin "baserom.dol", 0x404340, 0xFC
.global lbl_8040743C
lbl_8040743C:
    .asciz "object.h"
    .balign 4
.global lbl_80407448
lbl_80407448:
    .asciz "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF"
    .balign 4
    .asciz "scale > 0.0F"
    .balign 4
    .asciz "position"
    .balign 4
    .asciz "radius > 0.0F"
    .balign 4
    .asciz "a > 0.0F"
    .balign 4
.global lbl_804074A8
lbl_804074A8:
    .asciz "HSD_ArchiveParse: byte-order mismatch! Please check data format %x %x\n"
    .balign 4
.global lbl_804074F0
lbl_804074F0:
    .asciz "bytecode.c"
    .balign 4
    .asciz "operand < nb_args"
    .balign 4
    .asciz "specified stack doesn't exist (%d).\n"
    .balign 4
    .asciz "not yet implemented.\n"
    .balign 4
    .asciz "unexpected byte code.\n"
    .balign 4
    .asciz "stack->next"
    .balign 4
    .asciz "unexpected opcode 0x%x.\n"
    .balign 4
.global lbl_80407590
lbl_80407590:
	.incbin "baserom.dol", 0x404590, 0x3C
.global lbl_804075CC
lbl_804075CC:
    .asciz "class_info->head.obj_size >= parent_info->head.obj_size"
    .balign 4
.global lbl_80407604
lbl_80407604:
    .asciz "class_info->head.info_size >= parent_info->head.info_size"
    .balign 4
    .asciz "entry %d <null>\n"
    .balign 4
    .asciz "entry %d - %d <null>\n"
    .balign 4
    .asciz "entry %d(%d)"
    .balign 4
    .asciz "  nb_alloc %d nb_free %d\n"
    .balign 4
.global lbl_80407698
lbl_80407698:
    .asciz "idx >= 0"
    .balign 4
    .asciz "sysdolphin_base_library"
    .balign 4
    .asciz "hsd_class"
    .balign 4
.global lbl_804076C8
lbl_804076C8:
    .asciz "class_info"
    .balign 4
    .asciz "info_hash"
    .balign 4
    .asciz "<class %s>\n"
    .balign 4
    .asciz "    info %d object %d nb_exist %d nb_peak %d\n"
    .balign 4
    .incbin "baserom.dol", 0x40471C, 0x4
.global lbl_80407720
lbl_80407720:
    .asciz "idx < hash->table_size"
    .balign 4
.global lbl_80407738
lbl_80407738:
    .asciz "texp_list"
    .balign 4
.global lbl_80407744
lbl_80407744:
    .asciz "texp->cnst.ctype == type"
    .balign 4
.global lbl_80407760
lbl_80407760:
    .asciz "HSD_TExpGetType(texp) == HSD_TE_TEV"
    .balign 4
    .asciz "tev can't select multiple konst input.\n"
    .balign 4
    .asciz "sel == HSD_TE_RGB || sel == HSD_TE_A"
    .balign 4
    .asciz "idx == 3 || sel != HSD_TE_RGB || exp->tev.c_clamp"
    .balign 4
    .asciz "idx == 3 || sel != HSD_TE_A || exp->tev.a_clamp"
    .balign 4
    .asciz "swap == HSD_TE_UNDEF || tev->tex_swap == swap"
    .balign 4
    .asciz "swap == HSD_TE_UNDEF || tev->ras_swap == swap"
    .balign 4
.global jtbl_80407898
jtbl_80407898:
	.incbin "baserom.dol", 0x404898, 0xA0
.global jtbl_80407938
jtbl_80407938:
	.incbin "baserom.dol", 0x404938, 0x3C
.global lbl_80407974
lbl_80407974:
	.incbin "baserom.dol", 0x404974, 0xA0
.global lbl_80407A14
lbl_80407A14:
    .asciz "val >= 0"
    .balign 4
    .incbin "baserom.dol", 0x404A20, 0x80
.global lbl_80407AA0
lbl_80407AA0:
    .asciz "texpdag.c"
    .balign 4
    .asciz "HSD_TExpGetType(root) == HSD_TE_TEV"
    .balign 4
    .asciz "j<HSD_TEXP_MAX_NUM"
    .balign 4
    .incbin "baserom.dol", 0x404AE4, 0x34
.global lbl_80407B18
lbl_80407B18:
	.incbin "baserom.dol", 0x404B18, 0x40
.global lbl_80407B58
lbl_80407B58:
	.incbin "baserom.dol", 0x404B58, 0x208
.global lbl_80407D60
lbl_80407D60:
    .asciz "assertion \"%s\" failed"
    .balign 4
.global lbl_80407D78
lbl_80407D78:
    .asciz "%s in %s on line %d.\n"
    .balign 4
.global lbl_80407D90
lbl_80407D90:
    .asciz "audio heap overflow.\n"
    .balign 4
    .asciz "Can't load SFX file; bank(id=%d) buffer overflow.\n"
    .balign 4
    .asciz "hsd_SynthSFXBankHead[bankID + 1] - hsd_SynthSFXBank[bankID] >= hsd_SynthSFXLoadBuf[1]"
    .balign 4
.global lbl_80407E34
lbl_80407E34:
    .asciz "invalid bankID = %d; filename = %s\n"
    .balign 4
.global lbl_80407E58
lbl_80407E58:
    .asciz "(bankID >= 0 && bankID < hsd_SynthSFXBankNum)"
    .balign 4
.global lbl_80407E88
lbl_80407E88:
    .asciz "bank overflow\n"
    .balign 4
.global lbl_80407E98
lbl_80407E98:
    .asciz "hsd_SynthSFXBankHead[hsd_SynthSFXBankNum + 1] <= hsd_SynthSFXBankAREnd"
    .balign 4
    .asciz "bank stack underflow\n"
    .balign 4
    .asciz "hsd_SynthSFXBankNum"
    .balign 4
.global lbl_80407F0C
lbl_80407F0C:
    .asciz "sfxGroupDataReaddressCounter > 0"
    .balign 4
    .asciz "Can't relocate SFX group; bank = %d; sfxgroup = %d\n"
    .balign 4
    .asciz "hsd_SynthSFXBank[bankID] + group->arsize <= hsd_SynthSFXBankHead[bankID + 1]"
    .balign 4
    .incbin "baserom.dol", 0x404FB4, 0x24
.global lbl_80407FD8
lbl_80407FD8:
	.incbin "baserom.dol", 0x404FD8, 0x10
.global lbl_80407FE8
lbl_80407FE8:
    .asciz "sfx group ID %d out of range."
    .balign 4
.global lbl_80408008
lbl_80408008:
    .asciz "group >= 0 && group < HSD_SYNTHSFXGROUP_MAX"
    .balign 4
.global lbl_80408034
lbl_80408034:
    .asciz "flag >= 0 && flag < USERVOL_NUM"
    .balign 4
.global lbl_80408054
lbl_80408054:
    .asciz "flag == 0 || flag == 1"
    .balign 4
    .incbin "baserom.dol", 0x40506C, 0x80
.global lbl_804080EC
lbl_804080EC:
    .asciz "entry->voice[1]"
    .balign 4
    .incbin "baserom.dol", 0x4050FC, 0x44
.global lbl_80408140
lbl_80408140:
    .asciz "axdriver.c"
    .balign 4
.global lbl_8040814C
lbl_8040814C:
    .asciz "axfxallocsize < axfxmaxsize"
    .balign 4
.global lbl_80408168
lbl_80408168:
    .asciz "*head != v"
    .balign 4
.global lbl_80408174
lbl_80408174:
    .asciz "(v->flags&SMSTATE_MASK) == SMSTATE_ACTIVE || (v->flags&SMSTATE_MASK) == SMSTATE_SLEEP"
    .balign 4
.global lbl_804081CC
lbl_804081CC:
    .asciz "(v->flags&SMSTATE_MASK) == SMSTATE_ACTIVE"
    .balign 4
.global jtbl_804081F8
jtbl_804081F8:
	.incbin "baserom.dol", 0x4051F8, 0x58
.global lbl_80408250
lbl_80408250:
	.incbin "baserom.dol", 0x405250, 0x58
.global lbl_804082A8
lbl_804082A8:
	.incbin "baserom.dol", 0x4052A8, 0x8C
.global lbl_80408334
lbl_80408334:
    .asciz "can not open %s\n"
    .balign 4
.global lbl_80408348
lbl_80408348:
    .asciz "file size of \"%s\" is 0\n"
    .balign 4
    .asciz "channel == 0 || channel == 1"
    .balign 4
    .asciz "0 <= type && type <= 4"
    .balign 4
    .asciz "type == 0 || param != NULL"
    .balign 4
    .incbin "baserom.dol", 0x4053B4, 0x4
.global lbl_804083B8
lbl_804083B8:
    .asciz "devcom.c"
    .balign 4
    .asciz "dvdDC->size <= DEVCOM_BUF_SIZE"
    .balign 4
    .asciz "dvdDC->callback"
    .balign 4
    .asciz "!(HSD_DevComGetDestType(type) == DEVCOMDEST_SBUF && size > DEVCOM_BUF_SIZE)"
    .balign 4
    .asciz "src % 32 == 0"
    .balign 4
    .asciz "dest % 32 == 0"
    .balign 4
    .asciz "size % 32 == 0"
    .balign 4
    .asciz "size != 0"
    .balign 4
    .incbin "baserom.dol", 0x40547C, 0x4
.global lbl_80408480
lbl_80408480:
    .asciz "gobjproc.c"
    .balign 4
    .asciz "pri <= HSD_GObjLibInitData.gproc_pri_max"
    .balign 4
.global lbl_804084B8
lbl_804084B8:
    .asciz "gobjplink.c"
    .balign 4
.global lbl_804084C4
lbl_804084C4:
    .asciz "p_link <= HSD_GObjLibInitData.p_link_max"
    .balign 4
.global lbl_804084F0
lbl_804084F0:
    .asciz "gobjgxlink.c"
    .balign 4
.global lbl_80408500
lbl_80408500:
    .asciz "gx_link <= HSD_GObjLibInitData.gx_link_max"
    .balign 4
.global lbl_8040852C
lbl_8040852C:
    .asciz "gobj->gx_link != HSD_GOBJ_GXLINK_NONE"
    .balign 4
    .incbin "baserom.dol", 0x405554, 0x4
.global lbl_80408558
lbl_80408558:
    .asciz "gobjobject.c"
    .balign 4
.global lbl_80408568
lbl_80408568:
    .asciz "gobj->obj_kind == HSD_GOBJ_OBJ_NONE"
    .balign 4
    .incbin "baserom.dol", 0x40558C, 0x4
.global lbl_80408590
lbl_80408590:
    .asciz "gobjuserdata.c"
    .balign 4
.global lbl_804085A0
lbl_804085A0:
    .asciz "gobj->user_data_kind == HSD_GOBJ_USER_DATA_NONE"
    .balign 4
.global lbl_804085D0
lbl_804085D0:
    .asciz "gobj->user_data_remove_func"
    .balign 4
    .incbin "baserom.dol", 0x4055EC, 0x4
.global lbl_804085F0
lbl_804085F0:
	.incbin "baserom.dol", 0x4055F0, 0x20
.global lbl_80408610
lbl_80408610:
	.incbin "baserom.dol", 0x405610, 0x10
.global lbl_80408620
lbl_80408620:
	.incbin "baserom.dol", 0x405620, 0x10
.global lbl_80408630
lbl_80408630:
	.incbin "baserom.dol", 0x405630, 0x268
.global lbl_80408898
lbl_80408898:
	.incbin "baserom.dol", 0x405898, 0x20
.global lbl_804088B8
lbl_804088B8:
	.incbin "baserom.dol", 0x4058B8, 0x1C00
.global lbl_8040A4B8
lbl_8040A4B8:
    .asciz "\\c00ff00%2.3f \\cffffff%2.3f \\c00ffff%2.3f  \\c00ff00%2.3f \\cffffff%2.3f \\c00ffff%2.3f"
    .balign 4
.global lbl_8040A510
lbl_8040A510:
    .asciz "\\c00ff00%2.3f \\cffffff%2.3f \\c00ffff%2.3f"
    .balign 4
    .incbin "baserom.dol", 0x40753C, 0x4
.global lbl_8040A540
lbl_8040A540:
    .asciz "MCC is no initialize"
    .balign 4
    .asciz "No responce"
    .balign 4
    .asciz "PING error"
    .balign 4
    .asciz "Could not initialize HIO"
    .balign 4
    .asciz "Could not read HIO mailbox"
    .balign 4
    .asciz "Could not write HIO mailbox"
    .balign 4
    .asciz "Could not read HIO memory"
    .balign 4
    .asciz "Could not write HIO memory"
    .balign 4
    .asciz "Could not read HIO status"
    .balign 4
    .asciz "Could not flush channelInfo"
    .balign 4
    .asciz "Could not load channelInfo"
    .balign 4
    .asciz "Not enough memory block"
    .balign 4
    .asciz "Invalid function parameter"
    .balign 4
    .asciz "Invalid channel parameter"
    .balign 4
    .asciz "Invalid data size"
    .balign 4
    .asciz "Invalid offset parameter"
    .balign 4
    .asciz "Channel was (already) opened"
    .balign 4
    .asciz "Channel was (already) closed"
    .balign 4
    .asciz "Channel was (already) locked"
    .balign 4
    .asciz "Channel was (already) unlocked"
    .balign 4
    .asciz "Channel (read/write) busy"
    .balign 4
    .asciz "Unknown error"
    .balign 4
    .asciz "%s: MCC Error, %s (%d)\n"
    .balign 4
    .asciz "MCC Error, %s (%d)\n"
    .balign 4
.global jtbl_8040A7A8
jtbl_8040A7A8:
	.incbin "baserom.dol", 0x4077A8, 0x138
.global lbl_8040A8E0
lbl_8040A8E0:
    .asciz "EXI_%d:not support USB (Error=%d)\n"
    .balign 4
.global lbl_8040A904
lbl_8040A904:
    .asciz "EXI initialized (EXI_%d)\n"
    .balign 4
.global lbl_8040A920
lbl_8040A920:
    .asciz "Error(0x%x) in MCCNotify.\n"
    .balign 4
.global lbl_8040A93C
lbl_8040A93C:
	.incbin "baserom.dol", 0x40793C, 0x94
.global lbl_8040A9D0
lbl_8040A9D0:
    .asciz "loading file (%s) from USB ..."
    .balign 4
    .asciz "cannot open file\n"
    .balign 4
    .asciz "cannot get files stat\n"
    .balign 4
    .asciz "too large file size\n"
    .balign 4
    .asciz "cannot allocate memory\n"
    .balign 4
    .asciz "cannot load file\n"
    .balign 4
    .asciz "Done %s size:%d time:%f spped:%fkbps\n"
    .balign 4
    .asciz "cannot save file\n"
    .balign 4
    .asciz "Seaching files (%s) via USB ..."
    .balign 4
    .asciz "cannot get dir stat\n"
    .balign 4
    .asciz "too large dir size\n"
    .balign 4
    .asciz "cannot use USB now.\n"
    .balign 4
.global lbl_8040AB00
lbl_8040AB00:
	.incbin "baserom.dol", 0x407B00, 0x20
.global lbl_8040AB20
lbl_8040AB20:
	.incbin "baserom.dol", 0x407B20, 0x20
.global lbl_8040AB40
lbl_8040AB40:
	.incbin "baserom.dol", 0x407B40, 0xD30
.global jtbl_8040B870
jtbl_8040B870:
	.incbin "baserom.dol", 0x408870, 0x3C
.global lbl_8040B8AC
lbl_8040B8AC:
    .asciz "<< Push START Button >>"
    .balign 4
    .incbin "baserom.dol", 0x4088C4, 0x14
.global lbl_8040B8D8
lbl_8040B8D8:
    .asciz "<<PUSH START BUTTON TO SEE INSTRUCTION>>"
    .balign 4
.global lbl_8040B904
lbl_8040B904:
	.incbin "baserom.dol", 0x408904, 0x10
.global jtbl_8040B914
jtbl_8040B914:
	.incbin "baserom.dol", 0x408914, 0x1DC
.global lbl_8040BAF0
lbl_8040BAF0:
	.incbin "baserom.dol", 0x408AF0, 0x14
.global jtbl_8040BB04
jtbl_8040BB04:
	.incbin "baserom.dol", 0x408B04, 0x138
.global lbl_8040BC3C
lbl_8040BC3C:
	.incbin "baserom.dol", 0x408C3C, 0x1C
.global jtbl_8040BC58
jtbl_8040BC58:
	.incbin "baserom.dol", 0x408C58, 0x26C
.global lbl_8040BEC4
lbl_8040BEC4:
	.incbin "baserom.dol", 0x408EC4, 0x4C
.global lbl_8040BF10
lbl_8040BF10:
    .asciz "unsupported no. of special purpose register (%d)."
    .balign 4
    .incbin "baserom.dol", 0x408F44, 0x2C
.global lbl_8040BF70
lbl_8040BF70:
	.incbin "baserom.dol", 0x408F70, 0x40
.global lbl_8040BFB0
lbl_8040BFB0:
    .asciz "particle.c"
    .balign 4
    .asciz "illigal form data (strange number of group)\n"
    .balign 4
    .asciz "psInitDataBanks: unknown version\n"
    .balign 4
.global lbl_8040C010
lbl_8040C010:
    .asciz "object.h"
    .balign 4
.global lbl_8040C01C
lbl_8040C01C:
    .asciz "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF"
    .balign 4
.global lbl_8040C044
lbl_8040C044:
	.incbin "baserom.dol", 0x409044, 0x204
.global lbl_8040C248
lbl_8040C248:
    .asciz "generator.c"
    .balign 4
.global lbl_8040C254
lbl_8040C254:
    .asciz "psCamera"
    .balign 4
.global lbl_8040C260
lbl_8040C260:
	.incbin "baserom.dol", 0x409260, 0x20
.global lbl_8040C280
lbl_8040C280:
	.incbin "baserom.dol", 0x409280, 0x24
.global lbl_8040C2A4
lbl_8040C2A4:
    .asciz "object.h"
    .balign 4
.global lbl_8040C2B0
lbl_8040C2B0:
    .asciz "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF"
    .balign 4
.global jtbl_8040C2D8
jtbl_8040C2D8:
	.incbin "baserom.dol", 0x4092D8, 0x28
.global lbl_8040C300
lbl_8040C300:
    .asciz "object.h"
    .balign 4
    .asciz "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF"
    .balign 4
    .incbin "baserom.dol", 0x409334, 0x2C
.global lbl_8040C360
lbl_8040C360:
	.incbin "baserom.dol", 0x409360, 0x40
.global lbl_8040C3A0
lbl_8040C3A0:
	.incbin "baserom.dol", 0x4093A0, 0x4
.global lbl_8040C3A4
lbl_8040C3A4:
	.incbin "baserom.dol", 0x4093A4, 0xC
.global lbl_8040C3B0
lbl_8040C3B0:
    .asciz "sobjlib.c"
    .balign 4
.global lbl_8040C3BC
lbl_8040C3BC:
    .asciz "BadOBJ for SOBJ-displayfunc\n"
    .balign 4
.global jtbl_8040C3DC
jtbl_8040C3DC:
	.incbin "baserom.dol", 0x4093DC, 0xB4
.global lbl_8040C490
lbl_8040C490:
	.incbin "baserom.dol", 0x409490, 0x28
.global lbl_8040C4B8
lbl_8040C4B8:
	.incbin "baserom.dol", 0x4094B8, 0x68
.global lbl_8040C520
lbl_8040C520:
    .asciz "unknow camera\n"
    .balign 4
    .asciz "Cannot open archive %s.\n"
    .balign 4
    .asciz "Cannot find symbol %s.\n"
    .balign 4
    .incbin "baserom.dol", 0x409564, 0x4
.global lbl_8040C568
lbl_8040C568:
	.incbin "baserom.dol", 0x409568, 0x40
.global lbl_8040C5A8
lbl_8040C5A8:
	.incbin "baserom.dol", 0x4095A8, 0x6C
.global lbl_8040C614
lbl_8040C614:
	.incbin "baserom.dol", 0x409614, 0x6C
.global lbl_8040C680
lbl_8040C680:
	.incbin "baserom.dol", 0x409680, 0x240
.global lbl_8040C8C0
lbl_8040C8C0:
	.incbin "baserom.dol", 0x4098C0, 0x240
.global lbl_8040CB00
lbl_8040CB00:
	.incbin "baserom.dol", 0x409B00, 0x240
.global lbl_8040CD40
lbl_8040CD40:
	.incbin "baserom.dol", 0x409D40, 0x232C4
.global lbl_80430004
lbl_80430004:
	.incbin "baserom.dol", 0x42D004, 0xB3C
.global jtbl_80430B40
jtbl_80430B40:
	.incbin "baserom.dol", 0x42DB40, 0x44
.global lbl_80430B84
lbl_80430B84:
	.incbin "baserom.dol", 0x42DB84, 0x4C
.global lbl_80430BD0
lbl_80430BD0:
	.incbin "baserom.dol", 0x42DBD0, 0x34
.global jtbl_80430C04
jtbl_80430C04:
	.incbin "baserom.dol", 0x42DC04, 0x1C
.global jtbl_80430C20
jtbl_80430C20:
	.incbin "baserom.dol", 0x42DC20, 0x20
.global lbl_80430C40
lbl_80430C40:
	.incbin "baserom.dol", 0x42DC40, 0x40
.global lbl_80430C80
lbl_80430C80:
	.incbin "baserom.dol", 0x42DC80, 0x410
.global lbl_80431090
lbl_80431090:
	.incbin "baserom.dol", 0x42E090, 0x5A8
.global lbl_80431638
lbl_80431638:
	.incbin "baserom.dol", 0x42E638, 0x40
.global lbl_80431678
lbl_80431678:
	.incbin "baserom.dol", 0x42E678, 0x18
.global lbl_80431690
lbl_80431690:
	.incbin "baserom.dol", 0x42E690, 0xC
.global lbl_8043169C
lbl_8043169C:
	.incbin "baserom.dol", 0x42E69C, 0x18
.global lbl_804316B4
lbl_804316B4:
	.incbin "baserom.dol", 0x42E6B4, 0xC

