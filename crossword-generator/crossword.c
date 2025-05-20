// crossword_functions.c
// Kaza-Zack Kazirukanyo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "crossword.h"

int main(int argc, char *argv[]) {
    Word words[MAX_WORDS];
    char board[BOARD_L][BOARD_L];
    int word_count = 0;

    // Situation 1: If there are two arguments (file input and output file)
    if (argc == 3) {
        FILE *input_file = fopen(argv[1], "r");
        if (!input_file) {
            printf("Error: Could not open input file %s\n", argv[1]);
            return 1;
        }

        // Read words from the file
        word_count = read_words(words, input_file);
        fclose(input_file);

        // Solve the puzzle
        initialise_board(board);
        solve_puzzle(words, word_count, board);

        // Save solution to output file
        save_to_file(argv[2], words, word_count, board);
        printf("Puzzle, solution, and clues saved to %s.\n", argv[2]);

        return 0;  // Exit after saving the solution
    }

    // Situation 2: If there's one argument (input file)
    else if (argc == 2) {
        FILE *input_file = fopen(argv[1], "r");
        if (!input_file) {
            printf("Error: Could not open file %s\n", argv[1]);
            return 1;
        }

        // Read words from the file
        word_count = read_words(words, input_file);
        fclose(input_file);
    }
    // Situation 3: No file provided, read words from user input
    else {
        printf("Please enter your words (end with '.'):\n");
        word_count = read_words(words, stdin);
    }

    // Initialise the board and solve the puzzle
    initialise_board(board);
    solve_puzzle(words, word_count, board);

    // Display the menu
    int choice;
    while (choice != 5) {
        printf("\nMenu:\n");
        printf("1. Display Puzzle\n");
        printf("2. Display Solution\n");
        printf("3. Display Anagram Clues\n");
        printf("4. Play Guess the Word\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        // Ensure valid input for the menu choice
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input, please enter a number between 1 and 5.\n");
            while(getchar() != '\n');  // Clear the invalid input
            continue;
        }

        switch (choice) {
            case 1:
                display_puzzle(board);
                break;
            case 2:
                display_solution(board);
                break;
            case 3:
                display_anagram_clues(words, word_count);
                break;
            case 4:
                play_guess_the_word(words, word_count);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option, please try again.\n");
        }
    }

    return 0;
}

