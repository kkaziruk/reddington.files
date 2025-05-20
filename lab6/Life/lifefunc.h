// Kaza-Zack Kazirukanyo
// lifefunc.h
// Lab6: play Life
// Header file for Conway's Game of Life

#ifndef LIFEFUNC_H
#define LIFEFUNC_H

#define BOARD_SIZE 40

void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]);
void displayBoard(char board[BOARD_SIZE][BOARD_SIZE]);
void addCell(char board[BOARD_SIZE][BOARD_SIZE], int x, int y);
void removeCell(char board[BOARD_SIZE][BOARD_SIZE], int x, int y);
void advance(char board[BOARD_SIZE][BOARD_SIZE]);
int countNeighbors(char board[BOARD_SIZE][BOARD_SIZE], int x, int y);
void copyBoard(char source[BOARD_SIZE][BOARD_SIZE], char destination[BOARD_SIZE][BOARD_SIZE]);

#endif

