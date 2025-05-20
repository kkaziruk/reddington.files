// Kaza-Zack Kazirukanyo
// funanim.c
// Lab 9 Part 3: Rotating Animation
/*The program that have 5 shaps rotating where the user can use:
  1- 'i' and 'd' to increase and decrease the radius of the rotation
  2- 'f' and 's' to increase and decrease the spead of the rotation
  3- 'p' to Pause or Resume 
  4- 'r' to reverse the direction
*/


#include "gfx.h"
#include <unistd.h> // For usleep
#include <stdlib.h> // For rand(), srand()
#include <math.h> // For cos(), sin()
#include <time.h> // For time()

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define INITIAL_ORBIT_RADIUS 150
#define INITIAL_SPEED 0.05

// Function prototypes
void drawCircle(int x, int y, int radius);
void drawSquare(int x, int y, int side);
void drawTriangle(int x, int y, int size);
void drawPolygon(int x, int y, int sides, int radius, int r, int g, int b);
void drawPentagon(int x, int y, int size);
void drawHexagon(int x, int y, int size);

int main() {
	double angle = 0; // Angle for the circular motion
	double speed = INITIAL_SPEED; // Orbiting speed
	int orbitRadius = INITIAL_ORBIT_RADIUS; // Orbit radius
	int paused = 0; // Pause flag
	int direction = 1; // Direction of rotation

	gfx_open(WIN_WIDTH, WIN_HEIGHT, "Fun Animation");
	while (1) {
		int centerX = WIN_WIDTH / 2, centerY = WIN_HEIGHT / 2;

		// Clear the screen
		gfx_clear();

		if (!paused) {
			// Draw each shape in orbit, considering the orbit radius
			drawCircle(centerX + cos(angle) * orbitRadius, centerY + sin(angle) * orbitRadius, 20);
			drawSquare(centerX + cos(angle + 0.628) * orbitRadius, centerY + sin(angle + 0.628) * orbitRadius, 40);
			drawTriangle(centerX + cos(angle + 1.256) * orbitRadius, centerY + sin(angle + 1.256) * orbitRadius, 30);
			drawPentagon(centerX + cos(angle + 1.884) * orbitRadius, centerY + sin(angle + 1.884) * orbitRadius, 20);
			drawHexagon(centerX + cos(angle + 2.512) * orbitRadius, centerY + sin(angle + 2.512) * orbitRadius, 20);
		}

		gfx_flush();

		if (!paused) {
			// Adjust the angle for the next frame, considering direction
			angle += speed * direction;
		}

		// Handle user input
		if (gfx_event_waiting()) {
			char c = gfx_wait();
			switch(c) {
				case 'f': // Increase speed
					speed += 0.01;
					break;
				case 's': // Decrease speed
					if (speed > 0.01) speed -= 0.01;
					break;
				case 'i': // Increase orbit radius
					orbitRadius += 10;
					break;
				case 'd': // Decrease orbit radius
					if (orbitRadius > 20) orbitRadius -= 10; // Avoid negative or too small radius
					break;
				case 'p': // Pause or resume
					paused = !paused;
					break;
				case 'r': // Reverse direction
					direction *= -1;
					break;
			}
		}

		usleep(20000); // Control the animation speed
	}

	return 0;
}

void drawCircle(int x, int y, int radius) {
	gfx_color(255, 0, 0); // Red
	gfx_circle(x, y, radius);
}

void drawSquare(int x, int y, int side) {
	gfx_color(0, 255, 0); // Green
	int half = side / 2;
	gfx_line(x - half, y - half, x + half, y - half);
	gfx_line(x + half, y - half, x + half, y + half);
	gfx_line(x + half, y + half, x - half, y + half);
	gfx_line(x - half, y + half, x - half, y - half);
}

void drawTriangle(int x, int y, int size) {
	gfx_color(0, 0, 255); // Blue
	int height = (int)(size * sqrt(3) / 2);
	gfx_line(x - size / 2, y + height / 3, x + size / 2, y + height / 3);
	gfx_line(x + size / 2, y + height / 3, x, y - 2 * height / 3);
	gfx_line(x, y - 2 * height / 3, x - size / 2, y + height / 3);
}

void drawPolygon(int x, int y, int sides, int radius, int r, int g, int b) {
	gfx_color(r, g, b); // Set color myself by calling the function; also works as multi-shapes
	double angleIncrement = 2 * M_PI / sides;
	for (int i = 0; i < sides; i++) {
		double angle1 = i * angleIncrement;
		double angle2 = (i + 1) % sides * angleIncrement;
		gfx_line(x + radius * cos(angle1), y + radius * sin(angle1), x + radius * cos(angle2), y + radius * sin(angle2));
	}
}

void drawPentagon(int x, int y, int size) {
	drawPolygon(x, y, 5, size, 255, 255, 0); // Yellow
}

void drawHexagon(int x, int y, int size) {
	drawPolygon(x, y, 6, size, 255, 165, 0); // Orange
}
