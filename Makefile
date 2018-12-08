# Erkam BAYINDIR
# Muaz KARATAŞ
# Yusuf Taha ÖZTÜRK
# Nuh YURDUSEVEN
# Kadir Doğuş SEÇKİN
CC=gcc -g
CFLAGS=-c -Wall -I ./include
SRC=./src
LIB=./lib
BIN=./bin
EXEFILE=isOdev


compileAndRun: compile
#	clear
	$(BIN)/$(EXEFILE)

compile: main
	$(CC) $(LIB)/util.o $(LIB)/exec.o $(LIB)/main.o -o $(BIN)/$(EXEFILE)

util: $(SRC)/util.c
	$(CC) $(CFLAGS) $(SRC)/util.c -o $(LIB)/util.o

exec: util $(SRC)/exec.c
	$(CC) $(CFLAGS) $(SRC)/exec.c -o $(LIB)/exec.o

main: util exec $(SRC)/main.c
	$(CC) $(CFLAGS) $(SRC)/main.c -o $(LIB)/main.o
