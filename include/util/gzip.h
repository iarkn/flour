#ifndef UTIL_GZIP_H
#define UTIL_GZIP_H

#include <stdio.h>

int gzip_def(FILE *src, FILE *dst, int level);
int gzip_inf(FILE *src, FILE *dst);
int gzip_c(int code);

#endif // UTIL_GZIP_H
