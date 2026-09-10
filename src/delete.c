#include <stdio.h>
#include <stdlib.h>

#include "../include/search.h"
#include "../include/structure.h"

#include "../include/managers/aptget.h"
#include "../include/managers/brew.h"
#include "../include/managers/npm.h"

void delete(char searchString[]){
    manager managers[NUM_MANAS];
    managers[0] = APTGETMana();
    managers[1] = HOMEBREWMana();
    managers[2] = NPMMana();

    package packages[NUM_MANAS];
    manager validManagers[NUM_MANAS];
    int i;
    int counter = 1;
    int selectedPackage;

    for(i = 0; i < NUM_MANAS; i++){
        packages[i] = managers[i].find(searchString);
        if(packages[i].name[0] != '\0'){
            printf("%d: %s | %s | %s\n", counter, packages[i].mana, packages[i].name, packages[i].version);
            validManagers[counter - 1] = managers[i];
            counter++;
        }
    }

    printf("\nType the number in front of the manager to delete the package. Type 0 to quit\n");
    scanf(" %d", &selectedPackage);
    if(selectedPackage > counter || selectedPackage < 0){
        fprintf(stderr, "Error: entered number invalid: %d", selectedPackage);
    } else if(selectedPackage == 0){
        exit(0);
    } else {
        validManagers[selectedPackage - 1].delete(searchString);
        printf("%s has been successfully deleted\n", searchString);
    }
}