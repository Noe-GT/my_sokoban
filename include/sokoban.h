/*
** EPITECH PROJECT, 2023
** sokoban.h
** File description:
** sokoban.h
*/

#include "my_include.h"

#ifndef POSITION
    #define POSITION

typedef struct pos {
    int x;
    int y;
} pos;

#endif /* POSITION */

#ifndef PARAMS
    #define PARAMS

typedef struct params {
    int height;
    int length;
    int obj_nb;
    int box_nb;
    int players_nb;
    int objectives_nb;
    int *obj_x;
    int *obj_y;
    int stuck;
    int valid;
} params;

#endif /* PARAMS */

#ifndef SOKOBAN_H
    #define SOKOBAN_H

int sokoban(int argc, char **argv);
int game(char **map_array, params *map_par, pos *player);
int main(int argc, char **argv);
void set_arrays(char *str, char **array, int length);
int move_player(char **map_array, pos *player, params *map_par, int key);

#endif /* SOKOBAN_H */
