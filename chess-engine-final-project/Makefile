CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LIBS = -lX11 -lm

OBJS = project.o chess_logic.o gfx_chess.o  

all: project

project: $(OBJS)
	$(CC) $(OBJS) gfx.o -o $@ $(LIBS)   

project.o: project.c gfx_chess.h chess_logic.h gfx.h
	$(CC) $(CFLAGS) -c project.c

chess_logic.o: chess_logic.c chess_logic.h
	$(CC) $(CFLAGS) -c chess_logic.c

gfx_chess.o: gfx_chess.c gfx_chess.h chess_logic.h gfx.h
	$(CC) $(CFLAGS) -c gfx_chess.c

clean:
	rm -f project.o chess_logic.o gfx_chess.o project

