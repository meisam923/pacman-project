#ifndef laodmap
#define loadmap
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef HIGHT
#define HEIGHT 47
#endif
#ifndef WIDTH
#define WIDTH 67
#endif
int gamemap[HEIGHT][WIDTH];
void loadCSV(const char *filename);