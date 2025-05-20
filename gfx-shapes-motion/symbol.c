// Kaza-Zack Kazirukanyo
// symbol.c
// Lab9_Part1: Symbolic Typewriter Program
//
// This program opens a graphics window and displays different shapes at the mouse location
// based on key presses or mouse clicks. Shapes include a square, circle, triangle, and
// regular polygons. The ESC key clears the window, and 'q' quits the program.

#include "gfx.h"
#include <stdio.h>
#include <math.h>

#define SIZE 50 // Standard size/diameter for shapes

// Function declarations
void drawSquare(int x, int y, int size);
void drawCircle(int x, int y, int diameter);
void drawTriangle(int x, int y, int size);
void drawPolygon(int x, int y, int sides, int radius);

int main() {
	char c; // Input character or mouse event
	int x, y; // Mouse coordinates

	// Open graphics window
	gfx_open(600, 400, "Symbol Typewriter");

	// Main event loop
	while (1) {
		c = gfx_wait();       // Wait for input (key press or mouse click)
		x = gfx_xpos();       // Get current mouse X position
		y = gfx_ypos();       // Get current mouse Y position

		// Handle input
		if (c == 'q') {
			break; // Quit the program
		}
		else if (c == 1) { // Left mouse click (int value 1)
			gfx_color(0, 0, 255); // Blue
			drawSquare(x, y, SIZE);
		}
		else if (c == 'c') {
			gfx_color(255, 255, 255); // White
			drawCircle(x, y, SIZE);
		}
		else if (c == 't') {
			gfx_color(0, 255, 0); // Green
			drawTriangle(x, y, SIZE);
		}
		else if (c >= '3' && c <= '9') {
			int sides = c - '0'; // Convert character to integer
			gfx_color(128, 0, 128); // Purple
			drawPolygon(x, y, sides, SIZE / 2); // Radius = SIZE / 2
		}
		else if (c == 27) { // ESC key (ASCII 27)
			gfx_clear(); // Clear the window
		}
	}

	return 0;
}

// Draw a square centered at (x, y) with side length 'size'
void drawSquare(int x, int y, int size) {
	int half = size / 2;

	// Draw square outline
	gfx_line(x - half, y - half, x + half, y - half); // Top edge
	gfx_line(x + half, y - half, x + half, y + half); // Right edge
	gfx_line(x + half, y + half, x - half, y + half); // Bottom edge
	gfx_line(x - half, y + half, x - half, y - half); // Left edge
}

// Draw a circle outline centered at (x, y) with given diameter
void drawCircle(int x, int y, int diameter) {
	int radius = diameter / 2;
	double angleStep = 0.01; // Small angle increment for smoothness

	// Draw line segments around the circle
	for (double angle = 0; angle < 2 * M_PI; angle += angleStep) {
		int x1 = x + radius * cos(angle);
		int y1 = y + radius * sin(angle);
		int x2 = x + radius * cos(angle + angleStep);
		int y2 = y + radius * sin(angle + angleStep);
		gfx_line(x1, y1, x2, y2);
	}
}

// Draw an isosceles triangle centered at (x, y) with base = size
void drawTriangle(int x, int y, int size) {
	int height = (int)(size * sqrt(3) / 2); // Height for equilateral triangle
	int halfBase = size / 2;

	// Calculate vertices of the triangle
	int x1 = x;               int y1 = y - (2 * height / 3); // Top vertex
	int x2 = x - halfBase;    int y2 = y + (height / 3);     // Bottom left
	int x3 = x + halfBase;    int y3 = y + (height / 3);     // Bottom right

	// Draw triangle outline
	gfx_line(x1, y1, x2, y2); // Left edge
	gfx_line(x2, y2, x3, y3); // Base
	gfx_line(x3, y3, x1, y1); // Right edge
}

// Draw a regular polygon centered at (x, y) with given number of sides and radius
void drawPolygon(int x, int y, int sides, int radius) {
	double angleStep = 2 * M_PI / sides;

	// Loop through each side
	for (int i = 0; i < sides; i++) {
		// Calculate coordinates of the current and next vertex
		int x1 = x + radius * cos(i * angleStep);
		int y1 = y + radius * sin(i * angleStep);
		int x2 = x + radius * cos((i + 1) * angleStep);
		int y2 = y + radius * sin((i + 1) * angleStep);

		gfx_line(x1, y1, x2, y2); // Draw edge
	}
}

