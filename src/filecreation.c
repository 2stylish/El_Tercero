#include "filecreation.h"

void makeSrcDir(struct stat st) {
  if (-1 == stat("./src", &st)) {
    mkdir("./src", 0700);
  } else {
    printf(COLOR1 "src" RESET " already exists or you have no permission!\n");
  }

  if (-1 == stat("./lib", &st)) {
    mkdir("./lib", 0700);
  } else {
    printf(COLOR1 "lib " RESET "already exists or you have no permission!\n\n");
  }
}

void makeSrcFC(struct stat fakeSt, const char* name) {
  FILE* fp;
  /* Create the main file */
  if (-1 == stat("./src/main.c", &fakeSt)) {
    fp = fopen("./src/main.c", "w");
    fprintf(fp,
            "#include <stdio.h>\n\n"
            "int main(int argc, char** argv){\n"
            "  printf(\"Eternitatem cogita.\\n\");\n"
            "}");
    fclose(fp);
  } else {
    printf(COLOR2 "main.c" RESET
                  " already exists or you have no permission!\n");
  }

  if (-1 == stat("./meson.build", &fakeSt)) {
    fp = fopen("./meson.build", "w");
    fprintf(fp,
            "project(\'%s\', \'c\', default_options : [\'warning_level=3\', "
            "\'c_std=c99\'])\n\n"

            "add_global_arguments(language : \'c\')\n"
            "c = meson.get_compiler(\'c\')\n\n"

            "#Sample built-in libs\n"
            "#mathl = c.find_library(\'m\', required : true)\n"
            "#runtimel = c.find_library(\'rt\', required : true)\n"
            "#dlib = c.find_library(\'dl\', required : true)\n\n"

            "#Sample dependencies\n"
            "#depz = [dependency(\'raylib\'), dependency(\'GL\'), "
            "dependency(\'X11\'), dependency(\'threads\')]\n\n"

            "#include dirs\n"
            "#libz = include_directories(\'lib\')\n\n"

            "#main source\n"
            "srcs = [\'src/main.c\']\n\n"

            "executable(\'main\', srcs, dependencies : depz)",
            name);
    fclose(fp);
  } else {
    printf(COLOR2 "meson.build" RESET
                  " already exists or you have no permission!\n\n");
  }
}
void makeSrcFCXX(struct stat fakeSt, const char* name) {
  FILE* fp;
  if (-1 == stat("./src/main.cxx", &fakeSt)) {
    fp = fopen("./src/main.cxx", "w");
    fprintf(fp,
            "#include <iostream>\n\n"
            "int main(int argc, char** argv){\n"
            "  printf(\"Extra lutum pedes habes.\\n\");\n"
            "}");
    fclose(fp);
  } else {
    printf(COLOR2 "main.cxx" RESET
                  " already exists or you have no perimssions!\n");
  }

  if (-1 == stat("./meson.build", &fakeSt)) {
    fp = fopen("./meson.build", "w");
    fprintf(fp,
            "project(\'%s\', \'cpp\', default_options : [\'warning_level=3\', "
            "\'cpp_std=c++17\'])\n\n"

            "add_global_arguments(language : \'cpp\')\n"
            "cpp = meson.get_compiler(\'cpp\')\n\n"

            "#Sample built-in libs\n"
            "#mathl = cpp.find_library(\'m\', required : true)\n"
            "#runtimel = cpp.find_library(\'rt\', required : true)\n"
            "#dlib = cpp.find_library(\'dl\', required : true)\n\n"

            "#Sample dependencies\n"
            "#depz = [dependency(\'raylib\'), dependency(\'GL\'), "
            "dependency(\'X11\'), dependency(\'threads\')]\n\n"

            "#include dirs\n"
            "#libz = include_directories(\'lib\')\n\n"

            "#main source\n"
            "srcs = [\'src/main.cxx\']\n\n"

            "executable(\'main\', srcs, dependencies : depz)",
            name);
    fclose(fp);
  } else {
    printf(COLOR2 "meson.build" RESET
                  " already exists or you have no permission!\n");
  }
}

