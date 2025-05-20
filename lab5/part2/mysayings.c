// Kaza-Zack Kazirukanyo
// A program to read an initial “startup” file of sayings into a 2D array, let the user display them, add new ones, search by substring, and save all sayings to a new file before quitting.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Constants
#define MAXNUM 50     // Maximum number of sayings
#define MAX 256       // Maximum length of each saying

// Function Prototypes
void intro_display(void);
void get_filename(char filename[], size_t size);
int read_sayings(FILE *fp, char sayings[][MAX]);
void display_sayings(const char sayings[][MAX], int count);
int add_saying(char sayings[][MAX], int count);
void search_sayings(const char sayings[][MAX], int count);
void save_sayings(const char sayings[][MAX], int count);

int main(void) {
    // Clear screen and display program header
    intro_display();

    // Prompt user for startup file
    char filename[31]; // store up to 30 characters + '\0'
    get_filename(filename, sizeof(filename));

    // Attempt to open the file for reading
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("\nError: File '%s' not found.\n", filename);
        return 1; 
    }

    // Create a 2D array to hold all sayings
    char sayings[MAXNUM][MAX];

    // Read the sayings from file
    int count = read_sayings(fp, sayings);
    fclose(fp);

    // Let the user know how many sayings were loaded
    printf("\nLoaded %d sayings from file: %s\n", count, filename);

    // Main menu loop
    int choice;
    do {
        // Display the menu
        printf("\n---------------------------\n");
        printf("           MENU           \n");
        printf("---------------------------\n");
        printf("1) Display all sayings\n");
        printf("2) Add a new saying\n");
        printf("3) Search for a substring\n");
        printf("4) Save sayings to a file\n");
        printf("5) Quit\n");
        printf("Enter your choice (1-5): ");

        // Read user choice
        if (scanf("%d", &choice) != 1) {
            // if invalid input is entered
            printf("Invalid input. Please enter a number 1-5.\n");
            // Clear the buffer manually if needed
            while (getchar() != '\n'); // discard leftover input
            continue;
        }

        // Discard the leftover newline in the buffer
        while (getchar() != '\n'); 

        switch (choice) {
            case 1:
                display_sayings(sayings, count);
                break;
            case 2:
                count = add_saying(sayings, count);
                break;
            case 3:
                search_sayings(sayings, count);
                break;
            case 4:
                save_sayings(sayings, count);
                break;
            case 5:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}

// Function Definitions

void intro_display(void) { // Clears screen and displays a header
    printf("\033[H\033[J");

    // Program header
    printf("-----------------------------------------------\n");
    printf("              SAYINGS MANAGER                  \n");
    printf("-----------------------------------------------\n");
    printf("This program lets the user load and manage a set\n");
    printf("of sayings from a text file and add new ones.\n\n");
}

void get_filename(char filename[], size_t size) { // Prompts the user for a filename
    printf("Enter the name of your sayings repository file: ");
    if (fgets(filename, size, stdin) != NULL) {
        // Remove newline if present
        filename[strcspn(filename, "\n")] = '\0';
    }
}

int read_sayings(FILE *fp, char sayings[][MAX]) {
    // Reads lines (sayings) from a file into the 2D array
    char asaying[MAX];
    int count = 0;

    // Read until we can't read anymore or we hit MAXNUM
    while (fgets(asaying, MAX, fp) != NULL && count < MAXNUM) {
        asaying[strcspn(asaying, "\n")] = '\0';
        // Copy into our array
        strcpy(sayings[count], asaying);
        count++;
    }

    return count;  // Returns the number of sayings read
}

// Displays all the sayings
void display_sayings(const char sayings[][MAX], int count) {
    if (count == 0) {
        printf("\nNo sayings to display.\n");
        return;
    }

    printf("\n--- All Sayings (%d total) ---\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d) %s\n", i + 1, sayings[i]);
    }
}

// Adds a new saying
// Returns the updated count of sayings
int add_saying(char sayings[][MAX], int count) {
    // Check if there's space
    if (count >= MAXNUM) {
        printf("Cannot add more sayings; the array is full.\n");
        return count;
    }

    char newSaying[MAX];
    printf("Enter a new saying: ");

    // Read a line from stdin
    if (fgets(newSaying, sizeof(newSaying), stdin) != NULL) {
        // Strip trailing newline
        newSaying[strcspn(newSaying, "\n")] = '\0';

        // Store in the array
        strcpy(sayings[count], newSaying);
        count++;
        printf("Saying added!\n");
    } else {
        printf("Error reading new saying.\n");
    }

    return count;
}

// Searches for a substring in all sayings
void search_sayings(const char sayings[][MAX], int count) {
    if (count == 0) {
        printf("No sayings to search.\n");
        return;
    }

    char searchTerm[MAX];
    printf("Enter text to search for: ");
    if (fgets(searchTerm, sizeof(searchTerm), stdin) != NULL) {
        // Remove any trailing newline
        searchTerm[strcspn(searchTerm, "\n")] = '\0';
    } else {
        printf("Error reading search term.\n");
        return;
    }

    // Flag to see if we found any matches
    int found = 0;
    printf("\n--- Matching Sayings ---\n");
    for (int i = 0; i < count; i++) {
        if (strstr(sayings[i], searchTerm) != NULL) {
            printf("%s\n", sayings[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("No sayings matched your search.\n");
    }
}

// Saves all sayings to a user-specified file
void save_sayings(const char sayings[][MAX], int count) {
    if (count == 0) {
        printf("No sayings to save.\n");
        return;
    }

    char outputFilename[31];
    printf("Enter the name of the new file: ");
    if (fgets(outputFilename, sizeof(outputFilename), stdin) != NULL) {
        outputFilename[strcspn(outputFilename, "\n")] = '\0';
    } else {
        printf("Error reading output filename.\n");
        return;
    }

    FILE *outfile = fopen(outputFilename, "w");
    if (outfile == NULL) {
        printf("Error opening file '%s' for writing.\n", outputFilename);
        return;
    }

    // Write each saying to the file
    for (int i = 0; i < count; i++) {
        fprintf(outfile, "%s\n", sayings[i]);
    }

    fclose(outfile);
    printf("Sayings saved to '%s'\n", outputFilename);
}

