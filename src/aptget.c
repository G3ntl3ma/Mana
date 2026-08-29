//Manager for apt-get

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/structure.h"

int update(void){
    pid_t pid = fork();

    if(pid == -1){
        fprintf(stderr, "Error: Fork has failed");
        return -1;
    } else if (pid == 0){

        char *args[] = {"usr/bin/sudo", "apt-get", "update", "-y"};
        execv(args[0], args);

        fprintf(stderr, "Error: update for apt-get failed");
        exit(EXIT_FAILURE);
        return -1;
    } else {
    int status;
    waitpid(pid, &status, 0);

    if(WIFEXITED(status) && WEXITSTATUS(status) == 0){
        return 1;
    } else {
        return 0;
    }
    }
}