// Kaza-Zack Kazirukanyo
// Lab11: Mini Final Project
// Chess: Main game loop (mouse + keyboard input)
// "project.c"

#include <stdlib.h>  // for atoi
#include <stdio.h>
#include <ctype.h>
#include "gfx.h"
#include "gfx_chess.h"
#include "chess_logic.h"

int main(int argc, char *argv[]) {
    int squareSize = 80;
    if (argc > 1) {
        int s = atoi(argv[1]);
        if (s >= 20 && s <= 200) {
            squareSize = s;
        }
    }

    // Initialize game state and graphics
    GameState game;
    init_game(&game);
    gfx_chess_init(&game, squareSize);
    draw_board(&game);

    printf("Use mouse to select and move pieces.\n");
    printf("Press 'r' to reset, 'q' to resign or quit.\n");

    // Main input loop
    int running = 1;
    while (running) {
        char c = gfx_wait();

        if (c == 1) {  // Left-click
            int mx = gfx_xpos();
            int my = gfx_ypos();
            int row = my / game.squareSize;
            int col = mx / game.squareSize;

            if (!game.gameOver) {
                if (game.selectedRow == -1 || game.selectedCol == -1) {
                    // Selecting a piece
                    Piece piece = game.board[row][col];
                    if (piece.type != NONE && piece.color == game.turn) {
                        game.selectedRow = row;
                        game.selectedCol = col;
                    }
                } else {
                    // Attempt to move selected piece
                    int srcR = game.selectedRow;
                    int srcC = game.selectedCol;
                    if (row == srcR && col == srcC) {
                        game.selectedRow = -1;
                        game.selectedCol = -1;
                    } else {
                        bool moved = move_piece(&game, srcR, srcC, row, col);
                        if (!moved) {
                            printf("Illegal move. Try again.\n");
                        }
                    }
                }
            }

            draw_board(&game);
        } else if (c == 3) {  // Right-click to cancel selection
            if (!game.gameOver && game.selectedRow != -1) {
                game.selectedRow = -1;
                game.selectedCol = -1;
                draw_board(&game);
            }
        } else if (c != 0) {
            // Keyboard input
            if (c == 'q' || c == 'Q') {
                if (!game.gameOver) {
                    if (game.turn == WHITE) {
                        printf("White resigns. Black wins.\n");
                        game.status = BLACK_WON;
                    } else {
                        printf("Black resigns. White wins.\n");
                        game.status = WHITE_WON;
                    }
                    game.gameOver = true;
                    draw_board(&game);
                } else {
                    running = 0;  // quit if already over
                }
            } else if (c == 'r' || c == 'R') {
                init_game(&game);
                draw_board(&game);
            }
        }
    }

    return 0;
}

