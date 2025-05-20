//Kaza-Zack Kazirukanyo
//fractals.c
//lab10: Fractal Puzzles
//program that generates the fractal shapes according to user inputs from 1-8 and q for quit.

//Libraries
#include "gfx.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

//Constants:
#define MIN_SIZE 20
#define PI 3.14159265358979323846
#define MIN2_SIZE 2
#define ANGLE_INCREMENT PI/10 // This determines how tight the spiral will be
#define SCALE_FACTOR 0.9 // How much smaller each square gets compared to the previous

//Functions Prototypes
void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 );
void shrinking_squares(int x, int y, int size, int level);
void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 );
void spiral_squares(float centerX, float centerY, float size, int numSquares, float angle, float scaleFactor);
void draw_branch(int x0, int y0, double angle, double len);
void koch(int x0, int y0, int x1, int y1, int depth);
void draw_fractal_tree(int x, int y, int length, float angle, int depth, float branch_angle, int branches);
double degreesToRadians(double degrees);
void drawLine(double x1, double y1, double x2, double y2);
void drawSnowflake(double centerX, double centerY, double length, int depth);
void drawCircularLace(int xCenter, int yCenter, int radius, int depth);
void drawCircle(int xCenter, int yCenter, int radius);
void spiralSquares(int xCenter, int yCenter, int size, double angle, int depth);
void drawFern(int windowWidth, unsigned long iter);
void drawSpiral(double x, double y, double r, double direction, int depth);

//Main Program:
int main()
{
	int width = 800, height = 800, mrgn = 20;
	int shouldDraw = 0;
	char c;

	gfx_open(width, height, "Fractal Window");

	while(1) {
		if (shouldDraw) {
			gfx_clear();
			drawSpiral(width / 2, height/ 2, 800, 90, 5);
			shouldDraw = 0; // Reset the draw flag
		}

		c = gfx_wait();

		switch(c) {
			case '1':
				gfx_clear();
				sierpinski(mrgn, mrgn, width-mrgn, mrgn, width/2, height-mrgn);
				break;
			case '2':
				gfx_clear();
				shrinking_squares(width / 2, height / 2, width / 2 - mrgn, 6); // 5 is an example recursion level
				break;
			case '3':
				gfx_clear();
				int cerX = width/2-230;
				int cerY = height/2+400;
				int initialSize = 350; // Start with a small square.
				double initialAngle = 0; // Start angle for the first square
				int N = 35; // Adjust the recursion depth as needed.
				spiralSquares(cerX, cerY, initialSize, initialAngle, N);
				break;
			case '4':
				gfx_clear();
				int cenX = width / 2;
				int cenY = height / 2;
				int initialRadius = 200; // You can adjust the initial radius.
				int dep = 5; // You can adjust the recursion depth.
				drawCircularLace(cenX, cenY, initialRadius, dep);
				break;
			case '5':
				gfx_clear(); // Clear the screen before drawing a new shape.
				double centerX = width / 2;
				double centerY = height / 2;
				double initialLength = 200.0; // Set the initial length of the lines.
				int depth = 6; // Set the recursion depth.
				drawSnowflake(centerX, centerY, initialLength, depth);
				break;
			case '6': // Case for drawing the fractal tree
				gfx_clear();
				draw_branch(width / 2, height - mrgn, -PI / 2, 220); // Start the tree from the bottom center of the window
				break;
			case '7':
				gfx_clear();
				unsigned long num = 100000;
				int w = width;
				drawFern(w, num);
				break;
			case '8':
				shouldDraw = 1; // Set the flag to draw on the next loop iteration
				break;
			case 'q':
				return 0; // Exit the program
			default:
				break;
		}
	}
}

//Functions:
//Triangle Functions:
void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 )
{
	// Base case. 
	if( abs(x2-x1) < 5 ) return;

	// Draw a triangle
	drawTriangle( x1, y1, x2, y2, x3, y3 );

	// Recursive calls
	sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
	sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
	sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}

void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 )
{
	gfx_line(x1,y1,x2,y2);
	gfx_line(x2,y2,x3,y3);
	gfx_line(x3,y3,x1,y1);
}

void drawSquare(int centerX, int centerY, int size) {
	// Calculate the corner points of the square based on the center coordinates and size
	int halfSize = size / 2;
	int leftX = centerX - halfSize;
	int rightX = centerX + halfSize;
	int topY = centerY - halfSize;
	int bottomY = centerY + halfSize;

	// Draw the square using the gfx library's line drawing function
	gfx_line(leftX, topY, rightX, topY);     // Top edge
	gfx_line(rightX, topY, rightX, bottomY); // Right edge
	gfx_line(rightX, bottomY, leftX, bottomY); // Bottom edge
	gfx_line(leftX, bottomY, leftX, topY);   // Left edge
}

void shrinking_squares(int x, int y, int size, int level) {
	if (size < MIN_SIZE || level == 0) {
		// Base case: If the square is too small or we've reached the desired recursion level, do nothing
		return;
	} else {
		// Draw the square with the center at (x, y) and the given size
		drawSquare(x, y, size);

		// Calculate the size of the smaller squares
		int newSize = size / 2;

		// Recursive calls for the four corners
		shrinking_squares(x - size / 2, y - size / 2, newSize, level - 1);
		shrinking_squares(x + size / 2, y - size / 2, newSize, level - 1);
		shrinking_squares(x - size / 2, y + size / 2, newSize, level - 1);
		shrinking_squares(x + size / 2, y + size / 2, newSize, level - 1);
	}
}

void draw_branch(int x0, int y0, double angle, double len) {
	if (len < 1) {
		return; // The smallest branch length is 4 pixels
	}

	// Calculate the end point of the branch
	int x1 = x0 + (int)(len * cos(angle));
	int y1 = y0 + (int)(len * sin(angle));

	// Draw the branch
	gfx_line(x0, y0, x1, y1);

	// Recursively draw the next branches
	draw_branch(x1, y1, angle + PI / 6, len * 0.67); // Right branch
	draw_branch(x1, y1, angle - PI / 6, len * 0.67); // Left branch
}

void drawLine(double x1, double y1, double x2, double y2) {
	gfx_line(x1, y1, x2, y2);
}

// Function to convert degrees to radians.
double degreesToRadians(double degrees) {
	return (degrees * PI) / 180.0;
}

// Recursive function to draw a snowflake.
void drawSnowflake(double centerX, double centerY, double length, int depth) {
	if (depth == 0) {
		return;
	}

	for (int i = 0; i < 5; i++) {
		double angle = degreesToRadians(i * (360.0 / 5));
		double endX = centerX + length * cos(angle);
		double endY = centerY + length * sin(angle);

		drawLine(centerX, centerY, endX, endY);
		drawSnowflake(endX, endY, length / 3, depth - 1);
	}
}

// Function to draw a circle.
void drawCircle(int xCenter, int yCenter, int radius) {
	int x, y;
	for (double angle = 0; angle < 2 * PI; angle += 0.01) {
		x = xCenter + radius * cos(angle);
		y = yCenter + radius * sin(angle);
		gfx_point(x, y);
	}
}

// Recursive function to draw the Circular Lace pattern.
void drawCircularLace(int xCenter, int yCenter, int radius, int depth) {
	if (depth == 0) {
		return;
	}

	// Draw the central circle.
	drawCircle(xCenter, yCenter, radius);

	// Draw the surrounding circles.
	for (int i = 0; i < 6; i++) {
		int newRadius = radius / 3;
		double angle = i * (360.0 / 6) * (PI / 180);
		int newX = xCenter + radius * cos(angle);
		int newY = yCenter + radius * sin(angle);

		drawCircularLace(newX, newY, newRadius, depth - 1);
	}
}

void spiralSquares (int xc, int yc, int radius, double theta, int length){
	if(radius<1) return;

	int x = xc + radius * cos(theta);
	int y = yc + radius * sin(theta);

	drawSquare (x, y, radius/2);
	theta -= M_PI/4.0;
	length = length*0.95;
	radius = radius*0.9;
	spiralSquares(x, y, radius, theta, length);

}

// I found the concept of Barnsley's fern on Wiki and I thought it would be even cooler to impelement: 
void drawFern(int windowWidth, unsigned long iter) {
	double x0 = 0, y0 = 0, x1, y1;
	int diceThrow;
	time_t t;
	srand((unsigned)time(&t));
	gfx_color(255, 255, 255); // Set the color to white

	while (iter > 0) {
		diceThrow = rand() % 100;

		if (diceThrow == 0) {
			x1 = 0;
			y1 = 0.16 * y0;
		} else if (diceThrow >= 1 && diceThrow <= 7) {
			x1 = -0.15 * x0 + 0.28 * y0;
			y1 = 0.26 * x0 + 0.24 * y0 + 0.44;
		} else if (diceThrow >= 8 && diceThrow <= 15) {
			x1 = 0.20 * x0 - 0.26 * y0;
			y1 = 0.23 * x0 + 0.22 * y0 + 1.6;
		} else {
			x1 = 0.85 * x0 + 0.04 * y0;
			y1 = -0.04 * x0 + 0.85 * y0 + 1.6;
		}

		gfx_point(30 * x1 + windowWidth / 2.0, windowWidth - (30 * y1));
		x0 = x1;
		y0 = y1;
		iter--;
	}
}

void drawSpiral(double x, double y, double r, double direction, int depth) {
	if (r < 1 || depth == 0) return;

	double alpha = 20; // The angle to rotate at each step
	double r_ratio = cos(36 * PI / 180) / cos((36 - alpha) * PI / 180);
	double d_ratio = sin(36 * PI / 180) - r_ratio * sin((36 - alpha) * PI / 180);

	for (int i = 0; i < 5; ++i) {
		double px = x + r * cos(direction * PI / 180);
		double py = y + r * sin(direction * PI / 180);
		double r2 = r;
		double d = direction;
		int c = 0;
		int flag = 0;

		while (1) {
			double dist = r2 * d_ratio;
			if (c > 10 && dist < 1) break;
			if (dist > 3) {
				drawSpiral(px, py, dist * 0.5, d, depth - 1);
				px = px + dist * cos((d + 180 - 54) * PI / 180);
				py = py + dist * sin((d + 180 - 54) * PI / 180);
			} else if (!flag) {
				gfx_line(px, py, px + dist * cos((d + 180 - 54) * PI / 180), py + dist * sin((d + 180 - 54) * PI / 180));
				flag = 1;
			} else {
				gfx_line(px, py, px + dist * cos((d + 180 - 54) * PI / 180), py + dist * sin((d + 180 - 54) * PI / 180));
			}
			r2 = r2 * r_ratio;
			d += alpha;
			c += 1;
		}
		direction += 360 / 5;
	}
}

