// Kaza-Zack Kazirukanyo
// graph.c
/* This C program takes user input,
 * calculates and prints x and y values,
 * tracks the max and min,
 *  and generates an ASCII plot. */

#include <stdio.h>
#include <math.h>

int main(void) {

	double start = 0, end = 0, step = 0, y = 0, max, min, xmax, xmin;
	
	printf("\nOur graph equation is y = e^(-x^2/20) * sin(5x) + ln(|x|+1) * cos(2x)\n");

	double terma = 0, termb = 0;

	// User Input
	printf("State the start and end x values.\n");
	printf("Start value: ");
	scanf("%lf", &start);
	printf("End value: ");
	scanf("%lf", &end);

	printf("By how much shall we increment X? ");
	scanf("%lf", &step);

	if (step <= 0) {
        printf("\nStep must be greater than 0.\n");
        return 1;
	}

	// Header
	printf("\n%-8s %-8s\n", "X", "Y");

	// For Loop
	for (double x = start; x <= end; x += step) {
		terma = exp(-pow(x, 2) / 20) * sin(5 * x);
        	termb = log(fabs(x) + 1) * cos(2 * x);
        	y = terma + termb;

        	printf("%-8.2lf %-8.2lf", x, y);

		// Record Maximum and Minimum
		if (x == start) {
			max = y;
			xmax = x;
			min = y;
			xmin = x;
		}

		else if (y >= max) {
			max = y;
			xmax = x;
		}

		else if (y < min) {
			min = y;
			xmin = x;
	}

        // ASCII Plot
        int zero_position = 50;
        int graph_position = zero_position + (int)(y * 10); // Scale y for better visibility

        for (int i = 0; i < 100; i++) {
            if (i == zero_position) {
                printf("|");
            } else if ((y >= 0 && i > zero_position && i <= graph_position) || 
                       (y < 0 && i < zero_position && i >= graph_position)) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

	printf("\nThe maximum value is %.2lf at x = %.2lf.\nThe minimum is %.2lf at x = %.2lf\n", max, xmax, min, xmin);

    return 0;
}
	

