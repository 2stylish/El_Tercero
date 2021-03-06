#ifndef FILECREATION_H_
#define FILECREATION_H_

#define COLOR1 "\033[38;5;214m"
#define COLOR2 "\033[38;5;147m"
#define COLOR3 "\033[38;5;44m"
#define RED "\033[38;5;196m"
#define ORANGE "\033[38;5;208m"
#define RESET "\033[0m"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void makeRDME(struct stat st, const char* name);
void makeSrcDir(struct stat st);
void makeSrcFC(struct stat fakeSt, const char* name);
void makeSrcFCXX(struct stat fakeSt, const char* name);

#endif /* ifndef SYMBOL */
