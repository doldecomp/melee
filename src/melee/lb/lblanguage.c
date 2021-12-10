#include "lblanguage.h"

u8 lbLang_GetLanguageSetting(void) {
    return lbl_804D3EE0[0];
}

int lbLang_SetLanguageSetting(int language) {
    if(language >= 0 && language < 2) {
        lbl_804D3EE0[0] = language;
    }
}

int lbLang_IsSettingJP(void) {
    return (lbl_804D3EE0[0]) == 0 ? 1 : 0;
}

int lbLang_IsSettingUS(void) {
    return (lbl_804D3EE0[0]) == 1 ? 1 : 0;
}

u8 lbLang_GetSavedLanguage() {
    return func_8015CC58()[0x16];
}

void lbLang_SetSavedLanguage(int language) {
    if(language >= 0 && language < 2)
        func_8015CC58()[0x16] = language;
}

int lbLang_IsSavedLanguageJP(void) {
    return (func_8015CC58()[0x16] == 0) ? 1 : 0;
}

int lbLang_IsSavedLanguageUS(void) {
    return (func_8015CC58()[0x16] == 1) ? 1 : 0;
}
