// Kaza-Zack Kazirukanyo
// futurecount.c
// An attempt to use a "future looking" algorithm to effectively place words.

/* calculate_future_score(...)
   Calculates the "future score" based on free spaces available around a word's proposed placement.
   This is my CREATIVE (but not comprehensively proven) attempt to think beyond basic validation,
   and select intersections that leave the most room for future word placements.
        > This idea comes from my love of chess, and the necessity to consider how to optimize
          the position of a piece on the board to maximise it's utlity later in the game.

   Simply put, the future score helps us evaluate the "flexibility" of a word placement:
     1. For horizontal (Across), we consider the available free spaces to the left, right,
        above, and below each letter.
     2. For vertical (Down), we consider spaces above and below, as well as horizontally
        left and right of each letter.

   Hypothesis (Why this matters):
   By prioritizing intersections with more "free space" for future placements, we prevent "clogging" the grid
   and (hopefully) enable better puzzle completion, maximising the number of words we can
   successfully place on the board.
*/
int calculate_future_score(char board[BOARD_L][BOARD_L], const char *word, int row, int col, char direction) {
    int free_space_score = 0;
    int len = strlen(word);

    if (direction == 'A') {  // Horizontal placement (Across)
        // Check left of the word
        for (int i = col - 1; i >= 0 && board[row][i] == '.'; i--) {
            free_space_score++;  // Increment score for each free space
        }

        // Check right of the word
        for (int i = col + len; i < BOARD_L && board[row][i] == '.'; i++) {
            free_space_score++;  // Increment score for each free space
        }

        // Check vertically above and below each letter in the word
        for (int i = 0; i < len; i++) {
            if (row > 0 && board[row - 1][col + i] == '.') {
                free_space_score++;  // Space above each letter
            }
            if (row + 1 < BOARD_L && board[row + 1][col + i] == '.') {
                free_space_score++;  // Space below each letter
            }
        }

    } else {  // Vertical placement (Down)
        // Check above the word
        for (int i = row - 1; i >= 0 && board[i][col] == '.'; i--) {
            free_space_score++;  // Increment score for each free space
        }

        // Check below the word
        for (int i = row + len; i < BOARD_L && board[i][col] == '.'; i++) {
            free_space_score++;  // Increment score for each free space
        }

        // Check horizontally left and right of each letter in the word
        for (int i = 0; i < len; i++) {
            if (col > 0 && board[row + i][col - 1] == '.') {
                free_space_score++;  // Space to the left of each letter
            }
            if (col + 1 < BOARD_L && board[row + i][col + 1] == '.') {
                free_space_score++;  // Space to the right of each letter
            }
        }
    }

    return free_space_score;
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

    for (int i = 0; i < placedCount; i++) {
        char *placedWord = words[i].word;
        int placedRow = words[i].row;
        int placedCol = words[i].col;
        char placedDir = words[i].direction;

        for (int j = 0; j < strlen(word); j++) {
            for (int k = 0; k < strlen(placedWord); k++) {
                if (word[j] != placedWord[k]) continue;

                int row, col;
                char newDir = (placedDir == 'A') ? 'D' : 'A';

                // Calculate the potential placement for the word
                if (newDir == 'A') {
                    row = placedRow + k - j;
                    col = placedCol - j;
                } else {
                    row = placedRow - j;
                    col = placedCol + k;
                }

                // Calculate the overlap score and future score for this placement
                int score = count_overlaps(board, word, row, col, newDir) +
                            calculate_future_score(board, word, row, col, newDir);

                // Choose the placement with the highest combined score
                if (score > bestScore) {
                    *bestRow = row;
                    *bestCol = col;
                    *bestDir = newDir;
                    bestScore = score;
                }
            }
        }
    }

    return (bestScore >= 0);
}

 
