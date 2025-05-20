//Kaza-Zack Kazirukanyo
//table.c
/* This program generates a user-defined multiplication table with labeled row and column headers formatted for readability */

#include <stdio.h>

int main(void) {
	
	int rows, cols;			// declare rows and columns variable 
	
	printf("\nEnter the number of rows and columns in the multiplication table.\n");
	
	printf("Integer 1 (number of rows): ");
	scanf("%d", &rows);
	printf("Integer 2 (number of columns: ");
	scanf("%d", &cols);
	
	printf("\n*\t");		 // Header line formatting
	for (int x = 1; x<= cols; x++) {
		printf("%d\t", x);	// For Loop (column headers)
	}
	
	printf("\n  ");

	for (int y = 1; y<= (8*cols); y++) {
		printf("-");		// Dashed lines
	}

	printf("\n");			// Formatting
	
	for (int i = 1; i <= rows; i++) {
		printf("%d |\t", i);	// Row headers
		for (int j = 1; j <= cols; j++) {
		int result = i * j;	// Multiplication Table
		printf("%d\t", result);
		}
		printf("\n");		// Formatting
	} 

	return 0;
}

