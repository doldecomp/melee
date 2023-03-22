
#include "mn/mncharsel.h"

#include "gm/gmmain_lib.h"
#include "it/item2.h"
#include "lb/lblanguage.h"
#include "mn/mntext.h"

#include <baselib/sislib.h>

extern CSSData* lbl_804D6CB0;
extern SIS* lbl_804D1124[];

TextKerning* func_8025BC20(TextKerning* arg0, u32 arg1)
{
    TextKerning* kerning;
    u32 render_zeroes;
    render_zeroes = 0;
    kerning = lbl_804D1124[0][41].kerning;
    if (arg1 >= 10000) {
        arg1 = 9999;
    }
    if (arg1 >= 1000) {
        arg0->left = kerning[arg1 / 1000].left;
        arg0->right = kerning[arg1 / 1000].right;
        arg0 += 1;
        arg1 = arg1 % 1000;
        render_zeroes = 1;
    }
    if ((arg1 >= 100) || render_zeroes) {
        arg0->left = kerning[arg1 / 100].left;
        arg0->right = kerning[arg1 / 100].right;
        arg0 = arg0 + 1;
        arg1 = arg1 % 100;
        render_zeroes++;
    }
    if ((arg1 >= 10) || render_zeroes) {
        arg0->left = kerning[arg1 / 10].left;
        arg0->right = kerning[arg1 / 10].right;
        arg0 = arg0 + 1;
        arg1 = arg1 % 10;
    }
    arg0->left = kerning[arg1].left;
    arg0->right = kerning[arg1].right;
    arg0[1].left = 0;
    return ++arg0;
}

void func_8025BD30(void)
{
    TextKerning* kerning;

    kerning = lbl_804D1124[0][37].kerning;

    if (lbl_804D6CB0->match_type == 1) {
        func_803A6530(0, 0x4A, 0x4F);
        return;
    }
    if (lbl_804D6CB0->match_type == 2) {
        func_803A6530(0, 0x4A, 0x50);
        return;
    }
    if (lbLang_IsSavedLanguageJP() != 0) {
        if (gmMainLib_8015CC34()->mode == 1) {
            func_8025BC20(kerning, gmMainLib_8015CC34()->stock_count);
        } else if (gmMainLib_8015CC34()->time_limit != 0) {
            func_8025BC20(kerning, gmMainLib_8015CC34()->time_limit);
            func_803A660C(0, 0x4A, 0x53);
        } else {
            func_803A6530(0, 0x4A, 0x51);
        }
        switch (gmMainLib_8015CC34()->mode) {
        case Mode_Time:
            func_803A660C(0, 0x4A, 0x4B);
            return;
        case Mode_Stock:
            func_803A660C(0, 0x4A, 0x4C);
            return;
        case Mode_Coin:
            func_803A660C(0, 0x4A, 0x4D);
            return;
        case Mode_Bonus:
            func_803A660C(0, 0x4A, 0x4E);
            return;
        }
    } else {
        switch (gmMainLib_8015CC34()->mode) {
        case Mode_Time:
            if (gmMainLib_8015CC34()->time_limit != 0) {
                func_8025BC20(kerning, gmMainLib_8015CC34()->time_limit);
                func_803A660C(0, 0x4A, 0x53);
            } else {
                func_803A6530(0, 0x4A, 0x51);
            }
            func_803A660C(0, 0x4A, 0x4B);
            return;
        case Mode_Stock:
            func_8025BC20(kerning, gmMainLib_8015CC34()->stock_count);
            if (gmMainLib_8015CC34()->stock_count < 2U) {
                func_803A660C(0, 0x4A, 0x55);
            } else {
                func_803A660C(0, 0x4A, 0x54);
            }
            func_803A660C(0, 0x4A, 0x4C);
            return;
        case Mode_Coin:
            if (gmMainLib_8015CC34()->time_limit != 0) {
                func_8025BC20(kerning, gmMainLib_8015CC34()->time_limit);
                func_803A660C(0, 0x4A, 0x53);
            } else {
                func_803A6530(0, 0x4A, 0x51);
            }
            func_803A660C(0, 0x4A, 0x4D);
            return;
        case Mode_Bonus:
            if (gmMainLib_8015CC34()->time_limit != 0) {
                func_8025BC20(kerning, gmMainLib_8015CC34()->time_limit);
                func_803A660C(0, 0x4A, 0x53);
            } else {
                func_803A6530(0, 0x4A, 0x51);
            }
            func_803A660C(0, 0x4A, 0x4E);
            return;
        }
    }
}
