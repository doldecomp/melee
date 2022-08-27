#include <melee/lb/lblanguage.h>
#include <melee/gm/gmmain_lib.h>

u8 lbLang_GetLanguageSetting(void) {
    return lbl_804D3EE0->language;
}

int lbLang_SetLanguageSetting(int language) {
    if(language >= 0 && language < 2) {
        lbl_804D3EE0->language = language;
    }
}

int lbLang_IsSettingJP(void) {
    return (lbl_804D3EE0->language) == 0 ? 1 : 0;
}

int lbLang_IsSettingUS(void) {
    return (lbl_804D3EE0->language) == 1 ? 1 : 0;
}

u8 lbLang_GetSavedLanguage() {
    return func_8015CC58()->saved_language;
}

void lbLang_SetSavedLanguage(int language) {
    if(language >= 0 && language < 2)
        func_8015CC58()->saved_language = language;
}

int lbLang_IsSavedLanguageJP(void) {
    return (func_8015CC58()->saved_language == 0) ? 1 : 0;
}

int lbLang_IsSavedLanguageUS(void) {
    return (func_8015CC58()->saved_language == 1) ? 1 : 0;
}
