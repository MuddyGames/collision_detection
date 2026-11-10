// Please collision tests here

#include "tests.h"
#include "circle.h"

// Recommend starting here so you get familiar with cute_c2 API

void TestCollisions(void)
{
	TraceLog(LOG_INFO, "Collision Tests");

	// Using our Circle to circle
	Circle player;
	player.x = 1;
	player.y = 1;
	player.r = 1;

	Circle npc;
	npc.x = 1;
	npc.y = 1;
	npc.r = 1;

	int result = collision(player, npc);

	TraceLog(LOG_INFO, result ? "Simple Circle Collision" : "All Safe");

	player.x = 100;
	player.y = 100;
	player.r = 50;

	npc.x = 180;
	npc.y = 100;
	npc.r = 50;

	result = collision(player, npc);

	TraceLog(LOG_INFO, result ? "Simple Circle Collision" : "All Safe");

	npc.x = 180;
	npc.y = 180;
	npc.r = 50;

	result = collision(player, npc);

	TraceLog(LOG_INFO, result ? "Simple Circle Collision" : "All Safe");

	// Collision Report: same circles, so predict first!
	// Centres 80 apart, radii add to 100 -> depth 20, normal (1, 0)
	CollisionReport report = collisionReport(player, npc);

	TraceLog(LOG_INFO, "Collision Report as follows: count=%d depth=%.1f n=(%.2f, %.2f) contact=(%.1f, %.1f)",
			 report.count, report.depth, report.normal_x, report.normal_y, report.contact_x, report.contact_y);

	// Fix it: push player back out
	resolveCollision(&player, report);

	npc.x = 180;
	npc.y = 100;

	report = collisionReport(player, npc);

	TraceLog(LOG_INFO, "Collision Report as follows: count=%d depth=%.1f n=(%.2f, %.2f) contact=(%.1f, %.1f)",
			 report.count, report.depth, report.normal_x, report.normal_y, report.contact_x, report.contact_y);

	// Fix it: push player back out
	resolveCollision(&player, report);

	TraceLog(LOG_INFO, "Player after resolve: (%.1f, %.1f) -> %s",
			 player.x, player.y,
			 collision(player, npc) ? "Touching" : "All Safe");

	// Note: after resolving they are exactly touching, and our
	// collision() uses <= so touching still counts as a collision

	player.x = 100; // put the player back for the next tests
	player.y = 100;

	npc.x = 180;
	npc.y = 180;
	npc.r = 50;

	result = collision(player, npc);

	TraceLog(LOG_INFO, result ? "Simple Circle Collision" : "All Safe");

	// Test 1: Circle to Circle
	c2Circle c1 = {{100, 100}, 50};
	c2Circle c2 = {{180, 100}, 50};

	TraceLog(LOG_INFO, "Circle-Circle (overlapping ?): %s\n",
			 c2CircletoCircle(c1, c2) ? "PASS" : "FAIL");

	// Test 2: Ray to Circle
	// Ray starting at (0,100) going right with length 200
	c2Ray ray = {{0, 100}, {1, 0}, 200};

	// c2Raycast to store result
	c2Raycast out;

	TraceLog(LOG_INFO, "Ray-Circle (hit ?): %s\n",
			 c2RaytoCircle(ray, c1, &out) ? "PASS" : "FAIL");

	// Add more tests...
}