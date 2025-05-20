// Kaza-Zack Kazirukanyo
#include "chess_logic.h"
#include <stdio.h>
#include <stdlib.h>
// Chess Logic Engine — built with precision, tested by fire.
// Handles all core rules of chess: movement, check, mate, promotion, and chaos.
// And yes, it also handles en passent, Ramzi! Tsk, mechanical engineers.

// Flag to suppress output messages (used during move testing for legal moves)
static int suppressOutput = 0;

// Internal helper prototypes
static bool is_in_check(const GameState *game, Color color);
static bool is_square_attacked(const GameState *game, Color byColor, int row, int col);
static bool has_any_legal_moves(GameState *game, Color color);

// Initialize game state with starting chess positions
void init_game(GameState *game) {
    // Clear board
    for(int r = 0; r < 8; ++r) {
        for(int c = 0; c < 8; ++c) {
            game->board[r][c].type = NONE;
            game->board[r][c].color = NO_COLOR;
            game->board[r][c].hasMoved = false;
        }
    }
    // Place pawns
    for(int c = 0; c < 8; ++c) {
        game->board[6][c].type = PAWN;
        game->board[6][c].color = WHITE;
        game->board[6][c].hasMoved = false;
        game->board[1][c].type = PAWN;
        game->board[1][c].color = BLACK;
        game->board[1][c].hasMoved = false;
    }
    // Rooks
    game->board[7][0].type = ROOK;  game->board[7][0].color = WHITE; game->board[7][0].hasMoved = false;
    game->board[7][7].type = ROOK;  game->board[7][7].color = WHITE; game->board[7][7].hasMoved = false;
    game->board[0][0].type = ROOK;  game->board[0][0].color = BLACK; game->board[0][0].hasMoved = false;
    game->board[0][7].type = ROOK;  game->board[0][7].color = BLACK; game->board[0][7].hasMoved = false;
    // Knights
    game->board[7][1].type = KNIGHT; game->board[7][1].color = WHITE; game->board[7][1].hasMoved = false;
    game->board[7][6].type = KNIGHT; game->board[7][6].color = WHITE; game->board[7][6].hasMoved = false;
    game->board[0][1].type = KNIGHT; game->board[0][1].color = BLACK; game->board[0][1].hasMoved = false;
    game->board[0][6].type = KNIGHT; game->board[0][6].color = BLACK; game->board[0][6].hasMoved = false;
    // Bishops
    game->board[7][2].type = BISHOP; game->board[7][2].color = WHITE; game->board[7][2].hasMoved = false;
    game->board[7][5].type = BISHOP; game->board[7][5].color = WHITE; game->board[7][5].hasMoved = false;
    game->board[0][2].type = BISHOP; game->board[0][2].color = BLACK; game->board[0][2].hasMoved = false;
    game->board[0][5].type = BISHOP; game->board[0][5].color = BLACK; game->board[0][5].hasMoved = false;
    // Queens
    game->board[7][3].type = QUEEN; game->board[7][3].color = WHITE; game->board[7][3].hasMoved = false;
    game->board[0][3].type = QUEEN; game->board[0][3].color = BLACK; game->board[0][3].hasMoved = false;
    // Kings
    game->board[7][4].type = KING;  game->board[7][4].color = WHITE; game->board[7][4].hasMoved = false;
    game->board[0][4].type = KING;  game->board[0][4].color = BLACK; game->board[0][4].hasMoved = false;
    // Initial turn and status
    game->turn = WHITE;
    game->status = ONGOING;
    game->gameOver = false;
    // No selection initially
    game->selectedRow = -1;
    game->selectedCol = -1;
    // No en passant target
    game->en_passant_col = -1;
    game->en_passant_row = -1;
}

bool move_piece(GameState *game, int srcRow, int srcCol, int destRow, int destCol) {
    if(game->gameOver) return false;

    if(srcRow < 0 || srcRow > 7 || srcCol < 0 || srcCol > 7 ||
       destRow < 0 || destRow > 7 || destCol < 0 || destCol > 7)
        return false;

    Piece *srcPiece = &game->board[srcRow][srcCol];
    Piece *destPiece = &game->board[destRow][destCol];

    if(srcPiece->type == NONE || srcPiece->color != game->turn) return false;
    if(destPiece->type != NONE && destPiece->color == srcPiece->color) return false;
    if(srcRow == destRow && srcCol == destCol) return false;

    Color currentColor = game->turn;
    Color opponentColor = (currentColor == WHITE ? BLACK : WHITE);
    PieceType ptype = srcPiece->type;
    int dr = destRow - srcRow;
    int dc = destCol - srcCol;
    bool valid = false;
    bool isCastling = false;

    // --- Movement Rules ---
    if(ptype == PAWN) {
        int forward = (currentColor == WHITE ? -1 : 1);
        if(dc == 0) {
            if(dr == forward && destPiece->type == NONE) valid = true;
            if(dr == 2*forward && !srcPiece->hasMoved &&
               destPiece->type == NONE &&
               game->board[srcRow + forward][srcCol].type == NONE) valid = true;
        }
        if(abs(dc) == 1 && dr == forward) {
            if(destPiece->type != NONE && destPiece->color == opponentColor) valid = true;
            else if(destPiece->type == NONE &&
                    game->en_passant_row == destRow && game->en_passant_col == destCol) valid = true;
        }
    } else if(ptype == KNIGHT) {
        if((abs(dr) == 2 && abs(dc) == 1) || (abs(dr) == 1 && abs(dc) == 2)) valid = true;
    } else if(ptype == BISHOP && abs(dr) == abs(dc)) {
        valid = true;
        for(int i = 1; i < abs(dr); i++)
            if(game->board[srcRow + i*(dr/abs(dr))][srcCol + i*(dc/abs(dc))].type != NONE)
                valid = false;
    } else if(ptype == ROOK && (dr == 0 || dc == 0)) {
        valid = true;
        for(int i = 1; i < (dr ? abs(dr) : abs(dc)); i++)
            if(game->board[srcRow + (dr ? i*(dr/abs(dr)) : 0)]
                      [srcCol + (dc ? i*(dc/abs(dc)) : 0)].type != NONE)
                valid = false;
    } else if(ptype == QUEEN && (dr == 0 || dc == 0 || abs(dr) == abs(dc))) {
        valid = true;
        for(int i = 1; i < (abs(dr) > abs(dc) ? abs(dr) : abs(dc)); i++) {
            int rr = srcRow + (dr ? i*(dr/abs(dr)) : 0);
            int cc = srcCol + (dc ? i*(dc/abs(dc)) : 0);
            if(rr == destRow && cc == destCol) break;
            if(game->board[rr][cc].type != NONE) valid = false;
        }
    } else if(ptype == KING) {
        if(abs(dc) == 2 && dr == 0 && !srcPiece->hasMoved && !is_in_check(game, currentColor)) {
            int rookCol = (dc == 2) ? 7 : 0;
            Piece *rook = &game->board[srcRow][rookCol];
            if(rook->type == ROOK && rook->color == currentColor && !rook->hasMoved) {
                bool pathClear = true;
                for(int i = 1; i < abs(dc); i++) {
                    int cc = srcCol + i*(dc/abs(dc));
                    if(game->board[srcRow][cc].type != NONE ||
                       is_square_attacked(game, opponentColor, srcRow, cc)) {
                        pathClear = false;
                        break;
                    }
                }
                if(pathClear) {
                    isCastling = true;
                    valid = true;
                }
            }
        } else if(abs(dr) <= 1 && abs(dc) <= 1) valid = true;
    }

    if(!valid) return false;

    GameState newState = *game;
    Piece *newSrc = &newState.board[srcRow][srcCol];
    Piece *newDest = &newState.board[destRow][destCol];
    Piece movingPiece = *newSrc;

    // Apply the move
    newSrc->type = NONE;
    newSrc->color = NO_COLOR;
    newSrc->hasMoved = false;

    if(ptype == PAWN && destPiece->type == NONE && srcCol != destCol) {
        int captureRow = (currentColor == WHITE ? destRow + 1 : destRow - 1);
        newState.board[captureRow][destCol].type = NONE;
        newState.board[captureRow][destCol].color = NO_COLOR;
        newState.board[captureRow][destCol].hasMoved = false;
    }

    newDest->type = movingPiece.type;
    newDest->color = movingPiece.color;
    newDest->hasMoved = true;

    if(ptype == PAWN && (destRow == 0 || destRow == 7))
        newDest->type = QUEEN;

    if(isCastling) {
        int rookSrcCol = (dc == 2 ? 7 : 0);
        int rookDestCol = (dc == 2 ? 5 : 3);
        newState.board[srcRow][rookDestCol] = newState.board[srcRow][rookSrcCol];
        newState.board[srcRow][rookSrcCol].type = NONE;
        newState.board[srcRow][rookSrcCol].color = NO_COLOR;
        newState.board[srcRow][rookSrcCol].hasMoved = false;
        newState.board[srcRow][rookDestCol].hasMoved = true;
    }

    newState.en_passant_col = (ptype == PAWN && abs(dr) == 2) ? srcCol : -1;
    newState.en_passant_row = (ptype == PAWN && abs(dr) == 2) ? srcRow + dr/2 : -1;

    if(is_in_check(&newState, currentColor)) return false;

    *game = newState;
    game->turn = opponentColor;
    game->selectedRow = -1;
    game->selectedCol = -1;

    bool oppInCheck = is_in_check(game, opponentColor);

    // Add recursion guard here
    if (suppressOutput > 10) return true;

    bool oppHasMoves = has_any_legal_moves(game, opponentColor);

    if(oppInCheck && !oppHasMoves) {
        game->status = (opponentColor == WHITE ? BLACK_WON : WHITE_WON);
        game->gameOver = true;
        if(!suppressOutput)
            printf("Checkmate! %s wins.\n", opponentColor == WHITE ? "Black" : "White");
    } else if(!oppInCheck && !oppHasMoves) {
        game->status = DRAW;
        game->gameOver = true;
        if(!suppressOutput)
            printf("Stalemate. It's a draw.\n");
    } else {
        game->status = ONGOING;
        game->gameOver = false;
        if(oppInCheck && !suppressOutput)
            printf("Check!\n");
    }

    return true;
}

// Check if the king of the given color is in check (attacked by any opponent piece)
static bool is_in_check(const GameState *game, Color color) {
    int kr = -1, kc = -1;
    for(int r = 0; r < 8 && kr == -1; ++r) {
        for(int c = 0; c < 8; ++c) {
            if(game->board[r][c].type == KING && game->board[r][c].color == color) {
                kr = r; kc = c;
                break;
            }
        }
    }
    if(kr == -1) return false;

    Color opp = (color == WHITE ? BLACK : WHITE);

    for(int r = 0; r < 8; ++r) {
        for(int c = 0; c < 8; ++c) {
            Piece piece = game->board[r][c];
            if(piece.type == NONE || piece.color != opp) continue;

            int dr = kr - r, dc = kc - c;
            int abs_dr = abs(dr), abs_dc = abs(dc);

            switch(piece.type) {
                case PAWN:
                    if((opp == WHITE && dr == -1 && abs_dc == 1) ||
                       (opp == BLACK && dr == 1 && abs_dc == 1))
                        return true;
                    break;

                case KNIGHT:
                    if((abs_dr == 2 && abs_dc == 1) || (abs_dr == 1 && abs_dc == 2))
                        return true;
                    break;

                case BISHOP:
                    if(abs_dr == abs_dc) {
                        int stepR = dr > 0 ? 1 : -1, stepC = dc > 0 ? 1 : -1;
                        int rr = r + stepR, cc = c + stepC;
                        while(rr != kr && cc != kc) {
                            if(game->board[rr][cc].type != NONE) break;
                            rr += stepR; cc += stepC;
                        }
                        if(rr == kr && cc == kc) return true;
                    }
                    break;

                case ROOK:
                    if(dr == 0 || dc == 0) {
                        int stepR = (dr == 0 ? 0 : (dr > 0 ? 1 : -1));
                        int stepC = (dc == 0 ? 0 : (dc > 0 ? 1 : -1));
                        int rr = r + stepR, cc = c + stepC;
                        while(rr != kr || cc != kc) {
                            if(game->board[rr][cc].type != NONE) break;
                            rr += stepR; cc += stepC;
                        }
                        if(rr == kr && cc == kc) return true;
                    }
                    break;

                case QUEEN:
                    if(dr == 0 || dc == 0 || abs_dr == abs_dc) {
                        int stepR = (dr == 0 ? 0 : (dr > 0 ? 1 : -1));
                        int stepC = (dc == 0 ? 0 : (dc > 0 ? 1 : -1));
                        int rr = r + stepR, cc = c + stepC;
                        while(rr != kr || cc != kc) {
                            if(game->board[rr][cc].type != NONE) break;
                            rr += stepR; cc += stepC;
                        }
                        if(rr == kr && cc == kc) return true;
                    }
                    break;

                case KING:
                    if(abs_dr <= 1 && abs_dc <= 1) return true;
                    break;

                default: break;
            }
        }
    }
    return false;
}

// Check if any piece of 'byColor' can attack the square (row, col)
static bool is_square_attacked(const GameState *game, Color byColor, int row, int col) {
    for(int r = 0; r < 8; ++r) {
        for(int c = 0; c < 8; ++c) {
            Piece piece = game->board[r][c];
            if(piece.type == NONE || piece.color != byColor) continue;

            int dr = row - r, dc = col - c;
            int abs_dr = abs(dr), abs_dc = abs(dc);

            switch(piece.type) {
                case PAWN:
                    if((byColor == WHITE && dr == -1 && abs_dc == 1) ||
                       (byColor == BLACK && dr == 1 && abs_dc == 1))
                        return true;
                    break;

                case KNIGHT:
                    if((abs_dr == 2 && abs_dc == 1) || (abs_dr == 1 && abs_dc == 2))
                        return true;
                    break;

                case BISHOP:
                    if(abs_dr == abs_dc) {
                        int stepR = dr > 0 ? 1 : -1, stepC = dc > 0 ? 1 : -1;
                        int rr = r + stepR, cc = c + stepC;
                        while(rr != row && cc != col) {
                            if(game->board[rr][cc].type != NONE) break;
                            rr += stepR; cc += stepC;
                        }
                        if(rr == row && cc == col) return true;
                    }
                    break;

                case ROOK:
                    if(dr == 0 || dc == 0) {
                        int stepR = (dr == 0 ? 0 : (dr > 0 ? 1 : -1));
                        int stepC = (dc == 0 ? 0 : (dc > 0 ? 1 : -1));
                        int rr = r + stepR, cc = c + stepC;
                        while(rr != row || cc != col) {
                            if(game->board[rr][cc].type != NONE) break;
                            rr += stepR; cc += stepC;
                        }
                        if(rr == row && cc == col) return true;
                    }
                    break;

                case QUEEN:
                    if(dr == 0 || dc == 0 || abs_dr == abs_dc) {
                        int stepR = (dr == 0 ? 0 : (dr > 0 ? 1 : -1));
                        int stepC = (dc == 0 ? 0 : (dc > 0 ? 1 : -1));
                        int rr = r + stepR, cc = c + stepC;
                        while(rr != row || cc != col) {
                            if(game->board[rr][cc].type != NONE) break;
                            rr += stepR; cc += stepC;
                        }
                        if(rr == row && cc == col) return true;
                    }
                    break;

                case KING:
                    if(abs_dr <= 1 && abs_dc <= 1) return true;
                    break;

                default: break;
            }
        }
    }
    return false;
}

// Determine if the given color has any legal move available (for stalemate/checkmate detection)
static bool has_any_legal_moves(GameState *game, Color color) {
    if(game->gameOver) return false;
    // Save current turn and temporarily set turn to the color we want to test
    Color originalTurn = game->turn;
    game->turn = color;
    suppressOutput++;  // suppress console messages during simulation
    bool foundMove = false;
    for(int r = 0; r < 8 && !foundMove; ++r) {
        for(int c = 0; c < 8 && !foundMove; ++c) {
            if(game->board[r][c].type == NONE || game->board[r][c].color != color) continue;
            for(int rr = 0; rr < 8 && !foundMove; ++rr) {
                for(int cc = 0; cc < 8 && !foundMove; ++cc) {
                    if(r == rr && c == cc) continue;
                    if(game->board[rr][cc].type != NONE && game->board[rr][cc].color == color) continue;
                    GameState tempState = *game;
                    if(move_piece(&tempState, r, c, rr, cc)) {
                        foundMove = true;
                    }
                }
            }
        }
    }
    suppressOutput--;
    game->turn = originalTurn;
    return foundMove;
}

