#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "graphics.h"
#include "singleplusmulty.h"


void rules_and_about(int t);//��� ������� �������� �� ��������� 2 � 3 ������ ����
void gamemode_menu();//���� ������ ������ ����

//��� ��������(delay) ���������� ��� ����,��� �� ������� �������� �� ��������� 
//�� ������������ ������ ��� �� �����������, � �������� ������ � 30-100 ���

int main()
{
   const int width=960;
   const int height=720;


   initwindow(width, height);
   struct button_data {
      int x1, y1, x2, y2;
      IMAGE *active, *nonactive;
   };
   button_data buttons[4]= {{506,78,899,205},{506,221,899,348},{506,357,899,484},{506,493,899,620}};

   buttons[0].active=loadBMP("resources/start_game_button_active.jpg");
   buttons[0].nonactive=loadBMP("resources/start_game_button_non_active.jpg");
   buttons[1].active=loadBMP("resources/rules_button_active.jpg");
   buttons[1].nonactive=loadBMP("resources/rules_button_non_active.jpg");
   buttons[2].active=loadBMP("resources/about_button_active.jpg");
   buttons[2].nonactive=loadBMP("resources/about_button_non_active.jpg");
   buttons[3].active=loadBMP("resources/exit_button_active.jpg");
   buttons[3].nonactive=loadBMP("resources/exit_button_non_active.jpg");

   int x, y;
   int button=0;
   int already_button=-1;

   IMAGE *background;


   background=loadBMP("resources/menu.jpg");
   putimage(0, 0, background,COPY_PUT);//��������� �������� ����������� ����

   button=-1;

   while (1) {
      delay(1);//��� �������� ���������� ��� ����,��� �� ������� �������� �� ��������� 
      x=mousex();
      y=mousey();
      button=-1;
      for (int i=0; i<=3; ++i) {
         if (x>buttons[i].x1 && x<buttons[i].x2 && y>buttons[i].y1 && y<buttons[i].y2) button=i;
      }


      if (button!=already_button) {
         if (already_button!=-1) {
            putimage(buttons[already_button].x1, buttons[already_button].y1, buttons[already_button].nonactive,COPY_PUT);
         }
         if (button!=-1) {
            putimage(buttons[button].x1, buttons[button].y1, buttons[button].active,COPY_PUT);
         }
         already_button=button;

      }
      if (button==0  && mousebuttons()==1)//���� ������ ������ ����
      {
         gamemode_menu();
         putimage(0, 0, background,COPY_PUT);
         delay(250);
      }
      if (button==1  && mousebuttons()==1)//���� � ��������� ����
      {
         rules_and_about(button);
         putimage(0, 0, background,COPY_PUT);
         delay(250);
      }
      if (button==2  && mousebuttons()==1)//���� � ����������� � ���������
      {
         rules_and_about(button);
         putimage(0, 0, background,COPY_PUT);
         delay(250);
      }
      if (button==3  && mousebuttons()==1)//�����
      {
         exit(0);
      }

   }
}

void rules_and_about(int t)
{

   IMAGE *background;
   int x, y;
   int button=0;

   if (t==1) background=loadBMP("resources/rules_background.jpg");//����������,����� �� ������� �������� ����� ��������
   else background=loadBMP("resources/about_background.jpg");
   IMAGE *button_active=loadBMP("resources/to_menu_button_active.jpg");
   IMAGE *button_non_active=loadBMP("resources/to_menu_button_non_active.jpg");

   cleardevice();
   putimage(0, 0, background,COPY_PUT);//��������� ����
   freeimage(background);

   while (1) {//������ � ������� ������ � ������� ����
      delay(1);
      x=mousex();
      y=mousey();
      if (x>582 && x<860 && y>545 && y<650) {//��������,��� ���� �������� �� �������
         if (button==0) {
            putimage(582, 545, button_active,COPY_PUT);//������ ��� �� ����������
            button=1;
         }
         if (button==1 && mousebuttons()==1) {
            putimage(582, 545, button_non_active,COPY_PUT);//������ ��� ����������, ��������� ������� �� ���
            delay(100);
            return;
         }
      }
      if ((x<=582 || x>=860 || y<=545 || y>=650) && button==1) {//���������,������ �� �� ����
         putimage(582, 545, button_non_active,COPY_PUT);
         button=0;
      }
   }
}

void gamemode_menu() {
   int x, y;
   int button=0,
       already_button=0,
       gamemode;


   IMAGE *background=loadBMP("resources/gamemode_background.jpg");//�������� �������� � �����
   IMAGE *singleplayer_active=loadBMP("resources/singleplayer_active.jpg");
   IMAGE *multiplayer_active=loadBMP("resources/multiplayer_active.jpg");
   IMAGE *singleplayer_non_active=loadBMP("resources/singleplayer_non_active.jpg");
   IMAGE *multiplayer_non_active=loadBMP("resources/multiplayer_non_active.jpg");


   cleardevice();
   putimage(0, 0, background,COPY_PUT);//��������� ����
   freeimage(background);

   while (1) {
      delay(1);
      x=mousex();
      y=mousey();

      if (x>224 && x<736 && y>236 && y<386) {
         button=1;
         if (mousebuttons()==1) {
            gamemode=1;
            start_game(gamemode);//������ ��������� ����
            return;
         }
      }
      else {
         if (x>223 && x<736 && y>425 && y<572) {
            button=2;
            if (mousebuttons()==1){
               gamemode=0;//������ ����������
               start_game(gamemode);
               return;
            }
         }
         else button=0;
      }

      if (button!=already_button) {
         switch (already_button) {
         case 0:
            if (button==1) {
               putimage(224, 236, singleplayer_active,COPY_PUT);
               already_button=1;
            }
            else {
               if (button==2) {
                  putimage(223, 425, multiplayer_active,COPY_PUT);
                  already_button=2;
               }
            }
            break;
         case 1:
            putimage(224, 236, singleplayer_non_active,COPY_PUT);
            already_button=button;
            break;
         case 2:
            putimage(223, 425, multiplayer_non_active,COPY_PUT);
            already_button=button;
            break;
         }
      }
   }
}