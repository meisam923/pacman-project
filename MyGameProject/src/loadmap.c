#include "E:\MyGameProject\Headers\loadmap.h"
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
void loadCSV(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Unable to open file %s\n", filename);
        return;
    }

    char buffer[4096];
    int row = 0;

    while (fgets(buffer, sizeof(buffer), file) && row < HEIGHT) {
        int column = 0;
        char *value = strtok(buffer, ",");

        while (value) {
            if (column < WIDTH) {
                gamemap[row][column] = atoi(value);
                value = strtok(NULL, ",");
                column++;
            } else {
                break;
            }
        }
        row++;
    }
    fclose(file);
}