CC = clang
CFLAGS = -std=c11 -pipe -g3
INCS = -I./inc 
LIBS_CLIENT = -lpthread -lcurses $(shell pkg-config --cflags --libs gtk+-3.0)

SRC=src

BIN_CLIENT = uchat
BIN_SERVER = uchat_server

CFILES_CLIENT = $(wildcard src/client/*.c) $(wildcard src/lib/*.c)
CFILES_SERVER = $(wildcard src/server/*.c) $(wildcard src/server/*/*.c) $(wildcard src/lib/*.c)

all: ${BIN_CLIENT} ${BIN_SERVER}

sqlite3:
	@make -sC libraries/sqlite3


${BIN_CLIENT}:
	@mkdir -p obj
	@mkdir -p build
	@cp -R src/resources build
	@${CC} ${CFLAGS} ${INCS} ${LIBS_CLIENT} ${CFILES_CLIENT} -o ${BIN_CLIENT}
	@mv ${BIN_CLIENT} build


${BIN_SERVER}: 
	@mkdir -p obj
	@mkdir -p build
	@${CC} ${CFLAGS} ${INCS} ${LIBS_CLIENT} ${CFILES_SERVER} -o ${BIN_SERVER}
	@mv ${BIN_SERVER} build


uninstall:
	@rm -rf build

clean:
	@rm -rf data
	@rm -rf obj

reinstall: uninstall all
