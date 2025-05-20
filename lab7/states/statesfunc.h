// Kaza-Zack Kazirukanyo
// statesfunc.h
// Function headers

#ifndef STATESFUNC_H
#define STATESFUNC_H 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char abrv[3];       // e.g. TX
    char name[30];      // e.g. Texas
    char capital[30];   // e.g. Austin
    int year;           // year it joined the Union
} State; 

extern const int max;
// I discovered that a defined const int must have 'extern'
// in the header file, and then we initialize it elsewhere.

#define LINE_SIZE 256
#define MODE_ABRV 0
#define MODE_NAME 1
#define MODE_CAPITAL 2

// scan file and read in State information
int read_states(FILE *, State []);

// print the menu of options
void print_menu(void);

// clear the terminal screen using ANSI escape codes
void clear_screen(void);

// a modular function to provide a simplified output structure
void one_state(State);

// one of the menu options: display all states and their info
void all_states(State [], int); 

// find the index of a matching state based on a mode
// mode should be one of: MODE_ABRV, MODE_NAME, MODE_CAPITAL
int find_state_index(const char str[], const State states[], int count, int mode);

// search for a state by its abbreviation
void search_abrv(char [], State [], int);

// search for a state by its name
void search_name(char [], State [], int); 

// search for a state by its capital
void search_by_capital(char [], State [], int);

// search for states which joined before a user-input date (with error handling)
void joined_before(int, State[], int); 

// find all states which joined in a given year
void joined_in(int, State[], int);

// sort states in ascending order of the year they joined, using Bubble Sort
void sort_by_year(State [], int); 

#endif
