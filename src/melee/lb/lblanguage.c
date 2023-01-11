#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lblanguage.h>

enum_t lbLang_GetLanguageSetting(void)
{
    return lbl_804D3EE0->language;
}

enum_t lbLang_SetLanguageSetting(enum_t language)
{
    if (language >= 0 && language < 2) {
        lbl_804D3EE0->language = language;
    }

    return language;
}

enum_t lbLang_IsSettingJP(void)
{
    return (lbl_804D3EE0->language) == 0 ? 1 : 0;
}

enum_t lbLang_IsSettingUS(void)
{
    return (lbl_804D3EE0->language) == 1 ? 1 : 0;
}

enum_t lbLang_GetSavedLanguage(void)
{
    return func_8015CC58()->saved_language;
}

void lbLang_SetSavedLanguage(enum_t language)
{
    if (language >= 0 && language < 2)
        func_8015CC58()->saved_language = language;
}

enum_t lbLang_IsSavedLanguageJP(void)
{
    return (func_8015CC58()->saved_language == 0) ? 1 : 0;
}

enum_t lbLang_IsSavedLanguageUS(void)
{
    return (func_8015CC58()->saved_language == 1) ? 1 : 0;
}
