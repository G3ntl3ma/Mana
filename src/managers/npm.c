//Manager for brew

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <ctype.h>

#include "../include/structure.h"
#include "../include/managers/npm.h"

bool UpdateNpm(void){
    pid_t pid = fork();

    if(pid == -1){
        fprintf(stderr, "Error: Fork has failed");
        return -1;
    } else if (pid == 0){

        char *args[] = {"/home/linuxbrew/.linuxbrew/bin/npm",
             "update",
              "-g",
               NULL
            };
        execv(args[0], args);

        fprintf(stderr, "Error: update for npm failed\n");
        exit(EXIT_FAILURE);
        return -1;
    } else {

        int status;
        waitpid(pid, &status, 0);

        if(WIFEXITED(status) && WEXITSTATUS(status) == 0){
            return true;
        } else {
            return false;
        }
    }
}

package FindNpm(char searchString[]){
    package result = {0};
    int pipefd[2];
    strcpy(result.mana, "npm");

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
             "/home/linuxbrew/.linuxbrew/bin/npm",
             "list",
             "-g",
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
        int nameStart = 0, nameEnd, versionEnd;
        //if the package has been found, it will automatically be here, so no need for a thorough check;
        for(; buf[nameStart] != '\n'; nameStart++){
            ;
        }
        for(; !isalpha(buf[nameStart]); nameStart++){
            ;
        }
        for(nameEnd = nameStart; buf[nameEnd] != '@'; nameEnd++);
        strncpy(result.name, &(buf[nameStart]), nameEnd - nameStart);

        for(++nameEnd, versionEnd = nameEnd; buf[versionEnd] != '\n'; versionEnd++){
            ;
        }

        strncpy(result.version, &(buf[nameEnd]), versionEnd - nameEnd);

        return result;
    } else {
        return result;
    }
}

package SearchNpm(char searchString[]){
    package result = {0};
    int pipefd[2];
    strcpy(result.mana, "npm");

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
            "/home/linuxbrew/.linuxbrew/bin/npm",
            "view",
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
        int nameStart = 0, nameEnd, versionEnd;
        for(; !isalnum(buf[nameStart]); nameStart++){
            ;
        }
        for(nameEnd = nameStart; buf[nameEnd] != '@'; nameEnd++){
            ;
        }
        strncpy(result.name, &(buf[nameStart]), nameEnd - nameStart);
        
        for(++nameEnd, versionEnd = nameEnd; !isspace(buf[versionEnd]); versionEnd++){
            ;
        }
        strncpy(result.version, &(buf[nameEnd]), versionEnd - nameEnd);
        return result;
    } else {
        printf("Exit status not successfull, npm\n");
        return result;
    }
}

bool InstallNpm(char searchString[]){
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
            "/home/linuxbrew/.linuxbrew/bin/npm",
            "install",
            "-g",
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

bool DeleteNpm(char searchString[]){
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
            "/home/linuxbrew/.linuxbrew/bin/npm",
            "uninstall",
            "-g",
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

manager NPMMana(void){
    manager npmMana = {"npm", UpdateNpm, FindNpm, SearchNpm, InstallNpm, DeleteNpm};
    return npmMana;
}