//Manager for brew

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

#include "../include/structure.h"
#include "../include/managers/nix.h"

bool UpdateNix(void){
    printf("UpdateNix has not been implemented yet\n");
    return false;
}

package FindNix(char searchString[]){
    package result = {0};
    printf("FindNix has not been implemented yet: %s\n", searchString);

    return result;
}

package SearchNix(char searchString[]){
    package result = {0};
    printf("SearchNix function is not implemented yet: %s\n", searchString);
    return result;
}

bool InstallNix(char searchString[]){
    printf("InstallNix is not implemented yet: %s\n", searchString);
    return false;
}

bool DeleteNix(char searchString[]){
    printf("DeleteNix function is not implemented yet: %s\n", searchString);
    return false;
}

manager NIXMana(void){
    manager nixMana = {"nix", UpdateNix, FindNix, SearchNix, InstallNix, DeleteNix};
    return nixMana;
}