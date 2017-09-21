FILES=main.cpp grafo.cpp
OUT=grafo
CC=g++
WARN=-Wall
FLAGS=-fmax-errors=3

all: GRAFOS

GRAFOS: $(FILES)
	$(CC) $(WARN) -o $(OUT) $(FILES) $(FLAGS)

.PHONY: all
