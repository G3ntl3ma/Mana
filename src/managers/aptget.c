//Manager for apt-get

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

#include "../include/structure.h"
#include "../include/managers/aptget.h"

bool UpdateApt(void){
    pid_t pid = fork();

    if(pid == -1){
        fprintf(stderr, "Error: Fork has failed");
        return -1;
    } else if (pid == 0){

        char *args[] = {"/usr/bin/apt-get", "update", "-y"};
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

package FindApt(char searchstring[]){
    package result = {0};
    int pipefd[2];
    result.mana = "apt";

    if (pipe(pipefd) == -1){
        fprintf(stderr, "Error: pipe failed\n");
        return result;
    }

    pid_t pid = fork();
    if(pid == -1){
        fprintf(stderr, "Error: fork failed\n");
        close(pipefd[0]);
        close(pipefd[1]);
        return result;
    }

    if (pid == 0){
        close(pipefd[0]);
        if(dup2(pipefd[1], STDOUT_FILENO == -1)){
            fprintf(stderr, "Error: dup2 failed\n");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);

        char *args[] = {
            "/usr/bin/dpkg-query",
            "-W",
            "-f='${Package} ${Version}\n'",
            searchstring,
            NULL
        };
        execv(args[0], args);

        fprintf(stderr, "Error: execv failed\n");
        exit(EXIT_FAILURE);
    }

    close(pipefd[1]);

    char buf[4096];
    ssize_t n;
    size_t used = 0;
    char output[4096] = {0};

    while ((n = read(pipefd[0], buf, sizeof(buf))) > 0){
        if (used + (size_t)n >= sizeof(output)){
            break;
        }
        memcpy(output + used, buf, (size_t)n);
        used += (size_t)n;
    }
    close(pipefd[0]);

    int status;
    waitpid(pid, &status, 0);
    if(WIFEXITED(status) && WEXITSTATUS(status) == 0){
        
        //check if package has been found
        if(strcmp(output[10], ":") == 0){
            return result;
        }  else {
            int lenName = 0, lenVersion;
            for(;strcmp(output[lenName], " ") != 0; lenName++){
                ;
            }
            strncpy(result.name, output[0], lenName);
            strcat(result.name, "\0");
            for(lenVersion = lenName; strcmp(output[lenVersion], "\n") != 0; lenVersion++){
                ;
            }
            strncpy(result.version, output[lenName], lenVersion);
            strcat(result.version, "\0");
        }

    } else {
        return 0;
    }
}

package SearchApt(char searchString[]){
    package result = {0};
    printf("SearchApt function is not implemented yet: %s\n", searchString);
    return result;
}

bool DeleteApt(char searchString[]){
    printf("DeleteApt function is not implemented yet: %s\n", searchString);
    return false;
}

manager APTGETMana(void){
    manager aptMana = {"apt", UpdateApt, FindApt, SearchApt, DeleteApt};
    return aptMana;
}