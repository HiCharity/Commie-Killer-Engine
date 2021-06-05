
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <cwchar>
#include <dwmapi.h>
#include <sstream>
#include <WinUser.h>


//generic enemies have IDs starting at GENERIC_ENEMY_START_ID
#define GENERIC_ENEMY_START_ID 100
#define GENERIC_DEMON_START_ID 200

//total number of generic enemies (not including bosses)
#define NUM_ENEMIES 50

//X and Y sizes for map
#define X_AXIS 140
#define Y_AXIS 106

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
			"############################################################################################################################################"
			"#.......#..............................................#...............................#...................................................#"
			"#.......#................############################..#...................................................................................#"
			"#...#...#......###########.......................................................................................#...........#.............#"
			"#.......#......#......................................................#.........................#..........................##########......#"
			"#..............#................#.....................................#......................................................#.............#"
			"#.......#......####............................................###############.............................................................#"
			"#.......#.........####.........................#......................#.........................#..............###.........................#"
			"#.......#.........#...................................................#.......................................................##############"
			"#################.#.............#.................................................................................................#........#"
			"#.................#...............................................................................................................#........#"
			"#.................########................................#............................#..........................................#...##...#"
			"#............######......##########################################################################################################........#"
			"#####....................#########............................####............................####........................#########........#"
			"#####....................#.................................................................................................................#"
			"#####...................................#########............................####..........................##########......................#"
			"#........................#.................................................................................................................#"
			"#........................#########............................####............................####........................#########........#"
			"#............######......############################################################################################################......#"
			"######..##################........................................................................................................#........#"
			"#.................#......#........................................................................................................#........#"
			"#.................#.................#...........############.................................##...................................#........#"
			"#...#.......#.....#...............#####..............##.................................############..............................#####..###"
			"#.................#...............................................................................................................#........#"
			"#.................#......#.................................................................................................................#"
			"###################.########################################################################################################################"
			"#.....#................#..........................................................................................#........................#"
			"#.....#................#..........................................................................................#........................#"
			"#.....#................#.........................................#................................................#.........#..............#"
			"#............###########.........................................#.............................#..................#........................#"
			"#............#.........#.............................#...........#....................................#...........#........................#"
			"#.....#......#.........#.........................................#.........................................................................#"
			"#.....#......#.........#.............#...........................#...............................#......................#..................#"
			"#.....#......#.........#.........................................#...........##............................................................#"
			"#######......#.........#.........................................#................................................#........................#"
			"#.....#......#.........#.........................................#.........................................................................#"
			"#.....#......#.........#....##...................................#................############################..............#..............#"
			"#.....#......#.........#.........................#####.....................................................................................#"
			"#............#.........#...................................................................................................................#"
			"#............#.........#.......................................................#................................#..........................#"
			"#.....#......#.........#...................................................................................................................#"
			"#.....#......#.........#..........#......#..............#..................................................................................#"
			"#.....#......#.........#........................................................................................#..........................#"
			"#.....#......#..............................................................................#..............................................#"
			"#######......#.......................................................................................#.......................#.............#"
			"#.....#......#...........................#.................................................................................................#"
			"#.....#......#.........#.................#.......................##........................................................................#"
			"#.....#......#.........#.................#.........................................................###.....................................#"
			"#.....#......#.........#.............................................................................#..........#..........................#"
			"#.....#......#.........#......................................................#......................#.....................................#"
			"#............#.........#...............#...#.........................................................#.....................................#"
			"#............#.........#..........................................#..................................#.....................................#"
			"#.....#......#.........#...................................................................................................................#"
			"#.....#......#.........#.................#.................................................................................................#"
			"#.....#......###########.................#............................................#....................................#..#............#"
			"#.....#................#.................#................................................................................#....#...........#"
			"#.....#................####..............................................................................................#......#..........#"
			"#.....#................#................................................................................................#........#.........#"
			"##########..############............................................................................#.............#....#..........##########"
			"#...................................................................................................#.............#...#....................#"
			"#...................................................................................................#.............#..#.....................#"
			"#................................................................................#.......#..........#.............#.#......................#"
			"#...............................................................................#........#..........#.............##########################"
			"################################################################################........#...........#......................................#"
			"#........#.............................................................................#............#......................................#"
			"#........#..################################################################################################################################"
			"#............#..................#.....#....#............................................#..###......................................###....#"
			"#.......................................................................................#.....###................................###.......#"
			"#........#..............................................................................#........###...........######.........###..........#"
			"#.......................#...............................................................#...........###....................###.............#"
			"#...............................#.....#.................................................#..............###..............###................#"
			"#........#...#.................................#........................................#........#........###........###........#..........#"
			"#.......................................................................................#........#................###...........#..........#"
			"#...............#......#................................................................#........#.............#................#..........#"
			"#................................................#.#....#...#....#...#...#.....#....#...#...................###.....###....................#"
			"############################################............................................#................###...........###.................#"
			"#..........................................#............................................#.............###.................###..............#"
			"#..........................................#......#....#.........#...#...#...#...#......#..........###.........######........###...........#"
			"#......#######.............................#............................................#.......###.............................###........#"
			"#..........................................#.............#.............#................#....###...................................###.....#"
			"#..........................................#............................................#.###.........................................###..#"
			"#..........................................#............................................##################################################.#"
			"#.................##########...............#...#...#.......................................................................................#"
			"#..........................................#..............#................................................................................#"
			"#..........................................#...............................................................................................#"
			"#..........................................#.......#....................................#..................................................#"
			"#...########...............................#..............#.............................#............#######################################"
			"#..........................................#............................................#..................................................#"
			"#..........................................#............................................#..................................................#"
			"#..........................................#...#........................................#..................................................#"
			"#.................#########..............##......................................##.....#.........########################.................#"
			"#......................................##......................................##........#...............................#.................#"
			"#....................................##........##............................##...........#..............................#.................#"
			"#.................................###......................................##..............#.............................#.................#"
			"#..............................###.......................................##.................#............................##########........#"
			"#...........................###................#.......................##.............##.....#...........................#.................#"
			"#........................###..........#..................................##...................#..........................#.................#"
			"#.....................###..................................................##....##............#.........................#.................#"
			"#..................###................#......................................##.................#........................#.................#"
			"#...............###......#....#................................................##.......###......##..........###############################"
			"#...........####.....#...........................................................##................##......................................#"
			"#...........#......................................................................##................##....................................#"
			"#...........#............#...........................................................##................##..................................#"
			"#.............................#........................................................####..............##................................#"
			"#..........................................................................................####............##..............................#"
			"############################################################################################################################################";
		
		vWorldSize = { X_AXIS, Y_AXIS };

		gfxWall.Load("./gfx/dng_wall1.png");
		gfxEnemy.Load("./gfx/dng_enemy.png");
		gfxDemon.Load("./gfx/demon.png");
		gfxUn.Load("./gfx/un.png");
		gfxOracle.Load("./gfx/oracle.png");
		gfxBall.Load("./gfx/dng_ball.png");
		gfxZi.Load("./gfx/zi.png");
		gfxSky.Load("./gfx/bk.jpg");
		gfxFloor.Load("./gfx/fl.jpg");
		gfxPill.Load("./gfx/pill.png");
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
			p = gfxSky.Sprite()->Sample(sample_x, sample_y);
				//olc::DARK_RED + olc::VERY_DARK_GREEN + olc::VERY_DARK_RED;
			break;

		case olc::rcw::Engine::CellSide::Bottom: // Location is "Ground"
			p = gfxFloor.Sprite()->Sample(sample_x, sample_y);
				//olc::DARK_GREY;
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
		if (id >= GENERIC_ENEMY_START_ID && id < GENERIC_DEMON_START_ID) p = gfxEnemy.Sprite()->Sample(sample_x, sample_y);
		if (id >= GENERIC_DEMON_START_ID) p = gfxDemon.Sprite()->Sample(sample_x, sample_y);

		if (id == 2)
		{
			p = gfxBall.Sprite()->Sample(sample_x, sample_y);
		}
		if (id == 3)
		{
			p = gfxPill.Sprite()->Sample(sample_x, sample_y);
		}
		if (id == 5)
		{
			p = gfxZi.Sprite()->Sample(sample_x, sample_y);
		}
		if (id == 6)
		{
			p = gfxUn.Sprite()->Sample(sample_x, sample_y);
		}
		if (id == 7)
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
	olc::Renderable gfxBall;
	olc::Renderable gfxZi;
	olc::Renderable gfxSky;
	olc::Renderable gfxFloor;
	olc::Renderable gfxPill;
	olc::Renderable gfxUn;
	olc::Renderable gfxDemon;
	olc::Renderable gfxOracle;
};



class RayCastWorldDemo_SIMPLE : public olc::PixelGameEngine
{
public:
	RayCastWorldDemo_SIMPLE()
	{
		sAppName = "Commie Killer 2069";
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
			enemy[i]->pos = { float(rand() % 140) + 18.5f, float(rand() % 106) + 0.5f };
			enemy[i]->bVisible = true;
			enemy[i]->bNotifySceneryCollision = true;
			enemy[i]->vel = { 5.0f, 5.0f };
			pGame->mapObjects.insert_or_assign(enemy[i]->nGenericID, enemy[i]);

		}

		//create array of enemy object objects
		std::shared_ptr<olc::rcw::Object> demon[NUM_ENEMIES];
		//instantiate each enemy
		for (int i = 0; i < NUM_ENEMIES; i++) {
			demon[i] = std::make_shared<olc::rcw::Object>();
			demon[i]->nGenericID = i + GENERIC_DEMON_START_ID; //range of IDs is GENERIC_ENEMY_START_ID to (GENERIC_ENEMY_START_ID + NUM_ENEMIES -1) 
			demon[i]->pos = { float(rand() % 140) + 18.5f, float(rand() % 106) + 0.5f };
			demon[i]->bVisible = true;
			demon[i]->bNotifySceneryCollision = true;
			demon[i]->vel = { 7.5f, 7.5f };
			pGame->mapObjects.insert_or_assign(demon[i]->nGenericID, demon[i]);

		}

		// Add an object "zi"
		std::shared_ptr<olc::rcw::Object> zi = std::make_shared<olc::rcw::Object>();
		zi->nGenericID = 5;
		zi->iEnemyHealth = 100;
		zi->pos = { float(rand() % 140) + 18.5f, float(rand() % 106) + 0.5f };
		zi->bVisible = true;
		zi->bNotifySceneryCollision = true;
		zi->vel = { 3.0f, 3.0f };
		pGame->mapObjects.insert_or_assign(5, zi);

		// Add an object "un"
		std::shared_ptr<olc::rcw::Object> un = std::make_shared<olc::rcw::Object>();
		un->nGenericID = 6;
		un->iEnemyHealth = 25;
		un->pos = { float(rand() % 140) + 18.5f, float(rand() % 106) + 0.5f };
		un->bVisible = true;
		un->bNotifySceneryCollision = true;
		un->vel = { 8.0f, 8.0f };
		pGame->mapObjects.insert_or_assign(6, un);

		// Add an object "oracle"
		std::shared_ptr<olc::rcw::Object> oracle = std::make_shared<olc::rcw::Object>();
		oracle->nGenericID = 7;
		oracle->iEnemyHealth = 50;
		oracle->pos = { float(rand() % 140) + 18.5f, float(rand() % 106) + 0.5f };
		oracle->bVisible = true;
		oracle->bNotifySceneryCollision = true;
		oracle->vel = { 5.0f, 5.0f };
		pGame->mapObjects.insert_or_assign(7, oracle);

		// Add an object "pill"
		std::shared_ptr<olc::rcw::Object> pill = std::make_shared<olc::rcw::Object>();
		pill->nGenericID = 3;
		pill->pos = { 22.0f, 22.0f };
		pill->bVisible = true;
		pill->bNotifySceneryCollision = true;
		pGame->mapObjects.insert_or_assign(3, pill);
		
		

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		

		// Handle User Input =================================================

		auto& player = pGame->mapObjects[0];
		auto& ball = pGame->mapObjects[2];
		auto& pill = pGame->mapObjects[3];
		auto& zi = pGame->mapObjects[5];
		auto& un = pGame->mapObjects[6];
		auto& oracle = pGame->mapObjects[7];

		if (GetKey(olc::Key::A).bHeld) // Turn Left
			player->Turn(-fPlayerMoveSpeed * 0.15f * fElapsedTime);

		if (GetKey(olc::Key::D).bHeld) // Turn Right
			player->Turn(+fPlayerMoveSpeed * 0.15f * fElapsedTime);

		// Reset speed and velocity so player doesnt move if keys are not pressed
		player->Stop();

		// Walk Forward
		if (GetKey(olc::Key::ESCAPE).bHeld) return(0);
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
			ball->vel = olc::vf2d(std::cos(player->fHeading), std::sin(player->fHeading)) * 48.0f;
			ball->bCollideWithScenery = false;
		}

		// Update & Render World ==================================================

		// Update ray cast world engine - this will move the player object
		pGame->Update(fElapsedTime);

		// Link the camera to the play position
		pGame->SetCamera(player->pos, player->fHeading);

		// Render the scene!
		pGame->Render();

		//Demon
		olc::Sprite* sprite;
		sprite = new olc::Sprite("./gfx/dng_hud.png");
		DrawSprite({ 0,153 }, sprite);
		delete sprite;
		
		
			
		

		// Draw the players position, cos why not?
		
		olc::Sprite* sprite0;
		sprite0 = new olc::Sprite("./gfx/Untitled-1.png");
		DrawSprite({ 97,152 }, sprite0);
		delete sprite0;
		olc::Sprite* sprite1;
		sprite1 = new olc::Sprite("./gfx/Untitled-2.png");
		DrawSprite({ 97,151 }, sprite1);
		delete sprite1;
		olc::Sprite* sprite2;
		sprite2 = new olc::Sprite("./gfx/Untitled-3.png");
		DrawSprite({ 101,150 }, sprite2);
		delete sprite2;
		olc::Sprite* sprite3;
		sprite3 = new olc::Sprite("./gfx/Untitled-4.png");
		DrawSprite({ 101,149 }, sprite3);
		delete sprite3;
		olc::Sprite* sprite4;
		sprite4 = new olc::Sprite("./gfx/Untitled-5.png");
		DrawSprite({ 107,148 }, sprite4);
		delete sprite4;
		olc::Sprite* sprite5;
		sprite5 = new olc::Sprite("./gfx/Untitled-6.png");
		DrawSprite({ 107,147 }, sprite5);
		delete sprite5;
		olc::Sprite* sprite6;
		sprite6 = new olc::Sprite("./gfx/Untitled-7.png");
		DrawSprite({ 112,146 }, sprite6);
		delete sprite6;
		olc::Sprite* sprite9;
		sprite9 = new olc::Sprite("./gfx/Untitled-7.png");
		DrawSprite({ 112,145 }, sprite9);
		delete sprite9;
		olc::Sprite* sprite12;
		sprite12 = new olc::Sprite("./gfx/Untitled-7.png");
		DrawSprite({ 112,144 }, sprite12);
		delete sprite12;
		olc::Sprite* sprite13;
		sprite13 = new olc::Sprite("./gfx/Untitled-7.png");
		DrawSprite({ 112,143 }, sprite13);
		delete sprite13;
		olc::Sprite* sprite7;
		sprite7 = new olc::Sprite("./gfx/Untitled-8.png");
		DrawSprite({ 116,142 }, sprite7);
		delete sprite7;
		olc::Sprite* sprite10;
		sprite10 = new olc::Sprite("./gfx/Untitled-8.png");
		DrawSprite({ 116,141 }, sprite10);
		delete sprite10;
		olc::Sprite* sprite11;
		sprite11 = new olc::Sprite("./gfx/Untitled-8.png");
		DrawSprite({ 116,140 }, sprite11);
		delete sprite11;
		olc::Sprite* sprite8;
		sprite8 = new olc::Sprite("./gfx/Untitled-9.png");
		DrawSprite({ 118,139}, sprite8);
		delete sprite8;

		
		

		// Draw the players position, cos why not?
		DrawString({ 144,157 }, "Health:", olc::BLACK);
		DrawString({ 199,157 }, player->fHealth.str(), olc::BLACK);
		DrawString({ 144,169 }, "Score:", olc::BLACK);
		DrawString({ 199,169 }, player->fScore.str(), olc::BLACK);
		if (player->kills > 0) {
			DrawString({ 70,20 }, "WORLD SAVED", olc::GREEN);
		}
		
		


		//Player Death
		if (player->iHealth <= 0) {
			return 0;
		}


		
		//ENEMY COLLISION DETECTION********************************************************************************************************************************

		//generic enemy collision
		for (int i = 0; i < NUM_ENEMIES; i++) {
			auto& enemy = pGame->mapObjects[i + GENERIC_ENEMY_START_ID];
			auto& demon = pGame->mapObjects[i + GENERIC_DEMON_START_ID];
			if ((player->pos - enemy->pos).mag2() <= (player->fRadius + enemy->fRadius) * (player->fRadius + enemy->fRadius))
			{
				player->fHealth -= { 1.0f, 1.0f};
				player->iHealth -= 1;
			}
			if ((ball->pos - enemy->pos).mag2() <= (ball->fRadius + enemy->fRadius) * (ball->fRadius + ball->fRadius))
			{
				player->fScore += { 1.0f, 1.0f};
				enemy->pos = { float(rand() % 140) + 18.5f, float(rand() % 106) + 0.5f };
				ball->bVisible = false;
			}
			if ((player->pos - demon->pos).mag2() <= (player->fRadius + demon->fRadius) * (player->fRadius + demon->fRadius))
			{
				player->fHealth -= { 3.0f, 3.0f};
				player->iHealth -= 3;
			}
			if ((ball->pos - demon->pos).mag2() <= (ball->fRadius + demon->fRadius) * (ball->fRadius + ball->fRadius))
			{
				ball->bVisible = false;
				player->fScore += { 5.0f, 5.0f};
				demon->pos = { float(rand() % 140) + 18.5f, float(rand() % 106) + 0.5f };
			}
		}


		//oracle collision
		if ((player->pos - zi->pos).mag2() <= (player->fRadius + zi->fRadius) * (player->fRadius + zi->fRadius))
		{
			player->fHealth -= { 10.0f, 10.0f};
			player->iHealth -= 10;
		}
		if ((ball->pos - zi->pos).mag2() <= (ball->fRadius + zi->fRadius) * (ball->fRadius + ball->fRadius))
		{
			zi->iEnemyHealth -= 1;
			ball->bVisible = false;
			if (zi->iEnemyHealth <= 0) {
				player->kills += 1;
				player->fScore += { 1000.0f, 1000.0f};
				zi->pos = { 0.0f, 0.0f };
			}
		}

		if ((player->pos - un->pos).mag2() <= (player->fRadius + un->fRadius) * (player->fRadius + un->fRadius))
		{
			player->fHealth -= { 5.0f, 5.0f};
			player->iHealth -= 5;
		}
		if ((ball->pos - un->pos).mag2() <= (ball->fRadius + un->fRadius) * (ball->fRadius + ball->fRadius))
		{
			un->iEnemyHealth -= 1;
			ball->bVisible = false;
			if (un->iEnemyHealth <= 0) {
				player->fScore += { 100.0f, 100.0f};
				un->pos = { 0.0f, 0.0f };
			}
		}

		if ((player->pos - oracle->pos).mag2() <= (player->fRadius + oracle->fRadius) * (player->fRadius + oracle->fRadius))
		{
			player->fHealth -= { 7.0f, 7.0f};
			player->iHealth -= 7;
		}
		if ((ball->pos - oracle->pos).mag2() <= (ball->fRadius + oracle->fRadius) * (ball->fRadius + ball->fRadius))
		{
			oracle->iEnemyHealth -= 1;
			ball->bVisible = false;
			if (oracle->iEnemyHealth <= 0) {
				player->fScore += { 500.0f, 500.0f};
				oracle->pos = { 0.0f, 0.0f };
			}
		}

		//pill collision
		if ((player->pos - pill->pos).mag2() <= (player->fRadius + pill->fRadius) * (player->fRadius + pill->fRadius))
		{
			olc::Sprite* sprite666;
			sprite666 = new olc::Sprite("./gfx/hud_demon.png");
			DrawSprite({ 0,153 }, sprite666);
			delete sprite666;
			player->fHealth += { 5.0f, 5.0f};
			player->iHealth += 5;
			pill->pos = { 0.0f, 0.0f };
		}

		//ENEMY COLLISION DETECTION********************************************************************************************************************************

		return true;
	}


private:
	float fPlayerMoveSpeed = 15.0f;
	std::unique_ptr<ExampleGame> pGame = nullptr;
};
