//Main structs that contains everything from the package manager to do the tasks
#ifndef STRUCTURE_H
#define STRUCTURE_H

typedef struct manager {
    char name[25];
    int (*update)(void);
    void (*find)(char *result, char searchstring[]);
    void (*search)(char *result, char searchstring[]);
    int (*delete)(char searchstring[]);
} manager;

typedef struct package {
    char name[50];
    char version[10];
} package;

#endif