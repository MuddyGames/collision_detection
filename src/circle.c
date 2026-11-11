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

	// Need real hypotenuse, not squared: expensive sqrt function...see R36S project for fastmath
	// https://bitbucket.org/MuddyGames/r36s/src/main/include/core/fast_math.h
	float distance = sqrtf((distance_between_x * distance_between_x) + (distance_between_y * distance_between_y));

	// Which way? Normalise vector from lhs to rhs
	// Normalised vector = vector / length (distance or also called hypotenuse)
	// Result has length 1: it keeps only the direction
	// x and y will range from -1 to 1
	// Multiply it by any amount (e.g. depth push back out of collision) to move that far in that direction
	// Default Pushback Distance #define PUSHBACK_RATIO 0.5f which is define in constants
	// lhs->x -= report.normal_x * report.depth * PUSHBACK_RATIO;
	// lhs->y -= report.normal_y * report.depth * PUSHBACK_RATIO;
	// rhs->x += report.normal_x * report.depth * PUSHBACK_RATIO;
	// rhs->y += report.normal_y * report.depth * PUSHBACK_RATIO;

	if (distance > 0.0f)
	{
		report.normal_x = distance_between_x / distance;
		report.normal_y = distance_between_y / distance;
	}
	else
	{
		// Same centre: no direction (cute_c2 picks up/down)
		report.normal_x = 0.0f;
		report.normal_y = 1.0f;
	}

	// How far? Sum of radiuses minus actual distance
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