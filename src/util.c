//
// Created by user12043 on 03.12.2018.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"

char *readCommand() {
    char *line = malloc(sizeof(char) * BUFFER_SIZE);
    if (!line) {
        printf(ALLOCATION_ERROR);
        exit(EXIT_FAILURE);
    }
    int size = 0;
    size_t length = BUFFER_SIZE;
    while (63) {
        char c = (char) getchar();
        // Break loop on end
        if (c == EOF || c == '\n') {
            line[size++] = '\0';
            break;
        }
        if (size < length) {
            line[size++] = c;
        } else {
            length *= 2;
            line = realloc(line, length);
            line[size++] = c;
        }
    }
    printf("length: %d\n", size);
    return line;
}

char **parseCommand(char *line) {
    char **args = malloc(ARGUMENTS_SIZE * sizeof(char *));
    if (!args) {
        printf(ALLOCATION_ERROR);
        exit(EXIT_FAILURE);
    }
    size_t argsLength = ARGUMENTS_SIZE;
    int argCounter = 0;
    char *argument = malloc(sizeof(char) * ARGUMENT_SIZE);
    if (!argument) {
        printf(ALLOCATION_ERROR);
        exit(EXIT_FAILURE);
    }
    size_t argumentLength = ARGUMENT_SIZE;
    int counter = 0;
    size_t lineLength = strlen(line);
    for (int i = 0; i <= lineLength; ++i) {
        char c = line[i];
        if (c == ' ' || c == '\0') {
            if (argCounter >= argsLength) {
                argsLength *= 2;
                args = realloc(args, (argsLength * sizeof(char *)));
            }
            args[argCounter] = argument;
            argCounter++;
            argument = malloc(ARGUMENT_SIZE * sizeof(char));
            argumentLength = ARGUMENT_SIZE;
            counter = 0;
        } else {
            if (counter >= argumentLength) {
                argumentLength *= 2;
                argument = realloc(argument, (argumentLength * sizeof(char)));
            }
            argument[counter++] = c;
        }
    }

    return args;
}
