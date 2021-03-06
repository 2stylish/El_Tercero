#ifndef LANGUAGE_H_
#define LANGUAGE_H_ value

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

void getName(char* name);
void getLanguage(char* lang);
char* dummyTrim(char* string, int len);
void chooseInit(const char* lang, const char* pjname);

#endif /* ifndef LANGUAGE_H_ */
