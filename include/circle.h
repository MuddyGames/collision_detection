#ifndef CIRCLE_H
#define CIRCLE_H

typedef struct Circle
{
    float x;
    float y;
    float r;
} Circle;

int collision(Circle lhs, Circle rhs);

#endif