FILES=main.cpp grafo.cpp
OUT=grafo
CC=g++
WARN=-Wall
FLAGS=

all: GRAFOS

GRAFOS: $(FILES)
	$(CC) $(WARN) -o $(OUT) $(FILES) $(FLAGS)

.PHONY: all
