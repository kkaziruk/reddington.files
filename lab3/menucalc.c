//Kaza-Zack Kazirukanyo
//menucalc.c
//This program does basic arithmetic operations on two user-input integers.

#include <stdio.h>
#include <math.h>

void menu_display();
double addition(double, double);
double subtraction(double, double);
double multiplication(double, double);
double division(double, double);
void answer(int, double, double);

int main(void) {
	
	int choice;
	double x, y, result;

	do {
		menu_display(); // print menu
		scanf("%d", &choice); // user selects operation

		if (choice >= 1 && choice <= 4) {
			printf("Enter the first number: ");
			scanf("%lf", &x);
			printf("Enter the second number: ");
			scanf("%lf", &y);

			answer(choice, x, y);
	
		} else if (choice != 5) { 
			printf("\nInvlaid choice. Please select a number 1-5.");
		}

	} while (choice != 5);
	
	printf("\nThank you for using menucalc.c!\nExiting program...\n\n");

	return 0; 
}

void menu_display()
{
	printf("\n===== MENU =====\n");
	printf("1 for Addition\n");
	printf("2 for Subtraction\n");
	printf("3 for Multiplication\n");
	printf("4 for Division\n");
	printf("5 to Exit\n");
	printf("\nEnter your choice: ");
}

double addition(double x, double y) { return x + y; }
double subtraction(double x, double y) { return x - y; }
double multiplication(double x, double y) { return x * y; }
double division(double x, double y) { return x / y; }

void answer(int a, double x, double y)
{
	double result = 0;

	switch (a) {
		case 1:
			result = addition(x,y);
			break;
		case 2:
			result = subtraction(x,y);
			break;
		case 3:
			result = multiplication(x,y);
			break;
		case 4:
			if (y == 0) { // Accounting for this unique case
				printf("Error: Division by zero!\n");
                        	return;
			}
			result = division(x,y);
			break; // No need for default case due to the condition (choice>= 1 && choice <=4)
	}

	printf("\nResult: %.2lf\n", result);

}

