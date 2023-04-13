#include <placeholder.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSTime.h>

#ifdef MWERKS_GEKKO

asm OSTime OSGetTime(void){ // clang-format off
    mftbu r3
    mftb r4, 0x10c
    mftbu r5
    cmpw r3, r5
    bne OSGetTime
} // clang-format on

#else

OSTime OSGetTime(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm OSTick OSGetTick(void){ // clang-format off
    mftb r3, 0x10c
} // clang-format on

#else

OSTick OSGetTick(void)
{
    NOT_IMPLEMENTED;
}

#endif

extern volatile OSTime OS_SYSTEM_TIME AT_ADDRESS(0x800030D8);

OSTime __OSGetSystemTime(void)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    bool intr = OSDisableInterrupts();
    OSTime time = OSGetTime() + OS_SYSTEM_TIME;
    OSRestoreInterrupts(intr);
    return time;
}

OSTime __OSTimeToSystemTime(s64 time)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    bool intr = OSDisableInterrupts();
    OSTime sysTime = OS_SYSTEM_TIME + time;
    OSRestoreInterrupts(intr);
    return sysTime;
}

#define OS_TIME_MONTH_MAX 12
#define OS_TIME_WEEK_DAY_MAX 7
#define OS_TIME_YEAR_DAY_MAX 365

static s32 YearDays[12] = { 0,   31,  59,  90,  120, 151,
                            181, 212, 243, 273, 304, 334 };
static s32 LeapYearDays[12] = { 0,   31,  60,  91,  121, 152,
                                182, 213, 244, 274, 305, 335 };

static bool IsLeapYear(s32 year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static s32 GetLeapDays(s32 year)
{
    if (year < 1) {
        return 0;
    }
    return (year + 3) / 4 - (year - 1) / 100 + (year - 1) / 400;
}

static void GetDates(s32 days, OSCalendarTime* cal)
{
    s32 year;
    s32 totalDays;
    s32* p_days;
    s32 month;

    cal->wday = (days + 6) % OS_TIME_WEEK_DAY_MAX;

    for (year = days / OS_TIME_YEAR_DAY_MAX;
         days < (totalDays = year * OS_TIME_YEAR_DAY_MAX + GetLeapDays(year));
         year--)
    {
        ;
    }
    days -= totalDays;
    cal->year = year;
    cal->yday = days;

    p_days = IsLeapYear(year) ? LeapYearDays : YearDays;
    month = OS_TIME_MONTH_MAX;

    while (days < p_days[--month]) {
        continue;
    }

    cal->mon = month;
    cal->mday = days - p_days[month] + 1;
}

#ifdef MWERKS_GEKKO

extern unk_t __div2i();
extern unk_t __mod2i();

#pragma push
asm void OSTicksToCalendarTime(u64 ticks, OSCalendarTime* td)
{ // clang-format off
    nofralloc
/* 8034C668 00349248  7C 08 02 A6 */	mflr r0
/* 8034C66C 0034924C  90 01 00 04 */	stw r0, 4(r1)
/* 8034C670 00349250  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8034C674 00349254  BF 21 00 1C */	stmw r25, 0x1c(r1)
/* 8034C678 00349258  7C 7D 1B 78 */	mr r29, r3
/* 8034C67C 0034925C  7C 9E 23 78 */	mr r30, r4
/* 8034C680 00349260  7C BF 2B 78 */	mr r31, r5
/* 8034C684 00349264  3F 60 80 00 */	lis r27, 0x800000F8@ha
/* 8034C688 00349268  80 1B 00 F8 */	lwz r0, 0x800000F8@l(r27)
/* 8034C68C 0034926C  7F A3 EB 78 */	mr r3, r29
/* 8034C690 00349270  7F C4 F3 78 */	mr r4, r30
/* 8034C694 00349274  54 06 F0 BE */	srwi r6, r0, 2
/* 8034C698 00349278  38 A0 00 00 */	li r5, 0
/* 8034C69C 0034927C  4B FD 65 89 */	bl __mod2i
/* 8034C6A0 00349280  7C 7A 1B 78 */	mr r26, r3
/* 8034C6A4 00349284  38 A0 00 00 */	li r5, 0
/* 8034C6A8 00349288  7C 99 23 78 */	mr r25, r4
/* 8034C6AC 0034928C  6F 44 80 00 */	xoris r4, r26, 0x8000
/* 8034C6B0 00349290  6C A3 80 00 */	xoris r3, r5, 0x8000
/* 8034C6B4 00349294  7C 05 C8 10 */	subfc r0, r5, r25
/* 8034C6B8 00349298  7C 63 21 10 */	subfe r3, r3, r4
/* 8034C6BC 0034929C  7C 64 21 10 */	subfe r3, r4, r4
/* 8034C6C0 003492A0  7C 63 00 D0 */	neg r3, r3
/* 8034C6C4 003492A4  2C 03 00 00 */	cmpwi r3, 0
/* 8034C6C8 003492A8  41 82 00 14 */	beq lbl_8034C6DC
/* 8034C6CC 003492AC  80 1B 00 F8 */	lwz r0, 0xf8(r27)
/* 8034C6D0 003492B0  54 00 F0 BE */	srwi r0, r0, 2
/* 8034C6D4 003492B4  7F 39 00 14 */	addc r25, r25, r0
/* 8034C6D8 003492B8  7F 5A 29 14 */	adde r26, r26, r5
lbl_8034C6DC:
/* 8034C6DC 003492BC  38 80 00 08 */	li r4, 8
/* 8034C6E0 003492C0  7C 7A 21 D6 */	mullw r3, r26, r4
/* 8034C6E4 003492C4  7C 19 20 16 */	mulhwu r0, r25, r4
/* 8034C6E8 003492C8  3F 60 80 00 */	lis r27, 0x800000F8@ha
/* 8034C6EC 003492CC  80 DB 00 F8 */	lwz r6, 0x800000F8@l(r27)
/* 8034C6F0 003492D0  3C A0 43 1C */	lis r5, 0x431BDE83@ha
/* 8034C6F4 003492D4  38 A5 DE 83 */	addi r5, r5, 0x431BDE83@l
/* 8034C6F8 003492D8  54 C6 F0 BE */	srwi r6, r6, 2
/* 8034C6FC 003492DC  7C A5 30 16 */	mulhwu r5, r5, r6
/* 8034C700 003492E0  54 A6 8B FE */	srwi r6, r5, 0xf
/* 8034C704 003492E4  3B 80 00 00 */	li r28, 0
/* 8034C708 003492E8  7C 63 02 14 */	add r3, r3, r0
/* 8034C70C 003492EC  7C 19 E1 D6 */	mullw r0, r25, r28
/* 8034C710 003492F0  7C 99 21 D6 */	mullw r4, r25, r4
/* 8034C714 003492F4  7C 63 02 14 */	add r3, r3, r0
/* 8034C718 003492F8  38 A0 00 00 */	li r5, 0
/* 8034C71C 003492FC  4B FD 62 ED */	bl __div2i
/* 8034C720 00349300  38 A0 00 00 */	li r5, 0
/* 8034C724 00349304  38 C0 03 E8 */	li r6, 0x3e8
/* 8034C728 00349308  4B FD 64 FD */	bl __mod2i
/* 8034C72C 0034930C  90 9F 00 24 */	stw r4, 0x24(r31)
/* 8034C730 00349310  3C 60 10 62 */	lis r3, 0x10624DD3@ha
/* 8034C734 00349314  38 A3 4D D3 */	addi r5, r3, 0x10624DD3@l
/* 8034C738 00349318  80 1B 00 F8 */	lwz r0, 0xf8(r27)
/* 8034C73C 0034931C  7F 43 D3 78 */	mr r3, r26
/* 8034C740 00349320  7F 24 CB 78 */	mr r4, r25
/* 8034C744 00349324  54 00 F0 BE */	srwi r0, r0, 2
/* 8034C748 00349328  7C 05 00 16 */	mulhwu r0, r5, r0
/* 8034C74C 0034932C  54 06 D1 BE */	srwi r6, r0, 6
/* 8034C750 00349330  38 A0 00 00 */	li r5, 0
/* 8034C754 00349334  4B FD 62 B5 */	bl __div2i
/* 8034C758 00349338  38 A0 00 00 */	li r5, 0
/* 8034C75C 0034933C  38 C0 03 E8 */	li r6, 0x3e8
/* 8034C760 00349340  4B FD 64 C5 */	bl __mod2i
/* 8034C764 00349344  90 9F 00 20 */	stw r4, 0x20(r31)
/* 8034C768 00349348  7F D9 F0 10 */	subfc r30, r25, r30
/* 8034C76C 0034934C  7F BA E9 10 */	subfe r29, r26, r29
/* 8034C770 00349350  80 1B 00 F8 */	lwz r0, 0xf8(r27)
/* 8034C774 00349354  3C A0 00 01 */	lis r5, 0x00015180@ha
/* 8034C778 00349358  3B 25 51 80 */	addi r25, r5, 0x00015180@l
/* 8034C77C 0034935C  7F A3 EB 78 */	mr r3, r29
/* 8034C780 00349360  54 06 F0 BE */	srwi r6, r0, 2
/* 8034C784 00349364  7F C4 F3 78 */	mr r4, r30
/* 8034C788 00349368  38 A0 00 00 */	li r5, 0
/* 8034C78C 0034936C  4B FD 62 7D */	bl __div2i
/* 8034C790 00349370  7F 26 CB 78 */	mr r6, r25
/* 8034C794 00349374  38 A0 00 00 */	li r5, 0
/* 8034C798 00349378  4B FD 62 71 */	bl __div2i
/* 8034C79C 0034937C  3C A0 00 0B */	lis r5, 0x000B2575@ha
/* 8034C7A0 00349380  80 1B 00 F8 */	lwz r0, 0xf8(r27)
/* 8034C7A4 00349384  38 A5 25 75 */	addi r5, r5, 0x000B2575@l
/* 8034C7A8 00349388  7F 44 28 14 */	addc r26, r4, r5
/* 8034C7AC 0034938C  54 06 F0 BE */	srwi r6, r0, 2
/* 8034C7B0 00349390  7C 03 E1 14 */	adde r0, r3, r28
/* 8034C7B4 00349394  7F A3 EB 78 */	mr r3, r29
/* 8034C7B8 00349398  7F C4 F3 78 */	mr r4, r30
/* 8034C7BC 0034939C  38 A0 00 00 */	li r5, 0
/* 8034C7C0 003493A0  4B FD 62 49 */	bl __div2i
/* 8034C7C4 003493A4  7F 26 CB 78 */	mr r6, r25
/* 8034C7C8 003493A8  38 A0 00 00 */	li r5, 0
/* 8034C7CC 003493AC  4B FD 64 59 */	bl __mod2i
/* 8034C7D0 003493B0  7C 9B 23 78 */	mr r27, r4
/* 8034C7D4 003493B4  2C 1B 00 00 */	cmpwi r27, 0
/* 8034C7D8 003493B8  40 80 00 10 */	bge lbl_8034C7E8
/* 8034C7DC 003493BC  3F 7B 00 01 */	addis r27, r27, 1
/* 8034C7E0 003493C0  3B 5A FF FF */	addi r26, r26, -1
/* 8034C7E4 003493C4  3B 7B 51 80 */	addi r27, r27, 0x5180
lbl_8034C7E8:
/* 8034C7E8 003493C8  7F 43 D3 78 */	mr r3, r26
/* 8034C7EC 003493CC  7F E4 FB 78 */	mr r4, r31
/* 8034C7F0 003493D0  4B FF FC DD */	bl GetDates
/* 8034C7F4 003493D4  3C 60 88 89 */	lis r3, 0x88888889@ha
/* 8034C7F8 003493D8  38 A3 88 89 */	addi r5, r3, 0x88888889@l
/* 8034C7FC 003493DC  7C 05 D8 96 */	mulhw r0, r5, r27
/* 8034C800 003493E0  7C 80 DA 14 */	add r4, r0, r27
/* 8034C804 003493E4  7C 80 2E 70 */	srawi r0, r4, 5
/* 8034C808 003493E8  54 03 0F FE */	srwi r3, r0, 0x1f
/* 8034C80C 003493EC  7C E0 1A 14 */	add r7, r0, r3
/* 8034C810 003493F0  7C 05 38 96 */	mulhw r0, r5, r7
/* 8034C814 003493F4  7C 00 3A 14 */	add r0, r0, r7
/* 8034C818 003493F8  7C 05 2E 70 */	srawi r5, r0, 5
/* 8034C81C 003493FC  7C 00 2E 70 */	srawi r0, r0, 5
/* 8034C820 00349400  54 03 0F FE */	srwi r3, r0, 0x1f
/* 8034C824 00349404  7C 60 1A 14 */	add r3, r0, r3
/* 8034C828 00349408  7C 80 2E 70 */	srawi r0, r4, 5
/* 8034C82C 0034940C  54 A6 0F FE */	srwi r6, r5, 0x1f
/* 8034C830 00349410  1C 83 00 3C */	mulli r4, r3, 0x3c
/* 8034C834 00349414  54 03 0F FE */	srwi r3, r0, 0x1f
/* 8034C838 00349418  7C A5 32 14 */	add r5, r5, r6
/* 8034C83C 0034941C  7C 00 1A 14 */	add r0, r0, r3
/* 8034C840 00349420  90 BF 00 08 */	stw r5, 8(r31)
/* 8034C844 00349424  1C 00 00 3C */	mulli r0, r0, 0x3c
/* 8034C848 00349428  7C 64 38 50 */	subf r3, r4, r7
/* 8034C84C 0034942C  90 7F 00 04 */	stw r3, 4(r31)
/* 8034C850 00349430  7C 00 D8 50 */	subf r0, r0, r27
/* 8034C854 00349434  90 1F 00 00 */	stw r0, 0(r31)
/* 8034C858 00349438  BB 21 00 1C */	lmw r25, 0x1c(r1)
/* 8034C85C 0034943C  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8034C860 00349440  38 21 00 38 */	addi r1, r1, 0x38
/* 8034C864 00349444  7C 08 03 A6 */	mtlr r0
/* 8034C868 00349448  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void OSTicksToCalendarTime(u64 ticks, OSCalendarTime* td)
{
    NOT_IMPLEMENTED;
}

#endif
