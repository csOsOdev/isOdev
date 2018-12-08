//
// Created by user12043 on 02.12.2018.
//
// Erkam BAYINDIR
// Muaz KARATAŞ
// Yusuf Taha ÖZTÜRK
// Nuh YURDUSEVEN
// Kadir Doğuş SEÇKİN

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
#include "util.h"

// Arka plan islemleri icin sayac
int backgroundProcessesNumber = 0;

int main(int argc, char **argv) {
    int status;
    do {
        status = cycle();
    } while (status == 0);
    printf("\nexited with code: %d\n", status);
    return 0;
}

void prompt() {
    fflush(stdout);
    // Calisma klasorunu tespit et
    long max = pathconf(".", _PC_PATH_MAX);
    size_t pathSize;
    if (max == -1) {
        pathSize = 4096;
    } else if (max > 10240) {
        pathSize = 10240;
    } else {
        pathSize = (size_t) max;
    }
    char *path = malloc(sizeof(char) * pathSize);
    if (path == NULL) {
        printError(ALLOCATION_ERROR);
        exit(EXIT_FAILURE);
    }
    getcwd(path, pathSize); // path stringine calisma klasorunu ata
    // Promptu yaz
    char *username = getenv("USER");
    printf("%s:%s$ ", username, path);
    free(path);
}

int cycle() {
    prompt();
    char *line = readCommand();
    char **arguments = parseCommand(line);
    int status = execute(arguments);

    free(line);
    free(arguments);
    return status;
}
