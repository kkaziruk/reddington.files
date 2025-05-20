// Kaza-Zack Kazirukanyo
// grades.c
// A program to identify the avg and std_dev of a given sample of grades.

#include <stdio.h>
#include <math.h>

float avg(int a[], int length);
void std_dev(int a[], int length, float average);

int main(void) {

    int grades[] =
    { 96,73,62,87,80,63,93,79,71,99,
      82,83,80,97,89,82,93,92,95,89,
      71,97,91,95,63,81,76,98,64,86,
      74,79,98,82,77,68,87,70,75,97,
      71,94,68,87,79 };

    int length = sizeof(grades) / sizeof(grades[0]);
    printf("\nThere are %d grades in the array.\n", length);

    float average = avg(grades, length);
    printf("Average grade: %.2f.\n", average); 

    std_dev(grades, length, average);

	return 0;
}

float avg(int a[], int length) {
    float sum = 0;
    float average;

    for (int i = 0; i < length; i++) {
        sum += a[i];
    }
    
    return sum / (float) length;
}

void std_dev(int a[], int length, float average) {

    float sum = 0;
    float std_dev;

    for (int i = 0; i < length; i++) {
        sum += pow(a[i] - average, 2);
    }
    
    std_dev = sqrtf(sum/length);

    printf("\nStandard deviation: %.2f.\n", std_dev);
}


