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

int launchNormal(char **args);

int launchPiped(char **args, int pipeIndex, int totalArgsNumber);

int launchRedirect(char **args, int redirectIndex, int totalArgsNumber, int out);

int launchInRedirect(char **args, int redirectIndex, int totalArgsNumber);

#endif //ISODEV_EXEC_H
