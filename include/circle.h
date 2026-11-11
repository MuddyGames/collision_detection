#ifndef CIRCLE_H
#define CIRCLE_H

typedef struct Circle
{
    float x;
    float y;
    float r;
} Circle;

// Collision Report for the insurance assessor
// Which way, point the finger? normal(unit vector pointing from lhs to rhs)
// How far, two hands how deep? depth (how much the circles overlap)
// Where, it touched here? contact point
// Another name for this is a "manifold" in physics engines, but we don't need to get that fancy
typedef struct CollisionReport
{
    int count;      // 0 = not colliding, 1 = colliding
    float depth;    // overlap amount
    float normal_x; // direction from lhs to rhs (length 1)
    float normal_y;
    float contact_x; // point where they touch
    float contact_y;
} CollisionReport;

int collision(Circle lhs, Circle rhs);

CollisionReport collisionReport(Circle lhs, Circle rhs);

// Push lhs back out of rhs using collision report
void resolveCollision(Circle *lhs, CollisionReport report);

#endif