#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "filecreation.h"
#include "language.h"

int main(int argc, char** argv) {
  char name[41];
  char lang[4];
  int len;
  if (1 < argc) {
    printf("No flags, fuk u\n");
  }

  printf("Project" COLOR3 " name:" RESET);
  getName(name);
  printf("Project" COLOR3 " language:" RESET);
  getLanguage(lang);

  len = strlen(lang);
  char* langTrim = dummyTrim(lang, len);
  printf("trimmed str%s", langTrim);
  printf("test\n");
  chooseInit(langTrim, name);
  printf("Please choose a " COLOR3 "license" RESET
         " 8=D\n"
         "Options:\n"
         "\t" RED "BSD\n" RESET "\t" ORANGE "GPL\n" RESET
         "\tNone\n"
         "Choice: ");
}
