// Kaza-Zack Kazirukanyo

#include <stdio.h>
#include <math.h>

int main() {
    int touchdowns, extra_points, field_goals, safeties;
    int total_points;

    // Ask the user for the number of touchdowns
    printf("Enter the number of touchdowns: ");
    scanf("%d", &touchdowns);

    // Ask the user for the number of extra points
    printf("Enter the number of extra points: ");
    scanf("%d", &extra_points);

    // Ask the user for the number of field goals
    printf("Enter the number of field goals: ");
    scanf("%d", &field_goals);

    // Ask the user for the number of safeties
    printf("Enter the number of safeties: ");
    scanf("%d", &safeties);

    // Calculate the total points scored
    total_points = (touchdowns * 6) + (extra_points * 1) + (field_goals * 3) + (safeties * 2);

    // Display the total points
    printf("Total points scored by the Irish: %d\n", total_points);

    return 0;
}

