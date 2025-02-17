#include "E:\MyGameProject\include\raylib.h"
#ifndef HIGHT
#define HEIGHT 47
#endif
#ifndef WIDTH
#define WIDTH 67
#endif
#define MAX_SNOWFLAKES 100
typedef struct Snowflake {
    Vector2 position;
    float speed;
    float size;
} Snowflake;
int gamemap[HEIGHT][WIDTH];
void print(int second,int minute,int cnt,int board [47][67],int hardness,Snowflake snowflakes[MAX_SNOWFLAKES]);
void print_game_over_window(int board [47][67] ,double time,int cnt,char user_name[]);
#define MAX_SNOWFLAKES 100
void print_menu(int menu_position,Snowflake snowflakes[MAX_SNOWFLAKES]);
