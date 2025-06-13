CC = gcc
CFLAGS = -Wall -Iinclude -Wextra -Wpedantic
SRC = main.c src/cresult.c
OUT = build/main

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT); ./build/main
