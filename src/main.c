//
// Created by user12043 on 02.12.2018.
//
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "util.h"

int main(int argc, char **argv) {
    printf("Hello, World!\n");
    return 0;
}

void prompt() {
    printf("isOdev:$ ");
}

char *read() {
    return "";
}

int execute(char **arguments) {
    int status = 0;
    return status;
}

void cycle() {
    prompt();
    char *line = read();
    char **arguments = parseLine(line);
    int status = execute(arguments);

    free(line);
    free(arguments);
    printf("process exited with status %d", status);
}
