// Kaza-Zack Kazirukanyo
// mortgage.c
/* This program calculates and displays an amortization schedule for a loan,
   determining how long it will take to pay off a loan based on user-inputted principal,
   interest rate, and monthly payment, while ensuring the payment is sufficient to cover interest. */


#include <stdio.h>
#include <stdbool.h>

int main(void) {

	// Principal (loan amount)
	float principal = 0; // initialise and declare principal variable

	do {
		printf("\nEnter the principal (loan amount): $");
		scanf("%f", &principal);
		
		if (principal <= 0) {
			printf("\nPlease enter a positive value.\n");
		}
	} while (principal <= 0);
	
	// Interest Rate
	float rate = 0; // initialise and declare principal variable

	do {
		printf("\nEnter the interest rate: ");
		scanf("%f", &rate);
		
		if (rate <= 0) {
			printf("\nPlease enter a positive value.\n");
		}
	} while (rate <= 0);

	// Desired monthly payment
	float payment = 0; // initialise and declare payment variable
	float p_flag = (1.0/12)*(rate/100) * principal; // declare and initialise payment flag 

	do {
		printf("\nEnter the desired monthly payment: $");
		scanf("%f", &payment);
		
		if (payment <= 0) {
			printf("\nPlease enter a positive value.\n");
		} else if (payment <= p_flag) {
			printf("\nYour desired monthly payment must exceed $%.2f. Please enter your desired payment: \n", p_flag);
		}
	} while ((payment <= 0) || (payment <= p_flag));
	
	// Amortization Table Header
	printf("\n%-8s%-12s%-12s%12s", "Month", "Payment", "Interest", "Balance");
	
	int month = 0; // initialise and declare month counter variable
	float balance = 0, total = 0; // initialise balance and total variables
	
	// Amortization Table Body
	while (1) {
		month ++;
		float interest = (principal * rate) / (12.0 * 100) ; // Calculate interest

		if (principal + interest < payment) {
			total += principal + interest;		
			payment = principal + interest;
		} else {
			total += payment;
		}
			
		balance = principal + interest - payment;
		printf("\n%-8d$%-11.2f$%-11.2f$%-11.2f", month, payment, interest, balance);

		principal = balance;

		if (principal <= 0) {
			printf("\n");
			break;
		}
	}
	
	int years =  month/12;
	printf("\nYou paid a total of $%.2f over %d years and %d months.", total, years, month % 12);

	return 0;
}

