// Kaza-Zack Kazirukanyo
// lifefunc.c
// Lab6: play Life
// Functions for Conway's Game of Life

#include "lifefunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE + 2; i++) printf("-");
    printf("\n");

    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("|");
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c", board[i][j]);
        }
        printf("|\n");
    }

    for (int i = 0; i < BOARD_SIZE + 2; i++) printf("-");
    printf("\n");
}

void addCell(char board[BOARD_SIZE][BOARD_SIZE], int x, int y) {
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        board[x][y] = 'X';
    } else {
        printf("Warning: Cell (%d, %d) is out of bounds and cannot be added.\n", x, y);
    }
}

void removeCell(char board[BOARD_SIZE][BOARD_SIZE], int x, int y) {
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        board[x][y] = ' ';
    } else {
        printf("Warning: Cell (%d, %d) is out of bounds and cannot be removed.\n", x, y);
    }
}

int countNeighbors(char board[BOARD_SIZE][BOARD_SIZE], int x, int y) {
    int count = 0;
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && board[nx][ny] == 'X') {
            count++;
        }
    }
    return count;
}

void advance(char board[BOARD_SIZE][BOARD_SIZE]) {
    char tempBoard[BOARD_SIZE][BOARD_SIZE];

    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            tempBoard[x][y] = board[x][y];  // Copy board state
        }
    }

    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            int liveNeighbors = countNeighbors(board, x, y);
            if (board[x][y] == 'X') {
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    tempBoard[x][y] = ' ';
                }
            } else {
                if (liveNeighbors == 3) {
                    tempBoard[x][y] = 'X';
                }
            }
        }
    }

    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            board[x][y] = tempBoard[x][y];  // Copy new state back
        }
    }
}

void copyBoard(char source[BOARD_SIZE][BOARD_SIZE], char destination[BOARD_SIZE][BOARD_SIZE]) {
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            destination[x][y] = source[x][y];
        }
    }
}

