#ifndef _lblanguage_h_
#define _lblanguage_h_

#include <platform.h>

enum_t lbLang_GetLanguageSetting(void);
enum_t lbLang_SetLanguageSetting(enum_t language);
bool lbLang_IsSettingJP(void);
bool lbLang_IsSettingUS(void);
enum_t lbLang_GetSavedLanguage(void);
void lbLang_SetSavedLanguage(enum_t language);
bool lbLang_IsSavedLanguageJP(void);
bool lbLang_IsSavedLanguageUS(void);

#endif
