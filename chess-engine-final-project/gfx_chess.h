// Kaza-Zack Kazirukanyo
// Lab 11: Mini Final Project
// gfx_chess.j
#ifndef GFX_CHESS_H
#define GFX_CHESS_H

#include "chess_logic.h"

// Initializes the graphics window (using gfx library).
// Also stores square size into the GameState.
void gfx_chess_init(GameState *game, int squareSize);

// Draws the entire chess board, all pieces, and highlights
// the selected square if one is active.
void draw_board(const GameState *game);

#endif

