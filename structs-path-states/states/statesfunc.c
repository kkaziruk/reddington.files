// statesfunc.c
// Kaza-Zack Kazirukanyo
// Function definitions

#include "statesfunc.h"
const int max = 100; // we define the const int once here; referenced as extern in the header

// read_states assumes file format is correct: abrv,name,capital,year
int read_states(FILE *fp, State states[]) {
    char line[LINE_SIZE];
    int n = 0;
    char *delim = ","; // make it easy to change the delimiter if necessary in future

    while ((fgets(line, LINE_SIZE, fp)) != NULL) {
        strcpy(states[n].abrv, strtok(line,delim)); // cannot assign directly, usestrcpy
        strcpy(states[n].name, strtok(NULL, delim));
        strcpy(states[n].capital, strtok(NULL, delim));
        states[n].year = atoi(strtok(NULL, delim)); //convert year from string to int 
        n++; // go to next index in array
    }

    return n; // this will be the number of entries in the file
}

void print_menu(void) {
    printf("\n====== 🗺️ STATE INFO MENU ======\n");
    printf("1. 📜 List all states\n");
    printf("2. 🔤 Search for information by abbreviation\n");
    printf("3. 🏷️ Search for information by name\n");
    printf("4. ⏳ List states that joined before a given year\n");
    printf("5. 📆 List states that joined in a given year\n");
    printf("6. 📈 List states in order of joining (sort)\n");
    printf("7. 🏛️  Search by capital\n");
    printf("8. ❌ Exit\n");
    printf("=============================\n");
    printf("Enter your choice: ");
}

// clear_screen: clears the terminal using ANSI escape codes
void clear_screen(void) {
    printf("\033[2J\033[H"); // works in most UNIX terminals
}

// one_state: nicely prints one state's full info
void one_state(State s) {
    printf("Name: %s (%s), Capital: %s, Year Founded: %d\n", s.name, s.abrv, s.capital, s.year);
}

// all_states: prints info for all states
void all_states(State states[], int count) {
    for (int i = 0; i < count; i++) {
        one_state(states[i]); 
    }
}

// find_state_index: generalized search helper
int find_state_index(const char str[], const  State states[], int count, int mode) {
    for (int i = 0; i < count; i++) {
        if ((mode == MODE_ABRV && strcmp(str, states[i].abrv) == 0) ||
            (mode == MODE_NAME && strcmp(str, states[i].name) == 0) ||
            (mode == MODE_CAPITAL && strcmp(str, states[i].capital) == 0)) {
            return i; // return index if match is found
        }
    }
    return -1; // return -1 if not found
}

// search_abrv: search by abbreviation
void search_abrv(char str[], State states[], int count) {
    int idx = find_state_index(str, states, count, MODE_ABRV);
    if (idx != -1) {
        printf("Information for %s:\n", str);
        one_state(states[idx]);
    } else {
        printf("Error: no match found.\n");
    }
}

// search_name: search by name
void search_name(char str[], State states[], int count) {
    int idx = find_state_index(str, states, count, MODE_NAME);
    if (idx != -1) {
        printf("Information for %s:\n", str);
        one_state(states[idx]);
    } else {
        printf("Error: no match found.\n");
    }
}

// search_by_capital: search by capital city
void search_by_capital(char str[], State states[], int count) {
    int idx = find_state_index(str, states, count, MODE_CAPITAL);
    if (idx != -1) {
        printf("%s joined the Union in %d.\n", states[idx].name, states[idx].year);
    } else {
        printf("Error: no such state capital located.\n");
    }
}

// joined_before: list states that joined before a given year
void joined_before(int year, State states[], int count) {
    int n = 1;
    for (int i = 0; i < count; i++) {
        if (states[i].year < year) {
            printf("%d. %s: %d\n", n,states[i].name, states[i].year );
            n++;
        }
    }

    if (n == 1) {
        printf("No states found that joined before %d.\n", year);
    }
}

// joined_in: list states that joined in a specific year
void joined_in(int year, State states[], int count) {
    int n = 1;
    for (int i = 0; i < count; i++) {
        if (states[i].year == year) {
            printf("%d. %s\n", n,states[i].name);
            n++;
        }
    }

    if (n == 1) {
        printf("No states found that joined in %d.\n", year);
    }
}

// sort_by_year: sort the states in-place by the year they joined using bubble sort
void sort_by_year(State states[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (states[j].year > states[j + 1].year) {
                State temp = states[j];
                states[j] = states[j + 1];
                states[j + 1] = temp;
            }
        }
    }

    printf("\nStates in order of joining the Union:\n");
    for (int i = 0; i < count; i++) {
        one_state(states[i]); // reuse single print function for consistency
    }
}
