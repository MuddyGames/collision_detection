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

CollisionReport collisionReport(Circle lhs, Circle rhs)
{
    CollisionReport report = {0}; // count = 0, everything zeroed

    // Not colliding? Return an empty report
    if (!collision(lhs, rhs))
    {
        return report;
    }

    float distance_between_x = rhs.x - lhs.x;
    float distance_between_y = rhs.y - lhs.y;

    // Need the real distance, not squared, expensive sqrt
    float distance = sqrtf((distance_between_x * distance_between_x) + (distance_between_y * distance_between_y));

    // Which way? Normalise vector from lhs to rhs
    if (distance > 0.0f)
    {
        report.normal_x = distance_between_x / distance;
        report.normal_y = distance_between_y / distance;
    }
    else
    {
        // Same centre: no direction, so pick one like (cute_c2 picks up/down)
        report.normal_x = 0.0f;
        report.normal_y = 1.0f;
    }

    // How far? Sum of radii minus actual distance
    report.depth = (lhs.r + rhs.r) - distance;

    // Where? A point on rhs edge, facing lhs
    report.contact_x = rhs.x - report.normal_x * rhs.r;
    report.contact_y = rhs.y - report.normal_y * rhs.r;

    report.count = 1;

    return report;
}

void resolveCollision(Circle *lhs, CollisionReport report)
{
    if (report.count == 0)
    {
        return; // nothing to fix
    }

    // Normal points lhs -> rhs: so move lhs the opposite way by depth
    lhs->x -= report.normal_x * report.depth;
    lhs->y -= report.normal_y * report.depth;
}