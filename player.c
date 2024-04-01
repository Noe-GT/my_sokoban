/*
** EPITECH PROJECT, 2023
** player.c
** File description:
** player.c
*/

#include "include/sokoban.h"
#include "include/my.h"

static int move_right(char **map_array, params *map_par, pos *player)
{
    char temp;

    if (map_array[player->y][player->x + 1] == 'X') {
        temp = map_array[player->y][player->x + 2];
        if (temp == ' ' || temp == 'O') {
            map_array[player->y][player->x] = ' ';
            map_array[player->y][player->x + 2] = 'X';
            player->x += 1;
        }
    } else {
        map_array[player->y][player->x] = ' ';
        player->x += 1;
    }
}

static int move_left(char **map_array, params *map_par, pos *player)
{
    char temp;

    if (map_array[player->y][player->x - 1] == 'X') {
        temp = map_array[player->y][player->x - 2];
        if (temp == ' ' || temp == 'O') {
            map_array[player->y][player->x] = ' ';
            map_array[player->y][player->x - 2] = 'X';
            player->x -= 1;
        }
    } else {
        map_array[player->y][player->x] = ' ';
        player->x -= 1;
    }
}

static int move_up(char **map_array, params *map_par, pos *player)
{
    char temp;

    if (map_array[player->y - 1][player->x] == 'X') {
        temp = map_array[player->y - 2][player->x];
        if (temp == ' ' || temp == 'O') {
            map_array[player->y][player->x] = ' ';
            map_array[player->y - 2][player->x] = 'X';
            player->y -= 1;
        }
    } else {
        map_array[player->y][player->x] = ' ';
        player->y -= 1;
    }
}

static int move_down(char **map_array, params *map_par, pos *player)
{
    char temp;

    if (map_array[player->y + 1][player->x] == 'X') {
        temp = map_array[player->y + 2][player->x];
        if (temp == ' ' || temp == 'O') {
            map_array[player->y][player->x] = ' ';
            map_array[player->y + 2][player->x] = 'X';
            player->y += 1;
        }
    } else {
        map_array[player->y][player->x] = ' ';
        player->y += 1;
    }
}

int move_player(char **map_array, pos *player, params *map_par, int key)
{
    if (key == KEY_RIGHT && map_array[player->y][player->x + 1] != '#') {
        move_right(map_array, map_par, player);
    }
    if (key == KEY_LEFT && map_array[player->y][player->x - 1] != '#') {
        move_left(map_array, map_par, player);
    }
    if (key == KEY_UP && map_array[player->y - 1][player->x] != '#') {
        move_up(map_array, map_par, player);
    }
    if (key == KEY_DOWN && map_array[player->y + 1][player->x] != '#') {
        move_down(map_array, map_par, player);
    }
    map_array[player->y][player->x] = 'P';
    return 0;
}
