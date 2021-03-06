CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic
#LDFLAGS = -lraylib -lglfw -lSDL2 -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
BIN = xxx
ASM = xxx.S
VERS= -std=c99
PREFIX ?= /usr/local
DBG= debugxxx

all: $(BIN)

#config.h: config.def.h
#	cp config.def.h config.h

SRC = src/etr.c src/filecreation.c #config.h

etr.o: src/etr.c
	$(CC) -c $(SRC) $(CFLAGS)

filecreation.o: src/filecreation.c
	$(CC) -c src/filecreation.c $(CFLAGS)

language.o: src/language.c
	$(CC) -c src/language.c $(CFLAGS)

OBJ = etr.o filecreation.o language.o

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(LDFLAGS) $(VERS)

assembly: xxx
	$(CC) -S $(OBJ) -o $(ASM) $(LDFLAGS)

debug: xxx
	$(CC) -g $(OBJ) -o $(DBG) $(LDFLAGS) $(VERS)

#install: xxx
#	mkdir -p ${DESTDIR}${PREFIX}/bin
#	cp -f xxx ${DESTDIR}${PREFIX}/bin

#uninstall:
#	rm -f ${DESTDIR}${PREFIX}/bin/xxx

clean:
	rm -f xxx

.PHONY: all install uninstall clean

