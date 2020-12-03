
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <cwchar>

//generic enemies have IDs starting at GENERIC_ENEMY_START_ID
#define GENERIC_ENEMY_START_ID 100

//total number of generic enemies (not including bosses)
#define NUM_ENEMIES 99

//X and Y sizes for map
#define X_AXIS 64
#define Y_AXIS 84

//X and Y values for screen size
#define X_PIXELS 240
#define Y_PIXELS 180


// ADAPTOR CLASS - Override the RayCastWorld Engine and fill in the blanks!
class ExampleGame : public olc::rcw::Engine
{
public:
	ExampleGame(const int screen_w, const int screen_h, const float fov)
		: olc::rcw::Engine(screen_w, screen_h, fov)
	{
		sMap =
			"################################################################"
			"#...................................#..........................#"
			"#...................................#..........................#"
			"################################....############################"
			"#..............................#...............................#"
			"#..#############.###########...#...............................#"
			"#..#.......................#...############################....#"
			"#..#......................................................#....#"
			"#..#.......................#...#####.......#####..........#....#"
			"#..#########################...#...#.......#####..........#....#"
			"#..............................#...#.......#####..........#....#"
			"###############..###############...#.......#####...............#"
			"#.............................#....#...........................#"
			"#.............................##################################"
			"#.............................#.......#........................#"
			"#.............######..........#.......#......................###"
			"#.............#.......................#..............#.........#"
			"#.............#.......................################.........#"
			"#.....###.....#.........#.........#............................#"
			"#.....###.....#...........................#....................#"
			"#.....###.....#.....................................#..........#"
			"#.............#.....................#..........................#"
			"#.............#.....#........#.............#.................###"
			"#########..####................................................#"
			"#..........#.............................................#.....#"
			"#..........#.........#.........................................#"
			"############...............#...............#.............#.....#"
			"#.............####.........................................##..#"
			"#................#..................................#..........#"
			"#..............###................#.......#..............#.....#"
			"#................########......................................#"
			"#.....................................................#........#"
			"#................................................#........#....#"
			"#....................#########...#########.....................#"
			"#.........##.........#...................#.....................#"
			"#..........#.........#...................#.....................#"
			"#..........#.........#...................#............####.....#"
			"#......#####.........#...................#...............#.....#"
			"#....................#...................#.....................#"
			"#....................######.........######.....................#"
			"#####...###########..#....#.........#....#..........######.....#"
			"#.......#...#........#....#.........#....#............##.......#"
			"#.......#...#........#...................#.....................#"
			"#.......#...#........#...................#.....................#"
			"#.......#...#........#...................#.....................#"
			"#..##########...######...................#.....................#"
			"#....................########.....########..####################"
			"#...........................#.....#......................#.....#"
			"#...........................#.....#.............#..............#"
			"#...........................#.....############.................#"
			"############....##..........#.....#............................#"
			"#.......................#####.....#............................#"
			"#................#..........#.....#....................#########"
			"#...........................#.....#............................#"
			"#......#.............#......#.....#............................#"
			"#...........#################.....###################..##......#"
			"#...........#.........#...........#..............#.............#"
			"#...........#.........#...........#..............#.............#"
			"#...........#.........#...........##########.....#.....#.......#"
			"#...........#.........#....................#.....#.............#"
			"#...........#....................................#.........#...#"
			"#....###....#....................................#.............#"
			"#...........#........######################......#...........###"
			"#.....#....#......................................#............#"
			"#.....#...#....................###.................#...........#"
			"##....#..#..........................................#..........#"
			"#.......#............######################..........#.........#"
			"#......#........................##....................#.....####"
			"#.....###################.......##.....................#.......#"
			"#...............................##.....................#.......#"
			"#...............................##.....................#.......#"
			"#......#.............###########################......#........#"
			"#.......#............................................#........##"
			"###......############################################..........#"
			"#.........#........#................#.....#........#..........##"
			"#..........#.......#................#.....#.......########.....#"
			"#...........#......#....###.........#.....####...#...##........#"
			"#...........#......#......#.........#.....#......#.............#"
			"#######.....#......#......########..#######......#........##...#"
			"#...........#....#####....#...............#......#.............#"
			"#...........#.............#...............#...........#........#"
			"#......#....#.............#...............######...........#####"
			"#.....#######.............#...............#................#...#"
			"#.........................#...............#........####....#...#"
			"#.........................#...............#....................#"
			"################################################################";

		vWorldSize = { X_AXIS, Y_AXIS };

		gfxDoor.Load("./gfx/dng_wall2.png");
		gfxWall.Load("./gfx/dng_wall1.png");
		gfxEnemy.Load("./gfx/dng_enemy.png");
		gfxShroom.Load("./gfx/shroom.png");
		gfxBall.Load("./gfx/dng_ball.png");
		gfxOracle.Load("./gfx/oracle.png");
	}

protected:
	// User implementation to retrieve appropriate graphics for scenery
	olc::Pixel SelectSceneryPixel(const int tile_x, const int tile_y, const olc::rcw::Engine::CellSide side, const float sample_x, const float sample_y, const float distance) override
	{
		olc::Pixel p;

		// Choose appropriate colour
		switch (side)
		{
		case olc::rcw::Engine::CellSide::Top: // Location is "Sky"
			p = olc::VERY_DARK_GREEN;
			break;

		case olc::rcw::Engine::CellSide::Bottom: // Location is "Ground"
			p = olc::DARK_GREY;
			break;

		default: // Location is "Wall"
			//p = olc::DARK_RED;
			//if (sample_x < 0.05f || sample_x > 0.95f || sample_y < 0.05f || sample_y > 0.95f)
			//	p = olc::BLACK;
			p = gfxWall.Sprite()->Sample(sample_x, sample_y);
		}

		// Apply directional lighting, by first creating a shadow scalar...
		float fShadow = 1.0f;
		switch (side)
		{
		case olc::rcw::Engine::CellSide::South: fShadow = 0.3f; break;
		case olc::rcw::Engine::CellSide::East:  fShadow = 0.3f; break;
		}

		// ...also shade by distance...
		float fDistance = 1.0f - std::min(distance / 32.0f, 1.0f);

		// ...and applying it to sampled pixel
		p.r = uint8_t(float(p.r) * fDistance);
		p.g = uint8_t(float(p.g) * fDistance);
		p.b = uint8_t(float(p.b) * fDistance);

		return p;
	}

	// User implementation to retrieve if a particular tile is solid
	bool IsLocationSolid(const float tile_x, const float tile_y) override
	{
		if (int(tile_x) >= 0 && int(tile_x) < vWorldSize.x && int(tile_y) >= 0 && int(tile_y) < vWorldSize.y)
			return sMap[int(tile_y) * vWorldSize.x + int(tile_x)] == '#';
		else
			return true;
	}


	// NOTE! Objects are not used in this demonstration ===================

	// User implementation to retrieve dimensions of an in game object
	float GetObjectWidth(const uint32_t id) override
	{
		if (id == 28)
			return 2.0f;
		return 1;
	}

	float GetObjectHeight(const uint32_t id) override
	{
		return 1;
	}

	// User implementation to retrieve appropriate graphics for objects
	olc::Pixel SelectObjectPixel(const uint32_t id, const float sample_x, const float sample_y, const float distance, const float angle) override
	{
		olc::Pixel p = olc::BLACK;


		//enemy sprites
		if (id >= GENERIC_ENEMY_START_ID) p = gfxEnemy.Sprite()->Sample(sample_x, sample_y);

		if (id == 28)
		{
			p = gfxDoor.Sprite()->Sample(sample_x, sample_y);
		}

		if (id == 1)
		{
			p = gfxShroom.Sprite()->Sample(sample_x, sample_y);
		}
		if (id == 2)
		{
			p = gfxBall.Sprite()->Sample(sample_x, sample_y);
		}
		if (id == 3)
		{
			p = gfxOracle.Sprite()->Sample(sample_x, sample_y);
		}

		return p;
	}

	virtual void HandleObjectVsScenery(std::shared_ptr<olc::rcw::Object> object, const int tile_x, const int tile_y, const olc::rcw::Engine::CellSide side, const float offset_x, const float offset_y)
	{
		switch (side)
		{
		case olc::rcw::Engine::CellSide::North:
		case olc::rcw::Engine::CellSide::South:
			object->vel.y *= -1.0f;
			break;

		case olc::rcw::Engine::CellSide::East:
		case olc::rcw::Engine::CellSide::West:
			object->vel.x *= -1.0f;
			break;
		}
	}

private:
	std::string sMap;
	olc::vi2d vWorldSize;
	olc::Renderable gfxWall;
	olc::Renderable gfxEnemy;
	olc::Renderable gfxShroom;
	olc::Renderable gfxBall;
	olc::Renderable gfxOracle;
	olc::Renderable gfxDoor;
};



class RayCastWorldDemo_SIMPLE : public olc::PixelGameEngine
{
public:
	RayCastWorldDemo_SIMPLE()
	{
		sAppName = "Commie Killer 1848";
	}


public:
	bool OnUserCreate() override
	{
		// Create game object
		pGame.reset(new ExampleGame(ScreenWidth(), ScreenHeight(), 3.14159f / 3.333f));

		//OST
		music();

		// Add an object "player"
		std::shared_ptr<olc::rcw::Object> player = std::make_shared<olc::rcw::Object>();
		player->pos = { 2.0f, 2.0f };
		player->bVisible = false;
		player->iHealth = 100;
		player->fHealth = { 100.0f , 100.0f };
		player->fScore = { 0.0f, 0.0f };
		player->fRadius = 0.5f;
		player->kills = 0;
		pGame->mapObjects.insert_or_assign(0, player);


		// Add an object "ball"
		std::shared_ptr<olc::rcw::Object> ball = std::make_shared<olc::rcw::Object>();
		ball->nGenericID = 2;
		pGame->mapObjects.insert_or_assign(2, ball);


		//create array of enemy object objects
		std::shared_ptr<olc::rcw::Object> enemy[NUM_ENEMIES];
		//instantiate each enemy
		for (int i = 0; i < NUM_ENEMIES; i++) {
			enemy[i] = std::make_shared<olc::rcw::Object>();
			enemy[i]->nGenericID = i + GENERIC_ENEMY_START_ID; //range of IDs is GENERIC_ENEMY_START_ID to (GENERIC_ENEMY_START_ID + NUM_ENEMIES -1) 
			enemy[i]->pos = { float(rand() % 64) + 0.5f, float(rand() % 84) + 0.5f };
			enemy[i]->bVisible = true;
			enemy[i]->bNotifySceneryCollision = true;
			enemy[i]->vel = { 3.0f, 3.0f };
			pGame->mapObjects.insert_or_assign(enemy[i]->nGenericID, enemy[i]);

		}

		// Add an object "shroom"
		std::shared_ptr<olc::rcw::Object> shroom = std::make_shared<olc::rcw::Object>();
		shroom->nGenericID = 1;
		shroom->pos = { 45.0f, 75.0f };
		shroom->bVisible = true;
		pGame->mapObjects.insert_or_assign(1, shroom);

		// Add an object "oracle"
		std::shared_ptr<olc::rcw::Object> oracle = std::make_shared<olc::rcw::Object>();
		oracle->nGenericID = 3;
		oracle->iEnemyHealth = 500;
		oracle->pos = { 36.0f, 82.0f };
		oracle->bVisible = true;
		oracle->bNotifySceneryCollision = true;
		oracle->vel = { 3.0f, 3.0f };
		pGame->mapObjects.insert_or_assign(3, oracle);

		// Add an object "door"
		std::shared_ptr<olc::rcw::Object> door = std::make_shared<olc::rcw::Object>();
		door->nGenericID = 28;
		door->pos = { 35.0f, 78.0f };
		door->bVisible = true;
		pGame->mapObjects.insert_or_assign(28, door);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Handle User Input =================================================

		auto& player = pGame->mapObjects[0];
		auto& shroom = pGame->mapObjects[1];
		auto& ball = pGame->mapObjects[2];
		auto& oracle = pGame->mapObjects[3];
		auto& door = pGame->mapObjects[28];

		if (GetKey(olc::Key::A).bHeld) // Turn Left
			player->Turn(-fPlayerMoveSpeed * 0.15f * fElapsedTime);

		if (GetKey(olc::Key::D).bHeld) // Turn Right
			player->Turn(+fPlayerMoveSpeed * 0.15f * fElapsedTime);

		// Reset speed and velocity so player doesnt move if keys are not pressed
		player->Stop();

		// Walk Forward
		if (GetKey(olc::Key::W).bHeld) player->Walk(+fPlayerMoveSpeed);
		// Walk Backwards
		if (GetKey(olc::Key::S).bHeld) player->Walk(-fPlayerMoveSpeed);
		// Strafe Right
		if (GetKey(olc::Key::E).bHeld) player->Strafe(+fPlayerMoveSpeed);
		// Strafe Left
		if (GetKey(olc::Key::Q).bHeld) player->Strafe(-fPlayerMoveSpeed);
		//Fire
		if (GetMouse(0).bHeld) {
			ball->pos = player->pos;
			ball->bVisible = true;
			ball->vel = olc::vf2d(std::cos(player->fHeading), std::sin(player->fHeading)) * 32.0f;
			ball->bCollideWithScenery = false;
		}

		// Update & Render World ==================================================

		// Update ray cast world engine - this will move the player object
		pGame->Update(fElapsedTime);

		// Link the camera to the play position
		pGame->SetCamera(player->pos, player->fHeading);

		// Render the scene!
		pGame->Render();

		// Draw the players position, cos why not?
		olc::Sprite* sprite;
		sprite = new olc::Sprite("./gfx/dng_hud.png");
		DrawSprite({ 0,153 }, sprite);
		delete sprite;


		// Draw the players position, cos why not?
		DrawString({ 144,157 }, "Health:", olc::BLACK);
		DrawString({ 199,157 }, player->fHealth.str(), olc::BLACK);
		DrawString({ 144,169 }, "Score:", olc::BLACK);
		DrawString({ 199,169 }, player->fScore.str(), olc::BLACK);
		if (player->kills > 0) {
			DrawString({ 70,142 }, "FUTURE SAVED", olc::RED);
		}


		//Player Death
		if (player->iHealth <= 0) {
			return 0;
		}


		if ((ball->pos - door->pos).mag2() <= (ball->fRadius + door->fRadius) * (ball->fRadius + ball->fRadius))
		{
			door->pos = { 1.0f, 64.0f };
			ball->bVisible = false;
		}

		if ((player->pos - shroom->pos).mag2() <= (player->fRadius + shroom->fRadius) * (player->fRadius + shroom->fRadius))
		{
			player->fScore += { 1000.0f, 1000.0f};
			shroom->pos = { 1.0f, 1.0f };
		}
		//ENEMY COLLISION DETECTION********************************************************************************************************************************

		//generic enemy collision
		for (int i = 0; i < NUM_ENEMIES; i++) {
			auto& enemy = pGame->mapObjects[i + GENERIC_ENEMY_START_ID];
			if ((player->pos - enemy->pos).mag2() <= (player->fRadius + enemy->fRadius) * (player->fRadius + enemy->fRadius))
			{
				player->fHealth -= { 1.0f, 1.0f};
				player->iHealth -= 1;
			}
			if ((ball->pos - enemy->pos).mag2() <= (ball->fRadius + enemy->fRadius) * (ball->fRadius + ball->fRadius))
			{
				player->fScore += { 50.0f, 50.0f};
				enemy->pos = { 1.0f, 1.0f };
				ball->bVisible = false;
			}

		}


		//oracle collision
		if ((player->pos - oracle->pos).mag2() <= (player->fRadius + oracle->fRadius) * (player->fRadius + oracle->fRadius))
		{
			player->fHealth -= { 15.0f, 15.0f};
			player->iHealth -= 15;
		}
		if ((ball->pos - oracle->pos).mag2() <= (ball->fRadius + oracle->fRadius) * (ball->fRadius + ball->fRadius))
		{
			oracle->iEnemyHealth -= 1;
			ball->bVisible = false;
			if (oracle->iEnemyHealth <= 0) {
				player->kills += 1;
				player->fScore += { 2000.0f, 2000.0f};
				oracle->pos = { 1.0f, 1.0f };
			}
		}

		//ENEMY COLLISION DETECTION********************************************************************************************************************************

		return true;
	}

private:
	float fPlayerMoveSpeed = 16.0f;
	std::unique_ptr<ExampleGame> pGame = nullptr;
};
