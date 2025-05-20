// Kaza-Zack Kazirukanyo
// usastates.c
// Main function
#include "statesfunc.h"

int main(void) {
    char filename[30];
    printf("Enter the file name: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("\nError opening file %s.\n", filename);
        return 1;
    }

    State states[max]; // our previously defined const int
    int count = read_states(fp, states);
    fclose(fp); // good practice

    int choice;

    do {
        clear_screen(); // UI
        print_menu();
        scanf("%d", &choice);
        getchar(); // clear buffer

        switch (choice) {
            case 1:
                all_states(states, count); 
                break;

            case 2: {
                        char abr[4];
                        printf("\nEnter a two-letter abbreviation (e.g. \"TX\"): ");
                        fgets(abr, sizeof(abr), stdin);
                        abr[strcspn(abr, "\n")] = '\0';
                        search_abrv(abr, states, count);
                        break;
                    }
            case 3: {
                        char name[15];
                        printf("\nEnter state name (e.g. \"California\"): ");
                        fgets(name, sizeof(name), stdin);
                        name[strcspn(name, "\n")] = '\0';
                        search_name(name, states, count);
                        break;
                    }

            case 4: {
                    int year;
                    printf("Enter a year: ");
                    scanf("%d", &year);
                    getchar();
                    joined_before(year, states, count);
                    break;
                    }

            case 5: {
                    int y;
                    printf("Enter a year: ");
                    scanf("%d", &y);
                    getchar();
                    joined_in(y, states, count);
                    break;
                    }

            case 6:
                    sort_by_year(states, count);
                    break;
            case 7: {
                    char capital[30]; 
                    printf("\nEnter state capital (e.g. \"Austin\": ");
                    fgets(capital, sizeof(capital), stdin);
                    capital[strcspn(capital, "\n")] = '\0';
                    search_by_capital(capital, states, count);

                    break;
                    }

            case 8:
                    printf("Goodbye!\n");
                    break;

            default:
                    printf("Error. Enter an integer 1-8.\n");
                    break;
        }

        printf("\nPress Enter to continue...");
        getchar(); // wait for user to hit Enter before refreshing
    } while (choice != 8);


    return 0;
}
