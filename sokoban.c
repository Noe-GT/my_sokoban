/*
** EPITECH PROJECT, 2023
** sokoban.c
** File description:
** sokoban.c
*/

#include "include/sokoban.h"
#include "include/my.h"

static void print_array(char **array, int height)
{
    for (int i = 1; i <= height; i++) {
        write(1, array[i], height);
        write(1, "\n", 1);
    }
}

static int get_size(char *path)
{
    struct stat sb;

    stat(path, &sb);
    return sb.st_size;
}

static void map_size(char *map, params *map_par)
{
    int obj_nb = 0;

    for (int i = 0; map[i] != '\0'; i++) {
        if (map[i] == '\n') {
            map_par->height++;
        }
        if (map_par->height < 1) {
            map_par->length++;
        }
        if (map[i] == 'O') {
            map_par->obj_nb++;
        }
    }
}

static int pos_player(char **map_array, pos *player, int x, int y)
{
    int nbp = 0;

    if (map_array[y][x] == 'P') {
        player->x = x;
        player->y = y;
        nbp += 1;
    }
    return nbp;
}

static int conformity_check(params *map_par)
{
    if (map_par->box_nb < 1 || map_par->objectives_nb > map_par->box_nb) {
        write(1, "ERROR : Not enough boxes 'X'", 28);
        return 84;
    }
    if (map_par->objectives_nb < 1) {
        write(1, "ERROR : Not enough objectives 'O'", 3);
        return 84;
    }
    return 1;
}

void set_pos_sub(params *map_par, char c, int x, int y)
{
    if (c == 'X') {
        map_par->box_nb += 1;
    }
    if (c == 'O') {
        map_par->obj_x[map_par->objectives_nb] = x;
        map_par->obj_y[map_par->objectives_nb] = y;
        map_par->objectives_nb++;
    }
}

int set_pos(char **map_array, pos *player, int y, params *map_par)
{
    int x = 0;
    int obj_i = 0;
    char c;

    while (x < map_par->length) {
        c = map_array[y][x];
        if (c != 'P' && c != ' ' && c != 'O' && c != 'X' && c != '#') {
            write(1, "ERROR : Invalid character in map", 32);
            return 84;
        }
        if (pos_player(map_array, player, x, y) > 1) {
            write(1, "ERROR : No player spawn designated 'P'", 38);
            return 84;
        }
        set_pos_sub(map_par, c, x, y);
        x++;
    }
    return 1;
}

int objects_pos(char **map_array, pos *player, params *map_par)
{
    int y = 0;
    int result = 0;

    while (y < map_par->height) {
        result = set_pos(map_array, player, y, map_par);
        y++;
        if (result == 84) {
            return 84;
        }
    }
    return conformity_check(map_par);
}

void compute_map(pos *player, params *map_par, char *map)
{
    map_par->height = 0;
    map_par->length = 0;
    map_par->valid = 0;
    map_size(map, map_par);
    map_par->obj_x = malloc(sizeof(int) * map_par->obj_nb);
    map_par->obj_y = malloc(sizeof(int) * map_par->obj_nb);
}

int sokoban(int argc, char **argv)
{
    int result = 1;
    char *path = argv[1];
    int size = get_size(path);
    int fd = open(path, O_RDONLY);
    char *map = malloc(sizeof(char) * (size + 1));
    int n = read(fd, map, size + 1);
    char **map_array;
    pos player;
    params map_par;
    int error_test;

    compute_map(&player, &map_par, map);
    map_array = malloc(sizeof(char *) * map_par.height + 1);
    set_arrays(map, map_array, map_par.length);
    error_test = objects_pos(map_array, &player, &map_par);
    if (error_test == 84) {
        return 84;
    }
    return game(map_array, &map_par, &player);
}
