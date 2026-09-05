#include "lblanguage.h"

#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>

enum_t lbLang_GetLanguageSetting(void)
{
    return gmMainLib_804D3EE0->language;
}

enum_t lbLang_SetLanguageSetting(enum_t language)
{
    if (language >= 0 && language < LANG_COUNT) {
        gmMainLib_804D3EE0->language = language;
    }

    return language;
}

bool lbLang_IsSettingJP(void)
{
    return gmMainLib_804D3EE0->language == LANG_JP ? true : false;
}

bool lbLang_IsSettingUS(void)
{
    return gmMainLib_804D3EE0->language == LANG_US ? true : false;
}

enum_t lbLang_GetSavedLanguage(void)
{
    return gmMainLib_8015CC58()->saved_language;
}

void lbLang_SetSavedLanguage(enum_t language)
{
    if (language >= 0 && language < LANG_COUNT) {
        gmMainLib_8015CC58()->saved_language = language;
    }
}

bool lbLang_IsSavedLanguageJP(void)
{
    return gmMainLib_8015CC58()->saved_language == LANG_JP ? true : false;
}

bool lbLang_IsSavedLanguageUS(void)
{
    return gmMainLib_8015CC58()->saved_language == LANG_US ? true : false;
}
