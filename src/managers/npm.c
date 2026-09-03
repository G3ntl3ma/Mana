//Manager for brew

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

#include "../include/structure.h"
#include "../include/managers/npm.h"

bool UpdateNpm(void){
    printf("UpdateNpm has not been implemented yet\n");
    return false;
}

package FindNpm(char searchString[]){
    package result = {0};
    printf("FindNpm has not been implemented yet: %s\n", searchString);

    return result;
}

package SearchNpm(char searchString[]){
    package result = {0};
    printf("SearchNpm function is not implemented yet: %s\n", searchString);
    return result;
}

bool InstallNpm(char searchString[]){
    printf("InstallNpm function is not implemented yet: %s\n", searchString);
    return false;
}

bool DeleteNpm(char searchString[]){
    printf("DeleteNpm function is not implemented yet: %s\n", searchString);
    return false;
}

manager NPMMana(void){
    manager npmMana = {"npm", UpdateNpm, FindNpm, SearchNpm, InstallNpm, DeleteNpm};
    return npmMana;
}