#ifndef _lblanguage_h_
#define _lblanguage_h_

#include <platform.h>

enum_t lbLang_GetLanguageSetting(void);
enum_t lbLang_SetLanguageSetting(enum_t language);
enum_t lbLang_IsSettingJP(void);
enum_t lbLang_IsSettingUS(void);
enum_t lbLang_GetSavedLanguage(void);
void lbLang_SetSavedLanguage(enum_t language);
enum_t lbLang_IsSavedLanguageJP(void);
enum_t lbLang_IsSavedLanguageUS(void);

#endif
