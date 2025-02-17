#include "include/raylib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "src/loadmap.c"
#include "src/print.c"
#include "Headers/funda.h"
#include <time.h>
#ifndef WIDTH
#define WIDTH 67
#endif
#ifndef HEIGHT
#define HEIGHT 47
#endif
#include <math.h>
#include <conio.h>
double elapsedtime=0.0;
double time_start=0;
int hardness=1;
Sound starmusic;
Sound fruitmusic;
Sound hitmusic;
Sound eatmusic;
void give_random_position_to_stars(int board[47][67],int arr_for_select_random[][2],int cnt_of_free_space)
{
    for (int i=0;i<47;i++)
    {
        for (int j=0;j<67;j++)
        {
            if (board[i][j]==2)
            return;
        }
    }
    srand((unsigned int)time(NULL));
    for (int i=0;i<10;i++)
    {
        while (1)
        {
            int rnd=rand()%cnt_of_free_space;
            int randx= arr_for_select_random[rnd][1];
            int randy= arr_for_select_random[rnd][0];
            if (board[randy][randx]==0)
            {
                board[randy][randx]=2;
                break;
            }

        }
    }
    return;
}
void give_random_position_to_fruits(int board[47][67],int f,int arr_for_select_random[][2],int cnt_of_free_space)
{
    for (int i=0;i<47;i++)
    {
        for (int j=0;j<67;j++)
        {
            if (board[i][j]==f)
            return;
        }
    }
    srand((unsigned int)time(NULL));
    for (int i=0;i<2;i++)
    {
        while (1)
        {
            int rnd=rand()%cnt_of_free_space;
            int randx= arr_for_select_random[rnd][1];
            int randy= arr_for_select_random[rnd][0];
            if (board[randy][randx]==0)
            {
                board[randy][randx]=f;
                break;
            }
        }
    }
    return;
}
int is_valid_move(double x, double y) {
    int left = (int)floor(x);
    int right = (int)ceil(x);
    int top = (int)floor(y);
    int bottom = (int)ceil(y);
    return (
            gamemap[top][left] == 0 &&
            gamemap[top][right] ==0 &&
            gamemap[bottom][left] == 0 &&
            gamemap[bottom][right] == 0 );
}
void pacman_movement(double advance)
{

    if (IsKeyDown(KEY_RIGHT)&&pacman.direction!=1)
    {
        if (is_valid_move(pacman.x+advance,pacman.y))
        {
            pacman.x+=advance;
            pacman.direction=1;
        }
    }
    else if (IsKeyDown(KEY_LEFT)&&pacman.direction!=3)
    {
        if (is_valid_move(pacman.x-advance,pacman.y))
        {
            pacman.x-=advance;
            pacman.direction=3;
        }
    }
    else if (IsKeyDown(KEY_UP)&&pacman.direction!=2)
    {
       if (is_valid_move(pacman.x,pacman.y-advance))
        {
            pacman.y-=advance;
            pacman.direction=2;
        }
    }
    else if (IsKeyDown(KEY_DOWN)&&pacman.direction!=4)
    {
        if (is_valid_move(pacman.x,pacman.y+advance))
        {
            pacman.y+=advance;
            pacman.direction=4;
        }
    }
        if (pacman.direction==1)
    {
        if (is_valid_move(pacman.x+advance,pacman.y))
        {
            pacman.x+=advance;
            pacman.direction=1;
        }
    }
    else if (pacman.direction==3)
    {
        if (is_valid_move(pacman.x-advance,pacman.y))
        {
            pacman.x-=advance;
            pacman.direction=3;
        }
    }
    else if (pacman.direction==2)
    {
       if (is_valid_move(pacman.x,pacman.y-advance))
        {
            pacman.y-=advance;
            pacman.direction=2;
        }
    }
    else if (pacman.direction==4)
    {
        if (is_valid_move(pacman.x,pacman.y+advance))
        {
            pacman.y+=advance;
            pacman.direction=4;
        }
    }
    return ;
}
void ghosts_movement(struct ghost *ghost, double advance) {
    int valid_directions[6] = {0}; 
    int count = 0; 

    if (is_valid_move(ghost->x + advance, ghost->y)) {
        valid_directions[count++] = 1;
    }
    if (is_valid_move(ghost->x, ghost->y - advance)) {
        valid_directions[count++] = 2;
    }
    if (is_valid_move(ghost->x - advance, ghost->y)) {
        valid_directions[count++] = 3;
    }
    if (is_valid_move(ghost->x, ghost->y + advance)) {
        valid_directions[count++] = 4;
    }
    if (count == 1) {
    switch (valid_directions[0]) {
        case 1: ghost->x += advance; ghost->direction = 1; break;
        case 2: ghost->y -= advance; ghost->direction = 2; break;
        case 3: ghost->x -= advance; ghost->direction = 3; break;
        case 4: ghost->y += advance; ghost->direction = 4; break;
    }
    return;
    count=0;
    }
    if (is_valid_move(ghost->x + advance, ghost->y) && (ghost->direction!=3)) {
        valid_directions[count++] = 1;
    }
    if (is_valid_move(ghost->x, ghost->y - advance)  && (ghost->direction!=4)) {
        valid_directions[count++] = 2;
    }
    if (is_valid_move(ghost->x - advance, ghost->y)  && (ghost->direction!=1)) {
        valid_directions[count++] = 3;
    }
    if (is_valid_move(ghost->x, ghost->y + advance)  && (ghost->direction!=2)) {
        valid_directions[count++] = 4;
    }
    if ((ghost->direction == 1 && is_valid_move(ghost->x + advance, ghost->y)) ||
        (ghost->direction == 2 && is_valid_move(ghost->x, ghost->y - advance)) ||
        (ghost->direction == 3 && is_valid_move(ghost->x - advance, ghost->y)) ||
        (ghost->direction == 4 && is_valid_move(ghost->x, ghost->y + advance))) {
        for (int i=0;i<2;i++)
        {
            valid_directions[count++] = ghost->direction;
        }
         
    }
    if ((ghost->direction == 1 && is_valid_move(ghost->x + advance, ghost->y)))
    {
        for (int i=0;i<6-count;i++)
        {
        valid_directions[count++] = 2;
        }
    }
    if ((ghost->direction == 2 && is_valid_move(ghost->x, ghost->y-advance)))
    {
        for (int i=0;i<6-count;i++)
        {
        valid_directions[count++] = 1;
        }
    }
    if ((ghost->direction == 3 && is_valid_move(ghost->x - advance, ghost->y)))
    {
        for (int i=0;i<6-count;i++)
        {
        valid_directions[count++] = 4;
        }
    }
    if ((ghost->direction == 4 && is_valid_move(ghost->x, ghost->y+advance)))
    {
        for (int i=0;i<6-count;i++)
        {
        valid_directions[count++] = 3;
        }
    }

    if (count == 0) {
        return;
    }
    srand((unsigned int)time(NULL));
    int rnd = rand() % count;
    switch (valid_directions[rnd]) {
        case 1:
            ghost->x += advance;
            ghost->direction = 1; 
            break;
        case 2:
            ghost->y -= advance;
            ghost->direction = 2;
            break;
        case 3:
            ghost->x -= advance;
            ghost->direction = 3;
            break;
        case 4:
            ghost->y += advance;
            ghost->direction = 4;
            break;
    }
}
void searcher_movement(struct ghost* ghost, double advance) {
    
    int valid_directions[14] = {0}; 
    int count = 0; 

    if (is_valid_move(ghost->x + advance, ghost->y)) {
        valid_directions[count++] = 1;
    }
    if (is_valid_move(ghost->x, ghost->y - advance)) {
        valid_directions[count++] = 2;
    }
    if (is_valid_move(ghost->x - advance, ghost->y)) {
        valid_directions[count++] = 3;
    }
    if (is_valid_move(ghost->x, ghost->y + advance)) {
        valid_directions[count++] = 4;
    }
    if (count == 1) {
    switch (valid_directions[0]) {
        case 1: ghost->x += advance; ghost->direction = 1; break;
        case 2: ghost->y -= advance; ghost->direction = 2; break;
        case 3: ghost->x -= advance; ghost->direction = 3; break;
        case 4: ghost->y += advance; ghost->direction = 4; break;
    }
    return;
    count=0;
    }
    double distance [4];

    if (is_valid_move(ghost->x + advance, ghost->y)) {
        valid_directions[count++] = 1;
        distance[0]=sqrt(pow(fabs(pacman.x-(ghost->x+advance)),2)+pow(fabs(pacman.y-ghost->y),2));
    }
    else
    distance[0]=INT_MAX;
    if (is_valid_move(ghost->x, ghost->y - advance)  && (ghost->direction!=4)) {
        valid_directions[count++] = 2;
        distance[1]=sqrt(pow(fabs(pacman.x-ghost->x),2)+pow(fabs(pacman.y-(ghost->y-advance)),2));
    }
    else
    distance[1]=INT_MAX;
    if (is_valid_move(ghost->x - advance, ghost->y)  && (ghost->direction!=1)) {
        valid_directions[count++] = 3;
        distance[2]=sqrt(pow(fabs(pacman.x-(ghost->x-advance)),2)+pow(fabs(pacman.y-ghost->y),2));
    }
    else
    distance[2]=INT_MAX;
    if (is_valid_move(ghost->x, ghost->y + advance)  && (ghost->direction!=2)) {
        valid_directions[count++] = 4;
        distance[3]=sqrt(pow(fabs(pacman.x-ghost->x),2)+pow(fabs(pacman.y-(ghost->y+advance)),2));
    }
    else
    distance[3]=INT_MAX;
    int index_comparing=0;
    double distance_comparing=distance[0];
    for (int i=1;i<4;i++)
    {
        if (distance[i]<=distance_comparing)
        {
            distance_comparing=distance[i];
            index_comparing=i;
        }
    }
    index_comparing++;
    if ((ghost->direction == 1 && is_valid_move(ghost->x + advance, ghost->y)))
    {
        for (int i=0;i<1;i++)
        {
        valid_directions[count++] = 1;
        }
    }
    if ((ghost->direction == 2 && is_valid_move(ghost->x, ghost->y-advance)))
    {
        for (int i=0;i<1;i++)
        {
        valid_directions[count++] = 2;
        }
    }
    if ((ghost->direction == 3 && is_valid_move(ghost->x - advance, ghost->y)))
    {
        for (int i=0;i<1;i++)
        {
        valid_directions[count++] = 3;
        }
    }
    if ((ghost->direction == 4 && is_valid_move(ghost->x, ghost->y+advance)))
    {
        for (int i=0;i<1;i++)
        {
        valid_directions[count++] = 4;
        }
    }
    if ((index_comparing == 1 && is_valid_move(ghost->x + advance, ghost->y)) ||
        (index_comparing == 2 && is_valid_move(ghost->x, ghost->y - advance)) ||
        (index_comparing == 3 && is_valid_move(ghost->x - advance, ghost->y)) ||
        (index_comparing == 4 && is_valid_move(ghost->x, ghost->y + advance))) {
        for (int i=0;i<14-count;i++)
        {
            valid_directions[count++] = index_comparing;
        }
         
    }
    if (count == 0) {
        return;
    }
    srand((unsigned int)time(NULL));
    int rnd = rand() % count;
    switch (valid_directions[rnd]) {
        case 1:
            ghost->x += advance;
            ghost->direction = 1; 
            break;
        case 2:
            ghost->y -= advance;
            ghost->direction = 2;
            break;
        case 3:
            ghost->x -= advance;
            ghost->direction = 3;
            break;
        case 4:
            ghost->y += advance;
            ghost->direction = 4;
            break;
    }
}
void check_for_hit_fruits(int p,int board[47][67])
{
if (p==2)
{
    if (board[(int)floor(pacman.y+.5)][(int)floor(pacman.x+1)]==2 && pacman.x+1!=floor(pacman.x+1))
    {
        board[(int)floor(pacman.y+.5)][(int)floor(pacman.x+1)]=0;
        pacman.star++;
        PlaySound(starmusic);
    }
    else if (board[(int)floor(pacman.y+.5)][(int)floor(pacman.x)]==2)
    {
        board[(int)floor(pacman.y+.5)][(int)floor(pacman.x)]=0;
        pacman.star++;
        PlaySound(starmusic);
    }
    else if (board[(int)floor(pacman.y)][(int)floor(pacman.x+.5)]==2)
    {
        board[(int)floor(pacman.y)][(int)floor(pacman.x+.5)]=0;
        pacman.star++;
        PlaySound(starmusic);
    }
    else if (board[(int)floor(pacman.y+1)][(int)floor(pacman.x+.5)]==2 && pacman.y+1!=floor(pacman.y+1))
    {
        board[(int)floor(pacman.y+1)][(int)floor(pacman.x+.5)]=0;
        pacman.star++;
        PlaySound(starmusic);
    }
    return;
}
else if (p==3)
{
    if (board[(int)floor(pacman.y+.5)][(int)floor(pacman.x+1)]==3 && pacman.x+1!=floor(pacman.x+1))
    {
        PlaySound(fruitmusic);
        board[(int)floor(pacman.y+.5)][(int)floor(pacman.x+1)]=0;
        pacman.gilas_power=1;
        pacman.gilas_power_timer=(int)elapsedtime+15;
    }
    else if (board[(int)floor(pacman.y+.5)][(int)floor(pacman.x)]==3)
    {
        PlaySound(fruitmusic);
        board[(int)floor(pacman.y+.5)][(int)floor(pacman.x)]=0;
        pacman.gilas_power=1;
        pacman.gilas_power_timer=(int)elapsedtime+15;
    }
    else if (board[(int)floor(pacman.y)][(int)floor(pacman.x+.5)]==3)
    {
        PlaySound(fruitmusic);
        board[(int)floor(pacman.y)][(int)floor(pacman.x+.5)]=0;
        pacman.gilas_power=1;
        pacman.gilas_power_timer=(int)elapsedtime+15;
    }
    else if (board[(int)floor(pacman.y+1)][(int)floor(pacman.x+.5)]==3 && pacman.y+1!=floor(pacman.y+1))
    {
        PlaySound(fruitmusic);
        board[(int)floor(pacman.y+1)][(int)floor(pacman.x+.5)]=0;
        pacman.gilas_power=1;
        pacman.gilas_power_timer=(int)elapsedtime+15;
    }
    return;
}
else if (p==4)
{
    if (board[(int)floor(pacman.y+.5)][(int)floor(pacman.x+1)]==4 && pacman.x+1!=floor(pacman.x+1))
    {
        PlaySound(fruitmusic);   
        board[(int)floor(pacman.y+.5)][(int)floor(pacman.x+1)]=0;
        pacman.armor++;
    }
    else if (board[(int)floor(pacman.y+.5)][(int)floor(pacman.x)]==4)
    {
        PlaySound(fruitmusic);
        board[(int)floor(pacman.y+.5)][(int)floor(pacman.x)]=0;
        pacman.armor++;
    }
    else if (board[(int)floor(pacman.y)][(int)floor(pacman.x+.5)]==4)
    {
        PlaySound(fruitmusic);
        board[(int)floor(pacman.y)][(int)floor(pacman.x+.5)]=0;
        pacman.armor++;
    }
    else if (board[(int)floor(pacman.y+1)][(int)floor(pacman.x+.5)]==4 && pacman.y+1!=floor(pacman.y+1))
    {
        PlaySound(fruitmusic);
        board[(int)floor(pacman.y+1)][(int)floor(pacman.x+.5)]=0;
        pacman.armor++;
    }
    return;
}
else if (p==5)
{
    if (board[(int)floor(pacman.y+.5)][(int)floor(pacman.x+1)]==5 && pacman.x+1!=floor(pacman.x+1))
    {
        PlaySound(fruitmusic);
        board[(int)floor(pacman.y+.5)][(int)floor(pacman.x+1)]=0;
        pacman.armor--;
    }
    else if (board[(int)floor(pacman.y+.5)][(int)floor(pacman.x)]==5)
    {
        PlaySound(fruitmusic);
        board[(int)floor(pacman.y+.5)][(int)floor(pacman.x)]=0;
        pacman.armor--;
    }
    else if (board[(int)floor(pacman.y)][(int)floor(pacman.x+.5)]==5)
    {
        PlaySound(fruitmusic);
        board[(int)floor(pacman.y)][(int)floor(pacman.x+.5)]=0;
        pacman.armor--;
    }
    else if (board[(int)floor(pacman.y+1)][(int)floor(pacman.x+.5)]==5 && pacman.y+1!=floor(pacman.y+1))
    {
        PlaySound(fruitmusic);
        board[(int)floor(pacman.y+1)][(int)floor(pacman.x+.5)]=0;
        pacman.armor--;
    }
    return;
}
else if (p==6)
{
    if (board[(int)floor(pacman.y+.5)][(int)floor(pacman.x+1)]==6 && pacman.x+1!=floor(pacman.x+1))
    {
        PlaySound(fruitmusic);
        board[(int)floor(pacman.y+.5)][(int)floor(pacman.x+1)]=0;
        pacman.pepper_power=1;
        pacman.paper_power_time=(int)elapsedtime+15;
        pacman.x=floor(pacman.x);
        pacman.y=floor(pacman.y);
    }
    else if (board[(int)floor(pacman.y+.5)][(int)floor(pacman.x)]==6)
    {
        PlaySound(fruitmusic);
        board[(int)floor(pacman.y+.5)][(int)floor(pacman.x)]=0;
        pacman.pepper_power=1;
        pacman.paper_power_time=(int)elapsedtime+15;
        pacman.x=floor(pacman.x);
        pacman.y=floor(pacman.y);
    }
    else if (board[(int)floor(pacman.y)][(int)floor(pacman.x+.5)]==6)
    {
        PlaySound(fruitmusic);
        board[(int)floor(pacman.y)][(int)floor(pacman.x+.5)]=0;
        pacman.pepper_power=1;
        pacman.paper_power_time=(int)elapsedtime+15;
        pacman.x=floor(pacman.x);
        pacman.y=floor(pacman.y);
    }
    else if (board[(int)floor(pacman.y+1)][(int)floor(pacman.x+.5)]==6 && pacman.y+1!=floor(pacman.y+1))
    {
        PlaySound(fruitmusic);
        board[(int)floor(pacman.y+1)][(int)floor(pacman.x+.5)]=0;
        pacman.pepper_power=1;
        pacman.paper_power_time=(int)elapsedtime+15;
        pacman.x=floor(pacman.x);
        pacman.y=floor(pacman.y);
    }
    return;
}
}
void check_pacman_ghosts_hit()
{
    if (hardness==1)
    {
    for (int i=0;i<7;i++)
    {
    if ((norm_ghosts[i].x<= pacman.x+.5 && pacman.x+.5<=norm_ghosts[i].x+1 && norm_ghosts[i].y<= pacman.y+.5 && pacman.y+.5<=norm_ghosts[i].y+1))
    {
        if (pacman.gilas_power)
        {
            PlaySound(eatmusic);
            norm_ghosts[i].hide=1;
            norm_ghosts[i].x=0;
            norm_ghosts[i].y=0;
            norm_ghosts[i].hide_timer=(int)elapsedtime+15;
        }
        else
        {
        PlaySound(hitmusic);
        pacman.armor--;
        if (pacman.direction==1)
        pacman.direction=3;
        else if (pacman.direction==2)
        pacman.direction=4;
        else if (pacman.direction==3)
        pacman.direction=1;
        else if (pacman.direction==4)
        pacman.direction=2;
        }
    }
    }
    for (int i=0;i<2;i++)
    {
    if ((searcher[i].x<= pacman.x+.5 && pacman.x+.5<=searcher[i].x+1 && searcher[i].y<= pacman.y+.5 && pacman.y+.5<=searcher[i].y+1))
    {
    if (pacman.gilas_power)
        {
            PlaySound(eatmusic);
            searcher[i].hide=1;
            searcher[i].x=0;
            searcher[i].y=0;
            searcher[i].hide_timer=(int)elapsedtime+15;
        }
        else
        {
        PlaySound(hitmusic);
        pacman.armor--;
        if (pacman.direction==1)
        pacman.direction=3;
        else if (pacman.direction==2)
        pacman.direction=4;
        else if (pacman.direction==3)
        pacman.direction=1;
        else if (pacman.direction==4)
        pacman.direction=2;
        }
    }
    }
    }
    else if (hardness==2)
    {
    for (int i=0;i<8;i++)
    {
    if ((norm_ghosts[i].x<= pacman.x+.5 && pacman.x+.5<=norm_ghosts[i].x+1 && norm_ghosts[i].y<= pacman.y+.5 && pacman.y+.5<=norm_ghosts[i].y+1))
    {
        if (pacman.gilas_power)
        {
            PlaySound(eatmusic);
            norm_ghosts[i].hide=1;
            norm_ghosts[i].x=0;
            norm_ghosts[i].y=0;
            norm_ghosts[i].hide_timer=(int)elapsedtime+15;
        }
        else
        {
        PlaySound(hitmusic);
        pacman.armor--;
        if (pacman.direction==1)
        pacman.direction=3;
        else if (pacman.direction==2)
        pacman.direction=4;
        else if (pacman.direction==3)
        pacman.direction=1;
        else if (pacman.direction==4)
        pacman.direction=2;
        }
    }
    }
    for (int i=0;i<3;i++)
    {
    if ((searcher[i].x<= pacman.x+.5 && pacman.x+.5<=searcher[i].x+1 && searcher[i].y<= pacman.y+.5 && pacman.y+.5<=searcher[i].y+1))
    {
    if (pacman.gilas_power)
        {
            PlaySound(eatmusic);
            searcher[i].hide=1;
            searcher[i].x=0;
            searcher[i].y=0;
            searcher[i].hide_timer=(int)elapsedtime+15;
        }
        else
        {
        PlaySound(hitmusic);
        pacman.armor--;
        if (pacman.direction==1)
        pacman.direction=3;
        else if (pacman.direction==2)
        pacman.direction=4;
        else if (pacman.direction==3)
        pacman.direction=1;
        else if (pacman.direction==4)
        pacman.direction=2;
        }
    }
    }
    }
    if (hardness==3)
    {
    for (int i=0;i<9;i++)
    {
    if ((norm_ghosts[i].x<= pacman.x+.5 && pacman.x+.5<=norm_ghosts[i].x+1 && norm_ghosts[i].y<= pacman.y+.5 && pacman.y+.5<=norm_ghosts[i].y+1))
    {
        if (pacman.gilas_power)
        {
            PlaySound(eatmusic);
            norm_ghosts[i].hide=1;
            norm_ghosts[i].x=0;
            norm_ghosts[i].y=0;
            norm_ghosts[i].hide_timer=(int)elapsedtime+15;
        }
        else
        {
        PlaySound(hitmusic);
        pacman.armor--;
        if (pacman.direction==1)
        pacman.direction=3;
        else if (pacman.direction==2)
        pacman.direction=4;
        else if (pacman.direction==3)
        pacman.direction=1;
        else if (pacman.direction==4)
        pacman.direction=2;
        }
    }
    }
    for (int i=0;i<4;i++)
    {
    if ((searcher[i].x<= pacman.x+.5 && pacman.x+.5<=searcher[i].x+1 && searcher[i].y<= pacman.y+.5 && pacman.y+.5<=searcher[i].y+1))
    {
    if (pacman.gilas_power)
        {
            PlaySound(eatmusic);
            searcher[i].hide=1;
            searcher[i].x=0;
            searcher[i].y=0;
            searcher[i].hide_timer=(int)elapsedtime+15;
        }
        else
        {
        PlaySound(hitmusic);
        pacman.armor--;
        if (pacman.direction==1)
        pacman.direction=3;
        else if (pacman.direction==2)
        pacman.direction=4;
        else if (pacman.direction==3)
        pacman.direction=1;
        else if (pacman.direction==4)
        pacman.direction=2;
        }
    }
    }
    }
    return;
}
struct node
{
    char name[50];
    int score;
    int time;
    char current_time[30];
    char current_date[30];
    struct node *next;
};
struct node * create (char name_[],int score_,int time_,char current_time_[],char current_date_[])
{
struct node *nn=(struct node *)malloc(sizeof(struct node));
strcpy(nn->name,name_);
strcpy(nn->current_time,current_time_);
strcpy(nn->current_date,current_date_);
nn->score=score_;
nn->time=time_;
nn->next=NULL;
return nn;
}
void add_end(struct node *list,struct node *new)
{
    struct node *current = list;
    while (current->next != NULL) 
    {
        current = current->next;
    }
    current->next = new;
    return;
}
int compare(struct node *a,struct node *b)
{
    if (a->score>b->score)
    return 1;
    else if (a->score==b->score && a->time<b->time)
    return 1;
    else
    return 0;
}
void swap(struct node *a,struct node *b)
{
    char name_tmp[50];
    int score_tmp;
    int time_tmp;
    char current_time_tmp[30];
    char current_date_tmp[30];
    strcpy(name_tmp,a->name);
    strcpy(a->name,b->name);
    strcpy(b->name,name_tmp);
    strcpy(current_time_tmp,a->current_time);
    strcpy(a->current_time,b->current_time);
    strcpy(b->current_time,current_time_tmp);
    strcpy(current_date_tmp,a->current_date);
    strcpy(a->current_date,b->current_date);
    strcpy(b->current_date,current_date_tmp);
    score_tmp=a->score;
    a->score=b->score;
    b->score=score_tmp;
    time_tmp=a->time;
    a->time=b->time;
    b->time=time_tmp;
    return;
}
void sort_records(struct node *list)
{
    struct node *current=list;
    while(current->next!=NULL)
    {
        struct node *current_2=current->next;
        while(current_2!=NULL)
        {
            if (compare(current_2,current))
            swap(current,current_2);
            current_2=current_2->next;
        }
        current=current->next;
    }
    FILE *fp=fopen("RECORDS.txt","w+");
    if (fp==NULL)
    {
        printf("ERROR FROM SORT FUNCTION\n");
    }
    current=list;
    int cnt=0;
    while (current!=NULL && cnt<10)
    {
        struct node *cur=current;
        fprintf(fp,"%s\n",current->name);
        fprintf(fp,"%d %d\n",current->score,current->time);
        fprintf(fp,"%s\n", current->current_time);
        fprintf(fp,"%s\n", current->current_date);
        current=current->next;
        free(cur);
        cnt++;
    }
    fclose(fp);
}
void read_data_from_file()
{
    FILE *fp=fopen("RECORDS.txt","r");
    if (fp==NULL)
    {
        printf("ERROR FROM READDATAFROMFILE\n");
    }
    struct node *list=NULL;
    int i=0;
    while (1)
    {
        char name[50];
        char current_time[30];
        char current_date[30];
        int score,time;
        if (fgets(name,60,fp)==NULL)
        {
            break;
        }
        name[strcspn(name, "\n")] = '\0';
        fscanf(fp,"%d %d\n",&score,&time);
        if (fgets(current_time,40,fp)==NULL)
        {
            break;
        }
        current_time[strcspn(current_time, "\n")] = '\0';
        if (fgets(current_date,40,fp)==NULL)
        {
            break;
        }
        current_date[strcspn(current_date, "\n")] = '\0';
        if (i==0)
        {
            list=create(name,score,time,current_time,current_date);
        }
        else
        {   
            struct node * new;
            new=create(name,score,time,current_time,current_date);
            add_end(list,new);
        }
        i++;
    }
    sort_records(list);
    fclose (fp);
    return ;
}
int main()
{
InitAudioDevice();
Music background_music=LoadMusicStream("assets\\music.mp3");
hitmusic=LoadSound("assets\\hit.wav");
starmusic=LoadSound("assets\\starmusic.wav");
fruitmusic=LoadSound("\\fruitmusic.wav");
eatmusic=LoadSound("assets\\eat.wav");
InitWindow(WIDTH*36,HEIGHT*34, "pacman");
SetTargetFPS(60);
int menu_position=0;
Snowflake snowflakes[MAX_SNOWFLAKES];
for (int i = 0; i < MAX_SNOWFLAKES; i++) {
    snowflakes[i].position = (Vector2){ (float)GetRandomValue(0, 36*67), (float)GetRandomValue(0, 34*47) };
    snowflakes[i].speed = (float)GetRandomValue(1, 3);
    snowflakes[i].size = (float)GetRandomValue(1, 3);
}
PlayMusicStream(background_music);
while(!WindowShouldClose())
{
    UpdateMusicStream(background_music);
    if (!IsMusicStreamPlaying(background_music)) {
    PlayMusicStream(background_music);
    }
    UpdateSnowflakes(snowflakes, MAX_SNOWFLAKES, 36*67, 34*47);
    print_menu(menu_position,snowflakes);
    if (IsKeyPressed(KEY_DOWN))
    {
        menu_position=(menu_position+1)%5;
    }
    else if (IsKeyPressed(KEY_UP))
    {
        menu_position=(menu_position+4)%5;
    }
    else if (IsKeyPressed(KEY_ENTER))
    {
    if (menu_position==0)
    {
    pacman.star=0;
    pacman.armor=3;
    pacman.gilas_power=0;
    pacman.pepper_power=0;
    elapsedtime=0;
    char user_name[51]="\0";
    int letterCount = 0;
    bool back=false;
    int entering_name_pos=-1;
    while (!WindowShouldClose()) {
    UpdateMusicStream(background_music);
    if (!IsMusicStreamPlaying(background_music)) {
    PlayMusicStream(background_music);
    }
        if (IsKeyPressed(KEY_DOWN))
    {
        entering_name_pos=(entering_name_pos+1)%3;
    }
    else if (IsKeyPressed(KEY_UP))
    {
        entering_name_pos=(entering_name_pos+2)%3;
    }
    if (entering_name_pos==0)
    {
            if (letterCount < 50) {
                int key = GetCharPressed();
                while (key > 0) {
                    if ((key >= 32) && (key <= 125)) {
                        user_name[letterCount] = (char)key;
                        user_name[letterCount + 1] = '\0';
                        letterCount++;
                    }
                    key = GetCharPressed(); 
                }
            }

            if (IsKeyPressed(KEY_BACKSPACE)) {
                if (letterCount > 0) {
                    letterCount--;
                    user_name[letterCount] = '\0';
                }
            }
    }
        BeginDrawing();
        ClearBackground(DARK_BG);
        double fontSize = 35 + 20 * sin(GetTime() * 3); 
        DrawText("P",33*32,2,(int)fontSize,RED);
        DrawText("A",34*32,2,(int)fontSize,BLUE);
        DrawText("C",35*32,2,(int)fontSize,YELLOW);
        DrawText("-",36*32,2,(int)fontSize,SKYBLUE);
        DrawText("M",37*32,2,(int)fontSize,DARKGREEN);
        DrawText("A",38*32,2,(int)fontSize,PURPLE);
        DrawText("N",39*32,2,(int)fontSize,ORANGE);
        DrawText("Enter Player Name:", 26.5*32, 14*32, 70, SILVER);
        if (entering_name_pos==0)
        {
        DrawRectangle(26.5*32,(17)*32,32*25,64,SILVER);
            if (letterCount==0)
            {
                DrawText("ENTER YOR NAMR HERE",28*32,(17.5)*32,40,DARKGRAY);
            }
        DrawText(user_name, 28*32, 17*32, 60, LIME);
        DrawText("CONFIRM", 26.5*32,20*32, 40, OLIVE);
        DrawText("BACK", 26.5*32,23*32, 40, OLIVE);
        }
        else if (entering_name_pos==-1)
        {
            DrawText("PRESS ARROW KEYS TO ENTER NAME", 26.5*32,19*32, 40, SILVER);
        }
        else
        {
            if (entering_name_pos==1)
            {
            DrawRectangle(26.5*32,(17)*32,32*25,64,DARKGRAY);
            DrawText(">> CONFIRM <<", 26.5*32,20*32, 40, TEAL);
            DrawText("BACK", 26.5*32,23*32, 40, OLIVE);
            }
            if (entering_name_pos==2)
            {
            DrawRectangle(26.5*32,(17)*32,32*25,64,DARKGRAY);
            DrawText("CONFIRM", 26.5*32,20*32, 40, OLIVE);
            DrawText(">> BACK <<", 26.5*32,23*32, 40, TEAL);
            }
            DrawText(user_name, 28*32, 17*32, 60, SILVER);
            if (IsKeyPressed(KEY_ENTER))
            {
                if (entering_name_pos==1)
                {
                    break;
                }
                if (entering_name_pos==2)
                {
                    back=true;
                    break;
                }
            }
        }
        
        UpdateSnowflakes(snowflakes, MAX_SNOWFLAKES, 36*67, 34*47);
        DrawSnowflakes(snowflakes, MAX_SNOWFLAKES);
        EndDrawing();
    }
    if (back)
    {
        continue;
    }
        Music background_game_music=LoadMusicStream("assets\\music2.mp3");
        Sound gameover=LoadSound("assets\\gameover.wav");
        PlayMusicStream(background_music);
        pacman.x=1;
        pacman.y=45;
        pacman.direction=0;
        pacman.armor=3;
        searcher[0].x=65;
        searcher[0].y=15;
        searcher[0].direction=4;
        searcher[1].x=34;
        searcher[1].y=7;
        searcher[1].direction=4;
        searcher[2].x=32;
        searcher[2].y=40;
        searcher[2].direction=2;
        searcher[3].x=5;
        searcher[3].y=1;
        searcher[3].direction=3;
        random_ghosts_position[0][0]=1;
        random_ghosts_position[0][1]=40;
        random_ghosts_position[0][2]=3;
        random_ghosts_position[1][0]=1;
        random_ghosts_position[1][1]=1;
        random_ghosts_position[1][2]=2;
        random_ghosts_position[2][0]=65;
        random_ghosts_position[2][1]=1;
        random_ghosts_position[2][2]=4;
        random_ghosts_position[3][0]=65;
        random_ghosts_position[3][1]=10;
        random_ghosts_position[3][2]=3;
        random_ghosts_position[4][0]=30;
        random_ghosts_position[4][1]=40;
        random_ghosts_position[4][2]=3;
        random_ghosts_position[5][0]=15;
        random_ghosts_position[5][1]=13;
        random_ghosts_position[5][2]=1;
        random_ghosts_position[6][0]=32;
        random_ghosts_position[6][1]=25;
        random_ghosts_position[6][2]=4;
        random_ghosts_position[7][0]=37;
        random_ghosts_position[7][1]=34;
        random_ghosts_position[7][2]=3;
        random_ghosts_position[8][0]=27;
        random_ghosts_position[8][1]=36;
        random_ghosts_position[8][2]=1;
        pacman.IMP_base=LoadTexture("assets\\pacman_base.png");
        pacman.IMP_right=LoadTexture("assets\\pacman_right.png");
        pacman.IMP_left=LoadTexture("assets\\pacman_left.png");
        pacman.IMP_up=LoadTexture("assets\\pacman_up.png");
        pacman.IMP_down=LoadTexture("assets\\pacman_down.png");
        norm_ghosts[0].IMG=LoadTexture("assets\\ghost1.png");
        norm_ghosts[1].IMG=LoadTexture("assets\\ghost2.png");
        norm_ghosts[2].IMG=LoadTexture("assets\\ghost3.png");
        norm_ghosts[3].IMG=LoadTexture("assets\\ghost4.png");
        norm_ghosts[4].IMG=LoadTexture("assets\\ghost5.png");
        norm_ghosts[5].IMG=LoadTexture("assets\\ghost6.png");
        norm_ghosts[6].IMG=LoadTexture("assets\\ghost7.png");
        norm_ghosts[7].IMG=LoadTexture("assets\\ghost10.png");
        norm_ghosts[8].IMG=LoadTexture("assets\\ghost13.png");
        searcher[0].IMG=LoadTexture("assets\\ghost8.png");
        searcher[1].IMG=LoadTexture("assets\\ghost9.png");
        searcher[2].IMG=LoadTexture("assets\\ghost11.png");
        searcher[3].IMG=LoadTexture("assets\\ghost12.png");
        pacman.star_IMG=LoadTexture("assets\\star.png");
        pacman.gilas_IMG=LoadTexture("assets\\gilas.png");
        pacman.apple_IMG=LoadTexture("assets\\apple.png");
        pacman.pepper_IMG=LoadTexture("assets\\pepper.png");
        pacman.mushroom_IMG=LoadTexture("assets\\mushroom.png");
        if (hardness==1)
        {
        for (int i=0;i<7;i++)
        {
            while (1)
            {
                srand((unsigned int)time(NULL));
                int rnd=rand()%9;
                if (random_ghosts_position[rnd][3]==0)
                {
                norm_ghosts[i].x=random_ghosts_position[rnd][0];
                norm_ghosts[i].y=random_ghosts_position[rnd][1];
                norm_ghosts[i].direction=random_ghosts_position[rnd][2];
                random_ghosts_position[rnd][3]=1;
                break;
                }
            }
        }
        }
        if (hardness==2)
        {
        for (int i=0;i<8;i++)
        {
            while (1)
            {
                srand((unsigned int)time(NULL));
                int rnd=rand()%9;
                if (random_ghosts_position[rnd][3]==0)
                {
                norm_ghosts[i].x=random_ghosts_position[rnd][0];
                norm_ghosts[i].y=random_ghosts_position[rnd][1];
                norm_ghosts[i].direction=random_ghosts_position[rnd][2];
                random_ghosts_position[rnd][3]=1;
                break;
                }
            }
        }
        }
        if (hardness==3)
        {
        for (int i=0;i<9;i++)
        {
            while (1)
            {
                srand((unsigned int)time(NULL));
                int rnd=rand()%9;
                if (random_ghosts_position[rnd][3]==0)
                {
                norm_ghosts[i].x=random_ghosts_position[rnd][0];
                norm_ghosts[i].y=random_ghosts_position[rnd][1];
                norm_ghosts[i].direction=random_ghosts_position[rnd][2];
                random_ghosts_position[rnd][3]=1;
                break;
                }
            }
        }
        }
        for (int i=0;i<9;i++)
        {
            random_ghosts_position[i][3]=0;
        }
        int cnt_of_free_space=0;
        loadCSV("assets\\maze1.csv");
        int board [47][67];
        for (int i=0;i<47;i++)
        {
            for (int j=0;j<67;j++)
            {
                board[i][j]=gamemap[i][j];
                if (gamemap[i][j]==0)
                cnt_of_free_space++;
            }
        }
        int arr_for_select_random[cnt_of_free_space][2];
        for (int i=0,cnt=0;i<47;i++)
        {
            for (int j=0;j<67;j++)
            {
                if (gamemap[i][j]==0)
                {
                    arr_for_select_random[cnt][0]=i;
                    arr_for_select_random[cnt][1]=j;
                    cnt++;
                }
                
            }
        }
        time_t now;
        struct tm *local;
        time(&now);
        local = localtime(&now);
        int cnt=0;
        time_start=GetTime();
        while (!WindowShouldClose() && pacman.armor>0)
        {
            give_random_position_to_stars(board,arr_for_select_random,cnt_of_free_space);
            give_random_position_to_fruits(board,3,arr_for_select_random,cnt_of_free_space);
            give_random_position_to_fruits(board,4,arr_for_select_random,cnt_of_free_space);
            give_random_position_to_fruits(board,5,arr_for_select_random,cnt_of_free_space);
            give_random_position_to_fruits(board,6,arr_for_select_random,cnt_of_free_space);
            if (pacman.gilas_power && pacman.gilas_power_timer==(int)elapsedtime)
            {
                pacman.gilas_power=0;
                pacman.gilas_power_timer=0;
            }
            if (pacman.pepper_power && pacman.paper_power_time==(int)elapsedtime)
            {
                pacman.pepper_power=0;
                pacman.paper_power_time=0;
                pacman.x=floor(pacman.x);
                pacman.y=floor(pacman.y);
            }
            if (hardness==1)
            {
            for (int i=0;i<7;i++)
            {
                if (norm_ghosts[i].hide && norm_ghosts[i].hide_timer==(int)elapsedtime)
                {
                    norm_ghosts[i].hide=0;
                    norm_ghosts[i].hide_timer=0;
                    srand((unsigned int)time(0));
                    int rnd=rand()%9;
                    norm_ghosts[i].x=random_ghosts_position[rnd][0];
                    norm_ghosts[i].y=random_ghosts_position[rnd][1];
                    norm_ghosts[i].direction=random_ghosts_position[rnd][2];   
                }
            }
            }
            else if (hardness==2)
            {
            for (int i=0;i<8;i++)
            {
                if (norm_ghosts[i].hide && norm_ghosts[i].hide_timer==(int)elapsedtime)
                {
                    norm_ghosts[i].hide=0;
                    norm_ghosts[i].hide_timer=0;
                    srand((unsigned int)time(0));
                    int rnd=rand()%9;
                    norm_ghosts[i].x=random_ghosts_position[rnd][0];
                    norm_ghosts[i].y=random_ghosts_position[rnd][1];
                    norm_ghosts[i].direction=random_ghosts_position[rnd][2];   
                }
            }
            }
            else if (hardness==3)
            {
            for (int i=0;i<9;i++)
            {
                if (norm_ghosts[i].hide && norm_ghosts[i].hide_timer==(int)elapsedtime)
                {
                    norm_ghosts[i].hide=0;
                    norm_ghosts[i].hide_timer=0;
                    srand((unsigned int)time(0));
                    int rnd=rand()%9;
                    norm_ghosts[i].x=random_ghosts_position[rnd][0];
                    norm_ghosts[i].y=random_ghosts_position[rnd][1];
                    norm_ghosts[i].direction=random_ghosts_position[rnd][2];   
                }
            }
            }
            if (hardness==1)
            for (int i=0;i<2;i++)
            {
                if (searcher[i].hide && searcher[i].hide_timer==(int)elapsedtime)
                {
                    searcher[i].hide=0;
                    searcher[i].hide_timer=0;
                    srand((unsigned int)time(0));
                    int rnd=rand()%9;
                    searcher[i].x=random_ghosts_position[rnd][0];
                    searcher[i].y=random_ghosts_position[rnd][1];
                    searcher[i].direction=random_ghosts_position[rnd][2];
                }
            }
            if (hardness==2)
            for (int i=0;i<3;i++)
            {
                if (searcher[i].hide && searcher[i].hide_timer==(int)elapsedtime)
                {
                    searcher[i].hide=0;
                    searcher[i].hide_timer=0;
                    srand((unsigned int)time(0));
                    int rnd=rand()%9;
                    searcher[i].x=random_ghosts_position[rnd][0];
                    searcher[i].y=random_ghosts_position[rnd][1];
                    searcher[i].direction=random_ghosts_position[rnd][2];
                }
            }
            if (hardness==3)
            for (int i=0;i<4;i++)
            {
                if (searcher[i].hide && searcher[i].hide_timer==(int)elapsedtime)
                {
                    searcher[i].hide=0;
                    searcher[i].hide_timer=0;
                    srand((unsigned int)time(0));
                    int rnd=rand()%9;
                    searcher[i].x=random_ghosts_position[rnd][0];
                    searcher[i].y=random_ghosts_position[rnd][1];
                    searcher[i].direction=random_ghosts_position[rnd][2];
                }
            }
            if (cnt==2)
            cnt=0;
            if (pacman.pepper_power)
            {
            pacman_movement(.5);
            check_pacman_ghosts_hit();
            check_for_hit_fruits(2,board);
            check_for_hit_fruits(3,board);
            check_for_hit_fruits(4,board);
            check_for_hit_fruits(5,board);
            check_for_hit_fruits(6,board);
            elapsedtime=GetTime()-time_start;
            }
            pacman_movement(.5);
            check_pacman_ghosts_hit();
            check_for_hit_fruits(2,board);
            check_for_hit_fruits(3,board);
            check_for_hit_fruits(4,board);
            check_for_hit_fruits(5,board);
            check_for_hit_fruits(6,board);
            elapsedtime=GetTime()-time_start;
            if (hardness==1)
            {
            for (int i=0;i<7;i++)
            {
                if (!norm_ghosts[i].hide)
                ghosts_movement(&norm_ghosts[i],.25);
            }
            }
            if (hardness==2)
            {
            for (int i=0;i<8;i++)
            {
                if (!norm_ghosts[i].hide)
                ghosts_movement(&norm_ghosts[i],.25);
            }
            }
            if (hardness==3)
            {
            for (int i=0;i<9;i++)
            {
                if (!norm_ghosts[i].hide)
                ghosts_movement(&norm_ghosts[i],.25);
            }
            }
            if (hardness==1)
            {
            for (int i=0;i<2;i++)
            {
            if (!searcher[i].hide)
            searcher_movement(&searcher[i],.25);
            }
            }
            if (hardness==2)
            {
            for (int i=0;i<3;i++)
            {
            if (!searcher[i].hide)
            searcher_movement(&searcher[i],.25);
            }
            }
            if (hardness==3)
            {
            for (int i=0;i<4;i++)
            {
            if (!searcher[i].hide)
            searcher_movement(&searcher[i],.25);
            }
            }
            int second=(int)elapsedtime % 60;
            int minute=(int)elapsedtime /60;
            UpdateSnowflakes(snowflakes, MAX_SNOWFLAKES, 36*67, 34*47);
            print(minute,second,cnt,board,hardness,snowflakes);
            double start_wait_time=GetTime();
            while (GetTime()-start_wait_time<.065)
            {
            UpdateMusicStream(background_game_music);
            if (!IsMusicStreamPlaying(background_game_music)) {
            PlayMusicStream(background_game_music);
            }
            }
            cnt++;
        }
        UnloadTexture(pacman.IMP_down);
        UnloadTexture(pacman.IMP_left);
        UnloadTexture(pacman.IMP_right);
        UnloadTexture(pacman.IMP_up);
        UnloadTexture(pacman.apple_IMG);
        UnloadTexture(pacman.gilas_IMG);
        UnloadTexture(pacman.mushroom_IMG);
        UnloadTexture(pacman.star_IMG);
        UnloadTexture(pacman.pepper_IMG);
        UnloadTexture(norm_ghosts[0].IMG);
        UnloadTexture(norm_ghosts[1].IMG);
        UnloadTexture(norm_ghosts[2].IMG);
        UnloadTexture(norm_ghosts[3].IMG);
        UnloadTexture(norm_ghosts[4].IMG);
        UnloadTexture(norm_ghosts[5].IMG);
        UnloadTexture(norm_ghosts[6].IMG);
        UnloadTexture(norm_ghosts[7].IMG);
        UnloadTexture(norm_ghosts[8].IMG);
        UnloadTexture(searcher[0].IMG);
        UnloadTexture(searcher[1].IMG);
        UnloadTexture(searcher[2].IMG);
        UnloadTexture(searcher[3].IMG);
        FILE *fp=fopen("RECORDS.txt","a");
        fprintf(fp,"%s\n",user_name);
        fprintf(fp,"%d %d\n",pacman.star,(int)elapsedtime);
        fprintf(fp,"Time: %02d:%02d:%02d\n", local->tm_hour, local->tm_min, local->tm_sec);
        fprintf(fp,"Date: %02d-%02d-%d\n", local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);
        fclose(fp);
        read_data_from_file();
        int cnt_for_gameover_text_moving=25;
        PlaySound(gameover);
        while (!WindowShouldClose())
        {
        if (cnt_for_gameover_text_moving==35)
        cnt_for_gameover_text_moving=25;
        print_game_over_window(board,elapsedtime,cnt_for_gameover_text_moving,user_name);
        cnt_for_gameover_text_moving++;
        if (IsKeyPressed(KEY_ENTER))
        break;
        }
}
else if (menu_position==2)
{
    int hardness_pos=-1;
    while (!WindowShouldClose())
    {
    UpdateMusicStream(background_music);
    if (!IsMusicStreamPlaying(background_music))
    {
    PlayMusicStream(background_music);
    }
    if (IsKeyPressed(KEY_DOWN))
    {
        hardness_pos=(hardness_pos+1)%3;
    }
    else if (IsKeyPressed(KEY_UP))
    {
        hardness_pos=(hardness_pos+2)%3;
    }
    else if (IsKeyPressed(KEY_ENTER))
    {
        if (hardness_pos>=0)
        {
        hardness=hardness_pos+1;
        menu_position=0;
        break;
        }
    }
    BeginDrawing();
    ClearBackground(DARK_BG);
    UpdateSnowflakes(snowflakes, MAX_SNOWFLAKES, 36*67, 34*47);
    DrawSnowflakes(snowflakes, MAX_SNOWFLAKES);
    double fontSize = 35 + 20 * sin(GetTime() * 3); 
    DrawText("P",33*32,2,(int)fontSize,RED);
    DrawText("A",34*32,2,(int)fontSize,BLUE);
    DrawText("C",35*32,2,(int)fontSize,YELLOW);
    DrawText("-",36*32,2,(int)fontSize,SKYBLUE);
    DrawText("M",37*32,2,(int)fontSize,DARKGREEN);
    DrawText("A",38*32,2,(int)fontSize,PURPLE);
    DrawText("N",39*32,2,(int)fontSize,ORANGE);   
    DrawText("CHOOSE HARDNESS",26.5*32,11*32,60,OLIVE);
    DrawText("PRESS ENTER TO CONFIRM HARDNESS",19*32,29*32,60,SILVER);
    if (hardness_pos==0)
    {
    DrawText(">> EASY <<",30*32,16*32,50,TEAL);
    DrawText("MEDIUM",32*32,19*32,50,OLIVE);
    DrawText("HARD",32*32,22*32,50,OLIVE);
    }
    if (hardness_pos==1)
    {
    DrawText("EASY",32*32,16*32,50,OLIVE);
    DrawText(">> MEDIUM <<",30*32,19*32,50,TEAL);
    DrawText("HARD",32*32,22*32,50,OLIVE);
    }
    if (hardness_pos==2)
    {
    DrawText("EASY",32*32,16*32,50,OLIVE);
    DrawText("MEDIUM",32*32,19*32,50,OLIVE);
    DrawText(">> HARD <<",30*32,22*32,50,TEAL);
    }
    else if (hardness_pos==-1)
    {
    DrawText("EASY",32*32,16*32,50,OLIVE);
    DrawText("MEDIUM",32*32,19*32,50,OLIVE);
    DrawText("HARD",32*32,22*32,50,OLIVE);
    DrawText("PRESS ARROW KEYS TO SELECT",27*32,14*32,40,SILVER);
    }
    EndDrawing();
    }
}
else if (menu_position==1)
{
    struct node *list=NULL;
    FILE *fp=fopen("RECORDS.txt","r");
    int i=0;
    while (1)
    {
        char name[50];
        char current_time[30];
        char current_date[30];
        int score,time;
        if (fgets(name,60,fp)==NULL)
        {
            break;
        }
        name[strcspn(name, "\n")] = '\0';
        fscanf(fp,"%d %d\n",&score,&time);
        if (fgets(current_time,40,fp)==NULL)
        {
            break;
        }
        current_time[strcspn(current_time, "\n")] = '\0';
        if (fgets(current_date,40,fp)==NULL)
        {
            break;
        }
        current_date[strcspn(current_date, "\n")] = '\0';
        if (i==0)
        {
            list=create(name,score,time,current_time,current_date);
        }
        else
        {   
            struct node * new;
            new=create(name,score,time,current_time,current_date);
            add_end(list,new);
        }
        i++;
    }
    fclose (fp);
    int record_pos=-1;
    while(!WindowShouldClose())
    {
    UpdateMusicStream(background_music);
    if (!IsMusicStreamPlaying(background_music)) {
    PlayMusicStream(background_music);
    }
        if (IsKeyPressed(KEY_DOWN))
        {
            record_pos=(record_pos+1)%2;
        }
        else if (IsKeyPressed(KEY_UP))
        {
            record_pos=(record_pos+1)%2;
        }
        BeginDrawing();
        ClearBackground(DARK_BG);
        double fontSize = 35 + 20 * sin(GetTime() * 3); 
        DrawText("P",33*32,2,(int)fontSize,RED);
        DrawText("A",34*32,2,(int)fontSize,BLUE);
        DrawText("C",35*32,2,(int)fontSize,YELLOW);
        DrawText("-",36*32,2,(int)fontSize,SKYBLUE);
        DrawText("M",37*32,2,(int)fontSize,DARKGREEN);
        DrawText("A",38*32,2,(int)fontSize,PURPLE);
        DrawText("N",39*32,2,(int)fontSize,ORANGE); 
        DrawText("NAME",3*32,2*32,40,SILVER);
        DrawText("SCORE",17*32,2*32,40,SILVER);
        DrawText("DURATION",23*32,2*32,32,SILVER);
        DrawText("TIME",31*32,2*32,40,SILVER);
        DrawText("DATE",38*32,2*32,40,SILVER);  
        struct node*cur=list;
        for (int j=0;j<i;j++)
        {
            char number[10];
            char score[10];
            char time[20];
            int second=cur->time%60;
            int minute=cur->time/60;
            sprintf(score,"%d",cur->score);
            sprintf(time,"%.2d:%.2d",minute,second);
            sprintf(number,"%d ",j+1);
            DrawText(number,1*32,(j+1)*4*32,30,RAYWHITE);
            if (j==0)
            {
                DrawText(cur->name,3*32,(j+1)*4*32,30,GOLD);
            }
            else if (j==1)
            {
                DrawText(cur->name,3*32,(j+1)*4*32,30,SILVER);
            }
            else if (j==2)
            {
                DrawText(cur->name,3*32,(j+1)*4*32,30,CORAL);
            }
            else
            {
            DrawText(cur->name,3*32,(j+1)*4*32,30,RAYWHITE);
            }
            DrawText(score,17*32,(j+1)*4*32,30,RAYWHITE);
            DrawText(time,23*32,(j+1)*4*32,30,RAYWHITE);
            DrawText(cur->current_time,29*32,(j+1)*4*32,30,RAYWHITE);
            DrawText(cur->current_date,38*32,(j+1)*4*32,30,RAYWHITE);
            cur=cur->next;
        }
        if (record_pos==0)
        {
            DrawText(">> WATCHING <<",28*32,(4*i+1)*32+16,40,TEAL);
            DrawText("BACK",28*32,(4*i+3)*32,40,OLIVE);
        }
        else if (record_pos==1)
        {
            DrawText("WATCHING",28*32,(4*i+1)*32+16,40,OLIVE);
            DrawText(">> BACK <<",28*32,(4*i+3)*32,40,TEAL);
            DrawText("PRESS ENTER TO BACK",28*32,(4*i+4)*32+16,40,SILVER);

        }
        else if (record_pos==-1)
        {
            DrawText("WATCHING",28*32,(4*i+1)*32+16,40,OLIVE);
            DrawText("BACK",28*32,(4*i+3)*32,40,OLIVE);
            DrawText("PRESS ARROW KEYS TO BACK",28*32,(4*i+4)*32+16,30,SILVER);
        }
        UpdateSnowflakes(snowflakes, MAX_SNOWFLAKES, 36*67, 34*47);
        DrawSnowflakes(snowflakes, MAX_SNOWFLAKES);
        if (IsKeyPressed(KEY_ENTER))
        {
            if (record_pos==1)
            {
            cur=list;
            struct node *tmp;
            while(cur!=NULL)
            {
                tmp=cur;
                cur=cur->next;
                free(tmp);
            }
            break;
            }
        }
        EndDrawing();
    }
}
else if (menu_position==4)
{
    int exit_pos=-1;
    while(!WindowShouldClose())
    {
    UpdateMusicStream(background_music);
    if (!IsMusicStreamPlaying(background_music)) {
    PlayMusicStream(background_music);
    }
        if (IsKeyPressed(KEY_DOWN))
        {
            exit_pos=(exit_pos+1)%2;
        }
        else if (IsKeyPressed(KEY_UP))
        {
            exit_pos=(exit_pos+1)%2;
        }
        BeginDrawing();
        ClearBackground(DARK_BG);
        double fontSize = 35 + 20 * sin(GetTime() * 3); 
        DrawText("P",33*32,2,(int)fontSize,RED);
        DrawText("A",34*32,2,(int)fontSize,BLUE);
        DrawText("C",35*32,2,(int)fontSize,YELLOW);
        DrawText("-",36*32,2,(int)fontSize,SKYBLUE);
        DrawText("M",37*32,2,(int)fontSize,DARKGREEN);
        DrawText("A",38*32,2,(int)fontSize,PURPLE);
        DrawText("N",39*32,2,(int)fontSize,ORANGE); 
        DrawText("EXIT",32*32,16*32,40,OLIVE);
        if (exit_pos==0)
        {
            DrawText(">> NO <<",32*32,20*32,40,TEAL);
            DrawText("YES",32*32,23*32,40,OLIVE);
        }
        else if (exit_pos==1)
        {
            DrawText("NO",32*32,20*32,40,OLIVE);
            DrawText(">> YES <<",32*32,23*32,40,TEAL);
        }
        else if (exit_pos==-1)
        {
            DrawText("PRESS ARROW KEYS TO EXIT",32*32,20*32,40,SILVER);
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            if (exit_pos==1)
            {
                exit(1);
            }
            else if (exit_pos==0)
            {
                break;
            }
        }
        UpdateSnowflakes(snowflakes, MAX_SNOWFLAKES, 36*67, 34*47);
        DrawSnowflakes(snowflakes, MAX_SNOWFLAKES);
        EndDrawing();
    }
}
else if (menu_position==3)
{
    int about_us_pos=-1;
    while (!WindowShouldClose())
    {
    UpdateMusicStream(background_music);
    if (!IsMusicStreamPlaying(background_music)) {
    PlayMusicStream(background_music);
    }
        if (IsKeyPressed(KEY_DOWN))
        {
            about_us_pos=(about_us_pos+1)%2;
        }
        else if (IsKeyPressed(KEY_UP))
        {
            about_us_pos=(about_us_pos+1)%2;
        }
        BeginDrawing();
        ClearBackground(DARK_BG);
        char *aboutMe = 
"## About Me\n"
"Hello! I'm MEYSAM, a passionate game developer\n"
"with 1 month of experience in the gaming industry.\n "
"My journey in game development began with a deep love for\n"
"interactive storytelling and a fascination with creating immersive worlds. "
"after this game, I have honed my skills in game engineering\n"
", and have had the privilege of working on several exciting projects, including pacman.\n\n"

"### The Idea Behind the Game\n"
"Creating pacman is an innovative adventure that takes place in the captivating world of [Brief Description of the Game World].\n "
"Our primary goal was to develop a game that offers players a unique and engaging experience\n. "
"In pacman, players can immerse themselves in a rich narrative,\n"
 "explore intricate environments, and enjoy [Brief Description of Gameplay Mechanics].\n\n"

"### Inspirations and Motivations\n"
"The inspiration for pacman comes from my passion for creating\n. "
"Ever since I played pacman\n"
", I've dreamed of creating a game that could evoke similar emotions and excitement.\n "
"My aim was to blend beauty and enthusiasm to\n"
" craft an experience that feels both fresh and familiar to players.\n\n"

"### Key Features of the Game\n"
"Here are some of the standout features of pacman:\n"
"- **[passion]:** passion for enrolling better record.\n"
"- **[gammap]:** grace of map, focusing on what makes it unique and enjoyable.\n"
"- **[ghosts movement algorithm]:** it enhances the gameplay experience.\n\n"

"### Development Journey\n"
"Developing pacman has been an incredible journey filled with both challenges and triumphs.\n "
"From initial concept sketches to the final polished product, every step has been a learning experience.\n "
"I am grateful for the support of my friends and dr.zeinali\n"
", who have been instrumental in bringing this vision to life.\n\n"

"### Contact Information\n"
"I would love to hear your thoughts, feedback, or any questions you might have about pacman.\n "
"Feel free to reach out to me via:\n"
"- **Email:** [seyedmeysamhamidi7@gmail.com]\n"
"- **Linkedin:** [seyed meysam hamidi]\n"
"- **Github:** [meisam923]\n"
"- **Telegram:** [S_meisam_hamidi]\n"
"- **Number:** [09917572716]\n\n"

"Thank you for being a part of this journey. I hope you enjoy playing pacman as much as I enjoyed creating it!";

        DrawText(aboutMe,32,32,30,SILVER);
        double fontSize = 35 + 20 * sin(GetTime() * 3); 
        DrawText("P",33*32,2,(int)fontSize,RED);
        DrawText("A",34*32,2,(int)fontSize,BLUE);
        DrawText("C",35*32,2,(int)fontSize,YELLOW);
        DrawText("-",36*32,2,(int)fontSize,SKYBLUE);
        DrawText("M",37*32,2,(int)fontSize,DARKGREEN);
        DrawText("A",38*32,2,(int)fontSize,PURPLE);
        DrawText("N",39*32,2,(int)fontSize,ORANGE);
        if (about_us_pos==0)
        {
            DrawText(">> WATCHING <<",28*32,(43)*32+16,30,TEAL);
            DrawText("BACK",28*32,(44.5*32),30,OLIVE);
        }
        else if (about_us_pos==1)
        {
            DrawText("WATCHING",28*32,(43)*32+16,30,OLIVE);
            DrawText(">> BACK <<",28*32,(44.5*32),30,TEAL);
            DrawText("PRESS ENTER TO BACK",28*32,(46)*32+16,30,SILVER);

        }
        else if (about_us_pos==-1)
        {
            DrawText("WATCHING",28*32,(43)*32+16,30,OLIVE);
            DrawText("BACK",28*32,(44.5*32),30,OLIVE);
            DrawText("PRESS ARROW KEYS TO BACK",28*32,(46)*32+16,20,SILVER);
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            if (about_us_pos==1)
            {
                break;
            }
        }
        UpdateSnowflakes(snowflakes, MAX_SNOWFLAKES, 36*67, 34*47);
        DrawSnowflakes(snowflakes, MAX_SNOWFLAKES);
        EndDrawing();
    }
}
}
}
CloseAudioDevice();
CloseWindow();
return 0;
}