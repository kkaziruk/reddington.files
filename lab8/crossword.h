// Kaza-Zack Kazirukanyo
// crossword.h
#ifndef CROSSWORD_H
#define CROSSWORD_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BOARD_L 15       // Size of the crossword board (15x15)
#define MAX_LETTERS 16   // Max length of a word
#define MAX_WORDS 20   // Max number of words in the puzzle

/* Word structure to hold word details */
typedef struct {
    char word[MAX_LETTERS];  // Word itself
    int row;                 // Row position of the word
    int col;                 // Column position of the word
    char direction;          // 'A' for across, 'D' for down
    int placed;              // 0 if not placed, 1 if placed
} Word;

/* Function Declarations */
void initialise_board(char board[BOARD_L][BOARD_L]);
int is_alpha(const char *str);
void to_upper(char *str);
void sort_words(Word words[], int count);
int read_words(Word words[], FILE *fp);
int is_valid_adjacent(char board[BOARD_L][BOARD_L], int row, int col);
int count_overlaps(char board[BOARD_L][BOARD_L], const char *word, int row, int col, char direction);
int find_best_placement(Word words[], int count, char board[BOARD_L][BOARD_L], int placedCount, const char *word, int *bestRow, int *bestCol, char *bestDir);
void place_word(Word *w, char board[BOARD_L][BOARD_L]);
int solve_puzzle(Word words[], int count, char board[BOARD_L][BOARD_L]);
void display_solution(char board[BOARD_L][BOARD_L]);
void display_puzzle(char board[BOARD_L][BOARD_L]);
void display_anagram_clues(Word words[], int count);
void play_guess_the_word(Word words[], int count);
void save_to_file(char *filename, Word words[], int count, char board[BOARD_L][BOARD_L]);

#endif  // CROSSWORD_H

