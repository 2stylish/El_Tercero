#ifndef LANGUAGE_H_
#define LANGUAGE_H_ value

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

void getName(char* name);
void getLanguage(char* lang);
char* dummyTrim(char* hilo);
void chooseInit(char* lang, const char* pjname);
void getLicense(char* lic);
int getBSD(char* bsd);
int checkBSD(char* lic);

#endif /* ifndef LANGUAGE_H_ */
