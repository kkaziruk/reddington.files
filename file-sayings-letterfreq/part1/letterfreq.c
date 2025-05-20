// Kaza-Zack Kazirukanyo
// letterfreq.c
// The program asks the user for a file name, reads the file one character at a time, and counts how often each letter (A-Z) appears, ignoring case. It stores the counts in an array of 26 numbers and displays the results.

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define A_SIZE 26

int main(void) {

    FILE *fp;
    char filename[31];

    printf("\033[H\033[J");

    // Program header
    printf("--------------------------------------------------\n");
    printf("             LETTER FREQUENCY COUNTER             \n");
    printf("--------------------------------------------------\n");
    printf("This program reads a file and counts the frequency \n");
    printf("of each letter (A-Z), ignoring case.\n\n");

    // Prompt user for file name
    printf("Enter the name of the file you want to analyze: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;  // Remove the newline character if present

    fp = fopen(filename, "r");

    // Check if file opened successfully
    if (!fp) {
        printf("\nError: File '%s' not found.\n", filename);
        return 1;
    }

    int l_freq[A_SIZE] = {0}; // Frequency array for letters
    int ltr = 0; // number of letters
    int ctr = 0; // number of characters
    int ch; // character being read
    int index; // index for the letter

    // Start processing the file
    printf("\nProcessing file: %s\n", filename);
    printf("--------------------------------------------\n");

    // Read the file and count letter frequencies
    while ((ch = fgetc(fp)) != EOF) {
        ctr++; // increment for every character read

        if (isalpha(ch)) {
            ch = tolower(ch); // handles uppercase letters
            index = ch - 'a'; // calculate index for letter frequency
            l_freq[index]++;
            ltr++; // increment only for letters
        }
    }

    // Display results in a neat format
    printf("\n------------------- RESULTS -------------------\n");

    // Total number of characters
    printf("\nTotal number of characters: %d\n", ctr);

    // Total number of letters
    printf("Total number of letters: %d\n", ltr);

    // Scrabble point values for each letter
    int scrabble_points[A_SIZE] = {
        1, 1, 3, 3, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 3, 10, 1, 1, 1, 1, 2, 4, 4, 8, 4, 10
    };

    // Display Scrabble points and compare to frequency
    printf("\n-- Scrabble Points vs Frequency --\n");
    for (int i = 0; i < A_SIZE; i++) {
        if (l_freq[i] > 0) {
            printf("%-c: %-d occurrences | %-d points per letter\n", i + 'a', l_freq[i], scrabble_points[i]);
        }
    }

    // Calculating total Scrabble points based on the frequency of each letter
    int total_points = 0;
    for (int i = 0; i < A_SIZE; i++) {
        total_points += l_freq[i] * scrabble_points[i];
    }

    printf("\nTotal Scrabble points based on letter frequencies: %d\n", total_points);


    // Displaying letter percentages
    printf("\n-- Letter Percentages --\n");
    for (int i = 0; i < (sizeof(l_freq)/sizeof(int)); i++) {
        printf("%-c: %-.1f%%\n", i + 'a',(((float)l_freq[i]/(float)ltr))*100);
    }

    printf("\n--------------------------------------------------\n");
    printf("Thank you for using the Letter Frequency Counter!\n");
    printf("--------------------------------------------------\n");

    fclose(fp);

    return 0;
}

