// Main file for Mana: evaluate arguments and make appropriate calls

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/update.h"
#include "../include/find.h"
#include "../include/search.h"
#include "../include/delete.h"

#define VERSION "0.1.0"

int main(int argc, char *argv[]){
    char helptext[] = "Package manager manager\n" 
                    "Mana includes several tools to manage multiple package managers,\n"
                    "which are:\n"
                    "apt/aptget\n"
                    "npm\n"
                    "brew/homebrew\n"
                    "nix\n\n"
                    "Commands:\n"
                    "\tupdate\t\t\t: update packages across all managers\n"
                    "\tfind <package>\t\t: find which package manager has <package> installed\n"
                    "\tsearch <package>\t: See which manager has a package available and which version\n"
                    "\tdelete <package>\t: Find all packages with the name and select which should be deleted\n"
                    ;
    

    //evaluate arguments and make the correct call accordingly
    if(argc == 1){
        printf("%s\n", helptext);
        return 0;
    } else if(argc > 3){
        fprintf(stderr, "error: too many arguments\n");
        exit(EXIT_FAILURE);
    } else {

        for(int i = 1; i < argc; i++){
            if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0){
                printf("%s", helptext);
                return 0;
            } else if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0){
                printf("%s\n", VERSION);
            }
        }
        
        // check for all commands
        if(strcmp(argv[1], "update") == 0){
            if(argc == 2){
                update();
            } else {
                fprintf(stderr, "Error: too many arguments for update\n");
                exit(EXIT_FAILURE);
            }
        } else if(strcmp(argv[1], "find") == 0){
            if(argc == 3){
                find(argv[2]);
            } else {
                fprintf(stderr, "Error: missing argument\nmana find <package>\n");
                exit(EXIT_FAILURE);
            }
        } else if(strcmp(argv[1], "search") == 0){
            if(argc == 3){
                search(argv[2]);
            } else {
                fprintf(stderr, "Error: missing argument\nmana search <package>\n");
                exit(EXIT_FAILURE);
            }
        } else if(strcmp(argv[1], "delete") == 0){
            if(argc == 3){
                delete(argv[2]);
            } else {
                fprintf(stderr, "Error: missing argument\nmana delete <package>");
                exit(EXIT_FAILURE);
            }
        }
    }
}