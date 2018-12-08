//
// Created by user12043 on 03.12.2018.
//
// Erkam BAYINDIR
// Muaz KARATAŞ
// Yusuf Taha ÖZTÜRK
// Nuh YURDUSEVEN
// Kadir Doğuş SEÇKİN

#ifndef ISODEV_UTIL_H
#define ISODEV_UTIL_H

// Karakter okurken kullanilacak ilk uzunluk
#define BUFFER_SIZE 1024
// Argumanlari okurken kullanilacak ilk uzunluk
#define ARGUMENTS_SIZE 30
// Bir arguman uzunlugu icin kullanilacak ilk uzunluk
#define ARGUMENT_SIZE 20
// bellek ayirma hatasinda yazilacak hata mesaji
#define ALLOCATION_ERROR "Bellek tahsis edilirken hata olustu!"

char *readCommand();

char **parseCommand(char *line);

void printError(char *error, ...);

#endif //ISODEV_UTIL_H
