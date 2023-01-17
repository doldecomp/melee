#include <dolphin/dvd/dvd.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSReset.h>
#include <MetroTRK/intrinsics.h>
#include <placeholder.h>

static unk_t Header[0x20 / sizeof(unk_t)];
static unk_t SaveStart;
static unk_t SaveEnd;
static bool Prepared;

#ifdef MWERKS_GEKKO

void Run(register Event callback)
{
    OSDisableInterrupts();
    ICFlashInvalidate();
    __sync();
    __isync();
    asm {
        mtlr callback
        blr
    }
}

#else

void Run(Event arg0)
{
    NOT_IMPLEMENTED;
}

#endif

static void Callback(void)
{
    Prepared = true;
}

#ifdef MWERKS_GEKKO

#pragma push
asm void __OSReboot(u32 resetCode, bool forceMenu)
{ // clang-format off
    nofralloc
/* 80348144 00344D24  7C 08 02 A6 */	mflr r0
/* 80348148 00344D28  90 01 00 04 */	stw r0, 4(r1)
/* 8034814C 00344D2C  94 21 FC B8 */	stwu r1, -0x348(r1)
/* 80348150 00344D30  93 E1 03 44 */	stw r31, 0x344(r1)
/* 80348154 00344D34  93 C1 03 40 */	stw r30, 0x340(r1)
/* 80348158 00344D38  93 A1 03 3C */	stw r29, 0x33c(r1)
/* 8034815C 00344D3C  7C 7D 1B 78 */	mr r29, r3
/* 80348160 00344D40  3C 60 80 4A */	lis r3, Header@ha
/* 80348164 00344D44  3B C3 7D 40 */	addi r30, r3, Header@l
/* 80348168 00344D48  4B FF F1 FD */	bl OSDisableInterrupts
/* 8034816C 00344D4C  80 AD BC F0 */	lwz r5, SaveStart(r13)
/* 80348170 00344D50  3F E0 81 80 */	lis r31, 0x817FFFFC@ha
/* 80348174 00344D54  38 60 00 00 */	li r3, 0
/* 80348178 00344D58  80 0D BC F4 */	lwz r0, SaveEnd(r13)
/* 8034817C 00344D5C  3C 80 81 30 */	lis r4, 0x812FDFF0@ha
/* 80348180 00344D60  38 E0 00 01 */	li r7, 1
/* 80348184 00344D64  93 BF FF FC */	stw r29, 0x817FFFFC@l(r31)
/* 80348188 00344D68  3C C0 80 00 */	lis r6, 0x800030E2@ha
/* 8034818C 00344D6C  90 7F FF F8 */	stw r3, -8(r31)
/* 80348190 00344D70  38 61 00 70 */	addi r3, r1, 0x70
/* 80348194 00344D74  98 E6 30 E2 */	stb r7, 0x800030E2@l(r6)
/* 80348198 00344D78  90 A4 DF F0 */	stw r5, 0x812FDFF0@l(r4)
/* 8034819C 00344D7C  90 04 DF EC */	stw r0, -0x2014(r4)
/* 803481A0 00344D80  4B FF D0 B5 */	bl OSClearContext
/* 803481A4 00344D84  38 61 00 70 */	addi r3, r1, 0x70
/* 803481A8 00344D88  4B FF CE E5 */	bl OSSetCurrentContext
/* 803481AC 00344D8C  4B FE FC 3D */	bl DVDInit
/* 803481B0 00344D90  38 60 00 01 */	li r3, 1
/* 803481B4 00344D94  4B FF 1A 45 */	bl DVDSetAutoInvalidation
/* 803481B8 00344D98  3C 60 80 35 */	lis r3, Callback@ha
/* 803481BC 00344D9C  38 63 81 38 */	addi r3, r3, Callback@l
/* 803481C0 00344DA0  4B FF 1E 75 */	bl __DVDPrepareResetAsync
/* 803481C4 00344DA4  4B FF 1D 8D */	bl DVDCheckDisk
/* 803481C8 00344DA8  2C 03 00 00 */	cmpwi r3, 0
/* 803481CC 00344DAC  40 82 00 0C */	bne lbl_803481D8
/* 803481D0 00344DB0  80 7F FF FC */	lwz r3, -4(r31)
/* 803481D4 00344DB4  48 00 02 31 */	bl __OSDoHotReset
lbl_803481D8:
/* 803481D8 00344DB8  38 60 FF E0 */	li r3, -32
/* 803481DC 00344DBC  4B FF F5 51 */	bl __OSMaskInterrupts
/* 803481E0 00344DC0  38 60 04 00 */	li r3, 0x400
/* 803481E4 00344DC4  4B FF F5 D1 */	bl __OSUnmaskInterrupts
/* 803481E8 00344DC8  4B FF F1 91 */	bl OSEnableInterrupts
/* 803481EC 00344DCC  48 00 00 04 */	b lbl_803481F0
lbl_803481F0:
/* 803481F0 00344DD0  48 00 00 04 */	b lbl_803481F4
lbl_803481F4:
/* 803481F4 00344DD4  80 0D BC F8 */	lwz r0, Prepared(r13)
/* 803481F8 00344DD8  2C 00 00 00 */	cmpwi r0, 0
/* 803481FC 00344DDC  41 82 FF F8 */	beq lbl_803481F4
/* 80348200 00344DE0  7F C4 F3 78 */	mr r4, r30
/* 80348204 00344DE4  38 61 00 40 */	addi r3, r1, 0x40
/* 80348208 00344DE8  38 A0 00 20 */	li r5, 0x20
/* 8034820C 00344DEC  38 C0 24 40 */	li r6, 0x2440
/* 80348210 00344DF0  38 E0 00 00 */	li r7, 0
/* 80348214 00344DF4  4B FF 17 51 */	bl DVDReadAbsAsyncForBS
/* 80348218 00344DF8  3F E0 81 80 */	lis r31, 0x8180
/* 8034821C 00344DFC  48 00 00 04 */	b lbl_80348220
lbl_80348220:
/* 80348220 00344E00  48 00 00 04 */	b lbl_80348224
lbl_80348224:
/* 80348224 00344E04  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 80348228 00344E08  2C 00 00 01 */	cmpwi r0, 1
/* 8034822C 00344E0C  41 82 FF F8 */	beq lbl_80348224
/* 80348230 00344E10  40 80 00 14 */	bge lbl_80348244
/* 80348234 00344E14  2C 00 FF FF */	cmpwi r0, -1
/* 80348238 00344E18  41 82 00 18 */	beq lbl_80348250
/* 8034823C 00344E1C  40 80 00 20 */	bge lbl_8034825C
/* 80348240 00344E20  4B FF FF E4 */	b lbl_80348224
lbl_80348244:
/* 80348244 00344E24  2C 00 00 0C */	cmpwi r0, 0xc
/* 80348248 00344E28  40 80 FF DC */	bge lbl_80348224
/* 8034824C 00344E2C  48 00 00 04 */	b lbl_80348250
lbl_80348250:
/* 80348250 00344E30  80 7F FF FC */	lwz r3, -4(r31)
/* 80348254 00344E34  48 00 01 B1 */	bl __OSDoHotReset
/* 80348258 00344E38  4B FF FF CC */	b lbl_80348224
lbl_8034825C:
/* 8034825C 00344E3C  80 7E 00 18 */	lwz r3, 0x18(r30)
/* 80348260 00344E40  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 80348264 00344E44  38 03 00 1F */	addi r0, r3, 0x1f
/* 80348268 00344E48  38 84 00 20 */	addi r4, r4, 0x20
/* 8034826C 00344E4C  54 1E 00 34 */	rlwinm r30, r0, 0, 0, 0x1a
/* 80348270 00344E50  48 00 00 04 */	b lbl_80348274
lbl_80348274:
/* 80348274 00344E54  48 00 00 04 */	b lbl_80348278
lbl_80348278:
/* 80348278 00344E58  80 0D BC F8 */	lwz r0, Prepared(r13)
/* 8034827C 00344E5C  2C 00 00 00 */	cmpwi r0, 0
/* 80348280 00344E60  41 82 FF F8 */	beq lbl_80348278
/* 80348284 00344E64  7F C5 F3 78 */	mr r5, r30
/* 80348288 00344E68  38 61 00 10 */	addi r3, r1, 0x10
/* 8034828C 00344E6C  38 C4 24 40 */	addi r6, r4, 0x2440
/* 80348290 00344E70  3C 80 81 30 */	lis r4, 0x8130
/* 80348294 00344E74  38 E0 00 00 */	li r7, 0
/* 80348298 00344E78  4B FF 16 CD */	bl DVDReadAbsAsyncForBS
/* 8034829C 00344E7C  3F E0 81 80 */	lis r31, 0x8180
/* 803482A0 00344E80  48 00 00 04 */	b lbl_803482A4
lbl_803482A4:
/* 803482A4 00344E84  48 00 00 04 */	b lbl_803482A8
lbl_803482A8:
/* 803482A8 00344E88  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 803482AC 00344E8C  2C 00 00 01 */	cmpwi r0, 1
/* 803482B0 00344E90  41 82 FF F8 */	beq lbl_803482A8
/* 803482B4 00344E94  40 80 00 14 */	bge lbl_803482C8
/* 803482B8 00344E98  2C 00 FF FF */	cmpwi r0, -1
/* 803482BC 00344E9C  41 82 00 18 */	beq lbl_803482D4
/* 803482C0 00344EA0  40 80 00 20 */	bge lbl_803482E0
/* 803482C4 00344EA4  4B FF FF E4 */	b lbl_803482A8
lbl_803482C8:
/* 803482C8 00344EA8  2C 00 00 0C */	cmpwi r0, 0xc
/* 803482CC 00344EAC  40 80 FF DC */	bge lbl_803482A8
/* 803482D0 00344EB0  48 00 00 04 */	b lbl_803482D4
lbl_803482D4:
/* 803482D4 00344EB4  80 7F FF FC */	lwz r3, -4(r31)
/* 803482D8 00344EB8  48 00 01 2D */	bl __OSDoHotReset
/* 803482DC 00344EBC  4B FF FF CC */	b lbl_803482A8
lbl_803482E0:
/* 803482E0 00344EC0  3C 60 81 30 */	lis r3, 0x8130
/* 803482E4 00344EC4  7F C4 F3 78 */	mr r4, r30
/* 803482E8 00344EC8  4B FF C5 ED */	bl ICInvalidateRange
/* 803482EC 00344ECC  3C 60 81 30 */	lis r3, 0x8130
/* 803482F0 00344ED0  4B FF FE 09 */	bl Run
/* 803482F4 00344ED4  80 01 03 4C */	lwz r0, 0x34c(r1)
/* 803482F8 00344ED8  83 E1 03 44 */	lwz r31, 0x344(r1)
/* 803482FC 00344EDC  83 C1 03 40 */	lwz r30, 0x340(r1)
/* 80348300 00344EE0  7C 08 03 A6 */	mtlr r0
/* 80348304 00344EE4  83 A1 03 3C */	lwz r29, 0x33c(r1)
/* 80348308 00344EE8  38 21 03 48 */	addi r1, r1, 0x348
/* 8034830C 00344EEC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void __OSReboot(u32 resetCode, bool forceMenu)
{
    NOT_IMPLEMENTED;
}

#endif
