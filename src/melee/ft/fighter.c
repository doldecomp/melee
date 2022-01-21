#include "fighter.h"

// https://decomp.me/scratch/WtgBX

s32 debug_level_r13_min_0x6C98 = 0; // Probably always zero, meaning that debug tests are disabled. For example this disables a "position has NaN component" test at the end of PlayerThink_Physics

ftCommonData* p_stc_ftcommon; // = (R13 + -0x514C);

// 8006B82C
void fighter_procUpdate(HSD_GObj* pPlayerEntityStruct, s32 dummy) {
    //@1c
    Fighter* pCharData = (Fighter*) pPlayerEntityStruct->user_data;
    //float atkShieldKB_len; // 0x1c
    //float kb_vel_len; // 0x20
    Vec3 windOffset; // 0x4c
    //@20
    if (pCharData->x221f_4_sleep) // if pCharData->byte_at_0x221F & 0b10000
		return;
    
    //@30
    if (!pCharData->x2219_6_freeze)
    {
        Vec2* p_kb_vel;
        Vec2* pAtkShieldKB;
        float kb_vel_x, atkShieldKB_X;
        Vec3 selfVel; // 0x40

        //@3c
        if (pCharData->x2064_ledge_cooldown != 0)
			pCharData->x2064_ledge_cooldown -= 1;
        if (pCharData->x2108 != 0)
			pCharData->x2108 -= 1;
        
        //@64
        FtChkDevice_DecrementImmunity_800C0A98(pPlayerEntityStruct);

        //@6c
		if (pCharData->x21a4_callback_Phys != 0)
			pCharData->x21a4_callback_Phys(pPlayerEntityStruct); // AS_Physics_Func callback @0x21A4
        //@84
        p_kb_vel = (Vec2*)&pCharData->x8c_kb_vel;
		if ((kb_vel_x = p_kb_vel->x) != 0 || p_kb_vel->y != 0)
        {
            //@a4
			if (pCharData->xe0_airborne == 1) // # 0=grounded, 1=airborne.
            {
                //@b0
				float kb_vel_x = p_kb_vel->x;
				float kb_vel_y = p_kb_vel->y;
				// I was not able to trigger this case in normal gameplay yet. spreadsheet comment: facing angle? hi-pitch, lo-pitch, noCliffCatch
				if ((pCharData->x2228_unk_flags >> 5) & 1) // equivalent to x2228_unk_flags & 0b0010_0000
                {
                	p_kb_vel->x = reduceMagnitude_0x8007CD6C(p_kb_vel->x, getVec0x2D4_X_assertPlayerIndex_0x8007CDA4(pCharData));
					p_kb_vel->y = reduceMagnitude_0x8007CD6C(p_kb_vel->y, getVec0x2D4_Y_assertPlayerIndex_0x8007cdf8(pCharData));
                }
                else //@f8
                {
                    
                    float kb_angle = atan2_80022C30(kb_vel_y, kb_vel_x);
                    //@104
					float kb_vel_len = sqrtf(kb_vel_x * kb_vel_x + kb_vel_y * kb_vel_y);
					
					//@168 decrement knockback velocity magnitude
                    if (kb_vel_len < p_stc_ftcommon->kb_frameDecay) // kb_frameDecay offset is 0x204, value always 0.051?
                    {
						p_kb_vel->y = 0; // 0.0f@toc-0x778C
                        p_kb_vel->x = 0;
                    }
					else
                    {
                        // What we want to achieve is this:
                        // 	*p_kb_vel *= (kb_vel_len - kb_frameDecay)/kb_vel_len
                        // But this is implemented very inefficiently like this:
                        // (Also this doesn't work properly for 180° angles)
						p_kb_vel->x -= p_stc_ftcommon->kb_frameDecay * cos_80326240(kb_angle);//@188
                        p_kb_vel->y -= p_stc_ftcommon->kb_frameDecay * sin_803263d4(kb_angle);//@1a8
                    }
                }
                //@1c0
				pCharData->xf0_ground_kb_vel = 0; // 0.0f@toc-0x778C
            }
			else
            {
                // @1cc
                //float effectiveFriction;
                Vec3* pNormal = &pCharData->coll_data.ground_normal; // ground_normal offset inside pCharData is 0x844, surface normal points out of the surface. 
                struct attr* pAttr;
                // This is probably triggered when transitioning from the air to the ground, for example with ASDI down after getting hit.
				if (pCharData->xf0_ground_kb_vel == 0)
					pCharData->xf0_ground_kb_vel = kb_vel_x;
                //@1e4
                pAttr = &pCharData->attr; // attr has offset 0x110
                reduceGroundKnockbackVel_0x8007CCA0(pCharData,
                    /*effective friction - ground multiplier is usually 1. last factor was 1 when I looked*/
                    Stage_GetGroundFrictionMultiplier_0x80084A40(pCharData) * pAttr->x128_ground_friction * p_stc_ftcommon->x200);
				// @210 set knockback velocity to ground_kb_vel * surfaceTangent
                p_kb_vel->x =  pNormal->y * pCharData->xf0_ground_kb_vel;
                // @220
                p_kb_vel->y = -pNormal->x * pCharData->xf0_ground_kb_vel;
            }
        }
        //@230 Now handle the attacker's shield knockback in a similar way
        pAtkShieldKB = (Vec2*)&pCharData->x98_atk_shield_kb;
        if ((atkShieldKB_X = pAtkShieldKB->x) != 0 || pAtkShieldKB->y != 0)
        {
            //@250
            if (pCharData->xe0_airborne == 1)
            {
                //@25c
                float kb_x = pAtkShieldKB->x;
                float kb_y = pAtkShieldKB->y;
                float atkShieldKBAngle = atan2_80022C30(kb_y, kb_x);
                //@270
                float atkShieldKB_len = sqrtf(kb_x*kb_x + kb_y*kb_y);
                //@2d4
                if (atkShieldKB_len < p_stc_ftcommon->x3e8_shield_kb_frameDecay)
                {
                    //@2e4
                    // BUG IN THE MELEE CODE THAT CAUSES THE INVISIBLE CEILING GLITCH
                    // The next line should be 'pAtkShieldKB->y = 0', but instead it is:
                    p_kb_vel->y = 0;
                    pAtkShieldKB->x = 0;
                }
                else
                {
                    //@2f4
                    // again, the better implementation would be:
                    // *pAtkShieldKB *= (atkShieldKB_len - p_stc_ftcommon->x3e8_shield_kb_frameDecay)/atkShieldKB_len
                    //float atkShieldKBAngle = atan2_80022C30(pAtkShieldKB->y, pAtkShieldKB->x);
                    pAtkShieldKB->x -= p_stc_ftcommon->x3e8_shield_kb_frameDecay * cos_80326240(atkShieldKBAngle);
                    pAtkShieldKB->y -= p_stc_ftcommon->x3e8_shield_kb_frameDecay * sin_803263d4(atkShieldKBAngle);
                }
                pCharData->xf4_ground_attacker_shield_kb_vel = 0; // 0 = TOC.float@-0x778C
            }
            else
            {
                //@338
                float effectiveFriction;
                Vec3* pNormal = &pCharData->coll_data.ground_normal; // ground_normal offset inside pCharData is 0x844, surface normal points out of the surface. 
                struct attr* pAttr;
                //@344
                if (pCharData->xf4_ground_attacker_shield_kb_vel == 0)
                    pCharData->xf4_ground_attacker_shield_kb_vel = atkShieldKB_X;
                //@350
                pAttr = &pCharData->attr; // attr has offset 0x110
                //@374
                reduceGroundShieldKnockbackVel_0x8007CE4C(pCharData,
                    /* effectiveFriction - the last constant variable differs from the one for the knockback friction above*/
                    Stage_GetGroundFrictionMultiplier_0x80084A40(pCharData) * pAttr->x128_ground_friction * p_stc_ftcommon->x3ec);
                //@378
                pAtkShieldKB->x =  pNormal->y * pCharData->xf4_ground_attacker_shield_kb_vel;
                pAtkShieldKB->y = -pNormal->x * pCharData->xf4_ground_attacker_shield_kb_vel;
            }
        }

        //@39c update ground velocity
		pCharData->xec_ground_vel += pCharData->xe4_ground_accel_1 + pCharData->xe8_ground_accel_2;
        //@3c0
		pCharData->xe8_ground_accel_2 = 0;
        pCharData->xe4_ground_accel_1 = 0;

        //@3cc self_vel += anim_vel
		PSVECAdd_0x80342D54(&pCharData->x80_self_vel, &pCharData->x74_anim_vel, &pCharData->x80_self_vel);
        //@3d0
		pCharData->x74_anim_vel.z = 0;
        pCharData->x74_anim_vel.y = 0;
        pCharData->x74_anim_vel.x = 0;
		
		//@3e0 copy selfVel into a stack storage variable
		selfVel = pCharData->x80_self_vel;
		
		// TODO: these double_lower_32bit variables are probably integer counters that get decremented each frame,
        // but I was not able to trigger the following condition.
		//@3f8 The double value construction then is only used as an interpolation tool between selfVel and some UnkVel2.
		if (pCharData->x1948 != 0)
        {
            //@404
            // The compiler casts an u32 integer 'val' to a double type using
            // double v = *(double*)&(0x43300000_00000000 | val ^ 0x80000000) - *(double*)&43300000_80000000
            // which is all that happens in the lengthy assembly generated by this
			float C = 1.0f - (float)pCharData->x194C / (float)pCharData->x1948;
			
            selfVel.x = C * (pCharData->x80_self_vel.x - pCharData->xa4_unk_vel.x) + pCharData->xa4_unk_vel.x;
            //@458
            selfVel.y = C * (pCharData->x80_self_vel.y - pCharData->xa4_unk_vel.y) + pCharData->xa4_unk_vel.y;
            //@46c
            pCharData->x194C--;
			if (pCharData->x194C == 0)
				pCharData->x1948 = 0;
        }
		//@48c add some horizontal+depth offset to the position? Why is there no vertical component?
		pCharData->xb0_position.x += pCharData->xf8_player_nudge_vel.x;
		pCharData->xb0_position.z += pCharData->xf8_player_nudge_vel.y;
        //@4ac
        if (pCharData->x2222_7 && !pCharData->x2222_8)
        {
            s32 bit;
            //@4c0
            // pCharData->xd4_unk_vel += selfVel
			PSVECAdd_0x80342D54(&pCharData->xd4_unk_vel, &selfVel, &pCharData->xd4_unk_vel);
			//@4d0
            pCharData->xd4_unk_vel.x += p_kb_vel->x;
            pCharData->xd4_unk_vel.y += p_kb_vel->y;
            //@4f0
            if (pCharData->x2210_3_throw)
            {
			    pCharData->x2210_3_throw = 0;
                bit = 1;
            }
            else
                bit = 0;
			//@514
			if (bit || func_80070FD0(pCharData) != 0 || pCharData->x594_anim_curr_flags_1 & 1)
            {
                //@538
                // pCharData->xb0_position += pCharData->xd4_unk_vel
				PSVECAdd_0x80342D54(&pCharData->xb0_position, &pCharData->xd4_unk_vel, &pCharData->xb0_position);
				// TODO: we set this velocity to 0 after applying it -> Is this SDI or ASDI?
                pCharData->xd4_unk_vel.z = 0;
                pCharData->xd4_unk_vel.y = 0;
                pCharData->xd4_unk_vel.x = 0;
            }
			//@558 pCharData->xb0_position += *pAtkShieldKB
            PSVECAdd_0x80342D54(&pCharData->xb0_position, (Vec3*)pAtkShieldKB, &pCharData->xb0_position);
        }
		else
        {
            //pCharData@r31.position@0xb0.xyz += selfVel + pAtkShieldKB
			PSVECAdd_0x80342D54(&pCharData->xb0_position, &selfVel, &pCharData->xb0_position);
			pCharData->xb0_position.x += p_kb_vel->x;
            pCharData->xb0_position.y += p_kb_vel->y;
            PSVECAdd_0x80342D54(&pCharData->xb0_position, (Vec3*)pAtkShieldKB, &pCharData->xb0_position);
        }
		//@5ac accumulate wind hazards into the windOffset vector
		Stage_CheckForWindHazards_0x8007B924(pPlayerEntityStruct, /*result vec3*/&windOffset);
    }
    else
    {
        //@5bc
        windOffset.z = 0;
        windOffset.y = 0;
        windOffset.x = 0;
    }
    //@5cc
    DataOffset_ComboCount_TopNAttackerModify_0x80076528(pPlayerEntityStruct);

    //@5d4
	if (pCharData->x21d0_callback_EveryHitlag != 0)
		pCharData->x21d0_callback_EveryHitlag(pPlayerEntityStruct); // void (*EveryHitlag_x21D0)(HSD_GObj *fighter)
    
    //@5ec
	if (pCharData->xe0_airborne == 0)
    {
        //@5f8
        s32 dummy2;
		Vec3 difference; // 0x24
		// I think this function always returns r3=1, but it contains two __assert functions. But I guess these just stop or reset the game.
		// result is written to where r5 points to, which is 'difference' in this case
		if (Collision_GetPositionDifference_0x800567C0(pCharData->coll_data.x83c_ground_index/*groundID field not documented*/, /*Vec3*/&pCharData->xb0_position, &difference))
			//@610 pCharData->position += difference
			PSVECAdd_0x80342D54(&pCharData->xb0_position, &difference, &pCharData->xb0_position);
    }
	
	//@620
	pCharData->xb0_position.x += windOffset.x;
    pCharData->xb0_position.y += windOffset.y;
    pCharData->xb0_position.z += windOffset.z;

    //@654 TODO: do the bitflag tests here tell us if the player is dead?
	Player_CheckForDeath_0x800D3158(pPlayerEntityStruct);
    //@658
	if (pCharData->x2225_1)
    {
		//@664 if position.y crossed (0.25*stage.blastBottom+0.75*stage.cameraBottom) + stage.crowdReactStart from below...
		if (pCharData->xbc_pos_prev.y <= StageInfo_CrowdGaspHeight_0x80224BC4() &&
		    pCharData->xb0_position.y >  StageInfo_CrowdGaspHeight_0x80224BC4())
			pCharData->x2225_1 = 0;
    }
	else
    {
        //@69c
		if ((pCharData->x222a_2 == 0) && (/*!x2228_6*/((pCharData->x2228_unk_flags >> 2) & 1) == 0))
        {
			//@6b4 if position.y crossed 0.5*(stage.blastBottom+stage.cameraBottom) + stage.crowdReactStart from above...
			if (pCharData->xbc_pos_prev.y >= StageInfo_OffscreenBottomLoad_0x80224B98() &&
			    pCharData->xb0_position.y <  StageInfo_OffscreenBottomLoad_0x80224B98())
            {
				//@6e8 plays this sound you always hear when you get close to the bottom blast zone
				SFX_PlayCharacterSFX_0x80088148(pCharData, 96, 127, 64);
                //@6ec
				pCharData->x2225_1 = 1;
            }
        }
    }
	//@6fc
	if (pCharData->x18A4_knockbackMagnitude  && // 0.0f@toc-0x778C
        pCharData->x221c_7_hitstun == 0 &&
		!PositionXBetweenLedgesMinDelta_0x80322258(pCharData->xb0_position.x))
        // not sure when we reach this point, but often around the end of knockback, sometimes completely unrelated
    {
        // @728
		pCharData->x18A4_knockbackMagnitude = 0.0f; // 0.0f@toc-0x778C
    }
    //@730
	Hurtbox_SetAllNotUpdated_0x8007AF28(pPlayerEntityStruct);
	//@738 The following classify_float calls are inlined by the compiler. The classify_float function does not appear to be in the melee DOL, maybe it was optimized away by the linker.
	if (debug_level_r13_min_0x6C98 >= 3 && // This value is zero and I think it always will be. Probably some debug level indicator, because only a NaN test follows next.
        (fpclassify(pCharData->xb0_position.x)==FP_NAN || // @744
         fpclassify(pCharData->xb0_position.y)==FP_NAN || // @7ac
         fpclassify(pCharData->xb0_position.z)==FP_NAN)) // @814
	{
		//@87c CR.bits[6] = 1;  // this instruction is generated by the compiler because OSReport is a variadic function. bit[0] = leftmost bit
		OSReport_0x803456A8("fighter procUpdate pos error.  pos.x=%f    pos.y=%f\n"/*r3 = 0x803C0000 + 1452*/, pCharData->xb0_position.x, pCharData->xb0_position.y);
		//@894 TODO: use __FILE__ __LINE__ macros instead?
        __assert_0x80388220("fighter.c" /*filename pointer = 0x803C0000 + 1404*/, /*line*/2517, /*output*/"0"/*r5 = r13 - 31888*/);
    }
    //@8a8 stack unwind
}
