// Kaza-Zack Kazirukanyo

#include <stdio.h>
#include <math.h>

int main(void) {
    // Inputs
    float len1, len2, len3;

    printf("\nEnter the lengths of the three sides of a triangle.");

    printf("\nLength 1: ");
    scanf("%f", &len1);

    printf("Length 2: ");
    scanf("%f", &len2);

    printf("Length 3: ");
    scanf("%f", &len3);

    // Calculate semi-perimeter
    float s = (len1 + len2 + len3) / 2;

    // Calculate area using Heron's formula
    float area = sqrt(s * (s - len1) * (s - len2) * (s - len3));

    // Output the result
    printf("\nThe area of the triangle is %.2f.\n", area);

    return 0;
}

