#include "circle.h"

int collision(Circle lhs, Circle rhs)
{
    int result = 0;

    float distance_between_x = rhs.x - lhs.x;
    float distance_between_y = rhs.y - lhs.y;

    float distanceSquared = (distance_between_x * distance_between_x) + (distance_between_y * distance_between_y);
    float separation = lhs.r + rhs.r;
    float separationSquared = separation * separation;


    if (distanceSquared > separationSquared)
    {
        result = 0; // False not Colliding
    }
    else
    {
        result = 1; // True Collision
    }

    return result;
}