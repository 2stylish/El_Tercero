#include "language.h"

#include <ctype.h>

#include "filecreation.h"

void getName(char* name) {
  if (fgets(name, 41, stdin)) {
    /* Replaces newline with 0 */
    name[strcspn(name, "\n")] = 0;
  }
}

void getLanguage(char* lang) {
  if (fgets(lang, 4, stdin)) {
    /* Replaces newline with 0 */
    lang[strcspn(lang, "\n")] = 0;
  }
}

void getLicense(char* lic) {
  if (fgets(lic, 4, stdin)) {
    /* Replace newline with 0 */
    lic[strcspn(lic, "\n")] = 0;
  }
}

int getBSD(char* bsd) {
  int a;
  do {
    if (!fgets(bsd, 1024, stdin)) {
      return 1;
    }
    a = atoi(bsd);
  } while (a == 0);
  return a;
}

char* dummyTrim(char* hilo) {
  while (*hilo == ' ') {
    hilo++;
  }
  char* trailing = hilo + (strlen(hilo) - 1);
  while (trailing > hilo && *trailing == ' ') {
    trailing--;
  }
  trailing = '\0';
  /* have to return modified string */
  /* Since it decays into a pointer, im assuming it doesnt modify the real
   * value, we just moving locations around */
  return hilo;
}

int checkBSD(char* lic) {
  const char* licTrim = dummyTrim(lic);

  if (0 == strcmp(licTrim, "b")) {
    return 1;
  } else if (0 == strcmp(licTrim, "b ")) {
    return 1;
  } else if (0 == strcmp(licTrim, "B")) {
    return 1;
  } else if (0 == strcmp(licTrim, "B ")) {
    return 1;
  } else if (0 == strcmp(licTrim, "bsd")) {
    return 1;
  } else if (0 == strcmp(licTrim, "BSD")) {
    return 1;
  } else {
    /* Defaults to no license */
    return 0;
  }
}

void chooseInit(char* lang, const char* pjname) {
  struct stat fakeSt = {0};
  const char* langTrim = dummyTrim(lang);
  makeRDME(fakeSt, pjname);
  makeGIGN(fakeSt, pjname);
  makeGATR(fakeSt, pjname);
  makeSrcDir(fakeSt);
  /* I did this blasphemy because no string comparison in switch statements */
  if (0 == strcmp(langTrim, "c")) {
    makeSrcFC(fakeSt, pjname);
  } else if (0 == strcmp(langTrim, "c ")) {
    makeSrcFC(fakeSt, pjname);
  } else if (0 == strcmp(langTrim, "C ")) {
    makeSrcFC(fakeSt, pjname);
  } else if (0 == strcmp(langTrim, "C")) {
    makeSrcFC(fakeSt, pjname);
  } else if (0 == strcmp(langTrim, "cee")) {
    makeSrcFC(fakeSt, pjname);
  } else if (0 == strcmp(langTrim, "sea")) {
    makeSrcFC(fakeSt, pjname);
  } else if (0 == strcmp(langTrim, "see")) {
    makeSrcFC(fakeSt, pjname);
  } else if (0 == strcmp(langTrim, "cxx")) {
    makeSrcFCXX(fakeSt, pjname);
  } else if (0 == strcmp(langTrim, "cpp")) {
    makeSrcFCXX(fakeSt, pjname);
  } else if (0 == strcmp(langTrim, "c++")) {
    makeSrcFCXX(fakeSt, pjname);
  } else if (0 == strcmp(langTrim, "CXX")) {
    makeSrcFCXX(fakeSt, pjname);
  } else if (0 == strcmp(langTrim, "CPP")) {
    makeSrcFCXX(fakeSt, pjname);
  } else if (0 == strcmp(langTrim, "C++")) {
    makeSrcFCXX(fakeSt, pjname);
  } else if (0 == strcmp(langTrim, "gay")) {
    makeSrcFCXX(fakeSt, pjname);
  } else {
    printf("Defaulting to C\n");
    makeSrcFC(fakeSt, pjname);
  }
}

