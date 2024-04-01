/*
** EPITECH PROJECT, 2023
** set_arrays.c
** File description:
** set_arrays.c
*/

#include "include/sokoban.h"

void set_arrays(char *str, char **array, int length)
{
    int x = 0;
    int y = 0;

    array[y] = malloc(sizeof(char) * (length));
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            y++;
            array[y] = malloc(sizeof(char) * length + 1);
            x = 0;
        } else {
            array[y][x] = str[i];
            x++;
        }
    }
}
