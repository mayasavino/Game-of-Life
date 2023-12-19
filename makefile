CC=gcc
CFLAGS=-g -Wall
OBJFLAGS=-g -Wall -c 
SDL_CFLAGS=$(shell sdl2-config --cflags)
SDL_LDFLAGS=$(shell sdl2-config --libs) -lm
targets=logic life

# all targets to be compiled
all: $(targets)

logic: logic.c
	$(CC) $(OBJFLAGS) $@.c 

life: life.c logic.o sdl.o
	$(CC) $(CFLAGS) $(SDL_CFLAGS) $^ -o $@ $(SDL_LDFLAGS)

# clean it all up
clean:
	rm logic.o