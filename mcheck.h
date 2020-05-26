#ifndef MCHECK_H
#define MCHECK_H
#include <stdlib.h>
#define malloc(s) malloc_tracked(s, __LINE__, __FILE__)
#define free(p) free_tracked(p, __LINE__, __FILE__)

size_t DumpMemRecord();

void* malloc_tracked(size_t, long ln, const char *file);

void free_tracked(void *, long ln, const char *file);

#endif