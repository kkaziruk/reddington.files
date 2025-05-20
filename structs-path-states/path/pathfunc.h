#ifndef PATHFUNC_H
#define PATHFUNC_H

#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_POINT 30

// Struct definition
typedef struct {
    float x;
    float y;
} Point;

// Function prototypes
float distance(float, float, float, float);
float total_Distance(Point [], int);
void output1(int);
void output2(Point [], int);
void output3(float);

#endif
