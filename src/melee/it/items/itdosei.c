// Final version - 97.25% match
// Remaining differences are compiler scheduler artifacts:
// 1. Prologue: mflr/stw order vs stw/mflr (instruction scheduling)
// 2. Dead code: missing unreachable 'li r3,0' at 0x50 (optimizer artifact)

bool itDosei_UnkMotion1_Coll(Item_GObj* gobj)
{
    s32 unused[2];  // Stack padding to achieve 0x20 frame size
    Item* temp_r31;

    temp_r31 = gobj->user_data;

    if (it_8026D8A4(gobj, it_80281C6C)) {
        if (it_80276308(gobj)) {
            it_80281C6C(gobj);
            return false;
        }

        {
            Item* temp_r4 = gobj->user_data;
            f32 var_f1 = M2C_FIELD(temp_r4, f32*, 0x4CC);

            // Absolute value
            if (var_f1 < 0.0f) {
                var_f1 = -var_f1;
            }

            // Check if >= 0.0f (generates cror eq,gt,eq)
            if (var_f1 >= 0.0f) {
                temp_r4->xD5C = 1;
                M2C_FIELD(temp_r4, u8*, 0xDCB) |= 1;
            } else {
                temp_r4->xD5C = 0;
                M2C_FIELD(temp_r4, u8*, 0xDCB) &= ~1;
            }
        }

        // Use persistent r31 pointer for flag check
        if (temp_r31->xD5C == 1) {
            it_3F14_Logic7_EnteredAir(gobj);
        } else {
            it_80276CB8(gobj);
        }
    } else {
        it_80282074(gobj);
    }

    return false;
}
