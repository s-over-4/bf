#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void util_die(const char* fmt, ...);   // print msg and exit
void util_log(const char* fmt, ...);   // print msg
char* util_get_src(char* arg);         // parse argtuments
char* util_src_from_stdin();           // get source from stdin
char* util_src_from_fpath(FILE* f);    // get source from file path

#endif
