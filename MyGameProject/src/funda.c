#include "include\raylib.h"
#include "Headers\funda.h"
struct pac
{
    double x;
    double y;
    int direction;
    int move;
    int armor;
    int star;
    int gilas_power;
    int pepper_power;
    int gilas_power_timer;
    int paper_power_time;
    Texture2D IMP_base;
    Texture2D IMP_right;
    Texture2D IMP_left;
    Texture2D IMP_up;
    Texture2D IMP_down;
    Texture2D star_IMG;
    Texture2D gilas_IMG;
    Texture2D pepper_IMG;
    Texture2D apple_IMG;
    Texture2D mushroom_IMG;
};
struct pac pacman={0,0,0,0,3,0,0,0,0};
struct ghost
{
    double x;
    double y;
    int direction;
    int hide;
    Texture2D IMG;
    int hide_timer;
};
struct ghost norm_ghosts[9];
struct ghost searcher[4];
int random_ghosts_position[7][4]={{1,40,3,0},{1,1,2,0},{65,1,4,0},{65,10,3,0},{30,40,3,0},{15,13,1,0},{32,25,4,0},{37,33,3,0},{27,38,1,0}};
