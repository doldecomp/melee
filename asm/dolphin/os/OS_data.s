.include "macros.inc"

.section .data
    .balign 8
.global DriveInfo
DriveInfo:
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
    .4byte 0x00000100
    .4byte 0x00000200
    .4byte 0x00000300
    .4byte 0x00000400
    .4byte 0x00000500
    .4byte 0x00000600
    .4byte 0x00000700
    .4byte 0x00000800
    .4byte 0x00000900
    .4byte 0x00000C00
    .4byte 0x00000D00
    .4byte 0x00000F00
    .4byte 0x00001300
    .4byte 0x00001400
    .4byte 0x00001700
    .4byte 0x496E7374
    .4byte 0x616C6C69
    .4byte 0x6E67204F
    .4byte 0x53444249
    .4byte 0x6E746567
    .4byte 0x7261746F
    .4byte 0x720A0000
    .4byte 0x3E3E3E20
    .4byte 0x4F53494E
    .4byte 0x49543A20
    .4byte 0x65786365
    .4byte 0x7074696F
    .4byte 0x6E202564
    .4byte 0x20636F6D
    .4byte 0x6D616E64
    .4byte 0x65657265
    .4byte 0x64206279
    .4byte 0x2054524B
    .4byte 0x0A000000
    .4byte 0x3E3E3E20
    .4byte 0x4F53494E
    .4byte 0x49543A20
    .4byte 0x65786365
    .4byte 0x7074696F
    .4byte 0x6E202564
    .4byte 0x20766563
    .4byte 0x746F7265
    .4byte 0x6420746F
    .4byte 0x20646562
    .4byte 0x75676765
    .4byte 0x720A0000
    .4byte 0x45786365
    .4byte 0x7074696F
    .4byte 0x6E732069
    .4byte 0x6E697469
    .4byte 0x616C697A
    .4byte 0x65642E2E
    .4byte 0x2E0A0000
    .4byte NULL


.section .sbss
    .balign 8

.global BootInfo
BootInfo:
    .skip 0x4
.global BI2DebugFlag
BI2DebugFlag:
    .skip 0x4
.global BI2DebugFlagHolder
BI2DebugFlagHolder:
    .skip 0x4
.global AreWeInitialized
AreWeInitialized:
    .skip 0x4
.global OSExceptionTable
OSExceptionTable:
    .skip 0x8
.global __OSStartTime
__OSStartTime:
    .skip 0x8
