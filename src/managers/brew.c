//Manager for brew

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

#include "../include/structure.h"
#include "../include/managers/brew.h"

bool UpdateBrew(void){
    printf("UpdateBrew has not been implemented yet\n");
    return false;
}

package FindBrew(char searchString[]){
    package result = {0};
    printf("FindBrew has not been implemented yet: %s\n", searchString);

    return result;
}

package SearchBrew(char searchString[]){
    package result = {0};
    printf("SearchBrew function is not implemented yet: %s\n", searchString);
    return result;
}

bool DeleteBrew(char searchString[]){
    printf("DeleteBrew function is not implemented yet: %s\n", searchString);
    return false;
}

manager HOMEBREWMana(void){
    manager brewMana = {"brew", UpdateBrew, FindBrew, SearchBrew, DeleteBrew};
    return brewMana;
}