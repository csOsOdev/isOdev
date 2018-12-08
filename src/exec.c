//
// Created by user12043 on 08.12.2018.
//
// Erkam BAYINDIR
// Muaz KARATAŞ
// Yusuf Taha ÖZTÜRK
// Nuh YURDUSEVEN
// Kadir Doğuş SEÇKİN

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "exec.h"
#include "util.h"

int execute(char **args) {
    int status = 0;
    int counter = 0;
    char *arg;

    // Built-in komut kontrol
    if (args[0] == NULL || strcmp(args[0], "\0") == 0) {
        return status;
    } else if (strcmp(args[0], "quit") == 0 || strcmp(args[0], "exit") == 0) {
        // TODO arka plan bekle
        exit(0);
    } else if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            printError("give a target location after 'cd'");
        } else if (chdir(args[1]) != 0) {
            printError("cd unsuccessful");
        }
        return status;
    }

    int pipeIndex = -1;
    int redirectIndex = -1;

    while ((arg = args[counter]) != NULL) {
//        printf("%s\n", arg);
        if (strcmp(arg, "|") == 0) {
            pipeIndex = counter;
            printf("pipe: %d\n", pipeIndex);
        } else if ((strcmp(arg, ">") == 0) || (strcmp(arg, "<") == 0)) {
            redirectIndex = counter;
            printf("redirection: %d\n", redirectIndex);
        }
        counter++;
    }

    if (pipeIndex != -1) {
        status = launchPiped(args, pipeIndex, counter);
    } else if (redirectIndex != -1) {
        if ((strcmp(args[redirectIndex], ">") == 0)) {
            launchRedirect(args, redirectIndex, counter, 1);
        } else {
            launchRedirect(args, redirectIndex, counter, 0);
        }
    } else {
        status = launchNormal(args);
    }

    return status;
}

int launchNormal(char **args) {
    int status = 0;
    pid_t pid = fork();
    if (pid == 0) {
        // child
        if (execvp(args[0], args) == -1) {
            printError("failed to execute process");
            return -1;
        }
    } else if (pid > 0) {
        // parent
        waitpid(pid, &status, WUNTRACED); // cocuk processin durumunu rapor et
    } else {
        printError("fork failed");
        exit(EXIT_FAILURE);
    }
    return status;
}

int launchPiped(char **args, int pipeIndex, int totalArgsNumber) {
    int status = 0;
    char **beforePipe = malloc(sizeof(char *) * pipeIndex);
    for (int i = 0; i < pipeIndex; ++i) {
        beforePipe[i] = args[i];
    }

    int afterPipeLength = totalArgsNumber - pipeIndex - 1;
    char **afterPipe = malloc(sizeof(char *) * afterPipeLength);
    for (int i = 0; i < afterPipeLength; ++i) {
        afterPipe[i] = args[pipeIndex + i + 1];
    }

    int pfd[2];
    if (pipe(pfd) == -1) {
        printError("could not create pipe");
        return -1;
    }
    pid_t pid1 = fork();
    if (pid1 == 0) {
        // cocuk
        close(pfd[0]);
        dup2(pfd[1], STDOUT_FILENO);
//        close(pfd[1]);

        if (execvp(beforePipe[0], beforePipe) == -1) {
            printError("failed to execute process: %d", getpid());
            return -1;
        }
    } else if (pid1 > 0) {
        // parent
        pid_t pid2 = fork();
        if (pid2 == 0) {
            // cocuk
            close(pfd[1]);
            dup2(pfd[0], STDIN_FILENO);
            close(pfd[0]);
            if (execvp(afterPipe[0], afterPipe) == -1) {
                printError("failed to execute process: %d", getpid());
                return -1;
            }
        } else if (pid2 > 0) {
            //parent
            int status1;
            int status2;
            /*wait(&status2);
            wait(&status1);*/
            waitpid(pid1, &status1, WUNTRACED);
            printf("process %d exited with code: %d\n", pid1, status1);
            close(pfd[1]);
            waitpid(pid2, &status2, WUNTRACED);
            printf("process %d exited with code: %d\n", pid2, status2);
            /*wait(NULL);
            wait(NULL);*/
        } else {
            printError("fork failed");
            exit(EXIT_FAILURE);
        }
    } else {
        printError("fork failed");
        exit(EXIT_FAILURE);
    }

    free(beforePipe);
    free(afterPipe);
    return status;
}

int launchRedirect(char **args, int redirectIndex, int totalArgsNumber, int out) {
    int status = 0;
    char **beforeRedirect = malloc(sizeof(char *) * redirectIndex);
    for (int i = 0; i < redirectIndex; ++i) {
        beforeRedirect[i] = args[i];
    }

    int afterRedirectLength = totalArgsNumber - redirectIndex - 1;
    char **afterRedirect = malloc(sizeof(char *) * afterRedirectLength);
    for (int i = 0; i < afterRedirectLength; ++i) {
        afterRedirect[i] = args[redirectIndex + i + 1];
    }

    pid_t pid = fork();
    printf("aha pid bu: %i\n", pid);
    if (pid == 0) {
        // cocuk
        FILE *ioFile = fopen(afterRedirect[0], "r+");
        if (out) {
            dup2(fileno(ioFile), STDOUT_FILENO);
        } else {
            dup2(STDOUT_FILENO, fileno(ioFile));
        }
        if (execvp(beforeRedirect[0], beforeRedirect) == -1) {
            printError("failed to execute process: %d", getpid());
            fclose(ioFile);
            return -1;
        }
        fclose(ioFile);
    } else if (pid > 0) {
        // parent
        wait(NULL);
    } else {
        printError("fork failed");
        exit(EXIT_FAILURE);
    }

    free(beforeRedirect);
    free(afterRedirect);
    return status;
}

int launchInRedirect(char **args, int redirectIndex, int totalArgsNumber) {
    int status = 0;
    return status;
}
