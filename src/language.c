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

char* dummyTrim(char* string, int len) {
  if (isspace(string[0])) {
    printf("im entering this block for some reason\n");
    while (*string == ' ') {
      string++;
    }
  }
  char* trailing = string + (len - 1);
  printf("NUMBA%d\n", len);
  if (isspace(string[len - 1])) {
    while (*trailing == ' ') {
      trailing = '\0';
      trailing--;
    }
  }
  /* have to return modified string */
  /* Since it decays into a pointer, im assuming it doesnt modify the real
   * value, we just moving locations around */
  return string;
}

void chooseInit(const char* lang, const char* pjname) {
  struct stat fakeSt = {0};

  makeSrcDir(fakeSt);
  /* I did this blasphemy because no string comparation in switch statements */
  if (0 == strcmp(lang, "c")) {
    makeSrcFC(fakeSt, pjname);
    printf("c language\n");
  } else if (0 == strcmp(lang, "C")) {
    makeSrcFC(fakeSt, pjname);
    printf("C language\n");
  } else if (0 == strcmp(lang, "cee")) {
    makeSrcFC(fakeSt, pjname);
    printf("cee language\n");
  } else if (0 == strcmp(lang, "sea")) {
    makeSrcFC(fakeSt, pjname);
    printf("sea language\n");
  } else if (0 == strcmp(lang, "see")) {
    makeSrcFC(fakeSt, pjname);
    printf("see language\n");
  } else if (0 == strcmp(lang, "cxx")) {
    makeSrcFCXX(fakeSt, pjname);
    printf("cxx language\n");
  } else if (0 == strcmp(lang, "cpp")) {
    makeSrcFCXX(fakeSt, pjname);
    printf("cpp language\n");
  } else if (0 == strcmp(lang, "c++")) {
    makeSrcFCXX(fakeSt, pjname);
    printf("c++ language\n");
  } else if (0 == strcmp(lang, "CXX")) {
    makeSrcFCXX(fakeSt, pjname);
    printf("CXX language\n");
  } else if (0 == strcmp(lang, "CPP")) {
    makeSrcFCXX(fakeSt, pjname);
    printf("CPP language\n");
  } else if (0 == strcmp(lang, "C++")) {
    makeSrcFCXX(fakeSt, pjname);
    printf("C++ language\n");
  } else if (0 == strcmp(lang, "gay")) {
    makeSrcFCXX(fakeSt, pjname);
    printf("gay language\n");
  } else {
    printf("Defaulting to C\n");
    makeSrcFC(fakeSt, pjname);
  }
}

