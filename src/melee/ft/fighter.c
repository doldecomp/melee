#include "fighter.h"

typedef struct _Vec2 { float x, y;    } Vec2;
typedef struct _Vec3 { float x, y, z; } Vec3;

// 8006B82C
void /*fighter_procUpdate*/func_8006B82C(HSD_GObj* pPlayerEntityStruct)
{
    //@1c
    Fighter* pCharData = (Fighter*) pPlayerEntityStruct->user_data;
    u32 dummy; // not used, only here to match the target's stack allocation layout
    Vec3 windOffset;
    //@20
    if (pCharData->flags.sleep) // if pCharData->byte_at_0x221F & 0b10000
		return;
    
    //@30
    if (!pCharData->flags.freeze)
    {
        Vec2* p_kb_vel;
        Vec2* pAtkShieldKB;
        float kb_vel_x, atkShieldKB_X;
        Vec3 selfVel;

        //@3c
        if (pCharData->ledge_cooldown != 0)
			pCharData->ledge_cooldown -= 1;
        if (pCharData->x2108 != 0)
			pCharData->x2108 -= 1;
        
        //@64
        FtChkDevice_DecrementImmunity_800C0A98(pPlayerEntityStruct);

        //@6c
		if (pCharData->cb.Phys != 0)
			pCharData->cb.Phys(pPlayerEntityStruct); // AS_Physics_Func callback @0x21A4
        //@84
        p_kb_vel = (Vec2*)&pCharData->phys.x8c_kb_vel;
		if ((kb_vel_x = p_kb_vel->x) != 0 || p_kb_vel->y != 0)
        {//float f;
            //@a4
			if (pCharData->phys.xE0_airborne == 1) // # 0=grounded, 1=airborne.
            {
                //@b0
				float kb_vel_x = p_kb_vel->x;
				float kb_vel_y = p_kb_vel->y;
				// I was not able to trigger this case in normal gameplay yet. spreadsheet comment: facing angle? hi-pitch, lo-pitch, noCliffCatch
				if ((pCharData->flags.x2228 >> 5) & 1) // equivalent to x2228 & 0b0010_0000
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
				pCharData->phys.xF0_ground_kb_vel = 0; // 0.0f@toc-0x778C
            }
			else
            {
                // @1cc
                //float effectiveFriction;
                Vec3* pNormal = &pCharData->coll_data.ground_normal; // ground_normal offset inside pCharData is 0x844, surface normal points out of the surface. 
                struct attr* pAttr;
                // This is probably triggered when transitioning from the air to the ground, for example with ASDI down after getting hit.
				if (pCharData->phys.xF0_ground_kb_vel == 0)
					pCharData->phys.xF0_ground_kb_vel = kb_vel_x;
                //@1e4
                pAttr = &pCharData->attr; // attr has offset 0x110
                reduceGroundKnockbackVel_0x8007CCA0(pCharData,
                    /*effective friction - ground multiplier is usually 1. last factor was 1 when I looked*/
                    Stage_GetGroundFrictionMultiplier_0x80084A40(pCharData) * pAttr->x128_ground_friction * p_stc_ftcommon->x200);
				// @210 set knockback velocity to ground_kb_vel * surfaceTangent
                p_kb_vel->x =  pNormal->y * pCharData->phys.xF0_ground_kb_vel;
                // @220
                p_kb_vel->y = -pNormal->x * pCharData->phys.xF0_ground_kb_vel;
            }
        }
        //@230 Now handle the attacker's shield knockback in a similar way
        pAtkShieldKB = (Vec2*)&pCharData->phys.x98_atk_shield_kb;
        if ((atkShieldKB_X = pAtkShieldKB->x) != 0 || pAtkShieldKB->y != 0)
        {
            //@250
            if (pCharData->phys.xE0_airborne == 1)
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
                pCharData->phys.xF4_ground_attacker_shield_kb_vel = 0; // 0 = TOC.float@-0x778C
            }
            else
            {
                //@338
                float effectiveFriction;
                Vec3* pNormal = &pCharData->coll_data.ground_normal; // ground_normal offset inside pCharData is 0x844, surface normal points out of the surface. 
                struct attr* pAttr;
                //@344
                if (pCharData->phys.xF4_ground_attacker_shield_kb_vel == 0)
                    pCharData->phys.xF4_ground_attacker_shield_kb_vel = atkShieldKB_X;
                //@350
                pAttr = &pCharData->attr; // attr has offset 0x110
                //@374
                reduceGroundShieldKnockbackVel_0x8007CE4C(pCharData,
                    /* effectiveFriction - the last constant variable differs from the one for the knockback friction above*/
                    Stage_GetGroundFrictionMultiplier_0x80084A40(pCharData) * pAttr->x128_ground_friction * p_stc_ftcommon->x3ec);
                //@378
                pAtkShieldKB->x =  pNormal->y * pCharData->phys.xF4_ground_attacker_shield_kb_vel;
                pAtkShieldKB->y = -pNormal->x * pCharData->phys.xF4_ground_attacker_shield_kb_vel;
            }
        }

        //@39c update ground velocity
		pCharData->phys.xEC_ground_vel += pCharData->phys.xE4_ground_accel_1 + pCharData->phys.xE8_ground_accel_2;
        //@3c0
		pCharData->phys.xE8_ground_accel_2 = 0;
        pCharData->phys.xE4_ground_accel_1 = 0;

        //@3cc self_vel += anim_vel
		PSVECAdd_0x80342D54(&pCharData->phys.x80_self_vel, &pCharData->phys.x74_anim_vel, &pCharData->phys.x80_self_vel);
        //@3d0
		pCharData->phys.x74_anim_vel.z = 0;
        pCharData->phys.x74_anim_vel.y = 0;
        pCharData->phys.x74_anim_vel.x = 0;
		
		//@3e0 copy selfVel into a stack storage variable
		selfVel = pCharData->phys.x80_self_vel;
		
		// TODO: these double_lower_32bit variables are probably integer counters that get decremented each frame,
        // but I was not able to trigger the following condition.
		//@3f8 The double value construction then is only used as an interpolation tool between selfVel and some UnkVel2.
		if (pCharData->dmg.x1948 != 0)
        {
            //@404
            // The compiler casts an u32 integer 'val' to a double type using
            // double v = *(double*)&(0x43300000_00000000 | val ^ 0x80000000) - *(double*)&43300000_80000000
            // which is all that happens in the length assembly generated by this
			float C = 1.0f - (float)pCharData->dmg.x194C / (float)pCharData->dmg.x1948;
			selfVel.x = C * (pCharData->phys.x80_self_vel.x - pCharData->phys.xA4_unk_vel.x) + pCharData->phys.xA4_unk_vel.x;
            //@458
            selfVel.y = C * (pCharData->phys.x80_self_vel.y - pCharData->phys.xA4_unk_vel.y) + pCharData->phys.xA4_unk_vel.y;
            //@46c
            pCharData->dmg.x194C--;
			if (pCharData->dmg.x194C == 0)
				pCharData->dmg.x1948 = 0;
        }
		//@48c add some horizontal+depth offset to the position? Why is there no vertical component?
		pCharData->phys.xB0_position.x += pCharData->phys.xF8_player_nudge_vel.x;
		pCharData->phys.xB0_position.z += pCharData->phys.xF8_player_nudge_vel.y;
        //@4ac
        if (pCharData->flags.x2222_7 && !pCharData->flags.x2222_8)
        {
            s32 bit;
            //@4c0
            // pCharData->phys.xD4_unk_vel += selfVel
			PSVECAdd_0x80342D54(&pCharData->phys.xD4_unk_vel, &selfVel, &pCharData->phys.xD4_unk_vel);
			//@4d0
            pCharData->phys.xD4_unk_vel.x += p_kb_vel->x;
            pCharData->phys.xD4_unk_vel.y += p_kb_vel->y;
            //@4f0
            if (pCharData->flags.x2210_throw_3)
            {
			    pCharData->flags.x2210_throw_3 = 0;
                bit = 1;
            }
            else
                bit = 0;
			//@514
			if (bit || func_80070FD0(pCharData) != 0 || pCharData->x594_anim_curr_flags_1 & 1)
            {
                //@538
                // pCharData->phys.xB0_position += pCharData->phys.xD4_unk_vel
				PSVECAdd_0x80342D54(&pCharData->phys.xB0_position, &pCharData->phys.xD4_unk_vel, &pCharData->phys.xB0_position);
				// TODO: we set this velocity to 0 after applying it -> Is this SDI or ASDI?
                pCharData->phys.xD4_unk_vel.z = 0;
                pCharData->phys.xD4_unk_vel.y = 0;
                pCharData->phys.xD4_unk_vel.x = 0;
            }
			//@558 pCharData->phys.xB0_position += *pAtkShieldKB
            PSVECAdd_0x80342D54(&pCharData->phys.xB0_position, (Vec3*)pAtkShieldKB, &pCharData->phys.xB0_position);
        }
		else
        {
            //pCharData@r31.position@0xB0.xyz += selfVel + pAtkShieldKB
			PSVECAdd_0x80342D54(&pCharData->phys.xB0_position, &selfVel, &pCharData->phys.xB0_position);
			pCharData->phys.xB0_position.x += p_kb_vel->x;
            pCharData->phys.xB0_position.y += p_kb_vel->y;
            PSVECAdd_0x80342D54(&pCharData->phys.xB0_position, (Vec3*)pAtkShieldKB, &pCharData->phys.xB0_position);
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
	if (pCharData->cb.EveryHitlag_x21D0 != 0)
		pCharData->cb.EveryHitlag_x21D0(pPlayerEntityStruct); // void (*EveryHitlag_x21D0)(GOBJ *fighter)
    
    //@5ec
	if (pCharData->phys.xE0_airborne == 0)
    {
        //@5f8
		Vec3 difference;
		// I think this function always returns r3=1, but it contains two __assert functions. But I guess these just stop or reset the game.
		// result is written to where r5 points to, which is 'difference' in this case
		if (Collision_GetPositionDifference_0x800567C0(pCharData->coll_data.x83c_ground_index/*groundID field not documented*/, /*Vec3*/&pCharData->phys.xB0_position, &difference))
			//@610 pCharData->position += difference
			PSVECAdd_0x80342D54(&pCharData->phys.xB0_position, &difference, &pCharData->phys.xB0_position);
    }
	
	//@620
	pCharData->phys.xB0_position.x += windOffset.x;
    pCharData->phys.xB0_position.y += windOffset.y;
    pCharData->phys.xB0_position.z += windOffset.z;

    //@654 TODO: do the bitflag tests here tell us if the player is dead?
	Player_CheckForDeath_0x800D3158(pPlayerEntityStruct);
    //@658
	if (pCharData->flags.x2225_1)
    {
		//@664 if position.y crossed (0.25*stage.blastBottom+0.75*stage.cameraBottom) + stage.crowdReactStart from below...
		if (pCharData->phys.xBC_pos_prev.y <= StageInfo_CrowdGaspHeight_0x80224BC4() &&
		    pCharData->phys.xB0_position.y >  StageInfo_CrowdGaspHeight_0x80224BC4())
			pCharData->flags.x2225_1 = 0;
    }
	else
    {
        //@69c
		if ((pCharData->flags.x222A_2 == 0) && (/*!x2228_6*/((pCharData->flags.x2228 >> 2) & 1) == 0))
        {
			//@6b4 if position.y crossed 0.5*(stage.blastBottom+stage.cameraBottom) + stage.crowdReactStart from above...
			if (pCharData->phys.xBC_pos_prev.y >= StageInfo_OffscreenBottomLoad_0x80224B98() &&
			    pCharData->phys.xB0_position.y <  StageInfo_OffscreenBottomLoad_0x80224B98())
				//@6e8 plays this sound you always hear when you get close to the bottom blast zone
				SFX_PlayCharacterSFX_0x80088148(pCharData, 96, 127, 64);
                //@6ec
				pCharData->flags.x2225_1 = 1;
        }
    }
	//@6fc
	if (pCharData->dmg.x18A4_knockbackMagnitude  && // 0.0f@toc-0x778C
        pCharData->flags.x221c_7_hitstun == 0 &&
		!PositionXBetweenLedgesMinDelta_0x80322258(pCharData->phys.xB0_position.x))
        // not sure when we reach this point, but often around the end of knockback, sometimes completely unrelated
    {
        // @728
		pCharData->dmg.x18A4_knockbackMagnitude = 0.0f; // 0.0f@toc-0x778C
    }
    //@730
	Hurtbox_SetAllNotUpdated_0x8007AF28(pPlayerEntityStruct);
	//@738 The following classify_float calls are inlined by the compiler. The classify_float function does not appear to be in the melee DOL, maybe it was optimized away by the linker.
	if (debug_level_r13_min_0x6C98 >= 3 && // This value is zero and I think it always will be. Probably some debug level indicator, because only a NaN test follows next.
        (fpclassify(pCharData->phys.xB0_position.x)==FP_NAN || // @744
         fpclassify(pCharData->phys.xB0_position.y)==FP_NAN || // @7ac
         fpclassify(pCharData->phys.xB0_position.z)==FP_NAN)) // @814
	{
		//@87c CR.bits[6] = 1;  // this instruction is generated by the compiler because OSReport is a variadic function. bit[0] = leftmost bit
		OSReport_0x803456A8("fighter procUpdate pos error.  pos.x=%f    pos.y=%f\n"/*r3 = 0x803C0000 + 1452*/, pCharData->phys.xB0_position.x, pCharData->phys.xB0_position.y);
		//@894 TODO: use __FILE__ __LINE__ macros instead?
        __assert_0x80388220("fighter.c" /*filename pointer = 0x803C0000 + 1404*/, /*line*/2517, /*output*/"0"/*r5 = r13 - 31888*/);
    }
    //@8a8 stack unwind
}
