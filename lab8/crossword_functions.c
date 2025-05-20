// Kaza-Zack Kazirukanyo
// crossword_functions.c

#define _GNU_SOURCE        
#include "crossword.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>


/* initialise_board(...)
   This function initializes the board by filling every cell with '.'
   representing an empty cell.
   */
void initialise_board(char board[BOARD_L][BOARD_L]) {
    for (int i = 0; i < BOARD_L; i++) {
        for (int j = 0; j < BOARD_L; j++) {
            board[i][j] = '.';
        }
    }
}

/* is_alpha(...)
   This function checks whether a given string contains only alphabetic characters.
   It's used to validate user input before processing.
   */
int is_alpha(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha((unsigned char)str[i])) return 0;
    }
    return 1;
}

/* to_upper(...)
   This function converts a user-input string to uppercase.
   */
void to_upper(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

/* sort_words(...)
   This function sorts words in descending order of their length using bubble sort.
   */
void sort_words(Word words[], int count) {
    Word temp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (strlen(words[j].word) < strlen(words[j + 1].word)) {
                temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;
            }
        }
    }
}

/* read_words(...)
   This function reads words from a given input source (stdin or file pointer).
   It accepts only valid words and gracefully handles non-valid entries.
   */
int read_words(Word words[], FILE *fp) {
    int count = 0;
    char entry[MAX_LETTERS];

    while (count < MAX_WORDS && fscanf(fp, "%15s", entry) == 1) {
        int len = strlen(entry);

        // Exit when the user enters a period
        if (strcmp(entry, ".") == 0) break;

        // If word ends with '.', treat it as end-of-input marker
        if (entry[len - 1] == '.') {
            entry[len - 1] = '\0';
            if (strlen(entry) > 1 && is_alpha(entry)) {
                to_upper(entry);
                strcpy(words[count].word, entry);
                words[count].placed = 0;
                count++;
            }
            break;  // Stop after adding this last word
        }

        if (is_alpha(entry) && strlen(entry) > 1) {
            to_upper(entry);
            strcpy(words[count].word, entry);
            words[count].placed = 0;
            count++;
        } else {
            printf("\tError: '%s' has been ignored. Valid entries are 2-15 letters.\n", entry);
        }
    }

    return count;
}

/* is_valid_adjacent(...)
   This helper function checks whether a specific cell on the board is:
   1. Within the bounds of the grid (i.e rows [0,14] and cols [0,14]).
   2. Currently empty (i.e filled with a '.').
   We want to ensure that all words on the puzzle board do not touch except at valid intersection points.
   */
int is_valid_adjacent(char board[BOARD_L][BOARD_L], int row, int col) {
    return (row >= 0 && row < BOARD_L && col >= 0 && col < BOARD_L && board[row][col] == '.');
}

/* count_overlaps(...)
   This function checks if a word can be placed at a given position on the board, validating the position
   based on existing overlaps. count_overlaps ensures that the word intersects properly with existing words.
   */
int count_overlaps(char board[BOARD_L][BOARD_L], const char *word, int row, int col, char direction) {
    int overlaps = 0;
    int len = strlen(word);
    int future_score = 0;

    for (int i = 0; i < len; i++) {
        int r = (direction == 'A') ? row : row + i;
        int c = (direction == 'A') ? col + i : col;

        if (r < 0 || r >= BOARD_L || c < 0 || c >= BOARD_L) return -1;

        if (board[r][c] == word[i]) {
            overlaps++;
        } else if (board[r][c] == '.') {
            if (r > 0 && board[r - 1][c] == '.') future_score++;
            if (r < BOARD_L - 1 && board[r + 1][c] == '.') future_score++;
            if (c > 0 && board[r][c - 1] == '.') future_score++;
            if (c < BOARD_L - 1 && board[r][c + 1] == '.') future_score++;

            if (direction == 'A') {
                if ((r > 0 && board[r - 1][c] != '.') || (r < BOARD_L - 1 && board[r + 1][c] != '.'))
                    return -1;
            } else {
                if ((c > 0 && board[r][c - 1] != '.') || (c < BOARD_L - 1 && board[r][c + 1] != '.'))
                    return -1;
            }
        } else {
            return -1;
        }
    }

    if ((direction == 'A' && col > 0 && board[row][col - 1] != '.') ||
        (direction == 'A' && col + len < BOARD_L && board[row][col + len] != '.') ||
        (direction == 'D' && row > 0 && board[row - 1][col] != '.') ||
        (direction == 'D' && row + len < BOARD_L && board[row + len][col] != '.')) {
        return -1;
    }

    if (overlaps == 0) return -1;

    return overlaps * 3 + future_score;
}
/* find_best_placement(...)
   This function finds the best place to put a new word by considering two factors:
   1. Overlaps (how well the word fits with already placed words).
   2. Future space (how much free space there is around the word to allow future placements).

   We loop through all the words already placed on the board to check where the new word can intersect with them.
   For each intersection, we:
   a) check how many letters from the new word match with the letters already placed on the board (overlap count);
   b) calculate the free space around the potential word placement. This means checking how many empty cells
   are next to the new word in all directions (left, right, up, and down).

   The function returns the best intersection where the word can fit
   This is the place where the word overlaps the most with existing words and leaves the most free space around it.
   */
int find_best_placement(Word words[], int count, char board[BOARD_L][BOARD_L], int placedCount, const char *word, int *bestRow, int *bestCol, char *bestDir) {
    int bestScore = -1;
    int len = strlen(word);

    for (int row = 0; row < BOARD_L; row++) {
        for (int col = 0; col < BOARD_L; col++) {
            for (int d = 0; d < 2; d++) {
                char direction = (d == 0) ? 'A' : 'D';
                int score = count_overlaps(board, word, row, col, direction);
                if (score > bestScore) {
                    *bestRow = row;
                    *bestCol = col;
                    *bestDir = direction;
                    bestScore = score;
                }
            }
        }
    }

    return (bestScore >= 0);
}

/* place_word(...)
   Places a word on the board at the specified position (row, column) and direction ('A' for across, 'D' for down).
   Once placed, the word is marked as 'placed' in the words array (by setting the 'placed' flag to 1).
   */
void place_word(Word *w, char board[BOARD_L][BOARD_L]) {
    int len = strlen(w->word);
    for (int i = 0; i < len; i++) {
        int r = (w->direction == 'A') ? w->row : w->row + i;
        int c = (w->direction == 'A') ? w->col + i : w->col;
        board[r][c] = w->word[i];
    }
    w->placed = 1;
}

/* solve_puzzle(...)
   Attempts to place all words on the board, starting with the longest word at the center.
   It iterates through the remaining words, finding valid placements for each word with the `find_best_placement` function.
   If a word cannot be placed, it is skipped, and the function continues with the next word.
   The function also returns the number of successfully placed words.
   */
int solve_puzzle(Word words[], int count, char board[BOARD_L][BOARD_L]) {
    if (count == 0) return 0;

    // Ensure words are sorted by length so that the longest word comes first
    sort_words(words, count);

    // Place the longest word (now at index 0) in the middle of the board
    int startCol = (BOARD_L - strlen(words[0].word)) / 2;
    words[0].row = BOARD_L / 2;
    words[0].col = startCol;
    words[0].direction = 'A';  // Place the word horizontally (Across)
    place_word(&words[0], board);

    int placedCount = 1;

    // Try placing remaining words
    for (int i = 1; i < count; i++) {
        int row, col;
        char dir;

        // Attempt to find the best placement for the current word
        if (find_best_placement(words, count, board, placedCount, words[i].word, &row, &col, &dir)) {
            words[i].row = row;
            words[i].col = col;
            words[i].direction = dir;
            place_word(&words[i], board);
            placedCount++;
        } else {
            printf("Word '%s' is skipped; it could not be placed.\n", words[i].word);
            continue;  // Continue placing remaining words
        }
    }

    // Retry any skipped words and place them later.

    int morePlaced;
    do {
        morePlaced = 0;
        for (int i = 0; i < count; i++) {
            if (!words[i].placed) {
                int row, col;
                char dir; // Check if they are valid locations to place the words
                if (find_best_placement(words, count, board, placedCount, words[i].word, &row, &col, &dir)) {
                    words[i].row = row;
                    words[i].col = col;
                    words[i].direction = dir;
                    place_word(&words[i], board);
                    placedCount++;
                    morePlaced++;
                }
            }
        }
    } while (morePlaced > 0);

    return placedCount;
}

/* display_solution(...)
   Displays the completed crossword puzzle board (solution) by printing each row inside a bordered box.
   The solution shows the placement of all words on the board after they have been successfully placed.
*/
void display_solution(char board[BOARD_L][BOARD_L]) {
    printf("\nSolution:\n-----------------\n");
    for (int i = 0; i < BOARD_L; i++) {
        printf("|");
        for (int j = 0; j < BOARD_L; j++) {
            printf("%c", board[i][j]);
        }
        printf("|\n");
    }
    printf("-----------------\n");
}

/* display_puzzle(...)
   Displays the unsolved crossword puzzle board by printing each row inside a bordered box.
   Empty spots are represented by '#' characters, showing where words have not yet been placed.
*/
void display_puzzle(char board[BOARD_L][BOARD_L]) {
    printf("\nPuzzle:\n-----------------\n");
    for (int i = 0; i < BOARD_L; i++) {
        printf("|");
        for (int j = 0; j < BOARD_L; j++) {
            printf("%c", board[i][j] == '.' ? '#' : ' ');
        }
        printf("|\n");
    }
    printf("-----------------\n");
}

/* display_anagram_clues(...)
   Displays the clues for each placed word in the crossword puzzle.
   The clues consist of the word's location (row, column), the direction ('Across' or 'Down'),
   and a scrambled version of the word.
*/
void display_anagram_clues(Word words[], int count) {
    printf("\nCLUES:\nLocation | Direction | Anagram\n");
    for (int i = 0; i < count; i++) {
        if (!words[i].placed) continue;

        // Declare a temporary string to hold the scrambled word
        char scrambled[MAX_LETTERS];
        strcpy(scrambled, words[i].word);  // Copy the original word
        strfry(scrambled);  // Scramble the word

        printf("  %2d,%-2d  |  %-7s  | %s\n",
                words[i].row, words[i].col,
                (words[i].direction == 'A') ? "Across" : "Down",
                scrambled);
    }
}

/* play_guess_the_word(...)
   A simple game where the user has to guess the scrambled word.
   The user's score is tracked and displayed after all the guesses are made.
*/
void play_guess_the_word(Word words[], int count) {
    char guess[MAX_LETTERS];
    int score = 0, total = 0;

    for (int i = 0; i < count; i++) {
        if (!words[i].placed) continue;  // Skip words that are not placed

        total++;
        char scrambled[MAX_LETTERS];
        strcpy(scrambled, words[i].word);
        strfry(scrambled);  // Scramble the word

        printf("\nGuess the word: %s\n", scrambled);
        printf("Your guess: ");
        scanf("%15s", guess);
        to_upper(guess);

        if (strcmp(guess, words[i].word) == 0) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Nope! The correct word was: %s\n", words[i].word);
        }
    }

    printf("\nGame over! You got %d out of %d correct.\n", score, total);
}

/* save_to_file(...)
   Saves the solution (both the completed and unsolved puzzle) and the scrambled word clues to a specified file.
   The file is formatted neatly with a header, the crossword solution, the puzzle, and the scrambled clues.
*/
void save_to_file(char *filename, Word words[], int count, char board[BOARD_L][BOARD_L]) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stderr, "Error: Could not open file %s for writing.\n", filename);
        return;
    }

    fprintf(fp, "Solution:\n-----------------\n");
    for (int i = 0; i < BOARD_L; i++) {
        fprintf(fp, "|");
        for (int j = 0; j < BOARD_L; j++) {
            fprintf(fp, "%c", board[i][j]);
        }
        fprintf(fp, "|\n");
    }
    fprintf(fp, "-----------------\n\n");

    fprintf(fp, "Puzzle:\n-----------------\n");
    for (int i = 0; i < BOARD_L; i++) {
        fprintf(fp, "|");
        for (int j = 0; j < BOARD_L; j++) {
            fprintf(fp, "%c", board[i][j] == '.' ? '#' : ' ');
        }
        fprintf(fp, "|\n");
    }
    fprintf(fp, "-----------------\n\n");

    fprintf(fp, "CLUES:\nLocation | Direction | Anagram\n");
    for (int i = 0; i < count; i++) {
        if (!words[i].placed) continue;
        char scrambled[MAX_LETTERS];
        strcpy(scrambled, words[i].word);
        strfry(scrambled);
        fprintf(fp, "%2d,%-2d  | %-7s  | %s\n",
                words[i].row, words[i].col,
                (words[i].direction == 'A') ? "Across" : "Down",
                scrambled);
    }

    fclose(fp);
}
