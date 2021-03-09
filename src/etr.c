#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
/* TODO: add cerrno and make it so if i have no permissions i dont create shit
 */

#include "filecreation.h"
#include "language.h"

int main(int argc, char** argv) {
  char name[41];
  char lang[4];
  char lic[4];
  char bsd[1024];
  int bsdNum;
  if (1 < argc) {
    printf("No flags, fuk u\n");
  }

  printf("Project" COLOR3 " name:" RESET);
  getName(name);
  printf("Project" COLOR3 " language:" RESET);
  getLanguage(lang);

  chooseInit(lang, name);

  printf("Please choose a " COLOR3 "license" RESET
         " 8=D\n"
         "Options:\n"
         "\t" RED "BSD\n" RESET
         "\t[N]one\n"
         "Choice: ");
  getLicense(lic);
  if (checkBSD(lic)) {
    printf(
        "Choose your BSD license!\n"
        "Enter a number between:" RED " 1 - 4\n" RESET
        "(This determines the clause you get)\n"
        "Choice: ");
    bsdNum = getBSD(bsd);
    makeBSD(bsdNum);
  } else {
    printf(ORANGE "No license!\n" RESET);
  }
}
