// Kaza-Zack Kazirukanyo
// polar.c
// This program displays the quadrant, radius and angle of the user-entered co-ordinates (double x, double y).

#include <stdio.h>
#include <math.h>

int get_quadrant(double, double);
double get_radius(double, double);
double get_angle(double, double);
void show_info(int, double, double);

int main(void){

	double x, y;
	printf("\nEnter the x and y coordinates for a point in the Cartesian plane system.\n");
	printf("\nX coordinate: ");
	scanf("%lf", &x);
	printf("Y coordinate: ");
	scanf("%lf", &y);

	int quadrant = get_quadrant(x, y);
	double radius = get_radius(x, y);
	double theta = get_angle(x, y);

	show_info(quadrant, radius, theta);

	return 0;
}

int get_quadrant(double x, double y) {
	if (x == 0 || y == 0) return 0; // Point is on an axis or the origin
	if (x > 0 && y > 0) return 1;
	if (x < 0 && y > 0) return 2;
	if (x < 0 && y < 0) return 3;
	if (x > 0 && y < 0) return 4;
    
    return 0;
}

double get_radius(double x, double y) 
{
	return sqrt((x * x) + (y * y));
}

double get_angle(double x, double y) 
{
	return atan2(y, x) * (180.0 / M_PI);
}

void show_info(int quadrant, double radius, double theta) 
{
	printf("\nThe (x,y) coordinates are in Quadrant %d. Polar coordinates: (%.1f, %.1f).\n", quadrant, radius, theta);
}
