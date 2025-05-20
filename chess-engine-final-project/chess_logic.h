// Kaza-Zack Kazirukanyo
// Lab11: Mini Final Project (Chess)
//"chess_logic.h"
#ifndef CHESS_LOGIC_H
#define CHESS_LOGIC_H

#include <stdbool.h>

/** Piece types in chess */
typedef enum {
    NONE, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
} PieceType;

/** Colors for chess pieces */
typedef enum {
    WHITE, BLACK, NO_COLOR
} Color;

/** Structure for a chess piece */
typedef struct {
    PieceType type;
    Color color;
    bool hasMoved;
} Piece;

/** Possible game status outcomes */
typedef enum {
    ONGOING, WHITE_WON, BLACK_WON, DRAW
} GameStatus;

/** Structure representing the full game state */
typedef struct {
    Piece board[8][8];     /**< 8x8 board of pieces */
    Color turn;            /**< Whose turn it is (WHITE or BLACK) */
    GameStatus status;     /**< Current game status */
    bool gameOver;         /**< Flag if game is over (checkmate, draw, stalemate) */
    int selectedRow;       /**< Selected piece row (or -1 if none) */
    int selectedCol;       /**< Selected piece column (or -1 if none) */
    int en_passant_col;    /**< Column of en passant target square (-1 if none) */
    int en_passant_row;    /**< Row of en passant target square (-1 if none) */
    int squareSize;        /**< Size of each square in pixels (for graphics) */
} GameState;

/** Initializes the game state with the standard starting position. */
void init_game(GameState *game);

/**
 * Attempts to move a piece from (srcRow, srcCol) to (destRow, destCol).
 * Enforces all chess rules including castling, en passant, promotion, and checks.
 * Updates game status if the move ends the game.
 * Returns true if the move is valid and executed, false otherwise.
 */
bool move_piece(GameState *game, int srcRow, int srcCol, int destRow, int destCol);

#endif

