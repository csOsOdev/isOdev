//
// Created by user12043 on 02.12.2018.
//
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "util.h"


int main(int argc, char **argv) {
    int status;
    do {
        status = cycle();
    } while (status != 0);
    printf("exited with code: %d", status);
    return 0;
}

void prompt() {
    printf("isOdev:$ ");
}

int execute(char **arguments) {
    int status = 0;
    return status;
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
