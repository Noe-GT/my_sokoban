/*
** EPITECH PROJECT, 2023
** game.c
** File description:
** game.c
*/

#include "include/sokoban.h"
#include "include/my.h"

void draw_map(char **map_array, int height)
{
    for (int i = 0; i < height; i++) {
        mvaddstr(i, 0, map_array[i]);
    }
}

static int is_stuck(char **map_array, int x, int y)
{
    char ym = map_array[y - 1][x];
    char yp = map_array[y + 1][x];
    char xm = map_array[y][x - 1];
    char xp = map_array[y][x + 1];

    if ((ym == '#' || ym == 'X') || (yp == '#' || yp == 'X')) {
        if ((xm == '#' || xm == 'X') || (xp == '#' || xp == 'X')) {
            return 1;
        }
    }
    if ((xm == '#' || xm == 'X') || (xp == '#' || xp == 'X')) {
        if ((ym == '#' || ym == 'X') || (yp == '#' || yp == 'X')) {
            return 1;
        }
    }
    return 0;
}

static void check_stuck(char **map_array, params *map_par, int y)
{
    int x = 0;

    while (x < map_par->length) {
        if (map_array[y][x] == 'X') {
            map_par->stuck += is_stuck(map_array, x, y);
        }
        x++;
    }
}

void compute_game(char **map_array, pos *player, params *map_par)
{
    int y = 0;

    map_par->valid = 0;
    map_par->stuck = 0;
    for (int i = 0; i < map_par->obj_nb; i++) {
        if (map_array[map_par->obj_y[i]][map_par->obj_x[i]] == ' ') {
            map_array[map_par->obj_y[i]][map_par->obj_x[i]] = 'O';
        }
        if (map_array[map_par->obj_y[i]][map_par->obj_x[i]] == 'X') {
            map_par->valid++;
        }
    }
    while (y < map_par->height) {
        check_stuck(map_array, map_par, y);
        y++;
    }
}

int run(char **map_array, params *map_par, pos *player)
{
    int key;

    key = getch();
    while (key != 113) {
        key = getch();
        move_player(map_array, player, map_par, key);
        compute_game(map_array, player, map_par);
        draw_map(map_array, map_par->height);
        refresh();
        if (map_par->valid == map_par->obj_nb) {
            return 0;
        }
        if (map_par->stuck == map_par->box_nb) {
            return 1;
        }
    }
    return 1;
}

int game(char **map_array, params *map_par, pos *player)
{
    int result = 1;

    initscr();
    keypad(stdscr, 1);
    noecho();
    curs_set(0);
    draw_map(map_array, map_par->height);
    result = run(map_array, map_par, player);
    endwin();
    return result;
}
