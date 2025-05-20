// bounce.c
// Kaza-Zack Kazirukanyo - Lab 9 Part 2: Bouncing Ball
// Animates a circle bouncing around a window at a constant velocity.
// Clicking the mouse moves the ball to the click location and gives it a new random velocity.

#include "gfx.h"
#include <unistd.h>   // For usleep
#include <stdlib.h>   // For rand() and srand()
#include <time.h>     // For time(), to seed random

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define BALL_RADIUS 20
#define VELOCITY_RANGE 10  // Max velocity component magnitude

int main() {
    int x = WIN_WIDTH / 2, y = WIN_HEIGHT / 2; // Start position of the ball
    int vx = 5, vy = 5; // Initial velocity of the ball

    srand(time(NULL)); // Seed the random number generator

    gfx_open(WIN_WIDTH, WIN_HEIGHT, "Bouncing Ball");
    gfx_color(255, 255, 255); // Set the ball color to white

    while (1) {
        // Update position
        x += vx;
        y += vy;

        // Bounce off the walls
        if (x <= BALL_RADIUS || x >= WIN_WIDTH - BALL_RADIUS) {
            vx = -vx;
            x += vx;
        }
        if (y <= BALL_RADIUS || y >= WIN_HEIGHT - BALL_RADIUS) {
            vy = -vy;
            y += vy;
        }

        // Clear screen and draw ball
        gfx_clear();
        gfx_circle(x, y, BALL_RADIUS);
        gfx_flush();

        // Check for user input
        if (gfx_event_waiting()) {
            char c = gfx_wait();
            if (c == 1) { // Mouse left click
                x = gfx_xpos();
                y = gfx_ypos();

                // Assign new non-zero random velocity
                do {
                    vx = (rand() % (VELOCITY_RANGE * 2)) - VELOCITY_RANGE;
                } while (vx == 0);
                do {
                    vy = (rand() % (VELOCITY_RANGE * 2)) - VELOCITY_RANGE;
                } while (vy == 0);
            }
        }

        usleep(20000); // Delay for smooth animation (adjust if needed)
    }

    return 0;
}

