#ifndef SINGLEPLUSMULTI_H_
#define SINGLEPLUSMULTI_H_
#include "graphics.h"
void congratulations(int current_player,bool gamemode);
void draw_background(bool gamemode);
void generate_piles(int *pile);
int player_turn(int *pile, IMAGE *blank, bool gamemode, int current_player);
void PC_turn(int *pile,IMAGE *blank);
void congratulations(int player_turn);
void start_game(bool gamemode);
void show_whose_turn(int current_player, IMAGE *turn_1, IMAGE *turn_2);
#endif