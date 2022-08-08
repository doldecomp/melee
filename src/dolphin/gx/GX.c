#include <dolphin/gx/GX.h>
#include <dolphin/gx/GXLight.h>
#include <functions.h>
#include <string.h>

#pragma region variables
extern f32 lbl_804DE2F8; // at 0x004DAED8
extern f32 lbl_804DE300; // at 0x004DAEE0
extern f32 lbl_804DE308; // at 0x004DAEE8
extern f32 lbl_804DE30C; // at 0x004DAEEC
#pragma endregion

extern void __GXSetDirtyState();                                                                                                 // at 0x00339C30
extern void func_8033D0DC(s32, s32, s16);                                                                                        // at 0x00339CBC
extern void local_8033D1B8();                                                                                                    // at 0x00339D98
extern void func_8033D240(s32, s32);                                                                                             // at 0x00339E20
extern void func_8033D298(s32, s32);                                                                                             // at 0x00339E78
extern void func_8033D2EC(s32, s32, s32);                                                                                        // at 0x00339ECC
extern void func_8033D350(s32);                                                                                                  // at 0x00339ECC
extern void func_8033D3A0(s32);                                                                                                  // at 0x00339F80
extern void local_8033D3E4();                                                                                                    // at 0x00339FC4
extern void func_8033D408(s16, s32, s16, s16);                                                                                   // at 0x00339FE8
extern void func_8033D4C8(s16, s32, s16, s16);                                                                                   // at 0x0033A0A8
extern void func_8033D588(s32);                                                                                                  // at 0x0033A168
extern void func_8033D5CC(s32, s32, s32, s32);                                                                                   // at 0x0033A1AC
extern void func_8033D73C(s32);                                                                                                  // at 0x0033A31C
extern void func_8033D768(s32);                                                                                                  // at 0x0033A348
extern u32 func_8033D7E4(f32);                                                                                                   // at 0x0033A3C4
extern void func_8033D8A0(u8 *, s32);                                                                                            // at 0x0033A480
extern void func_8033D908(s8, u8 *, s8, u8 *);                                                                                   // at 0x0033A4E8
extern void func_8033DB30(s32);                                                                                                  // at 0x0033A710
extern void func_8033DB4C(u32, s8);                                                                                              // at 0x0033A72C
extern void func_8033DCBC(u32, s8);                                                                                              // at 0x0033A89C
extern void func_8033DE4C();                                                                                                     // at 0x0033AA2C
extern void GXInitLightAttn(GXLightObj *, f32, f32, f32, f32, f32, f32);                                                         // at 0x0033AA64
extern void func_8033DEA0(GXLightObj *, u32, f32);                                                                               // at 0x0033AA80
extern void func_8033E020(GXLightObj *, s32, f32, f32);                                                                          // at 0x0033AC00
extern void GXInitLightPos(GXLightObj *, f32, f32, f32);                                                                         // at 0x0033ACD0
extern void GXInitLightDir(GXLightObj *, f32, f32, f32);                                                                         // at 0x0033ACE0
extern void GXInitLightColor(GXLightObj *lobj, GXColor *color);                                                                  // at 0x0033ACFC
void GXLoadLightObjImm(GXLightObj *lobj, u32);                                                                                   // at 0x0033AD24
extern void GXSetChanAmbColor(GXChannelID chan_id, GXColor *color);                                                              // at 0x0033AE6C
extern void GXSetChanMatColor(GXChannelID chan_id, GXColor *color);                                                              // at 0x0033AFD4
extern void GXSetNumChans(u8);                                                                                                   // at 0x0033B13C
extern void GXSetChanCtrl(GXChannelID chan_id, u8, GXColorSrc, GXColorSrc color_src, GXLightID light_id, GXDiffuseFn, GXAttnFn); // at 0x0033B188
extern s32 func_8033E78C(u16, u16, s32, u8, u8);                                                                                 // at 0x0033B36C
extern void func_8033E8E8(u32, s16, s16, s32 *, s32 *, s32 *);                                                                   // at 0x0033B4C8
extern void func_8033E9B0(unk_t, u32, u16, u16, s32, s32, s32, s8);                                                              // at 0x0033B590
extern void func_8033EC24(unk_t, s32);                                                                                           // at 0x0033B804
extern void func_8033EC6C(unk_t, s32, s32, s32, s8, s32, f32, f32, f32);                                                         // at 0x0033B84C
extern s32 func_8033EE00(unk_t);                                                                                                 // at 0x0033B9E0
extern s32 func_8033EE10(unk_t);                                                                                                 // at 0x0033B9F0
extern void func_8033EE20(s32);                                                                                                  // at 0x0033BA00
extern void func_8033EE28(unk_t, unk_t, s32);                                                                                    // at 0x0033BA08
extern void func_8033EFD0(unk_t, s32);                                                                                           // at 0x0033BBB0
extern void func_8033F024(unk_t, u32, s32, s16);                                                                                 // at 0x0033BC04
extern void func_8033F06C(unk_t, s32);                                                                                           // at 0x0033BC4C
extern void func_8033F108(unk_t, s8, u32, s32, u32, s32, s32);                                                                   // at 0x0033BCE8
extern void func_8033F228(s32 *, s32, s32);                                                                                      // at 0x0033BE08
extern void func_8033F270(GXContext *ctx, s32, u8 *);                                                                            // at 0x0033BE50
extern GXTexRegionCallback func_8033F2B8(GXTexRegionCallback);                                                                   // at 0x0033BE98
extern GXTexRegionCallback func_8033F2CC(GXTexRegionCallback);                                                                   // at 0x0033BEAC
extern void func_8033F2E0(s32, s32);                                                                                             // at 0x0033BEC0
extern void func_8033F3AC();                                                                                                     // at 0x0033BF8C
extern void func_8033F518(s32);                                                                                                  // at 0x0033C0F8
extern void func_8033F758(s32, s32, u8, s32, s32, s32, s32, s32);                                                                // at 0x0033C338
void func_8033F7F4(s32 arg0, void *arg1, s32 arg2);                                                                              // at 0x0033C3D4
extern void func_8033F954(s32, s32, s32);                                                                                        // at 0x0033C534
void func_8033FB28(s32 arg0, s32 arg1, s32 arg2);                                                                                // at 0x0033C708
extern void func_8033FC60(s32);                                                                                                  // at 0x0033C840
extern void func_8033FC8C();                                                                                                     // at 0x0033C86C
extern void func_8033FCD4(s32);                                                                                                  // at 0x0033C8B4
extern void func_8033FDA0(GXContext *ctx, s32, u8 *);                                                                            // at 0x0033C980
extern void func_8033FDC4(s32, s32);                                                                                             // at 0x0033C9A4
extern void func_8033FF68(s32, s32, s32, s32, s32);                                                                              // at 0x0033CB48
extern void func_8033FFE8(s32, s32, s32, s32, s32);                                                                              // at 0x0033CBC8
extern void func_8034006C(s32, s32, s32, s32, s32, s32);                                                                         // at 0x0033CC4C
extern void func_8034012C(s32, s32, s32, s32, s32, s32);                                                                         // at 0x0033CD0C
void func_803401EC(s32 arg0, unk_t);                                                                                             // at 0x0033CDCC
void func_80340260(s32 arg0, GXColor *);                                                                                         // at 0x0033CE40
void func_803402D4(s32 arg0, unk_t arg1);                                                                                        // at 0x0033CEB4
extern void func_80340348(s32, s32);                                                                                             // at 0x0033CF28
extern void func_803403B4(s32, s32);                                                                                             // at 0x0033CF94
extern void func_80340420(s32, s32, s32);                                                                                        // at 0x0033D000
extern void func_80340478(s32, s32, s32, s32, s32);                                                                              // at 0x0033D058
extern void func_80340518();                                                                                                     // at 0x0033D0F8
extern void func_8034051C(s32, s32, s32, s32, s32);                                                                              // at 0x0033D0FC
extern void func_8034056C(s32, s32, s32);                                                                                        // at 0x0033D14C
extern void func_803405F0(u32, s32, s32, s32);                                                                                   // at 0x0033D1D0
extern void func_80340790(s8);                                                                                                   // at 0x0033D370
extern void func_80340790(s8);                                                                                                   // at 0x0033D370
extern void func_803407C4(s32, u8 *, f32, f32, f32, f32);                                                                        // at 0x0033D3A4
void func_80340974(s16 *arg0, u16 arg1, unk_t arg2);                                                                             // at 0x0033D554
extern void func_80340B3C(s8, s16, s32 *);                                                                                       // at 0x0033D71C
extern void func_80340C3C(s32, s32, s32, s32);                                                                                   // at 0x0033D81C
extern void func_80340D40(s32);                                                                                                  // at 0x0033D920
extern void func_80340D80(s32);                                                                                                  // at 0x0033D960
extern void func_80340DC0(s8, s32, s32);                                                                                         // at 0x0033D9A0
extern void func_80340E38(s32);                                                                                                  // at 0x0033DA18
extern void GXSetPixelFmt(s32, s32);                                                                                             // at 0x0033DA58
extern void func_80340F88(s32);                                                                                                  // at 0x0033DB68
extern void func_80340FC8(s32, s32);                                                                                             // at 0x0033DBA8
extern void func_8034101C(s32, s8);                                                                                              // at 0x0033DBFC
extern void GXSetFieldMode(s8, s32);                                                                                             // at 0x0033DC34
extern void func_803410D4(f32, f32);                                                                                             // at 0x0033DCB4

void func_803410D8(s32 arg0, s32 arg1);
void GXProject(void *arg0, void *arg1, void *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 arg8, f32 arg9, f32 argA);
void func_803412BC(unk_t arg0, s32 arg1);
void func_80341390(unk_t arg0);

extern void func_80341408(unk_t, s8 *, s8 *);                  // at 0x0033DFE8
extern void func_8034143C(unk_t, s8 *, s8 *);                  // at 0x0033E01C
extern void func_80341470(unk_t, s8 *);                        // at 0x0033E050
extern void func_80341494(unk_t, s32);                         // at 0x0033E074
extern void func_803414D0(unk_t, s32);                         // at 0x0033E0B0
extern void GXSetCurrentMtx(s32);                              // at 0x0033E0F0
extern void func_8034154C(unk_t, u32, s8);                     // at 0x0033E12C
extern void func_803415D0(BOOL, f32, f32, f32, f32, f32, f32); // at 0x0033E1B0
extern void func_803416EC(f32, f32, f32, f32, f32, f32);       // at 0x0033E2CC
extern void func_8034175C(s32, s32, s32, s32);                 // at 0x0033E33C
extern void func_8034180C(s32, s32);                           // at 0x0033E3EC
extern void func_80341850(s32);                                // at 0x0033E430
extern void func_803418FC(u32, u32);                           // at 0x0033E4DC
extern void func_80342194();                                   // at 0x0033ED74
