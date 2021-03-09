#include "filecreation.h"

#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "contents.h"
#include "licenseText.h"

void checkErr() {
  if (EACCES == errno) {
    printf("NO PERMISSION IDIOT\n");
    exit(EXIT_FAILURE);
  }
}

void makeRDME(struct stat fakeSt, const char* name) {
  FILE* rd;
  if (-1 == stat("./README.md", &fakeSt)) {
    rd = fopen("./README.md", "w");
    checkErr();
    fprintf(rd, RDME, name);
    fclose(rd);
  } else {
    printf(COLOR1 "README.md" RESET " already exists!\n");
  }
}
void makeGIGN(struct stat fakeSt, const char* name) {
  FILE* gign;
  if (-1 == stat("./.gitignore", &fakeSt)) {
    gign = fopen("./.gitignore", "w");
    checkErr();
    fprintf(gign, GIGN, name);
    fclose(gign);
  } else {
    printf(COLOR2 ".gitignore" RESET " already exists!\n");
  }
}
void makeGATR(struct stat fakeSt, const char* name) {
  FILE* gatr;
  if (-1 == stat("./.gitattributes", &fakeSt)) {
    gatr = fopen("./.gitattributes", "w");
    checkErr();
    fprintf(gatr, GATR, name);
    fclose(gatr);
  } else {
    printf(COLOR2 ".gitattributes" RESET " already exists!\n");
  }
}

void makeBSD(int bsdNum) {
  struct stat fakeSt = {0};
  FILE* bsd;
  if (-1 != stat("./LICENSE", &fakeSt)) {
    printf(COLOR2 "LICENSE" RESET " already exists!\n");
  }
  if (-1 == stat("./LICENSE", &fakeSt) && 1 == bsdNum) {
    bsd = fopen("./LICENSE", "w");
    checkErr();
    fprintf(bsd, BSD1);
    fclose(bsd);
  } else if (-1 == stat("./LICENSE", &fakeSt) && 2 == bsdNum) {
    bsd = fopen("./LICENSE", "w");
    checkErr();
    fprintf(bsd, BSD2);
    fclose(bsd);
  } else if (-1 == stat("./LICENSE", &fakeSt) && 3 == bsdNum) {
    bsd = fopen("./LICENSE", "w");
    checkErr();
    fprintf(bsd, BSD3);
    fclose(bsd);
  } else if (-1 == stat("./LICENSE", &fakeSt) && 4 == bsdNum) {
    bsd = fopen("./LICENSE", "w");
    checkErr();
    fprintf(bsd, BSD4);
    fclose(bsd);
  } else {
    printf("Defaulting to BSD 3-Clause\n");
    bsd = fopen("./LICENSE", "w");
    checkErr();
    fprintf(bsd, BSD3);
    fclose(bsd);
  }
}

void makeSrcDir(struct stat fakeSt) {
  if (-1 == stat("./src", &fakeSt)) {
    mkdir("./src", 0700);
    checkErr();
  } else {
    printf(COLOR1 "src" RESET " already exists!\n");
  }

  if (-1 == stat("./lib", &fakeSt)) {
    mkdir("./lib", 0700);
    checkErr();
  } else {
    printf(COLOR1 "lib " RESET "already exists!\n\n");
  }
}

void makeSrcFC(struct stat fakeSt, const char* name) {
  FILE* fp;
  /* Create the main file */
  if (-1 == stat("./src/main.c", &fakeSt)) {
    fp = fopen("./src/main.c", "w");
    checkErr();
    fprintf(fp, CCONT);
    fclose(fp);
  } else {
    printf(COLOR2 "main.c" RESET " already exists!\n");
  }

  if (-1 == stat("./meson.build", &fakeSt)) {
    fp = fopen("./meson.build", "w");
    checkErr();
    fprintf(fp, CMES, name);
    fclose(fp);
  } else {
    printf(COLOR2 "meson.build" RESET " already exists!\n\n");
  }
}
void makeSrcFCXX(struct stat fakeSt, const char* name) {
  FILE* fp;
  if (-1 == stat("./src/main.cxx", &fakeSt)) {
    fp = fopen("./src/main.cxx", "w");
    checkErr();
    fprintf(fp, CXXCONT);
    fclose(fp);
  } else {
    printf(COLOR2 "main.cxx" RESET " already exists!\n");
  }

  if (-1 == stat("./meson.build", &fakeSt)) {
    fp = fopen("./meson.build", "w");
    checkErr();
    fprintf(fp, CXXMES, name);
    fclose(fp);
  } else {
    printf(COLOR2 "meson.build" RESET " already exists!\n");
  }
}

