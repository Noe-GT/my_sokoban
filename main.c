/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** main.c
*/

#include "include/sokoban.h"
#include "include/my.h"

int main(int argc, char **argv)
{
    if (argc == 1 || argc > 2)
        return 84;
    if (my_strcmp(argv[1], "-h") == 0) {
        write(1, "USAGE\n./my_sokoban map\n\nDESCRIPTION\nMap file ", 46);
        write(1, "representing the warehouse map, containing '#' ", 47);
        write(1, "for walls, 'P' for the player, 'X' ", 35);
        write(1, "for boxes and 'O' for storage locations.\n", 41);
        write(1, "Player can be controled using the arrow keys.\nTo wi", 51);
        write(1, "n you must put the necessary amount of boxes 'X' on th", 54);
        write(1, "er storage location 'O', without getting them stuck.\n", 53);
    } else {
        return sokoban(argc, argv);
    }
}
