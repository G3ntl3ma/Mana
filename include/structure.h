//Main structs that contains everything from the package manager to do the tasks
#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdbool.h>

typedef struct package {
    char mana[25];
    char name[50];
    char version[10];
} package;

typedef struct manager {
    char name[25];
    bool (*update)(void);
    package (*find)(char *result, char searchstring[]);
    package (*search)(char searchstring[]);
    bool (*delete)(char searchstring[]);
} manager;

#endif