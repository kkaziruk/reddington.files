// Kaza-Zack Kazirukanyo
// ndfootball.c
// A program to answer user-selected questions related to Notre Dame football's win/loss record from 1900.

#include <stdio.h>
#include <stdbool.h>
#include "nd_data.h"

void menu_display();
void record_display(int year);
void losing_record();
void atleast(int a);
void streak();
void predictseason();

int main(void) {

    int choice;
    bool running = true; 
    int entry1;
    int n;
    int years = sizeof(wins)/sizeof(int);

    while(running) {

        menu_display();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nWhich year? ");
                scanf("%d", &entry1);

                if (entry1 < (years - years + 1900) || entry1 > (years + 1900)) {
                    printf("\n--- Invalid Entry. Enter a year between %d and %d. ---\n", (years - years + 1900), (years + 1900));
                } else {
                    record_display(entry1);
                }

                break;
            case 2:
                losing_record();
                break;
            case 3:
                printf("\n'n' =  ");
                scanf("%d", &n);
                atleast(n);
                break;
            case 4:
                streak();
                break;
            case 5:
                predictseason();
                    break;
            case 6:
                printf("\nThank you! Exiting now......\n\nExit COMPLETE\n");
                running = false;
                break;
            default:
                printf("\nInvalid entry. Please enter an integer between 1 and 5. To exit, enter '6'.\n");
        }
    }
    return 0;
}

void menu_display() {

    int years = sizeof(wins)/sizeof(int);

    printf("\n\n--------Go IRISH!--------\n");
    printf("\n--------MENU--------\n");
    printf("1. Display the record for a given year\n2. Display years with a losing record\n3. Display years with at least 'n' wins\n4. Display positive record streaks\n5. Predict the %d season!!!\n6. Exit\n", ((years) + 1900));
}

void record_display(int a) {

    int years = sizeof(wins)/sizeof(int);

    int w = wins[a - 1900];
    int l = losses[a - 1900];

    if (a < (years - years + 1900) || a > (years + 1900)) {
        printf("\n--------No data available--------\n");
    } else if (a == (years + 1900)) {
        printf("\n--- Coming Soon! ---\n");
    } else {
            printf("\n--------Win/Loss Record: %d--------\n\nWins: %d | Losses: %d\nRecord: %d", a, w, l, w - l);
    }
}

void losing_record() {

    int years = sizeof(wins)/sizeof(int);

    printf("\n--------Years With A Losing Record:--------\n\n");

    int count = 0; // Let's figure out how many years have a losing record 

    for (int i = 0; i < years; i++) {
        if (wins[i] - losses[i] < 0) {
            count+=1;   
        }
    }

    // Debugging test:
    // printf("%d\n", count);

    int x = 0;

    for (int i = 0; i < years; i++) {
        if (wins[i] - losses[i] < 0) {
            x++;
            if (x < count) printf("%d, ", i + 1900); // It's now clear why we had the previous for loop, why we have count and 'x'. If there's a more efficient way to do this please let me know!!
            else {
                printf("%d.", i + 1900); // Put so much effort just for this formatting! Come on guys, I need a tip!
            }     
        }
    }
}

void atleast(int num) {

    int years = sizeof(wins)/sizeof(int);
    
    if (num < 0 || num > 17) {
        printf("\nInvalid entry. Please enter an integer 0-17.\n");
    } else {

        printf("\n--------Years With At Least %d Wins:--------\n\n", num);

        for (int i = 0; i < years; i++) {
            if (wins[i] >= num) {
                if (i != years - 1) { printf("%d, ", 1900+i); }
                else if (i == years - 1) { printf("%d.", 1900+i); }
            } // This one was standard procedure
        }
    }
}

void streak() { // Finally, an interesting one

    int years = sizeof(wins)/sizeof(int);

    printf("\n----WINNING STREAKS----\nFor consecutive years during which the Fighting Irish maintained a positive net score.\n");


    for (int i = 0; i < years; i++) {
       
        if (i == 0) { // Handle the case where the first entry is the beginning of a streak
            if ((wins[i] - losses[i] > 0) && (wins[i+1] - losses[i + 1] > 0)) {
                printf("\n\t> %d ", i + 1900);
            }
        }

        if (i != 0) { // This should account for the start of any streak, apart from the first entry
            if (((wins[i - 1] - losses [i - 1]) <= 0) && (wins[i] - losses [i] > 0) && (wins[i + 1] - losses[i + 1] > 0)) {
                printf("\t> %d ", i + 1900);
            }

            if ((wins[i - 1] - losses[i - 1] > 0) && ((wins[i] - losses[i]) <= 0) && ((wins[i - 2] - losses[i - 2]) > 0)) { // This should account for the end of a streak, unless the streak 'has not yet ended'. The 'i-2' is to check that a streak existed in the first place.
                printf("to %d.\n", (i - 1) + 1900);
            }

        }
        if ((i == years - 1) && (wins[years - 1] - losses[years - 1] > 0) && (wins[years - 2] - losses[years -2] > 0)) {
            printf("and it continues!"); // Accounts for a case where the latest (most recent) entry has a positive record
        }

    }
}

void predictseason() { // LET'S COOK
    int N, use_recency = 0, use_bigwin = 0, use_losstrend = 0;
    double total_wins = 0, total_losses = 0, weight_sum = 0;

    int years = sizeof(wins) / sizeof(int);

    printf("\n--- Predict Notre Dame's 2025 Football Season ---\n");

    do {
        printf("Enter how many past seasons to use for prediction (Max: %d): ", years);
        scanf("%d", &N);
    } while (N <= 0 || N > years);

    printf("Use recency weighting? (1 = Yes, 0 = No): ");
    scanf("%d", &use_recency);
    printf("Boost undefeated seasons? (1 = Yes, 0 = No): ");
    scanf("%d", &use_bigwin);
    printf("Consider past losing seasons negatively? (1 = Yes, 0 = No): ");
    scanf("%d", &use_losstrend);

    for (int i = 0; i < N; i++) {
        int index = years - 1 - i; // Get latest N seasons
        int w = wins[index];
        int l = losses[index];

        double weight = 1.0;
        if (use_recency) weight = (double)(N - i) / N; // More weight to recent years

        total_wins += w * weight;
        total_losses += l * weight;
        weight_sum += weight;

        // Apply big win boost for undefeated seasons
        if (use_bigwin && l == 0 && w > 0) total_wins += 1;

        // Apply loss penalty for losing seasons
        if (use_losstrend && w < l) total_wins -= 1;
    }

    total_wins /= weight_sum;
    total_losses /= weight_sum;

    int predicted_wins = (int)(total_wins + 0.5);
    int predicted_losses = (int)(total_losses + 0.5);

    printf("\n🔮 Predicted 2025 Record: %d Wins, %d Losses\n", predicted_wins, predicted_losses);
    printf("(Based on factors: ");
    if (use_recency) printf("Recency Weighted, ");
    if (use_bigwin) printf("Big Win Boost, ");
    if (use_losstrend) printf("Losing Trends Considered");
    printf(")\n");

}

// That's it! Thank you for grading!
