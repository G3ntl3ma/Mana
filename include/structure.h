//Main structs that contains everything from the package manager to do the tasks
#ifndef STRUCTURE_H
#define STRUCTURE_H

#define NUM_MANAS 3
#define BUFFER_SIZE 4096
#include <stdbool.h>

typedef struct package {
    char mana[25];
    char name[50];
    char version[50];
} package;

typedef struct manager {
    char name[25];
    bool (*update)(void);
    package (*find)(char searchString[]);
    package (*search)(char searchString[]);
    bool (*install)(char searchString[]);
    bool (*delete)(char searchString[]);
} manager;

#endif