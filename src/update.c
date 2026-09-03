#include <stdio.h>
#include <stdlib.h>

#include "../include/update.h"
#include "../include/structure.h"

#include "../include/managers/aptget.h"
#include "../include/managers/brew.h"
#include "../include/managers/nix.h"
#include "../include/managers/npm.h"


void update(){
    manager managers[NUM_MANAS];
    managers[0] = APTGETMana();
    managers[1] = HOMEBREWMana();
    managers[2] = NIXMana();
    managers[3] = NPMMana();

    bool success;
    int i;

    for(i = 0; i < NUM_MANAS; i++){
        success = managers[i].update();
        if(!success){
            printf("Error: manager %s has not updated successfully\n", managers[i].name);
        } else {
            printf("%s updates\n", managers[i].name);
        }
    }
    printf("Finished updating all managers\n");
}