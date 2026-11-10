#include "game.h"

// Helper function to initialise an NPC based on index
static void NPCFactory(NPC *npc, int typeIndex)
{
	switch (typeIndex) // CIRCLE, AABB, CAPSULE
	{
	case 0:
		npc->type = CIRCLE;
		npc->collider.circle.p = c2V(200.0f, 200.0f); // Position
		npc->collider.circle.r = 30.0f;				  // Radius
		npc->color = BLUE;
		break;

	case 1:
		npc->type = AABB;
		npc->collider.aabb.min = c2V(300, 150); // Top-left corner
		npc->collider.aabb.max = c2V(350, 230); // Bottom-right corner
		npc->color = BLUE;
		break;

	case 2:
		npc->type = CAPSULE;
		npc->collider.capsule.a = c2V(500.0f, 100.0f); // Endpoint A
		npc->collider.capsule.b = c2V(700.0f, 400.0f); // Endpoint B
		npc->collider.capsule.r = 3.0f;				   // Set to 1.0f for a thin line
		npc->color = BLUE;
		break;
	}

	npc->isColliding = false; // Initialise collision status
}

// Helper function to Draw an NPC
static void DrawNPC(const NPC *npc)
{
	switch (npc->type)
	{
	case CIRCLE:
		// Draw the circle
		DrawCircle(
			npc->collider.circle.p.x, // X position
			npc->collider.circle.p.y, // Y position
			npc->collider.circle.r,	  // Radius
			npc->color				  // Color
		);
		break;
	case AABB:
		// Draw the AABB rectangle
		DrawRectangle(
			(int)npc->collider.aabb.min.x,								// X position
			(int)npc->collider.aabb.min.y,								// Y position
			(int)(npc->collider.aabb.max.x - npc->collider.aabb.min.x), // Width
			(int)(npc->collider.aabb.max.y - npc->collider.aabb.min.y), // Height
			npc->color													// Color
		);
		break;
	case CAPSULE:
		// Draw the line (Capsule)
		DrawLineEx(
			(Vector2){npc->collider.capsule.a.x, npc->collider.capsule.a.y}, // Start position
			(Vector2){npc->collider.capsule.b.x, npc->collider.capsule.b.y}, // End position
			npc->collider.capsule.r,										 // Thickness
			npc->color														 // Color
		);
		// Draw End Cap A
		DrawCircleV(
			(Vector2){npc->collider.capsule.a.x, npc->collider.capsule.a.y}, // Center
			npc->collider.capsule.r,										 // Radius
			npc->color														 // Color
		);

		// Draw End Cap B
		DrawCircleV(
			(Vector2){npc->collider.capsule.b.x, npc->collider.capsule.b.y}, // Center
			npc->collider.capsule.r,										 // Radius
			npc->color														 // Color
		);																	 // Color

		break;
	}
}

// Initialise Game Data
void InitGame(GameData *data)
{
	TraceLog(LOG_INFO, "Game Initialising");

	data->points = 0; // Initialise points to zero

	data->collisionCounter = 0; // Initialise collision counter to zero
	data->message[0] = '\0';	// Initialise message to empty string

	// Initialise NPCs
	for (int i = 0; i < NUM_NPCS; i++)
		NPCFactory(&data->npcs[i], i); // Create NPC based on index

	// Initialise player circle
	data->player.circle.p = c2V(0, 0); // c2v position cute_c2 vector
	data->player.circle.r = 10.0f;	   // Player radius note float
	data->player.color = GREEN;		   // Player color

	// Load player texture
	data->player.texture = LoadTexture("resources/player.png");

	TraceLog(LOG_INFO, "Game Initialised");
}

// Update Game Data
void UpdateGame(GameData *data)
{
	// Player follows mouse position
	Vector2 mousePosition = GetMousePosition(); // raylib vector2

	// Update player position based on mouse
	data->player.circle.p = c2V(mousePosition.x, mousePosition.y);

	bool collisionDetected = false; // Flag to track if any collision occurs

	// Check for collisions with all NPCs
	// loop through NPCs
	for (int i = 0; i < NUM_NPCS; i++)
	{
		NPC *npc = &data->npcs[i];

		bool collision = false; // Track collision for NPC

		switch (npc->type)
		{
		case CIRCLE:
			// Circle vs Circle collision (cute_c2 built-in)
			collision = c2CircletoCircle(npc->collider.circle, data->player.circle);
			if (collision)
			{
				// Compute one or two points that represent the point of contact.
				// Resolve and prevent shapes from overlapping (by pushing back player), below is where
				// its used as a collision response
				// If no collision occured the count member of the manifold struct is set to 0.
				c2CircletoCircleManifold(data->player.circle, npc->collider.circle, &npc->manifold);

				// Response to circle to circle collisions
				if (npc->manifold.count > 0)
				{
					// Simple collision response: push the player circle out of the NPC circle along the normal
					// npc->manifold.n is the collision normal
					// npc->manifold.depths[0] is the penetration depth
					float depth = npc->manifold.depths[0];
					// Does not allow the player to penetrate the circle
					data->player.circle.p = c2Sub(data->player.circle.p, c2Mulvs(npc->manifold.n, depth + PUSHBACK_DISTANCE));
				}
			}
			break;

		case AABB:
			// Circle vs AABB collision (cute_c2 built-in)
			collision = c2CircletoAABB(data->player.circle, npc->collider.aabb);
			break;

		case CAPSULE:
			// Circle vs Capsule collision (cute_c2 built-in)
			collision = c2CircletoCapsule(data->player.circle, npc->collider.capsule);
			break;
		}

		npc->color = (collision) ? RED : BLUE;

		// Update collision counter only on new collision event
		if (collision && !npc->isColliding)
		{
			data->collisionCounter++; // one event per NPC contact start

			// Example: Update points add game logic here
			data->points += 10; // Increment points as an example
		}

		// Update collision
		npc->isColliding = collision; // Update NPC collision status

		// If a collision is detected with this NPC, set the overall flag
		collisionDetected |= collision;
	}

	// Change player color on collision
	if (collisionDetected)
	{
		// Collision detected between player circle and NPC circle
		data->player.color = RED; // Change player color on collision
	}
	else
	{
		data->player.color = GREEN; // Reset player color if no collision
	}

	// Update collision status message after checking all NPCs
	snprintf(data->message, sizeof(data->message), "Counter : %d Collision : %s", data->collisionCounter, (collisionDetected ? "Collision" : "All Safe"));
}

// Draw Game Data
void DrawGame(const GameData *data)
{
	// Points display
	char points[80]; // Increased buffer size to prevent overflow
	snprintf(points, sizeof(points), "Points : %d", data->points);
	DrawText(points, 190, 40, 20, DARKBLUE);

	// Draw NPCs
	for (int i = 0; i < NUM_NPCS; i++)
		DrawNPC(&data->npcs[i]);

	// Draw Player Texture (centred on circle)
	DrawTexture(data->player.texture,											  // Player Texture
				(int)(data->player.circle.p.x - data->player.texture.width / 2),  // X Center texture on circle
				(int)(data->player.circle.p.y - data->player.texture.height / 2), // Y Center texture on circle
				WHITE															  // Tint color
	);

	// Player draw over NPCs note Draw Last | Draws on Top | Draw Order
	DrawCircle((int)(data->player.circle.p.x), // X position
			   (int)(data->player.circle.p.y), // Y position
			   (int)(data->player.circle.r),   // Radius
			   data->player.color			   // Color
	);										   // Draw Player

	// Draw Collision Message
	int textWidth = MeasureText(data->message, 20);

	// Center the text at the bottom of the screen
	int xPosition = (SCREEN_WIDTH - textWidth) / 2;
	int yPosition = SCREEN_HEIGHT - 40; // 20 for font 20 Margin
	DrawText(data->message, xPosition, yPosition, 20, LIGHTGRAY);
}

// Close Game and free resources
void CloseGame(GameData *data)
{
	// Uload player texture
	UnloadTexture(data->player.texture);

	// Free up and resources
	free(data); // Free the allocated memory for GameData

	TraceLog(LOG_INFO, "Game Closed");
}
