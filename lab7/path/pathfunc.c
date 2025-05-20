#include "pathfunc.h"

float distance(float x1, float y1, float x2, float y2) {
	float dx = x2 - x1;
	float dy = y2 - y1;
	float dist = sqrt(dx * dx + dy * dy);

	return dist;
}

float total_Distance(Point points[], int count) {
    float total_Dist = 0;
    for (int i = 0; i < count - 1; i++) {
        total_Dist += distance(points[i].x, points[i].y, points[i+1].x, points[i+1].y);
    }

    return total_Dist;
}

void output1(int count) {
	printf("\nThere are %d points:\n", count);
}

void output2(Point points[], int count) {
	printf("\n%5s   |%5s   \n", "x", "y"); // top line
	for (int i = 0; i < 8; i++) {
		printf("-"); // dashes - table
	}
	printf("+"); // separator - table
	for (int i = 0; i < 8; i++) {
		printf("-"); // dashes - table
	}

	printf("\n");

	for (int i = 0; i < count; i++) {
		printf("%7.1f |%7.1f \n", points[i].x, points[i].y);
	}
}

void output3(float dist) {
	printf("\nThe length of the path through them is %.2f\n", dist);
}



