// Kaza-Zack Kazirukanyo (1900 ELO)
// Lab11: Mini Final Project: Chess!!
// "gfx_chess.c"
// WARNING: Contains traces of strategy, caffeine, and raw rook energy.

#include "gfx_chess.h"
#include "gfx.h"
#include <math.h>

// ♟️ Color definitions for board aesthetics and visual clarity
#define COLOR_LIGHT_R 240
#define COLOR_LIGHT_G 217
#define COLOR_LIGHT_B 181
#define COLOR_DARK_R 181
#define COLOR_DARK_G 136
#define COLOR_DARK_B 99
#define COLOR_HIGHLIGHT_R 255
#define COLOR_HIGHLIGHT_G 0
#define COLOR_HIGHLIGHT_B 0
#define COLOR_WHITE_R 255
#define COLOR_WHITE_G 255
#define COLOR_WHITE_B 255
#define COLOR_BLACK_R 0
#define COLOR_BLACK_G 0
#define COLOR_BLACK_B 0

// Initializes the graphics window and stores the square size in the game state
void gfx_chess_init(GameState *game, int squareSize) {
    if (squareSize < 20) squareSize = 20;  // Don’t make it microscopic
    game->squareSize = squareSize;
    int width = 8 * squareSize;
    int height = 8 * squareSize;
    gfx_open(width, height, "Chess Game"); // Welcome to the battlefield
}

// Draw a filled circle for pawns and minimalist art snobs
static void draw_circle(int cx, int cy, int radius) {
    for (int dy = -radius; dy <= radius; ++dy) {
        int dx_limit = (int)floor(sqrt(radius * radius - dy * dy));
        int y = cy + dy;
        gfx_line(cx - dx_limit, y, cx + dx_limit, y);
    }
}

// Draw an upward-pointing triangle — aka The Knight
static void draw_triangle(int cx, int cy, int size) {
    int halfSize = size / 2;
    int topY = cy - halfSize;
    int bottomY = cy + halfSize;
    for (int y = topY; y <= bottomY; ++y) {
        double progress = (double)(y - topY) / (double)(bottomY - topY);
        int halfWidth = (int)(halfSize * progress);
        int leftX = cx - halfWidth;
        int rightX = cx + halfWidth;
        gfx_line(leftX, y, rightX, y);
    }
}

// Draw the board, highlight selection, and render every piece
void draw_board(const GameState *game) {
    int squareSize = game->squareSize;

    // 🎨 Draw the 8x8 battlefield
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (((r + c) % 2) == 0) {
                gfx_color(COLOR_LIGHT_R, COLOR_LIGHT_G, COLOR_LIGHT_B);
            } else {
                gfx_color(COLOR_DARK_R, COLOR_DARK_G, COLOR_DARK_B);
            }
            int x0 = c * squareSize;
            int y0 = r * squareSize;
            for (int y = y0; y < y0 + squareSize; ++y) {
                gfx_line(x0, y, x0 + squareSize - 1, y);
            }
        }
    }

    //  Highlight the selected square — strategy is brewing - Mikhail Tal
    if (game->selectedRow >= 0 && game->selectedCol >= 0) {
        int selR = game->selectedRow;
        int selC = game->selectedCol;
        int x0 = selC * squareSize;
        int y0 = selR * squareSize;
        int x1 = x0 + squareSize - 1; 
        int y1 = y0 + squareSize - 1;
        gfx_color(COLOR_HIGHLIGHT_R, COLOR_HIGHLIGHT_G, COLOR_HIGHLIGHT_B);
        gfx_line(x0, y0, x1, y0); // top
        gfx_line(x0, y1, x1, y1); // bottom
        gfx_line(x0, y0, x0, y1); // left
        gfx_line(x1, y0, x1, y1); // right
    }

    //  Draw each piece — low style points but high efficiency - Antony Karpov
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece piece = game->board[r][c];
            if (piece.type == NONE) continue;

            // Set piece color
            if (piece.color == WHITE) {
                gfx_color(COLOR_WHITE_R, COLOR_WHITE_G, COLOR_WHITE_B);
            } else {
                gfx_color(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
            }

            int cx = c * squareSize + squareSize / 2;
            int cy = r * squareSize + squareSize / 2;
            int pieceSize = (3 * squareSize) / 8;
            if (pieceSize < 1) pieceSize = 1;
            int half = pieceSize / 2;

            // Represent pieces 
            switch (piece.type) {
                case PAWN: {
                    int radius = (half * 2) / 3;
                    if (radius < 1) radius = 1;
                    draw_circle(cx, cy, radius);
                    break;
                }
                case ROOK: {
                    for (int y = cy - half; y <= cy + half; ++y) {
                        gfx_line(cx - half, y, cx + half, y);
                    }
                    break;
                }
                case KNIGHT: {
                    draw_triangle(cx, cy, pieceSize); // Galloping into battle
                    break;
                }
                case BISHOP: {
                    gfx_line(cx - half, cy - half, cx + half, cy + half);
                    gfx_line(cx - half, cy + half, cx + half, cy - half);
                    break;
                }
                case KING: {
                    gfx_line(cx, cy - half, cx, cy + half);
                    gfx_line(cx - half, cy, cx + half, cy);
                    break;
                }
                case QUEEN: {
                    gfx_line(cx, cy - half, cx, cy + half);
                    gfx_line(cx - half, cy, cx + half, cy);
                    gfx_line(cx - half, cy - half, cx + half, cy + half);
                    gfx_line(cx - half, cy + half, cx + half, cy - half);
                    break;
                }
                default:
                    break;
            }
        }
    }

    gfx_flush(); //  Now showing: 'House of Pawns', staring FundComp mechanical engineers
}

