// Kaza-Zack Kazirukanyo
// path.c
// Lab7_Part 1: Path Distance
// finds the distance length of a path through a sequence of points

#include "pathfunc.h"

int main() {
    char filename[30];
    
    // Get filename from user
    printf("Enter file name: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    // Create an array to store points
    Point points[MAX_POINT];
    int count = 0;

    // Open file
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) { 
        printf("Error opening file.\n"); 
        return 1;
    }

    // Read points from file
    while (fscanf(fp, "%f %f", &points[count].x, &points[count].y) == 2) {
        count++;
        if (count >= MAX_POINT) break;
    }

    // If no points in file
    if (count == 0) {
        printf("\nNo valid points in file %s.\n", filename);
        fclose(fp);
        return 1;
    }
    fclose(fp);  // Close file after reading

    // Calculate total path distance
    float total_Dist = total_Distance(points, count);
      
    // Call output functions
    output1(count);
    output2(points, count);
    output3(total_Dist);

    return 0;
}

