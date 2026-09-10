//Manager for apt-get

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <ctype.h>

#include "../include/structure.h"
#include "../include/managers/aptget.h"

bool UpdateApt(void){
    pid_t pid = fork();

    if(pid == -1){
        fprintf(stderr, "Error: Fork has failed");
        return -1;
    } else if (pid == 0){

        char *args[] = {"/usr/bin/sudo", "apt-get", "update", "-y", NULL};
        execv(args[0], args);

        fprintf(stderr, "Error: update for apt-get failed\n");
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
    strcpy(result.mana, "apt");

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
        if(dup2(pipefd[1], STDOUT_FILENO) == -1){
            fprintf(stderr, "Error: dup2 failed\n");
            exit(EXIT_FAILURE);
        }
        if(dup2(pipefd[1], STDERR_FILENO) == -1){
            fprintf(stderr, "Error: dup2 failed\n");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);

        char *args[] = {
            "/usr/bin/dpkg-query",
            "-W",
            "-f=${Package} ${Version}\n",
            searchstring,
            NULL
        };
        execv(args[0], args);

        fprintf(stderr, "Error: execv failed\n");
        exit(EXIT_FAILURE);
    }

    close(pipefd[1]);
    char buf[BUFFER_SIZE] = {0};
    size_t used = 0;
    ssize_t n;

    while((n = read(pipefd[0], buf + used, sizeof(buf) - 1 - used)) > 0){
        used += (size_t)n;
    }
    buf[used] = '\0';
    close(pipefd[0]);

    int status;
    waitpid(pid, &status, 0);
    if(WIFEXITED(status) && WEXITSTATUS(status) == 0){
        
        //check if package has been found
        if(buf[10] == ':'){
            return result;
        }  else {
            int lenName = 0, lenVersion;
            for(; buf[lenName] != ' ' && lenName < BUFFER_SIZE; lenName++){
                ;
            }
            strncpy(result.name, &(buf[0]), lenName);
            strcat(result.name, "\0");
            
            lenName++;
            for(lenVersion = lenName; buf[lenVersion] != '\n'; lenVersion++){
                ;
            }
            strncpy(result.version, &(buf[lenName]), lenVersion);
            strcat(result.version, "\0");
            return result;
        }

    } else {
        return result;
    }
}

package SearchApt(char searchString[]){
    package result = {0};
    int pipefd[2];
    strcpy(result.mana, "apt");

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
        if(dup2(pipefd[1], STDOUT_FILENO) == -1){
            fprintf(stderr, "Error: dup2 failed\n");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);

        char *args[] = {
            "/usr/bin/apt-cache",
            "madison",
            searchString,
            NULL
        };
        execv(args[0], args);

        fprintf(stderr, "Error: execv failed\n");
        exit(EXIT_FAILURE);
    }

    close(pipefd[1]);
    char buf[BUFFER_SIZE] = {0};
    size_t used = 0;
    ssize_t n;

    while((n = read(pipefd[0], buf + used, sizeof(buf) - 1 - used)) > 0){
        used += (size_t)n;
    }
    buf[used] = '\0';
    close(pipefd[0]);
    if(buf[0] == '\0'){
        return result;
    }
    int status;
    waitpid(pid, &status, 0);
    if(WIFEXITED(status) && WEXITSTATUS(status) == 0){
        
        //check if package has been found
        if(strncmp(buf, "N: Unable to locate package", 27) == 0){
            printf("Strncmp is not working\n");
            return result;
        }  else {

            int nameStart = 0, nameEnd, versionEnd;
            for(; isspace(buf[nameStart]) && nameStart < BUFFER_SIZE; nameStart++){
                ;
            }
            for(nameEnd = nameStart; !isspace(buf[nameEnd]); nameEnd++){
                ;
            }
            strncpy(result.name, &(buf[nameStart]), nameEnd - nameStart);
            strcat(result.name, "\0");
            
            for(++nameEnd; buf[nameEnd] == ' ' || buf[nameEnd] == '|'; nameEnd++){
                ;
            }

            for(versionEnd = nameEnd; !isspace(buf[versionEnd]); versionEnd++){
                ;
            }
            strncpy(result.version, &(buf[nameEnd]), versionEnd - nameEnd);
            strcat(result.version, "\0");
            return result;
        }

    } else {
        printf("Exit status not successfull\n");
        return result;
    }
}

bool InstallApt(char searchString[]){
    int pipefd[2];

    if (pipe(pipefd) == -1){
        fprintf(stderr, "Error: pipe failed\n");
        return false;
    }

    pid_t pid = fork();
    if(pid == -1){
        fprintf(stderr, "Error: fork failed\n");
        close(pipefd[0]);
        close(pipefd[1]);
        return false;
    }

    if (pid == 0){
        close(pipefd[0]);
        if(dup2(pipefd[1], STDOUT_FILENO) == -1){
            fprintf(stderr, "Error: dup2 failed\n");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);

        char *args[] = {
            "/usr/bin/sudo",
            "apt-get",
            "install",
            "-y",
            searchString,
            NULL
        };
        execv(args[0], args);

        fprintf(stderr, "Error: execv failed\n");
        exit(EXIT_FAILURE);
    }

    close(pipefd[1]);
    char buf[BUFFER_SIZE] = {0};
    size_t used = 0;
    ssize_t n;

    while((n = read(pipefd[0], buf + used, sizeof(buf) - 1 - used)) > 0){
        used += (size_t)n;
    }
    buf[used] = '\0';
    close(pipefd[0]);

    int status;
    waitpid(pid, &status, 0);
    if(WIFEXITED(status) && WEXITSTATUS(status) == 0){
        //I am assuming the package exists, since they need to be found with search first
        return true;

    } else {
        printf("Exit status not successfull\n");
        return false;
    }
}

bool DeleteApt(char searchString[]){
    int pipefd[2];

    if (pipe(pipefd) == -1){
        fprintf(stderr, "Error: pipe failed\n");
        return false;
    }

    pid_t pid = fork();
    if(pid == -1){
        fprintf(stderr, "Error: fork failed\n");
        close(pipefd[0]);
        close(pipefd[1]);
        return false;
    }

    if (pid == 0){
        close(pipefd[0]);
        if(dup2(pipefd[1], STDOUT_FILENO) == -1){
            fprintf(stderr, "Error: dup2 failed\n");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);

        char *args[] = {
            "/usr/bin/sudo",
            "apt-get",
            "remove",
            "-y",
            searchString,
            NULL
        };
        execv(args[0], args);

        fprintf(stderr, "Error: execv failed\n");
        exit(EXIT_FAILURE);
    }

    close(pipefd[1]);
    char buf[BUFFER_SIZE] = {0};
    size_t used = 0;
    ssize_t n;

    while((n = read(pipefd[0], buf + used, sizeof(buf) - 1 - used)) > 0){
        used += (size_t)n;
    }
    buf[used] = '\0';
    close(pipefd[0]);

    int status;
    waitpid(pid, &status, 0);
    if(WIFEXITED(status) && WEXITSTATUS(status) == 0){
        //I am assuming the package exists, since they need to be found with search first
        return true;

    } else {
        printf("Exit status not successfull\n");
        return false;
    }
}

manager APTGETMana(void){
    manager aptMana = {"apt", UpdateApt, FindApt, SearchApt, InstallApt, DeleteApt};
    return aptMana;
}