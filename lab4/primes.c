// Kaza-Zack Kazirukanyo
// primes.c
// A program to sift prime numbers from an array of ints 2-1000

#include <stdio.h>

int main(void) {

    int numbers[999]; // Array of numbers from 2 to 1000
    int index[999]; // Array for marking primes

    // Initialize the numbers array with values from 2 to 1000
    for (int i = 0, num = 2; i < 999; i++, num++) {
        numbers[i] = num;
        index[i] = 1; //Assume all numbers are prime initially
    }

    int factor;

    // Sieve of Eratosthenes: Mark non-primes
    for (int j = 0; j < 999; j++) {
        if (index[j] == 1) {
            factor = numbers[j];
            for (int k = (factor * factor) - 2; k < 999; k += factor) {
                index[k] = 0;
            }
        }
    }

    // Printing the prime numbers; 10 columns
    int count = 0;
    for (int i = 0; i < 999; i++) {
        if (index[i] == 1) {
             printf("%5d ", numbers[i]);
             count++;

             if (count % 10 == 0) { printf("\n"); }
          }
        }
    printf("\n");

	return 0;
}


