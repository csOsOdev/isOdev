//
// Created by user12043 on 08.12.2018.
//
// Erkam BAYINDIR
// Muaz KARATAŞ
// Yusuf Taha ÖZTÜRK
// Nuh YURDUSEVEN
// Kadir Doğuş SEÇKİN

#ifndef ISODEV_EXEC_H
#define ISODEV_EXEC_H

#define BACKGROUND_PROCESSES 10

pid_t *backgroundProcesses;

void addBackgroundProcess(pid_t pid);

int launchNormal(char **args);

int launchPiped(char **args, int pipeIndex, int totalArgsNumber);

int launchRedirect(char **args, int redirectIndex, int totalArgsNumber, int out);

int launchBackground(char **args, int backgroundIndex, int totalArgsNumber);

#endif //ISODEV_EXEC_H
