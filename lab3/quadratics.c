// Kaza-Zack Kazirukanyo
// quadratics.c
// This program creates a function to compute the discriminant of a set of
//  triplets (a, b, c). The program terminates when 0 is entered for a.

#include <stdio.h>
#include <math.h>

double discrim(int, int, int);

int main(void) {

	printf("\nLet's calculate the discriminant of a set of three integers a, b, and c!\n");
	int a, b, c;

	while (1) {
		printf("\nTo terminate this program, enter a = 0.\n");

		printf("\nEnter integer a: ");
		scanf("%d",&a);
		if (a == 0) {
			break;
		}
		printf("Enter integer b: ");
		scanf("%d",&b);
		printf("Enter integer c: ");
		scanf("%d",&c);
	
		printf("\nYour three integers are %d, %d, and %d\n", a, b, c);

		double result = discrim(a, b, c); // Calculate the discriminant
		printf("\nThe discriminant of these three integers is %.1f.\n", result);
	}
	
	return 0;
}

double discrim(int a,int b,int c) {
	return (b * b) - 4 * a * c;
}
