#!/usr/bin/env bash
set -oeu pipefail

file="$1"

replace() {
    sed -i "s#$1#$2#g" "$file"
}

replace '(1 << 0)' 'FtStateChange_PreserveFastFall'
replace '(1 << 1)' 'FtStateChange_PreserveGfx'
replace '(1 << 2)' 'FtStateChange_PreserveColAnimHitStatus'
replace '(1 << 3)' 'FtStateChange_SkipUpdateHit'
replace '(1 << 4)' 'FtStateChange_SkipUpdateModel'
replace '(1 << 5)' 'FtStateChange_SkipUpdateAnimVel'
replace '(1 << 6)' 'FtStateChange_Unk_6'
replace '(1 << 7)' 'FtStateChange_SkipUpdateMatAnim'
replace '(1 << 8)' 'FtStateChange_SkipUpdateThrowException'
replace '(1 << 9)' 'FtStateChange_PreserveSfx'
replace '(1 << 10)' 'FtStateChange_SkipUpdateParasol'
replace '(1 << 11)' 'FtStateChange_SkipUpdateRumble'
replace '(1 << 12)' 'FtStateChange_SkipUpdateColAnim'
replace '(1 << 13)' 'FtStateChange_PreserveAccessory'
replace '(1 << 14)' 'FtStateChange_UpdateCmd'
replace '(1 << 15)' 'FtStateChange_SkipUpdateNametagVis'
replace '(1 << 16)' 'FtStateChange_PreserveColaNimPartHitStatus'
replace '(1 << 17)' 'FtStateChange_PreserveSwordTrail'
replace '(1 << 18)' 'FtStateChange_SkipUpdateItemVis'
replace '(1 << 19)' 'FtStateChange_Unk_19'
replace '(1 << 20)' 'FtStateChange_Unk_UpdatePhys'
replace '(1 << 21)' 'FtStateChange_FreezeState'
replace '(1 << 22)' 'FtStateChange_SkipUpdateModelPartVis'
replace '(1 << 23)' 'FtStateChange_SkipUpdateMetalB'
replace '(1 << 24)' 'FtStateChange_Unk_24'
replace '(1 << 25)' 'FtStateChange_SkipUpdateAttackCount'
replace '(1 << 26)' 'FtStateChange_SkipUpdateModelFlag'
replace '(1 << 27)' 'FtStateChange_Unk_27'
replace '(1 << 28)' 'FtStateChange_SkipUpdateHitStunFlag'
replace '(1 << 29)' 'FtStateChange_SkipUpdateAnim'
replace '(1 << 30)' 'FtStateChange_Unk_30'
replace '(1 << 31)' 'FtStateChange_Unk_31'
