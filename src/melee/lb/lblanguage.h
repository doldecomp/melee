#ifndef _lblanguage_h_
#define _lblanguage_h_

#include <global.h>

#include <dolphin/types.h>

extern u8 *lbl_804D3EE0;
extern u8 *func_8015CC58();

u8 lbLang_GetLanguageSetting(void);
int lbLang_SetLanguageSetting(int language);
int lbLang_IsSettingJP(void);
int lbLang_IsSettingUS(void);
u8 lbLang_GetSavedLanguage(void);
void lbLang_SetSavedLanguage(int language);
int lbLang_IsSavedLanguageJP(void);
int lbLang_IsSavedLanguageUS(void);

#endif
