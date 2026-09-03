#include <stdio.h>
#include <stdlib.h>

#include "../include/search.h"
#include "../include/structure.h"

#include "../include/managers/aptget.h"
#include "../include/managers/brew.h"
#include "../include/managers/nix.h"
#include "../include/managers/npm.h"

void search(char searchString[]){
    manager managers[NUM_MANAS];
    managers[0] = APTGETMana();
    managers[1] = HOMEBREWMana();
    managers[2] = NIXMana();
    managers[3] = NPMMana();

    package packages[NUM_MANAS];
    manager validManagers[NUM_MANAS];
    int i;
    int counter = 1;
    int selectedPackage = 0;

    for(i = 0; i < NUM_MANAS; i++){
        packages[i] = managers[i].search(searchString);
        if(packages[i].name[0] != '\0'){
            printf("%d: %s | %s | %s\n", counter, packages[i].mana, packages[i].name, packages[i].version);
            validManagers[counter - 1] = managers[i];
            counter++;
        }
    }

    printf("\nType the number in front of the manager to install the package. Type 0 to quit\n");
    scanf("%d", &selectedPackage);
    if(selectedPackage > counter || selectedPackage < 0){
        fprintf(stderr, "Error: entered number invalid: %d", selectedPackage);
    } else if(selectedPackage == 0){
        exit(0);
    } else {
        validManagers[selectedPackage - 1].install(searchString);
        printf("%s has been successfully installed\n", searchString);
    }
}