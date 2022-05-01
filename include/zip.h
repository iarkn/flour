#ifndef ZIP_H
#define ZIP_H

#include <stdio.h>

int zip_def(FILE *src, FILE *dst, int level);
int zip_inf(FILE *src, FILE *dst);
int zip_c(int code);

#endif // ZIP_H
