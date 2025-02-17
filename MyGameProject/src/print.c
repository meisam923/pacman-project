#include "E:\MyGameProject\include\raylib.h"
#include "E:\MyGameProject\Headers\print.h"
#include "E:\MyGameProject\Headers\funda.h"
#define SILVER (Color){ 192, 192, 192, 255 }
#define DARK_BG (Color){ 30, 30, 30, 255 }
#define DARK_RED (Color){ 139, 0, 0, 255 }       // قرمز تیره
#define INDIGO (Color){ 75, 0, 130, 255 }        // نیلی
#define TEAL (Color){ 0, 128, 128, 255 }         // سبز آبی
#define CRIMSON (Color){ 220, 20, 60, 255 }      // قرمز پررنگ
#define OLIVE (Color){ 128, 128, 0, 255 }        // زیتونی
#define NAVY (Color){ 0, 0, 128, 255 }           // سرمه‌ای
#define MINT (Color){ 189, 252, 201, 255 }       // سبز نعنایی
#define CORAL (Color){ 255, 127, 80, 255 }       // مرجانی
#define LAVENDER (Color){ 230, 230, 250, 255 }   // اسطوخودوسی
#include <math.h>
#ifndef HIGHT
#define HEIGHT 47
#endif
#ifndef WIDTH
#define WIDTH 67
#endif
int gamemap[HEIGHT][WIDTH];
#define MAX_SNOWFLAKES 100
void UpdateSnowflakes(Snowflake snowflakes[], int maxSnowflakes, int screenWidth, int screenHeight) {
    for (int i = 0; i < maxSnowflakes; i++) {
        snowflakes[i].position.y += snowflakes[i].speed;
        if (snowflakes[i].position.y > screenHeight) {
            snowflakes[i].position.x =(float) GetRandomValue(0, screenWidth);
            snowflakes[i].position.y = 0 - snowflakes[i].size;
        }
    }
}
void DrawSnowflakes(Snowflake snowflakes[], int maxSnowflakes) {
    for (int i = 0; i < maxSnowflakes; i++) {
        DrawCircleV(snowflakes[i].position, snowflakes[i].size, WHITE);
    }
}
void print(int minute,int second,int cnt,int board [47][67],int hardness,Snowflake snowflakes[MAX_SNOWFLAKES])
{
BeginDrawing();
ClearBackground(RAYWHITE);
for (int i=0;i<47;i++)
{
    for (int j=0;j<67;j++)
    {
        if (board[i][j]==1)
        {
            DrawRectangle(j*32+134,i*32+47,32,32,SKYBLUE);
        }
        else if (board[i][j]==0)
        {
            DrawRectangle(j*32+134,i*32+47,32,32,DARKGREEN);
        } 
        else if (board[i][j]==2)
        {
            DrawTexture(pacman.star_IMG,j*32+134,i*32+47,GOLD);
        }
        else if (board[i][j]==3)
        {
            DrawTexture(pacman.gilas_IMG,j*32+134,i*32+47,RED);
        }
        else if (board[i][j]==4)
        {
            DrawTexture(pacman.apple_IMG,j*32+134,i*32+47,LIME);
        }
        else if (board[i][j]==5)
        {
            DrawTexture(pacman.mushroom_IMG,j*32+134,i*32+47,PURPLE);
        }
        else if (board[i][j]==6)
        {
            DrawTexture(pacman.pepper_IMG,j*32+134,i*32+47,MAROON);
        }
    } 
}
char time[20];
char armor[20];
char star[20];
sprintf(armor,"ARMOR : %d",pacman.armor);
sprintf(star,"STAR : %d",pacman.star);
sprintf(time,"TIME: %02d:%02d",minute,second);
DrawText(time,0,0,40,NAVY);
DrawText(armor,1*32,48.5*32,35,NAVY);
DrawText(star,60*32,48.5*32,35,NAVY);
double fontSize = 25 + 10 * sin(GetTime() * 3); 
DrawText("|HERE IS EMPTY OF YOUR ADVERTISMENT|",8*32,0,(int)fontSize,CRIMSON);
if (second%7==0)
{
DrawText("P",34*32,0,40,YELLOW);
DrawText("A",35*32,0,40,BLUE);
DrawText("C",36*32,0,40,RED);
DrawText("-",37*32,0,40,NAVY);
DrawText("M",38*32,0,40,DARKGREEN);
DrawText("A",39*32,0,40,PURPLE);
DrawText("N",40*32,0,40,ORANGE);
}
else if (second%7==1)
{
DrawText("P",34*32,0,40,BLUE);
DrawText("A",35*32,0,40,YELLOW);
DrawText("C",36*32,0,40,RED);
DrawText("-",37*32,0,40,NAVY);
DrawText("M",38*32,0,40,DARKGREEN);
DrawText("A",39*32,0,40,PURPLE);
DrawText("N",40*32,0,40,ORANGE);
}
else if (second%7==2)
{
DrawText("P",34*32,0,40,RED);
DrawText("A",35*32,0,40,BLUE);
DrawText("C",36*32,0,40,YELLOW);
DrawText("-",37*32,0,40,NAVY);
DrawText("M",38*32,0,40,DARKGREEN);
DrawText("A",39*32,0,40,PURPLE);
DrawText("N",40*32,0,40,ORANGE);
}
else if (second%7==3)
{
DrawText("P",34*32,0,40,NAVY);
DrawText("A",35*32,0,40,BLUE);
DrawText("C",36*32,0,40,RED);
DrawText("-",37*32,0,40,YELLOW);
DrawText("M",38*32,0,40,DARKGREEN);
DrawText("A",39*32,0,40,PURPLE);
DrawText("N",40*32,0,40,ORANGE);
}
else if (second%7==4)
{
DrawText("P",34*32,0,40,DARKGREEN);
DrawText("A",35*32,0,40,BLUE);
DrawText("C",36*32,0,40,RED);
DrawText("-",37*32,0,40,NAVY);
DrawText("M",38*32,0,40,YELLOW);
DrawText("A",39*32,0,40,PURPLE);
DrawText("N",40*32,0,40,ORANGE);
}
else if (second%7==5)
{
DrawText("P",34*32,0,40,PURPLE);
DrawText("A",35*32,0,40,BLUE);
DrawText("C",36*32,0,40,RED);
DrawText("-",37*32,0,40,NAVY);
DrawText("M",38*32,0,40,DARKGREEN);
DrawText("A",39*32,0,40,YELLOW);
DrawText("N",40*32,0,40,ORANGE);
}
else if (second%7==6)
{
DrawText("P",34*32,0,40,ORANGE);
DrawText("A",35*32,0,40,BLUE);
DrawText("C",36*32,0,40,RED);
DrawText("-",37*32,0,40,NAVY);
DrawText("M",38*32,0,40,DARKGREEN);
DrawText("A",39*32,0,40,PURPLE);
DrawText("N",40*32,0,40,YELLOW);
}
DrawText("|HERE IS EMPTY OF YOUR ADVERTISMENT|",45*32,0,(int)fontSize,CRIMSON);
if (pacman.direction==1)      /*pacman flasher printing*/
{
    if (cnt%2<1)
    DrawTexture(pacman.IMP_base,(int)(pacman.x*32)+134,(int)(pacman.y*32)+47,WHITE);
    else
    DrawTexture(pacman.IMP_right,(int)(pacman.x*32)+134,(int)(pacman.y*32)+47,WHITE);
}
else if (pacman.direction==2)
{
    if (cnt%2<1)
    DrawTexture(pacman.IMP_base,(int)(pacman.x*32)+134,(int)(pacman.y*32)+47,WHITE);
    else
    DrawTexture(pacman.IMP_up,(int)(pacman.x*32)+134,(int)(pacman.y*32)+47,WHITE);
}
else if (pacman.direction==3)
{
    if (cnt%2<1)
    DrawTexture(pacman.IMP_base,(int)(pacman.x*32)+134,(int)(pacman.y*32)+47,WHITE);
    else
    DrawTexture(pacman.IMP_left,(int)(pacman.x*32)+134,(int)(pacman.y*32)+47,WHITE);
}
else if (pacman.direction==4)
{
    if (cnt%2<1)
    DrawTexture(pacman.IMP_base,(int)(pacman.x*32)+134,(int)(pacman.y*32)+47,WHITE);
    else
    DrawTexture(pacman.IMP_down,(int)(pacman.x*32)+134,(int)(pacman.y*32)+47,WHITE);
}
else
{
    DrawTexture(pacman.IMP_base,(int)(pacman.x*32)+134,(int)(pacman.y*32)+47,WHITE);
}
if (hardness==1)
{
for (int i=0;i<7;i++)
{
if (!norm_ghosts[i].hide)
DrawTexture(norm_ghosts[i].IMG,(int)(norm_ghosts[i].x*32)+134,(int)(norm_ghosts[i].y*32)+47,WHITE);
}
for (int i=0;i<2;i++)
{
if (!searcher[i].hide)
DrawTexture(searcher[i].IMG,(int)(searcher[i].x*32)+134,(int)(searcher[i].y*32)+47,WHITE);
}
}
if (hardness==2)
{
for (int i=0;i<8;i++)
{
if (!norm_ghosts[i].hide)
DrawTexture(norm_ghosts[i].IMG,(int)(norm_ghosts[i].x*32)+134,(int)(norm_ghosts[i].y*32)+47,WHITE);
}
for (int i=0;i<3;i++)
{
if (!searcher[i].hide)
DrawTexture(searcher[i].IMG,(int)(searcher[i].x*32)+134,(int)(searcher[i].y*32)+47,WHITE);
}
}
if (hardness==3)
{
for (int i=0;i<9;i++)
{
if (!norm_ghosts[i].hide)
DrawTexture(norm_ghosts[i].IMG,(int)(norm_ghosts[i].x*32)+134,(int)(norm_ghosts[i].y*32)+47,WHITE);
}
for (int i=0;i<4;i++)
{
if (!searcher[i].hide)
DrawTexture(searcher[i].IMG,(int)(searcher[i].x*32)+134,(int)(searcher[i].y*32)+47,WHITE);
}
}
DrawSnowflakes(snowflakes, MAX_SNOWFLAKES);
EndDrawing();
}
void print_game_over_window(int board [47][67] ,double time,int cnt,char user_name[])
{
BeginDrawing();
ClearBackground(DARK_BG);
int second = (int)time %60;
int minute= (int)time/60;
for (int i=0;i<47;i++)
{
    for (int j=0;j<67;j++)
    {
        if (board[i][j]==1)
        {
            DrawRectangle(j*32+134,i*32+47,32,32,LIGHTGRAY);
        }
        else if (board[i][j]==0)
        {
            DrawRectangle(j*32+134,i*32+47,32,32,BLACK);
        } 
        else if (board[i][j]==2)
        {
            DrawTexture(pacman.star_IMG,j*32+134,i*32+47,BLACK);
        }
        else if (board[i][j]==3)
        {
            DrawTexture(pacman.gilas_IMG,j*32+134,i*32+47,BLACK);
        }
        else if (board[i][j]==4)
        {
            DrawTexture(pacman.apple_IMG,j*32+134,i*32+47,BLACK);
        }
        else if (board[i][j]==5)
        {
            DrawTexture(pacman.mushroom_IMG,j*32+134,i*32+47,BLACK);
        }
        else if (board[i][j]==6)
        {
            DrawTexture(pacman.pepper_IMG,j*32+134,i*32+47,BLACK);
        }
    } 
}
DrawTexture(pacman.IMP_base,(int)(pacman.x*32)+134,(int)(pacman.y*32)+47,GOLD);
for (int i = 0; i < 25; i++) {
    int x = GetRandomValue(0, WIDTH*36);
    int y = GetRandomValue(0, HEIGHT*34);
    DrawCircle(x, y, 5, RED);
}
for (int i = 0; i < 25; i++) {
    int x = GetRandomValue(0, WIDTH*36);
    int y = GetRandomValue(0, HEIGHT*34);
    DrawCircle(x, y, 5, ORANGE);
}
for (int i = 0; i < 25; i++) {
    int x = GetRandomValue(0, WIDTH*36);
    int y = GetRandomValue(0, HEIGHT*34);
    DrawCircle(x, y, 5, BLUE);
}
for (int i = 0; i < 25; i++) {
    int x = GetRandomValue(0, WIDTH*36);
    int y = GetRandomValue(0, HEIGHT*34);
    DrawCircle(x, y, 5, PINK);
}
DrawRectangle(0, 0, WIDTH*36, HEIGHT*34, Fade(BLACK, 0.5f));
char score[20];
char time_[20];
sprintf(score,"YOUR SCORE : %d",pacman.star);
sprintf(time_,"TIME: %02d:%02d",minute,second);
DrawText(user_name,32*32,23*32,50,YELLOW);
DrawText(time_,32*32,25*32,50,YELLOW);
DrawText(score,30*32,28*32,50,YELLOW);
DrawText("PRESS ENTER TO BACK TO MENU",30*32,30*32,40,SILVER);
double fontSize = 35 + 20 * sin(GetTime() * 3); 
DrawText("P",34*32,2,(int)fontSize,RED);
DrawText("A",35*32,2,(int)fontSize,BLUE);
DrawText("C",36*32,2,(int)fontSize,YELLOW);
DrawText("-",37*32,2,(int)fontSize,SKYBLUE);
DrawText("M",38*32,2,(int)fontSize,DARKGREEN);
DrawText("A",39*32,2,(int)fontSize,PURPLE);
DrawText("N",40*32,2,(int)fontSize,ORANGE);
DrawText("GAME OVER",cnt*32,20*32,80,RED);
EndDrawing();
WaitTime(0.095);
return;
}
void print_menu(int menu_position,Snowflake snowflakes[MAX_SNOWFLAKES])
{
    BeginDrawing();
    ClearBackground(DARK_BG);
    DrawSnowflakes(snowflakes, MAX_SNOWFLAKES);
    double fontSize = 35 + 20 * sin(GetTime() * 3); 
    DrawText("P",33*32,2,(int)fontSize,RED);
    DrawText("A",34*32,2,(int)fontSize,BLUE);
    DrawText("C",35*32,2,(int)fontSize,YELLOW);
    DrawText("-",36*32,2,(int)fontSize,SKYBLUE);
    DrawText("M",37*32,2,(int)fontSize,DARKGREEN);
    DrawText("A",38*32,2,(int)fontSize,PURPLE);
    DrawText("N",39*32,2,(int)fontSize,ORANGE);
    if (menu_position%5==0)
    {
    DrawText(">> PLAY <<",32*32,14*32,40,TEAL);
    DrawText("RECORDS",33*32,17*32,40,OLIVE);
    DrawText("HARDNESS",33*32,20*32,40,OLIVE);
    DrawText("ABOUT US",33*32,23*32,40,OLIVE);
    DrawText("EXIT",33*32,26*32,40,OLIVE);
    }
    else if (menu_position%5==1)
    {
    DrawText("PLAY",33*32,14*32,40,OLIVE);
    DrawText(">> RECORDS <<",32*32,17*32,40,TEAL);
    DrawText("HARDNESS",33*32,20*32,40,OLIVE);
    DrawText("ABOUT US",33*32,23*32,40,OLIVE);
    DrawText("EXIT",33*32,26*32,40,OLIVE);
    }
    else if (menu_position%5==2)
    {
    DrawText("PLAY",33*32,14*32,40,OLIVE);
    DrawText("RECORDS",33*32,17*32,40,OLIVE);
    DrawText(">> HARDNESS <<",32*32,20*32,40,TEAL);
    DrawText("ABOUT US",33*32,23*32,40,OLIVE);
    DrawText("EXIT",33*32,26*32,40,OLIVE);
    }
    else if (menu_position%5==3)
    {
    DrawText("PLAY",33*32,14*32,40,OLIVE);
    DrawText("RECORDS",33*32,17*32,40,OLIVE);
    DrawText("HARDNESS",33*32,20*32,40,OLIVE);
    DrawText(">> ABOUT US <<",32*32,23*32,40,TEAL);
    DrawText("EXIT",33*32,26*32,40,OLIVE);
    }
    else if (menu_position%5==4)
    {
    DrawText("PLAY",33*32,14*32,40,OLIVE);
    DrawText("RECORDS",33*32,17*32,40,OLIVE);
    DrawText("HARDNESS",33*32,20*32,40,OLIVE);
    DrawText("ABOUT US",33*32,23*32,40,OLIVE);
    DrawText(">> EXIT <<",32*32,26*32,40,TEAL);
    }
    const char *noticeText = 
    "                                                          Notice:\n"
    "By using this software, you agree to be bound by the terms and conditions of the End User License Agreement (EULA).\n"
    "All intellectual property rights in and to this software and its contents are owned by [HAMIDI ELECTRONICS].\n"
    "Unauthorized copying, distribution, or modification of this software is strictly prohibited and may result in legal action.\n"
    "\n"
    "                                                          Disclaimer:\n"
    "[HAMIDI ELECTRONICS] assumes no responsibility for any damages or losses resulting from the use or misuse of this software.\n"
    "This software is provided \"as Seyed Moahammadreza Hamidi \"\n"
    "without warranty of any kind, either express or implied, including but not\n"
    "limited to the implied warranties of merchantability and fitness for a particular purpose.\n"
    "\n"
    "                                                          Privacy Policy:\n"
    "Your privacy is important to us.\n"
    "Please review our Privacy Policy to understand how we collect, use, and protect your personal information.\n"
    "\n"
    "                                                          Contact Information:\n"
    "For support or inquiries, please contact us at: support@seyedmeysamhamidi7@gmail.com";
    DrawTextEx(GetFontDefault(), noticeText, (Vector2){ 20*32, 36.5*32 }, 20, 2, SILVER);
    EndDrawing();
    return;
}