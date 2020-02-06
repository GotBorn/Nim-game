#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "singleplusmulty.h"
#include "graphics.h"
void start_game(bool gamemode)
{
   draw_background(gamemode);//работа с фоном

   int pile[4];
   generate_piles(pile);//генерация кучек

   IMAGE *chip=loadBMP("resources/chip.jpg");//загрузка фишки в память
   IMAGE *blank=loadBMP("resources/blank.jpg");

   IMAGE *turn_1=loadBMP("resources/turn_1.jpg");
   IMAGE *turn_2;
   if (gamemode) turn_2=loadBMP("resources/turn_PC.jpg");
   else turn_2=loadBMP("resources/turn_2.jpg");

   int i, j;
   for (i=1; i<=3; ++i) {//для каждой кучи...
      for (j=1; j<=pile[i]; ++j) {//...n раз...
         putimage(109+83*(j-1), 232+85*(i-1), chip,COPY_PUT);//...нарисуем фишку
      }
   }

   int current_player=0;
   
   delay (800);
   while (1) {
      if (pile[1]==0 && pile[2]==0 && pile[3]==0) {
         congratulations(current_player, gamemode);
         return;
      }
      show_whose_turn(current_player, turn_1, turn_2);
      switch (current_player) {
      case 0:
         current_player=player_turn(pile, blank,gamemode, current_player);
         break;
      case 1:
         current_player=player_turn(pile, blank, gamemode, current_player);
         break;
      case 2:
         PC_turn(pile, blank);
         current_player=0;
         break;
      }
   }
}

int player_turn(int *pile,IMAGE *blank, bool gamemode, int current_player)
{
   int x,y,i,j;
   while (1) {
      delay(1);
      x=mousex();//считываение координат мыши
      y=mousey();
      if ((y<232 || x<109) && mousebuttons()==1) { //если нажатие выше/левее фишек
         return current_player;
      }
      else {
         if (mousebuttons()==1) {
            i=((y-232)/85)+1;//расчет номера кучки
            if (i<=3) {//если координаты соответствую кучке(одной из трех)
               j=((x-109)/83)+1;//вычисляем номер фишки
               if (j<=pile[i]) {
                  for (int m=j; m<=pile[i]; ++m) {
                     putimage(109+83*(m-1), 232+85*(i-1), blank,COPY_PUT);
                  }
                  pile[i]=j-1;
                  if (gamemode==0) return !current_player;
                  else return 2;
               }
               else return current_player;
            }
            else return current_player;
         }
      }
   }
}


void congratulations(int current_player, bool gamemode)
{
   while (kbhit()) getch();

   IMAGE *background;
   IMAGE *blank=loadBMP("resources/blank2.jpg");
   if (!gamemode) {
      switch (current_player) {
      case 0:
         background=loadBMP("resources/winner_2.jpg");
         break;
      case 1:
         background=loadBMP("resources/winner_1.jpg");
         break;
      }
   }
   else {
      switch (current_player) {
      case 0:
         background=loadBMP("resources/winner_PC.jpg");
         break;
      case 2:
         background=loadBMP("resources/winner_1.jpg");
         break;
      }
   }
   putimage(0, 0, background,COPY_PUT);
   freeimage(background);
   background=loadBMP("resources/text.jpg");
   while (!kbhit()) {
      delay(650);
      putimage(240, 601, background,COPY_PUT);
      delay(650);
      putimage(240, 601, blank,COPY_PUT);
   }
   getch();
   freeimage(background);
   freeimage(blank);
   return;
}


void draw_background(bool gamemode)
{
   IMAGE *background;
   cleardevice();
   if (gamemode) background=loadBMP("resources/multiplayer_menu_PC.jpg");
   else background=loadBMP("resources/multiplayer_menu_player.jpg");
   putimage(0, 0, background,COPY_PUT);
   freeimage(background);
}

void generate_piles(int *pile)
{
   srand(time(NULL));
   for (int i=1; i<=3; ++i) {
      pile[i]=rand() % 8;
      while (pile[i]==0) pile[i]=rand() % 8;
   }
   while (!(pile[1] ^ pile[2] ^ pile[3]) && pile[3]==0)  pile[3]=rand() % 8;//защита от невыигрываемой игры
}



void PC_turn(int *pile,IMAGE *blank)
{
   int nim_sum;
   int j;
   delay(1560);
   nim_sum=pile[1] ^ pile[2] ^ pile[3];
   int i=1;
   if (nim_sum==0) {//если Ним сумма равна 0
      while (1) {
         if (pile[i]!=0) {
            putimage(109+83*(pile[i]-1), 232+85*(i-1), blank,COPY_PUT);
            pile[i]=pile[i]-1;
            break;
         }
         else ++i;
      }
   }
   else {
      while (1) {
         if (pile[i]>(pile[i] ^ nim_sum)) {
            for (j=pile[i] ^ nim_sum; j<=pile[i]; ++j) {
               putimage(109+83*(j), 232+85*(i-1), blank,COPY_PUT);
            }
            pile[i]=pile[i] ^ nim_sum;
            break;
         }
         else ++i;
      }
   }
}

void show_whose_turn(int current_player, IMAGE *turn_1, IMAGE *turn_2)
{
   if (!current_player) putimage(94, 579, turn_1,COPY_PUT);
   else putimage(94, 579, turn_2,COPY_PUT);
}