#include <stdio.h>
#include <stdlib.h>

#include "../include/find.h"
#include "../include/structure.h"

#include "../include/managers/aptget.h"
#include "../include/managers/brew.h"
#include "../include/managers/nix.h"
#include "../include/managers/npm.h"

void find(char searchString[]){
    manager managers[NUM_MANAS];
    managers[0] = APTGETMana();
    managers[1] = HOMEBREWMana();
    managers[2] = NIXMana();
    managers[3] = NPMMana();

    package packages[NUM_MANAS];
    int i;

    for(i = 0; i < NUM_MANAS; i++){
        packages[i] = managers[i].find(searchString);
        if(packages[i].name[0] == '\0'){
            printf("%s: not available\n", packages[i].mana);
        } else {
            printf("%s: %s %s\n", packages[i].mana, packages[i].name, packages[i].version);
        }
    }
    
    
}