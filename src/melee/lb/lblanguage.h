#ifndef _lblanguage_h_
#define _lblanguage_h_

#include <dolphin/types.h>

int lbLang_GetLanguageSetting(void);
int lbLang_SetLanguageSetting(int language);
int lbLang_IsSettingJP(void);
int lbLang_IsSettingUS(void);
int lbLang_GetSavedLanguage(void);
void lbLang_SetSavedLanguage(int language);
int lbLang_IsSavedLanguageJP(void);
int lbLang_IsSavedLanguageUS(void);

#endif
